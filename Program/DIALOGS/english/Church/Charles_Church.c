// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, "+ GetSexPhrase("my son","my daughter") +"?", "Ask, I'm listening to you..."), "I'm listening to you, tell me, "+ GetSexPhrase("my son","my daughter") +"...", "And for the third time I tell you, "+ GetSexPhrase("my son","my daughter") +": ask your question.",
                          "A clergyman has so many responsibilities, and then you're bothering, "+ GetSexPhrase("my son","my daughter") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "Not now, Padre..."), "Yes, there's not much to say yet...",
                      "I'll ask, I'll ask... Only later...", "Excuse me, Holy Father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(PChar.MysteriousIsland == "3" && NPChar.City == "Charles")	// Загадочный остров
			{
				link.l1 = "Here's the thing. In one of the taverns, I met a strange sailor, Jim Smith. After the terrible events that happened to him, he is in a very bad state of mind.";
				link.l1.go = "MysteriousIsland_1";
			}
		break;
		
		// Загадочный остров -->
		case "MysteriousIsland_1":
			dialog.text = "I understand who you are talking about. I invited him to my place a long time ago, because two of his former comrades lived at our church, who also participated in those events that you mentioned. I helped them as much as I could, but I couldn't heal their souls.";
			link.l1 = "Where are they now?";
			link.l1.go = "MysteriousIsland_2";
		break;
		
		case "MysteriousIsland_2":
			dialog.text = "At the local graveyard, God rest their soul!";
			link.l1 = "Tell me, Father " + npchar.name+", did these two deceased people leave you anything before they died?";
			link.l1.go = "MysteriousIsland_3";
		break;
		
		case "MysteriousIsland_3":
			dialog.text = "You're talking about a part of the map, "+ GetSexPhrase("my son","my daughter") +"? I'll disappoint you- they didn't leave anything like that. And I wholeheartedly advise you not to mess with this story!";
			link.l1 = "Father " + npchar.name+", I want to figure out what happened.";
			link.l1.go = "MysteriousIsland_4";
		break;
		
		case "MysteriousIsland_4":
			dialog.text = "Well, I see I can't talk you out of it. Be vigilant, "+ GetSexPhrase("my son","my daughter") +", and don't forget our Lord!";
			link.l1 = "Thank you, Holy Father!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandToCharlesTown");
		break;
		// <-- Загадочный остров
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



