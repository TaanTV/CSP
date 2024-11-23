
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);						// 						АВТОРЫ И БЛАГОДАРНОСТИ
	makearef(Link, Dialog.Links);						// Оригинальная идея квеста				    			 - Акелла
	makearef(NextDiag, NPChar.Dialog);					// Написанный с нуля код и переосмысление квеста 	 	 - Sinistra
														// Новая модель и текстура для "Ведьмы" 				 - Domovoy
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First_time":
			dialog.text = "Приветствую вас, "+ GetSexPhrase("сэр","леди")+". Меня зовут Бартоломью Ольстер. Кстати, вы не видели Марию Карлэ, девушку из таверны? Она куда-то пропала...";
			link.l1 = "Нет, я не знаю, кто она, и уж тем более - где она. Но у вас английский акцент - скажите, как вы попали сюда?";
			link.l1.go = "Bartolom";
			link.l2 = "Не знаю. Быть может вам стоит поискать в таверне - это было бы логично. А у меня сейчас другие дела.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First_time";
			PlayVoice("Kopcapkz\Voices\Quest\Ne_videli_Mariu.wav");
			UnmarkCharacter(npchar);
		break;

		case "Bartolom":
			dialog.text = "Простите, но прямо сейчас я не могу с вами разговаривать. Мне нужно найти Марию!";
			link.l1 = "В таком случае, до встречи.";
			link.l1.go = "PoraVTavernu";
		break;

		case "PoraVTavernu":
			SetQuestHeader("PDM_Ohota_na_vedmu");
			AddQuestRecord("PDM_Ohota_na_vedmu", "1");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			sld = CharacterFromID("PDM_Isp_sekr_guber");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back", "PDM_ONV_BARTO_Ischezni", -1);

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Carla", "Witch", "woman", "woman", 10, SPAIN, -1, false));
			LAi_SetImmortal(sld, true);
			sld.name = "Мария";
			sld.lastname = "Карлэ";
			sld.city = "Beliz";
			ChangeCharacterAddressGroup(sld, "Beliz_tavern", "waitress", "stay2");
			LAi_SetWaitressType(sld);
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "First_Carla_1";
			
			sld = CharacterFromID("Beliz_waitress");
			sld.model	= "girl_6";			

			DialogExit();
		break;

		case "First_Carla_1":
			dialog.text = "Чего ты здесь ищешь, красав"+ GetSexPhrase("чик","ица")+"? Удовольствий, я полагаю? Меня зовут Мария Карлэ, или Весёлая Мария, как меня называют большинство мужчин в этом городе. А как тебя зовут, сеньор"+ GetSexPhrase("","ита")+"?";
			link.l1 = "Можешь звать меня "+pchar.name+", дорогуша. Но я полагаю, что тут в городе есть ещё один человек, который ищет удовольствий. Я видел"+ GetSexPhrase("","а")+" его на площади - ему похоже, не терпится встретиться с тобой.";
			link.l1.go = "First_Carla_2";
			PlayVoice("Kopcapkz\Voices\PDM\Spain\Catalina.wav");
		break;

		case "First_Carla_2":
			dialog.text = "Что? Бартоломью? Но я думала, что он... А, неважно... Знаешь что, красав"+ GetSexPhrase("чик","ица")+" - я тут вспомнила, что я немного занята сегодня. Но мы проделаем всё, чего нам хочется в другой раз - когда я буду посвободнее. У тебя очень красивые ноги, кстати.";
			link.l1 = "Э... Спасибо. Я пожалуй загляну к тебе попозже.";
			link.l1.go = "First_Carla_Uhodit";
		break;

		case "First_Carla_Uhodit":
			AddQuestRecord("PDM_Ohota_na_vedmu", "2");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			//bDisableFastReload = true;
			LocatorReloadEnterDisable("Beliz_town", "reload3_back", true);
			LocatorReloadEnterDisable("Beliz_town", "reloadR1", true);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload1", true);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload2", true);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload3", true);
			LocatorReloadEnterDisable("Beliz_townhall", "reload2", true);
			LocatorReloadEnterDisable("Beliz_townhall", "reload1_back", true);

			sld = CharacterFromID("PDM_ONV_Carla");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorRunToLocator(sld, "reload", "reload1_back", "PDM_ONV_Clara_Ischezni", -1);

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Sin", "SpaOfficer1", "man", "man", 100, SPAIN, -1, false));
			sld.name = "Синистра";
			sld.lastname = "";
			sld.greeting = "GR_Spainguard";
			sld.city = "Beliz";
			FantomMakeCoolFighter(sld, 100, 100, 100, "blade27", "pistol6", 0);
			LAi_SetHP(sld, 1.0, 1.0);
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, "Beliz_town", "reload", "reload3_back");
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "OfficerGuard";
			
			PChar.quest.PDM_ONV_Vkomnate.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_Vkomnate.win_condition.l1.location = "Beliz_TownhallRoom";
			PChar.quest.PDM_ONV_Vkomnate.win_condition = "PDM_ONV_Vkomnate";

			PChar.quest.PDM_ONV_Vzaimno.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_ONV_Vzaimno.win_condition.l1.character = "PDM_ONV_Sin";
			PChar.quest.PDM_ONV_Vzaimno.win_condition = "PDM_ONV_Vzaimno";

			DialogExit();
		break;

		case "OfficerGuard":
			dialog.text = "Извините, сеньор"+ GetSexPhrase("","ита")+", но мне не велено никого впускать.";
			link.l1 = "Как скажете, офицер. До свидания!";
			link.l1.go = "OfficerGuard_Cod";
			NextDiag.TempNode = "OfficerGuard_Again";
		break;

		case "OfficerGuard_Cod":
			AddQuestRecord("PDM_Ohota_na_vedmu", "3");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			LocatorReloadEnterDisable("Beliz_town", "reloadR1", false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "OfficerGuard_Again":
			dialog.text = "Извините, сеньор"+ GetSexPhrase("","ита")+", но мне не велено никого впускать.";
			link.l1 = "Как скажете, офицер. До свидания!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OfficerGuard_Again";
		break;

		case "Soldat15":
			dialog.text = "Cеньор"+ GetSexPhrase("","ита")+", поговорите пожалуйста с губернатором.";
			link.l1 = "Спасибо, солдат, я так и сделаю.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Soldat15";
		break;

		case "RazgovorSGuberom":
			dialog.text = "";
			link.l1 = "Сеньор губернатор! Прошу простить меня, что я без разрешения проник"+ GetSexPhrase("","ла")+" сюда, но я обнаружил"+ GetSexPhrase("","а")+" подозрительную активность в вашей резиденции и решил"+ GetSexPhrase("","а")+" проявить любопытство. В одной из комнат я наш"+ GetSexPhrase("ёл","ла")+" труп...";
			link.l1.go = "RazgovorSGuberom_2";
			locations[FindLocation("Beliz_TownhallRoom")].id.label = "TownhallRoom";	//возвращает работников в спальни
		break;

		case "RazgovorSGuberom_2":
			dialog.text = "Странные вещи здесь творятся, капитан. Моя правая рука, мой секретарь, был найден мёртвым в своей комнате. Кто-то задушил его прямо в постели, его руки были сжаты на горле, а глаза выпучены. Но нет никаких следов верёвки или пальцев на шее. Я не знаю, что всё это значит. Это ужасная трагедия.";
			link.l1 = "Какая странная история. Но как так случилось, что вашим секретарём стал англичанин?";
			link.l1.go = "RazgovorSGuberom_3";
		break;

		case "RazgovorSGuberom_3":
			dialog.text = "(обращается к стражникам) Оставьте нас.";
			link.l1 = "";
			link.l1.go = "RazgovorSGuberom_4";
		break;

		case "RazgovorSGuberom_4":
			dialog.text = "Английское правительство сослало его. Они выдвинули против него фальшивые обвинения. Он был очень благородным человеком с прекрасным характером. Мы познакомились пятнадцать лет назад в Европе. Тогда он был молодым дипломатом, мы встречались при дворе. Один из моих агентов пересёкся с ним в Порт-Рояле. Его выбросили на улицу после того, как обвинили в хищении. Лишённый своего титула, он согласился стать моим секретарем.";
			link.l1 = "Кажется, я встречал"+ GetSexPhrase("","а")+" его. Бартоломью, вы говорите? Кажется, на площади, он искал девушку из таверны по имени Мария Карлэ.";
			link.l1.go = "RazgovorSGuberom_5";
			sld = CharacterFromID("PDM_ONV_SoldatGub_1");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorGoToLocator(sld, "goto", "goto3", "PDM_ONV_STRAJIschezni", 3);
			sld = CharacterFromID("PDM_ONV_SoldatGub_2");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorGoToLocator(sld, "goto", "goto3", "PDM_ONV_STRAJIschezni", 3);
		break;

		case "RazgovorSGuberom_5":
			dialog.text = "Девушку из таверны? Это очень странно. Он был знатным человеком, как я сказал, у него не могло быть ничего общего с женщиной такой репутации.";
			link.l1 = "Сеньор губернатор, что вы думаете о его гибели? Кто мог убить его?";
			link.l1.go = "RazgovorSGuberom_6";
		break;

		case "RazgovorSGuberom_6":
			dialog.text = "Это интриги врагов испанской короны, я полагаю. Но не могу назвать никого конкретно...";
			link.l1 = "Надеюсь, сеньор губернатор, эту загадку можно разрешить. Но у меня есть важные дела, и если вы мне позволите, то я пойду.";
			link.l1.go = "RazgovorSGuberom_6_1";
		break;

		case "RazgovorSGuberom_6_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "officers", "reload1_2", "", -1);
			DoQuestFunctionDelay("PDM_ONV_NaRabotu", 2.6);
		break;

		case "RazgovorSGuberom_7":
			dialog.text = "Погодите... Вообще-то, да, сеньор"+ GetSexPhrase("","ита")+" "+pchar.name+". Вы говорили, что бедный Бартоломью искал девушку из таверны по имени Мария Карлэ, да? Вы не приведёте её ко мне? Я мог бы послать за ней, но это вызовет волну слухов. Может быть, вы бы могли решить это дело более деликатно. Я решил взять расследование под личный контроль.";
			link.l1 = "Ладно, сеньор губернатор, если я найду её, конечно, приведу её сюда.";
			link.l1.go = "RazgovorSGuberom_COD";
			link.l2 = "Простите, но эта работа не для меня.";
			link.l2.go = "OtkazOtZadaniya";
			NextDiag.TempNode = "RazgovorSGuberom_Again";
		break;
		
		case "OtkazOtZadaniya":
			dialog.text = "Очень жаль, тогда не смею вас задерживать.";
			link.l1 = "До свидания!";
			link.l1.go = "OtkazOtZadaniya_2";
			NextDiag.TempNode = "RazgovorSGuberom_AgainOtkaz";
		break;
		
		case "OtkazOtZadaniya_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			
			LocatorReloadEnterDisable("Beliz_Townhall", "reload1_back", false);
			LocatorReloadEnterDisable("Beliz_Townhall", "reload3", true);
			PChar.quest.PDM_ONV_VernutBezZadaniya.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_VernutBezZadaniya.win_condition.l1.location = "Beliz_town";
			PChar.quest.PDM_ONV_VernutBezZadaniya.win_condition = "PDM_ONV_VernutBezZadaniya";
			CloseQuestHeader("PDM_Ohota_na_vedmu");		
			pchar.questdata.OhotaNaVedmu = 1;			
			sld = CharacterFromID("PDM_ONV_Sin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;
		
		case "RazgovorSGuberom_AgainOtkaz":
			dialog.text = "Попрошу покинуть мой кабинет, у меня много работы.";
			link.l1 = "Уже ухожу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RazgovorSGuberom_AgainOtkaz";
		break;

		case "RazgovorSGuberom_Again":
			dialog.text = "Я уже вам дал задание, сеньор"+ GetSexPhrase("","ита")+". Что вы хотели ещё спросить?";
			link.l1 = "Я "+ GetSexPhrase("заблудился","заблудилась")+", сеньор губернатор. Я иду искать девушку Марию. До свидания!";
			link.l1.go = "exit";
			NextDiag.TempNode = "RazgovorSGuberom_Again";
		break;

		case "RazgovorSGuberom_COD":
			LocatorReloadEnterDisable("Beliz_Townhall", "reload1_back", false);
			LocatorReloadEnterDisable("Beliz_Townhall", "reload3", true);

			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition.l1.location = "Beliz_town";
			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition = "PDM_ONV_SVOBODA_URA";

			AddQuestRecord("PDM_Ohota_na_vedmu", "5");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex1", GetSexPhrase("ся","ась"));
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex2", GetSexPhrase("ен","на"));
			sld = CharacterFromID("PDM_ONV_Sin");
			ChangeCharacterAddressGroup(sld, "none", "", "");

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "RazgovorSViktorom_1":
			dialog.text = "Ты кто так"+ GetSexPhrase("ой","ая")+", "+ GetSexPhrase("парень","девчонка")+"? И что, чёрт тебя раздери, тебе нужно?";
			link.l1 = "Я думал"+ GetSexPhrase("","а")+", что ты торговец, которому, может быть, нужно сопровождение... Но, похоже, я "+ GetSexPhrase("ошибся","ошиблась")+".";
			link.l1.go = "RazgovorSViktorom_2";
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_PortoBello");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_SanJuan");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Maracaibo");
			UnmarkCharacter(npchar);
		break;

		case "RazgovorSViktorom_2":
			dialog.text = "Да, "+ GetSexPhrase("приятель, ты ошибся","милая, ты ошиблась")+". Я Силино Сэв, безработный боцман. Вчера один безмозглый обормот предложил мне работать дровосеком. Знаешь, что с ним случилось?";
			link.l1 = "Понятно... Но давай мы посидим за кружкой рома, и ты расскажешь мне свою историю.";
			link.l1.go = "RazgovorSViktorom_3";
		break;

		case "RazgovorSViktorom_3":
			ChangeCharacterAddressGroup(pchar, PChar.location, "sit", "sit_front2");
			LAi_SetSitType(pchar);
			LAi_SetSitType(npchar);
			locCameraTarget(PChar)
            locCameraFollow();
			dialog.text = "Я расскажу тебе, что со мной сучилось - но это не интересная сказка, которую рассказывают детям. Всё произошло из-за этой проклятой ведьмы, которую капитан подобрал в Белизе. Скажу я тебе, если бы он не связался с этой ведьмой, он был бы жив сейчас. Но он всегда был слишком упрямым. Он мог переспорить самого дьявола, наш старый добрый Мигель.\n"+
							"Но после того как эта женщина появилась на борту, он изменился. Да, он изменился. Он высох, словно сушёная вобла. Мы говорили, чтобы он не брал эту женщину с собой - среди моряков считается, что женщина на борту, это к несчастью... когда на борту женщина, жди неприятностей.\n"+
							"И вот из-за этой Марии Карлэ...";
			link.l1 = "Подожди! Ты сказал, её зовут Мария Карлэ? Эту женщину разыскивает губернатор Белиза. Он считает, что она может быть причастна к убийству!";
			link.l1.go = "RazgovorSViktorom_4";
		break;

		case "RazgovorSViktorom_4":
			dialog.text = "Да, губернатор прав. Эта чёртова ведьма убила нашего капитана. Он был мёртв, словно дохлая треска, когда мы достигли Сантьяго. Мы только-только вошли в порт, когда нашли его мёртвым на палубе. Мы бросились искать проклятую ведьму, но она загадочным образом исчезла. И теперь я безработный боцман. Дубина первый помощник в точности выполнил последнюю волю капитана, и продал нашу лоханку, а все деньги пожертвовал Церкви.";
			link.l1 = "Что за адское исчадие эта женщина! Она уничтожила уже двоих людей. Её необходимо остановить.";
			link.l1.go = "RazgovorSViktorom_5";
		break;

		case "RazgovorSViktorom_5":
			dialog.text = "Удачи тебе капитан в её поисках!";
			link.l1 = "Я обязательно её найду. До встречи!";
			link.l1.go = "RazgovorSViktorom_COD";
			NextDiag.TempNode = "RazgovorSViktorom_Again";
		break;

		case "RazgovorSViktorom_COD":
			sld = CharacterFromID("PDM_ONV_Viktor_Martos");
			sld.lifeday = 0;

			AddQuestRecord("PDM_Ohota_na_vedmu", "11");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			ChangeCharacterAddressGroup(pchar, PChar.location, "tables", "stay2");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Carla", "Witch", "woman", "woman", 10, SPAIN, -1, false));
			sld.city = "Santiago";
			ChangeCharacterAddressGroup(sld, "Santiago_tavern", "goto", "goto4");
			LAi_SetWaitressType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.name = "Мария ";
			sld.lastname = "Карлэ";
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "Carla_Final_1";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "RazgovorSViktorom_Again":
			dialog.text = "Удачи тебе капитан в её поисках!";
			link.l1 = "Я обязательно её найду. До встречи!";
			link.l1.go = "exit";
			NextDiag.TempNode = "RazgovorSViktorom_Again";
		break;

		case "Carla_Final_1":
			dialog.text = "О, дорогуша! Что ты делаешь сегодня вечером? Или прямо сейчас?";
			link.l1 = "Наглая ведьма! Ты позволяешь себе продолжать свои нечестивые занятия и склонять честных испанцев к служению дьяволу!? Мне приказано представить тебя к правосудию!";
			link.l1.go = "Carla_Final_2";
			PlayVoice("Kopcapkz\Voices\PDM\Carla.wav");
		break;

		case "Carla_Final_2":
			dialog.text = "Ч-что вы говорите, сеньор"+ GetSexPhrase("","ита")+"? Я н-н-не з-знаю ни о каких преступлениях.";
			link.l1 = "Ты думаешь, что тебе удастся доказать свою невинность, отрицая очевидное? У меня есть свидетель - боцман Силино Сэв. Он готов дать показания о том, что ты - ведьма.";
			link.l1.go = "Carla_Final_5";
			link.l2 = "У меня есть свидетель - боцман Силино Сэв. Мигель Куэнда умер на своём корабле недалеко от Сантьяго! И мы ещё узнаем, какую отвратительную роль твоё чародейство сыграло в ужасной смерти Бартоломью Ольстера в Белизе. И... Нет, я передумал"+ GetSexPhrase("","а")+". Я прямо здесь, в этом городе найду на тебя управу. Инквизиция выслушает меня - и моих слов будет достаточно для того, чтобы покарать тебя.";
			link.l2.go = "NaKoster_2";
		break;

		case "Carla_Final_5":
			dialog.text = "Я знаю, что смерть Мигеля была моей виной... Но я не могла ничего поделать - мне надо было избавиться от этого ублюдка Бартоломью. Но когда он всё-таки выговорил своё проклятие - я поняла, что всё кончено. Мигель был обречён. Я любила его...";
			link.l1 = "Погоди. Я ничего не понял"+ GetSexPhrase("","а")+". Какое ещё проклятье? Любила кого?";
			link.l1.go = "Carla_Final_6";
		break;

		case "Carla_Final_6":
			dialog.text = "Бартоломью Ольстер наложил смертельное заклятие на Мигеля. Я пыталась спасти Мигеля всю дорогу до Сантьяго, но... тщетно. Моих сил просто не хватило для того, чтобы рассеять его мощную магию. Я была всего лишь ученицей, которой не суждено было превзойти учителя.";
			link.l1 = "Так ты сознаёшься, что ты ведьма?";
			link.l1.go = "Carla_Final_7";
		break;

		case "Carla_Final_7":
			dialog.text = "Да. Бартоломью Ольстер был моим наставником в мастерстве ворожбы. Он заметил во мне этот Дар, когда мне было всего четырнадцать. Тогда я была просто глупенькой девочкой, которая не понимала, что творит. Я не была красивой, но он рассказал мне, как покорять сердца мужчин, и я стала всего-навсего дешёвой проституткой. Он использовал меня для того, чтобы выпытывать секреты у клиентов, он провёл меня через все унижения, которые я могла вообразить. Я просто не могла жить больше - он был слишком силён...\n"+
							"Но когда я встретила Мигеля, я подумала, что у меня появилась возможность...  Я полюбила этого отважного капитана... но Бартоломью сказал, что если я попытаюсь сбежать, то он расскажет священникам, что я ведьма, и они сожгут меня на костре. Я рассказала обо всём Мигелю. И он решил, что нам следует убить Ольстера. Мой Дар был слишком слаб, чтобы справиться с ним магически, и я всего лишь слабая женщина. Но Мигель вселил в меня веру.";
			link.l1 = "Но как вы пробрались через стражу?";
			link.l1.go = "Carla_Final_8";
		break;

		case "Carla_Final_8":
			dialog.text = "Это было самое простое. Я насыпала им сонного зелья в питьё... и они заснули как младенцы. После этого, мы прокрались в спальню этого чудовища в человеческом облике.  Но он не спал, как мы надеялись. Я думаю, что он наложил формулу охраны на дверь, которая и разбудила его. Мигель бросился на него, но этот подонок сумел применить магию. Раненный Мигель боролся с колдуном и задушил его подушкой, в конце концов.\n"+
							"Я пыталась спасти Мигеля всю дорогу до Сантьяго. Но когда он упал мёртвым на палубу, мне пришлось скрыться с корабля. Команда была в ярости - я была единственной женщиной на корабле, которую капитан и пальцем не позволял тронуть. Пока мы плыли, они распалились, как стая диких собак.";
			link.l1 = "И что произошло потом?";
			link.l1.go = "Carla_Final_10";
		break;

		case "Carla_Final_10":
			dialog.text = "Я не знала, что мне делать. Всё, чего я хотела это сбежать от моего прошлого. Когда я прибыла сюда, у меня не было денег, и я вернулась к единственному занятию, которое знаю...";
			link.l1 = "Единственно важная вещь в этом всём состоит в том, что ты ведьма. Поэтому я передам тебя в руки Инквизиции.";
			link.l1.go = "NaKoster_2";
			link.l2 = "Полагаю, что вы не совершили никакого преступления, Мария. Вы свободны.";
			link.l2.go = "Carla_Final_11";
		break;

		case "Carla_Final_11":
			dialog.text = "О, "+ GetSexPhrase("сеньор","сеньорита")+" - вы очень благородны. Я скажу вам вот что. Все считают, что колдовство, это занятие неугодное Богу. Но я скажу вам, что это просто Дар, или Мастерство, как и любое другое...";
			link.l1 = "";
			link.l1.go = "Carla_Final_12";
		break;

		case "NaKoster_2":
			dialog.text = "Как пожелаете, "+ GetSexPhrase("сеньор","сеньорита")+". Моя жизнь более для меня ничего не значит - я не видела милосердия, не стяжала любви - было бы странно рассчитывать на правосудие.";
			link.l1 = "Не пытайся разжалобить меня, проклятая ведьма! Ты будешь гореть в огне!";
			link.l1.go = "NaKoster_COD";
			NextDiag.TempNode = "NaKoster_Again";
		break;

		case "Carla_Final_12":
			dialog.text = "И примите мой Дар. Удача будет сопутствовать вам с этого дня.";
			link.l1 = "Желаю вам удачи, Мария! До встречи.";
			link.l1.go = "Dobro_Final";
			NextDiag.TempNode = "Carla_Final_Again";
			LAi_SetHP(pchar,LAi_GetCharacterMaxHP(pchar)+40,LAi_GetCharacterMaxHP(pchar)+40);
			PlaySound("Interface\new_level.wav");
			Log_info("Ведьма напустила на вас колдовские чары.");
			Log_info("Ваше здоровье увеличилось на 40 навсегда.");
		break;

		case "Dobro_Final":
			AddQuestRecord("PDM_Ohota_na_vedmu", "12");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("PDM_Ohota_na_vedmu");
			pchar.questdata.OhotaNaVedmu = 1;
			ChangeCharacterReputation(pchar, 3);
			AddCharacterExpToSkill(pchar, "Fortune", 300);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Carla_Final_Again":
			dialog.text = "Спасибо вам, "+ GetSexPhrase("добрый сеньор","добрая сеньорита")+", я не забуду вашего благородства!";
			link.l1 = "Удачи вам, Мария!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Carla_Final_Again";
			PlayVoice("Kopcapkz\Voices\PDM\Carla.wav");
		break;

		case "NaKoster_COD":
			pchar.questTemp.PDM_ONV_OhotaNaVedmu = true;

			AddQuestRecord("PDM_Ohota_na_vedmu", "13");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NaKoster_Again":
			dialog.text = "Моя жизнь больше ничего не стоит... Но я не потрачу даже минуты из её остатка на разговор с вами.";
			link.l1 = "Ты сгоришь в огне, мерзкая ведьма!";
			link.l1.go = "exit";
			NextDiag.TempNode = "NaKoster_Again";
		break;

		case "Inqizitor_1":
			dialog.text = "... этот город погряз в грехе! Но скоро мы освободим людей из тёмных тенёт Сатаны огнём и волей Господа нашего! Э-э... чего ты хочешь, "+ GetSexPhrase("сын мой","дочь моя") +"?";
			link.l1 = "Святой Отец, я знаю, здесь есть ведьма по имени Мария, бывшая портовая проститутка. Своим тёмным искусством она убила уже двоих - капитана Мигеля Куэнду, и доброго идальго Бартоломью, который умер, не успев покаяться. Он был слугой Дона Франсиско. Я молю Бога, чтобы Святая Инквизиция покарала её за греховные деяния.";
			link.l1.go = "Inqizitor_2";
			PlayVoice("Kopcapkz\Voices\PDM\Zaharia Marlow-02.wav");
		break;

		case "Inqizitor_2":
			dialog.text = "Ах, да будет душа твоя вечно благословенна за твой праведный поступок, "+ GetSexPhrase("сын мой","дочь моя") +". Мы позаботимся об этой ведьме.";
			link.l1 = "Я надеюсь на это, святой отец. Доброго вам дня.";
			link.l1.go = "KAZN";
			AddBonusEnergyToCharacter(pchar, 25);
			PlaySound("Interface\new_level.wav");
			Log_info("Ваша энергия увеличилась на 25 навсегда.");
		break;

		case "KAZN":
			DoQuestReloadToLocation("Santiago_town", "officers", "reload8_2", "PDM_ONV_KaznVedmi");
			TavernWaitDate("wait_night");
		break;
	}
}
