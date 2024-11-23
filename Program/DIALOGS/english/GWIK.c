
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	int price = 50000;
	if (CheckOfficersPerk(pchar, "Trader")) price = 10000;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (NPChar.id == "GWIK_char") dialog.text = "Greetings. I am " + GetFullName(NPChar) + ", a representative of the office of the Dutch West India Trading Company on the island of Curacao. Please introduce yourself.";
			else dialog.text = "Greetings. I am " + GetFullName(NPChar) + ", a representative of the office of the Dutch West India Trading Company on the island of San Martin. Please introduce yourself.";
			Link.l1 = "Hello, " + GetFullName(NPChar) + ". I am " + GetFullName(PChar) + ", captain of the ship '" + PChar.ship.name + "'.";
			link.l1.go = "Meet_2";
		break;

		case "Exit":
			NextDiag.CurrentNode = "Meet_2";
			DialogExit();
		break;

		case "Meet_2":
			if (!CheckAttribute(npchar, "met")) dialog.text = "Nice to meet you, Captain. What's the occasion?";
			else dialog.text = "What's the occasion, Captain?";
			if (!CheckAttribute(pchar, "GwikTimer"))
			{
				Link.l1 = "I would like to purchase price information from you in stores across the archipelago.";
				link.l1.go = "trade_info";
			}
			Link.l2 = "Dropped by to say hello, have a nice day.";
			link.l2.go = "exit";
			npchar.met = 1;
		break;

		case "trade_info":
			dialog.text = "Yes, I have such information and I can share it. That's "+price+" piastres.";
			if (sti(pchar.money) >= price)
			{
				Link.l1 = "Okay, here's your money.";
				link.l1.go = "trade_info_2";
			}
			Link.l2 = "I've changed my mind. Have a nice day.";
			link.l2.go = "exit";
		break;

		case "trade_info_2":
			for (int i = 0; i< MAX_COLONIES; i++)
			{
                ref rcolony = &Colonies[i];
			    if (rcolony.id != "Caiman" && rcolony.id != "Panama" && rcolony.nation != "none") SetPriceListByStoreMan(rcolony);
            }
			log_info("Received a list of prices in all stores in the Caribbean Archipelago.");
			PlayStereoSound("notebook");
			AddMoneyToCharacter(pchar,-price);

			dialog.text = "...Here you go, all the information you need is here. I wish you success!";
			Link.l1 = "Thank you. Goodbye!";
			link.l1.go = "exit";
			pchar.GwikTimer = true;
			SetTimerFunction("RefreshGWIK", 0, 0, 15);
		break;
	}
}
