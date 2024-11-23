// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать ворпос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                          "Да когда же это кончится?! У меня дел полно по управлению делами города, а ты все вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                      "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_ONV_VedmaKaznena"))	//Квест "Охота на ведьму". Ведьма казнена
			{
				link.l1 = "Я напоминаю, что вы просили передать в руки правосудия женщину, которая связана с убийством вашего секретаря, Бартоломью Ольстера.");
				link.l1.go = "PDM_ONV_VedmaKaznena";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Вы уже все забрали. Что вам ещё нужно?", "Неужели осталось ещё что-то, что вы не прихватили?");
            link.l1 = RandPhraseSimple("Осматриваюсь напоследок...", "Проверяю, может забыл"+ GetSexPhrase("","а") +" что забрать...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//************************** Квестовые штрумы ************************
       //==> Третий квест англ.линейки: нападение на Белиз.
        case "EngLine3Quest_BelizAttack":
			dialog.text = "Проклятье!!! Что тебе нужно"+ GetSexPhrase(", чёртов ладрон","") +"?!!";
			link.l1 = "Догадайся с трёх раз.";
			link.l1.go = "Step_E3_1";
			AfterTownBattle();
        break;

        case "Step_E3_1":
            dialog.text = "Золото...";
			link.l1 = "Вот видишь, ты сам все знаешь. Мы забираем золото и уходим, а ты остаёшься в живых... при одном условии.";
			link.l1.go = "Step_E3_2";
        break;

        case "Step_E3_2":
            dialog.text = "Каком условии?";
			link.l1 = "Ты скажешь, где спрятано золото, приготовленное к отправке в Испанию.";
			link.l1.go = "Step_E3_3";
        break;

        case "Step_E3_3":
            dialog.text = "А если не скажу?";
			link.l1 = "Хм, сначала тебе будет очень страшно, потом очень больно. А затем ты все расскажешь, только жить после всего этого не сможешь - очень уж серьёзные будут повереждения на твоём теле...";
			link.l1.go = "Step_E3_4";
        break;

        case "Step_E3_4":
            dialog.text = "Ни секунды не сомневаюсь, что всё это будет реализовано. Наслышан...\n"+
                          "Золото в форте. Поищите там как следует и найдёте без труда.";
			link.l1 = "Вы только что сохранили себе жизнь и здоровье. Поздравляю и желаю здравствовать также впредь, сеньор.";
			link.l1.go = "Step_E3_5";
        break;

        case "Step_E3_5":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("Henry Morgan")], true);
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("Jackman")], true);
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("John Morris")], true);
            DoReloadCharacterToLocation("Beliz_fort",  "goto", "goto61");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "Beliz_fort", "goto", "goto13");
			LAi_SetStayType(characterFromID("Henry Morgan"));
			characters[GetCharacterIndex("Henry Morgan")].dialog.currentnode = "Gold_found_in_fort";
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))   // Эта фигня нужна для определения, взял ли ГГ этих перцев на дело. Если нет, то и их в форте не будет.
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Beliz_fort", "goto", "goto72");
                LAi_SetStayType(characterFromID("Jackman"));
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "Gold_found_in_fort";
            }
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "Beliz_fort", "goto", "goto01");
                LAi_SetStayType(characterFromID("John Morris"));
                characters[GetCharacterIndex("John Morris")].dialog.currentnode = "Gold_found_in_fort";
            }
            LAi_LocationFightDisable(&Locations[FindLocation("Beliz_fort")], true);
            // ==> Делёж золота. Можно не брать Джекмена и Джона Морриса вообще в эскадру.
            // === Квест будет выполнен, а золото поделено соответственно.
            pchar.questTemp.BelizGoldQty = 3300 / sti(pchar.questTemp.CompanionQuantity);   // Нужно для контроля продаж золота Моргану, чтоб не продавать возможно уже существующее у ГГ золото.
			// грузим ГГ и его эскадру (не квестовые)
            SetCharacterGoods(pchar, GOOD_GOLD, GetCargoGoods(pchar, GOOD_GOLD) + sti(pchar.questTemp.BelizGoldQty));// перегруз
            if (IsCompanion(characterFromID("Henry Morgan")))   {AddCharacterGoodsSimple(characterFromID("Henry Morgan"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));}
            if (IsCompanion(characterFromID("Jackman")))        {AddCharacterGoodsSimple(characterFromID("Jackman"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));}
            if (IsCompanion(characterFromID("John Morris")))    {AddCharacterGoodsSimple(characterFromID("John Morris"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));}
            Log_SetStringToLog("Испанское золото перегружено в трюмы кораблей.");
            InterfaceStates.Buttons.Save.enable = false;
            chrDisableReloadToLocation = true;
        break;
		
//********************** //Квест "Охота на ведьму". Ведьма казнена ************************
		case "PDM_ONV_VedmaKaznena":
            dialog.text = "О, да, я получил письмо от святого отца Антонио де Соуза об этом дьявольском создании, и о её судьбе. Вы хорошо поработали, капитан. Я от всего сердца благодарю вас за помощь в этом деле. Полагаю, не так легко было найти её. Я предлагаю скромную плату - 50000 эскудо в знак своей благодарности.";
            link.l1 = "Спасибо, сеньор губернатор. До свидания!";
            link.l1.go = "PDM_ONV_Nagrada";
			AddMoneyToCharacter(pchar, 50000);
        break;

		case "PDM_ONV_Nagrada":
			AddQuestRecord("PDM_Ohota_na_vedmu", "15");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("PDM_Ohota_na_vedmu");
			pchar.questdata.OhotaNaVedmu = 1;
			DeleteAttribute(pchar, "questTemp.PDM_ONV_VedmaKaznena");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddSimpleRumour("Капитан, говорят, что вы сумели поймать ведьму Марию Карлэ! Неужели это правда?! Невероятно!!", SPAIN, 7, 1);

            DialogExit();
        break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
