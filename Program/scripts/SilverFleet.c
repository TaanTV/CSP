extern void GetLocHunterName();
extern void CheckForAchievement();

bool isSilverFleet = false;

bool S_armor(ref chr)
{
	if (CheckAttribute(chr, "ship.type") && chr.ship.type != SHIP_NOTUSED && RealShips[sti(chr.Ship.Type)].HullArmor == "S") return true;
	else return false;
}

void SFcondition (ref location)
{
	string typeHunter, sTemp, sCapId;
	ref    sld;
	bool   ok;
	
	if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "over") return;
	
	if (LAi_IsCapturedLocation) return;
	if (chrDisableReloadToLocation) return;
	if (LAi_grp_alarmactive == true)  return;
	if (Characters[GetCharacterIndex("eng_guber")].name != GetConvertStr("Variable_StoryCharacters_0.1", "Names.txt")) return;
	if (!CheckAttribute(PChar, "questTemp.silverfleet") && CheckAttribute(PChar, "InvitingOfficerDialogue") && GetQuestPastMonthParam("InvitingOfficerDialogue") < 1) return;
	
	if (location.id == "PortRoyal_town" && isDay() && !CheckAttribute(PChar, "questTemp.silverfleet") && sti(pchar.reputation) >= 60 && CheckAttribute(PChar, "achievements.ship_kills") && sti(pchar.achievements.ship_kills) >= 2)
	{
        sld = GetCharacter(NPC_GenerateCharacter("SF_InvitingOfficer", "off_eng_"+(rand(1)+1), "man", "man", 10, ENGLAND, 0, false));
		sld.dialog.filename = "Quest\Other_Quests_NPC.c";
		sld.dialog.currentnode = "SF_InvitingOfficer";
		sld.greeting = "eng_gov_common";
		PlaceCharacter(sld, "goto", PChar.location);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}

	if (location.type != "town" && location.type != "seashore" && location.type != "port") return;
	
    if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "ThirdSilverFleet" && sti(Colonies[FindColony(GetCurrentTown())].nation) != ENGLAND && GetQuestPastDayParam("SilverFleetHeadHunters") > (3 + rand(10)))
    {
		SaveCurrentQuestDateParam("SilverFleetHeadHunters");
		typeHunter = "SFhh";
		Log_QuestInfo("SilverFleetQuest_LandHunter");
		sCapId = typeHunter + "LandHunter0";
		sTemp = "LAND_HUNTER";
		ok = true;
		int hhqty = 3 + GetOfficersQuantity(PChar);
		if (hhqty > 8) hhqty = 8;
		for (int i = 1; i <= hhqty; i++) 
		{
			sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "OZG_" + (rand(9) + 1), "man", "man", 10, ENGLAND, 0, true));
			if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld.model.animation = "man_fast";
			sld.rank_bonus = makeint(MOD_SKILL_ENEMY_RATE*sti(PChar.rank)/5) + 2;
			SetFantomParamHunter(sld);
			sld.name = GetConvertStr("Variable_bountyhunters_0.1", "Names.txt");
			sld.lastname = "";
			sld.Dialog.CurrentNode = "First time";
			sld.dialog.filename = "Hunter_dialog.c";
			sld.greeting = "Gr_HUNTER";
			if (bHardBoss) sld.AlwaysReload = true;
			sld.location = "none";

			LAi_SetActorTypeNoGroup(sld);
			LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Battle_Hunters_Land");
			if (PlaceCharacter(sld, "goto", "random_must_be_near") == "" && i == 1)
			{
				ok = false;
				break;
			}
			LAi_ActorFollow(sld, pchar, "", 8.0);
			LAi_group_MoveCharacter(sld, sTemp);
		}

		LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

		LAi_group_ClearAllTargets();
		LAi_SetFightModeForOfficers(false);
		if (ok)
		{
	        PChar.HunterCost = 5000*sti(PChar.rank)*MOD_SKILL_ENEMY_RATE + drand(10000);
			PChar.HunterCost.TempHunterType = typeHunter;
			PChar.HunterCost.Qty = i;
			sld = characterFromID(sCapId + "1");
			LAi_type_actor_Reset(sld);
			LAi_ActorDialog(sld, pchar, "", 4.0, 0);
			chrDisableReloadToLocation = true;
			DoQuestCheckDelay("OpenTheDoors", 5.0);
		}
	}
}

void SF_CabinOfficer()
{
	ref sld;
	string ani, model;
	model = LAi_GetBoardingModel(pchar, &ani);
	sld = GetCharacter(NPC_GenerateCharacter("SilverSurferBoardingSailor", model, "man", ani, sti(PChar.rank)+10, sti(pchar.Nation), 0, true));
	LAi_SetActorTypeNoGroup(sld);
	sld.name = GenerateRandomName(sti(pchar.nation), "man") + " (" + XI_ConvertString("sailor3") + ")";
	sld.lastname = "";
	sld.greeting = "Gr_Officer";
	sld.dialog.filename = "Quest\Other_Quests_NPC.c";
	sld.dialog.currentnode = "SilverSurferCaptainTrap";
	ChangeCharacterAddressGroup(sld, PChar.location, "rld", LAi_FindNearestFreeLocator2Pchar("rld"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

bool SFheadhunters(string chid)
{
	if(HasSubStr(chid, "SFhh"))
	{
		if(CheckAttribute(PChar, "questTemp.silverfleet.waitingforheadhunters"))
		{
			AddQuestRecord("SilverFleet", "HeadHuntersFirstMeeting");
			AddQuestUserData("SilverFleet", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("SilverFleet", "sLoc", GetLocHunterName());
			DeleteAttribute(PChar, "questTemp.silverfleet.waitingforheadhunters");
		}
		else
		{
			AddQuestRecord("SilverFleet", "HeadHuntersAgain");
			AddQuestUserData("SilverFleet", "sSex", GetSexPhrase("ен","на"));
		}
		return true;
	}
	else return false;
}

int SF_CalculateBaseShipClass()
{
	int sf_baseshipclass = 6;
	int killshipclass1 = sti(pchar.Statistic.KillShip_1)+sti(pchar.Statistic.AbordShip_1)+sti(pchar.Statistic.KillAbordShip_1);
	int killshipclass2 = sti(pchar.Statistic.KillShip_2)+sti(pchar.Statistic.AbordShip_2)+sti(pchar.Statistic.KillAbordShip_2);
	int killshipclass3 = sti(pchar.Statistic.KillShip_3)+sti(pchar.Statistic.AbordShip_3)+sti(pchar.Statistic.KillAbordShip_3);
	if (killshipclass3 > 4) sf_baseshipclass = 5;
	if (killshipclass2 > 3) sf_baseshipclass = 4;
	if (killshipclass1 > 2) sf_baseshipclass = 3;
	return sf_baseshipclass;
}

int SF_GetBaseTypeEngShip (int class, string type)
{
	int killshipclass1 = sti(pchar.Statistic.KillShip_1)+sti(pchar.Statistic.AbordShip_1)+sti(pchar.Statistic.KillAbordShip_1);
	if (class == 6 && type == "war") return SHIP_ALERT;
	if (class == 5 && type == "war") return SHIP_SCHOONERWAR;
	if (class == 5 && type == "merchant") return SHIP_BARQUE;
	if (class == 4 && type == "war") return SHIP_ONTARIO;
	if (class == 4 && type == "merchant") return SHIP_FLEUT;
	if (class == 3 && killshipclass1 > 15 && type == "war") return SHIP_MORDAUNT;
	if (class == 3 && killshipclass1 > 5 && type == "war") return SHIP_ESSEX;
	if (class == 3 && type == "war") return SHIP_PANDORA;
	if (class == 3 && type == "merchant") return SHIP_INDIAMAN;
	if (class == 2 && type == "war") return SHIP_CENTURION;
	if (class == 2 && killshipclass1 > 10 && type == "merchant") return SHIP_WASA;
	if (class == 2 && type == "merchant") return SHIP_INDIAMAN;
	if (class == 1 && type == "war") return SHIP_VICTORY;
	return GetShipTypeExt(class, class, type, ENGLAND);
}

void SF_CorrectShipGoods(ref rFantom)
{
	int nShipType = sti(rFantom.ship.type);
	ref refBaseShip = GetRealShip(nShipType);
	int iCannons = sti(refBaseShip.CannonsQuantity);
	
	Fantom_SetCharacterGoods(rFantom, GOOD_SAILCLOTH, makeint(GetCargoGoods(rFantom, GOOD_SAILCLOTH)/3), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_PLANKS, makeint(GetCargoGoods(rFantom, GOOD_PLANKS)/2), 0);
    Fantom_SetCharacterGoods(rFantom, GOOD_FOOD, makeint(GetCargoGoods(rFantom, GOOD_FOOD)/2), 0);
	
	AddCharacterGoods(rFantom, GOOD_BALLS, 10 * iCannons + rand(iCannons));
	AddCharacterGoods(rFantom, GOOD_KNIPPELS, 5 * iCannons + rand(iCannons));
	AddCharacterGoods(rFantom, GOOD_POWDER, 10 * iCannons + rand(iCannons));		
}

int GenerateSilverSurfer(int iBaseType, ref chr)
{
	string  attr;
	int 	i;
	aref 	refShip;

	int iShip = CreateBaseShip(iBaseType);

	if (iShip == -1) return SHIP_NOTUSED;

	ref rRealShip = GetRealShip(iShip);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));

    if(CheckAttribute(rRealShip, "hullNums")) 
	{
        int nHulls = sti(rRealShip.hullNums);
        nHulls -= 1;
        if(nHulls < 0) nHulls = 0;
        rRealShip.ship.upgrades.hull = 1 + rand(nHulls);
    }
    else {rRealShip.ship.upgrades.hull = 1 + rand(2);}
	rRealShip.ship.upgrades.sails = 1 + rand(2);

	rRealShip.HullArmor = "S";

	makearef(refShip, chr.Ship);
	ResetShipCannonsDamages(chr);

	rRealShip.CannonsQuantityMax = sti(rRealShip.CannonsQuantity) - sti(rRealShip.MaxCannonDiff)*2;

	for (i = 0; i < sti(rRealShip.rcannon); i++)
	{
		attr = "c" + i;
		rRealShip.Cannons.Borts.cannonr.damages.(attr) = 1.0;
		rRealShip.Cannons.Borts.cannonl.damages.(attr) = 1.0;
		rRealShip.Cannons.Borts.rcannon.damages.(attr) = 1.0;
		rRealShip.Cannons.Borts.lcannon.damages.(attr) = 1.0;

		refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0;
		refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0;
		refShip.Cannons.Borts.rcannon.damages.(attr) = 1.0;
		refShip.Cannons.Borts.lcannon.damages.(attr) = 1.0;
	}

	rRealShip.rcannon = sti(rRealShip.rcannon) - sti(rRealShip.MaxCannonDiff);
	rRealShip.lcannon = sti(rRealShip.lcannon) - sti(rRealShip.MaxCannonDiff);

	rRealShip.cannonr = sti(rRealShip.rcannon);
	rRealShip.cannonl = sti(rRealShip.lcannon);
	rRealShip.cannonf = sti(rRealShip.fcannon);
	rRealShip.cannonb = sti(rRealShip.bcannon);

	rRealShip.Cannons = sti(rRealShip.CannonsQuantityMax);
	rRealShip.CannonsQuantity = sti(rRealShip.Cannons);

	for (i = 0; i < sti(rRealShip.rcannon); i++)
	{
		attr = "c" + i;
		rRealShip.Cannons.borts.cannonr.damages.(attr) = 0.0;
		rRealShip.Cannons.borts.cannonl.damages.(attr) = 0.0;
		rRealShip.Cannons.borts.rcannon.damages.(attr) = 0.0;
		rRealShip.Cannons.borts.lcannon.damages.(attr) = 0.0;

		refShip.Cannons.borts.cannonr.damages.(attr) = 0.0;
		refShip.Cannons.borts.cannonl.damages.(attr) = 0.0;
		refShip.Cannons.borts.rcannon.damages.(attr) = 0.0;
		refShip.Cannons.borts.lcannon.damages.(attr) = 0.0;
	}

	for (i = 0; i < sti(rRealShip.fcannon); i++)
	{
		attr = "c" + i;
		rRealShip.Cannons.borts.cannonf.damages.(attr) = 0.0;
		rRealShip.Cannons.borts.fcannon.damages.(attr) = 0.0;
		refShip.Cannons.borts.cannonf.damages.(attr) = 0.0;
		refShip.Cannons.borts.fcannon.damages.(attr) = 0.0;
	}

	for (i = 0; i < sti(rRealShip.bcannon); i++)
	{
		attr = "c" + i;
		rRealShip.Cannons.borts.cannonb.damages.(attr) = 0.0;
		rRealShip.Cannons.borts.bcannon.damages.(attr) = 0.0;
		refShip.Cannons.borts.cannonb.damages.(attr) = 0.0;
		refShip.Cannons.borts.bcannon.damages.(attr) = 0.0;
	}

	refShip.Cannons.Borts.cannonl = sti(rRealShip.lcannon);
	refShip.Cannons.Borts.cannonr = sti(rRealShip.rcannon);
	refShip.Cannons.Borts.cannonf = sti(rRealShip.fcannon);
	refShip.Cannons.Borts.cannonb = sti(rRealShip.bcannon);

	refShip.Cannons.Borts.lcannon = sti(rRealShip.lcannon);
	refShip.Cannons.Borts.rcannon = sti(rRealShip.rcannon);
	refShip.Cannons.Borts.fcannon = sti(rRealShip.fcannon);
	refShip.Cannons.Borts.bcannon = sti(rRealShip.bcannon);
	
	refShip.Cannons = sti(rRealShip.Cannons);

	rRealShip.Capacity		= makeint(sti(rRealShip.Capacity)*(1.001 - SHIP_STAT_RANGE_MAX));
	rRealShip.HP			= makeint(sti(rRealShip.HP)*(1.001 - SHIP_STAT_RANGE_MAX));
	rRealShip.SpeedRate		= stf(rRealShip.SpeedRate)*(1.001 - SHIP_STAT_RANGE_MAX);
	rRealShip.TurnRate		= stf(rRealShip.TurnRate)*(1.001 - SHIP_STAT_RANGE_MAX);
	rRealShip.WindAgainstSpeed 	= stf(rRealShip.WindAgainstSpeed)*(1.001 - SHIP_STAT_RANGE_MAX);
	rRealShip.MastMultiplier = stf(rBaseShip.MastMultiplier) + 0.299;
	rRealShip.OptCrew       = makeint(sti(rRealShip.OptCrew)*(1.001 - SHIP_STAT_RANGE_MAX));
	rRealShip.MaxCrew       = makeint(sti(rRealShip.OptCrew)*1.25);

	SetCabinTypeEx(rRealShip, sti(rRealShip.Class));

	rRealShip.Price	= GetShipPriceByTTH(iShip, chr)/2;

	if (sti(rRealShip.Price) <= 0) rRealShip.Price = 100;

	rRealShip.Stolen = true;
	rRealShip.soiling = 0;
	
	return iShip;
}

void SilverFleet()
{	
    ref sld, chref;
	int baseshipclass = SF_CalculateBaseShipClass();
    int iChar = NPC_GenerateCharacter("Head_of_Silver_Squadron", "off_eng_"+(rand(1)+1), "man", "man", 5, ENGLAND, 15, true);
    makeref(chref, Characters[iChar]);
	chref.Ship.Mode = "war";
    chref.ship.type = GenerateShipExt(SF_GetBaseTypeEngShip(baseshipclass-2, "war"), 1, chref);
	chref.rank_bonus = makeint(10*MOD_SKILL_ENEMY_RATE/(baseshipclass-2));
    SetCrewQuantityFull(chref);
	chref.ship.Crew.Morale = 85 + rand(5*MOD_SKILL_ENEMY_RATE);
	Fantom_SetUpgrade(sld, "pirate");
    Fantom_SetCannons(chref, "war");
    Fantom_SetBalls(chref, "pirate");
	SF_CorrectShipGoods(chref);
	SetFantomParamHunter(chref);
    SetCaptanModelByEncType(chref, "war");
	string sGroup = "Sea_"+chref.id;

	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, chref.id);
	Group_SetGroupCommander(sGroup, chref.id);

	int st = GetCharacterShipType(chref);
	ref shref;
	shref = GetRealShip(st);
	shref.ShipSails.Gerald_Name = "eng_5";

    chref.AlwaysEnemy = true;
    chref.DontRansackCaptain = true;
	chref.mapEnc.type = "trade";
	chref.mapEnc.worldMapShip = "manowar_red";
	chref.mapEnc.Name = XI_ConvertString("SilverConvoy");

	string sQuest = "KillHeadSilverFleet";
	pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
	pchar.quest.(sQuest).win_condition.l1.character = chref.id;
	pchar.quest.(sQuest).win_condition = "KillHeadSilverFleet";
    pchar.quest.(sQuest).function= "KillHeadSilverFleet";
	
	if (rand(11) == 0 && CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "over") chref.sftresureship = true;
	int sftresureship = 1+rand(10);
	while (sftresureship == 3 || sftresureship == 4) sftresureship = 1+rand(10);
	
    for(int k = 1; k < 12 ; k++)
	{
		iChar = NPC_GenerateCharacter("SilverFleetCap_"+k, "off_eng_"+(rand(1)+1), "man", "man", 5, ENGLAND, 15, true);
        makeref(sld, Characters[iChar]);
		sld.Ship.Mode = "war";
		if(k < 3 || k > 4)
		{
			if (k < 3)
			{
				if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "FirstSilverFleet") continue;
				if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "SecondSilverFleet" && k > 1) continue;
				if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "ThirdSilverFleet" && k == 2)
				{
					if ((sti(pchar.Statistic.KillShip_1)+sti(pchar.Statistic.AbordShip_1)+sti(pchar.Statistic.KillAbordShip_1)) > 30) sld.ship.type = GenerateSilverSurfer(SF_GetBaseTypeEngShip(baseshipclass-2, "war"), sld);
					else sld.ship.type = GenerateSilverSurfer(SF_GetBaseTypeEngShip(baseshipclass-1, "war"), sld);
					if (LanguageGetLanguage() != "russian")
					{
						sld.name = "Norrin";
						sld.lastname = "Radd";
						sld.Ship.Name = "Silver Surfer";
					}
					else
					{
						sld.name = "Норрин";
						sld.lastname = "Радд";
						sld.Ship.Name = "Серебряный Сёрфер";
					}	
					sld.rank_bonus = 10*MOD_SKILL_ENEMY_RATE;
					sld.Tasks.CanChangeShipAfterBoarding = false;
					sld.SilverSurferCap = true;
					SetCharacterPerk(sld, "Energaiser");
					sld.SuperShooter = true;
				}
				else
				{
					sld.ship.type = GenerateShipExt(SF_GetBaseTypeEngShip(baseshipclass-1, "war"), 1, sld);
					sld.rank_bonus = makeint(10*MOD_SKILL_ENEMY_RATE/(baseshipclass-1));
				}				
			}
			else
			{
				if (k > 8 && CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "FirstSilverFleet") continue;
				if (k > 9 && CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "SecondSilverFleet") continue;
				sld.ship.type = GenerateShipExt(SF_GetBaseTypeEngShip(baseshipclass, "war"), 1, sld);
				sld.rank_bonus = makeint(10*MOD_SKILL_ENEMY_RATE/baseshipclass);
				SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterPerk(sld, "FastReload");
				SetCharacterPerk(sld, "HullDamageUp");
				SetCharacterPerk(sld, "SailsDamageUp");
				SetCharacterPerk(sld, "CrewDamageU");
				SetCharacterPerk(sld, "CriticalShoot");
				SetCharacterPerk(sld, "MapMaker");
				SetCharacterPerk(sld, "LongRangeShoot");
				SetCharacterPerk(sld, "CannonProfessional");
				SetCharacterPerk(sld, "BasicBattleState");
				SetCharacterPerk(sld, "AdvancedBattleState");
				SetCharacterPerk(sld, "ShipDefenseProfessional");
				SetCharacterPerk(sld, "ShipSpeedUp");
				SetCharacterPerk(sld, "ShipTurnRateUp");
				SetCharacterPerk(sld, "WindCatcher");
				SetCharacterPerk(sld, "SailsMan");
				SetCharacterPerk(sld, "SailingProfessional");
				sld.GhostShipTuning = true;
			}
			Fantom_SetCannons(sld, "war");
			SetCrewQuantityFull(sld);
            Fantom_SetBalls(sld, "pirate");
			SF_CorrectShipGoods(sld);
			SetCaptanModelByEncType(sld, "war");
			SetFantomParamHunter(sld);
			if (!CheckAttribute(sld, "SilverSurferCap"))
			{
				Fantom_SetUpgrade(sld, "pirate");
				sld.ship.Crew.Morale = 70 + rand(10*MOD_SKILL_ENEMY_RATE);
			}
			else
			{
				LAi_SetHP(sld, stf(sld.chr_ai.hp) + 100*MOD_SKILL_ENEMY_RATE, stf(sld.chr_ai.hp) + 100*MOD_SKILL_ENEMY_RATE);
				GiveItem2Character(sld, "cirass5");
				EquipCharacterbyItem(sld, "cirass5");
				sld.SaveItemsForDead = true;
				sld.ship.Crew.Morale = 100;
			}			
			st = GetCharacterShipType(sld);
			shref = GetRealShip(st);
			shref.ShipSails.Gerald_Name = "eng_2";			
		}
		else
		{
			if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "FirstSilverFleet" && k == 4) continue;
            sld.ship.type = GenerateShipExt(SF_GetBaseTypeEngShip(baseshipclass-1, "merchant"), 1, sld);
            Fantom_SetCannons(sld, "war");
			SetCrewQuantity(sld, GetOptCrewQuantity(sld));
            Fantom_SetBalls(sld, "trade");
			st = GetCharacterShipType(sld);
			shref = GetRealShip(st);
			shref.ShipSails.Gerald_Name = "eng_3";
			AddCharacterGoods(sld, GOOD_SILVER, GetGoodQuantityByWeight(GOOD_SILVER, GetCargoFreeSpace(sld)*4/5));
			AddCharacterGoods(sld, GOOD_GOLD, GetGoodQuantityByWeight(GOOD_GOLD, GetCargoFreeSpace(sld)));
			SetCaptanModelByEncType(sld, "trade");
			SetFantomParamHunter(sld);
			sld.ship.Crew.Morale = 40 + rand(20*MOD_SKILL_ENEMY_RATE);
			if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "FirstSilverFleet" && k == 3)
			{
				LAi_SetHP(sld, stf(sld.chr_ai.hp) + 30*MOD_SKILL_ENEMY_RATE, stf(sld.chr_ai.hp) + 30*MOD_SKILL_ENEMY_RATE);
				GiveItem2Character(sld, "book2_14");
				GiveItem2Character(sld, "suit_2");
				EquipCharacterbyItem(sld, "suit_2");
				sld.SaveItemsForDead = true;
			}
		}		
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
		if (k == sftresureship && !CheckAttribute(chref, "sftresureship") && CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "over") sld.sftresureship = true;
        Group_AddCharacter(sGroup, sld.id);
	}
}

void KillHeadSilverFleet()
{
	Map_ReleaseQuestEncounter("Head_of_Silver_Squadron");
	isSilverFleet = false;
}

void SilverFleetQuestDeathCheck()
{
	if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "FirstSilverFleet") AddQuestRecord("SilverFleet", "FirstMeetSilverFleet");
	if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "SecondSilverFleet") AddQuestRecord("SilverFleet", "SecondMeetSilverFleet");
	if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "ThirdSilverFleet") AddQuestRecord("SilverFleet", "ThirdMeetSilverFleet");
    string sQuest = "SilverFleetQuestVictory";
	pchar.quest.(sQuest).win_condition.l1 = "Group_Death";
	pchar.quest.(sQuest).win_condition.l1.group = "Sea_Head_of_Silver_Squadron";
	pchar.quest.(sQuest).function = "SilverFleetQuestVictory";
	sQuest = "SFSeaBattleFail";
	pchar.quest.(sQuest).win_condition.l1 = "MapEnter";
	pchar.quest.(sQuest).function = "SFSeaBattleFail";
}

void SilverFleetQuestVictory()
{
	if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "FirstSilverFleet")
	{
		AddQuestRecord("SilverFleet", "FirstSilverFleetDeath");
		pchar.questTemp.silverfleet = "FirstSilverFleetDeath";
	}
	if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "SecondSilverFleet")
	{
		AddQuestRecord("SilverFleet", "SecondSilverFleetDeath");
		pchar.questTemp.silverfleet = "SecondSilverFleetDeath";
		Map_CreateSilverFleetPirates();
		string sQuest = "SilverFleetPiratesAfterBattle";
		pchar.quest.(sQuest).win_condition.l1 = "MapEnter";
		pchar.quest.(sQuest).function = "SilverFleetPiratesAfterBattle";
		
	}
	if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet == "ThirdSilverFleet")
	{
		if (CheckAttribute(PChar, "questTemp.silverfleet.silversurfercaptainspeak"))
		{
			AddQuestRecord("SilverFleet", "ThirdSilverFleetDeathWithAbordage");
			DeleteAttribute(PChar, "questTemp.silverfleet.silversurfercaptainspeak");
		}
		else AddQuestRecord("SilverFleet", "ThirdSilverFleetDeath");
		AddQuestUserData("SilverFleet", "sSex", GetSexPhrase("","а"));
		pchar.questTemp.silverfleet = "ThirdSilverFleetDeath";
	}
	EndOfSilverFleet();
	pchar.quest.SFSeaBattleFail.over = "yes";
	pchar.quest.EndOfSilverFleet.over = "yes";
	pchar.SilverFleetAtSea = false;
}

void SFSeaBattleFail()
{
	pchar.quest.SilverFleetQuestVictory.over = "yes";
	AddQuestRecord("SilverFleet", "SeaBattleFail");
	AddQuestUserData("SilverFleet", "sSex", GetSexPhrase("ся","ась"));
    EndOfSilverFleet();
	pchar.quest.EndOfSilverFleet.over = "yes";
	pchar.questTemp.silverfleet = "SeaBattleFail";
	pchar.SilverFleetAtSea = false;
}

void Map_CreateSilverFleetPirates()
{
    ref  sld;
    int  i;
    string sCapId = "SilverFleetPirates";
    string sGroup = "Sea_" + sCapId + "1";
	Group_FindOrCreateGroup(sGroup);
	int shipclass = SF_CalculateBaseShipClass();
	shipclass -= 1;
    for (i = 1; i < 3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, PIRATE, 15, true));
		sld.Ship.Type = GenerateShipExt(GetShipTypeExt(shipclass, shipclass, "war", PIRATE), true, sld);
		sld.rank_bonus = makeint(10*MOD_SKILL_ENEMY_RATE/shipclass);
		if (i == 1) sld.rank_bonus = sti(sld.rank_bonus) + MOD_SKILL_ENEMY_RATE*5;
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		RealShips[sti(sld.ship.type)].ship.upgrades.sails = 24 + rand(13);
		sld.Ship.Mode = "pirate";
		Fantom_SetUpgrade(sld, "hunter");
		Fantom_SetCannons(sld, "pirate");
		Fantom_SetBalls(sld, "pirate");
		SF_CorrectShipGoods(sld);
		SetFantomParamHunter(sld);
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
        sld.mapEnc.type = "war";
        sld.mapEnc.Name = GetConvertStrWithReplace("Variable_Treasure_7", "Names.txt", "#space#", " ");
		sld.hunter = "pirate";
        Group_AddCharacter(sGroup, sld.id);
		if (i == 1)
		{
			LAi_SetHP(sld, stf(sld.chr_ai.hp) + 60*MOD_SKILL_ENEMY_RATE, stf(sld.chr_ai.hp) + 60*MOD_SKILL_ENEMY_RATE);
			pchar.questTemp.silverfleet.piratesshiptype = RealShips[sti(sld.Ship.Type)].BaseName;
			GiveItem2Character(sld, "spyglass4");
			GiveItem2Character(sld, "book3_7");
			EquipCharacterbyItem(sld, "spyglass4");
			GiveItem2Character(sld, "suit_1");
			EquipCharacterbyItem(sld, "suit_1");
			sld.SaveItemsForDead = true;			
		}
    }
    Group_SetGroupCommander(sGroup, sCapId + "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
    Map_CreateFastWarrior("", sCapId + "1", 2);
}

void SilverFleetPiratesAfterBattle()
{
	if (CheckAttribute(pchar, "questTemp.silverfleet.piratesshiptype"))
	{
		AddQuestRecord("SilverFleet", "PiratesAfterBattle");
		AddQuestUserData("SilverFleet", "ShipType", GetStrSmallRegister(XI_ConvertString(pchar.questTemp.silverfleet.piratesshiptype)));
		DeleteAttribute(pchar, "questTemp.silverfleet.piratesshiptype");
	}
}

void TimerOnStartSilverFleet()
{
	if (CheckAttribute(Pchar, "SilverFleetMillionEveryMonth")) SilverFleetMillionEveryMonth();
	if (!CheckAttribute(PChar, "SilverFleetAtSea")) return;
	if (pchar.SilverFleetAtSea == false) return;
	if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet != "over" && Characters[GetCharacterIndex("eng_guber")].name != GetConvertStr("Variable_StoryCharacters_0.1", "Names.txt"))
	{	
		pchar.SilverFleetAtSea = false;
		CloseQuestHeader("SilverFleet");
		return;
	}
	if (isSilverFleet == false && Colonies[FindColony("PortRoyal")].nation == ENGLAND && Colonies[FindColony("Bridgetown")].nation == ENGLAND
    && !CheckAttribute(Colonies[FindColony("PortRoyal")], "Siege") && !CheckAttribute(Colonies[FindColony("Bridgetown")], "Siege") && rand(2) == 0)
    {
		isSilverFleet = true;
        string sQuest = "GenerateSilverFleet";
        if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet != "over") SetTimerCondition(sQuest, 0, 0, 15, false);
		else SetTimerCondition(sQuest, 0, 2, 0, false);
        pchar.quest.(sQuest).win_condition = "StartSilverFleet";
        pchar.quest.(sQuest).function = "StartSilverFleet";
    }
}

void StartSilverFleet()
{
	bool bOk1 = CheckAttribute(PChar, "SilverFleetAtSea") && pchar.SilverFleetAtSea == false;
	bool bOk2 = Colonies[FindColony("PortRoyal")].nation != ENGLAND || Colonies[FindColony("Bridgetown")].nation != ENGLAND;
	if (bOk1 || bOk2)
	{
		isSilverFleet = false;
		return;
	}
	SilverFleet();
	int pbx = worldMap.islands.Barbados.Bridgetown_town.position.x;
	int pbz = worldMap.islands.Barbados.Bridgetown_town.position.z;
	int pbx2 = worldMap.islands.Jamaica.PortRoyal_town.position.x;
	int pbz2 = worldMap.islands.Jamaica.PortRoyal_town.position.z;
	Map_CreateTraderXZ(pbx, pbz, pbx2, pbz2, "Head_of_Silver_Squadron", 21);
    string sQuest = "EndOfSilverFleet";
    SetTimerCondition(sQuest, 0, 0, 15, false);
    pchar.quest.(sQuest).win_condition = "EndOfSilverFleet";
    pchar.quest.(sQuest).function = "EndOfSilverFleet";
	SaveCurrentQuestDateParam("SilverFleetGo");
}

void EndOfSilverFleet()
{
    string sGroupID = "Sea_Head_of_Silver_Squadron";
    Map_ReleaseQuestEncounter("Head_of_Silver_Squadron");
    Group_SetAddressNone(sGroupID);
    Group_DeleteGroup(sGroupID);
	isSilverFleet = false;
}

void SilverFleetMillionEveryMonth()
{
	if(GetQuestPastMonthParam("SilverFleetMillionEveryMonth") > 0 || !CheckAttribute(Pchar, "SilverFleetMillionEveryMonth"))
	{
		SaveCurrentQuestDateParam("SilverFleetMillionEveryMonth");
		string NPC_Area = "PortRoyal";
		if(CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)) && makeint(Pchar.Quest.Deposits.(NPC_Area)) == true)
		{
			Pchar.Quest.Deposits.(NPC_Area).Sum = makeint(Pchar.Quest.Deposits.(NPC_Area).Sum) + 1000000;
		}
		else
		{
			bool isPatentSameNation = pchar.PatentNation == "eng";
			int iPercents = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1;
			Pchar.Quest.Deposits.(NPC_Area).Interest = iPercents + CheckAttribute(pchar, "EquipedPatentID") *  isPatentSameNation * iPercents;
			Pchar.Quest.Deposits.(NPC_Area).Sum = 1000000;
			Pchar.Quest.Deposits.(NPC_Area) = true;
			Pchar.Quest.Deposits.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Deposits.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Deposits.(NPC_Area).StartTime = getTime();
		}		
		CheckForAchievement();
	}
}

bool SF_boarding_check()
{
	if (CheckAttribute(boarding_enemy, "SilverSurferCap"))
	{
		if (CheckAttribute(&Locations[boarding_location], "boarding.nextdeck") && Locations[boarding_location].boarding.nextdeck == "" && !CheckAttribute(Pchar, "questTemp.silverfleet.boardinglocation"))
		{
			Pchar.questTemp.silverfleet.boardinglocation = Locations[boarding_location].id;
			return false;
		}
		if (CheckAttribute(Pchar, "questTemp.silverfleet.boardinglocation") && !CheckAttribute(boarding_enemy, "ShipCabinLocationId"))
		{
			ref chr = LocFromID(Pchar.questTemp.silverfleet.boardinglocation);
			boarding_enemy_crew = MAX_GROUP_SIZE;
			if(CheckAttribute(chr, "boarding.locatorNum")) boarding_enemy_crew = sti(chr.boarding.locatorNum);
			e_rank_bonus += makeint(sqrt(2*MOD_SKILL_ENEMY_RATE*sti(PChar.rank)));
			LAi_LoadLocation(Pchar.questTemp.silverfleet.boardinglocation, -1);
			DeleteAttribute(boarding_enemy, "SilverSurferCap");
			DeleteAttribute(Pchar, "questTemp.silverfleet.boardinglocation");
			return true;
		}
	}
	return false;
}
