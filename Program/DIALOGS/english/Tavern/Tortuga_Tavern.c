// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the gossip of the city "+ GetCityName(npchar.city) +" at your service. What would you like to know?",
                          "We have just raised this issue. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Why are you talking like a parrot? The same thing...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Yeah...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "Listen, where can I find Francois Gontier? He should have arrived at Tortuga by now.";
                link.l1.go = "Tortuga_ratT_1";
            }
            // ==> Проверяем поле состояния квестов.
            switch(pchar.questTemp.State)
            {
                case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
                    link.l1 = "Listen, do you know the filibuster of Pierre Picardy?";
                    link.l1.go = "Step_H3_1";
                break;
                case "DelivLettTortuga_toStranger": //Голландская линейка, квест №7. узнаем о ожидающем ГГ человеке.
                    link.l1 = "Listen, are you out of the loop? They're waiting for me here, I'm "+ GetSexPhrase("arrived", "arrived") +"from Curacao...";
                    link.l1.go = "Step_H7_1";
                break;
                case "DelivLettTortuga_AfterRape": //Голландская линейка, квест №7. пытаемся узнать, кто был грабитель.
                    link.l1 = "Where is this man who was waiting for me in the room upstairs?";
                    link.l1.go = "Step_H7_2";
                break;
                case "SeekBible_toTavern": //Голландская линейка, квест №8. узнаем, где Лоран де Граф.
                    link.l1 = "Do you know where I can find the filibuster Laurent de Graf?";
                    link.l1.go = "Step_H8_1";
                break;
                case "TakeRockBras_toTortuga": //Испанская линейка, квест №3. узнаем, где Рок Бразилец.
                    link.l1 = "Buddy, can you tell me how to find Rock the Brazilian?";
                    link.l1.go = "Step_S3_1";
                break;
                case "Sp4Detection_toTortuga": //Испанская линейка, квест №4. узнаем о донне Анне.
                    link.l1 = "What's new on Tortuga?";
                    link.l1.go = "Step_S4_1";
                break;
                case "Sp6TakeMess_toTotuga": //Испанская линейка, квест №6. узнаем о вестовом
                    link.l1 = "Listen, do the Dutch from Curacao visit you often?";
                    link.l1.go = "Step_S6_1";
                break;
                case "Sp6TakeMess_waitMessanger": //Испанская линейка, квест №6. узнаем о вестовом
                    link.l1 = "Listen, do the Dutch from Curacao visit you often?";
                    link.l1.go = "Step_S6_1";
                break;
				if(PChar.Dozor == "8")
              	{
                    link.l2 = "The brave captain is on the trail of the Elusive Squadron.";
                    link.l2.go = "Dozor_1";
              	}
            }
            // <== Проверяем поле состояния квестов.
        break;
//===================================== Голл. линейка, квест №3 =========================================
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat("I know how not to know. He rented a room from me and paid for a year in advance!", "Hey, aren't you already"+ GetSexPhrase("asked", "asked") +"me about this?",
				          "Hmm, we've already talked about Pierre...", "Maybe you won't distract me? I can send for Pierre if you really want to see him.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wow! Apparently, everything is fine with his money...", ""+ GetSexPhrase("Asked", "Asked") +"? Well, yes, probably...", "Yes, exactly, they said, I'm sorry...", "No, it's not worth it. "+ GetSexPhrase("By Myself", "By Myself") +"I'll find him...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = "Of course! Recently, Morgan invited him to participate in the attack on the Spanish silver mines. Apparently, they showed up there on time.";
			link.l1 = "Lucky, what can I say...";
			link.l1.go = "Step_H3_3";
        break;
 	 	case "Step_H3_3":
			dialog.text = "But he's not in his room right now, come back later, then you can catch him.";
			link.l1 = "Thanks, I'll do it.";
			link.l1.go = "exit";
            pchar.questTemp.Talks.Tavern = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "7");
        break;
//============================ Голл. линейка, квест №7. узнаем о ожидающем ГГ челе =======================
 	 	case "Step_H7_1":
			dialog.text = NPCStringReactionRepeat("In the course. Go to the room upstairs, there's a guy waiting for you.", "You already "+ GetSexPhrase("asked", "asked") +"I have this question today.", "Again?", "Maybe you won't distract me from work?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thanks, old man.", "You're right, "+ GetSexPhrase("asked", "asked") +"...", "Sorry...", "Okay, I won't. Sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H7_2":
			dialog.text = NPCStringReactionRepeat("Left about an hour ago, said you'd be late...", "You've already"+ GetSexPhrase("asked", "asked") +"I have this question today.", "Again?", "Maybe you won't distract me from work?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Damn it! Who is he and where did he go, do you know?", "Right, "+ GetSexPhrase("asked", "asked") +"...", "Hmm, sorry...", "Okay, I won't. Sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H7_3", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
  	 	case "Step_H7_3":
			dialog.text = "He appeared here the day before yesterday, immediately said that he was waiting for one person. He was interested in ships from Curacao. So I was waiting for you. And I don't know where he went.";
			link.l1 = "And you don't know anything about him at all?";
			link.l1.go = "Step_H7_4";
        break;
  	 	case "Step_H7_4":
			dialog.text = "I haven't seen him before, but he's a good guest, he paid two prices for a room. I can't tell you anything else.";
			link.l1 = "Well, thanks for that...";
			link.l1.go = "exit";
        break;
//============================ Голл. линейка, квест №8. узнаем о Лоране де Графе =======================
  	 	case "Step_H8_1":
			dialog.text = "You won't find it on Tortuga right now. He left town a couple of weeks ago. Probably gutting the Spaniards again...";
			link.l1 = "Where did he go, do you know for sure?";
			link.l1.go = "Step_H8_2";
        break;
  	 	case "Step_H8_2":
			dialog.text = "It is somehow not customary to spread filibuster about your plans.";
			link.l1 = "Understood... And who can I ask?";
			link.l1.go = "Step_H8_3";
        break;
  	 	case "Step_H8_3":
			dialog.text = "Why do you need it?";
			link.l1 = "I need him urgently on a very important matter. "+ GetSexPhrase("Searched", "Searched") +" he's in Bermudes, now I'm looking for him here. I "+ GetSexPhrase("the Dutchman himself", "the Dutchwoman herself") +"like Laurent...";
			link.l1.go = "Step_H8_4";
        break;
   	 	case "Step_H8_4":
			dialog.text = "Okay, I'll tell you if it's necessary. I heard that he runs near Cartagena. De Graaf has the frigate Cominte at his disposal.";
			link.l1 = "Understood. Thank you, my friend.";
			link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_toDeGraf";
            AddQuestRecord("Hol_Line_8_SeekBible", "5");
            Pchar.quest.SeekBible_SaveDeGraf.win_condition.l1 = "location";
            Pchar.quest.SeekBible_SaveDeGraf.win_condition.l1.location = "Cartahena";
            Pchar.quest.SeekBible_SaveDeGraf.win_condition = "SeekBible_SaveDeGraf";
        break;
//============================ Исп. линейка, квест №3. узнаем о Роке Бразильце =======================
  	 	case "Step_S3_1":
			dialog.text = "It depends on why you need it. How urgent is it?";
			link.l1 = "I need him urgently, I have serious business with him.";
			link.l1.go = "Step_S3_2";
        break;
  	 	case "Step_S3_2":
			dialog.text = "Then this is a problem. Rock went in search of Maracaibo on his corvette, will cruise nearby until he catches a galleon with decent loot.";
			link.l1 = "That's how it is! Yes, it's just great, because I also need to get to this region. I hope to meet him there. Thank you.";
			link.l1.go = "Step_S3_3";
        break;
  	 	case "Step_S3_3":
			dialog.text = "You're welcome...";
			link.l1 = "Be healthy, old man.";
			link.l1.go = "exit";
            pchar.questTemp.State = "TakeRockBras_toNearestMaracaibo";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "2");
			pchar.quest.TakeRockBras_toRock.win_condition.l1 = "location";
			pchar.quest.TakeRockBras_toRock.win_condition.l1.location = "Maracaibo";
			pchar.quest.TakeRockBras_toRock.win_condition = "TakeRockBras_toRock";
        break;
//============================ Испанская линейка, квест №4. узнаем о донне Анне. =======================
  	 	case "Step_S4_1":
			dialog.text = "Yes, everything is the same, we are at war with the damned papists.";
			link.l1 = "Ah, that's a good thing. And what about papists, do you have in the city? Hot, they say, women...";
			link.l1.go = "Step_S4_2";
        break;
  	 	case "Step_S4_2":
			dialog.text = "Until recently, there were none. But now our esteemed Governor-General has a'Augeron has a Spanish goat, oh, very beautiful. The Governor-General is just happy and his mouth is full from morning to late evening. I don't know how it was at night, hee-hee...";
			link.l1 = "That's it! And who is this brave woman?";
			link.l1.go = "Step_S4_3";
        break;
  	 	case "Step_S4_3":
			dialog.text = "Donna Anna - that's her name. I heard she's from Havana.";
			link.l1 = "The filibusters have not reached Havana yet. How did she get to d'Ogeron, captured on a Spanish galleon?";
			link.l1.go = "Step_S4_4";
        break;
  	 	case "Step_S4_4":
			dialog.text = "Nah, there's a mutual feeling here. Donna Anna loves our Governor-General as much as he loves her. I heard that they met back in the Old World. She was brought to Tortuga by one of the Governor-General's trusted officers, Henri d'Estre, no one knows where he found her.";
			link.l1 = "Understood... And where is this Henri d now?'Estre?";
			link.l1.go = "Step_S4_5";
        break;
  	 	case "Step_S4_5":
			dialog.text = "At home, probably. He has a house here on the island.";
			link.l1 = "I see that Tortuga is flourishing and I am very, very happy about it"+ GetSexPhrase("glad", "glad") +". Be healthy, buddy.";
			link.l1.go = "exit";
            pchar.questTemp.State = "Sp4Detection_toDEstre";
            AddQuestRecord("Spa_Line_4_MirderDetection", "5");
        break;
//============================ Испанская линейка, квест №6. перехватить вестового. =======================
  	 	case "Step_S6_1":
			dialog.text = NPCStringReactionRepeat("There are, but what do you care about them?",
                          "The Dutch? Sometimes, sometimes...", "We were talking about the Dutch today...",
                          "I don't want to talk about the Dutch anymore...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I'm waiting here for a man from Willemstad. So I'll have to rent a room from you for a week.",
                      "Great!", "They said that's right...", "Okay, whatever you say...", npchar, Dialog.CurrentNode);
			link.l1.go =  DialogGoNodeRepeat("Step_S6_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
  	 	case "Step_S6_2":
			dialog.text = "No problem, the room is free. Pay 35 coins a week and live.";
			link.l1 = "I'll pay you a hundred coins for a week, what is 35 coins? Crumbs...";
			link.l1.go = "Step_S6_3";
        break;
  	 	case "Step_S6_3":
			dialog.text = "Heh, well, thank you, "+ GetSexPhrase("kind man", "kind lady") +". I won't give up the money. And you can occupy the room right now, it's open there.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			pchar.questTemp.State.Open = 1;
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false);
            AddMoneyToCharacter(pchar, -100);
            if (CheckAttribute(pchar, "questTemp.State.Sp6Ok"))
            {
                SetTimerCondition("Sp6TakeMess_waitingBoy", 0, 0, rand(7)+1, false);
                DeleteAttribute(pchar, "questTemp.State.Sp6Ok");
            }
            else
            {
                pchar.questTemp.State.Sp6Ok = 1;
            }
        break;

		case "Tortuga_ratT_1":
			dialog.text = "Francois Gontier? And who is this guy? I do not know a person with that name.";
			link.l1 = "Well, he's captain of corvette '" + pchar.questTemp.Slavetrader.ShipName + "'.";
			link.l1.go = "Tortuga_ratT_2";
        break;

		case "Tortuga_ratT_2":
			dialog.text = "I have no idea, "+ GetSexPhrase("buddy", "madam") +". And a corvette with that name did not dock in our port, I know for sure.";
			link.l1 = "Well, have you seen any strangers in the city lately?";
			link.l1.go = "Tortuga_ratT_3";
        break;

		case "Tortuga_ratT_3":
			dialog.text = "Hah, such a stupid question! This is a port city, not a village. Strangers come here every day... Although, I've heard about some strange guys who recently showed up at our place, they always walk together, five of them, and hold on to the hilts of their sabers, as if in an enemy colony. The patrol has already checked them - no, everything is fine. But they definitely did not arrive on a corvette -neither in the port, nor on the raid - not a single corvette, do you understand?";
			link.l1 = "Um... Well, I see. Thank you, " + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;

            // DOZOR -->
		case "Dozor_1":
			TakeNItems(PChar, "Dozor_Mekakhrom", 1);
			dialog.text = "Ah! So it's you, watchman? Therefore, you guessed three riddles already, well done! Here's a Meckachrome with the fourth riddle. Good luck coping with her, she'll be a little more difficult than the others.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorTortugaTavernGetItem");
		break;
			// DOZOR <--

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

