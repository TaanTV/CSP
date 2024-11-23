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
			if (pchar.questTemp.State == "Fr9GuardPP_GoodWork")
			{
				dialog.text = "Captain, the whole city owes you for the rest of your life! You just saved us...";
				link.l1 = ""+ GetSexPhrase("Baron", "Baronessa") +", sir. I am the "+ GetSexPhrase("baron", "baronessa") +", not just a captain!.. Well, on this occasion - yes, I saved my life and very happy for it...";
				link.l1.go = "exit";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You've already taken everything. What else do you need?", "Is there really anything left that you didn't bring?");
            link.l1 = RandPhraseSimple("Looking around for the last time...", "Checking, maybe I forgot to pick up something");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

        //==> Двенадцатый квест исп.линейки: захват Порт-о-Принса.
        case "SpaLine12Quest_PortPax":
			dialog.text = "We give up, "+ GetSexPhrase("damn Castilian", "damn Spanish") +"...";
			link.l1 = "That's good - you saved your lives.";
			link.l1.go = "Step_S12_1";
			AfterTownBattle();
        break;
        case "Step_S12_1":
			dialog.text = "This is a French colony, what the hell...";
			link.l1 = "This is now a Spanish colony once and for all. Well, I'm not detaining you, Monsieur the former governor...";
			link.l1.go = "exit";
            AddQuestRecord("Spa_Line_12_OccupyPortPax", "2");
			pchar.questTemp.State = "OccupyPortPax_WeWin";
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

