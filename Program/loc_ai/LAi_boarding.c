//  логика абордажа, переработка boal 28.04.06
#define BRDLT_SHIP	0
#define BRDLT_FORT	1
//not used
#define BRDLT_MAXCREW 44

#define LOCINITBRD_DEFAULTLOCATION "BOARDING_U_H_CS_T12"
#define LOCINITBRD_DEFAULTLOCATION_FORT "Any_fort_1"

#define MAX_GROUP_SIZE   13
#define MAX_MUSKETEER_SIZE   12
#define PLAYER_BOARDING_COEFF 0.75

bool   IsFort = false;
int    boarding_location = -1;
int    boarding_location_type = -1;
object boarding_fader;


int   boarding_player_crew = 0;
int   boarding_officers    = 0;
float boarding_player_base_crew    = 0.0; //boal
float boarding_player_crew_per_chr = 1.0;
int   boarding_player_crew_start   = 0; //sd

int   boarding_enemy_crew = 0;
float boarding_enemy_base_crew    = 0.0;
float boarding_enemy_crew_per_chr = 1.0;
int   boarding_enemy_crew_start   = 0; //sd

ref    boarding_enemy;
object boarding_adr[10];
float  boarding_exp = 0;
float  boarding_player_hp = 40;
float  boarding_enemy_hp = 40;
int    boarding_echr_index = -1;
int    boarding_erank = 10;
bool   LAi_boarding_process = false;
bool   Surrendered = false; // сдача в плен

int inside_ecrew_1, inside_ecrew_2;
//Процес абордажа
bool LAi_IsBoardingProcess()
{
	return LAi_boarding_process;
}

//Получить картинку для перехода в абордаж
string LAi_GetBoardingImage(ref echr, bool isMCAttack)
{
	ref mchr = GetMainCharacter();
	string deckID = "";
	isMCAttack   = true;// boal 110804 fix всегда герой
	if(isMCAttack)
	{
		deckID = GetShipLocationID(echr);
	}else{
		deckID = GetShipLocationID(mchr);
	}
	int locID = -1;
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(locID >= 0)
	{
		if(CheckAttribute(&Locations[locID], "image"))
		{
			if(Locations[locID].image != "")
			{
				return Locations[locID].image;
			}
		}
	}
	return "loading\jonny_load\abordage\abord_0"+rand(2)+".tga";
}

//Начать абордаж с главным персонажем
void LAi_StartBoarding(int locType, ref echr, bool isMCAttack)
{
    SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
	//ResetSoundScheme();
	ResetSound(); // new
	PauseAllSounds();

	if(sti(RealShips[sti(echr.Ship.Type)].BaseType) <= SHIP_OCEAN) {//не исследуем квестовые, и лодку с фортом
		sTemp = RealShips[sti(echr.Ship.Type)].BaseName;
		Pchar.Encyclopedia.(sTemp) = "1";
	}
	if(bFillEncyShips) {
		aref aShips;
		makearef(aShips, Pchar.Encyclopedia);
		int Sum = GetAttributesNum(aShips);
		if (Sum != sti(pchar.questTemp.shipsearchcount)) {
			pchar.questTemp.shipsearchcount = Sum;
			log_info(GetConvertStrWithReplace("Variable_LAi_boarding_1", "Logs.txt", "#space#", " ") + XI_Convertstring(sTemp) + GetConvertStrWithReplace("Variable_LAi_boarding_2", "Logs.txt", "#space#", " ") + pchar.questTemp.shipsearchcount + GetConvertStrWithReplace("Variable_LAi_boarding_3", "Logs.txt", "#space#", " "));
			if (pchar.questTemp.shipsearchcount == "124") UnlockAchievement("AchShipSearch",3);//почему 124? сумма же 125.
			if (sti(pchar.questTemp.shipsearchcount) >= 95) UnlockAchievement("AchShipSearch",2);
			if (sti(pchar.questTemp.shipsearchcount) >= 50) UnlockAchievement("AchShipSearch",1);
		}
	}

	bQuestCheckProcessFreeze = true;//fix

	EmptyAbordageCharacters();
	// NK -->
    isMCAttack = (locType == BRDLT_FORT);
    IsFort = isMCAttack;
	// NK <--
	//Установим обработчик на убийство группы
	SetEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill", 1);
	//Настроим интерфейс
	DeleteBattleInterface();
	InitBattleLandInterface();
	//StartBattleLandInterface();
	//Сохраним индекс врага
	boarding_echr_index = sti(echr.index);
	//Параметры сражающихся сторон
	ref mchr = GetMainCharacter();
	int mclass = GetCharacterShipClass(mchr);
	int mcrew = GetCrewQuantity(mchr);
	int mcrewBak;
	// Saving enemy captain rank for future use in CalculateAppropriateSkills (Gray 12.02.2005)
	mchr.EnemyRank = echr.rank

	DeleteAttribute(pchar, "abordage_active");
	// boal учет оружия 21.01.2004 -->
	Log_TestInfo(GetConvertStrWithReplace("Variable_LAi_boarding_4", "Logs.txt", "#space#", " ") + mcrew);
	mcrew = GetWeaponCrew(mchr, mcrew);

	// boal 21.01.2004 <--
	int eclass = GetCharacterShipClass(echr);
	int ecrew = GetCrewQuantity(echr);
	int ecrewBak;

    Log_TestInfo(GetConvertStrWithReplace("Variable_LAi_boarding_5", "Logs.txt", "#space#", " ") + mcrew + GetConvertStrWithReplace("Variable_LAi_boarding_6", "Logs.txt", "#space#", " ") + ecrew);

    boarding_location_type = locType;
	// Сдача в плен -->
	//квестовые не сдаются
    if (!CheckAttribute(echr, "DontRansackCaptain") && boarding_location_type != BRDLT_FORT) {
		if (CheckForSurrender(mchr, echr, 1) || TestRansackCaptain) {// 1 - это учет первый раз, до битвы на палубе
			echr.ship.crew.morale = 5;// после захвата у них мораль такая

			AddCrewMorale(mchr, 3);

			SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
			//Следующей локации нет
			DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
			boarding_location = -1;

			// Saved value is not needed anymore... (Gray 14.02.2005)
			DeleteAttribute(GetMainCharacter(), "EnemyRank");
			bQuestCheckProcessFreeze = false;//fix

			//Настроим интерфейс
			Log_SetActiveAction("Nothing");
			EndBattleLandInterface();
			//Выгружаемся в интерфейс

			ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),1.0, 2.0));
			LaunchRansackMain(pchar, echr, "crew");
			// на деле параметры LaunchRansackMain не важны совсем - все определеятеся от реалий - жив кэп и сколько у него матросов - их и обрабатываем
			// но они используются в сообщениях  crew - это сдался сразу
			LAi_boarding_process = false;
			Event(SHIP_CAPTURED, "l", sti(echr.index));
			return;
		}
	}
	// Сдача в плен <--

	// MusketsShoot -->
	float tmpDefence;
    if (CheckOfficersPerk(mchr, "MusketsShoot") && IsFort == false)
    {
        tmpDefence   = MakeFloat(GetSummonSkillFromName(echr, SKILL_DEFENCE)) / SKILL_MAX;
		ecrewBak = makeint(mcrew * 0.25 * AIShip_isPerksUse(CheckOfficersPerk(echr, "EmergentSurgeon"), 1.0, 0.75));//aw013
		ecrewBak = makeint(ecrewBak * (2.1 - tmpDefence) / 2.0);
		if (ecrewBak > ecrew) ecrewBak = ecrew;//aw013
		PlaySound("INTERFACE\_musketshot_" + rand(7) + ".wav");
		if (CheckAttribute(RealShips[sti(echr.Ship.Type)],"Tuning.HighBort")) ecrewBak = makeint(ecrewBak/2);
	    	if (S_armor(echr)) ecrewBak = makeint(ecrewBak/3); // СФ
		ecrew = ecrew - ecrewBak;
		Log_SetStringToLog(GetConvertStrWithReplace("Variable_LAi_boarding_7", "Logs.txt", "#space#", " ") + ecrewBak + GetConvertStrWithReplace("Variable_LAi_boarding_8", "Logs.txt", "#space#", " "));
	}
	if (CheckOfficersPerk(echr, "MusketsShoot") && IsFort == false)
	{
		tmpDefence  = MakeFloat(GetSummonSkillFromName(mchr, SKILL_DEFENCE)) / SKILL_MAX;
		mcrewBak = makeint(ecrew * 0.25 * AIShip_isPerksUse(CheckOfficersPerk(mchr, "EmergentSurgeon"), 1.0, 0.75));//aw013
		mcrewBak = makeint(mcrewBak * (2.1 - tmpDefence) / 2.0);
		if (mcrewBak > mcrew) mcrewBak = mcrew;//aw013
		PlaySound("INTERFACE\_musketshot_" + rand(7) + ".wav");
		if (CheckAttribute(RealShips[sti(mchr.Ship.Type)],"Tuning.HighBort")) mcrewBak = makeint(mcrewBak/2);
		if (S_armor(mchr)) mcrewBak = makeint(mcrewBak/3); // СФ
		mcrew = mcrew - mcrewBak;
		Log_SetStringToLog(GetConvertStrWithReplace("Variable_LAi_boarding_9", "Logs.txt", "#space#", " ") + mcrewBak + GetConvertStrWithReplace("Variable_LAi_boarding_10", "Logs.txt", "#space#", " "));
		Statistic_AddValue(mchr, "DeadCrewBoard", mcrewBak);
    }
    // MusketsShoot <--

	if(ecrew < 1) ecrew = 1;
	if(mcrew < 1) mcrew = 1;
	boarding_erank = sti(echr.rank);

	// база для расчета
	boarding_enemy_base_crew = ecrew;
	boarding_player_base_crew = mcrew;

	//бонус хп игроку при опыте+морали солдат выше среднего
	GetBoardingHP(mchr, echr, &boarding_player_hp, &boarding_enemy_hp);

	//Определяем цепь локаций для абордажа
	boarding_location = -1;

	string deckID = "";
	isMCAttack   = true;// boal 110804 fix всегда герой
	if(isMCAttack) {
		deckID = GetShipLocationID(echr);
	}
	else {
		deckID = GetShipLocationID(mchr);
	}
	int locID = -1;
	if(deckID != "") {
		locID = FindLocation(deckID);
		if(locID < 0) {
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(deckID == "") {
		if(locType == BRDLT_FORT) {
			deckID = LOCINITBRD_DEFAULTLOCATION_FORT;
		}
		else {
			deckID = LOCINITBRD_DEFAULTLOCATION;
		}
		locID = FindLocation(deckID);
	}
	if (locID < 0) {   // исключительная ситуация
		Trace("Boarding: ship location not found <" + deckID + ">, no start boarding");
		// Saved value is not needed anymore... (Gray 14.02.2005)
		DeleteAttribute(GetMainCharacter(), "EnemyRank");
	    bQuestCheckProcessFreeze = false;//fix

		if(boarding_location_type == BRDLT_SHIP) {
            ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),1.0, 2.0));
            SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
			LaunchRansackMain(GetMainCharacter(), echr, "captain");	  // на деле параметры LaunchRansackMain не важны совсем - все определеятеся от реалий
            LAi_boarding_process = false;
			Event(SHIP_CAPTURED, "l", sti(echr.index)); // to_do can be harmfull
		}
		else {
			if (boarding_location_type == BRDLT_FORT) {
                ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),1.0, 2.0));
                SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
				Event(FORT_CAPTURED, "l", sti(echr.index));
				echr.Ship.Crew.Quantity = 10 + rand(350); // рабы (остатки выживших)
                LaunchFortCapture(echr);
                LAi_boarding_process = false;
			}
			else {
				Trace("Boarding: unknow boarding location type");
			}
		}
		return;
	}

	pchar.abordage = 0;
	//Определяем размеры команд
	boarding_enemy = echr;

	//Максимальное количество человек на корабле
	int maxcrew = MAX_GROUP_SIZE;
	int idecknum;
    if(CheckAttribute(&Locations[locID], "boarding.locatorNum")) {
		maxcrew = sti(Locations[locID].boarding.locatorNum);
	}
	//TODO: убрать этот костыль и разобраться как выставлять размер массива
	if (IsFort) {
		idecknum = FindLocation(Locations[locID].boarding.nextdeck);
		if(CheckAttribute(&Locations[idecknum], "boarding.locatorNum")) {
			maxcrew += sti(Locations[idecknum].boarding.locatorNum);
		}
		idecknum = FindLocation("Boarding_bastion2");//fixme: у boarding_bastion1 неправильное число локаторов, boarding_bastion не юзается.
		if(CheckAttribute(&Locations[idecknum], "boarding.locatorNum")) {
			maxcrew += sti(Locations[idecknum].boarding.locatorNum);
		}
	}
	else if (eclass <= 2) {
		idecknum = FindLocation("Boarding_GunDeck");//nextdeck не прописан в LocationInitBoarding
		if(CheckAttribute(&Locations[idecknum], "boarding.locatorNum")) {
			maxcrew += sti(Locations[idecknum].boarding.locatorNum) - 1;//плюсует лишнюю тушку
		}
		idecknum = FindLocation("Boarding_Cargohold");
		if(CheckAttribute(&Locations[idecknum], "boarding.locatorNum")) {
			maxcrew += sti(Locations[idecknum].boarding.locatorNum) - 1;
		}
	}
	else if (eclass <= 4) {
		idecknum = FindLocation("Boarding_Campus");
		if(CheckAttribute(&Locations[idecknum], "boarding.locatorNum")) {
			maxcrew += sti(Locations[idecknum].boarding.locatorNum) - 1;
		}
	}
	else if (eclass == 5) {
		idecknum = FindLocation("Boarding_Cargohold");
		if(CheckAttribute(&Locations[idecknum], "boarding.locatorNum")) {
			maxcrew += sti(Locations[idecknum].boarding.locatorNum) - 1;
		}
	}
	// на тартане каюты нет
	if (boarding_location_type == BRDLT_SHIP && eclass != 7) {
    	boarding_enemy.ShipCabinLocationId = GetShipCabinID(echr);
	}

	//Отношение сторон

	// fort -->
	// boal 21.01.2004 -->
	int cn, j, compCrew;
    ref officer;
    if(IsFort) {
        mcrew = mcrew + GetTroopersCrewQuantity(GetMainCharacter()); // если нет перка, то нолик
        boarding_player_base_crew = mcrew;// учет всех кораблей
        //Максимальное количество человек
        Log_TestInfo("Итого: До расчета mcrew = "+mcrew+ " ecrew = "+ ecrew + " boarding_enemy_hp = "+ boarding_enemy_hp + " boarding_player_hp = "+boarding_player_hp);
    }
    // boal 21.01.2004 <--
    // fort <--
	float rel;
	float reldiv;
	int irank = sti(pchar.rank) - sti(echr.rank);
	if(mcrew > ecrew) {
        // нам бонуc boal
		boarding_player_hp = boarding_player_hp + GetBoarding_player_hp_Bonus(mcrew, ecrew);
		GetBoarding_player_rank_Bonus(mcrew, ecrew);
		Log_TestInfo("Бонус матросов игрока за перевес в численности: к ХП " + boarding_player_hp+", к уровню "+m_rank_bonus);
		if (boarding_player_hp > 1000) boarding_player_hp = 1000;
		rel = Makefloat(mcrew)/makefloat(maxcrew);
		mcrew = maxcrew;
		ecrew = MakeInt(ecrew / (rel*PLAYER_BOARDING_COEFF) + 0.5);
		reldiv = Makefloat(mcrew)/Makefloat(ecrew);//половина преимущества - в тушках
		reldiv = sqrt(reldiv);
		ecrew = MakeInt(ecrew*reldiv);
		if (ecrew > maxcrew) {ecrew = maxcrew;}
	}
	else {
		// boal 30.01.2004 -->
		boarding_enemy_hp = boarding_enemy_hp + GetBoarding_enemy_hp_Bonus(mcrew, ecrew);
		GetBoarding_enemy_rank_Bonus(mcrew, ecrew);
		Log_TestInfo("Бонус матросов врагов за перевес в численности: к ХП " + boarding_enemy_hp+", к уровню "+e_rank_bonus);
		if (boarding_enemy_hp > 1500) boarding_enemy_hp = 1500;
		// boal 30.01.2004 <--
		rel = Makefloat(ecrew)/makefloat(maxcrew);
		ecrew = maxcrew;
		mcrew = MakeInt(mcrew*PLAYER_BOARDING_COEFF / rel + 0.5);
		reldiv = Makefloat(ecrew)/Makefloat(mcrew);//половина преимущества - в тушках
		reldiv = sqrt(reldiv);
		mcrew = MakeInt(mcrew*reldiv);
	}
	if(mcrew < 1) mcrew = 1;
	if(ecrew < 1) ecrew = 1;

	//небольшой автолевел
	e_rank_bonus = e_rank_bonus + MakeInt(irank / 3);
	m_rank_bonus += MakeInt(GetCrewBonusRank(pchar));//-2...+8

	boarding_player_hp += MakeInt(GetCrewBonusMoraleHP(pchar) * LAi_GetCharacterMaxHP(pchar));//-15...+10%
	if (m_rank_bonus > 35) {m_rank_bonus = 35;}
	if (e_rank_bonus > 35) {e_rank_bonus = 35;}
	if (sti(pchar.rank) > 15) {
		e_rank_bonus = e_rank_bonus + MakeInt((sti(pchar.rank)-15) / 3);//автолевел
	}
	if (e_rank_bonus < 0) {
		m_rank_bonus -= e_rank_bonus;
		e_rank_bonus = 0;
	}
	Log_TestInfo("После приведения mcrew = "+mcrew+ " ecrew = "+ ecrew + " boarding_enemy_hp = "+ boarding_enemy_hp + " boarding_player_hp = "+boarding_player_hp+" e_rank_bonus="+e_rank_bonus+" m_rank_bonus="+m_rank_bonus);
	if (inside_ecrew_1 < 1) inside_ecrew_1 = 1;
	if (inside_ecrew_2 < 1) inside_ecrew_2 = 1;
	boarding_enemy_crew        = ecrew;
	boarding_enemy_crew_start  = ecrew;
	//Количество офицеров
	boarding_officers = 0;
	int passq;


	// START MOD Code by Stone-D : 30/07/2003
	boarding_enemy_crew_per_chr = makefloat(boarding_enemy_base_crew / makefloat(ecrew)); // Stone-D : For calculating final crew numbers
	// END MOD Code by Stone-D : 30/07/2003
	for(int i = 1; i <=MAX_NUM_FIGHTERS; i++)
	{
		passq = GetOfficersIndex(pchar, i);
		if (passq >= 0){
			// boal 05.09.03 offecer need to go to abordage -->
			// to_do if(makeint(Characters[GetOfficersIndex(GetMainCharacter(), i)].AbordageMode) == 0) continue;	// не берем
			// boal 05.09.03 offecer need to go to abordage <--
			boarding_officers = boarding_officers + 1;
			LAi_SetOfficerType(&characters[passq]);
		}
	}
    //boarding_player_crew_per_chr = (curplayercrew + boarding_officers)/(mcrew + boarding_officers);
    boarding_player_crew_per_chr = makefloat((boarding_player_base_crew)/ makefloat(mcrew - boarding_officers)); //приведение типа
	boarding_player_crew       = mcrew;
	boarding_player_crew_start = mcrew;
	//Выставим игроку и офицерам максимальную жизнь и запомним адреса
	LAi_SetCurHPMax(mchr);
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group    = mchr.location.group;
	boarding_adr[0].locator  = mchr.location.locator;
	for(i = 1; i <= MAX_NUM_FIGHTERS; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		//Boyer mod
		int k = i % 3;
		if(k==0) k = 3;
		if(idx < 0)
		{
			//Boyer mod
			boarding_adr[k].location = "";
			boarding_adr[k].group	= "";
			boarding_adr[k].locator  = "";
			continue;
		}
		LAi_SetCurHPMax(&Characters[idx]);
		boarding_adr[k].location = Characters[idx].location;
		boarding_adr[k].group	= Characters[idx].location.group;
		boarding_adr[k].locator  = Characters[idx].location.locator;
	}
	//Стартуем
	LAi_boarding_process = true;
	LAi_LoadLocation(deckID, locType);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

//Загрузить локацию абордажа
void LAi_LoadLocation(string locationID, int locType)
{
//	Log_TestInfo("LoadLocation()");
	ReloadProgressStart();
	//Ищем локацию
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
    Dead_Char_num = 0; // boal dead body
	if(locIndex >= 0)
	{
		//Устанавливаем главного персонажа
		ref mchr = GetMainCharacter();
		mchr.location = locationID;
		mchr.location.group = "rld";
		// boal random place to star battle 28/11/03 -->
		int locNum[20];
		int locI;
		int maxLocators = 2;

		if (CheckAttribute(&Locations[locIndex], "boarding.locatorNum"))
		{
			maxLocators = sti(Locations[locIndex].boarding.locatorNum);
		}
		locI = 0;
		locNum[locI] = rand(maxLocators-1);
		string sLocType = "loc";
		// определение стороны на палубе
		if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
		{
		    sLocType = ChooseShipUpDeck(mchr, boarding_enemy);
		}

		mchr.location.locator = sLocType + locNum[locI];
		// для каюты перекрыть
		if (CheckAttribute(&Locations[locIndex], "CabinType") && CheckAttribute(&Locations[locIndex], "boarding.Loc.Hero"))
		{
		    mchr.location.locator = Locations[locIndex].boarding.Loc.Hero;
		}
		bool   okLoc;
		int iLoc, j;
		// boal random place to star battle 28/11/03 <--
		if (!CheckAttribute(&Locations[locIndex], "CabinType"))
		{ // не грузим офов, если каюту
	        //Устанавливаем офицеров, если такие есть
	        int logined = 0;
			//Boyer mod
			for(int i = 1; i <= MAX_NUM_FIGHTERS ; i++)
			{
				int idx = GetOfficersIndex(mchr, i);
				if(idx < 0) continue;
				//Log_TestInfo("Load Off " + Characters[idx].id);
				if (logined > maxLocators) break;
				if (CheckAttribute(characters[idx],"AboardRestriction")) continue;

	            // boal 05.09.03 offecer need to go to abordage -->
//			    if(makeint(Characters[idx].AbordageMode) == 0) continue;	// не берем
				// boal 05.09.03 offecer need to go to abordage <--
				DeleteAttribute(&Characters[idx], "location");
				//Characters[idx].location = locationID;
				// boal чтоб грузились в фортах -->
				Characters[idx].location.loadcapture = true;
			    // boal чтоб грузились в фортах <--
				//Characters[idx].location.group = "rld";
				// boal random place to star battle 28/11/03 -->
				iLoc = rand(5);//3

				okLoc = false;
				while (!okLoc)
				{
				    for(j = 0; j <=locI; j++)
				    {
				        if (locNum[j] == iLoc)
				        {
				            iLoc = rand(5);//3
				            okLoc = false;
				            break;
				        }
				        okLoc = true;
				    }
				    //Boyer mod to fix stack error
				    okLoc = true;
				}
				locI++;
			    locNum[locI] = iLoc;
				//Characters[idx].location.locator = sLocType + locNum[locI];
				// boal random place to star battle 28/11/03 <--
				ChangeCharacterAddressGroup(&Characters[idx], locationID, "rld", sLocType + locNum[locI]);
				logined = logined + 1;

			}
			boarding_player_crew = boarding_player_crew - logined;
		}
		//Перегружаемся в локацию
		boarding_location = locIndex;
		if(LoadLocation(&Locations[boarding_location]))
		{
			//работа с сундуком в каюте boal -->
			if (CheckAttribute(&Locations[boarding_location], "CabinType"))
			{
				FillAboardCabinBox(&Locations[boarding_location], boarding_enemy);
			}
			//Расставляем персонажей
			LAi_SetBoardingActors(locationID);
			// boal <--
			//Вытащим саблю
			SendMessage(&mchr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 1);
			//Запретим диалог
			dialogDisable = true;
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	SetPerspectiveSettings();
	//#20190815-01
	SetPerspective2Settings();
	PostEvent("LoadSceneSound", 500);
	pchar.OfficerAttRange = 100.0;//автоагр абордажников на палубе
}

//Перегрузиться в следующую локации
void LAi_ReloadBoarding()
{
//	Log_TestInfo("ReloadBoarding()");
	//Разрешим диалоги
	dialogDisable = false;
	//Проверим предыдущую локацию
	if(boarding_location < 0)
	{
		Trace("Boarding: No loaded current boarding location");
		LAi_boarding_process = false;
		return;
	}

	csmHideLootCollectorBox(true);

	//Установить хендлеры для обработки
	SetEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade", 0);
	//Создаём фейдер и запускаем
	CreateEntity(&boarding_fader, "fader");

	string nextDeck = Locations[boarding_location].boarding.nextdeck;
	if (nextDeck != "")
	{
		if(CheckAttribute(&Locations[FindLocation(nextDeck)], "image"))
		{
			pchar.loadscreen = Locations[FindLocation(nextDeck)].image;
			SendMessage(&boarding_fader, "ls", FADER_PICTURE0, pchar.loadscreen);
		}
	}
	float fadeOutTime = RELOAD_TIME_FADE_OUT;
	SendMessage(&boarding_fader, "lfl", FADER_OUT, fadeOutTime, false);
	SendMessage(&boarding_fader, "l", FADER_STARTFRAME);
}

void LAi_ReloadStartFade()
{
	//Выгружаем локацию
 //ResetSoundScheme();
	ResetSound(); // new
	PauseAllSounds();
	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
	DelEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade");
	if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
}

void LAi_ReloadEndFade()
{
	/* Восстанавливаем озвучку губера */
	LAi_type_huberstay_set_Boarding(false);
	bool bCaptanSurrender = false;
	//Загружаем следующую локацию
	DelEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	if (SF_boarding_check()) return;

	//if(boarding_enemy_crew <= 0) canReload = false;
	if(CheckAttribute(&Locations[boarding_location], "boarding.nextdeck") && Locations[boarding_location].boarding.nextdeck != "" && boarding_enemy_crew >= 1) {
		Trace("Boarding: go to inside location");
		LAi_LoadLocation(Locations[boarding_location].boarding.nextdeck, -1);
		return; //Jason Продолжаем абордаж
	}

	if (CheckAttribute(boarding_enemy, "ShipCabinLocationId")) {//остался только кэп
		if (!CheckAttribute(boarding_enemy, "DontRansackCaptain")) {//квестовые не сдаются
			bCaptanSurrender = (Surrendered) || (TestRansackCaptain);
		}

		if (!bCaptanSurrender) {
			boarding_enemy_crew = 1;
			if(CheckAttribute(&Locations[FindLocation(boarding_enemy.ShipCabinLocationId)], "image")) {
				SendMessage(&boarding_fader, "ls", FADER_PICTURE0, Locations[FindLocation(boarding_enemy.ShipCabinLocationId)].image);
			}
			LAi_LoadLocation(boarding_enemy.ShipCabinLocationId, -1);
			DeleteAttribute(boarding_enemy, "ShipCabinLocationId"); // чтоб не зациклилось
			return;
		}
	}

	ref mchar       = GetMainCharacter();

	// квестовая сдача в плен кэпа
	if (CheckAttribute(mchar, "GenQuest.QuestAboardCaptanSurrender")) {
		DeleteAttribute(mchar, "GenQuest.QuestAboardCaptanSurrender"); // разово
		bCaptanSurrender = true;
	}
	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
	//Следующей локации нет
	DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
	boarding_location = -1;
	//Пересчитываем команду игрока
	for(i = 1; i <=MAX_NUM_FIGHTERS; i++) {
		if (GetOfficersIndex(mchar, i) >= 0) {boarding_player_crew--;}// ВЫЖИВШИЕ офицеры - это не мартросы не должны влиять
	}

	float crew = boarding_player_crew * boarding_player_crew_per_chr;
	// boal 22.01.2004 -->
	float fDefenceSkill = 0.7 + MakeFloat(GetSummonSkillFromName(mchar, SKILL_DEFENCE)) / SKILL_MAX;//0.77...1.7
	int deadCrew    = makeint((boarding_player_base_crew - crew) / (fDefenceSkill + (1/PLAYER_BOARDING_COEFF - 1) + AIShip_isPerksUse(CheckOfficersPerk(mchar, "EmergentSurgeon"), 0.0, 0.325))); // бонус выжившим
	//25% не участвуют в бою, Защита -12...+42%, Экстренный хирург 20%
	int deadCrewWOMedic = makeint(boarding_player_base_crew - crew); // без бонуса
	float leaderSkill = GetSummonSkillFromNameToOld(mchar, SKILL_LEADERSHIP);
	int iTemp;
	float fTemp;
	if (deadCrew < 0) {deadCrew = 0;}
	if (leaderSkill < 1) {leaderSkill = 1;} //fix
	// расчет медицины -->
	iTemp = deadCrewWOMedic - deadCrew;
	iTemp *= 3;
	if (iTemp > 0){
		if(CheckShipSituationDaily_GenQuest(pchar) > 1) {// если эпидемия - матросы не лечатся, лекарство не потребляется
			deadCrew += deadCrewWOMedic;
		}
		else if (GetCargoGoods(mchar, GOOD_MEDICAMENT) < iTemp) {// не хватает лекарств
			fTemp = makefloat(iTemp);
			iTemp = MakeInt(fTemp/3 * (1.0 - makefloat(GetCargoGoods(mchar, GOOD_MEDICAMENT)) / fTemp)); // умерли от ран
			RemoveCharacterGoodsSelf(mchar, GOOD_MEDICAMENT, GetCargoGoods(mchar, GOOD_MEDICAMENT)); // все нулим
			deadCrew += iTemp; // трупов больше
			Log_Info(GetConvertStrWithReplace("Variable_LAi_boarding_11", "Logs.txt", "#space#", " ") + deadCrewWOMedic + GetConvertStrWithReplace("Variable_LAi_boarding_12", "Logs.txt", "#space#", " "));
		}
		else {
			RemoveCharacterGoodsSelf(mchar, GOOD_MEDICAMENT, iTemp);
			if (GetCargoGoods(mchar, GOOD_MEDICAMENT) < (crew-deadCrew)*2) {
				Log_Info(GetConvertStrWithReplace("Variable_LAi_boarding_13", "Logs.txt", "#space#", " ") + mchar.Ship.Name + GetConvertStrWithReplace("Variable_LAi_boarding_14", "Logs.txt", "#space#", " "));
			}
		}
	}
	// расчет медицины <--
	// Saved value is not needed anymore... (Gray 14.02.2005)
	DeleteAttribute(mchar, "EnemyRank");
	bQuestCheckProcessFreeze = false;//fix

	RemoveCharacterGoodsSelf(mchar, GOOD_WEAPON, makeint(deadCrew + 0.5));

	crew = boarding_player_base_crew - deadCrew; // выжившие с бонусом
	Statistic_AddValue(mchar, "Sailors_dead", deadCrew);
	Statistic_AddValue(mchar, "DeadCrewBoard", deadCrew);
	AddCharacterExpToSkill(mchar, "Defence", makeint(deadCrew / 3 + 0.5)); //качаем защиту
	AddCharacterExpToSkill(mchar, "Grappling", makeint(deadCrew / 3 + 0.5));

	// после боя падает мораль
	fTemp = makefloat(deadCrewWOMedic)/makefloat(boarding_player_base_crew);
	fTemp -= 0.15;//незаметные потери + капитан выжил
	if (fTemp < 0) {fTemp = 0;}
	fTemp -= leaderSkill/50.0;//2-20%
	if (fTemp < 0) {fTemp /= 2;}//падет быстрее чем растет
	fTemp *= (0-60);//-50% при потере всей команды
	iTemp = makeint(fTemp);
	if (fTemp > 0) {Log_Info(GetConvertStrWithReplace("Variable_LAi_boarding_22", "Logs.txt", "#space#", " ")+abs(iTemp)+GetConvertStrWithReplace("Variable_LAi_boarding_24", "Logs.txt", "#space#", " "));}
	else {Log_Info(GetConvertStrWithReplace("Variable_LAi_boarding_23", "Logs.txt", "#space#", " ")+abs(iTemp)+GetConvertStrWithReplace("Variable_LAi_boarding_24", "Logs.txt", "#space#", " "));}
	AddCrewMorale(mchar, iTemp);

	Log_TestInfo(GetConvertStrWithReplace("Variable_LAi_boarding_15", "Logs.txt", "#space#", " ") + crew +GetConvertStrWithReplace("Variable_LAi_boarding_16", "Logs.txt", "#space#", " "));
	// boal 22.01.2004 <--

	if(IsFort) {
		int cn;
		ref officer;
		for (int j=1; j<COMPANION_MAX; j++) {
			cn = GetCompanionIndex(pchar, j);
			if (cn <= 0) {
				continue;
			}
			officer = GetCharacter(cn);
			if (!GetRemovable(officer)) {
				continue;
			}

			if (crew >= GetMaxCrewQuantity(officer)) {
				SetCrewQuantity(officer, GetMaxCrewQuantity(officer));
				crew -= GetMaxCrewQuantity(officer) + GetMinCrewQuantity(officer);
			}
			else {
				AddCharacterCrew(officer, crew);
				crew = 0;
			}
			if (crew == 0) break;
		}
	}
	else {
		SetCrewQuantity(GetMainCharacter(),Makeint(crew + 0.3));
	}
	//Пересчитываем команду соперника
	crew = 0;// какие ещё люди? все трупы! boarding_enemy_base_crew*(0.1 + rand(20)*0.01);
	if (boarding_echr_index >= 0) {
		SetCrewQuantity(&Characters[boarding_echr_index], MakeInt(crew + 0.3));
		boarding_echr_index = -1;
	}

	//Начислим опыт
	//AddCharacterExp(GetMainCharacter(), MakeInt(boarding_exp));

	//Настроим интерфейс
	Log_SetActiveAction("Nothing");
	EndBattleLandInterface();
	//Востановим адреса
	ref mchr = GetMainCharacter();
	mchr.location         = boarding_adr[0].location;
	mchr.location.group   = boarding_adr[0].group;
	mchr.location.locator = boarding_adr[0].locator;

	for(int i = 1; i <=MAX_NUM_FIGHTERS; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		//Boyer mod
		int k = i % 3;
		if(k==0) k = 3;
		if(idx < 0) continue;
		Characters[idx].location			= boarding_adr[k].location;
		Characters[idx].location.group	= boarding_adr[k].group;
		Characters[idx].location.locator = boarding_adr[k].locator;
	}
	//Выгружаемся в интерфейс
	LAi_boarding_process = false;
	// START MOD Code by Stone-D : 27/07/2003
	if (bCaptanSurrender)
	{
		ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"), 4.0, 8.0));
		LAi_SetCurHPMax(boarding_enemy);  // нужно, чтоб был живой!!!
		SetCrewQuantity(boarding_enemy, MakeInt(boarding_enemy_base_crew*(rand(20)*0.01))); // раз кэп живой, то можно раненых воскресить
		LaunchRansackMain(pchar, boarding_enemy, "captain"); //капитан в плен
		LAi_boarding_process = false;
		Event(SHIP_CAPTURED, "l", sti(boarding_enemy.index));
		return;
	}
	// END MOD Code by Stone-D : 27/07/2003
	if(boarding_location_type == BRDLT_SHIP)
	{
		ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),5.0, 10.0));
		// нельзя это делать до формы, критерий будет "" LAi_SetCurHP(boarding_enemy, 0.0); // умер, чтоб на форме обмена не жил
		LaunchRansackMain(pchar, boarding_enemy, ""); //не сдался
		LAi_boarding_process = false;
		Event(SHIP_CAPTURED, "l", sti(boarding_enemy.index));
		return;
	}
	if(boarding_location_type == BRDLT_FORT)
	{
		ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),7.0, 14.0));
		Event(FORT_CAPTURED, "l", sti(boarding_enemy.index));
		boarding_enemy.Ship.Crew.Quantity = 10 + rand(350); // рабы (остатки выживших)
		LaunchFortCapture(boarding_enemy);
		LAi_boarding_process = false;
		return;
	}
	Trace("Boarding: unknow boarding location type");
	Log_TestInfo("Boarding - unknown boarding location type : " + boarding_location_type);
}

//Разрешить перегрузку на следующую палубу
#event_handler("LAi_event_boarding_EnableReload", "LAi_EnableReload");
void LAi_EnableReload()
{
    //Log_Testinfo("LAi_BoardingGroupKill boardM = " + boardM);
	if (boardM == 1)
	{
	//	Trace("Выключить шума абордажа");
		//ResetSound();
		ResetSoundScheme(); //надо гасить только Scheme, иначе партиклы звука на кострах, факелах, и прочем - не пашут
		//StopSound(abordageSoundID, 0);
		SetSoundScheme("deck"); // обычная схема
		SetMusic("music_bitva");
		boardM = -1;
		//Log_Testinfo(GetConvertStrWithReplace("Variable_LAi_boarding_17", "Logs.txt", "#space#", " ") + abordageSoundID);
	}
	Surrendered = CheckForSurrender(GetMainCharacter(), boarding_enemy, 2); // проверка сдачи в плен, перед каютой 2 - второй учет метода

	if (csmCA(pchar, "CSM.LootCollector.Enable") && loadedLocation.type != "boarding_cabine")
	{
		pchar.CSM.LootCollector.CanBeRun = true;
		csmLootCollector();
	}
	PostEvent("csmEvent_RefreshReload", 100);
    //#20171218-01 Re-enable fast action for cabin enter during boarding
    BattleInterface.LAi_ActivateReload = true;
	SetEventHandler("Control Activation","LAi_ActivateReload",1);
	Log_SetActiveAction("Reload");
	//Уберём саблю
	ref mchr = GetMainCharacter();
	SendMessage(&mchr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", 0);

	// sd -->
	Log_TestInfo("Start boarding_enemy_crew_start: " + boarding_enemy_crew_start + " boarding_enemy_crew: " + boarding_enemy_crew);
	Log_TestInfo("Start boarding_player_crew_start: " + boarding_player_crew_start + " boarding_player_crew: " + boarding_player_crew);
	// sd <--

	//Вернём выживших обратно в кучу
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int index = LAi_loginedcharacters[i];
		if(index >= 0)
		{
			if(index != GetMainCharacterIndex())
			{
				ref chr = &Characters[index];
				if(!LAi_IsDead(chr) && !CheckAttribute(chr,"AboardFantomMush")) // boal && sd не нужны офицеры для матросов
				{
					if(chr.chr_ai.group == LAI_GROUP_PLAYER)
					{
						boarding_player_crew = boarding_player_crew + 1;
						//LAi_tmpl_stay_InitTemplate(chr);  // 05.02.08 требует локаторов ГОТО, что б не ходили за ГГ матросы толпой - нихрена это не работает, всё равно ходят !
						//LAi_SetStayType(chr); // а вот так не ходят !!  <-- ugeen
						if (!IsOfficer(chr))
						{
							/* Отключаем озвучку губера для абордажников */
							LAi_type_huberstay_set_Boarding(true);
							LAi_SetHuberStayTypeNoGroup(chr); //нефиг им стоять, все-равно мешаются ! пущай расходятся по палубе

						}
					}
				}
				/*
				// Fix избытка команды ! - убираем, глючный
				if(chr.model.animation == "mushketer" && !IsOfficer(chr)) //мушкетеров убираем с палубы
				{
                    ChangeCharacterAddress(chr, "none", "");
				}
				*/
			}
		}
	}
	//костыль для расхода мушкетеров, по факту нужно эту херню всю переписывать
	for(i = 0; i < LAi_numloginedcharacters; i++)
	{
		index = LAi_loginedcharacters[i];
		if(index >= 0)
		{
			if(index != GetMainCharacterIndex())
			{
				chr = &Characters[index];
				if(!LAi_IsDead(chr) && CheckAttribute(chr,"AboardFantomMush"))
				{
					/* Отключаем озвучку губера для абордажников */
					LAi_type_huberstay_set_Boarding(true);
					LAi_SetHuberStayTypeNoGroup(chr);
				}
			}
		}
	}
	// Jason: перебираем классы кораблей и определяем следующую палубу
	int eclass = sti(GetCharacterShipClass(boarding_enemy)); // класс корабля противника
	if (CheckAttribute(&Locations[boarding_location], "UpDeckType"))
	{
		switch (eclass)
		{
			case 1: Locations[boarding_location].boarding.nextdeck = "Boarding_GunDeck"; break;
			case 2: Locations[boarding_location].boarding.nextdeck = "Boarding_GunDeck"; break;
			case 3: Locations[boarding_location].boarding.nextdeck = "Boarding_Campus"; break;
			case 4: Locations[boarding_location].boarding.nextdeck = "Boarding_Campus"; break;
			case 5: Locations[boarding_location].boarding.nextdeck = "Boarding_Cargohold"; break;
			case 6: Locations[boarding_location].boarding.nextdeck = ""; break;
			case 7: Locations[boarding_location].boarding.nextdeck = ""; break;
		}
	}
	if (boarding_enemy_crew == 0) Locations[boarding_location].boarding.nextdeck = "";
	if (IsFort && Locations[boarding_location].boarding.nextdeck == "Boarding_bastion")
	{
		Locations[boarding_location].boarding.nextdeck = "Boarding_bastion2"/* +(drand(1)+1 */);
	}
	// END MOD Code by Stone-D : 01/08/2003 -->
	Log_TestInfo("New boarding_player_crew: " + boarding_player_crew);
	Log_TestInfo("Next Location: " + Locations[boarding_location].boarding.nextdeck);
    Log_TestInfo("Enemy ship class: " + eclass);
	// END MOD Code by Stone-D : 01/08/2003 <--
}

//Активация перегрузки на следующую палубу
void LAi_ActivateReload()
{
	string controlName = GetEventData();
	if(controlName != "ChrAction") return;
	if (CheckAttribute(pchar, "GenQuest.CannotReloadBoarding")) return; // Jason
	DelEventHandler("Control Activation", "LAi_ActivateReload");
	//#20171218-01 Re-enable fast action for cabin enter during boarding
    DeleteAttribute(&BattleInterface, "LAi_ActivateReload");
	Log_SetActiveAction("Nothing");
	LAi_ReloadBoarding();
}

//Расставить персонажей для боя
void LAi_SetBoardingActors(string locID)
{
    int    limit, i, iQty;
	ref    chr;
	string model, ani, sTemp;
	int    xhp;
	int    locIndex = FindLocation(locID);
	int    mclass = GetCharacterShipClass(GetMainCharacter());
	int    eclass = GetCharacterShipClass(boarding_enemy);
	ref    mchr = GetMainCharacter(); // boal star with new loc always
    int    locMChar;

	limit = MAX_GROUP_SIZE;
	// локаторов разное число на моделях :( Переделал все на инфу из кода boal 01.01.05  +1 всегда для ГГ
	chr = &Locations[locIndex];

	if(CheckAttribute(chr, "boarding.locatorNum")) limit = sti(chr.boarding.locatorNum);

	Log_TestInfo("Location: " + locID + " Limit: " + limit);
	Log_TestInfo("Player: " + boarding_player_crew + GetConvertStrWithReplace("Variable_LAi_boarding_18", "Logs.txt", "#space#", " ") + boarding_player_crew_per_chr + " Enemy: " + boarding_enemy_crew + GetConvertStrWithReplace("Variable_LAi_boarding_19", "Logs.txt", "#space#", " ") + boarding_enemy_crew_per_chr);

	//Установим союзников из команды
	// boal прежде всего ставим офицеров, коротых в фотре почему-то нет -->
	/*if (IsFort) // boal 21.01.05 не прошло и года... починил в другом месте - правильно
	{
        for(i = 1; i < 4; i++)
		{
			int idx = GetOfficersIndex(mchr, i);
			if(idx < 0) continue;
            // boal 05.09.03 offecer need to go to abordage -->
		    if(makeint(Characters[idx].AbordageMode) == 0) continue;	// не берем
		    // грузим сами насильно уже в сущ локацию
		    chr = &Characters[idx];
		    PlaceCharacter(chr, mchr.location.group, mchr.location);
		}
	} */
	// boal прежде всего ставим офицеров, коротых в форте почему-то нет <--
    string sLocType = "loc";
	// определение стороны на палубе
	if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
	{
	    sLocType = ChooseShipUpDeck(mchr, boarding_enemy);
	}
	int ireserve = 0;
	for(i = 1; i <=MAX_NUM_FIGHTERS; i++) {
		if (GetOfficersIndex(mchr, i) >= 0){ireserve++;}
	}
	ireserve = boarding_player_crew + ireserve - limit;
	if(ireserve > 0){
		Log_Info("Мы имеем "+ireserve+" бойцов в запасе");//fixme: два офицера спавнятся поверх предела... почемуто
	}
	if (!CheckAttribute(&Locations[locIndex], "CabinType"))
	{ // не грузим матросов в каюту
		for(i = LAi_numloginedcharacters; i < limit; i++)
		{
			if(boarding_player_crew <= 0) break;
			model = LAi_GetBoardingModel(mchr, &ani);
			// boal star with new loc always  -->
			if (mchr.location.locator == (sLocType + i))
			{ // искодим из того, что наша локация всегда < 4 офицеры пусть накладываются а матросик идёт к противнику.
	           locMChar = rand(3);
	           while (mchr.location.locator == (sLocType + locMChar))
	           {
	               locMChar = rand(3);
	           }
		       chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType+locMChar);// 0-всегда свободен, если офицеров нет, а i != 0, тк мы точно есть
			}
			else
			{
			   chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
			}
			// boal star with new loc always  <--
			chr.sex = SetGenderFromCap(mchr);

			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);

			boarding_player_crew = boarding_player_crew - 1;
			// boal расчет как у нормальных фантомов -->
			//LAi_SetAdjustFencingSkill(chr, 3.0, 6.0);
			//LAi_AdjustFencingSkill(chr);

			// boal <--
			if (!IsFort)
			{
	            SetFantomParamAbordOur(chr);
			}
			else
			{
			    SetFantomParamFortOur(chr);
			}
			SetNewModelToChar(chr); //иначе сабли не те, что реально
			chr.AboardFantom = true;
			AddCharHP(chr, boarding_player_hp); // влияение опыта и морали в НР
			/*if (!bNewFantomGenerator)
	        {
				xhp = GetBoarding_player_hp(boarding_player_hp);
				LAi_SetHP(chr, xhp, xhp);
			}*/
		}
		//ставим своих мушкетеров -->
		if (CheckOfficersPerk(mchr, "MusketsShoot"))
		{
			iQty = MAX_MUSKETEER_SIZE;
			for(i=1; i<=iQty; i++)
			{
				if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
				{
					model = LAi_GetBoardingMushketerModel(mchr);
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, SetGenderFromCap(mchr), "mushketer", 5, sti(mchr.nation), 0, false));
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE*3, true);
					chr.id = "GenChar_" + chr.index;
					chr.AboardFantom = true;
					chr.AboardFantomMush = true;
					chr.norun = true;
					//if (!IsFort) chr.MusketerDistance = 0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
				}
				if (!IsFort)
				{
					SetMushketerParamAbordOur(chr);
				}
				else
				{
					SetMushketerParamFortOur(chr);
				}
				AddCharHP(chr, boarding_player_hp); // влияение опыта и морали в НР
			}
		}
		//<-- ставим своих мушкетеров
	}
	//Установим врагов
	if (sLocType == "loc")
	{
	    sLocType = "aloc";
	}
	else
	{
	    sLocType = "loc";
	}
	trace("sLocType = " + sLocType);
	if (HasSubStr(boarding_enemy.model,"trader_")) boarding_enemy.Ship.Mode = "Trade";
	for(i = 0; i < limit; i++) // <= тк loc0 .. loc4 = 5
	{
		if(boarding_enemy_crew <= 0) break;
		model = LAi_GetBoardingModel(boarding_enemy, &ani);
		if (i == 0 && CheckAttribute(&Locations[locIndex], "boarding.Loc.Capt")) //локатор каюты
		{
		    chr = LAi_CreateFantomCharacterEx(model, ani, "rld", Locations[locIndex].boarding.Loc.Capt);
			switch (MOD_SKILL_ENEMY_RATE)
			{
				case 1: TakeNItems(chr, "potion1", 1 + rand(1)); break;
				case 2: TakeNItems(chr, "potion1", 2 + rand(3)); break;
				case 3: TakeNItems(chr, "potion2", 2 + rand(3)); break;
			}
		}
		else
		{
			chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
		}
		chr.sex = SetGenderFromCap(boarding_enemy);

		LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);

		boarding_enemy_crew = boarding_enemy_crew - 1;
		// boal расчет как у нормальных фантомов -->
		//LAi_SetAdjustFencingSkill(chr, 2.0, 6.0);
		//LAi_AdjustFencingSkill(chr);

		if (!IsFort)
		{
            SetFantomParamAbordEnemy(chr);
		}
		else
		{
            SetFantomParamFortEnemy(chr);
			//xhp = GetBoarding_enemy_hp(LAi_GetCharacterMaxHP(chr));
		}
		// капитана в рубку!!! boal
		if (i == 0 && CheckAttribute(&Locations[locIndex], "CabinType"))
		{
			ChangeAttributesFromCharacter(chr, boarding_enemy, true);
			chr.CaptanId = boarding_enemy.id; // иначе у фантома свой ИД   // to_do поправить опечатку
			boarding_enemy.CaptanId = boarding_enemy.id;
			chr.SuperShooter = true; // супер стрелок (вероятность пальбы выше, от сложности, если ещё и пистоль есть)
			if (boarding_enemy.sex == "man") chr.greeting = "CapSinkShip";
			SetCharacterPerk(chr, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, дается ГГ и боссам уровней
			if (CheckAttribute(chr,"Situation"))
			{
				if(bSeaCanGenerateShipSituation) SetQuestAboardCabinDialogSituation(chr);
				else DeleteAttribute(chr,"Situation");
			}
			else
			{
				CaptainComission_GenerateSituation(chr);
				SetQuestAboardCabinDialog(chr); /// проверка на минНр
			}
			// если это место отработало, то кэп либо убит, либо по квестам сдается в плен
			// 1.2.3 эффект кирасы
			//if (CheckCharacterPerk(chr, "Ciras"))
			//{
		    xhp = makeint((MOD_SKILL_ENEMY_RATE*3*2+sti(chr.rank))/10.0);

		    if (xhp > 0)
		    {
		        if (xhp >= 5) xhp = 5;
		        // путаница с 3  и 4 кирасами (меняем)
		        if (xhp == 3)
				{
					xhp = 4;
				}
				else
				{
				    if (xhp == 4) xhp = 3;
				}
				model = "cirass" + xhp;
				chr.cirassId  = Items_FindItemIdx(model);
				if (!checkattribute(chr,"heromodel")) 
				{
					DeleteAttribute(chr,"VISUAL_CIRASS");
					FaceMaker(chr);
				}
				CheckForCirass(chr);
				Log_TestInfo(GetConvertStrWithReplace("Variable_LAi_boarding_20", "Logs.txt", "#space#", " ") + model);
		    }
			//}
			if(CheckAttribute(pchar, "CabinHelp") && pchar.CabinHelp == true)	BSHangover_FlintFight_3("");
			if(CheckAttribute(pchar, "MaryCabinHelp") && pchar.MaryCabinHelp == true)	Mary_Pomogaet_v_Kautah("");
		}
		SetNewModelToChar(chr); //иначе сабли не те, что реально
		string weaponID = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
		aref weapon;
		Items_FindItem(weaponID, &weapon);
		chr.chr_ai.fencingtype = weapon.FencingType;
		weaponID = GetCharacterEquipByGroup(chr, GUN_ITEM_TYPE);
		if (weaponID != "")
		{
			EquipCharacterByItem(chr,weaponID);
			Items_FindItem(weaponID, &weapon);
			chr.chr_ai.charge = makefloat(weapon.chargeQ);
		}
		chr.AboardFantom = true;
		AddCharHP(chr, boarding_enemy_hp); // влияение опыта и морали в НР
	}
	//ставим вражеских мушкетеров -->
	if (CheckCharacterPerk(boarding_enemy, "MusketsShoot") || IsFort)
	{
		if (!CheckAttribute(&Locations[locIndex], "CabinType"))
		{
			iQty = MAX_MUSKETEER_SIZE;
			for(i=1; i<=iQty; i++)
			{
				if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
				{
					model = LAi_GetBoardingMushketerModel(boarding_enemy);
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, SetGenderFromCap(boarding_enemy), "mushketer", 5, sti(boarding_enemy.nation), 0, false));
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE*3, true);
					chr.id = "GenChar_" + chr.index;
					chr.AboardFantom = true;
					chr.norun = true;
					//chr.MusketerDistance = 0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
				}
				if (!IsFort)
				{
					SetMushketerParamAbordEnemy(chr);
				}
				else
				{
					SetMushketerParamFortEnemy(chr);
				}
				AddCharHP(chr, boarding_enemy_hp); // влияение опыта и морали в НР
			}
		}
	}
	//<-- ставим вражеских мушкетеров
	//Заставим драться эти 2 группы
	LAi_group_FightGroupsEx(LAI_GROUP_PLAYER, LAI_GROUP_BRDENEMY, true, GetMainCharacterIndex(), -1, false, false);
	LAi_group_SetCheckEvent(LAI_GROUP_BRDENEMY);
}

//Убийство группы
void LAi_BoardingGroupKill()
{
	string group = GetEventData();
	if(IsFort && Locations[boarding_location].id == "BOARDING_FORT")
		StopFakeFire();
	if(group != LAI_GROUP_BRDENEMY) return;
	// отключим шум абордажа (который включается при аларме в sound.c)

	if (CheckAttribute(pchar, "questTemp.Whisper.KilledPortman"))
	{
		Log_Info(GetConvertStrWithReplace("Variable_LAi_boarding_21", "Logs.txt", "#space#", " "));
		LAi_SetFightMode(PChar, false);
		PlaySound("interface\important_item.wav");
		DoQuestCheckDelay("TalkSelf_Quest", 0.8);
	}

	PostEvent("LAi_event_boarding_EnableReload", 1000);
}

//Моделька для абордажного персонажа
string LAi_GetBoardingModel(ref rCharacter, ref ani)
{
	ani = "man";
	int iNation = sti(rCharacter.nation);
	string atr;
	string model;


	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
    {
        model = GetRandSkelModel();
		ani = "man";
		return model;
    }
	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelModeClassic"))
    {
        model = GetRandSkelModelClassic();
		ani = "man";
		return model;
    }
	if (CheckAttribute(rCharacter, "GenQuest.CrewSatanistMode"))
    {
        model = GetRandSatanistMode();
		ani = "man";
		return model;
    }
    if (CheckAttribute(rCharacter, "OZG") == true)
    {
        model = "OZG_" + (rand(8) + 1);
	    ani = "man";
		return model;
    }

	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
        // boal 290904 форма солдат -->
        if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
        {
            model = GetRandSkelModel();
			ani = "man";
			return model;
        }
		if (rCharacter.sex == "skeleton")
		{
			model = GetRandSkelModelClassic();
			ani = "man";
			return model;
		}
		if (CheckAttribute(rCharacter, "OZG") == true)
        {
            model = "OZG_" + (rand(9) + 1);
			ani = "man";
			return model;
        }
        if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1) //форма только со звания капитан
        {
            atr = "boardingModel.enemy";
            iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
        }
        else
        {
            atr = "boardingModel.player";
        }
        // boal 290904 форма солдат <--
	}
	else
    {   //boal -->
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
            atr = "boardingModel.merchant";
        }
		else
        {//boal <--
            atr = "boardingModel.enemy";
        }
	}

	if (iNation < 0) iNation = PIRATE;
	//eddy. замаскировавшися пиратов тоже надо учитывать
	if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate" && !IsMainCharacter(rCharacter)) iNation = PIRATE;
	Nations[iNation].boardingModel.player = "";
	Nations[iNation].boardingModel.enemy = "";
	Nations[iNation].boardingModel.merchant = "";

	aref models;
	makearef(models, Nations[iNation].(atr));
	int num = GetAttributesNum(models);
	if(num <= 0) return "pirate_1";
	int i = rand(num - 1);
	atr = GetAttributeName(GetAttributeN(models, i));
	model = models.(atr);
	atr = atr + ".ani";
	if(CheckAttribute(models, atr))
	{
		if(models.(atr) != "")
		{
			ani = models.(atr);
		}
	}
	if (GetCharacterItem(rCharacter, "SkullAztec") && rand(1)==0)
	{
		if(rand(1)==0)	model = GetRandSkelModel();
		else			model = GetRandSkelModelClassic();

		ani = "man";
		return model;
	}

	return model;
}

string LAi_GetBoardingMushketerModel(ref rCharacter)
{
	string model;
	int iNation = sti(rCharacter.nation);

	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
        if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1) //форма только со звания капитан
        {
            iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
        }
        else
        {
            iNation = PIRATE;
        }
		if (rCharacter.sex == "skeleton")
		{
			return GetRandMushketerSkeleton();
		}
	}
	else
    {   //boal -->
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
            iNation = PIRATE;
        }
		else
        {//boal <--
            iNation = sti(rCharacter.nation);
        }
	}

	if (iNation < 0) iNation = PIRATE;
	//eddy. замаскировавшися пиратов тоже надо учитывать
	if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate") iNation = PIRATE;
	if(iNation == PIRATE)
	{
		model = GetPirateMushketerModel();
	}
	else
	{
		model = NationShortName(iNation) + "_mush_" + (rand(2)+1);
	}
	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode")) return GetRandMushketerFishman();
	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelModeClassic"))	return GetRandMushketerSkeleton();
	if (CheckAttribute(rCharacter, "GenQuest.CrewSatanistMode")) return "animists"+(1+rand(1))+"_mush";
	return model;
}

string SetGenderFromCap(ref character)
{
	if (character.sex == "skeleton") return "skeleton";
	if (CheckAttribute(character, "GenQuest.CrewSkelMode") || CheckAttribute(character, "GenQuest.CrewSkelModeClassic")) return "skeleton";
	return "man";
}

// boal 03/08/06 полностью переписал метод Stone-D от 27/07/2003
bool CheckForSurrender(ref mchr, ref echr, int _deck)
{
    if(boarding_location_type == BRDLT_FORT) return false; // Forts don't surrender.

    if (GetPrisonerQty() > PRISONER_MAX) return false; // очень много пленых

	float fEnemyRate = 0.5 - 0.02 * MOD_SKILL_ENEMY_RATE*3;
	if (sti(echr.Nation) == PIRATE)
	{
		fEnemyRate = 0.2 - 0.01 * MOD_SKILL_ENEMY_RATE*3;
	}
	else
	{
		if (CheckAttribute(echr, "Ship.Mode") && echr.Ship.Mode == "Trade") // торговцы склонны сдаться
		{
			fEnemyRate = 0.9 - 0.03 * MOD_SKILL_ENEMY_RATE*3;
		}
	}

	int eclass = GetCharacterShipClass(echr);
	int mclass = GetCharacterShipClass(mchr);

	float mcrew = stf(GetWeaponCrew(mchr, GetCrewQuantity(mchr))); // честный учет с оружием
	float ecrew = stf(GetCrewQuantity(echr));

	float fRep    = Bring2Range(0.0, 1.0, stf(REPUTATION_MIN), stf(REPUTATION_MAX), stf(mchr.reputation)); // приведение к 0..1
	float mmorale = stf(mchr.ship.crew.morale) / MORALE_MAX; // 0..1
	float emorale = stf(echr.ship.crew.morale) / MORALE_MAX; // 0..1
	float mskill  = (GetSummonSkillFromName(mchr, "Leadership") + GetSummonSkillFromName(mchr, "Grappling")) / (2.0 * SKILL_MAX_TOTAL);  // 0..1
	float eskill  = (GetCharacterSkill(echr, "Leadership") + GetCharacterSkill(echr, "Defence")) / (2.0 * SKILL_MAX_TOTAL);              // 0..1
	float mcskill = GetCrewExp(mchr, "Soldiers") / GetCrewExpRate();
	float ecskill = GetCrewExp(echr, "Soldiers") / GetCrewExpRate();

	mcrew = mcrew * (1.0 + 5.0 * mskill) * (1.0 + 5.0 * mcskill) * (1.0 + 5.0 * mmorale) * (1.0 + 0.5 * _deck) * fEnemyRate * (fRep * fRep * fRep); // Если у ГГ низкая репутация - очень не хотят сдаваться
	ecrew = ecrew * (1.0 + 5.0 * eskill) * (1.0 + 5.0 * ecskill) * (1.0 + 5.0 * emorale);

	float seaDogCoeff = 1.0;
	if (CheckOfficersPerk(mchr, "SeaDogProfessional") && CheckAttribute(pchar, "SeaDogProfessionalSwitch"))
	{
		if (pchar.SeaDogProfessionalSwitch == 1)
			seaDogCoeff = 2.0;
	}
	mcrew = mcrew * seaDogCoeff;

	// подсчет компаньенов у сторон  -->
    int mShip = GetCompanionQuantity(mchr);
    int eShip;
    string sGroupID = Ship_GetGroupID(echr);
    if (sGroupID != "")
    {
    	eShip = Group_GetLiveCharactersNum(sGroupID);
    }
    else
    {
    	eShip = 1;
    }
    mcrew = mcrew * (1.0 + (mShip - 1) / 10.0);
    ecrew = ecrew * (1.0 + (eShip - 1) / 10.0);
	// <--

    Log_TestInfo("Surrender Hero = " + mcrew + "    Enemy = " + ecrew + " eShipQty = " + eShip);

    if (mcrew > ecrew)
	{
		int randval = rand(1000);
		Log_TestInfo("rand: " + randval);
		if (randval < 1000.0 * (mcrew - ecrew) / ecrew)
		{
			Log_TestInfo("Surrender!");
			return true;
		}
	}
	Log_TestInfo("Fight!");
	return false;
}

// boal 03/12/05 выбор локатора от корабля лок - маленькие, алок - большие-->
string ChooseShipUpDeck(ref _mchar, ref _enemy)
{
    string sLoc = "loc";

	if (GetCargoMaxSpace(_mchar) > GetCargoMaxSpace(_enemy))
	{
	    sLoc = "aloc";
	}

    return sLoc;
}
// boal 03/12/05 <--
// CSM -->
#event_handler("csmEvent_RefreshReload", "csmRefreshReload");
void csmRefreshReload()
{
	if (!LAi_IsBoardingProcess() || !IsEntity(&loadedLocation))
	{
		csmDA(pchar, "CSM.LootCollector.CanBeRun");
		return;
	}

	if (loadedLocation.type == "boarding_cabine" && csmCA(pchar, "CSM.LootCollector.Enable"))
		csmDA(pchar, "CSM.LootCollector.CanBeRun");

	if (g_ActiveActionName == "" || g_ActiveActionName == "Nothing")
		Log_SetActiveAction("Reload");

	PostEvent("csmEvent_RefreshReload", 250);
}
// CSM <--
