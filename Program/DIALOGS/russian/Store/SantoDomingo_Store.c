// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Спрашивай, чего ты хочешь?",
                          "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушай, это магазин, здесь люди покупают что-то. Не отвлекай меня!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Гм, не буду...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(PChar.MysteriousIsland == "10" && PChar.MysteriousIsland.FindForser.Store == false && NPChar.City == "SantoDomingo")	//Загадочный остров
			{
				link.l1 = "Не приобретал ли у вас чего-нибудь капитан Дэви Форсер?";
				link.l1.go = "MysteriousIsland_1";
			}
		break;
		
		// Загадочный остров -->
		case "MysteriousIsland_1":
			PChar.MysteriousIsland.FindForser.Store = true;
			dialog.text = "Впервые о таком слышу.";
			link.l1 = LinkRandPhrase("Эх, жаль...", "Спасибо и на том.", "До скорых встреч.");
			link.l1.go = "exit";
		break;
    	// Загадочный остров <--
	}
	UnloadSegment(NPChar.FileDialog2);
}

