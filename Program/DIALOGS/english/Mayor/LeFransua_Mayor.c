// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What did you want? Ask.", "I'm listening to you, what's the question?"), "For the second time in a day you're trying to ask a question...", "For the third time in a day you're trying to ask a question again...",
                          "But when will it end?! I have a lot of things to do to manage the affairs of the city, and you're trying to ask all the questions!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, not the place and not the time..."), "Yes, that's right... But not now, later...",
                      "I'll ask, I'll ask... Only later...", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l4 = "Listen, Rogers, does the word 'arrow' mean anything to you? Maybe there is a pirate named 'Arrow' here, or a pirate ship with that name came to your port?";
				link.l4.go = "Mushket";
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "I'm here about your prisoner.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
				}
				if(CheckAttribute(pchar, "GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Hello" + NPChar.name + ", I'm here about your errand.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "I'm here about your prisoner.";
					link.l1.go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "questTemp.silverfleet") && pchar.questTemp.silverfleet != "over" && pchar.questTemp.silverfleet != "ToHuber" && NPChar.id == "LeFransua_Mayor")
			{
				if(!CheckAttribute(NPChar, "SilverFleetSeaCheck"))
				{
					link.l1 = "Hello. You should have been notified about me. I'm here about a shipment from Brabados to Jamaica...";
					link.l1.go = "SF_LeFransuaBeginning";
				}
				if (GetNpcQuestPastDayParam(NPChar, "SilverFleetSeaCheck") > 0)
				{
					link.l1 = "About the convoy...";
					link.l1.go = "SF_LeFransuaSeaCheck";
				}
			}
		break;

		case "Mushket":
			dialog.text = "Ah, and this jerk has stepped on your tail. This ship of Albert Sievert is a very good brig, perhaps the best in the archipelago. No wonder Jackman couldn't get it himself. Why do you need it?";
			link.l1 = "Yes, there is one thing... I'd like to find this Sievert.";
			link.l1.go = "Mushket_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2");
		break;
		case "Mushket_1":
			dialog.text = "But how will you find him? He's on his own, he doesn't work for anyone, he doesn't pay anyone a share, he doesn't go into pirate ports himself - so that they don't force him to share, and they don't let him into the ports of the colonies. No, they're waiting for him there, of course, to woo him with a noose, but he won't take any chances - he's not that kind of person.";
			link.l1 = "Yeah... Can you recommend something?";
			link.l1.go = "Mushket_2";
		break;
		case "Mushket_2":
			dialog.text = "There is one person who was paired with this Sievert. But something didn't stick together - either Sievert left him overboard, or vice versa. Both of them are from the same field of berries, otherwise they probably wouldn't have come together.This guy now runs a tavern in Porto Bello, Rolando Pizarro is called, or simply - the Fox. He may know the parking spots. And besides, look for this brig at sea, you won't confuse it with anyone. Just be careful - he's really crazy...";
			link.l1 = "Clear. Well, thank you, Bartholomew.";
			link.l1.go = "exit";
			pchar.questTemp.mushket2x2_stid = true;
			AddQuestRecord("SeekDoubleMushket", "2");
		break;

		case "CapComission1":
			dialog.text = "Ho-ho. Do you think I have only one prisoner? Name who exactly do you have in mind?";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Is there one?";
			link.l1.go = "CapComission2";
		break;

		case "CapComission2":
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Was. I sold it to that damn Barbadian planter, Colonel Bishop, who came by last week.";
				link.l1 = "Damn it...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = "Ah, finally. I was thinking of selling it to the devil to that planter from Barbados, I should have it in a week or two... Did you bring a buy back?";
				link.l1 = "Listen, "+ NPChar.name +", here's the deal... In general, I don't have enough money. But I'm ready to work out.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Good thing you didn't. Here's 150000 gold. Where can I get it?"
					link.l2.go = "CapComission2_3";
				}
			}
		break;

		case "CapComission2_1":
			dialog.text = "You've been talking for a long time... By the way, how does this slave get to you? I remember paying a ransom to his relatives.";
			link.l1 = "Yes, I came on behalf of these relatives.";
			link.l1.go = "CapComission2_11";
		break;

		case "CapComission2_11":
			dialog.text = "Well, you late - what can I do?";
			link.l1 = "Listen, how much did you sell for, if it's not a secret?";
			link.l1.go = "CapComission2_12";
		break;

		case "CapComission2_12":
			dialog.text = "Uh, it's not a secret, of course, but I won't tell you. Otherwise you'll laugh, ha-ha-ha-ha... Well, bye.";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;

		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Hmm-hmm... I have something to do... I don't even know how to start... In general, we need to sink one arrogant pirate.";
				link.l1 = "Isn't it possible to remove it in the jungle?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Well, " + pchar.name + ", you know that's not how things are done. Come with the money and you'll get your pickle, hehe.";
				link.l1 = "Well, see you later.";
				link.l1.go = "exit";
				if(!CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName",  pchar.GenQuest.CaptainComission.PirateName);
				}
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Well, you know, that's not how serious things are done... I don't need his death, I need to discourage those who are too zealous from gaping at my part of the prey. Although, if he goes to the octopuses, I won't be upset.";
			link.l1 = "Why don't you send your people after him?";
			link.l1.go = "CapComission2_2_2";
		break;

		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			string sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hmm... In general, a certain " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " convinced some of the pirates that our hiding place is near " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + " there is also their share. They recently weighed anchor on two ships '" + pchar.GenQuest.CaptainComission.ShipName1 + "' and '" + pchar.GenQuest.CaptainComission.ShipName2 + "' went to " + sLoc + ". Do you understand now why I can't entrust this matter to my people?";
			link.l1 = "Understood. And how much time do I have?";
			link.l1.go = "CapComission2_2_3";
		break;

		case "CapComission2_2_3":
			dialog.text = "I think 12-15 days, no more. It is important to me that they did not have time to reach the hiding place, otherwise to drown them with valuable cargo on board will not make sense. They better bring him in.";
			link.l1 = "Okay, I'm taking this case. I'll try to make it.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.PirateName);
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips";
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";
		break;

		case "CapComission2_3":
			dialog.text = "Don't worry. My men will bring him aboard for you... Who is he to you?";
			link.l1 = "Nobody. I'm running an errand for his relative.";
			link.l1.go = "CapComission2_31";
		break;

		case "CapComission2_31":
			dialog.text = "Ah, that's good. I was already upset that I had sold out by setting such a low price for your man. Ha ha ha ha... Well, bye.";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission3":
			dialog.text = "Well, " + GetFullName(pchar) + ", did you let my friend go to the bottom? Heh heh heh...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "No. I didn't have time  catch up with them. And I didn't come across them on the way back.";
				link.l1.go = "CapComission4";
			}
			else
			{
				if(pchar.GenQuest.CaptainComission.PirateShips == "died")
				{
					link.l1 = "Yes, as agreed - sent feed the sharks.";
					link.l1.go = "CapComission5";
				}
			}
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;

		case "CapComission4":
			dialog.text = "Damn! Caught - not caught, what difference does it make now? So what do you propose next?";
			link.l1 = "Maybe you have some simpler errand?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Listen, " + npchar.name + ", give me this prisoner cheaper...";
			link.l2.go = "CapComission4_2";
		break;

		case "CapComission4_1":
			dialog.text = "No.";
			link.l1 = "...Well, then have a nice stay...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "la"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;

		case "CapComission4_2":
			dialog.text = "Cheaper?!! Just because of your slowness I lost my stash! and now I can concede it more expensive!!. Take it for 200,000 if you want.";
			link.l1 = "It's expensive... Goodbye...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Damn it, keep your money.";
				link.l2.go = "CapComission4_5";
			}
		break;

		case "CapComission4_4":
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;

		case "CapComission4_5":
			dialog.text = "You can take the starving one...";
			link.l1 = "Have a nice stay.";
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission5":
			dialog.text = "Ho ho! That's a job! Take your baby and be healthy.";
			link.l1 = "Thank you. Have a nice stay.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission6":
			dialog.text = "Did you bring a buy back? After all, I wasn't joking when I said I would sell it to the planters.";
			link.l1 = "Listen, "+ NPChar.name +", here's the deal... In general, I don't have enough money. But I'm ready to work out.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Good thing you didn't. Here's 150,000 gold. Where can I get it?"
				link.l2.go = "CapComission2_3";
			}
		break;
		case "SF_LeFransuaBeginning":
			dialog.text = "Yes, yes, I've been warned. But I won't tell you much. My immediate superiors have an interest in this convoy... So I won't give you a detailed tip, but I will give you some information.";
			link.l1 = "Thanks for that. So what do you have to say?";
			link.l1.go = "SF_LeFransuaSeaCheck";
			pchar.questTemp.silverfleet.lefransuamayorspeak = true;
		break;

		case "SF_LeFransuaSeaCheck":
			dialog.text = "At the moment, the Silver Convoy is not on its way. There may be new information tomorrow.";
			if (CheckExistQuestEncounter("Head_of_Silver_Squadron")) dialog.text = "Right now, the Silver Convoy is en route to Jamaica. I can't be more specific, sorry. There may be more information tomorrow.";
			if (GetNpcQuestPastDayWOInit(pchar, "SilverFleetGo") < 3) dialog.text = "Most recently, the 'Silver Convoy' was seen near Barbados. You know where it was headed.";
			link.l1 = "Got it. Thank you.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "SilverFleetSeaCheck");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
