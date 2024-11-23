void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;
	int i;
	bool hungry = true;
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":

			//dialog.text = "Error";
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.quest.meeting = "1";

			if (npchar.id == "CrazyScientist")
			{
				dialog.text = "Well, wait!";
				link.l1.go = "CS";
			}
			NextDiag.TempNode = "First time";
		break;

		case "DH_Villemstad_merc":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "ContraInterruptWaiting");
			dialog.Text = "I don't think it's worth wasting time.";
			Link.l1 = "I have a similar opinion.";
			Link.l1.go = "DH_Villemstad_merc_exit_to_bank";
		break;

		case "DH_Villemstad_merc_exit_to_bank":
			DialogExit();
			sld = CharacterFromID("Villemstad_usurer");
			//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_Villemstad_usurer";

			sld = CharacterFromID("Villemstad_shipyarder");
			//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_Villemstad_shipyarder"

			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;

		case "DH_Villemstad_shipyarder":
			dialog.Text = "Hello, mein her.";
			Link.l1 = "Hello. I'm not going to cheat - I'm interested in ships, and if possible cheaper.";
			Link.l1.go = "DH_Villemstad_shipyarder_1";
		break;
		case "DH_Villemstad_shipyarder_1":
			dialog.Text = "It's nice to see a man with a small purse, but who knows what he wants. I have a great offer for you.";
			Link.l1 = "And what is it?";
			Link.l1.go = "DH_Villemstad_shipyarder_2";
		break;
		case "DH_Villemstad_shipyarder_2":
			dialog.Text = "Junk, Empress. These are sometimes found in our waters. Surprisingly, it was my compatriots who managed to overtake a whole group of such ships to the Caribbean Sea from the Far East.";
			Link.l1 = "Miracles happen in life, but what's the catch?";
			Link.l1.go = "DH_Villemstad_shipyarder_3";
		break;
		case "DH_Villemstad_shipyarder_3":
			dialog.Text = "You see, this is a confiscation, the former owner was caught on... how should I say, dishonest dealings. And he decided with fright that firing guns at a patrol vessel was a good idea. Of course, his belligerence was quickly reduced. After a very short time, a hemp tie helped him to dance an incendiary dance, it was an interesting sight. But not the point.";
			Link.l1 = "Yes, let's get back to business.";
			Link.l1.go = "DH_Villemstad_shipyarder_4";
		break;
		case "DH_Villemstad_shipyarder_4":
			dialog.Text = "So, they reduced his belligerence with guns, which left certain traces on his junk. In addition, I was forced to buy it out voluntarily and against all rules. And it's hanging on me now like a dead weight.";
			Link.l1 = "Condition?";
			Link.l1.go = "DH_Villemstad_shipyarder_5";
		break;
		case "DH_Villemstad_shipyarder_5":
			dialog.Text = "I must say right away - not the best, but below the waterline I patched up all the holes. So don't drown - don't be afraid.";
			Link.l1 = "The price of the question?";
			Link.l1.go = "DH_Villemstad_shipyarder_6";
		break;
		case "DH_Villemstad_shipyarder_6":
			dialog.Text = "25 тысяч и она ваша. Честно скажу, желающих выкупить её, у меня нет, так что несколько недель, я смогу и потерпеть.";
			NextDiag.TempNode = "DH_Villemstad_shipyarder_wait_money";
			Link.l1 = "Well, I'll take it as soon as I have the money.";
			Link.l1.go = "exit";
			if(sti(pchar.money) >= 25000 && CheckAttribute(pchar, "DH_mercLeft"))
			{
				Link.l1 = "I'll take it.";
				Link.l1.go = "DH_Villemstad_shipyarder_getship";
			}
		break;
		case "DH_Villemstad_shipyarder_wait_money":
			dialog.Text = "Did you bring the money?";
			Link.l1 = "Not yet, there are still some things to settle.";
			Link.l1.go = "exit";
			if(sti(pchar.money) >= 25000 && CheckAttribute(pchar, "DH_mercLeft"))
			{
				Link.l1 = "Yes.";
				Link.l1.go = "DH_Villemstad_shipyarder_getship";
			}
		break;
		case "DH_Villemstad_shipyarder_getship":
			PChar.quest.DHRaceAgainstTime.win_condition.l1 = "location";
			PChar.quest.DHRaceAgainstTime.win_condition.l1.location = "LaVega_town";
			PChar.quest.DHRaceAgainstTime.function = "DHRaceAgainstTime";
			SetQuestHeader("DHRaceAgainstTime");
			AddQuestRecord("DHRaceAgainstTime", "1");

			AddMoneyToCharacter(pchar, -25000);
			DeleteAttribute(pchar, "DH_mercLeft");
			pchar.location.from_sea = "Villemstad_town"
			setWDMPointXZ(pchar.location.from_sea);  // коорд на карте
			pchar.Ship.Type = GenerateShipExt(SHIP_SCHOONER_B, 0, pchar);
			ref shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.SpeedRate        = 17.0;
			shTo.HP = 1900;
			shTo.WindAgainstSpeed = 7.35;
			shTo.TurnRate = 23.0;
			shTo.MaxCrew = 120;
			shTo.MastMultiplier = 1.45;
			shTo.Capacity = 1300;
			SetBaseShipData(pchar);
			pchar.Ship.Name = RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple("Fast Boar", "Fighting Tiger"), "Transporter"), "Antelope"), "Extra"), "Lightning"), "Dolphin"), "Mysterious"), "Terrible");
			SetCrewQuantityFull(pchar);
			ChangeCrewExp(pchar, "Sailors", rand(30)+20);
			ChangeCrewExp(pchar, "Cannoners", rand(30)+20);
			ChangeCrewExp(pchar, "Soldiers", rand(30)+20);
			SetCharacterGoods(pchar, GOOD_SAILCLOTH, 20 + rand(50));
			SetCharacterGoods(pchar, GOOD_PLANKS, 20 + rand(50));
			SetCharacterGoods(pchar, GOOD_RUM, 50 + rand(100));
			// коцаем корабль
			pchar.ship.HP = sti(pchar.ship.HP) - makeint(sti(pchar.ship.HP)*0.05) * (MOD_SKILL_ENEMY_RATE*3);
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));

			InterfaceStates.DisFastTravel = false;
			bDisableLandEncounters = false;

			dialog.Text = "Fine, take it. There were even some supplies left in the hold on the ship, I didn't really want to go in there.";
			Link.l1 = "Thank you. Goodbye.";
			Link.l1.go = "exit";
			npchar.Dialog.Filename = "Common_Shipyard.c";
			NextDiag.TempNode = "first time";
		break;

		case "DH_Villemstad_usurer":
			dialog.Text = "You finally arrived, and I was already starting to worry where you had gone. You know the turbulent times right now, have you heard the latest rumors?";
			Link.l1 = "Rumors are good, but right now my companion and I are interested in business matters.";
			Link.l1.go = "DH_Villemstad_usurer_0_1";
		break;
		case "DH_Villemstad_usurer_0_1":
			dialog.Text = "Yes. Business matters. Do you want to close the contract with the gentleman?";
			Link.l1 = "I wish.";
			Link.l1.go = "DH_Villemstad_usurer_0_2";
		break;
		case "DH_Villemstad_usurer_0_2":
			dialog.Text = "What is your will, " + GetFullName(characterFromId("DH_mercenary"))+". Congratulations, your debt to the bank has been paid.";
			Link.l1 = "...";
			Link.l1.go = "DH_Villemstad_usurer_0_3";
		break;
		case "DH_Villemstad_usurer_0_3":
			DialogExit();
			sld = CharacterFromID("DH_mercenary");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.currentnode = "DH_Villemstad_usurer_0_4";
		break;
		case "DH_Villemstad_usurer_0_4":
			dialog.Text = "Well, sometimes a guy, I don't know about you, but I'm going to get drunk.";
			Link.l1 = "Things are not waiting.";
			Link.l1.go = "DH_Villemstad_usurer_0_5";
		break;
		case "DH_Villemstad_usurer_0_5":
			dialog.Text = "As you wish.";
			npchar.lifeday = 0;
			Link.l1 = "...";
			Link.l1.go = "DH_Villemstad_usurer_0_6";
		break;
		case "DH_Villemstad_usurer_0_6":
			DialogExit();
			pchar.DH_mercLeft = true;
			LocatorReloadEnterDisable("SantaCatalina_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload4_back", false);
			LocatorReloadEnterDisable("SantaCatalina_exittown", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_exittown", "reload2_back", false);

			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			sld = CharacterFromID("Villemstad_usurer");
			Lai_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
			sld.dialog.currentnode = "DH_Villemstad_usurer_0_7";
		break;

		case "DH_Villemstad_usurer_0_7":
			dialog.Text = "Is there something else?";
			Link.l1 = "I'd like to withdraw my contribution.";
			Link.l1.go = "DH_Villemstad_usurer_1";
		break;
		case "DH_Villemstad_usurer_1":
			dialog.Text = "Your contribution... You know, there is some difficulty here...";
			Link.l1 = "What could be the difficulty in returning my money to me?";
			Link.l1.go = "DH_Villemstad_usurer_2";
		break;
		case "DH_Villemstad_usurer_2":
			dialog.Text = "You see... commerce, sometimes deals are successful, sometimes not. Sometimes money is needed urgently, sometimes not.";
			Link.l1 = "But what do your problems have to do with my contribution?";
			Link.l1.go = "DH_Villemstad_usurer_3";
		break;
		case "DH_Villemstad_usurer_3":
			dialog.Text = "Except that I will be able to return the money to you no earlier than in a month - no money at all. But what is a month of respite for old friends?";
			Link.l1 = "Nothing for old friends. However, my pocket is now as empty as your bins, and I need to eat for something this month!";
			Link.l1.go = "DH_Villemstad_usurer_4";
		break;
		case "DH_Villemstad_usurer_4":
			dialog.Text = "You know, I have one thing for connoisseurs, I think it will cover a third of the cost of your contribution.";
			Link.l1 = "And what is it?";
			Link.l1.go = "DH_Villemstad_usurer_6";
		break;
		case "DH_Villemstad_usurer_6":
			dialog.Text = "The crystal skull. Here, look.";
			Link.l1 = "I don't know...";
			Link.l1.go = "DH_Villemstad_usurer_7";
		break;
		case "DH_Villemstad_usurer_7":
			dialog.Text = "It's a pity to part with him, but what can you not do for a friend...";
			Link.l1 = "All right, I got it, I'm gonna charge him with 30 percent and a month's delay on the rest.";
			Link.l1.go = "DH_Villemstad_usurer_8";
		break;
		case "DH_Villemstad_usurer_8":
			LAi_SetOwnerTypeNoGroup(npchar);

			DeleteAttribute(pchar, "BlockOstin");

			Log_Info("You got the crystal skull.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "sculMa"+(drand(2)+1), 1);
			dialog.Text = "Great, it's a pleasure doing business with you.";
			Link.l1 = "I'll be back.";
			Link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp.DH_Villemstad_money");
			NextDiag.TempNode = "DH_Villemstad_usurer_get_money";
			AddQuestRecord("DarkHumanQuestline", "6");
		break;
		case "DH_Villemstad_usurer_get_money":
			dialog.Text = "I'm sorry, but I don't have the right amount yet.";
			Link.l1 = "I'll be back.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "DH_Villemstad_usurer_get_money";
			if (GetQuestPastDayParam("questTemp.DH_Villemstad_money") >= 28)
			{
				AddMoneyToCharacter(pchar, 35000);
				dialog.Text = "I've been waiting for you. Now I am ready to return your contribution. Here you go. I hope you will still want to use my services.";
				Link.l1 = "Well, that's fine. As for the latter, I would not hope.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				npchar.Dialog.Filename = "Usurer_dialog.c";
			}

		break;

		case "DH_mercenary_SK_vavern":
			dialog.Text = "This is where our paths should have parted.";
			Link.l1 = "Yes, you have fulfilled your obligations in full according to the letter and spirit of our agreement. You can receive the second part of your fee in Curacao.";
			Link.l1.go = "DH_mercenary_SK_vavern_1";
		break;
		case "DH_mercenary_SK_vavern_1":
			dialog.Text = "Yes, yes, yes. I know, but given the circumstances, I would prefer to accompany you to the Curacao Bank.";
			Link.l1 = "And what about the others?";
			Link.l1.go = "DH_mercenary_SK_vavern_2";
		break;
		case "DH_mercenary_SK_vavern_2":
			dialog.Text = "The rest will go separately, too big a group will attract too much attention.";
			Link.l1 = "Good.";
			Link.l1.go = "DH_mercenary_SK_vavern_exit";
		break;
		case "DH_mercenary_SK_vavern_exit":
			DialogExit();
			sld = CharacterFromID("SantaCatalina_Smuggler");
			//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_SK_smuggler";

			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;

		case "DH_SK_smuggler":
			dialog.Text = "You again? What can I do for you?";
			Link.l1 = "This gentleman and I need to get to Curacao.";
			Link.l1.go = "DH_SK_smuggler_1";
		break;
		case "DH_SK_smuggler_1":
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
			dialog.Text = "Curacao means it's possible. Two people, not a problem either. The money is on the barrel.";
			Link.l1 = "Get it.";
			Link.l1.go = "DH_SK_smuggler_2";
		break;
		case "DH_SK_smuggler_2":
			AddMoneyToCharacter(pchar, -sti(pchar.money));
			pchar.money = 10;
			//Log_Info("You gave away all the money you had with you.");
			PlaySound("interface\important_item.wav");
			dialog.Text = "Well, that's enough, let's sail.";
			Link.l1 = "...";
			Link.l1.go = "DH_SK_smuggler_exit";
		break;
		case "DH_SK_smuggler_exit":
			DialogExit();
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			npchar.dialog.filename = "Smuggler_Agent_dialog.c";
			DoQuestFunctionDelay("DarkHuman_Villemstad", 1.0);
			WaitDate("",0,0,7,2,25);
		break;

		case "DH_mercenary_SK_gate":
			dialog.Text = "We got there.";
			Link.l1 = "Damn, for thirty whole days! I didn't think it would take so long!";
			Link.l1.go = "DH_mercenary_SK_gate_1";
			PChar.quest.DHLockSK.win_condition.l1 = "location";
			PChar.quest.DHLockSK.win_condition.l1.location = "SantaCatalina_town";
			PChar.quest.DHLockSK.function = "DHLockSK";
		break;
		case "DH_mercenary_SK_gate_1":
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.BlockOstin = true;
			dialog.Text = "I think now you understand why we asked for such a price.";
			Link.l1 = "Yes, I think so.";
			Link.l1.go = "exit";
		break;

		case "DH_mercenary_Amatike_return":
			dialog.Text = "What the hell is going on here?! ";
			Link.l1 = "Has the ship sailed? Are we too late?";
			Link.l1.go = "DH_mercenary_Amatike_return_1";
		break;
		case "DH_mercenary_Amatike_return_1":
			dialog.Text = "Hey, kid! Explain to me what's going on...";
			Link.l1 = "...";
			Link.l1.go = "DH_mercenary_Amatike_return_2_sailor";
		break;
		case "DH_mercenary_Amatike_return_2_sailor":
			DialogExit();
			sld = CharacterFromID("DH_sailor");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_3_sailor";
		break;
		case "DH_mercenary_Amatike_return_3_sailor":
			dialog.Text = "You... You're back, thank God!";
			Link.l1 = "Now we'll find out what's going on here! Where did the ship go? Seven days have not come out yet!";
			Link.l1.go = "DH_mercenary_Amatike_return_4_sailor";
		break;
		case "DH_mercenary_Amatike_return_4_sailor":
			dialog.Text = "Spaniards on the corvette.As soon as you deigned to leave the shore, a Spanish corvette sailed out from behind the cape. The captain gave the order to move away, but this scoundrel was able to catch up with us at the exit of the bay. ";
			Link.l1 = "Next...";
			Link.l1.go = "DH_mercenary_Amatike_return_5_sailor";
		break;
		case "DH_mercenary_Amatike_return_5_sailor":
			dialog.Text = "Take it easy mister, we're all in the same boat here.";
			Link.l1 = "Don't pull it, kid.";
			Link.l1.go = "DH_mercenary_Amatike_return_6_sailor";
		break;
		case "DH_mercenary_Amatike_return_6_sailor":
			dialog.Text = "The corvette fired a volley at the ship, I was thrown off the mast and miraculously fell between the rocks.";
			Link.l1 = "And the ship?";
			Link.l1.go = "DH_mercenary_Amatike_return_7_sailor";
		break;
		case "DH_mercenary_Amatike_return_7_sailor":
			dialog.Text = "Even if our ship is not the strongest, but it is nimble, besides, the corvette's hull was damaged, captain was able to go to sea.";
			Link.l1 = "So, what about you?";
			Link.l1.go = "DH_mercenary_Amatike_return_8_sailor";
		break;
		case "DH_mercenary_Amatike_return_8_sailor":
			dialog.Text = "What about me? They didn't notice me, especially since I hid by the cliff. I saw everything with my own eyes. When the corvette was far enough away, I got to the shore and waited for you, I knew you had to come back.";
			Link.l1 = "Let's say.";
			Link.l1.go = "DH_mercenary_Amatike_return_9";
		break;
		case "DH_mercenary_Amatike_return_9":
			DialogExit();
			sld = CharacterFromID("DH_mercenary");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_10";
		break;
		case "DH_mercenary_Amatike_return_10":
			dialog.Text = "And what should we do with him?";
			Link.l1 = "At the expense.";
			Link.l1.go = "DH_mercenary_Amatike_return_kill";
			Link.l2 = "I don't think he's going to hold us up, and it won't hurt to have extra hands on the way.";
			Link.l2.go = "DH_mercenary_Amatike_return_10_1";
		break;
		case "DH_mercenary_Amatike_return_10_1":
			ChangeCharacterReputation(PChar, 30);
			dialog.Text = "Okay.";
			Link.l1 = "...";
			Link.l1.go = "DH_mercenary_Amatike_return_11";
		break;
		case "DH_mercenary_Amatike_return_kill":
			DialogExit();
			sld = CharacterFromID("DH_sailor");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_kill_1";
			sld = CharacterFromID("DH_mercenary");
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_11";
		break;
		case "DH_mercenary_Amatike_return_11":
			dialog.Text = "What are we going to do next?";
			Link.l1 = "Get to the city on your own.";
			Link.l1.go = "DH_mercenary_Amatike_return_12";

			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
		break;
		case "DH_mercenary_Amatike_return_kill_1":
			ChangeCharacterReputation(PChar, -30);
			dialog.Text = "Please don't touch me!";
			Link.l1 = "Don't twitch like that, then you won't feel anything.";
			Link.l1.go = "exit_fight_sailor";
		break;
		case "DH_mercenary_Amatike_return_12":
			dialog.Text = "It's not a long way to Santa Catalina.";
			Link.l1 = "And the Spanish corvette can return at any moment, plus an observation team.";
			Link.l1.go = "DH_mercenary_Amatike_return_13";
		break;
		case "DH_mercenary_Amatike_return_13":
			dialog.Text = "Got it.";
			Link.l1 = "Fortunately, we have provided for this scenario.";
			Link.l1.go = "DH_mercenary_Amatike_return_14";
		break;
		case "DH_mercenary_Amatike_return_14":
			dialog.Text = "Your truth. On the way?";
			Link.l1 = "Let's go.";
			Link.l1.go = "DH_mercenary_Amatike_return_15_exit";
		break;
		case "DH_mercenary_Amatike_return_15_exit":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);

			LAi_Fade("", "");
			WaitDate("",0,1,3,17,25);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestFunctionDelay("DarkHuman_SK", 1.5);
		break;

		case "DH_mercenary_temple_afterstash":
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetImmortal(sld, true);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetImmortal(sld, true);
			}
			dialog.Text = "Problems? ";
			Link.l1 = "Nothing that can't be handled... As a result.";
			Link.l1.go = "DH_mercenary_temple_afterstash_1";
		break;
		case "DH_mercenary_temple_afterstash_1":
			dialog.Text = "What?";
			Link.l1 = "Everyone is ready to move out, there is no time to waste. The ship is still waiting for us, and there is an alternative way... It will take too long.";
			Link.l1.go = "DH_mercenary_temple_afterstash_2";
		break;
		case "DH_mercenary_temple_afterstash_2":
			dialog.Text = "Yes, but why the rush?";
			Link.l1 = "Time is running out, and another group of Indians may descend at any moment.";
			Link.l1.go = "DH_mercenary_temple_afterstash_3";
		break;
		case "DH_mercenary_temple_afterstash_3":
			dialog.Text = "Indeed... You guys heard, let's get up and move out!";
			Link.l1 = "...";
			Link.l1.go = "DH_mercenary_temple_afterstash_exit";
		break;
		case "DH_mercenary_temple_afterstash_exit":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}

			LocatorReloadEnterDisable("Temple", "reload1_back", false);
			LocatorReloadEnterDisable("Temple", "reload2", true);
			DeleteAttribute(pchar, "CantTakeItems");
		break;

		case "Dark_Incquisitor":
			dialog.Text = "Thank God you are a spa... It's him, kill him!";
			Link.l1 = "...";
			Link.l1.go = "Dark_Incquisitor_fight";
		break;
		case "Dark_Incquisitor_fight":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorTypeNoGroup(npchar);
			sld = CharacterFromID("Dark_Incquisitor1");
			LAi_SetWarriorTypeNoGroup(sld);
			sld = CharacterFromID("Dark_Incquisitor2");
			LAi_SetWarriorTypeNoGroup(sld);
			AddQuestRecord("DarkHumanQuestline", "2");
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1 = "locator";
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1.location = "Temple_Inside";
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1.locator_group = "item";
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1.locator = "item1";
			PChar.quest.DarkHuman_Temple_Stash.function = "DarkHuman_Temple_Stash";
		break;

		case "DH_Ambush":
			dialog.Text = "So we met, my friend. We were told to take you alive, if possible. So drop your weapon!";
			Link.l1 = "Here's another thing, better tell me, who hired you?";
			Link.l1.go = "DH_Ambush_1";
		break;
		case "DH_Ambush_1":
			dialog.Text = "I said drop the weapon!";
			Link.l1 = "I see that we are not having a dialogue... Well, let's do it differently.";
			Link.l1.go = "DH_Ambush_fight";
		break;
		case "DH_Ambush_fight":
			LAi_SetWarriorTypeNoGroup(npchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "DH_mercenary_temple_afterfight":
			dialog.Text = "We put everyone down well. A red-assed rabble, what can they do against a good musket volley... Heh heh heh.";
			Link.l1 = "The way is clear now.";
			Link.l1.go = "DH_mercenary_temple_afterfight_1";
		break;
		case "DH_mercenary_temple_afterfight_1":
			dialog.Text = "Yes, we will stay here. You never know who will come to our souls. And you go why did you come...";
			Link.l1 = "There seems to be someone in the pyramid.";
			Link.l1.go = "DH_mercenary_temple_afterfight_2";
		break;
		case "DH_mercenary_temple_afterfight_2":
			dialog.Text = "And they will be beyond measure to you...";
			Link.l1 = "... to us...";
			Link.l1.go = "DH_mercenary_temple_afterfight_3";
		break;
		case "DH_mercenary_temple_afterfight_3":
			chrDisableReloadToLocation = false;
			dialog.Text = " for saved them.";
			Link.l1 = "...";
			Link.l1.go = "exit";
		break;

		case "DH_mercenary_temple":
			dialog.Text = "There are Indians there, apparently battered.";
			Link.l1 = "How many are there?";
			Link.l1.go = "DH_mercenary_temple_2";
		break;
		case "DH_mercenary_temple_2":
			dialog.Text = "Eight plus a dozen corpses. We are quite capable of overturning them if we act decisively.";
			Link.l1 = "A decisive blow?";
			Link.l1.go = "DH_mercenary_temple_3";
		break;
		case "DH_mercenary_temple_3":
			dialog.Text = "Exactly.";
			Link.l1 = "Go ahead, attack!";
			Link.l1.go = "DH_mercenary_temple_exit";
		break;
		case "DH_mercenary_temple_exit":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SetCharacterTask_FollowCharacter(npchar, PChar);
			LAi_warrior_DialogEnable(npchar, false);
			chrDisableReloadToLocation = true;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				SetCharacterTask_FollowCharacter(sld, PChar);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				SetCharacterTask_FollowCharacter(sld, PChar);
			}

			for (i = 0; i < sti(pchar.maxIndians) * 2; i++)
			{
				sld = CharacterFromID("DHindian" + i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			LAi_group_SetRelation("Jungle_indians", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Jungle_indians", LAI_GROUP_PLAYER, true);
		break;

		case "DH_mercenary_shore":
			dialog.Text = "Good morning boss, we're here.";
			Link.l1 = "Good morning. Is the next target known?";
			Link.l1.go = "DH_mercenary_shore_1";
		break;
		case "DH_mercenary_shore_1":
			dialog.Text = "The pyramid...";
			Link.l1 = "Yes, the pyramid. You know this area better than I do. What do you recommend?";
			Link.l1.go = "DH_mercenary_shore_2";
		break;
		case "DH_mercenary_shore_2":
			dialog.Text = "Firstly, do not waste time, secondly, keep your eyes open and your weapons ready.";
			Link.l1 = "Indians?";
			Link.l1.go = "DH_mercenary_shore_3";
		break;
		case "DH_mercenary_shore_3":
			dialog.Text = "Yes, the damn savages. However, we have a lot of firepower. (nods at the guys nearby)";
			Link.l1 = "Then we really won't waste any time.";
			Link.l1.go = "DH_mercenary_shore_exit";
		break;
		case "DH_mercenary_shore_exit":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_ActorFollowEverywhere(sld, "", -1);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			PChar.quest.DarkHuman_Temple.win_condition.l1 = "location";
			PChar.quest.DarkHuman_Temple.win_condition.l1.location = "Temple";
			PChar.quest.DarkHuman_Temple.function = "DarkHuman_Temple";

			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;

		case "PGG_transporter":
			//LAi_ActorSetSitMode(pchar);
			dialog.Text = "We have arrived, your people are ready to land.";
			Link.l1 = "Excellent, your obligations under the contract are practically fulfilled.";
			Link.l1.go = "PGG_transporter_1";
		break;
		case "PGG_transporter_1":
			dialog.Text = "The boat is waiting.";
			Link.l1 = "Great, waiting time?";
			Link.l1.go = "PGG_transporter_2";
		break;
		case "PGG_transporter_2":
			dialog.Text = "A week from the current date.";
			Link.l1 = "That's right, let's go.";
			Link.l1.go = "PGG_transporter_exit";
		break;
		case "PGG_transporter_exit":
			DialogExit();
			NextDiag.CurrentNode = "Second Time";
			if (npchar.sex != "woman")	npchar.Dialog.FileName = "PGG_dialog.c";
			else	npchar.Dialog.FileName = "PGG_dialog.c";
			//PGG_ChangeRelation2MainCharacter(npchar, 25);
			DoQuestFunctionDelay("DarkHuman_Amatike", 1.0);
			//LAi_SetWarriorType(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_fight_sailor":
			pchar.quest.DH_mercenary.win_condition.l1 = "NPC_Death";
			pchar.quest.DH_mercenary.win_condition.l1.character ="DH_sailor";
			PChar.quest.DH_mercenary.function = "SpeakAfterKill";
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();


			sld = CharacterFromID("DH_mercenary");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetCharacterTask_FollowCharacter(sld, PChar);
			LAi_warrior_DialogEnable(sld, false);
			chrDisableReloadToLocation = true;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				if (CheckAttribute(sld, "model"))
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					SetCharacterTask_FollowCharacter(sld, PChar);
				}

				sld = CharacterFromID("DH_merc_blade" + i);
				if (CheckAttribute(sld, "model"))
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					SetCharacterTask_FollowCharacter(sld, PChar);
				}

			}
		break;

		case "exit_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
	}
}

