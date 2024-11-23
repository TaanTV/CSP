
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

			if(PChar.Dozor == "0")
			{
				if(sti(PChar.rank) >= 1)
				{
					dialog.text = "Come closer, " + GetSexPhrase("son","daughter") +"! Closer, so that I can see your face. My eyesight has gone to hell by my old age. Yes, that's much better.";
					link.l1 = "You got my face, old man! I would go my own way, and not distract busy people from business.";
					link.l1.go = "1";
				}
				else
				{
					dialog.text = "You're still too stupid to communicate with me. Come back later...";
					link.l1 = "Stupid? Yes, I like you now!.. Eh, old man.";
					link.l1.go = "exit";
				}
				break;
			}

			dialog.text = "What do you need?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "Don't treat me like that, " + GetSexPhrase("son","daughter") +", because I want to give you something that others can't give you. Are you hinting?";
			link.l1 = "Sounds great. And what is this thing? Is it some useless trinket again?";
			link.l1.go = "2";
		break;

		case "2":
			dialog.text = "Don't jump to conclusions, I see the will to win on your face, there are sparkles of enthusiasm in your eyes, and your clothes betray you as an adventurer.";
			link.l1 = "Wait, wait. Look around you! Everywhere you look, everyone here is an adventurer, it's Bermudes!";
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = "No, no, they are all ordinary captains, some of whom are more successful, some less, it doesn't matter. They don't have what's in you, what's immediately obvious, what I noticed you for. Do you understand, " + GetSexPhrase("son","daughter") +"?";
			link.l1 = "Not really. And what is it?";
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = "Willingness to rush headlong into the fight for an insidious and undoubtedly dangerous opponent whose name is adventure!";
			link.l1 = "You see, friend, I'm not ready to risk my head for an adventure without profit, I'll tell you right away. So if your adventure doesn't promise me a hold of silver, or a bag of galleons, then our conversation can be over.";
			link.l1.go = "5";
		break;

		case "5":
			dialog.text = "... (smiles mysteriously)... Of course, you won't be left out, and if you have a bright head, and most importantly, you know how to use it, you can get rich pretty well, well, if you're smarter than you are in the whole archipelago, then you can grab a couple of valuable things. Just at the beginning, I'd like to tell you a story...(smacking his lips)..., listen to her, it will be useful for you.";
			link.l1 = "Well, let's hear it.";
			link.l1.go = "6";
		break;

		case "6":
			dialog.text = "My father once served as a cabin boy on a pirate brig, the Faylor. Young blood, hot head, strong hands, sharp eyes. And God did not deprive him of wit, except that he was painfully fussy, my dad, just like you. And if it weren't for his excessive fussiness, he would be captain in less than a couple of years, but otherwise, he stayed in the cabin for more than one year. And when I came to my senses, it was already too late, you can't turn back the time. So, remember, son, first of all, don't fuss. For vanity is the cause of failure...";
			link.l1 = "What are you saying, old man? Nowadays, if you don't make a fuss, you'll be left with your nose in a broken trough. Literally.";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "Wait for that, don't confuse promptness with fussiness. Promptness is success. Fussiness is a failure. Did you remember?";
			link.l1 = "Remembered. So what's with the adventure?";
			link.l1.go = "8";
		break;

		case "8":
			dialog.text = "Oh, it's young, it's green, again you're rushing an old man, and aren't you ashamed?";
			link.l1 = "And here, it's your fault, I'm busy, and you're walking around distracting me. Let's be quick.";
			link.l1.go = "9";
		break;

		case "9":
			dialog.text = "Good, good. So, are you listening? Listen carefully. I'm offering you an adventure, or to be more precise, a game. If you are a savvy person, not devoid of mind, and with logic in friendship, you have an adventure along the way. And if, stupid, yes stupid, then good riddance...";
			link.l1 = "I'm not a fool, if that's what you mean! Or do you think I could be the captain of a ship if I were stupid?";
			link.l1.go = "10";
		break;

		case "10":
			dialog.text = "If so, are you ready to join the game?";
			link.l1 = "Can I go into more detail? What kind of game is this?";
			link.l1.go = "11";
		break;

		case "11":
			dialog.text = "Everything is easier than a turnip! Or rather, in words it's simple, but in life, you see, everything is much more complicated. Hmph... Have you ever heard about a game called Watch, "+ GetSexPhrase("son","daughter") +"?";
			link.l1 = "Of course I heard!";
			link.l1.go = "12";
			link.l2 = "This is the first time I've heard it. Can I go into more detail? What kind of term is that?";
			link.l2.go = "13";
		break;

		case "12":
			dialog.text = "Great! Then you don't need to explain anything! Only in our game, unlike the real Watch, everything is simpler: eight tasks, without hints, danger levels and time limits. I repeat - enter the data into a special device that I will give you (mekachrome, it's called), get the key phrase, raise the sail, and to the next island, to the agent! You tell him the key phrase, and you get the next Mekahrom.";
			link.l1 = "What kind of Mekakhrom is this?";
			link.l1.go = "15";
		break;

		case "13":
			dialog.text = "In this game you have to complete eight tasks. Each task is a riddle, a puzzle that you have to solve, or, in professional terms, ";
			link.l1 = "For example?";
			link.l1.go = "14";
		break;

		case "14":
			dialog.text = "Well, I heard , probably, A and B were sitting on the pipe, And it fell, B was gone, who stayed on the pipe? The correct answer is And! It's the same type here. You are given a riddle. Solved it - enter the solution into a special device that I will give you (it's called a Mekachrome), get the key phrase, raise the sail, and to the next island, to the agent! You tell him the key phrase, and you get the next task.";
			link.l1 = "What kind of Mekakhrom is this?";
			link.l1.go = "15";
		break;

		case "15":
			dialog.text = "This is a keyword retrieval device.";
			link.l1 = "And how do I use this device?";
			link.l1.go = "16";
		break;

		case "16":
			dialog.text = "Eh, what is there to be able to do? Pour and drink, you'll figure it out if you took the riddles.";
			link.l1 = "Well, okay, let's say I figured out all eight riddles, and what's in the end? Didn't you mention something about valuable items?";
			link.l1.go = "17";
		break;

		case "17":
			dialog.text = "Well, if you reach the end of the game, you will have money, fame, and valuables, be sure! Well, do you agree?";
			link.l1 = "Probably agree. Only here's another question, which one...";
			link.l1.go = "18";
		break;

		case "18":
			dialog.text = "Uh, wait, "+ GetSexPhrase("nice man","kind lady") +", wait. I've been working on this game for 2 years, and I want to get paid for my work...";
			link.l1 = "Payment?! And how much do I owe you?";
			link.l1.go = "19";
		break;

		case "19":
			dialog.text = "Uh, you don't scream, so don't scream. What am I telling you? That I have been preparing this game for 2 years! I was looking for agents all over the archipelago, coming up with riddles, this and that.";
			link.l1 = "How much do you want?";
			link.l1.go = "20";
		break;

		case "20":
			dialog.text = "20,000 piastres.";
			link.l1 = "What?!";
			link.l1.go = "21";
		break;

		case "21":
			dialog.text = "...(grinning)... So you still didn't understand anything, "+ GetSexPhrase("son","daughter") +"?";
			link.l1 = "I understand that if I agree, then my hard-earned 20,000 will go down the drain!";
			link.l1.go = "22";
		break;

		case "22":
			dialog.text = ""+ GetSexPhrase("Son","Daughter") +" after completing this game, you will get such a rich treasure that you never dreamed of! And the glory of one of the most intelligent captains of the archipelago.";
			link.l1 = "And if I don't get to the end?";
			link.l1.go = "23";
		break;

		case "23":
			dialog.text = "Are you afraid?";
			link.l1 = "I'm not afraid of anything or anyone!";
			link.l1.go = "24";
		break;

		case "24":
			dialog.text = "Then go ahead! Towards adventure! That's why you came here. Isn't that right?!";
			link.l1 = "Yes, beyond that, only...";
			link.l1.go = "25";
		break;

		case "25":
			dialog.text = "It looks like I'm wasting my time. For the last time, I'm offering it to you. Yes or no?";

			NPChar.NeedMoney = 20000;
			if(sti(PChar.money) >= sti(NPChar.NeedMoney))
			{
				link.l1 = "Okay I agree.";
				link.l1.go = "26";
			}

			link.l2 = "I need time to collect this amount.";
			link.l2.go = "27";
			link.l3 = "Fuck you! Go and find yourself another sucker. I'm not buying this kind of divorce.";
			link.l3.go = "29";
		break;

		case "26":
	        AddMoneyToCharacter(pchar,-sti(NPChar.NeedMoney));
			dialog.text = "That's how it would be right away. Here you go, this is the first Mekachrome, it contains information about the first riddle. Good luck!";
			link.l1 = "And good luck to you. Goodbye.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorStart");
		break;

		case "27":
			dialog.text = "Hurry up, I won't wait long.";
			link.l1 = "As soon as I find it, I'll come straight to you. See you later, old man.";
			link.l1.go = "exit";
			NextDiag.TempNode = "28";
			AddDialogExitQuestFunction("DozorWait");
		break;

		case "28":
			dialog.text = "Found money?";
			NPChar.NeedMoney = 20000;
			if(sti(PChar.money) >= sti(NPChar.NeedMoney))
			{
				link.l1 = "All 20,000 are here.";
				link.l1.go = "26";
			}

			link.l2 = "Not yet, as soon as I find it, I'll come straight to you.";
			link.l2.go = "exit";

			link.l3 = "You know, I was thinking... Fuck you! Go and find yourself another sucker. I'm not buying this kind of divorce.";
			link.l3.go = "29";
			NextDiag.TempNode = "28";
		break;

		case "29":
			DozorCancel();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
