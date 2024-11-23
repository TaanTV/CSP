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
			if(PChar.MysteriousIsland == "10" && PChar.MysteriousIsland.FindForser.Store == false && NPChar.City == "SantoDomingo")	//Загадочный остров
			{
				link.l1 = "Did Captain Davy Forser buy anything from you?";
				link.l1.go = "MysteriousIsland_1";
			}
		break;
		
		// Загадочный остров -->
		case "MysteriousIsland_1":
			PChar.MysteriousIsland.FindForser.Store = true;
			dialog.text = "This is the first time I've heard of this.";
			link.l1 = LinkRandPhrase("Oh, sorry...", "Thanks for that.", "See you soon.");
			link.l1.go = "exit";
		break;
    	// Загадочный остров <--
	}
	UnloadSegment(NPChar.FileDialog2);
}

