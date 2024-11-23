#include "DIALOGS\english\Common_Duel.c" //navy
#include "DIALOGS\english\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle;
	int DonationSize;

	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	// boal 13.03.2004 -->
	int d1,d2,d3,d4;
	bool ok;
	// boal 13.03.2004 <--
    ref sld;

	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.last_theme = makeint(rand(1));
		npchar.quest.last_theme_game = makeint(rand(1));
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE*3));
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}

	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча

		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = "This is the menu for choosing the type of drunkenness (betatest)";
			link.l1 = "Let there be a drunkard";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Card player";
			link.l2.go = "Beta_test_card";
			link.l3 = "Dice player";
			link.l3.go = "Beta_test_dice";
		break;

		case "Beta_test_alc":
            dialog.text = "Drunk selected";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;

		case "Beta_test_card":
            dialog.text = "Player at cards (30% that will send the first time)";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;

		case "Beta_test_dice":
            dialog.text = "Dice player (30% that will send the first time)";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;

		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("I may be drunk, but I'm sane. I'm going to have a drink with you, and the soldiers will grab me too! Nah...", "I'm not an enemy of the city I live in. I won't drink with you!" , ""+ GetSexPhrase("Buddy", "Girlfriend") +"you'd better get out of here in a good way...");
				link.l1 = RandPhraseSimple("Well, as you know...", "Heh, it hurts to fill your eyes! Wrong time.");
				link.l1.go = "exit";
				break;
			}
            ok = CheckFreeSitFront(npchar); //checkAttribute(npchar, "Default.ToLocator"); // есть куда сесть
			if(CheckAttribute(pchar, "questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ha, "+ GetSexPhrase("sir", "miss") +", I've heard about you, of course, of course, hehe. In taverns they say that you are bully and duelist, and in a drunken case, almost a dozen souls have already been presented before the eyes of the Lord. Look, our people, of course, are not timid, but only who wants to lose their belly for a mug of rum. Personally, I'm afraid to even sit at the same table with you, so I think I'll go.";
				link.l1 = LinkRandPhrase("Good riddance!", "Roll while I'm kind...", "Come on, come on! Run away, fish food!");
				link.l1.go = "exit";
				link.l2 = "Wait, I wanted to ask something....";
				link.l2.go = "talk_habitue_duel";
				break;
			}

            dialog.text = "Don't block my light, there are no flies in the mug!";
            link.l1 = "Already gone...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "And-ir! Oh, "+ GetSexPhrase("boy, you look like a seasoned sea wolf", "girl, you look like a real sea wolf") +"! Why don't you buy me a glass of rum?";
						link.l1 = "Maybe I am " + GetSexPhrase("sea wolf", "sea wolf") +", but this does not mean that I will drink with all sorts of trash ...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "I will be happy to join you, for the company.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "Why is that?";
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// Игра в карты boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Shall we play cards?", "Let's put our cards on the table. You're in?");
										link.l1 = "Why not?";
										link.l1.go = "Cards_begin";
										link.l2 = "What are the rules of the game?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Not now.";
										link.l3.go = "exit";

										// Dolphin -> генератор возврата выигрыша
										// 1 раз в 15 дней + 30% вероятность + нет активного такого же квеста
										//flag = sti(npchar.nation)!=PIRATE && pchar.location != "Pirates_tavern" && pchar.location != "FortOrange_tavern" && pchar.location != "Dominica_tavern" && pchar.location != "Guibraltar_tavern" && pchar.location != "Fishing_Settlement_tavern" && pchar.location != "Panama_tavern";
										//Log_Info(" days: "+GetQuestPastDayParam("CasinoGenerator_timer")+" надо > 15 Шанс: "+sti(npchar.GenQuest)+" надо < 30");
										//if (flag && GetQuestPastDayParam("CasinoGenerator_timer") > 15 && sti(npchar.GenQuest) < 15 && !CheckAttribute(pchar, "HOTP_CasinoQuest") && !CheckAttribute(npchar, "CasinoQuest.decline"))
										if (drand(100) < 9 && !CheckAttribute(pchar, "HOTP_CasinoQuest") && !CheckAttribute(npchar, "CasinoQuest.decline") && !CheckAttribute(pchar, "questTemp.KIP_Looser") && (pchar.location != "Pirates_tavern") && (pchar.location != "LaVega_tavern") && (pchar.location != "PuertoPrincipe_tavern") && (pchar.location != "LeFransua_tavern") && (pchar.location != "FortOrange_tavern") && (pchar.location != "Panama_tavern") && (pchar.location != "Fishing_Settlement_tavern") && (pchar.location != "Guibraltar_tavern") && (pchar.location != "Dominica_tavern") && (pchar.location != "Caiman_tavern") && (pchar.location != "DesMoines_tavern"))
										{
											DeleteAttribute(link, "l2");
											DeleteAttribute(link, "l3");
											link.l1 = "What are you going to play for? I see that you have nothing to pay for even a pint of ale.";
											link.l1.go = "HOTP_CasinoQuest_1";
										}

									}
									else
					    			{
Dialog.text = "No, I don't want to play cards with you anymore.";
						    			link.l1 = "Well, don't.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
Dialog.text = RandPhraseSimple("Shall we throw dice?", "I suggest you roll the dice. You're in?");
										link.l1 = "Why not?";
										link.l1.go = "Dice_begin";
										link.l2 = "What are the rules of the game?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Not now.";
										link.l3.go = "exit";

										// Dolphin -> генератор возврата выигрыша
										// 1 раз в 15 дней + 30% вероятность + нет активного такого же квеста
										//flag = sti(npchar.nation)!=PIRATE && pchar.location != "FortOrange_tavern" && pchar.location != "Dominica_tavern" && pchar.location != "Guibraltar_tavern" && pchar.location != "Fishing_Settlement_tavern" && pchar.location != "Panama_tavern";
										//Log_Info(" days: "+GetQuestPastDayParam("CasinoGenerator_timer")+" надо > 15 Шанс: "+sti(npchar.GenQuest)+" надо < 30");
										//if (flag && GetQuestPastDayParam("CasinoGenerator_timer") > 15 && sti(npchar.GenQuest) < 15 && !CheckAttribute(pchar, "HOTP_CasinoQuest") && !CheckAttribute(npchar, "CasinoQuest.decline"))
										if (drand(100) < 9 && !CheckAttribute(pchar, "HOTP_CasinoQuest") && !CheckAttribute(npchar, "CasinoQuest.decline") && !CheckAttribute(pchar, "questTemp.KIP_Looser") && (pchar.location != "Pirates_tavern") && (pchar.location != "LaVega_tavern") && (pchar.location != "PuertoPrincipe_tavern") && (pchar.location != "LeFransua_tavern") && (pchar.location != "Panama_tavern") && (pchar.location != "Fishing_Settlement_tavern") && (pchar.location != "Guibraltar_tavern") && (pchar.location != "Dominica_tavern") && (pchar.location != "Caiman_tavern") && (pchar.location != "DesMoines_tavern"))
										{
											DeleteAttribute(link, "l2");
											DeleteAttribute(link, "l3");
											link.l1 = "What are you going to play for? I see that you have nothing to pay for even a pint of ale.";
											link.l1.go = "HOTP_CasinoQuest_1";
										}

									}
									else
					    			{
Dialog.text = "No, I don't want to play dice with you anymore.";
					    				link.l1 = "Well, don't.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) // && sti(NPChar.Quest.HeroLose))
									{
					    				link.l9 = RandSwear() + "You cheated!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} //switch
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Get the hell away from my desk!", "And... what? Who is it? and-ic.. Get off!");
	                        link.l1 = RandPhraseSimple("Drunkenness ruins your sinful soul - come to your senses!", "Don't be rude to me.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("How are you talking to me, you brute! Now I'm going to teach you good manners.", "I'm going to hit you on the head now, you'll sober up in a moment.");
	        	            link.l2.go = "tavern_keeper";
							if (SharleMaryIsHere() && PChar.sex != "woman" && rand(2) == 2)
							{
								link.l1 = "";
								link.l1.go = "Mary_Zastupaetsya_1";
								DeleteAttribute(link, "l2");
								pchar.Mary.hamila.npcharID = npchar.id;
							}
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;

		case "Mary_Zastupaetsya_1":
			StartInstantDialogNoType(pchar.SharleMaryId, "Mary_Zastupaetsya_2", "Habitue_dialog.c");
		break;

		case "Mary_Zastupaetsya_2":
			dialog.text = RandPhraseSimple("(to the drunkard) I'm going to tear your throat out!", "(to the drunkard) You're going to deal with me now, you dirty face!");
	        link.l1 = "Hush, hush, Mary, he's already figured it out.";
	        link.l1.go = "Mary_Zastupaetsya_3";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID(pchar.Mary.hamila.npcharID));
		break;

		case "Mary_Zastupaetsya_3":
			DialogExit();

			sld = characterFromID("SharleMary");
			sld.Dialog.Filename = "Quest\MainheroPrologues\Mary_dialog.c";
			sld.dialog.currentnode = "hired";
			LAi_SetOfficerType(sld);
		break;

		case "talk_habitue_duel":
			dialog.text = "Nothing, "+ GetSexPhrase("sir", "miss") +", I won't tell you! And hardly anyone else will agree, because conversations with you end badly... But human memory is short - you'll see in a month or two all your adventures will be forgotten. Unless, of course, you refresh people's memory, hehe... Goodbye, "+ GetSexPhrase("sir", "miss") +". ";
			link.l1 = "Well, okay....";
			link.l1.go = "exit";
		break;

	    // карты -->
	    case "Cards_Rule":
   			dialog.text = XI_ConvertString("CardsRules")
			link.l1 = "Well, let's get started!";
			link.l1.go = "Cards_begin";
			link.l3 = "No, it's not for me...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = "Then let's decide on the bid (enter the bid).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "I think I should go.";
			link.l3.go = "exit_sit";
		break;

		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "You have the fame of an unsurpassed cheat. I won't play cards with you at all.";
                link.l1 = "Everyone is lying! Well, you don't need to.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Yes you are, "+ GetSexPhrase("buddy", "darling") +", stranded. Come back when you're rich.";
                link.l1 = "Okay.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "I've already lost to the nines, not my day.";
                link.l1 = "Okay.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Heh, are you laughing?! Play on " + iLa_Puesta + " gold?! Let's change the bet, otherwise I won't play with you!";
				link.l1 = "Yes, perhaps. The bid should be raised.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "I've changed my mind about playing.";
				link.l2.go = "exit_sit";
				break;
			}

			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Playing for such money? No, please fire me... Let's change the bet!";
				link.l1 = "Yes, you're right. The rate needs to be lowered";
				link.l1.go = "Cards_begin_2";
				link.l2 = "I've changed my mind about playing.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Okay, let's play " + iLa_Puesta + " coins per card.";
			link.l1 = "Give up!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;

		case "Cards_begin_2":
			dialog.text = "So what's the bid going to be? (Enter the bid).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "I guess I won't play...";
			link.l2.go = "exit_sit";
		break;

		case "Cards_begin_go":
			// анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;

		case "Cards_begin_go":
                Diag.CurrentNode = Diag.TempNode;
                DialogExit();
                LaunchCardsGame();
		break;
	    // карты <--
	    // КОСТИ -->
	    case "Dice_Rule":
   			dialog.text = XI_ConvertString("DiceRules");
			link.l1 = "Well, let's get started!";
			link.l1.go = "Dice_begin";
			link.l3 = "No, it's not for me...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";

Dialog.text = "Let's decide on the bid (enter the bid).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
		//	link.l2 = "Давай по 200 золотых за кубик";
		//	link.l2.go = "Dice_Node_500";
			link.l3 = "I think I should go.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "You have the fame of an unsurpassed cheat. I won't play dice with you at all.";
                link.l1 = "Everyone is lying! Well, you don't need to.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = GetSexPhrase("Buddy", "Darling") +", you are broke. Come back when you're rich.";
                link.l1 = "Okay.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "I've already lost to the nines, not my day.";
                link.l1 = "Okay.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Heh, are you laughing?! Play " + iLa_Puesta + " gold per a dice?! Let's change the bet, otherwise I won't play with you!";
				link.l1 = "Yes, perhaps. The bid should be raised.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "I've changed my mind about playing.";
				link.l2.go = "exit_sit";
				break;
			}

			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Playing dice for that amount of money? No, let's change the bet!";
				link.l1 = "Yes, you're right. The rate needs to be lowered";
				link.l1.go = "Dice_begin_2";
				link.l2 = "I've changed my mind about playing.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Well, we play " + iLa_Puesta + " coins per dice.";
			link.l1 = "Let's go!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;

		case "Dice_begin_2":
			dialog.text = "So what's the bid going to be? (Enter the bid).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "I guess I won't play...";
			link.l2.go = "exit_sit";
			break;

		case "Dice_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");

                Diag.CurrentNode = Diag.TempNode;
                DialogExit();
                LaunchDiceGame();
		break;
		//////  1
	    case "GhostShip_Speak_1":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
            npchar.GhostShip_Speak_Yet = true;
            pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();
   			dialog.text = "Well... I-ic! I saw a terrible thing - a ghost ship, and there were only dead people on it... They say he's been swimming here since Columbus...";
			link.l1 = "You're probably lying!";
			link.l1.go = "GhostShip_Speak_1_2";
		break;

		case "GhostShip_Speak_1_2":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.text = "Am I lying? I-ic! Yes, I've been drinking for the second week to forget what I saw... how he entered the bay on black tattered sails...";
			link.l1 = "And how did you survive?";
			link.l1.go = "GhostShip_Speak_1_3";
		break;

		case "GhostShip_Speak_1_3":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.text = "Yes, as soon as I saw that they were sticking to the shore, I got my pants dirty. I-ic!.. And don't laugh!";
			link.l1 = "Oh... You're a pretty good liar, you've completely wasted your head.";
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "1";
			AddQuestRecord("GhostShipQuest", pchar.GenQuest.GhostShip.AskAbout);
		break;
		//////  2
		case "GhostShip_Speak_2":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
            npchar.GhostShip_Speak_Yet = true;
            pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();
            dialog.text = "Is it happening? What's going on here? But they say the Flying Dutchman has sent the golden caravan to the bottom again.";
			link.l1 = "What other Dutchman?";
			link.l1.go = "GhostShip_Speak_2_2";
		break;

		case "GhostShip_Speak_2_2":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.text = "'Volatile'! So the ghost ship reappeared in the archipelago. He seemed to disappear for many years... I must have been in hell. And then how cursed everything on it is and the bullet does not take them.";
			link.l1    = "And what, you can't kill them?";
			link.l1.go = "GhostShip_Speak_2_3";
		break;

		case "GhostShip_Speak_2_3":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.text = "Sometimes cities were stormed, the entire garrison of the fort was slaughtered, and there were thousands of soldiers in the fort! Although, I heard, they were drowned somehow, but what will happen to them, the dead, they will drag the ship along the bottom to the shore, fix it somehow and commit atrocities again.";
			link.l1 = "Oh, what a lot of people make up... 'Dragging along the bottom' - wow. Although, thanks, it's an interesting story.";
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "2";
			AddQuestRecord("GhostShipQuest", "2");
		break;
		//////  3
		case "GhostShip_Speak_3":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
            npchar.GhostShip_Speak_Yet = true;
            pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();

			if (!CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle") &&
                             CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins")  &&
                            !CheckAttribute(npchar, "quest.GhostShipHelp")          &&
                            !CheckAttribute(pchar, "GenQuest.GhostShipWorkId")      &&
                            rand(2) == 1)
            {
                dialog.text = "Well, they say they planned to rob the fort again. I don't know which one, ask the mayors, maybe someone needs help.";
                link.l1 = "Oh how! Thanks, I have to go.";
    			link.l1.go = "exit_sit";
                break;
            }

            dialog.text = "'Flying Dutchman'? Yes, there is such a ship, although many do not believe it.";
			if(CheckAttribute(Pchar, "GhostShip.AlreadyTalked"))
			{
				link.l1 = "Ah, I've already heard, let's go";
				link.l1.go = "exit";
			}
            if (sti(PChar.GenQuest.GhostShip.KillMe) > 0 || sti(PChar.GenQuest.GhostShip.DeadByMe) > 0)
            {
                link.l1 = "Yes, I saw him! I barely survived. Where can I find him?";
            }
            else
            {
				link.l1 = "Okay, I believe. Where can I find him?";
			}
			link.l1.go = "GhostShip_Speak_3_2";
		break;

		case "GhostShip_Speak_3_2":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.text = "They say that he is now near the mysterious island of Khael Roa.";
			if(!CheckAttribute(PChar, "GhostShip.AlreadyTalked"))
			{
				link.l1    = "And tell me, my dear, where to look for this island?";
				link.l1.go = "GhostShip_Speak_3_3";
			}
			else
			{
				link.l1 = "Well, I'll visit him.";
				GhostShipOnMap();
				link.l1.go = "exit_sit";
			}
		break;

		case "GhostShip_Speak_3_3":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.text = "Rumor has it that he is somewhere in the triangle that forms the islands of San Martin, Nevis and Antigua.";
			link.l1 = "Well, I'll try to find him, see what kind of ghost he is.";
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "2";// вечный генератор
			AddQuestRecord("GhostShipQuest", "3");
			Pchar.GhostShip.AlreadyTalked = true;
			GhostShipOnMap();
		break;
		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = "Well... I-ic! There's time when all is well and even fine... I-ic! But why it's so you can't explain... I-ic! Maybe by reason of the rum... I-ic! Jamaican black rum... I-ic! Substitute, pour!";
			link.l1 = "What's next?";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Come on!";
			link.l2.go = "exit";
		break;

		case "talk_with_alchogol_song_2":
			dialog.text = "Flashing mugs, faces also heels... I-ic! And a floor on the head... I always drink with everyone and everywhere... I-ic! Where's the booze? I need it!";
			link.l1 = "What's next?";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "Come on!";
			link.l2.go = "exit";
		break;

		case "talk_with_alchogol_song_3":
			dialog.text = "When your heart is heavy and your chest is cold, take a couple of mugs of rum on your chest! And without worries and falsehood, everything will suddenly be around. You will understand that I am your best friend!";
			link.l1 = "Come on!";
			link.l1.go = "exit";
		break;

		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = LinkRandPhrase("Ir! That's what I understand! That's our way! Well, what is it? Will you buy me a mug of rum?",
						"Have a seat, " + GetAddress_Form(npchar) + ", let's have a cup of good Jamaican rum. It never hurts your health. And for a person who is interested in business, there is no better place than a tavern, I tell you for sure... A little money, a couple of mugs of good booze, and you'll find out everything you want... and even more. Trust an old regular...",
						"Eh-heh, have a seat, "+ GetSexPhrase("my dear sir", "madam") +", let's have a drink... Why not have a drink in a good campaign? In our port tavern, sometimes very interesting things can be heard if you have patience and drink in small sips so that averkil does not fall off... Then some cap will load the excess on board and start bragging about his adventures, then someone who knows what will blurt out in the right condition... There are different people here, and many have something to tell, believe me, "+ GetSexPhrase("my lord", "madam") +".");
			link.l1 = "Yes, easily! Innkeeper, bring me rum!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "And more! I've heard that they have already started robbing churches!";
				link.l1 = "Well, only pirates are capable of this...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;

		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "What kind of pirates are there! Ordinary land scoundrels, moreover, clearly their own, local ones: how do pirates know when the church purse is full to the brim? And they wouldn't get involved.";
				link.l1 = "Brave fellows, however. They bravely opened the flimsy church bolt...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;

		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "First. And they're smart, they don't have the strength. Who is being framed like that?!";
				link.l1 = "Your truth. The whole parish, having tightened their belts, was saving an extra coin to take to the church circle, and now some smart guys have made money in one fell swoop? They won't let them down now, they'll catch them all over the world.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;

		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "No. Who will catch them, robbed donations - and remember what their name was, they rushed out of town. And the jungle is big, now look for them-fistula at least until the second coming. And a month or two will pass, and this case will be completely forgotten. I'm telling you something else...";
				link.l1 = "Well, you know, people don't forgive that.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;

		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "People have a memory like a leaky skiff. People will forgive. And God?! He sees everything... That's who to be afraid of! About ten years ago, a terrible story happened with one of my friends, who, for disrespect to the Creator, almost hit the sea devil in the teeth...";
				link.l1 = "Sorry, friend, I'll listen to your story another time. Bye.";
				link.l1.go = "Alcogol_GenQuest_Church_2_6";
			break;

		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo("The bandits who robbed the church will be in the location - " + sGenLocation + " Time to search for them - 1 day");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = "Ah, Francois! I remember, I remember this one... No, I don't know. But I'll tell you what: ask our waitress about him. As long as he lived here, she ran to him every night. A jerk, one word. Maybe he told her something.";
				link.l1 = "Thank you, buddy, for the kind advice. I'll go talk to her.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;

			case "EscapeSlave_Villemstad_H1":
				dialog.text = "Yeah, what you won't see in the sea... That's what happened on the last flight...";
				link.l1 = "Well, tell me, just don't lie too much. I'll pour some more rum in the meantime.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;

			case "EscapeSlave_Villemstad_H2":
				dialog.text = "Here's a cross for you, noble"+ GetSexPhrase("my lord", "my lady") +" - I saw it with my own eyes... There is a ship coming, and instead of a crew on it there are figurines-gavrils... uh... gorilla monkeys... Well, or macaques, the devil take them apart...";
				link.l1 = "What?! And tell me, my dear, do you drink a bottle on watch?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;

			case "EscapeSlave_Villemstad_H3":
				dialog.text = "I will stay here forever if I'm lying! Haven't you ever heard about the monkey ship? Well, it was him... Gore me shrimp!";
				link.l1 = "What the fuck is monkey ship? No, I haven't heard.";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;

			case "EscapeSlave_Villemstad_H4":
				dialog.text = "Oh... And I say that I saw him with my own eyes. In the storm it was, " + pchar.questTemp.SlavetraderAreal.add + ". It's pitch dark, and then he appears out of nowhere - a ship with ragged sails... He had a broken foresail, and mainsail, and nock, and forecastle, and-and-and... Long story short, everything was broken for him! And he's walking straight into the wind and at least that!There are so many monkeys on deck in rags, like seals in a rookery! And there is a natural gorilla at the helm! He is nine feet tall, wears a red shirt, and has shark teeth on his chest instead of a cross... His eyes are burning, his teeth are flashing, he saw us and screamed in an inhuman voice...";
				link.l1 = "Well, you're completely lying, brother. What can't be imagined from drunken eyes. You can also tell me that the inscription on the stern of it was 'Flying Dutchman'.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;

			case "EscapeSlave_Villemstad_H5":
				dialog.text = "Uh, no, it wasn't 'Dutch'. I'm telling you, I'm not lying! It was a bark, and on the stern it was written " + pchar.questTemp.Slavetrader.ShipName + ".";
				link.l1 = "Kha-rkh!! Damn it! I think I know what kind of monkeys they were... Indeed, rum loosens tongues, you just have to listen.";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;

			case "EscapeSlave_Villemstad_H6":
				dialog.text = "Well, I'm telling you! And you don't believe it!.. Come on, let's have one drink and that's it... I'm mooring.";
				link.l1 = "Okay, thank you for the interesting story. I have to go. Have a nice day, buddy.";
				link.l1.go = "exit_sit";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
				Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
				AddQuestRecord("Slavetrader", "22_4");
				AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
				pchar.questTemp.Slavetrader = "FindMayak";
			break;

			//ОЗГ, Крыса
			case "Rat_Tavern_1":
			dialog.text = "It was a case, but what do you care, Captain? The sailors will see the land and rum with the girls, so they will become stupid at once – if anyone had anything under his hat, it is not noticeable here.";
			link.l1 = "That's it, of course it is... it's just that my friend is the navigator on that pinnace, and his captain forgot to check in at the port. And I found out that they were moored here – I think: let me check on an old friend. Did you hear where they were going?";
			link.l1.go = "Rat_Tavern_2";
			break;

			case "Rat_Tavern_2":
			dialog.text = "And who will sort it out, Captain? I only heard how those sailors boasted that they would grope French whores in a brothel when they started drinking gold, that the owner would pay them for the flight. Maybe they went to the Old World, or maybe somewhere else. And they didn't say anything else - they just shouted songs and ordered rum.";
			link.l1 = "You say, grope French women... Okay, I have to go. Thanks for the information!";
			link.l1.go = "exit_sit";
			CreateRatOfficer();
			Pchar.quest.Headhunter_Rattortuga.win_condition.l1 = "location";
			Pchar.quest.Headhunter_Rattortuga.win_condition.l1.location = "Tortuga";
			Pchar.quest.Headhunter_Rattortuga.function = "Headhunter_CreateRatpinasse";
			pchar.questTemp.Headhunter = "Rat_tortuga";
			SetFunctionTimerCondition("Headhunter_PinasseOver", 0, 0, 30, false);
			AddQuestRecord("Headhunt", "14");
		break;

		case "sit_2":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			AddMoneyToCharacter(pchar, -2);
			//navy --> Alcohol - rum count;
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
			}
			else pchar.questTemp.Rum = 1;
			//<-- navy
			WaitDate("",0,0,0, 0, 30);
			dialog.text = LinkRandPhrase("You are real"+ GetSexPhrase("my friend", "my sailor girl") +"! Let's get to know each other!",
			                             "Ick! What a rum! Well... Let's shudder!",
										 "To your health and to your generosity!");
			link.l1 = "Oh, a picky rum. Okay, I have to go, have a good time.";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "Let's have another cup.";
				link.l2.go = "sit_3";
			}

            link.l4 = LinkRandPhrase("It seems that I've been in the sea for ages. What's new in your area?",
                                    "Tell me, what are they talking about now? It's not for nothing that I sing you with rum...",
                                    "Tell me, brother, what kind of stories are going around the taverns?");
		    link.l4.go = "rumours_habitue";
		    //homo
		break;

		case "sit_3":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			int iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
					dialog.text = "Oh! A sound idea!";
					link.l1 = "Innkeeper! Bring me rum!";
					link.l1.go = "sit_2";
				break;

				case 1:
					if(rand(1) == 0)
					{
						if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
						dialog.text = RandPhraseSimple("Here you are, " + GetAddress_Form(NPChar) + "You probably think that everyone admires you, right? And for me - you are ordinary robber and a murderer. They also came up with the idea of a 'blah-blah pirate'! A bandit is a bandit, what's on the sea, what's on land...",
							"Ick! "+ GetSexPhrase("Under... scumbag", "Dr... rubbish") +"! You f-want to get me drunk, ik! And steal my money!");
						link.l1 = "I see you've already taken the extra on board... Go sleep it off, and I have to go now.";
						link.l1.go = "exit_sit";
						link.l2 = "I don't like your tone, buddy. You should have held your tongue.";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "Who are you calling a bandit, land rat?! Let's see how you sing, with a hole in your belly!";
						link.l3.go = "sit_case_2_enemy2";
					}
					else
					{
						if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
						dialog.text = RandPhraseSimple("Why are you staring at me like that? I suppose you want to get drunk and pick your pockets?! There are all kinds of rabble here!  Ick!.. An honest man can't even enter a tavern anymore!",
							"Do you respect me? Do you respect me, I'm asking you?!! Otherwise, look at me... I won't let anything go - right between my eyes... and that's it - order a memorial service.");
						link.l1 = "Buddy, I see you have a full hold. You should go home... And I have to go now.";
						link.l1.go = "exit_sit";
						link.l2 = "Not so much, man. You still know who you're talking to...";
						link.l2.go = "sit_case_2_enemy1";
						link.l3 = "Who are you gaping at?! Now I'm going to teach you some sense!";
						link.l3.go = "sit_case_2_enemy2";
					}
					link.l4 = "Calm down! What did you forget? I am your only true friend!";
					link.l4.go = "sit_case_2_friend";
				break;

				case 2:
					if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
					dialog.text = "Listen! You're a g-g-good person! M-maybe you can help me in... in... in a little business?";
					link.l1 = "No, I think it's time for me to go.";
					link.l1.go = "exit_sit";
					link.l2 = "O-of course! After all, we are... hic... friends!";
					link.l2.go = "sit_case_3";
				break;

				case 3:
					if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
					if (IsCharacterPerkOn(pchar, "Adventurer") || IsCharacterPerkOn(pchar, "Agent"))
					{
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110))
						{
						dialog.text = "...And then I grabbed his sword by the l-blade and...";
							link.l1 = "Stop, but what did you think!";
							link.l1.go = "sit_case_6";
						}
						else
						{
							dialog.text = "...And then I grabbed his sword by the l-blade and...";
							link.l1 = "... and-ir! And she says to me...";
						link.l1.go = "sit_2";
						}
					}
					else
					{
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110))
						{
						dialog.text = "...And then I grabbed his sword by the l-blade and...";
							link.l1 = "... and she tells me...";
							link.l1.go = "sit_2";
						}
						else
						{
							dialog.text = "...And then I grabbed his sword by the l-blade and...";
							link.l1 = "... and-ir! And she says to me...";
						link.l1.go = "sit_case_4_exit";
						}
					}
				break;

				case 4:
					if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
					dialog.text = "For you! Ah, the devil! Who is this?!";
					link.l1 = "Eh? What? Where? It seemed to be visible.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;

                case 5:
					if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
                    if (!CheckAttribute(pchar , "GenQuest.GhostShip.LastBattleEnd") && !checkAttribute(npchar, "GhostShip_Speak_Yet") && pchar.GenQuest.GhostShip.lastspeak_date != LastSpeakDate() && pchar.rank >= 10)
					{
                        dialog.text = "Let's have another cup.";
                        link.l1 = "Oh, a picky rum. Okay, I have to go, have a good time.";
						link.l1.go = "exit_sit";
						switch (sti(pchar.GenQuest.GhostShip.AskAbout))
						{
							case 0 :
								link.l2 = "What kind of stories go around the taverns?";
								link.l2.go = "GhostShip_Speak_1";
							break;

							case 1 :
								link.l2 = "What interesting things are being done in these waters?";
								link.l2.go = "GhostShip_Speak_2";
							break;

							case 2 :
								link.l2 = "Tell me, brother, what do you know about the ghost ship, the Flying Dutchman?";
								link.l2.go = "GhostShip_Speak_3";
							break;
						}
					}
					else
					{
	         			dialog.text = "Drink like that!";
						link.l1 = "Drink it up!";
						link.l1.go = "sit_2";
					}
                break;
			}
		break;

		case "sit_case_5_exit": // дуэль
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_6": // откуп
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.text = "What's what?";
			link.l1 = "You decided to steal from me, then? Don't you want a sword in your chest?";
			link.l1.go = "sit_case_61";
		break;

		case "sit_case_61": // откуп
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.text = "No, no, I don't want any trouble! Take 1000 piastres and leave me alone, please.";
			AddMoneyToCharacter(pchar, 1000);
			link.l1 = "So be it, okay. I forgive you this time.";
			link.l1.go = "exit_sit";
		break;

		case "sit_case_4_exit":
			//navy --> Alcohol
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
			//<-- navy
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = "The fact is that I-I was insulted by one of the s-soldiers. That's it!";
			link.l1 = "S-soldier? N-no, I think I'll pass.";
			link.l1.go = "exit_sit";
			link.l2 = "Calm down! What did you forget? I'm your only true friend!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "Are you? W-what kind of friend are you?! N-no! You want to... hic...  You want to kill me! That's it!";
			link.l1 = "Okay, I see you've had enough for today. Goodbye.";
			link.l1.go = "exit_sit";
			link.l2 = "What? Yes, I'm going to prove to you now that I don't want to kill you! I'll give you a hand now... hic... I'll cut it off!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "Ah! Remove "+ GetSexPhrase("his", "her") +"from me!!";
			link.l1 = "Calm down... ic... It won't hurt!";
			link.l1.go = "tavern_keeper";
		break;
/*
		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = RandSwear() + "I'll carve you up like a pig!";
			link.l1 = "We'll see about that!";
//			link.l1.go = "tavern_keeper";
			link.l1.go = "fight_right_now"; //navy -- битва в таверне без базаров! :)
		break;
*/
		case "sit_case_2_enemy":
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Don't scare me!.. I attacked the wrong one-ick!.. People like you belong on the gallows, just like any other person! No matter how many feathers you spread, you can smell rotten fish a mile away. And I do not intend to choose expressions with the same-ik as you!";
			link.l1 = "Arch, but what to take with such drunkenness. I'm going to get some fresh air...";
			link.l1.go = "exit_sit1";
			link.l2 = "And you, boy, are overreacting. I'm going to shove these words down your throat!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "What is it?! Yes, I'm holding you now with these hands... Hic!.. Not one has left me yet!";
			link.l1 = "That's a drunken pig, I ruined such an evening. Okay, catch your cockroaches, I think I'll go.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear() + "I see you're not going to calm down. I'll have to give you a lesson in good manners.";
			link.l2.go = "sit_case_2_enemy3";
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
		break;

		case "sit_case_2_enemy2":
			ChangeCharacterReputation(pchar, -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Come on, you rascal! Now you're going to get it in full!", RandSwear() + "Now I'm going to carve you up properly!", "Ha! Come on, sailor - let's see what you can do on land!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("I swear you'll regret this!!!", "I'll shorten your filthy tongue to the ears!"), RandPhraseSimple("I'll gut you like a herring!", "I swear I'll shut you up!!!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Come on, guys! Let's get these scales out of our city!";
				link.l1 = RandPhraseSimple(RandSwear() + "Well, pray, you bastards!", "Oh, you're not alone yet!!! Well, you'll have company in hell!");
				link.l1.go = "fight_right_now_1";
			}
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
		break;

		case "sit_case_2_enemy3":
			ChangeCharacterReputation(pchar, 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Come on, you rascal! Now you're going to get it in full!", RandSwear() + "Now I'm going to carve you up properly!", "Ha! Come on, sailor - let's see what you can do on land!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("I swear you'll regret this!!!", "I'll shorten your filthy tongue to the ears!"), RandPhraseSimple("I'll gut you like a herring!", "I swear I'll shut you up!!!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Come on, guys! Let's get these scales out of our city!";
				link.l1 = RandPhraseSimple(RandSwear() + "Well, pray, you bastards!", "Oh, you're not alone yet!!! Well, you'll have company in hell!");
				link.l1.go = "fight_right_now_1";
			}
			if(Pchar.chr_ai.type != LAI_TYPE_SIT) LAi_SetSitType(pchar);
		break;

		case "exit_sit":
			//navy --> Alcohol
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
			//<-- navy
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterReputationToNeutral(pchar, 2);
			//navy --> Alcohol
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
			//<-- navy
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;


		case "tavern_keeper":
			//navy --> Alcohol
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
			//<-- navy
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;

		//------------------------------------------------------------------------------------------------------------------
		// Dolphin -> Генератор возврата выигрыша
		case "HOTP_CasinoQuest_1":
			pchar.questTemp.KIP_Looser = "KIP_Looser";
			//SetTimerFunction("LooserGenerator_NewGeneratorQuest", 0, 0, 15);
			npchar.CasinoQuest.decline = true;	// второй раз говорить об этому уже не будет
			dialog.text = "You're right, "+ GetSexPhrase("buddy", "girlfriend") +". I lost everything I had the other day. I guess fortune decided to make fun of me. It was like an obsession.";
			link.l1 = RandSwear()+"Who is this lucky guy?";
			link.l1.go = "HOTP_CasinoQuest_2";
		break;

		case "HOTP_CasinoQuest_2":
			dialog.text = "I'm not laughing, Captain! I have to return this money at all costs, and I need help. You're smart "+ GetSexPhrase("guy", "girl") +", and must understand that I can't do it myself - I'm too well known here.";
			link.l1 = "What are you implying?";
			link.l1.go = "HOTP_CasinoQuest_3";
		break;

		case "HOTP_CasinoQuest_3":
			dialog.text = "Help me get this money back, and I will thank you in a way that no one will ever thank you.";
			link.l1 = "I don't think it's possible.";
			link.l1.go = "exit";
			link.l2 = "Let's see what we can do.";
			link.l2.go = "HOTP_CasinoQuest_5";

			Diag.TempNode = "First time";
		break;

		case "HOTP_CasinoQuest_5":
			int KIP_Kto_Ukral
			KIP_Kto_Ukral = rand(1);
			if (KIP_Kto_Ukral == 0)
			{
				dialog.text = "The one I was playing with was a local store owner. He robbed me to the skin and now he's probably laughing at me. He needs to be taught a lesson "+
							"I suggest you discreetly rummage through the chests that are in his pantry. Seven wallets should still be there. We need to make it by the end of the day. It will be late tomorrow.";
				link.l1 = "Sorry, buddy, but this job is not for me.";
				link.l1.go = "exit";
				link.l2 = "I'll do it.";
				link.l2.go = "exit_CasinoQuest_Magazin";

				Diag.TempNode = "First time";
			break;
			}
			if (KIP_Kto_Ukral == 1)
			{
				dialog.text = "The one I was playing with was the owner of the shipyard. He robbed me to the skin and now he's probably laughing at me. He needs to be taught a lesson\n"+
							"I suggest you discreetly rummage through the chests that are in his pantry. Seven wallets should still be there. We need to make it by the end of the day. It will be late tomorrow.";
				link.l1 = "Sorry, buddy, but this job is not for me.";
				link.l1.go = "exit";
				link.l2 = "I'll do it.";
				link.l2.go = "exit_CasinoQuest_Verf";

				Diag.TempNode = "First time";
			break;
			}
		break;

		case "exit_CasinoQuest_Magazin":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();

			pchar.HOTP_CasinoQuest.npcharID = npchar.id;
			AddDialogExitQuestFunction("LooserGenerator_sart_Magazin");
		break;

		case "exit_CasinoQuest_Verf":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();

			pchar.HOTP_CasinoQuest.npcharID = npchar.id;
			AddDialogExitQuestFunction("LooserGenerator_sart_Verf");
		break;
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;

	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
