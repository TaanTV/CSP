// BOAL 27/06/06 переделка под нужны ВМЛ, все стерли и написали заново.
void SeaHunterCheck()
{
	int    j, i;
	string typeHunter, sGroup, sCapId;
	ref    sld;

	SetTimerCondition("SeaHunterCheck", 0, 0, 6+rand(20), true);
    for (j=0; j< MAX_NATIONS; j++)
    {
        if (j == PIRATE) continue;
        // открыть, если не нужны мирные охотники if(NationsRelations2MainCharacter[j] != RELATION_ENEMY) continue;

        typeHunter = NationShortName(j);

        if (ChangeCharacterNationReputation(pchar, j, 0) <= -10)// Минус это НЗГ
        {
            sCapId = typeHunter + "Hunter0";
            sGroup = "Sea_" + sCapId + "1";

			Group_DeleteGroup(sGroup);
			Group_FindOrCreateGroup(sGroup);
            for (i = 1; i <= 7; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, j, 20, true));
                SetShipHunter(sld);
                sld.WatchFort = true; //видеть форты
                SetFantomParamHunter(sld); //крутые парни
                SetCaptanModelByEncType(sld, "war");
                sld.AlwaysEnemy = true;
                sld.DontRansackCaptain = true;
                sld.mapEnc.type = "war";
                sld.mapEnc.Name = GetConvertStrWithReplace("Variable_bountyhunters_1", "Names.txt", "#space#", " ");
				sld.hunter = "hunter";
				//sld.mapEnc.worldMapShip = "Manowar_gold";
                Group_AddCharacter(sGroup, sCapId + i);

                if (i == 1 || GetCharacterShipClass(sld) == 1) SetRandGeraldSail(sld, sti(sld.Nation));

                if (abs(ChangeCharacterNationReputation(pchar, j, 0)) < (i * 15)) break; // добавим капитана только когда положенно
            }

            Group_SetGroupCommander(sGroup, sCapId+ "1");
            Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
            Group_LockTask(sGroup);
			//Lipsar подпилил функцию
            Map_CreateHunter("", sCapId + "1", 8);// LEO: Тестируем. Будет душно, вырубим, либо переделаем на здоровый лад.
        }
    }
}

void SetShipHunter(ref Hunter)	//эта функция распространяется на ДУ, ОЗГ, морской патруль, охрану торговцев по квесту?
{
	if(makeint(pchar.rank) >= 1 && makeint(pchar.rank) <=5) Hunter.Ship.Type = GenerateShipExt(GetShipTypeExt(6, 6,"war", sti(Hunter.nation)), true, Hunter); // 6 класс
	if(makeint(pchar.rank) >= 5 && makeint(pchar.rank) <=10) Hunter.Ship.Type = GenerateShipExt(GetShipTypeExt(5, 5,"war", sti(Hunter.nation)), true, Hunter); // 5 класс
	if(makeint(pchar.rank) >= 10 && makeint(pchar.rank) <=15) Hunter.Ship.Type = GenerateShipExt(GetShipTypeExt(4, 4,"war", sti(Hunter.nation)), true, Hunter); // 4 класс
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) <=20) Hunter.Ship.Type = GenerateShipExt(GetShipTypeExt(3, 3,"war", sti(Hunter.nation)), true, Hunter); // 3 класс
	if(makeint(pchar.rank) >= 20 && makeint(pchar.rank) <=30) Hunter.Ship.Type = GenerateShipExt(GetShipTypeExt(2, 2,"war", sti(Hunter.nation)), true, Hunter); // 2 класс
	if(makeint(pchar.rank) > 30 ) Hunter.Ship.Type = GenerateShipExt(GetShipTypeExt(2, 1,"war", sti(Hunter.nation)), true, Hunter); // 2 - 1 класс
	// <-- ОЗГ используют нац. корабли
	SetBaseShipData(Hunter);
    SetCrewQuantityFull(Hunter);
	RealShips[sti(Hunter.ship.type)].ship.upgrades.sails = 24 + rand(13); // LEO: Спец. паруса ОЗГ
	Hunter.OZG = true;

    DeleteAttribute(Hunter,"ship.sails");
    RepairMasts(Hunter);
    DeleteAttribute(Hunter,"ship.blots");

    if (Hunter.nation == PIRATE)
    {
        Fantom_SetCannons(Hunter, "pirate");
        Fantom_SetBalls(Hunter, "pirate");
		Fantom_SetUpgrade(Hunter, "pirate");
    }
    else
    {
        Fantom_SetCannons(Hunter, "war");
        Fantom_SetBalls(Hunter, "war");
		Fantom_SetUpgrade(Hunter, "hunter");
    }
}
// ОЗГИ на суше (порт и бухта)
void LandHunterReactionResult(ref loc)  // отработает после входа в локацию, но после квест_реакшна на вход
{
	int    j, i, k;
	string typeHunter, sTemp, sCapId;
	ref    sld;
	bool   ok, order;

	//if (actLoadFlag) return; // идёт лоад
	if (LAi_IsCapturedLocation) return;
	if (chrDisableReloadToLocation) return; // идёт некий другой квест с запретом выхода
	if (loc.type != "town" && loc.type != "seashore" && loc.type != "port") return;
	if (CheckAttribute(Pchar, "GenQuest.Hunter2Pause"))
	{
		DeleteAttribute(Pchar, "GenQuest.Hunter2Pause");
		return;
	}
	if (LAi_grp_alarmactive == true)  return;  // уже ГГ кто-то бьет

	//if (GetQuestPastDayParam("Land_HunterTimerHasBeen") == 0) return; // сегодня уже были
	for (j=0; j< MAX_NATIONS; j++)
    {
        if (j == PIRATE) continue;
        // открыть, если не нужны мирные охотники if(NationsRelations2MainCharacter[j] != RELATION_ENEMY) continue;

        typeHunter = NationShortName(j);
        if (GetQuestPastDayParam("Land_HunterTimer" + typeHunter) > (7 + rand(7)))
        {
			SaveCurrentQuestDateParam("Land_HunterTimer" + typeHunter); // запомним, даже если нет озгов, выход их ФОР отложит озгов до след раза у др нации

			order = false;
			if (j == SPAIN)
			{
				if (pchar.name == GetConvertStrWithReplace("Variable_bountyhunters_2", "Names.txt", "#space#", " ") || CheckAttribute(pchar, "PGGWhisperComplete"))
				{
					if (!CheckAttribute(pchar,"OrderDestroyed"))
					{
						if(CheckAttribute(pchar, "Whisper.DeSouzaTalked"))
						{
							order = true;
						}
						if (pchar.name != "Виспер" && sti(pchar.rank) >= 15)
						{
							order = true;
						}
						//Первые несколько встреч обязательны, потом шанс постепенно снижается
						if (order && CheckAttribute(pchar, "OrderHunter") && sti(pchar.OrderHunter) > 3 && rand(sti(pchar.OrderHunter)) > 2)
						{
							order = false;
						}
					}
				}

			}

			if (ChangeCharacterNationReputation(pchar, j, 0) <= -10 || order)// Минус это НЗГ
	        {
	            Log_QuestInfo("LandHunterReactionResult " + typeHunter);
				sCapId = typeHunter + "LandHunter0";
	            sTemp = "LAND_HUNTER";
				ok = true;
				//arrayNPCModelHow = 0;
				k = 8;
	            for (i = 1; i <= k; i++)
	            {
	                if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "OZG_" + (rand(9) + 1), "man", "man_fast", 30+rand(10), j, 0, true));
	                else sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "OZG_" + (rand(9) + 1), "man", "man", 30+rand(10), j, 0, true));
	                SetFantomParamHunter(sld); //крутые парни
	                sld.name 	= GetConvertStr("Variable_bountyhunters_0.1", "Names.txt");
	                sld.lastname 	= "";
	                sld.Dialog.CurrentNode = "First time";
	                sld.dialog.filename = "Hunter_dialog.c";
	                sld.greeting = "Gr_HUNTER";
					if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
	                sld.location = "none"; // вот где порылась собака!!!!!!!!!!!

	                //SetOZGModel(sld);
/* 	                k = 0;
					while (!CheckNPCModelUniq(sld) && k < 10)
					{
					    k++;
         				SetOZGModel(sld);
					} */
					//arrayNPCModel[arrayNPCModelHow] = sld.model;
					//arrayNPCModelHow++;

					if (order && i == 1)
					{
						FantomMakeCoolFighter(sld, 20, 100, 100, "blade22", "pistol_grapebok", 100);
						sld.SaveItemsForDead = true;
						sld.model = "PGG_Vincento_"+rand(5);
						sld.Heromodel = "PGG_Vincento_"+rand(5); // fix
						FaceMaker(sld);
						sld.name 	= GetConvertStr("Variable_bountyhunters_0.2", "Names.txt");
						sld.Dialog.CurrentNode = "OrderHunter";
						sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
					}

	                LAi_SetActorTypeNoGroup(sld);
	                LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Battle_Hunters_Land");
	                if (PlaceCharacter(sld, "goto", "random_must_be_near") == "" && i == 1) // fix если вдруг нет в локации
	                {
	                    ok = false;
	                    break;
	                }
	                LAi_ActorFollow(sld, pchar, "", 8.0);
	                LAi_group_MoveCharacter(sld, sTemp);
	                if (abs(ChangeCharacterNationReputation(pchar, j, 0)) < (i * 9)) break; // число от НЗГ
	            }

				LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

				LAi_group_ClearAllTargets();
				LAi_SetFightModeForOfficers(false);
				if (ok)
	            {
	                pchar.HunterCost = abs(ChangeCharacterNationReputation(pchar, j, 0));
	                PChar.HunterCost = makeint(PChar.HunterCost)*2000 + rand(5000); //сразу генерим
	                PChar.HunterCost.TempHunterType = typeHunter;
	                PChar.HunterCost.Qty = i;// fix
	                sld = characterFromID(sCapId + "1");
	                LAi_type_actor_Reset(sld);
	                LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		    		chrDisableReloadToLocation = true;
		    		DoQuestCheckDelay("OpenTheDoors", 5.0);
	            }
	            break;
	        }
        }
    }
}

void CheckForScam(ref location)
{
	if (CheckAttribute(pchar,"ScamFanActive") && rand(9)==0 && !CheckAttribute(pchar,"ScamDestroyed") && location.id != "FencingTown_ExitTown")
	{
		ref sld = CharacterFromID("ScamCharacter");
		bool isplaced = false;
		/*if (CheckAttribute(loadedLocation,"locators.officers"))
		{
			isplaced = true;
		}
		else
		{*/
			if (CheckAttribute(location,"locators.goto"))
			{
				//PlaceCharacter(sld, "goto", "random_must_be_near");
				isplaced = true;
			}
		//}
		if (chrDisableReloadToLocation || LAi_group_IsActivePlayerAlarm() || !CheckSaveGameEnabled() || sld.location != location.id) isplaced = false;
		if (isplaced)
		{
			//ChangeCharacterAddressGroup(sld,loc.id,"reload","reload1");
			chrDisableReloadToLocation = true;
			InterfaceStates.DisFastTravel = true;
			LAi_SetActorTypeNoGroup(sld);
			sld.dialog.currentnode = "CoolStory";
			LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		}
	}
}