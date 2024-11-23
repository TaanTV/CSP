
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
			if(CheckAttribute(PChar, "Arena.Mode"))
			{
				if(PChar.Arena.Mode == "Duel")
				{
					if(sti(PChar.Arena.Duel.BiletCount) == 1)
					{
						dialog.text = "Ah, it's you, captain " + GetFullName(pchar) + "? Come on in!";
						link.l1 = "...";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaDuelEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}

				if(PChar.Arena.Mode == "Etaps")
				{
					if(sti(PChar.Arena.Etaps.BiletCount) == 1)
					{
						dialog.text = "Ah, it's you, captain " + GetFullName(pchar) + "? Have you decided to fight with all kinds of evil spirits?";
						link.l1 = "Yeah... Come on, skip it.";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaEtapsEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}

				if(PChar.Arena.Mode == "Tournament")
				{
					if(sti(PChar.Arena.Tournament.BiletCount) == 1)
					{
						dialog.text = "Ah, it's you, captain " + GetFullName(pchar) + "? All the participants of the tournament are already assembled! The fights are expected to be very violent. Good luck to you, Captain...";
						link.l1 = "Thank you...";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaTournamentEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}

				if(PChar.Arena.Mode == "Odds")
				{
					if(sti(PChar.Arena.Odds.BiletCount) == 1)
					{
						dialog.text = "Ah, it's you, captain " + GetFullName(pchar) + "? I heard you made a bet and decided to try your luck by betting on one of the duelists? I wish you good luck!";
						link.l1 = "Thank you...";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaOddsEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}

				if(PChar.Arena.Mode.NotOdd == true)
				{
					dialog.text = "Stop! Who are you? Show me the ticket, otherwise I'll call the guards!";

					if(GetCharacterItem(PChar, "ArenaBilet"))
					{
						link.l1 = "Here is my ticket. Now open up!";
						link.l1.go = "Bilet_Action";
					}
					link.l2 = "Uh-uh... I'll come back later.";
					link.l2.go = "exit";
					AddDialogExitQuestFunction("PrepareArenaOddsBilet");
				}
			}

			NextDiag.TempNode = "First time";
		break;

		case "Bilet_Action":
			TakeItemFromCharacter(PChar, "ArenaBilet");
			dialog.text = "Uh.. Well, well.. Now you can go through.";
			link.l1 = "That's better.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PrepareArenaOddsEnd");
			NextDiag.TempNode = "Second Time";
		break;


		case "Second Time":
			dialog.text = "Would you like to buy elixirs and food? They will be very useful in battle!";
			link.l1 = "Yes.";
			link.l1.go = "Trade_exit";
			link.l2 = "No.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Second Time";
		break;

		case "Trade_exit":
            		if(CheckNPCQuestDate(NPChar, "Item_date"))
			{
				SetNPCQuestDate(NPChar, "Item_date");
				ArenaBileterGiveItems(NPChar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;


		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "":
			dialog.text = NPCStringReactionRepeat("",
				"",
				"",
                "", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("",
				"",
                "",
				"", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_1";
		break;
		case "_1":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_2";
		break;
		case "_2":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_3";
		break;
		case "_4":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_5";
		break;
	}
}
