#define SIMPLE_OPTIONS_COUNT 18

string SimpleOptionsList[SIMPLE_OPTIONS_COUNT] = {
	"RegionsWorldmap",
	"SimpleSea",
	"EnabledShipMarks",
	"EnabledAutoSaveMode",
	"ShowBattleMode",
	"SpyglassTextures",
	"HUDStyle",
	"CannonsHUD",
	"ShowBoardMode",
	"EnableSailors",
	"CharVoice",
	"IslandLoader",
	"AltIntIcons",
	"EnabledQuestsMarks",
	"EnabledFXMarks",
	"EnabledCMControls",
	"EnabledOldStore",
	"EnabledAltSoundsGun"};

void FillSimpleOptionsTable()//заполняем таблицу
{
    for (i = 0; i < SIMPLE_OPTIONS_COUNT; i++) setDefaultSimpleOption(SimpleOptionsList[i], i+1);
    Table_UpdateWindow("TABLE_SIMPLE_OPTIONS");
}

void setDefaultSimpleOption(string param, int idx) 
{
	string srow = "tr"+idx;
	aref row;
	makearef(row, GameInterface.TABLE_SIMPLE_OPTIONS.(srow));
	row.currentNode = param;//записываем имя опции - для показа подсказки по ПКМ

	row.td2.str = XI_ConvertString(param);
	//row.td2.str = GetOptionName(param);
	row.td1.icon.align = "center";
	row.td1.icon.valign = "center";
	row.td1.icon.width = 16;	//умещалось 17 чекбоксов по 14, увеличил размер для теста скролла
	row.td1.icon.height = 16;
	row.td1.icon.group = "CHECKBUTTON_ICON";
	if (sti(InterfaceStates.(param))) 
	{
		row.td1.icon.image = "check_yes";
		row.td2.color = argb(255,220,220,220);//цвет шрифта
	}
	else 
	{
		row.td1.icon.image = "check_no";
		row.td2.color = argb(255,180,180,180);//цвет шрифта
	}
}

void rightclickSimpleOption() //ПКМ по строке
{
	string srow = "tr" + GameInterface.TABLE_SIMPLE_OPTIONS.select;
	aref row;
	makearef(row, GameInterface.TABLE_SIMPLE_OPTIONS.(srow));
	ShowSimpleOptionInfo(row.currentNode);
}

void clickSimpleOption()
{
	string srow = "tr" + GameInterface.TABLE_SIMPLE_OPTIONS.select;
	aref row;
	makearef(row, GameInterface.TABLE_SIMPLE_OPTIONS.(srow));

	if (row.td1.icon.image == "check_yes") 
	{
		row.td1.icon.image = "check_no";
		row.td2.color = argb(255,180,180,180);//цвет шрифта
	} 
	else
	{
		row.td1.icon.image = "check_yes";
		row.td2.color = argb(255,220,220,220);//цвет шрифта
	}
	Table_UpdateWindow("TABLE_SIMPLE_OPTIONS");

	string param = row.currentNode;
	InterfaceStates.(param) = !sti(InterfaceStates.(param));
}
