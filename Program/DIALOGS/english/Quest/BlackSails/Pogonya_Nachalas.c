
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

		//Багамы. На выходе с глобалки запись в СЖ «‘Морж’ и «Рейнджер» стоят на рейде, подойду к ним и вышлю шлюпку». Собственно поставить туда Моржа и Рейнджера. Не забыть про чёрный флаг иначе файт со всеми и провал квеста.
		//Высаживаемся. Сильвер, Флинт, Вейн, Рекхэм, Бонни

		case "BS_PN_shipF":	//Флинт
			NextDiag.TempNode = "BS_PN_shipF";
			dialog.text = "You're here at last. Let's dock, we'll continue this conversation on shore.";
			link.l1 = "Agreed.";
			link.l1.go = "exit";
		break;

		case "BS_PN_shipV":	//Вейн
			NextDiag.TempNode = "BS_PN_shipV";
			dialog.text = "I see you're already here. Flint's called a meeting on the beach, so I'll meet you there.";
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
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 10);
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_2";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		//Сильвер уходит в таверну 6.04.2023

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
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10);
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_6";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		//Рекхэм уходит таверну 6.04.2023

		case "BS_PN_6":	//Флинт
			dialog.text = "The meeting with the British patrol near Nassau was not an accident. I was attacked twice more by the British military before I got here.";
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

		//Аларм «К оружию!» Нападает толпа англичан из перехода в джунгли. Файт 6.04.23

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
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "BS_PN_9":	//Вейн
			dialog.text = "What the hell? It's the English again! Where the hell did they come from?!";
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
			dialog.text = "This is no longer a random patrol! They landed in one of the coves.";
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
			dialog.text = "So we'll scour the jungle and the coves.";
			link.l1 = "And someone has to find their ship or ships, it's not like they've been hiding in caves all this time!";
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
			LocatorReloadEnterDisable("Shore69", "reload1_back", true);
			InterfaceStates.Buttons.Save.enable = true;
			SetFunctionExitFromLocationCondition("BS_EmptyAdress_Flint", pchar.location, false);
			SetFunctionExitFromLocationCondition("BS_EmptyAdress_Vein", pchar.location, false);
			SetFunctionExitFromLocationCondition("BS_EmptyAdress_Silver", pchar.location, false);
			SetFunctionExitFromLocationCondition("BS_EmptyAdress_Bony", pchar.location, false);
			SetFunctionExitFromLocationCondition("BS_EmptyAdress_Rakham", pchar.location, false);
			AddQuestRecord("BSChaseBegun", "2");
			dialog.text = "I'll take the Walrus and blockade the port. Wayne, take your men and sweep the jungle around the city.\n"+
							""+pchar.name+", go out to sea and find their transports. And sink it or board it. It's up to you!";
			link.l1 = "All right, I'm on my way!";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_12_loop";
		break;

		case "BS_PN_12_loop":	//Флинт
			dialog.text = "We can't delay. Order me to hoist the sails!";
			link.l1 = "All right, I'm coming.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_12_loop";
		break;

		case "BS_PN_11_loop":	//Флинт
			dialog.text = "I'll take a minute to catch my breath, gather my men and go.";
			link.l1 = "Me, too.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_11_loop";
		break;

		//Запись в СЖ «Встреча компаньонов закончилась резнёй. Целая рота английских солдат ворвалась в город. Флинт раздал команды, моя задача потопить корабль или корабли, которые привезли этих солдат. За дело! 6.04.2023

		//часть с Алексусом и подземкой уже не нужна. вырезаем всё это
		//ставим напротив бухты Приватиров что-нибудь большое и пару корветов охранения. морской файт 6.04.2023

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

		//Запись в СЖ: «Транспорты и сопровождени англичан потопленны. Пора на берег» 6.04.2023

		//Причаливаем. Бой окончен. На земле горы трупов в разнобой англичане и пираты. Флинт, Вейн, Бонни - стоят напротив дома Гатри. бродят несколько «наших» пиратов.6.04.2023

		case "BS_PN_15":	//Вейн
			chrDisableReloadToLocation = false
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
			dialog.text = "The house is barricaded, we're preparing to storm the place.";
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
			dialog.text = "Погоди, кажется, они открывают дверь.";
			link.l1 = "...";
			link.l1.go = "BS_PN_16exit";
		break;

		case "BS_PN_16exit":
			DialogExit();
			sld = CharacterFromID("gatri_home_grunt1");
			ChangeCharacterAddressGroup(sld, "Nassau_town", "officers", "houseS1_3");
			LAi_ActorTurnToCharacter(sld, PChar);
			sld = CharacterFromID("Gatri_temp");
			ChangeCharacterAddressGroup(sld, "Nassau_town", "reload", "houseS1");
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_17";
			LAi_SetStayTypeNoGroup(sld);
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		//Идём к резиденции, из неё выходит Гатри и несколько мушкетчиков.

		case "BS_PN_17":	//Гатри
			dialog.text = "James! And Charles. Well, you're just in time. The English have decided to kick me off my island! I've got to write a letter or two to my grandfather, they won't get away with it! They don't know who they're messing with yet!";
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
			dialog.text = "We have the encrypted page with the route, and Silver and Rackham are busy decrypting it. We've got current problems to solve. The English are persistently meddling in our affairs and it has nothing to do with your island, Eleanor! I know how the navy operates and it's not the way it works. And it pisses me off that I don't know who's behind it yet.";
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
			dialog.text = "There's bound to be survivors. I can interrogate them, give them a hard time.";
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
			dialog.text = "It can wait. We need to clean this place up. We'll talk later at my residence.";
			link.l1 = "...";
			link.l1.go = "BS_PN_20exit";
		break;

		case "BS_PN_20exit":	//Гатри
			DialogExit();
			LAi_MethodDelay("BSChaseBegun_FewDeaysLater",0.1);
			PChar.quest.BSChaseBegun_townhall.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_townhall.win_condition.l1.location = "Nassau_OfisGatri";
			PChar.quest.BSChaseBegun_townhall.function = "BSChaseBegun_townhall";
		break;

		//Картинка «На следующий день» убираем трупы, перемещаем ГГ, Флинта, Вейна, Гатри, Сильвера и Рекхэма в дом Гатри. 6.04.2023

		case "BS_PN_21":	//Сильвер
			dialog.text = "So gentlemen, 'Urca De Lima', judging by the transcript, is already in Havana. There she will take on board two companies of Marines and, accompanied by four warships, will sail to Puerto Rico, where two more guard ships will join the squadron. After that, the entire armada will go to Europe.";
			link.l1 = "...";
			link.l1.go = "BS_PN_21_1";
		break;

		case "BS_PN_21_1":
			sld = CharacterFromID("Flint");
			LAi_SetSitTypeNoGroup(sld);
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
			LAi_SetSitTypeNoGroup(sld);
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
			LAi_SetSitTypeNoGroup(sld);
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
			LAi_SetSitTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_25";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_25":	//Флинт
			dialog.text = "So we're going straight to San Juan. Wayne, I got a job for you. Find some crazy thugs here or in Puerto Principe with a couple or three sloops, and get to the north coast of Cayman without wasting a minute. Task: sail near Cape San Antonio and, noticing the movement of the squadron, attack the escort ships. Do not engage in combat, but run away at full sail.";
			link.l1 = "...";
			link.l1.go = "BS_PN_25_1";
		break;

		case "BS_PN_25_1":
			sld = CharacterFromID("BS_Vein");
			LAi_SetSitTypeNoGroup(sld);
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
			LAi_SetSitTypeNoGroup(sld);
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
			dialog.text = "Right in front of the Santo Domingo garrison, but out of range of its guns! Because of the quarantine, they can't do anything to help the Urca.";
			link.l1 = "...";
			link.l1.go = "BS_PN_27_1";
		break;

		case "BS_PN_27_1":
			sld = CharacterFromID("BS_Vein");
			LAi_SetSitTypeNoGroup(sld);
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
			dialog.text = "I'll be there. After I've driven the patrolmen onto the reefs.";
			link.l1 = "Then let's do it!";
			link.l1.go = "BS_PN_28exit";
		break;

		case "BS_PN_28exit":		
			PChar.quest.BSChaseBegun_lock_townhall.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_lock_townhall.win_condition.l1.location = "Nassau_town";
			PChar.quest.BSChaseBegun_lock_townhall.function = "BSChaseBegun_lock_townhall";
			DeleteAttribute(PChar, "currentsoundtrack");
			DeleteAttribute(PChar, "BS_permanentblackflag");
			Flag_Change(PIRATE);
			LAi_SetPlayerType(PChar);
			DoReloadCharacterToLocation("Nassau_town", "reload", "houseS1");
			DialogExit();
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
			PChar.quest.BSChaseBegun_EndQuest.win_condition.l1.location = "Nassau_Town";
			PChar.quest.BSChaseBegun_EndQuest.function = "BSChaseBegun_EndQuest";
			if (Group_isDead("BSChaseBegun_SeaBattle"))
			{
				if (!CheckCompanionInCharacter(pchar, npchar.id)){BS_ChaseBegun_WithFlintToNassau();}
				dialog.text = "It's too dangerous to stay here. We'll talk in Nassau.";
				link.l1 = "You're right. Follow my vessel.";
			}
			else
			{
				dialog.text = "We'll talk later! First, help me deal with the Spaniards.";
				link.l1 = "It can be done!";
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_30_seabattle";
			Flag_Change(PIRATE);
		break;

		case "BS_PN_30":	//Флинт
			dialog.text = "...";
			link.l1 = "Looks like the plan has failed! Either Silver lied or the Spaniards were more cunning!";
			link.l1.go = "BS_PN_31";
		break;

		case "BS_PN_31":
			AddQuestRecord("BSChaseBegun", "6");
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(Colonies[FindColony("SantoDomingo")], "DontSetShipInPort");
			DeleteAttribute(Colonies[FindColony("SantoDomingo")], "BSChaseBegun");
			dialog.text = "I'll talk to Silver. For now, we need to lay low. I'll meet you in the Bahamas. You run your channels for any leads, I'll run mine. My gut tells me the Urca is still in the Caribbean. The question is where?";
			link.l1 = "I've got a little birdie in mind, I'll see what she'll sing.";
			link.l1.go = "BS_PN_32";
		break;

		case "BS_PN_32":
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			dialog.text = "We should split up for now, we'll talk later.";
			link.l1 = "Seconded.";
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
			SetFunctionExitFromLocationCondition("BS_EmptyAdress_Flint", pchar.location, false);
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_1_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: «Любой план летит к чертям, как только возьмёшься за его реализацию. Но ещё не всё потерянно! Навещу-ка я Максин в Порт Рояле, портовые девки много чего знают, а эта мне обязана. Долг - платежом красен».

	}
}
