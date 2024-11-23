//navy 26.07.06
//генератор дуэлей...
//в диалоге НПС делаем линк с проверкой флага оскорбления... по нему переход на "outraged"
//если НПС сделал что-то ГГ (продажа фальшивки) или ГГ наехал на НПС, вешаем на него флаг.
//для некоторых, например ПГГ, можно делать переход сразу на вызов: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//флаг убираем
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("How dare you insult me, bastard?!", "You will pay dearly for your words!"),
				RandPhraseSimple("You have offended my honor, " + GetAddress_Form(NPChar) + "! You'll have to pay for it.", "How dare you? Take back your words immediately!"));

		//это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar,
				RandPhraseSimple("Huh??!! Yes, I don't want to dirty my sword about you!", "Huh??!! I don't even want to dirty my sword about you!"),
				RandPhraseSimple("I am always at your service!", "I do not intend to choose expressions when talking to trash!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() +
				RandPhraseSimple("I didn't mean to...", "I lost my temper..."),
				RandPhraseSimple("It was a mistake. I'm sorry.", "I'm mistaken, " + GetAddress_FormToNPC(NPChar) + ". Please forgive me.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,
				RandPhraseSimple("I'll cut off your ears!", "I'll cut out your heart!"),
				RandPhraseSimple("I hope you will apologize immediately, or I cannot vouch for myself!", "Do you understand what this means?"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() +
				RandPhraseSimple("I hope your sword is as fast as your tongue!", "My blade will speak for me."),
				RandPhraseSimple("I challenge you to a duel!", "This is a matter of honor!")), "let_s_duel",
					NPCharRepPhrase(pchar,
				RandPhraseSimple("I guess I'm not ready to face the devil yet!", "I think you shouldn't get so excited! These are just words!"),
				RandPhraseSimple("I just remembered, someone is waiting for me. All the best...", "Ah! It seems my ship is already sailing.")), "change_mind");
		break;

	case "let_s_duel":
		//проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "You should deal with the others first, and then we'll talk.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "You and I have already agreed on everything.";
			}
			link.l1 = RandSwear() + "How did I forget...";
			link.l1.go = "exit";
			break;
		}
		//может отказаться.
		if (drand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))         //WW
		{
			Dialog.Text = RandPhraseSimple("A duel?!!! Get lost, you're not worth the time.", "A duel? Too much honor! Get lost!");
			link.l1 = RandPhraseSimple("Well, well...", "I can wait...");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)
			if (drand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))    //WW
			{
				link.l1 = RandPhraseSimple("Well, we'll see about that now!!!", "What are you saying?! Now I'm going to see the color of your blood!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("A duel, you say? I guess I don't mind stretching.",
			"Do you even know which side of the sword to hold?");
		link.l1 = RandPhraseSimple("You will be on your knees begging for mercy.", "I will finish you off with these hands, merza"+ GetSexPhrase("vetz","vka") +"!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text + " Or we can go out to sea and see who's better!",
				"A duel?!! Ha, I'll crush you like a flea! Choose how you die!");
			link.l2 = RandPhraseSimple("I have no equal at sea.", "My ship will sink your old trough!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "I changed my mind...";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("I don't see your ship in port...", "Get lost until you find yourself at least some kind of trough!!!");
		link.l1 = RandPhraseSimple("My mistake...", "...Then I'm leaving you.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "Well, I'll be waiting for you at the exit of the bay...";
			link.l1 = "You won't have to wait long.";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//на суше
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear() + RandPhraseSimple("Take out your blade and we'll see what color your blood is!", "Well, if you want to die so much...");
		link.l1 = RandPhraseSimple("We'd better go where there are fewer witnesses. I know a place outside the city gates. I'll meet you there in " + iHour + " hours.",
			"Hey... Not so fast. It's better to do such things without witnesses. Come in " + iHour + " hours to the entrance to the city.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("Well, if you're in such a hurry to die...", "Damn it! I'll help you go to hell!!!");
		link.l2.go = "fight_right_now";
		link.l3 = "I changed my mind...";
		link.l3.go = "change_mind";

		if (drand(1))
		{
			Dialog.Text = RandSwear() + RandPhraseSimple("I think we should go outside the city gates. I'll be waiting for you there via " + pchar.questTemp.Duel.WaitTime + " hours. Don't stay too long!",
				"This is not the best place for proceedings. We'd better get out of town. Through " + pchar.questTemp.Duel.WaitTime + " I'll be there in an hour.");
			link.l1 = RandPhraseSimple("Too much honor! Defend yourself!", "I don't have time! Get your blade out!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("Well, let's take a walk.", "Maybe you're right. I'll meet you outside the gate.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "Let's go outside." рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("Too much honor! Defend yourself!", "I don't have time! Here and now!");
		link.l1 = RandPhraseSimple("Well, if you're in such a hurry to die...", "Damn it! I'll help you go to hell!!!");
		link.l1.go = "fight_right_now";
		if (drand(1))
		{
			Dialog.Text = RandPhraseSimple("Well, let's take a walk.", "Perhaps you're right. I'll meet you outside the gate.");
			link.l1 = RandPhraseSimple("Waiting for you there.", "Don't be late.");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//что ж, пойдём выйдем
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//где?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//приходит ко времени.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//на случай, если не дождётся, часа вполне достаточно
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi"))
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "Well, are you ready to go to hell?";
		link.l1 = "Yes. Now let's see who's who!";
		link.l1.go = "fight_right_now";
		link.l2 = "No, I decided to apologize to you. I was wrong, lost my temper.";
		link.l2.go = "change_mind";
		if (drand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))  //WW
		{
			Dialog.Text = RandPhraseSimple("Listen, I've been thinking and finally realized that I was wrong. I apologize",
				"Damn it! It's all rum!!! Sorry, "+ GetSexPhrase("brother","sister") +"!");
			link.l1 = NPCharRepPhrase(pchar,
				RandPhraseSimple("Well, no, now only your blood can bring me satisfaction!", "Take out your sword, and there's nothing to snot here!"),
				RandPhraseSimple("No! I demand satisfaction!", "You are a disgrace to your family! Get out your sword!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar,
				RandPhraseSimple("Well, I agree. Overreacted.", "What are the scores between your own!!"),
				RandPhraseSimple("Perhaps you are right. It is not worth shedding blood over trifles.", "My generosity knows no bounds! You are forgiven!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//дуэли быть!
	case "fight_right_now":
		if(findsubstr(npchar.id, "PsHero_" , 0) != -1)
		{
			LAi_SetCheckMinHP(npchar, 1, true, "PGG_CheckHPDuel");
			SaveCurrentQuestDateParam("pchar.questTemp.DuelCooldown");
			chrDisableReloadToLocation = true;
		}
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	                  //WW  ?????
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//передумал, э... не хорошо ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("Then get out of here!", "Hide then. Otherwise I might change my mind."),
				RandPhraseSimple("In that case, I dare not detain you any longer!", "Then you'd better leave before I change my mind."));
		link.l1 = "I'm already leaving...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("Get out of here!", "Hide. Otherwise I might change my mind."),
				RandPhraseSimple("What can I do for you"+ NPCharSexPhrase(NPChar,"en","on") +"?", "Did you want something?"));
		link.l1 = "I'm leaving.";
		link.l1.go = "peace";
		break;

	//мир и все такое.
	case "peace":
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;

	case "Duel_Won":
		LAi_SetCurHPMax(npchar);
		Dialog.text = "Damn it! I give up.";
		link.l1 = "I am today"+GetSexPhrase("kind","kind")+". Get out of here.";
		link.l1.go = "duel_nomoney";
		link.l2 = "Excellent. Now turn out your pockets!";
		link.l2.go = "duel_money";
		NextDiag.TempNode = "Second time";
		break;
	case "duel_nomoney":
		ChangeCharacterReputation(pchar, 10);
		PGG_ChangeRelation2MainCharacter(npchar, 20);
		Dialog.text = "Damn it, are you serious? I'm not saying I would do the same thing if I were you. I won't forget that.";
		link.l1 = "Go ahead before I change my mind.";
		link.l1.go = "duel_exit";
		break;
	case "duel_money":
		ChangeCharacterReputation(pchar, -25);
		PGG_ChangeRelation2MainCharacter(npchar, -30);
		AddMoneyToCharacter(pchar, sti(npchar.money)/3);
		AddMoneyToCharacter(npchar, -sti(npchar.money)/3);
		Dialog.text = "Oh you, "+GetSexPhrase("scoundrel","scoundrel")+"! Well, never mind, I'll get even with you.";
		link.l1 = "I'll be looking forward to it.";
		link.l1.go = "duel_exit";
		if (!CheckAttribute(npchar, "PGGAi.Boosted"))
		{
			Train_PPG(npchar, true, true);
		}
		break;
	case "duel_exit":
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), npchar.PGGAi.location.town+"_Tavern", "", "", "", 10.0);
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_SetImmortal(npchar, false);
		DialogExit();
		break;

	case "TreasureHunterPGG":
		NextDiag.CurrentNode = "Second time";
		//dialog.text = "Wait a minute, "+ GetSexPhrase("buddy","girlfriend") +"... I think you have something interesting. It is necessary to share the found treasures with your loved ones.";
		dialog.text = RandPhraseSimple("I suspected that this crook sold more than one map. No wonder I killed him.","Wait a minute, "+ GetSexPhrase("buddy","girlfriend") +". This map is mine. I don't know exactly how you got it, but a crook stole it from me drunk. So these treasures don't belong to you. ");
	    //if (PGG_ChangeRelation2MainCharacter(npchar, 0) < 41)
		if (sti(npchar.reputation) < 40)
		{
			dialog.text = "You were so blind you didn't notice the spying all the way to the treasure.";
			Link.l1 = "Well, it's time to separate your head from your body.";
			Link.l1.go = "battleTreasure";
			break;
		}
		Link.l1 = "Yeah, it's an awkward situation. You know, I won't give this treasure away just like that, because I didn't get this map for nothing, and the way here wasn't close. But I don't want to quarrel with you. I suggest we split the loot.";
		Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
        Link.l2 = "Well, everything happens in life, you're not lucky. Now get out of the way!";
		Link.l2.go = "NoMoney_1";
		break;
	case "battleTreasure":
        AddDialogExitQuest("Battle_PGGHunters_Land");
		PChar.quest.PGGbattleTreasure.win_condition.l1 = "NPC_Death";
		PChar.quest.PGGbattleTreasure.win_condition.l1.character = npchar.id;
		PChar.quest.PGGbattleTreasure.function = "T102_DoorUnlock";
        DialogExit();
        break;
	case "Cost_Head":
			PChar.HunterCost = MOD_SKILL_ENEMY_RATE*3/4 * sti(npchar.rank) * 1000 + rand(1000);
			dialog.text = "Even so? I have already been ready to take up arms.\nWell, I don't mind. I think " + sti(PChar.HunterCost) + " piastres will suit me.";
			if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "I don't have enough money.";
                Link.l1.go = "NoMoney";
            }
			else
			{
                Link.l1 = "So be it, take it.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "It is unclear to whom to give such an amount... I'd rather just stab you!!!";
                Link.l2.go = "NoMoney";
            }
	break;
	case "NoMoney":
			dialog.text = "In that case, the conversation is over!";
			ChangeCharacterReputation(pchar, -15);
			Link.l1 = "It looks like it.";
			Link.l1.go = "battleTreasure";
		break;
	case "NoMoney_1":
			dialog.text = "No way! You're not going anywhere with my treasure!";
			ChangeCharacterReputation(pchar, -15);
			Link.l1 = "In that case, it's time to separate your head from your body.";
			Link.l1.go = "battleTreasure";
	break;
	case "Cost_Head2":
        AddMoneyToCharacter(pchar, -(sti(PChar.HunterCost)));
		PGG_AddMoneyToCharacter(npchar, (sti(PChar.HunterCost)));
		ChangeCharacterReputation(pchar, 15);
		PGG_ChangeRelation2MainCharacter(npchar, 40);
		chrDisableReloadToLocation = false;
        dialog.text = "You are "+GetSexPhrase("not a bad guy","nice girl")+"! Thank you for your understanding. I hope we will meet again, I would've drank with you.";
		Link.l1 = "It's a tempting offer. If the opportunity comes up, we will definitely have a drink!";
		Link.l1.go = "Cost_Head3";
        break;
	case "Cost_Head3":
        AddDialogExitQuest("GoAway_PGGHunters_Land");
        DialogExit();
        break;

	case "Play_Game":
		bool allow = false;
		if (!CheckAttribute(pchar,"questTemp.pgggamesplayed"+npchar.index)) allow = true;
		if (GetQuestPastDayParam("questTemp.pgggamesplayed"+npchar.index) > 0) allow = true;
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 40 && allow)
		{
			DeleteAttribute(pchar,"questTemp.pgggamesplayed"+npchar.index);
			dialog.text = "What do you suggest?";
			link.l1 = "Play cards.";
			link.l1.go = "Card_Game";
			link.l2 = "Roll the dice.";
			link.l2.go = "Dice_Game";
			link.l10 = "I'm sorry, but I have things to do.";
			link.l10.go = "exit";
		}
		else
		{
			dialog.text = LinkRandPhrase ("Maybe I want to, but not with you", "Fuck off, I'm not up to you right now!", "You know what? " + LinkRandPhrase("I've already lost everything.", "I'm not in the mood, fuck off", "I'm not in the mood, fuck off."));
			link.l10 = "As you know, it's your business.";
			link.l10.go = "exit";
		}
	break;
	// карты -->
	case "Card_Game":
		if (isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < 1+rand(2))
		{
			dialog.text = "Shoo from here, I'm not in the mood.";
			link.l1 = "Whatever you want.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Come on, let's play...";
			link.l1 = "Wonderful.";
			link.l1.go = "Cards_begin";
			link.l2 = "What are the rules of the game?";
			link.l2.go = "Cards_Rule";
		}
	break;

	case "Cards_Rule":
		dialog.text = XI_ConvertString("CardsRules")
		link.l1 = "Well, let's get started!";
		link.l1.go = "Cards_begin";
		link.l3 = "No, it's not for me...";
		link.l3.go = "exit";
	break;

	case "Cards_begin":
		Dialog.text = "Let's decide on the bet.";
		link.l1 = "Playing 500 coins per card.";
		link.l1.go = "Cards_Node_100";
		link.l2 = "Let's play 2000 gold per card.";
		link.l2.go = "Cards_Node_500";
		link.l3 = "I think I should go.";
		link.l3.go = "exit";
	break;

	case "Cards_Node_100":
		if (sti(pchar.Money) < 15000)
		{
			dialog.text = "Are you kidding? You don't have any money!";
			link.l1 = "It happens.";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 15000)
		{
			dialog.text = "Enough is enough for me, otherwise there will be no money left for the maintenance of the ship...";
			link.l1 = "Sorry.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Okay, let's play for 500 coins.";
		link.l1 = "Let's get started!";
		link.l1.go = "Cards_begin_go";
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate     = 500;
		pchar.GenQuest.Cards.SitType   = false;
	break;

	case "Cards_Node_500":
		if (sti(pchar.Money) < 60000)
		{
			dialog.text = "Are you kidding? You don't have money for such bets!";
			link.l1 = "They will!";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 60000)
		{
			dialog.text = "No, such bets will not do any good.";
			link.l1 = "Whatever.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Okay, we're playing for 2000 coins.";
		link.l1 = "Let's get started!";
		link.l1.go = "Cards_begin_go";
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate     = 2000;
		pchar.GenQuest.Cards.SitType   = false;
	break;

	case "Cards_begin_go":
		SaveCurrentQuestDateParam("questTemp.pgggamesplayed"+npchar.index);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchCardsGame();
	break;
	// карты <--
	//  Dice -->
	case "Dice_Game":
		if (isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < 1+rand(2))
		{
			dialog.text = "Get out of here, I'm not in the mood.";
			link.l1 = "As you wish.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Come on! Rest has never been harmful to health... only the wallet...";
			link.l1 = "Wonderful.";
			link.l1.go = "Dice_begin";
			link.l2 = "What are the rules of the game?";
			link.l2.go = "Dice_Rule";
		}
	break;

	case "Dice_Rule":
		dialog.text = XI_ConvertString("DiceRules");
		link.l1 = "Well, let's get started!";
		link.l1.go = "Dice_begin";
		link.l3 = "No, it's not for me...";
		link.l3.go = "exit";
	break;

	case "Dice_begin":
		Dialog.text = "Let's decide on the bet.";
		link.l1 = "We play 200 coins per dice.";
		link.l1.go = "Dice_Node_100";
		link.l2 = "Let's play 1000 gold per dice.";
		link.l2.go = "Dice_Node_500";
		link.l3 = "I think I should go.";
		link.l3.go = "exit";
	break;

	case "Dice_Node_100":
		if (!CheckDiceGameSmallRate())
		{
			dialog.text = "Fame is unsurpassed about you, fraud. I won't play dice with you at all.";
			link.l1 = "Everyone is lying! Well, you don't need to.";
			link.l1.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 15000)
		{
			dialog.text = "Are you kidding? You don't have any money!";
			link.l1 = "It happens.";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 15000)
		{
			dialog.text = "That's it! We need to stop playing games, otherwise they will write us down as embezzlers and write us ashore...";
			link.l1 = "Sorry.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Okay, let's play for 200 coins.";
		link.l1 = "Let's get started!";
		link.l1.go = "Dice_begin_go";
		pchar.GenQuest.Dice.npcharIdx = npchar.index;
		pchar.GenQuest.Dice.iRate     = 200;
		pchar.GenQuest.Dice.SitType   = false;
	break;

	case "Dice_Node_500":
		if (!CheckDiceGameSmallRate())
		{
			dialog.text = "Fame is unsurpassed about you, fraud. I won't play dice with you at all.";
			link.l1 = "Everyone is lying! Well, you don't need to.";
			link.l1.go = "exit";
			break;
		}
		if (!CheckDiceGameBigRate())
		{
			dialog.text = "I heard that you play very well. I won't play with you at such high stakes.";
			link.l1 = "Let's get lower rates?";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Sorry, I have to go.";
			link.l2.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 60000)
		{
			dialog.text = "Are you kidding? You don't have that much money!";
			link.l1 = "They will!";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 60000)
		{
			dialog.text = "No, such bets will not do any good.";
			link.l1 = "Whatever.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Okay, let's play 1000 coins per die.";
		link.l1 = "Let's get started!";
		link.l1.go = "Dice_begin_go";
		pchar.GenQuest.Dice.npcharIdx = npchar.index;
		pchar.GenQuest.Dice.iRate     = 1000;
		pchar.GenQuest.Dice.SitType   = false;
	break;

	case "Dice_begin_go":
		SaveCurrentQuestDateParam("questTemp.pgggamesplayed"+npchar.index);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchDiceGame();
	break;

// Квест ПГГ Виспер

	case "Whisper_Officer":
		Dialog.Text = "Greetings, Captain. I would like to ask you a favor.";
		link.l1 = "Hmm. What are you talking about?";
		link.l1.go = "Quest_Whisper";
		sld.PGGWhisperQuestStart = true;
	break;
	
	case "Quest_Whisper":
		npchar.PGGWhisperQuestStart = true;//предложит только один раз? если отказать, то повтора не будет. 

		Dialog.Text = "This is a serious matter, I will not discuss it in front of everyone. Shall we continue in my room?";
		link.l1 = "Let's go.";
		link.l1.go = "Quest_Whisper_Room";
		link.l2 = "I've heard a lot"+GetSexPhrase("","а")+"that you bring bad luck in any business, I'd better stay away from you.";
		link.l2.go = "exit";
	break;

	case "Quest_Whisper_Room":
		chrDisableReloadToLocation = true;
		DoReloadCharacterToLocation(GetCurrentTown() + "_tavern_upstairs","goto","goto1");
		ChangeCharacterAddressGroup(npchar, GetCurrentTown() + "_tavern_upstairs", "goto", "goto1");
		pchar.InstantDialog = npchar.id;

		npchar.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
		npchar.dialog.currentnode   = "Quest_Whisper_1";
		DoQuestFunctionDelay("InstantDialog", 1);
		DialogExit();
	break;

	case "Quest_Whisper_1":
		dialog.text = "So, the job is not easy, but the jackpot that we can grab is worth the risk.";
		link.l1 = "I'm listening.";
		link.l1.go = "Quest_Whisper_2";
	break;

	case "Quest_Whisper_2":
		dialog.text = "Didn't you lock the door behind you?";
		link.l1 = "...";
		link.l1.go = "Quest_Whisper_2_exit";
		for (int i = 1; i < 4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PGG_Whisper_Incquisitor"+i, "PGG_Vincento_"+(2+i), "man", "man", MOD_SKILL_ENEMY_RATE*3/2, PIRATE, 1, false));
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
		}
	break;

	case "Quest_Whisper_2_exit":
		DialogExit();
		sld = CharacterFromId("PGG_Whisper_Incquisitor3");
		sld.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
		sld.dialog.currentnode   = "Quest_Whisper_3";
		pchar.InstantDialog = sld.id;
		DoQuestFunctionDelay("InstantDialog", 0);
	break;
// <-- Квест ПГГ Виспер
	}
}
