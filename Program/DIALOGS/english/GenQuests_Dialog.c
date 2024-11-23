void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods;
	String sTitle, sGroup, sTemp;
	float locx, locy, locz;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг. Как он здесь оказался? Сообщите о нем Warship'у и подробно расскажите, как Вы его получили.";
					link.l1 = RandSwear() + "I will definitely inform you!";
					link.l1.go = "exit";

			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "meeting at the bay"
			{
				dialog.text = "I am not authorized to talk to you. Contact our officer.";
					link.l1 = LinkRandPhrase("Of course...", "Clear.", "Required!");
					link.l1.go = "exit";
				break;
			}

			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "meeting at the bay"
			{
				dialog.text = "Introduce yourself, I want to know who I'm talking to!";
					link.l1 = "My name is " + GetFullName(PChar) + ". What's going on here?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}

			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting at the bay"
			{
				dialog.text = "Cap, your name is" + GetFullName(PChar) + ", isn't it?";
					link.l1 = "Yes, it is...";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "No. You've confused me with someone else...";
					link.l2.go = "exit";
					break;
			}

			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name + ", thank you very much! If it weren't for you, my fate would be deplorable... How can I thank you?";
					link.l1 = "I don't need anything...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "I would not refuse a small reward.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}

			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "meeting at the bay"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Hmm, indeed, this is it... Thank you, "+ GetSexPhrase("guy","girl") +", without your help, we would have had a hard time - all the ways out of the city are blocked for us. Here, hold " + FindRussianMoneyString(iMoney) + " and you can get lost. And we'll go talk to our friend...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Hmm, indeed, this is it... Thank you, "+ GetSexPhrase("guy","girl") +", without your help, we would have had a hard time - all the ways out of the city are blocked for us. Here, hold " + FindRussianMoneyString(iMoney) + " and get lost. Don't stop us from gutting this traitor!...";
						link.l1 = "Of course. See you later, gentlemen...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "What?! No, I will not allow murder to be committed, whoever it is... And I don't need your blood money!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}

			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "So-so-so... What do we have here?! Pirates?! You will have to come with us to the commandant's office for the trial...";
					link.l1 = "We are not pirates at all! I don't even know this man! He just moved into this room!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}

			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "So what were you saying? You owe to pass me a message?! Come on then!";
					link.l1 = "Hold...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}

			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Hey you! Yes, you are. I see you're a decent "+ GetSexPhrase("man","girl") + ", not poor.";
					link.l1 = "I would rate it like a compliment, if it didn't come from a crook like you.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}

			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Stop! Come on, "+ GetSexPhrase("buddy","girlfriend") +"Show me if your purse is too heavy!";
					link.l1 = "Have you already attached the church money?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}

			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "Hey-ik, in the boat! Clear the fairway, I need to talk to the guys...";
					link.l1 = "You've had a blast, buddy. Go and sleep it off.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "Hey, cap! Drop anchor, we've sailed...";
					link.l1 = "Why should I....";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "Who are you being rude to!?";
				link.l2.go = "ReasonToFast_Hunter3";
			}

			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Wait, "+ GetAddress_Form(pchar) +"! Would you give me a moment of your precious attention?","Won't the noble captain listen to the humble request of your unworthy interlocutors?","Noble captain, take a couple of minutes of your precious time to talk to the underprivileged.");
				link.l1 = LinkRandPhrase("I have no time.", "Get out of the way, and there are enough worries without you.", "Get off. Not up to you.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("What do you need?", "What do you want?", "What's the matter?");
				link.l2.go = "Convict_Begin";
			}
		break;

		// Генератор "The situation in the hold is a ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "I'm listening to you, Captain. Are you on business?";
			link.l1 = "I am looking for " + pchar.GenQuest.Hold_GenQuest.Name + "?";
			link.l1.go = "Hold_GenQuest2";
		break;

		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("I am " + pchar.GenQuest.Hold_GenQuest.Name + ". With whom do I have the honor, excuse me?","You found him. What can I do for you?");
			link.l1 = "I am the captain " + GetFullName(pchar) + ", I have a matter for you regarding " + pchar.GenQuest.Hold_GenQuest.CapName + ".";
			link.l1.go = "Hold_GenQuest3";
		break;

		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);

			switch(drand(3))
			{
				case 0:
					dialog.text = "Who is this?";
					link.l1 = "Wait, are you - " + pchar.GenQuest.Hold_GenQuest.Name + ", and don't know who " + pchar.GenQuest.Hold_GenQuest.CapName + "?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "Oh, haven't you heard from that old rascal in a while? What happened to him this time?";
					link.l1 = "He's in serious trouble this time... He has been captured and is asking for your help.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "Okay, I'm listening to you carefully.";
					link.l1 = "His ship was attacked by pirates, and he was captured and offered me to ask you for a ransom.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "Yes, I'm glad to hear about an old friend. How is he doing?";
					link.l1 = "He is in such a difficult position that it is difficult to imagine.";
					link.l1.go = "Hold_GenQuest70";
				break;
			}
		break;

		case "Hold_GenQuest40":
			dialog.text = "Yoy're absolutely right, I am " + pchar.GenQuest.Hold_GenQuest.Name + "! But why should I know " + pchar.GenQuest.Hold_GenQuest.CapName + "?!";
			link.l1 = "Sorry, there must have been an error...";
			link.l1.go = "Hold_GenQuest41";
		break;

		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;

		case "Hold_GenQuest50":
			dialog.text = "Wow! And how am I going to help him? Shouldn't we free him by killing all the enemies, ha ha ha?";
			link.l1 = "No, it won't be necessary... You just need to pass " + pchar.GenQuest.Hold_GenQuest.RansomSum + "gold as a ransom.";
			link.l1.go = "Hold_GenQuest51";
		break;

		case "Hold_GenQuest51":
			dialog.text = "This is arrogance! Why on earth should I pay a ransom for him?! Who exactly is he to me?!";
			link.l1 = "Hmm, and he told me that you are his last hope. And he also hinted at some kind of debt...";
			link.l1.go = "Hold_GenQuest52";
		break;

		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("Oh, what an impudent fellow! He owes me a tidy sum himself! But this is not a reason to pay a ransom for him in the hope that he will repay both debts.",
				"Well, isn't he a scoundrel?! Not only did he rob me when we were dividing the business, he also has the conscience to ask for a ransom!",
				"Those times! Why on earth would I fork out for him?! We don't know each other that well.");
			link.l1 = "Does that mean to tell him that you refuse to pay the ransom and do not recognize your debt?";
			link.l1.go = "Hold_GenQuest53";
		break;

		case "Hold_GenQuest53":
			dialog.text = "My God! Well, what kind of debt?! I've already explained everything to you! And anyway, if you have no more questions besides this stupid story, then let me take my leave.";
			link.l1 = "Well, there are no more questions for you... But there were a lot of questions for your friend...";
			link.l1.go = "Hold_GenQuest54";
		break;

		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;

		case "Hold_GenQuest60":
			dialog.text = "Hmm, so you are t"+ GetSexPhrase("from","a") +" who is holding it... Well, I'll be happy to help him.";
			link.l1 = "That's great. The redemption amount is " + pchar.GenQuest.Hold_GenQuest.RansomSum + " gold.";
			link.l1.go = "Hold_GenQuest61";
		break;

		case "Hold_GenQuest61":
			dialog.text = "You misunderstood me: this is a member of the city council for the supervision of compliance with the charter " +
				"Guards!!! Guards! Arrest "+ GetSexPhrase("this person","her") +" on suspicion of slave trade and robbery of ships " + NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation)) + "!";
			link.l1 = "Well, 'comrade,' I'll get to you...";
			link.l1.go = "Hold_GenQuest62";
		break;

		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;

		case "Hold_GenQuest70":
			dialog.text = "What are you saying?! Is there anything I can do to help him?";
			link.l1 = "He was captured and asked me to talk to you about the ransom.";
			link.l1.go = "Hold_GenQuest71";
		break;

		case "Hold_GenQuest71":
			dialog.text = "Of course, of course. I'll do my best. Where is it? How much money are we talking about?";
			link.l1 = "Pirates require " + pchar.GenQuest.Hold_GenQuest.RansomSum + " gold. I owe to deliver the money to the port, and then your friend will be free.";
			link.l1.go = "Hold_GenQuest72";
		break;

		case "Hold_GenQuest72":
			dialog.text = "Here's the money. Fortunately, I had enough with me.";
			link.l1 = "Yes, it turned out really well. Go to the port, you'll be able to see your buddy soon.";
			link.l1.go = "Hold_GenQuest73";
		break;

		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		// Генератор "The situation in the hold is a ransom"

		// Генератор "The situation in the hold is an accomplice"
		case "Hold_GenQuest80":
			dialog.text = "Hello, Captain, I did not have the honor to be introduced. I was told that you were looking for me.";
			link.l1 = "That's right, if you are the master " + pchar.GenQuest.Hold_GenQuest.Name + ". I am captain " + GetFullName(pchar) + ", I wanted to talk about a case.";
			link.l1.go = "Hold_GenQuest81";
		break;

		case "Hold_GenQuest81":
			dialog.text = "And what's the deal, Captain " + GetFullName(pchar) + "?";
			link.l1 = "I have heard rumors that you have a thing that you would like to get rid of.";
			link.l1.go = "Hold_GenQuest82";
		break;

		case "Hold_GenQuest82":
			dialog.text = "What are you implying?";
			link.l1 = "Don't persist, my dear, I know exactly about your dark past, and about the homemade map where the treasure is located " + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC) + " specified.";
			link.l1.go = "Hold_GenQuest83";
		break;

		case "Hold_GenQuest83":
			dialog.text = "Oh, damn it! I knew that this scoundrel " + pchar.GenQuest.Hold_GenQuest.CapName + " sooner or later he'll blurt it out! And it tugged at my tongue to offer him this case!";
			link.l1 = "Okay, stop wailing. I'm not with evil... Sell me this map and move on as you have been living.";
			link.l1.go = "Hold_GenQuest84";
		break;

		case "Hold_GenQuest84":
			dialog.text = "Hmm, it would be nice if so... And how much will you give for it? After all, keep in mind, there was a lot of gold in the chest - four of them dragged it to the place... God rest their souls...";
			link.l1 = "But " + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_NOM) + " could have taken his treasure... ";
			link.l1.go = "Hold_GenQuest85";
		break;

		case "Hold_GenQuest85":
			dialog.text = "And that's your truth... Eh, I was not - for " + pchar.GenQuest.Hold_GenQuest.Sum + "I'll give it to you. All the same, I will not dare to disturb the dead myself.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "So be it, it's a deal...";
				link.l1.go = "Hold_GenQuest86";
			}
			link.l2 = "No, dear, your piece of paper is not worth that much money. Goodbye...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;

		case "Hold_GenQuest86":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest");
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "The situation in the hold is an accomplice"

		// Генератор "Castaways"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterReputation(pchar, -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;

		case "Convict_Begin":
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Captain, help us get a longboat or a tartan, everything is the same for us. Due to circumstances, we are forced to leave this inhospitable place, and there is no way to shine in the settlement.";
					link.l1 = "What kind of circumstances are these?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Captain, could you borrow a few hundred piastres? We would not have asked, but the need forced us.";
					link.l1 = "Need you say? I guess I'm out of rum-that's all I need.";
					link.l1.go = "Convict_12";
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Captain, would you be so kind as to give our humble company a sail to the " + XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen") + " lighthouse.";
					link.l1 = "Something is not noticeable on your faces of special modesty.";
					link.l1.go = "Convict_13";
				break;
			}
			link.l2 = LinkRandPhrase("I don't file on Fridays.","I don't have time for any nonsense.","I'm not going to help anyone.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;

		case "Convict_11":
			dialog.text = "We are fugitives... with " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + ". And look, the former owner will come to his senses - then there will be no escape...";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "So you can handle sails?";
				link.l1.go = "Convict_11_1";
			}
			link.l2 = "And what are you going to pay with?";
			link.l2.go = "Convict_11_2";
		break;

		case "Convict_12":
			dialog.text = "We are not up to rum now. We escaped from " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + " a week ago, now we're hiding in the jungle, we wouldn't starve to death...";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Well, let's say I give you money, and then what? Are you going to hide until the patrol arrives?";
				link.l1.go = "Convict_12_1";
				link.l2 = "Okay, how much are you asking for?";
				link.l2.go = "Convict_12_2";
			}
			link.l3 = "I have a short conversation with people like you - a head on the block and a sentence to execution.";
			link.l3.go = "Convict_12_3";
		break;

		case "Convict_12_1":
			if(drand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "What do you want us to do? We wouldn't mind being hired as sailors, but who's going to take us on the run?";
				link.l1 = "I'll take it if you're familiar with the sail and won't run from a bullet.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "Yes, we have already agreed with the local fishermen. We're only three thousand short to get out of here.";
				link.l1 = "Keep your three thousand if it really helps.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Well, I don't know... These are your problems, solve them somehow without me.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;

		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Take it, Captain - you won't regret it! We are still with " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " they pirated in the Adriatic until he was hanged, and us " + pchar.GenQuest.Convict.ConvictQty + " the man was not sent here.";
			link.l1 = "That's nice. There is a place nearby, " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + " it's called. I'll pick you up there around midnight. Tea will not get lost.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);

		    makeref(MerPrm, MerchantParam);
			iTmp = drand(2);
			iTmp += !MerPrm.active;//добавляем вариант с генерацией легкой добычи только если она сейчас неактивна
			if(iTmp <= 1)
			{
				dialog.text = "Of course it will help! Today we will set sail, if the wind allows and the fishermen will not let us down. Thank you, Captain, may God protect you...";
				link.l1 = "And good luck to you.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "That's good luck! We did not expect to get money so quickly. Allow me, Captain, from the bottom of my heart to present you with a little thing that we stole from the former owner. Perhaps it will bring you good luck.";
				link.l1 = "Thanks, nice thing. Good luck to you.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();//не используется сейчас, так как в слухи переведено
				GenerateMerchant();
				dialog.text = "You can immediately see a generous person who is not afraid to part with money, because he knows how to get it!Last night we saw smugglers loading cargo into boats " + MerPrm.QuestGoodsIdx + ". It was dark, but on board one of the boats it was possible to read the name of the vessel - '" + MerPrm.ShipName + "'... The ship is flying the flag of " + MerPrm.nation + ". I think this might be useful to you, hehe.";
				link.l1 = "Oh? It may come in handy... Well, goodbye, trackers.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;

		case "Convict_12_2":
			dialog.text = "For God's sake, should we set conditions? No matter how much you give, we will be grateful for everything.";
			link.l1 = "300 gold.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 gold.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000 gold.";
			link.l3.go = "Convict_12_2_3";
		break;

		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Thank you, Captain, may the Lord protect you...";
			link.l1 = "And good luck to you.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(drand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "That's good luck! We did not expect to get money so quickly. Allow me, Captain, from the bottom of my heart to present you with a little thing that we stole from the former owner. Perhaps it will bring you good luck.";
				link.l1 = "Thanks, nice thing. Good luck to you.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Thank you, Captain, may the Lord protect you...";
				link.l1 = "And good luck to you.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);

			makeref(MerPrm, MerchantParam);
			if(drand(1) == 0 || MerPrm.active != true)//если уже сгенерирована легкая добыча, новую не делаем
			{
				dialog.text = "That's good luck! We did not expect to get money so quickly. Allow me, Captain, from the bottom of my heart to present you with a little thing that we stole from the former owner. Perhaps it will bring you good luck.";
				link.l1 = "Thanks, nice thing. Good luck to you.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();//не используется сейчас, так как в слухи переведено
				GenerateMerchant();
				dialog.text = "You can immediately see a generous person who is not afraid to part with money, because he knows how to get it!Last night we saw smugglers loading cargo into boats " + MerPrm.QuestGoodsIdx + ". It was dark, but on board one of the boats it was possible to read the name of the vessel - '" + MerPrm.ShipName + "'... The ship is flying the flag of " + MerPrm.nation + ". I think this might be useful to you, hehe.";
				link.l1 = "Oh? It may come in handy... Well, goodbye, trackers.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;

		case "Convict_12_1_End":
			ChangeCharacterReputation(pchar, -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_3":
			if(drand(1) == 0)
			{
				dialog.text = "Don't ruin it, Captain! We have a decent thing - take it as a ransom, and let it go in good time...";
				link.l1 = "Give me your thing and get out while you're safe.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "We have no choice - two deaths will not happen, and one will not pass. Oh, let's give one last shudder!";
				link.l1 = "This is a different conversation! Otherwise, they decided to be nice!";
				link.l1.go = "Convict_Fight";
			}
		break;

		case "Convict_13":
			dialog.text = "Well, we are certainly not saints, but we don't need to quarrel over trifles either... We are fugitives, we should get out of here as soon as possible.";
			link.l1 = "Do you have something to pay for the transportation?";
			link.l1.go = "Convict_13_1";
			link.l2 = "That's it... I don't want to ruin my reputation because of you. Goodbye.";
			link.l2.go = "Convict_11_5";
		break;

		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "But what about without it? We are also used to boarding. Read two years with the deceased " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " local merchants were kept in fear, only then he was hanged, and us - " + pchar.GenQuest.Convict.ConvictQty + " a man was sold to hard labor.";
			link.l1 = "Would you like to join my team? In calculations, I am not stingy, but I do not promise a quiet life either.";
			link.l1.go = "Convict_11_3";
		break;

		case "Convict_11_2":
			dialog.text = "Yes, we picked up something from " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + " so as not to be in trouble for the first time, so we'll pay double. Only the calculation will be in place. And don't bring the guards. We do not forgive offenses...";
			link.l1 = "Well, wait for me " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Voc") + ". There will be a boat for you closer to midnight... And don't expect to deceive me!";
			link.l1.go = "Convict_11_4";
			link.l2 = "No, good gentlemen, what if I'm a boat for you - and you're a dirk under my rib? In a word, I can't help you in this case.";
			link.l2.go = "Convict_11_5";
		break;

		case "Convict_11_3":
			dialog.text = "With great pleasure, Mr."+ GetSexPhrase("dean","Ms.") +" Captain. This case is familiar to us, but the road to the Royal Navy has been ordered for us - with such recommendations, hehe.";
			link.l1 = "That's nice. There is a place nearby, " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + " it's called. I'll pick you up there after midnight. Tea will not get lost.";
			link.l1.go = "Convict_11_6";
		break;

		case "Convict_11_4":
			dialog.text = "But captain, we are risking more than you. What if you decide to report to the commandant?";
			link.l1 = "And that's right... If I don't show up by morning, then the deal is off.";
			link.l1.go = "Convict_11_7";
		break;

		case "Convict_11_5":
			if(makeint(pchar.reputation) < 10 || makeint(pchar.reputation) > 90)
			{
				dialog.text = "Eh, Captain, we were hoping so much...";
				link.l1 = "Nothing. If there is money, then there will be a cab driver. Goodbye.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterReputation(pchar, -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "And you, captain, little tart. You'll probably run straight to the commandant's office. Do you think you can just slip away?";
				link.l1 = "Did you decide to stop me in any way?! Well, then get it!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}
		break;

		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", pchar.GenQuest.Convict.ConvictQty);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Voc"));
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "There is something. We rummaged a little in the owner's chests, although a lot of noise happened because of this - we had to break through with a fight. Only " + PChar.GenQuest.Convict.ConvictQty + "man alive and escaped.";
			link.l1 = "Considering the circumstances, I'm not going to ship you cheaper than " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + " each.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "And you, I see, are not shy. Will you join my team?";
				link.l2.go = "Convict_13_3";
			}
		break;

		case "Convict_13_2":
			dialog.text = "I think we don't have a choice, and we'll go for " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + "...";
			link.l1 = "Come on " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc") + " then. After midnight I'll send a boat for you.";
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;

		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Why not go? We are familiar with this case, also " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " and I in " + RandPhraseSimple("Gibraltar","English Channel") + " hunted until we got here.";
			link.l1 = "That's nice. There is a place nearby, " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + " it's called. I'll pick you up there around midnight. Tea will not get lost. ";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;

		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("xia","as"));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", pchar.GenQuest.Convict.ConvictQty);
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Eh, Captain, you probably ran around with an empty purse recently, but as it rang in my pockets, you turn your nose away from ordinary people.","Captain, it's not good to treat ordinary people like that. We all walk under the same God."),
											RandPhraseSimple("Eh-eh, the people have completely hardened their souls. You live as if you've been measured out for two centuries.","It's immediately obvious that you recently came from Europe - you haven't smelled the stench of our tropical garbage yet."));
			link.l1 = LinkRandPhrase("Are you going to shame me in any way?! I'm going to shorten your tongue now!","Are you threatening me?! Well, hold on!!!","Is that a philosopher? Now I'm going to fix your brain!");
			link.l1.go = "Convict_Fight";
			pchar.GenQuest.Convict = "fight";
		break;

		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(pchar.location, true);
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Convict_15":
			dialog.text = LinkRandPhrase("Well, Captain? have you brought a boat?","Welcome, Captain. Well, is the job done?","Hello captain, and we were already worried. Did everything go smoothly?");
			if(Convict_CheckShipType(SHIP_LEUDO) || Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_FELUCA))
			{
				link.l1 = "Yes, get your shell. And don't forget about the money. I asked " + pchar.GenQuest.Convict.ShipPrice + " gold, so that's enough for you " + sti(pchar.GenQuest.Convict.ShipPrice) * 2 + " as agreed.";
				link.l1.go = "Convict_15_1";
			}
			link.l2 = "No, I changed my mind. Find yourself another assistant. Have a nice stay...";
			link.l2.go = "Convict_15_2";
		break;

		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "What is the conversation about?! Our freedom was taken away from us, but not our conscience - you will receive payment and our immense gratitude. You've helped us out a lot. We'll settle with you in silver bars-do you mind?";
					link.l1 = "No, of course not. Have a nice swim. Just don't get caught in the open sea-I have a short conversation there.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry17", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Captain, we've been thinking that money is not the main thing in this life. And we probably need them more now. And we have one thing that we stole from the former owner, perhaps it will interest you more than any money. Take a look...";
					link.l1 = "Yes, you are right. The thing is really interesting. Well, thank you, and goodbye.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
					dialog.text = "Why do you need so much money, Captain? You are not in distress as it is. And without this boat, we are certain death. So don't blame me. We are a ship of this and that... Long story short, we're taking it.";
					link.l1 = "That's where you miscalculated. Without a boat, you could have gone swimming, and now you will stay here forever.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;

		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;

		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;

		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","a"));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}
			ChangeCharacterReputation(pchar, -2);
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_16":
			dialog.text = RandPhraseSimple("Well, Captain? Can I load up?","My plans have changed. You'll have to look for another captain.");
			link.l1 = "Get in the boat, I don't have much time.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Get in the boat, I don't have much time.";
				link.l2.go = "Convict_16_2";
			}
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Oh, damn you!.. I suppose the patrol has already sent ";
				link.l2.go = "Convict_16_2";
			}
		break;

		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "Ah! Fuck you! I bet you've already sent a patrol after us! You won't get away with this!";
				link.l1 = "What are you talking about?! Tired of living?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Captain, you're like little pussy...";
				link.l1 = "Ohh, shut up...";
				link.l1.go = "Convict_16_3";
			}
		break;

		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false);
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_16_3":
			ChangeCharacterReputation(pchar, -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","a"));
			CloseQuestHeader("Convict");
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_17":
			dialog.text = LinkRandPhrase("Thank you, "+ GetSexPhrase("kind man","sweet girl") +".","Thank you, captain - consider yourself pulled out of the loop.","Thanks for the pleasant the journey.");
			link.l1 = LinkRandPhrase("It's all good, but I'm waiting for the calculation.","It's time to pay off.","Money on the barrel, as agreed.");
			link.l1.go = "Convict_17_1";
		break;

		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Of course, of course! What kind of questions can there be! Here, keep the agreed amount in gold bars and our immense gratitude.";
					link.l1 = "Good luck to you too... Have a nice stay.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Captain, we've been thinking that money is not the main thing in this life. And we probably need them more now. And we have one thing that we stole from the former owner, perhaps it will interest you more than any money. Take a look...";
					link.l1 = "Yes, you are right. The thing is really interesting. Well, thank you, and goodbye.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "Why do you need so much money? You are not in distress as it is. You helped us out - there will be a chance, and we will help you out.";
					link.l1 = "It won't. Pray, you scoundrels, I do not forgive debts.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);
					break;
			}
		break;


		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Abl"));
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Abl"));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// <-- Генератор "Convicts"

		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "The one, who sent me here is "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ", okay?";
			link.l1 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "he's been waiting for you for two hours with an answer. Here, he sent me next.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;

		case "ReasonToFast_Hunter2":
			dialog.text = "I've been following you for a long time, but you're too fast.";
			link.l1 = "So what?";
			link.l1.go = "ReasonToFast_Hunter6";
		break;

		case "ReasonToFast_Hunter3":
			dialog.text = "Answer me better, does the governor pay his sixers a lot?";
			link.l1 = "Damn it!...";
			link.l1.go = "ReasonToFast_Fight";
		break;

		case "ReasonToFast_Hunter4":
			dialog.text = "I didn't drink at all - I was looking for a boatswain...";
			link.l1 = "Go, go... I'll tell to "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ", that you've lost in the jungle.";
			link.l1.go = "ReasonToFast_Hunter5";
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;

		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;

		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;

		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY);
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors");
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap":
			dialog.text = "And you provided"+ GetSexPhrase("you're a smart little one","you're a smart little one") +". Pray to God that no one finds out about your tricks " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			link.l1 = "He won't find out if you don't tell him... And you won't do that, will you?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;

		case "ReasonToFast_FightCap_1":
			dialog.text = "From what?! I will do it with great pleasure!";
			link.l1 = "He'll hang you anyway. For the stupidity that you have committed. So don't waste any time, and I'll help you get rid of the gallows.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;

		case "ReasonToFast_FightCap_2":
			dialog.text = "Hmm... In what way?";
			link.l1 = "I'll kill you...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;

		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "Are you on business, "+ GetSexPhrase("monsieur","mademoiselle") +"?";
			link.l1 = "No, I am visiting this truly luxurious residence at the invitation of the governor's charming wife.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "I accept"+ GetSexPhrase("eu","if") +"a message from people you know.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "Yes. I want to bring you to justice!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;
		break;

		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Oh yes, I am lucky to serve in such a gorgeous house.";
			link.l1 = "No wonder...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Don't forget to take a look at our garden!";
			link.l1 = "Thank you, my dear!";
			link.l1.go = "exit";
			bDisableFastReload = false;
		break;

		case "ReasonToFast_Lakey2":
			dialog.text = "Umm... " + pchar.questTemp.ReasonToFast.password + "?";
			link.l1.edit = 1;
			link.l1 = "";
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "You won't succeed, Judas!";
			link.l1 = "Stop, you bastard!!!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Hurry up, take your valuables and leave!";
				link.l1 = "I think it's time for you to get out too.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";
				bDisableFastReload = true;
				//chrDisableReloadToLocation = true;
			}
			else
			{
				dialog.text = "Mmm, sorry, I need to leave immediately.";
				link.l1 = "Stop, you bastard!!!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;

		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Yes you are "+ GetSexPhrase("thief, my dear! Guards, hold him down","thief! Guards, hold her down") +"!!!", "Wow! As soon as I looked at it, you went straight into the chest with your head! Hold this theif!!!", "Guards! They're robbing!!! Hold this theif!!!");
			link.l1 = "Ah, the devil!!!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break;
		// Генератор "A reason to hurry" <--

		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Hello, "+ GetSexPhrase("buddy","girlfriend") +"! I've prepared a surprise for you - I've set fire to the cord leading to the hook-up chamber. Now there will be such an explosion that the devils in hell will hear!","What are you standing for?! There's a fire in the hook chamber! Now there will be such fireworks - they will see it in Europe!");
			link.l1 = RandPhraseSimple("Oh, you rascal! You can't fool me. Fight, coward!","I see the rats are fleeing from the ship, and you are in the front ranks?!");
			link.l1.go = "ShipSituation12";
		break;

		case "ShipSituation12":
			dialog.text = RandPhraseSimple("Run and you, if you want to live... Okay, I don't have time - the boat is waiting. And have a good fishing trip for you!","I have no time to play nobility - the guys in the boat will not wait. Have a good fishing trip, winner"+ GetSexPhrase("","nice") +"!");
			link.l1 = RandPhraseSimple("Oh shit!!!.. Cut the fenders!!! Let's go!","It's necessary to get into so much trouble!.. Open the kingstons! Let's get out of here!");
			link.l1.go = "ShipSituation_End";
		break;

		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "What?! Do you think you won a duel?! You rejoice early. I set fire to the cord leading to the hook cell - so I can't let you get off this ship alive.";
			link.l1 = RandPhraseSimple("Oh, you rascal! You can't fool me. Fight, coward!","I see the rats are fleeing from the ship, and you are in the front ranks?!");
			link.l1.go = "ShipSituation22";
		break;

		case "ShipSituation22":
			dialog.text = RandPhraseSimple("I am fulfilling my oath, but this does not oblige me to die so stupidly. I'm sorry, I'm not offering a place in the boat, I'm afraid the sailors won't understand.","The ships fell safely in boarding, so your fate is decided. Sorry, the boat is waiting...");
			link.l1 = RandPhraseSimple("Oh shit!!!.. Cut the fenders!!! Let's go!","It's necessary to get into so much trouble!.. Open the kingstons! Let's get out of here!");
			link.l1.go = "ShipSituation_End";
		break;

		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("Well, the winner?! Welcome to the underworld! I set fire to the cord leading to the hook cell.","Here you are, dear! Now you can't get out of it - I set fire to the hook cell.");
			link.l1 = RandPhraseSimple("Oh, you rascal! You can't fool me. Fight, coward!","I see the rats are fleeing from the ship, and you are in the front ranks?!");
			link.l1.go = "ShipSituation32";
		break;

		case "ShipSituation32":
			dialog.text = RandPhraseSimple("I've been tracking you for a long time. It's a pity we had to sacrifice the ship. It's okay, they give so much for your head that I'll buy a couple of new ones. Have a good fishing trip!","Do you see how I have to clean you up? With fireworks like Indian "+ GetSexPhrase("prince","princeess") +". Well, come on, I'm not in trouble. Your head is worth more than my boat. Goodbye, the boat won't wait...");
			link.l1 = RandPhraseSimple("Oh shit!!!.. Cut the fenders!!! Let's go!","It's necessary to get into so much trouble!.. Open the kingstons! Let's get out of here!");
			link.l1.go = "ShipSituation_End";
		break;

		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;

		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("Stop, Captain! I want to say a few words to you.","Wait, Captain! I think you'll be interested to know.");
			link.l1 = LinkRandPhrase("What kind of conversations during the fight?!","What am I talking about to a dead man?","What's the matter?! Do you want to leave a will in my name?");
			link.l1.go = "ShipEpidemy2";
		break;

		case "ShipEpidemy2":
			dialog.text = "There is an epidemic on board. I lost a quarter of the crew during the voyage. So all of you are doomed...";
			link.l1 = RandPhraseSimple("You rotten sack! Why didn't they raise a signal that there was a disaster on the ship?!","Why did you forget the naval regulations? There should be a signal on the mast that there is a disaster on the ship!");
			link.l1.go = "ShipEpidemy3";
		break;

		case "ShipEpidemy3":
			dialog.text = "And we all had to die. That's why they didn't give up, so that they could take you and your henchmen to the next world!.. Now I'm satisfied. You can finish your dirty business.";
			link.l1 = RandPhraseSimple("Well, you will answer to me for this!..","I am also satisfied with that you will die sooner. And I'll see it...");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("I will not stain the blade with your filthy blood - live... Although why would you do that? I'm taking the team off this rotten trough.","There's a gallows for that, but you won't need it anymore. I'm taking people away... Live as long as you have left.");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;

		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля

		// Генератор "The Girl in the Jungle"
		case "EncGirl_Lover":
			dialog.text = "Hello, Captain, I was told you were looking for me.";
			link.l1 = "Only if you are " + pchar.GenQuest.EncGirl.sLoverId + ".";
			link.l1.go = "EncGirl_Lover1";
		break;

		case "EncGirl_Lover1":
			dialog.text = "Yes, it's me. Do you have something important?";
			link.l1 = "I don't know how important this is to you, but I brought " + pchar.GenQuest.EncGirl.name +". She ran away from home and is now waiting for you near the tavern.";
			link.l1.go = "EncGirl_Lover2";
		break;

		case "EncGirl_Lover2":
			dialog.text = "Oh my God, I knew it would end like this... Why did she run away, didn't she tell you?";
			link.l1 = "She is being married to the son of a usurer.";
			link.l1.go = "EncGirl_Lover3";
		break;

		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "Well, no, this cannot be allowed! Captain, I'm in such a stupid position... in general, I want to ask you to take us to " + XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland + "Acc") + " to the settlement " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + ", but I have absolutely no money right now - I have not found a job. And in the settlement " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + " I have wealthy parents and plans for the service...I assure you, my parents will be glad to see me with the young bride and will thank you generously. How are you taking it?";
			link.l1 = "...Listen, I have other plans right now. I can advise you to get a job as a sailor on any ship, and instead of a salary, rent your bride a cabin. People from Europe move like that, but a cormorant will fly to your settlement overnight.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Oh, youth! Do you even know what you're asking? Take my daughter away from her parents without a blessing? Of course I will!";
			link.l2.go = "EncGirl_Lover5";
		break;

		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");
			DialogExit();
		break;

		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");
			DialogExit();
		break;

		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("You heard, " + pchar.GenQuest.EncGirl.name + " she ran away with her lover from under the crown. I didn't want to connect my life with a disabled person. And her parents are to blame for everything - they were seduced by the groom's money, there was no need to woo such a beautiful woman for a freak.",
				"Have you heard? " + pchar.GenQuest.EncGirl.name + " I left both my dad and my newly-made fiance with a nose. It is said that a noble captain helped her and her lover escape to another island, where her lover's parents live... Oh, there are people who have not yet forgotten what passion is!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Thank you, Captain. We will not forget this service for the rest of our lives.";
			link.l1 = "Don't mention it. The main thing is that everything works out well for you now.";
			link.l1.go = "EncGirl_Lover7";
		break;

		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "to the store";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "to the shipyard";
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "to the port authority";
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "to the tavern";
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "to the bank";
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}
			if (pchar.location == "DesMoines_town")	//В Дес-Мойнес мало зданий
			{
				switch (rand(1))
				{
					case 0:
						sTemp = "I promised to introduce you to your parents. When you are free, go to ";
						pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
					break;
					case 1:
						sTemp = ", my father works there, I will tell him what you have done for us. I assure you, he will be glad to see you.";
						pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
					break;
				}
			}
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "to the store" + sTemp + "to the tavern";
			link.l1 = "Okay, Okay, I'll come in. Be happy...";
			link.l1.go = "EncGirl_Lover8";
		break;

		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярён за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false;
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();
		break;
		// Генератор "The Girl in the Jungle"

		// Генератор "The Captain's errand"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("Stop!.. Stop, Captain! Wait.","Captain, wait, please...");
			link.l1 = LinkRandPhrase("Are you short of breath?","Raise the blade! Coward.","What's the matter?! Did you forget to leave a will?");
			link.l1.go = "CaptainComission_2";
		break;

		case "CaptainComission_2":
			dialog.text = "Wait, I'm injured and I can't resist anymore... I'm not asking for mercy, but I have one unfinished business. Promise that you will not refuse the dying man.";
			link.l1 = RandPhraseSimple("Don't be a slobber, Captain, accept death like a man!..","Captain, what kind of sentiments? The battle rumbles around. And let's finish what we started with dignity.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Explain it, but quickly. ";
			link.l2.go = "CaptainComission_22";
		break;

		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterReputation(pchar, -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CaptainComission_22":
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Tell " + pchar.GenQuest.CaptainComission.Name + " from the settlement " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City) + " that I was unable to complete his assignment... or rather, I didn't have time. Let him forgive me...";
				link.l1 = RandPhraseSimple("Is that all?! Okay, I'll do it. Uh, my dear...","Okay, I'll tell him if I find the time. Uh, dear...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "I don't think I'm going to do this kind of nonsense. And let's finish what we started with dignity.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation Galleon"
			{
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "Tell captain of patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")) + " '" + pchar.GenQuest.CaptainComission.ShipTypeName + "' " + pchar.GenQuest.CaptainComission.Name + ", that he can't appear in " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc") + "... " +
							"The Governor learned of " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Gen")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "' death ... you need to hurry, or he'll be arrested... " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))) + " is sailing to " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc") + " from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + " and about 15 days will arrive... find him before it happens...";
				link.l1 = RandPhraseSimple("I promise nothing, but I will tell him if necessary. Uh, my dear... ","Okay, I'll tell him if I have time. Uh, dear...");
				link.l1.go = "CaptainComission_300";
			}
		break;

		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar);
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();
		break;

		case "CaptainComission_22_2":
			dialog.text = "What cruelty! I hope it will count for you in the next world.";
			link.l1 = "And not only that..";
			link.l1.go = "CaptainComission_22_3";
		break;

		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterReputation(pchar, -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("I'm listening to you, " + GetAddress_Form(pchar) + ".","What did you want?","What can I do for you?");
			link.l1 = "You " + pchar.GenQuest.CaptainComission.Name + "? I have an errand for you. Captain " + pchar.GenQuest.CaptainComission.CapName + " asked me to give you important information.";
			link.l1.go = "CaptainComission_4";
		break;

		case "CaptainComission_4":
			dialog.text = "Yes? Well, let's talk. So what did the captain " + pchar.GenQuest.CaptainComission.CapName + " ask you to do?";
			link.l1 = "He asked me to tell you that he will not be able to complete your assignment.";
			link.l1.go = "CaptainComission_5";
		break;

		case "CaptainComission_5":
			dialog.text = "What are you saying?! I've known him for a long time, he's an honest man-he couldn't do that!";
			link.l1 = "Let's just say that circumstances prevented him. In other words, he died.";
			link.l1.go = "CaptainComission_6";
		break;

		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "Oh, how inappropriate it all is! So much time has been lost..."
					+ "Captain, in that case, I have to ask for your help. Pirates from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Gen") + " captured my " + GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")) + " " + pchar.GenQuest.CaptainComission.SlaveName + " and demand a ransom for it. Would you be willing to take on this mission? The reward will be generous.";
				link.l1 = "Unfortunately, I have other plans.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "I will try to help you if you explain the essence of the matter in more detail.";
				link.l2.go = "CaptainComission_6_2";
			}
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "Oh, how inappropriate it all is! So much time has been lost...Where are the chests?";
				link.l1 = "Mm... What chests?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}
		break;

		case "CaptainComission_6_1":
			dialog.text = "Very sorry, Captain... It's a pity that you don't want to help me.";
			link.l1 = "It's not about desire, dear. You understand that... Goodbye.";
			link.l1.go = "CaptainComission_6_1End";
		break;

		case "CaptainComission_6_2":
			dialog.text = "Yesterday I received an letter from " + pchar.GenQuest.CaptainComission.PirateName + ", in which he announced that he was raising the ransom amount and threatening to sell the prisoner into slavery. The late captain should have notified " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_ACC) + "that I agree to the previous conditions, and give an advance payment. But now I understand why the pirates raised the stakes.";
			link.l1 = "And what do you suggest?";
			link.l1.go = "CaptainComission_6_21";
		break;

		case "CaptainComission_6_3":
			dialog.text = "Oh, "+ GetSexPhrase("buddy","girlfriend") +"it seems to me that someone has started a dishonest game. I warn you right away - this is dangerous and fraught with trouble. The captain has " + pchar.GenQuest.CaptainComission.CapName + "there were three chests of gold that he had to hand over " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT) + " in " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Voc") + " as a ransom for one person - " + pchar.GenQuest.CaptainComission.SlaveName + ". Since he instructed you to contact us, he couldn't help but mention the chests.";
			link.l1 = "Maybe he just didn't have time?";
			link.l1.go = "CaptainComission_6_31";
		break;

		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("cя","as"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterReputation(pchar, -2);
			DialogExit();
		break;

		case "CaptainComission_6_21":
			dialog.text = "I am left with no choice... The required amount is 150,000 gold, I have already collected. I want to ask you to deliver it to " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + " and bring " + GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")) + " this way. I am ready to pay 40,000 for the service, which you will receive upon your return.";
			link.l1 = "Okay, I'm ready.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "Unfortunately, I have other plans.";
			link.l2.go = "CaptainComission_6_1";
		break;

		case "CaptainComission_6_22":
			dialog.text = "Then keep the money, and God bless you... We just need to hurry - I'm afraid that " + pchar.GenQuest.CaptainComission.PirateName + " won't wait and sell the poor guy into slavery.";
			link.l1 = "Wait for me here. I think it won't take long.";
			link.l1.go = "CaptainComission_6_22End";
		break;

		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName", pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CaptainComission_6_31":
			dialog.text = "Or didn't want to... It doesn't change the case. The people who collected the ransom will not be interested in this. They need a result - alive and unharmed " + pchar.GenQuest.CaptainComission.SlaveName + ". So don't waste any time.";
			link.l1 = "And if I disagree?";
			link.l1.go = "CaptainComission_6_32";
		break;

		case "CaptainComission_6_32":
			dialog.text = "I don't need your consent. I'm just informing you that if you don't deliver a live one to this tavern in thirty days " + pchar.GenQuest.CaptainComission.SlaveName + ", then I will send bounty hunters on your trail...";
			link.l1 = "Hmm, however... And if I deliver it?";
			link.l1.go = "CaptainComission_6_33";
		break;

		case "CaptainComission_6_33":
			dialog.text = "And then we'll talk...";
			link.l1 = "All right... Let's see how it turns out.";
			link.l1.go = "CaptainComission_6_33End";
		break;

		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","la"));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hello, Captain " + GetFullName(pchar) + ". Is there any news?","Well, Captain, have you delivered the ransom yet?","Hello, I hope you brought good news?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "Unfortunately, my plans have changed, I have to break our agreement.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Not yet. I'm doing it.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("Ah, greetings, captain " + GetFullName(pchar) + ". How's it going?","Well, Captain, have you rescued our sufferer?","Glad to see you, Captain, in good health. How is our common cause progressing?");
					link.l1 = "No news yet, but I'm doing it.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Listen, dear, and on what basis do you oblige me to deal with this issue?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hello, Captain " + GetFullName(pchar) + ". Is there any news?","Well, Captain, have you delivered the ransom yet?","Hello, I hope you brought good news?");
					link.l1 = "Yes. Your assignment has been completed, " + pchar.GenQuest.CaptainComission.SlaveName + "I'm on board and getting ready to go ashore.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ah, greetings, captain " + GetFullName(pchar) + ". How's it going?","Well, Captain, have you rescued our sufferer?","Glad to see you, Captain, in good health. How is our common cause progressing?");
					link.l1 = "I'm brought the person you were talking about. I have him on board.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hello, Captain " + GetFullName(pchar) + ". Is there any news?","Well, Captain, have you delivered the ransom yet?","Hello, I hope you brought good news?");
					link.l1 = "Hello, " + pchar.GenQuest.CaptainComission.Name + ", I have to dissapoint you.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ah, greetings, captain " + GetFullName(pchar) + ". How are you doing?","Well, Captain, have you rescued our sufferer?","Glad to see you, Captain, in good health. How is our common cause progressing?");
					link.l1 = "The person you asked for is dead.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;

		case "CaptainComission_30":
			dialog.text = "Thank you, Captain, you have rendered an invaluable service to our whole family. Here is your reward... There are three chests here - that's just 40,000 piastres. I'm sorry, but I'll hurry to meet him.";
			link.l1 = "Of course, of course, happy meeting and all the best.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "I understand your impatience, but circumstances have arisen that have forced me to incur additional expenses.";
				link.l2.go = "CaptainComission_31";
			}
		break;

		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("You got the credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterReputation(pchar, 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You got the credit chests");
			PlaySound("interface\important_item.wav");
			dialog.text = "I don't understand you... We have agreed on the amount of remuneration in advance.";
			link.l1 = "Yes, but instead of 150,000 gold, I had to pay 200,000. And to go to Barbados.";
			link.l1.go = "CaptainComission_31_1";
		break;

		case "CaptainComission_31_1":
			dialog.text = "Captain, this is just the result of your sluggishness. I did not receive any additional conditions from the pirates. What a strange way to try to make dividends out of other people's troubles?!";
			link.l1 = "I see it's useless to explain anything to you...";
			link.l1.go = "CaptainComission_31_1End";
		break;

		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "That's great! And you doubted that we would work together.";
			link.l1 = "But I had to spend a lot on this event.";
			link.l1.go = "CaptainComission_32_1";
		break;

		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "I know, I know... But it's partly your own fault. How could we drown as many as three chests of gold, which we shook out of the treasury with such difficulty, in order to " + NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)) + " I could have gotten this specialist " + pchar.GenQuest.CaptainComission.SlaveSpeciality + "?";
			link.l1 = "Keep in mind that I do not intend to give it to you without decent compensation.";
			link.l1.go = "CaptainComission_32_2";
		break;

		case "CaptainComission_32_2":
			dialog.text = "Well, you're like "+ GetSexPhrase("the man is not stupid","the girl is not stupid") +", you must understand that it is too late to bargain. We could just arrest your ship along with all the junk.However, the compensation was provided in advance... So, on behalf of the government " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + "let me congratulate you on the successful completion of the operation and present you with this valuable gift and a small financial reward.";
			link.l1 = "Hmm-hmm... Thanks for that, too. Take your important specialist.";
			link.l1.go = "CaptainComission_32_2End";
		break;

		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item);
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_7_1":
			dialog.text = "Oh, what a shame! I've already wasted too much time. You've really let me down, Captain!";
			link.l1 = "I understand, but circumstances turned out to be stronger. Here's your money.";
			link.l1.go = "CaptainComission_7_1End";
		break;

		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0;
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterReputation(pchar, -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_7_2":
			dialog.text = "Can't we hurry up? I'm afraid the pirates will change the terms again.";
			link.l1 = "Don't worry, we'll make it in time.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;

		case "CaptainComission_7_3":
			dialog.text = "I hope you understand that time is working against you?";
			link.l1 = "I repeat that I am dealing with your question.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;

		case "CaptainComission_7_4":
			dialog.text = "God forbid! No obligations - only the help of a Puritan on a voluntary basis...There was nothing to mind my own business. You killed captain " + pchar.GenQuest.CaptainComission.CapName + ", blew a ransom of a valuable person, and even our gold was lost. Now clear up the mess. And don't expect to get away with it...";
			link.l1 = "Damn you..";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;

		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Hello, did you want something?";
			link.l1 = "May I see the plantation owner?";
			link.l1.go = "CaptainComission_10_1";
		break;

		case "CaptainComission_10_1":
			dialog.text = "He's away, looking for some kind of runaway slave - either Blade or Blood. And I'm " + npchar.name + " manager here and authorized to resolve all issues in the absence of the owner.";
			link.l1 = "Is that so? It's good... Are the questions about the sale of slaves also within your competence?";
			link.l1.go = "CaptainComission_10_2";
		break;

		case "CaptainComission_10_2":
			dialog.text = "Absolutely. Do you have a big batch?";
			link.l1 = "No, I only want to buy one slave.";
			link.l1.go = "CaptainComission_10_3";
		break;

		case "CaptainComission_10_3":
			dialog.text = "Uh, are you sure you only need one slave?";
			link.l1 = "Yes, I'm sure - his name is " + pchar.GenQuest.CaptainComission.SlaveName + ".";
			link.l1.go = "CaptainComission_10_4";
		break;

		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "Well, you do understand that the cost of one slave will always be higher than the unit price of a slave when buying a large batch?";
				link.l1 = "Well, can I finally hear this price?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Hmm, I suppose you know who you're asking for?";
					link.l1 = "In what sense?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "Ah, this sluggard. I wouldn't give a damn for him. He hasn't done a thing since he was brought in. And why is the colonel spending money on these convicts? Another thing is Negroes - these are workers! Passion for work is in their blood. And believe me, they absolutely don't care what kind of work they do! If you want, send them to the reed, if you want, put them as president...";
					link.l1 = "Hey, my dear, I don't need negroes, I need that lazy guy you were talking about.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;

		case "CaptainComission_11":
			dialog.text = "Of course, of course, here is the price list... Wow!!! 150,000 gold...";
			link.l1 = "However...";
			link.l1.go = "CaptainComission_11_1";
		break;

		case "CaptainComission_11_1":
			dialog.text = "That's what it says in the price list, take a look. I don't understand it myself... The prices for the rest of the slaves are normal, but for some reason the colonel put up a fortune for this one..";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "I think I can guess what's going on here... Here's the money, I'm taking her.";
				link.l1.go = "CaptainComission_14";
			}
			link.l2 = "Hmm... But I'm not freeing a hostage, I'm just buying a slave. Don't you think that for such money you can buy a ship in full combat gear.";
			link.l2.go = "CaptainComission_15";
		break;

		case "CaptainComission_12":
			dialog.text = "This is not a simple slave. Colonel Bishop gave strict orders to keep an eye on him, even put a reinforced guard on him.";
			link.l1 = "So you can't even buy it?";
			link.l1.go = "CaptainComission_12_1";
		break;

		case "CaptainComission_12_1":
			dialog.text = "Why not? The colonel has set a price of 200,000 gold for it, according to the price list.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "Wow! I suppose the colonel knows what kind of man fell into his clutches...";
				link.l1.go = "CaptainComission_16";
			}
			link.l2 = "Hmm... But I'm not freeing a hostage, I'm just buying a slave. Don't you think that for such money you can buy a ship in full combat gear.";
			link.l2.go = "CaptainComission_15";
		break;

		case "CaptainComission_13":
			dialog.text = "Oh yeah, sorry. Bishop left a price list here somewhere. Pag, here. Mm-uh... wow!.. 150000!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "There's probably some mistake here. You must agree that such an amount cannot possibly correspond to the price of one slave. I believe there is an extra zero and the amount should be 15,000. And even that's a lot for such a sluggard.";
				link.l1.go = "CaptainComission_17";
			}
			link.l2 = "Hmm... But I'm not freeing a hostage, I'm just buying a slave. Don't you think that for such money you can buy a ship in full combat gear.";
			link.l2.go = "CaptainComission_15";
		break;

		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "That's good! That's great! They're bringing him in now... Uh, would you like some tea?";
			link.l1 = "No, thanks... Give my regards to Colonel Bishop.";
			link.l1.go = "CaptainComission_14_1";
		break;

		case "CaptainComission_14_1":
			dialog.text = "And from whom, excuse me?";
			link.l1 = "Mm... No, you don't need to. Goodbye.";
			link.l1.go = "CaptainComission_14_1End";
		break;

		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;

		case "CaptainComission_15":
			dialog.text = "Alas, unfortunately, I can't do anything... Here is the price list...";
			link.l1 = "What are you talking about - price list, price list... You can't take a step without Bishop. Tell him... However, you don't need anything.";
			link.l1.go = "CaptainComission_15_1";
		break;

		case "CaptainComission_15_1":
			dialog.text = "So you won't buy this slave?";
			link.l1 = "No. Goodbye.";
			link.l1.go = "CaptainComission_15_1End";
		break;

		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;

		case "CaptainComission_16":
			dialog.text = "I don't know anything about this. I only have clear instructions in case it is sold.";
			link.l1 = "The devil knows what it is... Here's the money. Order the slave to be brought.";
			link.l1.go = "CaptainComission_16_1";
		break;

		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Yes, of course. It will be delivered right away.";
			link.l1 = "Goodbye.";
			link.l1.go = "CaptainComission_16_1End";
		break;

		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;

		case "CaptainComission_17":
			dialog.text = "Ugh, you're probably right. Just a mistake.";
			link.l1 = "Well, since we have decided on the price, can I pick it up?";
			link.l1.go = "CaptainComission_17_1";
		break;

		case "CaptainComission_17_1":
			dialog.text = "Yes, of course. They're bringing him in now.";
			link.l1 = "That's good. Here's your money... Goodbye.";
			link.l1.go = "CaptainComission_17_1End";
		break;

		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;

		case "CaptainComission_18":
			dialog.text = "Maybe a cup of tea, Captain?";
			link.l1 = "No. Thank you.";
			link.l1.go = "exit";
		break;

		case "CaptainComission_19":
			dialog.text = "Have you decided to buy it after all?";
			link.l1 = "No. Goodbye.";
			link.l1.go = "exit";
		break;

		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Hello, Captain. How can I thank you? I can't believe this hell is over.";
				link.l1 = "It's not me you need to thank, but your relative " + pchar.GenQuest.CaptainComission.Name + " from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". He has collected a ransom for you.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Hello captain. I was told that it was you who posted the bail. Thank you, although I understand that you are only a courier.";
				link.l1 = "And you don't look happy with your newly acquired freedom. Is something bothering you?";
				link.l1.go = "CaptainComission_202";
			}
		break;

		case "CaptainComission_201":
			dialog.text = "I beg you very much, if this does not disrupt your plans, please take me to him. I have to thank him.";
			link.l1 = "Of course I will. Come on, I'll take you on board.";
			link.l1.go = "CaptainComission_201_1";
		break;

		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;

		case "CaptainComission_202":
			dialog.text = "To be sure of my freedom, I need to know the names of those who paid for it.";
			link.l1 = "Well, let's say I paid for her, though there wasn't a choice.";
			link.l1.go = "CaptainComission_202_1";
		break;

		case "CaptainComission_202_1":
			dialog.text = "So, my fears are confirmed. Were you forced to do it by " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "?";
			link.l1 = "Yes, this is " + pchar.GenQuest.CaptainComission.Name + " from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ".";
			link.l1.go = "CaptainComission_202_2";
		break;

		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));
			if(iNation == -1) iNation(rand(3));
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			dialog.text = "Clear... I don't know what they promised you, but I offer you a deal: you will take me to the tavern " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + ", where I will be really safe, and I will share with you some of the information I have.";
			link.l1 = "Good. Moreover, they did not promise anything. Follow me, I'll take you to the ship.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "I won't risk getting in trouble for some questionable information.";
			link.l2.go = "CaptainComission_203";
		break;

		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");
			rChar.lifeDay = 0;
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("xia","as"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			DialogExit();
		break;

		case "CaptainComission_203":
			dialog.text = "Unfortunately, I can't open its properties for you now. It could hurt both of us.";
			link.l1 = "Even more so... Follow me and don't try to be weird. Consider yourself under arrest again.";
			link.l1.go = "CaptainComission_203_1";
		break;

		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DialogExit();
		break;

		case "CaptainComission_50":
			dialog.text = "What?! Have the pirates changed the terms again? But I am no longer able to withdraw money from circulation. Soon my whole business will go to waste!";
			link.l1 = "No... Your relative died on the plantations of Barbados in an unsuccessful attempt to escape.";
			link.l1.go = "CaptainComission_51";
		break;

		case "CaptainComission_51":
			ChangeCharacterReputation(pchar, -3);
			dialog.text = "Ah... I'm just crushed... How did this happen?";
			link.l1 = "The pirates, without waiting for a ransom, sold him into slavery. I followed him to Barbados, but I couldn't save him...";
			link.l1.go = "CaptainComission_52";
		break;

		case "CaptainComission_52":
			dialog.text = "My God! What is going on?Good, Captain, thanks for participating... And please return the money you borrowed from me for ransom.";
			link.l1 = "My expenses exceeded all expectations, so I keep your money... Goodbye.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Yes, of course take it... Sorry I couldn't help you... Goodbye.";
				link.l2.go = "CaptainComission_54";
			}
		break;

		case "CaptainComission_53":
			ChangeCharacterReputation(pchar, -5);
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_60":
			dialog.text = "This is bad... you have no idea how bad it is..";
			link.l1 = "I can't help you... I'm even glad that it turned out that way. Goodbye.";
			link.l1.go = "CaptainComission_61";
		break;

		case "CaptainComission_61":
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;

		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "Drink... Captain, bring some water...";
			link.l1 = "Hey, buddy, aren't you " + pchar.GenQuest.CaptainComission.SlaveName + "?";
			link.l1.go = "CaptainComission_71";
		break;

		case "CaptainComission_71":
			dialog.text = "Yes... It's me...";
			link.l1 = "Listen, if you don't want to die here like a flounder in shallow water, I suggest you wake up and listen to me. Do you know where the lighthouse is in Barbados?";
			link.l1.go = "CaptainComission_72";
		break;

		case "CaptainComission_72":
			dialog.text = "I know...";
			link.l1 = "As soon as you have the opportunity, run there. And I will try to organize this opportunity.";
			link.l1.go = "CaptainComission_73";
		break;

		case "CaptainComission_73":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}

			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");

			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Ask, captain, just briefly - I'm on duty.","Speak only on business, I can't be distracted by trifles.");
			link.l1 = RandPhraseSimple("Can you tell me how to find one slave? His name is " + pchar.GenQuest.CaptainComission.SlaveName + ".","Somewhere on the plantation there must be a slave named " + pchar.GenQuest.CaptainComission.SlaveName + ". Can you tell me how I can talk to him?");
			link.l1.go = "CaptainComission_81";
		break;

		case "CaptainComission_81":
			dialog.text = "He has been punished today and is in custody.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "CaptainComission_85":
			dialog.text = "Thank you... Captain, you saved my life...";
			link.l1 = "Run to the lighthouse of Barbados and wait for me there.";
			link.l1.go = "CaptainComission_86";
		break;

		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;

		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Captain, how can I thank you? I can't believe this hell is over.";
				link.l1 = "Your relative has already thanked me " + pchar.GenQuest.CaptainComission.Name + " from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". I'm acting on his behalf.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Thank you, Captain. I don't know on whose behalf you are acting, but bad freedom is always better than good slavery.";
				link.l1 = "What are you talking about?";
				link.l1.go = "CaptainComission_92";
			}
		break;

		case "CaptainComission_91":
			dialog.text = "If it doesn't disrupt your plans, please take me to him. I'm too tired of all this.";
			link.l1 = "Of course I will, if I manage to get out of here alive.";
			link.l1.go = "CaptainComission_91End";
		break;

		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;

		case "CaptainComission_92":
			dialog.text = "May I know the names of the people who paid you for my release?";
			link.l1 = "Well, let's say no one paid me anything... I was simply left with no choice.";
			link.l1.go = "CaptainComission_93";
		break;

		case "CaptainComission_93":
			dialog.text = "So, my fears are confirmed. You were forced to do it " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "?";
			link.l1 = "Yes, this is " + pchar.GenQuest.CaptainComission.Name + " from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ".";
			link.l1.go = "CaptainComission_94";
		break;

		case "CaptainComission_94":
			iNation = FindEnemyNation2Nation(sti(pchar.GenQuest.CaptainComission.Nation));
			if(iNation == -1) iNation(rand(3));
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			dialog.text = "Clear... I don't know what they promised you, but I offer you a deal: you will take me to the tavern " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + ", where I will be really safe, and I will share with you some of the information that I have.";
			link.l1 = "Good. Moreover, they did not promise anything. Follow me, I'll take you to the ship.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "I won't risk getting in trouble for some questionable information.";
			link.l2.go = "CaptainComission_96";
		break;

		case "CaptainComission_95":
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;

		case "CaptainComission_96":
			dialog.text = "Unfortunately, I can't open its properties for you now. It could hurt both of us.";
			link.l1 = "Even more so... Follow me and don't try to be weird. Consider yourself under arrest again.";
			link.l1.go = "CaptainComission_97";
		break;

		case "CaptainComission_97":
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;

		case "CaptainComission_100":
			dialog.text = "Thank you, Captain. Now I'm really safe. I am not offering you money, because I am sure that knowledge and its skillful use are worth much more than this perishable metal.";
			link.l1 = "Waiting for the promised information.";
			link.l1.go = "CaptainComission_101";
		break;

		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "The fact is that I am a scientist, a specialist " + pchar.GenQuest.CaptainComission.SlaveSpeciality + " and " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation)) + "they have been offering me cooperation for a long time, " +
				"but as a military engineer, I remained faithful to the oath. Then they tried to kidnap me. But that was still half the trouble, the real nightmare began when the leaders of the pirates found out about the importance of my person\n"+
				"In the end they managed to kidnap me, but they were hungry for gold, and they didn't need my knowledge. The interested parties, both my allies and opponents, for some reason delayed the ransom, so I ended up on the plantations... Well, then you know.";
			link.l1 = "Yes, woe from wit, you can't say otherwise.";
			link.l1.go = "CaptainComission_102";
		break;

		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "protect the ship and crew during the battle.";
				break;
				case 1:
					sTemp = "quickly load guns and conduct targeted artillery fire in conditions of sea rolling.";
				break;
				case 2:
					sTemp = "handle the sails quickly and maneuver the ship during combat.";
				break;
			}
			dialog.text = "Well, you can put it that way. If you listen to me carefully, you will become a cut above your opponents in the skill " + sTemp;
			link.l1 = "Thank you, the information received is really very useful.";
			link.l1.go = "CaptainComission_103";
		break;

		case "CaptainComission_103":
			dialog.text = "Well, goodbye and thank you for everything.";
			link.l1 = "And thank you. Goodbye and don't get caught again.";
			link.l1.go = "CaptainComission_104";
		break;

		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(drand(1) == 0)
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}
				break;
				case 1:
					if(drand(1) == 0)
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "The Captain's errand"

		// Генератор "Operation Galleon"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc"));
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar);
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();
		break;

		// диалог с кэпом на палубе
		case "CaptainComission_301":
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("Hello, I'm the captain " + GetFullName(NPChar) + ", what brings you to the deck of my ship '" + pchar.GenQuest.CaptainComission.ShipTypeName + "'?","Hello, I am always glad to have guests on board my ship. Captain " + GetFullName(NPChar) + "at your service.");
			link.l1 = "Hello, I am the captain " + GetFullName(pchar) +", acting on behalf of a certain captain " + pchar.GenQuest.CaptainComission.CapName +". He asked me to tell you that in " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc") + " you will be arrested. The authorities became aware of information about some kind of vessel, " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " if I'm not mistaken.";
			link.l1.go = "CaptainComission_302";
		break;

		case "CaptainComission_302":
			dialog.text = "Oh, what a failure! Wait, let me think... where is the captain himself " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "He died.";
			link.l1.go = "CaptainComission_303";
		break;

		case "CaptainComission_303":
			dialog.text = "Damn! It doesn't get any easier from hour to hour... Listen, " + GetFullName(pchar) + ", I'm not ready for this turn of events at all. The captain " + pchar.GenQuest.CaptainComission.CapName + " and I agreed to meet at " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc") + " to load some goods on board. Now it turns out that the captain is dead, and I can't even show up at the settlement to arrange the removal.It seems like I just have no choice but to ask for help from you.";
			link.l1 = "My consent will depend on what kind of help you need.";
			link.l1.go = "CaptainComission_304";
		break;

		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Help me with people and boats to get the cargo out of " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen") + ", and in return you will take everything that does not enter my hold.";
			link.l1 = "Hmm, it looks like you took too big a bite and now you can't swallow it.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "Unfortunately, circumstances do not allow me to spend time on this.";
			link.l2.go = "CaptainComission_306";
		break;

		case "CaptainComission_305":
			string sTempAcc = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc"));
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));//здесь нужен винительный падеж? его нет в коммон ини пока что
			dialog.text = "Well, so as not to lead you by the nose, I'll tell you everything in order " +
				"During one of the patrol raids, I met a ship sailing under the flag of " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". The order to drift was ignored. " +
				"When, after a short chase, we overtook " + sTemp + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "', the fugitives raised the pirate flag. Since it was already far from the fort, I had to take the fight alone. We were damaged by the bulkhead, so we could not avoid boarding\n" +
				"We were already preparing for death, but thanks to the Blessed Virgin Mary and a platoon of musketeers, we managed to kill the pirates. What was our glee when it was discovered that the hold of " + sTempAcc + " was stuffed to the brim with " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Abl")) + ".\n" +
				"We decided that this was a Sign from God and a worthy compensation for our wounds and the death of our comrades...\nBy that time, dusk had already fallen. We brought the " + sTemp +" into the nearest bay, the contents of the hold were taken ashore and safely hidden, and the " + sTemp + " was driven away into the sea and blown up. The next morning, I reported to the service about the sinking of a pirate ship, but did not mention a word about the contents of the hold.";
			link.l1 = "But it seems that someone still blabbed...";
			link.l1.go = "CaptainComission_307";
		break;

		case "CaptainComission_306":
			dialog.text = "Very sorry, Captain... It's a pity that you don't want to help me.";
			link.l1 = "It's not about desire, dear. You understand that... Goodbye...";
			link.l1.go = "CaptainComission_306End";
		break;

		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;

		case "CaptainComission_307":
			dialog.text = "I don't think these are my people. Most likely, this is the owner of the cargo trying to recoup his failure. So what? Can I count on your help?";
			link.l1 = "Yes, I think I'm interested.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "No, dear. Firstly: I do not know how much goods will be in my hold, and secondly: there is no guarantee that the authorities did not find it and did not take it out, and did not leave an ambush at the cache.";
			link.l2.go = "CaptainComission_309";
		break;

		case "CaptainComission_308":
			dialog.text = "Then let's meet in " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Abl") + " right after midnight, otherwise, in my current position, it's too dangerous to loom on the raid. No matter how the patrol finds us.";
			link.l1 = "Okay, wait for me there.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;

		case "CaptainComission_309":
			dialog.text = "I'm sorry, but you leave me no choice. One " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " it's not enough to take out all the cargo, for which I sacrificed a successful career and risked my life. And your team, unlike you, will probably not mind helping me in return for their share.";
			link.l1 = "And what do you suggest?";
			link.l1.go = "CaptainComission_310";
		break;

		case "CaptainComission_310":
			dialog.text = "I'll take your ship and leave you " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Abl") + ".";
			link.l1 = "It is unlikely that you will succeed. I'll get back on board, even if I have to cut out your entire crew to do it.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "It looks like you're not giving me a choice either. Well, I have to submit to violence...";
			link.l2.go = "CaptainComission_312";
		break;

		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;

		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;

		case "CaptainComission_313":
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Abl"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
			DialogExit();
		break;

		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Captain, we need to hurry. I'm afraid the patrol might find us.";
			link.l1 = "Okay, let's hurry up.";
			link.l1.go = "exit";
		break;

		case "CaptainComission_315":
			dialog.text = "Captain, order all boats to be lowered. We'll have to make more than one trip, and I'm afraid that a patrol may enter the bay.";
			link.l1 = "Don't worry, everything will be at its best. The boats are already approaching the shore.";
			link.l1.go = "CaptainComission_316";
		break;

		case "CaptainComission_316":
			dialog.text = "Oh, damn! And here are the guests...";
			link.l1 = "It's not for nothing that people say - remember a fool, and he will appear...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;

		// диалог с патрулём на берегу
		case "CaptainComission_317":
			dialog.text = "Captain, we are looking for a war criminal " + pchar.GenQuest.CaptainComission.Name + ", who hid a valuable cargo from the authorities. Present your documents.";
			link.l1 = "Officer, what documents? We landed to replenish fresh water supplies.";
			link.l1.go = "CaptainComission_318";
		break;

		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004";
			dialog.text = "But it looks like he is himself. Hand over your weapons and follow me... both of you.";
			link.l1 = "Eh, officer, how are you at a bad time...";
			link.l1.go = "CaptainComission_319";
		break;

		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }

			LAi_group_SetHearRadius("CoastalGuards", 100.0);
			sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
		break;

		case "CaptainComission_320":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "We need to hurry before reinforcements arrive here. The download is already coming to an end, your share is " + pchar.GenQuest.CaptainComission.GoodsQty + " pcs. of " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +".";
			link.l1 = "Great. It's time to leave. It was a pleasure doing business with you.";
			link.l1.go = "CaptainComission_321";
		break;

		case "CaptainComission_321":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "One more request. The authorities will probably organize a chase, could you escort my ship to " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + " which is on " + XI_ConvertString(GetIslandByCityName(sTemp) + "Voc") + "?";
			link.l1 = "No, dear, then it's every man for himself. Goodbye...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Of course I could if the reward is appropriate.";
				link.l2.go = "CaptainComission_323";
			}
		break;

		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1");
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0;
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			AddCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), sti(pchar.GenQuest.CaptainComission.GoodsQty));// меняю на распредление по всей эскадре
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + cRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + cRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			AddCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), sti(pchar.GenQuest.CaptainComission.GoodsQty));// меняю на распредление по всей эскадре

			dialog.text = "It goes without saying. I am ready to pay for an escort " + pchar.GenQuest.CaptainComission.ConvoyMoney + " gold. But on condition that we spend no more than " + pchar.GenQuest.CaptainComission.iDay + " days. It's important.";
			link.l1 = "Deal. Let's leave immediately.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc"));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;

		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Captain, we're wasting time. We may be discovered at any moment.","Captain, time is playing against us. Do not forget that they are looking for me.","Captain, delay is unacceptable. My " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + " is too conspicuous for patrol.");
			link.l1 = LinkRandPhrase("Yes, you're right, we need to hurry...","So get into the boats without unnecessary talk.","That's it... Gather your people. Let's go.");
			link.l1.go = "exit";
		break;

		case "CaptainComission_326_0":
			dialog.text = "Captain, I need to talk to my people.";
			link.l1 = "Permission granted.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false;
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;

		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "Greetings, captain " + pchar.CaptainComission.Name + ". Well, have you brought all the cargo? And where is the captain " + pchar.CaptainComission.CapName + "?";
			link.l1 = pchar.CaptainComission.CapName + " died. I had to use the services of this"+ NPCharSexPhrase(sld, "th gentleman","th lady") +". Let me introduce you, Captain " + pchar.CaptainComission.FullName + ".";
			link.l1.go = "CaptainComission_327";
		break;

		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "A "+ NPCharSexPhrase(sld, "what kind of type is he? He","who is she? She") +"are you aware of our business?";
			link.l1 = "In general terms, yes. But there is a nuance - "+ NPCharSexPhrase(sld, "he is sure","she is sure") +"that half of the cargo belongs to "+ NPCharSexPhrase(sld, "him","her") +". Need to convince "+ NPCharSexPhrase(sld, "him","her") +"that's not quite true.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;

		case "CaptainComission_328":
			dialog.text = "Dear " + GetFullName(pchar) +", you've already heard everything you should have known. We need access to your hold.";
			link.l1 = "Do you think my guys will calmly watch some poor bastards clean their hold?";
			link.l1.go = "CaptainComission_329";
		break;

		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "Also true. A cash amount, say " + pchar.GenQuest.CaptainComission.GoodsSum + " gold, will save us from having to conflict with your team. Please note - this is the cost of half of our goods, so everything is fair... Agree, and no one will get hurt.";
			link.l1 = "And if I refuse?";
			link.l1.go = "CaptainComission_330";
		break;

		case "CaptainComission_330":
			dialog.text = "Then violence cannot be avoided. But you will become the first victim and find peace in this cozy bay, and the crew of your ship simply will not have time to come to your aid... How do you like this prospect?";
			link.l1 = "You leave me no choice. I am forced to take the fight.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "I don't seem to have a choice. Here is your gold.";
				link.l2.go = "CaptainComission_332";
			}
		break;

		case "CaptainComission_331":
			dialog.text = "Well, the solution is worthy "+ GetSexPhrase("noble gentleman","brave lady") +".";
			link.l1 = "Stop philosophizing! Let's get down to business!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;

		case "CaptainComission_332":
			dialog.text = "A reasonable solution. All the best to you.";
			link.l1 = "To make you choke...";
			link.l1.go = "CaptainComission_333";
		break;

		case "CaptainComission_333":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors");
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CaptainComission_340":
			dialog.text = "Captain " + GetFullName(pchar) + ", we're too late. I think you understand that remuneration is out of the question.";
			link.l1 = "Of course I understand. I've already earned a lot thanks to you. Goodbye...";
			link.l1.go = "CaptainComission_341";
		break;

		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0;
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("xia","as"));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_Canoneer":
			dialog.text = "Would you treat an old soldier who suffered in fierce naval battles for the glory of the crown with rum?";
			link.l1 = "Rum to us, innkeeper!..";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;

		case "CaptainComission_Canoneer1":
			dialog.text = "Thank you, " + GetAddress_Form(pchar) + ", that's respected a disabled person who lost his memory...";
			link.l1 = "So lost?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;

		case "CaptainComission_Canoneer2":
			dialog.text = "Clean, state"+ GetSexPhrase("dean","zha") +"Captain, it's like a bummer. I don't remember anything, just a knippel flying straight at my head. Look at the hole he punched in my head. It was probably through her that all the memory flowed out of her head.";
			link.l1 = "Buddy, save your heartwarming stories for the dimwitted housewives. I saw people after a direct hit by buckshot, their memory was blown away along with their head. And you've come up with a whole knippel for yourself... Let's talk about the captain better " + pchar.GenQuest.CaptainComission.Name +".";
			link.l1.go = "CaptainComission_Canoneer3";
		break;

		case "CaptainComission_Canoneer3":
			dialog.text = "Yes, that's me, you need to earn something for a living... And about the captain " + pchar.GenQuest.CaptainComission.Name + " I'm not talking out of hand. If I took 100 coins for every question about him, I would already have as much gold as the governor does not collect from the entire settlement in a year...";
			link.l1 = "Did you try to sell the cargo hidden by the captain?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;

		case "CaptainComission_Canoneer4":
			dialog.text = "What sent a bloodhound again?! I don't remember any captain " + pchar.GenQuest.CaptainComission.Name + "! You were told - shell-shocked, and there is a certificate! What else do you need?!";
			link.l1 = "Okay, okay, don't get excited. The thing is... In general, I was late. Captain " + pchar.GenQuest.CaptainComission.CapName + " asked me to warn you so that " + pchar.GenQuest.CaptainComission.Name + " did not go to this settlement that the authorities became aware of the circumstances of the death " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "', and he will be arrested.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;

		case "CaptainComission_Canoneer5":
			dialog.text = "Ugh. That's what they would say right away, otherwise you're beating around the bush... I asked the captain for this " + pchar.GenQuest.CaptainComission.CapName + " intercept ours " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + " when he returns from the boathouses " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + ". " +
				"He was towed there for repairs after this ill-fated battle... Where did this pirate come from along with his " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Abl")) + "?! So many guys laid down their heads because of him, some in battle, others on the block.";
			link.l1 = "How did you survive?";
			link.l1.go = "CaptainComission_Canoneer6";
		break;

		case "CaptainComission_Canoneer6":
			dialog.text = "By mistake. By his own mistake, he survived - the irony of fate. I am a cord in a hook cell " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + " I cut it short, so the boat didn't have time to go far when the powder exploded. And it was only me who was thrown out by the blast wave, and even concussed by a fragment of the bulwark... The guys didn't find it in the dark, but I really don't remember how I got to the shore.";
			link.l1 = "How did you get out of the inquiry?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;

		case "CaptainComission_Canoneer7":
			dialog.text = "And I said that I was concussed during the boarding, so I don't know about any cargo - I don't know. I also pretended to be an imbecile, because I only recently got back on my feet, just before the arrival of " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + ". Before that, I couldn't move normally, my coordination was disrupted by concussion.";
			link.l1 = "Hey, who blabbed about the cargo anyway?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;

		case "CaptainComission_Canoneer8":
			dialog.text = "The pirates sent a letter to the governor, allegedly from the injured merchant. We decided to take revenge on the captain for his persistence. After all, if it weren't for his stubbornness, we would have " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + " we didn't catch up... Yes, and the captain would still be alive - a troublesome head.";
			link.l1 = "And how did you encounter this pirate?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;

		case "CaptainComission_Canoneer9":
			dialog.text = "Yes, the devil knows... Ordinary patrol, an ordinary vessel sailing under the flag of " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". I don't know what the captain decided to watch him for, but the ship didn't respond to the warning shot, and when we caught up with him, the pirates picked up Black Roger. " +
				"We have already moved far away from the fort, so it was not easy. Then there was a boarding dump... I still don't understand how we managed to gain the upper hand " +
				"Well, when we went down into the hold and saw that it was full " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ", that's where the whole fuss started. The devil himself must have given us this loot... The goods had to be unloaded ashore, and " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + "blow up - the roll was almost to the bulwark, and the rigging was badly damaged...";
			link.l1 = "Aren't you afraid that all your efforts and sacrifices will be in vain if the governor's people find the cache?";
			link.l1.go = "CaptainComission_Canoneer10";
		break;

		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "They won't find it. I blew up the entrance to the cave so that a mosquito wouldn't get through, because I'm the best pyrotechnic in the whole squadron. If anyone finds it, it's only the smugglers, they know every crevice on the island.. " +
				"Listen, I've been puzzling over what to do with this cargo for a long time, especially after the execution of the team. I can neither sell it alone, nor take it out, especially since no one will drive serious cases with a shell-shocked person... I don't want to speculate on the deaths of comrades, but for " + pchar.GenQuest.CaptainComission.Sum + " I am ready to show you the cache, provided that after downloading you will take me to the settlement" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity) + ".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))
			{
				link.l1 = "I agree. Here's the money. Now it's your word.";
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "Damn it! Stay here, I'll get the money now.";
				link.l1.go = "CaptainComission_Canoneer12";
			}
			link.l2 = "You're asking too much, buddy. And I don't have a suitable vessel. Good luck to you and goodbye...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;

		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "That's nice. Meet me after midnight today " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Voc") + ". And make sure that there is a place in your hold for " + pchar.GenQuest.CaptainComission.GoodsQty + " pcs. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ". It's a pity to throw away the hard-won...";
			link.l1 = "I will definitely take care of it. See you at the bay...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;

		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;

		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;

		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"));
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;

		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))
			{
				dialog.text = "Here you are at last. I was already starting to worry. I thought you'd turn me over to the authorities with all your guts.";
				link.l1 = "I'm not crazy yet. Here's the money. Now it's your word.";
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				dialog.text = "So where's the money?";
				link.l1 = "Damn it! Sit here, I'll get it right away.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;

		case "CaptainComission_350":
			dialog.text = "Captain, it looks like we're too late. The smugglers finally got to the hiding place.";
			link.l1 = "I don't intend to miss the prey, even if the devil himself comes for it.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "Damn it! I wash my hands of it, figure it out with your competitors.";
			link.l2.go = "CaptainComission_352";
		break;

		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;

		case "CaptainComission_352":
			DialogExit();
			SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
		break;

		case "CaptainComission_360":
			dialog.text = "Captain, we have a serious event here, you would take your squadron out of harm's way until our ships come to load.";
			link.l1 = "Gentlemen, it looks like you're trying to take something that doesn't belong to you.";
			link.l1.go = "CaptainComission_361";
		break;

		case "CaptainComission_361":
			dialog.text = "Wow! Who are you talking to now?";
			link.l1 = "With you, my dear. The goods that you intend to appropriate has an owner whose interests I currently represent.";
			link.l1.go = "CaptainComission_362";
		break;

		case "CaptainComission_362":
			dialog.text = "Even if you were the messiah of the Lord God himself, we will not allow you to meddle in our affairs! Clear the fairway if life is precious!";
			link.l1 = "Isn't it clear to you that this goods is mine, and I won't leave without it?";
			link.l1.go = "CaptainComission_363";
		break;

		case "CaptainComission_363":
			dialog.text = "Damn you! Then you will stay here forever!..";
			link.l1 = "Let's find out who's staying here!..";
			link.l1.go = "CaptainComission_364";
		break;

		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			}
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors");
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CaptainComission_365":
			dialog.text = "Captain, order us to hurry up, a patrol may come here at any moment. And the smugglers were clearly waiting for the transport to load.";
			link.l1 = "Of course let's hurry up... We quickly load the goods into the holds and leave.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "CaptainComission_366":
			dialog.text = "Thank you captain " + GetFullName(pchar) + ". If it weren't for you, the smugglers would have got our cargo, there wouldn't even be anything to remember the guys who laid down their heads for it...";
			link.l1 = "Thank you for believing me.";
			link.l1.go = "CaptainComission_367";
		break;

		case "CaptainComission_367":
			dialog.text = "I have one little thing that may have kept me alive. I want to give it to you as an amulet. Here you go and goodbye.";
			link.l1 = "Thanks for the gift, I didn't expect it. You would have treated your health before the money ran out.";
			link.l1.go = "CaptainComission_368";
		break;

		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}
			dialog.text = "It looks like I have an appointment today. Are you coming to me?";
			link.l1 = "If you are the captain " + pchar.GenQuest.CaptainComission.Name + ", then to you.";
			link.l1.go = "CaptainComission_371";
		break;

		case "CaptainComission_371":
			dialog.text = "...former captain " + pchar.GenQuest.CaptainComission.Name + "...";
			link.l1 = "I am " + GetFullName(pchar) + ", I have a couple of questions.";
			link.l1.go = "CaptainComission_372";
		break;

		case "CaptainComission_372":
			dialog.text = "Why do you think I will answer them?";
			link.l1 = "Captain " + pchar.GenQuest.CaptainComission.CapName + " asked me to warn you about " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "'... Governor knows everything, " +
				"but I late to meet you in sea, on the way from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + ".";
			link.l1.go = "CaptainComission_373";
		break;

		case "CaptainComission_373":
			dialog.text = "Where is captain " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "He died.";
			link.l1.go = "CaptainComission_374";
		break;

		case "CaptainComission_374":
			dialog.text = "Yeah... So that's what it's all about. Well, now a lot has become clear... So, someone blabbed that we gutted " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + ". " +
				"Sooner or later, the cargo will be found, and then they will hang me. Captain " + pchar.GenQuest.CaptainComission.CapName + " is dead, so there is no one else to wait for help... Except from you... Captain " + GetFullName(pchar) + ", get me out of here and I will thank you generously.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "A report has been received to the governor from the cargo owner. There are impressive figures there.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "But you don't think I'm going to help blindly, do you?";
					link.l1.go = "CaptainComission_375";
				}
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "A report has been received to the governor from the cargo owner. There are impressive figures there.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "There are rumors in the colony that you are associated with smugglers...";
					link.l1.go = "CaptainComission_375";
				}
			}
		break;

		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "I see I have to tell you everything in order so that you don't have any doubts about me " +
				"During one of the patrol raids, I came across a ship sailing under the flag of " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". The order to drift was ignored. " +
				"When, after a short chase, we overtook " + sTemp + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "', the fugitives raised the pirate flag. Since it was already far from the fort, I had to take the fight alone. We were damaged by the bulkhead, so we could not avoid boarding " +
				"We were already preparing for death, but thanks to the Blessed Virgin Mary and a platoon of musketeers, we managed to kill the pirates. What was our glee when it was discovered that the hold of " + sTemp + " was stuffed to the brim with " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Abl")) + ". " +
				"We decided that this was a Sign from God and a worthy compensation for our wounds and the death of our comrades...By that time, dusk had already fallen. We brought the " + sTemp +" into the nearest bay, the contents of the hold were taken ashore and safely hidden, and the " + sTemp + " was driven away into the sea and blown up. The next morning, I reported to the service about the sinking of a pirate ship, but did not mention a word about the contents of the hold.";
			link.l1 = "I think there is no point in you deceiving me... So, I propose a deal - you show me the hiding place, and I will take you to any place in the archipelago that you specify.";
			link.l1.go = "CaptainComission_376";
		break;

		case "CaptainComission_376":
			dialog.text = "Ha ha ha... No, Captain, I will not leave the settlement without my share, even if I have to hang from the gallows.";
			link.l1 = "Okay. You'll get your half.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Hmm... I will not risk my head for your well-being. Goodbye...";
			link.l2.go = "CaptainComission_378";
		break;

		case "CaptainComission_377":
			dialog.text = "That's another matter. Now I'm ready to go to hell in the teeth.First of all, you have to shelter me on board your ship. There I will point out the bay where the cache is located.";
			link.l1 = "Then we act quickly and smoothly: I open the cell, and you follow me. Keep up and keep your mouth shut until we get out of the fort.";
			link.l1.go = "CaptainComission_379";
		break;

		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterReputation(pchar, -5);
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
			{
				chrDisableReloadToLocation = true;
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison";
			DialogExit();
		break;

		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Thank you for saving me. Now we need to go to " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc") + ", there I will indicate the location of the cache. We just need to hurry before the bloodhounds get to him.";
			link.l1 = "Are you sure we can pick up all the goods?";
			link.l1.go = "CaptainComission_381";
		break;

		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Yes, you are right, you need to make sure that there is a place in your holds for " + pchar.GenQuest.CaptainComission.GoodsQty + " pcs. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ". The loot turned out to be solid, and it would be a shame to lose the cargo that came at the cost of so many lives. And they won't give us a second chance to take out the goods.";
			link.l1 = "I will definitely take care of it.";
			link.l1.go = "CaptainComission_382";
		break;

		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Voc"));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;

		case "CaptainComission_383":
			dialog.text = "Captain, we don't need any witnesses. Try to get these people out of the bay.";
			link.l1 = "Okay, let's do it now...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;

		case "CaptainComission_384":
			dialog.text = "Captain, you have chosen the wrong place for exercise. This dock is already occupied.";
			link.l1 = "Gentlemen, I'm here to admire the surroundings. I have a case here.";
			link.l1.go = "CaptainComission_385";
		break;

		case "CaptainComission_385":
			dialog.text = "We're not catching jellyfish here either-turn your squadron around and take it downwind.";
			link.l1 = "I have neither the time nor the desire to persuade you. Either you leave and live happily ever after, or you stay here, but forever.";
			link.l1.go = "CaptainComission_386";
		break;

		case "CaptainComission_386":
			dialog.text = "I see you don't understand the words. Well, then hold on...";
			link.l1 = "That's another conversation...";
			link.l1.go = "CaptainComission_364";
		break;

		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "Here we are. The hiding place is in the niche of that rock over there. The entrance is littered with rocks. In the cache " + pchar.GenQuest.CaptainComission.GoodsQty +" pcs. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +". Have you forgotten that half is mine?";
			link.l1 = "I didn't forget. While my people are loading, let's find out where you and your cargo need to be delivered.";
			link.l1.go = "CaptainComission_388";
			link.l2 = "That's nice. Now tell me, what reason would make me share with you?";
			link.l2.go = "CaptainComission_389";
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Captain " + pchar.GenQuest.CaptainComission.Name + ", I have to upset you. I'm really working on behalf of the governor. And I intends to give him all the cargo you have hidden. And you will have to go back to prison and wait for your fate there.";
				link.l3.go = "CaptainComission_389";
			}
		break;

		case "CaptainComission_388":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			pchar.GenQuest.CaptainComission.iDay  = 20 + cRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			AddCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), sti(pchar.GenQuest.CaptainComission.GoodsQty));//меняю на распределение по эскадре
			dialog.text = "I need to sail to " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + ", which is on the " + XI_ConvertString(GetIslandByCityName(sTemp) + "Voc") + " in " + pchar.GenQuest.CaptainComission.iDay + " days. That's where my people were supposed to prepare the distribution.";
			link.l1 = "Okay. It's time to leave.";
			link.l1.go = "CaptainComission_391";
		break;

		case "CaptainComission_389":
			dialog.text = "Yeah... 'No matter what life teaches us, our hearts believe in miracles...'Write it down, or you'll forget.I did not expect such a turn, but I am always ready for battle. You will have to answer for your treachery.";
			link.l1 = "I am at your service...";
			link.l1.go = "CaptainComission_390";
		break;

		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			AddQuestRecord("CaptainComission2", "26");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"))
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Voc"));
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");
			DialogExit();
		break;

		case "CaptainComission_392":
			dialog.text = "It looks like we're too late... The buyers did not wait, and I have no way to organize the storage and sale of goods alone...";
			link.l1 = "Do you have any specific suggestions in this regard?";
			link.l1.go = "CaptainComission_393";
		break;

		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Captain " + GetFullName(pchar) + ", I'm a little embarrassed to suggest this, but could you give my share in gold? I think, " + pchar.GenQuest.CaptainComission.GoodsPrice + "gold will be a worthy compromise.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Yes, it's a good price. I don't mind. Get your money and goodbye.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "Uh, no, dear, we didn't agree on that. I can't babysit you forever. If you don't want to take the cargo, then I will keep it with a clear conscience. I'll be able to arrange its storage and sale.";
			link.l2.go = "CaptainComission_395";
		break;

		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Wait, Captain. I want to thank you for saving me. I wasn't hoping for anything anymore... Here is a little thing that will be very useful to you in many situations... And now goodbye.";
			link.l1 = "Thank you. I did not expect that. It was a pleasure doing business with you.";
			link.l1.go = "CaptainComission_395";
		break;

		case "CaptainComission_395":
			dialog.text = "I did not expect such a turn from you... It seems like I have no choice but to offer you a duel.";
			link.l1 = "I am at your service...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;

		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("xia","as"));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Voc"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Captain, I need to talk to my people.";
			link.l1 = "Permission granted.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false;
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;

		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "Greetings, captain " + GetFullName(pchar) + ". Well, have you brought all the cargo? And where is the captain " + pchar.CaptainComission.CapName + "?";
			link.l1 =  pchar.CaptainComission.CapName + " died, and I was arrested on denunciation. In general, if captain " + pchar.CaptainComission.FullName + " hadn't helped me, you wouldn't see me or the goods.";
			link.l1.go = "CaptainComission_397";
		break;

		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "A "+ NPCharSexPhrase(sld, "what kind of type is he? He","who is she? She") +"are you aware of our business?";
			link.l1 = "More than. "+ NPCharSexPhrase(sld, "He pulled out","She pulled out") +" of prison, deliver half of the cargo here, I promised the other half as a payment for the trouble.";
			link.l1.go = "CaptainComission_398";
		break;

		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Uh, no, Captain, that's your problem! After all, I immediately suggested taking away " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.CaptainComission.ShipTypeVictim),"Name"))) + " to a secluded place, and you've been grabbing for your career. So I waited until your beloved governor put you in jail " +
				"And your share in this case was far less than half, so it would be at your disposal! And we did not put our heads under buckshot for "+ NPCharSexPhrase(sld, "some dude could","some girl could") +"it's so easy to pocket the whole half!";
			link.l1 = "Listen, boatswain, have you forgotten that " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " was the grotto smashed? Did you forget about the roll all the way to the bulwark, too? Do you even realize that if I hadn't given "+ NPCharSexPhrase(sld, "to this person","to her") +"half, would you rather wait for snow than goods?";
			link.l1.go = "CaptainComission_399";
		break;

		case "CaptainComission_399":
			dialog.text = "You're laying smoothly, but you can't fool me! How do we know that you didn't conspire? Maybe there was no arrest?! Maybe greed made you covet sailor's goods? Or do you think that we have forgotten how to handle our blades?!";
			link.l1 = "I see you've completely lost your head, probably the ringing of the piasters is already in your ears.";
			link.l1.go = "CaptainComission_400";
		break;

		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "Brothers! Look how our captain sang! That's what greed does to people. He sold our share to "+ NPCharSexPhrase(sld, "crook","adventurer") +"!!";
			link.l1 = "Shut your fucking mouth! Or I'll make you shut up forever!..";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;

		case "CaptainComission_401":
			dialog.text = "Sorry, Captain, that you had to witness and participate in this ridiculous scene. It's hard to even believe that just a month ago we were a united team in which everyone was ready to give their lives for a friend.";
			link.l1 = "I admit, even my rich imagination cannot imagine this picture.";
			link.l1.go = "CaptainComission_402";
		break;

		case "CaptainComission_402":
			dialog.text = "Unfortunately, I now have no way to organize the storage and sale of goods alone...";
			link.l1 = "Do you have any specific suggestions in this regard?";
			link.l1.go = "CaptainComission_403";
		break;

		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Captain " + GetFullName(pchar) + ", I'm a little embarrassed to suggest this, but could you give my share in gold? I think, " + pchar.GenQuest.CaptainComission.GoodsPrice + "gold will be a worthy compromise.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Perhaps so. I don't mind. Get your money and goodbye.";
				link.l1.go = "CaptainComission_404";
			}
			link.l2 = "No, this prospect does not suit me. You can pick up the cargo or leave it in the hold, but I won't give you the money.";
			link.l2.go = "CaptainComission_405";
		break;

		case "CaptainComission_404":
			bTemp = false;
			if(drand(1) == 0)
			{
			    NPChar.reputation = 61 + rand(29);
				NPChar.alignment = "good";
			}
			else
			{
			    NPChar.reputation = 10 + rand(29);
				NPChar.alignment = "bad";
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation) >= 50) bTemp = true;
			if (NPChar.alignment == "bad" && sti(pchar.reputation) <= 50) bTemp = true;

			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));

			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Wait, I want to thank you for saving me. I wasn't hoping for anything anymore... Here is a little thing that will be very useful to you in many situations... And now goodbye.";
				link.l1 = "Thank you. I did not expect that. It was a pleasure doing business with you.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Wait... I was thinking that my career was ruined anyway, there was no team left, I was an outcast in my homeland. And you probably need loyal people who can hold a blade in their hands and keep their mouths shut. Take me on the team - you won't regret it.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "I must admit, I've waited so long for you to decide. Of course I take it. I'll meet you on board.";
					link.l1.go = "CaptainComission_407";
				}
				link.l2 = "Hmm... it seems to me that you are too smart a person to serve under someone else. Goodbye...";
				link.l2.go = "CaptainComission_408";
			}
		break;

		case "CaptainComission_405":
			dialog.text = "Yeah, apparently, today is not my day... Captain, let's draw our blades and end it all at once...";
			link.l1 = "I am at your service...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;

		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("xia","as"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_407":
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			npchar.CaptainComission = true;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			SetCharacterRemovable(Npchar, true);
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer";
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;
			DeleteAttribute(NPChar, "LifeDay");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);

			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";

			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Operation Galleon"

		// Квест "meeting at the bay" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "It's none of your business. Tell me what you're sniffing around here right now! Aren't you looking for the person we just detained?!";
				link.l1 = "Human?! Nah...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;

		case "ContraMeetManQuest_Sold_2":
			dialog.text = "And that's good... For you... Otherwise, you should go to jail with him. Now don't get in our way, sailor. And don't you dare distract me anymore!...";
				link.l1 = "Yes, I'd better go...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;

		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрём всех из локации
			break;

		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "Great! We need to go to the smuggler's tavern immediately-I really don't want to stay too long!";
				link.l1 = "I don't see any problems. Let's go...";
				link.l1.go = "ContraMeetManQuest_2";
			break;

		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;

		// Контрики в комнате таверны
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;

		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterReputation(PChar, -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;

		case "ContraMeetManQuest_5":
			dialog.text = "Hehe... It looks like "+ GetSexPhrase("guy","girl") +", you're going to hell with him now... Hey, buddy, let's rip their bellies open!";
				link.l1 = "You dirty pig! Defend yourself!";
				link.l1.go = "ContraMeetManQuest_6";
			break;

		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;

		case "ContraMeetManQuest_7":
			dialog.text = "Thank you again, " + PChar.name + ". Goodbye...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;

		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "Rewards?! Oh, yes, of course... Here, take " + FindRussianMoneyString(iMoney) + " and goodbye...";
				link.l1 = "See you later...";
				link.l1.go = "ContraMeetManQuest_10";
			break;

		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterReputation(PChar, 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;

		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting at the bay"

		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "Heh, and you think we'll believe this nonsense?! Come on, guys, take these two hanged men!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Officer, believe me, you are making a terrible mistake and trying to arrest innocent people. Believe me, I don't know this man at all and, moreover, I don't want to know him."
				+ " I think your commandant will be very unhappy if you arrest two law-abiding citizens...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;

		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Ahem, yes, you're probably right. The commandant will be very unhappy. You know what, let's just forget about this little misunderstanding.";
				link.l1 = "Thank you, Officer, you saved us time. From now on, I ask you to be more careful, because you don't want to lose this high rank - an officer?!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;

		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "No way, I don't want that. Now I'm going to ask you to disperse. I have the honor...";
				link.l1 = "That's how it would be right away!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;

		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;

		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "Excellent. Now you can get lost!";
					link.l1 = "What?! But what about the money? We agreed...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Thanks for the delivery. Now you can try it... Hmm, someone is coming...";
						link.l1 = "What?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдаёт деньги
				{
					dialog.text = "Excellent. Thanks for the delivery. Here, hold " + FindRussianMoneyString(iMoney) ". And remember- smugglers don't forget good people...";
					link.l1 = "I really hope so. Goodbye.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}

			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterReputation(PChar, -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;

		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;

		case "ContraDeliverQuest_NoMon":
			dialog.text = "Listen - you and I didn't agree on anything. The one who negotiated with you is the one who should give you the money.";
				link.l1 = "I have a bad day today, what else can I say?! Okay, goodbye...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear() + "You will answer for this! Prepare to die!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;

		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;

		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "You dared challenge me, "+ GetSexPhrase("puppy","trash") +"? Well, it's worse for you. I'm going to rip your belly open!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;

		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;

		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрём
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику

		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("Five hundred people! And sung-ik! A dead man!.. Ik!", "Pei-ik! The devil will bring you to... ik! to the end.");
						link.l1 = "Uh... yeah. Hello there, mister " + GetFullName(NPChar) + ".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "So what do we have here... Three pieces of canvas and planks for the skin, more bits to replace and cables on the braces...";
							link.l1 = "Hello there, mister " + GetFullName(NPChar) + ". I am captain " + PChar.name + ".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("Get off my ship - I have my hands full without you!", "You got the books, what else do you need?!", "I did as you wanted, what the hell else do you want?!");
							link.l1 = "Don't boil like that, or you'll have a stroke!";
							link.l1.go = "exit";
					}
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("Rum, rum! Give me a rum... ick!", "It's been a while... ick! I didn't get drunk like that...");
					link.l1 = "Yes, the hold is already full, isn't it time to go to the harbor?";
					link.l1.go = "exit";
			}
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;

		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("Sit down, kap-ik-an! What are we going to drink?", "Please come to the table, cap! What will you drink? Ick!");
					link.l1 = "Thank you, but I would prefer a nice conversation with a good person.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;

		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "Do you want to offend-ir? There's not a nice one in the whole tavern. They're all bandits, damn thugs! All of them are extortionists, and that one is the first! The leader. Leader, moray eel down his throat!";
				link.l1 = "Actually, I mean you. And I wanted to talk with you. And who is the leader of the extortionate bandits here, and why would he...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;

		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = ""+ GetSexPhrase("Sir","Miss") +"! What did you say your name was? I respect you! Not a single soul has ever called the old sea wolf pleasant and amiable! Yes, I am for you!.. Yes, I am for you!.. Yes, I'm all for you!.. To the last peso!.. Oh, I forgot... The piastres are over. Even the handlebars ran out. This bastard, the extortionist, has just taken away the last steering wheel, so that the devils in hell can load a mortar with his guts!";
				link.l1 = "Captain... Should I call a doctor? You're not well, you have a fever... You're already seeing some kind of steering wheels...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;

		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "Old Cap may be drunk, but he's still sane. Books and pens were given by the father " + PChar.GenQuest.ChurchQuest_1.ToName + ", I was taking them to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ". And then I went to the local church in the morning, well, I mentioned these pieces of paper. The local padre really wanted to look at them with at least one eye. You know yourself, don't feed this Brethren bread - let me read about their saints and righteous. Well, I sent a cabin boy to the ship to bring my locker with this wealth. While I was waiting, I managed to lose to the nines, they stripped me clean, and even the drinks were unpaid. The innkeeper immediately realized, took the books as collateral, and then I gave him the rolls...";
				link.l1 = "That is, you drank the ones entrusted to you by the priest " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + "manuscripts and scrolls?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;

		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "I know I'm going to burn in hell, because now I can't show my face either to the padre who gave the assignment, or to the one to whom I was carrying these papers, or to the local... Who will pray for my soul? Or maybe I'll be excommunicated from the church? Oh, woe is me... I would like to have a drink...";
				link.l1 = "Well, well, don't get so upset. You acted abominably and ungodly, but I am ready to help you. I will pay your debt to the tavern keeper and buy back these steering wheels... these manuscripts. Moreover, since I know both mentioned priests and heading straight to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ", I will deliver these works safely to the address. Do you agree?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;

		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "Savior! An angel of God... Yes, I disagree. I agree!.. I'll give it with all my hands, I'll give it all... just have another drink...";
				link.l1 = "You've had enough... However, okay. I'll go talk to the innkeeper and order you some rum.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;

		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;

		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...and the sheets! the sheets need to be changed!.. Oh, yes - greetings and all that. Don't be rude, whatever your name is, but I am very busy at the moment, and I would like to explain as quickly as possible the essence of the trifle that brought you on board my ship.";
				link.l1 = "Ahem. Actually, the matter is really trivial. As far as I know, in " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Dat") + " you got it from your father " + PChar.GenQuest.ChurchQuest_1.ToName + " some theological works that undertook to deliver to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + "because we were heading that way.";
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;

		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "I was heading, yes! But that damn storm damn near killed my old boat, and now I'm stuck here for who knows how long! Because these scammers at the docks are trying to patch up the hull with rotten planks from broken tubs that the storm washed ashore, and instead of sails they pull on an old sackcloth on which their great-grandmother died.";
				link.l1 = "Uh... Sir, another time I will be happy to hear your opinion about the great-grandmother of the local dockers, but now I would like to know the fate of the books and manuscripts that you received in " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Dat") + ".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;

		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "Nobody, nobody, do you hear?! No one can accuse me of being too late with the delivery of these damned papers!";
				link.l1 = "God forbid, who would dare?! I just want to save you from unnecessary worry. The fact is that the father is " + PChar.GenQuest.ChurchQuest_1.ToName + "I am very concerned that books and manuscripts will be delivered to their destination in the shortest possible time, and I am just heading straight to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + "...";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;

		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "It seems to me, "+ GetSexPhrase("sir","miss") +", in each port, another spiritual mentor absolves you of your sins. However, it's none of my business. If you and all your mentors are so uncomfortable, take your books and get lost. Fair wind!";
				link.l1 = "Thank you, captain, and I wish you a successful repair.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдаёт
		{
			dialog.text = "Better get rid of unnecessary worry, "+ GetSexPhrase("sir","miss") +", and go to " +  XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ", because I undertook to deliver these papers and I will deliver them, no matter what it costs me, because that scoundrel has not yet been born who dares to claim that the captain " + npchar.name + "he doesn't keep his word!";
				link.l1 = "But, captain, it's not that...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;

		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даём рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","a"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трём судно кэпа
			break;

		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "The fact is that I actually have no business with you. I have an assignment from the Holy Father to take the books to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + " and give them to the Padre there. Where are you? You are not in any way sideways. Have a nice day.";
//				link.l1 = "Well. You are a responsible person, but this is your only pleasant trait. Have a nice day, my ungracious friend.";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "I've been patient long enough, but this donkey stubbornness and arrogance can infuriate even an angel, not to mention me, is sinful. I owe to carry out the instructions of my confessor, and if you do not want to voluntarily give up what does not belong to you, I will have to draw my weapon!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; //
			break;

		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трём судно кэпа
			break;

		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Hush, hush, Captain " + PChar.name + "! It's got you all figured out. It seems to be true, if you do not bring the papers, then you will get it properly from all your spiritual Fathers, and the Heavenly Father will add more. Take your theological jewels and go with God.";
				link.l1 = "I am glad that you not only entered my position, but also remembered my name. I advise you to repeat it three times whenever your bad temper will have a harmful effect on your health.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;

		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даём рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","a"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Dat"));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трём судно кэпа
			break;

		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем

		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Get out of here...", "Don't bother me!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;

		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear() + "But you shouldn't have said that... Now I have to send you to the Lord to atone for my sins!";
			}

			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear() + "But you shouldn't have said that... Now we'll have to send you to the Lord to atone for our sins!";
			}

			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear() + "But you shouldn't have said that... Now we will have to send you to the Lord, to atone for our sins before him!";
			}

				link.l1 = "No way, buddy. Before the Lord, everyone will be responsible for themselves!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;

		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "And you don't swear for nothing, I have a case for you, maybe.";
				link.l1 = "This is news! I have a short conversation with people like you.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;

		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "And I'm not going to have a long conversation with you. I wanted to suggest - maybe buy a couple of trinkets? We'll give it away inexpensively...";
				link.l1 = "Do you think I look like someone who wanna buy a stolen goods?!!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;

		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Take it easy, dear. There are no thieves among us! We got this vase for honest work. Look, it's pure gold, and it's trimmed with pearls. But we don't need it. We want to sell and share the money honestly.";
					link.l1 = "Let's take a closer look... Bah! Why, it's a communion bowl!!! So you are the godless ones who robbed the church in " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "?! So I tracked you down!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}

			dialog.text = "Keep it down hypocrite! We had a little bit of a hard time traveling and decided to sell something. Here, look at this vase: pure gold, and trimmed with pearls. We will give it to a good person inexpensively... Let's say for a thousand coins.";
				link.l1 = "Let's take a closer look... Bah! Why, it's a communion bowl!!! So you are the godless ones who robbed the church in " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "?! So I tracked you down!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;

		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Hey, take it easy on the turns, "+ GetSexPhrase("sir","miss") +"!.. Damn, I told that oaf not to make a fuss ahead of time...";
				link.l1 = "What are you mumbling about?! Choose: either you give up the stolen goods voluntarily, or I call the guards.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;

		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Listen, "+ GetSexPhrase("nice man","girl") +", we don't need a quarrel... Let's settle this quietly. You'll have to believe that we didn't rob the church, and we don't have any money. Yes, we received several piastres and a gold piece for depicting a robbery. That damn cup is the only thing left after we paid off the smugglers...";
				link.l1 = "And you want to say that...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;

		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "The damn priest hired us himself! But why was there a chase to equip?! But now we're even... Take a vase and show it to the saint, then you will see for yourself that he will wriggle like a squid in shallow water!..";
				link.l1 = "Give me the bowl and get out before I change my mind.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "Eat well. But I'm not so gullible. If you want to convince me, convince my blade first.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;

		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}

			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;

			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;

		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear() + "I told these cormorants: hold your raking paws, don't steal anything from the priest except money!";
			}
			else
			{
				dialog.text = RandSwear() + "I told you, insatiable cormorants: hold your raking paws, don't steal anything from the priest except money!";
			}

					link.l1 = "What are you mumbling about?! Choose: either you voluntarily give me the stolen goods, or I call the guards.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "I choose something else - you close your chatty mouth and give me the contents of your purse, and I give you life.";
				link.l1 = "Now I will give you an audience with the God!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "So be it, I will give you money, but only for noble reasons. So that you and your buddies can start an honest life. And they didn't stoop to robbing a church.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Uh... Let's forget our differences and get back to the beginning of the conversation. So how much did you want for this craft?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ate","la"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("","a"));
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаёмся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}

			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","a"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("xia","as"));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "I don't need any extra problems either, " + GetAddress_Form(pchar) + ", but now the prices have increased. For this priceless vase, I'll take everything you have.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "You greedy scum!.. I have only" + FindRussianMoneyString(iMoney) + " with me. Take it and get lost!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "And here you missed, you greedy rat - you won't be able to profit at my expense!"+ GetSexPhrase("I am a free wind, today I am here, tomorrow I am there, today I am poor, tomorrow I am rich...","") +"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даём чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}

			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","a"));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "Do you really want to say that it is today that "+ GetSexPhrase("you are poor","you have no money") +"?!";
				link.l1 = "Oh yes, my poor greedy friend! To your deep disappointment. And now take my leave, great things are waiting for me.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "Stop! Now we'll check it out, and if you lied, then I'll stick your lying tongue in an anthill!";
				link.l1 = "You will not live after such words!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;

		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a true gentleman, I am honest","I am honest"));
		break;

		case "Greedy":
			dialog.text = "Oh, you found our precious stone here? Please give it back. It won't hurt you, but it will help us support our pants.";
			link.l1 = "Yeah, right now. I was looking for it not to give it to bare-assed people like you.";
			link.l1.go = "Greedy_no";
			link.l2 = "What am I going to tell the usurer? I have contracted to find the stone.";
			link.l2.go = "Greedy_3";
		break;

		case "Greedy_no":
			dialog.text = "You are angry. And I've killed leopards in the past... I should teach you some manners. Defend yourself!";
			link.l1 = "And why does everything have to end in a fight...";
			link.l1.go = "Greedy_end";
		break;

		case "Greedy_3":
			dialog.text = "Give it back. You'll need us again. We're really barely making ends meet, and it won't make your wallet any heavier. This miser, our usurer, is still looking for some.";
			link.l1 = "Okay. Here you go, extortionists. I'll lie if I say that I didn't find him.";
			link.l1.go = "Greedy_4";
			link.l2 = "Perhaps not after all. I won't give you anything!";
			link.l2.go = "Greedy_no";
		break;

		case "Greedy_4":
			if (!CheckAttribute(pchar,"GemGiven")) pchar.GemGiven = 1;
			else pchar.GemGiven = sti(pchar.GemGiven) + 1;
			TakeItemFromCharacter(pchar, "UsurersJew");
			ChangeCharacterReputation(pchar, 3);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			if (sti(pchar.GemGiven)>=5)
			{
				bool ok = (GetCharacterItem(Pchar, "map_part1")>0)  && (GetCharacterItem(Pchar, "map_part2")>0);
				if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
				{

					dialog.text = "Thank you, Captain. We will try to repay your generosity if the opportunity arises. See you later!";
					AddQuestRecord("SeekUsurersJewel", "3");
				}
				else
				{
					if (GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") == 0 && GetCharacterItem(Pchar, "map_full") == 0)
					{
						dialog.text = "Thank you, Captain. We recently found a piece of the map here. It's useless to us, but maybe it will be useful to you. Accept it as a gift.";
						AddQuestRecord("SeekUsurersJewel", "4");
						GiveItem2Character(pchar, "map_part2");
						DeleteAttribute(pchar,"GemGiven");
					}
					if (GetCharacterItem(Pchar, "map_part1") == 0 && GetCharacterItem(Pchar, "map_part2") > 0 && GetCharacterItem(Pchar, "map_full") == 0)
					{
						dialog.text = "Thank you, Captain. We recently found a piece of the map here. It's useless to us, but maybe it will be useful to you. Accept it as a gift.";
						AddQuestRecord("SeekUsurersJewel", "4");
						GiveItem2Character(pchar, "map_part1");
						DeleteAttribute(pchar,"GemGiven");
					}
					if (GetCharacterItem(Pchar, "map_part1") == 0 && GetCharacterItem(Pchar, "map_part2") == 0 && GetCharacterItem(Pchar, "map_full") == 0)
					{
						aref item;
						Items_FindItem("map_full", &item);
						FillMapForTreasure(item);
						GiveItem2Character(pchar, "map_full");
						DeleteAttribute(pchar,"GemGiven");
						AddQuestRecord("SeekUsurersJewel", "5");
						dialog.text = "Thank you, Captain. Accept this item as a gift. We probably won't be able to use it, but maybe you'll need it...";
					}
				}
			}
			else
			{
				AddQuestRecord("SeekUsurersJewel", "3");
				dialog.text = "Thank you, Captain. We will try to repay your generosity if the opportunity arises. See you later!";
			}
			link.l1 = "Come on!";
			link.l1.go = "Greedy_good_end";
		break;

		case "Greedy_end":
			LAi_group_SetRelation("greedybastard", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("greedybastard", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetFightMode(npchar, true);
			for(i = 0; i < sti(npchar.quant); i++)
			{
				sld = CharacterFromID("GreedyBastard_"+pchar.location+"_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			DialogExit();
		break;

		case "Greedy_good_end":
			DialogExit();
			for(i = 0; i < sti(npchar.quant); i++)
			{
				sld = CharacterFromID("GreedyBastard_"+pchar.location+"_"+i);
				sld.lifeDay = 0;
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "OpenTheDoors", -1);
			}
		break;

		// КОНЕЦ

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 8; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_5"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}