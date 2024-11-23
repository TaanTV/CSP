#define ADVANCED_PARAMS_COUNT 18

string AdvancedParamsList[ADVANCED_PARAMS_COUNT] = {
    "CHECK_LOWERSHIP",
    "CHECK_LOWERSELF",
    "CHECK_DIFFICULTY_WEIGHT",
    "CHECK_PARTITION",
    "CHECK_CREWWEIGHT",
    "CHECK_SAILS",
    "CHECK_HALFIMMORTALPGG",
    "CHECK_ENC_SEARCH_SHIP",
    "CHECK_WORLDPAUSE",
    "CHECK_HARDCORE",
    "CHECK_PISTOL",
    "CHECK_SHOOTONLYENEMY",
    "CHECK_RANK_REQUIREMENT",
    "CHECK_NOBONUS_SKILL_OFF",
    "CHECK_HARD_BOSS",
    "CHECK_HARD_ANIMATIONS",
    "CHECK_ALTERNATIVE_BALANCE",
	"CHECK_QUESTS_RANK"};

void updateAdvancedParams()
{
    fillAdvancedParamsTable();
    Table_UpdateWindow("advanced_difficulty_settings_window_table_2");
}

void switchAdvancedParam(string param) {
	switch (param)
	{
	case "CHECK_PISTOL":
		bRechargePistolOnLine = !bRechargePistolOnLine;
		break;
	case "CHECK_HARDCORE":
		bHardcoreGame = !bHardcoreGame;
		break;
	case "CHECK_PARTITION":
		bPartitionSet = !bPartitionSet;
		break;
	case "CHECK_CREWWEIGHT":
		bSailorsWeight = !bSailorsWeight;
		break;
	case "CHECK_SAILS":
		bNewSails = !bNewSails;
		break;
	case "CHECK_NOBONUS_SKILL_OFF":
		bNoBonusSkillOff = !bNoBonusSkillOff;
		break;
	case "CHECK_HALFIMMORTALPGG":
		bHalfImmortalPGG = !bHalfImmortalPGG;
		break;
	case "CHECK_HARD_ANIMATIONS":
		bHardAnimations = !bHardAnimations;
		break;
	case "CHECK_HARD_BOSS":
		bHardBoss = !bHardBoss;
		break;
	case "CHECK_ENC_SEARCH_SHIP":
		bFillEncyShips = !bFillEncyShips;
		break;
	case "CHECK_ALTERNATIVE_BALANCE": 
		bAltBalance = !bAltBalance;
		if(bAltBalance) {
			ShowAltBalanceWindow(true);
		}
		break;
	case "CHECK_LOWERSHIP": 
		bHigherShipRate = !bHigherShipRate;
		break;
	case "CHECK_LOWERSELF": 
		bHigherSelfRate = !bHigherSelfRate;
		break;
	case "CHECK_RANK_REQUIREMENT": 
		bRankRequirement = !bRankRequirement;
		break;
	case "CHECK_DIFFICULTY_WEIGHT": 
		bDifficultyWeight = !bDifficultyWeight;
		break;
	case "CHECK_SHOOTONLYENEMY": 
		bShootOnlyEnemy = !bShootOnlyEnemy;
		break;
	case "CHECK_WORLDPAUSE": 
		bWorldAlivePause = !bWorldAlivePause;
		break;
	case "CHECK_QUESTS_RANK": 
		bQuestsRank = !bQuestsRank;
		break;
	}
}

void setDefaultAdvancedParam(string param, int idx) {
	string srow = "tr"+idx;
	aref row;
	makearef(row, GameInterface.advanced_difficulty_settings_window_table_2.(srow));
	row.currentNode = param;
	switch (param)
	{
	case "CHECK_PISTOL":
		row.normalColor = argb(255,180,150,150);
		row.selectedColor = argb(255,220,100,100);
		row.td2.str = XI_ConvertString("New Fight Mode");
		initParamCheckbox(row, bRechargePistolOnLine);
		break;
	case "CHECK_HARDCORE":
		row.normalColor = argb(255,180,150,150);
		row.selectedColor = argb(255,220,100,100);
		row.td2.str = XI_ConvertString("HardcoreGame");
		initParamCheckbox(row, bHardcoreGame);
		break;
	case "CHECK_PARTITION":
		row.normalColor = argb(255,180,180,180);
		row.selectedColor = argb(255,220,220,220);
		row.td2.str = XI_ConvertString("Partition Set");
		initParamCheckbox(row, bPartitionSet);
		break;
	case "CHECK_CREWWEIGHT":
		row.normalColor = argb(255,180,180,180);
		row.selectedColor = argb(255,220,220,220);
		row.td2.str = XI_ConvertString("CrewWeight");
		initParamCheckbox(row, bSailorsWeight);
		break;
	case "CHECK_SAILS":
		row.normalColor = argb(255,180,180,180);
		row.selectedColor = argb(255,220,220,220);
		row.td2.str = XI_ConvertString("NewSails");
		initParamCheckbox(row, bNewSails);
		break;
	case "CHECK_NOBONUS_SKILL_OFF":
		row.normalColor = argb(255,180,150,150);
		row.selectedColor = argb(255,220,100,100);
		row.td2.str = XI_ConvertString("NoBonusSkillOff");
		initParamCheckbox(row, bNoBonusSkillOff);
		break;
	case "CHECK_HALFIMMORTALPGG":
		row.normalColor = argb(255,180,180,180);
		row.selectedColor = argb(255,220,220,220);
		row.td2.str = XI_ConvertString("HalfImmortalPGG");
		initParamCheckbox(row, bHalfImmortalPGG);
		break;
	case "CHECK_HARD_ANIMATIONS":
		row.normalColor = argb(255,180,150,150);
		row.selectedColor = argb(255,220,100,100);
		row.td2.str = XI_ConvertString("HARD_ANIMATIONS");
		initParamCheckbox(row, bHardAnimations);
		break;
	case "CHECK_HARD_BOSS":
		row.normalColor = argb(255,180,150,150);
		row.selectedColor = argb(255,220,100,100);
		row.td2.str = XI_ConvertString("HARD_BOSS");
		initParamCheckbox(row, bHardBoss);
		break;
	case "CHECK_ENC_SEARCH_SHIP":
		row.normalColor = argb(255,180,180,180);
		row.selectedColor = argb(255,220,220,220);
		row.td2.str = XI_ConvertString("CHECK_ENC_SEARCH_SHIP");
		initParamCheckbox(row, bFillEncyShips);
		break;
	case "CHECK_ALTERNATIVE_BALANCE": 
		row.normalColor = argb(255,180,150,150);
		row.selectedColor = argb(255,220,100,100);
		row.td2.str = XI_ConvertString("CHECK_ALTERNATIVE_BALANCE");
		initParamCheckbox(row, bAltBalance);
		break;
	case "CHECK_LOWERSHIP": 
		row.normalColor = argb(255,150,180,150);
		row.selectedColor = argb(255,100,220,100);
		row.td2.str = XI_ConvertString("LowerShip");
		initParamCheckbox(row, bHigherShipRate);
		break;
	case "CHECK_LOWERSELF": 
		row.normalColor = argb(255,150,180,150);
		row.selectedColor = argb(255,100,220,100);
		row.td2.str = XI_ConvertString("LowerSelf");
		initParamCheckbox(row, bHigherSelfRate);
		break;
	case "CHECK_RANK_REQUIREMENT": 
		row.normalColor = argb(255,180,150,150);
		row.selectedColor = argb(255,220,100,100);
		row.td2.str = XI_ConvertString("CHECK_RANK_REQUIREMENT");
		initParamCheckbox(row, bRankRequirement);
		break;
	case "CHECK_DIFFICULTY_WEIGHT": 
		row.normalColor = argb(255,150,180,150);
		row.selectedColor = argb(255,100,220,100);
		row.td2.str = XI_ConvertString("DifficultyWeight");
		initParamCheckbox(row, bDifficultyWeight);
		break;
	case "CHECK_SHOOTONLYENEMY": 
		row.normalColor = argb(255,180,150,150);
		row.selectedColor = argb(255,220,100,100);
		row.td2.str = XI_ConvertString("ShootOnlyEnemy");
		initParamCheckbox(row, bShootOnlyEnemy);
		break;
	case "CHECK_WORLDPAUSE": 
		row.normalColor = argb(255,180,180,180);
		row.selectedColor = argb(255,220,220,220);
		row.td2.str = XI_ConvertString("WorldPause");
		initParamCheckbox(row, bWorldAlivePause);
		break;
	case "CHECK_QUESTS_RANK": 
		row.normalColor = argb(255,180,150,150);
		row.selectedColor = argb(255,220,100,100);
		row.td2.str = XI_ConvertString("QuestsRank");
		initParamCheckbox(row, bQuestsRank);
		break;
	}

	exceptionsAdvancedParams(row);
}

void fillAdvancedParamsTable() {
	for (i = 0; i < ADVANCED_PARAMS_COUNT; i++) {
		setDefaultAdvancedParam(AdvancedParamsList[i], i+1);
	}
}

void clickAdvancedParam() {
	string srow = "tr" + GameInterface.advanced_difficulty_settings_window_table_2.select;
	aref row;
	makearef(row, GameInterface.advanced_difficulty_settings_window_table_2.(srow));

	if (exceptionsAdvancedParams(row)) {
		return;
	}

	if (row.td1.icon.image == "check_yes") {
		row.td1.icon.image = "check_no";
		row.td2.color = row.normalColor;
		switchAdvancedParam(row.currentNode);
	} else {
		row.td1.icon.image = "check_yes";
		row.td2.color = row.selectedColor;
		switchAdvancedParam(row.currentNode);
	}
	Table_UpdateWindow("advanced_difficulty_settings_window_table_2");
}

void rightclickAdvancedParam() {
	string srow = "tr" + GameInterface.advanced_difficulty_settings_window_table_2.select;
	aref row;
	makearef(row, GameInterface.advanced_difficulty_settings_window_table_2.(srow));
	ShowInfo(row.currentNode);
}

void ShowAdvancedParamsWindow(bool show)
{
	if (show)
	{
		SetCurrentNode("ADVANCED_DIFFICULTY_SETTINGS_WINDOW_CLOSE");

		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("ADVANCED_DIFFICULTY_SETTINGS_WINDOW", false);
		XI_WindowShow("ADVANCED_DIFFICULTY_SETTINGS_WINDOW", true);
		// EI_CreateFrame("ALTBALANCE_WINDOW_BORDERS",190,190,610,360);

	}
	else
	{
		XI_WindowDisable("ADVANCED_DIFFICULTY_SETTINGS_WINDOW", true);
		XI_WindowShow("ADVANCED_DIFFICULTY_SETTINGS_WINDOW", false);
		XI_WindowDisable("MAIN_WINDOW", false);
		SetCurrentNode("OK_BUTTON");
	}
}

bool exceptionsAdvancedParams(aref row) {
	if (MOD_SKILL_ENEMY_RATE != 3 && row.currentNode == "CHECK_HARD_ANIMATIONS") {
		if (row.td1.icon.image == "check_yes") {
			switchAdvancedParam(row.currentNode);
		}
		row.td1.icon.image = "check_no";
		row.td2.color = argb(255,135,130,130);
		return true;
	}
	return false;
}