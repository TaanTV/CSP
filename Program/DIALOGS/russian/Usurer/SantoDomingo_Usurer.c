/// диалог по городам
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
			if(PChar.MysteriousIsland == "5" && NPChar.City == "SantoDomingo")
			{
				link.l1 = "Я интересуюсь судьбой матроса Диего Маркеса, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "MysteriousIsland_1";
			}
			if(PChar.MysteriousIsland == "5" && NPChar.City == "SantoDomingo" && PChar.MysteriousIsland.FirstNoneMoney == true)
			{
				link.l1 = "Я всё ещё по поводу Диего Маркеса.";
				link.l1.go = "MysteriousIsland_6";
			}		
			if(PChar.MysteriousIsland == "9" && NPChar.City == "SantoDomingo")
			{
				Link.l1 = "Здравствуйте, господин " + NPChar.lastname + ". Мне помнится, что вы при прошлом нашем визите упомянули имя капитана Дэви Форсера? Нет ли у вас ещё каких-нибудь сведений, касательно этой особы?";
				Link.l1.go = "MysteriousIsland_7";
			}
		break;
		
		// ЗАГАДОЧНЫЙ ОСТРОВ -->
		case "MysteriousIsland_1":
			dialog.text = "Вот как! Этот человек задолжал мне крупную сумму - 100000 монет. И сейчас он находится под арестом в местной тюрьме. Он всё время твердил, что у него скоро будет много денег и я поверил ему и, как оказалось, напрасно. Он вкратце рассказал мне о своих приключениях. Кстати, его капитан Дэви Форсер тоже бывал у меня, правда они никогда при мне не сталкивались.";
			if(sti(PChar.money) >= 100000)
			{
				link.l1 = "Я готов"+GetSexPhrase("","а")+" выплатить вам указанную сумму. Диего Маркес нужен мне на свободе.";
				link.l1.go = "MysteriousIsland_2";	
			}			
			link.l2 = "Это очень большие деньги! И как это ему удалось влезть в такие долги? В любом случае спасибо за информацию, разрешите откланяться.";
			link.l2.go = "MysteriousIsland_3";
		break;

		case "MysteriousIsland_2":
			AddMoneyToCharacter(PChar, -100000);
			PChar.MysteriousIsland.FirstNoneMoney = false;
			dialog.text = "Прекрасно! В таком случае я сам улажу все формальности. Приходите завтра - Диего Маркес будет ждать вас здесь.";
			link.l1 = "Отлично. До свидания.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandWaitDiegoMarkes");
		break;

		case "MysteriousIsland_3":
			PChar.MysteriousIsland.FirstNoneMoney = true;
			dialog.text = "Всего доброго, "+GetSexPhrase("господин капитан","госпожа")+"!";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "MysteriousIsland_4":
			dialog.text = "Видите ли, "+GetSexPhrase("господин капитан","госпожа")+" - тайна вклада - один из основных принципов моей работы с клиентами. Впрочем, за 2000 монет я готов поделиться с вами информацией.";
			if(sti(PChar.money) >= 2000)
			{
				AddMoneyToCharacter(PChar, -2000);
				link.l1 = "Возьмите деньги, господин " + NPChar.lastname + ". Итак, что вам известно?";
				link.l1.go = "MysteriousIsland_5";
			}
			else
			{
				link.l1 = "Что что? Да мне ничего не стоит пронзить тебя своей шпагой. Выкладывай всё, да без шуток!";
				link.l1.go = "MysteriousIsland_5";		
			}
		break;
		
		case "MysteriousIsland_5":
			dialog.text = "Хорошо... Дело в том, что Дэви Форсер больше не является моим клиентом, иначе я просто не стал бы с вами разговаривать. Вчера он забрал все свои деньги, очень, очень крупную сумму.";
			link.l1 = "Вчера?! Вот чёрт, мы совсем немного разминулись! Нам надо спешить! До свидания, господин " + NPChar.lastname + "!";
			link.l1.go = "exit";
		break;
		
		case "MysteriousIsland_6":
			dialog.text = "Вы готовы выплатить долг за Диего?";
			if(sti(PChar.money) >= 100000)
			{
				link.l1 = "Да. Вот эти деньги.";
				link.l1.go = "MysteriousIsland_2";
			}
		
			link.l2 = "Э-э.. Наверное, нет. До свидания.";
			link.l2.go = "exit";
		break;
		
		case "MysteriousIsland_7":
			dialog.text = "Видите ли, "+GetSexPhrase("господин капитан","госпожа")+" - тайна вклада - один из основных принципов моей работы с клиентами. Впрочем, за 2000 монет я готов поделиться с вами информацией.";
			if(sti(PChar.money) >= 2000)
			{
				AddMoneyToCharacter(PChar, -2000);
				link.l1 = "Возьмите деньги, господин " + NPChar.lastname + ". Итак, что вам известно?";
				link.l1.go = "MysteriousIsland_8";
			}
			else
			{
				link.l1 = "Что-что? Да мне ничего не стоит пронзить тебя своей шпагой. Выкладывай всё, да без шуток!";
				link.l1.go = "MysteriousIsland_8";		
			}
		break;
		
		case "MysteriousIsland_8":
			dialog.text = "Хорошо... Дело в том, что Дэви Форсер больше не является моим клиентом, иначе я просто не стал бы с вами разговаривать. Вчера он забрал все свои деньги, очень, очень крупную сумму.";
			link.l1 = "Вчера?! Вот чёрт, мы совсем немного разминулись! Нам надо спешить! До свидания, господин " + NPChar.lastname + "!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandFindDavyForser");
		break;
		// <-- ЗАГАДОЧНЫЙ ОСТРОВ
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

