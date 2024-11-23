
void QuestComplete(string sQuestName, string qname)
{
	// Lugger -->
	int iBuild = rand(3) + 3;
	// Lugger <--
	// boal -->
	ref sld, npchar;
	aref arOldMapPos, arAll, arPass;
	int     iTemp, i, ShipType, Rank, iRank; // нужно для вычислений любых целых (нации)
    float locx, locy, locz, fTemp;
	string  attrName, Model, Blade, Gun, sTemp, sQuestTown, sQuestTitle; // любые строки для вычислений
	bool   bOk;
	int iChurchGenBanditsCount;

	//#20190329-01
	iTemp = 10;
	//Boyer mod
    float nTimeAdd;

	if (bQuestLogShow)
    {
	    Log_Info("Quest completed : " + sQuestName + "  param = " + qname);
		trace("Quest completed : " + sQuestName + "  param = " + qname + " " + GetQuestBookDataDigit());
	}
	// boal <--
	if (CheckAttribute(pchar, "quest." + qname + ".function"))
	{
		string sFunction = pchar.quest.(qname).function;
		call sFunction(qname);
		return;
	}

	switch(sQuestName)
	{
		// boal -->
		// смена отношений от времени
        // boal все теперь проверяется 15-25 день при расчете состояния мира = изменение в 5 процентов - ранд(100) > 95
        case "Nation_Legend":
            SetTimerCondition("Nation_Legend", 0, 0, 15+rand(10), true);
			// тут чиним стророжевики -->
			if (!bSeaActive && !bAbordageStarted)
            {
              //  RepairAllDefenderFortShips();
            }
            // тут чиним стророжевики <--
            if (rand(100) > 93 && !bWorldAlivePause)
            {
                if(IsEntity(worldMap))
                {
                    LaunchNationLegend();
                }else{
                    if (!bQuestCheckProcessFreeze) // можно показать
					{
					    DoQuestCheckDelay("Nation_Legend_Map", 1.5);
					}
					else
					{
	      				Pchar.quest.Nation_Legend_Map.win_condition.l1 = "MapEnter";
	                    Pchar.quest.Nation_Legend_Map.win_condition = "Nation_Legend_Map";
			        }
                }
        	}
        break;

        case "Nation_Legend_Map":
            if (!bQuestCheckProcessFreeze) // можно показать
			{
                LaunchNationLegend();
            }else{
                Pchar.quest.Nation_Legend_Map_TEST.win_condition.l1 = "MapEnter";
                Pchar.quest.Nation_Legend_Map_TEST.win_condition = "Nation_Legend_Map";
            }
        break;
		case "LocTeleport":
			TeleportCharacterToPos(pchar, stf(pchar.locx), stf(pchar.locy), stf(pchar.locz));
		break;
		// начало игры, туториал
		case "Tut_StartGame_CheckMinHP_1":
			if (!CheckAttribute(pchar, "HeroParam.Teach_beat"))
			{
				pchar.HeroParam.Teach_beat	= 0;
			}
			pchar.HeroParam.Teach_beat = sti(pchar.HeroParam.Teach_beat) + 1;
			sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
			bOk = false;
			if (sti(pchar.HeroParam.Teach_beat) == 1 && sti(pchar.HeroParam.Teach_battle) == 1)
			{
				bOk = true;
			}
			else
			{
				if (sti(pchar.HeroParam.Teach_beat) == 2 && sti(pchar.HeroParam.Teach_battle) == 2)
				{
					bOk = true;
					pchar.HeroParam.Teach_beat = 3; // признак, что выиграл
				}
			}
			if (bOk)
			{
				DoQuestCheckDelay("Tut_StartGame_CheckMinHP_Hero", 0.3);
			}
        break;

        case "Tut_StartGame_CheckMinHP_2":
        	if (!CheckAttribute(pchar, "HeroParam.Teach_beat"))
			{
				pchar.HeroParam.Teach_beat	= 0;
			}
			pchar.HeroParam.Teach_beat = sti(pchar.HeroParam.Teach_beat) + 1;
			sld = characterFromID("Sailor_2");
   			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
			if (sti(pchar.HeroParam.Teach_beat) == 2 && sti(pchar.HeroParam.Teach_battle) == 2)
			{
				sld = characterFromID("Sailor_1");
				LAi_SetActorTypeNoGroup(sld);
				pchar.HeroParam.Teach_beat = 3; // признак, что выиграл
				DoQuestCheckDelay("Tut_StartGame_CheckMinHP_Hero", 0.3);
			}
        break;

        case "Tut_StartGame_CheckMinHP_Hero":
        	// запуск диалога
        	LAi_SetActorTypeNoGroup(pchar);
        	sld = characterFromID("Sailor_2");
			LAi_SetActorTypeNoGroup(sld);
			sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(sld);
            PChar.GenQuest.CallFunctionParam = "Tut_StartDialog";
			DoQuestCheckDelay("CallFunctionParam", 2.0);
        break;
		//  Карты сокровищ  ГЕНЕРАТОР -->
        case "SetTreasureFromMap":
            SetTreasureBoxFromMap();
        break;
        //  Карты сокровищ  ГЕНЕРАТОР <--

		case "ArestInResidenceEnd":
            //LAi_LocationFightDisable(&Locations[FindLocation(Pchar.quest.ArestInResidenceEnd.ResidenceLocation)], true);
		    LAi_LockFightMode(Pchar, false); // ножками убежал
        break;
        // ОЗГи
        case "Battle_Hunters_Land":
            Lai_SetPlayerType(pchar);
            LAi_SetFightMode(Pchar, true);
			for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				LAi_RemoveCheckMinHP(sld);
	            LAi_SetWarriorType(sld);
	            //LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	            LAi_group_MoveCharacter(sld, "LAND_HUNTER");

				/* sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter02" + i);
				LAi_RemoveCheckMinHP(sld);
	            LAi_SetWarriorType(sld);
	            //LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	            LAi_group_MoveCharacter(sld, "LAND_HUNTER"); */
			}
            //LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            //LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            //#20190708-01
            LAi_group_SetCheck("LAND_HUNTER", "LandHunter_Afterword");
            LAi_group_SetRelation("LAND_HUNTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LAND_HUNTER", LAI_GROUP_PLAYER, true);
			LAi_group_SetRelation("ENGLAND_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);
			LAi_group_SetRelation("FRANCE_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);
			LAi_group_SetRelation("SPAIN_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);//стража теперь Агрится на ОЗГ
			LAi_group_SetRelation("HOLLAND_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);//04.03 fix Lipsar теперь делаем другом ГГ, нужно для лока матросов
        break;
		case "Battle_PGGHunters_Land":
            Lai_SetPlayerType(pchar);
            LAi_SetFightMode(Pchar, true);
			for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            if (i == 1)
				{
					sld = characterFromID(pchar.chosenTreasureHero);
					DeleteAttribute(pchar,"chosenTreasureHero");
				}
				else
				{
					sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				}
				LAi_RemoveCheckMinHP(sld);
	            LAi_SetWarriorType(sld);
	            //LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	            LAi_group_MoveCharacter(sld, "LAND_HUNTER");
			}
            //LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            //LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            //#20190708-01
            LAi_group_SetCheck("LAND_HUNTER", "LandHunter_Afterword");
            LAi_group_SetRelation("LAND_HUNTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LAND_HUNTER", LAI_GROUP_PLAYER, true);
			//LAi_group_SetRelation("ENGLAND_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);
			//LAi_group_SetRelation("FRANCE_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);
			//LAi_group_SetRelation("SPAIN_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);//стража теперь Агрится на ОЗГ
			//LAi_group_SetRelation("HOLLAND_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);//04.03 fix Lipsar теперь делаем другом ГГ, нужно для лока матросов
        break;
        //#20190708-01
        case "LandHunter_Afterword":
		    LAi_group_SetAlarm("LAND_HUNTER", LAI_GROUP_PLAYER, 0.0);
			LAi_group_SetRelation(LAI_GROUP_PLAYER,"ENGLAND_CITIZENS",LAI_GROUP_NEITRAL);
			LAi_group_SetRelation(LAI_GROUP_PLAYER,"FRANCE_CITIZENS",LAI_GROUP_NEITRAL);//разАгр стражи на ОЗГ до следующего раза
			LAi_group_SetRelation(LAI_GROUP_PLAYER,"SPAIN_CITIZENS",LAI_GROUP_NEITRAL);
			LAi_group_SetRelation(LAI_GROUP_PLAYER,"HOLLAND_CITIZENS",LAI_GROUP_NEITRAL);
		break;
        case "GoAway_Hunters_Land":
            //LAi_SetActorType(Pchar);
            //DoQuestCheckDelay("pchar_back_to_player", 4.0);
            DoQuestCheckDelay("OpenTheDoors", 4.0);
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
            for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				//LAi_RemoveCheckMinHP(sld);  можно пальнуть в спину, тогда по идее будет бой
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
			}
        break;
		case "GoAway_PGGHunters_Land":
            //LAi_SetActorType(Pchar);
            //DoQuestCheckDelay("pchar_back_to_player", 4.0);
            DoQuestCheckDelay("OpenTheDoors", 4.0);
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
            for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            if (i == 1)
				{
					sld = characterFromID(pchar.chosenTreasureHero);
					DeleteAttribute(pchar,"chosenTreasureHero");
				}
				else
				{
					sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				}
				//LAi_RemoveCheckMinHP(sld);  можно пальнуть в спину, тогда по идее будет бой
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
			}
        break;
        //#20190804-01
        case "genericAlarmDown":
            if(CheckAttribute(pchar, "tmpKillGroup")) {
                LAi_group_SetAlarm(pchar.tmpKillGroup, LAI_GROUP_PLAYER, 0.0);
                DeleteAttribute(pchar, "tmpKillGroup");
            }
        break;

		// офицеры выживают!
        case "Survive_In_SeaOfficer":
			sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaOfficerIdx));
			if(!IsCharacterPerkOn(sld, "ShipEscape"))
			{
				LAi_CheckHalfImmortal(sld);
			}
			else
			{
				sld.HPminusDays = 0;
				sld.HPminusDaysNeedtoRestore = 1;
			}
    		PlayVoice("interface\"+LanguageGetLanguage()+"_EvShip1.wav");
			AddPassenger(pchar, sld, false);
    		Log_Info("" + GetFullName(sld) + GetConvertStrWithReplace("Variable_quests_reaction_1", "Logs.txt", "#space#", " ")+NPCharSexPhrase(sld,GetConvertStrWithReplace("Variable_quests_reaction_2", "Logs.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_3", "Logs.txt", "#space#", " "))+GetConvertStrWithReplace("Variable_quests_reaction_4", "Logs.txt", "#space#", " "));
        break;
		case "Get_TreasureBarrel":
			Set_TreasureBarrel();
		break;
        // враги спасшиеся на шлюпках homo
        case "Survive_In_SeaPrisoner":  //homo 22/06/07
            sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaPrisonerIdx));
            iTemp = SetCharToPrisoner(sld);
			if (iTemp != -1)
			{
                npchar = &Characters[iTemp];
                PlayVoice("interface\"+LanguageGetLanguage()+"_EvShip1.wav");
                // лишнее, помер ПГГ и все тут if (findsubstr(sld.id, "PsHero_" , 0) != -1) npchar = sld.id; //homo for navy (ПГГ fix)
                LAi_SetCurHPMax(npchar);
    			sld.location = "none";
    			sld.location.from_sea = "";
                Log_Info(GetFullName(npchar) + GetConvertStrWithReplace("Variable_quests_reaction_5", "Logs.txt", "#space#", " "));
            }
        break;
        //  ЛГ
        case "Survive_In_Sea":
            DeleteSeaEnvironment();
            PChar.GenQuest.GhostShip.KillMe      = sti(PChar.GenQuest.GhostShip.KillMe) + 1;
            PChar.GenQuest.GhostShip.AskAbout    = 2; // опять будет
            Survive_In_Sea_Go2Land();
        break;
        case "GhostShip_Start":
			AddQuestRecord("GhostShipQuest", "3_1");
			n = FindIsland("KhaelRoa");
			Islands[n].alwaysStorm = true;
			Islands[n].storm = true;
			Islands[n].tornado = true;
			pchar.GhostCap.Fight = true;
			if (!CheckAttribute(pchar , "GenQuest.GhostShip.LastBattle")) Pchar.Abordage.Enable = false;
			break;
        case "GhostShip_Dead":
            if (CheckAttribute(pchar , "GenQuest.GhostShip.LastBattle"))
            {
                Log_Info(GetConvertStrWithReplace("Variable_quests_reaction_6", "Logs.txt", "#space#", " "));
                AddQuestRecord("GhostShipQuest", "Dead_2");
				AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("","а"));
                CloseQuestHeader("GhostShipQuest");
				pchar.questdata.KorablPrizrak = 1;

                AddCharacterExpToSkill(PChar, "Leadership", 300);
    		    AddCharacterExpToSkill(PChar, "Sailing", 500);
    		    AddCharacterExpToSkill(PChar, "Accuracy", 500);
    		    AddCharacterExpToSkill(PChar, "Cannons", 500);
    		    AddCharacterExpToSkill(PChar, "Repair", 500);
    		    AddCharacterExpToSkill(PChar, "Defence", 500);
    		    AddCharacterExpToSkill(PChar, "Sneak", 300);
    		    PChar.GenQuest.GhostShip.LastBattleEnd = true;
    		    // меняем парус у корабля, если корабль взял ГГ
				sld = GetRealShip(sti(pchar.GenQuest.GhostShip.ShipType));
				DeleteAttribute(sld, "EmblemedSails.normalTex");
				AddSimpleRumourTip(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_1", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_2", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_3", "AddRumours.txt", "#space#", " ")) +", "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_4", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_5", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_6", "AddRumours.txt", "#space#", " "),
					GetConvertStrWithReplace("Variable_quests_reaction_7", "AddRumours.txt", "#space#", " "),
					GetConvertStrWithReplace("Variable_quests_reaction_8", "AddRumours.txt", "#space#", " ")),
					60, 5, "habitue", "");
            }
            else
            {
                Log_Info(GetConvertStrWithReplace("Variable_quests_reaction_7", "Logs.txt", "#space#", " "));
                AddQuestRecord("GhostShipQuest", "Dead_1");
				AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("ся","ась"));
                AddCharacterExpToSkill(PChar, "Leadership", 600);
    		    AddCharacterExpToSkill(PChar, "Sailing", 1000);
    		    AddCharacterExpToSkill(PChar, "Accuracy", 1000);
    		    AddCharacterExpToSkill(PChar, "Cannons", 1000);
    		    AddCharacterExpToSkill(PChar, "Repair", 1000);
    		    AddCharacterExpToSkill(PChar, "Defence", 1000);
    		    AddCharacterExpToSkill(PChar, "Sneak", 500);
    		    PChar.GenQuest.GhostShip.DeadByMe = sti(PChar.GenQuest.GhostShip.DeadByMe) + 1;
    		    PChar.GenQuest.GhostShip.AskAbout    = 2; // опять будет

    		    /*PChar.GenQuest.VideoAVI        = "Ending";
                PChar.GenQuest.VideoAfterQuest = "";

                DoQuestCheckDelay("PostVideo_Start", 0.1); */
            }
			n = FindIsland("KhaelRoa");
			DeleteAttribute(&Islands[n], "alwaysStorm");
			DeleteAttribute(&Islands[n], "storm");
			DeleteAttribute(&Islands[n], "tornado");
			DeleteAttribute(&Islands[n], "QuestlockWeather");
			DeleteAttribute(&Islands[n], "MaxSeaHeight");
			Pchar.Abordage.Enable = true;
			DeleteAttribute(pchar,"GhostCap.Fight");
        break;

		case "GhostCapt_OfferPrize":
			Sea_CabinStartNow();
			pchar.quest.GhostShipCapInCabin.win_condition.l1          = "location";
			pchar.quest.GhostShipCapInCabin.win_condition.l1.location = Get_My_Cabin();
			pchar.quest.GhostShipCapInCabin.win_condition             = "GhostShipCapInCabinOffer";
		break;

		case "GhostShipCapInCabinOffer":
			chrDisableReloadToLocation = true;
			LAi_LockFightMode(pchar, true);
			sld = CharacterFromID("GhostCapt");
			sld.dialog.currentnode = "GhostCapt_Prize";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "GhostShipCapInCabinDied":
			sld = CharacterFromID("GhostCapt");
			LAi_SetCurHP(sld, 0.0);
		break;

        case "GhostShipHelp": // битва в порту
            chrDisableReloadToLocation = true;
            Pchar.GenQuestFort.FarLocator = true;
			sTemp = "officers"; // не везде есть! :(
            for (i = 0; i < MAX_TOWN_CREW + MOD_SKILL_ENEMY_RATE*3/2; i++)
            {
				sld = SetFantomSkeletForts(sTemp, "", "TOWN_BATTLE_SOLDIERS", "GhostShipCrew");
				if (sld.location.locator == "")
				{
                    sTemp = "rld";
					sld = SetFantomSkeletForts(sTemp, "", "TOWN_BATTLE_SOLDIERS", "GhostShipCrew");
					if (sld.location.locator == "") break;
				}
            }
            // наши
            Pchar.GenQuestFort.FarLocator = false;
            // помощь эскадре
            iTemp = sti(Characters[GetCharacterIndex(pchar.GenQuest.GhostShipWorkId)].nation);

            for (i = 0; i < MAX_ESCADRA_CREW; i++) //всегда 5 даем
            {
            	SetFantomDefenceForts("goto", "", iTemp, LAI_GROUP_PLAYER);
            }

            for (i = MOD_SKILL_ENEMY_RATE*3/2; i < 6; i++)
            {
            	SetFantomDefenceForts("goto", "", iTemp, LAI_GROUP_PLAYER);
            }
            // натравим
            LAi_group_SetHearRadius("TOWN_BATTLE_SOLDIERS", 100.0);
            LAi_group_FightGroupsEx("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

            LAi_group_SetCheck("TOWN_BATTLE_SOLDIERS", "GhostShipHelp_Finish");
            LAi_SetFightMode(Pchar, true);
        break;

		case "GhostShipHelp_Finish":
            LAi_SetFightMode(Pchar, false);
            LAi_grp_alarmactive = false; // конец тревоги
            //#20190505-03
            LAi_group_SetAlarm(LAI_GROUP_PLAYER, "TOWN_BATTLE_SOLDIERS", 0.0);
            LAi_group_SetAlarm(LAI_GROUP_PLAYER, "SKEL_BATTLE_SOLDIERS", 0.0);
            if (!CheckAttribute(pchar , "GenQuest.GhostShip.ChurchHelpStart"))
            {  // город
                sTemp = "GhostShipDone_" + pchar.GenQuest.GhostShipWorkId;
                pchar.GenQuest.(sTemp) = true;
                Log_Info(GetConvertStrWithReplace("Variable_quests_reaction_8", "Logs.txt", "#space#", " "));
                Statistic_AddValue(Pchar, "QuestGhostShipHelp_Done", 1);
                AddQuestRecord("GhostShipQuest", "help_t2");
            }
            else
            { // бухта
                pchar.GenQuest.GhostShip.ChurchHelp = true;
                Log_Info(GetConvertStrWithReplace("Variable_quests_reaction_9", "Logs.txt", "#space#", " "));
                DeleteAttribute(pchar , "GenQuest.GhostShip.ChurchHelpStart")
                //AddQuestTemplate("GhostShipQuest", "church_t2");
                Statistic_AddValue(Pchar, "QuestChurchHelpGhostShip_Done", 1);
            }
            PlaySound("interface\door_locked.wav");
            chrDisableReloadToLocation = false;
            bDisableFastReload         = false;
            SetLocationCapturedState(pchar.location, false);
        break;
        // помощь церкви
        case "GhostShipChurchShorePlace":
            Pchar.GenQuest.Hunter2Pause            = true;

            Pchar.GenQuest.GhostShip.ChurchHelpStart = true;

            chrDisableReloadToLocation = true;
            Pchar.GenQuestFort.FarLocator = true;
			sTemp = "officers"; // не везде есть! :(
            iTemp = 3 + rand(4);
            for (i = 0; i < iTemp; i++)
            {
				sld = SetFantomSkeletForts(sTemp, "", "SKEL_BATTLE_SOLDIERS", "GhostShipCrew");
				if (sld.location.locator == "")
				{
                    sTemp = "reload"; // опасно - может быть лодка!
					sld = SetFantomSkeletForts(sTemp, "", "SKEL_BATTLE_SOLDIERS", "GhostShipCrew");
					if (sld.location.locator == "") break;
				}
            }
            Pchar.GenQuestFort.FarLocator = false;

            // натравим
            LAi_group_SetHearRadius("SKEL_BATTLE_SOLDIERS", 100.0);
            LAi_group_FightGroupsEx("SKEL_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation("SKEL_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

            LAi_group_SetCheck("SKEL_BATTLE_SOLDIERS", "GhostShipHelp_Finish");
            LAi_SetFightMode(Pchar, true);
        break;
        // GhostShipHelp <--
		////////////////////////////////////Квест награда за голову///////////////////////////////////////////////////////
        case "SeaHunterCheck":
            SeaHunterCheck();
        break;

		case "CheckMaxHealthQuest":
            SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
            SetNewDayHealthMax();
        break;

		case "My_Deck_Battle_End":  // запрет битв в трюме -после казни пленных
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], true);
            LAi_SetFightMode(Pchar, false);
        break;
		//  boal 290804 наказание битьем морды -->
        case "PunishmentAction":
            LAi_SetActorTypeNoGroup(PChar);
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
			LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToCharacter(pchar, sld);
            LAi_ActorAnimation(pchar, "attack_force_3", "", 0.9);
            DoQuestCheckDelay("PunishmentAction_1", 0.5);
         break;

         case "PunishmentAction_1":
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
            LAi_ActorAnimation(sld, "hit_attack_2", "PunishmentAction_2", 0.6);
         break;

         case "PunishmentAction_2":
            Lai_SetPlayerType(pchar);
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
            switch (pchar.GenQuest.PunishmentActionManType)
            {
                case "LAi_SetHuberStayType":
                    LAi_SetHuberStayTypeNoGroup(sld);
                    break;

                case "LAi_SetStayType":
                    LAi_SetCitizenTypeNoGroup(sld);
                    break;
            }
		break;
		//  boal 290804 наказание битьем морды <--

		case "SetNPCInShipDeck":  // народ внутри нашего корабля
            if (Pchar.location == Get_My_Cabin())//"My_Cabin" || Pchar.location == "My_Cabin_Small")
	        {
                SetOfficersInCabin();
            }
            else
            {
                if (Pchar.location == "My_Deck")// трюм
                {
                    SetPrisonerInHold();
                }
                else
                {
	                if (Pchar.location == "My_Campus")// кают-компания
	                {
	                    SetOfficersInCampus();
	                }
                }
            }
        break;

		case "SetQuestHoldBox":
			if (Pchar.location == "My_Deck")// трюм
            {
                FillQuestHoldBox(&Locations[FindLocation(Pchar.location)]);
            }
		break;

        case "Munity_on_Ship_Map":
            if (IsEntity(worldMap) && GetCrewQuantity(pchar) > 0 && !IsEquipCharacterByArtefact(pchar, "talisman16"))
        	{
                MunityOnShip("ShipMunity");
            }
        break;

        case "Munity_on_Ship":
            pchar.quest.Munity = "";
            pchar.GenQuest.MunityStart = true;
            PlayVoice("INTERFACE\"+LanguageGetLanguage()+"_GTMutiny_"+rand(2)+".wav");
            InterfaceStates.Buttons.Save.enable = 0;
            LAi_SetFightMode(Pchar, true);

            if (!CheckAttribute(pchar, "GenQuest.SlavesMunity"))
            {
                for (i=1; i<=9; i++)
                {
                    sld = SetFantomDefenceForts("goto", "", PIRATE, LAI_GROUP_TmpEnemy);
                    if (i >= (sti(PChar.Ship.Crew.Quantity)/((8-GetCharacterShipClass(PChar))*8))) break;
                    RemoveCharacterCrew(PChar, (8-GetCharacterShipClass(PChar))*8);
                }
                PChar.Ship.Crew.Morale = 25;
                ChangeCrewExp(PChar, "Soldiers", 2); // бонус на подавление
            }
            else
            {
                for (i=1; i<=9; i++)
                {
                    sld = SetFantomSlaves("goto", "", LAI_GROUP_TmpEnemy);
                    if (i >= (GetCargoGoods(PChar, GOOD_SLAVES)/((8-GetCharacterShipClass(PChar))*8))) break;
                    RemoveCharacterGoodsSelf(PChar, GOOD_SLAVES, (8-GetCharacterShipClass(PChar))*8);
                }
                DeleteAttribute(pchar, "GenQuest.SlavesMunity");
                ChangeCrewExp(PChar, "Soldiers", 3); // бонус на подавление
            }
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "Dead_Munity");
        break;

        case "Dead_Munity":
		if (Pchar.questTemp.MunityOfficerIDX.begin == "1")
		{
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_10", "Logs.txt", "#space#", " "));
			Pchar.questTemp.MunityOfficerIDX.begin = "0";
		}
		else Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_11", "Logs.txt", "#space#", " "));
            InterfaceStates.Buttons.Save.enable = 1;
            pchar.quest.Munity = "Deads";
            LAi_group_SetAlarm(LAI_GROUP_PLAYER, LAI_GROUP_TmpEnemy, 0.0);
            LAi_SetFightMode(Pchar, false);
            DeleteAttribute(pchar, "GenQuest.MunityStart");
        break;

		///  захват форта - город
        case "FreeCaptureForts": // уберем солдат, откроем входы (на всяк случай) при выходе на карту
            TWN_FreeCaptureForts();
        break;
        // захват с суши по диалогу мэра (телепорт)
        case "Town_Capture_Land":
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            //Pchar.GenQuestFort.SoundOff = true;
            DeleteQuestAttribute("Union_with_Escadra");

            SetLocationCapturedState(sld.Default, true);

            DoQuestReloadToLocation(sld.Default.BoardLocation, sld.Default.BoardGroup, sld.Default.BoardLocator, "Capture_Forts");
        break;

        case "Capture_Town_Siege":
            PrepareTownBattle(); // тут только джунгли для этого случая

			if (!CheckAttribute(Pchar, "GenQuestFort.SoundOff"))
			{
            	PlayVoice("INTERFACE\"+LanguageGetLanguage()+"_GTTown2.wav");
            	AddCharacterExpToSkill(Pchar, "Leadership", 100);
			    AddCharacterExpToSkill(Pchar, "Sneak", 100);
            }
            else
            {
                DeleteAttribute(Pchar, "GenQuestFort.SoundOff");
            }
        break;
        // Возвращение губернаторам родные диалоги // boal переделал 251204
        case "Return_Gover_Dialog":
            Characters[sti(PChar.GenQuest.GoverIdx)].dialog.CurrentNode = "First time";
        break;

        case "Return_Gover_Dialog_Exit":
            DoQuestCheckDelay("Return_Gover_Dialog", 0.5);
        break;
        // после битвы в форте сюда
        case "Capture_Forts":
            TWN_Capture_Forts();
        break;

        case "FightInTown":
            TWN_FightInTown();
        break;

        case "FightInTown_OpenNext":
            TWN_FightInTown_OpenNext();
        break;

        case "FightInTown_Finish":
			// в диалоге разрешим - а то можно слинять заранее
            //chrDisableReloadToLocation = false;
            //bDisableFastReload = false; // только после всего захвата
            //LAi_SetFightMode(Pchar, false);
            LAi_grp_alarmactive = false; // конец тревоги
            LAi_group_SetAlarm("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, 0.0);
            //LAi_LocationFightDisable(&Locations[FindLocation(Pchar.location)], true); eddy. не лочить боевки в резиденции
			LAi_LockFightMode(pchar, false);
            LAi_SetFightMode(Pchar, false);
        break;

        //Два пути захвата форта
        // 1 уходим с добычей - в диалоге мэра

        // 2 Если оставляем форт себе
        case "Residence_Captured_Any":
            TWN_Residence_Captured_Any();
        break;

        case "Residence_Captured_Any_02":
   			TWN_Residence_Captured_Any_02();
        break;

        case "Back_Mayor_Type":
            TWN_Back_Mayor_Type();
        break;

        case "CapturedToOurCity":
            LAi_group_SetAlarm("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, 0.0);
            FadeOutMusic(3);
			PlayStereoOGG("music_ship_victory");
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            //DeleteQuestHeader("tales_" + sld.City);  // to_do
            //AddQuestRecord("tales_" + sld.City, "1");

            Log_Info(GetConvertStrWithReplace("Variable_quests_reaction_12", "Logs.txt", "#space#", " ") + GetCityName(sld.City) + GetConvertStrWithReplace("Variable_quests_reaction_13", "Logs.txt", "#space#", " "));

			// убрать контрабандиста
			sTemp = sld.City + "_Smuggler";
			if (GetCharacterIndex(sTemp) >= 0) // не везде есть
			{
				ChangeCharacterAddress(characterFromID(sTemp), "None", ""); // вся логика теперь в рассидки таверны
			}
            SetCaptureTownByHero(sld.City);
            LaunchColonyInfoScreen(); // табличка   to_do даёт вылет :(
			// отсчет для отбития
			//if (!isCityHasFort(sld.City)) // сухопутный город
			sTemp = "Attack_Fort_" + sld.City;
            SetTimerCondition(sTemp, 0, 0, 25 + rand(70), false);
            PChar.Quest.(sTemp).CityId   = sld.City;
			PChar.Quest.(sTemp).function = "TWN_Siege_Any";
        break;
		///////////////////////////////// захват города <--
		//  системные фичи
		case "PostVideo_Start":
            bMainMenuLaunchAfterVideo = true;
			PostVideoAndQuest(PChar.GenQuest.VideoAVI, 100, "PostVideo_After");
        break;

        case "PostVideo_After":
            PostEvent("DoInfoShower",100,"s","");
			DoQuestCheckDelay(PChar.GenQuest.VideoAfterQuest, 0.1);
        break;

        case "SetTimerEvent":
        	attrName = PChar.Quest.(qname).Event;
        	sTemp = PChar.Quest.(qname).Event.Type;
        	Model = PChar.Quest.(qname).Event.Param;
        	SetEventHandler(attrName, attrName, 0);
        	Event(attrName, sTemp, Model);
        	break;

        case "CallFunctionParam":
            attrName = PChar.GenQuest.CallFunctionParam;
            call attrName();
        break;

	// Warship. CallFunctionParam не хочет работать с диалогами, поэтому испльзовать можно эту...
	case "NextFunction":
		DoQuestFunctionDelay(PChar.QuestTemp.NextFunction, 0.1);
		break;

        // вызов табличкм А в это время..
        case "LaunchFrameForm":
            PChar.GenQuest.CallFunctionParam = "LaunchFrameForm";
			DoQuestCheckDelay("CallFunctionParam", stf(pchar.AutoQuest.FrameDelay));
        break;

        case "Move_Govenour":  // переместим губернатора в другой город
            SetTimerCondition("Move_Govenour", 0, 0, 25+rand(10), true);
            Move_Govenour();
        break;

		case "pchar_back_to_player":
			Lai_SetPlayerType(pchar);
		break;

        case "God_hit_us": // это такой прикол - задействовать в ловушки для сундуков(boal)
			iTemp = 10+rand(15);
			if ((MakeInt(pchar.chr_ai.hp)-iTemp) > 0)
            {
    			LAi_SetActorType(PChar);
                LAi_ActorAnimation(PChar, "hit_attack_2", "pchar_back_to_player", 1.0);
            }
			LAi_ApplyCharacterDamage(pchar, iTemp);
			SendMessage(pchar, "lfff", MSG_CHARACTER_VIEWDAMAGE, iTemp, MakeFloat(MakeInt(pchar.chr_ai.hp)), MakeFloat(MakeInt(pchar.chr_ai.hp_max)));
			LAi_CheckKillCharacter(pchar);
		break;
		// диалог с ГГ генератор
        case "TalkSelf_Start":
            StartActorSelfDialog("TalkSelf_Main");
        break;
        // диалог с ГГ квестовые реплики
        case "TalkSelf_Quest":
            StartActorSelfDialog("First time");
        break;
        /////  сидим за столом в таверне ->
        case "alc":
			LAi_Fade("alc_2_prepare", "alc2");
		break;

		case "alc_2_prepare":
			LAi_SetSitType(pchar);
			LAi_SetActorType(characterFromID(pchar.questTemp.friend_in_tavern));
			LAi_ActorSetSitMode(characterFromID(pchar.questTemp.friend_in_tavern));

            sld = characterFromID(pchar.questTemp.friend_in_tavern);
            FreeSitLocator(sld.Default, sld.Default.ToLocator);  // очистим стул
			ChangeCharacterAddressGroup(pchar, sld.Default, sld.Default.group, sld.Default.ToLocator);
		break;

		case "alc2":
			LAi_ActorDialogNow(characterFromID(pchar.questTemp.friend_in_tavern), pchar, "", -1);
		break;

		case "exit_sit":
			if (CheckQuestAttribute("fight_in_tavern", "fight"))
			{
				pchar.quest.fight_in_tavern = "0";
				LAi_SetSitType(characterFromID(pchar.questTemp.friend_in_tavern));
			}
			else
			{
				if (pchar.location.group == "sit")
				{
					LAi_Fade("exit_sit_2", "");
				}
			}
		break;

		case "exit_sit_2":
   			sld = characterFromID(pchar.questTemp.friend_in_tavern);
			LAi_SetSitType(sld);
			LAi_SetPlayerType(pchar);
			//ChangeCharacterAddress(pchar, sld.Default, sld.Default.ToGo);
			PlaceCharacter(pchar, "tables", pchar.location); // ближний к столу
		break;
		// реплика таверншика о запрете драк -->
		case "tavern_keeper":
			attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
            sld = characterFromID(attrName);
			sld.dialog.currentnode = "tavern_keeper";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "tavern_keeper_2", -1);
		break;

		case "tavern_keeper_2":
            attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
            sld = characterFromID(attrName);
			sld.dialog.currentnode = "First time";
			LAi_SetBarmanType(sld);
		break;
		// реплика таверншика о запрете драк <--
 		case "without_memory":
			LAi_Fade("exit_sit_2", "saved_by_off");
			bQuestCheckProcessFreeze = true;
			WaitDate("",0,0,0, 5, 30);
			bQuestCheckProcessFreeze = false;
			RefreshLandTime();
		break;

		case "saved_by_off":
			LAi_SetStayType(pchar);
			Log_Info(GetConvertStrWithReplace("Variable_quests_reaction_14", "Logs.txt", "#space#", " "));

			int oSum = 500 + rand(4500);
			if (makeint(Pchar.money) < oSum) oSum = makeint(Pchar.money);
			AddMoneyToCharacter(pchar, -oSum);
			aref stelsTavern;
			makearef(stelsTavern, pchar.questTemp.stels);
			if (!CheckAttribute(stelsTavern,"tavern")) pchar.questTemp.stels.tavern = 0;
			if (sti(pchar.questTemp.stels.tavern) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, makeint(50+oSum/100));
				pchar.questTemp.stels.tavern = GetDataDay();
			}

   			sld = characterFromID(loadedLocation.fastreload + "_waitress");
   			pchar.questTemp.officiantLocator = sld.location.locator;
   			pchar.questTemp.officiantGroup   = sld.location.group;   // запомнить, где была
			PlaceCharacter(sld, "goto", pchar.location);
			sld.dialog.currentnode = "without_money";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "officiant_back_to_citizen", 5.0, 1.0);
			DoQuestCheckDelay("pchar_back_to_player", 6.0);
		break;

		case "officiant_back_to_citizen":
			LAi_SetPlayerType(pchar);
            sld = characterFromID(loadedLocation.fastreload + "_waitress");
			LAi_SetWaitressType(sld);
			sld.location.locator = pchar.questTemp.officiantLocator;
			sld.location.group   = pchar.questTemp.officiantGroup;
		break;
		//  агенты стран в таверне -->
        case "NationUpdate":
             NationUpdate();
            if(bSeaActive)
            {
                RefreshBattleInterface();
            }
		break;

        case "pir_flag_rise":
			Flag_Change(PIRATE);
		break;
		// агенты в тавернах -->
        case "any_patent_take":
            AddMoneyToCharacter(pchar, -sti(pchar.PatentPrice));

            RemovePatent();

			GiveItem2Character(pchar, "patent_" + pchar.PatentNation);
            EquipCharacterbyItem(pchar, "patent_" + pchar.PatentNation);

            Items[sti(pchar.EquipedPatentId)].TitulCur = 1; // текущ звание сбросим
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0; // счетчик звание сбросим
		break;

        case "fra_flag_rise":
            Flag_Change(FRANCE);
        break;

        case "eng_flag_rise":
            Flag_Change(ENGLAND);
        break;

        case "spa_flag_rise":
            Flag_Change(SPAIN);
        break;

        case "hol_flag_rise":
            Flag_Change(HOLLAND);
        break;

        case "QuestAboardCabinDialog":  // диалог в абордаже, в каюте при достижении минНР
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]; // фантом, тень отца капитана
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
		break;

		case "LAi_ReloadBoarding": // задержка нужна
			LAi_EnableReload();
		    DelEventHandler("Control Activation", "LAi_ActivateReload");
		    //#20171218-01 Re-enable fast action for cabin enter during boarding
            DeleteAttribute(&BattleInterface, "LAi_ActivateReload");
			Log_SetActiveAction("Nothing");
			LAi_ReloadBoarding();
		break;
		// boal <---
		//Blackthorn - Чистка странных слухов
		case "PGGContra_close":
			CloseQuestHeader("Gen_StrangeInfo");
			DeleteAttribute(pchar, "questTemp.PGGContra.Know");
			chr = CharacterFromID(pchar.PGG_Contra_Current);
			if (chr.PGGAi.location != "Dead")
			{
				chr.PGGAi.location.town = chr.PGGAi.location.town.back;
				DeleteAttribute(chr, "PGGAi.location.town.back");
			}
		break;
		//Линейка Виспер
		//Незавершенное дело Билла
		case "W_Smuggling":
			if (CheckAttribute(pchar,"Whisper.Contraband"))
			{
				DeleteAttribute(pchar, "Whisper.Contraband");
				AddQuestRecord("WhisperContraband", "4");
				CloseQuestHeader("WhisperContraband");
			}
			if (CheckAttribute(pchar, "Whisper.ContraSmuggler"))
			{
				DeleteAttribute(pchar, "Whisper.ContraSmuggler");
				WhisperRemoveSmugglersFromShore();
				AddQuestRecord("WhisperContraband", "4");
				CloseQuestHeader("WhisperContraband");
			}
		break;

		//Спавн Пса Войны
		case "Whisper_WarDog":
			WhisperWarDogSeaBattle();
		break;
		//Black Sails
		//ОЗГ от Гатри
		case "Gatri_Hunters":
			if (CheckAttribute(pchar, "BSStart") && !CheckAttribute(pchar, "BSInProgress"))
			{
				ChangeCharacterHunterScore(pchar, "enghunter", 40);
				ChangeCharacterHunterScore(pchar, "frahunter", 40);
				ChangeCharacterHunterScore(pchar, "spahunter", 40);
				ChangeCharacterHunterScore(pchar, "holhunter", 40);
				if (!CheckAttribute(pchar, "BSPrologue.GatriHunters"))	AddQuestRecord("BSPrologue", "4");
				else AddQuestRecord("BSPrologue", "5");
				SetTimerCondition("Gatri_Hunters", 0, 0, 30, true);// Повторяем до завершения квеста
				pchar.BSPrologue.GatriHunters = true;
			}
			else
			{
				SetTimerCondition("Gatri_Hunters", 0, 0, 1, false);
			}
		break;
		//Повторный спавн энки Флинта
		case "Flint_SetCity":
			sld = CharacterFromID("Flint");
			if (!CheckAttribute(sld, "StopSailing"))
			{
				string sGroup = "Flint_Group";
				Group_FindOrCreateGroup(sGroup);
				Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
				Group_LockTask(sGroup);
				Group_AddCharacter(sGroup, sld.id);
				Group_SetGroupCommander(sGroup, sld.id);
				sld.mapEnc.type = "trade";
				sld.mapEnc.worldMapShip = "quest_ship";
				sld.mapEnc.Name = GetConvertStrWithReplace("Variable_quests_reaction_1", "Names.txt", "#space#", " ");
				string sColony = pchar.questTemp.Flint.City;
				int daysQty;
				if (sColony == "PuertoPrincipe")
				{
					pchar.questTemp.Flint.City = "LeFransua";
					daysQty = 8;
				}
				if (sColony == "LeFransua")
				{
					pchar.questTemp.Flint.City = "LaVega";
					daysQty = 5;
				}
				if (sColony == "LaVega")
				{
					pchar.questTemp.Flint.City = "PuertoPrincipe";
					daysQty = 3;
				}
				sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
				sld.DeckDialogNode = "BS_CPNG_15";
				SetTimerCondition("Flint_SetCity", 0, 0, daysQty, false);
				Map_CreateTrader(sColony, pchar.questTemp.Flint.City, sld.id, daysQty);
				Log_TestInfo(GetConvertStrWithReplace("Variable_quests_reaction_15", "Logs.txt", "#space#", " ") + sColony + GetConvertStrWithReplace("Variable_quests_reaction_16", "Logs.txt", "#space#", " ") + pchar.questTemp.Flint.City+GetConvertStrWithReplace("Variable_quests_reaction_17", "Logs.txt", "#space#", " ")+daysQty);
				SetTimerCondition("Flint_SetCity", 0, 0, daysQty, true);
			}
			else
			{
				SetTimerCondition("Flint_SetCity", 0, 0, 1, false);
			}
		break;
        ////////////////////////////////////////////////////////////////////////
		//  Служебный квест контрабандистов - ограничение по времени
		////////////////////////////////////////////////////////////////////////
		case "Rand_Smuggling":
			//слишком падает ChangeContrabandRelation(pchar, -10); // boal
			pchar.quest.KillSmugglers_after.over = "yes";
			RemoveSmugglersFromShore();
		break;

		//Постановка стражников в локацию передачи контрабандистов
		case "Rand_ContrabandInterruption":
			if (CheckCharacterPerk(pchar, "UnlimitedContra") && GetCompanionQuantity(pchar) == 1 && sti(RealShips[sti(pchar.ship.type)].Class) > 2)
			{
				Log_TestInfo(GetConvertStrWithReplace("Variable_quests_reaction_18", "Logs.txt", "#space#", " "));
			}
			else
			{
				pchar.ContraInterruptWaiting = true;
				chrDisableReloadToLocation = true;
				LAi_SetFightMode(pchar, false);
				LAi_LockFightMode(pchar, true);

				// может быть два квеста - или торговля с контром, или корсарское метро
				// iTemp - Нация патруля
				if (CheckAttribute(PChar, "GenQuest.Contraband.GuardNation"))
				{
					iTemp = sti(pchar.GenQuest.Contraband.GuardNation);
				}
				else
				{
					iTemp = sti(pchar.GenQuest.ContraTravel.GuardNation);
				}

				Pchar.quest.contraband.SoldierQty = makeint(2*GetOfficersQuantity(Pchar) + 3);
				// солдаты в начале
				for (i = 2; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
				{
					sld = SetFantomDefenceForts("", "", iTemp, "CoastalGuards");
					attrName = "SoldierIDX"+i;
					Pchar.quest.contraband.(attrName) = sld.index;
					LAi_SetActorType(sld);
					LAi_ActorFollow(sld, Pchar, "", 38);
					sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
					sld.Dialog.CurrentNode = "First time";
					sld.greeting = "Gr_Costal_Guards";
				}
				// вызовем независимо!!!! не тут :) SetCoastalGuardPursuit();

				// офицер в конце
				sld = SetFantomOfficer("", "", iTemp, "CoastalGuards");
				Pchar.quest.contraband.SoldierIDX1 = sld.index;
				LAi_SetActorType(sld);
				sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
				sld.Dialog.CurrentNode = "First time";
				sld.greeting = "Gr_Costal_Guards";

				LAi_ActorDialog(&Characters[makeint(Pchar.quest.contraband.SoldierIDX1)], Pchar, "", 35, 1); // boal 120c - озвереть ждать!!!
				LAi_group_SetCheck("CoastalGuards", "CoastalGuardsAllDead");
				pchar.quest.CoastG.win_condition.l1 = "NPC_Death";
				pchar.quest.CoastG.win_condition.l1.character = sld.id;
				pchar.quest.CoastG.win_condition = "Rand_ContraFinal";
				//LAi_SetActorType(Pchar); //fix
				//LAi_ActorFollow(PChar, &Characters[makeint(Pchar.quest.contraband.SoldierIDX1)], "", 35);
				//Lai_QuestDelay("Rand_CoastalPatrolAppear", 3.0);
			}
		break;

		/*case "Rand_CoastalPatrolAppear":
			//Trace("QUEST Rand_CoastalPatrolAppear reports: Soldier Idx = " + Pchar.quest.contraband.SoldierIDX1);
			//StartQuestMovie(true, true, true);
			//LAi_SetActorTypeNoGroup(Pchar);
			LAi_SetActorType(Pchar);
			LAi_ActorTurnToCharacter(Pchar, &Characters[makeint(Pchar.quest.contraband.SoldierIDX1)]);
			LAi_ActorWaitDialog(Pchar, &Characters[makeint(Pchar.quest.contraband.SoldierIDX1)]);
			//LAi_SetPlayerType(Pchar);
		break;*/

		case "Rand_ContrabandInterruptionAtSeaEnded":
			StopCoastalGuardPursuit();

			AddSimpleRumourCity(GetConvertStrWithReplace("Variable_quests_reaction_9", "AddRumours.txt", "#space#", " ")+
				GetConvertStrWithReplace("Variable_quests_reaction_10", "AddRumours.txt", "#space#", " "), Pchar.quest.contraband.City, 3, 5, "");
		break;

		case "ContraClearGot":
			DeleteAttribute(pchar,"quest.Contraband.SneakGot");
			DeleteAttribute(pchar,"quest.Contraband.InterruptionGot");
		break;
		case "Rand_ContrabandAtSeaEnded":
			StopCoastalGuardPursuit();

			AddSimpleRumourCity(GetConvertStrWithReplace("Variable_quests_reaction_11", "AddRumours.txt", "#space#", " ")+
				GetConvertStrWithReplace("Variable_quests_reaction_12", "AddRumours.txt", "#space#", " "), Pchar.quest.contraband.City, 3, 5, "");
		break;
		case "CoastalGuardsAllDead":
			for (i=1; i<3+makeint(MOD_SKILL_ENEMY_RATE*3/2); i++)
			{
				sTemp = "Rand_Smug0" + i;
				LAi_SetGuardianTypeNoGroup(CharacterFromID(sTemp));
			}
			LAi_grp_alarmactive = false; // конец тревоги
		break;
		//  контрабанды <--

		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - УДАЛЕНИЕ ТЕКУЩЕГО НАПРАВЛЕНИЯ И СИЛЫ ВЕТРА
		/////////////////////////////////////////////////////////////////////////////////
		case "EraseWind":
			DeleteAttribute(pchar, "wind");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - УДАЛЕНИЕ ТЕКУЩЕГО НАПРАВЛЕНИЯ И СИЛЫ ВЕТРА
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// СБРОС СЧЕТЧИКА ДУЭЛЕЙ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////
		case "HabitueSpeakDisable_End":
			DeleteAttribute(pchar,"questTemp.HabitueSpeakDisable");
			DeleteAttribute(pchar,"questTemp.duelQty");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// СБРОС СЧЕТЧИКА ДУЭЛЕЙ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	СЛУЖЕБНЫЕ ФИЧИ
		/////////////////////////////////////////////////////////////////////////////////
		case "hide_weapon":
			LAi_SetFightMode(pchar, false);
			break;

		case "AnyReloadToLocation":
			int iMonth, iDay, iHour, iMin;

			iMonth	= sti(PChar.AutoQuest.delayMonth);
			iDay	= sti(PChar.AutoQuest.delayDay);
			iHour	= sti(PChar.AutoQuest.delayHour);
			iMin	= sti(PChar.AutoQuest.delayMin);

			if(iMonth > 0 || iDay > 0 || iHour > 0 || iMin > 0)
			{
                bQuestCheckProcessFreeze = true;
				WaitDate("", 0, iMonth, iDay, iHour, iMin);
				bQuestCheckProcessFreeze = false;
			}
			DoQuestReloadToLocation(PChar.AutoQuest.idLocation, PChar.AutoQuest.idGroup, PChar.AutoQuest.idLocator, PChar.AutoQuest.questName);
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	СЛУЖЕБНЫЕ ФИЧИ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	START OF ПГГ
		/////////////////////////////////////////////////////////////////////////////////
		case "PGG_Companion_Leave":
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.questTemp.PGG_Companion_Leave.index)];
			PlaceCharacter(sld, "goto", "random_must_be_near");

			sld.Dialog.CurrentNode = "companion_leave";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;

		case "RemoveCharacterFromLocation":
			sld = CharacterFromID(PChar.questTemp.Chr2Remove);
			ChangeCharacterAddressGroup(sld, "None", "", "");
			LAi_SetImmortal(sld, false);
			break;

		case "PGG_Q1AfterShoreFight":
			PGG_Q1AfterShoreFight();
			break;

		case "PGG_Q1AfterDeckFight":
			PGG_Q1AfterDeckFight();
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF ПГГ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	Корсарское метро
		/////////////////////////////////////////////////////////////////////////////////
		case "RemoveTravelSmugglers":
			if (!CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight")) ChangeContrabandRelation(PChar, -10);
			RemoveSmugglersFromShore();

			if (!CheckAttribute(PChar, "GenQuest.contraTravel.ship"))
			{
				AddQuestRecord("Gen_ContrabandTravel", "3");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","а"));
				DeleteAttribute(PChar, "GenQuest.contraTravel");
				CloseQuestHeader("Gen_ContrabandTravel");
			}

			sld = CharacterFromID("Abracham_Gray");
			sld.location.from_sea = "";
			break;

		case "Travel_talkOnDeck":
			//убираем контрабандистов
			RemoveSmugglersFromShore();
			//кинозвезда Абрахам Грей :)
			sld = CharacterFromID("Abracham_Gray");
			//параметры..
			sld.nation = PIRATE;
			Ship_FlagRefresh(PChar); //флаг на лету
			sld.location.from_sea = "";

			LAi_group_MoveCharacter(sld, "TmpEnemy");
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);

			SetActorDialogAny2Pchar("Abracham_Gray", "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "", 1.0);
			//компания....
			iTemp = 3 + rand(3);
			for(i = 0; i < iTemp; i++)
			{
				sTemp = "pirat" + (2 + rand(5));
				attrName = "goto" + (3 + i);
				sld = SetFantomDefenceForts("goto", attrName, PIRATE, "TmpEnemy");
			}
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_ClearAllTargets();
			LAi_SetFightModeForOfficers(false);
			break;

		case "Travel_AfterDeckFight":
			AddQuestRecord("Gen_ContrabandTravel", "5");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","а"));
			StartActorSelfDialog("GenTravel_Main");
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF Корсарское метро
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - ДОСТАВКА ГРУЗА
		/////////////////////////////////////////////////////////////////////////////////
		case "trade_quest_open":
			int iTradeGoods    = sti(pchar.CargoQuest.iTradeGoods);
			int iQuantityGoods = sti(pchar.CargoQuest.iQuantityGoods);
			int iTradeNation   = sti(pchar.CargoQuest.iTradeNation);
			int iMoney         = sti(pchar.CargoQuest.iMoney);
            AddCharacterGoods(pchar, iTradeGoods, iQuantityGoods);
			ref store = GetColonyByIndex(FindColony(characters[GetCharacterIndex(pchar.CargoQuest.GiveTraderID)].city));
            RemoveStoreGoods(&stores[sti(store.StoreNum)],iTradeGoods,iQuantityGoods);
			//задаем квест
			SetTimerCondition("generate_trade_quest", 0, 0, (sti(pchar.CargoQuest.iDaysExpired) + 1), false);

			pchar.quest.generate_trade_quest_progress = "begin";
			ReOpenQuestHeader("DELIVERY_TRADE_QUEST");
			AddQuestRecord("DELIVERY_TRADE_QUEST", "1");

			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));

			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sBaseColony", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.CargoQuest.GiveTraderID)].city+"Gen"));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            attrName = "";
            if (pchar.CargoQuest.iTradeIsland != pchar.CargoQuest.iTradeColony)
            {
                attrName = GetConvertStrWithReplace("Variable_quests_reaction_2", "Names.txt", "#space#", " ") + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Voc");
            }
            AddQuestUserData("DELIVERY_TRADE_QUEST", "island", attrName);
    		AddQuestUserData("DELIVERY_TRADE_QUEST", "sTermsDelivery", FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)));
    		AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            // немного веселой жизни
            //TraderHunterOnMap(); временно залочены
		break;

		case "generate_trade_quest":
			if (pchar.quest.generate_trade_quest_progress == "begin")
			{
				pchar.quest.generate_trade_quest_progress = "failed";
				Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_19", "Logs.txt", "#space#", " "));
				ChangeCharacterReputation(pchar, -10);
				OfficersReaction("bad");
                AddQuestRecord("DELIVERY_TRADE_QUEST", "3");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(sti(pchar.CargoQuest.iTradeGoods)));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - ДОСТАВКА ГРУЗА
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - СПИМ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////
		case "sleep_in_tavern":
			if (CheckAttribute(pchar, "QuestTemp.TakeShotgun") && rand(1) == 1 && !CheckAttribute(pchar , "GenQuest.GhostShip.LastBattleEnd")) // пасхалка
			{
			    DeleteAttribute(pchar, "QuestTemp.TakeShotgun");
			    PChar.GenQuest.CallFunctionParam = "QuestShotgunT102";
			    DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "CallFunctionParam");
			}
			if (CheckAttribute(pchar,"cursed.waitingSkull"))
			{
				if (GetQuestPastDayParam("pchar.questTemp.Cursed") >= 30 || CheckAttribute(pchar,"cursed.Skullbought"))
				{
					PChar.GenQuest.CallFunctionParam = "QuestCursedSceleton";


					DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "CallFunctionParam");
				}
				else
				{
					DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "restore_hp");
				}
			}
			if (CheckAttribute(pchar, "questTemp.UndeadPrologue2") && pchar.rank >= 5)	//Sinistra: Нежить, спим в таверне
			{
			    DeleteAttribute(pchar, "QuestTemp.UndeadPrologue2");
			    DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "UP_DrugPridet_2");
			}
			if (CheckAttribute(pchar, "questTemp.UndeadPrologue3") && pchar.rank >= 10)	//Sinistra: Нежить, спим в таверне
			{
			    DeleteAttribute(pchar, "QuestTemp.UndeadPrologue3");
			    DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "UP_DrugPridet_3");
			}
			else
			{
				DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "restore_hp");
			}
		break;

		case "restore_hp":
			int iOfficer;
			LAi_SetCurHPMax(pchar);
			for (i=1; i<=MAX_NUM_FIGHTERS; i++)
			{
				if (GetOfficersIndex(Pchar, i) != -1)
				{
					iOfficer = GetOfficersIndex(Pchar, i);
					LAi_SetCurHPMax(&characters[iOfficer]);
				}
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - СПИМ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало    LOAN - ОГРАНИЧЕНИЕ ПО ВРЕМЕНИ
		////////////////////////////////////////////////////////////////////////
		case "LoanFindCitizenTimer": // должник
            Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_20", "Logs.txt", "#space#", " "));
            LoansMoneyAvengerAmount(&Characters[GetCharacterIndex(pchar.GenQuest.Loan.FindCitizenNpcharId)], MOD_SKILL_ENEMY_RATE*3+30);
            //DeleteAttribute(pchar, "GenQuest.Loan");
		break;

		case "LoanChestTimer": // сундук
            Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_21", "Logs.txt", "#space#", " "));
            LoansMoneyAvengerAmount(&Characters[GetCharacterIndex(pchar.GenQuest.LoanChest.ChestNpcharId)], MOD_SKILL_ENEMY_RATE*3+15); // кто дал
            LoansMoneyAvengerAmount(&Characters[sti(pchar.GenQuest.LoanChest.TargetIdx)], MOD_SKILL_ENEMY_RATE*3+15);// кому везли
            pchar.GenQuest.LoanChest.Money.Discount = (rand(3)+1)*10; //процент удержания гонорара за просрочку
			//DeleteAttribute(pchar, "GenQuest.LoanChest");
            AddQuestRecord("Gen_LoanTakeChest", "2");
            //CloseQuestHeader("Gen_LoanTakeChest");
		break;

		case "LoansForAll":
			sTemp = pchar.quest.(qname).CityId;
			LoansMoneyAvenger(&Characters[GetCharacterIndex(sTemp + "_usurer")]);
			Characters[GetCharacterIndex(sTemp + "_usurer")].Dialog.CurrentNode = "DeadMotherfucker";
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    LOAN - ОГРАНИЧЕНИЕ ПО ВРЕМЕНИ
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  НАЧАЛО	ЦЕРКОВНЫЕ КВЕСТЫ
		////////////////////////////////////////////////////////////////////////

		// Остальное на функциях
		case "Church_GenQuest2_AskedBand":
			sQuestTown = PChar.GenQuest.ChurchQuest_2.QuestTown;
			PChar.GenQuest.ChurchQuest_2.AskContra_1 = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ел","ла"));
			Log_TestInfo(GetConvertStrWithReplace("Variable_quests_reaction_22", "Logs.txt", "#space#", " "));
			break;

		case "Church_GenQuest2_BanditsIsEnemies":
			sQuestTown = PChar.GenQuest.ChurchQuest_2.QuestTown;
			iChurchGenBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iChurchGenBanditsCount; i++)
			{
				sld = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_Group_MoveCharacter(sld, "Church_GenQuest2_Bandits_Group");
			}
			LAi_SetFightMode(PChar, true);
			LAi_Group_SetRelation("Church_GenQuest2_Bandits_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("Church_GenQuest2_Bandits_Group", LAI_GROUP_PLAYER, true);
			SetFunctionExitFromLocationCondition("Church_GenQuest2_BanditsIsEnemies_2_Clear", PChar.location, false);
			LAi_Group_SetCheckFunction("Church_GenQuest2_Bandits_Group", "Church_GenQuest2_DeadBandits");
			break;

		////////////////////////////////////////////////////////////////////////
		//  КОНЕЦ	ЦЕРКОВНЫЕ КВЕСТЫ
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало    Сопровождение торговца
		////////////////////////////////////////////////////////////////////////
		case "prepare_for_convoy_quest":
			iTemp = sti(colonies[FindColony(pchar.quest.destination)].nation);
            sld = GetCharacter(NPC_GenerateCharacter("QuestTrader", "", "man", "man", makeint((sti(pchar.rank)+60)/4), iTemp, -1, true));
			SetCaptanModelByEncType(sld, "trade");
			sld.reputation = 10 + rand(80);
			sld.Dialog.Filename = "convoy_traider.c";
			sld.dialog.currentnode = "prepare_convoy_quest";
			sld.greeting = "Gr_ConvoyTrader";
			sld.BakNation = sld.nation;
		    sld.Abordage.Enable = true;
			sld.CompanionEnemyEnable = true;
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			pchar.quest.generate_convoy_quest_progress = "begin";
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "convoy_refused":
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
			pchar.quest.generate_convoy_quest_timer.over = "yes";
			if (checkquestattribute("generate_convoy_quest_progress", "completed"))
			{
				OfficersReaction("good");
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 5);
				AddQuestRecord("convoy_quest", "4");
				CloseQuestHeader("convoy_quest");
				AddMoneyToCharacter(pchar, sti(pchar.ConvoyQuest.convoymoney));
				ChangeCharacterReputation(pchar, 1);
				RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
				CloseQuestHeader("convoy_quest");

				AchievementsCounter_genquests(1);
			}
			pchar.quest.generate_convoy_quest_progress = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(characterFromID("QuestTrader"));
			LAi_ActorGoToLocation(characterFromID("QuestTrader"), "reload", LAi_FindFarLocator("reload", locx, locy, locz), "none", "", "", "", 20.0);
		break;

		case "generate_convoy_quest_timer":
            AddQuestRecord("convoy_quest", "2");
			CloseQuestHeader("convoy_quest");
            sld = characterFromID("QuestTrader");
            ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 5+rand(10));// награда
			RemoveCharacterCompanion(Pchar, sld);
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -10);
			pchar.quest.generate_convoy_quest_progress = "";
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
		break;

		case "generate_convoy_quest_failed": // торговец умер
			ChangeCharacterReputation(pchar, -5);
			OfficersReaction("bad");
            RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
			pchar.quest.generate_convoy_quest_progress = "";
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
            pchar.quest.generate_convoy_quest_timer.over  = "yes";
            AddQuestRecord("convoy_quest", "3");
			CloseQuestHeader("convoy_quest");
		break;

		case "generate_convoy_quest_completed":
			sld = characterFromID("QuestTrader");
			if (IsCompanion(sld))
			{
				sld.dialog.currentnode = "complete_convoy_quest";
				PlaceCharacter(sld, "goto", pchar.location);
				Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
				chrDisableReloadToLocation = true;
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 10+rand(10));// награда
				OfficersReaction("bad");
				pchar.quest.generate_convoy_quest_progress = "";
				pchar.quest.generate_convoy_quest_failed.over = "yes";
				pchar.quest.generate_convoy_quest_completed.over = "yes";
				pchar.quest.generate_convoy_quest_timer.over  = "yes";
				AddQuestRecord("convoy_quest", "5");
				CloseQuestHeader("convoy_quest");
			}
		break;

		case "convoy_agreeded":
			sld = characterFromID("QuestTrader");
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", "reload1", 2.0, false);
            ReOpenQuestHeader("convoy_quest");
			AddQuestRecord("convoy_quest", "1");
			AddQuestUserData("convoy_quest", "sSex", GetSexPhrase("ся","ась"));
			sTemp = XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + GetConvertStrWithReplace("Variable_which_on", "Interface.txt", "#space#", " ") + XI_ConvertString(GetIslandByCityName(pchar.quest.destination) + "Voc") + ",";
			AddQuestUserData("convoy_quest", "sCity", sTemp);
			AddQuestUserData("convoy_quest", "sDay", FindRussianDaysString(sti(pchar.ConvoyQuest.iDay)));
            AddQuestUserData("convoy_quest", "sMoney", FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney)));
			// по городу вернем его порт
            attrName = GetPortByCityName(pchar.quest.destination);
			pchar.quest.generate_convoy_quest_completed.win_condition.l1 = "Location";
			pchar.quest.generate_convoy_quest_completed.win_condition.l1.location = attrName;
			pchar.quest.generate_convoy_quest_completed.win_condition = "generate_convoy_quest_completed";
			if (rand(2) == 1) TraderHunterOnMap();
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Сопровождение торговца
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало    Доставка пассажира
		////////////////////////////////////////////////////////////////////////
		case "prepare_for_passenger_quest":
			iTemp = sti(colonies[FindColony(sGlobalTemp)].nation);
            Rank = NPC_GenerateCharacter("QuestPassanger", "", "man", "man", makeint((sti(pchar.rank)+60)/4), iTemp, -1, true);
			sld = &characters[Rank];
			sld.id = sld.id + "_" + sld.index; //меняем ID на оригинальный
			sld.reputation = (10 + rand(80));
			SetCaptanModelByEncType(sld, "trade");
			SetRandomNameToCharacter(sld);
			sld.Dialog.Filename = "convoy_passenger.c";
			sld.dialog.currentnode = "prepare_convoy_quest";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "AllPassangersDead": // торговец умер
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			ChangeCharacterReputation(pchar, -5);
            RemovePassenger(PChar, sld);
			sTemp = sld.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = sld.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + sld.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			attrName = sld.index + "convoy_passenger";
			AddQuestRecordEx(attrName, "Gen_convoy_passenger", "3");
            CloseQuestHeader(attrName);
            //#20170629-01 Dialog/follow bug in Passenger quest
            DeleteAttribute(pchar, "tempDlgInterruptPass"));
		break;

		case "AllPassangersTimeOver":
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			sTemp = sld.id;
			Pchar.GenQuest.ConvoyPassenger.(sTemp) = sld.index; //в структуру недовольных
			if (!CheckAttribute(Pchar, "quest.ConvoyMapPassenger"))
			{
				Pchar.quest.ConvoyMapPassenger.win_condition.l1 = "MapEnter";
        		Pchar.quest.ConvoyMapPassenger.win_condition = "AllPassengerDeck";
			}
		break;

		case "AllPassengerDeck": // разговор на палубе
            MakeCloneShipDeck(pchar, true); // подмена палубы
			makearef(arAll, pchar.GenQuest.ConvoyPassenger);
    		iTemp = GetAttributesNum(arAll);
    		for (i=0; i<iTemp; i++)
    		{
    			arPass = GetAttributeN(arAll, i);
				sld = &characters[sti(arPass)];
				ChangeCharacterAddress(sld, "Ship_deck", "goto4");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
    		}
			makearef(arOldMapPos, worldMap.old);
			WdmPrepareMapForAbordage(arOldMapPos);
			DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
			ReloadFromWMtoL_complete();
            pchar.quest.Munity = "";  // признак выхода с палубы
            LAi_LockFightMode(Pchar, true);
        break;

		case "AllPassangersComplited":
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			sTemp = sld.id + "_TimeOver";
            pchar.quest.(sTemp).over = "yes";
			sTemp = sld.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			chrDisableReloadToLocation = true;
			sld.dialog.currentnode = "complete_convoy_quest";
			PlaceCharacter(sld, "goto", "random_must_be");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			//#20170629-01 Dialog/follow bug in Passenger quest
			pchar.tempDlgInterruptPass = pchar.quest.(qname).Idx;
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Доставка пассажира
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало   Ланд энкаунтеры
		////////////////////////////////////////////////////////////////////////
		//------------------- банда грабителей -------------------------
		case "LandEnc_RaidersBegin":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Gang"+ pchar.quest.(qname).LocIdx + "_";
			sld = characterFromId(sTemp + "0");
			fTemp = (stf(locations[reload_location_index].locators_radius.encdetector)-3)/5;
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", fTemp, 0);
			for(i = 1; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				if (sld.id != "none")
				{
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorFollow(sld, pchar, "", -1);
				}
			}
		break;

		case "LandEnc_RaidersBeforeDialog": //если выстрел до диалога
			attrName = locations[reload_location_index].index;
			sTemp = "EncRaiders_" + attrName;
			// iTemp = sti(pchar.quest.(sTemp).EncQty);	// LEO
			iTemp = sti(pchar.quest.(sTemp).EncQty);
			pchar.quest.(sTemp).over = "yes";
			Model = "RaidersGroup_" + attrName; //имя группы
			sTemp = "Gang"+ attrName + "_";
			for(i = 0; i < iTemp; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				//#20190329-01
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, Model);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			//#20190329-01
            LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "LandEnc_RaidersAfrer");
		break;

		case "LandEnc_RaidersAfrer": //чистим за собой
			attrName = locations[reload_location_index].index;
			sTemp = "TimeRaiders_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "RaidersGroup_" + attrName;
			Delay_DeleteGroup(sTemp);
			//#20190328-03
			LAi_group_SetAlarm(sTemp, LAI_GROUP_PLAYER, 0.0);
			Gun = "Raiders_" + attrName;
			AddSimpleRumour(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_13", "AddRumours.txt", "#space#", " ") + GetFullName(pchar) + GetConvertStrWithReplace("Variable_quests_reaction_14", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.(Gun).name + ". "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_15", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_16", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_17", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_18", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_19", "AddRumours.txt", "#space#", " ")) +" "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_20", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_21", "AddRumours.txt", "#space#", " ")) +". "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_22", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_23", "AddRumours.txt", "#space#", " ")) +" - "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_24", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_25", "AddRumours.txt", "#space#", " ")),
				GetConvertStrWithReplace("Variable_quests_reaction_26", "AddRumours.txt", "#space#", " ") + GetFullName(pchar) + GetConvertStrWithReplace("Variable_quests_reaction_27", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_28", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_29", "AddRumours.txt", "#space#", " ")) +", "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_30", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_31", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_32", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.(Gun).name + GetConvertStrWithReplace("Variable_quests_reaction_33", "AddRumours.txt", "#space#", " "),
				GetConvertStrWithReplace("Variable_quests_reaction_34", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.(Gun).name + GetConvertStrWithReplace("Variable_quests_reaction_35", "AddRumours.txt", "#space#", " ") + GetFullName(pchar) + "? "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_36", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_37", "AddRumours.txt", "#space#", " ")) + GetConvertStrWithReplace("Variable_quests_reaction_38", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_39", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_40", "AddRumours.txt", "#space#", " "))), sti(pchar.GenQuest.(Gun).nation), 5, 1);
			DeleteAttribute(pchar, "GenQuest." + Gun); //трем нацию и имя
		break;

		case "LandEnc_RaidersOver": //чистим за собой
			sTemp = "TimeRaiders_" + pchar.quest.(qname).LocIdx;
			iTemp = sti(pchar.quest.(sTemp).EncQty);
			sTemp = "Gang" + pchar.quest.(qname).LocIdx + "_";
			for(i = 0; i < iTemp; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				LAi_RemoveCheckMinHP(CharacterFromID(sTemp + i));
			}
			sTemp = "RaidersGroup_" + pchar.quest.(qname).LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			//#20190328-03
			LAi_group_SetAlarm(sTemp, LAI_GROUP_PLAYER, 0.0);
			pchar.quest.(qname).over = "yes";
			sTemp = "TimeRaiders_" + pchar.quest.(qname).LocIdx;
			pchar.quest.(sTemp).over = "yes";
			sTemp = pchar.quest.(qname).LocIdx;
			DeleteAttribute(pchar, "GenQuest." + sTemp); //трем нацию и имя
		break;
		//------------------- девка в джунлях -------------------------
		case "LandEnc_RapersTalk":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
		break;

		case "LandEnc_RapersBeforeDialog": //если выстрел до диалога
			if (GetCharacterIndex("CangGirl") != -1) LAi_RemoveCheckMinHP(CharacterFromID("CangGirl"));
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_RemoveCheckMinHP(sld);
				//#20190329-01
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			//#20190329-01
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");
			sld = CharacterFromID("CangGirl");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
		break;

		case "LandEnc_RapersAfrer":
		    //#20190328-03
			LAi_group_SetAlarm("EnemyFight", LAI_GROUP_PLAYER, 0.0);
			sGlobalTemp = "Saved_CangGirl";
			sld = CharacterFromID("CangGirl");
			sld.greeting = "Enc_RapersGirl_2";
			sld.dialog.currentnode = "ThanksForHelp";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "LandEnc_RapersBadExit":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_RemoveCheckMinHP(sld);
				sld.lifeDay = 0;
			}
			if (GetCharacterIndex("CangGirl") == -1) // если ГГ собственноручно прибил тетку
			{
				ChangeCharacterReputation(pchar, -3);
				AddSimpleRumour(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_41", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name + GetConvertStrWithReplace("Variable_quests_reaction_42", "AddRumours.txt", "#space#", " "),
					GetConvertStrWithReplace("Variable_quests_reaction_43", "AddRumours.txt", "#space#", " ") + GetFullName(pchar) + GetConvertStrWithReplace("Variable_quests_reaction_44", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name  + GetConvertStrWithReplace("Variable_quests_reaction_45", "AddRumours.txt", "#space#", " "),
					GetConvertStrWithReplace("Variable_quests_reaction_46", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name  + GetConvertStrWithReplace("Variable_quests_reaction_47", "AddRumours.txt", "#space#", " ")), sti(pchar.GenQuest.EncGirl.nation), 5, 1);
			}
			else
			{
				characters[GetCharacterIndex("CangGirl")].lifeDay = 0;
				if (sGlobalTemp == "Saved_CangGirl") // спасли тетку
				{
					if(pchar.GenQuest.EncGirl == "close") // .. и послали её куда подальше
					{
						characters[GetCharacterIndex("CangGirl")].lifeDay = 0;
						DeleteAttribute(pchar, "GenQuest.EncGirl");
					}
					else
					{
						if(!CheckAttribute(pchar, "GenQuest.EncGirl.Ransom"))
						{
							ChangeCharacterReputation(pchar, 5);
							AddSimpleRumour(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_48", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_49", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_50", "AddRumours.txt", "#space#", " ")) +" "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_51", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_52", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_53", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name + GetConvertStrWithReplace("Variable_quests_reaction_54", "AddRumours.txt", "#space#", " ") + GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_55", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_56", "AddRumours.txt", "#space#", " ")),
								GetConvertStrWithReplace("Variable_quests_reaction_57", "AddRumours.txt", "#space#", " ") + GetFullName(pchar) + " "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_58", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_59", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_60", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name + GetConvertStrWithReplace("Variable_quests_reaction_61", "AddRumours.txt", "#space#", " "),
								GetConvertStrWithReplace("Variable_quests_reaction_62", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name + GetConvertStrWithReplace("Variable_quests_reaction_63", "AddRumours.txt", "#space#", " ") + GetMainCharacterNameGen() + "!"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
						}
					}
				}
				else // оставил на растерзание бандитам
				{
					for(i = 1; i <= 3; i++)
					{
						if (GetCharacterIndex("GangMan_" + i) == -1) continue;
						sld = CharacterFromID("GangMan_" + i);
						LAi_RemoveCheckMinHP(sld);
						sld.lifeDay = 0;
					}
					characters[GetCharacterIndex("CangGirl")].lifeDay = 0;
					if(pchar.GenQuest.EncGirl == "Begin_11")
					{
						ChangeCharacterReputation(pchar, -8);
					}
					if(pchar.GenQuest.EncGirl == "Begin_22")
					{
						ChangeCharacterReputation(pchar, -8);
					}
					if(pchar.GenQuest.EncGirl == "Begin_33")
					{
						ChangeCharacterReputation(pchar, -5);
					}
					AddSimpleRumour(RandPhraseSimple(GetConvertStrWithReplace("Variable_quests_reaction_64", "AddRumours.txt", "#space#", " ") + GetFullName(pchar) + GetConvertStrWithReplace("Variable_quests_reaction_65", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name + GetConvertStrWithReplace("Variable_quests_reaction_66", "AddRumours.txt", "#space#", " "),
						GetConvertStrWithReplace("Variable_quests_reaction_67", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_68", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_69", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_70", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name + GetConvertStrWithReplace("Variable_quests_reaction_71", "AddRumours.txt", "#space#", " ")), sti(pchar.GenQuest.EncGirl.nation), 5, 1);
					DeleteAttribute(pchar, "GenQuest.EncGirl"); //трем нацию и имя
				}
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl"); //трем нацию и имя
		break;
		//------------------- девка просит помочь подруге -------------------------
		case "Enc_FriendGirl_after": //если выстрел до диалога
			ChangeCharacterReputation(pchar, -(rand(4)+1));
			if (rand(1))
			{
				AddSimpleRumour(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_72", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name + GetConvertStrWithReplace("Variable_quests_reaction_73", "AddRumours.txt", "#space#", " "),
					GetConvertStrWithReplace("Variable_quests_reaction_74", "AddRumours.txt", "#space#", " ") + GetFullName(pchar) + GetConvertStrWithReplace("Variable_quests_reaction_75", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name  + GetConvertStrWithReplace("Variable_quests_reaction_76", "AddRumours.txt", "#space#", " "),
					GetConvertStrWithReplace("Variable_quests_reaction_77", "AddRumours.txt", "#space#", " ") + pchar.GenQuest.EncGirl.name  + GetConvertStrWithReplace("Variable_quests_reaction_78", "AddRumours.txt", "#space#", " ")), sti(pchar.GenQuest.EncGirl.nation), 5, 1);
			}
		break;
		case "Enc_FriendGirl_afterGang":
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		//------------------- патруль в джунглях -------------------------
		case "LandEnc_PatrolBegin":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Patrol"+ pchar.quest.(qname).LocIdx + "_";
			npchar = characterFromId(sTemp + "0");
			fTemp = (stf(locations[reload_location_index].locators_radius.encdetector)-3)/5;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorDialog(npchar, pchar, "", fTemp, 0);
			for(i = 1; i < iTemp; i++)
			{
				sld = characterFromId(sTemp + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;

		case "LandEnc_PatrolBeforeDialog": //если выстрел до диалога
			attrName = locations[reload_location_index].index;
			sTemp = "EncPatrol_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "PatrolGroup_" + attrName; //имя группы
			sTemp = "Patrol"+ attrName + "_";
			for(i = 0; i < iTemp; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "LandEnc_PatrolAfrer");
		break;

		case "LandEnc_PatrolAfrer": //чистим за собой
			attrName = locations[reload_location_index].index;
			sTemp = "TimePatrol_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "PatrolGroup_" + attrName;
			Delay_DeleteGroup(sTemp);
			//слухи
			AddSimpleRumour(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_79", "AddRumours.txt", "#space#", " "),
				GetConvertStrWithReplace("Variable_quests_reaction_80", "AddRumours.txt", "#space#", " "),
				GetConvertStrWithReplace("Variable_quests_reaction_81", "AddRumours.txt", "#space#", " ")), sti(pchar.GenQuest.(attrName).nation), 5, 1);
			AddSimpleRumour(GetConvertStrWithReplace("Variable_quests_reaction_82", "AddRumours.txt", "#space#", " ") + GetFullName(pchar) + GetConvertStrWithReplace("Variable_quests_reaction_83", "AddRumours.txt", "#space#", " ") + NationNameGenitive(sti(pchar.GenQuest.(attrName).nation)) + GetConvertStrWithReplace("Variable_quests_reaction_84", "AddRumours.txt", "#space#", " ") + NationNamePeople(sti(pchar.GenQuest.(attrName).nation)) + GetConvertStrWithReplace("Variable_quests_reaction_85", "AddRumours.txt", "#space#", " "), sti(pchar.GenQuest.(attrName).nation)+10, 5, 1);
			DeleteAttribute(pchar, "GenQuest." + attrName); //трем нацию патруля, если есть
		break;

		case "LandEnc_PatrolOver": //чистим за собой
			sTemp = pchar.quest.(qname).LocIdx;
			//слухи
			AddSimpleRumour(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_86", "AddRumours.txt", "#space#", " ") + GetMainCharacterNameGen() + GetConvertStrWithReplace("Variable_quests_reaction_87", "AddRumours.txt", "#space#", " "),
				GetConvertStrWithReplace("Variable_quests_reaction_88", "AddRumours.txt", "#space#", " "),
				GetConvertStrWithReplace("Variable_quests_reaction_89", "AddRumours.txt", "#space#", " ")), sti(pchar.GenQuest.(sTemp).nation), 5, 1);
			DeleteAttribute(pchar, "GenQuest." + sTemp); //трем нацию патруля, если есть
			sTemp = "PatrolGroup_" + pchar.quest.(qname).LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			pchar.quest.(qname).over = "yes";
			sTemp = "EncPatrol_" + pchar.quest.(qname).LocIdx;
			pchar.quest.(sTemp).over = "yes";
		break;

		case "DeleteGroupOnExitLocation": //группу нулим
			sTemp = pchar.quest.DeleteGroupOnExitLocation.GroupName;
			LAi_group_Delete(sTemp);
		break;

        case "Followers_activate": //Активация ходока
			for(i = 1; i <= 2; i++)
			{
				if (GetCharacterIndex("Walker_" + i) == -1) continue;
				sld = CharacterFromID("Walker_" + i);
				LAi_SetActorType(sld);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_WalkerHit");
				LAi_group_MoveCharacter(sld, "LandEncGroup");
				LAi_ActorFollow(sld, characterFromID("Walker"), "", -1);
			}

			for(i = 1; i <= 2; i++)
			{
				if (GetCharacterIndex("Walker_sold_" + i) == -1) continue;
				sld = CharacterFromID("Walker_sold_" + i);
				LAi_SetActorType(sld);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_WalkerHit");
				LAi_group_MoveCharacter(sld, "LandEncGroup");
				LAi_ActorFollow(sld, characterFromID("Walker"), "", -1);
			}

			for(i = 1; i <= 2; i++)
			{
				if (GetCharacterIndex("WalkerGirl_husband_"+i) == -1) continue;
				sld = CharacterFromID("WalkerGirl_husband_"+i);
				LAi_SetActorType(sld);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_WalkerGirlGuardHit");
				LAi_group_MoveCharacter(sld, "LandEncGroup");
				LAi_ActorFollow(sld, characterFromID("WalkerGirl"), "", -1);
			}

            for(i = 1; i <= 2; i++)
			{
				if (GetCharacterIndex("WalkerGirl_sold_"+i) == -1) continue;
				sld = CharacterFromID("WalkerGirl_sold_"+i);
				LAi_SetActorType(sld);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_WalkerGirlGuardHit");
				LAi_group_MoveCharacter(sld, "LandEncGroup");
				LAi_ActorFollow(sld, characterFromID("WalkerGirl"), "", -1);
			}
		break;

		case "LandEnc_WalkerGirlGuardHit": //если выстрел в ходока
			sld = CharacterFromID("WalkerGirl_sold");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorTypeNoGroup(sld);

			LAi_group_SetRelation("LandEncGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LandEncGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("LandEncGroup", "LandEnc_WalkerGirlHitAfrer");
		break;

		case "LandEnc_WalkerGirlHusbandHit": //если выстрел в ходока
			sld = CharacterFromID("WalkerGirl_husband");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorTypeNoGroup(sld);

			LAi_group_SetRelation("LandEncGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LandEncGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("LandEncGroup", "LandEnc_WalkerGirlHitAfrer");
		break;

		case "LandEnc_WalkerHit": //если выстрел в ходока
		    sld = CharacterFromID("Walker");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorTypeNoGroup(sld);

			for(i = 1; i < 5; i++)
			{
				if (GetCharacterIndex("Walker_" + i) == -1) continue;
				sld = CharacterFromID("Walker_" + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);

				if (GetCharacterIndex("Walker_sold_" + i) == -1) continue;
				sld = CharacterFromID("Walker_sold_" + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			LAi_group_SetRelation("LandEncGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LandEncGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("LandEncGroup", "LandEnc_WalkerHitAfrer");
		break;

		case "LandEnc_WalkerHitAfrer": //чистим за собой
			LAi_group_SetRelation("LandEncGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;

		case "LandEnc_WalkerGirlHitAfrer": //чистим за собой
			LAi_group_SetRelation("LandEncGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец   Ланд энкаунтеры
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало    Уничтожение банды
		////////////////////////////////////////////////////////////////////////
		case "AllMayorsQuests_Late": //провальное прерывание на все квесты мэра
			sTemp = pchar.GenQuest.questName;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на квест
			pchar.GenQuest.(sTemp) = "Late"; //флаг опоздал
			npchar = characterFromId(pchar.GenQuest.(sTemp).MayorId);
			AddQuestRecord("MayorsQuestsList", "20");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			//снимаем кораблики пирата и торговцев
			if (sTemp == "DestroyPirate")
			{
				Group_DeleteGroup("MQGroupPirate");
				LAi_group_Delete("MayorPirateGroup");
				for (i=0; i<5; i++)
				{
					Group_DeleteGroup("MQGroupAll_" + i);
				}
			}
		break;

		case "DestroyGang_fight":
			if (rand(1))
			{
				chrDisableReloadToLocation = true;
				Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
				LAi_group_Delete("EnemyFight");
				sTemp = pchar.GenQuest.questName;
				pchar.quest.(sTemp).over = "yes"; //снимаем текущее многоразовое прерывание
				ref location = &locations[reload_location_index];
				LAi_LocationFightDisable(location, true);      //лочим возможность начать драку до диалог, это лишнее
				string encGroup = LAi_FindRandomLocator("encdetector");
				sTemp = "locators." + encGroup;
				makearef(arAll, location.(sTemp));
				iTemp = LAi_CalculateRaidersQuantity(GetAttributesNum(arAll)); // кол-во человек в банде
				if (iTemp <= 0 ) iTemp = 1; //если локаторов меньше четырех
				//--> генерим ранг
				if (sti(pchar.rank) > 6)
				{
					if (sti(pchar.rank) > 20) Rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*3*4/iTemp);
					else Rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*3*2.5/iTemp);
				}
				else
				{	//казуалам зеленый свет на начало игры
					if (sti(pchar.rank) > 3) Rank = sti(pchar.rank);
					else
					{
						Rank = 1;
						iTemp = 1;
					}
				}
				//<-- генерим ранг
				string iModel[25];
				iModel[0] = "pirate_1";
				iModel[1] = "pirate_2";
				iModel[2] = "pirate_3";
				iModel[3] = "pirate_4";
				iModel[4] = "pirate_5";
				iModel[5] = "pirate_6";
				iModel[6] = "pirate_7";
				iModel[7] = "pirate_8";
				iModel[8] = "pirate_9";
				iModel[9] = "pirate_10";
				iModel[10] = "pirate_11";
				iModel[11] = "pirate_12";
				iModel[12] = "pirate_13";
				iModel[13] = "pirate_14";
				iModel[14] = "pirate_15";
				iModel[15] = "pirate_16";
				iModel[16] = "pirate_17";
				iModel[17] = "pirate_18";
				iModel[18] = "pirate_19";
				iModel[19] = "pirate_20";
				iModel[20] = "pirate_21";
				iModel[21] = "pirate_22";
				iModel[22] = "pirate_23";
				iModel[23] = "pirate_24";
				iModel[24] = "pirate_25";
				i = 0;
				while(i < iTemp)
				{
					ShipType = rand(24);
					if (iModel[ShipType] != "")
					{
						if (i == 0)
						{   //главарь банды
							int iMainGang = NPC_GenerateCharacter("MayorQuestGang_" + i, iModel[ShipType], "man", "man", Rank, PIRATE, 0, true);
							sld = &characters[iMainGang];
							sld.name = pchar.GenQuest.DestroyGang.name;  //имя главаря
							sld.lastname = pchar.GenQuest.DestroyGang.lastname;
							sld.dialog.filename = "MayorQuests_dialog.c";
							sld.dialog.currentnode = "DestroyGang_begin";
							sld.greeting = "Enc_Raiders";
							sld.SaveItemsForDead   = true; // сохранять на трупе вещи
							sld.DontClearDead = true;  // не убирать труп через 200с
						}
						else sld = GetCharacter(NPC_GenerateCharacter("MayorQuestGang_" + i, iModel[ShipType], "man", "man", Rank, PIRATE, 0, true));
						LAi_SetActorType(sld);
						SetFantomParamFromRank(sld, Rank, true);
						//Получим локатор для логина
						attrName = GetAttributeName(GetAttributeN(arAll, 1));
						ChangeCharacterAddressGroup(sld, location.id, encGroup, attrName);
						LAi_SetActorType(sld);
						if (i == 0) LAi_ActorDialog(sld, pchar, "", -1, 0);
						else LAi_ActorFollow(sld, &characters[iMainGang], "", -1);
						i++;
						iModel[ShipType] = "";
					}
				}
			}
		break;

		case "Kamikazi":
			if (rand(1))
			{
				chrDisableReloadToLocation = true;
				Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
				LAi_group_Delete("EnemyFight");
				sTemp = pchar.GenQuest.questName;
				pchar.quest.(sTemp).over = "yes"; //снимаем текущее многоразовое прерывание
				location = &locations[reload_location_index];
				LAi_LocationFightDisable(location, true);      //лочим возможность начать драку до диалог, это лишнее
				encGroup = LAi_FindRandomLocator("encdetector");
				sTemp = "locators." + encGroup;
				makearef(arAll, location.(sTemp));

				iMainGang = NPC_GenerateCharacter("MayorQuestGang_0", "Skel_6", "skeleton", "man", 100, PIRATE, 0, true);
				sld = &characters[iMainGang];
				sld.name = pchar.GenQuest.DestroyGang.name;  //имя главаря
				sld.lastname = pchar.GenQuest.DestroyGang.lastname;
				sld.dialog.filename = "Kamikazi.c";
				sld.dialog.currentnode = "Kamikazi";
				sld.greeting = "";
				sld.SaveItemsForDead   = true; // сохранять на трупе вещи
				sld.DontClearDead = true;  // не убирать труп через 200с
				LAi_SetActorType(sld);
				SetFantomParamFromRank(sld, Rank, true);
				//Получим локатор для логина
				attrName = GetAttributeName(GetAttributeN(arAll, 1));
				ChangeCharacterAddressGroup(sld, location.id, encGroup, attrName);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				// PlaySound("Interface\P_Kamikadze_SS.wav");
				LAi_CharacterPlaySound(pchar, "P_Kamikadze_SS");
			}
		break;

		case "DestroyGang_SuddenAttack":
			for(i = 0; i < 30; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
		break;

		case "DestroyGang_Afrer":
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			Delay_DeleteGroup("EnemyFight");
			//#20190328-03
			LAi_group_SetAlarm("EnemyFight", LAI_GROUP_PLAYER, 0.0);
			makearef(arAll, pchar.GenQuest.DestroyGang);
			pchar.GenQuest.DestroyGang = "Execute"; //флаг выполнил успешно
			sTemp = GetFullName(&characters[GetCharacterIndex(arAll.MayorId)]);
			// судовой журнал
			AddQuestRecord("MayorsQuestsList", "2");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arAll));
			// слухи
			AddSimpleRumour(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_90", "AddRumours.txt", "#space#", " ") + sTemp + GetConvertStrWithReplace("Variable_quests_reaction_91", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_92", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_93", "AddRumours.txt", "#space#", " ")) +" " + GetMainCharacterNameDat() + GetConvertStrWithReplace("Variable_quests_reaction_94", "AddRumours.txt", "#space#", " ") + GetFullName(arAll) + GetConvertStrWithReplace("Variable_quests_reaction_95", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_96", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_97", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_98", "AddRumours.txt", "#space#", " "),
				""+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_99", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_100", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_101", "AddRumours.txt", "#space#", " ") + GetFullName(arAll) + GetConvertStrWithReplace("Variable_quests_reaction_102", "AddRumours.txt", "#space#", " ")+ GetSexPhrase("",GetConvertStrWithReplace("Variable_quests_reaction_103", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_104", "AddRumours.txt", "#space#", " ")+ GetSexPhrase("",GetConvertStrWithReplace("Variable_quests_reaction_105", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_106", "AddRumours.txt", "#space#", " "),
				GetConvertStrWithReplace("Variable_quests_reaction_107", "AddRumours.txt", "#space#", " ") + GetMainCharacterNameDat() + GetConvertStrWithReplace("Variable_quests_reaction_108", "AddRumours.txt", "#space#", " ") + GetFullName(arAll) + GetConvertStrWithReplace("Variable_quests_reaction_109", "AddRumours.txt", "#space#", " ")), sti(characters[GetCharacterIndex(arAll.MayorId)].nation), 5, 1);
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Уничтожение банды
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало    Поиск лазутчика в городе
		////////////////////////////////////////////////////////////////////////
        case "SeekSpy_login":
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City"))
			{	//шпион на улице
				sTemp = pchar.GenQuest.questName;
				pchar.quest.(sTemp).over = "yes"; //снимаем текущее многоразовое прерывание
				sld = GetCharacter(NPC_GenerateCharacter("MayorQuestSpy", "citiz_"+(rand(11)+1), "man", "man", Rank, PIRATE, sti(pchar.GenQuest.SeekSpy.Terms), false));
				sld.dialog.filename = "MayorQuests_dialog.c";
				sld.dialog.currentnode = "SeekSpy_street";
				sld.city = characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city;
				sld.greeting = "cit_common";
				LAi_SetLoginTime(sld, 6.0, 21.99);
				//SetFantomParamFromRank(sld, Rank, true);
				LAi_SetCitizenType(sld);
				iTemp = sti(characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].nation);
				sTemp = GetNationNameByType(iTemp) + "_citizens";
				LAi_group_MoveCharacter(sld, sTemp);
				PlaceCharacter(sld, "goto", "random");
			}
			else
			{	//шпион в коммонах
				iTemp = reload_location_index;
				if (locations[iTemp].fastreload == characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city)
				{
					chrDisableReloadToLocation = true;
					LAi_group_Delete("EnemyFight");
					sTemp = pchar.GenQuest.questName;
					pchar.quest.(sTemp).over = "yes"; //снимаем текущее прерывание
					pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
					//--> генерим ранг
					if (sti(pchar.rank) > 6)
					{
						if (sti(pchar.rank) > 20) Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE*3 + 10);
						else Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE*3 + 5);
					}
					else
					{	//казуалам зеленый свет на начало игры
						if (sti(pchar.rank) > 3) Rank = sti(pchar.rank);
						else
						{
							Rank = 1;
						}
					}
					//<-- генерим ранг
					// sld = GetCharacter(NPC_GenerateCharacter("MayorQuestSpy", "citiz_"+(rand(11)+1), "spy", "spy", Rank, PIRATE, 0, true)); // LEO: Убрал от бугуртов недовольных - Gregg :)
					if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("MayorQuestSpy", "citiz_"+(rand(11)+1), "man", "man_fast", Rank, PIRATE, 0, true)); // LEO: Пизда превозмогаторам 08.12.2021
					else sld = GetCharacter(NPC_GenerateCharacter("MayorQuestSpy", "citiz_"+(rand(11)+1), "man", "man", Rank, PIRATE, 0, true));
					sld.dialog.filename = "MayorQuests_dialog.c";
					sld.dialog.currentnode = "SeekSpy_house";
					sld.greeting = "cit_common";
					if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
					sld.money =  1000 + (sti(pchar.rank)*500) + rand(5000);
			        sld.SaveItemsForDead  = true;
					AddBonusEnergyToCharacter(sld, 30);
					FantomMakeCoolFighterWRankDepend(sld,Rank,20+rand(70),20+rand(70),70+(MOD_SKILL_ENEMY_RATE*3*3));//реф,уровень,скилы фехта(дополнительно скейлятся в методе от сложности),навык стрельбы и везения(аналогично),доп хп(аналогично)
					DeleteAllPerksExceptChar(sld);
					SetCharacterPerk(sld, "BasicDefense");
					SetCharacterPerk(sld, "CriticalHit");
					SetCharacterPerk(sld, "HardHitter");
					SetCharacterPerk(sld, "Energaiser");
					SetCharacterPerk(sld, "Ciras");
					SetCharacterPerk(sld, "Gunman");
                    SetCharacterPerk(sld, "Tireless");
                    TakeNItems(sld, "Lockpick", 1+rand(2));
					PlaceCharacter(sld, "goto", "random");
					LAi_SetCitizenType(sld);
					//LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
        break;

		case "SeekSpy_Afrer":
			LAi_group_Delete("EnemyFight");
			pchar.GenQuest.SeekSpy = "Execute"; //флаг выполнил успешно
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)]);
			// судовой журнал
			AddQuestRecord("MayorsQuestsList", "4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			// слухи
			AddSimpleRumour(RandPhraseSimple(GetConvertStrWithReplace("Variable_quests_reaction_110", "AddRumours.txt", "#space#", " ") + sTemp + " "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_111", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_112", "AddRumours.txt", "#space#", " ")) +" " + GetMainCharacterNameDat() + GetConvertStrWithReplace("Variable_quests_reaction_113", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_114", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_115", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_116", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_117", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_118", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_119", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_120", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_121", "AddRumours.txt", "#space#", " ")) +"!",
				GetConvertStrWithReplace("Variable_quests_reaction_122", "AddRumours.txt", "#space#", " ") + GetMainCharacterNameDat() + GetConvertStrWithReplace("Variable_quests_reaction_123", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_124", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_125", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_126", "AddRumours.txt", "#space#", " ")), sti(characters[sti(pchar.GenQuest.SeekSpy.MayorId)].nation), 5, 1);
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Поиск лазутчика в городе
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало    Повод для спешки
		////////////////////////////////////////////////////////////////////////

		case "ReasonToFast_PatrolDied":
			sTemp = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			if(pchar.questTemp.ReasonToFast == "PatrolAfterHunter")
			{
				AddQuestRecord("ReasonToFast", "6");
				AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("","а"));
			}
			if(pchar.questTemp.ReasonToFast == "PatrolAfter")
			{
				AddQuestRecord("ReasonToFast", "8");
			}
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				AddQuestRecord("ReasonToFast", "4");
			}
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther"); //можем говорить с губером

			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1 = "Timer";
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.function = "ReasonToFast_SpeakMayor";

			DeleteAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], "DisableEncounters");
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), sti(pchar.questTemp.ReasonToFast.relation));
			pchar.questTemp.ReasonToFast = "PatrolDied";
			pchar.questTemp.ReasonToFast.speakAfterPatrolDied = false;
			DeleteAttribute(pchar, "GenQuest.HunterScore2Pause"); //вертаем начисление нзг
			DeleteAttribute(pchar, "GenQuest.ReputationNotChange"); //вертаем смену репы
		break;

		case "ReasonToFast_MeetHunter":
			ReasonToFast_GenerateHunter();
		break;

		case "ReasonToFast_PatrolAngry":
			sTemp = "Patrol"+ pchar.questTemp.ReasonToFast.LocIdx + "_";
			sld = CharacterFromID(sTemp + "0");
			sld.dialog.filename = "Enc_Patrol.c";
			sld.dialog.currentnode = "Reason_To_Fast_AfterHunter3";
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, sld);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
			LAi_ActorFollow(sld, pchar,"ActorDialog_Any2Pchar", -1);
		break;

		case "ReasonToFast_HunterGoOut":
			sld = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			sld.LifeDay = 0;
			pchar.questTemp.ReasonToFast = "MeetHunterSuccess";

			sTemp = "Patrol"+ pchar.questTemp.ReasonToFast.LocIdx + "_";
			sld = CharacterFromID(sTemp + "0");
			sld.dialog.filename = "Enc_Patrol.c";
			sld.dialog.currentnode = "Reason_To_Fast_AfterHunter1";
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, sld);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
			LAi_ActorFollow(sld, pchar,"ActorDialog_Any2Pchar", -1);
		break;

		case "ReasonToFast_MeetWithSailor":
			Sea_DeckBoatStartNow(pchar);
		break;

		case "ReasonToFast_ClearVictim":
			pchar.quest.ReasonToFast_SetShip_1.over = "yes";
			pchar.quest.ReasonToFast_SetShip_2.over = "yes";
			sld = characterFromId("VictimCap_1");
			sld.lifeDay = 0;
			Group_DeleteGroup("Sea_Victim_1");
			AddQuestRecord("ReasonToFast","19");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
		break;

		case "ReasonToFast_TrHuntersDied":
			LAi_group_RemoveCheck("LAND_HUNTER");
			LAi_group_Delete("LAND_HUNTER");
			bDisableLandEncounters = false;
			if(pchar.questTemp.ReasonToFast == "GetMap")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", "картой");
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", "ценностями");
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", "деньгами");
			}
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "23");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");
				DeleteAttribute(pchar, "questTemp.ReasonToFast");
			}
		break;

		case "ReasonToFast_LakeyGoOut":
			sld = CharacterFromID("ReasonToFastLakey_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			sld.LifeDay = 0;
		break;

		case "ReasonToFast_GoAway_Hunters_Land":
            DoQuestCheckDelay("OpenTheDoors", 4.0);
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
            for (i=1; i<= sti(pchar.HunterCost.Qty); i++)
			{
				sld = characterFromID("LandHunter0" + i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
				iTemp = GetCharacterIndex("LandHunter0" + i);
				if (iTemp != -1)
				{
					characters[iTemp].lifeDay = 0;
				}
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			bDisableLandEncounters = false;
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
        break;

 		////////////////////////////////////////////////////////////////////////
		//  Конец    Повод для спешки
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало    Уничтожение контры
		////////////////////////////////////////////////////////////////////////
        case "KillSmugglers_after":
            if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[reload_location_index]))
            {
				pchar.GenQuest.KillSmugglers = "Execute"; //флаг выполнил успешно
				pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
				ChangeContrabandRelation(pchar, -30); //репу контры вниз
				Pchar.quest.Contraband.over = "yes";
				CloseQuestHeader("Gen_Contraband");
				pchar.GenQuest.KillSmugglers.shoreId = pchar.location; //бухту запомним, чисто понты :)
				sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)]);
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "9");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", sTemp));
				// слухи
				AddSimpleRumour(RandPhraseSimple(GetConvertStrWithReplace("Variable_quests_reaction_127", "AddRumours.txt", "#space#", " ") + sTemp + GetConvertStrWithReplace("Variable_quests_reaction_128", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_129", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_130", "AddRumours.txt", "#space#", " ")) +" " + GetMainCharacterNameDat() + GetConvertStrWithReplace("Variable_quests_reaction_131", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_132", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_133", "AddRumours.txt", "#space#", " ")) +" "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_134", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_135", "AddRumours.txt", "#space#", " ")) +".",
					GetConvertStrWithReplace("Variable_quests_reaction_136", "AddRumours.txt", "#space#", " ") + sTemp + GetConvertStrWithReplace("Variable_quests_reaction_137", "AddRumours.txt", "#space#", " ") + GetMainCharacterNameDat() + GetConvertStrWithReplace("Variable_quests_reaction_138", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_139", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_140", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_141", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_142", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_143", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_144", "AddRumours.txt", "#space#", " ")), sti(characters[sti(pchar.GenQuest.KillSmugglers.MayorId)].nation), 5, 1);
			}
		break;

        case "KillSmugglers_outShore":
			pchar.quest.KillSmugglers.over = "yes"; //снимаем текущее прерывание
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Уничтожение контры
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало    Поиск и уничтожение пирата
		////////////////////////////////////////////////////////////////////////
 		case "DestroyPirate_Begin":
			npchar = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
			int islandIdx = FindIsland(pchar.GenQuest.DestroyPirate.Areal);
			aref arQuestLoc, arPlTarget, arLocator;
			makearef(arPlTarget, Islands[islandIdx].reload);
			string locatorName, captainId, GroupName;
			//--> генерим ранг
			if (sti(pchar.rank) > 6)
			{
				if (sti(pchar.rank) > 20) Rank = sti(pchar.rank) + 2; //15
				else Rank = sti(pchar.rank);  //10
			}
			else
			{
				Rank = sti(pchar.rank);
			}
			//<-- генерим ранг
			//определяем локаторы для размещения торговцев
			makearef(arQuestLoc, Islands[islandIdx].Quest_ships);
			iTemp = GetAttributesNum(arQuestLoc)-1;
			int n = 0;
			int iRand = rand(4);
			for (i=iTemp; n<5; i--)
			{
				arLocator = GetAttributeN(arQuestLoc, i);
				locatorName = GetAttributeName(arLocator);
				sTemp = "l" + n;
				if (findsubstr(locatorName, "Quest" , 0) != -1)
				{
					if (iRand == n)
					{
						//==> ставим пирата
						Group_AddCharacter("MQGroupPirate", "MQPirate");
						Group_SetType("MQGroupPirate", "pirate");
						Group_SetGroupCommander("MQGroupPirate", "MQPirate");
						Group_LockTask("MQGroupPirate");
						Group_SetAddress("MQGroupPirate", pchar.GenQuest.DestroyPirate.Areal, "Quest_ships", locatorName);
						int iShore = GetAttributesNum(arPlTarget)-1;
						arLocator = GetAttributeN(arPlTarget, iShore);
						locatorName = GetAttributeName(arLocator);
						Group_SetTaskMove("MQGroupPirate", stf(arPlTarget.(locatorName).ships.(sTemp).x), stf(arPlTarget.(locatorName).ships.(sTemp).z))
					}
					else
					{
						//ставим торговцев
						captainId = "MQCaptain_" + n;
						GroupName = "MQGroupAll_" + n;
						sld = GetCharacter(NPC_GenerateCharacter(captainId, "", "man", "man", Rank, sti(npchar.nation), -1, true));
						SetCaptanModelByEncType(sld, "trade");
						DeleteAttribute(sld, "Ship");
						SetShipToFantom(sld, "trade", true);
						sld.Ship.Mode = "Trade";
						sld.AlwaysSandbankManeuver = true;
						sld.DontRansackCaptain = true;  //fix
						Group_AddCharacter(GroupName, captainId);
						Group_SetGroupCommander(GroupName, captainId);
						Group_SetAddress(GroupName, pchar.GenQuest.DestroyPirate.Areal, "Quest_ships", locatorName);
						Group_SetTaskMove(GroupName, stf(arPlTarget.l1.ships.(sTemp).x), stf(arPlTarget.l1.ships.(sTemp).z));
					}
					n++;
				}
			}
			//сформируем строку с типом корабля, пригодится
			sld = characterFromId("MQPirate");
			iTemp = RealShips[sti(sld.ship.type)].basetype;
			string sTempMan = GetConvertStrWithReplace("Variable_pirate_ship_man", "Interface.txt", "#space#", " ");
			string sTempWoman = GetConvertStrWithReplace("Variable_pirate_ship_woman", "Interface.txt", "#space#", " ");
			pchar.GenQuest.DestroyPirate.ShipType = GetShipSexWord(ShipsTypes[iTemp].name,
				sTempMan + XI_ConvertString(ShipsTypes[iTemp].name),
				sTempWoman + XI_ConvertString(ShipsTypes[iTemp].name + "Gen"));
			//прерывание на смерть пирата
			pchar.quest.DestroyPirate.win_condition.l1 = "NPC_Death";
			pchar.quest.DestroyPirate.win_condition.l1.character = "MQPirate";
			pchar.quest.DestroyPirate.win_condition = "DestroyPirate_after";
			//таймер
			SetTimerCondition("DestroyPirate_Late", 0, 0, sti(pchar.GenQuest.DestroyPirate.Terms), false);
			//судовой журнал
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyPirate.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyPirate.Money)));
		break;

		case "DestroyPirate_WithoutFight":
			pchar.quest.Munity = "Deads";  // откроем выход
			sld = characterFromId("MQPirate");
			sld.money = pchar.money;
			pchar.money = 0;
			Ship_SetTaskRunaway(SECONDARY_TASK, sti(sld.index), 1); //сваливаем
		break;

		case "DestroyPirate_FightInDeck":
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			Rank = 5 + sti(MOD_SKILL_ENEMY_RATE*3);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<Rank; i++)
			{
				iTemp = GetCharacterIndex("saylor_0"+i);
				if ( iTemp == -1)
				{
					iTemp = NPC_GenerateCharacter("saylor_0" + i, "pirate_"+(rand(9)+1) , "man", "man", 10, PIRATE, 0, true);
					ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				}
				LAi_group_MoveCharacter(&characters[iTemp], "EnemyFight");
			}
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DestroyPirate_TeamIsDead");
		break;

		case "DestroyPirate_TeamIsDead":
      		Pchar.quest.DestroyPirate_PirateIsOut.win_condition.l1 = "ExitFromSea";
			Pchar.quest.DestroyPirate_PirateIsOut.win_condition = "DestroyPirate_PirateIsOut";
			LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(loadedLocation, true);
			DoQuestCheckDelay("TalkSelf_Quest", 0.4); //диалог сам-на-сам
		break;

		case "DestroyPirate_PirateIsOut":
			pchar.quest.DestroyPirate_Late.over = "yes"; //снимаем таймер
			pchar.GenQuest.DestroyPirate = "PirateIsOut"; //флаг пират свалил
			npchar = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
			LAi_group_Delete("MayorPirateGroup");
			Group_DeleteGroup("MQGroupPirate");
			for (i=0; i<5; i++)
			{
				Group_DeleteGroup("MQGroupAll_" + i);
			}
			// слухи
			AddSimpleRumour(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_145", "AddRumours.txt", "#space#", " ") + GetMainCharacterNameGen() + GetConvertStrWithReplace("Variable_quests_reaction_146", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_147", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_148", "AddRumours.txt", "#space#", " ")) +"...",
				GetConvertStrWithReplace("Variable_quests_reaction_149", "AddRumours.txt", "#space#", " "),
				GetConvertStrWithReplace("Variable_quests_reaction_150", "AddRumours.txt", "#space#", " ") + GetFullName(pchar) + GetConvertStrWithReplace("Variable_quests_reaction_151", "AddRumours.txt", "#space#", " ")), sti(npchar.nation), 5, 1);
		break;

		case "DestroyPirate_after":
			pchar.quest.DestroyPirate_PirateIsOut.over = "yes"; //снимаем прерывание на ушёл с поля боя
			pchar.quest.DestroyPirate_Late.over = "yes"; //снимаем таймер
			LAi_group_Delete("MayorPirateGroup");
			Group_DeleteGroup("MQGroupPirate");
			pchar.GenQuest.DestroyPirate = "Execute"; //флаг выполнил успешно
			npchar = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
			// судовой журнал
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "ShipType", GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyPirate.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyPirate.Money)));
			// слухи
			AddSimpleRumour(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_152", "AddRumours.txt", "#space#", " ") + GetFullName(npchar) + GetConvertStrWithReplace("Variable_quests_reaction_153", "AddRumours.txt", "#space#", " ") + GetMainCharacterNameDat() + GetConvertStrWithReplace("Variable_quests_reaction_154", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_155", "AddRumours.txt", "#space#", " "),кэп нашGetConvertStrWithReplace("Variable_quests_reaction_156", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_157", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_158", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_159", "AddRumours.txt", "#space#", " ")) +" " + GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType) + "!",
				""+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_160", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_161", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_162", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_163", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_164", "AddRumours.txt", "#space#", " ")) +" "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_165", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_166", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_quests_reaction_167", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_168", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_169", "AddRumours.txt", "#space#", " ")) +" " + GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType) + "!",
				GetConvertStrWithReplace("Variable_quests_reaction_170", "AddRumours.txt", "#space#", " ") + XI_ConvertString("Colony"+npchar.city+"Gen") + GetConvertStrWithReplace("Variable_quests_reaction_171", "AddRumours.txt", "#space#", " ") + GetMainCharacterNameDat() + GetConvertStrWithReplace("Variable_quests_reaction_172", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_173", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_174", "AddRumours.txt", "#space#", " ")) +" "+ GetSexPhrase(GetConvertStrWithReplace("Variable_quests_reaction_175", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_quests_reaction_176", "AddRumours.txt", "#space#", " ")) +" " + GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType) + "!"), sti(npchar.nation), 5, 1);
		break;

		case "DestroyPirate_Late":
			if (bSeaActive)
			{
      			Pchar.quest.AllMayorsQuests_Late.win_condition.l1 = "ExitFromSea";
				Pchar.quest.AllMayorsQuests_Late.win_condition = "AllMayorsQuests_Late";
			}
			else
			{
				DoQuestCheckDelay("AllMayorsQuests_Late", 0.1);
			}
		break;

		case "DestroyPirate_toShore":
			sTemp = pchar.GenQuest.questName;
			pchar.quest.DestroyPirate_Late.over = "yes"; //снимаем таймер
			pchar.GenQuest.(sTemp) = "Found";
			npchar = characterFromId(pchar.GenQuest.(sTemp).MayorId);
			int lngFileID = LanguageOpenFile("LocLables.txt");
			attrName = LanguageConvertString(lngFileID, pchar.GenQuest.DestroyPirate.outShoreId);
			//судовой журнал
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "Shore", attrName);
			// слухи
			AddSimpleRumour(LinkRandPhrase(GetConvertStrWithReplace("Variable_quests_reaction_177", "AddRumours.txt", "#space#", " ") + GetFullName(npchar) + GetConvertStrWithReplace("Variable_quests_reaction_178", "AddRumours.txt", "#space#", " ") + GetMainCharacterNameDat() + GetConvertStrWithReplace("Variable_quests_reaction_179", "AddRumours.txt", "#space#", " ") + GetMainCharacterNameGen() + GetConvertStrWithReplace("Variable_quests_reaction_180", "AddRumours.txt", "#space#", " "),
				GetConvertStrWithReplace("Variable_quests_reaction_181", "AddRumours.txt", "#space#", " "),
				GetConvertStrWithReplace("Variable_quests_reaction_182", "AddRumours.txt", "#space#", " ")), sti(npchar.nation), 5, 1);
			//снимаем кораблики пирата и торговцев
			LAi_group_Delete("MayorPirateGroup");
			Group_DeleteGroup("MQGroupPirate");
			for (i=0; i<5; i++)
			{
				Group_DeleteGroup("MQGroupAll_" + i);
			}
			pchar.money = 0;
			pchar.quest.Munity = "Deads";
			pchar.location.from_sea = npchar.city + "_town";
			//--> ВОТ ЗДЕСЬ МЕТОД НА РЕЛОАД ИЗ ПАЛУБЫ В БУХТУ
			DoReloadFromDeckToLocation(pchar.GenQuest.DestroyPirate.outShoreId, "reload", "sea");
			//<-- ВОТ ЗДЕСЬ МЕТОД НА РЕЛОАД ИЗ ПАЛУБЫ В БУХТУ
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Поиск и уничтожение пирата
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало   Генератор - Поручение капитана "Операция 'Галеон'"
		////////////////////////////////////////////////////////////////////////

		case "CaptainComission_FightInDeck":
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			Rank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE*3);
			LAi_group_Delete("EnemyFight");
			for (i=1; i < 5; i++)
			{
				sld = characterFromID("saylor_0" + i);
				sld.rank = Rank;
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "CaptainComission_TeamIsDead");
		break;

		case "CaptainComission_TeamIsDead":
      		pchar.quest.CaptainComission_CapIsOut.win_condition.l1 = "ExitFromSea";
			pchar.quest.CaptainComission_CapIsOut.function = "CaptainComission_CapIsOut";
			pchar.quest.CaptainComission_CapIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_CapIsDead.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapIsDead.function = "CaptainComission_CapIsDead";
			LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(loadedLocation, true);
			DoQuestCheckDelay("TalkSelf_Quest", 0.4); //диалог сам-на-сам
		break;

		case "CaptainComission_TalkCanoneer":
			LAi_Fade("CaptainComission_TalkCanoneer_prepare", "CaptainComission_TalkCanoneer2");
		break;

		case "CaptainComission_TalkCanoneer_prepare":
			LAi_SetSitType(pchar);
			sld = characterFromID("CapComission_Canoneer");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			ChangeCharacterAddressGroup(pchar, pchar.GenQuest.CaptainComission.City + "_tavern", "sit", "sit_front2");
		break;

		case "CaptainComission_TalkCanoneer2":
			LAi_ActorDialogNow(characterFromID("CapComission_Canoneer"), pchar, "", -1);
		break;

		case "CaptainComission_exit_sit":
			if (pchar.location.group == "sit")
			{
				LAi_Fade("CaptainComission_exit_sit_2", "");
			}
		break;

		case "CaptainComission_exit_sit_2":
   			sld = characterFromID("CapComission_Canoneer");
			LAi_SetSitType(sld);
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location); // ближний к столу
		break;

		case "CaptainComission_GangDialog_1":
			sld = characterFromID("Gang_0");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "CaptainComission_MapEnterAfterShoreBattle":
			for (i = 1; i <=3; i++)
			{
				iTemp = GetCharacterIndex("Pirate_Captain0" + i);
				if (iTemp != -1)
				{
					characters[iTemp].lifeDay = 0;
				}
			}
			Group_DeleteGroup("Pirate_Guards");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;

		case "CaptainComission_GenerateCapJail":
			sld = characterFromID("CapComission_1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.CaptainComission.City + "_prison", "goto", "goto9");
			LAi_group_MoveCharacter(sld, "Prisoner_Group");
			LAi_SetCitizenType(sld);
		break;

		case "CaptainComission_PrisonFree_Death":
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			AddQuestRecord("CaptainComission2", "22");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;

		case "CaptainComission_DeletePrisonGroup":
			LAi_group_Delete("CapComission_Prison");
		break;

		case "CaptainComission_ExitFromPrison":
			iTemp = GetCharacterIndex("CapComission_1");
			if (iTemp != -1)
			{
				pchar.quest.CaptainComission_ExitFromTown.win_condition.l1 	= "EnterToSea";
				pchar.quest.CaptainComission_ExitFromTown.function    		= "CaptainComission_ExitFromTown";
				pchar.GenQuest.CaptainComission.canSpeakCaptain = true;
				pchar.TownEscape = true;
			}
		break;

		case "CaptainComission_MeetWithCaptain":
			Sea_DeckBoatStartNow(pchar);
		break;

		case "CaptainComission_MapEnterCapDied":
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;

		case "CaptainComission_ShoreGangDialog":
			SetMainCharacterIndex(1);
			pchar = GetMainCharacter();
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar)
			locCameraFollow();
			EndQuestMovie();
			ChangeShowIntarface();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			DoQuestFunctionDelay("CaptainComission_BattleInShore", 8.0);
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец   Генератор - Поручение капитана "Операция 'Галеон'"
		////////////////////////////////////////////////////////////////////////

  		////////////////////////////////////////////////////////////////////////
		//  Начало    Грабители в городах
		////////////////////////////////////////////////////////////////////////
		case "Berglars_Ostin":
			chrDisableReloadToLocation = true;
			if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations)sld = GetCharacter(NPC_GenerateCharacter("Ostin", "Ostin", "man", "man_fast", 30, SPAIN, -1, false)); //LEO: Превозмогаторам страдать 08.12.2021
			else sld = GetCharacter(NPC_GenerateCharacter("Ostin", "Ostin", "man", "man", 30, SPAIN, -1, false));
			FantomMakeCoolFighter(sld, 30, 100, 70, "blade32", "pistol5", 50);
			sld.name 	= GetConvertStr("Variable_quests_reaction_0.1", "Names.txt");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_3", "Names.txt", "#space#", " ");
			sld.rank = 30;
			sld.dialog.filename   = "Quest\Berglars.c";
			sld.dialog.currentnode = "Final_fight";
			sld.greeting = "Gr_OliverTrast";
			if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
			sld.money = 30670;
			sld.SaveItemsForDead  = true;
			sld.DontClearDead = true;
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Sliding");
			TakeNItems(sld, "jewelry1", 20+rand(5));
			TakeNItems(sld, "jewelry2", 14+rand(5));
			TakeNItems(sld, "jewelry3", 18+rand(5));
			TakeNItems(sld, "jewelry4", 16+rand(5));
			//Скорпион
			TakeNItems(sld, "talisman8", 1);
			GiveItem2Character(sld, "icollection");
			GiveItem2Character(sld, "spyglass4");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
  		////////////////////////////////////////////////////////////////////////
		//  Конец    Грабители в городах
		////////////////////////////////////////////////////////////////////////

   		////////////////////////////////////////////////////////////////////////
		//  Начало   Бордель
		////////////////////////////////////////////////////////////////////////
        case "Brothel_checkVisitTime":
			LocatorReloadEnterDisable(qname + "_Brothel", "reload2_back", true); //закрываем комнату
			sld = characterFromId(pchar.quest.(qname).HorseId);
			sld.location = qname+"_Brothel";
			sld.location.group = "goto";
			sld.location.locator = pchar.quest.(qname).locator;
			//ChangeCharacterAddressGroup(sld, qname+"_Brothel", "goto", pchar.quest.(qname).locator);
			DeleteAttribute(&characters[GetCharacterIndex(qname + "_Hostess")], "quest.selected"); //снимаем флаг у хозяйки
			//==> ноду девкам
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				makeref(sld, Characters[i]);
				if (sld.location == qname+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
				{
					sld.dialog.currentnode = "Horse_talk";
				}
			}
        break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Бордель
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    Грабеж жемчужного промысла
		////////////////////////////////////////////////////////////////////////
        //--------------------- промысел через залив Сан-Хуан дель Норте и подземелье -----------------------
		case "PearlGen_checkSantaCatalina":
			if (locations[reload_cur_location_index].id == "Pearl_CaveEntrance")
			{
				if (!CheckAttribute(&locations[reload_location_index], "PearlSantaCatalina") || GetNpcQuestPastDayParam(&locations[reload_location_index], "PearlSantaCatalina") > 30)
				{
					LAi_group_Delete("PearlGroup_2");
					iTemp = sti(colonies[FindColony("SantaCatalina")].nation); //принадлежность промысла нации, от Санта-Каталины
					SaveCurrentNpcQuestDateParam(&locations[reload_location_index], "PearlSantaCatalina");
					sld = GetCharacter(NPC_GenerateCharacter("PearlGuardMan_2", "pirate_"+(rand(9)+1), "man", "man", 10, iTemp, 31, true));
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto"+RandFromThreeDight(3, 4, 8));
					sld.city = "SantaCatalina"; //НЗГ Санта-Каталины
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "PearlGroup_2");
					locations[FindLocation("Pearl_town_2")].pearlVillage = true; //флаг генерить жемчужников
					bOk = true;	//мир
					if (GetRelation2BaseNation(iTemp) != RELATION_FRIEND)
					{
						if (GetDaysContinueNationLicence(iTemp) == -1)
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_23", "Logs.txt", "#space#", " "));
								LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
								bOk = false; //война
							}
							else
							{
								AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
							}
						}
					}
					if (bOk)
					{
						chrDisableReloadToLocation = true;
						sld.dialog.Filename = "Pearl_dialog.c";
						sld.dialog.currentnode = "GuardMan";
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else //обратный путь
			{
				if (locations[reload_cur_location_index].id == "Pearl_town_2" && GetCharacterIndex("HeadMan_2") == -1)
				{
					iTemp = 0;
					for(i=0; i<MAX_CHARACTERS; i++)
					{
						if (characters[i].location == "Pearl_town_2")
						{
							characters[i].location = "none";
							iTemp++;
						}
					}
					if (iTemp > 0) //остатки жемчуга скоммуниздили оставшиеся в живых жемчужники
					{
						DeleteAttribute(&locations[FindLocation("PearlTown2_Townhall")], "box1");
						DeleteAttribute(&locations[FindLocation("PearlTown2_Townhall")], "box2");
					}
				}
			}
			pchar.quest.PearlGen_SetNewInterrapt_2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.PearlGen_SetNewInterrapt_2.win_condition.l1.location = "Pearl_Jungle_06";
			pchar.quest.PearlGen_SetNewInterrapt_2.function = "PearlGen_SetSantaCatalina";
		break;

		//----------------------------------- промысел через Теночтитлан --------------------------------------
        case "PearlGen_checkTeno":
			if (locations[reload_cur_location_index].id == "Pearl_Jungle_03")
			{
				if (!CheckAttribute(&locations[reload_location_index], "PearlTeno") || GetNpcQuestPastDayParam(&locations[reload_location_index], "PearlTeno") > 30)
				{
					LAi_group_Delete("PearlGroup_1");
					iTemp = sti(colonies[FindColony("SantaCatalina")].nation); //принадлежность промысла нации, от Санта-Каталины
					SaveCurrentNpcQuestDateParam(&locations[reload_location_index], "PearlTeno");
					sld = GetCharacter(NPC_GenerateCharacter("PearlGuardMan_1", "pirate_"+(rand(9)+1), "man", "man", 10, iTemp, 31, true));
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto"+RandFromThreeDight(1, 9, 8));
					sld.city = "SantaCatalina"; //испанские НЗГ
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "PearlGroup_1");
					locations[FindLocation("Pearl_town_1")].pearlVillage = true; //флаг генерить жемчужников
					bOk = true;	//мир
					if (GetRelation2BaseNation(iTemp) != RELATION_FRIEND)
					{
						if (GetDaysContinueNationLicence(iTemp) == -1)
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_24", "Logs.txt", "#space#", " "));
								LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", -1);
								bOk = false; //война
							}
							else
							{
								AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
							}
						}
					}
					if (bOk)
					{
						chrDisableReloadToLocation = true;
						sld.dialog.Filename = "Pearl_dialog.c";
						sld.dialog.currentnode = "GuardMan";
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else //обратный путь
			{
				if (locations[reload_cur_location_index].id == "Pearl_town_1" && GetCharacterIndex("HeadMan_1") == -1)
				{
					iTemp = 0;
					for(i=0; i<MAX_CHARACTERS; i++)
					{
						if (characters[i].location == "Pearl_town_1")
						{
							characters[i].location = "none";
							iTemp++;
						}
					}
					if (iTemp > 0) //остатки жемчуга скоммуниздили оставшиеся в живых жемчужники
					{
						DeleteAttribute(&locations[FindLocation("PearlTown1_Townhall")], "box1");
						DeleteAttribute(&locations[FindLocation("PearlTown1_Townhall")], "box2");
					}
				}
			}
			pchar.quest.PearlGen_SetNewInterrapt_1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.PearlGen_SetNewInterrapt_1.win_condition.l1.location = "Pearl_Jungle_02";
			pchar.quest.PearlGen_SetNewInterrapt_1.function = "PearlGen_SetTeno";
        break;

        case "PearlToShore_ForSale":
			chrDisableReloadToLocation = false;
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.quest.PearlToShore_ForSale.idx)]);
        break;

        case "Pearl_GuardManIsLife":
			sld = &characters[sti(pchar.quest.Pearl_GuardManIsLife.idx)];
			sld.dialog.Filename = "Pearl_dialog.c";
 			sld.dialog.currentnode = "GuardManAllarm";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto10");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.5, 0);
        break;

		////////////////////////////////////////////////////////////////////////
		//  Конец    Грабеж жемчужного промысла
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало Тюремные квесты
		////////////////////////////////////////////////////////////////////////
        case "GivePrisonFree":
			chrDisableReloadToLocation = true;
			LAi_LocationDisableMonstersGen(pchar.location, true);
			pchar.quest.GivePrisonFree_Death.over = "yes";
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			sld.dialog.currentnode = "PrisonerInPlace";
			LAi_SetActorTypeNoGroup(sld);
			GetCharacterPos(sld, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

        case "GivePrisonFree_Death":
			AddQuestRecord("GivePrisonFree", "2");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			pchar.quest.GivePrisonFree.over = "yes";
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup"
		break;

        case "GivePrisonFree_Over":
			AddQuestRecord("GivePrisonFree", "6");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.prisonerId);
			if (iTemp > 0)
			{
				characters[iTemp].lifeDay = 0;
				ChangeCharacterAddress(&characters[iTemp], "none", "");
			}
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup"
		break;

        case "DeliverToBander":
			if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.City") && pchar.questTemp.jailCanMove.Deliver.City == locations[reload_location_index].fastreload)
			{
				LAi_group_Delete("EnemyFight");
				chrDisableReloadToLocation = true;
				pchar.quest.DeliverToBander.over = "yes";
				pchar.quest.DeliverToBander_over.over = "yes";
				//--> генерим ранг
				if (sti(pchar.rank) > 6)
				{
					Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE*3;
				}
				else
				{	//казуалам зеленый свет на начало игры
					if (sti(pchar.rank) > 3) Rank = sti(pchar.rank);
					else
					{
						Rank = 1;
					}
				}
				//<-- генерим ранг
				GetCharacterPos(pchar, &locx, &locy, &locz);
				for (i=1; i<=2; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Bander_"+i, "pirate_"+(rand(9)+1), "man", "man", Rank, PIRATE, 0, true));
					sld.dialog.filename = "quest\Banders_dialog.c";
					sld.dialog.currentnode = "First time";
					sld.greeting = "cit_common";
					SetFantomParamFromRank(sld, Rank, true);
					if (i == 1)
					{
						LAi_SetOwnerType(sld);
						sld.dialog.currentnode = "Second time";
         				ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
					}
					else
					{
						LAi_SetActorType(sld);
						sld.dialog.currentnode = "First time";
         				ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
					}
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_ActorDialog(sld, pchar, "", 1.0, 0);
			}
		break;

        case "DeliverToBander_over":
			AddQuestRecord("GivePrisonFree", "9");
			CloseQuestHeader("GivePrisonFree");
			pchar.quest.DeliverToBander.over = "yes";
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
			if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			TakeItemFromCharacter(pchar, "Malyava");
		break;

        case "DeliverToBander_Dead":
			AddQuestRecord("GivePrisonFree", "10");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			CloseQuestHeader("GivePrisonFree");

			AchievementsCounter_genquests(1);

            chrDisableReloadToLocation = false;
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
			if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			TakeItemFromCharacter(pchar, "Malyava");
		break;

        case "DeletePrisonGroup":
			LAi_group_Delete("DeliveQuest_Prison");
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец  Тюремные квесты
		////////////////////////////////////////////////////////////////////////

		// универсальный диалогостартер (см метод  SetActorDialogAny2Pchar)
        case "ActorDialog_Any2Pchar":
            LAi_SetActorType(PChar);
            LAi_ActorWaitDialog(Pchar, characterFromID(Pchar.AutoQuest.NPCharId));
            LAi_ActorDialog(characterFromID(Pchar.AutoQuest.NPCharId), Pchar, Pchar.AutoQuest.Quest, stf(Pchar.AutoQuest.Time1), stf(Pchar.AutoQuest.Time2));
        break;

        case "OpenTheDoors":
            chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			//#20190804-01
			if(CheckAttribute(pchar, "tmpKillGroup")) {
                LAi_group_SetAlarm(pchar.tmpKillGroup, LAI_GROUP_PLAYER, 0.0);
                DeleteAttribute(pchar, "tmpKillGroup");
            }
        break;

		case "OpenTheDoors_Greedy":
            chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_group_SetRelation("greedybastard", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
        break;

		case "OpenTheDoors_Priest":
            chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			StartActorSelfDialog("PriestSurprise");
        break;

		//Довакин
		case "Dovahkiin":
            // PlaySound("Interface\P_Dovahkiin.wav");
			LAi_CharacterPlaySound(pchar, "P_Dovahkiin");
			Log_TestInfo(GetConvertStrWithReplace("Variable_quests_reaction_25", "Logs.txt", "#space#", " "));
			pchar.Dovahkiin = 1;
        break;
		case "PGGLeft":
			Log_TestInfo(GetConvertStrWithReplace("Variable_quests_reaction_26", "Logs.txt", "#space#", " "));
			sld = CharacterFromID(pchar.chosenHero);
			DeleteAttribute(pchar, "chosenHero");
			string futureLoc = "none";
			ChangeCharacterAddress(sld, futureLoc, "");
			LAi_SetImmortal(sld, false);
			if (CheckAttribute(sld, "PGGOfficers"))
			{
				for (i = 0; i < sti(sld.PGGOfficers); i++)
				{
					chr = CharacterFromID("PGGOfficer" + i);
					ChangeCharacterAddress(chr, futureLoc, "");
				}
				DeleteAttribute(sld, "PGGOfficers");
			}
        break;

        case "CanEnterToMap":
            bQuestDisableMapEnter = false;
        break;

        case "CloseBermudesDungeonDoor":
            LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			sld = characterFromId("Pirates_shipyarder");
			DeleteAttribute(sld, "Step_Door");
        break;

        case "CanFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
        break;

        case "CannotFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, true);
			chrDisableReloadToLocation = false;
        break;
        //#20190527-01
        case "CannotFightCurLocationAStop":
			LAi_LocationFightDisable(loadedLocation, true);
			chrDisableReloadToLocation = false;
			LAi_group_SetAlarm(LAI_GROUP_PLAYER, "EnemyFight", 0.0);
        break;

        case "MainHeroFightModeOn":
			LAi_SetFightMode(pchar, true);
        break;

        case "MainHeroFightModeOff":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
        break;

		case "ChurchNightGuard_timerInChurch_2":
			TavernWaitDate("wait_day");
		break;

		case "MayorSitBack": //посадить мэра обратно
			iTemp = GetCharacterIndex(Pchar.quest.MayorSitBack.mayorId)
			if (iTemp > 0)
			{
				sld = &characters[iTemp];
				sld.location = Pchar.quest.MayorSitBack.locationName;
				sld.location.group = "sit";
				sld.location.locator = Pchar.quest.MayorSitBack.locatorName;
				LAi_SetHuberTypeNoGroup(sld);
				RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
				RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			}
        break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  START Английская линейка
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//==========================   Квест N1, Сопровождение герцога Альбермаля ========================

        case "fight_withSpanish_Albermal":                      //  Атака испанца на наш корабль с Альбермалем
            bQuestDisableMapEnter = true;
            Island_SetReloadEnableGlobal("Antigua", false);

            sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_2", "man", "man", 15, SPAIN, 0, true));
            FantomMakeCoolSailor(sld, SHIP_DIANA, "", CANNON_TYPE_CULVERINE_LBS24, 90, 90, 90);
            FantomMakeCoolFighter(sld, 20, 90, 50, "blade25", "pistol3", 80);
            sld.DontRansackCaptain = true; //квестовые не сдаются
            sld.SinkTenPercent = true; //уходим с повреждениями

			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Antigua", "", "");
			Group_LockTask("Spa_Attack");

			pchar.quest.after_fight_withSpanish_Albermal.win_condition.l1 = "NPC_Death";
			pchar.quest.after_fight_withSpanish_Albermal.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.after_fight_withSpanish_Albermal.win_condition = "after_fight_withSpanish_Albermal";
        break;

        case "after_fight_withSpanish_Albermal":                  // Испанский флейт на дне или захвачен
            bQuestDisableMapEnter = false;
            Island_SetReloadEnableGlobal("Antigua", true);
			pchar.quest.goto_Oxbay_Albermal.win_condition.l1 = "location";
			pchar.quest.goto_Oxbay_Albermal.win_condition.l1.location = "SentJons_townhall";
			pchar.quest.goto_Oxbay_Albermal.win_condition = "goto_SentJons_Albermal";
            AddQuestRecord("Eng_Line_1_Albermal", "3");
            group_DeleteGroup("Spa_Attack");
        break;

        case "goto_SentJons_Albermal":
            sld = characterFromID("Albermal");                    //  Альбермаль в резиденции губернатора
            ChangeCharacterAddressGroup(sld, "SentJons_townhall", "goto", "goto5");
			sld.dialog.currentnode = "in_the_SentJons";
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar("Albermal", "", 0.0, 1.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
        break;

//==========================   Квест N3, Нападение на Белиз ========================
        case "time_over_Beliz_attack":
            // 50 дней на взятие Белиза, включая и походы за двумя пиратами, если геймер решит, что это ему нужно
            if (IsEntity(worldMap))
            {
                if (!bQuestCheckProcessFreeze) // можно показать
				{
	        		pchar.quest.time_over_Beliz_attack_Map_01.over = "yes"; // сброс, если уже откладывали
	        		pchar.quest.time_over_Beliz_attack_Map_02.over = "yes";

                    makearef(arOldMapPos, worldMap.old);
                    WdmPrepareMapForAbordage(arOldMapPos);
                    MakeCloneShipDeck(pchar, true); // подмена палубы
                    DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
	                ReloadFromWMtoL_complete();

                    sld = characterFromID("Henry Morgan");
                    ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
                    LAi_SetWarriorType(sld);
	                LAi_warrior_DialogEnable(sld, true);
	                sld.dialog.currentnode = "time_over_Beliz";
   	                // ==> антураж
                    for (i=1; i<5; i++)
        			{
                        attrName = "pirate_" + i;
                        sld = GetCharacter(NPC_GenerateCharacter(attrName, attrName, "man", "man", 15, PIRATE, 1, true));
                        sld.dialog.Filename = "Quest\sailors_dialog.c";
	                    sld.dialog.currentnode = "Morgan_wait_you";
                    	LAi_SetWarriorType(sld);
                    	LAi_warrior_DialogEnable(sld, true);
                    	LAi_SetLoginTime(sld, 0.0, 24.0);
                    	LAi_SetHP(sld, 100.0, 100.0);
                    	ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto"+i);
                    }
                	pchar.quest.Munity = "";  // признак выхода с палубы (закрыто, а то можно не говорить)
            		LAi_LockFightMode(pchar, true);
				}
				else
				{   // отложим до разморозки (пролет табличек)
      				Pchar.quest.time_over_Beliz_attack_Map_01.win_condition.l1 = "MapEnter";
                    Pchar.quest.time_over_Beliz_attack_Map_01.win_condition = "time_over_Beliz_attack";
		        }
			}
			else
			{   // подождем выхода на карту, раз время прошло, но мы не на ней
			    Pchar.quest.time_over_Beliz_attack_Map_02.win_condition.l1 = "MapEnter";
                Pchar.quest.time_over_Beliz_attack_Map_02.win_condition = "time_over_Beliz_attack";
			}
        break;

//==========================   Квест N4, Разведмиссия в Кюрасао ========================
        case "Intelligence_Curacao_GoToShore":    //  Встреча с бригом близ Кюрасао.
            if (pchar.questTemp.State == "Intelligence_Curacao_FightGard" || pchar.questTemp.State == "Intelligence_Curacao_OutPrison")
            {
                LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_Bank")], true); // вертаем запрет на боевки
                sld = characterFromID("Villemstad_usurer");
                ChangeCharacterAddressGroup(sld, "Villemstad_Bank", "goto", "goto1");
	            LAi_SetOwnerType(sld);
                LAi_SetHP(sld, 80, 80); //вертаем ростовщика если убит
                pchar.quest.Intelligence_Curacao_OutTown.over = "yes";
            }
            else    //==> боевка с голландским бригом
            {
                bQuestDisableMapEnter = true;
                Island_SetReloadEnableGlobal("Curacao", false);

				pchar.questTemp.abordage = 0; // запрещаем абордаж повторно - это сброс запрета

                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_hol_2", "man", "man", 23, HOLLAND, 0, true));
                FantomMakeCoolSailor(sld, SHIP_NAVY, "", CANNON_TYPE_CANNON_LBS16, 95, 95, 95);
                FantomMakeCoolFighter(sld, 25, 90, 50, BLADE_LONG, "pistol3", 100);
                sld.DontRansackCaptain = true; //квестовые не сдаются
                sld.SinkTenPercent = true; // уходим с повреждениями
				sld.Ship.name = GetConvertStrWithReplace("Variable_quests_reaction_4", "Names.txt", "#space#", " ");

    			Group_FindOrCreateGroup("Hol_Attack");
    			Group_SetType("Hol_Attack", "war");
    			Group_AddCharacter("Hol_Attack", "CaptainAttack_1");
    			Group_SetGroupCommander("Hol_Attack", "CaptainAttack_1");
			    Group_SetAddress("Hol_Attack", "Curacao", "", "");
				Group_SetPursuitGroup("Hol_Attack", PLAYER_GROUP);
                Group_SetTaskAttack("Hol_Attack", PLAYER_GROUP);
				Group_LockTask("Hol_Attack");
    			//==> признак нахождения письма в каюте кэпа
    			pchar.questTemp.EngLineQ4_PutLetter = 1;

    			pchar.quest.Intelligence_Curacao_Boarding.win_condition.l1 = "Character_Capture";
    			pchar.quest.Intelligence_Curacao_Boarding.win_condition.l1.character = "CaptainAttack_1";
    			pchar.quest.Intelligence_Curacao_Boarding.win_condition = "Intelligence_Curacao_Boarding";

    			pchar.quest.Intelligence_Curacao_Sink.win_condition.l1 = "Character_sink";
    			pchar.quest.Intelligence_Curacao_Sink.win_condition.l1.character = "CaptainAttack_1";
    			pchar.quest.Intelligence_Curacao_Sink.win_condition = "Intelligence_Curacao_Sink";
            }
        break;

        case "Intelligence_Curacao_Sink":   // Голландский бриг потоплен
            bQuestDisableMapEnter = false;
            Island_SetReloadEnableGlobal("Curacao", true);
            pchar.questTemp.State = "Intelligence_Curacao_Sink";
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "8");
            group_DeleteGroup("Hol_Attack");
            DeleteAttribute(PChar, "questTemp.EngLineQ4_PutLetter");
            BackItemDescribe("letter_1");
            pchar.quest.Intelligence_Curacao_Boarding.over = "yes";
        break;

        case "Intelligence_Curacao_Boarding":   // Голландский брин захвачен
            pchar.quest.Intelligence_Curacao_Sink.over = "yes";
			if (CheckCharacterItem(pchar, "letter_1"))
            {
                AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "9");
				AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex1", GetSexPhrase("ел","ла"));
                pchar.questTemp.State = "Intelligence_Curacao_Boarding";
                TakeItemFromCharacter(pchar, "letter_1");
                ChangeItemDescribe("letter_open", "itmdescr_letter_open_EngLineQ4");
                GiveItem2Character(pchar, "letter_open");
            }
            else
            {
                AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "11");
                pchar.questTemp.State = "Intelligence_Curacao_BoardingNotFoundLetter";
            }

            bQuestDisableMapEnter = false;
            Island_SetReloadEnableGlobal("Curacao", true);
            pchar.quest.Intelligence_Curacao_Sink.over = "yes";
            group_DeleteGroup("Hol_Attack");
            DeleteAttribute(PChar, "questTemp.EngLineQ4_PutLetter");
            BackItemDescribe("letter_1");
        break;

		case "Intelligence_Curacao_KickYozef":  // ГГ отпинали в доме у ростовщика.
            LAi_SetFightMode(pchar, false);
            DoReloadCharacterToLocation("Villemstad_prison",  "goto", "goto9");
			LAi_SetImmortal(pchar, false);
            // ==> Забираем клинки, пистоли и деньги.
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
            while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
            {
                TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));
            }
            while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
            {
                TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
            }
            pchar.money = 0;
            // <== Забираем клинки, пистоли и деньги.
			TakeNationLicence(HOLLAND);
            DoQuestCheckDelay("Intelligence_Curacao_GoPrisonMan", 10);
            sld = GetCharacter(NPC_GenerateCharacter("Hoverd_Tantum", "citiz_11", "man", "man", 15, ENGLAND, 3, false));
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.2", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_5", "Names.txt", "#space#", " ");
            LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto13");
        break;

        case "Intelligence_Curacao_GoPrisonMan":
            sld = characterFromID("Hoverd_Tantum");
            LAi_SetActorType(sld);
            LAi_ActorGoToLocator(sld, "goto", "goto23", "Intelligence_Curacao_TalkingPrisonMan", -1);
        break;

        case "Intelligence_Curacao_TalkingPrisonMan":
            sld = characterFromID("Hoverd_Tantum");
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
        break;

//==========================   Квест N5, Нападение на Форт Оранж ========================
		case "AttackFortOrange_GoToFort":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_27", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
	        Ship_NationAgressive(chr, chr);
			pchar.HalfOfPaymentByCity = true;
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (i=1; i<=15; i++)
            {
                if (i == 3 || i == 7 || i == 11)
                {
                    Model = "off_hol_" + (rand(1)+1);
                    Blade = "blade24";
                    Rank = 25;
                    Gun = "pistol4";
                }
                else
                {
                    Model = "sold_hol_" + (rand(7)+1);
                    Rank = 20;
                    Blade = BLADE_LONG;
                    Gun = "pistol3";
                }
                sld = GetCharacter(NPC_GenerateCharacter("Solder"+i, Model, "man", "man", 25, HOLLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 70, 60, Blade, Gun, 70);
				LAi_LoginInCaptureTown(sld, true);

            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "TOWN_BATTLE_SOLDIERS");
               	ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
            }
			TWN_Capture_Forts();
            for (i=1; i<=8; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("pirate_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 25, ENGLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 60, 50, Blade, Gun, 40);
				LAi_LoginInCaptureTown(sld, true);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				//sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
				//if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
                ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
            }
            Pchar.quest.AttackOrange_FightInTown.win_condition.l1 = "location";
            Pchar.quest.AttackOrange_FightInTown.win_condition.l1.location = "FortOrange_town";
            Pchar.quest.AttackOrange_FightInTown.win_condition = "AttackOrange_FightInTown";
    	    /*Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
    	    DeleteQuestAttribute("Union_with_Escadra");
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            SetLocationCapturedState(sld.city + "_town", true);
            DoQuestCheckDelay("Capture_Forts", 0.5);
            Ship_NationAgressive(sld, sld);*/
            Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_28", "Logs.txt", "#space#", " "));
            // установка отмены боевки в резиденции при захвате города
            //string _city, string _method, bool _majorOff

            Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition.l1 = "location";
            Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition.l1.location = "FortOrange_townhall";
			Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition = "AttackFortOrange_FightWithCommendant";
        break;
		
		case "AttackFortOrange_GoToPort":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_29", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
	        Ship_NationAgressive(chr, chr);
			pchar.HalfOfPaymentByCity = true;
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (i=1; i<=15; i++)
            {
                if (i == 3 || i == 7 || i == 11)
                {
                    Model = "off_hol_" + (rand(1)+1);
                    Blade = "blade24";
                    Rank = 25;
                    Gun = "pistol4";
                }
                else
                {
                    Model = "sold_hol_" + (rand(7)+1);
                    Rank = 20;
                    Blade = BLADE_LONG;
                    Gun = "pistol3";
                }
                sld = GetCharacter(NPC_GenerateCharacter("Solder"+i, Model, "man", "man", 25, HOLLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 70, 60, Blade, Gun, 70);
				LAi_LoginInCaptureTown(sld, true);

            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "TOWN_BATTLE_SOLDIERS");
               	ChangeCharacterAddressGroup(sld, "FortOrange_port", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
            }
			TWN_Capture_Forts();
            for (i=1; i<=8; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("pirate_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 25, ENGLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 60, 50, Blade, Gun, 40);
				LAi_LoginInCaptureTown(sld, true);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
				if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
                ChangeCharacterAddressGroup(sld, "FortOrange_port", "goto", sTemp);
            }
            Pchar.quest.AttackOrange_FightInTown.win_condition.l1 = "location";
            Pchar.quest.AttackOrange_FightInTown.win_condition.l1.location = "FortOrange_town";
            Pchar.quest.AttackOrange_FightInTown.win_condition = "AttackOrange_FightInTown";
    	    /*Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
    	    DeleteQuestAttribute("Union_with_Escadra");
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            SetLocationCapturedState(sld.city + "_town", true);
            DoQuestCheckDelay("Capture_Forts", 0.5);
            Ship_NationAgressive(sld, sld);*/
            Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_30", "Logs.txt", "#space#", " "));
            // установка отмены боевки в резиденции при захвате города
            //string _city, string _method, bool _majorOff

            Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition.l1 = "location";
            Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition.l1.location = "FortOrange_townhall";
			Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition = "AttackFortOrange_FightWithCommendant";
        break;
		
		case "AttackOrange_FightInTown":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_31", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (i=1; i<=18; i++)
            {
                if (i == 3 || i == 7 || i == 11 || i == 17)
                {
                    Model = "off_hol_" + (rand(1)+1);
                    Blade = "blade24";
                    Rank = 25;
                    Gun = "pistol4";
                }
                else
                {
                    Model = "sold_hol_" + (rand(7)+1);
                    Rank = 20;
                    Blade = BLADE_LONG;
                    Gun = "pistol3";
                }
                sld = GetCharacter(NPC_GenerateCharacter("Solder"+i, Model, "man", "man", 25, HOLLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 100, 70, Blade, Gun, 70);
				LAi_LoginInCaptureTown(sld, true);

            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "TOWN_BATTLE_SOLDIERS");
               	ChangeCharacterAddressGroup(sld, "FortOrange_town", "rld", LAi_FindFarLocator("rld", locx, locy, locz));
            }
            for (i=1; i<=15; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("pirate_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 25, ENGLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 60, 50, Blade, Gun, 40);
				LAi_LoginInCaptureTown(sld, true);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
                ChangeCharacterAddressGroup(sld, "FortOrange_town", "rld",  LAi_FindNearestLocator("rld", locx, locy, locz));
            }
            LAi_group_SetCheck("TOWN_BATTLE_SOLDIERS", "AttackOrange_FightInTown_WeWon");
        break;
		
		case "AttackOrange_FightInTown_WeWon":
            chrDisableReloadToLocation = false; // открыть выход из локации.
			PChar.quest.AttackFortOrange_GoToFort.over = "yes";
			PChar.quest.AttackFortOrange_GoToPort.over = "yes";
        break;

        case "AttackFortOrange_FightWithCommendant":
            chrDisableReloadToLocation = true; // закрыть выход из локации
            bDisableFastReload = true; // закрыть переходы.
			//--> огонь и пламень
			locations[FindLocation("FortOrange_town")].hidden_effects = true;
			locations[FindLocation("FortOrange_ExitTown")].hidden_effects = true;
			//<-- огонь и пламень

            sld = GetCharacter(NPC_GenerateCharacter("Orange_Comendant", "off_hol_2", "man", "man", 25, HOLLAND, 0, true));
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
        	LAi_SetWarriorType(sld);
            LAi_warrior_DialogEnable(sld, true);
            sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
            sld.cirassId           = Items_FindItemIdx("cirass5"); //1.2.3
            LAi_LoginInCaptureTown(sld, true);
            FantomMakeCoolFighter(sld, 38, 90, 70, BLADE_LONG, "pistol3", 30);
           	ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto8");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.2);
        break;

        case "AttackFortOrange_AfterFightWithCommendant":
            pchar.questTemp.State = "AttackFortOrange_WeWin";
            AddQuestRecord("Eng_Line_5_AttackFortOrange", "2");
        break;

//==========================   Квест N6, Моррис Уильямс ========================
        case "MorrisWillams_ShipToPort":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_32", "Logs.txt", "#space#", " "));
            sld = GetCharacter(NPC_GenerateCharacter("Morris_Willams", "MorrisWillams", "man", "man", 25, ENGLAND, -1, true));
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.3", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_6", "Names.txt", "#space#", " ");
        	sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			sld.greeting = "Gr_MiddPirate";
            LAi_SetStayTypeNoGroup(sld);
            FantomMakeCoolSailor(sld, SHIP_ESSEX, GetConvertStr("Variable_quests_reaction_1", "ShipNames.txt"), CANNON_TYPE_CULVERINE_LBS24, 90, 90, 90);
            FantomMakeCoolFighter(sld, 28, 70, 40, BLADE_LONG, "pistol4", 100);
            sld.Ship.Stopped = true;
            sld.DeckDialogNode = "First time";
			sld.Ship.Mode = "Pirate";

			Group_FindOrCreateGroup("Willams_Group");
			Group_AddCharacter("Willams_Group", "Morris_Willams");
			Group_SetGroupCommander("Willams_Group", "Morris_Willams");
            Group_SetAddress("Willams_Group", "Jamaica", "quest_ships", "quest_ship_1");

			pchar.quest.MorrisWillams_WillamsAttack.win_condition.l1 = "NPC_Death";
			pchar.quest.MorrisWillams_WillamsAttack.win_condition.l1.character = "Morris_Willams";
			pchar.quest.MorrisWillams_WillamsAttack.win_condition = "MorrisWillams_WillamsAttack";
        break;

        case "MorrisWillams_WillamsAttack":
            sld = characterFromID("Morris_Willams");
    	    sld.LifeDay = 1; // уберем нпс на след.день.
    	    SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
            pchar.questTemp.State = "QuestLineBreake";
            ChangeCharacterReputation(pchar, -20);
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
        break;

        case "MorrisWillams_MeetWithManFromWillams":
			chrDisableReloadToLocation = true;
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_33", "Logs.txt", "#space#", " "));
            pchar.quest.MorrisWillams_WillamsAttack.over = "yes"; // снимаем прерывание на завершение линейки

            sld = GetCharacter(NPC_GenerateCharacter("Bocman_Willams", "officer_15", "man", "man", 25, ENGLAND, -1, true));
            sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.4", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_7", "Names.txt", "#space#", " ");
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "MorrisWillams_InTavernWithWillams":
            sld = characterFromID("Morris_Willams");
            FreeSitLocator("PortRoyal_tavern", "sit11");
			LAi_SetSitTypeNoGroup(sld);
         	ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit11");
            LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true); //на всякий случай, чтобы геймер не слинял.
            LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
        break;

        case "MorrisWillams_CheckTimeForForward":
            if (GetQuestPastTimeParam("questTemp") < 2)
            {
                Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_34", "Logs.txt", "#space#", " "));
                Pchar.quest.MW_AttackPinnace.win_condition.l1 = "location";
                Pchar.quest.MW_AttackPinnace.win_condition.l1.location = "PuertoRico";
                Pchar.quest.MW_AttackPinnace.win_condition = "MW_AttackPinnace";
                SetTimerCondition("MorrisWillams_PinaceTimeOver", 0, 0, 16, false);
            }
            else
            {
                Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_35", "Logs.txt", "#space#", " "));
                pchar.questTemp.State = "MorrisWillams_PinnaceNotFound";
                characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "First time";
            }
        break;

        case "MorrisWillams_PinaceTimeOver":
            pchar.quest.MW_AttackPinnace.over = "yes";
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_36", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "MorrisWillams_PinnaceNotFound";
            characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "First time";
        break;

        case "MW_AttackPinnace":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_37", "Logs.txt", "#space#", " "));
            Island_SetReloadEnableGlobal("PuertoRico", false);
            characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "First time";

            sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_1", "man", "man", 28, SPAIN, 0, true));
            sld.SinkTenPercent = true; // уходим с повреждениями
            sld.DontRansackCaptain = true; //квестовые не сдаются

            FantomMakeCoolSailor(sld, SHIP_PINNACE, GetConvertStr("Variable_quests_reaction_2", "ShipNames.txt"), CANNON_TYPE_CANNON_LBS32, 95, 90, 90);
            FantomMakeCoolFighter(sld, 28, 90, 70, BLADE_LONG, "pistol3", 100);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "trade");
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
            Group_SetAddress("Spa_Attack", "PuertoRico", "", "");
            Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
//            Group_SetTaskMove("Spa_Attack", 1930.0, -315.0);
            Group_LockTask("Spa_Attack");

            //==> признак нахождения письма в комоде
            pchar.questTemp.EngLineQ6_PutMoney = 1;
            pchar.questTemp.QtyMoneyTillBoarding = pchar.money;  // запомнить кол-во денег до абордажа, нужно для определения взял ли ГГ бабки из сундука в каюте

			pchar.quest.MorrisWillams_PinnaceBoarding.win_condition.l1 = "Character_Capture";
			pchar.quest.MorrisWillams_PinnaceBoarding.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.MorrisWillams_PinnaceBoarding.win_condition = "MorrisWillams_PinnaceBoarding";

			pchar.quest.MorrisWillams_PinnaceSink.win_condition.l1 = "Character_sink";
			pchar.quest.MorrisWillams_PinnaceSink.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.MorrisWillams_PinnaceSink.win_condition = "MorrisWillams_PinnaceSink";

			pchar.quest.MorrisWillams_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.MorrisWillams_DieHard.win_condition = "MorrisWillams_DieHard";
            pchar.quest.MorrisWillams_PinaceTimeOver.over = "yes";  // снимаем таймер на прибытие пинаса к острову
        break;


        case "MorrisWillams_PinnaceBoarding":
			iTemp = sti(pchar.money) - sti(pchar.questTemp.QtyMoneyTillBoarding);
            if (iTemp >= 140000)
            {
                Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_38", "Logs.txt", "#space#", " "));
                AddQuestRecord("Eng_Line_6_MorrisWillams", "10");
				AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex1", GetSexPhrase("ел","ла"));
                pchar.questTemp.State = "MorrisWillams_PinnaceBoard";
            }
            else
            {
                Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_39", "Logs.txt", "#space#", " "));
                AddQuestRecord("Eng_Line_6_MorrisWillams", "23");
                pchar.questTemp.State = "MorrisWillams_PinnaceBoardNotFoundMoney";
            }
            Island_SetReloadEnableGlobal("PuertoRico", true);
            group_DeleteGroup("Spa_Attack");
            Pchar.quest.MorrisWillams_DieHard.over = "yes";
            pchar.quest.MorrisWillams_PinnaceSink.over = "yes";
            DeleteAttribute(PChar, "questTemp.EngLineQ6_PutMoney");
            DeleteAttribute(PChar, "questTemp.QtyMoneyTillBoarding");
        break;

        case "MorrisWillams_PinnaceSink":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_40", "Logs.txt", "#space#", " "));
            Island_SetReloadEnableGlobal("PuertoRico", true);
            Pchar.quest.MorrisWillams_DieHard.over = "yes";
            pchar.quest.MorrisWillams_PinnaceBoarding.over = "yes";
            pchar.questTemp.State = "MorrisWillams_PinnaceSink";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "11");
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.EngLineQ6_PutMoney");
            DeleteAttribute(PChar, "questTemp.QtyMoneyTillBoarding");
        break;

        case "MorrisWillams_DieHard":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_41", "Logs.txt", "#space#", " "));
            Island_SetReloadEnableGlobal("PuertoRico", true);
            pchar.quest.MorrisWillams_PinnaceBoarding.over = "yes";
            pchar.quest.MorrisWillams_PinnaceSink.over = "yes";
            pchar.questTemp.State = "MorrisWillams_DieHard";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "12");
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.EngLineQ6_PutMoney");
            DeleteAttribute(PChar, "questTemp.QtyMoneyTillBoarding");
        break;

        case "MorrisWillams_Arrest":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_42", "Logs.txt", "#space#", " "));
			chrDisableReloadToLocation = true;
            sld = characterFromID("Bocman_Willams");
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "MorrisWillams_HusbandInCave":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_43", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "pirate_"+i, "man", "man", 20, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 20, 70, 60, BLADE_LONG, "pistol2", 50);
            	LAi_SetWarriorType(sld);
            	sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Jamaica_Grot", "monsters",  "monster"+i);
            }
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 1.5);

            npchar = GetCharacter(NPC_GenerateCharacter("Jillians_Husband", "citiz_3", "man", "man", 10, ENGLAND, 0, false));
            npchar.Dialog.Filename = "Quest\EngLineNpc_2.c";
        	npchar.name 	= GetConvertStr("Variable_quests_reaction_0.5", "Names.txt");
        	npchar.lastname = GetConvertStrWithReplace("Variable_quests_reaction_8", "Names.txt", "#space#", " ");
            ChangeCharacterAddressGroup(npchar, "Jamaica_Grot", "monsters", "monster4");
            LAi_SetActorType(npchar);
            LAi_SetImmortal(npchar, true);
            LAi_ActorWaitDialog(npchar, pchar);
        break;

        case "MorrisWillams_AftreFightingInCave":
            pchar.questTemp.State = "MorrisWillams_AfterFight";
            LAi_SetActorType(pchar);
            sld = characterFromID("Jillians_Husband");
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		    chrDisableReloadToLocation = false; // открыть выход из локации.
        break;

        case "MorrisWillams_SeekCirassa":
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			LAi_LocationDisableOffGenTimer("Shore_ship2", 1); //офицеров не пускать 1 день
            for (i=1; i<=7; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Skelet"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 25, PIRATE, 0, true));
                if (i == 2)
                {
                	sld.name 	= GetConvertStr("Variable_quests_reaction_0.6", "Names.txt");
                	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_9", "Names.txt", "#space#", " ");
                    sld.SaveItemsForDead = true; // сохранять на трупе вещи
                    sld.DontClearDead = true;
                    FantomMakeCoolFighter(sld, 40, 100, 70, BLADE_LONG, "pistol3", 110);
                    GiveItem2Character(sld, "cirass5");
                    GiveItem2Character(sld, "map_nevis");
                    GiveItem2Character(sld, "map_normal");
                    GiveItem2Character(sld, "spyglass4");
                    TakeNItems(sld, "jewelry5", 150);
					TakeNItems(sld, "jewelry1", 54);
					TakeNItems(sld, "jewelry2", 32);
					TakeNItems(sld, "jewelry3", 41);
					TakeNItems(sld, "jewelry5", 25);
                }
                else FantomMakeCoolFighter(sld, 25, 80, 60, BLADE_LONG, "pistol3", 70);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
                GetCharacterPos(pchar, &locx, &locy, &locz);
				sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
				if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
               	ChangeCharacterAddressGroup(sld, "Shore_ship2", "goto", sTemp);
            }
            LAi_group_SetLookRadius("EnemyFight", 100);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "MorrisWillams_AfterFightInShore");
            Pchar.quest.MorrisWillams_SeekCirassaAgain.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.MorrisWillams_SeekCirassaAgain.win_condition.l1.location = "Shore_ship2";
            Pchar.quest.MorrisWillams_SeekCirassaAgain.win_condition = "MorrisWillams_SeekCirassaAgain";
			chrDisableReloadToLocation = true;
        break;

        case "MorrisWillams_AfterFightInShore":
            Pchar.quest.MorrisWillams_SeekCirassaAgain.over = "yes";
			chrDisableReloadToLocation = false;
        break;

        case "MorrisWillams_SeekCirassaAgain":
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1 = "location";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1.location = "Shore_ship2";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition = "MorrisWillams_SeekCirassa";
        break;

//==========================   Квест N8, К Эдварду Мэнсфилду за золотом ========================
        case "ToMansfield_IntoTheTown":
            sld = GetCharacter(NPC_GenerateCharacter("Dick_Manson", "pirate_8", "man", "man", 10, ENGLAND, 5, true));
            sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.7", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_10", "Names.txt", "#space#", " ");
        	LAi_LoginInCaptureTown(sld, true);
            ChangeCharacterAddressGroup(sld, "LaVega_tavern", "goto", "goto2");
            LAi_SetStayTypeNoGroup(sld);
			chrDisableReloadToLocation = true;//блок перехода, чтобы нельзя было уйти из локи до активации диалога
			DoQuestCheckDelay("TalkSelf_Quest", 2.0); //диалог сам-на-сам
        break;

        case "ToMansfield_OutFromFort":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_44", "Logs.txt", "#space#", " "));
            characters[GetCharacterIndex("Dick_Manson")].lifeDay = 0;
            if (pchar.questTemp.State == "ToMansfield_CatchToPardal")
            {
                Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_45", "Logs.txt", "#space#", " "));
                Pchar.quest.ToMansfield_FightNearSantiago.win_condition.l1 = "location";
                Pchar.quest.ToMansfield_FightNearSantiago.win_condition.l1.location = "Cuba1";
                Pchar.quest.ToMansfield_FightNearSantiago.win_condition = "ToMansfield_FightNearSantiago";
                SetTimerCondition("ToMansfield_NotFoundGaleon", 0, 0, 12, false);
            }
            else
            {
                AddQuestRecord("Eng_Line_8_ToMansfield", "3");
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex1", GetSexPhrase("ел","ла"));
                pchar.questTemp.State = "ToMansfield_DidNotFindBecaners";
            }
        break;

        case "ToMansfield_NotFoundGaleon":
            // ==> снимаем все прерывания, которые могут быть установлены
            Pchar.quest.ToMansfield_FightNearSantiago.over = "yes";
            pchar.questTemp.State = "ToMansfield_NotFoundGaleon";
            AddQuestRecord("Eng_Line_8_ToMansfield", "4");
			AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("","а"));
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_46", "Logs.txt", "#space#", " "));
        break;

        case "ToMansfield_FightNearSantiago":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_47", "Logs.txt", "#space#", " "));
            Pchar.quest.ToMansfield_NotFoundGaleon.over = "yes"; // снимаем таймер на появление галеона

            sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_2", "man", "man", 31, SPAIN, 0, true));
            sld.SinkTenPercent = true; // уходим с повреждениями
            sld.DontRansackCaptain = true; //квестовые не сдаются

            FantomMakeCoolSailor(sld, SHIP_GALEON, "", CANNON_TYPE_CANNON_LBS32, 95, 90, 90);
            FantomMakeCoolFighter(sld, 38, 90, 70, BLADE_LONG, "pistol3", 120);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
            Group_SetAddress("Spa_Attack", "Cuba1", "", "");
            Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_LockTask("Spa_Attack");
            //==> признак нахождения письма в комоде
            pchar.questTemp.ELQ8_PutLetter = 1;

			pchar.quest.ToMansfield_GaleonBoarding.win_condition.l1 = "Character_Capture";
			pchar.quest.ToMansfield_GaleonBoarding.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.ToMansfield_GaleonBoarding.win_condition = "ToMansfield_GaleonBoarding";

			pchar.quest.ToMansfield_GaleonSink.win_condition.l1 = "Character_sink";
			pchar.quest.ToMansfield_GaleonSink.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.ToMansfield_GaleonSink.win_condition = "ToMansfield_GaleonSink";
			pchar.quest.ToMansfield_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.ToMansfield_DieHard.win_condition = "ToMansfield_DieHard";
        break;

        case "ToMansfield_GaleonBoarding":
            if (CheckCharacterItem(pchar, "letter_2"))
            {
                Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_48", "Logs.txt", "#space#", " "));
                AddQuestRecord("Eng_Line_8_ToMansfield", "5");
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex1", GetSexPhrase("ел","ла"));
                pchar.questTemp.State = "ToMansfield_Boarding";
                TakeItemFromCharacter(pchar, "letter_2");
                ChangeItemDescribe("letter_open", "itmdescr_letter_open_EngLineQ8");
                GiveItem2Character(pchar, "letter_open");
            }
            else
            {
                Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_49", "Logs.txt", "#space#", " "));
                AddQuestRecord("Eng_Line_8_ToMansfield", "6");
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("","а"));
                pchar.questTemp.State = "ToMansfield_BoardingNotFoundLetter";
            }
            pchar.quest.ToMansfield_GaleonSink.over = "yes";
            Pchar.quest.ToMansfield_DieHard.over = "yes"; // снимаем таймер на снятие галеона
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.ELQ8_PutLetter");
            BackItemDescribe("letter_2");
        break;

        case "ToMansfield_GaleonSink":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_50", "Logs.txt", "#space#", " "));
            pchar.quest.ToMansfield_GaleonBoarding.over = "yes";
            Pchar.quest.ToMansfield_DieHard.over = "yes"; // снимаем таймер на снятие галеона
            pchar.questTemp.State = "ToMansfield_GaleonSink";
            AddQuestRecord("Eng_Line_8_ToMansfield", "7");
			AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("","а"));
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.ELQ8_PutLetter");
            BackItemDescribe("letter_2");
        break;

        case "ToMansfield_DieHard":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_51", "Logs.txt", "#space#", " "));
            pchar.quest.ToMansfield_GaleonBoarding.over = "yes";
            pchar.quest.ToMansfield_GaleonSink.over = "yes";
            pchar.questTemp.State = "ToMansfield_NotFoundGaleon";
            AddQuestRecord("Eng_Line_8_ToMansfield", "4");
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.ELQ8_PutLetter");
            BackItemDescribe("letter_2");
        break;

//==========================   Квест N9, Нападение на Саньяго ========================
        case "AttackSantiago_FightWithPardal":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_52", "Logs.txt", "#space#", " "));
            Island_SetReloadEnableGlobal("Cuba1", false);
            PChar.questTemp.ELQ9_Diffrent = 1;
            Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> генерим эскадру Пардаля
            for (i=1; i<=4; i++)
            {
                attrName = "off_spa_1";
                Rank = 27;
                ShipType = SHIP_GALEON_H;
                if (i==1)
                {
                    attrName = "SpaOfficer1";
                    Rank = 40;
                    ShipType = SHIP_REDOUTABLE;
                }
                if (i==2)
                {
                    attrName = "off_spa_2";
                    Rank = 30;
                    ShipType = SHIP_CECILIA;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, attrName, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 95, 90, 90);
                FantomMakeCoolFighter(sld, Rank, 95, 70, BLADE_LONG, "pistol3", 120);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
                if (i==1)
                {
                    sld.Ship.Name = GetConvertStrWithReplace("Variable_quests_reaction_11", "Names.txt", "#space#", " ");
                    sld.name 	= GetConvertStr("Variable_quests_reaction_0.8", "Names.txt");
                	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_12", "Names.txt", "#space#", " ");
                }
            }
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
            Group_SetAddress("Spa_Attack", "Cuba1", "", "");
            Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_LockTask("Spa_Attack");

            pchar.quest.AttackSantiago_AfterFight.win_condition.l1 = "Group_Death";
			pchar.quest.AttackSantiago_AfterFight.win_condition.l1.group = "Spa_Attack";
			pchar.quest.AttackSantiago_AfterFight.win_condition = "AttackSantiago_AfterFight";
			pchar.quest.AttackSantiago_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.AttackSantiago_DieHard.win_condition = "AttackSantiago_DieHard";
			// ==> запрет выхода на карту на 6мин если порт, а то есть возмоность свалить
            // === на карту сразу по выходу и это меняет схему боя.
            if (pchar.location.from_sea == "Santiago_town")
            {
                bQuestDisableMapEnter = true;
                DoQuestCheckDelay("CanEnterToMap", 400);
            }
        break;

        case "AttackSantiago_AfterFight":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_53", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "AttackSantiago_GoodWork";
            AddQuestRecord("Eng_Line_9_AttackSantiago", "3");
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.ELQ9_Diffrent");
            ChangeCharacterReputation(pchar, 3);
            pchar.quest.AttackSantiago_DieHard.over = "yes"; //fix
            Island_SetReloadEnableGlobal("Cuba1", true);
        break;

        case "AttackSantiago_DieHard":
			pchar.quest.AttackSantiago_AfterFight.over = "yes";
			pchar.questTemp.State = "AttackSantiago_GoodWork";
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_54", "Logs.txt", "#space#", " "));
            AddQuestRecord("Eng_Line_9_AttackSantiago", "4");
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.ELQ9_Diffrent");
            AddCharacterExpToSkill(pchar, "Leadership", -1650);
			AddCharacterExpToSkill(pchar, "Defence", -1300);
			AddCharacterExpToSkill(pchar, "Cannons", -1600);
			AddCharacterExpToSkill(pchar, "Sailing", -1400);
			AddCharacterExpToSkill(pchar, "Sneak", -1350);
			AddCharacterExpToSkill(pchar, "Grappling", 1200);
			AddCharacterExpToSkill(pchar, "Repair", -950);
			AddCharacterExpToSkill(pchar, "Pistol", -1200);
			AddCharacterExpToSkill(pchar, "Accuracy", -1510);
			AddCharacterExpToSkill(pchar, "Fencing", -1900);
			ChangeCharacterReputation(pchar, -5);
			Island_SetReloadEnableGlobal("Cuba1", true);
        break;

//==========================   Квест N10, Отбить атаку испанцев на Порт-Рояль ========================
        case "SpanishAttack_Battle":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_55", "Logs.txt", "#space#", " "));
            Island_SetReloadEnableGlobal("Jamaica", false);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> Испанские кэпы
            for (i=1; i<=7; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_SANFELIPE;
                        Model = "off_spa_1";
                        Rank = 40;
                        Blade = "blade33";
                    break;
                    case 2:
                        ShipType = SHIP_POSEIDON;
                        Model = "off_spa_2";
                        Rank = 30;
                        Blade = "blade28";
                    break;
                    case 3:
                        ShipType = SHIP_SANTAANA;
                        Model = "off_spa_1";
                        Rank = 33;
                        Blade = "blade24";
                    break;
                    case 4:
                        ShipType = SHIP_TRINITY;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade34";
                    break;
                    case 5:
                        ShipType = SHIP_LINESHIP;
                        Model = "off_spa_2";
                        Rank = 27;
                        Blade = "blade26";
                    break;
                    case 6:
                        ShipType = SHIP_REDOUTABLE;
                        Model = "off_spa_2";
                        Rank = 33;
                        Blade = "blade28";
                    break;
                    case 7:
                        ShipType = SHIP_SANTAANA;
                        Model = "off_spa_1";
                        Rank = 39;
                        Blade = "blade32";
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Jamaica", "quest_ships", "quest_ship_3");
			Group_LockTask("Spa_Attack");
			// натравим сторожевиков
			//Group_SetTaskAttack("JamaykaSquadron", "Spa_Attack"); // обязательно потом сбросить, иначе вылет
			//Group_LockTask("JamaykaSquadron");
            // ==> прерывание на убиение эскадры
            pchar.quest.SpanishAttack_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.SpanishAttack_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SpanishAttack_AfterBattle.win_condition = "SpanishAttack_AfterBattle";
			pchar.quest.SpanishAttack_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.SpanishAttack_DieHard.win_condition = "SpanishAttack_DieHard";

            if (pchar.location.from_sea == "PortRoyal_town")
            {
                bQuestDisableMapEnter = true;
                DoQuestCheckDelay("CanEnterToMap", 400);
            }
        break;

        case "SpanishAttack_AfterBattle":
            /*if (!Group_isDead("JamaykaSquadron"))
			{
            	Group_SetTaskNone("JamaykaSquadron");
            }*/
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_56", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "SpanishAttack_GoodWork";
            AddQuestRecord("Eng_Line_10_SpanishAttack", "2");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Jamaica", true);
            pchar.quest.SpanishAttack_DieHard.over = "yes";
        break;

        case "SpanishAttack_DieHard":
            /*if (!Group_isDead("JamaykaSquadron"))
            {
            	Group_SetTaskNone("JamaykaSquadron");
            } */
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_57", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "QuestLineBreake";
            AddQuestRecord("Eng_Line_10_SpanishAttack", "3");
			CloseQuestHeader("Eng_Line_10_SpanishAttack");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Jamaica", true);
            pchar.quest.SpanishAttack_AfterBattle.over = "yes";
            SetCaptureTownByNation("PortRoyal", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
            SetGovenourToCity(ENGLAND, "PortSpein");
        break;

//==========================   Квест N12, Встреча полковника Линча и арест Мэдифорда ========================
        case "ColonelLinch_IntoTheResidence":
            sld = GetCharacter(NPC_GenerateCharacter("Thomas_Linch", "ThomasLinch", "man", "man", 30, ENGLAND, 10, true));
            sld.name 	= GetConvertStr("Variable_quests_reaction_0.9", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_13", "Names.txt", "#space#", " ");
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
			sld.greeting = "Gr_military";
            ChangeCharacterAddressGroup(sld, "SentJons_townhall", "goto", "goto5");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar("Thomas_Linch", "", 0.0, 1.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
        break;

        case "ColonelLinch_AfterFight":
            pchar.nation = ENGLAND;
            Ship_FlagRefresh(PChar); //флаг на лету
            bDisableFastReload = false; // открыть переходы.
            chrDisableReloadToLocation = false; // открыть выход из локации.
            pchar.questTemp.State = "ColonelLinch_ModifordArrested";
            //LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
            sld = GetCharacter(NPC_GenerateCharacter("Thomas_Modiford", "Modyford", "man", "man", 10, ENGLAND, 40, false));
            sld.name 	= GetConvertStr("Variable_quests_reaction_0.10", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_14", "Names.txt", "#space#", " ");
            sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
            sld.dialog.currentnode = "You_baster";
			LAi_SetImmortal(sld, true);
        	FaceMaker(sld);
            SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            DoReloadCharacterToLocation("PortRoyal_prison",  "goto", "goto23");
            ChangeCharacterAddressGroup(sld, "PortRoyal_prison", "goto", "goto9");
			LAi_SetActorType(sld);
            LAi_ActorDialog(sld, Pchar, "", 1.5, 0);
			pchar.quest.ColonelLinch_Exit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.ColonelLinch_Exit.win_condition.l1.location = pchar.location;
			pchar.quest.ColonelLinch_Exit.win_condition = "ColonelLinch_Exit";
        break;

        case "ColonelLinch_Exit":
            sld = characterFromID("eng_guber");   //  Англ.губер будет Томасом Линчем.
            sld.model = "ThomasLinch";
            sld.name 	= GetConvertStr("Variable_quests_reaction_0.11", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_15", "Names.txt", "#space#", " ");
        	sld.model.animation = "man"
            SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            FaceMaker(sld);
			SetGovenourToCity(ENGLAND, "PortRoyal");
            AddQuestRecord("Eng_Line_12_ColonelLinch", "3");
            LAi_SetHuberStayType(sld);
            LAi_SetImmortal(sld, false);
            LAi_SetImmortal(characterFromID("PortRoyal_Mayor"), false);
        break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  END Английская линейка
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  START Голландская линейка
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//==========================   Квест N1, доставка Аарона Мендеса Чумакейро ========================
        case "SeekChumakeiro_intoMarigoHouse":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_58", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
			LAi_group_Delete("EnemyFight");
            for (i=1; i<=2; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "pirate_"+i, "man", "man", 20, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 18, 70, 60, BLADE_LONG, "pistol2", 10);
            	LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, false);
            	sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Marigo_houseF1", "goto",  "goto"+i);
            }
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "SeekChumakeiro_intoResidence":
            sld = characterFromID("Chumakeiro");                    //  Чумакейро в резиденции губернатора
            ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto2");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar("Chumakeiro", "", 0.0, 1.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
        break;

//==========================   Квест N4, защита Форт Оранжа   ========================
        case "DefenceOrange_FightNearJamaica":
            if (GetQuestPastDayParam("questTemp") < 12)
            {
                Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_59", "Logs.txt", "#space#", " "));
                Island_SetReloadEnableGlobal("Jamaica", false);
                //bQuestDisableMapEnter = true;
        		Group_FindOrCreateGroup("Eng_Attack");
    			Group_SetType("Eng_Attack", "war");
                // ==> Английские кэпы
                for (i=1; i<=3; i++)
                {
                    switch (i)
                    {
                        case 1:
                            ShipType = SHIP_ESSEX;
                            Model = "off_eng_1";
                            Rank = 23;
                            Blade = "blade33";
                        break;
                        case 2:
                            ShipType = SHIP_NAVY;
                            Model = "off_eng_2";
                            Rank = 19;
                            Blade = "blade28";
                        break;
                        case 3:
                            ShipType = SHIP_CORVETTE;
                            Model = "off_eng_1";
                            Rank = 21;
                            Blade = "blade24";
                        break;
                    }
                    sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, ENGLAND, 0, true));
                    FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 80, 70, 95);
                    FantomMakeCoolFighter(sld, Rank, 70, 50, Blade, "pistol3", 75);
        			Group_AddCharacter("Eng_Attack", "CaptainAttack_"+i);
                }
                // ==> стравливание
    			Group_SetGroupCommander("Eng_Attack", "CaptainAttack_1");
    			Group_SetTaskAttack("Eng_Attack", PLAYER_GROUP);
    			Group_SetAddress("Eng_Attack", "Jamaica", "quest_ships", "quest_ship_8");
    			Group_LockTask("Eng_Attack");
                // ==> прерывание на убиение эскадры
                pchar.quest.DefenceOrange_AfterBattle.win_condition.l1 = "Group_Death";
    			pchar.quest.DefenceOrange_AfterBattle.win_condition.l1.group = "Eng_Attack";
    			pchar.quest.DefenceOrange_AfterBattle.win_condition = "DefenceOrange_AfterBattle";
    			pchar.quest.DefenceOrange_DieHard.win_condition.l1 = "MapEnter";
                pchar.quest.DefenceOrange_DieHard.win_condition = "DefenceOrange_DieHard";
            }
            else
            {
                SetLocationCapturedState("FortOrange_town", true);
                pchar.questTemp.State = "DefenceOrange_LateRiseOrange";
				//--> огонь и пламень
				locations[FindLocation("FortOrange_town")].hidden_effects = true;
				locations[FindLocation("FortOrange_ExitTown")].hidden_effects = true;
				//<-- огонь и пламень
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_60", "Logs.txt", "#space#", " "));
            AddQuestRecord("Hol_Line_4_DefenceOrange", "3");
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex", GetSexPhrase("","а"));
            }
        break;

        case "DefenceOrange_AfterBattle":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_61", "Logs.txt", "#space#", " "));
            AddQuestRecord("Hol_Line_4_DefenceOrange", "2");
            pchar.questTemp.State = "DefenceOrange_SquadronDestroyed";
            group_DeleteGroup("Eng_Attack");
            Island_SetReloadEnableGlobal("Jamaica", true);
            bQuestDisableMapEnter = false;
            Pchar.quest.DefenceOrange_FightInShore.win_condition.l1 = "location";
            Pchar.quest.DefenceOrange_FightInShore.win_condition.l1.location = "FortOrange_port";
            Pchar.quest.DefenceOrange_FightInShore.win_condition = "DefenceOrange_FightInShore";
			SetLocationCapturedState("FortOrange_town", true);
        break;

        case "DefenceOrange_FightInShore":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_62", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (i=1; i<=15; i++)
            {
                if (i == 3 || i == 7 || i == 11)
                {
                    Model = "off_eng_" + (rand(1)+1);
                    Blade = "blade24";
                    Rank = 25;
                    Gun = "pistol4";
                }
                else
                {
                    Model = "sold_eng_" + (rand(7)+1);
                    Rank = 20;
                    Blade = BLADE_LONG;
                    Gun = "pistol3";
                }
                sld = GetCharacter(NPC_GenerateCharacter("Solder"+i, Model, "man", "man", 25, ENGLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 70, 60, Blade, Gun, 70);
				LAi_LoginInCaptureTown(sld, true);

            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "FortOrange_port", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
            }
            for (i=1; i<=8; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("pirate_"+i, "sold_hol_"+(rand(7)+1), "man", "man", 25, HOLLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 60, 50, Blade, Gun, 40);
				LAi_LoginInCaptureTown(sld, true);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
				if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
                ChangeCharacterAddressGroup(sld, "FortOrange_port", "goto", sTemp);
            }
            LAi_group_SetLookRadius("EnemyFight", 100);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DefenceOrange_WeWon_half");
            Pchar.quest.DefenceOrange_FightInExitTown.win_condition.l1 = "location";
            Pchar.quest.DefenceOrange_FightInExitTown.win_condition.l1.location = "FortOrange_ExitTown";
            Pchar.quest.DefenceOrange_FightInExitTown.win_condition = "DefenceOrange_FightInExitTown";
        break;
		
		case "DefenceOrange_WeWon_half":
            chrDisableReloadToLocation = false; // открыть выход из локации.
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_63", "Logs.txt", "#space#", " "));
            AddQuestRecord("Hol_Line_4_DefenceOrange", "4.1");
        break;

        case "DefenceOrange_FightInExitTown":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_64", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (i=1; i<=18; i++)
            {
                if (i == 3 || i == 7 || i == 11 || i == 17)
                {
                    Model = "off_eng_" + (rand(1)+1);
                    Blade = "blade24";
                    Rank = 25;
                    Gun = "pistol4";
                }
                else
                {
                    Model = "sold_eng_" + (rand(7)+1);
                    Rank = 20;
                    Blade = BLADE_LONG;
                    Gun = "pistol3";
                }
                sld = GetCharacter(NPC_GenerateCharacter("Solder"+i, Model, "man", "man", 25, ENGLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 100, 70, Blade, Gun, 70);
				LAi_LoginInCaptureTown(sld, true);

            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "rld", LAi_FindFarLocator("rld", locx, locy, locz));
            }
            for (i=1; i<=15; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("pirate_"+i, "sold_hol_"+(rand(7)+1), "man", "man", 25, HOLLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 60, 50, Blade, Gun, 40);
				LAi_LoginInCaptureTown(sld, true);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
                ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "rld",  LAi_FindNearestLocator("rld", locx, locy, locz));
            }
            LAi_group_SetLookRadius("EnemyFight", 100);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DefenceOrange_WeWon");
        break;

        case "DefenceOrange_WeWon":
            chrDisableReloadToLocation = false; // открыть выход из локации.
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_65", "Logs.txt", "#space#", " "));
            AddQuestRecord("Hol_Line_4_DefenceOrange", "4.2");
			SetLocationCapturedState("FortOrange_town", false);
            pchar.questTemp.State = "DefenceOrange_LandingDestroyed";
            pchar.quest.DefenceOrange_DieHard.over = "yes";
            //==> чтобы все были просто счастливы и сразу.
            QuestSetCurrentNode("FortOrange_Mayor", "DefenceOrange");
            QuestSetCurrentNode("FortOrange_waitress", "DefenceOrange");
            QuestSetCurrentNode("FortOrange_tavernkeeper", "DefenceOrange");
            QuestSetCurrentNode("FortOrange_trader", "DefenceOrange");
        break;

        case "DefenceOrange_DieHard":
            pchar.quest.DefenceOrange_AfterBattle.over = "yes";
            pchar.quest.DefenceOrange_FightInShore.over = "yes";
            AddQuestRecord("Hol_Line_4_DefenceOrange", "5");
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex1", GetSexPhrase("","а"));
            SetLocationCapturedState("FortOrange_town", true);
            group_DeleteGroup("Eng_Attack");
            Island_SetReloadEnableGlobal("Jamaica", true);
            bQuestDisableMapEnter = false;
            pchar.questTemp.State = "DefenceOrange_DieHard";
			//--> огонь и пламень
			locations[FindLocation("FortOrange_town")].hidden_effects = true;
			locations[FindLocation("FortOrange_ExitTown")].hidden_effects = true;
			//<-- огонь и пламень
        break;

//==========================   Квест N5, сопровождение трёх флейтов до Ла Веги и обратно  ========================
        case "ThreeFleutes_TalkIntoLaVega":
			chrDisableReloadToLocation = true;
            //===> Эдвард убит :( теперь Ла Вегой рулит капитан Купер.
            sld = characterFromID("Edward Mansfield");
            sld.name 	= GetConvertStr("Variable_quests_reaction_0.12", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_16", "Names.txt", "#space#", " ");
        	sld.model.animation = "man"
            sld.model = "officer_8";
            SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            FaceMaker(sld);
			//===> к ГГ подходит перец и сообщает о смерти Мэнсфилда
			sld = GetCharacter(NPC_GenerateCharacter("Talker", "officer_6", "man", "man", 25, PIRATE, 0, true));
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
        	LAi_SetStayTypeNoGroup(sld);
            GetCharacterPos(pchar, &locx, &locy, &locz);
            ChangeCharacterAddressGroup(sld, "LaVega_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.5, 0);
		ref rStore = &stores[FindStore("LaVega")];
		AddStoreGoods(rStore, GOOD_FOOD, 72000);
        break;

        case "ThreeFleutes_BackToCuracao":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_66", "Logs.txt", "#space#", " "));
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //ссорим ГГ и испанцев, а то они в нейтрале.
			SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY);
            Island_SetReloadEnableGlobal("Hispaniola1", false);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> Испанские кэпы
            for (i=1; i<=4; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_LINESHIP;
                        Model = "off_spa_1";
                        Rank = 28;
                        Blade = "blade24";
                    break;
                    case 2:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 26;
                        Blade = "blade28";
                    break;
                    case 3:
                        ShipType = SHIP_CARAVEL;
                        Model = "off_spa_1";
                        Rank = 31;
                        Blade = "blade33";
                    break;
                    case 4:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 30;
                        Blade = "blade33";
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 90, 80, 80);
                FantomMakeCoolFighter(sld, Rank, 90, 70, Blade, "pistol3", 75);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Hispaniola1", "", "");
			Group_LockTask("Spa_Attack");
            // ==> прерывание на убиение эскадры
            pchar.quest.ThreeFleutes_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.ThreeFleutes_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.ThreeFleutes_AfterBattle.win_condition = "ThreeFleutes_AfterBattle";
			pchar.quest.ThreeFleutes_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.ThreeFleutes_DieHard.win_condition = "ThreeFleutes_DieHard";
        break;

        case "ThreeFleutes_AfterBattle":
            Island_SetReloadEnableGlobal("Hispaniola1", true);
            pchar.quest.ThreeFleutes_DieHard.over = "yes";
			group_DeleteGroup("Spa_Attack");
			//--> сколько у нас флейтов из компаньонов
			iTemp = 0;
            for (i=1; i<=COMPANION_MAX; i++)
            {
                ShipType = GetCompanionIndex(pchar,i);
                if(ShipType != -1)
                {
                	sld = GetCharacter(ShipType);
                    ShipType = sti(sld.ship.type);
                    Rank = sti(RealShips[ShipType].basetype);
                    if (Rank == SHIP_FLEUT) iTemp++;
                }
            }
			//--> результат в СЖ
			if (iTemp < 3)
            {
                pchar.questTemp.State = "ThreeFleutes_LostFleuts";
                if (iTemp < 1)
                {
                    AddQuestRecord("Hol_Line_5_ThreeFleutes", "6");
					AddQuestUserData("Hol_Line_5_ThreeFleutes", "sSex", GetSexPhrase("","а"));
                }
                else
                {
                    AddQuestRecord("Hol_Line_5_ThreeFleutes", "5");
                    AddQuestUserData("Hol_Line_5_ThreeFleutes", "QtyFleutes", iTemp);
                }
            }
            else
            {
                AddQuestRecord("Hol_Line_5_ThreeFleutes", "4");
				AddQuestUserData("Hol_Line_5_ThreeFleutes", "sSex", GetSexPhrase("","а"));
                pchar.questTemp.State = "ThreeFleutes_AllFleuts";
            }
        break;

        case "ThreeFleutes_DieHard":
            pchar.quest.ThreeFleutes_AfterBattle.over = "yes";
            AddQuestRecord("Hol_Line_5_ThreeFleutes", "3");
            pchar.questTemp.State = "ThreeFleutes_DieHard";
            Island_SetReloadEnableGlobal("Hispaniola1", true);
            group_DeleteGroup("Spa_Attack");
            for (i=1; i<=3; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
        break;

//==========================   Квест N7, доставка депеши на Тортугу  ========================
        case "DelivLettTortuga_SnapMeeting":
			chrDisableReloadToLocation = true;
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_67", "Logs.txt", "#space#", " "));
            sld = GetCharacter(NPC_GenerateCharacter("Stranger_HL7", "citiz_2", "man", "man", 15, FRANCE, 0, false));
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.13", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_17", "Names.txt", "#space#", " ");
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "DelivLettTortuga_2KickPhar":
            LAi_SetCitizenType(characterFromId("AntonioDeBarras"));
            LAi_ActorAnimation(pchar, "death_2", "DelivLettTortuga_3KickPhar", 3.0);
        break;

        case "DelivLettTortuga_3KickPhar":
            LAi_ActorSetLayMode(pchar);
            DoQuestCheckDelay("DelivLettTortuga_KickPhar", 1.0);
            sld = characterFromID("AntonioDeBarras");
            ChangeCharacterAddress(sld, "None", "");
        break;

        case "DelivLettTortuga_KickPhar":
            SetLaunchFrameFormParam(GetConvertStr("Variable_quests_reaction_1", "Frames.txt"), "", 0, 3);
            LaunchFrameForm();
            WaitDate("", 0, 0, 0, 1, 10); //крутим час
        	RecalculateJumpTable();
			pchar.questTemp.State = "DelivLettTortuga_AfterRape";
            //LAi_SetStayType(sld);
            TakeItemFromCharacter(pchar, "letter_1");
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "4");
            LAi_SetPlayerType(pchar);
            LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);
        break;

        case "DelivLettTortuga_BrigTimeOver":
            pchar.quest.DelivLettTortuga_AttackBrig.over = "yes";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "7");
            pchar.questTemp.State.KingResult = "BrigNotFound"; //флаг на вообще не нашёл
        break;

        case "DelivLettTortuga_AttackBrig":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_68", "Logs.txt", "#space#", " "));
            pchar.quest.DelivLettTortuga_BrigTimeOver.over = "yes";
            //SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY); //ссорим ГГ и пиратов.
            Island_SetReloadEnableGlobal("PuertoRico", false);
    		Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "trade");
            sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "officer_15", "man", "man", 30, PIRATE, 0, true));
            sld.Dialog.Filename    = "Quest\HolLineNpc_2.c";
			sld.DontRansackCaptain = true;
            FantomMakeCoolSailor(sld, SHIP_NAVY, GetConvertStr("Variable_quests_reaction_3", "ShipNames.txt"), CANNON_TYPE_CULVERINE_LBS24, 90, 80, 80);
            FantomMakeCoolFighter(sld, 30, 100, 40, "blade24", "pistol3", 80);
			Group_AddCharacter("Pirate_Attack", "CaptainAttack_1");
            // ==> стравливание
			Group_SetGroupCommander("Pirate_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "PuertoRico", "", "");
			Group_LockTask("Pirate_Attack");
            // ==> прерывания
			pchar.quest.DelivLettTortuga_AfterBrigSunk.win_condition.l1 = "Character_sink";
			pchar.quest.DelivLettTortuga_AfterBrigSunk.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.DelivLettTortuga_AfterBrigSunk.win_condition = "DelivLettTortuga_AfterBrigSunk";
			pchar.quest.DelivLettTortuga_BrigDieHard.win_condition.l1 = "MapEnter";
            pchar.quest.DelivLettTortuga_BrigDieHard.win_condition = "DelivLettTortuga_BrigDieHard";
        break;

        case "DelivLettTortuga_BrigDieHard":
            pchar.quest.DelivLettTortuga_AfterBrigSunk.over = "yes";
            group_DeleteGroup("Pirate_Attack");
            Island_SetReloadEnableGlobal("PuertoRico", true);
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "7");
            pchar.questTemp.State.KingResult = "BrigNotFound"; //флаг на вообще не нашёл
        break;

        case "DelivLettTortuga_AfterBrigSunk":
            pchar.quest.DelivLettTortuga_BrigDieHard.over = "yes";
            Island_SetReloadEnableGlobal("PuertoRico", true);
            group_DeleteGroup("Pirate_Attack");
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "6");
            pchar.questTemp.State.KingResult = "BrigSunk"; //флаг на утонул
        break;

        case "DelivLettTortuga_WarshipTimeOver":
            pchar.quest.DelivLettTortuga_AttackWarship.over = "yes";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "9");
        break;

        case "DelivLettTortuga_AttackWarship":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_69", "Logs.txt", "#space#", " "));
            pchar.quest.DelivLettTortuga_WarshipTimeOver.over = "yes";
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //ссорим ГГ и испанцев.
			SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY);
            Island_SetReloadEnableGlobal("SantaCatalina", false);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			Group_AddCharacter("Spa_Attack", "AntonioDeBarras");
            // ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "AntonioDeBarras");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "SantaCatalina", "", "");
			Group_LockTask("Spa_Attack");
            // ==> прерывания
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.win_condition.l1 = "Character_sink";
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.win_condition.l1.character = "AntonioDeBarras";
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.win_condition = "DelivLettTortuga_AfterWarshipSunk";
			pchar.quest.DelivLettTortuga_WarshipDieHard.win_condition.l1 = "MapEnter";
            pchar.quest.DelivLettTortuga_WarshipDieHard.win_condition = "DelivLettTortuga_WarshipDieHard";
        break;

        case "DelivLettTortuga_WarshipDieHard":
            pchar.quest.DelivLettTortuga_AfterWarshipSunk.over = "yes";
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("SantaCatalina", true);
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "9");
        break;

        case "DelivLettTortuga_AfterWarshipSunk":
            pchar.quest.DelivLettTortuga_WarshipDieHard.over = "yes";
            Island_SetReloadEnableGlobal("SantaCatalina", true);
            group_DeleteGroup("Spa_Attack");
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "10");
            pchar.questTemp.State.KingResult = "WarshipSunk"; //флаг на утонул
        break;

//==========================   Квест N8, поиски Библии  ========================
        case "SeekBible_SaveDeGraf":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_70", "Logs.txt", "#space#", " "));
            Island_SetReloadEnableGlobal("Cartahena", false);
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //ссорим ГГ и испанцев.
            SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> Испанские кэпы
            for (i=1; i<=5; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_IMPLACABLE;
                        Model = "SpaOfficer2";
                        Rank = 28;
                        Blade = "blade24";
                    break;
                    case 2:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 26;
                        Blade = "blade28";
                    break;
                    case 3:
                        ShipType = SHIP_POSEIDON;
                        Model = "off_spa_1";
                        Rank = 34;
                        Blade = "blade28";
                    break;
                    case 4:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 30;
                        Blade = "blade33";
                    break;
                    case 5:
                        ShipType = SHIP_POSTILLIONEN;
                        Model = "off_spa_1";
                        Rank = 36;
                        Blade = "blade28";
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 95, 90, 85);
                FantomMakeCoolFighter(sld, Rank, 96, 80, Blade, "pistol3", 85);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Cartahena", "", "");
            // ==> де Граф
            sld = GetCharacter(NPC_GenerateCharacter("LoranDeGraf", "officer_14", "man", "man", 45, HOLLAND, -1, true));
            sld.DeckDialogNode = "First time";
            sld.Dialog.Filename = "Quest\HolLineNpc_2.c";
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.14", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_18", "Names.txt", "#space#", " ");
			sld.greeting = "Gr_MiddPirate";
			sld.ShipEnemyDisable = true; //при попадании не враждебен
        	sld.Abordage.Enable = false; // НЕЛЬЗЯ!
            LAi_SetStayTypeNoGroup(sld);
            FantomMakeCoolSailor(sld, SHIP_ROSSIYA, GetConvertStr("Variable_quests_reaction_4", "ShipNames.txt"), CANNON_TYPE_CANNON_LBS32, 90, 80, 80);
            FantomMakeCoolFighter(sld, 45, 90, 70, "topor2", "pistol3", 100);
            Group_AddCharacter("Quest_Group", "LoranDeGraf");
            Group_SetType("Quest_Group", "war");
            Group_SetGroupCommander("Quest_Group", "LoranDeGraf");
            Group_SetPursuitGroup("Quest_Group", PLAYER_GROUP);
            Group_SetAddress("Quest_Group", "Cartahena", "", "");
			// ==> стравливание
			Group_SetTaskAttack("Spa_Attack", "Quest_Group");
            Group_SetTaskAttack("Quest_Group", "Spa_Attack");
            Group_LockTask("Quest_Group");
			Group_LockTask("Spa_Attack");
            pchar.quest.SeekBible_WeWon.win_condition.l1 = "Group_Death";
			pchar.quest.SeekBible_WeWon.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SeekBible_WeWon.win_condition = "SeekBible_WeWon";
    		pchar.quest.SeekBible_NotSavedDeGraf.win_condition.l1 = "NPC_Death";
			pchar.quest.SeekBible_NotSavedDeGraf.win_condition.l1.character = "LoranDeGraf";
			pchar.quest.SeekBible_NotSavedDeGraf.win_condition = "SeekBible_NotSavedDeGraf";
			pchar.quest.SeekBible_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.SeekBible_DieHard.win_condition = "SeekBible_DieHard";
        break;

        case "SeekBible_WeWon":
            pchar.quest.SeekBible_NotSavedDeGraf.over = "yes";
            pchar.quest.SeekBible_DieHard.over = "yes";
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Cartahena", true);
            AddQuestRecord("Hol_Line_8_SeekBible", "8");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex1", GetSexPhrase("","а"));
            pchar.questTemp.State = "SeekBible_WeWon";
        break;

        case "SeekBible_DieHard":
            if (pchar.questTemp.State == "SeekBible_DeGrafIsDead")
            {
                group_DeleteGroup("Spa_Attack");
            }
            else
            {
                pchar.quest.SeekBible_WeWon.over = "yes";
                pchar.quest.SeekBible_NotSavedDeGraf.over = "yes";
                group_DeleteGroup("Spa_Attack");
                group_DeleteGroup("Quest_Group");
                Island_SetReloadEnableGlobal("Cartahena", true);
                AddQuestRecord("Hol_Line_8_SeekBible", "6");
				AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("ся","ась"));
				AddQuestUserData("Hol_Line_8_SeekBible", "sSex1", GetSexPhrase("","ла"));
                pchar.questTemp.State = "SeekBible_DeGrafDieHard";
            }
        break;

        case "SeekBible_NotSavedDeGraf":
            pchar.quest.SeekBible_WeWon.over = "yes";
            Island_SetReloadEnableGlobal("Cartahena", true);
            AddQuestRecord("Hol_Line_8_SeekBible", "7");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex1", GetSexPhrase("","а"));
            pchar.questTemp.State = "SeekBible_DeGrafIsDead";
        break;

        case "SeekBible_DeGrafToTavern":
            sld = characterFromId("LoranDeGraf");
            FreeSitLocator("Tortuga_tavern", "sit3");
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit3");
            LAi_SetSitTypeNoGroup(sld);
            group_DeleteGroup("Quest_Group");
        break;

//==========================   Квест N10, Оборона Кюрасао.  ========================
        case "SpaAttackCuracao_Battle":
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //ссорим ГГ и испанцев.
            SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY);
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_71", "Logs.txt", "#space#", " "));
            Island_SetReloadEnableGlobal("Curacao", false);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> Испанские кэпы
            for (i=1; i<=7; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_SANFELIPE;
                        Model = "off_spa_1";
                        Rank = 45;
                        Blade = "blade33";
                    break;
                    case 2:
                        ShipType = SHIP_LINESHIP;
                        Model = "off_spa_2";
                        Rank = 35;
                        Blade = "blade28";
                    break;
                    case 3:
                        ShipType = SHIP_REDOUTABLE;
                        Model = "off_spa_1";
                        Rank = 33;
                        Blade = "blade24";
                    break;
                    case 4:
                        ShipType = SHIP_TRINITY;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade34";
                    break;
                    case 5:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 32;
                        Blade = "topor2";
                    break;
                    case 6:
                        ShipType = SHIP_SANTAANA;
                        Model = "off_spa_2";
                        Rank = 32;
                        Blade = "topor2";
                    break;
                    case 7:
                        ShipType = SHIP_POSEIDON;
                        Model = "off_spa_2";
                        Rank = 32;
                        Blade = "topor2";
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Curacao", "", "");
			Group_LockTask("Spa_Attack");
			// натравим сторожевиков
			//Group_SetTaskAttack("CuracaoSquadron", "Spa_Attack"); // обязательно потом сбросить, иначе вылет
			//Group_LockTask("CuracaoSquadron");
            // ==> прерывание на убиение эскадры
            pchar.quest.SpaAttackCuracao_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.SpaAttackCuracao_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SpaAttackCuracao_AfterBattle.win_condition = "SpaAttackCuracao_AfterBattle";
			pchar.quest.SpaAttackCuracao_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.SpaAttackCuracao_DieHard.win_condition = "SpaAttackCuracao_DieHard";

            if (pchar.location.from_sea == "Villemstad_town")
            {
                bQuestDisableMapEnter = true;
                DoQuestCheckDelay("CanEnterToMap", 400);
            }
        break;

        case "SpaAttackCuracao_AfterBattle":
            /*if (!Group_isDead("CuracaoSquadron"))
			{
            	Group_SetTaskNone("CuracaoSquadron");
            }*/
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_72", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "SpaAttackCuracao_GoodWork";
            AddQuestRecord("Hol_Line_10_SpaAttackCuracao", "2");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Curacao", true);
            pchar.quest.SpaAttackCuracao_DieHard.over = "yes";
        break;

        case "SpaAttackCuracao_DieHard":
            /*if (!Group_isDead("CuracaoSquadron"))
            {
            	Group_SetTaskNone("CuracaoSquadron");
            } */
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_73", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "QuestLineBreake";
            AddQuestRecord("Hol_Line_10_SpaAttackCuracao", "3");
			CloseQuestHeader("Hol_Line_10_SpaAttackCuracao");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Curacao", true);
            pchar.quest.SpaAttackCuracao_AfterBattle.over = "yes";
            SetCaptureTownByNation("Villemstad", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
            SetGovenourToCity(HOLLAND, "Marigo");
        break;

//==========================   Квест N11, Спасти Мариго от нападения испанцев.  ========================
        case "SpaAttackSentMartin_YouLate":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_74", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "SpaAttackSentMartin_Late";
            AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "4");
			AddQuestUserData("Hol_Line_11_SpaAttackSentMartin", "sSex", GetSexPhrase("","а"));
            pchar.quest.SpaAttackSentMartin_Battle.over = "yes";
            SetCaptureTownByNation("Marigo", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
        break;

        case "SpaAttackSentMartin_Battle":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_75", "Logs.txt", "#space#", " "));
            pchar.quest.SpaAttackSentMartin_YouLate.over = "yes";
            Island_SetReloadEnableGlobal("SentMartin", false);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> Испанские кэпы
            for (i=1; i<=8; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_SANFELIPE;
                        Model = "off_spa_1";
                        Rank = 42;
                        Blade = "blade33";
                    break;
                    case 2:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_1";
                        Rank = 42;
                        Blade = "blade33";
                    break;
                    case 3:
                        ShipType = SHIP_INGERMANLAND;
                        Model = "off_spa_2";
                        Rank = 32;
                        Blade = "blade28";
                    break;
                    case 4:
                        ShipType = SHIP_IMPLACABLE;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade24";
                    break;
                    case 5:
                        ShipType = SHIP_TRINITY;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade34";
                    break;
                    case 6:
                        ShipType = SHIP_LINESHIP;
                        Model = "off_spa_2";
                        Rank = 29;
                        Blade = "blade26";
                    break;
                    case 7:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 33;
                        Blade = "blade28";
                    break;
                    case 8:
                        ShipType = SHIP_SANTAANA;
                        Model = "off_spa_1";
                        Rank = 39;
                        Blade = "blade32";
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "SentMartin", "quest_ships", "quest_ship_4");
			Group_LockTask("Spa_Attack");
			// натравим сторожевиков
			//Group_SetTaskAttack("SentMartinSquadron", "Spa_Attack"); // обязательно потом сбросить, иначе вылет
			//Group_LockTask("SentMartinSquadron");
            // ==> прерывание на убиение эскадры
            pchar.quest.SpaAttackSentMartin_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.SpaAttackSentMartin_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SpaAttackSentMartin_AfterBattle.win_condition = "SpaAttackSentMartin_AfterBattle";
			pchar.quest.SpaAttackSentMartin_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.SpaAttackSentMartin_DieHard.win_condition = "SpaAttackSentMartin_DieHard";
        break;

        case "SpaAttackSentMartin_AfterBattle":
            /*if (!Group_isDead("SentMartinSquadron"))
			{
            	Group_SetTaskNone("SentMartinSquadron");
            }*/
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_76", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "SpaAttackSentMartin_GoodWork";
            AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "2");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("SentMartin", true);
            pchar.quest.SpaAttackSentMartin_DieHard.over = "yes";
        break;

        case "SpaAttackSentMartin_DieHard":
            /*if (!Group_isDead("SentMartinSquadron"))
            {
            	Group_SetTaskNone("SentMartinSquadron");
            } */
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_77", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "QuestLineBreake";
            AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "3");
			CloseQuestHeader("Hol_Line_11_SpaAttackSentMartin");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("SentMartin", true);
            pchar.quest.SpaAttackSentMartin_AfterBattle.over = "yes";
            SetCaptureTownByNation("Marigo", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
        break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  END Голландская линейка
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  START Испанская линейка
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//========================  Квест N2, задание Инквизиции.  =======================
        case "Inquisition_MeetFrancisco":
			chrDisableReloadToLocation = true;
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_78", "Logs.txt", "#space#", " "));
            sld = GetCharacter(NPC_GenerateCharacter("Francisco", "priest_4", "man", "man", 15, SPAIN, 0, false));
            sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.15", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_19", "Names.txt", "#space#", " ");
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "Inquisition_afterFightAndrew":
            LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_bank")], true);
            sld = characterFromId("Villemstad_usurer");
            LAi_IsDead(sld) LAi_SetHP(sld, 100, 100);
        	sld.location	= "Villemstad_Bank";
        	sld.location.group = "barmen";
        	sld.location.locator = "stay";
        	LAi_SetOwnerType(sld);
        	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
        break;

        case "Inquisition_LuggerTimeOver":
            pchar.quest.Inquisition_AttackLugger.over = "yes";
            AddQuestRecord("Spa_Line_2_Inquisition", "7");
        break;

        case "Inquisition_AttackLugger":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_79", "Logs.txt", "#space#", " "));
            pchar.quest.Inquisition_LuggerTimeOver.over = "yes";
            //SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY); //ссорим ГГ и пиратов.
            Island_SetReloadEnableGlobal("Jamaica", false);
    		Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "trade");
            sld = GetCharacter(NPC_GenerateCharacter("JansenDeFonceicao", "shipowner_5", "man", "man", 25, PIRATE, -1, true));
            sld.Dialog.Filename    = "Quest\SpaLineNpc_2.c";
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.16", "Names.txt");
        	sld.lastname 	= GetConvertStr("Variable_Curacao_0.3.1", "Names.txt");
			sld.DontRansackCaptain = true;
            FantomMakeCoolSailor(sld, SHIP_LUGGER, GetConvertStr("Variable_quests_reaction_5", "ShipNames.txt"), CANNON_TYPE_CULVERINE_LBS16, 100, 100, 100);
            FantomMakeCoolFighter(sld, 25, 60, 40, "blade24", "pistol3", 70);
            Group_AddCharacter("Pirate_Attack", "JansenDeFonceicao");
            // ==> стравливание
			Group_SetGroupCommander("Pirate_Attack", "JansenDeFonceicao");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "Jamaica", "quest_ships", "quest_ship_7");
			Group_LockTask("Pirate_Attack");
            // ==> прерывания
			pchar.quest.Inquisition_AfterLuggerSink.win_condition.l1 = "NPC_Death";
			pchar.quest.Inquisition_AfterLuggerSink.win_condition.l1.character = "JansenDeFonceicao";
			pchar.quest.Inquisition_AfterLuggerSink.win_condition = "Inquisition_AfterLuggerSink";
			pchar.quest.Inquisition_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Inquisition_DieHard.win_condition = "Inquisition_DieHard";
        break;

        case "Inquisition_DieHard":
            pchar.quest.Inquisition_LuggerSink.over = "yes";
            group_DeleteGroup("Pirate_Attack");
            Island_SetReloadEnableGlobal("Jamaica", true);
            AddQuestRecord("Spa_Line_2_Inquisition", "7");
        break;

        case "Inquisition_AfterLuggerSink":
			if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
			{
				pchar.quest.Inquisition_DieHard.over = "yes";
				Island_SetReloadEnableGlobal("Jamaica", true);
				group_DeleteGroup("Pirate_Attack");
				AddQuestRecord("Spa_Line_2_Inquisition", "9");
			}
			else
			{
				characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "JansenDeFonceicao";
			}
        break;

        case "Inquisition_fightForJacow":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_80", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            sld = GetCharacter(NPC_GenerateCharacter("Bandit", "pirate_10", "man", "man", 25, PIRATE, 0, true));
            FantomMakeCoolFighter(sld, 25, 70, 60, "blade21", "pistol2", 30);
        	LAi_SetStayType(sld);
        	sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
            LAi_group_MoveCharacter(sld, "EnemyFight");
           	ChangeCharacterAddressGroup(sld, "Panama_houseSp1", "goto",  "goto1");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.3);
            Pchar.quest.Inquisition_fightForJacow2.win_condition.l1 = "location";
            Pchar.quest.Inquisition_fightForJacow2.win_condition.l1.location = "Panama_houseSp1_Room";
            Pchar.quest.Inquisition_fightForJacow2.win_condition = "Inquisition_fightForJacow2";
       break;

       case "Inquisition_fightForJacow2":
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            sld = GetCharacter(NPC_GenerateCharacter("JacowDeFonseka", "trader_7", "man", "man", 10, HOLLAND, -1, false));
            ChangeCharacterAddressGroup(sld, "Panama_houseSp1_Room", "goto",  "goto4");
           	sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
			sld.name 	= GetConvertStr("Variable_quests_reaction_0.17", "Names.txt");
			sld.lastname 	= GetConvertStr("Variable_quests_reaction_0.17.1", "Names.txt");
			LAi_SetImmortal(sld, true);
            LAi_SetStayTypeNoGroup(sld);
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "pirate_"+i, "man", "man", 25, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 25, 70, 60, BLADE_LONG, "pistol3", 30);
            	LAi_SetStayType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Panama_houseSp1_Room", "goto",  "goto"+i);
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Inquisition_afterFightJacow");
       break;

       case "Inquisition_afterFightJacow":
            chrDisableReloadToLocation = false;
            LAi_SetActorType(pchar);
            sld = characterFromID("JacowDeFonseka");
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
       break;

       case "Inquisition_fightInDangeon":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_81", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true;
            for (i=1; i<=40; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Skelet"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 1, PIRATE, 0, true));
				sld.rank = 1;
				sld.skill.Fencing = 1;
				sld.skill.Pistol = 1;
				LAi_SetHP(sld, 1, 1);
				DeleteAttribute(sld, "Items");
				GiveItem2Character(sld, "blade1");
				EquipCharacterbyItem(sld, "blade1");
				GiveItem2Character(sld, "pistol1");
				EquipCharacterbyItem(sld, "pistol1");
				TakeNItems(sld,"bullet", 1);
				AddItems(sld, "GunPowder", 1);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
                ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters",  "monster"+i);
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Inquisition_afterFightSkel");
       break;

       case "Inquisition_afterFightSkel":
            LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
            chrDisableReloadToLocation = false;
       break;
//========================  Квест N3, захват Рока Бразильца.  =======================
       case "TakeRockBras_toRock":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_82", "Logs.txt", "#space#", " "));
			pchar.questTemp.State = "TakeRockBras_toNearestMaracaibo";
            pchar.quest.Inquisition_LuggerTimeOver.over = "yes";
            //SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY); //ссорим ГГ и пиратов.
            Island_SetReloadEnableGlobal("Maracaibo", false);
    		Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "war");
            sld = GetCharacter(NPC_GenerateCharacter("RockBrasilian", "officer_15", "man", "man", 30, PIRATE, -1, true));
            sld.Dialog.Filename    = "Quest\SpaLineNpc_1.c";
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.18", "Names.txt");
        	sld GetConvertStr("Variable_quests_reaction_0.18.1", "Names.txt");
			sld.DontRansackCaptain = true;
            FantomMakeCoolSailor(sld, SHIP_CRIMSONBLOOD, GetConvertStr("Variable_quests_reaction_6", "ShipNames.txt"), CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
            FantomMakeCoolFighter(sld, 30, 90, 90, "blade28", "pistol3", 80);
            Group_AddCharacter("Pirate_Attack", "RockBrasilian");
            // ==> стравливание
			Group_SetGroupCommander("Pirate_Attack", "RockBrasilian");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "Maracaibo", "", "");
			Group_LockTask("Pirate_Attack");
            // ==> прерывания
			pchar.quest.TakeRockBras_AfterCorvetteSink.win_condition.l1 = "NPC_Death";
			pchar.quest.TakeRockBras_AfterCorvetteSink.win_condition.l1.character = "RockBrasilian";
			pchar.quest.TakeRockBras_AfterCorvetteSink.win_condition = "TakeRockBras_AfterCorvetteSink";
			pchar.quest.TakeRockBras_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.TakeRockBras_DieHard.win_condition = "TakeRockBras_DieHard";
       break;

        case "TakeRockBras_DieHard":
            pchar.questTemp.State = "TakeRockBras_DieHardRock";
            pchar.quest.TakeRockBras_AfterCorvetteSink.over = "yes";
            group_DeleteGroup("Pirate_Attack");
            Island_SetReloadEnableGlobal("Maracaibo", true);
            AddQuestRecord("Spa_Line_3_RockBrasilian", "3");
        break;

        case "TakeRockBras_AfterCorvetteSink":
            if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
			{
				pchar.questTemp.State = "TakeRockBras_RockSink";
				pchar.quest.TakeRockBras_DieHard.over = "yes";
				Island_SetReloadEnableGlobal("Maracaibo", true);
				group_DeleteGroup("Pirate_Attack");
				AddQuestRecord("Spa_Line_3_RockBrasilian", "4");
			}
			else
			{
				characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "RockBrasilian";
			}
        break;
//========================  Квест N4, Расследование убийства коменданта.  =======================
        case "Sp4Detection_Race_1":
			LAi_LocationDisableMonstersGen("Tortuga_Cave", true); //монстров не генерить
			LAi_LocationDisableOfficersGen("Shore58", true); //офицеров не пускать
            sld = GetCharacter(NPC_GenerateCharacter("AnryDEstre", "BigPirate", "man", "man", 40, FRANCE, 10, false));
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.19", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_20", "Names.txt", "#space#", " ");
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
            sld.money = 21340;
            FantomMakeCoolFighter(sld, 40, 100, 100, "blade32", "pistol4", 100);
            TakeNItems(sld,"jewelry7", 1);
            ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto7");
            LAi_SetHP(sld, 1, 1);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorRunToLocation(sld, "reload", "basement1", "Tortuga_Cave", "goto", "goto1", "", -1);
			pchar.quest.Sp4Detection_Race_2.win_condition.l1 = "location";
			pchar.quest.Sp4Detection_Race_2.win_condition.l1.location = "Tortuga_Cave";
			pchar.quest.Sp4Detection_Race_2.win_condition = "Sp4Detection_Race_2";
        break;

        case "Sp4Detection_Race_2":
            sld = characterFromId("AnryDEstre");
            LAi_ActorRunToLocation(sld, "reload", "reload2", "Shore58", "goto", "goto15", "", -1);
			pchar.quest.Sp4Detection_Race_3.win_condition.l1 = "location";
			pchar.quest.Sp4Detection_Race_3.win_condition.l1.location = "Shore58";
			pchar.quest.Sp4Detection_Race_3.win_condition = "Sp4Detection_Race_3";
        break;

        case "Sp4Detection_Race_3":
            sld = characterFromId("AnryDEstre");
        	sld.DontClearDead      = true;
        	sld.SaveItemsForDead   =   true;
            LAi_SetActorType(pchar);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
        break;

        case "Sp4Detection_YouWin":
			LAi_LocationDisableOfficersGen("Shore58", false); //офицеров пускать
			LAi_LocationDisableMonstersGen("Tortuga_Cave", false); //монстров генерить
            pchar.questTemp.State = "Sp4Detection_DEstreIsDead";
            AddQuestRecord("Spa_Line_4_MirderDetection", "6");
			AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("","а"));
        break;

//==========================   Квест N5, Разорение Ла Веги ========================
		case "Sp5LaVegaAttack_AttackGoOn":
    	    Pchar.GenQuestFort.fortCharacterIdx = GetCharacterIndex("Edward Mansfield");
    	    DeleteQuestAttribute("Union_with_Escadra");
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            SetLocationCapturedState(sld.city + "_town", true);
            DoQuestCheckDelay("Capture_Forts", 0.5);
            Ship_NationAgressive(sld, sld);
            Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_83", "Logs.txt", "#space#", " "));
            //==> снимаем губернатора, он нестандарт.
            ChangeCharacterAddress(characterFromID("Edward Mansfield"), "None", "");
            Pchar.quest.Sp5LaVegaAttack_FightWithMayor.win_condition.l1 = "location";
            Pchar.quest.Sp5LaVegaAttack_FightWithMayor.win_condition.l1.location = "LaVega_townhall";
            Pchar.quest.Sp5LaVegaAttack_FightWithMayor.win_condition = "Sp5LaVegaAttack_FightWithMayor";
        break;

        case "Sp5LaVegaAttack_FightWithMayor":
            chrDisableReloadToLocation = true; // закрыть выход из локации
            bDisableFastReload = true; // закрыть переходы.
            sld = GetCharacter(NPC_GenerateCharacter("LaVega_Comendant", "Mansfield", "man", "man", 35, PIRATE, -1, true));
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
        	sld.name 	= GetConvertStr("Variable_quests_reaction_0.20", "Names.txt");
        	sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_21", "Names.txt", "#space#", " ");
	        sld.City = "LaVega";
			LAi_LoginInCaptureTown(sld, true);
            sld.DontClearDead = true; // не убирать труп через 200с
            sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.cirassId           = Items_FindItemIdx("cirass5");
            FantomMakeCoolFighter(sld, 45, 90, 70, "blade17", "pistol3", 50);
			ChangeCharacterAddressGroup(sld, "LaVega_townhall", "goto", "goto1");
			Statistic_AddValue(Pchar, "pir_GrabbingTown", 1); // статистика
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.8);
        break;

        case "Sp5LaVegaAttack_AfterFight":
            AfterTownBattle();
            chrDisableReloadToLocation = false;
            bDisableFastReload = false;
            pchar.questTemp.State = "Sp5LaVegaAttack_WeWon";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "3");
        break;
//=================== Квест N6, перехват голландского вестового на Тортуге ===================
        case "Sp6TakeMess_waitingBoy":
            Pchar.quest.Sp6TakeMess_TalkWithBoy.win_condition.l1 = "location";
            Pchar.quest.Sp6TakeMess_TalkWithBoy.win_condition.l1.location = "Tortuga_tavern";
            Pchar.quest.Sp6TakeMess_TalkWithBoy.win_condition = "Sp6TakeMess_TalkWithBoy";
        break;

        case "Sp6TakeMess_TalkWithBoy":
            //==> Алкаш
            sld = GetCharacter(NPC_GenerateCharacter("Boozer", "citiz_3", "man", "man", 10, FRANCE, 0, false));
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
            LAi_SetSitType(sld);
			FreeSitLocator("Tortuga_tavern", "sit2");
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit2");
            //==> Посыльный
			chrDisableReloadToLocation = true;
            sld = GetCharacter(NPC_GenerateCharacter("PortMansBoy", "shipowner_10", "man", "man", 10, FRANCE, 0, false));
            sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
         	ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "goto", "goto2");
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

		case "Sp6TakeMess_Interception":
			if (GetQuestPastTimeParam("questTemp") < 3)
			{
				Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_84", "Logs.txt", "#space#", " "));
				//==> вестовой.
				sld = GetCharacter(NPC_GenerateCharacter("Messanger", "off_hol_2", "man", "man", 30, FRANCE, 30, false));
				sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
				FantomMakeCoolFighter(sld, 30, 70, 50, "blade34", "pistol5", 60);
         		ChangeCharacterAddressGroup(sld, "Tortuga_town", "reload", "reload3");
				ChangeItemDescribe("letter_1", "itmdescr_letter_1_HolLineQ7"); //даем ту же депешу, что была по голландке
				GiveItem2Character(sld,"letter_1");
				sld.money = 18430;
				sld.DontClearDead = true; // не убирать труп через 200с
				sld.SaveItemsForDead = true; // сохранять на трупе вещи
				LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Sp6TakeMess_AttackMessanger");
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2_back", "none", "", "", "Sp6TakeMess_MessengerOut", -1);
				LAi_Actor2WaitDialog(sld, pchar);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
				LocatorReloadEnterDisable("Tortuga_town", "gate_back", true);
				//==> добавим солдатиков в город
				for (i=1; i<=10; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AddSolder"+i, "Sold_fra_"+(rand(7)+1), "man", "man", 25, FRANCE, 0, true));
					sld.Dialog.Filename = "Common_Soldier.c";
					sld.city = "Tortuga";
					sld.citytype = "soldier";
					FantomMakeCoolFighter(sld, sti(pchar.rank)+6, 70, 50, BLADE_LONG, "pistol3", 60);
            		LAi_SetPatrolType(sld);
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto",  "goto"+(rand(20)+1));
					LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
				}
				LAi_group_SetLookRadius("FRANCE_CITIZENS", 50);
				Pchar.quest.Sp6TakeMess_FightInPort.win_condition.l1 = "location";
				Pchar.quest.Sp6TakeMess_FightInPort.win_condition.l1.location = "Tortuga";
				Pchar.quest.Sp6TakeMess_FightInPort.win_condition = "Sp6TakeMess_FightInPort";
			}
        break;

        case "Sp6TakeMess_AttackMessanger":
			iTemp = GetCharacterIndex("Messanger");
			if (iTemp != -1)
			{
				sld = &characters[iTemp];
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
				LAi_group_Attack(sld, Pchar);
				SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			}
        break;

        case "Sp6TakeMess_MessengerOut":
			ChangeCharacterAddress(characterFromID("Messanger"), "None", "");
        break;

		case "Sp6TakeMess_FightInPort":
			if (GetCharacterIndex("Messanger") == -1)
			{
				bDisableFastReload = false; //открываем фаст релоад
				LocatorReloadEnterDisable("Tortuga_town", "gate_back", false);
				SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
				Island_SetReloadEnableGlobal("Tortuga", false);
    			Group_FindOrCreateGroup("Fra_Attack");
				Group_SetType("Fra_Attack", "war");
				// ==> Французские кэпы
				for (i=1; i<=8; i++)
				{
					iTemp = FRANCE;
					switch (i)
					{
						case 1:
							ShipType = SHIP_BELLE;
							Model = "off_fra_1";
							Rank = 42;
							Blade = "blade33";
						break;
						case 2:
							ShipType = SHIP_BRIG;
							Model = "off_fra_1";
							Rank = 42;
							Blade = "blade33";
						break;
						case 3:
							ShipType = SHIP_BELLE;
							Model = "off_fra_2";
							Rank = 32;
							Blade = "blade28";
						break;
						case 4:
							ShipType = SHIP_BELLE;
							Model = "off_fra_1";
							Rank = 35;
							Blade = "blade24";
						break;
						case 5:
							ShipType = SHIP_PANDORA;
							Model = "off_fra_1";
							Rank = 35;
							Blade = "blade34";
						break;
						case 6:
							ShipType = SHIP_NAVY;
							Model = "off_hol_2";
							Rank = 29;
							Blade = "blade26";
							//iTemp = HOLLAND;
						break;
						case 7:
							ShipType = SHIP_DEBRACKW;
							Model = "off_fra_2";
							Rank = 33;
							Blade = "blade28";
						break;
						case 8:
							ShipType = SHIP_CORVETTE;
							Model = "off_fra_1";
							Rank = 39;
							Blade = "blade32";
						break;
					}
					sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, iTemp, -1, true));
					FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS24, 80, 70, 90);
					FantomMakeCoolFighter(sld, Rank, 80, 60, Blade, "pistol3", 75);
    				Group_AddCharacter("Fra_Attack", "CaptainAttack_"+i);
				}
				// ==> стравливание
				Group_SetGroupCommander("Fra_Attack", "CaptainAttack_1");
				Group_SetTaskAttack("Fra_Attack", PLAYER_GROUP);
				Group_SetPursuitGroup("Fra_Attack", PLAYER_GROUP);
				Group_SetAddress("Fra_Attack", "Tortuga", "", "");
				Group_LockTask("Fra_Attack");
				pchar.quest.Sp6TakeMess_OpenTortuga.win_condition.l1 = "MapEnter";
				pchar.quest.Sp6TakeMess_OpenTortuga.win_condition = "Sp6TakeMess_OpenTortuga";
			}
			else characters[GetCharacterIndex("Messanger")].lifeDay = 0;
        break;

		case "Sp6TakeMess_OpenTortuga":
			Island_SetReloadEnableGlobal("Tortuga", true);
        break;

		case "Sp6TakeMess_WaitMessanger":
            chrDisableReloadToLocation = true; // закрыть выход из локации
            bDisableFastReload = true; // закрыть переходы.
			DoQuestCheckDelay("Sp6TakeMess_2WaitMessanger", 10.0);
        break;

		case "Sp6TakeMess_2WaitMessanger":
            sld = GetCharacter(NPC_GenerateCharacter("Messanger", "off_hol_2", "man", "man", 40, FRANCE, 0, false));
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
            FantomMakeCoolFighter(sld, 40, 95, 80, "blade34", "pistol5", 100);
         	ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "reload", "reload1_back");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_HolLineQ7"); //даем ту же депешу, что была по голландке
            GiveItem2Character(sld,"letter_1");
            sld.money = 18430;
            sld.DontClearDead = true; // не убирать труп через 200с
            sld.SaveItemsForDead = true; // сохранять на трупе вещи
	        LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;
//=================== Квест N7, спасти Пардаля ===================
        case "Sp7SavePardal_FightNearAntigua":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_85", "Logs.txt", "#space#", " "));
			PChar.questTemp.SLQ7_Diffrent = 1; //Моисею Воклейну в каюту
            Island_SetReloadEnableGlobal("Antigua", false);
			// ==> Пардаль
            Group_SetType("Quest_Group", "war");
    		Group_FindOrCreateGroup("Quest_Group");
            for (i=1; i<=3; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_REDOUTABLE;
                        Model = "SpaOfficer1";
                        Rank = 30;
                        Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 2:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_1";
                        Rank = 27;
                        Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_ROTERLOW;
                        Model = "off_spa_2";
                        Rank = 24;
                        Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS16;
                    break;
				}
                sld = GetCharacter(NPC_GenerateCharacter("OurCaptain_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
				sld.ShipEnemyDisable = true; //при попадании не враждебен
				FantomMakeCoolSailor(sld, ShipType, "", iTemp, 60, 50, 50);
                FantomMakeCoolFighter(sld, Rank, 70, 40, Blade, "pistol3", 50);
				if (sld.id == "OurCaptain_1")
				{
					sld.DeckDialogNode = "First time";
					sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
        			sld.name 	= GetConvertStr("Variable_quests_reaction_0.21", "Names.txt");
        			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_22", "Names.txt", "#space#", " ");
					sld.greeting = "Gr_military";
        			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
					sld.Ship.Name = GetConvertStrWithReplace("Variable_quests_reaction_23", "Names.txt", "#space#", " ");
					LAi_SetStayTypeNoGroup(sld);
				}
    			Group_AddCharacter("Quest_Group", "OurCaptain_"+i);
			}
            Group_SetGroupCommander("Quest_Group", "OurCaptain_1"); //это Пардаль
			Group_SetPursuitGroup("Quest_Group", PLAYER_GROUP);
			Group_SetAddress("Quest_Group", "Antigua", "", "");
			// ==> Флибустьеры
    		Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
            for (i=1; i<=7; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_REDOUTABLE;
                        Rank = 35;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 2:
                        ShipType = SHIP_DIANA;
                        Rank = 31;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_INGERMANLAND;
                        Rank = 33;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 4:
                        ShipType = SHIP_CRIMSONBLOOD;
                        Rank = 29;
                        Blade = "blade24";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 5:
                        ShipType = SHIP_REDOUTABLE;
                        Rank = 34;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 6:
                        ShipType = SHIP_LINESHIP;
                        Rank = 32;
                        Blade = "blade26";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 7:
                        ShipType = SHIP_CRIMSONBLOOD;
                        Rank = 28;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
				}
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "officer_"+(rand(42)+1), "man", "man", Rank, PIRATE, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
				if (sld.id == "CaptainAttack_1")
				{
        			sld.name 	= GetConvertStr("Variable_quests_reaction_0.22", "Names.txt");
        			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_24", "Names.txt", "#space#", " ");
					sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
					sld.Ship.Name = GetConvertStrWithReplace("Variable_quests_reaction_25", "Names.txt", "#space#", " ");
					LAi_SetStayTypeNoGroup(sld);
				}
    			Group_AddCharacter("Pir_Attack", "CaptainAttack_"+i);
            }
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
            Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Antigua", "", "");
			// ==> стравливание
			Group_SetTaskAttack("Pir_Attack", "Quest_Group");
            Group_SetTaskAttack("Quest_Group", "Pir_Attack");
            Group_LockTask("Quest_Group");
			//Group_LockTask("Pir_Attack");
			// ==> прерывание на убиение эскадры
            pchar.quest.Sp7SavePardal_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp7SavePardal_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp7SavePardal_AfterBattle.win_condition = "Sp7SavePardal_AfterBattle";
    		pchar.quest.Sp7SavePardal_NotSavedPardal.win_condition.l1 = "NPC_Death";
			pchar.quest.Sp7SavePardal_NotSavedPardal.win_condition.l1.character = "OurCaptain_1";
			pchar.quest.Sp7SavePardal_NotSavedPardal.win_condition = "Sp7SavePardal_NotSavedPardal";
			pchar.quest.Sp7SavePardal_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Sp7SavePardal_DieHard.win_condition = "Sp7SavePardal_DieHard";
        break;

        case "Sp7SavePardal_AfterBattle":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_86", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "Sp7SavePardal_GoodWork";
            AddQuestRecord("Spa_Line_7_SavePardal", "2");
			AddQuestUserData("Spa_Line_7_SavePardal", "sSex", GetSexPhrase("ел","ла"));
            Island_SetReloadEnableGlobal("Antigua", true);
			pchar.quest.Sp7SavePardal_NotSavedPardal.over = "yes";
        break;

        case "Sp7SavePardal_DieHard":
			group_DeleteGroup("Pir_Attack");
			group_DeleteGroup("Quest_Group");
            if (pchar.questTemp.State != "Sp7SavePardal_PardalIsSink" && pchar.questTemp.State != "Sp7SavePardal_GoodWork" && pchar.questTemp.State != "Sp7SavePardal_2GoodWork")
			{
				Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_87", "Logs.txt", "#space#", " "));
				pchar.questTemp.State = "Sp7SavePardal_DieHard";
				AddQuestRecord("Spa_Line_7_SavePardal", "3");
				Island_SetReloadEnableGlobal("Antigua", true);
				pchar.quest.Sp7SavePardal_AfterBattle.over = "yes";
				pchar.quest.Sp7SavePardal_NotSavedPardal.over = "yes";
			}
        break;

        case "Sp7SavePardal_NotSavedPardal":
            pchar.quest.Sp7SavePardal_AfterBattle.over = "yes";
            Island_SetReloadEnableGlobal("Antigua", true);
            AddQuestRecord("Spa_Line_7_SavePardal", "4");
            pchar.questTemp.State = "Sp7SavePardal_PardalIsSink";
        break;
//=================== Квест N8, спасти Куману ===================
        case "Sp8SaveCumana_RescueTimeOver":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_88", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "Sp8SaveCumana_YouLate";
            AddQuestRecord("Spa_Line_8_SaveCumana", "2");
            pchar.quest.Sp8SaveCumana_Battle.over = "yes";
			SetLocationCapturedState("Cumana_town", true);
			//TO_DO партиклы в куману
        break;

        case "Sp8SaveCumana_Battle":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_89", "Logs.txt", "#space#", " "));
            pchar.quest.Sp8SaveCumana_RescueTimeOver.over = "yes";
			PChar.questTemp.SLQ8_Diffrent = 1; //капитану Анселю в каюту
            Island_SetReloadEnableGlobal("Cumana", false);
    		Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
            // ==> Пиратские кэпы
            for (i=1; i<=8; i++)
            {
                switch (i)
                {
					case 1:
                        ShipType = SHIP_REDOUTABLE;
                        Rank = 42;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 2:
                        ShipType = SHIP_DIANA;
                        Rank = 34;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_INGERMANLAND;
                        Rank = 36;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 4:
                        ShipType = SHIP_CRIMSONBLOOD;
                        Rank = 32;
                        Blade = "blade24";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 5:
                        ShipType = SHIP_REDOUTABLE;
                        Rank = 37;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 6:
                        ShipType = SHIP_LINESHIP;
                        Rank = 33;
                        Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 7:
                        ShipType = SHIP_CRIMSONBLOOD;
                        Rank = 33;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 8:
                        ShipType = SHIP_DIANA;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade32";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "officer_"+(rand(42)+1), "man", "man", Rank, PIRATE, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
				if (sld.id == "CaptainAttack_1")
				{
        			sld.name 	= GetConvertStr("Variable_quests_reaction_0.23", "Names.txt");
        			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_26", "Names.txt", "#space#", " ");
					sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
					sld.Ship.Name = GetConvertStrWithReplace("Variable_quests_reaction_27", "Names.txt", "#space#", " ");
					LAi_SetStayTypeNoGroup(sld);
				}
    			Group_AddCharacter("Pir_Attack", "CaptainAttack_"+i);
            }
            // ==> стравливание
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pir_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Cumana", "", "");
			Group_LockTask("Pir_Attack");
            pchar.quest.Sp8SaveCumana_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp8SaveCumana_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp8SaveCumana_AfterBattle.win_condition = "Sp8SaveCumana_AfterBattle";
			pchar.quest.Sp8SaveCumana_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Sp8SaveCumana_DieHard.win_condition = "Sp8SaveCumana_DieHard";
        break;

        case "Sp8SaveCumana_AfterBattle":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_90", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "Sp8SaveCumana_GoodWork";
            AddQuestRecord("Spa_Line_8_SaveCumana", "3");
			AddQuestUserData("Spa_Line_8_SaveCumana", "sSex", GetSexPhrase("","а"));
            group_DeleteGroup("Pir_Attack");
            Island_SetReloadEnableGlobal("Cumana", true);
            pchar.quest.Sp8SaveCumana_DieHard.over = "yes";
        break;

        case "Sp8SaveCumana_DieHard":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_91", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "Sp8SaveCumana_DieHard";
            AddQuestRecord("Spa_Line_8_SaveCumana", "4");
	    AddQuestUserData("Spa_Line_8_SaveCumana", "sSex", GetSexPhrase("","а"));
            group_DeleteGroup("Pir_Attack");
            Island_SetReloadEnableGlobal("Cumana", true);
            pchar.quest.Sp8SaveCumana_AfterBattle.over = "yes";
			SetLocationCapturedState("Cumana_town", true);
			//TO_DO партиклы в куману
        break;
//=================== Квест N9, сопровождение четырех галеонов ===================
        case "Sp9SaveCumana_toCaimanBattle":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_92", "Logs.txt", "#space#", " "));
			pchar.questTemp.State = "Sp9SaveCumana_BackHavana";
            Island_SetReloadEnableGlobal("Caiman", false);
    		Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
            // ==> Пиратские кэпы
            for (i=1; i<=5; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_LINESHIP;
                        Rank = 32;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 2:
                        ShipType = SHIP_GALEON_H;
                        Rank = 26;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_CARAVEL;
                        Rank = 25;
                        Blade = "blade25";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 4:
                        ShipType = SHIP_GALEON_H;
                        Rank = 27;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 5:
                        ShipType = SHIP_INGERMANLAND;
                        Rank = 30;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "officer_"+(rand(42)+1), "man", "man", Rank, PIRATE, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", iTemp, 90, 80, 80);
                FantomMakeCoolFighter(sld, Rank, 90, 70, Blade, "pistol3", 75);
    			Group_AddCharacter("Pir_Attack", "CaptainAttack_"+i);
            }
            // ==> стравливание
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pir_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Caiman", "", "");
			Group_LockTask("Pir_Attack");
            // ==> прерывание на убиение эскадры
            pchar.quest.Sp9SaveCumana_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp9SaveCumana_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp9SaveCumana_AfterBattle.win_condition = "Sp9SaveCumana_AfterBattle";
			pchar.quest.Sp9SaveCumana_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Sp9SaveCumana_DieHard.win_condition = "Sp9SaveCumana_DieHard";
        break;

        case "Sp9SaveCumana_AfterBattle":
            Island_SetReloadEnableGlobal("Caiman", true);
            pchar.quest.Sp9SaveCumana_DieHard.over = "yes";
			group_DeleteGroup("Pir_Attack");
			//--> сколько у нас флейтов из компаньонов
			iTemp = 0;
            for (i=1; i<=COMPANION_MAX; i++)
            {
                ShipType = GetCompanionIndex(pchar,i);
                if(ShipType != -1)
                {
                	sld = GetCharacter(ShipType);
                    ShipType = sti(sld.ship.type);
                    Rank = sti(RealShips[ShipType].basetype);
                    if (Rank == SHIP_ROTERLOW) iTemp++;
                }
            }
			//--> результат в СЖ
			if (iTemp < 4)
            {
                if (iTemp == 1)
                {
                    AddQuestRecord("Spa_Line_9_FourGolgGaleons", "3");
					AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("","а"));
                }
                else
                {
                    AddQuestRecord("Spa_Line_9_FourGolgGaleons", "4");
					AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("","а"));
                    AddQuestUserData("Spa_Line_9_FourGolgGaleons", "QtyGaleons", iTemp);
                }
            }
            else
			{
				AddQuestRecord("Spa_Line_9_FourGolgGaleons", "5");
				AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("","а"));
	        }
        break;

        case "Sp9SaveCumana_DieHard":
            pchar.quest.Sp9SaveCumana_AfterBattle.over = "yes";
            AddQuestRecord("Spa_Line_9_FourGolgGaleons", "6");
            Island_SetReloadEnableGlobal("Caiman", true);
            group_DeleteGroup("Pir_Attack");
            for (i=1; i<=4; i++)
            {
                sld = characterFromID("Captain_"+i);
                if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
        break;
//=================== Квест N10, Защита Маракайбо  ===================
        case "Sp10Maracaibo_TalkWithOfficer":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_93", "Logs.txt", "#space#", " "));
            sld = GetCharacter(NPC_GenerateCharacter("SpaTalkOfficer", "off_spa_2", "man", "man", 20, SPAIN, 0, true));
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
         	ChangeCharacterAddressGroup(sld, "Maracaibo_town", "goto", "goto8");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;

        case "Sp10Maracaibo_Battle":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_94", "Logs.txt", "#space#", " "));
            Island_SetReloadEnableGlobal("Maracaibo", false);
    		Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
            // ==> Пиратские кэпы
            for (i=1; i<=8; i++)
            {
                switch (i)
                {
					case 1:
                        ShipType = SHIP_CRISTIAN;
                        Rank = 45;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 2:
                        ShipType = SHIP_DIANA;
                        Rank = 34;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_INGERMANLAND;
                        Rank = 37;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 4:
                        ShipType = SHIP_CRIMSONBLOOD;
                        Rank = 32;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 5:
                        ShipType = SHIP_REDOUTABLE;
                        Rank = 39;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 6:
                        ShipType = SHIP_LINESHIP;
                        Rank = 36;
                        Blade = "blade32";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 7:
                        ShipType = SHIP_CRISTIAN;
                        Rank = 42;
                        Blade = "topor2";
						iTemp = CANNON_TYPE_CANNON_LBS42;
                    break;
                    case 8:
                        ShipType = SHIP_DIANA;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "officer_"+(rand(42)+1), "man", "man", Rank, PIRATE, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
    			Group_AddCharacter("Pir_Attack", "CaptainAttack_"+i);
            }
            // ==> стравливание
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pir_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Maracaibo", "", "");
			Group_LockTask("Pir_Attack");
            pchar.quest.Sp10Maracaibo_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp10Maracaibo_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp10Maracaibo_AfterBattle.win_condition = "Sp10Maracaibo_AfterBattle";
			pchar.quest.Sp10Maracaibo_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Sp10Maracaibo_DieHard.win_condition = "Sp10Maracaibo_DieHard";
        break;

        case "Sp10Maracaibo_AfterBattle":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_95", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "Sp10Maracaibo_GoodWork";
            AddQuestRecord("Spa_Line_10_Maracaibo", "3");
            group_DeleteGroup("Pir_Attack");
            Island_SetReloadEnableGlobal("Maracaibo", true);
            pchar.quest.Sp10Maracaibo_DieHard.over = "yes";
        break;

        case "Sp10Maracaibo_DieHard":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_96", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "Sp10Maracaibo_DieHard";
            AddQuestRecord("Spa_Line_10_Maracaibo", "4");
            group_DeleteGroup("Pir_Attack");
            Island_SetReloadEnableGlobal("Maracaibo", true);
            pchar.quest.Sp10Maracaibo_AfterBattle.over = "yes";
            SetCaptureTownByNation("Maracaibo", ENGLAND);
            UpdateRelations();
            RefreshBattleInterface();
        break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  END Испанская линейка
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  START Французская линейка
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//=================== Квест N1, доставка Пьера Леграна до Мартиники  ===================
        case "Fr1Legran_intoLeMaren":
            GetCharacterPos(pchar, &locx, &locy, &locz);
			sld = characterFromId("Legran");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore39", "goto",  LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            for (i=1; i<=6; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("FraBandit"+i, "Pirate_"+(rand(9)+1), "man", "man", 20, PIRATE, 0, true));
                sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				FantomMakeCoolFighter(sld, 20, 65, 30, BLADE_LONG, "pistol2", 40);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Shore39", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
            }
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], true);
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "Fr1Legran_afterFightBandits":
			DeleteAttribute(&locations[FindLocation("Shore39")], "DisableEncounters"); //энкаутеры вернем
			chrDisableReloadToLocation = false;
			sld = characterFromId("Legran");
			if (!LAi_IsDead(sld))
			{
				pchar.questTemp.State = "Fr1Legran_afterFightBand";
				LAi_SetActorType(pchar);
				LAi_SetActorType(sld);
				SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
				LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 1.0);
			}
			else
			{
				pchar.questTemp.State = "Fr1Legran_LegranIsDead";
				AddQuestRecord("Fra_Line_1_LegranDis", "5");
			}
        break;
//=================== Квест N2, доставка письма в Кюрасао  ===================
        case "Fr2Letter_intoPrison_1":
			sld = GetCharacter(NPC_GenerateCharacter("HolPrisoner", "citiz_5", "man", "man", 15, HOLLAND, 0, false));
            sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
            LAi_SetStayTypeNoGroup(sld);
            LAi_LoginInCaptureTown(sld, true);
            ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto13");
            LAi_SetActorType(sld);
            LAi_ActorGoToLocator(sld, "goto", "goto23", "Fr2Letter_intoPrison_2", -1);
        break;

        case "Fr2Letter_intoPrison_2":
			pchar.questTemp.State = "Fr2Letter_PrisonTalk";
            sld = characterFromID("HolPrisoner");
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;

		case "Fr2Letter_intoPrison_3":
            WaitDate("", 0, 0, 1, 0, 0); //крутим день
			SetCurrentTime(9, 20);
        	RecalculateJumpTable();
            SetLaunchFrameFormParam(GetConvertStr("Variable_quests_reaction_2", "Frames.txt"), "", 0, 6);
            LaunchFrameForm();
			npchar = characterFromId("hol_guber");
			sld = GetCharacter(NPC_GenerateCharacter("GoverFantom", npchar.model, "man", npchar.model.animation, 15, HOLLAND, 0, false));
			sld.name  = GetConvertStr("Variable_StoryCharacters_0.4", "Names.txt");
   			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_28", "Names.txt", "#space#", " ");
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
            LAi_SetStayTypeNoGroup(sld);
            LAi_LoginInCaptureTown(sld, true);
            ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto13");
            LAi_SetActorType(sld);
            LAi_ActorGoToLocator(sld, "goto", "goto23", "Fr2Letter_intoPrison_4", -1);
        break;

        case "Fr2Letter_intoPrison_4":
			pchar.questTemp.State = "Fr2Letter_VisitGovernor";
            sld = characterFromID("GoverFantom");
			LAi_SetActorType(pchar);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;

        case "Fr2Letter_OutTavern_1":
			if (!CheckAttribute(pchar, "questTemp.Out"))
			{
				chrDisableReloadToLocation = false;
				bDisableFastReload = true;
				DoQuestCheckDelay("TalkSelf_Quest", 0.2); //диалог сам-на-сам
				pchar.quest.Fr2Letter_shore22.win_condition.l1 = "locator";
				pchar.quest.Fr2Letter_shore22.win_condition.l1.location = "Shore22";
				pchar.quest.Fr2Letter_shore22.win_condition.l1.locator_group = "quest";
				pchar.quest.Fr2Letter_shore22.win_condition.l1.locator = "detector1";
				pchar.quest.Fr2Letter_shore22.function = "Fr2Letter_shore22";
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Bandit_"+i);
				LAi_SetActorTypeNoGroup(sld);
				sTemp = "goto14";
				if (i==1) sTemp = "goto13";
				ChangeCharacterAddressGroup(sld, "Shore22", "goto", sTemp);
			}
        break;

        case "Fr2Letter_OutTavern_2":
			bDisableFastReload = false;
			if (GetQuestPastMinutesParam("questTemp") < 5)
			{
				Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_97", "Logs.txt", "#space#", " "));
				for (i=1; i<=2; i++)
				{
					sld = characterFromId("Bandit_"+i);
					ChangeCharacterAddressGroup(sld, "Villemstad_town", "officers", "houseS1_2");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "gate_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
				Pchar.quest.Fr2Letter_OutTavern_3.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_3.win_condition.l1.location = "Villemstad_ExitTown";
				Pchar.quest.Fr2Letter_OutTavern_3.win_condition = "Fr2Letter_OutTavern_3";
			}
			else Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_98", "Logs.txt", "#space#", " "));
        break;

        case "Fr2Letter_OutTavern_3":
			if (GetQuestPastMinutesParam("questTemp") < 13)
			{
				Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_99", "Logs.txt", "#space#", " "));
				for (i=1; i<=2; i++)
				{
					sld = characterFromId("Bandit_"+i);
					ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "goto", "goto11");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
				Pchar.quest.Fr2Letter_OutTavern_4.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_4.win_condition.l1.location = "Curacao_jungle_01";
				Pchar.quest.Fr2Letter_OutTavern_4.win_condition = "Fr2Letter_OutTavern_4";
				//SaveCurrentQuestDateParam("questTemp");
			}
			else Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_100", "Logs.txt", "#space#", " "));
        break;

        case "Fr2Letter_OutTavern_4":
			if (GetQuestPastMinutesParam("questTemp") < 19)
			{
				Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_101", "Logs.txt", "#space#", " "));
				for (i=1; i<=2; i++)
				{
					sld = characterFromId("Bandit_"+i);
					ChangeCharacterAddressGroup(sld, "Curacao_jungle_01", "goto", "goto5");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);

				}
				Pchar.quest.Fr2Letter_OutTavern_5.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_5.win_condition.l1.location = "Curacao_jungle_02";
				Pchar.quest.Fr2Letter_OutTavern_5.win_condition = "Fr2Letter_OutTavern_5";
				//SaveCurrentQuestDateParam("questTemp");
			}
			else Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_102", "Logs.txt", "#space#", " "));
        break;

        case "Fr2Letter_OutTavern_5":
			if (GetQuestPastMinutesParam("questTemp") < 24)
			{
				Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_103", "Logs.txt", "#space#", " "));
				for (i=1; i<=2; i++)
				{
					sld = characterFromId("Bandit_"+i);
					ChangeCharacterAddressGroup(sld, "Curacao_jungle_02", "goto", "goto4");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
				Pchar.quest.Fr2Letter_OutTavern_6.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_6.win_condition.l1.location = "Curacao_jungle_03";
				Pchar.quest.Fr2Letter_OutTavern_6.win_condition = "Fr2Letter_OutTavern_6";
				//SaveCurrentQuestDateParam("questTemp");
			}
			else Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_104", "Logs.txt", "#space#", " "));
        break;

        case "Fr2Letter_OutTavern_6":
			if (GetQuestPastMinutesParam("questTemp") < 32)
			{
				Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_105", "Logs.txt", "#space#", " "));
				for (i=1; i<=2; i++)
				{
					sld = characterFromId("Bandit_"+i);
					ChangeCharacterAddressGroup(sld, "Curacao_jungle_03", "goto", "goto7");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
			}
			else Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_106", "Logs.txt", "#space#", " "));
        break;

        case "Fr2Letter_FightWithGaleon":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_107", "Logs.txt", "#space#", " "));
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_1", "man", "man", 30, SPAIN, 0, true));
			sld.Dialog.Filename    = "Quest\FraLineNpc_2.c";
			sld.DontRansackCaptain = true;
			FantomMakeCoolSailor(sld, SHIP_GALEON_H, GetConvertStr("Variable_quests_reaction_7", "ShipNames.txt"), CANNON_TYPE_CULVERINE_LBS24, 80, 60, 60);
			FantomMakeCoolFighter(sld, 30, 70, 50, "blade28", "pistol3", 50);
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			// ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			//Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Curacao", "quest_ships", "Quest_ship_6");
			Group_LockTask("Spa_Attack");
		break;

        case "Fr2Letter_FightAfterShot":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
            for (i=1; i<=2; i++)
            {
				sld = characterFromId("Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetHP(sld, 200, 200);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddQuestRecord("Fra_Line_2_DelivLetter", "7");
			AddQuestUserData("Fra_Line_2_DelivLetter", "sSex", GetSexPhrase("ся","ась"));
        break;
//=================== Квест N3, похищение донны Анны  ===================
		case "Fr3TakeAnna_FightInHouse":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(loadedLocation, true);
			LAi_group_Delete("PeaceGroup");
			sld = GetCharacter(NPC_GenerateCharacter("AnnaDeLeiva", "AnnaDeLeiva", "woman", "towngirl2", 10, SPAIN, -1, false));
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_29", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_30", "Names.txt", "#space#", " ");
			sld.greeting = "Gr_Dama";
			sld.RebirthPhantom = true;
			LAi_NoRebirthEnable(sld);
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
			ChangeCharacterAddressGroup(sld, "Havana_houseS1Bedroom", "goto","goto7");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_group_Delete("EnemyFight");
			//#20171007-02 Rescale fight stats
			int nRank = sti(pchar.rank)+ round((MOD_SKILL_ENEMY_RATE*3 + 1.1) / 4) + 1;
			string sGoto = "goto2";
			Model = "SpaOfficer1";
			iTemp = nRank + 3;
			attrName = "DeLeiva";
            		if(Itemp > 23)
               		iTemp = 23;
			for (i=1; i<=5; i++)
			{
				Model = "Sold_spa_"+(rand(7)+1);
				iTemp = 18;
				attrName = "SpaFighter"+i;
				if (i==1)
				{
					Model = "SpaOfficer1";
					iTemp = 23;
					attrName = "DeLeiva";
				}
				sld = GetCharacter(NPC_GenerateCharacter(attrName, Model, "man", "man", iTemp, SPAIN, 0, true));
				//#20171007-02 Rescale fight stats French Quest line
				//FantomMakeCoolFighter(sld, sTemp, 70, 50, BLADE_LONG, "pistol2", 40);
				FantomMakeCoolFighter(sld, iTemp, (50 + round(4 * MOD_SKILL_ENEMY_RATE*3 / 2)), (30 + round(4 * MOD_SKILL_ENEMY_RATE*3 / 2)), BLADE_LONG, "pistol2", (20 + round(10 * MOD_SKILL_ENEMY_RATE*3 / 2)));
				LAi_SetWarriorType(sld);
				if (i==1)
				{
					sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
					sld.name = GetConvertStrWithReplace("Variable_quests_reaction_31", "Names.txt", "#space#", " ");
					sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_32", "Names.txt", "#space#", " ");
					//ChangeCharacterAddressGroup(sld, "Havana_houseS1", "goto", "goto2");
				}
				else
				{
					LAi_warrior_DialogEnable(sld, false);
					//ChangeCharacterAddressGroup(sld, "Havana_houseS1", "goto", "goto5");
				}
				ChangeCharacterAddressGroup(sld, "Havana_houseS1", "goto", sGoto);
				Model = "Sold_spa_"+(rand(7)+1);
				iTemp = nRank;
				if(iTemp > 18)
                    iTemp = 18;
				attrName = "SpaFighter"+i;
				sGoto = "goto5";
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("DeLeiva");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			DoQuestCheckDelay("MainHeroFightModeOff", 1.0);
		break;

		case "Fr3TakeAnna_DelivShip":
			sld = characterFromId("AnnaDeLeiva");
			if (LAi_IsDead(sld))
			{
				AddQuestRecord("Fra_Line_3_TakeAnna", "5");
				pchar.questTemp.State = "Fr3TakeAnna_BadResult";
				DeleteAttribute(sld, "RebirthPhantom");
				sld.LifeDay = 0;
			}
			else
			{
				AddQuestRecord("Fra_Line_3_TakeAnna", "4");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false);
				pchar.questTemp.State = "Fr3TakeAnna_NiceResult";
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, "Tortuga_townhall", "goto", "goto2");
			}
		break;

		case "Fr3_AfterAnna_IKnowYou": //Узнавание ГГ в таверне Гаваны.
			sld = characterFromId("Havana_waitress");
			if (sti(sld.nation) == SPAIN)
			{
				chrDisableReloadToLocation = true;
				LAi_LocationFightDisable(&Locations[FindLocation("Havana_tavern")], false);
				sld.dialog.currentnode = "Allarm";
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
			}
		break;

//=================== Квест N4, Солей Руаяль, сопровождение до Гваделупы  ===================
		case "Fr4SoleiRoyal_Fight":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_108", "Logs.txt", "#space#", " "));
            Island_SetReloadEnableGlobal("Dominica", false);
			group_DeleteGroup("Spa_Attack");
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> Испанские кэпы
            for (i=1; i<=4; i++)
            {
                switch (i)
                {
					case 1:
                        ShipType = SHIP_GALEON;
                        Rank = 23;
                        Blade = "topor2";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 2:
                        ShipType = SHIP_GALEON;
                        Rank = 21;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_GALEON;
                        Rank = 23;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    /*case 4:
                        ShipType = SHIP_INGERMANLAND;
                        Rank = 32;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 5:
                        ShipType = SHIP_GALEON_H;
                        Rank = 24;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 6:
                        ShipType = SHIP_GALEON_H;
                        Rank = 32;
                        Blade = "blade32";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;*/
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "off_spa_"+(rand(1)+1), "man", "man", Rank, SPAIN, 0, true));
				if (i==3)
				{
					sld.name = GetConvertStrWithReplace("Variable_quests_reaction_33", "Names.txt", "#space#", " ");
					sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_34", "Names.txt", "#space#", " ");
					sld.DontRansackCaptain = true;
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 80, 80, 60);
					FantomMakeCoolFighter(sld, Rank, 77, 80, Blade, "pistol5", 80);
				}
				else
				{
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 60, 50, 50);
					FantomMakeCoolFighter(sld, Rank, 80, 90, Blade, "pistol3", 50);
				}
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Dominica", "", "");
			Group_LockTask("Spa_Attack");
            pchar.quest.Fr4SoleiRoyal_WiWon.win_condition.l1 = "Group_Death";
			pchar.quest.Fr4SoleiRoyal_WiWon.win_condition.l1.group = "Spa_Attack";
			pchar.quest.Fr4SoleiRoyal_WiWon.win_condition = "Fr4SoleiRoyal_WiWon";
			pchar.quest.Fr4SoleiRoyal_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Fr4SoleiRoyal_DieHard.win_condition = "Fr4SoleiRoyal_DieHard";
        break;

        case "Fr4SoleiRoyal_WiWon":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_109", "Logs.txt", "#space#", " "));
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Dominica", true);
			pchar.quest.Fr4SoleiRoyal_DieHard.over = "yes";
			if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
			{
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "4");
				AddQuestUserData("Fra_Line_4_SoleiRoyal", "sSex", GetSexPhrase("ся","лась"));
				pchar.questTemp.State = "Fr4SoleiRoyal_SoleiRoyalSunk";

			}
			else
			{
				pchar.questTemp.State = "Fr4SoleiRoyal_GoodWork";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "3");
				AddQuestUserData("Fra_Line_4_SoleiRoyal", "sSex", GetSexPhrase("ся","лась"));
			}
        break;

        case "Fr4SoleiRoyal_DieHard":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_110", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "Fr4SoleiRoyal_DieHard";
            AddQuestRecord("Fra_Line_4_SoleiRoyal", "5");
			AddQuestUserData("Fra_Line_4_SoleiRoyal", "sSex", GetSexPhrase("ся","лась"));
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Dominica", true);
            pchar.quest.Fr4SoleiRoyal_WiWon.over = "yes";
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			sld.LifeDay = 0;
        break;
		//=================== Квест N5, решение проблем донны Анны  ===================
        case "Fr5Anna_InShore":
			chrDisableReloadToLocation = true;
			//==> братьев к маяку.
			for (i=1; i<=2; i++)
            {
				if (i==1) sTemp = "officer_12";
				else sTemp = "officer_2";
				sld = GetCharacter(NPC_GenerateCharacter("DeLeivaBrother_"+i, sTemp, "man", "man", 35, SPAIN, -1, true));
				if (i==1)
				{
					sld.name = GetConvertStrWithReplace("Variable_quests_reaction_35", "Names.txt", "#space#", " ");
					sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_36", "Names.txt", "#space#", " ");
					sld.money = 34780;
					FantomMakeCoolFighter(sld, 37, 95, 70, "blade25", "pistol5", 100);
				}
				else
				{
					sld.name = GetConvertStrWithReplace("Variable_quests_reaction_37", "Names.txt", "#space#", " ");
					sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_38", "Names.txt", "#space#", " ");
					sld.money = 41340;
					FantomMakeCoolFighter(sld, 34, 95, 70, "blade33", "pistol4", 100);
				}
				sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
				sld.SaveItemsForDead = true; // сохранять на трупе вещи
				sld.DontClearDead = true; // не убирать труп через 200с
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_warrior_DialogEnable(sld, true);
				ChangeCharacterAddressGroup(sld, "Mayak10", "goto", "goto12");
				LAi_group_MoveCharacter(sld, "PeaceGroup");
			}
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak10")], true);
        break;
//=================== Квест N6, доставка письма Олоне  ===================
        case "Fr6Olone_GuadeloupeBattle":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_111", "Logs.txt", "#space#", " "));
			AddQuestRecord("Fra_Line_6_Olone", "7");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("ся","лась"));
            bQuestDisableMapEnter = true;
			group_DeleteGroup("Spa_Attack");
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> Испанский кэп
            sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_1", "man", "man", 35, SPAIN, -1, true));
			sld.DontRansackCaptain = true;
			FantomMakeCoolSailor(sld, SHIP_CONSTITUTION, "", CANNON_TYPE_CULVERINE_LBS32, 100, 95, 95);
            FantomMakeCoolFighter(sld, 35, 100, 90, BLADE_LONG, "pistol3", 150);
    		Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
            // ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Guadeloupe", "", "");
			Group_LockTask("Spa_Attack");
			pchar.quest.CanEnterToMap.win_condition.l1 = "NPC_Death";
			pchar.quest.CanEnterToMap.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.CanEnterToMap.win_condition = "CanEnterToMap";
        break;

        case "Fr6Olone_TalkWithOlone":
            //==> Олоне
			GetCharacterPos(pchar, &locx, &locy, &locz);
			chrDisableReloadToLocation = true;
            sld = characterFromID("Olone");
			LAi_SetCurHPMax(sld);
         	ChangeCharacterAddress(sld, "Cumana_town", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
//=================== Квест N7, спасение рядового Рока Бразильца  ===================
		case "Fr7RockBras_DelivShip":
			sld = characterFromId("RockBrasilian");
			if (LAi_IsDead(sld))
			{
				AddQuestRecord("Fra_Line_7_RockBras", "4");
				AddQuestUserData("Fra_Line_7_RockBras", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("Fra_Line_7_RockBras", "sSex1", GetSexPhrase("","ла"));
				pchar.questTemp.State = "Fr7RockBras_RockIsDead";
				DeleteAttribute(sld, "RebirthPhantom");
				sld.LifeDay = 0;
			}
			else
			{
				AddQuestRecord("Fra_Line_7_RockBras", "3");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false);
				pchar.questTemp.State = "Fr7RockBras_RockIsSaved";
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, "Tortuga_townhall", "goto", "goto2");
			}
		break;
//=================== Квест N9, отбить нападение на Порт-о-Принс  ===================
		case "Fr9GuardPP_Late":
			pchar.quest.Fr9GuardPP_Fight.over = "yes";
			pchar.questTemp.State = "Fr9GuardPP_Late";
			AddQuestRecord("Fra_Line_9_GuardPortPax", "5");
			AddQuestUserData("Fra_Line_9_GuardPortPax", "sSex", GetSexPhrase("","а"));
            SetCaptureTownByNation("PortPax", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
		break;

		case "Fr9GuardPP_Fight":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_112", "Logs.txt", "#space#", " "));
			pchar.quest.Fr9GuardPP_Late.over = "yes";
            Island_SetReloadEnableGlobal("Hispaniola2", false);
    		group_DeleteGroup("Spa_Attack");
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> Испанские кэпы
            for (i=1; i<=6; i++)
            {
                switch (i)
                {
					case 1:
                        ShipType = SHIP_SANFELIPE;
                        Rank = 40;
                        Blade = "topor2";
						iTemp = CANNON_TYPE_CANNON_LBS42;
                    break;
                    case 2:
                        ShipType = SHIP_GALEON;
                        Rank = 30;
                        Blade = "blade31";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_SANTAANA;
                        Rank = 38;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 4:
                        ShipType = SHIP_INGERMANLAND;
                        Rank = 35;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 5:
                        ShipType = SHIP_GALEON;
                        Rank = 31;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 6:
                        ShipType = SHIP_LINESHIP;
                        Rank = 36;
                        Blade = "blade32";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    /*case 7:
                        ShipType = SHIP_GALEON_H;
                        Rank = 30;
                        Blade = "topor2";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 8:
                        ShipType = SHIP_REDOUTABLE;
                        Rank = 37;
                        Blade = "blade35";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;*/
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "off_spa_"+(rand(1)+1), "man", "man", Rank, SPAIN, 0, true));
				if (i==2 || i==5 || i==7)
				{
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 80, 90, 70);
					FantomMakeCoolFighter(sld, Rank, 90, 90, Blade, "pistol3", 100);
				}
				else
				{
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 100, 90);
					FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol5", 200);
				}
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Hispaniola2", "", "");
			Group_LockTask("Spa_Attack");
            pchar.quest.Fr9GuardPP_WiWon.win_condition.l1 = "Group_Death";
			pchar.quest.Fr9GuardPP_WiWon.win_condition.l1.group = "Spa_Attack";
			pchar.quest.Fr9GuardPP_WiWon.win_condition = "Fr9GuardPP_WiWon";
			pchar.quest.Fr9GuardPP_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Fr9GuardPP_DieHard.win_condition = "Fr9GuardPP_DieHard";
        break;

        case "Fr9GuardPP_WiWon":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_113", "Logs.txt", "#space#", " "));
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			pchar.quest.Fr9GuardPP_DieHard.over = "yes";
			if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
			{
				AddQuestRecord("Fra_Line_9_GuardPortPax", "3");
				pchar.questTemp.State = "Fr9GuardPP_SoleiRoyalSunk";

			}
			else
			{
				pchar.questTemp.State = "Fr9GuardPP_GoodWork";
				AddQuestRecord("Fra_Line_9_GuardPortPax", "2");
			}
        break;

        case "Fr9GuardPP_DieHard":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_114", "Logs.txt", "#space#", " "));
            pchar.questTemp.State = "Fr9GuardPP_DieHard";
            AddQuestRecord("Fra_Line_9_GuardPortPax", "4");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Hispaniola2", true);
            pchar.quest.Fr9GuardPP_WiWon.over = "yes";
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			sld.LifeDay = 0;
            SetCaptureTownByNation("PortPax", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
        break;
//=================== Квест N12, конец войны  ===================
        case "Fr12EndOfWar_TakeOutShip":
			group_DeleteGroup("SoleiRoyal");
        break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  END Французская линейка
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////   Изабелла начало   //////////////////////////////////////////
		case "Romantic_Pirat_Spawn":
			//Атилла
		if (PChar.sex != "woman")
        {
			sld = GetCharacter(NPC_GenerateCharacter("Atilla", "pirate_1", "man", "man", 22, PIRATE, -1, false));
			sld.name 	= GetConvertStr("Variable_quests_reaction_0.24", "Names.txt");
			sld.lastname 	= "";
			GiveItem2Character(sld, GUN_COMMON);
			sld.equip.gun = GUN_COMMON;
			GiveItem2Character(sld, BLADE_LONG);
			sld.equip.blade = BLADE_LONG;
			sld.location	= "Pirates_town";
			sld.location.group = "goto";
			sld.location.locator = "goto1";
			sld.Dialog.Filename = "Quest\Isabella\Atilla.c";
			sld.greeting = "Gr_Smuggler Agent";
			sld.rank 	= 25;
			sld.reputation = 25;
			sld.talker = 5; //начать диалог
			sld.TiedItems.itm1.model = "HandsItems\meet";
			sld.TiedItems.itm1.locator = "Saber_hand";
			sld.TiedItems.itm2.model = "HandsItems\cup";
			sld.TiedItems.itm2.locator = "Saber_hand";
			SetRandSPECIAL(sld);
			SetSelfSkill(sld, 80, 70, 90, 60, 50);
			SetShipSkill(sld, 50, 10, 60, 60, 40, 70, 70, 40, 50);
			sld.money = "200";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHP(sld, 200.0, 200.0);
			LAi_NoRebirthEnable(sld);
			sld.DontClearDead = true;  // не убирать труп
			sld.greeting = "Gr_Atilla";
		}
        else
        {
            DeleteAttribute(pchar, "questdata.IstoriyaIzabely");
        }
        break;

        case "Romantic_Pirat_toTavern":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			FreeSitLocator("Pirates_tavern", "sit2");
			DoQuestReloadToLocation("Pirates_tavern", "sit", "sit2", "");
			sld = characterFromID("Atilla");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
        break;

        case "Romantic_Pirat_toTavern_end":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false); //теперь открываем дом Изабеллы
			pchar.RomanticQuest = "toSalvator";
			AddQuestRecord("Romantic_Line", "3");
			LAI_SetPlayerType(pchar);
            DoQuestReloadToLocation("Pirates_tavern", "tables", "stay3", "");
            sld = CharacterFromID("Atilla");
            LAI_SetSitType(sld);
            Pchar.quest.Romantic_TalkInShop.win_condition.l1 = "location";
            Pchar.quest.Romantic_TalkInShop.win_condition.l1.location = "SanJuan_Store";
            Pchar.quest.Romantic_TalkInShop.win_condition = "Romantic_TalkInShop";
            PChar.quest.Romantic_TalkInShop.again = true; // вешаем на долго, тк не факт, что Pchar.RomanticQuest.TalkInShop = true; было
            PChar.quest.Romantic_TalkInShop.DontCheck = true;
            Pchar.RomanticQuest.PriestAsk = true;
        break;

        case "RP_afterVisitBedroom":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			sld = characterFromID("Husband");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, Pchar, "", -1, 0);
        break;

        case "RP_talkWithHusbandIsOver":
			LAi_SetStayType(characterFromID("Husband"));
        break;

        case "Romantic_TalkInShop":
            if(CheckAttribute(Pchar, "RomanticQuest.TalkInShop"))
            {
                PChar.quest.Romantic_TalkInShop.over = "yes";
                characters[GetCharacterIndex("SanJuan_trader")].dialog.currentnode = "Romantic_1";
                sld = CharacterFromID("Isabella");
        		LAi_SetStayType(sld);
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
                sld.dialog.currentnode = "TalkInShop";
    			LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "Romantic_TalkInShop_3", -1, 0);
            }
        break;

        case "Romantic_TalkInShop_2":
			sld = characterFromID("Isabella");
            LAi_ActorDialog(sld, Pchar, "", 1.0, 0);
        break;

        case "Romantic_TalkInShop_3":
            sld = CharacterFromID("SanJuan_trader");
			LAi_SetActorType(sld);
            LAi_ActorDialog(sld, Pchar, "", 0.0, 0);
        break;

        case "Romantic_TalkInShop_end":
			chrDisableReloadToLocation = false;
            LAi_SetStayType(characterFromID("SanJuan_trader"));
            LAI_SetPlayerType(Pchar);
            AddQuestRecord("Romantic_Line", "4");
			sld = CharacterFromID("Isabella");
			LAi_SetCitizenType(sld);
            sld.dialog.currentnode = "TalkInChurch";
			DoQuestFunctionDelay("SetIsabellaTalker", 4.0);
        break;

        case "Romantic_Battle_in_Bedroom_1":
            sld = CharacterFromID("Husband");
            ChangeCharacterAddressGroup(sld, "SanJuan_houseS1Bedroom", "reload", "reload1");
            LAi_SetActorType(Pchar);
			LAi_SetActorType(sld);
            LAi_ActorFollow(sld, Pchar, "Romantic_Battle_in_Bedroom_2", 3.0);
        break;

        case "Romantic_Battle_in_Bedroom_2":
            sld = CharacterFromID("Husband");
            sld.Dialog.CurrentNode = "Romantic_Battle_in_Bedroom";
            LAi_ActorWaitDialog(Pchar, sld);
		    LAi_ActorDialog(sld, Pchar, "", 2.0, 0);
        break;

        case "Romantic_Battle_in_Bedroom_3":
			pchar.quest.RP_afterVisitBedroom.over = "yes";
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
            LAi_SetPlayerType(pchar);
            ChangeCharacterReputation(pchar, -15);
			sld = CharacterFromID("Husband");
            Lai_SetImmortal(sld, false);
            LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "TmpEnemy");
            LAi_group_SetHearRadius("TmpEnemy", 100.0);
	        LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
	        LAi_group_SetCheck("TmpEnemy", "Romantic_Battle_in_Bedroom_End");
        break;

        case "Romantic_Battle_in_Bedroom_End":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
            sld = CharacterFromID("Isabella");
            sld.Dialog.CurrentNode = "Murder";
            AddQuestRecord("Romantic_Line", "1");
            CloseQuestHeader("Romantic_Line");
			pchar.questdata.IstoriyaIzabely = 1;
        break;

        case "Romantic_Battle_in_Bedroom_4":
            LAi_SetPlayerType(pchar);
            sld = CharacterFromID("Husband");
            LAi_ActorRunToLocation(sld, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto5", "Romantic_Battle_in_Bedroom_5", 2.0);
	        AddQuestRecord("Romantic_Line", "2");
        break;

        case "Romantic_Battle_in_Bedroom_5":
            sld = CharacterFromID("Husband");
            LAi_SetHuberStayType(sld);
	        LAi_SetStayHuberPointWindow(sld, "goto", "goto1");
	        LAi_SetStayHuberPointMap(sld, "goto", "goto2");
        break;
        // церковь
        case "Romantic_TalkInChurch_end":
            sld = CharacterFromID("Isabella");
            LAi_SetStayType(sld);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
        break;
        // разговор с братом в порту куманы -->
        case "Romantic_Brother":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
            Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			sld = GetCharacter(NPC_GenerateCharacter("MigelDeValdes", "citiz_9", "man", "man", 5, SPAIN, -1, true));
            sld.name 	= GetConvertStr("Variable_quests_reaction_0.25", "Names.txt");
	        sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_39", "Names.txt", "#space#", " ");
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
	        sld.dialog.currentnode = "Romantic_Brother_1";
			sld.greeting = "Gr_YoungMan";
            PlaceCharacter(sld, "goto", PChar.location);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.5, 0);
        break;

        case "Romantic_Brother_port":
			chrDisableReloadToLocation = true;
            Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
            sld = CharacterFromID("MigelDeValdes");
	        sld.dialog.currentnode = "Romantic_Brother_port_1";
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            //PlaceCharacter(sld, "goto", PChar.location);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0.5, 0);
        break;
		// --> разговор в доме с братом, сцена 8
        case "Romantic_Brother_House":
            sld = CharacterFromID("Isabella");
            sld.dialog.currentnode = "Brother_1";
            ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto", "goto3");
            LAi_SetActorType(sld);
            sld = CharacterFromID("MigelDeValdes");
            sld.dialog.currentnode = "Romantic_Brother_port_1";
            ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto", "goto4");
            LAi_SetActorType(sld);
			pchar.RomanticQuest = "exitFromDetector";
        break;

        case "Romantic_Brother_House_3":
            // ГГ обратно
            SetMainCharacterIndex(1);
            PChar = GetMainCharacter();
            LAi_SetPlayerType(PChar);
			locCameraTarget(PChar)
            locCameraFollow();
            EndQuestMovie();
            LAi_SetCitizenType(characterFromID("Isabella"));
			sld = characterFromID("MigelDeValdes");
			LAi_SetCitizenType(sld);
			sld.dialog.currentnode = "Romantic_Brother_Thanks";
			sld = characterFromID("Husband");
			sld.dialog.currentnode = "WeWaitYouTonight";
			pchar.RomanticQuest = "DelivMigel"; //флаг "братан доставлен"
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //закрываем двери, чтобы не доставал до поры своим присутствием
        break;
		// --> смерть брата
        case "Romantic_DeadBrother_1":
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			chrDisableReloadToLocation = true;
            SetMainCharacterIndex(1);
            PChar = GetMainCharacter();
            LAi_SetPlayerType(PChar);
			locCameraTarget(PChar)
            locCameraFollow();
			npchar = characterFromID("MigelDeValdes");
			LAi_group_MoveCharacter(npchar, "BrotherGroup");
			sld = characterFromID("Husband");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", "BrotherGroup", LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", "BrotherGroup", true);
			LAi_group_SetCheck("BrotherGroup", "Romantic_DeadBrother_2");
			LAi_LockFightMode(pchar, true); //саблю не достать
			EndQuestMovie();
        break;

		case "Romantic_DeadBrother_2":
			LAi_group_Delete("BrotherGroup");
			sld = characterFromID("Husband");
			sld.dialog.currentnode = "SeenMainHero";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
        break;

		case "Romantic_DeadBrother_3":
			sld = characterFromID("Husband");
			LAi_SetStayType(sld);
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", true); //спальню тоже, а то может быть открыта
			LAi_LocationFightDisable(&Locations[FindLocation("SanJuan_houseSp6")], true);
			// Атиллу поставим в дом на Бермудах для диалога в дальнейшем после ареста
			sld = characterFromID("Atilla");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Pirates_houseF1", "sit", "sit2");
			sld.dialog.currentnode = "TalkingNews";
		break;

		case "Romantic_DeadBrother_Cancel": //если ГГ не явлся к дому Изабеллы в течение суток
			pchar.RomanticQuest = "QuestOver";
			//LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //закрываем дверь в дом Изабеллы
			ChangeCharacterAddress(CharacterFromID("Husband"), "none", "");
			ChangeCharacterAddress(CharacterFromID("MigelDeValdes"), "none", "");
			CloseQuestHeader("Romantic_Line");
			pchar.questdata.IstoriyaIzabely = 1;
		break;
		// --> попытка ареста ГГ
		case "Romantic_ArrestInHouse":
			// Атиллу поставим в дом на Бермудах для диалога в дальнейшем после ареста
			sld = characterFromID("Atilla");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Pirates_houseF1", "sit", "sit2");
			sld.dialog.currentnode = "TalkingNews";
			//Сальватор убегает на выход
			npchar = characterFromID("Husband");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "SanJuan_houseS1Bedroom", "goto", "goto3", "", 5.0);
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //опять закрываем, чтобы ГГ до поры не ломился в дом
			//Команда на арест ГГ
			iTemp = FindColony("SanJuan");
			sTemp = NationShortName(sti(colonies[iTemp].nation));
            for (i=1; i<=3; i++)
            {
				if (i==1)
				{
					if (sti(colonies[iTemp].HeroOwn))
					{
						Model = "officer_18";
					}
					else
					{
						Model = "off_" + sTemp + "_1";
					}
					Rank = sti(pchar.rank)+ MOD_SKILL_ENEMY_RATE*3 + 6;
					Blade = "blade20";
				}
				else
				{
					if (sti(colonies[iTemp].HeroOwn))
					{
						Model = "pirate_" + i;
					}
					else
					{
						Model = "sold_" + sTemp + "_" +(rand(7)+1);
					}
					Rank = sti(pchar.rank)+ MOD_SKILL_ENEMY_RATE*3 + 2;
					Blade = "blade24";
				}
				sld = GetCharacter(NPC_GenerateCharacter("Soldier_"+i, Model, "man", "man", Rank, sti(colonies[iTemp].nation), 0, true));
				FantomMakeCoolFighter(sld, Rank, (80 + round(4 * MOD_SKILL_ENEMY_RATE*3 / 2)), (70 + round(4 * MOD_SKILL_ENEMY_RATE*3 / 2)), Blade, "pistol5", (140 + round(10 * MOD_SKILL_ENEMY_RATE*3 / 2)));
				sld.City = colonies[iTemp].id;
				sld.CityType = "soldier";
				sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
				sld.dialog.currentnode = "ArrestInHome_2";
				LAi_SetWarriorType(sld);
				if (i == 1) {LAi_ActorDialog(sld, pchar, "", 1.5, 0); LAi_SetActorTypeNoGroup(sld);}
				LAi_group_MoveCharacter(sld, GetNationNameByType(sti(colonies[iTemp].nation)) + "_citizens");
				ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "reload", "reload1");
			}
        break;
		//через два месяца Алиллу - в дом
		case "Romantic_AtillaToHouse":
			sld = characterFromID("Atilla");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Pirates_houseF1", "sit", "sit2");
			sld.dialog.currentnode =  "AtillaInHouse";
        break;
		//засада в доме Сальватора в Сан-Хуане
		case "Romantic_AmbushInHouse":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_115", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
			LAi_LocationFightDisable(&locations[FindLocation("SanJuan_houseSp6")], true);
            LAi_group_Delete("EnemyFight");
			for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "officer_"+(i+10), "man", "man", 25, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 25, 70, 60, BLADE_LONG, "pistol2", 20);
            	LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto",  "goto"+i);
            }
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "AmbushBandit";
			LAi_CharacterEnableDialog(sld);
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		//атака брига с Изабеллой
        case "Romantic_BrigTimeOver":
			Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_116", "Logs.txt", "#space#", " "));
            pchar.quest.Romantic_AttackBrig.over = "yes";
            AddQuestRecord("Romantic_Line", "14");
            QuestSetCurrentNode("Atilla", "Brig_Late"); //нода Атилле на опаздал
        break;

        case "Romantic_AttackBrig":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_117", "Logs.txt", "#space#", " "));
            pchar.quest.Romantic_BrigTimeOver.over = "yes";
            Island_SetReloadEnableGlobal("PortoBello", false);
    		Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "trade");
            sld = GetCharacter(NPC_GenerateCharacter("IsaAttackCap", "officer_14", "man", "man", 20, PIRATE, 0, true));
            sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "BrigAbordage";
            FantomMakeCoolSailor(sld, SHIP_BRIG, GetConvertStr("Variable_quests_reaction_8", "ShipNames.txt"), CANNON_TYPE_CULVERINE_LBS24, 70, 70, 70);
            FantomMakeCoolFighter(sld, 20, 70, 50, "blade24", "pistol3", 20);
			sld.DontRansackCaptain = true;
			Group_AddCharacter("Pirate_Attack", "IsaAttackCap");
            // ==> стравливание
			Group_SetGroupCommander("Pirate_Attack", "IsaAttackCap");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "PortoBello", "", "");
			Group_LockTask("Pirate_Attack");
            // ==> прерывания
			pchar.quest.Romantic_AfterBrigSunk.win_condition.l1 = "Character_sink";
			pchar.quest.Romantic_AfterBrigSunk.win_condition.l1.character = "IsaAttackCap";
			pchar.quest.Romantic_AfterBrigSunk.win_condition = "Romantic_AfterBrigSunk";
			pchar.quest.Romantic_BrigDieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Romantic_BrigDieHard.win_condition = "Romantic_BrigDieHard";
        break;

        case "Romantic_BrigDieHard":
            pchar.quest.Romantic_AfterBrigSunk.over = "yes";
            group_DeleteGroup("Pirate_Attack");
            Island_SetReloadEnableGlobal("PortoBello", true);
            AddQuestRecord("Romantic_Line", "16");
            QuestSetCurrentNode("Atilla", "Brig_DieHard"); //нода Атилле на бриг ушёл от погони
        break;

        case "Romantic_AfterBrigSunk":
            pchar.quest.Romantic_BrigDieHard.over = "yes";
            Island_SetReloadEnableGlobal("PortoBello", true);
            group_DeleteGroup("Pirate_Attack");
            AddQuestRecord("Romantic_Line", "15");
            QuestSetCurrentNode("Atilla", "Brig_Sunk"); //нода Атилле бриг утонул
        break;

        case "Romantic_TaklInCabinBrig":
			sld = characterFromID("Isabella");
			sld.dialog.currentnode = "BrigAbordage";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
        break;
		//засада в Порто Белло
		case "Romantic_AmbushInPortoBello":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_118", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
			LAi_LocationFightDisable(&locations[FindLocation("PortoBello_houseF2")], true);
			LAi_group_Delete("EnemyFight");
            for (i=4; i<=5; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "officer_"+i, "man", "man", 30, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 30, 80, 70, "topor2", "pistol3", 40);
            	LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "PortoBello_houseF2", "goto",  "goto"+i);
            }
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "AmbushPotroBello";
			LAi_CharacterEnableDialog(sld);
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

		case "Romantic_TalkPortoBello":
			chrDisableReloadToLocation = false;
            sld = CharacterFromID("Isabella");
	        sld.dialog.currentnode = "AmbushPortoBello";
            ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 1.5);
        break;
		//базар с Изабеллой у дома Роситы
        case "Romantic_BelizCityTalk":
			chrDisableReloadToLocation = true;
            Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
            sld = CharacterFromID("Isabella");
	        sld.dialog.currentnode = "BelizTalk";
            ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto17");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0.0);
        break;
		//смерть охранника Изабеллы в пещере
        case "Romantic_BanditIsDead":
            sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0.0);
        break;
		//Сальватор в пещере
        case "Romantic_SalvatorInCave":
			LAi_LockFightMode(pchar, true); //саблю не достать
            sld = CharacterFromID("Husband");
	        sld.dialog.currentnode = "TalkInCave";
			sld.items.jewelry5 = 100;
			sld.items.jewelry13 = 7;
			sld.items.jewelry14 = 6;
			sld.items.jewelry15 = 5;
			sld.items.jewelry17 = 30;
			sld.items.jewelry18 = 12;
			sld.items.indian1 = 1;
			sld.items.indian5 = 1;
			sld.items.indian6 = 1;
			sld.items.indian10 = 2;
			sld.items.indian12 = 1;
			sld.items.indian14 = 1;
			sld.items.jewelry12 = 12;
			sld.items.jewelry11 = 6;
			sld.items.jewelry10 = 20;
			sld.items.jewelry7 = 21;
			sld.items.jewelry6 = 11;
			sld.items.jewelry4 = 7;
			sld.items.jewelry3 = 15;
			sld.items.jewelry2 = 18;
			sld.items.jewelry1 = 31;
			sld.money = 350535;
			Lai_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto7");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "Romantic_SalvatorIsDead":
			LAi_LocationDisableOfficersGen("Beliz_Cave_2", false); //офицеров пускать
			LAi_LocationDisableMonstersGen("Beliz_Cave_2", false); //монстров генерить
			QuestSetCurrentNode("Isabella", "SalvatorIsDead");
            sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0.0);
        break;

		// --> разговор Изабеллы с Роситой в доме после освобождения Изабеллы
        case "Romantic_DelivToRosita":
			if (GetCharacterIndex("Isabella") == -1)
			{
				QuestSetCurrentNode("Rosita", "IsabellaIsDead_Beliz");
			}
			else
			{
				pchar.RomanticQuest = "Beliz_exitFromDetector";
				QuestSetCurrentNode("Rosita", "SavedIsabella");
			}
        break;

        case "Romantic_DelivToRosita_2":
            // ГГ обратно
            SetMainCharacterIndex(1);
            PChar = GetMainCharacter();
            LAi_SetPlayerType(PChar);
			locCameraTarget(PChar)
            locCameraFollow();
            EndQuestMovie();
            LAi_SetCitizenType(characterFromID("Rosita"));
			sld = characterFromID("Isabella");
			LAi_SetCitizenType(sld);
			sld.dialog.currentnode = "RositaHouse";
			//через месяц Изабеллу - в Сан-Хуан
			SetTimerCondition("Romantic_IsabellaToSanJuan", 0, 1, 0, false);
        break;

        case "Romantic_IsabellaToSanJuan":
			sld = CharacterFromID("Isabella");
			ChangeCharacterAddressGroup(sld , "SanJuan_houseSp6", "goto",  "goto1");
			sld.dialog.currentnode = "InSanJuanAgain";
        break;

        case "Romantic_OutFromHouse":
			DoReloadCharacterToLocation("SanJuan_town", "reload", "houseSp6");
        break;

		case "Romantic_Widding_Cancel": //если ГГ не явлся к в церковь для венчания в течение суток
			pchar.quest.Isabella_widding.over = "yes";
			pchar.RomanticQuest = "QuestOver";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false); //открываем дом
			sld = characterFromID("Isabella");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "Cancel_Widding";
			ChangeCharacterAddressGroup(sld , "SanJuan_houseSp6", "goto",  "goto1");
			sld = CharacterFromID("SanJuan_Priest");
			LAi_SetPriestType(sld);
		break;
		//свадьба Изабеллы и ГГ. Шампанского!!!!!
        case "Romantic_Padre":
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "barmen", "stay");
			DoQuestCheckDelay("Romantic_Padre_1", 1.0);
        break;

        case "Romantic_Padre_1":
            SetLaunchFrameFormParam(GetConvertStr("Variable_quests_reaction_3", "Frames.txt"), "Romantic_Padre_2", 0, 3);
            LaunchFrameForm();
            WaitDate("", 0, 0, 0, 0, 40);
        	RecalculateJumpTable();
        break;

        case "Romantic_Padre_2":
			StartQuestMovie(true, true, true);
			locCameraToPos(-1.52, 3.25, -3.36, false);
			sld = CharacterFromID("SanJuan_Priest");
			sld.dialog.currentnode = "Romantic_2";
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar("SanJuan_Priest", "", 0.0, 0.0);
		    LAi_ActorFollow(PChar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;

        case "Romantic_Padre_3":
            LAi_SetPlayerType(PChar);
			locCameraTarget(PChar)
            locCameraFollow();
            EndQuestMovie();
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			DoQuestCheckDelay("Romantic_fightInChurch", 2.0);
        break;
		//Нападение бандитов в церкви
        case "Romantic_fightInChurch":
            Log_QuestInfo(GetConvertStrWithReplace("Variable_quests_reaction_119", "Logs.txt", "#space#", " "));
            chrDisableReloadToLocation = true; // закрыть выход из локации.
			LAi_group_Delete("EnemyFight");
			iTemp = sti(2+(MOD_SKILL_ENEMY_RATE*3/1.5));
			Rank = 10+MOD_SKILL_ENEMY_RATE*3*2;
            for (i=1; i<=iTemp; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "officer_"+(i+3), "man", "man", Rank, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, Rank, 80, 70, "topor2", "pistol1", 40);
				sld.equip.gun = "";
            	LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
            	sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "SanJuan_church", "reload",  "reload1");
            }
			sld.dialog.currentnode = "AmbushInChurch";
            LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
        break;

		case "Romantic_fightInChurch_1":
			sld = characterFromID("Isabella");
 			sld.dialog.currentnode = "AmbushInChurch";
            LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

		case "Romantic_fightInChurch_2":
			LAi_LocationFightDisable(loadedLocation, false);
			//падре в сторону
			sld = characterFromID("SanJuan_Priest");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "barmen", "bar2", "", -1);
			//деремся
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("EnemyFight", "SPAIN_CITIZENS", LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Romantic_afterFightInChurch");
			//Изабелла в сторону
			sld = characterFromID("Isabella");
			//LAi_SetImmortal(sld, false); // для тестов
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			GiveItem2Character(sld, "unarmed");
			EquipCharacterbyItem(sld, "unarmed");
			LAi_SetFightMode(sld, false);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorRunToLocator(sld, "barmen", "bar1", "", -1);
        break;

		case "Romantic_afterFightInChurch":
            chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(loadedLocation, true);
			sld = CharacterFromID("SanJuan_Priest");
			LAi_SetPriestType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld = CharacterFromID("Isabella");
			if (LAi_IsDead(sld))
			{
				AddQuestRecord("Romantic_Line", "25");
				pchar.RomanticQuest = "IsabellaIsDead";
				QuestSetCurrentNode("Atilla", "IsabellaIsDead");
				QuestSetCurrentNode("Rosita", "IsabellaIsDead");
			}
			else
			{
				AddQuestRecord("Romantic_Line", "26");
				pchar.RomanticQuest = "IsabellaIsMyWife";
				QuestSetCurrentNode("Atilla", "IsabellaIsMyWife");
				QuestSetCurrentNode("Rosita", "IsabellaIsMyWife");
				LAi_SetCitizenType(CharacterFromID("Isabella"));
				QuestSetCurrentNode("Isabella", "IsabellaIsMyWife");
			}
        break;
		//новая сеймейная жизнь.
		case "Romantic_afterFirstTime":
			SaveCurrentQuestDateParam("RomanticQuest");
			IsabellaSetCurrentState("all");  //запомнинаем текущую статистику
			IsabellaCheckBreachState(); //тут же проверяем для обращений сразу же
			pchar.RomanticQuest.HorseCheck = pchar.questTemp.HorseQty; //запоминаем текущее кол-во посещения борделей
			IsabellaNullBudget(); //нулим семейный бюджет
			sld = CharacterFromID("Isabella");
			sld.greeting = "Gr_Isabella_1";
			SaveCurrentNpcQuestDateParam(sld, "sex"); //запомниаем последний секс
			sld.sex.control_year = sti(sld.sex.control_year) - 1; //-1 год (для первого раза)
			QuestSetCurrentNode("Rosita", "IsabellaIsWife"); //Росите ноду, по которой она помогать будет с проблемами
			pchar.RomanticQuest = "NewLifeForHero";
			AddQuestRecord("Romantic_Line", "28");
			AddQuestUserData("Romantic_Line", "IsabellaBuget", FindRussianMoneyString(MOD_SKILL_ENEMY_RATE*3*10000));
			//прерывание на вход в дом Изабеллы
			Pchar.quest.Romantic_OutHome.win_condition.l1 = "location";
			Pchar.quest.Romantic_OutHome.win_condition.l1.location = "PuertoRico";
			Pchar.quest.Romantic_OutHome.win_condition = "Romantic_OutHome";
		break;
		//запускаем проверку на пиратские делишки на входе в дом
		case "Romantic_EnterHome":
			if (CheckAttribute(pchar, "RomanticQuest.State"))
			{
				IsabellaCheckBreachState();
				pchar.RomanticQuest.Cheking = "";
				QuestSetCurrentNode("Isabella", "NewLife_hello");
				Pchar.quest.Romantic_OutHome.win_condition.l1 = "location";
				Pchar.quest.Romantic_OutHome.win_condition.l1.location = "PuertoRico";
				Pchar.quest.Romantic_OutHome.win_condition = "Romantic_OutHome";
			}
		break;

		case "Romantic_OutHome":
			if (CheckAttribute(pchar, "RomanticQuest.State"))
			{
				pchar.RomanticQuest = "NewLifeForHero";     //для проверки сроков отсутсвия на детекторе итем
				SaveCurrentQuestDateParam("RomanticQuest"); //эти самые сроки и запомним
				Pchar.quest.Romantic_EnterHome.win_condition.l1 = "location";
				Pchar.quest.Romantic_EnterHome.win_condition.l1.location = "SanJuan_houseSp6";
				Pchar.quest.Romantic_EnterHome.win_condition = "Romantic_EnterHome";
			}
		break;
		//сам секс собсно.
		case "Romantic_Sex":
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			if (GetNpcQuestPastMinutesParam(sld, "sex") > 10)
			{
				QuestSetCurrentNode("Isabella", "NewLife_Sex_Late");
				LAi_ActorDialog(sld, pchar, "", 1.0, 0);
			}
			else
			{
				DoQuestCheckDelay("PlaySex_1", 3.0);
			}
		break;

		case "PlaySex_1":
			ResetSound();
			iTemp = rand(13)+1;
			switch (iTemp)
			{
				case 1: fTemp = 18.2; break;
				case 2: fTemp = 5.1;  break;
				case 3: fTemp = 19.3; break;
				case 4: fTemp = 8.2;  break;
				case 5: fTemp = 11.3; break;
				case 6: fTemp = 18.2; break;
				case 7: fTemp = 18.2; break;
				case 8: fTemp = 9.3;  break;
				case 9: fTemp = 19.4; break;
				case 10:fTemp = 12.2; break;
				case 11:fTemp = 19.4; break;
				case 12:fTemp = 12.3; break;
				case 13:fTemp = 10.2; break;
				case 14:fTemp = 11.2; break;
			}
			sGlobalTemp = iTemp;
			//LAi_FadeDelay(fTemp, "loading\inside\censored1.tga");
			//StartPictureAsVideo( "loading\inside\censored1.tga", fTemp );
			SetLaunchFrameFormParam("", "", 0, fTemp);
			SetLaunchFrameFormPic("loading\jonny_load\inside\censored1.tga");
            LaunchFrameForm();
			DoQuestCheckDelay("PlaySex_2", 1.0);
		break;

		case "PlaySex_2":
			PlayStereoSound("sex\sex" + sGlobalTemp + ".wav");
            AddTimeToCurrent(2, rand(30));
			if (pchar.location == "SanJuan_houseS1Bedroom")
			{
			    QuestSetCurrentNode("Isabella", "NewLife_afterSex");
			    LAi_SetStayType(CharacterFromID("Isabella"));
			}
			//квест официантки
			if (pchar.questTemp.different == "FackWaitress_facking")
			{
				sld = characterFromId("WairessQuest");
				ChangeCharacterAddress(sld, "none", "");
				AddCharacterExpToSkill(pchar, "Loyality", 20);
				AddCharacterHealth(pchar, 3);
            	AddCharacterExpToSkill(pchar, "Fencing", -15);
            	AddCharacterExpToSkill(pchar, "Pistol", -15);
				ChangeCharacterReputation(pchar, -1);
				if (sti(pchar.questTemp.different.FackWaitress.Kick) != 1)
				{
					SetTimerFunction("WaitressFack_null", 0, 0, 1);
					pchar.questTemp.different = "FackWaitress_fackNoMoney";
					AddCharacterExpToSkill(pchar, "Fortune", 100);
				}
				pchar.money = sti(pchar.money) / sti(pchar.questTemp.different.FackWaitress.Kick);
				chrDisableReloadToLocation = false;
			}
			//квест развода хозяйки борделя
			if (pchar.questTemp.different == "HostessSex" && CheckAttribute(pchar, "questTemp.different.HostessSex.city"))
			{
				sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
				ChangeCharacterAddressGroup(sld, pchar.questTemp.different.HostessSex.city + "_SecBrRoom", "goto", "goto8");
				LAi_SetOwnerTypeNoGroup(sld);
				DeleteAttribute(pchar, "questTemp.different.HostessSex");
				pchar.questTemp.different = "free";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "EncGirl_facking")
			{
				sld = characterFromId("CangGirl");
				ChangeCharacterAddress(sld, "none", "");
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Loyality", 20);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
            	AddCharacterExpToSkill(pchar, "Fencing", -20);
            	AddCharacterExpToSkill(pchar, "Pistol", -20);
				AddCharacterHealth(pchar, 5);
				ChangeCharacterReputation(pchar, -1);
				pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/15);
				chrDisableReloadToLocation = false;
				SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
			}
		break;

		case "Romantic_IsabellaBackToHall":
			Pchar.quest.Romantic_Sex.over = "yes";
            sld = CharacterFromID("Isabella");
            LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto",  "goto1");
			QuestSetCurrentNode("Isabella", "NewLife");
		break;

		case "sleep_in_home":
			DoQuestReloadToLocation("SanJuan_houseS1Bedroom", "goto", "goto4", "restore_hp");
		break;

/////////////////////////////////////   Изабелла конец   //////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Квест Аскольда начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
			int iCannonType, iShipType;
			string sShipName;
        case "Ascold_AttackTenManowars":
			LocatorReloadEnterDisable("Tenotchitlan_Jungle_02", "reload3_back", true); //закроем до поры храм
			Island_SetReloadEnableGlobal("Caiman", false);
            pchar.questTemp.Ascold = "ILookedThisAss";
            // ==> корабль, куда помещаем предметы
            i = rand(5)+1;
            pchar.questTemp.Ascold.Ship = "AscoldCaptainAttack_" + i;
			Log_QuestInfo("Журнал в мановаре с ID кэпа: " + pchar.questTemp.Ascold.Ship);
            // ==> меняем дейскрайб судового журнала
            ChangeItemDescribe("ShipsJournal", "itmdescr_ShipsJournal_Ascold");
    		Group_FindOrCreateGroup("Ascold_Spa_Attack");
			Group_SetType("Ascold_Spa_Attack", "war");
            // ==> Испанские кэпы
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			int rat_counter = 0;
			for (i = 1; i <=6; i++)
			{
				Rank = 30 + rand(5);
				sTemp = "AscoldCaptainAttack_"+i;
				switch (i)
				{
					case 1:
						iCannonType = CANNON_TYPE_CANNON_LBS42;
						iShipType = SHIP_SANTISIMA;
						sShipName = GetConvertStrWithReplace("Variable_quests_reaction_40", "Names.txt", "#space#", " ");
						Blade = "blade20";
					break;
					case 2:
						iCannonType = CANNON_TYPE_CANNON_LBS32;
						iShipType = SHIP_PAVEL;
						sShipName = "";
						Blade = "topor2";
					break;
					case 3:
						iCannonType = CANNON_TYPE_CULVERINE_LBS32;
						iShipType = SHIP_RATTVISAN;
						sShipName = "";
						Blade = "blade15";
					break;
					case 4:
						iCannonType = CANNON_TYPE_CANNON_LBS32;
						iShipType = SHIP_SANTIAGO;
						sShipName = "";
						Blade = "blade31";
					break;
					case 5:
						iCannonType = CANNON_TYPE_CANNON_LBS32;
						iShipType = SHIP_CECILIA;
						sShipName = "";
						Blade = "blade21";
					break;
					case 6:
						iCannonType = CANNON_TYPE_CANNON_LBS32;
						iShipType = SHIP_FELIPE;
						sShipName = "";
						Blade = "blade34";
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter(sTemp, "off_spa_"+(rand(1)+1), "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolSailor(sld, iShipType, sShipName, iCannonType, 90, 90, 90);
				FantomMakeCoolFighter(sld, Rank, 90, 90, Blade, "pistol3", 100);
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.SuperShooter  = true;
				sld.ship.Crew.Morale = 100;
				ChangeCrewExp(sld, "Sailors", 100);
				ChangeCrewExp(sld, "Cannoners", 100);
				ChangeCrewExp(sld, "Soldiers", 90);
				SetRandGeraldSail(sld, sti(sld.Nation));
				Group_AddCharacter("Ascold_Spa_Attack", sTemp);
				if (sTemp == pchar.questTemp.Ascold.Ship)
				{
					pchar.questTemp.Ascold.ShipType = RealShips[sti(sld.Ship.Type)].BaseName;
					pchar.questTemp.Ascold.ShipName = sld.Ship.name;
				}
				if (rat_counter < 3 && sTemp != pchar.questTemp.Ascold.Ship)
				{
					if (1>rand(1) || 5-i < 3-rat_counter)
					{
						sld.Ascold.ratmark = true;
						rat_counter++;
					}
				}
			}
			if (CheckAttribute(pchar, "questTemp.Ascold.IKnowTheShip"))
			{
				AddQuestRecord("Ascold", "7_2");
				AddQuestUserData("Ascold", "ShipType", GetStrSmallRegister(XI_ConvertString(pchar.questTemp.Ascold.ShipType)));
				AddQuestUserData("Ascold", "ShipName", pchar.questTemp.Ascold.ShipName);
			}
			// ==> стравливание
			Group_SetGroupCommander("Ascold_Spa_Attack", "AscoldCaptainAttack_1");
			//Group_SetPursuitGroup("Ascold_Spa_Attack", PLAYER_GROUP); //TO_DO
			Group_SetAddress("Ascold_Spa_Attack", "Caiman", "quest_ships", "quest_ship_6");
			Group_SetTaskAttack("Ascold_Spa_Attack", PLAYER_GROUP);
			Group_LockTask("Ascold_Spa_Attack");
            // ==> прерывание на убиение эскадры
            pchar.quest.Ascold_VictoryManowar.win_condition.l1 = "Group_Death";
			pchar.quest.Ascold_VictoryManowar.win_condition.l1.group = "Ascold_Spa_Attack";
			pchar.quest.Ascold_VictoryManowar.win_condition = "Ascold_VictoryManowar";
			pchar.quest.Ascold_DieHardManowar.win_condition.l1 = "MapEnter";
			pchar.quest.Ascold_DieHardManowar.win_condition = "Ascold_DieHardManowar";
			//SetTimerCondition("Ascold_ManowarRepair", 0, 0, 10, true);
        break;

        case "Ascold_VictoryManowar":
			//PChar.quest.Ascold_ManowarRepair.over = "yes";
			LocatorReloadEnterDisable("Tenotchitlan_Jungle_02", "reload3_back", false); //откроем храм
			Island_SetReloadEnableGlobal("Caiman", true);
            group_DeleteGroup("Ascold_Spa_Attack");
			pchar.quest.Ascold_DieHardManowar.over = "yes";
            pchar.questTemp.Ascold = "Ascold_ManowarsDead";
			DeleteAttribute(PChar, "questTemp.Ascold.IKnowTheShip");
            DeleteAttribute(PChar, "questTemp.Ascold.Ship");
			DeleteAttribute(PChar, "questTemp.Ascold.ShipType");
			DeleteAttribute(PChar, "questTemp.Ascold.ShipName");
			DeleteAttribute(PChar, "questTemp.Ascold.SpainCapitainDialogue");
			DeleteAttribute(PChar, "questTemp.Ascold.Ship.foundcheck");
            AddQuestRecord("Ascold", "9");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("","а"));
            Pchar.quest.Ascold_FightNearTemple.win_condition.l1 = "location";
            Pchar.quest.Ascold_FightNearTemple.win_condition.l1.location = "Temple";
            Pchar.quest.Ascold_FightNearTemple.win_condition = "Ascold_FightNearTemple";
        break;

		case "Ascold_DieHardManowar":
            Island_SetReloadEnableGlobal("Caiman", true);
            group_DeleteGroup("Ascold_Spa_Attack");
			pchar.quest.Ascold_VictoryManowar.over = "yes";
            pchar.questTemp.Ascold = "Ascold_ManowarsNoDead";
			DeleteAttribute(PChar, "questTemp.Ascold.Ship");
            AddQuestRecord("Ascold", "9_1");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("","а"));
        break;
/*
        case "Ascold_ManowarRepair": //ремонт мановаров
			if (pchar.location != "Beliz")
			{
				for (i=1; i<=10; i++)
				{
					iTemp = GetCharacterIndex("AscoldCaptainAttack_" + i);
					if (iTemp != -1)
					{
						sld = &characters[iTemp];
						SetCrewQuantityFull(sld);
						DeleteAttribute(sld, "ship.sails");// убрать дыры на парусах
						DeleteAttribute(sld, "ship.blots");
						RepairMasts(sld);// вернуть сбитые мачты
						SetBaseShipData(sld);
					}
				}
			}
        break;
*/
        case "Ascold_FightNearTemple":
            chrDisableReloadToLocation = true; // закрыть выход из локации
			LAi_group_Delete("EnemyFight");
            for (i=1; i<=20; i++)
            {
                if (i==1 || i==8 || i==11 || i==15)
                {
					sld = GetCharacter(NPC_GenerateCharacter("Enemy_"+i, "off_spa_"+(rand(1)+1), "man", "man", 25, SPAIN, 0, true));
					FantomMakeCoolFighter(sld, 25, 80, 80, BLADE_LONG, "pistol5", 100);
                }
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Enemy_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 20, SPAIN, 0, true));
					FantomMakeCoolFighter(sld, 20, 50, 50, BLADE_LONG, "pistol3", 40);
				}
            	LAi_SetWarriorType(sld);
				if (i < 16) LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Temple", "goto",  "goto"+i);
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            //LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Ascold_WinNearTemple");
        break;

        case "Ascold_WinNearTemple":
            chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(pchar.location, "reload2", false);
            AddQuestRecord("Ascold", "14");
			pchar.quest.Ascold_fightInsideTemple.win_condition.l1 = "location";
			pchar.quest.Ascold_fightInsideTemple.win_condition.l1.location = "Temple_Inside";
			pchar.quest.Ascold_fightInsideTemple.function = "Ascold_fightInsideTemple";
        break;

        case "Ascold_InGraveAfterFight":
			pchar.questTemp.Ascold = "Ascold_MummyIsLive";
		    LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], true);
			if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("LeifEricson", "Mummy", "skeleton", "man_fast", 100, PIRATE, -1, true)); // LEO: Превозмогаторам страдать 08.12.2021
			else sld = GetCharacter(NPC_GenerateCharacter("LeifEricson", "Mummy", "skeleton", "man", 100, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 100, 100, 100, "blade28", "", 3000);
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_41", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_42", "Names.txt", "#space#", " ");
			if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
			sld.Dialog.Filename = "Quest\LeifEricson.c";
            sld.SaveItemsForDead = true; // сохранять на трупе вещи
			GiveItem2Character(sld, "Azzy_bottle");
            sld.DontClearDead = true; // не убирать труп через 200с
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "locator1");
			LAi_SetImmortal(sld, true);
			LAi_CharacterPlaySound(sld, "Gr_LeifEricson");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar("LeifEricson", "", -1, 0.0);
		    LAi_ActorFollow(PChar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;

        case "Ascold_MummyFightTown":
            for (i=1; i<=6; i++)
            {
				sld = characterFromId("MySkel"+i);
				sld.LifeDay = 0;
				ChangeCharacterAddress(sld, "none", "");
            }
    	    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
    	    DeleteQuestAttribute("Union_with_Escadra");
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            SetLocationCapturedState("BasTer_town", true);
            DoQuestCheckDelay("Capture_Forts", 0.5);
            Ship_NationAgressive(sld, sld);
            Log_SetStringToLog(GetConvertStr("Variable_quests_reaction_Leif", "Logs.txt"));
			characters[GetCharacterIndex("BasTer_Mayor")].dialog.captureNode = "Ascold_MummyAttack"; //капитулянтская нода мэра
        break;

        case "Ascold_AzzyIsFree":
  		    LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], true);
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Azzy")], "Shore28", "goto", "goto25");
            DoReloadCharacterToLocation("Shore28","goto","goto24");
            DoQuestCheckDelay("Azzy_IsFree", 4.0);
        break;

        case "Azzy_IsFree":
            LAi_SetActorType(PChar);
            sld = characterFromID("Azzy");
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
		break;

		case "Azzy_PlusSkill":
            DeleteAttribute(pchar, "questTemp.Azzy.AddSpecial");
            // boal оптимизация скилов -->
            DelBakSkillAttr(pchar);
            ClearCharacterExpRate(pchar);
            RefreshCharacterSkillExpRate(pchar);
            // boal оптимизация скилов <--
        	WaitDate("",0,0,2,0,1);
        	RecalculateJumpTable();
        	StoreDayUpdate();
			SetLaunchFrameFormParam(GetConvertStr("Variable_quests_reaction_4", "Frames.txt"), "", 0, 4);
			LaunchFrameForm();
            //DoReloadCharacterToLocation("Tortuga_town", "reload", "reload91");
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Квест Аскольда-Аззи конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Пиратская линейка     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "PiratesLine_toTavern":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			FreeSitLocator("PuertoPrincipe_tavern", "sit2");
			DoQuestReloadToLocation("PuertoPrincipe_tavern", "sit", "sit2", "");
			sld = characterFromID("QuestPirate1");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;

		case "PiratesLine_q1_MorganGoTo":
            sld = characterFromID("Henry Morgan");
			sld.Dialog.CurrentNode = "PL_Q1_1";
            LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

		case "PQ5_Morgan_2":
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Henry Morgan"));
			sld = characterFromID("CapGoodly");
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto1", "PQ5_Morgan_3", -1.0);
		break;

		case "PQ5_Morgan_3":
			SetMainCharacterIndex(GetCharacterIndex("CapGoodly"));
			PChar   = GetMainCharacter();
			locCameraToPos(2.49, 2.65, -11.076, false);
			LAi_SetActorType(PChar);
			LAi_ActorDialog(PChar, characterFromID("Henry Morgan"), "", 0, 0);
		break;

		case "PQ6_afterBattle":
			//убираем Джона Лидса
			chrDisableReloadToLocation = false;
			group_DeleteGroup("LidsGroup");
			LocatorReloadEnterDisable("Shore7", "boat", false); //откроем выход в море
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "4");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase("уничтожил своего 'родственничка', похож он был на меня очень сильно. Кто он, откуда, чем занимался","уничтожила свою 'сестричку', похожа она была на меня очень сильно. Кто она, откуда, чем занималась"));
			pchar.questTemp.piratesLine = "PL_Q6_AfterBattle";
		break;


/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Пиратская линейка     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

		case "CitizSeekCap_afterCabinFight":
		    //#20191003-01
            LAi_group_SetAlarm(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, 0.0);
			sld = GetCharacter(NPC_GenerateCharacter(pchar.GenQuest.CitizSeekCap.label + "_" + pchar.GenQuest.CitizSeekCap.WifeCity, pchar.GenQuest.CitizSeekCap.model, pchar.GenQuest.CitizSeekCap.sex, pchar.GenQuest.CitizSeekCap.ani, 5, pchar.GenQuest.CitizSeekCap.nation, -1, false));
			sld.name = pchar.GenQuest.CitizSeekCap.WifeName;
			sld.lastname = pchar.GenQuest.CitizSeekCap.WifeLastname;
			sld.dialog.filename   = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = pchar.GenQuest.CitizSeekCap.label + "_Board";
			sld.quest.SeekCap = pchar.GenQuest.CitizSeekCap.label;
			sld.quest.cribCity = pchar.GenQuest.CitizSeekCap.WifeCity;
			DeleteAttribute(pchar, "GenQuest.CitizSeekCap");
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;

		case "PQ8_jungle_afterFight":
			chrDisableReloadToLocation = false;
			pchar.questTemp.piratesLine = "Panama_inJungleIsOver";
			iTemp = GetCharacterIndex("Richard_Soukins");
			if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
			{
				sld = &characters[iTemp];
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
				for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
				{
					iTemp = GetCharacterIndex("RSpirate_"+i);
					if(iTemp != -1)
					{
						LAi_group_MoveCharacter(&characters[iTemp], sld.chr_ai.group);
					}
				}
				for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
				{
					iTemp = GetCharacterIndex("RSmush_"+i);
					if(iTemp != -1)
					{
						LAi_group_MoveCharacter(&characters[iTemp], sld.chr_ai.group);
					}
				}
				for (i=1; i<=3; i++)
				{
					iTemp = GetCharacterIndex("RSofficer_"+i);
					if(iTemp != -1)
					{
						LAi_group_MoveCharacter(&characters[iTemp], sld.chr_ai.group);
					}
				}
			}
		break;

		case "PQ8_ExitTown_afterFight":
			LocatorReloadEnterDisable("Shore48", "boat", false); //откроем выход из бухты
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", false); //открываем подходы к Панаме
			SetLocationCapturedState("Panama_town", true); //убираем всех из города
			sld = characterFromId("Henry Morgan");
			sld.dialog.currentNode = "PL_Q8_ExTPanama";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "NarvalDestroyed":
			chrDisableReloadToLocation = false;
			pchar.questTemp.LSC = "NarvalDestroyed";
			AddQuestRecord("ISS_MainLine", "13");
			int idxMent;
			string sOffName;
			for (i=1 ; i<=3; i++)
			{
				idxMent = GetCharacterIndex("Ment_" + i);
				if (idxMent != -1)
				{
					characters[idxMent].Dialog.CurrentNode = "AffterFightN";
					LAi_SetWarriorType(&characters[idxMent]);
					LAi_group_MoveCharacter(&characters[idxMent], LAI_GROUP_PLAYER_OWN);
				}
			}
			pchar.quest.NavalExitVelasco.win_condition.l1 = "ExitFromLocation";
			pchar.quest.NavalExitVelasco.win_condition.l1.location = pchar.location;
			pchar.quest.NavalExitVelasco.function = "NavalExitVelasco";
		break;

		case "LSC_EnterComplite_1":
			sld = characterFromId("LSCMayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "stay1");
			LAi_SetStayType(sld);
			sld = characterFromId("Casper_head");
			if (sld.chr_ai.type == LAI_TYPE_STAY)
			{
 				StartQuestMovie(true, true, true);
				SetMainCharacterIndex(GetCharacterIndex("Casper_head"));
				PChar   = GetMainCharacter();
				locCameraToPos(77.3, 8.65, -30.9, false);
				LAi_SetActorType(PChar);
				LAi_ActorDialog(PChar, characterFromID("LSCMayor"), "", 0, 0);
			}
		break;

		case "LSC_EnterComplite_2":
			sld = characterFromId("Casper_head");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "stay2");
			LAi_SetStayType(sld);
			sld = characterFromId("LSCMayor");
			if (sld.chr_ai.type == LAI_TYPE_STAY)
			{
 				StartQuestMovie(true, true, true);
				SetMainCharacterIndex(GetCharacterIndex("Casper_head"));
				PChar   = GetMainCharacter();
				locCameraToPos(77.3, 8.65, -30.9, false);
				LAi_SetActorType(PChar);
				LAi_ActorDialog(PChar, characterFromID("LSCMayor"), "", 0, 0);
			}
		break;

		case "LSC_SesilAfraid":
			sld = characterFromID("SesilGalard");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, false);
		break;

		case "LSC_SesilAfterFight":
			chrDisableReloadToLocation = false;
			iTemp = GetCharacterIndex("SesilGalard");
			if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
			{
				sld = &characters[iTemp];
				while (FindCharacterItemByGroup(sld, BLADE_ITEM_TYPE) != "")
				{
					TakeItemFromCharacter(sld, FindCharacterItemByGroup(sld, BLADE_ITEM_TYPE));
				}
				sld.dialog.currentnode = "First time";
				sld.greeting = "Enc_RapersGirl_2";
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TmpEnemy");
				LAi_ActorWaitDialog(sld, pchar);
				AddQuestRecord("ISS_MainLine", "28");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ел","ла"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("","а"));
				pchar.questTemp.LSC = "toKnowAboutMechanic";
				AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_quests_reaction_183", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_quests_reaction_184", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_quests_reaction_185", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_quests_reaction_186", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_quests_reaction_187", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "");
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "29");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ел","ла"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("","а"));
				pchar.questTemp.LSC = "SessilIsDead";
				AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_quests_reaction_188", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_quests_reaction_189", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_quests_reaction_190", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_quests_reaction_191", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(GetConvertStrWithReplace("Variable_quests_reaction_192", "AddRumours.txt", "#space#", " "), "LostShipsCity", 10, 1, "LSC", "");
			}
		break;

		case "LSC_casperIsGone":
			sld = &characters[sti(pchar.questTemp.LSC.Armo.casperIdx)];
			LAi_ActorTurnByLocator(sld, "quest", "target");
			sld.checkChrDistance = 5; //проверять дистанцию до характерса
			sld.checkChrDistance.id = "Blaze"; //Id характерса
			sld.checkChrDistance.time = 0; //время повторной проверки
			sld.checkChrDistance.node = sld.id; //нода диалога
		break;

		case "LSC_PrisonerAfterFight":
			iTemp = GetCharacterIndex("LSC_Prisoner1");
			if (!LAi_IsDead(&characters[iTemp]))
			{
				LAi_SetFightMode(pchar, false);
				characters[iTemp].dialog.currentnode = "AfterFightCasper";
				LAi_SetActorTypeNoGroup(&characters[iTemp]);
				LAi_ActorDialog(&characters[iTemp], pchar, "", -1.0, 0);
			}
		break;

		case "LSC_PedroOpenedDoor":
			sld = characterFromId("PedroHurtado");
            LAi_ActorTurnToLocator(sld, "goto", "goto04_5");
            LAi_ActorAnimation(sld, "Barman_idle", "LSC_EndOpenDoor", 1.5);
            DoQuestFunctionDelay("LSC_Click", 1.0);
		break;

		case "LSC_EndOpenDoor":
			sld = characterFromId("PedroHurtado");
			sld.dialog.currentNode = "StStart_Opened";
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		case "Teno_youWinFight":
			pchar.questTemp.Teno = "YouWinGod"; //флаг конца линейки Тено
			LAi_SetFightMode(pchar, false);
			iTemp = GetCharacterIndex("AztecCitizen_1");
			if (iTemp != -1) characters[iTemp].dialog.currentnode = "Aztec1AF";
			iTemp = GetCharacterIndex("AztecCitizen_2");
			if (iTemp != -1) characters[iTemp].dialog.currentnode = "Aztec2AF";
			LocatorReloadEnterDisable("Tenochtitlan", "reload1_back", true);
			sld = characterFromId("Montesuma");
			sld.lastname = "II";
			sld.dialog.currentnode = "AfterGTemple";
			DeleteAttribute(sld, "reactionOnFightModeOn");
			DeleteAttribute(sld, "BreakTmplAndFight");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			ChangeCharacterAddressGroup(sld, "Tenochtitlan", "teleport", "fire1");
			pchar.quest.Teno_exitFromTeno.win_condition.l1 = "locator";
			pchar.quest.Teno_exitFromTeno.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Teno_exitFromTeno.win_condition.l1.locator_group = "teleport";
			pchar.quest.Teno_exitFromTeno.win_condition.l1.locator = "fire1";
			pchar.quest.Teno_exitFromTeno.function = "Teno_exitFromTeno";
			sld = characterFromId("DeadmansGod");
			sld.dialog.currentnode = "WinInTemple";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		case "Teno_MontesumaArrived":
			sld = characterFromId("Montesuma");
			LAi_ActorTurnByLocator(sld, "quest", "quest1");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_warrior_SetStay(sld, true);
		break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  homo  Линейка Блада     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//case "CureLord":
        //    CureLord();
		//break;

		case "CureLordMovie_Con1":
            CureLordMovie_Con1();
		break;

		case "CureLordMovie_Con2":
            CureLordMovie_Con2();
		break;

		case "CureLordMovie_Con3":
            CureLordMovie_Con3();
		break;

		case "CapBloodLineInit":
            CapBloodLineInit("");
		break;

		case "CapBlood_CheckMinHP":
            LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
            InterfaceStates.Buttons.Save.enable = false;
            InterfaceStates.Launched = true;
            LAi_SetFightMode(pchar, false);
            DoQuestFunctionDelay("Blood_StartGame_End", 1.5);
            //CapBloodLineInit();
		break;

		case "Whisper_PC_CheckHP":
            LAi_group_SetRelation("wl_Pirate", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
            InterfaceStates.Buttons.Save.enable = false;
            LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			Pchar.model="PGG_Whisper_0_NoHat";
			DeleteAttribute(pchar,"cirassID");
			DoQuestFunctionDelay("WhisperHold", 0.5);
		break;

		case "WhisperLine_IncqGuard_bad_speaks":
			sld = characterFromId(pchar.Whisper.IncqGuard_bad);
			SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
		break;


		case "PGG_CheckHP":
		if (CheckAttribute(pchar, "PGG_FightOnShore"))
            {
				sld = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
				LAi_SetImmortal(sld, true);
				PChar.Quest.PGGQuest1_PGGDead.PGG_Dead = "yes";
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", 10.0);
			}
		break;

		case "PGG_CheckHPDuel":
			sld = CharacterFromID(PChar.questTemp.duel.enemy);
			DoQuestCheckDelay("hide_weapon", 1.0);
			sld.Dialog.CurrentNode = "Duel_Won";
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				DeleteAttribute(pchar, "questTemp.LocationClone");
			}
			if (CheckAttribute(pchar, "questTemp.LocFightEnable") && sti(pchar.questTemp.LocFightEnable))
			{
				sld = &Locations[FindLocation(pchar.location)];
				LAi_LocationFightDisable(sld, true);
				DeleteAttribute(pchar, "questTemp.LocFightEnable");
			}
		break;

		case "Sharp_Prologue_CheckHP":
			LAi_group_SetRelation("SharpSibling", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			sld = CharacterFromID("Sharp_Sibling");
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
		break;

		case "Dragun_0_CheckMinHP":
            for (i=0; i<=2; i++)
            {
                sld = characterFromID("Dragun_"+i);
                if (i == 0)
                {
                    LAi_RemoveCheckMinHP(sld);
                    LAi_KillCharacter(sld);
                }
                else
                {
                    string sQuest = "CapGobartAttack_"+i;
                    pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
                    pchar.quest.(sQuest).win_condition.l1.character = sld.id;
                    pchar.quest.(sQuest).function= "CapGobartAttack";
                    LAi_SetImmortal(sld, false);
                    LAi_SetWarriorTypeNoGroup(sld);//fix
                    LAi_warrior_DialogEnable(sld, false);//fix
                    LAi_group_MoveCharacter(sld, "TmpEnemy");
                }
            }
            //LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
		break;

		case "BishopOnHouse":
            sld = characterFromID("Bishop");
            sld.talker = 10;
            LAi_SetCitizenType(sld);
            LAi_SetOwnerTypeNoGroup(sld);
       	    //LAi_SetStayTypeNoGroup(sld);

        break;

        case "NettlOnTavern":
            sld = characterFromID("Nettl");
   	        LAi_SetSitTypeNoGroup(sld);
   	        //sld.dialog.currentnode = "NStep_1";
            ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit8");

        break;

        case "SaveArabelaServiceAfraid":

            ref chr;
            chr = characterFromID("ArabelaService");
            sld = characterFromID("SpaRaider");
            LAi_ActorAfraid(chr, sld, true);
            LAi_SetPatrolTypeNoGroup(sld);
            //sld.talker = 10;
            //LAi_ActorDialog(sld, pchar, "",  3.0, 0);

        break;

        case "ShipGuardsDie":
            ShipGuardsDie();
        break;

        case "move_slave_2":
			//Boyer fix to minimize daily iterations
			SaveCurrentQuestDateParam("PGG_DailyUpdate");
			pchar.quest.CapBloodLine_firstEnterHome.win_condition.l1          = "location";
			pchar.quest.CapBloodLine_firstEnterHome.win_condition.l1.location = "Plantation_S1";
			pchar.quest.CapBloodLine_firstEnterHome.function      = "CapBloodLine_firstEnterHome";
			StartPictureAsVideo("Loading\finalbad2.tga", 1);
			DoReloadCharacterToLocation("Plantation_S1", "goto", "goto1");
			LAi_FadeEndFadeOut();
			InterfaceStates.Buttons.Save.enable = true;
        break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ПОСТРОЙКА КОЛОНИИ - НАЧАЛО
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "ColonyBuilding":
			SetQuestHeader("ColonyBuilding");
			AddQuestRecord("ColonyBuilding", "1");
			AddQuestUserData("ColonyBuilding", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ColonyBuilding", "sSex1", GetSexPhrase("ся","ась"));
			string sArchitecorName = Characters[GetCharacterIndex("Builder")].name + " " + Characters[GetCharacterIndex("Builder")].lastname;
			AddQuestUserData("ColonyBuilding", "sArchitecorName", sArchitecorName);

			Locations[FindLocation("PortRoyal_town")].reload.l23.disable = true;

			PChar.ColonyBuilding.Stage.FirstStage = "0";
			PChar.ColonyBuilding.Action = true;

			PChar.quest.ColonyBuildingTerks_1.win_condition.l1 = "location";
			PChar.quest.ColonyBuildingTerks_1.win_condition.l1.location = "Shore57";
			PChar.quest.ColonyBuildingTerks_1.win_condition = "ColonyBuildingTerks_1";
			PChar.quest.ColonyBuildingDominica_1.win_condition.l1 = "location";
			PChar.quest.ColonyBuildingDominica_1.win_condition.l1.location = "Shore27";
			PChar.quest.ColonyBuildingDominica_1.win_condition = "ColonyBuildingDominica_1";
			PChar.quest.ColonyBuildingCayman_1.win_condition.l1 = "location";
			PChar.quest.ColonyBuildingCayman_1.win_condition.l1.location = "Shore17";
			PChar.quest.ColonyBuildingCayman_1.win_condition = "ColonyBuildingCayman_1";

			PChar.quest.ColonyBuilding_6.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyBuilding_6.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyBuilding_6.win_condition = "ColonyBuilding_6";

			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			SetCharacterRemovable(&Characters[GetCharacterIndex("Builder")], false);
			AddPassenger(PChar, &Characters[GetCharacterIndex("Builder")], 0);
		break;

		case "ColonyBuildingTerks":
			AddQuestRecord("ColonyBuilding", "2");
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_8";
			LAi_SetStayType(CharacterFromID("Builder"));
			PChar.quest.ColonyBuilding_5.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyBuilding_5.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyBuilding_5.win_condition = "ColonyBuilding_4";
		break;

		case "ColonyBuildingDominica":
			AddQuestRecord("ColonyBuilding", "11");
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_8";
			LAi_SetStayType(&Characters[GetCharacterIndex("Builder")]);
			PChar.quest.ColonyBuilding_5.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyBuilding_5.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyBuilding_5.win_condition = "ColonyBuilding_4";
		break;

		case "ColonyBuildingTerks_1":
			StartQuestMovie(true, false, true);
			ChangeCharacterAddressGroup(&Characters[GetCharacterIndex("Builder")], "Shore57", "goto", "goto2");
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_Terks";
			LAi_SetActorType(&Characters[GetCharacterIndex("Builder")]);
			LAi_ActorDialog(&Characters[GetCharacterIndex("Builder")], PChar, "", 20.0, 1.0);
		break;

		case "ColonyBuildingDominica_1":
			StartQuestMovie(true, false, true);
			ChangeCharacterAddressGroup(&Characters[GetCharacterIndex("Builder")], "Shore27", "encdetector", "enc01");
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_Dominica";
			LAi_SetActorType(&Characters[GetCharacterIndex("Builder")]);
			LAi_ActorDialog(&Characters[GetCharacterIndex("Builder")], PChar, "", 20.0, 1.0);
		break;

		case "ColonyBuildingCayman_1":
			StartQuestMovie(true, false, true);
			ChangeCharacterAddressGroup(&Characters[GetCharacterIndex("Builder")], "Shore17", "goto", "goto13");
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_2";
			LAi_SetActorType(&Characters[GetCharacterIndex("Builder")]);
			LAi_ActorDialog(&Characters[GetCharacterIndex("Builder")], PChar, "", 20.0, 1.0);
			AddQuestRecord("ColonyBuilding", "3");
		break;

		case "ColonyBuildingCayman":
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			AddQuestRecord("ColonyBuilding", "4");
			PChar.ColonyBuilding.Stage.FirstStage = "1";
			PChar.quest.ColonyBuildingDominica_1.over = "yes";
			PChar.quest.ColonyBuildingTerks_1.over = "yes";

			PChar.BuildingColony.Blocks = 500;
			PChar.BuildingColony.Planks = 1000;
			PChar.BuildingColony.Mahogany = 500;
			PChar.BuildingColony.Ebony = 250;
			PChar.BuildingColony.Slaves = 200;
			PChar.BuildingColony.Food = 400;

			LAi_SetStayType(&Characters[GetCharacterIndex("Builder")]);
			//LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER_OWN);
			RemovePassenger(PChar, &Characters[GetCharacterIndex("Builder")]);
		break;

		case "ColonyBuildingCayman_2":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_4";
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 5.0, 1.0);
		break;

		case "ColonyBuilding_1":
			AddQuestRecord("ColonyBuilding", "5");
			AddQuestUserData("ColonyBuilding", "sSex", GetSexPhrase("","а"));
			PChar.ColonyBuilding.Stage.FirstStage = "2";
			int iColonyBuildingTime = sti(PChar.BuildingColony.ColonyTime);
            		SetTimerCondition("ColonyBuilding_2", 0, 0, iColonyBuildingTime, false);
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			LAi_Fade("", "");
			PChar.ColonyBuilding.SlavesInShore.CurShore = "Shore17";
			CreateCaimanShoreSlaves(&Locations[FindLocation(PChar.location)]);
		break;

		case "ColonyBuilding_2":
			CreateSmallColonyCaiman();

			PChar.ColonyBuilding.Stage.FirstStage = "3";
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_7";
			PlayStereoSound("notebook");
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_120", "Logs.txt", "#space#", " "));

			PChar.quest.ColonyBuilding_2_1.win_condition.l1 = "location";
			PChar.quest.ColonyBuilding_2_1.win_condition.l1.location = "Shore17";
			PChar.quest.ColonyBuilding_2_1.win_condition = "ColonyBuilding_2_1";
		break;

		case "ColonyBuilding_2_1":
			chrDisableReloadToLocation = true;
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 15.0, 1.0);
		break;

		case "ColonyBuilding_3":
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = true;
			bDisableQuestInterface = true;

			AddQuestRecord("ColonyBuilding", "6");
			PChar.ColonyBuilding.Stage.FirstStage = "end";
			PChar.ColonyBuilding.Action = false;

			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);

			PChar.quest.ColonyBuilding_4.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyBuilding_4.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyBuilding_4.win_condition = "ColonyBuilding_4";

			PChar.ColonyBuilding.SlavesInShore.CurShore = "none";
			DeleteAllFantomCharactersFromLocation(&Locations[FindLocation(PChar.location)]);

			LAi_SetActorType(PChar);
            		DoQuestCheckDelay("ColonyBuilding_EnterName", 2.5);

		break;

		case "ColonyBuilding_EnterName":
			PChar.ColonyBuilding.FirstBuild = true;
			LaunchColonyBuilding(true, false);

			bDisableCharacterMenu = false;
			bDisableQuestInterface = false;
			LAi_SetPlayerType(PChar);
		break;

		case "ColonyBuilding_4":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "First time";
			ChangeCharacterAddressGroup(&Characters[GetCharacterIndex("Builder")], "Caiman_town", "goto", "goto5");
			LAi_SetCitizenType(&Characters[GetCharacterIndex("Builder")]);
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
		break;

		case "ColonyBuilding_5":
			ChangeCharacterAddress(&Characters[GetCharacterIndex("Builder")], "None", "");
		break;

		case "ColonyBuilding_6":
			LAi_SetCitizenType(&Characters[GetCharacterIndex("Builder")]);
			ChangeCharacterAddress(&Characters[GetCharacterIndex("Builder")], "None", "");
		break;

// Colony Modification
		case "ColonyModification":
			AddQuestRecord("ColonyBuilding", "7");
			AddQuestUserData("ColonyBuilding", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ColonyBuilding", "sColonyName", PChar.ColonyBuilding.ColonyName);

			PChar.ColonyBuilding.Stage.SecondStage = "0";
			PChar.ColonyBuilding.Action = true;

			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorGoToLocation(CharacterFromID("Builder"), "reload", "reload1", "none", "", "", "", -1);

			PChar.quest.ColonyModification_1.win_condition.l1 = "location";
			PChar.quest.ColonyModification_1.win_condition.l1.location = "Shore17";
			PChar.quest.ColonyModification_1.win_condition = "ColonyModification_1";
		break;

		case "ColonyModification_1":
			PChar.ColonyBuilding.Stage.SecondStage = "1";
			PChar.BuildingColony.Blocks = 1000;
			PChar.BuildingColony.Planks = 2000;
			PChar.BuildingColony.Mahogany = 750;
			PChar.BuildingColony.Ebony = 500;
			PChar.BuildingColony.Slaves = 600;
			PChar.BuildingColony.Food = 1500;
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Shore17", "goto", "goto13");
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_1";
		break;

		case "ColonyModification_1_1":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_3";
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 5.0, 1.0);
		break;

		case "ColonyModification_2":
			AddQuestRecord("ColonyBuilding", "9");
			AddQuestUserData("ColonyBuilding", "sSex", GetSexPhrase("","а"));
			PChar.ColonyBuilding.Stage.SecondStage = "2";
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			int iColonyModificationTime = sti(PChar.BuildingColony.ColonyModification);
            		SetTimerCondition("ColonyModification_3", 0, 0, iColonyModificationTime, false);
			LAi_Fade("", "");
			PChar.ColonyBuilding.SlavesInShore.CurShore = "Shore17";
			CreateCaimanShoreSlaves(&Locations[FindLocation(PChar.location)]);
		break;

		case "ColonyModification_3":
			PChar.ColonyBuilding.Stage.SecondStage = "3";
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_4";
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Caiman_town", "goto", "goto8");
			PlayStereoSound("notebook");
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_121", "Logs.txt", "#space#", " ") + PChar.ColonyBuilding.ColonyName + GetConvertStrWithReplace("Variable_quests_reaction_122", "Logs.txt", "#space#", " "));

			CreateModificyColonyCaiman();

			int idxLoadLoc = FindLoadedLocation();
            if (idxLoadLoc != -1)
            {
				if (locations[idxLoadLoc].islandId == "Caiman")
				{
					DoQuestReloadToLocation("Caiman_town","reload","reload1", "");
					setCharacterShipLocation(pchar, "Caiman_town");
					setWDMPointXZ("Caiman_town");
				}
			}

			PChar.ColonyBuilding.SlavesInShore.CurShore = "none";
			PChar.quest.ColonyModification_6.win_condition.l1 = "location";
			PChar.quest.ColonyModification_6.win_condition.l1.location = "Caiman_town";
			PChar.quest.ColonyModification_6.win_condition = "ColonyModification_6";
		break;

		case "ColonyModification_4":
			EndQuestMovie();
			AddQuestRecord("ColonyBuilding", "10");
			AddQuestUserData("ColonyBuilding", "sColonyName", PChar.ColonyBuilding.ColonyName);
			PChar.ColonyBuilding.Stage.SecondStage = "end";
			PChar.ColonyBuilding.Action = false;

			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "First time";
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "BuilderToTownhall":
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Caiman_townhall", "goto", LAi_FindFreeRandomLocator("goto"));
		break;

		case "ColonyModification_5":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "First time";
		break;

		case "ColonyModification_6":
			chrDisableReloadToLocation = true;
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_4";
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 25.0, 1.0);
		break;

		case "ColonyModification_7":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_2";
			LAi_SetActorType(PChar);
			LAi_ActorWaitDialog(PChar, CharacterFromID("Builder"));
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 5.0, 1.0);
		break;

// Set Hovernor
		case "SetHovernorToColonyResidence":
			LAi_SetHuberType(CharacterFromID(PChar.ColonyBuilding.Hovernor));
		break;

// Colony Fort Building
		case "ColonyFortBuilding_1":
			AddQuestRecord("ColonyBuilding", "12");
			PChar.quest.ColonyFortBuilding_2.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyFortBuilding_2.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyFortBuilding_2.win_condition = "ColonyFortBuilding_2";
			PChar.quest.ColonyFortBuilding_3.win_condition.l1 = "location";
			PChar.quest.ColonyFortBuilding_3.win_condition.l1.location = "Shore16";
			PChar.quest.ColonyFortBuilding_3.win_condition = "ColonyFortBuilding_3";

			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorRunToLocation(CharacterFromID("Builder"), "reload", "gate_back", "none", "", "", "", -1);
		break;

		case "ColonyFortBuilding_1_1":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyFortBuilding_4";
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 5.0, 1.0);
		break;

		case "ColonyFortBuilding_2":
			ChangeCharacterAddress(CharacterFromID("Builder"), "None", "");
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "First time";
		break;

		case "ColonyFortBuilding_3":
			PChar.BuildingColony.Blocks = 2500;
			PChar.BuildingColony.Planks = 1500;
			PChar.BuildingColony.Mahogany = 300;
			PChar.BuildingColony.Ebony = 200;
			PChar.BuildingColony.Slaves = 500;
			PChar.BuildingColony.Food = 1000;
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyFortBuilding_3";
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Shore16", "goto", "goto8");
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
		break;

		case "ColonyFortBuilding_4":
			AddQuestRecord("ColonyBuilding", "13");
		break;

		case "ColonyFortBuilding_5":
			AddQuestRecord("ColonyBuilding", "14");

			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);

			int iColonyFortTime = sti(PChar.BuildingColony.ColonyFort);
            		SetTimerCondition("ColonyFortBuilding_6", 0, 0, iColonyFortTime, false);

			LAi_Fade("", "");
			PChar.ColonyBuilding.SlavesInShore.CurShore = "Shore16";
			CreateCaimanShoreSlaves(&Locations[FindLocation(PChar.location)]);
		break;

		case "ColonyFortBuilding_6":
			PlayStereoSound("notebook");
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_123", "Logs.txt", "#space#", " ") + PChar.ColonyBuilding.ColonyName + GetConvertStrWithReplace("Variable_quests_reaction_124", "Logs.txt", "#space#", " "));
			CreateFortInCaiman();
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "LandGuardingPort", "goto", "goto1");
			LAi_SetStayType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyFortBuilding_6";
			PChar.ColonyBuilding.Stage = "3";

			PChar.ColonyBuilding.SlavesInShore.CurShore = "LandGuardingPort";
			PChar.quest.ColonyFortBuilding_6_1.win_condition.l1 = "location";
			PChar.quest.ColonyFortBuilding_6_1.win_condition.l1.location = "LandGuardingPort";
			PChar.quest.ColonyFortBuilding_6_1.win_condition = "ColonyFortBuilding_6_1";
		break;

		case "ColonyFortBuilding_6_1":
			chrDisableReloadToLocation = true;
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 5.0, 1.0);
		break;

		case "ColonyFortBuilding_7":
			chrDisableReloadToLocation = false;
			AddQuestRecord("ColonyBuilding", "15");
			CloseQuestHeader("ColonyBuilding");
			pchar.questdata.StroitelstvoKolonii = 1;

			LAi_Fade("", "");
			PChar.ColonyBuilding.SlavesInShore.CurShore = "None";
			DeleteAllFantomCharactersFromLocation(&Locations[FindLocation(PChar.location)]);

			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorRunToLocation(CharacterFromID("Builder"), "reload", "reload1_back", "none", "", "", "", -1);

			PChar.quest.ColonyFortBuilding_8.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyFortBuilding_8.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyFortBuilding_8.win_condition = "ColonyFortBuilding_8";
		break;

		case "ColonyFortBuilding_8":
			Locations[FindLocation("PortRoyal_town")].reload.l23.disable = false;
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "BuilderHouse", "sit", "sit1");
			LAi_SetHuberType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], "ENGLAND_CITIZENS");
		break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ПОСТРОЙКА КОЛОНИИ - КОНЕЦ
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ПОСТРОЙКА ЗДАНИЙ В КОЛОНИИ - НАЧАЛО
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "Store_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("Store_build_1", 0, 0, iBuild, false);
		break;

		case "Store_build_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_125", "Logs.txt", "#space#", " "));
			ChangeColonyMorale(5, false);
			PChar.ColonyBuilding.Store.BuildingTime = false;
			PChar.ColonyBuilding.Store = true;
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_trader"), "Caiman_store", "barmen", "stay");
			Locations[FindLocation("Caiman_town")].reload.l6.disable = false;

		break;

		case "Shipyard_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("Shipyard_build_1", 0, 0, iBuild, false);
		break;

		case "Shipyard_build_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_126", "Logs.txt", "#space#", " "));
			ChangeColonyMorale(5, false);
			PChar.ColonyBuilding.Shipyard.BuildingTime = false;
			PChar.ColonyBuilding.Shipyard = true;
			Locations[FindLocation("Caiman_town")].reload.l5.disable = false;
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_shipyarder"), "Caiman_shipyard", "sit", "sit1");
		break;

		case "Tavern_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("Tavern_build_1", 0, 0, iBuild, false);
		break;

		case "Tavern_build_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_127", "Logs.txt", "#space#", " "));
			ChangeColonyMorale(10, false);
			PChar.ColonyBuilding.Tavern.BuildingTime = false;
			PChar.ColonyBuilding.Tavern = true;
			Locations[FindLocation("Caiman_town")].reload.l4.disable = false;
			Locations[FindLocation("Caiman_town")].reload.l41.disable = false;
			Locations[FindLocation("Caiman_tavern")].habitues = 1;
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_tavernkeeper"), "Caiman_Tavern", "barmen", "stay");
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_waitress"), "Caiman_Tavern", "waitress", "barmen");
		break;

		case "Church_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("Church_build_1", 0, 0, iBuild, false);
		break;

		case "Church_build_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_128", "Logs.txt", "#space#", " "));
			ChangeColonyMorale(20, false);
			PChar.ColonyBuilding.Church.BuildingTime = false;
			PChar.ColonyBuilding.Church = true;
			Locations[FindLocation("Caiman_town")].reload.l7.disable = false;
			Locations[FindLocation("Caiman_town")].reload.l71.disable = false;
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_Priest"), "Caiman_church", "barmen", "stay");
		break;

		case "Bank_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("Bank_build_1", 0, 0, iBuild, false);
		break;

		case "Bank_build_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_129", "Logs.txt", "#space#", " "));
			ChangeColonyMorale(10, false);
			PChar.ColonyBuilding.Bank.BuildingTime = false;
			PChar.ColonyBuilding.Bank = true;
			Locations[FindLocation("Caiman_town")].reload.l8.disable = false;
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_usurer"), "Caiman_bank", "barmen", "stay");
		break;

		case "HeadPort_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("HeadPort_build_1", 0, 0, iBuild, false);
		break;

		case "HeadPort_build_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_130", "Logs.txt", "#space#", " "));
			ChangeColonyMorale(10, false);
			PChar.ColonyBuilding.HeadPort.BuildingTime = false;
			PChar.ColonyBuilding.HeadPort = true;
			Locations[FindLocation("Caiman_town")].reload.l10.disable = false;
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_PortMan"), "Caiman_PortOffice", "sit", "sit1");
		break;

		case "Expidition_build":
			iBuild = rand(3) + 2;
            		SetTimerCondition("Expidition_build_1", 0, 0, iBuild, false);
		break;

		case "Expidition_build_1":
			if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1 && GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != nMainCharacterIndex)
			{
				Characters[GetCharacterIndex(PChar.ColonyBuilding.Hovernor)].Dialog.CurrentNode = "ColonyBuilding_Expidition_End";
			}

			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_131", "Logs.txt", "#space#", " "));
			PChar.ColonyBuilding.Expidition.BuildingTime = false;
			PChar.ColonyBuilding.Expidition = true;
		break;

		case "Plantation_build":
			iBuild = rand(5) + 20;
            		SetTimerCondition("Plantation_build_1", 0, 0, iBuild, false);
		break;

		case "Plantation_build_1":
			if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1 && GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != nMainCharacterIndex)
			{
				Characters[GetCharacterIndex(PChar.ColonyBuilding.Hovernor)].Dialog.CurrentNode = "ColonyBuilding_Plantation_End";
			}
			CreatePlantationInCaiman();

			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_132", "Logs.txt", "#space#", " "));
			PChar.ColonyBuilding.Plantation.BuildingTime = false;
		break;

		case "Plantation_resize":
			iBuild = rand(5) + 10;
            		SetTimerCondition("Plantation_resize_1", 0, 0, iBuild, false);
		break;

		case "Plantation_resize_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_133", "Logs.txt", "#space#", " "));
			PChar.Plantation.Size.Resize.BuildingTime = false;
			PChar.ColonyBuilding.Plantation.Resize.BuildingTime = false;
			PChar.Plantation.Size = 2;
			PChar.Plantation.Slaves.MaxQuantity = 500;
			PChar.Plantation.Guardians.MaxQuantity = 500;
			PChar.Plantation.Food.MaxQuantity = 8000;
			PChar.Plantation.Medicament.MaxQuantity = 4500;
			PChar.Plantation.Items.MaxQuantity = 550;
			PChar.Plantation.Sugar.MaxQuantity = 10000;
		break;

		case "StoreHouse_build":
			iBuild = rand(2) + 2;
            		SetTimerCondition("StoreHouse_build_1", 0, 0, iBuild, false);
		break;

		case "StoreHouse_build_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_134", "Logs.txt", "#space#", " "));
			PChar.ColonyBuilding.StoreHouse.BuildingTime = false;
			PChar.ColonyBuilding.StoreHouse = true;

			if(PChar.ColonyBuilding.Stage == "1")
			{
				Locations[FindLocation("Caiman_town")].reload.l11.label = "Caiman Store House";
				Locations[FindLocation("Caiman_town")].reload.l11.disable = false;
				Locations[FindLocation("Caiman_StoreHouse")].reload.l1.emerge = "reload4";
			}
			else
			{
				Locations[FindLocation("Caiman_town")].reload.l11.label = "Caiman Store House";
				Locations[FindLocation("Caiman_town")].reload.l11.disable = false;
				Locations[FindLocation("Caiman_StoreHouse")].reload.l1.emerge = Locations[FindLocation("Caiman_town")].reload.l11.name;

				if(Locations[FindLocation("Caiman_StoreHouse")].reload.l1.emerge == "")
				{
					Locations[FindLocation("Caiman_StoreHouse")].reload.l1.emerge = "houseS1";
				}
			}
		break;

		case "GoldMine_build":
			iBuild = rand(5) + 12;
            		SetTimerCondition("GoldMine_build_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;

		case "GoldMine_build_1":
			if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1 && GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != nMainCharacterIndex && PChar.ColonyBuilding.MineMessage == false)
			{
				Characters[GetCharacterIndex(PChar.ColonyBuilding.Hovernor)].Dialog.CurrentNode = "ColonyBuilding_Mines_End";
			}

			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_135", "Logs.txt", "#space#", " "));
			PChar.Mines.GoldMine = true;
			PChar.ColonyBuilding.GoldMine = true;
			PChar.Mines.GoldMine.BuildingTime = false;
			PChar.ColonyBuilding.GoldMine.BuildingTime = false;
			CreateMinesInCaiman();
            		PChar.Mines.Defence.Block = false;
		break;

		case "SilverMine_build":
			iBuild = rand(5) + 10;
            		SetTimerCondition("SilverMine_build_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;

		case "SilverMine_build_1":
			if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1 && GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != nMainCharacterIndex && PChar.ColonyBuilding.MineMessage == false)
			{
				Characters[GetCharacterIndex(PChar.ColonyBuilding.Hovernor)].Dialog.CurrentNode = "ColonyBuilding_Mines_End";
			}

			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_136", "Logs.txt", "#space#", " "));
			PChar.Mines.SilverMine = true;
			PChar.Mines.SilverMine.BuildingTime = false;
			PChar.ColonyBuilding.SilverMine.BuildingTime = false;
			PChar.ColonyBuilding.SilverMine = true;
			CreateMinesInCaiman();
            		PChar.Mines.Defence.Block = false;
		break;

		case "IronMine_build":
			iBuild = rand(5) + 5;
            		SetTimerCondition("IronMine_build_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;

		case "IronMine_build_1":
			if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1 && GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != nMainCharacterIndex && PChar.ColonyBuilding.MineMessage == false)
			{
				Characters[GetCharacterIndex(PChar.ColonyBuilding.Hovernor)].Dialog.CurrentNode = "ColonyBuilding_Mines_End";
			}
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_137", "Logs.txt", "#space#", " "));
			PChar.Mines.IronMine = true;
			PChar.Mines.IronMine.BuildingTime = false;
			PChar.ColonyBuilding.IronMine.BuildingTime = false;
			PChar.ColonyBuilding.IronMine = true;
			CreateMinesInCaiman();
            		PChar.Mines.Defence.Block = false;
		break;

		case "GoldMine_resize":
			iBuild = rand(2) + 7;
            		SetTimerCondition("GoldMine_resize_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;

		case "GoldMine_resize_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_138", "Logs.txt", "#space#", " "));
			PChar.ColonyBuilding.GoldMine.Resize.BuildingTime = false;
			PChar.ColonyBuilding.GoldMine.Resize = true;
			PChar.Mines.GoldQuantity.Max = 5000;
			PChar.Mines.FoodQuantity.Max = sti(PChar.Mines.FoodQuantity.Max) + 1000;
			PChar.Mines.MedicamentQuantity.Max = sti(PChar.Mines.MedicamentQuantity.Max) + 1000;
			PChar.Mines.MaxSlavesQuantity = sti(PChar.Mines.MaxSlavesQuantity) + 100;
			PChar.Mines.MaxGuardiansQuantity = sti(PChar.Mines.MaxGuardiansQuantity) + 100;
            		PChar.Mines.Defence.Block = false;
		break;

		case "SilverMine_resize":
			iBuild = rand(2) + 5;
            		SetTimerCondition("SilverMine_resize_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;

		case "SilverMine_resize_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_139", "Logs.txt", "#space#", " "));
			PChar.ColonyBuilding.SilverMine.Resize.BuildingTime = false;
			PChar.ColonyBuilding.SilverMine.Resize = true;
			PChar.Mines.FoodQuantity.Max = sti(PChar.Mines.FoodQuantity.Max) + 1000;
			PChar.Mines.MedicamentQuantity.Max = sti(PChar.Mines.MedicamentQuantity.Max) + 1000;
			PChar.Mines.SilverQuantity.Max = 7500;
			PChar.Mines.MaxSlavesQuantity = sti(PChar.Mines.MaxSlavesQuantity) + 100;
			PChar.Mines.MaxGuardiansQuantity = sti(PChar.Mines.MaxGuardiansQuantity) + 100;
            		PChar.Mines.Defence.Block = false;
		break;

		case "IronMine_resize":
			iBuild = rand(2) + 3;
            		SetTimerCondition("IronMine_resize_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;

		case "IronMine_resize_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_140", "Logs.txt", "#space#", " "));
			PChar.ColonyBuilding.IronMine.Resize.BuildingTime = false;
			PChar.ColonyBuilding.IronMine.Resize = true;
			PChar.Mines.FoodQuantity.Max = sti(PChar.Mines.FoodQuantity.Max) + 1000;
			PChar.Mines.MedicamentQuantity.Max = sti(PChar.Mines.MedicamentQuantity.Max) + 1000;
			PChar.Mines.IronQuantity.Max = 10000;
			PChar.Mines.MaxSlavesQuantity = sti(PChar.Mines.MaxSlavesQuantity) + 100;
			PChar.Mines.MaxGuardiansQuantity = sti(PChar.Mines.MaxGuardiansQuantity) + 100;
            		PChar.Mines.Defence.Block = false;
		break;

		case "StoreHouse_resize":
			iBuild = rand(3) + 2;
            		SetTimerCondition("StoreHouse_resize_1", 0, 0, iBuild, false);
		break;

		case "StoreHouse_resize_1":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_141", "Logs.txt", "#space#", " "));
			Stores[STORE_HOUSE].max_weight = sti(Stores[STORE_HOUSE].max_resize_weight);
			PChar.ColonyBuilding.StoreHouse.Resize.BuildingTime = false;
			PChar.ColonyBuilding.StoreHouse.Resize = true;
		break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ПОСТРОЙКА ЗДАНИЙ В КОЛОНИИ - КОНЕЦ
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ЖИЗНЬ В КОЛОНИИ - НАЧАЛО
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "SetCommanderToMinesOffice":
			LAi_SetStayType(CharacterFromID(PChar.Mines.Commander));
		break;

		/*
                        PChar.quest.LiveOfTheColonyUptade_1.over = "yes";
                        PChar.quest.LiveOfTheColonyUptade_2.over = "yes";
                        PChar.quest.LiveOfTheColonyUptade_3.over = "yes";
                        PChar.quest.LiveOfTheColonyUptade_4.over = "yes";
                */

		case "LiveOfTheColonyUptade_1":
			SetTimerCondition("LiveOfTheColonyUptade_2", 0, 0, 0, false);
		break;

		case "LiveOfTheColonyUptade_2":
			SetTimerCondition("LiveOfTheColonyUptade_3", 0, 0, 7, false);
		break;

		case "LiveOfTheColonyUptade_3":
			LiveOfTheColonyUptade();
			SetTimerCondition("LiveOfTheColonyUptade_4", 0, 0, 1, false);
		break;

		case "LiveOfTheColonyUptade_4":
			SetTimerCondition("LiveOfTheColonyUptade_3", 0, 0, 6, false);
		break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ЖИЗНЬ В КОЛОНИИ - КОНЕЦ
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		// НАПАДЕНИЯ НА КОЛОНИЮ - НАЧАЛО
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "CheckDefenceColonyUptade_1":
			SetTimerCondition("CheckDefenceColonyUptade_2", 0, 0, 0, false);
		break;

		case "CheckDefenceColonyUptade_2":
			SetTimerCondition("CheckDefenceColonyUptade_3", 0, 0, 120, false);
		break;

		case "CheckDefenceColonyUptade_3":
			CheckDefenceColony();
			SetTimerCondition("CheckDefenceColonyUptade_4", 0, 0, 118, false);
		break;

		case "CheckDefenceColonyUptade_4":
			SetTimerCondition("CheckDefenceColonyUptade_3", 0, 0, 2, false);
		break;

		case "ClearMutinyColony":
			ClearMutinyColony("");
		break;

		case "ClearLandDefenceColony":
			ClearLandDefenceColony("");
		break;

		case "ColonyNotSetDead":
			PChar.ColonyBuilding.Defence.DeadInTown = false;

			if(CheckAttribute(&Locations[FindLocation("Caiman_town")], "hidden_effects"))
			{
				DeleteAttribute(&Locations[FindLocation("Caiman_town")], "hidden_effects");
			}
			if(CheckAttribute(&Locations[FindLocation("Caiman_ExitTown")], "hidden_effects"))
			{
				DeleteAttribute(&Locations[FindLocation("Caiman_ExitTown")], "hidden_effects");
			}
		break;

		case "MinesNotSetDead":
			PChar.Mines.Defence.DeadInTown = false;
		break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// НАПАДЕНИЯ НА КОЛОНИЮ - КОНЕЦ
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ПЛАНТАЦИЯ - НАЧАЛО
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "SetCommanderToPlantationOffice":
			LAi_SetStayType(CharacterFromID(PChar.Plantation.Commander));
		break;

		case "PlantationUptade1":
			SetTimerCondition("PlantationUptade2", 0, 0, 0, false);
		break;

		case "PlantationUptade2":
			SetTimerCondition("PlantationUptade3", 0, 0, 14, false);
		break;

		case "PlantationUptade3":
			UptadeLivedInPlantation();
			SetTimerCondition("PlantationUptade4", 0, 0, 1, false);
		break;

		case "PlantationUptade4":
			SetTimerCondition("PlantationUptade3", 0, 0, 13, false);
		break;

		case "PlantationUptade5":
			PChar.Plantation.Defence.Block = false;
			Log_TestInfo(GetConvertStrWithReplace("Variable_quests_reaction_142", "Logs.txt", "#space#", " "));
		break;

		case "PlantationNotSetDead":
			PChar.Plantation.Defence.DeadInTown = false;
		break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ПЛАНТАЦИЯ - КОНЕЦ
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		// РУДНИКИ - НАЧАЛО
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "MinesUptade1":
			SetTimerCondition("MinesUptade2", 0, 0, 0, false);
		break;

		case "MinesUptade2":
			SetTimerCondition("MinesUptade3", 0, 0, 14, false);
		break;

		case "MinesUptade3":
			UptadeLivedInMines();
			SetTimerCondition("MinesUptade4", 0, 0, 1, false);
		break;

		case "MinesUptade4":
			SetTimerCondition("MinesUptade3", 0, 0, 13, false);
		break;

		case "MinesUptade5":
			PChar.Mines.Defence.Block = false;
			Log_TestInfo(GetConvertStrWithReplace("Variable_quests_reaction_143", "Logs.txt", "#space#", " "));
		break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// РУДНИКИ - КОНЕЦ
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		// АКАДЕМИЯ И АРЕНА - НАЧАЛО
		////////////////////////////////////////////////////////////////////////////////////////////////
	        case "AcademyLand_Winner":
			AcademyLandTrainingEnd(true);
	        break;

	        case "AcademyLand_Loose":
			AcademyLandTrainingEnd(false);
	        break;

	        case "ArenaDuelCheckNewRound":
	        	ArenaDuelCheckNewRound();
	        break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// АКАДЕМИЯ И АРЕНА - КОНЕЦ
		////////////////////////////////////////////////////////////////////////////////////////////////
		//homo
		//-->работорговец
		case "Slavetrader_findTortugaRat"://охрана Гонтьера
            chrDisableReloadToLocation = true; // закрыть выход из локации.
			sld = GetCharacter(NPC_GenerateCharacter("Ratlover", "girl_8", "woman", "towngirl", 10, FRANCE, -1, false));
            ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "barmen",  "bar2");
           	sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Rat_lover"; // диалоговый узел
			sld.name 	= GetConvertStr("Variable_quests_reaction_0.26", "Names.txt");
			sld.lastname 	= GetConvertStr("Variable_quests_reaction_0.26.1", "Names.txt");
			LAi_SetImmortal(sld, true);
            LAi_SetStayTypeNoGroup(sld);

            sld = GetCharacter(NPC_GenerateCharacter("SLBanditHead", "pirate_10", "man", "man", 25, PIRATE, 0, true));
            FantomMakeCoolFighter(sld, 45, 100, 100, "blade26", "pistol6", 80);
			sld.cirassId = Items_FindItemIdx("cirass5");
        	LAi_SetStayType(sld);
        	sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Rat_bandos";
            LAi_group_MoveCharacter(sld, "EnemyFight");
           	ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "goto",  "goto1");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.3);
       break;

       case "Slavetrader_findTortugaRat1"://охрана Гонтьера
            for (i=3; i<=5; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("SVBandit"+i, "pirate_"+i, "man", "man", 25, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 35, 100, 100, "blade33", "pistol6", 80);
            	LAi_SetStayType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "goto",  "goto"+i);
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat2");
       break;

       case "Slavetrader_findTortugaRat2":
            chrDisableReloadToLocation = false;
            LAi_SetActorType(pchar);
            sld = characterFromID("Ratlover");
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
       break;

	   case "Slavetrader_EscapeSlaves_Win":
            chrDisableReloadToLocation = false;
			sld = GetCharacter(NPC_GenerateCharacter("Slavewoman", "horse07", "woman", "towngirl", 10, PIRATE, -1, false));
            ChangeCharacterAddressGroup(sld, pchar.questTemp.Slavetrader.Island.Shore, "goto",  "goto31");
           	sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Slave_woman"; // диалоговый узел
			sld.name 	= GetConvertStr("Variable_quests_reaction_0.27", "Names.txt");
			sld.lastname 	= "";
			LAi_SetImmortal(sld, true);
            LAi_SetStayTypeNoGroup(sld);
			LAi_SetActorType(pchar);
            sld = characterFromID("Slavewoman");
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);

        break;
		//<--работорговец

		//ОЗГ, Карлос Кассир
		case "CarlosDie":
			if (CheckAttribute(PChar, "quest.CarlosPlace")) Pchar.quest.CarlosPlace.over = "yes";
			if (CheckAttribute(PChar, "quest.HeadhunterTimer")) Pchar.quest.HeadhunterTimer.over = "yes";
			DoQuestCheckDelay("hide_weapon", 1.0);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen(pchar.questTemp.Headhunter.City + "_ExitTown", false); //офицеров пускать
			locations[FindLocation(pchar.questTemp.Headhunter.City + "_ExitTown")].DisableEncounters = false; //энкаутеры закроем
			AddQuestRecord("Headhunt", "2");
			pchar.questTemp.Headhunter = "hunt_carlos_yes";
		break;

		//ОЗГ, наймиты Крысы
		case "RatHunters_Dead":
			chrDisableReloadToLocation = false;
			if (pchar.name == GetConvertStrWithReplace("Variable_quests_reaction_43", "Names.txt", "#space#", " "))
			{
				if(CheckAttribute(pchar,"Whisper.EsFriendTown") && pchar.Whisper.EsFriendTown == "Villemstad")
				{
					sld = CharacterFromID("W_Chard");
					ChangeCharacterAddressGroup(sld, "Villemstad_tavern_upstairs", "goto", "goto1");
					LocatorReloadEnterDisable("Villemstad_tavern", "reload2_back", false);
					LAi_LocationFightDisable(loadedLocation, true);
				}

			}
			AddQuestRecord("Headhunt", "28");
			pchar.questTemp.Headhunter = "halen_still";
		break;

		case "Headhunter_FightInPort":
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			iTemp = GetCharacterIndex("Halen");
			if (iTemp != -1)
			{
				sld = &characters[iTemp];
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
				LAi_group_Attack(sld, Pchar);
				SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
			}
		break;

		case "Headhunter_HalenOut":
			ChangeCharacterAddress(characterFromID("Halen"), "None", "");
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
		break;

		case "FindJa":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Headhunt", "35");
		break;

		case "IndianInJungleClearGroup":
			LAi_group_SetRelation("Jungle_indians", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕН. КВЕСТ - ДУЭЛЯНТ - НАЧАЛО
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "QuestDuelTalkWifeWithDuelist":
			QuestDuelTalkWifeWithDuelist();
		break;

		case "QuestDuelTalkMainCharacterWithDuelist":
			QuestDuelTalkMainCharacterWithDuelist();
		break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕН. КВЕСТ - ДУЭЛЯНТ - КОНЕЦ
		////////////////////////////////////////////////////////////////////////////////////////////////

// --> тайна Санта-Люсии
		case "LSC_RingTalkLook": // смотрим на кольцо
			LAi_SetPlayerType(pchar);
			LSC_RingRishardTalk("ring_13");
        break;

		case "LSC_RingEnterInside": // входим в трюм разбитого корабля
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			// ставим крабикусов
			iRank = 25+MOD_SKILL_ENEMY_RATE*3*2;
			iTemp = 150+MOD_SKILL_ENEMY_RATE*3*30+sti(pchar.rank)*5;
			LAi_group_Register("EnemyCrab");
			for (i=1; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("CrabInside_"+i, "crabBig", "crab", "crabBig", iRank, PIRATE, -1, false));
				sld.name = GetConvertStrWithReplace("Variable_quests_reaction_44", "Names.txt", "#space#", " ");
				sld.lastname = "";
				DeleteAttribute(sld, "items");
				GiveItem2Character(sld, "unarmed");
				EquipCharacterbyItem(sld, "unarmed");
				sld.SaveItemsForDead = true;
				sld.animal = true;
				LAi_SetHP(sld, iTemp, iTemp);
				SetCharacterPerk(sld, "BasicDefense");
				SetCharacterPerk(sld, "AdvancedDefense");
				SetCharacterPerk(sld, "CriticalHit");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "ExternalRingInside", "goto", "goto"+i);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyCrab");
			}
			LAi_group_SetRelation("EnemyCrab", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("EnemyCrab", 13.0);
			LAi_group_SetHearRadius("EnemyCrab", 5.0);
			LAi_group_SetSayRadius("EnemyCrab", 8.0);
			LAi_group_SetCheck("EnemyCrab", "LSC_RingInsideCrabsDead");
			LAi_SetFightMode(pchar, true);
        break;

		case "LSC_RingInsideCrabsDead": // перебили крабов
			PlayStereoOGG("music_LostShipsCity");
			LAi_group_Delete("EnemyCrab");
			sld = characterFromId("LSC_Rishard");
			ChangeCharacterAddressGroup(sld, "ExternalRingInside", "reload", "reload1");
			LSC_RingRishardTalk("ring_15");
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;

		case "LSC_RingDialog": // активатор диалогов
			sld = characterFromId("LSC_Rishard");
			LSC_RingRishardTalk(sld.quest.diagnode);
        break;

		case "LSC_RingEnterDeck": // входим на палубу разбитого корабля
			chrDisableReloadToLocation = true;//закрыть локацию
			// ставим крабикусов
			iRank = 25+MOD_SKILL_ENEMY_RATE*3*2;
			iTemp = 150+MOD_SKILL_ENEMY_RATE*3*30+sti(pchar.rank)*5;
			for (i=1; i<=6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("CrabDeck_"+i, "crabBig", "crab", "crabBig", iRank, PIRATE, -1, false));
				sld.name = GetConvertStrWithReplace("Variable_quests_reaction_45", "Names.txt", "#space#", " ");
				sld.lastname = "";
				DeleteAttribute(sld, "items");
				GiveItem2Character(sld, "unarmed");
				EquipCharacterbyItem(sld, "unarmed");
				sld.SaveItemsForDead = true;
				sld.animal = true;
				LAi_SetHP(sld, iTemp, iTemp);
				SetCharacterPerk(sld, "BasicDefense");
				SetCharacterPerk(sld, "AdvancedDefense");
				SetCharacterPerk(sld, "CriticalHit");
				ChangeCharacterAddressGroup(sld, "ExternalRingDeck", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyCrab");
			}
			LAi_group_SetRelation("EnemyCrab", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("EnemyCrab", 15.0);
			LAi_group_SetHearRadius("EnemyCrab", 6.0);
			LAi_group_SetSayRadius("EnemyCrab", 12.0);
			LAi_group_SetCheck("EnemyCrab", "LSC_RingDeckCrabsDead");
			LSC_RingRishardTalk("ring_22");
        break;

		case "LSC_RingDeckCrabsDead": // перебили крабов
			PlayStereoOGG("music_LostShipsCity");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", true);
			LAi_group_Delete("EnemyCrab");
			LSC_RingRishardTalk("ring_24");
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;

		case "LSC_RingEnterCabin": // вошли в каюту
			chrDisableReloadToLocation = true;
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_31";
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto1", "LSC_RingDialog", -1);
        break;

		case "LSC_RingSetToBarman": //
			sld = characterFromId("LSC_Rishard");
			LAi_SetBarmanType(sld);
        break;

		case "LSC_RingFinalStage": //
			sld = characterFromId("LSC_Rishard");
			sld.quest.ring_final = true;
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, false);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "", 7.0);
			DoQuestFunctionDelay("LSC_RingOver", 3.0); // закрываем квест
			SetFunctionTimerCondition("LSC_RingDeleteItemsBoxes", 0, 0, 2, false); // через 2 дня боксы опустеют
        break;

		case "LSC_RingFindGold": // нашли золото
			PlaySound("Ambient\LAND\door_001.wav");
			PlaySound("Ambient\LAND\door_004.wav");
			PlayVoice("Types\warrior03.wav");
			PlayVoice("Types\warrior04.wav");
			SetLaunchFrameFormParam(GetConvertStr("Variable_quests_reaction_5", "Frames.txt")+ NewStr() +GetConvertStr("Variable_quests_reaction_6", "Frames.txt"), "", 0, 6);//табличка
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_46";
			DoQuestCheckDelay("LSC_RingDialog", 6.0);
        break;
		// <-- тайна Санта-Люсии
	// <-- тайна Санта-Люсии
//История давней дружбы, написал Lipsar//;
	case "Taverna":
		chrDisableReloadToLocation = true;
		pchar = GetMainCharacter();
		sld = characterFromID("Old Friend");
		DoQuestReloadToLocation("LaVega_tavern", "sit", "sit5", "");
		ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit6");
		sld.Dialog.CurrentNode = "StartQuest_4";
		LAi_SetSitType(pchar);
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, PChar, "", 1.5);
		chrDisableReloadToLocation = false;
	break;
	case "AfterDialog":
		pchar = GetMainCharacter();
		sld = characterFromID("Old Friend");
		Lai_SetPlayerType(PChar);
		LAi_SetSitType(sld);
		DoQuestReloadToLocation("LaVega_tavern", "tables", "stay4", "");
	break;
	case "GiveLetter":
		sld = characterFromID("Maks");
		pchar = GetMainCharacter();
		TakeItemFromCharacter(pchar, "Lukes_letter");
		PlaySound("Interface\important_item");
		LAi_SetStayType(pchar);
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, PChar, "", 1.5);
	break;
	case "Plata1":
		sld = characterFromID("Maks");
		pchar = GetMainCharacter();
		PlaySound("Interface\took_item");
		AddMoneyToCharacter(pchar, 10000);
		LAi_SetSitType(sld);
		Lai_SetPlayerType(pchar);
	break;
	case "ChangeLukesHome":
		sld = CharacterFromID("Old Friend");
		sld.City = RandomCityEnemy();
		Log_TestInfo(sld.City);
		ChangeCharacterAddressGroup(sld,RandomHouse(sld),"goto","goto1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, Pchar,"", 20.0,10.0)
		Pchar.Luke.City = sld.City;
		DeleteAttribute(Pchar,"Quest.Luke");
		AddQuestRecord("Silence_Price","4");
		AddQuestUserData("Silence_Price","sSex",GetSexPhrase("ся","ась"));
		Pchar.quest.GetSpawnPirate.win_condition.l1 = "Location";
		Pchar.quest.GetSpawnPirate.win_condition.l1.location = "LaVega_town";
		Pchar.quest.GetSpawnPirate.function = "GetSpawnPirate";
	break;
	case "PirateGoOut":
		sld = CharacterFromID("Anri");
		LAi_ActorRunToLocation(sld,"reload", "reload1","none","","","",20.0);
		AddQuestRecord("Silence_Price","5");
		chrDisableReloadToLocation = false;

		Pchar.quest.PirateComeToIsabella.win_condition.l1 = "Timer";
		Pchar.quest.PirateComeToIsabella.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		Pchar.quest.PirateComeToIsabella.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		Pchar.quest.PirateComeToIsabella.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		Pchar.quest.PirateComeToIsabella.function = "PirateComeToIsabella";

		Pchar.quest.PirateComeToIsabellaLoose.win_condition.l1 = "Timer";
		Pchar.quest.PirateComeToIsabellaLoose.win_condition.l1.date.hour = 3;
		Pchar.quest.PirateComeToIsabellaLoose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		Pchar.quest.PirateComeToIsabellaLoose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		Pchar.quest.PirateComeToIsabellaLoose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		Pchar.quest.PirateComeToIsabellaLoose.function = "PirateComeToIsabellaLoose";
	break;
	case "PirateGoOut1":
		sld = CharacterFromID("Anri");
		LAi_ActorRunToLocation(sld,"reload", "reload1","none","","","",20.0);
		AddQuestRecord("Silence_Price", "5_3");
		AddQuestUserData("Silence_Price", "sCityName", XI_ConvertString("Colony" + Pchar.Luke.City + "Acc"));
		LAi_LocationDisableOfficersGen("Shore32", false);
		GiveItem2Character(pchar,"book2_7");
		GiveItem2Character(pchar,"book2_6");
		PlaySound("Interface\important_item.wav");
	break;
	case "PrepareFightAnri":
		sld = CharacterFromID("Anri");
		sTemp = "AnriChrist";
		LAi_SetImmortal(sld, false);
		LAi_group_MoveCharacter(sld, sTemp);
		LAi_group_FightGroups(sTemp, LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(sld, true);
		LAi_SetFightMode(pchar, true);
		LAi_Group_SetCheck(sTemp, "AfterBatleAnri");
	break;
	case "AfterBatleAnri":
		AddQuestRecord("Silence_Price", "5_2");
		AddQuestUserData("Silence_Price", "sCityName", XI_ConvertString("Colony" + Pchar.Luke.City + "Acc"));
		LAi_LocationDisableOfficersGen("Shore32", false);
	break;
	case "LukeFight":
		chrDisableReloadToLocation = true;
		sld = CharacterFromID("Old Friend");
		sTemp = "Artist";
		LAi_SetImmortal(sld, false);
		LAi_group_MoveCharacter(sld, sTemp);
		GiveItem2Character(sld,"cirass5");
		EquipCharacterbyItem(sld,"cirass5");
		LAi_SetCheckMinHP(sld, 1, true, "QuestPreEnd");
		LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(sTemp, LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(pchar,true);
	break;
	case "QuestPreEnd":
		sld = CharacterFromID("Old Friend");
		sld.Dialog.CurrentNode = "SecondQuest_4";
		LAi_SetFightMode(sld, false);
		LAi_SetFightMode(pchar, false);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, Pchar, "", 20.0, 1.0);
	break;
	case "LukeOut":
		sld = CharacterFromID("Old Friend");
		LAi_SetActorType(pchar);
		LAi_SetImmortal(sld, true);
		LaunchBlastGrenade(pchar);
		PlaySound("People Fight\rifle_fire1.wav");
		pchar.chr_ai.poison = 1 + 30 + 20 + 40;
		pchar.chr_ai.Blooding = 50;
		MarkCharacter(pchar,"FX_Blood");
		Log_Info(GetConvertStrWithReplace("Variable_quests_reaction_144", "Logs.txt", "#space#", " "));
		Log_Info(GetConvertStrWithReplace("Variable_quests_reaction_145", "Logs.txt", "#space#", " "));
		AddCharacterHealth(pchar, -20);
		StartLookAfterCharacter(sld.id);
		LAi_ActorRunToLocation(sld,"reload","reload1", "none", "", "", "", 2.0);
		DoQuestFunctionDelay("MaksCome", 2.0);
	break;
	case "AddGuardians":
	for (i = 0; i < 3; i++)
	{
		sTemp = "off_" + NationShortName(sti(Colonies[FindColony(Pchar.Luke.City)].nation)) + "_" + (rand(1) + 1);
		sld = GetCharacter(NPC_GenerateCharacter("Maks_Guard" + i, sTemp, "man", "man", 30, sti(Colonies[FindColony(Pchar.Luke.City)].nation), -1, false));
		SelAllPerksToNotPchar(sld);
		sld.dialog.filename = "Quest\SilencePrice\Maks.c";
		sld.Dialog.CurrentNode = "Guardians";
		LAi_group_MoveCharacter(sld, "Maks1");
		FantomMakeCoolFighter(sld, 30, 90, 90, "blade28", "pistol5",300);
		ChangeCharacterAddressGroup(sld, Pchar.Luke.City.Loc, "reload", "reload1");
		GiveItem2Character(sld,"cirass3");
		EquipCharacterbyItem(sld,"cirass3");
		if(i < 2)
		{
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, Pchar, "", 20.0, 1.0);
		}
	}
	LAi_group_SetCheck("Maks1", "QuestEnd1");
	LAi_SetFightMode(pchar,false);
	sld = CharacterFromID("Maks");
	break;
	case "FightGuardians":
		LAi_group_FightGroups("Maks1", LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(pchar,true);
	break;
	case "QuestEnd1":
		chrDisableReloadToLocation = false;
		Pchar.quest.LukesEscape.win_condition.l1 = "ExitFromLocation";
		Pchar.quest.LukesEscape.win_condition.l1.location = Pchar.Luke.City.Loc;
		Pchar.quest.LukesEscape.function = "LukesEscape";
	break;
	case "HealingPoison":
		SetLaunchFrameFormParam(GetConvertStr("Variable_quests_reaction_7", "Frames.txt"), "Reload_To_Location", 0.1, 2.0);
		if(PChar.location == "Bridgetown_church")
		{
			SetLaunchFrameReloadLocationParam("Bridgetown_church", "barmen","bar1", "");
		}
		if(PChar.location == "Farmacia")
		{
			SetLaunchFrameReloadLocationParam("Farmacia", "barmen","bar2", "");
		}
		LaunchFrameForm();
		AddDataToCurrent(0, 1, 0);
		DeleteAttribute(PChar,"Luke.BadPoison");
		AddCharacterHealth(pchar, 50);
		AddQuestRecord("Silence_Price", "6_1");
		CloseQuestHeader("Silence_Price");
		pchar.questdata.IstoriaDavneyDrujby = 1;
		/*bDisableFastReload = true;		БЛОКИРОВКА ПОСЫЛЬНОГО ПО ИСТОРИИ ДАВНЕЙ ЖРАЖБЫ
		Pchar.quest.IDD_Pochta_1.win_condition.l1 = "ExitFromLocation";
		Pchar.quest.IDD_Pochta_1.win_condition.l1.location = Pchar.location;
		Pchar.quest.IDD_Pochta_1.function = "IDD_Pochta_1";*/
	break;
		//конец История давней дружбы
		//Евент с искателем лазутчиков Lipsar//
	case "SeekerFight":
		sld = CharacterFromID("SpySeeker");
		LAi_SetImmortal(sld, false);
		LAi_Group_MoveCharacter(sld, "SpySeeker");
		LAi_group_SetRelation("SpySeeker", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_Group_FightGroups(PLAYER_GROUP, "SpySeeker", true);
		LAi_SetFightMode(sld, true);
		LAi_SetFightMode(pchar, true);
		LAi_Group_SetCheck("SpySeeker","OpenTheDoors");
	break;
	case "SpySeekerGood":
		sld = CharacterFromID("SpySeeker");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5.0);
		chrDisableReloadToLocation = false;
	break;
	//Евент с искателем лазутчиков Lipsar//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////  	КВЕСТЫ "Проклятие Дальних Морей" НАЧАЛО  	///	 		АВТОР Sinistra				//////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================  Квест "Альбрехт".  =======================
		case "PDM_Albreht_Vhod":
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
            sld = CharacterFromID("Albreht_Zalpfer");
			sld.dialog.filename = "Quest\PDM\Albreht_Zalpfer.c";
			sld.dialog.currentnode = "Ja_1";
			PlaceCharacter(sld, "goto", PChar.location);
			RemovePassenger(pchar, sld);
			RemoveCharacterCompanion(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			SetTimerCondition("PDM_Albreht_Arhitector", 0, 0, 30, false);	//Через 30 дней откроется здание архитектора
        break;
		
		case "PDM_Albreht_Arhitector":
			Locations[FindLocation("PortRoyal_town")].reload.l23.disable = false;
        break;
//========================  Квест "Проклятый идол".  =======================

		case "PDM_CI_SpawnJC":
			sld = GetCharacter(NPC_GenerateCharacter("James_Callow", "ozg_green", "man", "man", 15, PIRATE, -1, false));
			sld.name	= GetConvertStr("Variable_quests_reaction_0.1.1", "Names.txt");											//Джеймс Кэллоу
			sld.lastname	= GetConvertStr("Variable_quests_reaction_0.2.1", "Names.txt");
			sld.model	= "ozg_green";
			GiveItem2Character(sld, "blade34");
			EquipCharacterByItem(sld, "blade34");
			sld.Dialog.Filename = "Quest\PDM\Cursed_Idol.c";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("LaVega_tavern", "sit_base3");
			ChangeCharacterAddressGroup(sld,"LaVega_tavern","sit","sit_base3");
		break;

		case "PDM_Callow_sadis_na_stul":
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "sit", "sit_front3");
			LAi_SetSitType(pchar);
			//LAi_SetSitType(npchar);
			sld = CharacterFromID("James_Callow")
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "PDM_Callow_vstaem":
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
		break;

		case "PDM_Callow_RodjerFin":
			sld = CharacterFromID("James_Callow")
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "CollowRad_1";
		break;

		case "PDM_Callow_RadPoka":
			sld = CharacterFromID("James_Callow")
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
		break;

		case "PDM_FraOff_Bitva_1_Posle":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			sld = CharacterFromID("James_Callow")
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "CollowNeRad_1";
			AddQuestRecord("PDM_Cursed_Idol", "3");
			SetTimerFunction("PDM_PI_Skelety_v_more", 0, 0, 1);		//У-у-у страшно!!!
			SetTimerFunction("PDM_PI_Vernut_Gorod", 0, 0, 1);
		break;

		case "PDM_Callow_poradomoy":
			sld = CharacterFromID("James_Callow")
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Callow_POBEDA_1";
			AddQuestRecord("PDM_Cursed_Idol", "9");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_LocationFightDisable(loadedLocation, true);

			sld = CharacterFromID("Tortuga_usurer")
			sld.dialog.filename = "Usurer_dialog.c";
			sld.dialog.currentnode = "First time";
		break;

		case "PDM_PI_Skelety_on_Ship":
            pchar.quest.Munity = "";
			
			StartQuestMovie(true, true, true);
			//ChangeShowIntarface();
			//locCameraFromToPos(-3.20, 7.00, -3.40, false, 20.00, -4.00, -25.00);
			locCameraToPos(-3.20, 7.00, -3.40, false);
			
			sTemp = "shipowner_"+(rand(28)+1);
			sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Matrosiki_10", sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_46", "Names.txt", "#space#", " ");
			sld.lastname = "";
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Matros_preduprejdaet";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			for (i=6; i<=9; i++)
			{
				sTemp = "shipowner_"+(rand(28)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Matrosiki_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
				sld.lifeday = 0;
				LAi_CharacterDisableDialog(sld);
				PlaceCharacter(sld, "goto", "random");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto4", "", -1);
			DoQuestCheckDelay("PDM_PI_Skelety_on_Ship_2", 3.0);
        break;
		
		case "PDM_PI_Skelety_on_Ship_2":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PDM_PI_Matrosiki_10")
            LAi_ActorDialogDelay(sld, pchar, "", 0.0);
        break;
		
		case "PDM_PI_Skelety_on_Ship_3":
			EndQuestMovie();
		
			DoQuestFunctionDelay("PDM_PI_Vykl_Music", 1.0);
            InterfaceStates.Buttons.Save.enable = 1;
            LAi_SetFightMode(Pchar, true);
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_146", "Logs.txt", "#space#", " "));
			//Скелеты
			for (i=1; i<=6; i++)
			{
				sTemp = "skel_"+(rand(3)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_"+i, sTemp, "skeleton", "skeleton", sti(pchar.rank), PIRATE, -1, true));;
				PlaceCharacter(sld, "goto", "random_free");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				DeleteAttribute(sld, "items");
				AddMoneyToCharacter(sld, 66);
				AddItems(sld, "mineral6", rand(100)-40);
				AddItems(sld, "mineral10", rand(15)-5);
				AddItems(sld, "compcraft_flint", rand(3));
			}
            ChangeCrewExp(PChar, "Soldiers", 2); // бонус на подавление
            LAi_group_SetHearRadius("EnemyFight", 100.0);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

            LAi_group_SetCheck("EnemyFight", "PDM_PI_Dead_Skelety");
		break;

        case "PDM_PI_Dead_Skelety":
			Log_SetStringToLog(GetConvertStrWithReplace("Variable_quests_reaction_147", "Logs.txt", "#space#", " "));
			if (pchar.rank >= 1 && pchar.rank <= 6) AddCharacterCrew(pchar, -30);
			if (pchar.rank >= 7 && pchar.rank <= 12) AddCharacterCrew(pchar, -70));
			if (pchar.rank >= 13 && pchar.rank <= 18) AddCharacterCrew(pchar, -120));
			if (pchar.rank >= 19) AddCharacterCrew(pchar, -200));
            InterfaceStates.Buttons.Save.enable = 1;
            pchar.quest.Munity = "Deads";
            LAi_SetFightMode(Pchar, false);
        break;
//========================  Квест "Новая Родина".  =======================

		case "PDM_HugoSeaHavana":
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"none","","");
		break;

		case "PDM_Lesopilka_Vremy":
			AddQuestRecord("PDM_Novaya_Rodina", "8");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","а"));
			Group_SetAddress("PDM_HUGO_GAL", "none", "", "");
		break;

		case "PDM_Lesopilka_SJ":
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"Havana_Town","goto","goto2");
			sld.dialog.filename   = "Quest\PDM\Novaya_Rodina.c";
			sld.dialog.currentnode   = "Final_1";
			PChar.quest.PDM_Lesopilka_Vremy.over = "yes";
		break;

		case "PDM_Lesopilka_SJNashel":
			AddQuestRecord("PDM_Novaya_Rodina", "7");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","а"));
			PChar.quest.PDM_Lesopilka_Vremy.over = "yes";
			PChar.quest.PDM_Lesopilka_SJ.over = "yes";

			PChar.quest.PDM_Zoloto_ne_tonet_BITVA_na_sushe.win_condition.l1 = "location";
			PChar.quest.PDM_Zoloto_ne_tonet_BITVA_na_sushe.win_condition.l1.location = "Shore27";
			PChar.quest.PDM_Zoloto_ne_tonet_BITVA_na_sushe.function = "PDM_Zoloto_ne_tonet_BITVA_na_sushe";

			PChar.quest.PDM_ZNT_SJ_GLOBAL.win_condition.l1 = "MapEnter";
			PChar.quest.PDM_ZNT_SJ_GLOBAL.win_condition = "PDM_ZNT_Otmena_SOKR";
		break;

		case "PDM_ZolNeTon_PobNaSush":
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"Havana_Town","goto","goto2");
			sld.city = "Havana";
			sld.dialog.filename   = "Quest\PDM\Novaya_Rodina.c";
			sld.dialog.currentnode   = "Final_1";
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			TakeItemFromCharacter(pchar, "PDM_SJ_Angl_Gal");
			chrDisableReloadToLocation = false;
			pchar.GenQuestBox.Dominica_Grot.box1.items.icollection = 5;
			pchar.GenQuestBox.Dominica_Grot.box1.items.indian10 = 1;
			pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry5 = 300;
			pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry17 = 300;
			SetQuestHeader("PDM_Novaya_Rodina");
			AddQuestRecord("PDM_Novaya_Rodina", "9");
			PChar.quest.PDM_ZNT_SJ_GLOBAL.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingLight", 30);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 30);
			AddCharacterExpToSkill(pchar, "Fencing", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;

		case "PDM_ZNT_Otmena_SOKR":
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"none","","");
			PChar.quest.PDM_Zoloto_ne_tonet_BITVA_na_sushe.over = "yes";
			AddQuestRecord("PDM_Novaya_Rodina", "10");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("PDM_Novaya_Rodina");
			pchar.questdata.NovayaRodina = 1;
			AddCharacterExpToSkill(pchar, "Leadership", -30);
			AddCharacterExpToSkill(pchar, "FencingLight", -30);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -30);
			AddCharacterExpToSkill(pchar, "Fencing", -30);
			AddCharacterExpToSkill(pchar, "Pistol", -30);
			AddCharacterExpToSkill(pchar, "Fortune", -30);
		break;

//========================  Квест "Охота на ведьму".  =======================

		case "PDM_ONV_Nachalo":
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Isp_sekr_guber", "trader_16", "man", "man", 10, SPAIN, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_47", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_48", "Names.txt", "#space#", " ");
			LAi_SetCitizenType(sld);
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "First_time";
			sld.sex = "man";
			sld.City = "Beliz";
			sld.location	= "Beliz_town";
			LAi_SetLoginTime(sld, 6.0, 21.99);
			sld.talker = 7;
			sld.nation = SPAIN;
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			ChangeCharacterAddressGroup(sld,"Beliz_town","goto","goto5");
			
			locations[FindLocation("Beliz_TownhallRoom")].id.label = "House";
			//locations[FindLocation("Beliz_TownhallRoom")].id.label = "TownhallRoom";
		break;

		case "PDM_ONV_BARTO_Ischezni":
			sld = CharacterFromID("PDM_Isp_sekr_guber")
			ChangeCharacterAddressGroup(sld,"none","","");
		break;

		case "PDM_ONV_Clara_Ischezni":
			sld = CharacterFromID("PDM_ONV_Carla")
			ChangeCharacterAddressGroup(sld,"none","","");
		break;

		case "PDM_ONV_Vkomnate":
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Isp_sekr_guber", "trader_16", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld,"Beliz_TownhallRoom","goto","goto9");
			LAi_KillCharacter(sld);

			pchar.GenQuestBox.Beliz_TownhallRoom.box2.items.PDM_ONV_Kluch = 1;

			PChar.quest.PDM_ONV_TRUP_2.win_condition.l1 = "locator";
			PChar.quest.PDM_ONV_TRUP_2.win_condition.l1.location = "Beliz_TownhallRoom";
			PChar.quest.PDM_ONV_TRUP_2.win_condition.l1.locator_group = "goto";
			PChar.quest.PDM_ONV_TRUP_2.win_condition.l1.locator = "goto5";
			PChar.quest.PDM_ONV_TRUP_2.win_condition = "PDM_ONV_Vkomnate_Trup";

			PChar.quest.PDM_ONV_TRUP_3.win_condition.l1 = "locator";
			PChar.quest.PDM_ONV_TRUP_3.win_condition.l1.location = "Beliz_TownhallRoom";
			PChar.quest.PDM_ONV_TRUP_3.win_condition.l1.locator_group = "box";
			PChar.quest.PDM_ONV_TRUP_3.win_condition.l1.locator = "box2";
			PChar.quest.PDM_ONV_TRUP_3.win_condition = "PDM_ONV_Vkomnate_Trup";

			PChar.quest.PDM_ONV_TRUP_4.win_condition.l1 = "locator";
			PChar.quest.PDM_ONV_TRUP_4.win_condition.l1.location = "Beliz_TownhallRoom";
			PChar.quest.PDM_ONV_TRUP_4.win_condition.l1.locator_group = "barmen";
			PChar.quest.PDM_ONV_TRUP_4.win_condition.l1.locator = "bar2";
			PChar.quest.PDM_ONV_TRUP_4.win_condition = "PDM_ONV_Vkomnate_Trup";
		break;

		case "PDM_ONV_Vkomnate_Trup":
			PChar.quest.PDM_ONV_TRUP_2.over = "yes";
			PChar.quest.PDM_ONV_TRUP_3.over = "yes";
			PChar.quest.PDM_ONV_TRUP_4.over = "yes";
			AddQuestRecord("PDM_Ohota_na_vedmu", "4");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			PChar.quest.PDM_ONV_kluch.win_condition.l1 = "item";
			PChar.quest.PDM_ONV_kluch.win_condition.l1.item = "PDM_ONV_kluch";
			PChar.quest.PDM_ONV_kluch.win_condition = "PDM_ONV_VstaemKDveri";
		break;

		case "PDM_ONV_VstaemKDveri":
			PChar.quest.PDM_ONV_LOCA.win_condition.l1 = "locator";
			PChar.quest.PDM_ONV_LOCA.win_condition.l1.location = "Beliz_TownhallRoom";
			PChar.quest.PDM_ONV_LOCA.win_condition.l1.locator_group = "reload";
			PChar.quest.PDM_ONV_LOCA.win_condition.l1.locator = "reload1";
			PChar.quest.PDM_ONV_LOCA.win_condition = "PDM_ONV_VhodKGubernatoru";
		break;

		case "PDM_ONV_VhodKGubernatoru":
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload1", false);
			PlaySound("Interface\key.wav");
			TakeItemFromCharacter(pchar, "PDM_ONV_kluch");

			sld = CharacterFromID("Beliz_Mayor")
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "RazgovorSGuberom";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_SoldatGub_1", "sold_spa_1", "man", "man", 10, SPAIN, -1, false));
			sld.city = "Beliz";
			ChangeCharacterAddressGroup(sld, "Beliz_townhall", "goto", "governor1");
			FantomMakeCoolFighter(sld, 50, 100, 100, "blade27", "pistol6", 50);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "Soldat15";
			sld.greeting = "GR_Spainguard";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_SoldatGub_2", "sold_spa_3", "man", "man", 10, SPAIN, -1, false));
			sld.city = "Beliz";
			ChangeCharacterAddressGroup(sld, "Beliz_townhall", "goto", "goto6");
			FantomMakeCoolFighter(sld, 50, 100, 100, "blade27", "pistol6", 50);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "Soldat15";
			sld.greeting = "GR_Spainguard";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
		break;

		case "PDM_ONV_STRAJIschezni":
			sld = CharacterFromID("PDM_ONV_SoldatGub_1")
			ChangeCharacterAddressGroup(sld,"none","","");
			sld = CharacterFromID("PDM_ONV_SoldatGub_2")
			ChangeCharacterAddressGroup(sld,"none","","");
		break;

		case "PDM_ONV_SVOBODA_URA":			
			LocatorReloadEnterDisable("Beliz_town", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload2", false);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload3", false);
			LocatorReloadEnterDisable("Beliz_Townhall", "reload3", false);
			LocatorReloadEnterDisable("Beliz_townhall", "reload2", false);

			sld = CharacterFromID("Beliz_Mayor")
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";

			pchar.questTemp.PDM_ONV_Detectiv_Tavern_NET = true;
		break;
		
		case "PDM_ONV_VernutBezZadaniya":			
			LocatorReloadEnterDisable("Beliz_town", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload2", false);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload3", false);
			LocatorReloadEnterDisable("Beliz_Townhall", "reload3", false);
			LocatorReloadEnterDisable("Beliz_townhall", "reload2", false);

			sld = CharacterFromID("Beliz_Mayor")
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
		break;

		case "PDM_ONV_Vzaimno":
			LAi_KillCharacter(pchar);
			ChangeCharacterAddressGroup(CharacterFromID("PDM_ONV_Sin"), "none", "", "");
		break;

		/*case "PDM_ONV_KaznVedmi":
			sld = CharacterFromID("PDM_ONV_Inkvizitor")
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "reload8_1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			sld.lifeday = 0;
			sld.dialog.currentnode   = "Inqizitor_Kazn_nachalo_1";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_1", "girl_2", "woman", "woman", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto17");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_2", "citiz_7", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "reload10_3");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_3", "citiz_4", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "reload10_2");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Podjigatel", "off_spa_1", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "reload8_3");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_4", "citiz_8", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "houseSp21_1");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_5", "citiz_1", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_6", "citiz_2", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_7", "citiz_10", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_8", "girl_8", "woman", "woman", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_9", "girl_9", "woman", "woman", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_10", "girl_10", "woman", "woman", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "houseSp21_2");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_11", "citiz_5", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "houseSp21_3");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = CharacterFromID("PDM_ONV_Carla")
			ChangeCharacterAddressGroup(sld, "Santiago_town", "merchant", "mrcActive2");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_12", "shipowner_13", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "reload10_3");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_13", "Priest_3", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_14", "BS_Gatry", "woman", "woman", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "merchant", "mrcActive1");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
		break;

		case "PDM_ONV_PodjIschezni":
			sld = CharacterFromID("PDM_ONV_Podjigatel")
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;

		case "PDM_ONV_InqIschzni":
			sld = CharacterFromID("PDM_ONV_Inkvizitor")
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;*/
		
		case "PDM_ONV_Kazn_NEW":
			sld = CharacterFromID("PDM_ONV_Carla")
			sld.lifeday = 0;
			AddQuestRecord("PDM_Ohota_na_vedmu", "14");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.PDM_ONV_VedmaKaznena = true;
		break;

//========================  Квест "Потерянное кольцо".  =======================

		case "PDM_PK_Ubita":
			AddQuestRecord("PDM_Poteryanoe_Koltso", "4");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","а"));
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("Josephine_Lodet")
			sld.dialog.currentnode   = "Konets";

			AddCharacterExpToSkill(pchar, "FencingLight", 100);
			AddCharacterExpToSkill(pchar, "Fencing", 100);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 100);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, SPAIN, -7);
		break;

//========================  Квест "Непутёвый казначей".  =======================

		case "PDM_NK_Nachalo":
			sld = GetCharacter(NPC_GenerateCharacter("Andreas_Fickler", "usurer_5", "man", "man", 10, HOLLAND, -1, false));
			sld.name	= GetConvertStr("Variable_quests_reaction_0.3.1", "Names.txt");
			sld.lastname	= GetConvertStr("Variable_quests_reaction_0.4.1", "Names.txt");
			sld.City = "Villemstad";
			sld.Dialog.Filename = "Quest\PDM\Neputyovy_kaznachey.c";
			LAi_SetCitizenType(sld);
			LAi_SetLoginTime(sld, 6.0, 21.99);
			sld.talker = 5;
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld,"Villemstad_town","officers","houseSp5_2");
		break;

		case "PDM_NK_Viktor":
			AddCharacterExpToSkill(pchar, "FencingLight", 100);
			AddCharacterExpToSkill(pchar, "Fencing", 100);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 100);
			AddCharacterExpToSkill(pchar, "Pistol", 100);
			AddCharacterExpToSkill(pchar, "Sneak", -120);
			AddCharacterExpToSkill(pchar, "Commerce", -100);

			AddQuestRecord("PDM_Neputyovy_kaznachey", "4");

			sld = CharacterFromID("Andreas_Fickler")
			sld.dialog.filename   = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode   = "Fickler_11";
		break;

		case "PDM_NK_Litsenzia":
			if (GetDaysContinueNationLicence(SPAIN) < 20) GiveNationLicence(SPAIN, 20);
			if (GetDaysContinueNationLicence(ENGLAND) < 20) GiveNationLicence(ENGLAND, 20);
			TakeItemFromCharacter(pchar, "Litsenzia");
		break;
		
//========================  Квест "Проклятая жара".  =======================		

		case "PDM_PJ_Arest_0":
			sld = GetCharacter(NPC_GenerateCharacter("PDM_PJ_Strajnik_4", "sold_fra_4", "man", "man", 10, FRANCE, -1, true));
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";
			ChangeCharacterAddressGroup(sld,"FortFrance_town","goto","goto34");
			LAi_ActorGoToLocator(sld, "officers", "reloadPr1_1", "", -1);
		
			sld = GetCharacter(NPC_GenerateCharacter("PDM_PJ_Strajnik_3", "sold_fra_3", "man", "man", 10, FRANCE, -1, true));
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";
			ChangeCharacterAddressGroup(sld,"FortFrance_town","goto","goto34");
			LAi_ActorGoToLocator(sld, "officers", "reloadPr1_3", "PDM_PJ_Arest_1_1", -1);
			
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			StartQuestMovie(true, true, true);
			locCameraFromToPos(-35.50, 7.00, 25.00, true, -20.00, 0.00, 15.00);
		break;

		case "PDM_PJ_Arest_1":
			sld = CharacterFromID("PDM_PJ_Strajnik_3")
			LAi_ActorAnimation(sld, "barman_idle", "", 1.5);
			DoQuestCheckDelay("PDM_PJ_Arest_2", 1.5);
			DoQuestCheckDelay("PDM_PJ_Arest_1_2", 0.8);
			sld = CharacterFromID("PDM_PJ_Strajnik_4")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_PJ_Strajnik_1"));
		break;
		
		case "PDM_PJ_Arest_1_1":
			locCameraFromToPos(-31.50, 6.00, 40.00, true, -20.00, 0.00, 0.00);
			DoQuestCheckDelay("PDM_PJ_Arest_1", 0.4);
		break;
		
		case "PDM_PJ_Arest_1_2":
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		break;
		
		case "PDM_PJ_Arest_2":
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			LAi_ActorGoToLocator(sld, "reload", "reload6_back", "", -1);
			DoQuestCheckDelay("PDM_PJ_Arest_3", 1.0);
		break;
		
		case "PDM_PJ_Arest_3":
			sld = CharacterFromID("PDM_PJ_Strajnik_3")
			LAi_ActorGoToLocator(sld, "reload", "reload6_back", "", -1);
			sld = CharacterFromID("PDM_PJ_Strajnik_4")
			LAi_ActorGoToLocator(sld, "officers", "reload6_3", "", -1);
			DoQuestCheckDelay("PDM_PJ_Arest_4", 6.0);
		break;
		
		case "PDM_PJ_Arest_4":
			DoQuestReloadToLocation("FortFrance_prison", "reload", "reload1", "PDM_PJ_Arest_5");
			EndQuestMovie();
		break;
		
		case "PDM_PJ_Arest_5":
			sld = GetCharacter(NPC_GenerateCharacter("PDM_PJ_Strajnik_5", "sold_fra_2", "man", "man", 10, FRANCE, -1, true));
			sld.name	= GetConvertStr("Variable_quests_reaction_0.5.1", "Names.txt");
			sld.lastname	= GetConvertStr("Variable_quests_reaction_0.6.1", "Names.txt");
			sld.dialog.filename   = "Common_Soldier.c";
			sld.dialog.currentnode   = "First time";
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";
			ChangeCharacterAddressGroup(sld,"FortFrance_town","officers","soldier_uniq2");
			
			sld = CharacterFromID("PDM_PJ_Strajnik_2")
			LAi_SetLoginTime(sld, 6.0, 21.99);
			
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			CloseQuestHeader("PDM_Proklyataya_Jara");
			pchar.questdata.ProklyatayaJara = 1;
			AddQuestRecord("PDM_Proklyataya_Jara", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 130);
			AddCharacterExpToSkill(pchar, "Sneak", 130);
		break;
		
		case "PDM_PJ_Protrezvel":
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			sld.dialog.filename   = "Common_Soldier.c";
			sld.dialog.currentnode   = "First time";
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";
		break;
		
//========================  Квест "Клан Ламбрини".  =======================

		case "PDM_CL_Lodka":
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(loadedLocation, true);
			LAi_group_SetRelation("", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		break;

		case "PDM_CL_Antonio_Ubit":
			sld = CharacterFromID("PDM_CL_Anto2")
			ChangeCharacterAddressGroup(sld, "none", "", "");
			Group_SetAddress("PDM_el_tib", "none", "", "");
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_2_1";
			DeleteAttribute(pchar, "questTemp.PDM_CL_Ishem");
			AddQuestRecord("PDM_Clan_Lambrini", "3");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("ен","на"));
		break;

		case "PDM_CL_PVT":
			sld = CharacterFromID(pchar.LambriniPGG)
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_1_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_base2");
		break;

		case "PDM_CL_Na_Plyaj":
			sld = CharacterFromID("PDM_CL_Antonio3")
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			sld.lifeday = 0;
			sld.dialog.currentnode   = "Antonio_6_1";
		break;

		case "PDM_CL_Na_Plyaj_2":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID(pchar.LambriniPGG);
			LAi_SetActorType(sld);
			DeleteAttribute(sld, "chr_ai.disableDlg");
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_6_1";
		break;

		case "LambriniPGG_CheckHP":
			LAi_group_SetRelation("PDM_CL_PirVrag_Status", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);

			LAi_SetActorTypeNoGroup(pchar);
			LAi_SetFightMode(PChar, false);
			DoQuestFunctionDelay("PDM_CL_PlayerType", 2.0);

			sld = CharacterFromID("PDM_CL_Antonio3");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorFollow(sld, PChar, "", -1);

			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_SetActorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			sld = CharacterFromID(pchar.LambriniPGG);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.currentnode   = "LambriniPGG_1_1";
			DoQuestFunctionDelay("PDM_CL_Pokupatel_Speech", 0);

			for (i=3; i<=14; i++)	//пираты м контрабандисты
			{
				sld = CharacterFromID("PDM_CL_PirVrag_"+i);
				LAi_SetActorTypeNoGroup(sld);
				sld.LifeDay = 0;
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}

			for (i=19; i<=27; i++)	//испанцы 1
			{
				sld = CharacterFromID("SraDruzya_"+i)
				LAi_SetActorTypeNoGroup(sld);
				LAi_SetFightMode(sld, true);
				LAi_LockFightMode(sld, true);
				sld.LifeDay = 0;
			}
		break;

		case "PDM_CL_Finish":
			LAi_SetFightMode(pchar, false);

			sld = CharacterFromID("PDM_CL_Antonio3");
			ChangeCharacterAddressGroup(sld, "PortRoyal_town", "none", "");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Antonio4", "SpaOfficer2", "man", "man", Rank, SPAIN, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_49", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_50", "Names.txt", "#space#", " ");
			sld.greeting = "GR_Spainguard";
			Blade = GetGeneratedItem("blade34");
			GiveItem2Character(sld, Blade);
			EquipCharacterbyItem(sld, Blade);
			ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto7");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.lifeday = 0;
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_8_1";
		break;

		case "LambriniPGG_Late":
			if(CheckAttribute(pchar,"LambriniPGGInPrison") && CheckAttribute(pchar,"LambriniPGGPlata"))
			{
				DeleteAttribute(pchar,"LambriniPGGPlata");
				AddQuestRecord("PDM_Clan_Lambrini", "10");
				CloseQuestHeader("PDM_Clan_Lambrini");
				pchar.questdata.ClanLambrini = 1;
				AddQuestUserData("PDM_Clan_Lambrini", "sName", GetFullName(CharacterFromID(pchar.LambriniPGG)));
				PGG_ChangeRelation2MainCharacter(CharacterFromID(pchar.LambriniPGG), -200);
				SetTimerCondition("LambriniPGG_Freedom", 0, 0, 27, false);
			}
		break;
		case "LambriniPGG_Freedom":
			if(CheckAttribute(pchar,"LambriniPGGInPrison"))
			{
				DeleteAttribute(pchar,"LambriniPGGInPrison");
				PGG_ChangeRelation2MainCharacter(CharacterFromID(pchar.LambriniPGG), -200);
			}
			sld = CharacterFromID(pchar.LambriniPGG);
			sld.dialog.filename = "PGG_dialog.c";
			sld.dialog.currentnode = "First time";
			DeleteAttribute(sld, "PGGAi.DontUpdate");
			DeleteAttribute(sld, "LambiniAsoleda");
			DeleteAttribute(sld, "PGGAi.Task.SetSail");
			DeleteAttribute(pchar, "LambriniPGG");
			DeleteAttribute(pchar, "LambriniPGGPlata");

		break;

//========================  Квест "Аптекарь".  =======================
		
		case "PDM_Apt_Prihov_v_buhtu":
			PChar.quest.PDM_Apt_Derevo_1.win_condition.l1 = "locator";
			PChar.quest.PDM_Apt_Derevo_1.win_condition.l1.location = "Common_jungle_01";
			PChar.quest.PDM_Apt_Derevo_1.win_condition.l1.locator_group = "randitem";
			PChar.quest.PDM_Apt_Derevo_1.win_condition.l1.locator = "randitem1";
			PChar.quest.PDM_Apt_Derevo_1.win_condition = "PDM_Apt_Nashel_Derevo";

			PChar.quest.PDM_Apt_Derevo_2.win_condition.l1 = "locator";
			PChar.quest.PDM_Apt_Derevo_2.win_condition.l1.location = "Common_jungle_01";
			PChar.quest.PDM_Apt_Derevo_2.win_condition.l1.locator_group = "randitem";
			PChar.quest.PDM_Apt_Derevo_2.win_condition.l1.locator = "randitem2";
			PChar.quest.PDM_Apt_Derevo_2.win_condition = "PDM_Apt_Nashel_Derevo";

			PChar.quest.PDM_Apt_Derevo_3.win_condition.l1 = "locator";
			PChar.quest.PDM_Apt_Derevo_3.win_condition.l1.location = "Common_jungle_01";
			PChar.quest.PDM_Apt_Derevo_3.win_condition.l1.locator_group = "randitem";
			PChar.quest.PDM_Apt_Derevo_3.win_condition.l1.locator = "randitem3";
			PChar.quest.PDM_Apt_Derevo_3.win_condition = "PDM_Apt_Nashel_Derevo";

			AddQuestRecord("PDM_Aptekar", "5");
		break;

		case "PDM_Apt_Nashel_Derevo":
			GiveItem2Character(PChar, "PDM_Derevo_Teshkali");

			sld = CharacterFromID("Pablo_Loco")
			sld.dialog.filename   = "Quest\PDM\Aptekar.c";
			sld.dialog.currentnode   = "Nashel_Derevo";

			AddQuestRecord("PDM_Aptekar", "6");

			PChar.quest.PDM_Apt_Derevo_1.over = "yes";
			PChar.quest.PDM_Apt_Derevo_2.over = "yes";
			PChar.quest.PDM_Apt_Derevo_3.over = "yes";
			
			chrDisableReloadToLocation = true;
			DoQuestCheckDelay("PDM_Apt_Canibaly_Attack", 3.5);
		break;
		
		case "PDM_Apt_Canibaly_Attack":
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_148", "Logs.txt", "#space#", " "));
			for (i=1; i<=3; i++)
			{
				sTemp = "Canib_"+(rand(5)+1);					
				sld = GetCharacter(NPC_GenerateCharacter("PDM_Apt_Canib_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			for (i=4; i<=5; i++)
			{
				sTemp = "Canib_"+(rand(5)+1);					
				sld = GetCharacter(NPC_GenerateCharacter("PDM_Apt_Canib_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "randitem",  "randitem5");
			}
			for (i=6; i<=7; i++)
			{
				sTemp = "Canib_"+(rand(5)+1);					
				sld = GetCharacter(NPC_GenerateCharacter("PDM_Apt_Canib_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "randitem",  "randitem10");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_Apt_Canibaly_Pobeda");
		break;
		
		case "PDM_Apt_Canibaly_Pobeda":
			chrDisableReloadToLocation = false;
		break;

		case "PDM_Apt_Lodka_Postroena":
			sld = CharacterFromID("Pablo_Loco")
			sld.dialog.filename   = "Quest\PDM\Aptekar.c";
			sld.dialog.currentnode   = "Pablo_Loco_Lodka_Postroena";
		break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   	КВЕСТЫ "Проклятие Дальних Морей" КОНЕЦ
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  	КВЕСТЫ "Пираты Карибского Моря" НАЧАЛО  	 ////	 		   Sinistra			    ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================  Квест "Странные вещи творятся на архипелаге"  =============================

		case "PKM_SvtvA_SpawnQuest":
			//******Странные вещи творятся на архипелаге******
			//Девушки ищут детей
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvtvA_Devushka_1", "girl_9", "woman", "woman", 1, HOLLAND, -1, false));
			sld.name	= GetConvertStr("Variable_quests_reaction_0.7.1", "Names.txt");
			sld.lastname	= GetConvertStr("Variable_quests_reaction_0.8.1", "Names.txt");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "First time";
			LAi_SetStayType(sld);
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetImmortal(sld, true);
			sld.City = "Marigo";
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld,"Marigo_town","quest","quest4");
			
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvtvA_Devushka_2", "girl_6", "woman", "woman", 1, HOLLAND, -1, false));
			sld.name	= GetConvertStr("Variable_quests_reaction_0.9.1", "Names.txt");
			sld.lastname	= GetConvertStr("Variable_quests_reaction_0.10.1", "Names.txt");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "First time";
			LAi_SetStayType(sld);
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetImmortal(sld, true);
			sld.City = "Marigo";
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld,"Marigo_town","quest","quest5");
			
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvtvA_Devushka_3", "girl_1", "woman", "woman", 1, HOLLAND, -1, false));
			sld.name	= GetConvertStr("Variable_quests_reaction_0.11.1", "Names.txt");
			sld.lastname	= GetConvertStr("Variable_quests_reaction_0.12.1", "Names.txt");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "First time";
			LAi_SetStayType(sld);
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetImmortal(sld, true);
			sld.City = "Marigo";
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld,"Marigo_town","quest","quest3");
		break;

		case "PKM_SvtvA_SprositKapitanov_v_more":
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_SprositKapitanov_v_more");
		break;
		
		case "PKM_SvtvA_DostavkaPisma_Gorod_1":
			LAi_LocationFightDisable(loadedLocation, true);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			sld = GetCharacter(NPC_GenerateCharacter("SatanaElita_11", "Animists1", "man", "man", 60, PIRATE, -1, true));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_51", "Names.txt", "#space#", " ");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 70, 100, 100, BLADE_LONG, "", 200);
			LAi_SetStayType(sld);
			sld.talker = 6;
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Satanist_v_gorode_1";
			ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest1");
			DeleteAttribute(sld, "items");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SatanaElita_"+i, "Animists1", "man", "man", 60, PIRATE, -1, true));
				FantomMakeCoolFighter(sld, 70, 100, 100, BLADE_LONG, "pistol1", 200);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest1");
				DeleteAttribute(sld, "items");
				sld.SaveItemsForDead = true;
				GiveItem2Character(sld, "PKM_SvtvA_znachok");
				AddItems(sld, "mineral3", rand(7)-4);
			}
			for (i=6; i<=8; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SatanaElita_"+i, "Animists1_mush_x", "man", "mushketer", 70, PIRATE, -1, false));
				sld.MusketerDistance = 0;
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto19");
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_SetActorType(sld);
				LAi_ActorTurnToCharacter(sld, pchar);
				DeleteAttribute(sld, "items");
				sld.SaveItemsForDead = true;
				GiveItem2Character(sld, "PKM_SvtvA_znachok");
				AddItems(sld, "mineral3", rand(7)-4);
			}
			for (i=9; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SatanaElita_"+i, "Animists1_mush_x", "man", "mushketer", 70, PIRATE, -1, false));
				sld.MusketerDistance = 0;
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto1");
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_SetActorType(sld);
				LAi_ActorTurnToCharacter(sld, pchar);
				DeleteAttribute(sld, "items");
				sld.SaveItemsForDead = true;
				GiveItem2Character(sld, "PKM_SvtvA_znachok");
				AddItems(sld, "mineral3", rand(7)-4);
			}
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvtvA_Jitel1", "Citiz_2", "man", "man", 1, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto20");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "soldiers", "protector4", "", -1);
			
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvtvA_Jitel2", "Citiz_5", "man", "man", 1, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto20");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto21", "", -1);
			
			DoQuestCheckDelay("PKM_SvtvA_Satamist_lutuet_1", 1.3);
			DoQuestCheckDelay("PKM_SvtvA_Satamist_lutuet_2", 1.9);
			LAi_SetActorType(pchar);
		break;
		
		case "PKM_SvtvA_Satamist_lutuet_1":
			sld = CharacterFromID("SatanaElita_2")
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "shot", "PKM_SvtvA_Satamist_lutuet_3", 1.0);
		break;
		case "PKM_SvtvA_Satamist_lutuet_2":
			sld = CharacterFromID("SatanaElita_5")
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "shot", "PKM_SvtvA_Satamist_lutuet_4", 1.0);
		break;
		
		case "PKM_SvtvA_Satamist_lutuet_3":
			LAi_KillCharacter(CharacterFromID("PKM_SvtvA_Jitel1"));
		break;
		case "PKM_SvtvA_Satamist_lutuet_4":
			LAi_KillCharacter(CharacterFromID("PKM_SvtvA_Jitel2"));
			
			LAi_SetPlayerType(pchar);
		break;
		
		case "PKM_SvtvA_DostavkaPisma_Gorod_2":		//Битва в городе
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("PKM_Animists", "9");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("PKM_Animists", "sSex2", GetSexPhrase("ся","ась"));
			pchar.questTemp.PKM_SvtvA_SanJuanChurch_1_Dobro = "Church1";
			PChar.quest.PKM_SvtvA_SJ_B1.over = "yes";
			PChar.quest.PKM_SvtvA_SJ_B2.over = "yes";
			PChar.quest.PKM_SvtvA_SJ_B3.over = "yes";
			pchar.questTemp.PKM_SvtvA_DralisVG = "DVG";
		break;
		
		case "PKM_SvtvA_DostavkaPisma_Buhta_2":		//Битва в бухте без разговора
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("PKM_Animists", "10");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("PKM_Animists", "sSex2", GetSexPhrase("ся","ась"));
			pchar.questTemp.PKM_SvtvA_SanJuanChurch_1_Dobro = "Church1";
			PChar.quest.PKM_SvtvA_SJ_B1.over = "yes";
			PChar.quest.PKM_SvtvA_SJ_B2.over = "yes";
			PChar.quest.PKM_SvtvA_SJ_B3.over = "yes";
		break;
		
		case "PKM_SvtvA_DostavkaPisma_Buhta_3":		//Битва в бухте с разговором и отказываемся отдавать письмо
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("PKM_Animists", "11");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("ёл","ла"));
			pchar.questTemp.PKM_SvtvA_SanJuanChurch_1_Dobro = "Church1";
			PChar.quest.PKM_SvtvA_SJ_B1.over = "yes";
			PChar.quest.PKM_SvtvA_SJ_B2.over = "yes";
			PChar.quest.PKM_SvtvA_SJ_B3.over = "yes";
		break;
		
		case "PKM_SvtvA_DostavkaPisma_Buhta_1":
			LAi_LocationFightDisable(loadedLocation, true);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_1", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_52", "Names.txt", "#space#", " ");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, sti(pchar.rank), 30, 30, "blade5", "", 0);
			LAi_SetActorType(sld);
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Satanist_v_buhte_1";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto1");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			DeleteAttribute(sld, "items");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			for (i=2; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Satanist_"+i, "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 30, 30, "blade5", "", 0);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto1");
				LAi_ActorFollow(sld, pchar, "", -1);
				DeleteAttribute(sld, "items");
				sld.SaveItemsForDead = true;
				GiveItem2Character(sld, "PKM_SvtvA_znachok");
				AddItems(sld, "mineral3", rand(7)-4);
			}		
		break;
		
		case "PKM_SvtvA_Маёнез_потопили":		//Поражение
			PChar.quest.PKM_SvtvA_TA_horosho.over = "yes";
			
			AddQuestRecord("PKM_Animists", "16");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("ен","на"));
			AddQuestUserData("PKM_Animists", "sSex2", GetSexPhrase("","а"));
			CloseQuestHeader("PKM_Animists");
		break;
		
		case "PKM_SvtvA_Ангела_потопили":		//Победа
			AddQuestRecord("PKM_Animists", "17");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("PKM_Animists", "sSex2", GetSexPhrase("ёл","ла"));
			
			sld = CharacterFromID("Maltese");
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.DeckDialogNode = "Знакомство с Жаком";
		break;
		
		case "PKM_SvtvA_Zasada2":
			LAi_LocationFightDisable(loadedLocation, true);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_1", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_53", "Names.txt", "#space#", " ");
			sld.lastname = "";
			LAi_SetActorType(sld);
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Satanist_zasada2";
			ChangeCharacterAddressGroup(sld, pchar.location, "patrol",  "patrol17");
			LAi_ActorDialog(sld, pchar, "", 1.4, 0);
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			for (i=2; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Satanist_"+i, "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
				sld.DontChangeBlade = true;
				sld.DontChangeGun = true;
				sld.DeleteFood = true;
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "patrol",  "patrol17");
				LAi_ActorFollow(sld, characterFromID("Satanist_1"), "", -1);
				sld.SaveItemsForDead = true;
				GiveItem2Character(sld, "PKM_SvtvA_znachok");
				AddItems(sld, "mineral3", rand(7)-4);
			}
		break;
		
		case "PKM_SvtvA_Zasada2_Pobeda":
			AddQuestRecord("PKM_Animists", "20");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			pchar.questTemp.PKM_SvtvA_PismoKlermon = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Krisa", "Priest_3", "man", "man", 10, PIRATE, -1, true));  //Предатель
			FantomMakeCoolFighter(sld, sti(pchar.rank), 50, 50, "blade5", "", 120);
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_54", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_55", "Names.txt", "#space#", " ");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			sld.SaveItemsForDead = true;
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "barmen", "bar1");
		break;
		
		case "PKM_SvtvA_Нападение_в_церкви":
			sld = CharacterFromID("Satanist_Krisa");
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Сатанист_крыса";
			LAi_ActorDialogNow(sld, Pchar, "", -1);
		break;
		
		case "PKM_SvtvA_Нападение_в_церкви_Победа":
			LAi_LocationFightDisable(loadedLocation, true);
			LAi_SetFightMode(pchar, false);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			LAi_SetActorType(pchar);
			
			sld = CharacterFromID("FortFrance_Priest");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			sld = CharacterFromID("Maltese");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			DoQuestFunctionDelay("PKM_SvtvA_Malta_na_pomosh_2", 1.5);
		break;
		
		case "PKM_SvtvA_PriestVernuDialog":
			sld = CharacterFromID("FortFrance_Priest");
			LAi_SetPriestType(sld);
			sld.dialog.filename = "Common_church.c";
			sld.dialog.currentnode = "First time";
		break;
		
		case "PKM_SvtvA_MalteseMertv":
			LAi_KillCharacter(pchar);
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_150", "Logs.txt", "#space#", " "));
		break;
		
		case "PKM_SvtvA_IdemSledom":
			pchar.GenQuestBox.CommonRoom_MH4.box2.items.PKM_SvtvA_znachok = 666;
			pchar.GenQuestBox.CommonRoom_MH4.box2.items.PKM_SvtvA_pismo3 = 1;
			
			PChar.quest.PKM_SvtvA_IdemSledom.win_condition.l1 = "Timer";
			PChar.quest.PKM_SvtvA_IdemSledom.win_condition.l1.date.hour = sti(GetTime() + 1);
			PChar.quest.PKM_SvtvA_IdemSledom.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PKM_SvtvA_IdemSledom.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PKM_SvtvA_IdemSledom.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PKM_SvtvA_IdemSledom.win_condition = "PKM_SvtvA_IdemSledom2";
			
			PChar.quest.PKM_SvtvA_Chitaem.win_condition.l1 = "item";
			PChar.quest.PKM_SvtvA_Chitaem.win_condition.l1.item = "PKM_SvtvA_pismo3";
			PChar.quest.PKM_SvtvA_Chitaem.win_condition = "PKM_SvtvA_Chitaem";			
		break;
		
		case "PKM_SvtvA_IdemSledom2":
			DeleteAttribute(&locations[FindLocation("CommonRoom_MH4")], "box2");
		break;
		
		case "PKM_SvtvA_TuremchikQuest":
			DoQuestCheckDelay("PKM_SvtvA_TuremchikQuest2", 0.2);
			
			SetTimerCondition("PKM_SvtvA_TuremchikKonets", 0, 0, 1, false);
		break;
		
		case "PKM_SvtvA_Chitaem":
			ChangeItemDescribe("PKM_SvtvA_amulet", "itmdescr_PKM_SvtvA_amulet_Sila");
		break;
		
		case "PKM_SvtvA_TuremchikQuest2":
			sld = CharacterFromID("PortPaxJailOff");
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Разговор с тюремщиком";
		break;
		
		case "PKM_SvtvA_TuremchikKonets":
			sld = CharacterFromID("Satanist_Uchitel");
			LAi_KillCharacter(sld);
			
			sld = CharacterFromID("PortPaxJailOff");
			sld.dialog.filename = "Common_Prison.c";
			sld.dialog.currentnode = "First_officer";
			
			CloseQuestHeader("PKM_Animists");
		break;
		
		case "PKM_SvtvA_TuremchikDialog":
			sld = CharacterFromID("PortPaxJailOff");
			sld.dialog.filename = "Common_Prison.c";
			sld.dialog.currentnode = "First_officer";
		break;
		
		case "PKM_SvtvA_UchitelPassakir":
			Island_SetReloadEnableGlobal("PuertoRico", false);
			bQuestDisableMapEnter = true;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			DoQuestCheckDelay("PKM_SvtvA_UchitelNaPalube", 3.0);
		break;
		
		case "PKM_SvtvA_UchitelNaPalube":
			DoQuestReloadToLocation("Ship_deck", "goto", "goto4", "PKM_SvtvA_UchitelNaPalube2");
		break;
		
		case "PKM_SvtvA_UchitelNaPalube2":
			for (i=1; i<=4; i++)
			{
				sTemp = "shipowner_"+(rand(28)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PKM_SvtvA__Matrosiki_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
				sld.lifeday = 0;
				LAi_CharacterDisableDialog(sld);
				PlaceCharacter(sld, "goto", "random");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Satanist_Uchitel");
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Обманываем Учителя";
			ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto3");
			DoQuestCheckDelay("PKM_SvtvA_UchitelNaPalube3", 2.8);
			LAi_ActorDialogDelay(sld, pchar, "", 2.8);
		break;
		
		case "PKM_SvtvA_UchitelNaPalube3":
			LAi_SetPlayerType(pchar);
		break;
		
		case "PKM_SvtvA_UchitelvTaverne":
			sld = CharacterFromID("Satanist_Uchitel");
			FantomMakeCoolFighter(sld, 12, 60, 60, BLADE_LONG, "", 100);
			sld.SaveItemsForDead = true;
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(10)-2);
			AddItems(sld, "jewelry1", 3);
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Обманываем Учителя_4";
			ChangeCharacterAddressGroup(sld, "SanJuan_tavern_upstairs", "goto", "goto3");
			LAi_ActorDialogNow(sld, Pchar, "", -1);
		break;
		
		case "PKM_SvtvA_UbivaemUchitelya":
			Island_SetReloadEnableGlobal("PuertoRico", true);
			bQuestDisableMapEnter = false;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.location.from_sea = "SanJuan_town";
			
			AddQuestRecord("PKM_Animists", "33");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			
			locations[FindLocation("Guadeloupe_deadlock")].models.day.charactersPatch = "jungle9_patch";
			locations[FindLocation("Guadeloupe_deadlock")].models.night.charactersPatch = "jungle9_patch";
			Locations[FindLocation("Guadeloupe_deadlock")].models.always.l4 = "jungle9_nowall";
			
			PChar.quest.LogovoSatanistov.win_condition.l1 = "location";
			PChar.quest.LogovoSatanistov.win_condition.l1.location = "Cave_Satanists";
			PChar.quest.LogovoSatanistov.win_condition = "LogovoSatanistov";
		break;
		
		case "LogovoSatanistov":
			chrDisableReloadToLocation = true;
			scareOfficers(70);
			
			//КУХНЯ
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Kuhnya_1", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			LAi_SetHP(sld, 1.0, 1.0);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_SetSitType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "sit",  "sit32");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			AddItems(sld, "food2", 12);
			GiveItem2Character(sld, "mineral9");
			AddItems(sld, "food3", 12);
			LAi_group_MoveCharacter(sld, "Satanist_Kuhnya");
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Kuhnya_2", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			LAi_SetHP(sld, 1.0, 1.0);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_SetSitType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "sit",  "sit34");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			GiveItem2Character(sld, "mineral9");
			AddItems(sld, "mineral3", rand(7)-4);
			AddItems(sld, "food5", 9);
			GiveItem2Character(sld, "mineral9");
			LAi_group_MoveCharacter(sld, "Satanist_Kuhnya");
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Kuhnya_3", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			FantomMakeCoolFighter(sld, sti(pchar.rank), 50, 50, "blade5", "", 0);
			LAi_SetHP(sld, 1.0, 1.0);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "lay_2", "", 2.0);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "sit",  "sit36");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			LAi_group_MoveCharacter(sld, "Satanist_Kuhnya");
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Kuhnya_4", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			LAi_SetHP(sld, 1.0, 1.0);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_SetSitType(sld);
			sld.nonTable = true;
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "sit",  "sit35");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			LAi_group_MoveCharacter(sld, "Satanist_Kuhnya");
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Kuhnya_5", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			LAi_SetHP(sld, 1.0, 1.0);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_SetActorType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto9");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			LAi_group_MoveCharacter(sld, "Satanist_Kuhnya");
			sld.lifeday = 0;
			
			PChar.quest.PKM_SvtvA_KuhnyaStels1.win_condition.l1 = "NPC_Death";
			PChar.quest.PKM_SvtvA_KuhnyaStels1.win_condition.l1.character = "Satanist_Kuhnya_1";
			PChar.quest.PKM_SvtvA_KuhnyaStels1.win_condition = "PKM_SvtvA_KuhnyaStels";
			
			PChar.quest.PKM_SvtvA_KuhnyaStels2.win_condition.l1 = "NPC_Death";
			PChar.quest.PKM_SvtvA_KuhnyaStels2.win_condition.l1.character = "Satanist_Kuhnya_2";
			PChar.quest.PKM_SvtvA_KuhnyaStels2.win_condition = "PKM_SvtvA_KuhnyaStels";
			
			PChar.quest.PKM_SvtvA_KuhnyaStels3.win_condition.l1 = "NPC_Death";
			PChar.quest.PKM_SvtvA_KuhnyaStels3.win_condition.l1.character = "Satanist_Kuhnya_3";
			PChar.quest.PKM_SvtvA_KuhnyaStels3.win_condition = "PKM_SvtvA_KuhnyaStels";
			
			PChar.quest.PKM_SvtvA_KuhnyaStels4.win_condition.l1 = "NPC_Death";
			PChar.quest.PKM_SvtvA_KuhnyaStels4.win_condition.l1.character = "Satanist_Kuhnya_4";
			PChar.quest.PKM_SvtvA_KuhnyaStels4.win_condition = "PKM_SvtvA_KuhnyaStels";
			
			PChar.quest.PKM_SvtvA_KuhnyaStels5.win_condition.l1 = "NPC_Death";
			PChar.quest.PKM_SvtvA_KuhnyaStels5.win_condition.l1.character = "Satanist_Kuhnya_5";
			PChar.quest.PKM_SvtvA_KuhnyaStels5.win_condition = "PKM_SvtvA_KuhnyaStels";
			
			//ТЮРЬМА
			
			//Пленники
			sld = GetCharacter(NPC_GenerateCharacter("Plennik_u_satanistov_1", "barmen_6", "man", "man", sti(pchar.rank), PIRATE, -1, false));
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Спасите, помогите1";
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto20");
			
			sld = GetCharacter(NPC_GenerateCharacter("Plennik_u_satanistov_2", "officer_20", "man", "man", sti(pchar.rank), PIRATE, -1, false));
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Спасите, помогите2";
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto21");
			
			sld = GetCharacter(NPC_GenerateCharacter("Plennik_u_satanistov_3", "Slave3", "man", "man", sti(pchar.rank), PIRATE, -1, false));
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode ="Спасите, помогите3";
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto23");
			
			sld = GetCharacter(NPC_GenerateCharacter("Plennik_Dominges", "Priest_4", "man", "man", sti(pchar.rank), PIRATE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_56", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_57", "Names.txt", "#space#", " ");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Домингес в клетке";
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto22");
			
			//Охрана
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Turma_1", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			LAi_SetGuardianType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Satanist_Turma");
			
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Turma_2", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			LAi_SetGuardianType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto4");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Satanist_Turma");
			
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Turma_3", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			LAi_SetGuardianType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto19");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Satanist_Turma");
			
			
			LAi_group_SetRelation("Satanist_Turma", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("Satanist_Turma", 4.0);
			LAi_group_SetHearRadius("Satanist_Turma", 2.0);
			LAi_group_SetSayRadius("Satanist_Turma", 10.0);
			
			//ВХОД ЛОГОВА
						
			//Охрана входа
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Vhod_1", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			LAi_SetGuardianType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto16");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Satanist_Vhod");
			
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Vhod_2", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			LAi_SetGuardianType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto17");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Satanist_Vhod");
			
			LAi_group_SetRelation("Satanist_Vhod", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("Satanist_Vhod", 4.0);
			LAi_group_SetHearRadius("Satanist_Vhod", 2.0);
			LAi_group_SetSayRadius("Satanist_Vhod", 10.0);
			
			//Красивое убийство		
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Vhod_3", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			LAi_SetGuardianType(sld);
			LAi_SetHP(sld, 1.0, 1.0);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto7");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Satanist_Vhod2");
			
			LAi_group_SetRelation("Satanist_Vhod2", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("Satanist_Vhod2", 4.0);
			LAi_group_SetHearRadius("Satanist_Vhod2", 0.0);
			LAi_group_SetSayRadius("Satanist_Vhod2", 0.0);
			
			//ТРОННЫЙ ЗАЛ
			
			//Чёрное Солнце
			sld = GetCharacter(NPC_GenerateCharacter("Chernoe_Solntse", "Animists2", "man", "man", sti(pchar.rank) + 10 + MOD_SKILL_ENEMY_RATE*3, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, sti(pchar.rank) + 10 + MOD_SKILL_ENEMY_RATE*3, 100, 100, "katar", "pistol6", 1000);
			LAi_SetHP(sld,800,800);
			LAi_SetDltHealth(sld, 110.0);
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_58", "Names.txt", "#space#", " ");
			sld.lastname = "";
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "sit",  "sit1");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			LAi_SetImmortal(sld, true);
			SetCharacterPerk(sld, "Energaiser");
			GiveItem2Character(sld, "cirass3");
			EquipCharacterbyItem(sld, "cirass3");
			sld.SuperShooter  = true;
			if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
			LAi_SetCheckMinHP(sld, 10, true, "PKM_SvtvA_Lord_Haos_Pobeda_no_ne_sovsem");
			
			//Одержимый#1
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Oderjim_1", "Animists1", "man", "man_worship", sti(pchar.rank), PIRATE, -1, false));
			LAi_SetActorType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto50");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse_sluga");	
			LAi_SetImmortal(sld, true);
			
			//Одержимый#2
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Oderjim_2", "Animists1", "man", "man_worship", sti(pchar.rank), PIRATE, -1, false));
			LAi_SetActorType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto51");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse_sluga");
			LAi_SetImmortal(sld, true);
			
			//Одержимый#3
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Oderjim_3", "Animists1", "man", "man_worship", sti(pchar.rank), PIRATE, -1, false));
			LAi_SetActorType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto52");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse_sluga");
			LAi_SetImmortal(sld, true);
			
			//Одержимый#4
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Oderjim_4", "Animists1", "man", "man_worship", sti(pchar.rank), PIRATE, -1, false));
			LAi_SetActorType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto53");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse_sluga");
			LAi_SetImmortal(sld, true);
			
			//Одержимый#5
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Oderjim_5", "Animists1", "man", "man_worship", sti(pchar.rank), PIRATE, -1, false));
			LAi_SetActorType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto54");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse_sluga");
			LAi_SetImmortal(sld, true);
			
			//Солдат#1
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_1", "Animists1", "man", "man", sti(pchar.rank) + 3, PIRATE, -1, true));
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto55");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			LAi_SetImmortal(sld, true);
			
			//Солдат#2
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_2", "Animists1", "man", "man", sti(pchar.rank) + 3, PIRATE, -1, true));
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto56");
			sld.SaveItemsForDead = true;
			GiveItem2Character(sld, "PKM_SvtvA_znachok");
			AddItems(sld, "mineral3", rand(7)-4);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			sld.DeleteFood = true;
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			LAi_SetImmortal(sld, true);
			
			PChar.quest.PKM_SvtvA_Altar.win_condition.l1 = "locator";
			PChar.quest.PKM_SvtvA_Altar.win_condition.l1.location = "Cave_Satanists";
			PChar.quest.PKM_SvtvA_Altar.win_condition.l1.locator_group = "quest";
			PChar.quest.PKM_SvtvA_Altar.win_condition.l1.locator = "quest1";
			PChar.quest.PKM_SvtvA_Altar.function = "PKM_SvtvA_RazgovorZKnyazem";
			
			//
			DoQuestFunctionDelay("PKM_SvtvA_SatanistyAnimation", 1.0);
		break;
		
		case "PKM_SvtvA_KuhnyaStels":
			PChar.quest.PKM_SvtvA_KuhnyaStels1.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels2.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels3.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels4.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels5.over = "yes";
			sld = CharacterFromID("Satanist_Kuhnya_1");
			LAi_SetWarriorType(sld);
			LAi_SetHP(sld, 180.0, 180.0);
			LAi_group_MoveCharacter(sld, "Satanist_Kuhnya");
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto", "goto42");
			sld = CharacterFromID("Satanist_Kuhnya_2");
			LAi_SetWarriorType(sld);
			LAi_SetHP(sld, 180.0, 180.0);
			LAi_group_MoveCharacter(sld, "Satanist_Kuhnya");
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto", "goto41");
			sld = CharacterFromID("Satanist_Kuhnya_3");
			LAi_SetWarriorType(sld);
			LAi_SetHP(sld, 180.0, 180.0);
			LAi_group_MoveCharacter(sld, "Satanist_Kuhnya");
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto", "goto39");
			sld = CharacterFromID("Satanist_Kuhnya_4");
			LAi_SetWarriorType(sld);
			LAi_SetHP(sld, 180.0, 180.0);
			LAi_group_MoveCharacter(sld, "Satanist_Kuhnya");
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto", "goto38");
			sld = CharacterFromID("Satanist_Kuhnya_5");
			LAi_SetWarriorType(sld);
			LAi_SetHP(sld, 180.0, 180.0);
			LAi_group_MoveCharacter(sld, "Satanist_Kuhnya");
			LAi_group_SetRelation("Satanist_Kuhnya", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Satanist_Kuhnya", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("Satanist_Kuhnya", "PKM_SvtvA_Satanist_Kuhnya_Pobeda");
		break;
		
		case "PKM_SvtvA_Satanist_Kuhnya_Pobeda":
			pchar.questTemp.PKM_SvtvA_Satanist_Kuhnya_Pobeda = true;
			sld = CharacterFromID("Satanist_Kuhnya_1");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Kuhnya_2");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Kuhnya_3");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Kuhnya_4");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Kuhnya_5");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;
		
		case "PKM_SvtvA_Lord_Haos_Padet":
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_157", "Logs.txt", "#space#", " "));
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_158", "Logs.txt", "#space#", " "));
			
			sld = CharacterFromID("Chernoe_Solntse");
			LAi_SetHP(sld,1200,1200);
			LAi_SetCurHP(sld, 500.0);
			LAi_SetDltHealth(sld, 4.0);
			
			if (!CheckAttribute(pchar, "questTemp.PKM_SvtvA_Satanist_Kuhnya_Pobeda"))
			{
				for (i=1; i<=5; i++)
				{
					sld = CharacterFromID("Satanist_Kuhnya_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
				}
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Satanist_Turma_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Satanist_Vhod_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			}
			LAi_group_SetSayRadius("Chernoe_Solntse", 100.0);
			LAi_group_SetRelation("Chernoe_Solntse", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PKM_SvtvA_Lord_Haos_Pobeda_no_ne_sovsem":		
			DoQuestCheckDelay("hide_weapon", 1.2);
			sld = CharacterFromID("Chernoe_Solntse");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse_Konets");
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Лорд_Хаоса_3";
			LAi_ActorDialogNow(sld, Pchar, "", -1);
			LAi_SetImmortal(sld, true);
		break;
		
		case "PKM_SvtvA_Lord_Haos_Pobeda_no_ne_sovsem2":			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Plennik_u_satanistov_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Satanist_Kuhnya_Pobeda");
			
			PChar.quest.PKM_SvtvA_Bitva_s_Mefisto.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_Bitva_s_Mefisto.win_condition.l1.location = "Guadeloupe";
			PChar.quest.PKM_SvtvA_Bitva_s_Mefisto.win_condition = "PKM_SvtvA_Bitva_s_Mefisto";
			
			sld = CharacterFromID("Plennik_Dominges");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Спасение пленников";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);			
		break;
		
		case "PKM_SvtvA_Dominges_na_bort":
			sld = GetCharacter(NPC_GenerateCharacter("Plennik_Dominges", "Priest_4", "man", "man", 3, PIRATE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_59", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_60", "Names.txt", "#space#", " ");
			LAi_SetCitizenType(sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			chrDisableReloadToLocation = false;
			
			Pchar.quest.PKM_SvtvA_Dominges_Doma.win_condition.l1           = "location";
        	Pchar.quest.PKM_SvtvA_Dominges_Doma.win_condition.l1.location  = "SanJuan_town";
        	Pchar.quest.PKM_SvtvA_Dominges_Doma.win_condition              = "PKM_SvtvA_Dominges_Doma";
		break;
		
		case "PKM_SvtvA_Dominges_Doma":
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
            sld = CharacterFromID("Plennik_Dominges");
			PlaceCharacter(sld, "goto", PChar.location);
			RemovePassenger(pchar, sld);
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
	        sld.dialog.currentnode = "Домингес_спасён_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PKM_SvtvA_Bitva_s_Mefisto":
			Island_SetReloadEnableGlobal("Guadeloupe", false);
			bQuestDisableMapEnter = true;
		
			sld = GetCharacter(NPC_GenerateCharacter("Chernoe_Solntse2", "Animists2", "man", "man", sti(pchar.rank) + 10 + MOD_SKILL_ENEMY_RATE*3, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, sti(pchar.rank) + 10 + MOD_SKILL_ENEMY_RATE*3, 100, 100, "katar", "pistol6", 300);
			AddCharacterHealth(sld, 30);
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_61", "Names.txt", "#space#", " ");
			sld.lastname = "";
			FantomMakeCoolSailor(sld, SHIP_MEFISTO, GetConvertStr("Variable_quests_reaction_9", "ShipNames.txt"), CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
			RemoveItems(sld, "katar", 1);
			sld.DontRansackCaptain = true;
			sld.DontHitInStorm = true;
			sld.SinkTenPercent = false;
			sld.AlwaysSandbankManeuver = true;
			sld.SaveItemsForDead = true;
			sld.AnalizeShips = true;
			sld.GenQuest.CrewSatanistMode = true;
			
			GiveItem2Character(sld, "cirass3");
			EquipCharacterbyItem(sld, "cirass3");
			
			Group_FindOrCreateGroup("Enemy_Attack");
			Group_SetType("Enemy_Attack", "war");
			Group_AddCharacter("Enemy_Attack", "Chernoe_Solntse2");

			Group_SetGroupCommander("Enemy_Attack", "Chernoe_Solntse2");
			Group_SetPursuitGroup("Enemy_Attack", PLAYER_GROUP);
			Group_SetAddress("Enemy_Attack", "Guadeloupe", "quest_ships", "Quest_ship_1");
			Group_LockTask("Enemy_Attack");
			
			PChar.quest.PKM_SvtvA_Bitva_s_Mefisto_Pobeda.win_condition.l1 = "NPC_Death";
			PChar.quest.PKM_SvtvA_Bitva_s_Mefisto_Pobeda.win_condition.l1.character = "Chernoe_Solntse2";
			PChar.quest.PKM_SvtvA_Bitva_s_Mefisto_Pobeda.win_condition = "PKM_SvtvA_Bitva_s_Mefisto_Pobeda";
			AddQuestRecord("PKM_Animists", "35");
		break;
		
		case "PKM_SvtvA_Bitva_s_Mefisto_Pobeda":		
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			bQuestDisableMapEnter = false;
			
			pchar.questTemp.PKM_SvtvA_Clermon_Final = true;
			pchar.questTemp.PKM_SvtvA_Gubernator_Final = true;
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_1")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Verni_detey_11";
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_2")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Verni_detey_11";
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_3")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Verni_detey_11";
			
			AddQuestRecord("PKM_Animists", "36");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
		break;
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   	КВЕСТЫ "Пираты Карибского Моря" КОНЕЦ
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  	КВЕСТЫ "Сундук Мертвеца" НАЧАЛО  	 ////	 		   Sinistra			    ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================  Квест "Спасение на рифах".  =======================
		case "KSM_Snr_Alloka_Spawn":
			//Джеймс Аллока
			sld = GetCharacter(NPC_GenerateCharacter("KSM_Alloka", "trader_1", "man", "man", 10, ENGLAND, -1, false));
			sld.name	= GetConvertStr("Variable_quests_reaction_0.13.1", "Names.txt");
			sld.lastname	= GetConvertStr("Variable_quests_reaction_0.14.1", "Names.txt");
			sld.Dialog.Filename = "Quest\KSM\Spasenie_na_rifah.c";
			LAi_SetCitizenType(sld);
			LAi_SetLoginTime(sld, 6.0, 21.99);
			sld.talker = 7;
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld,"PortRoyal_town","goto","goto12");
		break;

		case "KSM_Snr_EndloosTraider":
			Island_SetReloadEnableLocal("Reefs", "reload_3", true)
			sld = CharacterFromID("KSM_Alloka")
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_RemoveLoginTime(sld);
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			
			Pchar.quest.KSM_Snr_Nashli_Ship.win_condition.l1           = "location";
        	Pchar.quest.KSM_Snr_Nashli_Ship.win_condition.l1.location  = "WreckedShip";
			PChar.quest.KSM_Snr_Nashli_Ship.function = "KSM_Snr_Nashli_Ship";
			SetQuestHeader("KSM_Spasenie_na_rifah");
			AddQuestRecord("KSM_Spasenie_na_rifah", "1");
		break;
		
		case "KSM_Snr_EndloosTraiderKill":
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			Island_SetGotoEnableLocal("Reefs", "reload_3", true);
			sld = CharacterFromID("KSM_Alloka")
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, false);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//Враги
			for (i=1; i<=6; i++)
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("CSM_Snr_Bandity_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "randitem",  "randitem1");
			}
			for (i=7; i<=11; i++)
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("CSM_Snr_Bandity_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto7");
			}
			for (i=12; i<=15; i++)
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("CSM_Snr_Bandity_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc15");
			}
			//Наши
			for (i=4; i<=12; i++)
			{
				if (pchar.sex != "skeleton")
				{
					sTemp = "shipowner_"+(rand(24)+1);
				}
				else
				{
					sTemp = "Skel_" + (rand(4)+1);
				}
				sld = GetCharacter(NPC_GenerateCharacter("KSM_Snr_Matrosiki_"+i, sTemp, "man", "man", sti(pchar.rank), sti(pchar.nation), -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc0");
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("KSM_Snr_Matrosiki_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "KSM_Snr_Pobeda");
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("KSM_Snr_MushketyPodhodyt", 8.0);			//Мушкетёры включаются в бой
			DoQuestCheckDelay("KSM_Snr_GlavnyZlodey", 22.0);
			EndQuestMovie();
			DialogExit();
		break;
		
		case "KSM_Snr_MushketyPodhodyt":
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("KSM_Snr_Mushkety_"+i);
				sld.MusketerDistance = 10;
			}
		break;
		
		case "KSM_Snr_GlavnyZlodey":
			sld = CharacterFromID("KSM_Alloka");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		break;
		
		case "KSM_Snr_Pobeda":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			
			AddQuestRecord("KSM_Spasenie_na_rifah", "2");
			CloseQuestHeader("KSM_Spasenie_na_rifah");
			pchar.questdata.SpasenieNaRifah = 1;
		break;
		
//========================  Квест "Деньги в рост".  =======================

		case "KSM_DVR_Pobeda":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(-8.51, 4.38, 39.93, true, -20.00, 2.00, 40.00);
			
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(PChar, "goto", "goto22");
			
			sld = CharacterFromID("Villemstad_usurer");
			GiveItem2Character(sld, "pistol1");
			sld.equip.gun = "pistol1";
			ChangeCharacterAddressGroup(sld, "Shore22", "goto", "goto22");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromId("KSM_DVR_Saiman"), "", -1);
			DoQuestCheckDelay("KSM_DVR_Zastrelil", 5.0);
		break;
		
		case "KSM_DVR_Zastrelil":
			sld = CharacterFromID("Villemstad_usurer");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("KSM_DVR_Saiman"));
			LAi_ActorAnimation(sld, "Shot", "KSM_DVR_Zastrelil_2", 1.8);
			DoQuestCheckDelay("KSM_DVR_Zastrelil_3", 0.9);
		break;
		
		case "KSM_DVR_Zastrelil_2":
			LAi_ActorTurnToCharacter(pchar, characterFromID("Villemstad_usurer"));
			DoQuestCheckDelay("KSM_DVR_Zastrelil_4", 1.5);
		break;
		
		case "KSM_DVR_Zastrelil_3":
			LAi_KillCharacter(characterFromID("KSM_DVR_Saiman"));
		break;
		
		case "KSM_DVR_Zastrelil_4":
			locCameraFollow();
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			
			sld = CharacterFromID("Villemstad_usurer");
			LAi_SetActorType(sld);
			sld.dialog.filename = "Quest\KSM\Dengi_v_rost.c";
			sld.dialog.currentnode = "dolg_bazar_1";
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
		break;
		
		case "KSM_DVR_Smotrim_2":
			ChangeCharacterAddressGroup(pchar, "Shore22", "smugglers", "smugglerload");
			sld = CharacterFromID("Villemstad_usurer");
			ChangeCharacterAddressGroup(sld, "Shore22", "smugglers", "smugglerload");
			DoQuestCheckDelay("KSM_DVR_Smotrim_3", 1.0);
		break;
		
		case "KSM_DVR_Smotrim_3":
			sld = CharacterFromID("Villemstad_usurer");
			LAi_SetActorType(sld);
			sld.dialog.filename = "Quest\KSM\Dengi_v_rost.c";
			sld.dialog.currentnode = "dolg_bazar_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
		break;
		
		case "KSM_DVR_RostovshikDomoy":
			sld = CharacterFromID("Villemstad_usurer");
			sld.City = "Villemstad";
			sld.location	= "Villemstad_Bank";
			sld.location.group = "barmen";
			sld.location.locator = "stay";
			sld.Dialog.Filename = "Usurer_dialog.c";
			sld.dialog.currentnode = "First time";
			sld.nation = HOLLAND;
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			RemoveGeometryFromLocation("Shore22", "smg");
		break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   	КВЕСТЫ "Сундук Мертвеца" КОНЕЦ
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  	КВЕСТЫ "ПРОКЛЯТЫЕ СУДЬБОЙ" НАЧАЛО  	 ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================  Квест "ЗАГАДОЧНЫЙ ОСТРОВ".  =======================

		case "KPS_ZO_JimSmit_Spawn":		
			PChar.quest.KPS_ZO_JimSmit_Tavern.win_condition.l1 = "location";		//Вход в локацию
			PChar.quest.KPS_ZO_JimSmit_Tavern.win_condition.l1.location = "Bridgetown_tavern";
			PChar.quest.KPS_ZO_JimSmit_Tavern.function = "MysteriousIslandPrepare";
			
			FreeSitLocator("Bridgetown_tavern", "sit_base3");
			sld = GetCharacter(NPC_GenerateCharacter("Jimm Smith", "panhandler_1", "man", "man", 1, PIRATE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_62", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_63", "Names.txt", "#space#", " ");
			sld.greeting = "Gr_Tavern_Mate";
			sld.Dialog.FileName = "Quest\KPS\MysteriousIsland\Jimm Smith.c";
			sld.Dialog.CurrentNode = "1";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit", "sit_base3");
		break;

		case "KPS_MysteriousIsland_1":		
			MysteriousIslandRetryTalkWithDubben();
		break;
		
		case "KPS_MysteriousIsland_ZDvkaute":
			sld = CharacterFromID("Zhofrua Djubben");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "", "", "none", "", "", "", 1);
		break;
		
		case "KPS_MysteriousIslandFirstGrotFightWin":		
			sld = CharacterFromID("Zhofrua Djubben");
			sld.Dialog.FileName = "Quest\KPS\MysteriousIsland\Characters.c";
			sld.Dialog.CurrentNode = "9";
			LAi_CharacterEnableDialog(sld);
			SetDialogCharacter2Character(PChar, sld, 20.0, false);
		break;
		
		case "KPS_MysteriousIslandRuins":
			for (i=1; i<=12; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Skelet_SantaLusiaRuins_"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 10+MOD_SKILL_ENEMY_RATE*3, PIRATE, 1, true));
				FantomMakeCoolFighter(sld, 10+MOD_SKILL_ENEMY_RATE*3, 90, 90, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol3"), MOD_SKILL_ENEMY_RATE*10);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				ChangeCharacterAddressGroup(sld, "Ruins", "goto",  "goto"+i);
			}
		break;
		
		case "KPS_MysteriousIslandDungeon":
			for (i=1; i<=44; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Skelet_SantaLusiaDungeon_"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 10+MOD_SKILL_ENEMY_RATE*3, PIRATE, 1, true));
				FantomMakeCoolFighter(sld, 10+MOD_SKILL_ENEMY_RATE*3, 90, 90, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol3"), MOD_SKILL_ENEMY_RATE*10);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				ChangeCharacterAddressGroup(sld, "dungeon_02", "monsters",  "monster"+i);
			}
			
			chrDisableReloadToLocation = true;
			CreateLocationParticles("shadowstar", "box", "private6", 1, 0, 0, "");
		break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  	СЮЖЕТНАЯ ЛИНЕЙКА "АНЖЕЛИКА ТИЧ"    НАЧАЛО  	 ////	 		   Sinistra			    ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////		
//========================  Квест "Мечты сбываются"  =======================			

		case "Draka_s_Kotesom_Pobeda":
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.2);
			LAi_RemoveCheckMinHP(pchar);
			sld = characterFromId("Gasten_Kotes");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_ActorAnimation(sld, "kneeling_1", "Draka_s_Kotesom_Pobeda_2", 5.0);
		break;
		
		case "Draka_s_Kotesom_Pobeda_2":
			sld = CharacterFromID("AT_pr_Rebekka")
			PlaceCharacter(sld, "goto", PChar.location);
			sld.dialog.currentnode = "Rebekka_posle_draki";
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "AT_pr_Piraty_v_grote_1":
			sld = CharacterFromID("AT_pr_Rebekka")
			ChangeCharacterAddressGroup(sld, "Hispaniola_Grot", "goto", "goto2");
			DoQuestFunctionDelay("AT_pr_Piraty_v_grote_2", 1.0);
			DoQuestFunctionDelay("AT_pr_Piraty_v_grote_1_1", 0.1);
			
			for (i=1; i<=2; i++)
			{
				sTemp = "pirate_"+(rand(24)+1);					
				sld = GetCharacter(NPC_GenerateCharacter("AT_pr_Piraty_"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto1");
			}
		break;
		
		case "AT_pr_Pobeda_v_grote":
			AddQuestRecord("AT_Mechty_Sbivautsya", "2");
			chrDisableReloadToLocation = false;
			
			SetLocationCapturedState("LaVega_town", true);
			locations[FindLocation("LaVega_town")].models.always.locatorsl3 = "LaVega_locators_quest";
			locations[FindLocation("LaVega_town")].models.night.charactersPatch = "LaVega_patch_night_quest";
			locations[FindLocation("LaVega_town")].models.always.locatorsl2 = "LaVega_1_quest";
			locations[FindLocation("LaVega_town")].type = "QuestTragic";
			
			PChar.quest.AT_pr_tragedia.win_condition.l1 = "location";
			PChar.quest.AT_pr_tragedia.win_condition.l1.location = "LaVega_town";
			PChar.quest.AT_pr_tragedia.function = "AT_pr_tragedia";
			PChar.quest.AT_pr_Korabl.win_condition.l1 = "ExitFromLocation";
			PChar.quest.AT_pr_Korabl.win_condition.l1.location = PChar.location;
			PChar.quest.AT_pr_Korabl.win_condition = "AT_pr_Korabl";
			
			sld = CharacterFromID("Gasten_Kotes")
			LAi_LoginInCaptureTown(sld, true);
			LAi_SetStayType(sld);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "Stoim_na_pirse";
			sld.talker = 5;
			ChangeCharacterAddressGroup(sld, "LaVega_town", "officers", "reload1_2");
		break;
		
		case "AT_pr_Korabl":
			pchar.MaxSailing = true;
		
			pchar.Ship.Type = GenerateShipExt(SHIP_BARKENTINE, true, pchar);
			pchar.Ship.name=GetConvertStrWithReplace("Variable_quests_reaction_64", "Names.txt", "#space#", " ");
			SetBaseShipData(pchar);
			ChangeCrewExp(pchar, "Sailors", 50);
			ChangeCrewExp(pchar, "Cannoners", 20);
			ChangeCrewExp(pchar, "Soldiers", 20);
			pchar.ship.Crew.Morale = 50;
			SetCharacterGoods(pchar, GOOD_FOOD, 200);
			SetCharacterGoods(pchar, GOOD_RUM, 50 + rand(100));
			SetCharacterGoods(pchar, GOOD_BALLS, 220);
			SetCharacterGoods(pchar, GOOD_BOMBS, 80);
			SetCharacterGoods(pchar, GOOD_POWDER, 240);
			AddCharacterCrew(pchar, -120);
			pchar.ship.HP = sti(pchar.ship.HP) - 450;
			pchar.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS16;
			realships[sti(pchar.ship.type)].SpeedRate = 14.0;
			pchar.location.from_sea = "LaVega_town";
			LocatorReloadEnterDisable("LaVega_town", "reload1_back", true);
			setWDMPointXZ("LaVega_town");
		break;
		
		case "AT_pr_Stoim_na_pirse_9":
			sld = CharacterFromID("Gasten_Kotes")
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			LocatorReloadEnterDisable("LaVega_town", "reload1_back", false);
			AddQuestRecord("AT_Mechty_Sbivautsya", "3");
			
			Island_SetReloadEnableGlobal("Hispaniola1", false);
			bQuestDisableMapEnter = true;
			pchar.wind.angle = 300.0;
			
			//Создаём вражеские корабли
			Group_FindOrCreateGroup("AT_Pir_Attack_1");
			Group_SetType("AT_Pir_Attack_1", "war");
            sld = GetCharacter(NPC_GenerateCharacter("AT_pr_1_CaptainAttack_1", "officer_"+(rand(42)+1), "man", "man", 1, PIRATE, -1, true));
            FantomMakeCoolSailor(sld, SHIP_GALEON, "", CANNON_TYPE_CANNON_LBS12, 15, 25, 15);
            FantomMakeCoolFighter(sld, 1, 10, 10, "blade2", "", 10);
    		Group_AddCharacter("AT_Pir_Attack_1", "AT_pr_1_CaptainAttack_1");
			Group_SetGroupCommander("AT_Pir_Attack_1", "AT_pr_1_CaptainAttack_1");
			Group_SetTaskAttack("AT_Pir_Attack_1", PLAYER_GROUP);
			Group_LockTask("AT_Pir_Attack_1");
			Group_SetAddress("AT_Pir_Attack_1", "Hispaniola1", "Quest_Ships", "Quest_ship_11");
			realships[sti(sld.ship.type)].SpeedRate = 7.0;
			
			Group_FindOrCreateGroup("AT_Pir_Attack_2");
			Group_SetType("AT_Pir_Attack_2", "war");
			sld = GetCharacter(NPC_GenerateCharacter("AT_pr_1_CaptainAttack_2", "officer_"+(rand(42)+1), "man", "man", 1, PIRATE, -1, true));
            FantomMakeCoolSailor(sld, SHIP_FLEUT, "", CANNON_TYPE_CULVERINE_LBS12, 15, 25, 15);
            FantomMakeCoolFighter(sld, 1, 10, 10, "blade2", "", 10);
    		Group_AddCharacter("AT_Pir_Attack_2", "AT_pr_1_CaptainAttack_2");
			Group_SetGroupCommander("AT_Pir_Attack_2", "AT_pr_1_CaptainAttack_2");
			Group_SetTaskAttack("AT_Pir_Attack_2", PLAYER_GROUP);
			Group_LockTask("AT_Pir_Attack_2");
			Group_SetAddress("AT_Pir_Attack_2", "Hispaniola1", "Quest_Ships", "Quest_ship_12");
			realships[sti(sld.ship.type)].SpeedRate = 7.0;
			
			sld = CharacterFromID("AT_pr_1_CaptainAttack_1")
			AddCharacterCrew(sld, -330);
			sld.ship.HP = sti(sld.ship.HP) - 2000;		
			sld = CharacterFromID("AT_pr_1_CaptainAttack_2")
			AddCharacterCrew(sld, -120);
			sld.ship.HP = sti(sld.ship.HP) - 700;
			
			PChar.quest.AT_pr_Bejim_ot_piratov.win_condition.l1 = "EnterToSea"
			PChar.quest.AT_pr_Bejim_ot_piratov.win_condition = "AT_pr_Bejim_ot_piratov";
		break;
		
		case "AT_pr_Bejim_ot_piratov":
			DoQuestFunctionDelay("AT_pr_Bejim_ot_piratov_2", 4.0);
			DoQuestFunctionDelay("AT_pr_Bejim_ot_piratov_3", 200.0);
			DoQuestFunctionDelay("AT_pr_Bejim_ot_piratov_4", 300.0);
			
			PChar.quest.AT_pr_Santo_Domin.win_condition.l1 = "location";
			PChar.quest.AT_pr_Santo_Domin.win_condition.l1.location = "SantoDomingo_town";
			PChar.quest.AT_pr_Santo_Domin.win_condition = "AT_pr_Santo_Domin";
			
			DeleteAttribute(pchar, "questTemp.AnjelikaTichPrologue");
			DeleteAttribute(pchar, "questTemp.AnjelikaTichPrologue2");
			DeleteAttribute(pchar, "questTemp.ATPNapelsy");
			
			PChar.quest.ATpr_UbiraemKorabli.win_condition.l1 = "MapEnter";
			PChar.quest.ATpr_UbiraemKorabli.win_condition = "ATpr_UbiraemKorabli";		
			
			SetTimerFunction("ATpr_SvobodaIgry", 0, 0, 5);		//Таймер провала миссии!!!
		break;
		
		case "ATpr_UbiraemKorabli":
			sld = CharacterFromID("AT_pr_1_CaptainAttack_1")
			sld.lifeday = 0;
			sld = CharacterFromID("AT_pr_1_CaptainAttack_2")
			sld.lifeday = 0;
			bDisableFastReload = false;
		break;
		
		case "AT_pr_Santo_Domin":			//Важный кейс
			sld = CharacterFromID("AT_pr_1_CaptainAttack_1")
			sld.lifeday = 0;
			sld = CharacterFromID("AT_pr_1_CaptainAttack_2")
			sld.lifeday = 0;
			
			LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload1_back", false);	//Важная реакция
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload3", false);	//Важная реакция
			LocatorReloadEnterDisable("LaVega_town", "reload4_back", false);	//Важная реакция
			bDisableFastReload = true;
			LocatorReloadEnterDisable("SantoDomingo_town", "Reload1_back", true);	//Не даём выйти из города (квест продолжается)
			LocatorReloadEnterDisable("SantoDomingo_town", "Reload3_back", true);	//Блакируем резиденцию
			PChar.quest.ATpr_SvobodaIgry.over = "yes";				//Если успели в Санто-Доминго, то выключаем таймер
			
			/*PChar.quest.ATpr_KrasivoSD.win_condition.l1 = "locator";			//Встаём на определённое место
			PChar.quest.ATpr_KrasivoSD.win_condition.l1.location = "SantoDomingo_town";
			PChar.quest.ATpr_KrasivoSD.win_condition.l1.locator_group = "goto";
			PChar.quest.ATpr_KrasivoSD.win_condition.l1.locator = "goto7";
			PChar.quest.ATpr_KrasivoSD.win_condition = "ATpr_KrasivoSD";*/
		break;
		
		/*case "ATpr_KrasivoSD":
			StartQuestMovie(true, true, true);
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			object cam_pause;
			LoadTrackCamera("RESOURCE\MODELS\Locations\Town_SantoDomingo\Town\Margarita_track_camera_2.ant", 30.0, &cam_pause);
			DoQuestCheckDelay("ATpr_KrasivoSD_2", 20.0);
		break;
		
		case "ATpr_KrasivoSD_2":
			EndQuestMovie();
			ChangeShowIntarface();
			LAi_SetPlayerType(pchar);
			locCameraToPos(0.00, 0.50, 0.50, false);
			locCameraTarget(PChar);
			locCameraFollow();
		break;*/
		
		case "ATpr_OboronaSD":
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			DoQuestFunctionDelay("ATpr_OboronaSD_2", 0.1);
			ChangeCharacterAddressGroup(pchar, "SantoDomingo_ExitTown", "rld", "aloc15");
			chrDisableReloadToLocation = true;
			bDisableCharacterMenu = true;
		break;
		
		case "ATpr_3Volna":
			DoQuestFunctionDelay("ATpr_OboronaSD_14", 1.0);
		break;
		
		case "ATpr_3Volna_2":
			DoQuestFunctionDelay("ATpr_OboronaSD_19", 1.0);
		break;
		
		case "ATpr_3Volna_3":
			SetMusic("none");
			PlaySound("CSR\Music\Main-menu-09.ogg");
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetCurHPMax(sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "reload", "reload1_back");
			sld.dialog.filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "ATpr_SD_Koten_1";
		break;
		
		case "ATpr_Jiteli_Uspokoilis":
			DeleteAttribute(pchar, "questTemp.AnjelikaTichPrologue6");
		break;
		
		case "ATpr_Pereodevaemsya":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "ATpr_SD_Koten_6_3";
			LAi_ActorDialogNow(sld, Pchar, "", -1);
		break;
		
		case "ATpr_VosstanovimGorod":	
			LocatorReloadEnterDisable("SantoDomingo_town", "Reload1_back", false);
			bDisableFastReload = false;
			bDisableLandEncounters = false;
			ChangeCharacterNationReputation(pchar, SPAIN, 18);
			
			sld = CharacterFromID("SantoDomingo_Mayor")
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			
			AddQuestRecord("AT_Mechty_Sbivautsya", "4");
			
			//Восстанавливаем город из пепла
			SetLocationCapturedState("LaVega_town", false);
			SetCaptureTownByNation("LaVega", PIRATE);
			locations[FindLocation("LaVega_town")].models.always.locatorsl3 = "LaVega_locators";
			locations[FindLocation("LaVega_town")].models.night.charactersPatch = "LaVega_patch_night";
			locations[FindLocation("LaVega_town")].models.always.locatorsl2 = "LaVega_1";
			locations[FindLocation("LaVega_town")].type = "town";
			sld = CharacterFromID("Edward Mansfield")
			ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
			sld.Dialog.Filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "Pirat_Guber";
			
			sld = CharacterFromID("spa_guber")
			sld.Dialog.Filename = "Quest\AngelikaTichLine\MechtySbyvautsya.c";
			sld.dialog.currentnode = "Ispa_Guber";
			
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			sld.lifeday = 0;
			sld = CharacterFromID("Old Friend")
			sld.Dialog.Filename = "Quest\SilencePrice\Luke.c";
			sld.dialog.currentnode = "First Time";
		break;
		
//========================  Квест: "Портниха знатной дамы"  =======================	

		case "AT_PZD_Quest":
			PChar.quest.AT_PZD_StartQuest.win_condition.l1 = "location";
			PChar.quest.AT_PZD_StartQuest.win_condition.l1.location = "Marigo_town";
			PChar.quest.AT_PZD_StartQuest.win_condition = "AT_PZD_StartQuest";
		break;
		
		case "AT_PZD_StartQuest":
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Pilar", "PilarTernera", "woman", "YokoDias", 1, SPAIN, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_65", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_66", "Names.txt", "#space#", " ");
			LAi_SetImmortal(sld, true);
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_Pilar_1_1";
			sld.talker = 4;
			ChangeCharacterAddressGroup(sld, "Marigo_town", "goto", "goto12");

			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Herineldo", "sold_spa_2", "man", "man", 10, SPAIN, -1, true));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_67", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_68", "Names.txt", "#space#", " ");
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_town", "goto", "goto12");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, CharacterFromID("AT_PZD_Pilar"), "", -1);

			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_R1", "sold_spa_2", "man", "man", 5, SPAIN, -1, true));
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_town", "goto", "goto12");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, CharacterFromID("AT_PZD_Pilar"), "", -1);
		break;

		case "AT_PZD_ProvalMissii":
			AddQuestRecord("AT_PZD", "2");
			CloseQuestHeader("AT_PZD");
			
			//СЮДА ДОПИСАТЬ ВСЁ, ЧТО КАСАЕТСЯ ПРОВАЛА МИССИИ
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Marigo_town", "reload3_back", false);
			LocatorReloadEnterDisable("Marigo_town", "reloadR2", false);			
			DeleteAttribute(pchar, "questTemp.AT_PZD_Bordel")
			DeleteAttribute(pchar, "questTemp.AT_PZD_Bordel_2")
			DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki");
			DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki_2");
			DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki_3");
			DeleteAttribute(pchar, "questTemp.AT_PZD_taverna")
			DeleteAttribute(pchar, "questTemp.AT_PZD_PU")
			DeleteAttribute(pchar, "questTemp.AT_PZD_Rostovshik")
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("AT_PZD_Matros"+i);
				sld.lifeday = 0;
			}
		break;
		
		case "AT_PZD_IdemNaKarnaval":
			TeleportCharacterToPosAy(pchar, -5.17, 3.0, -4.0, 0.00);
			bDisableFastReload = true;
			InterfaceStates.Buttons.Save.enable = false;
			PChar.quest.AT_PZD_Karnaval.win_condition.l1 = "locator";
			PChar.quest.AT_PZD_Karnaval.win_condition.l1.location = "Marigo_town";
			PChar.quest.AT_PZD_Karnaval.win_condition.l1.locator_group = "reload";
			PChar.quest.AT_PZD_Karnaval.win_condition.l1.locator = "reload3_back";
			PChar.quest.AT_PZD_Karnaval.win_condition = "AT_PZD_Karnaval";
			RemoveCharacterEquip(pchar, SUIT_ITEM_TYPE);
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			pchar.model = "AngelicaBal";
			SetNewModelToChar(pchar);
			
			//locations[FindLocation("Marigo_hall")].models.always.l1 = "residence06";
			locations[FindLocation("Marigo_hall")].models.always.l1 = "residence06_quest";
			//locations[FindLocation("Marigo_hall")].models.always.locators = "residence06_locators";
			locations[FindLocation("Marigo_hall")].models.always.locators = "residence06_quest_locators";
			//locations[FindLocation("Marigo_hall")].models.day.charactersPatch = "residence06_patch";
			locations[FindLocation("Marigo_hall")].models.day.charactersPatch = "residence06_quest_patch";
			//locations[FindLocation("Marigo_hall")].models.night.charactersPatch = "residence06_patch";
			locations[FindLocation("Marigo_hall")].models.night.charactersPatch = "residence06_quest_patch";
			
			//
		break;
		
		case "AT_PZD_Karnaval":
			DoQuestReloadToLocation("Marigo_hall", "reload", "reload1", "AT_PZD_Karnaval_2");
		break;
		
		case "AT_PZD_Karnaval_2":
			chrDisableReloadToLocation = true;
			pchar.model = "AngelicaBal";
			SetNewModelToChar(pchar);
			AddQuestRecord("AT_PZD", "5");
			
			//Музыкант 1
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Musicant1", "Musician1", "man", "man", 3, HOLLAND, -1, false));
			LAi_SetSitType(sld);
			sld.nonTable = true;
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "quest", "quest7");
			
			//Музыкант 2
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Musicant2", "Musician2", "man", "man", 3, HOLLAND, -1, false));
			LAi_SetSitType(sld);
			sld.nonTable = true;
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "quest", "quest8");
			
			//Игрок в покер
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_ManBal5", "ManBal5", "man", "man", 3, HOLLAND, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_69", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_70", "Names.txt", "#space#", " ");
			LAi_SetSitType(sld);
			sld.nonTable = true;
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_ManBal5";
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "sit", "sit2");
			
			//Женщина 1 в углу
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_WomanBal1", "WomanBal1", "woman", "woman", 3, HOLLAND, -1, false));
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_WomanBal1";
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "quest", "quest1");
			
			//Женщина 2 в углу
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_WomanBal2", "WomanBal2", "woman", "woman", 3, HOLLAND, -1, false));
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "quest", "quest2");
			
			//Мужчина в углу
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_ManBal4", "ManBal4", "man", "man", 3, HOLLAND, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_71", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_72", "Names.txt", "#space#", " ");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "quest", "quest3");
			
			//Дочь губернатора
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_DochGubera", "WomanBal4", "woman", "woman", 3, HOLLAND, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_73", "Names.txt", "#space#", " ");
			sld.lastname = "";
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_DochGubera";
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "quest", "quest4");
			
			//Мужик раздаёт крафтовое пиво
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_MujikSPivom", "ManBal1", "man", "man", 3, HOLLAND, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_74", "Names.txt", "#space#", " ");
			sld.lastname = "";
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "goto", "goto3");
			
			//Мужик общается 1
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_MujikBoltun1", "ManBal2", "man", "man", 3, HOLLAND, -1, false));
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_MujikBoltun_1";
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "quest", "quest5");
			
			//Мужик общается 2
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_MujikBoltun2", "ManBal3", "man", "man", 3, HOLLAND, -1, false));
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "quest", "quest6");
			
			//Босс этой качалки
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_GabrielDeSeguensa", "deSeguesa", "man", "man", 10, HOLLAND, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_75", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_76", "Names.txt", "#space#", " ");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "barman_look_around", "", 2.9);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_GabrielDeSeguensa_1";
			//sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_hall", "quest", "quest9");
			
			PChar.quest.AT_PZD_GabrielZnakomstvo.win_condition.l1 = "locator";
			PChar.quest.AT_PZD_GabrielZnakomstvo.win_condition.l1.location = "Marigo_hall";
			PChar.quest.AT_PZD_GabrielZnakomstvo.win_condition.l1.locator_group = "quest";
			PChar.quest.AT_PZD_GabrielZnakomstvo.win_condition.l1.locator = "quest17";
			PChar.quest.AT_PZD_GabrielZnakomstvo.win_condition = "AT_PZD_GabrielZnakomstvo";
		break;
		
		case "AT_PZD_GabrielZnakomstvo":
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "AT_PZD_UbiliVremya":
			WaitDate("", 0, 0, 0, 1, 0);
			AddQuestRecord("AT_PZD", "9");
			
			PChar.quest.AT_PZD_Naberejnaya.win_condition.l1 = "locator";
			PChar.quest.AT_PZD_Naberejnaya.win_condition.l1.location = "Marigo_hall";
			PChar.quest.AT_PZD_Naberejnaya.win_condition.l1.locator_group = "reload";
			PChar.quest.AT_PZD_Naberejnaya.win_condition.l1.locator = "reload2_back";
			PChar.quest.AT_PZD_Naberejnaya.win_condition = "AT_PZD_Naberejnaya";
		break;
		
		case "AT_PZD_Naberejnaya":
			DoQuestReloadToLocation("Marigo_town", "reload", "reloadR2", "AT_PZD_Naberejnaya_2");
		break;
		
		case "AT_PZD_Naberejnaya_2":
			pchar.model = "AngelicaBal";
			SetNewModelToChar(pchar);
		
			//Женщина 1 на набережной
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_WomanBal3", "WomanBal3", "woman", "woman", 3, HOLLAND, -1, false));
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_town", "quest", "quest7");
			
			//Мужчина 1 на набережной
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_ManBal6", "ManBal6", "man", "man", 3, HOLLAND, -1, false));
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Marigo_town", "quest", "quest8");
			
			//Габриэль на набережной
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_GabrielDeSeguensa_11";
			ChangeCharacterAddressGroup(sld, "Marigo_town", "quest", "quest9");
		break;
		
		case "AT_PZD_VGorod":
			StartQuestMovie(true, false, true);
		
			GiveItem2Character(PChar, "suit_3");
			EquipCharacterByItem(Pchar, "suit_3");
			RemoveItems(pchar, "AT_PZD_KarnavalKostum", 1);
			ClearAllLogStrings();
			
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			ChangeCharacterAddressGroup(sld, "Marigo_town", "goto", "goto29");
			//ChangeCharacterAddressGroup(sld, "Marigo_town", "quest", "quest17");
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_GabrielDeSeguensa_15";
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest17", "", -1);
			//LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, sld, "", -1);
			
			locCameraFlyToPosition(-4.4, 5.7, 30.7, -4.3, 6.0, -25.0, -1, 800.0);
			DoQuestCheckDelay("AT_PZD_VGorod_2", 8.5);
			
			PChar.quest.AT_PZD_VDom.win_condition.l1 = "locator";
			PChar.quest.AT_PZD_VDom.win_condition.l1.location = "Marigo_town";
			PChar.quest.AT_PZD_VDom.win_condition.l1.locator_group = "reload";
			PChar.quest.AT_PZD_VDom.win_condition.l1.locator = "houseB3";
			PChar.quest.AT_PZD_VDom.win_condition = "AT_PZD_VDom";
		break;
		
		case "AT_PZD_VGorod_2":
			locCameraResetState();
			locCameraFlyToPosition(-4.3, 6.0, -25.0, -29.2, 5.8, -28.0, -1, 700.0);
			DoQuestCheckDelay("AT_PZD_VGorod_3", 7.5);
		break;
		
		case "AT_PZD_VGorod_3":
			locCameraResetState();
			locCameraFlyToPosition(-29.2, 5.8, -28.0, -31.6, 6.5, -50.8, -1, 1800.0);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest16", "", -1);
			DoQuestCheckDelay("AT_PZD_VGorod_4", 18.0);
		break;
		
		case "AT_PZD_VGorod_4":
			locCameraResetState();
			locCameraFlyToPosition(-31.6, 6.5, -50.8, -31.2, 6.5, -65.2, -1, 600.0);
			DoQuestCheckDelay("AT_PZD_VGorod_5", 7.0);
		break;
		
		case "AT_PZD_VGorod_5":
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "AT_PZD_VDom":	
			DoQuestReloadToLocation("BigHouseKNS", "reload", "reload3", "AT_PZD_VDom2");		
		break;
		
		case "AT_PZD_VDom2":			
			//Рабочий
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_shipowner_3", "shipowner_3", "man", "man", 3, HOLLAND, -1, false));
			LAi_SetActorType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "BigHouseKNS", "goto", "goto4");
			
			//София де ла Пьедад
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Sofia", "CitizenWom_2", "woman", "woman", 5, HOLLAND, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_77", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_78", "Names.txt", "#space#", " ");
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_Sofia_1";
			LAi_SetStayType(sld);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "BigHouseKNS", "quest", "quest2");			
		break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   	 СЮЖЕТНАЯ ЛИНЕЙКА "АНЖЕЛИКА ТИЧ"     КОНЕЦ
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		
//========================  "Нежить: Лиларкор"  =======================

		case "UP_KrovPismo":
			PChar.quest.UP_KrovPismo1.over = "yes";
			PChar.quest.UP_KrovPismo2.over = "yes";
			PChar.quest.UP_KrovPismo3.over = "yes";
			PChar.quest.UP_KrovPismo4.over = "yes";
			PChar.quest.UP_KrovPismo5.over = "yes";
			PChar.quest.UP_KrovPismo6.over = "yes";
			PChar.quest.UP_KrovPismo7.over = "yes";
			Locations[FindLocation(pchar.location)].box1.items.UP_PismoZagadka = 1;
		break;
		
		case "UP_DrugPridet":
			pchar.questTemp.UndeadPrologue2 = "UP2";
		break;
		
		case "UP_DrugPridet_2":
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("PGG_Undead", "PGG_Meriman_0", "skeleton", "man", 10, PIRATE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_79", "Names.txt", "#space#", " ");
			sld.lastname = "";
			GiveItem2Character(sld, "blade6");
			EquipCharacterByItem(sld, "blade6");
			ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			sld.dialog.filename = "Quest\MainheroPrologues\Prologue_Undead_dialog.c";
			sld.dialog.currentnode = "PGG_Undead_1";
			sld.lifeday = 0;
			LAi_SetImmortal(sld, false);
		break;
		
		case "UP_DrugPridet_3":
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("PGG_Undead", "PGG_Meriman_0", "skeleton", "man", 10, PIRATE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_80", "Names.txt", "#space#", " ");
			sld.lastname = "";
			GiveItem2Character(sld, "blade6");
			EquipCharacterByItem(sld, "blade6");
			ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			sld.dialog.filename = "Quest\MainheroPrologues\Prologue_Undead_dialog.c";
			sld.dialog.currentnode = "PGG_Undead_5";
			sld.lifeday = 0;
		break;
		
		case "UD_DrugUshel":
			pchar.questTemp.UndeadPrologue3 = "UP3";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "UP_SkeletyVPeshere_NanyatSnova":
			DeleteAttribute(pchar, "questTemp.UP_SkeletyVPeshere");
		break;
		
		case "UD_DrugUshel_2":
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			sld = CharacterFromID("PGG_Undead");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("UP_Korabl_s_klinkom", "officer_30", "man", "man", sti(PChar.rank)+2, PIRATE, 40, true));
			FantomMakeCoolSailor(sld, SHIP_SCHOONER, GetConvertStr("Variable_quests_reaction_10", "ShipNames.txt"), CANNON_TYPE_CULVERINE_LBS12, 40, 40, 40);
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			
			SetCaptanModelByEncType(sld, "war");
			sld.AlwaysEnemy = true;
			sld.DontRansackCaptain = true;
			sld.mapEnc.type = "war";
			sld.mapEnc.Name = GetConvertStrWithReplace("Variable_quests_reaction_81", "Names.txt", "#space#", " ");
			sld.hunter = "pirate";
			Group_AddCharacter("UP_Ship", "UP_Korabl_s_klinkom");

			Group_SetGroupCommander("UP_Ship", "UP_Korabl_s_klinkom");
			Group_SetTaskAttackInMap("UP_Ship", PLAYER_GROUP);
			Group_LockTask("UP_Ship");
			Map_CreateFastWarrior("", "UP_Korabl_s_klinkom", 30);
			
			PChar.quest.UD_Novye_Officery.win_condition.l1 = "item";
			PChar.quest.UD_Novye_Officery.win_condition.l1.item = "Lilarcor_Sword1";
			PChar.quest.UD_Novye_Officery.win_condition = "UD_Novye_Officery";
		break;
		
		case "UD_Novye_Officery":
			//Привидение
			sld = GetCharacter(NPC_GenerateCharacter("Undead_Jessika", "PGG_Ghost_0", "skeleton", "Jessika", 10, PIRATE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_82", "Names.txt", "#space#", " ");
			sld.lastname = "";
			sld.FaceId = 527;
			SetSPECIAL(sld, 7, 3, 8, 3, 8, 10, 10);
			GiveItem2Character(sld, "blade36");
			EquipCharacterByItem(sld, "blade36");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.HalfImmortal = true;
			AddPassenger(pchar, sld, false);
			sld.location = "None";
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.HeroModel = "PGG_Ghost_0,PGG_Ghost_1,PGG_Ghost_2,PGG_Ghost_3,PGG_Ghost_4,PGG_Ghost_5";
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "Energaiser");
			LAi_SetHP(sld, 260.0, 260.0);
			
			//Скелет индеец
			sld = GetCharacter(NPC_GenerateCharacter("Undead_Indeech", "skel_5", "skeleton", "skeleton", 10, PIRATE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_83", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_84", "Names.txt", "#space#", " ");
			sld.FaceId = 353;
			GiveItem2Character(sld, "toporAZ");
			EquipCharacterByItem(sld, "toporAZ");
			GiveItem2Character(sld, "Totem_11");
			SetSPECIAL(sld, 5, 9, 6, 5, 8, 6, 10);
			SetShipSkill(sld, 15, 25, 30, 30, 45, 30, 25, 20, 5);	//Умения морские (лидер, торг, точн, пушки, навиг, ремонт, аборд, защита, скрыт)
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.HalfImmortal = true;
			AddPassenger(pchar, sld, false);
			sld.location = "None";
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.HeroModel = "skel_5,skel_5_1,skel_5_2,skel_5_3,skel_5_4,skel_5_5";
			LAi_SetHP(sld, 150.0, 150.0);
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "ByWorker2");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			SetCharacterPerk(sld, "EmergentSurgeon");
			
			//Синий скелет
			sld = GetCharacter(NPC_GenerateCharacter("Undead_Blue", "skelt_0", "skeleton", "skeleton", 10, PIRATE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_85", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_86", "Names.txt", "#space#", " ");
			sld.FaceId = 354;
			SetSPECIAL(sld, 10, 3, 10, 3, 5, 10, 3);
			GiveItem2Character(sld, "topor2");
			EquipCharacterByItem(sld, "topor2");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.HalfImmortal = true;
			AddPassenger(pchar, sld, false);
			sld.location = "None";
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.HeroModel = "skelt_0,skelt_1,skelt_2,skelt_3,skelt_4,skelt_5";
			LAi_SetHP(sld, 300.0, 300.0);
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "EnergyPlus");
			SetCharacterPerk(sld, "HPPlus");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Energaiser");
			
			//Скелет с красной повязкой
			sld = GetCharacter(NPC_GenerateCharacter("Undead_Red", "skel_4", "skeleton", "skeleton", 10, PIRATE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_87", "Names.txt", "#space#", " ");
			sld.lastname = "";
			sld.FaceId = 352;
			GiveItem2Character(sld, "blade31");
			EquipCharacterByItem(sld, "blade31");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.HalfImmortal = true;
			AddPassenger(pchar, sld, false);
			sld.location = "None";
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.HeroModel = "skel_4,skel_4_1,skel_4_2,skel_4_3,skel_4_4,skel_4_5";
			LAi_SetHP(sld, 200.0, 200.0);
			SetSPECIAL(sld, 9, 3, 10, 3, 6, 9, 10);
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "EnergyPlus");
			SetCharacterPerk(sld, "HPPlus");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "Energaiser");
			
			//Скелет с зелёными штанами
			sld = GetCharacter(NPC_GenerateCharacter("Undead_Green", "skel_2", "skeleton", "skeleton", 10, PIRATE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_88", "Names.txt", "#space#", " ");
			sld.lastname = "";
			sld.FaceId = 351;
			SetSPECIAL(sld, 5, 10, 6, 5, 8, 6, 9);
			SetShipSkill(sld, 10, 40, 15, 20, 50, 38, 32, 60, 30);	//Умения морские (лидер, торг, точн, пушки, навиг, ремонт, аборд, защита, скрыт)
			GiveItem2Character(sld, "blade18");
			EquipCharacterByItem(sld, "blade18");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.HalfImmortal = true;
			AddPassenger(pchar, sld, false);
			sld.location = "None";
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.HeroModel = "skel_2,skel_2_1,skel_2_2,skel_2_3,skel_2_4,skel_2_5";
			LAi_SetHP(sld, 150.0, 150.0);
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "ImmediateReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "CannonProfessional");
		break;
		
//========================  Sinistra: "Игра в прятки"  ========================
		
		case "SCQ_Prytki_VremyPoshlo":
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_161", "Logs.txt", "#space#", " "));
			SetShowTimer(120.0);
			DoQuestCheckDelay("SCQ_Prytki_VremyVishlo", 119.3);

			string DvP;
			DvP = pchar.DvP;
			Log_TestInfo(GetConvertStrWithReplace("Variable_quests_reaction_162", "Logs.txt", "#space#", " ") + DvP);
			
			pchar.BlockingTalker = true;
			
			PChar.quest.SCQ_Prytki_PokinuliZonu.win_condition.l1 = "ExitFromLocation";
			PChar.quest.SCQ_Prytki_PokinuliZonu.win_condition.l1.location = PChar.location;
			PChar.quest.SCQ_Prytki_PokinuliZonu.win_condition = "SCQ_Prytki_PokinuliZonu";
			
			sld = CharacterFromID(pchar.DevushkaVPrytki);
			sld.dialog.currentnode = "SCQ_Prytki_Trah";
			if (rand(3) == 3)
			{
				sld.dialog.currentnode = "SCQ_Prytki_Trah";
			}
			else
			{
				sld.dialog.currentnode = "SCQ_Prytki_Dengi";
			}
		break;
		
		case "SCQ_Prytki_VremyVishlo":
			DeleteAttribute(pchar, "showTimer");
			ClearAllLogStrings();
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_163", "Logs.txt", "#space#", " "));
			sld = CharacterFromID(pchar.DevushkaVPrytki);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			InterfaceStates.Buttons.Save.enable = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			PChar.quest.SCQ_Prytki_PokinuliZonu.over = "yes";
			DeleteAttribute(pchar, "DvP");
			DeleteAttribute(pchar, "BlockingTalker");
		break;
		
		case "SCQ_Prytki_PokinuliZonu":
			DeleteAttribute(pchar, "showTimer");
			DeleteAttribute(pchar, "DvP");
			DeleteAttribute(pchar, "BlockingTalker");
			ClearAllLogStrings();
			//Log_info(GetConvertStrWithReplace("Variable_quests_reaction_164", "Logs.txt", "#space#", " "));
			sld = CharacterFromID(pchar.DevushkaVPrytki);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			InterfaceStates.Buttons.Save.enable = true;
			//bDisableFastReload = false;
			//chrDisableReloadToLocation = false;
		break;
		
		case "SCQ_Prytki_V_Komnate":
			sld = CharacterFromID(pchar.DevushkaVPrytki);
			if (rand(2) == 2)
			{
				sld.dialog.currentnode = "SCQ_Prytki_Ooops_Eto_Lovushka";
			}
			else
			{
				sld.dialog.currentnode = "SCQ_Prytki_Trah_3";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, Pchar, "", -1);
		break;
		
		case "SCQ_Prytki_V_Komnate_Ooops_Eto_Lovushka":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sTemp = "pirate_"+(rand(24)+1);					
				sld = GetCharacter(NPC_GenerateCharacter("Bandit_Prytki_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1_back");
			}
			sld = CharacterFromID(pchar.DevushkaVPrytki);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 1);
			sld = CharacterFromID("Bandit_Prytki_1");
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "SCQ_Prytki_Ooops_Eto_Lovushka_3";
			LAi_ActorDialogNow(sld, Pchar, "", -1);
		break;
		
		case "SCQ_Prytki_V_Komnate_Final":
			InterfaceStates.Buttons.Save.enable = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddCharacterExpToSkill(pchar, "FencingLight", 5);
			AddCharacterExpToSkill(pchar, "Fencing", 5);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 5);
		break;
		
//========================  Sinistra: "Латынь"  ======================

		case "SCQ_Zachet_VremyVishlo":
			DialogExit();
			DeleteAttribute(pchar, "showTimer");
			ClearAllLogStrings();
			sld = CharacterFromID(pchar.StudentZachet);
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "SCQ_Proverka_Znani_VremyVishlo";
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			//LAi_ActorDialogNow(sld, Pchar, "", -1);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "SCQ_Zachet_Skorostrel":
			pchar.questTemp.SCQ_Zachet_Skorostrel = true;
		break;
		
//============  Sinistra: "Кот в мешке"  ===============

		case "CSP_KvM_SpawnRibak":
			sld = GetCharacter(NPC_GenerateCharacter("CSP_KvM_Ribak", "fisherman", "man", "man1", 3, SPAIN, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_89", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_90", "Names.txt", "#space#", " ");
			sld.City = "SantoDomingo";
			sld.dialog.filename   = "Quest\KotVMeshke.c";
			sld.dialog.currentnode = "First time";
			LAi_SetStayType(sld);
			sld.talker = 2;
			ChangeCharacterAddressGroup(sld, "SantoDomingo_town", "quest", "quest_K1");
		break;
		
		case "CSP_KvM_GatilioVSunduke":
			PlaySound("Kopcapkz\Voices\Quest\cat.wav");
			DeleteAttribute(pchar, "questTemp.CSP_KvM_PoiskGatilio");
			DoQuestCheckDelay("CSP_KvM_GatilioVSunduke_2", 3.0);
			
			sld = CharacterFromID("CSP_KvM_Ribak");
			sld.dialog.filename = "Quest\KotVMeshke.c";
			sld.dialog.currentnode = "ВозвращаемГатилио_1";
			
			PChar.quest.CSP_KvM_Nazad.win_condition.l1 = "locator";
			PChar.quest.CSP_KvM_Nazad.win_condition.l1.location = "SantoDomingo_town";
			PChar.quest.CSP_KvM_Nazad.win_condition.l1.locator_group = "item";
			PChar.quest.CSP_KvM_Nazad.win_condition.l1.locator = "akula2";
			PChar.quest.CSP_KvM_Nazad.win_condition = "CSP_KvM_Nazad";
		break;
		
		case "CSP_KvM_GatilioVSunduke_2":
			AddQuestRecord("CSP_KvM", "2");
			AddQuestUserData("CSP_KvM", "sSex", GetSexPhrase("ёл","ла"));
		break;
		
		case "CSP_KvM_Nazad":
			SetTimeScale(1.0);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			DoQuestCheckDelay("CSP_KvM_Nazad_2", 0.5);
		break;
		
		case "CSP_KvM_Nazad_2":
			ChangeCharacterAddressGroup(pchar, "SantoDomingo_town", "quest", "quest_K1");
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("CSP_KvM_Ribak");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
//==================  "Найти пропавшего торговца"  ==================

		case "SCQ_Hasband_Truba":
			pchar.questTemp.womanHasband_Truba = true;
			if (CheckAttribute(pchar, "questTemp.womanHasband_Nagrada") && CheckAttribute(pchar, "questTemp.womanHasband_Truba"))
			{
				CloseQuestHeader("SCQ_womanHasband");
				pchar.questdata.NaitiTorgovtsa = 1;
				DeleteAttribute(pchar, "questTemp.womanHasband_Nagrada");
				DeleteAttribute(pchar, "questTemp.womanHasband_Truba");
			}
		break;

//============  "Вызволение из плена мужа горожанки"  ===============

		case "SCQ_womanPirates_afterCabinFight":
			sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortPax_MuzhPassajir", "trader_4", "man", "man", 3, FRANCE, -1, false));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_91", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_92", "Names.txt", "#space#", " ");
			sld.dialog.filename   = "Quest\Questions.c";
			sld.dialog.currentnode = "womanPirates_Board";
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;
		
		case "SCQ_Pirates_Kostum":
			CloseQuestHeader("SCQ_womanPirates");
			pchar.questdata.SpastiMuja = 1;
		break;
		
		case "SCQ_womanPirates_Potunul":
			AddQuestRecord("SCQ_womanPirates", "2");
			CloseQuestHeader("SCQ_womanPirates");
			pchar.questdata.SpastiMuja = 1;
			sld = characterFromId("QuetionsPortPax");
			sld.lifeday = 0;
		break;
		
		case "SCQ_womanPirates_Nashli":
			AddQuestRecord("SCQ_womanPirates", "3");
		break;
		
//============  "Тичингиту"  ===============
		case "TichingituFree":
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_9";
			ChangeCharacterAddressGroup(sld, "BasTer_exittown", "rld", "aloc14"); // 170712
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			RemoveAllCharacterItems(sld, true);
			string topor = GetGeneratedItem("topor_05")
			GiveItem2Character(sld, topor);
			EquipCharacterbyItem(sld, topor); // 151012
		break;

//============  "Осколок прошлого"  ===============

		case "RepeatReleaseCheck_pirateVikingShip":
			Pchar.quest.pirateVikingShipMapEnterCheckRepeat.win_condition.l1 = "MapEnter";
			Pchar.quest.pirateVikingShipMapEnterCheckRepeat.win_condition = "ReleaseCheck_pirateVikingShip";
		break;

		case "ReleaseCheck_pirateVikingShip":
			if(CheckExistQuestEncounter("pirateVikingQuest_Captain")) // Нужно для прервания, иначе цикл проверки смены корабля и наличия эскадры, при выходе на глобалку, будет бесконечным
			{
				PChar.quest.pirateVikingShipReturnToTownCheck.win_condition.l1 = "Location_Type"; // Специально делаю так, чтобы оставить лазейки для изобретательных игроков, например, найти компаньона или добыть в бою другой корабль до встречи с Викингом
				PChar.quest.pirateVikingShipReturnToTownCheck.win_condition.l1.location_type = "town";
				PChar.quest.pirateVikingShipReturnToTownCheck.win_condition = "RepeatReleaseCheck_pirateVikingShip";
				if (CheckAttribute(pchar, "questTemp.pirateVikingQuest.pcharShipType") && pchar.questTemp.pirateVikingQuest.pcharShipType != pchar.Ship.Type || GetCompanionQuantity(pchar) != 1)
				{
					Map_ReleaseQuestEncounter("pirateVikingQuest_Captain");
					AddQuestRecord("pirateVikingQuest", "6_1");
					AddQuestUserData("pirateVikingQuest", "sName", pchar.questTemp.pirateVikingQuest.Name);
				}
			}
		break;


//===================================================================

		case "SpookyScarySkeleton":
			if (loadedLocation.id == "Labirint_1" || loadedLocation.id == "Labirint_2" || loadedLocation.id == "Labirint_3")
			{
				int pRank;
				if (sti(pchar.rank) > 5)
				{
					if (sti(pchar.rank) > 20) pRank = sti(pchar.rank)+5 + MOD_SKILL_ENEMY_RATE*3;
					else pRank = sti(pchar.rank)+5 + sti(MOD_SKILL_ENEMY_RATE*3/2);
				}
				else
				{	//казуалам набьют ебало, ибо ранг+5 и толпа
					pRank = sti(pchar.rank)+5;
				}
				aref grp;
				int num;
				makearef(grp, loadedLocation.locators.monsters);
				num = GetAttributesNum(grp);
				for(i = 0; i < num; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Skelet"+loadedLocation.index+"_"+i, "Skel_5", "skeleton", "man", pRank, PIRATE, 1, true));
					FantomMakeCoolFighter(sld, pRank, 80, 80, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), "", MOD_SKILL_ENEMY_RATE*3*2);
					sld.name = GetConvertStrWithReplace("Variable_quests_reaction_93", "Names.txt", "#space#", " ");
					sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_94", "Names.txt", "#space#", " ");
					LAi_SetWarriorType(sld);
					LAi_warrior_SetStay(sld, true);
					LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
					string locator = GetAttributeName(GetAttributeN(grp, i));
					ChangeCharacterAddressGroup(sld, loadedLocation.id, "monsters", locator);
				}
			}
		break;

		case "recharge_portals":
			pchar.quest.first_portal.win_condition.l1 = "locator";
			pchar.quest.first_portal.win_condition.l1.location = "Treasure_alcove";
			pchar.quest.first_portal.win_condition.l1.locator_group = "teleport";
			pchar.quest.first_portal.win_condition.l1.locator = "teleport1";
			pchar.quest.first_portal.win_condition = "first_portal";

			pchar.quest.second_portal.win_condition.l1 = "locator";
			pchar.quest.second_portal.win_condition.l1.location = "Treasure_alcove";
			pchar.quest.second_portal.win_condition.l1.locator_group = "teleport";
			pchar.quest.second_portal.win_condition.l1.locator = "teleport2";
			pchar.quest.second_portal.win_condition = "second_portal";

			pchar.quest.third_portal.win_condition.l1 = "locator";
			pchar.quest.third_portal.win_condition.l1.location = "Treasure_alcove";
			pchar.quest.third_portal.win_condition.l1.locator_group = "teleport";
			pchar.quest.third_portal.win_condition.l1.locator = "teleport3";
			pchar.quest.third_portal.win_condition = "third_portal";

			pchar.quest.fourth_portal.win_condition.l1 = "locator";
			pchar.quest.fourth_portal.win_condition.l1.location = "Treasure_alcove";
			pchar.quest.fourth_portal.win_condition.l1.locator_group = "teleport";
			pchar.quest.fourth_portal.win_condition.l1.locator = "teleport4";
			pchar.quest.fourth_portal.win_condition = "fourth_portal";

			pchar.quest.fifth_portal.win_condition.l1 = "locator";
			pchar.quest.fifth_portal.win_condition.l1.location = "Treasure_alcove";
			pchar.quest.fifth_portal.win_condition.l1.locator_group = "teleport";
			pchar.quest.fifth_portal.win_condition.l1.locator = "teleport5";
			pchar.quest.fifth_portal.win_condition = "fifth_portal";

			pchar.quest.treasure_portal.win_condition.l1 = "locator";
			pchar.quest.treasure_portal.win_condition.l1.location = "Treasure_alcove";
			pchar.quest.treasure_portal.win_condition.l1.locator_group = "teleport";
			pchar.quest.treasure_portal.win_condition.l1.locator = "teleport6";
			pchar.quest.treasure_portal.win_condition = "treasure_portal";

			pchar.quest.monster_portal.win_condition.l1 = "locator";
			pchar.quest.monster_portal.win_condition.l1.location = "Treasure_alcove";
			pchar.quest.monster_portal.win_condition.l1.locator_group = "teleport";
			pchar.quest.monster_portal.win_condition.l1.locator = "teleport0";
			pchar.quest.monster_portal.win_condition = "monster_portal";
		break;

		case "empting_portals":
			pchar.quest.first_portal.over = "yes";
			pchar.quest.second_portal.over = "yes";
			pchar.quest.third_portal.over = "yes";
			pchar.quest.fourth_portal.over = "yes";
			pchar.quest.fifth_portal.over = "yes";
			pchar.quest.treasure_portal.over = "yes";
			pchar.quest.monster_portal.over = "yes";
		break;

		case "first_portal":
			LAi_QuestDelay("empting_portals", 0.0);
			LAi_fade("teleport_1_2", "");
			PlayStereoSound("Ambient\INCA TEMPLE\teleporter.wav");
		break;

		case "second_portal":
			LAi_QuestDelay("empting_portals", 0.0);
			LAi_fade("teleport_2_1", "");
			PlayStereoSound("Ambient\INCA TEMPLE\teleporter.wav");
		break;

		case "third_portal":
			LAi_QuestDelay("empting_portals", 0.0);
			LAi_fade("teleport_3_4", "");
			PlayStereoSound("Ambient\INCA TEMPLE\teleporter.wav");
		break;

		case "fourth_portal":
			LAi_QuestDelay("empting_portals", 0.0);
			LAi_fade("teleport_4_3", "");
			PlayStereoSound("Ambient\INCA TEMPLE\teleporter.wav");
		break;

		case "fifth_portal":
			LAi_QuestDelay("empting_portals", 0.0);
			LAi_fade("teleport_5_treasure", "");
			PlayStereoSound("Ambient\INCA TEMPLE\teleporter.wav");
		break;

		case "treasure_portal":
			LAi_QuestDelay("empting_portals", 0.0);
			if (!chrDisableReloadToLocation) LAi_fade("teleport_treasure_5", "");
			PlayStereoSound("Ambient\INCA TEMPLE\teleporter.wav");
		break;

		case "teleport_1_2":
			ChangeCharacterAddressGroup(pchar, "Treasure_alcove", "teleport", "teleport2");
			LAi_QuestDelay("recharge_portals", 2.0);
		break;

		case "teleport_2_1":
			ChangeCharacterAddressGroup(pchar, "Treasure_alcove", "teleport", "teleport1");
			LAi_QuestDelay("recharge_portals", 2.0);
		break;

		case "teleport_3_4":
			ChangeCharacterAddressGroup(pchar, "Treasure_alcove", "teleport", "teleport4");
			LAi_QuestDelay("recharge_portals", 2.0);
		break;

		case "teleport_4_3":
			ChangeCharacterAddressGroup(pchar, "Treasure_alcove", "teleport", "teleport3");
			LAi_QuestDelay("recharge_portals", 2.0);
		break;

		case "teleport_5_treasure":
			if (!CheckAttribute(pchar,"UmSamil") && !CheckAttribute(pchar,"UmSamilGuards"))
			{
				LoginUmSamilGuards();
				pchar.UmSamilGuards = true;
			}
			ChangeCharacterAddressGroup(pchar, "Treasure_alcove", "teleport", "teleport6");
			LAi_QuestDelay("recharge_portals", 2.0);
		break;

		case "UmSamilGuardsDefeated":
			pchar.UmSamilGuardsDefeated = true;
		break;

		case "UmSamilDefeated":
			LAi_SetFightMode(pchar, false);
			sld = CharacterFromID("DeadmansGod2");
			sld.dialog.filename = "Quest\Mictlantecuhtli.c";
			sld.dialog.currentnode = "Samil";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		case "teleport_treasure_5":
			if (!chrDisableReloadToLocation) ChangeCharacterAddressGroup(pchar, "Treasure_alcove", "teleport", "teleport5");
			LAi_QuestDelay("recharge_portals", 2.0);
		break;

		case "monster_portal":
			//LAi_QuestDelay("empting_portals", 0.0);
			LAi_fade("", "monster_generate_in_alcove");
			PlayStereoSound("Ambient\INCA TEMPLE\teleporter.wav");
			LAi_QuestDelay("recharge_portals", 2.0);
		break;

		case "monster_generate_in_alcove":
			ChangeCharacterAddressGroup(pchar, "Treasure_alcove", "teleport", "teleport0");
			Group_FindOrCreateGroup("almonsters");
			for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Skeletoon"+rand(999), "Skel"+(rand(3)+1), "skeleton", "skeleton", 25, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 25, 80, 60, BLADE_LONG, "pistol3", 70);
            	LAi_SetWarriorType(sld);

                LAi_group_MoveCharacter(sld, "almonsters");
                GetCharacterPos(pchar, &locx, &locy, &locz);
				sTemp = LAi_FindNearestFreeLocator("monsters", locx, locy, locz);
               	ChangeCharacterAddressGroup(sld, "Treasure_alcove", "monsters", sTemp);
            }
			LAi_group_SetLookRadius("almonsters", 30.0);
			LAi_group_SetRelation("almonsters", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("almonsters", LAI_GROUP_PLAYER, true);
		break;

		case "FishHeadsDefeated":
			//chrDisableReloadToLocation = false;
			if (loadedLocation.id == "Bermudes_Dungeon")
			{
				PlayStereoSound("notebook");
				TakeNItems(pchar,"Chest_quest",1);
				Log_info(GetConvertStrWithReplace("Variable_quests_reaction_165", "Logs.txt", "#space#", " "));
			}
		break;

		case "SpawnScamFan":
			sld = GetCharacter(NPC_GenerateCharacter("ScamCharacter", "PGG_WillTerner_5", "man", "man", 1, PIRATE, 1, false));
			DeleteAttribute(sld, "LifeDay");
			DeleteAttribute(sld, "items");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			sTemp = LAi_FindNearestFreeLocator("rld", locx, locy, locz);
			ChangeCharacterAddressGroup(sld, "FencingTown_ExitTown", "rld", sTemp);
			LAi_SetActorTypeNoGroup(sld);
			LAi_SetImmortal(sld,true);
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_95", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_96", "Names.txt", "#space#", " ");
			sld.dialog.filename = "Fan.c";
			sld.dialog.currentnode = "FirstMeet";
			LAi_group_MoveCharacter(sld, "player");
			LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		break;
		case "RidScamFan":
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("ScamCharacter");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			sTemp = LAi_FindNearestFreeLocator("rld", locx, locy, locz);
			ChangeCharacterAddressGroup(sld, "Temple_skulls", "goto", sTemp);
			LAi_SetActorTypeNoGroup(sld);
			LAi_SetImmortal(sld,true);
			sld.dialog.currentnode = "Scared";
			LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		break;
		case "GangRapeOld":
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("GangRapersMan_1");
			sld.Dialog.currentnode = "Third";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);

			for(i=1; i < sti(sld.num); i++)
			{
				sld = CharacterFromID("GangRapersMan_"+i);
				PlaceCharacter(sld, "goto", "random_must_be_near");
			}
			sld = CharacterFromID("OldMan");
			PlaceCharacter(sld, "goto", "random_must_be_near");
		break;
		case "GangRapeOld2":
			sld = CharacterFromID("GangRapersMan_1");
			sld.Dialog.currentnode = "Final";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "GangRapeOld3":
			sld = CharacterFromID("GangRapersMan_1");
			for(i=1; i < sti(sld.num); i++)
			{
				ref sled = CharacterFromID("GangRapersMan_"+i);
				LAi_SetActorType(sled);
				LAi_ActorRunToLocation(sled, "reload", "reload1", "", "", "", "OpenTheDoors", -1);
				sled.LifeDay = 0;
			}
			sld = CharacterFromID("OldMan");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "OpenTheDoors", -1);
			sld.LifeDay = 0;
		break;
		
		case "SpawnSalasarSupports":
			for(i = 0; i < 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SalSupp"+i, GetRandSkelModelClassic(), "skeleton", "man", 25, PIRATE, 0, true));
				FantomMakeCoolFighter(sld, 20, 90, 90, "blade01", "", 300);
				LAi_SetWarriorType(sld);
				PlaceCharacter(sld, "quest", "random_must_be_near");
				LAi_group_MoveCharacter(sld, "ReefAssholes");
				LAi_SetFightMode(sld, true);
			}
			scareOfficers(50);
			sld = CharacterFromID("Salasar");
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_166", "Logs.txt", "#space#", " "));
			AddCharacterHealth(pchar, -10);
			LAi_SetCheckMinHP(sld, 1000.0, false, "SpawnSalasarSupports_2");
		break;
		case "SpawnSalasarSupports_2":
			for(i = 0; i < 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SalSupps"+i, GetRandSkelModelClassic(), "skeleton", "man", 25, PIRATE, 0, true));
				FantomMakeCoolFighter(sld, 20, 90, 90, "blade01", "", 300);
				LAi_SetWarriorType(sld);
				PlaceCharacter(sld, "quest", "random_must_be_near");
				LAi_group_MoveCharacter(sld, "ReefAssholes");
				LAi_SetFightMode(sld, true);
			}
			sld = CharacterFromID("Salasar");
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_167", "Logs.txt", "#space#", " "));
			AddCharacterHealth(pchar, -10);
			LAi_SetCheckMinHP(sld, 5.0, true, "SpawnSalasarSupports_3");
		break;
		case "SpawnSalasarSupports_3":
			LAi_group_SetRelation("ReefAssholes", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_LocationFightDisable(loadedLocation, true);
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			sld = CharacterFromID("salasar");
			LAi_SetActorTypeNoGroup(sld);
			sld.dialog.filename = "Salasar.c";
			sld.dialog.currentnode = "Last";
			LAi_ActorDialog(sld, pchar, "", 4.0, 0);
			int salnum = sld.num;
			int npclocnum = sld.locid;
			for(i = 0; i < 10; i++)
			{
				sld = CharacterFromID("SalSupp"+i);
				LAi_KillCharacter(sld);
				sld = CharacterFromID("SalSupps"+i);
				LAi_KillCharacter(sld);
			}
			for(i = 0; i < salnum; i++)
			{
				sld = CharacterFromID("Skelet"+npclocnum+"_"+i);
				LAi_KillCharacter(sld);
			}
		break;
		case "SpawnGiantEvilSkeleton":
			if (loadedLocation.id != "DeckWithReefs" || CheckAttribute(pchar,"GiantEvilSkeletonSpawned")) {chrDisableReloadToLocation = false; break;}
			scareOfficers(50);
			log_info(GetConvertStrWithReplace("Variable_quests_reaction_168", "Logs.txt", "#space#", " "));
			if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("GiantEvilSkeleton", "PGG_Giant_5", "skeleton", "Giant_fast", iRank, PIRATE, 1, true)); // LEO: Превозмогаторам - страдать 01.12.2021
			else sld = GetCharacter(NPC_GenerateCharacter("GiantEvilSkeleton", "PGG_Giant_0", "skeleton", "Giant", iRank, PIRATE, 1, true));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_97", "Names.txt", "#space#", " ");
			sld.lastname = GetConvertStrWithReplace("Variable_quests_reaction_98", "Names.txt", "#space#", " ");
			sld.SaveItemsForDead = true;
			sld.cirassId = Items_FindItemIdx("cirass5");

			SetSPECIAL(sld, 10,10,10,10,10,10,10); // SPECIAL (Сила, Восприятие, Выносливость, Лидерство, Обучаемость, Реакция, Удача)
			FantomMakeCoolFighter(sld, 55, 100, 100, RandPhraseSimple("blade46","blade010"), "", 300); //40 лвл, Кракемарт или Кавалерийский палаш
			LAi_SetHP(sld,2500,2500);

			SelAllPerksToNotPCHAR(sld); //укоротил все перки
			if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки

			//установить ЛУ и КУ
			SetSelfSkill(sld, 100, 100, 100, 100, 100); //лёгкое, среднее, тяжёлое, пистолет, удача
			SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100); // лидерство, торговля, точность, пушки, навигация, ремонт, абордаж, защита, скрытность

			SetCharacterPerk(sld, "Grunt"); //рубака
			AddBonusEnergyToCharacter(sld, 50);
			TakeNItems(sld,"potion2",10);
			pchar.quest.GiantDead.win_condition.l1 = "NPC_Death";
			pchar.quest.GiantDead.win_condition.l1.character = "GiantEvilSkeleton";
			pchar.quest.GiantDead.win_condition = "GiantDead";
			ChangeCharacterAddressGroup(sld, loadedLocation.id, "item", "fire93");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "ReefAssholes");
			sld.chr_ai.special.valueCB = 100;
			sld.chr_ai.special.valueBB = 100;
			pchar.GiantEvilSkeletonSpawned = true;
		break;
		case "GiantDead":
			CaptureCapitol_ShoreBattleEnd();
			UnlockAchievement("AchKaskos", 3);
			pchar.talismanpreget = true;
			chrDisableReloadToLocation = false;
			log_info(GetConvertStrWithReplace("Variable_quests_reaction_169", "Logs.txt", "#space#", " "));
			log_info(GetConvertStrWithReplace("Variable_quests_reaction_170", "Logs.txt", "#space#", " "));
			CreateParticleSystemX("shadowstar",stf(loadedLocation.locators.item.item1.x),stf(loadedLocation.locators.item.item1.y),stf(loadedLocation.locators.item.item1.z),
				stf(loadedLocation.locators.item.item1.vz.x),stf(loadedLocation.locators.item.item1.vz.y),stf(loadedLocation.locators.item.item1.vz.z),0);
		break;

		case "Titch_Duel":
			LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(loadedLocation, true);
			sld = CharacterFromID("BlackBeardNPC");
			LAi_group_MoveCharacter(sld, "");
			sld.dialog.filename = "Capitans_dialog.c";
			sld.dialog.currentnode = "DuelWon";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		case "Titch_seabattle":
			LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(loadedLocation, true);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
            LAi_SetActorType(sld);
			sld.dialog.filename = "Capitans_dialog.c";
			sld.dialog.currentnode = "Titch_Seabattle_won";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		case "AngellicaDialog":
			sld = CharacterFromID("Angellica");
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "goto", "goto2");
			DoQuestReloadToLocation("LeFransua_town","reload","reload1", "");
			LAi_group_MoveCharacter(sld, "player");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;
		
		case "MG_ObezyanaKill":
			SetTimerCondition("MG_ObezyanaSkelet", 0, 0, 3, false);
		break;
		
		case "MG_ObezyanaSkelet":
			sld = GetCharacter(NPC_GenerateCharacter("MG_ObezyanaSkelet", "Monkey", "monkey", "monkey", sti(pchar.rank), PIRATE, -1, true));
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_99", "Names.txt", "#space#", " ");
			sld.lastname = "";
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			//sld.RebirthPhantom = true;
			LAi_SetLoginTime(sld, 21.99, 6.0);
			ChangeCharacterAddressGroup(sld, "Guadeloupe_deadlock", "monsters", "monster6");
		break;
		//Мини квест. Помощь Элен --->
		case "Raznoe_Pomosh_Elen":
			SetLocationCapturedState("PuertoPrincipe_town", true);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
		break;
		// <--- Помощь Элен
		
		//Квест. Макуауитль Куали --->
		case "Kuali_Spawn":
			//Куали
			sld = GetCharacter(NPC_GenerateCharacter("Kuali", "Miskito_3", "man", "man", 1, PIRATE, -1, false));
			ChangeCharacterAddressGroup(sld, "IndianVillage", "goto", "goto10");
			LAi_SetCitizenType(sld);
			sld.name = GetConvertStrWithReplace("Variable_quests_reaction_100", "Names.txt", "#space#", " ");
			sld.lastname = "";
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_group_MoveCharacter(sld, "ItzaIndian");
			sld.city = "SantaCatalina";
			sld.dialog.filename = "Quest\Kuali.c";
			sld.dialog.currentnode = "First time";
			sld.talker = 5;
		break;
		case "Peres_Kluch":
			AddQuestRecord("Kuali", "3");
			locations[FindLocation("Pearl_Jungle_09")].models.always.bones = "jungle9_bones";
			PChar.quest.Kuali_Palka.win_condition.l1 = "locator";
			PChar.quest.Kuali_Palka.win_condition.l1.location = "Pearl_Jungle_09";
			PChar.quest.Kuali_Palka.win_condition.l1.locator_group = "box";
			PChar.quest.Kuali_Palka.win_condition.l1.locator = "private1";
			PChar.quest.Kuali_Palka.win_condition = "Kuali_Palka";
			
			PChar.quest.Kuali_Podskazka.win_condition.l1 = "location";
			PChar.quest.Kuali_Podskazka.win_condition.l1.location = "Pearl_Jungle_09";
			PChar.quest.Kuali_Podskazka.win_condition = "Kuali_Podskazka";
			for (i=2; i<=4; i++)
			{
				sTemp = "Canib_"+(rand(5)+1);					
				sld = GetCharacter(NPC_GenerateCharacter("Kuali_Canib_"+i, sTemp, "man", "man", sti(pchar.rank)+2, PIRATE, -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				ChangeCharacterAddressGroup(sld, "Pearl_Jungle_09", "monsters",  "monster"+i);
			}
		break;
		case "Kuali_Podskazka":
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_171", "Logs.txt", "#space#", " "));
			if(InterfaceStates.EnabledQuestsMarks)
			{
				CreateLocationParticles("item", "box", "private1", 0, 0, 0, "");
			}
		break;
		case "Kuali_Palka":
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_172", "Logs.txt", "#space#", " "));
			AddQuestRecord("Kuali", "4");
			
			PChar.quest.Kuali_EtoNashaPalka.win_condition.l1 = "MapEnter";
			PChar.quest.Kuali_EtoNashaPalka.win_condition = "Kuali_EtoMoyaPalka";
			
			sld = CharacterFromID("Kuali");
			sld.dialog.filename = "Quest\Kuali.c";
			sld.dialog.currentnode = "ВозвращаемПалку_1";
			
			GiveItem2Character(PChar, "toporAZ");
		break;
		case "Kuali_EtoMoyaPalka":
			AddQuestRecord("Kuali", "5");
			CloseQuestHeader("Kuali");
			pchar.questdata.Kuali = 1;

			sld = CharacterFromID("Kuali");
			sld.lifeday = 0;
		break;
		// <--- Макуауитль Куали
		
		//Квест. Шаманка Чани --->
		
		case "CSP_Chani_Jemchug500":
			AddQuestRecord("ShamanChani", "2");
			AddQuestUserData("ShamanChani", "sSex", GetSexPhrase("","а"));
		break;
		
		case "CSP_Chani_2quest":
			pchar.quest.Chani_2quest = true;
		break;
		
		case "CSP_Chani_PoiskOtvara":
			AddQuestRecord("ShamanChani", "5");
			AddQuestUserData("ShamanChani", "sSex", GetSexPhrase("ёл","ла"));
		break;
		
		// <--- Шаманка Чани
	}
}

//Lipsar подпилил Хемфри для красоты --->
void FrameGiveMushket()
{
	sld = CharacterFromID("OffMushketer");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	SetLaunchFrameFormParam(GetConvertStr("Variable_quests_reaction_8", "Frames.txt"), "", 0.1, 2.0);
	LaunchFrameForm();
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld,"reload","reload1","none","","","",4.0);
}
//<--- Lipsar
void FrameAscoldVodka()
{
	pchar.GenQuest.CamShuttle = 2;
	WaitDate("",0,0,0,5,5);
	pchar.chr_ai.drunk = 600;
	SetLaunchFrameFormParam(GetConvertStr("Variable_quests_reaction_9", "Frames.txt"), "Reload_To_Location", 0.1, 2.0);
	SetLaunchFrameReloadLocationParam("BasTer_houseSp1", "barmen","bar1", "");
	LaunchFrameForm();
}

// boal -->
////////////////////////   общие методы //////////////////////////
void SetActorDialogAny2Pchar(string _charId, string _doQuest, float time1, float time2)
{
    Pchar.AutoQuest.NPCharId = _charId;
    Pchar.AutoQuest.Quest    = _doQuest;
    Pchar.AutoQuest.Time1    = time1;
    Pchar.AutoQuest.Time2    = time2;
}

//для универсализации (navy 17.10.05)
//уcтановки для телепорта ГГ в любую локацию с задержкой или без.
//Для отложенного вызова напр. AddDialogExitQuest()
void SetAnyReloadToLocation(string idLocation, string idGroup, string idLocator, string questName, int delayMonth, int delayDay, int delayHour, int delayMin)
{
    ref PChar = GetMainCharacter();

	PChar.AutoQuest.delayMonth	= delayMonth;
	PChar.AutoQuest.delayDay	= delayDay;
	PChar.AutoQuest.delayHour	= delayHour;
	PChar.AutoQuest.delayMin	= delayMin;

	PChar.AutoQuest.idLocation	= idLocation;
	PChar.AutoQuest.idGroup		= idGroup;
	PChar.AutoQuest.idLocator	= idLocator;
	PChar.AutoQuest.questName	= questName;
}

// Инициация таблички В это время на Беде  -->
// _FrameText - текст  Перенос строки делать "текст"+ NewStr() +"текст"
// _FrameQuest - квест после завершения таблички, если == "Reload_To_Location" см. SetLaunchFrameReloadLocationParam
// если же будет == "Run_Function" см. SetLaunchFrameRunFunctionParam
// _delay - время в с. отложения вызова таблички (нужно для неконфликта с заставкой загрузки локаций, где-то 0.1-1.5с)
// _autoEnd - время в с. автозавершения показа таблички, 4-6с на фразу
void SetLaunchFrameFormParam(string _FrameText, string _FrameQuest, float _delay, float _autoEnd)
{
    pchar.AutoQuest.FrameText    = _FrameText;
    pchar.AutoQuest.FrameQuest   = _FrameQuest;
    pchar.AutoQuest.FrameDelay   = _delay;
    pchar.AutoQuest.FrameAutoEnd = _autoEnd;
}

void SetLaunchFrameFormPic(string _FramePic)
{
    pchar.AutoQuest.FramePic    = _FramePic;
}
// метод для инициации перехода после таблички
void SetLaunchFrameReloadLocationParam(string idLocation, string idGroup, string idLocator, string questName)
{
    pchar.AutoQuest.FrameLocation      = idLocation;
    pchar.AutoQuest.FrameGroup         = idGroup;
    pchar.AutoQuest.FrameLocator       = idLocator;
    pchar.AutoQuest.FrameLocationQuest = questName;
}
// метод для вызова метода из кода после таблички _func - метод, _delay - задержка вызова метода после таблички в с.
void SetLaunchFrameRunFunctionParam(string _func, float _delay)
{
    pchar.AutoQuest.FrameFunction      = _func;
    pchar.AutoQuest.FrameFunctionDelay = _delay;
}
// Инициация таблички В это время на Беде  <--

void WaitNextHours(string qName)
{
	string sHour;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	sHour =  GetConvertStr("Variable_quests_reaction_10", "Frames.txt");
	if(sti(pchar.quest.waithours) == 1)		GetConvertStr("Variable_quests_reaction_11", "Frames.txt");
	if(sti(pchar.quest.waithours) == 24)	GetConvertStr("Variable_quests_reaction_12", "Frames.txt");
	if(isShipInside(pchar.location))
	{
		SetLaunchFrameFormParam(sHour, "", 0.1, 2.0);
	}
	else
	{
		SetLaunchFrameFormParam(sHour, "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	}

	WaitDate("", 0, 0, 0, sti(pchar.quest.waithours), 0);
	LaunchFrameForm();
	DeleteAttribute(pchar,"quest.waithours");
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

void WaitNextDays(string qName)
{
	string sHour;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	sHour = GetConvertStr("Variable_quests_reaction_13", "Frames.txt");
	if(isShipInside(pchar.location))
	{
		SetLaunchFrameFormParam(sHour, "", 0.1, 2.0);
	}
	else
	{
		SetLaunchFrameFormParam(sHour, "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	}

	WaitDate("", 0, 0, sti(pchar.quest.waithours), 0, 0);
	if (sti(pchar.quest.waithours)>1)
	{
		for (int i; i < sti(pchar.quest.waithours)-1; i++)
		{
			DailyEatCrewUpdate(); // boal
			ChangeImport();
			UpdateSmugglers();
			CheckOfficersHPMinus(); // ежедневное обновление дней для выздоровления офов
			CheckBook(); //Книги - Gregg
			CheckTrauma();//Тяжёлая травма
            SalaryNextDayUpdate();  // запрлата
			Log_QuestInfo("WorldSituationsUpdate SalaryNextDayUpdate");
			ProcessDayRepair();
			Group_FreeAllDead();
			QuestActions(); //eddy
			wdmEmptyAllOldEncounter();// homo чистка энкоутеров
			UpdateCrewExp();  // изменение опыта команды
			CheckTraining();//треня оффов
			UpdateCrewInColonies(); // пересчет наемников в городах
            UpdateFame();   // это теперь известность репутации
			GenerateRumour() //homo 05/07/06
		}
	}
	LaunchFrameForm();
	DeleteAttribute(pchar,"quest.waithours");
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

void RemovePatent()
{
	RemoveCharacterEquip(pchar, "patent");
    if (CheckCharacterItem(Pchar, "patent_eng"))
    {
        TakeItemFromCharacter(pchar, "patent_eng");
        ChangeCharacterReputation(pchar, -10);
    }
    if (CheckCharacterItem(Pchar, "patent_fra"))
    {
        TakeItemFromCharacter(pchar, "patent_fra");
        ChangeCharacterReputation(pchar, -10);
    }
    if (CheckCharacterItem(Pchar, "patent_spa"))
    {
        TakeItemFromCharacter(pchar, "patent_spa");
        ChangeCharacterReputation(pchar, -10);
    }
    if (CheckCharacterItem(Pchar, "patent_hol"))
    {
        TakeItemFromCharacter(pchar, "patent_hol");
        ChangeCharacterReputation(pchar, -10);
    }
}

void StartActorSelfDialog(string _CurrentNode)
{
    LAi_SetActorType(pchar);
    LAi_CharacterSaveAy(pchar);
    locCameraSleep(true);
    /*if (stf(pchar.chr_ai.type.ay) > 0)
    {
    	CharacterTurnAy(pchar,  -PI + abs(stf(pchar.chr_ai.type.ay)));  // 180 == 1
    }
    else
    {
    	CharacterTurnAy(pchar,  PI - abs(stf(pchar.chr_ai.type.ay)));  // 180 == 1
    }*/
    pchar.Dialog.CurrentNode = _CurrentNode;
    LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
}

//#20181102-03
void NationUpdate()
{
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
    }
}

// подъем флагов
void Flag_Change(int iNation)
{
	PChar.nation = iNation;
	Ship_FlagRefresh(PChar); //флаг на лету
	SetNationToOfficers(iNation);

	for (int i = 0; i < MAX_NATIONS; i++)
	{
		SetNationRelation2MainCharacter(i, GetNationRelation(iNation,i));
	}
	string sCitiz = ToUpper(GetNationNameByType(iNation)+"_CITIZENS");
	LAi_group_SetRelation(sCitiz, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	DoQuestCheckDelay("NationUpdate", 3.0);
	UpdateRelations();
	if(bSeaActive)
	{
	    RefreshBattleInterface();
	    //#20181021-01
	    SetSchemeForSea();
	}
    else { if(IsEntity(worldMap))
        SetSchemeForMap();
    }
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_SET_NATION_FLAG,  sti(pchar.nation));
}

void Flag_Rerise()
{
	Flag_Change(sti(pchar.nation));
}

// blackthorn - генератор "Проклятый капитан"
void QuestCursedSceleton()
{
	ref sld;
	//sld = GetCharacter(CharacterFromID("CursedSkeleton"));
	if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("CursedSkeleton", "PGG_Skeletcap_0", "skeleton", "skeleton_fast", sti(pchar.rank)+20, PIRATE, 1, true));
	else sld = GetCharacter(NPC_GenerateCharacter("CursedSkeleton", "PGG_Skeletcap_0", "skeleton", "skeleton", sti(pchar.rank)+20, PIRATE, 1, true));
	FantomMakeCoolFighter(sld, sti(pchar.rank)+20, 100, 100, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol3"), MOD_SKILL_ENEMY_RATE*3*4);
	DeleteAttribute(sld, "SuperShooter");
	int hitpoints = rand(sti(pchar.rank)*15)+1000;
	LAi_SetHP(sld, hitpoints, hitpoints);

	sld.name = GetConvertStrWithReplace("Variable_quests_reaction_101", "Names.txt", "#space#", " ");
	sld.lastname = "";
	AddBonusEnergyToCharacter(sld, 200);

	sld.Dialog.CurrentNode = "First time";
	sld.dialog.filename = "Cursed_Skeleton.c";
	if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки

	LAi_group_Delete("cursed");
	Group_FindOrCreateGroup("cursed");
	Group_AddCharacter("cursed", sld.id);
	//LAi_group_SetRelation("cursed", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//LAi_group_SetRelation("cursed", LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	chrDisableReloadToLocation = true;
	pchar.quest.CursedSceleton.win_condition.l1 = "NPC_Death";
	pchar.quest.CursedSceleton.win_condition.l1.character = sld.id;
	pchar.quest.CursedSceleton.win_condition = "OpenTheDoors";

	sld.cirassId = Items_FindItemIdx("cirass5");  // предмета нет, но влияение есть
	sld.SaveItemsForDead = true;
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	//LAi_group_MoveCharacter(sld, "TmpEnemy");
	LAi_SetActorType(sld);
    LAi_SetActorType(pchar);
	sld.quest.meeting = "2";
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
}