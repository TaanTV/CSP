// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	makearef(NextDiag, NPChar.Dialog);

	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;

	bool bGoldMine = false;
	bool bSilverMine = false;
	bool bIronMine = false;

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

	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, Captain, half the garrison is chasing you here. Now is clearly not the time to join your team!", "Do you propose to break into the ship with a fight? No, another time, Cap...");
				link.l1 = RandPhraseSimple("Well, as you know...", "Yes, I didn't"+ GetSexPhrase("I was going to", "I was going to") +"hire you.");
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Do you need an officer, Captain?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "An officer? What are you good for?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "No, I have a complete set.";
			Link.l2.go = "Exit";
		break;

		case "CitizenNotBlade":
			dialog.text = "Charles, what nonsense! Put away your weapon before you cause trouble!";
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Don't worry, I'm already removing...");
			link.l1.go = "exit";
		break;

		case "hired":
			Diag.TempNode = "Hired";
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 1 && LAi_grp_playeralarm == 0 && NPChar.id == "SharleMary" && NPChar.name == "Mary")
			{
				dialog.Text = ""+pchar.name+"! I need to talk to you, yes! Seriously!";
				Link.l1 = "What's wrong, Mary?";
				Link.l1.go = "Mary_brothel";
				break;
			}
			dialog.text = LinkRandPhrase("I'm all ears, my love!", "Yes, my joy, I'll do whatever you say!", "Do you have a task for me, my love?");
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "Mary, I have some orders for you.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			if (NPChar.id == "SharleMary" && NPChar.name == "Mary")
			{
				Link.l2 = LinkRandPhrase (LinkRandPhrase("Honey, ", "Darling, ", "Mary, ") + "I have an instruction for you.", LinkRandPhrase("Honey, ", "Darling, ", "Mary, ") + "I need to consult with you.", LinkRandPhrase("Honey, ", "Darling, ", "Mary, ") + "we need to do something.");
	            Link.l2.go = "stay_follow";
			}	
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Mary, give me a full report on the ship.";
			    Link.l8.go = "QMASTER_1";

			    Link.l11 = "I want you to buy goods while staying at the colony.";
			    Link.l11.go = "QMASTER_2";
			}

			for(iTemp=1; iTemp<=3; iTemp++) // Нужно, чтоб была свободная группа
			{
				attr = "Companion" + iTemp;
				if (CheckAttribute(PChar, "CompanionTravel."+(attr)+".ID"))
				{
					if (PChar.CompanionTravel.(attr).ID == NPChar.ID)
					{
						Link.l4 = "Mary, go back to the squadron.";
						Link.l4.go = "CompanionTravel_ToSquadron";
					}
				}
			}
			//Предлагаем сэкс Мэри Каспер (для Шарля)
			if (PChar.location == Get_My_Cabin() && CheckAttribute(npchar, "quest.daily_sex") && npchar.id == "SharleMary")
			{
				DeleteAttribute(link, "l3");
			}
			if (PChar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex") && npchar.id == "SharleMary")
			{
				Link.l3 = RandPhraseSimple("Honey, I want to be alone with you right now. Do you mind?", "Honey, how about a little... to be alone?");
				Link.l3.go = "Mary_cabin_sex";
			}
			if (!CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				if (PChar.location == "SentJons_tavern" || PChar.location == "PortRoyal_tavern" || PChar.location == "Charles_tavern" || PChar.location == "Bridgetown_tavern" || 
					PChar.location == "PortSpein_tavern" || PChar.location == "Villemstad_tavern" || PChar.location == "Marigo_tavern" || PChar.location == "FortOrange_tavern" || 
					PChar.location == "Nassau_tavern" || PChar.location == "FortFrance_tavern" || PChar.location == "BasTer_tavern" || PChar.location == "LeFransua_tavern" || 
					PChar.location == "Tortuga_tavern" || PChar.location == "Caracas_tavern" || PChar.location == "Cumana_tavern" || PChar.location == "Cartahena_tavern" || 
					PChar.location == "Maracaibo_tavern" || PChar.location == "PortoBello_tavern" || PChar.location == "SantaCatalina_tavern" || PChar.location == "Beliz_tavern" || 
					PChar.location == "SantoDomingo_tavern" || PChar.location == "SanJuan_tavern" || PChar.location == "Santiago_tavern" || PChar.location == "Havana_tavern" || 
					PChar.location == "PuertoPrincipe_tavern" || PChar.location == "PortPax_tavern" || PChar.location == "LaVega_tavern" || PChar.location == "Pirates_tavern" || 
					PChar.location == "Panama_tavern" || PChar.location == "DesMoines_tavern")
					{
						Link.l3 = RandPhraseSimple("Honey, why don't we rent a room and stay together?", "Darling, I really want to be alone with you... maybe we can rent a room and forget about everything for a couple of hours?");
						Link.l3.go = "Mary_room_sex";
					}
			}
			if (!CheckAttribute(pchar, "questTemp.FUNY_SHIP_FIND") && NPChar.sex == "woman" && GetCharacterItem(PChar, "mineral4") >= 25)
            {
                Link.l4 = "Look what an interesting collection I have gathered!";
				Link.l4.go = "FUNY_SHIP_1";
            }

            // по тёк локации определим можно ли тут приказать  -->
            if (IsEntity(loadedLocation))
            {
                if (CheckAttribute(loadedLocation, "fastreload"))
                {
                    iTemp = FindColony(loadedLocation.fastreload);
                    if (iTemp != -1)
                    {
                        sld = GetColonyByIndex(iTemp);
                        if (sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
                        {
							if(Locations[FindLocation(PChar.location)].islandId != "Caiman" && !CheckAttribute(NPChar, "HPminusDaysNeedtoRestore"))
							{
								NPChar.ColonyIdx = iTemp;
								Link.l7 = "I'm appointing you as the governor of this city!";
								Link.l7.go = "Gover_Hire";
							}
                        }
                    }
                }
            }
            if(PChar.ColonyBuilding.Stage != "0" && PChar.ColonyBuilding.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman" && !CheckAttribute(NPChar, "HPminusDaysNeedtoRestore"))
					{
						Link.l8 = "I want to appoint you as the governor of the colony " + PChar.ColonyBuilding.ColonyName + ", which we built on the island of Cayman.";
						Link.l8.go = "ColonyBuilding_Hovernor_1";
					}
				}
			}

			if(PChar.ColonyBuilding.Stage == "3" && PChar.Colony.Guardians.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman" && !CheckAttribute(NPChar, "HPminusDaysNeedtoRestore"))
					{
						Link.l9 = "I want to appoint you as the manager of the security base that we have built to strengthen the defense of our colony '" + PChar.ColonyBuilding.ColonyName + "'.";
						Link.l9.go = "ColonyGuarding_Hovernor_1";
					}
				}
			}

			if(bGoldMine || bSilverMine || bIronMine)
			{
				if(PChar.Mines.Commander == "")
				{
					if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
					{
						if(Locations[FindLocation(PChar.location)].islandId == "Caiman" && !CheckAttribute(NPChar, "HPminusDaysNeedtoRestore"))
						{
							Link.l10 = "I want to appoint you as the manager of the mines that are located on this island.";
							Link.l10.go = "MinesCommander_Hire";
						}
					}
				}
			}

			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.Plantation.Commander == "")
				{
					if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
					{
						if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
						{
							Link.l11 = "I want to appoint you as the manager of the plantation, which is located near the colony " + PChar.ColonyBuilding.ColonyName + " and belongs to her.";
							Link.l11.go = "PlantationCommander_Hire";
						}
					}
				}
			}
            Link.l12 = "Nothing. At ease.";
            Link.l12.go = "Exit";
			if (NPChar.id == "SharleMary" && NPChar.name == "Mary")
			{
				Link.l12 = LinkRandPhrase ("I can't take my eyes off you, " + LinkRandPhrase("my red talisman.", "my beautiful lioness.", "my beauty."), "I just wanted to admire you, " + LinkRandPhrase("my red talisman.", "my beautiful lioness.", "my beauty."), "I like you, " + LinkRandPhrase("my red-haired talisman.", "my beautiful lioness.", "my beauty."));
	            Link.l12.go = "Exit";
			}
        break;

		case "FUNY_SHIP_1":
		    dialog.text = "Oh horror! Charles, get that away from me, it's such an unbearable stench... Do you believe in all this nonsense of the old legend about getting eternal youth?";
   			Link.l1 = "No, of course, I'm sorry. I'm going to throw this whole stinking mass overboard.";
            Link.l1.go = "exit";
            Link.l2 = "Yes, I do! Moreover, I'll check it out. Come on, come closer, dear msya!";
            Link.l2.go = "FUNY_SHIP_2";
        break;

        case "FUNY_SHIP_2":
		    dialog.text = "What a stink! Ugh... Although it works, I feel stronger and even, uh, sexier.";
   			Link.l1 = "Here! And you were afraid, even your skirt wasn't wrinkled. Wash your hands only now.";
            Link.l1.go = "FUNY_SHIP_3";
        break;

        case "FUNY_SHIP_3":
            PChar.questTemp.FUNY_SHIP_FIND = false;
            DialogExit();
			NextDiag.CurrentNode = "Hired";

			TakeNItems(pchar, "mineral4", -25);
			AddSPECIALValue(Npchar, SPECIAL_S, 1);
			AddSPECIALValue(Npchar, SPECIAL_P, 1);
			AddSPECIALValue(Npchar, SPECIAL_E, 1);
			AddSPECIALValue(Npchar, SPECIAL_C, 1);
			AddSPECIALValue(Npchar, SPECIAL_I, 1);
			AddSPECIALValue(Npchar, SPECIAL_A, 1);
			AddSPECIALValue(Npchar, SPECIAL_L, 1);
        break;

		case "MaryCabinHelp_1":
			dialog.text = "Charles, I can't sit idly by! I'll be worried... and to be bored...";
            Link.l1 = "My sun, you are so dear to me that I cannot put you in danger!";
            Link.l1.go = "exit";
			pchar.MaryCabinHelp = !sti(pchar.MaryCabinHelp);
		break;
		
		case "MaryCabinHelp_2":
			dialog.text = "I'll go to the ends of the earth with you, yes!";
            Link.l1 = "You're my darling!";
            Link.l1.go = "exit";
			pchar.MaryCabinHelp = !sti(pchar.MaryCabinHelp);
		break;

		case "TransferGoodsEnable":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;

		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();

			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;

		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.CanTakeMushket = true;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();
		break;

        case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Charles, but we don't have a ship!";
				Link.l1 = "Thanks for reminding me...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
            dialog.text = "The ship is beautiful, Charles, yes! The hole below the waterline was patched up after the last battle, the sails were dried. What did you want? Don't look at me like that, I've never studied to be a treasurer.";
            Link.l1 = "I'm sorry, Mary, I really didn't think of that.";
            Link.l1.go = "Exit";
            Diag.TempNode = "Hired";
        break;
		
		case "QMASTER_2":
            dialog.text = "Charles, so I don't need to buy anything. I have clothes, I have a blade. But thanks for the concern, I'm very pleased, yes!";
            Link.l1 = "That's what I meant... Okay, honey, forget it, it's okay.";
            Link.l1.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "What are the orders?";
			if (NPChar.id == "SharleMary" && NPChar.name == "Mary")
				{
				dialog.text = LinkRandPhrase("And what are you up to?", "Do you want to kill someone? I'm with you, yes!", "And what are you up to?");
				}
            Link.l1 = "Stay here!";
            Link.l1.go = "Boal_Stay";
			if (NPChar.id == "SharleMary" && NPChar.name == "Mary")
				{
				Link.l1 = "Mary, wait for me here, don't go anywhere!";
				Link.l1.go = "Boal_Stay";
				}
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
			if (NPChar.id == "SharleMary" && NPChar.name == "Mary")
				{
				Link.l2 = "Mary, we have to go!";
				Link.l2.go = "Boal_Follow";
				}
            // boal 05.09.03 offecer need to go to abordage <--

			if (findsubstr(npchar.model, "PGG" , 0) != -1 && !CheckAttribute(npchar, "CanTakeMushket"))
			{
				Link.l3 = "Can I trust you with a musket?";
				Link.l3.go = "CheckMushket";
			}
			if (findsubstr(npchar.model.animation, "mushketer" , 0) != -1)
			{
				Link.l3 = "I want you to hold at a certain distance from the target.";
				Link.l3.go = "TargetDistance";
			}
			if (!CheckAttribute(npchar, "AboardRestriction"))
			{
				Link.l4 = "I ask you not to participate in the boarding. Take care of yourself.";
				Link.l4.go = "AboardRestriction";
			}
			else
			{
				Link.l4 = "I've changed my mind, you can participate in the boarding.";
				Link.l4.go = "AboardAllowed";
			}
			if (NPChar.id == "SharleMary" && NPChar.name == "Mary")
			{
				if(Pchar.MaryCabinHelp == true)
				{
					Link.l14 = "During the fight in the cabin, I will fight alone.";
					Link.l14.go = "MaryCabinHelp_1";
				}
				else
				{
					Link.l14 = "During the fight in the cabin, we will fight together side by side.";
					Link.l14.go = "MaryCabinHelp_2";
				}		
			}
			
			link.l9 = "Admiring you, I forgot what I wanted to say...";
			link.l9.go = "exit";
		break;

		case "AboardRestriction":
			npchar.AboardRestriction = true;
			dialog.text = "That's right captain. I will not participate in boarding until you allow it again.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
			if (NPChar.id == "SharleMary" && NPChar.name == "Mary")
				{
				dialog.text = "Charles, you're crazy! And if something happens to you and I'm not around... The two of us will show them all, yes!";
				Link.l1 = "Mary, this is out of the question, you are dear to me, and I want you to be safe.";
				Link.l1.go = "exit";
				}
		break;

		case "AboardAllowed":
			DeleteAttribute(npchar, "AboardRestriction");
			dialog.text = "That's right captain. I will participate in boarding from now on.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
			if (NPChar.id == "SharleMary" && NPChar.name == "Mary")
				{
				dialog.text = "Go-o-o-d! I'm glad you didn't forget about me, now we're going to destroy enemies together, yes!";
				Link.l1 = "I'm glad to hear that, my love!";
				Link.l1.go = "exit";
				}
		break;

		case "CheckMushket":
			if (findsubstr(npchar.model.animation, "man" , 0) != -1 || findsubstr(npchar.model.animation, "YokoDias" , 0) != -1 || findsubstr(npchar.model.animation, "Milenace" , 0) != -1)
			{
				if (findsubstr(npchar.model.animation, "man2_ab" , 0) == -1)	Npchar.CanTakeMushket = true;
			}

			if (CheckAttribute(npchar, "CanTakeMushket"))
			{
				dialog.text = "Of course, Charles!";
				Link.l1 = "Great, then we'll pick something up for you if possible.";
				Link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Better not, Charles. I might accidentally hit you.";
				Link.l1 = "That's right, you're very good with cold steel.";
				Link.l1.go = "exit";
			}
		break;

		case "TargetDistance":
			dialog.text = "Which one, Charles? Point it out, but not more than 20 meters.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Charles, I didn't hear that!";
				link.l1 = "I'll repeat it right now...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "I will stand still, not moving anywhere. Charles, is that okay with you?";
				link.l1 = "Yes, that's exactly what I want you to do, Mary.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "I think I said, that I can't stay more than 20 meters from the target.";
				link.l1 = "All right, keep your distance 20 meters.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Understood the task"+NPCharSexPhrase(npchar, "", "a")+"Yes!";
			link.l1 = "Excellent.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

        // boal 05.09.03 offecer need to go to abordage -->
	      case "Boal_Stay":
             //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
             //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
              Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
              AddDialogExitQuestFunction("LandEnc_OfficerStay");
		      Diag.TempNode = "Hired";
		      dialog.text = "There is a change of location!";
		      Link.l1 = "At ease.";
		      Link.l1.go = "Exit";
			  if (NPChar.id == "SharleMary" && NPChar.name == "Mary")
			  {
				dialog.text = "I'll be waiting for you here, my love!";
				Link.l1 = "I'll be right back, my love, don't miss";
				Link.l1.go = "Exit";
			  }
		      Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	      break;
	      case "Boal_Follow":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		      Diag.TempNode = "Hired";
		      dialog.text = "There is a change of location!";
		      Link.l1 = "At ease.";
		      Link.l1.go = "Exit";
			  if (NPChar.id == "SharleMary" && NPChar.name == "Mary")
			  {
				dialog.text = "We're back together, yes!";
				Link.l1 = "Yes, Mary, you're right as always!";
				Link.l1.go = "Exit";
			  }
	      break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "I would be honored!";
            Link.l1 = "Keep an eye on the order and prosperity of the city, I will sometimes come to collect the toll.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "I changed my mind.";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "What are the orders? Your last visit was " + FindRussianDaysString(iTemp) + " ago.";
			}
			else
			{
			    dialog.Text = "What are your orders?";
			}

            Link.l1 = "What amount of taxes you collected?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "You needed on the ship, I'm taking you off city duty.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Have a nice day.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "My skills allow me to collect " + FindRussianMoneyString(iFortValue*iTax) + " per day. For " + FindRussianDaysString(iTemp) + " I collected " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "I want to collect the entire amount of taxes.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Thank you for your service!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Wonderful! Being a land rat is not my destiny.";
            Link.l8 = "That's good.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "What did you want, my love?";
			Link.l1 = "It's about boarding.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "It's about your ship.";
			Link.l2.go = "Companion_TaskChange";
			// if(bBettaTestMode) // Только при бета-тесте
			// {
			    Link.l3 = "I want you to leave from my squadron and look for luck on your own for a while.";
			    Link.l3.go = "CompanionTravel";
			// }
			Link.l8 = "Nothing yet.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "";
			Link.l1 = "I want you not to board the ships. Take care of yourself and your team.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "I need you to board enemy ships.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "";
			Link.l1 = "I want you not to change your ship after boarding. He's too valuable.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "When you board the enemy, see if there's a decent boat, then take it for yourself.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "I get it, yes!";
			Link.l1 = "Good girl!";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "I get it, yes!";
			Link.l1 = "Good girl!";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "I get it, yes!";
			Link.l1 = "Good girl!";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "I get it, yes!";
			Link.l1 = "Good girl!";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--

		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Charles, I will not leave your squadron, since you have already released three ships.";
					Link.l1 = "Yes, I guess you're right.";
					Link.l1.go = "exit";
				break;
			}

			dialog.Text = "No problem, Charles. Where should I go?";
			Link.l1 = "Go to the city...";
			Link.l1.go = "Travel_Towns";

			Link.l2 = "Go to the pirate settlement...";
			Link.l2.go = "TravelToPiratesTowns";

			Link.l3 = "Go to a desert island...";
			Link.l3.go = "TravelToNomanIslands";

			Link.l99 = "I changed my mind. Nothing is needed.";
			Link.l99.go = "exit";
		break;

		case "Travel_Towns":
			dialog.Text = "Where will the meeting place be, Charles?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama") continue;
				attrLoc = "l" + iTemp;
				NPChar.Temp.(attr) = attr;
				Link.(attrLoc) = "In " + XI_ConvertString("Colony" + attr + "Voc");
				if (IsColonyEnemyToMainCharacter(attr)) {
					Link.(attrLoc).go = "CompanionTravel_EnemyColony";
					continue;
				}
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
			Link.l99 = "I changed my mind. Nothing is needed.";
			Link.l99.go = "exit";
		break;

		case "TravelToPiratesTowns":
			dialog.Text = "Which one exactly?";
				Link.l1 = "Sharp-Town";
				Link.l1.go = "TravelToPirates";
				Link.l2 = "Le Francois";
				Link.l2.go = "TravelToLeFransua";
				Link.l3 = "La Vega";
				Link.l3.go = "TravelToLaVega";
				Link.l4 = "Puero Principe";
				Link.l4.go = "TravelToPuertoPrincipe";
				Link.l6 = "You know, stay for now, I've changed my mind.";
				Link.l6.go = "exit";
		break;
		case "TravelToNomanIslands":
			dialog.Text = "Which one exactly?";
				Link.l1 = "Caiman";
				Link.l1.go = "TravelToCaiman";
				Link.l2 = "Dominica";
				Link.l2.go = "TravelToDominica";
				Link.l3 = "Turks";
				Link.l3.go = "TravelToTerks";
				Link.l4 = "Santa Lucia";
				Link.l4.go = "TravelToLucia";
				Link.l5 = "You know, stay for now, I've changed my mind.";
				Link.l5.go = "exit";
		break;

		case "TravelToCaiman":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_2;									// Companion index
				cn_2 = GetCompanionIndex(PChar, i);
				if (cn_2 == -1) continue;
				if (NPChar.name == characters[cn_2].name) NPChar.realcompanionidx = &characters[cn_2].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "Caiman";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("Caiman"))/300+1.0);
			dialog.Text = "And so, you want me to recover to "+XI_ConvertString("Caiman" + "Gen")+"Captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I changed my mind.";
            Link.l2.go = "exit";
        break;
		case "TravelToLucia":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_3;									// Companion index
				cn_3 = GetCompanionIndex(PChar, i);
				if (cn_3 == -1) continue;
				if (NPChar.name == characters[cn_3].name) NPChar.realcompanionidx = &characters[cn_3].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "StLucia";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("StLucia"))/300+1.0);
			dialog.Text = "And so, you want me to recover to "+XI_ConvertString("StLucia" + "Gen")+"Captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I changed my mind.";
            Link.l2.go = "exit";
        break;
		case "TravelToDominica":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_4;									// Companion index
				cn_4 = GetCompanionIndex(PChar, i);
				if (cn_4 == -1) continue;
				if (NPChar.name == characters[cn_4].name) NPChar.realcompanionidx = &characters[cn_4].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "Dominica";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("Dominica"))/300+1.0);
			dialog.Text = "And so, you want me to recover to "+XI_ConvertString("Dominica" + "Gen")+"Captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I changed my mind.";
            Link.l2.go = "exit";
        break;
		case "TravelToTerks":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_5;									// Companion index
				cn_5 = GetCompanionIndex(PChar, i);
				if (cn_5 == -1) continue;
				if (NPChar.name == characters[cn_5].name) NPChar.realcompanionidx = &characters[cn_5].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "Terks";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("Terks"))/300+1.0);
			dialog.Text = "And so, you want me to recover to "+XI_ConvertString("Terks" + "Gen")+"Captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I changed my mind.";
            Link.l2.go = "exit";
        break;
		case "TravelToLaVega":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_6;									// Companion index
				cn_6 = GetCompanionIndex(PChar, i);
				if (cn_6 == -1) continue;
				if (NPChar.name == characters[cn_6].name) NPChar.realcompanionidx = &characters[cn_6].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "LaVega";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("LaVega"))/300+1.0);
			dialog.Text = "So you want me to recover before"+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+"Captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I changed my mind.";
            Link.l2.go = "exit";
        break;
		case "TravelToPuertoPrincipe":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_7;									// Companion index
				cn_7 = GetCompanionIndex(PChar, i);
				if (cn_7 == -1) continue;
				if (NPChar.name == characters[cn_7].name) NPChar.realcompanionidx = &characters[cn_7].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "PuertoPrincipe";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("PuertoPrincipe"))/300+1.0);
			dialog.Text = "So you want me to recover before"+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+"Captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I changed my mind.";
            Link.l2.go = "exit";
        break;
		case "TravelToFortOrange":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_8;									// Companion index
				cn_8 = GetCompanionIndex(PChar, i);
				if (cn_8 == -1) continue;
				if (NPChar.name == characters[cn_8].name) NPChar.realcompanionidx = &characters[cn_8].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "FortOrange";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("FortOrange"))/300+1.0);
			dialog.Text = "So you want me to recover before"+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+"Captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I changed my mind.";
            Link.l2.go = "exit";
        break;
		case "TravelToPirates":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_9;									// Companion index
				cn_9 = GetCompanionIndex(PChar, i);
				if (cn_9 == -1) continue;
				if (NPChar.name == characters[cn_9].name) NPChar.realcompanionidx = &characters[cn_9].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "Pirates";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("Pirates"))/300+1.0);
			dialog.Text = "So you want me to recover before"+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+"Captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I changed my mind.";
            Link.l2.go = "exit";
        break;
		case "TravelToLeFransua":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_10;									// Companion index
				cn_10 = GetCompanionIndex(PChar, i);
				if (cn_10 == -1) continue;
				if (NPChar.name == characters[cn_10].name) NPChar.realcompanionidx = &characters[cn_10].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "LeFransua";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("LeFransua"))/300+1.0);
			dialog.Text = "So you want me to recover before"+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+"Captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I changed my mind.";
            Link.l2.go = "exit";
        break;

		int nFind = findSubStr(Dialog.CurrentNode, "CompanionTravelToColony_", 0);
		string idxVal;
		string nodName;
		if (nFind == 0)
		{
			idxVal = strcut(Dialog.CurrentNode, 24, strlen(Dialog.CurrentNode) - 1);
			nodName = "CompanionTravelToColony_" + idxVal;
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn;									// Companion index
				cn = GetCompanionIndex(PChar, i);
				if (cn == -1) continue;
				if (NPChar.name == characters[cn].name) NPChar.realcompanionidx = &characters[cn].index;
			}
			aref rCTravel;
			makearef(rCTravel, characters[sti(NPChar.realcompanionidx)].CompanionTravel);
			rCTravel.ToColonyID = NPChar.Temp.(idxVal);
			rCTravel.Days = makeint(GetDistanceToColony2D(NPChar.Temp.(idxVal)) / 300 + 1.0);
			dialog.Text = "You have chosen a colony" + XI_ConvertString("Colony" + rCTravel.ToColonyID + "Gen") + "Captain?";
			Link.l1 = "Yes, it is her.";
			Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I changed my mind.";
			Link.l2.go = "exit";
			break;
		}

		case "CompanionTravel_EnemyColony":
			dialog.Text = "Captain, but I can't wait for you in a colony that is hostile to us!";
				Link.l1 = "You know, forget about all these trips...";
				Link.l1.go = "exit";
		break;

		case "CompanionTravel_NoCrew":
			dialog.Text = "Cap, there are almost no sailors on the ship! What kind of swimming?!";
				Link.l1 = "Yes, that's right. There is almost no team...";
				Link.l1.go = "exit";
		break;

		case "CompanionTravel_NoFood":
			dialog.Text = "Cap, I don't have enough food on board for this trip.";
				Link.l1 = "Yes, you're right. The journey can wait until...";
				Link.l1.go = "exit";
		break;

		case "CompanionTravel_NoHP":
			dialog.Text = "Cap, but my ship is in bad shape. It is not wise for me to go to sea alone under such circumstances!";
				Link.l1 = "Yes, you're right. Your ship needs to be repaired.";
				Link.l1.go = "exit";
		break;

		case "CompanionTravel_PrepareStart":
			int iShip = sti(characters[sti(NPChar.realcompanionidx)].ship.type);
			ref refBaseShip = GetRealShip(iShip);
			if (sti(refBaseShip.hp)/4>sti(characters[sti(NPChar.realcompanionidx)].ship.hp))
			{
				dialog.Text = "I see a problem, Cap...";
				Link.l1 = "Which one?";
				Link.l1.go = "CompanionTravel_NoHP";
				break;
			}
			if (sti(refBaseShip.MinCrew)>GetCrewQuantity(characters[sti(NPChar.realcompanionidx)]))
			{
				dialog.Text = "I see a problem, Cap...";
				Link.l1 = "Which one?";
				Link.l1.go = "CompanionTravel_NoCrew";
				break;
			}
			if (sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+30>CalculateShipFood(characters[sti(NPChar.realcompanionidx)]))
			{
				dialog.Text = "I see a problem, Cap...";
				Link.l1 = "Which one?";
				Link.l1.go = "CompanionTravel_NoFood";
				break;
			}
			dialog.Text = "Everything is clear. To get to " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + " I need " + sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) + " days, what should I do upon arrival?";
			if (sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) == 1)
			{
			dialog.Text = "Everything is clear. " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + " is just around the corner, I'll get there today. What should I do there?";
			}
			Link.l1 = "Wait for me at the raid for a month.";
			Link.l1.go = "CompanionTravel_PrepareStart_2";
			Link.l2 = "You know, I changed my mind. Stay with me for now...";
			Link.l2.go = "exit";
		break;

		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "It's clear, Captain. I'm leaving immediately.";
				Link.l1 = "Yes, go ahead.";
				Link.l1.go = "CompanionTravel_Start";
		break;

		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;

		case "CompanionTravel_LastNode":
Dialog.text = RandPhraseSimple("Today I will go to sea again...",
			"Don't forget to meet me at " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Dat") + ".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;

		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "I wish it too. From now on, my ship is under your command again, Cap.";
					Link.l1 = "Good.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteGroup(NPChar.CompanionTravel.GroupID); // Потрём группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					AddQuestRecord("CompanionTravel", "2");
					AddQuestUserData("CompanionTravel", "sCapName", GetFullName(NPChar)); 
					AddQuestUserData("CompanionTravel", "sShipInfo", GetStrSmallRegister(XI_ConvertString(RealShips[sti(NPChar.Ship.Type)].Basename + "Dat")) + " '" + NPChar.Ship.name + "'");
					if(GetAttrValue(PChar, "CompanionTravel") == 0) CloseQuestHeader("CompanionTravel");
					DeleteAttribute(NPChar, "CompanionTravel");
					for(iTemp=1; iTemp<=3; iTemp++) // Нужно, чтоб была свободная группа
					{
						attr = "Companion" + iTemp;
						if (CheckAttribute(PChar, "CompanionTravel."+(attr)+".ID"))
						{
							if (PChar.CompanionTravel.(attr).ID == NPChar.ID)
							{
								DeleteAttribute(PChar, "CompanionTravel."+(attr));
								DeleteAttribute(NPChar, "Tasks.Clone");
							}
						}
					}
			}
			else
			{
				dialog.text = "Cap, you already have a squadron of five corrals, where else is the sixth? Anyway, I'll be waiting for you here on my ship - all these new companions of yours are not reliable - their ships will sink very soon and you will come back for me.";
					Link.l1 = "Eh, you're a smart head. You don't need to be a captain, but an admiral!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;

		case "CompanionTravel_ToSquadron_2":
			dialog.text = "Ah, Captain. So you're back, just like I said. Well, has a place in the squadron been vacated?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Yes, " + npchar.name + ", released. Welcome to the squadron.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteGroup(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				AddQuestRecord("CompanionTravel", "2");
				AddQuestUserData("CompanionTravel", "sCapName", GetFullName(NPChar)); 
				AddQuestUserData("CompanionTravel", "sShipInfo", GetStrSmallRegister(XI_ConvertString(RealShips[sti(NPChar.Ship.Type)].Basename + "Dat")) + " '" + NPChar.Ship.name + "'");
				if(GetAttrValue(PChar, "CompanionTravel") == 0) CloseQuestHeader("CompanionTravel");
				DeleteAttribute(NPChar, "CompanionTravel");
				for(iTemp=1; iTemp<=3; iTemp++) // Нужно, чтоб была свободная группа
				{
					attr = "Companion" + iTemp;
					if (CheckAttribute(PChar, "CompanionTravel."+(attr)+".ID"))
					{
						if (PChar.CompanionTravel.(attr).ID == NPChar.ID)
						{
							DeleteAttribute(PChar, "CompanionTravel."+(attr));
							DeleteAttribute(NPChar, "Tasks.Clone");
						}
					}
				}
			}
			else
			{
				Link.l1 = "Not yet, unfortunately.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;

		//////////////////////////////    офицер-наместник <--


	        // COLONY BUILDING
		case "ColonyBuilding_Hovernor_1":
			dialog.Text = "I am honored to be the governor of your colony!";
			Link.l1 = "Keep an eye on the order and prosperity of the city. You have a lot to control. I'll come here from time to time.";
			Link.l1.go = "ColonyBuilding_Hovernor_2";
			Link.l2 = "I changed my mind.";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;

	        case "ColonyBuilding_Hovernor_2":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			PChar.ColonyBuilding.Hovernor = NPChar.id;
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			Diag.TempNode = "ColonyBuilding_Hovernor";

			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "Caiman_townhall", "sit", "sit1");
			LAi_SetHuberType(NPChar);

			//PChar.quest.SetHovernorToColonyResidence.win_condition.l1 = "ExitFromLocation";
			//PChar.quest.SetHovernorToColonyResidence.win_condition.l1.location = PChar.location;
			//PChar.quest.SetHovernorToColonyResidence.win_condition = "SetHovernorToColonyResidence";

			DialogExit();
	        break;

		case "ColonyBuilding_Hovernor":
			if(PChar.ColonyBuilding.AutoPurchaseFirst == true && PChar.ColonyBuilding.Store.BuildingTime == false && PChar.ColonyBuilding.AutoPurchaseFirst.Disable != true)
			{
				dialog.Text = "Hello, Captain. A store has recently opened in our colony and I want to tell you about some of the advantages of this important building.";
				Link.l1 = "Go on.";
				Link.l1.go = "ColonyBuilding_AutoStore_1";
				break;
			}

			dialog.Text = "Hello, Captain " + GetFullName(pchar) + ". What can I do for you?";
			Link.l1 = "I want to know the current affairs of the colony.";
			Link.l1.go = "ColonyBuilding_Hovernor_3";
			Link.l2 = "I want to remove you from your position, " + npchar.name + ".";
			Link.l2.go = "ColonyBuilding_Hovernor_4";
			Link.l3 = "Solved to check on you, " + npchar.name + ".";
			Link.l3.go = "Exit";
			Diag.TempNode = "ColonyBuilding_Hovernor";
		break;

		case "ColonyBuilding_Hovernor_3":
			dialog.Text = "Hmm... What kind of cases do you want to inquire about?";
			Link.l1 = "I am interested in the state of the colony and its financial capabilities.";
			Link.l1.go = "ColonyBuilding_Hovernor_3_1";
			Link.l2 = "I am interested in the issue of the combat readiness of the garrison and the health of the residents.";
			Link.l2.go = "ColonyBuilding_Hovernor_3_2";
			Link.l3 = "I want to rename the colony and revise the appearance of the soldiers.";
			Link.l3.go = "ColonyBuilding_Hovernor_3_3";
			Link.l4 = "I'm sorry, " + npchar.name + "I need to take my leave.";
			Link.l4.go = "Exit";

		break;

		case "ColonyBuilding_AutoStore_1":
			PChar.ColonyBuilding.AutoPurchaseFirst.Disable = true;
			dialog.Text = "With an existing store, you can ensure the automatic purchase of essential goods so that the citizens living in the colony and the garrison guarding the colony can receive medicines and food in a timely manner. Contact our dealer if you are interested.";
			Link.l1 = "Interesting. Let's talk about something else.";
			Link.l1.go = "ColonyBuilding_Hovernor_3";
		break;

		case "ColonyBuilding_Hovernor_3_1":
			Diag.TempNode = "ColonyBuilding_Hovernor";
			DialogExit();
			LaunchColony();
		break;

		case "ColonyBuilding_Hovernor_3_2":
			Diag.TempNode = "ColonyBuilding_Hovernor";
			DialogExit();
			LaunchColonyLandGuard();
		break;

		case "ColonyBuilding_Hovernor_3_3":
			Diag.TempNode = "ColonyBuilding_Hovernor";
			DialogExit();
			LaunchColonyBuilding(true, false);
		break;

		case "ColonyBuilding_Hovernor_4":
			dialog.Text = "Are you sure?";
			Link.l1 = "Yes.";
			Link.l1.go = "ColonyBuilding_Hovernor_5";
			Link.l2 = "No, I changed my mind.";
			Link.l2.go = "Exit";
		break;

		case "ColonyBuilding_Hovernor_5":
			PChar.ColonyBuilding.Hovernor = "";
			dialog.Text = "Wonderful! Being a land rat is not my destiny.";
			Link.l1 = "That's good.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;

		case "ColonyBuilding_Expidition_End":
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			dialog.Text = "Hello, Captain " + GetFullName(pchar) + ". I have news for you. Our expedition recently ended. Very fruitful lands were found on the island, and most importantly, ore deposits.";
			Link.l1 = "Hmm, well, that's good. See you later.";
			Link.l1.go = "exit";
		break;

		case "ColonyBuilding_Mines_End":
			PChar.ColonyBuilding.MineMessage = true;
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			dialog.Text = "Hello, Captain " + GetFullName(pchar) + ". I have news for you. The construction of the mines has ended. Now you need to appoint the head of the mines. With him, you will solve all the cases related to this craft.";
			Link.l1 = "Hmm, well, that's good. See you later.";
			Link.l1.go = "exit";
		break;

		case "ColonyBuilding_Plantation_End":
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			dialog.Text = "Hello, Captain " + GetFullName(pchar) + ". I have news for you. The construction of the plantation has been completed. Now you need to appoint the head of the plantation. With him, you will solve all the cases related to this craft.";
			Link.l1 = "Hmm, well, that's good. See you later.";
			Link.l1.go = "exit";
		break;

        	// Начальник рудников
		case "MinesCommander_1":
			dialog.Text = "Hello, Captain " + GetFullName(pchar) + ". What can I do for you?";
			Link.l1 = "I want to know the current affairs of the mines.";
			Link.l1.go = "MinesCommander_2";
			Link.l2 = "I want to remove you from your position, " + npchar.name + ".";
			Link.l2.go = "MinesCommander_Remove";
			Link.l3 = "Solved to check on you, " + npchar.name + ".";
			Link.l3.go = "Exit";
			Diag.TempNode = "MinesCommander_1";
		break;

		case "MinesCommander_2":
			Diag.TempNode = "MinesCommander_1";
			DialogExit();
			LaunchMines();
		break;

		case "MinesCommander_Remove":
			dialog.Text = "Are you sure?";
			Link.l1 = "Yes.";
			Link.l1.go = "MinesCommander_Removed";
			Link.l2 = "No, I changed my mind.";
			Link.l2.go = "Exit";
			Diag.TempNode = "MinesCommander_1";
		break;

		case "MinesCommander_Removed":
			PChar.Mines.Commander = "";
			dialog.Text = "Wonderful! Being a land rat is not my destiny.";
			Link.l1 = "That's good.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;

		case "MinesCommander_Hire":
			dialog.Text = "Well. I will try to meet your expectations.";
			Link.l1 = "That's nice. Get on with your duties.";
			Link.l1.go = "MinesCommander_Hired";
			Link.l2 = "I changed my mind.";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;

		case "MinesCommander_Hired":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);

			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "Caiman_Mines_Comendant_House", "barmen", "stay");

			LAi_SetStayType(NPChar);
			PChar.Mines.Commander = NPChar.id;
			Diag.CurrentNode = "MinesCommander_1";
			Diag.TempNode = "MinesCommander_1";

			//PChar.quest.SetCommanderToMinesOffice.win_condition.l1 = "ExitFromLocation";
			//PChar.quest.SetCommanderToMinesOffice.win_condition.l1.location = PChar.location;
			//PChar.quest.SetCommanderToMinesOffice.win_condition = "SetCommanderToMinesOffice";

			DialogExit();
		break;

        	// Начальник плантации
		case "PlantationCommander_1":
			dialog.Text = "Hello, Captain " + GetFullName(pchar) + ". What can I do for you?";
			Link.l1 = "I want to know the current affairs of the plantation.";
			Link.l1.go = "PlantationCommander_2";
			Link.l2 = "I want to remove you from your position, " + npchar.name + ".";
			Link.l2.go = "PlantationCommander_Remove";
			Link.l3 = "I decided to check on you, " + npchar.name + ".";
			Link.l3.go = "Exit";
			Diag.TempNode = "PlantationCommander_1";
		break;

		case "PlantationCommander_2":
			DialogExit();
			LaunchPlantation();
			Diag.TempNode = "PlantationCommander_1";
		break;

		case "PlantationCommander_Remove":
			dialog.Text = "Are you sure?";
			Link.l1 = "Yes.";
			Link.l1.go = "PlantationCommander_Removed";
			Link.l2 = "No, I changed my mind.";
			Link.l2.go = "Exit";
			Diag.TempNode = "PlantationCommander_1";
		break;

		case "PlantationCommander_Removed":
			PChar.Plantation.Commander = "";
			dialog.Text = "Wonderful! Being a land rat is not my destiny.";
			Link.l1 = "That's good.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;

		case "PlantationCommander_Hire":
			dialog.Text = "Well. I will try to meet your expectations.";
			Link.l1 = "That's nice. Get on with your duties.";
			Link.l1.go = "PlantationCommander_Hired";
			Link.l2 = "I changed my mind.";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;

		case "PlantationCommander_Hired":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			PChar.Plantation.Commander = NPChar.id;
			Diag.CurrentNode = "PlantationCommander_1";
			Diag.TempNode = "PlantationCommander_1";

			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "CaimanPlantationOffice", "goto", "goto1");
			LAi_SetStayType(NPChar);

			//PChar.quest.SetCommanderToPlantationOffice.win_condition.l1 = "ExitFromLocation";
			//PChar.quest.SetCommanderToPlantationOffice.win_condition.l1.location = PChar.location;
			//PChar.quest.SetCommanderToPlantationOffice.win_condition = "SetCommanderToPlantationOffice";

			DialogExit();
		break;

	        // Помошник по охране - начальник гарнизона
		case "ColonyGuarding_Hovernor_1":
			dialog.Text = "Hmm... I think I can handle the task at hand.";
			Link.l1 = "Of course you will, otherwise... uh-uh... You can start!";
			Link.l1.go = "ColonyGuarding_Hovernor_2";
			Link.l2 = "I changed my mind.";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;

	        case "ColonyGuarding_Hovernor_2":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			PChar.Colony.Guardians.Hovernor = NPChar.id;

			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "LandGuardingHeadHouse", "goto", "goto3");
			LAi_SetStayType(NPChar);

			Diag.CurrentNode = "ColonyGuarding_Hovernor";
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
	        break;

		case "ColonyGuarding_Hovernor":
			dialog.Text = "Hello, Captain " + GetFullName(pchar) + ". What can I do for you?";
			Link.l1 = "I want to know the current protection status.";
			Link.l1.go = "ColonyGuarding_Hovernor_3";
			Link.l2 = "I want to remove you from your position, " + npchar.name + ".";
			Link.l2.go = "ColonyGuarding_Hovernor_4";
			Link.l3 = "I want to talk about hiring a team for the garrison guarding our colony.";
			Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_1";
			Link.l4 = "I decided to check on you, " + npchar.name + ".";
			Link.l4.go = "Exit";
			Diag.TempNode = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_3":
			dialog.Text = "Hmm... What kind of cases do you want to inquire about?";
			Link.l1 = "I'm interested in the question of the coastline.";
			Link.l1.go = "ColonyGuarding_Hovernor_3_1";
			Link.l2 = "I am interested in the issue of the combat readiness of the garrison and the health of the residents.";
			Link.l2.go = "ColonyGuarding_Hovernor_3_2";
			Link.l3 = "I am interested in the issue of the readiness of the coast guard.";
			Link.l3.go = "ColonyGuarding_Hovernor_3_3";
			Link.l4 = "I'm sorry, " + npchar.name + "I need to take my leave.";
			Link.l4.go = "Exit";
		break;

		case "ColonyGuarding_Hovernor_3_1":
		    	CheckDeadColonyGuard();
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
			LaunchColonyGuardiang();
		break;

		case "ColonyGuarding_Hovernor_3_2":
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
			LaunchColonyLandGuard();
		break;

		case "ColonyGuarding_Hovernor_3_3":
			CheckDeadColonyGuard();

			if(GetColonyGuardsShipsQuantity() < 1)
			{
				dialog.Text = "Captain, there are no ships in the squadron at the moment...";
				Link.l1 = "Oh yeah, I forgot...";
				Link.l1.go = "exit";
				PChar.Colony.Guardians.BaseComplete = false;
				break;
			}

			string sBaseComplete = "";

			if(PChar.Colony.Guardians.BaseComplete == true)
			{
				sBaseComplete = "the ships are fully equipped weekly and are always ready for battle. At the moment, the amount that is needed for this is " + GetCostForBaseCompletationAllGuards() + " piastres.";
			}
			else
			{
				sBaseComplete = "the ships of the coastline are not equipped. But, it is possible to inspect the ships every week and carry out their full complement in order to repel the scoundrels at any time.";
			}

			dialog.Text = "Hmm... At the moment " + sBaseComplete;

			if(PChar.Colony.Guardians.BaseComplete == true)
			{
				Link.l1 = "I think it's worth suspending the weekly package for now. The treasury is not rubber...";
				Link.l1.go = "ColonyGuarding_Hovernor_3_3_3";
			}
			else
			{
				if(PChar.Colony.Guardians.BaseComplete.First == true)
				{
					Link.l1 = "Tell me more about it.";
					Link.l1.go = "ColonyGuarding_Hovernor_3_3_1";
				}
				else
				{
					Link.l1 = "I think it's worth resuming the weekly coast guard training.";
					Link.l1.go = "ColonyGuarding_Hovernor_3_3_2";
				}
			}

			Link.l2 = "Excuse me, I have business to attend to.";
			Link.l2.go = "Exit";
			Diag.CurrentNode = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_3_3_1":
			PChar.Colony.Guardians.BaseComplete.First = false;
			dialog.Text = "Every week, the ships of the coast guard will be inspected, and those ships that will currently guard it will be supplemented with missing ammunition and essential goods, in addition, the crew will be replenished, but in order for all this to work, it will be necessary to go to some expenses that depend on the ships being completed. For example, at the moment it will be necessary to pay " + GetCostForBaseCompletationAllGuards() + " piastres per week from the treasury of the colony. If this amount is missing, then, unfortunately, there will be nothing to complete. What do you say?";
			Link.l1 = "It's a useful thing. I give permission for the timely disbursement of funds from the colony's treasury.";
			Link.l1.go = "ColonyGuarding_Hovernor_3_3_2";
			Link.l2 = "I guess we'll do without that for now.";
			Link.l2.go = "Exit";
		break;

		case "ColonyGuarding_Hovernor_3_3_2":
			PChar.Colony.Guardians.BaseComplete = true;
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
		break;

		case "ColonyGuarding_Hovernor_3_3_3":
			PChar.Colony.Guardians.BaseComplete = false;
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
		break;

		case "ColonyGuarding_Hovernor_4":
			dialog.Text = "Are you sure?";
			Link.l1 = "Yes.";
			Link.l1.go = "ColonyGuarding_Hovernor_5";
			Link.l2 = "No, I changed my mind.";
			Link.l2.go = "Exit";
		break;

		case "ColonyGuarding_Hovernor_5":
			PChar.Colony.Guardians.Hovernor = "";
			dialog.Text = "Wonderful! Being a land rat is not my destiny.";
			Link.l1 = "That's good.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_1":
			dialog.Text = "All right, Captain. What can I do for you in this matter?";
			Link.l1 = "I would like to know more about this possibility.";
			Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Info";
			Link.l2 = "I want to know the prices that are required to secure a hire.";
			Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_Costs";
			Link.l3 = "It is necessary to review the facilities where garrison recruitment is provided.";
			Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_Set";
			Link.l4 = "No, I changed my mind.";
			Link.l4.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Info":
			dialog.Text = "I can independently hire a team for the garrison, so that our colony and the buildings belonging to it could always repel the enemy and pacify the rebellious inhabitants and slaves. But, as you understand, it will cost much more than the usual hiring in the taverns of the archipelago. Each time, the garrison will be replenished taking into account the current configuration of the garrisons. The garrison can be hired for all facilities - and this is our colony, plantation and mines. Every time there should be an amount in the treasury of the colony that allows hiring a garrison for a certain object. If there is no such amount in the treasury, then hiring, accordingly, will not happen.";
			Link.l1 = "Thanks for the information, " + npchar.name + ".";
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Costs":
			dialog.Text = "The price of securing the hiring of which facilities are you interested in?";

			if(PChar.ColonyBuilding.Stage != "0")
			{
				Link.l1 = "The colony.";
				Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Colony";
			}
			if(PChar.Mines.GoldMine == true || PChar.Mines.SilverMine == true || PChar.Mines.IronMine == true)
			{
				Link.l2 = "The mines.";
				Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Mines";
			}
			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				Link.l3 = "The plantation.";
				Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Plantation";
			}

			Link.l4 = "Sorry, I have to go.";
			Link.l4.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Colony":
			dialog.Text = "At the moment, the price of hiring the garrison of the colony is based on the staffing of the garrison: " + ColonyGuardingGetCostForObject("Colony", false) + " gold; for full filling without taking into account staffing: " + ColonyGuardingGetCostForObject("Colony", true) + "gold.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Mines":
			dialog.Text = "At the moment, the price of securing the hiring of the garrison of mines is taking into account the staffing of the garrison: " + ColonyGuardingGetCostForObject("Mines", false) + " gold; for full filling without taking into account staffing: " + ColonyGuardingGetCostForObject("Mines", true) + "gold.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Plantation":
			dialog.Text = "At the moment, the price of securing the hiring of the plantation garrison is taking into account the staffing of the garrison: " + ColonyGuardingGetCostForObject("Plantation", false) + " gold; for full filling without taking into account staffing: " + ColonyGuardingGetCostForObject("Plantation", true) + "gold.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Okay.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Set":
			dialog.Text = ColonyGuardingAutoCrewHireGetWork();

			if(PChar.ColonyBuilding.Stage != "0")
			{
				if(PChar.Colony.Guardians.Colony.AutoCrewHire == false)
				{
					Link.l1 = "I want to take the opportunity to hire a garrison to guard the colony.";
					Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_1";
				}
				else
				{
					Link.l1 = "I want to suspend the hiring of a garrison to guard the colony.";
					Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_1";
				}
			}

			if(PChar.Mines.GoldMine == true || PChar.Mines.SilverMine == true || PChar.Mines.IronMine == true)
			{
				if(PChar.Colony.Guardians.Mines.AutoCrewHire == false)
				{
					Link.l2 = "I want to take the opportunity to hire a garrison to guard the mines.";
					Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_1";
				}
				else
				{
					Link.l2 = "I want to suspend the hiring of a garrison to guard the mines.";
					Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_1";
				}
			}

			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.Colony.Guardians.Plantation.AutoCrewHire == false)
				{
					Link.l3 = "I want to take the opportunity to hire a garrison to guard the plantation.";
					Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_1";
				}
				else
				{
					Link.l3 = "I want to suspend the hiring of a garrison to guard the plantation.";
					Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_1";
				}
			}

			Link.l4 = "Sorry, I have to go.";
			Link.l4.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_1":
			dialog.text = "Are you sure, Captain?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure..");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_2";
			link.l2 = LinkRandPhrase("Mm... Perhaps you're right - it's worth thinking more.", "I've changed my mind.", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_2":
			PChar.Colony.Guardians.Colony.AutoCrewHire = true;
			dialog.text = "All right, Captain! I will deal with this issue from today.";
			link.l1 = "That's nice.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_1":
			dialog.text = "Are you sure, Captain?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure..");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_2";
			link.l2 = LinkRandPhrase("Mm... Perhaps you're right - it's worth thinking more.", "I've changed my mind.", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_2":
			PChar.Colony.Guardians.Mines.AutoCrewHire = true;
			dialog.text = "All right, Captain! I will deal with this issue from today.";
			link.l1 = "That's nice.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_1":
			dialog.text = "Are you sure, Captain?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure..");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_2";
			link.l2 = LinkRandPhrase("Mm... Perhaps you're right - it's worth thinking more.", "I've changed my mind.", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_2":
			PChar.Colony.Guardians.Plantation.AutoCrewHire = true;
			dialog.text = "All right, Captain! I will deal with this issue from today.";
			link.l1 = "That's nice.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_1":
			dialog.text = "Do you really want to suspend the hiring of a team for the colony's garrison?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure..");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_2";
			link.l2 = LinkRandPhrase("Set aside!", "I may have changed my mind..", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_2":
			PChar.Colony.Guardians.Colony.AutoCrewHire = false;
			dialog.text = "As you wish, Captain.";
			link.l1 = LinkRandPhrase("Thank you.", "Clear.", "Good.");
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_1":
			dialog.text = "Do you really want to suspend hiring a team for the mine garrison?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure..");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_2";
			link.l2 = LinkRandPhrase("Set aside!", "I may have changed my mind..", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_2":
			PChar.Colony.Guardians.Mines.AutoCrewHire = false;
			dialog.text = "As you wish, Captain.";
			link.l1 = LinkRandPhrase("Thank you.", "Clear.", "Good.");
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_1":
			dialog.text = "Do you really want to suspend hiring a team for the plantation garrison?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure..");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_2";
			link.l2 = LinkRandPhrase("Set aside!", "I may have changed my mind...", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_2":
			PChar.Colony.Guardians.Plantation.AutoCrewHire = false;
			dialog.text = "As you wish, Captain.";
			link.l1 = LinkRandPhrase("Thank you.", "Clear.", "Good.");
			link.l1.go = "exit";
		break;
		// <-- Самостоятельное плавание компаньона
		
		// секс - Мэри не отказывает никогда
		case "Mary_cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+"there is no greater joy for me than being in your arms, yes... Let's go!", ""+pchar.name+" if it were possible, I wouldn't leave you for a minute at all. Let's go!");
			link.l1 = RandPhraseSimple("You are the best in the world, my girl...", "You are just lovely, my beauty ...");
			link.l1.go = "Mary_cabin_sex_go";
		break;
		
		case "Mary_room_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+"there is no greater joy for me than being in your arms, yes... Let's go!", ""+pchar.name+" if it were possible, I wouldn't leave you for a minute at all. Let's go!");
			link.l1 = RandPhraseSimple("You are the best in the world, my girl...", "You are just lovely, my beauty ...");
			link.l1.go = "Mary_room_sex_go";
		break;
		
		case "Mary_cabin_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			AddCharacterExpToSkill(pchar, "Leadership", 40);
            AddCharacterExpToSkill(npchar, "Leadership", 40);
            AddCharacterExpToSkill(pchar, "Fencing", 15);
            AddCharacterExpToSkill(npchar, "Fencing", 15);
            AddCharacterExpToSkill(pchar, "Pistol", 15);
            AddCharacterExpToSkill(npchar, "Pistol", 15);
            AddCharacterHealth(pchar, 12);
            AddCharacterHealth(npchar, 12);
			LAi_SetCurHPMax(pchar);
			LAi_SetCurHPMax(npchar);
   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "Mary_sex_after";
		break;
		
		case "Mary_room_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			AddCharacterExpToSkill(pchar, "Leadership", 40);
            AddCharacterExpToSkill(npchar, "Leadership", 40);
            AddCharacterExpToSkill(pchar, "Fencing", 15);
            AddCharacterExpToSkill(npchar, "Fencing", 15);
            AddCharacterExpToSkill(pchar, "Pistol", 15);
            AddCharacterExpToSkill(npchar, "Pistol", 15);
			AddCharacterHealth(pchar, 12);
            AddCharacterHealth(npchar, 12);
			LAi_SetCurHPMax(pchar);
			LAi_SetCurHPMax(npchar);
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			}
			DoQuestCheckDelay("PlaySex_1", 2.1);
			NextDiag.CurrentNode = "Mary_sex_after";
		break;
		
		case "Mary_sex_after":
			dialog.text = RandPhraseSimple("Honey, you were great as always!", "Everything was just wonderful, dear!");
			link.l1 = RandPhraseSimple("I'm glad you're happy, the light of my soul...", "I adore you, Mary...");
			link.l1.go = "exit";
			sld = characterFromID("SharleMary");
			sld.Dialog.Filename = "Quest\MainheroPrologues\Mary_dialog.c";
			sld.dialog.currentnode = "hired";
			LAi_SetOfficerType(sld);
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 5, false);
		break;
		
		case "Mary_givemesex":	// требует секса, если давно не давал
			dialog.text = RandPhraseSimple(""+pchar.name+", we haven't been together for so long... You completely forgot about me, yes! Honey, I want to relax - let's rent a room and leave!", ""+pchar.name+", you got completely carried away with business, and I'm beginning to suspect that you completely forgot about me! Darling, I really want to... to be alone with you. Let's rent a room, yeah!");
			link.l1 = "Mary, honey, what are you saying - 'forgot about me'? Nonsense... But I'm really stuck with all these problems, there's no end to them. I'm sorry, my girl. Of course, let's go upstairs - and let the whole world wait!";
			link.l1.go = "Mary_room_sex_go";
		break;
		
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "Mary_brothel":
			dialog.text = "Yes, it's not like that! You don't like me anymore, do you? Tell me!";
			link.l1 = "That's the number! Mary, what nonsense is this? What makes you think that?";
			link.l1.go = "Mary_brothel_1";
		break;
		
		case "Mary_brothel_1":
			dialog.text = "Then why did you go to these bitches, these bordello girls? I know that, yes, don't deny it! I don't suit you when we make love, do I? (crying) Tell me...";
			link.l1 = "Mary, Mary... Calm down, please, girl. Yes, I was in a brothel, but only on business. You see, for business, not for entertainment!";
			link.l1.go = "Mary_brothel_2";
		break;
		
		case "Mary_brothel_2":
			dialog.text = "And you're in the whore room too You've been up 'on business', haven't you? (sobbing) You're lying to me, "+pchar.name+"!";
			link.l1 = "Mary, honey, stop it at last... I did have business with the brothel owner. And I went upstairs too... Here, for the last time, at the personal request of the governor, he asked to find his lost wedding ring there. How could I refuse His Lordship?";
			link.l1.go = "Mary_brothel_5";
		break;
		
		case "Mary_brothel_5":
			dialog.text = "";
			link.l1 = "See? I'm telling you, these are business visits. Mary, I really don't need anyone but you. You're my best, honestly! Do you really think I'm going to go to some dirty harbor whores when I have you? How could you even think of such a thing?";
			link.l1.go = "Mary_brothel_6";
		break;
		
		case "Mary_brothel_6":
			dialog.text = ""+pchar.name+"... Is this really the case? Are you not lying? Weren't you with them?";
			link.l1 = "Mary, honey, there is no one else for me except you, really. Come closer, dear. Let me hug you... Wipe away your tears, and finally stop being jealous! Well, if you want, I won't go into brothels anymore!";
			link.l1.go = "Mary_brothel_7";
		break;
		
		case "Mary_brothel_7":
			dialog.text = "Yes, I want to!.. "+pchar.name+", I'm jealous because I like you... And I don't want to lose you, yes! Do you hear? I will kill any trash that dares to approach you!";
			link.l1 = "Hush, hush... my owner. You won't need to kill anyone. And you won't lose me, I promise. That's it, calm down. You are the only one and the best in the world...";
			link.l1.go = "Mary_brothel_8";
		break;
		
		case "Mary_brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("It's been a few minutes", "", 0, 5);
			//SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // всё, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
	}
}

void FireImmortalOfficer(ref chr)
{
	if (CheckAttribute(chr, "ImmortalOfficer"))
	{
		DeleteAttribute(chr, "ImmortalOfficer")
		pchar.Option_ImmortalOfficers = sti(sti(pchar.Option_ImmortalOfficers) - 1);
	}
}
