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
        dialog.text = "Who are you? Get out of here, I'm not in the mood to talk.";
        link.l1 = "Hush, hush, buddy, I've come to give you a letter from Luke the Actor.";
        link.l1.go = "GiveLetter1";
		Map_CreateFastWarriorTreasure();
		DeleteAttribute(Pchar, "Luke.SpawnMaks");
    break;
    case "GiveLetter1":
        dialog.text = "Yes? And where is it?";
        link.l1 = "Look at this.";
        NextDiag.CurrentNode = "Plata";
        AddDialogExitQuest("GiveLetter");
    break;
    case "Plata":
        dialog.text = "Well, that's right. Yes, I almost forgot, here's your money. Anyway, stay away from me.";
        link.l1 = "Thank you. I will gladly leave your company.";
        AddQuestRecord("Silence_Price", "2");
        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "a"));
        PlaySound("Interfaceotebook_01");
        link.l1.go = "exit";
        AddDialogExitQuest("Plata1");
		NextDiag.TempNode="Bye";
        Characters[GetCharacterIndex("Old Friend")].Dialog.CurrentNode = "SecondQuest_1";
		ChangeCharacterAddressGroup(CharacterFromID("Old Friend"), "none", "none", "none");
		Pchar.Quest.Luke = "1";

    break;
	case "Bye":
		dialog.text="Get lost, I'm not in the mood to talk.";
		link.l1="I didn't really want to.";
		link.l1.go="exit";
	break;
	case "Guardians":
		dialog.text = "What's going on here?! An enemy spy?! Take " + GetSexPhrase("him!","her!");
		link.l1 = "Well, try it...";
		link.l1.go = "exit";
		AddDialogExitQuest("FightGuardians");
		LAi_group_MoveCharacter(NPChar, "Maks1");
	break;
    }
}
