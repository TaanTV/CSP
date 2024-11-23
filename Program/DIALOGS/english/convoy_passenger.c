//пассажир на доставку
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, arAll;
	string NPC_Meeting, sTemp, sTitle, sTavern;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("Oh, damn!! I know who you are! Only a complete idiot can come aboard as a passenger. Goodbye!", "Ah, I know who you are! I won't set foot on board you. Look for a fool...");
				link.l1 = RandPhraseSimple("Heh, what a timid...", "What a timid people went!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! I am "+ GetFullName(NPChar) + ". I heard that you are taking passengers on board?";
				link.l1 = "Maybe yes, it all depends on my benefit.";
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;

		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = "I need to be taken to the tavern " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Voc") +
                          ", in " + FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)) + ", and if successful I will pay " + FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)) + ". What do you think about it?";
			link.l1 = "I "+ GetSexPhrase("I agree","I agree") +".";
			link.l1.go = "convoy_agreeded";
			link.l2 = "I don't think I'm interested in this.";
			link.l2.go = "convoy_refused";
		break;

		case "convoy_refused":
			chrDisableReloadToLocation = false;
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			DeleteAttribute(npchar, "GenQuest.GetPassenger");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "convoy_agreeded":
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "1");
			sTemp = XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Voc") + ",";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("xia","as"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sDay", FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
            // по городу вернём его таверну
			sTavern = npchar.GenQuest.GetPassenger_Destination + "_tavern";
			sTemp = npchar.id + "_complited";
			pchar.quest.(sTemp).win_condition.l1 = "location";
			pchar.quest.(sTemp).win_condition.l1.location = sTavern;
			pchar.quest.(sTemp).win_condition = "AllPassangersComplited";
			pchar.quest.(sTemp).Idx	= npchar.index;
			if (rand(2) == 1) TraderHunterOnMap();
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "complete_convoy_quest":
			dialog.text = "Thank you. You have fulfilled your obligations. I'm here now. Here is your reward.";
			Link.l1 = "Thank you.";
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
			//слухи
		    chrDisableReloadToLocation = false; //#20180201-01
			AddSimpleRumour(LinkRandPhrase("A certain person by name " + GetFullName(npchar) + " says that you can trust the captain " + GetMainCharacterNameDat() + ", since without any problems captain delivered him up to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ".",
				"Passenger by name " + GetFullName(npchar) + " says that the captain " + GetMainCharacterNameDat() + " can be trusted. "+ GetSexPhrase("That delivered","That delivered") +"its up to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "safe and sound.",
				"I have heard, Captain, that you keep your word to the passengers. A certain dealer named " + GetFullName(npchar) + "speaks very well of you."), sti(npchar.nation), 40, 1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			AddMoneyToCharacter(pchar, makeint(npchar.GenQuest.GetPassenger_Money));
			ChangeCharacterReputation(pchar, 1);
			RemovePassenger(PChar, npchar);
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "4");
            CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);

			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "convoy_DeskTalk":
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear() + "Captain, time is up. When am I going to end up in " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?",
						  RandSwear() + "Captain, how long can you wander around who knows where?! When we get to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?" ,
						  RandSwear() + "Listen, Captain, I needed to get to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "and I want to get a clear and precise answer when that happens!"),
				RandPhraseSimple("Captain, this is the second time I have brought up the topic of fulfilling your obligations. When we get to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?", "Captain, for the second time I have to raise the issue of my delivery. When will we finally see the shores " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?"),
				RandPhraseSimple(RandSwear() + "Captain, the third time I ask you the same thing is when we arrive at " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", "Captain, we've lost God knows how much time! When you take me to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?"),
                "Listen, Captain, this is out of the question...", "block", 0, npchar, Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Excuse me, things are..."+ GetSexPhrase("wound up","wound up") +"... You will definitely be there in 7 days.", "Sorry " + GetAddress_FormToNPC(NPChar) + ", it was not possible at all to fulfill obligations towards you. But don't worry, we'll be there in a week."),
					RandPhraseSimple("I "+ GetSexPhrase("forced","forced") +" apologize for the second time... We will be there in a week.", "I apologize for the second time. We'll be there in a week."),
					RandPhraseSimple("And for the third time I "+ GetSexPhrase("forced","forced") +" to apologize to you... We will be there in a week.", "I apologize for the third time. We'll be there in a week, I promise..."),
					"I understand, " + GetAddress_FormToNPC(NPChar) + ", but please be patient a little longer... I will take you to your destination in seven days!", npchar, Dialog.CurrentNode);
    			link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Ah... passenger... me and "+ GetSexPhrase("forgot","forgot") +" about you. I think you'll feel safer in the hold, and you'll stop bothering me.", "Heh, well, wow! I have strangers on my ship!.. I suppose you need to get to know my hold."),
				"The second time? Well, wow... I think I'll send you down to the hold for a tour.",
				"The third time? How wrong that is, hehe... Tell you what, buddy, it's time for you to get in the hold, there's no need to walk around on my ship.",
				"The gate? Ah, I understand, this is the highest degree of irritation! Well, it's probably enough to play biryulki... Welcome to the hold, " + GetAddress_FormToNPC(NPChar) + ".", npchar, Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //дверцы откроем
		break;

		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase("Okay, but I'll cut the payment for such a delay.", "Well, I'll believe it... But keep in mind that I will reduce the amount of payment to you!", "Hmm, I have nowhere to go from the ship, but keep in mind that the amount of your fee will be reduced ...");
			Link.l1 = LinkRandPhrase("Agreed.", "Well, okay...", "Okay, so be it.");
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple("I want to believe that the contract will be fulfilled this time.", "I hope this is our last conversation on such an unpleasant topic...");
			Link.l1 = "Of course.";
			link.l1.go = "convoy_DeskTalk_exit";
		break;

		case "convoy_DeskTalk_exit":
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_TimeOver";
			SetTimerCondition(sTemp, 0, 0, 7, false);
			pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
			pchar.quest.(sTemp).Idx						   = npchar.index;
			npchar.GenQuest.GetPassenger_Money = makeint(sti(npchar.GenQuest.GetPassenger_Money) / 1.5);
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "5");
			AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "convoy_Prison_1":
			dialog.text = RandSwear() + "What other hold? I don't understand you!";
			if (GetPrisonerQty() < PRISONER_MAX)
			{
    			Link.l1 = "What's unclear here? You're my prisoner now! Go to the hold!";
    			link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = "I'm kidding... We'll be in exactly the right city in seven days.";
			link.l2.go = "convoy_DeskTalk_1";
		break;

		case "convoy_Prison_2":
			dialog.text = RandSwear() + "You're going to pay for this, "+ GetSexPhrase("scoundrel","scoundrel") +"!";
			Link.l1 = "Everyone says that, but it turns out just the opposite - they pay me!";
			link.l1.go = "convoy_Prison_3";
		break;

		case "convoy_Prison_3":
			AddSimpleRumour(LinkRandPhrase("It became known that a certain captain " + GetFullName(pchar) + " undertook to deliver a passenger named " + GetFullName(npchar) + ", but not his words "+ GetSexPhrase("kept","kept") +". In addition, "+ GetSexPhrase("captured","captured") +"poor guy. That's how to trust unfamiliar people...",
				"Eh, where is the world going?! Captain " + GetFullName(pchar) + " "+ GetSexPhrase("captured","captured") +"a poor guy named " + GetFullName(npchar) + ", although he was a passenger on his ship...",
				"There are rumors, Captain, that you are "+ GetSexPhrase("decent bastard","decent bastard") +". They say that the poor guy " + GetFullName(npchar) + " was captured on your ship. And you promised to deliver it to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ". Yes, it's ugly..."), sti(npchar.nation), 40, 1);
            RemovePassenger(PChar, NPChar);
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
        	ChangeCharacterReputation(pchar, -5);
            OfficersReaction("bad");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 10+rand(10));// награда
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "6");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","a"));
            CloseQuestHeader(sTitle);
			AddCharacterExpToSkill(pchar, "COMMERCE", 25);
            SetCharToPrisoner(NPChar);
        	DialogExit();
		break;
	}
}

void GenerateConvoyPassengerQuest(ref npchar)
{
	int iTradeMoney, iNation, irank;
	string sTemp, sR;

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	npchar.GenQuest.GetPassenger_Destination = sGlobalTemp;
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.GetPassenger_City), GetArealByCityName(sGlobalTemp));
	if (sti(daysQty) > 14) daysQty = 14;
	npchar.GenQuest.GetPassenger_Time  = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*500*sti(pchar.GenQuest.GetPassenger.Shipmod)+rand(100))*sti(daysQty)/sti(npchar.GenQuest.GetPassenger_Time);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.3); //то размер награды увеличивается
	npchar.GenQuest.GetPassenger_Money = iTradeMoney;

	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(npchar.GenQuest.GetPassenger_Destination);
	//Log_Info(pchar.GenQuest.GetPassenger_City);


	sTemp = npchar.id + "_TimeOver";
	SetTimerCondition(sTemp, 0, 0, sti(npchar.GenQuest.GetPassenger_Time), false);
	pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
	pchar.quest.(sTemp).Idx						   = npchar.index;

	sTemp = npchar.id + "_dead";
	pchar.quest.(sTemp).win_condition.l1           = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).win_condition              = "AllPassangersDead";
	pchar.quest.(sTemp).Idx						   = npchar.index;
}

void LookShipPassenger()
{
	switch(makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.GetPassenger.Shipmod = 0.8;
		break;
		case 1:
			pchar.GenQuest.GetPassenger.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.GetPassenger.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.GetPassenger.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.GetPassenger.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
		case 6:
			pchar.GenQuest.GetPassenger.Shipmod = 4.5;
		break;
	}
}
