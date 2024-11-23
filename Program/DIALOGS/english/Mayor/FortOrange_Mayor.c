// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What did you want? Ask.", "I'm listening to you, what's the question?"), "For the second time in a day you're trying to ask a question...", "For the third time in a day you're trying to ask a question again...",
                          "But when will it end?! I have a lot of things to do to manage the affairs of the city, and you're trying to ask all the questions!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, not the place and not the time..."), "Yes, that's right... But not now, later...",
                      "I'll ask, I'll ask... Only later...", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "TakeFoodCuracao_toOrangeMayor": //Голландская линейка, квест №2, доставка продовольствия из Форт Оранжа.
                    link.l2 = "I have arrived by order of Peter Stuyvesant. You have a batch of goods prepared for Curacao, I should buy and deliver it. I ask you to familiarize yourself with the documents for the provision of special prices.";
                    link.l2.go = "Step_H2_1";
                break;

            }
             // <== Проверяем поле состояния квестов.
		break;

        case "Step_H2_1":
			dialog.text = "So, let's read it... Well, the papers are all right. You can get the whole batch of goods at a local store, I will immediately order it to be given to you\n"+
                          "The batch consists of coffee, black, red and sandal. The total weight of the batch of goods prepared for shipment is 5,600 centners. Pay off at the store and you can start loading.";
			link.l1 = "Very good.";
			link.l1.go = "exit";
            TakeItemFromCharacter(pchar, "Trust");
            BackItemDescribe("Trust");
            AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "2");
			pchar.questTemp.State = "TakeFoodCuracao_toOrangeStore";
        	pchar.GenQuest.StoreGoods.StoreIdx = FortOrange_STORE;
        	pchar.GenQuest.StoreGoods.HL2_DiscountPrices = true;
		break;

        case "DefenceOrange": //Голландская линейка, квест №4, защита Форт Оранжа.
            dialog.text = "How glad I am to see you, how glad I am!...";
            link.l2 = "I'm here on behalf of Stuyvesant. It seems that we managed to...";
            link.l2.go = "Step_H4_1";
        break;

        case "Step_H4_1":
			dialog.text = "Damn it, you didn't just make it, you just saved us! Fort Orange thanks you from the bottom of its heart! My compliments to Peter Stuyvesant.";
			link.l1 = "I will definitely pass it on. Have a nice day.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

