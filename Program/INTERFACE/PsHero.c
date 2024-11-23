//////////////////////////
// 		CSP 2.2.0+		//
//////////////////////////

string totalInfo = "";
string CurTable, CurRow;
string sMessageMode;
ref chr;

int iSelected; // курсор в таблице

void InitInterface(string iniName)
{
 	StartAboveForm(true);

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	if (!CheckAttribute(pchar, "PGG_killed"))
	{
		pchar.PGG_killed = 0;
	}
	if (!CheckAttribute(pchar, "PGG_NotKilled"))
	{
		pchar.PGG_NotKilled = 0;
	}

	string sTemp = "";
	if (!checkattribute(pchar, "buypgginfo")) {pchar.buyPGGinfo = 0; pchar.buyPGGinfo_Qty = " ";}//открыли первый раз до покупки, таблица должна быть пустой
	if (MOD_BETTATESTMODE == "On" || pchar.buyPGGinfo == "1")
	{
		sTemp += " (" + (PsHeroQty - sti(pchar.PGG_killed) - sti(pchar.PGG_NotKilled))+ " / " + (PsHeroQty - sti(pchar.PGG_NotKilled)) + ")";
		pchar.buyPGGinfo_Qty = sTemp;
	}
	if (MOD_BETTATESTMODE != "On" && pchar.buyPGGinfo == "2") sTemp = pchar.buyPGGinfo_Qty + GetConvertStrWithReplace("Variable_PsHero_1", "Interface.txt", "#space#", " ") + FindRussianDaysString(GetQuestPastDayParam("buy_PGG_info")) + GetConvertStrWithReplace("Variable_PsHero_2", "Interface.txt", "#space#", " ");
	if (MOD_BETTATESTMODE == "On") sTemp += GetConvertStrWithReplace("Variable_PsHero_3", "Interface.txt", "#space#", " ");
	SetFormatedText("MAP_CAPTION", XI_ConvertString("titlePsHero") + sTemp);
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("ShowPGGInfo","ShowPGGInfo",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0); // выход из интерфейса
	sMessageMode = "";
	if (MOD_BETTATESTMODE == "On" || pchar.buyPGGinfo == "1") FillTable(); else RecallTable(); //проверить, что будет при первом открытии без сохранки
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_ANY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_ANY_EXIT );
}

void IDoExit(int exitCode)
{
	if (MOD_BETTATESTMODE != "On") RememberTable();//при читах не обновляем запомненное
    EndAboveForm(true);
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("ShowPGGInfo","ShowPGGInfo");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{

	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}


void FillTable()
{
	ref chr;
	int i, n;
	string row;
	int iS,iP,iE,iC,iI,iA,iL;

	n = 1;
	// шапка -->
    GameInterface.TABLE_HERO.select = 0;
    GameInterface.TABLE_HERO.hr.td1.str = GetConvertStrWithReplace("Variable_PsHero_4", "Interface.txt", "#space#", " ");
    GameInterface.TABLE_HERO.hr.td1.scale = 1.0;
    GameInterface.TABLE_HERO.hr.td2.str = GetConvertStrWithReplace("Variable_PsHero_5", "Interface.txt", "#space#", " ");
    GameInterface.TABLE_HERO.hr.td2.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td3.str = GetConvertStrWithReplace("Variable_PsHero_6", "Interface.txt", "#space#", " ");
	GameInterface.TABLE_HERO.hr.td3.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td4.str = GetConvertStrWithReplace("Variable_PsHero_7", "Interface.txt", "#space#", " ");
	GameInterface.TABLE_HERO.hr.td4.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td5.str = GetConvertStrWithReplace("Variable_PsHero_8", "Interface.txt", "#space#", " ");
	GameInterface.TABLE_HERO.hr.td5.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td6.str = GetConvertStrWithReplace("Variable_PsHero_9", "Interface.txt", "#space#", " ");
	GameInterface.TABLE_HERO.hr.td6.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td7.str = "P.I.R.A.T.E.S.";
	GameInterface.TABLE_HERO.hr.td7.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td8.str = GetConvertStrWithReplace("Variable_PsHero_10", "Interface.txt", "#space#", " ");
	GameInterface.TABLE_HERO.hr.td8.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td9.str = GetConvertStrWithReplace("Variable_PsHero_11", "Interface.txt", "#space#", " ");
	GameInterface.TABLE_HERO.hr.td9.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td10.str = GetConvertStrWithReplace("Variable_PsHero_12", "Interface.txt", "#space#", " ");
	GameInterface.TABLE_HERO.hr.td10.scale = 1.0;
//--> mod tablesort
	//GameInterface.TABLE_HERO.hr.td1.sorttype = "string";//эту колонку не сортируем, не создаём атрибут!
	GameInterface.TABLE_HERO.hr.td2.sorttype = "string";
	GameInterface.TABLE_HERO.hr.td3.sorttype = "";//числа - любое значение кроме "string"
	GameInterface.TABLE_HERO.hr.td4.sorttype = "";
	GameInterface.TABLE_HERO.hr.td5.sorttype = "string";
	GameInterface.TABLE_HERO.hr.td6.sorttype = "string";
	GameInterface.TABLE_HERO.hr.td7.sorttype = "string";
	GameInterface.TABLE_HERO.hr.td8.sorttype = "";
	GameInterface.TABLE_HERO.hr.td9.sorttype = "";
	GameInterface.TABLE_HERO.hr.td10.sorttype = "";
	GameInterface.TABLE_HERO.hr.td10.sortdir = "dec";
//<-- mod tablesort
	for (i = 1; i <= PsHeroQty; i++)
	{
		chr = CharacterFromID("PsHero_" + i);
		if(!CharacterIsDead(chr))
		{
			if(chr.PGGAi.IsPGG != false)
			{
				row = "tr" + n;
				GameInterface.TABLE_HERO.(row).index = i;
				GameInterface.TABLE_HERO.(row).td1.icon.texture = "INTERFACES\PORTRAITS\128\face_" + chr.faceId + ".tga";
				GameInterface.TABLE_HERO.(row).td1.icon.uv = "0,0,1,1";
				GameInterface.TABLE_HERO.(row).td1.icon.width = 40;
				GameInterface.TABLE_HERO.(row).td1.icon.height = 40;
				GameInterface.TABLE_HERO.(row).td1.icon.offset = "-2, -1";
				GameInterface.TABLE_HERO.(row).td1.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td2.str = GetFullName(chr);
				GameInterface.TABLE_HERO.(row).td2.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td3.str = chr.rank;
				GameInterface.TABLE_HERO.(row).td3.scale = 1.0;
				GameInterface.TABLE_HERO.(row).td4.str = chr.nation;
				GameInterface.TABLE_HERO.(row).td4.icon.group  = "NATIONS";
				GameInterface.TABLE_HERO.(row).td4.icon.image  = Nations[sti(chr.nation)].Name;
				GameInterface.TABLE_HERO.(row).td4.icon.width  = 40;
				GameInterface.TABLE_HERO.(row).td4.icon.height = 40;
				GameInterface.TABLE_HERO.(row).td4.icon.offset = "4, 0";
				GameInterface.TABLE_HERO.(row).td4.scale = 0;

				if (GetCharacterShipType(chr) != SHIP_NOTUSED)
				{
					GameInterface.TABLE_HERO.(row).td5.str = XI_ConvertString(RealShips[GetCharacterShipType(chr)].BaseName);
					GameInterface.TABLE_HERO.(row).td5.scale = 0.8;
				}
				else
				{
					GameInterface.TABLE_HERO.(row).td5.str = GetConvertStrWithReplace("Variable_PsHero_13", "Interface.txt", "#space#", " ");
					GameInterface.TABLE_HERO.(row).td5.scale = 0.8;
				}
				if (!CheckAttribute(chr, "PGGAi.Task.SetSail"))
				{
					GameInterface.TABLE_HERO.(row).td6.str = XI_ConvertString("Colony"+chr.PGGAi.location.town);
				}
				else
				{
					if (CheckAttribute(chr, "PGG_warrior"))
					{
						GameInterface.TABLE_HERO.(row).td6.str = GetConvertStrWithReplace("Variable_PsHero_14", "Interface.txt", "#space#", " "));
					}
					else
					{
						GameInterface.TABLE_HERO.(row).td6.str = GetConvertStrWithReplace("Variable_PsHero_15", "Interface.txt", "#space#", " ")+ XI_ConvertString("Colony" + chr.PGGAi.Task.Target + "Acc");
					}
					if (CheckAttribute(chr, "PGG_trader"))
					{
						GameInterface.TABLE_HERO.(row).td6.str = GetConvertStrWithReplace("Variable_PsHero_16", "Interface.txt", "#space#", " ")+ XI_ConvertString("Colony" + chr.PGGAi.Task.Target + "Acc");
					}
					if (CheckAttribute(chr, "PGGAi.DontUpdate"))
					{
						GameInterface.TABLE_HERO.(row).td6.str = GetConvertStrWithReplace("Variable_PsHero_17", "Interface.txt", "#space#", " "));
					}
				}
				GameInterface.TABLE_HERO.(row).td6.scale = 0.8;
				iS = sti(chr.SPECIAL.Strength);
				iP = sti(chr.SPECIAL.Perception);
				iA = sti(chr.SPECIAL.Agility);
				iC = sti(chr.SPECIAL.Charisma);
				iI = sti(chr.SPECIAL.Intellect);
				iE = sti(chr.SPECIAL.Endurance);
				iL = sti(chr.SPECIAL.Luck);
				GameInterface.TABLE_HERO.(row).td7.str = "" + (iS+iP+iE+iC+iI+iA+iL) + " | "+iS+" "+iP+" "+iA+" "+iC+" "+iI+" "+iE+" "+iL;
				GameInterface.TABLE_HERO.(row).td7.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td8.str = ""+makeint(chr.reputation);
				GameInterface.TABLE_HERO.(row).td8.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td9.str = ""+PGG_ChangeRelation2MainCharacter(chr, 0);
				GameInterface.TABLE_HERO.(row).td9.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td10.str = ""+chr.Money;
				GameInterface.TABLE_HERO.(row).td10.scale = 0.8;
				n++;
			}
		}
	}
	Table_UpdateWindow("TABLE_HERO");
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);//разве не +1?
}

void ShowPGGInfo()
{
	if (MOD_BETTATESTMODE == "On" || pchar.buyPGGinfo == "1") 
	{
		if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
		{ // нет ПГГ в списке
			chr = CharacterFromID("PsHero_" + GameInterface.TABLE_HERO.(CurRow).index);
			SetSPECIALMiniTable("TABLE_SMALLSKILL", chr);
			SetOTHERMiniTable("TABLE_SMALLOTHER", chr);
			SetFormatedText("OFFICER_NAME", GetFullName(chr));
			SetNewPicture("CHARACTER_BIG_PICTURE", "interfaces\portraits\256\face_" + chr.faceId + ".tga");
			SetNewPicture("CHARACTER_FRAME_PICTURE", "interfaces\Frame3.dds");
			int iShip = sti(chr.ship.type);
			if (iShip != SHIP_NOTUSED)
			{
				ref refShip = GetRealShip(iShip);
				string sShip = refShip.BaseName;
				SetNewPicture("SHIP_BIG_PICTURE", "interfaces\ships\" + sShip + ".dds");
			}
			else {SetNewPicture("SHIP_BIG_PICTURE", "interfaces\blank_ship2.dds");}
			SetNewPicture("SHIP_FRAME_PICTURE", "interfaces\Frame2.dds");
			SetNewPicture("CHARACTER_PROFESSION", "INTERFACES\Sith\Char_"+GetSpeciality(chr)+".dds");
	
			XI_WindowShow("RPG_WINDOW", true);
			XI_WindowDisable("RPG_WINDOW", false);
			sMessageMode = "RPG_Hint";
		}
	}//в запомненной таблице подробности о ПГГ не показываем, надо как-то отдельно запоминать эти данные
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("RPG_WINDOW", false);
		XI_WindowDisable("RPG_WINDOW", true);
		sMessageMode = "";
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

//--> mod tablesort
	if (!SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, sControl, 1 ))
	{
		SortTable(sControl, iColumn);//сортировка запомненной таблицы отключена - крашит - когда-нибудь позже разобраться надо будет
	}
//<-- mod tablesort
	Table_UpdateWindow(sControl);
}
void RecallTable()
{
	RecursiveCopy(pchar, "buyPGGinfo", &GameInterface, "TABLE_HERO");
	Table_UpdateWindow("TABLE_HERO");
}

void RememberTable()
{
	aref arTo;
	aref arFrom;
	makearef(arTo, pchar.buyPGGinfo);
	makearef(arFrom, GameInterface.TABLE_HERO);
	CopyAttributes(arTo,arFrom);//новое запомним
	pchar.buyPGGinfo = "2";//таблица не купленная, а запомненная, второй раз так как затирается при копировании
}
