
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;

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

		case "First time":
			dialog.text = "Greetings, "+ GetSexPhrase("brother","sister") +"!";
			link.l1 = GetSexPhrase("Brother","Sister") +"? You're obviously a half-breed Indian. And what are you doing in such rags?";
			link.l1.go = "Meeting_1";
			NextDiag.TempNode = "First time";
		break;

        case "Meeting_1":
			dialog.text = "Was my mistake? You're a white man, I'm white, my name is even 'White Boy'. Clothes are a memory of my ancestors, I've been wearing them for a long time.";
			link.l1 = "Well, yes, not a girl for sure, but you're clearly over the age of a boy, but you still don't have the mind. Why go around in rags all your life?";
			link.l1.go = "Meeting_2";
		break;

		case "Meeting_2":
			dialog.text = "Don't understand yours. I am the son of the daughter of the chief shaman and the white captain of a large ship. I wear it so that the spirits do not see me and do not take me to themselves.";
			link.l1 = "In general, another fool, everything is clear. Do you sell pearls?";
			link.l1.go = "Meeting_3";
		break;

		case "Meeting_3":
			dialog.text = "I buy pearls.";
			link.l1 = "Buy or sell? Do you have any?";
			link.l1.go = "Meeting_4";
		break;

		case "Meeting_4":
			dialog.text = "No, not now, but you need to.";
			link.l1 = "You confused me like a fool. Goodbye.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "AfterMeet";
			ReOpenQuestHeader("GhostShipQuest");
        	AddQuestRecord("GhostShipQuest", "4");
		break;

		case "AfterMeet":
			dialog.text = "White "+ GetSexPhrase("brother","sister") +" he's back. Do you have something to say?";
			link.l1 = "No, we have nothing to talk about.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "AfterMeet";
			bOk = (sti(PChar.GenQuest.GhostShip.KillMe) > 0) || (sti(PChar.GenQuest.GhostShip.DeadByMe) > 0);
			if (bOk && !CheckAttribute(pchar , "GenQuest.GhostShip.NeedCoins"))
            {
    			Link.l3 = "What do you know about the ghost ship?";
    			Link.l3.go = "GhostCapt";
			}
			if (GetCharacterItem(Pchar, "Coins") >= 666 && CheckAttribute(pchar , "GenQuest.GhostShip.NeedCoins"))
			{
                Link.l4 = "I'm a prin"+ GetSexPhrase("eu","if") +"your pearls.";
    			Link.l4.go = "quest_coin_2";
			}
		break;

		// корабль
		case "GhostCapt":
			NextDiag.TempNode = "AfterMeet";
			dialog.Text = "A big ship? Swim around for a long time, be simple before, then become a ghost with a black sail.";
			Link.l1 = "When and how did he appear?";
			Link.l1.go = "GhostCapt_1";
		break;

		case "GhostCapt_1":
			dialog.Text = "A mistake, or maybe the evil spirit of the captain visited. They were here 40 winters ago, lived and traded in peace. The captain will greatly offend the tribe, take my mother by force, plunder us, steal the sacred black pearls.";
			Link.l1 = "Hmm... It's a normal thing, but how did the ghost ship come about?";
			Link.l1.go = "GhostCapt_2";
		break;

		case "GhostCapt_2":
			dialog.Text = "I've explained everything already. Don't you listen? Our leader demanded the captain's life as a sign of reconciliation, the sailors supported the captain and the ship sailed far, far away. Then the shaman of our people cursed the captain and the ship.";
			Link.l1 = "The curse seemed like something bad to me. How did they gain power and immortality?";
			Link.l1.go = "GhostCapt_3";
		break;

		case "GhostCapt_3":
			dialog.Text = "They will suffer, suffer a lot. It doesn't work out that way, the power of the sacred pearls protects them, they will suffer until everything comes back. I've been standing here since I was born and collecting our pearls back, changing them to white, they sell, I search.";
			Link.l1 = "In my opinion, other people suffer more from this curse. Cut their throats at night, and that's it. How can immortality be removed from them?";
			Link.l1.go = "GhostCapt_4";
		break;

		case "GhostCapt_4":
			dialog.Text = "There's not much left, they've already spent almost everything, I've collected everything that was, there's very little left, I need 666 black pearls from their ship. Then the curse will turn out to be the right side.";
			Link.l1 = "Okay, wait for me and I'll be back!";
			Link.l1.go = "Exit";
			AddQuestRecord("GhostShipQuest", "5");
			PChar.GenQuest.GhostShip.NeedCoins = true;
		break;

		case "quest_coin_2":
            dialog.Text = "That's great. You save us all! Hurry up and give them to me. All you have to do is meet the ship again and break it down or take it by battle. This is the end of their journey. Now they become just pirates, without the black sail.";
			Link.l1 = "Good. Take them away.";
			Link.l1.go = "Exit";
			TakeNItems(pchar, "Coins", -666);
			AddQuestRecord("GhostShipQuest", "6");
			AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("","a"));
			PChar.GenQuest.GhostShip.LastBattle = true;
			NPChar.location = "none";
			NPChar.LifeDay = 0;
			GhostShipOnMap();
            NextDiag.TempNode = "temp_coins";
		break;

		case "temp_coins":
            dialog.Text = "Thank you, friend.";
			Link.l1 = "I hope everything will be as you promised.";
			Link.l1.go = "Exit";
			NextDiag.TempNode = "temp_coins";
		break;

		case "GhostCapt_Prize":
			dialog.text = "Greetings, " + GetSexPhrase("young man","lady") + "! It has been a long time since such brave and skillful captains appeared in our swamp."
			link.l1 = "Who are you?! And where did you come from here?";
			link.l1.go = "GhostCapt_Prize1";
		break;

		case "GhostCapt_Prize1":
			dialog.text = "Yes... few, even of those who saw me alive, would recognize old Davy Jones now...";
			link.l1 = "So you are the legendary captain of the Flying Dutchman Davy Jones?!";
			link.l1.go = "GhostCapt_Prize2";
		break;

		case "GhostCapt_Prize2":
			dialog.text = "Ho ho! No, "+ GetSexPhrase("young man","lady") +", I am his pathetic likeness, or rather, what is left of him...  " +
				"Well, come on, get to the point - how did you not scare? Yes, I also managed to make so many holes in it that I sent it into the mouth of the squid, haha.. " +
				"Okay, I'm not offended - nothing will happen to him, he will be afloat again tomorrow. Although, admit that you were pretty lucky if it wasn't for that ball under the waterline - you'd floundering like a shrimp in shallow water right now, ha ha ha.. " +
				"and make it up tomorrow company for my guys. And I would love to take you on the team as a first assistant. Don't you want to?";
			link.l1 = "No, that's why I tried so hard not to go to the next world after the battle. I still have a lot to do here.";
			link.l1.go = "GhostCapt_Prize21";
		break;

		case "GhostCapt_Prize21":
			dialog.text = "Well, if that's your fate, live... while. Ah, admit it - I gave you a good beating too, ho-ho-ho... " +
				"Oh, if it weren't for that ball right under the waterline... I have a few thoughts here on how to thank you in return. I think I'll give you this charm. 'Jonah' he is called by knowledgeable people. If you own it, you won't be afraid of any storm anymore. Here, don't be afraid, it's not a damn thing.";
				Log_Info("You have received the 'Jonah' charm.");
			AddItems(pchar, "talisman2", 1);
			pchar.questTemp.IonaGathered = true;
			link.l1 = "Amazing! Thank you from the bottom of my heart.";
			link.l1.go = "GhostCapt_Prize3";
		break;

		case "GhostCapt_Prize3":
			dialog.text = "By the way, during our battle it seemed to me that you did not disclose your full potential as a captain. But I think it's because of inexperience. I can help you with that. Or would you rather learn only from your mistakes, huh?";
			link.l1 = "It would be stupid to refuse. Come on, tell me.";
			link.l1.go = "GhostCapt_Prize31";
			link.l2 = "No, thanks, I'd rather do it myself.";
			link.l2.go = "GhostCapt_noupgrade";
		break;
		
		case "GhostCapt_Prize31":
			WasteTime(1);
			dialog.text = "...Well, do you feel the changes already? I suppose so. And don't thank me, you really could impress me. And this... if you're on the west Main, find a White Boy there in the pearl fishing village-say hello...";
			link.l1 = "What can I say, they say hello to you from the late captain of the Flying Dutchman, Mr. Davy Jones?";
			link.l1.go = "GhostCapt_Prize5";
			pchar.GhostShipTuning = true;
		break;

		case "GhostCapt_noupgrade":
			dialog.text = "Look! You braved. I'm telling you, you're lucky, "+ GetSexPhrase("sucker","brat") +". I'm going to twist my tails to my gunners, another time I'll send one of them to the bottom!..Well, it's time for me. I've been staying with you too long. It's rare, you know, to talk to a living person like that..\n"+
				"And this... if you're on the west Main, find a White Boy there in the pearl fishing village-say hello...";
			link.l1 = "What should I say, they say hello to you from the late captain of the Flying Dutchman, Mr. Van der Decken?";
			link.l1.go = "GhostCapt_Prize5";
		break;

		case "GhostCapt_Prize5":
			dialog.text = "Hmm, really... Okay, I don't need anything... If it is destined to come true, then it will come true without greetings... Goodbye... Don't get caught by me anymore -I won't let you down another time...";
			link.l1 = "Glad to meet the legendary captain.";
			link.l1.go = "GhostCapt_PrizeExit";
		break;

		case "GhostCapt_PrizeExit":
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "GhostShipCapInCabinDied", 5.0);
			LAi_LockFightMode(pchar, false);
			DoQuestCheckDelay("OpenTheDoors", 5.0);
			InterfaceStates.Buttons.Save.enable = true;
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;

		case "GhostCapt_LastDialog":
			dialog.text = "Ah, " + GetSexPhrase("old acquaintance","old acquaintance") + "! But I was waiting for you - I knew that you would find the answer...";
			link.l1 = " I " + GetSexPhrase("I came","I came") + " to free you and your people from the curse. Your time is up - it's time to retire, thunderstorm of the seas and Captain of the ghost Davy Jones.";
			link.l1.go = "GhostCapt_LastDialog1";
		break;

		case "GhostCapt_LastDialog1":
			dialog.text = "I know, I know... Stubborn people like you always get their way. I used to be like that myself.. " +
				"Just don't expose yourself as a savior. I'm used to being, I even like it sometimes, and I'm not in a hurry to part with existence, even if it's ghostly. Therefore, don't think that I will give up so easily!";
			link.l1 = "I'm ready for this. And I really liked your boat.";
			link.l1.go = "GhostCapt_LastDialog2";
		break;

		case "GhostCapt_LastDialog2":
			dialog.text = "I believe this willingly. Only the right to be the captain of a ghost ship still needs to be earned. For now, I am its captain, and I will protect my ship as prescribed by the laws of the sea... Although... if I lose, I won't get upset...";
			link.l1 = "Get ready for the last fight, old killer! May the ocean rest your sinful soul...";
			link.l1.go = "GhostCapt_LastDialog3";
		break;

		case "GhostCapt_LastDialog3":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	}
}
