/////////////////////////////////////////////////////////////////////////////////////
// DoZoR
/////////////////////////////////////////////////////////////////////////////////////
void DozorSetRiddleQuestion(int iType)
{
	string sString = "";
	if (LanguageGetLanguage() != "russian")
	{
		switch(iType)
		{
			case 1:
				sString = "- Captain, the ship of the smugglers is captured! A strange note was found in the cabin of the ship!";
				sString += newStr() + "- Show it to me!";
				sString += newStr() + "- There is it, sir";
				sString += newStr() + "- 6 1 10 1 18 4 15";
				sString += newStr() + "- 2 5 1 3 8";
				sString += newStr() + "- Looks like an encrypted smuggling place.";
				sString += newStr() + "- Do you think so?";
				sString += newStr() + "- There is no other way!";

				PChar.Dozor.Riddle.Type_1.Question = sString;
				PChar.Dozor.Riddle.Type_1.Answer_1 = "fajardo beach";
				PChar.Dozor.Riddle.Type_1.KeyPhrase = "The Elusive Squadron appeared in the waters of the Caribbean Sea.";
			break;

			case 2:
				sString = "Have you heard the old story about the Caribbean Archipelago? It's usually the story of cartographers. No? Well, then, listen. If you go north from the center, you will see a monster as vicious as the one in the world. If you defeat an evil beast and continue in the same direction, you will meet the longest beast there. Defeat this devil, turn to the east. In the east you will see an armored bastard, whom the Spaniards and the French call a turtle. If you defeat this monster, your path lies in the northeast, where you will find peace and warmth.";
				PChar.Dozor.Riddle.Type_2.Question = sString;
				PChar.Dozor.Riddle.Type_2.Answer_1 = "turks";
				PChar.Dozor.Riddle.Type_2.Answer_2 = "south gulf";
				PChar.Dozor.Riddle.Type_2.KeyPhrase = "The brave captain seeks the Elusive Squadron.";
			break;

			case 3:
				sString = "- You should always pay attention to the first ship of the caravan, captain. Most often it is first attacked. Remember?";
				sString += newStr() + "- That's right, Admiral! First ship!";
				sString += newStr() + "- Very good! And now, Captain, take a look at the message and try to understand what is written here:";
				sString += newStr() + "...Today our revenge to ugly General Alvarez...";
				sString += newStr() + "...Triumph after victory! Everybody, rise now!...";
				sString += newStr() + "- I don't understand anything, Admiral. What is this nonsense?";
				sString += newStr() + "- Patience, captain, patience. A little diligence and you will see that sometimes there is a hidden meaning in delirium. At ease, captain.";
				PChar.Dozor.Riddle.Type_3.Question = sString;
				PChar.Dozor.Riddle.Type_3.Answer_1 = "tortuga";
				PChar.Dozor.Riddle.Type_3.Answer_2 = "tavern";
				PChar.Dozor.Riddle.Type_3.KeyPhrase = "The brave captain is on the trail of the Elusive Squadron.";
			break;

			case 4:
				PChar.Dozor.Riddle.Type_4.Question = "picture";
				PChar.Dozor.Riddle.Type_4.Answer_1 = "willemstad";
				PChar.Dozor.Riddle.Type_4.Answer_2 = "store";
				PChar.Dozor.Riddle.Type_4.KeyPhrase = "A brave captain almost catch the Elusive Squadron.";
			break;

			case 5:
				sString = "They first traveled to Port Royal in Jamaica, then to Hispaniola, the Spanish town of Santo Domingo, then to San Juan, Puerto Rico, and then to Charlestown, Nevis. After visiting Nevis, the English colony of Antigua, they visited the penultimate island of Martinique, in the pirate Le Franсois. But the last task they could not solve, you know? They came across a very inaccessible task.";
				PChar.Dozor.Riddle.Type_5.Question = sString;
				PChar.Dozor.Riddle.Type_5.Answer_1 = "maria galante";
				PChar.Dozor.Riddle.Type_5.Answer_2 = "cape inaccessible";
				PChar.Dozor.Riddle.Type_5.KeyPhrase = "A brave captain got into a fight with the Elusive Squadron.";
			break;

			case 6:
				PChar.Dozor.Riddle.Type_6.Question = "text";
				PChar.Dozor.Riddle.Type_6.Answer_1 = "gulf of doom";
				PChar.Dozor.Riddle.Type_6.KeyPhrase = "The elusive Squadron has lost flagship.";
			break;

			case 7:
				sString = "- Captain! Two small pirate ships ahead!";
				sString += newStr() + "- Report the number of cannons on each of them!";
				sString += newStr() + "- One ship has 10 cannons, the other 13!";
				sString += newStr() + "- Get ready to fight";
				sString += newStr() + "A - 1.2 2.2 2.4 2.11";
				sString += newStr() + "B - 2.9";
				sString += newStr() + "C - 2.12";
				sString += newStr() + "E - 1.10 2.7 2.10";
				sString += newStr() + "H - 2.13";
				sString += newStr() + "I - 1.5 1.7";
				sString += newStr() + "L - 2.1";
				sString += newStr() + "M - 1.1 2.3";
				sString += newStr() + "N - 1.6 2.5 2.8";
				sString += newStr() + "Q - 1.8";
				sString += newStr() + "R - 1.3";
				sString += newStr() + "T - 1.4 2.6";
				sString += newStr() + "U - 1.9";
				PChar.Dozor.Riddle.Type_7.Question = sString;
				PChar.Dozor.Riddle.Type_7.Answer_1 = "martinique";
				PChar.Dozor.Riddle.Type_7.Answer_2 = "la manten beach";
				PChar.Dozor.Riddle.Type_7.KeyPhrase = "The Elusive Squadron was defeated.";
			break;

			case 8:
				sString = "This is the end of your journey, watchman! A house awaits behind these gates, and in that house, in the chest, your reward awaits you! If you know where they are, go there immediately, if you do not know, I suggest you be more careful and more often look around to find the right place.";
				PChar.Dozor.Riddle.Type_8.Question = sString;
			break;
		}
	}
	else
	{
		switch(iType)
		{
			case 1:
				sString = "- Капитан, корабль контрабандистов захвачен! В каюте корабля обнаружена записка странного содержания!";
				sString += newStr() + "- Покажите мне её немедленно!";
				sString += newStr() + "- Вот она, сэр!";
				sString += newStr() + "17 13 33 8";
				sString += newStr() + "22 1 23 1 18 5 16";
				sString += newStr() + "- Похоже это зашифрованное место сбора контрабандистов. ";
				sString += newStr() + "- Вы так думаете?";
				sString += newStr() + "- Иных вариантов быть не может!";

				PChar.Dozor.Riddle.Type_1.Question = sString;
				PChar.Dozor.Riddle.Type_1.Answer_1 = "пляж фахардо";
				PChar.Dozor.Riddle.Type_1.KeyPhrase = "Неуловимая Эскадра появилась в водах Карибского Моря.";
			break;

			case 2:
				sString = "Наверное, ты слыхал старую историю про Карибский Архипелаг? Её обычно картографы рассказывают. Нет? Ну, тогда, слушай. Коли пойдёшь ты на север из самого центра, увидишь ты чудище злобное, страшнее которого на всём белом свете не сыщещь. Ежели победишь ты злобное чудище и продолжишь свой путь в прежнем направлении, встретишь ты там самого длинного зверя. Одолев сие исчадие ада, поворачивай на восток. На востоке увидишь ты бронированного гада, которого испанцы и французы кличут черепахой. Ежели ты одолел сего монстра, то путь твой лежит на северо-восток, где найдёшь ты покой и тепло.";
				PChar.Dozor.Riddle.Type_2.Question = sString;
				PChar.Dozor.Riddle.Type_2.Answer_1 = "теркс";
				PChar.Dozor.Riddle.Type_2.Answer_2 = "залив южный";
				PChar.Dozor.Riddle.Type_2.KeyPhrase = "Отважный капитан ищет Неуловимую Эскадру.";
			break;

			case 3:
				sString = "- Вам всегда следует обращать внимание на первый и последний корабли каравана, капитан. Чаще всего именно они первыми подвергаются нападению. Запомнили?";
				sString += newStr() + "- Так точно, адмирал! Первый и последний!";
				sString += newStr() + "- Очень хорошо! А теперь, капитан, взгляните на эти слова и попробуйте понять, что здесь написано:";
				sString += newStr() + "ПНАСТРОТР";
				sString += newStr() + "ДОНОКАЧИ";
				sString += newStr() + "РЗЕВРЕ";
				sString += newStr() + "ЕПНТИЕЕР";
				sString += newStr() + "АДРУ";
				sString += newStr() + "ОНИРАЗНГ";
				sString += newStr() + "КАААТ";
				sString += newStr() + "- Ничего не понимаю, адмирал. Что это за бред?";
				sString += newStr() + "- Терпение, капитан, терпение. Немного усердия и вы увидите, что иногда и в бреду есть свой скрытый смысл. Вольно, капитан.";
				PChar.Dozor.Riddle.Type_3.Question = sString;
				PChar.Dozor.Riddle.Type_3.Answer_1 = "тортуга";
				PChar.Dozor.Riddle.Type_3.Answer_2 = "таверна";
				PChar.Dozor.Riddle.Type_3.KeyPhrase = "Отважный капитан напал на след Неуловимой Эскадры.";
			break;

			case 4:
				PChar.Dozor.Riddle.Type_4.Question = "picture";
				PChar.Dozor.Riddle.Type_4.Answer_1 = "виллемстад";
				PChar.Dozor.Riddle.Type_4.Answer_2 = "магазин";
				PChar.Dozor.Riddle.Type_4.KeyPhrase = "Отважный капитан вступил в схватку с Неуловимой Эскадрой.";
			break;

			case 5:
				sString = "Сначала они побывали в Порт-Рояле на Ямайке, затем сорвались на Эспаньолу, в испанский городок Санто-Доминго, потом побывали в Сан-Хуане, что на Пуэрто-Рико, после чего сорвались в английский Чарльстаун, остров Невис. Посетив после Невиса английскую колонию Антигуа, они побывали на предпоследнем острове - Мартинике, в пиратском Ле-Франсуа. А вот последнее задание они разгадать не смогли, представляете? Им попалось очень недоступное задание.";
				PChar.Dozor.Riddle.Type_5.Question = sString;
				PChar.Dozor.Riddle.Type_5.Answer_1 = "мария галанте";
				PChar.Dozor.Riddle.Type_5.Answer_2 = "мыс недоступный";
				PChar.Dozor.Riddle.Type_5.KeyPhrase = "Отважный капитан вступил в схватку с Неуловимой Эскадрой.";
			break;

			case 6:
				PChar.Dozor.Riddle.Type_6.Question = "text";
				PChar.Dozor.Riddle.Type_6.Answer_1 = "залив гибели";
				PChar.Dozor.Riddle.Type_6.KeyPhrase = "Неуловимая Эскадра потеряла флагман.";
			break;

			case 7:
				sString = "- Капитан! По курсу два маленьких пиратских корабля!";
				sString += newStr() + "- Доложите о количестве орудий на каждом из них!";
				sString += newStr() + "- На одном корабле 9 орудий, на другом 8!";
				sString += newStr() + "- Приготовиться к бою!";
				sString += newStr() + "А – 1.2 1.9 2.2 2.4";
				sString += newStr() + "Е – 2.7";
				sString += newStr() + "И – 1.5 1.7";
				sString += newStr() + "К – 1.8";
				sString += newStr() + "Л – 2.1";
				sString += newStr() + "М – 1.1 2.3";
				sString += newStr() + "Н – 1.6 2.5 2.8";
				sString += newStr() + "Р – 1.3";
				sString += newStr() + "Т – 1.4 2.6";
				PChar.Dozor.Riddle.Type_7.Question = sString;
				PChar.Dozor.Riddle.Type_7.Answer_1 = "мартиника";
				PChar.Dozor.Riddle.Type_7.Answer_2 = "пляж ламантен";
				PChar.Dozor.Riddle.Type_7.KeyPhrase = "Неуловимая Эскадра потерпела поражение.";
			break;

			case 8:
				sString = "Вот и окончен твой путь, дозорный! За этими воротами ждёт тебя дом, а в доме том, в сундуке запертом ждёт тебя твоя награда! Если знаешь, где они находятся, отправляйся туда немедленно, если же не знаешь, советую тебе быть внимательнее и чаще глазеть по сторонам, чтобы найти нужное место.";
				PChar.Dozor.Riddle.Type_8.Question = sString;
			break;
		}
	}
}

void DozorPrepare()
{
	pchar.quest.DozorPrepare.win_condition.l1 = "Rank";
	pchar.quest.DozorPrepare.win_condition.l1.value = 3;
	pchar.quest.DozorPrepare.win_condition.l1.operation = ">=";
	PChar.quest.DozorPrepare.function = "DozorPrepare_2";
}

void DozorPrepare_2(string qName)
{
	ref chr = GetCharacter(NPC_GenerateCharacter("Fabian Gronholm", "usurer_5", "man", "man", 1, PIRATE, -1, false));
	chr.name = GetConvertStrWithReplace("Variable_Quests_1", "Names.txt", "#space#", " ");
	chr.lastname = GetConvertStrWithReplace("Variable_Quests_2", "Names.txt", "#space#", " ");
	chr.Dialog.FileName = "DamnedDestiny\Dozor\Fabian_Gronholm.c";
	chr.Dialog.CurrentNode = "First Time";
	chr.greeting = "cit_quest";
	LAi_SetStayType(chr);
	LAi_SetImmortal(chr, true);

	ChangeCharacterAddressGroup(chr, "Pirates_town", "officers", "reload6_3");
}

void DozorCancel()
{
	ref chr = CharacterFromID("Fabian Gronholm");
	chr.LifeDay = 0;
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload4_back", "none", "", "", "", -1);

	PChar.quest.DozorClear.win_condition.l1 = "ExitFromLocation";
	PChar.quest.DozorClear.win_condition.l1.location = PChar.location;
	PChar.quest.DozorClear.function = "DozorClear";
}

void DozorClear(string qName)
{
	ref chr;
	if(GetCharacterIndex("Fabian Gronholm") != -1)
	{
		chr = CharacterFromID("Fabian Gronholm");
		chr.LifeDay = 0;
		ChangeCharacterAddress(chr, "None", "");
		LAi_KillCharacter(chr);
	}
	if(GetCharacterIndex("Fisher Pedro") != -1)
	{
		chr = CharacterFromID("Fisher Pedro");
		chr.LifeDay = 0;
		ChangeCharacterAddress(chr, "None", "");
		LAi_KillCharacter(chr);
	}
	if(GetCharacterIndex("Spanch Bob") != -1)
	{
		chr = CharacterFromID("Spanch Bob");
		chr.LifeDay = 0;
		ChangeCharacterAddress(chr, "None", "");
		LAi_KillCharacter(chr);
	}
	if(GetCharacterIndex("Dozor_Ship") != -1)
	{
		chr = CharacterFromID("Dozor_Ship");
		chr.LifeDay = 0;
		ChangeCharacterAddress(chr, "None", "");
		LAi_KillCharacter(chr);
	}
	if(GetCharacterIndex("Dozor NoName") != -1)
	{
		chr = CharacterFromID("Dozor NoName");
		chr.LifeDay = 0;
		ChangeCharacterAddress(chr, "None", "");
		LAi_KillCharacter(chr);
	}

	for(int i=1; i<=3; i++)
	{
		if(GetCharacterIndex("Dozor Grot Agent Killer " + i) != -1)
		{
			chr = CharacterFromID("Dozor Grot Agent Killer " + i);
			chr.LifeDay = 0;
			ChangeCharacterAddress(chr, "None", "");
			LAi_KillCharacter(chr);
		}
	}

	if(CheckAttribute(PChar, "Dozor.CabinID")) { DeleteAttribute(PChar, "Dozor.CabinID"); }
	ClearQuestBoxStay("HouseDozor");
}

void DozorWait()
{
	SetTimerFunction("DozorClear", 0, 0, 90);
}

void DozorStart()
{
	ref chr = CharacterFromID("Fabian Gronholm");
	chr.LifeDay = 0;
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload4_back", "none", "", "", "", -1);

	PChar.quest.DozorClear.over = "yes";

	PChar.Dozor = "1";
	PChar.Dozor.Riddle.CurType = 1;
	PChar.Dozor.Riddle.CanInterface = 1;

	SetQuestHeader("Dozor");
	AddQuestRecord("Dozor", "1");
	AddQuestUserData("Dozor", "sSex", GetSexPhrase("","а"));

	TakeNItems(PChar, "Dozor_Mekakhrom", 1);
	
	for(int d=1; d<=8; d++)	{DozorSetRiddleQuestion(d);}
}

void DozorToPuertoRicoShore()
{
	AddQuestRecord("Dozor", "2");

	string sPhrase = PChar.Dozor.Riddle.Type_1.KeyPhrase;
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	PChar.Dozor.Riddle.CanInterface = 0;
	PChar.Dozor = "2";

	ref chr = GetCharacter(NPC_GenerateCharacter("Fisher Pedro", "shipowner_4", "man", "man", 1, PIRATE, -1, false));
	chr.name = GetConvertStrWithReplace("Variable_Quests_3", "Names.txt", "#space#", " ");
	chr.lastname = GetConvertStrWithReplace("Variable_Quests_4", "Names.txt", "#space#", " ");
	chr.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
	chr.Dialog.CurrentNode = "Fisher_Pedro_1";
	chr.greeting = "Gr_Fisher";
	LAi_SetCitizenType(chr);
	LAi_SetImmortal(chr, true);

	ChangeCharacterAddressGroup(chr, "Shore45", "goto", "goto8");
}

void DozorFisherPedroExit()
{
	PChar.Dozor = "3";
	TakeNItems(PChar, "Dozor_Mekakhrom", -1);
	AddQuestRecord("Dozor", "3");

	PChar.Dozor.Riddle.CurType = 2;
	PChar.Dozor.Riddle.CanInterface = 1;

	ref chr = CharacterFromID("Fisher Pedro");
	chr.LifeDay = 0;
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload1_back", "none", "", "", "", -1);
}

void DozorToTerks()
{
	PChar.Dozor = "4";
	AddQuestRecord("Dozor", "4");

	string sPhrase = PChar.Dozor.Riddle.Type_2.KeyPhrase;
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	PChar.Dozor.Riddle.CanInterface = 0;

	PChar.quest.DozorInTerks.win_condition.l1 = "location";
	PChar.quest.DozorInTerks.win_condition.l1.location = "Shore57";
	PChar.quest.DozorInTerks.function = "DozorInTerks";
}

void DozorInTerks(string qName)
{
	PChar.Dozor = "5";
	AddQuestRecord("Dozor", "5");
	TakeNItems(PChar, "Dozor_Mekakhrom", -1);

	PChar.quest.DozorPreTerksInGrot.win_condition.l1 = "location";
	PChar.quest.DozorPreTerksInGrot.win_condition.l1.location = "Terks_Grot";
	PChar.quest.DozorPreTerksInGrot.function = "DozorPreTerksInGrot";
}

void DozorPreTerksInGrot(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_SetActorType(PChar);
	DoQuestFunctionDelay("DozorTerksInGrot", 0.1);
}

void DozorTerksInGrot(string _tmp)
{
	PChar.Dozor = "6";

	StartQuestMovie(true, true, true);
	InterfaceStates.Buttons.Save.enable = false;

	SendMessage(&locCamera, "lfffl", MSG_CAMERA_TOPOS, 1, 3, 9, false);

	ref chr;

	int iRank = GetRank(PChar, 5) + MOD_SKILL_ENEMY_RATE;
	string sLocator = "";
	string sModel = "";
	for(int i=1; i<=3; i++)
	{
		switch(i)
		{
			case 1: sLocator = "monster1"; sModel = "pirate_" + (rand(24)+1); break;
			case 2: sLocator = "monster2"; sModel = "pirate_" + (rand(24)+1); break;
			case 3: sLocator = "monster3"; sModel = "citiz_" + (rand(11)+1); break;
		}

		chr = GetCharacter(NPC_GenerateCharacter("Dozor Grot Agent Killer " + i, sModel, "man", "man", iRank, PIRATE, 0, true));
		ChangeCharacterAddressGroup(chr, "Terks_Grot", "monsters", sLocator);
		chr.lastname = "";
		chr.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
		chr.Dialog.CurrentNode = "Grot_Agent_Killers_1";
		chr.greeting = "Gr_AllowToDump";
		LAi_SetStayType(chr);

		if(i == 1)
		{
			//TakeNItems(chr, "Dozor_Mekakhrom", 1);
			//chr.SaveItemsForDead   = true;
			chr.name = GetConvertStrWithReplace("Variable_Quests_5", "Names.txt", "#space#", " ");
		}
		else
		{
			if(i != 3)
			{
				chr.name = GetConvertStrWithReplace("Variable_Quests_6", "Names.txt", "#space#", " ");
			}
		}

		if(i == 3)
		{
			LAi_SetActorType(chr);
			LAi_ActorSetLayMode(chr);
			LAi_SetImmortal(chr, true);
			LaunchBlood(chr, 5.0, true);
		}
	}

	LAi_SetActorType(CharacterFromID("Dozor Grot Agent Killer 1"));
	LAi_SetActorType(CharacterFromID("Dozor Grot Agent Killer 2"));
	LAi_SetActorType(PChar);

	LAi_ActorTurnToCharacter(CharacterFromID("Dozor Grot Agent Killer 1"), CharacterFromID("Dozor Grot Agent Killer 2"));
	LAi_ActorTurnToCharacter(CharacterFromID("Dozor Grot Agent Killer 2"), CharacterFromID("Dozor Grot Agent Killer 1"));
	LAi_ActorTurnToCharacter(PChar, CharacterFromID("Dozor Grot Agent Killer 1"));

	DoQuestFunctionDelay("DozorDialogInTerksGrot", 2.5);
}

void DozorDialogInTerksGrot(string _tmp)
{
	SetDialogCharacter2Character(PChar, CharacterFromID("Dozor Grot Agent Killer 1"), 0.1, true);
}

void DozorBattleInTerksGrot()
{
	locCameraFollow();
	EndQuestMovie();
	InterfaceStates.Buttons.Save.enable = true;

	LAi_SetPlayerType(PChar);
	LAi_SetFightMode(pchar, true);
	LAi_SetWarriorType(CharacterFromID("Dozor Grot Agent Killer 1"));
	LAi_SetWarriorType(CharacterFromID("Dozor Grot Agent Killer 2"));
	LAi_group_MoveCharacter(CharacterFromID("Dozor Grot Agent Killer 1"), "EnemyFight");
	LAi_group_MoveCharacter(CharacterFromID("Dozor Grot Agent Killer 2"), "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	PChar.quest.DozorBattleInTerksGrotWinner.win_condition.l1 = "NPC_Death";
	PChar.quest.DozorBattleInTerksGrotWinner.win_condition.l1.character = "Dozor Grot Agent Killer 1";
	PChar.quest.DozorBattleInTerksGrotWinner.win_condition.l2 = "NPC_Death";
	PChar.quest.DozorBattleInTerksGrotWinner.win_condition.l2.character = "Dozor Grot Agent Killer 2";
	PChar.quest.DozorBattleInTerksGrotWinner.function = "DozorBattleInTerksGrotWinner";
}

void DozorBattleInTerksGrotWinner(string qName)
{
	//PlayStereoSound("new_round");
	//Log_Info(GetConvertStrWithReplace("Variable_Quests_1", "Logs.txt", "#space#", " "));

	DozorTerksGrotFindMekakhrom("");
	TakeNItems(PChar, "Dozor_Mekakhrom", 1);

	/*PChar.quest.DozorTerksGrotFindMekakhrom.win_condition.l1 = "item";
	PChar.quest.DozorTerksGrotFindMekakhrom.win_condition.l1.item = "Dozor_Mekakhrom";
	PChar.quest.DozorTerksGrotFindMekakhrom.function = "DozorTerksGrotFindMekakhrom";*/
}

void DozorTerksGrotFindMekakhrom(string qName)
{
	PChar.Dozor = "7";
	AddQuestRecord("Dozor", "6");
	AddQuestUserData("Dozor", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("Dozor", "sSex2", GetSexPhrase("ёл","ла"));

	PChar.Dozor.Riddle.CurType = 3;
	PChar.Dozor.Riddle.CanInterface = 1;

	chrDisableReloadToLocation = false;
}

void DozorToTortugaTavern()
{
	PChar.Dozor = "8";
	AddQuestRecord("Dozor", "7");

	string sPhrase = PChar.Dozor.Riddle.Type_3.KeyPhrase;
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	PChar.Dozor.Riddle.CanInterface = 0;
}

void DozorTortugaTavernGetItem()
{
	PChar.Dozor = "9";
	AddQuestRecord("Dozor", "8");

	TakeNItems(PChar, "Dozor_Mekakhrom", -1);

	PChar.Dozor.Riddle.CurType = 4;
	PChar.Dozor.Riddle.CanInterface = 1;
}

void DozorToVillemstadStore()
{
	PChar.Dozor = "10";
	AddQuestRecord("Dozor", "9");

	string sPhrase = PChar.Dozor.Riddle.Type_4.KeyPhrase;
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	PChar.Dozor.Riddle.CanInterface = 0;
}

void DozorToGuadeloupeShore()
{
	PChar.Dozor = "12";
	AddQuestRecord("Dozor", "11");
	AddQuestUserData("Dozor", "sSex1", GetSexPhrase("ен","на"));

	string sPhrase = PChar.Dozor.Riddle.Type_5.KeyPhrase;
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	ref chr = GetCharacter(NPC_GenerateCharacter("Spanch Bob", "citiz_5", "man", "man", 1, PIRATE, -1, false));
	chr.name = GetConvertStrWithReplace("Variable_Quests_7", "Names.txt", "#space#", " ");
	chr.lastname = GetConvertStrWithReplace("Variable_Quests_8", "Names.txt", "#space#", " ");
	chr.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
	chr.Dialog.CurrentNode = "Spanch_Bob_1";
	chr.greeting = "Gr_Crazy";
	LAi_SetCitizenType(chr);
	LAi_SetImmortal(chr, true);

	ChangeCharacterAddressGroup(chr, "Shore31", "goto", "goto4");
}

void DozorGuadeloupeShoreGetTask()
{
	PChar.Dozor = "13";
	AddQuestRecord("Dozor", "12");
	AddQuestUserData("Dozor", "sSex", GetSexPhrase("","а"));
}

void DozorToDeadShoreInMein()
{
	ref chr = CharacterFromID("Spanch Bob");
	chr.LifeDay = 0;
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload1_back", "none", "", "", "", -1);

	PChar.Dozor = "14";
	AddQuestRecord("Dozor", "13");

	string sPhrase = PChar.Dozor.Riddle.Type_6.KeyPhrase;
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	SetQuestBoxItems("Shore_ship2", "Dozor_Mekakhrom", 1);
	PChar.quest.DozorInDeadShoreInMein.win_condition.l1 = "location";
	PChar.quest.DozorInDeadShoreInMein.win_condition.l1.location = "Shore_ship2";
	PChar.quest.DozorInDeadShoreInMein.function = "DozorInDeadShoreInMein";
}

void DozorInDeadShoreInMein(string qName)
{
	PChar.Dozor = "15";
	AddQuestRecord("Dozor", "14");
	chrDisableReloadToLocation = true;

	PChar.quest.DozorInDeadShoreInMeinFindItem.win_condition.l1 = "item";
	PChar.quest.DozorInDeadShoreInMeinFindItem.win_condition.l1.item = "Dozor_Mekakhrom";
	PChar.quest.DozorInDeadShoreInMeinFindItem.function = "DozorInDeadShoreInMeinFindItem";
}

void DozorInDeadShoreInMeinFindItem(string qName)
{
	ClearQuestBoxStay("Shore_ship2");
	chrDisableReloadToLocation = false;

	PChar.Dozor = "16";
	AddQuestRecord("Dozor", "15");
	AddQuestUserData("Dozor", "sSex2", GetSexPhrase("ёл","ла"));

	PChar.Dozor.Riddle.CurType = 7;
	PChar.Dozor.Riddle.CanInterface = 1;
}

void DozorToMartiniqueShore()
{
	PChar.Dozor = "17";
	AddQuestRecord("Dozor", "16");
	PChar.Dozor.Riddle.CanInterface = 0;

	string sPhrase = PChar.Dozor.Riddle.Type_7.KeyPhrase;
	AddQuestUserData("Dozor", "sKeyPhrase", sPhrase);

	Group_FindOrCreateGroup("DozorShip");
	Group_SetType("DozorShip","war");

	int iRank = GetRank(PChar, 15) + MOD_SKILL_ENEMY_RATE;
	ref sld = GetCharacter(NPC_GenerateCharacter("Dozor_Ship", "officer_4", "man", "man", iRank, PIRATE, -1, true));
	FantomMakeCoolestSailor(sld, SHIP_POLACRE, GetConvertStr("Variable_Quests_1", "ShipNames.txt"), CANNON_TYPE_CULVERINE_LBS12, 70, 70, 70);
	// FantomMakeCoolSailor(sld, SHIP_DERFFLINGER, "Дозорный", CANNON_TYPE_CULVERINE_LBS24, 70, 70, 70); // LEO: Нихуя ты сделал изи флейт, прям БМС стайл. У него блять в ините 16 калибр, а нахуя ты ему 24фт воткнул? Изиблятьфлейт.жепеге
	sld.name = "Джастин";
	sld.lastname = "Батт";
	sld.greeting = "Gr_UnpleasantCaptain";
	sld.CaptanId = "";
	sld.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
	sld.Dialog.CurrentNode = "Justin_Butt_1";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");

	// фиксируем некоторые статы для полакра -->
	realships[sti(sld.ship.type)].SpeedRate = 16.2; //Уведичиваем скорость
	realships[sti(sld.ship.type)].TurnRate  = 22; //Увеличиваем маневренность
	realships[sti(sld.ship.type)].HP = 2500; //Фиксируем ХП
	realships[sti(sld.ship.type)].Capacity = 1500; //Фиксируем трюм
	realships[sti(sld.ship.type)].MastMultiplier = 1.3; //Упрочняем мачты

	//Уменьшаем команду, как плату за предыдущие статы.
	realships[sti(sld.ship.type)].MaxCrew = 200;
	realships[sti(sld.ship.type)].MinCrew = 50;
	realships[sti(sld.ship.type)].OptCrew = 150;
	// фиксируем некоторые статы для полакра <--

	SetCrewQuantity(sld,GetMaxCrewQuantity(sld)); //Gregg - режем команду, а то прямо как у БМС вышел адовый оверперегруз
	sld.skill.Sailing = 50; //подрезаем наву
	sld.skill.Accuracy = 50; //подрезаем меткость
	sld.skill.Cannons = 90;

	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	SetGeraldDetails(sld, 3, rand(7), "", "pir_" + (rand(5)+1));

	Group_AddCharacter("DozorShip", "Dozor_Ship");
	Group_SetType("DozorShip", "pirate");
	Group_SetGroupCommander("DozorShip", "Dozor_Ship");
	Group_SetAddress("DozorShip", "Martinique", "quest_ships", "quest_ship_10");
	Group_SetTaskAttack("DozorShip", PLAYER_GROUP);

	PChar.quest.DozorBattleWithDozorShip.win_condition.l1 = "location";
	PChar.quest.DozorBattleWithDozorShip.win_condition.l1.location = "Martinique";
	PChar.quest.DozorBattleWithDozorShip.function = "DozorBattleWithDozorShip";
}

void DozorBattleWithDozorShip(string qName)
{
	PChar.Dozor = "18";
	AddQuestRecord("Dozor", "17");

	TakeNItems(PChar, "Dozor_Mekakhrom", -1);

	PChar.quest.DozorDeadDozorShip.win_condition.l1 = "Group_Death";
	PChar.quest.DozorDeadDozorShip.win_condition.l1.group = "DozorShip";
	PChar.quest.DozorDeadDozorShip.function = "DozorDeadDozorShip";
}

void DozorDeadDozorShip(string qName)
{
	string sCabin = "";
	if(CheckAttribute(PChar, "Dozor.CabinID"))
	{
		sCabin = PChar.Dozor.CabinID;

		if(FindLocation(sCabin) != -1)
		{
			if(CheckAttribute(&Locations[FindLocation(sCabin)], "box1.items.Dozor_Key"))
			{
				DeleteAttribute(&Locations[FindLocation(sCabin)], "box1.items.Dozor_Key");
			}
			if(CheckAttribute(&Locations[FindLocation(sCabin)], "box1.items.Dozor_Mekakhrom"))
			{
				DeleteAttribute(&Locations[FindLocation(sCabin)], "box1.items.Dozor_Mekakhrom");
			}
		}
	}

	if(GetCharacterItem(PChar, "Dozor_Mekakhrom") >= 1 && GetCharacterItem(PChar, "Dozor_Key") >= 1)
	{
		DozorToHouse();
	}
	else
	{
		if(GetCharacterItem(PChar, "Dozor_Mekakhrom") <= 0 && GetCharacterItem(PChar, "Dozor_Key") <= 0)
		{
			AddQuestRecord("Dozor", "18");
		}
		else
		{
			if(GetCharacterItem(PChar, "Dozor_Mekakhrom") <= 0 && GetCharacterItem(PChar, "Dozor_Key") >= 1)
			{
				AddQuestRecord("Dozor", "18");
			}
			else
			{
				if(GetCharacterItem(PChar, "Dozor_Mekakhrom") >= 0 && GetCharacterItem(PChar, "Dozor_Key") <= 0)
				{
					AddQuestRecord("Dozor", "21");
					AddQuestUserData("Dozor", "sSex", GetSexPhrase("","а"));
				}
			}
		}

		PChar.Dozor = "END";
		DozorClear("");
		TakeNItems(PChar, "Dozor_Mekakhrom", -1);
		TakeNItems(PChar, "Dozor_Key", -1);
		CloseQuestHeader("Dozor");
		pchar.questdata.Dozor = 1;
	}
}

void DozorToHouse()
{
	PChar.Dozor = "19";
	AddQuestRecord("Dozor", "19");
	AddQuestUserData("Dozor", "sSex", GetSexPhrase("","а"));

	PChar.Dozor.Riddle.CurType = 8;
	PChar.Dozor.Riddle.CanInterface = 1;

	Locations[FindLocation("Charles_town")].reload.l29.disable = 0;
	Locations[FindLocation("Charles_town")].reload.l29.go = "HouseDozor";

	/*PChar.GenQuestBox.HouseDozor = true;
	PChar.GenQuestBox.HouseDozor.box2.items.Dozor_Storm = 1;
	PChar.GenQuestBox.HouseDozor.box2.items.Dozor_HorseShoe = 1;
	PChar.GenQuestBox.HouseDozor.box2.items.Dozor_Mirror = 1;
	PChar.GenQuestBox.HouseDozor.box2.money = 100000;
	PChar.GenQuestBox.HouseDozor.stay = true;*/

	//SetQuestFunction("DozorToHouseKeyInit", "DozorToHouseKeyInit", "l", "HouseDozor");

	PChar.quest.DozorLastDialog.win_condition.l1 = "locator";
	PChar.quest.DozorLastDialog.win_condition.l1.location = "HouseDozor";
	PChar.quest.DozorLastDialog.win_condition.l1.locator_group = "box";
	PChar.quest.DozorLastDialog.win_condition.l1.locator = "box2";
	PChar.quest.DozorLastDialog.function = "DozorLastDialog";
}

void DozorToHouseKeyInit(string qName)
{
	Locations[FindLocation("HouseDozor")].box2.key = "Dozor_Key";
	Locations[FindLocation("HouseDozor")].box2.key.delItem = true;
}

void DozorLastDialog(string qName)
{
	TakeNItems(PChar, "Dozor_Key", -1);
	TakeNItems(PChar, "Dozor_Mekakhrom", -1);

	ref loc = LocFromID("HouseDozor");
	loc.box2.items.Dozor_Storm = 1;
	loc.box2.items.Dozor_HorseShoe = 1;
	loc.box2.items.Dozor_Mirror = 1;
	loc.box2.money = 100000;

	StartQuestMovie(true, true, true);
	InterfaceStates.Buttons.Save.enable = false;

	ref chr = GetCharacter(NPC_GenerateCharacter("Dozor NoName", "officer_6", "man", "man", 1, PIRATE, 0, false));
	chr.name = GetConvertStrWithReplace("Variable_Quests_11", "Names.txt", "#space#", " ");
	chr.lastname = "";
	chr.greeting = "cit_common1";
	chr.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
	chr.Dialog.CurrentNode = "NoName_1";
	LAi_SetImmortal(chr, true);

	ChangeCharacterAddressGroup(chr, PChar.location, "reload", "reload1");
	SetDialogCharacter2Character(PChar, chr, 5.0, true);
}

void DozorHappyEnd()
{
	EndQuestMovie();
	InterfaceStates.Buttons.Save.enable = true;

	PChar.Dozor = "END";
	AddQuestRecord("Dozor", "20");
	CloseQuestHeader("Dozor");
	pchar.questdata.Dozor = 1;

	LAi_SetPlayerType(PChar);

	ref chr = CharacterFromID("Dozor NoName");
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload1", "none", "", "", "", -1);

	Locations[FindLocation("Charles_town")].reload.l29.disable = 1;

	PChar.quest.DozorClear.win_condition.l1 = "ExitFromLocation";
	PChar.quest.DozorClear.win_condition.l1.location = PChar.location;
	PChar.quest.DozorClear.function = "DozorClear";

	AddSimpleRumourToAllNations(LinkRandPhrase(GetConvertStrWithReplace("Variable_Quests_1", "AddRumours.txt", "#space#", " "), GetConvertStrWithReplace("Variable_Quests_2", "AddRumours.txt", "#space#", " "), GetConvertStrWithReplace("Variable_Quests_3", "AddRumours.txt", "#space#", " ")) + GetConvertStrWithReplace("Variable_Quests_4", "AddRumours.txt", "#space#", " ") + GetFullName(PChar) + GetConvertStrWithReplace("Variable_Quests_5", "AddRumours.txt", "#space#", " "), 5, 1);
}

/////////////////////////////////////////////////////////////////////////////////////
// ЗАГАДОЧНЫЙ ОСТРОВ
/////////////////////////////////////////////////////////////////////////////////////
void MysteriousIslandPrepare()
{	
	PChar.MysteriousIsland.FindForser.Citizen = false;
	PChar.MysteriousIsland.FindForser.Tavern = false;
	PChar.MysteriousIsland.FindForser.Store = false;
	PChar.MysteriousIsland.FindForser.PortOffice = false;
	PChar.MysteriousIsland.FindForser.Church = false;
	PChar.MysteriousIsland.FindForser.Brothel = false;
	PChar.MysteriousIsland.DisableBoxOpen = false;
	PChar.MysteriousIsland.Action = false;
	
	PChar.MysteriousIsland = "1";
	
	FreeSitLocator("Bridgetown_tavern", "sit_front3");
}

void MysteriousIslandTalkWithSmith()
{
	LAi_Fade("", "");
	DoQuestFunctionDelay("MysteriousIslandTalkWithSmith_2", 0.5);
}

void MysteriousIslandTalkWithSmith_2()
{	
	ref chr = CharacterFromID("Jimm Smith");
	chr.Dialog.CurrentNode = "2";
	
	FreeSitLocator(PChar.location, "sit_front3");
	ChangeCharacterAddressGroup(PChar, PChar.location, "sit", "sit_front3");
	LAi_SetSitType(PChar);
	LAi_SetActorType(chr);
	LAi_ActorSetSitMode(chr);
	LAi_ActorDialogNow(chr, PChar, "", -1);
}

void MysteriousIslandToBarmen()
{
	LAi_Fade("", "");
	DoQuestFunctionDelay("MysteriousIslandToBarmen_2", 0.5);
}

void MysteriousIslandToBarmen_2()
{	
	ref chr = CharacterFromID("Jimm Smith");
	LAi_SetSitType(chr);
	
	LAi_SetPlayerType(PChar);
	ChangeCharacterAddressGroup(PChar, PChar.location, "tables", "stay8");
	
	PChar.MysteriousIsland = "2";
	SetQuestHeader("KPS_MysteriousIsland");
	AddQuestRecord("KPS_MysteriousIsland", "1");
}

void MysteriousIslandToCharlesChurch()
{
	ref chr = CharacterFromID("Jimm Smith");
	chr.LifeDay = 0;
	
	PChar.MysteriousIsland = "3";
	AddQuestRecord("KPS_MysteriousIsland", "2");
}

void MysteriousIslandToCharlesTown()
{
	PChar.MysteriousIsland = "4";
	AddQuestRecord("KPS_MysteriousIsland", "3");
	
	ref chr = CharacterFromID("Charles_Priest");
	AddQuestUserData("KPS_MysteriousIsland", "sPriestName", chr.name);

	SetQuestFunction("MysteriousIslandInCharlesTown", "MysteriousIslandInCharlesTown", "l", "Charles_town");
}

void MysteriousIslandInCharlesTown(string qName)
{
	chrDisableReloadToLocation = true;
	ref chr = GetCharacter(NPC_GenerateCharacter("Zhofrua Djubben", "officer_16", "man", "man", sti(PChar.rank)+10, PIRATE, -1, true));
	chr.name = GetConvertStrWithReplace("Variable_Quests_12", "Names.txt", "#space#", " ");
	chr.lastname = GetConvertStrWithReplace("Variable_Quests_13", "Names.txt", "#space#", " ");
	chr.greeting = "Gr_questOfficer";
	chr.Dialog.FileName = "Quest\KPS\MysteriousIsland\Zhofrua Djubben.c";
	chr.Dialog.CurrentNode = "1";
	LAi_SetImmortal(chr, true);
	FantomMakeCoolFighter(chr, sti(PChar.rank)+10, 85, 85, "", "", 0);
	LAi_NPC_Equip(chr, sti(PChar.rank)+10, true, true);
	SetFoodToCharacter(chr, 5, 50);
	ChangeCharacterAddressGroup(chr, "Charles_town", "goto", "goto19");
	SetDialogCharacter2Character(PChar, chr, 60.0, false);
}

void MysteriousIslandToCharlesExitTown()
{
	chrDisableReloadToLocation = false;

	ref chr = CharacterFromID("Zhofrua Djubben");
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "gate_back", "none", "", "", "", -1);

	SetQuestFunction("MysteriousIslandInCharlesExitTown", "MysteriousIslandInCharlesExitTown", "l", "Charles_ExitTown");
}

void MysteriousIslandInCharlesExitTown(string qName)
{
	chrDisableReloadToLocation = true;
	DeleteAllOfficersFromLocation();
	bDisableOfficers = true;
		
	ref chr = CharacterFromID("Zhofrua Djubben");
	chr.Dialog.CurrentNode = "3";
	ChangeCharacterAddressGroup(chr, "Charles_ExitTown", "goto", "goto2");
	SetDialogCharacter2Character(PChar, chr, 25.0, false);
}

void MysteriousIslandFightWithDubben()
{
	ref chr = CharacterFromID("Zhofrua Djubben");
	float fHp = LAi_GetCharacterMaxHP(chr) + 300;

	LAi_SetHP(chr, fHp, fHp);
	LAi_SetImmortal(chr, false);
	
	LAi_SetWarriorType(chr);
	LAi_group_MoveCharacter(chr, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	Lai_SetCheckMinHP(chr, 5.0, true, "KPS_MysteriousIsland_1");
	
	LAi_SetFightMode(pchar, true);
}

void MysteriousIslandRetryTalkWithDubben()
{
	LAi_Fade("", "");
	LAi_SetFightMode(pchar, false);
	
	ref chr = CharacterFromID("Zhofrua Djubben");
	chr.Dialog.CurrentNode = "9";
	SetDialogCharacter2Character(PChar, chr, 10.0, false);
}

void MysteriousIslandToSantoDomingo()
{
	chrDisableReloadToLocation = false;
	
	ref chr = CharacterFromID("Zhofrua Djubben");
	LAi_RemoveCheckMinHP(chr);
	LAi_UseAtidoteBottle(chr);
	LAi_SetImmortal(chr, true);
	
	SetCharacterRemovable(chr, false);
	AddPassenger(PChar, chr, 0);

	PChar.quest.KPS_MysteriousIsland_ZDvkaute.win_condition.l1 = "ExitFromLocation";
	PChar.quest.KPS_MysteriousIsland_ZDvkaute.win_condition.l1.location = PChar.location;
	PChar.quest.KPS_MysteriousIsland_ZDvkaute.win_condition = "KPS_MysteriousIsland_ZDvkaute";
	
	LAi_SetActorType(chr);
	LAi_ActorFollowEverywhere(chr, "", -1);
	//LAi_ActorRunToLocation(chr, "reload", "reload1", "", "", "", "", -1); 
	
	//LAi_group_MoveCharacter(chr, LAI_GROUP_DEFAULT);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
	
	PChar.MysteriousIsland = "5";
	AddQuestRecord("KPS_MysteriousIsland", "4");
	AddQuestUserData("KPS_MysteriousIsland", "sSex", GetSexPhrase("","а"));
}

void MysteriousIslandWaitDiegoMarkes()
{
	PChar.MysteriousIsland = "6";
	AddQuestRecord("KPS_MysteriousIsland", "5");
	AddQuestUserData("KPS_MysteriousIsland", "sSex", GetSexPhrase("","а"));

	SetTimerFunction("MysteriousIslandWaitDayDiegoMarkes", 0, 0, 1);
}

void MysteriousIslandWaitDayDiegoMarkes(string qName)
{
	SetQuestFunction("MysteriousIslandMeetingDiegoMarkes", "MysteriousIslandMeetingDiegoMarkes", "l", "SantoDomingo_bank");
}

void MysteriousIslandMeetingDiegoMarkes(string qName)
{
	chrDisableReloadToLocation = true;
	
	ref chr = GetCharacter(NPC_GenerateCharacter("Diego Markes", "prison_5", "man", "man", 1, PIRATE, 0, false));
	chr.name = GetConvertStrWithReplace("Variable_Quests_14", "Names.txt", "#space#", " ");
	chr.lastname = GetConvertStrWithReplace("Variable_Quests_15", "Names.txt", "#space#", " ");
	chr.greeting = "Gr_prison";
	chr.Dialog.FileName = "Quest\KPS\MysteriousIsland\Jimm Smith.c";
	chr.Dialog.CurrentNode = "9";
	LAi_SetImmortal(chr, true);
	ChangeCharacterAddressGroup(chr, "SantoDomingo_bank", "reload", "reload2");
	SetDialogCharacter2Character(PChar, chr, 15.0, false);
}

void MysteriousIslandFirstVisit()
{
	chrDisableReloadToLocation = false;
	
	ref chr = CharacterFromID("Diego Markes");
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload1_back", "none", "", "", "", -1);

	PChar.MysteriousIsland = "7";
	AddQuestRecord("KPS_MysteriousIsland", "6");
	
	Island_SetReloadEnableGlobal("StLucia", false);
	PChar.MysteriousIsland.StLuciaHide = true;
	SetQuestFunction("MysteriousIslandNoIsland", "MysteriousIslandNoIsland", "l", "StLucia");
}

void MysteriousIslandNoIsland(string qName)
{
	PChar.MysteriousIsland = "9";
	AddQuestRecord("KPS_MysteriousIsland", "7");
}

void MysteriousIslandBattleAtNoIsland(string qName)
{
	bQuestDisableMapEnter = true;
	Island_SetReloadEnableGlobal("StLucia", false);

	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 15;
	ref sld;
	
	Group_FindOrCreateGroup("MysteriousIslandBattleShip");
	Group_SetType("MysteriousIslandBattleShip", "war");
	
	sld = GetCharacter(NPC_GenerateCharacter("MysteriousIslandBattleShip", "skel1", "skeleton", "skeleton", iRank, PIRATE, -1, true));
	FantomMakeCoolSailor(sld, SHIP_BLACKPEARL, GetConvertStr("Variable_Quests_2", "ShipNames.txt"), CANNON_TYPE_CANNON_LBS32, 100, 95, 95);
	FantomMakeCoolFighter(sld, iRank, 80, 80, "", "", 300);
	sld.name = GetConvertStrWithReplace("Variable_Quests_16", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_Quests_17", "Names.txt", "#space#", " ");
	sld.FaceId = 351;
	//LAi_NPC_Equip(sld, iRank, true, true);
	//SetGeraldDetails(sld, 2, 2, "", "pir_" + (rand(5)+1));
	Group_AddCharacter("MysteriousIslandBattleShip", "MysteriousIslandBattleShip");
	Group_SetGroupCommander("MysteriousIslandBattleShip", "MysteriousIslandBattleShip");
	Group_SetTaskAttack("MysteriousIslandBattleShip", PLAYER_GROUP);
	Group_SetAddress("MysteriousIslandBattleShip", "StLucia", "quest_ships", "quest_ship_1");
	Group_LockTask("MysteriousIslandBattleShip");
	sld.GenQuest.CrewSkelModeClassic = true;
	
	PChar.quest.MysteriousIslandBattleAtNoIslandWin.win_condition.l1 = "Group_Death";
	PChar.quest.MysteriousIslandBattleAtNoIslandWin.win_condition.l1.group = "MysteriousIslandBattleShip";
	PChar.quest.MysteriousIslandBattleAtNoIslandWin.function = "MysteriousIslandBattleAtNoIslandWin";
}

void MysteriousIslandBattleAtNoIslandWin(string qName)
{
	bQuestDisableMapEnter = false;
	Island_SetReloadEnableGlobal("StLucia", true);

	SetQuestFunction("MysteriousIslandInGrotto", "MysteriousIslandInGrotto", "l", "SantaQuiteriaInside");
}

void MysteriousIslandFindDavyForser()
{
	PChar.MysteriousIsland = "10";
	AddQuestRecord("KPS_MysteriousIsland", "9");
}

void MysteriousIslandToLaVega()
{
	PChar.MysteriousIsland = "11";
	AddQuestRecord("KPS_MysteriousIsland", "10");
	SetQuestFunction("MysteriousIslandInLaVega", "MysteriousIslandInLaVega", "l", "LaVega_town");
}

void MysteriousIslandInLaVega(string qName)
{
	PChar.MysteriousIsland = "12";
	AddQuestRecord("KPS_MysteriousIsland", "11");

	bDisableLandEncounters = true;
	SetQuestFunction("MysteriousIslandMeetingDavyForser", "MysteriousIslandMeetingDavyForser", "l", "Hispaniola_CaveEntrance");
}

void MysteriousIslandMeetingDavyForser(string qName)
{
	InterfaceStates.Buttons.Save.enable = false;	
	chrDisableReloadToLocation = true;
	DeleteAllOfficersFromLocation();
	bDisableOfficers = true;
	
	ref chr = CharacterFromID("Zhofrua Djubben");
	ChangeCharacterAddressGroup(chr, "Hispaniola_CaveEntrance", "reload", "reload2_back");
	LAi_ActorFollowEverywhere(chr, "", -1);
	
	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 15;
	chr = GetCharacter(NPC_GenerateCharacter("Davy Forser", "officer_7", "man", "man", iRank, PIRATE, 0, true));
	chr.name = GetConvertStrWithReplace("Variable_Quests_18", "Names.txt", "#space#", " ");
	chr.lastname = GetConvertStrWithReplace("Variable_Quests_19", "Names.txt", "#space#", " ");
	chr.greeting = "Gr_ArenaMember";
	chr.Dialog.FileName = "Quest\KPS\MysteriousIsland\Characters.c";
	chr.Dialog.CurrentNode = "1";
	chr.SaveItemsForDead = true;
	FantomMakeCoolFighter(chr, iRank, 100, 100, "topor2", "pistol6", 500);
	SetFoodToCharacter(chr, 2, 15);
	LAi_SetImmortal(chr, true);
	ChangeCharacterAddressGroup(chr, "Hispaniola_CaveEntrance", "reload", "reload1_back");
	SetDialogCharacter2Character(PChar, chr, 20.0, false);
}

void MysteriousIslandFightDavyForser()
{
	InterfaceStates.Buttons.Save.enable = true;
	LAi_SetFightMode(pchar, true);

	ref chr = CharacterFromID("Zhofrua Djubben");
	LAi_SetWarriorType(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER); 
	
	chr = CharacterFromID("Davy Forser");
	LAi_SetImmortal(chr, false);
	LAi_SetWarriorType(chr);
	LAi_group_MoveCharacter(chr, "EnemyFight"); 
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	PChar.quest.MysteriousIslandFightDavyForserWin.win_condition.l1 = "NPC_Death";
	PChar.quest.MysteriousIslandFightDavyForserWin.win_condition.l1.character = "Davy Forser";
	PChar.quest.MysteriousIslandFightDavyForserWin.function = "MysteriousIslandFightDavyForserWin";
}

void MysteriousIslandFightDavyForserWin(string qName)
{
	chrDisableReloadToLocation = false;
	bDisableOfficers = false;
	
	ref chr = CharacterFromID("Zhofrua Djubben");
	LAi_SetActorType(chr);
	LAi_ActorFollowEverywhere(chr, "", -1);
	
	TakeNItems(PChar, "MysteriousIsland_Map", -1);

	ref map = ItemsFromID("MysteriousIsland_Map");
	map.name = "itmname_MysteriousIsland_Map_1";
	map.describe = "itmdescr_MysteriousIsland_Map_1";
	map.picIndex = 16;
	map.picTexture = "ITEMS_20";

	TakeNItems(PChar, "MysteriousIsland_Map", 1);
	TakeNItems(PChar, "MysteriousIsland_Idol", 1);

	PChar.MysteriousIsland = "13";
	AddQuestRecord("KPS_MysteriousIsland", "12");
	
	Locations[FindLocation("Hispaniola_Cave")].locators_radius.item.dig2_2 = 3.5;
	SetQuestFunction("MysteriousIslandMeetingMonchitlan", "MysteriousIslandMeetingMonchitlan", "l", "Hispaniola_Cave");
	
	bDisableLandEncounters = false;
	PChar.quest.KPS_MysteriousIsland_ZDvkaute.win_condition.l1 = "ExitFromLocation";
	PChar.quest.KPS_MysteriousIsland_ZDvkaute.win_condition.l1.location = PChar.location;
	PChar.quest.KPS_MysteriousIsland_ZDvkaute.win_condition = "KPS_MysteriousIsland_ZDvkaute";
}

void MysteriousIslandMeetingMonchitlan(string qName)
{
	ref chr;
	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 20;
	if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) chr = GetCharacter(NPC_GenerateCharacter("Monchitlan", "mummy", "man", "man_fast", iRank, PIRATE, -1, true));
	else chr = GetCharacter(NPC_GenerateCharacter("Monchitlan", "mummy", "man", "man", iRank, PIRATE, -1, true));
	chr.name = GetConvertStrWithReplace("Variable_Quests_20", "Names.txt", "#space#", " ");
	chr.lastname = "";
	chr.Dialog.FileName = "Quest\KPS\MysteriousIsland\Characters.c";
	chr.Dialog.CurrentNode = "5";
	chr.SaveItemsForDead = true;
	if (bHardBoss) chr.AlwaysReload = true;//перезарядка независимо от Дозарядки
	FantomMakeCoolFighter(chr, iRank, 100, 100, "topor_01", "pistol6", 1000);
	SetFoodToCharacter(chr, 2, 15);
	LAi_SetImmortal(chr, true);
	LAi_SetStayType(chr);
	ChangeCharacterAddressGroup(chr, "Hispaniola_Cave", "quest", "quest3");

	//SetQuestLocatorFunction("MysteriousIslandMeetingMonchitlanTalk", "MysteriousIslandMeetingMonchitlanTalk", "Hispaniola_Cave", "item", "dig2_2");
}

/*void MysteriousIslandMeetingMonchitlanTalk(string qName)
{
	Locations[FindLocation("Hispaniola_Cave")].locators_radius.item.dig2_2 = 1.0;
	ref chr = CharacterFromID("Monchitlan");
	SetDialogCharacter2Character(PChar, chr, 20.0, false);
}*/

void MysteriousIslandRetryToIsland()
{
	ref chr = CharacterFromID("Monchitlan");
	LAi_SetStayType(chr);
	
	Island_SetReloadEnableGlobal("StLucia", true);
	PChar.MysteriousIsland.StLuciaHide = false;

	PChar.MysteriousIsland = "14";
	AddQuestRecord("KPS_MysteriousIsland", "13");
	
	//ref idol = ItemsFromID("MysteriousIsland_Idol");
	//idol.useLocation = "SantaQuiteriaInside";
	//idol.useLocator = "button01";
	
	PChar.MysteriousIsland.DisableBoxOpen = true;
	
	Locations[FindLocation("SantaQuiteriaInside")].locators_radius.item.button01 = 1.5;
	SetQuestFunction("MysteriousIslandBattleAtNoIsland", "MysteriousIslandBattleAtNoIsland", "l", "StLucia");
}

void MysteriousIslandInGrotto(string qName)
{
	TakeNItems(PChar, "MysteriousIsland_Map", -1);
	chrDisableReloadToLocation = true;

	ref chr = CharacterFromID("Zhofrua Djubben");
	RemovePassenger(PChar, chr);
	
	ChangeCharacterAddressGroup(chr, "SantaQuiteriaInside", "reload", "reload1");
	LAi_SetWarriorType(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
	LAi_CharacterDisableDialog(chr);
}

void MysteriousIslandIdolInstall()
{
	PChar.MysteriousIsland.DisableBoxOpen = false;
	DeleteAttribute(&locations[FindLocation("SantaQuiteriaInside")], "private1.QuestClosed");
	DeleteAttribute(&locations[FindLocation("SantaQuiteriaInside")], "private2.QuestClosed");
	DeleteAttribute(&locations[FindLocation("SantaQuiteriaInside")], "private3.QuestClosed");
	DeleteAttribute(&locations[FindLocation("SantaQuiteriaInside")], "private4.QuestClosed");
	DeleteAttribute(&locations[FindLocation("SantaQuiteriaInside")], "private5.QuestClosed");
	DeleteAttribute(&locations[FindLocation("SantaQuiteriaInside")], "private6.QuestClosed");
		
	//locations[FindLocation("SantaQuiteriaInside")].locators_radius.item.button01 = 0.5;
	//locations[FindLocation("SantaQuiteriaInside")].models.always.Stat1 = "Stat1";
	//locations[FindLocation("SantaQuiteriaInside")].models.always.Stat1.locator.group = "item";
	//locations[FindLocation("SantaQuiteriaInside")].models.always.Stat1.locator.name = "button01";
	
	PChar.MysteriousIsland = "15";
	
	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 8;
	string sLocator, sLocatorGroup;
	for (i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Skelet_SantaLusiaShip_"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 20+MOD_SKILL_ENEMY_RATE*5, PIRATE, 1, true));
		FantomMakeCoolFighter(sld, 20+MOD_SKILL_ENEMY_RATE*5, 90, 90, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol3"), MOD_SKILL_ENEMY_RATE*10);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, "SantaQuiteriaInside", "goto",  "goto"+i);
	}

	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "KPS_MysteriousIslandFirstGrotFightWin");
}

void MysteriousIslandFightWithDubbenInGrot()
{
	ref chr = CharacterFromID("Zhofrua Djubben");
	LAi_SetHP(chr, 1000, 1000);
	LAi_SetImmortal(chr, false);
	SetFoodToCharacter(chr, 5, 50);
	LAi_SetFightMode(pchar, true);
	
	LAi_SetWarriorType(chr);
	LAi_group_MoveCharacter(chr, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	
	PChar.quest.MysteriousIslandFightWithDubbenInGrotWin.win_condition.l1 = "NPC_Death";
	PChar.quest.MysteriousIslandFightWithDubbenInGrotWin.win_condition.l1.character = "Zhofrua Djubben";
	PChar.quest.MysteriousIslandFightWithDubbenInGrotWin.function = "MysteriousIslandFightWithDubbenInGrotWin";
}

void MysteriousIslandFightWithDubbenInGrotWin(string qName)
{
	chrDisableReloadToLocation = false;

	PChar.MysteriousIsland = "16";
	AddQuestRecord("KPS_MysteriousIsland", "14");
	
	pchar.MysteriousIslandTorgovets = true;	
	PChar.MysteriousIsland.Action = true;
}

void MysteriousIslandWaitAction(string qName)
{
	PChar.MysteriousIsland = "17";
	AddQuestRecord("KPS_MysteriousIsland", "15");
	
	ref chr = CharacterFromID("Monchitlan");
	chr.Dialog.CurrentNode = "10";
}

void MysteriousIslandFightWithMonchitlan()
{
	chrDisableReloadToLocation = true;
	LAi_SetFightMode(pchar, true);

	ref chr = CharacterFromID("Monchitlan");
	LAi_SetHP(chr, 1000, 1000);
	LAi_SetImmortal(chr, false);
	SetFoodToCharacter(chr, 5, 50);
	
	LAi_SetWarriorType(chr);
	LAi_group_MoveCharacter(chr, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	
	PChar.quest.MysteriousIslandFightWithMonchitlanWin.win_condition.l1 = "NPC_Death";
	PChar.quest.MysteriousIslandFightWithMonchitlanWin.win_condition.l1.character = "Monchitlan";
	PChar.quest.MysteriousIslandFightWithMonchitlanWin.function = "MysteriousIslandFightWithMonchitlanWin";
}

void MysteriousIslandFightWithMonchitlanWin(string qName)
{
	chrDisableReloadToLocation = false;
	bDisableOfficers = false;

	PChar.MysteriousIsland = "18";
	AddQuestRecord("KPS_MysteriousIsland", "16");
	AddQuestUserData("KPS_MysteriousIsland", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("KPS_MysteriousIsland", "sSex2", GetSexPhrase("ёл","ла"));
	
	PChar.quest.KPS_MysteriousIslandRuins.win_condition.l1 = "location";
	PChar.quest.KPS_MysteriousIslandRuins.win_condition.l1.location = "Ruins";
	PChar.quest.KPS_MysteriousIslandRuins.win_condition = "KPS_MysteriousIslandRuins";
	
	PChar.quest.KPS_MysteriousIslandDungeon.win_condition.l1 = "location";
	PChar.quest.KPS_MysteriousIslandDungeon.win_condition.l1.location = "dungeon_02";
	PChar.quest.KPS_MysteriousIslandDungeon.win_condition = "KPS_MysteriousIslandDungeon";
	
	TakeNItems(PChar, "MysteriousIsland_Amulet", 1);
	SetQuestFunction("MysteriousIslandInGrottoRetryVisit", "MysteriousIslandInGrottoRetryVisit", "l", "dungeon_02");
}

void MysteriousIslandInGrottoRetryVisit(string qName)
{
	//СЮДА ВПИСАТЬ ЛОКАТОР, ГДЕ ВСТАЁМ У СУНДУКА
	PChar.quest.MysteriousIslandAmuletInstall.win_condition.l1 = "locator";
	PChar.quest.MysteriousIslandAmuletInstall.win_condition.l1.location = "dungeon_02";
	PChar.quest.MysteriousIslandAmuletInstall.win_condition.l1.locator_group = "box";
	PChar.quest.MysteriousIslandAmuletInstall.win_condition.l1.locator = "private6";
	PChar.quest.MysteriousIslandAmuletInstall.function = "MysteriousIslandAmuletInstall";
	
	InterfaceStates.Buttons.Save.enable = false;
	
	ref locLoad = &locations[reload_location_index];
	locLoad.private1.items.jewelry5 = rand(10)+20;
	locLoad.private1.items.jewelry17 = rand(10)+20;
	locLoad.private1.items.jewelry2 = rand(4)-2;
	locLoad.private2.items.jewelry5 = rand(10)+20;
	locLoad.private2.items.jewelry17 = rand(10)+20;
	locLoad.private2.items.jewelry1 = rand(4)-2;
	locLoad.private3.items.jewelry5 = rand(10)+20;
	locLoad.private3.items.jewelry17 = rand(10)+20;
	locLoad.private3.items.jewelry3 = rand(4)-2;
	locLoad.private4.items.jewelry5 = rand(10)+20;
	locLoad.private4.items.jewelry17 = rand(10)+20;
	locLoad.private4.items.jewelry4 = rand(4)-2;
	locLoad.private4.items.jewelry13 = rand(2)+5;
	locLoad.private5.items.jewelry5 = rand(10)+20;
	locLoad.private5.items.jewelry17 = rand(10)+20;
	locLoad.private5.items.jewelry2 = rand(4)-2;
	locLoad.private6.items.jewelry5 = rand(10)+40;
	locLoad.private6.items.jewelry17 = rand(10)+40;
	locLoad.private6.items.jewelry1 = 5;
	locLoad.private6.items.jewelry4 = 5;
	locLoad.private6.items.icollection = 1;
	locLoad.private6.items.mushket_Rife = 1;
	locLoad.private7.items.jewelry5 = rand(10)+20;
	locLoad.private7.items.jewelry17 = rand(10)+20;
	locLoad.private7.items.jewelry3 = rand(4)-2;
	locLoad.private7.items.jewelry13 = rand(2)+5;
	locLoad.private8.items.jewelry5 = rand(10)+20;
	locLoad.private8.items.jewelry17 = rand(10)+20;
	locLoad.private8.items.jewelry4 = rand(4)-2;
}

void MysteriousIslandAmuletInstall(string qName)
{	
	Log_info(GetConvertStrWithReplace("Variable_Quests_3", "Logs.txt", "#space#", " "));
	TakeItemFromCharacter(pchar, "MysteriousIsland_Amulet");

	//LAi_Fade("", "");	
	
	sld = GetCharacter(NPC_GenerateCharacter("MysteriousIsland Mummy In Grot", "mummy", "man", "man", 1, PIRATE, 0, false));
	sld.name = GetConvertStrWithReplace("Variable_Quests_21", "Names.txt", "#space#", " ");
	sld.lastname = GetConvertStrWithReplace("Variable_Quests_22", "Names.txt", "#space#", " ");
	sld.Dialog.FileName = "Quest\KPS\MysteriousIsland\Characters.c";
	sld.Dialog.CurrentNode = "14";
	LAi_SetImmortal(sld, true);
	
	ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest2");
	LAi_SetActorType(sld);
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(sld, pchar);
	SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
	//SetDialogCharacter2Character(PChar, sld, 2.0, false);
}

void MysteriousIslandTheEnd()
{
	LAi_SetPlayerType(pchar);
    InterfaceStates.Buttons.Save.enable = true;
                        
	chrDisableReloadToLocation = false;

	ref chr = CharacterFromID("MysteriousIsland Mummy In Grot");
	ChangeCharacterAddress(chr, "None", "");
	
	PChar.MysteriousIsland.Action = false;
	PChar.MysteriousIsland = "END";

	AddQuestRecord("KPS_MysteriousIsland", "17");
	AddQuestUserData("KPS_MysteriousIsland", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("KPS_MysteriousIsland");
	pchar.questdata.ZagadochnyOstrov = 1;
	UnlockAchievement("AchZagadochniyOstrov", 3);
}
