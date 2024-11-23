// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Just recently you tried to ask me a question...", "Well, let me guess... Nothing significant again?",
                          "Listen, I'm handling finances, not answering questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "You guessed it, I'm sorry...", "I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = "They say Edward Law was supposed to contact you, I'm looking for him.";
				link.l1.go = "PL_Q3_1";
			}
		break;
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat("He came to me, asked for money. He didn't give it to me. A very slippery guy, his eyes are running around, clearly intended to run away. I dare say I'm a good judge of people.",
				"I've already said everything on this topic, look for yourself.",
				"Again?",
                "Get lost!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Where to...",
				"I see.",
                "Yeah, sorry...",
				"I see, I'm leaving.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = "And I have no idea where he could have gone.";
			link.l1 = "Clear...";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "5");
			AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("", "a"));
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

