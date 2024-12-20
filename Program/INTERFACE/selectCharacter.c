#include "interface\selectCharacter\expSlider.c"
#include "interface\selectCharacter\piratesOptions.c"
#include "interface\selectCharacter\advancedOptions.c"

#define DEFAULT_NAME "Player"
#define DEFAULT_PASS ""

bool isOkExit = false;
 int idLngFile = -1;
string sCharacterName;

bool g_bToolTipStarted = false;
int heroQty = 0;
int descWrong = 0;
string totalInfo;
string totalInfoChar;

void InitInterface(string iniName)
{
	GameInterface.title = "titleCharacterSelect";
	GameInterface.faces.current = 1;

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetNewGroupPicture("ENGLAND", "NATIONS", "England");
	SetNewGroupPicture("FRANCE", "NATIONS", "France");
	SetNewGroupPicture("SPAIN", "NATIONS", "Spain");
	SetNewGroupPicture("HOLLAND", "NATIONS", "Holland");
	SetNewGroupPicture("PIRATE", "NATIONS", "Pirate");
	// SetNewPicture("NOOB_HINT_STR", "INTERFACES\FaqPictures\NOOB.dds");

	SetMainCharacterIndex(1);

	sCharacterName = pchar.id;

	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"BLAZE", 5, 1);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"FRANCE", 5, 1);

	GameInterface.PROFILE_NAME.str = DEFAULT_NAME;
	GameInterface.PROFILE_PASS.str = DEFAULT_PASS;

	MOD_OFFICERS_RATE = 3;
	GameInterface.nodes.OFF_SLIDE.value = 0.5;
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"OFF_SLIDE", 0, 0.5);

	/*GameInterface.nodes.DEAD_SLIDE.value = makefloat(MOD_DEAD_CLEAR_TIME-100)/400.0;
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"DEAD_SLIDE", 0, stf(GameInterface.nodes.DEAD_SLIDE.value));*/
	
	GameInterface.nodes.DAMAGE_SLIDE.value = makefloat(FloatToString(((bModDamage-3.0+2.67)/2.67),2));
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"DAMAGE_SLIDE", 0, stf(GameInterface.nodes.DAMAGE_SLIDE.value));

	GameInterface.nodes.DEFENDERS_SLIDE.value = makeint(MOD_DEFENDERS_RATE);
    SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"DEFENDERS_SLIDE", 2, sti(GameInterface.nodes.DEFENDERS_SLIDE.value));

	startHeroType = sti(pchar.starttype);
    if (startHeroType < 1) startHeroType = 1; // fix
    if (startHeroType > sti(GetNewMainCharacterParam("hero_qty"))) startHeroType = sti(GetNewMainCharacterParam("hero_qty")); // fix

	SetEventHandler("exitCancel", "exitCancel", 0);
	SetEventHandler("exitOk", "exitOk", 0);
	SetEventHandler("selectEngland", "selectEngland", 0);
	SetEventHandler("selectFrance", "selectFrance", 0);
	SetEventHandler("selectSpain", "selectSpain", 0);
	SetEventHandler("selectHolland", "selectHolland", 0);
	SetEventHandler("selectPirate", "selectPirate", 0);
	SetEventHandler("confirmChangeProfileName", "confirmChangeProfileName", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);
	SetEventHandler("ShowInfo","toggleShowInfo",0);
	SetEventHandler("StopBlind_Hint","StopBlind_Hint",0);
	SetEventHandler("checkParam","clickAdvancedParam",0);
	SetEventHandler("infoParam","rightclickAdvancedParam",0);
	SetEventHandler("showPIRATESArrows","showPIRATESArrows",0);

	NullCharacter.HeroParam.HeroType = "Adventurer";

	updateAdvancedParams();
	updatePIRATES();

	SetEventHandler("noteOk","procNoteOk",0);

	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);

	setMinMaxExpRate();
	GameInterface.nodes.EXP_SLIDE.value = intToExpRate(MOD_EXP_RATE);
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"EXP_SLIDE", 0, stf(GameInterface.nodes.EXP_SLIDE.value));

	SetFormatedText("PIRATES_REMAINING", pchar.skill.FreeSPECIAL);

	//SetFormatedText("DESC_TITLE", GetConvertStrWithReplace("Variable_selectCharacter_1", "Interface.txt", "#space#", " "));
	SetFormatedText("DESC_TEXT", "Начало новой игры - это важный этап, в котором Вам предстоит настроить игру под себя. 
		\n\nИзначально всё выставлено так, чтобы игра была максимально приближена к оригиналу. 
		\n\nВсе стартовые параметры, которые Вы сейчас измените в данном меню, будут действовать до конца партии! 
		\n\n'Галочки' расставленные на чекбоксах подписанных красным текстом усложняют игру, зелёным упрощают. \n\nДля каждой опции есть описание, которое выводится при зажатии правой клавиши мыши на ней. 
		\n\nТеперь внимание! Чтобы начать игру, Вам просто нужно нажать правой кнопкой мыши по кнопке 'Соглашаюсь!' или 'Давай, поехали уже!'.");
	if (!CheckAttribute(&GameInterface, "SavePath"))
		GameInterface.SavePath = "SAVE";

	EI_CreateFrame("CHARACTER_BIG_PICTURE_BORDER",50,76,300,358); // tak from CHARACTER_BIG_PICTURE
    EI_CreateHLine("CHARACTER_BIG_PICTURE_BORDER", 54,107,296,1, 4);

    heroQty   = sti(GetNewMainCharacterParam("hero_qty"));

	SetVariable(true);

	TmpI_ShowLevelComplexity();
	TmpI_ShowOffAmount();
	SetByDefault();
	DisableEnable_CheckProcess();
	SetMusic("music_MainMenu");
}

void initParamCheckbox(ref row, bool value) {
	row.td1.icon.align = "center";
	row.td1.icon.valign = "center";
	row.td1.icon.width = 14;
	row.td1.icon.height = 14;
	row.td1.icon.group = "CHECKBUTTON_ICON";
	if (value) {
		row.td1.icon.image = "check_yes";
		row.td2.color = row.selectedColor;
	} else {
		row.td1.icon.image = "check_no";
		row.td2.color = row.normalColor;
	}
}

void SetByDefault()
{
    CheckButton_SetState("CHECK_ENCOUNTERS", iEncountersRate, true);
	CheckButton_SetState("CHECK_COUNT_ENCOUNTERS", iEncountersCountRate, true);
	CheckButton_SetState("CHECK_STEALTH_SYSTEM", iStealthSystem, true);

	if (iArcadeSails == 1)// 1 0
    {
    	CheckButton_SetState("CHECK_ARCADESAIL", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_ARCADESAIL", 2, true);
    }
	if(bAltBalanceTimeSlow)
	{
		CheckButton_SetState("CHECK_AB_TIMESLOW",1,true);
	}
	else
	{
		CheckButton_SetState("CHECK_AB_TIMESLOW",1,false);
	}
	if(bAltBalanceOffTopPerk)
	{
		CheckButton_SetState("CHECK_AB_OFFTOPPERK",1,true);
	}
	else
	{
		CheckButton_SetState("CHECK_AB_OFFTOPPERK",1,false);
	}
	if(bAltBalanceProHits)
	{
		CheckButton_SetState("CHECK_AB_PROHITS",1,true);
	}
	else
	{
		CheckButton_SetState("CHECK_AB_PROHITS",1,false);
	}
}

void IProcessFrame()
{
	TmpI_ShowOffAmount();
	//TmpI_ShowDeadAmount();
	TmpI_ShowDamageAmount();
	TmpI_ShowDefendersAmount();
	if(GetCurrentNode() == "PROFILE_NAME")
	{
		if(!CheckAttribute(&characters[GetCharacterIndex(sCharacterName)], "profile.name"))
		{
			confirmChangeProfileName();
		}

		if(characters[GetCharacterIndex(sCharacterName)].profile.name!= GameInterface.PROFILE_NAME.str)
		{
			confirmChangeProfileName();
		}
	}
	///
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 1))
	{
		iEncountersRate = 1;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 2))
	{
		iEncountersRate = 2;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 3))
	{
		iEncountersRate = 3;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_COUNT_ENCOUNTERS", 3, 1))
	{
		iEncountersCountRate = 1;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_COUNT_ENCOUNTERS", 3, 2))
	{
		iEncountersCountRate = 2;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_COUNT_ENCOUNTERS", 3, 3))
	{
		iEncountersCountRate = 3;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_STEALTH_SYSTEM", 3, 1))
	{
		bPortPermission = false;
		bBribeSoldiers = false;
		iStealthSystem = 1
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_STEALTH_SYSTEM", 3, 2))
	{
		bPortPermission = true;
		bBribeSoldiers = false;
		iStealthSystem = 2
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_STEALTH_SYSTEM", 3, 3))
	{
		bPortPermission = false;
		bBribeSoldiers = true;
		iStealthSystem = 3
	}
	////
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ARCADESAIL", 3, 1))
	{
		iArcadeSails = 1;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ARCADESAIL", 3, 2))
	{
		iArcadeSails = 0;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_AB_TIMESLOW", 3, 1))
	{
		bAltBalanceTimeSlow = true;
	}
	else
	{
		bAltBalanceTimeSlow = false;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_AB_OFFTOPPERK", 3, 1))
	{
		bAltBalanceOffTopPerk = true;
	}
	else
	{
		bAltBalanceOffTopPerk = false;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_AB_PROHITS", 3, 1))
	{
		bAltBalanceProHits = true;
	}
	else
	{
		bAltBalanceProHits = false;
	}
	updateExpSlide();
}

void exitCancel()
{
	if(MOD_BETTATESTMODE != "On") {
		ReloadMain();
	}
	pchar.perks.list.Ciras = "1";
	pchar.perks.list.GunMan = "1";
	pchar.perks.list.GunProfessional = "1";
	loadedLocation.box1.items.letter_A = 1;
	loadedLocation.box1.items.Ship_Print_1 = 1;
	loadedLocation.box1.items.Ship_Print_2 = 1;
	loadedLocation.box1.items.Ship_Print_3 = 1;
	loadedLocation.box1.items.Ship_Print_4 = 1;
	loadedLocation.box1.items.Ship_Print_5 = 1;
	loadedLocation.box1.items.Ship_Print_6 = 1;
	loadedLocation.box1.items.talisman1 = 1;
	loadedLocation.box1.items.talisman2 = 1;
	loadedLocation.box1.items.talisman3 = 1;
	loadedLocation.box1.items.talisman4 = 1;
	loadedLocation.box1.items.talisman6 = 1;
	loadedLocation.box1.items.talisman7 = 1;
	loadedLocation.box1.items.talisman8 = 1;

	loadedLocation.box2.items.letter_A = 1;
	loadedLocation.box2.items.blade38 = 1;
	loadedLocation.box2.items.blade41 = 1;
	loadedLocation.box2.items.blade28 = 1;
	loadedLocation.box2.items.cirass5 = 1;
	loadedLocation.box2.items.spyglass5 = 1;
	loadedLocation.box2.items.pistol8 = 1;
	loadedLocation.box2.items.mushket_seadevil = 1;
	loadedLocation.box2.items.mushket_spanish = 1;
	loadedLocation.box2.items.mushket_english = 1;
	loadedLocation.box2.items.mushket_france = 1;
	loadedLocation.box2.items.mushket_holland = 1;
	loadedLocation.box2.items.BackPack5 = 1;
	loadedLocation.box2.items.katar = 1;
	loadedLocation.box2.items.book4_1 = 1;
	loadedLocation.box2.items.book4_2 = 1;
	loadedLocation.box2.items.book4_3 = 1;
	loadedLocation.box2.items.book4_4 = 1;
	loadedLocation.box2.items.blade_whisper = 1;
	loadedLocation.box2.items.GunEchin = 50;
	loadedLocation.box2.items.gold = 50000000;
	ChangeItemDescribe("letter_A", "letter_B");

	if( CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{
		isOkExit = true;
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU, true);
		return;
	}
	IDoExit(RC_INTERFACE_MAIN_MENU_EXIT, true);
	//IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
	//ReturnToMainMenu();
}

void exitOk()
{
	if( !IsCorrectProfileName() )
	{
		ShowNoteText(true);
		return;
	}

	confirmChangeProfileName();

	if (!ProfileExists())
	{
		CreateProfileFolders();

        isOkExit = true;
		IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
	}
	else
	{

		ShowConfirmWindow(true);
	}
}

bool IsCorrectProfileName()
{
	int n,nLen;
	string str,sCurProfileName;

	sCurProfileName = GameInterface.PROFILE_NAME.str;
	nLen = strlen(sCurProfileName);
	if( nLen==0 ) {return false;}

	for( n=0; n<nLen; n++ )
	{
		str = GetSymbol(&sCurProfileName,n);
		if( str=="*" ) {return false;}
		if( str=="?" ) {return false;}
		if( str=="\" ) {return false;}
		if( str=="/" ) {return false;}
	}
	return true;
}

void ShowNoteText(bool bShow)
{
	if( bShow ) {
		XI_WindowDisable("MAIN_WINDOW", true);

		XI_WindowDisable("NOTE_WINDOW", false);
		XI_WindowShow("NOTE_WINDOW", true);

		SetCurrentNode("NOTE_WINDOW_OK");
	} else {
		XI_WindowDisable("MAIN_WINDOW", false);

		XI_WindowDisable("NOTE_WINDOW", true);
		XI_WindowShow("NOTE_WINDOW", false);

		SetCurrentNode("PROFILE_NAME");
	}
}

void procNoteOk()
{
	ShowNoteText(false);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
        case "LEFTCHANGE_COMPLEX":
		if(comName=="click")
		{
		    if (MOD_SKILL_ENEMY_RATE > 1)
		    {
               MOD_SKILL_ENEMY_RATE--;
            }
			setMinMaxExpRate();
            TmpI_ShowLevelComplexity();
			ResetDamageSlider();
			DisableEnable_CheckProcess();
		}
		break;

		case "LEFTCHANGE_SPECIAL":
			if(comName=="click")
			{
				downPIRATESArrows(1);
			}
			if(comName=="rclick")
			{
				downPIRATESArrows(5);
			}
		break;

		case "RIGHTCHANGE_SPECIAL":
			if(comName=="click")
			{
				upPIRATESArrows(1);
			}
			if(comName=="rclick")
			{
				upPIRATESArrows(5);
			}
		break;

		case "RIGHTCHANGE_COMPLEX":
			if(comName=="click")
			{
			    if (MOD_SKILL_ENEMY_RATE < 3)
			    {
	               MOD_SKILL_ENEMY_RATE++;
	            }
				setMinMaxExpRate();
	            TmpI_ShowLevelComplexity();
				ResetDamageSlider();
				DisableEnable_CheckProcess();
			}
		break;
		case "RANDCHARNATION":
			if(comName=="click")
			{
			    RandCharNation();
			}
		break;

		case "OFF_SLIDE":
			if(comName=="click" || comName=="leftstep" || comName=="speedleft" || comName=="rightstep" || comName=="speedright" || comName=="deactivate" || comName=="rclick")
			{
				TmpI_ShowOffAmount();
			}
		break;

		/*case "DEAD_SLIDE":
			if(comName=="click" || comName=="leftstep" || comName=="speedleft" || comName=="rightstep" || comName=="speedright" || comName=="deactivate" || comName=="rclick")
			{
				TmpI_ShowDeadAmount();
			}
		break;*/
		
		case "DAMAGE_SLIDE":
			if(comName=="click" || comName=="leftstep" || comName=="speedleft" || comName=="rightstep" || comName=="speedright" || comName=="deactivate" || comName=="rclick")
			{
				TmpI_ShowDamageAmount();
			}
		break;

		case "DEFENDERS_SLIDE":
			if(comName=="click" || comName=="leftstep" || comName=="speedleft" || comName=="rightstep" || comName=="speedright" || comName=="deactivate" || comName=="rclick")
			{
				TmpI_ShowDefendersAmount();
			}
		break;

		case "CONFIRM_WINDOW_MB_YES":

			if (comName == "click" || comName == "activate")
			{
				//DeleteProfile();
				//exitOk();
				isOkExit = true;
				IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
			}

			if (comName == "deactivate")
			{

				ShowConfirmWindow(false);
			}

			break;

		case "CONFIRM_WINDOW_MB_NO":

			if (comName == "click" || comName == "activate")
			{
				ShowConfirmWindow(false);
			}

			if (comName == "deactivate")
			{

				ShowConfirmWindow(false);
			}

			break;

		////////////////////////////////
		case "OK_BUTTON":
    		if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
    	case "CANCEL_BUTTON":
    		if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
    	case "SETUP_BUTTON":
    		if(comName=="activate" || comName=="click")
    		{
			//	 ProcessSetGameOptionsExit();
    		}
    		if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
		case "LEFTCHANGE_CHARACTER":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    	break;

    	case "RIGHTCHANGE_CHARACTER":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteRight();
    		}
    	break;

    	case "LEFTCHANGE_TYPE":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteTypeLeft();
    		}
    	break;

    	case "RIGHTCHANGE_TYPE":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteTypeRight();
    		}
    	break;

    	case "FACEPICT":
    		if(comName=="click")
    		{
          		totalInfo = GetConvertStr("hero_" + startHeroType, "HeroDescribe.txt");
				SetInfoText();
    		}
    	break;

		case "DESC_LEFT_BUTTON":
    		if(comName=="click")
    		{
          		descWrong++;
				SetTextForLulz();
    		}
			if(comName=="rclick")
    		{
          		XI_WindowShow("DESCRIPTION",false);
				XI_WindowDisable("DESCRIPTION",true);
    		}
    	break;

		case "DESC_RIGHT_BUTTON":
    		if(comName=="click")
    		{
          		descWrong++;
				SetTextForLulz();
    		}
			if(comName=="rclick")
    		{
          		XI_WindowShow("DESCRIPTION",false);
				XI_WindowDisable("DESCRIPTION",true);
    		}
    	break;
		case "ALTBALANCE_WINDOW_CLOSE":
		if(comName=="click")
		{
			ShowAltBalanceWindow(false);
		}
    	break;
		case "ADVANCED_DIFFICULTY_SETTINGS_BUTTON":
		if(comName=="click")
		{
			ShowAdvancedParamsWindow(true);
		}
		break;
		case "ADVANCED_DIFFICULTY_SETTINGS_WINDOW_CLOSE":
		if(comName=="click")
		{
			ShowAdvancedParamsWindow(false);
		}
    	break;

		case "UI_RELOAD_BUTTON":
		if(comName=="click")
		{
			IDoExit( RC_INTERFACE_ANY_EXIT, true );
			LaunchSelectCharacter();
		}
    	break;
	}

}

void ResetDamageSlider()
{
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case SAILOR_DIFFICULTY: GameInterface.nodes.DAMAGE_SLIDE.value = 0.14; break;
		case CAPTAIN_DIFFICULTY: GameInterface.nodes.DAMAGE_SLIDE.value = 0.21; break;
		case ADMIRAL_DIFFICULTY: GameInterface.nodes.DAMAGE_SLIDE.value = 0.28; break;
	}
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"DAMAGE_SLIDE", 0, stf(GameInterface.nodes.DAMAGE_SLIDE.value));
}

void SetTextForLulz()
{
	switch (makeint(descWrong/10))
	{
		case 0: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_2", "Interface.txt", "#space#", " ")+descWrong+"\n\n..."); break;
		case 1: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_3", "Interface.txt", "#space#", " ")+descWrong+"\n\nОй, слишком много вопросов будет, 10 раз неправильно"); break;
		case 2: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_4", "Interface.txt", "#space#", " ")+descWrong+"\n\nБяда, читать так и не научились, уже в 20 раз"); break;
		case 3: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_5", "Interface.txt", "#space#", " ")+descWrong+"\n\nДавай ещё раз прочитаем, 30 раз не пид...."); break;
		case 4: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_6", "Interface.txt", "#space#", " ")+descWrong+"\n\nНе, так не пойдёт, мы же не поняли, что тут написано уже в 40 раз"); break;
		case 5: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_7", "Interface.txt", "#space#", " ")+descWrong+"\n\nАга, прочитай ещё раз, уже раз 50 неверно жмакнул"); break;
		case 6: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_8", "Interface.txt", "#space#", " ")+descWrong+"\n\nНе, ваши вопросы сильно утомляют по 60 раз на дню писать"); break;
		case 7: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_9", "Interface.txt", "#space#", " ")+descWrong+"\n\nНу ладно... Так и быть, дам ещё одну попытку - прочитать внимательно ещё 70 раз"); break;
		case 8: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_10", "Interface.txt", "#space#", " ")+descWrong+"\n\nЧитать - значит быть умным, прочитать 80 раз"); break;
		case 9: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_11", "Interface.txt", "#space#", " ")+descWrong+"\n\nВсё херня, Миша, давай по новой 90 раз"); break;
		case 10: SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_12", "Interface.txt", "#space#", " ")+descWrong+"\n\nВот если бы ты прочитал всё внимательно, уже бы начал играть в СОТЫЙ РАЗ, МАТЬ ТВОЮ!"); break;
		else SetFormatedText("DESC_TEXT2",GetConvertStrWithReplace("Variable_selectCharacter_13", "Interface.txt", "#space#", " ")+descWrong+"\n\nМожет не стоит и начинать, а? У тебя явно беда с башкой, если счётчик показывает такие цифры.");
	}
}

void ShowConfirmWindow(bool show)
{
	if (show)
	{
		SetCurrentNode("CONFIRM_WINDOW_MB_NO");

		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("CONFIRM_WINDOW", false);
		XI_WindowShow("CONFIRM_WINDOW", true);
		EI_CreateFrame("CONFIRM_WINDOW_BORDERS",190,190,610,360);

	}
	else
	{
		XI_WindowDisable("CONFIRM_WINDOW", true);
		XI_WindowShow("CONFIRM_WINDOW", false);
		XI_WindowDisable("MAIN_WINDOW", false);
		SetCurrentNode("OK_BUTTON");
	}
}

void ShowAltBalanceWindow(bool show)
{
	if (show)
	{
		SetCurrentNode("ALTBALANCE_WINDOW_CLOSE");

		XI_WindowDisable("ADVANCED_DIFFICULTY_SETTINGS_WINDOW", true);
		XI_WindowDisable("ALTBALANCE_WINDOW", false);
		XI_WindowShow("ALTBALANCE_WINDOW", true);
		EI_CreateFrame("ALTBALANCE_WINDOW_BORDERS",190,190,610,360);
	}
	else
	{
		XI_WindowDisable("ALTBALANCE_WINDOW", true);
		XI_WindowShow("ALTBALANCE_WINDOW", false);
		XI_WindowDisable("ADVANCED_DIFFICULTY_SETTINGS_WINDOW", false);
		SetCurrentNode("ADVANCED_DIFFICULTY_SETTINGS_WINDOW_CLOSE");
	}
}

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
void CreateProfileFolders()
{
	String folder = GameInterface.SavePath + "\";
	folder+= pchar.profile.name;

	if (XI_CheckFolder(folder)) return;

	if(!XI_CreateFolder(folder))
		trace("Could not create profile folder");
}
//----------------------------------------------------------------------------------------------------
void DeleteProfile()
{
	String folder;

	folder = GameInterface.SavePath + "\"+ pchar.profile.name;

	int nSaveNum= 0;
	string saveName;
	int nSaveSize;

	String path = GameInterface.SavePath;
	GameInterface.SavePath = folder;

    while( SendMessage(&GameInterface,"llee",MSG_INTERFACE_SAVE_FILE_FIND,nSaveNum,&saveName,&nSaveSize)!=0 )
    {
		nSaveNum++;
		SendMessage(&GameInterface,"ls",MSG_INTERFACE_DELETE_SAVE_FILE,saveName);
    }

	GameInterface.SavePath = path;
	XI_DeleteFolder(folder);
}
//----------------------------------------------------------------------------------------------------
bool ProfileExists()
{
	String folder = GameInterface.SavePath + "\";


	folder+= pchar.profile.name;

	return (XI_CheckFolder(folder));
}
//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
void SelectNation(int iNation)
{
	/////////////////////////////////////////////////////
	string sNationPict;
	for (int i=0; i<MAX_NATIONS; i++)
	{
		sNationPict = GetNationNameByType(i);

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNationPict, 5, 0);
	}

	sNationPict = GetNationNameByType(iNation);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNationPict, 5, 1);
	/////////////////////////////////////////////////////
	NullCharacter.HeroParam.Nation = iNation;
	totalInfo = GetRPGText(Nations[iNation].Name + "_descr");
	SetInfoText();
}

void selectEngland()
{
	if (startHeroType == 1) SelectNation(ENGLAND);	//Питер Блад
	if (startHeroType == 2) SelectNation(PIRATE);	//Виспер
	if (startHeroType == 3) SelectNation(SPAIN);	//Анжелика Тич
	if (startHeroType > 3) SelectNation(ENGLAND);
}

void selectFrance()
{
    if (startHeroType == 1) SelectNation(ENGLAND);	//Питер Блад
	if (startHeroType == 2) SelectNation(PIRATE);	//Виспер
	if (startHeroType == 3) SelectNation(SPAIN);	//Анжелика Тич
	if (startHeroType > 3) SelectNation(FRANCE);
}

void selectSpain()
{
    if (startHeroType == 1) SelectNation(ENGLAND);	//Питер Блад
	if (startHeroType == 2) SelectNation(PIRATE);	//Виспер
	if (startHeroType == 3) SelectNation(SPAIN);	//Анжелика Тич
	if (startHeroType > 3) SelectNation(SPAIN);
}

void selectHolland()
{
    if (startHeroType == 1) SelectNation(ENGLAND);	//Питер Блад
	if (startHeroType == 2) SelectNation(PIRATE);	//Виспер
	if (startHeroType == 3) SelectNation(SPAIN);	//Анжелика Тич
	if (startHeroType > 3) SelectNation(HOLLAND);
}

void selectPirate()
{
	if (startHeroType == 1) SelectNation(ENGLAND);	//Питер Блад
	if (startHeroType == 2) SelectNation(PIRATE);	//Виспер
	if (startHeroType == 3) SelectNation(SPAIN);	//Анжелика Тич
	if (startHeroType > 3) SelectNation(PIRATE);
	if (startHeroType == 8) SelectNation(FRANCE);	//Нежить
}

void IDoExit(int exitCode, bool bCode)
{
	DelEventHandler("exitCancel", "exitCancel");
	DelEventHandler("exitOk", "exitOk");
	DelEventHandler("selectEngland", "selectEngland");
	DelEventHandler("selectFrance", "selectFrance");
	DelEventHandler("selectSpain", "selectSpain");
	DelEventHandler("selectHolland", "selectHolland");
	DelEventHandler("selectPirate", "selectPirate");
	DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("ShowInfo","toggleShowInfo");
	DelEventHandler("StopBlind_Hint","StopBlind_Hint");
	DelEventHandler("checkParam","clickAdvancedParam");
	DelEventHandler("infoParam","rightclickAdvancedParam");
	DelEventHandler("showPIRATESArrows","showPIRATESArrows");

	DelEventHandler("noteOk","procNoteOk");

	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("ievnt_command","ProcessCommandExecute");

	if(isOkExit == false)
	{
		EndCancelInterface(bCode);
	}
	else
	{
        MOD_EXP_RATE = floatToExpRate(stf(GameInterface.nodes.EXP_SLIDE.value));
		trace("MOD_EXP_RATE = " + MOD_EXP_RATE);

		// MOD_OFFICERS_RATE = makeint(9 - 6.0 * (1.0 - stf(GameInterface.nodes.OFF_SLIDE.value)));  // 0т 3 до 9
		MOD_OFFICERS_RATE = 9;
		trace("MOD_OFFICERS_RATE = " + MOD_OFFICERS_RATE);

		/*MOD_DEAD_CLEAR_TIME = makeint(100 + 400.0 * stf(GameInterface.nodes.DEAD_SLIDE.value));  // 0т 100 до 500
		trace("MOD_DEAD_CLEAR_TIME = " + MOD_DEAD_CLEAR_TIME);*/

		bModDamage = makefloat(3.0 - 2.67 * (1.0 - stf(GameInterface.nodes.DAMAGE_SLIDE.value)));  // 0т 0 до 5
		trace("bModDamage = " + bModDamage);
		
		MOD_DEFENDERS_RATE = round(stf(GameInterface.nodes.DEFENDERS_SLIDE.value) * 3.0)
		trace("MOD_DEFENDERS_RATE = " + MOD_DEFENDERS_RATE);
		
		if (bAltBalance == false)
		{
			bAltBalanceTimeSlow = false;
			bAltBalanceOffTopPerk = false;
			bAltBalanceProHits = false;
		}
		
		SaveStartGameParam(); // boal

		interfaceResultCommand = exitCode;
		EndCancelInterface(bCode);
	}
	if (startHeroType != 1) LAi_MethodDelay("NoFreeze",0.1);
}

void confirmChangeProfileName()
{
	PlayerProfile.name = GameInterface.PROFILE_NAME.str;
	pchar.profile.name = GameInterface.PROFILE_NAME.str;
}


void confirmChangeProfilePass()
{
	PlayerProfile.password = GameInterface.PROFILE_PASS.str;
	pchar.profile.pass = GameInterface.PROFILE_PASS.str;
	SetCurrentNode("OK_BUTTON");
}

void toggleShowInfo()
{
	string sNode = GetCurrentNode();
	ShowInfo(sNode);
}

void ShowInfo(string sNode)
{
	StopBlind_Hint();
	g_bToolTipStarted = true;
	string sHeader = "TEST";

	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	// sGroup = "none";
	// sGroupPicture = "none";
	int xx = 256;
	int yy = 256;

	switch(sNode)
	{
		case "ENGLAND":
			sHeader = XI_ConvertString("England");
			sText1 = GetRPGText("England_descr");
		break;

		case "FRANCE":
			sHeader = XI_ConvertString("France");
			sText1 = GetRPGText("France_descr");
		break;

		case "HOLLAND":
			sHeader = XI_ConvertString("Holland");
			sText1 = GetRPGText("Holland_descr");
		break;

		case "SPAIN":
			sHeader = XI_ConvertString("Spain");
			sText1 = GetRPGText("Spain_descr");
		break;

		case "PIRATE":
			sHeader = XI_ConvertString("Pirate");
			sText1 = GetRPGText("Pirate_descr");
		break;

		case "COMPLEX_TYPE":
			sHeader = XI_ConvertString("m_Complexity");
			sText1 = GetRPGText("LevelComplexity_desc");
		break;

		case "CHECK_ENCOUNTERS":
			sHeader = XI_ConvertString("EncountersRate");
			sText1 = GetRPGText("EncountersRate_desc");
		break;

		case "CHECK_COUNT_ENCOUNTERS":
			sHeader = XI_ConvertString("EncountersRateCount");
			sText1 = GetRPGText("EncountersRateCount_desc");
		break;

		case "CHECK_STEALTH_SYSTEM":
			sHeader = XI_ConvertString("StealthSystem");
			sText1 = GetRPGText("StealthSystem_desc");
		break;

		case "CHECK_ARCADESAIL":
			sHeader = XI_ConvertString("Sailing Mode");
			sText1 = GetRPGText("ArcadeSailMode_desc");
		break;

		case "CHECK_PISTOL":
			sHeader = XI_ConvertString("New Fight Mode");
			sText1 = GetRPGText("RechargePistolOnLine_desc");
		break;

		case "CHECK_HARDCORE":
			sHeader = XI_ConvertString("HardcoreGame");
			sText1 = GetRPGText("HardcoreGame_desc");
		break;

		case "CHECK_PARTITION":
			sHeader = XI_ConvertString("Partition Set");
			sText1 = GetRPGText("Partition_hint");
		break;

		case "CHECK_CREWWEIGHT":
			sHeader = XI_ConvertString("CrewWeight");
			sText1 = GetRPGText("CrewWeight_hint");
		break;

		case "CHECK_SAILS":
			sHeader = XI_ConvertString("NewSails");
			sText1 = GetRPGText("NewSails_hint");
            sPicture = "INTERFACES\FaqPictures\CHECK_SAILS.dds";
			xx = 256;
			yy = 256;
		break;

		case "CHECK_HARD_ANIMATIONS":
			sHeader = XI_ConvertString("HARD_ANIMATIONS");
			sText1 = GetRPGText("HARD_ANIMATIONS_hint");
		break;

		case "CHECK_HARD_BOSS":
			sHeader = XI_ConvertString("HARD_BOSS");
			sText1 = GetRPGText("HARD_BOSS_hint");
		break;

		case "CHECK_ENC_SEARCH_SHIP":
			sHeader = XI_ConvertString("CHECK_ENC_SEARCH_SHIP_header");
			sText1 = GetRPGText("CHECK_ENC_SEARCH_SHIP_hint");
		break;

		case "CHECK_ALTERNATIVE_BALANCE":
			sHeader = XI_ConvertString("CHECK_ALTERNATIVE_BALANCE");
			sText1 = GetRPGText("CHECK_ALTERNATIVE_BALANCE_hint");
		break;
		
		case "CHECK_AB_TIMESLOW":
			sHeader = XI_ConvertString("CHECK_AB_TIMESLOW");
			sText1 = GetRPGText("CHECK_AB_TIMESLOW_hint");
		break;
		
		case "CHECK_AB_OFFTOPPERK":
			sHeader = XI_ConvertString("CHECK_AB_OFFTOPPERK");
			sText1 = GetRPGText("CHECK_AB_OFFTOPPERK_hint");
		break;
		
		case "CHECK_AB_PROHITS":
			sHeader = XI_ConvertString("CHECK_AB_PROHITS");
			sText1 = GetRPGText("CHECK_AB_PROHITS_hint");
		break;

		case "CHECK_DIFFICULTY_WEIGHT":
			sHeader = XI_ConvertString("DifficultyWeight");
			sText1 = GetRPGText("DifficultyWeight_hint");
		break;
		
		case "CHECK_SHOOTONLYENEMY":
			sHeader = XI_ConvertString("ShootOnlyEnemy");
			sText1 = GetRPGText("ShootOnlyEnemy_hint");
		break;
		
		case "CHECK_WORLDPAUSE":
			sHeader = XI_ConvertString("WorldPause");
			sText1 = GetRPGText("WorldPause_hint");
		break;

		case "CHECK_MOD_DAMAGE":
			sHeader = XI_ConvertString("CHECK_MOD_DAMAGE");
			sText1 = XI_ConvertString("CHECK_MOD_DAMAGE_descr");
		break;

		case "CHECK_LOWERSHIP":
			sHeader = XI_ConvertString("LowerShip");
			sText1 = GetRPGText("LowerShip_hint");
		break;

		case "CHECK_PORTPERM":
			sHeader = XI_ConvertString("PortPerm");
			sText1 = GetRPGText("PortPerm_hint");
		break;

		case "CHECK_BRIBE":
			sHeader = XI_ConvertString("Bribe");
			sText1 = GetRPGText("Bribe_hint");
		break;

		case "CHECK_LOWERSELF":
			sHeader = XI_ConvertString("LowerSelf");
			sText1 = GetRPGText("LowerSelf_hint");
		break;
		
		case "CHECK_RANK_REQUIREMENT":
			sHeader = XI_ConvertString("CHECK_RANK_REQUIREMENT");
			sText1 = XI_ConvertString("CHECK_RANK_REQUIREMENT_descr");
		break;
		
		case "CHECK_HALFIMMORTALPGG":
			sHeader = XI_ConvertString("HalfImmortalPGG");
			sText1 = GetRPGText("HalfImmortalPGG_hint");
		break;

		case "CHECK_NOBONUS_SKILL_OFF":
			sHeader = XI_ConvertString("NoBonusSkillOff");
			sText1 = GetRPGText("NoBonusSkillOff_hint");
		break;
		
		case "CHECK_QUESTS_RANK":
			sHeader = XI_ConvertString("QuestsRank");
			sText1 = GetRPGText("QuestsRank_hint");
		break;

		case "EXP_SLIDE":
			sHeader = GetRPGText("EXP_SLIDE");
			sText1 = GetRPGText("EXP_SLIDE_desc");
		break;

		case "OFF_SLIDE":
			sHeader = GetRPGText("OFF_SLIDE");
			sText1 = GetRPGText("OFF_SLIDE_desc");
		break;

		/*case "DEAD_SLIDE":
			sHeader = GetRPGText("DEAD_SLIDE");
			sText1 = GetRPGText("DEAD_SLIDE_desc");
		break;*/
		
		case "DAMAGE_SLIDE":
			sHeader = GetRPGText("DAMAGE_SLIDE");
			sText1 = GetRPGText("DAMAGE_SLIDE_desc");
		break;

		case "DEFENDERS_SLIDE":
			sHeader = GetRPGText("DEFENDERS_SLIDE");
			sText1 = GetRPGText("DEFENDERS_SLIDE_desc");
		break;
	}
	//sHeader = XI_ConvertString("Nation");
	//sText1 = GetRPGText("Nation_hint");
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, xx, yy);
}

void HideInfo()
{
	if( g_bToolTipStarted ) {
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("OK_BUTTON");
	}
}

void ProcessCommandExecuteLeft()
{
    if (startHeroType > 1)
    {
       startHeroType--;
    }
    else
    {
       startHeroType = heroQty;
    }
    SetVariable(true);
}

void ProcessCommandExecuteRight()
{
    if (startHeroType < heroQty)
    {
       startHeroType++;
    }
    else
    {
       startHeroType = 1;
    }
    SetVariable(true);
}

void SetVariable(bool _init)
{
    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    SetFormatedText("HERO_NAME", GetNewMainCharacterName());

	pchar.name = GetNewMainCharacterParam("heroName_" + startHeroType);
	pchar.lastname = GetNewMainCharacterParam("heroLastname_" + startHeroType);
	pchar.sex = GetNewMainCharacterParam("sex_" + startHeroType);
	pchar.FaceID = GetNewMainCharacterFace();
	if (startHeroType < 4)	SetSelectable("RANDCHARNATION",false);	//Отключение у сюжетных ГГ функции GetConvertStrWithReplace("Variable_selectCharacter_14", "Interface.txt", "#space#", " ")
	else	SetSelectable("RANDCHARNATION",true);

    if (_init)
    {
    	NullCharacter.HeroParam.HeroType = GetNewMainCharacterType(startHeroType);
    	NullCharacter.HeroParam.nation = GetNewMainCharacterNation(startHeroType);
	}
    SetFormatedText("HERO_TYPE", XI_ConvertString(NullCharacter.HeroParam.HeroType));

    SetNewPicture("FACEPICT", "interfaces\portraits\256\face_" + GetNewMainCharacterFace() + ".tga");
    SelectNation(sti(NullCharacter.HeroParam.nation));
    totalInfo = LanguageConvertString(idLngFile, "hero_" + startHeroType);
    totalInfoChar = LanguageConvertString(idLngFile, NullCharacter.HeroParam.HeroType);
	MainChAnim = LanguageConvertString(idLngFile, "animation_" + startHeroType);
    SetInfoText();
    SetInfoChar();
    LanguageCloseFile(idLngFile);
}


string GetCharacterType(string type, int direction)
{
     switch (type)
	{
        case "Grunt":
            if (direction > 0)
            {
    	    	type = "Trader";
    	    }
    	    else
    	    {
    	        type = "SeaWolf";
    	    }
	    break;

	    case "Trader":
            if (direction > 0)
            {
    	    	type = "Fencer";
    	    }
    	    else
    	    {
    	        type = "Grunt";
    	    }
	    break;

	    case "Fencer":
            if (direction > 0)
            {
    	    	type = "Adventurer";
    	    }
    	    else
    	    {
    	        type = "Trader";
    	    }
	    break;

	    case "Adventurer":
            if (direction > 0)
            {
    	    	type = "Buccaneer";
    	    }
    	    else
    	    {
    	        type = "Fencer";
    	    }
	    break;

	    case "Buccaneer":
            if (direction > 0)
            {
    	    	type = "Agent";
    	    }
    	    else
    	    {
    	        type = "Adventurer";
    	    }
	    break;

	    case "Agent":
            if (direction > 0)
            {
    	    	type = "SeaWolf";
    	    }
    	    else
    	    {
    	        type = "Buccaneer";
    	    }
	    break;

		case "SeaWolf":
            if (direction > 0)
            {
    	    	type = "Grunt";
    	    }
    	    else
    	    {
    	        type = "Agent";
    	    }
	    break;
	}

	return type;
}

void ProcessCommandExecuteTypeLeft()
{
    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    NullCharacter.HeroParam.HeroType = GetCharacterType(NullCharacter.HeroParam.HeroType, -1);

    SetFormatedText("HERO_TYPE", XI_ConvertString(NullCharacter.HeroParam.HeroType));

    totalInfoChar = LanguageConvertString(idLngFile, NullCharacter.HeroParam.HeroType);
    SetInfoChar();
    LanguageCloseFile(idLngFile);
	updatePIRATES();
}

void RandCharNation()
{
	idLngFile = LanguageOpenFile("HeroDescribe.txt");
	switch (rand(6))
	{
		case 0:
			NullCharacter.HeroParam.HeroType = "Grunt";
		break;
		case 1:
			NullCharacter.HeroParam.HeroType = "Fencer";
		break;
		case 2:
			NullCharacter.HeroParam.HeroType = "Trader";
		break;
		case 3:
			NullCharacter.HeroParam.HeroType = "Adventurer";
		break;
		case 4:
			NullCharacter.HeroParam.HeroType = "Buccaneer";
		break;
		case 5:
			NullCharacter.HeroParam.HeroType = "SeaWolf";
		break;
		case 5:
			NullCharacter.HeroParam.HeroType = "Agent";
		break;
	}
	switch (rand(4))
	{
		case 0:
			SelectNation(0);
		break;
		case 1:
			SelectNation(1);
		break;
		case 2:
			SelectNation(2);
		break;
		case 3:
			SelectNation(3);
		break;
		case 4:
			SelectNation(4);
		break;
	}
	SetFormatedText("HERO_TYPE", XI_ConvertString(NullCharacter.HeroParam.HeroType));
	LanguageCloseFile(idLngFile);
	updatePIRATES();
}

void ProcessCommandExecuteTypeRight()
{
    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    NullCharacter.HeroParam.HeroType = GetCharacterType(NullCharacter.HeroParam.HeroType, 1);

    SetFormatedText("HERO_TYPE", XI_ConvertString(NullCharacter.HeroParam.HeroType));

    totalInfoChar = LanguageConvertString(idLngFile, NullCharacter.HeroParam.HeroType);
    SetInfoChar();
    LanguageCloseFile(idLngFile);
	updatePIRATES();
}

void SetInfoText()
{
    SetFormatedText("INFO_TEXT", totalInfo);
    SetVAligmentFormatedText("INFO_TEXT");
}

void SetInfoChar()
{
    SetFormatedText("INFO_CHAR", totalInfoChar);
    SetVAligmentFormatedText("INFO_CHAR");
}
void TmpI_ShowLevelComplexity()
{
    SetFormatedText("COMPLEX_TYPE", GetLevelComplexity(MOD_SKILL_ENEMY_RATE));
}
void TmpI_ShowOffAmount()
{
    SetFormatedText("OFF_COUNT", "" + makeint(9 - 6.0 * (1.0 - stf(GameInterface.nodes.OFF_SLIDE.value))));
}
/*void TmpI_ShowDeadAmount()
{
    SetFormatedText("DEAD_COUNT", "" + makeint(100 + 400.0 * stf(GameInterface.nodes.DEAD_SLIDE.value)));
}*/
void TmpI_ShowDamageAmount()
{
    SetFormatedText("DAMAGE_COUNT", "x" + FloatToString((makefloat(4+MOD_SKILL_ENEMY_RATE*3)/10)*makefloat(FloatToString((3.0 - 2.67 * (1.0 - stf(GameInterface.nodes.DAMAGE_SLIDE.value))),2)),2));
}
void TmpI_ShowDefendersAmount()
{
    SetFormatedText("DEFENDERS_COUNT", "" + round(stf(GameInterface.nodes.DEFENDERS_SLIDE.value) * 3.0));
}

void StopBlind_Hint()
{
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"NOOB_HINT_STR", 5, 0);
}

void DisableEnable_CheckProcess() // ugeen 2016
{
	updateAdvancedParams();
}
