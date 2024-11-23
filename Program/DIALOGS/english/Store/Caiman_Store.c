// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bGoldMine, bSilverMine, bIronMine;
	bGoldMine = false;
	bSilverMine = false;
	bIronMine = false;

	if(CheckAttribute(PChar, "ColonyBuilding.GoldMine.BuildingTime"))
	{
		bGoldMine = PChar.ColonyBuilding.GoldMine == true && PChar.ColonyBuilding.GoldMine.BuildingTime == false;
	}
	if(CheckAttribute(PChar, "ColonyBuilding.SilverMine.BuildingTime"))
	{
		bSilverMine = PChar.ColonyBuilding.SilverMine == true && PChar.ColonyBuilding.SilverMine.BuildingTime == false;
	}
	if(CheckAttribute(PChar, "ColonyBuilding.IronMine.BuildingTime"))
	{
		bIronMine = PChar.ColonyBuilding.IronMine == true && PChar.ColonyBuilding.IronMine.BuildingTime == false;
	}

	int iCost = 0;
	string sString = "";
	int iQty = 0;

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Ask me what you want?",
                          "We just brought up this topic. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Listen, this is a store, people are buying something here. Don't distract me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, I forgot...",
                      "Yeah, really for the third time...", "Um, I won't...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			link.l2 = "I would like to talk about supplying the colony with necessary goods.";
			link.l2.go = "Colony_1";

			link.l3 = "I want to talk to you about the auto-sale of mined ores and goods in mines and plantations.";
			link.l3.go = "AutoSell_1";
		break;


		case "Colony_1":
			dialog.Text = "Oh, that's what you mean. What exactly are you interested in?";
			Link.l1 = "The cost of supplying some facilities.";
			Link.l1.go = "Cost";
			Link.l2 = "Tell me more about it.";
			Link.l2.go = "AutoPurchase";

			if(PChar.ColonyBuilding.Colony.AutoPurchase == false)
			{
				Link.l3 = "I would like to take advantage of the opportunity to supply the colony.";
				Link.l3.go = "Colony_AutoPurchase";
			}
			else
			{
				Link.l3 = "It is necessary to suspend the supply of the colony.";
				Link.l3.go = "Colony_OffAutoPurchase";
			}

			if(bGoldMine || bSilverMine || bIronMine)
			{
				if(PChar.ColonyBuilding.Mines.AutoPurchase == false)
				{
					Link.l4 = "I would like to take advantage of the opportunity to supply the mines.";
					Link.l4.go = "Mines_AutoPurchase";
				}
				else
				{
					Link.l4 = "It is necessary to suspend the supply of mines.";
					Link.l4.go = "Mines_OffAutoPurchase";
				}
			}

			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.ColonyBuilding.Plantation.AutoPurchase == false)
				{
					Link.l5 = "I would like to take advantage of the opportunity to supply the plantation.";
					Link.l5.go = "Plantation_AutoPurchase";
				}
				else
				{
					Link.l5 = "It is necessary to suspend the supply of the plantation.";
					Link.l5.go = "Plantation_OffAutoPurchase";
				}
			}

			Link.l6 = "I'm sorry, " + npchar.name + "I need to take my leave.";
			Link.l6.go = "exit";
		break;

		case "Colony_AutoPurchase":
			dialog.Text = "Excellent, Captain! Make no mistake, from this day on, I will seriously take care of it.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "Colony_AutoPurchase_Yes";
			Link.l2 = "Uh.. I've changed my mind.";
			Link.l2.go = "exit";
		break;

		case "Colony_AutoPurchase_Yes":
			PChar.ColonyBuilding.Colony.AutoPurchase = true;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Mines_AutoPurchase":
			dialog.Text = "Excellent, Captain! Make no mistake, from this day on, I will seriously take care of it.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "Mines_AutoPurchase_Yes";
			Link.l2 = "Uh.. I've changed my mind.";
			Link.l2.go = "exit";
		break;

		case "Mines_AutoPurchase_Yes":
			PChar.ColonyBuilding.Mines.AutoPurchase = true;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Plantation_AutoPurchase":
			dialog.Text = "Excellent, Captain! Make no mistake, from this day on, I will seriously take care of it.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "Plantation_AutoPurchase_Yes";
			Link.l2 = "Uh.. I've changed my mind.";
			Link.l2.go = "exit";
		break;

		case "Plantation_AutoPurchase_Yes":
			PChar.ColonyBuilding.Plantation.AutoPurchase = true;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Colony_OffAutoPurchase":
			dialog.Text = "Are you sure, Captain?";
			Link.l1 = LinkRandPhrase("Of course. Too expensive.", "Sure.", "Too expensive.");
			Link.l1.go = "Colony_OffAutoPurchase_Yes";
			Link.l2 = LinkRandPhrase("Uh.. You're right, you shouldn't do that.", "Hmm... I've changed my mind.", "Set aside!");
			Link.l2.go = "exit";
		break;

		case "Colony_OffAutoPurchase_Yes":
			PChar.ColonyBuilding.Colony.AutoPurchase = false;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Mines_OffAutoPurchase":
			dialog.Text = "Are you sure, Captain?";
			Link.l1 = LinkRandPhrase("Of course. Too expensive.", "Sure.", "Too expensive.");
			Link.l1.go = "Mines_OffAutoPurchase_Yes";
			Link.l2 = LinkRandPhrase("Uh.. You're right, you shouldn't do that.", "Hmm... I've changed my mind.", "Set aside!");
			Link.l2.go = "exit";
		break;

		case "Mines_OffAutoPurchase_Yes":
			PChar.ColonyBuilding.Mines.AutoPurchase = false;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Plantation_OffAutoPurchase":
			dialog.Text = "Are you sure, Captain?";
			Link.l1 = LinkRandPhrase("Of course. Too expensive.", "Sure.", "Too expensive.");
			Link.l1.go = "Plantation_OffAutoPurchase_Yes";
			Link.l2 = LinkRandPhrase("Uh.. You're right, you shouldn't do that.", "Hmm... I've changed my mind.", "Set aside!");
			Link.l2.go = "exit";
		break;

		case "Plantation_OffAutoPurchase_Yes":
			PChar.ColonyBuilding.Plantation.AutoPurchase = false;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Cost":
			dialog.Text = "What objects do you mean? The full cost or taking into account the current filling of warehouses?";
			Link.l1 = "The full cost of supplying the colony.";
			Link.l1.go = "Cost_Colony_Full";
			Link.l2 = "The cost of supplying the colony, taking into account the current filling of warehouses.";
			Link.l2.go = "Cost_Colony";

			if(bGoldMine || bSilverMine || bIronMine)
			{
				Link.l3 = "The full cost of supplying the mines.";
				Link.l3.go = "Cost_Mines_Full";
				Link.l4 = "The cost of supplying the mines, taking into account the current filling of warehouses.";
				Link.l4.go = "Cost_Mines";
			}

			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				Link.l5 = "The full cost of supplying the plantation.";
				Link.l5.go = "Cost_Plantation_Full";
				Link.l6 = "The cost of supplying the plantation, taking into account the current filling of warehouses.";
				Link.l6.go = "Cost_Plantation";
			}

			Link.l7 = "I'm sorry, " + npchar.name + "I need to take my leave.";
			Link.l7.go = "exit";
		break;

		case "Cost_Colony_Full":
			iCost = GetSumAutoPurchaseColonyGoods("Colony", false);
			dialog.Text = "At the moment, taking into account the storage capacity, the total cost of supplying the colony is: " + iCost + " piastres.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "quests";
		break;

		case "Cost_Colony":
			iCost = GetSumAutoPurchaseColonyGoods("Colony", true);
			dialog.Text = "At the moment, taking into account the storage capacity, the cost of supplying the colony, taking into account the current filling, is: " + iCost + " piastres.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "quests";
		break;

		case "Cost_Mines_Full":
			iCost = GetSumAutoPurchaseColonyGoods("Mines", false);
			dialog.Text = "At the moment, taking into account the storage capacity, the total cost of supplying the mines is: " + iCost + " piastres.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "quests";
		break;

		case "Cost_Mines":
			iCost = GetSumAutoPurchaseColonyGoods("Mines", true);
			dialog.Text = "At the moment, taking into account the storage capacity, the cost of supplying the mines, taking into account the current filling, is: " + iCost + " piastres.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "quests";
		break;

		case "Cost_Plantation_Full":
			iCost = GetSumAutoPurchaseColonyGoods("Plantation", false);
			dialog.Text = "At the moment, taking into account the storage capacity, the total cost of supplying the plantation is: " + iCost + " piastres.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "quests";
		break;

		case "Cost_Plantation":
			iCost = GetSumAutoPurchaseColonyGoods("Plantation", true);
			dialog.Text = "At the moment, taking into account the storage capacity, the cost of supplying the plantation, taking into account the current filling, is: " + iCost + " piastres.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "quests";
		break;

		case "AutoPurchase":
			dialog.Text = "Timely supply of the population implies filling the warehouses of the colony and other buildings with the missing amount of essential goods - food, medicines and even tools. The availability of the necessary amount of these goods will guarantee a good life in the colony. Timely replenishment of urban and other warehouses will help to avoid diseases and hunger. For example, to fill the colony's warehouse with food and medicines at the moment, you will need " + GetSumAutoPurchaseColonyGoods("Colony", true) + " piastres. The supply does not stop at the colony - it is possible to supply facilities such as mines and plantations. Every few days, the supply of your chosen buildings is carried out, and if the colony's treasury has the necessary amount, then everything will be successful. In addition, since I am the one doing this, the purchase of goods will cost much cheaper than in other colonies. If you want to take advantage of this offer, then just tell me about it.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "exit";
		break;

		//////////////////////////////////////////////////////////////////////////
		// АВТО СБЫТ
		//////////////////////////////////////////////////////////////////////////
		case "AutoSell_1":
			dialog.text = "What exactly did you want to know about this, Captain?";
			link.l1 = "I would like to review the auto sales facilities.";
			link.l1.go = "AutoSell_SetAction";
			link.l2 = "I want to set the quantity of the goods being sold.";
			link.l2.go = "AutoSell_SetQty";
			link.l3 = "The latest prices at which the goods is sold.";
			link.l3.go = "AutoSellCosts";
			link.l4 = "I want to know more about this.";
			link.l4.go = "AutoSellInfo";
			link.l5 = "Sorry, I have a lot to do.";
			link.l5.go = "exit";
		break;

		case "AutoSell_SetAction":
			dialog.text = "Hmm, let's see. " + GetColonyAutoSellWork();

			if(PChar.Mines.GoldMine == true || PChar.Mines.SilverMine == true || PChar.Mines.IronMine == true)
			{
				if(PChar.ColonyBuilding.Mines.AutoSell == false)
				{
					link.l1 = "I want the goods to be sold from the mines warehouse.";
					link.l1.go = "AutoSell_Mines_On_1";
				}
				else
				{
					link.l1 = "I want to suspend the sale of goods from the mines warehouse.";
					link.l1.go = "AutoSell_Mines_Off_1";
				}
			}

			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.ColonyBuilding.Plantation.AutoSell == false)
				{
					link.l2 = "I want the goods to be sold from the plantation warehouse.";
					link.l2.go = "AutoSell_Plantation_On_1";
				}
				else
				{
					link.l2 = "I want to suspend the sale of goods from the plantation warehouse.";
					link.l2.go = "AutoSell_Plantation_Off_1";
				}
			}

			link.l3 = "I think I've changed my mind.";
			link.l3.go = "exit";
		break;

		case "AutoSell_Mines_On_1":
			dialog.text = "Are you sure, Captain?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure.");
			link.l1.go = "AutoSell_Mines_On_2";
			link.l2 = LinkRandPhrase("Mm... Perhaps you're right - it's worth thinking more.", "I've changed my mind.", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "AutoSell_Mines_On_2":
			PChar.ColonyBuilding.Mines.AutoSell = true;
			dialog.text = "All right, Captain! I will deal with this issue from today.";
			link.l1 = "That's nice.";
			link.l1.go = "exit";
		break;

		case "AutoSell_Plantation_On_1":
			dialog.text = "Are you sure, Captain?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure.");
			link.l1.go = "AutoSell_Plantation_On_2";
			link.l2 = LinkRandPhrase("Mm... Perhaps you're right - it's worth thinking more.", "I've changed my mind.", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "AutoSell_Plantation_On_2":
			PChar.ColonyBuilding.Plantation.AutoSell = true;
			dialog.text = "All right, Captain! I will deal with this issue from today.";
			link.l1 = "That's nice.";
			link.l1.go = "exit";
		break;

		case "AutoSell_Mines_Off_1":
			dialog.text = "Do you really want to suspend the sale of mined goods?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure.");
			link.l1.go = "AutoSell_Mines_Off_2";
			link.l2 = LinkRandPhrase("Set aside!", "I've probably changed my mind - we need to sell the loot in a timely manner.", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "AutoSell_Mines_Off_2":
			PChar.ColonyBuilding.Mines.AutoSell = false;
			dialog.text = "As you wish, Captain. In that case, as soon as you decide to resume the sale of goods from the mines again, come.";
			link.l1 = LinkRandPhrase("Thank you.", "Clear.", "Good.");
			link.l1.go = "exit";
		break;

		case "AutoSell_Plantation_Off_1":
			dialog.text = "Do you really want to suspend the sale of the goods extracted from the plantation?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure.");
			link.l1.go = "AutoSell_Plantation_Off_2";
			link.l2 = LinkRandPhrase("Set aside!", "I've probably changed my mind - we need to sell the loot in a timely manner.", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "AutoSell_Plantation_Off_2":
			PChar.ColonyBuilding.Plantation.AutoSell = false;
			dialog.text = "As you wish, Captain. In that case, as soon as you decide to resume the sale of goods from the plantation again, come.";
			link.l1 = LinkRandPhrase("Thank you.", "Clear.", "Good.");
			link.l1.go = "exit";
		break;

		case "AutoSell_SetQty":
			if(PChar.ColonyBuilding.Mines.AutoSell == false && PChar.ColonyBuilding.Plantation.AutoSell == false)
			{
				dialog.text = "Captain, at the moment the auto-sale of goods is not carried out either in the mines or on the plantation.";
				link.l1 = LinkRandPhrase("Thank you.", "Clear.", "Good.");
				link.l1.go = "exit";
				break;
			}

			dialog.text = "Current quantity of goods sold for mines: " + GetColonyAutoSellCurrentQty("Mines") + ", and for the plantation: " + GetColonyAutoSellCurrentQty("Plantation") + ". The maximum quantity of goods sold for mines is " +AUTO_SELL_MINES_MAX+ ", for plantations: " +AUTO_SELL_PLANTATION_MAX+ ".";

			if(PChar.ColonyBuilding.Mines.AutoSell == true)
			{
				link.l1 = "It is necessary to change the quantity of goods sold at the mines.";
				link.l1.go = "AutoSell_SetQty_Mines_1";
			}

			if(PChar.ColonyBuilding.Plantation.AutoSell == true)
			{
				link.l2 = "It is necessary to change the quantity of goods sold on the plantation.";
				link.l2.go = "AutoSell_SetQty_Plantation_1";
			}

			link.l3 = "I think I've changed my mind.";
			link.l3.go = "exit";
		break;

		case "AutoSell_SetQty_Mines_1":
			dialog.text = "So, what quantity do you want to set for the sale of goods in the mines?";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "AutoSell_SetQty_Mines_2";
		break;

		case "AutoSell_SetQty_Mines_2":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);

			if(iQty <= 0)
			{
				dialog.text = "Are you kidding?";
				link.l1 = "Let's try again...";
				link.l1.go = "AutoSell_SetQty_Mines_1";
				link.l2 = "I've changed my mind.";
				link.l2.go = "exit";
				break;
			}

			if(iQty > AUTO_SELL_MINES_MAX)
			{
				dialog.text = iQty + "? Captain, I warned you that the maximum quantity for the sale of goods produced at the mines is " + AUTO_SELL_MINES_MAX + " pcs.";
				link.l1 = "Let's try again...";
				link.l1.go = "AutoSell_SetQty_Mines_1";
				link.l2 = "I've changed my mind.";
				link.l2.go = "exit";
				break;
			}

			dialog.text = iQty + "? Well, that's an acceptable figure. Are you sure about your decision?";
			link.l1 = "Yes, absolutely.";
			link.l1.go = "AutoSell_SetQty_Mines_3";
			link.l2 = "No, I've changed my mind.";
			link.l2.go = "exit";
		break;

		case "AutoSell_SetQty_Mines_3":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);

			PChar.ColonyBuilding.Mines.AutoSell.Qty = iQty;
			dialog.text = "All right, captain.";
			link.l1 = "That's nice.";
			link.l1.go = "exit";
		break;

		case "AutoSell_SetQty_Plantation_1":
			dialog.text = "So, what quantity do you want to set for the sale of goods on the plantation?";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "AutoSell_SetQty_Plantation_2";
		break;

		case "AutoSell_SetQty_Plantation_2":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);

			if(iQty <= 0)
			{
				dialog.text = "Are you kidding?";
				link.l1 = "Let's try again...";
				link.l1.go = "AutoSell_SetQty_Plantation_1";
				link.l2 = "I've changed my mind.";
				link.l2.go = "exit";
				break;
			}

			if(iQty > AUTO_SELL_PLANTATION_MAX)
			{
				dialog.text = iQty + "? Captain, I warned you that the maximum quantity for the sale of goods extracted on the plantation is " + AUTO_SELL_PLANTATION_MAX + " pcs.";
				link.l1 = "Let's try again...";
				link.l1.go = "AutoSell_SetQty_Plantation_1";
				link.l2 = "I've changed my mind.";
				link.l2.go = "exit";
				break;
			}

			dialog.text = iQty + "? Well, that's an acceptable figure. Are you sure about your decision?";
			link.l1 = "Yes, absolutely.";
			link.l1.go = "AutoSell_SetQty_Plantation_3";
			link.l2 = "No, I've changed my mind.";
			link.l2.go = "exit";
		break;

		case "AutoSell_SetQty_Plantation_3":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);

			PChar.ColonyBuilding.Plantation.AutoSell.Qty = iQty;
			dialog.text = "All right, captain.";
			link.l1 = "That's nice.";
			link.l1.go = "exit";
		break;

		case "AutoSellCosts":
			dialog.text = "Gold: " + GetCurrentGoodBaseCostForAutoSell(GOOD_GOLD) + " piastres; Silver: " + GetCurrentGoodBaseCostForAutoSell(GOOD_SILVER) + " piastres; Iron: " + GetCurrentGoodBaseCostForAutoSell(GOOD_IRON) + " piastres; Sugar: " + GetCurrentGoodBaseCostForAutoSell(GOOD_SUGAR) + " piastres; Coffee: " + GetCurrentGoodBaseCostForAutoSell(GOOD_COFFEE) + " piastres.";
			link.l1 = "Thanks for the information. Let's talk more about the sale.";
			link.l1.go = "AutoSell_1";
			link.l2 = "Thanks for the information. I think I'll go.";
			link.l2.go = "exit";
		break;

		case "AutoSellInfo":
			dialog.text = "In order for the plantation and mines to bring income to the colony in a timely manner, you can use the auto-sale of goods from warehouses every time after the extraction of ores and goods.\nEach time, the number of items you specify will be allocated for sale from warehouses.  There is a maximum number of ores and goods for one-time sale - each ore from the mines you can sell no more than " +AUTO_SELL_MINES_MAX+ " pcs., and the goods extracted on the plantation no more than " +AUTO_SELL_PLANTATION_MAX+ " pcs.\nIf the quantity of goods in stock is less than the quantity you specified for sale, then all available goods of this type are for sale. If the goods is sold in this way, you will receive a notification about each such operation. It is important to note that the sale of ores and goods will be carried out at prices that are cheaper than for self-sale, since I take care of all the costs of finding buyers and transportation.";
			link.l1 = LinkRandPhrase("Thank you.", "Clear.", "Good.");
			link.l1.go = "exit";
		break;
	}

	UnloadSegment(NPChar.FileDialog2);
}

