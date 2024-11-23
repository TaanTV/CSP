
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

		//Заменить хозяйку борделя в ПР на Максин. Пускать на глобалке английских охотников (скоростые) 2-3 третьеклассника.

		//Прибыли в ПР. Идём в бордель к мадам. Опа, сюрприз. Это Макс (смуглянка)

		case "BS_NU_1":	//Максин
			dialog.text = "...";
			link.l1 = "Congratulations on your career growth! Unexpectedly, however.";
			link.l1.go = "BS_NU_2";
		break;

		case "BS_NU_2":
            dialog.text = "Greetings, "+pchar.name+". Decided to relax or entertain the team?";
            link.l1 = "I need your help. I know that girls from brothels see and hear a lot of things, and I'm ready to buy some information from you.";
			link.l1.go = "BS_NU_3";
		break;

		case "BS_NU_3":
            dialog.text = "Do you need a tip on a fat prey? You don't have to pay anything, I'll share it out of reciprocity, but I still owe you.";
            link.l1 = "We don't need a tip, we need any clue about the fattest prey imaginable! Do you understand what I mean?";
			link.l1.go = "BS_NU_4";
		break;

		case "BS_NU_4":
            dialog.text = "'Urca De Lima'! Flint doesn't waste time on trifles. I know something, but it's not free, I'm sorry.";
            link.l1 = "Name the price.";
			link.l1.go = "BS_NU_5";
		break;

		case "BS_NU_5":
            dialog.text = "Equal share as a companion. And some things are free from me. About the English raiders.";
            link.l1 = "Do you understand that shares need to be negotiated with all participants in the enterprise? Or do you want a share of my share?";
			link.l1.go = "BS_NU_6";
		break;

		case "BS_NU_6":
            dialog.text = "I understand, and that's why I'm going with you. And after meeting with the rest of the partners, I hope we will come to an agreement that is mutually beneficial for all parties.";
            link.l1 = "Persuaded, let's go now!";
			link.l1.go = "BS_NU_7";
		break;

		case "BS_NU_7":
            dialog.text = "Wait a minute. Something about the British. A squadron led by the warship Scarborough arrived in the Caribbean. It is rumored that this is the military intelligence of the Admiralty. They do not enter English ports, they do not report to the governors. Many privateers and pirates have already gone missing. And some were seen, but they pretended that they were not who they were supposed to be. Something strange is happening.";
            link.l1 = "I've already run into it several times with raiders under English flags. Nothing special. But these Brits are very persistent. Suicidally persistent.";
			link.l1.go = "BS_NU_8";
		break;

		case "BS_NU_8":
            dialog.text = "That's all I know about them. I'm ready to go.";
            link.l1 = "Let's go. Wait, though. Have you heard anything about Charles Wayne? Did he show up in the colonies?";
			link.l1.go = "BS_NU_9";
		break;

		case "BS_NU_9":
            dialog.text = "The wreckage of the Ranger was caught by fishermen near Fort Orange. I haven't heard anything about Charles himself.";
            link.l1 = "At least something. We'll need to check it out. On the way.";
			AddQuestRecord("BSUrka", "1");
			SetQuestHeader("BSUrka");
			CloseQuestHeader("BSChaseBegun");
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_NU_9_exit";
			PChar.quest.BSUrka_Negril.win_condition.l1 = "location";
			PChar.quest.BSUrka_Negril.win_condition.l1.location = "FortOrange_port";
			PChar.quest.BSUrka_Negril.function = "BSUrka_Negril";
		break;

		case "BS_NU_9_exit":
            dialog.text = "See you on the ship, captain.";
            link.l1 = "Yes, see you later.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_NU_9_exit";
		break;
		//Запись в СЖ: 'Таинственные английские военные, пропавший Вейн и новый компаньон в нашем дельце на сто пятьдесят миллионов. Нужно проверить информацию о разбившемся 'Рейнджере' и выдвигаться на Бермуды. Как бы не упустить денежный галеон'.

		//Пиздуем на Форт Оранж, в бухте запись в СЖ: 'Сломанные мачты, куски обшивки, рваный такелаж и прочий мусор. Нужно расспросить местных о случившемся'

		//В форт Оранж в таверне у бармена ничего. Выпиваем с алкашом – бинго

		case "BS_NU_10":	//Алкоголик
            dialog.text = "Well, your health! Wow, the rum is good. You should know what was going on here in the bay a couple of days ago! A pirate brig, dented with cannonballs, with sails like a ghost ship, gave battle to two Spanish frigates. And then, out of nowhere, three pirates on corvettes from behind the cape! Spaniards amicably laid down on the left tack and well, shove off side by side. One corvette was shot from bow to stern, there was a scream! I've already heard it in the fort! So, the shot immediately fell on board, and began to sink, and the other two, themselves onboard, almost at point-blank range smashed the frigate. And the brig, which was running away from the Spaniards, suddenly became bolder, dropped anchor on the port side and made a sharp turn around the chain, such that it already lost the mast. And let's shoot at the pirate from the side. In general, they sank the second corvette together with the Spaniard who survived. Ahem, my throat is dry.";
            link.l1 = "Here, have another drink. So what happened next? You're telling me an interesting story! I can see this fight in reality!";
			link.l1.go = "BS_NU_11";
		break;

		case "BS_NU_11":
            dialog.text = "Wow. It went well, thank you. And so. The pirate, on the surviving corvette, realized that things were bad, went downwind and ran off over the horizon with all sails! And on the brig, the anchor chain was cut off and the side of the frigate was piled on. So they went on board. And they defeated the Spaniards! The frigate raised the black flag, fired a volley at the battered brig and left, somewhere to the north. There was such a battle, even for a picture! The whole coast is strewn with debris.";
            link.l1 = "Thanks for the story. You should write books with such talent!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: 'Вейн жив, обзавёлся новым кораблём и выполнил свою часть по отвлечению сопровождения. Каков корсар! Надеюсь, увидимся на Бермудах'

		//Выходим в море, спауним фиолетовую энку (англичане). Файт. Три фрегата, кэп флагмана – Билли Бонс. Берём на абордаж. Файт в каюте, после 'убиения' - диалог.

		case "BS_NU_12":	//Билли Бонс
            dialog.text = "Stop! We need to talk!";
            link.l1 = "So, so, so. Flint's own XO and suddenly the English captain. What is this supposed to mean?";
			link.l1.go = "BS_NU_13";
		break;

		case "BS_NU_13":
            dialog.text = "I was the English captain. Admiralty Intelligence, Commander William Blackham, at your service.";
            link.l1 = "And why the hell is Admiralty intelligence chasing me? Are all these raiders that I sank yours too?";
			link.l1.go = "BS_NU_14";
		break;

		case "BS_NU_14":
            dialog.text = "Privateers, pirates who received a pardon and joined the service of His Majesty. There is a lot of zeal, unfortunately, little skill.";
            link.l1 = "Understood. Consumable material. So what does your office want from me?";
			link.l1.go = "BS_NU_15";
		break;

		case "BS_NU_15":
            dialog.text = "Flint. Rather, Captain James McGraw, a traitor, a thief, a murderer. A former officer of His Majesty's Navy, guilty of the murder of Lord Hamilton, his wife and a hundred other crimes. All my attempts to arrest or kill this man have failed, and I suggest that you, as his trusted companion, help the Crown arrest or destroy the traitor!";
            link.l1 = "And what interest do I have in doing this?";
			link.l1.go = "BS_NU_16";
		break;

		case "BS_NU_16":	//Тут выбор
            dialog.text = "A royal pardon for you and your subordinates, four hundred thousand pounds in silver and the opportunity to make a brilliant career in the Admiralty. As well as the gratitude of the Hamilton family, and believe me, it's worth a lot!";
            link.l1 = "Go to hell, Billy, with your pardon and his Majesty! I don't betray my friends! And I will get more benefits from this friendship! Are you ready to continue? Die!";
			link.l1.go = "Fight_Billi_Bons";
			//link.l2 = "I'll think about it. How can I contact you?";
			//link.l2.go = "BS_NU_17";
		break;

		case "Fight_Billi_Bons":
			AddQuestRecord("BSUrka", "4");
			pchar.BSBonsKilled = true;
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "BS_NU_17":
            dialog.text = "My man will be waiting in a tavern in Antigua. Password: ";
            link.l1 = "See you later, Sir William.";
			link.l1.go = "BS_NU_18";
		break;

		//Расходимся миром. В таверну Антигуа поселить непися за стол.

		//Запись в СЖ если убили Билла: 'Ситуация с английскими рейдерами прояснилась. Надо же. Разведка адмиралтейства! Нужно предупредить Флинта. Где-то всё ещё охотится 'Скарборо' и с этим, нужно что-то делать. В путь. На Бермуды'.

		//Запись в СЖ если приняли сторону Билла: 'Я принял(ла) косвенно предложение Бонса, то есть Блэкхэма. Но сначала 'Урка'! Такую добычу нельзя упускать. Нужно записать пароль для встречи со связным на Антигуа. 'Рыбалка успешной была. Улов – загляденье''

		//При любом раскладе – рейдеров, на глобалке выключаем.

		//Пиздуем на Бермуды. По улицам гуляют Бонни и Рекхэм. Просто гуляют с обычными для нпс диалогами.

		//В резиденции Флинт, Сильвер, Гатри, Вейн. С нами приходит Макс. Если согласились топить за Англию – про 'Скарборо' нет веток.

		case "BS_NU_18":	//Флинт
            dialog.text = "Finally everything is assembled. Who is your companion, "+pchar.name+"?";
            link.l1 = "Meet Maxine. Um... She's the owner of a brothel in Port Royal.";
			link.l1.go = "BS_NU_18_1";
		break;

		case "BS_NU_18_1":
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_19";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_19":	//Вейн
            dialog.text = "Wow, Max! Soared high! Remember that it hurts to fall, it really hurts!";
            link.l1 = "";
			link.l1.go = "BS_NU_19_1";
		break;

		case "BS_NU_19_1":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_20";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_20":	//Максин
            dialog.text = "I'll remember, thanks Charles. Gentlemen, I have the information you need about the money galleon, and I propose to sell it to you for an equal share of the loot.";
            link.l1 = "";
			link.l1.go = "BS_NU_20_1";
		break;
		case "BS_NU_20_1":
			DialogExit();
			sld = CharacterFromID("Gatri_temp");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_21";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_21":	//Гатри
            dialog.text = "Is your friend Charlie? The owner of a brothel? Someone sang to me stories about eternal love and fidelity to the grave, and he was on the hookers!";
            link.l1 = "";
			link.l1.go = "BS_NU_21_1";
		break;
		case "BS_NU_21_1":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_21_2";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_21_2":	//Флинт
            dialog.text = "Business first, Eleanor! Equal share, Miss Maxine, implies equal participation and risks. I hope your information is worth it. State it, and we will consider your participation in our partnership.";
            link.l1 = "";
			link.l1.go = "BS_NU_21_3";
		break;
		case "BS_NU_21_3":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_22";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_22":	//Максин
            dialog.text = "As far as I know, your hunt for the 'Urca' has failed. The fact is that she left by another route, without entering Havana, all this was a distraction. And I know where the ship has gone!";
            link.l1 = "Unbelievable! From where? Is it really from your workers?";
			link.l1.go = "BS_NU_23";
		break;
		case "BS_NU_23":
            dialog.text = "'Urca received strict orders not to enter any ports, but to use the services of trusted captains to replenish supplies and transport troops. One of these captains has specific tastes, and only my establishment can satisfy them. A couple of visits and he sang so much that he could be hanged, shot or quartered to choose from, or all at once.";
            link.l1 = "";
			link.l1.go = "BS_NU_23_1";
		break;
		case "BS_NU_23_1":
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_24";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_24":	//Вейн
            dialog.text = "What are the flavors?";
            link.l1 = "";
			link.l1.go = "BS_NU_24_1";
		break;
		case "BS_NU_24_1":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_25";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_25":	//Максин
            dialog.text = "Let it remain a mystery. So, the Urca De Lima is moving along the coast of Main and will anchor near the west coast of Curacao, where it will await the arrival of a convoy squadron from Havana and from there it will move to Europe, bypassing Barbados and Trinidad. Have I earned my share, gentlemen?";
            link.l1 = "";
			link.l1.go = "BS_NU_25_1";
		break;
		case "BS_NU_25_1":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_26";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_26":	//Флинт
            dialog.text = "Quite. But I'll ask you to keep me company, Miss Guthrie, here on the island. And we need to prepare ships and go to sea without delay! The west coast of Curacao is a dangerous place with sudden squalls, and the currents there are unpredictable, they can easily take us and our prize under the guns of Willemstad. We need to calculate the route more carefully.";
            link.l1 = "";
			link.l1.go = "BS_NU_26_exit";
			AddQuestRecord("BSUrka", "6");
		break;

		case "BS_NU_26_exit":
			DialogExit();
			NextDiag.CurrentNode = "BS_NU_28";

			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);

			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);

			sld = CharacterFromID("BS_Maks");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);

			sld = CharacterFromID("BS_Rakham");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);

			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);

			sld = CharacterFromID("gatri_temp");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", 10);
		break;
		//Запись в СЖ: 'Макс дала важную информацию. Испанцы предвидели охоту за галеоном и запутали следы. Но болтливые и похотливые людишки рушат любые планы и вскрывают любые тайны. Заметка себе: 'Не болтать в борделях!''

		//Все сваливают из резиденции. Остаётся ГГ и Флинт.

		case "BS_NU_28":	//Флинт
			pchar.quest.BSUrka_Fail1.win_condition.c1 = "NPC_Death";
			pchar.quest.BSUrka_Fail1.win_condition.c1.character ="Flint";
			PChar.quest.BSUrka_Fail1.function = "BSUrka_Fail";

			pchar.quest.BSUrka_Fail2.win_condition.c1 = "NPC_Death";
			pchar.quest.BSUrka_Fail2.win_condition.c1.character ="BS_Vein";
			PChar.quest.BSUrka_Fail2.function = "BSUrka_Fail";

			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//Флинт присоединяется к эскадре
			Flag_Change(PIRATE);
			BSRepairShip(npchar);
			LAi_SetImmortal(npchar, false);

			SetShipRemovable(npchar, false);
			SetCharacterRemovable(npchar, false);
            dialog.text = "";
            link.l1 = "Last push?";
			link.l1.go = "BS_NU_29_Ya_Ne_Krisa";
		break;

		//Если мы остались верны Флинту, то следующий диалог:

		case "BS_NU_29_Ya_Ne_Krisa":
            dialog.text = "I suspect that it is not the last one.";

			link.l1 = "We have already been through a lot together. You can count on me, no matter what happens.";
			link.l1.go = "BS_NU_32_Ya_Ne_Krisa";
			if(CheckAttribute(pchar, "BSBonsKilled"))
			{
				link.l1 = "I met your XO on Jamaica. Commander William Blackham. Bones. Billy Bones.";
				link.l1.go = "BS_NU_30_Ya_Ne_Krisa";
			}
		break;

		case "BS_NU_30_Ya_Ne_Krisa":
            dialog.text = "Commander? Hm... I suspected he was a spy, but he works for Jackman. But the Admiralty...";
            link.l1 = "They need your head, for the murder of Lord Hamilton and so on, so on, so on. He promised mountains of gold.";
			link.l1.go = "BS_NU_31_Ya_Ne_Krisa";
		break;

		case "BS_NU_31_Ya_Ne_Krisa":
            dialog.text = "But you didn't heed to him? Why?";
            link.l1 = "One hundred and fifty million brilliant reasons, damn it! And I don't sell friends.";
			link.l1.go = "BS_NU_32_Ya_Ne_Krisa";
		break;

		case "BS_NU_32_Ya_Ne_Krisa":
            dialog.text = "You honor me by offering your friendship. I am happy to accept it. Here's my hand.";
            link.l1 = "And here is mine. So what? It's time to check on the elusive 'Urca'!";
			link.l1.go = "BS_NU_32_exit";
		break;

		case "BS_NU_32_exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "reload1_3", "reload1_2", "", "", "", -1);
			chrDisableReloadToLocation = false;
			DialogExit();

			PChar.quest.BSUrka_Pirates_town_Vein.win_condition.l1 = "location";
			PChar.quest.BSUrka_Pirates_town_Vein.win_condition.l1.location = "Pirates_town";
			PChar.quest.BSUrka_Pirates_town_Vein.function = "BSUrka_Pirates_town_Vein";
		break;

		//Если мы предаём Флинта, то следующий диалог:

		case "BS_NU_29_Ya_Shpion":
            dialog.text = "I suspect it's not the last one.";
            link.l1 = "...";
			link.l1.go = "exit";
		break;

		//Ставим Моржа и Вейна на ТФ 'Рейнджер' в эскадру. На выходе из резиденции говорим с Вейном.

		//Если мы остались верны Флинту, то следующий диалог:

		case "BS_NU_33_Ya_Ne_Krisa":
			FantomMakeCoolestSailor(npchar, SHIP_ENDYMION, "Ranger", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//вейн присоединяется к эскадре
			BSRepairShip(npchar);
			SetShipRemovable(npchar, false);
			SetCharacterRemovable(npchar, false);
			Fantom_SetBalls(npchar, "war");
			SetCharacterGoods(npchar,GOOD_FOOD,1000);
			chrDisableReloadToLocation = false;
			LAi_SetImmortal(npchar, false);
            dialog.text = "What were you talking about with Flint?";
            link.l1 = "Planned a hike. I heard your fight with the Spaniards! And I see you have a new ship. It's got to be done! How did you even survive?";
			link.l1.go = "BS_NU_34_Ya_Ne_Krisa";
		break;

		case "BS_NU_34_Ya_Ne_Krisa":
            dialog.text = "I'm damn lucky, I don't know any other explanation myself.";
            link.l1 = "I wish I had a drop of your luck. Well, it's time to move out.";
			link.l1.go = "BS_NU_34_exit";

			//Sea_CabinStartNow();
			//Set_My_Cabin();
			//Sea_DeckBoatStartNow(pchar);
			//BSUrka_Curacao_SeaBattle(1);
			//DoReloadCharacterToLocation(Get_My_Cabin(), "goto", "goto4");

			//setCharacterShipLocation(pchar, "Shore23");
			//pchar.location.from_sea = "Shore23";
			//setWDMPointXZ("Shore23");  // коорд на карте
		break;

		//Если мы предаём Флинта, то следующий диалог:

		case "BS_NU_33_Ya_Shpion":
            dialog.text = "What were you talking about with Flint?";
            link.l1 = "There is something that needs to be discussed. But about this after the 'Urca'";
			link.l1.go = "BS_NU_34_Ya_Shpion";
		break;

		case "BS_NU_33_Ya_Shpion":
            dialog.text = "Whatever you say. On the way.";
            link.l1 = "";
			link.l1.go = "exit";
		break;

		case "BS_NU_34_exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "reload1_2", "", "", "", -1);
			BSUrka_Curacao_SeaBattle();
            pchar.quest.BSUrka_Curacao_SeaBattle.win_condition.l1 = "EnterToSea";
			pchar.quest.BSUrka_Curacao_SeaBattle.function    = "BSUrka_Curacao_SeaBattle";
			DialogExit();
			SetTimerFunction("BSUrka_Curacao_SeaBattle", 0, 0, 2);
		break;

		//Выходим в море, чешем до Кюрасао. С западной стороны выходим на локалку. Сюрпрайз. Урки нету! Зато есть 6-8 испанских фрегатов и линейников. Адовое мочилово. После боя, ТП на палубу Флинта.

		case "BS_NU_35":
            dialog.text = "";
            link.l1 = "Almost everything came together, but where is the 'Urca'?";
			link.l1.go = "BS_NU_36";
		break;

		case "BS_NU_36":
			chrDisableReloadToLocation = false;

			DeleteAttribute(pchar, "LockShoreReload");
            dialog.text = "Calm down, we fished some Spaniards out of the water, they are being interrogated now. We will stand in the raid at Cape Calvinist. We'll talk on the shore.";
            link.l1 = "";
			link.l1.go = "exit";
			pchar.LockMapReload = "First we need to interrogate the Spanish prisoners at Cape Calvinist.";
			pchar.quest.BSUrka_Curacao_Shore.win_condition.l1          = "location";
			pchar.quest.BSUrka_Curacao_Shore.win_condition.l1.location = "Shore23";
			pchar.quest.BSUrka_Curacao_Shore.function             = "BSUrka_Curacao_Shore";
		break;
		/*
		case "BS_NU_36_exit":
			DialogExit();
			DoReloadCharacterToLocation("Shore23", "reload", "sea");
		break;
		*/
		//Доплываем до мыса Кальвинистов, выходим на берег. На берегу испанский офицер, Флинт, Вейн, Бонни.

		case "BS_NU_37":	//Флинт
            DeleteAttribute(pchar, "LockMapReload");
			dialog.text = "We are in Curacao, you will be released without harm if we receive the information we are interested in. Otherwise, you know my reputation! And don't delay the decision.";
            link.l1 = "";
			link.l1.go = "BS_NU_381";
		break;

		case "BS_NU_381":
			DialogExit();
			sld = CharacterFromID("BSUrka_Prisoner");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_38";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_38":	//Испанский офицер
			sld = CharacterFromId("Flint");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToCharacter(sld, npchar);
            dialog.text = "Damn cabrons! Hell awaits you all! But I accept your terms! The ship you are interested in was swept away by a squall in the direction of Main. It is battered by the storm and will be repaired in one of the bays. That's all I can tell you.";
            link.l1 = "";
			link.l1.go = "BS_NU_391";
		break;

		case "BS_NU_391":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_39";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_39":	//Флинт
            dialog.text = "Thank you, you can go.";
            link.l1 = "";
			link.l1.go = "BS_NU_401";
		break;

		case "BS_NU_401":
			DialogExit();
			sld = CharacterFromID("BS_Bony");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_40";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_40":	//Бонни убивает испанца
            dialog.text = "The hell he can go!";
            link.l1 = "";
			link.l1.go = "exit";
			DoQuestFunctionDelay("BSUrka_BonyHits", 0.3);
		break;

		case "BS_NU_41":	//Вейн
            dialog.text = "What the hell is Ann? What's gotten into you?";
            link.l1 = "";
			link.l1.go = "BS_NU_421";
		break;

		case "BS_NU_421":
			DialogExit();
			sld = CharacterFromID("BS_Bony");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_42";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_42":	//Бонни
            dialog.text = "The search dragged on and there were already too many surprises to release this prisoner, who will bring another squadron to us!";
            link.l1 = "";
			link.l1.go = "BS_NU_431";
		break;

		case "BS_NU_431":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_43";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "BS_NU_43":	//Флинт
            dialog.text = "Mr. Wayne, keep an eye on your subordinates! This is the last trick I'll put up with.";
            link.l1 = "";
			link.l1.go = "BS_NU_44";
		break;

		case "BS_NU_44":	//Флинт
			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
            dialog.text = "Ann, get in the boat! Silently! We'll talk later.";
            link.l1 = "It's time to search a lot of bays. Get to work!";
			link.l1.go = "BS_NU_44_exit";
		break;

		case "BS_NU_44_exit":
			AddQuestRecord("BSUrka", "7");
			DialogExit();
			sld = CharacterFromID("Flint");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			BSUrka_PlaceUrka();
			pchar.quest.BSUrka_Found.win_condition.l1          = "location";
			pchar.quest.BSUrka_Found.win_condition.l1.location = "Cumana";
			pchar.quest.BSUrka_Found.function             = "BSUrka_Found";

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_4_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: 'Охота затянулась, и нервы начинают сдавать. Нужно разобраться с этим поскорее, пока мы не передрались'

		//Выходим в море. Ищем по бухтам Мурку. Мурка в Лос Текос. В бухте ставим раздолбаный имперский галеон под названием 'Урка де Лима'. Взаимодействовать с ней нельзя. Она просто декорация. На рейде – испанский мановар. Файт.

		//После потопления самовара, запись в СЖ: 'Наконец то! Вот она 'Урка'. Её сильно потрепало штормом и команды не видно на борту. Высаживаемся на берег!'

		//На берегу – адский файт. Испанцев лучше пускать волнами, чтоб не лагало всё к херам штук по 30 и так пять раз. Флинта, Вейна, Сильвера – лучше сделать либо бессмертными, либо очень толстыми на момент файта.

		//После победы запись в СЖ: 'Дело сделано, столько крови я никогда не проливал(ла) за один раз. Нет сил, даже говорить. Грузим сундуки на корабли и отчаливаем, пока на шум не налетела береговая охрана'.

		//Ставим табличку 'Прошло 3 часа, сундуки погружены на корабли'

		//Подходит Флинт

		case "BS_NU_45":	//Флинт
            dialog.text = "The job is done, we will do the division in Bermudes. It's time to leave.";
            link.l1 = "";
			link.l1.go = "BS_NU_45_exit";
		break;

		case "BS_NU_45_exit":
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);
			DialogExit();

			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Rakham");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);

			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_46_Ya_Ne_Krisa";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		//Флинт уходит на корабль. Остаётся Вейн.

		//Если мы остались верны Флинту, то следующий диалог:

		case "BS_NU_46_Ya_Ne_Krisa":	//Вейн
            chrDisableReloadToLocation = false;
			RemoveCharacterCompanion(PChar, npchar);
			AddQuestRecord("BSUrka", "9");
			dialog.text = "I have almost stopped believing that this galleon is real. And you fight well. Find me after everything, maybe we'll do a few things together!";
            link.l1 = "It's going to be a long time before I go to the next case! You know, but thanks for the offer! You're a damn good corsair too!";
			link.l1.go = "BS_NU_47_Ya_Ne_Krisa";
		break;

		case "BS_NU_47_Ya_Ne_Krisa":
            dialog.text = "I am a pirate. You can't lure me with a patent. I don't like uniforms.";
            link.l1 = "It's time to go to Bermudes. Let's go.";
			link.l1.go = "BS_NU_47_Ya_Ne_Krisaexit";
		break;

		case "BS_NU_47_Ya_Ne_Krisaexit":
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);
			DialogExit();

			pchar.BSBonsSpawned = true;
			BSBons_SeaBattle(true);
			BSChaseBegun_unlock_townhall();

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_5_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}

			PChar.quest.BSUrka_Finish.win_condition.l1 = "location";
			PChar.quest.BSUrka_Finish.win_condition.l1.location = "Pirates_townhall";
			PChar.quest.BSUrka_Finish.function = "BSUrka_Finish";

			PChar.quest.BSChaseBegun_Fail.over = "yes";
			PChar.quest.BSUrka_Fail1.over = "yes";
			PChar.quest.BSUrka_Fail2.over = "yes";
			PChar.quest.BSUrka_Curacao_EndSeaBattle.over = "yes";
			PChar.quest.BSUrka_SeaBattleEnded.over = "yes";
		break;

		//Если мы предаём Флинта, то следующий диалог:

		case "BS_NU_46_Ya_Shpion":	//Вейн
            dialog.text = "You wanted to talk about something? Back in Bermudes.";
            link.l1 = "Yes, there is something. Near Jamaica, I met Billy Bones, who is not Bones at all, but an officer of the British naval intelligence. Don't interrupt! They need Flint's head in exchange for the loyalty of the colonial authorities and a reward. Four hundred thousand pounds in silver. In local currency, that's two and a half million each, if you're in business. What do you say?";
			link.l1.go = "BS_NU_47_Ya_Shpion";
		break;

		case "BS_NU_47_Ya_Shpion":
            dialog.text = "To get a piece of all these Spanish millions and a reward from the British crown? In exchange for the head of that arrogant son of a bitch? How do you think you can pull this off?";
            link.l1 = "If we attack him at sea, right now, our teams will chop us into minced meat. Flint is a demigod to them now! After Bermudes and the division, when everyone gets drunk, then we'll tie him up. You can still make some money for a living.";
			link.l1.go = "BS_NU_48_Ya_Shpion";
		break;

		case "BS_NU_48_Ya_Shpion":
            dialog.text = "I'm in, even though this case reeks of shit, but to look into his eyes when he realizes that he's been fucked is worth it!";
            link.l1 = "Means at night, after the division. That's it, they're already looking at us. On the way.";
			link.l1.go = "exit";
		break;

		//Если мы остались верны Флинту, то следующая запись в СЖ: 'Осталось самое интересное – делёжка добычи! Пора отправляться на Бермуды'

		//Если мы предаём Флинта, то следующая запись в СЖ: 'Вейн в деле, делим добычу и ловим Флинта. Надо постараться оставить его в живых. Пора на Бермуды'

		//Если решили не продавать Флинтушку – на глобалке догоняет фиолетовая энка. 'Скарборо' линейник первого ранг. С ним пара фрегатов. Никаких диалогов, просто замес в море. По окончанию – запись в СЖ 'Скарборо' на дне. Остался только Джекмен'

		//Если решили продать, англичан нету, спокойно идём до бермуд.

		//В обоих вариантах – при выходе на локалку Бермуд – атакует эскадра Джекмена. Джекмен на 'Нептуне'. Бах-бах. Абордируем 'Нептуна' файт с Джекменом. Диалог

		case "BS_NU_49":	//Джекмен
            dialog.text = "Damn you! It all started with you and it should end with you!";
            link.l1 = "Why are you so mad? Because of Guthrie? Ha-ha. This woman is the true terror of pirates, and not you, a fat bumpkin!";
			link.l1.go = "exit";
		break;

		case "BS_NU_49":
            dialog.text = "Yes, I'll chop you in half and eat your heart!";
            link.l1 = "";
			link.l1.go = "exit";
		break;

		//Файт. На тушку Джекмена положить какие - нибудь уники. В сундук – бабла 300к и камушков штук по 50 каждого. Запись в СЖ: 'На подходе к Бермудам, мы были атакованы эскадрой Джекмена. Несчастный сукин сын не смог смириться с ролью второго после мисс Гатри. Передавай привет Сатане, мистер Джекмен!'

		//Селим Гатри и Макс в резиденцию, в магаз – рандомного челика.

		//Высаживаемся, идём в резиденцию. ГГ, Флинт, Вейн, Гатри, Макс

		case "BS_NU_50":	//Флинт
            dialog.text = "The job is done, the gold is being unloaded from the ships to Miss Guthrie's warehouse, we will start counting and dividing immediately after unloading. In the meantime, I propose to drink to the successful completion of the case! You're the best team I've ever had to deal with. For you! To the bottom!";
            link.l1 = "To the bottom!";
			link.l1.go = "BS_NU_50exit";
		break;

		case "BS_NU_50exit":	//Флинт
			DialogExit();
			BSUrka_Poison();
		break;

		//Типа пьём и валимся с ног все, кроме Флинта, Флинт уходит из резиденции. Нас отравили.

	}
}
