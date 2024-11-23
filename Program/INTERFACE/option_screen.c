#include "interface\option_screen_simple_option.c"

int g_nCurControlsMode = -1;
int g_ControlsLngFile = -1;
bool blockkey = true;
string curkey = "";
bool g_bToolTipStarted = false;
int OptionsTab = 1;

float 	fHUDRatio 	= 1.0;
float 	newBase 	= stf(screenscaling);

#define BI_LOW_RATIO 	0.25
#define BI_HI_RATIO 	4.0
#define BI_DIF_RATIO 	3.75

float CalcHUDBase(float fSlider, float MyScreen)
{
    float fRes = BI_DIF_RATIO * fSlider;
    float curBase = MyScreen / (BI_LOW_RATIO + fRes);

    return curBase;
}

float CalcHUDSlider(float fRatio)
{
    float fRes = fRatio - BI_LOW_RATIO;
    fRes /= BI_DIF_RATIO;

    return fRes;
}

float roundFloat(float value) {
	float newValue = stf(round(value * 100.0)) / 100.0
	float ostatok = sti(newValue * 100) % 5 / 100.0
	return newValue - ostatok
}

void InitInterface(string iniName)
{
	g_nCurControlsMode = -1;
	GameInterface.title = "titleOptions";
	g_ControlsLngFile = LanguageOpenFile("ControlsNames.txt");

	if( CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true) {
		LoadGameOptions();
	} else {
		DeleteAttribute( &PlayerProfile, "name" );
		LoadGameOptions();
	}

	IReadVariableBeforeInit();
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	IReadVariableAfterInit();

	SetControlsTabMode(1);

	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);  // boal
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("eventBtnAction","procBtnAction",0);
	SetEventHandler("eventKeyChange","procKeyChange",0);

	SetEventHandler("CheckButtonChange","procCheckBoxChange",0);
	SetEventHandler("eSlideChange","procSlideChange",0);

	SetEventHandler("evntKeyChoose","procKeyChoose",0);
	SetEventHandler("ShowInfo", "ShowInfo", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);

	SetEventHandler("checkParam","clickSimpleOption",0);
	SetEventHandler("infoParam","rightclickSimpleOption",0);

	SetEventHandler("evFaderFrame","FaderFrame",0);

	SetFormatedText("TEXT_NATIONS_PIC_SETTINGS", GetConvertStrWithReplace("Variable_option_screen_1", "Interface.txt", "#space#", " "));
	SetFormatedText("TEXT_VISUAL_CIRASS_PIC_SETTINGS", GetConvertStrWithReplace("Variable_option_screen_2", "Interface.txt", "#space#", " "));
	SetFormatedText("TEXT_FONT_QUESTBOOK_PIC_SETTINGS", GetConvertStrWithReplace("Variable_option_screen_3", "Interface.txt", "#space#", " "));
	SetFormatedText("TEXT_PARTICLES_PIC_SETTINGS", GetConvertStrWithReplace("Variable_option_screen_4", "Interface.txt", "#space#", " "));
	SetFormatedText("TEXT_ALT_GUN_SOUNDS_SETTINGS", GetConvertStrWithReplace("Variable_option_screen_5", "Interface.txt", "#space#", " "));

	aref ar; makearef(ar,objControlsState.key_codes);
	SendMessage(&GameInterface,"lsla",MSG_INTERFACE_MSG_TO_NODE,"KEY_CHOOSER", 0,ar);

	float ftmp1 = -1.0;
	float ftmp2 = -1.0;
	float ftmp3 = -1.0;
	SendMessage(&sound,"leee",MSG_SOUND_GET_MASTER_VOLUME,&ftmp1,&ftmp2,&ftmp3);
	if( ftmp1==-1.0 && ftmp2==-1.0 && ftmp3==-1.0 )
	{
		SetSelectable("MUSIC_SLIDE",false);
		SetSelectable("SOUND_SLIDE",false);
		SetSelectable("DIALOG_SLIDE",false);
	}
	//Set max perspective string (in case constants/ calc changes in AICameras.c)
	float fCamPersp = DEFAULT_CAM_PERSP + (1 / DEFAULT_CAM_PERSP_DEN);
    string sMsg = "#"+ FloatToString(fCamPersp, 3);
    //PerspMax is 17 in coll.
    SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 17, sMsg);
    fCamPersp = DEFAULT_LCAM_PERSP + (1 / DEFAULT_LCAM_PERSP_DEN);
    sMsg = "#"+ FloatToString(fCamPersp, 3);
    //PerspMax2 is 21 in coll.
    SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 21, sMsg);
    float fCamRad = CalcLandRadiusNew();
    sMsg = "#"+ FloatToString(fCamRad, 1);
    //CamRadMax is 24 in coll.
    SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 24, sMsg);

	fHUDRatio = stf(Render.screen_y) / screenscaling;
	float sl = CalcHUDSlider(fHUDRatio);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE, "HUD_SLIDE", 0, sl);
	GameInterface.nodes.hud_slide.value = sl;
    newBase = CalcHUDBase(sl, stf(Render.screen_y));
	
	OptionsTab = sti(InterfaceStates.menu);
	SetOptionsWindow(OptionsTab);
	ChangeVideoColor();
	ChangeSeaDetail();
	ChangePerspDetail();
	ChangePersp2Detail();
	ChangeRadDetail();
	ChangeSoundSetting();
	ChangeMouseSensitivity();
	ChangeHUDDetail();
	ChangeGrassDistanceLand();
	ChangeGrassDistanceSea();
	ChangeGrassCountLand();
	ChangeGrassCountSea();
}

void ProcessCancelExit()
{
	LoadGameOptions();
	ProcessExit();
}

void ProcessOkExit()
{
	screenscaling = newBase;

	SaveGameOptions();
	ProcessExit();
	Event("eventChangeOption");

	SetSeaGridStep(stf(InterfaceStates.SeaDetails));// change sea settings
	SetPerspectiveSettings();//#20171223-01 Camera perspective option
	SetPerspective2Settings();//#20190815-01
	if (sti(InterfaceStates.ShowExpLogs)==0)
	{
		objLandInterface.textinfo.EXP1.text = "";
		objLandInterface.textinfo.EXP2.text = "";
		objLandInterface.textinfo.EXP3.text = "";
		objLandInterface.textinfo.EXP4.text = "";
		objLandInterface.textinfo.EXP5.text = "";
	}
}

void ProcessExit()
{

	if(sti(InterfaceStates.EnabledCMControls) == 1)
	{
		CI_CreateAndSetControls( "Sailing3Pers", "BICommandsActivate", CI_GetKeyCode("VK_MBUTTON"), 0, true );
		CI_CreateAndSetControls( "PrimaryLand", "LICommandsActivate", CI_GetKeyCode("VK_MBUTTON"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsConfirm", CI_GetKeyCode("VK_LBUTTON"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsCancel", CI_GetKeyCode("VK_RBUTTON"), 0, false );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsLeft", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsRight", CI_GetKeyCode("VK_MWHEEL_UP"), 0, true );
	}
	else
	{
		CI_CreateAndSetControls( "Sailing3Pers", "BICommandsActivate", CI_GetKeyCode("VK_RETURN"), 0, true );
		CI_CreateAndSetControls( "PrimaryLand", "LICommandsActivate", CI_GetKeyCode("VK_RETURN"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsConfirm", CI_GetKeyCode("VK_RETURN"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsCancel", CI_GetKeyCode("VK_ESCAPE"), 0, false );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsLeft", CI_GetKeyCode("VK_LEFT"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsRight", CI_GetKeyCode("VK_RIGHT"), 0, true );
	}

	if( CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true) {
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}

	IDoExit(RC_INTERFACE_OPTIONSCREEN_EXIT);
	if( !CheckAttribute(&InterfaceStates,"InstantExit") || sti(InterfaceStates.InstantExit)==false ) {
		ReturnToMainMenu();
	}
}

void IDoExit(int exitCode)
{
	DelEventHandler("evntKeyChoose","procKeyChoose");
	DelEventHandler("eSlideChange","procSlideChange");
	DelEventHandler("CheckButtonChange","procCheckBoxChange");

	DelEventHandler("eventKeyChange","procKeyChange");
	DelEventHandler("eventBtnAction","procBtnAction");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ShowInfo", "ShowInfo");
	DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("evFaderFrame","FaderFrame");
	DelEventHandler("InterfaceBreak","ProcessCancelExit");  // boal

	DelEventHandler("checkParam","clickSimpleOption");
	DelEventHandler("infoParam","rightclickSimpleOption");
	LanguageCloseFile( g_ControlsLngFile );

	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"InstantExit") && sti(InterfaceStates.InstantExit)==true ) {
		EndCancelInterface(true);
	} else {
		EndCancelInterface(false);
	}
	ControlsMakeInvert();
	//#20200519-02
	if(bSeaActive) {
        BattleInterface.ShifInfoVisible = InterfaceStates.enabledshipmarks;
        BattleInterface.battleborder.used = InterfaceStates.ShowBattleMode;
	}

}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;

	switch( nMode )
	{
	case 1: // море от первого лица
		sPic1 = "TabSelected";
		nColor1 = argb(255,255,255,255);
	break;
	case 2: // режим путешествий на земле
		sPic2 = "TabSelected";
		nColor2 = argb(255,255,255,255);
	break;
	case 3: // море от 3-го лица
		sPic3 = "TabSelected";
		nColor3 = argb(255,255,255,255);
	break;
	case 4: // режим боя на земле
		sPic4 = "TabSelected";
		nColor4 = argb(255,255,255,255);
	break;
	}

	SetNewGroupPicture("TABBTN_SAILING_1ST", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_PRIMARY_LAND", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_SAILING_3RD", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_FIGHT_MODE", "TABS", sPic4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SAILING_1ST", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_PRIMARY_LAND", 8,0,nColor2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SAILING_3RD", 8,0,nColor3);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_FIGHT_MODE", 8,0,nColor4);

	FillControlsList(nMode);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if( sNodName == "TABBTN_SAILING_1ST" ) {
		SetControlsTabMode( 1 );
		return;
	}
	if( sNodName == "TABBTN_PRIMARY_LAND" ) {
		SetControlsTabMode( 2 );
		return;
	}
	if( sNodName == "TABBTN_SAILING_3RD" ) {
		SetControlsTabMode( 3 );
		return;
	}
	if( sNodName == "TABBTN_FIGHT_MODE" ) {
		SetControlsTabMode( 4 );
		return;
	}
	
	if( sNodName == "TABBTN_GRAPHICS" ) {
		SetOptionsWindow( 1 );
		return;
	}
	if( sNodName == "TABBTN_SOUND" ) {
		SetOptionsWindow( 2 );
		return;
	}
	if( sNodName == "TABBTN_CONTROLS" ) {
		SetOptionsWindow( 3 );
		return;
	}
	if( sNodName == "TABBTN_OPTIONS" ) {
		SetOptionsWindow( 4 );
		return;
	}
}

void SetOptionsWindow(int num)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;

	switch( num )
	{
	case 1: // море от первого лица
		sPic1 = "TabSelected";
		nColor1 = argb(255,255,255,255);
	break;
	case 2: // режим путешествий на земле
		sPic2 = "TabSelected";
		nColor2 = argb(255,255,255,255);
	break;
	case 3: // море от 3-го лица
		sPic3 = "TabSelected";
		nColor3 = argb(255,255,255,255);
	break;
	case 4: // режим боя на земле
		sPic4 = "TabSelected";
		nColor4 = argb(255,255,255,255);
	break;
	}

	SetNewGroupPicture("TABBTN_GRAPHICS", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_SOUND", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_CONTROLS", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_OPTIONS", "TABS", sPic4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_GRAPHICS", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SOUND", 8,0,nColor2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_CONTROLS", 8,0,nColor3);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_OPTIONS", 8,0,nColor4);
	
	XI_WindowDisable("GRAPHICS_WINDOW",true);
	XI_WindowDisable("SOUNDS_WINDOW",true);
	XI_WindowDisable("CONTROLS_WINDOW",true);
	XI_WindowDisable("OTHERS_WINDOW",true);
	XI_WindowShow("GRAPHICS_WINDOW",false);
	XI_WindowShow("SOUNDS_WINDOW",false);
	XI_WindowShow("CONTROLS_WINDOW",false);
	XI_WindowShow("OTHERS_WINDOW",false);
	switch (num)
	{
		case 1:
			XI_WindowShow("GRAPHICS_WINDOW",true);
			XI_WindowDisable("GRAPHICS_WINDOW",false);
		break;
		case 2:
			XI_WindowShow("SOUNDS_WINDOW",true);
			XI_WindowDisable("SOUNDS_WINDOW",false);
		break;
		case 3:
			XI_WindowShow("CONTROLS_WINDOW",true);
			XI_WindowDisable("CONTROLS_WINDOW",false);
		break;
		case 4:
			XI_WindowShow("OTHERS_WINDOW",true);
			XI_WindowDisable("OTHERS_WINDOW",false);
		break;
	}
	InterfaceStates.menu = num;
}

void procBtnAction()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if( sNodName == "BTN_OK" ) {
		if( iComIndex==ACTION_ACTIVATE || iComIndex==ACTION_MOUSECLICK ) {
			ProcessOkExit();
		}
		return;
	}
	if( sNodName == "BTN_CONTROLS_DEFAULT" ) {
		RestoreDefaultKeys(0);
		return;
	}

	if( sNodName == "BTN_CONTROLS_DEFAULT_GPK" ) {
		RestoreDefaultKeys(1);
		return;
	}
	
	if( sNodName == "HUD_SCALE_DEFAULT" ) {
		GameInterface.nodes.hud_slide.value = CalcHUDSlider(roundFloat(stf(Render.screen_y) / 900.0));
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE, "HUD_SLIDE", 0, stf(GameInterface.nodes.hud_slide.value));
		ChangeHUDDetail();
		return;
	}
	
	if( sNodName == "HUD_DIALOG_LEFT_BUTTON" ) {
		ChangeDialogStyle(false);
		return;
	}
	
	if( sNodName == "HUD_DIALOG_RIGHT_BUTTON" ) {
		ChangeDialogStyle(true);
		return;
	}
}

void IReadVariableBeforeInit()
{
	GetSoundOptionsData();
	GetMouseOptionsData();
	GetVideoOptionsData();
}

void IReadVariableAfterInit()
{
	GetHerbOptionsData();
	GetControlsStatesData();

	GetFlagAllOptionsData();
	GetVisualCirassOptionsData();
	GetAltFontOptionsData();
	GetBombsParticlesOptionsData();
	
	if( CheckAttribute(&InterfaceStates,"DialogStyle") ) SetFormatedText("HUD_DIALOG_TEXT", InterfaceStates.DialogStyle);
	else 
	{
		InterfaceStates.DialogStyle = 1;
		SetFormatedText("HUD_DIALOG_TEXT", InterfaceStates.DialogStyle);
	}

	if( !CheckAttribute(&InterfaceStates,"RegionsWorldmap") ) 		InterfaceStates.RegionsWorldmap = 0;
	if( !CheckAttribute(&InterfaceStates,"SimpleSea") ) 			InterfaceStates.SimpleSea = 0;
	if( !CheckAttribute(&InterfaceStates,"EnabledShipMarks") ) 		InterfaceStates.EnabledShipMarks = 1;//default
	if( !CheckAttribute(&InterfaceStates,"EnabledAutoSaveMode") ) 	InterfaceStates.EnabledAutoSaveMode = 1;//default
	if( !CheckAttribute(&InterfaceStates,"ShowBattleMode") ) 		InterfaceStates.ShowBattleMode = 0;
	if( !CheckAttribute(&InterfaceStates,"SpyglassTextures") ) 		InterfaceStates.SpyglassTextures = 0;
	if( !CheckAttribute(&InterfaceStates,"HUDStyle") )				InterfaceStates.HUDStyle = 0;
	if( !CheckAttribute(&InterfaceStates,"CannonsHUD") ) 			InterfaceStates.CannonsHUD = 0;
	if( !CheckAttribute(&InterfaceStates,"ShowBoardMode") ) 		InterfaceStates.ShowBoardMode = 0;
	if( !CheckAttribute(&InterfaceStates,"EnableSailors") )			InterfaceStates.EnableSailors = 0;
	if( !CheckAttribute(&InterfaceStates,"CharVoice") ) 			InterfaceStates.CharVoice = 0;
	if( !CheckAttribute(&InterfaceStates,"IslandLoader") ) 			InterfaceStates.IslandLoader = 0;
	if( !CheckAttribute(&InterfaceStates,"AltIntIcons") ) 			InterfaceStates.AltIntIcons = 0;
	if( !CheckAttribute(&InterfaceStates,"EnabledQuestsMarks") ) 	InterfaceStates.EnabledQuestsMarks = 1;//default
	if( !CheckAttribute(&InterfaceStates,"EnabledFXMarks") ) 		InterfaceStates.EnabledFXMarks = 1;//default
	if( !CheckAttribute(&InterfaceStates,"EnabledCMControls") ) 	InterfaceStates.EnabledCMControls = 0;
	if( !CheckAttribute(&InterfaceStates,"EnabledOldStore") ) 		InterfaceStates.EnabledOldStore = 0;
	if( !CheckAttribute(&InterfaceStates,"EnabledAltSoundsGun") ) 	InterfaceStates.EnabledAltSoundsGun = 0;
	if( !CheckAttribute(&InterfaceStates,"ShowExpLogs") ) 			InterfaceStates.ShowExpLogs = 0;
	FillSimpleOptionsTable();
/*
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SIMPLESEA_CHECKBOX", 2, 1, sti(InterfaceStates.SimpleSea) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SHIPMARK_CHECKBOX", 2, 1, sti(InterfaceStates.EnabledShipMarks) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"AUTOSAVE_CHECKBOX", 2, 1, sti(InterfaceStates.EnabledAutoSaveMode) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"BATTLE_MODE_CHECKBOX", 2, 1, sti(InterfaceStates.ShowBattleMode) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SPYGLASSTEX_CHECKBOX", 2, 1, sti(InterfaceStates.SpyglassTextures) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"HUDStyle_CHECKBOX", 2, 1, sti(InterfaceStates.HUDStyle) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CannonsHUD_CHECKBOX", 2, 1, sti(InterfaceStates.CannonsHUD) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"BOARD_MODE_CHECKBOX", 2, 1, sti(InterfaceStates.ShowBoardMode) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SAILORS_CHECKBOX", 2, 1, sti(InterfaceStates.EnableSailors) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHAR_VOICE_CHECKBOX", 2, 1, sti(InterfaceStates.CharVoice) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ISLAND_LOADER_CHECKBOX", 2, 1, sti(InterfaceStates.IslandLoader) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALT_INT_ICONS_CHECKBOX", 2, 1, sti(InterfaceStates.AltIntIcons) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"QUESTMARK_CHECKBOX", 2, 1, sti(InterfaceStates.EnabledQuestsMarks) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FXMARK_CHECKBOX", 2, 1, sti(InterfaceStates.EnabledFXMarks) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CM_CONTROLS_CHECKBOX", 2, 1, sti(InterfaceStates.EnabledCMControls) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"GOOD_OLD_STORE_CHECKBOX", 2, 1, sti(InterfaceStates.EnabledOldStore) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALT_GUN_SOUNDS_CHECKBOX", 2, 1, sti(InterfaceStates.EnabledAltSoundsGun) );
*/
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if( sNodName == "HERB_CHECKBOX" )
	{
		if( bBtnState==true ) {
			switch( nBtnIndex ) {
			case 1: iGrassQuality=3; break;
			case 2: iGrassQuality=2; break;
			case 3: iGrassQuality=1; break;
			case 4: iGrassQuality=0; break;
			}
		}
		return;
	}
	if( sNodName == "ALWAYS_RUN_CHECKBOX" )		SetAlwaysRun( bBtnState );
	if( sNodName == "INVERT_MOUSE_CHECKBOX" )	InterfaceStates.InvertCameras = bBtnState;
/*
	if( sNodName == "SIMPLESEA_CHECKBOX" )		InterfaceStates.SimpleSea = bBtnState;
	if( sNodName == "SHIPMARK_CHECKBOX" )		InterfaceStates.EnabledShipMarks = bBtnState;
	if( sNodName == "AUTOSAVE_CHECKBOX" )		InterfaceStates.EnabledAutoSaveMode = bBtnState;
	if( sNodName == "BATTLE_MODE_CHECKBOX" )	InterfaceStates.ShowBattleMode = bBtnState;
	if( sNodName == "SPYGLASSTEX_CHECKBOX" )	InterfaceStates.SpyglassTextures = bBtnState;
	if( sNodName == "HUDStyle_CHECKBOX" )		InterfaceStates.HUDStyle = bBtnState;
	if( sNodName == "CannonsHUD_CHECKBOX" )		InterfaceStates.CannonsHUD = bBtnState;
	if( sNodName == "BOARD_MODE_CHECKBOX")		InterfaceStates.ShowBoardMode = bBtnState;
	if( sNodName == "SAILORS_CHECKBOX")			InterfaceStates.EnableSailors = bBtnState;
	if( sNodName == "CHAR_VOICE_CHECKBOX")		InterfaceStates.CharVoice = bBtnState;
	if( sNodName == "ISLAND_LOADER_CHECKBOX" )	InterfaceStates.IslandLoader = bBtnState;
	if( sNodName == "ALT_INT_ICONS_CHECKBOX" )	InterfaceStates.AltIntIcons = bBtnState;
	if( sNodName == "QUESTMARK_CHECKBOX" )		InterfaceStates.EnabledQuestsMarks = bBtnState;
	if( sNodName == "FXMARK_CHECKBOX" )			InterfaceStates.EnabledFXMarks = bBtnState;
	if( sNodName == "CM_CONTROLS_CHECKBOX" )	InterfaceStates.EnabledCMControls = bBtnState;
	if( sNodName == "GOOD_OLD_STORE_CHECKBOX" )	InterfaceStates.EnabledOldStore = bBtnState;
	if( sNodName == "ALT_GUN_SOUNDS_CHECKBOX" )	InterfaceStates.EnabledAltSoundsGun = bBtnState;
*/
	if( sNodName == "FLAGALLWDM_CHECKBOX" )
	{
		if( bBtnState == true )
		{
			switch( nBtnIndex )
			{
				case 1:
					iFlagAllWdm=2;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 2, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 3, false );
				break;
				case 2:
					iFlagAllWdm=1;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 1, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 3, false );
				break;
				case 3:
					iFlagAllWdm=0;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 1, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 2, false );
				break;
			}
		}
		return;
	}

	if( sNodName == "VISUAL_CIRASS_CHECKBOX" )
	{
		InterfaceStates.VISUAL_CIRASS = 0

		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "VISUAL_CIRASS_CHECKBOX", 3, 1))
		{
			InterfaceStates.VISUAL_CIRASS = sti(InterfaceStates.VISUAL_CIRASS)+1;
		}
		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "VISUAL_CIRASS_CHECKBOX", 3, 2))
		{
			InterfaceStates.VISUAL_CIRASS = sti(InterfaceStates.VISUAL_CIRASS)+3;
		}
		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "VISUAL_CIRASS_CHECKBOX", 3, 3))
		{
			InterfaceStates.VISUAL_CIRASS = sti(InterfaceStates.VISUAL_CIRASS)+5;
		}
		//log_testinfo(InterfaceStates.VISUAL_CIRASS);
		return;
	}

	if( sNodName == "ALTFONT_CHECKBOX" )
	{
		if( bBtnState == true )
		{
			switch( nBtnIndex )
			{
				case 1:
					InterfaceStates.AltFont=0;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 2, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 3, false );
				break;
				case 2:
					InterfaceStates.AltFont=1;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 1, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 3, false );
				break;
				case 3:
					InterfaceStates.AltFont=2;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 1, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 2, false );
				break;
			}
		}
		return;
	}

	if( sNodName == "PARTICLES_CHECKBOX" )
	{
		if( bBtnState == true )
		{
			switch( nBtnIndex )
			{
				case 1:
					InterfaceStates.BombsParticles=0;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"PARTICLES_CHECKBOX", 2, 2, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"PARTICLES_CHECKBOX", 2, 3, false );
				break;
				case 2:
					InterfaceStates.BombsParticles=1;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"PARTICLES_CHECKBOX", 2, 1, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"PARTICLES_CHECKBOX", 2, 3, false );
				break;
				case 3:
					InterfaceStates.BombsParticles=2;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"PARTICLES_CHECKBOX", 2, 1, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"PARTICLES_CHECKBOX", 2, 2, false );
				break;
			}
		}
		return;
	}
}

void procSlideChange()
{
	string sNodeName = GetEventData();
	int nVal = GetEventData();
	float fVal = GetEventData();

	if( sNodeName=="GAMMA_SLIDE" || sNodeName=="BRIGHT_SLIDE" || sNodeName=="CONTRAST_SLIDE" ) {
		ChangeVideoColor();
		return;
	}
	if( sNodeName == "SEA_DETAILS_SLIDE" ) {
		ChangeSeaDetail();
		return;
	}
	if( sNodeName == "HERB_LAND_DISTANCE_SLIDE" ) {
		ChangeGrassDistanceLand();
		return;
	}
	if( sNodeName == "HERB_SEA_DISTANCE_SLIDE" ) {
		ChangeGrassDistanceSea();
		return;
	}
	if( sNodeName == "HERB_QUANTITY_SLIDE" ) {
		ChangeGrassCountLand();
		return;
	}
	if( sNodeName == "HERB_TRANSP_SLIDE" ) {
		ChangeGrassCountSea();
		return;
	}
	//#20171223-01 Camera perspective option
	if( sNodeName == "CAM_PERSP_SLIDE" ) {
		ChangePerspDetail();
		return;
	}
	//#20190815-01
	if( sNodeName == "CAM_PERSP_SLIDE2" ) {
		ChangePersp2Detail();
		return;
	}
	if( sNodeName == "CAM_RAD_SLIDE" ) {
		ChangeRadDetail();
		return;
	}
	if( sNodeName == "HUD_SLIDE" ) {
		ChangeHUDDetail();
		return;
	}
	if( sNodeName=="MUSIC_SLIDE" || sNodeName=="SOUND_SLIDE" || sNodeName=="DIALOG_SLIDE" ) {
		ChangeSoundSetting();
		return;
	}
	if( sNodeName=="VMOUSE_SENSITIVITY_SLIDE" || sNodeName=="HMOUSE_SENSITIVITY_SLIDE" ) {
		ChangeMouseSensitivity();
	}
}

void ChangeMouseSensitivity()
{
	InterfaceStates.mouse.x_sens = stf(GameInterface.nodes.hmouse_sensitivity_slide.value);
	InterfaceStates.mouse.y_sens = stf(GameInterface.nodes.vmouse_sensitivity_slide.value);
	SetRealMouseSensitivity();
	SetFormatedText("HMOUSE_SENSITIVITY_TEXT", its(makeint(makefloat(InterfaceStates.mouse.x_sens)*100)));
	SetFormatedText("VMOUSE_SENSITIVITY_TEXT", its(makeint(makefloat(InterfaceStates.mouse.y_sens)*100)));
}

void ChangeVideoColor()
{
	float fCurContrast = stf(GameInterface.nodes.contrast_slide.value);
	float fCurGamma = stf(GameInterface.nodes.GAMMA_SLIDE.value);
	float fCurBright = stf(GameInterface.nodes.BRIGHT_SLIDE.value);

	float fContrast = ConvertContrast(fCurContrast,false);
	float fGamma = ConvertGamma(fCurGamma,false);
	float fBright = ConvertBright(fCurBright,false);

	if( !CheckAttribute(&InterfaceStates,"video.contrast") ||
		(stf(InterfaceStates.video.contrast)!=fContrast) ||
		(stf(InterfaceStates.video.gamma)!=fGamma) ||
		(stf(InterfaceStates.video.brightness)!=fBright) ) {
			InterfaceStates.video.contrast = fContrast;
			InterfaceStates.video.gamma = fGamma;
			InterfaceStates.video.brightness = fBright;
			XI_SetColorCorrection(fContrast,fGamma,fBright);
	}
	SetFormatedText("GAMMA_TEXT", its(makeint(fCurGamma*100)));
	SetFormatedText("BRIGHTNESS_TEXT", its(makeint(fCurBright*100)));
	SetFormatedText("CONTRAST_TEXT", its(makeint(fCurContrast*100)));
}

void ChangeSeaDetail()
{
	float fCurSeaDetail = stf(GameInterface.nodes.sea_details_slide.value);
	float fSeaDetail = ConvertSeaDetails(fCurSeaDetail,false);
	if( !CheckAttribute(&InterfaceStates,"SeaDetails") ||
		(stf(InterfaceStates.SeaDetails)!=fSeaDetail) ) {
			InterfaceStates.SeaDetails = fSeaDetail;
	}
	SetFormatedText("SEA_DETAIL_TEXT", its(makeint(fSeaDetail*100)));
}

//#20171223-01 Camera perspective option
void ChangePerspDetail()
{
    float fCurPerspDetail = stf(GameInterface.nodes.cam_persp_slide.value);
	if( !CheckAttribute(&InterfaceStates,"PerspDetails") ||
		(stf(InterfaceStates.PerspDetails)!=fCurPerspDetail) ) {
			InterfaceStates.PerspDetails = fCurPerspDetail;
	}
	float fCamPersp = CalcSeaPerspective();
	SetFormatedText("SEACAMPERSP_TEXT", FloatToString(fCamPersp,3)));
}
//#20190815-01
void ChangePersp2Detail()
{
    float fCurPerspDetail = stf(GameInterface.nodes.cam_persp_slide2.value);
	if( !CheckAttribute(&InterfaceStates,"Persp2Details") ||
		(stf(InterfaceStates.Persp2Details)!=fCurPerspDetail) ) {
			InterfaceStates.Persp2Details = fCurPerspDetail;
	}
	float fCamPersp = CalcLandPerspective();
	SetFormatedText("LANDCAMPERSP_TEXT", FloatToString(fCamPersp,3)));
}

void ChangeRadDetail()
{
    float fCurPerspDetail = stf(GameInterface.nodes.cam_rad_slide.value);
	if( !CheckAttribute(&InterfaceStates,"RadDetails") ||
		(stf(InterfaceStates.RadDetails)!=fCurPerspDetail) ) {
			InterfaceStates.RadDetails = fCurPerspDetail;
	}
	float fCamPersp = CalcLandRadiusNew();
	SetFormatedText("CAMDISTANCE_TEXT", FloatToString(fCamPersp,1)));
}

void ChangeSoundSetting()
{
	float fMusic = stf(GameInterface.nodes.music_slide.value);
	float fSound = stf(GameInterface.nodes.sound_slide.value);
	float fDialog = stf(GameInterface.nodes.dialog_slide.value);
	SendMessage(&sound,"lfff", MSG_SOUND_SET_MASTER_VOLUME, fSound,	fMusic,	fDialog);
	SetFormatedText("MUSIC_TEXT", its(makeint(fMusic*100)));
	SetFormatedText("SOUND_TEXT", its(makeint(fSound*100)));
	SetFormatedText("DIALOG_TEXT", its(makeint(fDialog*100)));
}

void FillControlsList(int nMode)
{
	int n,qC,idx;
	string groupName;
	aref arGrp, arC;

	if( nMode == g_nCurControlsMode ) {return;}
	g_nCurControlsMode = nMode;
	DeleteAttribute(&GameInterface,"controls_list");
	GameInterface.controls_list.select = 0;

	groupName = GetGroupNameByMode(nMode);
	if( CheckAttribute(&objControlsState,"keygroups."+groupName) )
	{
		makearef(arGrp,objControlsState.keygroups.(groupName));
		qC = GetAttributesNum(arGrp);
		idx = 0;
		for( n=0; n<qC; n++ ) {
			arC = GetAttributeN(arGrp,n);
			if( false==CheckAttribute(arC,"invisible") || arC.invisible!="1" )
			{
			//if( CheckAttribute(arC,"remapping") && arC.remapping=="1" ) {
				if (GetAttributeValue(arC) == "") continue;
				if( AddToControlsList( idx, GetAttributeName(arC), GetAttributeValue(arC), CheckAttribute(arC,"remapping") && arC.remapping=="1" ) )
				{
					idx++;
				}
			}
		}
	}
	SendMessage( &GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONTROLS_LIST", 0 );
}

bool AddToControlsList(int row, string sControl, string sKey, bool bRemapable)
{
	string rowname = "tr" + (row+1);
	GameInterface.controls_list.(rowname).userdata.remapable = bRemapable;
	GameInterface.controls_list.(rowname).userdata.control = sControl;
	GameInterface.controls_list.(rowname).userdata.key = sKey;
	GameInterface.controls_list.(rowname).td1.str = LanguageConvertString(g_ControlsLngFile,sControl);
	GameInterface.controls_list.(rowname).td1.textoffset = "0,2";
	if( GameInterface.controls_list.(rowname).td1.str == "" ) {
		trace("Warning!!! " + sControl + " hav`t translate value");
	}
	if( !bRemapable ) { // выделение контролок которые нельзя поменять
		GameInterface.controls_list.(rowname).td1.color = argb(255,128,128,128);
	}
	if( CheckAttribute(&objControlsState,"key_codes."+sKey+".img") )
	{
		GameInterface.controls_list.(rowname).td2.fontidx = 0;
		GameInterface.controls_list.(rowname).td2.textoffset = "-1,-1";
		GameInterface.controls_list.(rowname).td2.scale = 0.6;
		GameInterface.controls_list.(rowname).td2.str = objControlsState.key_codes.(sKey).img;
	}
	return true;
}

string GetGroupNameByMode(int nMode)
{
	switch( nMode ) {
	case 1: return "Sailing1Pers"; break;
	case 2: return "PrimaryLand"; break;
	case 3: return "Sailing3Pers"; break;
	case 4: return "FightModeControls"; break;
	}
	return "unknown";
}

void GetSoundOptionsData()
{
	float fCurMusic = 0.5;
	float fCurSound = 0.5;
	float fCurDialog = 0.5;
	SendMessage(&sound,"leee",MSG_SOUND_GET_MASTER_VOLUME,&fCurSound,&fCurMusic,&fCurDialog);
	GameInterface.nodes.music_slide.value = fCurMusic;
	GameInterface.nodes.sound_slide.value = fCurSound;
	GameInterface.nodes.dialog_slide.value = fCurDialog;
}

void GetMouseOptionsData()
{
	float fCurXSens = 0.5;
	float fCurYSens = 0.5;
	if( CheckAttribute(&InterfaceStates,"mouse.x_sens") ) {fCurXSens=stf(InterfaceStates.mouse.x_sens);}
	if( CheckAttribute(&InterfaceStates,"mouse.y_sens") ) {fCurYSens=stf(InterfaceStates.mouse.y_sens);}
	if(fCurXSens<0.0) fCurXSens = 0.0;
	if(fCurXSens>1.0) fCurXSens = 1.0;
	if(fCurYSens<0.0) fCurYSens = 0.0;
	if(fCurYSens>1.0) fCurYSens = 1.0;
	GameInterface.nodes.hmouse_sensitivity_slide.value = fCurXSens;
	GameInterface.nodes.vmouse_sensitivity_slide.value = fCurYSens;
}

void GetVideoOptionsData()
{
	float fC = 1.0;
	float fG = 1.0;
	float fB = 0.0;
	float fD = 1.0;
	//#20171223-01 Camera perspective option
	float fE = 0.0;
	//#20190815-01
	float fE2 = 0.0;
	float fR = 0.0;
	int fDS = 0;

	if( CheckAttribute(&InterfaceStates,"video.contrast") ) {
		fC = stf(InterfaceStates.video.contrast);
	}
	if( CheckAttribute(&InterfaceStates,"video.gamma") ) {
		fG = stf(InterfaceStates.video.gamma);
	}
	if( CheckAttribute(&InterfaceStates,"video.brightness") ) {
		fB = stf(InterfaceStates.video.brightness);
	}

	if( CheckAttribute(&InterfaceStates,"SeaDetails") ) {
		fD = stf(InterfaceStates.SeaDetails);
	}
	if( CheckAttribute(&InterfaceStates,"GrassDistanceLand") ) {
		GameInterface.nodes.HERB_LAND_DISTANCE_SLIDE.value = stf(InterfaceStates.GrassDistanceLand);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE, "HERB_LAND_DISTANCE_SLIDE", 1, stf(GameInterface.nodes.HERB_LAND_DISTANCE_SLIDE.value));
	}
	if( CheckAttribute(&InterfaceStates,"GrassDistanceSea") ) {
		GameInterface.nodes.HERB_SEA_DISTANCE_SLIDE.value = stf(InterfaceStates.GrassDistanceSea);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE, "HERB_SEA_DISTANCE_SLIDE", 1, stf(GameInterface.nodes.HERB_SEA_DISTANCE_SLIDE.value));
	}
	if( CheckAttribute(&InterfaceStates,"GrassCountLand") ) {
		GameInterface.nodes.HERB_QUANTITY_SLIDE.value = stf(InterfaceStates.GrassCountLand);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE, "HERB_QUANTITY_SLIDE", 1, stf(GameInterface.nodes.HERB_QUANTITY_SLIDE.value));
	}
	if( CheckAttribute(&InterfaceStates,"GrassCountSea") ) {
		GameInterface.nodes.HERB_TRANSP_SLIDE.value = stf(InterfaceStates.GrassCountSea);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE, "HERB_TRANSP_SLIDE", 1, stf(GameInterface.nodes.HERB_TRANSP_SLIDE.value));
	}
    //#20171223-01 Camera perspective option
	if( CheckAttribute(&InterfaceStates,"PerspDetails") ) {
		fE = stf(InterfaceStates.PerspDetails);
	}
	//#20190815-01
	if( CheckAttribute(&InterfaceStates,"Persp2Details") ) {
		fE2 = stf(InterfaceStates.Persp2Details);
	}
	if( CheckAttribute(&InterfaceStates,"RadDetails") ) {
		fR = stf(InterfaceStates.RadDetails);
	}
	ISetColorCorrection( fC, fG, fB, fD, fE, fE2, fR );
}
//#20190815-01
void ISetColorCorrection(float fContrast, float fGamma, float fBright, float fSeaDetails, float fPerspDetails, float fPersp2, float fRad)
{
	float fCurContrast = ConvertContrast(fContrast,true);
	float fCurGamma = ConvertGamma(fGamma,true);
	float fCurBright = ConvertBright(fBright,true);
	float fCurSeaDetails = ConvertSeaDetails(fSeaDetails, true);

	if(fCurContrast>1.0) fCurContrast = 1.0;
	if(fCurContrast<0.0) fCurContrast = 0.0;
	if(fCurGamma>1.0) fCurGamma = 1.0;
	if(fCurGamma<0.0) fCurGamma = 0.0;
	if(fCurBright>1.0) fCurBright = 1.0;
	if(fCurBright<0.0) fCurBright = 0.0;
	if(fCurSeaDetails<0.0) fCurSeaDetails = 0.0;
	if(fCurSeaDetails>1.0) fCurSeaDetails = 1.0;
	//#20171223-01 Camera perspective option
	if(fPerspDetails<0.0) fPerspDetails = 0.0;
	if(fPerspDetails>1.0) fPerspDetails = 1.0;
	//#20190815-01
	if(fPersp2<0.0) fPersp2 = 0.0;
	if(fPersp2>1.0) fPersp2 = 1.0;
	if(fRad<0.0) fRad = 0.0;
	if(fRad>1.0) fRad = 1.0;

	GameInterface.nodes.CONTRAST_SLIDE.value = fCurContrast;
	GameInterface.nodes.GAMMA_SLIDE.value = fCurGamma;
	GameInterface.nodes.BRIGHT_SLIDE.value = fCurBright;
	GameInterface.nodes.SEA_DETAILS_SLIDE.value = fCurSeaDetails;
	GameInterface.nodes.CAM_PERSP_SLIDE.value = fPerspDetails;
	//#20190815-01
	GameInterface.nodes.CAM_PERSP_SLIDE2.value = fPersp2;
	GameInterface.nodes.CAM_RAD_SLIDE.value = fRad;

	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"CONTRAST_SLIDE", 0,fCurContrast);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"GAMMA_SLIDE", 0,fCurGamma);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"BRIGHT_SLIDE", 0,fCurBright);

	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SEA_DETAILS_SLIDE", 0, fCurSeaDetails);
	//#20171223-01 Camera perspective option
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"CAM_PERSP_SLIDE", 0, fPerspDetails);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"CAM_PERSP_SLIDE2", 0, fPersp2);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"CAM_RAD_SLIDE", 0, fRad);

	XI_SetColorCorrection(fContrast,fGamma,fBright);
	//Set sea detail
}

float ConvertContrast(float fContrast, bool Real2Slider)
{ // контрастность от 0.75 до 1.25
	if(Real2Slider) {
		return fContrast*2.0-1.5;
	}
	return fContrast*0.5+0.75;
}

float ConvertGamma(float fGamma, bool Real2Slider)
{ // гамма от 0.5 до 2.0
	if(Real2Slider)
	{
		return fGamma*2.0/3.0-1.0/3.0;
	}
	return fGamma*1.5+0.5;
}

float ConvertBright(float fBright, bool Real2Slider)
{
	if(Real2Slider) {
		return (fBright+50.0)/100.0;
	}
	return fBright*100.0-50.0;
}

float ConvertSeaDetails(float fDetails, bool Real2Slider)
{
	return fDetails;
}
void GetHerbOptionsData()
{
	int nSelBtn = 0;
	switch( iGrassQuality ) {
	case 0: nSelBtn=4; break;
	case 1: nSelBtn=3; break;
	case 2: nSelBtn=2; break;
	case 3: nSelBtn=1; break;
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"HERB_CHECKBOX", 2, nSelBtn, true );
}

void GetFlagAllOptionsData()
{
	int nSelBtn = 0;
	switch( iFlagAllWdm ) {
	case 0: nSelBtn=3; break;
	case 1: nSelBtn=2; break;
	case 2: nSelBtn=1; break;
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, nSelBtn, true );
}

void GetVisualCirassOptionsData()
{
	int nSelBtn = 0;
	switch( sti(InterfaceStates.VISUAL_CIRASS) )
	{
		case 0:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, false );
		break;
		case 1:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, false );
		break;
		case 3:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, false );
		break;
		case 4:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, false );
		break;
		case 5:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, true );
		break;
		case 6:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, true );
		break;
		case 8:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, true );
		break;
		case 9:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, true );
		break;
	}
}

void GetAltFontOptionsData()
{
	int nSelBtn = 0;
	switch( sti(InterfaceStates.AltFont) ) {
	case 0: nSelBtn=1; break;
	case 1: nSelBtn=2; break;
	case 2: nSelBtn=3; break;
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, nSelBtn, true );
}

void GetBombsParticlesOptionsData()
{
	int nSelBtn = 0;
	switch( sti(InterfaceStates.BombsParticles) ) {
	case 0: nSelBtn=1; break;
	case 1: nSelBtn=2; break;
	case 2: nSelBtn=3; break;
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"PARTICLES_CHECKBOX", 2, nSelBtn, true );
}

void GetControlsStatesData()
{
	int nAlwaysRun = 0;
	if( CheckAttribute(&InterfaceStates,"alwaysrun") ) {
		nAlwaysRun = sti(InterfaceStates.alwaysrun);
	}
	int nInvertCam = 0;
	if( CheckAttribute(&InterfaceStates,"InvertCameras") ) {
		nInvertCam = sti(InterfaceStates.InvertCameras);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALWAYS_RUN_CHECKBOX", 2, 1, nAlwaysRun );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INVERT_MOUSE_CHECKBOX", 2, 1, nInvertCam );
}

void SetAlwaysRun(bool bRun)
{
	InterfaceStates.alwaysrun = bRun;
}

void procKeyChange()
{
	//FillControlsList();
	string srow = "tr" + GameInterface.controls_list.select;
	if( !CheckAttribute(&GameInterface,"controls_list."+srow) ) {return;}
	if( sti(GameInterface.controls_list.(srow).userdata.remapable)!=1 ) {return;}
	ChooseOtherControl();
}

void ChooseOtherControl()
{
	XI_WindowDisable("MAIN_WINDOW",true);
	XI_WindowShow("CHANGEKEY_WINDOW",true);
	SetCurrentNode("KEY_CHOOSER");
	string srow = "tr" + GameInterface.controls_list.select;
	SetFormatedText("CHANGEKEY_TEXT", XI_ConvertString("Press any key"));
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	AddLineToFormatedText("CHANGEKEY_TEXT", GameInterface.controls_list.(srow).td2.str);
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	AddLineToFormatedText("CHANGEKEY_TEXT", XI_ConvertString("KeyAlreadyUsed"));
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 0, argb(255,255,128,128) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 4, argb(0,255,64,64) );
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 5);
}

int glob_retVal;
ref procKeyChoose()
{
	int keyIdx = GetEventData();
	int stickUp = GetEventData();

	glob_retVal = false;

	if (keyIdx == 7) {
		ReturnFromReassign();
		glob_retVal = true;
		return &glob_retVal;
	}

	if( DoMapToOtherKey(keyIdx,stickUp) )
	{
		ReturnFromReassign();
		glob_retVal = true;
	}

	return &glob_retVal;
}

void ReturnFromReassign()
{
	XI_WindowShow("CHANGEKEY_WINDOW",false);
	XI_WindowDisable("MAIN_WINDOW",false);
	SetCurrentNode("CONTROLS_LIST");
}

bool DoMapToOtherKey(int keyIdx,int stickUp)
{
	string srow = "tr" + GameInterface.controls_list.select;
	string groupName = GetGroupNameByMode( g_nCurControlsMode );
	string sControl = GameInterface.controls_list.(srow).userdata.control;
	string sKey = GameInterface.controls_list.(srow).userdata.key;


	aref arControlGroup;
	aref arKeyRoot,arKey;
	string tmpstr;
	int keyCode;

	if( stickUp )
	{
		//SetStickNotAvailable();
		return false;
	}

	makearef(arControlGroup,objControlsState.keygroups.(groupName));
	makearef(arKeyRoot,objControlsState.key_codes);
	if (keyIdx >= GetAttributesNum(arKeyRoot)) {
		trace("ERROR: DoMapToOtherKey keyIdx more than arKeyRoot length")
		return false;
	}
	arKey = GetAttributeN(arKeyRoot,keyIdx);
	keyCode = sti(GetAttributeValue(arKey));

	// check for not allowed keys
	if( //keyCode==sti(objControlsState.key_codes.VK_F1) ||
		keyCode==sti(objControlsState.key_codes.VK_F2) ||
		//keyCode==sti(objControlsState.key_codes.VK_F3) ||
		//keyCode==sti(objControlsState.key_codes.VK_F4) ||
		//keyCode==sti(objControlsState.key_codes.VK_F5) ||
		keyCode==sti(objControlsState.key_codes.VK_F6) ||
		//keyCode==sti(objControlsState.key_codes.VK_F7) ||
		keyCode==sti(objControlsState.key_codes.VK_F8) ||
		keyCode==sti(objControlsState.key_codes.VK_F9) )
	{
		return false;
	}

	if( CheckAttribute(arKey,"stick") && sti(arKey.stick)==true ) return false;

	if( KeyAlreadyUsed(groupName, sControl, GetAttributeName(arKey)) )
	{
		SetKeyChooseWarning( XI_ConvertString("KeyAlreadyUsed") );
		if (curkey != "" && curkey != GetAttributeName(arKey))
		{
			curkey = GetAttributeName(arKey);
			return false;
		}
		if (blockkey)
		{
			blockkey = false;
			curkey = GetAttributeName(arKey);
			return false;
		}
	}

	tmpstr = arControlGroup.(sControl);
	if( CheckAttribute(arKeyRoot,tmpstr+".stick") && sti(arKeyRoot.(tmpstr).stick)==true ) return false;

	int state = 0;
	if(CheckAttribute(arControlGroup,sControl+".state"))
	{	state = sti(arControlGroup.(sControl).state);	}

	CI_CreateAndSetControls( groupName,sControl,keyCode, state, true );
	GameInterface.controls_list.(srow).userdata.key = arKey;
	GameInterface.controls_list.(srow).td2.str = arKey.img;
	SendMessage( &GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONTROLS_LIST", 0 );
	curkey = "";
	blockkey = true;
	return true;
}

void RestoreDefaultKeys(int choice)
{
	SetMouseToDefault();
	if (choice == 0)
	{
		ControlsInit(GetTargetPlatform(),false, 0);
	}
	if (choice == 1)
	{
		ControlsInit(GetTargetPlatform(),false, 1);
	}

	int nMode = g_nCurControlsMode;
	g_nCurControlsMode = -1;
	FillControlsList(nMode);
}

void SetMouseToDefault()
{
	InterfaceStates.InvertCameras = false;
	InterfaceStates.mouse.x_sens = 0.5;
	InterfaceStates.mouse.y_sens = 0.5;

	SetRealMouseSensitivity();
	SetAlwaysRun(true);

	GetControlsStatesData();
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"VMOUSE_SENSITIVITY_SLIDE", 0,stf(InterfaceStates.mouse.y_sens));
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"HMOUSE_SENSITIVITY_SLIDE", 0,stf(InterfaceStates.mouse.x_sens));
}

void ShowSimpleOptionInfo(string sNode)
{
	g_bToolTipStarted = true;
	string sHeader = "TEST";

	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	// sGroup = "none";
	// sGroupPicture = "none";
	int xx = 256;
	int yy = 256;

	switch (sNode)
	{
		case "RegionsWorldmap":
			sHeader = XI_ConvertString("RegionsWorldmap");
			sText1 = XI_ConvertString("RegionsWorldmap Mode_descr");
            sPicture = "INTERFACES\FaqPictures\SEA_REGIONS.dds";
			xx = 256;
			yy = 256;
		break;
		case "SimpleSea":		//ПКМ для настроек простых внизу слева
			sHeader = XI_ConvertString("SimpleSea");
			sText1 = XI_ConvertString("SimpleSea Mode_descr");
		break;
		case "EnabledShipMarks":
			sHeader = XI_ConvertString("EnabledShipMarks");
			sText1 = XI_ConvertString("ShipMark Mode_descr");
            sPicture = "INTERFACES\FaqPictures\SHIPMARK_CHECKBOX.dds";
			xx = 256;
			yy = 256;
		break;
		case "EnabledAutoSaveMode":
			sHeader = XI_ConvertString("EnabledAutoSaveMode");
			sText1 = XI_ConvertString("AutoSave Mode_descr");
		break;
		case "ShowBattleMode":
			sHeader = XI_ConvertString("ShowBattleMode");
			sText1 = XI_ConvertString("Show battle mode_descr");
		break;
		case "SpyglassTextures":
			sHeader = XI_ConvertString("SpyglassTextures");
			sText1 = XI_ConvertString("SpyglassTextures_desc");
            sPicture = "INTERFACES\FaqPictures\SPYGLASSTEX_CHECKBOX.dds";
			xx = 256;
			yy = 256;
		break;
		case "HUDStyle":
			sHeader = XI_ConvertString("HUDStyle");
			sText1 = XI_ConvertString("HUDStyle_desc");
            sPicture = "INTERFACES\FaqPictures\HUDStyle_CHECKBOX.dds";
			xx = 256;
			yy = 256;
		break;
		case "CannonsHUD":
			sHeader = XI_ConvertString("CannonsHUD");
			sText1 = XI_ConvertString("CannonsHUD_desc");
            sPicture = "INTERFACES\FaqPictures\CannonsHUD_CHECKBOX.dds";
			xx = 256;
			yy = 256;
		break;
		case "ShowBoardMode":
			sHeader = XI_ConvertString("ShowBoardMode");
			sText1 = XI_ConvertString("BOARD_MODE_descr");
            sPicture = "INTERFACES\FaqPictures\BOARD_MODE_CHECKBOX.dds";
			xx = 600;
			yy = 300;
		break;
		case "EnableSailors":
			sHeader = XI_ConvertString("EnableSailors");
			sText1 = XI_ConvertString("SAILORS_CHECKBOX_desc");
		break;
		case "CharVoice":
			sHeader = XI_ConvertString("CharVoice");
			sText1 = XI_ConvertString("CHAR_VOICE_CHECKBOX_desc");
            // PlaySound("Voices\"+LanguageGetLanguage()+"\tra_common_"+rand(7)+".wav");
            PlayVoice("Kopcapkz\Voices\Traders\Trader_man_0"+rand(9)+".ogg");
		break;
		case "IslandLoader":
			sHeader = XI_ConvertString("IslandLoader");
			sText1 = XI_ConvertString("IslandLoader_desc");
		break;
		case "AltIntIcons":
			sHeader = XI_ConvertString("AltIntIcons");
			sText1 = XI_ConvertString("AltIntIcons_desc");
            sPicture = "INTERFACES\FaqPictures\ALT_INT_ICONS_CHECKBOX.dds";
			xx = 256;
			yy = 256;
		break;
		case "EnabledQuestsMarks":
			sHeader = XI_ConvertString("EnabledQuestsMarks");
			sText1 = XI_ConvertString("QuestMark Mode_descr");
            sPicture = "INTERFACES\FaqPictures\QUESTMARK_CHECKBOX.dds";
			xx = 256;
			yy = 256;
		break;
		case "EnabledFXMarks":
			sHeader = XI_ConvertString("EnabledFXMarks");
			sText1 = XI_ConvertString("FXMark Mode_descr");
            sPicture = "INTERFACES\FaqPictures\FXMARK_CHECKBOX.dds";
			xx = 256;
			yy = 256;
		break;
		case "EnabledCMControls":
			sHeader = XI_ConvertString("EnabledCMControls");
			sText1 = XI_ConvertString("CMControls Mode_descr");
		break;
		case "EnabledOldStore":
			sHeader = XI_ConvertString("EnabledOldStore");
			sText1 = XI_ConvertString("Store Mode_descr");
            sPicture = "INTERFACES\FaqPictures\OLDSTORE_CHECKBOX.dds";
			xx = 607;
			yy = 258;
		break;
		case "EnabledAltSoundsGun":
			sHeader = XI_ConvertString("EnabledAltSoundsGun");
			sText1 = XI_ConvertString("AltSoundsGun_descr");
            PlayVoice("CSR\GUNSFIRE_ALT\Fort_cannon_0"+rand(5)+".wav");
		break;
		case "ShowExpLogs":
			sHeader = XI_ConvertString("ShowExpLogs");
			sText1 = XI_ConvertString("ShowExpLogs_descr");
            sPicture = "INTERFACES\FaqPictures\SHOWEXPLOGS.dds";
			xx = 256;
			yy = 256;
		break;
	}

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, xx, yy);
}

void ShowInfo()
{
	g_bToolTipStarted = true;
	string sHeader = "TEST";
	string sNode = GetCurrentNode();

	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	// sGroup = "none";
	// sGroupPicture = "none";
	int xx = 256;
	int yy = 256;

	switch (sNode)
	{
		case "GAMMA_SLIDE":
			sHeader = XI_ConvertString("gamma");
			sText1 = XI_ConvertString("gamma_descr");
		break;
		case "BRIGHT_SLIDE":
			sHeader = XI_ConvertString("Brightness");
			sText1 = XI_ConvertString("brightness_descr");
		break;
		case "CONTRAST_SLIDE":
			sHeader = XI_ConvertString("Contrast");
			sText1 = XI_ConvertString("Contrast_descr");
		break;
		case "LAND_DETAILS_SLIDE":
			sHeader = XI_ConvertString("Land Detail");
			sText1 = XI_ConvertString("Land Detail_descr");
			sText2 = XI_ConvertString("ItCanRedusePerfomance");
			sText3 = XI_ConvertString("NeedToExitFromLand");
		break;
		case "SEA_DETAILS_SLIDE":
			sHeader = XI_ConvertString("Sea Detail");
			sText1 = XI_ConvertString("Sea Detail_descr");
			sText2 = XI_ConvertString("ItCanRedusePerfomance");
			sText3 = XI_ConvertString("NeedToExitFromSea");
		break;
		case "HERB_LAND_DISTANCE_SLIDE":
            sHeader = XI_ConvertString("Herb Land Distance");
            sText1 = XI_ConvertString("Herb Land Distance_descr");
            sText2 = XI_ConvertString("Herb Distance_warning");
        break;
		case "HERB_SEA_DISTANCE_SLIDE":
            sHeader = XI_ConvertString("Herb Sea Distance");
            sText1 = XI_ConvertString("Herb Sea Distance_descr");
            sText2 = XI_ConvertString("Herb Distance_warning");
        break;
		case "HERB_QUANTITY_SLIDE":
            sHeader = XI_ConvertString("Herb Quantity");
            sText1 = XI_ConvertString("Herb Quantity_descr");
            sText2 = XI_ConvertString("Herb Distance_warning");
        break;
		case "HERB_TRANSP_SLIDE":
            sHeader = XI_ConvertString("Herb Sea Transp");
            sText1 = XI_ConvertString("Herb Sea Transp_descr");
            sText2 = XI_ConvertString("ItCanRedusePerfomance");
        break;
		case "MUSIC_SLIDE":
			sHeader = XI_ConvertString("Music Volume");
			sText1 = XI_ConvertString("Music Volume_descr");
		break;

		case "SOUND_SLIDE":
			sHeader = XI_ConvertString("Sound Volume");
			sText1 = XI_ConvertString("Sound Volume_descr");
		break;

		case "DIALOG_SLIDE":
			sHeader = XI_ConvertString("Dialog Volume");
			sText1 = XI_ConvertString("Dialog Volume_descr");
		break;

		case "HUD_SLIDE":
			sHeader = XI_ConvertString("HUD_SLIDE");
			sText1 = XI_ConvertString("HUD_SLIDE_descr");
		break;

		case "ALWAYS_RUN_CHECKBOX":
			sHeader = XI_ConvertString("Always Run");
			sText1 = XI_ConvertString("Always Run_descr");
		break;

		case "INVERT_MOUSE_CHECKBOX":
			sHeader = XI_ConvertString("Invert Vertical Mouse Control");
			sText1 = XI_ConvertString("Invert Vertical Mouse Control_descr");
		break;

		case "VMOUSE_SENSITIVITY_SLIDE":
			sHeader = XI_ConvertString("Vertical Mouse Sensitivity");
			sText1 = XI_ConvertString("Vertical Mouse Sensitivity_descr");
		break;

		case "HMOUSE_SENSITIVITY_SLIDE":
			sHeader = XI_ConvertString("Horizontal Mouse Sensitivity");
			sText1 = XI_ConvertString("Horizontal Mouse Sensitivity_descr");
		break;

		case "FLAGALLWDM_CHECKBOX":
			sHeader = XI_ConvertString("FlagAllWDM");
			sText1 = XI_ConvertString("FlagAllWDM_descr");
            sPicture = "INTERFACES\FaqPictures\FLAGALLWDM_CHECKBOX.dds";
			xx = 600;
			yy = 200;
		break;
		case "VISUAL_CIRASS_CHECKBOX":
			sHeader = XI_ConvertString("VISUAL_CIRASS_title");
			sText1 = XI_ConvertString("VISUAL_CIRASS_desc");
            sPicture = "INTERFACES\FaqPictures\VISUAL_CIRASS_CHECKBOX.dds";
			xx = 512;
			yy = 256;
		break;
		case "ALTFONT_CHECKBOX":
			sHeader = XI_ConvertString("AltFont_title");
			sText1 = XI_ConvertString("AltFont_desc");
            sPicture = "INTERFACES\FaqPictures\ALTFONT_CHECKBOX.dds";
			xx = 570;
			yy = 494;
		break;
		case "HUD_DIALOG_BACK":
			sHeader = XI_ConvertString("Hud Dialog");
			sText1 = XI_ConvertString("Hud Dialog_descr");
            sPicture = "INTERFACES\FaqPictures\HUD_DIALOG_SLIDE.dds";
			xx = 512;
			yy = 256;
		break;
		case "PARTICLES_CHECKBOX":
			sHeader = XI_ConvertString("Particles_title");
			sText1 = XI_ConvertString("Particles_descr");
		break;

		case "CAM_PERSP_SLIDE":
			sHeader = XI_ConvertString("cameraPersp_title");
			sText1 = XI_ConvertString("cameraPersp_desc");
		break;

		case "CAM_RAD_SLIDE":
			sHeader = XI_ConvertString("cameraRad_title");
			sText1 = XI_ConvertString("cameraRad_desc");
		break;

		case "CAM_PERSP_SLIDE2":
			sHeader = XI_ConvertString("cameraPersp2_title");
			sText1 = XI_ConvertString("cameraPersp2_desc");
		break;
	}

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

bool KeyAlreadyUsed(string sGrpName, string sControl, string sKey)
{
	if( !CheckAttribute(&objControlsState,"keygroups."+sGrpName+"."+sControl) ) {return false;}
	if( objControlsState.keygroups.(sGrpName).(sControl) == sKey ) {return false;}

	bool bAlreadyUsed = false;
	int n,q, i,grp;
	aref arGrp,arCntrl, arGrpList;

	// проверка на совпадение в той же группе
	makearef(arGrp,objControlsState.keygroups.(sGrpName));
	q = GetAttributesNum(arGrp);
	for(n=0; n<q; n++)
	{
		arCntrl = GetAttributeN(arGrp,n);
		if( GetAttributeValue(arCntrl) == sKey ) {
			bAlreadyUsed = true;
			break;
		}
	}

	if( bAlreadyUsed ) {return bAlreadyUsed;}

	// найдем группу в которой эта контролка также отображается
	makearef(arGrpList, objControlsState.keygroups);
	grp = GetAttributesNum(arGrpList);
	for( i=0; i<grp; i++ )
	{
		arGrp = GetAttributeN(arGrpList,i);
		if( !CheckAttribute(arGrp,sControl) ) {continue;}

		q = GetAttributesNum(arGrp);
		for(n=0; n<q; n++)
		{
			arCntrl = GetAttributeN(arGrp,n);
			if( GetAttributeValue(arCntrl) == sKey ) {
				bAlreadyUsed = true;
				break;
			}
		}
		if( bAlreadyUsed ) {break;}
	}

	return bAlreadyUsed;
}

void SetKeyChooseWarning( string sWarningText )
{
	SendMessage(&GameInterface,"lslle",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 10, 4, &sWarningText );
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 5 );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 4, argb(255,255,64,64) );
	PostEvent("evFaderFrame",700,"lll",3000,0,50);
}

void FaderFrame()
{
	int nTotalTime = GetEventData();
	int nCurTime = GetEventData();
	int nDeltaTime = GetEventData();

	nCurTime = nCurTime + nDeltaTime;
	if( nCurTime>nTotalTime ) {nCurTime=nTotalTime;}

	int nAlpha = 255*(nTotalTime-nCurTime) / nTotalTime;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 4, argb(nAlpha,255,64,64) );

	if( nCurTime<nTotalTime ) {
		PostEvent("evFaderFrame",nDeltaTime,"lll",nTotalTime,nCurTime,nDeltaTime);
	}
}

void ChangeHUDDetail()
{
    float sl = stf(GameInterface.nodes.hud_slide.value);
	newBase = CalcHUDBase(sl, stf(Render.screen_y));
	fHUDRatio = stf(Render.screen_y) / newBase;
	SetFormatedText("HUD_DESCRIP_TEXT", Render.screen_y + "  / " + round(newBase) + " : " + roundFloat(fHUDRatio));
	if (roundFloat(fHUDRatio) != roundFloat(stf(Render.screen_y) / 900.0)) SetSelectable("HUD_SCALE_DEFAULT",true);
	else SetSelectable("HUD_SCALE_DEFAULT",false);
}

void ChangeDialogStyle(bool way)
{
	int value = sti(InterfaceStates.DialogStyle);
	if (way)
	{
		value++;
	}
	else
	{
		value--;
	}
	if (value < 1) value = 5;
	else if (value > 5) value = 1;
	InterfaceStates.DialogStyle = its(value);
	SetFormatedText("HUD_DIALOG_TEXT", InterfaceStates.DialogStyle);
}

void ChangeGrassDistanceLand()
{
    float gds = stf(GameInterface.nodes.HERB_LAND_DISTANCE_SLIDE.value)
	float maxd = gds*500.0;
	InterfaceStates.GrassDistanceLand = gds;
	SetFormatedText("HERB_LAND_DISTANCE_TEXT", ""+makeint(maxd));
}

void ChangeGrassDistanceSea()
{
    float gds = stf(GameInterface.nodes.HERB_SEA_DISTANCE_SLIDE.value)
	float maxd = gds*4000.0;
	InterfaceStates.GrassDistanceSea = gds;
	SetFormatedText("HERB_SEA_DISTANCE_TEXT", ""+makeint(maxd));
}

void ChangeGrassCountLand()
{
    float gds = stf(GameInterface.nodes.HERB_QUANTITY_SLIDE.value)
	float maxd = gds*100;
	InterfaceStates.GrassCountLand = gds;
	SetFormatedText("HERB_QUANTITY_TEXT", ""+makeint(maxd));
}


void ChangeGrassCountSea()
{
    float gds = stf(GameInterface.nodes.HERB_TRANSP_SLIDE.value)
	float maxd = gds*100;
	InterfaceStates.GrassCountSea = gds;
	SetFormatedText("HERB_TRANSP_TEXT", ""+makeint(maxd));
}