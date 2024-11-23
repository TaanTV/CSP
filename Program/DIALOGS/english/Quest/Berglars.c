
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp, sStr, sPlace;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (!CheckAttribute(NPChar,"refreshanim") && NPChar.id != "Ostin") NPChar.refreshanim = "yes";
    if (NPChar.refreshanim == "yes")
    {
        if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) NPChar.model.animation = "man_fast"; //LEO: Превозмогаторам страдать 08.12.2021
        Characters_RefreshModel(NPChar);
        if (bHardBoss) NPChar.AlwaysReload = true;//перезарядка независимо от Дозарядки
        NPChar.refreshanim = "no";
		AddHealingPots(NPChar,true);
    }
	if (Dialog.CurrentNode == "First time")
	{
		switch (pchar.questTemp.tugs.berglarState)
		{
			case "2": Dialog.CurrentNode = "Second time";	break;
			case "3": Dialog.CurrentNode = "Third time";	break;
			case "4": Dialog.CurrentNode = "Fourth time";	break;
			case "5": Dialog.CurrentNode = "Fifth time";	break;
			case "6": Dialog.CurrentNode = "Sixth time";	break;
		}
	}

	switch (Dialog.CurrentNode)
    {
        //------------- первая боевка --------------
		case "First time":
            dialog.text = "Wait, "+ GetSexPhrase("buddy","girlfriend") +"... Be kind, tell me, what's your name?";
            if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = GetFullName(pchar) + " in person. What is it?";
				link.l1.go = "Step1_1";
			}
			link.l2 = "I'm sorry, but I'm not buying or selling anything right now. Goodbye.";
			link.l2.go = "exit";
        break;
 		case "Step1_1":
        	dialog.text = "Yeah, that's what I need...";
    		link.l1 = "I'm listening carefully.";
    		link.l1.go = "Step1_2";
		break;
 		case "Step1_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "under";
			else sStr = "for";
        	dialog.text = "It's good to be careful, because we need to discuss something important... So that's it: I will be waiting for you in the dungeon that is located in the " + sStr + " city.";
    		link.l1 = "Maybe we should go to the tavern and discuss it there? What the hell is going on in the burrows?";
    		link.l1.go = "Step1_3";
		break;
 		case "Step1_3":
        	dialog.text = "No, we don't need extra ears and eyes, trust me...";
    		link.l1 = "Hmm, I don't even know... Is it worth it?";
    		link.l1.go = "Step1_4";
		break;
 		case "Step1_4":
        	dialog.text = "A matter of life and death, "+ GetSexPhrase("buddy","girlfriend") +". Well, I have no time to talk to you here, I'm waiting for you in the dungeon until midnight. If you don't come, as you know...";
    		link.l1 = "That's what I wanted to ask...";
    		link.l1.go = "Step_overAll";
			AddQuestRecord("BerglarsGang", "1");
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
		break;
		//--------------
        case "Fight_1":
            dialog.text = "You're here...";
            link.l1 = "Yes, I came. Tell me quickly, what is your life and death business?";
            link.l1.go = "FirstFight_1";
			PChar.quest.Birglars_Time.over = "yes";
        break;
		case "FirstFight_1":
            dialog.text = "That's right, "+ GetSexPhrase("buddy","girlfriend") +", so it is... Let's clarify the details - the matter of YOUR death.";
            link.l1 = "What are you talking about?";
            link.l1.go = "FirstFight_2";
        break;
		case "FirstFight_2":
            dialog.text = "I hope you confessed recently. Now you will go to the forefathers, it would be nice to have communion, otherwise I'll worry about you...";
            link.l1 = "Heh, I appreciate the concern. Do you even know who I am to talk to me like that?";
            link.l1.go = "FirstFight_3";
        break;
		case "FirstFight_3":
            dialog.text = "Captain, that's it, but I don't need to know more. You are not the first fool that come here, stay here forever. By the way, you're standing right on one of these, he was a good guy. And he was as handsome as Apollo.You understand, I must definitely kill you, otherwise there is no way.";
            link.l1 = "Wow, I would never have thought that a cynical killer could be hiding behind such an appearance...";
            link.l1.go = "FirstFight_4";
		break;
		case "FirstFight_4":
            dialog.text = "Heh, that's the calculation, "+ GetSexPhrase("buddy","girlfriend") +", looks deceptive. I wanted to say, remember for the future, but what kind of future do you have...";
			link.l1 = "I hope it's a happy...";
            link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "2");
        break;
        //------------ вторая боевка ----------------
        case "Second time":
            dialog.text = "Tell me, can I take a minute of your time?";
			if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = "You can.";
				link.l1.go = "Step2_1";
			}
			link.l2 = "I'm sorry, but I'm not buying or selling anything right now. Goodbye.";
			link.l2.go = "exit";
        break;
        case "Step2_1":
            dialog.text = "Your name...";
            link.l1 = GetFullName(pchar) + ". So what?";
            link.l1.go = "Step2_2";
        break;
        case "Step2_2":
            dialog.text = "Then I need you. I have something for you, I need to meet you in a private setting.";
            link.l1 = "Let's go to the tavern, have a cup and discuss everything there.";
            link.l1.go = "Step2_3";
        break;
        case "Step2_3":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "under the";
			else sStr = "near the ";
            dialog.text = "I'm sorry, but I can't do this, and believe me, there is a reason. I can't talk to you for a long time, so I ask you to come to the dungeon, which is located " + sStr + " city.";
            link.l1 = "Heh, that reminds me of something...";
            link.l1.go = "Step_overAll";
			AddQuestRecord("BerglarsGang", "3");
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
        break;
		//----------
        case "Fight_2":
            dialog.text = "I waited...";
            link.l1 = "Yes, as you can see, I'm here. What do you have for me, tell me quickly!";
            link.l1.go = "SecondFight_1";
			PChar.quest.Birglars_Time.over = "yes";
        break;
        case "SecondFight_1":
            dialog.text = "Lay out everything you have and tell me what kind of ship you have, what kind of goods are in the holds...";
            link.l1 = "Why on earth would that be?";
            link.l1.go = "SecondFight_2";
        break;
        case "SecondFight_2":
            dialog.text = "Speak, stupid bitch, otherwise you will lose your head in a moment!";
            link.l1 = "Ugh, some kind of attack! You're the second one who's already trying to kill me like this.";
            link.l1.go = "SecondFight_3";
        break;
        case "SecondFight_3":
            dialog.text = "Hmm, that's how it is, well, now something is clear to me...";
            link.l1 = "And what is clear to you?";
            link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "4");
        break;
        //------------ третья встреча, сумасшедший ----------------
        case "Third time":
            dialog.text = "Beware of optimates, "+ GetSexPhrase("buddy","girlfriend") +"!";
			if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = "What?";
				link.l1.go = "Step3_1";
			}
			link.l2 = "Get out of the way, or I'll call the guards, crazy!";
			link.l2.go = "exit";
        break;
        case "Step3_1":
            dialog.text = "Sullan proscriptions are outright evil! If he only knew what it would do to the empire...";
            link.l1 = "What are you talking about?";
            link.l1.go = "Step3_2";
        break;
        case "Step3_2":
            dialog.text = "How about what? Don't you understand?! n'Beware of a poorly belted youth' - that's what Sulla told the optimates, and he was right! The divine Julius destroyed the remnants of the republic...";
            link.l1 = "Buddy, it looks like you're very sick. So I'm sorry, but I'll go...";
            link.l1.go = "Step3_3";
        break;
        case "Step3_3":
            dialog.text = "Where to?! Where are you going? Evil is at every turn, and you already had misfortune to get to know his icy touch. To be trapped twice and escape death, hee hee hee...";
            link.l1 = "Are you talking about the strange people who invited me into the dungeon and tried to kill me?";
            link.l1.go = "Step3_4";
        break;
        case "Step3_4":
            dialog.text = "That's right, "+ GetSexPhrase("my friend","honey") +", that's right...";
            link.l1 = "Who the hell are they?!";
            link.l1.go = "Step3_5";
        break;
        case "Step3_5":
            dialog.text = "Hee-hee-hee, I won't say...";
            link.l1 = "Tell me, or I'll wring my neck in a flash!";
            link.l1.go = "Step3_6";
        break;
        case "Step3_6":
            dialog.text = "I'm not afraid anymore... I've killed captains too, I've had to do it... Ah, the fear was eating my soul!!!But now it's over, I'm not afraid anymore. And I have to hurry! It is necessary to warn August so that he does not warm up the gallbladder, but on the contrary, makes a cold compress. Then the bile will come out...";
            link.l1 = "What?!";
            link.l1.go = "Step3_7";
        break;
        case "Step3_7":
            dialog.text = "Nothing, it doesn't concern you. This is my business with the Caesars!";
            link.l1 = "Ah, that's understandable...";
            link.l1.go = "Step3_8";
        break;
        case "Step3_8":
            dialog.text = "Well, you look for them. You need to get to Austin before they find out that you killed two. Be careful and sneaky, don't scare them off, otherwise they will disappear!";
            link.l1 = "Austin?";
            link.l1.go = "Step3_9";
			AddQuestRecord("BerglarsGang", "5");
			AddQuestUserData("BerglarsGang", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
        break;
        case "Step3_9":
			sTemp = "berglar" + npchar.city;
			pchar.questTemp.tugs.berglarState = sti(pchar.questTemp.tugs.berglarState) + 1; //счётчик
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
        break;
        //------------ четвёртая встреча ----------------
        case "Fourth time":
            dialog.text = "Hello, " + GetAddress_Form(NPChar) + ".";
			if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = "Hello. To what do I owe the honor?";
				link.l1.go = "Step4_1";
			}
			link.l2 = "I'm sorry, but I'm not buying or selling anything right now. Goodbye.";
			link.l2.go = "exit";
        break;
        case "Step4_1":
            dialog.text = "Listen, I have something for you that will undoubtedly interest you. And at a reasonable price!";
            link.l1 = "Well, I'm always looking for business offers. Tell me what you have there.";
            link.l1.go = "Step4_2";
        break;
        case "Step4_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "under";
			else sStr = "for";
            dialog.text = "Not here, " + GetAddress_Form(NPChar) + ". We don't need extra eyes and ears. I will be waiting for you until midnight in the dungeon, which is located in the " + sStr + " city. Come, you won't regret it!";
            link.l1 = "You know, buddy, you're already the third nondescript guy who invites me to the local catacombs. The last two times ended in big trouble...";
            link.l1.go = "Step4_3";
            link.l2 = "Heh, I will be happy to come to the meeting place, you intrigued me. Is it expensive?";
            link.l2.go = "Step4_5";
        break;
        case "Step4_3":
			pchar.questTemp.OstinDelete = "true";
            dialog.text = "Ah, that's it... I'm sorry, our deal is off.";
            link.l1 = "Really?!";
            link.l1.go = "Step4_4";
        break;
        case "Step4_4":
			sTemp = "berglar" + npchar.city;
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			AddQuestRecord("BerglarsGang", "6");
			AddQuestUserData("BerglarsGang", "sSex", GetSexPhrase("","a"));
			AddDialogExitQuestFunction("Birglars_Time");
			DialogExit();
        break;
        case "Step4_5":
            dialog.text = "Yeah, it's not cheap.";
            link.l1 = "Then I'll grab more money!";
            link.l1.go = "Step4_6";
        break;
        case "Step4_6":
            dialog.text = "Well, I'm looking forward to seeing you, " + GetAddress_Form(NPChar) + ".";
            link.l1 = "See you soon, buddy.";
            link.l1.go = "Step_overAll";
			AddQuestRecord("BerglarsGang", "7");
			AddQuestUserData("BerglarsGang", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
        break;
        case "Fight_4":
            dialog.text = "Ah, finally!";
            link.l1 = "Tell me what you have there.";
            link.l1.go = "Fight4_1";
			PChar.quest.Birglars_Time.over = "yes";
        break;
        case "Fight4_1":
            dialog.text = "Heh, you are here. How much money you bring?";
            link.l1 = "Show your goods first.";
            link.l1.go = "Fight4_2";
        break;
        case "Fight4_2":
			dialog.text = "Yes, there is no goods, you still don't understand?";
            link.l1 = "You don't need much intelligence to understand this. You're the third person in a row who's trying to rob me like this. So tell me, who are you and who is Austin?";
            link.l1.go = "Fight4_3";
        break;
        case "Fight4_3":
            dialog.text = "I did not expect such a turn...";
            link.l1 = "I understand... Well, stop pulling the cat's tail, answer the questions immediately or you'll die!";
            link.l1.go = "Fight4_4";
        break;
        case "Fight4_4":
            dialog.text = "Hmm, I wouldn't be so categorical.";
            link.l1 = "You're running into it, so...";
            link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "8");
        break;
        //------------ пятая встреча ----------------
        case "Fifth time":
            dialog.text = "Hello, " + GetAddress_Form(NPChar) + ". Tell me, aren't you that famous captain, who bring large cargo of copra from the Old World?";
			if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = "No, I don't do transit transportation to the Old World.";
				link.l1.go = "Step5_1";
			}
			link.l2 = "I'm sorry, but I have things to do right now. Goodbye.";
			link.l2.go = "exit";
        break;
        case "Step5_1":
            dialog.text = "Oh, what a pity, what a pity! I wanted to offer to this captain an extremely good deal.";
            link.l1 = "Do you need a copra?";
            link.l1.go = "Step5_2";
        break;
        case "Step5_2":
            dialog.text = "No, not at all! I have a small-sized, but very expensive goods. This is exactly what merchant captains dream of - a minimum of space on the ship and maximum benefits.";
            link.l1 = "And what kind of goods is this? I might be interested in that.";
            link.l1.go = "Step5_3";
        break;
        case "Step5_3":
            dialog.text = "Hmm, Captain, I can't just say that. You understand that safety is above all. I can't lay out all the cards to the first person I meet.";
            link.l1 = "But how can I, or any other captain, assess the feasibility of the transaction if you do not want to talk about the goods?";
            link.l1.go = "Step5_4";
        break;
        case "Step5_4":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "under";
			else sStr = "for";
            dialog.text = "I am ready to discuss everything in full, but not here. I suggest we meet alone in the dungeon, which is located in the " + sStr + " city. It won't take long, but I'll be sure of my own safety.";
            link.l1 = "Heh, I've already been assigned a rendezvous in the dungeons three times. And all three times they tried to kill me there.";
            link.l1.go = "Step5_5";
            link.l2 = "I think this is a fair requirement. In these days, you have to be very careful...";
            link.l2.go = "Step5_7";
        break;
        case "Step5_5":
			pchar.questTemp.OstinDelete = "true";
            dialog.text = "In that case, we have nothing to talk about!";
            link.l1 = "...";
            link.l1.go = "Step5_6";
        break;
        case "Step5_6":
			sTemp = "berglar" + npchar.city;
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			AddQuestRecord("BerglarsGang", "9");
			AddQuestUserData("BerglarsGang", "sSex", GetSexPhrase("","a"));
			AddDialogExitQuestFunction("Birglars_Time");
			DialogExit();
        break;
        case "Step5_7":
            dialog.text = "Well, that's settled. I'll wait for you there until midnight, if you don't come, everything is canceled.";
            link.l1 = "Okay, I got it.";
            link.l1.go = "Step_overAll";
        break;
        case "Fight_5":
            dialog.text = "Well, well, well, excellent!";
            link.l1 = "Show your goods.";
            link.l1.go = "Fight5_1";
			PChar.quest.Birglars_Time.over = "yes";
        break;
        case "Fight5_1":
            dialog.text = "You know, I have some bad news. The goods is gone, but you will have to pay for it.";
            link.l1 = "Hmm, everything is as usual...";
            link.l1.go = "Fight5_2";
        break;
        case "Fight5_2":
            dialog.text = "What are you talking about?";
            link.l1 = "In my memory, you are already the fourth crook who tries to rob me in this way. Is the hunting season open for me?";
            link.l1.go = "Fight5_3";
        break;
        case "Fight5_3":
            dialog.text = "So you killed all of them?! Hmm, a worthy opponent...";
            link.l1 = "Tell me where Austin is and you'll live.";
            link.l1.go = "Fight5_4";
        break;
        case "Fight5_4":
            dialog.text = "If I tell you where Austin is, I'm screwed anyway, the gang doesn't forgive betrayal. This way I have a chance to survive.";
            link.l1 = "You have no chance to survive in a fight with me. Tell me, you'll live longer, at least...";
            link.l1.go = "Fight5_5";
        break;
        case "Fight5_5":
            dialog.text = "I'll try anyway!";
            link.l1 = "Hmm, as you know...";
            link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "11");
        break;
        //------------ шестая встреча ----------------
        case "Sixth time":
            dialog.text = "Greetings " + GetAddress_Form(NPChar) + ". Tell me please, are you " + GetFullName(pchar) + "?";
			if (!CheckAttribute(pchar, "BlockOstin"))
			{
				link.l1 = "Yes, that's my name.";
				link.l1.go = "Step6_1";
			}
			link.l2 = "I'm sorry, but I have things to do right now. Goodbye.";
			link.l2.go = "exit";
        break;
        case "Step6_1":
			dialog.text = "I have a message for you: someone Austin wants to see you.";
            link.l1 = "Hmm, I agree.";
            link.l1.go = "Step6_2";
        break;
        case "Step6_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "under";
			else sStr = "for";
            dialog.text = "Fine. He will be waiting for you until midnight in the dungeon, which is located in the " + sStr + " city.";
            link.l1 = "Everything is as usual... Well, all right.";
            link.l1.go = "Step_overAll";
			AddQuestRecord("BerglarsGang", "12");
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
        break;
        case "Fight_6":
            dialog.text = "Ah, here you are...";
            link.l1 = "Where is Austin?";
            link.l1.go = "Fight6_1";
			PChar.quest.Birglars_Time.over = "yes";
        break;
        case "Fight6_1":
            dialog.text = "He is not here himself, but he sent greetings to you and ordered you to be killed.";
            link.l1 = "Hmm, nothing new. Do you know what happened to those who tried to do it before you?";
            link.l1.go = "Fight6_2";
        break;
        case "Fight6_2":
            dialog.text = "I know, but I think I can do it.";
            link.l1 = "Well, where the fuck is Austin? He's already tired me out, to be honest.";
            link.l1.go = "Fight6_3";
        break;
        case "Fight6_3":
            dialog.text = "He lives in one of the pearl fishing settlements, on the west side of Main.";
            link.l1 = "Well, thanks for the information, I would never have guessed that the leader of a gang of robbers and murderers is hiding so far away.";
            link.l1.go = "Fight6_4";
        break;
        case "Fight6_4":
            dialog.text = "Well, now let's see if you can use this knowledge.";
            link.l1 = "Whatever you say, buddy...";
            link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "13");
        break;
		//------------ общие ноды ----------------
 		case "Step_overAll":
			sTemp = "berglar" + npchar.city;
			LAi_LocationDisableMonGenTimer(pchar.questTemp.tugs.(sTemp), 1); //монстров не генерить 1 день
			LAi_LocationDisableOffGenTimer(pchar.questTemp.tugs.(sTemp), 1); //офицеров не пускать 1 день
			LAi_LocationDisableToughSkeletonTimer(pchar.questTemp.tugs.(sTemp), 1); //ПК не пускать 1 день
			sStr = "Birglars_fight_" + npchar.index;
			pchar.quest.(sStr).win_condition.l1 = "locator";
			pchar.quest.(sStr).win_condition.l1.location = pchar.questTemp.tugs.(sTemp);
			pchar.quest.(sStr).win_condition.l1.locator_group = "item";
			pchar.quest.(sStr).win_condition.l1.locator = "berglar1";
			pchar.quest.(sStr).function = "Birglars_fight";
			pchar.quest.(sStr).city = npchar.city; //запомним город грабителя
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
            NextDiag.CurrentNode = "Fight_" + pchar.questTemp.tugs.berglarState;
			if (npchar.city == "SentJons")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade22"));
			}
			if (npchar.city == "FortFrance")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade31"));
			}
			if (npchar.city == "Marigo")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade34"));
			}
			if (npchar.city == "Panama")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade21"));
			}
			if (npchar.city == "Cartahena")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("topor2"));
			}
			if (npchar.city == "SantaCatalina")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade15"));
			}
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, pchar.questTemp.tugs.(sTemp), "item", "berglar1", "OpenTheDoors", -1.0);
			chrDisableReloadToLocation = true;
			PChar.quest.Birglars_Time.win_condition.l1 = "Timer";
			PChar.quest.Birglars_Time.win_condition.l1.date.hour = 22;
			PChar.quest.Birglars_Time.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.Birglars_Time.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.Birglars_Time.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.Birglars_Time.function = "Birglars_Time";
			//pchar.questTemp.tugs.(sTemp) = "fight";
			DialogExit();
		break;
		case "FirstFight_overAll":
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.tugs.berglarState = sti(pchar.questTemp.tugs.berglarState) + 1; //счётчик
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			SetCharacterPerk(npchar, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			npchar.cirassId           = Items_FindItemIdx("cirass5"); //1.2.3
			sTemp = "berglar" + npchar.city;

			// дадим слухи
			if(sti(pchar.questTemp.tugs.berglarState) == 2)
			{
				AddSimpleRumourCityTip("Oh, we live in difficult times, " + GetAddress_Form(pchar) + ". We had a ship on the raid just now, its captain went ashore, but did not come on board. Only a week later, in caves outside the city, the guards found his corpse... with his throat cut from ear to ear!.. " +
					"During the inquest, the locals replied that they had seen that captain on the way to the cave with some kind of unremarkable at first glance crook. So, we need to keep our eyes open...", npchar.city, 3, 1, "habitue", "");
			}
			if(sti(pchar.questTemp.tugs.berglarState) == 4)
			{
				AddSimpleRumourCityTip("We had a story here -the captain was missing... I got off the ship and I didn't hear a word. They found him a month later, in a cave outside the city. Shot through the head, and not a penny in his pockets! Yes, " + GetAddress_Form(pchar) + ", I tell you, is not evil in any way! Evil spirits do not rummage in their pockets. It's about something else, that's for sure!.. " +
					"I've heard that captains disappeared in St. John's as well, and more than once... Well, let's start...", npchar.city, 3, 1, "habitue", "");
			}

			LAi_SetHP(npchar, stf(pchar.questTemp.tugs.(sTemp).hp), stf(pchar.questTemp.tugs.(sTemp).hp));
			LAi_SetCurHPMax(npchar);
			chrDisableReloadToLocation = true;
			DeleteAttribute(npchar, "city"); //чтобы не ругались с нацией
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (npchar.id == "BerglarFortFrance")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man_fast", 18, PIRATE, 0, true)); //LEO: Превозмогаторам страдать 08.12.2021
				else sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man", 18, PIRATE, 0, true));
				if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
				FantomMakeCoolFighter(sld, 18, 60, 50, BLADE_LONG, "pistol3", 10);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			if (npchar.id == "BerglarPanama")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man_fast", 21, PIRATE, 0, true)); //LEO: Превозмогаторам страдать 08.12.2021
				else sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man", 21, PIRATE, 0, true));
				if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
				FantomMakeCoolFighter(sld, 21, 60, 50, BLADE_LONG, "pistol3", 20);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			if (npchar.id == "BerglarSantaCatalina")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man_fast", 20, PIRATE, 0, true)); //LEO: Превозмогаторам страдать 08.12.2021
				else sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man", 20, PIRATE, 0, true));
				if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
				FantomMakeCoolFighter(sld, 20, 60, 50, BLADE_LONG, "pistol3", 20);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");

			//--> главарь грабителей
			if (sti(pchar.questTemp.tugs.berglarState) > 6)
			{
				pchar.quest.Berglars_Ostin.win_condition.l1 = "location";
				pchar.quest.Berglars_Ostin.win_condition.l1.location = "PearlTown2_House6";
				pchar.quest.Berglars_Ostin.win_condition = "Berglars_Ostin";
				//==> трём базу по квесту
				DeleteAttribute(pchar, "questTemp.tugs");
				//==> ставим счётчик, чтобы не глючило по коду
				pchar.questTemp.tugs.berglarState = 0;
			}
			//<-- главарь грабителей

			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;
        //------------ финальная боевка с Остином ----------------
        case "Final_fight":
            dialog.text = "Greetings to the visitor, this is a rarity in our wilderness. To what do I owe the honor?";
            link.l1 = "Good afternoon, Austin. I wanted to look at you personally, so to speak. And then they send greetings, and everything is in the dungeons...";
            link.l1.go = "StepF1_1";
        break;
        case "StepF1_1":
            dialog.text = "Austin? Few people know my name... Ah, I get it. You are the captain who killed a few of my people - " + GetFullName(pchar) + ", aren't you?";
            link.l1 = "That's right, Austin... Tell me, my friend, what is it that is being done in the world? Assassins are roaming the cities, luring gullible captains and ripping open their guts.";
            link.l1.go = "StepF1_2";
        break;
        case "StepF1_2":
            dialog.text = "I don't believe my ears! Are you trying to shame me? And you tell me this by doing the same?!";
            link.l1 = "What does it mean?!";
            link.l1.go = "StepF1_3";
        break;
        case "StepF1_3":
            dialog.text = "Aren't you chasing merchants across the sea? Don't you kill people by the hundreds? And I want to ask a question, for what? And I will answer it myself - for the sake of money. We are "+ GetSexPhrase("brothers","relatives") +" by the blood of my victims, only I am a land brother.";
            link.l1 = "I don't meanly lure people into holes!";
            link.l1.go = "StepF1_4";
        break;
        case "StepF1_4":
            dialog.text = "Hmm, aren't you raising the flags of other powers, trying to deceive the victim and get closer to her without hindrance?";
            link.l1 = "This is different...";
            link.l1.go = "StepF1_5";
        break;
        case "StepF1_5":
            dialog.text = "It's the same, "+ GetSexPhrase("buddy","girlfriend") +"! Deception, murder, possession of the victim's property. Everything fits together, "+ GetSexPhrase("sea brother","sea sister") +". So I will answer your question at the beginning of our conversation - and nothing extraordinary is happening, everything is as it was, and goes on as usual.";
            link.l1 = "You're laying smoothly...";
            link.l1.go = "StepF1_6";
        break;
        case "StepF1_6":
            dialog.text = "Hmm, maybe so... Tell me why are you here, "+ GetSexPhrase("sea brother","sea sister") +"?";
            link.l1 = "You're great at confusing, but I'm not a fool either. And I'll tell you what, there's a huge difference between us. And it lies in the fact that I give people a choice - to surrender or to accept death. And you don't give a choice, and all your victims are buried in the same place, in the dungeons. So you're not my brother.";
            link.l1.go = "StepF1_7";
        break;
        case "StepF1_7":
            dialog.text = "You here to escalate?";
            link.l1 = "Exactly. I want to finish what I started and rid the Caribbean of scum.";
            link.l1.go = "StepF1_8";
        break;
        case "StepF1_8":
            dialog.text = "Well, it's for the best, I'm pretty tired of you too. Let's get started, bitch!";
            link.l1 = "It's time, perhaps...";
            link.l1.go = "StepF1_9";
        break;
        case "StepF1_9":
			LAi_LocationFightDisable(loadedLocation, false);
			AddQuestRecord("BerglarsGang", "14");
			AddQuestUserData("BerglarsGang", "sSex", GetSexPhrase("","a"));
			CloseQuestHeader("BerglarsGang");
			pchar.questdata.Ostin = 1;
			LAi_group_Delete("EnemyFight");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
   			npchar.cirassId           = Items_FindItemIdx("cirass5"); //1.2.3
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;

 		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
    }
}
