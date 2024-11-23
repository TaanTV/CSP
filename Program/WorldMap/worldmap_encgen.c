

//--------------------------------------------------------------------------------------
//Генерация энкоунтеров
//--------------------------------------------------------------------------------------

//Частота штормов в секунду
#define WDM_STORM_RATE   0.0001
//Частота торговцев в секунду
#define WDM_MERCHANTS_RATE		0.09
//Частота воюищих кораблей в секунду
#define WDM_WARRING_RATE		0.015
//Частота нападающих кораблей в секунду
#define WDM_FOLLOW_RATE  0.025
//Частота специальных событий  (бочка или шлюпка) в секунду
#define WDM_SPECIAL_RATE  		0.002

//MAX, это поменял Я!!!!!!! Шуршунчик.
// Boal - учите мат. часть, г-н Шуршунчик. не работает это до начала новой игры, всегда по уполчанию идёт. Дефайн правильно, тем более  iEncountersRate далее работает
//float WDM_FOLLOW_RATE = 0.025 * iEncountersRate;
//float WDM_STORM_RATE = 0.0001 * iEncountersRate;


//--------------------------------------------------------------------------------------


float wdmTimeOfLastStorm = 0.0;
float wdmTimeOfLastMerchant = 0.0;
float wdmTimeOfLastWarring = 0.0;
float wdmTimeOfLastFollow = 0.0;
float wdmTimeOfLastSpecial = 0.0;


void wdmReset()
{
	wdmTimeOfLastStorm = 0.0;
	wdmTimeOfLastMerchant = 0.0;
	wdmTimeOfLastWarring = 0.0;
	wdmTimeOfLastFollow = 0.0;
	wdmTimeOfLastSpecial = 0.0;
}

//Storm
void wdmStormGen(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{
	bool encoff = false;
	if(CheckAttribute(pchar,"worldmapencountersoff") == 1)
	{
		if(sti(pchar.worldmapencountersoff)) return;
	}
	int numStorms = wdmGetNumberStorms();
	if(numStorms < 1)
	{
		wdmTimeOfLastStorm = wdmTimeOfLastStorm + dltTime*WDM_STORM_RATE*1000.0*iEncountersRate;
		if(rand(1001) < wdmTimeOfLastStorm)
		{
			wdmCreateStorm();
			wdmTimeOfLastStorm = 0.0;
		}
	}else{
		wdmTimeOfLastStorm = 0.0;
	}
}

//Random ships
void wdmShipEncounter(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{
	int numShips = wdmGetNumberShipEncounters();
	//if( CheckAttribute(pchar,"worldmap.shipcounter") ) {
		//numShips = numShips - sti(pchar.worldmap.shipcounter);
	//}
	if( numShips < 0 )
	{
		trace("Warning! World map ship quantity < 0 : numShips = " + numShips);
		trace("pchar.worldmap.shipcounter = " + pchar.worldmap.shipcounter);
		numShips = 0;
	}
	int shipgen = 8;
	switch (iEncountersCountRate)
	{
		case 1: shipgen=6; break;
		case 2: shipgen=12; break;
		case 3: shipgen=30; break;
	}
	if (!CheckAttribute(pchar, "PGGsAtSea"))
	{
		pchar.PGGsAtSea = 0;
	}
	shipgen += sti(pchar.PGGsAtSea);
	if(numShips < shipgen)
	{
		//Вероятности появления
		wdmTimeOfLastMerchant = wdmTimeOfLastMerchant + dltTime*WDM_MERCHANTS_RATE*1000.0*iEncountersRate;
		wdmTimeOfLastWarring = wdmTimeOfLastWarring + dltTime*WDM_WARRING_RATE*1000.0*iEncountersRate;
		wdmTimeOfLastFollow = wdmTimeOfLastFollow + dltTime*WDM_FOLLOW_RATE*1000.0*iEncountersRate;
		wdmTimeOfLastSpecial = wdmTimeOfLastSpecial + dltTime*WDM_SPECIAL_RATE*1000.0*iEncountersRate;
		//Вероятность от количества созданных
		float nump = 1.0 - numShips*0.15;
		//Выбираем
		if(rand(1001) + 1 < wdmTimeOfLastMerchant)
		{
			wdmTimeOfLastMerchant = 0.0;
			wdmCreateMerchantShip(0.8 + rand(10)*0.03);
		}
		else
		{
			bool encoff = false;
			if(CheckAttribute(pchar,"worldmapencountersoff") == 1)
			{
				encoff = sti(pchar.worldmapencountersoff);
			}
			if(encoff == false)
			{
				if(rand(1001) + 1 < wdmTimeOfLastWarring)
				{
					wdmTimeOfLastWarring = 0.0;
					wdmCreateWarringShips();
				}
				else
				{
					if(rand(1001) + 1 < wdmTimeOfLastFollow)
					{
						wdmTimeOfLastFollow = 0.0;
						if(!IsStopMapFollowEncounters())
						{
							wdmCreateFollowShip(0.8 + rand(10)*0.05);
						}
					}
				}
				if(rand(1001) + 1 < wdmTimeOfLastSpecial)
				{
					wdmTimeOfLastSpecial = 0.0;
					wdmCreateSpecial(0.05 + rand(10)*0.02);
				}
			}
		}
	}
	else
	{
		wdmTimeOfLastMerchant = 0.0;
		wdmTimeOfLastWarring = 0.0;
		wdmTimeOfLastFollow = 0.0;
		wdmTimeOfLastSpecial = 0.0;
	}
}


#event_handler("Map_TraderSucces", "Map_TraderSucces");
#event_handler("Map_WarriorEnd", "Map_WarriorEnd");
// to_do -->
void Map_WarriorEnd()
{
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		return;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	if(sti(pchar.worldmap.shipcounter) < 0)
	{
		sti(pchar.worldmap.shipcounter) = 0;
	}
}
void Map_TraderSucces()
{
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		return;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	if(sti(pchar.worldmap.shipcounter) < 0)
	{
		pchar.worldmap.shipcounter = 0;
	}
	string sChar = GetEventData();

	Map_TraderSucces_quest(sChar); //обработка квестов по поиску кэпов

	//homo 03/08/06 Наводка на купца
	if (findsubstr(sChar, "_QuestMerchant" , 0) != -1)
	{
        Map_ReleaseQuestEncounter(sChar);
        Group_DeleteGroup("Sea_"+sChar);
        CloseQuestHeader("MerchantOnMap");
	}
    // homo 07/10/06 GoldFleet
    if (sChar == "Head_of_Gold_Squadron")
	{
        RouteGoldFleet();
	}

	if (findsubstr(sChar, "SiegeCap_" , 0) != -1)
	{
        SiegeProgress();
	}
	/*if(GetCharacterIndex(sChar) != -1)  // типа пример
	{
		if(CheckAttribute(&characters[GetCharacterIndex(sChar)], "hovernor"))
		{
			if(sti(characters[GetCharacterIndex(sChar)].hovernor) == 1)
			{
				//  to_do MakeNewCapital(sChar);
				return;
			}
		}
	}
	else
	{
		trace("Can't find character with character id " + sChar);
		return;
	}

	if(sChar == "Head of Gold Squadron")
	{
		PrepareContinueGoldConvoy();
		return;
	}
	if(CheckAttribute(&characters[GetCharacterIndex(sChar)], "mapEnc.quest"))
	{
		int iQuest = sti(characters[GetCharacterIndex(sChar)].mapEnc.quest);
		string sQuest = "sink_ship_character_" + sChar + "_wait_before_travel";
		pchar.quest.(sQuest).win_condition.l1 = "timer";
		pchar.quest.(sQuest).win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
		pchar.quest.(sQuest).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
		pchar.quest.(sQuest).win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
		pchar.quest.(sQuest).win_condition.l1.date.hour = rand(23);
		pchar.quest.(sQuest).win_condition = "sink_ship_travel";
		pchar.quest.(sQuest).quest = iQuest;

		return;
	}  */
}

void Map_TraderSucces_quest(string sChar)
{
	ref character = CharacterFromID(sChar);

	//пиратка, квест №7
	if (sChar == "LeonCapitain")
	{
		pchar.questTemp.piratesLine = "Soukins_LeonNotFound";
		QuestSetCurrentNode("Henry Morgan", "PL_Q7_LeonNotFound"); //нода, ничего не узнал
		AddQuestRecord("Pir_Line_7_Soukins", "14");
		Log_TestInfo(GetConvertStrWithReplace("Variable_worldmap_encgen_1", "Logs.txt", "#space#", " "));
		Map_ReleaseQuestEncounter("LeonCapitain");
		group_DeleteGroup("Leon_Group");
	}
	//пиратка, квест №7
	if (sChar == "QuestCap_PL7")
	{
		pchar.questTemp.piratesLine = "Soukins_battlshipNotFound";
		AddQuestRecord("Pir_Line_7_Soukins", "12");
		AddQuestUserData("Pir_Line_7_Soukins", "sSex", GetSexPhrase("","а"));
		Log_TestInfo(GetConvertStrWithReplace("Variable_worldmap_encgen_2", "Logs.txt", "#space#", " "));
		Map_ReleaseQuestEncounter("QuestCap_PL7");
		group_DeleteGroup("Quest_Ship");
	}

	// Warship 08.07.09 Пасхалка с бригантиной Мэри Селест
	if(sChar == "MaryCelesteCapitan")
	{
		Map_ReleaseQuestEncounter("MaryCelesteCapitan");

		// Для палубы, при Map_ReleaseQuestEncounter() рассылалось событие, а ставить ещё раз не нужно
		if(PChar.QuestTemp.MaryCeleste != "OnDeck")
		{
			character.fromCity = character.toCity; // Колония, из бухты которой выйдет
			character.fromShore = character.toShore;
			character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придет
			character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));

			Map_CreateTrader(character.fromShore, character.toShore, "MaryCelesteCapitan", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)));

			Log_TestInfo(GetConvertStrWithReplace("Variable_worldmap_encgen_3", "Logs.txt", "#space#", " ") + character.fromCity + GetConvertStrWithReplace("Variable_worldmap_encgen_4", "Logs.txt", "#space#", " ") + character.toShore);
		}
	}

	// ugeen --> генератор "Повод для спешки"
	if(sChar == "PirateCapt")
	{
		Log_TestInfo(GetConvertStrWithReplace("Variable_worldmap_encgen_7", "Logs.txt", "#space#", " "));
		Map_ReleaseQuestEncounter(sChar);
		AddQuestRecord("ReasonToFast","26");
		CloseQuestHeader("ReasonToFast");
		DeleteAttribute(pchar,"questTemp.ReasonToFast");
	}

	//розыск и отдача кэпу судового журнала
	if (findsubstr(sChar, "PortmansCap_" , 0) != -1 && characters[GetCharacterIndex(sChar)].quest == "InMap")
	{
		SetCapitainFromSeaToCity(sChar);
		Log_TestInfo(GetConvertStrWithReplace("Variable_worldmap_encgen_8", "Logs.txt", "#space#", " ") + sChar + GetConvertStrWithReplace("Variable_worldmap_encgen_9", "Logs.txt", "#space#", " "));
	}
	//поиски кэпа-вора
	if (findsubstr(sChar, "SeekCap_" , 0) != -1 && characters[GetCharacterIndex(sChar)].quest == "InMap")
	{
		SetRobberFromMapToSea(sChar);
		Log_TestInfo(GetConvertStrWithReplace("Variable_worldmap_encgen_10", "Logs.txt", "#space#", " ") + sChar + GetConvertStrWithReplace("Variable_worldmap_encgen_11", "Logs.txt", "#space#", " "));
	}
	//поиски кэпа, квест дают горожане
	if (findsubstr(sChar, "SeekCitizCap_" , 0) != -1)
	{
		int iChar = GetCharacterIndex(sChar);
		if (characters[iChar].quest == "InMap")
		{
			CitizCapFromMapToCity(sChar);
			Log_TestInfo(GetConvertStrWithReplace("Variable_worldmap_encgen_12", "Logs.txt", "#space#", " ") + sChar + GetConvertStrWithReplace("Variable_worldmap_encgen_13", "Logs.txt", "#space#", " "));
		}
		if (characters[iChar].quest == "outMap")
		{
			string sTemp = "SCQ_" + characters[iChar].index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			characters[iChar].lifeDay = 0;
		}
	}
	//поиски бригантины с мушкетом
	if (sChar == "MushketCap" && characters[GetCharacterIndex(sChar)].quest == "InMap")
	{
		SetMushketFromMapToSea();
		Log_TestInfo(GetConvertStrWithReplace("Variable_worldmap_encgen_14", "Logs.txt", "#space#", " "));
	}
	//поиски брига Королева
	if (sChar == "Danielle" && characters[GetCharacterIndex(sChar)].quest == "InMap")
	{
		SetDanielleFromMapToSea();
		Log_TestInfo("Энканутер кэпа брига Queen дошёл до места назначения.");
	}
	//поиски Чёрной Бороды
	if (sChar == "BlackBeardNPC" && characters[GetCharacterIndex(sChar)].quest == "InMap")
	{
		SetBlackBeardFromMapToSea();
		Log_TestInfo(GetConvertStrWithReplace("Variable_worldmap_encgen_15", "Logs.txt", "#space#", " "));
	}
}