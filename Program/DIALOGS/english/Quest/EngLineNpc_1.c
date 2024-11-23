// Герцог Альбермаль и другие
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;

    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = "Nothing to talk about.";
			link.l1 = "Okay...";
            link.l1.go = "exit";

//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
            //Альбермаль, англ.линейка, квест №1
            if (npchar.id == "Albermal")
            {
                dialog.text = "I'm listening to you carefully.";
                link.l1 = "My name is " + GetFullName(pchar) + ". I got necessary instructions from Governor Madiford.";
                link.l1.go = "Step_E1_1";
            }
            // тюремщик в Кюрасао, квест №4
            if (npchar.id == "Hoverd_Tantum")
            {
    			dialog.text = "What, "+ GetSexPhrase("gotcha, pigeon", "gotcha, pigeon") +"?";
    			link.l1 = "Are you kidding me?";
    			link.l1.go = "Step_E4_1";
            }
            // ==> Губернатор Форт Оранжа,  квест №5
            if (npchar.id == "Orange_Comendant")
            {
    			dialog.text = "Argh... Damn English dogs! I'll have time rip open at least one stomach...";
    			link.l1 = "Try it...";
    			link.l1.go = "Step_E5_1";
            }
            // ==> Квест №6, Моррис Уильямс
            if (npchar.id == "Morris_Willams")
            {
                dialog.text = "Damn the day you entered my deck...";
                link.l1 = "Hmm, you shouldn't do that...";
                link.l1.go = "exit";
            }
            if (pchar.questTemp.State == "MorrisWillams_GoToMorrisBegin" && npchar.id == "Morris_Willams")
            {
    			dialog.text = "Greetings! By what fate on my deck?";
    			link.l1 = "Came to look at the lucky privateer. They say you took three Spanish galleons!";
    			link.l1.go = "Step_E6_20";
            }
            if (pchar.questTemp.State == "MorrisWillams_AfterFirstTalkingWithMorris" && npchar.id == "Morris_Willams")
            {
    			dialog.text = "We've already discussed everything " + pchar.name + ". I'm getting unloaded at Port Royal.";
    			link.l1 = "Very good.";
    			link.l1.go = "exit";
            }
            if (pchar.questTemp.State == "MorrisWillams_ModifordGood5000" && npchar.id == "Morris_Willams")
            {
                LAi_ActorSetSitMode(pchar);
                dialog.text = "Damn it! I obeyed you, went to the port and my cargo was immediately confiscated! You set me up!";
                link.l1 = "What? Who confiscated it?";
                link.l1.go = "Step_E6_2";
            }
            if (pchar.questTemp.State == "MorrisWillams_ModifordPolitic" && npchar.id == "Morris_Willams")
            {
                dialog.text = "Well, what did that rascal in the governor's uniform tell you?";
                link.l1 = "It's hard for me to admit this, but it looks like we've been cheated. Madiford won't give away your goods.";
                link.l1.go = "Step_E6_6";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceNotFound" || pchar.questTemp.State == "MorrisWillams_2PinnaceNotFound")
            {
                dialog.text = "You captured my 'Indigo'?";
                link.l1 = "I sailed behind the pinnace, but couldn't see even his stern, he left me. I'm sorry...";
                link.l1.go = "Step_E6_11";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceBoard" && npchar.id == "Morris_Willams")
            {
                dialog.text = "You captured my 'Indigo'?";
                link.l1 = "I captured off the coast of San Juan the same Spanish pinnace. Only there was no 'Indigo', silver, or mahogany in the holds.";
                link.l1.go = "Step_E6_10";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceBoardNotFoundMoney" && npchar.id == "Morris_Willams")
            {
                dialog.text = "You captured my 'Indigo'?";
                link.l1 = "I captured off the coast of Sang Hoon the same Spanish pinnace. Only there was no 'Indigo', silver, or mahogany in the holds. I searched the whole ship, but nothing value was found, I'm sorry.";
                link.l1.go = "Step_E6_11";
            }
            if (pchar.questTemp.State == "MorrisWillams_DieHard" && npchar.id == "Morris_Willams")
            {
                dialog.text = "You captured my 'Indigo'?";
                link.l1 = "Sorry, but this pinnace turned out to be too much for me. I failed to take him.";
                link.l1.go = "Step_E6_11";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceSink" && npchar.id == "Morris_Willams")
            {
                dialog.text = "You captured my 'Indigo'?";
                link.l1 = "The damn pinnace went down, and with it your whole prize. I did everything I could. I'm sorry.";
                link.l1.go = "Step_E6_11";
            }
			// ==> Квест №12, диалоги с полковником Томасом Линчем
            if (pchar.questTemp.State == "ColonelLinch_GoToKingstown")
            {
                dialog.text = "Who do I have the honor to talk to? Introduce yourself!";
                link.l1 = "I am an English privateer, sir. My name is " + GetFullName(pchar) + ".";
                link.l1.go = "Step_E12_1";
            }

            if (pchar.questTemp.State == "ColonelLinch_ArrestModiford")
            {
                dialog.text = "You have to arrest Madiford. Hurry up.";
                link.l1 = "Okay, sir.";
                link.l1.go = "exit";
            }
        break;

//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Step_E1_1":
            if (GetQuestPastDayParam("questTemp") < 2)
            {
                dialog.text = "Are you and your ship ready for the task?";
                link.l1 = "I'm ready to , we're leaving immediately.";
                link.l1.go = "Go_with_Albermal";
                link.l2 = "Later, I need to restock. The journey will be dangerous.";
                link.l2.go = "exit";
			}
			else
			{
				dialog.text = "You are unreasonably late in completing the assignment given to you! You know I'm limited in time. How long can I wait?";
				link.l1 = "Sir, I'm sorry for the delay, but it was necessary. Now I'm ready, let's go immediately!";
				link.l1.go = "Go_with_Albermal";
				link.l2 = "Sir, I need to do some more preparatory work. I cannot put your life at unnecessary risk due to insufficient preparation of the operation. Please wait a little longer.";
				link.l2.go = "exit";
				ChangeCharacterReputation(pchar, -1);
            }
            NextDiag.TempNode = "Step_E1_1";
        break;

        case "Go_with_Albermal":
            AddQuestRecord("Eng_Line_1_Albermal", "2");
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.quest.fight_withSpanish_Albermal.win_condition.l1          = "location";
			pchar.quest.fight_withSpanish_Albermal.win_condition.l1.location = "Antigua";
			pchar.quest.fight_withSpanish_Albermal.win_condition             = "fight_withSpanish_Albermal";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

        case "in_the_SentJons":
            if (GetQuestPastDayParam("questTemp") < 14)
            {
                dialog.text = "I am grateful to you from the bottom of my heart. You have shown real heroism in the battle against a serious opponent. Besides, we made it to St. John's on time. I am giving you a letter for Sir Thomas Madiford, give this dispatch to him personally. Goodbye!";
                link.l1 = "Have a good trip to England! Goodbye, sir.";
                link.l1.go = "Albermal_go_out";
                pchar.questTemp.State = "Albermal_good_time";
            }
            else
            {
                dialog.text = "I am grateful to you for the heroism shown in the battle with the Spaniards. But because of your slowness, all my plans have collapsed! I'm sending you a letter for Madiford. Go on, I won't keep you any longer.";
                link.l1 = "Best wishes, sir.";
                link.l1.go = "Albermal_go_out";
                ChangeCharacterReputation(pchar, -4);
                pchar.questTemp.State = "Albermal_late";
            }
            GiveItem2Character(pchar, "letter_Albermal");
            NextDiag.TempNode = "in_the_SentJons";
        break;

        case "Albermal_go_out":
            AddQuestRecord("Eng_Line_1_Albermal", "4");
            RemovePassenger(pchar, npchar);
            DialogExit();
            // уходит
            LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload2", "none", "", "", "", 10.0);
            LAi_SetPlayerType(pchar);
    	    NPChar.LifeDay = 1; // уберём нпс на след.день.
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Диалоги тюремщика по четвёртому квесту английки **********************************
 		case "Step_E4_1":
			dialog.text = "No, I'm asking. I want you to be serious. And what happened then? What kind of noise was there in the city because of you?";
			link.l1 = "Your usurer, Josef Noonen de Foncacao, is a decent scoundrel. I had a business proposal for him, but when we didn't agree, he called security and I was arrested, my weapons and money were taken away. Now I am accused of espionage.";
			link.l1.go = "Step_E4_2";
		break;

 		case "Step_E4_2":
			dialog.text = "Hmm, it looks like our Josef... And what kind of business did you offer him?";
			link.l1 = "Buy jewelry and some Spanish junk. I'm a corsair, I didn't want to go to Tortuga, decided to hand over the loot nearby.";
			link.l1.go = "Step_E4_3";
		break;

 		case "Step_E4_3":
			dialog.text = "Heh, against corsair boys"+ GetSexPhrase("", ", and even more so corsair girls") +" I have nothing, I like you guys. However, you can bet that Josef will try to kill you here that very night so that you don't show too much, because he doesn't need connections with corsairs and the fame of a hoarder. He's kind of a respected man in the city.";
			link.l1 = "If you help me get out, I will not remain in debt.";
			link.l1.go = "Step_E4_4";
		break;

 		case "Step_E4_4":
			dialog.text = "I will open your lock on the grate. You can come out as soon as I'm gone. I don't need money, I have my own accounts with Josef...";
			link.l1 = "I understand. Well, thank you.";
			link.l1.go = "Step_E4_5";
		break;

 		case "Step_E4_5":
			dialog.text = "Get out yourself, I'm not your assistant here. By the way, since you don't have a weapon, I'm giving you a saber from the prison arsenal\n"+
                          "Goodbye. I hope Josef will be furious for a long time.";
			link.l1 = "Don't doubt it. Goodbye, friend. Thanks again for the help.";
			link.l1.go = "Step_E4_6";
		break;

 		case "Step_E4_6":
            DoQuestReloadToLocation("Villemstad_prison", "goto", "goto12", "");
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "7");
            ChangeCharacterReputation(pchar, -1);  // за обман.
            GiveItem2Character(pchar, "blade1");   // себельку герою; и этого бы не давал, но без оружия солдеры не нападают.
            EquipCharacterbyItem(pchar, "blade1");
            pchar.questTemp.State = "Intelligence_Curacao_OutPrison";
			pchar.questTemp.jailCanMove = false; //на всякий случай
			//==> делаем солдат поменьше, а то хрен выберешься
			for (int i=1; i<=4; i++)
			{
				sld = characterFromId("VillemstadJailSold_"+i);
				if (sld.location.locator != "soldier3")
				{
					ChangeCharacterAddress(sld, "None", "");
				}
			}
			ChangeCharacterAddress(npchar, "None", "");
			DialogExit();
		break;
//*************************************** Диалог губернатора Форт Оранжа *********************************
        case "Step_E5_1":
            LAi_SetPlayerType(pchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "AttackFortOrange_AfterFightWithCommendant");
            ChangeCharacterHunterScore(pchar, "holhunter", 70);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

//**************************************** Диалоги Морриса Уильямса **************************************
        case "Step_E6_2":
            dialog.text = "Madiford, by his order.";
            link.l1 = "I don't understand anything. Why was it confiscated?";
            link.l1.go = "Step_E6_3";
        break;

        case "Step_E6_3":
            dialog.text = "The cargo was transferred to the Spanish owner.";
            link.l1 = "I don't believe my ears! Are we friends with the Spaniards?";
            link.l1.go = "Step_E6_4";
        break;

        case "Step_E6_4":
            dialog.text = "The devil knows!";
            link.l1 = "I'll figure it out, wait for me here.";
            link.l1.go = "Step_E6_5";
        break;

        case "Step_E6_5":
            AddQuestRecord("Eng_Line_6_MorrisWillams", "4");
            pchar.questTemp.State = "MorrisWillams_ToModifordForCoolTalking";
            NextDiag.CurrentNode = "Willams_waiting";
            DialogExit();
        break;

        case "Willams_waiting": // если ГГ подойдёт в таверне к Уильямсу до проведения разговора с Мэдифордом
            dialog.text = "Well, did you find out anything?";
            link.l1 = "Not yet, but I will definitely deal with this case. Wait and don't leave the tavern.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_waiting";
        break;

        case "Step_E6_6":
            dialog.text = "You just destroyed me. This goods was used to pay off my debts\n"+
                          "As soon as I went ashore at the port, to my great surprise I found out that all my Ious had been bought up by a local usurer. He blocked my access to the sea, and my ship is secured by debt repayment. That's it!";
            link.l1 = "How much do you owe?";
            link.l1.go = "Step_E6_7";
            LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); //открываем выход из города
            LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false);
        break;

        case "Step_E6_7":
            dialog.text = "My debt is one hundred and forty thousand.";
            link.l1 = "You know what, your duty is your problem. Goodbye and be healthy.";
            link.l1.go = "Willams_GoogBye";
            link.l2 = "I have 140000. I'm sorry, because of me you fell into a trap. So take it and solve your problems.";
            link.l2.go = "Willams_GiveMoney";
            link.l3 = "I will return your goods.";
            link.l3.go = "Willams_BackGoods";
        break;

        case "Willams_GoogBye":
            dialog.text = "And good health to you, dear friend (with irony).";
            link.l1 = "May we all be well, amen... Goodbye.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.Waiting_time = "10";
            pchar.questTemp.CurQuestNumber = "7";
            ChangeCharacterReputation(pchar, -100);
            AddCharacterExpToSkill(pchar, "Leadership", -350);
            AddCharacterExpToSkill(pchar, "Accuracy", -50);
            AddCharacterExpToSkill(pchar, "Commerce", -150);
            AddCharacterExpToSkill(pchar, "Sneak ", -150);
            AddCharacterExpToSkill(pchar, "Fencing  ", -100);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "6");
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
            NextDiag.TempNode = "Willams_Fack";
			//слухи
			AddSimpleRumour("Captain, there are rumors that you did not treat poor Williams in the best way...", ENGLAND, 5, 1);
        break;

        case "Willams_Fack":
            dialog.text = "You are an extremely dishonest person, Captain " + GetFullName(pchar) + ". I don't want to talk to you.";
            link.l1 = "As you know, Captain.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_Fack";
			//слухи
			AddSimpleRumour("Morris Williams says such terrible things about you! To listen to him, so you are shaped"+ GetSexPhrase("the scoundrel", "the scoundrel") +"...", ENGLAND, 5, 1);
        break;

        case "Willams_GiveMoney":
            dialog.text = "Wow, you don't have enough money. Well, I'll be waiting here at the tavern while you collect them.";
            link.l1 = "Yes, exactly, I missed it... But never mind, I'll be back soon, you won't have to wait long.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Step_E6_7";
            if (sti(pchar.money) >= 140000)
            {
                dialog.text = "You're honest and noble "+ GetSexPhrase(" man", "girl") +", captain. The laws of the Brethren are not an empty word for you. I will take this money, as I need it badly. Thank you.";
                link.l1 = "No thanks, it was my fault too. As soon as you close your debts, I hope to meet you at sea. Goodbye, friend.";
                link.l1.go = "exit";
                SaveCurrentQuestDateParam("questTemp");
                pchar.questTemp.State = "empty";
                pchar.questTemp.Waiting_time = "5";
                pchar.questTemp.CurQuestNumber = "7";
                ChangeCharacterReputation(pchar, 20);
                AddCharacterExpToSkill(pchar, "Leadership", 150);
                AddCharacterExpToSkill(pchar, "Commerce", 250);
                AddCharacterExpToSkill(pchar, "Sneak ", 50);
                AddCharacterExpToSkill(pchar, "Defence", 150);
                AddQuestRecord("Eng_Line_6_MorrisWillams", "7");
				AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("", "a"));
                CloseQuestHeader("Eng_Line_6_MorrisWillams");
                AddMoneyToCharacter(pchar, -140000);
                NextDiag.TempNode = "Willams_NiceTalking";
				//слухи
				AddSimpleRumour("Captain, they say you helped Williams out a lot by paying off his debt. You are a noble man, Captain, it is an honor for me to talk to you!", ENGLAND, 5, 1);
            }
        break;

        case "Willams_NiceTalking":
            dialog.text = "I am very glad to see my friend! How are you, Captain " + GetFullName(pchar) + "?";
            link.l1 = "It's okay, Morris. I hope you're okay too.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_NiceTalking";
        break;

        case "Willams_BackGoods":
            dialog.text = "I wish I could do this, but I can't, my ship is in port on a dock\n"+
                          "And I wish you good luck. Spaniards should have already taken the confiscated goods. You need to find out which ship they're going to take him out, and then it's a small matter!";
            link.l1 = "Who do you think might know that?";
            link.l1.go = "Step_E6_8";
        break;

        case "Step_E6_8":
            dialog.text = "Your friend Madiford first of all, who else!"+
                          "As it is, I don't know, ask around in a tavern, in a brothel, at the port, or maybe you'll meet the right person on the street.";
            link.l1 = "I'll run to look, time is running out.";
            link.l1.go = "Step_E6_9";
        break;

        case "Step_E6_9":
            dialog.text = "Yeah, hurry up, please. My cargo is mahogany, silver and 'Indigo', I don't care about the rest.";
            link.l1 = "Okay. Wait for me here, I'll handle this case.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_WaitSeek";
            pchar.questTemp.State = "MorrisWillams_SeekSpanishGoods";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "8");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("xia", "as"));
        break;

        case "Willams_WaitSeek":
            dialog.text = "Unearthed anything? When will I receive my shipment?";
            link.l1 = "I'm doing this, wait.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_WaitSeek";
        break;

        case "Step_E6_10":
            dialog.text = "Damn it! And where did my goods go?";
            link.l1 = "I have no idea, maybe the Spaniards unloaded somewhere along the way. I'm sorry.";
            link.l1.go = "MorrisWillams_NotGiveMoney";
            link.l2 = "I guess the Spaniards sold it on the way. In captain's cabin, I found one hundred and forty thousand coins! This is your money, now you can pay off your debts.";
            link.l2.go = "MorrisWillams_GiveMoney";
            NextDiag.TempNode = "Willams_NiceTalking";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "7";
        break;

        case "MorrisWillams_NotGiveMoney":
            dialog.text = "That's it, I'm gone. Well, "+ GetSexPhrase("buddy", "girlfriend") +", thank you, you did everything you could.";
            link.l1 = "Come on, Morris. I wish you to avoid jail.";
            link.l1.go = "MorrisWillams_GoAway";
            pchar.questTemp.Waiting_time = "10";
            ChangeCharacterReputation(pchar, -100);
            AddCharacterExpToSkill(pchar, "Leadership", -150);
            AddCharacterExpToSkill(pchar, "Accuracy", -200);
            AddCharacterExpToSkill(pchar, "Commerce", -250);
            AddCharacterExpToSkill(pchar, "Sneak ", -170);
            AddCharacterExpToSkill(pchar, "Fencing  ", -140);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "13");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("", "a"));
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
			//слухи
			AddSimpleRumour("They say, Captain, that it was your fault that Morris Williams turned out to be penniless...", ENGLAND, 5, 1);
        break;

        case "MorrisWillams_GiveMoney":
        if (sti(pchar.money) >= 140000)
        {
            dialog.text = "You kept your word, thank you! From now on, you are my friend forever. I have nothing to thank you with right now. Truth... there is one thing whose importance in our business cannot be overestimated. You "+ GetSexPhrase("fearless man", "fearless girl") +"and maybe you can do something that my team and I couldn't decide to do.";
            link.l1 = "Hmm, interested. Tell me further what this thing is and what such desperate thugs did not dare to do.";
            link.l1.go = "Step_E6_14";
        }
        else
        {
            dialog.text = "And where is the money? You don't have any!";
            link.l1 = "Damn, I forgot it in cabin. I'm gonna get back to the ship, and you'll have all 140000, don't worry.";
            link.l1.go = "exit";
            NextDiag.TempNode = "MorrisWillams_GiveMoney";
        }
        break;

        case "Step_E6_14":
            dialog.text = "The thing is a cuirass, I don't think there is a second one in the Caribbean. About steel, listen further... "+
                          "Two and a half years ago, my frigate was blown by a storm onto the reefs in the north of the Main, into the Gulf of Doom. Only half of my team came out of this mess alive. The rest remained lying on the shore\n"+
                          "Among those missing that terrible night was my boatswain of that time, the Dutchman Lambert Groff - a man of desperate courage\n"+
                          "That's what he had, in addition to other fine ammunition, and there was that very cuirass, a real work of art and extremely reliable armor. I wanted to return to the ship later, but my surviving thugs tearfully persuaded me not to do so\n"+
                          "And the thing is that after the crash, we somehow got to Cozumel Bay, where we were picked up by a Dutch merchant ship that took us to Tortuga. Upon arrival, five of my crew expressed a desire to leave on a lugger to Cape Katoche, in the bay with our wrecked frigate\n"+
                          "It is understandable - it was necessary to take the remaining jewelry, money. When the first ones did not return, five more pirates set off. But no one else saw them, either one or the other. So I still don't know where these corsairs are or what's wrong with them. But perhaps I really won't go to the wreck of my frigate\n"+
                          "Well, you can try. Maybe my pirates just ran off with the money straight to the Old World or somewhere else. Who knows..\n"+
                          "And the cuirass, damn it, is worth a lot. And it's not about money, but about preserving your own health and life in battle.";
            link.l1 = "Well, thank you, friend. I'll think about it, maybe I'll pay a visit.";
            link.l1.go = "exit";
            pchar.questTemp.Waiting_time = "2";
            ChangeCharacterReputation(pchar, 20);
            AddCharacterExpToSkill(pchar, "Leadership", 250);
            AddCharacterExpToSkill(pchar, "Accuracy", 100);
            AddCharacterExpToSkill(pchar, "Commerce", 250);
            AddCharacterExpToSkill(pchar, "Sneak", 70);
            AddCharacterExpToSkill(pchar, "Fencing", 150);
            AddCharacterExpToSkill(pchar, "Defence", 150);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "14");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("", "a"));
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
            AddMoneyToCharacter(pchar, -140000);
            NextDiag.TempNode = "Willams_NiceTalking";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1 = "location";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1.location = "Shore_ship2";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition = "MorrisWillams_SeekCirassa";
			//слухи
			AddSimpleRumour("Morris Williams is always talking that you are great and honest captain. The characteristic, however, is simply magnificent! I didn't even think that such people still live on earth.", ENGLAND, 5, 1);
        break;

        case "MorrisWillams_GoAway":
			chrDisableReloadToLocation = true;//если провалить квест, то блочится переход чтоб показать как Моррис уходит
            LAi_SetActorType(npchar);
            ChangeCharacterAddressGroup(npchar, "PortRoyal_tavern", "tables", "stay8");
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
            NextDiag.CurrentNode = "First time";
            DialogExit();
        break;

        case "Step_E6_11":
            dialog.text = "Fuck you and your apologies. I'm facing jail, and you're asking for an apology...";
            link.l1 = "Despite the failure with the pinnace, I will still try to help you.";
            link.l1.go = "Step_E6_12";
            link.l2 = "You know, I'm already pretty tired of your rudeness. After all, I don't owe you anything. Goodbye and be well.";
            link.l2.go = "Willams_GoogBye";
        break;

        case "Step_E6_12":
            dialog.text = "Well, I will be grateful for any help. What are you going to do?";
            link.l1 = "I don't know yet. Let's see what happens next, and then we'll make a decision.";
            link.l1.go = "Step_E6_13";
        break;

        case "Step_E6_13":
            dialog.text = "Have it your way. " + pchar.name + " Thank you for not leaving me in trouble. I have to go about my business now, I'll see you later.";
            link.l1 = "Don't worry, everything will be fine.";
            link.l1.go = "MorrisWillams_GoAway";
            pchar.questTemp.State = "MorrisWillams_GoToHimselfBussines"
            Pchar.quest.MorrisWillams_Arrest.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.MorrisWillams_Arrest.win_condition.l1.location = "PortRoyal_tavern";
            Pchar.quest.MorrisWillams_Arrest.win_condition = "MorrisWillams_Arrest";
        break;

        case "Step_E6_20":
			dialog.text = "That's right. I managed to intercept a small squadron consisting of three Spaniards\n"+
                          "My frigate attacked these sanctimonious Catholics, and they took to their heels, instead of jointly opposing me. I boarded the galleons one at a time!";
			link.l1 = "Bled the Spaniards?";
			link.l1.go = "Step_E6_21";
        break;
        case "Step_E6_21":
			dialog.text = "On the contrary, I did not allow my guys to massacre the first galleon. The rest, seeing that their lives were not in danger, surrendered almost without a fight.";
			link.l1 = "Hmm, in Ancient Hellas, the Spartans in battle never pursued an opponent who ran, it was forbidden by law. The opponents of the Lacedaemonians knew that if they threw down their weapons, they would remain alive. Therefore, the enemy, as a rule, surrendered to the Spartans after the first onslaught. You used the same tactics, it gave a good result.";
			link.l1.go = "Step_E6_22";
        break;
        case "Step_E6_22":
			dialog.text = "The reputation of a merciful pirate can quickly make me rich. I've already figured that out, although I didn't know anything about the Spartans\n"+
                          "Okay, tell me, why?";
			link.l1 = "Thomas Madiford gives you permission to dock at Port Royal and sell the prize goods in the island's stores.";
			link.l1.go = "Step_E6_23";
        break;
        case "Step_E6_23":
			dialog.text = "Hmm, I have a French letter of marque, I want to go to Tortuga, I have well-established connections there.";
			link.l1 = "Invitations from the Governor of Jamaica are not thrown around, it's stupid. I advise you to accept it.";
			link.l1.go = "Step_E6_24";
        break;
        case "Step_E6_24":
			dialog.text = "Well, I have less problems: I don't have to drag myself to Tortuga with full holds\n"+
                          "Although I'm losing a little in value, I still agree, I'll go to the port immediately.";
			link.l1 = "Have a nice day, Morris. We'll meet again.";
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_AfterFirstTalkingWithMorris";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "2");
        break;

//**************************************** Диалоги Томаса Линча **************************************
        case "Step_E12_1":
            dialog.text = "I've heard about you. Your services to England are very high.";
            link.l1 = "Thank you, sir.";
            link.l1.go = "Step_E12_2";
        break;

        case "Step_E12_2":
            dialog.text = "My name is Thomas Lynch. I was chairman of the Council of Jamaica until 1664, when I was appointed governor of this rogue Madiford.";
            link.l1 = "Sir, Thomas Madiford is the governor of Jamaica and...";
            link.l1.go = "Step_E12_3";
        break;

        case "Step_E12_3":
            dialog.text = "He is no longer the governor of Jamaica. You should know that the government's patience has run out.\n"+
                          "On his appointment as Governor of Jamaica, Madiford had clear instructions from His Majesty Charles II to curb piracy and maintain friendly relations with Spain.\n"+
                          "Instead of following the instructions he received, Madiford condoned piracy, and his latest 'trick' - the capture and looting of the coast of Main - caused an unprecedented scandal in Europe! Queen Anne of Austria of Spain was in a fit of hysteria for three days.\n";
            link.l1 = "Sir, the Spaniards are to blame for this. They started the fighting by attacking Port Royal.";
            link.l1.go = "Step_E12_4";
        break;

        case "Step_E12_4":
            dialog.text = "And it's hard to blame them for this, because Port Royal is now a haven for bandits and robbers of all stripes\n"+
                          "You must understand that the balance of power in Europe cannot be put at risk in order to stuff robbers' wallets with real money!";
            link.l1 = "What about Tortuga, sir?";
            link.l1.go = "Step_E12_5";
        break;

        case "Step_E12_5":
            dialog.text = "Tortuga is a French colony, and Spain and France are permanently at war. Ha, Louis, if I may say so, cools the ardor of the Papists in Europe\n"+
                          "England cannot afford a serious increase in French influence in the Old World, which is why we have a peace treaty with Spain\n"+
                          "And our 'dear' Sir Thomas Madiford is doing the devil knows what here!!!";
            link.l1 = "Understood, sir.";
            link.l1.go = "Step_E12_6";
        break;

        case "Step_E12_6":
            dialog.text = "Moreover, we have absolutely clear reasons to believe that Madiford is maintaining the status quo in Port Royal for his own selfish interests\n"+
                          "Long story short, he fleeces privateers who are fleecing Spaniards.";
            link.l1 = "Sir, we do pay 10% of the loot to the English treasury.";
            link.l1.go = "Step_E12_7";
        break;

        case "Step_E12_7":
            dialog.text = "Damn no! The British government does not see this money\n"+
                          "We also know that Madiford has a special relationship with reputable pirates and buccaneers. And their joint so-called 'business' brings astronomical profits.";
            link.l1 = "Sir, I have been involved in some of these 'cases', and I can confirm that this is the case.";
            link.l1.go = "Step_E12_8";
        break;

        case "Step_E12_8":
            dialog.text = "I don't even doubt it... Listen, I have a business proposal for you.";
            link.l1 = "Listening carefully, sir.";
            link.l1.go = "Step_E12_9";

        break;

        case "Step_E12_9":
            dialog.text = "The fact is that Madiford is subject to arrest. However, it will not be possible to do this so easily\n"+
                          "For the British garrison in Port Royal, he remains the governor of Jamaica. In fact, we can provoke bloodshed between the British, which I do not intend to allow. In addition, the Port Royal garrison is very strong.\n"+
                          "As far as I know, do you have direct access to Madiford?";
            link.l1 = "Yes, sir.";
            link.l1.go = "Step_E12_10";
        break;

         case "Step_E12_10":
            dialog.text = "Well, very good. I need you to visit Madiford at his residence without making a fuss, accompanied by one or two people. The usual thing\n"+
                          "And when we get to Madiford, we need to make an arrest quietly and without too much noise. I will give you all the necessary powers\n"+
                          "It's clear that this is extremely dangerous.";
            link.l1 = "That's right. And the reward, sir?";
            link.l1.go = "Step_E12_11";
        break;

         case "Step_E12_11":
            dialog.text = "What would you like?";
            link.l1 = "Lately I've been pretty close to Madiford, and I want the condescending attitude of the new English authorities in the Caribbean towards me.";
            link.l1.go = "Step_E12_12";
        break;

         case "Step_E12_12":
            dialog.text = "I have nothing to accuse you of, you acted on the basis of a patent. In case of successful detention of Madiford, I guarantee you not the condescending, but the loyal attitude of the British authorities towards your person.";
			link.l1 = "Great! And the second: I want to get half of the income that Madiford illegally earned.";
            link.l1.go = "Step_E12_13";
        break;

        case "Step_E12_13":
            dialog.text = "Um... You're business person, " + GetFullName(pchar) + ".";
            link.l1 = "Believe me, I rightfully claim this money - my contribution to this piggy bank is very, very solid...";
            link.l1.go = "Step_E12_14";
        break;

        case "Step_E12_14":
            dialog.text = "Uh-oh, damn it... Agreed! Half of the confiscated property is yours. So, I am appointing you as my assistant and giving you an assignment of extreme importance.\n"+
                          "I need you to go immediately to Port Royal and arrest former governor and state criminal Thomas Madiford for trial in London.";
            link.l1 = "It will be, sir.";
            link.l1.go = "exit";
            pchar.questTemp.State = "ColonelLinch_ArrestModiford";
            AddQuestRecord("Eng_Line_12_ColonelLinch", "2");
			AddQuestUserData("Eng_Line_12_ColonelLinch", "sSex", GetSexPhrase("", "а"));
            LAi_SetPlayerType(pchar);
            LAi_SetStayType(npchar);
            NextDiag.TempNode = "YouMustGo";
        break;

        case "YouMustGo":
            dialog.text = "You must arrest Madiford as quickly as possible.";
            link.l1 = "Yes, sir!";
            link.l1.go = "exit";
            NextDiag.TempNode = "YouMustGo";
        break;
    }
}
