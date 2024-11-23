
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

		//Условия – закончен морской файт у Мартиники, 'Морж' цел. У гг пиратский флаг. Иначе файт с флинтом. Весь квест запрет на смену флага.
		//Пляж Ламантен. ГГ, Флинт, Сильвер, Бонс. Бродят матросы, несколько штук.

		case "BS_KS_1":	//Флинт
			dialog.text = "Unexpected, but predictable.";
			link.l1 = "What? Oh, you mean the English? They're not going to take back the colony, are they?";
			link.l1.go = "BS_KS_2";
		break;

		case "BS_KS_2":
            dialog.text = "I have an idea where this patrol is coming from, but the assumptions need to be checked. I don't think it's an attempt to retake the island, they'd do things very differently there. Line formation, parliamentarians, siege. I know all too well how His Majesty Charles II's fleet fights. No. This is something else. Mr. Silver, you're going with Captain "+GetFullName(pchar)+" to Fort de France. The mission is to retrieve the second part of the code. At any cost. Do you understand?";
            link.l1 = "";
			link.l1.go = "BS_KS_3_1";
		break;

		case "BS_KS_3_1":
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_3";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;

		case "BS_KS_3":	//Сильвер
            dialog.text = "Understandable. Why is captain so strict? I thought we were already friends.";
            link.l1 = "";
			link.l1.go = "BS_KS_4_1";
		break;

		case "BS_KS_4_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_4";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_KS_4":	//Флинт
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(npchar);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorTurnToCharacter(sld, npchar);
            dialog.text = "(Looks unblinkingly at Silver)";
            link.l1 = "";
			link.l1.go = "BS_KS_5_1";
		break;

		case "BS_KS_5_1":
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_5";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;

		case "BS_KS_5":	//Сильвер
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(npchar);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorTurnToCharacter(sld, npchar);
            dialog.text = "Khgm... Yes, yes, we will do it, Captain.";
            link.l1 = "";
			link.l1.go = "BS_KS_6_1";
		break;

		case "BS_KS_6_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_6";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_KS_6":
			SetQuestHeader("BSCourtlyPassions");
			AddQuestRecord("BSCourtlyPassions", "1");

            dialog.text = "As soon as you figure out the code, I'll be waiting for you at Ms. Guthrie's house. Good luck.";
            link.l1 = "To hell with it, Captain! Silver, follow me!";
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "BSCPFlint_talk");
			pchar.quest.BSCourtlyPassions_begin.over = "yes";
			DeleteAttribute(pchar, "LockMapReload");
			DeleteAttribute(npchar, "curtown");
			pchar.BSCPSailor_talk = true;
			pchar.BSCPSilver_talk = true;
			link.l1.go = "BS_KS_6_exit";
		break;

		case "BS_KS_6_exit":
			DialogExit();
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "Pirates_store", "", "", "", -1);
			//Запускаем Матроса.
			if(pchar.location == "LeFransua_town" || pchar.location == "FortFrance_town" ||  pchar.location == "Shore38" ||   pchar.location == "Shore39")
			{
				BSCourtlyPassions_sailor();
			}
			else
			{
				SetFunctionExitFromLocationCondition("BSCourtlyPassions_sailor_begin_again", pchar.location, true);
			}

		break;

		//Ставим Сильвера во временные оффы. Лучше сразу в абордаги, если возможно.

		case "BS_KS_7":	//Обращаемся к матросу
            dialog.text = "Orders?";
			string order1, order2, order3;
			if (pchar.nation != FRANCE)
			{
				order1 = "Get back on board and raise the French flag.";
				Flag_Change(FRANCE);
			}
			else order1 = "";
			if (pchar.location != "Shore39")
			{
				order2 = "Take the ship to Le Maren Bay.";
				pchar.location.from_sea = "Shore39";
			}
			else order2 = "";
			if (order1 == "" && order2 == "") order3 = "Get back to the ship and stay alert. If there's a patrol, tell them that the steering wheel is jammed, you can't get to the shipyard.";
			else order3 = "If there's a patrol, tell them that the steering wheel is jammed, you can't get to the shipyard.";
            link.l1 = order1+order2+order3;
			link.l1.go = "BS_KS_7_1";
		break;

		case "BS_KS_7_1":	//Обращаемся к матросу
			AddQuestRecord("BSCourtlyPassions", "2");
			dialog.text = "Yes, Captain!";
            link.l1 = "You're a good sailor, Sandro, and you've been with me the longest. Keep up the good work, and maybe one day we'll promote you to an officer.";
			link.l1.go = "BS_KS_7_2";
		break;

		case "BS_KS_7_2":	//Обращаемся к матросу
            dialog.text = "It's not my thing, Captain. There are a lot of responsibilities, and responsibilities. I'm a simple sailor and I don't want to change that.";
            link.l1 = "As you know. Okay, run, follow the order.";
			link.l1.go = "BS_KS_7_2_exit";
		break;

		case "BS_KS_7_2_exit":	//Обращаемся к матросу
			DialogExit();
			DeleteAttribute(pchar, "BSCPSailor_talk");
			LocatorReloadEnterDisable(pchar.location.from_sea, "boat", true);
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			PChar.MapBestTeleportDisable = true;
			LAi_ActorRunToLocation(npchar, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("Flint");
			DeleteAttribute(sld, "curtown");
			//Запускаем Сильвера.
			if(pchar.location == "FortFrance_town")
			{
				BSCourtlyPassions_sailor();
			}
			else
			{
				SetFunctionExitFromLocationCondition("BSCourtlyPassions_sailor_begin_again", pchar.location, true);
			}
		break;

		//Переместить корабль в Ле Марен

		//Запись в СЖ: Жаркая схватка у Нассау была. Какого дьявола тут забыли английские патрули? Ну да ладно, этим вопросом займётся Флинт, моя задача – добыть часть кода у Чарльза Вейна. Отправляюсь на Мартинику, нужно пристать в одной из бухт, мало ли чем там дело обернётся.

		//Залочить выход в море. Топаем в Форт де Франс ножками.

		//На следующей локе, Сильвер заводит диалог.

		case "BS_KS_8":	//Сильвер
			dialog.text = "You have a beautiful ship, and the crew are like eagles!";
            link.l1 = "Thank you. So what's the story with the two-half code? Just briefly, please. I'm not in the mood for stories.";
			link.l1.go = "BS_KS_9";
		break;

		case "BS_KS_9":
            dialog.text = "It's like a stick up your ass, captains, when you get captaincy: Listen to the order!!! Reefing the foretopsails!!! Left rudder!!!";
            link.l1 = "Ha. You're funny. I had a cook who also liked to make jokes.";
			link.l1.go = "BS_KS_10";
		break;

		case "BS_KS_10":
            dialog.text = "Any team needs such a person! And the sailor's strap doesn't seem so heavy then!";
			link.l1 = "Maybe. Yes, I was confused, they found him with a molt wrapped around his neck. In the hold. And no one has heard or heard a word. Why did you turn pale? I'm kidding. Haha.";
			link.l1.go = "BS_KS_11"
		break;

		case "BS_KS_11":
            dialog.text = "Haha. Okay, to the point. I got hold of a part of the logbook of a Spanish coaster. How I got it and what I did on the Spanish ship is a separate story. Long story short, glancing at the papers, I realized that the route of some very important ship was encrypted there, and I was fond of all sorts of ciphers and riddles back in the monastery, but this is also a separate story. I decided to celebrate the find in a brothel, and there is a girl there alone, Maxine's name. A Creole from Louisiana. She's a pretty little devil. What he's doing in bed... There are no words to describe it. But not only is the craftsman at the front, but everything is fine with his head. In every sense. She circled me drunk and tired of pleasures like a boy and took away the page with the encryption.";
            link.l1 = "It's interesting and almost funny if a page of one hundred and fifty million wouldn't be worth it.";
			link.l1.go = "BS_KS_12";
		break;

		case "BS_KS_12":
            dialog.text = "I agree. I only half remembered the page, I didn't have much time, you see. I've tried this and that with her, but the girl is smart and she has connections in the city like the governor. We decided to become partners and sell this code to one of the privateers or pirates. Her connections are most welcome here.";
            link.l1 = "Uh-huh, and then what?";
			link.l1.go = "BS_KS_13";
		break;

		case "BS_KS_13":
            dialog.text = "Well, she came out to XO Charles Wayne. Jack Wrexham. Jack is a good guy, you'll get to know him yourself and he was ready to make an honest exchange. Yes, but his team are thugs and scumbags. Someone heard something, and there was a massacre at the exchange site. Flint miraculously pulled me out, Maxine is with the pirates, they probably have the page with the code too.";
            link.l1 = "And why should we go to a brothel if the girl and the page are pirates? Where is their parking lot? In Le Francois?";
			link.l1.go = "BS_KS_14";
		break;

		case "BS_KS_14":
            dialog.text = "Yes, the birds sang that Max was in his nest, and Wayne was looking for a bigger ship and recruiting a team. I guess I've heard stories about 'Urca' too.";
            link.l1 = "I wonder if the girls are dancing... Let's go to the local innkeeper first. I want to ask you more about this Maxine.";
			link.l1.go = "BS_KS_14_1";
		break;

		case "BS_KS_14_1":
			AddQuestRecord("BSCourtlyPassions", "3");
			dialog.text = "To the tavern so to the tavern. You are captain here.";
            link.l1 = "The same thing.";
			link.l1.go = "BS_KS_14_2";
		break;

		case "BS_KS_14_2":
            DialogExit();
			DeleteAttribute(pchar, "BSCPSilver_talk")
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = CharacterFromID("FortFrance_tavernkeeper");
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_15";
		break;

		//Запись в СЖ 'Страница у девки, девка у пиратов, пираты в ларце, ларец на дубе... Ничего не понятно, но начать стоит с таверны, разузнать про эту Максин'.

		//Форт де Франс. У бармена интересуемся Максин

		case "BS_KS_15":	//Бармен
            dialog.text = "Welcome to our humble establishment, Captain. How can I help you?";
            link.l1 = "And how are you in the city with bodily pleasures? I'm sure that you have one slut, Creole.";
			link.l1.go = "BS_KS_16";
		break;

		case "BS_KS_16":
            dialog.text = "About the bed pleasures in the appropriate places, ask, "+ GetSexPhrase("monsieur", "mademoiselle") +". My place is decent.";
            link.l1 = "I understand. Will five hundred piastres help loosen your tongue?";
			link.l1.go = "BS_KS_17";
		break;

		case "BS_KS_17":
            dialog.text = "Five hundred? Do I look like a beggar? Five thousand pesos, and I'll tell you everything.";
			NextDiag.TempNode = "BS_KS_15";
			if (sti(pchar.money >= 5000))
			{
				link.l1 = "I'm listening.";
				link.l1.go = "BS_KS_18";
			}
			link.l2 = "Damn it, where did my purse go?";
			link.l2.go = "exit";
		break;

		case "BS_KS_18":
			AddMoneyToCharacter(pchar, -5000);
            dialog.text = "You need Maxine, she works at a local brothel. You'd better ask the hostess about her, she knows much better than me.";
            link.l1 = "And I paid you five thousand for it? Don't you want two feet of cold steel in your belly?";
			link.l1.go = "BS_KS_19";
		break;

		case "BS_KS_19":
			AddQuestRecord("BSCourtlyPassions", "4");
            dialog.text = "Have mercy! Well, I also heard that she doesn't accept clients, the pirates used her a lot for something there. They say the team of Wayne himself... Yeah, it's like the whole team. So look for another one, there are enough girls for every taste. But please don't touch the peddler. My niece.";
            link.l1 = "That's where it was worth starting. Okay, live. Does Wayne himself show up in town?";
			link.l1.go = "BS_KS_19_1";
		break;

		case "BS_KS_19_1":
            dialog.text = "I don't do business with pirates. It comes out sideways. So it's not for me.";
            link.l1 = "Goodbye.";
			link.l1.go = "BS_KS_19_1exit";
		break;

		case "BS_KS_19_1exit":
			DialogExit();
			npchar.dialog.filename = "Common_tavern.c";
			NPChar.Dialog.CurrentNode = "First time";
			sld = CharacterFromID("FortFrance_hostess");
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_20";
		break;
		//Запись в СЖ. Пора поискать Максин в борделе.

		//Идём в бордель, спрашиваем о Максин у хозяйки.

		case "BS_KS_20":
            dialog.text = "Welcome, "+GetSexPhrase("monsieur", "mademoiselle")+". By what fates?";
            link.l1 = "I want to spend time with one of your beauties. There are rumors around the archipelago about your Creole, Maxine, isn't her name? So I'm curious.";
			link.l1.go = "BS_KS_21";
		break;

		case "BS_KS_21":
            dialog.text = "She's not in the right shape to receive clients right now. But for ten thousand, we can make an exception.";
            NextDiag.TempNode = "BS_KS_20";
			if (sti(pchar.money >= 10000))
			{
				link.l1 = "Thank you, mademoiselle, I'm already burning with impatience.";	//Даём ей 10000
				link.l1.go = "BS_KS_21_exit";
			}
			link.l2 = "Damn it, where did my purse go?";
			link.l2.go = "exit";
		break;

		case "BS_KS_21_exit":
			DialogExit();
			npchar.Dialog.Filename = "Common_Brothel.c";
			NPChar.Dialog.CurrentNode = "First time";
			LocatorReloadEnterDisable("FortFrance_Brothel", "reload2_back", false);
            AddMoneyToCharacter(pchar, -10000);

			sld = GetCharacter(NPC_GenerateCharacter("BS_Maks", "BS_Maks", "woman", "woman", 1, PIRATE, -1, false));
			LAi_SetImmortal(sld, true);
			sld.name = GetConvertStrWithReplace("Variable_black_sails_functions_18", "Names.txt", "#space#", " ");
			sld.lastname 	= "";
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto3");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_22";
		break;

		//Наверху смуглая шлюха

		case "BS_KS_22":	//Максин
            dialog.text = "I've been waiting for you, "+ GetSexPhrase("cat", "fox") +". What are you doing here, John?";
            link.l1 = "I think you guessed that we didn't come here for pleasure.";
			link.l1.go = "BS_KS_22_1";
		break;

		case "BS_KS_22_1":	//Максин
            dialog.text = "Why then?";
            link.l1 = "We know all about your misadventures. I'll get to the point. I need what you were trying to sell to Wayne's EXEC. Tell me where those damn pirates are hiding and I'll gut them if it's any consolation.";
			link.l1.go = "BS_KS_23";
		break;

		case "BS_KS_23":
			AddQuestRecord("BSCourtlyPassions", "5");
            dialog.text = "Has someone decided to stand up for the poor whore? How unexpected! How can I resist? At midnight, Charles Wayne's whole gang will be in the dungeon, here in the city. Please, when it's over, take me to Port Royal?";
			link.l1 = "Agreed. At dawn, wait for me at Le Maren Bay.";
			link.l1.go = "BS_KS_24_1";
		break;

		case "BS_KS_24_1":
			LAI_SetActorType(npchar);
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_25";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;
		//На выходе из борделя диалог с Сильвером

		case "BS_KS_24":	//Сильвер
            dialog.text = "How are we doing?";
            link.l1 = "Tomorrow we will go to the dungeon at midnight.";
			link.l1.go = "BS_KS_25";
		break;

		case "BS_KS_25":
            dialog.text = "Cap, I'm not a fighter. I fight more with my tongue than with a saber.";
            link.l1 = "I noticed. Stay here and guard our girl Maxine, then escort her to Le Maren Bay.";
			link.l1.go = "BS_KS_26";
		break;

		case "BS_KS_26":
            dialog.text = "With great pleasure!";
			LAI_SetActorType(npchar);
            link.l1 = "See you later.";
			link.l1.go = "exit";
			LAi_LockFightMode(PChar, true);
			PChar.quest.BSCourtlyPassions_wait.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_wait.win_condition.l1.location = "FortFrance_town";
			PChar.quest.BSCourtlyPassions_wait.function = "BSCourtlyPassions_wait";
		break;

		//Запись В СЖ 'Следующей ночью отправляюсь в подземелье Форт де Франс. Бой предстоит жаркий, нужно подготовиться. Ах да. И не забыть потом Максин доставить в Порт Рояль'

		//Тусим до следующей полуночи. Идём в подземку. Там по полной пиратов, прям чтоб мясо. Вейн среди них, но бессмертный.

		case "BS_KS_27":	//Чарльз Вейн
            ref _location = &locations[reload_location_index];
			LAi_LocationFightDisable(_location, false);
		    dialog.text = "What the hell are you snooping around for?";
            link.l1 = "There is a conversation, Charles. About the page you appropriated for yourself.";
			link.l1.go = "BS_KS_28";
		break;

		case "BS_KS_28":
			AddQuestRecord("BSCourtlyPassions", "6");
			LAi_LockFightMode(PChar, false);
            dialog.text = "Why did you stand up like sheep? Kill them all!";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "", "", "", 10);
            link.l1 = "Where are you going? Stop!";
			link.l1.go = "BS_KS_28_exit";
			chrDisableReloadToLocation = false;

			PChar.quest.BSCourtlyPassions_fleeng.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_fleeng.win_condition.l1.location = "FortFrance_town";
			PChar.quest.BSCourtlyPassions_fleeng.function = "BSCourtlyPassions_fleeng";
		break;

		case "BS_KS_28_exit":
			DialogExit();
			LAi_group_SetHearRadius("EnemyFight", 100.0);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "", "", "", 10);
			AddDialogExitQuest("MainHeroFightModeOn");
			Log_info("'А ну стой! Всё равно догоню же!'");
		break;

		//Файт. Вейн удирает. Вывести лог "А ну стой! Всё равно догоню же!" - типо намёк, что файтится не обязательно со всеми. Там ещё вроде как должен музон играть боевой во время погони. 6.04.2023  

		case "BS_KS_29":
            dialog.text = "Well, it looks like Charles Wayne's luck has run out. But I won't give up just like that!";
            link.l1 = "Can we just talk?";
			link.l1.go = "BS_KS_30";

			PChar.quest.BSCourtlyPassions_final.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_final.win_condition.l1.location = "Shore39";
			PChar.quest.BSCourtlyPassions_final.function = "BSCourtlyPassions_final";
			DeleteAttribute(pchar, "BSCourtlyPassionsFail");
		break;

		case "BS_KS_30":
            dialog.text = "Ha ha ha. You're kidding me!";
            link.l1 = "The cipher page. I have someone who can crack this cipher. And you have the reputation of being the most desperate and lucky pirate in these waters. Shall we join forces? There's enough Urca gold for everyone.";
			link.l1.go = "BS_KS_31";
		break;

		case "BS_KS_31":
            dialog.text = "Who has it, 'us'? Aren't you with Flint?";
            link.l1 = "Yes, I'm with him. I know about his reputation, but a hundred and fifty million, Charles, think about it!";
			link.l1.go = "BS_KS_32";
		break;

		case "BS_KS_32":
			AddQuestRecord("BSCourtlyPassions", "7");		
            dialog.text = "Okay, I'm in. Why not? Everything's gone to hell lately, but I'm gonna hand the page to Flint personally. I really want to look into his fish eyes when I do.";
            link.l1 = "All right. I'll see you in the Bahamas. I still have unfinished business.";
			link.l1.go = "BS_KS_32exit";
		break;

		case "BS_KS_32exit":
            QuestAboardCabinDialogSurrender();
			SetFunctionExitFromLocationCondition("BS_Vein_Immortal", pchar.location, false);
			PChar.quest.BSCourtlyPassions_fail_to_board.over = "yes";
            DialogExit();
		break;

		//Топаем в Ле Марен. Уникумы тут используют фичу с телепортом по карте и ломают квест. Либо пусть ломают, либо  как то отключить возможность ТП на время 6.04.2023

		case "BS_KS_33":	//Сильвер
			Group_DeleteGroup("BSCourtlyPassions_SeaBattle");
            dialog.text = "Captain?";
            link.l1 = "It's done, let's go.";
			link.l1.go = "BS_KS_34";
		break;

		case "BS_KS_34":	//Сильвер
            dialog.text = "I never doubted you for a second!";
            link.l1 = "Yeah, come on, don't suck up.";
			link.l1.go = "BS_KS_35exit";
		break;


		case "BS_KS_35exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10);
			sld = CharacterFromID("BS_Maks");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_35";
			DialogExit();
			DoQuestFunctionDelay("MaksSpeech", 0);
		break;

		case "BS_KS_35":
            dialog.text = "Are they dead?";
            link.l1 = "Most of it.";
			link.l1.go = "BS_KS_36_1";
		break;

		case "BS_KS_36_1":
            dialog.text = "Now will you take me to Port Royal?";
            link.l1 = "I promised you. All aboard!";
			link.l1.go = "BS_KS_36_exit";
			PChar.quest.BSCourtlyPassions_finalRoyal.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_finalRoyal.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.BSCourtlyPassions_finalRoyal.function = "BSCourtlyPassions_finalRoyal";
		break;

		case "BS_KS_36_exit":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10);
		break;

		case "BS_KS_36":
            dialog.text = "Thank you, Captain! No one has ever taken such good care of me.";
            link.l1 = "There's a first time for everything.";
			link.l1.go = "BS_KS_37";
		break;

		case "BS_KS_37":
            dialog.text = "I hope we'll meet again?";
            link.l1 = "Who knows? Maybe. Take care of yourself.";
			link.l1.go = "BS_KS_37exit";
		break;

		case "BS_KS_37exit":
			DialogExit();
			pchar.quest.BSCourtlyPassions_DontStart.over = "yes";
			chrDisableReloadToLocation = false;
			pchar.ContraInterruptWaiting = true;
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", "none", "", "", "", -1);
			SetFunctionLocationCondition("BS_BahamasArrival", "Bahames", false);
			AddQuestRecord("BSCourtlyPassions", "8");
			CloseQuestHeader("BSCourtlyPassions");
			BSChaseBegun();
		break;

		//Отвозим шлюху в ПР, она уходит с корабля. Отправляемся на Багамы.

		//Запись в СЖ «Дело сделано, теперь можно отправиться на Багамы.»

	}
}
