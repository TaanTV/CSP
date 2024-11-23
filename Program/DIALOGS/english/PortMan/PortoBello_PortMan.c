// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Listen, if you're not on port business, then don't bother me with questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yeah, really for the third time...", "Sorry, but I'm not interested in port affairs right now.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "Good afternoon. I would like to know where Captain Francois Gontier went on his corvette. I have an important assignment for him.";
                link.l1.go = "Portobello_ratP_1";
            }
		break;

		case "Portobello_ratP_1":
			dialog.text = "An important matter, you say? Well, if that's the case, let's see... Francois Gontier, corvette '" + pchar.questTemp.Slavetrader.ShipName + "'... According to the records, Senor Gontiere went to Jamaica.";
			link.l1 = "Thank you! You've helped me a lot!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


