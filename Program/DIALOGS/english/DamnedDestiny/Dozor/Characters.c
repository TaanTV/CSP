
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sName = GetFullName(PChar);
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you need?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		// РЫБАК ПЕДРО -->
		case "Fisher_Pedro_1":
			dialog.text = "... (almost crying)... Are you going there too? Do you want to make fun of Pedro too? Come on, what are you waiting for?";
			link.l1 = "An elusive Squadron has appeared in the waters of the Caribbean Sea.";
			link.l1.go = "Fisher_Pedro_2";
		break;

		case "Fisher_Pedro_2":
			dialog.text = "What? What did you just say?";
			link.l1 = "An elusive Squadron has appeared in the waters of the Caribbean Sea.";
			link.l1.go = "Fisher_Pedro_3";
		break;

		case "Fisher_Pedro_3":
			dialog.text = "... (brightening up)... So you're watchman, who got involved in game?";
			link.l1 = "Yes, it's me. Do you have anything for me?";
			link.l1.go = "Fisher_Pedro_4";
		break;

		case "Fisher_Pedro_4":
			TakeNItems(PChar, "Dozor_Mekakhrom", 1);
			dialog.text = "Yes, here you go! This is the second Mekakhrom.";
			link.l1 = "Thank you. Good luck to you.";
			link.l1.go = "Fisher_Pedro_5";
		break;

		case "Fisher_Pedro_5":
			dialog.text = "Uh, Captain, wait! Would you happen to have 50 gold for the poor fisherman?";

			if(sti(PChar.money) >= 50)
			{
				link.l1 = "Just promise me you'll spend it wisely, not drink it or lose it, okay?";
				link.l1.go = "Fisher_Pedro_6";
			}

			link.l2 = "It won't happen by chance. Goodbye.";
			link.l2.go = "Fisher_Pedro_9";
		break;

		case "Fisher_Pedro_6":
			dialog.text = "Okay! Give them to me quickly!";
			link.l1 = "Ha! Did you really think that I would give them to you? Keep your pocket wider.";
			link.l1.go = "Fisher_Pedro_7";
			link.l2 = "Here you go and say goodbye. I don't have time to hang around with you.";
			link.l2.go = "Fisher_Pedro_8";
		break;

		case "Fisher_Pedro_7":
			dialog.text = "Oh, you! Oh, you greedy brute! Cursed, overindulged" +" " + GetSexPhrase("bastard","bitch") +"! Get out! ...(whimpering)... Get out!";
			link.l1 = "Get out of my sight, you jerk.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorFisherPedroExit");
		break;

		case "Fisher_Pedro_8":
			AddMoneyToCharacter(PChar, -50);
			DozorFisherPedroExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Fisher_Pedro_9":
			DozorFisherPedroExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// РЫБАК ПЕДРО <--

		// УБИЙЦЫ АГЕНТА В ГРОТЕ ТЕРКСА -->
		case "Grot_Agent_Killers_1":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 2"));
			dialog.text = "Goebels: Throw that thing away, Krieger, it's not worth a damn.";
			link.l1 = "";
			link.l1.go = "Grot_Agent_Killers_2";
		break;

		case "Grot_Agent_Killers_2":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 1"));
			dialog.text = "Krieger: And I'm sure this is a very important thing. Look, it says here...";
			link.l1 = "";
			link.l1.go = "Grot_Agent_Killers_3";
		break;

		case "Grot_Agent_Killers_3":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 2"));
			dialog.text = "Goebels: ...(interrupting)... Look who came to us!";
			link.l1 = "";
			link.l1.go = "Grot_Agent_Killers_4";
		break;

		case "Grot_Agent_Killers_4":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 1"));
			dialog.text = "Krieger: ...(through clenched teeth)... Another victim. Right into our clutches!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorBattleInTerksGrot");
		break;
		// УБИЙЦЫ АГЕНТА В ГРОТЕ ТЕРКСА <--

		// СПАНЧ БОБ -->
		case "Spanch_Bob_1":
			dialog.text = "And-ik? What do you need?";
			link.l1 = "The brave captain engaged in battle with the Elusive Squadron.";
			link.l1.go = "Spanch_Bob_2";
		break;

		case "Spanch_Bob_2":
			dialog.text = "Ah! Are you Watching, " + GetSexPhrase("friend","girlfriend") +"?";
			link.l1 = "Yes, I've decided to get involved, try it.";
			link.l1.go = "Spanch_Bob_3";
		break;

		case "Spanch_Bob_3":
			dialog.text = "And decided correctly! I remember playing this game too, those were nice days. It's been a while. Yes, but our team was unlucky all the time. Then the mast will break, then we will run aground, then some other dirty trick will happen.";
			link.l1 = "Have such games been held before?";
			link.l1.go = "Spanch_Bob_4";
		break;

		case "Spanch_Bob_4":
			dialog.text = "Of course! Didn't you know?";
			link.l1 = "I didn't know. This is the first time I've heard of this.";
			link.l1.go = "Spanch_Bob_5";
		break;

		case "Spanch_Bob_5":
			dialog.text = "Oh, you're a village, Cap. Well, good luck with that... I-ic! In general, goodbye, " + GetSexPhrase("brother","sister") +"!";
			link.l1 = "Hey! But what about the next Mekakhrom?";
			link.l1.go = "Spanch_Bob_6";
		break;

		case "Spanch_Bob_6":
			dialog.text = "Meka-how? Mecahrom?";
			link.l1 = "You should have handed it to me, there's the next riddle.";
			link.l1.go = "Spanch_Bob_7";
		break;

		case "Spanch_Bob_7":
			dialog.text = "Ah, this is a useless piece of... iron. I'm sorry, " + GetSexPhrase("brother","sister") +", I drank it the other day.";
			link.l1 = "What?! Did you drink it? Are you completely out of your mind, a drunken wreck? How do you think I should continue the game? Huh?!";
			link.l1.go = "Spanch_Bob_8";
		break;

		case "Spanch_Bob_8":
			dialog.text = "Don't get so worked up!";
			link.l1 = "I dropped 20 thousands for the game! I'm going to slit your throat, you pig!";
			link.l1.go = "Spanch_Bob_10";
		break;

		case "Spanch_Bob_10":
			dialog.text = "Hey! Get your hands off me! I-ic! If you help me, I'll help you!";
			link.l1 = "And how are you going to help me?";
			link.l1.go = "Spanch_Bob_11";
		break;

		case "Spanch_Bob_11":
			dialog.text = "If you give me five hundred, I'll tell you a riddle, I remember it well.";
			link.l1 = "And how do I get a keyword without a Mecachrome?";
			link.l1.go = "Spanch_Bob_12";
		break;

		case "Spanch_Bob_12":
			dialog.text = "I'll tell you if you solve the riddle. I remember her well.";
			link.l1 = "Is that so? So, did you solve that riddle in the Mecahrome?";
			link.l1.go = "Spanch_Bob_13";
		break;

		case "Spanch_Bob_13":
			dialog.text = "What's there to solve? Here in the real Watch, there are puzzles such that you will break your head while you solve them, and anyone will solve your children's 'riddles' in 5 minutes.";
			link.l1 = "... (in a low voice)... So maybe you can tell me the key phrase right away, and the puzzle is to hell with it!";
			link.l1.go = "Spanch_Bob_14";
		break;

		case "Spanch_Bob_14":
			dialog.text = "Uh, no " + GetSexPhrase("brother","sister") +"! The real watchman always plays fair, remember! Here's a riddle for you. ...(Recorded in the Ship's Log)\n When you solve it, tell me the answer. If correct, I tell you the key phrase, if not... Well, no, and no trial. And don't forget 500 gold! Without them I won't say the key phrase.";
			link.l1 = "...(quietly)... I won't forget, you damn scoundrel!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorGuadeloupeShoreGetTask");
			NextDiag.TempNode = "Spanch_Bob_15";
		break;

		case "Spanch_Bob_15":
			dialog.text = "Did you bring money?";

			if(sti(PChar.money) >= 500)
			{
				link.l1 = "Here are your piastres, you rascal.";
				link.l1.go = "Spanch_Bob_16";
			}

			link.l2 = "I don't have them right now. I'll bring it later.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Spanch_Bob_15";
		break;

		case "Spanch_Bob_16":
			AddMoneyToCharacter(PChar, -500);
			dialog.text = "That's another conversation! So, Captain, what are your guesses about the riddle? Just tell me the place and I'll give you the key phrase.";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Spanch_Bob_17";
		break;

		case "Spanch_Bob_17":
			string sString = GetStrSmallRegister(dialogEditStrings[1]);
			if(sString == "gulf of doom")
			{
				dialog.text = "Bingo! The key phrase is 'The Elusive Squadron has lost its flagship.'";
				Link.l1 = "Goodbye!";
				Link.l1.go = "exit";
				AddDialogExitQuestFunction("DozorToDeadShoreInMein");
			}
			else
			{
				dialog.text = "No, Captain, you're wrong. Try again.";
				link.l1 = "Damn it!";
				link.l1.go = "exit";
				NextDiag.TempNode = "Spanch_Bob_18";
			}
		break;

		case "Spanch_Bob_18":
			NextDiag.TempNode = "Spanch_Bob_18";
			dialog.text = "So, Captain, what are the guesses about the riddle? Just tell me the place and I'll give you the key phrase.";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Spanch_Bob_17";
		break;
		// СПАНЧ БОБ <--

		// КАПИТАН ФЛЕЙТА У МАРТИНИКИ -->
		case "Justin_Butt_1":
			dialog.text = "You won! Take the Meckachrome out of the chest, just leave me alone!";
			link.l1 = "Why did you attack me? Answer me!";
			link.l1.go = "Justin_Butt_2";
		break;

		case "Justin_Butt_2":
			dialog.text = "Isn't it clear, Captain?";
			link.l1 = "Is this part of the assignment? The point is that I have to take Mekakhrom by battle?";
			link.l1.go = "Justin_Butt_3";
		break;

		case "Justin_Butt_3":
			dialog.text = "What the hell kind of assignment is this? Don't you understand what's going on here?";
			link.l1 = "Yes, explain, you're finally getting it right!";
			link.l1.go = "Justin_Butt_4";
		break;

		case "Justin_Butt_4":
			dialog.text = "You and I are rivals, do you understand?";
			link.l1 = "Rivals?";
			link.l1.go = "Justin_Butt_5";
		break;

		case "Justin_Butt_5":
			dialog.text = "Yes! It's obvious from your face that this is the first time you've heard about it. Well, since you've won, in a fair fight, I'll tell you. You see, you aren't alone in this game, besides you and me, there are three other captains who play the Watch.\nThe old man who had organized the game had offered to play the game to all the captains who had anchored in Sharp Town while he was there. And five of them agreed.";
			link.l1 = "And you were among the others who agreed?";
			link.l1.go = "Justin_Butt_6";
		break;

		case "Justin_Butt_6":
			dialog.text = "That's right. But, old man, I didn't say that besides me, someone else would play. But I followed him and found out for myself, after which I killed him, and began to hunt for the rest of the captains.";
			link.l1 = "And what happened to them?";
			link.l1.go = "Justin_Butt_7";
		break;

		case "Justin_Butt_7":
			dialog.text = "I've eliminated every competitor except you. I sank one ship as soon as it left Bermuda, the second caught up with Puerto Rico, the third destroyed near Curaçao. Except you were the problem. I knew you were ahead of me, but I couldn't figure out how long I was losing to you.\n Untill Main, I was able to find that I was inferior to you only a couple of days. I quickly solved the puzzle and rushed on all sails to Martinique.";
			link.l1 = "So there are several players? It turns out that there should be several Mecachromes?";
			link.l1.go = "Justin_Butt_8";
		break;

		case "Justin_Butt_8":
			dialog.text = "Yes, each agent had ten Mecachromes. They had to give a Mekachrome to anyone who would tell them the key phrase.";
			link.l1 = "What about Turks? I found there only one Mekakhrom - the bandits who apparently killed the agent.";
			link.l1.go = "Justin_Butt_9";
		break;

		case "Justin_Butt_9":
			dialog.text = "I don't know what I don't know. I gave in to you then, came to Turks after you and found several corpses. One of them, apparently, was an agent, and the other two looked like bandits, whom, as I understand it now, he had failed you. I found the Mecachromes intended for us hidden in a cave.";
			link.l1 = "And Main? How did you know that I was two days ahead of you?";
			link.l1.go = "Justin_Butt_10";
		break;

		case "Justin_Butt_10":
			dialog.text = "There was an agent on Main, too, only he had another mission. By the logic of the game, the watchmen had to find Meckachrome in a chest, on a broken ship. I also found him there, but I knew that, because there are other players and should be other Meckachrome.\nI searched the area and found an agent. He told me he had to watch over us and plant the Mekachromes every time another lookout took him.";
			link.l1 = "That is, after I found Mekakhrom, did he put a new one in, for you to find?";
			link.l1.go = "Justin_Butt_11";
		break;

		case "Justin_Butt_11":
			dialog.text = "That's right, and after I took the second Mekakhrom, he put the third one, but since there was no one left thanks to me, both Mekakhrom and the agent were useless.";
			link.l1 = "Did you kill him?";
			link.l1.go = "Justin_Butt_12";
		break;

		case "Justin_Butt_12":
			dialog.text = "Yes, and why keep him alive? Only the agents on Tortuga and Curaçao survived. They were difficult to remove unnoticed. The fisherman from the beach Fahardo I killed, drunkard from Cape Inaccessible too. You already know about the agent from the gulf of Doom - he suffered the same fate. The agent from Lamantena turned out to be the most distrustful. I don't know how he figured me out, but he had to be chased.";
			link.l1 = "You know, I have no plans to let you live after what you've done. Defend yourself!";
			link.l1.go = "Justin_Butt_13";
		break;

		case "Justin_Butt_13":
			TakeNItems(PChar, "Dozor_Mekakhrom", -1);
			dialog.text = "And you thought, that I'm going to let you just walk away like that? The hell with it!";
			link.l1 = "Well, try it, you bastard!";
			link.l1.go = "exit";

			PChar.Dozor.CabinID = PChar.location;
			Locations[FindLocation(PChar.location)].box1.items.Dozor_Key = 1;
			Locations[FindLocation(PChar.location)].box1.items.Dozor_Mekakhrom = 1;

			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam");
		break;
		// КАПИТАН ФЛЕЙТА У МАРТИНИКИ <--

		// НЕЗНАКОМЕЦ В ДОМЕ -->
		case "NoName_1":
			dialog.text = "You're the first, who got to the treasure, watchman. Congratulations!";
			link.l1 = "Who are you?";
			link.l1.go = "NoName_2";
		break;

		case "NoName_2":
			dialog.text = "I'm from Fabian Gronholm, the organizer of this game, do you remember him?";
			link.l1 = "I remember it very well. Do you know that Fabian was murdered?";
			link.l1.go = "NoName_3";
		break;

		case "NoName_3":
			dialog.text = "Is that so?";
			link.l1 = "We crossed paths with a captain at Martinique. He told me that he killed Gronholm, all the other patrollers, as well as some agents. He wanted to kill me too, but it didn't work out.";
			link.l1.go = "NoName_4";
		break;

		case "NoName_4":
			dialog.text = "It's a pity, Fabian was a great person, energetic, brave, enterprising.";
			link.l1 = "Is it okay that he didn't tell any of us playing his game that there would be rivals?";
			link.l1.go = "NoName_5";
		break;

		case "NoName_5":
			dialog.text = "He didn't want to push you heads together, because he knew that you would strive not to solve puzzles, but to cut each other's throats.";
			link.l1 = "I definitely wouldn't have gone for it... It's sad.";
			link.l1.go = "NoName_6";
		break;

		case "NoName_6":
			dialog.text = "But Captain Justin Butt, as you can see, did it with pleasure with all of you. To be honest, I'm glad you managed to finish him off-I don't like that kind of people.";
			link.l1 = "And what is your role in the game? Are you an agent too?";
			link.l1.go = "NoName_7";
		break;

		case "NoName_7":
			dialog.text = "You could say that. Actually, I'm Fabian's associate, his right-hand man. I had to keep track of the order of your arrival here, thank you for playing, put a new treasure in the chest and close it.";
			link.l1 = "So those who are supposed to arrive here after me would also receive the treasure?";
			link.l1.go = "NoName_8";
		break;

		case "NoName_8":
			dialog.text = "Exactly. The first is the richest treasure - 3 valuable items and 100,000 gold, which will more than cover your expenses. The second arrival was entitled to a treasure that contains 1 valuable item and will cover the costs of the game.\nThe third we returned the payment for the game, and the others had to leave with nothing. But since no one else is coming, my task is done.";
			link.l1 = "Have such games been held before? Did one of my agents mention something about this?";
			link.l1.go = "NoName_9";
		break;

		case "NoName_9":
			dialog.text = "Yes, there were such games, Fabian has already managed to hold 3 such events..";
			link.l1 = "It's strange, but before Fabian asked me to play, I had never heard about the Watch.";
			link.l1.go = "NoName_10";
		break;

		case "NoName_10":
			dialog.text = "And you could hardly have heard. By the end of the game, as a rule, only one captain survived. I'm telling you, they're trying to destroy each other-they don't know how to play fair. That's why you didn't know, or rather shouldn't have known, about each other's existence. As you can see, it didn't work out again - only you stayed alive .";
			link.l1 = "And what will happen to the game now. If Fabian was killed, then the games will no longer be held?";
			link.l1.go = "NoName_11";
		break;

		case "NoName_11":
			dialog.text = "I could have been the organizer, but... What stops me is that too many people have already died because of this game. Therefore, the project is likely to be closed.";
			link.l1 = "I think this is the right decision.";
			link.l1.go = "NoName_12";
		break;

		case "NoName_12":
			dialog.text = "I'm glad you agreed with me. Thanks for playing. Good luck to you!";
			link.l1 = "Have a nice stay.";
			link.l1.go = "exit";
			UnlockAchievement("AchDozor", 3);
			AddDialogExitQuestFunction("DozorHappyEnd");
		break;
		// <-- НЕЗНАКОМЕЦ В ДОМЕ


		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
