
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Анжелика Тич
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void AnjelikaTich_StartGame(string qName)
{
	SetQuestsCharacters();
	bDisableLandEncounters = true;
	bDisableFastReload = true;
	bDisableCharacterMenu = true;
	pchar.Cirgnore = true;
	pchar.GenQuest.CannotWait = true;
	SetCaptureTownByNation("LaVega", SPAIN);
	pchar.questTemp.AnjelikaTichPrologue = "ATP";
	pchar.questTemp.AnjelikaTichPrologue5 = true;
	pchar.questTemp.AnjelikaTichPrologue7_Jackman = true;
	pchar.questTemp.AnjelikaTichPrologue8_Gudli = "ATP8";
	pchar.questTemp.AnjelikaTichPrologue9_BlackBeard = "ATP9";
	pchar.questTemp.AnjelikaTichPrologue10 = true;		//На всякий случай (нигде не задействовано)
	LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload1_back", true);
	LocatorReloadEnterDisable("PortPax_ExitTown", "reload3", true);
	LocatorReloadEnterDisable("LaVega_town", "reload4_back", true);
	
	DeleteAttribute(Pchar, "ship");
	DeleteAttribute(Pchar, "ShipSails.gerald_name");
	Pchar.ship.type = SHIP_NOTUSED;
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_Rebekka", "RebekkaRemedios", "woman", "YokoDias", 10, SPAIN, -1, false));
	sld.name	= GetConvertStr("Variable_Angelika_Tich_Line_1", "Names.txt");
	sld.lastname	= GetConvertStr("Variable_Angelika_Tich_Line_2", "Names.txt");
	sld.Dialog.Filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
	LAi_SetActorType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_MH12","goto","goto8");

	RemoveAllCharacterItems(pchar, true);
	DeleteAttribute(pchar, "items");
	GiveItem2Character(pchar, "blade9");
	EquipCharacterbyItem(pchar, "blade9");
	GiveItem2Character(pchar, "suit_2");
	EquipCharacterbyItem(pchar, "suit_2");
	TakeNItems(pchar, "potion1", 3);
	AddMoneyToCharacter(PChar, 500);
	pchar.GenQuestBox.LaVega_MH12.box4.items.map_hisp = 1;
	pchar.GenQuestBox.LaVega_MH12.box4.items.jewelry7 = 1;
	pchar.GenQuestBox.LaVega_MH12.box4.items.mineral8 = 2;
	pchar.GenQuestBox.LaVega_MH12.box4.items.jewelry2 = 5;
	
	LAi_SetActorType(pchar);
	DoQuestFunctionDelay("AnjelikaTich_Razgovor_1", 2.0);
	DoQuestFunctionDelay("AnjelikaTich_SprInt", 0.1);
	StartQuestMovie(true, false, true);
	
	pchar.quest.AT_PZD_Quest.win_condition.l1 = "Rank";
	pchar.quest.AT_PZD_Quest.win_condition.l1.value = 3;
	pchar.quest.AT_PZD_Quest.win_condition.l1.operation = ">=";
	PChar.quest.AT_PZD_Quest.win_condition = "AT_PZD_Quest";
	
	if (bQuestsRank)	//Если стоит галочка, то убрать требования рангов у квестов
	{
		DoQuestFunctionDelay("UbratTrebovanieRangov", 0.1);
	}
}
void AnjelikaTich_SprInt(string qName)
{
	ChangeShowIntarface();
}
void AnjelikaTich_Razgovor_1(string qName)
{
	LAi_ActorGoToLocator(pchar, "barmen", "stay", "", -1);
	DoQuestFunctionDelay("AnjelikaTich_Razgovor_2", 2.0);
}
void AnjelikaTich_Razgovor_2(string qName)
{
	LAi_SetPlayerType(pchar);
	
	sld = CharacterFromID("AT_pr_Rebekka")
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
void At_pr_Rebekka_gulyat(string qName)
{
	sld = CharacterFromID("AT_pr_Rebekka")
	LAi_SetCitizenType(sld);
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	
	DoQuestFunctionDelay("AnjelikaTich_UbiraemNPC_Gener", 0.5);	
}
void AnjelikaTich_UbiraemNPC_Gener(string qName)
{
	//Убираем персонажа, который мешает
	sld = CharacterFromID("Gasten_Kotes")
	int characterIndex = LAi_FindNearestVisCharacter(sld, 25);
	ref characterRef;

	if(characterIndex != -1)
	{
		characterRef = &Characters[characterIndex];

		if(!LAi_IsImmortal(characterRef)) // Квестовые
		{
			ChangeCharacterAddressGroup(characterRef, "none", "", "");
			LAi_KillCharacter(characterRef);
		}
	}
}
void AT_pr_Torgovets_6_2(string qName)
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("Gasten_Kotes")
	//LAi_SetActorType(sld);
	sld.dialog.filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
	sld.dialog.currentnode = "Torgovets_6_3";
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	
	sld = CharacterFromID("AT_pr_devushka_na_rynke")
	UnmarkCharacter(sld);
}
void AT_pr_Torgovets_10_1(string qName)
{
	EndQuestMovie();
	locCameraSleep(false);
	LAi_SetPlayerType(pchar);
	
	sld = CharacterFromID("AT_pr_Rebekka")
	LAi_SetCitizenType(sld);
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	
}
void AT_pr_Draka_s_Kotesom(string qName)
{
	sld = CharacterFromID("Gasten_Kotes")
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, false);
	LAi_SetCheckMinHP(sld, 1, true, "Draka_s_Kotesom_Pobeda");
	ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "enc04", "enc04_04");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "");
	
	chrDisableReloadToLocation = true;
}
void AT_pr_Oba_ischezaut(string qName)
{
	sld = CharacterFromID("Gasten_Kotes")
	ChangeCharacterAddressGroup(sld,"none","","");
	sld = CharacterFromID("AT_pr_Rebekka")
	ChangeCharacterAddressGroup(sld,"none","","");
}
void AT_MS_PodskazkaGrot(string qName)
{
	AddQuestRecord("AT_Mechty_Sbivautsya", "1.1");
	Log_info(GetConvertStrWithReplace("Variable_angelika_tich_line_functions_1", "Logs.txt", "#space#", " "));
}
void AT_pr_Grot(string qName)
{
	StartQuestMovie(true, true, true);
	DoQuestFunctionDelay("AT_pr_Grot_1_1", 0.1);
	DoQuestFunctionDelay("AT_pr_Grot_2", 0.4);
	LAi_SetActorType(pchar);
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("AT_pr_Rebekka")
	ChangeCharacterAddressGroup(sld, "Hispaniola_Grot", "goto", "goto4");
}
void AT_pr_Grot_1_1(string qName)
{
	ChangeShowIntarface();
}
void AT_pr_Grot_2(string qName)
{
	LAi_ActorGoToLocator(pchar, "goto", "goto5", "", -1);
	DoQuestFunctionDelay("AT_pr_Grot_3", 5.5);
}
void AT_pr_Grot_3(string qName)
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("AT_pr_Rebekka")
	sld.dialog.filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
	sld.dialog.currentnode = "Rebekka_v_grote_1";
	//LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}
void AT_pr_Strelba_is_pushki(string qName)
{
	PlaySound("CSR\GUNSFIRE\Cannon_36_1.wav");
	DoQuestFunctionDelay("AT_pr_Strelba_is_pushki_2", 1.4);
}
void AT_pr_Strelba_is_pushki_2(string qName)
{
	PlaySound("CSR\GUNSFIRE\Cannon_24_3.wav");
	DoQuestFunctionDelay("AT_pr_Strelba_is_pushki_3", 1.0);
}
void AT_pr_Strelba_is_pushki_3(string qName)
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("AT_pr_Rebekka")
	sld.dialog.filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
	sld.dialog.currentnode = "Rebekka_v_grote_8";
	//LAi_ActorDialog(sld, pchar, "", 0.0, 0);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}
void AT_pr_Strelba_is_pushki_4(string qName)
{
	PlaySound("CSR\GUNSFIRE\Fort_cannon_02.wav");
	DoQuestFunctionDelay("AT_pr_Strelba_is_pushki_5", 1.4);
}
void AT_pr_Strelba_is_pushki_5(string qName)
{
	PlaySound("CSR\GUNSFIRE\Fort_cannon_03.wav");
	DoQuestFunctionDelay("AT_pr_Strelba_is_pushki_5_5", 1.4);
}
void AT_pr_Strelba_is_pushki_5_5(string qName)
{
	PlaySound("CSR\GUNSFIRE\Fort_cannon_04.wav");
	DoQuestFunctionDelay("AT_pr_Strelba_is_pushki_6", 1.0);
}
void AT_pr_Strelba_is_pushki_6(string qName)
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("AT_pr_Rebekka")
	sld.dialog.filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
	sld.dialog.currentnode = "Rebekka_v_grote_11";
	//LAi_ActorDialog(sld, pchar, "", 0.0, 0);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}
void AT_pr_Piraty_v_grote(string qName)
{
	TavernWaitDate("wait_day");		//Sinistra Делаем день, чтобы в пещере было светло.
	WaitDate("", 0, 0, 0, 14, 40);	//Крутим время до ночи, чтобы когда вышли из пещеры, была ночь.
	locCameraTarget(PChar)
	locCameraFollow();
	DoQuestReloadToLocation("Hispaniola_Grot", "goto", "goto4", "AT_pr_Piraty_v_grote_1");
}
void AT_pr_Piraty_v_grote_1_1(string qName)
{
	ChangeShowIntarface();
}
void AT_pr_Piraty_v_grote_2(string qName)
{
	sld = CharacterFromID("AT_pr_Piraty_1")
	LAi_ActorDialog(sld, pchar, "", 2.3, 0);
	sld.dialog.filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
	sld.dialog.currentnode = "Pirate_v_grote_1";
	DoQuestFunctionDelay("AT_pr_Piraty_v_grote_3", 2.3);
}
void AT_pr_Piraty_v_grote_3(string qName)
{
	LAi_SetPlayerType(pchar);
}
void AT_pr_tragedia(string qName)
{	
	DoQuestFunctionDelay("AT_pr_tragedia_2", 1.0);
	chrDisableReloadToLocation = true;
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J1", "sold_spa_4", "man", "man", 1, SPAIN, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","patrol","patrol8");
	LAi_SetActorType(sld);
	sld.SaveItemsForDead = true;
	DeleteAttribute(sld, "items");
	LAi_ActorTurnToLocator(sld, "patrol", "patrol3");
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J2", "sold_spa_6", "man", "man", 1, SPAIN, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","patrol","patrol5");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J3", "priest_1", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto3");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J4", "trader_6", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto2");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J5", "pirate_4", "man", "man", 1, PIRATE, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto1");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J6", "pirate_13", "man", "man", 1, PIRATE, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","merchant","merchant3");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J7", "Girl_3", "woman", "woman", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","patrol","patrol1");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J8", "sold_spa_1", "man", "man", 1, SPAIN, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto9");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J9", "sold_spa_7", "man", "man", 1, SPAIN, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","officers","reload10_3");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J10", "sold_spa_2", "man", "man", 1, SPAIN, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto11");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J11", "shipowner_18", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","reload","houseSp4");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J12", "prison_2", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto10");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J13", "barmen_16", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","patrol","patrol7");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_pr_J14", "trader_7", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto4");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
}
void AT_pr_tragedia_2(string qName)
{	
	sld = CharacterFromID("AT_pr_J1")
	sld.CantLoot = true;
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
	
	sld = CharacterFromID("AT_pr_LaVegaIspanski_Gubernator")
	LAi_SetWarriorType(sld);
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetImmortal(sld, false);
	ChangeCharacterAddressGroup(sld,"LaVega_town","patrol","patrol4");
	LaunchBlood(sld, 1.0, true);
	LaunchBlood(sld, 2.0, true);
	LaunchBlood(sld, 3.0, true);
	LaunchBlood(sld, 4.0, true);
	LAi_KillCharacter(sld);
}
void AT_pr_Bejim_ot_piratov_2(string qName)
{
	Log_SetStringToLog(GetConvertStrWithReplace("Variable_angelika_tich_line_functions_2", "Logs.txt", "#space#", " "));
}
void AT_pr_Bejim_ot_piratov_3(string qName)
{
	Log_SetStringToLog(GetConvertStrWithReplace("Variable_angelika_tich_line_functions_3", "Logs.txt", "#space#", " "));
	Log_SetStringToLog(GetConvertStrWithReplace("Variable_angelika_tich_line_functions_4", "Logs.txt", "#space#", " "));
	SetTimeScale(1.0);
}
void AT_pr_Bejim_ot_piratov_4(string qName)
{
	Island_SetReloadEnableGlobal("Hispaniola1", true);
	bQuestDisableMapEnter = false;
}
void ATpr_OboronaSD_2(string qName)
{	
	locCameraFromToPos(-14.50, 7.00, 0.00, false, 0.22, 2.60, 0.00);
	ChangeShowIntarface();
	DoQuestFunctionDelay("ATpr_OboronaSD_3", 1.5);
	WaitDate("", 0, 0, 0, 3, 0);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
}
void ATpr_OboronaSD_3(string qName)
{
	SetMusic("none");
	SetMusicAlarm("music_bitva");
	
	DoQuestFunctionDelay("ATpr_OboronaSD_4", 1.5);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_SpaMush_1", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc13", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_SpaMush_2", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc15", "", -1);
}
void ATpr_OboronaSD_4(string qName)
{
	DoQuestFunctionDelay("ATpr_OboronaSD_5", 1.5);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_SpaMush_3", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc8", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_SpaMush_4", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc11", "", -1);
}
void ATpr_OboronaSD_5(string qName)
{
	DoQuestFunctionDelay("ATpr_OboronaSD_6", 1.5);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_SpaMush_5", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc7", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_SpaMush_6", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc9", "", -1);
}
void ATpr_OboronaSD_6(string qName)
{
	DoQuestFunctionDelay("ATpr_OboronaSD_7", 1.5);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_SpaMush_7", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc6", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_SpaMush_8", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc1", "", -1);
}
void ATpr_OboronaSD_7(string qName)
{
	DoQuestFunctionDelay("ATpr_OboronaSD_8", 5.0);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_SpaMush_9", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc3", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("AT_SpaMush_10", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc2", "", -1);
}
void ATpr_OboronaSD_8(string qName)
{
	DoQuestFunctionDelay("ATpr_OboronaSD_8_1", 0.8);
	locCameraFromToPos(-3.00, 11.30, -26.00, false, 0.27, -0.36, 0.00);
	
	//Пираты 1 волна (#1)
	for (i=1; i<=7; i++)
    {
		sTemp = "pirate_"+(rand(24)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("TA_Pirate_1_1"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		LAi_SetActorType(sld);
		sld.CantLoot = true;
		ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
    }
}
void ATpr_OboronaSD_8_1(string qName)
{
	DoQuestFunctionDelay("ATpr_OboronaSD_8_2", 1.5);
	PlayVoice("Interface\_bombs.wav");
}
void ATpr_OboronaSD_8_2(string qName)
{
	DoQuestFunctionDelay("ATpr_OboronaSD_9", 2.2);
	
	for (i=1; i<=7; i++)
    {
		sld = CharacterFromID("TA_Pirate_1_1"+i)
		LAi_ActorRunToLocation(sld, "rld", "loc11", "", "", "", "", -1);
	}
}
void ATpr_OboronaSD_9(string qName)
{
	CreateLocationParticles("shipfire", "rld", "loc6", -3.0, 0, 0, "");
	CreateLocationParticles("ShipExplode", "rld", "loc6", 0, 0, 0, "boom");
	CreateLocationParticles("Ship_cannon_fire", "quest", "quest21", 0, -90, 0, "");
	CreateLocationParticles("cancloud_fire_big", "quest", "quest21", 0, -90, 0, "");
	PlayVoice("Sea Battles\sdavl_kriki_002.wav");
	PlaySound("Sea Battles\vistrel_orudiya_004.wav");
	
	for (i=1; i<=7; i++)
    {
		sld = CharacterFromID("TA_Pirate_1_1"+i)
		LAi_KillCharacter(sld);
	}
	
	DoQuestFunctionDelay("ATpr_OboronaSD_10", 0.4);
}
void ATpr_OboronaSD_10(string qName)
{
	DoQuestFunctionDelay("ATpr_OboronaSD_11", 2.9);
	//Пираты 1 волна (#2)
	for (i=1; i<=7; i++)
    {
		sTemp = "pirate_"+(rand(24)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("TA_Pirate_1_2"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		LAi_SetActorType(sld);
		sld.CantLoot = true;
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
		LAi_ActorRunToLocation(sld, "item", "item1", "", "", "", "", -1);
    }
}
void ATpr_OboronaSD_11(string qName)
{
	CreateLocationParticles("shipfire", "rld", "loc9", -3.0, 0, 0, "");
	CreateLocationParticles("ShipExplode", "rld", "loc9", 0, 0, 0, "boom");
	CreateLocationParticles("Ship_cannon_fire", "quest", "quest22", 0, -90, 0, "");
	CreateLocationParticles("cancloud_fire_big", "quest", "quest22", 0, -90, 0, "");
	PlayVoice("Sea Battles\sdavl_kriki_004.wav");
	PlaySound("Sea Battles\vistrel_orudiya_005.wav");
	
	for (i=1; i<=7; i++)
    {
		sld = CharacterFromID("TA_Pirate_1_2"+i)
		LAi_KillCharacter(sld);
	}
	
	DoQuestFunctionDelay("ATpr_OboronaSD_12", 0.5);
}
void ATpr_OboronaSD_12(string qName)
{
	//Пираты 2 волна (#1)
	for (i=1; i<=7; i++)
    {
		sTemp = "pirate_"+(rand(24)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("TA_Pirate_2_1"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		LAi_SetHP(sld, 1.0, 1.0);
		LAi_SetWarriorType(sld);
		sld.CantLoot = true;
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
    }
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "ATpr_3Volna");
	DoQuestFunctionDelay("ATpr_OboronaSD_13", 3.0);
	DoQuestFunctionDelay("ATpr_OboronaSD_12_1", 7.3);
}
void ATpr_OboronaSD_12_1(string qName)
{
	//Если пираты где-то застряли - добиваем
	for (i=1; i<=7; i++)
    {
		sld = CharacterFromID("TA_Pirate_2_1"+i)
		LAi_KillCharacter(sld);
	}
}
void ATpr_OboronaSD_13(string qName)
{
	//Испанцы мушкетёны
	for (i=1; i<=10; i++)
    {
		sld = CharacterFromID("AT_SpaMush_"+i)
		LAi_SetWarriorType(sld);
		sld.CantLoot = true;
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}
void ATpr_OboronaSD_14(string qName)
{
	EndQuestMovie();
	locCameraTarget(PChar)
	locCameraFollow();
	DoQuestFunctionDelay("ATpr_OboronaSD_15", 1.0);
}
void ATpr_OboronaSD_15(string qName)
{
	LAi_SetPlayerType(pchar);
	bDisableCharacterMenu = false;
	LAi_SetFightMode(pchar, true);
	Log_info("ВПЕРЁД! В АТАКУ!");
	PlayVoice("Interface\"+LanguageGetLanguage()+"_GTMutiny_1.wav");
	
	DoQuestFunctionDelay("ATpr_OboronaSD_16", 1.0);
}
void ATpr_OboronaSD_16(string qName)
{	
	//Пираты 3 волна (#1)
	for (i=1; i<=18; i++)
    {
		sTemp = "pirate_"+(rand(24)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("TA_Pirate_3_1"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
    }
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "ATpr_3Volna_2");
	
	DoQuestFunctionDelay("ATpr_OboronaSD_17", 1.0);
	DoQuestFunctionDelay("ATpr_OboronaSD_18", 20.0);
	DoQuestFunctionDelay("ATpr_OboronaSD_20", 26.0);
}
void ATpr_OboronaSD_17(string qName)
{	
	//Испанцы подкрепление (#1)
	for (i=1; i<=8; i++)
    {
		sTemp = "sold_spa_"+(rand(7)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("TA_Spa_Guard_"+i, sTemp, "man", "man", 2, SPAIN, -1, true));
		LAi_SetWarriorType(sld);
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "reload",  "reload1_back");
    }
}
void ATpr_OboronaSD_18(string qName)
{	
	PlaySound("Interface\_musketshot_4.wav");
	//Испанцы подкрепление (#2)
	for (i=7; i<=16; i++)
    {
		sTemp = "sold_spa_"+(rand(7)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("TA_Spa_Guard_"+i, sTemp, "man", "man", 2, SPAIN, -1, true));
		LAi_SetWarriorType(sld);
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "reload",  "reload1_back");
    }
}
void ATpr_OboronaSD_19(string qName)
{	
	DoQuestFunctionDelay("ATpr_OboronaSD_22", 5.0);
	PlaySound("Interface\_musketshot_0.wav");
	//ПИРАТ БОСС
	sld = GetCharacter(NPC_GenerateCharacter("TA_Pirate_4", "BS_Vein", "man", "man", 1, PIRATE, -1, false));
	FantomMakeCoolFighter(sld, 1, 10, 10, "blade12", "pistol6", 60);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
	sld.SaveItemsForDead = true;
	sld.DontChangeBlade = true;
	AddMoneyToCharacter(sld, 3000);
	AddItems(sld, "jewelry5", rand(20)+30);
	AddItems(sld, "jewelry13", rand(5)+15);
	AddItems(sld, "mineral3", 20);
	AddItems(sld, "totem_11", 1);
	//Пираты 3 волна (#2)
	for (i=1; i<=10; i++)
    {
		sTemp = "pirate_"+(rand(24)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("TA_Pirate_3_2"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
    }
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "ATpr_3Volna_3");
}
void ATpr_OboronaSD_20(string qName)
{
	CreateLocationParticles("ShipExplode", "rld", "loc10", 0, 0, 0, "boom");
	CreateLocationParticles("Ship_cannon_fire", "quest", "quest22", 0, -90, 0, "cannon_fire_2");
	CreateLocationParticles("Bombard", "quest", "quest22", 0, -90, 0, "cannon_fire_2");
	//PlayVoice("Sea Battles\sdavl_kriki_004.wav");
	PlaySound("Sea Battles\vistrel_orudiya_004.wav");	
	
	DoQuestFunctionDelay("ATpr_OboronaSD_21", 8.0);
}
void ATpr_OboronaSD_21(string qName)
{
	CreateLocationParticles("ShipExplode", "rld", "loc13", 0, 0, 0, "boom");
	CreateLocationParticles("Ship_cannon_fire", "quest", "quest23", 0, -90, 0, "cannon_fire_2");
	CreateLocationParticles("Bombard", "quest", "quest23", 0, -90, 0, "cannon_fire_2");
	//PlayVoice("Sea Battles\sdavl_kriki_004.wav");
	PlaySound("Sea Battles\vistrel_orudiya_005.wav");
}
void ATpr_OboronaSD_22(string qName)
{
	//CreateLocationParticles("shipfire", "rld", "loc15", -3.0, 0, 0, "");
	CreateLocationParticles("ShipExplode", "rld", "loc15", 0, 0, 0, "boom");
	CreateLocationParticles("Bombard", "quest", "quest22", 0, -90, 0, "cannon_fire_2");
	CreateLocationParticles("Ship_cannon_fire", "quest", "quest22", 0, -90, 0, "cannon_fire_2");
	//PlayVoice("Sea Battles\sdavl_kriki_004.wav");
	PlaySound("Sea Battles\vistrel_orudiya_004.wav");
}
void ATpr_SvobodaIgry(string qName)
{
	PChar.quest.AT_pr_Santo_Domin.over = "yes";
	LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload1_back", false);	//Важная реакция
	LocatorReloadEnterDisable("PortPax_ExitTown", "reload3", false);	//Важная реакция
	LocatorReloadEnterDisable("LaVega_town", "reload4_back", false);	//Важная реакция
	bDisableFastReload = false;
	bDisableLandEncounters = false;
	AddQuestRecord("AT_Mechty_Sbivautsya", "7");
	CloseQuestHeader("AT_Mechty_Sbivautsya");
	DeleteAttribute(pchar, "questTemp.AnjelikaTichPrologue5");
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	TakeItemFromCharacter(pchar, "suit_2");
	DeleteAttribute(pchar, "Cirgnore");
	DeleteAttribute(pchar, "MaxSailing");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	
	sld = CharacterFromID("Gasten_Kotes")
	sld.Dialog.Filename = "Enc_Officer_dialog.c";
	sld.quest.meeting = true;
	Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
	sld.OfficerWantToGo.DontGo = true;
	ChangeCharacterReputation(sld, 20);
	sld.loyality = MAX_LOYALITY;
	LAi_SetCurHPMax(sld);
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, true);
	LAi_SetImmortal(sld, false);
	sld.HalfImmortal = true;
	sld.location = "None";
	sld.Dialog.CurrentNode = "hired";
			
	AddSimpleRumour(GetConvertStrWithReplace("Variable_angelika_tich_line_functions_1", "AddRumours.txt", "#space#", " "), PIRATE, 5, 1);
	AddSimpleRumour(GetConvertStrWithReplace("Variable_angelika_tich_line_functions_2", "AddRumours.txt", "#space#", " "), SPAIN, 5, 1);
	
	//Восстанавливаем город из пепла
	SetLocationCapturedState("LaVega_town", false);
	SetCaptureTownByNation("LaVega", PIRATE);
	locations[FindLocation("LaVega_town")].models.always.locatorsl3 = "LaVega_locators";
	locations[FindLocation("LaVega_town")].models.day.charactersPatch = "LaVega_patch_day";
	locations[FindLocation("LaVega_town")].models.night.charactersPatch = "LaVega_patch_night";
	locations[FindLocation("LaVega_town")].models.always.locatorsl2 = "LaVega_1";
	locations[FindLocation("LaVega_town")].type = "town";
	sld = CharacterFromID("Edward Mansfield")
	ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
	
	sld = CharacterFromID("AT_pr_OfficerRezid")
	sld.lifeday = 0;
	sld = CharacterFromID("AT_pr_devushka_na_rynke")
	sld.lifeday = 0;
	sld = CharacterFromID("Old Friend")
	sld.Dialog.Filename = "Quest\SilencePrice\Luke.c";
	sld.dialog.currentnode = "First Time";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  -- Анжелика Тич --    конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
