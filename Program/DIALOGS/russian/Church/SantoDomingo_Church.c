// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы, "+ GetSexPhrase("сын мой","дочь моя") +"?", "Спрашивай, я слушаю тебя..."), "Я слушаю тебя, говори, "+ GetSexPhrase("сын мой","дочь моя") +"...", "И в третий раз говорю тебе, "+ GetSexPhrase("сын мой","дочь моя") +": задавай свой вопрос.",
                          "Столько обязанностей у церковнослужителя, а тут ещё и ты донимаешь, "+ GetSexPhrase("сын мой","дочь моя") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Не сейчас, падре..."), "Да, пока особо и нечего сказать...",
                      "Задам, задам... Только позже...", "Простите, святой отец...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(PChar.MysteriousIsland == "10" && PChar.MysteriousIsland.FindForser.Church == false && NPChar.City == "SantoDomingo")	//Загадочный остров
			{
				link.l1 = "Святой отец, не знакомо ли вам такое имя - Дэви Форсер?";
				link.l1.go = "MysteriousIsland_1";
			}
		break;
		
		// Загадочный остров -->
		case "MysteriousIsland_1":
			PChar.MysteriousIsland.FindForser.Church = true;
			dialog.text = "Нет, сын мой, не слыхивал я о таком.";
			link.l1 = LinkRandPhrase("Эх, жаль...", "Спасибо и на том.", "До скорых встреч.");
			link.l1.go = "exit";
		break;
		// Загадочный остров <--
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



