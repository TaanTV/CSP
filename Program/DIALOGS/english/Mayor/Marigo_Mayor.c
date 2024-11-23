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
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_Gde_Deti"))	//Sinistra квест "Strange things are happening in the archipelago"
			{
				link.l1 = "I am here at the request of the women who are sitting in the gazebo at your residence.";
				Link.l1.go = "PKM_Animists_1";
			}
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_Gubernator_Final"))	//Sinistra квест "Strange things are happening in the archipelago"
			{
				link.l1 = "Your task is completed and the children are returned to their happy parents.";
				Link.l1.go = "PKM_SvtvA_Final";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You've already taken everything. What else do you need?", "Is there really anything left that you didn't bring?");
            link.l1 = RandPhraseSimple("I'm looking around for the last time...", "Checking, maybe I forgot to pick up something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//==> Sinistra квест "Strange things are happening in the archipelago"
		case "PKM_Animists_1":
			dialog.text = "Ah, you wanted to discuss this...";
			link.l1 = "Sorry to remind you of this, but your task is to ensure the safety of the colony's residents.";
			link.l1.go = "PKM_Animists_2";
        break;
		
		case "PKM_Animists_2":
			dialog.text = "You're not holding your tongue, Captain. If you don't want to lose my favor, then refrain from making such statements in the future.What concerns these women... Your reputation allows me to tell you some details.";
			link.l1 = "I'm all ears.";
			link.l1.go = "PKM_Animists_3";
        break;
		
		case "PKM_Animists_3":
			dialog.text = "At about three o'clock in the morning, captain of a merchant ship entering the port saw a black frigate leaving the island under full sail.\nIn the morning, two dead soldiers were found in the port, one of whom was clutching a piece of strange red cloth in his hand.\nIt is likely that the abducted children are no longer on the island. We do not have the necessary funds to equip a search party. Obviously, it won't be easy to find them, Captain.\nMoreover, if you want to take part in the fate of these women, I am ready to give you the necessary powers. I promise to reward you if successful.";
			link.l1 = "Yes, mynheer. I want to find the children and return them to their unhappy mothers. Has captain who saw the frigate left the island yet?";
			link.l1.go = "PKM_Animists_4";
			link.l2 = "No, mynheer. I will not work without an advance payment. Goodbye.";
			link.l2.go = "PKM_Animists_NET";
        break;
		
		case "PKM_Animists_NET":
			DialogExit();
			AddQuestRecord("PKM_Animists", "2");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("xia", "as"));
			CloseQuestHeader("PKM_Animists");
			pchar.questdata.Satanisty = 1;
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Gde_Deti");
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_1")
			sld.lifeday = 0;
			sld = CharacterFromID("PKM_SvtvA_Devushka_2")
			sld.lifeday = 0;
			sld = CharacterFromID("PKM_SvtvA_Devushka_3")
			sld.lifeday = 0;
        break;
		
		case "PKM_Animists_4":
			dialog.text = "Are you taking on this case?! Excellent! I suppose you can find captain at the tavern. His ship is still in port.";
			link.l1 = "I dare not take up any more of your time, Mynheer.";
			link.l1.go = "PKM_Animists_5";
        break;
		
		case "PKM_Animists_5":
			DialogExit();
			AddQuestRecord("PKM_Animists", "3");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Gde_Deti");
			
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvpvA_Capitan_1", "officer_32", "man", "man", 10, HOLLAND, -1, true));
			sld.name = "Gered";
			sld.lastname = "Drabbe";
			FreeSitLocator("Marigo_tavern", "sit3");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Capitan_v_taverne_1";
			LAi_SetSitType(sld);
			if(InterfaceStates.EnabledQuestsMarks)
			{
				sld.quest.questflag.model = "questionmarkY";
			}
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit3");			
        break;
		
		case "PKM_SvtvA_Final":
			dialog.text = "A successful conclusion to this unpleasant story. I'm glad to reward you, Captain. I know you can be relied on in sensitive matters.";
			link.l1 = "Thank you, Mynheer.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Gubernator_Final");
			AddMoneyToCharacter(pchar, 30000);
            AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("PKM_Animists", "38");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			pchar.questTemp.PKM_Animists_GuberMarigo = true;
			if (CheckAttribute(pchar, "questTemp.PKM_Animists_MamaDeti") && CheckAttribute(pchar, "questTemp.PKM_Animists_GuberMarigo") && CheckAttribute(pchar, "questTemp.PKM_Animists_OtetsKlermon") && CheckAttribute(pchar, "questTemp.PKM_Animists_PadreDominges"))
			{
				CloseQuestHeader("PKM_Animists");
				pchar.questdata.Satanisty = 1;
				UnlockAchievement("AchStrannyeDela", 3);
				DeleteAttribute(pchar, "questTemp.PKM_Animists_MamaDeti");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_GuberMarigo");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_OtetsKlermon");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_PadreDominges");
			}
        break;
		
        //==> Одиннадцатый квест исп.линейки: разорение Виллемстада и Мариго.
        case "SpaLine11Quest_DestrHol":
			dialog.text = "Why did Spain attack the Dutch settlements? There is no war between us!!";
			link.l1 = "De facto, you are fighting a war on the side of the French. You help them with money.";
			link.l1.go = "Step_S11_1";
			AfterTownBattle();
        break;
        case "Step_S11_1":
			dialog.text = "Do you have any proof?";
			link.l1 = "We don't need them. Your trading power in the Caribbean has been undermined for a long time, and now try to lend money to Louis. If you find free funds...";
			link.l1.go = "Step_S11_2";
        break;
        case "Step_S11_2":
			dialog.text = "Damn Spain...";
			link.l1 = "Be careful in your expressions, otherwise I'll cut your throat! The Dutch Mynheer...";
			link.l1.go = "exit";
            AddQuestRecord("Spa_Line_11_DestrHolland", "3");
            pchar.questTemp.Q11_Marigo = 1;
            NextDiag.TempNode = "Cupture_after";
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			AddDialogExitQuestFunction("TWN_ExitForPay");
            SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

