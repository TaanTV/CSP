// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Вопросы, " + GetAddress_Form(NPChar) + "?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Хм, уж не пристаёте ли вы ко мне, " + GetAddress_Form(NPChar) + "? ","Опять со странными вопросами? Девушка, выпили бы вы рому, что ли...") +"", "В течение этого дня вы уже третий раз говорите о каком-то вопросе..."+ GetSexPhrase(" Это знаки внимания?","") +"",
                          "Опять вопросы будете задавать, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить."), "Да нет, что ты, красавица...",
                      "Никак нет, дорогуша, склероз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Oficiantka_Beliz"))	// Квест "Охота на ведьму"
			{
				link.l1 = "А ты не знаешь, где сейчас Мария?";
				link.l1.go = "PDM_ONV_WOMAN";
			}
		break;
		
//========================== Квест "Охота на ведьму" ==================================
		case "PDM_ONV_WOMAN":
			dialog.text = "Эээ... Нет. Лучше поспрашивайте городских жителей. Я думаю, они точно что-то да скажут.");
			link.l1 = "Хорошо, красавица, я пойду.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Oficiantka_Beliz");
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

