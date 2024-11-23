void ProcessDialogEvent()
{
	ref NPChar;
    ref Pchar = GetMainCharacter();
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FirstTime":
			dialog.text = "Hello. I'm working on behalf of the governor and I'm looking for an enemy spy in the city. Who are you?";
			link.l1 = "Hello. I don't live in this city, but I'm not a spy. We can go to the governor, he will confirm.";
			link.l1.go = "TryNotBeCut";
			if (CheckNationLicence(sti(npchar.nation)))
			{
				link.l1 = "I have " + GetRusNameNationLicence(sti(npchar.nation)) + ", so I am here legally. Please familiarize yourself...";
				link.l1.go = "LicenceOk";
			}
			if (pchar.sex == "Skeleton")	//Проверка на скелета
			{
				if	(GetCharacterEquipSuitID(pchar)== "suit_1")
				{
					link.l1 = "Hello. You won't believe it, but I'm a living dead man.";
					link.l1.go = "TryNotBeCut";
				}
				else
				{
					dialog.text = "A LIVING SKELETON? Did you get out of the trunk? Get back in there!";
					link.l1 = "No way! I'm going to feast on your blood now!";
					link.l1.go = "exit";
					AddDialogExitQuest("SeekerFight");
				}
			}
		break;
		case "TryNotBeCut":
			if(pchar.SpySeeker == "Enemy" && (10 + rand(50) + rand(50)) > sti(pchar.skill.sneak))
			{
				dialog.text = "It seems to me that you are deceiving me. But okay, let's go to the governor.";
				link.l1 = "I'm not going anywhere with you! Defend yourself!";
				link.l1.go = "exit";
				AddDialogExitQuest("SeekerFight");
			}
			else
			{
				dialog.text = "Okay, no need. I believe you. Good luck!";
				link.l1 = "That's nice. Good luck!";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				AddCharacterExpToSkill(pchar, "Sneak", 100);
				AddDialogExitQuest("SpySeekerGood");
				if (pchar.sex == "Skeleton")
				{
					dialog.text = "Haha, good joke! But I see that you are not a spy, so I won't bother you anymore.";
				}
			}
		break;
		case "LicenceOk":
			dialog.text = "Okay. I dare not detain you any longer."
			link.l1 = "Great, goodbye.";
			link.l1.go = "exit";
			AddDialogExitQuest("SpySeekerGood");
		break;
	}
}
