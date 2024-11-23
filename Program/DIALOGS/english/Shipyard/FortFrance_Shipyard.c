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
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = "Did someone Edward Law contact you to purchase a ship?";
				link.l1.go = "PL_Q3_1";
			}
		break;
		//пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat("I came, but I didn't buy anything.",
				"I've already said everything about it...",
				"I applied, I applied. Only I have nothing to add to what I said earlier.",
                "Listen, "+ GetSexPhrase("tired", "tired") +"!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("What's wrong?",
				"Yes, that's right...",
                "Got it.",
				"I'm already leaving...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = "He wanted a brig, but I'm sorry, he just had money for a lugger.";
			link.l1 = "Clear... Did you notice where he went?";
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = "Hehe, we know where. I went to the usurer to borrow money, but he didn't give him any money, heh-heh-heh...";
			link.l1 = "What makes you think that?";
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = "So he didn't come back, so he didn't find the money, hehe...";
			link.l1 = "Right!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "4");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

