
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "I'm listening to you, " + PChar.lastname;
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "Wait, Captain, I have an urgent conversation with you.";
			link.l1 = "I'm listening to you carefully.";
			link.l1.go = "2";	
		break;
		
		case "2":
			dialog.text = "The conversation is very important and other ears are unnecessary. I'm waiting for you outside the city.";
			link.l1 = "As you wish.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandToCharlesExitTown");
		break;
		
		case "3":
			dialog.text = "The fact is that you accidentally became the owner of an item that rightfully belongs to me. I ask you to give it to me.";
			link.l1 = "What other right are you talking about? The first part of the map was given to me by Jim Smith, and you have nothing to do with it!";
			link.l1.go = "4";	
		break;
		
		case "4":
			dialog.text = "The fact is, Captain " + PChar.name + ", that unlike you, I also took part in that expedition, but you accidentally touched a story that you have no idea about.";
			link.l1 = "Jim Smith told me his story, and I'm going to get to the bottom of this case.";
			link.l1.go = "5";
		break;

		case "5":
			dialog.text = "Jim Smith was a pawn in that game and just happened to be alive. The matter is much more serious than you think. I advise you to give me all the parts of the map and forget everything as soon as possible.";
			link.l1 = "The hell with it! I'm not one of those people who stops halfway! Tell me what you know about this story!";
			link.l1.go = "6";
		break;

		case "6":
			dialog.text = "I thought you were smarter than you actually turned out to be. I'll have to take this piece of the map from your dead body!";
			link.l1 = "You're depriving me of the chance to find out what you alone know, because corpses can't talk! Defend yourself!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandFightWithDubben");
		break;

		case "7":
			dialog.text = "Okay, Captain " + PChar.name + ", I accept your terms. Listen carefully, now you will learn a lot of interesting things.";
			link.l1 = "I'm listening to you, " + npchar.name + "!";
			link.l1.go = "8";
		break;

		case "8":
			dialog.text = "Starfish Captain Davy Forser and I have made a deal. Now you will understand everything. Davy Forser knew in advance that it was impossible to leave this island, taking its treasures with him - the crew of the Starfish was doomed to perish. Two ships came to the island at once. Davy Forser's frigate and my brig, the Cutty Clark. I quietly anchored the ship on the other side of the island-these were the conditions. Captain Davy Forser said that without him, no one would be able to return to the island for treasures, and to take them now means certain death. Therefore, it was necessary to take some kind of thing from there, and then officially 'die' for his team. He promised me to return to the island for gold next time. Then, they say, it will be possible to touch the gold. It's all riddles, damn it! When we landed at the nearest port, captain was gone. When he fled, he took with him the map on which my navigator sailed to the island. I tried to chase him, but this scoundrel ruined my compass, I had to go back later, when I found out that several sailors of the Starfish had escaped from death, I began to look for them in order to take possession of the first copy of the map, that's where you beat me to it. I only know the fate of the fourth participant in the miraculous rescue, Diego Marquez. He is currently in prison in Santo Domingo for a debt to a local usurer. Perhaps he is the owner of the second part of the map.";
			link.l1 = "Yes, you told me a lot of interesting things, monsieur" + NPChar.name + ". Well, we have one part of the map, we need to sail to Santo Domingo for the second.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandToSantoDomingo");
		break;

		case "9":
			dialog.text = "Damn you! You are very good with a sword!";
			link.l1 = "If the matter is as serious as you say, I suggest you join our efforts. So, tell me everything you know!";
			link.l1.go = "7";

			bDisableOfficers = false;	
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
