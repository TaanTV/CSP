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

        //********************** Фр.линейка. Квест №11. Захват Санта Каталины ************************
		case "FraLine11Quest_OccupySC":
            dialog.text = "This is the second attack in recent times! The French are at great risk of blueprint the ire of the Escorial to the fullest.";
			link.l1 = "Heh, wow! Let the Queen Mother be angry, we have a war, my friend.";
            link.l1.go = "Step_F11_1";
			AfterTownBattle();
        break;
		case "Step_F11_1":
            dialog.text = "And what do you intend to do next?";
			link.l1 = "I intend to remove you, to swear the inhabitants to Louis XIV and transfer the management of the city into the hands of the French administration. Would you mind?";
			link.l1.go = "Step_F11_2";
        break;
		case "Step_F11_2":
            dialog.text = "Well, do you ironize, "+ GetSexPhrase("senor", "senorita") +"?";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr11OccupySC_toWeWon";
            AddQuestRecord("Fra_Line_11_OccupySantaCatalina", "2");
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

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

