// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Some time ago, while in my store, you tried to ask some question...", "Today is the third question. I need to trade, not talk nonsense...",
                          "More questions? Maybe we should trade better?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Yes, exactly, I tried...",
                      "Yeah, really for the third time...", "Hmm, maybe we'll trade...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = "Excuse me, did Edward Law buy a ship from you?";
				link.l1.go = "PL_Q3_1";
			}
		break;
		//пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat("Me?! You're confusing me with someone else, I'm a trader, but with ships... I don't sell ships! You, "+ GetSexPhrase("young man", "girl") +" need to contact the shipbuilders at the shipyard. Yes, to them, and to me for everything else!",
				"You've already asked. No, he didn't buy it.",
				"No, "+ GetSexPhrase("young man", "young lady") +", no...",
                "Oh, what a bore you are!!!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes, but there is no shipyard in your town!",
				"I see...",
                "Yeah, I see...",
				"Hmm, I'm already leaving...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = "I can not help, if I wish the shipyard will not appear. Ask someone else...";
			link.l1 = "Right... well, thanks for that.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "3");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

