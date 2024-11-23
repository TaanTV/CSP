void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;
	string cnd;
	DeleteAttribute(&Dialog,"Links");
	int i;

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Quest_Whisper_1":
			dialog.text = "So, the job is not easy, but the jackpot that we can grab is worth the risk.";
			link.l1 = "I've already figured that out. I want to know the details.";
			link.l1.go = "Quest_Whisper_2";
		break;

		case "Quest_Whisper_2":
			dialog.text = "Wait, it seems that someone is coming here. I'll lock the door.";
			link.l1 = "...";
			link.l1.go = "Quest_Whisper_2_exit";
			pchar.WhisperPGG = npchar.id;
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);

			for (i = 1; i < 4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PGG_Whisper_Incquisitor"+i, "PGG_Vincento_"+(2+i), "man", "man", sti(pchar.rank) + MOD_SKILL_ENEMY_RATE*3, PIRATE, 0, true));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
				cnd = "l"+i;
				pchar.quest.QuestWhisper_RoomFight.win_condition.(cnd) = "NPC_Death";
				pchar.quest.QuestWhisper_RoomFight.win_condition.(cnd).character = sld.id;
				LAi_group_MoveCharacter(sld, "Quest_Whisper_Enemy");
			}
			pchar.quest.QuestWhisper_RoomFight.function = "QuestWhisper_RoomFight";
		break;

		case "Quest_Whisper_2_exit":
			DialogExit();
			sld = CharacterFromId("PGG_Whisper_Incquisitor3");
			sld.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
			sld.dialog.currentnode   = "Quest_Whisper_3";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "Quest_Whisper_3":
			dialog.text = "Here you are, Whisper!";
			link.l1 = "...";
			link.l1.go = "Quest_Whisper_3_exit";
		break;

		case "Quest_Whisper_3_exit":
			DialogExit();
			sld = CharacterFromId(pchar.WhisperPGG);
			sld.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
			sld.dialog.currentnode   = "Quest_Whisper_4";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "Quest_Whisper_4":
			dialog.text = "Damn it! You brought them here for my soul?";
			link.l1 = "This is the first time I've seen these guys!";
			link.l1.go = "Quest_Whisper_4_exit";
		break;

		case "Quest_Whisper_4_exit":
			StartInstantDialog("PGG_Whisper_Incquisitor3", "Quest_Whisper_5", "Quest\WhisperLine\Whisper_PGG.c");
		break;

		case "Quest_Whisper_5":
			dialog.text = "We've finally tracked you down, witch! Now you will pay for your misdeeds!";
			link.l1.go = "Quest_Whisper_5_exit";
		break;

		case "Quest_Whisper_5_exit":
			StartInstantDialog(pchar.WhisperPGG, "Quest_Whisper_6", "Quest\WhisperLine\Whisper_PGG.c");
		break;

		case "Quest_Whisper_6":
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetImmortal(npchar, true);
			dialog.text = "I'm so tired of you already!";
			link.l1.go = "Quest_Whisper_6_exit";
			pchar.WhisperId = npchar.id;
		break;

		case "Quest_Whisper_6_exit":
			npchar.dialog.CurrentNode = "Quest_Whisper_8";
			StartInstantDialog("PGG_Whisper_Incquisitor3", "Quest_Whisper_7", "Quest\WhisperLine\Whisper_PGG.c");
		break;

		case "Quest_Whisper_7":
			dialog.text = "Get ready to go to hell with your servant!";
			link.l1 = "I didn't want to interfere in your business with her, but the word 'servant' sounded pretty insulting.";
			link.l1.go = "Quest_Whisper_7_fight";
			link.l2 = "Fuck it, I'm out of here!";
			link.l2.go = "Quest_Whisper_7_flee";
		break;
		case "Quest_Whisper_7_fight":
			sld = CharacterFromId(pchar.WhisperId);
			LAi_SetWarriorTypeNoGroup(sld);
			for (i = 1; i < 4; i++)
			{
				sld = CharacterFromId("PGG_Whisper_Incquisitor"+i);
				LAi_SetWarriorTypeNoGroup(sld);
			}

			DialogExit();
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "Quest_Whisper_7_flee":
			DialogExit();
			sld = CharacterFromId(pchar.WhisperId);
			DoReloadCharacterToLocation(sld.PGGAi.location.town + "_tavern","goto","goto1");
			chrDisableReloadToLocation = false;
		break;

		case "Quest_Whisper_8":
			if (HasSubStr(pchar.location,"upstairs"))
			{
				dialog.text = "Are you alive?";
				link.l1 = "I'm fine. Better tell me, what the hell is going on here?!";
				link.l1.go = "Quest_Whisper_9";
			}
			else
			{
				dialog.text = "You have the audacity to come to me after you quit?! I don't want to do business with you anymore.";
				link.l1 = "Well, you don't need to!";
				link.l1.go = "Quest_Whisper_end";
			}
		break;

		case "Quest_Whisper_9":
			dialog.text = "As you can see, I have enough enemies in this archipelago. You have them too, don't you?";
			link.l1 = "Yes, but not like that! How did you manage to anger the Inquisition?";
			link.l1.go = "Quest_Whisper_10";
		break;

		case "Quest_Whisper_10":
			dialog.text = "It's a long story. But I can tell you that the Inquisition is not just an order that fights heretics. In fact, they do not shy away from participating in politics, and in general they have long been mired in corruption and lies. They have the power to accuse any person of heresy, burn, and take away property in favor of their own treasury, and they do not neglect to use it. They did something similar to me once, but I managed to escape at the last moment. Since then, the Inquisition has been hunting me.";
			link.l1 = "It seems to me that you are not telling me a lot... Not that I'm defending the Inquisition, but you do look like a witch. Can you tell me how it happened?";
			link.l1.go = "Quest_Whisper_11";
		break;

		case "Quest_Whisper_11":
			dialog.text = "Maybe I'll tell you another time when I get to know you better. In the meantime, let's talk about the case. You want to earn money, don't you?";
			link.l1 = "Okay, tell me.";
			link.l1.go = "Quest_Whisper_12";
		break;

		case "Quest_Whisper_12":
			dialog.text = "Long story short, I suggest that we plunder a Spanish city together.";
			link.l1 = "Does this have anything to do with our recent 'guests'?";
			link.l1.go = "Quest_Whisper_13";
		break;

		case "Quest_Whisper_13":
			dialog.text = "This is not the first time, and far from the last time, when they come for me. We need to put an end to this, I'm going to hit the most painful thing for the Inquisition - money. And they have a lot of money. Mountains of gold that they confiscated from sentenced Spanish citizens for many years. A month ago, I met a squadron of hunters, just equipped at the expense of this treasury, which consisted of only battleships. I managed to fight back, but my trusty corvette leaked and had to be abandoned. The vessel that I got after is not at all suitable for the plan I have in mind, so I will need the help of someone like you.";
			link.l1 = "So you want to take revenge on them... And where is their treasury? In Santiago?";
			link.l1.go = "Quest_Whisper_14";
		break;


		case "Quest_Whisper_14":
			dialog.text = "Yes. There, under the church, is their main residence in the Caribbean. Sneaking in and robbing them will not work - there are more than one chest of valuables there. For the same reason, we can't raid the city from land-we just don't have enough time to take everything out before the soldiers from the fort miss it. No, we will have to take the city from the sea, first destroying the fort.";
			link.l1 = "Isn't this a suicidal plan? There are probably thousands of soldiers in the garrison of the fort, and besides, the city is guarded by a squadron of warships. Whatever the treasury is, it's hardly worth it.";
			link.l1.go = "Quest_Whisper_15";
		break;

		case "Quest_Whisper_15":
			dialog.text = "Don't forget, we will receive not only the treasury of the Inquisition, but also the loot for looting the city. And I can help with security.";
			link.l1 = "How can you help?";
			link.l1.go = "Quest_Whisper_16";
		break;

		case "Quest_Whisper_16":
			dialog.text = "I know how to get the governor to take the squadron and some of the soldiers out of the fort. If you whisper to him that I was seen in Puerto Principe, I have no doubt he will send all his forces to catch me. I've been wanted on this island for a long time.";
			link.l1 = "Do you think he'll just believe me like that?";
			link.l1.go = "Quest_Whisper_18";
		break;

		case "Quest_Whisper_18":
			dialog.text = "Unlikely. I'm afraid you'll have to run a few errands for him first to ingratiate yourself, and only then tell this story.";
			link.l1 = "Several?";
			link.l1.go = "Quest_Whisper_19";
		break;

		case "Quest_Whisper_19":
			dialog.text = "I think three is enough to dispel any doubts about your sincerity and friendliness. As soon as you do this, be ready to go to sea and immediately storm the fort on your own, because my ship will distract the guard squadron.";
			link.l1 = "Okay, I'll take it. Where can I find you when I'm done seducing the governor?";
			link.l1.go = "Quest_Whisper_20";
			link.l2 = "You know, I don't want to get involved in this. I have no doubt that Spain will put a bounty on my head after this.";
			link.l2.go = "Quest_Whisper_19_1";
		break;

		case "Quest_Whisper_19_1":
			dialog.text = "Sure? I won't offer you this case anymore. But if you agree, then I'm not in a hurry to do it, because I understand that you will need to thoroughly prepare for the assault.";
			link.l1 = "Sure.";
			link.l1.go = "Quest_Whisper_end";
			link.l2 = "Okay, I'll take it. Where can I find you when I'm done seducing the governor?";
			link.l2.go = "Quest_Whisper_20";
		break;

		case "Quest_Whisper_20":
			dialog.text = "Don't worry about me, I'll be near Cuba. As soon as you do your part of the plan, I'll find you myself.";
			pchar.PGGWhisperLetter = true;
			link.l1 = "Well, then let's get to it.";
			link.l1.go = "Quest_Whisper_accept";
		break;

		case "Quest_Whisper_end":
			LocatorReloadEnterDisable("Santiago_Town", "basement1", false);
			npchar.dialog.filename = "PGG_dialog.c";
			npchar.dialog.currentnode = "First time";
			npchar.PGGWhisperQuestEnd = true;
			DialogExit();
			CloseQuestHeader("PGGWhisper");
			DeleteAttribute(npchar, "PGGAi.DontUpdate");
			DeleteAttribute(pchar, "PGGWhisperQuest");
			DeleteAttribute(pchar, "PGGWhisperLetter");
			DeleteAttribute(pchar, "PGGWhisperLetterSent");
			DeleteAttribute(pchar, "PGGWhisperLetterSentFail");
			DeleteAttribute( Colonies[FindColony("Santiago")], "DontSetShipInPort");
		break;

		case "Quest_Whisper_accept":
			npchar.PGGAi.DontUpdate = true;
			if (!CheckAttribute(pchar, "PGGWhisperQuest"))
			{
				SetQuestHeader("PGGWhisper");
				AddQuestRecord("PGGWhisper", "1");
				pchar.PGGWhisperQuest = true;
			}
			npchar.dialog.currentnode = "Quest_Whisper_report";
			if (CheckAttribute(NPChar, "payment") && npchar.payment == true)
			{
				CheckForReleaseOfficer(sti(npchar.index));
				RemovePassenger(pchar, npchar);
				RemoveCharacterCompanion(pchar, npchar);
				LAi_SetWarriorType(npchar);
				npchar.location = "none";
				npchar.PGGAi.location.town = GetCurrentTown();
				npchar.PGGAi.IsPGG = true;
				int n = 0;
				int aShips[SHIP_OCEAN];
				for (i = 0; i <= SHIP_OCEAN; i++)
				{
					if (CheckAttribute(&ShipsTypes[i], "Class") && sti(ShipsTypes[i].Class) == GetCharacterShipClass(PChar))
					{
						aShips[n] = i;
						n++;
					}
				}
				i = rand(n-1);
				int iType = aShips[i];
				PGG_DebugLog(npchar.id + " Changed ship");
				npchar.Ship.Type = GenerateShipExt(iType, rand(1), npchar);
				SetBaseShipData(npchar);
				if (!CheckAttribute(npchar, "Ship.Name")) SetRandomNameToShip(npchar);
				PGG_UpdateShipEquip(npchar);
				npchar.PGGAi.OwnShip = true;	
			}
			DialogExit();
		break;

		case "Quest_Whisper_report":
			dialog.text = "You're here again! Are there any other questions?";

			if (CheckAttribute(pchar, "PGGWhisperLetterSentFail"))
			{
				DeleteAttribute(pchar, "PGGWhisperLetterSentFail");
				link.l1 = link.l1 + " But he didn't believe me. Sorry, it didn't work out.";
				link.l1.go = "Quest_Whisper_report_fail";
				break;
			}

			link.l1 = "No, I'm just passing by.";
			link.l1.go = "Quest_Whisper_accept";
			link.l2 = "Yes. It slipped my mind. Remind me, what's the deal with you and me?";
			link.l2.go = "Quest_Whisper_report_1";
			link.l3 = "I've been thinking... I don't like your case. I'm sorry, but I'll pass.";
			link.l3.go = "Quest_Whisper_report_fail";
		break;

		case "Quest_Whisper_report_1":
			dialog.text = "What?! Are you kidding me? If you have a head on your shoulders, then you write such things down in your journal. I'll pretend I didn't hear your question.";
			link.l1 = "I'm kidding.";
			link.l1.go = "Quest_Whisper_accept";
		break;

		case "Quest_Whisper_report_fail":
			dialog.text = "Clear. It looks like I'll have to find another way. Thanks for saying. Bye.";
			link.l1 = "Bye.";
			link.l1.go = "Quest_Whisper_end";
			//не забыть закрытие квеста
		break;
		case "Quest_Whisper_ToSiege":
			chrDisableReloadToLocation = false;
			dialog.text = "Ships in the harbor are being anchored, it looks like our plan is working.";
			link.l1 = "What are you doing here? Shouldn't your ship be distracting the squadron right now?";
			link.l1.go = "Quest_Whisper_ToSiege_1";
		break;
		case "Quest_Whisper_ToSiege_1":
			dialog.text = "My navigator will handle this himself. You didn't think that I'll leave you all the fun?";
			link.l1 = "What kind of equipment do you have? I've never seen this.";
			link.l1.go = "Quest_Whisper_ToSiege_2";
		break;
		case "Quest_Whisper_ToSiege_2":
			dialog.text = "And you probably won't see it anywhere else. Okay, stop talking. Let's go to the boat before the guards recognize me. I hope your ship is enough to take this city.";
			link.l1 = "Let's go check it out.";
			link.l1.go = "exit";
			LAi_LoginInCaptureTown(npchar, true);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("PGGWhisper", "4");
		break;
		case "Quest_Whisper_AfterSiege":
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Santiago_Town", "basement1", false);
			dialog.text = "We did it! The last breakthrough remains - the residence of the Inquisition. The entrance is under the stairs to the church. Come in as soon as you're ready. If you want, you can visit the governor right away, I'll wait.";
			link.l1 = "Okay.";
			link.l1.go = "exit";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollow(npchar, PChar, "", -1);

			PChar.quest.QuestWhisper_Incq.win_condition.l1 = "location";
			PChar.quest.QuestWhisper_Incq.win_condition.l1.location = "Santiago_Incquisitio";
			PChar.quest.QuestWhisper_Incq.function = "QuestWhisper_Incq";
		break;

		case "Quest_Whisper_Incq_fall":
			dialog.text = "Oh, my head is splitting, I see, did we win after all?";
			link.l1 = "Did you survive? When I saw you fall, I feared the worst.";
			link.l1.go = "Quest_Whisper_Incq";
		break;

		case "Quest_Whisper_Incq":
			//chrDisableReloadToLocation = false;

			dialog.text = "Come on, their treasures must be somewhere nearby.";
			if (!CheckAttribute(npchar, "FailedRecruitment"))	dialog.text = "It turned out to be much easier than I thought. " + dialog.text;
			link.l1 = "Okay, but let's take a little breath.";
			link.l1.go = "exit";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollow(npchar, PChar, "", -1);

			PChar.quest.QuestWhisper_Incq_4.win_condition.l1 = "locator";
			PChar.quest.QuestWhisper_Incq_4.win_condition.l1.location = "Santiago_Incquisitio";
			PChar.quest.QuestWhisper_Incq_4.win_condition.l1.locator_group = "box";
			PChar.quest.QuestWhisper_Incq_4.win_condition.l1.locator = "box2";
			PChar.quest.QuestWhisper_Incq_4.function = "QuestWhisper_Incq_4";

			ref _location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box2.money = 50000;
			_location.box2.items.icollection = 1;
			_location.box2.items.chest = 3;
			_location.box2.items.jewelry1 = 20+rand(5);
			_location.box2.items.jewelry2 = 20+rand(5);
			_location.box2.items.jewelry3 = 20+rand(5);
			_location.box2.items.jewelry4 = 11+rand(5);
			_location.box2.items.BackPack3 = 1;
			ChangeItemName("DeSouzaCross", "itmname_DeSouzaCross_DH");
		break;

		case "Quest_Whisper_Incq_1":
			dialog.text = "Damn!! Where's my shotgun?! He was supposed to be here!";
			link.l1 = "Shotgun? I don't know, I didn't come across anything like that. But look at the pile of valuables!";
			link.l1.go = "Quest_Whisper_Incq_2";
		break;

		case "Quest_Whisper_Incq_2":
			dialog.text = "I don't care about them, I'm interested in the weapons that were taken away from me here during my previous 'visit'. Besides, there should be much more values. There weren't enough Inquisitors here either. And of those that were - none of the influential ones, damn it, I missed something! The Inquisition must have another residence that I haven't heard of.";
			link.l1 = "Maybe so, but loot suits me. How are we going to divide it?";
			link.l1.go = "Quest_Whisper_Incq_3";
		break;

		case "Quest_Whisper_Incq_3":
			dialog.text = "You can keep everything for yourself, after all, you've done. And the loot for looting the city, too. I came here to get rid of an old annoying enemy and get my shotgun, not for this handful of blood coins.";
			link.l1 = "Are you serious about this? The handful is pretty big, you know.";
			link.l1.go = "Quest_Whisper_Incq_4";
		break;

		case "Quest_Whisper_Incq_4":
			dialog.text = "Let's not linger. The remaining Spanish forces may return to the city at any moment.";
			link.l1 = "Whatever you say.";
			link.l1.go = "Quest_Whisper_Incq_5";
		break;

		case "Quest_Whisper_Incq_5":
			AddQuestRecord("PGGWhisper", "5");
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;

			PChar.quest.QuestWhisper_Incq_5.win_condition.l1 = "location";
			PChar.quest.QuestWhisper_Incq_5.win_condition.l1.location = "Santiago_Town";
			PChar.quest.QuestWhisper_Incq_5.function = "QuestWhisper_Incq_5";
		break;

		case "Quest_Whisper_Finish":
			pchar.PGGWhisperComplete = true;
			DeleteAttribute(npchar, "PGGAi.DontUpdate");
			CloseQuestHeader("PGGWhisper");
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "LockMapReload");
			DeleteAttribute(pchar, "PGGWhisperLetter");
			DeleteAttribute(pchar, "PGGWhisperLetterSent");
			DeleteAttribute( Colonies[FindColony("Santiago")], "DontSetShipInPort");

			dialog.text = "My ship is already in the harbor. I don't know how soon the Spaniards will follow him, but I won't check. I don't advise you to stay here either.";
			link.l1 = "Well, goodbye.";
			link.l1.go = "Quest_Whisper_Finish_NoHire";
			link.l2 = "The Spaniards, the Inquisition... Now your enemies are my enemies. Maybe we can unite and continue to fight against them together? Who knows, maybe we'll get the Inquisition...";
			link.l2.go = "Quest_Whisper_Finish_Hire";
		break;

		case "Quest_Whisper_Finish_NoHire":
			npchar.dialog.filename = "PGG_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
		break;

		case "Quest_Whisper_Finish_Hire_1":
			npchar.dialog.filename = "Enc_Officer_dialog.c";
			npchar.dialog.currentnode = "hired";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
		break;

		case "Quest_Whisper_Finish_Hire":
			if (CheckAttribute(npchar, "FailedRecruitment"))
			{
				dialog.text = "I'm sorry, but I think I'll be safer alone.";
				link.l1 = "As you know.";
				link.l1.go = "Quest_Whisper_Finish_NoHire";
			}
			else
			{
				if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
				{
					Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
							RandPhraseSimple("A tempting offer! Good! I'll keep you company!", "And you're not a blunder, Captain... I think we'll work together!"),
							LinkRandPhrase("I like your offer. I agree.",
							"Well... I also think that together we can do more!", "Perhaps it will be fun. Agreed."));
					link.l1 = RandPhraseSimple("Great, I'm waiting for you at sea!", "That's right! We're going to be a great team.");
					link.l1.go = "Quest_Whisper_Finish_Hire_1";

					if (CheckAttribute(NPChar, "PGGAi.Task.SetSail"))
					{
						PGG_Disband_Fleet(npchar);
					}

					NPChar.PGGAi.IsPGG = false;
					NPChar.PGGAi.location.town = "none";
					if (NPChar.model.animation == "man" || NPChar.model.animation == "YokoDias" || NPChar.model.animation == "Milenace") Npchar.CanTakeMushket = true;
					if(npchar.model == "PGG_Whisper_6") EquipCharacterByItem(NPChar, "suit_1");
					NPChar.Payment = true;
					NPChar.Money   = 0;
					SetBaseShipData(NPChar);

					DeleteAttribute(NPChar,"ship.sails");
					RepairMasts(NPChar);
					DeleteAttribute(NPChar,"ship.blots");

					Fantom_SetCannons(NPChar, "pirate");
					Fantom_SetBalls(NPChar, "pirate");

					DeleteAttribute(NPChar, "PGGAi.Task");
					DeleteAttribute(NPChar, "PGGAi.LockService");
					SetCharacterRemovable(NPChar, true);
					SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");

					NPChar.HalfImmortal = true;  // Контузия
					NPChar.OfficerWantToGo.DontGo = true; //не пытаться уйти
					NPChar.loyality = MAX_LOYALITY;

					LAi_SetActorTypeNoGroup(npchar);
					LAi_ActorFollow(npchar, PChar, "", -1);
				}
				else
				{
					Dialog.Text = RandPhraseSimple("It looks like you have enough companions already.", "You have so many ships already. Why do you need another one?");
					link.l1 = "Yes... I think you're right.";
					link.l1.go = "Quest_Whisper_Finish_NoHire";
				}
			}
		break;
	}
}
