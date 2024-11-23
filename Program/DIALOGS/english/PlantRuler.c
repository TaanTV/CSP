
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int slaveCount, i, companion, slavePartCount;

	switch(Dialog.CurrentNode)
	{
		case "Meet":
			dialog.text = "Greetings. I am " + GetFullName(NPChar) + ", the head of the Barbados plantation. Please introduce yourself.";
			Link.l1 = "Hello, " + GetFullName(NPChar) + ". I am " + GetFullName(PChar) + ", captain of the ship '" + PChar.ship.name + "'.";
			link.l1.go = "Meet_2";
		break;

		case "Exit":
			NextDiag.CurrentNode = "Meet_2";
			DialogExit();
		break;

		case "Meet_2":
			if (!CheckAttribute(npchar, "met")) dialog.text = "Nice to meet you. What's the occasion?";
			else dialog.text = "What's the occasion, Captain?";

			if (sti(npchar.SlavesLimit) > 0)
			{
				slaveCount = sti(PChar.Ship.Cargo.Goods.Slaves);

				for (i = 1; i < COMPANION_MAX; i++)
				{
					companion = GetCompanionIndex(PChar, i);
					if(companion != -1 && GetRemovable(&Characters[companion]))
						slaveCount += sti(Characters[companion].Ship.Cargo.Goods.Slaves);
				}

				if (slaveCount > 0)
				{
					NPchar.HeroSlaveCount = slaveCount;
					Link.l1 = "I offer you to buy... goods.";
					link.l1.go = "trade_good";
				}
			}
			Link.l2 = "Just dropped by, have a nice day.";
			link.l2.go = "exit";
			npchar.met = 1;
		break;

		case "trade_good":
			dialog.text = "Goods? Do you mean slaves?";
			Link.l1 = "Yes, exactly.";
			link.l1.go = "trade_good_2";
			Link.l2 = "I've changed my mind. Have a nice day.";
			link.l2.go = "exit";
		break;

		case "trade_good_2":
			dialog.text = "Plantation assets allow me to purchase up to 1000 slaves every two weeks from private individuals. How much do you want to offer?";
			Link.l1 = (NPchar.HeroSlaveCount) + " slaves.";
			link.l1.go = "trade_good_3";
			Link.l2 = "I've changed my mind. Have a nice day.";
			link.l2.go = "exit";
		break;

		case "trade_good_3":
			slaveCount = func_min(sti(NPchar.HeroSlaveCount), sti(NPchar.SlavesLimit));
			dialog.text = "Now I can buy up to " + slaveCount + " slaves at 215 per unit. Total, " + FindRussianMoneyString(slaveCount * 215) + ". Are you satisfied?";
			Link.l1 = "Quite.";
			link.l1.go = "trade_good_4";
			Link.l2 = "I've changed my mind. Have a nice day.";
			link.l2.go = "exit";
		break;

		case "trade_good_4":
			slaveCount = func_min(sti(NPchar.HeroSlaveCount), sti(NPchar.SlavesLimit));

			AddMoneyToCharacter(PChar, 215 * slaveCount);
			npchar.SlavesLimit = sti(npchar.SlavesLimit) - slaveCount;

			slavePartCount = func_min(slaveCount, sti(PChar.Ship.Cargo.Goods.Slaves));
			PChar.Ship.Cargo.Goods.Slaves = sti(PChar.Ship.Cargo.Goods.Slaves) - slavePartCount;
			slaveCount -= slavePartCount;

			for (i = 1; (i < COMPANION_MAX) && (slaveCount > 0); i++)
			{
				companion = GetCompanionIndex(PChar, i);
				if(companion != -1 && GetRemovable(&Characters[companion]))
				{
					slavePartCount = func_min(slaveCount, sti(Characters[companion].Ship.Cargo.Goods.Slaves));
					Characters[companion].Ship.Cargo.Goods.Slaves = sti(Characters[companion].Ship.Cargo.Goods.Slaves) - slavePartCount;
					slaveCount -= slavePartCount;
				}
			}

			SetTimerFunction("RefreshSlavesLimit", 0, 0, 14);
			dialog.text = "Here you go, here's your money.";
			Link.l1 = "Thank you.";
			link.l1.go = "exit";
		break;
	}
}
