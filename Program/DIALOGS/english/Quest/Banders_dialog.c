
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "quest_fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DeliverToBander_Dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
			dialog.text = "Who are you?!";
			link.l1 = "Quiet, don't make any noise. I was sent by your friend who is in the dungeon. " + pchar.questTemp.jailCanMove.Deliver.name + "Do you know someone like that?";
			link.l1.go = "Step_1";
			NextDiag.TempNode = "Second time";
		break;
		case "Step_1":
			dialog.text = "How can you prove that you are not one of the governor's bloodhounds?";
			link.l1 = "I asked you to give me a note. Here she is.";
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;

		case "Step_2":
		dialog.text = "So...(reading). Damn it! He had to get into such a bad mess... Eh, such a thing is disappearing... Listen, sailor, I see "+ GetSexPhrase("you're strong guy", "you're fighting girl") +". And anyway, from pirates, it seems. Don't you want to earn some extra money? And you'll win, and we'll get it.";
					link.l1 = "I always want to earn extra money. What do you suggest?";
					link.l1.go = "Step_3";

			break;

			case "Step_3":
			dialog.text = "I can share information. I don't need it now-I can't make it, but it might be good for you. Just not for free - it costs money, you know it. It's a profitable business, believe me.";
			link.l1 = "How much do you want?";
			link.l1.go = "Step_4";
		break;

		case "Step_4":
			dialog.text = "50000 piastres.";
			if(makeint(Pchar.money) >= 50000)
			{
			link.l1 = "Hmm, it's a big sum. But if it's worth it... I agree.";
			link.l1.go = "Step_5";
			}
			link.l2 = "No. I do not intend to pay for unknown info from unknown guy. I don't buy cats in bags.";
			link.l2.go = "Step_no";
		break;

		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://попытка грабежа
					dialog.text = "Well, well, fine, "+ GetSexPhrase("fell for it, fraerok", "fell for it, fool") +". Come on, give me your money!";
				link.l1 = "Ek the impudent. And your friend said that his friends are generous.";
				link.l1.go = "Step_fight";
				break;
				case 1://кидалово
					AddMoneyToCharacter(pchar, -50000);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));

					dialog.text = "Okay, listen up. I have become reliably aware that in the coming " + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + " off the coast "+ pchar.questTemp.jailCanMove.Deliver.Island.Areal +" there will be two "+ pchar.questTemp.jailCanMove.Deliver.add1 +" merchant ships - '"+ pchar.questTemp.jailCanMove.Deliver.ShipName1 +"' and '"+ pchar.questTemp.jailCanMove.Deliver.ShipName2 +"', with holds full of "+ pchar.questTemp.jailCanMove.Deliver.add +". You can try to intercept them.";
					link.l1 = "Great!";
					link.l1.go = "Step_lay";
				break;
				case 2://наведём на торговый корабль
					AddMoneyToCharacter(pchar, -50000);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));

					dialog.text = "Okay, listen up. I have become reliably aware that in the coming " + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + " off the coast "+ pchar.questTemp.jailCanMove.Deliver.Island.Areal +" there will be two "+ pchar.questTemp.jailCanMove.Deliver.add1 +"Merchant ships - '"+ pchar.questTemp.jailCanMove.Deliver.ShipName1 +"' and '"+ pchar.questTemp.jailCanMove.Deliver.ShipName2 +"', with holds full of "+ pchar.questTemp.jailCanMove.Deliver.add +". You can try to intercept them.";
					link.l1 = "Great!";
					link.l1.go = "Step_trader";
				break;
				case 3://наведём на курьерский корабль
					AddMoneyToCharacter(pchar, -50000);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5+rand(5);
					dialog.text = "Okay, listen. I have become reliably aware that in the coming " + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + " off the coast "+ pchar.questTemp.jailCanMove.Deliver.Island.Areal +" there will be a courier ship "+ pchar.questTemp.jailCanMove.Deliver.add2 +" called '"+ pchar.questTemp.jailCanMove.Deliver.ShipName +"'. He's carrying a whole bunch of jewelry. You can try to intercept him.";
					link.l1 = "Great!";
					link.l1.go = "Step_cureer";
				break;
			}
			break;

		case "Step_fight":
			dialog.text = "If he wasn't such a fool, he would drink rum in a tavern, not slop in a casemate. So you'll ask him all the questions later, ha ha ha! And now the piastres on the barrel, otherwise " + GetSexPhrase("alive", "alive") + "you can't get out of here.";
			link.l1 = "Well, we'll see about that...";
			link.l1.go = "quest_fight";
			link.l2 = "Okay, take the money... The force is not on my side.";
			link.l2.go = "Step_takemoney";
		break;

		case "Step_takemoney":
			dialog.text = "That's it"+ GetSexPhrase("well done", "good girl") +". And our mutual friend will return them to you... Hehe, when he leans back. And come on, stomp out of here quietly...";
			link.l1 = "Damn you!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			AddQuestRecord("GivePrisonFree", "17");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;

		case "Step_lay":
			dialog.text = "Of course, not for nothing... That's it, now come on, hurry up. And come out quietly, don't attract attention.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_lay";//придём - а там пусто
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;

		case "Step_trader":
			dialog.text = "Of course, not for nothing... That's it, now come on, hurry up. And come out quietly, don't attract attention.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_CreateTraderShips";//создание кораблей
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;

		case "Step_cureer":
			dialog.text = "Of course, not for nothing... That's it, now come on, hurry up. And come out quietly, don't attract attention.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "14");
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sText", pchar.questTemp.jailCanMove.Deliver.add2);
			AddQuestUserData("GivePrisonFree", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsCAttack.function = "Deliver_CreateCureerShips";//создание кораблей
			SetFunctionTimerCondition("Deliver_CureerShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;

		case "Step_no":
			dialog.text = "Well, whatever you want. Then get lost, there's nothing more for you and me to talk about.";
			link.l1 = "Okay, goodbye.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "16");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("GivePrisonFree", "sSex1", GetSexPhrase("xia", "as"));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;

		case "Second time":
			dialog.text = "Well, what else? It's said to go quietly.";
			link.l1 = "Okay, I'm on my way...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Second time";
		break;

		case "Man_FackYou":
			dialog.text = "What are you, " + GetSexPhrase("starving, yourself", "fool, yourself") + "are you climbing on a dagger?!";
			link.l1 = LinkRandPhrase("Devil!!", "Carramba!!", "Oh, damn!");
			link.l1.go = "fight";
		break;
	}
}

void GetBandersTradeShore()//выберем остров для торгашей и курьера
{
	pchar.questTemp.jailCanMove.Deliver.Island = GetRandomIslandId();
	pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
	while (pchar.questTemp.jailCanMove.Deliver.Island.Shore == "")
	{
		pchar.questTemp.jailCanMove.Deliver.Island = GetRandomIslandId();
		pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
		if (!isLocationFreeForQuests(pchar.questTemp.jailCanMove.Deliver.Island)) pchar.questTemp.jailCanMove.Deliver.Island.Shore = "";
	}
	pchar.questTemp.jailCanMove.Deliver.Island.Town = FindTownOnIsland(pchar.questTemp.jailCanMove.Deliver.Island);
	if (pchar.questTemp.jailCanMove.Deliver.Island.Town == "" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Caiman" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Terks" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Dominica" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "StLucia")
	{
	pchar.questTemp.jailCanMove.Deliver.Island.Areal = GetConvertStr(pchar.questTemp.jailCanMove.Deliver.Island, "LocLables.txt") + "");
	}
	else
	{
	pchar.questTemp.jailCanMove.Deliver.Island.Areal = XI_ConvertString("Colony" + pchar.questTemp.jailCanMove.Deliver.Island.Town + "Gen");
	}
}

void GetBandersTradeGoods()//выберем товар для торгашей
{
switch (rand(6))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_EBONY;
			pchar.questTemp.jailCanMove.Deliver.add = "ebony";
			break;
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_MAHOGANY;
			pchar.questTemp.jailCanMove.Deliver.add = "mahogany";
			break;
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_SANDAL;
			pchar.questTemp.jailCanMove.Deliver.add = "sandal";
			break;
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_COFFEE;
			pchar.questTemp.jailCanMove.Deliver.add = "coffee";
			break;
		case 4:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_SILK;
			pchar.questTemp.jailCanMove.Deliver.add = "silks";
			break;
		case 5:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_FOOD;
			pchar.questTemp.jailCanMove.Deliver.add = "food";
			break;
		case 6:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_WEAPON;
			pchar.questTemp.jailCanMove.Deliver.add = "weapons";
			break;
	}
}

void GetBandersTradeNation()//выберем нацию торгаша и курьера
{
switch (rand(3))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Nation = SPAIN;
			pchar.questTemp.jailCanMove.Deliver.add1 = "Spanish";
			pchar.questTemp.jailCanMove.Deliver.add2 = "Spanish West India Trading Company";
			break;
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Nation = FRANCE;
			pchar.questTemp.jailCanMove.Deliver.add1 = "French";
			pchar.questTemp.jailCanMove.Deliver.add2 = "French West India Trading Company";
			break;
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Nation = HOLLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "Dutch";
			pchar.questTemp.jailCanMove.Deliver.add2 = "Dutch West India Trading Company";
			break;
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Nation = ENGLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "English";
			pchar.questTemp.jailCanMove.Deliver.add2 = "English West India Trading Company";
			break;
	}
}



