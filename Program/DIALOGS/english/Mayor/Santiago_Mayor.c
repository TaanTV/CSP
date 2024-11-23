// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What did you want? Ask.", "I'm listening to you, what's the question?"), "For the second time in a day you're trying to ask a question...", "For the third time in a day you're trying to ask a question again...",
                          "But when will it end?! I have a lot of things to do to manage the affairs of the city, and you're trying to ask all the questions!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, not the place and not the time..."), "Yes, that's right... But not now, later...",
                      "I'll ask, I'll ask... Only later...", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            //===> Проверка состояния текущего квеста
            if (pchar.questTemp.State == "Sp5LaVegaAttack_toSantiago")
            {
    			dialog.text = "I'm listening to you, "+ GetSexPhrase("senor", "senorita") +".";
    			link.l1 = "I'm on a business trip at your disposal by the Governor-General of Havana.";
    			link.l1.go = "Step_S5_1";
            }
            if (pchar.questTemp.State == "Sp5LaVegaAttack_WeWon")
            {
    			dialog.text = "What do you say, officer?";
    			link.l1 = "Everything is done in the best possible way. The La Vega Buccaneer settlement has been destroyed, and their leader, Mansfield, was killed by me personally.";
    			link.l1.go = "Step_S5_6";
            }
            //<=== Проверка состояния текущего квеста
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You've already taken everything. What else do you need?", "Is there really anything left that you didn't bring?");
            link.l1 = RandPhraseSimple("Looking around for the last time...", "Checking, maybe I forgot to pick up something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

        //********************** Девятый квест англ.линейки: нападение на Сантьяго ************************
        case "EL9_SantiagoAttack":
			dialog.text = "You won, ladron!";
			link.l1 = "Senor, I don't like being called that. I would prefer to be called a privateer.";
			link.l1.go = "Step_E9_1";
			AfterTownBattle();
        break;
        case "Step_E9_1":
            dialog.text = "You can do it, you English pig.";
			link.l1 = "I'm afraid not, sir. The fact is that we are not leaving alone. You will accompany us on a trip to the shores of Jamaica. Sir Thomas Madiford is eager to meet you.";
			link.l1.go = "Step_E9_2";
        break;
        case "Step_E9_2":
            dialog.text = "What?!!! By what right?!!!";
			link.l1 = "By right of the winner, senor. And therefore, since, due to circumstances, we will have to communicate for some time.";
			link.l1.go = "Step_E9_3";
        break;
        case "Step_E9_3":
            dialog.text = "Manoel Rivero Pardal is already rushing to my rescue. You can't get far...";
			link.l1 = "It is not unusual for me to meet a Spaniard at sea. Pardal so Pardal, no problem. Get ready, honorable sir. And hurry up!";
			link.l1.go = "Step_E9_4";
        break;
        case "Step_E9_4":
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1); // статистика
			AddQuestRecord("Eng_Line_9_AttackSantiago", "2");
			chrDisableReloadToLocation = false;
            Pchar.quest.AttackSantiago_FightWithPardal.win_condition.l1 = "location";
            Pchar.quest.AttackSantiago_FightWithPardal.win_condition.l1.location = "Cuba1";
            Pchar.quest.AttackSantiago_FightWithPardal.win_condition = "AttackSantiago_FightWithPardal";
            // ==> Меняем имя и модель у губера,
            npchar.model = "usurer_3";
            npchar.name 	= "Gregorio Florido";
        	npchar.lastname = "de Balboa";
        	SendMessage(npchar, "lss", MSG_CHARACTER_SETMODEL, npchar.model, npchar.model.animation);
        	FaceMaker(npchar);
            // ==> а пленным делаем Альбермаля.
            sld = GetCharacter(NPC_GenerateCharacter("Himenes", "huber_spa", "man", "man", 10, SPAIN, -1, false));
            LAi_SetStayTypeNoGroup(sld);
            sld.name 	= "Jose Sancho";
        	sld.lastname = "Jimenez";
            SetCharacterRemovable(sld, false);
            AddPassenger(pchar, sld, true);
			SetReturn_Gover_Dialog_Exit(NPChar);
            DoReloadCharacterToLocation("Santiago_town",  "reload", "reload3");
            NextDiag.CurrentNode = "Cupture_after";
            chrDisableReloadToLocation = false;
			AddDialogExitQuestFunction("TWN_ExitForPay");
            DialogExit();
        break;
        //********************** Квест №5, Нападение на Ла Вегу. ************************
        case "Step_S5_1":
            dialog.text = "Yes, it's very good that you're here. Are you ready to fight on land?";
			link.l1 = "Always ready.";
			link.l1.go = "Step_S5_2";
        break;
        case "Step_S5_2":
            dialog.text = "Fine. In that case, please listen to what you have to do.";
			link.l1 = "You have my attention.";
			link.l1.go = "Step_S5_3";
        break;
        case "Step_S5_3":
            dialog.text = "You must attack and destroy the Buccaneer settlement on Hispaniola, called La Vega. It's run by a certain Edward Mansfield, an old ladron. This settlement is subject to total destruction, everything found there is your legitimate prey. Hispaniola should be completely Spanish, and the first obstacle on the way to this is La Vega. I'm expecting a new batch of colonists, they need space to live.";
			link.l1 = "Understood. Can I get started?";
			link.l1.go = "Step_S5_4";
        break;
        case "Step_S5_4":
            dialog.text = "Of course, and the sooner the better. Once again, I would like to draw your attention to the fact that the settlement must be completely destroyed, not a single living person should remain there. Hispaniola is our island, there is no place for this rabble on it.";
			link.l1 = "I understand and start the task immediately.";
			link.l1.go = "Step_S5_5";
        break;
        case "Step_S5_5":
            dialog.text = "Excellent! Don Francisco has recommended you as an extremely capable and efficient combat officer. I am waiting for you with good news.";
			link.l1 = "I can assure you that La Vega will soon cease to exist.";
			link.l1.go = "exit";
            pchar.questTemp.State = "Sp5LaVegaAttack_AttackLaVega";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "2");
            Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition.l1 = "location";
			Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition.l1.location = "LaVega_town";	// 22.08.2022 Sinistra Теперь сражение происходит сразу в городе из-за новой локации
            Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition = "Sp5LaVegaAttack_AttackGoOn";
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry3 = Rand(19)+40;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry4 = Rand(19)+40;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry5 = Rand(19)+40;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry7 = Rand(19)+20;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry8 = Rand(19)+20;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry10 = Rand(19)+20;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry14 = Rand(19)+20;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry17 = Rand(19)+40;
            pchar.GenQuestBox.LaVega_townhall.box1.items.cirass4 = 1;
			sld = characterFromId("Edward Mansfield");
			sld.Default.Crew.Quantity    = 1700;
			sld.Default.Crew.MinQuantity = 1100;
			sld.from_sea = ""; // для захвата с суши
			sld.Default  = "LaVega_townhall";  // чтоб сухопутные города вернули население
			sld.Default.BoardLocation = "LaVega_town";
			SetLocationCapturedState("Lavega_town", true);
        break;
        case "Step_S5_6":
            dialog.text = "Great, " + GetSexPhrase("senor","senorita") + "! Just great! Don Francisco of Oregon-i-Gascon can take great pride in having such officers in his service.";
			link.l1 = "Buccaneers are a worthy opponent, I am glad that I managed with this task. Senor, what about my payment?";
			link.l1.go = "Step_S5_7";
        break;
        case "Step_S5_7":
            dialog.text = "Ah yes... The completion of such a difficult task is estimated by the city of Santiago of 100,000 piastres. Please get it.";
			link.l1 = "Excellent. Senor Jimenez, I enjoyed doing business with you. Goodbye.";
			link.l1.go = "exit";
            AddMoneyToCharacter(pchar, 100000);
            pchar.questTemp.State = "Sp5LaVegaAttack_BackToHavana";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "4");
        break;
	}
    UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

