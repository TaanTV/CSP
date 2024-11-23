// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now.");
		    link.l1.go = "exit";
			// Квест Изабеллы, розыск кэпа брига "wounds"
			if (CheckAttribute(pchar, "RomanticQuest.ShipToCumana"))
			{
                dialog.Text = "I'm listening to you.";
    			link.l1 = "Did the ship 'Five Wounds of Christ' enter the port?";
    			Link.l1.go = "RomanticQuest_1";
			}
		break;
		// ==> Квест Изабеллы, розыск кэпа брига "wounds"
		case "RomanticQuest_1":
			dialog.Text = "Yes, sir, it did. They got caught in a storm, lost the mainmast, they had to come back here.";
			link.l1 = "Where can I find captain?";
			Link.l1.go = "RomanticQuest_2";
		break;
		case "RomanticQuest_2":
			dialog.Text = "It seemed to me that he went to the tavern quite recently.";
			link.l1 = "Thank you.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "RomanticQuest.ShipToCumana");
			Pchar.RomanticQuest.ShipToCumanaTavenrn = true;
			ref rChar = GetCharacter(NPC_GenerateCharacter("BrigCaptain", "shipowner_13", "man", "man", 20, SPAIN, -1, false));
            rChar.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
            FreeSitLocator("Cumana_tavern", "sit3");  // очистим стул
			ChangeCharacterAddressGroup(rChar, "Cumana_tavern", "sit", "sit3");
            LAi_SetSitType(rChar);
		break;
		// <== Квест Изабеллы, розыск кэпа брига "wounds"
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Am I working for a secret agent network for "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "All right... Bye then.";
			link.l1.go = "exit";
			link.l2 = "Then another question";
			link.l2.go = "new question";
		break;

		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "What do I tell you? I don't know. I don't know anything.";

            link.l1 = "What a fool! Bye.";
			link.l1.go = "exit";
			link.l2 = "Then another question";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
