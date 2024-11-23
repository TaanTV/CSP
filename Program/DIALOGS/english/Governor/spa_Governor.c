// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, iTemp, iMoney, ShipType, Rank;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind...", "I have nothing to talk about right now.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Guber") && pchar.questTemp.PDM_Novaya_Rodina.Guber == "HugoLesopilka")	//Квест "A New Homeland.". Спрашиваем про Лесопилку.
			{
				link.l2 = "One of the pirates wants to join your service. He is willing to pay 10,000 gold for a patent that will allow him to serve with you.");
				link.l2.go = "HugoLesopilka_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Guber") && pchar.questTemp.PDM_Novaya_Rodina.Guber == "Lubopitno")	//Квест "A New Homeland.". Спрашиваем про Лесопилку.
			{
				link.l2 = "How's that Hugo Sawmill?");
				link.l2.go = "HugoLesopilka_Lubopitno_1";
			}
		break;

		case "work_1":  // работа на благо короны - линейка нации
            // сюда вход только с патентом, проверка выше
			//if (CheckAttribute(npchar, "notQuestLine"))
			//{
            //    dialog.text = "Unfortunately, I cannot provide you with a job. You are not the person I would like to entrust my affairs to. Goodbye.";
            //    link.l1 = "Wow...";
            //    link.l1.go = "exit";
			//	break;
			//}
            dialog.text = LinkRandPhrase("You are in the service of Spain! I ask you to immediately begin to carry out the task assigned to you!",
                                         "Start fulfilling your obligations immediately!",
                                         "I am waiting for your report on the fulfillment of my responsible assignment, but not for conversations.");
            link.l1 = RandPhraseSimple("I'm starting immediately, Senor Governor General", "I'm already in the process of doing...");
            link.l1.go = "exit";

        	switch (pchar.questTemp.State)   // что делаем в данный момент
            {
                case "empty":   // Нет взятых квестов
                    if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
                    {
                        dialog.text = LinkRandPhrase("I don't have any responsible assignments for you at the moment. You can come to my residence later...",
                                                     "Please excuse me, I'm very busy at the moment!",
                                                     "Mind your own business for the time being, I don't have any assignments for you right now.");
                        link.l1 = "All right, Senor Governor General.";
                        link.l1.go = "exit";
                    }
                    else
                    {
						switch(pchar.questTemp.CurQuestNumber)   // Взятие квестов начиная со второго
                        {
                            case "2":
                                dialog.text = "Ah, here you are, " + pchar.name + "! They say that you have shown rare courage and resourcefulness! I am glad to inform you that the people you saved are already on their way to Castile. Their gratitude literally knows no bounds. Our friends in Port Royal are reporting downright fantastic things, saying that you hacked the English jailers to pieces!";
                                link.l1 = "Fear has big eyes, Don Francisco...";
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":
                                dialog.text = "Glad to see you again, "+ GetSexPhrase("my friend","senorita") +". I want to offer you a case, and I think it will be to your taste.";
                                link.l1 = "I'm all ears.";
                                link.l1.go = "Step_3_1";
                            break;
                            case "4":
                                dialog.text = "Listen, I have a very unusual task this time.";
                                link.l1 = "I'm listening carefully, Don Francisco.";
                                link.l1.go = "Step_4_1";
                            break;
                            case "5":
                                dialog.text = "I am placing you at the disposal of the Governor of Santiago, Jose Sancho Jimenez.";
                                link.l1 = "What I should do?";
                                link.l1.go = "Step_5_1";
                            break;
                            case "6":
                                dialog.text = "I have a task for you. Let's have some background...";
                                link.l1 = "I'm listening carefully, Don Francisco.";
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = "Our glorious corsair Manoel Rivero Pardal is now prowling off the coast of Antigua in search of British merchant ships. I have received information that French filibusters under the command of Moses Vauclain went to intercept him. Hurry to Antigua and provide the necessary assistance to Pardal. He is a symbol of our courage!";
                                link.l1 = "I got it, Don Francisco. I'm starting immediately.";
                                link.l1.go = "exit";
								pchar.questTemp.State = "Sp7SavePardal_toAntigua";
								AddQuestRecord("Spa_Line_7_SavePardal", "1");
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition.l1 = "location";
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition.l1.location = "Antigua";
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition = "Sp7SavePardal_FightNearAntigua";
							break;
                            case "8":
                                dialog.text = "It's very good that you showed up on time. I have a very important task for you. The fact is that the famous filibuster Captain Ansel managed to unite English and French privateers in order to attack Cumana.";
                                link.l1 = "Don Francisco, do you have information about the size and nature of this squadron?";
                                link.l1.go = "Step_8_1";
                            break;
                            case "9":
                                dialog.text = "You should go to Porto Bello immediately. The governor of the city is waiting for you there, he will set you a task.";
                                link.l1 = "Senor, could you describe in general terms what I have to do?";
                                link.l1.go = "Step_9_1";
                            break;
                            case "10":
                                dialog.text = "I ask you to go immediately to the governor of the city of Maracaibo to carry out a responsible assignment.";
                                link.l1 = "Again, Don Francisco?";
                                link.l1.go = "Step_10_1";
                            break;
                            case "11":
                                dialog.text = "Are you ready for a serious operation to storm fortified cities?";
                                link.l1 = "Always ready, Senior Governor General";
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = "Ah, here you are, Captain! I've been waiting for you...";
                                link.l1 = "Always at your service, Don Francisco.";
                                link.l1.go = "Step_12_1";
                            break;
						}
                    }
                break;

                case "":           // Квест №1, Спасти горожан от Моргана.
                    dialog.text = "Well, well, Captain, I have been informed of your arrival.";
                    link.l1 = "It is a great honor for me, Don Francisco. I did not expect that my humble person would receive the attention of such a high-ranking senior.";
                    link.l1.go = "Step_1_1";
                break;
                case "SaveFromMorgan_OutOfPrison":
                    dialog.text = "Report on your situation with the rescue of prisoners.";
                    link.l1 = "Your order has been fulfilled, Senor Governor-General.";
                    link.l1.go = "Step_1_7";
                break;
                case "Inquisition_backBad":
                    dialog.text = "Ah, here you are back, very good. How did the case that the Holy Inquisition entrusted to you go?";
                    link.l1 = "Not very good, Don Juan. But nothing terrible happened, which, in fact, pleases.";
                    link.l1.go = "Step_2_3";
                break;
                case "Inquisition_backPartGood":
                    dialog.text = "Ah, here you are back, very good. How did the case that the Holy Inquisition entrusted to you go?";
                    link.l1 = "More or less fine, Don Juan. The rear ones are partially executed, which is also, in fact, not bad.";
                    link.l1.go = "Step_2_3";
                break;
                case "Inquisition_backAllGood":
                    dialog.text = "Ah, here you are back, very good. How did the case that the Holy Inquisition entrusted to you go?";
                    link.l1 = "Successful in the extreme, Don Francisco. Everything is done in the best possible way, the Holy Inquisition is extremely happy.";
                    link.l1.go = "Step_2_3";
                break;
                case "TakeRockBras_RockSink":
                    dialog.text = "So, what do you tell me about Rock the Brazilian?";
                    link.l1 = "I attacked his corvette is in the coastal waters of Maracaibo, where he hunted our galleons. I'm sorry, Don Francisco, but I couldn't take him alive, he drowned with his ship...";
                    link.l1.go = "Step_3_6";
                break;
                case "TakeRockBras_DieHardRock":
                    dialog.text = "So, what do you tell me about Rock the Brazilian?";
                    link.l1 = "I was goingg to attack his corvette in the coastal waters of Maracaibo, where he hunted our galleons. Unfortunately, for reasons beyond my control, I had to leave the waters where Rock the Brazilian was located. He left me...";
                    link.l1.go = "Step_3_6";
                break;
                case "TakeRockBras_RockTaken":
                    dialog.text = "So, what do you tell me about Rock the Brazilian?";
                    link.l1 = "He's in my hold, Don Francisco.";
                    link.l1.go = "Step_3_7";
                break;
                case "TakeRockBras_RockGiven":
                    dialog.text = "Yes, yes, I have already been informed about the successful delivery of the Brazilian to Santiago. I can congratulate you.";
                    link.l1 = "Thank you, Don Francisco. What else can I do for you?";
                    link.l1.go = "Step_3_8";
                break;
                case "TakeRockBras_WaitTwoDays":
                if (GetQuestPastDayParam("questTemp") > 2)
                    {
                        dialog.text = "So, as I expected, the vaunted corsair could not endure the methods of interrogation with partiality adopted in the Holy Inquisition for a long time.";
                        link.l1 = "So he was tortured?";
                        link.l1.go = "Step_3_9";
                    }
                    else
                    {
                        dialog.text = "I asked you to come back in two days, not earlier.";
                        link.l1 = "Excuse me, Senor Governor General.";
                        link.l1.go = "exit";
                    }
                break;
                case "TakeRockBras_SeekRocksMoney":
                    dialog.text = "Well, tell me, what did you manage to find from the Brazilian's treasures?";
                    link.l1 = "Nothing new yet, Senor Governor-General. But I'm on the lookout...";
                    link.l1.go = "exit";
                    if (sti(pchar.money) > 500000)
                    {
                        link.l2 = "Don Francisco, I'm ready toreport back, the search is complete.";
                        link.l2.go = "Step_3_10";
                    }
                break;
                case "Sp4Detection_toMirderPlace":
                    dialog.text = "Have you been able to find out anything about this case?";
                    link.l1 = "I'm working, Don Francisco, but I haven't been able to find out anything yet...";
                    link.l1.go = "exit";
                break;
                case "Sp4Detection_toGovernor":
                    dialog.text = "Report what you have learned about this murder.";
                    link.l1 = "I managed to find out that the alleged killer is described as similar to Ladron. I believe that the traces of the crime lead to Tortuga.";
                    link.l1.go = "Step_4_6";
                break;
                case "Sp4Detection_toDEstre":
                    dialog.text = "I look forward to your report on the Tortuga investigation";
                    link.l1 = "Don Francisco, I found out on Tortuga that a certain Donna Anna is staying with Bertrand d'Ogeron is on maintenance. We can assume that this is Donna Anna Ramirez de Leyva, but I cannot say this with certainty.";
                    link.l1.go = "Step_4_9";
                break;
                case "Sp4Detection_toDEstre_1":
                    dialog.text = "I look forward to your report on the Tortuga investigation";
                    link.l1 = "Don Francisco, I found out on Tortuga that a certain Donna Anna is staying with Bertrand d'Ogeron is on maintenance. We can assume that this is Donna Anna Ramirez de Leyva, but I cannot say this with certainty.";
                    link.l1.go = "Step_4_9";
                break;
                case "Sp4Detection_toDEstre_2":
                    dialog.text = "I look forward to your report on the Tortuga investigation";
                    link.l1 = "Don Francisco, on Tortuga I found out that a certain Donna Anna is staying with Bertrand d'Ogeron is on maintenance. In addition, I managed to catch up with the Governor-General's confidant, a certain Henri d'Estre.";
                    link.l1.go = "Step_4_10";
                break;
                case "Sp4Detection_DEstreIsDead":
                    dialog.text = "Report, how is your investigation progressing?";
                    link.l1 = "I found out everything. The fact is that the wife of Don Jose Ramirez de Leyva voluntarily ran away to the Governor-General of Tortuga.'Augeron.";
                    link.l1.go = "Step_4_14";
                break;
                case "Sp5LaVegaAttack_BackToHavana":
                    dialog.text = "Yes, yes, I already know about your new successful enterprise. Well, I had no doubt that the place on Hispaniola for the settlement of our colonists from the Old World would be properly cleared.";
                    link.l1 = "The Buccaneers are finished, Don Francisco. And Edward Mansfield was killed by me personally!";
                    link.l1.go = "Step_5_3";
                break;
                case "Sp6TakeMess_waitMessanger":
                    dialog.text = "So, glad to see you, "+ GetSexPhrase("captain","senorita") +".";
                    link.l1 = "I'm glad to see you too, Don Francisco.";
                    link.l1.go = "Step_6_4";
                break;
                case "Sp6TakeMess_Action":
                    dialog.text = "So, glad to see you, "+ GetSexPhrase("captain","senorita") +".";
                    link.l1 = "I'm glad to see you too, Don Francisco.";
                    link.l1.go = "Step_6_4";
                break;
                case "Sp7SavePardal_PardalIsSink":
                    dialog.text = "Report on the results of the mission.";
                    link.l1 = "Senor, I couldn't save Pardal, his galleons were sunk by many times superior forces. Manoel himself died...";
                    link.l1.go = "Step_7_1";
                break;
                case "Sp7SavePardal_GoodWork":
                    dialog.text = "Report on the results of the mission.";
                    link.l1 = "Senor, the information you received turned out to be reliable. I sailed to Antigua on all sails and arrived just in time for Pardal - he and two galleons of his squadron were already fighting with superior forces of French pirates. Together we managed to defeat a strong enemy, the ships of the filibusters went down!";
                    link.l1.go = "Step_7_3";
                break;
                case "Sp7SavePardal_2GoodWork":
                    dialog.text = "Report on the results of the mission.";
                    link.l1 = "Senor, the information you received turned out to be reliable. I sailed to Antigua on all sails and arrived just in time for Pardal - two of his galleons were already fighting with superior forces of French pirates. Together we managed to defeat a strong enemy, the ships of the filibusters went down!";
                    link.l1.go = "Step_7_3";
                break;
                case "Sp7SavePardal_DieHard":
                    dialog.text = "Report on the results of the mission.";
                    link.l1 = "Senor Governor-General, unfortunately, this task turned out to be too much for me. I couldn't help Pardal.";
                    link.l1.go = "Step_7_6";
                break;
                case "Sp8SaveCumana_YouLate":
                    dialog.text = "Some of the refugees from Cumana have already arrived here. You failed to save the city and its inhabitants.";
                    link.l1 = "I went to Cumana on all sails, not staying anywhere even for a minute. But I still didn't have time, it was simply impossible to do it.";
                    link.l1.go = "Step_8_5";
					pchar.questTemp.Waiting_time = "20";
                break;
                case "Sp8SaveCumana_DieHard":
                    dialog.text = "Some of the refugees from Cumana have already arrived here. You failed to save the city and its inhabitants.";
                    link.l1 = "The assembled squadron of Ladrons was so strong that we could not cope with it. With the forces I had at my disposal, it was simply impossible to do this.";
                    link.l1.go = "Step_8_5";
					pchar.questTemp.Waiting_time = "40";
                break;
                case "Sp8SaveCumana_GoodWork":
                    dialog.text = "I have already been informed that Cumana has been saved. Great!";
                    link.l1 = "We managed to sink the Ladron fleet. No one left alive...";
                    link.l1.go = "Step_8_6";
                break;
                case "Sp9SaveCumana_BackHavana":
                    dialog.text = "Report what happened to you?";
                    link.l1 = "Don Francisco, I got the task to escort four golden galleons to the uninhabited Cayman Island from the Governor-General of Porto Bello...";
                    link.l1.go = "Step_9_2";
                break;
                case "Sp10Maracaibo_DieHard":
                    dialog.text = "I have been informed that Maracaibo has been captured and an English protectorate has been established there!";
                    link.l1 = "Yes, probably, sir.";
                    link.l1.go = "Step_10_6";
                break;
                case "Sp10Maracaibo_GoodWork":
                    dialog.text = "I already know, you did a brilliant job!";
                    link.l1 = "This time we had to sink the ships of the English pirates.";
                    link.l1.go = "Step_10_11";
                break;
                case "Sp10Maracaibo_2GoodWork":
                    dialog.text = "I already know, you did a brilliant job!";
                    link.l1 = "This time we had to sink the ships of the English pirates.";
                    link.l1.go = "Step_10_9";
                break;
                case "DestrHolland_GoOn":
                    dialog.text = "You have not yet managed to capture either Willemstad or Marigo...";
                    link.l1 = "Senor Governor General, I'm doing this. The task is not easy, it requires serious preparation.";
                    link.l1.go = "exit";
                    if (CheckAttribute(pchar, "questTemp.Q11_Villemstad"))
                    {
                        dialog.text = "You've ruined Willemstad, great! Now it's Marigo's turn!";
                        link.l1 = "Exactly so, Don Francisco...";
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Marigo"))
                    {
                        dialog.text = "Excellent, Marigo is ruined! But I also expect you to capture and ruin Willemstad.";
                        link.l1 = "I will do everything, Senor Governor.";
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Villemstad") && CheckAttribute(pchar, "questTemp.Q11_Marigo"))
                    {
                        dialog.text = "Marigo and Willemstad are stormed and ruined! Great job, "+ GetSexPhrase("my friend","" + pchar.name + "") +"!";
                        link.l1 = "It's done, Don Francisco...";
                        link.l1.go = "Step_11_3";
                    }
                break;
                case "OccupyPortPax_WeWin":
                    dialog.text = "Well, the Escorial can be congratulated on a worthy purchase. The island of Hispaniola is ours!";
                    link.l1 = "Exactly so, Senor Governor-General. I managed to capture Port-au-Prince.";
                    link.l1.go = "Step_12_4";
                break;
                case "QuestLineBreake":
                    dialog.text = "I don't deal with people breaking their word. I have nothing more to say to you.";
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
                case "EndOfQuestLine":
                    dialog.text = ""+ GetSexPhrase("Don","Donna") +" " + pchar.name + ", The Escorial gives you complete freedom of action in the interests of Spain. Act on your own.";
                    link.l1 = "All right, Don Francisco.";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
			}
        break;
        //********************** Квест №1, Спасти горожан от Моргана. ************************
        case "Step_1_1":
            dialog.text = "My attention can be earned by doing good for the great Castile, which you, Captain, have not yet.\n"+
                          "But you have a ship and a Spanish patent, which is important for my country. Especially now, when Spain's enemies have raised their heads and are trying to take revenge for all their past defeats.";
            link.l1 = "Is Spain's situation really that serious?";
            link.l1.go = "Step_1_2";
        break;
        case "Step_1_2":
            dialog.text = "Yes, although at first glance everything seems to be in order. Spain's wealth and power have always been envy of European monarchies. Now that our enemies are willing to attract bandits of all stripes, the situation has become depressingly difficult.\n"+
                          "Attacks on our colonies and trade caravans have increased, and kidnapping of wealthy and wealthy citizens for ransom has become commonplace. The pirates literally flooded all the trade routes, which made swimming in these waters very dangerous.\n"+
                          "The Escorial is furious, Her Majesty the Queen Mother demands immediate and decisive action to curb the illegal activities of ladrones of all stripes. To achieve this goal, it was decided to fight the enemy with his own methods, that is, to hire privateers to serve the crown.";
            link.l1 = "It looks like I'm on time...";
            link.l1.go = "Step_1_3";
        break;
        case "Step_1_3":
            dialog.text = "It looks like it is. Yesterday a person like you could only count on the bonfire of the Holy Inquisition or a hemp rope. But times have changed. Prove your devotion to our Lord and Castile, and you will have everything - wealth, fame, honors and rewards.";
            link.l1 = "Sounds good. I'm ready toproceed directly to the execution of the work.";
            link.l1.go = "Step_1_4";
        break;
        case "Step_1_4":
            dialog.text = "Well, let's get down to business.\n"+
                          "Three of our esteemed citizens have been captured by English pirates. And the ransom that Henry Morgan, known for his cunning, is asking for is beyond reasonable and conceivable. This bandit is demanding 500,000 in gold! You will need to get into Port Royal, free our citizens from prison and bring them safely to me.\n"+
                          "You must sneak into the prison and surprise the guards. The prisoners are guarded very carefully, so the escape will be known immediately. In this regard, it is preferable to land in a secluded bay, away from the fort. Under no circumstances do you endanger the lives of the people in your charge, this is a categorical requirement.\n"+
                          "Do you understand everything?";
            link.l1 = "Yes, senor Governor General.";
            link.l1.go = "Step_1_5";
        break;
        case "Step_1_5":
            dialog.text = "You have a month to release the prisoners, no more. Get ready and hit the road.";
            link.l1 = "I'm starting immediately.";
            link.l1.go = "Step_1_6";
        break;
        case "Step_1_6":
            SaveCurrentQuestDateParam("questTemp");
    		// остальные линейки в сад -->
    		pchar.questTemp.NationQuest = SPAIN;
    		// остальные линейки в сад <--
    		pchar.questTemp.State = "SaveFromMorgan_toPrison";
            AddQuestRecord("Spa_Line_1_SaveCitizens", "1");
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("SpaPrisoner"+i, "usurer_"+i, "man", "man", 10, SPAIN, -1, false));
                sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
                LAi_SetCitizenType(sld);
            	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
                ChangeCharacterAddressGroup(sld, "PortRoyal_Prison", "goto", "goto9");
            }
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        case "Step_1_7":
            dialog.text = "Well, you have taken the first successful step on the thorny career path for Her Majesty Queen Mother Maria Anna of Austria. Get an honestly earned 50 thousand. I'm glad I didn't make a mistake about you.";
            link.l1 = "Thank you, Mr. Governor General. By the way, you are an excellent mathematician.";
            link.l1.go = "Step_1_8";
        break;
        case "Step_1_8":
            dialog.text = "What are you talking about?";
            link.l1 = "Well, if you add one '0' to my received 50 thousand, then you will get the amount that you did not want to give to Henry Morgan.";
            link.l1.go = "Step_1_9";
        break;
        case "Step_1_9":
            dialog.text = "Ah, that's what you mean. Of course, we can afford to pay such a fabulous ransom, thereby proving that our citizens are dear to us, but then 50 thousand would not be so comfortably in your pocket, would it?";
            link.l1 = "Oh yes, sir. You have given an extremely instructive example!";
            link.l1.go = "Step_1_10";
        break;
        case "Step_1_10":
            dialog.text = "In that case, I dare not detain you any longer... Come to my residence from time to time.";
            link.l1 = "All right, sir.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "2";
			if (startherotype == 2)
			{
				pchar.questTemp.CurQuestNumber = "4";
			}
            pchar.questTemp.Waiting_time = "7";
            CloseQuestHeader("Spa_Line_1_SaveCitizens");
            AddMoneyToCharacter(pchar, 50000);
            for (i=1; i<=3; i++)
            {
                sld = characterFromId("SpaPrisoner"+i);
                RemovePassenger(pchar, sld);
         	    sld.LifeDay = 0; // уберём нпс
            }
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			AddCharacterExpToSkill(pchar, "Grappling", 120);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour("You know, our glorious Governor-General of Oregon and Gascon has hired a captain " + GetMainCharacterNameGen() + " to free our citizens captured by that devil Morgan. And you know, the assignment was successfully completed.", SPAIN, 5, 1);
		break;
        //********************** Квест №2, задания Инквизиции. ************************
        case "Step_2_1":
            dialog.text = "Your modesty does you credit... well, it's time for a new job. A high-ranking Jesuit, Antonio de Souza, has come to us and asked for a cold-blooded, courageous and honest officer.\n"+
                          "I recommended you. Go to Santiago, where the Office of the Inquisition for the Caribbean is located, and find de Souza. Do whatever he orders, without thinking about anything. Do you have any questions?";
            link.l1 = "No, senor Governor General.";
            link.l1.go = "Step_2_2";
        break;
        case "Step_2_2":
            dialog.text = "Then go ahead.";
            link.l1 = "...";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Inquisition_toDeSouza";
            AddQuestRecord("Spa_Line_2_Inquisition", "1");
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_2_3":
            dialog.text = "Well, that's nice. You will rest for a couple of weeks from the labors of the righteous for the benefit of the Church, and then I ask you to come to my office. I suppose I'll find you a new case.";
            link.l1 = "Always at your service, senor!";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "15";
            CloseQuestHeader("Spa_Line_2_Inquisition");
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);

			//слухи
			AddSimpleRumour("Rumor has it that the captain " + GetFullName(pchar) + " contracted to carry out the orders of de Souza himself! The Inquisition... At the very word, a shudder runs through my body.", SPAIN, 5, 1);
        break;
        //********************** Квест №3, захватить Рока Бразица. ************************
        case "Step_3_1":
            dialog.text = "So, do you know anything about Ladron Rock the Brazilian?";
            link.l1 = "Hmm, a famous person, a very dangerous privateer. Hanging out on Tortuga.";
            link.l1.go = "Step_3_2";
        break;
        case "Step_3_2":
            dialog.text = "Yes, it is. A real headache for us.\n"+
                          "So, I intend to get rid of this migraine myself and rid our colonists of it. I want you to capture this notorious Rock the Brazilian. And what is very important is that he was delivered alive.";
            link.l1 = "Is it necessary? It's going to be a big fight, you can be sure of that.";
            link.l1.go = "Step_3_3";
        break;
        case "Step_3_3":
            dialog.text = "So what? I don't really understand you, "+ GetSexPhrase("senor","senorita") +" " + pchar.name + ". Are you scared?!";
            link.l1 = "Don Francisco, I'm not afraid of the devil or the devil. I believe that you have had the opportunity to verify this! But what I mean is that I can't control the boarding completely. Anyone can die in such a cabin.";
            link.l1.go = "Step_3_4";
        break;
        case "Step_3_4":
            dialog.text = "I understand that. But still, I repeat - I need Rock the Brazilian alive. Or rather, not to me, but to the well-known Monsignor Antonio de Souza. This is a requirement of the Holy Inquisition, do you understand how important this is for us?";
            link.l1 = "Yes, sir, I understand. Well, I can promise you that I will do everything possible to successfully implement this assignment in full.";
            link.l1.go = "Step_3_5";
        break;
        case "Step_3_5":
            dialog.text = "Excellent! I'm waiting for your ship with Rock the Brazilian in the hold to raid Santiago Bay.";
            link.l1 = "Goodbye, senor.";
            link.l1.go = "exit";
            pchar.questTemp.State = "TakeRockBras_toTortuga";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "1");
        break;
        case "Step_3_6":
            dialog.text = "Hmm, that's bad. I'm disappointed in you.\n"+
                          "Now please leave me alone... However, you can come to my reception from time to time, perhaps there is something for you...";
            link.l1 = "I understand, Senior Governor General. Thank you...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "30";
            CloseQuestHeader("Spa_Line_3_RockBrasilian");
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			//слухи
			AddSimpleRumour("Did you hear that, Captain " + GetFullName(pchar) + "failed the task of the Governor-General to capture this creepy ladron Rock Brazilian. Loser, in a word...", SPAIN, 5, 1);
        break;
        case "Step_3_7":
            dialog.text = "Great! Now go to Santiago and hand him over to Monsignor Antonio de Souza.";
            link.l1 = "All right, senor, it will be done.";
            link.l1.go = "exit";
        break;
        case "Step_3_8":
            dialog.text = "Come to me in a couple of days, Monsignor Antonio has to work on this Brazilian, there should be news.";
            link.l1 = "Okay, I'll be with you in two days, sir.";
            link.l1.go = "exit";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "9");
            pchar.questTemp.State = "TakeRockBras_WaitTwoDays";
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_3_9":
            dialog.text = "Of course, not a morality to him Monsignor de Souza read! Rock the Brazilian got exactly what he deserved.\n"+
                          "He had repeatedly tortured Spanish citizens for the money they had hidden, and now, under torture by the Holy Inquisition, Rock had revealed the location of his own treasure. He separated him and hid him in several places in Cuba, Hispaniola and the Belize area.\n"+
                          "You have to find and deliver the Brazilian's caches to me. According to preliminary estimates, there are about 500,000 piastres in total!";
            link.l1 = "Not bad, perhaps! Senor, did you manage to get the exact location of the treasure?";
            link.l1.go = "Step_3_13";
        break;
        case "Step_3_13":
            dialog.text = "No, unfortunately...";
            link.l1 = "Maybe we should wait a bit and Monsignor Antonio will give us the necessary information?";
            link.l1.go = "Step_3_14";
        break;
        case "Step_3_14":
            dialog.text = "This is no longer possible - the Rock Brazilian gave his soul to our Lord. Amen...";
            link.l1 = "Amen... Senor, can I count on some of the treasures I found?";
            link.l1.go = "Step_3_15";
        break;
        case "Step_3_15":
            dialog.text = "Undoubtedly. A fifth of the Brazilian piastres found are yours. And don't bring it all to me separately, come right away when you get the required amount - 500 thousand.";
            link.l1 = "Okay, Senor Governor General, I will start searching immediately.";
            link.l1.go = "exit";
         	pchar.GenQuestBox.Cuba_Grot = true;
            pchar.GenQuestBox.Cuba_Grot.box1.items.gold = 150000;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian17 = 1;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian10 = 1;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian18 = 1;
         	pchar.GenQuestBox.Hispaniola_Cave = true;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.gold = 150000;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry5 = 250;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry14= 10;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.potion3 = 5;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.mineral8 = 1;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry7 = 5;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry2 = 20;
         	pchar.GenQuestBox.Beliz_Cave = true;
            pchar.GenQuestBox.Beliz_Cave.box1.items.gold = 50000;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian6 = 1;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian11 = 1;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian15 = 1;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian12 = 1;
            pchar.GenQuestBox.Beliz_Cave.box2.items.gold = 150000;
            pchar.GenQuestBox.Beliz_Cave.box2.items.potion5 = 10;
            pchar.GenQuestBox.Beliz_Cave.box2.items.potionrum = 2;
            pchar.GenQuestBox.Beliz_Cave.box2.items.potion4 = 10;
            pchar.questTemp.State = "TakeRockBras_SeekRocksMoney";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "8");
        break;
        case "Step_3_10":
            dialog.text = "Great! Now let's summarize... You contribute 500 thousand to the treasury of the Escorial, therefore, your share is 100 thousand piastres.";
            link.l1 = "Thank you, Senor Governor General.";
            link.l1.go = "Step_3_11";
        break;
        case "Step_3_11":
            dialog.text = "Okay... I dare not detain you now, but I ask you to be at my reception in a week.";
            link.l1 = "Okay, Don Francisco, I will be with you at the specified time. And now let me take my leave...";
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, -400000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "5";
            CloseQuestHeader("Spa_Line_3_RockBrasilian");
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			//слухи
			AddSimpleRumour("Have you not heard the wonderful news? Certain captain " + GetFullName(pchar) + " captured that vile Ladron Rock Brazilian. Praise God Almighty!", SPAIN, 5, 1);
        break;
        //********************** Квест №4, расследование убийства. ************************
        case "Step_4_1":
            dialog.text = "Havana is thrilled with a strange crime. The strangest thing is that it is completely incomprehensible how it happened.\n"+
                          "The commandant of Havana, Don Jose Ramirez de Leyva, was killed in his own house along with four servants. Everyone was in full combat gear, as if they were going to war.";
            link.l1 = "Wow! And no one heard anything? The cook, for example?";
            link.l1.go = "Step_4_2";
        break;
        case "Step_4_2":
            dialog.text = "No, there was no one else in the house except his wife. The day before, Don Jose caused a terrible scandal with his wife and sent all the female servants away.";
            link.l1 = "What does his wife say?";
            link.l1.go = "Step_4_3";
        break;
        case "Step_4_3":
            dialog.text = "She disappeared...";
            link.l1 = "How did it disappear, completely?";
            link.l1.go = "Step_4_4";
        break;
        case "Step_4_4":
            dialog.text = "No, partially... Think about what you're saying!";
            link.l1 = "I'm sorry, Don Francisco. It's all strange... You know, this is not my profile, I am not a detective. Let the commandant's office handle it.";
            link.l1.go = "Step_4_5";
        break;
        case "Step_4_5":
            dialog.text = "Don Jose was the commandant of Havana. Look, I can't force you to investigate crimes, but right now I'm asking you to do that.\n"+
                          "The city is excited, you know. And then there's the disappearance... We searched all around, to no avail. I need effective measures in the investigation immediately, and you are the best candidate at the moment.";
            link.l1 = "All right, Senor Governor General. I'll do what I can.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp4Detection_toMirderPlace";
            AddQuestRecord("Spa_Line_4_MirderDetection", "1");
			AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("","a"));
         	pchar.GenQuestBox.Havana_houseS1Bedroom = true;
            pchar.GenQuestBox.Havana_houseS1Bedroom.box2.items.letter_notes = 1;
        break;
        case "Step_4_6":
            dialog.text = "Tortuga is a refuge for bandits of all stripes... And what about Donna Anna?";
            link.l1 = "It's hard to guess... But here's what I found - an unfinished letter at the crime scene...";
            link.l1.go = "Step_4_7";
        break;
        case "Step_4_7":
            dialog.text = "(reads) Hmm, I don't even know what to say... You need to get into Tortuga and figure out what's what.";
            link.l1 = "All right, Don Francisco, I'll do it.";
            link.l1.go = "Step_4_8";
            TakeItemFromCharacter(pchar, "letter_notes");
        break;
        case "Step_4_8":
            dialog.text = "I am handing you the license of the French West India Company, valid for 20 days. This document will allow you to move freely around Tortuga. And I hope you will think to raise the French flag on the ship...";
            link.l1 = "Of course, Don Francisco, this is very useful. I think I'll start the task.";
            link.l1.go = "exit";
            GiveNationLicence(FRANCE, 20);
            pchar.questTemp.State = "Sp4Detection_toTortuga";
            AddQuestRecord("Spa_Line_4_MirderDetection", "4");
            sld = GetCharacter(NPC_GenerateCharacter("ServantDEstre", "Barmen_13", "man", "man", 10, FRANCE, -1, false));
        	sld.name 	= "Guido";
        	sld.lastname = "";
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
            LAi_SetStayType(sld);
        	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
            ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "goto", "goto2");
        break;
        case "Step_4_9":
            dialog.text = "Just speculation... uh, that's not enough to draw firm conclusions.\n"+
                          "I'm not happy with you. I'm asking you to leave me alone, I have no business for you.\n"+
                          "However, you can come to my office periodically, perhaps something insignificant will turn up...";
            link.l1 = "Okay, senor Governor General...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "30";
            CloseQuestHeader("Spa_Line_4_MirderDetection");
            TakeNationLicence(FRANCE);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour("You know, our Governor-General has instructed the captain " + GetMainCharacterNameDat() + " to investigate the murder of Commandant de Leyva. However, the captain turned out to be a not good detective...", SPAIN, 5, 1);
        break;
        case "Step_4_10":
            dialog.text = "Continue...";
            link.l1 = "I've caught up this filibuster, but I couldn't kill him - he's very strong, I had to retreat.";
            link.l1.go = "Step_4_11";
        break;
        case "Step_4_11":
            dialog.text = "It is understandable. To kill five heavily armed men who are ready to meet him is not to poke a scarecrow on the parade ground with a sword...";
            link.l1 = "So, from a conversation with him, I managed to find out that the passion of d'Ogeron is Donna Anna Ramirez de Leyva. That's all, actually...";
            link.l1.go = "Step_4_12";
        break;
        case "Step_4_12":
            dialog.text = "Well, if Don Jose had treated Donna Anna properly, then I guess none of this would have happened. It must be admitted that Donna Anna suffered greatly from the morals of her husband and the rules that he established in his house. Nevertheless, he had the right to do so...";
            link.l1 = "Senior Governor General, may I consider the investigation completed?";
            link.l1.go = "Step_4_13";
        break;
        case "Step_4_13":
            dialog.text = "Yes, of course. Your reward is 3,000 piastres. If you could kill this 'trustee', the reward would be different.\n"+
                          "And now I ask you to leave me, I need to write to de Leyva's relatives in Castile about the loss that has befallen us.";
            link.l1 = "Okay, Don Francisco, goodbye...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "10";
            CloseQuestHeader("Spa_Line_4_MirderDetection");
            AddMoneyToCharacter(pchar, 3000);
            TakeNationLicence(FRANCE);
			AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Grappling", 100);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 120);
			ChangeCharacterReputation(pchar, 2);
			//слухи
			AddSimpleRumour("You know, our Governor-General has instructed the captain " + GetFullName(pchar) + " to investigate the murder of Commandant de Leyva. Our captain the murderer, it turned out to be some Frenchman. But he failed to take revenge.", SPAIN, 5, 1);
        break;
        case "Step_4_14":
            dialog.text = "I find it hard to believe...";
            link.l1 = "Nevertheless, it is true. She is currently in the Market and seems to be very happy.";
            link.l1.go = "Step_4_15";
        break;
        case "Step_4_15":
            dialog.text = "Well, if Don Jose had treated Donna Anna properly, then I suppose none of this would have happened. It must be admitted that Donna Anna suffered greatly from the morals of her husband and the rules that he established in his house. Nevertheless, he had the right to do so... So who killed Don Jose?";
            link.l1 = "French filibuster Henri d'Estre, a confidant of the Governor-General d'Ogeron.";
            link.l1.go = "Step_4_16";
        break;
        case "Step_4_16":
            dialog.text = "Damn it! I won't say that I really liked Don Jose, but it's simply unacceptable to tolerate this under my nose! There must be retribution!";
            link.l1 = "It has already happened - Don Jose's killer is dead. I found him killed on Tortuga.";
            link.l1.go = "Step_4_17";
        break;
        case "Step_4_17":
            dialog.text = "Damn it! You are indeed a brave officer and a man of honor, besides. I am grateful to you for your courage.";
            link.l1 = "Thank you, Don Francisco.";
            link.l1.go = "Step_4_18";
        break;
        case "Step_4_18":
            dialog.text = "You are free. Well, I need to make sure that Donna Anna is not so happy. I guess she doesn't have long to live...";
            link.l1 = "Do you intend to send an assassin to her?";
            link.l1.go = "Step_4_19";
        break;
        case "Step_4_19":
            dialog.text = "Me? No way, I have more important things to do. But I consider it my duty to inform Don Jose's relatives in detail about the results of your investigation. Considering the criteria of the Castilian laws of honor, Donna Anna has at most six months left to live...";
            link.l1 = "Understood. Well, that's not really my business anymore. Senior Governor General, may I consider the investigation completed?";
            link.l1.go = "Step_4_20";
        break;
        case "Step_4_20":
            dialog.text = "Yes, of course. You excelled in your task, your reward is 120,000 piastres.\n"+
                          "And now I ask you to leave me. And don't forget to drop by my residence from time to time...";
            link.l1 = "Okay, Don Francisco, goodbye...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "4";
            CloseQuestHeader("Spa_Line_4_MirderDetection");
            AddMoneyToCharacter(pchar, 120000);
            TakeNationLicence(FRANCE);
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			//слухи
			AddSimpleRumour("You know, our Governor-General has instructed the captain " + GetMainCharacterNameDat() + " to investigate the murder of Commandant de Leyva. Our captain the killer, it turned out to be some Frenchman, and sent him to the next world.", SPAIN, 5, 1);
        break;
        //********************** Квест №5, Нападение на Ла Вегу. ************************
        case "Step_5_1":
            dialog.text = "You will learn everything from Jimenez. In the near future, you will be completely at his disposal. The only thing I can tell you is that it won't be boring, there will be a serious combat operation.";
            link.l1 = "Details...";
            link.l1.go = "Step_5_2";
        break;
        case "Step_5_2":
            dialog.text = "Everything is with Jimenez. Move to Santiago immediately.";
            link.l1 = "All right, sir.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp5LaVegaAttack_toSantiago";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "1");
 		AddQuestUserData("Spa_Line_5_LaVegaAttack", "sSex", GetSexPhrase("","a"));
        break;
        case "Step_5_3":
            dialog.text = "Hmm, well done. Mansfield was the authoritative hand, the undoubted success of the Spanish weapon. I congratulate you on this victory!\n"+
                          "Tell me, was this military operation sufficiently paid for by the Governor of Santiago?";
            link.l1 = "Yes, Senor Governor-General, to a sufficient extent. It's all right.";
            link.l1.go = "Step_5_4";
        break;
        case "Step_5_4":
            dialog.text = "Well, great! I'll be waiting for you at my place in a while, maybe I'll have more work for you.";
            link.l1 = "I will visit you from time to time, senor.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "6";
            pchar.questTemp.Waiting_time = "7";
            CloseQuestHeader("Spa_Line_5_LaVegaAttack");
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("LaVega_town")], "hidden_effects");
			//<-- огонь и пламень
            //===> Эдвард убит :( теперь Ла Вегой рулит капитан Купер.
            sld = characterFromID("Edward Mansfield");
            sld.name 	= "Captain";
        	sld.lastname = "Cooper";
        	sld.model.animation = "man"
            sld.model = "officer_8";
            sld.Sp5LaVegaAttackDone = true; // fix 1.2.3
            sld.quest.meeting = "0";  // fix 1.2.3 типа новый чел
            // лишнее это тут 1.2.3 SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            FaceMaker(sld);
            ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "FencingLight", 350);
			AddCharacterExpToSkill(pchar, "Fencing", 350);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 320);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			SetLocationCapturedState("LaVega_town", false); // fix 1.2.3 вернуть людей
			//слухи
			AddSimpleRumour("They say it was you who killed the head of the Mansfield Buccaneers. It's about time, I'll tell you...", SPAIN, 5, 1);
        break;
        //********************** Квест №6, Разведка на Тортуге. ************************
        case "Step_6_1":
            dialog.text = "The fact is that the French and Dutch seem to be secretly working together. It is clear that Louis XIV is waging a devolution war with us for the Dutch provinces in Europe.\nThe Netherlands itself does not dare to confront us openly, but their financial aid to the French plays a very important, if not decisive, role in the war - everyone knows that Louis has money problems.\n"+
                          "Your task is to sneak back to Tortuga and try to intercept any of the state correspondence between Governor-General Curaçao Peter Stavezant and Governor-General Bertrand d'Ogeron.\n"+
                          "Messengers with diplomatic mail appear there regularly, so you will need to intercept one of them. I need a document that our diplomatic department can use as evidence of the coordination of the actions of the Dutch and the French.";
            link.l1 = "I understand, senor. What are the deadlines?";
            link.l1.go = "Step_6_2";
        break;
        case "Step_6_2":
            dialog.text = "Not at all. The only thing I want to ask you is not to arrange an open massacre on Tortuga, brave and executive officers are dear to me.";
            link.l1 = "Don Francisco, I will try to survive under any circumstances.";
            link.l1.go = "Step_6_3";
        break;
        case "Step_6_3":
            dialog.text = "One more thing. I give you a 20-day license from the French West India Company. You have to show this paper to the harbormaster and no one will suspect you of anything.\n"+
                          "Well, you have received all the instructions. You can start the task.";
            link.l1 = "I'm getting started, Senor Governor General.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp6TakeMess_toTotuga";
            AddQuestRecord("Spa_Line_6_TakeMessangeer", "1");
			GiveNationLicence(FRANCE, 20);
        break;
        case "Step_6_4":
            dialog.text = "Well, report on the completion of the task.";
			if (CheckCharacterItem(pchar, "letter_1"))
			{
				link.l1 = "I managed to get diplomatic correspondence between the Governors-General of Tortuga and Curacao.";
				link.l1.go = "Step_6_6";
			}
			else
			{
				link.l1 = "I couldn't get the papers so far. It seems to me that everything is useless and I can no longer complete this task...";
				link.l1.go = "Step_6_5";
			}
        break;
        case "Step_6_5":
            dialog.text = "I'm disappointed in you, very bad... Well, I don't need you anymore. You can come to me later, maybe I'll find a dusty job for such a stupid officer...";
            link.l1 = "Okay, senor Governor General...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "40";
            CloseQuestHeader("Spa_Line_6_TakeMessangeer");
            BackItemDescribe("letter_1");
  			TakeNationLicence(FRANCE);
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
			DeleteAttribute(pchar, "questTemp.State.Open");
			LAi_group_SetLookRadius("FRANCE_CITIZENS", LAI_GROUP_DEF_LOOK);
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			//слухи
			AddSimpleRumour("Our governor-General sent the captain " + GetMainCharacterNameGen() + " to Tortuga with some very important assignment. The captain returned with nothing, one word is a failure...", SPAIN, 5, 1);
         break;
        case "Step_6_6":
            dialog.text = "Excellent, " + pchar.name + "It's just great!";
            link.l1 = "Thank you, Don Francisco...";
            link.l1.go = "Step_6_7";
        break;
        case "Step_6_7":
            dialog.text = "Now we have a serious argument in the diplomatic war... You've done a great job.";
            link.l1 = "Really, I had to work hard, what can I say...";
            link.l1.go = "Step_6_8";
        break;
        case "Step_6_8":
            dialog.text = "50 thousand coins - that's your reward! Please receive it... I ask you not to leave Havana for a long time, I will need you soon.";
            link.l1 = "All right, Senor Governor General.";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 50000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "9";
            CloseQuestHeader("Spa_Line_6_TakeMessangeer");
			TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
			TakeNationLicence(FRANCE);
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
			DeleteAttribute(pchar, "questTemp.State.Open");
			LAi_group_SetLookRadius("FRANCE_CITIZENS", LAI_GROUP_DEF_LOOK);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			//слухи
			AddSimpleRumour("They say that the captain " + GetFullName(pchar) + " successfully completed an extremely dangerous case on Tortuga. Mmm, courage of "+ GetSexPhrase("this man","this girl") +" can only admire ...", SPAIN, 5, 1);
		break;
        //********************** Квест №7, Спасти Пардаля. ************************
        case "Step_7_1":
            dialog.text = "Devil, this is very, very bad. The morale of the settlers will seriously drop with this news...";
            link.l1 = "I'm sorry, sir, I did everything I could.";
            link.l1.go = "Step_7_2";
        break;
        case "Step_7_2":
            dialog.text = "Well, what has been done, or rather, what has not been done, cannot be undone. Go on vacation. You can visit me after a while, maybe I'll have a case for you.";
            link.l1 = "All right, Don Francisco. Goodbye...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "20";
            CloseQuestHeader("Spa_Line_7_SavePardal");
		break;
        case "Step_7_3":
            dialog.text = "Great, "+ GetSexPhrase("my friend","" + pchar.name + "") +", just fine!";
            link.l1 = "Senor, it was a good fight, Manoel, I believe, will tell you the details of the fight...";
            link.l1.go = "Step_7_4";
        break;
        case "Step_7_4":
            dialog.text = "Without a doubt... Well, your heroic efforts are worthy of all praise and high reward. 25,000 reais is your reward!";
            link.l1 = "Um, the amount... the amount... Yes, actually, it's not about money!";
            link.l1.go = "Step_7_5";
        break;
        case "Step_7_5":
            dialog.text = "The words of a real soldier! I was right about you.\n"+
				          "I am not detaining you now, I will only ask you to be at my residence in a week - there is a case planned for the brave captain. I think I know who this captain is...";
            link.l1 = "All right, Don Francisco, I'll be with you around this time.";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 25000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "5";
            CloseQuestHeader("Spa_Line_7_SavePardal");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sneak", 250);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			//слухи
			AddSimpleRumour("They say that you saved our hero Pardal! Let me express my admiration to you, you are real"+ GetSexPhrase("I am a warrior","I am a warrior") +"!", SPAIN, 5, 1);
        break;
        case "Step_7_6":
            dialog.text = "Yeah, I'm disappointed, very bad... Well, I won't keep you any longer. After a while, you can come to my reception, perhaps I will find a case for such a stupid captain...";
            link.l1 = "Okay, Don Francisco, I'm sorry...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "40";
            CloseQuestHeader("Spa_Line_7_SavePardal");
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour("There are rumors that Pardal died largely because of your fault. It's sad, "+ GetSexPhrase("senor coward","senorita coward") +"...", SPAIN, 5, 1);
        break;
//********************** Квест №8, Отбить нападение на Куману. ************************
        case "Step_8_1":
            dialog.text = "Unfortunately, only in general terms. I was informed that their squadron even has a first-class battleship, which is completely uncharacteristic for pirates. There is no doubt that this attack is sponsored by the authorities of Tortuga...";
            link.l1 = "And we can't somehow stop them?";
            link.l1.go = "Step_8_2";
        break;
        case "Step_8_2":
            dialog.text = "Eh, "+ GetSexPhrase("my friend","dear senorita") +", we have lived with you at a very difficult time... Spain, our homeland, has suffered blows from all sides. In the Old World, we are losing the northern provinces in a devolution war with Louis, and there is increasing pressure on us from competing powers...\n"+
				          "Needless to say, it seems that the Pope's power will soon be seriously shaken in the world...";
            link.l1 = "It's sad, senor...";
            link.l1.go = "Step_8_3";
        break;
        case "Step_8_3":
            dialog.text = "However, we should not be disheartened. We are on the edge of a blade that punishes our enemies in the name of Spain and the Lord Almighty! And as we are challenged again, we must rise to the challenge.\n"+
				          "More than once rogues and criminals of all stripes, which are all the palms, have seized our cities, tortured and killed our colonists...\n"+
						  "This time we have to provide reliable protection for Kumane, this is your task. Go to Cumana immediately and repel the Ladron attack under the command of Captain Ansel.";
            link.l1 = "I got it, Don Francisco. It will be done.";
            link.l1.go = "Step_8_4";
        break;
		case "Step_8_4":
            dialog.text = "Great! And remember that in your hands, in the hands of your soldiers and sailors, is the fate of the whole city! Don't let me down.";
            link.l1 = "The Ladrones will be destroyed, you can be sure, senor.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp8SaveCumana_toCumana";
            AddQuestRecord("Spa_Line_8_SaveCumana", "1");
			SetTimerCondition("Sp8SaveCumana_RescueTimeOver", 0, 0, 20, false);
            Pchar.quest.Sp8SaveCumana_Battle.win_condition.l1 = "location";
            Pchar.quest.Sp8SaveCumana_Battle.win_condition.l1.location = "Cumana";
            Pchar.quest.Sp8SaveCumana_Battle.win_condition = "Sp8SaveCumana_Battle";
        break;
		case "Step_8_5":
            dialog.text = "It's all the same, I'm very unhappy with you. You can come to my residence a little later, but for now I have no business for you. I don't need officers who fail operations very often...";
            link.l1 = "I get it, Don Francisco.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            CloseQuestHeader("Spa_Line_8_SaveCumana");
			SetLocationCapturedState("Cumana_town", false);
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -260);
			AddCharacterExpToSkill(pchar, "Cannons", -300);
			AddCharacterExpToSkill(pchar, "FencingLight", -270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -250);
 			//слухи
			AddSimpleRumour("They say the captain " + GetFullName(pchar) + "failed to save the people of Cumana! A sad fate...", SPAIN, 5, 1);
        break;
		case "Step_8_6":
            dialog.text = "Great! A good blow to Spain's enemies in the Caribbean. As a reward for your courage, I ask you to accept 100,000 gold from the Spanish crown!";
            link.l1 = "Thank you, sir. Now let me take my leave, I need to put the ships in order after the battle...";
            link.l1.go = "Step_8_7";
        break;
		case "Step_8_7":
            dialog.text = "Okay, "+ GetSexPhrase("my friend","senorita") +". I ask you not to disappear from the city for a long time, it may very well be that I will need you again.";
            link.l1 = "I got it, Don Francisco.";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "7";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            CloseQuestHeader("Spa_Line_8_SaveCumana");
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddTitleNextRate(sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
 			//слухи
			AddSimpleRumour("Captain, they say that you saved Cumana! Let me express my admiration, "+ GetSexPhrase("senor","senorita") +"...", SPAIN, 5, 1);
        break;
//********************** Квест №9, Четыре золотых галеона. ************************
		case "Step_9_1":
            dialog.text = "The task will be to escort ships. I can't say anything more, the Governor of Porto Bello has all the instructions. Kindly receive a letter of credence addressed to the Governor of Porto Bello.";
            link.l1 = "I understand, senor. I'm starting immediately.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp9SaveCumana_toPortoBello";
            AddQuestRecord("Spa_Line_9_FourGolgGaleons", "1");
			AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("","a"));
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_SpaLineQ10");
            GiveItem2Character(pchar,"letter_1");
        break;
		case "Step_9_2":
            dialog.text = "You were supposed to escort the galleons to Belize, what does the Cayman have to do with it?!";
            link.l1 = "Senor, I have no idea what the Cayman has to do with it, but I was promised that a Spanish military squadron would meet me at the Cayman.";
            link.l1.go = "Step_9_3";
        break;
		case "Step_9_3":
            dialog.text = "Did you meet me?";
            link.l1 = "The Spanish military squadron - no, but five Ladron ships prepared a warm welcome for me. They were obviously waiting for my galleons.";
            link.l1.go = "Step_9_4";
        break;
		case "Step_9_4":
            dialog.text = "Why did you decide that?";
            link.l1 = "Senor, what should an entire squadron of pirates do near an uninhabited island in the middle of a deserted part of the Caribbean Sea? One can, of course, assume that they are going to play cards, but this is unlikely.";
            link.l1.go = "Step_9_5";
        break;
		case "Step_9_5":
            dialog.text = "Damn it, it looks like we're dealing with either a monstrous mistake or betrayal. I'll deal with that, but in the meantime, tell me, are all the galleons intact?";
			iTemp = 0;
			iMoney = 0;
            for (i=1; i<=COMPANION_MAX; i++)
            {
                ShipType = GetCompanionIndex(pchar,i);
                if(ShipType != -1)
                {
                	sld = GetCharacter(ShipType);
                    ShipType = sti(sld.ship.type);
                    Rank = sti(RealShips[ShipType].basetype);
                    if (Rank == SHIP_ROTERLOW)
					{
						iTemp++;
						iMoney = iMoney + sti(sld.Ship.Cargo.Goods.Gold);
					}
                }
            }
			npchar.quest.money = iMoney;
			if (iTemp < 4 && iTemp > 0)
            {
                if (iTemp == 1)
                {
					link.l1 = "Senor, the attack was sudden. I only managed to save one galleon.";
					link.l1.go = "Step_9_6";
                }
                else
                {
					link.l1 = "Senor, the attack was sudden. I managed to save the " + iTemp + " of the galleon...";
					link.l1.go = "Step_9_6";
                }
            }
            else
            {
				if (iTemp == 0)
				{
					link.l1 = "Senor, the Ladron attack was sudden and characterized by extreme fury. I lost all the galleons...";
					link.l1.go = "Step_9_8";
				}
				else
				{
					link.l1 = "Senor, although the Ladron attack was characterized by surprise, I managed to save all the galleons entrusted to me.";
					link.l1.go = "Step_9_11";
				}
            }
        break;
		case "Step_9_6":
            dialog.text = "This is very bad. I understand that you are in a difficult situation, but you could be more efficient. And now I have to account in Madrid for the serious shortfall in the supply of gold... and this is when Spain is wrestling in Europe!\n"+
				          "Mmm, very, very bad. I was counting on you, and you failed to justify my trust.";
            link.l1 = "Don Francisco, believe me, I did everything I could. And even more than that... However, the forces were too unequal, and I only had one ship to protect four galleons! By the way, at the insistence of the Governor of Porto Bello. Maybe I should ask him to the fullest extent of the law?";
            link.l1.go = "Step_9_7";
        break;
		case "Step_9_7":
            dialog.text = "Maybe, but it's none of your business. I understand you, but the numerous reasons you have outlined for the defeat do not detract from your guilt.";
            link.l1 = "I understand...";
            link.l1.go = "Step_9_71";
		break;
		case "Step_9_71":
			if (sti(npchar.quest.money) < (iTemp*1200))
			{
				dialog.text = "Therefore, I ask you to leave me now. In the future, you can come to my residence, perhaps there will be a suitable task for you...";
				link.l1 = "Thank you, Don Francisco.";
				link.l1.go = "Step_9_exit";
				pchar.questTemp.Waiting_time = "20";
				pchar.questTemp.State = "empty";
				SaveCurrentQuestDateParam("questTemp");
				pchar.questTemp.CurQuestNumber = "10";
			}
			else
			{
				dialog.text = "Uh, "+ GetSexPhrase("senor","senorita") +", are you trying to cheat in any way?! There is not enough gold on the galleons! I don't want to do business with you anymore under any circumstances. Goodbye!";
				link.l1 = "Um, well...";
				link.l1.go = "Step_9_exit";
				pchar.questTemp.State = "QuestLineBreake";
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
				AddCharacterExpToSkill(pchar, "Sailing", -300);
				AddCharacterExpToSkill(pchar, "Leadership", -300);
				AddCharacterExpToSkill(pchar, "Commerce", -300);
				AddCharacterExpToSkill(pchar, "Pistol", -300);
				//слухи
				AddSimpleRumour("Captain, they say you've been caught cheating. And that the Governor-General kicked you out of the residence. Oh, now you can order there...", SPAIN, 5, 1);
			}
        break;
		case "Step_9_8":
            dialog.text = "Damn it!!! How could this happen?! I understand that you are in a difficult situation, but you could be more efficient. And now I have to report to Madrid for a serious shortage in gold supplies... And this is when Spain is fighting an exhausting battle in Europe!";
            link.l1 = "Don Francisco, believe me, I did everything I could. Besides, I got trapped by the governor of Porto Bello!";
            link.l1.go = "Step_9_10";
        break;
		case "Step_9_10":
            dialog.text = "I won't even listen to your excuses. Go away!\n"+
				          "However, you can come to me, maybe there will be some work for "+ GetSexPhrase("such a talentless person","such a clumsy person") +"...";
            link.l1 = "All right, Don Francisco.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "60";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
            CloseQuestHeader("Spa_Line_9_FourGolgGaleons");
        break;
		case "Step_9_11":
            dialog.text = "Is the gold on them safe too?";
			if (sti(npchar.quest.money) >= 5000)
			{
				link.l1 = "Yes, Don Francisco, it's all right.";
				link.l1.go = "Step_9_12";
			}
			else
			{
				if(sti(npchar.quest.money) > 4800)
				{
					link.l1 = "Not really, don Francisco. I have " + FindRussianQtyString(sti(npchar.quest.money)) + " gold on galleons.";
					link.l1.go = "Step_9_14";
				}
				else
				{
					link.l1 = "Not really, don Francisco. I have  " + FindRussianQtyString(sti(npchar.quest.money)) + " gold on galleons.";
					link.l1.go = "Step_9_16";
				}
			}
        break;
		case "Step_9_12":
            dialog.text = "This is very good. You have managed to get out of a difficult situation with honor. Therefore, 220000 piastres will be a worthy reward for you.";
            link.l1 = "I am grateful, sir, for appreciating my deeds. If you no longer need me then let me leave you for a while.";
            link.l1.go = "Step_9_13";
        break;
		case "Step_9_13":
            dialog.text = "Okay, mind your own business. Don't forget, however, to visit me from time to time.";
            link.l1 = "All right, Don Francisco.";
            link.l1.go = "Step_9_exit";
			pchar.questTemp.Waiting_time = "7";
			pchar.questTemp.State = "empty";
			AddMoneyToCharacter(pchar, 220000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			//слухи
			AddSimpleRumour("Captain, it is said everywhere that while escorting galleons with gold, you were ambushed! How you managed to get out of this situation with honor is beyond my mind...", SPAIN, 5, 1);
        break;
		case "Step_9_14":
            dialog.text = "Well, these losses are justified in your situation. However, the reward will be paid to you minus the missing gold. Your total reward is 200,000 gold.\n"+
				          "I think we can safely say that you have managed to get out of a difficult situation with honor.";
            link.l1 = "I am grateful, sir, for appreciating my deeds. If you no longer need me then let me leave you for a while.";
            link.l1.go = "Step_9_15";
        break;
		case "Step_9_15":
            dialog.text = "Okay, mind your own business. Don't forget, however, to visit me from time to time.";
            link.l1 = "All right, Don Francisco.";
            link.l1.go = "Step_9_exit";
			pchar.questTemp.Waiting_time = "12";
			pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
			AddMoneyToCharacter(pchar, 200000);
			AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 190);
			AddCharacterExpToSkill(pchar, "Leadership", 70);
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			//слухи
			AddSimpleRumour("Captain, it is said everywhere that while escorting galleons with gold, you were ambushed! You've lost some of the galleons, but that's okay! The main thing is that they wiped the ladrons' noses!", SPAIN, 5, 1);
		break;
		case "Step_9_16":
			dialog.text = "Where could you go " + FindRussianQtyString(5000-sti(npchar.quest.money)) + " gold?! This is simply outrageous and unacceptable in no way.";
            link.l1 = "Senor Governor General, you know what a mess I'm in and what I've been through. Panic on the galleons, the devil knows what was going on...";
            link.l1.go = "Step_9_17";
        break;
		case "Step_9_17":
            dialog.text = "This is not an excuse! However, the argument does not make sense... I don't want to do business with you anymore under any circumstances. Goodbye!";
            link.l1 = "Um, well...";
            link.l1.go = "Step_9_exit";
			pchar.questTemp.State = "QuestLineBreake";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -300);
			AddCharacterExpToSkill(pchar, "Leadership", -300);
			AddCharacterExpToSkill(pchar, "Commerce", -300);
			AddCharacterExpToSkill(pchar, "Pistol", -300);
			//слухи
			AddSimpleRumour("Captain, they say that the Governor-General has kicked you out of the residence. Oh, now you can order there...", SPAIN, 5, 1);
		break;
		case "Step_9_exit":
			pchar.questTemp.CurQuestNumber = "10";
            CloseQuestHeader("Spa_Line_9_FourGolgGaleons");
            for (i=1; i<=4; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
            DialogExit();
        break;
//********************** Квест №10, Защита Маракайбо ************************
		case "Step_10_1":
            dialog.text = "Yes, again!";
            link.l1 = "Senor, as far as you know, fulfilling the instructions of the governor of Porto Bello, I got in a serious mess...";
            link.l1.go = "Step_10_2";
        break;
		case "Step_10_2":
            dialog.text = "This problem was the result of uncoordinated actions. Measures have been taken, this will not happen again.";
            link.l1 = "What tasks do I have to complete in Maracaibo?";
            link.l1.go = "Step_10_3";
        break;
		case "Step_10_3":
            dialog.text = "I am sending you there to strengthen the city, the squadron and the garrison of the city. Your task will be to protect Maracaibo from hostile actions.";
            link.l1 = "How much do I obey the governor of the city?";
            link.l1.go = "Step_10_4";
        break;
		case "Step_10_4":
            dialog.text = "As part of the global task of protecting the city, you report to the Governor of Maracaibo. Your task does not include operations that are not directly related to this.";
            link.l1 = "Great! Well, I'm ready tostart the task.";
            link.l1.go = "Step_10_5";
        break;
		case "Step_10_5":
            dialog.text = "Great! Go to Maracaibo as soon as possible.";
            link.l1 = "Okay, Don Francisco, my transition to Maracaibo will not take long.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp10Maracaibo_toMaracaibo";
            AddQuestRecord("Spa_Line_10_Maracaibo", "1");
			AddQuestUserData("Spa_Line_10_Maracaibo", "sSex", GetSexPhrase("","a"));
        break;
		case "Step_10_6":
            dialog.text = "But I specifically sent you to protect the city!";
            link.l1 = "Don Francisco, the pirates' forces were disproportionately greater than mine. I couldn't give them decent resistance, I had to leave the battlefield in order to stay alive...";
            link.l1.go = "Step_10_7";
        break;
		case "Step_10_7":
            dialog.text = "I don't believe my ears! ";
            link.l1 = "Alas, but it is so...";
            link.l1.go = "Step_10_8";
        break;
		case "Step_10_8":
            dialog.text = "I don't want to have anything to do with you anymore. There have never been such cowards and sloppies in the service of Spain! What a shame... That's it, the conversation with you is over once and for all, goodbye.";
            link.l1 = "...";
            link.l1.go = "exit";
			CloseQuestHeader("Spa_Line_10_Maracaibo");
            DeleteAttribute(pchar, "questTemp.CurQuestNumber");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "QuestLineBreake";
            bWorldAlivePause   = false; // Конец линейки
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Pistol", -430);
			AddCharacterExpToSkill(pchar, "Fortune", -460);
			AddCharacterExpToSkill(pchar, "Accuracy", -420);
			AddCharacterExpToSkill(pchar, "Grappling", -450);
			AddCharacterExpToSkill(pchar, "Sailing", -300);
			AddCharacterExpToSkill(pchar, "Leadership", -300);
			AddCharacterExpToSkill(pchar, "Commerce", -300);
			//слухи
			AddSimpleRumour("Captain, they say that the Governor-General kicked you out of the residence for cowardice. Oh, now you can order there...", SPAIN, 5, 1);
        break;
		case "Step_10_9":
            dialog.text = "Excellent! I didn't doubt you.";
            link.l1 = "Governor of Maracaibo, senor " + Characters[GetCharacterIndex("Maracaibo_Mayor")].name + ", told me to tell you that I am grateful to you for your timely assistance.";
            link.l1.go = "Step_10_10";
        break;
		case "Step_10_10":
            dialog.text = "Okay... Did he thank you?";
            link.l1 = "Yes, sir, everything is fine...";
            link.l1.go = "Step_10_11";
        break;
		case "Step_10_11":
            dialog.text = "Well, great! Now I will ask you to rest and gain strength for the next battles. And don't disappear from the city for a long time, it's possible that I'll need you in the near future.";
            link.l1 = "All right, Don Francisco.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "15";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
            CloseQuestHeader("Spa_Line_10_Maracaibo");
			ChangeCharacterReputation(pchar, 5);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			//слухи
			AddSimpleRumour("Captain, they say that you managed to defend Maracaibo! Without exaggeration, this is a real feat, "+ GetSexPhrase("senor","senorita") +"!", SPAIN, 5, 1);
        break;
//********************** Квест №11, Нападение на Кюрасао и Сан Мартин ************************
		case "Step_11_1":
            dialog.text = "Very good! So, listen to the task.\n"+
				          "As part of the ongoing devolution war with France for Spanish possessions in Holland, the first and most important task for us is to destroy Curaçao and San Martín. From the intercepted dispatch it was revealed that the Dutch were devoting huge sums of money to France's military needs.\n"+
						  "We can't prove that, because all the correspondence is encrypted in a special way, the meaning of the letter is completely different. But nevertheless, we must end this, the Dutch trade power must end!\n"+
						  "You must storm and destroy the Dutch settlements of Willemstad, on the island of Curacao, and Marigo, on the island of San Martin. All trophies captured as a result of the operation remain with you.\n"+
						  "Are you ready for such a task?";
            link.l1 = "Yes, Don Francisco. What are the deadlines?";
            link.l1.go = "Step_11_2";
        break;
		case "Step_11_2":
            dialog.text = "Not at all.";
            link.l1 = "Well, very good. I'm getting started.";
            link.l1.go = "exit";
            SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY); //ссорим ГГ и голландцев.
            SetNationRelationBoth(HOLLAND, SPAIN, RELATION_ENEMY);
            SetQuestHeader("Spa_Line_11_DestrHolland");
            AddQuestRecord("Spa_Line_11_DestrHolland", "1");
			AddQuestUserData("Spa_Line_11_DestrHolland", "sSex", GetSexPhrase("","a"));
            pchar.questTemp.State = "DestrHolland_GoOn";
			characters[GetCharacterIndex("Villemstad_Mayor")].dialog.captureNode = "SpaLine11Quest_DestrHol"; //капитулянтская нода мэра
			characters[GetCharacterIndex("Marigo_Mayor")].dialog.captureNode = "SpaLine11Quest_DestrHol"; //капитулянтская нода мэра
		break;
		case "Step_11_3":
            dialog.text = "And well done! The Dutch got a slap on the wrist, hopefully it'll make them squeamish in spending, ha-ha.\n"+
				          "The loot captured on the island rightfully belongs to you! I ask you to come to my office in a month. I have a case brewing for you again.";
            link.l1 = "All right, Don Francisco. I will definitely be at your place around this time.";
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 2);
            DeleteAttribute(pchar, "questTemp.Q11_Villemstad");
            DeleteAttribute(pchar, "questTemp.Q11_Marigo");
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "30";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
            CloseQuestHeader("Spa_Line_11_DestrHolland");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			//слухи
			AddSimpleRumour("Great job, Captain! You've given these Dutch scoundrels a great beating!", SPAIN, 5, 5);
        break;
//********************** Квест №12, Захват Порт-о-Принса ************************
		case "Step_12_1":
            dialog.text = "I need you to capture another city. Only this time, not for the purpose of ruin, but for the purpose of asserting the power of Spain.";
            link.l1 = "Excellent, Senor Governor-General. What kind of city is this?";
            link.l1.go = "Step_12_2";
        break;
		case "Step_12_2":
            dialog.text = "This city is now the French Port-au-Prince. You have already managed to solve the problem of the Buccaneers of La Vega, now it's the turn of this colony. Hispaniola should become completely Spanish!";
            link.l1 = "I understand... What are the deadlines?";
            link.l1.go = "Step_12_3";
        break;
		case "Step_12_3":
            dialog.text = "Again, no. Taking cities is not an easy task, therefore it would be reckless on my part to demand any deadlines. Prepare properly for the capture and proceed.";
            link.l1 = "Excellent, Senor Governor General. I'm getting started.";
            link.l1.go = "exit";
            SetQuestHeader("Spa_Line_12_OccupyPortPax");
            AddQuestRecord("Spa_Line_12_OccupyPortPax", "1");
			AddQuestUserData("Spa_Line_12_OccupyPortPax", "sSex", GetSexPhrase("","a"));
            pchar.questTemp.State = "OccupyPortPax_GoOn";
			characters[GetCharacterIndex("PortPax_Mayor")].dialog.captureNode = "SpaLine12Quest_PortPax"; //капитулянтская нода мэра
        break;
		case "Step_12_4":
            dialog.text = "Great! I will immediately notify all interested parties of this great news. A magnificent victory, Captain, just fabulous luck!";
            link.l1 = "Good training and combat skills - nothing supernatural, senor...";
            link.l1.go = "Step_12_5";
        break;
		case "Step_12_5":
            dialog.text = "Undoubtedly, modesty adorns a warrior. Well, I'm frankly happy for you, "+ GetSexPhrase("my friend","" + pchar.name + "") +", you have become the most important captain in the Caribbean. Congratulations!";
            link.l1 = "Thank you, Don Francisco...";
            link.l1.go = "Step_12_6";
        break;
		case "Step_12_6":
            dialog.text = "So, the main tasks set for me by Spain have been completed. From now on, I give you the freedom to act in the interests of the kingdom. I really hope that your subsequent actions will only increase the power of Spain in these waters.";
            link.l1 = "You can be sure of that, Senor Governor-General. For this, allow me to take my leave.";
            link.l1.go = "exit";
            AddTitleNextRate(sti(NPChar.nation), 4);
            DeleteAttribute(pchar, "questTemp.CurQuestNumber");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
            pchar.questTemp.State = "EndOfQuestLine";
			bWorldAlivePause   = false; // Конец линейки
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			CloseQuestHeader("Spa_Line_12_OccupyPortPax");
			AddCharacterExpToSkill(pchar, "Repair", 630);
			AddCharacterExpToSkill(pchar, "Sneak", 490);
			AddCharacterExpToSkill(pchar, "FencingLight", 530);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 530);
			AddCharacterExpToSkill(pchar, "Fencing", 530);
			AddCharacterExpToSkill(pchar, "Pistol", 530);
			AddCharacterExpToSkill(pchar, "Fortune", 660);
			AddCharacterExpToSkill(pchar, "Accuracy", 520);
			AddCharacterExpToSkill(pchar, "Grappling", 750);
			//слухи
			AddSimpleRumour("Captain, they say that you have managed to capture Port-au-Prince! Is the whole island ours now?! Great!!", SPAIN, 5, 1);
		break;

//********************** //Квест "A New Homeland.". Спрашиваем про Лесопилку ************************
		case "HugoLesopilka_1":
            dialog.text = "Who is this person?";
            link.l1 = "His name is Hugo Sawmill. He...";
            link.l1.go = "HugoLesopilka_2";
			DeleteAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Guber");
        break;

		case "HugoLesopilka_2":
            dialog.text = "Do you realize that this man is a disgusting pirate and a brutal murderer? I will never allow this man to serve in our Navy.";
            link.l1 = "It is not necessary to accept him for service. It's enough to just take his money and then... The criminal should be punished, right?";
            link.l1.go = "Nakazat_1";
			link.l2 = "But he's not dangerous... I saw him, he's just a tired old man, and his biggest wish is to sleep in a comfortable bed. He is ready to retire and is looking for a safe haven where he will be allowed to live in peace.";
            link.l2.go = "Na_Slujbu_1";
        break;

		case "Nakazat_1":
            dialog.text = "This is terrible! Are you offering me a bribe from a criminal? This is offensive and unacceptable, "+ GetSexPhrase("senor","senorita") +"! Don't ever talk about this with me again!";
            link.l1 = "Understood. I made a mistake. It won't happen again. Asta luego!";
            link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -12);
        break;

		case "Na_Slujbu_1":
            dialog.text = "Hmmmm... If you say that, maybe you're right. I will trust you in this matter, "+pchar.name+". I will prepare a patent for this man and give it to you. He will have to come to me immediately after receiving it. Now let me get back to my business.";
            link.l1 = "Of course, Your Excellency. Asta luego!";
            link.l1.go = "Na_Slujbu_2";
			Log_info("You have received a Spanish patent for Hugo");
			GiveItem2Character(PChar, "Patent_Espa_Lesopilka");
			PlaySound("Interface\important_item.wav");
			ChangeCharacterReputation(pchar, 1);
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"none","","");
			pchar.questTemp.PDM_Novaya_Rodina.IshemHugo = "IshemHugo";
        break;

		case "Na_Slujbu_2":
			AddQuestRecord("PDM_Novaya_Rodina", "2");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","a"));
			pchar.questTemp.PDM_Novaya_Rodina.Patent = "Patent";
			DialogExit();
        break;

		case "HugoLesopilka_Lubopitno_1":
			dialog.text = "Oh, thank you so much, "+ GetSexPhrase("senor","senorita") +" "+pchar.name+". He is a very brave and experienced soldier. Our enemies have already lost half a dozen ships. And he's also a great storyteller. His stories about the old days gather crowds of listeners in the tavern! Now, if you'll excuse me, I'll ask you to leave me.";
            link.l1 = "Si, Your Excellency. Asta luego!";
            link.l1.go = "HugoLesopilka_Lubopitno_2";
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"Havana_Town","goto","goto2");
			LAi_SetCitizenType(sld);
        break;

		case "HugoLesopilka_Lubopitno_2":
			AddQuestRecord("PDM_Novaya_Rodina", "5");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","a"));
			sld = CharacterFromID("Hugo_Lesopilka")
			sld.dialog.filename   = "Quest\PDM\Novaya_Rodina.c";
			sld.dialog.currentnode   = "Novoe_Zadanie_1";
			ChangeCharacterAddressGroup(sld,"Havana_Town","goto","goto2");
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			LAi_SetCitizenType(sld);
			LAi_SetLoginTime(sld, 6.0, 21.99);
			DeleteAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Guber");
			DialogExit();
        break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
