// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "First time":
			dialog.text = "Talk to our captain. I have nothing to tell you.";
			Link.l1 = "Good.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Talk to our captain. I have nothing to tell you.";
			Link.l1 = "Good.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Gospo"+ GetSexPhrase("din", "zha") +"Are you looking for someone?";
					Link.l1 = "Yeah, man. May I see captain of this vessel?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "If you have any questions, please contact captain. He recently went ashore.";
					Link.l1 = "Good, good";
					Link.l1.go = "exit";
				}
				break;
			}
*/
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даём нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("Wow, you've come yourself... Well, once you have then go to the cap. Talk about your sorrowful affairs...",
	                                           "Heh, well, you give it, "+ GetSexPhrase("buddy", "girlfriend") +"! I've never seen anything like it... Come to captain, he will talk to you.");
				Link.l1 = "It's a pity...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*
		case "ChurchQuest1_Node1":
			dialog.text = "You'd better look for it in the port.";
			Link.l1 = "Thank you, my dear.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/
        //  на палубе <--

		// ugeen --> разговор с боцманом по генератору "A reason to hurry"
		case "On_MyShip_Deck":
			dialog.text = "Well, you made a noise, Captain! The guys and I had just ordered another drink when we heard screams on the street. After rushing out of the tavern and learning that they were trying to arrest you, we decided to cut loose and leave this inhospitable harbor.";
			link.l1 = "Yes, some people have a strange understanding of justice.";
			link.l1.go = "On_MyShip_Deck_1";
		break;

		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A")
			{
				// карты не было
				dialog.text = "Captain! Stop being sad! Since it was impossible to leave in peace anyway, in the confusion we decided to drop by a local usurer and slightly lightened his chests. Here is your share - " + sti(pchar.questTemp.ReasonToFast.p9) + " piastres...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Captain! Stop being sad! Since it was impossible to leave in peace anyway, in the confusion we decided to drop by a local usurer and slightly lightened his chests. And they also took a decent blade from a pawnshop cupboard. Here is your share - " + sti(pchar.questTemp.ReasonToFast.p9) + " piastres and the blade...";
			}
			link.l1 = "Very handy. Well done!";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("xia", "as"));
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;

		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;

		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "Captain, your buddy has escaped.";
			link.l1 = "Which buddy?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;

		case "CapComission_OnShipDeck1":
			dialog.text = "Well, this one you got out of prison.";
			link.l1 = "How could you have buried him?!!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;

		case "CapComission_OnShipDeck2":
			dialog.text = "What are we doing? He climbed over the latrine bars at night, ostensibly out of need, and himself went down the anchor rope and swam... We were shooting, but it was dark...";
			link.l1 = "Damn!!! They've completely dissolved! I'll take everyone ashore, you'll be hoeing reeds on plantations! Such a valuable bird was missed!..";
			link.l1.go = "CapComission_OnShipDeck3";
		break;

		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputationToNeutral(pchar, -4);//отдалить от нейтральной на 4 единицы
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen

		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "Captain, I'm sorry, we didn't catch up - the prisoner escaped.";
			link.l1 = "What kind of prisoner? Who escaped?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;

		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Yes, this one, what's his name, " + pchar.GenQuest.Hold_GenQuest.CapName + "or something.";
			link.l1 = "Damn it! Where were you looking?!";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;

		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "Yes, he got out of the hold, jumped over the bulwark and was gone. We did not shoot, so as not to make a noise, but by the time the boat was lowered, the fishermen had already picked him up.";
			link.l1 = "What am I only paying you a salary for! The senior watch should be flogged and deprived of a week's ration of rum. Everyone to your places! We're taking off the anchor...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;

		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;

		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "Greetings, Captain. There have been no incidents during your absence on board...";
			link.l1 = "Okay, okay, I see... We have a prisoner in the hold, " + pchar.GenQuest.Hold_GenQuest.CapName + " name. Send a team to bring him to the port. He's free.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;

		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "How, should I let go completely? Should I send it by boat?";
			link.l1 = "On the turtle... I think I've made myself very clear. And let them move! We need to get off the anchors by the beginning of low tide.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;

		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
Dialog.text = "Captain, there is not a single person on the ship! There's something fishy here... Tommy says he saw a cat in the forecastle, but not a single living soul...";
			Link.l1 = "Dummy, the cat has no soul. I haven't been to church for a long time... If ever there was one... Have you looked in captain's cabin? I need a logbook.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;

		case "On_MaryCeleste_Deck_1":
Dialog.text = "We have examined everything, there is no log or navigation devices. There is also no stern boat...";
			Link.l1 = "The boat was torn off by the storm?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;

		case "On_MaryCeleste_Deck_2":
Dialog.text = "No, Captain, the boat was removed by a hoist... And this... we found a dusak on the floor in the forecastle. Either bloody or rusty. Take a look...";
			Link.l1 = "Why are you giving me all kinds of stuff?! Inspect the hold and let's go... Oh, I don't like all this...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;

		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил

			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернём маневренность, для интерфейса

			chrDisableReloadToLocation = false; // Откроем выход

			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;

		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
Dialog.text = "Captain, it's kind of creepy here... Maybe it's time to leave already?";
					Link.l1 = "yeah... Get in the boat.";
					Link.l1.go = "exit";
				break;

				case 1:
Dialog.text = "Captain, if you plan to take this strange ship to port, then I will not stay on it. It's better to go overboard.";
					Link.l1 = "I'm not planning anything... It's creepy.";
					Link.l1.go = "exit";
				break;

				case 2:
Dialog.text = "Can we flood it, and captain?";
					Link.l1 = "So that the souls of the missing sailors living here can appear to us in our nightmares?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}

			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;

		case "On_MaryCeleste_Deck_SailorLast_1":
Dialog.text = "God forbid, Captain... What are you saying!..";
			Link.l1 = "Don't look so pale, I'm joking... Get in the boat.";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест

        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Talk to the boss. I have nothing to tell you.", "I'm on duty. With all questions, go to the commandant of the fort.");
			Link.l1 = "Good.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;

		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("I'm terribly busy right now. Leave me alone.",
                                           "Don't stop me from working. We have nothing to talk about.");
			Link.l1 = "It's a pity...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;

		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("Morgan wanted to say 'a couple of affectionate words' to you... He's here on deck somewhere.",
                                           "Heh, find Morgan. Unpleasant news awaits you...");
			Link.l1 = "Good.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
