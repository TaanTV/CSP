
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//Скипаем с отравления три дня. ГГ приходит в себя в комнате таверны. Запись в СЖ: «Неожиданно. Но предсказуемо. Флинт поимел нас всех. Кто бы мог подумать. Хорошо, что жив(ва) остался(лась)! Нужно разобраться в происходящем. Дьявол, как же мутит то!

		//Далее, если договорились поймать Флинта для разведки – Вейна нет на Багамах. Если не договаривались – он в таверне за столом пьянствует.

		//Спускаемся в таверну. Вариант без Вейна. Подходит Макс// ВАЖНО! этот вариант для финала 3 7.04.2023

		case "BS_F1_1":	//Максин
			dialog.text = "You're finally awake, you were out the longest.";
			link.l1 = "Is everyone alive? What's new?";
			link.l1.go = "BS_F1_2";
		break;

		case "BS_F1_2": //Максин
			dialog.text = "Everybody's alive, he put belladonna in the wine. Inez gave us all a drink of charcoal and God knows what else. Puked all over the place, but we survived.";
			link.l1 = "I'll be sure to thank her somehow. So what's the news? Flint? Gold?"; //для въедливых, можно прописать какой то бонусный диалог с Инес. благодарности ГГ, попытка сунуть денег и посыл в пешее эротическое от Инес. это вполне в её характере 7.04.2023
			link.l1.go = "BS_F1_3";
		break;

		case "BS_F1_3":	//Максин
			dialog.text = "No Flint, no gold. There's only one chest of doubloons in the warehouse, about fifty thousand each. And a note. 'Sorry, divide this up and forget about 'Urka' and Flint. It's the right thing to do. You wouldn't understand anyway. Ф.'";
			link.l1 = "Fucking prude! And I almost believed in his 'friendship'. Where are the others?";
			link.l1.go = "BS_F1_4";// получаем 50000 7.04.2023
			AddMoneyToCharacter(PChar, 50000);
		break;

		case "BS_F1_4":	//Максин
			dialog.text = "Eleanor's at her place, with Rackham and Bonnie, all three of them mad as hell. Always hitting things and yelling at each other. Vane, as soon as he was on his feet, hoisted the sails and went off somewhere.";
			link.l1 = "I think it's best to stay out of the residence for now. I'm gonna go get some air.";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: «Трудно думать, когда тебя постоянно тошнит. Но нужно что-то делать. Попробую подключить разведку. Какой там пароль? На Антигуа! В путь».

		//Вариант с Вейном финал номер один если убил Бонса 7.04.2023

		//Подходит Макс

		case "BS_F1_5":	//Максин
			LAi_SetActorType(npchar);
			dialog.text = "You're finally awake, you were out the longest.";
			link.l1 = "Is everyone alive? What's new?";
			link.l1.go = "BS_F1_6";
		break;

		case "BS_F1_6": //Максин
			dialog.text = "Everybody's alive, he put belladonna in the wine. Inez gave us all a drink of charcoal and God knows what else. Puked all over the place, but we survived.";
			link.l1 = "I'll be sure to thank her somehow. So what's the news? Flint? Gold?"; //для въедливых, можно прописать какой то бонусный диалог с Инес. благодарности ГГ, попытка сунуть денег и посыл в пешее эротическое от Инес. это вполне в её характере 7.04.2023
			link.l1.go = "BS_F1_7";
		break;

		case "BS_F1_7":	//Максин
			dialog.text = "No Flint, no gold. There's only one chest of doubloons in the warehouse, there's about fifty thousand for everyone. And a note: \nI'm sorry, divide this up and forget about 'Urka' and Flint. It's the right thing to do. You wouldn't understand anyway. Ф.'";
			link.l1 = "Fucking prude! And I almost believed in his 'friendship'. Where are the others?";
			link.l1.go = "BS_F1_8";
			AddMoneyToCharacter(PChar, 50000);
		break;

		case "BS_F1_8":	//Максин
			dialog.text = "In the residence, Charles and Eleanor are figuring out who has bigger balls. Constantly yelling and hitting things, then they get quiet. They'll either stab each other or fuck each other. Or both.";
			link.l1 = "They weren't married before? Mm-hmm. You don't have to answer that. Any leads?";
			link.l1.go = "BS_F1_9";
		break;

		case "BS_F1_9":	//Максин
			dialog.text = "I need to get back to Port Royal, maybe the girls heard something.";
			link.l1 = "Well, in that case, welcome aboard! Let's leave the lovebirds to work things out. I hope they fuck and not kill each other.";
			link.l1.go = "BS_F1_9exit";
		break;

		case "BS_F1_9exit":	//Максин
			DialogExit();
			PChar.quest.BSHangover_PortRoyal.win_condition.l1 = "location";
			PChar.quest.BSHangover_PortRoyal.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.BSHangover_PortRoyal.function = "BSHangover_PortRoyal";
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddQuestRecord("BSHangover", "2");
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_7_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;
		
		case "BS_F1_8_MaksRoyal":	//Максин
			chrDisableReloadToLocation = false;
			dialog.text = "Thank you. I'll need some time to gather information. You can rest in the tavern for a few days.";
			link.l1 = "All right, well, I'm gonna go see Wayne and Guthrie. I think they've calmed down.";
			link.l1.go = "BS_F1_8_MaksRoyal_exit";
		break;

		case "BS_F1_8_MaksRoyal_exit":
			DialogExit();
			BS_ReplaceHostessWithMaks();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", "none", "", "", "", -1);
			AddQuestRecord("BSHangover", "3");
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

			sld = CharacterFromID("gatri_temp");
			ChangeCharacterAddressGroup(sld, "Nassau_OfisGatri", "quest", "quest5");
			CharacterTurnToLoc(sld, "reload", "reload1_back");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_10";
			BS_GatriHomeGuardsOn();
			LocatorReloadEnterDisable("Nassau_town", "houseS1", false);
		break;

		//Запись в СЖ: «Флинт не мог испариться бесследно и в Европу, ему путь заказан. Попробуем узнать что-то с помощью пташек Макс. В Порт Рояль!»

		//Далее вариант поисков Флинта, без договора с Бонсом

		//Отвозим Макс в Порт Рояль. Она покидает корабль. Заменяем мадам на Макс.

		//Запись в СЖ: «Максин пока займётся сбором слухов, а я проведаю Вейна и мисс Гатри»

		//Пиздуем на Багамы. В резиденции Гатри. Вейна пока нигде нет, после диалога, ставим его в комнату таверны.

		case "BS_F1_10": //Гатри
			dialog.text = "";
			link.l1 = "Has the storm subsided? When I left this harbor, the walls were shaking and the rats were drowning in droves!";
			link.l1.go = "BS_F1_11";
		break;

		case "BS_F1_11": //Гатри
			dialog.text = "That disgusting, narcissistic, uncouth cretin! How dare he! I never want to see him again! Don't remind me of him! Better yet, go after him! To hell with him!";
			link.l1 = "";
			LAi_SetActorTypeNoGroup(npchar);
			link.l1.go = "BS_F1_11_exit";
			sld = CharacterFromID("Nassau_tavernkeeper");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_12";
		break;
		
		case "BS_F1_11_exit": //Гатри
			DialogExit();
			LocatorReloadEnterDisable("Nassau_town", "houseS1", true);
			DoReloadCharacterToLocation("Nassau_Town", "reload", "houseS1");
		break;

		//Выкидывает нас на порог. Дверь закрыта.

		//Идём в таверну. Ставим Вейна в комнату.

		//Подходим к Инес.

		case "BS_F1_12": //И
			dialog.text = "";
			link.l1 = "Is Wayne upstairs?";
			link.l1.go = "BS_F1_13";
		break;

		case "BS_F1_13": //И
			dialog.text = "Three days old. He's had a barrel of rum and he's asking for more.";
			link.l1 = "Wait for the rum, we need to talk.";
			link.l1.go = "BS_F1_13exit";
		break;

		case "BS_F1_13exit": //И
			DialogExit();
			RestoreOldDialog(npchar);
			DoReloadCharacterToLocation("Nassau_tavern_upstairs", "goto", "goto1");
			pchar.quest.BSHangover_Vein.win_condition.l1          = "location";
			pchar.quest.BSHangover_Vein.win_condition.l1.location = "Nassau_tavern_upstairs";
			pchar.quest.BSHangover_Vein.function             = "BSHangover_Vein";
		break;

		//Идём наверх

		case "BS_F1_14": //Вейн
			dialog.text = "Get out!";
			link.l1 = "What a stench! Are you getting drunk in here? Get your head together. We may have a lead on Flint! You with me?";
			link.l1.go = "BS_F1_15";
		break;

		case "BS_F1_15": //Вейн
			dialog.text = "Leads? Hell, yeah, I'm with you! And burn that Miss Arrogant Ass to the ground!";
			link.l1 = "That's fine. I won't go into the nature of the conflict. Join the squadron for Port Royal!";
			link.l1.go = "BS_F1_15exit";
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));
			BSRepairShip(npchar);
			SetCrewQuantityFull(npchar);
			npchar.ship.Crew.Morale = 60+rand(40);
			ChangeCrewExp(npchar, "Sailors", 60+rand(40));
			ChangeCrewExp(npchar, "Cannoners", 60+rand(40));
			ChangeCrewExp(npchar, "Soldiers", 60+rand(40));
			AddQuestRecord("BSHangover", "4");
			npchar.location = "none";
			pchar.quest.BSHangover_RoyalVein.win_condition.l1          = "location";
			pchar.quest.BSHangover_RoyalVein.win_condition.l1.location = "PortRoyal_SecBrRoom";
			pchar.quest.BSHangover_RoyalVein.function             = "BSHangover_RoyalVein";	
		break;

		case "BS_F1_15exit": //Вейн
			DialogExit();
			DoReloadCharacterToLocation("Nassau_town", "reload", "reload4_back");
			npchar.dialog.currentnode = "BS_F1_15Vein";
		break;

		case "BS_F1_15Vein": //Вейн
			dialog.text = "Flint will pay!";
			link.l1 = "He can't get away from us.";
			link.l1.go = "BS_F1_15Veinloopexit";
		break;
		
		case "BS_F1_15Veinloopexit": //Вейн
			DialogExit();
			npchar.dialog.currentnode = "BS_F1_15Vein"
		break;
		//Запись в СЖ: «Гатри и Вейн поссорились. Ничего нового. Главное мы снова в деле. Пора проведать Макс»

		//Без приключений плывём в Порт Рояль. Идём в кабинет Макс. Вейн прицепом.

		case "BS_F1_16": //Максин
			dialog.text = "";
			link.l1 = "What news, ma'am?";
			link.l1.go = "BS_F1_17";
		break;

		case "BS_F1_17": //Максин
			dialog.text = "Good day to you, too. This is unexpected news. We got a new girl from Bridgetown, and she tells me there's a pirate in the joint. Spreading gold by the handful, drunkenly telling every girl how his best friend and captain dumped him. And he loved him like his own father. And on and on in the same vein. And this sailor's name is John Stinger.";
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
			dialog.text = "Silver?! He once boasted that his nickname was Whore Sting!";
			link.l1 = "We've got to hurry. I don't believe Flint just wrote him off the ship!";
			link.l1.go = "BS_F1_18exit";

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
		
		case "BS_F1_18exit": //Вейн
			DialogExit();
			DoReloadCharacterToLocation("PortRoyal_town", "reload", "reload9_back");
			npchar.dialog.currentnode = "BS_F1_15Vein";
		break;
		
		case "BS_F1_SearchStinger":
			dialog.text = "";
			link.l1 = "Hi. I'm looking for someone. Uh, have you seen a John Stinger? Or maybe John Silver? He still wears a wooden leg. I can pay good money for information.";
			if(npchar.id == "BridgetownJailOff")
			{
				link.l1 = "Hi. I apologize for the indiscreet question, but do you happen to have a man named John Stinger among your 'mentees'? Or maybe John Silver?  He also wears a wooden leg.";
			}
			link.l1.go = "BS_F1_SearchStinger_1";
		break;

		case "BS_F1_SearchStinger_1":
			dialog.text = "I'm sorry, but this is the first time I've heard that name. I can't help you.";
			link.l1 = "Too bad.";
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

		//Запись в СЖ: «Есть зацепка, в борделе на Барбадосе, сорит деньгами и жалуется на жизнь Джон Сильвер. Нужно успеть туда раньше Флинта и подготовить засаду!»

		//Плывём на Барбадос. В борделе никто ничего про Сильвера-Стингера не знает. Тыкаемся во все двери. После того, как оббежали всех (бармен, ПУ, верфь, церковь, магазин, банк) дзынь! Запись в СЖ: «Никто не видел или не хочет говорить о Сильвере или Стингере, или ком-то похожем на него. Остаётся проверить тюрьму!»

		//Идём в тюрячку. Комендант, тоже шлёт нахой. В расстроенных чувствах уходим. На переходе Форт-Гор Ворота, в локации ворот, подходит сам Сильвер.

		case "BS_F1_19": //Сильвер
			dialog.text = "Good to see you companions! You're thinking faster than Flint's!";
			link.l1 = "You deliberately used whores to get the word out about poor drunk Stinger to Maxine? Risky move. Flint could have gotten to her first!";
			link.l1.go = "BS_F1_19exit";
		break;

		case "BS_F1_19exit":
			StartInstantDialog("BS_Vein", "BS_F1_20", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_20": //Вейн
			dialog.text = "Holy shit! Maxine! If Flint was thinking what you're thinking, she's in danger!";
			link.l1 = "";
			link.l1.go = "BS_F1_20exit";
		break;

		case "BS_F1_20exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_21", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_21": //Сильвер
			dialog.text = "Oh, our Max can take care of herself. She's not that poor slave girl from Louisiana who was sold to a brothel when she was a kid.";
			link.l1 = "And yet, I sense she's in trouble. We must hurry to Port Royal.";
			link.l1.go = "BS_F1_22";
		break;

		case "BS_F1_22": //Сильвер
			dialog.text = "Or wait a little longer. What would Flint do to her? Ambush her, and I'm the bait. Poor, drunk Silver.";
			link.l1 = "";
			link.l1.go = "BS_F1_22exit";
		break;

		case "BS_F1_22exit":
			StartInstantDialogNoType("BS_Vein", "BS_F1_23", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_23": //Вейн
			dialog.text = "Stop baring your teeth. How'd you end up here, anyway? Bad blood?";
			link.l1 = "";
			link.l1.go = "BS_F1_23exit";
		break;

		case "BS_F1_23exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_24", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_24": //Сильвер
			dialog.text = "Almost. Flint came on the Walrus and gave the order to sail at once. 'I'll talk to you later John, I think you'll understand,' he said, and gave me that Flint-esque glare. You know. And that's when it hit me. I look on deck, and all the faces on the deck are strangers, when did he get a crew? Something's fishy, I think.";
			link.l1 = "What happened next? No embellishments, please!";
			link.l1.go = "BS_F1_25";
		break;

		case "BS_F1_25": //Сильвер
			dialog.text = "When we were ten miles from the Bahamas, the sailors took out their new pistols and shot all the veterans with whom we had taken the gold of the 'Urki'! The deck was covered with blood, and they were killing the survivors with cleavers. So, I ran to the cabin, grabbed the belt with the gold, an empty rum barrel and went overboard. The current carried me to Tortuga, where I hired fishermen to ferry me away. Eventually, I settled here.";
			link.l1 = "Interesting, so Flint planned all this in advance and wasn't going to share it with anyone.";
			link.l1.go = "BS_F1_25exit";
		break;

		case "BS_F1_25exit":
			StartInstantDialogNoType("BS_Vein", "BS_F1_27", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_26": //Вейн
			dialog.text = "I'm gonna shove that gold down his throat until it comes out the bottom!";
			link.l1 = "";
			link.l1.go = "BS_F1_27";
		break;

		case "BS_F1_27": //Вейн
			dialog.text = "I'm gonna shove that gold down his throat until it comes out the bottom!";
			link.l1 = "";
			link.l1.go = "BS_F1_27exit";
		break;

		case "BS_F1_27exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_28", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_28": //Сильвер
			dialog.text = "What's up? I'll go to the whorehouse, play the desperate drunk, and you lurk here and move the ships to Rigged Point Bay. And, uh, uh. Uh. Can you spare some money for the whorehouse? I've had enough of this.";
			link.l1 = "Here you go. It's the rest of the fifty thousand Flint left us all.";	//- 12000
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
			dialog.text = "That's settled, then. I'll take care of the ships while you get a room at the tavern, we'll probably be here for a while.";
			link.l1 = "Uh, okay.";
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
			link.l1 = "Thank you.";
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
			dialog.text = "Handsome Johnny said to get you ready. The 'Walrus' is in the roadstead. He'll lure the hunter out to the cave here on the island.";
			link.l1 = "Thanks, babe.";
			link.l1.go = "BS_F1_30";
		break;

		case "BS_F1_30": //Шлюха
			dialog.text = "And the coin?";
			link.l1 = "Oh, yeah. Here's some coins for you."; //- 100
			link.l1.go = "BS_F1_30exit";
		break;

		case "BS_F1_30exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			StartInstantDialog("BS_Vein", "BS_F1_31", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_31": //Вейн
			AddMoneyToCharacter(PChar, -100);
			dialog.text = "It's just so simple. I don't like it!";
			AddQuestRecord("BSHangover", "7");
			link.l1 = "Me, too. Let's split up. Take your men and take up positions around the cave entrance. I'll go inside. If you hear any trouble, be on your guard, don't go in, sit in ambush. Let's see how this plays out.";
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

		//Вейн уходит. Запись в СЖ: «Ну что же, посмотрим, какая рыба заглотила наживку!»

		//Идём в пещеру. Войдя – запускается аларм и в логе таймер 60 сек. «Джон в беде, нужно поспешить на выручку!» – это тоже в логе. Бежим в место шахтных выработок. Там, сразу гасим таймер, Сильвер – становится смертным. В пещёре 10-12 ОЗГов, начинается замес. Сильвер погиб – провал квеста, принудительный – экран смерти. Сильвер выжил – продолжаем.

		case "BS_F1_32": //Сильвер
			dialog.text = "";
			link.l1 = "There's no Flint! Damn it!";
			link.l1.go = "BS_F1_33";
		break;

		case "BS_F1_32_beaten": //Сильвер
			dialog.text = "Oh, I think I've been stabbed right through...";
			link.l1 = "I don't see anything serious, you'll live.";
			link.l1.go = "BS_F1_32_beaten_1";
		break;

		case "BS_F1_32_beaten_1": //Сильвер
			dialog.text = "Are you sure? I feel a lot worse.";
			link.l1 = "There's no Flint! Damn it!";
			link.l1.go = "BS_F1_33";
		break;

		case "BS_F1_33": //Сильвер
			dialog.text = "Right, did you notice? Those are the faces I was talking about. They're definitely not from around here. I know most of the hired guns. Where's Wayne?";
			link.l1 = "Outside, in an ambush. Let's not waste any time, get into the bay and try to board the Walrus!";
			link.l1.go = "BS_F1_33_2";
		break;

		case "BS_F1_33_2":
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "BS_F1_33_1";
			DialogExit();
		break;
		case "BS_F1_33_1":
			dialog.text = "I'm gonna sit here for a while, and then I'll be right behind you.";
			link.l1 = "Come on, don't play dumb, faker.";
			link.l1.go = "BS_F1_33_2";
		break;

		//Бяжим к выходу. Снаружи идёт замес. Опять озги (модельки), Вейн, Бонни, Рекхэм и пара – тройка их матросов против десятка наёмников. Опять та же история, если кто то из ключевых героев гибнет – сразу экран смерти. Завалили геев. Говорим с Вейном.

		case "BS_F1_34": //Вейн
			dialog.text = "These, (kicks the corpse with his foot), came out of the undergrowth as soon as you entered the cave, I had to intervene.";
			link.l1 = "It was hot inside, too! Flint's not among the corpses! We've got to get to the ships and try to get the Walrus. Follow me!";
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

		//Запись в СЖ: «На наживку клюнула целая стая рыбин! Но главного лосося, среди них не было. «Морж» всё ещё на рейде, нужно взять его на абордаж и быстро, пока сторожевики не решили посмотреть, кто там палит из пушек».

		//Скачем в Риггед Поинт, садимся на корабли берём Моржа на абордаж. В каюте рубимся с Флинтом. Суровый по статам мужик с какой нибудь уникальной саблей. Банки, жратва – всё по полной. Порубили. Заводит диалог// там драка в каюте подвязана на участие Виспер в ней. если её нет в команде, то спавн подсосов Флинта явно лишний. он и так крут. оставить спавн, если ГГ с Виспер или шарик, ему вроде ржавая помогает в каютных замесах 7.04.2023

		case "BS_F1_35": //Флинт
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (int z = 1; z <= 6; z++)
			{
				sld = CharacterFromID("FlintOff"+z);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			PChar.quest.BSHangover_Fail1.over = "yes";

			dialog.text = "That's not how it was supposed to go at all! I'm sorry. But hear me out!";
			link.l1 = "Not like this?! We weren't supposed to survive? I was stupid to think you were my friend! Goddamn it, we could do stuff like this together! Why would you do that?";
			link.l1.go = "BS_F1_36";
		break;

		case "BS_F1_36": //Флинт
			dialog.text = "It's complicated, buddy. If you hadn't started the chase, if I hadn't fallen for John's trick. Things would have been different. No one would have walked away hurt. I thought of everything! I thought I'd thought of everything. This money isn't for me personally, it's for the foundation of a new, free nation. A republic! Without kings and their wars, a place where free men can live according to their conscience, not depending on the whims of bankers or aristocrats! This is the New World, so let it be the beginning of a New, better World! Do you understand?!";
			link.l1 = "What are you talking about? What republic? Sharpe tried it, Avery tried it. How did it end? Blood. The blood of the very free people you're trying to build a new world for! Or is your 'world' special? What is it?";
			link.l1.go = "BS_F1_37";
		break;

		case "BS_F1_37": //Флинт
			dialog.text = "This is not the place for philosophical disputes. Let's end it all and talk like civilized people.";
			link.l1 = "Hell no. You're going in the hold now. In shackles. And we'll all talk together. Together with the men you tried to poison! And pray to all the gods you know that I can convince Wayne not to keelhaul you.";
			link.l1.go = "BS_F1_38";
		break;

		case "BS_F1_38": //Флинт
			dialog.text = "I forgot I was dealing with a pirate. All right, here's my weapon. Lead the way.";
			TakeNItems(PChar, "blade43", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You got Narwhal!");
			link.l1 = "";
			link.l1.go = "BS_F1_38exit";
		break;

		case "BS_F1_38exit": //Флинт
			for (int k = 1; k <= 6; k++)
			{
				sld = CharacterFromID("FlintOff"+k);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeDay = 0;
			}
			
			DialogExit();

			QuestAboardCabinDialogFree();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "");
			DeleteAttribute(pchar, "FlintBoardingDialog");
			LAi_KillCharacter(npchar);
			DeleteCharacter(npchar);
			SetLaunchFrameFormParam("Your men take Flint away. Meanwhile, you search his quarters. A book catches your eye - Marcus Aurelius' 'Meditations'. You take it, along with Flint's ship's log.", "", 0.1, 15.0);
			LaunchFrameForm();
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

		//ВАЖНО! Залочить возможность диалога с Флинтом в трюме, во избежание найма. Оставить фразу «Позже поговорим». 7.04.2023

		//Запись в СЖ: «Флинт пойман! Пытался нести какую -  то ахинею про Республику и свободных людей. Путь на Багамы, там расспросим подробнее, про Республику, а главное – про сто пятьдесят миллионов причин ввязаться в эту авантюру! Но сначала нужно проведать Макс в Порт Рояле. Компаньон как – никак». //тоже ВАЖНЫЙ момент, не забирая Максин из ПР можно словить софтлок. заблочить все двери на Багамах пока она не на корабле у нас 7.04.2023

		//Плывём в ПР, забираем Макс из борделя. С ней всё заебись.

		//Диалог в кабинете мадам.

		case "BS_F1_39": //Максин
			dialog.text = "";
			link.l1 = "I have news! Flint's in shackles, in the hold. Are you with us? Time to find out how our millions are doing!";
			link.l1.go = "BS_F1_40";
		break;

		case "BS_F1_40": //Максин
			dialog.text = "Of course I'm in! There were some creepy guys hanging around yesterday, obviously not from around here. I don't want to take any chances.";
			link.l1 = "Come on, I'll take you aboard.";
			link.l1.go = "BS_F1_40_1";
			SetFunctionExitFromLocationCondition("BSHangover_MaksOnShip", pchar.location, false);
			SetFunctionLocationCondition("BSHangover_FlintEscaped", "Nassau_town", false);
		break;

		case "BS_F1_40_1":
			npchar.dialog.currentnode = "BS_F1_40_2";
			DialogExit();
		break;

		case "BS_F1_40_2": //Максин
			dialog.text = "Just a minute, I'll get my things.";
			link.l1 = "Okay, then you'll catch up.";
			link.l1.go = "BS_F1_40_1";
		break;

		//Плывём на Багамы. Удаляем Флинта из пленников. Сходим на берег, подбегает матрос.

		case "BS_F1_41": //Матрос
			dialog.text = "Captain! The prisoner has escaped! The shackles are open!";
			link.l1 = "";
			link.l1.go = "BS_F1_41exit";
		break;

		case "BS_F1_41exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			StartInstantDialog("BS_Vein", "BS_F1_42", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_42": //Вейн
			dialog.text = "Holy shit! How?";
			link.l1 = "To see every rock, every palm tree! What are you doing? RUN!";
			link.l1.go = "BS_F1_42exit";
		break;

		case "BS_F1_42exit":
			DialogExit();
			SetLaunchFrameFormParam("It's been 12 hours of searching", "", 0.1, 2.0);
			LaunchFrameForm();
			StartInstantDialogNoType("BS_Vein", "BS_F1_43", "Quest\BlackSails\BS_Final_1.c");
		break;

		//Табличка «Прошло 12 часов поисков»

		//Улицы Нассау. Подходит Вейн. 7.04.2023

		case "BS_F1_43": //Вейн
			dialog.text = "";
			link.l1 = "No sign of him?";
			link.l1.go = "BS_F1_44";
		break;

		case "BS_F1_44": //Вейн
			dialog.text = "It's like he's fallen through the earth. What about the ship? Any idea how he got away?";
			link.l1 = "Either he was searched badly or someone helped him.";
			link.l1.go = "BS_F1_45";
		break;

		case "BS_F1_45": //Вейн
			dialog.text = "Silver? He's a fox, not a man. I don't trust him!";
			link.l1 = "Maybe, but Silver's not going anywhere and it's too early to blame him. In the Walrus' cabin I found Flint's logbook and a book by Marcus Aurelius.";
			link.l1.go = "BS_F1_46";
		break;

		case "BS_F1_46": //Вейн
			dialog.text = "I've seen his journal. It's all encrypted.";
			link.l1 = "That's why we're not going to suspect Mr. Silver of anything, and we're going to be delicate and polite to him.";
			link.l1.go = "BS_F1_47";
		break;

		case "BS_F1_47": //Вейн
			dialog.text = "What the hell are you talking about? Ahh. I got it. Ciphers!";
			link.l1 = "Right. Let's go to the others, to the house.";
			link.l1.go = "BS_F1_47exit";
		break;
		case "BS_F1_47exit": //Вейн
			AddQuestRecord("BSHangover", "10");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Nassau_town", "houseS1", false);
			BS_GatriHomeGuardsOff();
			DialogExit();
			Lai_SetActorTypeNoGroup(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			RemoveCharacterCompanion(PChar, npchar);
			pchar.quest.BSHangover_TownHall.win_condition.l1          = "location";
			pchar.quest.BSHangover_TownHall.win_condition.l1.location = "Nassau_OfisGatri";
			pchar.quest.BSHangover_TownHall.function             = "BSHangover_TownHall";
		break;

		//Запись в СЖ: «Флинт, как угорь выскользнул из трюма и растворился неизвестно где. Остался только его судовой журнал и старая, зачитанная книга, за авторством римского императора. Стоит уговорить Сильвера, помочь с расшифровкой. И не давить на него. Нутром чую, без его участия, побег Флинта не обошёлся».

		//Идём в дом Гатри. Гатри, Макс, Вейн, ГГ, Бонни, Рекхэм, Сильвер.

		case "BS_F1_48": //ко всем
			dialog.text = "";
			link.l1 = "So here's what we got. Flint escaped from the ship, somehow miraculously unlocked the shackles. The boats are here, which means he swam here. Maybe he borrowed a boat from one of the locals and now he's headed for our money. To hell with him! Sooner or later, he's gonna get caught. The good news is we have his logbook, encrypted. And the key to the code is probably this book.";
			link.l1.go = "BS_F1_49";
		break;

		case "BS_F1_49": //Гатри
			dialog.text = "And Mr. Silver is excellent at breaking any cipher, as well as locks!";
			link.l1 = "";
			link.l1.go = "BS_F1_49_1";
		break;

		case "BS_F1_49_1": //Гатри
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialogNoType("BS_Silver", "BS_F1_50", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_50": //Сильвер
			dialog.text = "If this is about Flint's shackles, I assure you I had nothing to do with it! I'd be happy to help you decipher the journal. For a share of the treasure. Even if it's not equal. Do we have a deal?";
			link.l1 = "";
			link.l1.go = "BS_F1_50_1";
		break;

		case "BS_F1_50_1":
			StartInstantDialogNoType("BS_Vein", "BS_F1_51", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_51": //Вейн
			dialog.text = "Deal. Except you'll do the decryption under the supervision of Anne and a couple of Ms. Guthrie's hired guns.";
			link.l1 = "";
			link.l1.go = "BS_F1_51_1";
		break;

		case "BS_F1_51_1":
			StartInstantDialogNoType("BS_Silver", "BS_F1_52", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_52": //Сильвер
			dialog.text = "Well, I'm ready to get started. May I see the magazine and the book?";
			link.l1 = "Here, have fun. I'll be back in a few hours.";
			PlaySound("interface\important_item.wav");
			Log_Info("You gave Flint's book and magazine");
			link.l1.go = "BS_F1_52exit";
		break;

		case "BS_F1_52exit": //Сильвер
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			sld = CharacterFromID("BS_Rakham");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("BS_Vein");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("BS_Bony");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("BS_Silver");
			LAi_CharacterDisableDialog(sld);
			LAi_SetPlayerType(PChar);
			ChangeCharacterAddressGroup(PChar, "Nassau_OfisGatri", "goto", "goto5");
			AddQuestRecord("BSHangover", "11");
			DeleteAttribute(PChar, "currentsoundtrack");
			LocatorReloadEnterDisable("Nassau_town", "houseS1", true);
			pchar.quest.BSHangover_Cutscene.win_condition.l1          = "location";
			pchar.quest.BSHangover_Cutscene.win_condition.l1.location = "Nassau_tavern";
			pchar.quest.BSHangover_Cutscene.function             = "BSHangover_Cutscene";
		break;

		//Передаём то и другое.

		//Запись в СЖ: «Сильвер занят расшифровкой. Пойти, что ли выпить? Или искать Флинта? Местные течения, небольшой баркас или тартану, могут унести куда – угодно, хоть в открытый океан. Или чёрт с ним с Флинтом. Всё - таки такой человек, как он, заслуживает шанс. Да, буду считать это форой, из уважения. Пойду выпью!»

		//Идём в таверну, садим ГГ за столик, бухаем. Типо кат сцена (первая бля кат сцена!) Показываем табличку «Прошло три часа размышлений и возлияний».

		//Запись в СЖ: «Пора проведать нашего дешифратора!»

		//Идём в резиденцию. Сильвер за столом, Гатри, Бонни, Вейн.

		case "BS_F1_53": //Сильвер
			dialog.text = "";
			link.l1 = "Any results?";
			link.l1.go = "BS_F1_54";
		break;

		case "BS_F1_54": //Сильвер
			dialog.text = "Yeah. Here you go.";
			link.l1 = "21°3N, 80°00W. 15 25 N, 61 20 W. 12°07N61°40W. 72° 25'N 19° 00'W. 19°30N 80°30W. 55,755831°, 37,617673° N55.755831°, E37.617673° 55°45.35′N, 37°37.06′E. 15°N, 30°E. 15 10,234, 30 -23,456. 15,23456, -30,67890. и так далее...";
			link.l1.go = "BS_F1_55_1";
		break;

		case "BS_F1_55_1":
			StartInstantDialog("BS_Vein", "BS_F1_55", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_55": //Вейн
			dialog.text = "Coordinates? What are we waiting for?";
			link.l1 = "There's two more pages of coordinates... And no clues? Does Aurelius mention an island? There must be something?!";
			link.l1.go = "BS_F1_56_1";
		break;

		case "BS_F1_56_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialogNoType("BS_Silver", "BS_F1_56", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_56": //Сильвер
			dialog.text = "I need more time. We need to study the book, look for clues, check against the coordinates!";
			link.l1 = "Admit it to yourselves. Flint's screwed us and he's heading to coordinates he knows! Where? Anywhere! There are hundreds of islands and reefs. Damn it, damn it, damn it, damn it!";
			link.l1.go = "BS_F1_57_1";
		break;

		case "BS_F1_57_1":
			StartInstantDialog("BS_Vein", "BS_F1_57", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_57": //Вейн
			dialog.text = "You're just giving up? I thought better of you!";
			link.l1 = "Here's the money that was in Flint's quarters. I'm sure it's part of Urka's gold. A million each. That's not so bad. Just think about it. Searching for all that gold without knowing the starting point would take years or even decades! Devoting your whole life to prospecting? There are better things to do. If there's any progress on the coordinates, let me know. I'm outta here!";
			if(sti(pchar.money) < 5000000)	link.l1 = "Here's the money that was in Flint's quarters. I'm sure it's part of Urka's gold. A million each. Oh, I'm sorry, I've already spent it. Take what you have, I'll owe you the rest. If there's any progress on the coordinates, let me know. I'm outta here!";
			link.l1.go = "BS_F1_57exit";	//минус 4кк.
		break;

		case "BS_F1_57exit": //Вейн
			bDisableOfficers = false;
			Lai_SetActorTypeNoGroup(npchar);
			LAi_SetPlayerType(PChar);
			sld = CharacterFromID("BS_Silver");
			LAi_CharacterDisableDialog(sld);
			if (sti(pchar.money) >= 4000000)
			{
				pchar.makslover = true;
				SaveCurrentQuestDateParam("MaksLoverDateDay");
			}
			BS_ReplaceHostessWithMaks();
			AddMoneyToCharacter(pchar, -4000000);
			AddQuestRecord("BSHangover", "13");
			pchar.currentsoundtrack = "Theme_from_Black_Sails";
			CloseQuestHeader("BSHangover");
			pchar.questdata.ChernyeParusa = 1;
			DialogExit();
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_14_WhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
			}
			SetFunctionExitFromLocationCondition("BS_NassauCobHouseEnding_1", "Nassau_OfisGatri", false);
		break;

		//Запись в СЖ: «Несколько сотен возможных мест. Годы поисков, десятилетия уйдут на это. Тут всё ещё есть чем занять себя, клады, жирные торгаши, дуэли и осады фортов! Займусь развитием своей колонии или стану грозой Мейна. Но навсегда запомню капитана Джеймса, мать его Флинта и сто пятьдесят миллионов причин его ненавидеть или любить. Авантюра вышла запоминающаяся! Нужно отдать ему должное».

		//ФиналОчка. Макс теперь мадам в ПР со стандартными диалогами. Гатри – губернатор Бермуд. Про Вейна можно пустить слух по алкашам, что он отплыл на Нассау и ввязался в войну с колониальными властями. Сильвер? – гы гы. Читаем Остров Сокровищ.


	}
}
