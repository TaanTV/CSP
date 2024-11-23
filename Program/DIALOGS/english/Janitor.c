
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
		case "First":
			dialog.text = RandPhraseSimple("They walk around here, trample all sorts, and then I clean up...", "And what did you bring"+GetSexPhrase("here? The residence needs cleaning, and he carries dirt everywhere here.", "come here? The residence needs cleaning, and she's dragging mud around here."));
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
