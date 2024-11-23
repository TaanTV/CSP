// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question, " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Are we going to ask questions again?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yeah, really for the third time...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(PChar.MysteriousIsland == "2" && Characters[GetCharacterIndex("Jimm Smith")].location == PChar.location)
			{
				link.l1 = "Listen, buddy, could you tell me something about that sailor I was sitting with recently?";
				link.l1.go = "MysteriousIsland_1";
			}
		break;
		
		// Загадочный Остров -->
		case "MysteriousIsland_1":
			dialog.text = "Oh, you're talking about Jim Smith! What can I tell you, " + GetAddress_Form(NPChar) + ". He drinks godlessly every day, and when he gets drunk to hell, he keeps saying that he will soon leave here for the Charlestown church. It's the same thing every day!";
			if(sti(PChar.money) >= 500)
			{
				AddMoneytoCharacter(PChar, -500);
				link.l1 = "Thank you, " + npchar.name + ", take 500 coins, nowadays such selfless people like you are very rare.";
				link.l1.go = "exit";			
			}
			else
			{
				link.l1 = "Thank you, " + npchar.name + ".";
				link.l1.go = "exit";
			}
			AddDialogExitQuestFunction("MysteriousIslandToCharlesChurch");
		break;
		// Загадочный Остров <--
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

