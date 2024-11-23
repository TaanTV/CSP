// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Ask me, what do you want?",
                          "We have just raised this issue. You probably forgot...", "This is the third time you've talked about a question today...",
                          "Listen, this is a store, people are buying something here. Don't distract me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + "some other time.", "Exactly, "+ GetSexPhrase("I forgot", "I forgot") +"something...",
                      "Yeah, it's really the third time...", "Um, I won't...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

