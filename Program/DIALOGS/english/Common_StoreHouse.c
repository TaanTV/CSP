
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
			NextDiag.TempNode = "First time";
			dialog.text = LinkRandPhrase("Greetings! It's not easy to be a storekeeper...", "Oh, the boredom is mortal here!", "Oh, damn it, what would you do?");
			link.l1 = LinkRandPhrase("Of course!", "I understand...", "Yes, you have serious problems...");
			link.l1.go = "exit";
			link.l2 = "Hello, " + npchar.name + ". I'm going to take an interest in the affairs of the warehouse, and perhaps leave something for storage.";
			link.l2.go = "StoreHouse_Details";
			link.l3 = "And nothing will be lost from here, if I decide to leave something personal?";
			link.l3.go = "StoreHouse_Details2";

		break;

		case "StoreHouse_Details":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(STORE_HOUSE);
		break;

		case "StoreHouse_Details2":
			dialog.text = "I guarantee with my head that nothing of yours will disappear from here. You can leave anything you want here, "+GetSexPhrase("sir!", "madam!");
			link.l1 = "Just fine! Then, see you later.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
