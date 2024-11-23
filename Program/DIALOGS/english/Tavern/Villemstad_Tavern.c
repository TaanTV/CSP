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
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "I heard that you had a serious mess on the island... The slaves seem to have rebelled.";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//виспер
			if(CheckAttribute(pchar, "Whisper.FindDesouzaHol") && !CheckAttribute(npchar, "Whisper.FindDesouzaHol"))
			{
				npchar.Whisper.FindDesouzaHol = true;
				link.l1 = "Listen, did any guys of suspicious appearance come up to you here? They should also have a crucifix-shaped brand on their arm.";
				link.l1.go = "FindDesouzaHol";
				break;
			}
			//виспер
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
			{
			case "Intelligence_Curacao_tavern":
				link.l1 = "Listen, I need to know something...";
				link.l1.go = "Step_E4_1";
				break;
			case "Intelligence_Curacao_dWant_pay_tavern":
				dialog.text = "You ready?";
				link.l1 = "Yes. Keep your thousand.";
				link.l1.go = "E4_OK_pay";
				link.l2 = "A thousand coins for two words?! It's too much!";
				link.l2.go = "E4_dWant_pay";
				break;
			case "Intelligence_Curacao_NoMoney_tavern":
				dialog.text = "Stashed money?";
				link.l1 = "Yes, it seems to be.";
				link.l1.go = "E4_OK_pay";
				break;
			case "Inquisition_toCuracao":
				dialog.text = "I'm listening to you.";
				link.l1 = "I'm interested in people: Joao Ilhaio, Joseph Nunen de Fonquesao, and Jacob Lopez de Fonseca. What can you say about them?";
				link.l1.go = "Step_S2_1";
				break;
			case "Inquisition_afterFrancisco":
				dialog.text = "I'm listening to you.";
				link.l1 = "I'm interested in people: Joao Ilhaio, Joseph Nunen de Fonquesao, and Jacob Lopez de Fonseca. What can you say about them?";
				link.l1.go = "Step_S2_1";
				break;
			case "Fr2Letter_SeekProblems":
				dialog.text = "Listening attentively "+ GetSexPhrase("dear French guest", "dear French guest") +"!";
				link.l1 = "I want to understand why the hell Governor-General Stuyvesant put an official courier of France behind bars. What the hell is going on here?";
				link.l1.go = "Step_F2_1";
				break;
			}
			if (pchar.questTemp.LSC == "toVillemstadTavern")
			{
				dialog.text = "I'm listening to you.";
				link.l1 = "Listen, I need to order a key to the chest here.";
				link.l1.go = "MasterKeys";
			}
			if (pchar.questTemp.LSC == "toMasterKeysNoMoney")
			{
				dialog.text = "I'm listening to you carefully.";
				link.l1 = "Listen, I need a key master, have you seen him?";
				link.l1.go = "MasterKeysNM";
			}
			if (pchar.questTemp.LSC == "toTalkStuvesant")
			{
				dialog.text = "I'm listening carefully.";
				link.l1 = "Listen, did you know such a tramp Teaser Dan? They say that he lived in your city for a while.";
				link.l1.go = "TizerFind";
			}
            // <== Проверяем поле состояния квестов.
			//ОЗГ, Хален
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
		    	if (pchar.questTemp.Headhunter == "hunt_halen")
	    		{
	    			link.l1 = "Listen, do you know where to find Martin van Halen?";
		    		link.l1.go = "Halen_tavern_1";
		    	}
	    		if (pchar.questTemp.Headhunter == "halen_still")
    			{
    				link.l1 = "What's going on here?! They just tried to kill me in my room!";
    				link.l1.go = "Halen_tavern_1_1";
    			}
    			if (pchar.questTemp.Headhunter == "halen_wait")
    			{
    				link.l1 = "Well, did Martin van Halen show up?";
	    			link.l1.go = "Halen_tavern_6_6";
    			}
			}
			//ОЗГ, Хален
 		break;
//*************************** Квест №4 английки, разведка в Кюрасао ***************************
 		case "Step_E4_1":
    		dialog.text = "I will help you as much as I can. Ask away.";
    		link.l1 = "I have accumulated some junk, gold, stones... We need to hand it over, but quietly. In general, I need someone who is not particularly scrupulous.";
    		link.l1.go = "Step_E4_2";
 		break;
 		case "Step_E4_2":
    		dialog.text = "Hmm, 1000 coins and you'll know his name.";
    		link.l1 = "Aren't you asking too much for two words?";
    		link.l1.go = "E4_dWant_pay";
    		link.l2 = "Keep your thousand.";
    		link.l2.go = "E4_OK_pay";
 		break;
 		case "E4_dWant_pay":
    		dialog.text = "No, too little. If you don't want to pay, try to find out somewhere else. You'll come anyway.";
    		link.l1 = "Well, I'll follow your advice. I'll try to find out somewhere else.";
    		link.l1.go = "exit";
    		pchar.questTemp.State = "Intelligence_Curacao_dWant_pay_tavern";
 		break;
 		case "E4_OK_pay":
            if (sti(pchar.money) >= 1000)
            {
        		dialog.text = "This man's name is Josef Nunen de Fonquezao. He's a merchant, came here with those Jansenists who organized a fairly large community here, Josef is its main organizer and leader.\n"+
                         "But if all these Jansenists are normal people, this man has no conscience, he immediately became a usurer in the city. The money comes willingly, but if you don't pay him back in right second, you'll be in jail the next morning.\n"+
                         "He has more than one starvation death and more than one suicide on his conscience, but he doesn't care about anything.";
        		link.l1 = "What about the Governor General?";
        		link.l1.go = "Step_E4_3";
            }
            else
            {
        		dialog.text = "Heh, "+ GetSexPhrase("brother", "sister") +", no money? Why are you messing with my head? Come back when they are.";
        		link.l1 = "Yes, they won't let you to the banquet when there is no money in your pocket...";
        		link.l1.go = "exit";
        		pchar.questTemp.State = "Intelligence_Curacao_NoMoney_tavern";
        		//ChangeCharacterReputation(pchar, -1); TO_DO eddy
            }
 		break;
 		case "Step_E4_3":
    		dialog.text = "Our governor-General seems to be helping Josef with debt collection. Josef is a welcome guest in his house.";
    		link.l1 = "So if he is friends with the authorities, then it is dangerous for me to contact him!";
    		link.l1.go = "Step_E4_4";
 		break;
 		case "Step_E4_4":
    		dialog.text = "It's not dangerous at all. He will buy your stuff from you, of course, not at store prices, but he will not take it either. So come on, you're not the first person I've sent him.";
    		link.l1 = "Well, thank you.";
    		link.l1.go = "exit";
    		pchar.questTemp.State = "Intelligence_Curacao_toYozef";
    		AddMoneyToCharacter(pchar, -1000);
    		AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "2");
 		break;
//*************************** Квест №2 испанки, задания Инквизиции ***************************
 		case "Step_S2_1":
    		dialog.text =  NPCStringReactionRepeat("Joao Ilhaio is a good man, trades honestly, the goods are cheap, he does not lend money at interest. Yakov Lopez de Fonseca is Joao Ilhaio's partner, they run the store together. But Joseph Nunen de Fonquesao is a usurer, he has more than one suicide on his conscience of the people he ruined.",
            "We've already talked about this topic...", "Again?", "Hmm, how much can I do, huh?", "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("You're the devil alive!", "Yeah, exactly...", "No, sorry...", "Sorry...", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
 		break;
 		case "Step_S2_2":
    		dialog.text = "Maybe not the devil himself, but he's quite attracted to a sidekick.";
    		link.l1 = "Thanks, buddy, you helped me a lot.";
    		link.l1.go = "exit";
 		break;
//*************************** Квест №2 фр.линейки, доставка письма Стэвезанту ***************************
 		case "Step_F2_1":
    		dialog.text =  NPCStringReactionRepeat("And no wonder. It's no joke, in a month the pirates on the galleon have already robbed nineteen of our ships and sent them to the bottom. Two of them are with the goods of the Governor-General himself. So he looks at all strangers like a wolf!",
            "We've already talked about this topic...", "Again?", "Hmm, how much can I do, huh?", "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("What about me "+ GetSexPhrase("turned out to be the most suspicious", "turned out to be the most suspicious") +"of all?", "Yes, exactly.", "No, sorry...", "Sorry...", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_F2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
 		break;
 		case "Step_F2_2":
    		dialog.text = "Yes, you are probably just a hot hand. There are more strange guys.\n"+
				          "By the way, look, there are two people sitting at that table in the corner, to your right. What kind of people? It's the first time I've seen them, and there doesn't seem to be anything to call the guards for - I value the reputation of my institution. Talk to them if you want!";
    		link.l1 = "Thanks, buddy, you helped me a lot.";
    		link.l1.go = "exit";
 		break;
//*************************** ГПК, Мастер Ключей ***************************
		case "MasterKeys":
			dialog.text = "Ah, well, you need to go to the Master of Keys.";
			link.l1 = "What is the Master of Keys?";
			link.l1.go = "MasterKeys_1";
		break;
		case "MasterKeys_1":
			dialog.text = "This is how Hill Corner is called because he makes locks on chests and doors with keys.";
			link.l1 = "Hmm, is this a local craftsman?";
			link.l1.go = "MasterKeys_2";
		break;
		case "MasterKeys_2":
			dialog.text = "Yeah. There he is, sitting at a round table by the stairs. He's wearing a red shirt.";
			link.l1 = "I understand. Thank you.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toMasterKeys";
		break;

		case "MasterKeysNM":
			dialog.text = "Yes, there he is, in his usual place in the corner, at the entrance to the tavern.";
			link.l1 = "Ah, thank you...";
			link.l1.go = "exit";
			if (!LAi_CheckLocatorFree("sit", "sit1"))
			{
				FreeSitLocator("Villemstad_tavern", "sit1");
			}
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("GiveKeyMan")], "Villemstad_tavern", "sit", "sit1");
		break;
		//ищем Тизера
		case "TizerFind":
			dialog.text = NPCStringReactionRepeat("How not to know, the whole city knew him! He was a noble inventor...",
				"Listen, I've already told you about this.",
				"We've already talked about this.",
                "I'm sorry, but I don't have time for such a long narrative anymore.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("How to understand?",
				"Ah, yes, I remember.",
                "Yes, of course.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("TizerFind_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "TizerFind_1":
			dialog.text = "Well, you know, he made a good living telling stories about his adventures. It's very fashionable now to travel and discover new lands on everyone's lips!";
			link.l1 = "Did you tell me about the island?";
			link.l1.go = "TizerFind_2";
		break;
		case "TizerFind_2":
			dialog.text = "And about the island too! In general, it was fun with him. He used to say, 'Have you been to Tahiti?'and the people start to gather around. And he was a good storyteller! It's a pity he left us.";
			link.l1 = "Where to?";
			link.l1.go = "TizerFind_3";
		break;
		case "TizerFind_3":
			dialog.text = "I don't know, I didn't tell anyone. I just didn't see him in my tavern one day, that's all. I can say more - his colleagues were looking for him, so to speak, tramps, that is. I don't know if they found it or not...";
			link.l1 = "No, we didn't find it.";
			link.l1.go = "TizerFind_4";
		break;
		case "TizerFind_4":
			dialog.text = "It's a pity, he was a good man, even though he was a tramp. You know, there are people with a heightened sense of entitlement. That's Teaser was one of those, and even life beat him pretty badly. Stories about the Island of Justice were his favorite topic.";
			link.l1 = "Hmm, and what did you say?";
			link.l1.go = "TizerFind_5";
		break;
		case "TizerFind_5":
			dialog.text = "That there is an island somewhere nearby consisting of ships! That people live there very well, and everyone is equal to each other. Well, heaven on earth, in general. Utopia.";
			link.l1 = "How does your governor-General treat beggars?";
			link.l1.go = "TizerFind_6";
		break;
		case "TizerFind_6":
			dialog.text = "You know, it's very bad. Teaser said that he was sold into slavery, and our Stuyvesant does not consider slaves to be people, and former ones too.";
			link.l1 = "Clear. Listen, they say Stuyvesant has business with the Dutch West India Company, and...";
			link.l1.go = "TizerFind_7";
		break;
		case "TizerFind_7":
			dialog.text = "T-s-s!! Quietly, "+ GetSexPhrase("buddy", "girlfriend") +". It is not customary to talk about these connections of our Peter. And I don't recommend asking either - you'll get into trouble for the most part!";
			link.l1 = "What's the matter?";
			link.l1.go = "TizerFind_8";
		break;
		case "TizerFind_8":
			dialog.text = "This company doesn't like to joke, "+ GetSexPhrase("buddy", "girlfriend") +". And don't look at the fact that their offices are mainly located in Europe and the Indian Ocean. They are also present here, but not so clearly...";
			link.l1 = "Damn!.. And where can they be found?";
			link.l1.go = "TizerFind_9";
		break;
		case "TizerFind_9":
			dialog.text = "Why do you need them?";
			link.l1 = "I want to offer my services in freight transportation.";
			link.l1.go = "TizerFind_10";
		break;
		case "TizerFind_10":
			dialog.text = "You know, "+ GetSexPhrase("buddy", "girlfriend") +", this company does its business without the participation of people like you. It is rumored that Curacao itself belongs to her, and not only this island!..";
			link.l1 = "Oh, the devil! A serious office.";
			link.l1.go = "TizerFind_11";
		break;
		case "TizerFind_11":
			dialog.text = "Yeah. My advice to you is not to try to do business with them, here they only work with our Peter.";
			link.l1 = "I understand... Well, my friend, thank you for such a detailed presentation. It was very interesting.";
			link.l1.go = "TizerFind_12";
		break;
		case "TizerFind_12":
			dialog.text = "You're welcome. I'm happy to chat myself.";
			link.l1 = "Be healthy.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "8");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("ISS_PoorsMurder", "sSex1", GetSexPhrase("", "la"));
		break;
		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "Yeah, that's never happened... More than a thousand slaves participated in the riot. Two plantations were burned to the ground, and the owners were killed almost completely. The commandant was afraid that they would attack the city - he imposed martial law. And it all started with the love story of two slaves - Tamango and Izaura...";
			link.l1 = "Interesting! Tell me more, who is this?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;

		case "EscapeSlaveVillemstad_T2":
				dialog.text = "Tamango and Izaura are slaves from the Blenheim plantation, well, from the one that was burned first. They had love. And then the son of the plantation owner, Leoncio, came from Europe and set his eyes on Isaura. In general, I decided to make my concubine. Tamango didn't like it very much, and Isaura wasn't thrilled - she loved this nigger. I must say that Tamango was some kind of leader or king in his Africa... He is healthy as a bull, a master of swinging an axe, and an authority among slaves. So I incited them to revolt, they attacked the guards and slaughtered all the Dutch in Blenheim. Izaura opened the gates of the estate to them - they killed everyone there too. Then they went in a crowd to the neighboring plantation, Blenburg, and staged the same massacre there. Then they went into the jungle and disappeared without a trace...";
			link.l1 = "That's the story! It's like a plot for a novel! And how do you know all this?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;

		case "EscapeSlaveVillemstad_T3":
			dialog.text = "Rumors, "+ GetSexPhrase("mynheer", "mistress") +", the earth is full of rumors. Rum loosens tongues, just listening is enough...";
			link.l1 = "And how did it end? Have you found these niggers?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;

		case "EscapeSlaveVillemstad_T4":
				dialog.text = "What's there! Until reinforcements arrived, no one took a step into the jungle. Then a warship arrived with a detachment of soldiers, they searched the island - there was no one.";
			link.l1 = "Well, think about it! A thousand people - and everything disappeared into the water!";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;

		case "EscapeSlaveVillemstad_T5":
			dialog.text = "Exactly, "+ GetSexPhrase("mynheer", "mistress") +"! They sank into the water!";
			link.l1 = "What are you talking about now, " + npchar.name + "? I don't understand something...";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;

		case "EscapeSlaveVillemstad_T6":
			dialog.text = "Hehe... I bet they sailed off the island. The fact is that the next night after the uprising, a bark disappeared from the parking lot of ships. I will not drink rum for the rest of my days, unless it is the work of Tamango and his brothers! That's why they're not on the island.";
			link.l1 = "Okay, thanks for the interesting story, " + npchar.name + ". Although I can't imagine how Negroes can handle sails.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;

		case "EscapeSlaveVillemstad_T7":
			dialog.text = "Well, maybe they can... Maybe one of them used to be a sailor. Come and see me again, " + pchar.name + ", don't forget, and I'll tell you some more stories.";
			link.l1 = "Thank you! Well, I have to go.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;

		//ОЗГ, Хален
		case "Halen_tavern_1":
			dialog.text = "No, he's not here right now. He's gone sailing, but he'll be back any day now. You can stay at my place. When he returns, I'll let you know.";
			link.l1 = "Understood. I need to wait for him. Well, then, will I rent a room from you?";
			link.l1.go = "Halen_tavern_2";
		break;

		case "Halen_tavern_2":
			dialog.text = "Yes, of course. It costs 100 gold coins.";
			link.l1 = "Okay. Open your room.";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "halen_room";
			LocatorReloadEnterDisable("Villemstad_tavern", "reload2_back", false);
            AddMoneyToCharacter(pchar, -100);
			Pchar.quest.Headhunter_inRoom.win_condition.l1 = "location";
			Pchar.quest.Headhunter_inRoom.win_condition.l1.location = "Villemstad_tavern_upstairs";
			Pchar.quest.Headhunter_inRoom.function = "RatHunters_inRoom";
			AddQuestRecord("Headhunt", "27");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("", "a"));
			pchar.quest.Headhunter_HalenOver.over = "yes";
		break;

		case "Halen_tavern_1_1":
			dialog.text = "What are you saying? I will order the commandant to be called immediately!";
			link.l1 = "Call. And call the gravediggers too - I killed those two guys.";
			link.l1.go = "Halen_tavern_2_2";
		break;

		case "Halen_tavern_2_2":
			dialog.text = "Mother of the Most Holy Theotokos! What a nightmare! And this is in my tavern...";
			link.l1 = "Calm down. It's better to do this: quietly take the corpses out through the backyard, without making too much noise, so as not to damage the reputation of your institution... I don't think these two are locals, so no one will know anything. Did you see them come in? Two guys, in black, their faces covered with handkerchiefs.";
			link.l1.go = "Halen_tavern_4_4";
		break;

		case "Halen_tavern_4_4":
			dialog.text = "No... I haven't seen it. God... What kind of punishment is this!";
			link.l1 = "Will you stop wailing at last? You didn't see it, did you say? However, I did not expect any other answer... Aren't you in cahoots with them by any chance? Otherwise I...";
			link.l1.go = "Halen_tavern_5_5";
		break;

		case "Halen_tavern_5_5":
			dialog.text = "What are you, "+ GetSexPhrase("noble sir", "noble lady") +"! Here is a true cross for you, I would never take a sin on my soul...";
			link.l1 = "Okay, okay, I believe you. Martin hasn't shown up, have you heard?";
			link.l1.go = "Halen_tavern_6_6";
		break;

		case "Halen_tavern_6_6":
			if (makeint(environment.time) > 18.0 || makeint(environment.time) < 6.0)
			{
				dialog.text = "No, it did not appear. Come back tomorrow morning-maybe I'll have some news.";
				link.l1 = "Okay.";
				link.l1.go = "exit";
				pchar.questTemp.Headhunter = "halen_wait";
				break;
			}
			dialog.text = "You're just in time! Martin van Halen's corvette has anchored in our port.";
			link.l1 = "Great! So Martin is already in town?";
			link.l1.go = "Halen_tavern_7_7";
		break;

		case "Halen_tavern_7_7":
			dialog.text = "Yes, he went to visit the Governor General immediately upon arrival. I think if you hurry up, you'll find him at the residence. Or you'll find him on the ship.";
			link.l1 = "I understand. I'm already running. Thank you!";
			link.l1.go = "Halen_tavern_8_8";
		break;

		case "Halen_tavern_8_8":
			AddQuestRecord("Headhunt", "29");
			pchar.questTemp.Headhunter = "halen_town";
			CreateHalen();
			DialogExit();
		break;
		case "FindDesouzaHol":
    		dialog.text = "No, I definitely haven't seen them here.";
    		link.l1 = "Okay, thanks.";
    		link.l1.go = "exit";
 		break;



	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

