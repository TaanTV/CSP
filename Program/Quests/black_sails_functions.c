/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Прочие функции
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BS_SpawnEnemies(int iRnd, int iNation, string winFunction)
{
	ref chr;
	string sLoc, sLoc_2, relation;
	int i;

	relation = LAI_GROUP_PLAYER;
	sLoc = pchar.location;

	chrDisableReloadToLocation = true;
	PChar.GenQuestFort.FarLocator = false;

	Pchar.GenQuestFort.FarLocator = true;
	sLoc = LAi_FindNPCLocator("goto");
	sLoc_2 = LAi_FindNPCLocator("smugglers");
	int rank = 0;
	int fencing = 0;
	int pistol = 0;
	int AddHP = 30*MOD_SKILL_ENEMY_RATE;
	for (i = 1; i <= iRnd; i++)
	{
		rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE*4 + rand(MOD_SKILL_ENEMY_RATE*4);
		fencing = 50 + 10*MOD_SKILL_ENEMY_RATE + rand(10*MOD_SKILL_ENEMY_RATE);
		if (fencing > 100) fencing = 100;
		pistol = 50 + 10*MOD_SKILL_ENEMY_RATE + rand(10*MOD_SKILL_ENEMY_RATE);
		if (pistol > 100) pistol = 100;
		chr = SetFantomDefenceForts("goto", sLoc, iNation, "BS_SpawnEnemies");
		chr.id = "pirate_" + i;
		FantomMakeCoolFighterWRankDepend(chr,rank,fencing,pistol,AddHP);
	}
	//натравим.
	LAi_group_SetHearRadius("BS_SpawnEnemies", 100.0);
	LAi_group_FightGroupsEx("BS_SpawnEnemies", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
	LAi_group_FightGroupsEx("BS_SpawnEnemies", relation, true, Pchar, -1, false, false);

	LAi_group_SetCheckFunction("BS_SpawnEnemies", winFunction);

	LAi_SetFightMode(pchar, true);
}

void BSRepairShip(ref chr)
{
	ProcessHullRepair(chr, 100.0);
	ProcessSailRepair(chr, 100.0);
	DeleteAttribute(chr, "ship.blots");
	DeleteAttribute(chr, "ship.sails");
	RepairMasts(chr);
}

void BS_ReplaceHostessWithMaks()
{
	sld = CharacterFromID("PortRoyal_hostess");
	sld.beforeGatriModel = sld.model;
	sld.model = "BS_Maks";
	sld.beforeGatriModelAnimation = sld.model.animation;
	sld.model.animation = "woman";
	sld.beforeGatriName = sld.name;
	sld.name = GetConvertStrWithReplace("Variable_black_sails_functions_1", "Names.txt", "#space#", " ");
	sld.beforeGatriLastName = sld.lastname;
	sld.lastname = "";
	sld.beforeGatriGreeting = sld.greeting;
	//sld.greeting = "";
	sld.beforeGatriFileName = sld.Dialog.FileName;
	sld.beforeGatriCurrentNode = sld.Dialog.CurrentNode;
}

void BS_RestoreMaksHostess()
{
	sld = CharacterFromID("PortRoyal_hostess");
	sld.model = sld.beforeGatriModel;
	sld.model.animation = sld.beforeGatriModelAnimation;
	sld.name = sld.beforeGatriName;
	sld.lastname = sld.beforeGatriLastName;
	sld.greeting = sld.beforeGatriGreeting;
	sld.Dialog.FileName = sld.beforeGatriFileName;
	sld.Dialog.CurrentNode = sld.beforeGatriCurrentNode;
}

void BS_ReplaceTraderWithGatri()
{
	sld = CharacterFromID("Pirates_trader");
	sld.beforeGatriModel = sld.model;
	sld.model = "BS_Gatry";
	sld.beforeGatriModelAnimation = sld.model.animation;
	sld.model.animation = "woman";
	sld.beforeGatriName = sld.name;
	sld.name = GetConvertStrWithReplace("Variable_black_sails_functions_2", "Names.txt", "#space#", " ");
	sld.beforeGatriLastName = sld.lastname;
	sld.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_3", "Names.txt", "#space#", " ");
	sld.beforeGatriGreeting = sld.greeting;
	sld.greeting = "Gr_Woman_Citizen";
	sld.beforeGatriFileName = sld.Dialog.FileName;
	sld.beforeGatriCurrentNode = sld.Dialog.CurrentNode;
}

void BS_RestoreGatriTrader(string q)
{
	sld = CharacterFromID("Pirates_trader");
	sld.sex = "man";
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	sld.model = sld.beforeGatriModel;
	sld.model.animation = sld.beforeGatriModelAnimation;
	sld.name = sld.beforeGatriName;
	sld.lastname = sld.beforeGatriLastName;
	sld.greeting = sld.beforeGatriGreeting;
	sld.Dialog.FileName = sld.beforeGatriFileName;
	sld.Dialog.CurrentNode = sld.beforeGatriCurrentNode;
}

void BS_QuestCleaning(bool the_end)
{
	if (CheckAttribute(&Colonies[FindColony("Nassau")], "BSBlackFlag"))
	{
		DeleteAttribute(&Colonies[FindColony("Nassau")], "BSBlackFlag");
		DeleteAttribute(pchar, "BSBonsSpawned");
		DeleteAttribute(PChar, "GatriSalutation");
		sld = CharacterFromID("Gatri_temp");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		BS_GatriHomeGuardsCleaning();		
		LocatorReloadEnterDisable("Nassau_town", "houseS1", false);
		LocatorReloadEnterDisable("Nassau_fort", "reload2", false);
		LocatorReloadEnterDisable("Nassau_town", "reload3_back", false);
		LocatorReloadEnterDisable("Nassau_town", "reload5_back", false);
		LocatorReloadEnterDisable("Nassau_town", "reload7_back", false);
		LocatorReloadEnterDisable("Nassau_town", "reload8_back", false);
		LocatorReloadEnterDisable("Nassau_town", "reload9_back", false);
		LocatorReloadEnterDisable("Nassau_town", "reload10_back", false);
		ref  rChar;
		int  j;
		string sColony = "Nassau";
		int iNation = ENGLAND;
		int iColony = FindColony(sColony);
		string sGroup;
		sGroup = GetNationNameByType(iNation) + "_CITIZENS";
		for (j=0; j< MAX_CHARACTERS; j++)
		{
			rChar = GetCharacter(j);
			if(CheckAttribute(rChar, "city") && rChar.City == sColony)
			{
				if (CheckAttribute(rChar, "CityType"))
				{
					rChar.LifeDay = 0;
				}
				rChar.nation = iNation;
				LAi_group_MoveCharacter(rChar, sGroup);
				if (rChar.id == (sColony + "_Mayor"))
				{
					if (iNation != PIRATE)
					{
						rChar.Default.nation = iNation;
					}
	        	SetTownMayor(rChar, iNation);
				}
				if (rChar.id == (sColony + " Fort Commander"))
				{
					if (iNation != PIRATE)
					{
						rChar.Default.nation = iNation;
						rChar.FaceId = 69+rand(1);
					}
					SetTownOfficForts(rChar, iNation);
				}
			}
    }
    ClearIslandShips(sColony);
	sColony = sColony + "_town";
	worldMap.labels.(sColony).icon = iNation;
	AddFortNation(sti(Colonies[iColony].nation), -1);
 	AddFortNation(iNation, 1);
	sld = GetFortCommander("Nassau");
	sld.FaceId = 69+rand(1);
    Colonies[iColony].nation = iNation;
   	Colonies[iColony].isBought = false;
	}
	if (the_end)
	{
		EraseBSCharacters();
		pchar.BSFinish = true;
		DeleteAttribute(pchar, "BSInProgress");
		Log_TestInfo(GetConvertStrWithReplace("Variable_black_sails_functions_1", "Logs.txt", "#space#", " "))
	}
}

void GatriSpeech(string qName)
{
	sld = CharacterFromID("Gatri_temp");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void GatriStoreSpeech(string qName)
{
	sld = CharacterFromID("Pirates_trader");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void FlintSpeech(string qName)
{
	sld = CharacterFromID("Flint");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void SilverSpeech(string qName)
{
	sld = CharacterFromID("BS_Silver");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void MaksSpeech(string qName)
{
	sld = CharacterFromID("BS_Maks");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void VeinSpeech(string qName)
{
	sld = CharacterFromID("BS_Vein");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void BonySpeech(string qName)
{
	sld = CharacterFromID("BS_Bony");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void RakhamSpeech(string qName)
{
	sld = CharacterFromID("BS_Rakham");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void Gatri_upstairs(string qName)
{
	DoQuestFunctionDelay("GatriSpeech", 0);
}

void Flint_upstairs(string qName)
{
	DoQuestFunctionDelay("FlintSpeech", 0);
}

void Silver_Downstairs(string qName)
{
	DoQuestFunctionDelay("SilverSpeech", 0);
}

void BS_CorrectShipGoods(ref chr)
{
	Fantom_SetCharacterGoods(chr, GOOD_SAILCLOTH, makeint(GetCargoGoods(chr, GOOD_SAILCLOTH)/2), 0);
	Fantom_SetCharacterGoods(chr, GOOD_PLANKS, makeint(GetCargoGoods(chr, GOOD_PLANKS)/2), 0);
	Fantom_SetCharacterGoods(chr, GOOD_POWDER, makeint(GetCargoGoods(chr, GOOD_POWDER)*2/3), 0);
	Fantom_SetCharacterGoods(chr, GOOD_BALLS, makeint(GetCargoGoods(chr, GOOD_BALLS)*3/4), 0);
}

void BS_SL_no()
{
	InterfaceStates.Buttons.Save.enable = false;
	bDisableFastReload = true;
	chrDisableReloadToLocation = true;
}

void BS_SL_yes()
{
	InterfaceStates.Buttons.Save.enable = true;
	bDisableFastReload = false;
	chrDisableReloadToLocation = false;
}

void UltimatePerksSet(ref chr)
{
	SetCharacterPerk(chr, "MusketsShoot");
	SetCharacterPerk(chr, "FastReload");
	SetCharacterPerk(chr, "HullDamageUp");
	SetCharacterPerk(chr, "SailsDamageUp");
	SetCharacterPerk(chr, "CrewDamageU");
	SetCharacterPerk(chr, "CriticalShoot");
	SetCharacterPerk(chr, "MapMaker");
	SetCharacterPerk(chr, "LongRangeShoot");
	SetCharacterPerk(chr, "CannonProfessional");
	SetCharacterPerk(chr, "BasicBattleState");
	SetCharacterPerk(chr, "AdvancedBattleState");
	SetCharacterPerk(chr, "ShipDefenseProfessional");
	SetCharacterPerk(chr, "ShipSpeedUp");
	SetCharacterPerk(chr, "ShipTurnRateUp");
	SetCharacterPerk(chr, "WindCatcher");
	SetCharacterPerk(chr, "SailsMan");
	SetCharacterPerk(chr, "SailingProfessional");
	chr.GhostShipTuning = true;
}

void BS_EmptyAdress_Silver(string qName)
{
	sld = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void BS_EmptyAdress_Maks(string qName)
{
	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	DeleteAttribute(pchar,"ContraInterruptWaiting");
}

void BS_EmptyAdress_Flint(string qName)
{	
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void BS_EmptyAdress_Vein(string qName)
{	
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void BS_EmptyAdress_Rakham(string qName)
{	
	sld = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void BS_EmptyAdress_Bony(string qName)
{	
	sld = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void BS_Vein_Immortal(string qName)
{
	sld = CharacterFromID("BS_Vein_free");
	LAi_SetImmortal(sld, true);
	sld.ShipEnemyDisable = true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Прочие функции
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Чёрные паруса на горизонте
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void BST_Pirates_Store(string qName)
{	
	bDisableOfficers = true;
	LAi_SetStayType(pchar);
	BS_SL_no();
	pchar.currentsoundtrack = "Theme_from_Black_Sails";
	SetFunctionExitFromLocationCondition("BS_RestoreGatriTrader", "Pirates_Store", false);
	SetFunctionExitFromLocationCondition("BS_Pirates_Store_Exit", "Pirates_Store", false);
	locCameraFlyToPosition(-7.499, 1.6431, -1.3645, -1.8691, 3.5261, -4.6096, 1.0, 200);
	DoQuestFunctionDelay("BST_Pirates_Store_1", 0.1);
}

void BST_Pirates_Store_1(string qName)
{
	ChangeShowIntarface();
	sld = CharacterFromID("Pirates_trader");
	locCameraTarget(sld);
	pchar.funcaftermovie = "BST_Pirates_Store_2";
}

void BST_Pirates_Store_2()
{
	locCameraToPos(-1.8691, 3.5261, -4.6096, false);
	LAi_FadeDelay(2.0, "");
	DoQuestFunctionDelay("BST_Pirates_Store_3", 1.0);
}

void BST_Pirates_Store_3(string qName)
{	
	ChangeShowIntarface();
	LAi_SetPlayerType(PChar);
	DeleteAttribute(PChar, "funcaftermovie");
	locCameraResetState();
	locCameraTarget(pchar);
}

void BS_Pirates_Store_Exit(string qName)
{
	for (int i = 1; i < 4; i++)
	{
		if(GetCharacterIndex("gatri_grunt"+i) != -1)
		{
			sld = CharacterFromID("gatri_grunt"+i);
			sld.LifeDay = 0;
		}
	}
	BS_SL_yes();
	bDisableOfficers = false;
	DeleteAttribute(PChar, "currentsoundtrack");
	if (CheckAttribute(PChar, "questTemp.BSPrologue.WaitingForNassauSiege"))
	{
		sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp", "BS_Gatry", "woman", "woman", 1, PIRATE, -1, false));			
		sld.name = GetConvertStrWithReplace("Variable_black_sails_functions_2", "Names.txt", "#space#", " ");
		sld.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_3", "Names.txt", "#space#", " ");
		sld.model.animation = "woman";
		//sld.greeting = "Gr_Woman_Citizen";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, PChar, "", "", "");
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		sld.Dialog.FileName = "Quest\BlackSails\NePluyjVKolodec.c";
		sld.dialog.CurrentNode = "BS_NPVK_15";
		ChangeCharacterAddressGroup(sld, "Pirates_tavern_upstairs", "goto", "goto1");	
	}
}

void BS_ToNassauSiege_PiratesTown()
{
	AddQuestRecord("BSPrologue", "7");
	AddQuestUserData("BSPrologue", "sSex", GetSexPhrase("ся","ась"));
	DeleteAttribute(pchar, "BSStart");
	pchar.BSInProgress = true;
	Flag_Change(PIRATE);
	pchar.BS_permanentblackflag = true;
	pchar.BS_NassauWaitingForSiege = true;
	DeleteAttribute(PChar, "questTemp.BSPrologue.WaitingForNassauSiege");
	DoReloadCharacterToLocation("Pirates_town", "reload", "reload4_back");
	sld = CharacterFromID("Gatri_temp");	
	ChangeCharacterAddress(sld, "None", "");	
}

void BS_NassauEntriesDisable()
{
	LocatorReloadEnterDisable("Nassau_fort", "reload2", true);
	LocatorReloadEnterDisable("Nassau_town", "reload3_back", true);
	LocatorReloadEnterDisable("Nassau_town", "reload5_back", true);
	LocatorReloadEnterDisable("Nassau_town", "reload7_back", true);
	LocatorReloadEnterDisable("Nassau_town", "reload8_back", true);
	LocatorReloadEnterDisable("Nassau_town", "reload9_back", true);
	LocatorReloadEnterDisable("Nassau_town", "reload10_back", true);
}

void BS_NassauSiegeWin(string qName)
{
	SetMusic("Nassau_Shores");
	LAi_FadeDelay(2.0, "");
	DoQuestFunctionDelay("BS_NassauSiege_Camera_1", 1.5);
	DoQuestFunctionDelay("BS_NassauSiegeGatriArriving", 1.0);
	LAi_SetStayType(pchar);
}

void BS_NassauSiege_Camera_1(string qName)
{
	ChangeShowIntarface();
	locCameraFlyToPosition(98.1727, 6.1956, 6.9158, 98.0520, 9.3835, 6.2299, 1.0, 300);
	pchar.funcaftermovie = "BS_NassauSiege_Camera_2";
}

void BS_NassauSiege_Camera_2()
{
	locCameraToPos(98.0520, 9.3835, 6.2299, false);
	DeleteAttribute(PChar, "funcaftermovie");
	DoQuestFunctionDelay("BS_NassauGatriAfterSiegeDialogue", 3.0);
}

void BS_NassauSiegeGatriArriving(string qName)
{
	LocatorReloadEnterDisable("Nassau_town", "houseS1", true);
	LAi_LocationFightDisable(&Locations[FindLocation("Nassau_town")], true);
	LAi_IsCapturedLocation = false;
	TeleportCharacterToPos(pchar, 103.45377, 3.8435075, 3.1869335);
	sld = CharacterFromID("Gatri_temp");
	sld.Dialog.FileName = "Quest\BlackSails\NePluyjVKolodec.c";
	sld.dialog.CurrentNode = "BS_NPVK_17";
	ChangeCharacterAddressGroup(sld, "Nassau_town", "reload", "houseS1");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToCharacter(sld, Pchar);
	LAi_SetStayType(sld);
	LAi_SetActorTypeNoGroup(PChar);
	LAi_ActorTurnToCharacter(PChar, sld);
	LAi_SetStayType(pchar);
	float posX, posY, posZ;
	GetCharacterPos(sld, &posX, &posY, &posZ);	
	for (int i = 1; i < 8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("gatri_grunt"+i, GetPirateMushketerModel(), "man", "mushketer", 100, PIRATE, 0, false));
		ChangeCharacterAddressGroup(sld, "Nassau_town", "officers", LAi_FindNearestFreeLocator("officers", posX, posY, posZ));
		if (i==1) TeleportCharacterToPos(sld, 101.36577, 3.8572285, 1.6394247);
		if (i==2) TeleportCharacterToPos(sld, 104.27003, 3.8809671, 0.580896);
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorTurnToCharacter(sld, PChar);
		//LAi_SetStayType(sld);
		LAi_warrior_DialogEnable(sld, false);		
	}
}
void BS_NassauGatriAfterSiegeDialogue(string qName)
{
	sld = CharacterFromID("Gatri_temp");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, PChar, "", "", "");
}

void BS_NassauSiegeComplete()
{
	locCameraResetState();
	ChangeShowIntarface();
	LAi_SetPlayerType(PChar);
	chrDisableReloadToLocation = false;
    ref rColony = GetColonyByIndex(FindColony("Nassau"));
	ClearIslandShips("Nassau");
	LaunchColonyCapture(rColony);
	DeleteAttribute(rColony, "AlreadyGen");
	DeleteAttribute(PChar, "BS_permanentblackflag");
	DeleteAttribute(PChar, "BS_NassauWaitingForSiege");
	Flag_Change(PIRATE);
	SetFunctionExitFromLocationCondition("BS_GiveNassauToGatri", "Nassau_town", false);
	sld = CharacterFromID("Gatri_temp");
	LAi_SetStayType(sld);
	if (ChangeCharacterHunterScore(Pchar, "enghunter", 0) > 0) {ChangeCharacterHunterScore(Pchar, "enghunter", -ChangeCharacterHunterScore(Pchar, "enghunter", 0));}
}

void BS_GiveNassauToGatri(string qName)
{
	SetCaptureTownByNation("Nassau", PIRATE);
	LAi_LocationFightDisable(&Locations[FindLocation("Nassau_OfisGatri")], true);
	LAi_LocationFightDisable(&Locations[FindLocation("Nassau_town")], false);
	LAi_LocationDisableOfficersGen("Nassau_OfisGatri", true);
	Colonies[FindColony("Nassau")].BSBlackFlag = true;
	//LocatorReloadEnterDisable("Nassau_OfisGatri", "reload2", true);
	LocatorReloadEnterDisable("Nassau_town", "houseS1", false);
	sld = CharacterFromID("Gatri_temp");
	sld.Dialog.FileName = "Quest\BlackSails\NePluyjVKolodec.c";
	sld.dialog.currentnode = "BS_NPVK_20_meet";
	sld.CityType = "citizen";
	sld.city = "Nassau";
	//sld.greeting = "Gr_Woman_Citizen";	
	ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "quest", "quest5");	
	CharacterTurnToLoc(sld, "reload", "reload1_back");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	BS_GatriHomeGuards();
}

void BS_GatriHomeGuards()
{
	for (int i = 1; i < 6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("gatri_home_grunt"+i, GetPirateMushketerModel(), "man", "mushketer", 100, PIRATE, -1, false));
		if (i < 3)
		{
			ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "goto", "goto"+i);
			LAi_SetStayType(sld);
			LAi_SetActorTypeNoGroup(sld);
		}
		else
		{
			ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "goto", "goto7");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, false);
		}		
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		LAi_SetImmortal(sld, true);
	}
}

void BS_GatriHomeGuardsOn()
{
	for (int i = 1; i < 6; i++)
	{
		sld = CharacterFromID("gatri_home_grunt"+i);
		if (i < 3)
		{
			ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "goto", "goto"+i);
		}
		else
		{
			ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "goto", "goto7");
		}
	}
}

void BS_GatriHomeGuardsOff()
{
	for (int i = 1; i < 6; i++)
	{
		sld = CharacterFromID("gatri_home_grunt"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
}

void BS_GatriHomeGuardsCleaning()
{
	for (int i = 1; i < 6; i++)
	{
		sld = CharacterFromID("gatri_home_grunt"+i);
		sld.lifeDay = 0;
	}
}

void BSOnTheHorizon_start(string qName)
{
	DoQuestFunctionDelay("BSOnTheHorizon_StoreScene", 0.5);
}

void BSOnTheHorizon_StoreScene(string qName)
{
	pchar.currentsoundtrack = "Nassau_Shores";
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Nassau_town")], true);
	sld = CharacterFromID("Gatri_temp");
	sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
	sld.dialog.currentnode = "BS_CPNG_3";
	ChangeCharacterAddressGroup(sld, "Nassau_town", "officers", "reload6_3");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToCharacter(sld, PChar);
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	int i = 0;
	for (i = 1; i < 4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("gatri_grunt"+i, GetPirateMushketerModel(), "man", "mushketer", 100, PIRATE, 0, false));
		if (i==1) ChangeCharacterAddressGroup(sld, "Nassau_town", "officers", "reload6_1");
		if (i==2) ChangeCharacterAddressGroup(sld, "Nassau_town", "officers", "reload6_3");
		if (i==3) ChangeCharacterAddressGroup(sld, "Nassau_town", "reload", "reload6_back");
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		LAi_SetStayType(sld);
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorTurnToCharacter(sld, PChar);
		LAi_warrior_DialogEnable(sld, false);		
	}
	string smodel = "head_pir";
	for (i = 1; i < 6; i++)
	{
		switch (i)
		{
			case 1:
				smodel = "trader_1";
			break;
			case 2:
				smodel = "off_eng_2";
			break;
			case 3:
				smodel = "head_pir";
			break;
			case 4:
				smodel = "off_eng_1";
			break;
			case 5:
				smodel = "huber_eng";
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp"+i, smodel, "man", "man", 10, PIRATE, 0, true));
		ChangeCharacterAddressGroup(sld, "Nassau_town", "goto", "goto11");
		if (i==1) TeleportCharacterToPos(sld, 103.7956, 3.8304389, 4.21834);
		if (i==2) TeleportCharacterToPos(sld, 103.05895, 3.84115, 3.2375011);
		if (i==3) TeleportCharacterToPos(sld, 102.66961, 3.8575888, 1.9739792);
		if (i==4) TeleportCharacterToPos(sld, 102.49572, 3.8729136, 0.91424334);
		if (i==5) TeleportCharacterToPos(sld, 102.0905, 3.8913054, -0.49147958);
		LAi_SetStayType(sld);
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorTurnToCharacter(sld, CharacterFromID("Gatri_temp"));
		LAi_SetImmortal(sld, true);
	}
}

void BSOnTheHorizon_Flint();
{
	string langtemp = "";
	if (LanguageGetLanguage() != "russian") { langtemp = "Walrus"; }
	else { langtemp = "Морж"; }
	sld = GetCharacter(NPC_GenerateCharacter("Flint", "BS_Flint_0", "man", "man", 999, PIRATE, -1, true));
	FantomMakeCoolestSailor(sld, SHIP_ROTTERDAM, langtemp, CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
	FantomMakeCoolFighter(sld, 100, 100, 100, "blade43", "pistol4", 1000);
	SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);
	sld.name = GetConvertStrWithReplace("Variable_black_sails_functions_6", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_7", "Names.txt", "#space#", " ");
	//sld.greeting = "pirat_common";
	string sGroup = "Sea_Flint";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = GetConvertStrWithReplace("Variable_black_sails_functions_8", "Names.txt", "#space#", " ");
	string sColony = "LeFransua";
	pchar.questTemp.Flint.City = "LaVega";
	int daysQty = 5;
	SetTimerCondition("Flint_SetCity", 0, 0, daysQty, true);
	Map_CreateTrader(sColony, pchar.questTemp.Flint.City, sld.id, daysQty);
	sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
	sld.DeckDialogNode = "BS_CPNG_15";
	LAi_SetImmortal(sld, true);
	sld.Abordage.Enable = false;
	Log_TestInfo(GetConvertStrWithReplace("Variable_black_sails_functions_2", "Logs.txt", "#space#", " ") + sColony + GetConvertStrWithReplace("Variable_black_sails_functions_3", "Logs.txt", "#space#", " ") + pchar.questTemp.Flint.City+GetConvertStrWithReplace("Variable_black_sails_functions_4", "Logs.txt", "#space#", " ")+daysQty);
}

void MeetFlintCrew(string qName)
{
	pchar.currentsoundtrack = "All_Saints";
	bDisableOfficers = true;
	chrDisableReloadToLocation = true;
	BS_GatriHomeGuardsOff();
	TeleportCharacterToPos(pchar, 73.12008, 3.20824, 25.118425);
	sld = CharacterFromID("Flint");
	sld.dialog.currentnode = "BS_CPNG_18";
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	TeleportCharacterToPos(sld, 74.198654, 3.126261, 22.670755);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_SetImmortal(sld, true);
	Group_DeleteGroup("Sea_Flint");
	sld = GetCharacter(NPC_GenerateCharacter("BS_Silver", "BS_Silver", "man", "man", 999, PIRATE, -1, true));
	//sld.greeting = "pirat_common";
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	TeleportCharacterToPos(sld, 74.1475, 3.1212275, 21.183332);
	sld.name = GetConvertStrWithReplace("Variable_black_sails_functions_9", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_10", "Names.txt", "#space#", " ");
	LAi_SetImmortal(sld, true);
	sld = GetCharacter(NPC_GenerateCharacter("BS_Billy", "BS_Billy", "man", "man", 999, PIRATE, -1, true));
	//sld.greeting = "pirat_common";
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	TeleportCharacterToPos(sld, 75.27994, 3.1098757, 21.558277);
	sld.name = GetConvertStrWithReplace("Variable_black_sails_functions_11", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_12", "Names.txt", "#space#", " ");
	LAi_SetImmortal(sld, true);
}

void BSOnTheHorizon_End(string qName)
{
	AddQuestRecord("BSOnTheHorizon", "5");
	CloseQuestHeader("BSOnTheHorizon");
	LocatorReloadEnterDisable("Nassau_town", "houseS1", false);
	string langtemp = "";
	if (LanguageGetLanguage() != "russian") { langtemp = "I need to talk to Flint on the beach"; }
	else { langtemp = "Мне нужно поговорить с Флинтом на берегу"; }
	pchar.LockMapReload = langtemp;
	pchar.quest.BSCourtlyPassions_begin.win_condition.l1 = "ExitFromLocation";
	pchar.quest.BSCourtlyPassions_begin.function = "BSCourtlyPassions_begin";

	sld = CharacterFromID("Flint");
	LAi_SetImmortal(sld, false);
	LocatorReloadEnterDisable("Nassau_town", "gate1", false);
	LocatorReloadEnterDisable("Nassau_ExitTown", "reload2_back", false);
	pchar.BSCPFlint_talk = true;
}

void BSOnTheHorizon_SeaBattle()
{
    string sCapId = "BSOnTheHorizon_SeaBattle";
    string sGroup = "Sea_" + sCapId + "1";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "pirate");
	for (int i = 1; i < 7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(sCapId+i, "off_eng_"+(rand(1)+1), "man", "man", 999, ENGLAND, -1, true));
		if (i == 1)
		{
			sld.Ship.Type = GenerateShipExt(SHIP_DIANA, true, sld);
			sld.Ship.Name = GetConvertStrWithReplace("Variable_black_sails_functions_13", "Names.txt", "#space#", " ");
			sld.Name = GetConvertStrWithReplace("Variable_black_sails_functions_14", "Names.txt", "#space#", " ");
			sld.Lastname = GetConvertStrWithReplace("Variable_black_sails_functions_15", "Names.txt", "#space#", " ");
			sld.rank_bonus = 9*MOD_SKILL_ENEMY_RATE;
		}
		if (i == 2) sld.Ship.Type = GenerateShipExt(SHIP_INDEFATIGABLE, true, sld);
		if (i == 3) sld.Ship.Type = GenerateShipExt(SHIP_MORDAUNT, true, sld);
		if (i == 4) sld.Ship.Type = GenerateShipExt(SHIP_LINESHIP, true, sld);
		if (i == 5) sld.Ship.Type = GenerateShipExt(SHIP_NAVIO, true, sld);
		if (i == 6) sld.Ship.Type = GenerateShipExt(SHIP_LEOPARD, true, sld);

		sld.rank_bonus = 6*MOD_SKILL_ENEMY_RATE;
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		UltimatePerksSet(sld);
		sld.Ship.Mode = "war";
		Fantom_SetUpgrade(sld, "hunter");
		Fantom_SetCannons(sld, "pirate");
		Fantom_SetBalls(sld, "pirate");
		BS_CorrectShipGoods(sld);

		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		SetFantomParamHunter(sld);
		Group_AddCharacter(sGroup, sld.id);		
	}
	int ig = Group_FindGroup(sGroup);
	
	AIGroups[ig].location = "Bahames";
	AIGroups[ig].pos.x = -646.0;
	AIGroups[ig].Pos.z = 3298.2;
	AIGroups[ig].Pos.ay = 0;
	Group_SetGroupCommander(sGroup, sCapId + "1");
	Group_SetTaskAttack(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	sld = CharacterFromID("Flint");
	LAi_SetImmortal(sld, false);
}


void BS_GatryFlintInHouseDialogue(string qName)
{
	sld = CharacterFromID("Flint");
	LAi_SetSitTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "sit", "sit2");
	sld = CharacterFromID("Gatri_temp");
	ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "quest", "quest5");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToCharacter(CharacterFromID("Gatri_temp"), CharacterFromID("Flint"));
	
	LAi_SetStayType(CharacterFromID("Gatri_temp"));
	LAi_SetActorTypeNoGroup(pchar);
	LAi_ActorTurnToCharacter(pchar, CharacterFromID("Gatri_temp"));
	LAi_SetPlayerType(pchar);
}

void StartReloadToCobHouse()
{
	InterfaceStates.Buttons.Save.enable = false;
	LAi_FadeDelay(3.0, "");
	DoQuestFunctionDelay("ReloadToCobHouseInProcess_1", 2.0);
}

void ReloadToCobHouseInProcess_1(string qName)
{
	StartQuestMovie(true, true, false);
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = CharacterFromID("BS_Billy");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	TeleportCharacterToPos(pchar, 110, 6.55, -12.83);
	LAi_SetStayType(pchar);
	locCameraToPos(90.0, 10.0, 80.0, false);
	DoQuestFunctionDelay("ReloadToCobHouseInProcess_2", 4.0);
}

void ReloadToCobHouseInProcess_2(string qName)
{
	locCameraFlyToPosition(90.0, 10.0, 80.0, 33.0, 36.0, 49.0, 1.0, 350);
	pchar.funcaftermovie = "ReloadToCobHouseInProcess_3";
}

void ReloadToCobHouseInProcess_3(string qName)
{
	pchar.funcaftermovie = "EndReloadToCobHouse";
	locCameraFlyToPosition(33.0, 36.0, 49.0, 101.7, 4.55, -0.83, 1.0, 200);
}

void EndReloadToCobHouse(string qName)
{
	DeleteAttribute(PChar, "funcaftermovie");
	pchar.currentsoundtrack = "On_the_Beach";
	EndQuestMovie();
	LAi_SetPlayerType(PChar);
    DoReloadCharacterToLocation("Nassau_OfisGatri","officers","reload1_3");
}
/*
void BS_OnTheHorizonTavernExit(string qName)
{
	DoQuestFunctionDelay("BS_OnTheHorizonTavernExitProcess", 0.1);
}
*/
void BS_OnTheHorizonTavernExit(string qName)
{
	sld = CharacterFromID("Gatri_temp");	
	ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "quest", "quest5");
	sld.Dialog.FileName = "Quest\BlackSails\NePluyjVKolodec.c";
	sld.dialog.currentnode = "BS_NPVK_20_meet";
	sld = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	LAi_CharacterEnableDialog(sld);
	sld = CharacterFromID("BS_Billy");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	LAi_CharacterEnableDialog(sld);
	BS_GatriHomeGuardsOn();
	bDisableOfficers = false;
	LocatorReloadEnterDisable("Nassau_town", "houseS1", true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Чёрные паруса на горизонте --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Куртуазные страсти
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BSCourtlyPassions_DontStart(string qName)
{
	DeleteAttribute(pchar, "BSCPFlint_talk");
	CloseQuestHeader("BSOnTheHorizon");
	BS_QuestCleaning(true);
	PChar.quest.BattleSeaDefenceColonyWinner.over = "yes";
	Group_DeleteGroup("Sea_BSOnTheHorizon_SeaBattle1");
}

void BSCourtlyPassions_begin(string qName)
{
	ref sld, chr;

	if(pchar.location == pchar.location.from_sea || HasSubStr(pchar.location,"_town") || HasSubStr(pchar.location,"shore"))
	{
		if (CheckAttribute(pchar, "BSCPFlint_talk") && !bSeaActive)
		{
			sld = CharacterFromID("Flint");
			if (!CheckAttribute(sld, "curtown") || sld.curtown != pchar.location)
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));	
				chrDisableReloadToLocation = true;
				LAi_SetActorType(sld);
				sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
				sld.dialog.currentnode = "BS_KS_1";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				sld.curtown = pchar.location;
				LAi_SetImmortal(sld, true);

				chr = CharacterFromID("BS_Silver");
				ChangeCharacterAddressGroup(chr, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", -1);
				LAi_SetImmortal(chr, true);
			}
		}
	}
	else
	{
		SetFunctionExitFromLocationCondition("BSCourtlyPassions_begin_again", pchar.location, true);
	}
}

void BSCourtlyPassions_begin_again(string quest)
{
	if(CheckAttribute(pchar, "BSCPFlint_talk"))
	{
		pchar.quest.BSCourtlyPassions_begin.win_condition.l1 = "ExitFromLocation";
		pchar.quest.BSCourtlyPassions_begin.function = "BSCourtlyPassions_begin";
	}
}

void BSCourtlyPassions_sailor_begin(string qName)
{
	if(pchar.location == "LeFransua_town" || pchar.location == "FortFrance_town" ||  pchar.location == "Shore38" ||   pchar.location == "Shore39")
	{
		BSCourtlyPassions_sailor();
	}
	else
	{
		SetFunctionExitFromLocationCondition("BSCourtlyPassions_sailor_begin_again", pchar.location, true);
	}
}

ref BSTutorialSailor();
{
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Pirate_9", "man", "man", 1, PIRATE, 0, false));
	sld.name 	= GetConvertStr("Variable_black_sails_functions_0.1", "Names.txt");
	sld.lastname 	= GetConvertStr("Variable_black_sails_functions_0.1.1", "Names.txt");
	sld.greeting = "Teacher_pirat";
	return sld;
}

void BSCourtlyPassions_sailor()
{
	ref sld, chr;

	if (CheckAttribute(pchar, "BSCPSailor_talk") && !bSeaActive)
	{
		chr = CharacterFromID("Flint");
		if (!CheckAttribute(chr, "curtown") || chr.curtown != pchar.location)
		{
			chrDisableReloadToLocation = true;
			sld = BSTutorialSailor();
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chr.curtown = pchar.location;
			LAi_SetImmortal(sld, true);
		}
	}
	else
	{
		if (CheckAttribute(pchar, "BSCPSilver_talk") && pchar.location == "FortFrance_town")
		{
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("BS_Silver");
			LAi_type_actor_Reset(sld);
			sld.dialog.currentnode = "BS_KS_8";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.curtown = pchar.location;
		}
	}
}

void BSCourtlyPassions_sailor_begin_again(string _quest)
{
	if(CheckAttribute(pchar, "BSCPSailor_talk") || CheckAttribute(pchar, "BSCPSilver_talk"))
	{
		pchar.quest.BSCourtlyPassions_sailor_begin.win_condition.l1 = "ExitFromLocation";
		pchar.quest.BSCourtlyPassions_sailor_begin.function = "BSCourtlyPassions_sailor_begin";
	}
}

void BSCourtlyPassions_wait(string _quest)
{
	pchar.ContraInterruptWaiting = true;//Заблочить сон и отдых
	PChar.quest.BSCourtlyPassions_dungeon.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_dungeon.win_condition.l1.location = "FortFrance_dungeon";
	PChar.quest.BSCourtlyPassions_dungeon.function = "BSCourtlyPassions_dungeon";
}

void LockWeapons(string _quest)
{
	ref _location = &locations[reload_location_index];
	LAi_LocationFightDisable(_location, true);
}
void UnLockWeapons(string _quest)
{
	ref _location = &locations[reload_location_index];
	LAi_LocationFightDisable(_location, false);
}

void BSCourtlyPassions_dungeon(string _quest)
{
	WaitDate("",0,0,0,24 - sti(environment.time),5);
	LAi_LocationDisableMonGenTimer("FortFrance_dungeon", 3);//Лок спавна скелетов
	LAi_LocationDisableToughSkeletonTimer("FortFrance_dungeon", 3); //ПК не пускать
	DoQuestFunctionDelay("LockWeapons", 0);
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("BS_Vein", "BS_Vein", "man", "man", 99, PIRATE, -1, true));
	sld.name 	= GetConvertStr("Variable_black_sails_functions_0.2", "Names.txt");
	sld.lastname 	= GetConvertStr("Variable_black_sails_functions_0.2.1", "Names.txt");
	ChangeCharacterAddressGroup(sld, "FortFrance_dungeon", "monsters", "monster35");
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
	sld.dialog.currentnode = "BS_KS_27";
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
	BSCourtlyPassions_spawn_podsos();
}

void BSCourtlyPassions_spawn_podsos()
{
	aref grp;
	ref _location = &Locations[FindLocation(pchar.location)];
	makearef(grp, _location.locators.monsters);
	int maxPodsos = GetAttributesNum(grp);
	string cnd;
	for (int i = 1; i < maxPodsos; i++)
	{

		sld = GetCharacter(NPC_GenerateCharacter("BS_VeinPodsos"+i, "pirate_"+sti(rand(24)+1), "man", "man", 99, PIRATE, 3, true));
		ChangeCharacterAddressGroup(sld, _location.id, "monsters", GetAttributeName(GetAttributeN(grp, i)));
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_warrior_DialogEnable(sld, false);
		cnd = "l" + i;
		//pchar.quest.BSCourtlyPassions_kill_podsos.win_condition.(cnd) = "NPC_Death";
		//pchar.quest.BSCourtlyPassions_kill_podsos.win_condition.(cnd).character = sld.id;
	}
	//PChar.quest.BSCourtlyPassions_kill_podsos.function = "BSCourtlyPassions_kill_podsos";

}

void BSCourtlyPassions_kill_podsos(string _quest)
{
	chrDisableReloadToLocation = false;
	Log_testinfo ("killed all");
	LocatorReloadEnterDisable("FortFrance_Brothel", "reload2_back", true);
	LocatorReloadEnterDisable(pchar.location.from_sea, "boat", false);
	BSCourtlyPassions_SeaBattle();

	DoQuestCheckDelay("hide_weapon", 2.0);
	DoQuestFunctionDelay("BSCourtlyPassions_kill_podsos_1", 2.5);
}

void BSCourtlyPassions_kill_podsos_1(string _quest)
{
	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_16_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}

void BSCourtlyPassions_fleeng(string _quest)
{
	pchar.currentsoundtrack = "Vein_Chase";
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "FortFrance_town", "goto", "goto34");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "gate_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_1.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_1.win_condition.l1.location = "FortFrance_exittown";
	PChar.quest.BSCourtlyPassions_fleeng_1.function = "BSCourtlyPassions_fleeng_1";
}

void BSCourtlyPassions_fleeng_1(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "FortFrance_exittown", "goto", "goto8");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_2.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_2.win_condition.l1.location = "Martinique_jungle_01";
	PChar.quest.BSCourtlyPassions_fleeng_2.function = "BSCourtlyPassions_fleeng_2";
}

void BSCourtlyPassions_fleeng_2(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Martinique_jungle_01", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_3.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_3.win_condition.l1.location = "Martinique_jungle_02";
	PChar.quest.BSCourtlyPassions_fleeng_3.function = "BSCourtlyPassions_fleeng_3";
}

void BSCourtlyPassions_fleeng_3(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Martinique_jungle_02", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_4.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_4.win_condition.l1.location = "Martinique_jungle_03";
	PChar.quest.BSCourtlyPassions_fleeng_4.function = "BSCourtlyPassions_fleeng_4";
}

void BSCourtlyPassions_fleeng_4(string _quest)
{
	
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Martinique_jungle_03", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_5.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_5.win_condition.l1.location = "Shore39";
	PChar.quest.BSCourtlyPassions_fleeng_5.function = "BSCourtlyPassions_fleeng_5";

	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_15_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}

void BSCourtlyPassions_fleeng_5(string _quest)
{
	UnLockWeapons("");
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("BS_Vein");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto1");
	LAi_ActorGoToLocation(sld, "reload", "sea", "", "", "", "", -1);
	DeleteAttribute(PChar, "MapBestTeleportDisable");
	BS_SpawnEnemies(3*MOD_SKILL_ENEMY_RATE + GetOfficersQuantity(pchar), PIRATE, "BSCourtlyPassions_kill_podsos");
}

void BSCourtlyPassions_SeaBattle()
{
	DeleteAttribute(PChar, "currentsoundtrack");
	Group_FindOrCreateGroup("BSCourtlyPassions_SeaBattle");
	Group_SetType("BSCourtlyPassions_SeaBattle", "pirate");
	sld = CharacterFromID("BS_Vein");
	//LAi_SetHP(sld, 20, 20);
	sld.Ship.Type = GenerateShipExt(SHIP_NEUFCHATEL, true, sld);
	string langtemp = "";
	if (LanguageGetLanguage() != "russian") { langtemp = "Ranger"; }
	else { langtemp = "Рейнджер"; }
	FantomMakeCoolestSailor(sld, SHIP_NEUFCHATEL, langtemp, CANNON_TYPE_CANNON_LBS24, 100, 100, 100);

	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 50);
	ChangeCrewExp(sld, "Soldiers", 50);

	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);
	UltimatePerksSet(sld);
	
	Fantom_SetBalls(sld, "war");

	LAi_SetImmortal(sld, false);
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_AddCharacter("BSCourtlyPassions_SeaBattle", sld.id);
	Group_SetGroupCommander("BSCourtlyPassions_SeaBattle", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

	Group_SetPursuitGroup("BSCourtlyPassions_SeaBattle", PLAYER_GROUP);
	Group_SetTaskRunaway("BSCourtlyPassions_SeaBattle", PLAYER_GROUP);
	Group_LockTask("BSCourtlyPassions_SeaBattle");

	Group_SetAddress("BSCourtlyPassions_SeaBattle", "Martinique", "Quest_ships", "quest_ship_0");

	pchar.quest.BSCourtlyPassions_fail_to_board.win_condition.l1 = "NPC_Death";
	pchar.quest.BSCourtlyPassions_fail_to_board.win_condition.l1.character = sld.id;
	PChar.quest.BSCourtlyPassions_fail_to_board.function = "BSCourtlyPassions_fail_to_board";
	pchar.BSCourtlyPassionsFail = true;
}

void BSCourtlyPassions_final(string _quest)
{
	ref chr;
	sld = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto1");
	chr = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(chr, "Shore39", "goto", "goto3");
	DeleteAttribute(pchar, "ContraInterruptWaiting");
	LAi_SetActorTypeNoGroup(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	sld.dialog.currentnode = "BS_KS_33";
}

void BSCourtlyPassions_finalRoyal(string _quest)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", "goto1");
	LAi_SetActorType(sld);
	sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
	sld.dialog.currentnode = "BS_KS_36";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void BSCourtlyPassions_fail_to_board(string _quest)
{
	if (CheckAttribute(pchar, "BSCourtlyPassionsFail"))
	{
		CloseQuestHeader("BSCourtlyPassions");
		AddQuestRecord("BSCourtlyPassions", "9");
		BS_QuestCleaning(true);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Куртуазные страсти --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Погоня начинается
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BS_BahamasArrival(string qName)
{
	SetQuestHeader("BSChaseBegun");
	AddQuestRecord("BSChaseBegun", "1");
	Flag_Change(PIRATE);
	pchar.BS_permanentblackflag = true;
}
void BSChaseBegun()
{	
	Group_FindOrCreateGroup("Flint_Group");
	Group_SetType("Flint_Group", "pirate");

	sld = CharacterFromID("Flint");
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.DeckDialogNode = "BS_PN_shipF";
	Group_AddCharacter("Flint_Group", sld.id);
	Group_SetGroupCommander("Flint_Group", sld.id);
	SetCrewQuantityFull(sld);
	ProcessHullRepair(sld, 100.0);
	ProcessSailRepair(sld, 100.0);
	DeleteAttribute(sld, "ship.blots");
	DeleteAttribute(sld, "ship.sails");
	RepairMasts(sld);
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
	
	string langtemp = "";
	if (LanguageGetLanguage() != "russian") { langtemp = "Ranger"; }
	else { langtemp = "Рейнджер"; }
	sld = GetCharacter(NPC_GenerateCharacter("BS_Vein", "BS_Vein", "man", "man", 99, PIRATE, -1, true));
	FantomMakeCoolestSailor(sld, SHIP_NEUFCHATEL, langtemp, CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
	Fantom_SetBalls(sld, "war");
	sld.name 	= GetConvertStr("Variable_black_sails_functions_0.3", "Names.txt");
	sld.lastname 	= GetConvertStr("Variable_black_sails_functions_0.2.1", "Names.txt");
	//sld.greeting = "pirat_common";
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.DeckDialogNode = "BS_PN_shipV";
	
	Group_AddCharacter("Flint_Group", sld.id);
	Fantom_SetBalls(sld, "war");
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);

	Group_SetTaskAttack("Flint_Group", PLAYER_GROUP);
	Group_LockTask("Flint_Group");
	
	int ig = Group_FindGroup("Flint_Group");
	
	AIGroups[ig].location = "Bahames";
	AIGroups[ig].pos.x = 1174.26;
	AIGroups[ig].Pos.z = 836.274;
	AIGroups[ig].Pos.ay = 0;

	PChar.quest.BSChaseBegun_shore.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_shore.win_condition.l1.location = "Shore69";
	PChar.quest.BSChaseBegun_shore.function = "BSChaseBegun_shore";
	SetFunctionLocationCondition("BS_Cinematic_Shore69_Begin", "Shore69", false);
}

void BSChaseBegun_shore(string q)
{
	InterfaceStates.Buttons.Save.enable = false;
	chrDisableReloadToLocation = true;
	ref chr;
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Shore69", "quest", "quest3");
	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	sld.dialog.currentnode = "BS_PN_1";
	LAi_SetImmortal(sld, true);

	chr = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(chr, "Shore69", "quest", "quest1");
	chr.name = GetConvertStrWithReplace("Variable_black_sails_functions_19", "Names.txt", "#space#", " ");
	chr.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_20", "Names.txt", "#space#", " ");
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Shore69", "quest", "quest2");
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);

	chr = GetCharacter(NPC_GenerateCharacter("BS_Rakham", "BS_Rakham", "man", "man", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(chr, "Shore69", "quest", "quest8");
	chr.name = GetConvertStrWithReplace("Variable_black_sails_functions_21", "Names.txt", "#space#", " ");
	chr.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_22", "Names.txt", "#space#", " ");
	//sld.greeting = "pirat_common";
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);

	chr = GetCharacter(NPC_GenerateCharacter("BS_Bony", "BS_Bony", "woman", "YokoDias", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(chr, "Shore69", "quest", "quest4");
	chr.name = GetConvertStrWithReplace("Variable_black_sails_functions_23", "Names.txt", "#space#", " ");
	chr.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_24", "Names.txt", "#space#", " ");
	//sld.greeting = "pirat_common";
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);
}

void BSChaseBegun_shore_fight()
{
	string sGroup = "BS_ChaseBegun_shore_fight_group";
	int i = 0;
	int irank = 0;
	for (i = 0; i < 44; i++)
	{
		irank = 15 + 7*MOD_SKILL_ENEMY_RATE + rand(3*MOD_SKILL_ENEMY_RATE);
		sld = GetCharacter(NPC_GenerateCharacter(sGroup+i, "off_eng_"+(rand(1)+1), "man", "man", irank, ENGLAND, 1, true));
		LAi_SetWarriorType(sld);
		Group_AddCharacter(sGroup, sld.id);
		LAi_group_MoveCharacter(sld, sGroup);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		if(i < 2) ChangeCharacterAddressGroup(sld, "Shore69", "goto", "goto8");
		if(i >= 2 && i < 8) ChangeCharacterAddressGroup(sld, "Shore69", "goto", "goto9");
		if(i >= 8 && i < 14) ChangeCharacterAddressGroup(sld, "Shore69", "goto", "goto11");
		if(i >= 14 && i < 20) ChangeCharacterAddressGroup(sld, "Shore69", "goto", "goto4");
		if(i >= 20 && i < 26) ChangeCharacterAddressGroup(sld, "Shore69", "goto", "goto6");
		if(i >= 26 && i < 36) ChangeCharacterAddressGroup(sld, "Shore69", "goto", "goto5");
		if(i >= 36 && i < 40) ChangeCharacterAddressGroup(sld, "Shore69", "goto", "goto7");
		if(i >= 40 && i < 44) ChangeCharacterAddressGroup(sld, "Shore69", "goto", "goto1");
	}
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
	LAi_group_SetCheckFunction(sGroup, "BSChaseBegun_shore_fightReCheck");
}

void BSChaseBegun_shore_fightReCheck(string qName)
{
	sld = CharacterFromID("BS_Vein");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.dialog.currentnode = "BS_PN_9";
			
	Group_DeleteGroup("Flint_Group");
	SetFunctionLocationCondition("BS_FindTheEnglishInTheBay", "Bahames", false);
}

void BS_FindTheEnglishInTheBay(string qName)
{
	string sCapId = "EnglishInTheBay";
    string sGroup = "Sea_" + sCapId + "1";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "pirate");
	for (int i = 1; i < 5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(sCapId+i, "off_eng_"+(rand(1)+1), "man", "man", 999, ENGLAND, -1, true));
		if (i < 3) sld.Ship.Type = GenerateShipExt(SHIP_HOLLGALEON_H, true, sld);
		if (i >= 3) sld.Ship.Type = GenerateShipExt(SHIP_ROSSIYA, true, sld);

		sld.rank_bonus = 6*MOD_SKILL_ENEMY_RATE;
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "CannonProfessional");
		sld.Ship.Mode = "war";
		Fantom_SetUpgrade(sld, "hunter");
		Fantom_SetCannons(sld, "pirate");
		Fantom_SetBalls(sld, "pirate");
		BS_CorrectShipGoods(sld);

		sld.AlwaysEnemy = true;
		sld.AnalizeShips = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		SetFantomParamHunter(sld);
		Group_AddCharacter(sGroup, sld.id);		
	}
	int ig = Group_FindGroup(sGroup);
	
	AIGroups[ig].location = "Bahames";
	AIGroups[ig].pos.x = -1003.95;
	AIGroups[ig].Pos.z = -615.026;
	AIGroups[ig].Pos.ay = 0;
	Group_SetGroupCommander(sGroup, sCapId + "1");
	Group_SetTaskNone(sGroup);
	PChar.quest.BattleSeaDefenceColonyWinner.win_condition.l1 = "Group_Death";
	PChar.quest.BattleSeaDefenceColonyWinner.win_condition.l1.group = sGroup;
	PChar.quest.BattleSeaDefenceColonyWinner.function = "BS_NassauAfterEnglishInTheBay";
	string langtemp = "";
	if (LanguageGetLanguage() != "russian") { langtemp = "I need to find and destroy the British ships"; }
	else { langtemp = "Мне нужно отыскать и уничтожить английские корабли"; }
	pchar.LockMapReload = langtemp;
	pchar.LockShoreReload = langtemp;
}

void BS_NassauAfterEnglishInTheBay(string qName)
{
	LocatorReloadEnterDisable("Shore69", "reload1_back", false);
	SetFunctionLocationCondition("BSChaseBegun_town", "Nassau_town", false);
	DeleteAttribute(pchar, "LockMapReload");
	DeleteAttribute(pchar, "LockShoreReload");
}

void BSChaseBegun_town(string q)
{
	pchar.currentsoundtrack = "The_Final_Battle";
	chrDisableReloadToLocation = true;
	BS_spawn_dead_podsos();
	ref chr;
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Nassau_town", "officers", "houseS1_1");
	LAi_SetActorType(sld);
	LAi_SetImmortal(sld, true);

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Nassau_town", "officers", "houseS1_2");
	LAi_SetStayTypeNoGroup(chr);
	chr.talker = 10;
	chr.dialog.currentnode = "BS_PN_15";
	LAi_SetImmortal(chr, true);

	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Nassau_town", "goto", "goto8");
	chr.name = GetConvertStrWithReplace("Variable_black_sails_functions_25", "Names.txt", "#space#", " ");
	chr.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_26", "Names.txt", "#space#", " ");
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);
}

void BS_spawn_dead_podsos()
{
	InterfaceStates.Buttons.Save.enable = false;
	aref grp;
	ref _location = &Locations[FindLocation(pchar.location)];
	makearef(grp, _location.locators.patrol);
	int maxPodsos = GetAttributesNum(grp);
	string cnd;
	for (int i = 1; i < maxPodsos; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BS_VeinPodsos"+i, "off_eng_"+(rand(1)+1), "man", "man", 99, ENGLAND, 3, true));
		ChangeCharacterAddressGroup(sld, _location.id, "patrol", GetAttributeName(GetAttributeN(grp, i)));
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_warrior_DialogEnable(sld, false);
		LAi_KillCharacter(sld);
		cnd = "l" + i;
	}
}

void BSChaseBegun_townhall(string q)
{
	pchar.currentsoundtrack = "The_Wrecks";
	BS_GatriHomeGuardsOff();
	chrDisableReloadToLocation = true;
	LAi_SetSitTypeNoGroup(pchar);
	ChangeCharacterAddressGroup(pchar, "Nassau_OfisGatri", "sit", "sit5");
	
	ref chr;
	
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "sit", "sit2");
	LAi_SetSitTypeNoGroup(sld);

	chr = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit3");
	LAi_SetSitTypeNoGroup(chr);
	chr.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	chr.dialog.currentnode = "BS_PN_21";
	LAi_tmpl_SetDialog(chr, pchar, -1.0);

	chr = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit4");
	LAi_SetSitTypeNoGroup(chr);

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit7");
	LAi_SetSitTypeNoGroup(chr);

	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit6");
	LAi_SetSitTypeNoGroup(chr);

	chr = CharacterFromID("gatri_temp");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest5");
	LAi_SetActorType(chr);
	CharacterTurnToLoc(chr, "reload", "reload1_back");
}

void BSChaseBegun_lock_townhall(string qName)
{
	sld = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	BSChaseBegun_SeaBattle();
	InterfaceStates.Buttons.Save.enable = true;	
	LocatorReloadEnterDisable("Nassau_town", "houseS1", true);

	PChar.quest.BSChaseBegun_Hispaniola.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_Hispaniola.win_condition.l1.location = "Hispaniola1";
	PChar.quest.BSChaseBegun_Hispaniola.function = "BSChaseBegun_Hispaniola";
}

void BSChaseBegun_FewDeaysLater(string qName)
{
	WaitDate("",0,0,3,3,3);
	SetLaunchFrameFormParam(GetConvertStr("Variable_black_sails_functions_1", "Frames.txt"), "", 0.1, 3.0);
	LaunchFrameForm();
	DoQuestFunctionDelay("BSChaseBegun_FewDeaysLater_Reload", 3.0);
}

void BSChaseBegun_FewDeaysLater_Reload(string q)
{
	ClearIslandShips("SantoDomingo");
    Colonies[FindColony("SantoDomingo")].DontSetShipInPort = true;
    Colonies[FindColony("SantoDomingo")].BSChaseBegun = true;
	DoQuestReloadToLocation("Nassau_OfisGatri", "reload", "reload1_back", "");
}

void BSChaseBegun_Hispaniola(string q)
{
	AddQuestRecord("BSChaseBegun", "5");
}

void BSChaseBegun_Fail(string q)
{
	CloseQuestHeader("BSChaseBegun");
	DeleteAttribute(Colonies[FindColony("SantoDomingo")], "DontSetShipInPort");
	if (CheckAttribute(Colonies[FindColony("SantoDomingo")], "BSChaseBegun"))
	{
		AddQuestRecord("BSChaseBegun", "7");
		DeleteAttribute(Colonies[FindColony("SantoDomingo")], "BSChaseBegun");
		BS_QuestCleaning(true);
	}
}

void EraseBSCharacters()
{
	if(GetCharacterIndex("Flint") != -1)
	{
		sld = CharacterFromID("Flint");
		sld.LifeDay = 0;
		if(CheckCompanionInCharacter(pchar, sld.id)) RemoveCharacterCompanion(PChar, sld);
	}
	if(GetCharacterIndex("gatri_temp") != -1)
	{
		sld = CharacterFromID("gatri_temp");
		sld.LifeDay = 0;
	}
	if(GetCharacterIndex("BS_Vein") != -1)
	{
		sld = CharacterFromID("BS_Vein");
		sld.LifeDay = 0;
		if(CheckCompanionInCharacter(pchar, sld.id)) RemoveCharacterCompanion(PChar, sld);
	}
	if(GetCharacterIndex("BS_Rakham") != -1)
	{
		sld = CharacterFromID("BS_Rakham");
		sld.LifeDay = 0;
	}
	if(GetCharacterIndex("BS_Bony") != -1)
	{
		sld = CharacterFromID("BS_Bony");
		sld.LifeDay = 0;
	}
	if(GetCharacterIndex("BS_Silver") != -1)
	{
		sld = CharacterFromID("BS_Silver");
		sld.LifeDay = 0;
	}
	if(GetCharacterIndex("BSUrka_enemyfleet") != -1)
	{
		sld = CharacterFromID("BSUrka_enemyfleet");
		sld.LifeDay = 0;
	}
	if(GetCharacterIndex("BSUrka") != -1)
	{
		sld = CharacterFromID("BSUrka");
		sld.LifeDay = 0;
	}
	for (int i = 1; i < 7; i++)
	{
		if(GetCharacterIndex("BSUrka_Curacao_enemyfleet"+i) != -1)
		{
			sld = CharacterFromID("BSUrka_Curacao_enemyfleet"+i);	sld.LifeDay = 0;
		}
	}
	DeleteAttribute(pchar, "LockMapReload");
	DeleteAttribute(pchar, "LockShoreReload");
}
void BSChaseBegun_EndQuest(string q)
{	
	TeleportCharacterToPos(pchar, 73.12008, 3.20824, 25.118425);
	sld = CharacterFromID("Flint");
	RemoveCharacterCompanion(PChar, sld);
	ProcessHullRepair(sld, 100.0);
	ProcessSailRepair(sld, 100.0);
	DeleteAttribute(sld, "ship.blots");
	DeleteAttribute(sld, "ship.sails");
	RepairMasts(sld);
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	TeleportCharacterToPos(sld, 74.198654, 3.126261, 22.670755);
	chrDisableReloadToLocation = true;
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "BS_PN_30";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
void BSChaseBegun_SeaBattle()
{
	Group_FindOrCreateGroup("BSChaseBegun_SeaBattle");
	Group_SetType("BSChaseBegun_SeaBattle", "pirate");

	Group_FindOrCreateGroup("Flint_Group");
	Group_SetType("Flint_Group", "pirate");

	ref chr = CharacterFromID("Flint");
	chr.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	chr.DeckDialogNode = "BS_PN_30_seabattle";
	Group_AddCharacter("Flint_Group", chr.id);
	Group_SetGroupCommander("Flint_Group", chr.id);
	Fantom_SetBalls(chr, "war");
	LAi_SetImmortal(chr, false);
	chr.AlwaysFriend = true;
	chr.Tasks.CanBoarding = false;
	chr.DontRansackCaptain = true;
	chr.AlwaysSandbankManeuver = true;
	SetCharacterRelationBoth(sti(chr.index), GetMainCharacterIndex(), RELATION_FRIEND);

	Group_SetAddress("Flint_Group", "Hispaniola1", "Quest_ships", "quest_ship_5");

	pchar.quest.BSChaseBegun_Fail.win_condition.c1 = "NPC_Death";
	pchar.quest.BSChaseBegun_Fail.win_condition.c1.character ="Flint";
	PChar.quest.BSChaseBegun_Fail.function = "BSChaseBegun_Fail";

	for (int i = 1; i < 9; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BSChaseBegun_SeaBattle"+i, "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));
		sld.Ship.Type = GenerateShipExt(GetShipTypeExt(3, 3, "war", SPAIN), true, sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		sld.Ship.Mode = "pirate";
		sld.Tasks.CanBoarding = false;
		Fantom_SetUpgrade(sld, "pirate");
		Fantom_SetCannons(sld, "pirate");
		Fantom_SetBalls(sld, "pirate");
		SetFantomParamHunter(sld);		
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		UltimatePerksSet(sld);
		
		Group_AddCharacter("BSChaseBegun_SeaBattle", sld.id);
		if (i == 1) Group_SetGroupCommander("BSChaseBegun_SeaBattle", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
	}
	Group_SetAddress("BSChaseBegun_SeaBattle", "Hispaniola1", "Quest_ships", "quest_ship_1");
	
	Group_SetTaskAttack("BSChaseBegun_SeaBattle", PLAYER_GROUP);
	Group_LockTask("BSChaseBegun_SeaBattle");	
	
	Group_SetTaskAttack("Flint_Group", "BSChaseBegun_SeaBattle");
	Group_LockTask("Flint_Group");
	PChar.quest.BSChaseBegun_CheckFlag.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_CheckFlag.win_condition.l1.location = "Hispaniola1";
	PChar.quest.BSChaseBegun_CheckFlag.function = "BSChaseBegun_CheckFlag";
}

void BS_ChaseBegun_WithFlintToNassau()
{
	DeleteAttribute(pchar, "LockMapReload");
	DeleteAttribute(pchar, "LockShoreReload");
	Group_DeleteGroup("Flint_Group");
	sld = CharacterFromID("Flint");
	DeleteAttribute(sld, "Tasks.CanBoarding");
	SetCompanionIndex(PChar, -1, GetCharacterIndex(sld.id));
}

void BSChaseBegun_CheckFlag(string q)
{
	if (sti(pchar.nation) != PIRATE)
	{
		sld = CharacterFromID("Flint");
		DeleteAttribute(sld, "AlwaysFriend");
		sld.AlwaysEnemy = true;
	}
	else
	{
		string langtemp = "";
		if (LanguageGetLanguage() != "russian") { langtemp = "I can't leave Flint here"; }
		else { langtemp = "Я не могу бросить здесь Флинта"; }
		pchar.LockMapReload = langtemp;
		pchar.LockShoreReload = langtemp;
	}
}

void BS_Cinematic_Shore69_Begin(string qName)
{
	LAi_SetStayType(pchar);
	DoQuestFunctionDelay("BS_Cinematic_Shore69_Process_1", 1.0);
}

void BS_Cinematic_Shore69_Process_1(string qName)
{
	StartQuestMovie(true, true, false);
	SetMusic("Vanes_Visions");
	LAi_FadeDelay(3.0, "");
	DoQuestFunctionDelay("BS_Cinematic_Shore69_Process_2", 2.0);
}
void BS_Cinematic_Shore69_Process_2(string qName)
{
	locCameraToPos(50.6629639, 3.9930797, 91.2482758, false);
	DoQuestFunctionDelay("BS_Cinematic_Shore69_Process_3", 4.0);
}

void BS_Cinematic_Shore69_Process_3(string qName)
{
	locCameraFlyToPosition(50.6629639, 3.9930797, 91.2482758, 49.6213150, 12.9346609, 91.5773697, 1.0, 300);
	pchar.funcaftermovie = "BS_Cinematic_Shore69_Process_4";
}

void BS_Cinematic_Shore69_Process_4()
{
	locCameraToPos(49.6213150, 12.9346609, 91.5773697, false);
	DoQuestFunctionDelay("BS_Cinematic_Shore69_Process_5", 2.0);
}

void BS_Cinematic_Shore69_Process_5(string qName)
{
	locCameraFlyToPosition(49.6213150, 12.9346609, 91.5773697, -54.7228699, 16.6609039, 120.8671417, 1.0, 800);
	pchar.funcaftermovie = "BS_Cinematic_Shore69_Process_6";
}

void BS_Cinematic_Shore69_Process_6()
{
	locCameraToPos(-54.7228699, 16.6609039, 120.8671417, false);
	DoQuestFunctionDelay("BS_Cinematic_Shore69_Process_7", 5.0);
}

void BS_Cinematic_Shore69_Process_7(string qName)
{
	locCameraFlyToPosition(-54.7228699, 16.6609039, 120.8671417, -27.2323818, 6.0508270, 75.6156235, 1.0, 250);
	pchar.funcaftermovie = "BS_Cinematic_Shore69_Process_8";
}

void BS_Cinematic_Shore69_Process_8()
{
	locCameraToPos(-27.2323818, 6.0508270, 75.6156235, false);
	DoQuestFunctionDelay("BS_Cinematic_Shore69_Process_9", 0.5);
}

void BS_Cinematic_Shore69_Process_9(string qName)
{
	LAi_FadeDelay(3.0, "");
	DoQuestFunctionDelay("BS_Cinematic_Shore69_The_End", 1.5);
}

void BS_Cinematic_Shore69_The_End(string qName)
{
	LAi_SetPlayerType(PChar);
	EndQuestMovie();
	locCameraResetState();
	locCameraTarget(pchar);
	DeleteAttribute(PChar, "funcaftermovie");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Погоня начинается --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Неуловимая «Урка»
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BSUrka_Negril()
{
	AddQuestRecord("BSUrka", "2");
	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_2_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}

void BSBons_SeaBattle(bool bonsAdmiral)
{
	int  i, irank, iclass, iqty;
	string langtemp = "";
    string sCapId = "BSBons";
    string sGroup = "Sea_" + sCapId + "1";
	string sScarboro = "";
	Group_FindOrCreateGroup(sGroup);
	iqty = 4+MOD_SKILL_ENEMY_RATE;
	if (bonsAdmiral) {iqty += MOD_SKILL_ENEMY_RATE;}
	for (i = 1; i < iqty; i++)
	{
		irank = 25 + 10*MOD_SKILL_ENEMY_RATE + rand(3*MOD_SKILL_ENEMY_RATE);		
		if (i == 1 && bonsAdmiral) irank = 50 + 20*MOD_SKILL_ENEMY_RATE;
		iclass = 4 - MOD_SKILL_ENEMY_RATE;
		if (iclass < 1) iclass = 1;
		if (i > 1) iclass = iclass + rand(1);
		sld = GetCharacter(NPC_GenerateCharacter("BSBons"+i, "off_eng_"+(rand(1)+1), "man", "man", irank, ENGLAND, 8, true));
		sld.Ship.Type = GenerateShipExt(GetShipTypeExt(iclass, iclass, "war", ENGLAND), true, sld);
		Group_AddCharacter(sGroup, sld.id);
		if (i == 1 && bonsAdmiral)
		{
			if (!CheckAttribute(pchar, "BSBonsSpawned"))
			{			
				if (LanguageGetLanguage() != "russian") { langtemp = "Fortune"; }
				else { langtemp = "Фортуна"; }
				FantomMakeCoolestSailor(sld, SHIP_DIANA, langtemp, CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
				FantomMakeCoolFighter(sld, 40+MOD_SKILL_ENEMY_RATE*10, 100, 100, "blade30", "pistol4", 250+MOD_SKILL_ENEMY_RATE*75);
				sld.Name = GetConvertStrWithReplace("Variable_black_sails_functions_27", "Names.txt", "#space#", " ");
				sld.Lastname = GetConvertStrWithReplace("Variable_black_sails_functions_28", "Names.txt", "#space#", " ");
				sld.Model = "BS_Billy";
				FaceMaker(sld);
				sld.SaveItemsForDead = true;
				sld.SuperShooter  = true;
				sld.money = 300000;
				sld.items.jewelry1 = 10+rand(5);
				sld.items.jewelry2 = 10+rand(5);
				sld.items.jewelry3 = 10+rand(5);
				sld.items.jewelry4 = 5+rand(5);
				sld.items.jewelry6 = rand(20);
				sld.items.jewelry7 = rand(50);
				sld.items.jewelry10 = rand(20);
				sld.items.jewelry14 = rand(20);
				sld.items.jewelry15 = rand(5);
				sld.items.jewelry18 = rand(50);
			}
			else
			{
				if (LanguageGetLanguage() != "russian") { langtemp = "Scarboro"; }
				else { langtemp = "Скарборо"; }
				FantomMakeCoolestSailor(sld, SHIP_MANOWAR, langtemp, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
				FaceMaker(sld);
				if (LanguageGetLanguage() != "russian") { langtemp = " with Scarboro at the helm"; }
				else { langtemp = " со 'Скарборо' во главе"; }
				sScarboro = langtemp;
				FantomMakeCoolFighter(sld, 50+MOD_SKILL_ENEMY_RATE*15+rand(5), 100, 100, "blade33", "howdah", 500+MOD_SKILL_ENEMY_RATE*150+rand(50));
				sld.name = GetConvertStrWithReplace("Variable_black_sails_functions_29", "Names.txt", "#space#", " ");
				sld.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_30", "Names.txt", "#space#", " ");
				sld.SaveItemsForDead = true;				
				if (bHardBoss) sld.AlwaysReload = true;
				sld.SuperShooter  = true;
				sld.money = 1250000;
				sld.items.jewelry1 = 20+rand(5);
				sld.items.jewelry2 = 20+rand(5);
				sld.items.jewelry3 = 20+rand(5);
				sld.items.jewelry4 = 11+rand(5);
				sld.items.jewelry6 = rand(50);
				sld.items.jewelry7 = rand(100);
				sld.items.jewelry10 = rand(50);
				sld.items.jewelry14 = rand(50);
				sld.items.jewelry15 = rand(10);
				sld.items.jewelry18 = rand(100);
				sld.items.GunEchin = 20+rand(5);
				LAi_SetCharacterUseBullet(sld, "GunEchin");
				pchar.quest.BSUrka_Scarboro.win_condition.l1 = "NPC_Death";
				pchar.quest.BSUrka_Scarboro.win_condition.l1.character ="BSBons1";
				PChar.quest.BSUrka_Scarboro.function = "BSUrka_Scarboro";
			}
		}
		if (i == 1) Group_SetGroupCommander(sGroup, sld.id);
		sld.mapEnc.type = "war";
		sld.mapEnc.Name = GetConvertStrWithReplace("Variable_black_sails_functions_31", "Names.txt", "#space#", " ") + sScarboro;
		if (bonsAdmiral){sld.mapEnc.worldMapShip = "quest_ship";}
		else{sld.mapEnc.worldMapShip = "Galleon_red";}		
		if (!bonsAdmiral || i > 1)
		{
			SetBaseShipData(sld);
			sld.Ship.Mode = "war";
			Fantom_SetUpgrade(sld, "pirate");
			Fantom_SetCannons(sld, "pirate");
			Fantom_SetBalls(sld, "pirate");
		}
		UltimatePerksSet(sld);
		SetCrewQuantityFull(sld);
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);
		BS_CorrectShipGoods(sld);		
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
	}
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);	
	Map_CreateFastWarrior("", sCapId + "1", 8);
}

void BS_Billi_Bons(string qName)
{
	sld = CharacterFromID("BSBons1_free");
	LAi_SetImmortal(sld, true);
	sld.ShipEnemyDisable = true;
}

void BS_Billi_Bons_NotEnemy()
{
	string sGroup = "Sea_BSBons1";
	Group_UnlockTask(sGroup);
	Group_SetTaskNone(sGroup);
	int BBGroupIndex = Group_FindGroup(sGroup);
	ref rGroup = Group_GetGroupByIndex(BBGroupIndex);
	int i = 0;
	int iCharacterIndex = 0;
	while (true)
	{
		iCharacterIndex = Group_GetCharacterIndexR(rGroup, i);
		if (iCharacterIndex < 0) {break;}
		SetCharacterRelationBoth(iCharacterIndex, GetMainCharacterIndex(), RELATION_FRIEND);
		sld = GetCharacter(iCharacterIndex);
		DeleteAttribute(sld, "AlwaysEnemy");
		LAi_SetImmortal(sld, true);
		sld.ShipEnemyDisable = true;
		sld.lifeDay = 0;
		i++;
	}
}

void BSUrka_Pirates_town(string q)
{
	pchar.currentsoundtrack = "Nassau_Shores";
	chrDisableReloadToLocation = true;
	ref chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Nassau_Town", "goto", "goto40");
	LAi_SetActorTypeNoGroup(chr);
	LAi_SetImmortal(chr, true);
	sld = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(sld, "Nassau_Town", "goto", "goto37");
	LAi_SetImmortal(sld, true);
	LAi_SetCitizenTypeNoGroup(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_ActorFollow(chr, sld, "", -1);
	
	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, "Nassau_Town", "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	LAi_SetImmortal(sld, true);
	PChar.quest.BSChaseBegun_townhall.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_townhall.win_condition.l1.location = "Nassau_OfisGatri";
	PChar.quest.BSChaseBegun_townhall.function = "BSUrka_Pirates_town_residence_Dialogue";
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1 = "locator";
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.location = "Nassau_town";
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.locator_group = "reload";
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.locator = "houseS1";
	PChar.quest.BSUrka_Pirates_town_residence.function = "BSUrka_Pirates_town_residence";
}

void BSUrka_Pirates_town_residence(string qname)
{
	DoReloadCharacterToLocation("Nassau_OfisGatri","officers","reload1_3");
}

void BSUrka_Pirates_town_residence_Dialogue(string qname)
{	
	pchar.currentsoundtrack = "Clamanda";
	LAi_SetSitTypeNoGroup(pchar);
	ChangeCharacterAddressGroup(pchar, "Nassau_OfisGatri", "sit", "sit5");
	ref chr;
	
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "sit", "sit2");
	LAi_SetSitTypeNoGroup(sld);
	sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
	sld.dialog.currentnode = "BS_NU_18";
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
	
	chr = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit3");
	LAi_SetSitTypeNoGroup(sld);

	chr = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest3");
	LAi_SetActorType(chr);
	CharacterTurnToLoc(chr, "sit", "sit5");

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit7");
	LAi_SetSitTypeNoGroup(chr);

	chr = CharacterFromID("gatri_temp");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest5");
	LAi_SetActorType(chr);
	CharacterTurnToLoc(chr, "reload", "reload1_back");
	sld = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	LAi_CharacterEnableDialog(sld);
	sld = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void BSUrka_Nassau_Ending()
{
	pchar.currentsoundtrack = "Clamanda";
	ChangeCharacterAddressGroup(pchar, "Nassau_OfisGatri", "sit", "sit5");
	LAi_SetSitTypeNoGroup(pchar);
	ref chr;
	
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "sit", "sit2");
	LAi_SetSitTypeNoGroup(sld);	
	sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
	sld.dialog.currentnode = "BS_NU_50";
	LAi_tmpl_SetDialog(sld, pchar, -1.0);

	chr = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest3");
	LAi_SetActorType(chr);
	CharacterTurnToLoc(chr, "sit", "sit5");

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit7");
	LAi_SetSitTypeNoGroup(chr);

	chr = CharacterFromID("gatri_temp");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest5");
	LAi_SetActorType(chr);
	CharacterTurnToLoc(chr, "reload", "reload1_back");
}

void BS_BSUrka_NassauFlintDialogue(string qName)
{
	DeleteAttribute(PChar, "currentsoundtrack");
	LAi_SetPlayerType(PChar);
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Nassau_Town", "officers", "HouseS1_1");
	LAi_SetActorType(sld);
	LAi_SetStayTypeNoGroup(sld);
	CharacterTurnToLoc(sld, "officers", "HouseS1_3");
}

void BSUrka_Curacao_SeaBattle()
{
	int  i, irank;
	string sGroup = "BSUrka_Curacao_SeaBattle";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "pirate");
	
	for (i = 1; i < 7; i++)
	{
		irank = 25 + 8*MOD_SKILL_ENEMY_RATE + rand(2*MOD_SKILL_ENEMY_RATE);
		sld = GetCharacter(NPC_GenerateCharacter(sGroup+i, "off_spa_"+(rand(1)+1), "man", "man", irank, SPAIN, -1, true));
		sld.Ship.Type = GenerateShipExt(GetShipTypeExt(3, 2, "war", SPAIN), true, sld);
		SetBaseShipData(sld);
		Group_AddCharacter(sGroup, sld.id);
		if (i == 1) Group_SetGroupCommander(sGroup, sld.id);

		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		UltimatePerksSet(sld);

		sld.Ship.Mode = "war";
		Fantom_SetUpgrade(sld, "pirate");
		Fantom_SetCannons(sld, "pirate");
		Fantom_SetBalls(sld, "pirate");
		
		BS_CorrectShipGoods(sld);

		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;		
	}
	
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetPursuitGroup(sGroup, PLAYER_GROUP);
	Group_SetTaskAttack(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_SetAddress(sGroup, "Curacao", "", "");
	
	PChar.quest.BattleSeaDefenceColonyWinner.win_condition.l1 = "Group_Death";
	PChar.quest.BattleSeaDefenceColonyWinner.win_condition.l1.group = sGroup;
	PChar.quest.BattleSeaDefenceColonyWinner.function = "BSUrka_Curacao_EndSeaBattle";

	PChar.quest.BSUrka_Curacao_Entered.win_condition.l1 = "location";
	PChar.quest.BSUrka_Curacao_Entered.win_condition.l1.location = "Curacao";
	PChar.quest.BSUrka_Curacao_Entered.function = "BSUrka_Curacao_SeaBattleStarted";
}

void BSUrka_Curacao_SeaBattleStarted(string q)
{
	if (!CheckAttribute(pchar, "BSFinish"))
	{
		string langtemp = "";
		if (LanguageGetLanguage() != "russian") { langtemp = "First we have to finish off the Spanish squadron"; }
		else { langtemp = "Сперва нужно добить испанскую эскадру"; }
		pchar.LockMapReload = langtemp;
		pchar.LockShoreReload = langtemp;
	}
}

void BSUrka_Curacao_EndSeaBattle(string q)
{
	Sea_CabinStartNow();
	pchar.quest.BSUrka_Curacao_Cabin.win_condition.l1          = "location";
	pchar.quest.BSUrka_Curacao_Cabin.win_condition.l1.location = Get_My_Cabin();
	pchar.quest.BSUrka_Curacao_Cabin.function             = "BSUrka_Curacao_CabinTalk";
}

void BSUrka_Curacao_CabinTalk(string q)
{
	chrDisableReloadToLocation = true;
	LAi_LockFightMode(pchar, true);
	sld = CharacterFromID("Flint");
	sld.dialog.currentnode = "BS_NU_35";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindNearestFreeLocator2Pchar("rld"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void BSUrka_Curacao_Shore(string q)
{
	ref locLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, true);
	chrDisableReloadToLocation = true;
	LAi_LockFightMode(pchar, true);
	sld = CharacterFromID("Flint");
	sld.dialog.currentnode = "BS_NU_37";
	ChangeCharacterAddressGroup(sld, pchar.location, "smugglers", "smugglerload");
	LAi_SetStayType(sld);
	sld.talker = 10;
	sld = GetCharacter(NPC_GenerateCharacter("BSUrka_Prisoner", "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, 3, true));
	ChangeCharacterAddressGroup(sld, pchar.location, "smugglers", "smuggler01");
	LAi_SetActorType(sld);
	sld = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(sld, pchar.location, "smugglers", "smuggler02");
	LAi_SetActorType(sld);
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
	LAi_SetActorType(sld);
}

void BSUrka_BonyHits(string qName)
{
	sld = CharacterFromId("BSUrka_Prisoner");
	ref chr = CharacterFromId("BS_Bony");
	LAi_SetActorTypeNoGroup(chr);
	LAi_ActorTurnToCharacter(chr, sld);
	LAi_ActorAnimation(chr, "Shot", "", 1.9);
    DoQuestFunctionDelay("BSUrka_BonyHits_1", 0.8);
}
void BSUrka_BonyHits_1(string qName)
{
	DialogExit();
	sld = CharacterFromId("BSUrka_Prisoner");
	ref chr = CharacterFromId("BS_Bony");
	LAi_KillCharacter(sld);
    DoQuestFunctionDelay("BSUrka_BonyHits_2", 0.25);
}
void BSUrka_BonyHits_2(string qName)
{
	ref chr = CharacterFromId("BS_Bony");
	Lai_SetStayType(chr);

	sld = CharacterFromID("BS_Vein");
	sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
	sld.dialog.currentnode   = "BS_NU_41";
	pchar.InstantDialog = sld.id;
	DoQuestFunctionDelay("InstantDialog", 1.3);

	ref locLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, false);
}
void BSUrka_Found(string qName)
{
	AddQuestRecord("BSUrka", "8");
}

void BSUrka_PlaceUrka()
{
	//Урка
	Group_FindOrCreateGroup("BSUrka");
	Group_SetType("BSUrka", "pirate");

	sld = GetCharacter(NPC_GenerateCharacter("BSUrka", "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));

	sld.Ship.Type = GenerateShipExt(SHIP_WASA, true, sld);
	sld.Ship.Name = GetConvertStrWithReplace("Variable_black_sails_functions_36", "Names.txt", "#space#", " ");
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;

	sld.LockBoat = true;
	sld.ShipEnemyDisable = true;
	sld.AlwaysFriend = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_AddCharacter("BSUrka", sld.id);
	LAi_group_MoveCharacter(sld, "BSUrka");
	Group_SetGroupCommander("BSUrka", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);

	int iMast = 0;
	int iMastQty = 4;
	string sMast = "";
	for(int m=1; m <= iMastQty; m++)
	{
		sMast = "mast" + m;
		sld.ship.masts.(sMast) = true;
	}
	sld.ship.HP = sti(sld.ship.HP) / 4;
	SetCrewQuantity(sld, 0);
	LAi_SetImmortal(sld, true);

	Group_SetAddress("BSUrka", "Cumana", "quest_ships", "quest_ship_9");

	//Самовар
	Group_FindOrCreateGroup("BSUrka_SeaBattle");
	Group_SetType("BSUrka_SeaBattle", "pirate");

	sld = GetCharacter(NPC_GenerateCharacter("BSUrka_enemyfleet", "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));
	sld.Ship.Type = GenerateShipExt(SHIP_SANFELIPE, true, sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
	
	Fantom_SetBalls(sld, "pirate");
	BS_CorrectShipGoods(sld);

	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);

	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);

	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "CannonProfessional");

	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_AddCharacter("BSUrka_SeaBattle", sld.id);
	Group_SetGroupCommander("BSUrka_SeaBattle", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

	Group_SetTaskAttack("BSUrka_SeaBattle", PLAYER_GROUP);
	Group_LockTask("BSUrka_SeaBattle");

	Group_SetAddress("BSUrka_SeaBattle", "Cumana", "Quest_ships", "quest_ship_9");

	SetFunctionNPCDeathCondition("BSUrka_SeaBattleEnded", "BSUrka_enemyfleet", false);
}

void BSUrka_SeaBattleEnded(string q)
{
	AddQuestRecord("BSUrka", "8_1");
	pchar.quest.BSUrka_ShoreBattle.win_condition.l1          = "location";
	pchar.quest.BSUrka_ShoreBattle.win_condition.l1.location = "Shore20";
	pchar.quest.BSUrka_ShoreBattle.function             = "BSUrka_ShoreBattle";
	AddGeometryToLocation("Shore20", "smg");
}

void BSUrka_ShoreBattle(string q)
{
	ref chr;
	string attrName, sLoc, sLoc_2, relation;
	int i, iRnd, iNation, irank;

	relation = LAI_GROUP_PLAYER;
	sLoc = "Shore20";
	iNation = SPAIN;

	chrDisableReloadToLocation = true;

	chr = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);

	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);

	chr = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);

	chr = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);

	iRnd = 15 - GetOfficersQuantity(pchar);
	PChar.GenQuestFort.FarLocator = false;
	sLoc = LAi_FindNPCLocator("officers");
	for (i = 1; i < iRnd; i++)
	{
		if (i % 3 != 0)
		{
		chr = SetFantomDefenceForts("officers", sLoc, PIRATE, relation);
		}
		else
		{
		chr = SetFantomDefenceForts("enc02", "",PIRATE, relation);
		}
		FantomMakeCoolFighterWRankDepend(chr,sti(pchar.rank),25+rand(75),25+rand(75),50);
	}
	Pchar.GenQuestFort.FarLocator = true;

	//enemy
	iRnd = 30+MOD_SKILL_ENEMY_RATE*15;
	irank = 20 + 7*MOD_SKILL_ENEMY_RATE + rand(3*MOD_SKILL_ENEMY_RATE);
	Pchar.GenQuestFort.FarLocator = true;
	sLoc = LAi_FindNPCLocator("goto");
	sLoc_2 = LAi_FindNPCLocator("smugglers");
	for (i = 1; i < iRnd; i++)
	{
		if (i % 2 == 0)
		{
		chr = SetFantomDefenceForts("goto", sLoc, iNation, "BSUrkaShore");
		}
		else
		{
			chr = SetFantomDefenceForts("smugglers", sLoc_2, iNation, "BSUrkaShore");
		}
		chr.id = "pirate_" + i;
		FantomMakeCoolFighterWRankDepend(chr,irank,64+rand(12*MOD_SKILL_ENEMY_RATE),64+rand(12*MOD_SKILL_ENEMY_RATE),40*MOD_SKILL_ENEMY_RATE);
	}
	//натравим.
	LAi_group_SetHearRadius("BSUrkaShore", 100.0);
	LAi_group_FightGroupsEx("BSUrkaShore", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
	LAi_group_FightGroupsEx("BSUrkaShore", relation, true, Pchar, -1, false, false);

	LAi_group_SetCheckFunction("BSUrkaShore", "BSUrka_AfterShoreBattle");
	LAi_SetFightMode(pchar, true);
}

void BSUrka_AfterShoreBattle(string qName)
{
	RemoveGeometryFromLocation("Shore20", "smg");
	ref chr, rGroup;
	string sGroup;
	Group_DeleteGroup("BSUrka");
	chr = CharacterFromID("BSUrka");
	chr.LifeDay = 0;
	chr = CharacterFromID("Flint");
	chr.dialog.currentnode   = "BS_NU_45";
	DoQuestCheckDelay("hide_weapon", 2.0);
	LAi_SetActorType(chr);
	LAi_ActorDialog(chr, pchar, "", -1, 0);
}

void BSUrka_Scarboro(string q)
{
	sld = CharacterFromID("Flint");
	if(LAi_IsDead(sld))
	{
		AddQuestRecord("BSHangover", "72");
	}
	else 
	{
		AddQuestRecord("BSUrka", "11"); 
	}
}

void BSUrka_Fail(string q)
{
	AddQuestRecord("BSUrka", "12");
	CloseQuestHeader("BSUrka");
	PChar.quest.BSChaseBegun_Fail.over = "yes";
	PChar.quest.BSUrka_Fail1.over = "yes";
	PChar.quest.BSUrka_Fail2.over = "yes";
	PChar.quest.BSUrka_Curacao_EndSeaBattle.over = "yes";
	PChar.quest.BSUrka_SeaBattleEnded.over = "yes";
	BS_QuestCleaning(true);
}

void BSUrka_Poison()
{
	sld = CharacterFromID("Flint");
	LAi_SetSitTypeNoGroup(sld);
	locCameraToPos(4.0085573, 0.2911763, 4.8491907, false);
	locCameraTarget(sld);
	ChangeShowIntarface();
	DoQuestFunctionDelay("BSUrka_Poison_1", 3);
	DoQuestFunctionDelay("BSUrka_Poison_2", 5);
	DoQuestFunctionDelay("BSUrka_Poison_3", 7);
	DoQuestFunctionDelay("BSUrka_Poison_4", 9);
	DoQuestFunctionDelay("BSUrka_Poison_5", 10);
	DoQuestFunctionDelay("BSUrka_Poison_6", 12);
	if (!WhisperIsHere())
	{
		//DoQuestFunctionDelay("BSUrka_PoisonOfficers", 13);
		DoQuestFunctionDelay("BSUrka_PoisonSelf", 14.0);
		DoQuestFunctionDelay("BSUrka_Poison_Flint", 17.0);
	}

	
}
void BSUrka_PoisonSelf(string q)
{
	SetCharacterTask_Dead(pchar);
}
/*
void BSUrka_PoisonOfficers(string q)
{
	int idx;
	for(int i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		idx = GetOfficersIndex(PChar,i);
		if (idx != -1) {
			ref offchar = GetCharacter(idx);
			SetCharacterTask_Dead(offchar);
		}
	}
}
*/
void BSUrka_Poison_1(string q)
{
	sld = CharacterFromID("BS_Silver");
	SetCharacterTask_Dead(sld);
	Log_Info(GetConvertStrWithReplace("Variable_black_sails_functions_5", "Logs.txt", "#space#", " "));
}
void BSUrka_Poison_2(string q)
{
	sld = CharacterFromID("BS_Rakham");
	SetCharacterTask_Dead(sld);
}
void BSUrka_Poison_3(string q)
{
	sld = CharacterFromID("BS_Vein");
	SetCharacterTask_Dead(sld);
}
void BSUrka_Poison_4(string q)
{
	sld = CharacterFromID("BS_Bony");
	SetCharacterTask_Dead(sld);

	if (WhisperIsHere())
	{
		LAi_SetPlayerType(pchar);
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_20_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}
void BSUrka_Poison_5(string q)
{
	sld = CharacterFromID("gatri_temp");
	SetCharacterTask_Dead(sld);
	Log_Info(GetConvertStrWithReplace("Variable_black_sails_functions_6", "Logs.txt", "#space#", " "));
}
void BSUrka_Poison_6(string q)
{
	sld = CharacterFromID("BS_Maks");
	SetCharacterTask_Dead(sld);
}
void BSUrka_Poison_Flint(string q)
{
	BSUrka_FewDaysLater();
}

void BSUrka_FewDaysLater()
{
	WaitDate("",0,0,3,3,3);
	SetLaunchFrameFormParam(GetConvertStr("Variable_black_sails_functions_2", "Frames.txt"), "", 0.1, 3.0);
	LaunchFrameForm();
	DoQuestFunctionDelay("BSUrka_FewDaysLater_Reload", 3.0);
}

void BSUrka_FewDaysLater_Reload(string q)
{
	DeleteAttribute(PChar, "currentsoundtrack");
	ChangeShowIntarface();
	DoReloadCharacterToLocation("Nassau_tavern_upstairs","goto","goto1");
	pchar.quest.BSHangover_Start.win_condition.l1          = "location";
	pchar.quest.BSHangover_Start.win_condition.l1.location = "Nassau_tavern_upstairs";
	pchar.quest.BSHangover_Start.function             = "BSHangover_Start";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Неуловимая «Урка» --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Тяжелое похмелье --     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BSHangover_Start(string q)
{
	LAi_SetPlayerType(pchar);
	chrDisableReloadToLocation = false;
	CloseQuestHeader("BSUrka");
	SetQuestHeader("BSHangover");
	AddQuestRecord("BSHangover", "1");

	pchar.quest.BSHangover_Downstairs.win_condition.l1          = "location";
	pchar.quest.BSHangover_Downstairs.win_condition.l1.location = "Nassau_tavern";
	pchar.quest.BSHangover_Downstairs.function             = "BSHangover_Downstairs";

	if (WhisperIsOfficer())
	{
		sld = CharacterFromID(pchar.WhisperId);
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
		SaveOldDialog(sld);
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_6_WhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
	}
}

void BSHangover_Downstairs(string q)
{
	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
	
	if (CheckAttribute(pchar, "BSBonsAccept"))
	{
		sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
		sld.dialog.currentnode = "BS_F3_1";
	}
	else
	{
		sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
		sld.dialog.currentnode = "BS_F1_5";
	}
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	sld.talker = 10;
}

void BSHangover_PortRoyal(string q)
{
	BSCourtlyPassions_finalRoyal("");
	sld = CharacterFromID("BS_Maks");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_8_MaksRoyal";
}

void BSHangover_Vein(string q)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
	StartInstantDialog("BS_Vein", "BS_F1_14", "Quest\BlackSails\BS_Final_1.c");
}

void BSHangover_RoyalVein(string q)
{
	chrDisableReloadToLocation = true;

	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto7");

	sld = CharacterFromID("PortRoyal_hostess");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_16";
}

void BSHangover_SearchStingerCheck()
{
	if(sti(pchar.BSSearchStinger) == 7)
	{
		AddQuestRecord("BSHangover", "6");
		LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
		pchar.quest.BSHangover_Jail.win_condition.l1          = "location";
		pchar.quest.BSHangover_Jail.win_condition.l1.location = "Bridgetown_prison";
		pchar.quest.BSHangover_Jail.function             = "BSHangover_Jail";

		if (WhisperIsHere())
		{
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "BS_11_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
		}
	}
}

void BSHangover_Jail(string q)
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("BSHangover_Jail_1", 0);
}
void BSHangover_Jail_1(string q)
{
	sld = CharacterFromID("BridgetownJailOff");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_SearchStinger";
}

void BSHangover_StingerFound(string q)
{
	chrDisableReloadToLocation = true;
	LockWeapons("");
	sld = CharacterFromID("BS_Silver");
	Lai_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto61");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_19";
}
void BSHangover_VeinFollows(string q)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	Lai_SetActorTypeNoGroup(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);

	LocatorReloadEnterDisable("Bridgetown_town", "gate_back", true);
	LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", true);
	LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", true);
	LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", true);
	LocatorReloadEnterDisable("Bridgetown_exittown", "reload1_back", true);
}

void BSHangover_FewDaysLater()
{
	WaitDate("",0,0,3,3,3);
	SetLaunchFrameFormParam(GetConvertStr("Variable_black_sails_functions_3", "Frames.txt"), "", 0.1, 3.0);
	LaunchFrameForm();
	DoQuestFunctionDelay("BSHangover_FewDaysLater_Reload", 3.0);
}

void BSHangover_FewDaysLater_Reload(string q)
{
	DoReloadCharacterToLocation("Bridgetown_tavern_upstairs","goto","goto1");
	pchar.quest.BSHangover_horse.win_condition.l1          = "location";
	pchar.quest.BSHangover_horse.win_condition.l1.location = "Bridgetown_tavern_upstairs";
	pchar.quest.BSHangover_horse.function             = "BSHangover_horse";
}

void BSHangover_horse(string q)
{
	sld = CharacterFromID("BS_Vein");
	Lai_SetStayTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	sld = GetCharacter(NPC_GenerateCharacter("BSHangover_horse", "horse0"+(rand(7)+1), "woman", "woman", 1, PIRATE, 0, false));
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_29";
	Lai_SetStayTypeNoGroup(sld);
	sld.talker = 10;

	LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
	LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
	LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
	LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
	LocatorReloadEnterDisable("Bridgetown_exittown", "reload1_back", false);
	LocatorReloadEnterDisable("Shore5", "boat", true);

	string langtemp = "";
	if (LanguageGetLanguage() != "russian") { langtemp = "There's no way in hell I'm leaving here without Flint!"; }
	else { langtemp = "Чёрта с два я уплыву отсюда без Флинта!"; }
	pchar.LockMapReload = langtemp;

	pchar.quest.BSHangover_Cave.win_condition.l1          = "location";
	pchar.quest.BSHangover_Cave.win_condition.l1.location = "barbados_cave";
	pchar.quest.BSHangover_Cave.function             = "BSHangover_Cave";

	if (WhisperIsOfficer())
	{
		sld = CharacterFromID(pchar.WhisperId);
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
	}
}

void BSHangover_Cave(string q)
{
	chrDisableReloadToLocation = true;
	LAi_LocationDisableMonGenTimer("barbados_cave", 3);
	LAi_LocationDisableToughSkeletonTimer("barbados_cave", 3); //ПК не пускать

	sld = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(sld, pchar.location, "item", "berglar1");
	LAi_SetWarriorType(sld);
	//LAi_SetHP(sld, 2000, 2000);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_SetImmortal(sld, true);
	DoQuestFunctionDelay("BSHangover_SilverMortality", 35);

	string cnd;
	for (int i = 1; i <= 12; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DeSouzaHunter"+sti(i), "OZG_" + (rand(6) + 1), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE*3 * 2, PIRATE, 0, true));

		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		sld.LifeDay = 0;

		cnd = "l" + i;
		pchar.quest.BSHangover_CaveAfterBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.BSHangover_CaveAfterBattle.win_condition.(cnd).character ="DeSouzaHunter"+sti(i);

		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto"+i);
	}
	PChar.quest.BSHangover_CaveAfterBattle.function = "BSHangover_CaveAfterBattle";
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

void BSHangover_CaveAfterBattle(string qName)
{
	sld = CharacterFromID("BS_Silver");
	sld.dialog.currentnode   = "BS_F1_32";
	if(LAi_IsDead(sld))
	{
		DeleteCharacter(sld);
		LAi_SetCurHPMax(sld);
		DoQuestFunctionDelay("BSHangover_CaveAfterBattle_1", 0);
		sld.dialog.currentnode   = "BS_F1_32_beaten";
	}
	else
	{
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}

	pchar.quest.BSHangover_CaveEntrance.win_condition.l1          = "location";
	pchar.quest.BSHangover_CaveEntrance.win_condition.l1.location = "barbados_CaveEntrance";
	pchar.quest.BSHangover_CaveEntrance.function             = "BSHangover_CaveEntrance";
}

void BSHangover_CaveAfterBattle_1(string qName)
{
	sld = CharacterFromID("BS_Silver");
	LAi_SetGroundSitTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "item", "berglar1");
	sld.CantLoot = true;
}

void BSHangover_SilverMortality(string qName)
{
	sld = CharacterFromID("BS_Silver");
	LAi_SetImmortal(sld, false);
	sld.DontClearDead = true;
}

void BSHangover_CaveEntrance(string qName)
{
	/*PChar.quest.BSChaseBegun_Fail.over = "yes";
	PChar.quest.BSUrka_Fail1.over = "yes";
	PChar.quest.BSUrka_Fail2.over = "yes";
	PChar.quest.BSUrka_Curacao_EndSeaBattle.over = "yes";
	PChar.quest.BSUrka_SeaBattleEnded.over = "yes";
	pchar.quest.BSCourtlyPassions_DontStart.over = "yes";*/
	chrDisableReloadToLocation = true;
	LAi_LocationDisableToughSkeletonTimer("barbados_cave", -1);
	int i = 0;
	for (i = 1; i <= 4; i++)
	{
		if(i == 1)	sld = CharacterFromID("BS_Vein");
		if(i == 2)	sld = CharacterFromID("BS_Silver");
		if(i == 3)	sld = CharacterFromID("BS_Rakham");
		if(i == 4)	sld = CharacterFromID("BS_Bony");
		LAi_SetHP(sld, 1000 - MOD_SKILL_ENEMY_RATE*3 * 50, 1000);
		ChangeCharacterAddressGroup(sld, pchar.location, "enc01", "enc01_02");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_SetImmortal(sld, false);
		sld.DontClearDead = true;
		sld.CantLoot = true;
	}

	string cnd;
	for (i = 1; i <= 20; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DeSouzaHunter"+sti(i), "OZG_" + (rand(6) + 1), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE*3 * 2, PIRATE, 0, true));

		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		sld.LifeDay = 0;

		cnd = "l" + i;
		pchar.quest.BSHangover_CaveEntranceAfterBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.BSHangover_CaveEntranceAfterBattle.win_condition.(cnd).character ="DeSouzaHunter"+sti(i);

		ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster"+(rand(2)+1));
	}
	PChar.quest.BSHangover_CaveEntranceAfterBattle.function = "BSHangover_CaveEntranceAfterBattle";
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_SetFightMode(PChar, true);
}

void BSHangover_CaveEntranceAfterBattle(string qName)
{
	AddQuestRecord("BSHangover", "8");
	BSHangover_IsEveryoneOkay();
	DoQuestFunctionDelay("BSHangover_CaveEntranceAfterBattle_2", 3);
	DoQuestFunctionDelay("BSHangover_CaveEntranceAfterBattle_1", 5);
	
	sld = CharacterFromID("Flint");
	Group_FindOrCreateGroup("Flint_Group");
	Group_SetType("Flint_Group", "pirate");
	Group_AddCharacter("Flint_Group", sld.id);
	Group_SetGroupCommander("Flint_Group", sld.id);
	sld.AlwaysEnemy = true;
	DeleteAttribute(sld, "AlwaysFriend");
	BSRepairShip(sld);
	BS_CorrectShipGoods(sld);
	DeleteAttribute(sld, "Abordage.Enable");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_35";
	LAi_SetImmortal(sld, false);
	pchar.FlintBoardingDialog = true;
	Group_SetAddress("Flint_Group", "Barbados", "Quest_ships", "quest_ship_7");
}

void BSHangover_CaveEntranceAfterBattle_2(string qName)
{
	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_12_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}
void BSHangover_CaveEntranceAfterBattle_1(string qName)
{
	sld = CharacterFromID("BS_Vein");
	Lai_SetStayTypeNoGroup(sld);
	sld.dialog.currentnode = "BS_F1_34";
	sld.talker = 10;
}

void BSHangover_IsEveryoneOkay()
{
	for (int i = 1; i <= 4; i++)
	{
		if(i == 1)	sld = CharacterFromID("BS_Vein");
		if(i == 2)	sld = CharacterFromID("BS_Silver");
		if(i == 3)	sld = CharacterFromID("BS_Rakham");
		if(i == 4)	sld = CharacterFromID("BS_Bony");
		Lai_SetActorTypeNoGroup(sld);
		if(LAi_IsDead(sld))
		{
			if(!CheckAttribute(pchar, "BSHangover_IsEveryoneOkay"))
			{
				pchar.BSHangover_IsEveryoneOkay = true;
				SetLaunchFrameFormParam(GetConvertStr("Variable_black_sails_functions_4", "Frames.txt"), "", 0.1, 3.0);
				LaunchFrameForm();
			}
			DeleteCharacter(sld);
			LAi_SetCurHPMax(sld);
			sld.RezMe = true;
			DoQuestFunctionDelay("BSHangover_IsEveryoneOkay_1", 0);
		}
	}

	pchar.quest.BSHangover_Fail1.win_condition.c1 = "NPC_Death";
	pchar.quest.BSHangover_Fail1.win_condition.c1.character ="Flint";
	PChar.quest.BSHangover_Fail1.function = "BSHangover_Fail";

	pchar.quest.BSHangover_Fail2.win_condition.c1 = "NPC_Death";
	pchar.quest.BSHangover_Fail2.win_condition.c1.character ="BS_Vein";
	PChar.quest.BSHangover_Fail2.function = "BSHangover_Fail";
}

void BSHangover_IsEveryoneOkay_1(string q)
{
	for (int i = 1; i <= 4; i++)
	{
		if(i == 1)	sld = CharacterFromID("BS_Vein");
		if(i == 2)	sld = CharacterFromID("BS_Silver");
		if(i == 3)	sld = CharacterFromID("BS_Rakham");
		if(i == 4)	sld = CharacterFromID("BS_Bony");

		if(CheckAttribute(sld, "RezMe"))
		{
			DeleteAttribute(sld, "RezMe")
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto1");
		}
	}
}

void BSHangover_Fail(string q)
{
	CloseQuestHeader("BSHangover");
	BS_QuestCleaning(true);
}
void BSHangover_FlintFight()
{
	for (int i = 1; i <= 6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FlintOff"+i, "officer_" + (rand(62)+2), "man", "man", sti(pchar.rank) + MOD_SKILL_ENEMY_RATE*3, PIRATE, 0, true));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
	}
	DoQuestFunctionDelay("BSHangover_FlintFight_1", 3);
	DoQuestFunctionDelay("BSHangover_FlintFight_2", 15);
	if (WhisperIsOfficer())
	{
		DoQuestFunctionDelay("BSHangover_FlintFight_3", 8);
		DoQuestFunctionDelay("BSHangover_FlintFight_4", 30);
	}
}

void BSHangover_FlintFight_1(string q)
{
	Log_Info(GetConvertStrWithReplace("Variable_black_sails_functions_7", "Logs.txt", "#space#", " "));
	sld = CharacterFromID("FlintOff1");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
}

void BSHangover_FlintFight_2(string q)
{
	Log_Info(GetConvertStrWithReplace("Variable_black_sails_functions_8", "Logs.txt", "#space#", " "));
	sld = CharacterFromID("FlintOff2");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	sld = CharacterFromID("FlintOff3");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
}

void BSHangover_FlintFight_3(string q)
{
	Log_Info(GetConvertStrWithReplace("Variable_black_sails_functions_9", "Logs.txt", "#space#", " "));
	sld = CharacterFromID(pchar.WhisperId);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
}

void BSHangover_FlintFight_4(string q)
{
	Log_Info(GetConvertStrWithReplace("Variable_black_sails_functions_10", "Logs.txt", "#space#", " "));
	sld = CharacterFromID("FlintOff4");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	sld = CharacterFromID("FlintOff5");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	sld = CharacterFromID("FlintOff6");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
}

void BSHangover_MaksOnShip(string q)
{
	BS_RestoreMaksHostess();
}
void BSHangover_FlintEscaped(string q)
{
	PChar.quest.BSHangover_Fail2.over = "yes";
	if (!CheckAttribute(&Colonies[FindColony("Nassau")], "BSBlackFlag")) return;
	chrDisableReloadToLocation = true;
	bDisableOfficers = true;
	BS_GatriHomeGuardsOff();
	TeleportCharacterToPos(pchar, 73.12008, 3.20824, 25.118425);
	CharacterTurnToLoc(pchar, "rld", "loc0");
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	TeleportCharacterToPos(sld, 74.1475, 3.1212275, 21.183332);
	LAi_SetImmortal(sld, true);
	sld = BSTutorialSailor();
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	TeleportCharacterToPos(sld, 75.27994, 3.1098757, 21.558277);
	LAi_SetActorType(sld);
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_41";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_SetImmortal(sld, true);
}

void BSHangover_TownHall(string q)
{
	pchar.currentsoundtrack = "The_Final_Battle";
	LAi_SetSitTypeNoGroup(pchar);
	ChangeCharacterAddressGroup(pchar, "Nassau_OfisGatri", "sit", "sit5");
	ref chr;
	
	chr = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit4");
	LAi_SetSitTypeNoGroup(chr);

	chr = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest3");
	LAi_SetActorType(chr);
	CharacterTurnToLoc(chr, "sit", "sit5");

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit7");
	LAi_SetSitTypeNoGroup(chr);

	chr = CharacterFromID("gatri_temp");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest5");
	LAi_SetActorType(chr);
	CharacterTurnToLoc(chr, "reload", "reload1_back");
	LAi_SetStayTypeNoGroup(chr);
	chr.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	chr.dialog.currentnode = "BS_F1_48";
	LAi_tmpl_SetDialog(chr, pchar, -1.0);	
	
	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit6");
	LAi_SetSitTypeNoGroup(chr);

	chr = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit3");
	LAi_SetSitTypeNoGroup(chr);
}

void BSHangover_Cutscene(string q)
{
	FreeSitLocator("Nassau_tavern", "sit_front2");
	FreeSitLocator("Nassau_tavern", "sit_base2");
	FreeSitLocator("Nassau_tavern", "sit_base1");
	FreeSitLocator("Nassau_tavern", "sit2");
	ChangeCharacterAddressGroup(pchar, "Nassau_tavern", "sit", "sit_front2");
	LAi_SetSitTypeNoGroup(pchar);
	DoQuestFunctionDelay("BSHangover_Cutscene_0", 0);
}
void BSHangover_Cutscene_0(string q)
{
	DoQuestFunctionDelay("BSHangover_Cutscene_1", 5);
	if (WhisperIsHere())
	{
		sld = CharacterFromID(pchar.WhisperId);
		ChangeCharacterAddressGroup(sld, "Nassau_tavern", "sit", "sit_base2");
		LAi_SetSitTypeNoGroup(sld);
	}
}
void BSHangover_Cutscene_1(string q)
{
	SetLaunchFrameFormParam(GetConvertStr("Variable_black_sails_functions_5", "Frames.txt"), "", 0.1, 3.0);
	LaunchFrameForm();
	WaitDate("",0,0,0,3,3);
	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_13_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
	else
	{
		DoQuestFunctionDelay("BSHangover_Cutscene_2", 5);
	}
}
void BSHangover_Cutscene_2(string q)
{
	LocatorReloadEnterDisable("Nassau_town", "houseS1", false);
	ChangeCharacterAddressGroup(pchar, "Nassau_tavern", "tables", "stay4");
	LAi_SetPlayerType(pchar);
	AddQuestRecord("BSHangover", "12");
	pchar.quest.BSHangover_TownHall.win_condition.l1          = "location";
	pchar.quest.BSHangover_TownHall.win_condition.l1.location = "Nassau_OfisGatri";
	pchar.quest.BSHangover_TownHall.function             = "BSHangover_FirstEnding";
}

void BSHangover_FirstEnding(string q)
{
	ChangeCharacterAddressGroup(PChar, "Nassau_OfisGatri", "goto", "goto5");
	LAi_SetActorTypeNoGroup(PChar);
	CharacterTurnToLoc(PChar, "sit", "sit2");
	LAi_SetStayTypeNoGroup(PChar);
	
	sld = CharacterFromID("BS_Rakham");
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "none", "", "");

	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	ref chr;	
	
	chr = CharacterFromID("BS_Silver");
	LAi_CharacterEnableDialog(chr);
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit2");
	LAi_SetSitTypeNoGroup(chr);
	chr.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	chr.dialog.currentnode = "BS_F1_53";
	LAi_tmpl_SetDialog(chr, pchar, -1.0);
	
	chr = CharacterFromID("gatri_temp");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest5");
	LAi_SetActorTypeNoGroup(chr);
	CharacterTurnToLoc(chr, "sit", "sit2");
	
	chr = CharacterFromID("BS_Vein");
	LAi_CharacterEnableDialog(chr);
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest6");
	LAi_SetActorTypeNoGroup(chr);
	CharacterTurnToLoc(chr, "sit", "sit2");
	
	chr = CharacterFromID("BS_Bony");
	LAi_CharacterEnableDialog(chr);
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest4");
	LAi_SetActorTypeNoGroup(chr);
	CharacterTurnToLoc(chr, "sit", "sit2");
}

void BS_NassauCobHouseEnding_1(string qName)
{
	sld = CharacterFromID("BS_Silver");
	LAi_CharacterEnableDialog(sld);
	sld.location = "none";
	sld = CharacterFromID("BS_Vein");
	sld.location = "none";
	sld = CharacterFromID("BS_Bony");
	sld.location = "none";
	LocatorReloadEnterDisable("Nassau_town", "houseS1", true);
	SetFunctionTimerConditionParam("BS_NassauCobHouseEnding_2", 0, 0, 0, 24, false);
	SetFunctionExitFromLocationCondition("BS_NassauStopMusic", pchar.location, false);
}

void BS_NassauStopMusic(string qName)
{
	DeleteAttribute(PChar, "currentsoundtrack");
}

void BS_NassauCobHouseEnding_2(string qName)
{
	LocatorReloadEnterDisable("Nassau_town", "houseS1", false);
	sld = CharacterFromID("Gatri_temp");
	sld.Dialog.FileName = "Quest\BlackSails\NePluyjVKolodec.c";
	sld.dialog.currentnode = "BS_NPVK_20_meet";
	sld.CityType = "citizen";
	sld.city = "Nassau";
	sld.greeting = "Gr_Woman_Citizen";	
	ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "quest", "quest5");	
	CharacterTurnToLoc(sld, "reload", "reload1_back");
	LAi_SetStayType(sld);
	BS_GatriHomeGuardsOn();
}

void BS_SentJonsTavernAgentDialugue()
{
	sld = GetCharacter(NPC_GenerateCharacter("BSAgent", "shipowner_"+(rand(15)+1), "man", "man", 10, ENGLAND, -1, false));
	FreeSitLocator("SentJons_tavern", "sit_base3");
	ChangeCharacterAddressGroup(sld, "SentJons_tavern", "sit", "sit_base3");
	LAi_SetSitTypeNoGroup(sld);
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode = "BS_F3_5";
}

void BS_AfterAgentMeeting(string qName)
{
	LAi_SetSitTypeNoGroup(pchar);
	ChangeCharacterAddressGroup(pchar, "Nassau_OfisGatri", "sit", "sit5");
	
	sld = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(sld, "none", "", "");

	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	ref chr;
	
	chr = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit4");
	LAi_SetSitTypeNoGroup(chr);
	

	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "sit", "sit6");
	LAi_SetSitTypeNoGroup(chr);

	chr = CharacterFromID("gatri_temp");
	ChangeCharacterAddressGroup(chr, "Nassau_OfisGatri", "quest", "quest5");
	LAi_SetActorType(chr);	
	CharacterTurnToLoc(chr, "reload", "reload1_back");
	LAi_SetStayTypeNoGroup(chr);
	chr.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	chr.dialog.currentnode = "BS_F3_10";
	LAi_tmpl_SetDialog(chr, pchar, -1.0);
}

void BS_AfterAgentMeetingExit(string qName)
{
	sld = CharacterFromID("BS_Rakham");
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = CharacterFromID("BS_Bony");
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
	LAi_SetStayType(sld);
	DeleteAttribute(sld, "talker");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode = "BS_F3_18";
}

void BS_HangoverMaksPortRoyalArriving(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", "goto1");
	LAi_SetActorType(sld);
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode = "BS_F3_19";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void BS_IntimWithMaks(string qName)
{
	LAi_FadeDelay(10.0, "");
	LAi_SetActorType(pchar);
	LAi_ActorSetStayMode(pchar);
	BS_ReplaceHostessWithMaks();
	PlayStereoSound("sex\sex" + (rand(13)+1) + ".wav");
    AddTimeToCurrent(2, rand(30));
	AddCharacterMaxHealth(pchar, 4);
	AddCharacterHealth(pchar, 10);
	if(CheckAttribute(PChar, "chr_ai.HeavyTrauma"))
	{
		DeleteAttribute(PChar, "chr_ai.TraumaQ");
		DeleteAttribute(PChar, "chr_ai.HeavyTrauma");
		string langtemp = "";
		if (LanguageGetLanguage() != "russian") { langtemp = "You've recovered from a serious injury"; }
		else { langtemp = "Вы оправились от тяжёлой травмы"; }
		Log_Info(langtemp);
		CheckAndSetOverloadMode(pchar);
	}
	CharacterTurnToLoc(pchar, "reload", "reload1_back");
	DoQuestFunctionDelay("BS_IntimWithMaksOver", 10.0);
}

void BS_IntimWithMaksOver(string qName)
{
	chrDisableReloadToLocation = false;
	AddQuestRecord("BSHangover", "25");
	LAi_SetPlayerType(PChar);
}

void BS_IntimWithMaksAsLover()
{
	LAi_SetActorType(pchar);
	LAi_ActorSetStayMode(pchar);
	LAi_FadeDelay(9.0, "");
	PlayStereoSound("sex\sex" + (rand(13)+1) + ".wav");
    AddTimeToCurrent(2, rand(30));
	AddCharacterMaxHealth(pchar, 4);
	AddCharacterHealth(pchar, 10);
	if(CheckAttribute(PChar, "chr_ai.HeavyTrauma"))
	{
		DeleteAttribute(PChar, "chr_ai.TraumaQ");
		DeleteAttribute(PChar, "chr_ai.HeavyTrauma");
		string langtemp = "";
		if (LanguageGetLanguage() != "russian") { langtemp = "You've recovered from a serious injury"; }
		else { langtemp = "Вы оправились от тяжёлой травмы"; }
		Log_Info(langtemp);
		CheckAndSetOverloadMode(pchar);
	}
	DoQuestFunctionDelay("BS_IntimWithMaksAsLoverOver", 8.0);
}

void BS_IntimWithMaksAsLoverOver(string qName)
{
	LAi_SetPlayerType(PChar);
	DoReloadCharacterToLocation("PortRoyal_town", "reload", "reload9_back");
}


void BS_HangoverToAntigua(string qName)
{
	//AddQuestRecord("BSHangover", "61");
	pchar.BSSentJonsWaitress = true;
}

void BS_BonsDominicaMeeting(string qName)
{
	string sCapId = "BSBons";
    string sGroup = "Sea_" + sCapId;
	Group_FindOrCreateGroup(sGroup);
	sld = GetCharacter(NPC_GenerateCharacter(sCapId, "off_eng_"+(rand(1)+1), "man", "man", 100, ENGLAND, -1, true));
	string langtemp = "";
	if (LanguageGetLanguage() != "russian") { langtemp = "Fortune"; }
	else { langtemp = "Фортуна"; }
	FantomMakeCoolestSailor(sld, SHIP_DIANA, langtemp, CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
	FantomMakeCoolFighter(sld, 40+MOD_SKILL_ENEMY_RATE*10, 100, 100, "blade30", "pistol4", 250+MOD_SKILL_ENEMY_RATE*75);
	sld.Name = GetConvertStrWithReplace("Variable_black_sails_functions_27", "Names.txt", "#space#", " ");
	sld.Lastname = GetConvertStrWithReplace("Variable_black_sails_functions_28", "Names.txt", "#space#", " ");
	sld.Model = "BS_Billy";
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.DeckDialogNode = "BS_F3_25";
	FaceMaker(sld);
	sld.SaveItemsForDead = true;
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true;	
	UltimatePerksSet(sld);
	SetCrewQuantityFull(sld);
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	BS_CorrectShipGoods(sld);
	sld.AlwaysSandbankManeuver = true;
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetTaskNone(sGroup);
	Group_SetAddress(sGroup, "Dominica", "Quest_ships", "quest_ship_4");
}

void BS_BonsDominicaNone(string qName)
{
	string sCapId = "BSBons";
    string sGroup = "Sea_" + sCapId;
	Group_SetAddressNone(sGroup);
}

void BS_ShoreSeeking(string qName)
{
	AddQuestRecord("BSHangover", "64");
	string sCapId = "LosTequesPirates";
    string sGroup = "Sea_" + sCapId + "1";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "pirate");
	for (int i = 1; i < 3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(sCapId+i, "off_eng_"+(rand(1)+1), "man", "man", 999, ENGLAND, -1, true));
		sld.Ship.Type = GenerateShipExt(GetShipTypeExt(2, 2, "war", ENGLAND), true, sld);
		sld.rank_bonus = 6*MOD_SKILL_ENEMY_RATE;
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "CannonProfessional");
		sld.Ship.Mode = "war";
		Fantom_SetUpgrade(sld, "hunter");
		Fantom_SetCannons(sld, "pirate");
		Fantom_SetBalls(sld, "pirate");
		BS_CorrectShipGoods(sld);

		sld.AlwaysEnemy = true;
		sld.AnalizeShips = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		SetFantomParamHunter(sld);
		Group_AddCharacter(sGroup, sld.id);		
	}
	int ig = Group_FindGroup(sGroup);
	
	AIGroups[ig].location = "Cumana";
	AIGroups[ig].pos.x = -5117.66;
	AIGroups[ig].Pos.z = -745.068;
	AIGroups[ig].Pos.ay = 0;
	Group_SetGroupCommander(sGroup, sCapId + "1");
	Group_SetTaskNone(sGroup);
	PChar.quest.BS_LosTequesPiratesOver.win_condition.l1 = "Group_Death";
	PChar.quest.BS_LosTequesPiratesOver.win_condition.l1.group = sGroup;
	PChar.quest.BS_LosTequesPiratesOver.function = "BS_LosTequesPiratesOver";
	string langtemp = "";
	if (LanguageGetLanguage() != "russian") { langtemp = "I need to check out Los Teques beach"; }
	else { langtemp = "Мне нужно проверить пляж Лос-Текес"; }
	pchar.LockMapReload = langtemp;
}

void BS_LosTequesPiratesOver(string qName)
{
	SetFunctionLocationCondition("BS_LosTequesPiratesLanding", "Shore20", false);
}

void BS_LosTequesPiratesLanding(string qName)
{
	InterfaceStates.Buttons.Save.enable = false;
	chrDisableReloadToLocation = true;
	string sGroup = "BS_LosTequesLandPirates";
	int i = 0;
	int irank = 0;
	for (i = 0; i < 30; i++)
	{
		irank = 18 + 8*MOD_SKILL_ENEMY_RATE + rand(4*MOD_SKILL_ENEMY_RATE);
		sld = GetCharacter(NPC_GenerateCharacter(sGroup+i, "off_eng_"+(rand(1)+1), "man", "man", irank, ENGLAND, 1, true));
		LAi_SetWarriorType(sld);
		Group_AddCharacter(sGroup, sld.id);
		LAi_group_MoveCharacter(sld, sGroup);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		if(i < 10) ChangeCharacterAddressGroup(sld, "Shore20", "goto", "goto11");
		if(i >= 10 && i < 20) ChangeCharacterAddressGroup(sld, "Shore20", "goto", "goto6");
		if(i >= 20 && i < 30) ChangeCharacterAddressGroup(sld, "Shore20", "goto", "goto1");
	}
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
	LAi_group_SetCheckFunction(sGroup, "BS_LosTequesLandPiratesover");
}

void BS_LosTequesLandPiratesOver(string qName)
{
	DeleteAttribute(pchar, "LockMapReload");
	SetFunctionLocationCondition("BS_MosquitoGulfSailor", "Shore47", false);
	AddQuestRecord("BSHangover", "65");
	InterfaceStates.Buttons.Save.enable = true;
	chrDisableReloadToLocation = false;
}

void BS_MosquitoGulfSailor(string q)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	sld = GetCharacter(NPC_GenerateCharacter("BS_MosquitoGulfSailor", "shipowner_"+(rand(3)+1), "man", "man", 100, PIRATE, 0, false));
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode   = "BS_F3_32";
	ChangeCharacterAddressGroup(sld, "Shore47", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void BS_BridgetownBonsAlarm(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("BSBons");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode   = "BS_F3_35";
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "reload", "gate1_back");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void BS_BridgetownPlantationOrders(string qName)
{
	WaitDate("",0,0,0,0,1);
	string langtemp = "";
	if (LanguageGetLanguage() != "russian") { langtemp = "You give the necessary orders"; }
	else { langtemp = "Вы отдаёте необходимые приказы"; }
	SetLaunchFrameFormParam(langtemp, "", 0.1, 3.0);
	LaunchFrameForm();
}

void BS_ReloadToPlantation(string qName)
{
	DoReloadCharacterToLocation("Bridgetown_Plantation", "reload", "reload1_back");
}

void BS_BridgetownPlantationPrepare(string qName)
{
	pchar.currentsoundtrack = "On_the_Beach";
	InterfaceStates.Buttons.Save.enable = false;
	chrDisableReloadToLocation = true;
	string sGroup = "BS_PlantationDefenders";
	sld = CharacterFromID("BSBons");
	LAi_SetStayType(sld);
	LAi_SetActorTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "soldiers", "soldier1");
	int addhp = makeint(400/MOD_SKILL_ENEMY_RATE) + 200;
	sld = GetCharacter(NPC_GenerateCharacter("BS_PlantOfficer", "head_pir", "man", "man", sti(pchar.rank), PIRATE, 0, true));
	LAi_SetHP(sld, stf(sld.chr_ai.hp) + addhp, stf(sld.chr_ai.hp) + addhp);
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto18");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, PChar);
	LAi_SetStayType(sld);
	Group_AddCharacter(LAI_GROUP_PLAYER, sld.id);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld.talker = 10;
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode = "BS_F3_PlantOfficer";
	float posX, posY, posZ;
	GetCharacterPos(sld, &posX, &posY, &posZ);
	for (int i = 0; i < 31; i++)
	{
		if(i >= 0 && i < 12)
		{
			sld = GetCharacter(NPC_GenerateCharacter(sGroup+i, "off_eng_"+(rand(1)+1), "man", "man", sti(pchar.rank), ENGLAND, 0, true));
			LAi_SetHP(sld, stf(sld.chr_ai.hp) + addhp, stf(sld.chr_ai.hp) + addhp);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", posX, posY, posZ));
		}
		if(i >= 12 && i < 23)
		{
			sld.MusketerDistance = 0;
			sld = GetCharacter(NPC_GenerateCharacter(sGroup+i, "eng_mush_" + (rand(2)+1), "man", "mushketer", sti(pchar.rank), ENGLAND, 0, true));
			LAi_SetHP(sld, stf(sld.chr_ai.hp) + addhp, stf(sld.chr_ai.hp) + addhp);
			ChangeCharacterAddressGroup(sld, pchar.location, "patrol",  LAi_FindNearestFreeLocator("patrol", posX, posY, posZ));
		}
		if(i >= 23 && i < 31)
		{
			sld = GetCharacter(NPC_GenerateCharacter(sGroup+i, "pirate_" + (rand(5) + 5), "man", "man", sti(pchar.rank), PIRATE, 0, true));
			LAi_SetHP(sld, stf(sld.chr_ai.hp) + addhp, stf(sld.chr_ai.hp) + addhp);
			ChangeCharacterAddressGroup(sld, pchar.location, "officers", LAi_FindNearestFreeLocator("officers", posX, posY, posZ));
		}
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
		Group_AddCharacter(LAI_GROUP_PLAYER, sld.id);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
		LAi_group_Attack(sld, Pchar);		
	}
}
void BS_BridgetownPlantationBattleStart(string qName)
{
	string sGroup = "BS_PlantationEnemies1";
	for (int i = 0; i < 12; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(sGroup+i, "pirate_" + (rand(5) + 11), "man", "man", sti(pchar.rank), PIRATE, 0, true));
		FantomMakeCoolFighterWRankDepend(sld, 15+MOD_SKILL_ENEMY_RATE*5+rand(5), 55+MOD_SKILL_ENEMY_RATE*15, 55+MOD_SKILL_ENEMY_RATE*15, 50*MOD_SKILL_ENEMY_RATE);
		if(i >= 0 && i < 2)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto3");
		}
		if(i >= 2 && i < 4)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto4");
		}
		if(i >= 4 && i < 6)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto7");
		}
		if(i >= 6 && i < 8)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto8");
		}
		if(i >= 8 && i < 10)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto21");
		}
		if(i >= 10 && i < 12)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto22");
		}
		sld.AlwaysEnemy = true;
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
		Group_AddCharacter(sGroup, sld.id);
		LAi_group_MoveCharacter(sld, sGroup);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
	}
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
	DeleteAttribute(PChar, "currentsoundtrack");
	LAi_SetFightMode(PChar, true);
	LAi_group_SetCheckFunction(sGroup, "BS_BridgetownPlantationWaiting_1");
}

void BS_BridgetownPlantationWaiting_1(string qName)
{
	DoQuestFunctionDelay("BS_BridgetownPlantationReinforcement_1", 5.0);
}

void BS_BridgetownPlantationReinforcement_1(string qName)
{
	string sGroup = "BS_PlantationEnemies2";
	for (int i = 0; i < 24; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(sGroup+i, "pirate_" + (rand(5) + 11), "man", "man", sti(pchar.rank), PIRATE, 0, true));
		FantomMakeCoolFighterWRankDepend(sld, 15+MOD_SKILL_ENEMY_RATE*5+rand(5), 55+MOD_SKILL_ENEMY_RATE*15, 55+MOD_SKILL_ENEMY_RATE*15, 70*MOD_SKILL_ENEMY_RATE);
		if(i >= 0 && i < 4)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto3");
		}
		if(i >= 4 && i < 8)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto4");
		}
		if(i >= 8 && i < 12)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto7");
		}
		if(i >= 12 && i < 16)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto8");
		}
		if(i >= 16 && i < 20)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto21");
		}
		if(i >= 20 && i < 24)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto22");
		}
		sld.AlwaysEnemy = true;
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
		Group_AddCharacter(sGroup, sld.id);
		LAi_group_MoveCharacter(sld, sGroup);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
	}
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
	DeleteAttribute(PChar, "currentsoundtrack");
	LAi_SetFightMode(PChar, true);
	LAi_group_SetCheckFunction(sGroup, "BS_BridgetownPlantationBattleBonsWaiting");
}

void BS_BridgetownPlantationBattleBonsWaiting(string qName)
{
	DoQuestFunctionDelay("BS_BridgetownPlantationBattleBonsAlarm", 5.0);	
}

void BS_BridgetownPlantationBattleBonsAlarm(string qName)
{
	InitSound();
	SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, "CSR\Music\BlackSailsMusic\Fromthefields.ogg", SOUND_WAV_STEREO, 10, false, false, false);
	LAi_SetFightMode(PChar, false);
	StartInstantDialog("BSBons", "BS_F3_38", "Quest\BlackSails\BS_Final_3.c");
}

void BS_BridgetownPlantationReinforcement_2()
{
	string sGroup = "BS_PlantationEnemies3";
	for (int i = 0; i < 36; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(sGroup+i, "pirate_" + (rand(5) + 11), "man", "man", sti(pchar.rank), PIRATE, 0, true));
		FantomMakeCoolFighterWRankDepend(sld, 15+MOD_SKILL_ENEMY_RATE*5+rand(5), 55+MOD_SKILL_ENEMY_RATE*15, 55+MOD_SKILL_ENEMY_RATE*15, 90*MOD_SKILL_ENEMY_RATE);
		if(i >= 0 && i < 6)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto3");
		}
		if(i >= 6 && i < 12)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto4");
		}
		if(i >= 12 && i < 18)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto7");
		}
		if(i >= 18 && i < 24)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto8");
		}
		if(i >= 24 && i < 30)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto21");
		}
		if(i >= 30 && i < 36)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto22");
		}
		sld.AlwaysEnemy = true;
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
		Group_AddCharacter(sGroup, sld.id);
		LAi_group_MoveCharacter(sld, sGroup);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
	}
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(PChar, true);
	LAi_group_SetCheckFunction(sGroup, "BS_BridgetownPlantationWaitingForFlint");
}

void BS_BridgetownPlantationWaitingForFlint(string qName)
{
	DoQuestFunctionDelay("BS_BridgetownPlantationFlintAppear", 5.0);
}

void BS_BridgetownPlantationFlintAppear(string qName)
{
	string sGroup = "BS_PlantationEnemies4";
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto16");
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	Group_AddCharacter(sGroup, sld.id);
	LAi_group_MoveCharacter(sld, sGroup);
	
	sld = CharacterFromID("BS_Vein");
	FantomMakeCoolFighter(sld, sti(sld.rank), 100, 100, "blade28", "pistol4", 150*MOD_SKILL_ENEMY_RATE);
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto16");
	LAi_SetImmortal(sld, true);
	SetCharacterPerk(sld, "Energaiser");
	TakeNItems(sld, "potionwine", 8);
	TakeNItems(sld, "Food4", 15);
	sld.items.cartridge = 35;
	LAi_SetWarriorType(sld);
	Group_AddCharacter(sGroup, sld.id);
	LAi_group_MoveCharacter(sld, sGroup);
	for (int i = 0; i < 48; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(sGroup+i, "pirate_" + (rand(5) + 11), "man", "man", sti(pchar.rank), PIRATE, 0, true));
		FantomMakeCoolFighterWRankDepend(sld, 15+MOD_SKILL_ENEMY_RATE*5+rand(5), 55+MOD_SKILL_ENEMY_RATE*15, 55+MOD_SKILL_ENEMY_RATE*15, 120*MOD_SKILL_ENEMY_RATE);
		if(i >= 0 && i < 8)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto3");
		}
		if(i >= 8 && i < 16)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto4");
		}
		if(i >= 16 && i < 24)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto7");
		}
		if(i >= 24 && i < 32)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto8");
		}
		if(i >= 32 && i < 40)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto21");
		}
		if(i >= 40 && i < 48)
		{
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto22");
		}
		sld.AlwaysEnemy = true;
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
		Group_AddCharacter(sGroup, sld.id);
		LAi_group_MoveCharacter(sld, sGroup);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
	}
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
	DeleteAttribute(PChar, "currentsoundtrack");
	LAi_SetFightMode(PChar, true);
	bDisableCharacterMenu = true;
	DoQuestFunctionDelay("BS_BridgetownPlantationFightFortStrikes_1", 110.0);
	DoQuestFunctionDelay("BS_BridgetownPlantationFightFortStrikes_2", 112.5);
	DoQuestFunctionDelay("BS_BridgetownPlantationFightFortStrikes_3", 115.0);
	DoQuestFunctionDelay("BS_BridgetownPlantationFightFortStrikes_4", 116.5);
	DoQuestFunctionDelay("BS_BridgetownPlantationFightFortStrikes_5", 118.5);
	DoQuestFunctionDelay("BS_BridgetownPlantationFlintRunning", 120.0);
}
void BS_BridgetownPlantationFlintRunning(string qName)
{
	bDisableCharacterMenu = false;
	string sGroup = "BS_PlantationEnemies4";
	
	for (int i = 0; i < 48; i++)
	{
		sld = CharacterFromID(sGroup+i);
		if(!LAi_IsDead(sld)) {LAi_KillCharacter(sld);}
	}
	sld = CharacterFromID("Flint");
	Group_AddCharacter(LAI_GROUP_PLAYER, sld.id);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld = CharacterFromID("BS_Vein");	
	Group_AddCharacter(LAI_GROUP_PLAYER, sld.id);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	DoQuestFunctionDelay("BS_BridgetownPlantationFlintDialogue", 0.5);
}

void BS_BridgetownPlantationFlintDialogue(string qName)
{
	LAi_SetFightMode(pchar, false);
	StartInstantDialog("Flint", "BS_F3_40Flint_1", "Quest\BlackSails\BS_Final_3.c");
}

void BS_BridgetownPlantationVeinFight(string qName)
{
	sld = CharacterFromID("BS_Vein");
	LAi_SetImmortal(sld, false);
	pchar.quest.BS_BridgetownPlantationVeinFightOver.win_condition.l1 = "NPC_Death";
	pchar.quest.BS_BridgetownPlantationVeinFightOver.win_condition.l1.character = sld.id;
	PChar.quest.BS_BridgetownPlantationVeinFightOver.function = "BS_BridgetownPlantationVeinFightOver";
	Group_AddCharacter(LAI_GROUP_ENEMY, sld.id);
	LAi_group_MoveCharacter(sld, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(LAI_GROUP_ENEMY, LAI_GROUP_PLAYER, true);
	int i = 0;
	string sGroup = "BS_PlantationDefenders";
	for (i = 0; i < 31; i++)
	{
		sld = CharacterFromID(sGroup+i);		
		if(!LAi_IsDead(sld))
		{
			LAi_SetFightMode(sld, false);
			Group_AddCharacter(LAI_GROUP_NEITRAL, sld.id);
			LAi_group_MoveCharacter(sld, LAI_GROUP_NEITRAL);
			
		}
	}
	sld = CharacterFromID("BS_PlantOfficer");
	Group_AddCharacter(LAI_GROUP_NEITRAL, sld.id);
	LAi_group_MoveCharacter(sld, LAI_GROUP_NEITRAL);
	for(i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		if(GetOfficersIndex(GetMainCharacter(),i)!=-1 )
		{
			sld = Characters[GetOfficersIndex(GetMainCharacter(), i)];
			LAi_SetFightMode(sld, false);
			Group_AddCharacter(LAI_GROUP_NEITRAL, sld.id);
			LAi_group_MoveCharacter(sld, LAI_GROUP_NEITRAL);
		}
	}
}

void BS_BridgetownPlantationVeinFightOver(string qName)
{
	DeleteAttribute(PChar, "BS_PlantationBattle");
	DeleteAttribute(PChar, "currentsoundtrack");
	InterfaceStates.Buttons.Save.enable = true;
	chrDisableReloadToLocation = false;
	SetFunctionLocationCondition("BS_BridgetownSilverAfterPlantationBattle", "Bridgetown_town", false);
	for(i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		if(GetOfficersIndex(GetMainCharacter(),i)!=-1 )
		{
			sld = Characters[GetOfficersIndex(GetMainCharacter(), i)];
			Group_AddCharacter(LAI_GROUP_PLAYER, sld.id);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
}

void BS_BridgetownPlantationFightFortStrikes_1(string qName)
{
	InitSound();
	SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, "Sea Battles\cannon_fire_04.wav", SOUND_WAV_STEREO, 10, false, false, false);
}

void BS_BridgetownPlantationFightFortStrikes_2(string qName)
{
	InitSound();
	SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, "Sea Battles\cannon_fire_05.wav", SOUND_WAV_STEREO, 10, false, false, false);
}

void BS_BridgetownPlantationFightFortStrikes_3(string qName)
{
	InitSound();
	SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, "Sea Battles\cannon_fire_09.wav", SOUND_WAV_STEREO, 10, false, false, false);
}

void BS_BridgetownPlantationFightFortStrikes_4(string qName)
{
	InitSound();
	SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, "Sea Battles\cannon_fire_03.wav", SOUND_WAV_STEREO, 10, false, false, false);
}

void BS_BridgetownPlantationFightFortStrikes_5(string qName)
{
	InitSound();
	SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, "Sea Battles\cannon_fire_06.wav", SOUND_WAV_STEREO, 10, false, false, false);
}

void BS_BridgetownSilverAfterPlantationBattle(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("BS_Silver");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode   = "BS_F3_45";
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", "goto7");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void BS_Hangover_BarbadosRangerSeaBattle(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("RangerNewCap", "off_hol_2", "man", "man", 45+rand(5), PIRATE, 0, true));
	string langtemp = "";
	if (LanguageGetLanguage() != "russian") { langtemp = "Ranger"; }
	else { langtemp = "Рейнджер"; }
	FantomMakeCoolestSailor(sld, SHIP_DIANA, langtemp, CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
	DeleteAttribute(sld, "SaveItemsForDead");
	string sGroup = "RangerGroup";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "pirate");
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	SetCrewQuantityFull(sld);
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);

	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);

	UltimatePerksSet(sld);
	sld.Ship.Mode = "war";
	Fantom_SetUpgrade(sld, "hunter");
	Fantom_SetCannons(sld, "pirate");
	Fantom_SetBalls(sld, "pirate");
	BS_CorrectShipGoods(sld);
	
	Group_SetTaskAttack(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Group_SetAddress(sGroup, "Barbados", "Quest_ships", "quest_ship_7");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetPursuitGroup(sGroup, PLAYER_GROUP);
	string sQuest = "BS_BonsRunning_AddRecord";
    pchar.quest.(sQuest).win_condition.l1 = "ExitFromSea";  // fix homo 20/01/07
    pchar.quest.(sQuest).win_condition = "BS_BonsRunning_AddRecord";
    pchar.quest.(sQuest).function = "BS_BonsRunning_AddRecord";
}

void BS_Hangover_ChaseFromBarbados()
{
	string sCapId = "BSBons";
    string sGroup = "Sea_" + sCapId;
	sld = CharacterFromID(sCapId);
	sld.mapEnc.type = "war";
	sld.mapEnc.Name = GetConvertStrWithReplace("Variable_black_sails_functions_31", "Names.txt", "#space#", " ");
	sld.mapEnc.worldMapShip = "quest_ship";
	Group_FindOrCreateGroup(sGroup);
	Map_CreateTrader("Bridgetown", "Shore6", sCapId, 5);
}

void BS_BonsRunning_AddRecord(string qName)
{
	AddQuestRecord("BSHangover", "70");
}

void BS_BonsFlintRunning_AddRecord(string qName)
{
	string sIsland = "";
	if (CheckAttribute(AISea, "Island")) sIsland = AISea.Island;
	AddQuestRecord("BSHangover", "71");		
	AddQuestUserData("BSHangover", "sIsland", XI_ConvertString(sIsland + "Gen"));
	AddQuestUserData("BSHangover", "sSex", GetSexPhrase("","ла"));
}

void BS_Hangover_CapeCatocheBattle(string qName)
{
	ref chr;
	pchar.FlintCatocheBoardingDialog = true;
	string sCapId = "BSBons";
	chr = CharacterFromID(sCapId);
	chr.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	chr.DeckDialogNode = "BS_F3_50BonsDeck";
    string sGroup1 = "Sea_" + sCapId;
	Group_FindOrCreateGroup(sGroup1);
	Group_SetType(sGroup1, "pirate");
	Group_AddCharacter(sGroup1, chr.id);
	Group_SetGroupCommander(sGroup1, chr.id);
	chr.ship.HP = makeint(sti(chr.ship.HP)/4);
	SetCrewQuantity(chr, makeint(GetMaxCrewQuantity(chr)/3));
	chr.ship.masts.mast2 = true;
	LAi_SetImmortal(chr, true);
	chr.AlwaysFriend = true;
	chr.ShipEnemyDisable = true;
	sCapId = "Flint";
	sld = CharacterFromID(sCapId);
	string sGroup2 = "Flint_Group";
	Group_FindOrCreateGroup(sGroup2);
	Group_SetType(sGroup2, "pirate");
	Group_AddCharacter(sGroup2, sld.id);
	Group_SetGroupCommander(sGroup2, sld.id);
	sld.AlwaysEnemy = true;
	DeleteAttribute(sld, "AlwaysFriend");
	BSRepairShip(sld);
	BS_CorrectShipGoods(sld);
	DeleteAttribute(sld, "Abordage.Enable");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode = "BS_F3_48";
	LAi_SetImmortal(sld, false);
	SetCharacterRelationBoth(sti(sld.index), sti(chr.index), RELATION_ENEMY);
	Group_SetTaskAttack(sGroup1, sGroup2);
	Group_LockTask(sGroup1);
	Group_SetTaskAttack(sGroup2, PLAYER_GROUP);
	Group_LockTask(sGroup2);
	Group_SetPursuitGroup(sGroup1, sGroup2);
	Group_SetAddress(sGroup1, "Beliz", "Quest_ships", "quest_ship_9");
	Group_SetAddress(sGroup2, "Beliz", "Quest_ships", "quest_ship_9");
	pchar.quest.BS_Hangover_CapeCatocheBattleOver.win_condition.l1 = "NPC_Death";
	pchar.quest.BS_Hangover_CapeCatocheBattleOver.win_condition.l1.character = sld.id;
	PChar.quest.BS_Hangover_CapeCatocheBattleOver.function = "BS_Hangover_CapeCatocheBattleLanding";
}

void BS_Hangover_CapeCatocheBattleLanding(string qName)
{
	sld = CharacterFromID("Flint");
	if(sld.Killer.Status != KILL_BY_ABORDAGE && bSeaActive && !bAbordageStarted)
	{
		BS_Hangover_CapeCatocheBattleOver("qname");
		SetFunctionLocationCondition("BS_Hangover_CapeCatocheDialogue", "Shore6", false);
	}
}

void BS_Hangover_CapeCatocheBattleOver(string qName)
{
	chrDisableReloadToLocation = true;
	pchar.currentsoundtrack = "The_Final_Battle";
	PChar.quest.BS_SecondFinalEndingTimeOutFail.over = "yes";
	string shore = "Shore6";
	PChar.location.from_sea = shore;
	Locations[FindLocation(shore)].DisableEncounters = true;
	LAi_LocationFightDisable(&Locations[FindLocation(shore)], true);
	LAi_LocationDisableOfficersGen(shore, true);
	DoReloadFromSeaToLocation(shore, "reload", "sea");	
}

void BS_Hangover_CapeCatocheDialogue(string qName)
{
	sld = CharacterFromID("BSBons");
	Group_DeleteGroup("Sea_BSBons");
	Lai_SetActorTypeNoGroup(sld);
	CharacterTurnToLoc(sld, "officers", "sea_2");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
	
	sld = CharacterFromID("BS_Silver");
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto9");
	LAi_SetActorType(sld);
	CharacterTurnToLoc(sld, "officers", "sea_2");
	LAi_SetStayTypeNoGroup(sld);
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode = "BS_F3_51";
	sld.talker = 10;
}

void BS_CubaSilverOut(string qName)
{	
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	sld = CharacterFromID("BS_Silver");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode   = "BS_F3_59";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void BS_PortRoyalSilver(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	sld = CharacterFromID("BS_Silver");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
	sld.dialog.currentnode   = "BS_F3_67";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void BS_SecondFinalEndingTimeOutFail(string qName)
{
	PChar.quest.BS_Hangover_CapeCatocheBattle.over = "yes";
	Group_DeleteGroup("Sea_BSBons");
	Group_DeleteGroup("Flint_Group");
	CloseQuestHeader("BSHangover");
	BS_QuestCleaning(true);
}

void BS_SecondFinalEndingQuest(string qName)
{
	chrDisableReloadToLocation = false;
	LAi_LocationFightDisable(loadedLocation, false);
	CloseQuestHeader("BSHangover");
	pchar.questdata.ChernyeParusa = 1;
	BS_QuestCleaning(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Тяжелое похмелье --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
