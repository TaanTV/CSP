/*!
 * \brief Механика обмена предметов для КШП.
 * Открывает интерфейс обмена предметами между собой согласно прописанным
 * предметам и коэффициентам. Настраиваемый запрет на одно/двухсторонний обмен.
 * Алгоритм занесения нового предмета на обмен:
 * - инкрементируем ITEM_CNT
 * - инкрементируем MATRIX_SIZE на ITEM_CNT^2
 * - добавляем строку itm.id в массив items_names
 * - добавляем коэффициенты в матрицу exchange_table. При этом обмен предмета на самого себя должен иметь коэффициент 0 или 1
 * - если нужно запретить менять один предмет на другой - настраиваем table_protect (запрет обмена предмету игрока),
 * т.е. можно запретить менять игроку алмаз на саблю, но саблю на алмаз обменять можно.
 * \author Dmitry Susokolov
 * \date 04.07.2024
 * \warning НЕ ПРИМЕНЯЙТЕ К ФАЙЛУ ЛИНТЕР, ЧТО БЫ НЕ СБИТЬ ФОРМАТИРОВАНИЕ МАТРИЦ
 */

#define ITEM_CNT 8	// кол-во предметов на обмен
#define MATRIX_SIZE 64	// размер матрицы коэффициентов обмена, равен ITEM_CNT * ITEM_CNT

int lngFileID;	// хранит файл с описанием предметов
int SelectedLineHero = 0;	// номер строки минус один предмета игрока для обмена. Начинается с нуля, а сама строка начинается с единицы (нулевая техническая)
int SelectedLineExch = 0;	// номер строки минус один предмета на обмен. Начинается с нуля, а сама строка начинается с единицы (нулевая техническая)

/*								сапфир, 	алмаз, 		рубин, 		изумруд	    золотой серебряный слитки большая маленькая жемчужины   */
string items_names[ITEM_CNT] = {"jewelry1", "jewelry2", "jewelry3", "jewelry4", "jewelry5", "jewelry17", "jewelry11", "jewelry12"};	// itm.id вещей на обмен
int items_cnt[ITEM_CNT];	// хранит кол-во предметов игрока. Порядок предметов прибивается гвоздями в InitInterface_gm и не должен меняться по ходу обмена т.к. зависит от items_names
int items_init_cnt[ITEM_CNT];	// хранит начальное кол-во предметов
/* Значение, которое будет забираться у игрока и даваться игроку, читается слева сверху, т.е. в первой строке во втором столбце алмаз на сапфир. Забирается транспонирование матрицы */ 
						         //С  А  Р  И  Зс Сс Бж Мж  
int exchange_table[MATRIX_SIZE] = {1, 1, 1, 1, 1, 2, 3, 6,  // С
						    	   3, 1, 3, 3, 3, 6, 7, 14, // А
								   2, 1, 1, 2, 2, 4, 5, 10, // Р
								   1, 1, 1, 1, 2, 4, 5, 10, // И
								   1, 1, 1, 1, 1, 2, 3, 6,  // Зс
								   1, 1, 1, 1, 1, 1, 2, 4,  // Сс
								   1, 1, 1, 1, 1, 1, 1, 2,  // Бж
								   1, 1, 1, 1, 1, 1, 1, 1}; // Мж
/* Таблица запрета обмена предметов, 1 - можно менять, 0 - нельзя */
int table_protect[MATRIX_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 1, 1, 1};
string all_exch_arr[ITEM_CNT];	// Массив строк с результатами обмена

/* Инит предметов игрока */
void InitHeroItems()
{
	for(int i = 0; i < ITEM_CNT; i++)
	{
		items_cnt[i] = GetCharacterItemWithCabin(pchar, items_names[i], true); // отображаем предметы из сундуков каюты
		items_init_cnt[i] = items_cnt[i];
	}
}

void InitInterface_gm(string iniName)
{
	lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	
	InitHeroItems();

	GameInterface.title = "ItemsExchangeTitle";

	SetTimeScale(0.0);
	LAi_SetActorTypeNoGroup(pchar);
	locCameraSleep(true);

	EngineLayersOffOn(true);
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("TableSelectChange", "SelectTable", 0);

	InterfaceStates.showGameMenuOnExit = true;

	SetNodeUsing("PCHAR_ITEMS_LIST",true);
	SetNodeUsing("EXCHANGE_LIST",true);

	FillItemsTab();
}

void FillItemsTab()
{
	/* Выравнивание строк */
	GameInterface.PCHAR_ITEMS_LIST.hr.td2.scale = 0.9;
	GameInterface.PCHAR_ITEMS_LIST.hr.td3.scale = 0.9;
	GameInterface.EXCHANGE_LIST.hr.td2.scale = 0.9;
	GameInterface.EXCHANGE_LIST.hr.td3.scale = 0.9;

	/* Заполняем таблицу игрока предметами, даже если у него их нет, т.к. в ходе обмена они могут появится */
	for(int i=0; i<ITEM_CNT; i++)
	{
		ref hero_items = ItemsFromID(items_names[i]);
		string row = "tr" + (i+1);

		GameInterface.PCHAR_ITEMS_LIST.(row).td1.icon.group = hero_items.picTexture;
		GameInterface.PCHAR_ITEMS_LIST.(row).td1.icon.image = "itm" + hero_items.picIndex;
		GameInterface.PCHAR_ITEMS_LIST.(row).td1.icon.offset = "-2, 0";
		GameInterface.PCHAR_ITEMS_LIST.(row).td1.icon.width = 48;
		GameInterface.PCHAR_ITEMS_LIST.(row).td1.icon.height = 48;
		GameInterface.PCHAR_ITEMS_LIST.(row).td2.str = LanguageConvertString(lngFileID, hero_items.name);
		GameInterface.PCHAR_ITEMS_LIST.(row).td2.scale = 0.9;
		GameInterface.PCHAR_ITEMS_LIST.(row).td3.str = items_cnt[i];
		GameInterface.PCHAR_ITEMS_LIST.(row).td3.scale = 0.9;

		GameInterface.EXCHANGE_LIST.(row).td1.icon.group = hero_items.picTexture;
		GameInterface.EXCHANGE_LIST.(row).td1.icon.image = "itm" + hero_items.picIndex;
		GameInterface.EXCHANGE_LIST.(row).td1.icon.offset = "-2, 0";
		GameInterface.EXCHANGE_LIST.(row).td1.icon.width = 48;
		GameInterface.EXCHANGE_LIST.(row).td1.icon.height = 48;
		GameInterface.EXCHANGE_LIST.(row).td2.str = LanguageConvertString(lngFileID, hero_items.name);
		GameInterface.EXCHANGE_LIST.(row).td2.scale = 0.9;
		GameInterface.EXCHANGE_LIST.(row).td3.scale = 0.9;
	}

	Table_UpdateWindow("PCHAR_ITEMS_LIST");
	Table_UpdateWindow("EXCHANGE_LIST");
}

/* heroIndex - строка предмета игрока, exchIndex - строка предмета на обмен, value - кол-во предмета.
Положительное - вычитается предмет игрока, прибавляется выбранный предмет на обмен.
Отрицательное - прибавляется предмет игроку, вычитается выбранный на обменю.
Т.е. передав в value единицу функция посмотрит коэффициент обмена в таблице, заберет у игрока value*K предмета heroIndex и даст предмет exchIndex в кол-ве value*K */
void ExchangeItems(int heroIndex, int exchIndex, int value)
{
	int hero_take = (exchIndex * ITEM_CNT) + heroIndex;	// кол-во, которое забирем у игрока
	int hero_get = (heroIndex * ITEM_CNT) + exchIndex;	// кол-во, которое дадим игроку (транспонированная матрица)
	/* Проверяем запрет на обмен */
	if(table_protect[hero_take] == 0)
	{
		return;
	}
	int hero_k = value * exchange_table[hero_take];
	int hero_e = value * exchange_table[hero_get];
	/* Предварительно проверяем, что после обмена не появится отрицательного числа в кол-ве предмета */
	if( ((items_cnt[heroIndex] - hero_k) < 0) || ((items_cnt[exchIndex] + hero_e) < 0) )
	{
		return;
	}
	
	items_cnt[heroIndex] = items_cnt[heroIndex] - hero_k;
	items_cnt[exchIndex] = items_cnt[exchIndex] + hero_e;
	
	/* Если что-то не учли - делаем ноль */
	if(items_cnt[exchIndex] < 0)
	{
		items_cnt[exchIndex] = 0;
	}
	
}

/* Сохраняет результаты обмена. Кладет в сундук результаты обмена, если предмета не было на игроке изначально */
void SaveItemsToPChar()
{
	for(int i = 0; i < ITEM_CNT; i++)
	{
		/* Показываем игроку какие предметы куда положили */
		int cnt = items_cnt[i] - items_init_cnt[i];
		string tmp = "";
		if(cnt == 0)
		{
			continue;
		}
		// Кладем в инвентарь
		if(cnt > 0)
		{
			tmp = XI_ConvertString("ToInv");
			TakeNItems(pchar, items_names[i], cnt);
		}
		// Забираем из сундука или инвентаря
		else
		{
			tmp = items_names[i];
			if((CheckAttribute(pchar, "Items."+items_names[i]) == 0))
			{
				tmp = XI_ConvertString("FromChest");
			}
			else if (sti(pchar.Items.(tmp)) + cnt < 0)	// + т.к. cnt отрицательный
			{
				tmp = XI_ConvertString("FromChestAndInv");
			}
			else
			{
				tmp = XI_ConvertString("FromInv");
			}
			TakeNItemsWithCabin(pchar, items_names[i], cnt, false);
		}
		Log_Info(all_exch_arr[i] + tmp);
	}
	InitHeroItems();
}

/* Анализ выбранных кнопок */
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	if(nodName == "QTY_REMOVE_BUTTON")
	{
		/* В обратную сторону не меняем */
		if(items_init_cnt[SelectedLineHero] - items_cnt[SelectedLineHero] > 0)
		{
			ExchangeItems(SelectedLineHero, SelectedLineExch, -1);
		}
	}
	else if(nodName == "QTY_ADD_BUTTON")
	{
		ExchangeItems(SelectedLineHero, SelectedLineExch, 1);
	}
	else if(nodName == "EXCHANGE_LIST" || nodName == "PCHAR_ITEMS_LIST")
	{
		if(comName == "rightstep")
		{
			ExchangeItems(SelectedLineHero, SelectedLineExch, 1);
		}
		else if (comName == "leftstep")
		{
			/* В обратную сторону не меняем */
			if(items_init_cnt[SelectedLineHero] - items_cnt[SelectedLineHero] > 0)
			{
				ExchangeItems(SelectedLineHero, SelectedLineExch, -1);
			}
		}
		else if(comName == "speedleft")
		{
			/* В обратную сторону не меняем */
			if(items_init_cnt[SelectedLineHero] - items_cnt[SelectedLineHero] > 10)
			{
				ExchangeItems(SelectedLineHero, SelectedLineExch, -10);
			}
		}
		else if(comName == "speedright")
		{
			ExchangeItems(SelectedLineHero, SelectedLineExch, 10);
		}
	}
	else if(nodName == "CONFIRM_BUTTON")
	{
		if (comName=="activate" || comName=="click")
		{
			SaveItemsToPChar();
		}
	}
	
	/* Обновляем кол-во всех вещей после обмена */
	string row = "tr" + (SelectedLineHero + 1);
	GameInterface.PCHAR_ITEMS_LIST.(row).td3.str = items_cnt[SelectedLineHero];
	row = "tr" + (SelectedLineExch + 1);
	GameInterface.PCHAR_ITEMS_LIST.(row).td3.str = items_cnt[SelectedLineExch];
	Table_UpdateWindow("PCHAR_ITEMS_LIST");

	/* Пишем результаты обмена */
	string general_exch_info_str;
	for(int i = 0; i < ITEM_CNT; i++)
	{
		if(items_cnt[i] - items_init_cnt[i] == 0)
		{
			continue;
		}

		ref hero_items = ItemsFromID(items_names[i]);
		if(items_cnt[i] - items_init_cnt[i] < 0)
		{
			all_exch_arr[i] = "Отдано " + (items_cnt[i] - items_init_cnt[i])*-1 + " " + LanguageConvertString(lngFileID, hero_items.name);
		}
		else
		{
			all_exch_arr[i] = "Получено " + (items_cnt[i] - items_init_cnt[i]) + " " + LanguageConvertString(lngFileID, hero_items.name);
		}
		general_exch_info_str = general_exch_info_str + all_exch_arr[i] + "\n";
	}
	SetFormatedText("SUB_INFO_TEXT", general_exch_info_str);
}

/* Клик по строке */
void SelectTable()
{
	string CurTable = GetEventData();
	int iSelected = GetEventData();
    string CurRow   =  "tr" + (iSelected);
	
	if(CurTable == "PCHAR_ITEMS_LIST")
	{
		SelectedLineHero = iSelected - 1;
	}
	if(CurTable == "EXCHANGE_LIST")
	{
		SelectedLineExch = iSelected - 1;
	}

	ref hero_item = ItemsFromID(items_names[SelectedLineHero]);
	ref exh_item = ItemsFromID(items_names[SelectedLineExch]);
	int hero_take = (SelectedLineExch * ITEM_CNT) + SelectedLineHero;	// кол-во, которое забирем у игрока
	int hero_get = (SelectedLineHero * ITEM_CNT) + SelectedLineExch;	// кол-во, которое дадим игроку (транспонированная матрица)
	
	/* Проверяем запрет на обмен */
	if(table_protect[hero_take] != 0)
	{
		SetFormatedText("INFO_TEXT", "Обмен " + exchange_table[hero_take] + " к " + exchange_table[hero_get]);
	}
	else
	{
		SetFormatedText("INFO_TEXT", "Нельзя обменять " + LanguageConvertString(lngFileID, hero_item.name) + " на " + LanguageConvertString(lngFileID, exh_item.name));
	}
    SetVAligmentFormatedText("INFO_TEXT");
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
}

void IDoExit(int exitCode, bool bClear)
{
	LanguageCloseFile(lngFileID);
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("TableSelectChange", "SelectTable");

	LAi_SetPlayerType(pchar);

	SetTimeScale(1.0);
	TimeScaleCounter = 0;
	DelPerkFromActiveList("TimeSpeed");
	locCameraSleep(false);
	DeleteAttribute(pchar, "pause");

	interfaceResultCommand = exitCode;

	if( interfaceResultCommand == RC_INTERFACE_DO_RESUME_GAME ) {
		DeleteEntitiesByType("scrshoter");
	}

	EndCancelInterface(bClear);
}
