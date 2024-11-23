void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	ref PChar = GetMainCharacter();
	string sName = PChar.name + " " + PChar.lastname; 
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Oh, it's you, Captain " + sName + ". Shall we have a drink?";
			link.l1 = "Uh, I don't have time right now.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "Ah, sit down, human soul! Won't you buy rum for the old sailor?";
			link.l1 = "Of course, old man, I don't mind a drink! Innkeeper, bring me rum!";
			link.l1.go = "exit";	
			AddDialogExitQuestFunction("MysteriousIslandTalkWithSmith");
			FreeSitLocator(PChar.location, "sit_front3");
		break;
		
		case "2":
			dialog.text = "Thank you, Captain! I'm always happy to have a free drink, because this tavern is where most of my life is spent, and I'm tight on money.";
			link.l1 = "The whole life in this tavern?! What happened to you, buddy?";
			link.l1.go = "3";
		break;
		
		case "3":
			dialog.text = "Ah, don't ask, Captain! It's a scary story. Let's have a drink instead!";
			link.l1 = "Innkeeper, two more mugs of rum!";
			link.l1.go = "4";
		break;
		
		case "4":
			LAi_Fade("", "");
			dialog.text = "You're "+GetSexPhrase("nice guy", "nice girl")+"! Once I was like that, but my life turned out so that now I hardly sleep at night - I am haunted by terrible dreams! Damn it... It's only in rum that I find solace...";
			link.l1 = "Share your trouble with me, sailor - maybe it will make you feel better.";
			link.l1.go = "5";
		break;
		
		case "5":
			dialog.text = "Well, listen then. I once sailed on the pirate frigate Starfish under Captain Devi Forser. One day we landed on an uninhabited island. The captain took us to a cave-that was a cave, I'll tell you -the chests there were bursting with all sorts of goods! Well, we grabbed as much as we could and went back to the ship. They missed us, but our captain is not there. We looked for him everywhere, but that's it. We thought that he was dead and decided to swim ourselves into the sea, and suddenly it started! A terrible storm, a hurricane wind - I have never seen such a thing in my life! Our ship was blown to pieces, and only four of the sailors escaped - they were thrown ashore by the waves. One of the survivors said that before the storm he went into captain's cabin to look for a drink, and saw a map on the table. Well, he took it with him just in case. We divided the map into two parts - we decided to assemble a team and come back here again.";
			link.l1 = "How did you get out of there?";
			link.l1.go = "6";
		break;
		
		case "6":
			dialog.text = "We decided to leave all the gold we had on the island - we put it all back. Fear attacked us - at night all sorts of evil spirits of Indian appearance began to appear, they threatened, they terrified us - a terrible thing. In general, we returned the gold and began to make a skiff - thank God, there was a carpenter among us, and some tools were thrown ashore.. That's my story, Captain... I returned home, but I can't live in peace. So I drown my fears in rum.";
			link.l1 = "That's the story! Where's the map?";
			link.l1.go = "7";
		break;
		
		case "7":
			TakeNItems(PChar, "MysteriousIsland_MapChapter", 1);
			dialog.text = "Yes, take it!";
			link.l1 = "Where's the rest?";
			link.l1.go = "8";
		break;
		
		case "8":
			dialog.text = "Where? My accomplices have it, if they are still alive. Go ahead. Captain, you make me nervous.";
			link.l1 = "Well, have a nice day, sailor!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandToBarmen");
		break;
		
		case "9":
			dialog.text = "I was told that I owe you my freedom?!";
			link.l1 = "Yes, Diego, I needed to talk to you!";
			link.l1.go = "10";
		break;
		
		case "10":
			dialog.text = "Oh here's the thing! However, I'm lucky. If you don't mind 1000 coins for an old drunk, I'll give it to you immediately.";
			if(sti(PChar.money) >= 1000)
			{
				AddMoneyToCharacter(PChar, -1000);
				link.l1 = "Here's the money, Diego. Give me a piece of the map!";
				link.l1.go = "11";			
			}
			else
			{
				link.l1 = "Give me a piece of the map! Otherwise, you're going back now.";
				link.l1.go = "11";			
			}
		break;

		case "11":
			TakeNItems(PChar, "MysteriousIsland_MapChapter", -1);
			TakeNItems(PChar, "MysteriousIsland_Map", 1);
			dialog.text = "Take it. I can guess what you are up to, and I sincerely advise you to abandon this idea.";
			link.l1 = "Goodbye, Diego. I wish you good luck.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandFirstVisit");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}