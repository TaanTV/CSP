
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("An alarm has been raised in the city. It looks like it's time for me to take up arms...", "Isn't the whole city guard running after you? Come to me, soldiers!!!", "You will not find shelter with me. But you'll find a few inches of cold steel under the rib!"),
					LinkRandPhrase("What do you need, scoundrel?! The city guard has already are on your trail, you can't get far, dirty pirate!", "Dirty murderer! Guards!!!", "I'm not afraid of you, scoundrel! You'll be hanged in our fort soon, you won't get far..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("It looks like you're tired of living...", "Heh, and peaceful citizens don't live in peace " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"),
					RandPhraseSimple("Go to hell!", "Heh, you have a few seconds left to live..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "I warned you. And then look yourself, to run into or not...";
					link.l1 = "Heh!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "What do you want in my house, you scoundrel?! I'll give you ten seconds to get out of here!";
					link.l1 = LinkRandPhrase("Heh, they know me here too!", "My glory goes ahead of me...", "Hmm, I see.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("I am glad to welcome you to my house. Are you on business with me?",
						"How can I help you?",
						"Hmm, what can I do for you?",
						"I'm sorry if you don't need me, I'll ask you not to bother me...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("No, just looking around the city, getting to know the residents...",
						"Oh, nothing special...",
						"Nothing...",
						"Okay, whatever you say.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("I'm sorry, you showed up at my house at the wrong time - it's night outside. I'm asking you to leave my house!",
						"I have already said that the time is late. Please leave.",
						"I don't want to be rude, but I insist that you leave my house immediately!",
						"What the hell is this?! Guards, thieves!!!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Okay, I understand...",
						"Yes, now...",
						"Okay, don't get all worked up.",
						"Shut up, what thieves?!", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "Oh, let me introduce myself - " + GetFullName(npchar) + ". We are glad to see you, the laws of hospitality for our city are not an empty phrase.";
			link.l1 = GetFullName(pchar) + ", with your permission...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			if(!CheckCharacterPerk(pchar, "Grunt") && pchar.reputation >= 30)
			{
				dialog.text = LinkRandPhrase("Yes you are "+ GetSexPhrase("thief, my dear! Guards, hold him down", "thief! Guards, hold her down") +"!!!", "Wow! As soon as I looked at it, you went straight into the chest with your head! Hold "+ GetSexPhrase("thief", "thief") +"!!!", "Guards! They're robbing!!! Hold "+ GetSexPhrase("thief", "thief") +"!!!");
				link.l1 = "Ah, the devil!!!";
				link.l1.go = "fight";
				if (CheckAttribute(pchar, "KIP_PI_SleditZaNami"))	//Проверка квеста "The losing player"
				{
					DoQuestFunctionDelay("LooserGenerator_FailedByEnc", 0.1);
				}
			}
			if(CheckCharacterPerk(pchar, "Grunt") || pchar.reputation < 30)
			{
				dialog.text = LinkRandPhrase("Yes you are "+ GetSexPhrase("thief, my dear! Guards, hold him down", "thief! Guards, hold her down") +"!!!", "Wow! As soon as I looked at it, you went straight into the chest with your head! Hold "+ GetSexPhrase("thief", "thief") +"!!!", "Guards! They're robbing!!! Hold "+ GetSexPhrase("thief", "thief") +"!!!");
				link.l1 = "Shut up! I'll tear my mouth, I'll put out my blink! All my life... you will work for medicines!";
				link.l1.go = "nofight";
			}
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("I warn you that my husband will be coming home soon! If you were walking out of my house...", "I don't think you'll be able to escape. And know that my husband is coming home soon!", "My husband will be home soon, you need to leave here immediately!"),
					LinkRandPhrase("Oh, it's a pity my husband is not at home... Get out!!!", "Dirty murderer, get out of my house! Guards!!", ""+ GetSexPhrase("What a scoundrel", "What a scoundrel") +"... My husband will come soon and see what color your blood is!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Husband, he ate too many pears...", "Heh, you can't scare me with a husband, pussy..."),
					RandPhraseSimple("Shut your mouth, or I'll let my guts out...", "I'll only stay here as long as I want. And you sit quietly, otherwise it will be worse..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "I warned you. Get out, or it will get worse!";
					link.l1 = "One word is a fool...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "What do you need in my house, "+ GetSexPhrase("scoundrel", "scoundrel") +"?! If you don't get out in ten seconds, then I'll call the guards!";
					link.l1 = "What a fool...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("I am glad to see you in our house. My name is " + GetFullName(npchar) + ". How can I help you?",
						"Are you still here?",
						"Hmm, I'm sorry, but don't you think you've been staying with us too long?",
						"I ask you not to abuse our hospitality.", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat( GetFullName(pchar) + ", at your service. Come to you without a specific case, just to get acquainted.",
						"Still here.",
						"Well, how can I say...",
						"Okay.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Oh, my God, why are you breaking into the house at such a time! They just scared me... I ask you to leave, come to us tomorrow.",
						"Go away, please! "+ GetSexPhrase("I'm a married woman!", "") +"",
						"I kindly ask you to leave our house for the last time!",
						"What is it doing?!!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Don't be afraid, I won't hurt you.",
						"Okay, don't worry...",
						"I'm leaving.",
						"What's the matter?", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "Well, we are always glad to have guests. I just ask you not to stay too long"+ GetSexPhrase("I have, since I'm married...", "I have a lot to do.") +"";
			link.l1 = "Oh, yes, of course...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			if(!CheckCharacterPerk(pchar, "Grunt") && pchar.reputation >= 30)
			{
				dialog.text = "Oh, so that's how it is?! I let you into the house as a guest, and you decided to rummage through the chests?! Guards-ah!!!";
				link.l1 = "Shut up, you fool...";
				link.l1.go = "exit_setOwner";
				LAi_group_Attack(NPChar, Pchar);
				if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			}
			if(CheckCharacterPerk(pchar, "Grunt") || pchar.reputation < 30)
			{
				dialog.text = "Oh, so that's how it is?! I let you into the house as a guest, and you decided to rummage through the chests?! Guards-ah!!!";
				link.l1 = "Shut up! I'll tear my mouth, I'll put out my blink! All my life... you will work for medicines!";
				link.l1.go = "nofight";
			}
		break;
		case "HouseWoman_2":
			dialog.text = "How many times have I asked you to get out of the house in a good way! Well, that's enough... Help! Guards!!!";
			link.l1 = "Shut up, you fool, are you crazy?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- завсклад ---------------------------------
		case "SkladMan":
			NextDiag.TempNode = "SkladMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("The alarm has been raised in the city. It looks like it's time for me to take up arms...", "Isn't the whole city guard running after you? Come to me, soldiers!!!", "You will not find shelter with me. But you'll find a few inches of cold steel under the rib!"),
					LinkRandPhrase("What do you need, scoundrel?! The city guard has already are on your trail, you can't get far, dirty pirate!", "Dirty murderer! Guards!!!", "I'm not afraid of you, scoundrel! You'll be hanged in our fort soon, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("It looks like you're tired of living...", "Heh, and peaceful citizens don't live in peace" + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"),
					RandPhraseSimple("Go to hell!", "Heh, you have a few seconds left to live..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = "What do you need here? Wait, I think I know you... Guards, take that bastard!!!";
				link.l1 = "Now you will be silent forever...";
				link.l1.go = "fight";
				if (CheckAttribute(pchar, "KIP_PI_SleditZaNami"))	//Проверка квеста "The losing player"
				{
					DoQuestFunctionDelay("LooserGenerator_FailedByEnc", 0.1);
				}
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Greetings! My name is " + GetFullName(npchar) + ". I'm in charge of everything here, so don't take anything with you...",
					"Behave yourself. And remember that I'm watching over you.",
					"As long as you don't go into the chests, it's okay, you can stay here. I'm bored alone...",
					RandPhraseSimple("Oh, the boredom is mortal here!", "Oh, damn it, what would you do?"), "block", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Okay, don't worry.",
					"Of course!",
					"I understand...",
					"Yes, you have serious problems...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
				//открывание двери верфи по квесту промышленного шпионажа
				if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
				{
					link.l2 = "Listen, buddy, I want to talk to you frankly.";
					link.l2.go = "ShipyardsMap_1";
					pchar.questTemp.different.ShipyardsMap = "toResult";
				}
			}
		break;
		case "ShipyardsMap_1":
			dialog.text = "Heh! Well, let's talk.";
			link.l1 = "I need to get to the shipyard at night when no one is there.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "Wow! Hey guards, there's a thief coming!!!";
				link.l1 = "Which thief?! I want to talk!..";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingLight", 5);
				AddCharacterExpToSkill(pchar, "Fencing", 5);
				AddCharacterExpToSkill(pchar, "FencingHeavy", 5);
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.text = "Ho! Well, you give "+ GetSexPhrase("buddy. I came", "girlfriend. She came") +"to the shipyard warehouse with such a request!";
				link.l1 = "I don't need to go to the warehouse, but to the shipyard. I haven't set foot here...";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "Why do you need this?";
			link.l1 = "It's necessary, buddy, it's necessary. I'm ready even to ypay...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Hmm, it's already more interesting... In general, so! Drive " + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000) + ", and for the next day I will leave the front door of the shipyard open.";
			link.l1 = "It's too expensive for me. I'll manage...";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "Okay, I am " + GetSexPhrase("I agree", "I agree") +". Take the money and do as agreed.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "Don't worry, I'll do it.";
			link.l1 = "Okay, I believe...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;
		case "nofight":
			dialog.text = "Okay, okay, I don't need any problems! Take whatever you want, just don't touch it!";
			link.l1 = "With your permission, hehe!";
			link.l1.go = "exit_setOwner";
			NextDiag.TempNode = "nofight";
		break;
	}
}
