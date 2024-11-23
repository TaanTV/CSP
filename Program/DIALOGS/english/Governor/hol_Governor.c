// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind...", "I have nothing to talk about right now.");
		    link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr2Letter_toCuracao")
			{
                dialog.text = "I'm listening to you.";
                link.l1 = "Mr. Governor General, I have been instructed to deliver a letter to you.";
                link.l1.go = "Step_F2_1";
			}
			if (pchar.questTemp.State == "Fr2Letter_NiceResult")
			{
                dialog.text = "You again? Is it the Tortuga bag again?";
                link.l1 = "Not this time, Monsieur Governor-General. I have good news for you.";
                link.l1.go = "Step_F2_4";
			}
			if (pchar.questTemp.LSC == "toTalkStuvesant")
			{
				link.l1 = "I want to ask about one person. Do not refuse the courtesy to answer me.";
				link.l1.go = "TizerFind";
			}
		break;

		case "work_1":  // работа на благо короны - линейка нации
            // сюда вход только с патентом, проверка выше
            dialog.text = LinkRandPhrase("You are in the service of the Republic of the United Provinces! I ask you to immediately begin fulfilling the assignment assigned to you!",
                                         "I will not hide that a lot depends on your successful actions. Therefore, proceed to fulfill your obligations!",
                                         "I am waiting for your report on the fulfillment of my responsible assignment, but not stupid overreactions.");
            link.l1 = RandPhraseSimple("I'm starting immediately, mynheer", "I'm already in the process of doing...");
            link.l1.go = "exit";

        	switch (pchar.questTemp.State)   // что делаем в данный момент
            {
                case "empty":   // Нет взятых квестов
                    if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
                    {
                        dialog.text = LinkRandPhrase("I don't have any responsible assignments for you at the moment. You can come to my residence later...",
                                                     "Please excuse me, I'm very busy at the moment!",
                                                     "Mind your privateering business for the time being, I don't have any assignments for you right now.");
                        link.l1 = "Okay, mynheer.";
                        link.l1.go = "exit";
                    }
                    else
                    {
						switch(pchar.questTemp.CurQuestNumber)   // Взятие квестов начиная со второго
                        {
                            case "2":
                                dialog.text = "I have a new assignment for you. It is necessary to purchase a batch of coffee, black, red and sandal prepared for Curacao in Fort Orange. Go immediately, here are the necessary papers for this, hand them over to the governor of Fort Orange.";
                                link.l1 = "Did you say to buy?";
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":
                                dialog.text = "I must inform you that we are at war with England, another trade war has begun.";
                                link.l1 = "That's how...";
                                link.l1.go = "Step_3_1";
                            break;
                            case "4":
                                if (CheckAttribute(pchar, "questTemp.GoodWormRusult"))
                                {
                                    dialog.text = "You have obtained the most important information. Madiford doesn't have the strength right now to cause us serious trouble in Curacao, but they want to destroy Fort Orange, which is right next to them in Jamaica.";
                                    link.l1 = "Yes, Mynheer, I know that.";
                                    link.l1.go = "Step_4_1";
                                }
                                else
                                {
                                    dialog.text = "You failed to properly complete the previous task. Instead of you, this task was successfully completed by other brave men. Now I'm giving you the opportunity to rehabilitate yourself. As a result of the information I received, I concluded that Madiford is currently not strong enough to cause us serious trouble in Curacao, but they want to destroy Fort Orange, which is located next to them in Jamaica.";
                                    link.l1 = "I see...";
                                    link.l1.go = "Step_4_1";
                                }
                            break;
                            case "5":
                                dialog.text = "So, the next task awaits you. It consists in the fact that you need to escort three loaded flutes to the Buccaneer settlement of La Vega to Edward Manfield.";
                                link.l1 = "I got it, mynheer.";
                                link.l1.go = "Step_5_1";
                            break;
                            case "6":
                                dialog.text = "Here you are, I've been waiting for you.";
                                link.l1 = "At your service, mynher.";
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = "I have a serious mission for you. I need to deliver a dispatch to the Governor-General of Tortuga, Bertrand d'Ogeron. This is due to our actions in the devolution war of France against Spain. This correspondence is strictly confidential, so I ask you to understand how much I trust you. This dispatch should not reach anyone except the Governor-General of Tortuga, this is a categorical requirement!";
                                link.l1 = "I got it, mynher. Everything will be executed in the proper way, namely Monsieur d'Ogeron will receive this dispatch.";
                                link.l1.go = "Step_7_1";
                            break;
                            case "8":
                                dialog.text = "I have a personal request for you. My friend, the head of the Yansenist community of Curacao, whom you brought to the island, asks to send a smart officer to him. I have no one better than your candidacy. His request is to find something he really needs. In general, Aaron will tell you everything himself, he is in his house now, visit him.";
                                link.l1 = "I got it, mynher. I'll go to him immediately.";
                                link.l1.go = "exit";
                                pchar.questTemp.State = "SeekBible_toAaron";
                                AddQuestRecord("Hol_Line_8_SeekBible", "1");
								AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("","a"));
                                SaveCurrentQuestDateParam("questTemp");
								sld = characterFromId("Chumakeiro");
								LAi_SetStayTypeNoGroup(sld);
                                ChangeCharacterAddressGroup(sld, "Villemstad_houseS3", "goto", "goto1");
                            break;
                            case "9":
                                dialog.text = "We are experiencing serious difficulties with the construction of large-displacement battleships in our European shipyards - shallow harbors, you know... I was thinking about this sad fact yesterday, and then a brilliant idea came to my mind!";
                                link.l1 = "What is it, Mynheer?";
                                link.l1.go = "Step_9_1";
                            break;
                            case "10":
                                dialog.text = "Damn it, " + pchar.name + "You were right when you suggested that I leave the squadron you captured here in the Caribbean...";
                                link.l1 = "What happened, Mynheer?";
                                link.l1.go = "Step_10_1";
                            break;
                            case "11":
                                dialog.text = "Here you are! I've been waiting for your appearance at the residence.";
                                link.l1 = "What happened, Mynheer?";
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = "I hasten to inform you that a Spanish city has been identified that will be attacked. This is Maracaibo. The residents of the city will have to swear allegiance to the Republic of the United Provinces!";
                                link.l1 = "Good choice, Mynheer.";
                                link.l1.go = "Step_12_1";
                            break;
                        }
                    }
                break;

                case "":           // Квест №1, доставка главы янсенистов мистера Аарона.
                    dialog.text = "Well, I have a very important task for you for the city. I think you'll be able to handle it\n"+
                                  "The thing is this: quite a lot of Protestants from Europe have recently begun to arrive in Curacao, mainly from Flanders and Burgundy, where the Inquisition is rampant. Recently, supporters of the teachings of Yansenius also arrived to us. In order to lead the Jansenist community, the influential Jansenist Aaron Mendes Chumaqueiro arrived on San Martin by French cruise ship from Holland\n"+
                                  "This is a major merchant, an old acquaintance of mine and a great friend. Head to Marigot and bring him to me, the local Jansenist community is in great need of him.";
                    link.l1 = "Let me ask you, who are the Jansenists?";
                    link.l1.go = "Step_1_1";
                break;
                case "SeekChumakeiro_GoToVillemstad":
                    dialog.text = "Well, Aaron has already told me everything. Good job, "+ GetSexPhrase("mynheer","mistress") +". Come to me after a while, it seems to me that I will continue to use your services.";
                    link.l1 = "Okay, mynheer.";
                    link.l1.go = "exit";
                    pchar.questTemp.State = "empty";
                    SaveCurrentQuestDateParam("questTemp");
                    pchar.questTemp.CurQuestNumber = "2";
                    pchar.questTemp.Waiting_time = "7";
                    CloseQuestHeader("Hol_Line_1_Chumakeiro");
					AddTitleNextRate(sti(NPChar.nation), 1);
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(pchar, "Pistol", 150);
					AddCharacterExpToSkill(pchar, "Grappling", 120);
					ChangeCharacterReputation(pchar, 5);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
					//слухи
					AddSimpleRumour("You know, our Governor-General, Stuyvesant, hired the captain " + GetMainCharacterNameGen() + " to bring his friend from Marigot here to Willemstad. And you know, the assignment was successfully completed.", HOLLAND, 5, 1);
                break;
                case "TakeFoodCuracao_toOrangeStore":
                    dialog.text = "So, Captain, what did you come to Curacao with?";
                    link.l1 = "I am fulfilling your assignment for the delivery of cargo from Fort Orange, Mynheer.";
                    if (GetQuestPastDayParam("questTemp") > 60)
                    {
                        dialog.text = "I asked you to deliver the entire batch to me within 60 days. You failed....";
                        link.l1 = "That's right, I didn't have time, there were serious problems with the wind...";
                    }
                    link.l1.go = "Step_2_5";
                break;
                case "WormEnglPlans_SurrenderWorkMorgan":
                    dialog.text = "Here you are, finally! Tell me immediately what you have learned.";
                    link.l1 = "Mansfield knows nothing about Madiford's plans. But I found out that Madiford was trying to get the corsairs to attack Curacao. Thus, it can be assumed that the order to open hostilities against the Netherlands in the Caribbean Sea was received by Madiford.";
                    link.l1.go = "Step_3_3";
                break;
                case "WormEnglPlans_SaveOfficer":
                    dialog.text = "Here you are, finally! Tell me immediately what you have found out.";
                    link.l1 = "Mansfield knows nothing about Madiford's plans. Admiral of the Corsairs Henry Morgan suggests that there is an order to attack the Dutch settlements.";
                    link.l1.go = "Step_3_3";
                break;
                case "WormEnglPlans_GoodRusultWorm":
                    dialog.text = "What did you find out?";
                    link.l1 = "Madiford is preparing an attack on Fort Orange. Preparations are underway to storm the Port Royal garrison. Madiford tried to persuade the corsairs to attack Curacao, but he failed. So Madiford does not have the strength for a larger operation than the storming of Fort Orange.";
                    link.l1.go = "Step_3_7";
                break;
                case "DefenceOrange_LateRiseOrange":
                    dialog.text = "Tell me what's wrong with Fort Orange?";
                    link.l1 = "Mynheer, I couldn't come to rescue of Fort Orange. The unfortunate inhabitants have been exterminated, Fort Orange as a Dutch settlement no longer exists...";
                    link.l1.go = "Step_4_2";
                break;
                case "DefenceOrange_DieHard":
                    dialog.text = "Tell me what's wrong with Fort Orange?";
                    link.l1 = "Mynheer, I couldn't come to rescue of Fort Orange. We fought, but the British were stronger. We had to run for our lives... Unfortunately, Fort Orange no longer exists as a Dutch settlement...";
                    link.l1.go = "Step_4_2";
                break;
                case "DefenceOrange_LandingDestroyed":
                    dialog.text = "Tell me what's wrong with Fort Orange?";
                    link.l1 = "Mynheer, the task is completed. All the ships and landing units of the British were destroyed while trying to break into the city. He is no longer in danger.";
                    link.l1.go = "Step_4_4";
                break;
                case "DefenceOrange_SquadronDestroyed":
                    dialog.text = "Tell me what's wrong with Fort Orange?";
                    link.l1 = "Mynheer, I managed to destroy the British ships at sea. But unfortunately I couldn't resist the British ground forces. Fort Orange has been destroyed...";
                    link.l1.go = "Step_4_5";
                break;
                case "ThreeFleutes_DieHard":
                    dialog.text = "I have already been informed that you could not save the flutes entrusted to you. Moreover, you have escaped from the battlefield!";
                    link.l1 = "Mynheer, off the coast of Hispaniola, I was attacked by a whole squadron of Spaniards! The forces were too unequal...";
                    link.l1.go = "Step_5_3";
                break;
                case "ThreeFleutes_AllFleuts":
                    dialog.text = "Report what happened to you?";
                    link.l1 = "Mynheer, off the coast of Hispaniola, I was attacked by a whole squadron of Spaniards! But I managed to save the ships entrusted to me.";
                    link.l1.go = "Step_5_4";
                break;
                case "ThreeFleutes_LostFleuts":
                    dialog.text = "I have already been informed that you could not save the flutes entrusted to you. This is very bad.";
                    link.l1 = "Mynheer, I was attacked by a whole squadron of Spaniards off the coast of Hispaniola!";
                    link.l1.go = "Step_5_9";
                break;
                case "RevengeMansfield_FromMorganWithResult":
                    dialog.text = "So, glad to see you. What news are you going to tell me?";
                    link.l1 = "Well, what can I say? You can't envy the city of Santiago and its governor!";
                    link.l1.go = "Step_6_2";
                break;
                case "DelivLettTortuga_NotFoundLetter":
                    dialog.text = "Report the results of your mission.";
                    link.l1 = "I have successfully delivered your dispatch to d'Ogeron.";
                    link.l1.go = "Step_7_2";
                break;
                case "DelivLettTortuga_LetterFound":
                    dialog.text = "Report the results of your mission.";
                    link.l1 = "I have successfully delivered your dispatch to d'Ogeron.";
                    link.l1.go = "Step_7_8";
                break;
                case "DelivLettTortuga_WaitingNews":
                    if (GetQuestPastDayParam("questTemp") > 30)
                    {
                        dialog.text = "Well, we're all very lucky. D'Ogeron, the cunning fox, guessed to encrypt the letter in a way known to me. Therefore, the Spaniards will not be able to prove anything directly.";
                        link.l1 = "Glory to the Lord!";
                        link.l1.go = "Step_7_20";
                    }
                    else
                    {
                        dialog.text = "I haven't heard from d yet'Augeron. Come back later.";
                        link.l1 = "Okay, mynheer.";
                        link.l1.go = "exit";
                    }
                break;
                case "SeekBible_BadResult":
                    dialog.text = "Chumakeiro informed me that you failed to complete his assignment.";
                    link.l1 = "In general, yes. I did everything I could.";
                    link.l1.go = "Step_8_1";
                break;
                case "SeekBible_GoodResult":
                    dialog.text = ""+ GetSexPhrase("My friend","Mistress") +", Aaron and his community are in religious ecstasy. He told me that you managed to do something very important for him. Tell me, what is it?";
                    link.l1 = "I'm searching one lost item for him. A book, an ancient Christian treatise.";
                    link.l1.go = "Step_8_2";
                break;
                case "TakeThreeShips_toAbordage":
                    dialog.text = "So, what do you tell me about your assignment? How is the capture of the ships going?";
                    tempQty = 0;
                    int money = 0;
                    for (i=1; i<=COMPANION_MAX; i++)
                	{
                        chComp = GetCompanionIndex(pchar,i);
                        if(chComp != -1)
                		{
                			sld = GetCharacter(chComp);
                    		iShip = sti(sld.ship.type);
                    		iBaseType = sti(RealShips[iShip].basetype);
                            if (iBaseType == SHIP_SANTAANNA || iBaseType == SHIP_OCEAN || iBaseType == SHIP_MANOWAR || iBaseType == SHIP_SANFELIPE || iBaseType == SHIP_VICTORY || iBaseType == SHIP_SOLEY)
                            {
                                tempQty++;
                                RemoveCharacterCompanion(pchar, sld);
                                AddPassenger(pchar, sld, false);
                               money += 75000;
                            }
                        }
                    }
                    if (money > 0) AddMoneyToCharacter(pchar, money);
                    if (tempQty == 0)
                    {
                        link.l1 = "So far, I have not managed to capture anything worthy of your attention. But I'm working on it, wait, Mynheer...";
                        link.l1.go = "exit";
                    }
                    else
                    {
                        if (sti(pchar.questTemp.QtyShips) > tempQty)
                        {
                            if (tempQty > 1)
                            {
                                link.l1 = "Not bad, mynheer. I'm ready to hand over " + tempQty +  " ships.";
                            }
                            else
                            {
                                link.l1 = "Not bad, mynheer. I'm ready to hand over one ship.";
                            }
                            link.l1.go = "Step_9_5";
                            pchar.questTemp.QtyShips = sti(pchar.questTemp.QtyShips) - tempQty;
                            AddQuestRecord("Hol_Line_9_TakeThreeShips", "2");
                            AddQuestUserData("Hol_Line_9_TakeThreeShips", "QtyTook", tempQty);
                            AddQuestUserData("Hol_Line_9_TakeThreeShips", "QtyElse", pchar.questTemp.QtyShips);
                        }
                        else
                        {
                            AddQuestRecord("Hol_Line_9_TakeThreeShips", "3");
                            link.l1 = "Great, mynheer. The task has been completed completely.";
                            link.l1.go = "Step_9_6";
                            DeleteAttribute(pchar, "questTemp.QtyShips");
                        }
                     }
                break;
                case "SpaAttackCuracao_GoodWork":
                    dialog.text = "I saw everything! It was just great!";
                    link.l1 = "Thank you, my participation in the battle was quite modest...";
                    link.l1.go = "Step_10_3";
                break;
                case "SpaAttackSentMartin_Late":
                    dialog.text = "Report, did you manage to protect San Martin?";
                    link.l1 = "Mynheer, I did it too late to do everything in time... Marigo is now a Spanish city.";
                    link.l1.go = "Step_11_5";
                break;
                case "SpaAttackSentMartin_GoodWork":
                    dialog.text = "Report, did you manage to protect San Martin?";
                    link.l1 = "I managed, mynheer. The siege of the Spanish squadron from the city of San Martin has been lifted. The Spaniards are defeated.";
                    link.l1.go = "Step_11_8";
                break;
                case "OccupyMaracaibo_toWeWon":
                    dialog.text = "I already know, "+ GetSexPhrase("my friend","" + pchar.name + "") +", we have already reported on your brilliant victory!";
                    link.l1 = "Mynheer, I managed to capture Maracaibo. It's a Dutch colony now.";
                    link.l1.go = "Step_12_3";
                break;
                case "QuestLineBreake":
                    dialog.text = "I don't deal with people breaking their word. I have nothing more to say to you.";
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
                case "EndOfQuestLine":
                    dialog.text = "Act independently in the interests of the Netherlands, I count on your common sense.";
                    link.l1 = "Okay, mynheer.";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
            }
        break;
        //********************** Квест №1, доставка главы янсенистов мистера Аарона. ************************
        case "Step_1_1":
            dialog.text = "Christian religious movement, if you are interested\n"+
                          "It began with the writing by Jansenius in 1640 of a theological treatise on Augustine. The Jesuits emphasize the closeness of the Jansenist doctrine with Protestant dogmas and persecute the followers of this religious trend. Louis XIV also outlawed the Jansenists\n"+
                          "The establishment of the community here, under my care, is a very important step for the development of the Dutch colonies in the Caribbean. The fact is that most of them are nobles, officers, bourgeois and large merchants. At least such people will not be superfluous here\n"+
                          "Well, if you are ready, then please proceed immediately to the task at hand.";
            link.l1 = "I'm ready, mynheer. Expect me back soon.";
            link.l1.go = "Step_1_2";
            link.l2 = "Sorry, but I'm very busy at the moment. Later I'm ready to fulfill this assignment of yours.";
            link.l2.go = "exit";
        break;
        case "Step_1_2":
            SaveCurrentQuestDateParam("questTemp");
    		// остальные линейки в сад -->
    		pchar.questTemp.NationQuest = HOLLAND;
    		// остальные линейки в сад <--
    		pchar.questTemp.State = "SeekChumakeiro_ToAaronHouse";
            sld = GetCharacter(NPC_GenerateCharacter("Chumakeiro", "usurer_4", "man", "man", 10, HOLLAND, -1, false));
        	sld.name 	= "Aaron Mendes";
        	sld.lastname = "Chumakeiro";
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
			sld.greeting = "Gr_padre";
        	LAi_SetHuberStayType(sld);
        	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
            ChangeCharacterAddressGroup(sld, "Marigo_RoomHouseF1", "goto", "goto1");
            AddQuestRecord("Hol_Line_1_Chumakeiro", "1");
			AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex", GetSexPhrase("","a"));
            Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition.l1 = "location";
            Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition.l1.location = "Marigo_houseF1";
            Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition = "SeekChumakeiro_intoMarigoHouse";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        //********************** Квест №2, закупка и доставка товара из Форт Оранж. ************************
        case "Step_2_1":
            dialog.text = "Exactly to purchase. Fort Orange gives us very good prices for the purchase of this batch of goods. As soon as you present my credentials to the Governor of Fort Orange, you will receive discounted prices\n"+
                          "The batch prepared for you is 400 units of each item. The prices for you will be about ten times cheaper than the current ones\n"+
                          "According to my calculations, I am allocating 17700 gold to you for purchase. Please receive it.";
            link.l1 = "If you calculated this operation, can you tell me how much this batch is in hundredweight? I need to plan the transportation.";
            link.l1.go = "Step_2_2";
        break;
        case "Step_2_2":
            dialog.text = "Of course, I'll tell you. In total, the weight of the entire batch is 5,600 quintals.";
            link.l1 = "Hmm, a lot... Mynheer, I am "+ GetSexPhrase("free captain","not a trading captain") +", and I do not really like these cargo transportation operations...";
            link.l1.go = "Step_2_3";
        break;
        case "Step_2_3":
            dialog.text = "That's because you are, so to speak, "+ GetSexPhrase("free captain","and not a trading captain") +", I am attracting you to fulfill this assignment. I need this cargo safe and sound here, and it seems to me that it is "+ GetSexPhrase("free captain","privateer") +" will be able to ensure its integrity and safety\n"+
                          "Spaniards are sneaking around, the British do not show friendly feelings towards us, there are plenty of pirates around... So I ask you to understand me correctly..\n"+
                          "I will not accept refusal from you to fulfill this assignment. Get started! And remember that I need the whole shipment, all 5,600 quintals, here in Willemstad, no later than in two months.";
            link.l1 = "Hmm, yeah... All right, Mynheer, I'll do it. You leave me no choice.";
            link.l1.go = "Step_2_4";
        break;
        case "Step_2_4":
            dialog.text = "I am very glad that you agreed. Well, I'm waiting for you with a load.";
            link.l1 = "See you later, Mynheer.";
            link.l1.go = "exit";
            pchar.questTemp.State = "TakeFoodCuracao_toOrangeMayor";
            AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "1");
            ChangeItemDescribe("Trust", "itmdescr_Trust_HolLineQ2");
            GiveItem2Character(pchar,"Trust");
            AddMoneyToCharacter(pchar, 17700);
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.EbonyQtyElseNeed = 400;
            pchar.questTemp.CoffeeQtyElseNeed = 400;
            pchar.questTemp.MahoganyQtyElseNeed = 400;
            pchar.questTemp.SandalQtyElseNeed = 400;
        break;
        case "Step_2_5":
            if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) pchar.questTemp.EbonyQty = pchar.Ship.Cargo.Goods.Ebony;
            if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) pchar.questTemp.CoffeeQty = pchar.Ship.Cargo.Goods.Coffee;
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) pchar.questTemp.MahoganyQty = pchar.Ship.Cargo.Goods.Mahogany;
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) pchar.questTemp.SandalQty = pchar.Ship.Cargo.Goods.Sandal;
            for (i=1; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar,i);
                if(chComp != -1)
        		{
        			sld = GetCharacter(chComp);
                    if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) pchar.questTemp.EbonyQty = sti(pchar.questTemp.EbonyQty) + sti(sld.Ship.Cargo.Goods.Ebony);
                    if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) pchar.questTemp.CoffeeQty = sti(pchar.questTemp.CoffeeQty) + sti(sld.Ship.Cargo.Goods.Coffee);
                    if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) pchar.questTemp.MahoganyQty = sti(pchar.questTemp.MahoganyQty) + sti(sld.Ship.Cargo.Goods.Mahogany);
                    if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) pchar.questTemp.SandalQty = sti(pchar.questTemp.SandalQty) + sti(sld.Ship.Cargo.Goods.Sandal);
                }
            }
            tempStr = "Mynheer, I brought the following items:\n";
            if (CheckAttribute(pchar, "questTemp.EbonyQty"))
            {
                if (sti(pchar.questTemp.EbonyQty > 0)) tempStr = tempStr + " Ebony - " + pchar.questTemp.EbonyQty + " pieces.";
            }
            if (CheckAttribute(pchar, "questTemp.CoffeeQty"))
            {
                if (sti(pchar.questTemp.CoffeeQty > 0)) tempStr = tempStr + " Coffee - " + pchar.questTemp.CoffeeQty + " pieces.";
            }
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed"))
            {
                if (sti(pchar.questTemp.MahoganyQty > 0)) tempStr = tempStr + " Mahogany - " + pchar.questTemp.MahoganyQty + " pieces.";
            }
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
            {
                if (sti(pchar.questTemp.SandalQty > 0)) tempStr = tempStr + " Sandal - " + pchar.questTemp.SandalQty + " pieces.";
            }
            dialog.text = "Tell me how much and what you brought from Fort Orange.";
            link.l1 = tempStr;
            link.l1.go = "Step_2_6";
            if (tempStr == "Mynheer, I brought the following items:\n")
            {
                link.l1 = "Mynheer, I'm in the process of doing it. So far, nothing new has been delivered, please excuse me...";
                link.l1.go = "exit";
                DeleteAttribute(pchar, "questTemp.EbonyQty");
                DeleteAttribute(pchar, "questTemp.CoffeeQty");
                DeleteAttribute(pchar, "questTemp.MahoganyQty");
                DeleteAttribute(pchar, "questTemp.SandalQty");
            }
        break;
        case "Step_2_6":
            tempStr = "So, let's summarize.";
            if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed"))
            {
                HolLine2_NullGoods();
                if (sti(pchar.questTemp.EbonyQty) >= sti(pchar.questTemp.EbonyQtyElseNeed))
                {
                    tempStr = tempStr + "You've made a complete delivery of ebony.";
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_EBONY, sti(pchar.questTemp.EbonyQty)-sti(pchar.questTemp.EbonyQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.EbonyQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.EbonyQty > 0))
                    {
                        tempStr = tempStr + " I accept " + pchar.questTemp.EbonyQty + " units of ebony.";
                        pchar.questTemp.EbonyQtyElseNeed = sti(pchar.questTemp.EbonyQtyElseNeed) - sti(pchar.questTemp.EbonyQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed"))
            {
                if (sti(pchar.questTemp.CoffeeQty) >= sti(pchar.questTemp.CoffeeQtyElseNeed))
                {
                    tempStr = tempStr + "You bet the whole lot of coffee.";
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_COFFEE, sti(pchar.questTemp.CoffeeQty)-sti(pchar.questTemp.CoffeeQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.CoffeeQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.CoffeeQty > 0))
                    {
                        tempStr = tempStr + " I accept " + pchar.questTemp.CoffeeQty + " units of coffee.";
                        pchar.questTemp.CoffeeQtyElseNeed = sti(pchar.questTemp.CoffeeQtyElseNeed) - sti(pchar.questTemp.CoffeeQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed"))
            {
                if (sti(pchar.questTemp.MahoganyQty) >= sti(pchar.questTemp.MahoganyQtyElseNeed))
                {
                    tempStr = tempStr + "You delivered the whole batch of mahogany.";
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_MAHOGANY, sti(pchar.questTemp.MahoganyQty)-sti(pchar.questTemp.MahoganyQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.MahoganyQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.MahoganyQty > 0))
                    {
                        tempStr = tempStr + " I accept " + pchar.questTemp.MahoganyQty + " mahogany units.";
                        pchar.questTemp.MahoganyQtyElseNeed = sti(pchar.questTemp.MahoganyQtyElseNeed) - sti(pchar.questTemp.MahoganyQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
            {
                if (sti(pchar.questTemp.SandalQty) >= sti(pchar.questTemp.SandalQtyElseNeed))
                {
                    tempStr = tempStr + "You managed to get the whole lot of sandal.";
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_SANDAL, sti(pchar.questTemp.SandalQty)-sti(pchar.questTemp.SandalQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.SandalQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.SandalQty > 0))
                    {
                        tempStr = tempStr + " I accept " + pchar.questTemp.SandalQty + " pieces of sandal.";
                        pchar.questTemp.SandalQtyElseNeed = sti(pchar.questTemp.SandalQtyElseNeed) - sti(pchar.questTemp.SandalQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            DeleteAttribute(pchar, "questTemp.EbonyQty");
            DeleteAttribute(pchar, "questTemp.CoffeeQty");
            DeleteAttribute(pchar, "questTemp.MahoganyQty");
            DeleteAttribute(pchar, "questTemp.SandalQty");
            dialog.text = tempStr;
            link.l1 = "Very good, Mynheer.";
            link.l1.go = "Step_2_7";
        break;
        case "Step_2_7":
            tempStr = "";
            if (!CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed") && !CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed") && !CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed") && !CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
            {
                if (GetQuestPastDayParam("questTemp") > 60)
                {
                    dialog.text = "You have completed the delivery in full, that's good. However, my request to you included the delivery of the goods within two months. You couldn't do that.";
                    link.l1 = "Mynheer, the task turned out to be difficult, I did not have enough roomy ships to speed up transportation...";
                    link.l1.go = "Step_2_8";
                }
                else
                {
                    dialog.text = "You have completed the delivery in full. Moreover, you completed it on time! I would like to inform you that receiving this cargo on time was extremely important for Curacao.";
                    link.l1 = "I'm glad that I complete the task in the best possible way.";
                    link.l1.go = "Step_2_11";
                }
            }
            else
            {
                dialog.text = "I ask you to finish the job you started. I need the entire shipment from Fort Orange, down to the last hundredweight.";
                link.l1 = "Okay, Mynheer, everything will be delivered to Willemstad.";
                link.l1.go = "exit";
                AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "3");
                if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "EbonyQtyElseNeed", pchar.questTemp.EbonyQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "EbonyQtyElseNeed", "completed");
                if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "CoffeeQtyElseNeed", pchar.questTemp.CoffeeQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "CoffeeQtyElseNeed", "completed");
                if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "MahoganyQtyElseNeed", pchar.questTemp.MahoganyQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "MahoganyQtyElseNeed", "completed");
                if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "SandalQtyElseNeed", pchar.questTemp.SandalQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "SandalQtyElseNeed", "completed");
            }
        break;
        case "Step_2_8":
            dialog.text = "I understand, but you must understand that I am guided by global plans and I just need to follow my instructions clearly.\n"+
                          "Due to the above reason, the amount of remuneration for conducting this trading operation is greatly reduced\n"+
                          "I could give you no more than 15,000 gold.";
            link.l1 = "Hmm, cough, mmm... Well, thanks for that...";
            link.l1.go = "Step_2_9";
        break;
        case "Step_2_9":
            dialog.text = "Always at your service, Captain. Come to me from time to time, maybe I can find more work for you.";
            link.l1 = "Okay, mynheer.";
            link.l1.go = "Step_2_10";
            AddMoneyToCharacter(pchar, 15000);
            pchar.questTemp.Waiting_time = "30";
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour("Did you hear that captain " + GetFullName(pchar) + " took the trading operation - the delivery of food from Fort Orange. Captain completed the task, but did not meet the deadlines.", HOLLAND, 5, 1);
        break;
        case "Step_2_10":
            AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "4");
            CloseQuestHeader("Hol_Line_2_TakeFoodCuracao");
			DeleteAttribute(pchar, "GenQuest.HL2_AgainDiscount");  //сносим дисконтные цены
        	pchar.GenQuest.StoreGoods.StoreIdx = FortOrange_STORE; //восстанавливаем старые цены и кол-во
        	pchar.GenQuest.StoreGoods.HL2_QtyPriceIsBack = true;
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        case "Step_2_11":
            dialog.text = "So, the amount of remuneration for the successful completion of this order is 75,000 gold. Agree that this is a worthy reward.";
            link.l1 = "Undoubtedly, mynheer...";
            link.l1.go = "Step_2_12";
        break;
        case "Step_2_12":
            dialog.text = "That's great! And now I ask you to leave me - business... Come visit me in a few days, maybe a few.";
            link.l1 = "Okay, Mynheer, I'll try.";
            link.l1.go = "Step_2_10";
            AddMoneyToCharacter(pchar, 75000);
            pchar.questTemp.Waiting_time = "2";
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			//слухи
			AddSimpleRumour("Did you hear that, Captain " + GetFullName(pchar) + "took for the trading operation - the delivery of food from Fort Orange. Captain completed it, and even did it fast!", HOLLAND, 5, 1);
        break;
        //********************** Квест №3, Узнать о планах англичан в связи с торговой войной ************************
        case "Step_3_1":
            dialog.text = "The epicenter of the war is in the coastal waters of Europe and in the Indian Ocean, but here, in the Caribbean, this war will have its impact\n"+
                          "I need information about the plans of the British, accurate and absolutely reliable. There is a Buccaneer settlement on the island of Hispaniola, where mainly the French live, but there are also a lot of Dutch. So, the head of the Buccaneers is Edward Mansfield\n"+
                          "His name has been changed to English, his real name is Edward Mansvelt, he is Dutch. Edward is a confidant of the English Governor-General, Sir Thomas Madiford, in matters of plundering the Spaniards.";
            link.l1 = "Hmm, interesting...";
            link.l1.go = "Step_3_2";
        break;
        case "Step_3_2":
            dialog.text = "Your task is as follows: deliver this letter to Mansfield, the letter asks for help. Persuade him to tell you what he knows about the British plans. There is no doubt that they are attacking us. We need to know what they're going to do.";
            link.l1 = "I got it, mynheer. I'm getting started.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
    		pchar.questTemp.State = "WormEnglPlans_toMansfield";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "1");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_HolLineQ3");
            GiveItem2Character(pchar,"letter_1");
            QuestSetCurrentNode("Edward Mansfield", "HolLine3_WormEngPlans");
        break;
        case "Step_3_3":
            dialog.text = "Report further.";
            link.l1 = "Actually, there is nothing more to report. That's all.";
            link.l1.go = "Step_3_4";
        break;
        case "Step_3_4":
            dialog.text = "It turns out that we have only assumptions and no specifics. Have you learned anything about the specific plans of the British?";
            link.l1 = "No, mynheer. I haven't been able to find out anything specific.";
            link.l1.go = "Step_3_5";
        break;
        case "Step_3_5":
            dialog.text = "You did not complete the task. I will have to involve other, more agile people in this task. And now I have only lost time. I am very disappointed in you.";
            link.l1 = "Mynheer, please give me the opportunity to rehabilitate myself.";
            link.l1.go = "Step_3_6";
        break;
        case "Step_3_6":
            dialog.text = "Not in this case - too much time has been lost. Well, come to me from time to time, maybe I can find a suitable case for you.";
            link.l1 = "Thank you, Mynheer.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "5");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex1", GetSexPhrase("boy","girl"));
            CloseQuestHeader("Hol_Line_3_WormEnglishPlans");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			//слухи
			AddSimpleRumour("Rumor has it that the captain " + GetFullName(pchar) + " failed a certain secret assignment of Stuyvesant related to big politics...", HOLLAND, 5, 1);
        break;
        case "Step_3_7":
            dialog.text = "Great! Now I know everything I need to know. Come to me in a couple of days, I will make a decision on the response to this threat from the British... You've done a good job, your reward is 50,000.";
            link.l1 = "Thank you, Mynheer.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_3_WormEnglishPlans");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "3";
            pchar.questTemp.GoodWormRusult = true;
            AddMoneyToCharacter(pchar, 50000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			//слухи
			AddSimpleRumour("Rumor has it that it is the captain " + GetFullName(pchar) + " completed task to learn about the plans of the British in the new war.", HOLLAND, 5, 1);
        break;
        //********************** Квест №4, Защитить Форт Оранж ************************
        case "Step_4_1":
            dialog.text = "Go to Fort Orange immediately, you must intercept the English expedition in time, otherwise our settlement is over, they will destroy the city and capture everyone. Go right now, you must understand that a lot depends on your promptness right now.";
            if (CheckAttribute(pchar, "questTemp.GoodWormRusult"))
            {
                link.l1 = "I got it, mynheer. I'm starting immediately.";
            }
            else
            {
                link.l1 = "I understand, mynheer, thank you for your trust. Be sure - this time I will not let you down! I'm starting immediately.";
            }
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.GoodWormRusult");
            AddQuestRecord("Hol_Line_4_DefenceOrange", "1");
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex", GetSexPhrase("","a"));
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "DefenceOrange_toFortOrange";
            Pchar.quest.DefenceOrange_FightNearJamaica.win_condition.l1 = "location";
            Pchar.quest.DefenceOrange_FightNearJamaica.win_condition.l1.location = "Jamaica";
            Pchar.quest.DefenceOrange_FightNearJamaica.win_condition = "DefenceOrange_FightNearJamaica";
			locations[FindLocation("FortOrange_port")].DisableEncounters = true;
        break;
        case "Step_4_2":
            dialog.text = "Damn it! We have failed to protect the citizens of the Republic of the United Provinces from the bloodthirsty British. This is very bad, our already modest presence in the Caribbean region is now completely weakened.";
            link.l1 = "I'm sorry, I did everything I could...";
            link.l1.go = "Step_4_3";
        break;
        case "Step_4_3":
            dialog.text = "Well, nevertheless, I ask you to look me up from time to time. I may have something to do for you.";
            link.l1 = "Okay, mynheer. I will definitely visit you.";
            link.l1.go = "exit";
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");
			//<-- огонь и пламень
			DeleteAttribute(&locations[FindLocation("FortOrange_port")], "DisableEncounters"); //энкаутеры вернём
            CloseQuestHeader("Hol_Line_4_DefenceOrange");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour("They say that they failed to protect the unfortunate inhabitants of Fort Orange from the British. Oh, it's a pity...", HOLLAND, 5, 1);
        break;
        case "Step_4_4":
            dialog.text = "Great! I am sincerely glad that it was you who managed to prove yourself in such a dangerous situation. Your reward for the work done is 100,000 coins. Besides, I'm asking you to come back a little later, I'll have another assignment for you.";
            link.l1 = "Okay, mynheer. I will definitely show up at your residence no later than in a month.";
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
            AddMoneyToCharacter(pchar, 100000);
            CloseQuestHeader("Hol_Line_4_DefenceOrange");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "5";
            //==> на всякий случай дублируем снятие восторгов.
            QuestSetCurrentNode("FortOrange_Mayor", "First time");
            QuestSetCurrentNode("FortOrange_waitress", "First time");
            QuestSetCurrentNode("FortOrange_tavernkeeper", "First time");
            QuestSetCurrentNode("FortOrange_trader", "First time");
			DeleteAttribute(&locations[FindLocation("FortOrange_port")], "DisableEncounters"); //энкаутеры вернём
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			//слухи
			AddSimpleRumour("They say that it was you who protected the residents of Fort Orange from the British. Let me express my admiration to you!", HOLLAND, 5, 1);
        break;
        case "Step_4_5":
            dialog.text = "Damn it! You've done half the job, and you're just a little short of saving the unfortunate residents of Fort Orange!";
            link.l1 = "That's right, Mynheer. I have no strength left for a land attack. I'm sorry...";
            link.l1.go = "Step_4_6";
        break;
        case "Step_4_6":
            dialog.text = "Yes, sadly. The unfortunate people of Fort Orange.\nYou can count on me to keep you on my assignments.";
            link.l1 = "I got it, mynheer. Thank you.";
            link.l1.go = "exit";
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");
			//<-- огонь и пламень
			DeleteAttribute(&locations[FindLocation("FortOrange_port")], "DisableEncounters"); //энкаутеры вернём
            CloseQuestHeader("Hol_Line_4_DefenceOrange");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "15";
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Grappling", -150);
			AddCharacterExpToSkill(pchar, "Defence", -150);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			Pchar.quest.DefenceOrange_FightInShore.over = "yes";
			Pchar.quest.DefenceOrange_FightInExitTown.over = "yes";
			//слухи
			AddSimpleRumour("They say that you defeated the British escara at Fort Orange, but the British were stronger in ground combat. Very, very sorry...", HOLLAND, 5, 1);
        break;

		//********************** Квест №5, Сопроводить три флейта к Мэнсфилду ************************
        case "Step_5_1":
            dialog.text = "That's not all. You are appointed squadron commander. Your competence includes the sale of cargo in the store from the filibusters and the purchase of food from them. The carcasses that they slaughter by the hundreds are of very good quality. Naturally, in order for the deal to be profitable, you must make sure that all the flutes reach the shores of Hispaniola in one piece.";
            link.l1 = "I understand everything.";
            link.l1.go = "Step_5_2";
        break;
        case "Step_5_2":
            dialog.text = "Then proceed, but without undue haste. Be careful. And remember that you have to deliver 7000 quintals of food to me on flutes. The flutes will be placed at your disposal by the portmaster.";
            link.l1 = "Okay, mynheer.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_5_ThreeFleutes", "1");
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "ThreeFleutes_toPortMan";
        break;
        case "Step_5_3":
            dialog.text = "It's hard for me to talk to a captain who turned out to be elementary"+ GetSexPhrase("oh coward","oh coward") +"! I ask you to leave me immediately, I am extremely disappointed.";
            link.l1 = "Okay, mynheer. I want to say that I am very sorry...";
            link.l1.go = "Step_5_10";
            pchar.questTemp.Waiting_time = "100";
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour("There are rumors that our governor-General kicked you out of the residence for cowardice!", HOLLAND, 5, 1);
        break;

        case "Step_5_4":
            tempQty = sti(pchar.Ship.Cargo.Goods.Food);
			for (i=1; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar,i);
                if(chComp != -1)
        		{
					sld = GetCharacter(chComp);
					iShip = sti(sld.ship.type);
                    iBaseType = sti(RealShips[iShip].basetype);
                    if (iBaseType == SHIP_FLEUT) tempQty = tempQty + sti(sld.Ship.Cargo.Goods.Food); //считаем только у флейтов
                }
            }
            tempQty = tempQty / 10; //вес от кол-ва
            dialog.text = "Excellent! I didn't expect anything else. Now tell me, have you brought food in the amount of 7000 quintals I need?";
            if (tempQty >= 7000)
            {
                link.l1 = "Yes, Mynheer, everything is fine.";
                link.l1.go = "Step_5_5";
            }
            else
            {
                link.l1 = "Mynheer, I couldn't do that. In total, I delivered food " + tempQty + "hundredweight";
                link.l1.go = "Step_5_8";
            }
        break;
        case "Step_5_5":
            dialog.text = "Well, you are not only a good warrior, but also "+ GetSexPhrase("prudent host","prudent hostess") +". I am grateful to you for the success of this very dangerous operation. Your reward is 60,000 coins, please get it. Please hand over the delivered food.";
            link.l1 = "Thank you, Mynheer.";
            link.l1.go = "Step_5_6";
            tempQty = sti(pchar.Ship.Cargo.Goods.Food);
            for (i=1; i<=3; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
        			tempQty = tempQty + sti(sld.Ship.Cargo.Goods.Food);
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
            pchar.Ship.Cargo.Goods.Food = tempQty - 70000; //в пачке - 10 шт.
            AddMoneyToCharacter(pchar, 60000);
            pchar.questTemp.Waiting_time = "2";
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
        break;
        case "Step_5_6":
            dialog.text = "Well, I'll be waiting for you at my place in a few days.";
            link.l1 = "I got it, mynheer. Before I leave, I owe to report very bad news - Edward Mansfield was killed in a Spanish attack on a Buccaneer settlement.";
            link.l1.go = "Step_5_7";
        break;
        case "Step_5_7":
            dialog.text = "Damn it, what terrible news! Well, thanks for the information, "+ GetSexPhrase("my friend","madam") +". I feel sorry for Mansfield...";
            link.l1 = "Yes, mynheer. He was a good man... For this, allow me to take my leave.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_5_ThreeFleutes");
            pchar.GenQuest.StoreGoods.HL5_QtyPriceIsBack = true;
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "6";
        break;
        case "Step_5_8":
            if (tempQty > 4000)
            {
                dialog.text = "Well, you are a good warrior, but you are not "+ GetSexPhrase("prudent host","prudent hostess") +". Nevertheless, I am grateful to you for the overall successful operation. Your reward is 20,000 coins, please get it. I'm withdrawing all food.";
                link.l1 = "Okay, mynheer.";
                AddMoneyToCharacter(pchar, 20000);
				AddTitleNextRate(sti(NPChar.nation), 3);
            }
            else
            {
                dialog.text = "Are you joking? And where is the rest of the food? Yes, I see you are a scammer! You won't get a reward.";
                link.l1 = "No, mynheer, I honestly tortured to fulfill your crazy tasks! That's all I could bring...";
            }
            link.l1.go = "Step_5_6";
            for (i=1; i<=3; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
            pchar.Ship.Cargo.Goods.Food = 0;
            pchar.questTemp.Waiting_time = "7";
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
        break;
        case "Step_5_9":
            dialog.text = "This cannot be an excuse! I have entrusted you with Dutch ships with an elementary task. You couldn't complete it. I don't want to see you!";
            link.l1 = "Okay, mynheer. I'm leaving, although I don't feel guilty about myself.";
            link.l1.go = "Step_5_10";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Grappling", -150);
			AddCharacterExpToSkill(pchar, "Defence", -150);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
            for (i=1; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar,i);
                if(chComp != -1)
        		{
        			sld = GetCharacter(chComp);
        			tempStr = sld.id;
                    if (findsubstr(tempStr, "Captain_", 0) != -1)
                    {
                        RemoveCharacterCompanion(pchar, sld);
                        sld.LifeDay = 0;
                    }
                }
            }
        break;
        case "Step_5_10":
            dialog.text = "You probably did everything you could. Maybe I can find some more work for you, but not now...";
            link.l1 = "I got it, mynheer. Before I leave, I owe to report very bad news - Edward Mansfield was killed in a Spanish attack on a Buccaneer settlement.";
            link.l1.go = "Step_5_11";
        break;
        case "Step_5_11":
            dialog.text = "Damn it, I don't have enough unpleasant news for today! Nevertheless, thanks for the information. I feel sorry for Mansfield...";
            link.l1 = "Yes, mynheer. He was a good man. For this, allow me to take my leave.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_5_ThreeFleutes");
            pchar.GenQuest.StoreGoods.HL5_QtyPriceIsBack = true;
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "6";
			//слухи
			AddSimpleRumour("They say you brought the news of Edward Mansfield's death. Pity the old man...", HOLLAND, 5, 1);
		break;
        //********************** Квест №6, узнать о планах мщения за Мэнсфилда ************************
        case "Step_6_1":
            dialog.text = "The Spanish attack on the Buccaneer settlement and the death of Mansfield will have a serious impact on the balance of power in the Caribbean region. I'm not sure if we should do anything about it\n"+
                          "It is quite possible that the Brethren will set out on its own, as it has done more than once, to avenge the death of such a respected filibuster. Therefore, we need to coordinate our actions\n"+
                          "Go to Henry Morgan and find out from him what they are going to do. If Morgan decides to involve you in a retaliation operation, then consider my permission for your participation received.";
            link.l1 = "Okay, mynheer. I am happy to participate in such a noble cause.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "1");
			AddQuestUserData("Hol_Line_6_RevengeMansfield", "sSex", GetSexPhrase("en","on"));
            pchar.questTemp.State = "RevengeMansfield_toMorgan";
            QuestSetCurrentNode("Henry Morgan", "HolLine6_fromStuvesant");
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_6_2":
            dialog.text = "So, go on.";
            link.l1 = "Morgan has assigned me to carry out a reconnaissance mission. I found out that Governor Jimenez will be in town soon. Santiago's fate is sealed.";
            link.l1.go = "Step_6_3";
        break;
        case "Step_6_3":
            dialog.text = "That's good... Did Morgan not consider it necessary to involve you in the storming of the city?";
            link.l1 = "No, the British will participate directly in the assault, for well-known reasons we cannot unite the squadrons.";
            link.l1.go = "Step_6_4";
        break;
        case "Step_6_4":
            dialog.text = "That's right. Well, as they say - for the best! The main thing is that Mansvelt will be avenged, he was a good man and a worthy son of his fatherland.";
            link.l1 = "Fully agree with you, Mynheer.";
            link.l1.go = "Step_6_5";
        break;
        case "Step_6_5":
            dialog.text = "For a successfully completed task, you can receive a reward of 20,000 coins. Please come to my residence in a while. I will have a task for you again.";
            link.l1 = "Okay, mynheer.";
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, 20000);
            CloseQuestHeader("Hol_Line_6_RevengeMansfield");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "4";
			AddCharacterExpToSkill(pchar, "FencingLight", 350);
			AddCharacterExpToSkill(pchar, "Fencing", 350);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 320);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour("There are rumors that you managed to conduct a successful reconnaissance mission against the Spaniards... Congratulations.", HOLLAND, 5, 1);
        break;
        //********************** Квест №7, Доставка письма д'Ожерону ************************
        case "Step_7_1":
            dialog.text = "In case you are attacked, this package must be destroyed immediately, regardless of the expected outcome of the battle.";
            link.l1 = "Okay, mynheer. I'm getting started.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "1");
            pchar.questTemp.State = "DelivLettTortuga_toDOjeron";
            SaveCurrentQuestDateParam("questTemp");
            ChangeItemDescribe("letter_2", "itmdescr_letter_2_HolLineQ7");
            GiveItem2Character(pchar,"letter_2");
        break;
        case "Step_7_2":
            dialog.text = "Great! I am pleased that everything has been resolved so successfully.";
            link.l1 = "Hmm, not very well, Mynheer. The fact is that Monsieur d'Ogeron wrote a reply dispatch for you.";
            link.l1.go = "Step_7_3";
        break;
        case "Step_7_3":
            dialog.text = "Why is it unsuccessful? It's all right, give it to me.";
            tempStr = "Cough, cough... The fact is that she was stolen from me right on Tortuga.";
            switch (pchar.questTemp.State.KingResult)
            {
                case "BrigNotFound":
                    tempStr = tempStr + "I chased the brig kidnappers, but couldn't return the dispatch.";
                break;
                case "BrigSunk":
                    tempStr = tempStr + "I chased the brig kidnappers and sank him, but I couldn't find the dispatch. I don't know where she is.";
                break;
                case "BrigAborded":
                    tempStr = tempStr + "I chased the brig kidnappers. From the captain of the captured brig, I learned that the Spaniards had organized the attack on me. But the dispatch itself was no longer on the brig, it fell to the Spaniards.";
                break;
                case "WarshipSunk":
                    tempStr = tempStr + "I chased the brig kidnappers. From the captain of the captured brig, I learned that the Spaniards had organized the attack on me. I've caught up with the galleon on which they left towards Santa Catalina, but the galleon was sunk in battle, the dispatch was not found. I don't know where she is at the moment.";
                break;
            }
            link.l1 = tempStr;
            link.l1.go = "Step_7_4";
        break;
        case "Step_7_4":
            dialog.text = "What?!!!";
            link.l1 = "I'm very sorry, mynheer...";
            link.l1.go = "Step_7_5";
        break;
        case "Step_7_5":
            dialog.text = "Do you even understand what you've done?!";
            link.l1 = "Approximately, mynheer...";
            link.l1.go = "Step_7_6";
        break;
        case "Step_7_6":
            dialog.text = "In general, so. I don't want to see you at my place until I find out from d'Ogeron the contents of the dispatch. And pray that there is nothing 'like that' there!";
            link.l1 = "I got it, mynheer. I apologize again...";
            link.l1.go = "Step_7_7";
        break;
        case "Step_7_7":
            dialog.text = "Get out!!!";
            link.l1 = "Okay, mynheer.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "DelivLettTortuga_WaitingNews";
            DeleteAttribute(pchar, "questTemp.State.KingResult");
            BackItemDescribe("letter_1");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			//слухи
			AddSimpleRumour("They say the captain " + GetFullName(pchar) + " was literally exposed from the residence of the Governor General...", HOLLAND, 5, 1);
        break;

        case "Step_7_20":
            dialog.text = "And this is more than true! Now I ask you to leave me, I have no business for you. Maybe something will turn up in the future, but not now.";
            link.l1 = "Okay, mynheer. Thank you, Mynheer.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_7_DelivLettTortuga");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "40";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
        break;

        case "Step_7_8":
            dialog.text = "Great! I am pleased that everything has been resolved so successfully.";
            link.l1 = "Yes, more than that. You can't even imagine-the Spaniards attacked me right on Tortuga.";
            link.l1.go = "Step_7_9";
        break;
        case "Step_7_9":
            dialog.text = "Wow! So what?";
            link.l1 = "They wanted to take away the reply dispatch from me.'Augeron.";
            link.l1.go = "Step_7_10";
        break;
        case "Step_7_10":
            dialog.text = "Do you have it?";
            link.l1 = "Of course, mynheer. It's all right, here she is!";
            link.l1.go = "Step_7_11";
        break;
        case "Step_7_11":
            dialog.text = "I am more than grateful to you for your quickness and courage. Perhaps you have prevented a political crisis in Europe.";
            link.l1 = "Monsieur d'Ogeron outlined the situation to me, I understand what it is about.";
            link.l1.go = "Step_7_12";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
        break;
        case "Step_7_12":
            dialog.text = "Well, I am pleased to announce to you that the reward for completing the mission is 150,000.";
            link.l1 = "Great, mynheer! And thank you.";
            link.l1.go = "Step_7_13";
        break;
        case "Step_7_13":
            dialog.text = "I'll be waiting for you at my place in a while. I believe that I will have more assignments for SUCH an officer!";
            link.l1 = "I will certainly appear at your place periodically.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_7_DelivLettTortuga");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "10";
            DeleteAttribute(pchar, "questTemp.State.KingResult");
            AddMoneyToCharacter(pchar, 150000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			//слухи
			AddSimpleRumour("They say that the captain " + GetFullName(pchar) + ", performing the functions of a messenger, hit in a serious alteration - the Spaniards suddenly attacked this captain right in Tortuga. But "+ GetSexPhrase("he's out","she's out") +" from the fight the winner.", HOLLAND, 5, 1);
        break;
        //********************** Квест №8, Поиски Евангелие для Аарона ************************
        case "Step_8_1":
            dialog.text = "But it wasn't enough. I am amazed at your failure, you could not complete the simplest task. Well, come and see me from time to time, maybe I can find something for you that you can do.";
            link.l1 = "Okay, mynheer.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_8_SeekBible");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -260);
			AddCharacterExpToSkill(pchar, "Cannons", -300);
			AddCharacterExpToSkill(pchar, "FencingLight", -270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -250);
 			//слухи
			AddSimpleRumour("They say the captain " + GetFullName(pchar) + "took for completing an unusual task - the search for some mysterious biblical treatise. Took, but didn't complete...", HOLLAND, 5, 1);
		break;
        case "Step_8_2":
            dialog.text = "Ah, that's what he is... Well, that's fine. I hope he thanked you properly?";
            link.l1 = "More than, mynheer.";
            link.l1.go = "Step_8_3";
        break;
        case "Step_8_3":
            dialog.text = "Great. Perhaps that's it. I don't need you yet, you can go about your business. But in a couple of weeks, please come to me, for sure I will have a new task for you.";
            link.l1 = "Always at your service, Mynheer.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_8_SeekBible");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            pchar.questTemp.Waiting_time = "2";
			TakeItemFromCharacter(pchar, "LegransMap");
			ChangeCharacterReputation(pchar, 2);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
 			//слухи
			AddSimpleRumour("They say the captain " + GetFullName(pchar) + " I took up an unusual task - the search for some mysterious biblical treatise. And they say that they found it.", HOLLAND, 5, 1);
        break;
        //********************** Квест №9, Захват линейных кораблей. ************************
        case "Step_9_1":
            dialog.text = "If we can't build big ships, we have to capture them!";
            link.l1 = "Amazing! Just like everything brilliant...";
            link.l1.go = "Step_9_2";
        break;
        case "Step_9_2":
            dialog.text = "Hmm, that's right... So, I ask you to put at least four ships of the first class, that is, Manovars, at the disposal of the Dutch fleet.";
            link.l1 = "Hmm... Not bad, perhaps...";
            link.l1.go = "Step_9_3";
        break;
        case "Step_9_3":
            dialog.text = "I think so too. Capture at least four ships, bring them to Curacao, to the port of Willemstad, and hand them over to me personally. You will be paid 50,000 coins for each of the surrendered ships. Do you think you can handle this task?";
            link.l1 = "I suppose so.";
            link.l1.go = "Step_9_4";
        break;
        case "Step_9_4":
            dialog.text = "Then let's not waste time - get started immediately.";
            link.l1 = "Okay, Mynheer, I'll start immediately.";
            link.l1.go = "exit";
            pchar.questTemp.QtyShips = 4;
            pchar.questTemp.State = "TakeThreeShips_toAbordage";
            AddQuestRecord("Hol_Line_9_TakeThreeShips", "1");
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_9_5":
            if (sti(pchar.questTemp.QtyShips)>1)
            {
                dialog.text = "Excellent, but the task has not yet been completed completely, you need to provide our fleet more " + pchar.questTemp.QtyShips + " ships. Don't waste your time, I'm waiting for good news from you.";
            }
            else
            {
                dialog.text = "Excellent, but the task has not yet been fully completed, you need to provide our fleet with another ship. Don't waste your time, I'm waiting for good news from you.";
            }
            link.l1 = "Okay, Mynheer, I'll do whatever it takes.";
            link.l1.go = "exit";
        break;
        case "Step_9_6":
            dialog.text = "Great! I will immediately order the captured ships to be sent to the Indian Ocean.";
            link.l1 = "Why there, may I ask, Mynheer?";
            link.l1.go = "Step_9_7";
        break;
        case "Step_9_7":
            dialog.text = "Because there is an active confrontation with Portugal. And right now, there has been some success in the actions of the Portuguese. I believe that this squadron will restore parity.";
            link.l1 = "Well, look for yourself. But I wouldn't stay in such a rosy mood about the situation here in the Caribbean.";
            link.l1.go = "Step_9_8";
        break;
        case "Step_9_8":
            dialog.text = "What do you mean?";
            link.l1 = "Don't you think these ships might be useful here? For additional protection of Dutch settlements, for example.";
            link.l1.go = "Step_9_9";
        break;
        case "Step_9_9":
            dialog.text = "Well, no, of course not. Nothing threatens us, be calm about the fate of the Dutch settlements.";
            link.l1 = "Okay, mynheer. However, calmness seems deceptive to me. Besides, Holland, after all, is at war with England.";
            link.l1.go = "Step_9_10";
        break;
        case "Step_9_10":
            dialog.text = "The active phase of the fighting has passed. The British are not up to us, they have problems with the Spaniards. Actually, assessing the political situation is not your problem.";
            link.l1 = "I just said my opinion...";
            link.l1.go = "Step_9_11";
        break;
        case "Step_9_11":
            dialog.text = "Your opinion is taken into account. And now I'm going to ask you to leave me alone. But after a while, I'd like to see you at my place.";
            link.l1 = "Okay, mynheer.";
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
            CloseQuestHeader("Hol_Line_9_TakeThreeShips");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
            pchar.questTemp.Waiting_time = "20";
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			//слухи
			AddSimpleRumour("Captain, you have captured so many battleships that it is simply breathtaking!", HOLLAND, 5, 1);
        break;
        //********************** Квест №10, Оборона Кюрасао. ************************
        case "Step_10_1":
            dialog.text = "I was informed that a large Spanish squadron was approaching Curacao. I don't know if we can withstand an attack... I have no idea how Spain managed to gather such forces in Caribbean waters, and even in such a short time\n"+
                          "However, we'll think about it later if we manage to survive. Now I ask you to apply all your knowledge and skills to help the fort and the guard squadron repel the attack. Without your help, I'm quite sure we'll be crushed.";
            link.l1 = "I will try to do my best. I guess we'll fight back.";
            link.l1.go = "Step_10_2";
        break;
        case "Step_10_2":
            dialog.text = "Well, I'm counting on you!";
            link.l1 = "See you after the battle.";
            link.l1.go = "exit";
            pchar.questTemp.State = "SpaAttackCuracao_toBattle";
            AddQuestRecord("Hol_Line_10_SpaAttackCuracao", "1");
 		 AddQuestUserData("Hol_Line_10_SpaAttackCuracao", "sSex", GetSexPhrase("en","on"));
            SaveCurrentQuestDateParam("questTemp");
            Pchar.quest.SpaAttackCuracao_Battle.win_condition.l1 = "location";
            Pchar.quest.SpaAttackCuracao_Battle.win_condition.l1.location = "Curacao";
            Pchar.quest.SpaAttackCuracao_Battle.win_condition = "SpaAttackCuracao_Battle";
        break;
        case "Step_10_3":
            dialog.text = "I have a different opinion about this - your participation in the battle was decisive! I don't think money is the most important thing in your life, but I ask you to accept 200,000 coins as a reward for saving the city.";
            link.l1 = "Really, Mynheer, I probably don't deserve this...";
            link.l1.go = "Step_10_4";
        break;
        case "Step_10_4":
            dialog.text = "I don't want to listen to anything, the Netherlands should encourage such people in every possible way. And that's it! And now I need to gather as much information as possible about why the Spaniards attacked Curacao. I ask you to come to me the other day, apparently, this is not all...";
            link.l1 = "Okay, Mynheer, I'll be with you at this time.";
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
            AddMoneyToCharacter(pchar, 200000);
            CloseQuestHeader("Hol_Line_10_SpaAttackCuracao");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
            pchar.questTemp.Waiting_time = "3";
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			//слухи
			AddSimpleRumour("You saved us, Captain! To repel such a powerful attack is simply magnificent!", HOLLAND, 5, 5);
        break;
        //********************** Квест №11, Спасение Мариго от испанцев. ************************
        case "Step_11_1":
            dialog.text = "It really happened. It looks like we've finished playing 'helping the French'...";
            link.l1 = "What do you mean, Mynheer?";
            link.l1.go = "Step_11_2";
        break;
        case "Step_11_2":
            dialog.text = "You know that Louis XIV is waging a devolution war with Spain over the so-called Spanish inheritance - Flanders and Burgundy. Although these territories are not part of the Republic of the United Provinces, they are nevertheless ethnically and culturally connected with Holland. Therefore, we are doing everything we can to help the French in this war - financially, of course\n"+
                          "It seems that Spain has seriously decided to block this money stream, with which Louis generously pays for the war. This step, I must say, is verified, since France is in a very difficult financial situation and without our money Louis simply will not have anything to pay for the conduct of the war\n"+
                          "Today I learned that Curacao is not the only Dutch colony that has been attacked. San Martin is also under siege.";
            link.l1 = "Damn it...";
            link.l1.go = "Step_11_3";
        break;
        case "Step_11_3":
            dialog.text = "I ask you to gather all your forces and immediately move to San Martin to help the besieged. You must try to save the city from destruction in time.";
            link.l1 = "I will do my best, Mynheer. Rely on me.";
            link.l1.go = "Step_11_4";
        break;
        case "Step_11_4":
            dialog.text = "Yes, it seems that I just have no choice.";
            link.l1 = "I will speak immediately.";
            link.l1.go = "exit";
            pchar.questTemp.State = "SpaAttackSentMartin_toBattle";
            AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "1");
            SaveCurrentQuestDateParam("questTemp");
            Pchar.quest.SpaAttackSentMartin_Battle.win_condition.l1 = "location";
            Pchar.quest.SpaAttackSentMartin_Battle.win_condition.l1.location = "SentMartin";
            Pchar.quest.SpaAttackSentMartin_Battle.win_condition = "SpaAttackSentMartin_Battle";
            SetTimerCondition("SpaAttackSentMartin_YouLate", 0, 0, 10, false);
        break;
        case "Step_11_5":
            dialog.text = "It's bad. But there's nothing you can do, that's life.";
            link.l1 = "I'm really sorry...";
            link.l1.go = "Step_11_6";
        break;
        case "Step_11_6":
            dialog.text = "You did everything you could, I notified you too late. Well, enough of this! I ask you to come to my residence in about a month. Do not waste time, put your ships in order, recruit a team, replenish ammunition. In general, prepare yourself properly for the response. It seems to me that the moment has come when the Netherlands will be able to increase the number of its colonial possessions in the Caribbean.";
            link.l1 = "And which city will have to become Dutch?";
            link.l1.go = "Step_11_7";
        break;
        case "Step_11_7":
            dialog.text = "I don't know yet. It all depends on the information I get in the near future.";
            link.l1 = "I got it, mynheer. I'll be with you in a month.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_11_SpaAttackSentMartin");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
            pchar.questTemp.Waiting_time = "30";
        break;
        case "Step_11_8":
            dialog.text = "Great, "+ GetSexPhrase("my friend","" + pchar.name + "") +", just great. I've never doubted you.";
            link.l1 = "Glad to hear, Mynheer.";
            link.l1.go = "Step_11_9";
        break;
        case "Step_11_9":
            dialog.text = "Your reward for saving San Martin is 200,000 coins. Please receive it.";
            link.l1 = "Thank you, Mynheer.";
            link.l1.go = "Step_11_10";
            AddMoneyToCharacter(pchar, 200000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			//слухи
			AddSimpleRumour("They say you saved San Martin from destruction! Great job, Captain!", HOLLAND, 5, 1);
        break;
        case "Step_11_10":
            dialog.text = "I also ask you to come to my residence in about a month. Do not waste time, put your ships in order, recruit a team, replenish ammunition. In general, prepare yourself properly for the response. The Spaniards are exhausted, and now is the moment when the Netherlands will be able to increase the number of its colonial possessions in the Caribbean.";
            link.l1 = "And which city will have to become Dutch?";
            link.l1.go = "Step_11_7";
        break;
        //********************** Квест №12, Захват Венесуэллы. ************************
        case "Step_12_1":
            dialog.text = "I think so too. Actually, get started.";
            link.l1 = "I'm ready for the operation, the city of Maracaibo will be Dutch!";
            link.l1.go = "Step_12_2";
        break;
        case "Step_12_2":
            dialog.text = "So be it!";
            link.l1 = "I will speak immediately, Mynheer.";
            link.l1.go = "exit";
            pchar.questTemp.State = "OccupyMaracaibo_toFight";
            AddQuestRecord("Hol_Line_12_OccupyMaracaibo", "1");
            SaveCurrentQuestDateParam("questTemp");
			characters[GetCharacterIndex("Maracaibo_Mayor")].dialog.captureNode = "HolLine12Quest_Occupy"; //капитулянтская нода мэра
        break;
        case "Step_12_3":
            dialog.text = "I have already sent a report on this acquisition to the metropolis. Our state, our young nation, is hungry for victories! And we are doing everything for the prosperity of the Republic of the United Provinces\n"+
                          "So you've done a good job. I don't have any more assignments for you. But I sincerely hope that your further actions in the Caribbean region will be just as effective and just as effective.";
            link.l1 = "I think you can count on me, Mynheer. The good of the Netherlands comes first!";
            link.l1.go = "Step_12_4";
        break;
        case "Step_12_4":
            dialog.text = "Here are the words "+ GetSexPhrase("a great warrior and a true patriot","a great warrior and a true patriot") +"! And now I ask you to accept 300,000 coins from me as payment for your devoted service.";
            link.l1 = "Thank you, Mynheer.";
            link.l1.go = "Step_12_5";
            AddMoneyToCharacter(pchar, 300000);
        break;
        case "Step_12_5":
            dialog.text = "Well, now tell me, what are your plans?";
            link.l1 = "Sleep it off, mynheer. And then we'll see.";
            link.l1.go = "Step_12_6";
        break;
        case "Step_12_6":
            dialog.text = "Well, I dare not disturb you.";
            link.l1 = "Goodbye, Mynheer.";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Waiting_time");
            pchar.questTemp.State = "EndOfQuestLine";
			CloseQuestHeader("Hol_Line_12_OccupyMaracaibo");
			bWorldAlivePause   = false; // Конец линейки
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
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
			AddSimpleRumour("Captain, they say that you have managed to capture Venezuela! Wow...", HOLLAND, 5, 1);
        break;

        //********************** Французская линейка. Квест №2, доставка письма д'Ожерона. ************************
        case "Step_F2_1":
            dialog.text = "Yes, yes, thank you... and you claim that this letter was given to you by the Governor General d'Ogeron?";
            link.l1 = "Of course! I have the honor to be in the service of the King of France.";
            link.l1.go = "Step_F2_2";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
        break;
        case "Step_F2_2":
            dialog.text = "But you're not an officer. Doesn't d'Ogeron have soldiers anymore? But it seems to me that you are in the service of the Coast Brotherhood and intercepted this letter, and here came to spy! Guards, arrest "+ GetSexPhrase("him","her") +"!!!";
            link.l1 = "Listen, monsieur...";
            link.l1.go = "Step_F2_3";
        break;
        case "Step_F2_3":
			pchar.questTemp.State = "Fr2Letter_Arrest";
			for (i=1; i<=3; i++)
			{
				tempStr = "sold_hol_"+i;
				if (i==3) tempStr = "off_hol_1";
				sld = GetCharacter(NPC_GenerateCharacter("Guard_"+i, tempStr, "man", "man", 30, HOLLAND, 0, true));
				sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				FantomMakeCoolFighter(sld, 30, 70, 60, "blade34", "pistol2", 70);
         		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
				LAi_SetWarriorType(sld);
			}
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
			DialogExit();
        break;
 		case "Step_F2_4":
    		dialog.text =  NPCStringReactionRepeat("I'm listening to you carefully.",
            "We've already talked about this topic...", "Again?", "Stop it!", "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("Monsieur Governor-General, as far as I know, pirates were operating near Curacao, who sank two dozen ships.", "Yes, exactly...", "No, sorry...", "Sorry...", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_F2_5", "none", "none", "none", npchar, Dialog.CurrentNode);
 		break;
        case "Step_F2_5":
            dialog.text = "That's right. Well, actually, what?";
            link.l1 = "I managed to track down the bandits in the city and follow their footsteps to the galleon, which hunted Dutch ships. These bandits turned out to be Spanish privateers.";
            link.l1.go = "Step_F2_6";
        break;
        case "Step_F2_6":
            dialog.text = "And where is this galleon?";
            link.l1 = "At the bottom near the Palm beach. I boarded him and killed the team. The captain was interrogated by me before he died, so there can be no doubt - this is the same galleon that haunted you.";
            link.l1.go = "Step_F2_7";
        break;
        case "Step_F2_7":
            dialog.text = "Well, what can I say - it's just great! You have done the city a great service. I must admit, I thought it was the work of the Brethren...";
            link.l1 = "I figured it out, monsieur, that's why I took searches. Filibusters do not attack Dutch ships.";
            link.l1.go = "Step_F2_8";
        break;
        case "Step_F2_8":
            dialog.text = "It's good that I didn't hang you... Well, I guess you deserve a reward. I am ready to pay you 20,000 gold for the sunk pirate galleon. Will that suit you?";
            link.l1 = "Without a doubt, sir, that's enough. Now let me take my leave-it's time for me to go back. Goodbye.";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			AddQuestRecord("Fra_Line_2_DelivLetter", "6");
			AddQuestUserData("Fra_Line_2_DelivLetter", "sSex", GetSexPhrase("","a"));
        break;
		// --------------------- линейка ГПК, вопрос о Тизере ---------------------
		case "TizerFind":
			dialog.text = "If I know this person, then, without a doubt, I will answer you, Captain.";
			link.l1 = "I'm interested in Teaser Dan, mynheer.";
			link.l1.go = "TizerFind_1";
		break;
		case "TizerFind_1":
			dialog.text = "It is very strange that you are interested in a beggar, a tramp, a convict and a former slave!";
			link.l1 = "Convict?";
			link.l1.go = "TizerFind_2";
		break;
		case "TizerFind_2":
			dialog.text = "That's right! For his participation in the troubles, he was deprived of the rights of Dutch citizenship and exiled to hard labor. However, the ship on which he was transported was captured by pirates, and Teaser himself was sold into slavery by them...";
			link.l1 = "Damn it, what an interesting fate!";
			link.l1.go = "TizerFind_3";
		break;
		case "TizerFind_3":
			dialog.text = "I don't see anything interesting! And why are you interested in criminals?";
			link.l1 = "Mynheer, the thing is that... In general, I'm worried about collecting samples of folk art. You know, when I return to the Old World, I want to write a book about my adventures in the New One. That's it, sir... And Teaser is a very colorful figure!";
			link.l1.go = "TizerFind_4";
		break;
		case "TizerFind_4":
			dialog.text = "Are you serious about this?";
			link.l1 = "Absolutely. I happened to learn from the residents of your city about the stories that Teaser told in public. It's very interesting, you know... Of course, I understand that all this is a lie, but how entertaining! Perfect material for a book.";
			link.l1.go = "TizerFind_5";
		break;
		case "TizerFind_5":
			dialog.text = "Hmm, I encourage writing. These are new lands, new heroes, new horizons of the boundless world ocean... Yeah, it's very interesting. But I did not expect such inclinations from you, Captain!";
			link.l1 = "Mynheer, there's still a lot you don't know about me.";
			link.l1.go = "TizerFind_6";
		break;
		case "TizerFind_6":
			dialog.text = "Understood. Well, I would be happy to help you with Teaser Dan, but I do not know where he is. And I have no idea. The fact is that this tramp violated public order more than once, and I had to apply repressive measures to him. I believe he has left the island.";
			link.l1 = "Sad... And I understand that you don't know where.";
			link.l1.go = "TizerFind_7";
		break;
		case "TizerFind_7":
			dialog.text = "I have already said that I have no idea. I suggest you describe Curacao as it is, without the idiotic nonsense of a former slave. Believe me, your essay will only benefit from this.";
			link.l1 = "Well, I'll look for material on your island. Thank you!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toLicencer";
			AddQuestRecord("ISS_PoorsMurder", "9");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("ся","as"));
			AddQuestUserData("ISS_PoorsMurder", "sSex1", GetSexPhrase("","а"));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
