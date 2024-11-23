
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

		case "BS_CPNG_1":	//Бармен
			dialog.text = "Hey, aren't you the one our hope and strength is looking for, fair-faced Miss Guthrie?";
			link.l1 = "Oh, my God! What is it this time?";
			link.l1.go = "BS_CPNG_2";
		break;

		case "BS_CPNG_2":
            dialog.text = "I have no idea. But her messenger was very persuasive in telling her to tell the captain "+pchar.name+", that they're waiting for him at the Guthrie residence in the Bahamas. And if I were this captain, I wouldn't delay.";
            link.l1 = "Okay, I get it..";
			link.l1.go = "exit";
		break;

		//Багамы, перед магазином сценка. Гатри орёт на кучку пиратских кэпов. (штук 5-6 неписей Кэпов)

		case "BS_CPNG_3":	//Гатри
            dialog.text = "Mr. Fix! Tobacco is valuable when it's not soaked in urine! If you or your chief mate can't enforce proper discipline on the ship, I can easily find a replacement!";
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
            dialog.text = "Ms. Guthrie! With all due respect, this is my ship and I am...";
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
            dialog.text = "Prevon! You are now Captain of the Fox. Take command!";
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
            dialog.text = "I am... How dar... I'm not gonna let it go!";	//уходит
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
            dialog.text = "Ah, there you are. Just in time. Okay, gentlemen, let's take a short break. We'll continue this later.";	//остальные уходят
            link.l1 = "";
			link.l1.go = "BS_CPNG_8";
		break;

		case "BS_CPNG_8":	//Гатри
			chrDisableReloadToLocation = false;
            dialog.text = "I have a case. Mutually beneficial, let's do it in my living room.";	//Релоад в дом Гатри, первый этаж.
            link.l1 = "Let's go.";
			link.l1.go = "BS_CPNG_9_1";
		break;

		case "BS_CPNG_9_1":	//Гатри
			PChar.quest.Gatri_upstairs.win_condition.l1 = "location";
			PChar.quest.Gatri_upstairs.win_condition.l1.location = "Nassau_OfisGatri";
			PChar.quest.Gatri_upstairs.function = "Gatri_upstairs";
			NextDiag.CurrentNode = "BS_CPNG_9";
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "Nassau_OfisGatri", "quest", "quest5");
            DoReloadCharacterToLocation("Nassau_OfisGatri","officers","reload1_3");
		break;

		case "BS_CPNG_9":	//Гатри
            dialog.text = "Listen carefully!";
            link.l1 = "Wait a minute. Why are we suddenly on a first-name basis? And what's happened that requires my services? I can see that business is booming here, I can see how many caps are catching your every word.";
			link.l1.go = "BS_CPNG_10";
		break;

		case "BS_CPNG_10":
            dialog.text = "Would a more formal style of communication suit you? Is your lordship offended by the 'you'? To hell with formality! I have a case. It's urgent and very lucrative, and the Guthrie are not in the habit of missing out! Can you keep up with the thinking?";
			link.l1 = "I'm all ears.";
			link.l1.go = "BS_CPNG_11"
		break;

		case "BS_CPNG_11":
            dialog.text = "Okay. I have a friend. More than a friend. Almost like a father. Captain Flint. You ever heard of him?";
            link.l1 = "Flint. Wow. They scare kids with his name even in Asia.";
			link.l1.go = "BS_CPNG_12";
		break;

		case "BS_CPNG_12":
            dialog.text = "You have nothing to fear. And his reputation is well deserved - he is a very cruel and rational man, but fair and appreciative of friendship.\n"+
							"So here it is. He has embarked on a venture that could enrich all those involved or, on the contrary, ruin them. And I want things to go the first way and I intend to help in any way I can.";
            link.l1 = "And what is my role in this scenario?";
			link.l1.go = "BS_CPNG_13";
		break;

		case "BS_CPNG_13":
            dialog.text = "Find him at sea. Remember, it's very important to be under a black flag when you meet him! When you see him, tell him you've also read Marcus Aurelius. That's the password. He'll tell you the rest.";
            link.l1 = "And where to find Flint?";
			link.l1.go = "BS_CPNG_14";
		break;

		case "BS_CPNG_14":
            dialog.text = "It's hard to say. He only goes into pirate coves, and not for long. Look for him at sea.";
            link.l1 = "I'll see you later.";			
			link.l1.go = "BS_CPNG_14_exit";			
		break;
		
		case "BS_CPNG_14_exit":
			DialogExit();			
			DeleteAttribute(PChar, "currentsoundtrack");
			DeleteAttribute(npchar, "talker");
			LAi_LocationFightDisable(&Locations[FindLocation("Nassau_town")], false);
			AddQuestRecord("BSOnTheHorizon", "2");
			BSOnTheHorizon_Flint();
			SaveCurrentQuestDateParam("GatriSalutation");
			npchar.Dialog.FileName = "Quest\BlackSails\NePluyjVKolodec.c";
			npchar.dialog.currentnode = "BS_NPVK_20_meet";			
			DoReloadCharacterToLocation("Nassau_town", "reload", "houseS1");
		break;

		//Запись в сж, та же, что и теперь. Для сибиряка и прочих умственно отсталых, можно продублировать правильный пролог там. но я бы не стал 6.04.2023
		//После диалога запускаем по глобалке модельку БОЛЬШУЮ пиратскую( или фиолетовый квестовик), который курсирует между ПИРАТСКИМИ портами.
		//Под пиратским флагом – всё ОК. под любым другим – файт и провал квеста.
		//Флинт на Тяжёлом военном пинасе «Морж». Высылаем шлюпку. Говорим.

		case "BS_CPNG_15":	//Флинт
            dialog.text = "I'm familiar with this ship, but this is the first time I've seen the captain. Introduce yourself.";
            link.l1 = "I "+GetFullName(pchar)+", Ms. Guthrie asked me to look you up, Captain Flint.";
			link.l1.go = "BS_CPNG_16";
		break;

		case "BS_CPNG_16":
            dialog.text = "I'm familiar with Ms. Guthrie and her father, but what is your connection to them and me?";

			//это такая засада.. чтобы читали текст :)
			MakeRandomLinkOrderThree(link,
			"I too have read Marcus Aurelius and am a big fan of his work and am willing to give all the support and help I can to a like-minded person.",
			"BS_CPNG_17_Horosho",

			"I too have read Mark Anthony and am a big fan of his work and am willing to give all the support and help I can to a like-minded person.",
			"BS_CPNG_17_Ploho",

			"I hear the legendary Flint needs help on some adventure. And here I am!",
			"BS_CPNG_17_Ploho"
			);
		break;

		case "BS_CPNG_17_Ploho":
            DeleteAttribute (npchar, "AlwaysFriend");
			npchar.AlwaysEnemy = true;
			dialog.text = "I don't know who you are and I suggest you leave my ship.";
            link.l1 = "Uh, uh... Goodbye.";
			NextDiag.TempNode = "BS_CPNG_17_Ploho_end";
			link.l1.go = "exit";
		break;

		case "BS_CPNG_17_Ploho_end":
            dialog.text = "Get off my ship now!";
            link.l1 = "You don't have to be rude to me, I was just leaving.";
			NextDiag.TempNode = "BS_CPNG_17_Ploho_end";
			link.l1.go = "exit";
		break;

		case "BS_CPNG_17_Horosho":
			PChar.quest.MeetFlintCrew.win_condition.l1 = "location";
			PChar.quest.MeetFlintCrew.win_condition.l1.location = "Nassau_town";
			PChar.quest.MeetFlintCrew.function = "MeetFlintCrew";
            dialog.text = "It's better to talk about this without anyone hearing about it. I'll take care of some business and go to the Bahamas, and we'll talk there.";
			npchar.StopSailing = true;
			AddQuestRecord("BSOnTheHorizon", "3");
            link.l1 = "All right, I'll see you later.";
			NextDiag.TempNode = "BS_CPNG_17_Horosho_end";
			link.l1.go = "exit";
		break;

		case "BS_CPNG_17_Horosho_end":
            dialog.text = "Go back to your ship, let's not waste any more time.";
            link.l1 = "You're right, I'll go.";
			NextDiag.TempNode = "BS_CPNG_17_Horosho_end";
			link.l1.go = "exit";
		break;

		//Бвнвмы. На берегу Флинт, Сильвер, Бонс.

		case "BS_CPNG_18":	//Флинт
            dialog.text = "Meet. First Mate Billy Bones, Corporal John Silver.";
            link.l1 = "Nice to meet you. I "+GetFullName(pchar)+". Ms. Guthrie's already been waiting for us, I don't think we should keep her waiting.";
			link.l1.go = "BS_CPNG_19";
		break;

		case "BS_CPNG_19":
            dialog.text = "Yeah, it's not polite to keep a lady waiting. Especially this lady! Come on, I want to dot the i's.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_19_exit";	//Переход в дом на первый этаж. Гатри, Флинт, ГГ.
		break;

		case "BS_CPNG_19_exit":
			sld = CharacterFromID("Gatri_temp");
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.dialog.currentnode = "BS_CPNG_20";
			sld.talker = 10;
			DialogExit();
			SetFunctionLocationCondition("BS_GatryFlintInHouseDialogue", "Nassau_OfisGatri", false);
            StartReloadToCobHouse();
		break;

		case "BS_CPNG_20":	//Гатри
            dialog.text = "James, I'm the one who sent him to you. He's not just a miner, this captain is like you, if you know what I mean.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_21_1";
		break;

		case "BS_CPNG_21_1":
			NextDiag.CurrentNode = "BS_CPNG_21";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_21":	//Флинт
			npchar.name = GetConvertStrWithReplace("Variable_black_sails_functions_6", "Names.txt", "#space#", " ");
			npchar.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_7", "Names.txt", "#space#", " ");
            dialog.text = "I see an adventurer, an experienced captain with a fine ship and a well-trained crew. I'm very rarely wrong, Eleanor, you know that. You vouch for him?";
            link.l1 = "";
			link.l1.go = "BS_CPNG_22_1";
		break;

		case "BS_CPNG_22_1":
            npchar.name = GetConvertStrWithReplace("Variable_black_sails_functions_2", "Names.txt", "#space#", " ");
			npchar.lastname = GetConvertStrWithReplace("Variable_black_sails_functions_3", "Names.txt", "#space#", " ");
			NextDiag.CurrentNode = "BS_CPNG_22";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_22":	//Гатри
            dialog.text = "We had our disagreements, but it's all worked out. And my island is mine because of h"+ GetSexPhrase("im","er") +". Yes, I vouch for this captain.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_23_1";
		break;

		case "BS_CPNG_23_1":
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_23";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_CPNG_23":	//Флинт
            dialog.text = "Well, now for the case.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_24";
		break;

		case "BS_CPNG_24":	//Флинт
            dialog.text = "So, Captain "+GetFullName(pchar)+". Have you heard of the 'Urca de Lima'? The Spanish money galleon carrying not gold ore, but minted gold doubloons?";
            link.l1 = "Mmm... I confess I've heard rumors about this floating fortress. Not even rumors, but speculations and tales that this galleon almost carries the treasury of Escorial. But only if the 'Golden Fleet' was seen by many people, the 'Urka' was never seen!";
			link.l1.go = "BS_CPNG_25";
		break;

		case "BS_CPNG_25":
            dialog.text = "'Urca De Lima' is a very tough nut to crack, yes. And I have information on where and when this galleon will be resupplying water and provisions for the voyage to Spain. And this is the perfect chance to crack that nut.";
            link.l1 = "What's the price of the question?";
			link.l1.go = "BS_CPNG_26";
		break;

		case "BS_CPNG_26":
            dialog.text = "One hundred and fifty million pesos!";
            link.l1 = "Mother of God!";
			link.l1.go = "BS_CPNG_27";
		break;

		case "BS_CPNG_27":
            dialog.text = "Are you in? Yes or no? Otherwise, you know how this meeting ends.";
            link.l1 = "Of course I'm in! Where, how and when?!";
			link.l1.go = "BS_CPNG_28";
		break;

		case "BS_CPNG_28":
			chrDisableReloadToLocation = false;
            dialog.text = "We'll ask Mr. Silver about that, if he's not already drunk as hell.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_28_exit";	//Спускаемся вниз. За столом Бонс и Сильвер.
		break;

		case "BS_CPNG_28_exit":
			PChar.quest.Silver_Downstairs.win_condition.l1 = "location";
			PChar.quest.Silver_Downstairs.win_condition.l1.location = "Nassau_tavern";
			PChar.quest.Silver_Downstairs.function = "Silver_Downstairs";
			NextDiag.CurrentNode = "BS_CPNG_24";
			DialogExit();           
			FreeSitLocator("Nassau_tavern", "sit_front2");
			FreeSitLocator("Nassau_tavern", "sit_base2");
			FreeSitLocator("Nassau_tavern", "sit_base1");
			FreeSitLocator("Nassau_tavern", "sit2");
			pchar.currentsoundtrack = "All_Saints";
			DoReloadCharacterToLocation("Nassau_tavern","sit", "sit_front2");
			ChangeCharacterAddressGroup(npchar, "Nassau_tavern", "sit", "sit_base2");
			LAi_SetSitType(npchar);
			LAi_SetSitType(pchar);
			sld = CharacterFromID("BS_Billy");
			ChangeCharacterAddressGroup(sld, "Nassau_tavern", "sit", "sit_base1");
			LAi_SetSitTypeNoGroup(sld);
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("BS_Silver");
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.dialog.currentnode = "BS_CPNG_29";
			ChangeCharacterAddressGroup(sld, "Nassau_tavern", "sit", "sit2");
			LAi_SetSitType(sld);
			sld = CharacterFromID("gatri_temp");
			ChangeCharacterAddressGroup(sld, "Nassau_tavern", "tables", "stay3");
		break;

		case "BS_CPNG_29":	//Сильвер
            dialog.text = "...";
            link.l1 = "Mr. Silver? I'm Captain Flint's new companion, it's about time I shared some information!";
			link.l1.go = "BS_CPNG_30";
		break;

		case "BS_CPNG_30":
            dialog.text = "Greetings, Captain! What do you think of the local, colonial brothels?";
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
            dialog.text = "I'm more serious than ever! I only have part of the code to the encrypted route! Captain Wayne has the rest.";
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
		break;

		case "BS_CPNG_32_gatri":
			LAi_SetActorTypeNoGroup(npchar);
            dialog.text = "Charles Wayne! Damn it! How! Rrrr!!!";
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
			ProcessHullRepair(npchar, 100.0);
			ProcessSailRepair(npchar, 100.0);
			DeleteAttribute(npchar, "ship.blots");
			DeleteAttribute(npchar, "ship.sails");
			RepairMasts(npchar);
			SetShipRemovable(npchar, false);
			SetCharacterRemovable(npchar, false);
			Fantom_SetBalls(npchar, "war");
			SetCharacterGoods(npchar, GOOD_FOOD, 2900);
            dialog.text = "Calm down, Eleanor. Mr. Silver, where was the last place you saw Wayne?";
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
			LAi_CharacterDisableDialog(npchar);
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_Final";

            dialog.text = "";
            link.l1 = "I'm already loving the beginning of the adventure! Let's go!";
			link.l1.go = "BS_CPNG_33_exit";
		break;

		case "BS_CPNG_33_exit":		
			SetFunctionExitFromLocationCondition("BS_OnTheHorizonTavernExit", pchar.location, false);
			DeleteAttribute(PChar, "currentsoundtrack");
			BSOnTheHorizon_SeaBattle();
			PChar.quest.BattleSeaDefenceColonyWinner.win_condition.l1 = "Group_Death";
			PChar.quest.BattleSeaDefenceColonyWinner.win_condition.l1.group = "Sea_BSOnTheHorizon_SeaBattle1";
			PChar.quest.BattleSeaDefenceColonyWinner.function = "BSOnTheHorizon_End";
			pchar.quest.BSCourtlyPassions_DontStart.win_condition.c1 = "NPC_Death";
			pchar.quest.BSCourtlyPassions_DontStart.win_condition.c1.character ="Flint";
			PChar.quest.BSCourtlyPassions_DontStart.function = "BSCourtlyPassions_DontStart";
			AddQuestRecord("BSOnTheHorizon", "4");
			InterfaceStates.Buttons.Save.enable = true;
			ChangeCharacterAddressGroup(pchar, "Nassau_tavern", "tables", "stay4");
			LAi_SetPlayerType(pchar);
			DialogExit();
		break;

		case "BS_CPNG_Final":
			dialog.text = "We'll have a couple more drinks before we set sail.";
			NextDiag.TempNode = "BS_CPNG_Final";
            link.l1 = "Don't be late.";
			link.l1.go = "exit";
			if (npchar.id == "Gatri_temp")
			{
				dialog.text = "You have a fair wind, Captain.";
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

		//Выходим в море. В эскадре – Флинт на «Морже».
		//На глобалке, на подходе к Мартинике – энка английский патруль.
		//Файт. (4-6 второклассников). Квест уходит в архив (СЖ: «На подходе к Мартинике нарвались на патруль англичан. Вода вам пухом, саксы. Хе хе».)

	}
}
