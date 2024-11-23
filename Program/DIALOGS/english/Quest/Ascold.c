// Аскольд
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Tichingitu_11":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Great! That's the thing! Now I will write a note and attach my seal, wait a bit... Here you go. Give this to the commandant and you can take your Indian. But why you need it, I don't know. Except to show it at fairs for money, haha!";
			link.l1 = "God sees everything, Askold. Saving a person's life is a good thing.";
			npchar.quest.Tichingitu = "paid"
			link.l1.go = "Tichingitu_12";
		break;

		if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "ascold")
		{
			dialog.text = "Well, what do you say? Went to look at this Indian scarecrow?";
			link.l1 = "Went down... Therefore, back to you.";
			link.l1.go = "Tichingitu_7";
			if (!CheckAttribute(npchar, "quest.Tichingitu"))
			{
				npchar.quest.Tichingitu = true;
				break;
			}
		}
		if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "money")
		{
			dialog.text = "Oh, it's you again! Well, prin"+GetSexPhrase("eu","if")+"money for an Indian?";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Yes. Here you go.";
				link.l1.go = "Tichingitu_11";
			}
			if (CheckAttribute(npchar, "quest.Tichingitu") && npchar.quest.Tichingitu != "paid")
			{
				link.l2 = "No, I haven't collected yet.";
				link.l2.go = "exit";
				break;
			}
		}
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (npchar.quest.meeting == "0")
            {
            	dialog.text = "Greetings. My name is Askold. And who do I have the honor to talk to?";
        		link.l1 = "My name is " + GetFullName(pchar) + ".";
        		link.l1.go = "Step_1";
                npchar.quest.meeting = "1";
            }
            else
            {
				
            	dialog.text = "I don't like it when people I don't know bother me.";
        		link.l1 = "I understand, I'm already leaving...";
        		link.l1.go = "exit";
        		link.l2 = "Are you being rude, sir?";
        		link.l2.go = "Step_3";
                NextDiag.TempNode = "First time";
            }
		break;

 		case "Step_1":
        	dialog.text = "Who are you and what do you do?";
    		link.l1 = "I am a privateer.";
    		link.l1.go = "Step_2";
		break;

 		case "Step_2":
        	dialog.text = "Listen, caper...";
    		link.l1 = "Yes?";
    		link.l1.go = "First time";
		break;

 		case "Step_3":
            if (npchar.quest.meeting == "1")
            {
            	dialog.text = "Ooh, you're not just a privateer, you're a fearsome privateer... Get out of here!";
        		link.l1 = "...";
        		npchar.quest.meeting = "2";
            }
            else
            {
            	dialog.text = RandPhraseSimple("Again, the formidable and evil privateer deigns to break the silence?! Let's repeat the removal of the body...", "I got into a huff again... It's time to take action.");
        		link.l1 = RandPhraseSimple("Yes, I like you now...", "Let's see who throws who out of the house this time...");
            }
            link.l1.go = "Step_4";
		break;

 		case "Step_4":
            DoReloadCharacterToLocation("BasTer_town", "reload", "houseSp1");
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

 		case "HaveRecomendation":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
            if (npchar.quest.meeting == "0")
            {
            	dialog.text = "Greetings. My name is Askold. And with whom do I have the honor...";
				link.l1 = "My name is " + GetFullName(pchar) + ". And I was sent to you by " + GetFullName(sld) + ", the owner of the store, which is located in " + XI_ConvertString("Colony" + sld.City + "Voc") + ".";
                npchar.quest.meeting = "1";
            }
            else
            {
            	dialog.text = "Back on the horizon "+ GetSexPhrase("our formidable corsair appeared","our formidable corsair woman appeared") +". What do you need this time?";
        		link.l1 = "This time I was sent to you by " + GetFullName(sld) + ", the owner of the store that is on " + XI_ConvertString("Colony" + sld.City + "Voc") + ".";
            }
            link.l1.go = "Step_5";
		break;

 		case "Step_5":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
        	dialog.text = "Heh, I know this person. Well, come on in, sit down, let's have a vodka.. "+
                          "(confidentially) In these parts, Russian vodka - a big deficit. Jamaican rum - at least get, but compared to vodka, rum - shark urine\n"+
                          "Anyway, tell me, what's your business with me?";
    		link.l1 = sld.lastname + " said you were looking for mummy powder. I have it.";
    		link.l1.go = "Step_6";
		break;

 		case "Step_6":
        	dialog.text = "Very good. I'm paying 30,000 for this powder.";
    		link.l1 = "Good price. It's a deal.";
            if (CheckCharacterItem(pchar, "Powder_mummie"))
            {
        		link.l1.go = "Step_7";
        		TakeItemFromCharacter(pchar, "Powder_mummie");
        		AddMoneyToCharacter(pchar, 30000);
            }
            else
            {
        		link.l1.go = "No_Powder";
            }
		break;

 		case "No_Powder":
        	dialog.text = "Hey, "+ GetSexPhrase("brother","sister") +", you're messing around! You don't have any powder. I don't recognize people who are trying to deceive me anymore.. "+
                          "Get out of here!";
    		link.l1 = "What are you talking about! I was joking! I had no idea...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
			pchar.questdata.Ascold = 1;
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_7":
        	dialog.text = "The job is done, now we can drink...";
    		link.l1 = "No, I won't drink anything. You better tell me, why do you need this stuff? How many times have I been racking my head over this, but I couldn't understand. Absolutely useless and disgusting thing.";
    		link.l1.go = "Step_8";
		break;

 		case "Step_8":
        	dialog.text = "Well, that's how to say it. This powder and similar objects of the Indian cult are ordered by the well-known scientist Pierre de la Fontaine in Europe.. "+
                          "I am here as his confidant. In principle, I am quite satisfied. De la Fontaine pays for the rent of the house and my accommodation.. "+
                          "And for every such thing that I find here for him to order, he pays very, very well.";
    		link.l1 = "Understood.";
    		link.l1.go = "Step_9";
		break;

 		case "Step_9":
        	dialog.text = "Listen, since such a song went on and we worked together, then I offer you another job.. "+
                          "I just received a new order for three Aztec artifacts.";
    		link.l1 = "I agree.";
    		link.l1.go = "Step_10";
    		link.l2 = "No, I won't take it. I have other things to do.";
    		link.l2.go = "No_Work";
		break;

 		case "No_Work":
        	dialog.text = "Yes? I don't like being rejected, I don't want to know any more of them. Therefore - get out of my house!";
    		link.l1 = "Hey, hey! What are you doing?!!";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
			pchar.questdata.Ascold = 1;
    		pchar.questTemp.Ascold = "BreakeQuest";
    		group_DeleteGroup("Ascold_Spa_Attack");
    		DeleteAttribute(PChar, "questTemp.Ascold.Ship");
		break;

 		case "Step_10":
        	dialog.text = "Okay. Now listen to what I need to find.. "+
                          "I need a statuette of Tlaloc, the Aztec god of rain and thunder, a ceremonial vessel of the Purepcha tribe and a ceremonial knife of Tumi.";
    		link.l1 = "I understand. Well, I'll look around. I'll pack all three things and I'll be at your place. But it seems to me that something else is bothering you, isn't it?";
    		link.l1.go = "Tichingitu_1";
    	    pchar.questTemp.Ascold = "SeekThreeObject";
            AddQuestRecord("Ascold", "3");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("xia","as"));
		break;

		case "Tichingitu_1":
			dialog.text = "You have a surprisingly good sense. Well, I'll tell you. A week ago, several bandits broke into my house. Wherever the guards looked...";
			link.l1 = "Obviously, anywhere but where it was needed. What's next?";
			link.l1.go = "Tichingitu_2";
		break;

		case "Tichingitu_2":
			dialog.text = "Well, I took the shaft and punched them. They barely got away with it. Yes, but what an attack, those who broke in distracted me. A thief got on the second floor and took away a chest with valuables, so that he would be torn apart by greed!";
			link.l1 = "And you didn't stop him?";
			link.l1.go = "Tichingitu_3";
		break;

		case "Tichingitu_3":
			dialog.text = "Where is it, he ran away with his accomplices into the jungle. And you won't find them there anymore. Okay, there's nothing you can do about it. Of course, I hired mercenaries to scour the island, but the robbers and the thief are already gone.";
			link.l1 = "It sounds very unpleasant. You can say grief...";
			link.l1.go = "Tichingitu_4";
		break;

		case "Tichingitu_4":
			dialog.text = "So this theft is not all. Just the other day - imagine, a thief got into my room again.  I'm too much! But then he didn't leave me: I caught him, gave him a good beating and handed him over to the commandant. I think he's going to be hanged soon. And it serves him right!";
			link.l1 = "Don't you think you overreacted?";
			link.l1.go = "Tichingitu_5";
		break;

		case "Tichingitu_5":
			dialog.text = "Maybe. He looked rather emaciated. I can see it from complete despair. And he was only interested in coins. But understand me, too... Can you imagine, a scarecrow climbed into my room and rummaged through the chests .  Indian from some remote jungle, just a miracle. All dressed up, painted... You can go to our casemates and see this buffoon in disguise, if you're interested, while he's still alive.";
			link.l1 = "Hmm... Maybe I'll look in.";
			link.l1.go = "Tichingitu_6";
		break;

		case "Tichingitu_6":
			dialog.text = "Go-go, look at the local walking curiosities...";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ResultOfSeek";
			pchar.questTemp.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
		break;

		case "Tichingitu_7":
			dialog.text = "Well, what else?";
			link.l1 = "Askold, I told with this Indian. And I'll ask for him. This wretch just wanted to eat...";
			link.l1.go = "Tichingitu_8";
		break;

		case "Tichingitu_8":
			dialog.text = "It can be understood. So do you want to rescue him?";
			link.l1 = "They are going to execute him, but he may be useful to me on the ship...";
			link.l1.go = "Tichingitu_9";
		break;

		case "Tichingitu_9":
			dialog.text = "Since that's the case, I think you can buy it back. I will be satisfied with a compensation of 10,000 piastres.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Okay, here's the money.";
				link.l1.go = "Tichingitu_11";
			}
			link.l2 = "I'll probably come back later then.";
			link.l2.go = "Tichingitu_10";
		break;

		case "Tichingitu_10":
			dialog.text = "And hurry up! They won't be needed in ten days...";
			link.l1 = "I'll take note. Goodbye!";
			link.l1.go = "exit";
			pchar.questTemp.Tichingitu = "money";
		break;

		case "Tichingitu_12":
			GiveItem2Character(pchar, "letter_A");
			PlaySound("interface\important_item.wav");
			dialog.text = "This is a controversial issue. What if you're saving a murderer or a rapist? Would you like some vodka for a drink? And then go to the commandant before your red-skinned friend is hanged...";
			link.l1 = "So be it, persuaded.";
			link.l1.go = "exit_vodka";
			pchar.questTemp.Tichingitu = "pay";
		break;

		case "exit_vodka":
			LAi_MethodDelay("FrameAscoldVodka",0.1);
			DialogExit();
			AddQuestRecord("Ascold", "3_3");
		break;

 		case "ResultOfSeek":
        	dialog.text = "Did you manage to find the Indian rattles? I need all three at once, you don't have to carry one at a time.";
    		link.l1 = "Not yet, but I'm doing it.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "ResultOfSeek";
            if (CheckCharacterItem(pchar, "indian19") && CheckCharacterItem(pchar, "indian20") && CheckCharacterItem(pchar, "indian21"))
            {
                link.l2 = "Yes, I found it. And where is my money?";
                link.l2.go = "Step_11";
            }
		break;

 		case "Step_11":
        	dialog.text = "Heh, I'm ready to pay 30,000 for each item. Total - 90,000 coins. Agree?";
            link.l1 = "I am satisfied with the price. It's a deal.";
            if (pchar.questTemp.Ascold == "SoughtThreeObject")
            {
               link.l1 = "If you knew, Askold, how much I paid for these artifacts... But I understand that it is simply unrealistic to demand a refund from you, you are already offering a price six times more expensive... I agree.";
            }
    		link.l1.go = "Step_12";
            link.l2 = "No, give me more money.";
    		link.l2.go = "WantMoreMoney";
		break;

 		case "WantMoreMoney":
        	dialog.text = "Wow. It looks like I was wrong about you - you are beyond measure "+ GetSexPhrase("greedy man","greedy girl") +". Such people are nobody to me, I don't know them. I don't want to know you anymore.. "+
                          "Get out!";
        	link.l1 = "Hey Askold, wait! We are normal people, let's bargain, come to an agreement...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
			pchar.questdata.Ascold = 1;
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_12":
        	dialog.text = "So, here are your 90,000, and the items are now ours.";
        	link.l1 = "Take it.";
    		link.l1.go = "Step_13";
		break;

 		case "Step_13":
        	dialog.text = "Listen, if you want, drop by my place in a month or two. Maybe another job will turn up.";
    		link.l1 = "I will pass by - I will definitely visit you. You're not throwing in a dusty job, but the profit is decent.";
    		link.l1.go = "exit";
    		TakeItemFromCharacter(pchar, "indian19");
    		TakeItemFromCharacter(pchar, "indian20");
    		TakeItemFromCharacter(pchar, "indian21");
    		AddMoneyToCharacter(pchar, 90000);
			pchar.questTemp.Ascold = "TakenThreeObject";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		NextDiag.TempNode = "WalkTwoMounth";
    		AddQuestRecord("Ascold", "4");
		break;

		case "WalkTwoMounth":
		    if (GetQuestPastDayParam("questTemp.Ascold") > 62)
		    {
            	dialog.text = "Oh, finally! And I'm waiting for you. I need your services, " + GetFullName(pchar) + ".";
            	link.l1 = "What do you need to find this time?";
        		link.l1.go = "Step_14";
		    }
            else
            {
            	dialog.text = "Oh, who do I see?! "+ GetSexPhrase("My friend","My girlfriend") +", " + GetFullName(pchar) + ", glad to see you. If it's about work, then I can't please you with anything yet, I'm sitting penniless myself. And you come by sometime later.";
            	link.l1 = "Okay, Askold. I'll be in these parts - I'll look in.";
        		link.l1.go = "exit";
        		NextDiag.TempNode = "WalkTwoMounth";
            }
		break;

 		case "Step_14":
        	dialog.text = "You know, this time it's not about the search, it's going to be a more serious task.";
        	link.l1 = "Ooh, it's freezing... I smell a lot of money! Come on, state the problem.";
    		link.l1.go = "Step_15";
		break;

 		case "Step_15":
        	dialog.text = "The problem is as follows. The Spaniards, who have been ruthlessly exterminating the continental Indians and destroying their cultural heritage for hundreds of years, suddenly took care of collecting objects of this very Indian culture.. "+
                          "The fact is that at Marianne's court, out of nowhere, a strange fashion for objects of Indian worship arose. And now the Spaniards are scouring everywhere and collecting artifacts that I desperately need. And they ship what they find to the Old World. My business is suffering, and I don't agree with that.. "+
                          "In general, I managed to find out that a large batch of Aztec cult items of unprecedented value has been collected in Havana. I want to get these items, it is clear that I will not be able to take everything, but at least something.. "+
                          "And also, by the way... I want to get an inventory of the Indian goods collected by the Spaniards. De la Fontaine will be very interested to see her.";
        	link.l1 = "And that's all it is? No problem. You'll have everything. Do you know for sure that there is such an inventory?";
    		link.l1.go = "Step_16";
        	link.l2 = "Listen, don't be offended, but I can't do it right now. There is no time.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_16":
        	dialog.text = "Yes, exactly. My friends whispered to me here on a not unknown basis... An inventory is attached to the cargo, so where there are artifacts, there is an inventory.";
        	link.l1 = "Understood. Well, I'm getting started. So to speak, wait for me and I'll be back.";
    		link.l1.go = "exit";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		NextDiag.TempNode = "AfterManowarsBattle";
    		pchar.questTemp.Ascold = "ToHavanna";
    		AddQuestRecord("Ascold", "5");
		break;

 		case "AfterManowarsBattle":
        	dialog.text = "You did something errand?";
        	link.l1 = "Not yet, but I'm doing it.";
    		link.l1.go = "exit";
        	link.l2 = "I have no desire to deal with your problems anymore. I'm sorry.";
    		link.l2.go = "No_Work";
            if (pchar.questTemp.Ascold == "SeekInformatorHavanna")
            {
             	link.l1 = "Listen, in our last conversation you said something there about your friend who whispered to you about the list that I'm looking for.";
        		link.l1.go = "Step_17";
            }
            if (pchar.questTemp.Ascold == "ReciveInformationManowar")
            {
             	link.l1 = "Askold! I found your informant friend! This is a Spanish officer named Fernando Gonzalez in Santiago. By the way, he sent his regards to you...";
        		link.l1.go = "Step_20";
            }
            if (pchar.questTemp.Ascold == "ILookedThisAss" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "Askold! There's a Spanish squadron of six ships with Man at the head!!!";
        		link.l1.go = "Step_24";
            }
            if (pchar.questTemp.Ascold == "ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "Askold! You have the list, but there are still unsinkable ships.";
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "2ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "Askold! You have the list, but there are still unsinkable ships.";
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "I sank all the ships, but I couldn't find the inventory list.";
        		link.l1.go = "NoFoundList";
            }
    		if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "ILookedThisAss")
    		{
            	link.l1 = "Yes, damn me! I passed throught seven circles of hell, but I got list is for you. Here it is.";
        		link.l1.go = "Step_26";
    		}
    		if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "2ILookedThisAss")
    		{
            	link.l1 = "Yes, damn me! I passed throught seven circles of hell, but I got this list is for you. Here it is.";
        		link.l1.go = "Step_26";
    		}
            if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "Ascold_ManowarsDead")
            {
             	link.l1 = "I destroyed Spanish ships, I have the inventory list too.";
        		link.l1.go = "ManowarGoodWork";
            }
            if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "I sent the squadron to the bottom!";
        		link.l1.go = "ManowarGoodWork";
            }
			if (pchar.questTemp.Ascold == "Ascold_ManowarsNoDead")
            {
             	link.l1 = "Listen, I failed to sink the Spanish squadron. And I couldn't find any expedition near the temple.";
        		link.l1.go = "ManowarNoGoodWork";
            }
		break;

 		case "Step_17":
        	dialog.text = "So what?";
        	link.l1 = "I need your help, the fact is that I had a problem in Havana. I can't find out where the man went, on which the Indian artifacts were loaded. Let your friend help.";
    		link.l1.go = "Step_18";
		break;

 		case "Step_18":
        	dialog.text = "No, it won't do. I'm not going to talk all over the Caribbean about my connections.";
        	link.l1 = "But I'm acting in your best interests, after all!!!";
    		link.l1.go = "Step_19";
		break;

 		case "Step_19":
        	dialog.text = "That's right, but act on your own. Don't count on my help.";
        	link.l1 = "Well, thank you, friend Askold...";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "2SeekInformatorHavanna";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "Step_20":
        	dialog.text = "We will somehow manage to communicate without your mediation... Did you find anything?";
        	link.l1 = "Yes, the Spaniards found an Indian temple near Amatique Bay, south of Belize, and now an entire expedition is working there. And loaded ships are coming to this place from all over the New World.";
    		link.l1.go = "Step_21";
		break;

 		case "Step_21":
        	dialog.text = "Why?";
        	link.l1 = "I suppose they will plunder the Indian temple and go to Spain with all this.";
    		link.l1.go = "Step_22";
		break;

 		case "Step_22":
        	dialog.text = "Sad news. Then I have a request for you - you should destroy all Spaniards located near the bay of Amatique. All ships must go down, and the expedition itself at the temple must be destroyed.. "+
                          "And I need an inventory list of Spaniards.";
        	link.l1 = "I'm ready. I can start right now.";
    		link.l1.go = "Step_23";
        	link.l2 = "Don't you want too much from me, buddy? Look for a fool somewhere else.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_23":
        	dialog.text = "It's good, I don't even know how to thank you for your help...";
        	link.l1 = "We'll settle up later, friend Askold.";
    		link.l1.go = "exit";
    		AddQuestRecord("Ascold", "8");
    		pchar.questTemp.Ascold = "IMustKillAll";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "Step_24":
        	dialog.text = "Very good, this should make you happy. Are you a corsair or a rag? Destroy all the Spaniards and get me that damn inventory list.";
        	link.l1 = "Yes, of course. I will do it. You will have the inventory list and the Spaniards will be destroyed.";
    		link.l1.go = "Step_25";
            link.l2 = "It's without me. Look for a fool!";
    		link.l2.go = "No_Work";
		break;

 		case "Step_25":
        	dialog.text = "Well, so what are you standing for! Go destroy it.";
        	link.l1 = "I'm on my way.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "2ILookedThisAss";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "NoFoundList":
        	dialog.text = "And it's necessary to send a myriad of Spaniards to their forefathers, but I couldn't find any list. I don't deal with such inept people.. "+
                      "Get out of here!";
    		link.l1 = "Yeah, and that's after everything I've been through because of you...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
			pchar.questdata.Ascold = 1;
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_26":
        	dialog.text = "The list is good, you're good. But you need you to sink all ships of the Spaniards, and also clear the temple. No one should leave there alive.";
        	link.l1 = "Tell me a good reason that would interest me...";
    		link.l1.go = "Step_27";
            link.l2 = "You, of course, excuse me, I don't want to cut up poor Spaniards.";
    		link.l2.go = "No_Work";
            link.l3 = "Askold, I need money. After all, I delivered you a list. I would like to receive a reward.";
    		link.l3.go = "WantMoreMoney";
            BackItemDescribe("ShipsJournal");
            TakeItemFromCharacter(pchar, "ShipsJournal");
            pchar.questTemp.Ascold.list = 1;
		break;

 		case "Step_27":
        	dialog.text = "I am waiting for money from my patron, Pierre de la Fontaine. Be patient and I'll pay you in full.";
        	link.l1 = "Okay, I will destroy the Spaniards. I hope I'll be happy with the size of the reward.";
    		link.l1.go = "exit";
            AddQuestRecord("Ascold", "10");
	    	AddQuestUserData("Ascold", "sSex", GetSexPhrase("","a"));
		break;

 		case "ManowarGoodWork":
        	dialog.text = "You didn't destroy Spaniards on the island itself. All Spaniards working in the temple must be destroyed.";
        	link.l1 = "Okay, I'll finish the job.";
    		link.l1.go = "exit";
            link.l2 = "You, of course, excuse me, I don't want to cut up poor Spaniards anymore.";
    		link.l2.go = "Step_28";
    		NextDiag.TempNode = "ManowarGoodWork";
		break;

		case "ManowarNoGoodWork":
        	dialog.text = "And it is necessary! And he also called a privateer. I don't deal with such inept people.. "+
                      "Get out of here!";
    		link.l1 = "Yeah, and that's after everything I've been through because of you...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
			pchar.questdata.Ascold = 1;
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_28":
        	dialog.text = "Are you going to drop the case halfway?";
        	link.l1 = "Yeah, I'll quit because you got me.";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
			pchar.questdata.Ascold = 1;
    		pchar.questTemp.Ascold = "BreakeQuest";
    		pchar.quest.Ascold_FightNearTemple.over = "yes";
		break;

 		case "Ascold_KilledTemple":
        	dialog.text = "So you returned. What will please you?";
        	link.l1 = "Askold, the Spanish expedition to the Inca temple has been completely destroyed. But I couldn't find a damn inventory list anywhere.";
    		link.l1.go = "NoFoundList";
            if (CheckCharacterItem(pchar, "ShipsJournal") || CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
            	link.l1 = "Askold, the Spanish expedition to the Inca temple has been completely destroyed.";
        		link.l1.go = "Step_29";
                BackItemDescribe("ShipsJournal");
                TakeItemFromCharacter(pchar, "ShipsJournal");
                DeleteAttribute(PChar, "questTemp.Ascold.List");
            }
		break;

 		case "Step_29":
        	dialog.text = "Great! I knew I could rely on you.";
        	link.l1 = "I want to talk about the reward.";
    		link.l1.go = "Step_30";
		break;

 		case "Step_30":
        	dialog.text = "Yes, of course... Listen, I don't have anything to pay you with, I haven't received the money from the patron yet. You need to wait a bit.";
        	link.l1 = "Oh, there are no words... If you only knew what I've been through...";
    		link.l1.go = "Step_31";
		break;

 		case "Step_31":
        	dialog.text = "I understand, but I just don't have the money. I need to send to France the inventory list that you captured. I hope this will speed things up. Come and see me from time to time...";
        	link.l1 = "Well, have it your way. I will visit you whenever possible.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Mummie_begin";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		AddQuestRecord("Ascold", "12");
	        AddQuestUserData("Ascold", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Ascold", "sSex1", GetSexPhrase("xia","as"));
		break;

 		case "Mummie_begin":
        	dialog.text = "Glad to see you, "+ GetFullName(pchar) + ". But I don't have any news yet. The money hasn't arrived yet...";
        	link.l1 = "Sorry... Well, let's wait.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Mummie_begin";
		    if (GetQuestPastDayParam("questTemp.Ascold") > 40)
            {
            	dialog.text = "Oh, who do I see, "+ GetSexPhrase("my friend","my girlfriend") +" "+ GetFullName(pchar) + "...";
            	link.l1 = "Any news?";
        		link.l1.go = "Step_31A";
            }
		break;

 		case "Step_31A":
        	dialog.text = "Yes, but you won't like them. The fact is, I have received word from de la Fontaine.";
        	link.l1 = "Well, did he send the money?";
    		link.l1.go = "Step_32";
		break;

 		case "Step_32":
        	dialog.text = "Sent a little bit. But he wasn't interested in the work you did. The inventory list turned out to be clueless, and the destruction of the Spanish expedition, according to him, had a negative impact on European science as a whole.";
        	link.l1 = "Wow...";
    		link.l1.go = "Step_33";
        break;

        case "Step_33":
        	dialog.text = "To be honest, I don't have the words either. But life goes on. I have business with you.";
        	link.l1 = "And what is it this time?";
    		link.l1.go = "Step_34";
            link.l2 = "Listen, you should go somewhere far away with your business.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_34":
        	dialog.text = "De la Fontaine has unearthed some ancient documents in Europe, which seem to say that there is also some kind of tomb on our island, it is unclear who.. "+
                          "We should try to search the island properly and try to find this place if it really exists.";
        	link.l1 = "Okay, I'll do it. Will my work be paid this time?";
    		link.l1.go = "Step_35";
        	link.l2 = "Listen, Askold, do I look like a grave digger? I'm not going to dig into graves.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_35":
        	dialog.text = "Don't even doubt it. This is a direct order from the patron, so if successful, there will be payment.";
        	link.l1 = "Okay, I got it. I will look for it.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Seek_Grave";
    		AddQuestRecord("Ascold", "13");
    		CloseQuestHeader("Ascold");
			pchar.questdata.Ascold = 1;
    		pchar.questTemp.Ascold = "Ascold_SeekGrave";
		break;

 		case "Seek_Grave":
        	dialog.text = "Did you find anything?";
        	link.l1 = "Not yet, we are looking for...";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Seek_Grave";
            if (pchar.questTemp.Ascold == "Ascold_SeekGrave")
            {
            	dialog.text = "Ah, good afternoon, "+ GetSexPhrase("my friend","my friend") +". How are you, what will please you?";
            	link.l1 = "Damn it, Askold, I climbed everything in the area, but nothing was found. Absolutely nothing.";
        		link.l1.go = "Step_36";
            }
            if (pchar.questTemp.Ascold == "Ascold_CantSeekGrave")
            {
            	dialog.text = "What do you say this time? Did you find anything?";
            	link.l1 = "No. There is no tomb here, it's all stupid...";
        		link.l1.go = "Step_37";
            }
            if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
            {
            	dialog.text = "How are the search results? Is there anything new?";
            	link.l1 = "I don't know exactly what it is, but I found there an entrance somewhere in the cave, but it is closed.";
        		link.l1.go = "Step_38";
            }
            if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && !CheckCharacterItem(pchar, "Rock_letter"))
            {
            	dialog.text = "Found the tablets?";
            	link.l1 = "Not yet, but I'm doing it.";
        		link.l1.go = "exit";
            }
            if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && CheckCharacterItem(pchar, "Rock_letter"))
            {
            	dialog.text = "Ah, I see by the burning eyes that you have found the tablets.";
            	link.l1 = "Exactly, I found them, carramba!";
        		link.l1.go = "Step_45";
            }
            if (pchar.questTemp.Ascold == "Ascold_EnterGrave")
            {
            	dialog.text = "Did you manage to get into the tomb?";
            	link.l1 = "Not yet, but I'm working on it.";
        		link.l1.go = "exit";
            }
		break;

 		case "Step_36":
        	dialog.text = "Hmm, I don't even know what to say.. "+
                          "Maybe there is no tomb, I don't know... But still, if you are lucky enough to find something, I will be glad to see you.";
        	link.l1 = "Well, I'll try again.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_CantSeekGrave";
		break;

 		case "Step_37":
        	dialog.text = "Maybe not, maybe there is... Keep looking.";
        	link.l1 = "Okay.";
    		link.l1.go = "exit";
		break;

 		case "Step_38":
        	dialog.text = "Yeah, it seems you found exactly what de la Fontaine is looking for... "+
                          "Damn it, I'm sure that's where the tomb is located. We must try to get inside at all costs.";
        	link.l1 = "Easy to say. And how to do it? It is clear that there is an entrance, but it is tightly blocked by a rock.";
    		link.l1.go = "Step_40";
		break;

 		case "Step_40":
        	dialog.text = "Hmm, that's how it is... Listen, apparently this protection of graves, akin to which the pharaohs used in Egypt to protect their crypts from uninvited guests.. "+
                          "From my experience working with de la Fontaine, and he is a famous Egyptologist, I can say that somewhere nearby there is a mechanism that opens the entrance.. "+
                          "As a rule, this is some kind of object that needs to be placed somewhere.";
        	link.l1 = "And what is this item? And where to put it?";
    		link.l1.go = "Step_41";
		break;

 		case "Step_41":
        	dialog.text = "Well, I can't know for sure. Wait, though.. "+
                          "De la Fontaine, in his letter in which he gives the task to find the tomb, writes that there is a mention of some kind of stone tablet. I didn't think much of it, but it seems to be important.. "+
                          "So, it mentions that certain tablets open the way to Leif the Happy. Apparently, this is the desired item.";
        	link.l1 = "And who is Leif the Happy?";
    		link.l1.go = "Step_42";
		break;

 		case "Step_42":
        	dialog.text = "Didn't I tell you? It's his tomb you're looking for.";
        	link.l1 = "Yes, business... So what about the tablets? Where should I look for them and where should I put them?";
    		link.l1.go = "Step_43";
		break;

 		case "Step_43":
        	dialog.text = "You need to look for them here, in the Caribbean Sea. You know, they bring me all sorts of junk, but I haven't even heard of any tablets. So, I think we should look on uninhabited islands or on the west coast of Main, near pearl fisheries. Or maybe where are the ruins of the temple that the Spaniards found. Otherwise, these tablets would have been found long ago and brought to me for sale.. "+
                          "I do not know where to put it, but I think there is a place for just this somewhere near the entrance. We need to look for it.";
        	link.l1 = "Interesting. Well, I guess I'll start looking for these tablets. I hope that this entrance really leads to the right place.";
    		link.l1.go = "Step_44";
        	link.l2 = "I'm tired of running around without a specific goal. I won't look for anything else.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_44":
        	dialog.text = "I really hope so. Well, good luck with your search!";
        	link.l1 = "Thank you for the wish.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_SeekRockLetter";
            // ==> Делаем скрижали видимыми, теперь их можно найти.
            sld = ItemsFromID("Rock_letter");
            sld.shown = 1;
		break;

 		case "Step_45":
        	dialog.text = "Activate them and try to get into the tomb.";
        	link.l1 = "I really hope that everything will work out and my work will not be wasted.";
    		link.l1.go = "exit";
			bDisableLandEncounters = true; //закроем энкаунтеров, лучше раньше, чем баги.
    		pchar.questTemp.Ascold = "Ascold_EnterGrave";
		break;

 		case "Found_Grave":
            if (pchar.questTemp.Ascold == "Ascold_FoundMummy")
            {
            	dialog.text = "Ah, here you are, " + GetFullName(pchar) + "! Tell me quickly that you did you found.";
            	link.l1 = "I managed to open the entrance to the cave. In the cave, in one of the branches there was an entrance to the tomb. I found her.";
        		link.l1.go = "Step_46";
            }
		break;

 		case "Step_46":
        	dialog.text = "A thousand devils! Oh, my God! Did you find something inside?";
        	link.l1 = "There is a stone sarcophagus in the middle of the tomb, covered with a massive slab. I couldn't move the stove, there is nothing suitable for such an event.";
    		link.l1.go = "Step_47";
		break;

 		case "Step_47":
        	dialog.text = "Hmm, there were no valuables, burial items and other nonsense?";
        	link.l1 = "There was nothing special.";
    		link.l1.go = "Step_48";
		break;

 		case "Step_48":
        	dialog.text = "Hmm... So everything is inside.. "+
                          "Here's what, take this crowbar, use it as a lever and you can move the slab from the sarcophagus.";
        	link.l1 = "Hmm, not sure that it worth disturbing the dead man that lies there...";
    		link.l1.go = "Step_49";
		break;

 		case "Step_49":
        	dialog.text = "Heh, well, well! Captain, these are just rotted bones. You're a corsair, are you afraid of death?";
        	link.l1 = "I'm not afraid of anything. It's just that I personally would hate it if some grave digger sorted through my remains in my grave.";
    		link.l1.go = "Step_50";
		break;

 		case "Step_50":
        	dialog.text = "Are you taking it or not?";
        	link.l1 = "I'll take it. I wonder what's in there...";
    		link.l1.go = "Step_51";
		break;

 		case "Step_51":
        	dialog.text = "Well, that's wonderful. Take your crowbar. Well, I'm looking forward to seeing you.";
           	link.l1 = "Okay, Askold.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_WateringMummy";
		LAi_LocationDisableToughSkeletonTimer("Guadeloupe_Cave", 9999); //ПК не пускать 30 лет
    		GiveItem2Character(Pchar,"Ascold_rabble");
		break;

 		case "AfterAttackMummy":
        	dialog.text = "Ah, here you are. You can't imagine what was going on in the city! The city was stormed by walking skeletons!!!";
        	link.l1 = "Really?! It can't be!";
    		link.l1.go = "Step_52";
            if (pchar.questTemp.Ascold == "Ascold_SaveWorld")
            {
            	dialog.text = "Well, I'm sorry, a monster?";
            	link.l1 = "Not yet, I'm in the process of being destroyed.";
        		link.l1.go = "exit";
                NextDiag.TempNode = "AfterAttackMummy";
            }
            if (GetCharacterIndex("LeifEricson") == -1)
            {
            	dialog.text = "Well, how are you doing to save the world?";
            	link.l1 = "Yes, everything is fine, the world is saved, people can sleep peacefully.";
        		link.l1.go = "Step_60";

				// перебиваем иниты пещеры - возвращаем сферы обратно и закрываем гробницу   - ugeen fix
				locations[FindLocation("Guadeloupe_CaveEntrance")].reload.l1.name = "reload1_back";
				locations[FindLocation("Guadeloupe_CaveEntrance")].reload.l1.emerge = "reload1";

				locations[FindLocation("Guadeloupe_Cave")].reload.l1.name = "reload1_back";
				locations[FindLocation("Guadeloupe_Cave")].reload.l1.emerge = "reload1";
				LocatorReloadEnterDisable("Guadeloupe_Cave", "reload1_back", false);

				RestoreOfficers_Ascold(pchar);
				Log_Info("The passage to the tomb has closed");
            }
		break;

 		case "Step_52":
        	dialog.text = "Can't?! They killed half the garrison, and scared the governor of the city so much that he just pooped in his pants!. "+
                          "During the assault, I barricaded myself on the second floor and thus avoided problems. It wasn't easy for these walking mummies to get to me...";
        	link.l1 = "Glad for you... By the way, would you like to know what was in the crypt?";
    		link.l1.go = "Step_53";
		break;

 		case "Step_53":
        	dialog.text = "In which crypt? Oh, so you opened it?";
        	link.l1 = "Yeah, I opened it. Your poker came in handy.";
    		link.l1.go = "Step_54";
		break;

 		case "Step_54":
        	dialog.text = "The devil! As soon as you leave, I received a letter from de la Fontaine. He wrote that he had managed to decipher the ancient manuscripts completely.. "+
                          "They say if you open a stone coffin, it'll wake up some ancient Indian monster.";
        	link.l1 = "That's what happened. This monster is the damn mummy that I've been looking for for so long.";
    		link.l1.go = "Step_55";
		break;

 		case "Step_55":
        	dialog.text = "And what happened next?";
        	link.l1 = "Then I... well, in general, the attack on the skeleton city was his doing.";
    		link.l1.go = "Step_56";
		break;

 		case "Step_56":
        	dialog.text = "Damn it! We've played it out with you.. "+
                          "What should we do now? This awakened monster will destroy everyone on the island.";
        	link.l1 = "Not only on the island. He's going to be the master of the world. The whole world is not enough for him...";
    		link.l1.go = "Step_57";
		break;

 		case "Step_57":
        	dialog.text = "Wow... Listen, it sounds stupid, but you must save the world.";
        	link.l1 = "Why me? For example, don't you want to save the world? After all, you sent me there, and you will be stronger than me.";
    		link.l1.go = "Step_58";
		break;

 		case "Step_58":
        	dialog.text = "Harder, I don't argue. I'm good with a shaft, but a sword is not mine.. "+
                          "You said about the cave, you'll have to go there. And how am I going to wave a shaft in a cramped space? It won't work for me.";
        	link.l1 = "Yes, that's right, it won't come out with a shaft... Well, I'll save the world myself. There's nowhere to go.";
    		link.l1.go = "Step_59";
		break;

 		case "Step_59":
        	dialog.text = "Wow, it's great that you agreed. Good luck with this difficult task, "+ GetSexPhrase("friend","girlfriend") +".";
        	link.l1 = "Thank you for the wish, Askold. It will help me a lot.";
    		link.l1.go = "exit";
			LocatorReloadEnterDisable("Guadeloupe_Cave", "reload3_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], false);
			pchar.quest.Ascold_LeifIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.Ascold_LeifIsDead.win_condition.l1.character = "LeifEricson";
			pchar.quest.Ascold_LeifIsDead.function = "Ascold_LeifIsDead";
			NextDiag.TempNode = "AfterAttackMummy";
    		pchar.questTemp.Ascold = "Ascold_SaveWorld";
			sld = characterFromId("LeifEricson");
            LAi_SetImmortal(sld, false);
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_group_MoveCharacter(sld, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;

 		case "Step_60":
        	dialog.text = "Great. Yeah, it wasn't easy for you, apparently.. "+
                          "Listen, did you find anything interesting there? De la Fontaine will be coming to the island soon, it will be great to show him something.";
        	link.l1 = "No, I didn't find anything.";
    		link.l1.go = "Step_61";
            if (CheckCharacterItem(pchar, "Azzy_bottle"))
            {
            	link.l2 = "Some kind of lamp, this is Leif's eastern one. I don't know what it is.";
        		link.l2.go = "Step_63";
            }
		break;

 		case "Step_61":
        	dialog.text = "Oh, it's a pity... Listen, maybe we should look at it again.. "+
                          "I feel there must be something useful for de la Fontaine. You can get so much money for an interesting little thing...";
        	link.l1 = "Now listen to me, Askold. I've been through so much doing your errands that I've had enough impressions for a dozen lifetimes. That's enough, I'm not working with you anymore.";
    		link.l1.go = "Step_62";
		break;

 		case "Step_62":
        	dialog.text = "Oh, it's a pity. But I see that it's useless to persuade you. Well, let's part as friends.";
        	link.l1 = "Yeah, so be it.";
    		link.l1.go = "exit";
            NextDiag.TempNode = "GoodFriends";
            pchar.questTemp.Ascold = "Ascold_OverBusiness";
			UnlockAchievement("Mummydust_quest", 3);
		break;

 		case "GoodFriends":
        	dialog.text = "Oh! "+ GetSexPhrase("Old Man","Beauty") +" " + GetFullName(pchar) + "! It's good to see you again. Are you on business or just dropped by?";
        	link.l1 = "Just wanted to see you.";
    		link.l1.go = "exit";
            NextDiag.TempNode = "GoodFriends";
            if (pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
            	link.l1 = "Listen, I have a case for you. Do you happen to know how I can find the demon?";
        		link.l1.go = "Step_64";
            }
		break;

 		case "Step_63":
        	dialog.text = "Well, sell it to me. 50,000 for this stuff.";
        	link.l1 = "There's nothing inside, it's too light... Okay, take it, I don't need it.";
    		link.l1.go = "BuyAzzy";
        	link.l2 = "No, Askold, I will return to the ship, I will try to find where the lamp would be neatly cut or soldered for me. I'll see what's inside.";
    		link.l2.go = "Step_62";
		break;

 		case "BuyAzzy":
        	dialog.text = "Your money is our thing. Maybe we can work together some more? Such cases await us...";
        	link.l1 = "No, Askold. I've had enough of this kind of adventure.";
    		link.l1.go = "Step_62";
            TakeItemFromCharacter(pchar, "Azzy_bottle");
            AddMoneyToCharacter(pchar, 50000);
		break;

 		case "Step_64":
        	dialog.text = "What?!!";
        	link.l1 = "I need one demon, I can't find it in any way. And the question is vital.";
    		link.l1.go = "Step_65";
		break;

 		case "Step_65":
        	dialog.text = "Have you already established communication with demons?!";
        	link.l1 = "It's all thanks to you, or rather, your orders! Listen, maybe there are recipes for summoning demons, the Toltecs seem to have one.";
    		link.l1.go = "Step_66";
		break;

 		case "Step_66":
        	dialog.text = "They have a ritual, I even know which one. I can't guarantee that it will work, but you can try.";
        	link.l1 = "What kind of ritual? Tell me!!!";
    		link.l1.go = "Step_67";
		break;

 		case "Step_67":
        	dialog.text = "In general, three Toltec crystal skulls are needed. Our governor had them, but do you remember when the skeletons attacked the city, then their chief took these skulls.";
        	link.l1 = "Ah, that's what Leif needed them for... Clear. And then what?";
    		link.l1.go = "Step_68";
		break;

 		case "Step_68":
        	dialog.text = "We also need a strange object, an idol of an ancient deity. You collect all three items - and you are looking for a person who can perform the ceremony. Some local witch will do just fine.";
        	link.l1 = "Can a witch? I know one such lady...";
    		link.l1.go = "Step_69";
		break;

 		case "Step_69":
        	dialog.text = "That's great. Now get the items and go ahead. I suppose your witch is familiar with the ritual, since she is a witch.";
        	link.l1 = "I suppose so. By the way, do you have any of these items? I would buy .";
    		link.l1.go = "Step_70";
		break;

 		case "Step_70":
           	dialog.text = "No, there is nothing. So search for yourself.";
        	link.l1 = "Well, thanks for that too. Be healthy.";
    		link.l1.go = "exit";
            pchar.questTemp.Azzy = "DestrContract";
        	if (sti(pchar.questTemp.Azzy.Immortal.Penalty) >= 15 && GetQuestPastDayParam("questTemp.Azzy") > 90)
        	{
                dialog.text = "Yes. I just got those governor's skulls. I found them in caves, risked my life...";
                link.l1 = "I'm ready tobuy them from you for any price. How much do you want?";
                link.l1.go = "Step_71";
            }
		break;

 		case "Step_71":
        	dialog.text = "I won't take money from you. After all, de la Fontaine and I owe you more... How much did you do for us... Waiting for the reward? Let's assume that we're even. And take the skulls.";
        	link.l1 = "Thank you very much, Askold. Listen, have you found a strange thing, an idol of a deity?";
    		link.l1.go = "Step_72";
            GiveItem2Character(pchar, "sculMa1");
            GiveItem2Character(pchar, "sculMa2");
            GiveItem2Character(pchar, "sculMa3");
            GiveItem2Character(pchar, "indian22");
		break;

 		case "Step_72":
        	dialog.text = "Well, I found it. Take it too, what's the problem?";
        	link.l1 = "Good, very good. Now I'm ready to get back to a normal life. Thank you, Askold.";
    		link.l1.go = "exit";
		break;
	}
}


