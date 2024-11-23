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
			if(PChar.MysteriousIsland == "3" && NPChar.City == "Charles")	// Загадочный остров
			{
				link.l1 = "Дело вот в чём. В одной из таверн я познакомил"+GetSexPhrase("ся","ась")+" с одним странным моряком - Джимом Смитом. После произошедших с ним страшных событий он находится в очень плохом душевном состоянии.";
				link.l1.go = "MysteriousIsland_1";
			}
		break;
		
		// Загадочный остров -->
		case "MysteriousIsland_1":
			dialog.text = "Я понимаю, о ком идёт речь. Я давно приглашал его к себе, ведь при нашей церкви жили двое прежних его товарищей, тоже участвовавших в тех событиях, о которых ты упомянул"+GetSexPhrase("","а")+". Я помогал им чем мог, но вылечить их души мне не удалось.";
			link.l1 = "А где же они сейчас?";
			link.l1.go = "MysteriousIsland_2";
		break;
		
		case "MysteriousIsland_2":
			dialog.text = "На местном кладбище, царствие им небесное!";
			link.l1 = "Скажите, отец "+npchar.name+", эти двое усопших ничего не оставили вам перед смертью?";
			link.l1.go = "MysteriousIsland_3";
		break;
		
		case "MysteriousIsland_3":
			dialog.text = "Ты говоришь о части карты, "+ GetSexPhrase("сын мой","дочь моя") +"? Я разочарую тебя - ничего такого они не оставляли. И я от всего сердца не советую тебе связываться с этой историей!";
			link.l1 = "Отец "+npchar.name+", я хочу разобраться в происшедшем.";
			link.l1.go = "MysteriousIsland_4";
		break;
		
		case "MysteriousIsland_4":
			dialog.text = "Ну что ж, я вижу - мне не отговорить тебя. Будь бдител"+ GetSexPhrase("ен","ьна") +", "+ GetSexPhrase("сын мой","дочь моя") +", и не забывай Господа нашего!";
			link.l1 = "Спасибо, святой отец!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandToCharlesTown");
		break;
		// <-- Загадочный остров
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



