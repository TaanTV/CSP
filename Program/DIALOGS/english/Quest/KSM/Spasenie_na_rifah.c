
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sBlade;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = "Captain, it's good that I met you! Can you help me?";
			link.l1 = "What's the matter?";
			link.l1.go = "1";
			UnmarkCharacter(npchar);
			
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "I was heading for Nevis, but a violent storm confused all my plans. Due to an error in navigation, we ended up near the Skeleton Reef and the ship landed firmly on the rocks. I was lucky to get to this colony in the only surviving lifeboat... I beg you, save the valuable cargo and my team!";
			link.l1 = "Skeleton Reef is not far from here... I don't remember... What kind of reward were you talking about?";
			link.l1.go = "2";
		break;

		case "2":
			dialog.text = "I will give you half of the cost of the goods, but you need to hurry. My people have two weeks' worth of supplies left at best.";
			link.l1 = "Hmm, so where exactly did you land your ship on the rocks?";
			link.l1.go = "3";
			link.l2 = "No, Captain, I have my own things to do. Get out of this without me.";
			link.l2.go = "2.5";
			DeleteAttribute(npchar, "talker");
			UnmarkCharacter(npchar);
		break;
		
		case "2.5":
			sld = CharacterFromID("KSM_Alloka")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "3":
			dialog.text = "Approximately southeast of the central rock in the shape of a high arch. It's hard to make mistakes.";
			link.l1 = "Deal, let's try to find your property.";
			link.l1.go = "Exit1";
		break;

		case "REEFS":
			dialog.text = "You did a great job, Captain. It's time to pay you back.";
			link.l1 = "What are you talking about? But what about your starving crew, the valuable cargo rotting in the hold?";
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = "Haven't you figured it out yet? How gullible you are. My ship really crashed on these rocks, and there was only one way to get a new one...";
			link.l1 = "Trap "+ GetSexPhrase("some gullible simpleton", "some naive sucker") +".";
			link.l1.go = "5";
		break;

		case "5":
			dialog.text = "That's right, Captain, and to my great joy, it turned out to be you. Goodbye...";
			link.l1 = "This is an ambush! To arms!";
			link.l1.go = "Exit2";
		break;

		case "Piers":
			dialog.text = "Captain, your sluggishness will cost you your life!";
			link.l1 = "Yes, I understand... To admit, I was not up to saving your people...";
			link.l1.go = "6";
		break;

		case "6":
			dialog.text = "My people? To hell with my people. You didn't fall into a trap, you didn't let your ship be captured! Oh, you'll pay for it!";
			link.l1 = "Damn schemer!";
			link.l1.go = "Exit3";
		break;
		
		
		case "Exit1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("KSM_Snr_EndloosTraider");
		break;

        case "Exit2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("KSM_Snr_EndloosTraiderKill");
		break;
	}
}
