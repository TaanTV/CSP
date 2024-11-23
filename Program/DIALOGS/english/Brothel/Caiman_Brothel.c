// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, young man?", "What do you want, handsome?"), "More questions?", "Hee-hee, the third time a day the same thing - questions...",
                          "Hmm, can you choose some beauty for yourself? And then I already have a very definite opinion about you...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "Hmm, nothing..."), "No...",
                      "Yeah, it's really the third time... Sorry.", "Not now... Another time...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

