void CreateOtherCharacters()
{
	ref ch;
	
	////////////////////////////////////////////////////////////////////////////////////////
	/// персонаж для ВАНО
	/// делаем его неписем для корректного отображения флага ГГ на шлюпке
	////////////////////////////////////////////////////////////////////////////////////////
	

	makeref(ch,Characters[BOAT_CHARACTER]);		// boat character

	ch.name 	= GetConvertStr("Variable_Other_0.1", "Names.txt");
	ch.lastname = GetConvertStrWithReplace("Variable_Other_1", "Names.txt", "#space#", " ");
	ch.id		= "Boat1234";
	ch.nation	= ENGLAND;
	ch.activity_begin = "0";
	ch.activity_end = "24";
	ch.experience = "0";
	ch.Ship.Name = GetConvertStrWithReplace("Variable_Other_2", "Names.txt", "#space#", " ");
	ch.Ship.Type = GenerateShip(SHIP_BOAT, 1);
	ch.Ship.Stopped = true;
}
