string sNationNameglobal;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog, "Links");

	ref arItem;

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string attrLoc, QuestName, sTemp;
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		case "First Time":
			dialog.text = "Hello, you are " + GetFullName(pchar) + ", right?";
			link.l1 = "Yes, you are right. What exactly happened?";
			link.l1.go = "Invite";
		break;
		case "Invite":
			string sNationName = GetNationNameByType(sti(npchar.nation));
			sNationNameglobal = GetNationNameByType(sti(npchar.nation));
			dialog.text = "Your deeds to the Crown of " + XI_ConvertString(sNationName+"Dat") + " have not gone unnoticed. The Governor-General himself invites you to pay your respects.\nYou are not limited in the time of arrival.";
			link.l1 = "Wonderful! I will definitely visit him if possible. Goodbye, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			sld = CharacterFromID(NationShortName(sti(npchar.nation))+"_guber");
			sld.dialog.CurrentNode = "GivePatent";
			chrDisableReloadToLocation = false;
			pchar.(sNationName).quest.mayor.done = true;
		break;
	}
}