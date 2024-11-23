
void InitInterface(string iniName)
{
    	GameInterface.title = "titleAttackMessage";

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	MessageInfo();

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_SALARY_EXIT);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_SALARY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
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
	    case "BUTTON":
		  if(comName=="activate" || comName=="click")
		  {
			 PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_SALARY_EXIT);
		  }
	    break;

	    /*
	    case "TO_NOTICE":
		  if(comName=="activate" || comName=="click")
		  {
			IDoExit(RC_INTERFACE_CREATE_NOTICE, false);
			return;
		  }
	    break;
	    */
	}
}


void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void MessageInfo()
{
	string sMessageFrom = "";

	CreateString(true,"Header", GetConvertStrWithReplace("Variable_AttackMessage_1", "Interface.txt", "#space#", " "), FONT_CAPTION, COLOR_NORMAL, 395,153,SCRIPT_ALIGN_CENTER,1.5);

	string sColonyName = GetConvertStrWithReplace("Variable_AttackMessage_2", "Interface.txt", "#space#", " ");
	if(CheckAttribute(PChar, "ColonyBuilding.ColonyName"))
	{
		sColonyName = PChar.ColonyBuilding.ColonyName;
	}

	bool bFirst = sti(PChar.ColonyBuilding.MessageInfo.First);

	string sTarget = PChar.ColonyBuilding.MessageInfo.Target;
	string sType = PChar.ColonyBuilding.MessageInfo.Type;
	string sEnd = PChar.ColonyBuilding.MessageInfo.End;
	int iTime = sti(PChar.ColonyBuilding.MessageInfo.Time);
	int iNation = sti(PChar.ColonyBuilding.MessageInfo.Nation);

	string sNation = GetNationNameByType(iNation) + "Gen";
	string sNationEnd = GetNationNameByType(iNation) + "Abl";
	string sNationDat = "people" + GetNationNameByType(iNation) + "Dat";

	sNation = XI_ConvertString(sNation);
	sNationEnd = XI_ConvertString(sNationEnd);
	sNationDat = XI_ConvertString(sNationDat);

	string sTexture = GetPictureForMessage(sTarget, true);
	string sPicture = GetPictureForMessage(sTarget, false);

	if(PChar.ColonyBuilding.Stage == "1" && sTarget == "Colony")
	{
		SetNewPicture("TARGET", "loading\jonny_load\city\Caiman_Town.dds");
	}
	else
	{
		SetNewGroupPicture("TARGET", sTexture, sPicture);
	}

	string sTemp = "";
	string sMessage = "";

	if(bFirst)
	{
		sMessage += GetConvertStrWithReplace("Variable_AttackMessage_3", "Interface.txt", "#space#", " ") + GetFullName(PChar) + GetConvertStrWithReplace("Variable_AttackMessage_4", "Interface.txt", "#space#", " ") + sColonyName + "'!";
	}

	sMessage += newStr();

	if(bFirst)
	{
		sPicture = "Enemy";

		switch(sTarget)
		{
			case "Colony":
				switch(sType)
				{
					case "Mutiny": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_5", "Interface.txt", "#space#", " "); break;
					case "BattleLand": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_6", "Interface.txt", "#space#", " "); break;
					case "BattleSea": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_7", "Interface.txt", "#space#", " ") + sNation + GetConvertStrWithReplace("Variable_AttackMessage_8", "Interface.txt", "#space#", " "); break;
				}
			break;

			case "Mines":
				switch(sType)
				{
					case "Mutiny": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_9", "Interface.txt", "#space#", " "); break;
					case "BattleLand": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_10", "Interface.txt", "#space#", " "); break;
					case "BattleSea": sTemp = ""; break;
				}
			break;

			case "Plantation":
				switch(sType)
				{
					case "Mutiny": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_11", "Interface.txt", "#space#", " "); break;
					case "BattleLand": sTemp = ""; break;
					case "BattleSea": sTemp = ""; break;
				}
			break;
		}
	}
	else
	{
		if(sEnd == "Good")
		{
			sPicture = "Friend";
		}
		else
		{
			sPicture = "Enemy";
		}

		switch(sTarget)
		{
			case "Colony":
				switch(sType)
				{
					case "Mutiny": if(sEnd == "Good") { sTemp = GetConvertStrWithReplace("Variable_AttackMessage_12", "Interface.txt", "#space#", " "); }else{ sTemp = GetConvertStrWithReplace("Variable_AttackMessage_13", "Interface.txt", "#space#", " "); } break;
					case "BattleLand": if(sEnd == "Good") { sTemp = GetConvertStrWithReplace("Variable_AttackMessage_14", "Interface.txt", "#space#", " "); }else{ sTemp = GetConvertStrWithReplace("Variable_AttackMessage_15", "Interface.txt", "#space#", " "); } break;
					case "BattleSea": if(sEnd == "Good") { sTemp = GetConvertStrWithReplace("Variable_AttackMessage_16", "Interface.txt", "#space#", " ") + sNationDat + "."; }else{ sTemp = GetConvertStrWithReplace("Variable_AttackMessage_17", "Interface.txt", "#space#", " ") + sNationEnd + GetConvertStrWithReplace("Variable_AttackMessage_18", "Interface.txt", "#space#", " "); } break;
				}
			break;

			case "Mines":
				switch(sType)
				{
					case "Mutiny": if(sEnd == "Good") { sTemp = GetConvertStrWithReplace("Variable_AttackMessage_19", "Interface.txt", "#space#", " "); }else{ sTemp = GetConvertStrWithReplace("Variable_AttackMessage_20", "Interface.txt", "#space#", " "); } break;
					case "BattleLand": if(sEnd == "Good") { sTemp = GetConvertStrWithReplace("Variable_AttackMessage_21", "Interface.txt", "#space#", " "); }else{ sTemp = GetConvertStrWithReplace("Variable_AttackMessage_22", "Interface.txt", "#space#", " "); } break;
				}
			break;

			case "Plantation":
				switch(sType)
				{
					case "Mutiny": if(sEnd == "Good") { sTemp = GetConvertStrWithReplace("Variable_AttackMessage_23", "Interface.txt", "#space#", " "); }else{ sTemp = GetConvertStrWithReplace("Variable_AttackMessage_24", "Interface.txt", "#space#", " "); } break;
				}
			break;
		}
	}

	SetNewGroupPicture("STATE", "RELATIONS", sPicture);

	bool bLoose = sType == "MutinyLoose" || sType == "BattleLandLoose" || sType == "BattleSeaLoose";
	if(!bFirst && bLoose)
	{
		switch(sTarget)
		{
			case "Colony":
				switch(sType)
				{
					case "MutinyLoose": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_25", "Interface.txt", "#space#", " "); break;
					case "BattleLandLoose": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_26", "Interface.txt", "#space#", " "); break;
					case "BattleSeaLoose": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_27", "Interface.txt", "#space#", " ") + sNation + GetConvertStrWithReplace("Variable_AttackMessage_28", "Interface.txt", "#space#", " "); break;
				}
			break;

			case "Mines":
				switch(sType)
				{
					case "MutinyLoose": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_29", "Interface.txt", "#space#", " "); break;
					case "BattleLandLoose": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_30", "Interface.txt", "#space#", " "); break;
				}
			break;

			case "Plantation":
				switch(sType)
				{
					case "MutinyLoose": sTemp = GetConvertStrWithReplace("Variable_AttackMessage_31", "Interface.txt", "#space#", " "); break;
				}
			break;
		}
	}

	sMessage += sTemp;

	if(bFirst)
	{
		sMessage += FindRussianDaysString(iTime) + "."
	}

	SetFormatedText("MESSAGE", sMessage);
}

string GetPictureForMessage(string sTarget, bool bTexture)
{
	int iTown = 1;
	if(CheckAttribute(PChar, "ColonyBuilding.Architecture.Town"))
	{
		iTown = sti(PChar.ColonyBuilding.Architecture.Town);
	}

	switch(sTarget)
	{
		case "Colony": 		if(bTexture) { return "COLONY_ARCHITECTURE"; 	}else{ return "Town_Type_" + iTown; } 	break;
		case "Mines": 		if(bTexture) { return GetCurrentTexture(); 	}else{ return "GoldMine"; } 		break;
		case "Plantation": 	if(bTexture) { return GetCurrentTexture(); 	}else{ return "Plantation"; } 		break;
	}

	return "none";
}

string GetCurrentTexture()
{
	if(CheckAttribute(PChar, "ColonyBuilding.CurrentIconsTexture"))
	{
		return "COLONY_BUILDINGS_" + sti(PChar.ColonyBuilding.CurrentIconsTexture);
	}

	return "COLONY_BUILDINGS_1";
}




