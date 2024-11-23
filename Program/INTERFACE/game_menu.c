
void InitInterface_gm(string iniName)
{
	GameInterface.title = "titleGameMenu";

	SetTimeScale(0.0);
	locCameraSleep(true);

	EngineLayersOffOn(true);

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","IProcessFrame",0);

	SetEventHandler("NewClick","NewClick",0);
	SetEventHandler("LoadClick","LoadClick",0);
	SetEventHandler("SaveClick","SaveClick",0);
	SetEventHandler("ResumeClick","ResumeClick",0);
	SetEventHandler("OptionsClick","OptionsClick",0);
	SetEventHandler("MainMenuClick","MainMenuClick",0);
	SetEventHandler("QuitClick","QuitClick",0);
	SetEventHandler("QuitProcess","QuitProcess",0);

	SetEventHandler("ConfirmExitClick","ConfirmExitClick",0);
	SetEventHandler("ConfirmExitCancel","ConfirmExitCancel",0);

	SetEventHandler("ConfirmMainMenuClick","ConfirmMainMenuClick",0);
	SetEventHandler("ConfirmMainMenuCancel","ConfirmMainMenuCancel",0);

	InterfaceStates.showGameMenuOnExit = true;

	if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
	{
		SetSelectable("MB_RESUME", true);
	} else {

		SetSelectable("MB_RESUME", false);
	}

	if (QuickSaveGameEnabledHardcore()) // boal 09.07.06
	{
		SetSelectable("MB_SAVE", true);
	}
	else
	{
		SetSelectable("MB_SAVE", false);
	}

	if (!CheckSaveGameEnabled())
	{
		SetSelectable("MB_SAVE", false);
	}

	string text4 = GetConvertStrWithReplace("Variable_game_menu_1", "Interface.txt", "#space#", " ");
    SetFormatedText("STARTINFO_TITLE", text4);
	SetFormatedText("VERSION_TEXT", VERSION_NUMBER1 + GetVerNum());
	string text = GetConvertStrWithReplace("Variable_game_menu_2", "Interface.txt", "#space#", " ")+pchar.model.animation + newStr() + GetConvertStrWithReplace("Variable_game_menu_2.1", "Interface.txt", "#space#", " ") + " " + bRechargePistolOnLine+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.2", "Interface.txt", "#space#", " ") + " "+bHardcoreGame+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.2.1", "Interface.txt", "#space#", " ") + " "+bPartitionSet+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.3", "Interface.txt", "#space#", " ") + " "+bSailorsWeight+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.4", "Interface.txt", "#space#", " ") + " "+bNewSails+
	newStr() + GetConvertStrWithReplace("Variable_game_menu_2.5", "Interface.txt", "#space#", " ") + " "+bHardAnimations+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.6", "Interface.txt", "#space#", " ") + " "+bHardBoss+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.7", "Interface.txt", "#space#", " ") + " "+bAltBalance;
	string text3;
	if (pchar.BaseNation == ENGLAND) text3 = GetConvertStrWithReplace("Variable_game_menu_3", "Interface.txt", "#space#", " ");
	if (pchar.BaseNation == FRANCE) text3 = GetConvertStrWithReplace("Variable_game_menu_4", "Interface.txt", "#space#", " ");
	if (pchar.BaseNation == HOLLAND) text3 = GetConvertStrWithReplace("Variable_game_menu_5", "Interface.txt", "#space#", " ");
	if (pchar.BaseNation == SPAIN) text3 = GetConvertStrWithReplace("Variable_game_menu_6", "Interface.txt", "#space#", " ");
	if (pchar.BaseNation == PIRATE) text3 = GetConvertStrWithReplace("Variable_game_menu_7", "Interface.txt", "#space#", " ");
	string text5;
	if (IsCharacterPerkOn(pchar, "Grunt")) text5 = " " + GetConvertStrWithReplace("Variable_game_menu_8", "Interface.txt", "#space#", " ");
	if (IsCharacterPerkOn(pchar, "Trader")) text5 = " " + GetConvertStrWithReplace("Variable_game_menu_9", "Interface.txt", "#space#", " ");
	if (IsCharacterPerkOn(pchar, "Fencer")) text5 = " " + GetConvertStrWithReplace("Variable_game_menu_10", "Interface.txt", "#space#", " ");
	if (IsCharacterPerkOn(pchar, "Adventurer")) text5 = " " + GetConvertStrWithReplace("Variable_game_menu_11", "Interface.txt", "#space#", " ");
	if (IsCharacterPerkOn(pchar, "Buccaneer")) text5 = " " + GetConvertStrWithReplace("Variable_game_menu_12", "Interface.txt", "#space#", " ");
	if (IsCharacterPerkOn(pchar, "Agent")) text5 = " " + GetConvertStrWithReplace("Variable_game_menu_13", "Interface.txt", "#space#", " ");
	if (IsCharacterPerkOn(pchar, "SeaWolf")) text5 = " " + GetConvertStrWithReplace("Variable_game_menu_14", "Interface.txt", "#space#", " ");
	string text2 = GetConvertStrWithReplace("Variable_game_menu_15", "Interface.txt", "#space#", " ")+text5+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.8", "Interface.txt", "#space#", " ") + " "+GetLevelComplexity(MOD_SKILL_ENEMY_RATE)+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.9", "Interface.txt", "#space#", " ") + " "+text3+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.10", "Interface.txt", "#space#", " ") + " "+MOD_EXP_RATE+" / "+MAX_EXP_RATE+ + newStr() + GetConvertStrWithReplace("Variable_game_menu_2.11", "Interface.txt", "#space#", " ") + " " + MOD_OFFICERS_RATE+newStr() + GetConvertStr("Variable_game_menu_2.12", "Interface.txt") + " " + bQuestsRank + newStr() + GetConvertStrWithReplace("Variable_game_menu_2.13", "Interface.txt", "#space#", " ") + " "+MOD_DEFENDERS_RATE+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.14", "Interface.txt", "#space#", " ") + " "+iEncountersRate;
	string text6 = GetConvertStrWithReplace("Variable_game_menu_16", "Interface.txt", "#space#", " ")+iEncountersCountRate+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.15", "Interface.txt", "#space#", " ") + " "+iArcadeSails+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.16", "Interface.txt", "#space#", " ") + " "+bPortPermission+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.17", "Interface.txt", "#space#", " ") + " "+bBribeSoldiers+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.18", "Interface.txt", "#space#", " ") + " "+bHigherSelfRate+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.19", "Interface.txt", "#space#", " ") + " "+bHigherShipRate+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.20", "Interface.txt", "#space#", " ") + " "+bNoBonusSkillOff+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.21", "Interface.txt", "#space#", " ") + " "+bHalfImmortalPGG;
	string text7 = GetConvertStrWithReplace("Variable_game_menu_17", "Interface.txt", "#space#", " ")+bShootOnlyEnemy+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.22", "Interface.txt", "#space#", " ") + " "+bFillEncyShips+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.23", "Interface.txt", "#space#", " ") + " "+bRankRequirement+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.24", "Interface.txt", "#space#", " ") + " "+bDifficultyWeight+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.25", "Interface.txt", "#space#", " ") + " "+FloatToString(makefloat((4.0+MOD_SKILL_ENEMY_RATE*3)/10.0)*bModDamage,2)+newStr() + GetConvertStrWithReplace("Variable_game_menu_2.26", "Interface.txt", "#space#", " ") + " "+bWorldAlivePause;

	SetFormatedText("STARTINFO_TEXT1", text+"\n"+text2+"\n"+text6+"\n"+text7);
	SetFormatedText("COPYRIGHTS_TEXT", PROVIDER_TXT);

	MoveNodeSpecially("LOGO",243,20,551,174);

	// if(LAi_IsBoardingProcess())	SetSelectable("MB_RESUME",false);
}


void IProcessFrame()
{
}

void ProcessCancelExit()
{
	if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
	IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
}

void IDoExit(int exitCode, bool bClear)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","IProcessFrame");

	DelEventHandler("NewClick","NewClick");
	DelEventHandler("LoadClick","LoadClick");
	DelEventHandler("SaveClick","SaveClick");
	DelEventHandler("ResumeClick","ResumeClick");
	DelEventHandler("OptionsClick","OptionsClick");
	DelEventHandler("MainMenuClick","MainMenuClick");
	DelEventHandler("QuitClick","QuitClick");
    DelEventHandler("QuitProcess","QuitProcess");

	DelEventHandler("ConfirmExitClick","ConfirmExitClick");
	DelEventHandler("ConfirmExitCancel","ConfirmExitCancel");

	DelEventHandler("ConfirmMainMenuClick","ConfirmMainMenuClick");
	DelEventHandler("ConfirmMainMenuCancel","ConfirmMainMenuCancel");

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

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "MB_NEW":

			if (comName == "click" || comName == "activate"){

				if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
				{
					ShowConfirmWindow(true);
				} else {

					NewClick();
				}
			}

			break;

		case "CONFIRM_WINDOW_MB_YES":

			if (comName == "click" || comName == "activate"){

				//ShowConfirmWindow(false);
				NewClick();
			}

			if (comName == "deactivate"){

				ShowConfirmWindow(false);
			}

			break;

		case "CONFIRM_WINDOW_MB_NO":

			if (comName == "click" || comName == "activate"){
				ShowConfirmWindow(false);
			}

			if (comName == "deactivate"){

				ShowConfirmWindow(false);
			}

			break;

		case "MB_STARTINFO_OPEN":
			if (comName == "click" || comName == "activate")
			{
				XI_WindowDisable("MAIN_WINDOW",true);
				XI_WindowShow("MAIN_WINDOW", false);
				XI_WindowDisable("STARTINFO_WINDOW",false);
				XI_WindowShow("STARTINFO_WINDOW", true);
				SetNodeUsing("FRAME_COPYRIGHTS", false);
				SetNodeUsing("CIRCLE1", true);
				SetNodeUsing("CIRCLE2", true);
				SetNodeUsing("CIRCLE3", true);
			}
			break;

		case "STARTINFO_EXIT":
			if (comName == "click" || comName == "activate")
			{
				XI_WindowDisable("MAIN_WINDOW",false);
				XI_WindowShow("MAIN_WINDOW", true);
				XI_WindowDisable("STARTINFO_WINDOW",true);
				XI_WindowShow("STARTINFO_WINDOW", false);
				SetNodeUsing("FRAME_COPYRIGHTS", true);
			}
			break;
	}

}

void NewClick()
{
	InterfaceStates.showGameMenuOnExit = false;
	IDoExit( RC_INTERFACE_DO_NEW_GAME, true);
}

void LoadClick()
{
	IDoExit( RC_INTERFACE_DO_LOAD_GAME, true);
}

void SaveClick()
{
	IDoExit( RC_INTERFACE_DO_SAVE_GAME, true);
}

void ResumeClick()
{
	IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
}

void OptionsClick()
{
	IDoExit(RC_INTERFACE_DO_OPTIONS, true);
}

void MainMenuClick()
{
	XI_WindowDisable("MAIN_WINDOW",true);
	XI_WindowDisable("CONFIRM_MAINMENU_WINDOW",false);
	XI_WindowShow("CONFIRM_MAINMENU_WINDOW", true);
	SetCurrentNode("CONFIRM_MAINMENU_NO");
}

void QuitClick()
{
	XI_WindowDisable("MAIN_WINDOW",true);
	XI_WindowDisable("CONFIRM_EXIT_WINDOW",false);
	XI_WindowShow("CONFIRM_EXIT_WINDOW", true);
	SetCurrentNode("CONFIRM_EXIT_NO");
}

void ConfirmExitClick()
{
	//PauseParticles(true); //fix вылета у форта	//видимо, очень старый комментарий, уже не актуально? в движке было идентично удалению партиклов, сейчас пофиксили, чтобы именно на паузу ставило. 
	EngineLayersOffOn(false);
	QuitProcess();
	//IDoExit(-1, false); // fix
	//ExitProgram();
}

void ConfirmExitCancel()
{
    XI_WindowDisable("CONFIRM_EXIT_WINDOW",true);
	XI_WindowShow("CONFIRM_EXIT_WINDOW",false);
	XI_WindowDisable("MAIN_WINDOW",false);
	SetCurrentNode("MB_EXITGAME");
}

void ConfirmMainMenuClick()
{
	IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
	ReloadMain();
}

void ConfirmMainMenuCancel()
{
    XI_WindowDisable("CONFIRM_MAINMENU_WINDOW",true);
	XI_WindowShow("CONFIRM_MAINMENU_WINDOW",false);
	XI_WindowDisable("MAIN_WINDOW",false);
	SetCurrentNode("MB_MAINMENU");
}

void ShowConfirmWindow(bool show)
{
	if (show){

		SetCurrentNode("CONFIRM_WINDOW_MB_NO");

		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("CONFIRM_WINDOW", false);
		XI_WindowShow("CONFIRM_WINDOW", true);
		EI_CreateFrame("CONFIRM_WINDOW_BORDER",190,190,610,360);

	} else {

		XI_WindowDisable("CONFIRM_WINDOW", true);
		XI_WindowShow("CONFIRM_WINDOW", false);
		XI_WindowDisable("MAIN_WINDOW", false);

		if(GetSelectable("MB_RESUME"))
			SetCurrentNode("MB_RESUME");
		else
			SetCurrentNode("MB_NEW");
	}
}

void QuitProcess()
{
    // вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	IDoExit(-1, false);
	ExitProgram();
}
