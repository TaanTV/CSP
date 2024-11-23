
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

		case "BS_NPVK_1":	//Торговец
			dialog.text = "Капитан, ничего личного, но очень влиятельная особа запретила вести дела с вами. Никаких сделок, извините";
			link.l1 = "Простите, но я не понимаю. Что произошло?";
			link.l1.go = "BS_NPVK_2";
		break;

		case "BS_NPVK_2":
            dialog.text = "Обратитесь к мисс Гатри, она недавно прибыла с Нассау и взяла под контроль сделки с призами. Сам Джекман к ней с поклоном заходит.";
            link.l1 = "Хм. Гатри... Что – то знакомое. Хорошо, до встречи.";
			link.l1.go = "exit";
		break;

		case "BS_NPVK_3":	//Гатри
            dialog.text = "А, вот и наш проблемный капитан! Пришли уладить разногласия? Давайте уладим, но предупреждаю – эти парни с мушкетами здесь не просто так стоят.";
            link.l1 = "Хм. Дело в том, что торговцы в колониях и даже пираты перестали вести со мной дела, говорят, что это вы тому причиной. Могу я поинтересоваться, в чём дело?";
			link.l1.go = "BS_NPVK_4";
		break;

		case "BS_NPVK_4":
            dialog.text = "Дело в вашей неосмотрительности, и как я думаю, в неопытности в делах Нового Света. Позвольте объяснить.";
            link.l1 = "Слушаю вас.";
			link.l1.go = "BS_NPVK_5";
		break;

		case "BS_NPVK_5":
            dialog.text = "Прежний владелец этого магазина, месье Вуазье, был, можно сказать, поверенным нашей семьи. Весь добытый пиратами, а часто и каперами товар, его усилиями, становился вполне легальным и приносил прибыль всем. В том числе и губернаторам и командующим военных эскадр.\n"+
							"И вдруг, некий бравый капитан решает, что ему правила не указ и начинает творить хаос. Деньги, дорог"+ GetSexPhrase("ой","ая") +" мо"+ GetSexPhrase("й","я") +" – любят покой.\n";
            link.l1 = "Ваш 'поверенный' сам, по сути был пиратом и мешал торговле на архипелаге. Ко мне обратился уважаемый торговец от имени сообщества, и я решил"+ GetSexPhrase("","а") +" проблему в меру своих сил и возможностей. Не понимаю, какие у нас с Вами могут быть разногласия?";
			link.l1.go = "BS_NPVK_6";
		break;

		case "BS_NPVK_6":
            dialog.text = "Капитан. Ваш тон я могу списать на неопытность и непонимание сути вещей, но предупреждаю: ещё слово и говорить будет оружие!";
            if (WhisperIsHere())
			{
				link.l1.go = "BS_NPVK_6_WhisperIsHere";
				break;
			}
			link.l1 = "Да кем ты себя возомнила, девка?";	//Драка
			link.l1.go = "Fight_gatri";
			link.l2 = "Давайте сбавим тон и найдём решение наших 'затруднений'.";
			link.l2.go = "BS_NPVK_7";
		break;

		case "BS_NPVK_6_1":
			link.l1 = "Да кем ты себя возомнила, девка?";	//Драка
			link.l1.go = "Fight_gatri";
			link.l2 = "Давайте сбавим тон и найдём решение наших 'затруднений'.";
			link.l2.go = "BS_NPVK_7";
		break;

		case "BS_NPVK_6_WhisperIsHere":
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "BS_9_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
		break;

		case "Fight_gatri":
			AddQuestRecord("BSPrologue", "6");
			AddQuestUserData("BSPrologue", "sSex", GetSexPhrase("того","ту"));
			CloseQuestHeader("BSPrologue");
			PChar.BS_PiratesStoreMassacre = true;
			SaveCurrentQuestDateParam("BS_PiratesStoreMassacreDate");
			BS_SL_yes();
			DeleteAttribute(pchar, "BSStart");
			BS_QuestCleaning(true);			
			ChangeCharacterHunterScore(pchar, "enghunter", 200);
			pchar.questTemp.BlueBird = "declined";//Блокировка ЧП
			string killGatri;
			for (i = 1; i < 4; i++)
			{
				sld = CharacterFromID("gatri_grunt"+i);
				LAi_SetImmortal(sld, false);
				killGatri = "l"+i;
				pchar.quest.KillGatri.win_condition.(killGatri) = "NPC_Death";
				pchar.quest.KillGatri.win_condition.(killGatri).character = sld.id;
				pchar.quest.KillGatri1.win_condition.(killGatri) = "NPC_Death";
				pchar.quest.KillGatri1.win_condition.(killGatri).character = sld.id;
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_MoveCharacter(npchar, "EnemyFight");
				LAi_SetHP(sld, 200, 200);
			}
			killGatri = npchar.id;
			LAi_SetImmortal(npchar, false);
			npchar.Dialog.FileName = npchar.beforeGatriFileName;
			npchar.Dialog.CurrentNode = npchar.beforeGatriCurrentNode;
			pchar.quest.KillGatri.win_condition.(killGatri) = "NPC_Death";
			pchar.quest.KillGatri.win_condition.(killGatri).character = npchar.id;
			pchar.quest.KillGatri1.win_condition.(killGatri) = "NPC_Death";
			pchar.quest.KillGatri1.win_condition.(killGatri).character = npchar.id;
			pchar.quest.KillGatri.function = "LockWeapons";
			pchar.quest.KillGatri1.win_condition = "OpenTheDoors";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "BS_NPVK_7":
            dialog.text = "Уладить наши разногласия, капитан, будет для вас просто. Всего-то нужно выбить англичан из форта Нассау.";
			link.l1 = "Это вы называете 'просто'? Объявить войну Британии?";
			link.l1.go = "BS_NPVK_8";
		break;

		case "BS_NPVK_7_WhisperIsHere":
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "BS_10_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
		break;

		case "BS_NPVK_8":
            dialog.text = "Никакой войны. Просто группа пиратов, под черными флагами, грабит отдалённую, не очень важную колонию и скрывается за горизонтом. Пройдёт несколько лет, пока у Короны найдутся средства и силы попытаться вернуть колонию, но скорее всего, они просто закроют глаза и сделают вид, что никакой колонии и не было. Тем более, семья Гатри приложит немало усилий для того, что бы глаза эти так и оставались закрыты.";
            link.l1 = "Вашей семье стало тесно в Бостоне и Филадельфии и вы расширяете зону влияния?";
			link.l1.go = "BS_NPVK_9";
		break;

		case "BS_NPVK_9":
            dialog.text = "Вы быстро схватываете! Разнесите форт, перебейте или плените гарнизон. Силы для этого найдёте самостоятельно, но даже не пытайтесь подписать на это местных пиратских баронов. Это должна быть частная инициатива отчаянного пирата. Избежать огласки - это в ваших же интересах.";
            link.l1 = "Допустим, город взят. Что дальше? У вас же есть план как удержать колонию?";
			link.l1.go = "BS_NPVK_10";
		break;
		
		case "BS_NPVK_10":
            dialog.text = "План есть, просто дайте знать, когда вы отправитесь к Багамам. И в случае успеха, я и мои люди будем там через день-два.";
            link.l1 = "Семья Гатри 'совершенно случайно' окажется неподалёку и придёт на помощь колонистам? Хитро. А что будет если я откажусь провернуть эту авантюру?";
			link.l1.go = "BS_NPVK_11";
		break;
		
		case "BS_NPVK_11":
            dialog.text = "Все охотники за головами, в Старом свете и Новом, вдруг загорятся желанием принести мне вашу голову. Уверяю вас, капитан, ссорится с 'Торговым домом Гатри' - не решаются даже короли. У нас есть средства и связи, которые могут очень сильно испортить жизнь кому угодно.";
            link.l1 = "Да кем ты, девка, себя возомнила? Ха! Кучка торгашей и счетоводов! Я знаю лучший способ уладить наши разногласия - холодная сталь!";
			link.l1.go = "Fight_gatri";
			link.l2 = "Всё это звучит как полнейшее безумие, но я соглас" + GetSexPhrase("ен","на") + "! Мне нужно время на подготовку. Не скажу сколько, но дам вам знать. Увидимся.";
			link.l2.go = "BS_NPVK_12";
		break;
		
		case "BS_NPVK_12":
            dialog.text = "Вот и прекрасно. А всем необходимым вы можете закупиться в этом магазине. Склады Бермуд всегда к вашим услугам. Найдёте меня через бармена.";
            link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_NPVK_13";
			BS_SL_yes();
			AddQuestRecord("BSPrologue", "2");
			AddQuestUserData("BSPrologue", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.BSPrologue.WaitingForNassauSiege = true;
		break;

		case "BS_NPVK_13":
            dialog.text = "Что ещё? Я вас больше не задерживаю.";
			link.l1 = "...";
			link.l1.go = "BS_NPVK_14";
		break;
		
		case "BS_NPVK_14":
			DialogExit();
			DoReloadCharacterToLocation("Pirates_town", "reload", "reload6_back");
		break;
		
		case "Woman_FackYou":
			dialog.text = "Мил"+ GetSexPhrase("ый","ая") +", ты куда это полез"+ GetSexPhrase("","ла") +"?! Надо же, а казал"+ GetSexPhrase("ся","ась") +" порядочн"+ GetSexPhrase("ым капитаном","ой девушкой") +".\nНу а теперь так просто тебе не уйти, красав"+ GetSexPhrase("чик","ица") +". Подрежут тебе крылышки...";
			link.l1 = "Заткнись, дура...";
			link.l1.go = "Fight_gatri";
			LAi_SetOwnerTypeNoGroup(npchar);
		break;
		
		case "BS_NPVK_15":
			dialog.text = "День настал? Вы готовы к походу?";
			link.l1 = "Более чем! А ваши люди готовы?";
			link.l1.go = "BS_NPVK_16";
		break;
		
		case "BS_NPVK_16":
			dialog.text = "Мы будем неподалёку. Удачи, капитан!";
			link.l1 = "Удача нам не помешает. За дело!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("BS_ToNassauSiege_PiratesTown");
		break;
		
		case "BS_NPVK_17":
			dialog.text = "Дело сделано, ваши долги аннулированы. Теперь покиньте остров, я с вами свяжусь через пиратских барменов, если будет какая работа по вашему профилю.";
			link.l1 = "У меня тут толпа головорезов, которые только что хлебнули крови. Их просто так не убедить сесть в шлюпки и отчалить. Вы понимаете к чему я?";
			link.l1.go = "BS_NPVK_18";
		break;
		
		case "BS_NPVK_18":
			dialog.text = "Прекрасно понимаю. Что ж, склады колонии к вашим услугам, берите сколько можете увезти и наконец покиньте мой остров!";
			link.l1 = "Вот это деловой подход. Приятно работать с понимающим человеком!";
			link.l1.go = "BS_NPVK_18_exit";
			
		break;
		
		case "BS_NPVK_18_exit":
			NextDiag.CurrentNode = "BS_NPVK_19";
			DialogExit();
			SaveCurrentQuestDateParam("BSPrologueEnded");
			AddQuestRecord("BSPrologue", "3");
			CloseQuestHeader("BSPrologue");
			DeleteAttribute(pchar, "BSStart");
			pchar.BSInProgress = true;
			AddDialogExitQuestFunction("BS_NassauSiegeComplete");
		break;
		
		case "BS_NPVK_19":
			dialog.text = "Дело сделано.";
			link.l1 = "Да.";
			Link.l1.go = "BS_NPVK_19_loop";
		break;
		
		case "BS_NPVK_19_loop":
			NextDiag.CurrentNode = "BS_NPVK_19";
			DialogExit();
		break;
		
		case "BS_NPVK_20":
			dialog.text = NPCStringReactionRepeat("Я сейчас занята.", "Зайдите в другой раз.", "А, капитан, рада видеть, но простите, много дел.", "Давайте в другой раз, очень много дел.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Извините.", "Всенепременно.", "Я понимаю.", "Уже ухожу.", npchar, Dialog.CurrentNode);
			Link.l1.go = "BS_NPVK_20_loop";			
		break;
		
		case "BS_NPVK_20_meet":
			if(!CheckAttribute(PChar, "GatriSalutation") || GetQuestPastDayParam ("GatriSalutation") > 0)
			{
				SaveCurrentQuestDateParam("GatriSalutation");
				dialog.text = "Здравствуйте.";
				link.l1 = "Добрый день...";				
			}
			else
			{
				dialog.text = "Вы что-то хотели?";
				link.l1 = "Да...";
			}
			Link.l1.go = "BS_NPVK_20";
		break;
		
		case "BS_NPVK_20_loop":
			NextDiag.CurrentNode = "BS_NPVK_20_meet";
			DialogExit();
		break;
	}
}
