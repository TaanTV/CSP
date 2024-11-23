void initPIRATES() {
	string type = NullCharacter.HeroParam.HeroType;
	SetSPECIAL(pchar, 3,3,3,3,3,3,3); //фикс для любителей стирать тип ГГ в файле - была дыра
	pchar.skill.FreeSPECIAL = 0;
	switch (type)
	{  // SPECIAL (Сила, Восприятие, Выносливость, Лидерство, Обучаемость, Реакция, Удача)
        case "Grunt":	//Рубака
    	    SetSPECIAL(pchar, 10,5,10,4,7,8,6);
	    break;

        case "Trader":	//Торговец
    	    SetSPECIAL(pchar, 8,6,5,9,9,3,10);
	    break;

	    case "Fencer":	//Фехтовальщик
         	SetSPECIAL(pchar, 9,3,9,3,10,10,6);
	    break;
	    case "Adventurer":	//Авантюрист
    	    SetSPECIAL(pchar, 7,8,7,8,8,5,7);
	    break;

		case "Buccaneer":	//Буканьер
    	    SetSPECIAL(pchar, 8,10,7,6,7,6,6);
	    break;

	    case "Agent":	//Тайный агент
    	    SetSPECIAL(pchar, 7,7,6,10,6,7,7);
	    break;

		case "SeaWolf":	//Морской Волк
    	    SetSPECIAL(pchar, 6,8,6,9,8,7,6);
	    break;
	}
}

void showPIRATESArrows() {
	int selected = GameInterface.table_special.select;
	string srow = "tr" + selected;
	aref row;
	makearef(row, GameInterface.table_special.(srow));
	int val = GetSkillValue(pchar, SPECIAL_TYPE, row.UserData.ID);
	updatePIRATESArrows(val);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"LEFTCHANGE_SPECIAL",0, 250, 362 + 28*(selected-1), 266, 380 + 28*(selected-1), 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"RIGHTCHANGE_SPECIAL",0, 284, 362 + 28*(selected-1),300, 380 + 28*(selected-1), 0);
}

void upPIRATESArrows(int value) {
	int selected = GameInterface.table_special.select;
	string srow = "tr" + selected;
	aref row;
	makearef(row, GameInterface.table_special.(srow));
	string name = row.UserData.ID;
	int val = GetSkillValue(pchar, SPECIAL_TYPE, name);
	for (int g = 0; g < value; g++)
	{
		if (val < SPECIAL_MAX && pchar.skill.FreeSPECIAL > 0)
		{
			val++;
			int skillValue = GetSkillValue(pchar, SPECIAL_TYPE, name);
			pchar.skill.FreeSPECIAL = MakeInt(pchar.skill.FreeSPECIAL)-1;
			pchar.SPECIAL.(name) = val;
			setPIRATESVal(row, val);
			SetFormatedText("PIRATES_REMAINING", pchar.skill.FreeSPECIAL);
		}
	}
	updatePIRATESArrows(val);
	Table_UpdateWindow("table_special");
}

void downPIRATESArrows(int value) {
	int selected = GameInterface.table_special.select;
	string srow = "tr" + selected;
	aref row;
	makearef(row, GameInterface.table_special.(srow));
	string name = row.UserData.ID;
	int val = GetSkillValue(pchar, SPECIAL_TYPE, name);
	for (int h = 0; h < value; h++)
	{
		if (val > 3)
		{
			val--;
			int skillValue = GetSkillValue(pchar, SPECIAL_TYPE, name);
			pchar.skill.FreeSPECIAL = MakeInt(pchar.skill.FreeSPECIAL)+1;
			pchar.SPECIAL.(name) = val;
			setPIRATESVal(row, val);
			SetFormatedText("PIRATES_REMAINING", pchar.skill.FreeSPECIAL);
		}
	}
	updatePIRATESArrows(val);
	Table_UpdateWindow("table_special");
}

void updatePIRATESArrows(int val) {
    SetNodeUsing("RIGHTCHANGE_SPECIAL", true);
    SetNodeUsing("LEFTCHANGE_SPECIAL", true);
	if (val == SPECIAL_MAX || makeint(pchar.skill.FreeSPECIAL) == 0) {
		SetNodeUsing("RIGHTCHANGE_SPECIAL", false);
	}
	if (val == 3) {
		SetNodeUsing("LEFTCHANGE_SPECIAL", false);
	}
}

void updatePIRATES() {
	initPIRATES();
	fillPIRATESTable();
	Table_UpdateWindow("table_special");
	SetFormatedText("PIRATES_REMAINING", pchar.skill.FreeSPECIAL);
}

void setPIRATESVal(aref row, int val) {
	row.td2.str = val;
	if (row.td2.str == "10") row.td2.color = COLOR_MONEY;
	else row.td2.color = COLOR_NORMAL;
}

void fillPIRATESTable() {
	for (i=1; i<=7; i++)
	{
	    string srow = "tr" + i;
	    string skillName = GetSkillNameByTRIdx("SPECIALType", i);
		aref row;
		makearef(row, GameInterface.TABLE_SPECIAL.(srow));

        row.UserData.ID = skillName;
		row.td1.fontidx = 0;
		row.td1.textoffset = "3,-5";
		row.td1.scale = 0.75;
		row.td2.align = "left";
		row.td3.scale = 0.85;
		row.td3.valign = "top";
		row.td2.scale = 0.8;
		row.td2.fontidx = 1;
		row.td2.textoffset = "-6,0";

		row.td1.str = XI_ConvertString(skillName + "T");
		row.td3.str = GetRPGText(skillName + "Sh");
		setPIRATESVal(row, GetSkillValue(pchar, SPECIAL_TYPE, skillName));
	}

	int selected = 1;
    GameInterface.table_special.select = selected;
	int val = GetSkillValue(pchar, SPECIAL_TYPE, GameInterface.table_special.tr1.UserData.ID);
    updatePIRATESArrows(val);
}