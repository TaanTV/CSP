// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What did you want? Ask.", "I'm listening to you, what's the question?"), "For the second time in a day you're trying to ask a question...", "For the third time in a day you're trying to ask a question again...",
                          "But when will it end?! I have a lot of things to do to manage the affairs of the city, and you're trying to ask all the questions!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, not the place and not the time..."), "Yes, that's right... But not now, later...",
                      "I'll ask, I'll ask... Only later...", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You've already taken everything. What else do you need?", "Is there really anything left that you didn't bring?");
            link.l1 = RandPhraseSimple("Looking around for the last time...", "Checking, maybe I forgot to pick up something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

        //==> Одиннадцатый квест исп.линейки: разорение Виллемстада и Мариго.
        case "SpaLine11Quest_DestrHol":
			dialog.text = "Damn it, damn Spaniards!! You've ruined the city!";
			link.l1 = "This is a punishment.";
			link.l1.go = "Step_S11_1";
			AfterTownBattle();
        break;
        case "Step_S11_1":
			dialog.text = "Punishment for what?";
			link.l1 = "For secretly participating in the devolution war on the side of the French. This will be a lesson to you...";
			link.l1.go = "exit";
            AddQuestRecord("Spa_Line_11_DestrHolland", "2");
            pchar.questTemp.Q11_Villemstad = 1;
            NextDiag.TempNode = "Cupture_after";
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			AddDialogExitQuestFunction("TWN_ExitForPay");
            SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

