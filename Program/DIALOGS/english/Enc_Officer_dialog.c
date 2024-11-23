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
				link.l1 = RandPhraseSimple("Well, as you know...", "I'm not."+ GetSexPhrase("I was going to", "I was going to") +"hire you.");
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
			if (pchar.sex == "Skeleton")
			{
				dialog.text = LinkRandPhrase("Ic... Oh, what?", "I'm resting, don't bother me!", RandSwear()+ "I have a fly in my mug!");
				Link.l1 = "...";
    			Link.l1.go = "exit";
				DeleteAttribute(link, "l2");
				NextDiag.TempNode = "First time";
			}
		break;

		case "CitizenNotBlade":
			dialog.text = "Captain, what nonsense! Put away your weapons before you cause trouble!";
			link.l1 = LinkRandPhrase("Good.", "Okay.", "Don't worry, I'm already removing...");
			link.l1.go = "exit";
		break;

		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "Today we will go to sea again!";
				link.l2 = "Yeah... I'm glad too.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "I'll finish my drink now, Captain, and go on board. Don't worry, I'll be there before we sail.";
				Link.l1 = "All right. If you're late, I'll make you scrub the deck!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "What do you want, Captain?";
			if (NPChar.id == "James_Callow")
			{
				dialog.text = "Do you want to kick some ass? I'm at your disposal!";
			}
			if (NPChar.id == "Tichingitu")
			{
				dialog.text = "Tichingitu is listening to you, Captain "+pchar.name+"!";
			}
			if (NPChar.id == "Andreas_Fickler")
			{
				dialog.text = "What d-do you want, "+pchar.name+"?";
			}
			if (NPChar.sex == "skeleton" && PChar.sex == "skeleton")
			{
				dialog.text = "What do you want, my lord?";
			}
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "I have some orders for you.";
				Link.l2.go = "Companion_Tasks";
				break;
			}

			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
	            Link.l2 = "Listen to my order!";
	            Link.l2.go = "stay_follow";
            }

			//aw013 --> Найм на постоянку
			bool bOk = !CheckAttribute(PChar, "questTemp.MunityOfficerID") || PChar.questTemp.MunityOfficerID != NPChar.id;
			if (!bHalfImmortalPGG)
			{
				if (!CheckAttribute(NPChar, "OfficerWantToGo.DontGo"))
				{					
					if (bOk)
					{
						Link.l3contract = "I have a proposal for you.";
						Link.l3contract.go = "contract";
					}
				}
			}
			else
			{
				if (!CheckAttribute(pchar,"Option_ImmortalOfficers"))
				{
					pchar.Option_ImmortalOfficers = "0";
				}
				if (sti(pchar.Option_ImmortalOfficers) < makeint(GetCharacterSPECIAL(pchar,"Charisma")*2) && !CheckAttribute(npchar,"ImmortalOfficer"))
				{
					if (bOk)
					{
						Link.l3contract = "I have a proposal for you.";
						Link.l3contract.go = "contract";
					}
				}
			}
			//aw013 <-- Найм на постоянку
			
			//Расторжение контракта
			
			if (CheckAttribute(npchar, "ImmortalOfficer"))
			{
				Link.l6 = "I want to terminate the contract between us.";
				Link.l6.go = "cancelcontract1";
			}
			
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Give me a full report on the ship, " + GetStrSmallRegister(XI_ConvertString("treasurer")) + ".";
			    Link.l8.go = "QMASTER_1";
				if (NPChar.id == "Andreas_Fickler")
				{
					Link.l8 = "Give me a full report on the ship, Andreas.";
					Link.l8.go = "QMASTER_1";
				}
				
			    Link.l11 = "Let's discuss how many goods and items need to be purchased in stores.";
			    Link.l11.go = "TransferGoodsEnable";
			}

			if (npchar.id != "Sharp_Sibling" && npchar.id != "SharleMary")
			{
				Link.l4 = "Officer, I no longer need your services.";
				Link.l4.go = "AsYouWish";
				if (NPChar.sex == "skeleton" && PChar.sex == "skeleton")
				{
					Link.l4 = "You failed me, kinsman! Get out of my sight!";
					Link.l4.go = "exit_fire_1";
				}
			}

			for(iTemp=1; iTemp<=3; iTemp++) // Нужно, чтоб была свободная группа
			{
				attr = "Companion" + iTemp;
				if (CheckAttribute(PChar, "CompanionTravel."+(attr)+".ID"))
				{
					if (PChar.CompanionTravel.(attr).ID == NPChar.ID)
					{
						Link.l4 = "Get back to the squadron, Officer.";
						Link.l4.go = "CompanionTravel_ToSquadron";
					}
				}
			}

			// приколы -->
			if (PChar.sex == "woman" && !CheckAttribute(pchar, "questTemp.MainHeroWoman"))
			{//Запускаем счётчик для отката
				pchar.questTemp.MainHeroWoman = true;
				SaveCurrentQuestDateParam("pchar.questTemp.MainHeroWomanSex");
			}

            if (PChar.location == Get_My_Cabin() && npchar.id != "Sharp_Sibling" && GetQuestPastDayParam("pchar.questTemp.MainHeroWomanSex") >= 5)
            {
    			if (PChar.sex == "woman" && NPChar.sex == "man")
    			{
					Link.l3 = RandPhraseSimple("Since we're in the cabin, come on, maybe... Look, there's a bed here too... so soft...",
	                                           "Look at the big bed in my cabin. Don't you want to share it with me?");
	                if (drand(70) < sti(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) || CheckAttribute(npchar, "devoted"))
	                {
	                    Link.l3.go = "Love_Sex_Yes";
	                }
	                else
	                {
	                    Link.l3.go = "Love_Sex";
	                }
                }
            }

			if (PChar.location == Get_My_Cabin() && npchar.id != "Sharp_Sibling")
            {
    			if (PChar.sex != "woman" && NPChar.sex == "woman")
    			{
					Link.l3 = RandPhraseSimple("Since we're in the cabin, come on, maybe... Look, there's a bed here too... so soft...",
	                                           "Look at the big bed in my cabin. Don't you want to share it with me?");
	                if (sti(pchar.GenQuest.BrothelCount) > 4+rand(3))
	                {
	                    Link.l3.go = "Man_Love_Sex_Yes";
	                }
	                else
	                {
	                    Link.l3.go = "Man_Love_Sex";
	                }
                }
                if (!CheckAttribute(pchar, "questTemp.FUNY_SHIP_FIND") && NPChar.sex == "woman" && GetCharacterItem(PChar, "mineral4") >= 25)
                {
                    Link.l4 = "Look what an interesting collection I have gathered!";
            		Link.l4.go = "FUNY_SHIP_1";
                }
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
							Link.l11 = "I want to appoint you as the manager of the plantation, which is located near the colony '" + PChar.ColonyBuilding.ColonyName + "' and it belongs to her.";
							Link.l11.go = "PlantationCommander_Hire";
						}
					}
				}
			}
			/*
			if(npchar.id == "Mechanic1")
			{
				if (CheckCharacterItem(pchar, "pistolcolt") || CheckCharacterItem(pchar, "pistol7shotgun"))
				{
					Link.lcraftMechanic = "Mechanic, I have a question for you, just about your specialty.";
					Link.lcraftMechanic.go = "mechanic_craft_ammo";
				}
				if (CheckAttribute(pchar, "craftingAmmo"))
				{
					Link.lcraftMechanic = "How are you doing? Did you manage to make something?";
					Link.lcraftMechanic.go = "mechanic_craft_ammo_finish";
				}
			}*/
			if (CheckAttribute(pchar, "WhisperPGG") && npchar.id == pchar.WhisperPGG)
			{
				if (CheckAttribute(pchar, "CabinHelp"))
				{
					if(Pchar.CabinHelp == true)
					{
						Link.WhisperCabinHelp = "I no longer want you to accompany me to the cabins.";
						Link.WhisperCabinHelp.go = "WhisperCabinHelp";
					}
					else
					{
						Link.WhisperCabinHelp = "I want you to help me in the cabins.";
						Link.WhisperCabinHelp.go = "WhisperCabinHelp";
					}
				}
				if(GetCharacterItem(npchar, "pistol7shotgun") >= 1)
				{
					Link.WhisperWeapons = "You have an unusual weapon. May I take a look?";
					Link.WhisperWeapons.go = "WhisperWeapons";
				}

			}
			if(npchar.id == "W_chinaman" && CheckAttribute(pchar, "Whisper.GiveChinaSword") && CheckCharacterItem(pchar, "blade_china"))
			{
				Link.wChinaSword = "Look what I have for you. It wasn't easy, but I still got your sword.";
				Link.wChinaSword.go = "w_give_china_sword";
			}
            Link.l12 = "Nothing. At ease.";
            Link.l12.go = "Exit";
			if (NPChar.id == "Andreas_Fickler")
			{
				Link.l12 = "Calm down, Andreas. Keep counting the money.";
				Link.l12.go = "Exit";
			}
        break;

		case "FUNY_SHIP_1":
		    dialog.text = "Oh, the horror! Captain, take this away from me, such an unbearable stench... Do you believe in all this nonsense of the old legend about getting an invincible fighter?";
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

		case "WhisperCabinHelp":
			dialog.text = "Agreed.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
			pchar.CabinHelp = !sti(pchar.CabinHelp);
		break;

		case "WhisperWeapons":
			dialog.text = "You can take my sword if you want. But I won't trust anyone with the shotgun, I had to do too much to get it back, you know. And I don't think anyone but me will figure out how to use it.";
            Link.l2 = "I see.";
            Link.l2.go = "exit";
			Link.l1 = "I see. Are you using any special ammunition for it?";
            Link.l1.go = "WhisperWeapons_1";
		break;
		case "WhisperWeapons_1":
			dialog.text = "yeah. You can hardly buy these anywhere in the Caribbean, so I make them myself. It doesn't work out much, but I think I'll get better at it over time and be able to do more.";
            Link.l2 = "I see.";
            Link.l2.go = "exit";
		break;

		case "w_give_china_sword":
			dialog.text = "I can't believe my eyes... It's really him, the sword of my family. I have nothing to offer you in return, except my eternal devotion. If you trust me to protect you, I will protect your life before mine.";
			TakeItemFromCharacter(pchar, "blade_china");
			if (pchar.equip.blade == "blade_china")
			{
				RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			}
			LAi_SetHP(npchar, 100.0 + LAi_GetCharacterMaxHP(npchar), 100.0 + LAi_GetCharacterMaxHP(npchar));
			AddBonusEnergyToCharacter(npchar, 50);
			GiveItem2Character(npchar, "blade_china");
			EquipCharacterByItem(npchar, "blade_china");
			npchar.Skill.Sailing    = sti(npchar.Skill.Sailing) + 20;
			if (sti(npchar.Skill.Sailing) > 100) npchar.Skill.Sailing = 100;
			npchar.Skill.FencingHeavy  = sti(npchar.Skill.FencingHeavy) + 20;
			if (sti(npchar.Skill.FencingHeavy) > 100) npchar.Skill.FencingHeavy = 100;
			npchar.perks.FreePoints_self = sti(npchar.perks.FreePoints_self) + 1;
			npchar.perks.FreePoints_ship = sti(npchar.perks.FreePoints_ship) + 2;
			npchar.rank = sti(npchar.rank) + 5;
			npchar.perks.list.AgileMan = "1";
			ApplayNewSkill(npchar, "AgileMan", 0);
			npchar.devoted = true;
			DeleteAttribute(pchar, "Whisper.GiveChinaSword")
            link.l1 = "Loyalty is enough for me. Okay, I'll leave you alone with your 'toy'.";
			link.l1.go = "exit";
		break;

		case "mechanic_craft_ammo_finish":
		    dialog.text = "Don't rush me, Captain. I told you when I was done.";
            link.l1 = "Okay, I'm sorry. I just can't wait to shoot already.";
			link.l1.go = "exit";
			if (GetQuestPastDayParam("pchar.questTemp.craftingAmmo") >= sti(pchar.ammoCraftDays))
			{
				dialog.text = "You bet. Please take it away. I made 50 copies. Watch out, don't use it all up at once.";
				link.l1 = "Thank you. You're a genius!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "craftingAmmo");
				switch(pchar.ammoCrafttype)
				{
					case "shotgun":
						TakeNItems(Pchar, "12_gauge", 50);
					break;
					case "colt":
						TakeNItems(Pchar, "GunCap_colt", 50);
						TakeNItems(Pchar, "shotgun_cartridge", 50);
					break;
					case "both":
						TakeNItems(Pchar, "12_gauge", 50);
						TakeNItems(Pchar, "GunCap_colt", 50);
						TakeNItems(Pchar, "shotgun_cartridge", 50);
					break;
				}
			}
        break;
		case "mechanic_craft_ammo":
			if (!CheckAttribute(npchar, "ammoCraftedOnce"))
			{
				dialog.text = "Really? You've intrigued me, Captain.";
				link.l1 = "The fact is that I own a certain device - a weapon. It works properly, but special ammunition is needed to use it. Would it be difficult for you to make them?";
				link.l1.go = "mechanic_craft_ammo_1";
			}
			else
			{
				dialog.text = "Do you want me to make you ammunition again?";
				link.l1 = "You're reading my mind.";
				link.l1.go = "mechanic_craft_ammo_1";
			}
        break;
		case "mechanic_craft_ammo_1":
			if (!CheckAttribute(npchar, "ammoCraftedOnce"))
			{
				dialog.text = "Hmm... May I take a look at your device?";
			}
			else
			{
				dialog.text = "Please remind me, what kind of device do you have there?";
			}
			link.l1 = "You know, forget it.";
			link.l1.go = "exit";
			if (!CheckCharacterItem(pchar, "pistolcolt") && CheckCharacterItem(pchar, "pistol7shotgun"))
			{
				pchar.ammoCrafttype = "shotgun";
				link.l2 = "(Show shotgun)";
				link.l2.go = "mechanic_craft_ammo_3";
			}
			if (CheckCharacterItem(pchar, "pistolcolt") && !CheckCharacterItem(pchar, "pistol7shotgun"))
			{
				pchar.ammoCrafttype = "colt";
				link.l2 = "(Show revolver)";
				link.l2.go = "mechanic_craft_ammo_3";
			}
			if (CheckCharacterItem(pchar, "pistolcolt") && CheckCharacterItem(pchar, "pistol7shotgun"))
			{
				pchar.ammoCrafttype = "both";
				link.l2 = "(Show him a shotgun and a revolver)";
				link.l2.go = "mechanic_craft_ammo_3";
			}
        break;
		case "mechanic_craft_ammo_3":
			pchar.ammoCrafPrice = 50000;
			pchar.ammoCraftDays = 14;
			string sDays = " days.";
			if (pchar.ammoCrafttype == "both")
			{
				pchar.ammoCraftPrice = 100000;
				pchar.ammoCraftDays = 21;
				sDays = "day.";
			}
			string sTemp = "I'll take it" + pchar.ammoCraftPrice + " piastres for the job. Everything will be ready in about " + pchar.ammoCraftDays + sDays;
		    if (!CheckAttribute(npchar, "ammoCraftedOnce"))
			{
				dialog.text = "A curious mechanism. Well, let me take a closer look\nThat's a very interesting device you have there, Captain! Yes, I think I can make a weapon that would fit here. But, you know, it's going to take time and money for stuff, and it's also going to cost me. " + sTemp;
			}
			else
			{
				dialog.text = "Yeah, I remember now " + sTemp;
			}
			if (sti(pchar.money)>=sti(pchar.ammoCraftPrice))
			{
				link.l1 = "In that case, get to work. Here's the money.";
				link.l1.go = "mechanic_craft_ammo_4";
			}
			link.l2 = "I don't have the money for such expenses right now. We'll talk about it another time.";
			link.l2.go = "exit";
			npchar.ammoCraftedOnce = true;
        break;
		case "mechanic_craft_ammo_4":
			AddMoneyToCharacter(pchar, -sti(pchar.ammoCraftPrice));
			pchar.craftingAmmo = true;
			SaveCurrentQuestDateParam("pchar.questTemp.craftingAmmo");
			dialog.text = "Yes, Captain!";
			link.l1 = "I will look forward to your results.";
			link.l1.go = "exit";
        break;

		case "Love_Sex_Yes":
		    dialog.text = RandPhraseSimple("Perhaps it's a sin to refuse such a beauty.",
                                           "I'm willing to do anything for you, Captain.");
            link.l1 = RandPhraseSimple("Oh, yeah!", "Clever girl! If you try hard, maybe you'll get a bonus this month.");
			link.l1.go = "Love_Sex_Yes_2";
        break;

        case "Love_Sex_Yes_2":
            AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterExpToSkill(pchar, "Fencing", -50);// утрахала
            AddCharacterExpToSkill(pchar, "Pistol", -50);
            AddCharacterHealth(pchar, 10);
			SaveCurrentQuestDateParam("pchar.questTemp.MainHeroWomanSex");
   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "After_sex";
			DialogExit();
        break;

        case "After_sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("You're on top as always, Captain.",
                                           "Captain, I hope you enjoyed everything, I tried my best.");
            link.l1 = RandPhraseSimple("Yes, we had a great time.", "Yeah. Now let's get back to our business.");
			link.l1.go = "exit";
        break;

        case "Love_Sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("What!!!?? Captain, have you been ashore or in a brothel for a long time?", "I don't understand what you're talking about.");
            link.l1 = RandPhraseSimple("Well, think about it... You're so handsome, and you're under my command.", "Well, I can't go to a brothel when you're at my side!");
			link.l1.go = "Love_Sex_2";
			link.l2 = RandPhraseSimple("I'm sorry, handsome, it was very difficult not to offer..", "Eh.. Okay, never mind...");
			link.l2.go = "exit";
        break;

        case "Love_Sex_2":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Captain! Control yourself! Or call your sailors for this!", "The fact that I am an officer and nominally obey you, Captain, does not mean anything!");
            link.l1 = RandPhraseSimple("Baby, don't resist. I can't hold myself back anymore. Let's go...", "I am your captain! And I command you!");
			link.l1.go = "Love_Sex_3";
			link.l2 = RandPhraseSimple("I'm sorry, kid, it was very hard not to offer..", "Eh... Okay, never mind...");
			link.l2.go = "exit";
        break;

        case "Love_Sex_3":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("That's it! You will be responsible for this! And right now!", "Roll around with you? Well, now let's see who is capable of what..");
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

		//Мужской ГГ
		case "Man_Love_Sex_Yes":
		    dialog.text = RandPhraseSimple("Perhaps you can give in to such a ladies' man.",
                                           "Well, it's better than wasting money on street girls.");
            link.l1 = RandPhraseSimple("Oh, yeah!", "Smart girl, I can't go to a brothel when I have a paw like you by my side!");
			link.l1.go = "Man_Love_Sex_Yes_2";
        break;

        case "Man_Love_Sex_Yes_2":
            pchar.GenQuest.BrothelCount = 0;
            AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterExpToSkill(pchar, "Fencing", -50);// утрахала
            AddCharacterExpToSkill(pchar, "Pistol", -50);
            AddCharacterHealth(pchar, 10);

   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "Man_After_sex";
			DialogExit();
        break;

        case "Man_After_sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Hmm... strange, I thought you were capable of more...",
                                           "Captain, now you can think with your head again, and not... ? Let's get back to our business.");
            link.l1 = RandPhraseSimple("How do you talk to a senior!", "I can do a lot if I collect my thoughts.");
			link.l1.go = "exit";
        break;

        case "Man_Love_Sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("What!!!?? Captain, have you been ashore or in a brothel for a long time?", "I don't know what you're talking about.");
            link.l1 = RandPhraseSimple("Well, think about it yourself... You're such a beauty, and you're also under my command.", "Well, I can't go to a brothel when you're at my side!");
			link.l1.go = "Man_Love_Sex_2";
			link.l2 = RandPhraseSimple("I'm sorry, baby, it was very difficult not to offer...", "Eh... Okay, never mind...");
			link.l2.go = "exit";
        break;

        case "Man_Love_Sex_2":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Captain! Control yourself! Or call your sailors for this!", "The fact that I am an officer and nominally obey you, Captain, does not mean anything!");
            link.l1 = RandPhraseSimple("Baby, don't resist. I can't hold myself back anymore. Let's go...", "I am your captain! And I command you!");
			link.l1.go = "Man_Love_Sex_3";
			link.l2 = RandPhraseSimple("I'm sorry, baby, it was very difficult not to offer..", "Eh... Okay, never mind...");
			link.l2.go = "exit";
        break;

        case "Man_Love_Sex_3":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("That's it! You will answer for this! And right now!", "Roll around with you? Well, now let's see who is capable of what..");
            link.l1 = "Uh... what are you talking about?";
			link.l1.go = "Man_Love_Sex_4";
        break;

        case "Man_Love_Sex_4":
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
			npchar.SystemInfo.ChangePIRATES = true; //пояснение касательно респека. нужно ставить в функцию ниже реф на офицера
			LaunchCharacter(npchar); //в некоторых случаях он не совпадает с персонажем, с которым идёт диалог, так что нужно внимание
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

		//aw013 --> Найм на постоянку
		case "contract":
			dialog.text = "I'm listening to you carefully, Captain.";
			Link.l1 = "You are a good officer and you are completely suitable for me. I want to suggest that you join my contract service.";
			Link.l1.go = "contract2";
		break;

		case "contract2":
			dialog.text = "Thank you for the kind words, Captain. And what are the terms of the contract?";
			Link.l1 = "A large one-time payment. Better equipment, "+ NPCharSexPhrase(NPChar, "by myself", "by myself") +"you know. The contract period is 10 years. You can quit at the end of the term, and if everything suits both of us, we'll extend it further.";
			Link.l1.go = "contract3";
		break;

		case "contract3":
			NPChar.contractMoney = makeint(sti(NPChar.rank)*MOD_SKILL_ENEMY_RATE*3*1000);
			dialog.text = "It's a tempting offer, you can't say anything. Earn a little money for a quiet old age. What about small lifts for the permanent staff?";
			if (sti(Pchar.money) >= sti(NPChar.contractMoney))
			{
				Link.l1 = "I have nothing against it, is " + sti(NPChar.contractMoney) + " gold enough for your hands right now?";
				Link.l1.go = "contract4";
			}
			Link.l2 = "I don't mind, but let's get back to this conversation later.";
			Link.l2.go = "Exit";
		break;

		case "contract4":
			dialog.text = "Quite, Captain. I agree.";
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
			Link.l1 = "That's great! Agreed.";
			Link.l1.go = "Exit";
		break;
		
		case "cancelcontract1":
			dialog.text = "Quite unexpected, Captain. And what am I " + NPCharSexPhrase(NPChar, "guilty?", "guilty?");
			Link.l1 = "Forget it, I was wrong " + GetSexPhrase("Xia.", "Las.");
			Link.l1.go = "Exit";
			Link.l2 = "I'm not satisfied with your skills.";
			Link.l2.go = "cancelcontract2";
		break;
			
		case "cancelcontract2":
			NPChar.contractMoney = makeint(sti(NPChar.rank)*MOD_SKILL_ENEMY_RATE*3*1000);
			dialog.text = "So, well, if you pay the penalty under the contract, then I will have no complaints.";
			if (sti(Pchar.money) >= sti(NPChar.contractMoney))
			{
				Link.l1 = "Whatever you say, " + sti(NPChar.contractMoney) + "is gold enough for your hands right now?";
				Link.l1.go = "cancelcontract3";
			}
			Link.l2 = "I'm having cash problems right now, we'll come back to this conversation later.";
			Link.l2.go = "Exit";
		break;
			
		case "cancelcontract3":
			dialog.text = "Quite, Captain. I agree" + NPCharSexPhrase(NPChar, "En.", "on.");
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
		
		//aw013 <-- Найм на постоянку
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("Captain, here's the deal... In general, I ask for my resignation. It's time for me to get married a long time ago, anchor in a quiet harbor and have kids, but I won't warm up all the places for myself. So in my old age, there will be no one to serve water.", "Captain, give me a resignation, otherwise I've been traveling all over the world for so many years, and I haven't really seen anything. I want to taste another life, drop the anchor, and look at the world with different eyes.", "Captain, naval service is, of course, not bad - it is profitable and adventures are different, but you need to think about yourself. Anchor in a quiet harbor, buy a house and have kids. You're going to let me go."), LinkRandPhrase("Captain, I'm sorry, of course, but these regimes with watches and disciplines are so boring that it's just sickening. I want to go on a free life for a while. I understand that you will not wait, so I ask for my resignation.", "Captain, I just happened to have a boat here. One day, after all, you need to get your own business. Let them go free - let them resign.", "Captain, I've been offered a place in the port here. I've been dreaming of dropping anchor and starting a family for a long time. Resign-when another opportunity comes up."), LinkRandPhrase("Captain, I'm sick of the sea already. Doctors say it's an idiosyncrasy. Let me go, for Christ's sake, otherwise someday I won't stand it - I'll throw a cigar overboard.", "Captain, I guess it's time for me to settle down and find a quieter place. Stray bullets began to scare, before each boarding, I pray to the Savior that I save my life... And the innocents are dreaming at night - they all beg for mercy... Resign, be a man.", "Captain, old wounds are aching - there is no strength, and the recent concussion does not give life. A little more and you will kick me out yourself, then who will take me into service? Resign - I'll get better and I'll look for a quieter place."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("Hmm, everyone will run away like that... But I won't force you - go, if you've decided.", "Well, the reason is clear. Sooner or later it all ends. Go... Don't forget that you offended me.", "What kind of people! He tries to sneak away at the most inopportune moment!.. Go, what kind of soldier are you now..."), LinkRandPhrase("It's hard to believe. There's something you're not telling me... Well, anyway, I didn't take the oath on the Bible from you, so walk with a clear conscience.", "I didn't expect to hear it from you! So much time side by side... I could have suspected anyone, but not you. I really don't like to be disappointed in people... Pack your things and don't get in my way anymore.", "This is a serious matter - I will not hold back... Although I will miss you very much."));
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("Yeah, you see how it turned out... And I was counting on you... Well, since the decision has been made, let's part ways. Here is "+sti(NPChar.rank)*250+" gold for faithful service. And don't hold a grudge if you ever offended" + GetSexPhrase(".", "Ah."), "Well, I don't hold a grudge and I don't remember anything bad. Once you've decided, go. Take "+sti(NPChar.rank)*250+" gold coins on the track. It will always come in handy.", "I see... It was bound to happen sooner or later. I present "+sti(NPChar.rank)*250+" gold coins to you for the arrangement of personal life. Yes, improve your health, naval service is not sugar - it leaves a trace for life ...");
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("So that's how it is. Do you even realize that now your departure is like a knife in my back? I can't let you go now-don't even ask or think about it.", "That's the news! It is customary to warn about such things in advance. So forget about your personal life for now. When the time comes, I'll do it myself. I'll offer you my resignation.", "No resignations. I have every person on my account. I cannot, out of a personal whim of everyone, throw a team around. Serve until I decide.");
			Link.l3.go = "WantToGo_Stay";
		break;

		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "Thank you, Captain! What an unexpected generosity. I have some of your things left here, would you like to return them?";
			Link.l1 = "Yes, I suppose so... It's not easy to find a good blade right now...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "No need. Keep it for yourself in memory of the service under my command...";
			Link.l2.go = "WantToGo_free";
		break;
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("But how is that? Slaves, and those are written off on the shore. Also I am not a slave, and I have the right to decide your fate!", "Captain, haven't I earned right to decide my own fate for all my diligence?");
			Link.l1 = LinkRandPhrase("I see you can't be held back that easily. What about financial support? Such a thing is always useful - and to organize a nest in a quiet harbor, and to improve your health...", "Okay, let's have a different conversation. How much money you need to stay?", "You're right about that. What about a one-time cash allowance?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(
				RandPhraseSimple("Uh no, you're wrong about that... While you were wiping pants in the tavern, you could decide your fate yourself... But as soon as you got on my ship my ship - I decide for you.", "Hmm, this is a serious statement. I guess you don't remember how I found you in a stinking tavern with no money in his pocket. Yes, you can't even show gold from afar - it immediately turns into rum, and there you can 'decide your fate'."),
				LinkRandPhrase("As long as you're in my service, I'll make the decisions. Please return to your duties if you don't want to completely ruin your relationship with me!", "Hmm. This is a serious statement. But you haven't worked out all the money paid to you yet. Therefore, I have the right to regard your demarche as an attempt at blackmail.", "I see...And let's remember the ship's charter. The second point reads: 'If anyone decides to run... May he be landed on a deserted shore with a flask of gunpowder, a flask of water, one gun and bullets.'How do you like this twist?'"));
			Link.l2.go = "WantToGo_Stay_force";
		break;

	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Well, that makes a difference. "+sti(NPChar.rank)*500+" gold coins and I'm staying.", "Well, perhaps for "+sti(NPChar.rank)*500+" gold coins I would stay.", "Hmm, since this conversation started, then for "+sti(NPChar.rank)*500+" I'd stay.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("That's settled.", "All right. Although I could be more modest...", "What appetites you have! Well, since I promised - here you go.");
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("Well, you're bending it. For such money, you can hire two officers. It's probably easier to let you go.", "You value yourself highly. I think I'll let you go free. But you'll see - it's not smeared with honey either.", "I'm not ready to pay such money. You can go, but don't ask to go back - I don't forgive betrayal.");
		Link.l2.go = "WantToGo_free";
	break;

	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "Well, if that's the case, I'm staying... But know that I am acting against my will...";
		Link.l1 = LinkRandPhrase("That's good. Go back to your duties, and we'll continue this conversation later.", "Get back on board now. And next time, think carefully before you ask for my resignation.", "That's it. Service is service, and there is nothing to indulge your fantasies.");
		Link.l1.go = "exit";
	break;

	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		if (NPChar.sex != "woman")
		{
			NPChar.greeting = "Gr_Officer";
		}
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;
            Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
		break;

		case "WantToGo_free":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				Diag.CurrentNode = Diag.TempNode;
				DialogExit();
				break;
			}
			//navy <--
            Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "WantToGo_free_Yet":
            Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase ("You won't believe it, Captain - it's a load off my mind.", "Thank you, Captain, for not holding me back. I want to try something else in my life.", "Eh, I'll get used to freedom. I'm only now realizing how disgusted the Navy service is.");
		Link.l1 = RandPhraseSimple("Well, I wish you every success...", "Take a walk. Your service is over.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--

	// пассажир возмущён игроком и сваливает -->
	case "WantToRemove":
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("Captain, I don't want to rape my conscience and engage in robbery for profit.", "Captain, I no longer wish to take part in your outrages. I'm not a butcher, I'm an officer.", "Captain, your bandit ways make it impossible for me to stay in the team any longer."), LinkRandPhrase("Captain, I must admit that my hiring you was an unfortunate mistake. I am absolutely not ready to sacrifice my honest name for money.", "Captain, thugs from all over the New World have gathered on your ship, it is disgusting for a decent person to enter the cabin. I don't want to serve in such a team anymore.", "Captain, you have recruited some crooks into the team - there is no one to say a kind word to. The soul does not lie at all for such a service.")) + "Goodbye.";
			Link.l1 = "What?!! I have a warship, not a noble boarding house! You can go to hell!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "I've known that you will leave for a long time... This kind of service is not for you. But I have nothing to reproach you with. Here "+sti(NPChar.rank)*500+" gold coins for you, they will be useful until you find a job you like.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Yeah. So that's how we sang. Does the share that was paid to you from each robbery not burn your hands? Or will you go straight from here to a monastery to make up for your sins? Then put in a good word for us! Ah ha ha ha...", "Hmm, this is a serious statement. And where did your virgin conscience look when we robbed merchants together? What are you going to wash it with? You'll probably run to scribble a denunciation so that you can hang out on the gallows in good company...", "Wow, how bravo!.. I guess you don't remember how I found you in a stinking tavern with no money in his pocket. Yes, you, as an officer, are worthless, and there is also free bread.");
			Link.l3.go = "WantToGo_stop";
			}
			else
			{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Captain, I don't like your games of nobility at all. I will not break my habits for your peace of mind. Goodbye.", "Captain, I can no longer remain in your service. So much time was wasted - it was already possible to make a fortune by simple privateering. I'm leaving.", "Captain, I am sick of such colleagues. At least don't go into the mess - there are only mama's boys, there's no one to drink rum with. I'm leaving."), LinkRandPhrase("Captain, I'm a combat officer, and your ship is more like a cargo barge. This kind of service is not for me, I'm leaving. Goodbye.", "Captain, you have recruited some clean-minded people into the team - there is no one to drink rum with and say a word. My soul does not lie at all for such a service, so goodbye.", "Captain, I thought I was serving a real corsair. And what are we doing? It's all charity! I don't want to waste time and I'm leaving."));
			Link.l1 = RandPhraseSimple("Well, yes. With your attitude to the service, sooner or later it had to happen. Well, I won't hold you back.", "Such a statement did not come as a surprise to me. I have not been satisfied with your attitude towards the service for a long time.") + "Have a nice day.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "I knew that you will leave... This kind of service is not for you. But I have nothing to reproach you with. Here "+sti(NPChar.rank)*500+" gold coins. They will come in handy while you're looking for a new place.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Hmm. This is a serious statement. But you haven't earned all the money you've been paid yet. Therefore, I have the right to regard your demarche as an escape.", "I see...And let's remember the ship's charter. The second point reads: 'If anyone decides to run... May he be landed on a deserted shore with a flask of gunpowder, a flask of water, one gun and bullets.'How do you like this twist?'");
			Link.l3.go = "WantToGo_stop";
		}
		break;

		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("Don't try to insult me! I, like everyone else, serve for money, but I have the right to choose a job I like.", "I am a free man! And I have the right to change jobs when I see fit.", "I am not a slave to serve just for food, so my conscience is clear! But I'm not going to continue to participate in this robbery!");
				Link.l1 = "Uh no, that's where you're wrong... While you were slobbering over a mug in the tavern, yes, you could choose any job... But after he boarded my ship, that's it... The path back is only with the ball on the neck, hehe... Yes, I still have to trim my tongue, so that in the next world I don't accidentally blurt out what I shouldn't...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";
				}
				Link.l2 = "Well, okay. Go... But God forbid that you should meet me on the open sea. I swear you'll regret not staying by my side.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("Don't try to intimidate me! I, like everyone else, serve for money, and I have the right to choose a job I like.", "I am a free man! And I have the right to change jobs when I see fit.", "I am not your slave! And I do not intend to continue to vegetate on your trough!");
				Link.l1 = "Uh no, that's where you're wrong... While you were slobbering over a mug in the tavern, yes, you could choose any job... But after he boarded my ship, that's it... The path back is only with the ball on the neck, hehe... Yes, to trim the tongue, so that in the next world you don't accidentally blurt out what you shouldn't...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";
				}
				Link.l2 = "Well, okay. Go... But God forbid that you should meet me on the open sea. I swear you'll regret not staying by my side.";
				Link.l2.go = "exit_fire_5";
			}
		break;

		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("If things take this turn, then I will stay - I simply have no other choice. But know that I'm not doing this of my own free will...", "Well, if that's the case, I'm staying... But know that I am acting against my will...");
			Link.l1 = RandPhraseSimple("That's fine... Serve till I decide to kick you out.", "That's good - serve for now... And I'll decide when to kick you myself.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведёт к бегству
		break;

		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar, "You will never force me to change my mind! The wrong one was attacked!", "You probably think you can scare a combat officer?! It's not the first time I've looked death in the eye. And for that matter, it's better to die in a fair fight than during a dastardly robbery!");
			Link.l1 = NPCharRepPhrase(NPChar, "Well... everyone chooses their own destiny. I hope you prayed before visiting me.", "If I had known who are you when I picked you up in a tavern under the reef and penniless - I swear I'd rather let you die. And now it's not too late to arrange it...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar, "Well, go on, since you need freedom so much. But keep in mind - you won't get any recommendations from me.", "Well, okay. Go... But God forbid you should get caught by me in the open sea. I swear you'll regret not staying by my side.");
			Link.l2.go = "exit_fire_5";
		break;

		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -1);
			dialog.text = NPCharRepPhrase(NPChar, "Just don't scare me! Which one of your youngsters decides to raise his voice against me?! If I were captain, they'd be rich already! And you have divorced... Benevolence, and now you're trembling so that the team doesn't defect to my side?!", "Drop your manners, you can't scare me! Goodbye.");
			Link.l1 = NPCharRepPhrase(NPChar, "No, buddy, you won't live to see the scaffold. Such luxury is not for you...", "Not so fast, buddy, I haven't paid you yet...");
			Link.l1.go = "Get_out_fight";
		break;
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			if (!CheckAttribute(PChar, "questTemp.MunityOfficerID") || PChar.questTemp.MunityOfficerID != NPChar.id)
			{
				Pchar.questTemp.MunityOfficerID = Npchar.id;
				Pchar.questTemp.MunityOfficerID.begin = "1";
				SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
			}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущён игроком и сваливает <--

		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar, RandSwear() + "I am the best "+ XI_ConvertString(Npchar.quest.officertype) + " in these waters. " + Npchar.quest.officertype_2 + "I can do you a favor by joining the service.",
                                    "Well, they say I'm not a bad " + XI_ConvertString(Npchar.quest.officertype) + ". " + Npchar.quest.officertype_2 + "Take me in your team, Captain, see for yourself.");
			Link.l1 = "How much do you want?";
			Link.l1.go = "price";
			Link.l2 = "And what do you think of yourself as a specialist?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "Sorry, I already have a " + XI_ConvertString(Npchar.quest.officertype) + " in my team.";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, Captain, half the garrison is chasing you here. Now is clearly not the time to join your team!", "Do you propose to break into the ship with a fight? No, another time, Cap...");
				link.l1 = RandPhraseSimple("Well, as you know...", "I wan't goingg to hire you.");
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Have you changed your mind, Captain? Did you decide that new " + XI_ConvertString(Npchar.quest.officertype) + " would be great for you?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Perhaps so. How much do you want?";
                Link.l1.go = "price";
			}
			Link.l2 = "How will you be in business?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "I have a complete set. Have a nice stay.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "I think you and I will agree on " + Npchar.quest.OfficerPrice + " piastres.";
			Link.l1 = "Don't you want too much?";
			Link.l1.go = "trade";
			Link.l2 = "I agree. Consider yourself enrolled in the team.";
			Link.l2.go = "hire";
			Link.l3 = "You're not worth the money. Goodbye.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "All right... Perhaps I am ready to agree even to " + Npchar.quest.OfficerPrice + " piastres. How's it going?";
				Link.l1 = "That's better. You're accepted.";
				Link.l1.go = "hire";
				Link.l2 = "I still think it's too much. Goodbye.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Alas, Captain, I'm worth exactly what I asked for. If it's too expensive for you, look for someone else.";
				Link.l1 = "All right, I agree. I'm taking you.";
				Link.l1.go = "hire";
				Link.l2 = "That's what I'm going to do. Have a nice day.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			if(makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				pchar.questTemp.officercount = sti(pchar.questTemp.officercount) + 1;
				if(sti(pchar.questTemp.officercount) >= 3) UnlockAchievement("officers", 1);
				if(sti(pchar.questTemp.officercount) >= 6) UnlockAchievement("officers", 2);
				if(sti(pchar.questTemp.officercount) >= 10) UnlockAchievement("officers", 3);

				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Thank you, Captain. You won't regret giving me this gold.";
				Link.l1 = "I want to believe it.";
				Link.l1.go = "Exit_hire";
			}
			else
			{
				dialog.text = "Hey, it looks like you're having cash problems! I'm sorry, Captain, but I don't work on credit.";
				Link.l1 = "Oh, damn it!";
				Link.l1.go = "Exit";
			}
		break;

		case "OnboardSoon":
			Diag.TempNode = "OnboardSoon";
			dialog.text = "I'll finish my drink now, Captain, and go on board. Don't worry, I'll be there before we sail.";
			Link.l1 = "All right. If you're late, I'll make you scrub the deck!";
			Link.l1.go = "Exit";
		break;

        case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Captain, but we don't have a ship!";
				Link.l1 = "Thanks for reminding me...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
            dialog.text = "Maximum rat activity on ship " +
            FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
            "% from good's quantity. For "+GetCrewQuantity(PChar) + " sailors we need  " + makeint((GetCrewQuantity(PChar)+6) / 10) + " food per day. This is without taking into account the slaves being transported.";
            Link.l1 = "Thank you.";
            Link.l1.go = "Exit";
			if (NPChar.id == "Andreas_Fickler")
			{
				dialog.text = "Maximum activity of r-r-rats on ship is " +
				FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
				"% from good's quantity. For "+GetCrewQuantity(PChar) + " sailors are n-needed " + makeint((GetCrewQuantity(PChar)+6) / 10) + " f-food per day. That's without taking into account the t-t-transported slaves.";
				Link.l1 = "Thank you, my stuttering friend.";
				Link.l1.go = "Exit";
			}
            Diag.TempNode = "Hired";
        break;

        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "What are your orders?";
			if (NPChar.id == "Andreas_Fickler")
			{
				dialog.text = "W-what are your orders?";
			}
            Link.l1 = "Stay here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
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
		break;

		case "AboardRestriction":
			npchar.AboardRestriction = true;
			dialog.text = "Yes, Captain! I will not participate in boarding until you allow it again.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
		break;

		case "AboardAllowed":
			DeleteAttribute(npchar, "AboardRestriction");
			dialog.text = "Yes, Captain! I will participate in boarding from now on.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
		break;

		case "CheckMushket":
			if (findsubstr(npchar.model.animation, "man" , 0) != -1 || findsubstr(npchar.model.animation, "YokoDias" , 0) != -1 || findsubstr(npchar.model.animation, "Milenace" , 0) != -1)
			{
				if (findsubstr(npchar.model.animation, "man2_ab" , 0) == -1)	Npchar.CanTakeMushket = true;
			}

			if (CheckAttribute(npchar, "CanTakeMushket"))
			{
				dialog.text = "Yes, Captain!";
				Link.l1 = "Great, then we'll pick something up for you if possible.";
				Link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Better not, Captain. I'll shoot you again inadvertently.";
				Link.l1 = "It's a pity, it's a pity...";
				Link.l1.go = "exit";
			}
		break;

		case "TargetDistance":
			dialog.text = "Which one exactly, Captain? Specify in meters, but not more than 20.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Captain, what a bad tone!";
				link.l1 = "Sorry, I made a mistake...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "I will stand still, not moving anywhere. Is that okay with you, Captain?";
				link.l1 = "Yes, that's exactly what is required of you.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "I thought I said that I can't stay more than 20 meters from the target.";
				link.l1 = "Okay, keep a distance of 20 meters.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "I understand the task, I take note.";
			link.l1 = "Good.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Captain, although I do not understand the reason for such a statement, let's return to this issue on shore. Or did you decide to just throw me overboard?";
					Link.l1 = "Hmm... no, I didn't mean it. Stay until we get to the port.";
					Link.l1.go = "Exit";
					break;
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation) >= 40 && makeint(NPChar.reputation) < 40) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("That's the news!", "What kind of joy is that?!", "Why is this all of a sudden?!"), RandPhraseSimple("Captain, are you out of your mind? To report such news out of the blue!", "Wow! And what's wrong with me?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("I've decided to restore order in the squadron. And since I don't like your relationship with your colleagues, ", "Your advantages were not as good as they were signed at the time of hiring, so", "There will be no thugs and crooks in my team! Therefore, "), LinkRandPhrase("I've learned that you're sneaking rum and getting the team drunk, thereby weakening their morale. Therefore, ", "I'm damn tired of your robber ways, I'm not going to endure them endlessly. So, ", "You constantly spend time in the mess playing cards or dice, distracting other officers from duty. It can't go on indefinitely, so")) + " pack up and leave the ship.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;
			}
			if (makeint(PChar.reputation) >= 40 && makeint(NPChar.reputation) >= 40) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("May I know the reasons for this decision?", "Surely such a decision has good reasons?"), RandPhraseSimple("Please explain yourself, Captain.", "Very unexpected. But I would like to know the reasons."));
				if (NPChar.id == "Andreas_Fickler")
				{
					dialog.text = RandPhraseSimple(RandPhraseSimple("M-may I know the p-p-reasons for this decision?", "N-n-surely such a decision has good p-reasons?"), RandPhraseSimple("P-p-please explain yourself, Captain.", "Very n-unexpected. B-but I would like to know the reasons."));
				}
				Link.l1 = RandPhraseSimple(LinkRandPhrase("I am absolutely not satisfied with your attitude to your duties.", "Unfortunately, you didn't make a good officer, and probably won't...", "You are a good officer, and you served well, but here our paths diverge. And don't ask me why."), LinkRandPhrase("I warned you that the passion for rum will ruin you. How can I trust a man in battle who can't get a saber into a scabbard?", "To put it bluntly, you didn't make a sailor... I think you will achieve more on the shore.", "I haven't been satisfied with your qualifications for a long time, but now I finally found a worthy replacement."));
				Link.l1.go = "Get_out_A2";
				break;
			}
			if (makeint(PChar.reputation) < 40 && makeint(NPChar.reputation) >= 40) // злодей против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Hmm. May I know the reasons?", "This is a serious statement. May I ask what exactly is wrong with you?"), RandPhraseSimple("Please explain yourself, Captain.", "I hope there are good reasons for such a statement?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("I'm not satisfied with your qualifications at all, so", "Unfortunately, you didn't make a good officer. So, ", "I'm damn tired of your noble impulses. I don't intend to put up with them endlessly, so, "), LinkRandPhrase("I've heard rumors that you're the one encouraging the team to disobey. There will be no riots on my ship! And you don't have to thank me for not throwing you out earlier... So, ", "Your noble principles do you credit, but they run counter to the rogue life of a free privateer. So, ", "I am absolutely not satisfied with your attitude to your duties. Therefore, ")) + "pack up and leave the ship.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}
				break;

			}
			if (makeint(PChar.reputation) < 40 && makeint(NPChar.reputation) < 40) // злодей против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Captain, I did not expect such a turn in any way! Can you explain what happened?", "Captain, what kind of fly has bitten you?!", "What do you mean, Captain?!"), RandPhraseSimple("How is that, Captain?! Even the sutra everything was fine, but here it's on you...", "Wow! I think you can find a few words to explain?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("You are a rare incompetent and incompetent - you should have been a cabin boy on a coaster. I've been patient for too long alread. So, ", "You haven't satisfied me for a long time, but now I'm finally found a worthy replacement. So, ", "I've learned that you're sneaking rum and getting the team drunk, thereby weakening their morale. Therefore, "), LinkRandPhrase("When you were hired, you were saying that you couldn't find a better officer in the entire fleet, but in fact you turned out to be an ordinary loafer, so", "I warned you that your drinking will end badly. Why do I have to do everything for you myself? So, ", "Instead of doing duty, you're constantly stuck in the mess playing cards or dice. I hope you didn't think that this could go on indefinitely? So, ")) + "pack up and get out.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;

		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("That's how it is! Well, it's up to you. But keep in mind: I will not come back to you. You will ask for more...", "I must admit, I don't like your games of nobility either. So goodbye...", "Well, to hell with you! Stay with your sycophants. Too much for me - a 'hero'!"), LinkRandPhrase("Yes, I have never liked you, not a ship, but a cargo barge. They have built a noble boarding house...", "Yes, I myself am sick of such colleagues. At least don't go into the cabin, as a selection - only mama's boys...", "All right, Captain, have it your way. But, God knows, I'm clean astern..."));
			Link.l1 = "Wait. I can't leave the ship without an officer right now. But we'll come back to this conversation later.";
			Link.l1.go = "exit_bad";
			Link.l2 = "So go with God.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Don't get angry. I got a severance package in amount of "+sti(NPChar.rank)*500+" gold for you. I hope this will clear up all the questions.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("Allow me! What does 'abandon ship' mean?! I didn't put my head under buckshot so that you could throw me out whenever you want!", "Ha! 'Abandon ship'! Do you think I'm going to let myself be thrown out like a kitten?!", "Take it easy, Captain, this is not how things are solved in a serious company. I'm not going to be treated like a rookie.");
			Link.l1 = "Okay, stay. But only until I find a worthy replacement." ;
			Link.l1.go = "exit_bad";
			Link.l2 = "I repeat, your service is over. You can pack your things.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Don't get angry. I got a severance package in amount of "+sti(NPChar.rank)*500+" gold for you. I hope this will clear up all the questions.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("Yes, I am not eager to stay with you. But I'm not going to leave the ship without compensation!", "Yes, now I won't stay on your trough myself. Just be so kind as to pay compensation first!") + " "+sti(NPChar.rank)*1000+"gold, and we'll forget about each other.";
			Link.l1 = "I overreacted... Accept my apologies, and return to your post.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "Which money can we talk about if you regularly received your share? This all looks pretty much like extortion!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "Okay. Hand over the equipment and you'll get what you're asking for.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "Well, that's a completely different matter. Goodbye!";
			Link.l1 = "I hope our paths don't cross again.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Consider this compensation for moral costs. I won't let anyone treat me like that! And whoever dares, he will regret it very much!", "This is not extortion, but compensation for wasted time! And I will get it, no matter what it costs me!", "I have spent too much time in the service of so"+ GetSexPhrase("wow clean-cut", "the cleanest girl") +"like you. During this time, it was possible to get rich by robbing merchants. Now I want to compensate for the lost profit.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "Okay. Here's your money... Now get out of here!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "You're forgetting yourself! I won't let any idiots raise their voices at me!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterReputation(pchar, 1);
			OfficersReaction("good");
			dialog.text = "Come on, come on, Captain! Show me what it's like - up against a serious opponent!";
			Link.l1 = "God knows, I didn't want that!";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			dialog.text = "Well, that's a completely different matter. Goodbye!";
			Link.l1 = "I hope our paths don't cross again.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Well, then it's not fate. Goodbye, Captain, don't mention it too much...", "It's a pity, Captain. But, God knows, I tried. Goodbye.", "Well, Captain, you will not please!.. Have a nice stay."), LinkRandPhrase("It's a pity, Captain. I really enjoyed serving with you.", "That's how it happens... But I don't hold a grudge, goodbye.", "You're being unfair to me, Captain. But I respect your decision. Goodbye."));
			if (NPChar.id == "Andreas_Fickler")
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Well, then it's not fate. G-g-goodbye, C-captain, don't mention it too much...", "It's a pity, C-captain. But, God knows, I tried. P-p-goodbye.", "Well, Captain, you're not going to be pleased!.. Have a nice stay."), LinkRandPhrase("It's a pity, C-captain. I-I really enjoyed serving with you.", "That's how it happens... B-b-but I don't hold a grudge, p-goodbye.", "You're not being very nice to me, Captain. But I respect your decision. P-goodbye."));
			}
			Link.l1 = "Wait, I've changed my mind. Let's get back to this conversation later.";
			Link.l1.go = "exit_good";
			Link.l2 = "Don't worry. Good luck to you...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Wait... I've equipped you well. I need to return the things - I need to equip a bunch of them...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Wait... I don't want to let you go empty-handed. Take "+sti(NPChar.rank)*500+" gold coins, they'll come in handy while you're looking for a new job.";
				Link.l4.go = "Im_kind_A2";
			}
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Yes, what is it about, of course take it...";
			Link.l1 = "I knew that you will understand me correctly...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "Thank you, Captain! What an unexpected generosity. I have some of your things left here, would you like to return them?";
			Link.l1 = "Yes, I suppose so... It's not easy to find a good blade right now...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "No need. Keep it for yourself in memory of the service under my command...";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Well, that's up to you. But keep in mind: I won't come back to you, even if I have to starve to death.", "I must admit, I don't like your gangster ways either. So it was bound to happen sooner or later... And there is no need to invent any reasons.", "Well, stay with your thugs. It's a shame for a decent person to enter the mess on your ship. They started a brothel, God forgive me!"), LinkRandPhrase("I must admit, I also have no heart for such a service. They recruited some crooks into the team - there is no one to say a kind word to.", "Yes, if you treat the personnel like that, everyone will run away from you. You won't have to invent any reasons.", "I am comforted by the fact that our dislike is mutual. Have a nice stay."));
			Link.l1 = "Wait. This is not a good time to write you off. But all claims remain valid.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Go on, go on. I'll do without your moralizing.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Wait. I'll give you "+sti(NPChar.rank)*500+" gold. Otherwise you'll die under the fence, and then I'll answer to God.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("And thanks for that. Goodbye...", "Thank you for your understanding. Have a nice stay.", "Now we're even. Have a nice day...");
			Link.l1 = "I knew that you will understand me correctly...";
			Link.l1.go = "exit_fire_3";
		break;

		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("But, Captain, in this scenario, I remain completely broke. You don't want to send me from the ship directly to the porch, do you?", "You're being unfair to me, Captain. But I'm willing to forget the grudge if I get a decent compensation.", "And this is your thanks for all my battle wounds? I think there is no way to do without monetary compensation.");
			Link.l1 = "Okay, I've changed my mind. Stay for now, but we'll get back to this conversation later.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Well, you don't have to worry about that. Here's "+sti(NPChar.rank)*500+" gold. I think that's enough for the first time.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "I'll give you the money. But thanks to me, you're well equipped-the stuff needs to be returned.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "Wow! But what about the share you regularly receive?! I knew that it will all end up whining and begging for handouts.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "I knew you'd say that, but you can only pick up the equipment when I get "+sti(NPChar.rank)*1000+" gold. Or you'll have to take it off the corpse.";
			Link.l1 = "Okay, keep your money.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "Are you out of your mind?! To demand such a sum for what I gave you for free! It seems that such a low quality as greed has finally prevailed over your pretended benefactor.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "You don't dare insult me! I may not be the best in the Navy, but I'm still a combat officer. And I will make you respect me, even such ignorant like you!";
			Link.l1 = "If it's not clear to you yet, then I repeat - you don't have to beg, you won't get anything anyway.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			dialog.text = "Well, I'll get satisfaction anyway!!";
			Link.l1 = "Yes, it's a challenge! Well, as you wish...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("That's how it always is! You give your whole soul in the service, and to you - bang, and without severance pay!", "What kind of attack is this?! You don't have time to get hired, as you are immediately kneeled in the ass. I don't know who to put the candle on...", "Here they are! This is the third layoff in a year- and all on Mondays. Don't show yourself to these captains with a hangover!"), LinkRandPhrase("Well, okay, so be it. Just God forbid we meet again.", "Well, that's up to you. But keep in mind: you won't find a better officer anyway.", "All right, Captain, have it your way. But, God knows, my stern is clear..."));
			Link.l1 = "Wait. This is not a good time to write you off. But all claims remain valid.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Stomp, stomp. And thank God I'm in a good mood today.", "Come on, come on. You're still an officer, like a bullet out of shit.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Wait. I got "+sti(NPChar.rank)*500+" gold for you. Otherwise you'll die under the fence, and then I'll answer to God.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Wait... I've equipped you well. The things should be returned.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Thanks a lot, Captain! That's how they respected...", "Thank you for your understanding. Have a nice stay.", "Now we're even. Have a nice day...");
			Link.l1 = "Have a nice day. Just don't leave them all in the nearest tavern.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("Now you're also taking away your equipment! Damn it all to hell! By God, I'm going to become a fisherman...", "I see you've decided to strip me clean. Well, take it. One road now is to the porch...", "Thank you very much! Now they've decided to clean it up too. Oh, fate!.. Take it away, damn it all...");
				Link.l1 = "Come on, come on. You're still an officer, like a bullet out of shit.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else
			{
				dialog.text = RandPhraseSimple("Have it your way, Captain, just give it to me first."+sti(NPChar.rank)*1000+"gold. We will consider this compensation for moral costs.", "All right. That's the only thing I want to get "+sti(NPChar.rank)*1000+" gold coins as compensation for hard service.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "What a rascal! Okay, keep your money.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "Are you crazy?! Dare you ask for so much money for what I do myself!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "Ah ha! I was joking! How can I throw out an old friend like a leaky cap!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterReputation(pchar, -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Well, then you won't get anything! I won't move until I hear my gold ring!";
			Link.l1 = RandPhraseSimple("Now you will hear my blade ringing!", "So you're going to be carried away feet first!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			if(CheckAttribute(Npchar, "HalfImmortal")) DeleteAttribute(Npchar, "HalfImmortal");
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			Npchar.SaveItemsForDead = true;
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterReputation(pchar, -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -1);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_2":	//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_3":	//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_4":	//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_5":	//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar)
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";
			dialog.text = "Well, what else? We seem to have already decided everything! I will never set foot on your ship again.";
			Link.l1 = RandPhraseSimple("Go on, go on. The loss is small.", "Go on, go on. I won't hold you back.");
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2";
			dialog.text = "Is there anything else, Captain? It seemed to me that we had already decided everything...";
			Link.l1 = "No, nothing. I just wanted to say goodbye...";
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3";
			dialog.text = "Captain, all issues have been resolved, claims have been made. You don't want to say you've changed your mind after all this.";
			Link.l1 = "Go on, go on. The loss is small.";
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4";
			dialog.text = "Captain, what other questions can there be? To tell you the truth, I am very offended with you, and I have no desire to return...";
			Link.l1 = "Go on, go on. I need you painfully, you just dirty the deck.";
			Link.l1.go = "Exit";
		break;
        // boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "Yes, Captain!";
		    Link.l1 = "At ease.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
			if (NPChar.sex == "skeleton" && PChar.sex == "skeleton")
			{
				dialog.text = "I obey and obey, my lord!";
			}
	    break;
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "Yes, Captain!";
		    Link.l1 = "At ease.";
		    Link.l1.go = "Exit";
			if (NPChar.sex == "skeleton" && PChar.sex == "skeleton")
			{
				dialog.text = "I obey and obey, my lord!";
			}
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "I would be honored!";
            Link.l1 = "Keep an eye on the order and prosperity of the city, I will sometimes come to collect the toll.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "I've changed my mind.";
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
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("", "а"));
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
			dialog.Text = "I'm listening carefully.";
			Link.l1 = "It's about boarding.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "It's about your ship.";
			Link.l2.go = "Companion_TaskChange";
			// if(bBettaTestMode) // Только при бета-тесте
			// {
			    Link.l3 = "I want you to come out from my squadron for a month and look for luck on your own.";
			    Link.l3.go = "CompanionTravel";
			// }
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
			Link.l1 = "I want you not to change your ship after boarding. He's too valuable.";
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

		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Captain, I will not withdraw from your squadron, since you have already released three ships.";
					Link.l1 = "Yes, I guess you're right.";
					Link.l1.go = "exit";
				break;
			}

			dialog.Text = "No problem, Cap. Where should I go?";
			Link.l1 = "Go to the city...";
			Link.l1.go = "Travel_Towns";

			Link.l2 = "Go to the pirate settlement...";
			Link.l2.go = "TravelToPiratesTowns";

			Link.l3 = "Go to a desert island...";
			Link.l3.go = "TravelToNomanIslands";

			Link.l99 = "I've changed my mind. Nothing is needed.";
			Link.l99.go = "exit";
		break;

		case "Travel_Towns":
			dialog.Text = "Where will the meeting place be, Captain?";
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
			Link.l99 = "I've changed my mind. Nothing is needed.";
			Link.l99.go = "exit";
		break;

		case "TravelToPiratesTowns":
			dialog.Text = "Which one exactly?";
				Link.l1 = "Pirate Settlement";
				Link.l1.go = "TravelToPirates";
				Link.l2 = "Le Francois";
				Link.l2.go = "TravelToLeFransua";
				Link.l3 = "La Vega";
				Link.l3.go = "TravelToLaVega";
				Link.l4 = "Puerto Principe";
				Link.l4.go = "TravelToPuertoPrincipe";
				Link.l6 = "You know, stay for now, I've changed my mind.";
				Link.l6.go = "exit";
		break;
		case "TravelToNomanIslands":
			dialog.Text = "Which one exactly?";
				Link.l1 = "Cayman";
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
			dialog.Text = "So, you want me to go to "+XI_ConvertString("Caiman" + "Gen")+", captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I've changed my mind.";
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
			dialog.Text = "So, you want me to go to "+XI_ConvertString("StLucia" + "Gen")+", captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I've changed my mind.";
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
			dialog.Text = "So, you want me to go to "+XI_ConvertString("Dominica" + "Gen")+", captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I've changed my mind.";
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
			dialog.Text = "So, you want me to go to "+XI_ConvertString("Terks" + "Gen")+", captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I've changed my mind.";
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
			dialog.Text = "So, you want me to go to "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I've changed my mind.";
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
			dialog.Text = "So, you want me to go to "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I've changed my mind.";
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
			dialog.Text = "So, you want me to go to "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I've changed my mind.";
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
			dialog.Text = "So, you want me to go to "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I've changed my mind.";
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
			dialog.Text = "So, you want me to go to "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", captain?";
			Link.l1 = "Yes, that's right.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I've changed my mind.";
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
			dialog.Text = "You have chosen a colony" + XI_ConvertString("Colony" + rCTravel.ToColonyID + "Gen") + ", captain?";
			Link.l1 = "Yes, it is her.";
			Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "No, I've changed my mind.";
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
				Link.l1 = "Yes, you're right. The journey will wait until...";
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
			dialog.Text = "Everything is clear. To get to " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + " I need " + sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) + " days. What should I do upon arrival?";
			if (sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) == 1)
			{
			dialog.Text = "Everything is clear. " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + " is just around the corner, I'll get there today. What should I do there?";
			}
			Link.l1 = "Wait for me at the raid for a month.";
			Link.l1.go = "CompanionTravel_PrepareStart_2";
			Link.l2 = "You know, I've changed my mind. Stay with me for now...";
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
			"Don't forget about our meeting at " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Dat") + ".");
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
								DeleteAttribute(PChar, "CompanionTravel."+(attr));//фикс - удаляем всю ветку
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
				Link.l1 = "Yes, " + npchar.name + ", it was released. Welcome to the squadron.";
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
			Link.l2 = "I've changed my mind.";
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
			Link.l3 = "Just checking on you, " + npchar.name + ".";
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
			dialog.Text = "With a functioning store, you can ensure the automatic purchase of essential goods, so that the citizens living in the colony and guarding the colony garrison can receive medicines and food in a timely manner.\nContact our merchant if you are interested.";
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
			Link.l2 = "No, I've changed my mind.";
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
			Link.l1 = "Hmm, well, good. See you later.";
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
			Link.l3 = "Just checking on you, " + npchar.name + ".";
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
			Link.l2 = "No, I've changed my mind.";
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
			Link.l2 = "I've changed my mind.";
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
			Link.l2 = "No, I've changed my mind.";
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
			Link.l2 = "I've changed my mind.";
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
				sBaseComplete = "the ships are fully equipped weekly and are always ready for battle. At the moment, the amount needed for this is " + GetCostForBaseCompletationAllGuards() + " piastres.";
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
			dialog.Text = "Coastal ships will be inspected every week, and those ships currently guarding the coastline will be augmented with the missing ammunition and relief items, and the crew will be replenished.\nBut for all of this to work, it's going to have to be spent on some of the costs that depend on the ships that you complete. For example, it will now be necessary to pay " + GetCostForBaseCompletationAllGuards() + " piastres a week from the treasury of the colony. If this amount is missing, then, unfortunately, there will be nothing to complete. What do you say?";
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
			Link.l2 = "No, I've changed my mind.";
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
			Link.l2 = "I want to know the prices that are required to secure the hire.";
			Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_Costs";
			Link.l3 = "It is necessary to review the facilities where garrison recruitment is provided.";
			Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_Set";
			Link.l4 = "No, I've changed my mind.";
			Link.l4.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Info":
			dialog.Text = "I can myself recruit a garrison team so that our colony and its buildings can always fight the enemy and pacify the rebellious citizens and slaves. But, as you can imagine, it's going to cost a lot more than a regular hire in the archipelago's taverns. Each time the garrison will be manned according to the current configuration of garrisons.\nGarrison can be hired for all objects - this is our colony, plantation and mines. Each time in the treasury of the colony must be the amount that allows you to hire a garrison for a certain object. If this amount is not in the treasury, the hiring, accordingly, will not happen.";
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
			dialog.Text = "At the moment, the price of securing the hiring of the colony's garrison is taking into account the staffing of the garrison: " + ColonyGuardingGetCostForObject("Colony", false) + " gold, for full filling without taking into account staffing: " + ColonyGuardingGetCostForObject("Colony", true) + "gold.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Good.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Mines":
			dialog.Text = "At the moment, the price of hiring a garrison of mines is based on the staffing of the garrison: " + ColonyGuardingGetCostForObject("Mines", false) + " gold, for full filling without taking into account staffing: " + ColonyGuardingGetCostForObject("Mines", true) + "gold.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Good.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Plantation":
			dialog.Text = "At the moment, the price of securing the hiring of the plantation garrison is taking into account the staffing of the garrison: " + ColonyGuardingGetCostForObject("Plantation", false) + " gold, for full filling without taking into account staffing: " + ColonyGuardingGetCostForObject("Plantation", true) + "gold.";
			Link.l1 = LinkRandPhrase("Thank you.", "I see.", "Good.");
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
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure.");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_2";
			link.l2 = LinkRandPhrase("Mm... Perhaps you're right - it's worth thinking more.", "I've changed my mind.", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_2":
			PChar.Colony.Guardians.Colony.AutoCrewHire = true;
			dialog.text = "All right, Captain! I will deal with this issue from today.";
			link.l1 = "That's good.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_1":
			dialog.text = "Are you sure, Captain?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure.");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_2";
			link.l2 = LinkRandPhrase("Mm... Perhaps you're right - it's worth thinking more.", "I've changed my mind.", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_2":
			PChar.Colony.Guardians.Mines.AutoCrewHire = true;
			dialog.text = "All right, Captain! I will deal with this issue from today.";
			link.l1 = "That's good.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_1":
			dialog.text = "Are you sure, Captain?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure.");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_2";
			link.l2 = LinkRandPhrase("Mm... Perhaps you're right - it's worth thinking more.", "I've changed my mind.", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_2":
			PChar.Colony.Guardians.Plantation.AutoCrewHire = true;
			dialog.text = "All right, Captain! I will deal with this issue from today.";
			link.l1 = "That's good.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_1":
			dialog.text = "Do you really want to suspend the hiring of a team for the colony's garrison?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure.");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_2";
			link.l2 = LinkRandPhrase("Stand down!", "I've probably changed my mind...", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_2":
			PChar.Colony.Guardians.Colony.AutoCrewHire = false;
			dialog.text = "As you wish, Captain.";
			link.l1 = LinkRandPhrase("Thank you.", "I see.", "Good.");
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_1":
			dialog.text = "Do you really want to suspend hiring a team for the mine garrison?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure.");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_2";
			link.l2 = LinkRandPhrase("Stand down!", "I've probably changed my mind...", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_2":
			PChar.Colony.Guardians.Mines.AutoCrewHire = false;
			dialog.text = "As you wish, Captain.";
			link.l1 = LinkRandPhrase("Thank you.", "I see.", "Good.");
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_1":
			dialog.text = "Do you really want to suspend hiring a team for the plantation garrison?";
			link.l1 = LinkRandPhrase("Yes.", "Absolutely.", "Of course I'm sure.");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_2";
			link.l2 = LinkRandPhrase("Stand down!", "I've probably changed my mind...", "Uh... No, I'm not sure.");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_2":
			PChar.Colony.Guardians.Plantation.AutoCrewHire = false;
			dialog.text = "As you wish, Captain.";
			link.l1 = LinkRandPhrase("Thank you.", "I see.", "Good.");
			link.l1.go = "exit";
		break;
		// <-- Самостоятельное плавание компаньона
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
