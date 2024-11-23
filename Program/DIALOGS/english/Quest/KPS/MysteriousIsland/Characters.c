
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string sName = PChar.name + " " + PChar.lastname;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What else do you need, paleface? I don't want to talk to you right now.";
			link.l1 = "As you know.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "Bah, what a meeting, Captain Geoffroy! I didn't think we'd see each other again.";
			link.l1 = "";
			link.l1.go = "1_1";
			sld = CharacterFromID("Davy Forser");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Zhofrua Djubben"));
		break;	
		
		case "1_1":
			DialogExit();
			StartInstantDialog("Zhofrua Djubben", "2", "Quest\KPS\MysteriousIsland\Characters.c");
		break;
		
		case "2":
			dialog.text = "You tricked me, you dirty brute!";
			link.l1 = "";
			link.l1.go = "2_1";
			sld = CharacterFromID("Zhofrua Djubben");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Davy Forser"));
		break;
		
		case "2_1":
			DialogExit();
			StartInstantDialog("Davy Forser", "3", "Quest\KPS\MysteriousIsland\Characters.c");
		break;
		
		case "3":
			dialog.text = "No, it was your greed and greed that closed your eyes to the truth. Anyway, I used you, and now I don't need you.";
			link.l1 = "";
			link.l1.go = "3_1";
			sld = CharacterFromID("Davy Forser");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Zhofrua Djubben"));
		break;
		
		case "3_1":
			dialog.text = "By the way, who is this with you? Your new companion?";
			link.l1 = "Now the blood will wash the smile off your face. Defend yourself, you treacherous bastard!";
			link.l1.go = "exit";
			sld = CharacterFromID("Davy Forser");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			AddDialogExitQuestFunction("MysteriousIslandFightDavyForser");
			LAi_LocationDisableMonGenTimer("Hispaniola_Cave", 9999);
			LAi_LocationDisableToughSkeletonTimer("Hispaniola_Cave", 9999);
		break;
		
		case "5":
			dialog.text = "Looks like Captain Davy Forser is dead, isn't he? Did I hear the sounds of fighting?!";
			link.l1 = "Yes, you were not mistaken - he gave his soul to God.";
			link.l1.go = "6";
		break;
		
		case "6":
			dialog.text = "Did you take the golden idol that I gave to him?";
			link.l1 = "Yes, we have the idol, but we don't know what its purpose is.";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "I helped Davy enter the island for the first time - with the help of two ships, we managed to circumvent the spell. He had to get one thing for me, which was in an ancient underground ruin located right under the village. Davy Forser kept his word and delivered that thing to me. For this, I promised him to give the idol that removes the spell from this island. Place the idol on the sacred altar, which is located inside the wrecked ship and take the gold. As much as you want. There will be no more danger.";
			link.l1 = "Why are you so kind to us, Monchitlan? We killed your companion!";
			link.l1.go = "8";
		break;

		case "8":
			dialog.text = "All white people are the same to me. I don't see the difference. Consider that this gift has fallen on you from heaven.";
			link.l1 = "You're saying strange things. It remains only to believe you, goodbye!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandRetryToIsland");
		break;

		case "9":
			dialog.text = "Yes, captain " + sName + ", you helped a lot. And so I will thank you with good steel.";
			link.l1 = "What are you talking about?";
			link.l1.go = "9_1";
		break;
		
		case "9_1":
			dialog.text = "You're so naive, "+pchar.name+"! Did you really think that I will share the gold with you?";
			link.l1 = "Oh, that's what you mean... I should guessed it. The greed of the fraer ruined...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandFightWithDubbenInGrot");
		break;
		
		case "10":
			dialog.text = "I've been waiting for you, Captain!";
			link.l1 = "It looks like you made a mistake in something, old man! Look at what's going on around you!";
			link.l1.go = "11";
			
			DeleteAllOfficersFromLocation();
			bDisableOfficers = true;
		break;
		
		case "11":
			dialog.text = "There was no mistake, Captain. Both you and Davy Forser wanted gold - you got it, didn't you? White people exterminated almost all of our ancient people for the sake of gold, now let them drown in it themselves. Before the appearance of pale-faces on our land, people treated gold correctly - ate on it, drank water from gold cups and made beautiful jewelry for their women, but when the conquistadors came, they were greedy and merciless, and began to kill people Because of the gold trinkets, the Indian elders gathered a great council. It was decided to bury the remaining gold on that very island, and the supreme shaman put a spell on it. I am his direct descendant.";
			link.l1 = "You did it on purpose, you old bastard! Why do you think the current generation of white people should pay with their lives for the actions of the conquistadors of the early 16th century? By taking advantage of me, you want to condemn innocent mothers and their children, honest fathers and noble old men, but I will not allow you to do that! It is foolish to take revenge on people who were born many years after the events you speak of and have found this world as it is! History cannot be turned back!";
			link.l1.go = "12";
		break;

		case "12":
			dialog.text = "Your morals have not changed since then, and neither have your values. You wanted gold, Captain - take as much as you want!";
			link.l1 = "I "+GetSexPhrase("wrong", "wrong")+", but God gave man a choice between good and evil and now I will correct my mistake! I'm going to kill you!";
			link.l1.go = "13";
		break;

		case "13":
			dialog.text = "Stupid "+GetSexPhrase("boy", "girl")+"! What can you do to me!?";
			link.l1 = "Whatever I can do! If I die, then so be it!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandFightWithMonchitlan");
		break;

		case "14":
			dialog.text = "You did the right thing, captain " + GetFullName(pchar)+"! Now the spell has regained its power!";
			link.l1 = "How do you know me?";
			link.l1.go = "15";
		break;

		case "15":
			dialog.text = "Don't ask stupid questions!";
			link.l1 = "I don't know how to address you...";
			link.l1.go = "16";
		break;

		case "16":
			dialog.text = "It's better for you not to know. Goodbye, Captain! I'm sure you won't bother the Indian cache anymore, but just in case, I remind you not to do this.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandTheEnd");
			LAi_LocationDisableMonGenTimer("Hispaniola_Cave", -1);
			LAi_LocationDisableToughSkeletonTimer("Hispaniola_Cave", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
