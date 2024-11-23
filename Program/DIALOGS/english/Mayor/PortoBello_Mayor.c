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
			if (pchar.questTemp.State == "Sp9SaveCumana_toPortoBello")//квест №9 испанки.
			{
				dialog.text = "Who are you and what do you need?";
				link.l1 = "My name is " + GetFullName(pchar) + ", please read this document. This is a letter of credence addressed to me, signed by Governor General Francisco Oregon y Gascon.";
				link.l1.go = "Step_S10_1";
			}
			if (pchar.questTemp.State == "Sp9SaveCumana_toCompOut")//квест №9 испанки, после того, как 0 компаньонов.
			{
				dialog.text = "So, Captain, glad to see you. What do you say?";
				link.l1 = "I'm here about the assignment. Are you ready to place these galleons at my disposal?";
				link.l1.go = "Step_S10_5";
			}
			if (pchar.questTemp.piratesLine == "Panama_toPortoBello")//пиратка, штурм Панамы
			{
				dialog.text = "";
				link.l1 = "";
				link.l1.go = "Step_S10_5";
			}
		break;
        //==> Девятый квест исп.линейки: сопроводить четыре золотых галеона.
        case "Step_S10_1":
			dialog.text = "Yes, I see it. Very well, I've been waiting for you for a long time. Are you aware of the purpose of your visit here?";
			link.l1 = "In general terms, I kind of owe to escort some ships somewhere...";
			link.l1.go = "Step_S10_2";
  			TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
        break;
        case "Step_S10_2":
			dialog.text = "Hmm, that's right. I am giving you four galleons loaded with gold. You need to deliver them safely to the uninhabited island of Cayman. Is everything clear to you?";
			link.l1 = "Not really... If I may, I will express my opinion on this matter.";
			link.l1.go = "Step_S10_3";
        break;
        case "Step_S10_3":
			dialog.text = "Yes, of course.";
			link.l1 = "I understand when it comes to delivering gold galleons to a fortified city, under the protection of a powerful fort. But to take them to a desert island...";
			link.l1.go = "Step_S10_4";
        break;
        case "Step_S10_4":
			dialog.text = "This is the gathering place for a large squadron that goes to the Old World. A powerful Spanish fleet arriving from Belize will be waiting for you there. So there is no reason to worry, this is our new tactical ploy to fight the Ladrons: they used to guard the approaches to Belize, but this time only reinforced military galleons will come out of there, which the pirates cannot handle\n"+
				          "Is everything clear to you now?";
			link.l1 = "Almost. And where are these galleons, where are their captains?";
			link.l1.go = "Step_S10_5";
        break;
        case "Step_S10_5":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "The captains will be placed at your disposal as soon as you get rid of the extra ships in your squadron. You should only have one of your ships.";
				link.l1 = "I understand. I'll be with you later, as soon as I settle with my squadron...";
				link.l1.go = "exit";
				pchar.questTemp.State = "Sp9SaveCumana_toCompOut";
			}
			else
			{
				dialog.text = "The galleons are on the raid of Porto Bello, and captains are immediately placed at your disposal. Actually, you can start the task immediately.";
				link.l1 = "Very good. Am I limited in time?";
				link.l1.go = "Step_S10_6";
			}
        break;
        case "Step_S10_6":
			dialog.text = "No, the important thing is that all the galleons get to Cayman safely and with the same contents as they are now. I mean the gold. It's currently in the hold of 5,000 ships, which in terms of weight is 10000c.";
			link.l1 = "I understand. Well, I'm getting started.";
			link.l1.go = "Step_S10_7";
        break;
        case "Step_S10_7":
            pchar.questTemp.State = "Sp9SaveCumana_toCompOut";
			AddQuestRecord("Spa_Line_9_FourGolgGaleons", "2");
			AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("en", "on"));
            ref sld;
            for (int i=1; i<=4; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Captain_"+i, "trader_"+(rand(15)+1), "man", "man", 15, SPAIN, -1, true));
                FantomMakeCoolSailor(sld, SHIP_ROTERLOW, "", CANNON_TYPE_CANNON_LBS16, 30, 15, 15);
                FantomMakeCoolFighter(sld, 15, 10, 10, BLADE_SHORT, "pistol1", 0);
                sld.Ship.Cargo.Goods.Balls = 48;
                sld.Ship.Cargo.Goods.Grapes = 10;
                sld.Ship.Cargo.Goods.Knippels = 48;
                sld.Ship.Cargo.Goods.Bombs = 48;
                sld.Ship.Cargo.Goods.Weapon = 0;
                sld.Ship.Cargo.Goods.Powder = 80;
				sld.Ship.Cargo.Goods.Food = 300;
				sld.Ship.Cargo.Goods.Gold= 1250;
				SetCharacterRemovable(sld, false);
				sld.CompanionEnemyEnable = false;
				sld.Abordage.Enable = false; // НЕЛЬЗЯ!
                SetCompanionIndex(pchar, -1, sti(sld.index));
                Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition.l1 = "location";
                Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition.l1.location = "Caiman";
                Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition = "Sp9SaveCumana_toCaimanBattle";
            }
			DialogExit();
        break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("You've already taken everything. What else do you need?", "Is there really anything left that you didn't bring?");
            link.l1 = RandPhraseSimple("Looking around for the last time...", "Checking, maybe I forgot to pick up something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
        //==> пиратка, штурм Панамы
        case "PQ8_MayorPortoBello":
			dialog.text = "The devil!!! How quickly did you manage to take the city!";
			link.l1 = "Ha! I understand your surprise. But this is just the beginning...";
			link.l1.go = "Step_P1_1";
			AfterTownBattle();
        break;
        case "Step_P1_1":
			dialog.text = "We knew that an attack on Panama was being prepared. You took my city, but you will never take Panama... The jungle will destroy your entire pack.";
			link.l1 = "This is no longer your concern. By the way, how did you know about the campaign?";
			link.l1.go = "Step_P1_2";
        break;
        case "Step_P1_2":
			dialog.text = "For me? From the Governor-General. And how he found out, I have no idea.";
			link.l1 = "Clear. Well, that's interesting...";
			link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
			AddDialogExitQuestFunction("PQ8_MorganInPortoBello");
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

