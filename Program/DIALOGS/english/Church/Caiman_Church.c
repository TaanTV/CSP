// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, my son?", "Ask, I'm listening to you..."), "I'm listening to you, speak, my son...", "And for the third time I'm telling you, my son: ask your question.",
                          "A clergyman has so many responsibilities, and then you're bothering me, my son...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind..", "Not now, Padre..."), "Yes, there's not much to say yet...",
                      "I will ask, I will ask... Only later...", "Excuse me, Holy Father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

