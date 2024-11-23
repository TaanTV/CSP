// 03.02.08 перенос из ВМЛ

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;

    Pchar.quest.FreeRandomOfficerIdx = NPChar.index;

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":

            NextDiag.TempNode = "First time";
			dialog.text = RandPhraseSimple("Greetings, Captain! Don't you need a female officer on your trough?",
                          "Do you need a new, very advanced officer?");
			link.l1 = ""+ GetSexPhrase("Girl? An officer? It's very strange... And what are you good for?", "There's another woman on the ship, and what's the use of you?") +"";
			link.l1.go = "Node_2";
            link.l2 = ""+ GetSexPhrase("No, cutie, I have a complete set.", "With that appearance, go to the men... an officer...") +"";
			link.l2.go = "exit";
		break;

		case "CitizenNotBlade":
			dialog.text = "Captain, what nonsense! Put away your weapons before you cause trouble!";
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Don't worry, I'm already removing...");
			link.l1.go = "exit";
		break;

		case "Node_2":
            if (NPChar.alignment == "good" && sti(pchar.reputation) <= 70)
            {
                dialog.text = "I'm good for a lot of things, but we won't work together with you. Your reputation is not good enough. I guess I won't join your team.";
    			link.l1 = "With such requests, you will be out of work for a long time!";
    			link.l1.go = "exit";
    			break;
            }

            if (NPChar.alignment == "bad" && sti(pchar.reputation) >= 30)
            {
                dialog.text = "I'm good for a lot, but not for saints like you, "+ GetSexPhrase("handsome", "beautiful") +". I guess I won't join your team.";
    			link.l1 = "With such requests, you will be out of work for a long time!";
    			link.l1.go = "exit";
    			break;
            }
			dialog.text = "Take me as a bodyguard and your back will always be covered by my sword. Agility and speed are my trump cards.";
			link.l1 = "Personal bodyguard mmm..."+ GetSexPhrase("", "also a girl...") +"How much do you want for this service?";
			link.l1.go = "price";
            link.l2 = "Thanks, I'll manage.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgain";
		break;

        case "OnceAgain":
            NextDiag.TempNode = "OnceAgain";
            if (NPChar.alignment == "good" && sti(pchar.reputation) <= 70)
            {
                dialog.text = "I'm good for a lot of things, but we won't work together with you. Your reputation is not good enough. I guess I won't join your team.";
    			link.l1 = "With such requests, you will be out of work for a long time!";
    			link.l1.go = "exit";
    			break;
            }

            if (NPChar.alignment == "bad" && sti(pchar.reputation) >= 30)
            {
                dialog.text = "I'm good for a lot, but not for saints like you, "+ GetSexPhrase("handsome", "beautiful") +". I guess I won't join your team.";
    			link.l1 = "With such requests, you will be out of work for a long time!";
    			link.l1.go = "exit";
    			break;
            }
			dialog.text = "Have you changed your mind, Captain? Have you decided that a new bodyguard, and even a girl, won't bother you?";
			link.l1 = "Perhaps so. How much do you want?";
			link.l1.go = "price";
            link.l2 = "You're wrong. Have a nice stay.";
			link.l2.go = "exit";
		break;

		case "price":
            if (FindFreeRandomOfficer() == -1)
            {
                dialog.text = "Hmm. You have a complete set. We'll talk about the price when you can give me a job.";
    			link.l1 = "Okay.";
    			link.l1.go = "exit";
    			break;
            }
			dialog.text = "I think you and I will agree on 50,000 piastres.";
			link.l1 = "I agree, pretty woman. Consider yourself enrolled in the team.";
			link.l1.go = "hire";
            link.l2 = "You're not worth the money. Goodbye.";
			link.l2.go = "exit";
		break;

        case "hire":
			if(makeint(Pchar.money) >= 50000)
			{
				AddMoneyToCharacter(Pchar, -50000);
                dialog.text = "I won't thank you, Captain. You know very well that you have successfully invested your gold.";
			    link.l1 = "I want to believe it.";
			    link.l1.go = "Exit_hire";
			}
			else
			{
				NextDiag.TempNode = "OnceAgain";
                dialog.text = "Hey, it looks like you're having cash problems! I'm sorry, Captain, but I don't work on credit.";
				link.l1 = "Oh, damn it!";
				link.l1.go = "Exit";
			}
		break;

        case "hired":
			NextDiag.TempNode = "Hired";
			dialog.text = ""+ GetSexPhrase("What does my precious captain want?", "What are the orders?") +"";
			link.l2 = "You're fired. I'll do without your services!";
			link.l2.go = "AsYouWish";

			if (bHalfImmortalPGG)
			{
				if (!CheckAttribute(pchar, "Option_ImmortalOfficers"))
				{
					pchar.Option_ImmortalOfficers = "0";
				}
				if (sti(pchar.Option_ImmortalOfficers) < makeint(GetCharacterSPECIAL(pchar, "Charisma")*2) && !CheckAttribute(npchar, "ImmortalOfficer"))
				{
					Link.l6 = "I have a proposal for you.";
					Link.l6.go = "contract";
				}
			}

			//Расторжение контракта
			
			if (CheckAttribute(npchar, "ImmortalOfficer"))
			{
				Link.l6 = "I want to terminate the contract between us.";
				Link.l6.go = "cancelcontract1";
			}

			// приколы -->
            if (PChar.location == Get_My_Cabin())
            {
    			if (PChar.sex != "woman")
    			{
					Link.l3 = RandPhraseSimple("Since we're in the cabin, let's maybe... eh? Look, there's a bed here... so soft...",
	                                           "Look at the big bed in my cabin. Don't you want to share it with me?");
	                if (sti(pchar.GenQuest.BrothelCount) > 4+rand(3))
	                {
	                    Link.l3.go = "Love_Sex_Yes";
	                }
	                else
	                {
	                    Link.l3.go = "Love_Sex";
	                }
                }
                if (CheckAttribute(pchar , "questTemp.FUNY_SHIP_FIND") && PChar.questTemp.FUNY_SHIP_FIND == true && GetCharacterItem(PChar, "mineral4") >= 25)
                {
                    Link.l4 = "Look what an interesting collection I have gathered!";
            		Link.l4.go = "FUNY_SHIP_1";
                }
            }
            else
            {
                if (PChar.sex != "woman")
                {
					Link.l3 = RandPhraseSimple("A bodyguard girl is good, of course, but can we try to get closer?",
	                                           "What about non-statutory services?");
	                Link.l3.go = "Love_Sex";
                }
            }
            Link.l5 = "Listen to my order!";
            Link.l5.go = "stay_follow";

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
								Link.l7 = "I am appointing you as the governor of this city!";
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
						Link.l8 = "I want to appoint you as the governor of the colony '" + PChar.ColonyBuilding.ColonyName + "', which we built on the island of Cayman.";
						Link.l8.go = "ColonyBuilding_Hovernor_1";
					}
				}
			}

            link.l9 = ""+ GetSexPhrase("Relax, pretty girl, relax", "Nothing. At ease") +".";
			link.l9.go = "exit";
        break;

        case "FUNY_SHIP_1":
		    dialog.text = "Oh horror! Captain, take this away from me, such an unbearable stench... Do you believe in all this nonsense of the old legend about getting an invincible fighter?";
   			Link.l1 = "No, of course, I'm sorry. I'm going to throw this whole stinking mass overboard.";
            Link.l1.go = "exit";
            Link.l2 = "Yes, I do! Moreover, I'll check it out. Come on, come closer!";
            Link.l2.go = "FUNY_SHIP_2";
        break;

        case "FUNY_SHIP_2":
		    dialog.text = "What a stink! Ugh... Although it works, I feel stronger and even, um, more beautiful.";
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

		case "contract":
			dialog.text = "I'm listening to you carefully, Captain.";
			Link.l1 = "You are a good officer and you are completely suitable for me. I want to suggest that you join my contract service.";
			Link.l1.go = "contract2";
		break;

		case "contract2":
			dialog.text = "Thanks for the kind words, Captain. And what are the terms of the contract?";
			Link.l1 = "A large one-time payment. Better equipment, "+ NPCharSexPhrase(NPChar, "myself", "myself") +" you see. The contract period is 10 years. You can quit at the end of the term, and if everything suits both of us, we'll extend it further.";
			Link.l1.go = "contract3";
		break;

		case "contract3":
			NPChar.contractMoney = makeint(sti(NPChar.rank)*MOD_SKILL_ENEMY_RATE*3*1000);
			dialog.text = "Tempting offer, you can't say anything. Earn a little money for a quiet old age. What about small lifts for the permanent staff?";
			if (sti(Pchar.money) >= sti(NPChar.contractMoney))
			{
				Link.l1 = "I have nothing against it, would " + sti(NPChar.contractMoney) + " gold coins suit you right now?";
				Link.l1.go = "contract4";
			}
			Link.l2 = "I don't mind, but let's get back to this conversation later.";
			Link.l2.go = "Exit";
		break;

		case "contract4":
			dialog.text = "Quite, Captain. I agree" + GetSexPhrase("en.", "sleep.");
			AddMoneyToCharacter(Pchar, -sti(NPChar.contractMoney));
			SetCharacterPerk(NPChar, "EnergyPlus");
			SetCharacterPerk(NPChar, "HPPlus");
			NPChar.OfficerWantToGo.DontGo = true;
			NPChar.loyality = MAX_LOYALITY;
			NPChar.Reputation = REPUTATION_NEUTRAL;
			DeleteAttribute(NPChar, "alignment");
			if (bHalfImmortalPGG)
			{
				if (!CheckAttribute(pchar, "Option_ImmortalOfficers"))
				{
					pchar.Option_ImmortalOfficers = "1";
				}
				else
				{
					pchar.Option_ImmortalOfficers = sti(sti(pchar.Option_ImmortalOfficers) + 1);
				}
				//pchar.PGG_hired = true;
				NPChar.ImmortalOfficer = true;
				NPChar.HalfImmortal = true;  // Контузия
				//string immortal_officer = npchar.id;
				//pchar.quest.(immortal_officer).win_condition.l1 = "NPC_Death";
				//pchar.quest.(immortal_officer).win_condition.l1.character = npchar.id;
				//pchar.quest.(immortal_officer).function = "Remove_Contract_Officer";
			}
			// DeleteAttribute(NPChar, "contractMoney");//Mett: это можно заблокировать по желанию, мб потом понадобиться для перерасчёта суммы контракта
			Link.l1 = "That's great! Agreed";
			Link.l1.go = "Exit";
		break;

		case "cancelcontract1":
			dialog.text = "Quite unexpected, Captain. And what am I " + NPCharSexPhrase(NPChar, "guilty?", "guilty?");
			Link.l1 = "Forget it, I was wrong" + GetSexPhrase("xia.", "las.");
			Link.l1.go = "Exit";
			Link.l2 = "I'm not satisfied with your skills.";
			Link.l2.go = "cancelcontract2";
		break;
			
		case "cancelcontract2":
			NPChar.contractMoney = makeint(sti(NPChar.rank)*MOD_SKILL_ENEMY_RATE*3*1000);
			dialog.text = "That's how, well, if you pay the penalty under the contract, then I will have no complaints.";
			if (sti(Pchar.money) >= sti(NPChar.contractMoney))
			{
				Link.l1 = "Whatever you say, would " + sti(NPChar.contractMoney) + " gold coins suit you right now?";
				Link.l1.go = "cancelcontract3";
			}
			Link.l2 = "I'm having cash problems right now, we'll come back to this conversation later.";
			Link.l2.go = "Exit";
		break;
			
		case "cancelcontract3":
			dialog.text = "Quite, Captain. I agree" + NPCharSexPhrase(NPChar, "en.", "on.");
			AddMoneyToCharacter(Pchar, -sti(NPChar.contractMoney));
			pchar.Option_ImmortalOfficers = sti(sti(pchar.Option_ImmortalOfficers) - 1);
			NPChar.OfficerWantToGo.DontGo = false;
			NPChar.HalfImmortal = false;
			NPchar.loyalty = MAX_LOYALITY / 2;
			DeleteAttribute(npchar, "ImmortalOfficer");
			if (rand(sti(pchar.reputation)) >= 50)
			{
				NPchar.alignment  = "good";
				NPchar.reputation = 61 + rand(29);
			}
			else
			{
				NPchar.alignment = "bad";
				NPchar.reputation = 39 - rand(29);
			}
			Link.l1 = "That's good.";
			Link.l1.go = "Exit";
		break;

        case "Love_Sex_Yes":
		    dialog.text = RandPhraseSimple("Perhaps you can give in to such a ladies' man.",
                                           "Well, it's better than wasting money on street girls.");
            link.l1 = RandPhraseSimple("Oh, Yes!", "Smart girl, I can't go to a brothel when there's a beauty like you by my side!");
			link.l1.go = "Love_Sex_Yes_2";
        break;

        case "Love_Sex_Yes_2":
            pchar.GenQuest.BrothelCount = 0;
            AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterExpToSkill(pchar, "Fencing", -50);// утрахала
            AddCharacterExpToSkill(pchar, "Pistol", -50);
            AddCharacterHealth(pchar, 10);

   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "After_sex";
			DialogExit();
        break;

        case "After_sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Hmm.. It's strange, I thought you were capable of more...",
                                           "Captain, now you can think with your head again, and not... ? Let's get back to our business.");
            link.l1 = RandPhraseSimple("How do you talk to a senior!", "I can do a lot if I collect my thoughts.");
			link.l1.go = "exit";
        break;

        case "Love_Sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("What!!!?? Captain, have you been ashore or in a brothel for a long time?", "I don't understand what you're talking about?");
            link.l1 = RandPhraseSimple("Well, think about it.. you are such a beauty, and even in my subordination", "Well, I can't go to a brothel when you are at my side!");
			link.l1.go = "Love_Sex_2";
			link.l2 = RandPhraseSimple("I'm sorry, baby, it was very difficult not to offer..", "Eh.. Okay, never mind...");
			link.l2.go = "exit";
        break;

        case "Love_Sex_2":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Captain! Keep yourself in hand, if you can't in yours, call the sailors", "The fact that I am an officer and nominally obey you, captain, does not mean anything!");
            link.l1 = RandPhraseSimple("Baby, don't mind. I can't hold myself back anymore. Let's go..", "I'm your captain! And I'm ordering you!");
			link.l1.go = "Love_Sex_3";
			link.l2 = RandPhraseSimple("I'm sorry, baby, it was very difficult not to offer..", "Eh.. Okay, never mind...");
			link.l2.go = "exit";
        break;

        case "Love_Sex_3":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("That's it! You will answer for this! And right now!", "Roll around with you? Well, now let's see who is capable of what..");
            link.l1 = "Uh... what are you talking about?";
			link.l1.go = "Love_Sex_4";
        break;

        case "Love_Sex_4":
            ChangeCharacterReputation(pchar, -15);
            CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
            LAi_SetWarriorType(Npchar);
            LAi_group_MoveCharacter(Npchar, "TmpEnemy");
            LAi_group_SetHearRadius("TmpEnemy", 100.0);
            LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			DeleteAttribute(Npchar, "HalfImmortal");
			Npchar.LifeDay = 0;
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
                LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;
        // приколы <--

        case "AsYouWish":
			dialog.text = "Whatever you say, Captain, it's up to you.";
			link.l1 = "I think I've changed my mind. I still need you.";
			link.l1.go = "exit";
			link.l2 = "Excellent. You can get the hell out of here.";
			link.l2.go = "Exit_Fire";
		break;

        case "Exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			npchar.Dialog.FileName = "Enc_Officer_dialog.c";
			NPChar.Dialog.TempNode = "hired";
			Npchar.CanTakeMushket = true;
			npchar.HalfImmortal = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_fire":
   			NextDiag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Fired":
		      NextDiag.TempNode = "Fired";
		      dialog.text = "I warned you, Captain, that I would not return to your ship. I have my own pride.";
		      Link.l1 = "I don't need you!";
		      Link.l1.go = "Exit";
	    break;
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "stay_follow":
            dialog.Text = "What are your orders?";
            Link.l1 = "Stay here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
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
        break;

		case "AboardRestriction":
			npchar.AboardRestriction = true;
			dialog.text = "That's right captain. I will not participate in boarding until you allow it again.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
		break;

		case "AboardAllowed":
			DeleteAttribute(npchar, "AboardRestriction");
			dialog.text = "That's right captain. I will participate in boarding from now on.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
		break;

        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "There is a change of location!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;

        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar); // it works!!!
            dialog.Text = "There is a change of location!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
        break;

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "I would be honored!";
            Link.l1 = "Keep an eye on the order and prosperity of the city, I will sometimes come to collect the toll.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "I changed my mind.";
            Link.l2.go = "Exit";
            NextDiag.TempNode = "Hired";
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
			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "What are your orders? Your last visit was " + FindRussianDaysString(iTemp) + " ago.";
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
            NextDiag.TempNode = "Gover_Main";
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
			dialog.Text = "My skills allow me to collect " + FindRussianMoneyString(iFortValue*iTax) + " a day. For " + FindRussianDaysString(iTemp) + " I've collected " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
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

			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Wonderful! Being a land rat is not my destiny.";
            Link.l8 = "That's good.";
            Link.l8.go = "exit_hire";
            NextDiag.TempNode = "Hired";
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
			dialog.Text = "I'm listening carefully.";
			Link.l1 = "It's about boarding.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "It's about your ship.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "I want you to come out from my squadron for a month and look for luck on your own.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Nothing yet.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "What do you want?";
			Link.l1 = "I want you not to board enemy ships. Take care of yourself and your team.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "I need you to board enemy ships.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "What do you want?";
			Link.l1 = "I want you not to change"+ NPCharSexPhrase(NPChar, "", "a") +" your ship after boarding. He's too valuable.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "When you board your enemies, see if there's a decent boat, then take it for yourself.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "That's right.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "It will be done.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "That's right.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "It will be done.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
		case "exit_spec":
			DialogExit();
		break;
		//Йока
		case "Yoko_meet":
			if (sti(pchar.reputation) > 70)
			{
				dialog.Text = "Greetings, Captain. I am Yoko Diaz, the free blade.";
				Link.l1 = "You look kind of shabby. Are you looking for a job?";
				Link.l1.go = "Yoko";
			}
			else
			{
				dialog.Text = "I don't think we have much to talk about, Captain.";
				Link.l1 = "I didn't really want to.";
				Link.l1.go = "exit_spec";
				NextDiag.TempNode = "Yoko_meet";
			}
		break;

		case "Yoko":
			dialog.Text = "I'm looking for it, but I'm hardly going to be of any use right now.";
			Link.l1 = "Why is that?";
			Link.l1.go = "Yoko_1";
		break;

		case "Yoko_1":
			ref locLoad = &locations[FindLocation("Shore_ship1")];
			string blade = GetGeneratedItem("Blade15");
			locLoad.box1.items.(blade) = 1;
			npchar.stortaid = blade;
			locLoad.box1.money = 7461;
			locLoad.box1.notouch = true;

			dialog.Text = "I went for a walk last night in a local tavern, and in the morning it turned out that all the money and my Storta were missing. If you can get them back, I'll join your team.";
			Link.l1 = "Find a specific sword on the big island... It's a bit of a challenge, but I can try.";
			Link.l1.go = "Yoko_2";
		break;

		case "Yoko_2":
			dialog.Text = "I'll be waiting, Captain.";
			Link.l1 = "See you later, Yoko!";
			Link.l1.go = "exit_spec";
			NextDiag.currentnode = "Yoko_wait";
			NextDiag.TempNode = "Yoko_wait";
		break;

		case "Yoko_wait":
			dialog.Text = "How's it going, Captain?";
			if (GetCharacterFreeItem(pchar,npchar.stortaid))
			{
				Link.l1 = "I managed to find your Storta. Here you go.";
				Link.l1.go = "Yoko_nowait";
			}
			Link.l2 = "Sorry, nothing yet.";
			Link.l2.go = "Yoko_2";
		break;

		case "Yoko_nowait":
			TakeNItems(pchar,npchar.stortaid,-1);
			GiveItem2Character(NPChar, npchar.stortaid);
			EquipCharacterbyItem(NPChar, npchar.stortaid);
			dialog.Text = "Thank you!";
			Link.l1 = "And now what?";
			Link.l1.go = "price";
			DeleteAttribute(NPChar, "Dialog.CurrentNode");
			NextDiag.TempNode = "OnceAgain";
		break;
		//Элен
		case "Helen_meet":
			if (pchar.name == "Charles" || pchar.name == "Mary")
			{
				if(npchar.id == "Beatrice")
				{
					dialog.text = "Do you have the nerve to come here after what happened? Get out of my sight before I cut you down!";
					link.l1 = "Sorry, Helen...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Helen_meet";
					break;
				}
			}
			if (sti(pchar.reputation) > 70)
			{
				if (CheckAttribute(npchar, "MetWhisper"))
				{
					dialog.Text = "I heard you've already become a captain. You're growing fast! We haven't introduced ourselves, have we? ";
				}
				else dialog.Text = "Greetings, Captain.";
				dialog.Text = dialog.Text + "I am Helen McArthur, by the will of fate I ended up on the shore and now I am looking for a job as an officer.";
				Link.l1 = "Were you a captain before? So I'm sure I have to figure out at least a little bit about everything, right?";
				Link.l1.go = "Helen";
			}
			else
			{
				dialog.Text = "I don't think we have much to talk about, Captain.";
				Link.l1 = "I didn't really want to.";
				Link.l1.go = "exit_spec";
				NextDiag.TempNode = "Helen_meet";
			}
		break;
		case "Helen":
			dialog.Text = "That's right. I understand both navigation and shooting.";
			Link.l1 = "If you're so good, why haven't you been hired yet?";
			Link.l1.go = "Helen_1";
		break;
		case "Helen_1":
			dialog.Text = "There is a scoundrel here in Puerto Principe, I don't even know why everyone tolerates him here. So he's spreading all sorts of dirty rumors about me, which is why no one wants to take me in.";
			Link.l1 = "Have you tried to plug his mouth with steel?";
			Link.l1.go = "Helen_2";
		break;
		case "Helen_2":
			dialog.Text = "Why do you think I'm still here? I've already tried, so he butchered me and spared me the first time.";
			Link.l1 = "And you want me to help you with this? And then will you join?";
			Link.l1.go = "Helen_3";
		break;
		case "Helen_3":
			dialog.Text = "Of course. Well, even with modest lifting.";
			Link.l1 = "I'll try to help you, Helen.";
			Link.l1.go = "Helen_wait";

			sld = GetCharacter(NPC_GenerateCharacter("HelenBastard", "pirate_1", "man", "man", 30, PIRATE, -1, false));
			sld.name 	= "Julius";
			sld.lastname = "Brin";
			SetSPECIAL(sld, 9,8,7,6,7,8,9);
			FantomMakeCoolFighter(sld, 30, 90, 50, "blade21", "pistol10", 300);
			SelAllPerksToNotPchar(sld);
			sld.location	= "PuertoPrincipe_port";
			sld.location.group = "goto";
			sld.location.locator = "goto7";
			sld.dialog.filename   = "Enc_OfficerGirl.c";
			sld.dialog.currentnode = "Helen_Bastard";
			sld.perks.list.BasicDefense = true;
			sld.perks.list.AdvancedDefense = true;
			sld.perks.list.SwordplayProfessional = true;
			sld.perks.list.CriticalHit = true;
			sld.perks.list.Gunman = true;
			sld.perks.list.GunProfessional = true;
			sld.perks.list.Energaiser = true;
			sld.perks.list.ByWorker = true;
			sld.perks.list.ShipEscape = true;
			sld.perks.list.Ciras = true;
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_SetImmortal(sld,true);
			DeleteAttribute(sld, "lifeDay");
			LAi_group_MoveCharacter(sld, "player");
			if(InterfaceStates.EnabledQuestsMarks)
			{
				sld.quest.questflag.model = "questionmarkB";
			}
			LAi_LoginInCaptureTown(sld, true);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", true);
			
			PChar.quest.Raznoe_Pomosh_Elen.win_condition.l1 = "locator";
			PChar.quest.Raznoe_Pomosh_Elen.win_condition.l1.location = "PuertoPrincipe_ExitTown";
			PChar.quest.Raznoe_Pomosh_Elen.win_condition.l1.locator_group = "reload";
			PChar.quest.Raznoe_Pomosh_Elen.win_condition.l1.locator = "reload2_back";
			PChar.quest.Raznoe_Pomosh_Elen.win_condition = "Raznoe_Pomosh_Elen";
			
			SetQuestHeader("PomoshElen");
			AddQuestRecord("PomoshElen", "1");
			AddQuestUserData("PomoshElen", "sSex", GetSexPhrase("", "a"));
		break;
		case "Helen_wait":
			if (!CheckAttribute(pchar, "HelenMet"))
			{
				dialog.Text = "I'll be waiting, Captain. Good luck!";
				pchar.HelenMet = true;
			}
			else
			{
				dialog.Text = "How's it going, Captain?";
			}
			Link.l1 = "Good. Bye, Helen.";
			Link.l1.go = "exit_spec";
			if (CheckAttribute(pchar, "HelenQuest"))
			{
				Link.l1 = "He's finished, no one will spread rumors about you anymore.";
				Link.l1.go = "Helen_nowait";
			}
			NextDiag.currentnode = "Helen_wait";
			NextDiag.TempNode = "Helen_wait";
		break;
		case "Helen_Bastard":
			dialog.Text = "Who are you? Another"+ GetSexPhrase("oh idiot", "oh fool") +" which want's to hire Helen as an officer? I'll tell you things about her that will make your hair stand on end.";
			Link.l1 = "I'm not interested. I'm offering you a deal. You get out of Puerto Principe in an hour or you'll be dead right here and now. What do you say?";
			Link.l1.go = "Helen_Bastard_2";
			UnmarkCharacter(npchar);
		break;

		case "Helen_Bastard_2":
			dialog.Text = "Dare you threaten me? Well, that's your problem. Defend yourself, Captain!";
			Link.l1 = "I thought that you wouldn't ask...";
			Link.l1.go = "Helen_Bastard_exit";
		break;
		case "Helen_Bastard_exit":
			pchar.HelenQuest = 1;
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			LAi_SetImmortal(NPChar,false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			chrDisableReloadToLocation = true;
			pchar.quest.HelenBastard.win_condition.l1 = "NPC_Death";
			pchar.quest.HelenBastard.win_condition.l1.character = "HelenBastard";
			pchar.quest.HelenBastard.win_condition = "OpenTheDoors";
			SetLocationCapturedState("PuertoPrincipe_town", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", false);
		break;
		case "Helen_nowait":
			dialog.Text = "Thank you, Captain! Now about my payment...";
			Link.l1 = "You're welcome! Well, how much is it?";
			Link.l1.go = "price";
			DeleteAttribute(pchar, "HelenMet");
			DeleteAttribute(pchar, "HelenQuest");
			DeleteAttribute(NPChar, "Dialog.CurrentNode");
			NextDiag.TempNode = "OnceAgain";
			AddQuestRecord("PomoshElen", "2");
			CloseQuestHeader("PomoshElen");
			pchar.questdata.PomoshElen = 1;
		break;
		//Анжелика
		case "Angellica_meet":
			if (startherotype == 4 || startherotype == 5)
			{
				if(npchar.id == "Angellica")
				{
					dialog.text = "Who is it we have here? Another fruit of my dad's irrepressible love for the fairer sex? I'm not in the mood to kill my relatives today. Go your own way!";
					link.l1 = "Oh, and we could make Father's dream come true together. Well, as you know, Angelica, goodbye.";
					link.l1.go = "exit";
					break;
				}
			}
			if (NPChar.alignment == "bad" && sti(pchar.reputation) < 30)
			{
				dialog.Text = "Hey, Captain! You have the honor to hire Nicholas Sharp's own daughter as your XO! If you get"+ GetSexPhrase("in", "yna") +"Of course!";
				Link.l1 = "What an arrogance! And are you sure that someone with such views will take you?";
				Link.l1.go = "Angellica";
			}
			else
			{
				dialog.Text = "I don't think we have much to talk about, Captain.";
				Link.l1 = "I didn't really want to.";
				Link.l1.go = "exit_spec";
				NextDiag.TempNode = "Angellica_meet";
			}
		break;
		case "Angellica":
			dialog.Text = "Believe me, there will be those who want to. Do you want to try it?";
			Link.l1 = "And what do you consider a sign of dignity?";
			Link.l1.go = "Angellica_2";
		break;

		case "Angellica_2":
			if (!CheckAttribute(pchar, "AngellicaDuelInfo")) {dialog.Text = "Defeat me in a duel and for a modest reward I will join you."; pchar.AngellicaDuelInfo = true;}
			else dialog.Text = "Well, have you decided?";
			Link.l1 = "I'm ready!";
			Link.l1.go = "Angellica_duel_exit";
			Link.l2 = "Maybe later.";
			Link.l2.go = "exit_spec";
			NextDiag.currentnode = "Angellica_2";
			NextDiag.TempNode = "Angellica_2";
		break;

		case "Angellica_duel_exit":
			DialogExit();
			NextDiag.currentnode = "Angellica_duel_won";
			NextDiag.TempNode = "Angellica_duel_won";
			ChangeCharacterAddressGroup(NPChar, "LeFransua_ExitTown", "enc01", "enc01_04");
			LAi_SetCheckMinHP(NPChar, 5, true, "AngellicaDialog");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DoQuestReloadToLocation("LeFransua_ExitTown", "reload", "reload3", "");
			chrDisableReloadToLocation = true;
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		case "Angellica_duel_won":
			dialog.Text = "Amazing! No one from the locals has ever managed to defeat me...";
			Link.l1 = "You made me sweat too.";
			Link.l1.go = "Angellica_duel_won_exit";
			LAi_SetHP(npchar, 150, 150);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "AngellicaDuelInfo");
			LAi_SetImmortal(NPChar,false);
			LAi_RemoveCheckMinHP (npchar);
		break;
		case "Angellica_duel_won_exit":
			DialogExit();
			LAi_SetWarriorType(NPChar);
			LAi_warrior_DialogEnable(NPChar, true);
			NextDiag.currentnode = "Angellica_duel_won_2";
			NextDiag.TempNode = "Angellica_duel_won_2";
		break;
		case "Angellica_duel_won_2":
			dialog.Text = "I'm ready to join you now, Captain.";
			Link.l1 = "And for how much?";
			Link.l1.go = "price";
			DeleteAttribute(NPChar, "Dialog.CurrentNode");
			NextDiag.TempNode = "OnceAgain";
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
