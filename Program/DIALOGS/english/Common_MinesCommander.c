void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar = GetMainCharacter();
	string sName = PChar.name + " " + PChar.lastname;

	int iBricks = sti(PChar.BuildingColony.Blocks);
	int iPlanks = sti(PChar.BuildingColony.Planks);
	int iMahogany = sti(PChar.BuildingColony.Mahogany);
	int iEbony = sti(PChar.BuildingColony.Ebony);
	int iSlaves = sti(PChar.BuildingColony.Slaves);
	int iFood = sti(PChar.BuildingColony.Food);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What can I do for you, captain " + sName + "?";
			if(PChar.ColonyBuilding.Stage != "2" && PChar.ColonyBuilding.Action != true)
			{
				link.l1 = "Perhaps I am interested in your services.";
				link.l1.go = "Building";
			}
			link.l2 = "Just came to see you.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Hi1":
			dialog.text = "Greetings, Captain! Do you need my services?";
			link.l1 = "Hello. In what services?";
			link.l1.go = "Hi";
			NextDiag.TempNode = "First time";
		break;

		case "Hi":
			dialog.text = "Ah, you probably don't know. I am a well-known architect in this archipelago. I can start building a colony on one of the uninhabited islands. I have a lot of experience behind me, believe me.";
			link.l1 = "Is that so? Interesting enough.";
			link.l1.go = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
