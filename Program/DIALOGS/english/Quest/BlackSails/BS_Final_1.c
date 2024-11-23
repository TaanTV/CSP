

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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

		//Скипаем с отравления три дня. ГГ приходит в себя в комнате таверны. Запись в СЖ: 'Неожиданно. Но предсказуемо. Флинт поимел нас всех. Кто бы мог подумать. Хорошо, что жив(ва) остался(лась)! Нужно разобраться в происходящем. Дьявол, как же мутит то!

		//Далее, если договорились поймать Флинта для разведки – Вейна нет в Шарп-Тауне. Если не договаривались – он в таверне за столом пьянствует.

		//Спускаемся в таверну. Вариант без Вейна. Подходит Макс

		case "BS_F1_1":	//Максин
			dialog.text = "You're finally awake , you've been out the longest.";
			link.l1 = "Is everyone alive? What's new?";
			link.l1.go = "BS_F1_2";
		break;

		case "BS_F1_2": //Максин
			dialog.text = "Everyone is alive, he put belladonna in the wine. Master Alexus was giving us all some kind of charcoal stuff and God knows what else. They vomited all over the residence, but they survived.";
			link.l1 = "I will definitely buy him something technical. So what's the news? Flint? Gold?";
			link.l1.go = "BS_F1_3";
		break;

		case "BS_F1_3":	//Максин
			dialog.text = "No Flint, no gold. There's only one chest of doubloons in the warehouse, there's about fifty thousand for everyone. And a note. ";
			link.l1 = "Damn prude! And I almost believed in his 'friendship'. Where are the others?";
			link.l1.go = "BS_F1_4";
		break;

		case "BS_F1_4":	//Максин
			dialog.text = "Eleanor is in residence, with Rekham and Bonnie with her, all three are angry as hell. They are constantly hitting and yelling at each other. As soon as Wayne got to his feet, he hoisted the sails and sped off somewhere";
			link.l1 = "I think it's better not to go into the residence yet. I'm going to get some air.";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: 'Трудно думать, когда тебя постоянно тошнит. Но нужно что-то делать. Попробую подключить разведку. Какой там пароль? На Антигуа! В путь'.

		//Вариант с Вейном

		//Подходит Макс

		case "BS_F1_5":	//Максин
			LAi_SetActorType(npchar);
			dialog.text = "Ypu're finally awake, you've been out the longest.";
			link.l1 = "Is everyone alive? What's new?";
			link.l1.go = "BS_F1_6";
		break;

		case "BS_F1_6": //Максин
			dialog.text = "Everyone is alive, he put belladonna in the wine. Master Alexus was giving us all some kind of charcoal stuff and God knows what else. They vomited all over the residence, but they survived.";
			link.l1 = "I will definitely buy him something technical. So what's the news? Flint? Gold?";
			link.l1.go = "BS_F1_7";
		break;

		case "BS_F1_7":	//Максин
			dialog.text = "No Flint, no gold. There is only one chest of doubloons in the warehouse, there are about fifty thousand for everyone. And the note: 'Sorry, share it and forget about 'Urca' and Flint. It's necessary. You won't understand anyway. F.'";
			link.l1 = "Damn prude! And I almost believed in his 'friendship'. Where are the others?";
			link.l1.go = "BS_F1_8";
			AddMoneyToCharacter(PChar, 50000);
		break;

		case "BS_F1_8":	//Максин
			dialog.text = "At the residence, Charles and Eleanor find out which of them has the bigger balls. They are constantly shouting and hitting something, then they quiet down. They'll either kill each other or fuck each other. Or both.";
			link.l1 = "Have they been married before? Hmm. You don't have to answer. Are there any leads?";
			link.l1.go = "BS_F1_9";
		break;

		case "BS_F1_9":	//Максин
			dialog.text = "I need to go back to Port Royal, maybe the girls heard something.";
			link.l1 = "Well, in that case, welcome aboard! Let's leave the lovebirds to sort things out. I hope they fuck after all, and not kill each other.";
			link.l1.go = "BS_F1_9exit";
		break;

		case "BS_F1_9exit":	//Максин
			DialogExit();
			PChar.quest.BSHangover_PortRoyal.win_condition.l1 = "location";
			PChar.quest.BSHangover_PortRoyal.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.BSHangover_PortRoyal.function = "BSHangover_PortRoyal";
			AddQuestRecord("BSHangover", "2");
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_7_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;
		case "BS_F1_8_MaksRoyal":	//Максин
			chrDisableReloadToLocation = false;
			dialog.text = "Thank you. It will take me some time to gather information. You can relax in the tavern for a few days.";
			link.l1 = "Okay, then I'll go visit Wayne and Guthrie. I think they've calmed down already.";
			link.l1.go = "BS_F1_8_MaksRoyal_exit";
		break;

		case "BS_F1_8_MaksRoyal_exit":
			DialogExit();
			BS_ReplaceHostessWithMaks();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", "none", "", "", "", -1);
			DeleteAttribute(npchar, "LifeDay");
			AddQuestRecord("BSHangover", "3");
			//npchar.location = "none";
			sld = CharacterFromID("BS_Silver");
			sld.location = "none";
			sld = CharacterFromID("BS_Rakham");
			sld.location = "none";
			sld = CharacterFromID("BS_Vein");
			sld.location = "none";
			sld = CharacterFromID("BS_Bony");
			sld.location = "none";
			sld = CharacterFromID("Flint");
			sld.location = "none";

			ref jackman = CharacterFromID("Jackman");
			ChangeCharacterAddressGroup(jackman, "Pirates_townhall", "sit", "sit1");

			sld = CharacterFromID("gatri_temp");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_10";
			if (jackman.dialog.currentnode == "Jackman_Defeated")
			{
				sld.location.locator = "goto4";
			}

			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
			LocatorReloadEnterDisable("Pirates_townhall", "reload2", false);
			LocatorReloadEnterDisable("Pirates_portoffice", "reload1", false);
		break;

		//Запись в СЖ: 'Флинт не мог испариться бесследно и в Европу, ему путь заказан. Попробуем узнать что-то с помощью пташек Макс. В Порт Рояль!'

		//Далее вариант поисков Флинта, без договора с Бонсом

		//Отвозим Макс в Порт Рояль. Она покидает корабль. Заменяем мадам на Макс.

		//Запись в СЖ: 'Максин пока займётся сбором слухов, а я проведаю Вейна и мисс Гатри'

		//Пиздуем на Бермуды. В резиденции Гатри. Вейна пока нигде нет, после диалога, ставим его в комнату таверны.

		case "BS_F1_10": //Гатри
			dialog.text = "";
			link.l1 = "Has the storm subsided? When I left this harbor, the walls were shaking and the rats were running in a crowd to drown themselves!";
			link.l1.go = "BS_F1_11";
		break;

		case "BS_F1_11": //Гатри
			dialog.text = "That vile, narcissistic, uncouth cretin! How dare he! I don't want to see him anymore! Don't remind me of him! Better get out after him! To hell with it!";
			link.l1 = "";
			LAi_SetActorTypeNoGroup(npchar);
			link.l1.go = "exit";

			sld = CharacterFromID("Pirates_tavernkeeper");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_12";

		break;

		//Выкидывает нас на порог. Дверь закрыта.

		//Идём в таверну. Ставим Вейна в комнату.

		//Подходим к бармену.

		case "BS_F1_12": //Б
			dialog.text = "";
			link.l1 = "Is Wayne upstairs?";
			link.l1.go = "BS_F1_13";
		break;

		case "BS_F1_13": //Б
			dialog.text = "The third day as. He's already drunk a barrel of rum and still demands it.";
			link.l1 = "Wait with the rum, we need to talk.";
			link.l1.go = "BS_F1_13exit";
		break;

		case "BS_F1_13exit": //Б
			DialogExit();
			RestoreOldDialog(npchar);

			DoReloadCharacterToLocation("Pirates_tavern_upstairs", "goto", "goto1");
			pchar.quest.BSHangover_Vein.win_condition.l1          = "location";
			pchar.quest.BSHangover_Vein.win_condition.l1.location = "Pirates_tavern_upstairs";
			pchar.quest.BSHangover_Vein.function             = "BSHangover_Vein";
		break;

		//Идём наверх

		case "BS_F1_14": //Вейн
			dialog.text = "Get lost!";
			link.l1 = "What a stink! Have you decided to get drunk here? Get your brains together. There may be some leads on Flint! Are you with me?";
			link.l1.go = "BS_F1_15";
		break;

		case "BS_F1_15": //Вейн
			dialog.text = "Any leads? Yes, damn it, I'm with you! And burn this Miss Arrogant Ass with blue flames!";
			link.l1 = "That's wonderful. I will not delve into the essence of the conflict. Join the squadron, the way to Port Royal!";
			link.l1.go = "BS_F1_15exit";
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));
			BSRepairShip(npchar);
			AddQuestRecord("BSHangover", "4");
			npchar.location = "none";
			pchar.quest.BSHangover_RoyalVein.win_condition.l1          = "location";
			pchar.quest.BSHangover_RoyalVein.win_condition.l1.location = "PortRoyal_SecBrRoom";
			pchar.quest.BSHangover_RoyalVein.function             = "BSHangover_RoyalVein";
		break;

		case "BS_F1_15exit": //Вейн
			DialogExit();
			npchar.dialog.currentnode = "BS_F1_15Vein";
		break;

		case "BS_F1_15Vein": //Вейн
			npchar.dialog.currentnode = "BS_F1_15Vein"
			dialog.text = "Flint will pay!";
			link.l1 = "He can't get away from us.";
			link.l1.go = "BS_F1_15exit";
		break;
		//Запись в СЖ: 'Гатри и Вейн поссорились. Ничего нового. Главное мы снова в деле. Пора проведать Макс'

		//Без приключений плывём в Порт Рояль. Идём в кабинет Макс. Вейн прицепом.

		case "BS_F1_16": //Максин
			dialog.text = "";
			link.l1 = "What's the news, madam?";
			link.l1.go = "BS_F1_17";
		break;

		case "BS_F1_17": //Максин
			dialog.text = "And you don't get sick. The news is unexpected. We have a new girl from Bridgetown, so she told us that a certain pirate was almost registered in their institution. He throws gold by handfuls, drunkenly tells each girl how his best friend and captain abandoned him. And he loved him like his own father. And so on in the same spirit. And this sailor's name is John Stinger.";
			link.l1 = "";
			link.l1.go = "BS_F1_17exit";
		break;

		case "BS_F1_17exit": //Максин
			RestoreOldDialog(npchar);
			StartInstantDialogNoType("BS_Vein", "BS_F1_18", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_18": //Вейн
			chrDisableReloadToLocation = false;
			npchar.location = "none";
			AddQuestRecord("BSHangover", "5");
			dialog.text = "Silver?! He once boasted that they called him the Whore's Sting!";
			link.l1 = "We need to hurry. I don't believe Flint just wrote him off the ship!";
			link.l1.go = "BS_F1_15exit";

			pchar.quest.BSHangover_VeinFollows.win_condition.l1          = "location";
			pchar.quest.BSHangover_VeinFollows.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.BSHangover_VeinFollows.function             = "BSHangover_VeinFollows"

			pchar.BSSearchStinger = 0;

			sld = CharacterFromID("Bridgetown_tavernkeeper");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_shipyarder");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_trader");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_hostess");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_usurer");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_priest");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_portman");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";
		break;

		case "BS_F1_SearchStinger":
			dialog.text = "";
			link.l1 = "Hello. I'm looking for someone. Did a certain John Stinger come to see you? Or maybe John Silver? He also wears a piece of wood for a leg. I can pay well for the information.";
			if(npchar.id == "BridgetownJailOff")
			{
				link.l1 = "Hello. I'm sorry for the indiscreet question, but is there by any chance a man named John Stinger among your 'wards'? Or maybe John Silver?  He also wears a piece of wood for a leg.";
			}
			link.l1.go = "BS_F1_SearchStinger_1";
		break;

		case "BS_F1_SearchStinger_1":
			dialog.text = "I'm sorry, but this is the first time I've heard this name. I can't help you.";
			link.l1 = "Sorry.";
			link.l1.go = "BS_F1_SearchStinger_2";
		break;

		case "BS_F1_SearchStinger_2":
			pchar.BSSearchStinger = sti(pchar.BSSearchStinger)+1;
			Log_TestInfo(pchar.BSSearchStinger);
			RestoreOldDialog(npchar);
			DialogExit();
			if(npchar.id == "BridgetownJailOff")
			{
				chrDisableReloadToLocation = false;
				InterfaceStates.DisFastTravel = true;

				pchar.quest.BSHangover_StingerFound.win_condition.l1          = "location";
				pchar.quest.BSHangover_StingerFound.win_condition.l1.location = "Bridgetown_fort";
				pchar.quest.BSHangover_StingerFound.function             = "BSHangover_StingerFound";
			}
			else
			{
				BSHangover_SearchStingerCheck();
			}

		break;

		//Запись в СЖ: 'Есть зацепка, в борделе на Барбадосе, сорит деньгами и жалуется на жизнь Джон Сильвер. Нужно успеть туда раньше Флинта и подготовить засаду!'

		//Плывём на Барбадос. В борделе никто ничего про Сильвера-Стингера не знает. Тыкаемся во все двери. После того, как оббежали всех (бармен, ПУ, верфь, церковь, магазин, банк) дзынь! Запись в СЖ: 'Никто не видел или не хочет говорить о Сильвере или Стингере, или ком-то похожем на него. Остаётся проверить тюрьму!'

		//Идём в тюрячку. Комендант, тоже шлёт нахой. В расстроенных чувствах уходим. На переходе Форт-Гор Ворота, в локации ворот, подходит сам Сильвер.

		case "BS_F1_19": //Сильвер
			dialog.text = "Glad to see you companions! Your brain is working faster than Flint's!";
			link.l1 = "Did you specifically use whores to get word of the unfortunate drunk Stinger to Maxine? A risky move. Flint could have gotten to her first!";
			link.l1.go = "BS_F1_19exit";
		break;

		case "BS_F1_19exit":
			StartInstantDialog("BS_Vein", "BS_F1_20", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_20": //Вейн
			dialog.text = "Holy shit! Maxine! If Flint thought the same way you did, she's in danger!";
			link.l1 = "";
			link.l1.go = "BS_F1_20exit";
		break;

		case "BS_F1_20exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_21", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_21": //Сильвер
			dialog.text = "Oh, our Max can stand up for himself. This is no longer the same poor slave from Louisiana who was sold to a brothel as a child.";
			link.l1 = "Also, I feel like she's in trouble. We must hurry to Port Royal.";
			link.l1.go = "BS_F1_22";
		break;

		case "BS_F1_22": //Сильвер
			dialog.text = "Or wait a little longer. What would Flint do to her? We'll set up an ambush, and I'll be the bait. Poor, drunken Silver.";
			link.l1 = "";
			link.l1.go = "BS_F1_22exit";
		break;

		case "BS_F1_22exit":
			StartInstantDialogNoType("BS_Vein", "BS_F1_23", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_23": //Вейн
			dialog.text = "Stop baring your teeth. How did you get here in the first place? Didn't you get along?";
			link.l1 = "";
			link.l1.go = "BS_F1_23exit";
		break;

		case "BS_F1_23exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_24", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_24": //Сильвер
			dialog.text = "Almost. Flint rushed to the Walrus and immediately ordered them to sail. 'We'll talk later, John, I think you'll understand everything,' he said and glared so Flintishly, from under his brow. Well, you know. And then it hit me all the way. I look, and all the faces on the deck are unfamiliar, when did he manage to dial the command? There's something fishy here, I think.";
			link.l1 = "What happened next? Don't go without decorations, please!";
			link.l1.go = "BS_F1_25";
		break;

		case "BS_F1_25": //Сильвер
			dialog.text = "We got ten miles away from Bermudes, and then the sailors took out these new pistols and shot all the veterans with whom they took the gold of the Urca! The deck is covered in blood, and they are finishing off the survivors with cleavers. Well, I ran into the forecastle as fast as I could, grabbed a belt with hidden gold, an empty rum barrel and overboard. The current carried me to Sin Martin, where I hired fishermen to ferry me away. After all, the donkey is here.";
			link.l1 = "Interesting, Flint means he planned all this in advance and wasn't going to share it with anyone.";
			link.l1.go = "BS_F1_25exit";
		break;

		case "BS_F1_25exit":
			StartInstantDialogNoType("BS_Vein", "BS_F1_27", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_26": //Вейн
			dialog.text = "Yes, I will stuff this gold down his throat until it falls from below!";
			link.l1 = "";
			link.l1.go = "BS_F1_27";
		break;

		case "BS_F1_27": //Вейн
			dialog.text = "Yes, I will stuff this gold down his throat until it falls from below!";
			link.l1 = "";
			link.l1.go = "BS_F1_27exit";
		break;

		case "BS_F1_27exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_28", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_28": //Сильвер
			dialog.text = "Well? I'll go to a brothel, I'll continue to play the desperate drunkard, and you'll hide here and drive the ships to the bay of Rigged Point. And, that's... um... Can you give me some money for a brothel? I've been holding out here.";
			link.l1 = "Hold on. Here are the remnants of the fifty thousand that Flint left for us all.";	//- 12000
			link.l1.go = "BS_F1_28exit";
		break;

		case "BS_F1_28exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.location = "none";
			AddMoneyToCharacter(PChar, -12000 - rand(500));
			StartInstantDialogNoType("BS_Vein", "BS_F1_27_1", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_27_1": //Вейн
			dialog.text = "So it's decided. I'll take care of the ships, while you get a room in the tavern, we'll probably stay here for a while.";
			link.l1 = "Okay.";
			link.l1.go = "BS_F1_27_2";
		break;

		case "BS_F1_27_2": //Вейн
			DialogExit();
			UnLockWeapons("");
			InterfaceStates.DisFastTravel = false;
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.location = "none";
			pchar.location.from_sea = "Shore5";

			sld = CharacterFromID("Bridgetown_tavernkeeper");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_RentRoom";
		break;

		case "BS_F1_RentRoom":
			dialog.text = "";
			link.l1 = "Greetings. I want to rent a room for a week.";
			link.l1.go = "BS_F1_RentRoom_1";
		break;

		case "BS_F1_RentRoom_1":
			dialog.text = "That'll be a hundred coins.";
			if (sti(pchar.money) >= 100)
			{
				link.l1 = "Here you go.";
				link.l1.go = "BS_F1_RentRoom_2";
			}
			link.l2 = "Hmm... I'll be back.";
			link.l2.go = "BS_F1_RentRoom_exit";
		break;

		case "BS_F1_RentRoom_2":
			dialog.text = "The room is yours. Here's the key.";
			AddMoneyToCharacter(PChar, -100);
			link.l1 = "Thank you";
			link.l1.go = "BS_F1_RentRoom_3";
		break;

		case "BS_F1_RentRoom_3":
			DialogExit();
			RestoreOldDialog(npchar);
			BSHangover_FewDaysLater();
		break;

		case "BS_F1_RentRoom_exit":
			DialogExit();
			npchar.dialog.currentnode = "BS_F1_RentRoom";
		break;

		//Ставим корабли в бухту. Ножками топаем в город и просто чилим три дня или скипаем. Через три дня, на улице, подходит шлюха

		case "BS_F1_29": //Шлюха
			dialog.text = "Handsome Johnny said to get you ready. The Walrus got up on the raid. He will lure the hunter into a cave here on the island.";
			link.l1 = "Thanks, baby.";
			link.l1.go = "BS_F1_30";
		break;

		case "BS_F1_30": //Шлюха
			dialog.text = "And the coin?";
			link.l1 = "Oh, yes. Here are some coins for you."; //- 32000
			link.l1.go = "BS_F1_30exit";
		break;

		case "BS_F1_30exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			StartInstantDialog("BS_Vein", "BS_F1_31", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_31": //Вейн
			AddMoneyToCharacter(PChar, -500);
			dialog.text = "It just happened. I don't like this!";
			AddQuestRecord("BSHangover", "7");
			link.l1 = "Me too. Let's split up. Take your men and take up positions around the cave entrance. I'm going inside. If you hear something wrong, be on your guard, don't go inside, sit in ambush. Let's see how it turns out.";
			link.l1.go = "BS_F1_31_1";

		break;
		case "BS_F1_31_1": //Вейн
			npchar.dialog.currentnode = "BS_F1_15Vein";
			DialogExit();
			npchar.location = "none";
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_8_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Вейн уходит. Запись в СЖ: 'Ну что же, посмотрим, какая рыба заглотила наживку!'

		//Идём в пещеру. Войдя – запускается аларм и в логе таймер 60 сек. 'Джон в беде, нужно поспешить на выручку!' – это тоже в логе. Бежим в место шахтных выработок. Там, сразу гасим таймер, Сильвер – становится смертным. В пещёре 10-12 ОЗГов, начинается замес. Сильвер погиб – провал квеста, принудительный – экран смерти. Сильвер выжил – продолжаем.

		case "BS_F1_32": //Сильвер
			dialog.text = "";
			link.l1 = "There is no Flint here! Damn it!";
			link.l1.go = "BS_F1_33";
		break;

		case "BS_F1_32_beaten": //Сильвер
			dialog.text = "Oh, I think I've been pierced through...";
			link.l1 = "I don't see anything serious, you're going to live.";
			link.l1.go = "BS_F1_32_beaten_1";
		break;

		case "BS_F1_32_beaten_1": //Сильвер
			dialog.text = "Are you sure? I feel much worse.";
			link.l1 = "There is no Flint here! Damn it!";
			link.l1.go = "BS_F1_33";
		break;

		case "BS_F1_33": //Сильвер
			dialog.text = "Exactly, did you notice? These are the faces I was talking about. These are definitely not local, I know almost all the hired fighters here. Where's Wayne?";
			link.l1 = "Outside, in ambush. Let's not waste time, go to the bay and try to board the Walrus!";
			link.l1.go = "BS_F1_33_2";
		break;

		case "BS_F1_33_2":
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "BS_F1_33_1";
			DialogExit();
		break;
		case "BS_F1_33_1":
			dialog.text = "I'll sit here a little longer, and then right behind you.";
			link.l1 = "Come on, don't pretend, you're a fake.";
			link.l1.go = "BS_F1_33_2";
		break;

		//Бяжим к выходу. Снаружи идёт замес. Опять озги (модельки), Вейн, Бонни, Рекхэм и пара – тройка их матросов против десятка наёмников. Опять та же история, если кто то из ключевых героев гибнет – сразу экран смерти. Завалили геев. Говорим с Вейном.

		case "BS_F1_34": //Вейн
			dialog.text = "These, (kicks the corpse), climbed out of the undergrowth as soon as you entered the cave, I had to intervene.";
			link.l1 = "It was hot inside too! Flint is not among the corpses! We need to run to the ships and try to take the Walrus. Follow me!";
			link.l1.go = "BS_F1_34exit";
			BSHangover_IsEveryoneOkay();
		break;
		case "BS_F1_34exit": //Вейн
			DialogExit();
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));
			LocatorReloadEnterDisable("Shore5", "boat", false);
			chrDisableReloadToLocation = false;

			for (int i = 1; i <= 4; i++)
			{
				if(i == 1)	sld = CharacterFromID("BS_Vein");
				if(i == 2)	sld = CharacterFromID("BS_Silver");
				if(i == 3)	sld = CharacterFromID("BS_Rakham");
				if(i == 4)	sld = CharacterFromID("BS_Bony");
				Lai_SetActorTypeNoGroup(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.location = "none";
			}
		break;

		//Запись в СЖ: 'На наживку клюнула целая стая рыбин! Но главного лосося, среди них не было. 'Морж' всё ещё на рейде, нужно взять его на абордаж и быстро, пока сторожевики не решили посмотреть, кто там палит из пушек'.

		//Скачем в Риггед Поинт, садимся на корабли берём Моржа на абордаж. В каюте рубимся с Флинтом. Суровый по статам мужик с какой нибудь уникальной саблей. Банки, жратва – всё по полной. Порубили. Заводит диалог

		case "BS_F1_35": //Флинт
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (int z = 1; z <= 6; z++)
			{
				sld = CharacterFromID("FlintOff"+z);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			PChar.quest.BSHangover_Fail1.over = "yes";
			PChar.quest.BSHangover_Fail2.over = "yes";

			dialog.text = "Everything should have gone completely wrong! I'm sorry. But listen to me!";
			link.l1 = "Wrong?! Shouldn't we have survived? Yes, I'm a fool"+ GetSexPhrase("k", "") +", decided to that you are my friend! Damn it, we could do this kind of thing together! Why are you doing this?";
			link.l1.go = "BS_F1_36";
		break;

		case "BS_F1_36": //Флинт
			dialog.text = "Everything is very difficult, my friend. If you hadn't started the chase, I wouldn't have fallen for John's trick... It would have been different. No one would leave offended. I've thought of everything! I thought that was it. I don't need this money personally, it will become the basis of a new, free state. The Republic! Without kings and their wars, a place where free people can live according to their conscience, not depending on the whims of bankers or aristocrats! This is a New World, so let it be the beginning of a New, better World! Do you understand?!";
			link.l1 = "What are you talking about? Which republic? Sharp had already tried, and so had Avory. How did it end? With blood. With the blood of those very free people for whom you are going to build a new world! Or is your 'world' special? What is it?";
			link.l1.go = "BS_F1_37";
		break;

		case "BS_F1_37": //Флинт
			dialog.text = "This is not the place for philosophical debates. Let's finish this and talk like civilized people.";
			link.l1 = "The hell with it. You're going to the hold now. In shackles. And we'll all talk together. Along with those you tried to poison! And pray to all the gods you know that I can convince Wayne not to drag you under the keel.";
			link.l1.go = "BS_F1_38";
		break;

		case "BS_F1_38": //Флинт
			dialog.text = "I forgot I was dealing with a pirate. Okay, here's my weapon. Lead on.";
			TakeNItems(PChar, "blade43", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You got a Narwhal!");
			link.l1 = "";
			link.l1.go = "BS_F1_38exit";
		break;

		case "BS_F1_38exit": //Флинт
			for (int k = 1; k <= 6; k++)
			{
				sld = CharacterFromID("FlintOff"+k);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}


			DialogExit();

			QuestAboardCabinDialogFree(); // важный метод
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "");

			LAi_KillCharacter(npchar);
			DeleteCharacter(npchar);
			SetLaunchFrameFormParam("Your men are taking Flint away. Meanwhile, you are searching his cabin. In one of the chests you find five million pesos. Also, your attention is attracted by the book - Marcus Aurelius 'Reflections'. You're taking her, along with Flint's logbook..", "", 0.1, 15.0);
			LaunchFrameForm();
			AddMoneyToCharacter(PChar, 5000000);
			AddQuestRecord("BSHangover", "9");
			sld = CharacterFromID("PortRoyal_hostess");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_39";

			DeleteAttribute(pchar, "LockMapReload");

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				sld = CharacterFromID(pchar.WhisperPGG);
				sld.dialog.filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
				sld.dialog.currentnode = "BS_21_WhisperIsHere";
				LAi_SetActorType(pchar);
				LAi_SetActorTypeNoGroup(sld);
				SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
				LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
			}
		break;

		//Отдаёт свою саблю. ВАЖНО! Не делать релоад после драки, нужно дать обыскать каюту. В сундуке – 2.5кк денег, побрякушки. Судовой Журнал Флинта и книга - Марк Аврелий 'Размышления'. Моржа можно топить или себе забрать – похер. (!) Залочить возможность диалога с Флинтом в трюме, во избежание найма. Оставить фразу 'Позже поговорим'.

		//Запись в СЖ: 'Флинт пойман! Пытался нести какую -  то ахинею про Республику и свободных людей. Путь на Бермуды, там по расспросим подробнее, про Республику, а главное – про сто пятьдесят миллионов причин ввязаться в эту авантюру! Ах, да! И нужно проведать Макс в Порт Рояле. Компаньон как – никак'.

		//Плывём в ПР, забираем Макс из борделя. С ней всё заебись.

		//Диалог в кабинете мадам.

		case "BS_F1_39": //Максин
			dialog.text = "";
			link.l1 = "I'm with the news! Flint is in shackles, in the hold. Are you with us? It's time to find out how our millions are doing there!";
			link.l1.go = "BS_F1_40";
		break;

		case "BS_F1_40": //Максин
			dialog.text = "Of course I'm with you! There were some gloomy guys hanging around here yesterday, obviously not local. I don't want to take any chances.";
			link.l1 = "Get ready, I'll take you on board.";
			link.l1.go = "BS_F1_40_1";
			pchar.quest.BSHangover_MaksOnShip.win_condition.l1          = "location";
			pchar.quest.BSHangover_MaksOnShip.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.BSHangover_MaksOnShip.function             = "BSHangover_MaksOnShip";
		break;

		case "BS_F1_40_1":
			npchar.dialog.currentnode = "BS_F1_40_2";
			DialogExit();
		break;

		case "BS_F1_40_2": //Максин
			dialog.text = "Wait a minute, I'll pack my things.";
			link.l1 = "Okay, then you'll catch up.";
			link.l1.go = "BS_F1_40_1";
		break;

		//Плывём на Бермуды. Удаляем Флинта из пленников. Сходим на берег, подбегает матрос.

		case "BS_F1_41": //Матрос
			dialog.text = "Captain! The prisoner has escaped! The shackles are opened!";
			link.l1 = "";
			link.l1.go = "BS_F1_41exit";
		break;

		case "BS_F1_41exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10);
			StartInstantDialog("BS_Vein", "BS_F1_42", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_42": //Вейн
			dialog.text = "Holy shit! How?";
			link.l1 = "Inspect every stone, every palm tree here! Why did you get up? RUN!";
			link.l1.go = "BS_F1_42exit";
		break;

		case "BS_F1_42exit":
			DialogExit();
			SetLaunchFrameFormParam("It's been 12 hours of searching.", "", 0.1, 2.0);
			LaunchFrameForm();
			StartInstantDialogNoType("BS_Vein", "BS_F1_43", "Quest\BlackSails\BS_Final_1.c");
		break;

		//Табличка 'Прошло 12 часов поисков'

		//Таверна. Подходит Вейн.

		case "BS_F1_43": //Вейн
			dialog.text = "";
			link.l1 = "No trace?";
			link.l1.go = "BS_F1_44";
		break;

		case "BS_F1_44": //Вейн
			dialog.text = "I fell through the ground. What's on the ship? Do you understand how he was able to escape?";
			link.l1 = "Either he was badly searched or someone helped him.";
			link.l1.go = "BS_F1_45";
		break;

		case "BS_F1_45": //Вейн
			dialog.text = "Silver? It's a fox, not a human. I don't trust him!";
			link.l1 = "Maybe, but Silver hasn't gone anywhere and it's too early to blame him. In the cabin of the Walrus, I found Flint's logbook and the book of Marcus Aurelius.";
			link.l1.go = "BS_F1_46";
		break;

		case "BS_F1_46": //Вейн
			dialog.text = "I saw his log. Everything is encrypted.";
			link.l1 = "That's why we will not suspect Mr. Silver of anything, but we will be extremely considerate and polite with him.";
			link.l1.go = "BS_F1_47";
		break;

		case "BS_F1_47": //Вейн
			dialog.text = "What the hell are you talking about? Aaaa... I understand. Ciphers!";
			link.l1 = "Exactly. Let's go to the others, to the residence.";
			link.l1.go = "BS_F1_47exit";
		break;
		case "BS_F1_47exit": //Вейн
			AddQuestRecord("BSHangover", "10");
			BSChaseBegun_unlock_townhall();
			chrDisableReloadToLocation = false;
			DialogExit();
			Lai_SetActorTypeNoGroup(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			RemoveCharacterCompanion(PChar, npchar);
			pchar.quest.BSHangover_TownHall.win_condition.l1          = "location";
			pchar.quest.BSHangover_TownHall.win_condition.l1.location = "pirates_townhall";
			pchar.quest.BSHangover_TownHall.function             = "BSHangover_TownHall";
		break;

		//Запись в СЖ: 'Флинт, как угорь выскользнул из трюма и растворился неизвестно где. Остался только его судовой журнал и старая, зачитанная книга, за авторством римского императора. Стоит уговорить Сильвера, помочь с расшифровкой. И не давить на него. Нутром чую, без его участия, побег Флинта не обошёлся'.

		//Идём в резиденцию. Гатри, Макс, Вейн, ГГ, Бонни, Рекхэм, Сильвер.

		case "BS_F1_48": //ко всем
			dialog.text = "";
			link.l1 = "So here's what we have. Flint escaped from the ship, miraculously opening the shackles. The boats are in place, which means he swam here. Perhaps he borrowed a boat from one of the locals and is now heading for our money. And to hell with it! Sooner or later, he'll get caught. The good news is that we have his logbook encrypted. And the key to the cipher is most likely this book.";
			link.l1.go = "BS_F1_49";
		break;

		case "BS_F1_49": //Гатри
			dialog.text = "And Mr. Silver perfectly breaks any ciphers, as well as locks!";
			link.l1 = "";
			link.l1.go = "BS_F1_49_1";
		break;

		case "BS_F1_49_1": //Гатри
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Silver", "BS_F1_50", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_50": //Сильвер
			dialog.text = "If you're talking about Flint's shackles, then I assure you, I have nothing to do with it! And in decoding the log, I will be happy to help. For a share in the treasure. Even if not equal. Is it a deal?";
			link.l1 = "";
			link.l1.go = "BS_F1_50_1";
		break;

		case "BS_F1_50_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_51", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_51": //Вейн
			dialog.text = "Deal. But you'll do the decryption under the supervision of Ann and a couple of Miss Guthrie's mercenary shooters.";
			link.l1 = "";
			link.l1.go = "BS_F1_51_1";
		break;

		case "BS_F1_51_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Silver", "BS_F1_52", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_52": //Сильвер
			dialog.text = "Well, I'm ready to get started. May I take a look at the magazine and the book?";
			link.l1 = "Here, have fun. I'll be back in a few hours.";
			PlaySound("interface\important_item.wav");
			Log_Info("You gave away Flint's book and magazine");
			link.l1.go = "BS_F1_52exit";
		break;

		case "BS_F1_52exit": //Сильвер
			DialogExit();
			Lai_SetActorTypeNoGroup(npchar);
			AddQuestRecord("BSHangover", "11");
			pchar.quest.BSHangover_Cutscene.win_condition.l1          = "location";
			pchar.quest.BSHangover_Cutscene.win_condition.l1.location = "pirates_tavern";
			pchar.quest.BSHangover_Cutscene.function             = "BSHangover_Cutscene";
		break;

		//Передаём то и другое.

		//Запись в СЖ: 'Сильвер занят расшифровкой. Пойти, что ли выпить? Или искать Флинта? Местные течения, небольшой баркас или тартану, могут унести куда – угодно, хоть в открытый океан. Или чёрт с ним с Флинтом. Всё - таки такой человек, как он, заслуживает шанс. Да, буду считать это форой, из уважения. Пойду выпью!'

		//Идём в таверну, садим ГГ за столик, бухаем. Типо кат сцена (первая бля кат сцена!) Показываем табличку 'Прошло три часа размышлений и возлияний'.

		//Запись в СЖ: 'Пора проведать нашего дешифратора!'

		//Идём в резиденцию. Сильвер за столом, Гатри, Бонни, Вейн.

		case "BS_F1_53": //Сильвер
			dialog.text = "";
			link.l1 = "Any results?";
			link.l1.go = "BS_F1_54";
		break;

		case "BS_F1_54": //Сильвер
			dialog.text = "Yes. Here, check it out.";
			link.l1 = "21°3N, 80°00W. 15 25 N, 61 20 W. 12°07N61°40W. 72° 25'N 19° 00'W. 19°30N 80°30W.";
			link.l1.go = "BS_F1_55_1";
		break;

		case "BS_F1_55_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_55", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_55": //Вейн
			dialog.text = "Coordinates? What are we waiting for?";
			link.l1 = "There are two more pages of coordinates... And no leads? Does Aurelius mention any island? There must be something?!";
			link.l1.go = "BS_F1_56_1";
		break;

		case "BS_F1_56_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_56", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_56": //Сильвер
			dialog.text = "It takes more time. We need to study the book, look for clues, check the coordinates!";
			link.l1 = "Admit it to yourself. Flint has fucked us and is now heading to the coordinates he knows only! Where to? Yes, anywhere! There are hundreds of islands and reefs here. Damn, damn, damn!!!";
			link.l1.go = "BS_F1_57_1";
		break;

		case "BS_F1_57_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_57", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_57": //Вейн
			dialog.text = "Are you just giving up like that? I thought better of you!";
			link.l1 = "Here's the money that was in Flint's cabin. I am sure that this is part of the Urca gold. Five hundred thousand each. If there's any movement with the coordinates, let me know. I'm washing my hands of it!";
			if(sti(pchar.money) < 5000000)	link.l1 = "Here's the money that was in Flint's cabin. I am sure that this is part of the Urca gold. Five hundred thousand each. Oh, sorry, I've already spent them. Take as much as you have, the rest will be my debt. If there's any movement with the coordinates, let me know. I wash my hands of it!";
			link.l1.go = "BS_F1_57exit";	//минус 2кк.
		break;

		case "BS_F1_57exit": //Вейн
			Lai_SetActorTypeNoGroup(npchar);
			AddMoneyToCharacter(pchar, -4000000);
			AddQuestRecord("BSHangover", "13");
			CloseQuestHeader("BSHangover");
			pchar.questdata.ChernyeParusa = 1;
			DialogExit();
			sld = CharacterFromID("BS_Silver");
			sld.location = "none";
			sld = CharacterFromID("BS_Rakham");
			sld.location = "none";
			sld = CharacterFromID("BS_Vein");
			sld.location = "none";
			sld = CharacterFromID("BS_Bony");
			sld.location = "none";
			sld = CharacterFromID("BS_Maks");
			sld.location = "none";
			BS_ReplaceHostessWithMaks();

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_14_WhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: 'Несколько сотен возможных мест. Годы поисков, десятилетия уйдут на это. Тут всё ещё есть чем занять себя, клады, жирные торгаши, дуэли и осады фортов! Займусь развитием своей колонии или стану грозой Мэйна. Но навсегда запомню капитана Джеймса, мать его Флинта и сто пятьдесят миллионов причин его ненавидеть или любить. Авантюра вышла запоминающаяся! Нужно отдать ему должное'.

		//ФиналОчка. Макс теперь мадам в ПР со стандартными диалогами. Гатри – губернатор Бермуд. Про Вейна можно пустить слух по алкашам, что он отплыл на Нассау и ввязался в войну с колониальными властями. Сильвер? – гы гы. Читаем Остров Сокровищ.


	}
}
