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
		//************************** Квестовые штрумы ************************
        //==> Одиннадцатый квест англ.линейки: захват Каракаса и Куманы.
        case "EngLine11Quest_OccupyMein":
			dialog.text = "You have captured the city. What do you need?";
			link.l1 = "I am acting on the orders of the Governor-General of Jamaica, Sir Thomas Madiford, on the basis of a patent issued to me by the Council of Jamaica.";
			link.l1.go = "Step_E10_1";
			AfterTownBattle();
        break;
        case "Step_E10_1":
			dialog.text = "So what?";
			link.l1 = "From now on, the city of Caracas belongs to the English Crown. All tax fees, trade duties, and other taxes must be paid by the new English administration.";
			link.l1.go = "exit";
            AddQuestRecord("Eng_Line_11_OccupyMein", "2");
            pchar.questTemp.Q11_Caracas = 1;
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

