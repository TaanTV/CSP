// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What did you want? Ask.", "I'm listening to you, what's the question?"), "For the second time in a day you're trying to ask a question...", "For the third time in a day you're trying to ask a question again...",
                          "But when will it end?! I have a lot of things to do to manage the affairs of the city, and you're trying to ask all the questions!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, not the place and not the time..."), "Yes, that's right... But not now, later...",
                      "I'll ask later...", "Sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//==> Проверка на стейт квестов
			if (pchar.questTemp.State == "Sp10Maracaibo_toMaracaibo")
			{
				dialog.text = "I'm listening to you...";
				link.l1 = "Senor, I have arrived to you to fulfill a responsible assignment to protect Maracaibo from an external threat. I'm on a business trip at your disposal by the Governor of Havana, Francisco Oregon y Gascon.";
				link.l1.go = "Step_S10_1";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_toGovernor")
			{
				dialog.text = "Well, you're just in time. We haven't had time to get settled and place a team in the city yet - and let's go into battle!";
				link.l1 = "That's right!";
				link.l1.go = "Step_S10_4";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_toBattle")
			{
				dialog.text = "Are you still here? I guess it's time for you to go into battle.";
				link.l1 = "That's right, senor. I won't keep the Ladrons waiting...";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_GoodWork")
			{
				dialog.text = "Great job, "+ GetSexPhrase("my friend","senorita") +". Don Francisco sent me a very brave and intelligent captain!";
				link.l1 = "Thank you, senor...";
				link.l1.go = "Step_S10_5";
			}
			//<== Проверка на стейт квестов
		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("You've already taken everything. What else do you need?", "Is there really anything left that you didn't bring?");
            link.l1 = RandPhraseSimple("Looking around for the last time...", "Checking, maybe I forgot to pick up something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

        //==> Двенадцатый квест голл. линейки. Захват Маракайбо.
        case "HolLine12Quest_Occupy":
			dialog.text = "That's it, we've stopped resisting. The city is yours. What's going to happen now?";
			link.l1 = "This city now belongs to the Republic of the United Provinces. Dutch governance is established here and Dutch laws are put into effect.";
			link.l1.go = "Step_H12_1";
			AfterTownBattle();
        break;
        case "Step_H12_1":
			dialog.text = "You are stronger at the moment. But we'll see what happens after a while. Apparently, Portugal in the Indian Ocean did not bother you very much, since you decided to take such an audacious step.";
			link.l1 = "This step is a logical response to the attacks of the Spanish squadrons.";
			link.l1.go = "Step_H12_2";
        break;
        case "Step_H12_2":
			dialog.text = "If you hadn't supplied France with money, none of this would have happened!";
			link.l1 = "I guess it's too late to argue about anything now. This city has become Dutch, and then we'll see.";
			link.l1.go = "exit";
            AddQuestRecord("Hol_Line_12_OccupyMaracaibo", "2");
            pchar.questTemp.State = "OccupyMaracaibo_toWeWon";
            NextDiag.TempNode = "Cupture_after";
			PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            UpdateRelations();
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
        break;
        //==> Десятый квест испанки. Защита Маракайбо.
        case "Step_S10_1":
			dialog.text = "Excellent, my request to reinforce the squadron and garrison has been satisfied!";
			link.l1 = "Yes, it is. Could you tell me what you're afraid of?";
			link.l1.go = "Step_S10_2";
        break;
        case "Step_S10_2":
			dialog.text = "Of course, Captain. So, I have some information that another gathering of English bandits in Port Royal is going to capture Maracaibo. This information does not deserve one hundred percent confidence, but nevertheless I asked for help from Senor Francisco Oregon y Gascon.";
			link.l1 = "Understood. What I owe to do now?";
			link.l1.go = "Step_S10_3";
        break;
        case "Step_S10_3":
			dialog.text = "Actually, nothing. Just be on alert.";
			link.l1 = "My team and I are always in this state... Well, if you don't need me then I'll probably walk around the city on my own business.";
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp10Maracaibo_TalkWithOfficer";
            Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition.l1 = "location";
            Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition.l1.location = "Maracaibo_town";
            Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition = "Sp10Maracaibo_TalkWithOfficer";
		break;
        case "Step_S10_4":
			dialog.text = "I ask you to proceed with your task. It is necessary to destroy the English pirate squadron!";
			link.l1 = "All right, senor.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Maracaibo_town", "gate_back", false);
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", false);
			pchar.questTemp.State = "Sp10Maracaibo_toBattle";
            Pchar.quest.Sp10Maracaibo_Battle.win_condition.l1 = "location";
            Pchar.quest.Sp10Maracaibo_Battle.win_condition.l1.location = "Maracaibo";
            Pchar.quest.Sp10Maracaibo_Battle.win_condition = "Sp10Maracaibo_Battle";
        break;
        case "Step_S10_5":
			dialog.text = "For the successful repulse of the English attack, the city is ready to pay you 70,000 gold. Please receive it, Captain.";
			link.l1 = "Very good.";
			link.l1.go = "Step_S10_6";
        break;
        case "Step_S10_6":
			dialog.text = "So, your task is done here, I dare not detain you any longer. Convey my sincere thanks to the Governor General of Oregon and Gascon.";
			link.l1 = "Absolutely, senor. Goodbye.";
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp10Maracaibo_2GoodWork";
			AddMoneyToCharacter(pchar, 70000);
        break;



	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

