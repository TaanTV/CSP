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
			// ==> Анжелика Тич: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.AT_PZD_Rostovshik"))
			{
				DeleteAttribute(pchar, "questTemp.AT_PZD_Rostovshik")
				link.l1 = "Tell me mynheer, are you married?";
				link.l1.go = "AT_PZD_Rost_1";
				break;
			}
			// <== Анжелика Тич: Портниха знатной дамы
		break;
		
		//============ Анжелика Тич: Портниха знатной дамы
		case "AT_PZD_Rost_1":
    		dialog.text = "Admittedly, an extremely unexpected question. I'm right in some confusion.";
    		link.l1 = "I would like to buy a dress worthy of your spouse's high status.";
    		link.l1.go = "AT_PZD_Rost_2";
 		break;
		case "AT_PZD_Rost_2":
    		dialog.text = "Oh, that's it! I'm married, but you see, my wife is a lady in the body. I'm afraid even if she agrees to sell you something from her wardrobe, you will need more than one day to cut and stitch.";
    		link.l1 = "It's a pity, I just don't have that much time.";
    		link.l1.go = "AT_PZD_Rost_3";
 		break;
		case "AT_PZD_Rost_3":
    		dialog.text = "Ask around the local storekeepers in the city, maybe they will find the dress you need.";
    		link.l1 = "Thank you, I'll take your advice. Goodbye.";
    		link.l1.go = "AT_PZD_Rost_3";
 		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

