// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(PChar.MysteriousIsland == "10" && PChar.MysteriousIsland.FindForser.PortOffice == false && NPChar.City == "SantoDomingo")	//Загадочный остров
			{
				link.l1 = "Добрый день, не отмечался ли в вашем порту Дэви Форсер?";
				link.l1.go = "MysteriousIsland_1";
			}
		break;
		
		// Загадочный остров -->
		case "MysteriousIsland_1":
			PChar.MysteriousIsland.FindForser.PortOffice = true;
			dialog.text = "Последнее время в городе ничего не происходит, и если бы он отметился у меня - я бы запомнил.";
			link.l1 = LinkRandPhrase("Эх, жаль...", "Спасибо и на том.", "До скорых встреч.");
			link.l1.go = "exit";
		break;
    	// Загадочный остров <--

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


