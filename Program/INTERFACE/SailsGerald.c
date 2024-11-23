#include "interface\modelviewer\modelviewer.c"

#define SAILS_COUNT 91

ref shref;
ref chref;

int    price;
int curcolor = 0;
int defcolor = 0;
int cursails = 0;
int defsails = 0;
string curgerald = "";
string defgerald = "";
string embsail = "";
bool allowgerald = false;
bool setcolor = false;
bool sails = false;
bool geraldsails = false;
bool sailfound = false;

int basehull = 0;
int hullid = 0;

void InitInterface_RR(string iniName, ref shipyarder, ref who)
{
	//use fake char to edit ship
	chref = &Characters[GenerateCharacter(sti(pchar.nation),WITHOUT_SHIP,"pirate",MAN,1,WARRIOR)];
	chref.ship.type = who.ship.type;
    int st = GetCharacterShipType(chref);
    shref = GetRealShip(st);

	if (!CheckAttribute(shref,"SailsColorIdx")) shref.SailsColorIdx = defcolor;
	defcolor = sti(shref.SailsColorIdx);
	curcolor = defcolor;
	cursails = sti(shref.ship.upgrades.sails);
	defsails = cursails;
	if (CheckAttribute(shref,"ShipSails.Gerald_Name"))
	{
		curgerald = shref.ShipSails.Gerald_Name;
		defgerald = curgerald;
	}
	if (CheckAttribute(shref,"EmblemedSails.normalTex"))
	{
		embsail = shref.EmblemedSails.normalTex;
		DeleteAttribute(shref,"EmblemedSails");
	}
	if (CheckAttribute(chref,"Features.GeraldSails") && chref.Features.GeraldSails == true)
	{
		geraldsails = true;
	}

    price = GetSailsTuningPrice(chref, shipyarder, SAILSGERALD_PRICE_RATE);

    SetEventHandler("GetInterfaceTexture", "ScrollGetTexture", 0);

	EnumerateIcons("resource\textures\interfaces\sails", "00*", "SCROLL_COLORS", 0);
	if (bNewSails && shipyarder.name == GetConvertStrWithReplace("Variable_SailsGerald_1", "Interface.txt", "#space#", " ")) EnumerateIcons("resource\textures\ships", "parus_sail_*", "SCROLL_SAILS", 0);
	else EnumerateIcons("resource\textures\ships\PlayerSails", "*.tga.tx", "SCROLL_SAILS", 0);
	if(CheckSailsGerald(chref) && CanSetSailsGerald(chref)) EnumerateIcons("resource\textures\ships\gerald", "*.tga.tx", "SCROLL_GERALD", 0);
	if(!CheckAttribute(&GameInterface,"SCROLL_COLORS.current"))
	{
		GameInterface.SCROLL_COLORS.current = defcolor;
	}
	if(!CheckAttribute(&GameInterface,"SCROLL_GERALD.current"))
	{
		GameInterface.SCROLL_GERALD.current = GetChosenTypeIndex("gerald")-1;
	}
	if(!CheckAttribute(&GameInterface,"SCROLL_SAILS.current"))
	{
		GameInterface.SCROLL_SAILS.current = GetChosenTypeIndex("sails")-1;
	}

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("ChangeSelectScrollImage", "ChangeSelectScrollImage", 0);
	SetEventHandler("CheckButtonChange","procCheckBoxChange",0);

	CheckChangeSailStatus();
	if(!CheckSailsGerald(chref) || !CanSetSailsGerald(chref))
	{
		SetNodeUsing("SAILS_GERALD_LEFT_BUTTON",false);
		SetNodeUsing("SAILS_GERALD_RIGHT_BUTTON",false);
		SetNodeUsing("GERALD_CHECKBOX",false);
		XI_WindowShow("GERALDBUTTONS", false);
		XI_WindowDisable("GERALDBUTTONS", true);
		SetNewPicture("GERALD_NO_PIC", "interfaces\DeleteGerald.tga");
		SetFormatedText("GERALD_NO", GetConvertStrWithReplace("Variable_SailsGerald_2", "Interface.txt", "#space#", " "));
	}
	else {if (defgerald != "") CheckButton_SetState("GERALD_CHECKBOX", 1, true);}
	if (sailfound == true) CheckButton_SetState("SETSAIL_CHECKBOX", 1, true);
	CheckChangeSailStatus();
	
	basehull = sti(shref.Ship.Upgrades.Hull);
	hullid = basehull;
	InitModelViewer("VIEWER");
    SailsGeraldShipModelViewer(chref, shref, hullid);
}

bool CheckSailsGerald(ref chr)
{
	int	st = GetCharacterShipType(chr);
	ref	shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void IDoExit(int exitCode)
{
	if (!setcolor)
	{
		shref.SailsColorIdx = defcolor;
		shref.ShipSails.SailsColor = SailsColors[defcolor].color;
		shref.ship.upgrades.sails = defsails;
		if(CheckSailsGerald(chref) && CanSetSailsGerald(chref)) shref.ShipSails.Gerald_Name = defgerald;
		if (!geraldsails) DeleteAttribute(chref,"Features.GeraldSails");
		if (embsail != "") shref.EmblemedSails.normalTex = embsail;
	}
	else 
	{
		if (embsail != "") shref.EmblemedSails.normalTex = embsail;
		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "SETSAIL_CHECKBOX", 3, 1)) DeleteAttribute(shref,"EmblemedSails");
	}

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
    DelEventHandler("GetInterfaceTexture", "ScrollGetTexture");
    DelEventHandler("ChangeSelectScrollImage", "ChangeSelectScrollImage");
	DelEventHandler("CheckButtonChange","procCheckBoxChange");

	ExitModelViewer();

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if( sNodName == "GERALD_CHECKBOX" )
	{
		allowgerald = bBtnState;
		CheckChangeSailStatus();
	}
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
    	case "B_OK":
    		if(comName=="activate" || comName=="click")
    		{
                SetNewSailsGerald();
    		}
    	break;

    	case "B_REMOVE":
    		if(comName=="activate" || comName=="click")
    		{
                ClearSailsGerald();
    		}
    	break;

		case "SAILS_COLOR_LEFT_BUTTON":
    		if(comName=="activate" || comName=="click")
    		{
                ColorSwap(-1);
    		}
    	break;

		case "SAILS_COLOR_RIGHT_BUTTON":
    		if(comName=="activate" || comName=="click")
    		{
                ColorSwap(1);
    		}
    	break;
		
		case "GERALD_CHECKBOX":
    		if(comName=="activate" || comName=="click")
    		{
				CheckChangeSailStatus();
    			SailsGeraldShipModelViewer(chref, shref, hullid);
    		}
    	break;
		
		case "HULL_LEFT_BUTTON":
    		if(comName=="activate" || comName=="click")
    		{
                HullSwap(-1);
				CheckChangeSailStatus();
    		}
    	break;
		
		case "HULL_RIGHT_BUTTON":
    		if(comName=="activate" || comName=="click")
    		{
                HullSwap(1);
				CheckChangeSailStatus();
    		}
    	break;
		
		case "SETHULL_CHECKBOX":
    		if(comName=="activate" || comName=="click")
    		{
				CheckChangeSailStatus();
    		}
    	break;
		
		case "SETSAIL_CHECKBOX":
    		if(comName=="activate" || comName=="click")
    		{
				CheckChangeSailStatus();
    		}
    	break;
	}
}

void HullSwap(int swap)
{
	ref rShip = GetRealShip(sti(chref.ship.Type));
	int iMax = 3;
	if (CheckAttribute(rShip,"hullNums")) iMax = sti(rShip.hullNums);
	hullid = hullid + swap;
	if (swap == 1 && hullid > iMax) hullid = 1;
	if (swap == -1 && hullid < 1) hullid = iMax;
	SailsGeraldShipModelViewer(chref, shref, hullid);
}

void ColorSwap(int swap)
{
	if (swap == -1)
	{
		curcolor--;
	}
	else
	{
		curcolor++;
	}
	if (curcolor == -1 && swap == -1) curcolor = 8;
	if (curcolor == 9 && swap == 1) curcolor = 0;
	CheckChangeSailStatus();
	SailsGeraldShipModelViewer(chref, shref, hullid);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

int ScrollGetTexture()
{
	string sName = GetEventData();
	int iPicIndex = GetEventData();
	string sScrollID = GetEventData();
	int iTexture = GetTexture(sName);
	return iTexture;
}

void ChangeSelectScrollImage()
{
	string sNod = GetEventData();
	int nIdx = GetEventData();
	if (sNod == "SCROLL_GERALD")
	{
		GameInterface.SCROLL_GERALD.current = nIdx;
	}
	if (sNod == "SCROLL_SAILS")
	{
		GameInterface.SCROLL_SAILS.current = nIdx;
	}
	CheckChangeSailStatus();
	SailsGeraldShipModelViewer(chref, shref, hullid);
}

void CheckChangeSailStatus()
{
	SetFormatedText("COLOR_SAILS_CAPTION", GetConvertStrWithReplace("Variable_SailsGerald_3", "Interface.txt", "#space#", " "));
	SetFormatedText("SAILS_CAPTION", GetConvertStrWithReplace("Variable_SailsGerald_4", "Interface.txt", "#space#", " "));
	SetFormatedText("GERALD_CAPTION", GetConvertStrWithReplace("Variable_SailsGerald_5", "Interface.txt", "#space#", " "));
	SetFormatedText("SAILS_COLOR_TEXT", ""+XI_ConvertString(SailsColors[curcolor].name));
	// SetNewPicture("COLOR_PIC1", "resource\textures\ships\PlayerSails\parus_pat.tga");
	bool bNewValue = true;
	bool CanRemove = true;
	
	shref.SailsColorIdx   = curcolor;
	shref.ShipSails.SailsColor = SailsColors[curcolor].color;
	shref.ship.upgrades.sails = GetChosenType("sails");

	price = 0;
	bNewValue = false;
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "SETHULL_CHECKBOX", 3, 1) && hullid != basehull)
	{
		bNewValue = true;
		price = CalculateHullChangePrice(sti(shref.Class));
	}
	Event("GetSailTextureData","l",sti(chref.index));
		
	if (allowgerald)
	{
		if(CheckSailsGerald(chref) && CanSetSailsGerald(chref))
		{
			if (GetChosenType("gerald") != defgerald) {bNewValue = true; price = price + CalculateSailsChangePrice(sti(shref.Class)); SetFormatedText("GERALD_CURRENT", "");}
			else SetFormatedText("GERALD_CURRENT", GetConvertStrWithReplace("Variable_SailsGerald_6", "Interface.txt", "#space#", " "));
			shref.ShipSails.Gerald_Name = GetChosenType("gerald");
			chref.Features.GeraldSails = true;
		}
	}
	else DeleteAttribute(shref,"ShipSails.Gerald_Name");
	Event("GetSailTextureData","l",sti(chref.index));

	if (SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "SETSAIL_CHECKBOX", 3, 1) && GetChosenType("sails") != defsails) 
	{bNewValue = true; price = price + makeint(CalculateSailsChangePrice(sti(shref.Class))/2); SetFormatedText("SAILS_CURRENT", "");}
	if (SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "SETSAIL_CHECKBOX", 3, 1) && GetChosenType("sails") == defsails) SetFormatedText("SAILS_CURRENT", GetConvertStrWithReplace("Variable_SailsGerald_7", "Interface.txt", "#space#", " "));
	
	if (GetChosenType("color") != defcolor) {bNewValue = true; price = price + makeint(CalculateSailsChangePrice(sti(shref.Class))/3);}
	else SetFormatedText("SAILS_COLOR_TEXT", ""+XI_ConvertString(SailsColors[curcolor].name)+GetConvertStrWithReplace("Variable_SailsGerald_8", "Interface.txt", "#space#", " "));
	SetFormatedText("TOTAL_PRICE", GetConvertStrWithReplace("Variable_SailsGerald_9", "Interface.txt", "#space#", " ")+FindRussianMoneyString(price));

	if (!CheckAttribute(shref,"ShipSails.Gerald_Name")) CanRemove = false;
	SetSelectable("B_OK", bNewValue);
	SetSelectable("B_REMOVE", CanRemove);
	if (price > sti(pchar.money))
	{
		SetSelectable("B_OK", false);
		SetSelectable("B_REMOVE", false);
	}
}

int CalculateSailsChangePrice(int value)
{
	switch (value)
	{
		case 7: return 1000+drand(500);
		break;
		case 6: return 5000+drand(2500);
		break;
		case 5: return 10000+drand(5000);
		break;
		case 4: return 20000+drand(10000);
		break;
		case 3: return 35000+drand(17500);
		break;
		case 2: return 50000+drand(25000);
		break;
		case 1: return 100000+drand(50000);
		break;
	}
}

int CalculateHullChangePrice(int value)
{
	switch (value)
	{
		case 7: return 1000+drand2(500);
		break;
		case 6: return 5000+drand2(2500);
		break;
		case 5: return 10000+drand2(5000);
		break;
		case 4: return 20000+drand2(10000);
		break;
		case 3: return 35000+drand2(17500);
		break;
		case 2: return 50000+drand2(25000);
		break;
		case 1: return 100000+drand2(50000);
		break;
	}
}

string GetChosenType(string total)
{
	if (total == "gerald")
	{
		string geraldname = "";
		int nEmblem = sti(GameInterface.SCROLL_GERALD.current);
		string sattr = "pic"+(nEmblem+1);
		if(CheckSailsGerald(chref) && CanSetSailsGerald(chref)) // Warship fix 04.06.09
		{
			geraldname = GameInterface.SCROLL_GERALD.(sattr).FileName;
			return FindStringBeforeChar(geraldname,".tga");
		}
	}
	if (total == "sails")
	{
		int nSail = sti(GameInterface.SCROLL_SAILS.current);
		string sattr2 = "pic"+(nSail+1);
		for (i = 1; i <= sti(GameInterface.SCROLL_SAILS.ListSize); i++)
		{
			if (GameInterface.SCROLL_SAILS.(sattr2).FileName == "parus_"+sailsUpgrades[i-1]+".tga.tx") {
				return its(i);
			}
		}
	}
	if (total == "color")
	{
		return its(curcolor);
	}
	return "";
}

void SetNewSailsGerald()
{
	string geraldname = "";
	int nEmblem = sti(GameInterface.SCROLL_GERALD.current);
	int nSail = sti(GameInterface.SCROLL_SAILS.current);
	SetSailsColor(chref, curcolor);

	string sattr = "pic"+(nEmblem+1);
	string sattr2 = "pic"+(nSail+1);

	if (allowgerald)
	{
		if(CheckSailsGerald(chref) && CanSetSailsGerald(chref)) // Warship fix 04.06.09
		{
			geraldname = GameInterface.SCROLL_GERALD.(sattr).FileName;
			shref.ShipSails.Gerald_Name = FindStringBeforeChar(geraldname,".tga");
			Log_testInfo(shref.ShipSails.Gerald_Name);
		}
	}

	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "SETSAIL_CHECKBOX", 3, 1))
	{
		for (i = 1; i <= sti(GameInterface.SCROLL_SAILS.ListSize); i++)
		{
			if (GameInterface.SCROLL_SAILS.(sattr2).FileName == "parus_"+sailsUpgrades[i-1]+".tga.tx") {
				shref.ship.upgrades.sails = i;
				break;
			}
		}
		if (!CheckAttribute(shref, "ship.upgrades.sails") || shref.ship.upgrades.sails <= 0) {
			shref.ship.upgrades.sails = 1;
		}
		Log_testInfo(shref.ship.upgrades.sails);
		if (CheckAttribute(shref,"EmblemedSails")) DeleteAttribute(shref,"EmblemedSails");
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "SETHULL_CHECKBOX", 3, 1) && hullid != basehull) shref.ship.upgrades.hull = hullid;

	AddMoneyToCharacter(Pchar, -price);
	WaitDate("",0,0,0, 1, 30);
	setcolor = true;
	ProcessCancelExit();
}

int GetChosenTypeIndex(string total)
{
	int i;
	string varname;
	if (total == "gerald" && CheckAttribute(shref, "ShipSails.Gerald_Name"))
	{
		for (i = 1; i <= sti(GameInterface.SCROLL_GERALD.ListSize); i++)
		{
			varname = "pic"+i;
			if (GameInterface.SCROLL_GERALD.(varname).FileName == shref.ShipSails.Gerald_Name+".tga.tx") return i;
		}
	}
	if (total == "sails" && CheckAttribute(shref, "ship.upgrades.sails") && shref.ship.upgrades.sails > 0)
	{
		string sUpgrade = sailsUpgrades[sti(shref.ship.upgrades.sails)-1];
		for (i = 1; i <= sti(GameInterface.SCROLL_SAILS.ListSize); i++)
		{
			varname = "pic"+i;
			if (GameInterface.SCROLL_SAILS.(varname).FileName == "parus_"+sUpgrade+".tga.tx") 
			{
				sailfound = true;
				return i;
			}
		}
	}
	return 1;
}

void ClearSailsGerald()
{
    //AddMoneyToCharacter(Pchar, -price);
	DeleteAttribute(shref, "ShipSails.Gerald_Name");
	curgerald = "";
	defgerald = "";
	CheckChangeSailStatus();
	WaitDate("",0,0,0, 1, 30);
	CheckButton_SetState("GERALD_CHECKBOX", 1, false);
}

string sailsUpgrades[SAILS_COUNT] = {
	"common","pat","silk","silkblack","usual_1", // 5
	"usual_2","usual_3","usual_4","usual_5","usual_6", // 10
	"usual_7","usual_8","usual_9","usual_10","usual_11", // 15
	"usual_12","usual_13","usual_14","usual_15","usual_16", // 20
	"usual_17","usual_18","usual_19","usual_20","usual_21", // 25
	"usual_22","usual_23","usual_24","usual_25","usual_26", // 30
	"usual_27","usual_28","usual_29","usual_30","usual_31", // 35
	"usual_32","usual_33","sail_torn_black_pirate_1","sail_torn_black_pirate_2","sail_torn_black_pirate_3", // 40
	"sail_torn_black_pirate_4","sail_torn_black_pirate_5","sail_torn_black_pirate_6","sail_torn_black_pirate_7","sail_torn_black_pirate_8", // 45
	"sail_torn_black_pirate_9","sail_torn_black_pirate_10","sail_torn_black_pirate_11","sail_torn_black_pirate_12","sail_torn_black_pirate_13", // 50
	"sail_torn_black_pirate_14","sail_whole_black_pirate_1","sail_whole_black_pirate_2","sail_whole_black_pirate_3","sail_whole_black_pirate_4", // 55
	"sail_whole_black_pirate_5","sail_whole_black_pirate_6","sail_whole_black_pirate_7","sail_whole_black_pirate_8","sail_whole_black_pirate_9", // 60
	"sail_whole_black_pirate_10","sail_whole_black_pirate_11","sail_whole_black_pirate_12","sail_whole_black_pirate_13","sail_whole_black_pirate_14", // 65
	"sail_whole_black_pirate_15","sail_whole_black_pirate_16","sail_whole_black_pirate_17","sail_whole_white_pirate_1","sail_whole_white_pirate_2", // 70
	"sail_whole_white_pirate_3","sail_whole_white_pirate_4","sail_whole_white_pirate_5","sail_whole_white_pirate_6","sail_whole_white_pirate_7", // 75
	"sail_whole_white_pirate_8","sail_whole_white_pirate_9","sail_whole_white_pirate_10","sail_whole_white_pirate_11","sail_whole_white_pirate_12", // 80
	"sail_whole_white_pirate_13","sail_whole_white_pirate_14","sail_whole_white_pirate_15","sail_whole_white_pirate_16","sail_whole_white_pirate_17", // 85
	"sail_whole_white_pirate_18","sail_whole_white_pirate_19","sail_whole_white_pirate_20","common_torn","common_torn1", // 90
	"common_torn2"} // 95