// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Quite recently you tried to ask me a question...", "At my shipyard, and in general in the city, I have not seen such monotonously inquisitive people.",
                          "Well, what kind of questions? My job is to build ships, let's do it.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Hmm, however...", "Let's...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Listen, have you contacted with a privateer named Francois Gontier? He was in Porto Bello recently, I know for sure.";
                link.l1.go = "Portobello_ratS_1";
            }
		break;

		case "Portobello_ratS_1":
			dialog.text = "Yes, I have. He bought a corvette from me and soon went to sea.";
			link.l1 = "Thank you! Do you know where he went, by any chance?";
			link.l1.go = "Portobello_ratS_2";
		break;

		case "Portobello_ratS_2":
			dialog.text = "No, "+ GetSexPhrase("buddy", "girlfriend") +", without the slightest idea. I repair and sell ships, not keep track of who's going where. I don't care about that.";
			link.l1 = "Well, let's find out...";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

