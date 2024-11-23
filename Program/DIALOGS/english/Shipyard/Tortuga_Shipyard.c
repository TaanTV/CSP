// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Quite recently you tried to ask me a question...", "At my shipyard, and in general in Tortuga, I have not seen such monotonously inquisitive people.",
                          "My job is to build ships, let's do it.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Hmm, however...", "Let's...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
                    link.l2 = "I heard that Pierre Picardy has the best ship in these waters.";
                    link.l2.go = "Step_H3_1";
                break;

            }
             // <== Проверяем поле состояния квестов.
		break;
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat("Maybe so. His frigate was already good enough, and the other day I finished upgrading it. Now his culverins are the latest anywhere, they are loaded from the breech! It's expensive, but it's worth it... So, apparently, you are "+ GetSexPhrase("right", "right") +". Why do you ask?", ""+ GetSexPhrase("Senor", "Senorita") +", let's get on with ship business, I don't care about the Picardy right now...", "You've already asked me about Pierre...", "Listen, maybe you can ask about Pierre elsewhere, huh?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I want to pull off a small event, but "+ GetSexPhrase("myself", "myself") +"I won't pull it... Therefore, I am looking for someone who could keep me company.", "Let's get busy...", "Yes? Hmm, exactly "+ GetSexPhrase("I asked", "I asked") +"...", "Yes, I guess I'll ask around somewhere else.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = "Understood. Well, Pierre is a good choice in this regard, Morgan himself offers him such events from time to time.";
			link.l1 = "Wow, Morgan himself?! This Pierre is a serious man. Thank you for the recommendation.";
			link.l1.go = "exit";
            pchar.questTemp.Talks.Shipyard = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "9");
        break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

