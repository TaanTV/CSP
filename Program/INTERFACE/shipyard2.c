//Смена каюты -->
string sCabins[10] = {"Cabin_Small","Cabin_Small2","New_Cabin1","Cabin_Medium1","Cabin_Medium","Cabin_Medium2","New_Cabin2","Cabin_Quest","Cabin","Cabin_Huge"};//берём из SetCabinTypeEx
int iCabinsNum = 10;//число видов кают
int iCurCabin = 0;
//Смена каюты <--

ref refNPCShipyard;
ref refStore;

int z = 0;
int iYarderSkill = 100;
int iTunPoints = 8;
int iTimeMake, iShipPoints, iQBorders, iPriceOrder;
int iQMAX, iQMIN, iFreeSP, iFreeTP;
bool Tune_Sheme[10] = {0,0,0,0,0,0,0,0,0,0};//элементы 0(заголовок таблицы) и 2(паруса) пропускаем. просто для удобства
float Ship_Sheme[11] = {10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0};//тип флоат, чтоб не преобразовывать лишний раз при умножении на коэффициент, по факту - целые
int CannonTypes[20] = {1000,9,0,10,1,11,2,12,3,13,4,14,5,15,6,16,7,17,8,18};// #define CANNON_TYPE_CULVERINE_LBS8	0, #define CANNON_TYPE_CANNON_LBS8		7

string CurTable, CurRow, sNation;
int iSelected; // курсор в таблице
int FIS_FilterState = 7;
bool FState_Material = 0;
string sMessageMode, index;

int sundukSum;//на все апгрейды одинаковое колво сундуков	//chest
int Tun_Mater1[10];//кол-во товар
int Tun_Mater2[10];//кол-во предмет
int Tun_Mater3[10];//кол-во деньги	//gold
string sAdd[10];

void InitInterface_R(string iniName, ref _shipyarder)
{
	GameInterface.title = "titleShipyard";
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	refNPCShipyard  = _shipyarder;

	InitSAddMassive();

	if (!CheckCharacterItem(pchar, "Ship_Print_1")) DeleteAttribute(refNPCShipyard,"print1");
	if (!CheckCharacterItem(pchar, "Ship_Print_2")) DeleteAttribute(refNPCShipyard,"print2");
	if (!CheckCharacterItem(pchar, "Ship_Print_3")) DeleteAttribute(refNPCShipyard,"print3");
	if (!CheckCharacterItem(pchar, "Ship_Print_4")) DeleteAttribute(refNPCShipyard,"print4");
	if (!CheckCharacterItem(pchar, "Ship_Print_5")) DeleteAttribute(refNPCShipyard,"print5");
	if (!CheckCharacterItem(pchar, "Ship_Print_6")) DeleteAttribute(refNPCShipyard,"print6");

	sNation = GetNationNameByType(sti(refNPCShipyard.nation));

	if (refNPCShipyard.id != "Pirates_shipyarder") {iYarderSkill = sti(refNPCShipyard.reputation)/2+50; iTunPoints = (iYarderSkill-41)/18;}
	//берём за навык кораблестроения репутацию верфиста и приводим к отрезку (56:100)

	iShipPoints = 999;//целые переменные делятся с округлением вниз
	iQBorders = (iShipPoints+10)/3;
	if (iQBorders > 10) iQBorders = 10;
	iQMAX = iQBorders;
	iQMIN = -iQBorders;
	iFreeSP = iShipPoints;
	iFreeTP = iTunPoints;

	int iTest = FindColony(refNPCShipyard.City); // город магазина
	ref rColony;
	if (iTest != -1) {rColony = GetColonyByIndex(iTest);}
	refStore = &stores[sti(rColony.StoreNum)];

	if (iTunPoints < 1) SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", -1, 1, 0);//если тюнинга нет из-за низкого навыка, отключаем клики по кнопкам

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("CheckButtonChange", "ProcessFilter", 0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("ExitChangeCabinMenu", "ExitChangeCabinMenu",0);

	EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",156,40,366,275); // tak from SHIP_BIG_PICTURE
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 161,246,361,1, 4);
	EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",20,46,134,161);
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,187,147,1, 4);
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,166,147,1, 4);

	SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");

	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\128\face_" + refNPCShipyard.FaceId + ".tga");

	SetFormatedText("HERO_TEXT", GetConvertStrWithReplace("Variable_shipyard2_30","Interface.txt", "#enter#", "\n"));

	SetFormatedText("HERO_NAME", GetFullName(refNPCShipyard));
	SetFormatedText("HERO_RANK",refNPCShipyard.Rank);

	SetFormatedText("HERO_SKILL","" + iYarderSkill);
	SetFormatedText("HERO_QBORDERS", iQBorders*10 + "%");
	SetFormatedText("HERO_SHIPPOINTS",iFreeSP + "/" + iShipPoints);
	SetFormatedText("HERO_TUNPOINTS",iFreeTP + "/" + iTunPoints);

	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));

	FillShipyardTable();
	FillShipParam();
	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
	GameInterface.TABLE_SHIPYARD.select = 1;
	Table_UpdateWindow("TABLE_SHIPYARD");
	SetButtionsAccess();//доступность кнопки GetConvertStrWithReplace("Variable_shipyard2_1", "Interface.txt", "#space#", " ")
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("CheckButtonChange", "ProcessFilter");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("ExitChangeCabinMenu", "ExitChangeCabinMenu");

	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
		DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "BUTTON_CABIN":
			if (comName=="click" || comName=="activate")
			{
			    ShowChangeCABINMenu();
			}
		break;
		case "CHANGE_CABIN_LEFT":
			if(comName=="click")
			{
				SelectChangeCABIN(true);
			}
		break;
		case "CHANGE_CABIN_RIGHT":
			if(comName=="click")
			{
				SelectChangeCABIN(false);
			}
		break;
		case "CHANGE_CABIN_OK":
			if(comName=="click")
			{
				SetNewCABINToCharacterShip();
			}
		break;

		case "B_SKILLUP":
			if (comName=="click")
			{
				IncShipQ(1);
			}
			if (comName=="rclick")
			{
				IncShipQ(8);
			}
		break;

		case "B_SKILLDOWN":
			if (comName=="click")
			{
				DecShipQ(1);
			}
			if (comName=="rclick")
			{
				DecShipQ(8);
			}
		break;

		case "BUTTON_BUY":
			if (comName=="click" || comName=="activate")
			{
				ShowMessageInfo();
			}
		break;

		case "MSG_OK":
			if (comName=="click" || comName=="activate")
			{
				DoBuyShip();
			}
		break;
	}
}

void FillOrderShip(int _iShipBaseType)
{
	int iShip = CreateBaseShip(_iShipBaseType);
	refNPCShipyard.Ship.Type = iShip;
	aref refShip;
	makearef(refShip, refNPCShipyard.Ship);

	if (!CheckAttribute(refShip,"soiling")) refShip.soiling = 0;//чтоб не срало в лог об отсутствии

	if(!CheckAttribute(refNPCShipyard, "ship.upgrades"))
	{
		refNPCShipyard.ship.upgrades.hull = 1;
		refNPCShipyard.ship.upgrades.sails = 1;
		refNPCShipyard.ship.upgrades.cannons = 1;
	}

	refShip.Pos.x = 0;
	refShip.Pos.y = 0;
	refShip.Pos.z = 0;
	refShip.Ang = "";
	refShip.Cannons.Charge.Type = GOOD_BALLS;

	if (!CheckAttribute(refShip,"Cannons.Type")) refShip.Cannons.Type = CANNON_TYPE_NONECANNON;
	if (!CheckAttribute(refShip,"Crew.Morale"))	refShip.Crew.Morale = 20 + rand(79);
	if (!CheckAttribute(refShip,"Crew.Quantity")) refShip.Crew.Quantity = 0;

	if(!CheckAttribute(refNPCShipyard, "ship.crew.Exp"))
	{
		refNPCShipyard.Ship.Crew.Exp.Sailors   = 1 + rand(80);
		refNPCShipyard.Ship.Crew.Exp.Cannoners = 1 + rand(80);
		refNPCShipyard.Ship.Crew.Exp.Soldiers  = 1 + rand(80);
	}
	refNPCShipyard.ship.crew.disease = 0;
	ResetShipCannonsDamages(refNPCShipyard);
	DeleteAttribute(refNPCShipyard, "Ship.Cargo");
	NullCharacterGoods(refNPCShipyard);
	SetRandomNameToShip(refNPCShipyard);

	if (isCabinforClass(sti(refShip.Class))) SetNewCABINToCharacterShip();//ставим выбранную у прошлого корабля каюту, если она подходит классу
		else SetCabinTypeEx(RealShips[iShip], sti(RealShips[iShip].Class));//рандом каюты 
}

void FillShipParam()
{
	int iShip = sti(refNPCShipyard.ship.type);
	if (iShip != SHIP_NOTUSED)
	{
		ref rRealShip = &RealShips[iShip];
		ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
		DeleteAttribute(rRealShip, "Tuning");//просто затираем записи об апгрейдах
		DeleteAttribute(rRealShip, "Untuned");
		//снимаем чекбокс тюнинга на 42фт	//получается рекурсия какая-то - после снятия чекбокса заного вызывается эта же функция
		if (Tune_Sheme[9] && sti(rBaseShip.MaxCaliber) == 42) SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", 2, 9, 0);

		rRealShip.HP = stf(rBaseShip.HP) * (1 + Ship_Sheme[1]/10.0*SHIP_STAT_RANGE_DRAFT);
		rRealShip.MastMultiplier = stf(rBaseShip.MastMultiplier) - (Ship_Sheme[3] * 0.03);
		rRealShip.SpeedRate = stf(rBaseShip.SpeedRate) * (1 + Ship_Sheme[4]/10.0*SHIP_STAT_RANGE_DRAFT);
		rRealShip.TurnRate = stf(rBaseShip.TurnRate) * (1 + Ship_Sheme[5]/10.0*SHIP_STAT_RANGE_DRAFT);
		rRealShip.WindAgainstSpeed = stf(rBaseShip.WindAgainstSpeed) * (1 + Ship_Sheme[6]/10.0*SHIP_STAT_RANGE_DRAFT);
		rRealShip.Capacity = makeint(stf(rBaseShip.Capacity) * (1 + Ship_Sheme[7]/10.0*SHIP_STAT_RANGE_DRAFT));
		rRealShip.OptCrew = stf(rBaseShip.OptCrew) * (1 + Ship_Sheme[8]/10.0*SHIP_STAT_RANGE_DRAFT);
		rRealShip.MaxCrew = stf(rBaseShip.MaxCrew) * (1 + Ship_Sheme[8]/10.0*SHIP_STAT_RANGE_DRAFT);
		rRealShip.MinCrew = stf(rBaseShip.MinCrew) * (1 + Ship_Sheme[8]/10.0*SHIP_STAT_RANGE_DRAFT);
		rRealShip.MaxCaliber = rBaseShip.MaxCaliber;

		refNPCShipyard.Ship.Cannons.Type = CANNON_TYPE_NONECANNON;
		int iAddedPrice = 1;
		if (sti(rRealShip.class) <= 4) {
			iAddedPrice++;
		}
		rRealShip.Price	= GetShipPriceByTTH(iShip, refNPCShipyard)*iAddedPrice;//цена без пушек
		CalcTuningPrice();//стоимость апгрейда до применения апгрейдов считаем

		SetBermudeTuningStates2Ship(refNPCShipyard, Tune_Sheme[9], Tune_Sheme[7], Tune_Sheme[4], Tune_Sheme[8], Tune_Sheme[5], Tune_Sheme[1], Tune_Sheme[3], Tune_Sheme[6]);
		//void SetBermudeTuningStates2Ship(ref chr, bool MaxCaliber, bool Capacity, bool SpeedRate, bool MaxCrew, bool TurnRate, bool HP, bool MastMulti, bool WAS)

		int iQMAXTemp = 9;
		int curMaxCaliber = sti(rRealShip.MaxCaliber);
		switch (curMaxCaliber)
		{
		case 8: iQMAXTemp = -8; break;
		case 10: iQMAXTemp = -6; break;
		case 12: iQMAXTemp = -4; break;
		case 16: iQMAXTemp = -2; break;
		case 20: iQMAXTemp = 0; break;
		case 24: iQMAXTemp = 2; break;
		case 28: iQMAXTemp = 4; break;
		case 32: iQMAXTemp = 6; break;
		case 36: iQMAXTemp = 8; break;
		}
		if (Ship_Sheme[10] > iQMAXTemp) Ship_Sheme[10] = iQMAXTemp;//сбрасываем установленный тип орудий до максимально возможного для корабля (после смены корабля или снятия тюнинга калибра)
		refNPCShipyard.Ship.Cannons.Type = CannonTypes[makeint(Ship_Sheme[10])+10];

		refNPCShipyard.ship.hp = GetCharacterShipHP(refNPCShipyard);//прочность корпуса на максимум
		refNPCShipyard.ship.sp = 100;

		DeleteAttribute(refNPCShipyard,"ship.blots");//и пробоины убираем //а они могут тут быть???
		DeleteAttribute(refNPCShipyard,"ship.sails");
		RepairMasts(refNPCShipyard);

		iTimeMake = 5 + sti(rRealShip.Price)/40000 + (iTunPoints - iFreeTP)*0.27;
		SetFormatedText("Time_TEXT", GetConvertStrWithReplace("Variable_shipyard2_2", "Interface.txt", "#space#", " ") + iTimeMake + GetConvertStrWithReplace("Variable_shipyard2_3", "Interface.txt", "#space#", " "));

		FillPrice();

		string sShip = rRealShip.BaseName;
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\ships\" + sShip + ".dds");
		GameInterface.edit_box.str = refNPCShipyard.ship.name;
		SetFormatedText("SHIP_RANK", rRealShip.Class);
		SetShipOTHERTable("TABLE_OTHER", refNPCShipyard);
		SetShipQualityTable(refNPCShipyard, "BAR_HP", "BAR_Mast", "BAR_Speed", "BAR_TurnRate", "BAR_WAS", "BAR_Capacity", "BAR_Crew");
		SetFormatedText("FRAME_INFO_CAPTION", XI_ConvertString(sShip));
		SetFormatedText("INFO_TEXT", GetConvertStr(sShip, "ShipsDescribe.txt"));
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\blank_ship2.dds");
		GameInterface.edit_box.str = XI_Convertstring("NoneBoat");
		SetFormatedText("FRAME_INFO_CAPTION","");
		SetFormatedText("INFO_TEXT","");
	}
	Table_UpdateWindow("TABLE_OTHER");

	HideSkillChanger();
	SetSkillArrows();
	SetButtionsAccess();
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;
	int xx = 64;
	int yy = 64;

	sPicture = "";
	string sAttributeName;
	int nChooseNum = -1;
	int iShip;
	ref refBaseShip;

	bool  bShowHint = true;

	ref rChr = refNPCShipyard;

	switch (sCurrentNode)
	{
		case "SHIP_BIG_PICTURE":
			iShip = sti(rChr.ship.type);
			refBaseShip = GetRealShip(iShip);
			sHeader = XI_ConvertString(refBaseShip.BaseName);
			sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
			//--> показ каюты по ПКМ на портрете корабля
			int nLoc = FindLocation(refBaseShip.CabinType);
			if (nLoc >= 0 && CheckAttribute(&Locations[nLoc],"image")) 
			{
				sPicture = Locations[nLoc].image;
				xx = 512;//размер картинки
				yy = 288;
			}
			//<-- показ каюты
		break;

		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
			sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(rChr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
			{
				ref Cannon = GetCannonByType(sti(rChr.Ship.Cannons.Type));
				sText2 = GetConvertStrWithReplace("Variable_shipyard2_4", "Interface.txt", "#space#", " ") + XI_ConvertString(GetCannonType(sti(rChr.Ship.Cannons.Type)));
				sText2 = sText2 + NewStr() + GetConvertStrWithReplace("Variable_shipyard2_5", "Interface.txt", "#space#", " ") + XI_ConvertString("caliber" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type)));
				sText2 = sText2 + NewStr() + GetConvertStrWithReplace("Variable_shipyard2_6", "Interface.txt", "#space#", " ")  + sti(Cannon.FireRange);
				sText2 = sText2 + NewStr() + GetConvertStr("Variable_dmg_x", "Interface.txt")  + FloatToString(stf(Cannon.DamageMultiply), 1);
				sText2 = sText2 + NewStr() + GetConvertStrWithReplace("Variable_shipyard2_7", "Interface.txt", "#space#", " ")  + sti(GetCannonReloadTime(Cannon)) + GetConvertStrWithReplace("Variable_shipyard2_8", "Interface.txt", "#space#", " ");
				sText2 = sText2 + NewStr() + GetConvertStrWithReplace("Variable_shipyard2_9", "Interface.txt", "#space#", " ")  + sti(Cannon.Weight) + GetConvertStrWithReplace("Variable_shipyard2_10", "Interface.txt", "#space#", " ");

				sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(rChr.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type));

				sText3 = GetConvertStr("Variable_check_cannons", "Interface.txt");
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText2 = GetConvertStr("Variable_overload_crew", "Interface.txt");
				sText2 = sText2 + NewStr() + GetConvertStrWithReplace("Variable_shipyard2_11", "Interface.txt", "#space#", " ") + GetMaxCrewQuantity(rChr);
			}
			// процент ремонта
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(rChr), 1)  + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(rChr), 1) + " %";
			}
			// трюм
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = GetConvertStrWithReplace("Variable_shipyard2_12", "Interface.txt", "#space#", " ") + FloatToString((stf(GetCargoLoad(rChr))  /  stf(GetCargoMaxSpace(rChr))) * 100.0, 1)+ " %";
			}
		break;
		case "TABLE_SHIPYARD" :
			sHeader = XI_Convertstring("Shipyard");
			sText1  = GetConvertStr("Shipyard_hint", "ShipsDescribe.txt");
		break;
	}
	if (bShowHint)
	{
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, xx, yy);
	}
}

void HideInfoWindow()
{
	CloseTooltip();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
	CurTable = sControl;
	CurRow   =  "tr" + (iSelected);
	NullSelectTable("TABLE_OTHER");

	if (CurTable == "TABLE_SHIPYARD")
	{

		int iCurShip = RealShips[sti(refNPCShipyard.ship.type)].basetype;
		int iNewShip = sti(GameInterface.(CurTable).(CurRow).index);
		if (iNewShip == iCurShip) return;

		DeleteAttribute(&RealShips[sti(refNPCShipyard.Ship.Type)], "name");//при смене типа корабля помечаем предыдущий на удаление из массива реальных
		FillOrderShip(iNewShip);
	}
	FillShipParam();
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
		GameInterface.(sControl).select = 0;
		Table_UpdateWindow(sControl);
	}
}

void ExitMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", false);
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}

void FillShipyardTable()
{
	Table_Clear("TABLE_SHIPYARD", false, true, false);
	string attrName;

	GameInterface.TABLE_SHIPYARD.hr.td1.str = GetConvertStr("Variable_shipyard_25", "Interface.txt");
	GameInterface.TABLE_SHIPYARD.hr.td1.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td2.str = GetConvertStr("Variable_shipyard_27", "Interface.txt");
	GameInterface.TABLE_SHIPYARD.hr.td2.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td3.str = GetConvertStr("Variable_shipyard1_15", "Interface.txt");
	GameInterface.TABLE_SHIPYARD.hr.td3.scale = 0.8;
	GameInterface.TABLE_SHIPYARD.hr.td4.str = GetConvertStr("Variable_shipyard_30", "Interface.txt");
	GameInterface.TABLE_SHIPYARD.hr.td4.scale = 0.8;
	GameInterface.TABLE_SHIPYARD.hr.td5.str = GetConvertStr("Variable_shipyard1_17", "Interface.txt");
	GameInterface.TABLE_SHIPYARD.hr.td5.scale = 0.8;
	GameInterface.TABLE_SHIPYARD.hr.td6.str = GetConvertStr("Variable_shipyard1_18", "Interface.txt");
	GameInterface.TABLE_SHIPYARD.hr.td6.scale = 0.8;
	GameInterface.TABLE_SHIPYARD.hr.td7.str = GetConvertStr("Variable_ColonyGuardiang_18", "Interface.txt");
	GameInterface.TABLE_SHIPYARD.hr.td7.scale = 0.8;
	GameInterface.TABLE_SHIPYARD.hr.td8.str = GetConvertStr("Variable_badwind_short", "Interface.txt");
	GameInterface.TABLE_SHIPYARD.hr.td8.scale = 0.8;
	GameInterface.TABLE_SHIPYARD.select = 0;
	GameInterface.TABLE_SHIPYARD.top = 0;
//--> mod tablesort
	GameInterface.TABLE_SHIPYARD.hr.td1.sorttype = "";
	GameInterface.TABLE_SHIPYARD.hr.td2.sorttype = "string";
	GameInterface.TABLE_SHIPYARD.hr.td3.sorttype = "string";//нарушение сортировки 1 - 10 - 2, нужно проверять длину строки и дописывать в начале 0 коротким
	GameInterface.TABLE_SHIPYARD.hr.td4.sorttype = "";
	GameInterface.TABLE_SHIPYARD.hr.td5.sorttype = "";
	GameInterface.TABLE_SHIPYARD.hr.td6.sorttype = "";
	GameInterface.TABLE_SHIPYARD.hr.td7.sorttype = "";
	GameInterface.TABLE_SHIPYARD.hr.td8.sorttype = "";
//<-- mod tablesort

	int	iStart = 0;
	int iEnd = -1;
	int k = 0;
	z = k;

	if (CheckAttribute(refNPCShipyard,"print6")) {iStart = 1; iEnd = 5; z = FillShip2(iStart,iEnd,z);}
	if (CheckAttribute(refNPCShipyard,"print5")) {iStart = 6; iEnd = 10; z = FillShip2(iStart,iEnd,z);}
	if (CheckAttribute(refNPCShipyard,"print4")) {iStart = 11; iEnd = 15; z = FillShip2(iStart,iEnd,z);}
	if (CheckAttribute(refNPCShipyard,"print3")) {iStart = 16 iEnd = 20; z = FillShip2(iStart,iEnd,z);}
	if (CheckAttribute(refNPCShipyard,"print2")) {iStart = 21; iEnd = 25; z = FillShip2(iStart,iEnd,z);}
	if (CheckAttribute(refNPCShipyard,"print1")) {iStart = 26; iEnd = 30; z = FillShip2(iStart,iEnd,z);}

	Table_UpdateWindow("TABLE_SHIPYARD");
}

int FillShip2(int iStart, int iEnd, int k)
{
	string sShip, sTemp;
	string row;
	for (int i = iStart; i < iEnd+1; i++)
	{
		if (k == 0) FillOrderShip(shipspool[i]);
		row = "tr" + (k+1);

		sShip = shipstypes[shipspool[i]].Name;
		GameInterface.TABLE_SHIPYARD.(row).index = i;

		GameInterface.TABLE_SHIPYARD.(row).td1.icon.texture = "interfaces\ships\" + sShip + ".dds";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.uv = "0,0,1,1";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.width = 46;
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.height = 46;
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.offset = "0, 1";
		GameInterface.TABLE_SHIPYARD.(row).td1.str = shipstypes[shipspool[i]].Class;
		GameInterface.TABLE_SHIPYARD.(row).td1.textoffset = "40,-16";

		GameInterface.TABLE_SHIPYARD.(row).td2.str = XI_Convertstring(sShip);
		GameInterface.TABLE_SHIPYARD.(row).td2.align = "left";
		GameInterface.TABLE_SHIPYARD.(row).td2.scale = 0.82;

		GameInterface.TABLE_SHIPYARD.(row).td2.textoffset = "0,6";//сдвинул текст чуть ниже, для более красивого расположения плашки, по умолчанию пустая строка IG Baron. 
		GameInterface.TABLE_SHIPYARD.(row).td2.icon.width = 51;
		GameInterface.TABLE_SHIPYARD.(row).td2.icon.height = 26;
		GameInterface.TABLE_SHIPYARD.(row).td2.icon.offset = "0, -4";
		if (LanguageGetLanguage() != "russian") sTemp = "english "; else sTemp = "";
		GameInterface.TABLE_SHIPYARD.(row).td2.icon.group = "ICONS_SPEC";
		GameInterface.TABLE_SHIPYARD.(row).td2.icon.image = sTemp + "universal ship icon"; 
		if ( sti(shipstypes[i].Type.Merchant) && !sti(shipstypes[i].Type.War)) 
			GameInterface.TABLE_SHIPYARD.(row).td2.icon.image = sTemp + "trader ship icon";
		if ( !sti(shipstypes[i].Type.Merchant) && sti(shipstypes[i].Type.War)) 
			GameInterface.TABLE_SHIPYARD.(row).td2.icon.image = sTemp + "battle ship icon";//плашка для боевого типа корабля (есть ещё для быстрого fast ship icon)

		GameInterface.TABLE_SHIPYARD.(row).td3.str = shipstypes[shipspool[i]].rcannon + "\n" + shipstypes[shipspool[i]].fcannon + "<::::::::::>" + shipstypes[shipspool[i]].bcannon + "\n" + shipstypes[shipspool[i]].lcannon;
		GameInterface.TABLE_SHIPYARD.(row).td4.str = shipstypes[shipspool[i]].Capacity;
		GameInterface.TABLE_SHIPYARD.(row).td5.str = floattostring(stf(shipstypes[shipspool[i]].Speedrate),1);
		GameInterface.TABLE_SHIPYARD.(row).td6.str = shipstypes[shipspool[i]].OptCrew;
		GameInterface.TABLE_SHIPYARD.(row).td7.str = shipstypes[shipspool[i]].hp;
		GameInterface.TABLE_SHIPYARD.(row).td8.str = FloatToString(stf(shipstypes[shipspool[i]].WindAgainstSpeed),2);
		GameInterface.TABLE_SHIPYARD.(row).td8.textoffset = "-8,0";
		GameInterface.TABLE_SHIPYARD.(row).index = shipspool[i];
		k++;
	}
	return k;
}

void ProcessFilter()
{
	string sControl = GetEventData();
	int iSelectedCB = GetEventData();
	int iNewState = GetEventData();
//========================================//
	if (sControl == "CLASS_ALL")
	{
	FIS_FilterState = 8 - iSelectedCB;
	FillShipyardTable();
	return;
	}
//========================================//
	if (sControl == "Check_Material")
	{
	FState_Material = iNewState;
	FillPrice();
	return;
	}
//========================================//
	if (sControl == "TunSheme")
	{
		bool bneedunlock = false;
		int i;
		if (!iFreeTP) bneedunlock = true;//было залочено

		if (iNewState) {iFreeTP--;} else {iFreeTP++; }
		Tune_Sheme[iSelectedCB] = iNewState;

		if (iFreeTP < 1 || bneedunlock)
		{
		for(i=1;i<10;i++)
			{
				if (SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", 3, i)) continue;//нажатые кнопки не трогаем
				SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", 5, i, !bneedunlock); //ненажатые блочим, если апгрейды кончились
			}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", 5, 2, 1);//паруса всегда заблочены
		if (RealShips[refNPCShipyard.ship.type].MaxCaliber == 42) SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TunSheme", 5, 9, 1);
		}
		SetFormatedText("HERO_TUNPOINTS",iFreeTP + "/" + iTunPoints);
		FillShipParam();
		return;
	}
//========================================//
}

void SetButtionsAccess()
{
	if (iPriceOrder > sti(pchar.Money)) SetSelectable("BUTTON_BUY", false); else SetSelectable("BUTTON_BUY", true);
}

void ShowMessageInfo()
{
	SetFormatedText("MSG_WINDOW_CAPTION", XI_ConvertString("Ship"));
	SetFormatedText("MSG_WINDOW_TEXT", GetConvertStrWithReplace("Variable_shipyard2_19", "Interface.txt", "#space#", " ") + FindRussianMoneyString(iPriceOrder) + "?");
	SetSelectable("MSG_OK", true);
	XI_WindowShow("MSG_WINDOW", true);
	XI_WindowDisable("MSG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MSG_CANCEL");
}

void GetBortName(string _sBort, string _sBort_real, int BortNumb)
{
	if (BortNumb == 1) {_sBort = "rcannon"; _sBort_real = "cannonr"; return;}
	if (BortNumb == 2) {_sBort = "lcannon"; _sBort_real = "cannonl"; return;}
	if (BortNumb == 3) {_sBort = "fcannon"; _sBort_real = "cannonf"; return;}
	if (BortNumb == 4) {_sBort = "bcannon"; _sBort_real = "cannonb"; return;}
}

void DoBuyShip()
{
	AddMoneyToCharacter(pchar, -iPriceOrder);
	AddCharacterExpToSkill(pchar, "Commerce", GetShipPriceByTTH(sti(refNPCShipyard.Ship.Type), refNPCShipyard)*4 / 700.0);//опыт торговли надо начислять только за корабль? За апгрейды и пушки не начисляется?
	WaitDate("",0,0,0, 0, 35);
	Statistic_AddValue(pchar, "BuyShip", 1);
	Statistic_AddValue(Pchar, "Money_spend", iPriceOrder);

	pchar.ShipInOrder = sti(pchar.ShipInOrder) + 1;//TODO - Проверить, может ли верфист исчезнуть-умереть и добавить там проверок закрытия стройки корабля
	SaveCurrentNpcQuestDateParam(refNPCShipyard,"questTemp.ShipOrderDate");
	refNPCShipyard.questTemp.ShipOrderTime = iTimeMake;
	refNPCShipyard.questTemp.NPCid = NPC_GenerateCharacter("ShipOrder", "PKM_rab_"+(rand(3)+1), "man", "man", rand(5)+1, refNPCShipyard.nation, -1, false);//непись для хранения заказанного корабля
	ref chref = GetCharacter(sti(refNPCShipyard.questTemp.NPCid));
	chref.id = chref.id + "_" + chref.index; //меняем ID на оригинальный
	DeleteAttribute(chref,"ship");
	chref.ship = "";

	aref	arTo, arFrom;
	makearef(arTo, chref.ship);
	makearef(arFrom, refNPCShipyard.Ship);
	CopyAttributes(arTo, arFrom);
	TakeItemFromCharacter(pchar, "Ship_Print_"+GetCharacterShipClass(chref));
	DeleteAttribute(refNPCShipyard,"print1");
	DeleteAttribute(refNPCShipyard,"print2");
	DeleteAttribute(refNPCShipyard,"print3");
	DeleteAttribute(refNPCShipyard,"print4");
	DeleteAttribute(refNPCShipyard,"print5");
	DeleteAttribute(refNPCShipyard,"print6");
	chref.location = "";
	chref.location.group = "";
	chref.location.locator = "";

	if (Ship_Sheme[10] == -10) //если пушки не выбраны, ставим 8фт и обнуляем их кол-во
	{
		int maxQty;
		string sBort, sBort_real, attr;

		chref.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS8;//внимание - вот тут надо ставить макс калибр!!! и на обычной верфи тоже

		sBort = "rcannon";
		sBort_real = "cannonr";
		maxQty = GetBortCannonsMaxQty(chref, sBort);
		for (i = 0; i < maxQty; i++)
		{
			attr = "c" + i;
			chref.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;//нет пушки
			chref.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0;//нет пушки
		}
		sBort = "lcannon";
		sBort_real = "cannonl";
		maxQty = GetBortCannonsMaxQty(chref, sBort);
		for (i = 0; i < maxQty; i++)
		{
			attr = "c" + i;
			chref.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;//нет пушки
			chref.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0;//нет пушки
		}
		sBort = "fcannon";
		sBort_real = "cannonf";
		maxQty = GetBortCannonsMaxQty(chref, sBort);
		for (i = 0; i < maxQty; i++)
		{
			attr = "c" + i;
			chref.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;//нет пушки
			chref.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0;//нет пушки
		}
		sBort = "bcannon";
		sBort_real = "cannonb";
		maxQty = GetBortCannonsMaxQty(chref, sBort);
		for (i = 0; i < maxQty; i++)
		{
			attr = "c" + i;
			chref.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;//нет пушки
			chref.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0;//нет пушки
		}
	}

	string sTemp, sTemp2;
	if (!FState_Material && iFreeTP<iTunPoints)//запоминаем число нужных материалов и записываем их судовой журнал
	{
		int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
		sTemp = GetConvertStrWithReplace("Variable_shipyard2_20", "Interface.txt", "#space#", " ");
		for (int i=1; i<10; i++)
		{
			if (i==2) continue;
			if (Tune_Sheme[i])
			{
				sTemp2 = g_ShipBermudeTuningGoods[i];
				refNPCShipyard.questTemp.(sTemp2) = Tun_Mater1[i];
				sTemp += NewStr() + XI_ConvertString(sTemp2) + " - " + Tun_Mater1[i] + GetConvertStrWithReplace("Variable_shipyard2_21", "Interface.txt", "#space#", " ");
				sTemp2 = g_ShipBermudeTuningItems[i];
				refNPCShipyard.questTemp.(sTemp2) = Tun_Mater2[i];
				sTemp += NewStr() + LanguageConvertString(idLngFile, Items[FindItem(g_ShipBermudeTuningItems[i])].name) + " - " + Tun_Mater2[i] + GetConvertStrWithReplace("Variable_shipyard2_22", "Interface.txt", "#space#", " ");
			}
			else
			{
				sTemp2 = g_ShipBermudeTuningGoods[i];
				refNPCShipyard.questTemp.(sTemp2) = 0;
				sTemp2 = g_ShipBermudeTuningItems[i];
				refNPCShipyard.questTemp.(sTemp2) = 0;
			}
		}
		refNPCShipyard.questTemp.chest = sundukSum*(iTunPoints-iFreeTP);
		sTemp += NewStr() + GetConvertStrWithReplace("Variable_shipyard2_23", "Interface.txt", "#space#", " ") + sundukSum*(iTunPoints-iFreeTP) + GetConvertStrWithReplace("Variable_shipyard2_24", "Interface.txt", "#space#", " ");
	}
	else sTemp = "";

	string sTitle = "ShipOrder";
	ReOpenQuestHeader(sTitle);
	AddQuestRecordEx(sTitle, "ShipOrder", "t1");
	AddQuestUserData(sTitle, "sName", GetFullName(refNPCShipyard));
	AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + refNPCShipyard.city + "Gen"));
	AddQuestUserData(sTitle, "sShipType", XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(refNPCShipyard.ship.type)].basetype), "Name") + "Acc"));
	AddQuestUserData(sTitle, "money", iPriceOrder);
	AddQuestUserData(sTitle, "time", iTimeMake);
	AddQuestUserData(sTitle, "TuningMaterial", sTemp);

	DeleteAttribute(refNPCShipyard,"ship");
	refNPCShipyard.ship = "";
	ProcessExitCancel();
}

void IncShipQ(int _add)
{
	if (CurTable != "TABLE_OTHER") return;

	int iQMAXTemp = iQMAX;
	int iFreeSPTemp = iFreeSP;
	if (iSelected == 10) //если выбран тип пушек
	{
		iFreeSPTemp = 10;//выбор типа орудий не тратит очки апгрейда
		int curCaliber = sti(RealShips[sti(refNPCShipyard.ship.type)].MaxCaliber);
		iQMAXTemp = 9;//42 фт
		switch (curCaliber)
		{
		case 8: iQMAXTemp = -8; break;
		case 10: iQMAXTemp = -6; break;
		case 12: iQMAXTemp = -4; break;
		case 16: iQMAXTemp = -2; break;
		case 20: iQMAXTemp = 0; break;
		case 24: iQMAXTemp = 2; break;
		case 28: iQMAXTemp = 4; break;
		case 32: iQMAXTemp = 6; break;
		case 36: iQMAXTemp = 8; break;
		}
	}

	if (iFreeSPTemp < _add) _add = iFreeSPTemp;
	if ((Ship_Sheme[iSelected] + _add) > iQMAXTemp)
	{
		_add = iQMAXTemp - Ship_Sheme[iSelected];
	}
	if (_add > 0)
	{
		Ship_Sheme[iSelected] += _add;
		if (iSelected-10) iFreeSP -= _add;//если строка 10, то свободные баллы не меняем
	}
	else return;
	FillShipParam();
	SetFormatedText("HERO_SHIPPOINTS",iFreeSP + "/" + iShipPoints);
}

void DecShipQ(int _add)
{
	if (CurTable != "TABLE_OTHER") return;
	int iQMINTemp = iQMIN;

	if (iSelected == 10) iQMINTemp = -10;//если строка 10, то нижний предел всегда максимальный

	if ((Ship_Sheme[iSelected] - _add) < iQMINTemp)
	{
		_add = Ship_Sheme[iSelected] - iQMINTemp;
	}
	if (_add > 0)
	{
		Ship_Sheme[iSelected] -= _add;
		if (iSelected-10) iFreeSP += _add;//если строка 10, то свободные баллы не меняем
	}
	else return;
	FillShipParam();
	SetFormatedText("HERO_SHIPPOINTS",iFreeSP + "/" + iShipPoints);
}

void HideSkillChanger()
{
	SetNodeUsing("B_SKILLUP",  false);
	SetNodeUsing("B_SKILLDown",  false);
}

void SetSkillArrows()
{
	if (CurTable == "TABLE_OTHER")
	{
		if (iSelected == 2) return;//на парусах не включаем
		if (iSelected == 9) return;//на калибре тоже

		int iQMINTemp = iQMIN;
		int iQMAXTemp = iQMAX;
		int iFreeSPTemp = iFreeSP;
		if (iSelected == 10) //тип пушек
		{
			iFreeSPTemp = 1;//выбор типа орудий не тратит очки апгрейда
			iQMINTemp = -10;//минимум - без пушек

			int curCaliber = sti(RealShips[sti(refNPCShipyard.ship.type)].MaxCaliber);
			iQMAXTemp = 9;//42 фт
			switch (curCaliber)
			{
			case 8: iQMAXTemp = -8; break;
			case 10: iQMAXTemp = -6; break;
			case 12: iQMAXTemp = -4; break;
			case 16: iQMAXTemp = -2; break;
			case 20: iQMAXTemp = 0; break;
			case 24: iQMAXTemp = 2; break;
			case 28: iQMAXTemp = 4; break;
			case 32: iQMAXTemp = 6; break;
			case 36: iQMAXTemp = 8; break;
			}
		}

		if (Ship_Sheme[iSelected] > iQMINTemp)
		{
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 237,298 + 26*(iSelected-1), 258, 319 + 26*(iSelected-1), 0);
			SetNodeUsing("B_SKILLDown", true);
		}

		if (iFreeSPTemp > 0 && Ship_Sheme[iSelected] < iQMAXTemp)
		{
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 258,298 + 26*(iSelected-1), 279, 319 + 26*(iSelected-1), 0);
			SetNodeUsing("B_SKILLUP",  true);
		}
	}
}

void FillPrice()
{
	int iShip = sti(refNPCShipyard.ship.type);
	ref rRealShip = &RealShips[iShip];
	int iTemp, i, k, m;
	string row, sGood;
	int iAddedPrice = 1;
	if (sti(rRealShip.class) <= 4) {
		iAddedPrice++;
	}
	iPriceOrder	= GetShipPriceByTTH(iShip, refNPCShipyard)*iAddedPrice;
	string stextPRICE = GetConvertStrWithReplace("Variable_shipyard2_25", "Interface.txt", "#space#", " ") + MakeMoneyShow(iPriceOrder, MONEY_SIGN, MONEY_DELIVER);

	if (Ship_Sheme[10] != -10.0)
	{
	iTemp = GetStoreGoodsPrice(refStore, GetCannonGoodsIdxByType(sti(refNPCShipyard.Ship.Cannons.Type)), PRICE_TYPE_BUY, pchar, sti(rRealShip.CannonsQuantity));
	stextPRICE += newStr() + GetConvertStrWithReplace("Variable_cannons_price", "Interface.txt", "#space#", " ") + MakeMoneyShow(iTemp, MONEY_SIGN, MONEY_DELIVER);
	iPriceOrder += iTemp;
	}
	else stextPRICE += "\n";

	if (iFreeTP < iTunPoints)
	{
	SetNodeUsing("TABLE_TUN", !FState_Material);//показать/скрыть таблицу с материалами
	SetNodeUsing("SCROLL_TUN", !FState_Material);
	SetNodeUsing("Money_TEXT4", !FState_Material);
		if (FState_Material)
		{
			stextPRICE += "\n\n\n";
			for (k=1;k<10;k++)
			{
				if(Tune_Sheme[k])
				{
				iTemp = Tun_Mater3[k];
				iTemp += GetStoreGoodsPrice(refStore, FindGood(g_ShipBermudeTuningGoods[k]), PRICE_TYPE_BUY, pchar, Tun_Mater1[k]);
				iTemp += Tun_Mater2[k] * GetTradeItemPrice(g_ShipBermudeTuningItems[k], PRICE_TYPE_BUY);
				iTemp += sundukSum * GetTradeItemPrice("Chest", PRICE_TYPE_BUY);
				stextPRICE += sAdd[k] + MakeMoneyShow(iTemp, MONEY_SIGN, MONEY_DELIVER);
				iPriceOrder += iTemp;
				}
			}
		}
		else
		{
			Table_Clear("TABLE_TUN", false, true, false);
			GameInterface.TABLE_TUN.hr.td1.str = GetConvertStrWithReplace("Variable_shipyard2_26", "Interface.txt", "#space#", " ");//заголовок скрываю, но если его не объявлять первая строчка не будет показываться
			GameInterface.TABLE_TUN.hr.td2.str = GetConvertStrWithReplace("Variable_shipyard2_27", "Interface.txt", "#space#", " ");

			int Tun_Mater3_sum = 0;
			int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
			i = 1;
			for (k=1;k<10;k++)
			{
				if (Tune_Sheme[k])
				{
					row = "tr" + i;
					sGood = g_ShipBermudeTuningGoods[k];
					GameInterface.TABLE_TUN.(row).td1.icon.group = "GOODS";
					GameInterface.TABLE_TUN.(row).td1.icon.image = sGood;
					GameInterface.TABLE_TUN.(row).td1.icon.offset = "-3, -1";
					GameInterface.TABLE_TUN.(row).td1.icon.width = 20;
					GameInterface.TABLE_TUN.(row).td1.icon.height = 20;
					GameInterface.TABLE_TUN.(row).td1.textoffset = "17,0";
					GameInterface.TABLE_TUN.(row).td1.str = XI_ConvertString(sGood);
					GameInterface.TABLE_TUN.(row).td1.scale = 0.85;
					GameInterface.TABLE_TUN.(row).td1.align = "left";
					GameInterface.TABLE_TUN.(row).td2.str = Tun_Mater1[k];
					GameInterface.TABLE_TUN.(row).td2.scale = 0.85;
					i++;
					row = "tr" + i;
					m = FindItem(g_ShipBermudeTuningItems[k]);
					GameInterface.TABLE_TUN.(row).td1.icon.group = Items[m].picTexture;
					GameInterface.TABLE_TUN.(row).td1.icon.image = "itm" + Items[m].picIndex;
					GameInterface.TABLE_TUN.(row).td1.icon.offset = "-2,0";
					GameInterface.TABLE_TUN.(row).td1.icon.width = 18;
					GameInterface.TABLE_TUN.(row).td1.icon.height = 18;
					GameInterface.TABLE_TUN.(row).td1.textoffset = "17,0";
					GameInterface.TABLE_TUN.(row).td1.scale = 0.65;
					GameInterface.TABLE_TUN.(row).td1.align = "left";
					GameInterface.TABLE_TUN.(row).td1.str = LanguageConvertString(idLngFile, Items[m].name);
					GameInterface.TABLE_TUN.(row).td2.str = Tun_Mater2[k];
					GameInterface.TABLE_TUN.(row).td2.scale = 0.85;
					i++;
					Tun_Mater3_sum += Tun_Mater3[k];
				}
			}
			row = "tr" + i;
			m = FindItem("Chest");
			GameInterface.TABLE_TUN.(row).td1.icon.group = Items[m].picTexture;
			GameInterface.TABLE_TUN.(row).td1.icon.image = "itm" + Items[m].picIndex;
			GameInterface.TABLE_TUN.(row).td1.icon.offset = "-2, 0";
			GameInterface.TABLE_TUN.(row).td1.icon.width = 18;
			GameInterface.TABLE_TUN.(row).td1.icon.height = 18;
			GameInterface.TABLE_TUN.(row).td1.textoffset = "17,0";
			GameInterface.TABLE_TUN.(row).td1.scale = 0.85;
			GameInterface.TABLE_TUN.(row).td1.align = "left";
			GameInterface.TABLE_TUN.(row).td1.str = LanguageConvertString(idLngFile, Items[m].name);
			GameInterface.TABLE_TUN.(row).td2.str = sundukSum*(iTunPoints - iFreeTP);
			GameInterface.TABLE_TUN.(row).td2.scale = 0.85;

			Table_UpdateWindow("TABLE_TUN");
			SetFormatedText("Money_TEXT4", GetConvertStrWithReplace("Variable_shipyard2_28", "Interface.txt", "#space#", " ") + MakeMoneyShow(Tun_Mater3_sum, MONEY_SIGN, MONEY_DELIVER));
			iPriceOrder += Tun_Mater3_sum;
		}
	}
	else
	{
	SetNodeUsing("TABLE_TUN", false);//скрыть таблицу с материалами
	SetNodeUsing("SCROLL_TUN", false);
	SetNodeUsing("Money_TEXT4", false);
	}

	SetFormatedText("Money_TEXT3", stextPRICE);
	SetFormatedText("Money_TEXT2", GetConvertStrWithReplace("Variable_shipyard2_29", "Interface.txt", "#space#", " ") + MakeMoneyShow(iPriceOrder, MONEY_SIGN, MONEY_DELIVER));
}

void CalcTuningPrice()
{
	int iShipT = refNPCShipyard.ship.type;
	int cannonQ = sti(RealShips[iShipT].CannonsQuantity);
	int shipClass = sti(RealShips[iShipT].Class);
	int shipCapacity = sti(RealShips[iShipT].Capacity);
	float shipSpeedRate = stf(RealShips[iShipT].SpeedRate);
	float MastMulti = stf(RealShips[iShipT].MastMultiplier);
	int shipMaxCrew = sti(RealShips[iShipT].MaxCrew);
	int shipHP		= sti(RealShips[iShipT].HP);
	float shipTurnRate = stf(RealShips[iShipT].TurnRate);
	float shipWindAgainst = stf(RealShips[iShipT].WindAgainstSpeed);

	float fBasePrice = 0.0;
	if(shipClass <= 4){ fBasePrice = stf(RealShips[iShipT].Price) / 20 * MOD_SKILL_ENEMY_RATE*3;}


	sundukSum = 7-shipClass;

	int i = 1;//HP
	Tun_Mater1[i] = makeint(35 * (7-shipClass) + shipHP * 7/100);
	Tun_Mater2[i] = makeint(5 * ((7-shipClass)*3));
	Tun_Mater3[i] = makeint(shipHP * MOD_SKILL_ENEMY_RATE*3 + fBasePrice);
	i = i + 2;//MAST
	Tun_Mater1[i] = makeint((shipHP * 25/1000 + 70 * (7-shipClass)));
	Tun_Mater2[i] = makeint(10 * (7-shipClass));
	Tun_Mater3[i] = makeint(100 * MastMulti * MOD_SKILL_ENEMY_RATE*3 + fBasePrice);
	i++;//Speed
	Tun_Mater1[i] = makeint((shipHP * 25/1000 + 70 * (7-shipClass)));
	Tun_Mater2[i] = makeint(5 * (7-shipClass));
	Tun_Mater3[i] = makeint(100 * shipSpeedRate * MOD_SKILL_ENEMY_RATE*3 + fBasePrice);
	i++;//Turn
	Tun_Mater1[i] = makeint((shipHP * 25/1000 + 375/shipClass+20));
	Tun_Mater2[i] = makeint((5 * (7-shipClass)+2));
	Tun_Mater3[i] = makeint(30 * shipTurnRate * MOD_SKILL_ENEMY_RATE*3 + fBasePrice);
	i++;//Wind
	Tun_Mater1[i] = makeint((shipHP * 25/1000 + 750/shipClass+20));
	Tun_Mater2[i] = makeint((6 * (7-shipClass)+1));
	Tun_Mater3[i] = makeint(300 * shipWindAgainst * MOD_SKILL_ENEMY_RATE*3 + fBasePrice);
	i++;//capacity
	Tun_Mater1[i] = makeint((35 * (7-shipClass) + shipCapacity * 7/100));
	Tun_Mater2[i] = makeint((10 * (7-shipClass)+10));
	Tun_Mater3[i] = makeint(2 * shipCapacity * MOD_SKILL_ENEMY_RATE*3 + fBasePrice);
	i++;//MaxCrew
	Tun_Mater1[i] = makeint((shipMaxCrew * 6/10 + 50 * (7-shipClass)));
	Tun_Mater2[i] = makeint((6 * (7-shipClass)+3));
	Tun_Mater3[i] =  makeint(15 * shipMaxCrew * MOD_SKILL_ENEMY_RATE*3 + fBasePrice);
	i++;//cannon
	Tun_Mater1[i] = makeint((cannonQ * 2 + 35 * (7-shipClass) - 20));
	Tun_Mater2[i] = makeint((7-shipClass)/2);
	if (Tun_Mater2[i] < 1) Tun_Mater2[i] = 1;
	Tun_Mater3[i] = makeint(100 * cannonQ * MOD_SKILL_ENEMY_RATE*3 + fBasePrice);
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	//string sRow = "tr" + (iRow + 1);
	if (sControl == "TABLE_SHIPYARD")
	{
		if (!SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, sControl, 1 )) SortTable(sControl, iColumn);
		Table_UpdateWindow(sControl);
	}
}

void InitSAddMassive()
{
	string sAddString = GetConvertStrWithReplace("Variable_sAdd_1", "Interface.txt", "#enter#", "\n");
	sAdd[1] = sAddString + " ";
	sAddString = GetConvertStrWithReplace("Variable_sAdd_2", "Interface.txt", "#enter#", "\n");
	sAdd[3] = sAddString + " ";
	sAddString = GetConvertStrWithReplace("Variable_sAdd_3", "Interface.txt", "#enter#", "\n");
	sAdd[4] = sAddString + " ";
	sAddString = GetConvertStrWithReplace("Variable_sAdd_4", "Interface.txt", "#enter#", "\n");
	sAdd[5] = sAddString + " ";
	sAddString = GetConvertStrWithReplace("Variable_sAdd_5", "Interface.txt", "#enter#", "\n");
	sAdd[6] = sAddString + " ";
	sAddString = GetConvertStrWithReplace("Variable_sAdd_6", "Interface.txt", "#enter#", "\n");
	sAdd[7] = sAddString + " ";
	sAddString = GetConvertStrWithReplace("Variable_sAdd_7", "Interface.txt", "#enter#", "\n");
	sAdd[8] = sAddString + " ";
	sAddString = GetConvertStrWithReplace("Variable_sAdd_8", "Interface.txt", "#enter#", "\n");
	sAdd[9] = sAddString + " ";
}

//Смена каюты -->
void ExitChangeCABINMenu()
{
	XI_WindowShow("CHANGE_CABIN_WINDOW", false);
	XI_WindowDisable("CHANGE_CABIN_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}
void ShowChangeCABINMenu()
{
	XI_WindowShow("CHANGE_CABIN_WINDOW", true);
	XI_WindowDisable("CHANGE_CABIN_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	SetCurrentNode("CHANGE_CABIN_CANCEL");

	ref refShip = GetRealShip(sti(refNPCShipyard.Ship.Type));
	for (int i=0;i<iCabinsNum;i++)
	{
		if (sti(refShip.Class)==7) break;
		if (refShip.CabinType != sCabins[i]) continue;
		iCurCabin = i; 
		break;
	}
	SetChangeCABINInfo();
}
void SetChangeCABINInfo()
{
	string sTexture = GetShipTexturesForChangeCABIN();
	SetNewPicture("CHANGE_CABIN_TYPE", sTexture);

	bool isNewCabin = true;
	ref refShip = GetRealShip(sti(refNPCShipyard.Ship.Type));
	if (!isCabinforClass(sti(refShip.Class))) isNewCabin = false;

	if (isNewCabin) SetSelectable("CHANGE_CABIN_OK", true);	
		else SetSelectable("CHANGE_CABIN_OK", false);
}
//Каюты, доступные разным классам при смене
bool isCabinforClass(int iClass)
{
	switch (iClass)
	{
	case 7: return false; break;									//тут только один тип, так что всегда отказ в смене
	case 6: if (iCurCabin>-1 && iCurCabin<3) return true; break; 	//0-2
	case 5: if (iCurCabin>0 && iCurCabin<4) return true; break;		//1-3
	case 4: if (iCurCabin>2 && iCurCabin<6) return true; break;		//3-5
	case 3: if (iCurCabin>3 && iCurCabin<7) return true; break; 	//4-6
	case 2: if (iCurCabin>5 && iCurCabin<9) return true; break;		//6-8
	case 1: if (iCurCabin>6 && iCurCabin<10) return true; break;	//7-9
	}
	return false;
}
string GetShipTexturesForChangeCABIN()
{
	int nLoc = FindLocation(sCabins[iCurCabin]);
	if (nLoc >= 0 && CheckAttribute(&Locations[nLoc],"image")) 
	return Locations[nLoc].image;
}
void SelectChangeCABIN(bool bLeft)
{
	if (bLeft) iCurCabin--; else iCurCabin++;
	if (iCurCabin < 0) iCurCabin = iCabinsNum-1;
	if (iCurCabin == iCabinsNum) iCurCabin = 0;
	SetChangeCABINInfo();
}
void SetNewCABINToCharacterShip()
{
	ref refShip = GetRealShip(sti(refNPCShipyard.Ship.Type));
	refShip.CabinType = sCabins[iCurCabin];
	ExitChangeCABINMenu();
}
//Смена каюты <--