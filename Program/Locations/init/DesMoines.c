
int LocationInitDesMoines(int n)
{
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Locations[n].id = "DesMoines_town";
	locations[n].id.label = "Street";
	Locations[n].image = "loading\jonny_load\city\Town_DesMoines.tga";
	locations[n].townsack = "DesMoines";
	//Town sack
	locations[n].citizens = true;
	locations[n].soldiers = true;
	//locations[n].carrier = true;
	//==> флаг генерации квестодателя по розыску кэпов, int значение - шанс что сам заговорит(1-10)
	locations[n].questSeekCap = 2;
	//Sound
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].type = "town";
	locations[n].islandId = "Mein";
	locations[n].fastreload = "DesMoines";
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	Locations[n].filespath.models = "locations\Town_Oxbay\Town";
	//Always
	Locations[n].models.always.town = "Oxbaytown";
	Locations[n].models.always.town.tech = "DLightModel";
	Locations[n].models.always.mount = "Oxbaytown_exsk";
	Locations[n].models.always.mount.tech = "DLightModel";
	Locations[n].models.always.locators = "Oxbaytown_l";		
	Locations[n].models.always.grassPatch = "Oxbaytown_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "Oxbaytown_b04";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";	
	locations[n].models.always.L2 = "Oxbaytown_l_Cross";
	locations[n].models.always.L2.tech = "DLightModel";
	//Day	
	locations[n].models.day.fonars = "Oxbaytown_fd";
	locations[n].models.day.fonars.tech = "DLightModel";
	locations[n].models.day.charactersPatch = "Oxbaytown_pd";
	locations[n].models.day.rinok = "Oxbaytown_e1";
	locations[n].models.day.rinok.tech = "DLightModel";
	//Night
	locations[n].models.night.charactersPatch = "Oxbaytown_pn";
	locations[n].models.night.fonars = "Oxbaytown_fn";	
	Locations[n].models.night.fonars.tech = "DLightModel";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	
	// --> Типовые городские локации, четкая фиксация на 10 номеров.
	Locations[n].reload.l1.name = "gate_back"; 
	Locations[n].reload.l1.go = "DesMoines_ExitTown";
	Locations[n].reload.l1.emerge = "reload3";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.gate_back = 1.5;

	Locations[n].reload.l2.name = "reload1"; 
	Locations[n].reload.l2.go = "DesMoines_port";
	Locations[n].reload.l2.emerge = "gate_back";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.label = "DesMoines Port";
	locations[n].locators_radius.reload.reload1 = 1.5;
	
	Locations[n].reload.l3.name = "reload13";
	Locations[n].reload.l3.go = "DesMoines_townhall";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Townhall";
	Locations[n].reload.l3.close_for_night = 1;
	
	Locations[n].reload.l4.name = "reload15";
	Locations[n].reload.l4.go = "DesMoines_tavern";
	Locations[n].reload.l4.emerge = "reload1_back";
	Locations[n].reload.l4.autoreload = "0";
	Locations[n].reload.l4.label = "Tavern";

	Locations[n].reload.l6.name = "reload3";
	Locations[n].reload.l6.go = "DesMoines_store";
	Locations[n].reload.l6.emerge = "reload1";
	Locations[n].reload.l6.autoreload = "0";
	Locations[n].reload.l6.label = "Store";
	Locations[n].reload.l6.close_for_night = 1;
	
	locations[n].reload.l7.name = "reload9";
	locations[n].reload.l7.go = "DesMoines_bank";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Usurer House";
	Locations[n].reload.l7.close_for_night = 1;
	
	locations[n].reload.l9.name = "reload7";
	locations[n].reload.l9.go = "DesMoines_church";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Church";
	
	Locations[n].reload.l10.name = "reload11";
	Locations[n].reload.l10.go = "DesMoines_packhouse";
	Locations[n].reload.l10.emerge = "reload1";
	Locations[n].reload.l10.autoreload = "0";
	Locations[n].reload.l10.label = "House";
	Locations[n].reload.l10.close_for_night = 1;
	
	// --> Комоны, загрушки. Номера с начинаются с 11.
	locations[n].reload.l11.name = "reload5";
	locations[n].reload.l11.go = "CommonRoom_MH2";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "House";
	
	locations[n].reload.l12.name = "reload16";
	locations[n].reload.l12.go = "CommonRoom_MH5";
	locations[n].reload.l12.emerge = "reload1";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "House";
	
	locations[n].reload.l13.name = "reload4";
	locations[n].reload.l13.go = "CommonRoom_MH";
	locations[n].reload.l13.emerge = "reload1";
	locations[n].reload.l13.autoreload = "0";
	locations[n].reload.l13.label = "House";
	
	locations[n].reload.l14.name = "reload6";
	locations[n].reload.l14.go = "CommonStoneHouse";
	locations[n].reload.l14.emerge = "reload1";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "House";
	
	locations[n].reload.l16.name = "reload8";
	locations[n].reload.l16.go = "CommonRoom_MH9";
	locations[n].reload.l16.emerge = "reload1";
	locations[n].reload.l16.autoreload = "0";
	locations[n].reload.l16.label = "House";
	
	// --> Псевдоквестовые локации.	
	locations[n].reload.l20.name = "reload2";
	locations[n].reload.l20.go = "DesMoines_Hut1";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";
	
	locations[n].reload.l22.name = "reload18";
	locations[n].reload.l22.go = "DesMoines_TH"; //тут есть коммонка CommonFlamHouse
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";
	
	locations[n].reload.l23.name = "reload17";
	locations[n].reload.l23.go = "DesMoines_Hut3";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";
	
	locations[n].reload.l24.name = "reload10";
	locations[n].reload.l24.go = "DesMoines_Crypt";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "dungeon";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Порт Дес-Мойнес
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_port";
	locations[n].id.label = "Port";
	locations[n].image = "loading\jonny_load\city\Port_DesMoines.tga";
	locations[n].worldmap = "DesMoines";
	locations[n].townsack = "DesMoines";
	//Town sack
	locations[n].citizens = true;
	locations[n].soldiers = true;
	//Sound
	locations[n].type = "port";
	locations[n].islandId = "Mein";
	locations[n].fastreload = "DesMoines";
	//Models
	//Always
	locations[n].filespath.models = "locations\Town_Oxbay\Port";
	
	Locations[n].models.always.locators = "Oxbayport_l";
	Locations[n].models.always.l1 = "Oxbayport";
	Locations[n].models.always.l1.foam = "1";
	Locations[n].models.always.l2 = "Oxbayport_sb";
	Locations[n].models.always.l2.foam = "1";
	Locations[n].models.always.grassPatch = "Oxbayport_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga";
	
	//Day
	locations[n].models.day.charactersPatch = "Oxbayport_pd";
	locations[n].models.day.fonar = "Oxbayport_fd";
	Locations[n].models.day.rinok = "Oxbayport_e1";
	//Night
	locations[n].models.night.charactersPatch = "Oxbayport_pn";
	locations[n].models.night.fonar = "Oxbayport_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "gate_back";
	locations[n].reload.l1.go = "DesMoines_town";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.reload.gate_back = 1.5;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Maracaibo";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	locations[n].locators_radius.reload.reload1_back = 0.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Резиденция Дес-Мойнес
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_Townhall";
	locations[n].id.label = "Townhall";
	locations[n].image = "loading\jonny_load\inside\mediumhouse02.tga";
	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].islandId = "Mein";
	locations[n].fastreload = "DesMoines";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse02";
	locations[n].models.always.mediumhouse02 = "mediumhouse02";
	locations[n].models.always.mediumhouse02.level = 65538;
	locations[n].models.day.locators = "mediumhouse02_locators";
	locations[n].models.night.locators = "mediumhouse02_Nlocators";

	Locations[n].models.always.mediumhouse02windows = "mediumhouse02_windows";
	Locations[n].models.always.mediumhouse02windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse02windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.always.mediumhouse02rand= "mediumhouse02_rand";
	locations[n].models.day.charactersPatch = "mediumhouse02_patch";
	//Night
	locations[n].models.night.charactersPatch = "mediumhouse02_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "DesMoines_town";
	locations[n].reload.l1.emerge = "reload13";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом Трёхэтажный
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_TH";
	locations[n].id.label = "House";
	locations[n].image = "loading\jonny_load\inside\largehouse01.tga";
	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Mein";
	//Models
	locations[n].filespath.models = "locations\inside\largehouse01";
	//Always
	locations[n].models.always.TripleHouse = "largehouse01";
	locations[n].models.always.TripleHouse.level = 65538;
	
	Locations[n].models.always.windows = "largehouse01_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.TripleHouserand= "largehouse01_rand";
	locations[n].models.day.charactersPatch = "largehouse01_patch";
	locations[n].models.day.locators = "largehouse01_locators";
	//Night
	locations[n].models.night.charactersPatch = "largehouse01_patch";
	locations[n].models.night.locators = "largehouse01_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "DesMoines_town";
	locations[n].reload.l1.emerge = "reload18";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonFlamHouse";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Маленький дом из ПКМ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_Hut1";
	
	locations[n].id.label = "House";
	locations[n].image = "loading\jonny_load\inside\Smallhome_k2.tga";
	locations[n].MustSetReloadBack = true;
 	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Mein";
	//Models
	locations[n].filespath.models = "locations\inside\Smallhome";
	//Always
	locations[n].models.always.Smallhome = "SH";
	locations[n].models.always.Smallhome.level = 65538;
	locations[n].models.always.locators = "SH_l";
	locations[n].models.always.window = "SH_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "SH_p";
	//Night
	locations[n].models.night.charactersPatch = "SH_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "reload2";
	locations[n].reload.l1.emerge = "DesMoines_town";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом кузнеца с камином
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_Hut3";
	locations[n].id.label = "House";
	locations[n].image = "loading\jonny_load\inside\Hut3_Kns.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
 	locations[n].islandId = "Mein";
	//Models
	locations[n].filespath.models = "locations\inside\Hut3";
	//Always
	locations[n].models.always.locators = "Hut3_locators";
	locations[n].models.always.tavern = "Hut3";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut3_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut3_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut3_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "DesMoines_town";
	locations[n].reload.l1.emerge = "reload14";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// склеп под часовней
	/////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_Crypt";
	locations[n].id.label = "Crypt";
	locations[n].image = "loading\jonny_load\inside\crypt_inside.tga";
	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "Dungeon";
	locations[n].islandId = "Mein";
	//Models
	locations[n].filespath.models = "locations\inside\crypt_inside\";
	//Always
	locations[n].models.always.crypt = "crypt_inside";
	locations[n].models.always.locators = "crypt_inside_locators";
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "crypt_inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "crypt_inside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "DesMoines_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Таверна Дес-Мойнес
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	locations[n].id = "DesMoines_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\Tavern09\";
	locations[n].image = "loading\jonny_load\inside\Tavern09.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "DesMoines";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].models.always.tavern = "Tavern09";
	locations[n].models.always.locators = "Tavern09_locators";
	locations[n].models.always.window = "Tavern09_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Tavern09_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern09_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "DesMoines_town";
	locations[n].reload.l1.emerge = "reload15";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "DesMoines_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload11";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната в таверне наверху, Дес-Мойнес
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\jonny_load\inside\Tavern_room.tga";
	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "DesMoines";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].models.always.locators = "Tavern_room_locators";
	locations[n].models.always.tavern = "Tavern_room";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "tavern_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "DesMoines_tavern";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Магазин Дес-Мойнес
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_store";
	locations[n].id.label = "Store";
	locations[n].image = "loading\jonny_load\inside\StoreSmall.tga";
	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "DesMoines";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\StoreSmall\";
	locations[n].models.always.locators = "StoreSmall_locators";
	locations[n].models.always.store = "StoreSmall";
	locations[n].models.always.window = "StoreSmall_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "StoreSmall_patch";
	//Night
	locations[n].models.night.charactersPatch = "StoreSmall_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "DesMoines_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    ////////////////////////==> комната в магазине
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonRoom_MH10";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пиратский дом (ростовщик)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_bank";
	locations[n].id.label = "Usurer House";
	locations[n].image = "loading\jonny_load\inside\bank03.tga";
	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "DesMoines";
	locations[n].islandId = "Mein";
	//Always
	locations[n].filespath.models = "locations\inside\Pirate_House";
	locations[n].models.always.locators = "PirH_l";
	locations[n].models.always.tavern = "PirH";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "PirH_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "PirH_p";
	//Night
	locations[n].models.night.charactersPatch = "PirH_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "DesMoines_town";
	locations[n].reload.l1.emerge = "reload9";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
    LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ЦЕРКОВЬ Дес-Мойнес
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_church";
	locations[n].id.label = "Church";
	locations[n].image = "loading\jonny_load\inside\church_IM.tga";
	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "DesMoines";
	locations[n].islandId = "Mein";
	//Models
	locations[n].filespath.models = "locations\inside\church_IM\";
	//Always
	locations[n].models.always.church = "church_IM";
	locations[n].models.always.locators = "church_IM_locators";
	locations[n].models.always.window = "church_IM_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "church_IM_patch";
	//Night
	locations[n].models.night.charactersPatch = "church_IM_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "DesMoines_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Склад 02 (ККС)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DesMoines_packhouse";
	locations[n].id.label = "packhouse";
	locations[n].image = "loading\jonny_load\inside\sklad02.tga";
	locations[n].MustSetReloadBack = true;
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "DesMoines";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "fort";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Sklad02";
	locations[n].models.always.locators = "sklad02_locators";
	locations[n].models.always.modelSklad = "sklad02";
	locations[n].models.always.modelSklad.level = 65538;
	//Day
	locations[n].models.day.charactersPatch = "sklad02_patch";
	//Night
	locations[n].models.night.charactersPatch = "sklad02_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "DesMoines_town";
	locations[n].reload.l1.emerge = "reload11";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// выход из Дес-Мойлеса
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "DesMoines_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\jonny_load\jungle\TownExitDes.tga";
	//Sound
	locations[n].type = "jungle";
	Locations[n].townsack = "DesMoines";
	locations[n].islandId = "Mein";
	locations[n].fastreload = "DesMoines";
	//Models
	Locations[n].filespath.models = "locations\Town_Oxbay\Exit";
	//Always
	Locations[n].models.always.townExit = "OxbayExit";
	Locations[n].models.always.townExit.tech = "DLightModel";
	Locations[n].models.always.locators = "OxbayExit_l";		
	Locations[n].models.always.grassPatch = "OxbayExit_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan_1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan_2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan_3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";	
	//Day
	locations[n].models.day.charactersPatch = "OxbayExit_p";
	locations[n].models.day.fonars = "OxbayExit_fd";
	//Night
	locations[n].models.night.charactersPatch = "OxbayExit_p";
	locations[n].models.night.fonars = "OxbayExit_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "OutRHouse";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Maracaibo_Jungle_04";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

    Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "DesMoines_town";
	Locations[n].reload.l3.emerge = "gate_back";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Street";
	locations[n].locators_radius.reload.reload3 = 1.5;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// домик в джунглях
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "OutRHouse";
	locations[n].id.label = "jungle";
	locations[n].image = "loading\jonny_load\outside\House_in_jungle.tga";
	//Sound
	locations[n].islandId = "Mein";
	locations[n].type = "jungle";
	locations[n].DisableEncounters = true;
	//Models
	//Always
	Locations[n].filespath.models = "locations\Outside\OutRHouse";
    Locations[n].models.always.house = "RHouse";
    Locations[n].models.always.l1 = "rhouse_b01";
    Locations[n].models.always.l1.level = 9;
    Locations[n].models.always.l1.tech = "LocationModelBlend";
    Locations[n].models.always.l2 = "rhouse_b02";
    Locations[n].models.always.l2.level = 8;
    Locations[n].models.always.l2.tech = "LocationModelBlend";
    Locations[n].models.always.l3 = "rhouse_b03";
    Locations[n].models.always.l3.level = 7;
    Locations[n].models.always.l3.tech = "LocationModelBlend";
	Locations[n].models.always.l4 = "rhouse_b04";
    Locations[n].models.always.l4.level = 7;
    Locations[n].models.always.l4.tech = "LocationModelBlend";
	Locations[n].models.always.locators = "rhouse_l";
	
	Locations[n].models.always.grassPatch = "rhouse_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
    //Day
    Locations[n].models.day.charactersPatch = "rhouse_p";
    //Night
    Locations[n].models.night.charactersPatch = "rhouse_p";
    //Environment
    Locations[n].environment.weather = "true";
    Locations[n].environment.sea = "false";	
	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "SmallHouse_Jungle";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "House";
	locations[n].locators_radius.reload.reload2_back = 1.2;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "DesMoines_ExitTown";
	locations[n].reload.l2.emerge = "reload1_back";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "ExitTown";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// вход в домик 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SmallHouse_Jungle";
	locations[n].id.label = "House";
	locations[n].image = "loading\jonny_load\inside\SmallHouse_inside.tga";
	locations[n].islandId = "Mein";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "House";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\SmallHouse_inside\";
	locations[n].models.always.SmallHouse = "SmallHouse_inside";
	//locations[n].models.always.SmallHouse.level = 65538;
	Locations[n].models.always.windows = "SmallHouse_inside_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back2";
	//Day
	locations[n].models.day.charactersPatch = "SmallHouse_inside_patch";
	locations[n].models.day.locators = "SmallHouse_inside_ld";
	//Night
	locations[n].models.night.charactersPatch = "SmallHouse_inside_patch";
	locations[n].models.night.locators = "SmallHouse_inside_ln";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "OutRHouse";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "jungle";
	n = n + 1;

	return n;
}
