// Джон Моррис, авторитетный корсар по английской линейке
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			dialog.text = "Please leave my house. I'm busy, and I don't have time to talk to you.";
			link.l1 = "I'm already leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.Sharp == "begin" && rand(1))
			{
				link.l1 = "John, I heard about the pearl fishermen who fish in our waters. Are you not aware of this issue?";
				link.l1.go = "SharpPearl_1";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			dialog.text = LinkRandPhrase(GetFullName(pchar) + ", glad to see you! Why did you here?",
                                         RandSwear() + " Who do I see?!" + GetFullName(pchar) + "! What brings you to the island?",
                                         "So, so, "+ GetFullName(pchar)+ " I have a guest. I'd like to see you handle a blade again... Well, what are the questions, "+ GetSexPhrase("friend","girlfriend") +"?");
			link.l1 = RandPhraseSimple("Just dropped by to check on you.", "Small things, nothing significant.");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (pchar.questTemp.Sharp == "begin" && rand(1))
			{
				link.l1 = "John, I heard about the pearl fishermen who fish in our waters. Are you not aware of this issue?";
				link.l1.go = "SharpPearl_1";
			}
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = "No, I don't know. This is to Sharp, "+ GetSexPhrase("buddy","girlfriend") +". I can't bring myself to call him captain...";
			link.l1 = "Do you know where to find it?";
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
		break;
		case "SharpPearl_2":
			dialog.text = "I have no idea. I'm not interested in pearl cases. Although, if I were you, I'd look for him in brothels. Sooner or later you'll find him there...";
			link.l1 = "Okay, John, thanks.";
			link.l1.go = "exit";
		break;
		//********************* Английская линейка *********************
 		case "EngLine_quests":
            dialog.text = "Please leave my house. I'm busy, and I don't have time to talk to you.";
			link.l1 = "I'm already leaving.";
			link.l1.go = "exit";
			switch (pchar.questTemp.State)   // Доступ к квестам
            {
	     		case "go_talks_with_pirates":
	    			dialog.text = "Tell me why you came?";
	    			link.l1 = "I'm here on behalf of the Governor-General of Jamaica, Sir Thomas Madiford.";
	    			link.l1.go = "Step_1";
	      		break;
            }
		break;

 		case "Step_1":
			dialog.text = "It's already interesting! Madiford doesn't like me, so what made him send me "+ GetSexPhrase("pirate","his man") +"?";
			link.l1 = "Madiford is assembling a squadron to attack Curacao.";
			link.l1.go = "Step_2";
  		break;

 		case "Step_2":
			dialog.text = "Without me.";
			link.l1 = "Why?";
			link.l1.go = "Step_3";
  		break;

 		case "Step_3":
			dialog.text = "The Governor General of Jamaica treats me, to put it mildly, not friendly. Therefore, his invitation to participate in the case causes me serious concerns. Something is not right here.";
			link.l1 = "Perhaps Madiford has turned his anger to mercy.";
			link.l1.go = "Step_4";
  		break;

 		case "Step_4":
			dialog.text = "You don't know Madiford well. No, I'm not that stupid, there's something wrong here. There may be a bloodbath ahead, and somehow I don't want to wash my face in blood for the sake of the Governor-General of Jamaica. So without me, and good luck to you, "+ GetSexPhrase("corsair","girlfriend") +".";
			link.l1 = "Thank you. And good luck to you, friend.";
			link.l1.go = "exit";

            AddQuestRecord("Eng_Line_2_Talking", "5");
            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")   {pchar.questTemp.State = "after_talks_with_pirates";}
            NextDiag.TempNode = "First time";
  		break;

 		case "Lets_go_bussines":
			dialog.text = "Yeah, here you are again. What do you say now?";
			link.l1 = "I'm involved in the Morgan case. Are you ready to storm Belize?";
			link.l1.go = "Step_5";
  		break;

 		case "Step_5":
            if (GetCompanionQuantity(pchar) != 4)
            {
    			dialog.text = "I am ready to speak immediately.";
    			link.l1 = "Then go ahead!";
    			link.l1.go = "Step_6";
            }
            else
            {
    			dialog.text = "I saw four ships on the raid. If I also go with you, then we will only interfere with each other during the assault. So without me this time.";
    			link.l1 = "Well, as you know, be healthy.";
    			link.l1.go = "exit";
                NextDiag.TempNode = "First time";
            }

  		break;

 		case "Step_6":
			AddQuestRecord("Eng_Line_3_Morgan", "5");
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
            ChangeCharacterAddressGroup(NPChar, "PortSpein_houseF2", "goto", "goto3");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 6, false);
            Fantom_SetBalls(npchar, "pirate");
            npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
            pchar.questTemp.CompanionQuantity = makeint(sti(pchar.questTemp.CompanionQuantity) + 1);
            pchar.questTemp.CompanionQuantity.Morris = true;
            NextDiag.TempNode = "Have_hot_bussines";
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

  		break;

	 	case "Have_hot_bussines":   // Если геймеру вдруг захочется ещё пообщаться, не знаю, сможет ли. Но на всякий случай.
			dialog.text = "We have to hurry, time is running out.";
			link.l1 = "We'll make it in time.";
			link.l1.go = "exit";
            NextDiag.TempNode = "Have_hot_bussines";
  		break;

	 	case "Gold_found_in_fort":    // Нода разговора в форте Куманы
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris") && !IsCompanion(characterFromID("John Morris")))
    		{
            	dialog.text = "Damn it, my galleon went down! I lost the ship and a good quarter of the crew. Sorry for the good guys..\n"+
                              " Oh, one thing, for the survivors life goes on, and the reward is the gold of Cumana. We found gold in this room underneath the planks on the floor. You're a real corsair."+ GetSexPhrase("",", though a girl") +".";
            }
            else
            {
            	dialog.text = "I didn't have to search for a long time, damn it! We found gold in this room under the floorboards. You are a real corsair"+ GetSexPhrase("",", though a girl") +".";
            }
			link.l1 = "Thank you. Glad to hear it from you.";
			link.l1.go = "Step_7";
        break;

	 	case "Step_7":
			dialog.text = "I'm going to my place in Trinidad. You can always find me there.";
			link.l1 = "Have a nice day, John. We'll meet again!";
			link.l1.go = "Step_8";
        break;

	 	case "Step_8":
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
        break;

		//********************* Французская линейка *********************
        case "FraLine8_talk":
            dialog.text = "Who are you and what do you need?";
            link.l1 = "I am the captain " + GetFullName(pchar) + ". But I need a trifle. Messengers from Governor General Madiford will surely arrive to you...";
            link.l1.go = "Step_F8_1";
        break;
        case "Step_F8_1":
            dialog.text = "What kind of messengers? Speak plainly, don't hint at me here!";
            link.l1 = "Okay, John. The question is essentially the following - Madiford is preparing an attack on the Dutch and wants to involve the Brethren in this case.";
            link.l1.go = "Step_F8_2";
        break;
        case "Step_F8_2":
            dialog.text = "So what?";
            link.l1 = "It's important to me that you don't participate in this adventure.";
            link.l1.go = "Step_F8_3";
        break;
        case "Step_F8_3":
            dialog.text = "Heh, I don't like the idea of attacking the Dutch and I'll probably agree to your suggestion. But you'll have to do something for me.";
            link.l1 = "What exactly?";
            link.l1.go = "Step_F8_4";
        break;
        case "Step_F8_4":
            dialog.text = "I don't know, I thought you are familiar with this story... Well, in general, the thing is as follows: a certain merry fellow, Captain Gay, took a walk on the sea, not knowing where his own were, where strangers were, let a couple of English merchants go around the world, and when it smelled fried, blamed everything on me. I was on a camping trip then, too, and Madiford had been itching to rein me in for a long time. In general, I don't have access to Port Royal right now.";
            link.l1 = "And what do you suggest?";
            link.l1.go = "Step_F8_5";
        break;
        case "Step_F8_5":
            dialog.text = "You see, all this mess is beneficial to me. If Madiford asks me for a favor, then the charges against me are dropped. Well, if you can get documents proving that I did not arrange the lawlessness of which I am accused, that's also good. The second option is preferable to me, since I do not want to spoil relations with the Dutch.";
            link.l1 = "Well, a favor for a favor. I'll try to get a document justifying you. What do you recommend to do?";
            link.l1.go = "Step_F8_6";
        break;
        case "Step_F8_6":
            dialog.text = "To rummage through Captain Gay's documents, I need his logbook.";
            link.l1 = "Well, I got it. I'll act, and you don't do anything until I get back.";
            link.l1.go = "Step_F8_7";
        break;
        case "Step_F8_7":
            dialog.text = "Hurry up...";
            link.l1 = "Absolutely!";
            link.l1.go = "exit";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "6");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("en","on"));
			NextDiag.TempNode = "Step_F8_Result";
			// ==> открываем дверь таверны Порт Рояля - там кэп Гей.
			LocatorReloadEnterDisable("PortRoyal_tavern", "reload2_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_tavern_upstairs")], false);
            ref sld = GetCharacter(NPC_GenerateCharacter("CaptainGay", "bocman", "man", "man", 40, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 40, 100, 90, "blade34", "pistol5", 150);
            sld.Dialog.Filename    = "Quest\FraLineNpc_2.c";
        	sld.name 	= "Captain";
        	sld.lastname 	= "Gay";
			sld.items.ShipsJournal = 1;
			sld.money = 65720;
			sld.items.potion4 = 4;
			sld.items.potionrum = 1;
			sld.items.potionwine = 2;
			sld.items.sculMa2 = 1;
			sld.items.jewelry17 = 30;
			sld.items.jewelry18 = 15;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_NoRebirthEnable(sld);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_tavern_upstairs", "goto", "goto1");
		break;
        case "Step_F8_Result":
            dialog.text = "Well, how are you doing, Captain? Did you get the ship's log of that Gay bastard?";
			if (CheckCharacterItem(pchar, "ShipsJournal"))
			{
				link.l1 = "There are two news items, and both are good, which happens infrequently. Gay went to his forefathers. And his magazine-here it is.";
				link.l1.go = "Step_F8_8";
			}
			else
			{
				link.l1 = "Not yet... But I'm working on it, everything will be...";
				link.l1.go = "exit";
			}
        break;
        case "Step_F8_8":
            dialog.text = "So-so... Yes, I assumed that this peacock would paint his exploits in all colors. Well, I'll send this notebook with reliable people to Madiford, and I'm sure he won't blackmail me anymore. And you can calm the Dutch down - I won't touch them!";
            link.l1 = "Great, Morris. Well, now I have to go, goodbye...";
            link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count)+1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "7");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("","a"));
            TakeItemFromCharacter(pchar, "ShipsJournal");
        break;

		//********************* Пиратская линейка *********************
		case "PL_Q8_deck":
			dialog.text = "And what are you doing on my deck? We're going to Porto Bello!";
			link.l1 = "Yes, I remember...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = "You shouldn't waste time, trust me.";
			link.l1 = "Yes, I know.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;


	}
}
