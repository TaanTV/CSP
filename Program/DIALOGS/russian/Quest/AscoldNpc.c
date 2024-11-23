void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
		case "First time":
			dialog.text = "Не о чем говорить.";
			link.l1 = "Ладно...";
			link.l1.go = "exit";
//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
            if (pchar.questTemp.Ascold == "SeekInformatorHavanna" || pchar.questTemp.Ascold == "2SeekInformatorHavanna")
            {
            	dialog.text = "" + TimeGreeting() + ". Кто вы так"+GetSexPhrase("ой ","ая ") + "и что вы хотите от меня?";
        		link.l1 = "" + TimeGreeting() + ". Меня зовут " + GetFullName(pchar) + ". Я прибыл"+GetSexPhrase("","а") + " к вам по поручению Аскольда.";
        		link.l1.go = "Step_1";
            }
			if (pchar.questTemp.Ascold == "ReciveInformationManowar")
            {
				if (!CheckAttribute(pchar, "questTemp.Ascold.IKnowTheShip"))
				{
					dialog.text = "Что вы ещё от меня хотите?";
					link.l1 = "Послушайте, вы мне сказали, что оформляли инвентарную опись. Я вам щедро заплачу, если вы сейчас вспомните корабль и капитана, которому доверили эту опись.";
					link.l1.go = "Step_8";	
				}
				else
				{
					dialog.text = "Я пожалуй, воздержусь от контактов с вами, вы мне не нравитесь, хоть и " + GetSexPhrase("друг", "знакомая") + " Аскольда.";
					link.l1 = "Ну как знаешь...";
					link.l1.go = "exit";
				}
            }
		break;
		
//<<<<<<<<<<<<======== Разброс диалогов по персонажам ======================
 		case "Step_1":
        	dialog.text = "Какого ещё Аскольда?";
    		link.l1 = "Обыкновенного, который на Гваделупе живёт. Другого на Карибах нет...";
    		link.l1.go = "Step_2";
		break;
 		
		case "Step_2":
        	dialog.text = "Говорите тише, я вас прекрасно понял. Что же нужно моему другу Аскольду?";
    		link.l1 = "Есть одна проблема. Некоторое время назад из Гаваны ушёл некий корабль, под завязку гружённый всевозможными предметами индейской культуры...";
    		link.l1.go = "Step_3";
		break;
 		
		case "Step_3":
        	dialog.text = "Ну, это громко сказано... Были там предметы индейской культуры, но не так уж и много\n" + "Я был откомандирован в Гавану и лично оформлял инвентарный отгрузочный список.";
    		link.l1 = "Вот он-то и нужен Аскольду, этот список.";
    		link.l1.go = "Step_4";
		break;
 		
		case "Step_4":
        	dialog.text = "Знал бы я, что он ему нужен - сделал бы копию. Ну а сейчас не вспомню уже и половины всего\n" + "Теперь даже не знаю, как ему помочь.";
    		link.l1 = "Я понимаю... Поэтому мне бы хотелось узнать, куда именно ушёл этот корабль.";
    		link.l1.go = "Step_5";
		break;
 		
		case "Step_5":
        	dialog.text = "Он ушёл к бухте Аматике, южней Белиза. Однако, по пути экспедиция намерена сделать остановку у острова Кайман.";
    		link.l1 = "Странное место... Интересно бы, для чего? И что, корабль этот так и ушёл один?";
    		link.l1.go = "Step_6";
		break;
 		
		case "Step_6":
        	dialog.text = "Да, ушёл один. Дело в том, что Кайман - место сбора и других кораблей с испанских колоний в Южной Америке. Представляете, вглубине материка наши исследователи нашли заброшенный индейский храм. Сейчас там работает королевская археологическая экcпедиция. Как только они закончит работы, эскадра отправится в Старый Свет, в Испанию\n" + "Это всё, что я знаю.";
    		link.l1 = "Этого хватает, спасибо, друг. Передам от тебя привет Аскольду.";
    		link.l1.go = "Step_7";
		break;
 		
		case "Step_7":
        	dialog.text = "Эй, " + GetAddress_Form(pchar) + ", подождите! А деньги?";
    		link.l1 = "Послушай, я твой новый друг, а Аскольд - старый. А деньги приносят только старые друзья. Так что прощай и до новых встреч!";
    		link.l1.go = "exit";
			
			// Nathaniel (21.01.24): здесь делаю развилку на случай, если игрок захочет упростить себе задачу
			link.l2 = "Послушайте, вы мне сказали, что оформляли инвентарную опись. Я вам щедро заплачу, если вы сейчас вспомните корабль и капитана, которому доверили эту опись.";
			link.l2.go = "Step_8";
			
			npchar.LifeDay = 5;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
            AddQuestRecord("Ascold", "7");
            pchar.questTemp.Ascold = "ReciveInformationManowar";
            Pchar.quest.Ascold_AttackTenManowars.win_condition.l1 = "location";
            Pchar.quest.Ascold_AttackTenManowars.win_condition.l1.location = "Caiman";
            Pchar.quest.Ascold_AttackTenManowars.win_condition = "Ascold_AttackTenManowars";
		break;

        case "Step_8":
            dialog.text = "Хм... Однако... Не ожидал от вас этого, " + GetAddress_Form(pchar) + " " + pchar.name + ". И сколько вы готовы предложить за эту информацию?";
            link.l1 = "Ну... Скажем. Двести пятьдесят тысяч песо. Полагаю, это достаточно большая сумма за информацию о наборе дешёвых статуэток на жалкой бумаге?";
            link.l1.go = "Step_9";
        break;

		case "Step_9":
			if (IsCharacterPerkOn(pchar, "Agent") || GetCharacterSkillNoBonus(pchar, SKILL_LEADERSHIP) > 70)
			{
				dialog.text = "Хорошо, вы меня убедили.";
				link.l1 = "Ну вот видите, мне сразу стало понятно, что мы сможем договориться. Вот, получите ваши деньги и мою искреннюю благодарность! Прощайте, " + GetAddress_FormToNPC(npchar) + ".";
				link.l1.go = "Step_10";
			}
			else
			{
				dialog.text = "Помилуйте, что я слышу?! Вы предлагаете мне сейчас взятку, чтобы взять на абордаж и уничтожить корабль моих соотечественников?! Убирайтесь прочь, не то я позову сюда стражу!!!";
				link.l1 = "Да что же ты так раскричался, " + GetAddress_FormToNPC(npchar) + "? Я всё понимаю и не обижаюсь на тебя. Прощай...";
				link.l1.go = "exit";
			}
		break;

		case "Step_10":
			if (sti(pchar.money) < 250000)
			{
				dialog.text = "Вы что, издеваетесь надо мной?! Ну и где же обещанные мне двести пятьдесят тысяч песо? О, у вас, кажется, проблемы с деньгами...";
				link.l1 = "Кхм... Забыл"+GetSexPhrase(" ","а ") + "спросить у казначея. Ждите меня здесь, никуда не уходите!";
				link.l1.go = "exit";
				NextDiag.TempNode = "IHaveNoMoney";
			}
			else
			{
				dialog.text = "Премного вам благодарен, " + GetAddress_Form(pchar) + " " + pchar.name + ". Названия корабля, на котором список, я не видел, но смогу точно описать сам корабль - увидите, не ошибётесь. Желаю вам удачи в ваших с моим предприимчивым другом Аскольдом делах.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddMoneyToCharacter(pchar, -250000);
				
				// Nathaniel (21.01.24): признак того, что знаем корабль (пока не знаю, вдруг понадобится)
				pchar.questTemp.Ascold.IKnowTheShip = true;
				
				// Nathaniel (21.01.24): дополнительная запись в судовом журнале
				AddQuestRecord("Ascold", "7_1");
			}
		break;

		case "IHaveNoMoney":
			dialog.text = "Чёрт побери, " + GetAddress_FormToNPC(npchar) + ", где вы пропадаете?! Моё терпение не бесконечно, я могу и передумать!..";
			link.l1 = "Вот ваши двести пятьдесят тысяч песо, " + GetAddress_FormToNPC(npchar) + ".";
			link.l1.go = "Step_10";
		break;
 		
		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
    }
}
