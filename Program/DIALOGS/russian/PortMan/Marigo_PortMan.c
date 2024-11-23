// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// ==> Анжелика Тич: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.AT_PZD_PU"))
			{
				DeleteAttribute(pchar, "questTemp.AT_PZD_taverna")
				DeleteAttribute(pchar, "questTemp.AT_PZD_PU")
				link.l1 = "Подскажите, какие корабли под испанским флагом отмечались у вас за последнюю неделю?";
				link.l1.go = "AT_PZD_PU_1";
				break;
			}
			// <== Анжелика Тич: Портниха знатной дамы
		break;
		
		//============ Анжелика Тич: Портниха знатной дамы
		case "AT_PZD_PU_1":
    		dialog.text = "Под испанским флагом, говорите? Под испанским не так много\nВот. Галеон 'Эрналь Диас' капитана Габриэля де Сегуенса. Два торговых флейта прибыли из Порто Белло вчера. Владельцем обоих указан Андрес Фосека. А также ваш '" + PChar.Ship.Name + "'.";
    		link.l1 = "А галеон откуда?";
    		link.l1.go = "AT_PZD_PU_2";
 		break;
		
		case "AT_PZD_PU_2":
    		dialog.text = "Из Гаваны. Но это то, что указано у меня в документах, о своём маршруте в деталях никто не отчитывался.";
    		link.l1 = "Может вам что-то известно о пассажирах?";
    		link.l1.go = "AT_PZD_PU_3";
 		break;
		
		case "AT_PZD_PU_3":
    		dialog.text = "Сожалею, это всё.";
    		link.l1 = "Да, жаль.";
    		link.l1.go = "AT_PZD_PU_4";
 		break;
		
		case "AT_PZD_PU_4":
    		dialog.text = "Знаете, если вы кого-то ищите, поспрашивайте у местных подёнщиков в порту, они же общаются с прибывающими моряками. Днём, правда, им не до болтовни, но по вечерам они часто разбивают лагеря прямо тут на берегу.";
    		link.l1 = "Благодарю.";
    		link.l1.go = "AT_PZD_PU_5";
 		break;
		
		case "AT_PZD_PU_5":
    		DialogExit();
			
			AddQuestRecord("AT_PZD", "3");
			
			//Сюда ставить матросов у костра
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Matros1", "shipowner_22", "man", "man", 3, HOLLAND, -1, false));
			sld.name = "Палтурс";
			sld.lastname = "Кейт";
			LAi_SetLoginTime(sld, 22.0, 3.99);
			LAi_SetGroundSitType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_MatrosUKostra_1";
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			sld.City = "Marigo";
			ChangeCharacterAddressGroup(sld, "Marigo_town", "sit", "fire1_1");
			
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Matros2", "pirate_19", "man", "man", 3, HOLLAND, -1, false));
			sld.name = "Палтурс";
			sld.lastname = "Кейт";
			LAi_SetLoginTime(sld, 22.0, 3.99);
			LAi_SetGroundSitType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_MatrosUKostra_1";
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			sld.City = "Marigo";
			ChangeCharacterAddressGroup(sld, "Marigo_town", "sit", "fire1_2");
			
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Matros3", "pirate_20", "man", "man", 3, HOLLAND, -1, false));
			sld.name = "Палтурс";
			sld.lastname = "Кейт";
			LAi_SetLoginTime(sld, 22.0, 3.99);
			LAi_SetGroundSitType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_MatrosUKostra_1";
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			sld.City = "Marigo";
			ChangeCharacterAddressGroup(sld, "Marigo_town", "sit", "fire1_3");
			
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Matros4", "shipowner_23", "man", "man", 3, HOLLAND, -1, false));
			LAi_SetLoginTime(sld, 22.0, 3.99);
			LAi_SetActorType(sld);
			LAi_ActorSetLayMode(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			sld.City = "Marigo";
			ChangeCharacterAddressGroup(sld, "Marigo_town", "sit", "fire2_1");
 		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


