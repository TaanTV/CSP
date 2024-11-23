// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "Whatever you want, " + GetAddress_Form(NPChar) + "?"), "More questions, " + GetAddress_Form(NPChar) + "...", "Questions, questions... Maybe we'll do some trading, " + GetAddress_Form(NPChar) + "?",
                          "Listen, how many empty conversations can you have?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("No questions...", "I have nothing to talk about right now."), "Eh, again...",
                      "Yes, it's really better to bargain...", "Hmm, sorry, trader...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
