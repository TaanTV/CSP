
bool PrepareSiege()
{
    int iColony, iNation, iAtaker, n;
    ref rColony;
    aref aData;
    makearef(aData, NullCharacter.Siege);
    n = 0;
    while (n < 10)
    {
        if (rand(100)<=60) // 40 мало все время испанские колонии осаждают причем одни и те же
        {
            iNation = rand(PIRATE);
            iColony = SelectColonyForSiege(iNation);//ранд нация жертва, сразу ищем город
            if (iColony != -1)
            {
                iAtaker = FindEnemyNation2NationWithoutPirates(iNation);//нашли - ищем атакера по врагу
                if (iAtaker != -1 )
                {
                    makeref(rColony, Colonies[iColony]);
                    aData.nation = iAtaker;
                    aData.conation = sti(rColony.nation);
                    aData.colony = rColony.id;
                    aData.island = rColony.island;
                    Log_TestInfo(GetConvertStrWithReplace("Variable_Siege_1", "Logs.txt", "#space#", " ")+iColony);
                    return true;
                }
            }
        }
        else
        {
            //ищем жертву по мах городу
            NationForceBalance(aData);
            iNation = func_max_pos(sti(aData.nation_0), sti(aData.nation_1), sti(aData.nation_2), sti(aData.nation_3));
            iColony = SelectColonyForSiege(iNation);
            if (iColony != -1)
            {
                iAtaker = FindEnemyNation2NationWithoutPirates(iNation);//нашли - ищем атакера по врагу
                if (iAtaker != -1 )
                {
                    makeref(rColony, Colonies[iColony]);
                    aData.nation = iAtaker;
                    aData.conation = sti(rColony.nation);
                    aData.colony = rColony.id;
                    aData.island = rColony.island;
                    Log_TestInfo(GetConvertStrWithReplace("Variable_Siege_2", "Logs.txt", "#space#", " "));
                    return true;
                }
            }
        }
        n++;
    }
    return false;
}

int func_max_pos(int a, int b, int c, int d)
{
	if (a >= b && a >= c && a >= d) return 0;
	if (b >= a && b >= c && b >= d) return 1;
	if (c >= a && c >= b && c >= d) return 2;
	if (d >= a && d >= b && d >= c) return 3;
}

bool CheckQuestColonyList(string sColony)
{
    if (CheckAttribute(pchar, "GenQuest.Intelligence.City" ) && pchar.GenQuest.Intelligence.City == sColony) return false;

    if (CheckAttribute(pchar, "GenQuest.Intelligence.MayorId") &&
        characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].City == sColony) return false;

    //fix не осаждать Барбадос по линейке Блада
    if (CheckAttribute(pchar, "questTemp.CapBloodLine") &&  Pchar.questTemp.CapBloodLine == true && sColony == "Bridgetown") return false;

    if (CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "EndOfQuestLine") return true;

    if (CheckAttribute(pchar, "questTemp.NationQuest"))
    {
		//Захват со сменой владельца исключен паузой мира, вместо них только грабеж должен быть. 
		//Но тут запрет даже осаждать колонии во время национальной линейки. Это очистка бухт от посторонних эскадр, чтоб не мешали квестам. 
		//Но непонятно, почему везде ЛаВега включена в списки. Там же вообще осад не может быть. 
		switch(sti(pchar.questTemp.NationQuest))
        {
            case ENGLAND:
                if (sColony == "SentJons" || sColony == "Beliz"
                || sColony == "Villemstad" || sColony == "PortRoyal"
                || sColony == "SanJuan" || sColony == "LaVega"
                || sColony == "Havana" || sColony == "Santiago") return false;
                break;
                /*SentJons
                Beliz
                Villemstad
                PortRoyal
                SanJuan
                LaVega
                Havana
                Santiago*/

            case FRANCE:
                if (sColony == "FortFrance" || sColony == "Villemstad"
                || sColony == "Havana" || sColony == "Guadeloupe"
                || sColony == "Cumana" || sColony == "Tortuga" || sColony == "PortPax") return false;
            break;
            /*
            FortFrance
            Villemstad
            Havana
            Guadeloupe
            Cumana
            Tortuga
            PortPax
            */


            case SPAIN:
                if (sColony == "PortRoyal" || sColony == "Santiago"
                || sColony == "Villemstad" || sColony == "Maracaibo"
                || sColony == "Tortuga" || sColony == "Panama"
                || sColony == "Cumana" || sColony == "LaVega"
                || sColony == "Havana" || sColony == "SentJons") return false;
            break;
            /*
            PortRoyal
            Santiago
            Villemstad
            Panama
            Maracaibo
            Tortuga
            LaVega
            SentJons
            Cumana
            Havana
            */


            case HOLLAND:
                if (sColony == "Marigo" || sColony == "Villemstad"
                || sColony == "PortRoyal" || sColony == "LaVega"
                || sColony == "Cartahena" || sColony == "Tortuga") return false;
             break;
            /*
             Marigo
             Villemstad
             PortRoyal
             LaVega
             Tortuga
             Cartahena
            */
        }
    }
    return true;
}


void NationForceBalance(aref base)
{
    string nat;

    base.nation_0 = 0;
    base.nation_1 = 0;
    base.nation_2 = 0;
    base.nation_3 = 0;
    base.nation_4 = 0;

    for (int i=0; i<MAX_COLONIES; i++)
	{
        nat = "nation_"+sti(Colonies[i].nation);
        if (Colonies[i].nation != "none") base.(nat) = sti(base.(nat))+ 1;
	}
	Log_TestInfo("Eng = "+base.nation_0);
	Log_TestInfo("Fra = "+base.nation_1);
	Log_TestInfo("Spa = "+base.nation_2);
	Log_TestInfo("Hol = "+base.nation_3);
	Log_TestInfo("Pir = "+base.nation_4);
}

int SelectColonyForSiege(int ination)  // выбираем колонию для нападения
{
    ref AttakColony;
    int i = 0;
    int j = 0;
    bool bb, aa;

    while (i < 20)
    {
        j = rand(MAX_COLONIES-1);
        makeref(AttakColony, Colonies[j]);
        bb = sti(AttakColony.nation) == ination && !CheckAttribute(AttakColony, "HasNoFort");
        aa = CheckAttribute(AttakColony, "FortValue") && sti(AttakColony.HeroOwn) == false;
        if ( bb && aa && CheckQuestColonyList(AttakColony.id))
        {
            //to_do проверка списка Эдди
            return j;
        }
        i++;
    }
    return -1;
/*
    if (i == 15)
    {
        // поругать и всё-таки сгенерить колонию, если конечно это возможно
        if (tempcolony != ination && !bWorldAlivePause)
        {
            SetNationRelationBoth(tempcolony, ination, RELATION_ENEMY)
            Log_TestInfo(GetConvertStrWithReplace("Variable_Siege_3", "Logs.txt", "#space#", " ")+NationShortName(tempcolony)+GetConvertStrWithReplace("Variable_Siege_4", "Logs.txt", "#space#", " ")+NationShortName(ination)+GetConvertStrWithReplace("Variable_Siege_5", "Logs.txt", "#space#", " "));
            //makeref(AttakColony, Colonies[itemp]);
        }
        else return -1;
    }

    return itemp;  */

}


void BeginSiegeMap(string sChar)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    SiegeRumourEx(GetConvertStrWithReplace("Variable_Siege_1", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_2", "SiegeRumours.txt", "#space#", " "), aData.Colony, sti(aData.nation)+10, -1, 2, 1, "citizen,habitue,trader,tavern");
    int idist = makeint(GetDistanceToColony(aData.Colony));
    if (idist != -1 && idist <= 100 )
    {
        Log_TestInfo("Squadron on the map!");
        Map_CreateTrader("none", aData.Colony, sChar, 1);
        return;
    }
    else
    {
        Log_TestInfo("Squadron on the Timer");
        aData.progress = -1;
        string sQuest = "BattleOfTheColony";
        SetTimerCondition(sQuest, 0, 0, 2, false);
        pchar.quest.(sQuest).win_condition = "BattleOfTheColony";
        pchar.quest.(sQuest).function= "BattleOfTheColony";
    }
}

float GetDistanceToColony(string sColony);
{
    if (!IsEntity(loadedLocation))
    {

        int iCnum = FindColony(sColony);
		string sIsland = Colonies[iCnum].island;
		string sTemp = sColony+"_town";

        return GetDistance2D(stf(worldMap.playerShipX), stf(worldMap.playerShipZ),
                            stf(worldMap.islands.(sIsland).(sTemp).position.x),
                            stf(worldMap.islands.(sIsland).(sTemp).position.z));
    }
    else
    {
        int locnum = FindLocation(pchar.location);
        if (locnum != -1 && CheckAttribute(locations[locnum], "townsack") )
        {
            if (sColony == locations[locnum].townsack)
            return makefloat(0);
        }

    }
    return makefloat(-1);
}

void EndSiegeMap()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sHead = FillSquadronGoods();
    Map_CreateTrader(aData.Colony, colonies[FindNonEnemyColonyForNation(sti(aData.nation), true)].id, sHead, 4);
    string sQuest = "ClearSiege";
    SetTimerCondition(sQuest, 0, 0, 5, false);
    pchar.quest.(sQuest).win_condition = "ClearSiege";
    pchar.quest.(sQuest).function= "SiegeClear";
    //--> слухи
    SiegeRumourEx(GetConvertStrWithReplace("Variable_Siege_3", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_4", "SiegeRumours.txt", "#space#", " "), aData.Colony, sti(aData.conation), -1, 5, 3, "citizen,habitue,trader,tavern");
    //<-- слухи

}

string FillSquadronGoods()
{
    aref aData;
    ref rchar;

    makearef(aData, NullCharacter.Siege);
    Group_FreeAllDead();
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";

    ref rGroup = Group_GetGroupByID(sGroup);
    rGroup.Task = AITASK_MOVE;
    rchar = Group_GetGroupCommander(sGroup);
    return rchar.id;
}

int MakeSiegeSquadron(int ination)
{
    ref sld;
    aref aData;
    string sCapId = NationShortName(ination)+"SiegeCap_";
    string sGroup = "Sea_" + sCapId + "1";
    makearef(aData, NullCharacter.Siege);
    aData.iSquadronPower = 0;

	// Filter ship types.
	string sNation = GetNationNameByType(ination);

	int suitableShipTypes[SHIP_TYPES_QUANTITY];
	int bestShipTypesCount = 0;
	int usualShipTypesCount = 0;
	int i = 0;

	while (ShipsTypes[i].Class != 2) i++;

	while (ShipsTypes[i].CannonsQuantity < 90)
	{
		if ((ShipsTypes[i].Type.War == true) && (ShipsTypes[i].nation.(sNation) == true))
		{
			suitableShipTypes[usualShipTypesCount] = i;
			usualShipTypesCount++;
		}
		i++;
	}

	while (i < SHIP_TYPES_QUANTITY-1)//шлюпку не проверяем
	{
		if (CheckAttribute(ShipsTypes[i], "CanEncounter") && ShipsTypes[i].CanEncounter == true)
		{
			if ((ShipsTypes[i].Type.War == true) && (ShipsTypes[i].nation.(sNation) == true))
			{
				suitableShipTypes[usualShipTypesCount + bestShipTypesCount] = i;
				bestShipTypesCount++;
			}
		}
		i++;
	}

	int bestShipCount = rand(3) - 1;
	if (bestShipCount < 0) bestShipCount = 0;
	aData.ShipCount = 5 + rand(2);

	Log_TestInfo("Default ship types count: " + usualShipTypesCount + " best ship types count: " + bestShipTypesCount);
	Log_TestInfo("Best ships count in squadron: " + bestShipCount + " all ships count in squadron: " + aData.ShipCount);

	int itmp = 0;
	int shipType;

	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);

    for (i = 1; i <= sti(aData.ShipCount); i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, ination, 30, true));

        sld.dialog.filename = "Capitans_dialog.c";
	    sld.dialog.currentnode = "Siegehelp";
	    sld.DeckDialogNode = "Siegehelp";

		if (i <= bestShipCount)
		{
			shipType = suitableShipTypes[usualShipTypesCount + rand(bestShipTypesCount - 1)];
			itmp = makeint(shipType * 19 / 124);
		}
		else
		{
			shipType = suitableShipTypes[rand(usualShipTypesCount - 1)];
			itmp = makeint(shipType * 15 / 87);
		}

		SetRandomNameToCharacter(sld);
		SetRandomNameToShip(sld);
		sld.Ship.Type = GenerateShipExt(ShipType, 1, sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);

		DeleteAttribute(sld,"ship.sails");
		RepairMasts(sld);
		DeleteAttribute(sld,"ship.blots");

		Fantom_SetCannons(sld, "war");
		Fantom_SetBalls(sld, "war");
		Fantom_SetGoods(sld, "war");

        aData.iSquadronPower = sti(aData.iSquadronPower) + itmp;
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.mapEnc.type = "war";
        sld.mapEnc.worldMapShip = Nations[ination].worldMapShip+"_manowar";
        sld.mapEnc.Name = GetConvertStrWithReplace("Variable_Siege_1", "Names.txt", "#space#", " ");
        Group_AddCharacter(sGroup, sCapId + i);
        if (i == 1) SetRandGeraldSail(sld, sti(sld.Nation)); // homo Гербы
    }
    aData.iSquadronPower = sti(aData.iSquadronPower) - 19;
    Log_TestInfo(GetConvertStrWithReplace("Variable_Siege_6", "Logs.txt", "#space#", " ")+aData.iSquadronPower+GetConvertStrWithReplace("Variable_Siege_7", "Logs.txt", "#space#", " "));
    Log_TestInfo(GetConvertStrWithReplace("Variable_Siege_8", "Logs.txt", "#space#", " ")+sti(colonies[FindColony(aData.colony)].FortValue)+GetConvertStrWithReplace("Variable_Siege_9", "Logs.txt", "#space#", " "));

    Group_SetGroupCommander(sGroup, sCapId+ "1");
    ref rGroup = Group_GetGroupByID(sGroup);
    rGroup.Task = AITASK_MOVE;
    //Group_LockTask(sGroup);
    //Group_SetTaskAttack(sGroup, PLAYER_GROUP);
    return sti(aData.iSquadronPower);
}

void Siege_DailyUpdate()
{
	int iDays;
    if(!actLoadFlag)
    {
		iDays = GetQuestPastDayParam("Siege_DailyUpdate");
		if (iDays >= 20+rand(20))
		{   trace("CreateSiege!");
	        CreateSiege("");
	        SaveCurrentQuestDateParam("Siege_DailyUpdate");
		}
	}
}

void CreateSiege(string tmp)
{
    SiegeClear("");
    ref rColony;
    aref aData;
    makearef(aData, NullCharacter.Siege);

    if (PrepareSiege())
    {
       // aData.nation = 3;//rand(3);//2
       // aData.conation = 0;
       // aData.colony = "SentJons";
       // aData.island = "Antigua";

        aData.progress = 0;
        DeleteAttribute(aData, "loot");
        DeleteAttribute(aData, "PlayerHelpMayor");
        DeleteAttribute(aData, "HelpColony");
        string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
        Log_TestInfo("CreateSiege "+NationShortName(sti(aData.nation)));
        makeref(rColony, Colonies[FindColony(aData.colony)]);
		Log_TestInfo("WhoIsUnderSiege "+rColony.id);
        MakeSiegeSquadron(sti(aData.nation));
        aData.SiegeHP = Group_GetPowerHP(sGroup);
        //Log_TestInfo
        trace("Attak "+aData.colony);
        //Log_TestInfo
        trace("SiegeHP: "+aData.SiegeHP);
        BeginSiegeMap(NationShortName(sti(aData.nation))+"SiegeCap_1");
        aData.isSiege = 1;
    }
}

void SiegeProgress()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    int i = sti(aData.progress);

    switch (i)
    {
        case 0:
	        Log_TestInfo(GetConvertStrWithReplace("Variable_Siege_10", "Logs.txt", "#space#", " "));
	        BattleOfTheColony("");
        break;

        case 1:
        	SiegeClear("");
        break

    }
    i++;
    aData.progress = i;
}

int CheckSquadronInjuri()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    float maxHP = stf(aData.SiegeHP);
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
    return makeint(Group_GetPowerHP(sGroup)*(100/maxHP));
}

int CheckFortInjuri()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    ref FC = GetFortCommander(aData.colony);
    float maxCannons = 10;
    if (CheckAttribute(FC, "fort.cannons.quantity"))
    {
    	maxCannons = sti(FC.fort.cannons.quantity);
    }
    if (CheckAttribute(FC, "Fort.Mode") && sti(FC.Fort.Mode) == FORT_DEAD) return 0;
    return makeint(makeint(GetCurrentShipHP(FC)/100)*(100/maxCannons)));
}

void LeaveBattle(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sQuest = "SiegeResult";
    pchar.quest.(sQuest).win_condition.l1 = "ExitFromLocation";
    pchar.quest.(sQuest).win_condition.l1.location = aData.island;
    pchar.quest.(sQuest).win_condition = "SiegeResult";
    pchar.quest.(sQuest).function = "SiegeResult";
}

void LeaveTown(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
    string sGroup = "Sea_"+sCap+"1";
    ref NPChar = Group_GetGroupCommander(sGroup);

    AfterTownBattle();  // все, все свободны
    LAi_LoginInCaptureTown(NPChar, false);
    aData.win = 1;
    EndOfTheSiege("End");
    NPChar.location = "";
}

void SiegeResult(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
    int fortDamage = CheckFortInjuri();
    int SquadronDamage = CheckSquadronInjuri();
    Log_TestInfo("fortDamage: "+ fortDamage);
    Log_TestInfo("SquadronDamage: "+ SquadronDamage);
    aData.win =((ifortPower)*fortDamage < sti(aData.iSquadronPower)*SquadronDamage );
    Log_TestInfo(" Win: "+aData.win);

    string sQuest = "LeaveBattle";
    pchar.quest.(sQuest).win_condition.l1 = "location";
    pchar.quest.(sQuest).win_condition.l1.location = aData.island;
    pchar.quest.(sQuest).function= "LeaveBattle";
    CheckGroupCommander("");

}

void CheckGroupCommander(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
    string sGroup = "Sea_"+sCap+"1";
    ref rchar = Group_GetGroupCommander(sGroup);
    bool bhasCom = false;

    if ( !CharacterIsDead(rchar)) return;

    int CapNum = sti(aData.ShipCount);

    for(int k = 1; k <= CapNum ; k++)
    {
       if (GetCharacterIndex(sCap+k) != -1 && !CharacterIsDead(CharacterFromID(sCap+k)))
       {
            Group_AddCharacter(sGroup,sCap + k);
            if (!bhasCom)
            {
                Group_SetGroupCommander(sGroup, sCap+k );
                bhasCom = true;
            }

       }
    }
    //Group_SetAddress(sGroup, aData.island, "ships", "");
}


void BattleOfTheColony(string tmp)
{
    aref aData;
    ref rColony;
    makearef(aData, NullCharacter.Siege);
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";

    if (CheckAttribute(PChar, "quest.BattleOfTheColony")) Pchar.quest.BattleOfTheColony.over = "yes";
    CheckGroupCommander("");

    makeref(rColony, Colonies[FindColony(aData.Colony)]);
    rColony.DontSetShipInPort = true;
    rColony.Siege = true;
    //Group_SetTaskNone(sGroup);

    ref FC = GetFortCommander(aData.colony);
    Group_SetTaskMove(sGroup, stf(FC.ship.pos.x), stf(FC.ship.pos.z));
    //Group_SetAddress(sGroup, aData.island, "IslandShips1", "ship_4");
    Group_SetAddress(sGroup, aData.island, "Quest_ships", "reload_fort1_siege");//  to_do

    string sQuest = "EndOfTheSiege";
    int ifort = sti(colonies[FindColony(aData.colony)].FortValue);
    int btime = ifort - sti(aData.iSquadronPower);
    aData.win =(ifort < sti(aData.iSquadronPower));
    int SiegeTime = 14 - makeint((abs(btime))/10);
    aData.SiegeTime = SiegeTime;
    Log_TestInfo("Siege period: "+SiegeTime);
    Log_TestInfo("Win: "+aData.win);
    SetTimerCondition(sQuest, 0, 0, SiegeTime, false);
    pchar.quest.(sQuest).win_condition = "EndOfTheSiege";
    pchar.quest.(sQuest).function= "EndOfTheSiege";

    sQuest = "LeaveBattle";
    pchar.quest.(sQuest).win_condition.l1 = "location";
    pchar.quest.(sQuest).win_condition.l1.location = aData.island;
    pchar.quest.(sQuest).function= "LeaveBattle";

    sQuest = "PlayerKillSquadron";
    pchar.quest.(sQuest).win_condition.l1 = "Group_Death";
    pchar.quest.(sQuest).win_condition.l1.group = sGroup;
    pchar.quest.(sQuest).function= "PlayerKillSquadron";

    SaveCurrentQuestDateParam("Siege_Start");
    aData.tmpID1 = SiegeRumourEx(GetConvertStrWithReplace("Variable_Siege_5", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_6", "SiegeRumours.txt", "#space#", " "), aData.Colony, sti(aData.nation)+10, -1, sti(aData.SiegeTime)-2, 3, "citizen,habitue,trader,tavern");
    aData.tmpID2 = SiegeRumour("OnSiege_1", "", sti(aData.conation)+10, sti(aData.nation)+10, sti(aData.SiegeTime)-2, 3);
    aData.tmpID3 = SiegeRumour("OnSiege_2", "", sti(aData.nation), -1, sti(aData.SiegeTime)-2, 3);
    aData.tmpID4 = SiegeRumour("OnSiege_3", "!"+aData.Colony, sti(aData.conation), -1, sti(aData.SiegeTime)-2, 3);
}

void PlayerKillSquadron(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    Log_TestInfo("Player Kill Squadron!");
    aData.win = 0;
    if (GetNationRelation2MainCharacter(sti(aData.nation))) aData.PlayerHelpMayor = true;
    EndOfTheSiege("End");
}

void  EndOfTheSiege(string tmp)
{
    ref sld;
    int l, f;
    string tmpName;

	Log_TestInfo("Siege End");

    bool bcapt = false;
    aref aData;

    makearef(aData, NullCharacter.Siege);

    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
    ref rColony = GetColonyByIndex(FindColony(aData.colony));
    int ifortPower = sti(rColony.FortValue);
    int idist = makeint(GetDistanceToColony(aData.Colony));

    if(idist == -1 || idist > 60 || tmp != "")
    {
        // чистим слухи
        for (l = 1; l <= 4; l++)
        {
            tmpName = "tmpID"+l;
            if (CheckAttribute(aData, tmpName))
            {
                f = FindRumour(sti(aData.(tmpName)));
                Rumour[f].state = 0;
                DeleteAttribute(aData, tmpName);
            }
        }
        // меняем диалог
        ref comand = Group_GetGroupCommander(sGroup);
        if (!CheckAttribute(comand, "dialog")
        || !CheckAttribute(comand, "dialog")
        || comand.dialog.currentnode != "no_return_02"
        || comand.DeckDialogNode != "no_return_02")
        {
            comand.dialog.currentnode = "First time";
		    comand.DeckDialogNode = "First time";
        }
        // возвращаем мэру обычный диалог
        DeleteAttribute(rColony, "Siege"); //снимаем осаду

        if (CheckAttribute(PChar, "quest.EndOfTheSiegeLater.again"))
        {
            DeleteAttribute(Pchar, "quest.EndOfTheSiegeLater.again");
            Pchar.quest.EndOfTheSiegeLater.over = "yes";
        }
        if (CheckAttribute(PChar, "quest.SiegeResult")) Pchar.quest.SiegeResult.over = "yes";
        if (CheckAttribute(PChar, "quest.LeaveBattle")) Pchar.quest.LeaveBattle.over = "yes";
        if (sti(aData.win) == 1)
        {
            aData.loot = 200000+100000*makeint(ifortPower/30);
            Log_TestInfo("Siege loot ="+aData.loot);
            if (CheckSquadronInjuri()>= 70)
            {
                int icon = Group_GetCharactersNum(sGroup);
                ref rgrp = Group_GetGroupByID(sGroup);
                int i, j;
                int qrew;

                for (i =0; i < icon; i++)
                {
                    j = Group_GetCharacterIndexR(rgrp, i);
                    if (j != -1) sld = &Characters[j];
                    Fantom_SetGoods(sld, "trade");
                    if (i > 3 && rand(1) == 0)
                    {
                        Group_DelCharacter(sGroup, sld.id);
                        Log_TestInfo(sld.id+" - dead!");
                        DeleteCharacter(sld);
                    }
                    else
                    {
                        if (rand(3)==1)
						{
							sld.ship.masts.mast3 = 1;//а если нет такой мачты?
						}
                        else
						{
							sld.ship.SP = sti(sld.ship.SP) - 10*(rand(3)+1);//а это не работает. нужно отложенный урон делать
						}
    	                sld.ship.HP = sti(sld.ship.HP) - makeint(sti(sld.ship.HP)/(2+rand(2)));
    	                qrew = GetMaxCrewQuantity(sld);
    	                SetCrewQuantity(sld, qrew - makeint(qrew/(2+rand(1))));
                    }
                }
            }
            EndSiegeMap();
            if (ifortPower <= 60 ) //Решение о взятии колонии себе взвешивается очень тщательно!
            {
                bcapt = (rand(3)==2)
            }
            else
            {  // Если колония важная, то вероятность меньше
               bcapt = sti(aData.iSquadronPower) > ifortPower && rand(abs(ifortPower-60)) == 0 ;
            }
            if (!bWorldAlivePause && bcapt && !CheckAttribute(rColony, "notCaptured"))
            {
                SetCaptureTownByNation(aData.colony, sti(aData.nation))

                SiegeRumour(GetConvertStrWithReplace("Variable_Siege_7", "SiegeRumours.txt", "#space#", " ")+ NationNameGenitive(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_8", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_9", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.conation))+GetConvertStrWithReplace("Variable_Siege_10", "SiegeRumours.txt", "#space#", " "), aData.Colony, sti(aData.nation), -1, 15, 3);
                SiegeRumour(GetConvertStrWithReplace("Variable_Siege_11", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_12", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.conation))+GetConvertStrWithReplace("Variable_Siege_13", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_14", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+" - "+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_15", "SiegeRumours.txt", "#space#", " "), "", sti(aData.conation)+10, sti(aData.nation)+10, 30, 3);
                SiegeRumour(GetConvertStrWithReplace("Variable_Siege_16", "SiegeRumours.txt", "#space#", " ")+NationNamePeople(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_17", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_18", "SiegeRumours.txt", "#space#", " "), "", sti(aData.conation), -1, 30, 3);
                SiegeRumour(GetConvertStrWithReplace("Variable_Siege_19", "SiegeRumours.txt", "#space#", " ")+ NationNameGenitive(sti(aData.conation))+GetConvertStrWithReplace("Variable_Siege_20", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+". ", ("!"+aData.Colony), sti(aData.nation), -1, 30, 3);

            }
            else
            {
                SetNull2StoreMan(rColony)// нулим магазин при захвате города эскадрой
                SetNull2Deposit(aData.colony);// нулим ростовщиков
				ClearIslandShips(aData.colony);

                SiegeRumourEx(GetConvertStrWithReplace("Variable_Siege_21", "SiegeRumours.txt", "#space#", " ")+ NationNameGenitive(sti(aData.conation))+GetConvertStrWithReplace("Variable_Siege_22", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_23", "SiegeRumours.txt", "#space#", " "), aData.Colony, sti(aData.conation), -1, 15, 3, "citizen,habitue,trader,tavern");
                SiegeRumour(GetConvertStrWithReplace("Variable_Siege_24", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_25", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.conation))+GetConvertStrWithReplace("Variable_Siege_26", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_27", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_28", "SiegeRumours.txt", "#space#", " "), "", sti(aData.conation)+10, sti(aData.nation)+10, 30, 3);
                SiegeRumour(GetConvertStrWithReplace("Variable_Siege_29", "SiegeRumours.txt", "#space#", " ")+NationNamePeople(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_30", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_31", "SiegeRumours.txt", "#space#", " ")+NationNamePeople(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_32", "SiegeRumours.txt", "#space#", " "), "!"+aData.Colony, sti(aData.conation), -1, 30, 3);
                SiegeRumour(GetConvertStrWithReplace("Variable_Siege_33", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.conation))+GetConvertStrWithReplace("Variable_Siege_34", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_35", "SiegeRumours.txt", "#space#", " "), "!"+aData.Colony, sti(aData.nation), -1, 30, 3);
            }
            FortDestroy();// уничтожаем форт
            Group_SetAddressNone(sGroup);

            Log_TestInfo("Siege Finish - Squadron win!");
        }
        else
        {
            SiegeRumourEx(GetConvertStrWithReplace("Variable_Siege_36", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_37", "SiegeRumours.txt", "#space#", " "), aData.Colony, sti(aData.conation), -1, 15, 3, "citizen,habitue,trader,tavern");
            SiegeRumour(GetConvertStrWithReplace("Variable_Siege_38", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_39", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.conation))+GetConvertStrWithReplace("Variable_Siege_40", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_41", "SiegeRumours.txt", "#space#", " "), "", sti(aData.conation)+10, sti(aData.nation)+10, 30, 3);
            SiegeRumour(GetConvertStrWithReplace("Variable_Siege_42", "SiegeRumours.txt", "#space#", " ")+NationNamePeople(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_43", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_44", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_45", "SiegeRumours.txt", "#space#", " "), "!"+aData.Colony, sti(aData.conation), -1, 30, 3);
            SiegeRumour(GetConvertStrWithReplace("Variable_Siege_46", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.conation))+GetConvertStrWithReplace("Variable_Siege_47", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_48", "SiegeRumours.txt", "#space#", " "), "!"+aData.Colony, sti(aData.nation), -1, 30, 3);
            SiegeClear("");
            Log_TestInfo("Siege Finish - Squadron defeat!");
        }
    }
    else
    {
        Log_TestInfo("End Siege Later!");
        string sQuest = "EndOfTheSiegeLater";
        SetTimerCondition(sQuest, 0, 0, 1, true);
        pchar.quest.(sQuest).win_condition = "EndOfTheSiegeLater";
        pchar.quest.(sQuest).function= "EndOfTheSiege";
    }



}
void FortDestroy()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    int ind = GetCharacterIndex(aData.colony + " Fort Commander");
    ref FC;

	if (ind == -1) return;

    FC = &Characters[ind];
    FC.Fort.Mode = FORT_DEAD;
	// data of frot die
	FC.Fort.DieTime.Year = GetDataYear();
	FC.Fort.DieTime.Month = GetDataMonth();
	FC.Fort.DieTime.Day = GetDataDay();
	FC.Fort.DieTime.Time = GetTime();
	Event(FORT_DESTROYED, "l", sti(FC.index));
    Log_TestInfo("FORT_DEAD");
}

void SiegeClear(string tmp)
{
    aref aData;
    ref rColony;
    if (CheckAttribute( NullCharacter, "Siege.Colony"))
    {
        makearef(aData, NullCharacter.Siege);
        makeref(rColony, Colonies[FindColony(aData.Colony)]);
        DeleteAttribute(rColony, "DontSetShipInPort"); //возвращаем жизнь
        DeleteAttribute(rColony, "Siege"); //снимаем осаду
        if (CheckAttribute(PChar, "quest.Union_with_Escadra")) Pchar.quest.Union_with_Escadra.over = "yes";
        if (CheckAttribute(PChar, "quest.BattleOfTheColony")) Pchar.quest.BattleOfTheColony.over = "yes";
        if (CheckAttribute(PChar, "quest.EndOfTheSiege")) Pchar.quest.EndOfTheSiege.over = "yes";
        if (CheckAttribute(PChar, "quest.ClearSiege")) Pchar.quest.ClearSiege.over = "yes";
        if (CheckAttribute(PChar, "quest.LeaveBattle")) Pchar.quest.LeaveBattle.over = "yes";
        if (CheckAttribute(PChar, "quest.SiegeResult")) Pchar.quest.SiegeResult.over = "yes";
        if (CheckAttribute(PChar, "quest.PlayerKillSquadron")) Pchar.quest.PlayerKillSquadron.over = "yes";
        if (CheckAttribute(PChar, "Siege_Start")) DeleteAttribute(PChar, "Siege_Start");
        string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
        aData.progress = 1;
        Group_SetAddressNone(sGroup);
        Group_DeleteGroup(sGroup);
        aData.isSiege = 0;
		Log_TestInfo(GetConvertStrWithReplace("Variable_Siege_11", "Logs.txt", "#space#", " ")+rColony.id+GetConvertStrWithReplace("Variable_Siege_12", "Logs.txt", "#space#", " "));
		DeleteAttribute(rColony, "AlreadyGen");
    }
}

void SiegeSquadronOnMap(string _chrId)
{
    Group_FreeAllDead();
    //string sQuest = "CheckGroupCommander";
    //pchar.quest.(sQuest).win_condition.l1 = "MapEnter";
    //pchar.quest.(sQuest).win_condition = "CheckGroupCommander";
    //pchar.quest.(sQuest).function = "CheckGroupCommander";
}

//////////////////////////////СЛУХИ////////////////////////////////////////////
int SiegeRumour(string stext, string sCity, int nation1, int nation2, int terms, int qty)
{
   return SiegeRumourEX(stext, sCity, nation1, nation2, terms, qty, "all")
}

int SiegeRumourEX(string stext, string sCity, int nation1, int nation2, int terms, int qty, string tip)
{
    object tmp;

    if (findsubstr(stext, "OnSiege_" , 0) != -1)
	{
		tmp.event = stext;
	}
    else
	{
		tmp.event = "none";
	}

    tmp.text = stext;
    tmp.state = qty;//кол-во раз
    tmp.tip = tip;
    tmp.rep = "none";
    if (sCity != "") tmp.City = sCity;
	//10, 11, 12, 13 - исключить эти нации из слухов
    if (nation1 != -1)
    {
        if (nation1 > 5)
        {
	    	tmp.nonation.n1 = nation1 - 10;
	    }
	    else
		{
			tmp.onlynation = nation1; //локализация
		}
	}

	if (nation2 != -1 && nation2 > 5)
	tmp.nonation.n2 = nation2 - 10;

    tmp.starttime = 0;
    tmp.actualtime = terms; //сроки
    tmp.next = "none";
    return AddRumorR(&tmp);
}

string NationNameSK(int nat)
{
    if(LanguageGetLanguage() != "russian")
    {
        switch (nat)
        {
            case ENGLAND:
            	return "english";
            break;

            case FRANCE:
            	return "french";
            break;

            case SPAIN:
            	return "spanish";
            break;

            case HOLLAND:
            	return "dutch";
            break;
        }
    }
    else
    {
        switch (nat)
        {
            case ENGLAND:
            	return "английск";
            break;

            case FRANCE:
            	return "французск";
            break;

            case SPAIN:
            	return "испанск";
            break;

            case HOLLAND:
            	return "голландск";
            break;
        }
    }
}

string SiegeRumourText(int inum)
{
    aref aData;
    string sDays;

    makearef(aData, NullCharacter.Siege);

    int iDays = sti(aData.SiegeTime) - GetQuestPastDayParam("Siege_Start");
    sDays = iDays + GetConvertStrWithReplace("Variable_days_with_space", "Interface.txt", "#space#", " ");

    if (iDays < 5) sDays = iDays + GetConvertStrWithReplace("Variable_days_with_space_voc", "Interface.txt", "#space#", " ");
    if (iDays <= 1 ) sDays = GetConvertStr("Variable_couple_hours", "Interface.txt");

    switch (inum)
    {
        case 1:
        	return GetConvertStrWithReplace("Variable_Siege_49", "SiegeRumours.txt", "#space#", " ")+NationNamePeople(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_50", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.conation))+GetConvertStrWithReplace("Variable_Siege_51", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_52", "SiegeRumours.txt", "#space#", " ")+sDays+GetConvertStrWithReplace("Variable_Siege_53", "SiegeRumours.txt", "#space#", " ");
        break;

        case 2:
        	return GetConvertStrWithReplace("Variable_Siege_54", "SiegeRumours.txt", "#space#", " ")+NationNameSK(sti(aData.conation))+GetConvertStrWithReplace("Variable_Siege_55", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_56", "SiegeRumours.txt", "#space#", " ")+sDays+".";
        break;

        case 3:
        	return GetConvertStrWithReplace("Variable_Siege_57", "SiegeRumours.txt", "#space#", " ")+NationNamePeople(sti(aData.nation))+GetConvertStrWithReplace("Variable_Siege_58", "SiegeRumours.txt", "#space#", " ")+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+GetConvertStrWithReplace("Variable_Siege_59", "SiegeRumours.txt", "#space#", " ")+sDays+".";
        break;
    }
}
