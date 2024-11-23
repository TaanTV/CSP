// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, "+ GetSexPhrase("my son", "my daughter") +"?", "Ask, I'm listening to you..."), "I'm listening to you, tell me, "+ GetSexPhrase("my son", "my daughter") +"...", "And for the third time I tell you, "+ GetSexPhrase("my son", "my daughter") +": ask your question.",
                          "A clergyman has so many responsibilities, and then you're bothering, "+ GetSexPhrase("my son", "my daughter") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "Not now, Padre..."), "Yes, there's not much to say yet...",
                      "I'll ask, I'll ask... Only later...", "Excuse me, Holy Father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(PChar.MysteriousIsland == "10" && PChar.MysteriousIsland.FindForser.Church == false && NPChar.City == "SantoDomingo")	//Загадочный остров
			{
				link.l1 = "Holy Father, do you know the name Davy Forser?";
				link.l1.go = "MysteriousIsland_1";
			}
		break;
		
		// Загадочный остров -->
		case "MysteriousIsland_1":
			PChar.MysteriousIsland.FindForser.Church = true;
			dialog.text = "No, my son, I have not heard of such a thing.";
			link.l1 = LinkRandPhrase("Oh, sorry...", "Thanks for that.", "See you soon.");
			link.l1.go = "exit";
		break;
		// Загадочный остров <--
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



