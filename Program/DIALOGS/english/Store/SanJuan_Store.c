// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Ask me what you want?",
                          "We have just raised this issue. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Listen, this is a store, people are buying something here. Don't distract me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Um, I won't...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Romantic_1":
            dialog.Text = "(To Isabella): So are you going to pay or should I call the soldiers?";
			Link.l1 = "How dare you, you bastard!  Apologize to the senora immediately, or I will pierce your fat belly!";
		    Link.l1.go = "exit";
		    NextDiag.TempNode = "Second time";
		    AddDialogExitQuest("Romantic_TalkInShop_2");
		break;

		case "Romantic_2":
            dialog.Text = "Of course, of course, Senor Captain.";
			Link.l1 = "Here's another conversation.";
		    Link.l1.go = "exit";
		    NextDiag.TempNode = "Second time";
		    AddDialogExitQuest("Romantic_TalkInShop_2");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);
}

