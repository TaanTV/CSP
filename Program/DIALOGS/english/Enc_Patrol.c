void ProcessDialogEvent()
{
	ref NPChar, sld;
	ref arItem;
	aref Link, Diag;
	int i, iShipType, iShipGoods;
	int jewelType;
	string sItemName = "";
	string sItem;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;
	string sTemp1, sTemp2;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "exit_fight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple("Ah, it seems like "+ GetSexPhrase("this bastard raised", "this bastard raised") +" alarm in " + XI_ConvertString("Colony" + npchar.city + "Dat") + "! Grab "+ GetSexPhrase("him", "her") +"!!", "Heh, just look at it! Some " + NationNamePeople(sti(pchar.nation))+ " manage to be at enmity with " + NationNameAblative(sti(npchar.nation)) + "! Grab the scoundrel!!!");
				}
				else
				{
					dialog.text = RandPhraseSimple("An enemy agent is near" + XI_ConvertString("Colony" + npchar.city + "Gen") + "! Take "+ GetSexPhrase("him", "her") +"!!", "Look at this, " + NationNamePeople(sti(pchar.nation))+ " walking around almost in " + XI_ConvertString("Colony" + npchar.city + "Dat") + "! Grab him immediately!!!");
				}
				link.l2 = RandPhraseSimple("Try it, we're alone here...", "Heh, there's no help for you here.");
				link.l2.go = "exit_fight";
				if (IsCharacterPerkOn(pchar, "Adventurer") || IsCharacterPerkOn(pchar, "Agent"))
				{
					link.l1 = RandPhraseSimple("You've made a mistake, "+GetAddress_Form(NPChar)+"! I am a law-abiding person.", "Why such aggression? Can I just take a walk?");
					link.l1.go = "CheckPeg";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("I have the honor to introduce myself! I am the patrol chief from " + XI_ConvertString("Colony" + npchar.city + "Gen") + ", we are looking for an escaped convict.",
					"Hello, I'm the head of this patrol. We are looking for an escaped slave from " + XI_ConvertString("Colony" + npchar.city + "Gen") + ".",
					"Greetings, " + GetAddress_Form(NPChar) + ". My unit is patrolling the area near " + XI_ConvertString("Colony" + npchar.city + "Gen") + ".");
				Link.l1 = LinkRandPhrase("That's fine. How can I help you?",
				"Very good. Can I help you, " + GetAddress_FormToNPC(NPChar) + "?",
				"Great. What can I personally do for you?");
				Link.l1.go = "Node_2";
			}
		break;

		case "CheckPeg":
		switch (rand(1))
		{
			case 0:
				dialog.text = RandPhraseSimple("Ah, I see... It's okay, you can go, " + GetAddress_Form(pchar) + ".", "I'm a little tired on patrol... It's okay, "+GetAddress_Form(NPChar)+", I'm sorry.");
				link.l1 = "That's it!";
				link.l1.go = "exit_noFight";
				if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
				{
					AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
					pchar.questTemp.stels.landSolder = GetDataDay();
				}
				break;
			case 1:
				dialog.text = RandPhraseSimple("You don't mess with my head! Hand over your weapons!", "Well, definitely a spy... Surrender immediately!");
				link.l1 = RandPhraseSimple("As if not so!", "After the rain, on Thursday...");
				link.l1.go = "exit_fight";
				if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
				{
					AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
					pchar.questTemp.stels.landSolder = GetDataDay();
				}
				break;
		}
		break;

		case "Node_2":
			dialog.text = RandPhraseSimple("Have you seen anything suspicious in the area?", "Have you met anyone suspicious, " + GetAddress_Form(NPChar) + "?");
			link.l1 = RandPhraseSimple("No, nothing like that.", "No, Officer, everything is calm.");
			link.l1.go = "Node_3";

			/* Nathaniel (09.03.2021): возможность спровоцировать драку с патрулём ------------- */
			link.l2 = "Yes, Officer, I have a very important matter for you... Come on, defend yourself, soldiers!";
			link.l2.go = "exit_fight";
			/* --------------------------------------------------------------------------------- */
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("Well, I dare not detain you. Goodbye, " + GetAddress_Form(NPChar) + ".",
				"I see. In that case, goodbye.");
			Link.l1 = "Good luck to you.";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("Don't distract us from our duty.",
				"I ask you not to disturb us!",
				"Oh, it's you again... Go your own way, don't bother us.");
			Link.l1 = "Good.";
			Link.l1.go = "Exit";
		break;

		// генератор "A reason to hurry"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "Hmm... I haven't seen you before. Who are you?";
					link.l1 = "I'm the one who are you waiting for...";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "I am captain " + GetFullName(pchar) + ". I want to ask why you were in such a hurry to get here, you almost left your pants in a brothel...";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "I am captain " + GetFullName(pchar) + ". I'm walking here, breathing the sea breeze...";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "Finally you're here. I thought I couldn't wait... Is this guy with you?";
					link.l1 = "What guy?";
					link.l1.go = "Reason_To_Fast_Hunter";
				}
		break;

		case "Reason_To_Fast_Hunter":
			DialogExit();
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;

		case "Reason_To_Fast_11":
			dialog.text = "You don't look like someone I would trust that " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			if(!CheckCharacterItem(pchar, "mapQuest"))
			{
				link.l1 = "Okay, I'll tell him so.";
				link.l1.go = "Reason_To_Fast_12";
			}
			link.l2 = "And who is this one?" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "?";
			link.l2.go = "Reason_To_Fast_13";
		break;

		case "Reason_To_Fast_21":
			dialog.text = "Curiosity is certainly not a vice, but sometimes it shortens life considerably...";
			link.l1 = "Well, well!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";
		break;

		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "The tide is coming in. You would leave the bay, here the water rises to the palm thickets.";
			link.l1 = "Nothing, I swim well.";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;

		case "Reason_To_Fast_12":
			jewelType = sti(pchar.questTemp.ReasonToFast.p4);
			pchar.questTemp.ReasonToFast.item = "jewelry" + jewelType;
			sItem = "jewelry" + jewelType;
			switch (jewelType)
			{
				case 1:
					sItemName = "sapphires";
				break;
				case 2:
					sItemName = "diamonds";
				break;
				case 3:
					sItemName = "Rubinov";
				break;
				case 4:
					sItemName = "emeralds";
				break;
			}
			pchar.questTemp.ReasonToFast.jewType = sItemName;
			dialog.text = "Okay, okay. Are promised 30 " + sItemName + " with you?";
			link.l1 = GetName(NAMETYPE_MAIN , pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " said that there was little time to collect so many pebbles. He told me to offer money.";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "Get it.";
				link.l2.go = "Reason_To_Fast_15";
			}
		break;

		case "Reason_To_Fast_13":
			dialog.text = "Heh! You'll find out in the next world!";
			link.l1 = "What self-confidence...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";
		break;

		case "Reason_To_Fast_14":
			dialog.text = "Fine, then that's it " + sti(pchar.questTemp.ReasonToFast.p5) + "gold, as agreed.";
			link.l1 = "Aren't you asking a lot?";
			link.l1.go = "Reason_To_Fast_16";
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "Get it.";
				link.l2.go = "Reason_To_Fast_17";
			}
			link.l3 = "But I don't have that amount on me!";
			link.l3.go = "Reason_To_Fast_18";
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;

		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30);
			dialog.text = "Everything is according to the agreement. Here you go. This map was taken away from that hanged pirate, about whom he asked "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			link.l1 = "It's done!";
			link.l1.go = "Reason_To_Fast_15_1";
		break;

		case "Reason_To_Fast_15_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//fix
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			DialogExit();
			AddQuestRecord("ReasonToFast", "10");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			pchar.questTemp.ReasonToFast = "PatrolSuccess_2";
			GiveItem2Character(pchar, "mapQuest");
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Reason_To_Fast_16":
			dialog.text = "We are talking about the sum with " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_ABL) + " agreed in advance... I don't like it... Kill "+ GetSexPhrase("him", "her") +" guys!";
			link.l1 = "Well, try it!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";
		break;

		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
			if(CheckAttribute(pchar, "questTemp.ReasonToFast.chain")) DeleteAttribute(pchar, "questTemp.ReasonToFast.chain");
			if(CheckAttribute(pchar, "questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar, "questTemp.ReasonToFast.ShipName");
			if(CheckAttribute(pchar, "questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar, "questTemp.ReasonToFast.TypeName");
			switch (sti(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // корабль с товаром
					sTemp1 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = "Great! Now about the case. We intercepted that '" + GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName) +" '" + sTemp1 + "' with cargo of " + GetGoodsNameAlt(iShipGoods) + ", the entire crew is already in the casemates, and the 'goods' are still on board. The transport team is recruited from the port drunks, and it is unlikely to get to the port until tomorrow. Do with them as you see fit.";
					link.l1 = "Good. I'll tell you everything like that " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A0";
					pchar.questTemp.ReasonToFast.ShipName = sTemp1;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					AddQuestRecord("ReasonToFast", "11");
					AddQuestUserData("ReasonToFast", "sShipType", pchar.questTemp.ReasonToFast.ShipTypeName);
					AddQuestUserData("ReasonToFast", "sShipName", sTemp1);
					AddQuestUserData("ReasonToFast", "sGoodsName", GetGoodsNameAlt(iShipGoods));
					ReasonToFast_GenerateVictimShip(iShipType, iShipGoods);
				break;

				case 1: // сокровища губернатора
					switch(rand(3))
					{
						case 0:
							sTemp1 = "Your daughter's dowry";
						break;
						case 1:
							sTemp1 = "Gifts for the Viceroy";
						break;
						case 2:
							sTemp1 = "Gifts for your anniversary";
						break;
						case 3:
							sTemp1 = "Their 'retirement'";
						break;
					}
					switch(rand(3))
					{
						case 0:
							sTemp2 = "The cheat";
						break;
						case 1:
							sTemp2 = "Minx";
						break;
						case 2:
							sTemp2 = "The Prankster";
						break;
						case 3:
							sTemp2 = "Naughty girl";
						break;
					}
					pchar.questTemp.ReasonToFast.password = sTemp2;
					sTemp2 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = "Great!  The governor keeps " + sTemp1 + " in his boudoir. There will be a courier ship for transportation any day now, but you will make it in time. The footman is 'our' man. Password: '"+ pchar.questTemp.ReasonToFast.password +"', answer: '"+ sTemp2 +"'.";
					link.l1 = "Good. I'll tell you everything like that " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A1";
					AddQuestRecord("ReasonToFast", "12");
					pchar.questTemp.ReasonToFast.ShipName = sTemp2;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером

					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1 = "Timer";
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.function = "ReasonToFast_ClearLakey";
				break;
			}
		break;

		case "Reason_To_Fast_18":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = "Are you trying to trick me?! The dog!";
				link.l1 = "Shut your mouth!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";
			}
			else
			{
				dialog.text = "You! Drank! My! Money!... Argh!";
				link.l1 = "Damn it!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";
			}
		break;

		case "Reason_To_Fast_GoodBye_0":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//fix
			LAi_SetPlayerType(pchar);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "Reason_To_Fast_GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			pchar.quest.RemovePatrolFromShore.win_condition.l1          = "ExitFromLocation";
			pchar.quest.RemovePatrolFromShore.win_condition.l1.location = pchar.location;
            pchar.quest.RemovePatrolFromShore.function    				= "ReasonToFast_DeletePatrolFromShore";
			DialogExit();
		break;

		case "Reason_To_Fast_GoodBye":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "You would have left the bay, the tide has already started...";
			link.l1 = "Yes, yes, I'm already leaving.";
			link.l1.go = "Exit";
		break;

		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY);

			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять

			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				sld = CharacterFromID("ReasonToFast_Hunter");
				if(sld != -1)
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, sGroup);
				}
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors");
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Reason_To_Fast_AfterHunter1":
			dialog.text = "We agreed that the messenger should be alone!";
			link.l1 = "The problem is out. See, the messenger got lost? I was sent to replace him.";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "And I came"+ GetSexPhrase("ate alone", "la alone") +"just not for what you're thinking.";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;

		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "So you tracked me down... Well, then forgive me.";
			link.l1 = "Argh...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";
		break;

		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "Ah, bastard! And I almost got caught!.. Guards! Take "+ GetSexPhrase("him", "her") +"...";
			link.l1 = "Argh...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";
		break;
		// генератор "A reason to hurry"
	}
}
