
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sName = GetFullName(PChar);
	string sCharacter = "";

	int iShip = 0;
	int iCrew = 0;
	int iShipSP = 0;
	int iShipHP = 0;

	string sShipName = "";

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Thank you again for the service.";
			link.l1 = "Don't mention it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "Thank you, Lord!!!";
			link.l1 = "My name is " + GetFullName(PChar) + "! I am captain of the ship '" + PChar.Ship.Name + "'. What happened to you?";
			link.l1.go = "2";
		break;

		case "2":
			dialog.text = "I am captain " + GetFullName(NPChar) + ". We were caught in a storm a week ago.";
			link.l1 = "Damn you -it must have been a tornado!";
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = "It was the most terrible and violent storm I have ever seen in this archipelago. And I've seen a lot, believe me. For three days we were rocked in this mess, and at the end of the fourth day, when the storm had already subsided, two masts cracked at once. The sailors did not even have time to capture them - everything was instantly washed overboard. When this horror ended, my XO missed more than half of our team! We have been drifting in these waters for several days. You are the first who we met.";
			link.l1 = "I sincerely sympathize with you! If there's anything I can do to help...";
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = "You see, Captain. We could sail with you-I think there would be enough room on your ship. But the fact is that there is a cargo in the hold of my ship that I have to deliver to its destination. I don't want to bother you too much, but I'm only asking you to take my man and drop him off at the nearest colony...";
			link.l1 = "Of course.";
			link.l1.go = "YesYes";
			link.l2 = "Sorry, but I can't help you...";
			link.l2.go = "NotNot";
		break;

		case "YesYes":
			ShipWreckInSeaWait();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NotNot":
			ShipWreckInSeaCancel();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "5":
			sCharacter = PChar.GenerateShipWreck.CharacterID;
			SetCameraDialogMode(CharacterFromID(sCharacter));
			dialog.text = GetFullName(CharacterFromID(sCharacter)) + ": " + npchar.name + ", you will open this package upon arrival on earth. But not before. There are additional instructions.";
			link.l1 = GetFullName(NPChar) + ": Understood, Captain.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckInSeaWaitEnd");
		break;

		case "6":
			dialog.text = "Have you been a captain for a long time?";
			link.l1 = "Oh, it's a long time ago.";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "Then you understand what I'm experiencing right now. For fifteen years I sailed on this ship, and in just three days it turned into a ragged tub. There is not the slightest chance to repair it. When the ship arrives for us, I will have to scuttle my ship. I won't survive this...";
			link.l1 = "Hold on, " + GetAddress_FormToNPC(NPChar) + ". Things happen much worse in life.";
			link.l1.go = "8";
		break;

		case "8":
			dialog.text = "Well, enough of the lyrics. Upon arrival at the destination, my person will give you " + sti(PChar.GenerateShipWreck.Money) + " gold. That's all I can do to reward you for your help.";
			link.l1 = "Really, it wasn't worth it!";
			link.l1.go = "9";
		break;

		case "9":
			dialog.text = "Hit the road. Good luck, " + GetFullName(PChar) + "!";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckInSeaWaitEndToSea");
		break;

		case "10":
			dialog.text = "Ah, Captain. Thanks again for taking us on board.";
			link.l1 = "Don't mention it.";
			link.l1.go = "11";
		break;

		case "11":
			dialog.text = "May I ask where we are going?";
			link.l1 = "I can't... Damn, I can't!!!";
			link.l1.go = "12";
			link.l2 = "I have a case for you. I'm know that there is some valuable cargo in the hold of your ship...";
			link.l2.go = "14";
		break;

		case "12":
			dialog.text = "Are you okay? Has something happened?";
			link.l1 = "My navigator will notify you about our course. Lunch will be at noon. You will be called.";
			link.l1.go = "exit";
			NextDiag.TempNode = "13";
		break;

		case "13":
			dialog.text = "Ah, Captain. Thanks again for taking us on board.";
			link.l1 = "Don't mention it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "13";
		break;

		case "14":
			dialog.text = "What are you implying?!";
			link.l1 = "I would like to find out what kind of cargo it is. And you will help me with this. Either...";
			link.l1.go = "15";
		break;

		case "15":
			dialog.text = "Either?";
			link.l1 = "Either you die, right here and now.";
			link.l1.go = "16";
		break;

		case "16":
			dialog.text = "Two-faced brute! Defend yourself, carrion!";
			link.l1 = "Eh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBattleWithSailor");
		break;

		case "17":
			dialog.text = "Asshole! What do you need?";
			link.l1 = "Just your gold, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(NPChar) + ".";
			link.l1.go = "18";
		break;

		case "18":
			dialog.text = "Take it away. And get the hell out!";
			link.l1 = "I will also take your life, because you know that the dead are silent?";
			link.l1.go = "19";
		break;

		case "19":
			dialog.text = "What a snake I treated on my ship!";
			link.l1 = "...";
			link.l1.go = "exit";
			PChar.GenerateShipWreck.State = "none";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam");
		break;

		case "20":
			dialog.text = "Here we are. Thank you, Captain, I'll do the rest.";
			link.l1 = "Well. Good luck to you.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckInTownSuccess");
		break;

		case "21":
			dialog.text = "Who are you?";
			link.l1 = "I have exactly the same question.";
			link.l1.go = "22";
		break;

		case "22":
			dialog.text = "I don't like to wait.";
			link.l1 = "Chill. I am captain " + GetFullName(PChar) + ".";
			link.l1.go = "23";
		break;

		case "23":
			dialog.text = "And what do you need on board this ship?";
			link.l1 = "I don't like waiting either. Sometimes I get very annoyed, so I can make the wrong decision for you.";
			link.l1.go = "24";
		break;

		case "24":
			dialog.text = "Anchor down my throat. I am the navigator of this ship - " + GetFullName(NPChar) + ". So what do you need here?";
			link.l1 = "I want to talk to captain.";
			link.l1.go = "25";
		break;

		case "25":
			dialog.text = "The captain is ill. During the storm, he was attacked by a fever attack. I'm filling in for him now.";
			link.l1 = "Really? And what is that blood on the deck?";
			link.l1.go = "26";
		break;

		case "26":
			dialog.text = "Ask our cook. He likes to cut fish right on the deck, he breathes fresh air.";
			link.l1 = "Understood. Well, gentlemen, I dare not detain you. Have a nice swim.";
			link.l1.go = "27";
			link.l2 = "Listen to me, you pathetic ragamuffins...";
			link.l2.go = "36";
			link.l3 = "Do you think I'm stupid?";
			link.l3.go = "45";
			link.l4 = "I'm not a marine patrol, but I hate traitors. Therefore, it is better for you to die - I will personally order the living to be hung from that mast over there. To arms, you scoundrels!";
			link.l4.go = "41";
		break;

		case "27":
			dialog.text = "Wait. As you can see, our ship was caught in a storm. Solid canvas and a stack of planks wouldn't hurt us. What do you say?";

			if(GetCargoGoods(PChar, GOOD_PLANKS) > 0 || GetCargoGoods(PChar, GOOD_SAILCLOTH) > 0)
			{
				link.l1 = "Free - only in paradise.";
				link.l1.go = "28";
			}

			link.l2 = "I've already told you - bye.";
			link.l2.go = "35";
		break;

		case "28":
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			SetCameraDialogMode(CharacterFromID(sCharacter));
			dialog.text = "" + characters[GetCharacterIndex(sCharacter)].name + ", run to captain, borrow his wallet.";
			link.l1 = "...";
			link.l1.go = "29";
			ShipWreckBandValodyaToMoney();
		break;

		case "29":
			SetCameraDialogMode(NPChar);
			dialog.text = "Do you want an exchange for goods? We have a cargo of well-paid goods in the hold.";
			link.l1 = "I prefer hard currency.";
			link.l1.go = "30";
		break;

		case "30":
			dialog.text = "Hehe.";
			link.l1 = "...";
			link.l1.go = "31";
		break;

		case "31":
			ShipWreckBandValodyaReturnWithMoney();
			dialog.text = "Gold is so gold. How much can you transfer?";
			link.l1 = "Let's see.";
			link.l1.go = "32";
		break;

		case "32":
			PChar.GenerateShipWreck.GoodsChange = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchQuicklyTrade();
		break;

		case "33":
			dialog.text = "Did ypu finish?";
			link.l1 = "Quite. The cargo will be delivered by boats. And, navigator, I would advise you to change your rank on the ship, and prepare the cook in the galley. His Majesty's Naval Patrol may not understand.";
			link.l1.go = "34";
		break;

		case "34":
			PChar.GenerateShipWreck.GoodsChange.Yes = true;
			dialog.text = "Haha.";
			link.l1 = "Have a nice swim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;

		case "35":
			PChar.GenerateShipWreck.GoodsChange.Yes = false;
			ShipWreckBanditsOneTypeEnd();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "36":
			dialog.text = "How are you talking to me, dog?";
			link.l1 = "I can still distinguish human blood. You have not been caught in any storm. I don't know which one of you was chopping masts and ripping sails. He also set fire to these barrels of gunpowder, but he was clearly out of his mind. You will tell the naval patrol that your captain is ill, who will board you and hang you like rioters on that single mast over there. So, you vile rats, do you want to live?";
			link.l1.go = "37";
		break;

		case "37":
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			dialog.text = "For such words, I will personally open your stomach.";

			if(sti(PChar.GenerateShipWreck.ToSquadron) == 1)
			{
				SetCameraDialogMode(CharacterFromID(sCharacter));
				link.l1 = GetFullName(CharacterFromID(sCharacter)) + ": Chill, " + npchar.name + ". He has more people and a whole ship.";
				link.l1.go = "38";
			}
			else
			{
				link.l1 = "Well, try it, fucker!";
				link.l1.go = "41";
			}
		break;

		case "38":
			SetCameraDialogMode(NPChar);
			dialog.text = RandSwear();
			link.l1 = "I forgive you for the first time, you piece of shit. But if I hear anything like this in the future, I'll throw it to the sharks.";
			link.l1.go = "39";
		break;

		case "39":
			dialog.text = "What do you need?";
			link.l1 = "Do you want to swim under me?";
			link.l1.go = "40";
		break;

		case "40":
			dialog.text = "Damn it, of course! I've heard about you.";
			link.l1 = "I have two conditions. First, you will pay a fee for joining under my supervision. And secondly, you will finish off all the prisoners from the old team.";
			link.l1.go = "42";
			link.l2 = "You have to finish off all the prisoners from the old team.";
			link.l2.go = "43";
			link.l3 = "Ha-ha, I was joking. Have a nice swim!";
			link.l3.go = "35";
		break;

		case "41":
			ShipWreckBanditsStartBattle();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "42":
			if(sti(PChar.GenerateShipWreck.ToSquadronWithMoney) == 1)
			{
				sCharacter = PChar.GenerateShipWreck.ValodyaID;
				PChar.GenerateShipWreck.ValodyaToMoney = true;
				SetCameraDialogMode(CharacterFromID(sCharacter));
				dialog.text = "We agree. " + characters[GetCharacterIndex(sCharacter)].name + ", you know what to do.";
				link.l1 = "I understand.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ShipWreckBandValodyaToMoney");
			}
			else
			{
				dialog.text = "But we don't have any money.";
				link.l1 = "In that case, roll away. Have a nice day.";
				link.l1.go = "35";
				link.l2 = "Then prepare to die, dogs!";
				link.l2.go = "41";
				link.l3 = "So be it - I'll take you.";
				link.l3.go = "43";
			}
		break;

		case "43":
			PChar.GenerateShipWreck.AddBandaShip = true;
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			dialog.text = "We agree. " + characters[GetCharacterIndex(sCharacter)].name + ", you know what to do.";
			link.l1 = "That's great. Now get to work!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;

		case "44":
			PChar.GenerateShipWreck.AddBandaShip = true;
			AddMoneyToCharacter(PChar, sti(PChar.GenerateShipWreck.Money));
			dialog.text = "Captain, here's the money. Here exactly " + sti(PChar.GenerateShipWreck.Money) + " piastres.";
			link.l1 = "Consider yourself on my team. And now to clean up this tub! AND, NOW!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;

		case "45":
			dialog.text = "What are you talking about?";
			link.l1 = "Do you see that ship over there? So, before you know it, he'll sweep all the asses off this boat if something happens to me. Now listen up, you piece of shit. You are a rebel and by law you will be strung up on that mast over there. And the whole team will be hanged. So, to save your pathetic souls, you will pay me. If I don't see this money in five minutes, then you can pray to God in absentia for mercy. But you guys are clearly not going to heaven. Time has passed.";
			link.l1.go = "46";
		break;

		case "46":
			dialog.text = "You forgot that you are here and not in the cabin of your ship. I'll easily run you through.";
			link.l1 = "I am one of the best swordsmen in this archipelago. And I have a boarding party of seasoned fighters with me. You won't have time to pull out a rusty broadsword, as your head will roll around the deck. Got it?";
			link.l1.go = "48";
		break;

		case "47":
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			dialog.text = "For such words, I will personally open your stomach.";

			if(sti(PChar.GenerateShipWreck.ToSquadronWithMoney) == 1)
			{
				SetCameraDialogMode(CharacterFromID(sCharacter));
				link.l1 = GetFullName(CharacterFromID(sCharacter)) + ": Here's the money, " + npchar.name + ", we have no way out.";
				link.l1.go = "49";
			}
			else
			{
				link.l1 = "Well, try it, fucker!";
				link.l1.go = "41";
			}
		break;

		case "48":
			dialog.text = "...";
			link.l1 = "Three minutes have passed. I'm waiting.";
			link.l1.go = "47";
		break;

		case "49":
			AddQuestRecord("ShipWreck", "8");
			AddMoneyToCharacter(PChar, sti(PChar.GenerateShipWreck.Money));
			SetCameraDialogMode(NPChar);
			dialog.text = "...";
			link.l1 = "I'm glad you saved your skins. I advise you to change this loser, he doesn't look much like a captain. Goodbye. And pray to God if I see you again.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;

		case "NewCap_1":
			dialog.text = "You saved us!";
			link.l1 = "What happened here?";
			link.l1.go = "NewCap_2";
		break;

		case "NewCap_2":
			dialog.text = "My name is " + GetFullName(NPChar) + " - I am the real captain of the ship. About a month ago, I was boarded by a pirate ship. I wouldn't be talking to you right now if the military patrol hadn't arrived in time. We somehow fought back, and the enemy ship sailed away with all sails. The patrol failed to catch up with him. I am a merchant, constantly moving goods. I had to hire a new team at one of the ports. There are no more than thirty of the old members left... And now there are only " + sti(PChar.GenerateShipWreck.PrisonedCrew) + " men. A week ago, I realized that I had hired inveterate scoundrels. One night, having been drugged with rum, they knocked down the lock on the arsenal and armed themselves, began to smash the ship, simultaneously killing everyone they met. I don't know how it happened, but they cut down the masts themselves and blew up several barrels of gunpowder. It's good that the holes were small. When they sobered up, they drove us into this cabin. What happened next, you understand for yourself.";
			link.l1 = "Yes, your chances of living another day were zero.";
			link.l1.go = "NewCap_3";
		break;

		case "NewCap_3":
			dialog.text = "What's your name?";
			link.l1 = GetFullName(PChar) + ", captain of the ship '" + PChar.Ship.Name + "'.";
			link.l1.go = "NewCap_4";
		break;

		case "NewCap_4":
			AddMoneyToCharacter(PChar, sti(PChar.GenerateShipWreck.Money));
			dialog.text = PChar.name + ", I thank you for saving me. Take this gold, as a sign of great respect.";
			link.l1 = "I did it for noble reasons. Tell me, what are you going to do next?";
			link.l1.go = "NewCap_5";
		break;

		case "NewCap_5":
			if(sti(PChar.GenerateShipWreck.ToSquadron) == 1)
			{
				dialog.text = "I suggest you take my ship to the squadron. You have proved your honesty.";

				if(GetCompanionQuantity(PChar) < 5)
				{
					link.l1 = "Why not. With pleasure.";
					link.l1.go = "NewCap_6";
				}

				link.l2 = "Unfortunately, I cannot take you to my squadron. Good luck to you.";
				link.l2.go = "NewCap_7";
			}
			else
			{
				dialog.text = "It's not that far to the nearest colony - we'll swim by ourselves. Thank you again, Captain.";
				link.l1 = "Goodbye.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ShipWreckBanditsNewCapNoAdd");
			}
		break;

		case "NewCap_6":
			dialog.text = "Thank you, Captain. I hope we can work together.";
			link.l1 = "I have no doubt.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsNewCapAdd");
		break;

		case "NewCap_7":
			dialog.text = "So pity. Than we have to get it on our own.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsNewCapNoAdd");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
