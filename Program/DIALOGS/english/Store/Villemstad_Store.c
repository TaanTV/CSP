// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Ask me what you want?",
                          "We just brought up this topic. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Listen, this is a store, people are buying something here. Don't distract me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, I forgot...",
                      "Yeah, really for the third time...", "Um, I won't...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

				if(PChar.Dozor == "10")
                {
                	link.l1 = "The brave captain engaged in battle with the Elusive Squadron.";
                	link.l1.go = "Dozor_1";
                }

                if(PChar.Dozor == "11")
                {
                	link.l1 = "I'm talking about the Watch...";
                	link.l1.go = "Dozor_7";
                }
            // ==> Проверяем поле состояния квестов.
            if (pchar.questTemp.State == "Inquisition_toCuracao" || pchar.questTemp.State == "Inquisition_afterFrancisco")// квест №2 голл. линейки.
            {
                if (!CheckAttribute(pchar, "questTemp.State.Store"))
                {
                    dialog.text = "You don't look like a simple customer. What do you need?";
        			link.l1 = "My name is " + GetFullName(pchar) + ". Вы грешны, друг мой, очень грешны. Меня послала Святая Инквизиция , вам предлагается прощение Папы, индульгенция обойдётся в 50 тысяч.";
        			link.l1.go = "Step_S2_1";
                }
                else
                {
                    if (CheckPassengerInCharacter(pchar, "JacowDeFonseka"))
                    {
                        dialog.text = "You did it! I am very grateful to you! Here is the required sum of 100 thousand for the two of us.";
            			link.l1 = "Well, that's fine. I can congratulate you that everything was so successfully resolved.";
            			link.l1.go = "Step_S2_7";
                        AddMoneyToCharacter(pchar, 100000);
                        pchar.questTemp.State.Store = "Ok";
                        AddQuestRecord("Spa_Line_2_Inquisition", "14");
                        RemovePassenger(pchar, characterFromId("JacowDeFonseka"));
                    }
                    else
                    {
                        if (pchar.questTemp.State.Store != "Ok")
                        {
                            dialog.text = "Have you learned anything about Yakov?";
                			link.l1 = "Not yet, but I'm doing it.";
                			link.l1.go = "exit";
                		}
                		else
                		{
                            dialog.text = "Yakov and I are grateful to you. Although you have come with bad news, you have nevertheless done us a great service. Thank you.";
                			link.l1 = "Yes, no problem.";
                			link.l1.go = "exit";
                		}
                    }
                }
            }
            // <== Проверяем поле состояния квестов.
		break;
//*************************** Квест №2 испанки, задание Инквизиции ***************************
 		case "Step_S2_1":
    		dialog.text = "Even under better circumstances for the development of my business, I am unable to pay such an amount. I don't cheat people and I don't profit from it. All my money is in circulation now.";
    		link.l1 = "So you refuse to pay?";
    		link.l1.go = "Step_S2_2";
 		break;
 		case "Step_S2_2":
    		dialog.text = "If I had that amount at my disposal, I would have paid.";
    		link.l1 = "I see you don't fully understand the essence of what is happening, my friend. Even if we assume that I will take pity on you, because of which I can easily say goodbye to my career, the inquisitors will not leave you alone, no matter where you go, and no matter how you hide. If they put you on their blacklist, then you're doomed. Anyway, if you don't pay, then I'll have to kill you.";
    		link.l1.go = "Step_S2_3";
 		break;
 		case "Step_S2_3":
    		dialog.text = "I already seem to have explained to you that I don't have enough money.";
    		link.l1 = "If you don't care about your life, and you don't even rate it 50 grand, no problem, I'll take your skin.";
    		link.l1.go = "Step_S2_4";
 		break;
 		case "Step_S2_4":
    		dialog.text = "Let me be curious, am I the only one who has been awarded such an honor, or are there any other candidates for indulgence?";
    		link.l1 = "Hmm, what a relevant question! I just wanted to ask where is your companion, Jacob Lopez de Fonseca!?";
    		link.l1.go = "Step_S2_5";
 		break;
 		case "Step_S2_5":
    		dialog.text = "I'd like to know that too... Wait, I think I've found a way out of the situation that's acceptable to both of us\n"+
                          "At the moment, I won't even have half of that amount. But if you agree to fulfill one of my requests, then by that time I will have collected the required money.";
    		link.l1 = "I'm all ears.";
    		link.l1.go = "Step_S2_6";
 		break;
 		case "Step_S2_6":
    		dialog.text = "My partner, Jacob Lopez de Fonseca, went to Panama on business and disappeared. He is an honest and good man. I'm worried about him\n"+
                          "If you find him, then our families together will be able to raise the required amount.";
    		link.l1 = "Um, I think I'll agree... make 50 thousand for yourself and as much for a companion. I'll see you later.";
    		link.l1.go = "exit";
            AddQuestRecord("Spa_Line_2_Inquisition", "3");
	    AddQuestUserData("Spa_Line_2_Inquisition", "sSex", GetSexPhrase("xia", "as"));
            pchar.questTemp.State.Store = 1;
            Pchar.quest.Inquisition_fightForJacow.win_condition.l1 = "location";
            Pchar.quest.Inquisition_fightForJacow.win_condition.l1.location = "Panama_houseSp1";
            Pchar.quest.Inquisition_fightForJacow.win_condition = "Inquisition_fightForJacow";
 		break;
 		case "Step_S2_7":
    		dialog.text = "Yes, indeed. You did us a great favor by finding Yakov. Thank you.";
    		link.l1 = "Yes, no problem. Goodbye.";
    		link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
        		link.l2 = "Listen, Jacob asked me to get hold of a certain book, a very dear Gospel for you, from Judas, it seems...";
        		link.l2.go = "Step_S2_8";
            }
 		break;
 		case "Step_S2_8":
    		dialog.text = "So what?";
    		link.l1 = "Hmm, that's how I managed to do it. I have the gospel.";
    		link.l1.go = "Step_S2_9";
    		link.l2 = "Oh, nothing special... Goodbye.";
    		link.l2.go = "exit";
 		break;
 		case "Step_S2_9":
    		dialog.text = "Wow!!! Listen, I'm asking you to give it to me. This is very important for our Jansenist community, you can't imagine what hardships the Jansenists went through to possess this Gospel...";
    		link.l1 = "Well, why, I really can imagine. Take it away.";
    		link.l1.go = "Step_S2_10";
 		break;
 		case "Step_S2_10":
    		dialog.text = "Oh Lord Almighty, this is IT, the Gospel of Judas Iscariot!!!"+
                          "Listen, you should know that the reward for finding this shrine is one million...";
    		link.l1 = "What?!!";
    		link.l1.go = "Step_S2_11";
    		TakeItemFromCharacter(pchar, "Bible");
 		break;
 		case "Step_S2_11":
    		dialog.text = "Yes, yes, one million. And I am happy to present it to you!";
    		link.l1 = "I am happy to take it to us... I think I'll go, my head is spinning...";
    		link.l1.go = "Step_S2_12";
    		AddMoneyToCharacter(pchar, 1000000);
 		break;
 		case "Step_S2_12":
    		dialog.text = "Go, my friend. Goodbye, our whole community is grateful to you for the rest of its life! Ah, I imagine what will begin now when everyone finds out that the missing artifact of Samuel Kohane has been found...";
    		link.l1 = "Goodbye, I won't bother you...";
    		link.l1.go = "exit";
 		break;

		// DOZOR -->
		case "Dozor_1":
			dialog.text = "Ah! Are you playing Patrol? And how do you like it?";
			link.l1 = "Just great!";
			link.l1.go = "Dozor_2";
			link.l2 = "Not a delight, of course, but it can be interesting.";
			link.l2.go = "Dozor_2";
			link.l3 = "This Watch is complete nonsense!";
			link.l3.go = "Dozor_2";
		break;

		case "Dozor_2":
			dialog.text = "You know, a captain once told me - he also played Patrol. First they visited Port Royal in Jamaica, then they broke into Hispaniola, in the Spanish town of Santo Domingo, then they visited San Juan, in Puerto Rico, after which they broke into the English Charlestown, Nevis Island.After visiting Nevis, the English colony of Antigua, they visited the penultimate island - Martinique, in the pirate Le Francois. But they couldn't solve the last task, can you imagine? They came across a very inaccessible task.";
			link.l1 = "I'd rather get a Mekahrom than listen to such stories.";
			link.l1.go = "Dozor_3";
		break;

		case "Dozor_3":
			dialog.text = "(chuckles) Eh, Captain, so you didn't guess? I'm here instead of Mecachrome! And I just told you the following puzzle!";
			link.l1 = "The next puzzle? So this nonsense was my next assignment?";
			link.l1.go = "Dozor_4";
		break;

		case "Dozor_4":
			dialog.text = "Yes. I'll repeat the task. Listen carefully. First they visited Port Royal in Jamaica, then they broke into Hispaniola, in the Spanish town of Santo Domingo, then they visited San Juan, in Puerto Rico, after which they broke into the English Charlestown, Nevis Island. After visiting Nevis, the English colony of Antigua, they visited the penultimate island - Martinique, in the pirate Le Francois. But they couldn't solve the last task, can you imagine? They came across a very inaccessible task.";
			link.l1 = "What's the hint? Where is she?";
			link.l1.go = "Dozor_5";
		break;

		case "Dozor_5":
			dialog.text = "And there are no hints here! You just have to figure out where to go next.";
			link.l1 = "But can you give me any advice?";
			link.l1.go = "Dozor_6";
		break;

		case "Dozor_6":
            dialog.text = "No tips, no hints. 'En el interior Del itinerario', as the Spaniards say! Good luck! As soon as you solve the riddle, tell me the answer.";
            link.l1 = "I'm ready to answer right now.";
			link.l1.go = "Dozor_8";
			link.l2 = "I need some time to think about it. But sure I'll be back to answer.";
			link.l2.go = "exit";
			PChar.Dozor = "11";
			AddQuestRecord("Dozor", "10");
			TakeNItems(PChar, "Dozor_Mekakhrom", -1);
		break;

		case "Dozor_7":
			dialog.text = "Well, Captain, how are you doing? Did you blow up the puzzle?";
			link.l1 = "Yes, I dud, and ready to say the right answer.";
			link.l1.go = "Dozor_8";
			link.l2 = "No, I didn't.";
			link.l2.go = "exit";
		break;

		case "Dozor_8":
			dialog.text = "So, the island?";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Dozor_9";
		break;

		case "Dozor_9":
			string sString = GetStrSmallRegister(dialogEditStrings[1]);

			if(sString == "maria galante")
			{
				dialog.text = "And the destination?";
				Link.l1.edit = 1;
				Link.l1 = "";
				Link.l1.go = "Dozor_10";
			}
			else
			{
				dialog.text = "Incorrect, Captain. Think further.";
				link.l1 = "Argh!";
				link.l1.go = "exit";
			}

		break;

		case "Dozor_10":
			string sExString = GetStrSmallRegister(dialogEditStrings[1]);
			if(sExString == "cape inaccessible")
			{
				dialog.text = "That's right, Captain! The key phrase: 'A brave captain got into a fight with the Elusive Squadron'.";
				Link.l1 = "Thank you and goodbye.";
				Link.l1.go = "exit";
				AddDialogExitQuestFunction("DozorToGuadeloupeShore");
			}
			else
			{
				dialog.text = "No, Captain, wrong. Try again.";
				link.l1 = "Damn it!";
				link.l1.go = "exit";
			}
		break;
 		// <-- DOZOR

	}
	UnloadSegment(NPChar.FileDialog2);
}

