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
			if (CheckAttribute(PChar, "BSSentJonsWaitress"))
			{			
				link.l1 = "Дорогуша, ты не видела тут моего друга? Он большой любитель рыбалки, мы тут выпивали не так давно?";
				link.l1.go = "BS_F3_24";
			}
		break;
		
		case "BS_F3_24":
			DeleteAttribute(PChar, "BSSentJonsWaitress");
			AddMoneyToCharacter(pchar, -500);
			SetFunctionLocationCondition("BS_BonsDominicaMeeting", "Dominica", false);
			AddQuestRecord("BSHangover", "62");
			dialog.text = "Охотитесь за крупной рыбой? Он просил передать, что другой рыбак, будет ждать вас в водах Доминики у пляжа Касл Брус.";
			link.l1 = "Спасибо. Вот тебе на эмм..., на что-нибудь красивое!"; //Отдаём 500 рублей
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
