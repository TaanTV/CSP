#include "DIALOGS\english\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	ref FortChref = GetFortCommander(NPChar.City);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("The alarm has been raised in the city, they are looking for you everywhere! If I were you, I wouldn't stay here too long.", "The entire city guard is scouring the city in search of you. I'm not an idiot and I won't talk to you!", "Run, "+ GetSexPhrase("buddy", "girlfriend") +"before the soldiers make a sieve out of you..."),
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel", "scoundrel") +"?! The city guard has already are on your trail, you won't get far"+ GetSexPhrase("dirty pirate!", "") +"", "Dirty murderer, get out of my house! Guards!!", "I'm not afraid of you, bastard! You'll be hanged in our fort soon, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, anxiety is not a problem for me...", "They will never catch me."),
					RandPhraseSimple("Shut your mouth, " + GetWorkTypeOfMan(npchar, "") + ", or I'll rip out your filthy tongue!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", and still there - catch pirates! I'll tell you what, buddy: stay quiet and you'll live..."));
				link.l1.go = "exit";
				break;
			}
            // homo линейка капитана Блада
            if (CheckAttribute(Pchar, "questTemp.CapBloodLine") && Pchar.questTemp.CapBloodLine == true)
            {
                dialog.Text = LinkRandPhrase("Hey, Dr. Blood! " + TimeGreeting() + ".",
                                    "Glad to see you, Peter Blood.",
                                    "It's good that you looked at me, " + GetFullName(pchar) + ". How is Colonel Bishop?");
                Link.l1 = "Alas, I'm already leaving, " + npchar.name + ". See you later.";
				Link.l1.go = "exit";

                if(Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
                {
            		link.l2 = "Can you tell me, my friend " + npchar.name + ", how do I find Dr. Wacker?";
            		link.l2.go = "TStep_0";
                }

                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape")
                {
            		link.l2 = "I have a delicate matter for you.";
            		link.l2.go = "TStep_1";
                }

                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff") && pchar.questTemp.CapBloodLine.QuestRaff == true)
                {
            		link.l2 = "I am interested in a man named Raphael Guinness. How do I find him?";
            		link.l2.go = "TStep_5";
                }
                break;
    		}
			//Sinistra пролог Анжелики Тич
			if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue"))
            {
                dialog.Text = "Good afternoon, senorita.";
                Link.l1 = "Good afternoon, " + npchar.name + ".";
				Link.l1.go = "At_pr_1";
                break;
    		}

			if (drand2(100)==0 && sti(pchar.rank) >= 20 && GetCharacterItem(Pchar, "map_full") <= 0)
			{
				if (!CheckAttribute(pchar, "questTemp.UniquePirate.Drake") || !CheckAttribute(pchar, "questTemp.UniquePirate.Barbarigo") || !CheckAttribute(pchar, "questTemp.UniquePirate.BlackBeard") || !CheckAttribute(pchar, "questTemp.UniquePirate.Levasser"))
				{
					dialog.text = "Captain, I have a treasure map lying around here, it's probably very valuable. Interested?";
					link.l1 = "Of course! How much are you asking for?";
					link.l1.go = "SpecialMapBuy";
					link.l2 = "I'll manage, I guess. You never know whose daub, maybe it's a fake at all.";
					link.l2.go = "exit";
					break;
				}
			}

			//зачарованный город -->
			if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
			{
				dialog.text = "For God's sake, Captain, save me! They will ruin everything! My tavern!";
				link.l1 = "Are you a werewolf or something?";
				link.l1.go = "MCTavern";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasWervolf" && npchar.city == "Caracas")
			{
				dialog.text = "Captain, you promised to go to the werewolf...";
				link.l1 = "I remember.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				dialog.text = "Well, what do you say, Captain? Have you found him?";
				link.l1 = "I have. But now is not the time to talk, I'll tell you everything later...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasTavern" && npchar.city == "Caracas")
			{
				dialog.text = "Captain, glad to see you!";
				link.l1 = "What happened to this guest of yours?";
				link.l1.go = "MCCaracasAfter";
				break;
			}
			//<-- зачарованный город

			if(NPChar.quest.meeting == "0")
			{
				if (npchar.city == "Pirates")
				{
					dialog.Text = "Bah, here's another "+ GetSexPhrase("one dashing captain", "one brave sailor") +" has come! Make yourself comfortable, "+ GetSexPhrase("sir", "miss") +". My name is Lucky Rosin, and I am always at your service. The weather is good today, isn't it? Would you like a rum?";
					Link.l1 = "What did you say your name was? La Kerosene? I didn't think that there are Castilians among the pirates!";
					Link.l1.go = "Pirates_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "Charles")
				{
					dialog.Text = "Welcome, " + GetAddress_Form(NPChar) + ". Food, booze and entertainment - all at reasonable prices! My name is " + GetFullName(npchar) + ". I am the owner of this tavern.";
					Link.l1 = "One-eyed Steed? I heard about you. People say that in the recent past you became famous for hunting Spanish galleons. It's hard to believe...";
					Link.l1.go = "Charles_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "Portobello")
				{
					dialog.Text = "Welcome, " + GetAddress_Form(NPChar) + ". Food, booze and entertainment - all at reasonable prices! My name is " + GetFullName(npchar) + ", but I am better known as the Catalan Fox. I am the owner of this tavern.";
					Link.l1 = "The Catalan Fox? I've heard about you. People say that you once shook up the British in Barbados - you captured a military brig in the harbor of Barbados on some kind of tub and stole it literally from under the nose of the fort.";
					Link.l1.go = "Portobello_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "FortFrance")
				{
					dialog.Text = "Welcome, " + GetAddress_Form(NPChar) + ". " + GetFullName(NPChar)+" at your service! And will you allow your faithful servant to suggest that you respect the only thing, in his opinion, worthwhile in this whole world - a little rum? Heh heh heh!";
					Link.l1 = "Ah, " + npchar.name+", the most valuable thing in the world is information.";
					Link.l1.go = "FortFrance_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "Nassau")
				{
					dialog.Text = "Why are you staring? You didn't expect, that a woman running everything here?! Ha! " + GetFullName(NPChar)+" will show everyone that there is life in the old dog!";
					Link.l1 = "Hey, where did you learn these manners?";
					Link.l1.go = "Nassau_1";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.Text = "Welcome, " + GetAddress_Form(NPChar) + ". Food, booze and entertainment - all at reasonable prices!";
				Link.l1 = "Let's see... I am " + GetFullName(pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "Well, cap, you brought me " + FindRussianMoneyString(iTemp) + ".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Yes, prin"+ GetSexPhrase("eu", "esla") +". Here they are...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "No, not yet"+ GetSexPhrase("eu", "if") +"...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "What do you want, gracious"+ GetSexPhrase("my lord", "my lady") +"?";
						link.l1 = "A bottle of rum to my friend, at that table over there.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.

				////////////////
				//Линейка Виспер
				////////////////
				if(startherotype == 2 && CheckAttribute(pchar, "Whisper.FindDesouza") && !CheckAttribute(pchar, "Whisper.Contraband") && sti(pchar.money) >= 10000 && npchar.nation!=3)
				{
					bool Whisper_cnd = GetCharacterSkill(pchar,SKILL_SAILING)>= 65 && pchar.rank >=5 && GetCharacterShipClass(PChar) <= 4;
					if (pchar.rank >=10 || Whisper_cnd)
					{
						dialog.Text = "Captain, you shouldn't walk around like this. I've heard the Inquisition is looking for a girl with the same hair color. You should cover up, or something.";
						DeleteAttribute(pchar, "Whisper.FindDesouza")
						Link.l1 = "Who did you hear that from?";
						Link.l1.go = "w_find_desouza";
						break;
					}
				}
				if (CheckAttribute(pchar, "Whisper.NanoCostume") && !CheckAttribute(pchar, "Whisper.AfterWarDog") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_WH_CORVETTE_QUEST && npchar.id != "Pirates_tavernkeeper")
				{
					pchar.Whisper.AfterWarDog = true;
					dialog.Text = "Greetings. Isn't that your corvette that recently docked at our port?";
					Link.l1 = "Well, let's say mine, what do you care?";
					Link.l1.go = "w_meet_esteban_friend";
					break;
				}

				// <-- Линейка Виспер
				// ЧП
				if(GetQuestPastDayParam("BSPrologueEnded") > 7 && sti(pchar.rank) >= 30 && sti(npchar.nation) == PIRATE && npchar.id != "Pirates_tavernkeeper" && !CheckAttribute(pchar, "BSOnTheHorizon"))
				{
					pchar.BSOnTheHorizon = true;
					BSBons_SeaBattle(false);
					dialog.text = "Hey, isn't our hope and support looking for you, bright-faced Miss Guthrie?";
					link.l1 = "Oh my God! What is it this time?";
					link.l1.go = "BS_CPNG_2";
					break;
				}
				// ЧП
				dialog.Text = LinkRandPhrase("Hey, " + GetAddress_Form(NPChar) + " " + PChar.name + "! " + TimeGreeting() + ".",
                                    "Who do I see! Glad to see you, " + GetAddress_Form(NPChar) + " " + PChar.name + ".",
                                    "It's good that you looked at me, " + GetFullName(pchar) + ". What will your order be today?");
				Link.l1 = "Are there guys on the island who are ready to go sailing?";
				Link.l1.go = "crew hire";
				Link.l2 = "I hope you can answer a few questions.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Listen, we need to talk about financial matters.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}


				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery of a church?", "What do you know about the recent robbery of a local church?", "Have you heard anything about the recent robbery of a local church?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase("Is there a free kennel in your bedbug?", "Do you have a free room? I would like to stay here for a while.");
				link.l3.go = "room";
				Link.l4 = "Alas, I'm already leaving, " + npchar.name + ". See you later.";
				Link.l4.go = "exit";
			}
		break;

		case "BS_CPNG_2":
            dialog.text = "I have no idea. But her messenger asked very convincingly to tell captain "+pchar.name+" that someone is waiting for " + GetSexPhrase("him", "her") + " at the Guthrie residence in the Bahamas. And if I were this captain, I wouldn't delay.";
            link.l1 = "Okay, I got it.";
			link.l1.go = "exit";
			SetQuestHeader("BSOnTheHorizon");
			AddQuestRecord("BSOnTheHorizon", "1");
			LocatorReloadEnterDisable("Nassau_town", "gate1", true);
			LocatorReloadEnterDisable("Nassau_ExitTown", "reload2_back", true);
			PChar.quest.BSOnTheHorizon_start.win_condition.l1 = "location";
			PChar.quest.BSOnTheHorizon_start.win_condition.l1.location = "Nassau_town";
			PChar.quest.BSOnTheHorizon_start.function = "BSOnTheHorizon_start";
		break;

		case "SpecialMapBuy":
			pchar.questTemp.SpecialMapPrice = 100000+drand(50000);
			aref item;
			Items_FindItem("map_full", &item);
			string type = GetUniquePirateName();
			FillMapForUniqueTreasure(item, type);
			type = GetUniquePirateNameString(type);
			dialog.Text = "Cheaper than for "+pchar.questTemp.SpecialMapPrice+" I will not concede piastres. According to rumors, this is a treasure map of the "+type+" itself. If it wasn't for the tavern, maybe I would have tried to equip a search team.";
			if (sti(pchar.money)>sti(pchar.questTemp.SpecialMapPrice))
			{
				link.l1 = "Caramba, nice price though. Well, I'll take it.";
				link.l1.go = "SpecialMapBuy_1";
			}
			link.l2 = "For such a price? I found "+GetSexPhrase("fool.", "fool.")+"Come on!";
			link.l2.go = "exit";
		break;

		case "SpecialMapBuy_1":
			AddMoneyToCharacter(pchar,-sti(pchar.questTemp.SpecialMapPrice));
			GiveItem2Character(pchar, "map_full");
			dialog.Text = "Here you go, I hope it will be worth it. Have a good treasure hunt, Captain!";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
		break;

		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "What do you want, gracious"+ GetSexPhrase("my lord", "my lady") +"?";
				link.l1 = "A bottle of rum for my friend at that table over there.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			if (npchar.city == "Pirates")
			{
				dialog.Text = "Oh, don't take my words so personally, " + GetAddress_Form(NPChar) + ". I like to grumble, and sometimes complain about life... Well, I'm listening to you carefully, Captain.";
				Link.l1 = "I need a team, " + npchar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", lets talk...";
				Link.l2.go = "int_quests";

				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Listen, we need to talk about financial matters.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}

				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery of a church?", "What do you know about the recent robbery of a local church?", "Have you heard anything about the recent robbery of a local church?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}

				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase("Is there a free kennel in your bedbug?", "Do you have a free room, I wanted to stay here for a while.");
				link.l3.go = "room";
				Link.l4 = "I'll probably check in on you later.";
				Link.l4.go = "exit";
				break;
			}

			if (npchar.city == "Charles")
			{
				dialog.Text = "Yes, in general, I am always happy to talk to "+ GetSexPhrase("pleasant companion", "pretty companion") +"... Well, so what did you want, " + GetAddress_Form(NPChar) + "?";
				Link.l1 = "I need a team, " + npchar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", lets talk...";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Listen, we need to talk about financial matters.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery of a church?", "What do you know about the recent robbery of a local church?", "Have you heard anything about the recent robbery of a local church?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase("Is there a free kennel in your bedbug?", "Do you have a free room, I wanted to stay here for a while.");
				link.l3.go = "room";
				Link.l4 = "I'll probably check in on you later.";
				Link.l4.go = "exit";
				break;
			}

			if (npchar.city == "Portobello")
			{
				dialog.Text = "Oh, I'm always happy to chat, "+ GetSexPhrase("buddy", "girlfriend") +". After all, now you are my friend, know this, " + GetAddress_Form(NPChar) + ". What do you want?";
				Link.l1 = "I need a team, " + npchar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", lets talk...";
				Link.l2.go = "int_quests";

				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Listen, we need to talk about financial matters.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery of a church?", "What do you know about the recent robbery of a local church?", "Have you heard anything about the recent robbery of a local church?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}

				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase("Is there a free kennel in your bedbug?", "Do you have a free room, I would like to stay here for a while.");
				link.l3.go = "room";
				Link.l4 = "I'll probably check in on you later.";
				Link.l4.go = "exit";
				break;
			}
			
			if (npchar.city == "FortFrance")
			{
				dialog.Text = "I'm a cheerful old innkeeper, and I'm always happy to cheer you up, "+ GetSexPhrase("my friend", "my dear") +". Would you like a rum? Hee hee hee.";
				Link.l1 = "I need a team, " + npchar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", lets talk...";
				Link.l2.go = "int_quests";

				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Listen, we need to talk about financial matters.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery of a church?", "What do you know about the recent robbery of a local church?", "Have you heard anything about the recent robbery of a local church?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}

				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase("Is there a free kennel in your bedbug?", "Do you have a free room, I would like to stay here for a while.");
				link.l3.go = "room";
				Link.l4 = "I'll probably check in on you later.";
				Link.l4.go = "exit";
				break;
			}
			
			if (npchar.city == "Nassau")
			{
				dialog.Text = "What do you need, "+pchar.name+"? Came to get your whistle wet?";
				Link.l1 = "I need a team, " + npchar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", lets talk...";
				Link.l2.go = "int_quests";

				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Listen, we need to talk about financial matters.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery of a church?", "What do you know about the recent robbery of a local church?", "Have you heard anything about the recent robbery of a local church?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}

				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase("Is there a free kennel in your bedbug?", "Do you have a free room, I would like to stay here for a while.");
				link.l3.go = "room";
				if (!CheckAttribute(pchar, "questTemp.Istoria_InesDias"))	//Инес Диас расскажет о себе
				{
					link.l35 = "Tell me about yourself. How did you become the owner of this tavern?";
					link.l35.go = "Istoria_InesDias_1";
				}
				Link.l4 = "I'll probably check in on you later.";
				Link.l4.go = "exit";
				break;
			}
			dialog.Text = "Oh, you'll see for yourself, " + GetAddress_Form(NPChar) + ". My name is " + GetFullName(npchar) + ". I am the owner of this tavern.";
			Link.l1 = "I need a team, " + npchar.name + ".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name + ", lets talk...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "Listen, we need to talk about financial matters.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery of a church?", "What do you know about the recent robbery of a local church?", "Have you heard anything about the recent robbery of a local church?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			link.l3 = pcharrepphrase("Is there a free kennel in your bedbug?", "Do you have a free room, I would like to stay here for a while.");
			link.l3.go = "room";
			Link.l4 = "I'll probably check in on you later.";
			Link.l4.go = "exit";
		break;

		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (NPChar.id == "Caiman_tavernkeeper") ok = true;
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;

			// здесь убираю условие
			if (!ok)
			{
				Dialog.text = "What do you need sailors for? I don't see your ship in port.";
				link.l1 = RandPhraseSimple("Exactly... I docked it in the wrong place.", "I forgot to enter the port...");
				link.l1.go = "exit";
				break;
			}
			//здесь меняю дату
            if (makeint(environment.time) > 24.0 || makeint(environment.time) < 0.0)
			{
				Dialog.text = "I usually have a lot of people in my tavern who want to become sailors, but it's too late now, and they won't start showing up until the morning. Would you like to rent a room and wait for them?";
				link.l1 = "Okay. Do you have any rooms available?";
				link.l1.go = "room";
				link.l2 = "I'm not interested in the room at the moment. See you later.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "Do you think someone will come to you when you are at enmity with us? Be grateful that I'm not calling the guards.";
					link.l1 = "Thank you.";
					link.l1.go = "exit";
                }
                else
                {
					if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) == FORT_DEAD)
					{
						Dialog.text = "Now there is no one. During the recent storming of the city, most of the applicants died, and the smaller one hid so that they are not found now.";
						link.l1 = "Oh, it's a pity!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 1 && GetCrewQuantity(rColony) == 0 && drand(100) > 90)
					{
						Dialog.text = "I'm sorry, but there's no one here right now. Everyone left with a brave cap " + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + ".";
						link.l1 = "Oh, it's a pity!";
						link.l1.go = "exit";
					}
					else
					{
						if(bPartitionSet)
						{
							if((Partition_GetSetting("Part_Crew") == 0) || GetPartitionAmount("CrewPayment") > 0)
							{	
								if(IsEquipCharacterByArtefact(pchar, "talisman11"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Captain, they say that you are stingy. I don't have anyone willing to join your team.";
									link.l1 = "I see...";
									link.l1.go = "exit";
								}
							}	
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();
							}
						}
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();
						}
					}
				}
			}
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////
        case "int_quests":
			dialog.text = "I am "+NPCharSexPhrase(NPChar, "all attention", "listening")+".";
			link.l1 = "I'm looking for a job. Will you help me?";
			link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Tell me the latest news?", "What's new in these parts?",
                                    "How does life flow on land?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "I'm on another case.";
			link.l3.go = "quests";
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City")) //квест мэра по поиску шпиона
			{
				link.l4 = "I am acting on behalf of the governor. Tell me, have you noticed anyone suspicious in the city lately?";
				if (pchar.GenQuest.SeekSpy.City == "0")
				{
					link.l4.go = "SeekSpy_Seen";
				}
				else
				{
					link.l4.go = "SeekSpy_NotSeen";
				}
			}
			if(CheckAttribute(pchar, "GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Don't you know, where I can find " + pchar.GenQuest.EncGirl.name +"?";
					link.l5.go = "EncGirl_1";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Don't you know, where I should look for " + pchar.GenQuest.EncGirl.sLoverId + "?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Hello, I'm here at your son's invitation.";
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar, "QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek"))
			{
				link.l8 = "Can you tell me where to look for Andre Abel?";
				link.l8.go = "Andre_Abel_Quest_TavernOwner_Dialog_1";
			}
			if(CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar, "GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Hey, didn't " + pchar.GenQuest.CaptainComission.Name + "come in?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Don't you know, where I should look for " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_1";
					}
				}

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Don't you know, where I can find captain of patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l9.go = "CaptainComission_Tavern7";
				}
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Hey, was " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + " here?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Do you know something about captain of patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}
					}
				}
			}
			if(CheckAttribute(pchar, "GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Can you tell me where to find a gentleman by name " + pchar.GenQuest.Hold_GenQuest.Name + "?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "I happen to find ship's documents....";
				link.l11.go = "ShipLetters_4";
			}

                        //ОЗГ
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if(pchar.questTemp.Headhunter == "hunt_carlos" && npchar.city == pchar.questTemp.Headhunter.City)
	    		{
	    			link.l12 = "Can you tell me where to look for Carlos Cashier?";
	    			link.l12.go = "Seek_Carlos";
	    		}
			}

			//zagolski. начальный квест пирата
			if(CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "1" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
			{
				if (!CheckAttribute(pchar, "questTemp.pirateStartQuest.TavernInfo"))
				{
					link.l12 = "Listen, my friend, can you tell me if no one is selling slaves here?";
					link.l12.go = "pirateStartQuest_Tavern";
				}
				else
				{
					if (sti(pchar.money) >= 500)
					{
						link.l12 = "I brought you 500 piastres. Tell me what you know.";
						link.l12.go = "pirateStartQuest_Tavern_2";
					}
				}
			}
			//Lipsar квест История Давней дружбы--->
				if(CheckAttribute(Pchar, "Quest.Luke") && Pchar.Quest.Luke == "1" && NPChar.City == "LaVega")
				{
					link.l13 = "Listen, I'm looking for the man who was sitting at the table to the right of the door. Do you know where he is?";
					link.l13.go = "LukeQuest_1";
					sld = CharacterFromID("Maks");
					ChangeCharacterAddressGroup(sld, "none", "none", "none");
				}
				if(CheckAttribute(Pchar, "Luke.SpawnMaks") && Pchar.Luke.SpawnMaks == "1")
				{
					sld = CharacterFromID("Maks");
					if(NPChar.Location == sld.City)
					{
						link.l13 = "Listen, I'm looking for a man named Maximilian Weber. Do you know where he is?";
						link.l13.go = "MaksQuest_1";
					}
				}
				//<---Lipsar квест История Давней дружбы

			link.l14 = "Do you happen to have any information about how my colleagues are doing at sea?";
			link.l14.go = "PGGInfo";

			link.l15 = "Thanks, nothing. Goodbye.";
			link.l15.go = "exit";
		break;

		//-------------------------------------------
		case "PGGInfo":
			int rep = pchar.reputation;
			int repcheck = 40;
			if (IsCharacterPerkOn(pchar, "Adventurer"))
			{
				repcheck = 10;
			}

			if (rep < repcheck)
			{
				dialog.text = "I may know, but a person with your reputation cannot be trusted with such information. So get the hell out of here with such questions, Cap!";
				link.l1 = "Well, okay, I'll do it!";
				link.l1.go = "exit";
			}
			else
			{
				int cost = 4000 + makeint(500 * sti(PChar.rank) * MOD_SKILL_ENEMY_RATE*3/2);
				if (IsCharacterPerkOn(pchar, "Agent"))
				{
					cost = makeint(cost/2);
				}
				dialog.text = "Hmm, well, maybe I know something... But it won't be cheap, Cap. I will ask you for this "+cost+" and not a penny less! Are you satisfied?";
				if (sti(pchar.money) >= cost)
				{
					link.l1 = "Okay, here's your money. Now tell me what you know.";
					link.l1.go = "PGGInfo_2";
				}
				link.l2 = "Maybe sometime later.";
				link.l2.go = "exit";
			}
		break;

		case "PGGInfo_2":
			int cost1 = 4000 + makeint(500 * sti(PChar.rank) * MOD_SKILL_ENEMY_RATE*3/2);
			if (IsCharacterPerkOn(pchar, "Agent"))
			{
				cost1 = makeint(cost1/2);
			}
			AddMoneyToCharacter(pchar, -cost1);
			pchar.buyPGGinfo = 1;//купили инфо
			SaveCurrentQuestDateParam("buy_PGG_info");
			AddDialogExitQuestFunction("OpenPGGInformation");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "pirateStartQuest_Tavern":
			dialog.text = "Are you serious?! In the neighboring settlement of pirates, such cases are solved very simply.";
			link.l1 = "I was there. Now they have nothing, and I can't wait - a very good deal is falling through. I only have a couple of days, then I won't need it.";
			link.l1.go = "pirateStartQuest_Tavern_1";
		break;
		case "pirateStartQuest_Tavern_1":
			dialog.text = "Hmm, well, maybe I know something... But I won't talk for free, I don't do charity work. My information is worth 500 piastres. Pay or leave.";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "Okay, here's 500 piastres for you... Tell me what you know.";
				link.l1.go = "pirateStartQuest_Tavern_2";
			}
			else
			{
				link.l1 = "I don't have enough money... I'll be back when I get it.";
				link.l1.go = "exit";
				pchar.questTemp.pirateStartQuest.TavernInfo = "";
			}
		break;
		case "pirateStartQuest_Tavern_2":
			AddMoneyToCharacter(pchar, -500);
			dialog.text = "Well, I don't know. This case is under jurisdiction, so no one will offer you slaves directly. The planters buy themselves wherever they can find them. Unless you ask the smugglers. But the pirates took over this business a long time ago, hardly anyone will decide to openly covet their monopoly...";
			link.l1 = "Clear. Do you know if the schooner Sentblue has recently entered your port?";
			link.l1.go = "pirateStartQuest_Tavern_3";
		break;
		case "pirateStartQuest_Tavern_3":
			dialog.text = "'SentBlue'? No, she definitely didn't come in. And the name is not familiar to me.";
			link.l1 = "Okay, thanks. You've been a great help to me. See you later.";
			link.l1.go = "exit";

			PChar.questTemp.pirateStartQuest = "2";
			pchar.questTemp.pirateStartQuest.City2 = npchar.city;
			DeleteAttribute(pchar, "questTemp.pirateStartQuest.TavernInfo");
			AddQuestRecord("pSQ", "2");
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
		break;


		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("How do you say? " + pchar.GenQuest.Hold_GenQuest.Name + "? Hmm, I've never heard of such a thing.",
						"Do you know for sure that he is from our settlement? I've just never heard of it.",
						"There has never been such a thing in our settlement. I haven't heard how long I've lived here.");
					link.l1 = "Are you sure?";
					link.l1.go = "hold_genquest2";
				break;

				case 1:
					switch (drand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "to the church";
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "to the shipyard";
								pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "to the church";
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "to the usurer";
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "to the store";
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					}
					dialog.text = "Go to " + pchar.GenQuest.Hold_GenQuest.foundStr + ", he is usually there.";
					link.l1 = "Thank you, I will definitely come by.";
					link.l1.go = "hold_genquest3";
				break;

				case 2:
					dialog.text = LinkRandPhrase(
						RandPhraseSimple("What do you say? " + pchar.GenQuest.Hold_GenQuest.Name + "? Hmm, I've never heard of such a thing. Are you sure that he is from our settlement?",
						"Eh-heh-heh... God alone knows where to look for him now, either in heaven or in hell. He died... he's been dead for two years now, and everyone is asking about him, sniffing around, they don't give him any peace, poor guy..."),
						RandPhraseSimple("You won't find him anymore, in this world that's for sure. Not so long ago, he died of yellow fever... God rest his soul... And what a tough guy he was! In his youth, they say, he did such things that God forbid! And go ahead - the bride has come - and remember her name...",
						"Ek, missed! He moved out a long time ago. Either he went to the children, or to Europe - no one knows. I just packed up my stuff and took off."),
						"Ah, that's not it " + pchar.GenQuest.Hold_GenQuest.Name + " are you looking for what suddenly got rich and bought yourself a house in New Albion? But there were times when I treated him to rum on loan! He owes me money to this day. So go ahead and get it now! No, people don't remember the good...");
					link.l1 = "Clear. Well, thanks for that, too.";
					link.l1.go = "hold_genquest4";
				break;

				case 3:
					dialog.text = "And where to look for him, if not in our tavern? He comes here often - he pours old sins with rum, hehe. You come back later, if he shows up, I'll tell him to wait for you.";
					link.l1 = "Thanks, I'll come in.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;

		case "hold_genquest2":
			dialog.text = "How can I not be sure, if I know all the local settlers as one. I've been keeping a tavern for tea for years\n"+
				"I've seen them all in different forms - whom my wife drags home, who always gets to the harbor with a full hold himself, and who had to be put out in return. And you are 'sure' to me!";
			link.l1 = "Well, thanks for that...";
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;

		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen"));
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;

		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("ate", "la"));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			DialogExit();
		break;

		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");
		break;

		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("He often comes here, but now something is not visible. Look me up from time to time, if he shows up, I'll tell him to wait for you.", "He comes here often. If you come in later, you'll probably find him.", "Come in from time to time, he comes here often. I'll tell him you were looking for him.");
			link.l1 = "Thanks, I'll come back later...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;

		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CaptainComission_3":
			dialog.text = "I came in. He must be sitting here somewhere...";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.CaptainComission.Speak_Tavern");
		break;

		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Who doesn't know about him? It's been the talk of the settlement for days now.";
			link.l1 = "Can you tell me more?";
			link.l1.go = "CaptainComission_Tavern2";
		break;

		case "CaptainComission_Tavern2":
			dialog.text = "But it's hard to believe, because neither the owner of this vessel nor the goods have been found... They are still combing all the bays.";
			link.l1 = "Really? No one from the team confessed where the cache is?";
			link.l1.go = "CaptainComission_Tavern3";
		break;

		case "CaptainComission_Tavern3":
			dialog.text = "None!.. I don't understand why the governor believed this slander so easily. After all, captain  " + pchar.GenQuest.CaptainComission.Name + " was in good standing, and how he kept the team - any admiral would envy, take my word for it.";
			link.l1 = " Where should I look for the surviving team members?";
			link.l1.go = "CaptainComission_Tavern4";
		break;


		case "CaptainComission_Tavern4":
			dialog.text = "Well, I do not know that, they took them all away... Although no, there is one left, but it is unlikely to be of any use to you. He is shell-shocked, he was a gunner at " + pchar.GenQuest.CaptainComission.Name + ". He was found unconscious in a bay two days after that unfortunate incident. At first, they identified the hospital as a hero, and when things took a different turn, they were put in a casemate and tried to interrogate, but then they decided that they still needed to be treated.";
			link.l1 = "So is he in the settlement now?";
			link.l1.go = "CaptainComission_Tavern5";
		break;

		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Yes, his name is " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + ", sometimes he comes here, begs for rum. If I see him, I'll tell him to wait for you.";
			link.l1 = "Thanks, I'll come back later.";
			link.l1.go = "CaptainComission_Tavern6";
		break;

		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar, "GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "How not to know? Of course I know. What do you need him for?";
			link.l1 = "I have a case for him.";
			link.l1.go = "CaptainComission_Tavern8";
		break;

		case "CaptainComission_Tavern8":
			dialog.text = "You would be careful with this 'case', " + GetAddress_Form(pchar) + ". " + pchar.GenQuest.CaptainComission.Name + " was captured on suspicion of an official crime, and now the governor's bloodhounds are scouring the island in search of his accomplices.";
			link.l1 = "However... What has he done?";
			link.l1.go = "CaptainComission_Tavern9";
		break;

		case "CaptainComission_Tavern9":
			dialog.text = "I don't know how true this is, but they say that he hid the cargo that he confiscated from a passing pirate ship. But no one managed to find either the pirate or the cargo. I don't understand why the governor believed this slander so easily. After all, captain " + pchar.GenQuest.CaptainComission.CapName + "  was in good standing, and he's an excellent soldier, believe me, " + GetAddress_Form(pchar) + ".";
			link.l1 = "Well, thanks for the warning. Have a nice day.";
			link.l1.go = "CaptainComission_Tavern10";
		break;

		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = " Why do you need her?";
			link.l1 = "There is a case for her...";
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = "Half of the men in our settlement have business with her. If the women had caught her, they would have thrown her naked outside the city gates.";
			link.l1 = "Oh. "+ GetSexPhrase("It looks like I'm at the back of a long queue. If anyone asks her, tell them wait for me first", "I see") +"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;

		case "EncGirl_3":
			dialog.text = "He often comes here hoping to find a job, but now something is not visible. Look me up from time to time, if he shows up, I'll tell him to wait for you.";
			link.l1 = "Thanks, I'll come back later...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, so you are "+ GetSexPhrase("captain who brought", "the girl who brought") +" my prodigal son with a young bride?";
				link.l1 = "Yes, I helped them escape.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, revealed "+ GetSexPhrase("you, benefactor", "you, benefactress") +". Are you expecting a reward?";
				link.l1 = "Well, not that there are awards, but it would be nice to hear gratitude.";
				link.l1.go = "EncGirl_6";
			}
		break;

		case "EncGirl_5":
			dialog.text = "I am very grateful to you for not leaving my child in a difficult situation and helping him to get out of such a delicate situation with honor. Let me thank you as much as I can. Accept this modest sum and a gift from me personally.";
			link.l1 = "Thank you, it was a pleasure to help these young people.";
			link.l1.go = "EncGirl_5_1";
		break;

		case "EncGirl_6":
			dialog.text = "What thanks?! What is the gratitude for?! Not only has this blockhead been hanging around without work for six months, he's also found time to be nice! Yes, I was already running my own business at his age. And look, he's gone hunting! The governor has a marriageable daughter, and this one has brought some kind of rootless slut, God forgive me, and is asking for parental blessing!";
			link.l1 = "Hmm, so you don't believe in sincere feelings?";
			link.l1.go = "EncGirl_6_1";
		break;

		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_6_1":
			dialog.text = "What kind of feelings are these?! What kind of feelings are you talking about? An adult, like a person, but there too... Feelings! It should be a shame for you young people to indulge in such matters, and to contract as a pimp. The girl was torn out of her parents' nest and my sucker's life was ruined. There will be no gratitude to you. Goodbye.";
			link.l1 = "Well, you don't get sick either...";
			link.l1.go = "EncGirl_6_2";
		break;

		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ate", "la"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", "a"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Let's take a look! Hm... You're captain yourself. I think you should go to the portmaster.";
				link.l1 = "Thanks for the advice.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Let's take a look! Oh! judging by the name, they belong to one of my regular visitors, a very decent man. I can hand over the documents to the owner myself.";
				link.l1	= "Probably not ...";
				link.l1.go = "exit";
				link.l2 = "Glad that I was useful for him.";
				link.l2.go = "ShipLetters_end";
			}
		break;

		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "3");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//эскорт-пассажиры
		case "work":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			int  iOrionRankReq = 1;
			if (!bQuestsRank) iOrionRankReq = 5;	//Если стоит галочка, то убрать требования рангов у квестов
			if (!CheckAttribute(PChar, "QuestTemp.AndreAbelQuest_StartQuest") && PChar.location == "FortFrance_tavern" && sti(pchar.rank) >= iOrionRankReq)
			{
				dialog.text = "Talk to that guy over there, to the right of the stairs. He's got some kind of problem.";
				link.l1 = "Thank you!";
				link.l1.go = "exit";
				Log_TestInfo("Сопровождение флейта 'Орион' - сгенерился квестодатель в sit, sit7");
				PChar.QuestTemp.AndreAbelQuest_StartQuest = true;
				PChar.QuestTemp.AndreAbelQuest = true;

				// Потереть для начала новой игры -->
				sld = GetCharacter(NPC_GenerateCharacter("Andre_Abel" , "officer_19", "man", "man", 10, FRANCE, -1, true));
				FantomMakeCoolFighter(sld, 10, 30, 35, "blade9", "pistol2", 10);
				FantomMakeCoolSailor(sld, SHIP_FLEUT, "Orion", CANNON_TYPE_CANNON_LBS16, 30, 30, 30);
				sld.name = "Andre";
				sld.lastname = "Abel";
				sld.SaveItemsForDead = true; // сохранять на трупе вещи
				sld.DontClearDead = true; // не убирать труп через 200с
				sld.dialog.FileName = "Quest\Andre_Abel_Dialog.c";
				sld.greeting = "cit_quest";
				LAi_SetSitType(sld);
				LAi_SetImmortal(sld, true);	// До поры нельзя убить
				SetCharacterGoods(sld, GOOD_SILK, 700);
				SetCharacterGoods(sld, GOOD_TOBACCO, 500);
				FreeSitLocator("FortFrance_tavern", "sit7");
				ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
				SetFunctionTimerCondition("Andre_Abel_Quest_1Day_Left", 0, 0, 1, false);
				// <-- Потереть для начала новой игры
				break;
			}
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("I don't care who I serve - money has no nationality. But I'm not going to help you, because you're sailing under the " + NationNameGenitive(sti(pchar.nation)) + " flag .", "I'm just a simple tavern owner, but I have no desire to cooperate with " + NationNameAblative(sti(pchar.nation)) + ".");
				link.l1 = RandPhraseSimple("Hmm, your right...", "Well, as you know...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("There are usually enough passengers. But it's unlikely that there will be such a simpleton among them to decide to travel on your ship. Notoriety runs ahead of you, and the reputation of an honest captain still needs to be earned.", "I am often approached by merchants who need an escort. But notoriety follows you around, and I will not recommend your services to anyone. I value my reputation more.");
				link.l1 = RandPhraseSimple("Yes, you believe less different gossip...", "Yes, you don't shut everyone's mouths...", "Eh, the cowardly people have gone...");
				link.l1.go = "exit";
				break;
			}
			dialog.text = "There is a job if you are not afraid to go to pirate settlements or ports of enemy nations. This is usually the only thing that merchants turn to me for - they are looking for an escort, then passengers who do not dare to go to the port authority. Are you interested in something in particular?";
			link.l1 = "Well, it's not scary. I would take the escort.";
			link.l1.go = "work_1";
			link.l2 = "Are there any passengers? I'll take you to hell in your teeth, as long as you pay the money.";
			link.l2.go = "work_2";
			link.l3 = "No, this kind of work is not for me. Thank you.";
			link.l3.go = "exit";
		}
		else
		{
		dialog.text = "Where is your ship? Put your boat to the pier, then we'll talk about work.";
		link.l1 = "Hmm, that's right...";
		link.l1.go = "exit";
		}
		break;

		case "work_1":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 1 || bBettaTestMode)
    		{
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//при низком авторитете и на 7 класс не даём
				{
				dialog.text = "I'm sorry, but I don't have anyone willing to travel with you.";
				link.l1 = "Understood. Whatever you say.";
                link.l1.go = "exit";
				break;
				}
				//конвой
                if (!CheckQuestAttribute("generate_convoy_quest_progress", "begin"))
                {
					if (GetCompanionQuantity(PChar) == COMPANION_MAX)
					{
						dialog.text = "Hmm, but you have too big a squadron for an escort. You should not lose your ships, not save someone else's.";
						link.l1 = "Come on, I won't lose mine, except to sell a couple... Okay, I'll come back later if I decide to.";
						link.l1.go = "exit";
					}
					else
					{
						if (drand(8) > 1)
						{
							dialog.text = "Well, then talk to that guy over there who came into the tavern. He asked about the escort today.";
							link.l1 = RandPhraseSimple("Do you know him well? Maybe some kind of pirate?", "And who is he? Is it worth dealing with?");
							link.l1.go = "ConvoyAreYouSure";
						}
            			else
            			{
            				dialog.text = "Today, as luck would have it, no one approached about the escort. Come back in a couple of days, maybe someone will show up.";
							link.l1 = RandPhraseSimple("Okay, there is no trial either.", "Yes, it was not lucky... Well, goodbye.");
							link.l1.go = "exit";
						}
            		}
                }
				else
				{
					dialog.text = "Did you decide to assemble a caravan? You have an escort, finish with him first, then look for another one. Otherwise, you won't know who to protect in case of an attack.";
					link.l1 = RandPhraseSimple("Here's the problem... Well, good day.", "Yes, indeed, I did not think about it. Well, goodbye.");
					link.l1.go = "exit";
        		}
    		}
    		else
    		{
				dialog.text = "No one is here today. Come back in a couple of days.";
				link.l1 = "Okay. Whatever you say.";
                link.l1.go = "exit";
    		}
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 1 || bBettaTestMode)
    		{
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//при низком авторитете и на 7 класс не даём
				{
				dialog.text = "I'm sorry, but I don't have anyone willing to travel with you.";
				link.l1 = "Understood. Whatever you say.";
                link.l1.go = "exit";
				break;
				}
		         // пассажир
				if (drand(6) > 1)
				{
					dialog.Text = "That guy came into the tavern, he recently asked a passing ship where he wanted to get somewhere. If you want, talk to him.";
					link.l1 = RandPhraseSimple("What kind of guy? Maybe some kind of crook, or wanted?", "And who is he? Will there be any problems with him?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "No, no one asked today. Maybe another day...";
					link.l1 = RandPhraseSimple("Well, no, that's not it. What is there ...", "Yes, it was not lucky... Well, goodbye.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "No one is here today. Come back in a couple of days.";
				link.l1 = "Okay. Whatever you say.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Who knows. You asked - I answered.", "Well, that's up to you. I wouldn't vouch for anyone here.", "Decide for yourself, all sorts of people come to me. This is a tavern, not the governor's residence.");
			Link.l1 = "Well, thanks, we'll bargain now.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Who knows. You asked - I answered.", "Well, that's up to you. I wouldn't vouch for anyone here.", "Decide for yourself, all sorts of people come to me. This is a tavern, not the governor's residence.");
			Link.l1 = "Okay, let's find out what kind of guy he is.";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "room":
			if (CheckAttribute(PChar, "questTemp.BSPrologue.WaitingForNassauSiege") && pchar.location == "Pirates_Tavern")
			{
				dialog.text = "I'm sorry, Captain, but all the seats are taken now.";
				link.l1 = "Too bad...";
				link.l1.go = "exit";
				break;
			}
			//Квест Виспер
			if (CheckAttribute(pchar, "Whisper.EsFriendTown") && pchar.location == pchar.Whisper.EsFriendTown+"_tavern")
			{
				dialog.text = "Sorry, Captain, but all the seats are occupied right now.";
				link.l1 = "Sorry...";
				link.l1.go = "exit";
				break;
			}
			//Квест Виспер

			if (CheckAttribute(pchar, "ContraInterruptWaiting"))
			{
				dialog.text = "I'm sorry, but I can't rent a room right now. Just a couple of minutes ago, a crowd of soldiers burst into the tavern and began searching my rooms. They're looking for smugglers, you know. Only they spoil my business with their showdowns... Come back later, Captain.";
				if (sti(npchar.nation == PIRATE))
				{
					dialog.text = "I'm sorry, but I can't rent a room right now. The last tenant decided to set up a brothel in it, or worse. The bed is broken, and the smell is like in a pigsty... Come back later, Captain.";
				}
				link.l1 = "Clear.";
				link.l1.go = "exit";
				break;
			}

   			/*if (chrDisableReloadToLocation || CheckAttribute(pchar, "questTemp.different.Church_NightGuard")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "The room is occupied now, " + GetAddress_Form(NPChar) + "I can't help you.";
				link.l1 = "Sorry, very sorry...";
				link.l1.go = "exit";
				break;
			}*/
			if (CheckAttribute(pchar, "questTemp.State.Open") && npchar.id == "Tortuga_tavernkeeper")//исп.линейка, квест №6, блокировка спать в комнате
			{
				dialog.text = "You paid me a week in advance, I can't take any more money from you. The room is yours, go and rest...";
				link.l1 = "Okay, buddy, thanks.";
				link.l1.go = "exit";
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "Do you want to rent a room? Not a problem. That'll be 100 coins, and you can go there.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Take your money, open the room, buddy...";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Hmm, I'll probably come back later...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "The room is yours, go and rest...";
				link.l1 = "Okay, buddy, thanks.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "The Girl in the Jungle"
			if(CheckAttribute(pchar, "GenQuest.EncGirl.city") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "Do you want to rent a room? Not a problem. That'll be 50 coins, and you can go there.";
					if (sti(pchar.money) >= 50)
					{
						link.l1 = "Take your money, open the room, buddy...";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -50);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Hmm, I'll probably come back later...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тётки в пампасах
				{
					dialog.text = "The room is yours, go and rest...";
					link.l1 = "Okay, buddy, thanks.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "The Girl in the Jungle"
			dialog.text = "How long are you planning to stay?";
			if(!isDay())
			{
				link.l1 = "Until morning.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Until the night.";
				link.l1.go = "room_night";
				link.l2 = "Until the next morning.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "It will cost you 5 gold.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Deal. Here's your money.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("Are you renting out the royal chambers? No, for that price, I'd rather sit in the common room.",
            "Alas, apparently, such a luxury as sleeping on a bed is not for my wallet. I'll spend the night in the common room.");
			link.l2.go = "hall_day_wait";
			link.l3 = "Not now. Let's talk about something else.";
			link.l3.go = "int_quests";
		break;

		case "room_day_next":
			dialog.text = "It will cost you 10 gold.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Deal. Here's your money.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("Are you renting out the royal chambers? No, for that price, I'd rather sit in the common room.",
            "Alas, apparently, such a luxury as sleeping on a bed is not for my wallet. I'll spend the night in the common room.");
			link.l2.go = "hall_day_wait";
			link.l3 = "Not now. Let's talk about something else.";
			link.l3.go = "int_quests";
		break;

		case "room_night":
			dialog.text = "It will cost you 5 gold.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Deal. Here's your money.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("Are you renting out the royal chambers? No, for that price, I'd rather sit in the common room.",
            "Alas, apparently, such a luxury as sleeping on a bed is not for my wallet. I'll spend the night in the common room.");
			link.l2.go = "hall_night_wait";
			link.l3 = "Not now. Let's talk about something else.";
			link.l3.go = "int_quests";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (cRand(3) == 1)
            {
                Dialog.text = "Get out, you bastard! There's nothing to sit in the common room for free.";
				link.l1 = "Okay, okay... I'm already leaving.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (drand(1) == 1)
            {
                Dialog.text = "Get out, you bastard! There's nothing to sit in the common room for free.";
				link.l1 = "Okay, okay... I'm already leaving.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;

		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Dear ones, I ask you to stop this mess in my tavern, or I will call the guards!";
			link.l1 = "Okay, okay, I'm already leaving.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		//==> eddy. квест мэра, вопросы не замечал ли шпиона
		case "SeekSpy_Seen":
			dialog.text = NPCStringReactionRepeat("Hmm, let me think... You know, there's one guy who doesn't inspire confidence in me personally. He looks like an ordinary citizen, but he turns around here and in the city, he has strange questions. He's unlikely to show up here-I turned him down yesterday, but look in the city.",
				"We have already talked about this topic, I have nothing more to say to you.", "The same thing again... I've already told you everything.", "How many times can I ask about the same thing?!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thank you, buddy. Well, I'm going to look for this guy.", "Hmm, well, I'm sorry...",
                      "Hmm, yeah...", "Sorry, buddy...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "SeekSpy_NotSeen":
			dialog.text = NPCStringReactionRepeat("No, I didn't see anyone that made me suspicious.",
				"We have already talked about this topic, I have nothing more to say to you.", "The same thing again... I've already told you everything.", "How many times can I ask the same thing?!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Well, thanks for that, buddy.", "Hmm, I'm sorry...",
                      "Hmm, yeah...", "Sorry, buddy...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		//==> homo линейка Блада
		case "TStep_0":
			dialog.text = "Right and straight to the end. I haven't talked to you.";
			link.l1 = "Thank you.";
			link.l1.go = "Exit";
			int n= FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = false;
		break;

		case "TStep_1":
			dialog.text = "What is your business with me, dear doctor?";
			link.l1 = "A matter of everyday life... I could use a few cutlasses and a couple of pistols, just in case, dear friend. Can you arrange this, or can you point to a person who could pull something like this off? You know, there's no point in me going to the store...";
			link.l1.go = "TStep_2";
		break;

		case "TStep_2":
			dialog.text = "Well, of course not.";
			link.l1 = "Can't you? Or is there no point?";
			link.l1.go = "TStep_3";
            if (makeint(pchar.money) >= 500)
            {
    			link.l1 = "Didn't I mention that I have a bonus for a knowledgeable person in the amount of... well, say, three hundred piastres? And remember how I treated your daughter, sparing no effort and time.";
    			link.l1.go = "TStep_4";
            }
		break;

		case "TStep_3":
			dialog.text = "I can't help you, Doctor.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
		break;

		case "TStep_4":
			dialog.text = "Of course I have what you need, Dr. Blood. Mr. Griffin, whom you fixed a fracture not so long ago, is an old gunsmith in life. His house is located near the estate of Governor Steed - go to him. I'm sure he won't refuse you.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -300);
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1";
			AddQuestRecord("WeaponsForEscape", "2");

		break;

		case "TStep_5":
            pchar.questTemp.CapBloodLine.QuestRaff = false;
			dialog.text = "I think I remember this one... Or it wasn't him... It doesn't seem to be him...";
            if (makeint(pchar.money) >= 200)
            {
    			link.l1 = "Will two hundred refresh your memories?";
    			link.l1.go = "TStep_6";
            }
			link.l2 = "Is he right or not?";
			link.l2.go = "TStep_7";
		break;

		case "TStep_6":
            AddMoneyToCharacter(pchar, -200);
			dialog.text = "Of course! Of course it's him! I came by quite recently, said something about buying a ship... I don't know exactly which one or who has it.";
			link.l1 = "What do you know? It seems to me that for 200 piastres you can remember a lot more details than just the fact that he was here.";
			link.l1.go = "TStep_8";
		break;

		case "TStep_7":
			dialog.text = "No, alas... Definitely not him. Confused - it happens.";
			link.l1 = "Annoying...";
			link.l1.go = "TStep_10";
		break;

		case "TStep_8":
			dialog.text = "I think you'll find it at the shipyard if you hurry up.";
			link.l1 = "Thank you very much.";
			link.l1.go = "TStep_9";
		break;

		case "TStep_9":
            AddQuestRecord("UsurerQuest", "2");
            sld = GetCharacter(NPC_GenerateCharacter("QStranger", "citiz_7", "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.greeting = "Gr_bankeer";
            sld.name = "Alex";       //fix имени
            sld.lastname = "Winner";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
            LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "Bridgetown_Shipyard", "goto", "goto1");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "TStep_10":
            sld = GetCharacter(NPC_GenerateCharacter("QStranger", "citiz_7", "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.greeting = "Gr_bankeer";
            sld.name = "Alex";    //fix имени
            sld.lastname = "Winner";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
            LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "CommonRoom_MH7", "goto", "goto1");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		//==> Sinistra пролог Анжелики Тич
		case "AT_pr_1":
			dialog.text = "You know, if my guests start a fight here because of your fault, I will be forced to file a claim covering damages in your name.";
			link.l1 = "Senior " + npchar.name+", you like no one else, are able to pronounce the word 'get out' so unobtrusively and tactfully.";
			link.l1.go = "AT_pr_2";
		break;
		case "AT_pr_2":
			dialog.text = "No way, I'm glad to have any client.";
			link.l1 = "Of course, of course.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AT_pr_3";
		break;
		case "AT_pr_3":
			dialog.text = "Should I pour something?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AT_pr_3";
		break;
		//зачарованный город
		case "MCTavern":
			dialog.text = "No, no! It's upstairs, the guest, they say he really is a werewolf, you "+ GetSexPhrase("brave man", "brave girl") +"Please do something! If these people from the street break in here... I'm afraid to imagine what will happen!";
			link.l1 = "I do not know which of you is more afraid – you or those who are outside the door. Okay, I'll talk to your guest.";
			link.l1.go = "exit";
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.MC = "toCaracasWervolf";
			DeleteAttribute(&locations[reload_location_index], "reload.l2.disable");
			sld = GetCharacter(NPC_GenerateCharacter("CaracasWervolf", "trader_14", "man", "man", 10, PIRATE, -1, true));
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "CaracasWervolf";
			sld.location	= "Caracas_tavern_upstairs";
			sld.location.group = "goto";
			sld.location.locator = "goto1";
			sld.BreakTmplAndFight = true;
			sld.reactionOnFightModeOn = true;
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(sld, pchar);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		break;

		case "MCCaracasAfter":
			dialog.text = "Thank God I got rid of it! I had to open the door, because most of the crowd were my customers! A couple of broken bottles of rum is a small fee...";
			link.l1 = "I'm asking, what's wrong with the guest?";
			link.l1.go = "MCCaracasAfter_1";
		break;
		case "MCCaracasAfter_1":
			dialog.text = "Oh, with a werewolf? They sent him to the stake, of course. Didn't you see the smoke from the fire coming from the church? That's how he burns down, this werewolf...";
			link.l1 = "Oh, and you guys are fast, I'll see.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MC_endCaracas");
		break;

		//*************************** Квест "Orion fluyt accompaniment"Орион"" **********************
		case "Andre_Abel_Quest_TavernOwner_Dialog_1":
			dialog.text = "Ah, captain " + GetFullName(pchar) + "! Andre Abel was killed two days ago. The assassins were waiting for him right at the entrance to the tavern... Oh, what a pity! What a pleasant man he was - generous, courteous, never raised his voice, never got into fights. And so, come on - such a death! Ay-ay-ay...";
			link.l1 = "Wow!.. I did not expect such a turn. Sincerely sorry for the poor guy, sincerely sorry...";
			link.l1.go = "Andre_Abel_Quest_TavernOwner_Dialog_2";
		break;

		case "Andre_Abel_Quest_TavernOwner_Dialog_2":
			DialogExit();
			AddQuestRecord("Andre_Abel_Quest", "13");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "a"));
			CloseQuestheader("Andre_Abel_Quest");
			pchar.questdata.FleitOrion = 1;
			DeleteAttribute(pchar, "QuestTemp.AndreAbelQuest");
			DeleteAttribute(PChar, "QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek");
			pchar.questdata.FleitOrion = 1;
		break;

		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "I don't know much about this... You'd better ask one of the regulars.";
			link.l1 = "Okay, thanks.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;

		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "We do not service in debt, "+ GetSexPhrase("sir", "miss") +".";
			link.l1 = "I'm used to pay in hard cash, my dear. Or gold is no longer accepted here?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;

		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Sorry, Mr."+ GetSexPhrase("dean", "Ms.") +"Captain, but your friend is in debt, and I thought...";
			link.l1 = "Think less, my dear, and serve more quickly. So how much does my valiant friend owe you?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;

		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*10;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If it's simple and gives it away right away"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", "+ GetSexPhrase("sir", "miss") +"Captain, and he left the church books as collateral-that's all he had with him of value.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Hold the coins and give me the manuscripts. Be careful, this is not a keg of ale, but the writings of God's righteous!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Wait a bit... I'm going to bring you this money now.";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If it's not simple"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", "+ GetSexPhrase("sir", "miss") +" captain.";
				link.l1 = "I will pay his debt and take back what he left as collateral.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;

		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даём рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "No, "+ GetSexPhrase("sir", "miss") +", that won't do.";
			link.l1 = "What does 'won't do' mean?! Cap's debt is being paid off-he's happy. You get your money, you're happy. They return the deposit to me - I'm satisfied with it. Everyone is happy, and everything is fine. Why won't it 'go'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Because I don't need the money. I know this captain of yours too well, and I didn't even hope that one day he would be able to pay off and demand these manuscripts back.";
			link.l1 = "How is it that you don't need money? So you wanted to keep the books? But why, in the name of God?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "Just in the name of the Lord, "+ GetSexPhrase("sir", "miss") +". My little son was very ill, and my wife and I made a vow that we would donate to the temple if the Creator would rid the child of fever. God's mercy is boundless, the child is alive and well, and now we must fulfill our vow. And so, just in time, captain appears " + PChar.GenQuest.ChurchQuest_1.CapFullName + " and leaves church books as collateral. I could not allow such indecency - to be paid for by the Word of God for drinking - and decided today to donate books to our parish priest.";
			link.l1 = "There is no doubt, it is a good thing, but you should know that these manuscripts belong to another priest, that is, not even a priest, but a powerful bishop, my spiritual mentor, who will be very angry, and possibly curse the one who encroaches on them... I would like to buy them from you and deliver them to him safely.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = ""+ GetSexPhrase("Sir", "Miss") +" captain... Of course I will, and I don't need any money. Just put in a good word to the bishop, may he bless us and honor the fulfillment of the vow...";
			link.l1 = "Of course, my dear, the vow will be counted to you and your wife, because, after all, you sacrificed the proceeds by returning the manuscripts according to their affiliation, and it doesn't matter which church we go to, we all go under the same God. Give them to me, and good luck to you...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даём рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc"));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;

		case "Pirates_1":
			dialog.text = "Everywhere for you gentlemen"+ GetSexPhrase("", " and ladies") +"good luck, the Spaniards are seeing things! They were completely stupefied by the rich prizes... Not La Kerosene, but Lucky Rosin, or Lucky Violinist - that means. Maybe you've heard? Actually, my name is Waynard d'Alto, though.. This is unlikely to tell you anything. Nowadays, few people are interested in history, hehe. Well, all right.";
			link.l1 = "Wait... I seem to remember. You are the same privateer who quarreled with the French crown and disappeared a couple of years ago! The devil and his pitchfork! What a meeting! And I've heard that the Violinist sometimes chooses to pinch the Spaniards and the French for old times' sake!";
			link.l1.go = "Pirates_2";
		break;
		case "Pirates_2":
			dialog.text = "Take it easy on the tacks, "+ GetSexPhrase("sir", "miss") +". Those who gossip a lot are attracted by the bad wind. If you know what I'm talking about.";
			link.l1 = "Yes, perhaps you are right. Let's leave the empty talk and get down to business.";
			link.l1.go = "meeting";
		break;

		case "Charles_1":
			dialog.text = "Well, it's right that you don't believe. People lie... Well, one day a Spanish caravan turned up, which was swept away by a storm, so I had to escort it to Jamaica. It wasn't to Havana, really, hehe hehe...";
			link.l1 = "Oh, there's something you're not telling me... Okay, I won't pry. Let's get down to business.";
			link.l1.go = "meeting";
		break;

		case "Portobello_1":
			dialog.text = "Yes, yes, yes, that's how it was, " + GetAddress_Form(NPChar) + "! People are telling the truth. Everyone in the archipelago knows about the exploits of the Catalan Fox!";
			link.l1 = "And I've also heard that you're at odds with Morgan. And that you spent a month in Port Royal Prison. And the fact that you escaped from the dungeons, pretending to be Lady Taylor...";
			link.l1.go = "Portobello_2";
		break;

		case "Portobello_2":
			dialog.text = "T-s-s... Don't talk about it so loudly, "+ GetSexPhrase("buddy", "girlfriend") +". Gossip is all that... gossips. Well, Morgan will never get me here, hehe.";
			link.l1 = "Okay, " + npchar.name + ", we chatted, now let's get down to business.";
			link.l1.go = "meeting";
		break;
		
		case "FortFrance_1":
			dialog.text = "Hehe hehe! Information, you say? You've come to the right place, Captain. I heard that one trader, Virginie Audric, landed on the reefs, somewhere between our blessed Martinique and Guadeloupe. No one has ever heard of reefs in this place, so I think this reef had at least 12 guns! Heh-heh-heh! Well, don't you need a mug of rum to calm your nerves? Heh heh heh!";
			link.l1 = "Terribly funny, " + npchar.name+". Express yourself more clearly, otherwise you will feel sick laughing.";
			link.l1.go = "FortFrance_2";
		break;
		
		case "FortFrance_2":
			dialog.text = "Should I be clearer? Hehe. Well, from all points of view, it's time to be serious for a bit.";
			link.l1 = "You're kidding. YOU? ARE SERIOUS? Of course this is impossible. What was I thinking?";
			link.l1.go = "FortFrance_3";
		break;
		
		case "FortFrance_3":
			dialog.text = "Oh, "+ GetSexPhrase("buddy", "darling") +". I am absolutely serious. Heh heh heh heh. Really.";
			link.l1 = "Okay, " + npchar.name+". We laughed, now to the point.";
			link.l1.go = "meeting";
		break;
		
		case "Nassau_1":
			dialog.text = "Ha, the young ones who didn't smell life properly! Well, get excited, get excited, build yourself up "+ GetSexPhrase("sea wolf", "sea wolf") +", but be careful - don't run into someone really cool!";
			link.l1 = "E... Did I understand correctly? Your name is " + npchar.name+"?";
			link.l1.go = "Nassau_2";
		break;
		
		case "Nassau_2":
			dialog.text = "Yes, that's what my name has been since the minute I opened my throat announcing my birth, in some dirty shack on the outskirts of Lisbon.";
			link.l1 = "Well, my name is " + GetFullName(pchar)+".";
			link.l1.go = "meeting";
		break;
		
		//Инес Диас рассказывает историю о себе
		case "Istoria_InesDias_1":
			pchar.questTemp.Istoria_InesDias = "Istoria_InesDias";
			dialog.text = "Oh my God! I've told this story a hundred times already!";
			link.l1 = "I understand that you are terribly tired of telling everyone your life story, but maybe you will make an exception for me?";
			link.l1.go = "Istoria_InesDias_2";
			link.l2 = "So tell me one hundred and first, what's the matter? The tongue, the tea, without bones, will somehow withstand this test.";
			link.l2.go = "Istoria_InesDias_2";
		break;
		case "Istoria_InesDias_2":
			dialog.text = "Ha! Do you know how to convince people, you sucker! Okay, so be it, listen.";
			link.l1 = "So far, I don't hear anything but insults. Maybe you'll start the story after all?";
			link.l1.go = "Istoria_InesDias_3";
		break;	
		case "Istoria_InesDias_3":
			dialog.text = "You keep quiet, but listen, and don't interrupt your elders! It was a long time ago, about 30 years ago, and I was just a girl. I was dizzy with the sound of the sea, the smell of algae rotting on the shore, starry nights and hot hugs...";
			link.l1 = "Go on.";
			link.l1.go = "Istoria_InesDias_4";
			link.l2 = "I already understand everything. Let's get down to business.";
			link.l2.go = "meeting";
		break;		
		case "Istoria_InesDias_4":
			dialog.text = "Once upon a time, a young sailor from the military, what was his name? Oh, it doesn't matter, so he convinced me to sail with him to a fabulous country where you can get rich quickly and everyone lives happily.";
			link.l1 = "Did he mean the New World?";
			link.l1.go = "Istoria_InesDias_5";
			link.l2 = "I already understand everything. Let's get down to business.";
			link.l2.go = "meeting";
		break;
		case "Istoria_InesDias_5":
			dialog.text = "You are smart "+GetSexPhrase("guy", "girl")+". Yes, that's exactly how it was, as I said before - I was young, it was easy for me to turn my head, and I agreed with his crazy proposal.";
			link.l1 = "But how did an ordinary sailor get you on a warship? It's forbidden.";
			link.l1.go = "Istoria_InesDias_6";
			link.l2 = "I already understand everything. Let's get down to business.";
			link.l2.go = "meeting";
		break;	
		case "Istoria_InesDias_6":
			dialog.text = "You know everything! Ha, we came up with a cunning plan, as it seemed to us at the time, and he hid me in the hold among the bales of breadcrumbs.";
			link.l1 = "And what happened next?";
			link.l1.go = "Istoria_InesDias_7";
			link.l2 = "I already understand everything. Let's get down to business.";
			link.l2.go = "meeting";
		break;	
		case "Istoria_InesDias_7":
			dialog.text = "And then, of course, they found me. I turned out to be completely unsuited to sea rolling, so literally an hour after sailing, I began to scream, asking for help, thinking that I was dying, and my minutes were numbered. How do you order a young fool to behave when her stomach is about to pop out of her mouth?";
			link.l1 = "Go on.";
			link.l1.go = "Istoria_InesDias_8";
			link.l2 = "I already understand everything. Let's get down to business.";
			link.l2.go = "meeting";
		break;
		case "Istoria_InesDias_8":
			dialog.text = "My sailor was executed for violating the rules on the ship, and they were just deciding to let me go around in a circle, after which they dumped me for shark food, but fortunately a ship with a black flag appeared on the horizon.";
			link.l1 = "Out of the fire, into the flames, that's what it reminds me of.";
			link.l1.go = "Istoria_InesDias_9";
			link.l2 = "I already understand everything. Let's get down to business.";
			link.l2.go = "meeting";
		break;
		case "Istoria_InesDias_9":
			dialog.text = "And you are close to the truth. I was thrown into some cabin, during the battle, to take care of me after, by the will of providence, something did not work out there, and the pirates defeated these would-be warriors.";
			link.l1 = "And you fell into the hands of pirates?";
			link.l1.go = "Istoria_InesDias_10";
			link.l2 = "I already understand everything. Let's get down to business.";
			link.l2.go = "meeting";
		break;
		case "Istoria_InesDias_10":
			dialog.text = "Something like that. A very young boy opened my cabin. God, how handsome he was!I forgot my fears at once when I saw his figure in the doorway, his strong hand clutching a broadsword stained with blood.";
			link.l1 = "What happened next?";
			link.l1.go = "Istoria_InesDias_11";
			link.l2 = "I already understand everything. Let's get down to business.";
			link.l2.go = "meeting";
		break;
		case "Istoria_InesDias_11":
			dialog.text = "That's all you need to know! Don't embarrass the old woman!";
			link.l1 = "I didn't mean to...";
			link.l1.go = "Istoria_InesDias_12_1";
			link.l2 = "Are you embarrassed? Don't pretend, but there's nowhere to put a sample on you, and you're trying to play the shy girl.";
			link.l2.go = "Istoria_InesDias_12_2";
			link.l3 = "I already understand everything. Let's get down to business.";
			link.l3.go = "meeting";
		break;
		case "Istoria_InesDias_12_1":
			dialog.text = "You didn't want to? Are you kidding me?!";
			link.l1 = "Maybe you'll just tell me what happened after... how did you end up on the shore.";
			link.l1.go = "Istoria_InesDias_13";
		break;
		case "Istoria_InesDias_12_2":
			dialog.text = "How perceptive we are, it's crazy. You'll probably be good if you don't die prematurely.";
			link.l1 = "Continue your story, " + npchar.name+".";
			link.l1.go = "Istoria_InesDias_13";
		break;
		case "Istoria_InesDias_13":
			dialog.text = "Okay, okay, I'm already continuing. It was there, on the ship, that I met the one everyone now knows as Isenbrandt Jurksen. And then he was just a blue-eyed Handsome Guy, I guess he liked me too, huh! After all, it was on this very night that he became the commander of his first ship, having hacked down the former captain in a duel because of me.";
			link.l1 = "And what happened next?";
			link.l1.go = "Istoria_InesDias_14";
		break;
		case "Istoria_InesDias_14":
			dialog.text = "We swam together, and I loved this life, damn it! And then we quarreled over some trifle, and I equipped my ship, fortunately the piastres rang in my corset.";
			link.l1 = "Have you become captain of a pirate ship?";
			link.l1.go = "Istoria_InesDias_15";
		break;
		case "Istoria_InesDias_15":
			dialog.text = "Yes, damn it! And a good captain! All the merchants of these waters were afraid of me, there was a reward for my head, but I was lucky, and I escaped from the hands of my pursuers, or destroyed them.";
			link.l1 = "And? What happened next?";
			link.l1.go = "Istoria_InesDias_16";
		break;
		case "Istoria_InesDias_16":
			dialog.text = "And then I was wounded during the boarding of an English corvette, under the command of some persistent guy who had been chasing me for several months, and after recovering, I decided to quit all this business, and my health was already not the same, I suddenly wanted a quiet life somewheresomewhere on the shore, so I opened a tavern on this piece of land.";
			link.l1 = "An interesting story. Thanks for telling her, but let's talk about something else now.";
			link.l1.go = "meeting";
		break;

		//ОЗГ
		case "Seek_Carlos":
		if (pchar.questTemp.Headhunter.Chance == 1)
		{
			dialog.text = "Ha! So he's here somewhere, in the tavern! I saw him about five minutes ago. Look, he should be here.";
		}
		else
		{
			dialog.text = "Hmm... I had him about an hour ago. And now he's gone - to a brothel, it seems, he was going to.";
		}
		link.l1 = "Thank you! You've helped me a lot!";
		link.l1.go = "exit";
		pchar.questTemp.Headhunter = "hunt_carlos_fight";
		break;
		//ОЗГ

		//Виспер
		case "w_find_desouza":
			dialog.text = "Yes, some guys came here, they asked questions. They certainly didn't say they were working for the Inquisition, but you can't fool me. I immediately noticed a crucifix-shaped brand on one of the wrists. Such inquisitors put former criminals when they recruit them into their order.";
			link.l1 = "And you are very perceptive, as for a simple innkeeper. But why did you decide to tell me about those guys and not them about me?";
			link.l1.go = "w_find_desouza_1";
		break;
		case "w_find_desouza_1":
			dialog.text = "Well, first of all, I don't really like inquisitors, and secondly, they have long since sailed away. You, on the other hand, may be interested in where.";
			link.l1 = "And where to?";
			link.l1.go = "w_find_desouza_2";
		break;
		case "w_find_desouza_2":
			dialog.text = "And now we come to the main reason why I told you all this. Of course, such information costs money. Ten thousand.";
			link.l1 = "Get it. Come on, tell me, don't Tom.";
			link.l1.go = "w_find_desouza_3";
		break;
		case "w_find_desouza_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Oh, that's a completely different matter. And they went to the Dutch port.";
			link.l1 = "And more specifically?";
			link.l1.go = "w_find_desouza_4";
		break;
		case "w_find_desouza_4":
			dialog.text = "I don't know more specifically, but the Dutch don't have many ports in the Caribbean, you'll probably find them.";
			AddQuestRecord("WhisperQuestline", "4");
			pchar.Whisper.FindDesouzaHol = true;
			link.l1 = "Okay, goodbye.";
			link.l1.go = "exit";
		break;
		case "w_meet_esteban_friend":
			dialog.text = "One of my guests asked for you. He said he was looking for captain 'The Dog of War' for an important cause.";
			link.l1 = "What's the deal?";
			link.l1.go = "w_meet_esteban_friend_1";
		break;
		case "w_meet_esteban_friend_1":
			dialog.text = "You can find out from him yourself. He's in his room right now.";
			link.l1 = "Intrigued. I'll go talk to him.";
			link.l1.go = "exit";
			pchar.Whisper.EsFriendTown = FindStringBeforeChar(npchar.id, "_tavernkeeper");
			WhisperSpawn_Chard();
		break;

		//Виспер

		//Lipsar Квест История Давней Дружбы
		case "MaksQuest_1":
			dialog.text = "You're probably looking for that muddy guy in the hat and green doublet.";
			link.l1 = "Thanks for helping.";
			link.l1.go = "exit";
			DeleteAttribute(Pchar, "Luke.SpawnMaks");
		break;
		case "LukeQuest_1":
			bDisableFastReload = true;
			dialog.text = "As soon as you left, some people came into the tavern, talked to him, and they left together. And where, I don't even know.";
			link.l1 = "These are the ones on! What did they look like, can you tell me?";
			link.l1.go = "LukeQuest_2";
		break;
		case "LukeQuest_2":
			dialog.text = "Typical pirates, there was nothing special about their appearance.";
			link.l1 = "Okay, thanks for the information.";
			link.l1.go = "exit";
			link.l2 = "Okay, thanks for the information. Here you go, as a token of gratitude.";
			link.l2.go = "Pay1000";
			Pchar.Luke.Info = "Fight";
			AddDialogExitQuest("ChangeLukesHome");
		break;
		case "Pay1000":
			dialog.text = "Thank you, " + GetSexPhrase("sir", "madam") + ", I didn't expect it."
			link.l1 = "It's not difficult for me.";
			link.l1.go = "exit";
			AddMoneyToCharacter(Pchar, -1000);
			Pchar.Luke.Info = "Peace";
		break;
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}
