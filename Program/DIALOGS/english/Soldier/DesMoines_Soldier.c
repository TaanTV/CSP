// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have for the soldier?", "A soldier's life is painted - guards, divorces... Whatever you want, " + GetAddress_Form(NPChar) + "?"), "It's not appropriate to pester a soldier with stupid questions, " + GetAddress_Form(NPChar) + "...", "For the third time today, you're trying to ask a question...",
                          "The soldier's share is already difficult, and then there's you, "+ GetSexPhrase("bastard, ", " ") +"you're pissing me off...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I have nothing to talk about right now."), "It's not appropriate...",
                      "Yeah, it's really the third time...", "I'm sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

