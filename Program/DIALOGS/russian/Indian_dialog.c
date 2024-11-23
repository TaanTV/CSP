// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Не о чем говорить!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Бледнолицый","Белая скво") +" хочет говорить?", 
				"Снова ты, "+ GetSexPhrase("бледнолицый","белая скво") +".", 
				""+ GetSexPhrase("Бледнолицый любит говорить. Он похож на скво.","Белая скво любит говорить.") +"",
                "Духи привели ко мне бледнолиц"+ GetSexPhrase("его брата","ую сестру") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да.", 
				"Да, снова я.",
                "Очень поэтично.", 
				"Я тоже рад"+ GetSexPhrase("","а") +" тебя видеть.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
			
			/*if (npchar.quest.meeting == "0")
			{
				dialog.text = "Здравствуй, белый брат. Ты хотеть говорить индеец?";
				link.l1 = "Приветствую, сын джунглей. Я рад тебя видеть, но мне пора продолжить свой путь.";
				link.l1.go = "exit";
				link.l2 = "Да. Я слышал, у вас можно купить интересные вещички. У тебя нет чего-нибудь на продажу?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}*/
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Говори, зачем приш"+ GetSexPhrase("ёл","ла") +".";
			link.l1 = "Да ничего особенного, послушать тебя хотел"+ GetSexPhrase("","а") +"...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Бледнолицый","Белая скво") +" хочет говорить?", 
				"Снова ты, яланауи?", 
				""+ GetSexPhrase("Бледнолицый","Белая скво") +" любит говорить.",
                "Духи привели ко мне бледнолиц"+ GetSexPhrase("его брата","ую сестру") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да.", 
				"Да, снова я.",
                "Очень поэтично.", 
				"Я тоже рад"+ GetSexPhrase("","а") +" тебя видеть.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" слушать тебя, "+ GetSexPhrase("сын моря","дочь моря") +".","Что ты хотеть от "+npchar.name+", "+ GetSexPhrase("бледнолицый","белая скво") +"?","Мои уши открыты для твоих слов, чужезем"+ GetSexPhrase("ец","ка") +".");
			/*if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("У меня есть кое-что для тебя. Хочешь посмотреть?","Хочешь, покажу тебе кое-что интересное? Тебе понравится...","У меня есть кое-что, что порадует тебя, дитя джунглей... Хочешь глянуть?");
				link.l1.go = "gift";
			}*/
			link.l9 = "Да ничего особенного, просто послушать тебя хотел"+ GetSexPhrase("","а") +"...";
			link.l9.go = "exit";
		break;
		
		case "Shoko_1":
			dialog.text = "Ахау, яланауи.");
			link.l9 = "Привет, красавица. Меня зовут "+pchar.name+". А тебя как зовут?";
			link.l9.go = "Shoko_2";
		break;
		
		case "Shoko_2":
			dialog.text = "Шоко.");
			link.l9 = "Можешь рассказать что-нибудь о своём народе, Шоко?";
			link.l9.go = "Shoko_3";
		break;
		
		case "Shoko_3":
			dialog.text = "Лилачиль пэль укучу лутилили, чин ту култ.");
			link.l9 = "Это очень интересно. Можно тут с кем-нибудь поторговаться?";
			link.l9.go = "Shoko_4";
		break;
		
		case "Shoko_4":
			dialog.text = "Долин вохан хинч боли. Баш кулючу нахау?");
			link.l9 = "Э-э-э, ладно... Спрошу кого-нибудь другого. Пока!";
			link.l9.go = "exit";
			NextDiag.TempNode = "ShokoAgain";
		break;
		
		case "ShokoAgain":
			dialog.text = "Ахау, яланауи. Маче эщ.");
			link.l9 = "Я тебя тоже рад"+GetSexPhrase("","а")+" видеть.";
			link.l9.go = "exit";
			NextDiag.TempNode = "ShokoAgain";
		break;
		
		case "Chani_1":
			dialog.text = "Капоно бамбуле, гучо. Я Чани, дочь Чаки Бакира, шаманка племени Шаганумби.");
			link.l1 = "Меня зовут "+GetFullName(pchar)+", я капитан корабля '" + PChar.Ship.Name + "'. Я случайно забр"+GetSexPhrase("ёл","ела")+" в эти земли, знакомлюсь с местными традициями.";
			link.l1.go = "Chani_2";
		break;
		
		case "Chani_2":
			dialog.text = "Раз уж ты капитан, то значит, ты большой человек. Мне неудобно об этом просить, но нам нужна твоя помощь, яланауи.");
			link.l1 = "Чем я могу вам помочь?";
			link.l1.go = "Chani_3";
			link.l2 = "Извини, но мне сейчас не до ваших проблем.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Chani_1";
		break;
		
		case "Chani_3":
			dialog.text = "Белые люди собирают с нас дань, заставляют нас отдавать им наши жемчужины. Они просят немного, и мы отдавали им столько, сколько они просили\nНо недавно сюда прибыл очень важный человек, Мануэль де Морено, который привёл с собой большое войско, и потребовал собрать с нас 800 больших жемчужин. Мы отдали всё что у нас было, но этого было недостаточно\nМы всё ещё должны Мануэлю де Морено отдать 500 больших жемчужин, но у нас больше ничего нет. А иначе он обещал сравнять с землёй нашу деревню\nПожалуйста, капитан, помоги нам выплатить эту дань, а взамен я обещаю тебе дать эликсир Слёзы Иш-Чель, который поможет улучшить твоё здоровье.");
			link.l1 = "Хорошо, я отыщу эти 500 больших жемчужин и принесу их тебе.";
			link.l1.go = "Chani_4";
			if (sti(pchar.items.jewelry11) >= 500)
			{
				link.l1 = "У меня есть при себе 500 больших жемчужин. Теперь твоя деревня будет в безопасности.";
				link.l1.go = "Chani_Zhemchug2";
			}
			link.l2 = "Мне очень жаль твою деревню, но помочь я не смогу.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Chani_1";
		break;
		
		case "Chani_4":
			dialog.text = "Спасибо тебе, яланауи. У тебя доброе сердце. Буду ждать тебя.");
			link.l1 = "Как соберу нужное количество - вернусь к тебе.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chani_Zhemchug";
			npchar.quest.takePearls = "seek";
			npchar.quest.takePearls.Qty = 0; //кол-во жемчужин
			
			SetQuestHeader("ShamanChani");
			AddQuestRecord("ShamanChani", "1");
		break;
		
		case "Chani_Zhemchug":
			dialog.text = "Рада тебя видеть, яланауи.");
			link.l1 = "Чани, хочу отдать тебе свои жемчужины.";
			link.l1.go = "Chani_Zhemchug2";
			link.l2 = "Мне уже пора...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Chani_Zhemchug";
		break;
		
		case "Chani_Zhemchug2":
			iTemp = GetCharacterItem(pchar, "jewelry11");
			npchar.quest.takePearls.Qty = sti(npchar.quest.takePearls.Qty) + iTemp;
			DeleteAttribute(pchar, "items.jewelry11");
			if (sti(npchar.quest.takePearls.Qty) < 500)
			{
				dialog.text = "Давай считать. Сейчас ты прин"+ GetSexPhrase("ёс","есла") +" " + FindRussianQtyString(iTemp) + " больших жемчужин. Всего ты прин"+ GetSexPhrase("ёс","есла") +" " + FindRussianQtyString(sti(npchar.quest.takePearls.Qty)) + " больших жемчужин. Тебе осталось принести ещё " + FindRussianQtyString(500 - sti(npchar.quest.takePearls.Qty)) + ".";
				link.l1 = "Понятно. Скоро вернусь с новыми жемчужинами, Чани.";
				link.l1.go = "exit";
				AddQuestRecord("ShamanChani", "2");
				AddQuestUserData("ShamanChani", "iQty", 500 - sti(npchar.quest.takePearls.Qty));
			}
			else
			{
				dialog.text = "Слава богам! Ты доказал"+GetSexPhrase("","а")+", "+pchar.name+", что наша деревня - это и твой дом тоже. Теперь я уверена, что индейцы будут в безопасности.");
				link.l1 = "Я очень рад"+GetSexPhrase("","а")+" это слышать, Чани.";
				link.l1.go = "Chani_12";
				ChangeCharacterReputation(pchar, 1);
				AddQuestRecord("ShamanChani", "3");
			}
		break;
		
		case "Chani_12":
			dialog.text = "Я хочу тебе приподнести наш ценный дар, Слёзы Иш-Чель. Он поможет тебе поправить здоровье при плохом самочувствии.");
			link.l1 = "Это очень ценный подарок, благодарю тебя.";
			link.l1.go = "Chani_13";
			GiveItem2Character(PChar, "potion7");
			Log_info("Шаманка дала вам Слёзы Иш-Чель");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "Chani_13":		
			dialog.text = "Приходи к нам в гости ещё, в будущем у меня найдётся для тебя работа.");
			link.l1 = "Непременно загляну. До встречи!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chani_21";
			SetTimerCondition("CSP_Chani_2quest", 0, 0, 14, false);
		break;
		
		case "Chani_21":		
			dialog.text = "Добро пожаловать в нашу деревню, яланауи. Ты что-то хотел"+GetSexPhrase("","а")+"?");
			link.l1 = "Я просто мимо проходил"+GetSexPhrase("","а")+". Ещё увидимся!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chani_21";
			if (CheckAttribute(pchar, "quest.Chani_2quest"))
			{
				dialog.text = "Ты вернул"+GetSexPhrase("ся","ась")+", гучо. Ты очень вовремя. Нужна твоя помощь.");
				link.l1 = "И что же на этот раз?";
				link.l1.go = "Chani_22";
			}
		break;
		
		case "Chani_22":		
			dialog.text = "Тагана, один из наших сильных воинов. Я отправила его с заданием, но он не вернулся.");
			link.l1 = "А можно поконкретнее? Куда ты отправила Тагану и что у него было за задание?";
			link.l1.go = "Chani_23";
		break;
		
		case "Chani_23":		
			dialog.text = "Ему нужно было идти далеко, в чужие земли, найти там очень нужную мне вещь.");
			link.l1 = "Я бы мог"+GetSexPhrase("","ла")+" поискать его. Хотя, если он отправился в одиночку, то скорее всего, он просто сгинул в дикой сельве.";
			link.l1.go = "Chani_24";
		break;
		
		case "Chani_24":		
			dialog.text = "Тагана слишком умён, чтобы стать добычей для хищных зверей.");
			link.l1 = "Он и для людей достаточно умён? Возможно он стал добычей патруля.";
			link.l1.go = "Chani_25";
		break;
		
		case "Chani_25":		
			dialog.text = "Солдаты со своими гром-копьями даже не заметили бы Тагану, он как ягуар крадущийся в листве.");
			link.l1 = "А что за задание было у Таганы?";
			link.l1.go = "Chani_26";
		break;
		
		case "Chani_26":		
			dialog.text = "Он должен был добыть у каннибалов особый отвар, который нужен мне для ритуала вуду, чтобы защитить деревню.");
			link.l1 = "А если я добуду этот отвар?";
			link.l1.go = "Chani_28";
			if (sti(pchar.items.StrangePotion) >= 1)
			{
				link.l1 = "У меня есть при себе этот странный отвар. Я наткнулся в джунглях на агрессивных дикарей, у одного из них была эта фляжка при себе. Думаю они и стали причиной пропажи вашего Таганы.";
				link.l1.go = "Chani_30";
			}
			link.l2 = "Мне очень жаль Тагану, но помочь я не смогу.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Chani_21";
		break;

		case "Chani_28":
			dialog.text = "Если ты добуешь для меня этот отвар, то обещаю, что буду верно служить тебе и пойду туда, куда и ты.");
			link.l1 = "Хорошо, Чани. Если найду нужный отвар - вернусь к тебе.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chani_29";
			AddQuestRecord("ShamanChani", "4");
			PChar.quest.CSP_Chani_PoiskOtvara.win_condition.l1 = "item";
			PChar.quest.CSP_Chani_PoiskOtvara.win_condition.l1.item = "StrangePotion";
			PChar.quest.CSP_Chani_PoiskOtvara.win_condition = "CSP_Chani_PoiskOtvara";
			pchar.questTemp.СhaniJidkost = "СhaniJidkost";
		break;
		
		case "Chani_29":
			dialog.text = "Рада тебя видеть, гучо. Ты прин"+GetSexPhrase("ёс","есла")+" отвар?");
			link.l1 = "Ещё нет, Чани, но я обязательно отыщу его.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chani_29";
			if (sti(pchar.items.StrangePotion) >= 1)
			{
				link.l1 = "Вот, взгляни, по-моему это то, что ты ищешь. Я подобрал"+GetSexPhrase("","а")+" его с трупа каннибала.";
				link.l1.go = "Chani_30";
			}
		break;
		
		case "Chani_30":		
			dialog.text = "Отлично! Дай мне немного времени провести обряд по защите деревни, и я присоединюсь к тебе в путешествии на твоём большом каное.");
			link.l1 = "Хорошо, Чани, буду ждать тебя на улице.";
			link.l1.go = "Chani_31";
			DeleteAttribute(pchar, "quest.Chani_2quest");
			DeleteAttribute(pchar, "questTemp.СhaniJidkost");
			AddItems(pchar, "StrangePotion", -1);
			Log_info("Вы отдали странную жидкость");
		break;
				
		case "Chani_31":
			DialogExit();
			
			sld = CharacterFromID("Chani");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetShipRemovable(sld, true);
			SetCharacterRemovable(sld, true);
			sld.HalfImmortal = true;
			sld.location = "None";
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			
			AddQuestRecord("ShamanChani", "6");
			CloseQuestHeader("ShamanChani");
			pchar.questdata.ShamankaChani = 1;
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen			
		case "CitizenNotBlade":
			dialog.text = RandPhraseSimple("Убирать оружие, яланауи, пока мы не заставить тебя это сделать!", "Не искушать судьбу, бледнолицый! Убери свой сабля!");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
			link.l1.go = "exit";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Мил"+ GetSexPhrase("ый","ая") +", ты куда это полез"+ GetSexPhrase("","ла") +"?! Надо же, а казал"+ GetSexPhrase("ся","ась") +" порядочн"+ GetSexPhrase("ым капитаном","ой девушкой") +".\nНу а теперь так просто тебе не уйти, красав"+ GetSexPhrase("чик","ица") +". Подрежут тебе крылышки...";
			link.l1 = "Заткнись, дура...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
