// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Some time ago, while in my store, you tried to ask some question...", "Today is the third question. I need to trade, not talk nonsense...",
                          "More questions? Maybe we should trade better?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Yes, exactly...",
                      "Yeah, really for the third time...", "Hmm, maybe we'll trade...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "TakeFoodCuracao_toOrangeStore": //Голландская линейка, квест №2, доставка продовольствия из форта Оранж.
                    link.l2 = "I have an order from the commandant of the fort for you.";
                    link.l2.go = "Step_H2_1";
                break;

            }
             // <== Проверяем поле состояния квестов.
		break;

        case "Step_H2_1":
			dialog.text = NPCStringReactionRepeat("That's right, I received this order. Let's settle for the prices we were talking about, "+ GetSexPhrase("mynheer", "madam") +".",
                         "You again, very good. Let's continue our special deal.",
                         "Again our brave captain! Fine. Let's wait...",
                         "Captain, I'm glad to see you on the same occasion. Well, let's continue trading on this special batch of goods.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Let's start trading.", "Let's continue...",
                      "Goodbye.", "Oh, don't be ironic, please. "+ GetSexPhrase("By Myself", "By Myself") +"I'm sick to death of all this..." , npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

         case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
            dialog.text = "Cough, cough, glad to see you in good health, Captain. And even after such a massacre!";
            link.l2 = "Hmm, yeah, it was a good mess...";
            link.l2.go = "Step_H4_1";
        break;

        case "Step_H4_1":
			dialog.text = "I've done business with you, Captain, and now I see that you are not only good at trading. And these Englishmen won't come near us for a long time now... Thank you, "+ GetSexPhrase("mynheer", "madam") +", thank you from the bottom of my heart.";
			link.l1 = "You're welcome, keep trading.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);
}

