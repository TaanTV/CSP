// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Just recently you tried to ask me a question...", "There have not been such questions in the Tortuga store for a long time...",
                          "Questions, questions, more questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind..", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Well, it wasn't - it wasn't like that.", "First of all, yes...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
                    link.l2 = "Listen, has Pierre Picardy been to your store? I was told that he went here.";
                    link.l2.go = "Step_H3_1";
                break;

            }
             // <== Проверяем поле состояния квестов.
		break;
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat("I was two hours ago, bought another batch of expensive trinkets and went on to burn my life.", "Senor, let's trade, what are the same questions?", "You already asked me about Pierre...", "Listen, maybe you can ask about Pierre elsewhere, eh?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes, Pierre is rolling like cheese in butter right now... Does he come to you often on this kind of business?", "Did you say? Well, yes, probably...", "You can trade...", "Yes, I guess I'll ask around somewhere else.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = "Read, it happens every day, with rare exceptions.";
			link.l1 = "Oh, and people are lucky! Well, I'll go on looking for him. Thank you.";
			link.l1.go = "exit";
            pchar.questTemp.Talks.Store = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "8");
        break;



	}
	UnloadSegment(NPChar.FileDialog2);
}

