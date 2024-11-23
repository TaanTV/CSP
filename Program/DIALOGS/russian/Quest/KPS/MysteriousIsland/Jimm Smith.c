void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	ref PChar = GetMainCharacter();
	string sName = PChar.name + " " + PChar.lastname; 
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "А, это вы, капитан " + sName + ". Может, выпьем?";
			link.l1 = "Э-э, мне сейчас некогда.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "А, садись, душа-человек! Не купишь ли рома старому моряку?";
			link.l1 = "Конечно, старина, я и сам"+GetSexPhrase("","а")+" не против выпить! Трактирщик, рома!";
			link.l1.go = "exit";	
			AddDialogExitQuestFunction("MysteriousIslandTalkWithSmith");
			FreeSitLocator(PChar.location, "sit_front3");
		break;
		
		case "2":
			dialog.text = "Благодарю тебя, капитан! Я всегда рад бесплатной выпивке - ведь в этой таверне проходит большая часть моей жизни, а с деньгами у меня туговато.";
			link.l1 = "Вся жизнь в этой таверне?! Что с тобой случилось, дружище?";
			link.l1.go = "3";
		break;
		
		case "3":
			dialog.text = "А-а, не спрашивай, капитан! Это страшная история. Давай лучше выпьем!";
			link.l1 = "Трактирщик, ещё две кружки рома!";
			link.l1.go = "4";
		break;
		
		case "4":
			LAi_Fade("", "");
			dialog.text = "Ты "+GetSexPhrase("славный парень","славная деваха")+"! Когда-то и я был таким, но жизнь моя повернулась так, что сейчас я почти не сплю по ночам - меня преследуют страшные сны! Чёрт возьми... Только в роме я нахожу утешение...";
			link.l1 = "Поделись со мной своей бедою, моряк - может, полегчает на душе.";
			link.l1.go = "5";
		break;
		
		case "5":
			dialog.text = "Ну слушай, раз так сам"+GetSexPhrase("","а")+" решил"+GetSexPhrase("","а")+". Когда-то я плавал на пиратском фрегате 'Морская звезда' у капитана Деви Форсера. Однажды мы причалили к одному необитаемому острову. Капитан повёл нас в пещеру - вот это была пещера, я тебе доложу - сундуки там ломились от всякого добра! Ну, мы нахапали сколько смогли и назад, на корабль. Хватились, а капитана нашего нет. Поискали его везде, нет и всё тут. Мы подумали, что он погиб и решили плыть сами\nВышли в море, и вдруг такое началось! Страшный шторм, ветер ураганный - я такого в жизни не видел! Корабль наш в щепки разнесло, а из матросов спаслось только четверо - выбросило волнами на берег. Один из спасшихся рассказал, что перед бурей зашёл в капитанскую каюту, поискать себе выпивку, и увидел на столе карту. Ну, он и прихватил её с собой на всякий случай. Карту мы разделили на две части - решили собрать команду и снова вернуться сюда.";
			link.l1 = "Как же ты выбрался оттуда?";
			link.l1.go = "6";
		break;
		
		case "6":
			dialog.text = "Решили мы оставить всё золото, что у нас было, на острове - положили всё назад. Страх на нас напал - по ночам стала являться всякая нечисть индейской наружности, грозились, ужас нагоняли - страшное дело. В общем, вернули мы золото и стали делать ялик - слава богу, среди нас оказался плотник, да и инструмент кое-какой на берег повыбрасывало.. Вот такая моя история, капитан... Вернулся я домой, а жить спокойно не могу. Вот и топлю свои страхи в роме.";
			link.l1 = "Вот так история! А карта та где?";
			link.l1.go = "7";
		break;
		
		case "7":
			TakeNItems(PChar, "MysteriousIsland_MapChapter", 1);
			dialog.text = "Да на, забирай!";
			link.l1 = "А где остальное?";
			link.l1.go = "8";
		break;
		
		case "8":
			dialog.text = "Ну где, у подельников моих, если они ещё живы. Ступай. Капитан, растревожил"+GetSexPhrase("","а")+" ты меня, аж душу выворачивает.";
			link.l1 = "Ну, счастливо тебе, моряк!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandToBarmen");
		break;
		
		case "9":
			dialog.text = "Мне сказали, что я обязан вам своей свободой?!";
			link.l1 = "Да, Диего, мне необходимо было поговорить с тобой!";
			link.l1.go = "10";
		break;
		
		case "10":
			dialog.text = "Ах вот в чём дело! Однако, мне повезло. Если вам не жалко 1000 монет для старого пьяницы, я тут же отдам его вам.";
			if(sti(PChar.money) >= 1000)
			{
				AddMoneyToCharacter(PChar, -1000);
				link.l1 = "Вот деньги, Диего. Давай сюда часть карты!";
				link.l1.go = "11";			
			}
			else
			{
				link.l1 = "Давай сюда часть карты! Иначе, сейчас отправишься обратно.";
				link.l1.go = "11";			
			}
		break;

		case "11":
			TakeNItems(PChar, "MysteriousIsland_MapChapter", -1);
			TakeNItems(PChar, "MysteriousIsland_Map", 1);
			dialog.text = "Возьмите, сеньор"+GetSexPhrase("","ита")+". Я догадываюсь о том, что вы задумали, и искренне советую отказаться от этой затеи.";
			link.l1 = "Прощай, Диего. Желаю тебе удачи.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandFirstVisit");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}