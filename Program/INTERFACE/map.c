string totalInfo = "";
bool isSkipable = false;
bool bEncType   = false;
string  sQuestSeaCharId = "";

void InitInterface(string iniName)
{
	EngineLayersOffOn(true);
	SetTimeScale(0.0);

    bQuestCheckProcessFreeze = true;//лочим квест и карту
    bEncType = false; //обычный тип

    GameInterface.title = "title_map";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
    SetFormatedText("MAP_CAPTION", XI_ConvertString("title_map"));
	SetFormatedText("INFO_TEXT_QUESTION", XI_ConvertString("MapWhatYouWantToDo"));
	SetCurrentNode("INFO_TEXT_QUESTION");
	SetNewPicture("INFO_PICTURE", "loading\SeaEnc_NavalSignal.tga");
	SetNewPicture("INFO_PICTURE2", "loading\SeaEnc_"+rand(3)+".tga");

    wdmRecalcReloadToSea();//выношу из CalculateInfoData
	SetFormatedText("INFO_TEXT",totalInfo);
	CalculateInfoData();//проверяем возможность скипнуть энку, там же вызов 
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); // Выход на море
	SetEventHandler("exitCancel","ProcessCancelExit",0); // Выход на море по крестику или Esc
	SetEventHandler("ievnt_command","ProcCommand",0); // выход на карту только тут (по НЕТ)
	SetEventHandler("evntDoPostExit","DoPostExit",0); // выход из интерфейса

	PlayVoice("interface\"+LanguageGetLanguage()+"_EvShip"+rand(3)+".wav");
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_MAP_EXIT );
	wdmReloadToSea();
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_MAP_EXIT );
	if (GetSelectable("B_CANCEL")==0) wdmReloadToSea();
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

    SetTimeScale(1.0);
	TimeScaleCounter = 0;
	if(IsPerkIntoList("TimeSpeed"))
	{
		DelPerkFromActiveList("TimeSpeed");
	}

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	PostEvent("StopQuestCheckProcessFreeze", 100);//boal 230804 заморозка проверки квестов
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	ref chr;
	switch(nodName)
	{
	case "B_OK":
		if(comName=="activate" || comName=="click")
		{
			if (sQuestSeaCharId != "") wdmEnterSeaQuest(sQuestSeaCharId);

			// напасть
   			IDoExit(RC_INTERFACE_MAP_EXIT);
			wdmReloadToSea();
			if(CheckAttribute(PChar, "GenerateShipWreck.ShipInMap"))
			{
				if(GetCharacterIndex(PChar.GenerateShipWreck.ShipInMap) != -1)
				{
					chr = CharacterFromID(PChar.GenerateShipWreck.ShipInMap);
					if(CheckAttribute(chr, "ShipWreck")) ShipWreckInSea(chr);
				}
			}
		}
		if(comName=="downstep")
		{
			if(GetSelectable("B_CANCEL"))	{SetCurrentNode("B_CANCEL");}
		}
	break;

	case "B_CANCEL":
		if(comName=="activate" || comName=="click")
		{
			//пропустить
			pchar.SkipEshipIndex = pchar.eshipIndex;
			IDoExit(RC_INTERFACE_MAP_EXIT);
		}
		if(comName=="upstep")
		{
			if(GetSelectable("B_OK"))	{SetCurrentNode("B_OK");}
		}
	break;
	}
}
void wdmRecalcReloadToSea()
{
	worldMap.encounter.type = "";
	totalInfo = "";
	int iRand;

	int k = 0;//счетчик для строк таблицы с картинками корабликов
	int iShipType, n, iS, q;
	string sCol, sRow1, sShip;
	//string sShipMode;
	//aref arShipModes;
	aref arAttr, arShips;//типы кораблей в энке

	int numEncounters = wdmGetNumberShipEncounters();
	int isShipEncounterType = 0;
	Log_TestInfo(GetConvertStrWithReplace("Variable_map_1", "Interface.txt", "#space#", " "));

	for(int i = 0; i < numEncounters; i++)
	{
		if(wdmSetCurrentShipData(i))
		{
		   if(MakeInt(worldMap.encounter.select) == 0) continue;
			isShipEncounterType++;

			string encID = worldMap.encounter.id;

			aref rEncounter;
			makearef(rEncounter, worldMap.encounters.(encID).encdata);

			int iRealEncounterType = sti(rEncounter.RealEncounterType);

			if (isShipEncounterType > 1 && iRealEncounterType < ENCOUNTER_TYPE_BARREL)
			{
			    totalInfo = totalInfo + "\n" + XI_ConvertString("But in the same way");
			}

			int iNumMerchantShips = 0;
			int iNumWarShips = 0;
			if(CheckAttribute(rEncounter, "NumMerchantShips"))
			{
				iNumMerchantShips = sti(rEncounter.NumMerchantShips);
			}
			if(CheckAttribute(rEncounter, "NumWarShips"))
			{
				iNumWarShips = sti(rEncounter.NumWarShips);
			}

			if (CheckAttribute(rEncounter, "CharacterID"))
			{
                iNumWarShips = GetCharacterIndex(rEncounter.CharacterID);
                if (iNumWarShips != -1)
                {
					sQuestSeaCharId = characters[iNumWarShips].id; // квестовый
					PChar.GenerateShipWreck.ShipInMap = sQuestSeaCharId;
					if (CheckAttribute(&characters[iNumWarShips], "mapEnc.Name"))
					{
						totalInfo = totalInfo + characters[iNumWarShips].mapEnc.Name;
					}
					else
					{
						totalInfo = totalInfo + "'" + characters[iNumWarShips].ship.name + "'."
					}
				}
				bEncType = true;
			}
			else
			{
				if(iRealEncounterType <= ENCOUNTER_TYPE_MERCHANT_LARGE)
				{
					totalInfo = totalInfo + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("of traders");
				}
				if(iRealEncounterType >= ENCOUNTER_TYPE_MERCHANT_GUARD_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_MERCHANT_GUARD_LARGE)
				{
					totalInfo = totalInfo + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
				}
				if(iRealEncounterType >= ENCOUNTER_TYPE_ESCORT_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_ESCORT_LARGE)
				{
					totalInfo = totalInfo + XI_ConvertString("Trade caravan") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
				}

				if(iRealEncounterType >= ENCOUNTER_TYPE_PATROL_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_PATROL_LARGE)
				{
					totalInfo = totalInfo + XI_ConvertString("Patrol") + GetTextOnShipsQuantity(iNumWarShips);
				}

				if(iRealEncounterType >= ENCOUNTER_TYPE_PIRATE_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_PIRATE_LARGE)
				{
					totalInfo = totalInfo + XI_ConvertString("Pirates") + GetTextOnShipsQuantity(iNumWarShips);
				}

				if(iRealEncounterType >= ENCOUNTER_TYPE_SQUADRON && iRealEncounterType <= ENCOUNTER_TYPE_ARMADA)
				{
					totalInfo = totalInfo + XI_ConvertString("Naval squadron") + GetTextOnShipsQuantity(iNumWarShips);
				}

				if(iRealEncounterType == ENCOUNTER_TYPE_PUNITIVE_SQUADRON)
				{
					totalInfo = totalInfo + XI_ConvertString("Punitive expedition") + GetTextOnShipsQuantity(iNumWarShips);
				}
				if(iRealEncounterType == ENCOUNTER_TYPE_BARREL)
				{
					totalInfo = totalInfo + XI_ConvertString("SailingItems");
				}

				if(iRealEncounterType == ENCOUNTER_TYPE_BOAT)
				{
					totalInfo = totalInfo + XI_ConvertString("ShipWreck");
				}
			}
			if(sti(rEncounter.Nation) < 0)
			{
        		totalInfo = totalInfo + GetConvertStrWithReplace("Variable_map_2", "Interface.txt", "#space#", " ");
      		}

			if(iRealEncounterType != ENCOUNTER_TYPE_BARREL && iRealEncounterType != ENCOUNTER_TYPE_BOAT)
            {
                string nationname = "";
                switch(sti(rEncounter.Nation))
                {
                    case ENGLAND:
                        totalInfo = totalInfo + XI_ConvertString("under english flag");
                        nationname = "Eng";
                    break;
                    case FRANCE:
                        totalInfo = totalInfo + XI_ConvertString("under french flag");
                        nationname = "Fra";
                    break;
                    case SPAIN:
                        totalInfo = totalInfo + XI_ConvertString("under spanish flag");
                        nationname = "Spa";
                    break;
                    case HOLLAND:
                        totalInfo = totalInfo + XI_ConvertString("under dutch flag");
                        nationname = "Hol";
                    break;
                    case PIRATE:
                        totalInfo = totalInfo + ".";
                        nationname = "Pir";
                    break;
                }
            }

			if(GetNationRelation2MainCharacter(sti(rEncounter.Nation)) != RELATION_ENEMY)
			{
				isSkipable = true;
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_OK",0, "#"+XI_ConvertString("GetCloser"));
			}
			else
			{
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_OK",0, "#"+XI_ConvertString("map_yes"));
			}
		}

		if (CheckAttribute(rEncounter, "CharacterID"))
		{
			string sGroupID = Characters[iNumWarShips].SeaAI.Group.Name;
			ref rGroup = Group_FindOrCreateGroup(sGroupID);
			if (!CheckAttribute(rGroup,"quest")) { trace("EncCheck map-interface. Broken group: " + sGroupID);}
			else
			{
				makearef(arShips, rGroup.Quest);
				iNumShips = GetAttributesNum(arShips);
			}
		}
		else
		{
			makearef(arShips, rEncounter.shiptypes); 
			//makearef(arShipModes, rEncounter.shipmodes); //не удалось две картинки в одну ячейку запихнуть
			iNumShips = GetAttributesNum(arShips);
		}

		//Заполнение таблицы картинками корабликов
		if (iNumShips>9) //Золотой флот в три строки	
		{
			int k1=0;
			for(q = 1; q < 10; q++)//фикс - если первой ячейки нет - движок не рисует всю таблицу
			{
				sCol = "td" + q;
				sRow1 = "tr" + (k + 1);
				GameInterface.TABLE_ENC.hr.(sCol).str = "";
				GameInterface.TABLE_ENC.(sRow1).(sCol).str = "";
				sRow1 = "tr" + (k + 2);
				GameInterface.TABLE_ENC.hr.(sCol).str = "";
				GameInterface.TABLE_ENC.(sRow1).(sCol).str = "";
				sRow1 = "tr" + (k + 3);
				GameInterface.TABLE_ENC.hr.(sCol).str = "";
				GameInterface.TABLE_ENC.(sRow1).(sCol).str = "";
			}
			for(iS=0; iS<iNumShips; iS++)
			{
				if (CheckAttribute(rEncounter, "CharacterID"))//особые одиночные энкаунтеры
				{	
					arAttr = GetAttributeN(arShips, iS);
					iShipType = sti(RealShips[sti(Characters[sti(arAttr.index)].ship.type)].basetype);
				}
				else
				{
					iShipType = GetAttributeValue(GetAttributeN(arShips, iS));
					//sShipMode = GetAttributeValue(GetAttributeN(arShipModes, iS));
				}
//q1 - номер строки из трёх, iS - номер корабля с нуля, iNumShips - общее число кораблей, нужно определить номер колонки и общее число колонок для центрирования
//			1	4	7	10
//	ф	0	3	6	9	12
//			2	5	8	11
				n = (iS+2)/3 + 6 - (1+(iNumShips+1)/3)/2;//9 колонок - центрируем от фактического числа кораблей
				sCol = "td" + n;
				switch (iS%3)
				{
					case 0: k1 = 2; break;
					case 1: k1 = 1; break;
					case 2: k1 = 3; break;
				}
				sRow1 = "tr" + (k + k1);
				sShip = shipstypes[iShipType].Name;
				GameInterface.TABLE_ENC.(sRow1).(sCol).str = shipstypes[iShipType].Class;
				GameInterface.TABLE_ENC.(sRow1).(sCol).textoffset = "35,-16";
				if ( (1+(iNumShips+1)/3)%2 ) GameInterface.TABLE_ENC.(sRow1).(sCol).textoffset = "-13,-16";
				GameInterface.TABLE_ENC.(sRow1).(sCol).icon1.texture = "interfaces\\ships\\" + sShip + ".tga.tx";
				GameInterface.TABLE_ENC.(sRow1).(sCol).icon1.width = 47;
				GameInterface.TABLE_ENC.(sRow1).(sCol).icon1.height = 47;
				GameInterface.TABLE_ENC.(sRow1).(sCol).icon1.offset = "-2,0";
				if ( (1+(iNumShips+1)/3)%2 ) GameInterface.TABLE_ENC.(sRow1).(sCol).icon1.offset = "-26,0";
			}
			sCol = "td" + (5 - (1+(iNumShips+1)/3)/2);//iS = -1
			sRow1 = "tr" + (k + 2);//средняя строка для флага
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.group  = "NATIONS";
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.image = Nations[sti(rEncounter.Nation)].Name;//флаг эскадры сюда
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.uv = "0,0,0,0";
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.width = 48;
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.height = 48;
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.offset = "-3, -1";
			if ( (1+(iNumShips+1)/3)%2 ) GameInterface.TABLE_ENC.(sRow1).(sCol).icon.offset = "-27, -1";
			k++;
			k++;
			k++;
		}
		else
		{
			for(q = 1; q < 10; q++)//фикс - если первой ячейки нет - движок не рисует всю таблицу
			{
				sCol = "td" + q;
				sRow1 = "tr" + (k + 1);
				GameInterface.TABLE_ENC.hr.(sCol).str = "";
				GameInterface.TABLE_ENC.(sRow1).(sCol).str = "";
			}
			for(iS=0; iS<iNumShips; iS++)
			{
				if (CheckAttribute(rEncounter, "CharacterID"))//особые одиночные энкаунтеры
				{	
					arAttr = GetAttributeN(arShips, iS);
					iShipType = sti(RealShips[sti(Characters[sti(arAttr.index)].ship.type)].basetype);
				}
				else
				{
					iShipType = GetAttributeValue(GetAttributeN(arShips, iS));
					//sShipMode = GetAttributeValue(GetAttributeN(arShipModes, iS));
				}
				n = iS + 6 - iNumShips/2;//9 колонок - центрируем от фактического числа кораблей
				sCol = "td" + n;
				sRow1 = "tr" + (k + 1);
				sShip = shipstypes[iShipType].Name;
				GameInterface.TABLE_ENC.(sRow1).(sCol).str = shipstypes[iShipType].Class;
				GameInterface.TABLE_ENC.(sRow1).(sCol).textoffset = "35,-16";
				if (iNumShips%2) GameInterface.TABLE_ENC.(sRow1).(sCol).textoffset = "-13,-16";
				GameInterface.TABLE_ENC.(sRow1).(sCol).icon1.texture = "interfaces\\ships\\" + sShip + ".tga.tx";
				GameInterface.TABLE_ENC.(sRow1).(sCol).icon1.width = 47;
				GameInterface.TABLE_ENC.(sRow1).(sCol).icon1.height = 47;
				GameInterface.TABLE_ENC.(sRow1).(sCol).icon1.offset = "-2,0";
				if (iNumShips%2) GameInterface.TABLE_ENC.(sRow1).(sCol).icon1.offset = "-26,0";
/*
GameInterface.TABLE_ENC.(sRow1).(sCol).icon2.group = "ICONS_SPEC";
switch (sShipMode)//крашит вторая иконка - взять из шрифта символ???
{
case "trade":	GameInterface.TABLE_ENC.(sRow1).(sCol).icon2.image = "commerce skill icon"; break;
case "war": 	GameInterface.TABLE_ENC.(sRow1).(sCol).icon2.image = "grappling skill icon"; break;
case "pirate": 	GameInterface.TABLE_ENC.(sRow1).(sCol).icon2.image = "exit button"; break;
}
GameInterface.TABLE_ENC.(sRow1).(sCol).icon2.width = 14;
GameInterface.TABLE_ENC.(sRow1).(sCol).icon2.height = 14;
GameInterface.TABLE_ENC.(sRow1).(sCol).icon2.offset = "-1, 15";		//its(-1-24*(iNumShips%2))+",15";
*/
			}
			sCol = "td" + (5 - iNumShips/2);//iS = -1
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.group  = "NATIONS";
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.image = Nations[sti(rEncounter.Nation)].Name;//флаг эскадры сюда
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.uv = "0,0,0,0";
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.width = 48;
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.height = 48;
			GameInterface.TABLE_ENC.(sRow1).(sCol).icon.offset = "-3, -1";
			if (iNumShips%2) GameInterface.TABLE_ENC.(sRow1).(sCol).icon.offset = "-27, -1";
			k++;
		}
	}
	Table_UpdateWindow("TABLE_ENC");

	Log_TestInfo("isShipEncounterType :" + isShipEncounterType);
	if (isShipEncounterType > 1)
    {
       totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("battle on course") + "\n" + totalInfo;
    }
	else
	{
		if(iRealEncounterType == ENCOUNTER_TYPE_BARREL || iRealEncounterType == ENCOUNTER_TYPE_BOAT)
		{
			if(iRealEncounterType == ENCOUNTER_TYPE_BARREL)
			{
				SetNewPicture("INFO_PICTURE2", "loading\BarrelEnc_"+rand(2)+".tga");
			}
			if(iRealEncounterType == ENCOUNTER_TYPE_BOAT)
			{
				SetNewPicture("INFO_PICTURE2", "loading\BarrelEnc_"+rand(2)+".tga");
			}
			totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("SpecialSituation") + totalInfo;
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_OK",0, "#"+XI_ConvertString("GetItemToBort"));
		}
		else
		{
			totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("someone sails") + "\n" + totalInfo;

		}
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
	if (IsCharacterPerkOn(GetMainCharacter(), "SailingProfessional") || pchar.space_press == "1")
	{
		isSkipable = true;
	}
	SetCurrentNode("B_OK");

    float iSKILL_SNEAK = GetSummonSkillFromNameToOld(pchar, SKILL_SNEAK);

    SetSelectable("B_CANCEL",true);
    if (iSKILL_SNEAK < 1) iSKILL_SNEAK = 1;
	if( (rand(100) / iSKILL_SNEAK) > GetSummonSkillFromNameToOld(pchar, SKILL_SAILING) )// сделать учет скила навигация для запрета кнопки Нет
	{
        if (!isSkipable && !bBettaTestMode) SetSelectable("B_CANCEL",false);
	}
	if (pchar.space_press == "1") bEncType = false;

	if (bEncType && !bBettaTestMode) // спец тип не пропустить
	{
        SetSelectable("B_CANCEL",false);
	}
	pchar.space_press = 0;
}
