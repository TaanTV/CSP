// BOAL новый диалог офицера и компаньона 21/06/06

void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;

	switch(Dialog.CurrentNode)
	{
        case "hired":

			dialog.text = "(A loyal friend is examining you carefully, waiting for an order)";
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
	            Link.l2 = "Listen to my order!";
	            Link.l2.go = "stay_follow";
            }
			Link.l4 = "It's time for us to split up, buddy. Go back to the ocean, to your people.";
			Link.l4.go = "AsYouWish";

            Link.l9 = "Nothing. At ease.";
            Link.l9.go = "exit";
			Diag.TempNode = "hired";
        break;

		case "exit":
			Diag.TempNode = "hired";
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "AsYouWish":
			dialog.text = "(The crab pathetically taps its claws on the ground.)";
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
	            Link.l2 = "I'm sorry, this is my final decision. All these sea adventures are too dangerous for you.";
	            Link.l2.go = "exit_fire";
			Link.l4 = "Sorry, I changed my mind. I don't know what came over me...";
			Link.l4.go = "exit";
			Diag.TempNode = "hired";
        break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();
		break;

        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "(The crab makes a clicking sound to show that it is listening to you attentively.)";
            Link.l1 = "Stay here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";

		break;

        // boal 05.09.03 offecer need to go to abordage -->
	      case "Boal_Stay":
             //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
             //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
              Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
              AddDialogExitQuestFunction("LandEnc_OfficerStay");
		      Diag.TempNode = "hired";
		      dialog.text = "(It is clear that he does not approve of your decision, but is not going to challenge the order.)";
		      Link.l1 = "At ease.";
		      Link.l1.go = "Exit";
		      Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	      break;

	      case "Boal_Follow":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		      Diag.TempNode = "hired";
		      dialog.text = "(The crab clicks its claws in agreement.)";
		      Link.l1 = "At ease.";
		      Link.l1.go = "Exit";
	      break;

		  case "Fired":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
			  Diag.TempNode = "Fired";
		      dialog.text = "(The crab clicks viciously after you.)";
		      Link.l1 = "Over time, you will understand why I did this.";
		      Link.l1.go = "Exit";
	      break;
        // boal 05.09.03 offecer need to go to abordage <--
		// <-- Самостоятельное плавание компаньона
	}
}
