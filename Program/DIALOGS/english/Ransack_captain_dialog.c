// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	ref rColony;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear() + "I am your prisoner, " + GetAddress_Form(NPChar) + ". But I must say that " + NationNameNominative(sti(NPChar.nation)) + " never redeems his own - every man for himself.";
				link.l1 = "Oh... The only way to make money off you is to turn you in as a criminal at some port for ransom.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Listen, you're not a bad fighter, but I just need desperate thugs. Would you like to serve as an officer for me?";
					link.l2.go = "free_to_officer";
					if (pchar.sex == "Skeleton")
					{
						DeleteAttribute(link, "l2");
					}
				}
			}
			else
			{
				dialog.text = RandSwear() + "I am your prisoner, " + GetAddress_Form(NPChar) + ". " + NationNameNominative(sti(NPChar.nation)) + "he will pay a good sum for my freedom.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Listen, you are a good seaman, but I need experienced sailors. Would you like to serve under me?";
					link.l1.go = "free_to_officer_trader";
					if (pchar.sex == "Skeleton")
					{
						DeleteAttribute(link, "l1");
					}
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none" && FindColony(attrLoc) != -1)
			{
				rColony = GetColonyByIndex(FindColony(attrLoc));
                link.l3 = "We are now near the city " + GetConvertStr(attrLoc +" Town", "LocLables.txt") + ". I could drop you off here.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Go to the boatswain, tell him to allocate a locker on the forecastle. You will go ashore in the nearest bay.";
			    link.l3.go = "free_withoutFee_2";
			}
			link.l4 = "I think you will make a great slave - strong and obedient.";
			link.l4.go = "Slave_1";
			link.l5 = "You ignored the order to drift and resisted, for this you will be executed. The boatswain has already received the relevant orders.";
			link.l5.go = "PunishmentAction";
			link.l99 = "I know.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time";
		break;

		case "second time":
			if(CheckAttribute(NPChar, "Hold_GenQuest") && !CheckAttribute(pchar, "GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("Captain, would you consider it impertinent, would I be allowed to offer a rather advantageous option for my release?",
							"I understand that it is inappropriate to bargain in my position, but would you agree to listen to a business proposal, so to speak?");
						link.l1 = "Hmm, well, state your proposal.";
						link.l1.go = "free_tip_off";
					break;

					case 1:
						dialog.text = "Captain, would you let me go. What do you need me for now? Well, sell me to the slavers - maybe you'll get a handful of piastres, but you'll earn a reputation as a cruel man.";
						link.l1 = "If I let go, I won't earn anything at all...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none")
						{
							link.l2 = "You ignored the order to drift and resisted, for which you will be executed. The boatswain has already received the relevant orders.";
							link.l2.go = "PunishmentAction";
						}
						else
						{
							link.l2 = "You insist on being released so much that I am ready to meet you halfway. You are free to leave the ship.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Don't tempt my patience. You're already lucky to be alive.",
							"I have other plans for you.", "I think I'll need you again.");
						link.l3.go = "exit";
					break;

					case 2: // "ransom"
						dialog.text = "Captain, the uncertainty is most depressing. May I ask what your plans are for me?";
						link.l1 = "Do you have any specific suggestions?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple(RandPhraseSimple("I haven't decided what to do with you yet.", "You'll find out when the time comes."),
							RandPhraseSimple("What are the plans? A ball on the neck and aha... I'm kidding, I'm kidding.", "You are my prisoner, and I have the right to do with you as I see fit, without taking into account either your opinion or desire."));
						link.l2.go = "exit";
					break;
				}
				NextDiag.TempNode = "second time";
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Captain, would you let me go in a good, healthy way. What can you charge me for? After all, I didn't go into robbery from a good life-I'm not trained in anything else. I thought I'd save some money for my old age, but it turned out that way.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Listen, you're not a bad fighter, but I just need desperate thugs. Would you like to serve as an officer for me?";
						link.l2.go = "free_to_officer";
						if (pchar.sex == "Skeleton")
						{
							DeleteAttribute(link, "l2");
						}
					}
					link.l3 = LinkRandPhrase("Don't expect mercy. There are a lot of you like this prowling the sea, now there will be one less.",
						"What did you cry, 'thunderstorm of the seas'? Sit down, if you got caught.",
						"No matter how the string twists, there are no loops to avoid. I will turn you over to the authorities so that others will not be offended.");
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Captain, I pray by all the saints - let me go in peace. Family at home, small children, what is it like for them without a breadwinner? They've probably already buried it...";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Listen, you are a good seaman, but I need experienced sailors. Would you like to serve under me?";
							link.l2.go = "free_to_officer_trader";
							if (pchar.sex == "Skeleton")
							{
								DeleteAttribute(link, "l2");
							}
						}
						link.l3 = LinkRandPhrase("I have other plans for you.", "I think that you will still be useful to me.", "Captain, I lost my battle and I want to ask for leniency. As a generous person, let go for the glory of mercy. All I can't avoid is punishment - I'll be demoted for surrendering the ship. So at least don't deprive me of my freedom...");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Captain, I appeal to your generosity! I understand that there is no point in demanding that you treat me like a prisoner of war, so I ask you to release me. I give you my word as an officer that I will avoid meeting you in the future.",
							"Don't tempt my patience. You're already lucky to be alive.");
						link.l2 = LinkRandPhrase("I have other plans for you.",
							RandPhraseSimple("I think I'll need you again.", "You are my prisoner, and I have the right to do with you as I see fit, without taking into account either your opinion or desire."),
							RandPhraseSimple("You are captain of a military vessel and you knew what you were doing. There's nothing to be a saint about now.",
							"Listen, you're not a bad fighter, but I just need desperate thugs. Would you like to serve as an officer for me?"));
						link.l2.go = "exit";
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "We are now near the city ";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none" && FindColony(attrLoc) != -1)
				{
					rColony = GetColonyByIndex(FindColony(attrLoc));
					link.l4 = ". I " + GetConvertStr(attrLoc +" Town", "LocLables.txt") + "could"+ GetSexPhrase("could", "would like to drop you off here.") +"Go to the boatswain, tell him to allocate a locker on the forecastle. You will go ashore in the nearest bay.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "The hell with you! Go to the boatswain, he will receive the appropriate orders, you will be dropped off in the nearest bay. And remember, our next meeting will be our last.";
						link.l4.go = "free_withoutFee_4";
					}
					else
					{
						link.l4 = "You ignored the order to drift and resisted, for this you will be executed. The boatswain has already received the relevant orders.";
						link.l4.go = "free_withoutFee_4";
					}
				}
				link.l5 = "The criminal? You're probably joking, ";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time";
			}
		break;

		case "offender":
			dialog.text = "!" + GetAddress_Form(NPChar) + "!";
			link.l1 = "What kind of jokes are there. A pirate is a pirate.";
			link.l1.go = "exit";
		break;

		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "To serve you? No, it's better to feed the sharks!";
				link.l1 = "Hold your tongue, or I'll do it.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Officer, " + GetAddress_Form(NPChar) + "? I will not refuse. I know the business, and how long you can drag an anchor and wait for a meeting with a loop.";
				link.l1 = "That's settled! Go take the cases.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Take your time, I've changed my mind. Having a former pirate as an officer is more expensive for yourself.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("This is certainly a flattering offer, but I have to refuse... for ideological reasons, so to speak.",
					"Alas, after what you've done to my comrades, it's hardly possible...",
					"No, Captain, after all this horror, I can't do it anymore. I made a vow that if the Blessed Virgin hears my prayers and grants me freedom, then I will not set foot in the sea anymore.");
				link.l1 = "Well, as you know. I won't beg.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Why not serve? I didn't make a captain, I ruined my business, what awaits me on the shore, except bills of exchange and debt receipts? A sailor is a sailor.";
				link.l1 = "That's settled! Go to the boatswain - let him put you on allowance. After that, I will determine your position.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Take your time, I've changed my mind. Still, the ship is not a passing yard.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) >= 40)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трём накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";

			if(CheckAttribute(NPChar, "Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");

			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;

		case "Slave_1":
			dialog.text = "But " + GetAddress_Form(NPChar) + "You can't do that! I surrendered in battle at your mercy.";
            link.l1 = "Set aside conversations! Shackle him.";
			link.l1.go = "Slave_2";
			link.l99 = "Well, okay, I'll think about it, sit down for now...";
			link.l99.go = "exit";
		break;

		case "Slave_2":
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -2);
            if (rand(5) == 1)
            {
    			dialog.text = "No way!.. I'd rather kill myself than become a slave!";
                link.l1 = "Stop! I'm ordering you!.. Boatswain! clear the hold...";
    			link.l1.go = "free_in_sea_4";
			}
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Oh, you executioner! Brothers, two deaths will not happen, and one will not pass!";
                        link.l1 = "But you shouldn't have done that. I stop attempts at rebellion with my own hand and without delay...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "No! Death in battle is better!";
						link.l1 = "As you wish...";
						link.l1.go = "free_in_sea_battle_1";
					}
    			}
    			else
    			{
					dialog.text = "Okay, I agree. I just don't have any other choice...";
                    link.l1 = "That's nice. It's better to be a living slave than a dead hero.";
        			link.l1.go = "Slave_3";
    			}
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterReputation(pchar, -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "Oh, " + GetAddress_Form(NPChar) + "Are you kind enough to let me go without ransom?";
            link.l1 = "Yes, I'm letting go. You are free, " + GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Hmm... yes, you're right! I'll think about it...";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Thank you, " + GetFullName(PChar) + "! I will pray for you.";
            link.l1 = "Okay, go, before I change my mind.";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;

		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterReputation(pchar, 2);
        	DialogExit();
        break;

		case "free_withoutFee_4":
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("Here, thanks, Captain. I will never forget your kindness. I'll give up this trade and get a job repairing longboats. That's what I can do...",
						"Thank you, Captain. And my own mother couldn't have comforted me like that. Here's a cross for you - I'll give up this thankless task, I'll become a fisherman.");
					link.l1 = "I would like to believe...";
				break;
				case "trade":
					dialog.text = "I don't even know how to thank you, Captain. I did not expect deliverance. I'll tell everyone about your generosity. And I swear, I'll light a candle for you-just let me get to the church!";
					link.l1 = "Goodbye, and don't try to resist in the future. Your first shot is a death sentence for both you and the team.";
				break;
				case "war":
					dialog.text = "Thank you, Captain. I will pray for you.";
					link.l1 = "Keep in mind for the future that next time I may be less supportive.";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;

		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref, "prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;

		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "But " + GetAddress_Form(NPChar) + "You can't do that! I surrendered in battle at your mercy.";
			link.l1 = "After the people you just betrayed died... Boatswain! Get started.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Well, okay, I'll think about it, sit down for now...";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -2);
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Oh, you executioner! Brothers, two deaths will not happen, and one will not pass!";
                    link.l1 = "But you shouldn't have done that. I stop attempts at rebellion with my own hand and without delay...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "No! Death in battle is better!";
					link.l1 = "As you wish...";
					link.l1.go = "free_in_sea_battle_1";
				}
    		}
			else
    		{
				dialog.text = "At least let me pray before I die...";
                link.l1 = "Pray...";
        		link.l1.go = "PunishmentAction2";
    		}
		break;

		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;

		case "free_tip_off":
			dialog.text = "I have some information, given the nature of your business, it may be of interest to you. But I would like to have guarantees that I will get freedom in exchange for information.";
			link.l1 = "How can I guarantee you anything if I don't know what it's about? Surely your information is not worth a damn.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "What guarantees do you expect, other than my word of honor?";
			link.l2.go = "free_tip_off_1";
		break;

		case "free_tip_off_0":
			ChangeCharacterReputation(pchar, -2);
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;

		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "I wanted to charter my ship too, but I was too greedy with the payment - I refused.";
				break;
				case "war":
					sTmp = "I had to accompany him several times as a convoy captain.";
				break;
				case "pirate":
					sTmp = "I was thinking of gutting him once, but I didn't get the chance.";
				break;
			}
			dialog.text = "Good. That's enough. Now to the point - in " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + " there lives a rich merchant " + NPChar.Hold_GenQuest.Name + ". " +
				"He made his considerable fortune by being on the ship '" + NPChar.Hold_GenQuest.ShipName + "' carries " + GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name + "Acc")) + " route " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.FromCity) + " - " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.ToCity) +". " +
				"When a shipment is too big for his hold, he hires an escort. " + sTmp + "I am sure that this information is worth much more to you than the freedom of one prisoner.";
			link.l1 = "I don't think they can be useful to me. I will not hunt peaceful merchants.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "I don't know if your information will be useful to me, but according to the agreement, you are free. The boatswain will place you with the crew, and put you ashore at the nearest port.";
			link.l2.go = "free_tip_off_2";
		break;

		case "free_tip_off_2":
			dialog.text = "Thank you, Captain! I didn't doubt your honesty for a second!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("I would like to think the same about you", "Unfortunately, I can't say the same about you."),
				RandPhraseSimple("Keep in mind for the future that next time I may be less supportive.", "Go and don't get caught by me anymore. Another time I won't be so gullible."));
			link.l1.go = "free_tip_off_3";
		break;

		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity;
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;

			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc")));
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);

			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);

            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();
		break;

		case "free_buyout":
			dialog.text = "That's right, there is an offer. In " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + " my good friend lives, " + NPChar.Hold_GenQuest.Name + " name, we started the business together. " +
				"If we are in those places, find him. I am sure he will not be stingy, he will give a good ransom. And I'll pay him off in my own way... And he owes me a favor.";
			link.l1 = "Comrade, you say? Well, let's visit your friend...";
			link.l1.go = "free_buyout1";
			link.l2 = "I'm unlikely to look for your comrade if the first governor can give you a ransom.";
			link.l2.go = "free_tip_off_0";
		break;

		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);

			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;

			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc"));
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "Uh, don't tell me... I know one person who has a huge treasure, but because of his cowardice he does not dare to use it.";
			link.l1 = "What are you talking about?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Leave your stories, now is the time for you to think about your soul.";
			link.l2.go = "free_tip_off_0";
		break;

		case "free_by_hoard1":
			dialog.text = "I will tell you this story, which leads straight to untold riches... Just give me your word that you'll let me go at the first cove.";
			link.l1 = "I will decide what and when to do with you. It will not depend on your inventions.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Well, tell your story. I give you my word...";
			link.l2.go = "free_by_hoard2";
		break;

		case "free_by_hoard2":
			dialog.text = "I believe a noble man! If you've already given your word, then oh-go-go... Let the devils dance around, but " +GetSexPhrase("he", "she")+ " will keep this word! Isn't it true, Captain " + GetFullName(pchar) + "?";
			link.l1 = "Either tell me, or I'll let you go right now... just overboard.";
			link.l1.go = "free_by_hoard4";
		break;

		case "free_by_hoard4":
			dialog.text = "Hehe, good joke, hehe... And the story is as follows. In " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + " lives man "+
				"by name " + NPChar.Hold_GenQuest.Name + ", in his youth he was a desperate guy, he did so much that it's scary to remember... " +
				"So, once over a bottle of rum, this friend told me that, while working in a gang " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + ", he happened to witness how the pirates buried the treasure." +
				"\nFive of his friends " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_NOM) + " killed right near this trerasure... Then rumors spread that " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + " was caught and hanged, and " + NPChar.Hold_GenQuest.Name + " since then he's been retired, " +
				" settled down, got a family. But he remembered the place of the treasure well, even scribbled a map. He offered to go treasure hunting with him. He says he is afraid - that treasure was abundantly watered with blood, and he is a superstitious man. I must admit, I didn't dare either. " +
				"He was ready to sell the map, but why would I need it - I'm not going to take on this case all by myself... That's my story... I think this map would be just right for you as a brave man... he'll give it away cheap.";
			link.l1 = "And you really hope that I will believe this nonsense? The agreement is terminated due to the inconsistency of your story.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Hmm... It's an interesting story, although it's hard to believe. Well, since you gave the word, go tell the boatswain, let him allocate you a locker on the forecastle. You will go ashore at the first bay.";
			link.l2.go = "free_by_hoard5";
		break;

		case "free_by_hoard5":
			dialog.text = "Thank you, Captain! That's what the word of "+ GetSexPhrase("gentleman", "lady") + " means!";
			link.l1 = "Go and don't get caught by me anymore. Another time I won't be so kind.";
			link.l1.go = "free_by_hoard6";
		break;

		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;

			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc"));
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));

            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();
		break;

		case "free_in_sea":
			dialog.text = "But, " + GetAddress_Form(NPChar) + ", we are in the open sea! This is equivalent to my execution!!!";
			link.l1 = "But that's exactly what you wanted - so goodbye. The boatswain will see to the execution of my orders.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Okay, I'll think about it...";
			link.l2.go = "exit";
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	}
}
