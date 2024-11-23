// boal 25/04/04 общий диалог Usurer
#include "DIALOGS\english\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;

	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "First time":
			if(!CheckAttribute(npchar, "CapitolMoney")) npchar.CapitolMoney = 500000 + drand(30) * 50000;
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = "Hurry up, " + pchar.name + ". And I'll clean up here...";
					link.l1 = "Going out to sea!";
					link.l1.go = "exit";
					break;
				}
				//работорговец
				//проклятый идол
				if(pchar.questTemp.PDM_CI_RostBlago == "PDM_CI_RostBlago")
				{
					dialog.text = "I don't even know how to thank you, " + pchar.name + ". These bandits have been bothering me for a long time.";
					link.l1 = "It's nothing. You have already done me a great favor by accepting this idol from me. I hope he brings you a lot of luck, haha!";
					link.l1.go = "exit";
					break;
				}

       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("The alarm has been raised in the city, they are looking for you everywhere! If I were you, I wouldn't stay here too long.", "The entire city guard is scouring the city in search of you. I'm not an idiot and I won't talk to you!", "Run, "+ GetSexPhrase("buddy", "girlfriend") +"before the soldiers make a sieve out of you..."),
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel", "scoundrel") +"?! The city guards have already are on your trail, you can't get far"+ GetSexPhrase(" dirty pirate", "") +"!", " Dirty murderer, get out of my house! Guards!!", "I'm not afraid of you, bastard! You'll be hanged in our fort soon, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, anxiety is not a problem for me...", "They will never catch me."),
					RandPhraseSimple("Shut your mouth, " + GetWorkTypeOfMan(npchar, "") + ", or I'll rip out your filthy tongue!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", and still there - catch pirates! I'll tell you what, buddy: stay quiet and you'll live..."));
				link.l1.go = "fight";
				break;
			}
			//homo Линейка Блада
            if (CheckAttribute(Pchar, "questTemp.CapBloodLine") && Pchar.questTemp.CapBloodLine == true)
            {
                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && !CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff"))
                {
                    dialog.text = "Good afternoon, Dr. Blood. Would you like to help me with something? Of course, you will receive a generous bonus.";
                    Link.l1 = "I wonder what the deal is?";
    				Link.l1.go = "CapBloodUsurer_5";
                    break;
                }
                dialog.Text = LinkRandPhrase("Hey, Dr. Blood! " + TimeGreeting() + ".",
                                    "Glad to see you, Peter Blood.",
                                    "It's good that you looked at me, " + GetFullName(pchar) + ". How is Colonel Bishop?");
                Link.l1 = "Alas, I'm already leaving, " + npchar.name + ". See you later.";
				Link.l1.go = "exit";
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.Ogl") && Pchar.questTemp.CapBloodLine.Ogl == false)//homo линейка Блада
                {
                    Link.l2 = "I'm here on business.";
    				Link.l2.go = "CapBloodUsurer_1";
                }
				break;
            }
			//пиратка, квест №5, заглушка на возврат бабла -->
			if (CheckAttribute(npchar, "PLQ5Money") && CheckAttribute(pchar, "questTemp.piratesLine.PLQ5Money")) 
			{
				dialog.text = "Did you bring me 50 thousand?";
				link.l1 = "Not yet, I'm doing it. Wait.";
				link.l1.go = "exit";
				link.l2 = "I'm afraid I'm not going to make it with this case. Consider that I refused.";
				link.l2.go = "StepPL5End_close";
				if (sti(pchar.money) >= 50000)
				{
					link.l3 = "Yes, I took your 50 thousand and ready to return them to you.";
					link.l3.go = "StepPL5End_1";
				}
				break;
			}
			//<--пиратка, квест №5, заглушка на возврат бабла

			//-->работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Well, finally he looked in on me"+ GetSexPhrase("worthy captain", "a worthy lady") +", and not these half-witted philistines who think that I plant their piastres in the courtyard of the bank and harvest every month to pay them interest. Ponies tremble for every penny, completely unaware of what tricks the poor usurer has to go to in order not to starve himself and still give them the opportunity to buy a goose for Christmas.";
				Link.l1 = "I think your depositors would not be happy to hear such words from a person they trust with their savings.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}

			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Well, old ferret, now you're going to have to try really hard to explain everything to me! There was a whole company of soldiers waiting for me in the hold of the ship instead of slaves! I barely managed to deal with them! I am so exited, so you must hurry up with the explanations!";
				Link.l1.go = "Slaveshore_5";
				break;
			}
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ah, here you are at last! There are already rumors all over the archipelago about your daring raid. Glad to see you!";
				Link.l1 = "I would prefer obscurity to such fame... It's too dangerous.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Did you bring five thousand slaves?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
				Link.l1 = "Yes, I did. They're in my holds.";
				Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "No, I'm still working on it.";
					Link.l1.go = "exit";
				}
				break;
			}

			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hmm... Are you still alive? Strange... Well, I guess it won't be for long. Soldiers! Help me! There's a bandit here!";
				link.l1 = "That bastard!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}

			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Good afternoon. My name is " + GetFullName(npchar) + ". What can I do for you?";
				link.l1 = "Oh! And what are you doing here, dear?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<--работорговец

			dialog.text = NPCStringReactionRepeat("Hello, " + GetAddress_Form(npchar) + ". How can I help you?",
				"Oh, is it you again? Welcome, " + GetAddress_Form(npchar) + ". What do you want this time?",
				"Hmm, you again, " + GetAddress_Form(npchar) + "... Well, I'm glad to see you again for the second time in a day. What do you want?",
                "Oh, " + GetAddress_Form(npchar) + ", you can't imagine how intrusive customers can sometimes be... What do you want?" , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nothing, I just came to watch and talk.",
				"Me again. And again, I decided to just talk like that.",
                "Yeah, me again. And again, without a specific case, just came to talk.",
				"Yeah, it's hard for usurers sometimes... And I don't need anything from you, I just wanted to chat...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "I want to discuss our financial relationship.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "I need some information... In general, there is a question.";
			link.l3.go = "quests";//(перессылка в файл города)

			//линейка ГПК, закладка миллиона на депозит
			if (CheckAttribute(pchar, "questTemp.LSC.usurerId") && pchar.questTemp.LSC.usurerId == npchar.id)
			{
				if (pchar.questTemp.LSC == "SignOnPoorMurder")
				{
					link.l4 = "Listen, you should have received a deposit in my name.";
					link.l4.go = "ISS_deposit";
				}
				if (pchar.questTemp.LSC == "PoorMurderExecute")
				{
					link.l4 = "I need to withdraw a deposit for a million piastres that you have.";
					link.l4.go = "ISS_takeDeposit";
					DeleteAttribute(pchar, "questTemp.LSC.usurerId");
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("I'm here on behalf of a man. His name is the governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".",
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " sent me to pick up something...");
				link.l7.go = "IntelligenceForAll";
			}
			//<<<<---------------- пиратка, квест №5. --------------------
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_1") && npchar.city == pchar.questTemp.piratesLine.Q5.city_1)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFirstUsurer")
				{
					link.l5 = "They say you hired John Avory.";
					link.l5.go = "StepPL5First_1";
				}
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst")
				{
					link.l5 = "Listen, did you hire John Avory?";
					link.l5.go = "StepPL5First_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_2") && npchar.city == pchar.questTemp.piratesLine.Q5.city_2)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toSecondUsurer")
				{
					link.l5 = "They say you had problems with John Avory...";
					link.l5.go = "StepPL5Second_0";
				}
				if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond")
				{
					link.l5 = "Listen, did you hire John Avory to run errands?";
					link.l5.go = "StepPL5Second_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_3") && npchar.city == pchar.questTemp.piratesLine.Q5.city_3)
			{
				if (pchar.questTemp.piratesLine == "PPL5Hunter_toThirdUsurer" || pchar.questTemp.piratesLine == "PPL5Hunter_toThird")
				{
					link.l5 = "I'm looking for John Avory, has he contacted you?";
					link.l5.go = "StepPL5Third_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_4") && npchar.city == pchar.questTemp.piratesLine.Q5.city_4)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFourth")
				{
					link.l5 = "I've heard you had an accident, maybe you need help?";
					link.l5.go = "StepPL5Four_1";
				}
			}
			//-------------------- пиратка, квест №5. ---------------->>>>
			//-->> сдача квеста найти потерянный драгоценный камень
			if (CheckCharacterItem(pchar, "UsurersJew") && CheckAttribute(npchar, "quest.usurersJewel.type"))
			{
				link.l6 = "I found your " + npchar.quest.usurersJewel.type + ". Here it is.";
				link.l6.go = "usurersJewel_R1";
			}
			if (CheckAttribute(npchar, "quest.usurersJewel.type") && !CheckCharacterItem(pchar, "UsurersJew"))
			{
				link.l6 = "I think I'm giving up on the search for the stone. I don't think I can find him.";
				link.l6.go = "jewelCancel";
			}
			//<<-- сдача квеста найти потерянный драгоценный камень
			if(CheckAttribute(pchar, "GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Hello, I'm here at your son's invitation.";
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "I am interested in what the owner of these documents is.";
				link.l10.go = "ShipLetters_Usurer1";
			}
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "I'm here about your slave supply order.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Hello, " + npchar.name + ", I'm here about your assignment.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Hello, " + npchar.name + ", I'm here about your assignment.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Hello, " + npchar.name + ", I'm here about your assignment.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "I'm here, as we agreed. What about the job?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "As we agreed, I'm here. What about the job?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good afternoon, " + npchar.name + ". How are you? Is there a new assignment?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Your task is completed. I managed to find the runaway slaves, even though it wasn't easy.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good afternoon, " + npchar.name + ". I'm here as we agreed, for another profitable business.";
				link.l8.go = "Slaveshore";
				break;
			}

			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "I have bad news, " + npchar.name + ". I failed to capture the brigantine.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Listen, " + npchar.name + ". I've caught up brigantine, but didn't find any documents. Are you sure they were there?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "I have good news, " + npchar.name + ". I managed to catch up with the brigantine and get the papers. Here they are.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good afternoon, " + npchar.name + ". Well, have you already prepared a new case for me?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", I managed to intercept your so-called 'galleon'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", I'm sorry, but I couldn't capture this galleon.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good afternoon, " + npchar.name + ". I'm here for my money.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", your task is completed. The bastard Gontier is dead, as is his entire team.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", I am very sorry, I missed Francois Gontier, although I led it's all the way to Tortuga. But there he managed to escape in his corvette right out from under my nose.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good afternoon, " + npchar.name + ". Well, tell me what kind of hot case you have prepared for me.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			//Капитул
			if(CheckAttribute(pchar, "SellCapitol"))
			{
				link.lCapitol = "I have something that might interest you. Take a look at this list.";
				link.lCapitol.go = "SellCapitol";
			}
			//Китайская реликвия
			if(CheckAttribute(pchar, "Whisper.UsurerId") && npchar.id == pchar.Whisper.UsurerId)
			{
				if (!CheckAttribute(pchar, "WhisperChSpokeToUsurer"))
				{
					link.lWhisper = "Good afternoon. I have received information that you have an ancient Chinese sword in your possession. Is that so?";
					link.lWhisper.go = "Whisper_china_relic";
				}
				else
				{
					if (CheckCharacterGeneratedItem(PChar, "topor_emperor") != "")
					{
						link.lWhisper = "I brought you the imperial axe.";
						link.lWhisper.go = "Whisper_china_relic_finish_topor";
					}
					if (CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3"))
					{
						link.lWhisper1 = "I brought you three crystal skulls.";
						link.lWhisper1.go = "Whisper_china_relic_finish_sculma";
					}
					if(CheckAttribute(pchar, "SellCapitol"))
					{
						link.lCapitol = "I found something more interesting than the things you asked me for. Take a look at this list.";
						link.lCapitol.go = "Whisper_china_relic_finish_capitol";
					}
				}
			}
			//Нежданное наследство
			if (CheckAttribute(PChar, "UnexpectedInheritance"))
            {
				if(!CheckAttribute(pchar, "UnexpectedInheritance_translator"))
				{
					link.lUnexpectedInheritance = "Do you provide translation services? I have an interesting document in Latin.";
					link.lUnexpectedInheritance.go = "UnexpectedInheritance_translate";
				}
				else
				{
					if(npchar.id == pchar.UnexpectedInheritance_translator && GetNpcQuestPastDayWOInit(npchar, "UnexpectedInheritance_translate") > 0 && sti(pchar.money) >= 1000)
					{
						link.lUnexpectedInheritance = "Do you provide translation services? I have an interesting document in Latin.";
						link.lUnexpectedInheritance.go = "UnexpectedInheritance_translate_end";
					}
				}
            }


			NextDiag.TempNode = "First time";
		break;

		//Нежданное наследство
		case "UnexpectedInheritance_translate":
			dialog.text = "Usually not, but for ten thousand...";
			if(sti(pchar.money) >= 10000)
			{
				link.l1 = "Here's your money.";
				link.l1.go = "UnexpectedInheritance_translate_end";
			}
			link.l2 = "You have some kind of inadequate pricing. I think I'll go.";
			link.l2.go = "exit";

		break;

		case "UnexpectedInheritance_translate_end":
			dialog.text = "Let's see... Hm... It's not really Latin, it's vulgaris. Wait a minute, here you go.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			UnexpectedInheritanceTranslatePart(pchar.UnexpectedInheritance);
			DeleteAttribute(pchar, "UnexpectedInheritance_translator");
			DeleteAttribute(pchar, "UnexpectedInheritance");

		break;
		//Капитул
		case "SellCapitol":
			dialog.text = "Hmm, it's really an interesting list. I am ready to give you for these things... "+npchar.CapitolMoney+". What do you say?";
			link.l1 = "Deal. You can pick it all up at Skeleton Reef. Here are the coordinates. It's safe there, you can send a ship there.";
			link.l1.go = "SellCapitol_1";
			link.l2 = "It won't be enough. I'll look for another buyer, no offense.";
			link.l2.go = "exit";
		break;
		case "SellCapitol_1":
			AddMoneyToCharacter(pchar, sti(npchar.CapitolMoney));
			DeleteAttribute(pchar, "SellCapitol");
			Log_Info("You gave away the location of the Chapter");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("TheLastMass");
			dialog.text = "Nice to do business with you. I hope you are not lying and the truth will be in place. Otherwise...";
			link.l1 = "I have no desire to meet with your familiar bounty hunters. I assure you, everything is there. Goodbye.";
			link.l1.go = "exit";
		break;
		//Виспер - Китайская реликвия
		case "Whisper_china_relic_finish_topor":
			dialog.text = "Wow! It looks even more luxurious than I imagined. I'm afraid to imagine how you got it.";
			s1 = CheckCharacterGeneratedItem(PChar, "topor_emperor");
			if ((sti(PChar.Items.(s1)) == 1) && (PChar.equip.blade == s1))
			{
				RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
			}
			TakeItemFromCharacter(PChar, s1);
			Log_Info("You gave away the imperial axe");
			PlaySound("interface\important_item.wav");
			link.l1 = "And no need, better show me the sword at last.";
			link.l1.go = "Whisper_china_relic_finish";
		break;
		case "Whisper_china_relic_finish_sculma":
			dialog.text = "Did you really find them?! To be honest, I didn't even hope.";
			TakeItemFromCharacter(pchar, "sculMa1");
			TakeItemFromCharacter(pchar, "sculMa2");
			TakeItemFromCharacter(pchar, "sculMa3");
			Log_Info("You gave away the crystal skulls");
			PlaySound("interface\important_item.wav");
			link.l1 = "Now I want to see the sword.";
			link.l1.go = "Whisper_china_relic_finish";
		break;
		case "Whisper_china_relic_finish_capitol":
			DeleteAttribute(pchar, "SellCapitol");
			CloseQuestHeader("TheLastMass");
			dialog.text = "Hmm, it's really an interesting list. I'm ready to give you a sword for him. Where can I find all these things?";

			Log_Info("You gave away the location of the Chapter");
			PlaySound("interface\important_item.wav");
			link.l1 = "On the Skeleton Reef. Here are the coordinates. It's safe there, you can send a ship there. So what about the sword? I would like to see him as soon as possible.";
			link.l1.go = "Whisper_china_relic_finish";
		break;
		case "Whisper_china_relic_finish":
			DeleteAttribute(pchar, "WhisperChSpokeToUsurer");
			DeleteAttribute(pchar, "Whisper.UsurerId");
			pchar.Whisper.GiveChinaSword = true;
			CloseQuestHeader("WhisperChinamanRelic");
			GiveItem2Character(pchar, "blade_china");
			Log_Info("You got a Chinese sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Of course! Here he is, handsome. I've tried to keep it in good condition, so please be careful with it.";
			link.l1 = "Don't worry, I'll give it to someone who will cherish it like the apple of his eye - the real owner. Goodbye.";
			link.l1.go = "exit";
		break;
		case "Whisper_china_relic":
			dialog.text = "That's right. Judging by the decorations on the blade, it belonged to a famous and influential family. Why are you interested in him?";
			link.l1 = "How much do you want for it? I'd like to buy it.";
			link.l1.go = "Whisper_china_relic_1";
		break;
		case "Whisper_china_relic_1":
			dialog.text = "Buy? I'm sorry, but I'm not selling anything from my collection.";
			link.l1 = "Sorry. Then maybe you wouldn't mind exchanging it for some other item?";
			link.l1.go = "Whisper_china_relic_2";
		break;
		case "Whisper_china_relic_2":
			dialog.text = "Hmm, but it's possible. I've been looking for the Imperial axe for a long time. It is a golden, jewel-encrusted symbol of power. They say that some pirate in the Caribbean definitely has it, I would like to get three Toltec crystal skulls: white, red and blue. If you find all three, I will be happy to exchange them with you.";
			link.l1 = "Clear. Is there any clue where these items can be obtained?";
			link.l1.go = "Whisper_china_relic_3";
		break;
		case "Whisper_china_relic_3":
			dialog.text = "If I knew that, I wouldn't ask you for anything. But I'm not in a hurry, come back when you find it. I'm not going to get rid of the sword anytime soon.";
			pchar.WhisperChSpokeToUsurer = true;
			AddQuestRecord("WhisperChinamanRelic", "2");
			link.l1 = "Okay, let's look for it. Goodbye.";
			link.l1.go = "exit";
		break;
		//

		//<<<<----------генератор -"Ship's documents". ------
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "It takes a lot of time to get acquainted with all the papers in detail, and my time is expensive.";
			link.l1 = "Maybe" + sti(pchar.questTemp.different.GiveShipLetters.price1) + "does the gold compensate for your hard work?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Your will. Goodbye!";
			link.l2.go = "exit";
		break;

		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Let's take a look! No, this is the first time I've seen that name. Show the papers to the port authority.";
				link.l1 = "Excuse me, but we agreed that you would tell me about this captain!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well , then ... I know the owner of this ship. He may not be the richest, but he is a very wealthy man.";
				dialog.text = s1 + "it is rumored that he has been successfully smuggling for a long time. Isn't that what you wanted to hear?";
				link.l1 = "Listen to you, so we can conclude....";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Yeah.... I don't even know if you were lucky to find it.";
				dialog.text = s1 + "The documents are issued for our colonial patrol ship, and its captain is known for his principled and strict morals.";
				link.l1 = "Patrolman? In charge of the commandant?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;

		case "ShipLetters_Usurer2_1":
			dialog.text = "We agreed that I would look at these papers, nothing more. I dare not detain you any longer.";
			link.l1 = "Thanks for that...";
			link.l1.go = "exit";
		break;

		case "ShipLetters_Usurer2_2":
			dialog.text = "You should draw conclusions. Our commandant has been 'looking closely' for a long time, can you guess who? And here there are invoices that are not marked by customs...";
			link.l1 = "I guess. Thank you, my dear!";
			link.l1.go = "exit";
		break;

		case "ShipLetters_Usurer2_3":
			s1 = "That's right. By the way, the local smugglers have a big grudge against this captain.";
			dialog.text = s1 + "As I said, the owner of these papers is very strict and does not favor violators of the law.";
			link.l1 = "I guess. Thank you, my dear!";
			link.l1.go = "exit";
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, so you are that "+ GetSexPhrase("captain who brought", "girl who brought") +" my prodigal son with a young bride?";
				link.l1 = "Yes, I helped them escape.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, revealed"+ GetSexPhrase("you, benefactor", "you, benefactress") +". Are you expecting a reward?";
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
			dialog.text = "What thanks? What is the gratitude for? Not only has this blockhead been hanging around without work for six months, he's also found time to be nice! Yes, I was already running my own business at his age. And look, he's gone hunting! The governor has a marriageable daughter, and this one has brought some kind of rootless slut, God forgive me, and is asking for parental blessing!";
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
			dialog.text = "What kind of feelings are these?! What kind of feelings are you talking about? An adult, like a person, but there too... Feelings! It should be a shame for you young people to indulge in such matters and to contract as a pimp. The girl was torn out of her parents' nest and my sucker's life was ruined. There will be no gratitude to you. Goodbye.";
			link.l1 = "Well, you don't get sick either...";
			link.l1.go = "EncGirl_6_2";
		break;

		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("la", "a"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", "a"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//<<<<---------------- пиратка, квест №5. --------------------
		case "StepPL5First_1":
			dialog.text = "I hired him, and he did a great job with my assignment. However, hee-hee, they say he got so drunk in the tavern that he confused the local drunk with my debtor.";
			link.l1 = "Did he say where he was going? Maybe some other usurer needs help?";
			link.l1.go = "StepPL5First_2";
		break;
		case "StepPL5First_2":
			dialog.text = "I don't know that, other people's problems don't concern me.";
			link.l1 = "It is clear that they do not concern. But maybe there was something in passing?";
			link.l1.go = "StepPL5First_3";
		break;
		case "StepPL5First_3":
			pchar.questTemp.piratesLine.Q5.city_2 = GetQuestNationsCity(SPAIN);
			dialog.text = "Yes, it seems that I was going to keep heading north of Main, to the Spaniards. But I don't know exactly where... Although wait, he said something about " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Voc") + ". But you understand that I cannot vouch for the authenticity.";
			link.l1 = "I understand. Thank you.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "4");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity1", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Acc"));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_2) + "Voc"));
			pchar.questTemp.piratesLine = "PL5Hunter_toSecond";
		break;

		case "StepPL5Second_0":
			dialog.text = "Uh, not that there's a problem...";
			link.l1 = "Hmm, so you hired him?";
			link.l1.go = "StepPL5Second_1";
		break;
		case "StepPL5Second_1":
			dialog.text = "Hired. He did his job, he paid back the debt in full. It was only in the tavern that he began to chatter that he allegedly beat out a debtor for an amount many times higher than the amount owed, and how he tricked me by keeping silent about it\n"+
				"Personally, it is completely unclear to me where the deception is, and why this story makes everyone terribly amused?! It's a bit insulting, of course, if I had known earlier that the debtor has such a sum..\n"+
				"In general, I breathed a sigh of relief when John Avory sailed away from our city. And now, I don't want to hear about him!";
			link.l1 = "Clear. And where he went, of course, you don't know...";
			link.l1.go = "StepPL5Second_2";
		break;
		case "StepPL5Second_2":
			pchar.questTemp.piratesLine.Q5.city_3 = GetQuestNationsCity(FRANCE);
			dialog.text = "I think this brat has gone to the French. I happened to overhear his conversation in a brothel. I went there on business, not for the intended purpose of this institution...";
			link.l1 = "Dear, I don't care what you did there. Thank you for the information about Avory.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "6");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_3) + "Voc"));
			pchar.questTemp.piratesLine = "PL5Hunter_toThird";
		break;

		case "StepPL5Third_1":
			dialog.text = "John periodically fulfills my orders, just recently completed another one...";
			link.l1 = "Where can he be now?";
			link.l1.go = "StepPL5Third_2";
		break;
		case "StepPL5Third_2":
			dialog.text = "God only knows that. You see, John is good as a performer, but he is very short-tempered. Recently, in a tavern, God forgive a sinful soul, I stabbed a man. That's why I don't ask John unnecessary questions...";
			link.l1 = "Understood... But maybe there is at least some idea where he might have gone?";
			link.l1.go = "StepPL5Third_3";
		break;
		case "StepPL5Third_3":
			pchar.questTemp.piratesLine.Q5.city_4 = GetQuestNationsCity(Holland);
			dialog.text = "If you are interested in my opinion, then I think he went to " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4) + ".";
			link.l1 = "Hmm... Can I hear the reasons for this conclusion?";
			link.l1.go = "StepPL5Third_4";
		break;
		case "StepPL5Third_4":
			dialog.text = "Of course. You see, the thing is that in " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Voc") + "a usurer was robbed recently.";
			link.l1 = "Ah, I get you! Thank you very much.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "8");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity1", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_4) + "Voc"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFourth";
		break;

		case "StepPL5Four_1":
			dialog.text = "No, no, thank you. I don't need any help anymore, I just hired John Avory yesterday, he's the best in this business! Oh, no offense, you're also od"+ GetSexPhrase("in", "on") +" one of the best, it's just that Avory came to me before you... Uh, excuse me, what did you say your name was?";
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "StepPL5Four_2";
		break;
		case "StepPL5Four_2":
			dialog.text = "Yes, yes, I've heard about you... it seems... So what was I talking about? And yes, imagine, a kind of image bursts in, puts a knife to my throat, and starts robbing me! Me!!! Dear man, in broad daylight...";
			link.l1 = "Sorry to interrupt, but who are you talking about now?";
			link.l1.go = "StepPL5Four_3";
		break;
		case "StepPL5Four_3":
			dialog.text = "...how much money is missing. How about who?! About the robber, of course! Oh, my money! Well, never mind, John Avory will show him! Avory is a force! Power!.. He had the audacity to brag that, they say, my arms are short, I can get him in Bermudes...";
			link.l1 = "Who? Avory?!";
			link.l1.go = "StepPL5Four_4";
		break;
		case "StepPL5Four_4":
			dialog.text = "Yes, what does Avory have to do with it? The robber, of course! Listen, why are you interrupting me all the time?!";
			link.l1 = "Sorry. What if I bring you the loot? Won't it upset you too much?";
			link.l1.go = "StepPL5Four_5";
		break;
		case "StepPL5Four_5":
			dialog.text = "Uh... well... in principle, I don't care who returns the money, but you figure it out for yourself. Your business with him is none of my business.";
			link.l1 = "No problem. John and I are not going to affect you. So how much money are we talking about?";
			link.l1.go = "StepPL5Four_6";
		break;
		case "StepPL5Four_6":
			dialog.text = "Fifty thousand! If you bring it all to me, your reward will be five thousand.";
			link.l1 = "What was the robber's name?";
			link.l1.go = "StepPL5Four_7";
		break;
		case "StepPL5Four_7":
			dialog.text = "Do you think he introduced himself to me?! Where have you seen such polite robbers? By the way, John did not ask such questions.";
			link.l1 = "Okay. It's a deal! Wait for me, I'll be back soon!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "9");
			pchar.questTemp.piratesLine = "PL5Hunter_toBermudes";
			npchar.PLQ5Money = true; //метка на ростовщика, которому должен бабла
			//здесь ставим прерывание на вход в дом Орри в Шарп-Тауне
            Pchar.quest.PQ5_inOrryHouse.win_condition.l1 = "location";
            Pchar.quest.PQ5_inOrryHouse.win_condition.l1.location = "Pirates_houseS1";
            Pchar.quest.PQ5_inOrryHouse.function = "PQ5_inOrryHouse";
		break;

		case "StepPL5End_close":
			dialog.text = "Bad, I'm very disappointed with you. It seems to me that you are not telling me something... Well, all right.";
			link.l1 = "Exactly! It's okay, buddy.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "PLQ5Money");
    		ChangeCharacterReputation(pchar, -50);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -20);
		break;

		case "StepPL5End_1":
			dialog.text = "Damn it, I'm glad! Tell me, what happened to that bastard who robbed me?";
			link.l1 = "He got what he deserved, he won't bother you anymore...";
			link.l1.go = "StepPL5End_2";
		break;
		case "StepPL5End_2":
			dialog.text = "Great, well, I'm ready to count my money. Let's get started...";
			link.l1 = "Please receive.";
			link.l1.go = "StepPL5End_3";
		break;
		case "StepPL5End_3":
			dialog.text = "Great! It's just perfect! Everything is fine. Here's your 5 thousand, as agreed.";
			link.l1 = "Thank you...";
			link.l1.go = "StepPL5End_4";
			DeleteAttribute(npchar, "PLQ5Money");
			AddMoneyToCharacter(pchar, -45000);
    		ChangeCharacterReputation(pchar, 10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
		break;
		case "StepPL5End_4":
			dialog.text = "Well, I'm always glad to see you at my place. And I want to tell you that I will tell everyone about your diligence and honesty. Arrogant Avory is no match for you, you are definitely the best...";
			link.l1 = "You drive it right into the paint... Well, good-bye.";
			link.l1.go = "exit";
		break;
		//-------------------- пиратка, квест №5. ---------------->>>>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			dialog.text = "Let's discuss. I'm listening to you carefully.";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 26)//при низком авторитете даётся гарантированный квест на камень
			{
				link.l1 = "Do you have a case that requires outside help?";
				link.l1.go = "Quest_gemstone";
			}
			else
			{
				link.l1 = "Do you have a case that requires outside help?";
				link.l1.go = "Loan_GiveWork";
			}
			if (npchar.city == "villemstad" && !CheckAttribute(pchar, "questTemp.KSM_DVR_Rostovshik"))	//Квест в Виллемстад "Money in growth"
			{
				link.l1 = "Do you have a case that requires outside help?";
				link.l1.go = "KSM_DVR_1";
			}
			if (npchar.city == "DesMoines" && CheckAttribute(pchar, "questTemp.MCzagadka"))	// Sinistra Иммунитет от квеста "Зачарованный город" (не даём квесты)
			{
				DeleteAttribute(link, "l1");
			}
			if (!CheckAttribute(NPChar,"StorageOpen"))
			{
				link.l11 = "Can I rent a storage box for personal items from you?";
				link.l11.go = "PersonalStorage";
			}
			else
			{
				link.l11 = "Open my storage cell.";
				link.l11.go = "PersonalStorage_Open";
			}
			//найти должника
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && pchar.GenQuest.Loan.FindCitizenNpcharId == NPChar.id)
            {
                link.l2 = "I'm here about the debtor assignment.";
                link.l2.go = "FindCitizen_1";
            }
			//доставить сундук
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && pchar.GenQuest.LoanChest.ChestNpcharId == NPChar.id)
            {
                link.l3 = "I'm here about the loan delivery assignment.";
                link.l3.go = "TakeChest_1";
            }
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
            {
                link.l4 = "I brought your credit.";
                link.l4.go = "TakeChest_2";
            }
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "I owe you "+ FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + LinkRandPhrase(". I'm ready to repay the debt.", ". At the moment, I am able to repay the debt to you.", ". It's time to finally settle up.");
					Link.l5.go = "loan_return";
					sTemp = "credit";
				}
			}
			else
			{
				Link.l6 = LinkRandPhrase("I want to borrow money.", "I urgently needed a couple of piastres.", "How about a small loan?");
				Link.l6.go = "loan";
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("I would like to give money to the growth.", "Will you take pirate loot for storage?", "Can I leave a piece of gold for a rainy day?");
					Link.l7.go = "deposit";
				}
			}
			if(CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)) && makeint(Pchar.Quest.Deposits.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(NPC_Area).StartYear),makeint(Pchar.Quest.Deposits.(NPC_Area).StartMonth),makeint(Pchar.Quest.Deposits.(NPC_Area).StartDay), makefloat(Pchar.Quest.Deposits.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Deposits.(NPC_Area).Result = makeint(Pchar.Quest.Deposits.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Deposits.(NPC_Area).Interest))*iPastMonths;
				Link.l8 = LinkRandPhrase("I want to withdraw my deposit.", "It's time to take my money that you have stored.", "I need my gold and the accumulated interest.");
				Link.l8.go = "Deposit_return";
			}
			/* Обмен драгоценных камней */
			link.l10 = "I want to exchange some gems.";
			link.l10.go = "Gems_exchange_1";
			//выход
			if (sTemp == "credit")
			{
				link.l9 = LinkRandPhrase("I remember taking a loan, but you are not ready to pay off yet...", "I know I owe thank you, but I don't have any money right now. I'll return it later...", "I remember that I owe you, but at the moment I do not have sufficient funds to repay the loan. I'll do it later.");
				link.l9.go = "Loan_Remind";
			}
			else
			{
				link.l9 = "I was wrong, I have no financial affairs with you. Goodbye.";
				link.l9.go = "exit";
			}
		break;
		//Ветка для персонального хранилища
		case "PersonalStorage":
			dialog.text = "Yes, I provide this service to my clients. I can guarantee that nothing will ever be lost from my vaults. The cost of the service is 10,000 piastres at a time, and after 1,500 for each subsequent month. Security is a troublesome and expensive business, you know. Would you like to register?";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Of course, here's your money.";
				link.l1.go = "PersonalStorage_2";
			}
			link.l2 = "Maybe some other time...";
			link.l2.go = "exit";
		break;
		case "PersonalStorage_2":
			AddMoneyToCharacter(Pchar, -10000);
			NPChar.StorageOpen = "Opened";
			NPChar.StoragePrice = 1500;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			DeleteAttribute(NPChar, "items");
			dialog.text = "Well, everything is paid, please go to the cell.";
			link.l1 = "(Open cell)";
			link.l1.go = "PersonalStorage_Open_2";
		break;
		case "PersonalStorage_Open":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.StoragePrice);
			if(sti(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = "You will be charged for renting a cell more " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Okay, I'll pay the rent now.";
					link.l1.go = "PersonalStorage_Open_1";
				}
				else
				{
					link.l1 = "I'll come back later.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "... It's all right, you can go to the vault.";
				link.l1 = "(Open cell)";
				link.l1.go = "PersonalStorage_Open_2";
			}
			link.l2 = "No, I changed my mind.";
			link.l2.go = "exit";
		break;
		case "PersonalStorage_Open_1":
			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForStorage));
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			dialog.text = "... It's all right, you can go to the vault.";
			link.l1 = "(Open cell)";
			link.l1.go = "PersonalStorage_Open_2";
		break;
		case "PersonalStorage_Open_2":
			DialogExit();
			LaunchItemsBox(npchar);
		break;
		//=============================  даём или не даём работу - сундуки и должники
		case "Loan_GiveWork":
            // проверка на проф пригодность -->
            if (isBadReputation(pchar, 40))
            {
                dialog.text = RandSwear() + "You're " + GetFullName(pchar) + ", isn't that right? " +
                              RandPhraseSimple("There are terrible rumors about you", "They don't speak in the best way about you") + ". I don't want to deal with you.";
				link.l1 = RandPhraseSimple("Eh... If a person stumbles, everyone will spit at him.", RandSwear() + "Well, don't!");
				link.l1.go = "exit";
                break;
            }
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 26)//при низком авторитете не даём
			{
            dialog.text = "No, fortunately, I'm fine.";
			link.l9 = "Sorry, I have to go.";
		    link.l9.go = "exit";
			break;
			}
            // проверка на проф пригодность <--
            dialog.text = "No, fortunately, I'm fine.";

			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
                npchar.quest.trade_date = lastspeak_date;
                iNum = rand(2);
                if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
                {
                    iNum = 0; // всегда первый
                }
                switch (iNum)
                {
					case 0: // найти потерянный драгоценный камень
						if (pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.usurersJewel") && GetNpcQuestPastDayWOInit(npchar, "usurersJewel") > 7 && !CheckAttribute(pchar, "questTemp.different.SeekUsurersJewel") && npchar.city != "Charles" && !CheckAttribute(npchar, "quest.slave"))
						{
							dialog.text = "You're just in time! I want to entrust you with a task.";
							link.l1 = "I'm listening carefully. What's the deal?";
							link.l1.go = "usurersJewel_1";
							npchar.quest.usurersJewel = "inSeek"; //личный флаг ростовщика на взятый квест
							SaveCurrentNpcQuestDateParam(npchar, "usurersJewel");
						}
					break;

                    case 1: // доставить сундуки
                        if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest")) break;

                        iNum = findChestMan(Npchar);
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.LoanChest.Chest      = 2 + drand(2);
                            pchar.GenQuest.LoanChest.Money      = (3 + cRand(sti(pchar.GenQuest.LoanChest.Chest)))*400 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + cRand(20)*250;
                            pchar.GenQuest.LoanChest.TargetIdx  =  iNum;
                            pchar.GenQuest.LoanChest.Time       = 20 + rand(15);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = " which is on the " + XI_ConvertString(GetIslandByCityName(chr.city)+"Voc");
							}
                            dialog.text = "I need a trusted person for an important mission. You need to deliver a loan - " + pchar.GenQuest.LoanChest.Chest +
									" chests of gold in "+ XI_ConvertString("Colony"+chr.city+"Acc") + sTemp + " for a man named " +
									GetFullName(chr) + ". He is a local " + GetWorkTypeOfMan(chr, "") +
									". You will receive a " + FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)) + " for the work. This should be done for " + FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)) + ".";
                            link.l1 = "I'm ready to !";
                			link.l1.go = "LoanUsurer_ChestWork_1";
            			}
                    break;
					
					case 2 : // найти должника
                        if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen")) break;

                        if (sti(Pchar.Ship.Type) == SHIP_NOTUSED && sti(npchar.quest.FindCitizenNoShip) < 2)
                        {
                            iNum = findCitizenMan(Npchar, true);
                            npchar.quest.FindCitizenNoShip = sti(npchar.quest.FindCitizenNoShip) + 1; // знатичит на суше без корабля
                        }
                        else
                        {
                            iNum = findCitizenMan(Npchar, false);
                        }
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.Loan.FindCitizenMoney   = (7 + cRand(sti(PChar.rank)))*1000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + cRand(20)*200 * GetCharacterSPECIALSimple(PChar, SPECIAL_L);
                            pchar.GenQuest.Loan.FindCitizenPercent = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) / (3+rand(2)));
                            pchar.GenQuest.Loan.FindCitizenIdx  =  iNum;
							pchar.GenQuest.Loan.FindCitizenChance1 = rand(2);
							pchar.GenQuest.Loan.FindCitizenChance2 = rand(1);
							pchar.GenQuest.Loan.FindCitizenChance3 = rand(1);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = " which is on the " + XI_ConvertString(GetIslandByCityName(chr.city)+"Voc");
							}
                            dialog.text = "Yes, you are on time. I have a sensitive issue that needs to be resolved. "+
                                     GetFullName(chr) + ", living in " + XI_ConvertString("Colony"+chr.city+"Voc") + sTemp + ", owed me " + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)) +
                                     ". If you return the entire amount to me, then you can keep the accrued interest. By the way, they make up " + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)) + ".";
                            link.l1 = "I'll take it!";
                			link.l1.go = "LoanUsurer_GiveWork_1";
            			}
                    break;
    			}
    		}
            else
            {
                dialog.text = "I've already told you everything.";
            }
            link.l9 = "Sorry, I have to go.";
		    link.l9.go = "exit";
		break;
		
		case "Quest_gemstone":
            // проверка на проф пригодность -->
            if (isBadReputation(pchar, 40))
            {
                dialog.text = RandSwear() + "You're " + GetFullName(pchar) + ", isn't that right? " +
                              RandPhraseSimple("There are terrible rumors about you", "They don't speak in the best way about you") + ". I don't want to deal with you.";
				link.l1 = RandPhraseSimple("Eh... If a person stumbles, everyone will spit at him.", RandSwear() + "Well, don't!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			dialog.text = "No, fortunately, I'm fine.";
			// найти потерянный драгоценный камень
			if (pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.usurersJewel") && GetNpcQuestPastDayWOInit(npchar, "usurersJewel") > 7 && !CheckAttribute(pchar, "questTemp.different.SeekUsurersJewel") && npchar.city != "Charles" && !CheckAttribute(npchar, "quest.slave"))
			{
				dialog.text = "You're just in time! I want to entrust you with a task.";
				link.l1 = "I'm listening carefully. What's the deal?";
				link.l1.go = "usurersJewel_1";
				npchar.quest.usurersJewel = "inSeek"; //личный флаг ростовщика на взятый квест
				SaveCurrentNpcQuestDateParam(npchar, "usurersJewel");
			}
			link.l9 = "Sorry, I have to go.";
		    link.l9.go = "exit";
		break;
		//============== boal нахождение должника ===============
		case "LoanUsurer_GiveWork_1":
            pchar.GenQuest.Loan.FindCitizen = true;
            pchar.GenQuest.Loan.FindCitizenNpcharId = Npchar.id;
            dialog.text = "Wonderful. I'm waiting for you as soon as possible.";
			link.l9 = "I won't let you down!";
			link.l9.go = "exit";
            chr = &Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)];
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = " which is on the " + XI_ConvertString(GetIslandByCityName(chr.city)+"Voc");
			}
			ReOpenQuestHeader("Gen_LoanFindCitizen");
            AddQuestRecord("Gen_LoanFindCitizen", "1");
            AddQuestUserData("Gen_LoanFindCitizen", "sName", GetFullName(chr));
            AddQuestUserData("Gen_LoanFindCitizen", "sCity", XI_ConvertString("Colony"+chr.city+"Voc") + sTemp);
			AddQuestUserData("Gen_LoanFindCitizen", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanFindCitizen", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)));
			AddQuestUserData("Gen_LoanFindCitizen", "sMyMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
		break;

		case "FindCitizen_1": //проверка выполнения квеста
            dialog.text = "I'm all ears.";
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone"))
            {
                link.l1 = "Your assignment is completed!";
                link.l1.go = "finish_work";
                link.l2 = "I managed to find the debtor, but I couldn't get the money out of him.";
                //if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= rand(11))
               // {
                //    link.l2.go = "finish_work_bad";
                //}
               // else
               // {
                    link.l2.go = "finish_work_lie";
              //  }
            }

            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                link.l1 = "I managed to find the debtor, but I couldn't get the money out of him.";
                link.l1.go = "finish_work_bad";
            }
            link.l3 = "I have decided to canceling your debtor search order is not for me.";
            link.l3.go = "finish_work_cancel";
            //link.l9 = "No. Nothing.";
			//link.l9.go = "exit";
		break;

		case "finish_work":
            if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
            {
                dialog.text = "That's nice!";
    			link.l9 = "Please!";
    			link.l9.go = "exit";
    			AddMoneyToCharacter(Pchar, -1*sti(pchar.GenQuest.Loan.FindCitizenMoney));
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.rank) * 3);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.rank) * 6);
    			ChangeCharacterReputation(pchar, 1);
    			OfficersReaction("good");
    			AddQuestRecord("Gen_LoanFindCitizen", "4");
                CloseQuestHeader("Gen_LoanFindCitizen");
			}
			else
			{
			    dialog.text = "Wonderful! But where is my money? Time is running out.";
    			link.l9 = "Coming soon!";
    			link.l9.go = "exit";
    		}
		break;

		case "finish_work_bad":
            dialog.text = "Very, very bad! You are not able to do your job!";
			link.l9 = "This man really wasn't wealthy, but you're right - this is my job.";
			link.l9.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Loan");
			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("Gen_LoanFindCitizen", "5");
			AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase("xia", "as"));
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;

		case "finish_work_cancel":
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") || CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                dialog.text = "But it seems to me that you are deceiving me! I know for sure that you talked to him. Give my money back!";
                link.l1 = "Yes, you're right, here's the money.";
    			link.l1.go = "finish_work";
    			link.l2 = "But he refused to pay!";
    			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
                {
    			   link.l2.go = "finish_work_bad";
    			}
    			else
    			{
    			   link.l2.go = "finish_work_bad_2";
    			}
    			//link.l9 = "I don't have time right now. I'll come back later.";
    			//link.l9.go = "exit";
    			//ChangeCharacterReputation(pchar, -1);
			}
            else
            {
                ChangeCharacterReputation(pchar, -1);
                dialog.text = "Bad, I was already counting on you.";
                link.l1 = "Yes, you're right, but that's life.";
    			link.l1.go = "exit";
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddQuestRecord("Gen_LoanFindCitizen", "6");
				AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase("xia", "as"));
                CloseQuestHeader("Gen_LoanFindCitizen");
            }
		break;

		case "finish_work_bad_2":
			ChangeCharacterReputation(pchar, -3);
            dialog.text = "You have already shown that you are prone to lying. Give my money back!";
			link.l1 = "I'm telling you, I don't have any money!";
    		link.l1.go = "finish_work_hanter";
			if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
			{
            link.l2 = "Yes, you're right, here's the money.";
    		link.l2.go = "finish_work";
			}
		break;

		case "finish_work_lie":
            dialog.text = "Hmm, exactly?";
            link.l1 = "Of course!";
    		link.l1.go = "finish_work_cancel";
		break;

		case "finish_work_hanter":
            dialog.text = "Oh, is that so? And you think I'm going to leave it like this? You'll be in big trouble, which will cost you a lot more than this money, I promise you. Get out!";
            link.l1 = "You won't scare me. Have a nice stay!";
    		link.l1.go = "exit";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 40);
			DeleteAttribute(pchar, "GenQuest.Loan");
    		DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    		AddQuestRecord("Gen_LoanFindCitizen", "7");
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;

		//============== boal доставка сундуков ===============
		case "LoanUsurer_ChestWork_1":
            pchar.GenQuest.LoanChest.TakeChest = true;
            pchar.GenQuest.LoanChest.ChestNpcharId = Npchar.id;
            dialog.text = "I'm counting on you very much.";
			link.l9 = "I won't let you down!";
			link.l9.go = "exit";
			TakeNItems(pchar, "Chest", sti(pchar.GenQuest.LoanChest.Chest));
			SetTimerCondition("LoanChestTimer", 0, 0, sti(pchar.GenQuest.LoanChest.Time), false);
			// немного весёлой жизни
            TraderHunterOnMap();
            chr  = &Characters[sti(pchar.GenQuest.LoanChest.TargetIdx)];
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = GetConvertStrWithReplace("Variable_which_on", "Interface.txt", "#space#", " ") + XI_ConvertString(GetIslandByCityName(chr.city)+"Voc");
			}
			ReOpenQuestHeader("Gen_LoanTakeChest");
            AddQuestRecord("Gen_LoanTakeChest", "1");
            AddQuestUserData("Gen_LoanTakeChest", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanTakeChest", "sQty", pchar.GenQuest.LoanChest.Chest);
			AddQuestUserData("Gen_LoanTakeChest", "sCity", XI_ConvertString("Colony"+chr.city+"Acc") + sTemp);
			AddQuestUserData("Gen_LoanTakeChest", "sName", GetFullName(chr));
			AddQuestUserData("Gen_LoanTakeChest", "sType", GetWorkTypeOfMan(chr, ""));
			AddQuestUserData("Gen_LoanTakeChest", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)));
			AddQuestUserData("Gen_LoanTakeChest", "sDay", FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)));
		break;

		case "TakeChest_1":
            dialog.text = "I'm all ears.";
            link.l1 = "I decided to cancel your credit delivery order is not for me.";
            link.l1.go = "TakeChestFinish_work_cancel";
            link.l9 = "No. Nothing.";
			link.l9.go = "exit";
		break;

		case "TakeChestFinish_work_cancel":
            if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
            {
                ChangeCharacterReputation(pchar, -1);
                dialog.text = "Bad, I was already counting on you.";
                link.l1 = "Yes, you're right, but that's life.";
    			link.l1.go = "exit";
    			TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));
    			DeleteAttribute(pchar, "GenQuest.LoanChest");
    			DeleteAttribute(Pchar, "quest.LoanChestTimer");
                AddQuestRecord("Gen_LoanTakeChest", "5");
				AddQuestUserData("Gen_LoanTakeChest", "sSex", GetSexPhrase("xia", "as"));
                CloseQuestHeader("Gen_LoanTakeChest");
			}
			else
			{
                dialog.text = "I may be ready to abort your mission if you RETURN all the chests to me.";
                link.l1 = "I'll come back later.";
    			link.l1.go = "Exit";
			}
		break;
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "No, I can't help you. In our troubled place, I can only offer money storage services.";
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Okay, let's figure out the amount.";
	                Link.l1.go = "deposit";
				}
                Link.l2 = "I'm not interested in this.";
				link.l2.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 40))
            {
                dialog.text = RandSwear() + "You're " + GetFullName(pchar) + ", isn't that right? " +
                              RandPhraseSimple("There are terrible rumors about you", "They don't speak in the best way about you") + ". I don't want to deal with you.";
				link.l1 = RandPhraseSimple("Eh.. if a person stumbles, everyone will spit at him.", RandSwear() + " Well, don't!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "Oh, you're welcome. How much money do you need?";
			Link.l1 = "I need a short-term loan for a small amount";
			Link.l1.go = "Small";
			Link.l2 = "I want a decent amount for an average period of time";
			Link.l2.go = "Medium";
			Link.l3 = "I need a long-term loan for a very significant amount.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 5000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Excellent. It is always easier with small amounts - there is less risk. I can offer you " + FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)) + "...";
			Link.l1 = "Agreed. At what interest?";
			Link.l1.go = "Interest_1";
			Link.l2 = "Alas, this amount is not suitable. Let's change it.";
			Link.l2.go = "Loan";
			Link.l3 = "I think it's better for me not to get into debt. Goodbye.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = PcharReputation();
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 10000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "No problem. I hope that " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + " will help you solve your problems. This is quite a significant amount.";
			Link.l1 = "Agreed. At what interest rate?";
			Link.l1.go = "Interest_2";
			Link.l2 = "Alas, this amount is not suitable. Let's change it.";
			Link.l2.go = "Loan";
			Link.l3 = "I think it's better for me not to get into debt. Goodbye.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = PcharReputation();
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 20000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "Mmm... It's risky... But okay, I'm ready to provide you with a loan in the amount of " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + ". As you understand, Captain, this is really a lot of money. I ask you to take this matter seriously.";
			Link.l1 = "Agreed. At what interest?";
			Link.l1.go = "Interest_3";
			Link.l2 = "Alas, this amount is not suitable. Let's change it.";
			Link.l2.go = "Loan";
			Link.l3 = "I think it's better for me not to get into debt. Goodbye.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = PcharReputation();
		break;

		case "Interest_1":
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + " interest per month. Based on what I know about you, I can't offer you better terms right now.";
			Link.l1 = "It suits me fine. It remains to discuss the deadline.";
			Link.l1.go = "Period_1";
			Link.l3 = "I think it's better for me not to get into debt. Goodbye.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest_2":
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + " interest per month. Based on what I know about you, I can't offer you better terms right now.";
			Link.l1 = "It suits me fine. It remains to discuss the deadline.";
			Link.l1.go = "Period_2";
			Link.l3 = "I think it's better for me not to get into debt. Goodbye.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest_3":
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + " interest per month. Based on what I know about you, I can't offer you better terms right now.";
			Link.l1 = "It suits me fine. It remains to discuss the deadline.";
			Link.l1.go = "Period_3";
			Link.l3 = "I think it's better for me not to get into debt. Goodbye.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period_1":
			Pchar.Quest.Loans.(NPC_Area).Period = 3;
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "Considering what I've heard about you, " + Pchar.name + ", I will wait for the repayment of this loan " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". After which, as you understand, I will take action.";
			Link.l1 = "Well, I'm happy to accept your terms... And your money.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Alas, we have not agreed with you. Goodbye.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period_2":
			Pchar.Quest.Loans.(NPC_Area).Period = 6;
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "Considering what I've heard about you, " + Pchar.name + ", I will wait for the repayment of this loan " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". After which, as you understand, I will take action.";
			Link.l1 = "Well, I'm happy to accept your terms... And your money.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Alas, we have not agreed with you. Goodbye.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period_3":
			Pchar.Quest.Loans.(NPC_Area).Period = 12;
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "Considering what I've heard about you, " + Pchar.name + ", I will wait for the repayment of this loan " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". After which, as you understand, I will take action.";
			Link.l1 = "Well, I'm happy to accept your terms... And your money.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Alas, we have not agreed with you. Goodbye.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "I am sincerely glad about this. But let me warn you. I have been doing my business for a long time and I know how to return the invested funds. So if you had any thoughts of pocketing my money, it's better to leave them, I don't want to offend you - I'm just warning you.";
			Link.l1 = "Hmm... Well, well. Have a nice day.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "Well, look... The interest is dripping. And you don't have much time left.";
			Link.l1 = "Don't worry. See you later.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			int iPastDays = GetPastTime(" days", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Sum) / 5000 * ((iPastDays+15)/30) );//фикс - опыта начисляем, если прошло пару недель, увеличил бонус - проценты всё равно же платим, и больше чем прокачивая торговлю не сходя с места
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans " + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("Oh, that's just wonderful! Any time you need money, I am at your service.", "Thank you. It is very pleasant to deal with a business person who knows how to repay a debt on time. And then you know, different things happen...",  "Oh, I was so sure of you for a reason, " + GetAddress_Form(NPChar) + "! I hope this is not the last time you will use my services!");
			Link.l1 = LinkRandPhrase("I want to borrow money.", "I urgently needed a couple of piastres.", "How about a small loan?");
			Link.l1.go = "loan";
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("I would like to give the money in growth.", "Will you take the pirate loot for storage?", "Can I leave the gold for a rainy day?");
				Link.l2.go = "deposit";
			}
			Link.l3 = "Goodbye, " + npchar.name + ".";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("I hear a reasonable person! So how much money are you willing to give in growth?", "Okay. Believe me, the amount that you give me will be waiting for you safe and sound, and even with interest... By the way, what is this amount?", "I see you understand what's what in this life. How much do you want to give me for safekeeping?");
			link.l1.edit = 3;
			link.l1 = "";
			Link.l1.go = "result";
		break;

		case "result":
			bool isPatentSameNation = pchar.PatentNation == NationShortName(sti(npchar.nation));
			int iPercents = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1;
			Pchar.QuestTemp.Deposits.(NPC_Area).Interest = iPercents + CheckAttribute(pchar, "EquipedPatentID") *  isPatentSameNation * iPercents;
			Pchar.QuestTemp.Deposits.(NPC_Area).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Are you kidding?";
				link.l1 = "Hmm, sorry, I mistaken..";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hmm, you don't have enough money with you, unfortunately. Let's not be silly...";
				link.l1 = "Um... All right.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Okay. I am ready to offer you interest on this amount... mm... let's say " + Pchar.QuestTemp.Deposits.(NPC_Area).Interest + ". Of course, per month.";
			Link.l1 = "That's fine with me.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "I'd better change the amount.";
			Link.l2.go = "Deposit";
			Link.l3 = "It seems like I shouldn't part with the money. Have a nice day.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)+".Result"))
			{
			    Pchar.Quest.Deposits.(NPC_Area).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Excuse me, Captain, but this amount is too large for a provincial bank. I simply have no place to organize the turnover of such money in order to be able to pay interest on your deposit. And the lack of decent security, you know... Well, I hope you understand me correctly? In general, I can accept no more from you in general. " +
						FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = "It's a pity, I'll have to turn to another usurer.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Now you can be sure that even the most violent storm will not leave you without means of livelihood. If you decide to withdraw the deposit, then come at any time.";
				Link.l1 = "Good. Have a nice day.";
				Link.l1.go = "Deposit_Exit";
			}
		break;

		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			Pchar.Quest.Deposits.(NPC_Area).Interest = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Interest);
			Pchar.Quest.Deposits.(NPC_Area).Sum      = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum);

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)));
			//pchar.questTemp.depositcount = sti(pchar.questTemp.depositcount) + makeint(Pchar.Quest.Deposits.(NPC_Area).Sum);
			//if(sti(pchar.questTemp.depositcount) >= 50000000) UnlockAchievement("bank_money", 3);
			// общий долг
			Pchar.Quest.Deposits.(NPC_Area).Sum = sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.Quest.Deposits.(NPC_Area).Sum);
			Pchar.Quest.Deposits.(NPC_Area) = true;
			Pchar.Quest.Deposits.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Deposits.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Deposits.(NPC_Area).StartTime = getTime();
			CheckForAchievement();
			DialogExit();
		break;

		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Based on the percentages that we agreed on last time, and taking into account the elapsed time, I calculated that I owe you " + FindRussianMoneyString(sti(Pchar.Quest.Deposits.(NPC_Area).Result)) + "... Are you sure you want to take this money?";
			Link.l1 = "Absolutely. Give them all here.";
			Link.l1.go = "Deposit_return_1";
			Link.l2 = "I would like to take back part of your contribution.";
			Link.l2.go = "Deposit_return_2";
			Link.l3 = "You know, you're right. Let them lie down a little longer. Have a nice day.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(NPC_Area).Result));
			//pchar.questTemp.depositcount = sti(pchar.questTemp.depositcount) - makeint(Pchar.Quest.Deposits.(NPC_Area).ClearDeposite);
			//pchar.questTemp.depositcount = sti(pchar.questTemp.depositcount) - makeint(Pchar.Quest.Deposits.(NPC_Area).Result);
			//if(sti(pchar.questTemp.depositcount) >= 50000000) UnlockAchievement("bank_money", 3);
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... It's even a pity to part with them. I've gotten used to them somehow. Well, come to me again.";
			Link.l1 = "If necessary, I will come. Have a nice stay.";
			Link.l1.go = "Exit";
			CheckForAchievement();
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;

		case "Deposit_return_2":
			link.l1.edit = 3;
			link.l1 = "";
			Link.l1.go = "Deposit_return_3";
			dialog.text = "And how much do you want to take away?";
		break;

		case "Deposit_return_3":
			iTemp = sti(dialogEditStrings[3]);
			CheckForAchievement();
			if (iTemp <= 0 || iTemp > sti(Pchar.Quest.Deposits.(NPC_Area).Sum))
			{
				dialog.text = "Are you kidding?";
				link.l1 = "Hmm, sorry, I mistaken..";
				link.l1.go = "exit";
				break;
			}
			if (iTemp <= sti(Pchar.Quest.Deposits.(NPC_Area).Result))
			{
				AddMoneyToCharacter(pchar,iTemp);
				if (sti(Pchar.Quest.Deposits.(NPC_Area).Result) == iTemp)
				{
					DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
					dialog.text = "Receive and sign.";
					link.l1 = "Great!";
					link.l1.go = "exit";
				}
				else
				{
					Pchar.Quest.Deposits.(NPC_Area).Sum = sti(Pchar.Quest.Deposits.(NPC_Area).Result)-iTemp;
					Pchar.Quest.Deposits.(NPC_Area).Result = Pchar.Quest.Deposits.(NPC_Area).Sum;
					Pchar.Quest.Deposits.(NPC_Area).StartDay = getDataDay();
					Pchar.Quest.Deposits.(NPC_Area).StartMonth = getDataMonth();
					Pchar.Quest.Deposits.(NPC_Area).StartYear = getDataYear();
					Pchar.Quest.Deposits.(NPC_Area).StartTime = getTime();
					dialog.text = "Get it and sign it. Your deposit balance is "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(NPC_Area).Result))+".";
					link.l1 = "Great!";
					link.l1.go = "exit";
				}
				//pchar.questTemp.depositcount = sti(pchar.questTemp.depositcount) - iTemp;
				//if(sti(pchar.questTemp.depositcount) >= 50000000) UnlockAchievement("bank_money", 3);
			}
		break;

		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Are you still alive? You probably want to give me a refund? To hell with it! Because of you, I've lost more than you can ever repay me! I won't rest until I see your corpse!";
            Link.l1 = "I just want to settle our affairs peacefully.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Well, let's see! Just keep in mind that you can easily become a corpse yourself!", "Are you threatening me?! Well, let's see what you do...", "Money is not the main thing in life. So you shouldn't kill yourself and others for them.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Get out of my house! My eyes wouldn't have seen you!";
			Link.l1 = "...";
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Yes? And what do you suggest?";
			Link.l1 = "I owe you the amount in " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ". I offer it to you.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "To improve relations, I propose to refund you the amount of debt in the amount of " + FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;

		case "LoanRestore_2":
			dialog.text = "That's another matter! You can still be dealt with.";
			Link.l1 = "Thank you. I won't let you down anymore.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterReputation(pchar, 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;

        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";

			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
		//поиски драгоценного камня за гордом
		case "usurersJewel_1":
			sld = ItemsFromID("UsurersJew");
			switch (rand(3))
			{
				case 0:
					sld.JevelType = "diamond";
					sld.model = "DiamondA";
					sld.picIndex = 2;
					sld.Jewel = "jewelry5";
				break;
				case 1:
					sld.JevelType = "ruby";
					sld.model = "RubyA";
					sld.picIndex = 3;
					sld.Jewel = "jewelry5";
				break;
				case 2:
					sld.JevelType = "emerald";
					sld.model = "EmeraldA";
					sld.picIndex = 4;
					sld.Jewel = "jewelry5";
				break;
				case 3:
					sld.JevelType = "sapphire";
					sld.model = "SapphireA";
					sld.picIndex = 1;
					sld.Jewel = "jewelry5";
				break;
			}
			dialog.text = "You know, a great misfortune has happened to me. I have lost the " + sld.JevelType + " of a wonderful job. But the most unpleasant thing is not even that. The worst thing is that the stone is not mine!";
			link.l1 = "So what? Buy another " + sld.JevelType + " and that's it.";
			link.l1.go = "usurersJewel_2";
			npchar.quest.usurersJewel.type = sld.JevelType; //тип камня
			npchar.quest.usurersJewel.money = (cRand(6)+2) * 500 + 1000; //вознаграждение
			npchar.quest.usurersJewel.jewel = sld.Jewel;//камешек
		break;
		case "usurersJewel_2":
			dialog.text = "Oh, if only it were that simple! The fact is that this " + npchar.quest.usurersJewel.type + " is unique in its kind. This stone was given to me by a customer for making a ring. I can't find anything similar in size and shape...";
			link.l1 = "Oh, this is really a problem. Well, how can I help you?";
			link.l1.go = "usurersJewel_3";
		break;
		case "usurersJewel_3":
			dialog.text = "Find it " + npchar.quest.usurersJewel.type + "That's all!";
			link.l1 = "Where did you lose it?";
			link.l1.go = "usurersJewel_4";
		break;
		case "usurersJewel_4":
			dialog.text = "In the jungle, just outside the city. I sometimes like to walk there in silence. It's comforting...";
			link.l1 = "You see, I am a man of a slightly different profession. I am not a detective and I am not "+ GetSexPhrase("footman", "maid") +". I'm not interested in finding the things you've lost.";
			link.l1.go = "usurersJewel_out";
			link.l2 = "Um, well, I'm ready to take up the search for the lost stone. What is the reward for the work?";
			link.l2.go = "usurersJewel_5";
		break;

		case "usurersJewel_out":
			dialog.text = "Mmm, it's a pity. Apparently, I was mistaken about you. Please excuse me...";
			link.l1 = "No problem.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.usurersJewel");
			ChangeCharacterReputation(pchar, -1);
		break;
		case "jewelCancel":
			dialog.text = "Mmm, it's a pity. Apparently, I was mistaken about you. Please excuse me...";
			link.l1 = "No problem.";
			link.l1.go = "exit";
			OfficersReaction("good");
			AddQuestRecord("SeekUsurersJewel", "7");
			AddQuestUserData("SeekUsurersJewel", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("SeekUsurersJewel", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekUsurersJewel");
			DeleteAttribute(npchar, "quest.usurersJewel");
			DeleteAttribute(pchar, "questTemp.different.SeekUsurersJewel");
			ChangeCharacterReputation(pchar, -1);
		break;
		case "usurersJewel_5":
			dialog.text = "If you find the lost one " + npchar.quest.usurersJewel.type + ", then I will pay well. I want to note that time is running out.";
			link.l1 = "Hmm, that's good. Well, I'm going on a search. Expect the result.";
			link.l1.go = "exit";
			pchar.questTemp.different = "SeekUsurersJewel";
			pchar.questTemp.different.SeekUsurersJewel = true;
			//ложим камень
			sld = ItemsFromID("UsurersJew");
			sld.shown = true;
			sld.startLocation = npchar.city + "_ExitTown";
			sld.startLocator = "item" + (rand(14)+1);
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			Log_QuestInfo("The stone is in the locator " + sld.startLocator);
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			ReOpenQuestHeader("SeekUsurersJewel");
			AddQuestRecord("SeekUsurersJewel", "1");
			AddQuestUserDataForTitle("SeekUsurersJewel", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekUsurersJewel", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekUsurersJewel", "sName", GetFullName(npchar));
			AddQuestUserData("SeekUsurersJewel", "sJewType", npchar.quest.usurersJewel.type);
		break;

		case "usurersJewel_R1":
			dialog.text = "Great! Yes, yes, that's him, the lost one " + npchar.quest.usurersJewel.type + "... Well, I'm happy, very happy. I am ready to pay you a reward for your work.";
			link.l1 = "Very good.";
			link.l1.go = "usurersJewel_R2";
			TakeItemFromCharacter(pchar, "UsurersJew");
		break;
		case "usurersJewel_R2":
			dialog.text = "Thank you again. You can contact me at any time, I will always listen to you.";
			link.l1 = "Thank you, why...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 2);
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Leadership", 15);
			AddCharacterExpToSkill(pchar, "Fortune", 25);
			AddMoneyToCharacter(pchar, sti(npchar.quest.usurersJewel.money));
			TakeNItems(pchar, npchar.quest.usurersJewel.jewel, 1);
			Log_Info("You got a gold bar");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.different.SeekUsurersJewel");
			AddQuestRecord("SeekUsurersJewel", "6");
			AddQuestUserData("SeekUsurersJewel", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("SeekUsurersJewel", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekUsurersJewel", "sJewType", npchar.quest.usurersJewel.type);
			CloseQuestHeader("SeekUsurersJewel");
			DeleteAttribute(npchar, "quest.usurersJewel");
		break;

        //============== Линейка Блада =============== homo

		case "CapBloodUsurer_1":
			dialog.text = "I do not issue funds to the colonel's living property, sir.";
			link.l1 = "Nevertheless, you did it.";
			link.l1.go = "CapBloodUsurer_2";
		break;

		case "CapBloodUsurer_2":
			dialog.text = "What?! What are you talking about?";
			if (sti(pchar.money) >= 5000)
			{
    			link.l1 = "Calm down. I have brought you a loan that the old gunner Ogle took out. Exactly five thousand.";
    			link.l1.go = "CapBloodUsurer_3";
            }
            else
            {
    			link.l1 = "I'm telling you about the loan that the old gunner took out. Exactly five thousand. I'll pay you for it.";
    			link.l1.go = "CapBloodUsurer_4";
            }
		break;


		case "CapBloodUsurer_3":
            AddMoneyToCharacter(pchar, -5000);
            Pchar.questTemp.CapBloodLine.Ogl = true;
            AddQuestRecord("OglQuest", "2");
			dialog.text = "Oh... Thank you, sir.";
			link.l1 = "All the best.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "CapBloodUsurer_4":
			dialog.text = "Did you bring the money for the Ogle?";
			if (sti(pchar.money) >= 5000)
			{
    			link.l1 = "That's right.";
    			link.l1.go = "CapBloodUsurer_3";
            }
            else
            {
    			link.l1 = "Unfortunately not, but I'll bring it soon.";
    			link.l1.go = "Exit";
    			NextDiag.TempNode = "CapBloodUsurer_4";
            }
		break;

		case "CapBloodUsurer_5":
			dialog.text = "A man from the city borrowed from me early this morning. The fact is that... He tricked me. He gave his name as Raphael Guinness, who often comes to see me, and, frankly, looks a little like him. I gave him a loan of 30,000 piastres, but then Rafe came in and...";
			link.l1 = "Do you want me to find this person? Why do you think he's still in town?";
			link.l1.go = "CapBloodUsurer_6";
		break;

		case "CapBloodUsurer_6":
			dialog.text = "He's in town, I assure you. No one has sailed yet today. And you will receive 10 percent as a bonus, that is, 3,000 piastres. What do you say?";
			link.l1 = "You know, I think I'll help you.";
			link.l1.go = "CapBloodUsurer_7";
			link.l2 = "Don't count on me.";
			link.l2.go = "Exit";
			NextDiag.TempNode = "First time";
			PChar.questTemp.CapBloodLine.QuestRaff = false;
		break;

		case "CapBloodUsurer_7":

            AddQuestRecord("UsurerQuest", "1");
            PChar.questTemp.CapBloodLine.QuestRaff = true;
            NextDiag.CurrentNode = "CapBloodUsurer_8";
			DialogExit();
		break;

		case "CapBloodUsurer_8":
			dialog.text = "Well, did you succeed?";
			if (sti(pchar.money) >= 27000)
			{
    			link.l1 = "Yes, here's your money without my ten percent.";
    			link.l1.go = "exit";
    			AddMoneyToCharacter(pchar, -27000);
                Pchar.quest.QUsurer.over = "yes";
                NextDiag.TempNode = "First time"; // fix многократной отдачи денег
		   		CloseQuestHeader("UsurerQuest");
            }
            else
            {
    			link.l1 = "Unfortunately not, but I'll bring it soon.";
    			link.l1.go = "Exit";
    			NextDiag.TempNode = "CapBloodUsurer_8";
            }
		break;
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 300 + rand(100);
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Oh, leave it! We are serious people, and there is no need to look back at the gossip of all this nonsense, which is ready to strangle itself for a Spanish doubloon, but at the same time will not lift a finger to make two out of it. I am looking for a person to whom I want to offer a serious case. A man of courage and activity, honest and punctual, but not burdened... Uh-uh... excessive scrupulousness in matters of morality. And I really hope to find such a person in your person.";
			Link.l1 = "It will largely depend on what kind of 'case' it is you're going to propose to me.";
			Link.l1.go = "GiveTaskSlave_1";
		break;

		case "GiveTaskSlave_1":
			dialog.Text = "Okay, listen up. There is no more profitable business in all the Caribbean now than the slave trade. I am not a planter, but I have a reliable buyer for this goods, and not just one. In general, I need slaves in quantity " + pchar.questTemp.Slavetrader.iSlaveQuantity + " pieces. I am ready to pay 250 piastres for each of them - this is a good price, you must agree. The total amount of the transaction will be " + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + ".";
			Link.l1 = "No, I don't do the slave trade. Look for another assistant who is not burdened with a conscience.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Hmm, the offer is really tempting. I would take it. How urgently do you need these slaves?";
			Link.l2.go = "GiveTaskSlave_2";
		break;

		case "exit_slaves":
			dialog.Text = "Uh-uh, few people want to move their backs to pick up the gold that is lying right under their feet. I'm disappointed... Goodbye, and don't try to chat about our conversation - I have long arms...";
			Link.l1 = "I see that your hands are dirty... however, so is the language. Have a nice day.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;

		case "GiveTaskSlave_2":
			dialog.Text = "I'm not limiting you in terms, but still try to hurry up. The demand for 'black ivory' is huge. If you prove yourself in my eyes on the good side, such orders will come to you without interruption, I assure you.";
			Link.l1 = "I believe it willingly. Well, wait for the good news.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
		break;

		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Well, did you manage to get the agreed-upon batch of 'ebony'?";
            if (amount < 0)
			{
				Link.l1 = "Not yet. I just decided to make sure our agreement is still in effect.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "It succeeded. The whole lot is in my holds.";
				if(amount != 0 && (GetSquadronGoods(Pchar, GOOD_SLAVES) <= makeint(sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 1.5))) Link.l1.go = "TakeMoreslaves1";
				else Link.l1.go = "Takeslaves";
			}

		break;

		case "TakeMoreslaves1":
			dialog.Text = "I see you have more 'ebony' than we agreed on. Do you want me to take everything from you, beyond our agreement?";
			Link.l1 = "Hmm... Yes, take everything!";
			Link.l1.go = "TakeMoreslaves2";
			Link.l2 = "No, dear, the rest is for my personal purposes."
			Link.l2.go = "Takeslaves";
		break;

		case "TakeMoreslaves2":
			dialog.Text = "Great! My people will take them away... Don't worry about the customs and the commandant of the fort. I have this business set up in a big way, so there will be no problems, and no one will accuse you of smuggling.";
			Link.l1 = "I see you've already got everything covered here! How about the payment?";
			Link.l1.go = "TakesMoreslaves3";
		break;

		case "TakesMoreslaves3":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES);
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
			AddMoneyToCharacter(pchar, makeint(amount * 250));
			dialog.Text = "Please get it... I don't waste words. Hold on to me, Captain, and soon you will have so many piastres that it will take an entire galleon to transport them!";
			Link.l1 = "It would be nice... Well, what's next?";
			Link.l1.go = "Takeslaves_2";
		break;

		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Great! My people will take them away... Don't worry about the customs and the commandant of the fort. I have this business set up in a big way, so there will be no problems, and no one will accuse you of smuggling.";
			Link.l1 = "I see you've already got everything covered here! How about the payment?";
			Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;

		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Please get it... I don't waste words. Hold on to me, Captain, and soon you will have so many piastres that it will take an entire galleon to transport them!";
			Link.l1 = "It would be nice... Well, what's next?";
            Link.l1.go = "Takeslaves_2";
		break;

		case "Takeslaves_2":
			dialog.Text = "Next? And then - come back in three weeks, I just have a solid order maturing. I think everything will have worked out by then.";
			Link.l1 = "Agreed. See you soon...";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;

		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "There will be work. But there is a problem - you have a weak ship. I don't want to fail the case, and I don't want to send you to certain death either. Since time is running out, get a more solid ship, no less than a barquentine, and preferably a brig or brigantine. Well, with a fluyt, as a last resort. And don't delay, we may miss the moment.";
				Link.l1 = "Of course, we will resolve this issue. See you later.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "Finally! I've been waiting for you. Now to the point. As you know, there are competitors in any business. I have them, too. These greedy, unscrupulous scoundrels always strive to steal a client from under their very noses! In general, I want to eliminate one such scoundrel and make a good profit from it.";
				Link.l1 = "I'm all ears.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;

		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Excellent. And so. This scoundrel, nicknamed " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " brought a cargo of slaves from Africa, and now staying in the " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + ", this is an island " + XI_ConvertString(pchar.questTemp.Slavetrader.Island) + ". He's waiting for smugglers there. His galleon is called '" + pchar.questTemp.Slavetrader.ShipName + "'. This deal must be thwarted, no matter what!";
			link.l1 = "Hmm, what about the slaves? Don't drown them!";
			link.l1.go = "Takeslaves_5";
		break;

		case "Takeslaves_5":
			dialog.Text = "Why on earth? " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " on a very bad account, and no one will be upset if it disappears. You capture a galleon, you send it to waste, you bring the goods to me, and I sell them. According to my information, he has at least fifteen hundred slaves on board-a huge shipment.";
			Link.l1 = "Wow! It's really quite a lot. What about the work fee?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "No, dear, these intrigues are not for me. Why should I quarrel with smugglers?'";
            Link.l2.go = "exit_slaves_1";
		break;

		case "exit_slaves_1":
			dialog.Text = "Yeah, it looks like I was wrong about you... Goodbye, and forget about our conversation. And if you don't want any trouble, I advise you not to talk about what you've heard here. As you can already see, everything is captured in my city. And if you cheat and try to board '" + pchar.questTemp.Slavetrader.ShipName + "' on your own - I will make sure that you are hanged on the gallows. Keep this in mind.";
			Link.l1 = "You don't have to worry - I don't do denunciations. And I don't need your galleon with slaves either. Have a nice day.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("xia", "as"));
			CloseQuestHeader("Slavetrader");
			pchar.questdata.Rabotorgovets = 1;
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста, зачищать атрибут нельзя
		break;

		case "Takeslaves_6":
			dialog.Text = "Taking into account the fact that I give full information about the location of the cargo, saving you from having to surf the sea in search of prey, the payment will be, as you understand, somewhat lower. 200 piastres for each slave. But it's still a huge amount-about three hundred thousand if everything goes well.";
			Link.l1 = "It's fine. How much time do I have for surgery?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Ho ho! You talk as if these slaves would swim themselves to get into my hold! Do you want my people to put their heads under grapeshot for such an absurd price? Increase the reward, or I won't do it.";
            Link.l2.go = "exit_slaves_1";
		break;

		case "Takeslaves_7":
			dialog.text = "I think no more than two weeks. If you are late, he will have time to unload and the moment will be lost.";
			link.l1 = "We'll have to hurry. Wait for me with good news. See you later.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Abl"));
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc"));
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;

		case "Takeslaves_4_lose":
			dialog.text = "Well, " + GetFullName(pchar) + ", how was the operation? Judging by your despondent appearance, you failed it.";
			link.l1 = "You're damn right... I... well, that... too late to the island. He must have already left there, since I didn't find anyone. I had to go all the way to the backwind - the headwind was constantly blowing, damn it...";
			link.l1.go = "Takeslaves_5_lose";
		break;

		case "Takeslaves_4_win":
			dialog.text = "Well, " + GetFullName(pchar) + ", what's the catch today? I have already been informed that " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + "blowing bubbles.";
			link.l1 = "Yes, I arrived just in time! " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " loaded slaves onto a smuggler's ship. I had to send his customers on a date with Davy Jones at the same time, so you have significantly fewer competitors.";
			link.l1.go = "Takeslaves_5_win";
		break;

		case "Takeslaves_5_lose":
			dialog.text = "Yes, it looks like I was wrong about you. Are you late? Or maybe he just chickened out by leaving the battlefield? Okay. It doesn't matter anymore. You ruined a great idea, and I don't want to do business with you anymore. Get lost and forget about everything you've seen and heard here.";
			link.l1 = "Well, goodbye.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questdata.Rabotorgovets = 1;
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "I see I was not mistaken in you - "+ GetSexPhrase("you are a dashing thug", "you are a dashing sailor") +". That's the kind of person I need. You have coped with the task perfectly - you have more than one and a half thousand slaves in your holds! But, unfortunately, I can only accept one thousand six hundred units of goods - I just don't have the money for more right now. You will have to sell the rest of the slaves yourself. So, your reward is 320000 piastres.";
				link.l1 = "Thank you. It's a pleasure doing business with you, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6_1");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "I see I was not mistaken in you - "+ GetSexPhrase("you are a dashing thug", "you are a dashing sailor") +". That's the kind of person I need. You coped with the task perfectly - you brought "+ sTemp +" slaves. Your reward is " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Thank you. It's a pleasure doing business with you, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "Well, you came out of a difficult situation with honor. And although the goods is less than I expected, I am still satisfied. So, you have brought "+ sTemp +" slaves. Your reward is " + FindRussianMoneyString(iSlaveMoney) + "";
				link.l1 = "Thank you. It's a pleasure doing business with you, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Yeah... Of course, this is understandable, but I was counting on more. You only brought "+ sTemp +" slaves. Well, come on, on the other hand, you eliminated the competition, it's worth something too. Your reward is " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Thank you. Thanks for understanding, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "It's certainly very entertaining, but... um... Looks like I was wrong about you. What did you bring me? "+ sTemp +" slaves? And where is the rest of the goods? And don't tell me that you drowned him. You sold it to smugglers, or, even worse, to the bastard Voisier from Bermudes. Get out of my sight, I don't want to have anything to do with you anymore.";
				link.l1 = "Have a nice stay.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "It's certainly very entertaining, but... Where are the slaves? Where is our goods? And don't tell me that you drowned him. You sold it to smugglers, or, even worse, to the bastard Voisier from Bermudes. Get out of my sight, I don't want to have anything to do with you anymore.";
			link.l1 = "Have a nice stay.";
			link.l1.go = "node_hanter_1";
		break;

		case "node_hanter_1":
			dialog.text = "That's not all. I don't let anyone lead me by the nose! And you will pay for your treachery - I will provide you with problems, do not doubt. Now get lost!";
			link.l1 = "Damn you and your slave trade!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			pchar.questdata.Rabotorgovets = 1;
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Takeslaves_6_win":
			dialog.text = "I see we've worked together, " + pchar.name + ". I am very glad about it. Come to me in about a month - maybe I'll pick up a job according to your profile. I'm just planning something.";
			link.l1 = "I will definitely come in! Cooperation with you brings good dividends.";
			link.l1.go = "Takeslaves_7_win";
		break;

		case "Takeslaves_7_win":
			dialog.text = "It will bring you a fortune... Yes, there is another question, " + pchar.name + ": did you find anything like that in the galleon's cabin during the boarding?";
			link.l1 = "No, I haven't seen anything so unusual. Was there supposed to be something?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "statue1"))
			{
				link.l2 = "Do you mean this statue here?";
				link.l2.go = "Yestatue";
			}
		break;

		case "Nostatue":
			dialog.text = "Maybe it should, or maybe it shouldn't... Okay, if they didn't find it, they didn't find it. I'll see you in a month. Goodbye!";
			link.l1 = "See you later, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;

		case "Yestatue":
			dialog.text = "Yes, exactly! This is a statue of the ancient Indian god Shochipilli. So she was in that bastard's cabin after all... May I take a closer look?";
			link.l1 = "Of course, keep it.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "statue1", 1);
		break;

		case "Yestatue_1":
			Log_Info("You gave the statue to Xochipilli");
			PlaySound("interface\important_item.wav");
			dialog.text = "So-so... Without a doubt, it's her. Listen, " + pchar.name + ", sell me this statue. I'm willing to pay a hundred thousand gold for it.";
			link.l1 = "One hundred thousand? Hmm... I agree. Take it away!";
			link.l1.go = "Buystatue";
			link.l2 = "No, I won't sell. The value of this statuette is not in the gold that you can get for it. I understand the subjects of the Indian cult.";
			link.l2.go = "Nobuystatue";
		break;

		case "Buystatue":
			dialog.text = "Excellent! I'm glad we have an agreement. Get your money. And I'll be waiting for you in a month. Goodbye.";
			link.l1 = "See you later, " + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;

		case "Nobuystatue":
			dialog.text = "You see, but I really need this statue! I completely agree with you - it is not valuable in money - any illiterate trader will not pay you a couple of thousand for it. But you really know a lot about Indian rituals, if you refuse to sell it for such a sum, if you don't want money for it, then I suggest an exchange. I have something that might interest you. Here, take a look. Magnificent noble attire! Straight from Europe! This is not to be found in the Caribbean. Not every governor can boast of such a thing. Rate it!\n It costs much more than a hundred thousand, but its main value, as you understand, is also measured by no means money. I offer you this robe in exchange for the statue. She's not the only one in the Caribbean. You're sailor, you will be able to find yourself more. But it's more difficult for me. Well, do you agree?";
			link.l1 = "Heh... Perhaps I agree. Give me this dress, and keep the statue for yourself.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "No. The statue is more valuable to me than this magnificent dress. I'll keep it for myself.";
			link.l2.go = "Nobuystatue_no";
		break;

		case "Nobuystatue_yes":
			dialog.text = "Excellent! I'm glad we have an agreement. This delightful garment is yours from now on. Get it. And I'll be waiting for you in a month. Goodbye.";
			link.l1 = "See you later, " + npchar.name + ".";
			link.l1.go = "exit";
			TakeNItems(pchar, "suit_3", 1);
			Log_Info("You got a noble dress");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;

		case "Nobuystatue_no":
			dialog.text = "Sorry, very sorry... Well, take it back. I'm not judging you - the statue is really valuable to a sailor. I'll see you in a month. Goodbye.";
			link.l1 = "See you later.";
			link.l1.go = "exit";
			TakeNItems(pchar, "statue1", 1);
			Log_Info("You got the Shochipilli statue");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;

		case "EscapeSlave":
			dialog.text = "You're on time, " + pchar.name + ". There is a task if you are ready to start doing it right now.";
			link.l1 = "Of course, I'm ready to do this.";
			link.l1.go = "EscapeSlave_1";
		break;

		case "EscapeSlave_1":
			dialog.text = "Great! Now to the point. Have you heard the latest news?";
			link.l1 = "Um... What are you talking about? There is a lot of news, and every day there is a new one.";
			link.l1.go = "EscapeSlave_2";
		break;

		case "EscapeSlave_2":
			dialog.text = "This news concerns our case directly. Curacao has seen the most massive slave escape in the history of the New World! More than a thousand souls escaped, and along the way several Dutch trading posts were cut out and burned.";
			link.l1 = "Interesting. Go on.";
			link.l1.go = "EscapeSlave_3";
		break;

		case "EscapeSlave_3":
			dialog.text = "But they didn't just escape - they incredibly escaped from the island! Without a trace. Stevesant is furious. But it doesn't matter... The important thing is that I ask you to go to Curacao, find out all the details of what happened, find these fugitives and capture them and, of course, not hand them over to Dutch justice, according to the laws of which they will face a very sad fate, but bring them to me. I will pay 300 piastres for each slave -I have heard that these are very good slaves.";
			link.l1 = "The task is clear. I'm heading for Curacao. Wait for me with good news.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "You know, I'm not going to do this. I will not take away freedom from people who earned it by risking their lives. They deserve it.";
			link.l2.go = "EscapeSlave_no";
		break;

		case "EscapeSlave_no":
			dialog.text = "Sorry, very sorry... I didn't expect a trick from you at the most inopportune moment... I think it's clear to you that our cooperation cannot continue after that. Goodbye.";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("xia", "as"));
			CloseQuestHeader("Slavetrader");
			pchar.questdata.Rabotorgovets = 1;
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;

		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Hehe! Yes, you not only coped superbly with a difficult task, but also brought slaves more than the specified number - "+ sTemp +" slaves. But the "+ sNum +" slaves are clearly not from Curacao runaways. I will pay 100 piastres for each of them. I suppose you won't be left out. Your reward is 330000 piastres for the main batch of slaves, and " + FindRussianMoneyString(iSlaveMoneyH) + " for exceeding the norm, so to speak.";
				link.l1 = "Ha ha ha, but you can't be fooled! Consent it your way, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", "a"));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "You have perfectly completed a difficult task and brought "+ sTemp +" slaves. Your reward is " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Thank you. It's a pleasure doing business with you, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "You have completed a difficult task, and although the goods is less than I expected, I am still satisfied. So, you have brought "+ sTemp +" slaves. Your reward is " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Thank you. It's a pleasure doing business with you, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Did you find it? Ahem... Well, what did you bring me? "+ sTemp +" slaves? And where is the rest of the goods? And don't tell me you drowned him. You sold it to the smugglers, or worse, to the bastard Voisier from Bermudes. Get out of my sight, I don't want to have anything to do with you anymore.";
				link.l1 = "Have a nice stay.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Did you find it? Where are the slaves? Where is our goods? And don't tell me you drowned him. You sold it to the smugglers, or worse, to the bastard Voisier from Bermudes. Get out of my sight, I don't want to have anything to do with you anymore.";
			link.l1 = "Have a nice stay.";
			link.l1.go = "node_hanter_1";
		break;

		case "Escape_slaves_win_1":
			dialog.text = "I am very pleased with you, " + pchar.name + ". I am very pleased. Come back in a month, I will prepare another profitable business for both of us by that time.";
			link.l1 = "I'm glad too, " + npchar.name + ". I will definitely show up in a month.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;

		case "Slaveshore":
			dialog.text = "You showed up very timely, " + pchar.name + ". I just need the services of a brave and not very scrupulous sailor, hehe. Are you ready to do my errand?";
			link.l1 = "Yes, I'm listening to you carefully.";
			link.l1.go = "Slaveshore_1";
		break;

		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "This time it's very simple. Today at " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + " pinnace '" + pchar.questTemp.Slavetrader.ShipName + "' anchored, under the flag of " + NationNameGenitive(sti(npchar.nation)) + ". Secretly, with the help of local smugglers, a large batch of 'ebony' has already been loaded onto it, at least two thousand heads of the pinnace team - an ordinary harbor sailor, a merchant captain. In general, they are worthless warriors. Your task is as usual: board the ship, pick up the goods and bring them to me. Payment - according to our fee, 200 piastres per unit of goods. Everything is as usual.";
			link.l1 = "Hmm... Not quite like last time. You're suggesting that I attack your countrymen's ship!";
			link.l1.go = "Slaveshore_2";
		break;

		case "Slaveshore_2":
			dialog.text = "I don't quite understand you, " + pchar.name + ". What difference does it make which nation this ship is? Or is it of fundamental importance to you?";
			link.l1 = "To me? I don't give a damn, gold doesn't have a nationality! I was just a little surprised...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Yes, it does. Quarrel with " + NationNameAblative(sti(npchar.nation)) + "I don't intend to .";
			link.l2.go = "Slaveshore_3_no";
		break;

		case "Slaveshore_3_no":
			dialog.text = "Is that so? Are you kidding? Well, if that's the case, then get lost. And forget about everything you've seen and heard here!";
			link.l1 = "Have a nice stay, " + npchar.name + ".";
			link.l1.go = "node_hanter_1";
		break;

		case "Slaveshore_3_yes":
			dialog.text = "What surprised you? That I'm not interested in the nationality of the gold coins either? I assure you, it is, and it's strange that you haven't noticed it yet. Moreover, excessive patriotic preferences are simply harmful for a professional banker, unless, of course, he plans to end his days on the porch, but let's do without philosophy. Get to the point - the ship will be in our waters until midnight, so you don't have much time. Are you ready to start the operation?";
			link.l1 = "Yes, " + npchar.name + ", I'm starting immediately.";
			link.l1.go = "Slaveshore_4";
		break;

		case "Slaveshore_4":
			dialog.text = "Excellent. I do not doubt for a second the success of our enterprise. Good luck to you, " + pchar.name + ".";
			link.l1 = "Thank you! See you later.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;

		case "Pinas_lose":
		dialog.text = "Well, " + GetFullName(pchar) + ", how was the operation? Judging by your despondent appearance, you failed it.";
			link.l1 = "You're damn right... I... well, that... too late. Delayed in the tavern, and when I'm out - there is no one in the sea anymore.";
			link.l1.go = "Takeslaves_5_lose";
		break;

		case "Slaveshore_5":
			dialog.text = "" + pchar.name + "Please calm down. It's not my fault! Damn it, I was informed too late... This is a betrayal! I was framed by one of my trusted people!";
			link.l1 = "Okay, I see you're not lying. Fortunately for you, captain of the pinnace blabbed before he died that our cases were solved. If it wasn't for that phrase of his, I would have already finished you off... But you said, you damn money bag, that you've got everything covered here on the island!";
			link.l1.go = "Slaveshore_6";
		break;

		case "Slaveshore_6":
			dialog.text = "The ambush was not organized by the local authorities, otherwise I would have known all about it.. " + pchar.name + ", now is not the time for swearing and insults. You and I are both in mortal danger - we were betrayed by one of my former contractors, but we managed to find out that all the collected evidence - a package of papers - is now on its way to our Governor-General. If they fall into his hands, we're finished! And you, by the way, first of all.";
			link.l1 = "So that's what that rascal captain meant!";
			link.l1.go = "Slaveshore_7";
		break;

		case "Slaveshore_7": //выбор острова, куда бригантина пойдёт
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Tortuga";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Listen carefully. We still have a chance. The package was sent by brigantine '" + pchar.questTemp.Slavetraderbrig.ShipName + "'. That's the only thing I know. The papers are being taken to the Governor-General, to his residence on the island " + XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island) + ". You have to intercept her, board her and find this compromising material.";
			link.l1 = "That's all I have to do. Well, pray for yourself and for me, and hope that I will catch up with her. And when I get back, we'll continue our conversation. And don't think that I'm going to leave it all like this!";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;

		case "Slaveshore_8":
			dialog.text = "The main thing is to find the package! I will be sure of my safety only if you deliver it to me... Damn it.. " + pchar.name + "It seems we have a problem...";
			link.l1 = "What else is it?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;

		case "Brig_lose":
			dialog.text = "Curse... And I was so hoping for you, " + pchar.name + ". Well, we can't do any more business with you. If I fail to pay off the investigation, I will be forced to flee. And I don't advise you to be here either - soldiers can descend at any moment. Goodbye.";
			link.l1 = "Goodbye, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Letter_lose":
			dialog.text = "Were. I know this for sure. Well, we can't do any more business with you-it's not safe anymore. Goodbye.";
			link.l1 = "Goodbye, " + npchar.name + ".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questdata.Rabotorgovets = 1;
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Brig_win":
			dialog.text = "Great! I didn't doubt you for a minute, " + pchar.name + ". Please hand the papers over to me, otherwise my soul is not in place.";
			link.l1 = "Hold on.";
			link.l1.go = "Brig_win_1";
		break;

		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Excellent... Now you can be calm. The Governor-General won't find out about anything, and I've already settled all the issues with the local authorities, although I had to fuss a lot, I'll tell you.";
			link.l1 = "All this is good, of course, but don't you think you should compensate me for the moral and material damage caused by your ill-considered actions?";
			link.l1.go = "Brig_win_2";
		break;

		case "Brig_win_2":
			dialog.text = "Absolutely, " + pchar.name + ". Moreover, I owe you a lot. And I very much look forward to continuing our cooperation. But I ask you to understand my position - I have incurred huge expenses - the loyalty of the governor and the commandant is not cheap. In addition, I had to hush up the murder of a patrol squad in my residence...";
			link.l1 = "Are you saying that you don't intend to cover my losses?!";
			link.l1.go = "Brig_win_3";
		break;

		case "Brig_win_3":
			dialog.text = "Don't get too excited, " + pchar.name + ". I really have money problems right now, so I suggest you make a slightly different kind of calculation.";
			link.l1 = "Then I'm listening to you carefully.";
			link.l1.go = "Brig_win_4";
		break;

		case "Brig_win_4":
			dialog.text = "About a year ago, my companion and I were caught in a severe storm off the southern coast of Main. The ships were smashed on the rocks near Boca de la Sierpe, and although they did not last long afloat, we managed to take our cargo ashore - chests with jewelry, which contained a large batch of stones and jewelry. The bay is cozy there, and it was not difficult to hide the treasures, but as soon as the storm subsided, the Indians attacked us. That's how the few who managed to survive the shipwreck died, including my companion. And I and a handful of sailors managed to leave in a boat, we safely reached Cumana, but I did not dare to return for the chests. I am sure that the local savages are reliably protecting their coast from invasion, and at the same time my treasure. But you are "+ GetSexPhrase("a strong and brave man", "a strong and brave girl") +" - you can handle this gang of redskins quite well, there are really a lot of jewels there - they will cover all the losses you incurred, as well as the costs of the expedition to south Main.";
			link.l1 = "Hmm... Okay. Then I think I'll go to Cumana. I hope you're not lying to me. Keep in mind: if you try to cheat me, I'll get you out of the ground!";
			link.l1.go = "Brig_win_5";
		break;

		case "Brig_win_5":
			dialog.text = "You can be sure, " + pchar.name + ", everything said is true. Well, I'm waiting for you in about a month - I've already outlined one case that is designed to strengthen the shaky position of my business. See you later.";
			link.l1 = "See you later, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			pchar.GenQuestRandItem.Shore18 = true;
			pchar.GenQuestRandItem.Shore18.randitem1 = "sculMa1";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;

		case "SlaveGalleon":
			dialog.text = "Here you are, " + pchar.name + ". Great, you're on time, as always. Before getting to the heart of the matter, I would like to brief you on the current situation in the archipelago around the slave market. I think it will be useful for you. Do you know what the word 'repartimentos' means?";
			link.l1 = "Hmm... No, " + npchar.name + ", I do not know what it is. But, judging by the sound, it's close to taking something away from someone. Am I right?";
			link.l1.go = "SlaveGalleon_1";
		break;

		case "SlaveGalleon_end":
			dialog.text = "You really surprised me. What did you expect from me? Get out!";
			link.l1 = "Illegal business, and even more so, human trafficking, is too morally depressing. Have a nice stay.";
			link.l1.go = "node_hanter_1";
		break;

		case "SlaveGalleon_1":
			dialog.text = "You are very close to the truth, " + pchar.name + ". It is to take away, and specifically - freedom. Repartimentos is a kind of cunning way of enslaving Indians under plausible pseudo-legal pretexts - peacefully, so to speak. It is used by the Spanish authorities in relation to the indigenous population of Main. Are you interested in hearing the details?";
			link.l1 = "Why not?";
			link.l1.go = "SlaveGalleon_2";
		break;

		case "SlaveGalleon_2":
			dialog.text = "Representatives of the Spanish Crown visit Indian settlements. In them, they, using cynical deception and under the influence of direct threats, force the Indians to buy from them for fabulous sums all sorts of useless rubbish: rotten meat, old razors and the like. Moreover, in debt, after a certain period of time, let's say a year, the messengers return and demand payment. If the Indians cannot pay off - and this is most often the case - the Spaniards take with them part of the able-bodied male population, ostensibly for a while, in order to work off the debt and 'learn how to cultivate the land', you understand that these Indians never return to their settlements. That's how our trusting red-skinned brothers end up on sugar cane plantations and mahogany trading posts.";
			link.l1 = "Heh, well, it's necessary... Don't the Indians resist being taken away as slaves? Or don't they understand?";
			link.l1.go = "SlaveGalleon_3";
		break;

		case "SlaveGalleon_3":
			dialog.text = "They probably understand, but few people dare to speak openly when a paper with the thumbprint of the leader is thrust at you. Of course, such tactics are more often used against peaceful tribes such as the Arawaks, for example, or the Miskito. With the militant Itza and akavoi, and even more so, the Caribs, such a move will not work - even force does not always help there, but now let's move directly to your task.";
			link.l1 = "I can already smell the big money! I'm listening to you, " + npchar.name + ".";
			link.l1.go = "SlaveGalleon_4";
		break;

		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add;
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "A heavy galleon called " + pchar.questTemp.Slavetrader.ShipName + " will sail " + sTemp + " in a few days. He is transporting a huge batch of slaves - about 3,000 people - Indians, brought from various settlements of the lower Orinoco, captured according to the tactics of repartimentos, the galleon goes to Santiago - the sugar plantations of Cuba are in dire need of workers. Your task is to capture this galleon along with the cargo. Payment for the goods is, as usual, 200 piastres per unit.";
			link.l1 = "Heh! It sounds tempting. I agree.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "You know, I don't like this repartimentos of yours, it's too cynical. I guess I won't do this case.";
			link.l2.go = "SlaveGalleon_end";
		break;

		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add;
			dialog.text = "Well, then, I wish you good luck. Keep in mind: this galleon is operated by a very experienced naval officer. The fight with him will not be easy, so prepare yourself properly. And don't waste any time - it will take him fifteen to twenty days to get " + sTemp + " to Santiago. Try not to miss it, keep your eyes open - you can easily distinguish this galleon from other ships! I almost forgot! In addition, the ship will be full of all sorts of Indian trinkets - the Redskins pay their debts with the goods of their crafts and objects of worship. If you find anything unusual on the galleon, be sure to grab it and bring it to me - I will pay generously for every valuable find.";
			link.l1 = "I understand you. I'm moving out immediately.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 21, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("Oh", "oh"));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;

		case "Lostgalleon":
			dialog.text = "Eh, " + pchar.name + ", this was my last hope... That's why I assigned the case to you-no one else could have handled it anyway... As it turned out, so are you. Well, let's say goodbye. After the failure yesterday and the bad rumors that followed, my entire clientele fled. I'm practically bankrupt, and I may have to leave this city. But I don't blame you - the task was very difficult. Eh-H... Goodbye, " + pchar.name + ".";
			link.l1 = "I'm really sorry, " + npchar.name + "that everything turned out that way. Honestly. Maybe it's still working out. Goodbye.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questdata.Rabotorgovets = 1;
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1)
			{
				dialog.text = "Phew, such a relief... It's not for nothing that I trusted you, it's not for nothing... And why such irony? Is something wrong?";
				link.l1 = "And to the fact, dear, that your galleon was not a galleon at all... Well, or a very large galleon... The devil!! It was a battleship! And you didn't warn me about it! However, I captured him. I have "+ sTemp +" slaves in my holds, and I am ready to I'll give them to you. According to our agreement, you owe me " + FindRussianMoneyString(iSlaveMoney) + ". And compensation for misinformation would also be nice.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Have you found the galleon? Where are the slaves? There should have been at least three thousand slaves! Damn it, there are only scoundrels and traitors around! I didn't expect this from anyone, but from you... You were my last hope, if that's the case... I swear, I will spend the rest of my fortune and go to the porch, but I will make sure that the whole fleet will chase you " + NationNameGenitive(sti(npchar.nation)) + "! Get out of my sight!";
				link.l1 = "Um...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;

		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			pchar.questdata.Rabotorgovets = 1;
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;

		case "Wingalleon_1":
			dialog.text = "What are you talking about! I swear, I didn't know that. It was supposed to be a heavy galleon, but not a battleship! Apparently, something changed at the last moment... But you did it!Counting the money and compensating your unplanned expenses, I completely agree, I admit everything, but there is one circumstance of irresistible force - I simply do not have such a large amount now. Recent problems... Well, you know everything yourself. But don't get too excited, " + pchar.name + " for God's sake. You give me the goods, I will sell it - the customer is already waiting, but in five days I will have the entire amount, and I will pay you in full. You can be sure of that. And to make sure, I'm ready to give you all the cash that I have at the moment - all my loans.";
			link.l1 = "Hmm... I was counting on get the money now. If you only knew what a fight I had to endure! Oh, okay... I'll get into your position. But keep in mind: just try to cheat me - I'll get it in Europe!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "You know what, " + npchar.name + ", go to hell. That's not what we agreed on. You can't even imagine what a fight I had to endure. I will keep all the slaves for myself and implement them without your mediation.";
			link.l2.go = "Wingalleon_no";
		break;

		case "Wingalleon_no":
			dialog.text = "Oh, so that's how we started talking! So, while I was a cash cow for you, you were satisfied with everything, and as soon as the matter touched on the postponement, you are ready to step over it and conduct business on your own. At the same time, you immediately forgot that you received a tip on this prey from me, if so... I swear, I will spend the rest of my fortune and go to the porch, but I will make sure that the whole fleet will chase you " + NationNameGenitive(sti(npchar.nation)) + "! Get out of my sight!";
			link.l1 = "Don't scare me, you empty money bag. I'll feed your fleet to the crabs. Have a nice stay!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Wingalleon_yes":
			dialog.text = "Thanks for understanding, " + pchar.name + ". I promise, everything will be in the best possible way, so your threats are not necessary here, take this as an advance payment. There are fifteen chests here. Ten will be offset in the final calculation, and take five for yourself as compensation for moral damage. Come back for the rest in five days.Don't forget to bring all the Indian items you found on the captured ship... if they found it, of course. I have nothing to offer you for them now anyway.";
			link.l1 = "In exactly five days, " + npchar.name + ". In exactly five days...";
			link.l1.go = "Wingalleon_yes_1";
		break;

		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("You got the credit chests");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;

		case "FindRat":
			dialog.text = "As I promised, " + pchar.name + ", I am ready to pay you back. The slaves are sold, the customer is satisfied, and so are we. With the advance payment, the amount due to you is " + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + ". Please, get your money.";
			link.l1 = "Excellent, " + npchar.name + ". It's nice to deal with a man who can keep his word...";
			link.l1.go = "FindRat_1";
		break;

		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "You can always take my word for it, " + pchar.name + ". I have never given you any reason to doubt it yet. It will continue to be so. The honesty of partners with each other is the foundation of success in any joint business Now about Indian artifacts. Show me what you have there, otherwise, as a devout collector, I'm already exhausted.";
			link.l1 = "Hmm... Look, please.";
			link.l1.go = "FindRat_2";
		break;

		case "FindRat_2":
			if (CheckCharacterItem(pchar, "indian15"))
			{
				dialog.text = "Here! Wonderful! The basalt head of the Olmecs! This is a rare artifact. I've wanted to have it in my collection for a long time. I offer you 30,000 for it, or an exchange for a Tlaloc statuette, I have two of them.";
				link.l1 = "I'll take the money.";
				link.l1.go = "BG_money";
				link.l2 = "I am exchanging this item for a Tlaloc statuette.";
				link.l2.go = "BG_change";
				link.l3 = "I'll keep this artifact for myself.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "So-so... Unfortunately, there is nothing that could interest me.";
				link.l1 = "Well, no, no, whatever you say.";
				link.l1.go = "BG_PF";
			}
		break;

		case "BG_money":
			dialog.text = "Wonderful! Here are your 30,000, and this Olmec head is mine now.";
			link.l1 = "Fine. Well, if that's all you're interested in...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You gave away the basalt head");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian15", 1);
		break;

		case "BG_change":
			dialog.text = "Wonderful! Here is your statuette, and this Olmec head is now mine.";
			link.l1 = "Fine. Well, if that's all you're interested in...";
			link.l1.go = "BG_PF";
			Log_Info("You gave away the basalt head");
			Log_Info("You got a Tlaloc statuette");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian15", 1);
			TakeNItems(pchar, "indian19", 1);
		break;

		case "BG_no":
			dialog.text = "Well, as you know. Although it's a pity, it's a pity...";
			link.l1 = "Well, if that's all you're interested in...";
			link.l1.go = "BG_PF";
		break;

		case "BG_PF":
			dialog.text = "Wait! Let me take another look...";
			link.l1 = "Please watch, choose.";
			link.l1.go = "PF_check";
		break;

		case "PF_check":
			if (CheckCharacterItem(pchar, "indian2"))
			{
				dialog.text = "Here! I didn't notice her right away! I'm interested in this Indian boy figurine. A very interesting subject, I tell you... I am ready to pay 20,000 piastres for it, or exchange it for a Shiucoatl amulet.";
				link.l1 = "I'll take the money.";
				link.l1.go = "PF_money";
				link.l2 = "I'm changing this item to a Shiucoatl amulet.";
				link.l2.go = "PF_change";
				link.l3 = "I'll keep this artifact for myself.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "No, um... After all, you don't have anything I need.";
				link.l1 = "Oh well! There is no trial either.";
				link.l1.go = "FindRat_3";
			}
		break;

		case "PF_money":
			dialog.text = "Wonderful! Here are your 20,000, and this figurine is mine now.";
			link.l1 = "Fine. I was very satisfied with our deal.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You gave away a frightening figurine");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian2", 1);
		break;

		case "PF_change":
			dialog.text = "Wonderful! Here is your amulet, and this figurine is mine now.";
			link.l1 = "Fine. I was very satisfied with our deal.";
			link.l1.go = "FindRat_3";
			Log_Info("You gave away a frightening figurine");
			Log_Info("You have received the amulet of Shiucoatl");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian2", 1);
			TakeNItems(pchar, "indian6", 1);
		break;

		case "PF_no":
			dialog.text = "Well, as you know. Although it's a pity, it's a pity...";
			link.l1 = "I need this statuette for myself, I'm sorry.";
			link.l1.go = "FindRat_3";
		break;

		case "FindRat_3":
			dialog.text = "Well... By capturing this galleon... I'm sorry, battleship, you literally saved me. I am glad to cooperate with you, " + pchar.name + ". I probably didn't have a single agent better than you.";
			link.l1 = "Flattered, I won't hide it. But you exaggerate my merits somewhat...";
			link.l1.go = "FindRat_4";
		break;

		case "FindRat_4":
			dialog.text = "I'm being completely serious. And it is precisely because you have such outstanding abilities, and because I fully trust you, that I ask you to carry out my next assignment.";
			link.l1 = "Heh! Unexpectedly! I'm listening carefully. Where is the next galleon with slaves?";
			link.l1.go = "FindRat_5";
		break;

		case "FindRat_5":
			dialog.text = "This time I will have a different task for you that has nothing to do with slaves. Are you surprised? I will pay well for completing this assignment... I'll pay you very well.";
			link.l1 = "Let's get to the point.";
			link.l1.go = "FindRat_6";
		break;

		case "FindRat_6":
			dialog.text = "This case is directly related to recent events, which, by the way, you were also involved in... So, as you know, I am engaged in an illegal business - the slave trade. You also know that I hire privateers like you to run errands. Recently, one of my people, for a reason completely incomprehensible to me, betrayed me - made a denunciation and collected evidence incriminating me and my confidants in the illegal slave trade. You saw the consequences - a ship with soldiers arrived here from a neighboring colony, well... You know the rest, but it was with great difficulty that we managed to resolve the situation, as well as hide the circumstances of the destruction of the pinnace and the murder of soldiers in my house. As you understand, betrayal cannot go unpunished. Besides, I can't live and work peacefully knowing that this rat is alive and walking around the archipelago. I set bounty hunters on this scoundrel, but so far the result is zero, I ask you to personally take up this case. Moreover, the betrayal of this scoundrel has directly affected you.";
			link.l1 = "Hmm... This scoundrel should be strung up on the yardarm! Let me know more information about him, and, of course, the amount of the fee for the work.";
			link.l1.go = "FindRat_7";
		break;

		case "FindRat_7":
			dialog.text = "Don't worry about the reward. I will pay you handsomely for its destruction, and not only with money. I will not spare the best things from my Indian collection. Now about him. This rat's name is Francois Gonthier, and a long time ago, to cover his tracks - because he knows that I'm after him - he sold his frigate at one of the shipyards of the archipelago and disappeared. I managed to find out from my colleagues that he had recently been seen in Panama. Perhaps you should start looking from there.";
			link.l1 = "Well, I'm moving out immediately.";
			link.l1.go = "FindRat_8";
		break;

		case "FindRat_8":
			dialog.text = "I wish you good luck. And be careful: Scoundrel Gontier is a very experienced sailor, and has a team of desperate thugs. He has nothing to lose, so he will fight desperately.";
			link.l1 = "And you've seen less formidable ones... But I will take note of your words. Goodbye, and rest assured - I will find him even in hell.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;

		case "Wincorvette":
			dialog.text = "Great! Now let him scribble his denunciations to the jellyfish. No one dares to shit on me with impunity! Thank you, " + pchar.name + "you are just an irreplaceable person.";
			link.l1 = "Thank you, " + npchar.name + ", for a flattering assessment of my actions. What about the payment?";
			link.l1.go = "Wincorvette_1";
		break;

		case "Wincorvette_1":
			dialog.text = "Yes, of course. I will pay for this most difficult job accordingly. I am giving you the pride of my collection, the Atlaua statuette, free of charge. I hope you are aware that this is not a simple trinket?";
			link.l1 = "Wow, what a gift! Yes, I know, it's the 'lord of the waters', a magical statue. A very necessary thing for a sailor.";
			link.l1.go = "Wincorvette_2";
		break;

		case "Wincorvette_2":
			dialog.text = "In addition, I will pay you 100,000 piastres of premium and 50,000 piastres to cover travel expenses.";
			link.l1 = "Thank you, " + npchar.name + ". Once again, it's a pleasure to work with you.";
			link.l1.go = "Wincorvette_3";
			Log_Info("You got the Atlaua idol");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "indian18", 1);
		break;

		case "Wincorvette_3":
			dialog.text = "Well, as usual, in a month, I'm waiting for you at my place. A very large-scale case is being prepared, and you will need a well-equipped squadron. Please take my words seriously and prepare yourself properly. If it works out, you and I will become rich.";
			link.l1 = "Okay, " + npchar.name + ". I will arrive fully armed.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;

		case "Lostcorvette":
			dialog.text = "Sorry, very sorry... Well, don't get too upset, you are not the first, who failed to catch this crook. It's okay, I'll nail him anyway, and I'm waiting for you in a month. A very large-scale case is being prepared, and you will need a well-equipped squadron. Please take my words seriously and prepare yourself properly. If it works out, you and I will become rich.";
			link.l1 = "Okay, " + npchar.name + ". I will arrive fully armed.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;

		case "Havana_fort":
			dialog.text = "You are very timely, " + pchar.name + "! I was already starting to worry, and I was going to send a man to look for you, let's get started! The task in front of you this time will be very serious, but the reward will be appropriate. After the operation, you will receive a million or more.";
			link.l1 = "That's the thing! I'm listening to you carefully, " + npchar.name + ".";
			link.l1.go = "Havana_fort_1";
		break;

		case "Havana_fort_1":
			dialog.text = "During the last month, enslaved Indians were brought to Havana from all over Main in small batches, in addition, several galleons with 'black ivory' arrived there from Africa and unloaded. At the moment, there are at least five thousand slaves in Havana, behind the high walls of the fort.";
			link.l1 = "I feel that it will be nothing more or less than the storming of Havana.";
			link.l1.go = "Havana_fort_2";
		break;

		case "Havana_fort_2":
			dialog.text = "You understand everything correctly, " + pchar.name + ". That's exactly what I want you to do. You and only you. I don't think any of my other agents will be able to carry out such a serious operation, surely you will take on this case?";
			link.l1 = "To be honest, " + npchar.name + ", I'm somewhat taken aback. I didn't think that your activity is so... it is large-scale. Of course I will. " + RandSwear() + "";
			link.l1.go = "Havana_fort_3";
			link.l2 = "You know what, " + npchar.name + ", it doesn't fit in any gate anymore. I'm tired of your surprises. With your greed, I will have to go to war against Spain tomorrow. If you need these slaves, storm Havana personally.";
			link.l2.go = "Havana_fort_not";
		break;

		case "Havana_fort_not":
			dialog.text = "I didn't expect this from you. I didn't expect it... What the hell am I going to tell the customer now? Okay. If you don't want to, I'll look for another performer. Goodbye, " + pchar.name + ". I do not think that I will continue to use your services. And remember - you voluntarily gave up a business that could provide for all your descendants up to the seventh generation.";
			link.l1 = "You won't earn all the money. Have you never heard the saying 'a big spoon tears your mouth'? Have a nice day, " + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ся", "as"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;

		case "Havana_fort_3":
			dialog.text = "I had no doubt that I would hear exactly this answer. A few details: The fort of Havana is not easy to take, but now this task has become even more difficult. Two battleships are constantly cruising along the shores of Havana at the moment - they guard the approaches to the city from the sea. You will need to get rid of these ships before launching an assault...";
			link.l1 = "Understood. It's not the first time I've fought a battle against battleships. How much time do I have?";
			link.l1.go = "Havana_fort_4";
		break;

		case "Havana_fort_4":
			dialog.text = "A little bit. Three weeks, no more. After that, the slaves will be sent to the Spanish trading posts in Cuba. So you should hurry up.";
			link.l1 = "Then let's not delay. I'm going!";
			link.l1.go = "Havana_fort_5";
		break;

		case "Havana_fort_5":
			dialog.text = "Just a minute! " + pchar.name + ", you and I have never had misunderstandings and disagreements. But I still want to inform you about the current state of affairs. I am counting on you, and the customer is counting on me, and I, and he, have already invested forces and funds in this enterprise, and quite a lot - to obtain the information that I have now provided to you. All captured slaves, all five thousand units of goods, must be delivered to me safely, otherwise we will take very, very drastic measures against you. I ask you not to take offense at this warning, but just take note.";
			link.l1 = "Don't worry, " + npchar.name + ", I understand what business is. See you later.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;

		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Well, what are the results of your victory in the material equivalent, so to speak?";
				link.l1 = "I have " + sTemp + " slaves in my holds.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "So-so... Have you forgotten what I told you? You were supposed to bring me at least five thousand slaves, but for some reason you have only " + sTemp + ". How did it happen?";
				link.l1 = "Um... Not everyone moved the way in the holds here from Havana...";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "So-so... Have you decided to cheat me? Have you forgotten what I told you? Where are my slaves? Where are they, I ask you?!";
			link.l1 = "Um... Here such a thing happened...";
			link.l1.go = "Havana_Fort_no";
		break;

		case "Havana_Fort_no":
			dialog.text = "Okay. No explanation is needed. I'll give you a week to deliver at least five thousand slaves to me according to our agreement. Otherwise, blame yourself!";
			link.l1 = "Okay, okay, don't get all worked up, you'll have your five thousand slaves!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;

		case "Havana_Fort_yes":
			dialog.text = "Great! As always, you did a great job with my assignment. I am very, very pleased with you.";
			link.l1 = "I'm satisfied with myself too... But I will be even more pleased when I get the money for the goods.";
			link.l1.go = "Havana_Fort_yes_1";
		break;

		case "Havana_Fort_yesA":
		dialog.text = "Well, I'm very, very happy about it. Despite the delay, you did a brilliant job on my assignment.";
			link.l1 = "Well, now I want to get paid for the goods.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;

		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Yes, absolutely. I will transfer the slaves to the customer, he will pay off, and you will receive your money. It's just like last time. Let's do the math: you have brought " + sTemp + " slaves. Accordingly, the amount due to you is " + FindRussianMoneyString(iSlaveMoney) + ". In a week, come to me for a settlement.";
			link.l1 = "Okay, " + npchar.name + ", agreed. Wait for me in a week. But look...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;

		case "Havana_Fort_yes_2":
			dialog.text = "" + pchar.name + "Please don't go on. We are partners, and there can be no deception and distrust between partners. I promised you a lot of money - you got it, I promised you lucrative jobs - you have them. I compensated your expenses and covered your expenses even during the most difficult times for my business. Can you complain that I didn't keep my word at least once?";
			link.l1 = "Um... no.";
			link.l1.go = "Havana_Fort_yes_3";
		break;

		case "Havana_Fort_yes_3":
			dialog.text = "You see... " + pchar.name + ", you are my best agent, and I look forward to doing business with you in the future. Maybe you should stop constantly expressing your distrust of me, and even in such a situation... in a harsh form?";
			link.l1 = "Okay, " + npchar.name + ". Just understand me: a million is not a small amount.";
			log_info("You got a Khanda.");
			TakeNItems(pchar, "blade42",1);
			TakeNItems(pchar, "talisman16",1);
			TakeNItems(pchar, "cirass5",1);
			link.l1.go = "Havana_Fort_yes_4";
		break;

		case "Havana_Fort_yes_4":
			dialog.text = "I understand you perfectly, but you also understand that the goods must first be sold, and only then get the money.";
			link.l1 = "Okay. Let's assume that we understand each other.";
			link.l1.go = "Havana_Fort_yes_5";
		break;

		case "Havana_Fort_yes_5":
			dialog.text = "That's great. I'll be waiting for you at my place in a week. And now I need to prepare a deal with the customer.";
			link.l1 = "Then I won't interfere. See you in a week, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "What am I doing here? Hm... This is my bank. I just bought it a couple of days ago. As the first client, I can offer you very favorable loan terms...";
			link.l1 = "To hell with loans! Where " + pchar.questTemp.Slavetrader.Name + "?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Hush, hush, don't shout! He hasn't been here for a long time.";
			link.l1 = "How not?";
			link.l1.go = "Usurer_Escape_2";
		break;

		case "Usurer_Escape_2":
			dialog.text = "Don't you know? He disappeared a week ago. Then it turned out that he had taken the money of all his depositors with him. They say even the governor got hurt. He abandoned this house, and I bought it from the city.";
			link.l1 = "Where did he disappear to? How?";
			link.l1.go = "Usurer_Escape_3";
		break;

		case "Usurer_Escape_3":
			dialog.text = "I heard that he sailed away from our colony... I see he owes you one too... A lot?";
			link.l1 = "More than a million! Well, I'm going to get that rat anyway! Is it unknown where he sailed? On which ship?";
			link.l1.go = "Usurer_Escape_4";
		break;

		case "Usurer_Escape_4":
			dialog.text = "No one knows. Nothing. Generally. He seemed to have disappeared. He was and he wasn't. On that day, a fluyt came out of the harbor, either 'Mauritius' or 'Mavrodi' - he probably disappeared on it.";
			link.l1 = "Damn it! It was necessary to trust such a scoundrel! He reeked of meanness a mile away! And I, the simpleton, believed that we are really partners! But he's going to regret it... Okay, " + npchar.name + " Please excuse me for being rude... Goodbye.";
			link.l1.go = "Usurer_Escape_5";
		break;

		case "Usurer_Escape_5":
		string sColony;
		sColony = npchar.city;
		SetNull2Deposit(sColony);
			dialog.text = "Nothing, I understand everything. If you need money, or vice versa, you want to open a deposit, I am always at your service.";
			link.l1 = "Thank you. But I'd rather keep the money to myself. Have a nice day.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ate", "la"));
			CloseQuestHeader("Slavetrader");
			pchar.questdata.Rabotorgovets = 1;
			pchar.questTemp.Slavetrader = "wait1";
		break;

		//<--работорговец
		
		//Квест "Money in growth" -->
		
		case "KSM_DVR_1":
			dialog.text = "Yes, yes. Some delicate business... One man, Simon Barton, took a rather large sum from me, at a good percentage. Yes, but he's in no hurry to return it.";
			link.l1 = "The situation is unpleasant. Why did you give money to such a dubious person?";
			link.l1.go = "KSM_DVR_2";
		break;

		case "KSM_DVR_2":
			dialog.text = "Simon seemed to be quite a successful businessman. But his entire fortune went down in one day, along with the ship belonging to him... And now he's drinking away the gold he borrowed from me.";
			link.l1 = "I can visit Mr. Simon and ask him for a refund.";
			link.l1.go = "KSM_DVR_3";
			link.l2 = "I'm not interested in knocking out debts. Goodbye.";
			link.l2.go = "KSM_DVR_2_2";
		break;
		
		case "KSM_DVR_2_2":
			DialogExit();
			pchar.questTemp.KSM_DVR_Rostovshik = true;
		break;

		case "KSM_DVR_3":
			pchar.Quest.KSM_DVR_Dengi.FindCitizenMoney = ((7 + Rand(sti(PChar.rank)))/2)*350 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + Rand(20)*10 * GetCharacterSPECIALSimple(PChar, SPECIAL_L);
			int KSM_DVR_Schitaem = pchar.Quest.KSM_DVR_Dengi.FindCitizenMoney;
			if(KSM_DVR_Schitaem < 10000) { KSM_DVR_Schitaem = 10000 + drand2(1000); }
			if(KSM_DVR_Schitaem > 30000) { KSM_DVR_Schitaem = 30000 + drand2(1000); }
			dialog.text = "He took " + KSM_DVR_Schitaem + " piastres... It would be great if you could withdraw at least half of it. In addition, your share also depends on how much money you will be able to return.";
			link.l1 = "In my opinion, everything is fair. Where should I look for Mr. Barton?";
			link.l1.go = "KSM_DVR_4";
		break;

		case "KSM_DVR_4":
			dialog.text = "It looks like Simon has gone a little crazy from his troubles. He sits in Palm Beach Bay all day, waiting for his ship to appear on the horizon...";
			link.l1 = "I'll find him.";
			link.l1.go = "KSM_DVR_4_1";
		break;
		
		case "KSM_DVR_4_1":
			DialogExit();
			pchar.questTemp.KSM_DVR_Rostovshik = true;
			SetQuestHeader("KSM_DVR");
			AddQuestRecord("KSM_DVR", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("KSM_DVR_Saiman", "trader_14", "man", "man", 3, PIRATE, -1, false));
			sld.name = "Simon";
			sld.lastname = "Barton";
			sld.dialog.filename = "Quest\KSM\Dengi_v_rost.c";
			sld.dialog.currentnode = "simon_bazar";
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Shore22", "smugglers", "smugglerload");
			
			for (i=1; i<=3; i++)									//Количество
			{
				sTemp = "pirate_"+(rand(4)+1);
				sld = GetCharacter(NPC_GenerateCharacter("KSM_DVR_SaimanOhrana_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
				sld.dialog.filename = "Quest\KSM\Dengi_v_rost.c";
				sld.dialog.currentnode = "simon_helper_bazar";
				LAi_SetStayType(sld);
				LAi_SetImmortal(sld, true);
				ChangeCharacterAddressGroup(sld, "Shore22", "smugglers",  "smuggler0"+i);
			}
			AddGeometryToLocation("Shore22", "smg");
		break;
		
		//<-- Квест "Money in growth"

		/* Обмен камней */
		case "Gems_exchange_1":
			DialogExit();
			LaunchItemsExchange();
		break;
	}
}

int findCitizenMan(ref NPChar, bool bCity)
{
    ref ch;
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (bCity && sti(Pchar.Ship.Type) == SHIP_NOTUSED)
	{
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(11)+1), "man", "man", 10, sti(npchar.nation), -1, false));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = npchar.city;
		ch.RebirthPhantom = true;
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(npchar.nation)) + "_citizens");
		PlaceCharacter(ch, "goto", npchar.city + "_town");
	}
	else
	{
		for(n=0; n<MAX_COLONIES; n++)
		{
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
			if (nation != RELATION_ENEMY && colonies[n].nation != "none")
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
		if (howStore == 0) return -1;
		nation = storeArray[cRand(howStore-1)];
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(11)+1), "man", "man", 10, sti(colonies[nation].nation), -1, false));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = colonies[nation].id;
		ch.RebirthPhantom = true;
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(colonies[nation].nation)) + "_citizens");
		PlaceCharacter(ch, "goto", colonies[nation].id + "_town");
	}
	return sti(ch.index);
}

int findChestMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[TOTAL_CHARACTERS];
    int howStore = 0;
	string sTemp, sCity;

	for(n=2; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		sTemp = ch.id;
		if (CheckAttribute(ch, "City") && ch.id != "Jackman") sCity = ch.City;
		else continue;
		if (sti(ch.nation) == PIRATE) continue; // пираты не имеют реплик
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
		// магазины
		if (sTemp == "trader")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
        // мэры
		if (sTemp == "Mayor")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
			if (ch.location != ch.Default) continue; //захвачанных мэров не надо
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
        // верфисты
		if (sTemp == "shipyarder")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman" || ch.City == "DesMoines") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
		// тавернщики
		if (sTemp == "tavernkeeper")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
	    // церковники
		if (sTemp == "Priest")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
		// ростовщики
		if (sTemp == "usurer")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
		// начальники портов
		if (sTemp == "PortMan")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none" || ch.City == "Caiman" || ch.City == "DesMoines") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[cRand(howStore-1)];
    }
}

void SlavetraderGalleonInWorld()
{
	//создаём галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, -1, true));
 	SetCaptanModelByEncType(sld, "war");
	FantomMakeCoolSailor(sld, SHIP_INGERMANLAND, sName, CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade28", "pistol5", 100);//создание фантома кэпа
	sld.Ship.Mode = "war";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	sld.WatchFort = true; //видеть форты
	sld.AlwaysEnemy = true;
	sld.SuperShooter  = true;
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";//какую группу уничтожить
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";//это победа
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("The cap of the galleon came out of: " + sld.city + " and headed to: " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даём с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
	sld.lifeDay = 20;
}


int PcharReputation()
{
	//Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
	return makeint(42 - sti(pchar.reputation)*0.33);
}

void CheckForAchievement()
{
	int deposits = 0;
	if (CheckAttribute(pchar, "Quest.Deposits")) // не треться при возврате
	{
		aref quest;
		aref quests;
		makearef(quests,Characters[GetMainCharacterIndex()].Quest.Deposits);

		int nQuestsNum = GetAttributesNum(quests);

		for(int n = 0; n < nQuestsNum; n++)
		{
			quest = GetAttributeN(quests,n);

			string sQuestName = GetAttributeName(quest);
			if (CheckAttribute(Pchar, "Quest.Deposits."+sQuestName+".Sum"))
			{
				int iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sQuestName).StartYear),makeint(Pchar.Quest.Deposits.(sQuestName).StartMonth),makeint(Pchar.Quest.Deposits.(sQuestName).StartDay), makefloat(Pchar.Quest.Deposits.(sQuestName).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				deposits += makeint(Pchar.Quest.Deposits.(sQuestName).Sum) + ((makeint(Pchar.Quest.Deposits.(sQuestName).Sum)/100)*makeint(Pchar.Quest.Deposits.(sQuestName).Interest))*iPastMonths;
			}
		}
	}
	if(deposits >= 50000000) UnlockAchievement("bank_money", 3);
}
