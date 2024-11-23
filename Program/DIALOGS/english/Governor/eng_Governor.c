// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now.";
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.BlackYosh_1"))	//Квест "Black Hedgehog"
			{
    			link.l1 = "I heard that two frigates came to the Port Royal shipyard to replenish their weapons and food.";
				link.l1.go = "BlackYosh_1";
			}
			if (CheckAttribute(PChar, "questTemp.silverfleet") && pchar.questTemp.silverfleet != "over" && NPChar.name == GetConvertStr("Variable_StoryCharacters_0.1", "Names.txt"))
			{
				if (!CheckAttribute(NPChar, "SilverFleetCancelThinking") || GetNpcQuestPastDayParam(NPChar, "SilverFleetCancelThinking") > 0)
				{
					link.l1 = "I've decided to abandon your mission to destroy the convoy.";
					link.l1.go = "SF_HuberDialogueThinking";
				}
				if (pchar.questTemp.silverfleet == "ToHuber")
				{
					link.l1 = "I've been informed that you wish to see me.";
					link.l1.go = "SF_HuberDialogueBeginning";
				}
				if (pchar.questTemp.silverfleet == "FirstSilverFleetDeath")
				{
					link.l1 = "Silver convoy destroyed, sir. I'd like a reward.";
					link.l1.go = "SF_HuberDialogueFirstSilverFleetDeath";
				}
				if (pchar.questTemp.silverfleet == "SecondSilverFleetDeath")
				{
					link.l1 = "I come to you with news, sir. But from the looks of you, it's you who's going to do the talking.";
					link.l1.go = "SF_HuberDialogueSecondSilverFleetDeath";
				}
				if (pchar.questTemp.silverfleet == "ThirdSilverFleetDeath")
				{
					link.l1 = "Is it finally over?";
					link.l1.go = "SF_HuberDialogueTheEnd";
				}
				if (pchar.questTemp.silverfleet == "SeaBattleFail")
				{
					link.l1 = "I couldn't destroy the Silver Convoy. The squadron is too strong.";
					link.l1.go = "SF_HuberDialogueFail";
				}
			}
		break;

		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Unfortunately, I cannot provide you with a job. You are not the person I would like to entrust my affairs to. Goodbye.";
                link.l1 = "Wow...";
                link.l1.go = "exit";
				break;
			}
            // сюда вход только с патентом, проверка выше
            dialog.text = LinkRandPhrase("You are an English privateer and you must keep your word to me! I ask you to immediately begin fulfilling the assignment assigned to you!",
                                         "Until you complete my assignment, I have nothing to talk about with you.",
                                         "I am waiting for your report on the fulfillment of a responsible assignment, and not empty conversations!");
            link.l1 = RandPhraseSimple("Starting immediately.", "I'm already in the process of doing...");
            link.l1.go = "exit";

			switch (pchar.questTemp.State)   // что делаем в данный момент
            {
                case "empty":   // Нет взятых квестов
                    if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
                    {
                        dialog.text = LinkRandPhrase("I don't have any special assignments for you yet. Come visit me from time to time.",
                                                     "Not now, I'm too busy!",
                                                     "Your dexterity and courage are not in demand yet, go about your privateering business, "+ GetSexPhrase("my friend","" + pchar.name + "") +".");
                        link.l1 = "Okay, sir.";
                        link.l1.go = "exit";
                    }
                    else
                    {
						switch(pchar.questTemp.CurQuestNumber)   // Взятие квестов начиная со второго
                        {
                            case "2":
                                dialog.text = "I have a task for you.";
                                link.l1 = "I'm ready, sir.";
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":   // раньше тройки не было, теперь нужно для того, чтобы ГГ мог взять квест №4 без квеста №3.
                                dialog.text = "Come to me in two days, I have a case brewing for you.";
                                link.l1 = "Okay, sir.";
                                link.l1.go = "exit";
                                pchar.questTemp.Waiting_time = "2";
                                SaveCurrentQuestDateParam("questTemp");
                                pchar.questTemp.CurQuestNumber = "4";
                            break;
                            case "4":
                                dialog.text = "I have a case for you - a reconnaissance mission. I need to know what the Dutch are going to do about the trade war. Make your way to Curacao and try to gather as much information as possible about what is happening there. I'm interested in everything that happens in the city, down to the smallest detail.";
                                link.l1 = "I'm ready, sir.";
                                link.l1.go = "Step_4_0";
                            break;
                            case "5":
                                dialog.text = "Ah, here you are. I've been waiting for you.";
                                link.l1 = "I am at your service.";
                                link.l1.go = "Step_5_1";
                            break;
                            case "6":
                                dialog.text = "The captain of the privateer frigate Morris Williams asks my permission to stand in the raid at Port Royal.";
                                link.l1 = "I know Captain Williams.";
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = "It is with great regret that I must inform you that the order of the British government to return the cargo seized by Morris Williams to the Spanish owner has led to serious consequences for Jamaica.";
                                link.l1 = "Hmm... I don't really understand, sir...";
                                link.l1.go = "Step_7_1";
                                // ==> Убираем Морриса Уильямса
                                sld = characterFromID("Morris_Willams");
                        	    sld.LifeDay = 1; // уберём нпс на след.день.
                        	    SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
                            break;
                            case "8":
                                dialog.text = "I need you again, "+ GetSexPhrase("my friend","" + pchar.name + "") +". I need to send a reliable person to the head of the Buccaneer settlement of La Vega, in Hispaniola. Yes, you know Edward Mansfield, you have already visited him on my behalf. Do you remember?";
                                link.l1 = "I remember, sir. I "+ GetSexPhrase("tried","tried") +"persuade him to organize an attack on Curacao.";
                                link.l1.go = "Step_8_1";
                            break;
                            case "9":
                                dialog.text = "Are you ready to complete the serious task of storming the Spanish city?";
                                link.l1 = "Yes, I am enough "+ GetSexPhrase("prepared","prepared") +".";
                                link.l1.go = "Step_9_1";
                                link.l2 = "No, sir. I don't have enough ships for such a serious event. I'll prepare properly and come back later.";
                                link.l2.go = "exit";
                            break;
                            case "10":
                                dialog.text = "The Spanish government has equipped a squadron of seven battleships under the command of Admirals de Bustos and del Campo y Espinosa against the Jamaican corsairs. They have already reached Jamaica. The moment could not have been better chosen, you saw for yourself that there are no more corsairs on the raid of Port Royal, except for you, all with Morgan in another hunt for the Spaniards. You must repel the attack. The guard ships are coming to your disposal, that's all I can help you with. Go ahead, and may the Lord help us!";
                                link.l1 = "Okay, sir. I guess we'll fight back.";
                                link.l1.go = "exit";
                                pchar.questTemp.State = "SpanishAttack_ShipsInShore";
                                SetQuestHeader("Eng_Line_10_SpanishAttack");
                                AddQuestRecord("Eng_Line_10_SpanishAttack", "1");
                                Pchar.quest.SpanishAttack_Battle.win_condition.l1 = "location";
                                Pchar.quest.SpanishAttack_Battle.win_condition.l1.location = "Jamaica";
                                Pchar.quest.SpanishAttack_Battle.win_condition = "SpanishAttack_Battle";
                                ChangeCharacterAddress(characterFromID("Henry Morgan"), "None", "");
                            break;
                            case "11":
                                dialog.text = "You are most welcome! I have an important assignment for you.";
                                link.l1 = "I'm listening to you, sir.";
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = ""+ GetSexPhrase("My friend","" + pchar.name + "") +", I have a somewhat unusual assignment for you...";
                                link.l1 = "I'm listening carefully.";
                                link.l1.go = "Step_12_1";
                            break;
                            case "13":
                                dialog.text = "I am very glad to see you at my place. And you're very welcome, sir.";
                                link.l1 = "Sir?";
                                link.l1.go = "Step_12_5";
                            break;
                        }
                    }
                break;

                case "":           // Квест №1 - сопровождение Альбермаля
                    dialog.text = "I have a very important assignment for you. You're a new person here, I'm not sure if I should trust you, but I don't seem to have a choice.";
                    link.l1 = "I will "+ GetSexPhrase("glad","glad") +"to carry out your assignment.";
                    link.l1.go = "Step_1_1";
                    link.l2 = "Sorry, but I'm currently solving another problem.";
                    link.l2.go = "exit";
                break;
                case "Albermal_good_time":                  // Геймер успел доставить Альбермаля за неделю.
                    dialog.text = "In the letter you delivered, Duke Albermaal gives you a very flattering assessment. The Duke is my relative, and it is to him that I owe my appointment to this position. If not for his active and timely actions in England, it is not known how my governorship in Barbados would have ended..\n"+
                                  "You have brilliantly completed the task. The promised reward is 50,000. You have earned this money and my gratitude\n"+
                                  "Duke Albermaal's recommendation is the best guarantee for me. If you are ready to continue cooperation with England, then please come to me from time to time.";
                    link.l1 = "Thank you, sir. You can count on me in the future.";
                    link.l1.go = "exit";
    				AddMoneyToCharacter(pchar, 50000);
    				ChangeCharacterReputation(pchar, 5);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
    				AddCharacterExpToSkill(pchar, "Defence", 100);
    				AddTitleNextRate(sti(NPChar.nation), 1);
                    CloseQuestHeader("Eng_Line_1_Albermal");
                    pchar.questTemp.State = "empty";
                    SaveCurrentQuestDateParam("questTemp");
                    TakeItemFromCharacter(pchar, "letter_Albermal");
					//слухи
					AddSimpleRumour("You heard the captain " + GetMainCharacterNameGen() + " our governor-General praised very much. "+ GetSexPhrase("He allegedly managed","She allegedly managed") +"to smuggle his London uncle and patron, the Peer of England, the Duke of Albemarle, off the island. Do you know who Albermaal is?! I will tell you in confidence that it is only thanks to him that Sir Thomas Madiford is acting governor of Jamaica, otherwise he would not have been well...", ENGLAND, 5, 1);
                break;
                case "Albermal_late":  // Геймер не успел за неделю доставить Альбермаля.
                    dialog.text = "Well, in the letter you delivered, Albermal informs me of his safe arrival in St. John's. You repulsed the attack of the Spanish brig, but you were unable to deliver the Duke to his destination on time. Your reward is 20,000. I would not say that I am fully satisfied with you.";
                    link.l1 = "Sir, I'm sorry for being late, but I was delayed by force majeure. I hope I can expect to receive special assignments in the future?";
                    link.l1.go = "Step_1_4";
                break;
                case "after_talks_with_pirates":  // После опроса пиратов
                    dialog.text = "Have you enlisted the support of the pirates? When is Mansfield planning the action?";
                    link.l1 = "Sir, unfortunately, I was unable to negotiate with any of the pirates you mentioned. Everywhere I received a refusal to attack Curacao. The reasons why the corsairs refused to attack are different.";
                    link.l1.go = "Step_2_3";
                break;
                case "Intelligence_Curacao_Sink":  // Голландский флейт с инфой на борту был потоплен, провал миссии
                    dialog.text = "Report what you have learned.";
                    link.l1 = "Unfortunately, I was unable to capture the ship I was on "+ GetSexPhrase("should have","should have") +" find the necessary papers. I haven't been able to find out anything useful.";
                    link.l1.go = "Step_4_1";
                break;
                case "Intelligence_Curacao_Boarding":  // Миссия выполнена, голландский флейт взят на абордаж
                    dialog.text = "Report what you have learned.";
                    link.l1 = "Here is the document that was found on the captured Dutch brig. This is an order to the governor of Fort Orange to urgently fortify the city.";
                    link.l1.go = "Step_4_2";
                break;
                case "Intelligence_Curacao_BoardingNotFoundLetter":  // Миссия провалена, голландский флейт взят на абордаж, но письмо не найдено
                    dialog.text = "Report what you have learned.";
                    link.l1 = "I received an information about the Dutch courier brig. I managed to board this brig, but I didn't find any documents there.";
                    link.l1.go = "Step_4_1";
                break;
                case "Intelligence_Curacao_OutPrison":  // Миссия провалена, ГГ побывал в тюрьме
                    dialog.text = "Report what you have learned.";
                    link.l1 = ""+ GetSexPhrase("Unfortunately, I was captured and imprisoned. I managed to escape, but I didn't find out anything,","Unfortunately, I was captured and imprisoned. I managed to escape, but I didn't find out anything") +".";
                    link.l1.go = "Step_4_4";
                break;
                case "Intelligence_Curacao_FightGard": // Миссия провалена, ГГ дрался и ушёл из города ни с чем
                    dialog.text = "Report what you have learned.";
                    link.l1 = "Unfortunately, I was exposed during the assignment. There was a fight, and I barely "+ GetSexPhrase("broke out","broke out") +" from the city. Now my appearance in Curacao is out of the question. I haven't been able to find out anything interesting for you.";
                    link.l1.go = "Step_4_5";
                break;
                case "AttackFortOrange_WeWin":   // Форт Оранж взят.
                    dialog.text = "You're covered in blood";
                    link.l1 = "This is Dutch blood... We did it, Fort Orange is looted. My team has made a good profit. The task is completed.";
                    link.l1.go = "Step_5_2";
                break;
                case "MorrisWillams_AfterFirstTalkingWithMorris": // Получено согласие Морриса Уильямса зайти в Порт Рояль.
                    dialog.text = "So what do you say, " + GetFullName(pchar) + "?";
                    link.l1 = "Sir, your assignment is completed, Morris Williams is entering port.";
                    link.l1.go = "Step_6_2";
                break;
                case "MorrisWillams_ToModifordForCoolTalking": // На разборки после разговора с Уильямсом в таверне
                    dialog.text = "Ah, here you are again, " + GetFullName(pchar) + ". I'm listening to you carefully.";
                    link.l1 = "Damn it! What's going on?";
                    link.l1.go = "Step_6_3";
                break;
                case "MorrisWillams_ArrestedToModiford": // На разборки после разговора с начальником тюрьмы
                    dialog.text = "Ah, here you are again, " + GetFullName(pchar) + ". What brings you to me this time?";
                    link.l1 = "Sir, I need to talk to you.";
                    link.l1.go = "Step_6_6";
                break;
                case "MorrisWillams_ModifordGood5000":
                    dialog.text = "Ah, "+ GetSexPhrase("my friend","" + pchar.name + "") +", have you already spent five thousand rubles and you need a job?";
                    link.l1 = "No, I am "+ GetSexPhrase("logged in","logged in") +"talk about abstract topics.";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_ModifordPolitic":
                    dialog.text = "I have nothing more to say to you. Politics decides the fate of states, there is nothing to think about the fate of individual privateers...";
                    link.l1 = "Very sorry, sir.";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_SeekSpanishGoods":
                    dialog.text = "Well, "+ GetSexPhrase("my friend","" + pchar.name + "") +" Have you calmed down about Williams yet? My advice to you is to leave this case, the poor guy is out of luck. But that's life, someone has to be the loser...";
                    link.l1 = "Sir, I highly appreciate your kind advice. I will try to follow it...";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_PinnaceBoard":
                    dialog.text = "I heard you boarded a Spanish pinnace right near San Juan under fire from the fort?!! I must say, a risky operation...";
                    link.l1 = "All's well that ends well, sir...";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_PinnaceBoardNotFoundMoney":
                    dialog.text = "I heard you boarded a Spanish pinnace right near San Juan?!! Tell me, was the risk justified?";
                    link.l1 = "No, sir. There's nothing useful in the holds...";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_PinnaceSink":
                    dialog.text = "I heard you sank a Spanish pinnace right near San Juan. And why climb right into the fire of the fort?";
                    link.l1 = "As it happened, sir...";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_DieHard":
                    dialog.text = "The portmaster reported to me that you were in pursuit of a Spanish pinnace. Tell me, my friend, is it successful? (with mockery)";
                    link.l1 = "No, sir. "+ GetSexPhrase("Tried","Tried") +"in vain...";
                    link.l1.go = "exit";
                break;
                case "SevenTreasures_GoOn":
                    dialog.text = "Have you found gold?";
                    link.l1 = "Not yet, but I'm constantly searching. The task is not easy...";
                    link.l1.go = "exit";
                    if (CheckCharacterItem(pchar, "jewelry5"))
                    {
                        link.l1 = "There is something.";
                        link.l1.go = "Step_7_4";
                    }
                    link.l2 = "You know, Governor General, I'm sick to death of this. I no longer want to rush around the Caribbean and look for gold for you.";
                    link.l2.go = "Step_7_10";
                break;
                case "ToMansfield_CatchToPardal":
                    dialog.text = "Did you bring gold from Mansfield?";
                    link.l1 = "Sir, the Buccaneer settlement has been attacked by the Spanish. Mansfield is killed, the gold is stolen. The admiral of the Spanish squadron, apparently, was Manoel Rivero Pardal.";
                    link.l1.go = "Step_8_3";
                break;
                case "ToMansfield_NotFoundGaleon":
                    dialog.text = "Did you bring gold from Mansfield?";
                    link.l1 = "Sir, La Vega has been attacked by the Spaniards. Mansfield is killed, the gold is stolen. The admiral of the Spanish squadron was Manoel Rivero Pardal. Sir, I "+ GetSexPhrase("checked","checked") +"all the way to Santiago, but not "+ GetSexPhrase("met","met") +"the attacking Spaniards.";
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = "Were you able to overtake the Spaniards?";
                        link.l1 = "No, sir. I did not succeed. I "+ GetSexPhrase("checked","checked") +"all the way to Santiago, but not "+ GetSexPhrase("met","met") +"galleons.";
                    }
                    link.l1.go = "Step_8_5";
                break;
                case "ToMansfield_Boarding":
                    dialog.text = "Did you bring gold from Mansfield?";
                    link.l1 = "Sir, La Vega has been attacked by the Spanish. Mansfield is killed, the gold is stolen. The admiral of the Spanish squadron was Manoel Rivero Pardal. I managed to overtake one of the three attacking galleons and board it. There was no gold there, but I found Pardal's letter to Governor Santiago Jimenez in the captain's cabin. Here it is.";
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = "Were you able to overtake the Spaniards?";
                        link.l1 = "Next to Santiago I am "+ GetSexPhrase("managed","managed") +" to board a Spanish galleon, one of those that participated in the attack on the buccaneers. There was no gold there, but a letter from Pardal to Governor Santiago Jimenez was found in the captain's cabin, here it is.";
                    }
                    link.l1.go = "Step_8_5";
                    npchar.TempQuest.KindResult = 1; // признак результата завершения квеста, 1 == было захвачено письмо
        			AddCharacterExpToSkill(pchar, "Cannons", 600);
        			AddCharacterExpToSkill(pchar, "Sailing", 750);
        			AddCharacterExpToSkill(pchar, "Defence", 550);
        			AddCharacterExpToSkill(pchar, "Accuracy", 700);
        			AddTitleNextRate(sti(NPChar.nation), 1);
                break;
                case "ToMansfield_BoardingNotFoundLetter":
                    dialog.text = "Did you bring gold from Mansfield?";
                    link.l1 = "Sir, La Vega has been attacked by the Spaniards. Mansfield is killed, the gold is stolen. The admiral of the Spanish squadron was Manoel Rivero Pardal. I managed to overtake one of the three attacking galleons and board it. There was no gold there. Apparently, it was on another ship. I don't know where the other two galleons went.";
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = "Were you able to overtake the Spaniards?";
                        link.l1 = "Next to Santiago I am "+ GetSexPhrase("managed","managed") +" to board a Spanish galleon, one of those that participated in the attack on the buccaneers. There was no gold there. Apparently it was on another ship. I don't know where the other two galleons went.";
                    }
                    link.l1.go = "Step_8_5";
        			AddCharacterExpToSkill(pchar, "Repair", 40);
        			AddCharacterExpToSkill(pchar, "Commerce", 50);
        			AddCharacterExpToSkill(pchar, "Defence", 20);
        			AddCharacterExpToSkill(pchar, "Leadership", 10);
        			AddTitleNextRate(sti(NPChar.nation), 0.5);
                break;
                case "ToMansfield_GaleonSink":
                    dialog.text = "Did you bring gold from Mansfield?";
                    link.l1 = "Sir, La Vega has been attacked by the Spaniards. Mansfield is killed, the gold is stolen. The admiral of the Spanish squadron was Manoel Rivero Pardal. I managed to overtake one of the three attacking galleons and sink it. I don't know where the other two galleons went.";
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = "Were you able to overtake the Spaniards?";
                        link.l1 = "Next to Santiago I am "+ GetSexPhrase("managed","managed") +" to board a Spanish galleon, one of those that participated in the attack on the buccaneers. I managed to overtake one of the three attacking galleons and sink it. I don't know where the other two galleons went.";
                    }
                    link.l1.go = "Step_8_5";
        			AddCharacterExpToSkill(pchar, "Repair", 5);
        			AddCharacterExpToSkill(pchar, "Commerce", 10);
        			AddCharacterExpToSkill(pchar, "Cannons", -50);
        			AddCharacterExpToSkill(pchar, "Accuracy", -70);
        			AddCharacterExpToSkill(pchar, "Fencing", -100);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
                break;
                case "ToMansfield_DidNotFindBecaners":
                    dialog.text = "Did you bring gold from Mansfield?";
                    link.l1 = "Sir, when I arrived in La Vega, it turned out to be empty! Not a single living soul. I searched around, but found nothing.";
                    link.l1.go = "Step_8_5";
                    npchar.TempQuest.KindResult = 2; // признак результата завершения квеста, 2 == вообще не в курсе, что произошло
        			AddCharacterExpToSkill(pchar, "Cannons", 10);
        			AddCharacterExpToSkill(pchar, "Pistol", -200);
        			AddCharacterExpToSkill(pchar, "Defence", -100);
        			AddCharacterExpToSkill(pchar, "Accuracy", -210);
        			AddCharacterExpToSkill(pchar, "Fencing", -400);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
                break;
                case "AttackSantiago_GoodWork":
                    dialog.text = "I already know about your exploits. This is a brilliant victory, "+ GetSexPhrase("my friend","" + pchar.name + "") +".";
                    link.l1 = "Thank you, sir. I think you will be pleased to know that the Governor of Santiago is my prisoner and is on board.";
                    link.l1.go = "Step_9_4";
                break;
                case "SpanishAttack_GoodWork":
                    dialog.text = "Damn it, you literally saved us all! The city of Port Royal owes you its life!";
                    link.l1 = "Yes, the Spaniards have gathered forces that I could not even guess about"+ GetSexPhrase("could","could") +"...";
                    link.l1.go = "Step_10_1";
                break;
                case "OccupyMein_GoOn":
                    dialog.text = "You haven't captured Cumana or Caracas yet. The whole coast of Main is still in the power of the Spaniards...";
                    link.l1 = "Sir, I'm on it. The task is not easy and requires serious preparation. The attack will be carried out as soon as it is ready.";
                    link.l1.go = "exit";
                    if (CheckAttribute(pchar, "questTemp.Q11_Caracas"))
                    {
                        dialog.text = "You have captured Caracas! That's fine, "+ GetSexPhrase("my friend","" + pchar.name + "") +". But Cumana has not been captured yet. Hurry up!";
                        link.l1 = "Okay, sir.";
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Cumana"))
                    {
                        dialog.text = "Cumana belongs to England, and this is your merit! Excellent, "+ GetSexPhrase("my friend","" + pchar.name + "") +"! But I also expect you to capture Caracas, which must also be captured!";
                        link.l1 = "I'll do it, sir.";
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Caracas") && CheckAttribute(pchar, "questTemp.Q11_Cumana"))
                    {
                        dialog.text = "Cumana and Caracas are captured! Now this coast of Main belongs to England!";
                        link.l1 = "Yes, sir. We did it.";
                        link.l1.go = "Step_11_2";
                    }
                break;
                case "ColonelLinch_ArrestModiford":
                    dialog.text = "Tell me, what have you found out? What's going on in St. John's?";
                    link.l1 = "Sir, I met Colonel Thomas Lynch at the residence of the Governor of St. Johns.";
                    link.l1.go = "Step_12_2";
                break;
                case "ColonelLinch_ModifordArrested":
                    dialog.text = "You have completed the task, Madiford has been arrested and placed in prison. A comprehensive investigation into his activities as Governor-General of Jamaica is now beginning. I would really like to see you at my place in about a month.";
                    link.l1 = "Okay, sir.";
                    link.l1.go = "exit";
                    pchar.questTemp.State = "empty";
                    SaveCurrentQuestDateParam("questTemp");
                    pchar.questTemp.CurQuestNumber = "13";
                    pchar.questTemp.Waiting_time = "30";
                    CloseQuestHeader("Eng_Line_12_ColonelLinch");
                break;
                case "QuestLineBreake":
                    dialog.text = "I don't deal with people breaking their word. I have nothing more to say to you.";
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
                case "EndOfQuestLine":
                    dialog.text = pchar.name + ", I trust your vision of the situation in the Caribbean. Therefore, you are given complete freedom of action in the interests of England.";
                    link.l1 = "I understand, sir. Thank you for your trust.";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
             }
		break;

		case "Step_1_1":
			//LockQuestLine(characterFromId("Jackman")); // лочим пиратскую линейку
            dialog.text = "My close relative, the Duke of Albermaal, is staying with me now. His mission here is over, and I must urgently escort him to Britain. A Royal Navy frigate is waiting for the Duke on the island of Antigua, in St. John's. Take the Duke to St. John's, to the governor's residence\n"+
                          "Go immediately and be careful, two Spanish spies have already been caught in Port Royal and I am absolutely sure that there are still agents in the city. I must assume that the Spaniards are aware of the presence of such a high-ranking English person here. In addition, I am being informed of the strange activity of Spanish military vessels around Jamaica.";
            link.l1 = "Hmm, really, it's better to count on the worst.";
            link.l1.go = "Step_1_2";
        break;

        case "Step_1_2":
            dialog.text = "Right now I need a captain with a non-attention-grabbing vessel. My calculation is based on surprise. No one knows you, your sailboat is also unknown. You have the least risk of getting Duke Albermale safely to Antigua.";
            link.l1 = "I think you're right, sir.";
            link.l1.go = "Step_1_3";
        break;

        case "Step_1_3":
            dialog.text = "Do it within two weeks and you will be richly rewarded. You are responsible for the Duke of Albermale with your head. He is currently in my residence in a separate office. Get started as soon as you're ready, and don't delay it.";
            link.l1 = "I understand you, sir.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
			// остальные линейки в сад -->
			pchar.questTemp.NationQuest = ENGLAND;
			// остальные линейки в сад <--
            pchar.questTemp.State = "to_Albermal";               // переменная состояния квеста для линеек
            sld = GetCharacter(NPC_GenerateCharacter("Albermal", "Albermal", "man", "man", 10, ENGLAND, -1, false));
        	sld.name 	= "The Duke";
        	sld.lastname = "Albermal";
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
			sld.greeting = "Gr_QuestMan";
        	LAi_SetHuberStayType(sld);
        	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Albermal")], "PortRoyal_RoomTownhall", "goto", "goto3");
            AddQuestRecord("Eng_Line_1_Albermal", "1");
        break;

        case "Step_1_4":
            dialog.text = "I think so. But from now on, be more careful in the execution of my assignments. You are an English privateer. The interests of England are above all!";
            link.l1 = "You're right, sir. You can firmly count on me to be more "+ GetSexPhrase("executive","executive") +".";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			pchar.questTemp.Waiting_time = 10;
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
            CloseQuestHeader("Eng_Line_1_Albermal");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            TakeItemFromCharacter(pchar, "letter_Albermal");
			AddCharacterExpToSkill(pchar, "Leadership", -70);
			//слухи
			AddSimpleRumour("You know, Captain " + GetFullName(pchar) + " "+ GetSexPhrase("managed","managed") +" complete a very dangerous Madiford mission. "+ GetSexPhrase("Him","Her") +" it was necessary to bring his Duke Albermale to a safe place... Do you know who Albermaal is?! I will tell you in confidence that it is only thanks to him that Sir Thomas Madiford is acting governor of Jamaica... Only the captain with the terms "+ GetSexPhrase("failed","failed") +".", ENGLAND, 5, 1);
        break;

        case "Step_2_1":
            dialog.text = "There is a trade war with the Netherlands in Europe. The Anglo-Frankish fleet approached the shores of Holland, but, to the greatest surprise, was defeated. Now, by order of the British government, I have to organize an attack on the Dutch colony of Curacao\n"+
                          "However, I currently have no forces at my disposal capable of dealing with a fortress like Willemstad. I will use English privateers to attack. In fact, it is very profitable for me to keep an improvised pirate fleet in Port Royal - good protection and completely free for the crown! Heh...";
            link.l1 = "What is my assignment?";
            link.l1.go = "Step_2_2";
        break;

        case "Step_2_2":
            dialog.text = "I need you to find Edward Mansfield in the Buccaneer settlement of La Vega in Hispaniola, Henry Morgan currently in St. John's, Jackman in the pirate settlement in Bermudes, and John Morris on the island of Trinidad. You must get the consent of these pirates to launch an attack on Curacao, which will be led by Mansfield. Do it as quickly as possible, I'm counting on you.";
            link.l1 = "I will proceed immediately, sir.";
            link.l1.go = "Step_2_21";
        break;

        case "Step_2_21":
            dialog.text = "And I would like to talk about Morgan separately. The fact is that his house in Antigua is a real fortress. It's not that easy to get there. You have to get into the house through the dungeon located under St. John's.";
            link.l1 = "I understand, sir. Thanks for the warning. I guess I'll figure it out.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "go_talks_with_pirates";          // переменная состояния квеста для линеек
            AddQuestRecord("Eng_Line_2_Talking", "1");
            // ==>  Помещаем Моргана на Антигуа и даём ноду доступа к квестам
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
            QuestSetCurrentNode("Henry Morgan", "EngLine_quests");
            sld = characterFromID("Henry Morgan");
            LAi_SetHuberStayType(sld);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            // ==>  Генерим и помещаем Джона Морриса в Бриджтаун и даём ноду доступа к квестам
            sld = GetCharacter(NPC_GenerateCharacter("John Morris", "bocman", "man", "man", 38, PIRATE, -1, false));
        	sld.name 	= "John";
        	sld.lastname = "Morris";
            sld.Dialog.Filename = "Quest\JohnMorris.c";
            FantomMakeCoolSailor(sld, SHIP_GALEON_H, "Lagoon", CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
            FantomMakeCoolFighter(sld, 35, 90, 50, BLADE_LONG, "pistol3", 150);
			sld.greeting = "Gr_HeadPirates";
            LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			sld.RebirthPhantom = true; //не тереть фантома после смерти.
           	LAi_SetHuberType(sld);
        	LAi_SetLoginTime(sld, 0.0, 24.0);
        	LAi_SetHP(sld, 180.0, 180.0);
            ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "sit", "sit1");
            LAi_LocationFightDisable(&Locations[FindLocation("PortSpein_houseF2")], true);
            // ==>  Даём ноду доступа к квестам Джону Моррису
            QuestSetCurrentNode("John Morris", "EngLine_quests");
            // ==>  Даём ноду доступа к квестам Джекмену
            QuestSetCurrentNode("Jackman", "EngLine_quests");
            // ==>  Даём ноду доступа к квестам Манфсфилду
            QuestSetCurrentNode("Edward Mansfield", "EngLine_quests");
            // ==>  Оформляем счётчик посещения корсаров, в итоге должен == 4
            pchar.questTemp.Count = "0";
        break;

        case "Step_2_3":
            dialog.text = "Do you think anything can be changed in the future?";
            link.l1 = "It's hard to say, but I don't think so, sir. You can't convince all four of them for sure.";
            link.l1.go = "Step_2_4";
        break;

        case "Step_2_4":
            if (GetQuestPastDayParam("questTemp") < 35)
            {
                dialog.text = "Hmm, I see. Well, despite the negative result of the mission, I am pleased with your promptness and diligence. You are entitled to 15,000 rewards. I hope I can use your services from now on?";
                link.l1 = "Of course, sir. I will "+ GetSexPhrase("glad","glad") +"to help you.";
                AddMoneyToCharacter(pchar, 15000);
				ChangeCharacterReputation(pchar, 3);
				AddCharacterExpToSkill(pchar, "Repair", 150);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddTitleNextRate(sti(NPChar.nation), 2);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
            }
            else
            {
                dialog.text = "I am extremely disappointed, the order of the British government will not be executed. This is bad, and besides, you were not quick enough in completing this task. You have spent " +
                                GetQuestPastDayParam("questTemp") + " days! Payment will be appropriate, that is low.";
                link.l1 = "Well, you know better.";;
                AddMoneyToCharacter(pchar, 800);
				ChangeCharacterReputation(pchar, 1);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
            }
            link.l1.go = "exit";
			//слухи
			AddSimpleRumour("You know, Captain " + GetFullName(pchar) + " "+ GetSexPhrase("worked","worked") +"at Madiford's beck and call - "+ GetSexPhrase("hung around","hung around") +"all over the Caribbean from end to end, even to Morgan "+ GetSexPhrase("visited","visited") +"...", ENGLAND, 5, 1);
            DeleteAttribute(pchar, "questTemp.Count");
            pchar.questTemp.State = "empty";
            AddQuestRecord("Eng_Line_2_Talking", "6");
			AddQuestUserData("Eng_Line_2_Talking", "sSex", GetSexPhrase("","a"));
            CloseQuestHeader("Eng_Line_2_Talking");
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "70";    // Чтобы Мэдифорд дал квест №4 через 70 дней, даже если ГГ не зашёл к Моргану
            // ==> Моргана - в резиденцию на Ямайке
            LAi_SetHuberType(characterFromID("Henry Morgan"));
            QuestSetCurrentNode("Henry Morgan", "hot_business");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
        break;

        case "Step_4_0":
            dialog.text = "In order to facilitate the execution of the assignment, I am giving you a license from the Dutch West India Company for a period of 15 days, which will allow you to safely enter the city. Proceed immediately.";
            link.l1 = "Okay, sir.";
            link.l1.go = "exit";
			GiveNationLicence(HOLLAND, 15);
			pchar.questTemp.State = "Intelligence_Curacao_tavern";
			SetQuestHeader("Eng_Line_4_Intelligence_Curacao");
			AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "1");
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex1", GetSexPhrase("k","ca"));
			SaveCurrentQuestDateParam("questTemp");
		break;

        case "Step_4_1":
            dialog.text = "This is very bad, I'm disappointed in you. You can come here later, when I manage to get the information I need.";
            link.l1 = "Of course, sir. Sorry for not "+ GetSexPhrase("could","could") +"to help you.";
            link.l1.go = "exit";
			TakeNationLicence(HOLLAND);
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "30";    //только через месяц следующий квест, т.к. Мэдифорд будет добывать инфу без участия ГГ
			AddCharacterExpToSkill(pchar, "Sailing", -140);
			AddCharacterExpToSkill(pchar, "Sneak", -180);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//слухи
			AddSimpleRumour("They say that you were unable to conduct reconnaissance in Curacao. Hmm, wow...", ENGLAND, 5, 1);
        break;

        case "Step_4_2":
            dialog.text = "Did you manage to get hold of the document itself?! Fine, I was not mistaken about you\n"+
                          "However, the Dutch have found out about our plans... I'm asking you to come to my place a little later, I have to think about it. For a perfectly completed task, you are entitled to a reward of 100,000.";
            link.l1 = "Sir, I had to bribe a usurer in Willemstad. The amount of the bribe is just one hundred thousand. With this reward, you will only compensate my expenses.";
            link.l1.go = "Step_4_3";
        break;

        case "Step_4_3":
            dialog.text = "Well, then I give you 110000, I'll arrange it. Now leave me alone for a while. Please come and see me in a couple of days.";
            link.l1 = "Thank you very much, sir. I won't fail to look in later.";
            link.l1.go = "exit";
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "10");
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("","a"));
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "2";
            AddMoneyToCharacter(pchar, 110000);
			AddCharacterExpToSkill(pchar, "Sailing", 250);
			AddCharacterExpToSkill(pchar, "Sneak", 170);
			AddCharacterExpToSkill(pchar, "Grappling", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			TakeItemFromCharacter(pchar, "letter_open");
			BackItemDescribe("letter_open");
			TakeNationLicence(HOLLAND);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour("They say that you infiltrated Willemstad and managed to find out all the Dutch secrets. I believe that now we will be better prepared for the impending war...",ENGLAND, 5, 1);
        break;

        case "Step_4_4":
            dialog.text = "The fact that you have been in a Dutch prison does not bother me much. I need information, and you don't have it. I'm disappointed. You can come here later, when I manage to get the information I need.";
            link.l1 = "Of course, sir. Sorry for not "+ GetSexPhrase("could","could") +"to help you.";
            link.l1.go = "exit";
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "30";    // только через месяц следующий квест, т.к. Мэдифорд будет добывать инфу без участия ГГ
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "Leadership", -150);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//слухи
			AddSimpleRumour("They say that you managed to visit a Dutch prison. Well, how are there rats?", ENGLAND, 5, 1);
        break;

        case "Step_4_5":
            dialog.text = "You showed a good side of yourself as a warrior, but where cunning is required, you could not cope\n"+
                          "I will need to get the information I need through other people, and when I get it, I may need you.";
            link.l1 = "Understood, sir. Sorry for not "+ GetSexPhrase("could","could") +"to help you.";
            link.l1.go = "exit";
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
			TakeNationLicence(HOLLAND);
            pchar.questTemp.Waiting_time = "30";    // только через месяц следующий квест, т.к. Мэдифорд будет добывать инфу без участия ГГ
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "Fencing", -300);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//слухи
			AddSimpleRumour("They say you made a good mess in Willemstad...", ENGLAND, 5, 1);
        break;

        case "Step_5_1":
            dialog.text = "Well, now we have information that the Dutch are hastily trying to strengthen their settlement in Jamaica - Fort Orange. In principle, the fact that they settled on the other side of the island was not a problem for me, but only until the trade war began\n"+
                          "Now it is my duty to ruin the Dutch settlement on English territory. I'm entrusting this to you\n"+
                          "The entire captured prize at Fort Orange is yours. Take action.";
            link.l1 = "Very good, sir.";
            link.l1.go = "exit";
         	pchar.GenQuestBox.Trinidad_Cave = true;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry3 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry4 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry5 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry7 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry8 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry10 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry14 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry17 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.cirass3 = 1;
			//locations[FindLocation("FortOrange_townhall")].models.day.charactersPatch = "SmallResidence_BoxPatch";
			pchar.questTemp.State = "AttackFortOrange_GoToFort";
            SetQuestHeader("Eng_Line_5_AttackFortOrange");
            AddQuestRecord("Eng_Line_5_AttackFortOrange", "1");
            LAi_LocationFightDisable(&Locations[FindLocation("FortOrange_townhall")], false);
			
            Pchar.quest.AttackFortOrange_GoToFort.win_condition.l1 = "location";
            Pchar.quest.AttackFortOrange_GoToFort.win_condition.l1.location = "FortOrange_ExitTown";
            Pchar.quest.AttackFortOrange_GoToFort.win_condition = "AttackFortOrange_GoToFort";
			
			Pchar.quest.AttackFortOrange_GoToPort.win_condition.l1 = "location";
            Pchar.quest.AttackFortOrange_GoToPort.win_condition.l1.location = "FortOrange_port";
            Pchar.quest.AttackFortOrange_GoToPort.win_condition = "AttackFortOrange_GoToPort";
            SetLocationCapturedState("FortOrange_town", true);
        break;

        case "Step_5_2":
            dialog.text = "Yes, I would like to see the fort right after your work... Your appearance alone is worth something - just a demon in the flesh!\n"+
                          "I sincerely respect the brave privateers who are not afraid to pour streams of red... Glory to the heroes!\n"+
                          "I hope to see you at my place more often, "+ GetSexPhrase("my friend","" + pchar.name + "") +".";
            link.l1 = "Undoubtedly, sir, you will see me periodically... I am a privateer, and the friendship of Sir Thomas Madiford is worth a lot. And now let me take my leave - business...";
            link.l1.go = "Step_5_3";
        break;

        case "Step_5_3":
            dialog.text = ""+ GetSexPhrase("Well, I understand... Apparently, a girl is moaning somewhere in anticipation of your appearance... Haha","Well, I understand") +"\n"+
                          ""+ GetSexPhrase("My friend, I sincerely wish you to have a good time, with the same payload, so to speak... A talented person is talented in everything","" + pchar.name + ", I sincerely wish you a good time") +"\n"+
                          "Well, I won't keep you. See you later...";
            link.l1 = "Goodbye, sir.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            CloseQuestHeader("Eng_Line_5_AttackFortOrange");
            pchar.questTemp.CurQuestNumber = "6";
            pchar.questTemp.Waiting_time = "30"; // По идее геймер должен испытывать угрызения совести после этого задания. Пусть поболтается просто так с месяц.
            // ==> вертаем разграбленному Форт Оранжу нормальную жизнь.
            SetLocationCapturedState("FortOrange_town", false);
            LAi_LocationFightDisable(&Locations[FindLocation("FortOrange_townhall")], true);
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");
			//<-- огонь и пламень
			//locations[FindLocation("FortOrange_townhall")].models.day.charactersPatch = "SmallResidence_patch";
			AddCharacterExpToSkill(pchar, "Pistol", 250);
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Repair", 350);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour("What you've done at Fort Orange is, you know, impressive... The unfortunate Dutch...", ENGLAND, 5, 1);
			
			//******Чёрный Ёж Sinistra******
			//Кристофер
			/*sld = GetCharacter(NPC_GenerateCharacter("BlackYosh_Kristofer", "sold_eng_2", "man", "man", 10, ENGLAND, -1, false));
			FantomMakeCoolFighter(sld, sti(pchar.rank), 15, 15, "blade7", "", 0);
			sld.name	= "Christopher";
			sld.lastname	= "Clayston";
			sld.Dialog.Filename = "Quest\PDM\Black_Yosh.c";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld,"PortRoyal_tavern","sit","sit3");*/
        break;

        case "Step_6_1":
            dialog.text = "Well, that's good. So, he is coming after a successful campaign against the Spaniards, with a cargo of mahogany, silver and indigo in his hold\n"+
                          "He needs to sell the trophies, let him come to Port Royal for these purposes. Give him personally my permission to sell the prize in the English colony\n"+
                          "Yes, and I want you to tell Williams that in private.";
            link.l1 = "Nothing is easier.";
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_GoToMorrisBegin";
            SetQuestHeader("Eng_Line_6_MorrisWillams");
            AddQuestRecord("Eng_Line_6_MorrisWillams", "1");

			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1.location = "Jamaica";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition = "MorrisWillams_ShipToPort";
        break;

        case "Step_6_2":
            dialog.text = "I have already been informed. Here's 5,000 for your trouble.";
            link.l1 = "It didn't take me any trouble, but I won't give up the money.";
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ModifordGood5000";
            AddMoneyToCharacter(pchar, 5000);
            AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "3");
            group_DeleteGroup("Willams_Group");

			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1.location = Pchar.location.from_sea;
			Pchar.quest.MorrisWillams_ShipToPort.win_condition = "MorrisWillams_MeetWithManFromWillams";
        break;

        case "Step_6_3":
            dialog.text = "What kind of manners? What's the matter?";
            link.l1 = "You have confiscated the cargo of the privateer Morris Williams! And his "+ GetSexPhrase("invited","invited") +"I'm going to Port Royal!";
            link.l1.go = "Step_6_4";
        break;

        case "Step_6_4":
            dialog.text = "Not you, but I invited him to Port Royal. You were acting as a messenger, nothing more. As for the cargo, it has been returned to the Spanish owner.";
            link.l1 = "I don't believe my ears! Why?!!";
            link.l1.go = "Step_6_5";
        break;

        case "Step_6_5":
            dialog.text = "Relations between England and Spain are improving. It's a gesture of goodwill\n"+
                          ""+ GetSexPhrase("My friend","" + pchar.name + "") +", don't get into politics, you can't change anything. Goodbye.";
            link.l1 = "I just don't have the words... Well, goodbye, sir.";
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ModifordPolitic";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "5");
            QuestSetCurrentNode("Morris_Willams", "First time");
			//слухи
			AddSimpleRumour("Captain, did you really set up poor Williams like that?! No one thought that you were capable of such a thing...", ENGLAND, 5, 1);
        break;

        case "Step_6_6":
            dialog.text = "What happened, "+ GetSexPhrase("my friend","" + pchar.name + "") +"?";
            link.l1 = "Morris Williams is languishing in prison, and it's my fault. I consider it extremely necessary to release him.";
            link.l1.go = "Step_6_7";
        break;

        case "Step_6_7":
            dialog.text = "Well, I see that you are a noble man. I also don't enjoy keeping a good privateer in custody, but I have to do it. The law is the law\n"+
                          "I advise you to contact a local usurer, it is because of non-payment of a debt to him that Morris is in prison.";
            link.l1 = "Thanks for the advice.";
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ArrestedToUsurer";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "17");
        break;

        case "Step_7_1":
            dialog.text = "The fact is that the English corsairs stopped coming in with the prize goods captured from the Spaniards. They now only come in for repairs with the minimum amount of money needed.\n"+
                          "I hope you don't need to explain how much England loses every month on non-payment of a ten percent duty on the size of the seized cargo, and how much Jamaican merchants lose!!!\n"+
                          "Corsairs now either hide cargoes in secluded places on the islands, or try to drag themselves to Portsmouth and sell goods there, or sell captured cargoes through French intermediaries on Tortuga.\n"+
                          "That is, the situation is clear as day: the campaigns against the Spaniards continue, and we get NOTHING from it!\n"+
                          "The Council of Jamaica has decided to resume the distribution of letters of marque for our corsairs. Your assignment is very delicate and consists in the following: I have learned that seven famous corsairs have hidden gold in caves all over the region.\n"+
                          "I became aware of the approximate storage locations of the treasures:\n"+
                          "1. Thomas Wheatson - near Cartagena.\n"+
                          "2. Adrian Swart on the island of Trinidad.\n"+
                          "3. Captain Gay is on Turks Island.\n"+
                          "4. Captain Cooper is on the island of Dominica.\n"+
                          "5. George Brennenham on Cayman Island.\n"+
                          "6. Captain Goodley is on Cuba.\n"+
                          "7. Abraham Blauvelt in on Guadeloupe.\n"+
                          "Find all these treasures and deliver them to me. I think it would be superfluous to say that the mission is strictly secret, it is in your interests...";
            link.l1 = "I understand. I believe I can resolve this issue, sir.";
            link.l1.go = "Step_7_3";
            link.l2 = "Sir, I don't really understand the nature of the assignment. The treasures of the corsairs are their own business. I had nothing to do with it...";
            link.l2.go = "Step_7_2";
        break;

        case "Step_7_2":
            dialog.text = "I am very puzzled by your behavior...";
            link.l1 = "Sir, I'm sorry, but I can't help you.";
            link.l1.go = "exit";
            ChangeCharacterReputation(pchar, 3);
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "8";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "35";
            AddCharacterExpToSkill(pchar, "Leadership", -500);
            AddCharacterExpToSkill(pchar, "Cannons", -300);
            AddCharacterExpToSkill(pchar, "Sneak", -350);
			//слухи
			AddSimpleRumour("You know, Captain " + GetFullName(pchar) + " "+ GetSexPhrase("refused","refused") +"to carry out Madiford's assignment to search for pirate stashes...", ENGLAND, 5, 1);
        break;

        case "Step_7_3":
            dialog.text = "According to my estimates, there are 2,100 bars of gold in all seven treasures! Bring it all to me...";
            link.l1 = "Okay, sir. I'm starting immediately.";
            link.l1.go = "exit";
            ChangeCharacterReputation(pchar, -4);
            pchar.questTemp.State = "SevenTreasures_GoOn";
            pchar.questTemp.GoldQtyGaveModiford = "0"; // кол-во сданное Мэдифорду
            pchar.questTemp.GoldQtyForSeek = "2100"; // кол-во, которое ещё нужно разыскать
            SaveCurrentQuestDateParam("questTemp");
            SetQuestHeader("Eng_Line_7_SevenTresures");
            AddQuestRecord("Eng_Line_7_SevenTresures", "1");
            // ==> клад Томаса Уитсона в пещере близ Картахены.
         	pchar.GenQuestBox.Cartahena_Cave = true;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.jewelry5 = 300;
			pchar.GenQuestBox.Cartahena_Cave.box1.items.jewelry1 = 110;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.statue1 = 1;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.indian17 = 1;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.pistol2 = 1;
			pchar.GenQuestBox.Cartahena_Cave.box1.items.icollection = 1;
            // ==> клад Адриана Сварта на Тринидаде.
         	pchar.GenQuestBox.Trinidad_Grot = true;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.jewelry5 = 450;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.blade5 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.potion2 = 10;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.potionwine = 3;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.jewelry2 = 90;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian6 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian11 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian15 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian12 = 1;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.chest = 1;
            // ==> клад Капитана Гея в гроте на Терксе.
         	pchar.GenQuestBox.Terks_Grot = true;
            pchar.GenQuestBox.Terks_Grot.box1.items.jewelry5 = 250;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry3 = 85;
            pchar.GenQuestBox.Terks_Grot.box1.items.blade10 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.potion2 = 5;
            pchar.GenQuestBox.Terks_Grot.box1.items.indian18 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.jewelry7 = 5;
            // ==> клад Капитана Купера на Домнинике.
         	pchar.GenQuestBox.Dominica_Grot = true;
            pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry5 = 150;
			pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry4 = 75;
            pchar.GenQuestBox.Dominica_Grot.box1.items.pistol10 = 1;
            pchar.GenQuestBox.Dominica_Grot.box1.items.potion1 = 5;
            pchar.GenQuestBox.Dominica_Grot.box1.items.potionrum = 2;
			pchar.GenQuestBox.Dominica_Grot.box1.items.chest = 1;
            // ==> клад Джоржа Бренинхема на Каймане.
         	pchar.GenQuestBox.Caiman_Grot = true;
            pchar.GenQuestBox.Caiman_Grot.box1.items.jewelry5 = 350;
			pchar.GenQuestBox.Caiman_Grot.box1.items.jewelry17 = 250;
            pchar.GenQuestBox.Caiman_Grot.box1.items.blade2 = 1;
            pchar.GenQuestBox.Caiman_Grot.box1.items.potion5 = 10;
            pchar.GenQuestBox.Caiman_Grot.box1.items.indian18 = 1;
            // ==> клад капитана Гудли на Кубе.
         	pchar.GenQuestBox.Cuba_Grot = true;
            pchar.GenQuestBox.Cuba_Grot.box1.items.jewelry5 = 350;
			pchar.GenQuestBox.Cuba_Grot.box1.items.jewelry17 = 150;
            pchar.GenQuestBox.Cuba_Grot.box1.items.topor2 = 1;
            pchar.GenQuestBox.Cuba_Grot.box1.items.potion2 = 5;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian10 = 1;
			pchar.GenQuestBox.Cuba_Grot.box1.items.chest = 3;
            // ==> клад Абрахама Блаувельта в катакомбах Гаити рядом с городом.
         	pchar.GenQuestBox.Guadeloupe_Cave = true;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry5 = 250;
			pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry17= 100;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry14= 10;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.potion3 = 5;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.mineral8 = 1;
			pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry5 = 250;
			pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry2 = 50;
            pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry14= 10;
            pchar.GenQuestBox.Guadeloupe_Cave.box4.items.potion3 = 5;
            pchar.GenQuestBox.Guadeloupe_Cave.box4.items.mineral8 = 1;
        break;

        case "Step_7_4":
            dialog.text = "So, let's see...";
            link.l1 = "So, sir, I have " + pchar.items.jewelry5 + " gold bars now. I'm ready to hand it over to you.";
            link.l1.go = "Step_7_5";
            link.l2 = "Sir, I have " + pchar.items.jewelry5 + " gold bars with me. But this gold became mine not as a result of the task you set. So I'm keeping this gold for myself.";
            link.l2.go = "Step_7_7";
        break;

        case "Step_7_5":
            if ((sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5)) <= 2100)
            {
                pchar.questTemp.GoldQtyGaveModiford = sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5);
                pchar.questTemp.GoldQtyForSeek = 2100 - sti(pchar.questTemp.GoldQtyGaveModiford);
                if (pchar.questTemp.GoldQtyForSeek != "0")
                {
                    dialog.text = "Very good, I accept " + pchar.items.jewelry5 + " gold bars from you. In total, you gave me " + pchar.questTemp.GoldQtyGaveModiford + " gold bars. Accordingly, it remains for you to find and deliver to me " + pchar.questTemp.GoldQtyForSeek + " bars more.";
                    link.l1 = "I understand, sir. The search will continue.";
                    link.l1.go = "exit";
                    AddQuestRecord("Eng_Line_7_SevenTresures", "3");
                    AddQuestUserData("Eng_Line_7_SevenTresures", "GoldQtyGaveModiford", pchar.questTemp.GoldQtyGaveModiford);
                    AddQuestUserData("Eng_Line_7_SevenTresures", "GoldQtyForSeek", pchar.questTemp.GoldQtyForSeek);
                }
                else
                {
                    dialog.text = "You have completed the task. You have delivered and handed over to me, as I expected, 2,100 gold bars. Your 10 percent is 70 thousand.";
                    link.l1 = "Thank you, sir.";
                    link.l1.go = "Step_7_6";
                }
                DeleteAttribute(pchar, "items.jewelry5");
            }
            else
            {
                pchar.questTemp.GoldQtyForSeek = sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5) - 2100);
                dialog.text = "Wow, you found more gold than I expected! You have now " + pchar.items.jewelry5 + " gold bars. Before that, you gave me " + pchar.questTemp.GoldQtyGaveModiford + " gold bars. Accordingly, overfulfilling the plan by " + pchar.questTemp.GoldQtyForSeek + " bars.";
                link.l1 = "Sir, 'overfulfilling the plan' is my personal gold, it has nothing to do with the completed task.";
                link.l1.go = "Step_7_6";
                pchar.items.jewelry5 = pchar.questTemp.GoldQtyForSeek;
            }
        break;

        case "Step_7_6":
            dialog.text = "Well, I am very, very pleased with you. Our cooperation is very pleasant for me. I will always be glad to see you at my place.";
            link.l1 = "Thank you, sir. I will visit you periodically.";
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, 70000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "2";
            AddQuestRecord("Eng_Line_7_SevenTresures", "2");
            CloseQuestHeader("Eng_Line_7_SevenTresures");
            DeleteQuestHeader("Eng_Line_7_Second");
            DeleteAttribute(pchar, "questTemp.GoldQtyGaveModiford");
            DeleteAttribute(pchar, "questTemp.GoldQtyForSeek");
			AddCharacterExpToSkill(pchar, "Repair", 500);
			AddCharacterExpToSkill(pchar, "Commerce", 550);
			AddCharacterExpToSkill(pchar, "Defence", 450);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour("There are vague rumors that a certain captain helped Madiford to rob the treasures of some pirates. But it's Madiford's own fault that the privateers began to hide their loot in caves and grottoes...", ENGLAND, 5, 1);
        break;

        case "Step_7_7":
            dialog.text = RandPhraseSimple("And then why the hell are you shaking it in front of my eyes?", "From now on, I ask you to talk only about MY gold.");
            link.l1 = "Sir, you asked me - I told you"+ GetSexPhrase("answered","answered") +" as is. Please excuse me.";
            link.l1.go = "exit";
        break;

        case "Step_7_10":
			dialog.text = "Hmm, I do not recommend you to express your thoughts in this tone here. I am disappointed with you and I am imposing a fine on you!I'm not detaining you anymore, you can go.";
            link.l1 = "I'm sorry "+ GetSexPhrase("delivered","delivered") +"it's inconvenient for you, sir.";
            link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuestBox.Cartahena_Cave");
			DeleteAttribute(pchar, "GenQuestBox.Trinidad_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Terks_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Dominica_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Caiman_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Cuba_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Guadeloupe_Cave");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "20";
            AddQuestRecord("Eng_Line_7_SevenTresures", "4");
			AddQuestUserData("Eng_Line_7_SevenTresures", "sSex", GetSexPhrase("xia","as"));
            CloseQuestHeader("Eng_Line_7_SevenTresures");
            DeleteQuestHeader("Eng_Line_7_Second");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			ChangeCharacterReputation(pchar, -5);
			AddMoneyToCharacter(pchar, -150000);
        break;

        case "Step_8_1":
            dialog.text = "Exactly! Well, so much the better\n"+
                          "Mansfield has prepared a large sum of gold bars for us. I need to get this gold to Port Royal. I can only entrust this matter to you.";
            link.l1 = "Okay, sir. Am I limited in time?";
            link.l1.go = "Step_8_2";
        break;

        case "Step_8_2":
            dialog.text = "No, there's not much hurry. But it's not worth dragging it out either.";
            link.l1 = "Understood. As soon as I am ready, I will immediately go to sea.";
            link.l1.go = "exit";
            pchar.questTemp.State = "ToMansfield_GoOn";
            SetQuestHeader("Eng_Line_8_ToMansfield");
            AddQuestRecord("Eng_Line_8_ToMansfield", "1");
            Pchar.quest.ToMansfield_IntoTheTown.win_condition.l1 = "location";
            Pchar.quest.ToMansfield_IntoTheTown.win_condition.l1.location = "LaVega_town";
            Pchar.quest.ToMansfield_IntoTheTown.win_condition = "ToMansfield_IntoTheTown";
            SetLocationCapturedState("LaVega_town", true);
			//--> огонь и пламень
			locations[FindLocation("LaVega_town")].hidden_effects = true;
			locations[FindLocation("LaVega_ExitTown")].hidden_effects = true;
			//<-- огонь и пламень
            Log_QuestInfo("The Buccaneer fort is empty and burning.");
        break;

        case "Step_8_3":
            dialog.text = "Damn it!!! Have you managed to clarify the situation in any way?";
            link.l1 = "It seems that the Spaniards went to Santiago. I'll try to intercept them.";
            link.l1.go = "Step_8_4";
        break;

        case "Step_8_4":
            dialog.text = "Very good. I ask you to do your best to search.";
            link.l1 = "Understood, sir.";
            link.l1.go = "exit";
            npchar.TempQuest.KnowAboutModiford = 1;
        break;

        case "Step_8_5":
            dialog.text = "I need to think about it. Come see me in ten days.";
            link.l1 = "Okay, sir.";
            link.l1.go = "exit";
            TakeItemFromCharacter(pchar, "letter_open");
			BackItemDescribe("letter_open");
            DeleteAttribute(npchar, "TempQuest.KnowAboutModiford");
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "9";
            pchar.questTemp.Waiting_time = "10";
            CloseQuestHeader("Eng_Line_8_ToMansfield");
            SetLocationCapturedState("LaVega_town", false);
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("LaVega_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("LaVega_ExitTown")], "hidden_effects");
			//<-- огонь и пламень
            // ==> Мэнсфилд убит, теперь он будет Алистером Гудом.
            sld = characterFromID("Edward Mansfield");
            LAi_SetStayTypeNoGroup(sld);
            sld.model = "bocman";
        	sld.name 	= "Alistair";
        	sld.lastname = "Gud";
            SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            FaceMaker(sld);
            QuestSetCurrentNode("Edward Mansfield", "No_Mansfield_first_time");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Edward Mansfield")], "LaVega_townhall", "sit", "sit1");
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			AddCharacterExpToSkill(pchar, "Sailing", 550);
			AddCharacterExpToSkill(pchar, "FencingLight", 450);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour("There are rumors that the Buccaneer settlement in Hispaniola was ravaged by the Spaniards...", ENGLAND, 5, 1);
		break;

        case "Step_9_1":
            pchar.questTemp.State = "AttackSantiago_GoOn";
            if (!CheckAttribute(npchar, "TempQuest.KindResult")) // письмо не получено, но в курсе нападения испанцев
            {
                dialog.text = "I took certain actions and I managed to establish exactly who was behind the Spanish attack on La Vega.";
                link.l1 = "And who is it?";
                link.l1.go = "Step_9_2";
            }
            else if (npchar.TempQuest.KindResult == 2) // признак результата завершения квеста, 2 == вообще не в курсе, что произошло
            {
                dialog.text = "I would like to inform you that the massacre in La Vega was the result of an attack by the Spaniards.";
                link.l1 = "I see, sir.";
                link.l1.go = "Step_9_2";
            }
            else // признак результата завершения квеста, 1 == было захвачено письмо
            {
                dialog.text = "Thanks to the letter you found on the Spanish galleon, we can now clearly imagine who is behind the Spanish attack on La Vega.";
                link.l1 = "Yes, sir. The letter I "+ GetSexPhrase("read","read") +".";
                link.l1.go = "Step_9_2";
            }
            Log_QuestInfo("The task has been received.");
            DeleteAttribute(npchar, "TempQuest.KindResult");
			characters[GetCharacterIndex("Santiago_Mayor")].dialog.captureNode = "EL9_SantiagoAttack"; //капитулянтская нода мэра
        break;

        case "Step_9_2":
            dialog.text = "This attack was organized by Santiago Governor Jose Sancho Jimenez. To carry out this operation, he enlisted Manoel Rivero Pardal, the only Spanish pirate in these waters.";
            link.l1 = "What do I need to do?";
            link.l1.go = "Step_9_3";
        break;

        case "Step_9_3":
            dialog.text = "You need to attack Santiago and deliver Governor Jose Sancho Jimenez to me. I need Jimenez, the city is yours.";
            link.l1 = "I understand, sir.";
            link.l1.go = "exit";
            SetQuestHeader("Eng_Line_9_AttackSantiago");
            AddQuestRecord("Eng_Line_9_AttackSantiago", "1");
        break;

        case "Step_9_4":
            dialog.text = "Damn it, you really are an indispensable person, " + pchar.name + ". Mansfield has been gloriously avenged!";
            link.l1 = "What should I do with Jimenez?";
            link.l1.go = "Step_9_5";
            QuestSetCurrentNode("Santiago_Mayor", "First time");
        break;

        case "Step_9_5":
            dialog.text = "Hand it over to my duty officer. I'll take care of it tomorrow, today I'm in too good a mood for that\n"+
                          "I think you need to rest and get yourself in order after such significant achievements. I dare not detain you, come to me at any time\n"+
                          "Yes, and one more thing... Go to Morgan, I think he will be very pleased to know that the revenge for Edward Mansfield was accomplished so quickly and effectively. Mansfield was like a father to Morgan...";
            link.l1 = "Okay, sir. I will definitely come in.";
            link.l1.go = "exit";
            QuestSetCurrentNode("Henry Morgan", "Give_blade");
            sld = characterFromID("Himenes");
            RemovePassenger(pchar, sld);
    	    sld.LifeDay = 1; // уберём нпс на след.день.
    	    SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
            pchar.questTemp.Waiting_time = "20";
            CloseQuestHeader("Eng_Line_9_AttackSantiago");
			AddCharacterExpToSkill(pchar, "Repair", 550);
			AddCharacterExpToSkill(pchar, "Cannons", 760);
			AddCharacterExpToSkill(pchar, "Defence", 450);
			AddCharacterExpToSkill(pchar, "Pistol", 300);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour("Captain, everyone is talking about the fact that you have brought a captive Spanish governor to Port Royal! You "+ GetSexPhrase("real hero","real heroine") +", Captain...", ENGLAND, 5, 1);
        break;

        case "Step_10_1":
            dialog.text = "The Spaniards decided to just end us. To assemble such a large number of battleships here is simply incredible! But we've dealt with them!";
            link.l1 = "Yes, sir. Although it was extremely difficult, nevertheless, the townspeople can breathe easy. And the Spaniards, I suppose, are unlikely to recover from such a blow...";
            link.l1.go = "Step_10_2";
        break;

        case "Step_10_2":
            dialog.text = "I agree with you, "+ GetSexPhrase("my friend","" + pchar.name + "") +". I believe that the sum of 80,000 will be enough to put your ships in order and recruit a new team. England needs you, "+ GetSexPhrase("my friend","" + pchar.name + "") +", and England will not forget you!"+
                          "I'm sorry, but right now I need to think about retaliatory measures... Please come and see me in a week.";
            link.l1 = "Okay, I'll try to be there on time, sir.";
            link.l1.go = "exit";
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
            pchar.questTemp.Waiting_time = "7";
            CloseQuestHeader("Eng_Line_10_SpanishAttack");
			AddCharacterExpToSkill(pchar, "Repair", 600);
			AddCharacterExpToSkill(pchar, "Leadership", 550);
			AddCharacterExpToSkill(pchar, "Commerce", 600);
			AddCharacterExpToSkill(pchar, "Accuracy", 400);
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddMoneyToCharacter(pchar, 80000);
			//слухи
			AddSimpleRumour("Captain, you just saved us all. The residents of the city are grateful to you as one for your feat.", ENGLAND, 10, 6);
        break;

        case "Step_11_1":
            dialog.text = "The response to the Spanish attack on Port Royal will be our attack on the Spanish cities.\n"+
                          "There are two Spanish cities on the continent next to Trinidad: Cumana and Caracas. Capture these cities and bring the population under oath to His Majesty Charles II Stuart.\n"+
                          "Facilitate the appointment of a new administration to normalize urban governance and collect taxes and duties as soon as possible.";
            link.l1 = "I understand, sir. I'll start as soon as I'm ready.";
            link.l1.go = "exit";
            SetQuestHeader("Eng_Line_11_OccupyMein");
            AddQuestRecord("Eng_Line_11_OccupyMein", "1");
            pchar.questTemp.State = "OccupyMein_GoOn";
			characters[GetCharacterIndex("Cumana_Mayor")].dialog.captureNode = "EngLine11Quest_OccupyMein"; //капитулянтская нода мэра
			characters[GetCharacterIndex("Caracas_Mayor")].dialog.captureNode = "EngLine11Quest_OccupyMein"; //капитулянтская нода мэра
        break;

        case "Step_11_2":
            dialog.text = "Excellent, "+ GetSexPhrase("my friend","" + pchar.name + "") +". It's just great! The loot captured on the island rightfully belongs to you!"+
                          " I ask you to be at my residence in a month. I'll have a case for you again.";
            link.l1 = "Okay, sir.";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Q11_Cumana");
            DeleteAttribute(pchar, "questTemp.Q11_Caracas");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
            pchar.questTemp.Waiting_time = "30";
            CloseQuestHeader("Eng_Line_11_OccupyMein");
			AddCharacterExpToSkill(pchar, "Repair", 1000);
			AddCharacterExpToSkill(pchar, "Commerce", 1600);
			AddCharacterExpToSkill(pchar, "Accuracy", 1000);
			AddCharacterExpToSkill(pchar, "Defence", 1100);
			AddCharacterExpToSkill(pchar, "Cannons", 1300);
			AddCharacterExpToSkill(pchar, "Sailing", 1200);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour("Captain, it looks like you'll be getting a nickname soon " + pchar.name + ""+ GetSexPhrase("-Conqueror","-Conqueror") +"", ENGLAND, 5, 1);
        break;

        case "Step_12_1":
            dialog.text = "Something unusual is happening in St. John's. I do not receive the required status notifications from the governor of the city\n"+
                          "You are my confidant, so I ask you to go to the St. Johns residence and clarify the situation with the governor.";
            link.l1 = "Okay, sir. I don't think there are any problems, but I'll find out everything.";
            link.l1.go = "exit";
            SetQuestHeader("Eng_Line_12_ColonelLinch");
            AddQuestRecord("Eng_Line_12_ColonelLinch", "1");
            pchar.questTemp.State = "ColonelLinch_GoToKingstown";

            Pchar.quest.ColonelLinch_IntoTheResidence.win_condition.l1 = "location";
            Pchar.quest.ColonelLinch_IntoTheResidence.win_condition.l1.location = "SentJons_townhall";
            Pchar.quest.ColonelLinch_IntoTheResidence.win_condition = "ColonelLinch_IntoTheResidence";
        break;

        case "Step_12_2":
            dialog.text = "Hmm... So what?";
            link.l1 = "By order of the British government, you are under arrest, sir...";
            link.l1.go = "Step_12_3";
        break;

        case "Step_12_3":
            dialog.text = "Not so fast... Officer, come to me!!!";
            link.l1 = "Damn it!!!";
            link.l1.go = "Step_12_4";
        break;

        case "Step_12_4":
            pchar.nation = PIRATE;
            LAi_SetImmortal(npchar, true);
            LAi_SetImmortal(characterFromID("PortRoyal_Mayor"), true);
            bDisableFastReload = true; // закрыть переходы.
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
            LAi_NoRebirthEnable(npchar);
            //LAi_SetActorType(npchar);
            //LAi_ActorAfraid(npchar, pchar, false);

            LAi_group_Register("EnemyFight");
           	float locx, locy, locz;
            GetCharacterPos(pchar, &locx, &locy, &locz);
			//поставим стражников во враждебную группу
			int num = FindNearCharacters(pchar, 20.0, -1.0, -1.0, 0.01, true, true);
			if(num > 0)
			{
				for(int i = 0; i < num; i++)
				{
					int idx = sti(chrFindNearCharacters[i].index);
					sld = &Characters[idx];
					if (sld.chr_ai.type == "guardian")
					{
						LAi_NoRebirthEnable(sld);
						LAi_CharacterReincarnation(sld, false, false);
						LAi_group_MoveCharacter(sld, "EnemyFight");
					}
				}
			}
			//добавим солдат для хардокора
            string SModel;
            for (i=1; i<=3; i++)
            {
                SModel = "off_eng_"+i;
                if (i == 3) SModel = "sold_eng_3";
                sld = GetCharacter(NPC_GenerateCharacter("EngSolder"+i, SModel, "man", "man", 30, ENGLAND, 0, true));
                FantomMakeCoolFighter(sld, 30, 100, 100, "topor1", "pistol3", 250);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "PortRoyal_townhall", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ColonelLinch_AfterFight");
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
			//слухи
			AddSimpleRumour("Well, things are happening here!! Governor Madiford is arrested and imprisoned by one of his privateers! Well, that's it!..", ENGLAND, 5, 1);
        break;

        case "Step_12_5":
            dialog.text = "Don't be surprised! But let's take it all in order\n"+
                          "It is with great pleasure that I must inform you that your services to the fatherland have been duly appreciated\n"+
                          "I have the honor to announce your knighthood. From now, should always be used prefix before your name: "+ GetSexPhrase("sir","lady") +"\n"+
                          "Also, as a result of the investigation of Madiford's activities, his huge fortune was found. Some of this money belongs to you, "+ GetSexPhrase("sir","lady") + ". That's three hundred thousand. Please receive it.";
            link.l1 = "Thank you. I hope that I can continue to be useful to His Majesty as always.";
            link.l1.go = "Step_12_6";
        break;

        case "Step_12_6":
            dialog.text = "I'm counting on it.\n"+
                          "I hope that with your participation, "+ GetSexPhrase("sir","lady") +", Caribbean will become more English. And don't forget that Spain is not our enemy. So far, anyway...";
            link.l1 = "I understand, sir. I will do my best for the prosperity of the British colonies in the Caribbean.";
            link.l1.go = "exit";
			if (PChar.sex == "woman")
			{
			pchar.name = "Lady " + pchar.name;
			}
			else
			{
			pchar.name = "Sir " + pchar.name;
			}
            AddMoneyToCharacter(pchar, 300000);
            AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            SetNationRelationBoth(SPAIN, ENGLAND, RELATION_NEUTRAL);
            DeleteAttribute(pchar, "questTemp.Waiting_time");
            pchar.questTemp.State = "EndOfQuestLine";
			bWorldAlivePause   = false; // Конец линейки
			UnlockAchievement("Nation_quest_E", 3);
        break;
		
		case "BlackYosh_1":
            dialog.text = "Yes, it's true. I suppose you wanted to command one of these frigates? Alas, all positions have already been allocated.";
            link.l1 = "This is terrible, sir. But is it true that frigates are already very old, and completely unsuitable for conducting military operations?";
            link.l1.go = "BlackYosh_2";
        break;
		
		case "BlackYosh_2":
            dialog.text = "Who started such an idiotic rumor? Speak at once, or I'll have you hanged from the first yard I see!";
            link.l1 = "I'm sorry, sir, but why did my simple question cause such a reaction?";
            link.l1.go = "BlackYosh_3";
        break;
		
		case "BlackYosh_3":
            dialog.text = "A true English corsair will NEVER doubt the readiness of the fleet. You cast a shadow on me and on my competence. I ask you again, who told you that?";
            link.l1 = "I met a man in a tavern who said he had recently been assigned to one of the frigates. He complained about the condition of the ship. It seemed to me that he was completely drunk, but his words sounded true.";
            link.l1.go = "BlackYosh_4";
        break;
		
		case "BlackYosh_4":
            dialog.text = "Captain, if you drink in dirty local taverns, you may also hear less nonsense. It's a shame. You drink in a tavern with other officers, and then you come here and repeat false rumors. When I find your gossip, I'll have him molted like a common sailor!";
            link.l1 = "But, sir...";
            link.l1.go = "BlackYosh_5_VREMENAYA_ZAGLUSHKA";	//Пока квест не будет сделан, дальше пройти нельзя. Будет переход на временную заглушку.
			//link.l1.go = "BlackYosh_5";
        break;
		
		case "BlackYosh_5_VREMENAYA_ZAGLUSHKA":	//Временная заглушка
            dialog.text = "Now leave me, I need to work!";
			link.l1 = "Yes, sir, I'm leaving now.";
            link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.BlackYosh_1");
        break;
		
		case "BlackYosh_5":
            dialog.text = "Okay, since you're here, I just need a captain to escort one of these frigates to a safe place.";
            link.l1 = "Yes, sir, I'm ready to take up this case. Where do I need to escort the frigate?";
            link.l1.go = "BlackYosh_6";
			link.l2 = "Sir, I'm sorry, but I'm not ready right now.";
            link.l2.go = "exit";
			DeleteAttribute(pchar, "questTemp.BlackYosh_1");
        break;
		
		case "BlackYosh_6":
            dialog.text = "According to reports from the eastern English colonies, there are not enough ships in Bridgeout to patrol the maritime border. Therefore, the Frigate Black Hedgehog must be escorted safely to Bridgetown. Is that clear to you?";
            link.l1 = "Yes, sir, I'm going to sea today.";
            link.l1.go = "BlackYosh_7";
        break;
		
		case "BlackYosh_7":
            dialog.text = "And more. Before you set course for Bridgetown, I want you to deliver this letter to the Governor of Charlestown first. It's important!";
            link.l1 = "First the letter to Charlestown, then the 'Black Hedgehog' to Bridgetown, I remembered.";
            link.l1.go = "exit";
        break;
	// СФ
	case "SF_HuberDialogueBeginning":
    		dialog.text = "Yes, " + GetAddress_Form(pchar) + ", I've been waiting for you. I have a favor to ask of you.";
    		link.l1 = "Why me?";
    		link.l1.go = "SF_HuberDialogueExplanation";
	break;
		
	case "SF_HuberDialogueExplanation":
    		dialog.text = "It's simple. You have sunk dozens of ships, and you are not hanging on the gallows, not hiding in pirate dens, but docked freely in the main port of the Caribbean Sea. You're the best I've ever seen.";
    		link.l1 = "Is the case related to the raid at sea?";
    		link.l1.go = "SF_HuberDialogueBingo";
	break;
		
	case "SF_HuberDialogueBingo":
    		dialog.text = "Exactly! And very profitable for you.";
    		link.l1 = "State your case.";
    		link.l1.go = "SF_HuberDialogueDealDitails";
	break;
		
	case "SF_HuberDialogueDealDitails":
    		dialog.text = "Yes, you have the grip of a real sea wolf. It's a very simple matter. Our Royal Highness is sticking his nose where it doesn't belong! They've taken over the most lucrative areas with their own men from London. And that, by rights, should be my job!";
    		link.l1 = "What exactly can I do for you?";
    		link.l1.go = "SF_HuberDialogueBarbadosSilver";
	break;
		
	case "SF_HuberDialogueBarbadosSilver":
    		dialog.text = "Barbados has gigantic deposits of silver and, of course, it is being mined. Even the plantation is kept there just to hide the scale of the work, and the increased death of slaves.";
    		link.l1 = "Very interesting...";
    		link.l1.go = "SF_HuberDialogueSilverLogistic";
	break;
		
	case "SF_HuberDialogueSilverLogistic":
    		dialog.text = "All cargo from England's Caribbean colonies arrives first at Port Royal and then leaves for Europe. And Barbados is home to England's most valuable asset in the Caribbean...";
    		link.l1 = "I'm beginning to understand. You want me to intercept this particular shipment from Barbados.";
    		link.l1.go = "SF_HuberDialogueSilverIsMine";
	break;
		
	case "SF_HuberDialogueSilverIsMine":
    		dialog.text = "You've got that right. I've said many times that I don't need help from the metropolis, but they don't trust me, you see.";
    		link.l1 = "And you need to make guests from across the ocean lose confidence and make you an exceptional figure who can organize logistics correctly and safely.";
    		link.l1.go = "SF_HuberDialogueCloserToTheDeal";
	break;
		
	case "SF_HuberDialogueCloserToTheDeal":
    		dialog.text = "Shorter. There's a Silver Convoy running between Barbados and Jamaica. I need it to disappear en route, all of it. All the loot for you. Besides, if it works out and I supervise all the English shipments, a million piasters a month will fall into your deposit at the Port Royal bank. Is it a deal?";
    		link.l1 = "Deal. When does the convoy leave the port of Bridgetown?";
    		link.l1.go = "SF_HuberDialogueDealAgreed";
		link.l2 = "No. Large squadrons are not my specialty.";
    		link.l2.go = "SF_HuberDialogueNoDeal";
	break;
		
	case "SF_HuberDialogueDealAgreed":
    		dialog.text = "Well, it's not that simple. The convoy never leaves any port. One ship at a time, they gather on the high seas to form a squadron and then move on to Jamaica. The foreigners know how to hide. Besides, they have the power, and no English subject, not even my intimates, in this matter, should be asked to help me.";
    		link.l1 = "So it's only by accident? How can I guarantee a result?";
    		link.l1.go = "SF_HuberDialogueDealHelper";
		AddQuestRecord("SilverFleet", "QuestTaken");
		AddQuestUserData("SilverFleet", "sSex", GetSexPhrase("ся","ась"));
		pchar.questTemp.silverfleet = "FirstSilverFleet";
		pchar.SilverFleetAtSea = true;
	break;
		
	case "SF_HuberDialogueDealHelper":
    		dialog.text = "Don't worry. I'm not rushing you with the result - the convoy runs regularly. My old friend Le Francois, head of the pirate settlement, will help you in this endeavor. He has eyes all along the convoy route.";
    		link.l1 = "Understood. But do you have any information about the ships and the size of the squadron.";
    		link.l1.go = "SF_HuberDialogueDealMoreDitals";
	break;
		
	case "SF_HuberDialogueDealMoreDitals":
    		dialog.text = "Very little. That's why I'm not giving you a time limit. Specialists from overseas are carefully concealed. I can only say that, in contrast to the Spaniards, English squadrons necessarily contain fast and maneuverable ships.";
    		link.l1 = "It's all clear. Wait for the good news. Goodbye.";
    		link.l1.go = "exit";	
	break;
		
	case "SF_HuberDialogueNoDeal":
    		dialog.text = "Oh, yeah? I was wrong about you. That's too bad. This conversation never happened. Goodbye.";
    		link.l1 = "I understand. Goodbye.";
    		link.l1.go = "exit";
		pchar.questTemp.silverfleet = "over";
	break;
		
	case "SF_HuberDialogueThinking":
    		dialog.text = "Really? I thought you were more ambitious... Why don't you think about it?";
 		link.l2 = "Yeah, I guess I was a little hasty in saying no. Sorry for the inconvenience.";
    		link.l2.go = "exit";
		link.l1 = "That's what I thought. The decision has been made. Goodbye, sir.";
    		link.l1.go = "SF_HuberDialogueQuestCancel";
		SaveCurrentNpcQuestDateParam(NPChar, "SilverFleetCancelThinking");
	break;
		
	case "SF_HuberDialogueQuestCancel":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.silverfleet = "over";
		pchar.SilverFleetAtSea = false;
		KillHeadSilverFleet();
		AddQuestRecord("SilverFleet", "SelfCancelingQuest");
		AddQuestUserData("SilverFleet", "sSex", GetSexPhrase("","а"));
		CloseQuestHeader("SilverFleet");
		DeleteAttribute(NPChar, "SilverFleetCancelThinking");
	break;
		
	case "SF_HuberDialogueFail":
		dialog.text = "Thank you for trying. Of course, I don't owe you any money. Goodbye, "  + pchar.name + ".";
    		link.l1 = "I understand, sir. Goodbye.";
		link.l1.go = "SF_HuberDialogueQuestCancel";
	break;

	case "SF_HuberDialogueTheEnd":
		dialog.text = "Yes, you're brilliant. I wouldn't have come to you if I'd known how much resistance they'd put up. But you've exceeded my expectations, far beyond them. And you know what? The king's henchmen are no longer here. I think what awaits them in London is not just a demotion...";
    		link.l1 = "How about a reward?";
		link.l1.go = "SF_HuberDialogueTheEndReward";
		ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 30);
	break;

	case "SF_HuberDialogueTheEndReward":
		dialog.text = "I've already instructed the bank to take your money. Rest assured, you'll be credited exactly one million every month. Goodbye, " + pchar.name + ".";
    		link.l1 = "Pleasure doing business with you, sir. Goodbye.";
		link.l1.go = "SF_HuberDialogueQuestСlose";
	break;

	case "SF_HuberDialogueQuestСlose":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		SilverFleetMillionEveryMonth();
		pchar.questTemp.silverfleet = "over";
		pchar.questdata.SilverFleet = 1;
		AddQuestRecord("SilverFleet", "QuestEnd");
		CloseQuestHeader("SilverFleet");
		pchar.SilverFleetAtSea = true;
	break;

	case "SF_HuberDialogueFirstSilverFleetDeath":
		dialog.text = "Take your time, "  + GetAddress_Form(pchar) + " " + pchar.name + ". We agreed on a reward if it worked out, if the foreigners would spit out a piece of my pie and go away. I laid out my plan and you were satisfied.";
		link.l1 = "Don't mess with my head. I smashed the convoy clean through. What's wrong?";
		link.l1.go = "SF_HuberDialogueFirstSilverFleetProblem";
	break;

	case "SF_HuberDialogueFirstSilverFleetProblem":
		dialog.text = "That's right. You did a great job, but they were tougher than I thought they'd be. It was decided to reinforce the convoy. Things are moving toward victory, our victory. But it's not over.";
		link.l1 = "This convoy was no easy ride... Well, I can't quit now that I'm involved.";
		link.l1.go = "SF_HuberDialogueFirstSilverFleetContinue";
	break;

	case "SF_HuberDialogueFirstSilverFleetContinue":
		dialog.text = "So we keep working together. All the same inputs. I'll be waiting for news.";
		link.l1 = "You'll get them.";
		link.l1.go = "exit";
		pchar.questTemp.silverfleet = "SecondSilverFleet";
		pchar.SilverFleetAtSea = true;
		AddQuestRecord("SilverFleet", "FirstSilverFleetContinue");
		AddQuestUserData("SilverFleet", "sSex", GetSexPhrase("сам подписался","сама подписалась"));
	break;

	case "SF_HuberDialogueSecondSilverFleetDeath":
		dialog.text = "Yes, " + pchar.name + "I've heard about your exploits. And yes, again, it's not everything. But it is certain that the third strike will be the last.";
		link.l1 = "How can you be so sure?";
		link.l1.go = "SF_HuberDialogueSecondSilverFleetProblem";
	break;

	case "SF_HuberDialogueSecondSilverFleetProblem":
		dialog.text = "After the first attack on the convoy, the Crown sent here an experimental ship, the Silver Surfer, built at the Chatham shipyard. What it is, I don't know. They say it looks no different from any other ship of its class, but it's a real armored car! It was built just to carry valuable cargo in the Caribbean, alone! \nIt's so strong that it can withstand a group of ships before it reaches a safe port, and it has enough firepower to discourage enemies from coming within boarding distance. \nSo if you can handle these, there won't be a trace of the English Crown's henchmen left here. Of course, they won't let him go alone...";
		link.l1 = "I don't care. The important thing is that I'm done with this case.";
		link.l1.go = "SF_HuberDialogueSecondSilverFleetSmallDetail";
	break;

	case "SF_HuberDialogueSecondSilverFleetSmallDetail":
		dialog.text = "Little detail... They somehow got wind of who was attacking them and set up bounty hunters. Be careful they don't want them to find out about my head in this case. All I can do is prevent them from attacking you in the English colonies - you'll be safe there.";
		if (CheckAttribute(PChar, "questTemp.silverfleet.lefransuamayorspeak"))
		{
			link.l1 = "They're in cahoots with the pirates - that's how they found out! Even your buddy in Le Francois is squeamish about sharing information. Well, that's just a story. We'll get through this!";
			DeleteAttribute(PChar, "questTemp.silverfleet.lefransuamayorspeak");
		}
		else link.l1 = "They're in cahoots with the pirates - that's how they found out! Well, that's just a story. We'll get through this!";
		link.l1.go = "SF_HuberDialogueSecondSilverFleetPartingWords";
	break;

	case "SF_HuberDialogueSecondSilverFleetPartingWords":
		dialog.text = "Seven feet under the keel, " + pchar.name + "! You're in for what may be the toughest sea battle of your life. You've really pissed them off. If you slack off, they'll never let you go.";
		link.l1 = "I'm not the kind of man to let his guard down. And don't worry about your head - I'm the kind of man who goes down with his ship, not into the hold of an enemy ship.";
		link.l1.go = "SF_HuberDialogueSecondSilverFleetLetsGo";
	break;

	case "SF_HuberDialogueSecondSilverFleetLetsGo":
		dialog.text = "Here's to our victory, " + pchar.name + ". See you later!";
		link.l1 = "See you later, sir.";
		link.l1.go = "exit";
		SaveCurrentQuestDateParam("SilverFleetHeadHunters");
		pchar.SilverFleetAtSea = true;
		pchar.questTemp.silverfleet = "ThirdSilverFleet";
		pchar.questTemp.silverfleet.waitingforheadhunters = true;
		AddQuestRecord("SilverFleet", "SecondSilverFleetContinue");
		AddQuestUserData("SilverFleet", "sSex", GetSexPhrase("","а"));
	break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
