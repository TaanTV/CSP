
int CreateStoryCharacters(int n)
{
    ref ch;
    ///////////////////////////////////
    makeref(ch,Characters[n]);		// ГУБЕРНАТОР Англия
	ch.name 	= GetConvertStr("Variable_StoryCharacters_0.1", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_StoryCharacters_1", "Names.txt", "#space#", " ");
	ch.id		= "eng_guber";
	ch.model	= "Modyford";
	ch.model.animation	= "man";
	ch.sex = "man";
	ch.location	= "PortRoyal_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Governor.c";
	ch.nation = ENGLAND;
	ch.rank 	= 10;
	LAi_NoRebirthEnable(ch);
	LAi_RemoveLoginTime(ch);
	LAi_SetHuberStayType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetHP(ch, 100.0, 100.0);
	LAi_SetImmortal(ch, true);
	ch.greeting = "Gr_Hovernor";
//	ch.notQuestLine = true; //флаг не давать задания по линейке
	n = n + 1;

	makeref(ch,Characters[n]);		// ГУБЕРНАТОР Испания
	ch.name 	= GetConvertStr("Variable_StoryCharacters_0.2", "Names.txt");
	//ch.middlename = "";
	ch.lastname = GetConvertStrWithReplace("Variable_StoryCharacters_2", "Names.txt", "#space#", " ");
	ch.id		= "spa_guber";
	ch.model	= "Gaskon";
	ch.model.animation	= "man";
	ch.sex = "man";
	ch.location	= "Muelle_Residence";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Governor.c";
	ch.nation = SPAIN;
	ch.rank 	= 10;
	LAi_NoRebirthEnable(ch);
	LAi_RemoveLoginTime(ch);
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetHP(ch, 100.0, 100.0);
	LAi_SetImmortal(ch, true);
	ch.greeting = "Gr_Hovernor";
	n = n + 1;

	makeref(ch,Characters[n]);		// ГУБЕРНАТОР Франция
	ch.name 	= GetConvertStr("Variable_StoryCharacters_0.3", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_StoryCharacters_3", "Names.txt", "#space#", " ");
	ch.id		= "fra_guber";
	ch.model	= "dOgeron";
	ch.sex = "man";
	ch.location	= "Tortuga_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Governor.c";
	ch.nation = FRANCE;
	ch.rank 	= 10;
	LAi_NoRebirthEnable(ch);
	LAi_RemoveLoginTime(ch);
	LAi_SetHuberStayType(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	LAi_SetHP(ch, 100.0, 100.0);
	LAi_SetImmortal(ch, true);
	ch.greeting = "Gr_Hovernor";
	n = n + 1;

	makeref(ch,Characters[n]);		// ГУБЕРНАТОР Голландия
	ch.name 	= GetConvertStr("Variable_StoryCharacters_0.4", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_StoryCharacters_4", "Names.txt", "#space#", " ");
	ch.id		= "hol_guber";
	ch.model	= "stuvesant";
	ch.sex = "man";
	ch.location	= "Villemstad_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Governor.c";
	ch.nation = HOLLAND;
	ch.rank 	= 10;
	LAi_NoRebirthEnable(ch);
	LAi_RemoveLoginTime(ch);
	LAi_SetHuberStayType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetHP(ch, 100.0, 100.0);
	LAi_SetImmortal(ch, true);
	ch.greeting = "Gr_Hovernor";
	ch.notMoveAble = true; //не переезжать
	n = n + 1;

//============== Генри Морган! Всем трепетать. =================
    makeref(ch,Characters[n]);
	ch.name 	= GetConvertStr("Variable_StoryCharacters_0.5", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_StoryCharacters_5", "Names.txt", "#space#", " ");
	ch.id		= "Henry Morgan";
	ch.model	= "Morgan";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.location	= "PortRoyal_houseS1";
	ch.location.group = "sit";
	ch.location.locator = "sit2";
	ch.Dialog.Filename = "Quest\Morgan.c";
	ch.nation = PIRATE;
	GiveItem2Character(ch, GUN_COMMON);
	ch.equip.gun = GUN_COMMON;
	GiveItem2Character(ch, "blade27");// сабля Моргана
	ch.equip.blade = "blade27";
	// ==> Кораблик Моргану делаем с хорошими пушками
	ch.Abordage.Enable = false; // НЕЛЬЗЯ!
	ch.Ship.Name = "Elisabett";
	ch.Ship.Type = GenerateShipExt(SHIP_FRIGATE, true, ch);
	ch.Ship.Stopped = true;
   	ch.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS48;
    SetCrewQuantityFull(ch);
    Fantom_SetBalls(ch, "pirate");
    ch.rank = 45;
    SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
    SetShipSkill(ch, 100, 10, 100, 100, 90, 60, 80, 90, 50);
	ch.money = "50000";
	SetCharacterPerk(ch, "FastReload");
	SetCharacterPerk(ch, "HullDamageUp");
	SetCharacterPerk(ch, "SailsDamageUp");
	SetCharacterPerk(ch, "CrewDamageUp");
	SetCharacterPerk(ch, "CriticalShoot");
	SetCharacterPerk(ch, "LongRangeShoot");
	SetCharacterPerk(ch, "CannonProfessional");
	SetCharacterPerk(ch, "ShipDefenseProfessional");
	SetCharacterPerk(ch, "ShipSpeedUp");
	SetCharacterPerk(ch, "ShipTurnRateUp");
	SetCharacterPerk(ch, "SwordplayProfessional");
	SetCharacterPerk(ch, "AdvancedDefense");
	SetCharacterPerk(ch, "CriticalHit");
	SetCharacterPerk(ch, "Sliding");
	LAi_NoRebirthDisable(ch);
	LAi_RebirthOldName(ch);
	LAi_SetHuberType(ch);
	ch.standUp = true; //вставать и нападать на врага
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetImmortal(ch, true);
	LAi_SetHP(ch, 230.0, 230.0);
	ch.greeting = "Gr_Morgan";
	n = n + 1;

//============== Секретать Моргана, можно расслабиться. =================
	makeref(ch,Characters[n]);
	ch.name 	= GetConvertStr("Variable_StoryCharacters_0.6", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_StoryCharacters_6", "Names.txt", "#space#", " ");
	ch.id		= "Oliver_Green";
	ch.model	= "Helper";
	ch.sex = "man";
    ch.model.animation = "man";
	ch.location	= "PortRoyal_houseS1";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Quest\OliverGreen.c";
    SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
    SetShipSkill(ch, 100, 10, 100, 100, 90, 60, 80, 90, 50);
	ch.greeting = "Gr_OliverGreen";
	ch.nation = PIRATE;
	ch.rank 	= 20;
	LAi_NoRebirthDisable(ch);
	LAi_RemoveLoginTime(ch);
	LAi_SetHuberType(ch);
	//ch.standUp = true; //вставать и нападать на врага
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetHP(ch, 100.0, 100.0);
	n=n+1;

    //............................. квест Изабеллы ...........................................
	makeref(ch,Characters[n]);		// Любовь понимашь...
	ch.name 	= GetConvertStr("Variable_StoryCharacters_0.7", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_StoryCharacters_7", "Names.txt", "#space#", " ");
	ch.id		= "Isabella";
	ch.model	= "liza";
	ch.sex = "woman";
    ch.model.animation = "towngirl";
	ch.location	= "SanJuan_houseS1Bedroom";
	ch.location.group = "goto";
	ch.location.locator = "goto4";
	ch.Dialog.Filename = "Quest\Isabella\Isabella.c";
	ch.nation = SPAIN;
	ch.rank 	= 8;
	ch.DontClearDead = true;  // не убирать труп
	ch.money = "10000";
    LAi_NoRebirthEnable(ch);
	LAi_SetStayType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 75.0, 75.0);
//	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	ch.greeting = "Isabella";
	n = n + 1;

	//////////////////=====>>>> Магический квест Аскольда.
    makeref(ch,Characters[n]);		// Аскольд
	ch.name 	= GetConvertStr("Variable_StoryCharacters_0.8", "Names.txt");
	ch.lastname = "";
	ch.id		= "Ascold";
	ch.model	= "PGG_Moscovit";
	ch.model.animation = "Moscovit";
	ch.sex = "man";
	ch.location	= "BasTer_houseSp1";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Quest\Ascold.c";
	ch.nation = PIRATE;
    ch.rank 	= 38;
	ch.reputation = "15";
    SetSelfSkill(ch, 90, 90, 90, 70, 90);
    SetShipSkill(ch, 20, 90, 10, 10, 10, 20, 10, 10, 50);
    LAi_NoRebirthDisable(ch);  // воскресть при убиении
	LAi_SetSitType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 200.0, 200.0);
	LAi_SetImmortal(ch, true);
	ch.greeting = "Gr_Ascold";
	n = n+1;

//============== Капитан Шарп =================
    makeref(ch,Characters[n]);
	ch.name 	= GetConvertStr("Variable_StoryCharacters_0.9", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_StoryCharacters_8", "Names.txt", "#space#", " ");
	ch.id		= "Sharp";
	ch.model	= "Sharp";
	ch.sex = "man";
	ch.location	= "none";
	ch.location.group = "";
	ch.location.locator = "";
	ch.Dialog.Filename = "Quest\ForAll_dialog.c";
	ch.Dialog.CurrentNode = "CitySharp"; //нода суша
	ch.DeckDialogNode = "DeckSharp"; //нода палуба
	ch.nation = PIRATE;
	GiveItem2Character(ch, GUN_COMMON);
	ch.equip.gun = GUN_COMMON;
	GiveItem2Character(ch, "blade25");
	ch.equip.blade = "blade25";
	LAi_SetHP(ch, 200.0, 200.0);
	// ==> Кораблик
	ch.Ship.Name = GetConvertStrWithReplace("Variable_StoryCharacters_9", "Names.txt", "#space#", " ");
	ch.Ship.Type = GenerateShipTop(SHIP_BRIGQUEEN, true, ch);
	ch.Ship.Stopped = true;
   	ch.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
	ch.Ship.Mode = "Pirate";
	SetCrewQuantityFull(ch);
    Fantom_SetBalls(ch, "pirate");
	SetRandGeraldSail(ch, sti(ch.Nation));
    ch.rank = 20;
    SetRandSPECIAL(ch);
    SetSelfSkill(ch, 60, 60, 60, 60, 60);
    SetShipSkill(ch, 70, 70, 70, 70, 60, 60, 30, 60, 50);
	ch.money = "1120";
	ch.AlwaysSandbankManeuver = true;
	ch.BreakTmplAndFight = true; //актеру. если атакован, то прервать темплейт и стать warrior
	SetCharacterPerk(ch, "FastReload");
	SetCharacterPerk(ch, "HullDamageUp");
	SetCharacterPerk(ch, "SailsDamageUp");
	SetCharacterPerk(ch, "CrewDamageUp");
	SetCharacterPerk(ch, "CriticalShoot");
	SetCharacterPerk(ch, "LongRangeShoot");
	SetCharacterPerk(ch, "CannonProfessional");
	SetCharacterPerk(ch, "ShipDefenseProfessional");
	SetCharacterPerk(ch, "ShipSpeedUp");
	SetCharacterPerk(ch, "ShipTurnRateUp");
	SetCharacterPerk(ch, "SwordplayProfessional");
	SetCharacterPerk(ch, "AdvancedDefense");
	SetCharacterPerk(ch, "CriticalHit");
	SetCharacterPerk(ch, "Sliding");
	LAi_SetStayType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	ch.greeting = "Gr_MiddPirate";
	LAi_group_MoveCharacter(ch, LAI_GROUP_PLAYER_OWN);
	n = n + 1;

	makeref(ch,Characters[n]);			// Билетёр :)
	ch.id = "ArenaBileter";
	ch.model	= "trader_9";
	ch.sex 		= "man";
	ch.City 	= "";
	ch.location	= "none";
	ch.location.group = "";
	ch.location.locator = "";
	ch.Dialog.Filename = "ArenaBileter_dialog.c";
	ch.Dialog.CurrentNode = "First Time";
	ch.greeting = "Gr_ArenaBileter";
	ch.nation = PIRATE;
	ch.quest.type = "";
	//ch.watchBoxes = true;
	SetRandSPECIAL(ch);
    	SetSelfSkill(ch, 30, 30, 70, 50, 30);
    	SetShipSkill(ch, 30, 50, 30, 30, 40, 70, 30, 25, 70)
	ch.standUp = true;
	LAi_SetStayType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "FENCING_TOWN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

    makeref(ch,Characters[n]);
	ch.name = GetConvertStrWithReplace("Variable_StoryCharacters_10", "Names.txt", "#space#", " ");
	ch.lastname = "";
	ch.id = "Uicilopochtli";
	ch.model = "Uchilopochi";
	ch.sex = "skeleton";
	ch.location	= "none";
	ch.location.group = "";
	ch.location.locator = "";
	ch.Dialog.Filename = "Quest\Mictlantecuhtli.c";
	ch.Dialog.CurrentNode = "Uicilopochtli_F_0";
	ch.nation = PIRATE;
	GiveItem2Character(ch, "topor_01");
	ch.equip.gun = "topor_01";
	GiveItem2Character(ch, "pistol7");
	ch.equip.blade = "pistol7";
    ch.rank = 300;
	SetSPECIAL(ch, 10,10,10,10,10,10,10);
    SetSelfSkill(ch, 100, 100, 100, 100, 100);
    SetShipSkill(ch, 100, 100, 100, 100, 100, 100, 100, 100, 100);
	ch.money = "666";
	LAi_SetImmortal(ch, true);
	LAi_SetActorType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_group_MoveCharacter(ch, "AztecCitizenGroup");
	n = n + 1;

	return n;
}