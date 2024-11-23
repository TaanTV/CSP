// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What did you want? Ask.", "I'm listening to you, what's the question?"), "For the second time in a day you're trying to ask a question...", "For the third time in a day you're trying to ask a question again...",
                          "But when will it end?! I have a lot of things to do to manage the affairs of the city, and you're trying to ask all the questions!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, not the place and not the time..."), "Yes, that's right... But not now, later...",
                      "I'll ask, I'll ask... Only later...", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You've already taken everything. What else do you need?", "Is there really anything left that you didn't bring?");
            link.l1 = RandPhraseSimple("Looking around for the last time...", "Checking, maybe I forgot to pick up something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

		case "Slavetrader_HavanaAttack":
			dialog.text = "Damn ladrons! To dare to attack Havana is an unheard-of audacity! What do you need?!";
			link.l1 = "Think carefully and you will understand.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;

		case "Slavetrader_HavanaAttack_1":
			dialog.text = "Gold, of course! What else do you damn people need besides gold? But we don't have it... Except for those pathetic few measures that are in the store's warehouse?";
			link.l1 = "Hehe... No, we're not after gold. We came for the ivory... black ivory. Do you understand what I'm talking about?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;

		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "Haha! I suspected that slaves were your target. Yes, but they are in the fort. Reinforcements are coming now, and not even a leaky cocked hat will be left of your gang.";
				link.l1 = "Oh, the devil! Okay, stay quiet and don't twitch... Let's go! Damn it...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "How... How did you find out about this?";
				link.l1 = "Ha! To gather five thousand slaves in one place and hope that no one will know about it, only a complete idiot can. Yes, they stink all the way to the Tortuga... As you know, we're taking them away.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;

		case "Slavetrader_HavanaAttack_3":
			dialog.text = "Well, you have won, and we are forced to submit to violence. But do not think that you will get away with this robbery and the sinking of two Spanish warships! You will pay dearly for this outrage!";
			link.l1 = "Don't puff up so much, the blow will be enough. Sit still and don't twitch...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterReputation(pchar, -8);
        break;

		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c перегрузом пойдёт
            Log_SetStringToLog("The slaves are loaded onto the ship");
			Log_SetStringToLog("You have 30 days to deliver slaves to your employer");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;

		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterReputation(pchar, -8);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришёл - уберём корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader("Slavetrader");
			pchar.questdata.Rabotorgovets = 1;
			pchar.questTemp.Slavetrader = "End_quest";
        break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

