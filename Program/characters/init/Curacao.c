
int CreateCuracaoCharacters(int n)
{
	ref ch;

	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//Губернатор
	ch.id		= "Villemstad_Mayor";
	ch.model	= "huber_hol";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.greeting = "hol_gov_common";
	ch.nation = HOLLAND;
	ch.quest.type = "hovernor";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Священик
	ch.id		= "Villemstad_Priest";
	ch.model	= "priest_4";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_church.c";
	ch.greeting = "Gr_Church";
	ch.nation = HOLLAND;
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		// ОФициантка
	ch.id		= "Villemstad_waitress";
	ch.model	= "girl_4";
	ch.name 	= GetConvertStr("Variable_Curacao_0.1", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_Curacao_1", "Names.txt", "#space#", " ");
	ch.sex = "woman";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Waitress_dialog.c";
	ch.greeting = "Gr_officiant";
	ch.nation = HOLLAND;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id		= "Villemstad_tavernkeeper";
	ch.model	= "barmen_4";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = HOLLAND;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Торговец
	ch.id		= "Villemstad_trader";
	ch.model	= "trader_4";
	ch.name 	= GetConvertStr("Variable_Curacao_0.2", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_Curacao_2", "Names.txt", "#space#", " ");
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = HOLLAND;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			//Корабел
	ch.id		= "Villemstad_shipyarder";
	ch.model	= "shipowner_4";
	ch.greeting = "Gr_shipyarder";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_Shipyard";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = HOLLAND;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor1");
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Банкир
	ch.id		= "Villemstad_usurer";
	ch.name 	= GetConvertStr("Variable_Curacao_0.3", "Names.txt");
	ch.lastname 	= GetConvertStr("Variable_Curacao_0.3.1", "Names.txt");
	ch.model	= "usurer_2";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Usurer_dialog.c";
	ch.nation = HOLLAND;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 11000; // *1000 денег
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	n = n + 1;

	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "Villemstad_PortMan";
	ch.model	= "usurer_5";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = HOLLAND;
	ch.greeting = "portmans";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);
	ch.name 	= GetConvertStr("Variable_Curacao_0.4", "Names.txt");
	ch.lastname = "";
	ch.id		= "Villemstad_Smuggler";
	ch.model    = "pirate_1";
	ch.sex      = "man";
	LAi_SetLoginTime(ch, 0.0, 24.0);
	ch.nation = PIRATE;
	GiveItem2Character(ch, BLADE_SABER);
	ch.equip.blade = BLADE_SABER;
	// посадим в генераторе
	ch.Dialog.Filename = "Smuggler_Agent_dialog.c";
	LAi_SetSitType(ch);
	LAi_SetHP(ch, 80.0, 80.0);
	ch.greeting = "Gr_Smuggler Agent";
	n = n + 1;

	//смотритель кладбища
	makeref(ch,Characters[n]);
	ch.name 	= GetConvertStr("Variable_Curacao_0.5", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_Curacao_3", "Names.txt", "#space#", " ");
	ch.id		= "Villemstad_Graveyard_Watcher";
	ch.model    = "LeoMaskett";
	ch.sex      = "man";
	ch.model.animation = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_KeepersHouse";
	ch.location.group = "goto";
	ch.location.locator = "goto2";
	ch.watchBoxes = true;
	ch.NotRemoved = true;
	LAi_SetLoginTime(ch, 0.0, 24.0);
	ch.nation = HOLLAND;
	FantomMakeCoolFighter(ch,30,60,60,BLADE_LONG, "pistol3",60);
	ch.Dialog.Filename = "Graveyard_Watcher_dialog.c";
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetHP(ch, 200.0, 200.0);
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);
	ch.name 	= GetConvertStr("Variable_Curacao_0.6", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_Curacao_4", "Names.txt", "#space#", " ");
	ch.id		= "GWIK_char";
	ch.model    = "trader_11";
	ch.sex      = "man";
	ch.model.animation = "man";
	ch.City = "Villemstad";
	ch.location	= "GWIK";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.watchBoxes = true;
	ch.NotRemoved = true;
	ch.nation = HOLLAND;
	ch.Dialog.Filename = "GWIK.c";
	LAi_SetSitTypeNoGroup(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetHP(ch, 200.0, 200.0);
	LAi_SetImmortal(ch, true);
	n = n + 1;

	return n;
}
