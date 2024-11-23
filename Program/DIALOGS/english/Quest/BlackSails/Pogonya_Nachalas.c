
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int z;
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//Бермуды. На выходе с глобалки запись в СЖ ''Морж' и 'Рейнджер' стоят на рейде бухты Разбитого корыта, отправляюсь туда же'. Собственно поставить туда Моржа и Рейнджера. Не забыть про чёрный флаг иначе файт со всеми и провал квеста.
		//Высаживаемся. Сильвер, Флинт, Вейн, Рекхэм, Бонни, несколько матросов и мушкетчиков на берегу 12 и более.

		case "BS_PN_shipF":	//Флинт
			NextDiag.TempNode = "BS_PN_shipF";
			dialog.text = "You've finally come. Berth in the bay of the Broken Trough, we will continue the conversation on the shore.";
			link.l1 = "Agreed.";
			link.l1.go = "exit";
		break;

		case "BS_PN_shipV":	//Вейн
			NextDiag.TempNode = "BS_PN_shipV";
			dialog.text = "I see you're already here. Flint announced a meeting at the Broken Trough, we'll meet there.";
			link.l1 = "Okay.";
			link.l1.go = "exit";
		break;

		case "BS_PN_1":	//Флинт
			dialog.text = "Mr. Wayne briefly told about your adventures.";
			link.l1 = "Yes, it was a stormy acquaintance!";
			link.l1.go = "BS_PN_1_1";
		break;

		case "BS_PN_1_1":	//Флинт
			dialog.text = "John, start decrypting, time is precious.";
			link.l1 = "...";
			link.l1.go = "BS_PN_2exit";
		break;

		case "BS_PN_2exit":
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_2";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		//Сильвер уходит из пати в локатор высадки.

		case "BS_PN_2":	//Вейн
			dialog.text = "Meet me. These are my companions. Jack Wrexham and Anne Bonney. An inseparable couple. Jack is a smart guy, and I insist that he help Mr. Silver with the decryption. Pretty Ann and her daggers will stay with us.";
			link.l1 = "...";
			link.l1.go = "BS_PN_3exit";
		break;

		case "BS_PN_3exit":
			sld = CharacterFromID("BS_Bony");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_3";
			DialogExit();
			DoQuestFunctionDelay("BonySpeech", 0);
		break;

		case "BS_PN_3":	//Энн
			dialog.text = "Call me pretty again, Charles, and then don't be surprised if you find a knife in your back.";
			link.l1 = "...";
			link.l1.go = "BS_PN_4exit";
		break;

		case "BS_PN_4exit":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_4";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_4":	//Вейн
			dialog.text = "Don't get excited, baby. Now about business.";
			link.l1 = "...";
			link.l1.go = "BS_PN_5exit";
		break;

		case "BS_PN_5exit":
			sld = CharacterFromID("BS_Rakham");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_5";
			DialogExit();
			DoQuestFunctionDelay("RakhamSpeech", 0);
		break;

		case "BS_PN_5":	//Рекхэм
			dialog.text = "Yes, don't mess around while I'm gone.";
			link.l1 = "...";
			link.l1.go = "BS_PN_6exit";
		break;

		case "BS_PN_6exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_6";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		//Рекхэм уходит в выгрузку.

		case "BS_PN_6":	//Флинт
			dialog.text = "The meeting with the British patrol near Bermudes was not an accident. I was attacked twice more by the British military before I got here.";
			link.l1 = "...";
			link.l1.go = "BS_PN_7exit";
		break;

		case "BS_PN_7exit":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_7";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_7":	//Вейн
			dialog.text = "We were also followed by a frigate near Dominica, but the Ranger easily got away from it.";
			link.l1 = "I have not come across the British.";
			link.l1.go = "BS_PN_8exit";
		break;

		case "BS_PN_8exit":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_8";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_8":	//Флинт
			dialog.text = "I suspect that my XO, Billy Bones, could have clarified the situation, but he miraculously disappeared during his watch.";
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_17_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
			else
			{
				link.l1 = "What the?!...";
				link.l1.go = "BS_PN_9exit";
			}
		break;

		case "BS_PN_8_1":	//Флинт
			link.l1 = "What the?!...";
			link.l1.go = "BS_PN_9exit";
		break;

		//Аларм 'К оружию!' Нападает толпа пиратов из перехода в след локу. Файт

		//По окончанию

		case "BS_PN_9exit":
			DialogExit();
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			sld = CharacterFromID("BS_Vein");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = CharacterFromID("BS_Bony");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			BSChaseBegun_shore_fight();

			LAi_group_SetHearRadius("BSChaseBegun_shore_fight", 100.0);
			LAi_group_SetRelation("BSChaseBegun_shore_fight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("BSChaseBegun_shore_fight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//pchar.quest.BSChaseBegun_shore_fight_end.win_condition.l1 = "Group_Death";//условие победы
			//pchar.quest.BSChaseBegun_shore_fight_end.win_condition.l1.group = "BSChaseBegun_shore_fight";//какую группу уничтожить
			//pchar.quest.BSChaseBegun_shore_fight_end.function = "BSChaseBegun_shore_fight_end";
		break;

		case "BS_PN_9":	//Вейн
			dialog.text = "What the hell? These are Jackman's people!";
			link.l1 = "...";
			link.l1.go = "BS_PN_10exit";
		break;

		case "BS_PN_10exit":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_10";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_10":	//Флинт
			dialog.text = "Eleanor! We need to get to the settlement urgently.";
			link.l1 = "...";
			link.l1.go = "BS_PN_11exit";
		break;

		case "BS_PN_11exit":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_11";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_11":	//Вейн
			dialog.text = "Is she here? It's weird, but not surprising. It smells like a lot of money.";
			link.l1 = "We'll figure it out later. We need to figure out what the hell is going on here.";
			link.l1.go = "BS_PN_12exit";
			NextDiag.TempNode = "BS_PN_11_loop";
			NextDiag.CurrentNode = "BS_PN_11_loop";
		break;

		case "BS_PN_12exit":
			NextDiag.TempNode = "BS_PN_11_loop";
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_12";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_12":	//Флинт
			chrDisableReloadToLocation = false;
			AddQuestRecord("BSChaseBegun", "2");
			dialog.text = "I will block the port on the Walrus. Wayne, take your men and move through the jungle to the settlement\n"+
							""+pchar.name+"That's right, I'm moving out!";
			link.l1 = "You can't delay. Go through the jungle to Rune Bay. He's on the other side of the island. Walk a little along the shore and you will see the entrance to the dungeon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_12_loop";
		break;

		case "BS_PN_12_loop":	//Флинт
			dialog.text = "Okay, I'm coming.";
			link.l1 = "Now, I'll catch my breath for a minute, gather people and go.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_12_loop";
		break;

		case "BS_PN_11_loop":	//Флинт
			dialog.text = "Me too.";
			link.l1 = "What do you want? Pass by.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_11_loop";
		break;

		//Запись в СЖ 'Встреча компаньонов закончилась резнёй. Люди Джекмена атаковали нас на берегу. Флинт сразу придумал план по захвату поселения. Выдвигаюсь в залив Руны и через подземелье постараюсь проникнуть на верфь. За дело!

		//Подземка. Мясной файт. Пиратов по напихано во все щели. Пробиваемся, выходим на верфь. Говорим с Алексусом.

		case "BS_PN_13_1":
			dialog.text = RandPhraseSimple("Stop blocking the road, get off.", "You know what? Don't bark!");
			link.l1 = RandPhraseSimple("Slow down your ardor. Otherwise I'll cool it down quickly!", "Captain! You are very welcome! Look, I've come up with a new way to fix the staysail! It will make a splash in the ranks of shipbuilders!");
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_13_1";
		break;

		case "BS_PN_13":	//Алексус
			dialog.text = "Sorry, master, not up to the staxels now. What's going on here? Jackman's men are shooting at anything that moves!";
			link.l1 = "What's going on? There's always someone shooting at someone. The old man has no peace at all! Take a look, I can redesign the block system for the gaff, and it can be controlled literally with one hand!";
			link.l1.go = "BS_PN_14";
		break;

		case "BS_PN_14":
			AddQuestRecord("BSChaseBegun", "3");
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			dialog.text = "Let's do it later, master. We won't bother you!";
			link.l1 = "That's the thing! Just for me!";
			link.l1.go = "BS_PN_14_1";

			NPChar.Dialog.Filename = "Common_Shipyard.c";
			NPChar.Dialog.CurrentNode = "Second time";

			PChar.quest.BSChaseBegun_town.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_town.win_condition.l1.location = "Pirates_Town";
			PChar.quest.BSChaseBegun_town.function = "BSChaseBegun_town";

		break;

		case "BS_PN_14_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_19_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: 'Позади подземелье и куча трупов. У меня всё больше вопросов к Джекмену. Алексус как всегда на своей волне. Пора в поселение, по времени как раз успеваю. Вперёд!'

		//Выходим в поселение. Бой окончен. На земле горы трупов. Флинт, Вейн, Бонни, бродят несколько 'наших' пиратов.

		case "BS_PN_15":	//Вейн
			chrDisableReloadToLocation = false
			sld = CharacterFromID("Atilla");
			sld.dialog.currentnode = sld.AtillaNode;
			sld.Dialog.Filename = "Quest\Isabella\Atilla.c";
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "BS_PN_15_1";
		break;

		case "BS_PN_15_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_16";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_16":	//Флинт
			dialog.text = "The residence is barricaded, we are preparing for an assault.";
			link.l1 = "...";
			link.l1.go = "BS_PN_16_1";
		break;

		case "BS_PN_16_1":
			sld = CharacterFromID("BS_Bony");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_16_2";
			DialogExit();
			DoQuestFunctionDelay("BonySpeech", 0);
		break;

		case "BS_PN_16_2":
			dialog.text = "Wait, I think they're opening the door.";
			link.l1 = "...";
			link.l1.go = "BS_PN_16exit";
		break;

		case "BS_PN_16exit":
			sld = CharacterFromID("gatri_grunt2");
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload3_back");
			sld.LifeDay = 0;

			sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp", "BS_Gatry", "woman", "woman", 1, PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload3_back");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.name = "Eleanor";
			sld.lastname = "Guthrie";
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_17";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		//Идём к резиденции, из неё выходит Гатри и несколько мушкетчиков.

		case "BS_PN_17":	//Гатри
			dialog.text = "James! And Charles... Well, you're very timely. Jackman decided to expel me from the island and prepared a riot. Three days of carnage, shooting and blood.But after seeing all of you, he finally realized that further resistance was useless and had just laid down his arms.";
			link.l1 = "...";
			link.l1.go = "BS_PN_17_1";
		break;

		case "BS_PN_17_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_18";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_18":	//Флинт
			dialog.text = "We have the encrypted route page, and Silver and Rekham are currently busy decrypting it. We need to solve the current problems. The British persistently meddle in our affairs, as well as the Jackman rebellion.";
			link.l1 = "...";
			link.l1.go = "BS_PN_18_1";
		break;

		case "BS_PN_18_1":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_19";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_19":	//Вейн
			dialog.text = "I can interrogate him, 'with passion'.";
			link.l1 = "...";
			link.l1.go = "BS_PN_19_1";
		break;

		case "BS_PN_19_1":
			sld = CharacterFromID("gatri_temp");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_20";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_PN_20":	//Гатри
			dialog.text = "It can wait. We need to put things in order here. We'll talk later at the residence.";
			link.l1 = "...";
			link.l1.go = "BS_PN_20exit";
		break;

		case "BS_PN_20exit":	//Гатри
			DialogExit();
			LAi_MethodDelay("BSChaseBegun_FewDeaysLater",0.1);
			PChar.quest.BSChaseBegun_townhall.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_townhall.win_condition.l1.location = "Pirates_townhall";
			PChar.quest.BSChaseBegun_townhall.function = "BSChaseBegun_townhall";
		break;

		//Картинка 'На следующий день' убираем трупы, перемещаем ГГ, Флинта, Вейна, Гатри, Сильвера и Рекхэма в резиденцию.

		case "BS_PN_21":	//Сильвер
			dialog.text = "So gentlemen, 'Urca De Lima', judging by the transcript, is already in Havana. There she will take on board two companies of Marines and, accompanied by four warships, will sail to Puerto Rico, where two more guard ships will join the squadron. After that, the entire armada will go to Europe.";
			link.l1 = "...";
			link.l1.go = "BS_PN_21_1";
		break;

		case "BS_PN_21_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_22";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_22":	//Флинт
			dialog.text = "Which route will the squadron take from Havana?";
			link.l1 = "...";
			link.l1.go = "BS_PN_22_1";
		break;

		case "BS_PN_22_1":
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_23";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;

		case "BS_PN_23":	//Сильвер
			dialog.text = "Southern. To Cape San Antonio and from there to the east, avoiding French waters. Parking is not planned in Santo Domingo, but it cannot be excluded. There are notes about it in the text. In case of a storm or any other troubles. Then to San Juan, then San Martin and into the ocean.";
			link.l1 = "...";
			link.l1.go = "BS_PN_23_1";
		break;

		case "BS_PN_23_1":
			sld = CharacterFromID("gatri_temp");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_24";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_PN_24":	//Гатри
			dialog.text = "Smugglers reported that there is a plague in Santo Domingo, most likely the Spanish squadron will pass by the city without stopping.";
			link.l1 = "...";
			link.l1.go = "BS_PN_24_1";
		break;

		case "BS_PN_24_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_25";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_25":	//Флинт
			dialog.text = "Means a direct route to San Juan. Wayne, there's a job for you. Find crazy thugs here in Bermudes on a couple of sloops, and do not waste a minute moving to the north coast of Cayman. Task: cruise near Cape San Antonio and, noticing the movement of the squadron, attack the escort ships. Don't get involved in battle, but run away with all sails.";
			link.l1 = "...";
			link.l1.go = "BS_PN_25_1";
		break;

		case "BS_PN_25_1":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_26";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_26":	//Вейн
			dialog.text = "I understand. The warlike Spaniards will decide to show off and chase me.";
			link.l1 = "...";
			link.l1.go = "BS_PN_26_1";
		break;

		case "BS_PN_26_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_27";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_27":	//Флинт
			dialog.text = "That's right, and you will lead the chase to Skeleton Reef, where their ships will hit the rocks, after which they will go back to Havana for repairs.";
			link.l1 = "Are we attacking Urca at this time? Where?";
			link.l1.go = "BS_PN_27_2";
		break;

		case "BS_PN_27_2":	//Флинт
			npchar.nation = PIRATE;
			dialog.text = "Right in front of the Santo Domingo garrison, but out of reach of its guns! Because of the quarantine, they won't be able to help the Urca in any way.";
			link.l1 = "...";
			link.l1.go = "BS_PN_27_1";
		break;

		case "BS_PN_27_1":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_28";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_28":	//Вейн
			AddQuestRecord("BSChaseBegun", "4");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(pchar.location.from_sea, "boat", false);
			LocatorReloadEnterDisable("Bermudes_Cavern", "reload2_back", false);
			pchar.location.from_sea = "Pirates_town";
			dialog.text = "I'll be there. After I drive the guardsmen to the reefs.";
			link.l1 = "Then let's get to work!";
			link.l1.go = "BS_PN_28exit";
		break;

		case "BS_PN_28exit":
			PChar.quest.BSChaseBegun_lock_townhall.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_lock_townhall.win_condition.l1.location = "Pirates_town";
			PChar.quest.BSChaseBegun_lock_townhall.function = "BSChaseBegun_lock_townhall";

			DialogExit();
			sld = CharacterFromID("Flint");
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, false);
			ProcessHullRepair(sld, 100.0);
			ProcessSailRepair(sld, 100.0);
			DeleteAttribute(sld, "ship.blots");
			DeleteAttribute(sld, "ship.sails");
			RepairMasts(sld);

			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);

			sld = CharacterFromID("BS_Rakham");
			LAi_SetActorType(sld);

			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);

			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);

			sld = CharacterFromID("gatri_temp");
			LAi_SetActorType(sld);

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: 'Самоубийственный план, как по мне. Но больше возможностей взять золотишко не будет. Выдвигаюсь, как только буду готов(ва). Вейн займётся выманиванием охраны, Флинт выдвинется раньше и станет вне видимости форта на якорь. Дело за мной'.

		//Двигаем в локацию Санто-Доминго. Морж уже там далеко от форта. На всякий убрать сторожей местных и мелочь, чтоб не было содомии. Подходим к Моржу, спаун испанцев. Урки среди них нет. Штук 8 военных. Мясо.

		//Запись в СЖ: 'Где чёртов галеон? Нужно поговорить с Флинтом на его корабле! Вейна тоже невидно, что–то пошло не так.'

		//Высылаем шлюпу на Моржа. Говорим с Флинтом

		case "BS_PN_30_seabattle":	//Флинт
			PChar.quest.BSChaseBegun_EndQuest.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_EndQuest.win_condition.l1.location = "Pirates_Town";
			PChar.quest.BSChaseBegun_EndQuest.function = "BSChaseBegun_EndQuest";

			dialog.text = "It's too dangerous to stay here. We'll talk in Bermudes.";
			link.l1 = "You're right. Follow my vessel.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_30_seabattle";
			DeleteAttribute(pchar, "LockMapReload");
			DeleteAttribute(pchar, "LockShoreReload");
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//Флинт присоединяется к эскадре
			Flag_Change(PIRATE);

			for (z = 1; z < 9; z++)
			{
				sld CharacterFromID("BSChaseBegun_SeaBattle"+z);
				sld.LifeDay = 0;
			}
		break;

		case "BS_PN_30":	//Флинт
			dialog.text = "...";
			link.l1 = "It looks like the plan failed! Either Silver lied, or the Spaniards were smarter!";
			link.l1.go = "BS_PN_31";
		break;

		case "BS_PN_31":
			AddQuestRecord("BSChaseBegun", "6");
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(Colonies[FindColony("SantoDomingo")], "DontSetShipInPort");
			DeleteAttribute(Colonies[FindColony("SantoDomingo")], "BSChaseBegun");
			Group_SetAddress("Flint_Group", "Bermudes", "Quest_ships", "quest_ship_8");

			dialog.text = "I'll talk to Silver. For now, we need to lay low. I'll meet you in Bermudes. Look through your channels for any clue, I'll look through mine. I can feel it in my gut, 'Urca' is still in the Caribbean. The question is where?";
			link.l1 = "I have one bird in mind, I'll listen to what she sings.";
			link.l1.go = "BS_PN_32";
		break;

		case "BS_PN_32":
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			dialog.text = "We should break up for now, we'll talk later.";
			link.l1 = "I support it.";
			link.l1.go = "BS_PN_32exit";
		break;

		case "BS_PN_32exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 20);
			BS_ReplaceHostessWithMaks();
			sld = CharacterFromID("PortRoyal_hostess");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode = "BS_NU_1";
			BSBons_SeaBattle(false);

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_1_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: 'Любой план летит к чертям, как только возьмёшься за его реализацию. Но ещё не всё потерянно! Навещу-ка я Максин в Порт Рояле, портовые девки много чего знают, а эта мне обязана. Долг - платежом красен'.

	}
}
