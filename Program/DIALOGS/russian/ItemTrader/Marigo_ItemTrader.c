// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Опять вопросы, " + GetAddress_Form(NPChar) + "...", "Вопросы, вопросы... Может торговлей займёмся, " + GetAddress_Form(NPChar) + "?",
                          "Послушайте, ну сколько можно пустые разговоры вести?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Нет вопросов...", "Сейчас мне не о чем говорить."), "Эх, опять...",
                      "Да, действительно лучше торговаться...", "Хм, извини, торговец...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Анжелика Тич: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.AT_PZD_Lavochniki") && !CheckAttribute(npchar, "AT_PZD_Vopros"))
			{
				link.l1 = "Не подскажете, где бы мне приобрести платье, достойное выхода в свет?";
				link.l1.go = "AT_PZD_Lavochniki_1";
				DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki");
			}
            if(CheckAttribute(pchar, "questTemp.AT_PZD_Lavochniki_2") && !CheckAttribute(npchar, "AT_PZD_Vopros"))
            {
				link.l1 = "Мне нужно обзавестись платьем, не хуже чем у жены местного банкира.";
				link.l1.go = "AT_PZD_Lavochniki_2";
				DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki_2");
			}
			if(CheckAttribute(pchar, "questTemp.AT_PZD_Lavochniki_3") && !CheckAttribute(npchar, "AT_PZD_Vopros"))
            {
				link.l1 = "Мне нужно платье, но не обычное, а такое, чтоб в нём было не стыдно показаться хоть на приёме у самого короля Франции.";
				link.l1.go = "AT_PZD_Lavochniki_3";
				DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki_3");
			}
			// <== Анжелика Тич: Портниха знатной дамы
		break;
		
		//============ Анжелика Тич: Портниха знатной дамы
		case "AT_PZD_Lavochniki_1":
    		dialog.text = "На рынке вы такое вряд ли купите. Вам бы портниху найти хорошую. К сожалению, я никого не могу посоветовать...";
    		link.l1 = "Ладно...";
    		link.l1.go = "exit";
			pchar.questTemp.AT_PZD_Lavochniki_2 = true;
			npchar.AT_PZD_Vopros;
 		break;
		
		case "AT_PZD_Lavochniki_2":
    		dialog.text = "Нет, госпожа, такого в продаже у меня нет.";
    		link.l1 = "Ладно...";
    		link.l1.go = "exit";
			pchar.questTemp.AT_PZD_Lavochniki_3 = true;
			npchar.AT_PZD_Vopros;
 		break;
		
		case "AT_PZD_Lavochniki_3":
    		dialog.text = "У портного короля Франции, у кого же ещё. А мы люди простые, не то что эти богатые господа, которые посещают местный бордель.";
    		link.l1 = "Как интересно, а эти господа пользуются особым статусом? Не бегают же они туда к портовым девкам?";
    		link.l1.go = "AT_PZD_Lavochniki_3_1";
 		break;
		
		case "AT_PZD_Lavochniki_3_1":
    		dialog.text = "Простите, не в моих правилах сплетни распускать. Зайдите поинтересуйтесь, может и вам что-то особое предложат, а меня нет, не спрашивайте. Хозяйка там дама видная, у кузена моего вино берёт, он отменный винодел, и ни к чему мне на неё наговаривать.";
    		link.l1 = "Я вас поняла. Что же, приму к сведению и вина вашего как нибудь обязательно возьму.";
    		link.l1.go = "exit";
 		break;
		

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

