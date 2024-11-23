void SetRandSelfSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Leadership = _min + rand(iDelta);
	_ch.skill.FencingLight = _min + rand(iDelta);
	_ch.skill.Fencing = _min + rand(iDelta);
	_ch.skill.FencingHeavy = _min + rand(iDelta);
	_ch.skill.Pistol = _min + rand(iDelta);
	_ch.skill.Fortune = _min + rand(iDelta);
	_ch.skill.Sneak = _min + rand(iDelta);
}

void SetRandShipSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Sailing = _min + rand(iDelta);
	_ch.skill.Commerce = _min + rand(iDelta);
	_ch.skill.Accuracy = _min + rand(iDelta);
	_ch.skill.Cannons = _min + rand(iDelta);
	_ch.skill.Repair = _min + rand(iDelta);
	_ch.skill.Grappling = _min + rand(iDelta);
	_ch.skill.Defence = _min + rand(iDelta);
}

void DeleteAllPerksExceptChar(ref _ch)
{
	string character = "";
	if (CheckAttribute(_ch,"perks.list.Buccaneer")) character = "Buccaneer";
	if (CheckAttribute(_ch,"perks.list.Fencer")) character = "Fencer";
	if (CheckAttribute(_ch,"perks.list.Grunt")) character = "Grunt";
	if (CheckAttribute(_ch,"perks.list.Trader")) character = "Trader";
	if (CheckAttribute(_ch,"perks.list.Adventurer")) character = "Adventurer";
	if (CheckAttribute(_ch,"perks.list.Agent")) character = "Agent";
	if (CheckAttribute(_ch,"perks.list.SeaWolf")) character = "SeaWolf";
	DeleteAttribute(_ch,"perks.list");
	_ch.perks.list.(character) = 1;
}

void SelAllPerksToNotPChar(ref _ch)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.Ciras = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	//_ch.perks.list.Grus = "1";
	_ch.perks.list.Rush = "1";
	_ch.perks.list.Tireless = "1";
	_ch.perks.list.HardHitter = "1";
	_ch.perks.list.BladeDancer = "1";
	_ch.perks.list.Sliding = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.GunProfessional = "1";
	_ch.perks.list.IronWill = "1";
	//_ch.perks.list.Medic = "1";
	_ch.perks.list.HPPlus = "1";
	_ch.perks.list.EnergyPlus = "1";
	_ch.perks.list.Trustworthy = "1";
	_ch.perks.list.ShipEscape = "1";

	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.FastReload = "1";
	_ch.perks.list.ImmediateReload = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.CannonProfessional = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.MusketsShoot = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipDefenseProfessional = "1";
	_ch.perks.list.LightRepair = "1";
	_ch.perks.list.InstantRepair = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.Brander = "1";
	_ch.perks.list.Troopers = "1";
	_ch.perks.list.BasicCommerce = "1";
	_ch.perks.list.AdvancedCommerce = "1";
	_ch.perks.list.Carpenter = "1";
	_ch.perks.list.Builder = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	_ch.perks.list.Doctor1 = "1";
	_ch.perks.list.Doctor2 = "1";
	_ch.perks.list.EmergentSurgeon = "1";
	_ch.perks.list.ByWorker = "1";
	_ch.perks.list.ByWorker2 = "1";
}

// Установить персу все перки
void SelAllPerksToChar(ref _ch, bool _isOfficer)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.Ciras = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	_ch.perks.list.AgileMan = "1";
	//_ch.perks.list.Grus = "1";
	_ch.perks.list.Rush = "1";
	_ch.perks.list.Tireless = "1";
	_ch.perks.list.HardHitter = "1";
	_ch.perks.list.BladeDancer = "1";
	_ch.perks.list.Sliding = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.GunProfessional = "1";
	_ch.perks.list.IronWill = "1";
	_ch.perks.list.SharedExperience = "1";
	//_ch.perks.list.Medic = "1";
	_ch.perks.list.Craft = "1";
	_ch.perks.list.HPPlusFixed = "1";
	_ch.perks.list.EnergyPlusFixed = "1";
	_ch.perks.list.Trustworthy = "1";
	_ch.perks.list.UnlimitedContra = "1";
	_ch.perks.list.ShipEscape = "1";
	_ch.perks.list.Buldozer = "1";
	_ch.perks.list.AboardCollector = "1";

	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.FastReload = "1";
	_ch.perks.list.ImmediateReload = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.CannonProfessional = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.MusketsShoot = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipDefenseProfessional = "1";
	_ch.perks.list.LightRepair = "1";
	_ch.perks.list.InstantRepair = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SeaDogProfessional = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.Brander = "1";
	_ch.perks.list.Troopers = "1";
	_ch.perks.list.BasicCommerce = "1";
	_ch.perks.list.AdvancedCommerce = "1";
	_ch.perks.list.Carpenter = "1";
	_ch.perks.list.Builder = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	_ch.perks.list.Doctor1 = "1";
	_ch.perks.list.Doctor2 = "1";
	_ch.perks.list.EmergentSurgeon = "1";

	if(_isOfficer) // У офов есть доп. перки
	{
		_ch.perks.list.ByWorker = "1";
		_ch.perks.list.ByWorker2 = "1";
	}
}

// Установить персу половину перков
void SetHalfPerksToChar(ref _ch, bool _isOfficer)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.Ciras = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.SharedExperience = "1";

	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";

	if(_isOfficer) // У офов есть доп. перки
	{
		_ch.perks.list.ByWorker = "1";
		_ch.perks.list.ByWorker2 = "1";
	}
}

// Отобрать все предметы (кроме квестовых) у выбранного персонажа
void RemoveAllCharacterItems(ref _ch, bool _removemoney)
{
	// сносим нафик всю экипировку
	if(IsMainCharacter(_ch))
	{
		StoreEquippedMaps(_ch);
		_ch.MapsAtlasCount = 0;
	}
	RemoveCharacterEquip(_ch, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(_ch, GUN_ITEM_TYPE);
	RemoveCharacterEquip(_ch, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(_ch, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, MAPS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, BACKPACK_ITEM_TYPE);
	RemoveCharacterEquip(_ch, TALISMAN_ITEM_TYPE);
	RemoveCharacterEquip(_ch, BOOK_ITEM_TYPE);

	//сносим все предметы, кроме квестовых -->
	aref arItems;
	string sName;
	ref rLoc;
	makearef(arItems, _ch.items);
	int	Qty = GetAttributesNum(arItems);
	for (int a=0; a<Qty; a++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if (rLoc.ItemType == "QUESTITEMS")
		{
			_ch.questTemp.items.(sName) = _ch.items.(sName);
		}
	}
	DeleteAttribute(_ch, "items");
	_ch.items = "";
	makearef(arItems, _ch.questTemp.items);
	Qty = GetAttributesNum(arItems);
	for (a=0; a<Qty; a++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(_ch, sName, sti(arItems.(sName)));
	}
	DeleteAttribute(_ch, "questTemp.items");

	if(_removemoney)
	{
		_ch.money = 0;
	}
}

// снести всех пассажиров и компаньонов ГГ
void RemoveAllPassengersAndCompanions()
{
    int iDay = GetPassengersQuantity(pchar);
    int i = 0;
    int n = 0;
	int idx;
	ref ch;

 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n); // всегда первый в массиве со смещением, если не трем
		if (idx == -1) break;
		ch = GetCharacter(idx);
		if (GetRemovable(ch)) // квестовых не трогаем
		{
		    ch.LifeDay = 1; // чтоб не сразу потерся
		    RemovePassenger(pchar, ch);
			ChangeCharacterAddress(ch,"none","");
		}
		else
		{
		    n++;
		}
	}
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
			if (GetShipRemovable(ch) && GetRemovable(ch))  // не трогаем квестовых и ПГГ
			{
			    ch.LifeDay = 1; // чтоб не сразу потерся
			    RemoveCharacterCompanion(pchar, ch);
			}
		}
	}
}

void CleanAllCabinBoxes()
{
	ref loc;
	int n;
	string sTemp;

    if (Pchar.SystemInfo.CabinType != "")
    {
	    loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; //"My_Cabin"

	    for (n = 1; n <= 4; n++)
	    {
	        sTemp = "box" + n;
			DeleteAttribute(loc, sTemp + ".items");
		    loc.(sTemp).items = "";
		    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
		    loc.(sTemp).money = 0;
	    }
    }
    loc = &locations[FindLocation("My_Deck")];
    for (n = 1; n <= 4; n++)
    {
        sTemp = "box" + n;
		DeleteAttribute(loc, sTemp + ".items");
	    loc.(sTemp).items = "";
	    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
	    loc.(sTemp).money = 0;
    }
}

/*	//устарел и нигде не используется. ссылается на старые номера кораблей
// Метод вернёт случайный тип корабля, который зависит от класса шипа персонажа
int RandShipFromShipClass(ref _ch)
{
	int iShipClass = sti(RealShips[sti(_ch.Ship.Type)].Class);
	int iShipType;
	switch(iShipClass)
	{
		case 1:
			iShipType = SHIP_INGERMANLAND + rand(2);
			break;

		case 2:
			iShipType = SHIP_FRIGATE + rand(1);
			break;

		case 3:
			iShipType = SHIP_CORVETTE + rand(2);
			break;

		case 4:
			iShipType = SHIP_FLEUT + rand(2);
			break;

		case 5:
			iShipType = SHIP_BARQUE + rand(1);
			break;

		case 6:
			iShipType = SHIP_SLOOP + rand(1);
			break;

		case 7:
			iShipType = SHIP_FELUCA + rand(1);
			break;
	}
	return iShipType;
}
*/
// Проверка, есть ли у ГГ казначей
bool IsPCharHaveTreasurer()
{
	ref rOfficer;

	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		rOfficer = &characters[i];
		if(CheckAttribute(rOfficer, "treasurer") && sti(rOfficer.Treasurer) == 1)
		{
			return true; // Казначей есть
		}

	}

	return false;
}

// Метод вернёт ссылку на казначея
ref GetPCharTreasurerRef()
{
	if(!IsPCharHaveTreasurer()) return &NullCharacter;
	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		if(CheckAttribute(&characters[i], "treasurer") && sti(characters[i].Treasurer) == 1)
		{
			return &characters[i];
		}
	}

	return &NullCharacter;
}

// Метод вернёт значение атрибута
string GetAttrValue(ref _rChar, string _sAttr)
{
	string sTemp;
	if(!CheckAttribute(_rChar, _sAttr)) _rChar.(_sAttr) = "";

	sTemp = _rChar.(_sAttr);
	return sTemp;
}

// Получить рандомную локацию с указанным типом на заданном острове
string IslandGetLocationFromType(string _island, string _type)
{
	ref rLoc;
	int i, iMaxLoc[MAX_LOCATIONS];
	int iRandLoc = 0;
	for(i=1; i<MAX_LOCATIONS; i++)
	{
		makeref(rLoc, locations[i]);
		if(findsubstr(rLoc.id, _type, 0) != -1 && rLoc.islandId == _island)
		{
			iMaxLoc[iRandLoc] = i;
			iRandLoc++;
		}
	}

	if(iRandLoc == 0)
		return "none";

	i = iMaxLoc[rand(iRandLoc-1)];
	return locations[i].id;
}

// Просто сокращение -->
void DisableAllExits(bool _truefalse)
{
	chrDisableReloadToLocation = _truefalse;
	bDisableFastReload         = _truefalse;
}
// Просто сокращение <--

// Warship <--

void LockQuestLine(ref refChar) // Лочим квестовую линейку
{
	refChar.notQuestLine = true;
}

string QuestGetGangLocation(string _areal)	// Получить локацию для генерации банд и т.д.
{
	int n;
	string island = GetArealByCityName(_areal);
	string LocationId, sAreal;
	int storeArray[MAX_LOCATIONS];
	int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{
		if(GiveArealByLocation(&locations[n]) == island)
		{
			//==> на всякий случай
			if(CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if(findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[rand(howStore-1)];
	return locations[n].id;
}

string QuestGetColony(string _city) // Получить рандомную колонию по аттрибуту NPChar.city, не равную _city
{
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetNationRelation2MainCharacter(sti(colonies[n].nation)) != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != _city)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}

string GetColonyExpect2Colonies(string _city1, string _city2) // Исключая две колонии
{
	int storeArray[MAX_COLONIES];
	int howStore = 0;
	string sChrId;
	ref rColony;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		if(!CheckAttribute(rColony, "HasNoFort") && rColony.nation != "none" && sti(rColony.nation) != PIRATE && GetNationRelation2MainCharacter(sti(rColony.nation)) != RELATION_ENEMY && rColony.id != "Panama" && rColony.id != _city1 && rColony.id != _city2)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}

void initStartState2Character(ref ch)
{// метод вызывается в момент новой игры, заполняет главного героя атрибутами, чтоб убрать лишние проверки в if
    NullCharacter.Siege = "";

	ch.SystemInfo.SaveCount = 0;
    ch.SystemInfo.LoadCount = 0;
    ch.SystemInfo.DeadCount = 0;

    ch.SystemInfo.CabinType          = ""; // boal 28.03.05 каюты нет  My_Cabin_Small

    ch.questTemp.Contraband.relation = 60;
    DeleteAttribute(ch, "quest.meeting");
    ch.ShipInStock = 0; // кораблей в порту
	ch.questTemp.abordage = 0;   // двойной абордаж
	ch.questTemp.donate   = 0; // пожертвование церкви

	ch.questTemp.friend_in_tavern = ""; // оптимизация boal
	ch.questTemp.RelationAgentMet = "0"; // оптимизация boal

	ch.questTemp.NationQuest = ""; // взятая линейка квестов

	ch.GenQuest.BrothelCount = "0"; // счетчик посещений девочек
	//ch.GenQuest.Hunter2Pause   = false; // признак бойни в форте на суше - не делать ОЗГов
	ch.I_MAP_SHOW = false;  // boal карты смотрим из предметов
	ch.CameraHoldPos = false;
	ch.CameraShipNPC = 0;// номер компаньона для камеры 0 - ГГ
	ch.GenQuestFort.FarLocator = true; // для методов пихания фантомов в город

	// Чёрная жемчужина
	ch.GenQuest.GhostShip.DeadByMe       = 0;
	ch.GenQuest.GhostShip.KillMe         = 0;
	ch.GenQuest.GhostShip.AskAbout       = 0; // в таверне три раза спросить до появления
	ch.GenQuest.GhostShip.lastspeak_date = "";
    GhostShipInit();

    ch.GenQuest.Find_Merchant.lastspeak_date = "";
    ch.GenQuest.ConvoyPassenger = ""; //структура недовольных по квесту доставки пассажира

	// ==> состояние квеста текущей линейки
	ch.questTemp.State = "";
	// ==> кол-во дней ожидания выдачи следующего квеста губером, стандарт - два дня
	ch.questTemp.Waiting_time = "2";
	// ==> номер текущего квеста, присваиваем сразу второй, т.к. первый берется на момент первого обращения к губеру.
	ch.questTemp.CurQuestNumber = "2";
	//параметры островов и бухт для корсарского метро, ПГГ, и много ещё чего :)
	InitTravelMap();
	// ==> проверка не посещение борделей после свадьбы
	pchar.RomanticQuest.HorseCheck = -1;
	// ==> Количество карт в навигационном атласе
	ch.MapsAtlasCount = 0;
	// ==> Номер пиратского флага (берется из текстуры персональных флагов ГГ)
	ch.Flags.Pirate = 5;
	// ==> Квест Аскольда.
	ch.questTemp.Ascold = "canTakeQuest"; // состояние, если равен "", то пока не даем квест.
	// ==> работорговец
	ch.questTemp.Slavetrader = "canTakeQuest"; //сюда же пихаем флаг
	// ==> общий индекс Аззи.
	ch.questTemp.Azzy = "1";
	// ==> выбор хозяна магазина и уличного торговца по Аскольду.
	SelectAscoldRendom();
	// ==> выбор ростовщика-работорговца
	SelectSlavetraderRendom(); //это непосредственно выбор
	// ==> квест Изабеллы
	IsabellaInit();
	// ==> квест История давней дружбы Lipsar
	SilencePriceInit();
	// ==> Квесты Проклятие Дальних Морей Sinistra
	PDMQuestsInit();
	// ==> Квесты Пираты Карибского Моря
	PKMQuestsInit();
	// ==> Квесты Корсары: Сундук Мертвеца
	KSMQuestsInit();
	// ==> Квесты Корсары: Проклятые Судьбой
	KPSQuestsInit();
	// ==> Все остальные НПС
	VSEnpcInit()
	// ==>  флаги и иниты бергларов
	BerglarsInit();
	// ==>  нищие
	PoormansInit();
	// ==>  кол-во лута, отданного шлюхами
	pchar.questTemp.HorseLoot = 0;
	// ==>  кол-во перетраха со шлюхами
	pchar.questTemp.HorseQty = 0;
	// ==> прерывания на ход к жемчужному промыслу
	PearlGen_SetSantaCatalina("none");
	PearlGen_SetTeno("none");
	// ==> спрашивальщики
	InitQuestions();
	QuestionsInit();
	SeaQuestionsInit(); //02/02/08
	// ==> тюремный флаг на проход внутрь
	ch.questTemp.jailCanMove = false;
	OfficerGirlInit();
	// ==> мушкетеры
	OfficerMushketerInit();
	// ==> линейка ГПК
	ch.questTemp.LSC = false;
	ch.questTemp.LSC.checkBoxes = false; //флаг проверки сундуков в полночь
	pchar.quest.FirstLoginLostShipsCity.win_condition.l1 = "location";
	pchar.quest.FirstLoginLostShipsCity.win_condition.l1.location = "LostShipsCity_town";
	pchar.quest.FirstLoginLostShipsCity.function = "FirstLoginLostShipsCity";
	// ==> квест получения Синей Птицы
	ch.questTemp.BlueBird = "begin";
	ch.questTemp.BlueBird.City = "";
	ch.questTemp.BlueBird.count = 0;
	// ==> генератор Шарпа по жемчугу
	ch.questTemp.Sharp = "begin";
	ch.questTemp.Sharp.City = "";
	ch.questTemp.Sharp.count = 0; //счетчик кол-ва поисков
	ch.questTemp.Sharp.brothelChance = 1; //античит, шанс встретить Шарпа прямо в борделе
	ch.questTemp.Sharp.SeekSpy = "begin"; //состояние квест на поиски информатора Шарпа
	// ==> пиратская линейка
	PiratesLineInit();
	// ==> набор мелких квестов, дается по одному до закрытия
	ch.questTemp.different = "free";
	// ==> ГГ сабля не положена - false
	ch.questTemp.CapBUnarmed = false;
	// ==> линейка Теночтитлана
	ch.questTemp.Teno = "begin";
	pchar.quest.Teno_startInShore.win_condition.l1 = "location";
	pchar.quest.Teno_startInShore.win_condition.l1.location = "Shore53";
	pchar.quest.Teno_startInShore.function = "Teno_startInShore";
	//зачарованный город
	ch.questTemp.MC = "begin"; //флаг квеста
	pchar.quest.MC_startInCaracasRang.win_condition.l1 = "Rank";
	pchar.quest.MC_startInCaracasRang.win_condition.l1.value = 10;
	pchar.quest.MC_startInCaracasRang.win_condition.l1.operation = ">=";
	pchar.quest.MC_startInCaracasRang.function = "MC_startInCaracasRang";
	//ситуации в море
	ch.CanGenerateShipSituation = true;
	//считаем кол во квестов у губеров
	MayorQuestCounter();
}

//==> eddy. квестовая обработка 'ноль часов'.
void QuestActions()
{
	ref sld;
	int i;
	CompanionTravel_ProcessAllTravellers(); // Warship. Процессирование компаньонов-путешественников
	// забираем просроченные лицензии
	for (i=0; i<4; i++)
	{
		if (CheckCharacterItem(pchar, NationShortName(i)+"TradeLicence") && GetDaysContinueNationLicence(i) == -1)
		{
			TakeNationLicence(i);
		}
		else if (CheckCharacterItem(pchar, NationShortName(i)+"TradeLicence"))
		{
			string sTemp = NationShortName(i)+"TradeLicence";
			ref rItem = ItemsFromID(sTemp);
			rItem.Days_left = sti(GetDaysContinueNationLicence(i));
		}
	}
	//Если идёт линейка ГПК, то шмаляем открытые сундуки. Все, кроме Диффиндура.
	if (sti(pchar.questTemp.LSC.checkBoxes))
	{
		LSC_checkBoxes();
	}
	//************** Фр.линейка, третий квест. открываем двери дома коменданта Гаваны *******************
	if (pchar.questTemp.State == "Fr3TakeAnna_WaitMidnight")
	{
		LocatorReloadEnterDisable("Havana_town", "houseS1", false);
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition.l1 = "location";
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition.l1.location = "Havana_houseS1";
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition = "Fr3TakeAnna_FightInHouse";
		pchar.questTemp.State = "Fr3TakeAnna_DoorIsOpen";
	}
	//************** Изабелла, вечер ужина после спасения братца наступил *******************
	if (CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "DelivMigel")
	{
		pchar.RomanticQuest = "SeeTalkNearHouse"; //детектор на итеме теперь сработает
        sld = CharacterFromID("MigelDeValdes");
		//Мигель
		sld.dialog.currentnode = "TalkNearHouse_1";
        ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto24");
        LAi_SetActorType(sld);
		sld.rank = 1; //чтобы умер сразу
		sld.skill.Fencing = 1;
		sld.skill.Pistol = 1;
		LAi_SetHP(sld, 1, 1);
		DeleteAttribute(sld, "Items");
		GiveItem2Character(sld, "blade1");
		GiveItem2Character(sld, "pistol1");
		GiveItem2Character(sld, "order");
		TakeNItems(sld,"bullet", 1);
		TakeNItems(sld,"GunPowder", 1);
		//Сальватор с бандюганами
		LAi_group_Delete("EnemyFight");
        sld = CharacterFromID("Husband");
        sld.dialog.currentnode = "TalkNearHouse_1";
        ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto25");
        for (i=8; i<=9; i++)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Bandit_"+i, "pirate_"+i, "man", "man", 30, PIRATE, 1, true));
			FantomMakeCoolFighter(sld, 30, 80, 70, "blade33", "pistol3", 100);
			LAi_SetStayType(sld);
			if (i==8) ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto7");
			else ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto26");
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		SetTimerCondition("Romantic_DeadBrother_Cancel", 0, 0, 1, false);
	}
	//************** Изабелла, свадьба!!!! *******************
	if (CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "WaitBeginWidding")
	{
		pchar.RomanticQuest = "BeginWidding";
		pchar.quest.Isabella_widding.win_condition.l1 = "locator";
		pchar.quest.Isabella_widding.win_condition.l1.location = "SanJuan_church";
		pchar.quest.Isabella_widding.win_condition.l1.locator_group = "quest";
		pchar.quest.Isabella_widding.win_condition.l1.locator = "detector1";
		pchar.quest.Isabella_widding.function = "Isabella_widding";
		sld = CharacterFromID("Isabella");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld , "SanJuan_church", "goto",  "goto11");
		sld.dialog.currentnode = "TalkWidding";
		//падре
		LAi_SetActorType(CharacterFromID("SanJuan_Priest"));
		SetTimerCondition("Romantic_Widding_Cancel", 0, 0, 1, false);
	}
	//************** ночной сторож в церкви *******************
	if (CheckAttribute(pchar, "questTemp.different.Church_NightGuard"))
	{
		if (pchar.questTemp.different.Church_NightGuard == pchar.location)
		{
			if (!CheckAttribute(pchar, "pchar.quest.ChurchNightGuard_exitFromLoc") && sti(pchar.questTemp.different.Church_NightGuard.NightQty) < 3)
			{
				pchar.quest.ChurchNightGuard_exitFromLoc.win_condition.l1 = "ExitFromLocation";
				pchar.quest.ChurchNightGuard_exitFromLoc.win_condition.l1.location = pchar.location;
				pchar.quest.ChurchNightGuard_exitFromLoc.function = "ChurchNightGuard_exitFromLoc";
				DoQuestFunctionDelay("ChurchNightGuard_timerInChurch", 10.0 + frand(10.0));
			}
		}
		else
		{	//ГГ не находится в нужной церкви в момент полночи
			string sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			AddQuestRecordEx(sTitle, "Church_NightGuard", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterReputation(pchar, -20);
		}
	}
	//************** линейка ГПК, переход в погребок таверны *******************
	if (pchar.questTemp.LSC == "toWineCellar")
	{
		if (GetHour() < 1)
		{
			pchar.questTemp.LSC = "toWineCellarGone";
			sld = characterFromId("LSCBarmen");
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FleuronTavern", "rld", "stay1");
			PChar.quest.LSC_returnBarmen.win_condition.l1            = "Timer";
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.hour  = 1;
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			PChar.quest.LSC_returnBarmen.function = "LSC_returnBarmen";
		}
		else pchar.questTemp.LSC = "toWineCellarLate";
	}
	//************** линейка ГПК, переход в погребок для подслушивания *******************
	if (pchar.questTemp.LSC == "toInterception")
	{
		if (pchar.location == "FleuronTavern" && pchar.location.locator == "reload2")
		{
			DoQuestFunctionDelay("LSC_scriptInterception", 10.0 + frand(20));
		}
		else
		{
			pchar.questTemp.LSC = "InterceptionLate";
			AddQuestRecord("ISS_MainLine", "19");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("","а"));
		}
	}
	//************** линейка ГПК, завал первого каспера с помощь Армо *******************
	if (CheckAttribute (pchar, "questTemp.LSC.Armo"))
	{
		//первый каспер пошёл
		if (sti(pchar.questTemp.LSC.Armo) == 1 || sti(pchar.questTemp.LSC.Armo) == 3 || sti(pchar.questTemp.LSC.Armo) == 5)
		{
			if (pchar.location == "LostShipsCity_town" && GetHour() < 2)
			{
				LAi_group_Delete("EnemyFight");
				sld = characterFromId("Casper_" + pchar.questTemp.LSC.Armo);
				sld.BreakTmplAndFight = true; //проверять на атаку
				sld.reactionOnFightModeOn = true; //проверять на вытаскивание оружия
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload55");
				LAi_ActorGoToLocator(sld, "reload", "reload65", "LSC_casperIsGone", -1.0);
				sld.talker = 11;
				LAi_Character_CanDialog(sld, pchar)
				pchar.questTemp.LSC.Armo.casperIdx = sld.index; //запомним индекс, пригодится на выходе
				//таймер на проверку, убит ли каспер
				pchar.quest.LSC_checkCasperDead.win_condition.l1               = "Location_Type";
				pchar.quest.LSC_checkCasperDead.win_condition.l1.location_type = "LSC_inside";
				pchar.quest.LSC_checkCasperDead.win_condition.l2            = "Timer";
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.hour  = 2;
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.function = "LSC_checkCasperDead";
				pchar.quest.LSC_checkCasperDead.casperIdx = sld.index;
			}
			else
			{
				pchar.questTemp.LSC.Armo = 11; //профукал каспера
			}
		}
	}
	//************** генератор "Продажный патруль" *********************************
	if(CheckAttribute(pchar, "questTemp.ReasonToFast"))
	{
		if(pchar.questTemp.ReasonToFast == "SpeakHorse") // не пришёл в бухту
		{
			AddQuestRecord("ReasonToFast", "2");
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("ReasonToFast");
			pchar.questTemp.ReasonToFast.end = true;
		}
		if(pchar.questTemp.ReasonToFast == "MeetPatrolFail") // в бухту пришёл не один или удачи не хватило
		{
			AddQuestRecord("ReasonToFast", "3");
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("ReasonToFast");
			pchar.questTemp.ReasonToFast.end = true;
		}
		if(CheckAttribute(pchar, "questTemp.ReasonToFast.PatrolLocation"))
		{
			if(CheckAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)],"DisableEncounters"))
			{
				DeleteAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], "DisableEncounters");
			}
		}
		if(CheckAttribute(pchar, "questTemp.ReasonToFast.end"))
		{
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
		}
	}
	//************** генератор "Эпидемия на вражеском корабле" **********************
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		ShipSituation_CheckConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
	}
	//************** поверка нпс-кэпов 5 и 20 числа каждого месяца *******************
	if (GetDataDay() == 5 || GetDataDay() == 20)
	{
		if (CheckAttribute(NullCharacter, "capitainBase"))
		{
			string sName;
			int capIndex, a;
			aref arCapBase, arBase;
    		makearef(arBase, NullCharacter.capitainBase);
    		int	Qty = GetAttributesNum(arBase);
    		for (a=0; a<Qty; a++)
    		{
    			arCapBase = GetAttributeN(arBase, a);
				sName = GetAttributeName(arCapBase); //Id кэпа
				capIndex = GetCharacterIndex(sName);
    			//---------- мёртв ------------
    			if (capIndex == -1)
    			{
					//страховка. если квест ещё открыт - закрываем его
					/*if (CheckActiveQuest(arCapBase.Tilte1))
					{
						CitizCapIsDead_CloseQuest(arCapBase, sName);
					}*/
					DeleteAttribute(arBase, sName);
					Qty --; //для корректной работы цикла при удалении записи в базе
					a--;
				}
				//---------- жив ------------
				else
				{
					if (GetNpcQuestPastDayParam(arCapBase, "checkTime") >= sti(arCapBase.checkTime))
					{
						//if (characters[capIndex].location == "none" && characters[capIndex].quest == "InMap")
						//{
							Cap_SetMapAgain(&characters[capIndex], arCapBase);
						//}
					}
				}
    		}
		}
	}
}

//снятие квеста, если энкаунтер кэпа исчез на карте
void CitizCapIsDead_CloseQuest(aref arCapBase, string capId)
{
	ref sld;
	string sTemp;
	//снимаем установленный таймер
	sTemp = "SecondTimer_" + capId;
	if (capId == "MushketCap") sTemp = "MushketTimer";
	if (capId == "Danielle")   sTemp = "DanielleTimer";
	if (capId == "BlackBeardNPC")   sTemp = "BlackBeardTimer";
	pchar.quest.(sTemp).over = "yes";
	//---------- нпс-квестодатель -------------
	int iTemp = GetCharacterIndex(arCapBase.questGiver);
	if (iTemp != -1)
	{
		//снимаем прерывание на смерть квестодателя
		ref npchar = &characters[iTemp];
		if (CheckAttribute(npchar, "quest.PortmansSeekShip") || CheckAttribute(npchar, "quest.PortmansJornal"))
		{
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			DeleteAttribute(npchar, "quest.PortmansJornal");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		}
		else
		{
			sTemp = "SCQ_" + iTemp;
			pchar.quest.(sTemp).over = "yes";
			characters[iTemp].lifeDay = 0;
		}
	}
	string sTitle1 = arCapBase.Tilte1;
	string sTitle2 = arCapBase.Tilte2;
}

//переустанавливаем на карте живого, но потерянного кэпа
void Cap_SetMapAgain(ref sld, aref arCapBase)
{
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	switch (arCapBase.quest)
	{
	case "mushket":
		if (sld.cityShore == sld.quest.targetShore)
		{
			sld.quest.targetShore = SelectAnyColony(sld.cityShore);
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-2);
		break
	case "citizen":
		if (sld.city == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.city);
		}
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-2);
		break
	case "robber":
		if (sld.city == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.city);
		}
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-2);
		break
	case "jornal":
		if (sld.quest.baseShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.quest.baseShore);
		}
		Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-2);
		break
	case "Danielle":
		if (sld.cityShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.cityShore);
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-2);
		break
	case "BlackBeard":
		if (sld.cityShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = GetRandomPirateCity();
			sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-2);
		break
	}
	//меняем сроки проверки по Id кэпа в базе нпс-кэпов
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = 2;//тут была неопознанная переменная +iTemp... потенциальный баг, если в ней мусор?
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//Иниты Остина, убийцы в городах
void BerglarsInit()
{
	//Остин начинает охоту в городах
	pchar.quest.Ostin_SpawnBanditov.win_condition.l1 = "Rank";
	pchar.quest.Ostin_SpawnBanditov.win_condition.l1.value = 3;
	pchar.quest.Ostin_SpawnBanditov.win_condition.l1.operation = ">=";
	PChar.quest.Ostin_SpawnBanditov.function = "Birglars_Spawn";
}

void QuestionsInit()
{
	ref sld;
	//============> спрашиватель в Тринидаде
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortSpein", "citiz_"+(rand(11)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.rank = 5;
	sld.city = "PortSpein";
	sld.location	= "PortSpein_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortSpein";
	sld.greeting = "cit_common";
	sld.talker = 4; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	SetSelfSkill(sld, 10, 10, 10, 10, 10);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//============> спрашивательница в Виллемстде даёт квест: "Найти пропавшего торговца"
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsVillemstad", "GrunIrma", "woman", "towngirl", 5, HOLLAND, -1, false));
	sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_1", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_2", "Names.txt", "#space#", " ");
	sld.rank = 5;
	sld.city = "Villemstad";
	sld.location	= "Villemstad_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Villemstad";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 3; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	//============> спрашивательница в Порт-о-Принсе даёт квест: "Вызволение из плена мужа горожанки"
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortPax", "LabbeLiliana", "woman", "woman", 5, FRANCE, -1, false));
	sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_3", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_4", "Names.txt", "#space#", " ");
	sld.rank = 5;
	sld.city = "PortPax";
	sld.location	= "PortPax_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortPax";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 3; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//============> спрашиватель в Сан-Хуане
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsSanJuan", "citiz_"+(rand(11)+1), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "SanJuan";
	sld.location	= "SanJuan_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "SanJuan";
	sld.greeting = "cit_common";
	sld.talker = 6; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> спрашиватель в Кумане
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsCumana", "citiz_"+(rand(11)+1), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "Cumana";
	sld.location	= "Cumana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Cumana";
	sld.greeting = "cit_common";
	sld.talker = 6; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> спрашиватель в Порт Рояле
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortRoyal", "girl_"+(rand(7)+1), "woman", "towngirl", 5, ENGLAND, -1, false));
	sld.rank = 5;
	sld.city = "PortRoyal";
	sld.location	= "PortRoyal_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortRoyal";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 3; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//============> спрашиватель в Сантьяго
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsSantiago", "citiz_"+(rand(11)+1), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "Santiago";
	sld.location	= "Santiago_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Santiago";
	sld.greeting = "cit_common";
	sld.talker = 5; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");

}
// ==> обработка базы вопросов, относится к методу выше
int SelectQuestions()
{
	bool bOk = true;
	int iTemp;
	string sTemp;
	while (bOk)
	{
		iTemp = rand(sti(NullCharacter.questions));
		sTemp = "m" + iTemp;
		if (!CheckAttribute(NullCharacter, "questions" + sTemp))
		{
			NullCharacter.questions.(sTemp) = true;
			break;
		}
	}
	return iTemp;
}
// -- нищие --
void PoormansInit()
{
	ref sld;
	//нищий в Нассау
	sld = GetCharacter(NPC_GenerateCharacter("Nassau_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "Nassau";
	sld.location	= "Nassau_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto15";
	sld.forSit.locator1 = "goto17"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Сент-Джонсе
	sld = GetCharacter(NPC_GenerateCharacter("SentJons_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "SentJons";
	sld.location	= "SentJons_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto15";
	sld.forSit.locator1 = "goto17"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Бриджтауне
	sld = GetCharacter(NPC_GenerateCharacter("Bridgetown_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "Bridgetown";
	sld.location	= "Bridgetown_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto19"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Белизе
	sld = GetCharacter(NPC_GenerateCharacter("Beliz_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Beliz";
	sld.location	= "Beliz_town";
	sld.location.group = "goto";
	sld.location.locator = "goto9";
	sld.forStay.locator = "goto9"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto7";
	sld.forSit.locator1 = "goto19"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Каракасе
	sld = GetCharacter(NPC_GenerateCharacter("Caracas_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Caracas";
	sld.location	= "Caracas_town";
	sld.location.group = "goto";
	sld.location.locator = "goto20";
	sld.forStay.locator = "goto20"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto21"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto23";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Картахене
	sld = GetCharacter(NPC_GenerateCharacter("Cartahena_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Cartahena";
	sld.location	= "Cartahena_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto18";
	sld.forSit.locator1 = "goto14"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto6";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Кумане
	sld = GetCharacter(NPC_GenerateCharacter("Cumana_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Cumana";
	sld.location	= "Cumana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto13";
	sld.forSit.locator1 = "goto15"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Кюрасао
	/*sld = GetCharacter(NPC_GenerateCharacter("Villemstad_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, HOLLAND, -1, false));
	sld.city = "Villemstad";
	sld.location	= "Villemstad_town";
	sld.location.group = "goto";
	sld.location.locator = "goto24";
	sld.forStay.locator = "goto24"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto23";
	sld.forSit.locator1 = "goto7"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto8";
	LAi_SetLoginTime(sld, 9.0, 22.0);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");*/
	//нищий в Бас-Тере, Гваделупа
	sld = GetCharacter(NPC_GenerateCharacter("BasTer_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "BasTer";
	sld.location	= "BasTer_town";
	sld.location.group = "goto";
	sld.location.locator = "goto18";
	sld.forStay.locator = "goto18"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto24";
	sld.forSit.locator1 = "goto16"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto17";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий в Гаване
	sld = GetCharacter(NPC_GenerateCharacter("Havana_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Havana";
	sld.location	= "Havana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto22"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto23";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Порт Рояле
	sld = GetCharacter(NPC_GenerateCharacter("PortRoyal_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "PortRoyal";
	sld.location	= "PortRoyal_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto28"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto7";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Форт-де-Франсе, Мартиника
	sld = GetCharacter(NPC_GenerateCharacter("FortFrance_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "FortFrance";
	sld.location	= "FortFrance_town";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	sld.forStay.locator = "goto4"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto14";
	sld.forSit.locator1 = "goto10"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий на Невисе
	sld = GetCharacter(NPC_GenerateCharacter("Charles_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "Charles";
	sld.location	= "Charles_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto19";
	sld.forSit.locator1 = "goto13"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Порто Белло
	sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "PortoBello";
	sld.location	= "PortoBello_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto25"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto12";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Порт-о-Принс, Эспаньола
	sld = GetCharacter(NPC_GenerateCharacter("PortPax_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "PortPax";
	sld.location	= "PortPax_town";
	sld.location.group = "goto";
	sld.location.locator = "goto14";
	sld.forStay.locator = "goto14"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto25";
	sld.forSit.locator1 = "goto13"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto11";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий в Сантьяго
	sld = GetCharacter(NPC_GenerateCharacter("Santiago_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Santiago";
	sld.location	= "Santiago_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto15"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto28";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Мариго, Сан Мартин
	sld = GetCharacter(NPC_GenerateCharacter("Marigo_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, HOLLAND, -1, false));
	sld.city = "Marigo";
	sld.location	= "Marigo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto16";
	sld.forStay.locator = "goto16"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto4"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto9";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	//нищий в Тортуге
	sld = GetCharacter(NPC_GenerateCharacter("Tortuga_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "Tortuga";
	sld.location	= "Tortuga_town";
	sld.location.group = "goto";
	sld.location.locator = "goto23";
	sld.forStay.locator = "goto23"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto18"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий в Порт Спейне, Тринидад
	sld = GetCharacter(NPC_GenerateCharacter("PortSpein_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "PortSpein";
	sld.location	= "PortSpein_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto14"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//заказчик нищих
	pchar.quest.ISS_SpawnTrust.win_condition.l1 = "Rank";
	pchar.quest.ISS_SpawnTrust.win_condition.l1.value = 15;
	pchar.quest.ISS_SpawnTrust.win_condition.l1.operation = ">=";
	PChar.quest.ISS_SpawnTrust.function = "ISS_SpawnTrust";
	//несчастный мушкетер
	sld = GetCharacter(NPC_GenerateCharacter("OffMushketer", "MusketeerEnglish_1", "man", "man", 25, ENGLAND, -1, false));
	sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_7", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_8", "Names.txt", "#space#", " ");
	sld.location	= "PortSpein_houseH3";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "OffMushketer";
	sld.HalfImmortal = true;  // Контузия
	sld.HeroModel = "MusketeerEnglish_1,MusketeerEnglish_1_1,MusketeerEnglish_1_2,MusketeerEnglish_1_3,MusketeerEnglish_1_4,MusketeerEnglish_1_5";
	SetSelfSkill(sld, 80, 10, 2, 100, 80);
	SetShipSkill(sld, 5, 5, 2, 10, 5, 20, 10, 10, 70);
	SetSPECIAL(sld, 7, 4, 9, 3, 8, 7, 9);
	LAi_SetSitType(sld);
	sld.greeting = "cit_common";
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "HPPlus");
	//SetCharacterPerk(sld, "Medic");
	SetCharacterPerk(sld, "GunProfessional");
	DeleteAttribute(sld, "Items");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	sld.HoldEquip = true; //удерживать оружие при обмене предметами
}

//=============== капитан Шарп ====================
string Sharp_choiceAction()
{
	string sBack;
	ref sld;
	//удалим Шарпа с карты, если он плывёт ещё где-то
	Map_ReleaseQuestEncounter("Sharp");
	group_DeleteGroup("Sharp_Group");
	if (rand(3) != 2 && sti(pchar.questTemp.Sharp.count) < 5)
	{	//ещё динамим, отправляем ГГ в другой город
		string sCity = pchar.questTemp.Sharp.City; //предыдущая цель, запомним для СЖ
		pchar.questTemp.Sharp.City.rumour = true; //флаг дать слух в городе
		pchar.questTemp.Sharp.City = GetSharpCity(); //новый город
		sBack = GetSharpRumour_toCityTarget();
		pchar.questTemp.Sharp.count = sti(pchar.questTemp.Sharp.count) + 1; //счетчик
		AddQuestRecord("SharpPearl", "2");
		AddQuestUserData("SharpPearl", "sOldTarget", XI_ConvertString("Colony" + sCity + "Voc"));
		AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
		if (GetIslandByCityName(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
		{
			AddQuestUserData("SharpPearl", "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(pchar.questTemp.Sharp.City) + "Voc"));
		}
		//запускаем опять Шарпа на карту
		sld = characterFromId("Sharp");
		string sGroup = "Sharp_Group";
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		sld.mapEnc.type = "trade";
		sld.mapEnc.worldMapShip = "quest_ship";
		sld.mapEnc.Name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_9", "Names.txt", "#space#", " ");
		string sColony= SelectAnyColony(sCity); //колония, откуда плывёт Шарп
		int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sColony), GetArealByCityName(pchar.questTemp.Sharp.City)) + 1; //дней доехать даем с запасом
		Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
	}
	else
	{
		if (rand(5) < 4)
		{
			sBack = GetSharpRumour_inIsland();
			pchar.questTemp.Sharp.Island = GiveArealByLocation(loadedLocation);
			pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			Pchar.quest.Sharp_loginNearIsland.win_condition.l1 = "location";
			Pchar.quest.Sharp_loginNearIsland.win_condition.l1.location = pchar.questTemp.Sharp.Island;
			Pchar.quest.Sharp_loginNearIsland.function = "Sharp_loginNearIsland";
			AddQuestRecord("SharpPearl", "3");
			SaveCurrentQuestDateParam("questTemp.Sharp");
			Log_QuestInfo(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_1", "Logs.txt", "#space#", " "));
		}
		else
		{
			sBack = GetSharpRumour_inCity();
			pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			float locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			sld = &characters[GetCharacterIndex("Sharp")];
			sld.dialog.currentnode = "CitySharp";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			ChangeCharacterAddressGroup(sld, pchar.location, "patrol", LAi_FindFarLocator("patrol", locx, locy, locz));
			AddQuestRecord("SharpPearl", "11");
			Log_QuestInfo(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_2", "Logs.txt", "#space#", " "));
		}
	}
	return sBack;
}

//ищем новый город
string GetSharpCity()
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (GetBaseHeroNation() != PIRATE)
	{
	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && GetRelation2BaseNation(sti(colonies[n].nation)) != RELATION_ENEMY && GiveArealByLocation(loadedLocation) != colonies[n].island && colonies[n].id != "Panama") //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	else
	{
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GiveArealByLocation(loadedLocation) != colonies[n].island && colonies[n].id != "Panama") //не на свой остров
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[rand(howStore-1)];
	return colonies[iRes].id;
}
//фразы по умолчанию
string GetSharpRumour_default()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "Капитан Шарп был здесь, я его видел. Но сейчас его в городе нет, а куда ушёл - не знаю."; break;
        case 1: sRumour = "Капитан Шарп заходил в наш город. Где он сейчас я не знаю, у нас его точно нет."; break;
        case 2:	sRumour = "Капитан Барталомью Шарп ушёл из города буквально на днях..."; break;
    }
	return sRumour;
}
//фразы в другой город
string GetSharpRumour_toCityTarget()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "Капитан Бартоломью Шарп был у нас в городе и, как всегда, умудрился 'отметиться'... Но сейчас его здесь нет. По слухам он ушёл в " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + "."; break;
        case 1: sRumour = "Знаете, капитан Шарп был в городе недавно. Веселый пират, этот Барталомью... Хорошо, однако, что он покинул наш город. Кажется он ушёл в " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + "."; break;
        case 2:	sRumour = "Вы знаете, недавно нас почтил своим присутствием капитан Шарп. Но, к нашему большому разочарованию, нового карибского анекдота 'от Шарпа' не случилось. Жаль... А сейчас его нет у нас в городе. Говорят, он ушёл в " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + ". Может им повезёт..."; break;
    }
	return sRumour;
}
//фразы у осрова
string GetSharpRumour_inIsland()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "Вы знаете, капитан Шарп только что вышел из города на своем бриге. Если бы вы прибыли с пол часа назад, то увидели бы его прямо в порту."; break;
        case 1: sRumour = "Капитан Шарп... Да уже, тот ещё капитан. Знаете, он только что покинул наш город. Если вы поторопитесь, то сможете его застать в окрестных водах."; break;
        case 2:	sRumour = "Бартоломью Шарп буквально с час назад вышел из нашего порта в море."; break;
    }
	return sRumour;
}
//фразы в городе
string GetSharpRumour_inCity()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "Пару минут назад капитан Шарп столкнулся со мной лицом к лицу. Ходит здесь по улицам, странно, что не в борделе..."; break;
        case 1: sRumour = "Только что на улице довелось поговорить с капитаном Шарпом. Занятный, знаете ли, тип..."; break;
        case 2:	sRumour = "Капитан Шарп сейчас гуляет по улицам. А мы все ждем, чего же он выкинет в очередной раз..."; break;
    }
	return sRumour;
}

//=============== шебека Синяя Птица.  ====================
string BlueBurd_setTradeShip()
{
	pchar.questTemp.BlueBird.Island = GiveArealByLocation(loadedLocation);
	Pchar.quest.BlueBird_loginFleut.win_condition.l1 = "location";
	Pchar.quest.BlueBird_loginFleut.win_condition.l1.location = pchar.questTemp.BlueBird.Island;
	Pchar.quest.BlueBird_loginFleut.function = "BlueBird_loginFleut";
	pchar.questTemp.BlueBird.nation = colonies[FindColony(pchar.questTemp.BlueBird.City)].nation; //нация колонии, откуда кораблик
	aref aName;
	makearef(aName, pchar.questTemp.BlueBird);
	SetRandomNameToShip(aName);
	AddQuestRecord("Xebeca_BlueBird", "10");
	AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + pchar.questTemp.BlueBird.City + "Voc"));
	AddQuestUserData("Xebeca_BlueBird", "sShipName", "'" + aName.Ship.Name + "'");
	AddQuestUserData("Xebeca_BlueBird", "sCity_2", XI_ConvertString("Colony" + pchar.questTemp.BlueBird.City + "Gen"));
	AddQuestUserData("Xebeca_BlueBird", "sTradeName", GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")));
	AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	SaveCurrentQuestDateParam("questTemp.BlueBird");
	return GetBlueBirdRumour_Ship(); //текст слуха
}
//фразы по слухам, наводки на корабли тоговцев
string GetBlueBirdRumour_Ship()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = GetConvertStrWithReplace("Variable_Blue_Bird_1.1", "AddRumours.txt", "#space#", " ") + GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")) + GetConvertStrWithReplace("Variable_Blue_Bird_1.2", "AddRumours.txt", "#space#", " ") + pchar.questTemp.BlueBird.Ship.Name + GetConvertStrWithReplace("Variable_Blue_Bird_1.3", "AddRumours.txt", "#space#", " "); break;
		case 1: sRumour = GetConvertStrWithReplace("Variable_Blue_Bird_2.1", "AddRumours.txt", "#space#", " ") + GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")) + GetConvertStrWithReplace("Variable_Blue_Bird_2.2", "AddRumours.txt", "#space#", " ") + pchar.questTemp.BlueBird.Ship.Name + GetConvertStrWithReplace("Variable_Blue_Bird_2.3", "AddRumours.txt", "#space#", " "); break;
        case 2:	sRumour = GetConvertStrWithReplace("Variable_Blue_Bird_3.1", "AddRumours.txt", "#space#", " ") + GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")) + GetConvertStrWithReplace("Variable_Blue_Bird_3.2", "AddRumours.txt", "#space#", " ") + pchar.questTemp.BlueBird.Ship.Name + GetConvertStrWithReplace("Variable_Blue_Bird_3.3", "AddRumours.txt", "#space#", " "); break;
    }
	return sRumour;
}
//======================= пиратская линейка ===================================
void PiratesLineInit()
{
	pchar.questTemp.piratesLine = "begin";
}

//ищем город определённой нации, проверять наличие ростовщика и тавернщика
string GetQuestNationsCity(int _nation)
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none"  && colonies[n].id != "Panama" && sti(colonies[n].nation) == _nation && GiveArealByLocation(loadedLocation) != colonies[n].island) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_tavernkeeper") > 0 && GetCharacterIndex(colonies[n].id + "_usurer") > 0)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[cRand(howStore-1)];
	return colonies[iRes].id;
}

string GetQuestNationsPrison(int _nation)//ищем город определённой нации, проверять наличие тавернщика и тюремного босса
{
	int n, iRes;
    int fortArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none"  && colonies[n].id != "Panama" && sti(colonies[n].nation) == _nation && GiveArealByLocation(loadedLocation) != colonies[n].island) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_tavernkeeper") > 0 && !CheckAttribute(colonies[n], "HasNoFort"))
			{
				fortArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	iRes = fortArray[cRand(howStore-1)];
	return colonies[iRes].id;
}

string GetRandomPirateCity()
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none"  && colonies[n].id != "Panama" && sti(colonies[n].nation) == 4 && GiveArealByLocation(loadedLocation) != colonies[n].island) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[cRand(howStore-1)];
	return colonies[iRes].id;
}

//ищем не вражескую колонию, куда можно доплыть
string SelectNotEnemyColony(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{

		/* if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Caiman" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров */
		if (colonies[n].id != "Panama" && colonies[n].id != "Caiman" && colonies[n].nation != "none"  && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
			if (nation != RELATION_ENEMY)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

//ищем любую национальную колонию, куда можно доплыть
string SelectAnyColony(string _City)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(_City) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string SelectAnyColony2(string _City1, string _City2)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(_City1) != colonies[n].islandLable && GetIslandByCityName(_City2) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

ref CheckLSCCitizen()
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[3]);
	if (sSeeked == "адмирал" || sSeeked == "адмиралa")
	{
		return characterFromId("LSCMayor");
	}
	if (sSeeked == "трактирщик" || sSeeked == "трактирщика" || sSeeked == "тавернщик"|| sSeeked == "тавернщика" || sSeeked == "хозяин таверны" || sSeeked == "хозяина таверны")
	{
		return characterFromId("LSCBarmen");
	}
	if (sSeeked == "официантка" || sSeeked == "официантку")
	{
		return characterFromId("LSCwaitress");
	}
	if (sSeeked == "механика" || sSeeked == "механик")
	{
		return characterFromId("Mechanic");
	}
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "city") && rCharacter.city == "LostShipsCity")
		{
			sTemp = GetStrSmallRegister(rCharacter.name + " " + rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
			{
				return rCharacter;
			}
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
			{
				return rCharacter;
			}
			else
			{
				sTemp = GetStrSmallRegister(rCharacter.name);
				if (findsubstr(sSeeked, sTemp , 0) != -1)
				{
					return rCharacter;
				}
			}
		}
	}
	return &NullCharacter;
}

string WhereLSCCitizen(ref rCharacter)
{
	string sShip = "none";
	string sTemp;
	if (rCharacter.location	== "LostShipsCity_town")
	{
		sTemp = rCharacter.location.locator;
		sTemp = strcut(sTemp, 4, 5);
		switch (sTemp)
		{
			case "01": sShip = "на бэттлшипе 'Тартарус', где тюрьма"; break;
			case "02": sShip = "на фрегате 'Каролина'"; break;
			case "03": sShip = "на флейте 'Церес Смити'"; break;
			case "04": sShip = "на галеоне 'Эсмеральда', где магазин"; break;
			case "05": sShip = "на каравелле 'Флерон', где таверна"; break;
			case "06": sShip = "на пинасе 'Фурия', в носовой части"; break;
			case "07": sShip = "на пинасе 'Фурия', в кормовой части"; break;
			case "08": sShip = "на галеоне 'Глория', где церковь"; break;
			case "09": sShip = "на флейте 'Плуто'"; break;
			case "10": sShip = "на корвете 'Протектор'"; break;
			case "11": sShip = "на варшипе 'Сан Августин', где резиденция адмирала"; break;
			case "12": sShip = "на барке 'Сан Габриель', в носовой части"; break;
			case "13": sShip = "на барке 'Сан Габриель', в кормовой части"; break;
			case "14": sShip = "на бриге 'Санта Флорентина'"; break;
			case "15": sShip = "на галеоне 'Эва'"; break;
			case "16": sShip = "на галеоне 'Веласко'"; break;
		}
	}
	else
	{
		switch (rCharacter.location)
		{
			case "AvaShipInside3": sShip = "в галеоне 'Эва'"; break;
			case "CarolineBank": sShip = "в фрегате 'Каролина'"; break;
			case "CeresSmithy": sShip = "во флейте 'Церес Смити'"; break;
			case "EsmeraldaStoreBig": sShip = "в галеоне 'Эсмеральда', в магазине"; break;
			case "FenixPlatform": sShip = "в платформе 'Феникс'"; break;
			case "FernandaDiffIndoor": sShip = "во флейте 'Фернандо Диффиндур'"; break;
			case "FleuronTavern": sShip = "в каравелле 'Флерон', в таверне"; break;
			case "FurieShipInside2": sShip = "в пинасе 'Фурия'"; break;
			case "GloriaChurch": sShip = "в галеоне 'Глория', в церкви"; break;
			case "PlutoStoreSmall": sShip = "в трюме флейта 'Плуто'"; break;
			case "ProtectorFisher": sShip = "в корвете 'Протектор'"; break;
			case "SanAugustineResidence": sShip = "в варшипе 'Сан Августин', в резиденции адмирала"; break;
			case "SanGabrielMechanic": sShip = "в барке 'Сан Габриель'"; break;
			case "SantaFlorentinaShipInside4": sShip = "в бриге 'Санта Флорентина'"; break;
			case "TartarusPrison": sShip = "в бэттлшипе 'Тартарус', в тюрьме"; break;
			case "VelascoShipInside1": sShip = "в галеоне 'Веласко'"; break;
		}
	}
	return sShip;
}

//отдать забытый судовой журнал. помещаем в город кэпа, который приплыл к назначенной колонии
void SetCapitainFromSeaToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг в городе
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	sld.location	= sld.City + "_PortOffice";
	sld.location.group = "goto";
	sld.location.locator = "goto"+(rand(2)+1);
	LAi_SetCitizenType(sld);

	/*int iColony = FindColony(sld.City);
	string sGroup = "PorpmansShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);*/

	//таймер через сколько опять выйти в море
	int Qty = rand(2)+2;
	string name = "Timer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetCapitainFromCityToSea";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 2;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//даем слух, что кэп в городе
	AddSimpleRumourCity(LinkRandPhrase(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_1", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_2", "AddRumours.txt", "#space#", " ") + GetFullName(sld) + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_3", "AddRumours.txt", "#space#", " "),
		GetConvertStrWithReplace("Variable_LSC_Q2Utilite_4", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_5", "AddRumours.txt", "#space#", " "),
		GetConvertStrWithReplace("Variable_LSC_Q2Utilite_6", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_7", "AddRumours.txt", "#space#", " ") + GetFullName(sld) + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_8", "AddRumours.txt", "#space#", " ")), sld.City, Qty, 1, "none");
}
//отдать забытый судовой журнал. записть в квестбук из слухов
void PortmansBook_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		string sTitle = characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")].id + "PortmansBook_Delivery";
		AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Voc"));
		}
	}
}

//разыскать кэпа-вора. помещаем в город кэпа, который приплыл к назначенной колонии
void SetRobberFromMapToSea(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InPort"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; //нацию дадим, что и у города

	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);

	//таймер через сколько опять выйти на карту
	int Qty = rand(2)+2;
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetRobberFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 2;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//даем слух, что кэп на рейде
	AddSimpleRumourCity(LinkRandPhrase(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_9", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_10", "AddRumours.txt", "#space#", " ") + GetFullName(sld) + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_11", "AddRumours.txt", "#space#", " "),
		GetConvertStrWithReplace("Variable_LSC_Q2Utilite_12", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_13", "AddRumours.txt", "#space#", " "),
		GetConvertStrWithReplace("Variable_LSC_Q2Utilite_14", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_15", "AddRumours.txt", "#space#", " ") + GetFullName(sld) + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_16", "AddRumours.txt", "#space#", " ")), sld.City, Qty, 1, "none");
}
//разыскать кэпа-вора. запись в квестбук из слухов
void PortmansSeekShip_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		ref npchar = &characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")];
		string sTitle = npchar.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTitle, "Portmans_SeekShip", "3");
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName)));
		AddQuestUserData(sTitle, "sShipName", sld.Ship.name);
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		iTemp = RealShips[sti(sld.Ship.Type)].basetype;
		AddQuestUserData(sTitle, "sSexWord", GetShipSexWord(ShipsTypes[iTemp].name, "ушёл", "ушла"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Voc"));
		}
	}
}

//розыск кэпов горожанами
void CitizCapFromMapToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг кэпа ходит по городу
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; //нацию дадим, что и у города
	if (rand(1))
	{	//ходит в городе
		sld.location	= sld.City + "_town";
		sld.location.group = "goto";
		sld.location.locator = "goto"+(rand(5)+1);
		LAi_SetCitizenType(sld);
		string slai_group = GetNationNameByType(sti(colonies[iColony].nation))  + "_citizens";
		LAi_group_MoveCharacter(sld, slai_group);
		//даем слух, что кэп на рейде
		AddSimpleRumourCity(LinkRandPhrase(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_17", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_18", "AddRumours.txt", "#space#", " ") + GetFullName(sld) + ".",
			GetConvertStrWithReplace("Variable_LSC_Q2Utilite_19", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_20", "AddRumours.txt", "#space#", " "),
			GetConvertStrWithReplace("Variable_LSC_Q2Utilite_21", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_22", "AddRumours.txt", "#space#", " ") + GetFullName(sld) + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_23", "AddRumours.txt", "#space#", " ")), sld.City, Qty, 1, "none");
	}
	else
	{	//стоит на рейде в порту
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
		Group_SetTaskNone(sGroup);
		//даем слух, что кэп на рейде
		AddSimpleRumourCity(LinkRandPhrase(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_24", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_25", "AddRumours.txt", "#space#", " ") + GetFullName(sld) + ".",
			GetConvertStrWithReplace("Variable_LSC_Q2Utilite_26", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_27", "AddRumours.txt", "#space#", " "),
			GetConvertStrWithReplace("Variable_LSC_Q2Utilite_28", "AddRumours.txt", "#space#", " ") + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_29", "AddRumours.txt", "#space#", " ") + GetFullName(sld) + GetConvertStrWithReplace("Variable_LSC_Q2Utilite_30", "AddRumours.txt", "#space#", " ")), sld.City, Qty, 1, "none");
	}
	//таймер через сколько опять выйти на карту
	int Qty = rand(2)+2; //через сколько дней выйдем на карту
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "CitizCapFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 2;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//разыск кэпа от горожан. запись в квестбук из слухов
void CitizSeekCap_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		ref npchar = &characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)];
		string sTitle = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "3");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Voc"));
		}
	}
}

//плавание мушкетерского кэпа
void SetMushketFromMapToSea()
{
	ref sld = characterFromId("MushketCap");
	sld.quest = "InShore"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);

	string sGroup = "MushketCapShip";
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+5));
	Group_SetTaskNone(sGroup);
	//таймер через сколько опять выйти на карту
	int Qty = rand(2)+2;
	string name = "MushketTimer";
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetMushketFromSeaToMap";
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 2;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//плавание Даньки
void SetDanielleFromMapToSea()
{
	ref sld = characterFromId("Danielle");
	sld.quest = "InShore"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);

	string sGroup = "DanielleGroup";
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+3));
	Group_SetTaskNone(sGroup);
	//таймер через сколько опять выйти на карту
	int Qty = rand(2)+2;
	string name = "DanielleTimer";
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetDanielleFromSeaToMap";
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 2;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

void SetBlackBeardFromMapToSea()
{
	ref sld = characterFromId("BlackBeardNPC");
	sld.quest = "InShore"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);

	string sGroup = "BlackBeardGroup";
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+3));
	Group_SetTaskNone(sGroup);
	//таймер через сколько опять выйти на карту
	int Qty = rand(2)+2;
	string name = "BlackBeardTimer";
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetBlackBeardFromSeaToMap";
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 2;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//линейка Блада в Барбадосе
//поставить Синко Льягас в город
void SetShipInBridgetown()
{
	int n = FindLocation("Bridgetown_town");
	locations[n].models.always.ship = "Bridgetown_ship";
	locations[n].models.always.shipreflect = "Bridgetown_shipreflect";
	Locations[n].models.always.shipreflect.sea_reflection = 1;
	locations[n].models.always.locators = "Bridgetown_locatorsShip";
	locations[n].models.day.fonarShip = "Bridgetown_fdShip";
	locations[n].models.night.fonarShip = "Bridgetown_fnShip";
	locations[n].models.day.charactersPatch = "Bridgetown_patchship_day";
	locations[n].models.night.charactersPatch = "Bridgetown_patchship_night";

	locations[n].reload.ship1.name = "reloadShip";
	locations[n].reload.ship1.go = "Cabin";
	locations[n].reload.ship1.emerge = "reload1";
	locations[n].reload.ship1.autoreload = "0";
	locations[n].reload.ship1.label = "cabine";

	n = FindLocation("Cabin");
	DeleteAttribute(&locations[n], "boarding");
	DeleteAttribute(&locations[n], "camshuttle");
	DeleteAttribute(&locations[n], "CabinType");

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Bridgetown_town";
	locations[n].reload.l1.emerge = "reloadShip";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Ship";
}
//убрать Синко Льягас из города
void RemoveShipFromBridgetown()
{
	int n = FindLocation("Bridgetown_town");
	DeleteAttribute(&locations[n], "models.always.ship");
	DeleteAttribute(&locations[n], "models.always.shipreflect");
	DeleteAttribute(&locations[n], "models.always.shipreflect.sea_reflection");
	locations[n].models.always.locators = "Bridgetown_locators";
	DeleteAttribute(&locations[n], "models.day.fonarShip");
	DeleteAttribute(&locations[n], "models.night.fonarShip");
	locations[n].models.day.charactersPatch = "Bridgetown_patch_day";
	locations[n].models.night.charactersPatch = "Bridgetown_patch_night";
	DeleteAttribute(&locations[n], "reload.ship1");

	n = FindLocation("Cabin");
	DeleteAttribute(&locations[n], "reload");
	Locations[n].boarding = "true";
	Locations[n].boarding.nextdeck = "";
	Locations[n].camshuttle = 1;
	Locations[n].boarding.locatorNum = 1;
	Locations[n].CabinType = true;
	locations[n].environment.weather.rain = false;
	Locations[n].boarding.Loc.Hero = "loc0";
    Locations[n].boarding.Loc.Capt = "aloc2";
}

//------------------- линейка ГПК ----------------------
//пробежаться по сундукам
void LSC_checkBoxes()
{
	ref loc;
	aref arBox;
	string sName;
	for(int i=0; i<MAX_LOCATIONS; i++)
	{
		loc = &locations[i];
		if (CheckAttribute(loc, "fastreload") && loc.fastreload == "LostShipsCity" && loc.id != "FernandaDiffIndoor")
		{
			for(int n=1; n<=MAX_HANDLED_BOXES; n++)
			{
				sName = "private" + n;
				if (CheckAttribute(loc, sName) && sName != "private11")
				{
					makearef(arBox, loc.(sName));
					if (CheckAttribute(arBox, "equip") && rand(1))
					{
						DeleteAttribute(arBox, "items");
						arBox.items = "";
					}
				}
				else break;
			}
		}
	}
}

//линейка ГПК. проверить дистанцию до своих во время атаки
void LSC_CheckCasperDistance(ref sld)
{
	if (!CheckAttribute(pchar, "questTemp.LSC.Armo.Interrapt"))
	{
		sld.quest.checkCasper = true; //для обработки в АИ warrior
		pchar.quest.LSC_KillOneCasper.win_condition.l1 = "NPC_Death";
		pchar.quest.LSC_KillOneCasper.win_condition.l1.character = sld.id;
		pchar.quest.LSC_KillOneCasper.function= "LSC_KillOneCasper";
		pchar.quest.LSC_KillOneCasper.casperIdx = sld.index;
		pchar.questTemp.LSC.Armo.Interrapt = true; //чтобы не вызывать больше прерывания
	}
	float dist;
	if (GetCharacterDistByLoc(sld, "goto", "goto12_4", &dist))
	{
		if (dist < 40.0)
		{
			LSC_CasperIsHelp();
		}
	}
}
//клан ломится на выручку
void LSC_CasperIsHelp()
{
	Log_SetStringToLog(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_3", "Logs.txt", "#space#", " "));
	chrDisableReloadToLocation = true;
	pchar.questTemp.LSC = "toSeekMechanikCasperOff";
	//если пошёл навал, то чистим квест Армо
	pchar.questTemp.LSC.Armo = 15; //завязываем с дачей квестов от Армо
	pchar.quest.LSC_KillOneCasper.over = "yes";
	pchar.quest.LSC_checkCasperDead.over = "yes";
	//бойцов в подмогу
	int iTemp = GetCharacterIndex("Casper_head");
	if (iTemp != -1) ChangeCharacterAddressGroup(&characters[iTemp], "LostShipsCity_town", "reload", "reload55");
	for (int i=1; i<=11; i++)
	{
		iTemp = GetCharacterIndex("Casper_"+i);
		if (iTemp != -1)
		{
			if (characters[iTemp].location != "LostShipsCity_town")
			{
				ChangeCharacterAddressGroup(&characters[iTemp], "LostShipsCity_town", "reload", "reload55");
			}
			else
			{
				if (!LAi_IsDead(&characters[iTemp]))
				{
					LAi_group_MoveCharacter(&characters[iTemp], "PearlGroup_2");
					DeleteAttribute(&characters[iTemp], "quest.checkCasper"); //сносим флаги на проверку расстояния до базы
				}
			}
		}
	}
	//мушкетеров ставим
	sld = GetCharacter(NPC_GenerateCharacter("CasperMush_1", "Mushketer_2", "man", "mushketer", 30, PIRATE, -1, false));
	SetCharacterPerk(sld, "GunProfessional");
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload55");

	sld = GetCharacter(NPC_GenerateCharacter("CasperMush_2", "Mushketer_4", "man", "mushketer", 30, PIRATE, -1, false));
	SetCharacterPerk(sld, "GunProfessional");
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload55");
	//дополнительно, на всякий случай
	//LAi_group_SetRelation("PearlGroup_2", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	//LAi_group_FightGroups("PearlGroup_2", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("PearlGroup_2", "OpenTheDoors");
}

//квест на мужа Элис Тейлор, после получения слуха
void LSC_rumourElisHusband()
{
	if (!CheckActiveQuest("ISS_ElisHusband"))
	{
		pchar.questTemp.LSC.ElisHusband = "begin";
		AddQuestRecord("ISS_ElisHusband", "1");
	}
}
//начало сразу, после первого базара с адмиралом
void LSC_beginElisHusband()
{
	// муж Элис Тейлор
	ref sld = GetCharacter(NPC_GenerateCharacter("MaximTailor", "shipowner_10", "man", "man", 10, PIRATE, -1, false));
	sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_10", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_11", "Names.txt", "#space#", " ");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "TartarusPrison";
	sld.location.group = "quest";
	sld.location.locator = "prison4";
	sld.dialog.filename   = "Quest\LostShipsCity\MaximTailor.c";
	sld.dialog.currentnode   = "InPrison";
	sld.cityTape = "quest"; //тип нпс
	sld.greeting = "pirat_common";
	sld.location.hours = 4; //передвижения через .. часов
	LAi_SetGroundSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
}

//квест со скелетом Лейтона Декстера
void LSC_rumourLostDecster()
{
	if (!CheckActiveQuest("LSC_findDekster"))
		AddQuestRecord("LSC_findDekster", "1");
}
void LSC_enterAdmiralBox()
{
	if (!CheckAttribute(pchar, "questTemp.LSC.private10"))
	{
		if (CheckAttribute(pchar, "questTemp.LSC.lostDecster"))
		{
			if (pchar.questTemp.LSC.lostDecster == "seekBox")
			{
				AddQuestRecord("LSC_findDekster", "6");
				AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("ел","ла"));
			}
			else
			{
				iTemp = GetCharacterIndex("LSC_Prisoner1");
				if (iTemp != 1 && CheckAttribute(&characters[iTemp], "quest.decster"))
				{
					AddQuestRecord("LSC_findDekster", "7");
				}
				else
				{
					AddQuestRecord("LSC_findDekster", "9");
					AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("ел","ла"));
				}
			}
		}
		else
		{
			AddQuestRecord("LSC_findDekster", "8");
			AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("ел","ла"));
		}
		pchar.questTemp.LSC.lostDecster = "foundAdmiralBox";
		AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_31", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "LSC_rumourAdmiralLostKey");
		pchar.questTemp.LSC.private10 = true; //чтобы больше не срабатывало
	}
}
void LSC_rumourAdmiralLostKey()
{
	//делаем видимым ключ
	ref sld = ItemsFromID("keyPanama");
	sld.shown = true;
	sld.startLocation = "LostShipsCity_town";
	sld.startLocator = "item" + (rand(4)+2);
	ChangeItemName("keyPanama", "itmname_keyPanama_LSC");
	ChangeItemDescribe("keyPanama", "itmdescr_keyPanama_LSC");
	SetTimerFunction("LSC_admiralFoundOwnKey", 0, 0, 2); //таймер на снятие ключа из локатора
	pchar.questTemp.LSC.lostDecster = "admiralLostKey";
	AddQuestRecord("LSC_findDekster", "10");
}

//таймер
void SetShowTimer(float time)
{
	pchar.showTimer = time + 0.99;
	pchar.quest.ClearTimer.win_condition.l1 = "ExitFromLocation";
	pchar.quest.ClearTimer.win_condition.l1.location = pchar.location;
	pchar.quest.ClearTimer.function = "ClearTimer";
}

void ClearTimer(string qName)
{
	DeleteAttribute(pchar, "showTimer");
	ClearAllLogStrings();
}

//создание резервной базы на абордажников для юза нефритового черепа
void CopyPassForAztecSkull()
{
	if (CheckCharacterItem(pchar, "SkullAztec"))
	{
        //сносим старую базу
        DeleteAttribute(pchar, "AztecSkull");
		pchar.AztecSkull = "";
		//заполняем архивную базу
		string sTemp;
		aref	arFromBox, arToBox;
    	makearef(arFromBox, pchar.fellows.passengers.officers);
		makearef(arToBox, pchar.AztecSkull);
		CopyAttributes(arToBox, arFromBox);
	}
}

bool IsAztecSkullOfficer(ref sld)
{
	if (!CheckAttribute(pchar, "AztecSkull.id1")) return false;
	string sTemp;
	aref arOfficer;
    makearef(arOfficer, pchar.AztecSkull);
    for (i=1; i<=MAX_NUM_FIGHTERS; i++)
    {
		sTemp = "id" + i;
		if (CheckAttribute(arOfficer, sTemp) && arOfficer.(sTemp) == sld.index)
		{
			return true;
		}
	}
	return false;
}

void SetAztecUsedTotem(ref _location, string _itemId, string _locator)
{
	//-----------------------------------------
	if (_itemId == "Totem_11")    //снимаем огонь
	{
		DeleteAttribute(_location, "gotoFire");
		Log_SetStringToLog(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_4", "Logs.txt", "#space#", " "));
		pchar.questTemp.Teno = "takeFire";
	}
	//-----------------------------------------
	if (_itemId == "Totem_12") //открываем каменный сундук в большом храме (с кинжалом)
	{
		DeleteAttribute(_location, "private1.closed");
		Log_SetStringToLog(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_5", "Logs.txt", "#space#", " "));
	}
	//-----------------------------------------
	if (_itemId == "Totem_13") //снимаем огонь 2х
	{
		_location.lockFire.button02.active = true;
		if (CheckAttribute(_location, "lockFire.button02.active") && CheckAttribute(_location, "lockFire.button03.active"))
		{
			DeleteAttribute(_location, "gotoFire");
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_6", "Logs.txt", "#space#", " "));
			pchar.questTemp.Teno = "takeFire";
		}
	}
	if (_itemId == "Totem_14") //снимаем огонь 2х
	{
		_location.lockFire.button03.active = true;
		if (CheckAttribute(_location, "lockFire.button02.active") && CheckAttribute(_location, "lockFire.button03.active"))
		{
			DeleteAttribute(_location, "gotoFire");
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_7", "Logs.txt", "#space#", " "));
			pchar.questTemp.Teno = "takeFire";
		}
	}
	//-----------------------------------------
	if (_itemId == "Totem_15") //открываем каменный сундук в большом храме
	{
		DeleteAttribute(_location, "private2.closed");
		Log_SetStringToLog(GetConvertStrWithReplace("Variable_LSC_Q2Utilite_8", "Logs.txt", "#space#", " "));
	}
	//-----------------------------------------
	if (_itemId == "Totem_1" || _itemId == "Totem_2" || _itemId == "Totem_3" || _itemId == "Totem_4" || _itemId == "Totem_5" ||
		_itemId == "Totem_6" || _itemId == "Totem_7" || _itemId == "Totem_8" || _itemId == "Totem_9" || _itemId == "Totem_10")
	{
		int n;
		int num = 0;
		int locIndex = sti(_location.idxTeno); //индекс Теночтитлана
		string sTemp;
		_location.openGreatTemple = true;
		for (int i=1 ; i<=10; i++)
		{
			sTemp = "idx" + i;
			n = sti(locations[locIndex].temples.(sTemp));
			if (CheckAttribute(locations[n], "openGreatTemple")) num++;
		}
		if (num >= 10)
		{
			DeleteAttribute(&locations[locIndex], "reload.l32.disable");
			DeleteAttribute(&locations[locIndex], "reload.l33.disable");
			DeleteAttribute(&locations[locIndex], "reload.l34.disable");
			AddQuestRecord("Tenochtitlan", "7");
			pchar.questTemp.Teno = "takeSkull";
		}
	}
}

//бог мертвых разгневан
void LoginDeadmansGod()
{
	chrDisableReloadToLocation = true;
	LAi_group_SetRelation("teno_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//ставим бога мертвых
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) ref sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod", "mictlantecuhtli", "skeleton", "man_fast", 100, PIRATE, 0, true));
	else sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod", "mictlantecuhtli", "skeleton", "man", 100, PIRATE, 0, true));
    FantomMakeCoolFighter(sld, 100, 100, 100, "toporAZ", "pistol5", 3000);
	//LAi_SetDltHealth(sld, 3.0);
	sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_12", "Names.txt", "#space#", " ");
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Mictlantecuhtli.c";
	sld.dialog.currentnode   = "InGreateTemple";
	if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
	ChangeCharacterAddressGroup(sld, "Temple_great", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_ActorDialog(sld, pchar, "", 0.0, 0);
	LAi_CharacterPlaySound(sld, "DeadmansGod");
}

void TenoRoundTempleChestOpen()
{
	ref sld;
	if (pchar.questTemp.Teno != "YouWinGod")
	{
		// Если квест Тено не закончен, генерируем охрану револьвера
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = true;
		for (i=1; i<=8; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("AztecWarrior_"+i, "AztecWarrior"+(rand(4)+1), "skeleton", "man", 30, PIRATE, 0, true));
			FantomMakeCoolFighter(sld, 30, 90, 90, "toporAZ", "", 100);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		}
	}
	else
	{
		if (!CheckAttribute(PChar, "questTemp.Uicilopochtli"))
		{
			sld = GetCharacter(GetCharacterIndex("Uicilopochtli"));
			ChangeCharacterAddressGroup(sld, "Temple_round", "goto", "goto1");
			LAi_ActorDialog(sld, pchar, "", 0.0, 0);

			PChar.questTemp.Uicilopochtli = 0;
		}
	}
}

void LoginDeadmansGod2()
{
	if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) ref sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod2", "mictlantumsamil", "skeleton", "man_fast", 60, PIRATE, 0, true)); // LEO: Превозмогаторам - страдать 01.12.2021
	else sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod2", "mictlantumsamil", "skeleton", "man", 60, PIRATE, 0, true));
    FantomMakeCoolFighter(sld, 60, 100, 100, "blade48", "", 2500);
	//LAi_SetDltHealth(sld, 3.0);
	sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_13", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_14", "Names.txt", "#space#", " ");
	sld.vampire = true;
	sld.SaveItemsForDead = true;
	if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
	ChangeCharacterAddressGroup(sld, "treasure_alcove", "goto", "goto3");
	LAi_CharacterPlaySound(sld, "DeadmansGod");
	LAi_group_MoveCharacter(sld, "evil");
	LAi_group_SetRelation("evil", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("evil", LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(sld, true);
	LAi_SetCheckMinHP(sld, 5.0, true, "UmSamilDefeated");
}

void LoginUmSamilGuards()
{
	chrDisableReloadToLocation = true;
	for(int i = 0; i < 3; i++)
	{
		if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) ref sld = GetCharacter(NPC_GenerateCharacter("UmSamilGuard"+i, "Chavinavi_1", "skeleton", "man_fast", 55, PIRATE, 0, true)); // LEO: Превозмогаторам - страдать 01.12.2021
		else sld = GetCharacter(NPC_GenerateCharacter("UmSamilGuard"+i, "Chavinavi_1", "skeleton", "man", 55, PIRATE, 0, true));
		if (i == 0) FantomMakeCoolFighter(sld, 55, 90, 90, "blade05", "", 750);
		if (i == 1) FantomMakeCoolFighter(sld, 55, 90, 90, "blade31", "", 750);
		if (i == 2) FantomMakeCoolFighter(sld, 55, 90, 90, "blade01", "", 750);
		sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_15", "Names.txt", "#space#", " ");
		sld.lastname = "";
		sld.vampire = true;
		if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
		if (i == 0) ChangeCharacterAddressGroup(sld, "treasure_alcove", "goto", "monster1");
		if (i == 1) ChangeCharacterAddressGroup(sld, "treasure_alcove", "goto", "monster4");
		if (i == 2) ChangeCharacterAddressGroup(sld, "treasure_alcove", "goto", "monster3");
		LAi_group_MoveCharacter(sld, "evil_");
		LAi_group_SetRelation("evil_", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("evil_", LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(sld, true);
	}
	LAi_group_SetCheck("evil_", "UmSamilGuardsDefeated");
}

void SpawnFishHeads()
{
	int stopp = 0;
	//chrDisableReloadToLocation = true;
	for(int i = 0; i < 36; i++)
	{
		if (stopp == 1) {stopp = 0; continue;}
		ref sld = GetCharacter(NPC_GenerateCharacter("FishHead"+i, GetRandSkelModel(), "skeleton", "man", 55, PIRATE, 0, true));
		FantomMakeCoolFighter(sld, 25, 90, 90, "blade01", "", 300);
		sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_16", "Names.txt", "#space#", " ");
		sld.lastname = "";
		ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster"+i);
		LAi_group_MoveCharacter(sld, "evilf_");
		LAi_group_SetRelation("evilf_", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("evilf_", LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(sld, true);
		sld.lifeDay = 0;
		stopp = 1;
	}
	LAi_group_SetCheck("evilf_", "FishHeadsDefeated");
}

void SpawnGreedyBastards()
{
	chrDisableReloadToLocation = true;
	int iCount = makeint(MOD_SKILL_ENEMY_RATE*3/2+0.5);
	if (sti(pchar.rank) < 3 && iCount > 2) iCount = 1; //казуалам не набьют ебало сразу
	if (iCount<1) iCount = 1;
	for(int i = 0; i < iCount; i++)
	{
		ref sld = GetCharacter(NPC_GenerateCharacter("GreedyBastard_"+pchar.location+"_"+i, "panhandler_"+(rand(4)+1), "man", "man", 5+makeint(sti(pchar.rank)/3), PIRATE, 0, true));
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_group_Delete("greedybastard");
		LAi_group_MoveCharacter(sld, "greedybastard");

		if (i!=0)
		{
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		else
		{
			sld.quant = iCount;
			switch (rand(14))
			{
				case 0: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_17", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_18", "Names.txt", "#space#", " "); break;
				case 1: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_19", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_20", "Names.txt", "#space#", " "); break;
				case 2: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_21", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_22", "Names.txt", "#space#", " "); break;
				case 3: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_23", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_24", "Names.txt", "#space#", " "); break;
				case 4: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_25", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_26", "Names.txt", "#space#", " "); break;
				case 5: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_27", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_28", "Names.txt", "#space#", " "); break;
				case 6: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_29", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_30", "Names.txt", "#space#", " "); break;
				case 7: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_31", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_32", "Names.txt", "#space#", " "); break;
				case 8: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_33", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_34", "Names.txt", "#space#", " "); break;
				case 9: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_35", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_36", "Names.txt", "#space#", " "); break;
				case 10: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_37", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_38", "Names.txt", "#space#", " "); break;
				case 11: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_39", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_40", "Names.txt", "#space#", " "); break;
				case 12: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_41", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_42", "Names.txt", "#space#", " "); break;
				case 13: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_43", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_44", "Names.txt", "#space#", " "); break;
				case 14: sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_45", "Names.txt", "#space#", " "); sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_46", "Names.txt", "#space#", " "); break;
			}
			LAi_SetActorTypeNoGroup(sld);
			sld.dialog.filename = "GenQuests_dialog.c";
			sld.dialog.currentnode = "Greedy";
			LAi_ActorDialog(sld, pchar, "", 10.0, 0);
		}
	}
	LAi_group_SetCheck("greedybastard", "OpenTheDoors");
}

//проверка на наличие тотемов в ГГ и их использование ранее
bool CheckMainHeroTotem(string itemName)
{
    if( CheckAttribute(pchar,"Items."+itemName) && sti(pchar.Items.(itemName))>0 )
	{
		return true;
	}
	else
	{
		for (int i=Totems_start; i<Totems_end; i++)
		{
			if (Items[i].id == itemName)
			{
				if (CheckAttribute(&Items[i], "shown.used"))
				{
					return true;
				}
				break;
			}
		}
	}
	return false;
}

// --> ugeen 20.06.09 - проверка на наличие карт у ГГ
bool CheckMainHeroMap(string itemName)
{
    if( CheckAttribute(pchar,"Items."+itemName) && sti(pchar.Items.(itemName))>0 )
	{
		return true;
	}
	return false;
}

// Инициализация прочих квестов. Warship
void OtherQuestCharactersInit()
{
	ref sld;

	// Квест "Помощь Андрэ Абелю"
	/*sld = GetCharacter(NPC_GenerateCharacter("Andre_Abel" , "officer_19", "man", "man", 10, FRANCE, -1, true));
	FantomMakeCoolFighter(sld, 10, 30, 35, "blade14", "pistol2", 10);
	FantomMakeCoolSailor(sld, SHIP_FLEUT, "", CANNON_TYPE_CANNON_LBS16, 30, 30, 30);
	sld.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_47", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_48", "Names.txt", "#space#", " ");
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; // не убирать труп через 200с
	sld.dialog.FileName = "Quest\Andre_Abel_Dialog.c";
	sld.greeting = "cit_quest";
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);	// До поры нельзя убить
	SetCharacterGoods(sld, GOOD_SILK, 700);
	SetCharacterGoods(sld, GOOD_TOBACCO, 500);
	ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");*/
}

// Warship 07.07.09 Пасхалка - бригантина "Мэри Селест"
void MaryCelesteInit()
{
	ref character, realShip;
	String capID = "MaryCelesteCapitan";
	String seaGroup = "MaryCelesteGroup";
	int good;

	// Сцуко.. В функции низя делать как generableGoods[15] = { GOOD_FOOD, GOOD_WEAPON, ... }; - даёт ошибку
	// Если вынести из функции, то все норм
	/*int generableGoods[15] = { GOOD_FOOD, GOOD_WEAPON, GOOD_MAHOGANY, GOOD_MEDICAMENT, GOOD_SILK,
		GOOD_SANDAL, GOOD_COFFEE, GOOD_CLOTHES, GOOD_EBONY, GOOD_TOBACCO,
		GOOD_CHOCOLATE, GOOD_WINE, GOOD_RUM, GOOD_CINNAMON, GOOD_LEATHER };*/

	int generableGoods[15];

	generableGoods[0] = GOOD_FOOD;
	generableGoods[1] = GOOD_WEAPON;
	generableGoods[2] = GOOD_MAHOGANY;
	generableGoods[3] = GOOD_MEDICAMENT;
	generableGoods[4] = GOOD_SILK;
	generableGoods[5] = GOOD_SANDAL;
	generableGoods[6] = GOOD_COFFEE;
	generableGoods[7] = GOOD_CLOTHES;
	generableGoods[8] = GOOD_EBONY;
	generableGoods[9] = GOOD_TOBACCO;
	generableGoods[10] = GOOD_CHOCOLATE;
	generableGoods[11] = GOOD_WINE;
	generableGoods[12] = GOOD_RUM;
	generableGoods[13] = GOOD_CINNAMON;
	generableGoods[14] = GOOD_LEATHER;

	character = GetCharacter(NPC_GenerateCharacter(capID , "Pirate_5", "man", "man", 50, ENGLAND, -1, true));
//	FantomMakeCoolFighter(character, 50, 50, 45, "blade34", "pistol5", 50);
	FantomMakeCoolSailor(character, SHIP_BRIGANTINE, GetConvertStr("Variable_LSC_Q2Utilite_1", "ShipNames.txt"), CANNON_TYPE_CANNON_LBS24, 50, 50, 50);
	character.name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_49", "Names.txt", "#space#", " ");
	character.lastname = "";
	character.mapEnc.type = "trade";
	character.mapEnc.Name = GetConvertStrWithReplace("Variable_LSC_Q2Utilite_50", "Names.txt", "#space#", " ");
	LAi_SetImmortal(character, true);
	SetCharacterGoods(character, GOOD_RUM, 700);
	Character_SetAbordageEnable(character, false); // Низя абордировать

	SetCrewQuantity(character, 0); // Никого живого

	realShip = GetRealShip(GetCharacterShipType(character));

	PChar.QuestTemp.MaryCeleste = "NotFind";
	PChar.QuestTemp.MaryCeleste.TurnRate = realShip.TurnRate; // Запомним, потом восстановим для интерфейса

	realShip.lowpolycrew = 0; // Нету никого на палубе
	realShip.TurnRate = 1; // Чтоб не особо изворотливым был
	realShip.capacity = 2820;

	NullCharacterGoods(character); // Нулим товары в трюме

	AddCharacterGoodsSimple(character, GOOD_BALLS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_GRAPES, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_KNIPPELS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_BOMBS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_POWDER, 500 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_FOOD, 50 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_WEAPON, 20 + rand(30));
	AddCharacterGoodsSimple(character, GOOD_MEDICAMENT, 10 + rand(20));
	AddCharacterGoodsSimple(character, GOOD_SAILCLOTH, 50 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_PLANKS, 20 + rand(30));

	good = generableGoods[rand(14)];
	// GetCharacterFreeSpace(ref _refCharacter,int _Goods) - вернёт сколько можно положить данного товара в трюм персонажу
	AddCharacterGoodsSimple(character, good, GetCharacterFreeSpace(character, good) - 1);

	character.AlwaysFriend = true; // Друзья навек
	character.ShipEnemyDisable = true; // Флаг не обижаться на выстрелы
	character.CanDropSails = false; // Низя спускать паруса

	Group_FindOrCreateGroup(seaGroup);
	Group_SetTaskAttackInMap(seaGroup, PLAYER_GROUP);
	Group_LockTask(seaGroup);
	Group_AddCharacter(seaGroup, capID);
	Group_SetGroupCommander(seaGroup, capID);
	SetRandGeraldSail(character, ENGLAND);

	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придет
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));

	Map_CreateTrader(character.fromShore, character.toShore, capID, GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)));

	trace("Бригантина Мэри Селест вышла из " + character.fromCity + " и направилась в " + character.toShore);
}
void MayorQuestCounter()
{
	for(int i = 0; i<4; i++)
	{
		string sNationname = GetNationNameByType(i);
		pchar.(sNationname).quest.mayor = 0;
		pchar.(sNationname).quest.mayor.done = false;
	}
}
		
