
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);						// 						АВТОРЫ И БЛАГОДАРНОСТИ
	makearef(Link, Dialog.Links);						// Идея квеста, диалоги и кодинг					- Sinistra
	makearef(NextDiag, NPChar.Dialog);					// Модель, текстура и анимация акулы				- IG Baron
														// Иконка кота										- Noctus
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = "(зовёт кого-то) Гатилио... Где же ты, друг мой?.. Гатилио...";
			link.l1 = "Ты кого-то потерял, парень?";
			link.l1.go = "Знакомство_1";
		break;
		
		case "Знакомство_1":
			dialog.text = "Ой, простите, капитан, я вас не заметил. Меня зовут Хорацио, я местный рыбак. Живу здесь у берега и ловлю различных морских обитателей. Этим я и зарабатываю себе на жизнь.";
			link.l1 = "Меня зовут "+GetFullName(pchar)+". Так что у тебя случилось?";
			link.l1.go = "Знакомство_2";
		break;
		
		case "Знакомство_2":
			dialog.text = "Так уж и быть, расскажу я вам, "+pchar.name+". Вчера поздно вечером разыгрался ужасный шторм. И все мои вещи, которые были на берегу, унесло в море. И вот... Мой дорогой друг Гатилио очень любит спать внутри моего сундука...";
			link.l1 = "Погоди, ЧТО?! Зачем сеньор Гатилио вообще полез в сундук?";
			link.l1.go = "Знакомство_3";
		break;
		
		case "Знакомство_3":
			dialog.text = "Потому что Гатилио был очень голоден, а внутри сундука я храню свою добытую рыбу.";
			link.l1 = "Но если во время шторма Гатилио действительно сидел в сундуке, боюсь, его унесло течением, и он утонул вместе с твоими вещами. Его больше нет в живых...";
			link.l1.go = "Знакомство_4";
		break;
		
		case "Знакомство_4":
			dialog.text = "Неправда! Я слышал жалобное мяуканье с той стороны, он точно жив! Я знаю это!";
			link.l1 = "Так твой Гатилио - кот?! Что же ты мне сразу не сказал?";
			link.l1.go = "Знакомство_4_1";
			locCameraFromToPos(1.43, 5.67, -3.17, false, 56.59, 6.38, -11.15);
		break;
		
		case "Знакомство_4_1":
			DialogExit();
			npchar.dialog.filename = "Quest\KotVMeshke.c";
			npchar.dialog.currentnode = "Знакомство_5";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 0.0);
		break;
		
		case "Знакомство_5":
			dialog.text = "Так я сказал. Он мой друг. Как можно было этого не понять\nЕсли вы найдёте мой сундук, то можете забрать себе всё его содержимое как награду. Главное, верните мне назад моего дорогого друга Гатилио. ";
			link.l1 = "Ладно, я поищу твоего кота.";
			link.l1.go = "Согласие_1";
			link.l2 = "Тебе нужно нанять кого-нибудь другого для такой странной работы.";
			link.l2.go = "Отказ_1";
		break;
		
		case "Отказ_1":
			dialog.text = "Вы очень злой человек, капитан. Но да, вы правы, эту работу я вам бы не доверил.";
			link.l1 = "До встречи.";
			link.l1.go = "Отказ_2";
		break;
		
		case "Отказ_2":
			DialogExit();
			DeleteAttribute(npchar, "talker");
			UnmarkCharacter(npchar);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Согласие_1":
			dialog.text = "Благодарю вас, капитан. Я буду ждать вас с моим Гатилио.";
			link.l1 = "Скоро вернусь.";
			link.l1.go = "Согласие_2";
		break;
		
		case "Согласие_2":
			DialogExit();
			DeleteAttribute(npchar, "talker");
			UnmarkCharacter(npchar);
			LAi_SetStayType(npchar);
			
			SetQuestHeader("CSP_KvM");
			AddQuestRecord("CSP_KvM", "1");
			AddQuestUserData("CSP_KvM", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("CSP_KvM_Ribak");
			sld.dialog.filename = "Quest\KotVMeshke.c";
			sld.dialog.currentnode = "ЕщёРаз_1";
			
			pchar.questTemp.CSP_KvM_PoiskGatilio = true;
			
			DeleteAttribute(&locations[FindLocation("SantoDomingo_town")], "private1.QuestClosed");
			
			PChar.quest.CSP_KvM_GatilioVSunduke.win_condition.l1 = "item";
			PChar.quest.CSP_KvM_GatilioVSunduke.win_condition.l1.item = "CSP_KvM_Gatilio";
			PChar.quest.CSP_KvM_GatilioVSunduke.win_condition = "CSP_KvM_GatilioVSunduke";
		break;
		
		case "ЕщёРаз_1":
			dialog.text = "Гатилио... Где же ты...";
			link.l1 = "Найду я твоего кота, не пережививай...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ЕщёРаз_1";
		break;
		
		case "ВозвращаемГатилио_1":
			dialog.text = "Гатилио! Я думал, больше тебя не увижу... (пускает слезу) Гатилио...";
			link.l1 = "Я рад"+GetSexPhrase("","а")+", что всё удачно сложилось.";
			link.l1.go = "ВозвращаемГатилио_2";
			TakeItemFromCharacter(pchar, "CSP_KvM_Gatilio");
			Log_info("Вы вернули Гатилио");
		break;
		case "ВозвращаемГатилио_2":
			dialog.text = "Спасибо, капитан "+GetFullName(pchar)+". Вы человек слова. Я всем расскажу, какой вы прекрасный человек.";
			link.l1 = "Мне правда было приятно помочь тебе и твоему коту. До свидания.";
			link.l1.go = "ВозвращаемГатилио_3";
		break;
		case "ВозвращаемГатилио_3":
			DialogExit();
			
			AddQuestRecord("CSP_KvM", "3");
			AddQuestUserData("CSP_KvM", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("CSP_KvM");
			pchar.questdata.KotVMeshke = 1;
			ChangeCharacterReputation(pchar, 2);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			InterfaceStates.Buttons.Save.enable = true;
			bDisableFastReload = false;
			DeleteAttribute(pchar, "questTemp.CSP_KvM_Akula");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddSimpleRumour("Говорят, что вы спасли кота в Санто-Доминго! Потрясающе!", SPAIN, 10, 1);
		break;
		
		
	}
}
