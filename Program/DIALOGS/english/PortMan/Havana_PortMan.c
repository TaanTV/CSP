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
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Hello. I would like to find out if a corvette '" + pchar.questTemp.Slavetrader.ShipName + "' has stopped at your port, under the command of Francois Gontier?";
                link.l1.go = "Havana_ratP_1";
			}

		break;

		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Yes, I stopped. But he has already left us. Ask our innkeeper about him, captain of the corvette rented a room in the tavern from him.", "You have already"+ GetSexPhrase("asked", "asked") +"about this, I answered you.", "I'm telling you, you already"+ GetSexPhrase("asked", "asked") +"about this Gontier.", "I ask you not to interfere with my work!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thank you! That's what I'll do.", "Hmm, well, yes...", "Yes, that's right, "+ GetSexPhrase("I asked", "I asked") +"...", "I'm sorry, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
