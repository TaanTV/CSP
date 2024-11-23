void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;

	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;

	// Церковный квест № 2 -->
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- Церковный квест № 2

	string sColony;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DeleteAttribute(npchar, "pricevalue");
			DeleteAttribute(npchar, "pricev");
			DeleteAttribute(npchar, "itemtype");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToSmuggler(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
		break;

		case "Smuggling_exit":
			PChar.CurrentSmuggler = npchar.id;
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));

			DialogExit();
		break;

		case "First time":
		UpdateSmugglers();
		//ОЗГ
			if (CheckAttribute(pchar, "contrabandmoneyback") && sti(pchar.contrabandmoneyback) >= 1000000+(MOD_SKILL_ENEMY_RATE*1000000) && !CheckCharacterPerk(pchar, "UnlimitedContra"))
			{
				dialog.text = "Captain, you have proved to be a truly useful customer for the entire smuggling business. From now on, you will be provided with the best deal terms.";
				link.l1 = "Thank you for your trust.";
				link.l1.go = "First time";
				Log_info("The Avid Smuggler perk has been unlocked");
				SetCharacterPerk(pchar, "UnlimitedContra");
				NPChar.quest.meeting = "1";
				break;
			}
			int iCondottiereRankReq = 1;
			if (!bQuestsRank) iCondottiereRankReq = 10;	//Если стоит галочка, то убрать требования рангов у квестов
			if (!CheckAttribute(pchar, "questTemp.Headhunter") && sti(pchar.rank) >= iCondottiereRankReq)	//Квест Кондотьер
			{
				dialog.text = "Captain, I would like to talk to you about a matter. As I see, you are a new person in the Archipelago, and you are not yet known in the Brethren... Perhaps you are exactly the one, who is needed.";
				link.l1 = "Hmm... Interesting. State what your case is.";
				link.l1.go = "Give_vector";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "What do you want, Captain? I do not know your name, and I cannot tell you mine.";
				Link.l1 = "I'm captain " + GetFullName(pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				if(CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "There will be no deals today. All the bays are full of patrol, the governor is looking for cargo, which is captain of the patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "allegedly confiscated it from some pirate and hid it.";
						link.l1 = "And where is captain himself?" + pchar.GenQuest.CaptainComission.Name + "?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "There won't be any deals today.";
						link.l1 = "I see.";
						link.l1.go = "exit";
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "There won't be any deals today.";
					link.l1 = "I see.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "What have you brought this time, Captain?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Speak quickly, "+ GetSexPhrase("buddy", "girlfriend") +", what do you need? And then, you know, the pursuit of you!", "Don't delay, state the matter quickly! The soldiers are running after you, not up to long conversations, you know...");
				}
				if(FindFirstContrabandGoods(PChar) != -1)
				{
					Link.l1 = "I'm brought few items for sale.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "About the trip...";
				else
					Link.l2 = "I need to get somewhere.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "I have a 'special' item, I think you'll be curious. Take a look!";
						link.l3.go = "SM_ShipLetters_1";
					}
				}
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "I need to figure something out, buddy.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}

				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "Your colleague and my good friend from " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "He said you were aware of a case.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2

		    	////////////////////////////////////////////////////////
		    	//zagolski. начальный квест пирата
		    	if(CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "2" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
		    	{
			    	link.l4 = "Listen, I desperately need a hundred or two slaves. I don't know who to turn to anymore.";
			    	link.l4.go = "pirateStartQuest_Smuggler";
			    }

				if (CheckAttribute(pchar, "contratrade.time"))
				{
					if (pchar.contratrade.time != GetDataDay() && ChangeContrabandRelation(pchar, 0) > 5)
					{
						Link.l17 = "(softly) I heard that I can buy something interesting from you.";
						Link.l17.go = "Trade";
					}
				}
				if (!CheckAttribute(pchar, "contratrade.time") && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l17 = "(softly) I heard that I can buy something interesting from you.";
					Link.l17.go = "Trade";
				}
				if (CheckAttribute(pchar, "RimalieGood") && npchar.id == "PortSpein_Smuggler" && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l18 = "I would like to talk about a Musketeer living as a hermit on a nearby island.";
					Link.l18.go = "Rimalie";
				}

				Link.l7 = "Nothing. See you later.";
				Link.l7.go = "Exit";
			}
		break;

		case "Rimalie":
			if (!CheckAttribute(pchar, "RimalieWait"))
			{
				Dialog.Text = "Of course, I've heard of him. One of my colleagues got hurt because of him. He broke one deal and stole some of the goods while everyone was blinking.";
				Link.l1 = "Maybe I could make up for the losses because of his act?";
				Link.l1.go = "Rimalie_2";
			}
			else
			{
				Dialog.Text = "About him again...? 50,000 piastres right now. If you pay, we'll leave him alone.";
				if (sti(pchar.money) >= 50000)
				{
					Link.l1 = "Here you go.";
					Link.l1.go = "Rimalie_3";
				}
				Link.l2 = "I'll be back about it.";
				Link.l2.go = "exit";
			}
		break;

		case "Rimalie_2":
			if (ChangeContrabandRelation(pchar, 0) >= 70)
			{
				Dialog.Text = "You're a pretty respected customer for our organization and brought a lot of profit. For your sake, we are ready to make concessions and stop harassing him right now. Do you really need him that much? There are some pretty bad rumors about Rimbaud. Aren't you afraid?";
				Link.l1 = "For the sake of a good Musketeer officer, it's not a sin to take a risk. Thank you for your help!";
				Link.l1.go = "exit";
				pchar.RimalieDone = true;
				DeleteAttribute(pchar, "RimalieGood");
				DeleteAttribute(pchar, "RimalieWait");
			}
			else
			{
				pchar.RimalieWait = true;
				Dialog.Text = "For damages, we want... 50,000 piastres right now. If you pay, we'll leave him alone.";
				if (sti(pchar.money) >= 50000)
				{
					Link.l1 = "Here you go.";
					Link.l1.go = "Rimalie_3";
				}
				Link.l2 = "I'll be back about it.";
				Link.l2.go = "exit";
			}
		break;


		case "Rimalie_3":
			AddMoneyToCharacter(pchar,-50000);
			Dialog.Text = "It's a pleasure doing business with you. But do you really need him that much? There are some pretty bad rumors about Rimbaud. Aren't you afraid?";
			Link.l1 = "For the sake of a good Musketeer officer, it's not a sin to take a risk. See you later!";
			Link.l1.go = "exit";
			pchar.RimalieDone = true;
			DeleteAttribute(pchar, "RimalieGood");
			DeleteAttribute(pchar, "RimalieWait");
			AddQuestRecord("Rimalie", "2");
		break;

		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "In the basement of the fort, where else would he be? The captain can give the authorities the place where he hid the cargo at any moment, and then we will be left with a nose. So, until all this fuss settles down, don't even think about deals.";
				link.l1 = "Listen, you know every stone on the island. Don't you know captain's hiding place? " + pchar.GenQuest.CaptainComission.Name + "?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "In heaven, probably. He was recently executed along with his team. And the verdict did not say that the ship was pirated.";
				link.l1 = "And how are you sure that the ship belonged to pirates?";
				link.l1.go = "CapComission_2";
			}
		break;

		case "CapComission_2":
			dialog.text = "We watched that fight from the cliff until it got dark. It was clearly visible through the tube that " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name"))) + "under Black Roger. And then, about five hours later, we saw only a flash in the dark, as if the cell had gone off. During this time, it was quite possible to take the goods ashore.";
			link.l1 = "Don't you know where captain's hiding place is?" + pchar.GenQuest.CaptainComission.Name +"? You know every stone on the island.";
			link.l1.go = "CapComission_3";
		break;

		case "CapComission_3":
			dialog.text = "No. We are also looking for him, but not to please the governor...";
			link.l1 = "I see... Well, have a nice stay.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")));
		break;

		case "CapComission_4":
			dialog.text = "No. We're looking for him too, but not to please the governor, hehe...";
			link.l1 = "I see... Well, have a nice stay.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;

		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Why did you decide that? I'm an honest coaster. Look for another buyer.";
				link.l1 = "Thanks for that too....";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "How do I say it? Maybe your 'goods' will come in handy. Take it " + sti(pchar.questTemp.different.GiveShipLetters.price2) + "gold, and forget about it.";
					link.l1 = "Probably not.";
					link.l1.go = "SM_ShipLetters_2";
					link.l2 = "Yes, you guessed it, I'm already starting to forget!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "That's right! I'm not just curious anymore. I think if I pay you "+ sti(pchar.questTemp.different.GiveShipLetters.price3) +"gold, then you won't be at all curious about what's in these papers.";
						link.l1 = "Probably not.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Yes, you guessed it, I'm already starting to forget!";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "This is a chance to nail an impudent man! It's very, very curious. Let's do this: I'm paying you " + sti(pchar.questTemp.different.GiveShipLetters.price4) + ", and you pretend that you forgot documents on the table?";
						link.l1 = "Probably not.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Yes, you guessed it, I'm already starting to forget!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;

		case "SM_ShipLetters_2":
			dialog.text = "Well, well, don't make enemies.";
			link.l1 = "And don't forget to look back!";
			link.l1.go = "exit";
		break;

		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3));
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4));
				}
			}

			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{
				ChangeCharacterReputation(pchar, -1);
				OfficersReaction("bad");
			}
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "7");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "There will be no deals today. All the bays are full of patrol, the governor is looking for cargo, which is captain of the patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "allegedly confiscated it from some pirate and hid it.";
					link.l1 = "And where is captain himself?" + pchar.GenQuest.CaptainComission.Name + "?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "There won't be any deals today.";
					link.l1 = "I see.";
					link.l1.go = "exit";
					break;
				}
			}

			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "There won't be any deals today.";
				link.l1 = "I see.";
				link.l1.go = "exit";
				break;
			}

			Dialog.Text = "What can I do for you, Captain?";
			if(FindFirstContrabandGoods(PChar) != -1)
			{
				Link.l1 = "I want to sell something.";
				Link.l1.go = "Meeting_1";
			}
			Link.l2 = "I need to get somewhere.";
			Link.l2.go = "Travel";
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "I need to figure something out, buddy.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}

			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "Your colleague and my good friend from " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "He said you were aware of a case.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			////////////////////////////////////////////////////////
			//zagolski. начальный квест пирата
			if(CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "2" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
			{
				link.l4 = "Listen, I desperately need a hundred or two slaves. I don't know who to turn to anymore.";
				link.l4.go = "pirateStartQuest_Smuggler";
			}

            if (CheckAttribute(pchar, "contratrade.time"))
			{
				if (pchar.contratrade.time != GetDataDay() && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l17 = "(Softly) I heard that I can buy something interesting from you.";
					Link.l17.go = "Trade";
				}
			}
			if (!CheckAttribute(pchar, "contratrade.time") && ChangeContrabandRelation(pchar, 0) > 5)
			{
				Link.l17 = "(Softly) I heard that I can buy something interesting from you.";
				Link.l17.go = "Trade";
			}
			if (CheckAttribute(pchar, "RimalieGood") && npchar.id == "PortSpein_Smuggler" && ChangeContrabandRelation(pchar, 0) > 5)
			{
				Link.l18 = "I would like to talk about a Musketeer living as a hermit on a nearby island.";
				Link.l18.go = "Rimalie";
			}

			Link.l5 = "Nothing. Good luck!";
			Link.l5.go = "Exit";
		break;

		////////////////////////////////////////////////////////
		//zagolski. начальный квест пирата
		case "pirateStartQuest_Smuggler":
		if (!CheckAttribute(pchar, "GenQuest.contraTravel.active") && !CheckAttribute(Pchar, "quest.Contraband.Active"))
		{
			dialog.text = "There is a great demand for slaves nowadays. For such cases, pirates are usually approached in a neighboring settlement.";
			link.l1 = "There are no slaves there, but my business is on fire. There's no time left at all.";
			link.l1.go = "pirateStartQuest_Smuggler_1";
		}
		else
		{
			dialog.text = "First, buddy, finish what you started. And then we'll talk about it.";
			link.l1 = "Got it.";
			link.l1.go = "exit";
		}
		break;
		case "pirateStartQuest_Smuggler_1":
			dialog.text = "Damn me if I don't know who your customer is! Well, this rascal will get his party with a substantial margin if he decides to lead me by the nose.";
			link.l1 = "I do not know who you are talking about. My customer is sitting on another island, so I'm in a hurry while the wind is fair.";
			link.l1.go = "pirateStartQuest_Smuggler_2";
		break;
		case "pirateStartQuest_Smuggler_2":
			dialog.text = "And how many slaves do you need?";
			link.l1 = "We need 100 slaves. I'll pay you well!";
			link.l1.go = "pirateStartQuest_Smuggler_3";
		break;
		case "pirateStartQuest_Smuggler_3":
			dialog.text = "It will cost you 30,000 piastres, 300 per slave. Is there that much?";
			link.l1 = "It's a deal.";
			link.l1.go = "pirateStartQuest_Smuggler_4";
		break;
		case "pirateStartQuest_Smuggler_4":
			pchar.questTemp.pirateStartQuest.Shore = SelectQuestShoreLocation();
			dialog.text = "Okay. Come with the money to a place called " + XI_ConvertString(pchar.questTemp.pirateStartQuest.Shore) + ", we'll talk there...";
			link.l1 = "Okay, I will. Just don't try to lead me by the nose - I don't have time to play games.";
			link.l1.go = "exit";

			pchar.questTemp.pirateStartQuest = "3";
			pchar.questTemp.pirateStartQuest.City2Nation = npchar.nation;
			AddQuestRecord("pSQ", "3");
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
			AddQuestUserData("pSQ", "sShore", XI_ConvertString(pchar.questTemp.pirateStartQuest.Shore));

			pchar.quest.pirateStartQuest_Smuggler_fc.win_condition.l1 = "Location";
			pchar.quest.pirateStartQuest_Smuggler_fc.win_condition.l1.location = pchar.questTemp.pirateStartQuest.City2 + "_ExitTown";
			pchar.quest.pirateStartQuest_Smuggler_fc.function = "pirateStartQuest_Smuggler_fc";

			AddGeometryToLocation(pchar.questTemp.pirateStartQuest.Shore, "smg");
			pchar.quest.pirateStartQuest_Smuggler_fc2.win_condition.l1 = "Location";
			pchar.quest.pirateStartQuest_Smuggler_fc2.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Shore;
			pchar.quest.pirateStartQuest_Smuggler_fc2.function = "pirateStartQuest_Smuggler_fc2";
		break;
		//--------------------------------------------------

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "I'm not your friend. And finding out some things can cost you dearly.";
				link.l1 = "Hmm. I need to know something worth nothing more " + FindRussianMoneyString(iChurchQuest2_Summ) + ".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;

		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Give me your money. And keep in mind, you won't learn much for that amount.";
				link.l1 = "I don't need much. I'm late to a meeting, but they didn't wait...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Heh, you don't have any money! Come when you get rich...";
				link.l1 = "Exactly.";
				link.l1.go = "exit";
			}
			break;

		case "Contra_GenQuest_Church_2_3":
			dialog.text = "What does this have to do with me?";
				link.l1 = "They are not in the city, they did not have their own ship either. So I thought that maybe one of your business partners did them a favor...?";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;

		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "That's it... Well, there was a case. People came up and said they urgently needed to leave, and it didn't matter where. In such cases, we do not ask for reasons, as long as we pay the price. We had a walk in " + XI_ConvertString("Colony" + sColony + "Acc") + " which is on " + XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat") + ". That's where they went. We can give you a lift too, if we agree on the price.";
			link.l1 = "Thanks, I'm under my own sail.";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "a"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
			break;

		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "I haven't had any dealings with you yet.";
				link.l1 = "Well, it's a matter of time. Not so long ago, you brought my friends here, whom I missed.";
				link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
			break;

		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Hmm, we dropped them off " + XI_ConvertString(sGenLocation + "Dat") + "... You know, it would be better if they really turned out to be your friends, otherwise I would not advise them to bother.";
			link.l1 = "Thanks for the concern, but I'm armed and very charming.";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Acc"));
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
			break;
		// <-- Церковный генератор №2

		case "Meeting_1":
			Dialog.Text = "Hmm... What does that have to do with me? You must have gone in the wrong place, Captain. Go to the store - they will be happy to buy what you brought.";
			Link.l1 = "I'm afraid it's you I need.";
			Link.l1.go = "Meeting_2";
			Link.l2 = "Thanks for the advice. Have a nice day.";
			Link.l2.go = "exit";
		break;

		case "Meeting_2":
			Dialog.Text = "Why then?";
			Link.l1 = "I want to sell something that no merchant on this island will buy.";
			Link.l1.go = "Meeting_3";
		break;

		case "Meeting_3":
			if (sti(npchar.SmugglingMoney) < 200000)
			{
				Dialog.Text = "I haven't sold your previous batch yet. I don't have money for a new goods yet, come back in a month or two.";
				Link.l1 = "I can find another client, you know... Well, goodbye.";
            	Link.l1.go = "exit";
				break;
			}

			if (CheckCharacterPerk(pchar, "UnlimitedContra"))
			{
				if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;

                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None" && !CheckAttribute(pchar, "Whisper.ContraSmuggler")&& !CheckAttribute(pchar, "Whisper.Contraband"))//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "I know you can be dealt with. We will be waiting for you at a place called " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
                            }
                            else
                            {
            				    Dialog.Text = "Hmm... Perhaps there will be a buyer. We will be waiting for you at a place called " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
            				}
            				Link.l1 = "Good. See you later.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar, "Whisper.Contraband"))
							{
								Dialog.Text = "It seems that you already have one deal scheduled, with someone on Tortuga. Come back when you figure it out.";
							}
							else
							{
								Dialog.Text = "There will be no more deals today. Come back tomorrow.";
							}
            				Link.l1 = "Good.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "And after all that, do you think anyone would want to work with you? Be glad we haven't sent assassins after your head yet. Get out!";
        				Link.l1 = "Eh... so it's not my destiny to become a smuggler.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar, "Whisper.Contraband"))
					{
						Dialog.Text = "It seems that you already have one deal scheduled, with someone on Tortuga. Come back when you figure it out.";
					}
					else
					{
						Dialog.Text = "There will be no more deals today. Come back tomorrow.";
					}
    				Link.l1 = "Good.";
    				Link.l1.go = "Exit";
				}
				break;
			}
			if (GetCompanionQuantity(pchar) > 1 && GetBaseHeroNation() != PIRATE)
			{
				dialog.text = NPCStringReactionRepeat("Get rid of your squadron first. It's too conspicuous. We can't take that risk. Come on one ship, and don't let it be bigger than a brig or a galleon.",
					"Did I make myself unclear? I repeat -no squadron!",
					"Are you stupid? O-n-e, I'm telling you - o-n-e ship, not two, not three, but one! Do you understand?",
					"Oh, and how earth wears such fools...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Okay, I got you. One so one.",
					"Everything is clear, I just wanted to clarify.",
					"No, I'm not stupid, just very greedy. I thought maybe something has changed, and you can come immediately as a squadron...",
					"Well, you see, he wears it somehow...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				break;
			}

		//редкостная хрень, но по-другому не работает-класс корабля ГГ считается отдельно от компаньонов, и всё тут
			int iClass, ipClass;
			ipClass = 4-sti(RealShips[sti(pchar.ship.type)].Class);
			iClass = 3;//т.к. не пройдёт по числу кораблей в любом случае
		if (GetBaseHeroNation() == PIRATE)
		{
			ipClass = sti(ipClass)-1;
			int iChIdx, i;
			// поиск старшего класса компаньона
			for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
					iClass = GetCharacterShipClass(sld);
				}
			}
		}
			if (sti(ipClass) > 0 || 3 - sti(iClass) > 0)
			{
				dialog.text = NPCStringReactionRepeat("You should have shown it at the royal man. I can see your boat from a mile away from the fort. We won't risk our heads. Come on a smaller ship, and only one.",
					"Am I making myself unclear? Find yourself a smaller boat, then come.",
					"Are you dumb or are you pretending? I'm telling you, find yourself a schooner, well, a brig as a last resort, or the deal won't happen.",
					"Oh, and how such fools"+ GetSexPhrase("akov", "") +"the earth wears...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Okay, I get you. I'll come back later, as soon as I change the boat.",
					"Yes, everything is clear, I just wanted to clarify.",
					"No, not stupid, just greedy. I thought that maybe something has changed. I would have brought a couple more pins with you...",
					"Well, you see, he wears it somehow...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // просрочка
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				if (makeint(environment.time) < 19.0)
				{
					Dialog.Text = "I'm sorry, we already have things to do. Come tonight, after 19 o'clock, maybe we'll be free.";
					Log_Info(FloatToString(ChangeContrabandRelation(pchar, 0),1));
					if (ChangeContrabandRelation(pchar, 0) > 5 && sti(pchar.money) >= 1000 && !bOk && !bOk2 && !bOk3 && npchar.quest.trade_date != lastspeak_date)
					{
						Link.l1 = "May be now? For a modest reward to you as an agent? 1000 piastres for example.";
						Link.l1.go = "AntiPGGContra";
					}
					Link.l2 = "It's a pity...";
					Link.l2.go = "Exit";
					break;
				}
				else
				{
					if (bOk || bOk2 || bOk3)
					{
						Dialog.Text = "Maybe we should finish one thing before we start another?";
						Link.l1 = "I guess you're right.";
						Link.l1.go = "Exit";
					}
					else
					{
						if (npchar.quest.trade_date != lastspeak_date)
						{
							npchar.quest.trade_date = lastspeak_date;

							if (ChangeContrabandRelation(pchar, 0) > 5)
							{
								Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
								Pchar.quest.contraband.City = NPChar.city;
								if (Pchar.quest.contraband.CurrentPlace != "None"  && !CheckAttribute(pchar, "Whisper.ContraSmuggler")&& !CheckAttribute(pchar, "Whisper.Contraband"))//boal fix
								{
									if (ChangeContrabandRelation(pchar, 0) >= 70)
									{
										Dialog.Text = "I know you can be dealt with. We will be waiting for you at a place called " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
									}
									else
									{
										Dialog.Text = "Hmm... Perhaps there will be a buyer. We will be waiting for you at a place called " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
									}
									Link.l1 = "Good. See you later.";
									Link.l1.go = "Smuggling_exit";
								}
								else
								{   //boal fix
									if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar, "Whisper.Contraband"))
									{
										Dialog.Text = "It seems that you already have one deal scheduled, with someone on Tortuga. Come back when you figure it out.";
									}
									else
									{
										Dialog.Text = "There will be no more deals today. Come back tomorrow.";
									}
									Link.l1 = "Good.";
									Link.l1.go = "Exit";
								}
							}
							else
							{
								Dialog.Text = "And after all that, do you think anyone would want to work with you? Be glad we haven't sent assassins after your head yet. Get out!";
								Link.l1 = "Eh... so it's not my destiny to become a smuggler.";
								Link.l1.go = "Exit";
							}
						}
						else
						{
							if(CheckAttribute(pchar, "Whisper.ContraSmuggler")|| CheckAttribute(pchar, "Whisper.Contraband"))
							{
								Dialog.Text = "It seems that you already have one deal scheduled, with someone on Tortuga. Come back when you figure it out.";
							}
							else
							{
								Dialog.Text = "There will be no more deals today. Come back tomorrow.";
							}
							Link.l1 = "Good.";
							Link.l1.go = "Exit";
						}
					}
				}
			}
			else if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "Maybe we should finish one thing before we start another?";
				Link.l1 = "I guess you're right.";
				Link.l1.go = "Exit";
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;

                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None"  && !CheckAttribute(pchar, "Whisper.ContraSmuggler")&& !CheckAttribute(pchar, "Whisper.Contraband"))//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "I know you can be dealt with. We will be waiting for you at a place called " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
                            }
                            else
                            {
            				    Dialog.Text = "Hmm... Perhaps there will be a buyer. We will be waiting for you at a place called " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
            				}
            				Link.l1 = "Good. See you later.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
							if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar, "Whisper.Contraband"))
							{
								Dialog.Text = "It seems that you already have one deal scheduled, with someone on Tortuga. Come back when you figure it out.";
							}
							else
							{
								Dialog.Text = "There will be no more deals today. Come back tomorrow.";
							}
            				Link.l1 = "Good.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "And after all that, do you think anyone would want to work with you? Be glad we haven't sent assassins after your head yet. Get out!";
        				Link.l1 = "Eh... so it's not my destiny to become a smuggler.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    if(CheckAttribute(pchar, "Whisper.ContraSmuggler")|| CheckAttribute(pchar, "Whisper.Contraband"))
					{
						Dialog.Text = "It seems that you already have one deal scheduled, with someone on Tortuga. Come back when you figure it out.";
					}
					else
					{
						Dialog.Text = "There will be no more deals today. Come back tomorrow.";
					}
    				Link.l1 = "Good.";
    				Link.l1.go = "Exit";
				}
			}
		break;

		case "AntiPGGContra":
			AddMoneyToCharacter(pchar,-1000);
			bool canDeal = GetCompanionQuantity(pchar) == 1 && sti(RealShips[sti(pchar.ship.type)].Class) > 2
			if (CheckCharacterPerk(pchar, "UnlimitedContra") || canDeal)
			{
				npchar.quest.trade_date = lastspeak_date;
				Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
				Pchar.quest.contraband.City = NPChar.city;
				if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
				{
					if (ChangeContrabandRelation(pchar, 0) >= 70)
					{
						Dialog.Text = "I know you can be dealt with. We will be waiting for you at a place called " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
					}
					else
					{
						Dialog.Text = "Hmm... Perhaps there will be a buyer. We will be waiting for you at a place called " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
					}
					Link.l1 = "Good. See you later.";
					Link.l1.go = "Smuggling_exit";
				}
			}
			else
			{
				Dialog.Text = "Wait, it's not going to work out this way! You should have shown it at the royal man. Come on a small ship, and only one, then we'll talk. And I'll take your money, as payment for the advice.";
				Link.l1 = RandSwear();
				Link.l1.go = "exit";
			}
		break;

		case "Trade"://торговля с контрами - Gregg
			int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
			Dialog.Text = "(Softly) Hmm... Yes, it is. ";
			switch (makeint(drand(7)))
			{
				case 0:
					npchar.itemtype = "Lockpick";//отмычки за драги
					npchar.pricev = "jewelry"+(drand2(3)+1);
					string type = npchar.pricev;
					Dialog.Text = dialog.text+ "I have some master keys available today. Are you interested? For 3 pieces, I ask only 5 "+LanguageConvertString(idLngFile, "itmname_"+npchar.pricev)+"s.";
					LanguageCloseFile(idLngFile);
					if (CheckCharacterItem(pchar, npchar.pricev) && sti(pchar.items.(type)) >= 5)
					{
						Link.l1 = "Of course I'm interested.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "No, it just got interesting.";
					Link.l2.go = "Exit";
				break;
				case 1:
					npchar.itemtype = "Totem_"+(drand2(13)+1);//тотем, не шипе-топеку
					npchar.pricevalue = 30000+drand1(20000);
					Dialog.Text = dialog.text+ "I have it in stock today "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+". Interested? I'm asking for him "+npchar.pricevalue+" piastres.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue))
					{
						Link.l1 = "Of course I'm interested.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "No, it just got interesting.";
					Link.l2.go = "Exit";
				break;
				/*case 2:
					npchar.itemtype = "sculMa"+(drand2(2)+1);//хрустальный череп
					npchar.pricevalue = 75000+drand1(25000);
					Dialog.Text = dialog.text+ "I have a real exclusive available today, "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+". Are you interested? I'm asking for him."+npchar.pricevalue+"piastres.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue))
					{
						Link.l1 = "Of course I'm interested.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "No, it just got interesting.";
					Link.l2.go = "Exit";
				break;*/
				case 2:
					npchar.itemtype = "indian"+(drand2(21)+1);//индиан, не крысобог
					if (npchar.itemtype == "indian11") npchar.itemtype = "indian"+(22-drand1(2));
					aref ind;
					Items_FindItem(npchar.itemtype, &ind);
					npchar.pricevalue = sti(GetItemPrice(npchar.itemtype))*10;
					if (CheckAttribute(ind, "groupID") && sti(GetItemPrice(npchar.itemtype)) < 100) npchar.pricevalue = sti(npchar.pricevalue)*25;
					Dialog.Text = dialog.text+ "Today I have a native trinket in stock, "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+". Interested? I'm asking "+npchar.pricevalue+" piastres for it.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue))
					{
						Link.l1 = "Of course I'm interested.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "No, it just got interesting.";
					Link.l2.go = "Exit";
				break;
				case 3:
					npchar.itemtype = "jewelry"+(drand2(3)+1);//драги за бабки
					npchar.pricev = "j";
					npchar.pricevalue = 20000+drand1(5000);
					Dialog.Text = dialog.text+ "I have precious stones in stock today, "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+"s. Are you interested? For a collection of 25 pieces, I ask "+npchar.pricevalue+" piastres.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue))
					{
						Link.l1 = "Of course I'm interested.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "No, it just got interesting.";
					Link.l2.go = "Exit";
				break;
				case 4:
					npchar.itemtype = "Lockpick";//отмычки за драги
					npchar.pricev = "jewelry"+(drand2(3)+1);
					string type1 = npchar.pricev;
					Dialog.Text = dialog.text+ "I have some master keys available today. Are you interested? For 3 pieces, I ask only 5 "+LanguageConvertString(idLngFile, "itmname_"+npchar.pricev)+"s.";
					LanguageCloseFile(idLngFile);
					if (CheckCharacterItem(pchar, npchar.pricev) && sti(pchar.items.(type1)) >= 5)
					{
						Link.l1 = "Of course I'm interested.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "No, it just got interesting.";
					Link.l2.go = "Exit";
				break;
				else
					Dialog.Text = "Alas, I don't have anything interesting available today.";
					Link.l2 = "Oh, what a pity. Well, see you then.";
					Link.l2.go = "Exit";
				break;
			}
			/*Dialog.Text = "(Softly) Hmm... Yes, it is. Do you want to buy something now?";
			Link.l1 = "Yes, show me your goods.";
			Link.l1.go = "Trade_exit";
			Link.l2 = "No, it just got interesting.";
			Link.l2.go = "Exit";*/
		break;

		case "Trade_2":
		{
			int idLngFile1 = LanguageOpenFile("ItemsDescribe.txt");
			if (CheckAttribute(npchar, "pricev"))
			{
				if (npchar.itemtype == "Lockpick")
				{
					Log_Info("You gave away 5 "+LanguageConvertString(idLngFile1, "itmname_"+npchar.pricev)+"s.");
					Log_Info("You have received 3 master keys.")
					TakeNItems(pchar, npchar.pricev, -5);
					TakeNItems(pchar, npchar.itemtype, 3);
				}
			}
			if (CheckAttribute(npchar, "pricevalue"))
			{
				if (npchar.itemtype != "Lockpick")
				{
					AddMoneyToCharacter(pchar, -sti(npchar.pricevalue));
					if (CheckAttribute(npchar, "pricev"))
					{
						TakeNItems(pchar, npchar.itemtype, 25);
						Log_Info("You got 25"+LanguageConvertString(idLngFile1, "itmname_"+npchar.itemtype)+"s.");
					}
					else
					{
						GiveItem2Character(pchar, npchar.itemtype);
						Log_Info("You got it"+LanguageConvertString(idLngFile1, "itmname_"+npchar.itemtype)+".");
					}
				}
			}
			LanguageCloseFile(idLngFile1);
			DeleteAttribute(npchar, "pricevalue");
			DeleteAttribute(npchar, "pricev");
			DeleteAttribute(npchar, "itemtype");
			pchar.contratrade.time = GetDataDay();
			ChangeContrabandRelation(pchar, 5)
			Dialog.Text = "Here you go! It's a pleasure doing business with you. I guess we'll meet again.";
			Link.l2 = "Thank you. See you later!";
			Link.l2.go = "Exit";
		}
		break;

////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
			//если нет корабля у ГГ и нет компаньонов все ок
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//случай если уже была инфа
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//платил уже
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "I think we've already agreed?";
						Link.l2 = "Yes, that's right!";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Prin"+ GetSexPhrase("collective", "if") +"money?";
							Link.l1 = "Yes.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "I've changed my mind....";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Not yet.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "I've already told you everything.";
								Link.l2 = "Exactly.";
								Link.l1 = "I've changed my mind....";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "I can't help you today. Come back in a couple of days, maybe that will happen.";
								Link.l2 = "It's a pity.";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//если не было договора, обговариваем условия
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//если нормальные отношения и количество подстав меньше 20, работаем....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//бухта...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//за сколько доставят
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;

						//если метро активно, и нет пассажиров у ГГ, и ещё сегодня не виделись, есть доступная бухта, и ранд ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") &&
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "Well, we can get you there " + GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id, "LocLables.txt") + " near " +
								XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen") + " for " + pchar.GenQuest.contraTravel.price + " gold. Will you bring the money through " +
								FindRussianDaysString(nDay) + ". The ship will be waiting for you at a place called " +
								GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id, "LocLables.txt") + " exactly one day.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Okay, that's fine with me.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "No, thanks.";
						}
						else
						{
							Dialog.Text = "I can't help you today. Come back in a couple of days, maybe something will happen.";
							Link.l2 = "It's a pity.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "And after all that, do you think anyone would want to work with you? Be glad we haven't sent assassins after your head yet. Get out!";
        				Link.l2 = "Eh... so it's not fate.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "No, we're not taking you. Just one.";
					Link.l2 = RandSwear() + "And you don't need to!";
				}
				else
				{
					Dialog.Text = "And why do you need your own ship? No, we're not doing that.";
					Link.l2 = "It's obviously not fate...";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "Well, whatever you want...";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//активируем квест
			pchar.GenQuest.contraTravel.active = true;
			pchar.GenQuest.contraTravel.GuardNation = npchar.nation;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//ГГ согласен платить
		case "Travel_pay":
			//денег хватает?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//ставим флаг оплаты
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "It's nice doing business with you. The ship is waiting, don't be late.";
				Link.l1 = "I'll try.";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("", "a"));

				//ставим контру.
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//корабль на волнах в бухте....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "pirate_6", "man", "man", 5, PIRATE, Sum + 2, true));
				//воскресим...
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_SILVER));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//нет, посылаем в сад...
			else
			{
				Dialog.Text = "It looks like you're having cash problems."
				Link.l1 = "It's a pity, I'll come later.";
			}
			Link.l1.go = "Exit";
			break;

		case "Give_vector":
			dialog.text = "My old friend, Snakeman Young, a former pirate, runs a tavern in Le Francois. He is looking for a pirate captain who is little known in the Brethren. I promised to help him find such a captain. So I suggest you go to Martinique and talk to my friend. As far as I know him - you certainly will not stay in the overhang.";
			link.l1 = "And what kind of business does he want to offer? Don't you know?";
			link.l1.go = "Give_vector_1";
		break;

		case "Give_vector_1":
			dialog.text = "No. He's become very secretive lately. Contact him - he will tell you everything himself.";
			link.l1 = "Well, I'll definitely look him up.";
			link.l1.go = "Give_vector_2";
			link.l2 = "Hmm... You know, I have too many problems to solve other people's problems as well. Going to Le Francois without even knowing what exactly your friend wants from me? I'm sorry, but this is not for me.";
			link.l2.go = "exit_quest";
		break;

		case "Give_vector_2":
			dialog.text = "Just don't delay the visit too much, Captain.";
			link.l1 = "Yes, of course. I am intrigued by your offer. All the best and good luck to you!";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "vector_barmen";
            AddQuestRecord("Headhunt", "1_1");
			AddQuestUserData("Headhunt", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		break;

		case "exit_quest":
			dialog.text = "Then let's forget about this conversation. Goodbye.";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "end_quest";
		break;

////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
	}
}
