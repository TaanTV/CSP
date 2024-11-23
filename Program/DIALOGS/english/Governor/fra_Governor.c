// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind..", "I have nothing to talk about right now.");
		    link.l1.go = "exit";

            //******************** голландская линейка ***************************
        	switch (pchar.questTemp.State)   // что делаем в данный момент
            {
				case "DelivLettTortuga_toDOjeron": // Квест №7 голл. линейки. Письмо от Стэвезанта
					link.l1 = "Monsieur, I am authorized to deliver to you a diplomatic dispatch from the Governor-General of Curacao, Peter Stuyvesant. Please receive it.";
					link.l1.go = "Step_H7_1";
				break;
				case "DelivLettTortuga_WaitTwoHours":
					if (GetQuestPastTimeParam("questTemp") > 1)
					{
						link.l1 = "Monsieur Governor-General, I have arrived.";
						link.l1.go = "Step_H7_3";
					}
					else
					{
						dialog.text = "You came too early, I told you - in two hours!";
						link.l1 = "Sorry, monsieur, I hurried.";
						link.l1.go = "exit";
					}
				break;
				case "DelivLettTortuga_AfterRape": //Голландская линейка, квест №7. после грабежа.
					link.l1 = "Monsieur Governor-General, it's me again!";
					link.l1.go = "Step_H7_5";
				break;
			}
		break;
		//******************** французская линейка ***************************
		case "work_1":  // работа на благо короны - линейка нации
            // сюда вход только с патентом, проверка выше
            dialog.text = LinkRandPhrase("You are in the service of France! I ask you to immediately begin fulfilling the assignment assigned to you!",
                                         "I will not hide that a lot depends on your successful actions. Therefore, proceed to fulfill your obligations!",
                                         "I am waiting for your report on the fulfillment of my responsible assignment, but not empty interpretations.");
            link.l1 = RandPhraseSimple("Starting immediately, Monsieur Governor General.", "I'm already in the process of doing...");
            link.l1.go = "exit";

        	switch (pchar.questTemp.State)   // что делаем в данный момент
            {
                case "empty":   // Нет взятых квестов
                    if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
                    {
                        dialog.text = LinkRandPhrase("I don't have any responsible assignments for you at the moment. You can come to my residence later...",
                                                     "Please excuse me, I'm very busy at the moment!",
                                                     "Mind your own business for the time being, I don't have any assignments for you right now.");
                        link.l1 = "All right, Monsieur Governor General.";
                        link.l1.go = "exit";
                    }
                    else
                    {
						switch(pchar.questTemp.CurQuestNumber)   // Взятие квестов начиная со второго
                        {
                            case "2":
                                dialog.text = "I need you to deliver this letter to Governor General Peter Stuyvesant in Curacao as soon as possible. And the faster, the higher the reward will be.";
								link.l1 = "All right, Monsieur Governor-General, I'll do it. Give me your letter.";
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":
                                dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", I have an assignment for you of a very delicate nature. You are honest, you know how to keep your word, which you have proven more than once... I want to entrust the honor of a person dear to me into your hands...";
								link.l1 = "Monsieur, let's get to the point...";
                                link.l1.go = "Step_3_1";
                            break;
                            case "4":
                                dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", you have proven your loyalty and honor, so I am entrusting you with an important and top secret case.";
								link.l1 = "I hope it's still connected to the sea?";
                                link.l1.go = "Step_4_1";
                            break;
                            case "5":
                                dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", an assignment of a delicate nature for you again. I have serious concerns for the life of Donna de Leyva. Please visit her, she is now in my residence in the next room. The senora will fill you in on the details.";
								link.l1 = "I will do it immediately.";
                                link.l1.go = "exit";
								LAi_group_Delete("PeaceGroup");
    							pchar.questTemp.State = "Fr5AnnaHant_toAnna";
								AddQuestRecord("Fra_Line_5_KillAnnaHanters", "1");
								sld = GetCharacter(NPC_GenerateCharacter("AnnaDeLeiva", "AnnaDeLeiva", "woman", "towngirl2", 10, SPAIN, -1, false));
								sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
								sld.name = "Anna Ramirez";
								sld.lastname = "de Leyva";
								LAi_SetStayType(sld);
								LAi_group_MoveCharacter(sld, "PeaceGroup");
								ChangeCharacterAddressGroup(sld, "Tortuga_townhallRoom", "goto", "goto2");
                            break;
                            case "6":
                                dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", urgently deliver this package to Mr. Jean David, who is currently in Guadeloupe. Just don't try to find Jean David there, haha, he is better known as Francois Olone.";
								link.l1 = "That famous filibuster?";
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = "It's great that you came, I was just about to instruct you to find you. I have a matter for you that cannot wait.";
								link.l1 = "Then let's get to it soon!";
                                link.l1.go = "Step_7_1";
                            break;
                            case "8":
                                dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", I received an order to send a smart, executive, loyal and quite authoritative filibuster to the French Naval Quartermaster Marquis Bonrepos, who is currently in Guadeloupe. I consider your candidacy worthy.";
								link.l1 = "Thank you for your trust. But what is my assignment?";
                                link.l1.go = "Step_8_1";
                            break;
                            case "9":
                                dialog.text = ""+ GetSexPhrase("Baron", "Baronessa") +", I have been ordered to appoint you commander of the special punitive marine corps and place at your disposal the already known battleship Soleil Royal. Your next tasks will be military action against Spain as part of the devolution war. The first task is to repel the attack of the Spanish squadron on Port-au-Prince.";
								link.l1 = "Hmm, apparently the Spaniards want to own Hispaniola alone...";
                                link.l1.go = "Step_9_1";
                            break;
                            case "10":
                                dialog.text = "So, "+ GetSexPhrase("Baron", "Baronessa") +", I'm glad to see you. You're just in time!";
								link.l1 = "I am listening to you, sir.";
                                link.l1.go = "Step_10_1";
                            break;
                            case "11":
                                dialog.text = "So, "+ GetSexPhrase("Baron", "Baronessa") +", France is waiting for new achievements from you. This time, a military operation very similar to the previous one.";
								link.l1 = "Capture of the city, monsieur?";
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = ""+ GetSexPhrase("Baron", "Baronessa") +", the devolution war is over with the magnificent victory of our beloved Sun King Louis XIV!!!";
								link.l1 = "Vivat, Monsieur Governor-General!";
                                link.l1.go = "Step_12_1";
                            break;
						}
					}
				break;
                case "":           // Квест №1, Охрана пирата Леграна.
                    dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", do you know Pierre Legrand? The other day, just imagine, he captured a Spanish military galleon with fine loot on a lugger. The ship and cargo were sold, the ransom for the Spaniards was received, the amount was paid to the royal treasury. Legrand has become a wealthy man and wants to return to France. Well, I respect his decision.";
                    link.l1 = "And it is desirable for him to leave quietly?";
                    link.l1.go = "Step_1_1";
                break;
                case "Fr1Legran_backGovernor":
                    dialog.text = "Monsieur Legrand managed to tell me that he is all right. By the way, he spoke very highly of you. I am glad that I did not make a mistake in choosing an honest and reliable person.";
                    link.l1 = "Thank you for the praise, monsieur...";
                    link.l1.go = "Step_1_2";
                break;
                case "Fr1Legran_LegranKilled":
                    dialog.text = "Ah, it's you... Well, what do you say?";
                    link.l1 = "I have completed your assignment is fine. Moreover, I helped Legrand deal with the bandits who tried to rob him.";
                    link.l1.go = "Step_1_3";
                break;
                case "Fr1Legran_LegranIsDead":
                    dialog.text = "Ah, it's you... Well, what do you say?";
                    link.l1 = "Mr. Governor-General, I hate to say this, but there was an ambush waiting for us in Martinique. Legrand and I got into a fight. Unfortunately, Legrand died in this battle...";
                    link.l1.go = "Step_1_5";
                break;
                case "Fr2Letter_SeekProblems":
                    dialog.text = "So, Captain, tell me what you have?";
                    link.l1 = "Your letter has been delivered to the recipient, monsieur.";
                    link.l1.go = "Step_2_3";
                break;
                case "Fr2Letter_NiceResult":
                    dialog.text = "So, Captain, tell me, what do you have?";
                    link.l1 = "I'll tell you, Monsieur d'Ogeron that I hit in a pretty mess...";
                    link.l1.go = "Step_2_6";
                break;
                case "Fr3TakeAnna_BadResult":
                    dialog.text = "I've been waiting for you. What do you say, "+ GetSexPhrase("monsieur", "mademoiselle") +"?";
                    link.l1 = "I couldn't bring Donna Anna, I'm sorry that it happened...";
                    link.l1.go = "Step_3_5";
                break;
                case "Fr3TakeAnna_NiceResult":
                    dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", I don't even know how to thank you!";
                    link.l1 = "It wasn't difficult, monsieur...";
                    link.l1.go = "Step_3_7";
                break;
                case "Fr4SoleiRoyal_DieHard":
                    dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", report on the completion of the task.";
                    link.l1 = "Monsieur Governor-General, I did not find the French squadron near Dominica, but I was attacked by the Spanish squadron of Juan Galeno. I couldn't resist her, I had to leave the place of battle...";
                    link.l1.go = "Step_4_7";
                break;
                case "Fr4SoleiRoyal_SoleiRoyalSunk":
                    dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", report on the completion of the task.";
                    link.l1 = "Monsieur Governor-General, I did not find the French squadron near Dominica, but I was attacked by the Spanish squadron of Juan Galeno. I reflected the attack, but as a result of the battle, the Soleil Royal was sunk. I'm really sorry...";
                    link.l1.go = "Step_4_9";
                break;
                case "Fr4SoleiRoyal_backTortuga":
                    dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", report on the completion of the task.";
                    link.l1 = "Everything is fine, monsieur, although not without problems. I reflected attack of the Spanish squadron under the command of the same Juan Galeno, I didn't find the French squadron near Dominica, so I had to deliver the Soleil Royal to Basse-Terre.";
                    link.l1.go = "Step_4_11";
                break;
                case "Fr5AnnaHant_GoodWork":
                    dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", I'm starting to think that there is no such assignment that you can't complete. Here is your reward, and Donna de Leyva wants to personally thank you.";
                    link.l1 = "Thank you, Monsieur Governor General...";
                    link.l1.go = "exit";
					DeleteAttribute(&locations[FindLocation("Mayak10")], "DisableEncounters"); //откроем энканутеры
					pchar.questTemp.State = "empty";
					SaveCurrentQuestDateParam("questTemp");
					pchar.questTemp.CurQuestNumber = "6";
					pchar.questTemp.Waiting_time = "7";
					CloseQuestHeader("Fra_Line_5_KillAnnaHanters");
					AddMoneyToCharacter(pchar, 5000);
                break;
                case "Fr6Olone_OloneIsDead":
                    dialog.text = "What do you say, Captain? Did everything go well?";
                    link.l1 = "The letter was delivered, but the problem came out with Olone...";
                    link.l1.go = "Step_6_3";
                break;
                case "Fr6Olone_OloneIsLive":
                    dialog.text = "What do you say, Captain? Did everything go well?";
                    link.l1 = "Yes, it's all right, monsieur. On top of everything else, we managed to capture Cumana and took a hefty prize.";
                    link.l1.go = "Step_6_7";
                break;
                case "Fr6Olone_TakeMoney":
                    dialog.text = "What do you say, Captain? Did everything go well?";
                    link.l1 = "Yes, monsieur, the letter has been delivered to the addressee personally. Everything is fine.";
                    link.l1.go = "Step_6_9";
                break;
                case "Fr7RockBras_toSeekPlace":
                    dialog.text = "Okay, Captain. Tell me about the results of the mission to save Rock the Brazilian.";
                    link.l1 = "So far I have failed to find him, but I'll keep looking...";
                    link.l1.go = "exit";
					link.l2 = "Sir, I was looking for it everywhere, but I couldn't find it. I have to admit that everything is useless...";
                    link.l2.go = "Step_7_6";
                break;
                case "Fr7RockBras_RockIsDead":
                    dialog.text = "So, Captain, I've been waiting for you. Is there any news about the Brazilian?";
                    link.l1 = "There is news, Monsieur Governor-General. However, they are disappointing - the Rock Brazilian died while escaping from the dungeons of the Inquisition...";
                    link.l1.go = "Step_7_7";
                break;
                case "Fr7RockBras_RockIsSaved":
                    dialog.text = "I see, Captain, everything is in order. Rock has already told you what he went through in the Inquisition and how you got him out of there. I am delighted!";
                    link.l1 = "Monsieur, it was a completely ordinary thing...";
                    link.l1.go = "Step_7_8";
                break;
                case "Fr7RockBras_RockIsAgony":
                    dialog.text = "So, Captain, I've been waiting for you. Is there any news about the Brazilian?";
                    link.l1 = "There is news, Monsieur Governor-General. However, they are disappointing - the Inquisition tortured Rock the Brazilian to death. He expired in my arms...";
                    link.l1.go = "Step_7_7";
                break;
                case "Fr8ThreeCorsairs_backGovernor":
                    dialog.text = "So, " + GetFullName(pchar) + ", I am happy to congratulate you on the title of "+ GetSexPhrase("Baron", "Baroness") +"! Believe me, it is rare for anyone to receive such an honor.";
                    link.l1 = "I must admit, sir, I don't really understand why I need it? Moreover, I didn't get it cheap...";
                    link.l1.go = "Step_8_2";
                break;
                case "Fr9GuardPP_GoodWork":
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", you've lost the Soleil Royal!";
						link.l1 = "I saved Port-au-Prince and launched to the bottom of the most powerful squadron of Spaniards!";
						link.l1.go = "Step_9_4";
					}
					else
					{
						dialog.text = ""+ GetSexPhrase("Baron", "Baronessa") +", I already know about your victory. What can I say? Fine, "+ GetSexPhrase("my friend", "mademoiselle") +", just great!";
						link.l1 = "The first military operation has been completed, Monsieur Governor-General...";
						link.l1.go = "Step_9_2";
					}
                break;
                case "Fr9GuardPP_SoleiRoyalSunk":
                    dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", you've lost the Soleil Royal!";
                    link.l1 = "I saved Port-au-Prince and launched to the bottom of the most powerful squadron of Spaniards!";
                    link.l1.go = "Step_9_4";
                break;
                case "Fr9GuardPP_DieHard":
                    dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", you failed to protect Port-au-Prince! What's the matter?!";
                    link.l1 = "Monsieur the Governor, the Spaniards have managed to assemble a squadron of unprecedented strength! I had to retreat...";
                    link.l1.go = "Step_9_6";
                break;
                case "Fr9GuardPP_Late":
                    dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", you failed to protect Port-au-Prince! What's the matter?!";
                    link.l1 = "I didn't have time, Monsieur Governor-General, when I arrived to the city, it was already Spanish...";
                    link.l1.go = "Step_9_7";
                break;
                case "Fr10OccupySD_toWeWon":
					dialog.text = "What do you say, "+ GetSexPhrase("Baron", "Baronessa") +"? How was the operation?";
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						link.l1 = "I captured Santo Domingo, now this city belongs to France! But not everything went smoothly...";
						link.l1.go = "Step_10_4";
					}
					else
					{
						link.l1 = "I captured Santo Domingo, now this city belongs to France!";
						link.l1.go = "Step_10_6";
					}
                break;
                case "Fr11OccupySC_toWeWon":
					dialog.text = ""+ GetSexPhrase("Baron", "Baronessa") +", I am waiting for your report, how successful is the operation to capture Santa Catalina?";
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						link.l1 = "Santa Catalina captured and sworn in by Louis XIV. This is good news, but the bad news is that I lost 'Soleil Royal'...";
						link.l1.go = "Step_11_3";
					}
					else
					{
						link.l1 = "Santa Catalina captured and sworn in by Louis XIV.";
						link.l1.go = "Step_11_5";
					}
                break;
                case "QuestLineBreake":
                    dialog.text = "I don't deal with people breaking their word. I have nothing more to say to you.";
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
                case "EndOfQuestLine":
                    dialog.text = "Act independently in the interests of France, do not forget about filibusters either. The war is over, it's time to arrange your life, "+ GetSexPhrase("Baron", "Baronessa") +"...";
					/*if (!CheckAttribute(npchar, "quest.answer_1"))
					{
						link.l2 = "Sir, the Soleil Royal is a beautiful ship, in the interests of our country, it will be necessary to build another royal man to strengthen the dominance of the sea. This will give us a great advantage in the coming wars.";
						link.l2.go = "build_ship";
					}*/
                    link.l1 = "All right, sir.";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
			}
		break;
        //********************** Квест №7 голландки, Доставка письма д'Ожерону от Стэвезанта ************************
        case "Step_H7_1":
            dialog.text = "Fine.";
            link.l1 = "For this, allow me to take my leave...";
            link.l1.go = "Step_H7_2";
            TakeItemFromCharacter(pchar, "letter_2");
            BackItemDescribe("letter_2");
        break;
        case "Step_H7_2":
            dialog.text = "Wait. Come to me in two hours, I must familiarize myself with the contents of this document. Perhaps there will be an answer.";
            link.l1 = "I understand, I will be at your residence in two hours, monsieur.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "2");
            pchar.questTemp.State = "DelivLettTortuga_WaitTwoHours";
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_H7_3":
            dialog.text = "Yes, good. So, I got acquainted with the contents of the dispatch. I really have an answer for Stuyvesant, please deliver this package to Curacao.";
            link.l1 = "All right, monsieur. Can I leave now?";
            link.l1.go = "Step_H7_4";
        break;
        case "Step_H7_4":
            dialog.text = "Yes, of course. Good luck on the way back. With the beginning of the devolution war, the Spaniards became seriously active. So be very careful. If any of our correspondence gets to the Spaniards, they will be able to prove our concerted actions against Spain. The young Republic of the United Provinces will not be well off in this case.";
            link.l1 = "I understand, monsieur. Goodbye and good luck to you too.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "3");
	    AddQuestUserData("Hol_Line_7_DelivLettTortuga", "sSex", GetSexPhrase("", "a"));
            pchar.questTemp.State = "DelivLettTortuga_SnapMeeting";
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_HolLineQ7");
            GiveItem2Character(pchar, "letter_1");
            LocatorReloadEnterDisable("Tortuga_town", "gate_back", true);
            LocatorReloadEnterDisable("Tortuga_town", "reload1_back", true);
            LocatorReloadEnterDisable("Tortuga_town", "reload2_back", true);
            LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false);
            LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);
            Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition.l1 = "location";
            Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition.l1.location = "Tortuga_town";
            Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition = "DelivLettTortuga_SnapMeeting";
        break;
        case "Step_H7_5":
            dialog.text = "I see. Why are you still here? It looks like you're in no hurry either!";
            link.l1 = "Monsieur, the dispatch you wrote has been stolen. I was hit on the head and I was lying unconscious all this time!";
            link.l1.go = "Step_H7_6";
        break;
        case "Step_H7_6":
            dialog.text = "Go immediately to the portmaster with my instructions to tell you which ship left Tortuga in the last two hours. Then catch up with them, board the ship and find the package!";
            link.l1 = "I understand, Monsieur, thank you for your help!";
            link.l1.go = "exit";
            pchar.questTemp.State = "DelivLettTortuga_toPortMan";
        break;
        //********************** Квест №1 французской линейки, охрана Леграна ************************
        case "Step_1_1":
            dialog.text = "You got it right. Monsieur Legrand needs to get to Martinique secretly, then he will be able to go from there by regular ship to Dieppe. But he is 'sitting' on a pile of gold and everyone knows this, so there are serious concerns for the safe outcome of returning to the Old World\n"+
				          "Go to the tavern-you will find Legrand there. Your task is to deliver it to the Bay of Le Maren, in Martinique. Pierre will thank you, "+ GetSexPhrase("sir", "miss") +".";
            link.l1 = "All right, monsieur, I'll do as you say.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
    		// остальные линейки в сад -->
    		pchar.questTemp.NationQuest = FRANCE;
    		// остальные линейки в сад <--
    		pchar.questTemp.State = "Fr1Legran_toTavern";
            AddQuestRecord("Fra_Line_1_LegranDis", "1");
            sld = GetCharacter(NPC_GenerateCharacter("Legran", "officer_9", "man", "man", 40, FRANCE, -1, false));
			FantomMakeCoolFighter(sld, 40, 90, 40, "blade33", "pistol10", 120);
			sld.name = "Pierre";
			sld.lastname = "Legrand";
            sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			sld.money = 1000000;
			sld.items.jewelry5 = 30;
			sld.items.indian6 = 1;
			sld.items.jewelry14 = 12;
			sld.items.indian2 = 1;
			sld.items.indian8 = 1;
			sld.items.indian7 = 1;
			sld.items.indian12 = 1;
			sld.items.jewelry2 = 20;
			sld.greeting = "Gr_MiddPirate";
			GiveItem2Character(sld, "cirass3");
			FreeSitLocator("Tortuga_tavern", "sit3");
            LAi_SetSitType(sld);
            ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit3");
        break;
		case "Step_1_2":
            dialog.text = "Well, I'm not detaining you at the moment, but I ask you not to disappear from my field of vision for a long time - I often have a job for a filibuster.";
            link.l1 = "All right, Monsieur Governor-General, I will visit you from time to time.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "2";
            pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Fra_Line_1_LegranDis");
			AddTitleNextRate(sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Sneak", -170);
			AddCharacterExpToSkill(pchar, "Commerce", 90);
			AddCharacterExpToSkill(pchar, "Fencing", 80);
			AddCharacterExpToSkill(pchar, "Fortune",70);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
        break;
        case "Step_1_3":
            dialog.text = "Hmm, all this is fine, but here's the problem - Legrand himself is missing. He was supposed to write to me before leaving Fort de France, but there is no letter, and he himself has disappeared into the water. What do you think about it?";
            link.l1 = "I'm not aware, monsieur...";
            link.l1.go = "Step_1_4";
        break;
        case "Step_1_4":
            dialog.text = "It's all weird... That's what, "+ GetSexPhrase("sir", "miss") +", I don't want to deal with you anymore. Moreover, if I ever find out that you killed Legrand, it's hard for me to describe in words what will happen to you\n"+
				          "I'm not detaining you!";
            link.l1 = "I understand, monsieur...";
            link.l1.go = "exit";
            pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_1_LegranDis");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -3);
			bWorldAlivePause   = false; // Конец линейки
			ChangeCharacterReputation(pchar, -10);
			AddCharacterExpToSkill(pchar, "Sneak", -170);
			//слухи
			AddSimpleRumour("You heard captain " + GetMainCharacterNameGen() + " was kicked out of the residence for some dark story related to Legrand by governor-General ... Now you have a 'wolf ticket.'", FRANCE, 5, 1);
        break;
        case "Step_1_5":
            dialog.text = "Yes, I am already aware of this sad event... It's a pity that Legrand never managed to return to normal life, it's a pity...";
            link.l1 = "I knew that he's just a little bit, but he seemed like a good guy to me.";
            link.l1.go = "Step_1_6";
        break;
		case "Step_1_6":
            dialog.text = "And it really is, "+ GetSexPhrase("monsieur", "mademoiselle") +" " + pchar.lastname + ". Well, it's sad that this happened, but nevertheless, I am grateful for your cooperation. Therefore, I ask you to look me up from time to time - perhaps a job for a filibuster will turn up.";
            link.l1 = "All right, Monsieur d'Ogeron, I will be visiting your residence.";
            link.l1.go = "Step_1_7";
        break;
        case "Step_1_7":
            dialog.text = "One minute, "+ GetSexPhrase("sir", "miss") +"! Return the money Legrand had, it doesn't belong to you.";
            link.l1 = "Hmm, monsieur...";
            link.l1.go = "Step_1_8";
        break;
        case "Step_1_8":
            dialog.text = "I will never believe that you didn't take them away. Therefore, give me back 1200,000 coins, and I will continue to cooperate with you.";
            link.l1 = "Why are there so many - 1200000?";
            link.l1.go = "Step_1_9";
        break;
        case "Step_1_9":
            dialog.text = "Because I know how much money Legrand had.";
			link.l1 = "So what should I do now?";
			link.l1.go = "Step_1_10";
        break;
        case "Step_1_10":
            dialog.text = "Until you return Legrand's money to me in full, you have nothing to do at my residence.";
			if (sti(pchar.money) >= 1200000)
			{
				link.l1 = "All right, monsieur, take it...";
				link.l1.go = "Step_1_11";
				AddMoneyToCharacter(pchar, -1200000);
				NextDiag.TempNode = "First time";
			}
			else
			{
				link.l1 = "I don't have enough money yet. But I'll get them and bring them to you.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Step_1_10";
			}
        break;

		case "Step_1_11":
            dialog.text = "Well, we're even. You can visit me now, I will give you a job from time to time, "+ GetSexPhrase("sir", "miss") +".";
			link.l1 = "Very good, Mr. Governor General.";
			link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "2";
            pchar.questTemp.Waiting_time = "15";
			CloseQuestHeader("Fra_Line_1_LegranDis");
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			AddCharacterExpToSkill(pchar, "Grappling", 120);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour("You know, Captain " + GetFullName(pchar) + " was hired by the Governor-General to accompany the glorious corsair Legrand. And "+ GetSexPhrase("he", "she") +" honorably fulfilled this assignment!", FRANCE, 5, 1);
        break;
        //********************** Квест №2 доставка письма на Кюрасао ************************
        case "Step_2_1":
            dialog.text = "Peter Stuyvesant, Governor General of Curacao, my personal friend and friend of the Republic of the United Provinces. Therefore, do not try to do anything like that there, otherwise, upon arrival at Tortuga, I will skin you.";
			link.l1 = "Monsieur Bertrand, I am a filibuster, but does it look like irresponsible? Everything will be done in the best possible way, don't worry.";
            link.l1.go = "Step_2_2";
        break;
        case "Step_2_2":
            dialog.text = "Well, very good. Go, "+ GetSexPhrase("sir", "miss") +".";
            link.l1 = "Goodbye, monsieur.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
    		pchar.questTemp.State = "Fr2Letter_toCuracao";
            AddQuestRecord("Fra_Line_2_DelivLetter", "1");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_FraLineQ1");
            GiveItem2Character(pchar, "letter_1");
        break;
        case "Step_2_3":
            dialog.text = "Did everything go well, without any trouble?";
			link.l1 = "Well, how can I tell you, not really. I was first arrested for some unknown reason, then released...";
            link.l1.go = "Step_2_4";
        break;
        case "Step_2_4":
            dialog.text = "What could you have been arrested for?";
			link.l1 = "I have no idea. For the appearance, I suppose. But it ended well in the end, monsieur. So there's no reason to worry right now.";
            link.l1.go = "Step_2_5";
        break;
        case "Step_2_5":
            dialog.text = "Yeah, it's weird... Well, all right. I don't have a job for you at the moment, so drop by my residence from time to time, maybe something will turn up.";
			link.l1 = "All right, Monsieur Governor-General.";
            link.l1.go = "exit";
			group_DeleteGroup("Spa_Attack");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "20";
			CloseQuestHeader("Fra_Line_2_DelivLetter");
			DeleteAttribute(pchar, "questTemp.Out");
			DeleteAttribute(pchar, "questTemp.shore");
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Accuracy", 200);
			ChangeCharacterReputation(pchar, -1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//слухи
			AddSimpleRumour("Did you hear that, Captain " + GetFullName(pchar) + ", performed duties of the vests for our Governor-General. And you know, a strange story happened to "+ GetSexPhrase("him", "her") +" in Willemstad, very strange...", FRANCE, 5, 1);
        break;
        case "Step_2_6":
            dialog.text = "What happened, "+ GetSexPhrase("sir", "miss") +"?";
			link.l1 = "Oh, monsieur, let's take it in order. At first they threw me in jail and wanted to hang me, but they released me the next morning.";
            link.l1.go = "Step_2_7";
        break;
        case "Step_2_7":
            dialog.text = "How to hang? You were my messenger!";
			link.l1 = "They thought I was a spy from bandits who plunder Dutch ships near Curacao. In general, in the end I found and finished this gang. They turned out to be Spanish privateers, how do you like that?!";
            link.l1.go = "Step_2_8";
        break;
        case "Step_2_8":
            dialog.text = "Spanish privateers?! Haha, that sounds very convincing\n"+
				          "It's good that you were able to prove yourself in Willemstad. I am glad that I assigned this task to "+ GetSexPhrase("such a meticulous filibuster", "such a smart and brave girl") +"\n"+
						  "Now I don't dare to detain you anymore - rest. But in a week or two, please come to my residence, I will find more work for you.";
			link.l1 = "Excellent, Monsieur Governor-General. I will definitely be there.";
            link.l1.go = "exit";
			group_DeleteGroup("Spa_Attack");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "10";
			CloseQuestHeader("Fra_Line_2_DelivLetter");
			DeleteAttribute(pchar, "questTemp.Out");
			DeleteAttribute(pchar, "questTemp.shore");
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			//слухи
			AddSimpleRumour("Did you hear that, Captain " + GetFullName(pchar) + ", performed duties of the messenger for our Governor-General. And you know, a strange story happened to "+ GetSexPhrase("him", "her") +" in Willemstad - "+ GetSexPhrase("he", "she") +" was arrested. But to the credit of the French, "+ GetSexPhrase("he managed", "she managed") +" to get out of the situation. D'Ogeron must be pleased...", FRANCE, 5, 1);
		break;
        //********************** Квест №3 похищение донны Анны ************************
        case "Step_3_1":
            dialog.text = "There is a rumor about you that you are desperate"+ GetSexPhrase("thug", "daredevil") +", and I know that for you the word 'honor' is not an empty word. I admit it's not easy for me to trust you, but I think it's the best option... My life is in your hands, and it's up to you to decide whether you will exchange it for gold or prove that you are "+ GetSexPhrase("knight", "noble woman") +"!";
			link.l1 = "Damn it, anyone will say that I can cut throats, but no one will dare to say that I am "+ GetSexPhrase("scoundrel and traitor", "traitor") +"! I'm listening to you.";
            link.l1.go = "Step_3_2";
        break;
        case "Step_3_2":
            dialog.text = "You probably know that I ordered the delivery of friends from France for our brave filibusters. Now Tortuga is a pirate's paradise, there are vibes of love everywhere, women's laughter turns your head... But alas, not everyone eats the fruits of paradise.";
			link.l1 = "Did Amur target more than just Buccaneers?";
            link.l1.go = "Step_3_3";
        break;
        case "Step_3_3":
            dialog.text = "It's not about me. There is a lady who will be happy to breathe the free air of our colony, but is forced to stay locked up under the rule of an abusive spouse... To rescue her from the dungeon in which she resides is a matter of "+ GetSexPhrase("worthy of a cavalier", " fair! You, as a woman, must understand me") +"!";
			link.l1 = "Thank the Creator, you finally got to the bottom of it. Who do I owe to save?";
            link.l1.go = "Step_3_4";
        break;
        case "Step_3_4":
            dialog.text = "So you're taking on this case? Great! The lady I am talking about is the wife of Don Jose Ramirez de Leyva, the commandant of Havana. You have to get into the city and find a way to get her out of there\n"+
						  "In order for you to do this successfully, I am giving you a Spanish Escorial Trading License for a period of 15 days, with which you will be allowed to enter Spanish ports and visit Spanish cities. And make sure that a friendly Spanish flag is flying on your ship\n"+
				          "Here, take this ring, by it Donna Anna Ramirez de Leyva will know that you are my trusted person. And remember, the honor of this worthy woman is in your hands.";
			link.l1 = "I understand you, monsieur. I admit it's an unusual thing, but I appreciate your trust... Everything will be done in the best possible way - do not hesitate.";
            link.l1.go = "exit";
            GiveNationLicence(SPAIN, 15);
			GiveItem2Character(pchar, "DOjeronRing");
    		pchar.questTemp.State = "Fr3TakeAnna_toHavana";
            AddQuestRecord("Fra_Line_3_TakeAnna", "1");
	    AddQuestUserData("Fra_Line_3_TakeAnna", "sSex", GetSexPhrase("", "a"));
			LocatorReloadEnterDisable("Havana_town", "houseS1", true);
        break;
        case "Step_3_5":
            dialog.text = "The devil! And I was counting on your intelligence and skill. What happened?";
			link.l1 = "Nothing special, monsieur. I just couldn't to get close to her is the wife of the commandant of the capital, after all...";
            link.l1.go = "Step_3_6";
        break;
        case "Step_3_6":
            dialog.text = "Yeah, it's sad... Well, it was my personal request to you, so you are not to blame in front of France\n"+
				          "I ask you to come to me in the future, perhaps I will have a case for you.";
			link.l1 = "All right, Monsieur Governor-General...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "20";
			CloseQuestHeader("Fra_Line_3_TakeAnna");
            TakeItemFromCharacter(pchar, "letter_open");
            BackItemDescribe("letter_open");
			TakeNationLicence(SPAIN);
			ChangeCharacterReputation(pchar, 10);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//слухи
			AddSimpleRumour("Rumor has it that captain " + GetFullName(pchar) + ", failed some very important task for d'Ogeron, related to amorous affairs...", FRANCE, 5, 1);
		break;
        case "Step_3_7":
			dialog.text = "Nevertheless, accept a modest reward from me\n"+
				          "And damn it, you leave me alone, I'm not up to administrative matters right now. Come back in a while...";
			link.l1 = "All right, Monsieur Governor-General. I will definitely be there later...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "40";
			CloseQuestHeader("Fra_Line_3_TakeAnna");
            TakeItemFromCharacter(pchar, "letter_open");
            BackItemDescribe("letter_open");
			TakeNationLicence(SPAIN);
			AddMoneyToCharacter(pchar, 25000);
            sld = characterFromId("AnnaDeLeiva");
            RemovePassenger(pchar, sld);
			DeleteAttribute(sld, "RebirthPhantom");
         	sld.LifeDay = 0; // уберём нпс
			pchar.questTemp.AnnaIsLife = true; //но оставим флаг на пятый квест
			//==> вешаем прерывание на узнавание в таверне.
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition.l1 = "location";
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition.l1.location = "Havana_tavern";
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition = "Fr3_AfterAnna_IKnowYou";
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			//слухи
			AddSimpleRumour("Rumor has it that it is captain " + GetFullName(pchar) + ", showed miracles of bravery and resourcefulness, and brought the Spanish passion here d'Ogeron - donna Anna...", FRANCE, 5, 1);
		break;

        //********************** Квест №4  Солей Руаяль ************************
		case "Step_4_1":
            dialog.text = "Yes, I know that you are the sailor, not a alcove secrets lover. But I'll reassure you: the current case is to your taste. Recently, the most powerful and beautiful ship in the world, the Soleil Royal, was launched in the metropolis. His Majesty is interested in the safety of the French colonies in the West Indies, and it is a great honor for us that this ship is sent to us.";
			link.l1 = "When will it arrive?";
            link.l1.go = "Step_4_2";
        break;
		case "Step_4_2":
            dialog.text = "He's already here, on the raid. And now he has to leave for Dominica. You should accompany him to this island.";
			link.l1 = "With my ship - to guard the best ship in France? Hmm, it's weird...";
            link.l1.go = "Step_4_3";
        break;
		case "Step_4_3":
            dialog.text = "Nothing strange. Two ships are always better than one, and you are "+ GetSexPhrase("brave and skillful captain", "brave and skillful captain") +". Besides, I have reason to believe that the Spaniards are going to hunt the Soleil Royal. Three or four galleons with a boarding crew on board are quite capable of capturing even the most powerful ship\n"+
				          "Moreover, I know for sure that these galleons under the command of one Juan Galeno are already ready. Lay down your life if necessary, but we must not allow our flagship to fall into the hands of the Escorial. Either you will return with a report on the successful completion of the mission, or it is better not to return...";
			link.l1 = "Lay down your life... I am far from a coward"+ GetSexPhrase("", "iha") +"but it doesn't sound very tempting!";
            link.l1.go = "Step_4_4";
        break;
		case "Step_4_4":
            dialog.text = "I got the hint, Captain. I hope the promise of a generous reward for this work sounds tempting?";
			link.l1 = "Why take the ship to Dominica? It's a desert island...";
            link.l1.go = "Step_4_5";
        break;
		case "Step_4_5":
            dialog.text = "There you will have to connect with the squadron from Guadeloupe. She should be sent to Dominica by the Governor-General of Basse-Terre " + GetFullName(characterFromId("BasTer_Mayor")) + ".";
			link.l1 = "Understood. Well, I agree to complete this assignment.";
            link.l1.go = "Step_4_6";
        break;
		case "Step_4_6":
            dialog.text = "Excellent. So, the Soleil Royal comes under your command. I ask you to report to the head of the port immediately, he will register captain of the Soleil Royal as your companion.";
			link.l1 = "We are going, monsieur.";
            link.l1.go = "exit";
			pchar.questTemp.State = "Fr4SoleiRoyal_toPortMan";
			AddQuestRecord("Fra_Line_4_SoleiRoyal", "1");
        break;
		case "Step_4_7":
            dialog.text = "I can't believe it... You abandoned the Soleil Royal to save yourself?!";
			link.l1 = "I had to do it monsieur...";
            link.l1.go = "Step_4_8";
        break;
		case "Step_4_8":
            dialog.text = "Everything is clear to me - you "+ GetSexPhrase("uniform coward", "just a cowardly girl") +", captain. I ask you to leave immediately, I don't want to see you anymore. Maybe someday you will be able to count on my favor, but not in the near future...";
			link.l1 = "Okay, monsieur, I understand.";
            link.l1.go = "Step_4_check";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // Конец линейки
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour("There are rumors that our governor-General kicked you out of the residence for abandoning the Soleil Royal in battle. Heh, it serves you right...", FRANCE, 5, 1);
        break;
		case "Step_4_9":
            dialog.text = "Damn it, you failed to protect the Soleil Royal... This is a disaster...";
			link.l1 = "Monsieur Governor General, I did everything I could...";
            link.l1.go = "Step_4_10";
        break;
		case "Step_4_10":
            dialog.text = "We tried very badly, since we couldn't complete an elementary task. You drown the Spaniards by the dozens, and then you couldn't settle everything! I'm extremely disappointed in you and I don't want to deal with you anymore!"+
				          "Now leave me alone!";
			link.l1 = "All right, monsieur...";
            link.l1.go = "Step_4_check";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // Конец линейки
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour("There are rumors that our governor-General kicked you out of the residence because you managed to sink the Soleil Royal. Heh, it serves you right...", FRANCE, 5, 1);
        break;
		case "Step_4_11":
            dialog.text = "Hmm, unforeseen circumstances... Well, you made the right decision, "+ GetSexPhrase("sir", "miss") +". I congratulate you on the successful completion of another case and ask you to accept a reward of 28,000 gold.";
			link.l1 = "Thank you, Monsieur Governor General...";
            link.l1.go = "Step_4_12";
        break;
		case "Step_4_12":
            dialog.text = "I ask you to be at my residence in a week or two, perhaps I have a new case for you.";
			link.l1 = "All right, sir. I will definitely be with you.";
            link.l1.go = "Step_4_check";
			npchar.quest.answer_3 = "true";
			AddMoneyToCharacter(pchar, 28000);
            pchar.questTemp.Waiting_time = "8";
        break;
		case "Step_4_check":
			if (CheckAttribute(pchar, "questTemp.AnnaIsLife"))
			{
				pchar.questTemp.CurQuestNumber = "5";
				DeleteAttribute(pchar, "questTemp.AnnaIsLife");
			}
			else pchar.questTemp.CurQuestNumber = "6";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "empty";
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			//слухи
			AddSimpleRumour("There are rumors that the Spaniards attacked you while escorting the Soleil Royal! Let me express my admiration to you"+ GetSexPhrase(" - you are a wonderful sailor and a real warrior", " - you are a real Joan of Arc") +"!", FRANCE, 5, 1);
			DialogExit();
        break;
        //********************** Квест №6. Доставка письма Олоне ************************
		case "Step_6_1":
            dialog.text = "That's it. And keep in mind that under no circumstances should this letter end up in the wrong hands. If you get into trouble, you don't even have the right to die before you destroy the package.";
			link.l1 = "Do you think there will be people who want to see what's in this letter?";
            link.l1.go = "Step_6_2";
        break;
		case "Step_6_2":
            dialog.text = "There has never been a shortage of curious people. Go at once, the reward will be given to you by Monsieur David himself.";
			link.l1 = "All right, Monsieur Governor-General. I hope it will be worthy.";
            link.l1.go = "exit";
			LAi_group_Delete("PeaceGroup");
    		pchar.questTemp.State = "Fr5Olone_toGuadeloupe";
            AddQuestRecord("Fra_Line_6_Olone", "1");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_FraLineQ6");
            GiveItem2Character(pchar, "letter_1");
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition.l1 = "location";
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition.l1.location = "Guadeloupe";
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition = "Fr6Olone_GuadeloupeBattle";
			//==> Олоне
            sld = GetCharacter(NPC_GenerateCharacter("Olone", "BigPirate", "man", "man", 45, FRANCE, -1, false));
            FantomMakeCoolSailor(sld, SHIP_FRIGATE, "Blood Demon", CANNON_TYPE_CULVERINE_LBS32, 90, 80, 80);
			FantomMakeCoolFighter(sld, 45, 100, 90, "blade28", "pistol5", 200);
			sld.name = "Francois";
			sld.lastname = "Olone";
            sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			sld.RebirthPhantom = true;
			sld.greeting = "Gr_EvilPirate";
			ChangeCharacterReputation(sld, -100);
            LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
            ChangeCharacterAddressGroup(sld, "BasTer_houseF1", "goto", "goto5");
        break;
		case "Step_6_3":
            dialog.text = "What happened?";
			link.l1 = "Monsieur Governor-General, Olone and I have agreed to take Cumana... They took it, but then there was a quarrel... In general, Olone is dead, sir...";
            link.l1.go = "Step_6_4";
        break;
		case "Step_6_4":
            dialog.text = "Wow... And who is this hero who dared to challenge Francois Olona himself?";
			link.l1 = "Monsieur, "+ GetSexPhrase("this is your humble servant, ", "um.. It's me") +"...";
            link.l1.go = "Step_6_5";
        break;
		case "Step_6_5":
            dialog.text = "Yes, you are, "+ GetSexPhrase("sir, desperate thug", "madam, desperate daredevil") +"! Olone is a demon in the flesh\n"+
				          "I would not say that I like his death, but I will not be particularly sad either. Moreover, such fights are not uncommon among the Brethren.";
			link.l1 = "That's right, Monsieur Governor-General.";
            link.l1.go = "Step_6_6";
        break;
		case "Step_6_6":
            dialog.text = "Well, I won't keep you any longer. I don't have any business for you yet, but you can come by my place from time to time...";
			link.l1 = "All right, sir, that's exactly what I'll do.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "30";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", 170);
			AddCharacterExpToSkill(pchar, "Sneak", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//слухи
			AddSimpleRumour("There are rumors that you have dealt with Francois Olone himself! Yes, I'll tell you, you're desperate for courage"+ GetSexPhrase("man", "girl") +"...", FRANCE, 5, 1);
        break;
		case "Step_6_7":
            dialog.text = "Oh, that's great. In fact, it was the capture of Cumana that I sought. Well, great job, "+ GetSexPhrase("my friend", "mademoiselle") +". I am quite satisfied with your promptness.";
			link.l1 = "Thank you for the kind words addressed to me, sir. For this, let me take my leave - business ...";
            link.l1.go = "Step_6_8";
        break;
		case "Step_6_8":
            dialog.text = "Yes, of course, I dare not detain you, Captain. But don't forget to drop by my residence from time to time.";
			link.l1 = "All right, Monsieur Governor-General.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 6);
			AddCharacterExpToSkill(pchar, "Grappling", 220);
			AddCharacterExpToSkill(pchar, "Sneak", 160);
			AddCharacterExpToSkill(pchar, "Defence", 280);
			AddCharacterExpToSkill(pchar, "Accuracy", 190);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			//слухи
			AddSimpleRumour("There are rumors around the city that you have looted Cumana with Francois Olone. The Spanish Dons must have fucked themselves up! ", FRANCE, 5, 1);
        break;
		case "Step_6_9":
            dialog.text = "What did Olone do in connection with the dispatch?";
			link.l1 = "He offered me a trip to Cumana. Unfortunately, I had to refuse. However, I think he can handle it without me, having three ships in his squadron.";
            link.l1.go = "Step_6_10";
        break;
		case "Step_6_10":
            dialog.text = "Well, let's hope my plan works... I dare not detain you any longer, "+ GetSexPhrase("sir", "miss") +". Don't forget to visit me from time to time, you may be needed.";
			link.l1 = "All right, Monsieur Governor-General.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "15";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 2);
			AddCharacterExpToSkill(pchar, "Sneak", 190);
			AddCharacterExpToSkill(pchar, "Defence", 150);
			AddCharacterExpToSkill(pchar, "Accuracy", 220);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
        break;
        //********************** Квест №7. Вызволение из тюрьмы Рока Бральзильца ************************
		case "Step_7_1":
            dialog.text = "Spaniards got into the clutches of the famous filibuster Rock Brazilian. He does not have to wait for mercy, because he has pinched the Spaniards a lot. Of course, before introducing Rock to the hemp aunt, they will want to find out where he hid the gold taken from them. But that's not even the most important thing.";
			link.l1 = "Gold is not the main thing?! What then?";
            link.l1.go = "Step_7_2";
        break;
		case "Step_7_2":
            dialog.text = "The Holy fathers of the Inquisition are able to loosen tongues, and I am afraid that the Brazilian will tell not only about gold...";
			link.l1 = "... but also about the letters that, as I believe, are delivered on your behalf not only to Jean David...";
            link.l1.go = "Step_7_3";
        break;
		case "Step_7_3":
            dialog.text = "That's right. So you understand: you need to act without delay. I was informed that Rock had been sent to a Havana prison. You must get there as quickly as possible and get him out of captivity at any cost. I want the Brazilian to be here, and if possible alive and well.";
			link.l1 = "But if he dies...";
            link.l1.go = "Step_7_4";
        break;
		case "Step_7_4":
            dialog.text = "Then the Spaniards won't know anything, but neither will we. And I have reason to believe that Rock, in gratitude for the rescue, will give the government possession of some of his treasures...";
			link.l1 = "The task is not easy, but just for me! I'm leaving immediately.";
            link.l1.go = "Step_7_5";
        break;
		case "Step_7_5":
            dialog.text = "Very good. Also - in the city you need to act covertly, if possible without raising the alarm. To do this, I once again give you the credentials of a Spanish trading company.";
			link.l1 = "Thank you very much, Mr. Governor General.";
            link.l1.go = "exit";
			LAi_group_Delete("PeaceGroup");
			GiveNationLicence(SPAIN, 10);
			SetNationRelation2MainCharacter(SPAIN, RELATION_NEUTRAL);
    		pchar.questTemp.State = "Fr7RockBras_toSeekPlace";
            AddQuestRecord("Fra_Line_7_RockBras", "1");
			SaveCurrentQuestDateParam("questTemp");
			//==> Бразильца - в инквизицию.
            sld = GetCharacter(NPC_GenerateCharacter("RockBrasilian", "bocman", "man", "man", 30, PIRATE, -1, false));
			FantomMakeCoolFighter(sld, 30, 90, 90, "", "", 80);
            sld.Dialog.Filename    = "Quest\FraLineNpc_2.c";
			sld.RebirthPhantom = true;
        	sld.name 	= "Rock";
        	sld.lastname 	= "Brazilian";
			LAi_LoginInCaptureTown(sld, true);
			LAi_NoRebirthEnable(sld);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetGroundSitType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
			ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "prison", "prison9");

			sld = CharacterFromID("AntonioDeSouza");	//Прячем главу инквизиции на время квеста
			ChangeCharacterAddressGroup(sld, "none", "", "");
        break;
		case "Step_7_6":
            dialog.text = "Hmm, useless in your performance, "+ GetSexPhrase("monsieur", "mademoiselle") +". Don't speak for the whole New World\n"+
				          "Very sorry, "+ GetSexPhrase("sir", "miss") +". It is a pity that you failed to complete the tasks... I don't think I need you anymore. You can come to my residence periodically, perhaps there will be a job for you...";
			link.l1 = "All right, Monsieur Governor-General.";
            link.l1.go = "Step_7_exit";
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			//слухи
			AddSimpleRumour("They say captain " + GetFullName(pchar) + ", failed to get Rock the Brazilian out of the Spanish dungeons. Bad, he was a good man...", FRANCE, 5, 1);
            pchar.questTemp.Waiting_time = "35";
        break;
		case "Step_7_7":
            dialog.text = "Yeah, it's sad... He was a good privateer and a real man. Very sorry\n"+
				          "Well, I suppose you did everything possible to save him. Therefore, I invite you to be at my residence in a couple of weeks - I will find a new case for you.";
			link.l1 = "All right, sir, I will certainly be there.";
            link.l1.go = "Step_7_exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 100);
			AddCharacterExpToSkill(pchar, "Defence", 100);
			AddCharacterExpToSkill(pchar, "Cannons", 100);
			//слухи
			AddSimpleRumour("They say captain " + GetFullName(pchar) + ", failed to get Rock the Brazilian out of the Spanish dungeons. Bad, he was a good man...", FRANCE, 5, 1);
            pchar.questTemp.Waiting_time = "15";
        break;
		case "Step_7_exit":
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
			CloseQuestHeader("Fra_Line_7_RockBras");
			TakeNationLicence(SPAIN);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
            sld = characterFromId("RockBrasilian");
			DeleteAttribute(sld, "RebirthPhantom");
         	sld.LifeDay = 0; // уберём нпс
			sld = CharacterFromID("AntonioDeSouza");	//Возвращаем главу инквизиции на место
			ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "sit", "armchair1");
			DialogExit();
        break;
		case "Step_7_8":
            dialog.text = "Don't be modest, Captain. The reward for the work done is 30 thousand coins. Please receive it.";
			link.l1 = "Thank you, Monsieur Governor General...";
            link.l1.go = "Step_7_9";
        break;
		case "Step_7_9":
            dialog.text = "As always, I ask you to look into my residence from time to time, I believe that I will need you in the near future.";
			link.l1 = "Well, sir, I will definitely visit you.";
            link.l1.go = "Step_7_Rock";
			AddMoneyToCharacter(pchar, 30000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
			CloseQuestHeader("Fra_Line_7_RockBras");
            TakeNationLicence(SPAIN);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			//слухи
			AddSimpleRumour("They say captain " + GetFullName(pchar) + ", pulled out Rock the Brazilian from Spanish dungeons. Good news, I'll tell you, Rock is respected here.", FRANCE, 5, 1);
        break;
		case "Step_7_Rock":
			sld = characterFromId("RockBrasilian");
			RemovePassenger(PChar, sld);
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			DialogExit();
        break;
        //********************** Квест №8. Встреча с тремя корсарами ************************
		case "Step_8_1":
            dialog.text = "So far, the only thing is to come to the marquis as soon as possible. I don't know the details, apparently, the case will be very secret.";
			link.l1 = "Well, I'm not in the first one. No problem, I'm going...";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr8ThreeCorsairs_toBonrepo";
            AddQuestRecord("Fra_Line_8_ThreeCorsairs", "1");
			//==> маркиз Бонрепо.
            sld = GetCharacter(NPC_GenerateCharacter("Bonrepo", "huber_fra", "man", "man", 20, FRANCE, -1, false));
            sld.Dialog.Filename    = "Quest\FraLineNpc_1.c";
        	sld.name 	= "Marquis";
        	sld.lastname 	= "Bonrepo";
			sld.greeting = "Gr_QuestMan";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "BasTer_townhall", "goto", "governor1");
        break;
		case "Step_8_2":
            dialog.text = "Captain, not everything in this life is measured by money. No amount of money can buy the honor of a nobleman and the respect of others.";
			link.l1 = "That's right, monsieur...";
            link.l1.go = "Step_8_3";
        break;
		case "Step_8_3":
            dialog.text = "Well, I don't have any new requests for you yet, but I'll be happy if you visit me from time to time - maybe we still have things to do together!";
			link.l1 = "All right, sir. I, as "+ GetSexPhrase("French nobleman, baron", "French noblewoman, baroness") +", will visit your residence more often.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "12";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
			CloseQuestHeader("Fra_Line_8_ThreeCorsairs");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", -100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			//слухи
			AddSimpleRumour("They say that captain " + GetMainCharacterNameDat() + " was granted the noble title of "+ GetSexPhrase("Baron", "Baronessa") +"! Well, things are...", FRANCE, 5, 1);
        break;
        //********************** Квест №9. Отбить нападение на Порт-о-Принс ************************
		case "Step_9_1":
            dialog.text = "That's right, "+ GetSexPhrase("Baron", "Baronessa") +". They have already attacked the La Vega Buccaneer settlement, now, apparently, it is the turn for Port-au-Prince.";
			link.l1 = "I understand, sir. Can I start the task?";
            link.l1.go = "Step_9_11";
        break;
		case "Step_9_11":
            dialog.text = "Basically, yes. However, I need to bring the following to you - the Soleil Royal is being assigned to you as a squadron reinforcement\n"+
				          "In no case should you lose this ship, it will mean the failure of the mission. And you won't be able to work for the French government anymore.";
			link.l1 = "Hmm, well, I will take all measures to ensure that the magnificent Soleil Royal is not seriously damaged.";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr9GuardPP_toPortPax";
            AddQuestRecord("Fra_Line_9_GuardPortPax", "1");
			sld = GetCharacter(NPC_GenerateCharacter("SoleiRoyalCaptain", "off_fra_2", "man", "man", 35, FRANCE, -1, true));
			sld.Ship.Type = CreateBaseShip(SHIP_SOLEYRU);
			sld.Ship.Name = "Soleil Royal";
			SetBaseShipData(sld);
			ResetShipCannonsDamages(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");
			FantomMakeCoolFighter(sld, 35, 80, 70, BLADE_LONG, "pistol3", 100);
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetShipRemovable(sld, false);
			pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
			SetTimerCondition("Fr9GuardPP_Late", 0, 0, 5, false);
            Pchar.quest.Fr9GuardPP_Fight.win_condition.l1 = "location";
            Pchar.quest.Fr9GuardPP_Fight.win_condition.l1.location = "Hispaniola2";
            Pchar.quest.Fr9GuardPP_Fight.win_condition = "Fr9GuardPP_Fight";
        break;
		case "Step_9_2":
            dialog.text = "That's right, "+ GetSexPhrase("Baron", "Baronessa") +", and performed brilliantly. The French government has provided a certain amount for the repair of ships and replenishment of personnel - 5 thousand gold... Please receive it.";
			link.l1 = "Only 5 thousand?! Carramba, it's less than nothing!";
            link.l1.go = "Step_9_3";
        break;
		case "Step_9_3":
            dialog.text = ""+ GetSexPhrase("Baron", "Baronessa") +", this war requires all of us to exert ourselves as much as possible. I ask you to understand the situation - there is a catastrophic shortage of money. Therefore, I ask you to accept the current situation as a given\n"+
				          "I don't dare detain you now - prepare for the next military action. And remember - France needs you!";
			link.l1 = "Um, well, if I'm so needed to France - it'll get me. I will be at your residence after I have put my affairs in order, sir. Goodbye.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "18";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
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
			AddSimpleRumour("They say captain " + GetFullName(pchar) + ", saved inhabitants of Port-au-Prince from the Spaniards!", FRANCE, 5, 1);
        break;
		case "Step_9_4":
            dialog.text = "But you've lost the Soleil Royal, Captain, and there's no excuse for that!";
			link.l1 = "I did everything that was in my power...";
            link.l1.go = "Step_9_5";
        break;
		case "Step_9_5":
            dialog.text = "You haven't done enough! In general, the loss of such a ship has led to the fact that France refuses your services, "+ GetSexPhrase("sir", "miss") +". Goodbye.";
			link.l1 = "And this is after everything I've done for Crown of France?! Goodbye, sir, I'm already pretty tired of all this...";
            link.l1.go = "exit";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // Конец линейки
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//слухи
			AddSimpleRumour("There are rumors that our governor-General kicked you out of the residence because you managed to sink the Soleil Royal. Heh, it serves you right...", FRANCE, 5, 1);
        break;
		case "Step_9_6":
            dialog.text = "Damn it, you're just "+ GetSexPhrase("uniform coward", "cowardly girl") +"! I don't want anything to do with you. Goodbye, "+ GetSexPhrase("Baron", "Baronessa") +"...";
			link.l1 = "Farewell, sir, my fervent greetings to the Marquis Bonrepos...";
            link.l1.go = "exit";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // Конец линейки
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//слухи
			AddSimpleRumour("There are rumors that our governor-General kicked you out of the residence for abandoning the Soleil Royal in battle. Heh, it serves you right...", FRANCE, 5, 1);
        break;
		case "Step_9_7":
            dialog.text = "Devil, how is that?! It's been two days here!! Anyway, I don't want to have anything to do with you. Goodbye, "+ GetSexPhrase("Baron", "Baronessa") +"...";
			link.l1 = "Farewell, sir, my fervent greetings to the Marquis Bonrepos...";
            link.l1.go = "exit";
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			sld.LifeDay = 0;
			pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			bWorldAlivePause   = false; // Конец линейки
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//слухи
			AddSimpleRumour("There are rumors that our governor-General kicked you out of the residence because you failed to arrive at Port-au-Prince on time and the city was ravaged by the Spaniards. Serves you right!", FRANCE, 5, 1);
        break;
        //********************** Квест №10. Захват Санто-Доминго ************************
		case "Step_10_1":
            dialog.text = "It is time to give an adequate response to the attempted capture of Port-au-Prince. And, it seems to me, the best answer would be the embodiment of the Spanish plan to capture Hispaniola, only in a mirror image...";
			link.l1 = "Monsieur Governor-General, I ask you to speak less ornately.";
            link.l1.go = "Step_10_2";
        break;
		case "Step_10_2":
            dialog.text = "Okay, "+ GetSexPhrase("Baron", "Baronessa") +". So, I charge you to capture Santo Domingo! Thus, the whole of Hispaniola will belong entirely to one power, but not to Spain, but to France. Do you understand now?";
			link.l1 = "I see, sir. Tell me, how about paying for this military operation? I can't keep the Soleil Royal and wage war at my own expense!";
            link.l1.go = "Step_10_3";
        break;
		case "Step_10_3":
            dialog.text = "Yes, I understand. The issue has essentially been resolved - after the capture of Santo Domingo, you will receive a very significant reward.";
			link.l1 = "Well, sir, I believe you. So, I'm starting the operation, wait for me with good news.";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr10OccupySD_toSantoDomingo";
            AddQuestRecord("Fra_Line_10_OccupySantoDomingo", "1");
			CloseQuestHeader("Fra_Line_12_EndOfWar");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			characters[GetCharacterIndex("SantoDomingo_Mayor")].dialog.captureNode = "FraLine10Quest_OccupySD"; //капитулянтская нода мэра
        break;
		case "Step_10_4":
            dialog.text = "You've lost the Soleil Royal!!";
			link.l1 = "The battle was hot, Monsieur Governor-General, the handsome ship really went down. I'm really sorry...";
            link.l1.go = "Step_10_5";
        break;
		case "Step_10_5":
            dialog.text = "I don't need your regrets. The loss of this ship is a terrible tragedy for France. That's why I don't want to deal with you anymore, the French government won't entrust you with anything anymore. Goodbye.";
			link.l1 = "Hmm, as you know, sir...";
            link.l1.go = "exit";
			CloseQuestHeader("Fra_Line_10_OccupySantoDomingo");
			pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_12_EndOfWar");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			bWorldAlivePause   = false; // Конец линейки
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "FencingLight", -130);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -130);
			AddCharacterExpToSkill(pchar, "Fencing", -130);
			//слухи
			AddSimpleRumour("There are rumors that our governor-General kicked you out of the residence because you managed to drown the Soleil Royal. Heh, it serves you right...", FRANCE, 5, 1);
        break;
		case "Step_10_6":
            dialog.text = "Fine, "+ GetSexPhrase("my friend", "mademoiselle") +", just great!"+
				          "Now about a topic that is very important to you - about remuneration. I managed to get an unheard-of sum out of the budget to finance your expedition - 40 thousand gold... They are yours, "+ GetSexPhrase("Baron", "Baronessa") +"!";
			link.l1 = "Excellent, Monsieur Governor-General. It's much better already!";
            link.l1.go = "Step_10_7";
        break;
		case "Step_10_7":
            dialog.text = "I am very glad that you are satisfied... Well, I dare not detain you any longer, I ask you to start preparing for another case. Get your squadron in order and be with me in about a month, "+ GetSexPhrase("Baron", "Baronessa") +".";
			link.l1 = "All right, Monsieur Governor-General, I will be there on time.";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 40000);
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "30";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
			CloseQuestHeader("Fra_Line_10_OccupySantoDomingo");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 330);
			AddCharacterExpToSkill(pchar, "Fortune", 360);
			AddCharacterExpToSkill(pchar, "Accuracy", 320);
			AddCharacterExpToSkill(pchar, "Grappling", 350);
			AddCharacterExpToSkill(pchar, "Defence", 350);
			//слухи
			AddSimpleRumour("They say that you have captured Santo Domingo! Great job, Captain, just great!", FRANCE, 5, 1);
        break;
        //********************** Квест №11. Захват Санта-Каталины ************************
		case "Step_11_1":
            dialog.text = "That's right, "+ GetSexPhrase("sir", "miss") +".";
			link.l1 = "Understood... And which city will become French after a while?";
            link.l1.go = "Step_11_2";
        break;
		case "Step_11_2":
            dialog.text = "Santa Catalina, on the Main. This city controls the pearl fisheries on the west coast of the New World. The French government believes that pearl mining will be very useful for us now...";
			link.l1 = "Absolutely agree with the French government. I'm ready to perform this operation. I'm starting immediately.";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr11OccupySC_toSantaCatalina";
            AddQuestRecord("Fra_Line_11_OccupySantaCatalina", "1");
			characters[GetCharacterIndex("SantaCatalina_Mayor")].dialog.captureNode = "FraLine11Quest_OccupySC"; //капитулянтская нода мэра
        break;
		case "Step_11_3":
            dialog.text = "Devil, this is very, very bad. The loss of this ship makes it impossible for us to cooperate further.";
			link.l1 = "Is he really that dear to you?";
            link.l1.go = "Step_11_4";
        break;
		case "Step_11_4":
            dialog.text = "It's not even about me, the Soleil Royal is the pride of the Royal French Navy. This masterpiece of shipbuilding was entrusted to you, relying on your abilities as a naval commander. You have not justified the high trust, so I have to refuse you further cooperation.";
			link.l1 = "Well, so be it. I was also pretty tired of tasks that were completely unfunded. Good-bye, sir.";
            link.l1.go = "Step_11_2";
			CloseQuestHeader("Fra_Line_11_OccupySantaCatalina");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // Конец линейки
			DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //снятия перка квестового десанта
			AddCharacterExpToSkill(pchar, "Repair", -550);
			AddCharacterExpToSkill(pchar, "Pistol", -530);
			AddCharacterExpToSkill(pchar, "Fortune", -560);
			AddCharacterExpToSkill(pchar, "Accuracy", -520);
			AddCharacterExpToSkill(pchar, "Grappling", -550);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			//слухи
			AddSimpleRumour("There are rumors that our governor-General kicked you out of the residence because you managed to sink the Soleil Royal. Heh, it serves you right...", FRANCE, 5, 1);
        break;
		case "Step_11_5":
            dialog.text = "Excellent! You have once again proved that the trust placed in you is completely justified.";
			link.l1 = "Monsieur Governor-General, how about financing the operation?";
            link.l1.go = "Step_11_6";
        break;
		case "Step_11_6":
            dialog.text = "Any more questions?";
			link.l1 = "I wanted to discuss the issue of my participation in the development of the pearl fishery, monsieur...";
            link.l1.go = "Step_11_7";
        break;
		case "Step_11_7":
            dialog.text = "This is impossible, "+ GetSexPhrase("sir", "miss") +". This issue is under the control of Jean-Baptiste Colbert, the Prime Minister of France! "+ GetSexPhrase("Baron", "Baronessa") +", it is not good to make money at a time when France is exerting super-strength in this war.";
			link.l1 = "Hmm, perhaps you are right, sir...";
            link.l1.go = "Step_11_8";
        break;
		case "Step_11_8":
            dialog.text = "Well, I am sincerely glad that we understand each other well. "+ GetSexPhrase("Baron", "Baronessa") +", I dare not detain you now, I ask you to put your squadron in order and be ready to new exploits for the benefit of France and our great Sun King!";
			link.l1 = "Monsieur Governor-General, I will comply with your request. See you later.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "10";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
			DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //снятия перка квестового десанта
			CloseQuestHeader("Fra_Line_11_OccupySantaCatalina");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			//слухи
			AddSimpleRumour("There are rumors that you have captured Santa Catalina. And then they tried to get a share of the pearl developments from d'Ogeron. Heh, rolled out the lip, it's called...", FRANCE, 5, 1);
        break;
        //********************** Квест №12. Завершение линейки ************************
		case "Step_12_1":
            dialog.text = "You also contributed to this victory. In fact, it was you who ensured the decisive defeat of the Spanish forces in the Caribbean\n"+
				          "Jean-Baptiste Colbert noted your successful actions at the report in the Louvre, your name is now known to Louis XIV himself!";
			link.l1 = "I am very, very glad. Tell me, monsieur, are there any monetary incentives for the results of the war?";
            link.l1.go = "Step_12_2";
        break;
		case "Step_12_2":
            dialog.text = "I don't know anything about this. However, we can ask the Marquis Bonrepos this question. Your next task is to get to Basse Terre, in Guadeloupe, and meet the Marquis there. He's expecting you.";
			link.l1 = "Excellent, monsieur! I won't miss this chance... I'm going out immediately.";
            link.l1.go = "Step_12_3";
        break;
		case "Step_12_3":
            dialog.text = "And put the Soleil Royal in order, it should be in full combat readiness.";
			link.l1 = "All right, sir.";
            link.l1.go = "exit";
			pchar.questTemp.State = "Fr12EndWar_toBorepo";
			AddQuestRecord("Fra_Line_12_EndOfWar", "1");
			//==> маркиз Бонрепо.
            sld = GetCharacter(NPC_GenerateCharacter("Bonrepo", "huber_fra", "man", "man", 20, FRANCE, -1, false));
            sld.Dialog.Filename    = "Quest\FraLineNpc_1.c";
        	sld.name 	= "Marquis";
        	sld.lastname 	= "Bonrepo";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "BasTer_townhall", "goto", "governor1");
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
