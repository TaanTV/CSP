/// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Just recently you tried to ask me a question...", "Well, let me guess... Nothing significant again?",
                          "Listen, I'm handling finances, not answering questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "You guessed it, I'm sorry...", "I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(PChar.MysteriousIsland == "5" && NPChar.City == "SantoDomingo")
			{
				link.l1 = "I am interested in the fate of sailor Diego Marquez.";
				link.l1.go = "MysteriousIsland_1";
			}
			if(PChar.MysteriousIsland == "5" && NPChar.City == "SantoDomingo" && PChar.MysteriousIsland.FirstNoneMoney == true)
			{
				link.l1 = "I'm still on about Diego Marquez.";
				link.l1.go = "MysteriousIsland_6";
			}		
			if(PChar.MysteriousIsland == "9" && NPChar.City == "SantoDomingo")
			{
				Link.l1 = "Hello, Mr. " + NPChar.lastname + ". I remember that you mentioned the name of Captain Davy Forser during our last visit? Do you have any other information about this person?";
				Link.l1.go = "MysteriousIsland_7";
			}
		break;
		
		// ЗАГАДОЧНЫЙ ОСТРОВ -->
		case "MysteriousIsland_1":
			dialog.text = "Wow! This man owed me a large sum of 100000 coins. And now he's in custody in a local prison. He kept saying that he was going to have a lot of money, and I believed him, and as it turned out, in vain. He briefly told me about his adventures. By the way, his Captain Davy Forcer has been to my place, but I've never seen them before.";
			if(sti(PChar.money) >= 100000)
			{
				link.l1 = "I'm ready to pay you the specified amount. I need Diego Marquez free.";
				link.l1.go = "MysteriousIsland_2";	
			}			
			link.l2 = "This is a lot of money! And how did he manage to get into such debts? Anyway, thanks for the information, let me take my leave.";
			link.l2.go = "MysteriousIsland_3";
		break;

		case "MysteriousIsland_2":
			AddMoneyToCharacter(PChar, -100000);
			PChar.MysteriousIsland.FirstNoneMoney = false;
			dialog.text = "Great! In that case, I'll handle all the formalities myself. Come back tomorrow - Diego Marquez will be waiting for you here.";
			link.l1 = "Excellent. Goodbye.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandWaitDiegoMarkes");
		break;

		case "MysteriousIsland_3":
			PChar.MysteriousIsland.FirstNoneMoney = true;
			dialog.text = "Have a nice day, captain!";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "MysteriousIsland_4":
			dialog.text = "You see, captain - the secrecy of the deposit is one of the basic principles of my work with clients. However, for 2000 coins I am ready to share with you information.";
			if(sti(PChar.money) >= 2000)
			{
				AddMoneyToCharacter(PChar, -2000);
				link.l1 = "Take the money, senor " + NPChar.lastname + ". So, what do you know?";
				link.l1.go = "MysteriousIsland_5";
			}
			else
			{
				link.l1 = "What's what? It doesn't cost me anything to pierce you with my sword. Tell me everything, no kidding!";
				link.l1.go = "MysteriousIsland_5";		
			}
		break;
		
		case "MysteriousIsland_5":
			dialog.text = "Okay... The fact is that Davy Forser is no longer my client, otherwise I just wouldn't be talking to you. Yesterday he took all his money, a very, very large sum.";
			link.l1 = "Yesterday?! Damn it, we missed each other quite a bit! We have to hurry! Goodbye, Mr. " + NPChar.lastname + "!";
			link.l1.go = "exit";
		break;
		
		case "MysteriousIsland_6":
			dialog.text = "Are you ready to pay off the debt for Diego?";
			if(sti(PChar.money) >= 100000)
			{
				link.l1 = "Yes. This is the money.";
				link.l1.go = "MysteriousIsland_2";
			}
		
			link.l2 = "Uh.. Probably not. Goodbye.";
			link.l2.go = "exit";
		break;
		
		case "MysteriousIsland_7":
			dialog.text = "You see, captain - the secrecy of the deposit is one of the basic principles of my work with clients. However, for 2000 coins I am ready to share with you information.";
			if(sti(PChar.money) >= 2000)
			{
				AddMoneyToCharacter(PChar, -2000);
				link.l1 = "Take the money, senor " + NPChar.lastname + ". So, what do you know?";
				link.l1.go = "MysteriousIsland_8";
			}
			else
			{
				link.l1 = "What's that? It doesn't cost me anything to pierce you with my sword. Tell me everything, no kidding!";
				link.l1.go = "MysteriousIsland_8";		
			}
		break;
		
		case "MysteriousIsland_8":
			dialog.text = "Okay... The fact is that Davy Forser is no longer my client, otherwise I just wouldn't be talking to you. Yesterday he took all his money, a very, very large sum.";
			link.l1 = "Yesterday?! Damn it, we missed each other quite a bit! We have to hurry! Goodbye, Mr. " + NPChar.lastname + "!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandFindDavyForser");
		break;
		// <-- ЗАГАДОЧНЫЙ ОСТРОВ
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

