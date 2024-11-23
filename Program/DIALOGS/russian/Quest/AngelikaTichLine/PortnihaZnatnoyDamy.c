void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
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
		
////////////////////////////////////////////////////////////////////////////////////////////////
// Анжелика Тич: "Портниха знатной дамы"			Авторы: Nikk и Sinistra
////////////////////////////////////////////////////////////////////////////////////////////////		
		
		case "First time":
			dialog.text = "Сообщите Синистре о баге";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "AT_PZD_Pilar_1_1":
			dialog.text = "";
			link.l1 = "Ребекка?";
			link.l1.go = "AT_PZD_Pilar_1_2";
			DeleteAttribute(npchar, "talker");
		break;

		case "AT_PZD_Pilar_1_2":
			dialog.text = "Прошу прощения?";
			link.l1 = "Как... Кажется, я ошиблась. Перепутала вас с одной своей знакомой.";
			link.l1.go = "AT_PZD_Pilar_1_3";
		break;

		case "AT_PZD_Pilar_1_3":
			dialog.text = "И я это уже прекрасно поняла. Теперь, прошу, отойдите от меня.";
			link.l1 = "Конечно, конечно. Но мне бы только хотелось узнать, кто вам сшил платье? Из-за него мне и показалось, что вы та самая девушка.";
			link.l1.go = "AT_PZD_Pilar_1_4";
		break;

		case "AT_PZD_Pilar_1_4":
			dialog.text = "Чепуха.";
			link.l1 = "";
			link.l1.go = "AT_PZD_Pilar_1_5";
		break;

		case "AT_PZD_Pilar_1_5":
			dialog.text = "Гарберд, для чего вы здесь стоите?";
			link.l1 = "";
			link.l1.go = "AT_PZD_Pilar_1_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("AT_PZD_Herineldo"));
		break;

		case "AT_PZD_Pilar_1_6":
			DialogExit();
			StartInstantDialog("AT_PZD_Herineldo", "AT_PZD_Pilar_1_7", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
			sld = CharacterFromID("AT_PZD_Pilar");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);			
		break;

		case "AT_PZD_Pilar_1_7":
			dialog.text = "Сеньорита, я вынужден настоять.";
			link.l1 = "Не утруждайте себя!";
			link.l1.go = "AT_PZD_Pilar_1_8";
		break;

		case "AT_PZD_Pilar_1_8":
			DialogExit();
			
			sld = CharacterFromID("AT_PZD_Pilar");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("AT_PZD_Herineldo");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, CharacterFromID("AT_PZD_Pilar"), "", -1);
			sld.lifeday = 0;
			
			sld = CharacterFromID("AT_PZD_R1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, CharacterFromID("AT_PZD_Pilar"), "", -1);
			sld.lifeday = 0;
			
			SetQuestHeader("AT_PZD");
			AddQuestRecord("AT_PZD", "1");
			LocatorReloadEnterDisable("Marigo_town", "reload3_back", true);
			LocatorReloadEnterDisable("Marigo_town", "reloadR2", true);
			
			PChar.quest.AT_PZD_ProvalMissii.win_condition.l1 = "MapEnter";
			PChar.quest.AT_PZD_ProvalMissii.win_condition = "AT_PZD_ProvalMissii";
			
			pchar.questTemp.AT_PZD_taverna = true;
			pchar.questTemp.AT_PZD_PU = true;
		break;
		
		case "AT_PZD_MatrosUKostra_1":
			locCameraFromToPos(43.47, 3.58, -6.19, true, 32.50, 0.20, 0.00);
			TeleportCharacterToPosAy(pchar, 39.58, 0.02, -4.80, -0.40);
			dialog.text = "...(не замечая нас)... А я ему и говорю, что он наивный дурак, раз верит в эти слухи, что якобы я обнимался с чёрным медведем... Да не было такого\nА тебе чего надо?";
			link.l1 = "Отдыхаете, работники? Есть разговор.";
			link.l1.go = "AT_PZD_MatrosUKostra_2";
		break;
		
		case "AT_PZD_MatrosUKostra_2":
			dialog.text = "Вы это, барышня, верно подметили. Отдыхаем\nЕсли хотите предложить работу, приходите завтра... Или нет, лучше через 2 дня. На завтра у нас уже есть наниматель, или предлагайте большую цену.";
			link.l1 = "Мне нужно прямо сейчас. 2000 монет за простой разговор, идёт?";
			link.l1.go = "AT_PZD_MatrosUKostra_3";
		break;
		
		case "AT_PZD_MatrosUKostra_3":
			dialog.text = "По рукам. Выкладывайте, только деньги вперёд, а мы уж подскажем, что знаем.";
			if (sti(pchar.Money) >= 2000)
			{
				link.l1 = "Держи.";
				link.l1.go = "AT_PZD_MatrosUKostra_4";
			}
			link.l2 = "Я кошелёк в каюте оставила, скоро вернусь.";
			link.l2.go = "AT_PZD_MatrosUKostra_3_0";
		break;
		
		case "AT_PZD_MatrosUKostra_3_0":
			DialogExit();
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("AT_PZD_Matros"+i);
				sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
				sld.dialog.currentnode = "AT_PZD_MatrosUKostra_3_1";
			}
		break;
		
		case "AT_PZD_MatrosUKostra_3_1":
			dialog.text = "Ну что, барышня, принесла 2000 монет?";
			if (sti(pchar.Money) >= 2000)
			{
				link.l1 = "Держи.";
				link.l1.go = "AT_PZD_MatrosUKostra_4";
			}
			link.l2 = "Ещё нет, скоро вернусь.";
			link.l2.go = "exit";
			NextDiag.TempNode = "AT_PZD_MatrosUKostra_3_1";
		break;
		
		case "AT_PZD_MatrosUKostra_4":
			dialog.text = "Отлично, так что ты хотела узнать?";
			link.l1 = "Меня интересует женщина аристократка, которая сошла с одного из испанских кораблей. Прогуливалась недавно по набережной в сопровождении солдат, на ней была широкополая шляпа, сложно не заметить.";
			link.l1.go = "AT_PZD_MatrosUKostra_5";
		break;
		
		case "AT_PZD_MatrosUKostra_5":
			dialog.text = "Её светлость, поди, по мостовой изволила гулять, а мы от зари до заката в порту пашем. К губернатору тебе, морячка, нужно с такими вопросами, только он таких как ты не принимает.";
			link.l1 = "Я капитан собственного судна, примет по долгу службы.";
			link.l1.go = "AT_PZD_MatrosUKostra_6";
		break;
		
		case "AT_PZD_MatrosUKostra_6":
			dialog.text = "То-то и оно. У них там балы-маскарады каждый вечер, не до государственных дел. Гости к нему знатные съезжаются, а больше никого не пускают.";
			link.l1 = "Прямо маскарады?";
			link.l1.go = "AT_PZD_MatrosUKostra_7";
		break;
		case "AT_PZD_MatrosUKostra_7":
			dialog.text = "Как есть. Вот вчера иду мимо резиденции, смотрю, пугало такое в саду носатое, я аж перекрестился, а это какой-то дон маску напялил и стоит, статую разглядывает. Ох меня и смех разобрал тогда.";
			link.l1 = "Что ж, хоть какая-то зацепка. Как бы ещё мне попасть на этот приём?";
			link.l1.go = "AT_PZD_MatrosUKostra_8";
		break;
		case "AT_PZD_MatrosUKostra_8":
			dialog.text = "Это ты, морячка, опять не тем людям вопросы задаёшь.";
			link.l1 = "Знаю, и на том спасибо.";
			link.l1.go = "AT_PZD_MatrosUKostra_9";
		break;
		case "AT_PZD_MatrosUKostra_9":
			DialogExit();
			
			AddQuestRecord("AT_PZD", "4");
			
			pchar.questTemp.AT_PZD_Rostovshik = true;
			pchar.questTemp.AT_PZD_Lavochniki = true;
			pchar.questTemp.AT_PZD_Bordel = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("AT_PZD_Matros"+i);
				sld.lifeday = 0;
				LAi_CharacterDisableDialog(sld);
			}
		break;
		
		case "AT_PZD_ManBal5":
			dialog.text = "И куда запропал хозяин вечера? Он обещал мне партию в покер.";
			link.l1 = "В саду его нет.";
			link.l1.go = "AT_PZD_ManBal5_2";
		break;
		case "AT_PZD_ManBal5_2":
			dialog.text = "Будьте любезны, если встретите, передайте, что я его жду здесь.";
			link.l1 = "Так и сделаю.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AT_PZD_ManBal5";
		break;
		
		case "AT_PZD_WomanBal1":
			dialog.text = "Если мефрау Шарп в глубине души решила одержать победу над тучным щёголем, то я не думаю, что мы вправе хоть сколько-нибудь осуждать её за это, ведь задача уловления женихов обычно с подобающей скромностью препоручается юными особами своим маменькам, но вспомните, что у мефрау Шарп нет любящей родительницы, и если она сама не раздобудет себе мужа, то не найдётся никого в целом мире, кто оказал бы ей эту услугу.";
			link.l1 = "";
			link.l1.go = "AT_PZD_WomanBal2";
			sld = CharacterFromID("AT_PZD_WomanBal1");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest1");
		break;
		
		case "AT_PZD_WomanBal2":
			DialogExit();
			StartInstantDialog("AT_PZD_WomanBal2", "AT_PZD_WomanBal3", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_WomanBal3":
			dialog.text = "Не могу не согласиться. Другое дело мефрау Пилар, которая привезла на смотрины своего великовозрастного сына. Бедный мальчик, он вероятно, сгорает со стыда.";
			link.l1 = "";
			link.l1.go = "AT_PZD_WomanBal4";
			sld = CharacterFromID("AT_PZD_WomanBal2");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest2");
		break;
		
		case "AT_PZD_WomanBal4":
			DialogExit();
			StartInstantDialog("AT_PZD_WomanBal1", "AT_PZD_WomanBal5", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_WomanBal5":
			dialog.text = "Родители могли бы уладить вопрос и без присутствия своих отпрысков, не думаю, что даже одна из сестёр обратит на юношу хоть сколько-нибудь внимания.";
			link.l1 = "";
			link.l1.go = "AT_PZD_WomanBal6";
			sld = CharacterFromID("AT_PZD_WomanBal1");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest1");
		break;
		
		case "AT_PZD_WomanBal6":
			DialogExit();
			StartInstantDialog("AT_PZD_WomanBal2", "AT_PZD_WomanBal7", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_WomanBal7":
			dialog.text = "По мне он довольно мил, а вы что думаете, минхер Андрес?";
			link.l1 = "";
			link.l1.go = "AT_PZD_WomanBal8";
			sld = CharacterFromID("AT_PZD_WomanBal2");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest2");
		break;
		
		case "AT_PZD_WomanBal8":
			DialogExit();
			StartInstantDialog("AT_PZD_ManBal4", "AT_PZD_WomanBal9", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_WomanBal9":
			dialog.text = "Семейство Тернера ведёт дела в Вест-Индской компании, у парня большое будущее, было бы непредусмотрительным отпускать его без невесты...";
			link.l1 = "";
			link.l1.go = "exit";
			sld = CharacterFromID("AT_PZD_ManBal4");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest3");
			
			AddQuestRecord("AT_PZD", "6");
		break;
		
		case "AT_PZD_DochGubera":
			dialog.text = "...";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			
			AddQuestRecord("AT_PZD", "7");
		break;

		case "AT_PZD_MujikBoltun_1":
			dialog.text = "Я предупреждал тебя тысячу раз. Не могу больше ничем тебе помочь. Все мои деньги рассчитаны до последнего шиллинга.";
			link.l1 = "";
			link.l1.go = "AT_PZD_MujikBoltun_2";
			sld = CharacterFromID("AT_PZD_MujikBoltun1");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest5");
		break;
		
		case "AT_PZD_MujikBoltun_2":
			DialogExit();
			StartInstantDialog("AT_PZD_MujikBoltun2", "AT_PZD_MujikBoltun_3", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_MujikBoltun_3":
			dialog.text = "Я хочу говорить не о себе. Неважно, что будет со мной...";
			link.l1 = "";
			link.l1.go = "AT_PZD_MujikBoltun_4";
			sld = CharacterFromID("AT_PZD_MujikBoltun2");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest6");
		break;
		
		case "AT_PZD_MujikBoltun_4":
			DialogExit();
			StartInstantDialog("AT_PZD_MujikBoltun1", "AT_PZD_MujikBoltun_5", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_MujikBoltun_5":
			dialog.text = "Тогда в чём же дело?";
			link.l1 = "";
			link.l1.go = "AT_PZD_MujikBoltun_6";
			sld = CharacterFromID("AT_PZD_MujikBoltun1");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest5");
		break;
		
		case "AT_PZD_MujikBoltun_6":
			DialogExit();
			StartInstantDialog("AT_PZD_MujikBoltun2", "AT_PZD_MujikBoltun_7", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_MujikBoltun_7":
			dialog.text = "Ты знаешь, что я должен был получить деньги мефрау Кроули. Я не так уж плохо нёс службу в полку, жалование покрывало все мои расходы. И тебе известно, почему наследство уплыло от меня, и кто его получил...";
			link.l1 = "";
			link.l1.go = "AT_PZD_MujikBoltun_8";
			sld = CharacterFromID("AT_PZD_MujikBoltun2");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest6");
		break;
		
		case "AT_PZD_MujikBoltun_8":
			DialogExit();
			StartInstantDialog("AT_PZD_MujikBoltun1", "AT_PZD_MujikBoltun_9", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_MujikBoltun_9":
			dialog.text = "Не повышай голос, здесь не время и не место\nЧёрт, да куда все запропастились? Ни хозяина, ни прислуги... Видит бог, в следующий раз принесу бутылку вина с собой.";
			link.l1 = "";
			link.l1.go = "exit";
			sld = CharacterFromID("AT_PZD_MujikBoltun1");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest5");
		break;
		
		case "AT_PZD_GabrielDeSeguensa_1":
			dialog.text = "Чувствуете себя неуютно в незнакомом обществе?";
			link.l1 = "Даже не представляете насколько.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_2";
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_ActorTurnByLocator(sld, "quest", "quest9");
			LAi_ActorAnimation(sld, "barman_look_around", "", 2.9);
			locCameraFromToPos(-0.74, 8.81, 42.94, true, 2.00, 7.20, 42.00);
			ChangeCharacterAddressGroup(pchar, "Marigo_hall", "quest", "quest17");
		break;
		
		case "AT_PZD_GabrielDeSeguensa_1":
			dialog.text = "Чувствуете себя неуютно в незнакомом обществе?";
			link.l1 = "Даже не представляете насколько.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_2";
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_ActorTurnByLocator(sld, "quest", "quest9");
			LAi_ActorAnimation(sld, "barman_look_around", "", 2.9);
			locCameraFromToPos(-0.74, 8.81, 42.94, true, 2.00, 7.20, 42.00);
			ChangeCharacterAddressGroup(pchar, "Marigo_hall", "quest", "quest17");
		break;
		
		case "AT_PZD_GabrielDeSeguensa_2":
			dialog.text = "О, вы испанка? Невероятно жаль, что мы встретились только сейчас, когда мероприятие уже подошло к концу. Был бы рад пригласить вас на танец.";
			link.l1 = "Ничего бы из этого не вышло, я не умею танцевать вальсы.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_3";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_3":
			dialog.text = "Даму вашего положения не могли не обучить данному искусству. Верно, заочно отказываете мне даже надеяться...";
			link.l1 = "Честно говоря, я здесь даже без приглашения. Воспользовалась тем, что все гости в масках и рассчитывала на их учтивость, ведь накануне нас якобы уже представляли друг другу. Кстати, а где ваша маска?";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_4";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_4":
			dialog.text = "Она натёрла мне переносицу. И всё же, позвольте мне быть неучтивым.";
			link.l1 = "Меня зовут Анжелика Ремедиос, старшая дочь коменданта форта Ла Вега.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_5";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_5":
			dialog.text = "Габриэль де Сегуенса, прибыл на Карибы по поручении испанской короны, решать проблему пиратства в водах Кубы. Меня совсем недавно командировали из Старого света, но я уже наслышан о печальной судьбе форта. Почему вы до сих пор не сказали мне ни слово правды? Играете со мной как с котёнком.";
			link.l1 = "Слышали поговорку, лучший способ скрыть правду, это рассказать её, и раз уж вы посвящены в мою маленькую тайну, могу ли я попросить о небольшой услуге?";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_6";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_6":
			dialog.text = "Что же, я принимаю условия вашей игры.";
			link.l1 = "В ночь, когда Ла-Вега была разграблена, пираты разлучили меня и мою сестру. Она пропала без вести и я уже смирилась с мыслью о её гибели, пока не встретила женщину в платье, точь-в-точь таком, какое было на бедняжке Бекки, когда мы виделись в последний раз. Её лицо закрывала широченная шляпа, на мгновение я даже решила, что это и впрямь Ребекка, но надменная женщина отказалась со мной даже говорить. Вот я здесь, прячусь за маской в надежде снова её найти и разузнать историю её наряда.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_7";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_7":
			dialog.text = "Скверный характер, широкая шляпа - сеньора Тернера Пилар. Она не присутствует на вечере, но совсем недавно я сталкивался во дворе с её сыном.";
			link.l1 = "Вы окажете мне просто неоценимую услугу, если сведёте нас.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_8";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_8":
			dialog.text = "Я поищу и переговорю с ним. Анжелика, постарайтесь пока не привлекать к себе лишнего внимания, заодно поможете мне. Видите вон того сеньора сидящего за столиком? Он командующий гарнизоном, думаю вы найдёте общий язык. Скажите, что Габриэль попросил составить ему компанию, а спустя какое-то время через дверь за сценой выходите на набережную.";
			link.l1 = "Хорошо, я поняла.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_9";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_9":
			DialogExit();
			
			AddQuestRecord("AT_PZD", "8");
			
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2_back", "", "", "", "", -1);
			
			sld = CharacterFromID("AT_PZD_ManBal5");
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_IgraVKosti";
		break;
		
		case "AT_PZD_IgraVKosti":
			dialog.text = "";
			link.l1 = "Пригласите даму за стол?";
			link.l1.go = "AT_PZD_IgraVKosti_2";
		break;
		
		case "AT_PZD_IgraVKosti_2":
			dialog.text = "Не хотел бы показаться бестактным, я жду партнёра для игры в кости.";
			link.l1 = "Давайте мои кубики.";
			link.l1.go = "AT_PZD_IgraVKosti_3";
		break;
		
		case "AT_PZD_IgraVKosti_3":
			dialog.text = "Правила очень просты, по очереди мы выбрасываем кости...";
			link.l1 = "Кубики!";
			link.l1.go = "AT_PZD_IgraVKosti_4";
		break;
		
		case "AT_PZD_IgraVKosti_4":
			dialog.text = "Видит бог, поставил бы свой наградной пистоль, если хоть одна женщина сможет меня обыграть. К своему стыду, я заложил его на прошлой неделе.";
			link.l1 = "Играем на интерес, мне просто нужно убить немного времени.";
			link.l1.go = "AT_PZD_IgraVKosti_5";
			npchar.money = 10000;
			
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = 0;
            pchar.GenQuest.Dice.SitType   = true;			
			//pchar.GenQuest.Cards.npcharIdx = npchar.index;
            //pchar.GenQuest.Cards.iRate     = 0;
			//pchar.GenQuest.Cards.SitType   = true;
		break;
		
		case "AT_PZD_IgraVKosti_5":
			DialogExit();
			LaunchDiceGame();
			//LaunchCardsGame();
			
			LAi_CharacterDisableDialog(npchar);
			DoQuestCheckDelay("AT_PZD_UbiliVremya", 60.0);
		break;
		
		case "AT_PZD_GabrielDeSeguensa_11":
			dialog.text = "";
			link.l1 = "Удалось найти парня?";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_12";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_12":
			dialog.text = "Да вон он на балюстраде. Юнец не настроен на долгие разговоры, по крайней мере не в моём обществе\nА всё же прекрасный вечер, не находите?";
			link.l1 = "Не могу согласиться, мои мысли сейчас заняты другим.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_13";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_13":
			dialog.text = "Мне удалось узнать где квартирует мисс Пилар. С ней самой лучше дел не иметь, но поговорите с её прислугой, кто знает, возможно она привезла и свою портниху. Позвольте, я провожу вас.";
			link.l1 = "Конечно, идём.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_14";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_14":
			DialogExit();
			
			DoQuestReloadToLocation("Marigo_town", "goto", "goto29", "AT_PZD_VGorod");
		break;
		
		case "AT_PZD_GabrielDeSeguensa_15":
			dialog.text = "Здесь. По лестнице наверх.";
			link.l1 = "Поднимитесь со мной?";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_16";
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_160", "Logs.txt", "#space#", " "));
		break;
		
		case "AT_PZD_GabrielDeSeguensa_16":
			dialog.text = "Мне пора возвращаться в Гавану. Его милость, Оригон-и-Гаскон уже заждался моих отчётов. Удачи вам, Анжелика.";
			link.l1 = "Берегите себя. Охота на пиратов очень опасное занятие.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_17";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_17":
			DialogExit();
			
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
		break;
		
		case "AT_PZD_Sofia_1":
			dialog.text = "";
			link.l1 = "Вы?! Так это ваша работа?";
			link.l1.go = "AT_PZD_Sofia_2";
		break;
		
		case "AT_PZD_Sofia_2":
			dialog.text = "Боже! Сеньорита, я не услышала как вы вошли. Хозяева остановились внизу, эти комнаты сейчас отданы прислуге. Только боюсь, они ещё...";
			link.l1 = "София, не узнаёте меня? Ла-Вега, день перед осадой.";
			link.l1.go = "AT_PZD_Sofia_3";
		break;
		
		case "AT_PZD_Sofia_3":
			dialog.text = "Ой... Вы та девушка на рынке, которая хотела чем-то мне помочь?\nЗнаете, мне так неловко, я тогда была охвачена навалившимся проблемами, к тому же меня увлёк необычный крой наряда вашей спутницы, поэтому совершенно не запомнила вашего лица.";
			link.l1 = "Как вам удалось тогда спастись?";
			link.l1.go = "AT_PZD_Sofia_4";
		break;
		
		case "AT_PZD_Sofia_4":
			dialog.text = "Говорили, что пираты до того как начали стрелять по городу, проникли на наш корабль и выбросили все бочки пороха в море. Офицеры отправились к ним на переговоры, а когда вернулись, капитан приказал всем пассажирам сесть в шлюпки, и мы уплыли.";
			link.l1 = "Они просто бросили нас!";
			link.l1.go = "AT_PZD_Sofia_5";
		break;
		
		case "AT_PZD_Sofia_5":
			dialog.text = "Это так ужасно, я только недавно узнала, что там произошло.";
			link.l1 = "А почему вы не вернулись в Европу?";
			link.l1.go = "AT_PZD_Sofia_6";
		break;
		
		case "AT_PZD_Sofia_6":
			dialog.text = "Корабль не стал возвращаться, мне пришлось искать работу. На счастье, мисс Пилар была так великодушна, и знаете, я не хочу обратно в отцовское имение. А я уже говорила? Её здесь нет.";
			link.l1 = "Что ж, я зайду в другой раз. Рада, что вы справились со своими трудностями.";
			link.l1.go = "AT_PZD_Sofia_7";
		break;
		
		case "AT_PZD_Sofia_7":
			dialog.text = "Благодарю, сеньорита.";
			link.l1 = "Удачи, София.";
			link.l1.go = "AT_PZD_Sofia_8";
		break;
		
		case "AT_PZD_Sofia_8":
			DialogExit();
			
			sld = CharacterFromID("AT_PZD_Sofia");
			LAi_SetActorType(sld);
			
			AddQuestRecord("AT_PZD", "10");
			CloseQuestHeader("AT_PZD");
			PChar.quest.AT_PZD_ProvalMissii.over = "yes";
			
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			bDisableOfficers = false;
			LocatorReloadEnterDisable("Marigo_town", "reload3_back", false);
			LocatorReloadEnterDisable("Marigo_town", "reloadR2", false);			
			DeleteAttribute(pchar, "questTemp.AT_PZD_Bordel")
			DeleteAttribute(pchar, "questTemp.AT_PZD_Bordel_2")
			DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki");
			DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki_2");
			DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki_3");
			DeleteAttribute(pchar, "questTemp.AT_PZD_taverna")
			DeleteAttribute(pchar, "questTemp.AT_PZD_PU")
			DeleteAttribute(pchar, "questTemp.AT_PZD_Rostovshik")
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "Cirgnore");
			locations[FindLocation("Marigo_hall")].models.always.l1 = "residence06";
			//locations[FindLocation("Marigo_hall")].models.always.l1 = "residence06_quest";
			locations[FindLocation("Marigo_hall")].models.always.locators = "residence06_locators";
			//locations[FindLocation("Marigo_hall")].models.always.locators = "residence06_quest_locators";
			locations[FindLocation("Marigo_hall")].models.day.charactersPatch = "residence06_patch";
			//locations[FindLocation("Marigo_hall")].models.day.charactersPatch = "residence06_quest_patch";
			locations[FindLocation("Marigo_hall")].models.night.charactersPatch = "residence06_patch";
			//locations[FindLocation("Marigo_hall")].models.night.charactersPatch = "residence06_quest_patch";
			
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Sneak", 150);
		break;

	}
}
