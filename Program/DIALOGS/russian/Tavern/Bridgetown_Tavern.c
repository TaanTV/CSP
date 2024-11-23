// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(PChar.MysteriousIsland == "2" && Characters[GetCharacterIndex("Jimm Smith")].location == PChar.location)
			{
				link.l1 = "Послушай, дружище, не мог бы ты рассказать мне что-нибудь про того моряка, с которым я недавно сидел"+GetSexPhrase("","а")+" за одним столиком?";
				link.l1.go = "MysteriousIsland_1";
			}
		break;
		
		// Загадочный Остров -->
		case "MysteriousIsland_1":
			dialog.text = "А-а, ты о Джиме Смите! Да что мне рассказать, " + GetAddress_Form(NPChar) + ". Пьёт безбожно каждый день, а как напьётся до чёртиков, всё твердит, что скоро уедет отсюда в церковь Чарльстауна. Каждый день одно и тоже!";
			if(sti(PChar.money) >= 500)
			{
				AddMoneytoCharacter(PChar, -500);
				link.l1 = "Спасибо тебе, " + NPChar.name + ", возьми-ка вот 500 монет, в наше время такие бескорыстные люди как ты - большая редкость.";
				link.l1.go = "exit";			
			}
			else
			{
				link.l1 = "Спасибо тебе, " + NPChar.name + ".";
				link.l1.go = "exit";
			}
			AddDialogExitQuestFunction("MysteriousIslandToCharlesChurch");
		break;
		// Загадочный Остров <--
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

