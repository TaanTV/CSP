// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "М-да, позвольте угадаю... Опять ничего существенного?",
                          "Послушайте, я финансами оперирую, а не на вопросы отвечаю...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Вы угадали, простите...", "Я понимаю...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Анжелика Тич: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.AT_PZD_Rostovshik"))
			{
				DeleteAttribute(pchar, "questTemp.AT_PZD_Rostovshik")
				link.l1 = "Скажите минхер, вы женаты?";
				link.l1.go = "AT_PZD_Rost_1";
				break;
			}
			// <== Анжелика Тич: Портниха знатной дамы
		break;
		
		//============ Анжелика Тич: Портниха знатной дамы
		case "AT_PZD_Rost_1":
    		dialog.text = "Признаться, крайне неожиданный вопрос. Я право в некотором замешательстве.";
    		link.l1 = "Я бы хотела выкупить платье, достойное высокого статуса вашей супруги.";
    		link.l1.go = "AT_PZD_Rost_2";
 		break;
		case "AT_PZD_Rost_2":
    		dialog.text = "Ах вот оно что! Женат, но видите ли, моя супруга дама в теле. Боюсь, даже если она согласится продать вам что-нибудь из своего гардероба, вам понадобится не один день на перекрой и ушивку.";
    		link.l1 = "Очень жаль, у меня как раз нет такого количества времени.";
    		link.l1.go = "AT_PZD_Rost_3";
 		break;
		case "AT_PZD_Rost_3":
    		dialog.text = "Поспрашивайте лучше местных лавочников в городе, может быть у них найдётся нужное вам платье.";
    		link.l1 = "Спасибо, воспользуюсь вашим советом. До свидания.";
    		link.l1.go = "AT_PZD_Rost_3";
 		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

