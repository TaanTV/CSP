void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;
    int i;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
    break;
    case "First Time":
        dialog.text = "Hush, "+GetSexPhrase("buddy.", "girlfriend.") + " You're looking for Luke, right? You don't have to answer. I'm waiting for you at midnight on the beach of Cape Isabela. One" + GetSexPhrase("wow.", "y.");
        link.l1 = "Ahem... Okay, I'll be there.";
        link.l1.go = "exit";
		AddDialogExitQuest("PirateGoOut");
		NextDiag.TempNode = "Isabella_1";
    break;
	case "Isabella_1":
		Pchar.quest.PirateComeToIsabellaLoose.over = "yes";
		dialog.text = "Ah, here you are. Well, come on, why do you need a Luke?";
		link.l1 = "And who are you to answer your questions?";
		link.l1.go = "PrepareFight";
		if (Pchar.Luke.Info == "Peace")
		{
			link.l2 = "Luke is an old friend of mine. I was fulfilling his request. When I came back, he was nowhere. It bothered me."
			link.l2.go = "PeaceDial";
		}
		DeleteAttribute(pchar, "Luke.Info");
	break;
	case "PrepareFight":
		dialog.text = "Do you even know who Luke is? He is an agent, and it is not a fact that one nation has. What do you say to that?";
		link.l1 = "Argkh! I couldn't even think! What are you doing with him?!";
		link.l1.go = "PrepareFight_1";
	break;
	case "PrepareFight_1":
		dialog.text = "This has absolutely nothing to do with you! All I need from you is your ship.";
		link.l1 = "I didn't hear wrong" + GetSexPhrase("what?!", "what?!") + " Do you want my ship?! Why do you need it?";
		link.l1.go = "PrepareFight_2";
	break;
	case "PrepareFight_2":
		dialog.text = "You know, I want to get even with Luke, but before " + XI_ConvertString("Colony" + Pchar.Luke.City + "Gen") + " you can't get there on foot. Defend yourself!";
		link.l1 = "Bastard, hold on!";
		link.l1.go = "exit";
		AddDialogExitQuest("PrepareFightAnri");
	break;
	case "PeaceDial":
		dialog.text = "Hmm... I see. So he deceived you too. What are you going to do?";
		link.l1 = "It would be nice to find him first, and then I'll figure out what to do.";
		link.l1.go = "PeaceDial_1";
	break;
	case "PeaceDial_1":
		dialog.text = "You know, I'll help you. I'll tell you where he is. I can't get it myself, I don't have a ship, and in the colonies of " + NationNameGenitive(sti(Colonies[FindColony(Pchar.Luke.City)].nation)) + " my way is ordered.";
		link.l1 = "Okay, I agree" + GetSexPhrase("en.", "on.") + "Tell me everything you know.";
		link.l1.go = "PeaceDial_2";
	break;
	case "PeaceDial_2":
		dialog.text = "He is currently in " + XI_ConvertString("Colony" + Pchar.Luke.City + "Gen") + " port. Most likely he is hiding somewhere, look more carefully and be careful, he is very cunning.";
		link.l1 = "";
		link.l1.go = "PeaceDial_3";
	break;
	case "PeaceDial_3":
		dialog.text = "Good luck to you, and take these books. They will help to anticipate his tricks. Goodbye.";
		link.l1 = "Thank you. Goodbye.";
		link.l1.go = "exit";
		AddDialogExitQuest("PirateGoOut1");
	break;
    }
}
