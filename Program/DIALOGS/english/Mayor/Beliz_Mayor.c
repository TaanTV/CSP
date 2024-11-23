// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What did you want? Ask.", "I'm listening to you, what's the question?"), "For the second time in a day you're trying to ask a question...", "For the third time in a day you're trying to ask a question again...",
                          "But when will it end?! I have a lot of things to do to manage the affairs of the city, and you're trying to ask all the questions!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, not the place and not the time..."), "Yes, that's right... But not now, later...",
                      "I'll ask, I'll ask... Only later...", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_ONV_VedmaKaznena"))	//Квест "The witch hunt.". Ведьма казнена
			{
				link.l1 = "I remind you that you asked to bring to justice a woman who is connected with the murder of your secretary, Bartholomew Ulster.");
				link.l1.go = "PDM_ONV_VedmaKaznena";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You've already taken everything. What else do you need?", "Is there really anything left that you didn't bring?");
            link.l1 = RandPhraseSimple("Looking around for the last time...", "Checking, maybe I forgot to pick up something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//************************** Квестовые штрумы ************************
       //==> Третий квест англ.линейки: нападение на Белиз.
        case "EngLine3Quest_BelizAttack":
			dialog.text = "Damn it!!! What do you need"+ GetSexPhrase(", damn ladron", "") +"?!!";
			link.l1 = "Guess three times.";
			link.l1.go = "Step_E3_1";
			AfterTownBattle();
        break;

        case "Step_E3_1":
            dialog.text = "Gold...";
			link.l1 = "You see, you know everything yourself. We take the gold and leave, and you stay alive... on one condition.";
			link.l1.go = "Step_E3_2";
        break;

        case "Step_E3_2":
            dialog.text = "What condition?";
			link.l1 = "You will tell me where the gold is hidden, ready to be shipped to Spain.";
			link.l1.go = "Step_E3_3";
        break;

        case "Step_E3_3":
            dialog.text = "And if I don't tell you?";
			link.l1 = "Hmm, at first you will be very scared, then it will hurt a lot. And then you'll tell me everything, but you won't be able to live after all this - there will be very serious injuries on your body...";
			link.l1.go = "Step_E3_4";
        break;

        case "Step_E3_4":
            dialog.text = "I don't doubt for a second that all this will be implemented. I've heard..\n"+
                          "The gold is in the fort. Search there properly and you will find it without difficulty.";
			link.l1 = "You have just saved your life and health. Congratulations and I wish you good health in the future, senor.";
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
            Log_SetStringToLog("Spanish gold is loaded into the holds of ships.");
            InterfaceStates.Buttons.Save.enable = false;
            chrDisableReloadToLocation = true;
        break;
		
//********************** //Квест "The witch hunt.". Ведьма казнена ************************
		case "PDM_ONV_VedmaKaznena":
            dialog.text = "Oh yes, I have received a letter from Father Antonio de Souza about this diabolical creature and its fate. You have done well, Captain. I thank you from the bottom of my heart for your help in this matter. I guess it wasn't so easy to find her. I offer a modest fee of 200,000 escudos as a token of my gratitude. And also accept from me this unusual, incredibly powerful musket - Hornet.";
            link.l1 = "Thank you, Mr. Governor. Goodbye!";
            link.l1.go = "PDM_ONV_Nagrada";
			AddMoneyToCharacter(pchar, 50000);
        break;

		case "PDM_ONV_Nagrada":
			AddQuestRecord("PDM_Ohota_na_vedmu", "15");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("PDM_Ohota_na_vedmu");
            pchar.questdata.OhotaNaVedmu = 1;
			DeleteAttribute(pchar, "questTemp.PDM_ONV_VedmaKaznena");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddSimpleRumour("Captain, they say that you managed to catch the witch Maria Carle! Is this really true?! Unbelievable!!", SPAIN, 7, 1);

            DialogExit();
        break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

