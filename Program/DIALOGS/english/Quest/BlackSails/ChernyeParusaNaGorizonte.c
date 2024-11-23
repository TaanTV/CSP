
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

		case "BS_CPNG_1":	//Бармен
			dialog.text = "Hey, isn't our hope and support looking for you, bright-faced Miss Guthrie?";
			link.l1 = "Oh my God! What is it this time?";
			link.l1.go = "BS_CPNG_2";
		break;

		case "BS_CPNG_2":
            dialog.text = "I have no idea. But her messenger asked very convincingly to tell captain "+pchar.name+" that someone is waiting for "+ GetSexPhrase("him", "her") +" at the Bermudes store. And if I were this captain, I wouldn't hesitate.";
            link.l1 = "Okay, I got it.";
			link.l1.go = "exit";
		break;

		//На Бермудах, перед магазином сценка. Гатри орёт на кучку пиратских кэпов. (штук 5-6 неписей Кэпов)

		case "BS_CPNG_3":	//Гатри
            dialog.text = "Mr. Fix! Tobacco is valuable when it is not soaked in urine! If you or your XO cannot ensure proper discipline on the ship, then I can easily find a replacement for you!";
            link.l1 = "";
			link.l1.go = "BS_CPNG_4_1";
		break;

		case "BS_CPNG_4_1":
            npchar.name = "Fix";
			npchar.lastname = "";
			NextDiag.CurrentNode = "BS_CPNG_4";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_4":	//Фикс
            dialog.text = "Miss Guthrie! With all due respect, this is my ship and I...";
            link.l1 = "";
			link.l1.go = "BS_CPNG_5_1";
		break;

		case "BS_CPNG_5_1":
            npchar.name = "Eleanor";
			npchar.lastname = "Guthrie";
			NextDiag.CurrentNode = "BS_CPNG_5";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_5":	//Гатри
            dialog.text = "Prevon! You are now captain of the Fox. Take command!";
            link.l1 = "";
			link.l1.go = "BS_CPNG_6_1";
		break;

		case "BS_CPNG_6_1":
            npchar.name = "Fix";
			npchar.lastname = "";
			NextDiag.CurrentNode = "BS_CPNG_6";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_6":	//Фикс
            dialog.text = "Yes I am... Yes, how are you? I'm going to Jackman!";	//уходит в резиденцию
            link.l1 = "";
			link.l1.go = "BS_CPNG_7_1";
		break;

		case "BS_CPNG_7_1":
            npchar.name = "Eleanor";
			npchar.lastname = "Guthrie";
			NextDiag.CurrentNode = "BS_CPNG_7";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_7":	//Гатри
            dialog.text = "Ah, here you are. Just in time. So, gentlemen, a short break. We'll continue later.";	//остальные уходят
            link.l1 = "";
			link.l1.go = "BS_CPNG_8";
			for (i = 1; i < 4; i++)
			{
				sld = CharacterFromID("Gatri_temp"+i);
				sld.LifeDay = 0;
			}
		break;

		case "BS_CPNG_8":	//Гатри
			chrDisableReloadToLocation = false;
            dialog.text = "There is a case. Mutually beneficial, let's go to the tavern.";	//Переход в Таверну. Диалог в комнате наверху.
            link.l1 = "Let's go.";
			link.l1.go = "BS_CPNG_9_1";
		break;

		case "BS_CPNG_9_1":	//Гатри
			PChar.quest.Gatri_upstairs.win_condition.l1 = "location";
			PChar.quest.Gatri_upstairs.win_condition.l1.location = "Pirates_tavern_upstairs";
			PChar.quest.Gatri_upstairs.function = "Gatri_upstairs";
			NextDiag.CurrentNode = "BS_CPNG_9";
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
            DoReloadCharacterToLocation("Pirates_tavern_upstairs", "goto", "goto1");
		break;

		case "BS_CPNG_9":	//Гатри
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
            dialog.text = "Listen carefully!";
            link.l1 = "Wait a minute. Why did we suddenly become friends?";
			link.l1.go = "BS_CPNG_10";
		break;

		case "BS_CPNG_10":
            dialog.text = "This is a New World, where people quickly become friends or enemies. Rich or dead. Can you keep up with the thought?";
			link.l1 = "I'm all ears.";
			link.l1.go = "BS_CPNG_11"
		break;

		case "BS_CPNG_11":
            dialog.text = "Okay. I have a friend. More than a friend. Almost like my father... Captain Flint. Did you hear about him?";
            link.l1 = "Flint. Wow. Yes, his name scares children even in Asia.";
			link.l1.go = "BS_CPNG_12";
		break;

		case "BS_CPNG_12":
            dialog.text = "You have nothing to fear. And his reputation is well deserved – he is a very cruel and rational person, but fair and appreciative of friendship\n"+
							"So that's it. He got involved in an adventure that could enrich all those involved or, conversely, ruin them. And I want events to go according to the first scenario and I intend to help in every possible way.";
            link.l1 = "And what is my role in this scenario?";
			link.l1.go = "BS_CPNG_13";
		break;

		case "BS_CPNG_13":
            dialog.text = "Find him in the sea. Remember, it is very important to be under the black flag at the moment of the meeting! When you see him, tell him you also read Marcus Aurelius. This is the password. He will tell you the rest himself.";
            link.l1 = "And where to find Flint?";
			link.l1.go = "BS_CPNG_14";
		break;

		case "BS_CPNG_14":
            dialog.text = "It's hard to say. He only goes into pirate bays for a short time. Look for him in the sea.";
            link.l1 = "See you later.";
			AddQuestRecord("BSOnTheHorizon", "2");
			BSOnTheHorizon_Flint();
			link.l1.go = "exit";
		break;

		//После диалога запускаем по глобалке модельку БОЛЬШУЮ пиратскую( или фиолетовый квестовик), который курсирует между ПИРАТСКИМИ портами.
		//Под пиратским флагом – всё ОК. под любым другим – файт и провал квеста.
		//Флинт на Тяжёлом военном пинасе 'Морж'. Высылаем шлюпку. Говорим.

		case "BS_CPNG_15":	//Флинт
            dialog.text = "I know this ship, but this is the first time I've seen captain. Introduce yourself.";
            link.l1 = "I am " + GetFullName(pchar)+"Miss Guthrie asked me to find you, Captain Flint.";
			link.l1.go = "BS_CPNG_16";
		break;

		case "BS_CPNG_16":
            dialog.text = "I know Ms. Guthrie and her father, but how are you connected to them and to me?";

			//это такая засада.. чтобы читали текст :)
			MakeRandomLinkOrderThree(link,
			"I also read Marcus Aurelius and I am great fan of his work and ready to provide all possible support and assistance to a like-minded person.",
			"BS_CPNG_17_Horosho",

			"I also read Mark Antony and I am big fan of his work and ready to provide all possible support and assistance to a like-minded person.",
			"BS_CPNG_17_Ploho",

			"I heard that the legendary Flint needs help with some kind of adventure. And here I am!",
			"BS_CPNG_17_Ploho"
			);
		break;

		case "BS_CPNG_17_Ploho":
            DeleteAttribute (npchar, "AlwaysFriend");
			npchar.AlwaysEnemy = true;
			dialog.text = "I don't know who you are and I suggest you leave my ship.";
            link.l1 = "Uh... Goodbye.";
			NextDiag.TempNode = "BS_CPNG_17_Ploho_end";
			link.l1.go = "exit";
		break;

		case "BS_CPNG_17_Ploho_end":
            dialog.text = "Leave my ship immediately!";
            link.l1 = "There's no need for me to be rude, I'm already leaving.";
			NextDiag.TempNode = "BS_CPNG_17_Ploho_end";
			link.l1.go = "exit";
		break;

		case "BS_CPNG_17_Horosho":
			PChar.quest.MeetFlintCrew.win_condition.l1 = "location";
			PChar.quest.MeetFlintCrew.win_condition.l1.location = "Pirates_town";
			PChar.quest.MeetFlintCrew.function = "MeetFlintCrew";
            dialog.text = "It's better to talk about this without unnecessary ears. I'll settle some business and go to Bermudes, we'll talk at the tavern there.";
			npchar.StopSailing = true;
			AddQuestRecord("BSOnTheHorizon", "3");
            link.l1 = "Okay, see you later.";
			NextDiag.TempNode = "BS_CPNG_17_Horosho_end";
			link.l1.go = "exit";
		break;

		case "BS_CPNG_17_Horosho_end":
            dialog.text = "Get back to your ship, let's not waste time.";
            link.l1 = "You're right, I'll go.";
			NextDiag.TempNode = "BS_CPNG_17_Horosho_end";
			link.l1.go = "exit";
		break;

		//Бермуды. На берегу Флинт, Сильвер, Бонс.

		case "BS_CPNG_18":	//Флинт
			//chrDisableReloadToLocation = false;
            dialog.text = "Meet me. First Mate Billy Bones, Captain John Silver.";
			BS_ReplaceTraderWithGatri();
            link.l1 = "Glad to see you. I am " + GetFullName(pchar)+". Are we going to the tavern?";
			link.l1.go = "BS_CPNG_19";
		break;

		case "BS_CPNG_19":

            dialog.text = "Later. First, to the store, to our mutual friend. I want to set the record straight";
            link.l1 = "";
			link.l1.go = "BS_CPNG_19_exit";	//Переход в магаз. Гатри, Флинт, ГГ.
		break;

		case "BS_CPNG_19_exit":
			NextDiag.CurrentNode = "BS_CPNG_9";
			sld = CharacterFromID("gatri_grunt3");
			sld.LifeDay = 0;
			sld = CharacterFromID("Pirates_trader");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.dialog.currentnode = "BS_CPNG_20";
			sld.talker = 10;
			sld.LifeDay = 0;
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "Pirates_store", "goto", "goto3");
            DoReloadCharacterToLocation("Pirates_store", "reload", "reload1_back");
		break;

		case "BS_CPNG_20":	//Гатри
            dialog.text = "James, I sent "+ GetSexPhrase("him", "her") +" to you. He is not just a breadwinner, "+ GetSexPhrase("this captain looks", "this girl looks") +" at you like... You understand me.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_21_1";
		break;

		case "BS_CPNG_21_1":
            npchar.name = "James";
			npchar.lastname = "Flint";
			NextDiag.CurrentNode = "BS_CPNG_21";
			DialogExit();
			DoQuestFunctionDelay("GatriStoreSpeech", 0);
		break;

		case "BS_CPNG_21":	//Флинт
            dialog.text = "I see an adventurer, an experienced captain with a beautiful ship and a well-trained team. I'm very rarely wrong, Eleanor, you know. Do you vouch for "+ GetSexPhrase("him", "her") +"?";
            link.l1 = "";
			link.l1.go = "BS_CPNG_22_1";
		break;

		case "BS_CPNG_22_1":
            npchar.name = "Eleanor";
			npchar.lastname = "Guthrie";
			NextDiag.CurrentNode = "BS_CPNG_22";
			DialogExit();
			DoQuestFunctionDelay("GatriStoreSpeech", 0);
		break;

		case "BS_CPNG_22":	//Гатри
            dialog.text = "We had disagreements, but everything was resolved. Yes, I vouch for this captain.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_23_1";
		break;

		case "BS_CPNG_23_1":
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_23";
			//NPChar.Dialog.Filename = "Common_store.c";
			//NPChar.Dialog.CurrentNode = "Second time";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_CPNG_23":	//Флинт
            dialog.text = "Well, let's continue in the tavern.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_23_exit";	//Переход в таверну. Таверна комната.
		break;

		case "BS_CPNG_23_exit":
			PChar.quest.Flint_upstairs.win_condition.l1 = "location";
			PChar.quest.Flint_upstairs.win_condition.l1.location = "Pirates_tavern_upstairs";
			PChar.quest.Flint_upstairs.function = "Flint_upstairs";
			NextDiag.CurrentNode = "BS_CPNG_24";
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
            DoReloadCharacterToLocation("Pirates_tavern_upstairs", "goto", "goto1");
		break;

		case "BS_CPNG_24":	//Флинт
            dialog.text = "So, Captain " + GetFullName(pchar)+". Have you heard of the Urca De Lima? A Spanish money galleon carrying not gold ore, but minted gold doubloons?";
            link.l1 = "Mmm... I admit, I heard rumors about this floating fortress. Not even rumors, but speculation and stories about the fact that this galleon almost carries the treasury of the Escorial. Yes, but if many people have seen the Golden Fleet live, then the Urca is nothing!";
			link.l1.go = "BS_CPNG_25";
		break;

		case "BS_CPNG_25":
			BS_RestoreGatriTrader("q");
            dialog.text = "'Urca De Lima' is a very tough nut to crack, yes. And I have information on where and when this galleon will replenish water and food for the trip to Spain. And this is the perfect chance to crack that nut.";
            link.l1 = "What is the price of the question?";
			link.l1.go = "BS_CPNG_26";
		break;

		case "BS_CPNG_26":
            dialog.text = "One hundred and fifty million pesos!";
            link.l1 = "Mother of God!";
			link.l1.go = "BS_CPNG_27";
		break;

		case "BS_CPNG_27":
            dialog.text = "Are you in business? Yes or no? Otherwise, you understand how this meeting will end.";
            link.l1 = "Of course I'm in! Where, how and when?!";
			link.l1.go = "BS_CPNG_28";
		break;

		case "BS_CPNG_28":
			chrDisableReloadToLocation = false;
            dialog.text = "And we'll ask Mr. Silver about this, if he hasn't drunk himself to hell yet.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_28_exit";	//Спускаемся вниз. За столом Бонс и Сильвер.
		break;

		case "BS_CPNG_28_exit":
			PChar.quest.Silver_Downstairs.win_condition.l1 = "location";
			PChar.quest.Silver_Downstairs.win_condition.l1.location = "Pirates_tavern";
			PChar.quest.Silver_Downstairs.function = "Silver_Downstairs";
			NextDiag.CurrentNode = "BS_CPNG_24";
			DialogExit();
            DoReloadCharacterToLocation("Pirates_tavern", "sit", "sit_front4");
			FreeSitLocator("Pirates_tavern", "sit_front4");  // очистим стул
			FreeSitLocator("Pirates_tavern", "sit_front1");  // очистим стул
			FreeSitLocator("Pirates_tavern", "sit_base4");  // очистим стул
			FreeSitLocator("Pirates_tavern", "sit_base1");  // очистим стул

			ChangeCharacterAddressGroup(npchar, "Pirates_tavern", "sit", "sit_base4");
			LAi_SetSitType(npchar);
			LAi_SetSitType(pchar);
			sld = CharacterFromID("BS_Billy");
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			sld = CharacterFromID("BS_Silver");
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.dialog.currentnode = "BS_CPNG_29";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit_base1");
			LAi_SetSitType(sld);
			sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp", "BS_Gatry", "woman", "woman", 1, PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay1");
			sld.name = "Eleanor";
			sld.lastname = "Guthrie";
		break;

		case "BS_CPNG_29":	//Сильвер
            dialog.text = "...";
            link.l1 = "Mr. Silver? I'm Captain Flint's new companion, it's time to share the information!";
			link.l1.go = "BS_CPNG_30";
		break;

		case "BS_CPNG_30":
            dialog.text = "Greetings Captain! How do you like the local, colonial brothels?";
            link.l1 = "...";
			link.l1.go = "BS_CPNG_30_flint_1";
		break;

		case "BS_CPNG_30_flint_1":
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_30_flint";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_CPNG_30_flint":
            dialog.text = "No kidding!";
            link.l1 = "...";
			link.l1.go = "BS_CPNG_31_1";
		break;

		case "BS_CPNG_31_1":
			sld = CharacterFromID("BS_Silver");
			sld.dialog.currentnode = "BS_CPNG_31";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;

		case "BS_CPNG_31":
            dialog.text = "I am more serious than ever! I only have a part of the code from the encrypted route! Captain Wayne has the rest.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_32_1";
		break;

		case "BS_CPNG_32_1":
			sld = CharacterFromID("Gatri_temp");
			sld.dialog.currentnode = "BS_CPNG_32_gatri";
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.talker = 10;
			DialogExit();
			//DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_32_gatri":
            dialog.text = "Charles Wayne! Damn it! How!!! Argh..!!";
            link.l1 = "";
			link.l1.go = "BS_CPNG_32_flint_1";
		break;

		case "BS_CPNG_32_flint_1":
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_32_flint";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_CPNG_32_flint":
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//Флинт присоединяется к эскадре
			Flag_Change(PIRATE);
			BSRepairShip(npchar);
			SetShipRemovable(npchar, false);
			SetCharacterRemovable(npchar, false);
			Fantom_SetBalls(npchar, "war");
			SetCharacterGoods(npchar,GOOD_FOOD,1000);
            dialog.text = "Calm down Eleanor. Mr. Silver, where did you see Wayne last?";
            link.l1 = "";
			link.l1.go = "BS_CPNG_32_silver_1";
		break;

		case "BS_CPNG_32_silver_1":
			sld = CharacterFromID("BS_Silver");
			sld.dialog.currentnode = "BS_CPNG_32_silver";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;

		case "BS_CPNG_32_silver":
            dialog.text = "Heh. I already told you, but you weren't listening. In a brothel in Martinique.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_33";
		break;

		case "BS_CPNG_33":
			npchar.LifeDay = 0;
			npchar.dialog.currentnode = "BS_CPNG_Final";
			sld = CharacterFromID("BS_Billy");
			sld.dialog.currentnode = "BS_CPNG_Final";
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.LifeDay = 0;
			sld = CharacterFromID("Gatri_temp");
			sld.LifeDay = 0;
			sld.dialog.currentnode = "BS_CPNG_Final";
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_Final";

            dialog.text = "";
            link.l1 = "I already like the beginning of the adventure! Let's go!";
			link.l1.go = "BS_CPNG_33_exit";
			//DoReloadCharacterToLocation("Pirates_tavern", "goto", "goto2");
		break;

		case "BS_CPNG_33_exit":
			PChar.quest.BSOnTheHorizon_End.win_condition.l1 = "location";
			PChar.quest.BSOnTheHorizon_End.win_condition.l1.location = "Bermudes";
			PChar.quest.BSOnTheHorizon_End.function = "BSOnTheHorizon_End";
			BSOnTheHorizon_SeaBattle();
			AddQuestRecord("BSOnTheHorizon", "4");
			ChangeCharacterAddressGroup(pchar, "Pirates_tavern", "goto", "goto2");
			LAi_SetPlayerType(pchar);
			DialogExit();
		break;

		case "BS_CPNG_Final":
			dialog.text = "We'll have a couple more mugs before we sail.";
			NextDiag.TempNode = "BS_CPNG_Final";
            link.l1 = "Don't be late.";
			link.l1.go = "exit";
			if (npchar.id == "Gatri_temp")
			{
				dialog.text = "Have a fair wind, Captain.";
				link.l1 = "Thank you.";
				link.l1.go = "exit";
			}
			if (npchar.id == "Flint")
			{
				dialog.text = "Let's not delay.";
				link.l1 = "I agree.";
				link.l1.go = "exit";
			}
		break;

		//Выходим в море. В эскадре – Флинт на 'Морже'.
		//На глобалке, на подходе к Мартинике – энка английский патруль.
		//Файт. (4-6 второклассников). Квест уходит в архив (СЖ: 'На подходе к Мартинике нарвались на патруль англичан. Вода вам пухом, саксы. Хе хе'.)

	}
}
