void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string attrLoc = Dialog.CurrentNode;

	if (findsubstr(attrLoc, "AndreAbelQuestSetNationLicence_", 0) != -1)
 	{
		i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		Dialog.CurrentNode = "Andre_Abel_In_Tavern_Quest_Complete_2";
 	}

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = RandPhraseSimple("Greetings, Captain...", "Glad to see you, Captain.");
			link.l1 = "Sorry, buddy, I've got my hands full. I can't pay attention to you.";
			link.l1.go = "exit";
			if(GetCompanionQuantity(PChar) != COMPANION_MAX)
			{
				link.l2 = "Hmm, I haven't seen you before. Do we know each other?";
				link.l2.go = "Andre_Abel_1";
			}
		break;

		case "Andre_Abel_1":
			dialog.text = "No, we don't know each other... My name is " + GetFullName(NPChar) + ". I'm captain of the ship '" + NPChar.ship.name + "'.";
			link.l1 = "And I am " + GetFullName(PChar) + ". Did you want something?";
			link.l1.go = "Andre_Abel_2";
		break;

		case "Andre_Abel_2":
			dialog.text = "Captain, can I count on your help? I really need an escort to Port-au-Prince.";
			link.l1 = "Is that all? And I was already thinking ...";
			link.l1.go = "Andre_Abel_3";
		break;

		case "Andre_Abel_3":
			dialog.text = "But I'm willing to pay no more than 3,000 piastres for the job, and I have to do it in five days.";
			link.l1 = "Hmm, what are such harsh conditions related to?";
			link.l1.go = "Andre_Abel_5";
			link.l2 = "No, I won't take it. You're limiting my time too much.";
			link.l2.go = "Andre_Abel_4";
		break;

		case "Andre_Abel_4":
			dialog.text = "Very sorry...";
			link.l1 = "Don't be offended...";
			link.l1.go = "exit";
			NPChar.LifeDay = 0;
			NextDiag.TempNode = "Andre_Abel_No_Quest";
		break;

		case "Andre_Abel_No_Quest":
			dialog.text = RandPhraseSimple("It's a pity that you don't have the opportunity to help me...", "Well, we'll have to wait for a patrol raid.");
			link.l1 = "Don't be offended...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_No_Quest";
		break;

		case "Andre_Abel_5":
			dialog.text = "The fact is that I spent a lot of time and money on repairing the ship. Now we have to save a lot and hurry up.";
			link.l1 = "Well, I agree. Is your ship ready to sail?";
			link.l1.go = "Andre_Abel_6";
			link.l2 = "I'll probably refuse... I had other plans, and your suggestion somehow doesn't inspire me to change them.";
			link.l2.go = "Andre_Abel_4";
		break;

		case "Andre_Abel_6":
			dialog.text = "Yes, the ship is completely ready. While you finish your business in the city, I'll be waiting for you here.";
			link.l1 = "Okay. See you soon...";
			link.l1.go = "exit";
			SetQuestHeader("Andre_Abel_Quest");
			AddQuestRecord("Andre_Abel_Quest", "1");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("xia", "as"));
			PChar.Quest.Andre_Abel_Quest_1Day_Left.over = "yes";
			PChar.QuestTemp.Andre_Abel_Quest_In_Progress = true;	// Флаг - квест начат
			SetFunctionTimerCondition("Andre_Abel_Quest_2Days_Left", 0, 0, 2, false);
			NextDiag.TempNode = "Andre_Abel_To_Sea_1";
		break;

		case "Andre_Abel_7":
			dialog.text = RandPhraseSimple("We were lucky with the wind, captain " + GetFullName(PChar) + ".", "Fort de France is a nice town, but during the time I was stuck in it, it managed to bore me to hell.");
			link.l1 = "Let's not waste time...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Andre_Abel_7";
		break;

		case "Andre_Abel_To_Sea_1":
			dialog.text = "Well, are we leaving already?";
			link.l1 = "Yes. Order them to weigh anchor.";
			link.l1.go = "Andre_Abel_To_Sea_2";
			link.l2 = "No, I still have some things to do.";
			link.l2.go = "Andre_Abel_To_Sea_1_1";
			NextDiag.TempNode = "Andre_Abel_To_Sea_1";
		break;

		case "Andre_Abel_To_Sea_1_1":
			dialog.text = "Can't we hurry up? As you remember, I am limited in time.";
			link.l1 = "I remember. We'll all make it...";
			link.l1.go = "exit";
			//	NextDiag.Tempnode = "Andre_Abel_To_Sea_1";
		break;

		case "Andre_Abel_To_Sea_2":
			dialog.text = "Well, that's great.";
			link.l1 = "I hope this flight won't cause us any trouble.";
			link.l1.go = "Andre_Abel_To_Sea_3";
			NextDiag.TempNode = "Andre_Abel_7";
		break;

		case "Andre_Abel_To_Sea_3":
			DialogExit();
			NextDiag.CurrentNode = "Andre_Abel_7";
			AddQuestRecord("Andre_Abel_Quest", "3");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "a"));
			PChar.Quest.Andre_Abel_Quest_2Days_Left.over = "yes";
			SetFunctionTimerCondition("Andre_Abel_Quest_5_Days_Is_Left", 0, 0, 5, false);
			SetFunctionNPCDeathCondition("Andre_Abel_Quest_Andre_Is_Dead", "Andre_Abel", false);
			SetFunctionLocationCondition("Andre_Abel_Quest_Battle_With_Pirates_Squadron", "Hispaniola2", false);
			SetFunctionExitFromLocationCondition("Andre_Abel_Quest_Delete_Andre_From_Tavern", PChar.location, false);
		break;

		case "Andre_Abel_15Days_Left_1": // Это на случай, если время закончиться тогда, когда Абель будет подходить к ГГ в порту Порт-о-Принса
			if(PChar.location == "FortFrance_Tavern")	// Из таверны можно было не выходить fix
			{
				dialog.text = PChar.Name + ", you let me down! I can't imagine what kind of business could make a free captain hang out in this damn Fort de France for half a month!";
				link.l1.go = "Andre_Abel_15Days_Left_In_FortFrance";
				break;
			}
			dialog.text = PChar.Name + ", you let me down! We didn't make it to Port-au-Prince in fifteen days!";
			link.l1 = "No offense, buddy, but I have more important things to do than escort an old galosha, and almost for free.";
			link.l1.go = "Andre_Abel_15Days_Left_2";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_SetImmortal(NPChar, true);
		break;

		case "Andre_Abel_15Days_Left_In_FortFrance":
			dialog.text = "The terms of the deal have been violated, so I'm breaking the contract!";
			link.l1 = "Well, it goes without saying...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "Andre_Abel_15Days_Left_2":
			dialog.text = "I think you understand that there is no question of any reward!";
			link.l1 = "What is there not to understand?";
			link.l1.go = "Andre_Abel_15Days_Left_3";
		break;

		case "Andre_Abel_15Days_Left_3":
			dialog.text = "I hope we don't meet again.";
			link.l1 = "How to know, how to know...";
			link.l1.go = "Andre_Abel_15Days_Left_4";
		break;

		case "Andre_Abel_15Days_Left_4":
			DialogExit();
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
//			LAi_ActorGoToLocatorFunc(NPChar, "reload", "reload6_back", "Andre_Abel_Quest_Delete_Andre", 15);
			LAi_ActorGoToLocator(NPChar, "reload", "reload6_back", "", 15);
		break;

		case "Andre_Abel_In_PortPax":
			dialog.text = "Thank you, Captain, you helped me out a lot. I'll pay for your services in silver bars, there's even more than three thousand here. Do you mind?";
			link.l1 = "No, of course... listen, why did you need an escort? After all, neither your ship nor the contents of the hold are of particular value.";
			link.l1.go = "Andre_Abel_In_PortPax_2";
			Group_DeleteGroup("Andre_Abel_Quest_Pirates_Ships"); // На всякий случай
			//AddMoneyToCharacter(PChar, 3000);
			TakeNItems(pchar, "jewelry17", 33);
			Log_Info("You got the silver bars");
			PlaySound("interface\important_item.wav");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_SetImmortal(NPChar, true);
			PChar.Quest.Andre_Abel_Quest_5_Days_Is_Left.over = "yes";
		break;

		case "Andre_Abel_In_PortPax_2":
			dialog.text = "Hmm, does the pirate attack near Hispaniola mean anything to you?";
			link.l1 = "That's it! And I had no idea to connect this attack with your presence in the squadron.";
			link.l1.go = "Andre_Abel_In_PortPax_3";
			link.l2 = "What did you do to annoy the pirates so much that they risk attacking your escort in line of sight of the fort?";
			link.l2.go = "Andre_Abel_In_PortPax_5";
		break;

		case "Andre_Abel_In_PortPax_3":
			dialog.text = "Yes, these events are directly related...";
			link.l1 = "Understood... Well, have a nice stay!";
			link.l1.go = "Andre_Abel_In_PortPax_4";
		break;

		case "Andre_Abel_In_PortPax_4":
			DialogExit();
			AddQuestRecord("Andre_Abel_Quest", "9");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader("Andre_Abel_Quest");
			pchar.questdata.FleitOrion = 1;
			DeleteAttribute(pchar, "QuestTemp.AndreAbelQuest");
			PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead.over = "yes";
			NPChar.LifeDay = 0;
			LAi_ActorGoToLocator(NPChar, "reload", "reload6_back", "", 15);
//			LAi_ActorGoToLocatorFunc(NPChar, "reload", "reload6_back", "Andre_Abel_Quest_Delete_Andre", 15);
		break;

		case "Andre_Abel_In_PortPax_5":
			dialog.text = "It's a pretty long story... I suggest we go to the tavern, and there, over a mug of rum, I'll tell you about it.";
			link.l1 = "Well, let's go...";
			link.l1.go = "Andre_Abel_In_PortPax_6";
		break;

        case "Andre_Abel_In_PortPax_6":
			DialogExit();
			LAi_ActorSetSitMode(NPChar);
			LAi_SetSitType(PChar);
			FreeSitLocator("PortPax_tavern", "sit_front2");
			FreeSitLocator("PortPax_tavern", "sit_base2");
			ChangeCharacterAddressGroup(NPChar, "PortPax_tavern", "sit", "sit_front2");
			DoFunctionReloadToLocation("PortPax_tavern", "sit", "sit_base2", "Andre_Abel_Quest_Dialog_In_PortPax_Tavern");
		break;

		case "Andre_Abel_In_Tavern_1":
			dialog.text = "In general, so... About four months ago, under not very favorable circumstances, I met with Jackman...";
			link.l1 = "Wait! Aren't you talking about that Jackman who runs the Bermudes pirates?";
			link.l1.go = "Andre_Abel_In_Tavern_2";
		break;

		case "Andre_Abel_In_Tavern_2":
			dialog.text = "It's about him... Well, Jackman, taking advantage of the situation, offered me his protection in exchange for 50 percent of all my profits. I refused. First of all, because it's a rip-off, and secondly, I didn't think Jackman was going to get me in trouble. But I was wrong...\n"
                          + "About a month later, near Guadeloupe, my galleon was attacked by two pirate-flagged schooners. I miraculously managed to leave, though, I had to drop part of the cargo to save the move. What saved me was that Fort Basse-Terre spotted us in time and opened fire...\n"
                          + "A few months later, I met a pirate squadron off the coast of Jamaica... If it wasn't for an English watchdog frigate patrolling the coastal waters, we wouldn't be here talking to you...\n"
                          + "About half a month later, I joined a small commercial caravan at Fort-de-France. There he unloaded his battered galleon and sold it in hopes of confusing Jackman's men... Then I bought and equipped the fluyt, took the freight to Port-au-Prince and waited for the companion. But the timing of the charter made me look for an escort...\n" 
						  "And then you know...";
			link.l1 = "Yeah, buddy, you're in trouble...";
			link.l1.go = "Andre_Abel_In_Tavern_3";
		break;

		case "Andre_Abel_In_Tavern_3":
			dialog.text = "I've thought many times whether it was worth agreeing to Jackman's terms back then. And you know what I'll tell you? I would already be ready to back down, but now what reason does he have to babysit someone whose business is collapsing to hell ..."
                          + "Hey, help me out, huh? Go to Bermudes to see Jackman.";
			link.l1 = "And what will I tell him?!";
			link.l1.go = "Andre_Abel_In_Tavern_4";
		break;

		case "Andre_Abel_In_Tavern_4":
			dialog.text = "Say: so, they say, and so, Andre Abel is very sorry that he did not accept your offer, he repents... Tell me that my business has practically collapsed and I am no longer interested in it..."
                          + "Go, huh? I'm not allowed to go there-it's certain death.";
			link.l1 = "Listen, Andre, do you even know what you're asking? And I'm not familiar with him at all, and I'm nothing to him at all.";
			link.l1.go = "Andre_Abel_In_Tavern_5";
			link.l2 = "Of course, you can try, but Bermudes is half a month away, and I had completely different plans...";
			link.l2.go = "Andre_Abel_In_Tavern_7";
		break;

		case "Andre_Abel_In_Tavern_5":
			dialog.text = "Oh, it's a pity... But you're probably right. No, that's not it... Goodbye.";
			link.l1 = "Jackman will leave you alone when he sees that you are broke... Don't despair like that.";
			link.l1.go = "Andre_Abel_In_Tavern_6";
		break;

		case "Andre_Abel_In_Tavern_6":
			DialogExit();
			NPChar.greeting = "pirat_common";
			NPChar.LifeDay = 0;
			NextDiag.CurrentNode = "Andre_Abel_In_PortPax_Tavern_No_Quest";
			CloseQuestHeader("Andre_Abel_Quest");
			pchar.questdata.FleitOrion = 1;
			DeleteAttribute(pchar, "QuestTemp.AndreAbelQuest");
			LAi_SetSitType(NPChar);
			LAi_SetPlayerType(PChar);
			DoFunctionReloadToLocation("PortPax_tavern", "tables", "stay3", "");
		break;

		case "Andre_Abel_In_PortPax_Tavern_No_Quest":
			dialog.text = LinkRandPhrase("I wish you could help me...", "What should I do now?", "My whole business has gone to waste...");
			link.l1 = "Andre, no offense, but you're demanding the impossible.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_In_PortPax_Tavern_No_Quest";
		break;

		case "Andre_Abel_In_Tavern_7":
			dialog.text = "Help me out, huh? In return, I will give you a bearer trading license. A very necessary thing, you know. And a collection of jewelry. Well, will you take it?";
			link.l1 = "Damn! Okay, I'll go to Jackman, maybe something will work out.";
			link.l1.go = "Andre_Abel_In_Tavern_8";
			link.l2 = "No, dealing with Jackman for such a dubious reward is not for me.";
			link.l2.go = "Andre_Abel_In_Tavern_5";
		break;

		case "Andre_Abel_In_Tavern_8":
			dialog.text = "That's great!.. I'll be waiting for you here at the tavern. Anyway, the sea is too dangerous for me right now.";
			link.l1 = "Wait... I'll try not to linger.";
			link.l1.go = "Andre_Abel_In_Tavern_9";
		break;

		case "Andre_Abel_In_Tavern_9":
			dialog.text = "You have no idea how grateful I am to you.";
			link.l1 = "Better pray for me. And you'll thank me when I come back with good luck.";
			link.l1.go = "Andre_Abel_In_Tavern_10";
		break;

		case "Andre_Abel_In_Tavern_10":
			ref rChar = CharacterFromID("Jackman");
			DialogExit();
			AddQuestRecord("Andre_Abel_Quest", "10");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("xia", "as"));
			NextDiag.CurrentNode = "Andre_Abel_In_Tavern_Continue_Quest";
			LAi_SetSitType(NPChar);
			LAi_SetPlayerType(PChar);
			QuestSetCurrentNode("Jackman", "Andre_Abel_Quest_Jackman_Dialog_1");
			DoFunctionReloadToLocation("PortPax_tavern", "tables", "stay3", "");
		break;

		case "Andre_Abel_In_Tavern_Continue_Quest":
			dialog.text = "Well, did you talk to Jackman? Did he agree?";
			if(!CheckAttribute(PChar, "QuestTemp.Andre_Abel_Quest_Complete"))
			{
				link.l1 = LinkRandPhrase("Not yet.", "Don't worry so much. Everything will work out for us...", "Andre, relax... relax, have fun, nothing depends on you right now anyway.");
				link.l1.go = "exit";
				NextDiag.TempNode = "Andre_Abel_In_Tavern_Continue_Quest";
			}
			else
			{
				link.l1 = "Yes, everything worked out. Jackman's not threatening you anymore.";
				link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_1";
			}
			break;

		case "Andre_Abel_In_Tavern_Quest_Complete_1":
			dialog.text = "Well, thank God! It's not for nothing that I hoped so much for you... Here's your jewelry collection, here you go... So, what kind of trading license do you need?";
			link.l1 = "I think I'll take the English one.";
			link.l1.go = "AndreAbelQuestSetNationLicence_0";
			link.l2 = "I would not refuse French.";
			link.l2.go = "AndreAbelQuestSetNationLicence_1";
			link.l3 = "I often visit Spanish settlements, so Spanish is the most necessary.";
			link.l3.go = "AndreAbelQuestSetNationLicence_2";
			link.l4 = "Dutch of course! You can enter almost any port with it.";
			link.l4.go = "AndreAbelQuestSetNationLicence_3";
			TakeNItems(pchar, "icollection", 1);
			Log_Info("You got the treasure");
			PlaySound("interface\important_item.wav");
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_2":
			dialog.text = "That's nice. I have only 20-day trade license of " + XI_ConvertString(Nations[sti(NPChar.LicenceNation)].Name + "Gen") + ". Don't forget to enter the port under a friendly flag... You know that very well.";
			link.l1 = "Of course I know! Thank you... listen, how did you get licenses from all countries?";
			link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_3";
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_3":
			dialog.text = "Hmm, why do you think Jackman was chasing me all over the Caribbean?"
                          + " Well, we're even now. Thank you and goodbye...";
			link.l1 = "Hmm, and have a nice stay...";
			link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_4";
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_4":
			DialogExit();
			NPChar.LifeDay = 0;
			GiveNationLicence(sti(NPChar.LicenceNation), 20);
			SetCharacterShipLocation(NPChar, "none");	// Уберём корабль из порта
			NextDiag.CurrentNode = "Andre_Abel_In_Tavern_Quest_Complete_5";
			AddQuestRecord("Andre_Abel_Quest", "23");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("Andre_Abel_Quest", "sNation", XI_ConvertString(Nations[sti(NPChar.LicenceNation)].Name + "Gen"));
			CloseQuestHeader("Andre_Abel_Quest");
			pchar.questdata.FleitOrion = 1;
			DeleteAttribute(pchar, "QuestTemp.AndreAbelQuest");
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_5":
			dialog.text = LinkRandPhrase("Thank you, "+ GetSexPhrase("buddy", "girlfriend") +", you helped me out a lot.", "I'm glad you could help me.", "Finally, you can safely do business.");
			link.l1 = "Good luck to you!.. Look, don't get caught anymore.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_In_Tavern_Quest_Complete_5";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
