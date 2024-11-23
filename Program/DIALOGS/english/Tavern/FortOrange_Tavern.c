// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question, " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Are we going to ask questions again?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yes, really for the third time...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Have you had such a Francois Gontier in your city? I really need him.";
                link.l1.go = "Jamaica_ratF_1";
            }
			//виспер
			if(CheckAttribute(pchar, "Whisper.FindDesouzaHol") && !CheckAttribute(npchar, "Whisper.FindDesouzaHol"))
			{
				npchar.Whisper.FindDesouzaHol = true;
				link.l1 = "Listen, did any guys of suspicious appearance come up to you here? They should also have a crucifix-shaped brand on their arm.";
				link.l1.go = "FindDesouzaHol";
				break;
			}
			//виспер
			if(CheckAttribute(pchar, "BSUrka_Negril") && !CheckAttribute(npchar, "BSUrka_Negril"))
			{
				npchar.BSUrka_Negril = true;
				link.l1 = "Have you heard anything about the brig that sank nearby? 'Ranger'.";
				link.l1.go = "BSUrka_Negril";
				break;
			}
		break;

        case "BSUrka_Negril":
            dialog.text = "I'm afraid I can't help you with that. Last week I almost gave my soul to God - I picked up some kind of sore from an English whore. I had to stay in bed, so I didn't have time for local news at all. I just went to work today, but you ask the guests, surely someone saw something.";
            link.l2 = "I will do so.";
            link.l2.go = "exit";
        break;

        case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
            dialog.text = "Yes, I'll tell you, I've never seen such a dashing massacre in my lifetime...";
            link.l2 = "Well done to the English dogs, huh?";
            link.l2.go = "Step_H4_1";
        break;

        case "Step_H4_1":
			dialog.text = "What can I say, "+ GetSexPhrase("mynheer", "mistress") +". There is no finer way. Thank you so much!";
			link.l1 = "You're welcome.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Jamaica_ratF_1":
			dialog.text = "He appeared. He rented a room from me for several days. The most unpleasant guy, I'll tell you. And besides, with delusions of persecution, he was always looking around and being afraid of everything, like a paranoid. Wasn't he so afraid of you?";
			link.l1 = "No, not me. In general, privateers have a lot of enemies, you know. So where can I find him? We agreed to go to work together, but he just disappeared through the ground!";
			link.l1.go = "Jamaica_ratF_2";
		break;

		case "Jamaica_ratF_2":
			dialog.text = "Went to sea on his ship. But I don't know where to go. He didn't report to me.";
			link.l1 = "Oh, it's a pity! Where am I going to look for him now?";
			link.l1.go = "Jamaica_ratF_3";
		break;

		case "Jamaica_ratF_3":
			dialog.text = "I don't know, "+ GetSexPhrase("buddy", "madam") +". If I knew, I'd tell you.";
			link.l1 = "Okay, everything is clear. I'll go ask someone else...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		case "FindDesouzaHol":
    		dialog.text = "No, I definitely haven't seen them here.";
    		link.l1 = "Okay, thanks.";
			pchar.Whisper.FindDesouzaHolWaitress = true;
    		link.l1.go = "exit";
 		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
