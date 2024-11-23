
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//Скипаем с отравления три дня. ГГ приходит в себя в комнате таверны. Запись в СЖ: «Неожиданно. Но предсказуемо. Флинт поимел нас всех. Кто бы мог подумать. Хорошо, что жив(ва) остался(лась)! Нужно разобраться в происходящем. Дьявол, как же мутит то!»

		//Далее, Вейна нет на Багамах. Спускаемся в таверну. Подходит Макс

		case "BS_F3_1":	//Максин
			LAi_SetActorType(npchar);
			dialog.text = "Очнул"+ GetSexPhrase("ся","ась") +" наконец, ты дольше всех в отключке был"+ GetSexPhrase("","а") +".";
			link.l1 = "Все живы? Что нового?";
			link.l1.go = "BS_F3_2";
		break;

		case "BS_F3_2": //Максин
			dialog.text = "Все живы, он подмешал белладонну в вино. Инес отпаивала нас всех, какой то дрянью из древесного угля и Бог знает чего ещё. Заблевали всё вокруг, но выжили.";
			link.l1 = "Обязательно отблагодарю её как-нибудь. Так какие новости? Флинт? Золото?";
			link.l1.go = "BS_F3_3";
		break;

		case "BS_F3_3":	//Максин
			dialog.text = "Ни Флинта, ни золота. На складе только один сундук с дублонами, там примерно по пятьдесят тысяч на всех. И записка. «Простите, поделите это и забудьте про 'Урку' и Флинта. Так нужно. Всё равно вам не понять. Ф.»";
			link.l1 = "Чёртов ханжа! А я почти поверил"+ GetSexPhrase("","а") +" в его 'дружбу'. Где остальные?";
			link.l1.go = "BS_F3_4";
			AddMoneyToCharacter(PChar, 50000);
		break;

		case "BS_F3_4":	//Максин
			dialog.text = "Элеонора у себя, с ней Рекхэм и Бонни, все трое злые как черти. Постоянно что–то бьют и орут друг на друга. Вейн как только встал на ноги, поднял паруса и умчался куда-то";
			link.l1 = "Думаю, в резиденцию пока лучше не соваться. Пойду, подышу воздухом.";
			link.l1.go = "BS_F1_9exit";
		break;
		
		case "BS_F1_9exit":	//Максин
			DialogExit();
			PChar.quest.BS_SentJonsTavernAgentDialugue.win_condition.l1 = "location";
			PChar.quest.BS_SentJonsTavernAgentDialugue.win_condition.l1.location = "SentJons_tavern";
			PChar.quest.BS_SentJonsTavernAgentDialugue.function = "BS_SentJonsTavernAgentDialugue";
			pchar.BSLookingForAgentDialugue = true;
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddQuestRecord("BSHangover", "21");
		break;

		//Запись в СЖ: «Трудно думать, когда тебя постоянно тошнит. Но нужно что-то делать. Попробую подключить разведку. Какой там пароль? На Антигуа! В путь».

		//В таверну Сен Джонса посадить непися, который отзовётся на пароль

		//На Антигуа, идём в таверну и начинаем донимать нпс паролем «Рыбалка удалась». Ответы в духе: «Пойди проспись!», «Закусывать надо!», «Что? О чем вы?».

		//Нужный непись:

		case "BS_F3_5":	//Агент
			dialog.text = RandPhraseSimple(RandPhraseSimple("Не загораживай мне свет, мух в кружке не видно!", "Чего тебе?"), RandPhraseSimple("Похмелья не допущу - трезветь не буду!", "У тебя есть что выпить?"));
			link.l1 = "Рыбалка удалась.";
			link.l1.go = "BS_F3_6";
		break;

		case "BS_F3_6":	//Агент
			dialog.text = "Улов просто ...?";
			link.l1 = "Нет улова, удрал лосось, или угорь. Тунец? К чертям ваши игры! Есть разговор!";
			link.l1.go = "BS_F3_7";
		break;

		case "BS_F3_7":	//Агент
			dialog.text = "Кхгм. Что же... Слушаю вас.";
			link.l1 = "Организуйте мне встречу с вашим начальством. Срочно. Рыбка может совсем из рук выскользнуть, если вы понимаете, о чем я!";
			link.l1.go = "BS_F3_8";
		break;

		case "BS_F3_8":	//Агент
			dialog.text = "У меня нет таких полномочий, но информацию я передам. Как выйти с вами на связь?";
			link.l1 = "Я буду заглядывать в эту таверну, время от времени.";
			link.l1.go = "BS_F3_9";
		break;

		case "BS_F3_9":	//Агент
			npchar.location = "none";
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(PChar, "BSLookingForAgentDialugue");
			AddQuestRecord("BSHangover", "22");
			AddQuestUserData("BSHangover", "sSex", GetSexPhrase("","а"));
			pchar.quest.BS_AfterAgentMeeting.win_condition.l1          = "location";
			pchar.quest.BS_AfterAgentMeeting.win_condition.l1.location = "Nassau_OfisGatri";
			pchar.quest.BS_AfterAgentMeeting.function             = "BS_AfterAgentMeeting";
			LocatorReloadEnterDisable("Nassau_town", "houseS1", false);
			dialog.text = "Прекрасно, если не застанете меня на месте, обратитесь к подавальщице.";
			link.l1 = "Хорошо, но передайте, что время дорого. Всех благ!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Весточку отправил(ла). Нужно вернуться на Багамы и поискать Вейна. Как бы он дров не наломал".
		//Плывём на Багамы. В резиденции Гатри, Бонни, Рекхэм.


		case "BS_F3_10":	//Гатри начинает диалог.
			dialog.text = "Наш"+ GetSexPhrase("ёл","ла") +" Вейна?";
			link.l1 = "Нет. Есть идеи, куда он умчался?";
			link.l1.go = "BS_F3_10_1";
		break;
		
		case "BS_F3_10_1":
			StartInstantDialogNoType("BS_Rakham", "BS_F3_11", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_11":	//Рэкхэм.
			dialog.text = "Сказал, что вытряхнет из чёрных образин душу, поставил мне синяк под глазом и был таков.";
			link.l1 = "Образин? Всё интереснее и интереснее!";
			link.l1.go = "BS_F3_11_1";
		break;
		
		case "BS_F3_11_1":
			StartInstantDialogNoType("BS_Bony", "BS_F3_12", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_12":	//Бонни.
			dialog.text = "Флинт вёл какие-то дела с беглыми рабами. Возможно он сейчас у них.";
			link.l1 = "Есть тут хоть кто-то, с кем у него нет связей и дел?";
			link.l1.go = "BS_F3_12_1";
		break;
		
		case "BS_F3_12_1":
			StartInstantDialog("gatri_temp", "BS_F3_13", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_13":	//Гатри.
			dialog.text = "Он забил им головы идеей о свободном государстве в Новом Свете. Равные права, нет господ, мир и счастье. На деле же, использует их как пушечное мясо\nЯ говорила, что Флинт – человек жестокий и рациональный? Идеалистом его никак назвать нельзя, а тот, кто поверит его пламенным речам – станет инструментом, не более.";
			link.l1 = "(Про себя) Думаю пока не стоит им знать о моём договоре с Бонсом. (Обращаясь ко всем) Джэк, Энн. Вы остались на берегу? Предлагаю вам места в моей команде. Найдём Чарльза, разберёмся с рабами, поищем следы Флинта по их укрытиям.";
			link.l1.go = "BS_F3_13_1";
		break;
		
		case "BS_F3_13_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialogNoType("BS_Rakham", "BS_F3_14", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_14":	//Рэкхэм.
			dialog.text = "Мы бы с удовольствием, но Энн беременна. Я купил тут за гроши старую шхуну. В общем, мы решили пока отойти от дел. Осядем в Чарльзтауне у отца Энн. Займусь каботажными перевозками, ну и так, промыслом по мелочи.";
			link.l1 = "Вот, тут немного. Для молодой семьи, так сказать. Кхм... И не смейте отказываться! Что же. Удачи вам троим. Не пропадайте из виду."; //отдаём 35к 7.04.2023
			link.l1.go = "BS_F3_14_1";
		break;
		
		case "BS_F3_14_1":
			AddMoneyToCharacter(PChar, -35000);
			StartInstantDialog("gatri_temp", "BS_F3_15", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_15":	//Гатри.
			dialog.text = "Благородный жест! Но к делу. Рабы беглые, в джунглях прячутся, их буканьеры подкармливают. А значит искать их нужно или на Кубе, или на Эспаньоле. Но зачем тебе сдался Вейн? Пиратское братство? Я бы стала искать по представителям голландской Вест–Индской компании.";
			link.l1 = "У нас с Вейном, есть дело незаконченное. Никаких сантиментов. А при чём тут голландские торгаши?";
			link.l1.go = "BS_F3_16";
		break;

		case "BS_F3_16":	//Гатри.
			dialog.text = "У Флинта – узнаваемый корабль и несколько тонн испанского золота. Было бы логично разделить груз на части и отправить торговыми галеонами под военной охраной куда угодно. В Каролину, например или вообще в Бостон. Не удивлюсь, если в этом замешан мой дражайший папочка.";
			link.l1 = "Стоит проверить и это. Спасибо. Ещё что-нибудь?";
			link.l1.go = "BS_F3_17";
		break;

		case "BS_F3_17":	//Гатри.
			SetFunctionLocationCondition("BS_AfterAgentMeetingExit", "Nassau_tavern", false);
			LocatorReloadEnterDisable("Nassau_town", "houseS1", true);
			AddQuestRecord("BSHangover", "23");
			Lai_SetActorTypeNoGroup(npchar);
			dialog.text = "Максин. Увези её отсюда. Если нужно будет, то силой!";
			link.l1 = "Вот как? Хорошо. Займусь поисками. В каком направлении - понятия не имею. Слишком много вводных. До встречи.";
			link.l1.go = "BS_F3_17exit";
		break;
		
		case "BS_F3_17exit":	//Гатри.
			DialogExit();
			sld = CharacterFromID("BS_Rakham");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("BS_Bony");
			LAi_CharacterDisableDialog(sld);
			LAi_SetPlayerType(PChar);
			ChangeCharacterAddressGroup(PChar, "Nassau_OfisGatri", "goto", "goto5");
		break;	

		//Запись в СЖ: "Возможное участие отца Элеоноры? Вест-Индская торговая компания? Джек и Энн – благочестивые плантаторы? Беглые рабы и ссора Элеоноры с Макс. Ах да, ещё британская военная разведка. Не хватает только мстительных испанцев, проклятого сокровища и древнего бога местных дикарей! Ну, начнём с простого. Макс. Проверю таверну"
		//Идём в таверну. Говорим с Макс.

		case "BS_F3_18":	//Максин.
			dialog.text = "Она требует, что бы я убралась с её острова! Да после всего, что у нас было! Я...";
			link.l1 = "Тссс. Знать не желаю, что там у вас было. Я отправляюсь на поиски наших денег и мне пригодятся твои таланты по добыче информации. Поэтому, на борт! Без возражений!";
			link.l1.go = "BS_F3_18_exit";
		break;
		
		case "BS_F3_18_exit":	//Максин.
			DialogExit();
			AddQuestRecord("BSHangover", "24");
			Lai_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			SetFunctionLocationCondition("BS_HangoverMaksPortRoyalArriving", "PortRoyal_town", false);
		break;

		//Макс в пассажиры. Выходим в море.
		//Запись в СЖ: "Доставлю Максин в Порт Рояль, пусть собирает слухи. А после решу, что делать дальше"
		//Отвозим Макс в ПР. Диалог на причале.

		case "BS_F3_19":	//Максин. Вариант с отказом от секаса.
			SetFunctionLocationCondition("BS_HangoverToAntigua", "Antigua", false);
			dialog.text = "Знаешь, мы через столько прошли уже вместе, а так и не познакомились поближе. Может, отложим на вечер все дела и проведём его за бутылкой хорошего вина?";
			link.l1 = "Мне вино поперёк горла станет, если понимаешь о чём я. Сначала дело – развлечения потом! Без обид.";
			link.l1.go = "BS_F3_20";
			link.l2 = "Заманчивое предложение! Только от вина меня воротит, если понимаешь о чём я. Как насчёт рома.";
			link.l2.go = "BS_F3_21";
		break;

		case "BS_F3_20":	//Максин.
			dialog.text = "Никаких обид. До свидания капитан!";
			link.l1 = "(Про себя) А может...? Нет! Время не терпит!";
			link.l1.go = "BS_F3_20exit";
		break;
		
		case "BS_F3_20exit":	//Максин.
			DialogExit();
			chrDisableReloadToLocation = false;
			BS_ReplaceHostessWithMaks();
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", "none", "", "", "", 2.3);
			AddQuestRecord("BSHangover", "25");
		break;

		case "BS_F3_21":	//Максин. Вариант с секасом.
			dialog.text = "Пусть будет ром! Идём же!";
			link.l1 = "Идём! У меня как раз с собой есть пара-тройка бутылок!";
			link.l1.go = "BS_F3_21_exit";
		break;
		
		case "BS_F3_21_exit":	//Максин. Вариант с секасом.
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", "none", "", "", "", 2.3);
			PChar.quest.BS_IntimWithMaks.win_condition.l1 = "locator";
			PChar.quest.BS_IntimWithMaks.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.BS_IntimWithMaks.win_condition.l1.locator_group = "reload";
			PChar.quest.BS_IntimWithMaks.win_condition.l1.locator = "reload9_back";
			PChar.quest.BS_IntimWithMaks.function = "BS_IntimWithMaks";
		break;

		//В обоих вариантах запись в СЖ: "Итак, я на перепутье. Искать Вейна и лагеря беглых рабов? Или узнать, чем может помочь британский флот? Или стоит проверить версию Элеоноры с торгашами? Распыляться не стоит, банально не хватит времени на всё сразу. Отмету голландцев сразу, пусть и логично звучит, но у Компании своя разведка есть, и Флинт немало им крови попортил. Значит поиски Вейна или помощь флота. Вейн большой мальчик, думаю, что справится и без меня, значит на Антигуа!" 7.04.2023 // так как выбора уже и нет, то не забыть потереть лишее из СЖ финала_2
		//Ниже вариант помощи разведке и Бонсу.
		//Плывём на Антигуа, в локации острова запись в СЖ: "Вейн – большой мальчик, надеюсь, дров не наломает. Проверю таверну. Агент говорил, что если его не будет на месте, спросить разносчицу."

		case "BS_F3_23":	//Офицантка.
			dialog.text = "Вам что-нибудь принести, капитан?";
			link.l1 = "Нет. Дорогуша, ты не видела тут моего друга? Он большой любитель рыбалки, мы тут выпивали не так давно?";
			link.l1.go = "BS_F3_24";
		break;


		case "BS_F3_24":	//Офицантка.
			dialog.text = "Охотитесь за крупной рыбой? Он просил передать, что другой рыбак, будет ждать вас в водах Доминики у пляжа Касл Брус";
			link.l1 = "Спасибо. Вот тебе на эмм..., на что-нибудь красивое!"; //Отдаём 500 рублей
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Сбор рыбаков у Доминики. Нужно поспешить".
		//У пляжа стоит фрегат Бонса. Если решим пострелять - провал линейки. Высылаем шлюпку, разговор с Бонсом на борту.

		case "BS_F3_25":	//Бонс.
			dialog.text = "Вам бы память тренировать, капитан. Правильный пароль иногда может жизнь спасти!";
			link.l1 = "Мне плевать на ваши игры в пароли и явки. Я по делу! Флинт скрылся! Вместе с кораблём и золотом. Мы чудом выжили! По своим каналам, я зацепок не имею. Выкладывай, что есть у тебя. Может быть, вместе и поймаем твою рыбку. После чего разбежимся!";
			link.l1.go = "BS_F3_26";
		break;


		case "BS_F3_26":	//Бонс.
			dialog.text = "А как же почести? Награда? Помилование, наконец?";
			link.l1 = "На золото 'Урки', я себе хоть титул купить смогу. А благосклонность короны тоже покупается. Не томи, Билли. У меня руки чешутся кого-нибудь прирезать!";
			link.l1.go = "BS_F3_27";
		break;

		case "BS_F3_27":	//Бонс.
			dialog.text = "Начну издалека. 'Скарборо' и остальная эскадра, тут не только и не сколько для поимки Флинта и устрашения пиратов. Первоочередная задача – не дать попасть золоту с ‘Урки’ в Европу. Испания легко погасит часть своих долгов этим золотом, а это лишит влияния на них, их кредиторов. К тому же, такое количество уже отчеканенной монеты – обесценит уже имеющиеся. Так что, если золото исчезнет на Карибах – это даже лучше. То есть, никто в Европе, его искать не станет, и заявлять права на него – тоже.";
			link.l1 = "Понимаю. Политика, интриги, заговоры. Старушка Европа, всё никак не угомониться.";
			link.l1.go = "BS_F3_28";
		break;

		case "BS_F3_28":	//Бонс.
			dialog.text = "Мой формальный командир, Сэр Френсис Ньюм, капитан 'Скарборо', напыщенный болван, сын какого-то мелкого лордика. Раздаёт налево-направо патенты и помилования, вербует сторонников. Ищет, тоже, что и вы и, подозреваю, мои неудачи – его рук дело. У меня есть все основания полагать, что золото он прибрать к рукам собирается.";
			link.l1 = "Я нить теряю, Билл. Флинт, золото. Чем ты можешь мне помочь?";
			link.l1.go = "BS_F3_29";
		break;

		case "BS_F3_29":	//Бонс.
			dialog.text = "Есть непроверенная информация о стоянках 'Моржа' в разных бухтах. Возможности проверить их быстро – у меня нет. Поэтому, разделимся. Я пойду к мысу Каточе и под испанским флагом двину на юг. Ты – к бухте Бока де ла Сьерпе, и пойдёшь оттуда на запад, проверяя каждую бухту. Встречаемся у лагуны Чирике. В порты не входить, столкновений избегать. Начиная с этого дня, двух недель должно хватить.";
			link.l1 = "Ты сказал, что есть конкретная информация о стоянках! Это же нужно каждую бухту осмотреть!";
			link.l1.go = "BS_F3_30";
		break;

		case "BS_F3_30":	//Бонс.
			dialog.text = "Информатор был не очень точен в описаниях и быстро умер. Ньюм, мало того, что кретин, ещё и садист.";
			link.l1 = "Стало быть, Ньюм тоже ищет стоянки?";
			link.l1.go = "BS_F3_31";
		break;

		case "BS_F3_31":	//Бонс.		
			SetFunctionExitFromLocationCondition("BS_BonsDominicaNone", "Dominica", false);
			SetFunctionLocationCondition("BS_ShoreSeeking", "Shore18", false);
			AddQuestRecord("BSHangover", "63");
			dialog.text = "Скоро начнёт. На днях прибыл курьерский бриг из метрополии и 'Скарборо' снялся с якорей. Какие приказы получил Ньюм, я не знаю. Но это даёт нам фору.";
			link.l1 = "Значит, не будем медлить!";
			link.l1.go = "BS_F3_31exit";
		break;
		
		case "BS_F3_31exit":
			DialogExit();
			npchar.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
			npchar.dialog.currentnode = "BS_F3_31_loop";
		break;
		
		case "BS_F3_31_loop":	//Бонс.
			dialog.text = "Нужно поторопиться!";
			link.l1 = "Значит, не будем медлить!";
			link.l1.go = "BS_F3_31exit";
		break;

		//Запись в СЖ: "От Бонса-Блэкхема проку немного, нужно исследовать большой кусок побережья Мэйна. Но это хоть что-то. Начну с бухты Бока де ла Сьерпе"
		//В бухте Бока де ла Сьерпэ, на берегу пусто. Запись в СЖ: "Пусто. Продолжу поиски. Нужно исключить бухты, которые находятся в виду фортов, Флинт не стал бы так рисковать. Сверюсь с картой. Ага, остаются: Пляж Лос Текес, бухта Гуахира, бухта Ковеньяс, залив Москитос. Что же, в путь."
		//В Лос Текес – пара агрессивных английских фрегатов. Бой. Высадка. На берегу штук 30 военных – файт. Запись в СЖ: "Похоже люди Ньюма. Ищут зацепки на месте гибели 'Урки'. Нужно быть настороже". //игрок может и не высадиться в бухте. нужна принудиловка ! 7.04.2023
		//Москитос. На берегу подбегает матрос.

		case "BS_F3_32":	//Матрос.
			dialog.text = "Капитан " + GetFullName(pchar) + "? Я от коллеги по рыбалке!";
			link.l1 = "Билли всё никак не наиграется? Что там у тебя?";
			link.l1.go = "BS_F3_33";
		break;

		case "BS_F3_33":	//Матрос.
			dialog.text = "Срочно прибудьте в Бриджтаун! Поиски потерпят. Так он сказал.";
			link.l1 = "И это всё? Что за срочность?";
			link.l1.go = "BS_F3_34";
		break;


		case "BS_F3_34":	//Матрос.
			dialog.text = "Понятия не имею, "+ GetSexPhrase("сэр","мэм") +", я просто посыльный!" ;
			link.l1 = "Хорошо, я понял"+ GetSexPhrase("","а") +".";
			link.l1.go = "BS_F3_34exit";
		break;
		
		case "BS_F3_34exit":	//Матрос.
			AddQuestRecord("BSHangover", "66");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 3.0);
			SetFunctionLocationCondition("BS_BridgetownBonsAlarm", "Bridgetown_town", false);
			DialogExit();
		break;

		//Запись в СЖ: "Что-то произошло. Бонс требует срочно прибыть в Бриджтаун."
		//Плывём на Барбадос. В городе подходит Бонс.

		case "BS_F3_35":	//Бонс.
			dialog.text = "Ты здесь. Хорошо. Власти Барбадоса просят помощи, их гарнизон до сих пор не укомплектован после набега испанцев. И 'Скарборо' неизвестно где.";
			link.l1 = "Что стряслось то? Я, кстати, наткнул"+ GetSexPhrase("ся","ась") +" на пляже Лос-Текес на людей Ньюма. Рылись в обломках 'Урки'.";
			link.l1.go = "BS_F3_36";
		break;

		case "BS_F3_36":	//Бонс.
			dialog.text = "Много они там не нароют. На плантации, расположенные на острове, планируется нападение. Сегодня, завтра, скоро. И возглавит нападение, не поверишь кто. Сам Флинт!";
			link.l1 = "За каким дьяволом ему это нужно?";
			link.l1.go = "BS_F3_37";
		break;

		case "BS_F3_37":	//Бонс.	
			dialog.text = "Где-то в колониях он создаёт армию из каторжан и беглых рабов, а тут королевская каторга. Головорезы всех мастей, вооружай и готово. Вот для чего ему испанское золото. И делиться им, он не намерен. В местном гарнизоне одни новобранцы и ополчение из колонистов. Они разбегутся кто-куда при первых залпах. Но если мы объединим наши команды, то сможем дать ему отпор и, даст бог, схватить его самого!";
			link.l1 = "Устроим засаду? Что же, это может сработать. Собирай людей, встретимся на плантации!";
			link.l1.go = "BS_F3_37exit";
		break;
		
		case "BS_F3_37exit":
			AddQuestRecord("BSHangover", "67");
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			SetFunctionLocationCondition("BS_BridgetownPlantationPrepare", "Bridgetown_Plantation", false);
			pchar.BS_PlantationBattle = true;
			PChar.quest.BS_ReloadToPlantation.win_condition.l1 = "locator";
			PChar.quest.BS_ReloadToPlantation.win_condition.l1.location = "Bridgetown_town";
			PChar.quest.BS_ReloadToPlantation.win_condition.l1.locator_group = "reload";
			PChar.quest.BS_ReloadToPlantation.win_condition.l1.locator = "gate1_back";
			PChar.quest.BS_ReloadToPlantation.function = "BS_ReloadToPlantation";
			LAi_MethodDelay("BS_BridgetownPlantationOrders",0.1);
			DialogExit();
		break;

		//Запись в СЖ: "Предстоит жаркое дельце. Флинт собирается освободить каторжан для своей армии. Отличная возможность прихлопнуть ублюдка. Но, всё же стоит помнить, с кем мы имеем дело. Устроим засаду на плантации".
		//Идём на плантацию. Там бродят наши в перемешку с английскими солдатами, заходим за калитку плантации. Вывести лог «Засада организована! Всем быть на готове!» Начинаем спаунить пиратов от ворот. В три-четыре волны.
		//Перебили всех, Бонс орёт : «Они с полей прут, ещё больше! Стрелки, к бою!»
		
		case "BS_F3_PlantOfficer":
			dialog.text = "Капитан, по вашему приказу, засада организована.";
			link.l1 = "Хорошо.";
			link.l1.go = "BS_F3_PlantOfficerexit";
		break;
		
		case "BS_F3_PlantOfficerexit":	
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, false);
			Group_AddCharacter(LAI_GROUP_PLAYER, npchar.id);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("BS_BridgetownPlantationBattleStart", 30.0);
			DialogExit();
		break;	
		
		case "BS_F3_38":	//Бонс.
			dialog.text = "Они с полей прут, ещё больше! Стрелки, к бою!";
			link.l1 = "За мной!";
			link.l1.go = "BS_F3_38tobattle";
		break;
		
		case "BS_F3_38tobattle":	//Бонс.
			BS_BridgetownPlantationReinforcement_2();
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		//Спауним пиратов прям на плантации. Перебили.

		case "BS_F3_39":	//Бонс.
			dialog.text = "Где, чёрт его дери Флинт?";
			link.l1 = "Это ещё не конец! Слышишь? Пушки стреляют! Ложись!";
			link.l1.go = "exit";
		break;

		//Нужна пара взрывов где-нибудь. От ворот ещё толпа пиратов. С ними Флинт и Вейн. Пока живы их пираты - Ф и В бессмернтые. Как только полегли все пираты Флинт начинает диалог.

		case "BS_F3_40Flint_1":	//Флинт.
			dialog.text = "Вейн! Отступаем, идут подкрепления из форта!";
			link.l1 = ""; //Вейн
			link.l1.go = "BS_F3_40Vein_1";
		break;
		
		case "BS_F3_40Vein_1":
			StartInstantDialog("BS_Vein", "BS_F3_40Vein_2", "Quest\BlackSails\BS_Final_3.c");
		break;
		
		case "BS_F3_40Vein_2":	//Флинт.
			dialog.text = "Я прикрою, уходи!";
			link.l1 = ""; //Вейн
			link.l1.go = "BS_F3_40Bons_1";
		break;
		
		case "BS_F3_40Bons_1":	//Флинт.
			StartInstantDialog("BSBons", "BS_F3_40Bons_2", "Quest\BlackSails\BS_Final_3.c");
		break;


		case "BS_F3_40Bons_2":	//Флинт.
			dialog.text = "Я понимаю. "+pchar.name+", ты не на той стороне сражаешься! Но это твой выбор." ; //Убегает.
			link.l1 = "Я за Флинтом. Нельзя его упустить!"; //Бонс. Убегает.
			link.l1.go = "BS_F3_40Vein_3";
		break;
		
		case "BS_F3_40Vein_3":
			sld = CharacterFromID("Flint");
			Group_AddCharacter(LAI_GROUP_NEITRAL, sld.id);
			LAi_group_MoveCharacter(sld, LAI_GROUP_NEITRAL);
			Lai_SetActorTypeNoGroup(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 10.0);
			StartInstantDialog("BS_Vein", "BS_F3_40Vein_4", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_40Vein_4":	//Вейн.
			sld = CharacterFromID("BSBons");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			dialog.text = "Ну что? Только ты и я?!" ;
			link.l1 = "Какого чёрта Чарльз? У нас же был уговор!";
			link.l1.go = "BS_F3_42";
		break;

		case "BS_F3_42":	//Вейн.
			dialog.text = "Ты слишком часто меняешь стороны. А твои новые друзья убили Элеонору!";
			link.l1 = "Как?! Когда?";
			link.l1.go = "BS_F3_43";
		break;

		case "BS_F3_43":	//Вейн.
			dialog.text = "'Скарборо' пришёл на Багамы, пока я искал Флинта, и устроил там зачистку. Элеонору отвезли в цепях в Порт-Рояль и повесили в порту. Максин в тюрьме и её скоро тоже повесят. Джэк – в тюрьме Чарльзтауна, но он выкрутится. Энн помилована. Гуманный суд решил, что вешать беременную женщину, хоть и пирата – это через чур. А ты стал" + GetSexPhrase("","а") +" собачкой,  вынюхивающей испанское золото для английской разведки";
			link.l1 = "Тебе это Флинт рассказал? Он умеет играть с мозгами!";
			link.l1.go = "BS_F3_44";
		break;

		case "BS_F3_44":	//Вейн.
			dialog.text = "Я видел её тело. Её в клетку поместили, чтоб не развалилась при разложении. Так и висит возле пристани. Хватит болтать! Отсюда кто-то один уйдёт!" ;
			link.l1 = "В этом нет моей вины, Чарльз. Но тебя не переубедить. Начинай как будешь готов!";
			link.l1.go = "BS_F3_44VeinFight";
		break;
		
		case "BS_F3_44VeinFight":	//Вейн.
			DialogExit();
			BS_RestoreMaksHostess();
			BS_QuestCleaning(false);
			DoQuestFunctionDelay("BS_BridgetownPlantationVeinFight", 5.0);
		break;
		
		//Рубимся с Вейном. Убиваем. Страдаем, какой автор гнида. Идём в город. Подбегает Сильвер.

		case "BS_F3_45":	//Сильвер.
			dialog.text = "Эй, "+pchar.name+", на тебе лица нет! Что там было? Это Флинт?" ;
			link.l1 = "Заткнись, Джон. Как ты тут очутился?";
			link.l1.go = "BS_F3_46";
		break;

		case "BS_F3_46":	//Сильвер.
			dialog.text = "Удрал от Флинта, когда он начал хвосты подчищать. Всю старую команду вырезал!";
			link.l1 = "Я думаю нагнать его в море. Ты со мной?";
			link.l1.go = "BS_F3_47";
		break;

		case "BS_F3_47":	//Сильвер.
			dialog.text = "Флинта?! Нет! Да! Да, думаю, с тобой безопаснее будет. Я тут у шлюх под юбками прячусь уже неделю!" ;
			link.l1 = "Тогда в море!";
			link.l1.go = "BS_F3_47exit";
		break;
		
		case "BS_F3_47exit":	//Сильвер.
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("BSHangover", "68");
			AddQuestUserData("BSHangover", "sSex", GetSexPhrase("","а"));
			Lai_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5.0);
			SetFunctionLocationCondition("BS_Hangover_BarbadosRangerSeaBattle", "Barbados", false);
			Pchar.BonsFlintRunning = true;
			SetFunctionTimerConditionParam("BS_Hangover_CapeCatocheBattle", 0, 0, 5, 0, false);
			SetFunctionTimerConditionParam("BS_SecondFinalEndingTimeOutFail", 0, 0, 14, 0, false);
			BS_Hangover_ChaseFromBarbados();		
		break;

		//Запись в СЖ: "Вейн. Чёрт тебя дери. Ты был мне другом! И Бонс, чёртов Бонс. Пока я искал(ла) непойми что, англичане устроили зачистку. Гатри мертва. Всё катиться в бездну! Осталось поквитаться с Флинтом и плевать, что будет дальше!"
		//Выходим в море, нас атакует «Рейнджер». Топим. Выходим на глобалку. От нас по съёбам удирает квестовик-энка (типо Флинт с Бонсом). Нужно скорости им накрутить, чтоб мы только-только угнаться могли. Энка пиздует к мысу Каточе и там исчезает. Выходим на локалку. Там фрегат Бонса гасится с Моржом (Бонс зелёненький). Берём Моржа на абордаж. В каюте рубилово с Флинтом. Нулим Флинта. Диалог
		//Диалог после боя в каюте Моржа, ниже 7.04.2023																	   


		case "BS_F3_48":	//Флинт.
			dialog.text = "Вейн мёртв? Жаль, но он был слишком эмоционален. А ты принял" +GetSexPhrase("","а")+" предложение английских властей? Помилование, патент, королевские милости? Ты же понимаешь, что они легко дают обещания и так же легко забирают их обратно. Я был одним из них!";
			link.l1 = "...";
			link.l1.go = "BS_F3_49";
		break;

		case "BS_F3_49":	//Флинт.
			dialog.text = "Вот только не нужно жечь меня взглядом. На меня это не действует.  Есть ещё способы всё уладить. Захватим фрегат Бонса, далее под английскими флагами и с помощью его сигнальной книги, заманим в ловушку 'Скарборо'. Таким образом, избавимся от внимания военной разведки, у них сейчас и без нас забот полон рот. Далее ...";
			link.l1 = "Вот так у тебя голова устроена? Планы, внутри планов? Нет друзей, нет врагов. Есть только инструменты и помехи. Ты вообще человек?";
			link.l1.go = "BS_F3_50";
		break;

		case "BS_F3_50":	//Флинт.
			dialog.text = "Эмоции неуместны, мораль – признак слабости, компромиссы – путь к посредственности. Мои цели – новый мир. А что бы построить новый, нужно сломать старый. Ты мог" + GetSexPhrase("","ла") +" бы быть полезным инструментом, но я вижу иррациональные чувства, которые помешают твоей эффективности. Так и быть. Это будет чуточку труднее, но нет ничего невозможного!";
			link.l1 = "Просто заткнись и сдохни!";
			link.l1.go = "BS_F3_50exit";
		break;

		case "BS_F3_50exit":	//Флинт.
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar);
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			SetFunctionExitFromLocationCondition("BS_Hangover_CapeCatocheBattleOver", pchar.location, false);
			SetFunctionLocationCondition("BS_Hangover_CapeCatocheDialogue", "Shore6", false);
			Log_Info("Ваше внимание привлекает книга - Марк Аврелий 'Размышления'. Вы забираете её, вместе с судовым журналом Флинта.");
		break;

			
		//Файт. На трупе Нарвал, книга Марк Аврелий «Размышления». В сундуке 5кк денег, судовой журнал Флинта (зашифрованый).
		//Как только закрываем окно захвата корабля - СЮРПРИЗ. Спаун "Скарборо" с парой фрегатов. Бой, без диалогов в случае захвата. 7.04.2023 //если не получится такой спавн, то по старинке - спавн на глобалке
		//После победы ТП на берег. Скотс Хэд или второй пляж - не важно 7.04.2023 Фрегат Бонса удаляем, он потонул. На берегу Бонс, Сильвер, ГГ.
		
		case "BS_F3_50BonsDeck":	//Флинт.
			dialog.text = "Наконец разделаемся с этим ублюдком!";
			link.l1 = "Да!";
			link.l1.go = "BS_F3_50BonsDeckexit";
		break;
		
		case "BS_F3_50BonsDeckexit":
			DialogExit();
			npchar.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
			npchar.dialog.currentnode = "BS_F3_50BonsDeck_loop";
		break;
		
		case "BS_F3_50BonsDeck_loop":	//Бонс.
			dialog.text = "Наконец разделаемся с этим ублюдком!";
			link.l1 = "Да!";
			link.l1.go = "BS_F3_50BonsDeckexit";
		break;
		
		case "BS_F3_51":	//Сильвер.
			dialog.text = "Флинт мёртв?";
			link.l1 = "Мёртв.";
			link.l1.go = "BS_F3_52_1";
		break;
		
		case "BS_F3_52_1":
			LAi_SetStayTypeNoGroup(npchar);
			npchar.dialog.filename = "Quest\BlackSails\BS_Final_3.c";
			npchar.dialog.currentnode = "BS_F3_54";
			StartInstantDialog("BSBons", "BS_F3_52", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_52":	//Бонс.
			dialog.text = "Хех. Жаль. Живым его в Лондоне очень рады были бы видеть.";
			link.l1 = "После всего, что было, думаю ТЕБЕ, в Лондоне будут тоже рады!";
			link.l1.go = "BS_F3_53";
		break;

		case "BS_F3_53":	//Бонс.
			dialog.text = "Думаю, да. Френсис Ньюм, эсквайр, погиб как герой, а какой-то коммандер – выжил. Мне совсем не хочется отвечать на вопросы, которые возникнут!" ;
			link.l1 = "Вы, двое! Вот бумаги Флинта, зашифрованные. Разберётесь? А я тут прилягу и отдохну. Устал" + GetSexPhrase("","а")+" убивать."; //Отдаём книгу, журнал.
			link.l1.go = "BS_F3_53exit";
		break;
		
		case "BS_F3_53exit":	//Бонс.
			DialogExit();
			Lai_SetActorTypeNoGroup(npchar);
			WaitDate("",0,0,0,10,0);
			AddQuestRecord("BSHangover", "69");
			AddQuestUserData("BSHangover", "sSex", GetSexPhrase("","а"));
			SetLaunchFrameFormParam("Прошло десять часов", "", 0.1, 3.0);
			DoQuestFunctionDelay("SilverSpeech", 3.0);
			LaunchFrameForm();
		break;

		//Запись в СЖ: "Где-то на этом пути я сделал(ла) неправильный выбор. Какой момент стал поворотным? Элеонора, Чарльз. Как бы сложились их судьбы, прими я другие решения? Стал(ла) бы я бездушной машиной под руководством Флинта? Чёрт, как голова болит! Нужно отдохнуть".
		//Ставим табличку "Прошло десять часов", мотаем время.

		case "BS_F3_54":	//Сильвер.
			dialog.text = "Эй! Ты жив" + GetSexPhrase("","а") +"? Храпеть ты мастер!";
			link.l1 = "Что? Как успехи?";
			link.l1.go = "BS_F3_55_1";
		break;
		
		case "BS_F3_55_1":
			StartInstantDialog("BSBons", "BS_F3_55", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_55":	//Бонс.
			dialog.text = "Два листа координат. Широта, долгота. Всё. Никаких 'Семь шагов от засохшего дерева', ничего!" ;
			link.l1 = "Как думал этот дьявол, как у него голова устроена – это непостижимо.";
			link.l1.go = "BS_F3_56";
		break;

		case "BS_F3_56":	//Бонс.
			dialog.text = "Возможно это маршрут? Только где начало и конец? Тут сотни точек на карте! Должна быть связь! Должна! Нужно только подумать, перечитать чёртову книгу, должно что-то быть!" ;
			link.l1 = "Куда вас доставить?";
			link.l1.go = "BS_F3_57_1";
		break;
		
		case "BS_F3_57_1":
			StartInstantDialog("BS_Silver", "BS_F3_57", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_57":	//Сильвер.
			dialog.text = "Что? Ты сдаёшься?";
			link.l1 = "Пуэрто-Присипе? Мы недалеко от Кубы.";
			link.l1.go = "BS_F3_58_1";
		break;
		
		case "BS_F3_58_1":
			StartInstantDialog("BSBons", "BS_F3_58", "Quest\BlackSails\BS_Final_3.c");
		break;

		case "BS_F3_58":	//Бонс.
			dialog.text = "Да, Пуэрто-Присипе подойдёт. У меня есть тайничок там. На первое время хватит." ;
			link.l1 = "Тогда в путь.";
			link.l1.go = "BS_F3_58exit";
		break;
		
		case "BS_F3_58exit":	//Бонс.
			DialogExit();
			DeleteAttribute(pchar, "BSBonsAccept");
			DeleteAttribute(pchar, "BonsFlintRunning");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);			
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			pchar.BSBonsSpawned = true;
			BSBons_SeaBattle(true);
			SetFunctionLocationCondition("BS_CubaSilverOut", "PuertoPrincipe_port", false);
			DeleteAttribute(PChar, "currentsoundtrack");
			string shore = "Shore6";
			Locations[FindLocation(shore)].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation(shore)], false);
			LAi_LocationDisableOfficersGen(shore, false);
		break;

		//Везём братву на Кубу. В бухте Ла Франсуа подходит Сильвер.

		case "BS_F3_59":	//Сильвер.
			dialog.text = "Я присмотрю за Билли, сдаётся мне, он не в себе. А ты куда?";
			link.l1 = "Попытаюсь спасти Макс. Наведаюсь в тюрьму. Хоть что-то сделаю правильно. Удачи, Джон!";
			link.l1.go = "BS_F3_59exit";
		break;
		
		case "BS_F3_59exit":	//Сильвер.
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto6", "none", "", "", "", -1);
			pchar.ToHelpMaksInPortRoyal = true;
		break;

		//Плывём в Порт Рояль, идём в тюрягу, комендант.

		case "BS_F3_60":	//Комендант.
			dialog.text = "Вы по какому вопросу?";
			link.l1 = "Я хотел" +GetSexPhrase("","а")+" поинтересоваться судьбой одной особы. Максин.";
			link.l1.go = "BS_F3_61";
		break;

		case "BS_F3_61":	//Комендант.
			dialog.text = "Ааа, мадам! Всё с ней в порядке. Подержали в клетке пару дней, потом пришёл посыльный от самого губернатора с помилованием. И отпустили с Богом!";
			link.l1 = "Благодарю вас.";
			link.l1.go = "exit";
		break;

		//Идём в бордель. Комната мадам.

		case "BS_F3_62":	//ГГ
			dialog.text = "" ;
			link.l1 = "Я и не надеял" +GetSexPhrase("ся","ась")+" увидеть тебя живой!";
			link.l1.go = "BS_F3_63";
		break;
		
		case "BS_F3_63":	//ГГ
			dialog.text = "Мой капитан! Пока мои девочки собирают слухи, мне ничего не грозит. Я щедро делюсь ими и с властями, и с корсарами. Каждый готов постоять за меня.";
			link.l1 = "Что же. Тогда моя миссия завершена. Вот, твоя доля, компаньон. Здесь всё, что удалось обнаружить из золота 'Урки'";
			link.l1.go = "BS_F3_64";			
		break;

		case "BS_F3_64":	//ГГ.
			dialog.text = "Не стану отказываться. Тем более предстоят расходы. Я добилась разрешения похоронить по-человечески Элеонору. И вышлю денег Энн. Ты слышал" + GetSexPhrase("","а") +" про Джека?.";
			link.l1 = "Да. Флинт мёртв, Вейн мёртв.";
			link.l1.go = "BS_F3_65";
			if (sti(pchar.money) >= 1000000)
			{
				pchar.makslover = true;
				SaveCurrentQuestDateParam("MaksLoverDateDay");
			}
			AddMoneyToCharacter(PChar, -1000000);
		break;

		case "BS_F3_65":	//ГГ.
			dialog.text = "История подошла к концу?" ;
			link.l1 = "Эта история, да. Есть ещё много нерассказанных историй. Прощай Макс!";
			link.l1.go = "BS_F3_66";
		break;

		case "BS_F3_66":	//ГГ.
			SetFunctionLocationCondition("BS_PortRoyalSilver", "PortRoyal_town", false);
			RestoreOldDialog(npchar);
			dialog.text = "Навещай меня, капитан, время от времени.";
			link.l1 = "Обязательно!";
			link.l1.go = "exit";
		break;

		//Уходим в закат. Макс – остаётся в роли мадам, с бесплатными потрахушками. Можно ей добавить слухов по «Лёгкой добыче».
		//На выходе из борделя – подбегает Сильвер


		case "BS_F3_67":	//Сильвер.
			dialog.text = "Бонс нашёл связь! Это и вправду маршрутные точки! И только у него есть карта!";
			link.l1 = "Карта острова сокровищ капитана Флинта?";
			link.l1.go = "BS_F3_68";
		break;


		case "BS_F3_68":	//Сильвер.
			dialog.text = "Да! Но он удрал. Растворился. Исчез вместе с картой! Нужно найти его!" ;
			link.l1 = "Это уже твоя история, Джон. Вот тебе немного. Купи себе лоханку и гонись за Билли Бонсом хоть в Англию!"; //отдаём 25к
			link.l1.go = "BS_F3_69";
		break;

		case "BS_F3_69":	//Сильвер.
			dialog.text = "Но... Ты уверен" +GetSexPhrase("","а")+"?! Вижу, что, да. Я найду тебя, обязательно! Ох и попируем мы на денюжки Флинта!" ;
			link.l1 = "Проваливай Сильвер!";
			link.l1.go = "BS_F3_69exit";
			AddMoneyToCharacter(PChar, -25000);
		break;
		
		case "BS_F3_69exit":	//Сильвер.
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto4", "none", "", "", "", 2.0);
			DoQuestFunctionDelay("BS_SecondFinalEndingQuest", 3.0);
			SetMusic("Theme_from_Black_Sails");
		break;

		//Квест уходит в архив.
	}
}
