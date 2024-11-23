// Генри Морган
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	float locx, locy, locz;
	string sTemp;
	int iTemp;
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat("Do you have a case for me? No? Then leave my residence immediately!",
                         "I seem to have made myself clear.", "Although I have made myself clear, but you keep distracting me!",
                         "So, this already looks like rudeness, it tired me.", "repeat", 20, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I'm already leaving.",
                                               "Yes, Morgan, quite clearly.",
                                               "I'm sorry, Morgan...",
                                               "Oh...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.Sharp == "begin")
			{
				link.l1 = "Morgan, listen, have you heard anything about pearl fishing in the sea? They say they trade with us.";
				link.l1.go = "SharpPearl_1";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", glad to see you! Why did you here?",
                         "Well, what else do you want?", "How long will this last? If you have nothing to do, don't distract others!",
                         "You "+ GetSexPhrase("good caper","good girl") +", so live for now. But I don't want to communicate and talk with you anymore.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes, actually, I just looked in, to check. There is nothing on the case.",
                                               "Nothing, just like that...",
                                               "Okay, Morgan, I'm sorry...",
                                               "Damn it, I finished playing!!!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (pchar.questTemp.Sharp == "begin")
			{
				link.l1 = "Morgan, listen, have you heard anything about pearl fishing in the sea? They say they trade with us.";
				link.l1.go = "SharpPearl_1";
			}
			if (pchar.questTemp.piratesLine == "waiting_Q4" && GetQuestPastDayParam("questTemp.piratesLine") > 5 && pchar.questTemp.Sharp != "toPearl")
			{
				link.l1 = "Listen, Henry, is there a suitable case for me?";
				link.l1.go = "PL_Q4_1";
			}
			if (pchar.questTemp.piratesLine == "waiting_Q8" && GetQuestPastDayParam("questTemp.piratesLine") > 30)
			{
				link.l1 = "Henry, I'm here, as we agreed.";
				link.l1.go = "PL_Q8_1";
			}
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = "Heh, they're fishing, that's right. Only the profits from them are pennies... Look for Sharp, he's our pearl specialist, hehe...";
			link.l1 = "Do you know where to find him?";
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
		break;
		case "SharpPearl_2":
			dialog.text = "I have no idea. In general, this best corsair of all time often hangs out in brothels. Look there...";
			link.l1 = "Understood... Thanks, Morgan.";
			link.l1.go = "exit";
		break;
		//********************* Английская линейка *********************
 		case "EngLine_quests":
			dialog.text = "Do you have business with me?";
			link.l1 = "Sir, Governor General of Jamaica, Sir Thomas Madiford needs your help.";
			link.l1.go = "Step_1_1";
  		break;

 		case "Step_1_1":
			dialog.text = "Who are you?";
			link.l1 = "I am his messenger.";
			link.l1.go = "Step_1_2";
  		break;

 		case "Step_1_2":
			dialog.text = "Hmm, good. And how can I help Sir Thomas Madiford?";
			link.l1 = "You must attack the Dutch city of Curacao.";
			link.l1.go = "Step_1_3";
  		break;

 		case "Step_1_3":
			dialog.text = "I don't think this is possible at the moment. I don't have enough strength for such an operation right now. Give this to Madiford.";
			link.l1 = "Sir Thomas Madiford is counting on you in this case.";
			link.l1.go = "Step_1_4";
  		break;

 		case "Step_1_4":
			dialog.text = "It seems to me that I have made it clear that I cannot perform this operation now. However, if you find me a little later at my house in Jamaica, then perhaps I can offer you a hot case personally. A case for a real corsair. In the meantime, have a nice day.";
			link.l1 = "I will remember your words. I think we'll have a lot to talk about as soon as I'm free. All the best.";
			link.l1.go = "exit";
            AddQuestRecord("Eng_Line_2_Talking", "2");
			AddQuestUserData("Eng_Line_2_Talking", "sSex", GetSexPhrase("","a"));
			AddQuestRecord("Eng_Line_3_Morgan", "1");
			AddQuestUserData("Eng_Line_3_Morgan", "sSex", GetSexPhrase("","a"));

            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")   {pchar.questTemp.State = "after_talks_with_pirates";}
            NextDiag.TempNode = "First time";
  		break;

 		case "hot_business":            // начало диалога по третьему квесту англ.линейки
			dialog.text = "Yeah, did you found time to take a look?";
			link.l1 = "Good afternoon, Henry. I'm here to learn about the 'hot case for a real corsair'. Is it time?";
			link.l1.go = "Step_3_1";
  		break;

	 	case "Step_3_1":
            if (GetQuestPastDayParam("questTemp") < 27 && pchar.questTemp.CurQuestNumber == "3")
            {
    			dialog.text = "Hehe, the time has come even earlier! When you were persuaded to attack Curacao, I have already planned an expedition and started preparing for it. But not in Curacao.";
    			link.l1 = "Why didn't you say so right away?";
    			link.l1.go = "Step_3_2";
            }
            else
            {
    			dialog.text = "Time has already passed. What did you think, I will wait for you forever? Heh... I wanted to offer you a trip to Cumana, but you were shaking somewhere all this time. We did it without you.";
    			link.l1 = "Oh, what a pity...";
    			link.l1.go = "exit";
                AddQuestRecord("Eng_Line_3_Morgan", "8");
				AddQuestUserData("Eng_Line_3_Morgan", "sSex", GetSexPhrase("ate","la"));
				AddQuestUserData("Eng_Line_3_Morgan", "sSex1", GetSexPhrase("","a"));
                CloseQuestHeader("Eng_Line_3_Morgan");
                NextDiag.TempNode = "First time";
                if (pchar.questTemp.CurQuestNumber == "3")
                {
                    SaveCurrentQuestDateParam("questTemp");
                    pchar.questTemp.Waiting_time = "2";
                    pchar.questTemp.CurQuestNumber = "4";
                }
            }
  		break;

	 	case "Step_3_2":
			dialog.text = "Because you were shaking all over the archipelago like crazy, zealously trying to fulfill Madiford's assignment. And I invite only those people who can immediately join my squadron to participate in the case. I don't need any extra chatter. Besides, Madiford's very errand smelled bad.";
			link.l1 = "Explain what the smell is?";
			link.l1.go = "Step_3_3";
  		break;

	 	case "Step_3_3":
			dialog.text = "The fact is that Madiford knows perfectly well that we, as a rule, do not attack the Dutch even at sea, let alone capture settlements. The Dutch are the most active traders, they keep the abundance of goods in the archipelago. If we take them away from trading, we will lose many things that are now sold everywhere. "+
                          "Besides, there are quite a lot of Dutch among the corsairs, this is also a factor. So Madiford gave you an almost impossible task.";
			link.l1 = "Now it's clear. If you don't mind, let's get back to our business. What's the hot case?";
			link.l1.go = "Step_3_4";
  		break;

	 	case "Step_3_4":
			dialog.text = "I want to attack a Spanish city. Are you ready to kill some Spaniards?";
			link.l1 = "Naturally! I'm with you, for an equal share in the loot according to the laws of the Brethren.";
			link.l1.go = "I_want_attack";
			link.l2 = "Damn! As tempting as it sounds, but I have to refuse. The condition of my ship leaves much to be desired, and the crew is on edge after a long trip to the Caribbean. Not this time.";
			link.l2.go = "Step_3_6";
  		break;

	 	case "I_want_attack":    // Идём на испанцев, а может и не идём
            if (GetCompanionQuantity(pchar) == 1)   // Заставляем геймера избавиться от взятых кубиков.
            {
           		dialog.text = "Well, the attacked city is Belize. I was informed that there is now a lot of gold collected there from Spanish gold mines on the American continent. Gold is being prepared for shipment to Europe, we cannot delay. "+
                              "It remains to complete the last preparations for the expedition. Now we need to go to Jackman in Bermudes and John Morris in Port of Spain, on the island of Trinidad. They are ready and waiting for us. We have fifty days to take Belize. "+
                              "And one more important point - if you storm the fort and you are lucky, then know that the crews of our ships will support you during the assault. "+
                              "And now we have to hurry up.";
    			link.l1 = "Go ahead!";
                link.l1.go = "Step_3_7";
            }
            else
            {
                NextDiag.TempNode = "Step_3_4";
               	dialog.text = "There's a whole tail behind you! We are going on a serious business, we don't need the burden of extra ships\n"+
                              "So take care of your readiness for the operation, get rid of unnecessary companions. And don't delay it, otherwise you won't be able to participate in the case.";
    			link.l1 = "I'll do my best.";
    			link.l1.go = "exit";
    			link.l2 = "I don't have the opportunity to change my plans so abruptly. Forcedto refuse the case you are offering.";
    			link.l2.go = "Step_3_6";
             }
  		break;

	 	case "Have_hot_bussines":    // Если геймеру вдруг захочется ещё пообщаться, не знаю, сможет ли. Но на всякий случай.
			dialog.text = "What are we waiting for? Time is precious, we need to perform.";
			link.l1 = "Of course, we will act immediately.";
			link.l1.go = "exit";
            NextDiag.TempNode = "Have_hot_bussines";
  		break;

	 	case "Step_3_6":                   // Отказ от предложения Моргана атаковать испанский город.
			dialog.text = "Well, you don't need to know the money... Ha ha! "+
                          "There will be no such offer from me anymore. Have a nice day.";
			link.l1 = "Come on, Morgan. I'm sorry...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -10);
            AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);

            AddQuestRecord("Eng_Line_3_Morgan", "2");
			AddQuestUserData("Eng_Line_3_Morgan", "sSex", GetSexPhrase("xia","as"));
            CloseQuestHeader("Eng_Line_3_Morgan");
            pchar.questTemp.Waiting_time = "2";       // 2 так, для проформы, чтоб поддержать стандарт
            pchar.questTemp.CurQuestNumber = "4";     // идём на четвёртый квест
            NextDiag.TempNode = "First time";
  		break;

	 	case "Step_3_7":                  // Согласие на участие в нападении на Белиз
			AddQuestRecord("Eng_Line_3_Morgan", "3");
            pchar.nation = PIRATE;
            pchar.questTemp.State = "AttackBeliz_GoOn";
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
            ChangeCharacterAddressGroup(NPChar, "PortRoyal_houseS1", "goto", "goto7");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 8.5, false);
            Fantom_SetBalls(npchar, "pirate");
            npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
            // ==>  Кол-во компаньонов. Нужно для раздела золота независимо от того, кто остался жив, т.е. в обойме компаньонов(по закону берегового братства).
            pchar.questTemp.CompanionQuantity = "2";
            // ==>  Даём соотв. ноду Джекмену
            characters[GetCharacterIndex("Jackman")].dialog.currentnode = "Lets_go_bussines";
            // ==>  Помещаем Джона Морриса в Бриджтаун и даём соотв. ноду
            characters[GetCharacterIndex("John Morris")].dialog.currentnode = "Lets_go_bussines";
            // ==>  Заводим таймер на прерывание, даём 31 дней.
            SetTimerCondition("time_over_Beliz_attack", 0, 0, 51, false);
            SaveCurrentQuestDateParam("questTemp");
            NextDiag.TempNode = "Have_hot_bussines";
            pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
            // ==> капитулянтская нода губернатору Белиза
			characters[GetCharacterIndex("Beliz_Mayor")].dialog.captureNode = "EngLine3Quest_BelizAttack"; //капитулянтская нода мэра
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
  		break;

	 	case "time_over_Beliz":    // Геймер не успел взять Венесуэлу
			dialog.text = "While we were hanging out here, the gold from Belize went to Spain, and without this gold, Belize is not interesting to me. You tore off our plans, we're leaving.";
			link.l1 = "Well, that's your right.";
			link.l1.go = "Step_3_8";
			// выход с палубы
			pchar.quest.Munity = "Deads";
            LAi_LockFightMode(Pchar, false);
        break;

        case "Step_3_8":
			LAi_SetPlayerType(pchar);
            if(IsCompanion(npchar))  {RemoveCharacterCompanion(pchar, npchar);}
            if(IsCompanion(characterFromID("Jackman")))  {RemoveCharacterCompanion(pchar, characterFromID("Jackman"));}
            if(IsCompanion(characterFromID("John Morris")))  {RemoveCharacterCompanion(pchar, characterFromID("John Morris"));}

            QuestToSeaLogin_Prepare(worldMap.playerShipX, worldMap.playerShipZ, worldMap.island);
            if(worldMap.island !=	WDM_NONE_ISLAND)      // если возле острова
            {
                questToSeaLoginer.FromCoast = true;
            }
            else
            {
                questToSeaLoginer.FromCoast = false;
            }
            QuestToSeaLogin_Launch();

            Log_SetStringToLog("The ships of the famous corsairs have withdrawn from the squadron.");
            // ==> Возвращаем на место Моргана
            ChangeCharacterAddressGroup(npchar, "PortRoyal_houseS1", "sit", "sit2");
            LAi_SetHuberType(npchar);
            // ==> Возвращаем на место Джекмена
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))
            {
                LAi_SetHuberType(characterfromID("Jackman"));
				LAi_group_MoveCharacter(characterfromID("Jackman"), "PIRATE_CITIZENS");
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Pirates_townhall", "sit", "sit1");
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "First time";
            }
            // ==> Возвращаем на место Джона Морриса
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
            {
                LAi_SetHuberType(characterfromID("John Morris"));
				LAi_group_MoveCharacter(characterfromID("John Morris"), "ENGLAND_CITIZENS");
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "PortSpein_houseF2", "sit", "sit1");
                characters[GetCharacterIndex("John Morris")].dialog.currentnode = "First time";
            }
            AddMoneyToCharacter(pchar, -50000);
            ChangeCharacterReputation(pchar, -20);
            // нулим опыт в авторитете и удаче
            AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);
            AddCharacterSkill(pchar, SKILL_SNEAK, 0);

            AddQuestRecord("Eng_Line_3_Morgan", "6");
            CloseQuestHeader("Eng_Line_3_Morgan");
            pchar.questTemp.Waiting_time = "2";
            pchar.questTemp.CurQuestNumber = "4";     // идём на четвёртый квест
            DeleteAttribute(pchar, "questTemp.CompanionQuantity");
            DeleteAttribute(pchar, "TempPerks.QuestTroopers");  //снятие перка квестового десанта
			// потом подумаем как дать солдат в помошь...
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
  		break;

	 	case "Gold_found_in_fort":    // Нода разговора в форте Куманы
			dialog.text = "Gold found, as you said, in the fort. We are finishing loading it into the holds. You are brave and a skilled warrior.";
			link.l1 = "Thank you.";
			link.l1.go = "Step_3_9";
        break;

	 	case "Step_3_9":
            if (!IsCompanion(characterFromID("Henry Morgan")))
            {
                dialog.text = "Well, it's time to leave this city. And although I lost my magnificent frigate here, I consider this raid a success. Each of us leaves Belize on our own course. Goodbye and be healthy.";
            }
            else
            {
            	dialog.text = "Well, it's time to leave this city. We have fulfilled what we wanted and are leaving with a good prize. Each of us leaves Belize on our own course. Goodbye and be healthy.";
            }
			link.l1 = "Have a nice day, Morgan.";
			link.l1.go = "Step_3_10";
        break;

	 	case "Step_3_10":
            if (GetCargoMaxSpace(pchar) >= RecalculateCargoLoad(pchar))
            {
                dialog.text = "Wait one more minute. I was thinking: maybe it's very convenient that you don't want to burden yourself with buying and selling? If so, then I'm ready to buy your share of the gold from you. "+
                              "Your share of gold is " + pchar.Ship.Cargo.Goods.gold + " hundredweight. Maybe you'll sell some or even all of it? I'll take 200 coins per unit of weight.";
            }
            else
            {
                dialog.text = "Wait a minute. Look, your ship has sunk below the waterline. You're overloaded, you won't be able to get far from the port. "+
                              "Maximum cargo capacity of your ship " + GetCargoMaxSpace(pchar) + " hundredweight, and in your holds now " + RecalculateCargoLoad(pchar) + "hundredweight "+
                              "You have gold " + pchar.Ship.Cargo.Goods.gold + " hundredweight. Why don't you sell some of it? I'll take 200 coins per unit of weight.";
            }
			link.l1 = "No, Morgan. I will deal with my gold myself. Goodbye.";
			link.l1.go = "out_fort";
			link.l2 = "I really need to sell the surplus.";
			link.l2.go = "Agree_sale_gold";
			link.l3 = "Let me think, I'm not ready to reply yet.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Think_sale_gold";
        break;

	 	case "Think_sale_gold":    // ГГ думает о продаже золота
			dialog.text = "Well, you decided to sell me gold?";
			link.l1 = "Oh, I'm selling...";
			link.l1.go = "Agree_sale_gold";
			link.l2 = "No, Morgan. I'll sell it somewhere else. Goodbye.";
			link.l2.go = "out_fort";
			link.l3 = "I'll think about it a little more...";
			link.l3.go = "exit";
			NextDiag.TempNode = "Think_sale_gold";
        break;

	 	case "Agree_sale_gold":    // ГГ согласен продать золото
			dialog.text = "Okay. How much gold do you want to sell?";
			link.l1 = "I'm ready to sell 25 percent of my share of gold.";
			link.l1.go = "sale_gold_25_persent";
			link.l2 = "I'm ready to sell 50 percent of my share of gold.";
			link.l2.go = "sale_gold_50_persent";
			link.l3 = "I'm ready to sell 75 percent of my gold share.";
			link.l3.go = "sale_gold_75_persent";
			link.l4 = "I'm ready to sell everything.";
			link.l4.go = "sale_gold_all";
			link.l5 = "Sorry Morgan, I changed my mind... Goodbye.";
			link.l5.go = "out_fort";
        break;

	 	case "sale_gold_25_persent":
			dialog.text = "Okay, you sold a quarter of my share. Well, it's a good deal for both of us. Goodbye.";
			link.l1 = "Come on, Morgan. See you later.";
			link.l1.go = "out_fort";
			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty)*0.25));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*0.25*200));
        break;

	 	case "sale_gold_50_persent":
			dialog.text = "Very good, you sold half of my share. Well, it's a good deal for both of us. Goodbye.";
			link.l1 = "Come on, Morgan. See you later.";
			link.l1.go = "out_fort";
   			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty)*0.5));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*0.50*200));
        break;

	 	case "sale_gold_75_persent":
			dialog.text = "Very good, you sold three quarters of its share. Well, it's a good deal for both of us. Goodbye.";
			link.l1 = "Come on, Morgan. See you later.";
			link.l1.go = "out_fort";
   			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty)*0.75));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*0.75*200));
        break;

	 	case "sale_gold_all":
			dialog.text = "Are you selling me everything? That's great! A good deal for both of us. Goodbye.";
			link.l1 = "Come on, Morgan. See you later.";
			link.l1.go = "out_fort";
   			RemoveCharacterGoods(Pchar, GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*200));
        break;

	 	case "out_fort":
			pchar.quest.time_over_Beliz_attack_Map_01.over = "yes"; // сброс, если уже откладывали
	        pchar.quest.time_over_Beliz_attack_Map_02.over = "yes";
	        pchar.quest.time_over_Beliz_attack.over = "yes";

			if(IsCompanion(characterFromID("Jackman")))  {RemoveCharacterCompanion(pchar, characterFromID("Jackman"));}
            if(IsCompanion(characterFromID("John Morris")))  {RemoveCharacterCompanion(pchar, characterFromID("John Morris"));}
            AddQuestRecord("Eng_Line_3_Morgan", "7");
            RemoveCharacterCompanion(pchar, npchar);
            // ==> Возвращаем на место Моргана
            ChangeCharacterAddressGroup(npchar, "PortRoyal_houseS1", "sit", "sit2");
            LAi_SetHuberTypeNoGroup(npchar);
            // ==> Возвращаем на место Джекмена
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Pirates_townhall", "sit", "sit1");
                LAi_SetHuberType(characterfromID("Jackman"));
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "I_know_you_good";
            }
            else
            {
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "First time";
            }
            // ==> Возвращаем на место Джона Морриса
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "PortSpein_houseF2", "sit", "sit1");
                LAi_SetHuberType(characterfromID("John Morris"));
                characters[GetCharacterIndex("John Morris")].dialog.currentnode = "I_know_you_good";
            }
            else
            {
               characters[GetCharacterIndex("John Morris")].dialog.currentnode = "First time";
            }
            ChangeCharacterReputation(pchar, 1);
            AddCharacterExpToSkill(pchar, "Leadership", 20);
            AddCharacterExpToSkill(pchar, "Fencing", 500);
            AddCharacterExpToSkill(pchar, "Pistol", 550);
            AddCharacterExpToSkill(pchar, "Sailing", 550);
            AddCharacterExpToSkill(pchar, "Accuracy", 330);
            AddCharacterExpToSkill(pchar, "Cannons", 150);

            CloseQuestHeader("Eng_Line_3_Morgan");
            pchar.questTemp.Waiting_time = "2";
            pchar.questTemp.CurQuestNumber = "4";     // идём на четвёртый квест
            pchar.questTemp.State = "empty";
            DeleteAttribute(pchar, "questTemp.CompanionQuantity");
            DeleteAttribute(pchar, "questTemp.BelizGoldQty");
            DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //дублирование снятия перка квестового десанта
            LAi_LocationFightDisable(&Locations[FindLocation("Beliz_fort")], false); //вернём боевки
            chrDisableReloadToLocation = false;
            pchar.nation = ENGLAND; // вернём нацию
            InterfaceStates.Buttons.Save.enable = true;   // вернём запись
			DoReloadCharacterToLocation("Beliz_town",  "reload", "gate_back"); //ГГ в город
            NextDiag.CurrentNode = "I_know_you_good";
			DialogExit();
        break;

	 	case "Give_blade":
			dialog.text = GetFullName(pchar) + ", I am grateful to you to the depths of my soul. Old man Mansfield was a very good man and deserved more than to be stabbed by a Spaniard.";
			link.l1 = "I've only talked to Mansfield a few times and haven't talked to him closely. But he seemed to me to be an honest and noble man.";
			link.l1.go = "Step_9_1";
        break;

	 	case "Step_9_1":
			dialog.text = "And it really is. "+
                          "As a reward for such a deed, I ask you to accept a gift from me - my rapier. This blade has no equal in the Caribbean.";
			link.l1 = "Thank you, Morgan. This gift does me honor. Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

            GiveItem2Character(pchar, "blade27");
            RemoveCharacterEquip(NPChar, BLADE_ITEM_TYPE);
            TakeItemFromCharacter(NPChar, "blade27");
            GiveItem2Character(NPChar, "blade22");
            EquipCharacterByItem(NPChar, "blade22");
        break;
		//********************* Голландская линейка *********************
        case "HolLine3_fromMansfield":
            dialog.text = "To what do I owe the pleasure of seeing you here?";
            link.l1 = "I have arrived to you on behalf of Edward Mansfield.";
            link.l1.go = "Step_H3_1";
        break;
 	 	case "Step_H3_1":
			dialog.text = "I am listening to you attentively.";
			link.l1 = "Edward asks you to help me. I need information about the plans of the Governor General of Port Royal, Thomas Madiford. I am interested in whether he has an order to open hostilities against the Dutch colonies and what exactly he is going to do.";
			link.l1.go = "Step_H3_2";
        break;
 	 	case "Step_H3_2":
			dialog.text = "Hmm, no more, no less - and that's exactly what you're interested in?!";
			link.l1 = "Yes, that's right, sir.";
			link.l1.go = "Step_H3_3";
        break;
 	 	case "Step_H3_3":
			dialog.text = "Well, then let's get right to the point. Mansfield is like a father to me, I'm ready for a lot for him. But for the sake of Holland, I'm not ready for much. Therefore, if you want me to help you, you will have to work for me personally.";
			link.l1 = "I carry out orders only from the Governor General of Curacao.";
			link.l1.go = "Step_H3_NoWork";
			link.l2 = "I'm ready toto carry out any of your orders.";
			link.l2.go = "Step_H3_4";
        break;
 	 	case "Step_H3_NoWork":
			dialog.text = "In that case, goodbye. We have nothing more to talk about.";
			link.l1 = "Very sorry...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
    		pchar.questTemp.State = "WormEnglPlans_SurrenderWorkMorgan";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "4");
		AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("xia","as"));
        break;
 	 	case "Step_H3_4":
			dialog.text = "Okay. The assignment is as follows: a filibuster named Pierre Picardy is currently hanging around Tortuga. We were involved in the same case together, and I suspect that the Picardy embezzled some of the loot. "+
                          "I need to check it out. Go to Tortuga-no one really knows you there-and try to get me as much information as possible about the Picardy.";
			link.l1 = "Wait, I'll be with you soon with the results.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HolLine3_aboutWorm";
    		pchar.questTemp.State = "WormEnglPlans_WormPicarder";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "6");
		AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("xia","as"));
        break;
 	 	case "HolLine3_aboutWorm":
			dialog.text = "What have you learned? How is my great friend and colleague Pierre Picardy doing?";
            if (CheckAttribute(pchar, "questTemp.Talks"))
            {
    			link.l1 = "Yes, it's not bad, he spends money right and left.";
    			link.l1.go = "Step_H3_5";
            }
            else
            {
    			link.l1 = "I haven't been able to find out anything significant yet...";
    			link.l1.go = "exit";
            }
        break;
 	 	case "Step_H3_5":
            sTemp = "I managed to find out the following facts.";
            if (CheckAttribute(pchar, "questTemp.Talks.Tavern")) sTemp = sTemp + "Pierre Picardes rented a room at Tortuga Tavern a year in advance.";
            if (CheckAttribute(pchar, "questTemp.Talks.Store")) sTemp = sTemp + "Buys jewelry at the Tortuga store in almost bulk.";
            if (CheckAttribute(pchar, "questTemp.Talks.Shipyard")) sTemp = sTemp + "Put the latest expensive culevrins on my frigate.";
            if (CheckAttribute(pchar, "questTemp.Talks.Usurer")) sTemp = sTemp + "The usurer has been given so much money that he doesn't take money from anyone anymore.";
            if (CheckAttribute(pchar, "questTemp.Talks.Brothel")) sTemp = sTemp + "He's a regular at the brothel and welcome.";
            dialog.text = "From now on, I want you to talk in as much detail as possible. What exactly is he spending money on?";
			link.l1 = sTemp;
			link.l1.go = "Step_H3_6";
        break;
 	 	case "Step_H3_6":
            if (CheckAttribute(pchar, "questTemp.Talks.Tavern") && CheckAttribute(pchar, "questTemp.Talks.Store") && CheckAttribute(pchar, "questTemp.Talks.Shipyard") && CheckAttribute(pchar, "questTemp.Talks.Usurer") && CheckAttribute(pchar, "questTemp.Talks.Brothel"))
 	 	    {
    			dialog.text = "Well, I guess everything is clear. The Picardian did not have such a sum before and did not receive it as a result of the joint operation. Given my suspicions, he will have to work hard to justify such expenses... I thank you.";
    			link.l1 = "Um, glad that I could help. Well, now, if you don't mind, let's get down to the business that brought me here, actually.";
    			link.l1.go = "Step_H3_10";
 	 	    }
            else
            {
                dialog.text = "Understood. But that still doesn't prove anything for sure. I know that he has such sums available. So you will have to return to Tortuga and continue collecting information.";
    			link.l1 = "I found out enough to draw the appropriate conclusions.";
    			link.l1.go = "Step_H3_7";
    			link.l2 = "Okay, I'll visit Tortuga again and continue my inquiries.";
    			link.l2.go = "exit";
    		}
        break;
 	 	case "Step_H3_7":
			dialog.text = "I don't think so.";
			link.l1 = "Pierre Picardy has money.";
			link.l1.go = "Step_H3_8";
        break;
 	 	case "Step_H3_8":
			dialog.text = "Of course there is, he got his share. The question is how much.";
			link.l1 = "I won't be able to find out.";
			link.l1.go = "Step_H3_9";
        break;
 	 	case "Step_H3_9":
			dialog.text = "In that case, consider that we have not agreed. For Mansfield's sake, I won't inform anyone about your strange desire to know so much. Goodbye, you can safely leave.";
			link.l1 = "Hmm, well, goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "12");
            DeleteAttribute(pchar, "questTemp.Talks");
        break;
 	 	case "Step_H3_10":
			dialog.text = "The fact is that I do not know what plans Madiford has and what orders he received about participating in the war. However, I know that Madiford is preparing an amphibious operation by the Port Royal garrison.";
			link.l1 = "That's not enough for me, I need to know exactly what he's up to.";
			link.l1.go = "Step_H3_11";
        break;
 	 	case "Step_H3_11":
			dialog.text = "There is a way to find out. An English officer, a lieutenant named Alan McLane, is currently in prison, who is due to be tied with a hemp tie tomorrow. Yesterday, he sent his colleague from the garrison to his forefathers in a drunken brawl. Get him out of jail and he'll tell you what's going on. And remember that he will be hanged tomorrow.";
			link.l1 = "I understand. Thanks for the advice, Henry.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "13");
            DeleteAttribute(pchar, "questTemp.Talks");
            pchar.questTemp.State = "WormEnglPlans_SaveOfficer";
            sld = GetCharacter(NPC_GenerateCharacter("Alan_MacLine", "off_eng_2", "man", "man", 10, ENGLAND, 1, false));
        	sld.name 	= "Alan";
        	sld.lastname = "McLane";
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
        	LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Alan_MacLine")], "SentJons_prison", "goto", "goto9");
        break;
        // ==> Квест №6 голландки.
 	 	case "HolLine6_fromStuvesant":
			dialog.text = "What brought you to me this time?";
			link.l1 = "I am authorized to declare that the Netherlands wants retribution for the death of Edward Mansfield.";
			link.l1.go = "Step_H6_1";
        break;
 	 	case "Step_H6_1":
			dialog.text = "Well, Edward was Dutch, I understand... What are you planning to do?";
			link.l1 = "I need to coordinate with you the order of my actions.";
			link.l1.go = "Step_H6_2";
        break;
 	 	case "Step_H6_2":
			dialog.text = "Hmm, that's reasonable. Well, let me tell you what I know myself. The Spaniards attacked the Buccaneer settlement. The customer and the direct organizer of this is the Governor-General of Santiago, Jose Sancho Jimenez, it was he who conceived and financed this operation.";
			link.l1 = "Are we going to attack Santiago?";
			link.l1.go = "Step_H6_3";
        break;
 	 	case "Step_H6_3":
			dialog.text = "Maybe. However, we should not hurry - there is already a queue for the head of the Governor-General of Santiago. The British also want his blood, but you and England are at war and joint action is impossible. Therefore, this party should be clearly defined by roles.";
			link.l1 = "Yeah, Jimenez is in big trouble.";
			link.l1.go = "Step_H6_4";
        break;
 	 	case "Step_H6_4":
			dialog.text = "Heh, that's right. So, if you want to participate in this case, you should conduct a reconnaissance mission.";
			link.l1 = "What exactly do I owe to do?";
			link.l1.go = "Step_H6_5";
        break;
 	 	case "Step_H6_5":
			dialog.text = "You must make your way to Santiago and find out if the governor-General of this city, the notorious Jose Sancho Jimenez, is in place. The attack must be carried out precisely when the Governor-General is in the city. Therefore, it is advisable to know his schedule in the near future.";
			link.l1 = "Everything is clear. I will be with you soon with the necessary information.";
			link.l1.go = "exit";
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "2");
			AddQuestUserData("Hol_Line_6_RevengeMansfield", "sSex", GetSexPhrase("en","on"));
            pchar.questTemp.State = "RevengeMansfield_toTavern";
            NextDiag.TempNode = "I_know_you_good";
            LAi_group_MoveCharacter(characterFromID("Santiago_tavernkeeper"), "QuestGroup");
            LAi_group_MoveCharacter(characterFromID("Santiago_waitress"), "QuestGroup");
        break;
 	 	case "HolLine6_fromSantiago":
			dialog.text = "Well, tell me quickly what you found out.";
			link.l1 = "Jimenez is in town and not going anywhere anytime soon. They have a city holiday planned in Santiago and there is no way without the governor-General.";
			link.l1.go = "Step_H6_6";
        break;
 	 	case "Step_H6_6":
			dialog.text = "Great! Well, you did my business, thank you. Your significant contribution to this holy cause will be appreciated by the Brethren.";
			link.l1 = "I am very glad that we were able to help you. Well, what about the storming of the city?";
			link.l1.go = "Step_H6_7";
        break;
 	 	case "Step_H6_7":
			dialog.text = "This is no longer your task, you have done your job. Mansfield will be avenged.";
			link.l1 = "I understand. Goodbye, Morgan.";
			link.l1.go = "exit";
            pchar.questTemp.State = "RevengeMansfield_FromMorganWithResult";
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "4");
            NextDiag.TempNode = "I_know_you_good";
        break;
		//********************* Французская линейка *********************
        case "FraLine8_talk":
            dialog.text = "Hello, captain " + GetFullName(pchar) + "! I've been looking out for you for a long time. So far you haven't climbed into my business, and therefore still alive and healthy. Tell me why you came. Not for idle talk, I suppose.";
            link.l1 = "Listen, Morgan, you know I didn't just do that to bother you. I'm on business.";
            link.l1.go = "Step_F8_1";
        break;
        case "Step_F8_1":
            dialog.text = "Upload...";
            link.l1 = "What do you think about the upcoming Anglo-Dutch skirmish?";
            link.l1.go = "Step_F8_2";
        break;
        case "Step_F8_2":
            dialog.text = "You know too... Well, I can say that the Dutch do not interfere with us in these waters, moreover, they are beneficial to us - they support all trade in these parts. So I don't like the idea of war itself, and the British military won't be able to really annoy the Dutch, only they will shed useless blood to the delight of the Spaniards. "+
				          "However, I believe that old fox Madiford will try to pull the chestnuts out of the fire with someone else's hands.";
            link.l1 = "That's right, that's right. It is believed that he will try to use the Brethren in the war.";
            link.l1.go = "Step_F8_3";
        break;
        case "Step_F8_3":
            dialog.text = "This may well be...";
            link.l1 = "Henry, I don't want to beat around the bush. I need you not to take part in the attack on the Dutch. I can say that I am glad that you are not interested in this war...";
            link.l1.go = "Step_F8_4";
        break;
        case "Step_F8_4":
            dialog.text = "Hmm, there is a problem here - this war is unpleasant to me, but I would not say that I am not interested in it. The fact is that my drunken guard has already spent the last piastres in the taverns, and we haven't had big business for a long time. However, whoever sent you on an errand to dissuade me, surely provided for such an option?";
            link.l1 = "Yeah, not giving a penny at the same time. But these are my worries. How long will it take your thugs to have fun on the shore and not interfere in big politics?";
            link.l1.go = "Step_F8_5";
        break;
        case "Step_F8_5":
            dialog.text = "They don't care about politics at all, and 250 thousand, I think, will be enough for a couple of weeks.";
            link.l1 = "I intend to compensate you for the losses from non-aggression against the Dutch.";
            link.l1.go = "Step_F8_6";
        break;
        case "Step_F8_6":
            dialog.text = "250 thousand per barrel - and I'll pass in the Dutch affairs of Madiford.";
			if (sti(pchar.money) >= 250000)
			{
				link.l1 = "Well, your guys are healthy to whip rum! Take the money and remember: this is a deal of honor.";
				link.l1.go = "Step_F8_7";
				AddMoneyToCharacter(pchar, -250000);
			}
			else
			{
				link.l1 = "I don't have enough money right now, but I will definitely find it and give it to you. So wait a bit.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Step_F8_6";
			}
        break;
        case "Step_F8_7":
            dialog.text = "Since when have I been reminded of honor? You talk, but don't talk...";
            link.l1 = "Sorry, Henry, I didn't meanto offend you. Well, goodbye and be well.";
            link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count)+1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "4");
        break;
		//********************* Пиратская линейка *********************
		//квест №1, диалог в тюрьме
		case "PL_Q1_1":
			dialog.text = "Yeah, "+ GetSexPhrase("guy","girl") +", you're in trouble. Well done - I did not resist. It's good that I have a lot of friends in Port Royal, and the commandant immediately reported you to me. So the issue of your release has already been resolved.";
			link.l1 = "What about John Bolton? I was taking him to you.";
			link.l1.go = "PL_Q1_2";
		break;
		case "PL_Q1_2":
			dialog.text = "I'll release him too... later. Someone tried to set me up, and I'm going to find out who it is.Now about you. I will have one assignment, I warn you right away - I will not accept refusal, I need such restrained "+ GetSexPhrase("guys","corsairs") +". Get your affairs in order and come to me.";
			link.l1 = "Okay, I'll just wash off this casemate mold. And, Morgan, Goodley said you'd pay me back.";
			link.l1.go = "PL_Q1_3";
		break;
		case "PL_Q1_3":
			dialog.text = ""+ GetSexPhrase("Oh shit, I almost forgot... Keep in mind, there's a swanky brothel in Port Royal. So don't waste your time.","Bye, captain!") +"";
			link.l1 = ""+ GetSexPhrase("Okay, I'll keep that in mind","Bye, Morgan") +"."
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q2_1";
			AddMoneyToCharacter(PChar, 10000);
			AddDialogExitQuestFunction("PiratesLine_q1_MorganEnd");
		break;
		//квест №2, диалог в резиденции Порт Рояля.
		case "PL_Q2_1":
			CloseQuestHeader("Pir_Line_1_JohnBolton");
			dialog.text = "You're here. It's good. I've already found out something about Bolton.Now you need to go to Martinique. There's a crook living there, his name is Edward Law. When you find him, give me a Black Mark.";
			link.l1 = "Can I convey anything in words?";
			link.l1.go = "PL_Q2_2";
		break;
		case "PL_Q2_2":
			dialog.text = "Heh, well, what kind of words can there be when you give a BLACK MARK?! That alone is enough.But it's not worth killing him, let him get nervous. My people will remove it themselves when the time comes. Yes, tell him anyway, let him come to me if he wants to live. That's it, go, there will be a reward waiting for you when you return.";
			link.l1 = "I understand. I will do that.";
			link.l1.go = "exit";
			sld = GetCharacter(NPC_GenerateCharacter("EdwardLoy", "reservist_1", "man", "man", 20, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 20, 65, 50, "blade25", "pistol3", 50);
			FantomMakeCoolSailor(sld, SHIP_BRIGSW, "Sea Wolf", CANNON_TYPE_CANNON_LBS20, 70, 70, 70);
			sld.name = "Edward";
			sld.lastname = "Law";
			sld.city = "LeFransua";
			sld.location	= "LeFransua_House4";
			sld.location.group = "goto";
			sld.location.locator = "goto1";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "EdwardLoy";
			sld.greeting = "Gr_EvilPirate";
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
			LAi_SetWarriorType(sld);
			GiveItem2Character(pchar, "BlackLabel");
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			pchar.questTemp.piratesLine = "BlackLabel_toLaVega";
            SetQuestHeader("Pir_Line_2_BlackLabel");
            AddQuestRecord("Pir_Line_2_BlackLabel", "1");
			NextDiag.TempNode = "PL_Q2_wait";
		break;
		case "PL_Q2_wait":
			dialog.text = "Did you hand over a Black Mark?";
			link.l1 = "Not yet, Morgan, I'm doing this...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q2_wait";
		break;

		case "PL_Q2_away_1":
			dialog.text = "Ah, " + GetFullName(PChar) + ", greetings to you. Well, tell me, was Law on Martinique?";
			link.l1 = "Was, passed the Mark to him.";
			link.l1.go = "PL_Q2_away_2";
			CloseQuestHeader("Pir_Line_2_BlackLabel");
		break;
		case "PL_Q2_away_2":
			dialog.text = "And what is he?";
			link.l1 = "Well, I wouldn't say that he was very happy.";
			link.l1.go = "PL_Q2_away_3";
		break;
		case "PL_Q2_away_3":
			dialog.text = "Yes, I have no doubt. However, all the deadlines have expired, and he did not come to me.Well, then it's time to issue a license for his capture. Don't you want to participate?";
			link.l1 = "Hmm, why not? I hope the reward will be decent?";
			link.l1.go = "PL_Q2_away_4";
		break;
		case "PL_Q2_away_4":
			dialog.text = "Yes, about the reward. Here's what's due for the delivery of the tag.";
			link.l1 = "Thank you... So what about the new assignment?";
			link.l1.go = "PL_Q2_away_5";
			//AddMoneyToCharacter(PChar, 15000);
			TakeNItems(pchar, "chest", 1);
			Log_Info("You got a credit chest");
			PlaySound("interface\important_item.wav");
		break;
		case "PL_Q2_away_5":
			dialog.text = "I have already made this offer to several of my guys, I invite you to join the business. Whoever delivers Law's head to me will receive a reward of fifty thousand gold.";
			link.l1 = "Hmm, is it necessary to have a head? He's not very attractive in life, and I think even more so when he's dead...";
			link.l1.go = "PL_Q2_away_6";
		break;
		case "PL_Q2_away_6":
			dialog.text = "No, of course not. That's how I put it, figuratively.";
			link.l1 = "Well, of course I will.";
			link.l1.go = "exit";
            SetQuestHeader("Pir_Line_3_KillLoy");
            AddQuestRecord("Pir_Line_3_KillLoy", "1");
			AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","a"));
			NextDiag.TempNode = "PL_Q2_awaywait";
			pchar.questTemp.piratesLine = "KillLoy_toHouse";
			ChangeCharacterAddress(characterFromId("EdwardLoy"), "none", "");
			pchar.quest.PiratesLine_q3_LoyHouse.win_condition.l1 = "location";
			pchar.quest.PiratesLine_q3_LoyHouse.win_condition.l1.location = "LeFransua_House4";
			pchar.quest.PiratesLine_q3_LoyHouse.function = "PiratesLine_q3_LoyHouse";
		break;
		case "PL_Q2_awaywait":
			dialog.text = "Is Edward Law dead?";
			link.l1 = "Not yet, Morgan, but it will be soon.";
			link.l1.go = "exit";
			link.l2 = "You know, Morgan, I'm tired of all this. I didn't find Law, and there is no longer any strength to search...";
			link.l2.go = "PL_Q3_notFound";
			NextDiag.TempNode = "PL_Q2_awaywait";
		break;

		case "PL_Q3_notFound":
			dialog.text = "You don't look happy, you missed Law?";
			link.l1 = "Missed...";
			link.l1.go = "PL_Q3_notFound_1";
		break;
		case "PL_Q3_notFound_1":
			dialog.text = "Well, for some reason I thought so. Maybe you shouldn't have given such orders, maybe your element is raids, boarding, fights? Time will tell. Go, maybe someday, I'll give you another chance.";
			link.l1 = "Thanks for that, Morgan...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q4";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_3_KillLoy");
		break;

		case "PL_Q3_GoodWork":
			dialog.text = "By "+ GetSexPhrase("your shining face","your shining face") +"it can be understood that everything was successful.";
			link.l1 = "Yes! Edward Law is dead!";
			link.l1.go = "PL_Q3_GoodWork_1";
		break;
		case "PL_Q3_GoodWork_1":
			dialog.text = "Great news. Did you have to sweat? They say he was a good fighter and a skilled captain.";
			link.l1 = "I had to work hard to lure him out of the kennel. Well, then – the usual work, because the money itself will not jump into your pocket. And more. Law said that a lot of pirates are unhappy with you.";
			link.l1.go = "PL_Q3_GoodWork_2";
		break;
		case "PL_Q3_GoodWork_2":
			dialog.text = "You see, " + GetFullName(pchar) + ", this is a separate philosophical question... " +
				"I'll try to explain on my fingers. Even if you have only two subordinates who do the same job and receive the same pay, they will already find a reason to be unhappy with you. And both of them! One, the one who is less lazy, will think that you pay the lazy one more than he deserves. A lazy person will think that for the same job he should get more than a partner, because he spends more energy on it. " +
				"Long story short, you will not please everyone, and you should not strive for this. And you honestly deserve reward. Keep this collection of jewelry. And check in with me periodically, maybe you'll have a task for you soon.";
			link.l1 = "Okay, Morgan, thanks!";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q4";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_3_KillLoy");
			//AddMoneyToCharacter(PChar, 50000);
			TakeNItems(pchar, "icollection", 1);
			Log_Info("You got the treasure");
			PlaySound("interface\important_item.wav");
		break;
		//квест №4, жемчужные тартаны
		case "PL_Q4_1":
			dialog.text = "Yes. I just need someone like you. I warn you right away, there is not much work here, but the income is good. Shall we compete with the best pirate of all time, Mr. Bartholomew Sharp? Long story short, I have information about where the tartans of pearl fishermen will be located for the next month.";
			link.l1 = "Money is not lying on the road. And where is it?";
			link.l1.go = "PL_Q4_3";
		break;
		case "PL_Q4_3":
			dialog.text = "At Turks, in the North Bay. So go there and make some noise in the fishery. I'm waiting for you with a bunch of pearls.";
			link.l1 = "Let's do it!";
			link.l1.go = "PL_Q4_4";
		break;
		case "PL_Q4_4":
			dialog.text = "According to my calculations, they should have at least a thousand small and five hundred large pearls by that time. So try your best. The loot is in half.";
			link.l1 = "I understand. I'm already lifting the anchor.";
			link.l1.go = "PL_Q4_5";
		break;

		case "PL_Q4_5":
			dialog.text = "Wait. Just in case, I want to warn you. Do not try to hide at least one extracted pearl! If you knew how many people have been killed by petty greed...";
			link.l1 = "I'll remember. Although you didn't have to say it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q4_wait";
			pchar.questTemp.piratesLine = "PearlQ4_toTerks"; //флаг квеста
			pchar.questTemp.Sharp.PearlAreal = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Island = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore56";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
			pchar.questTemp.Sharp.PearlAreal.terms = 30; //сроки
			pchar.questTemp.Sharp.PearlAreal.qtyShips = 9; //кол-во тартан ловцов
			pchar.questTemp.Sharp.PearlAreal.SmallPearlQty = 0; //для итогового подсчёта
			pchar.questTemp.Sharp.PearlAreal.BigPearlQty = 0;
			SetQuestHeader("Pir_Line_4_Pearl");
			AddQuestRecord("Pir_Line_4_Pearl", "1");
			AddQuestUserData("Pir_Line_4_Pearl", "sSex", GetSexPhrase("en","on"));
			pchar.quest.PQ4_SeaPearl_login.win_condition.l1 = "location";
			pchar.quest.PQ4_SeaPearl_login.win_condition.l1.location = "Terks";
			pchar.quest.PQ4_SeaPearl_login.function = "PQ4_SeaPearl_login";
			SetTimerFunction("PQ4_SeaPearl_Late", 0, 0, sti(pchar.questTemp.Sharp.PearlAreal.terms));
		break;

		case "PL_Q4_wait":
			dialog.text = "Did you robb pearl fishermen?";
			link.l1 = "Not yet, Morgan, I'm doing this...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q4_wait";
		break;
		//опоздал
		case "PL_Q4_late":
			dialog.text = "Well, what do you say?";
			link.l1 = "Henry, it so happened that I was late to Turks.";
			link.l1.go = "PL_Q4_late_1";
		break;
		case "PL_Q4_late_1":
			dialog.text = ""+ GetSexPhrase("Buddy","Girlfriend") +", you're just not serious!.. Although it's my own fault. I have so many guys at my disposal, and I gave this case to you. I'll be more careful next time.";
			link.l1 = "Henry, I really have such circumstances...";
			link.l1.go = "PearlQ4_late_2";
		break;
		case "PearlQ4_late_2":
			dialog.text = "Required. Just some other time. In the meantime, go somewhere far away, I'm not up to you...";
			link.l1 = "All right, Admiral...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q5";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_4_Pearl");
			//дача пятого квеста
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1 = "location";
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1.location = "PortRoyal_town";
            Pchar.quest.PQ5_meetInPortRoyal.function = "PQ5_meetInPortRoyal";
		break;
		//неудачный наезд
		case "PL_Q4_badWork":
			dialog.text = "Well, how are you doing with the pearls?";
			link.l1 = "Bad. Those damn tartans fell apart from me. I didn't catch up with any.";
			link.l1.go = "PL_Q4_badWork_1";
		break;
		case "PL_Q4_badWork_1":
			dialog.text = ""+ GetSexPhrase("Buddy","Girlfriend") +", you're just not serious! It was necessary to prepare! Although it's my own fault. I have so many guys at my disposal, and I gave this case to you. I'll be more careful next time.";
			link.l1 = "Henry, this is my mistake. But I beg you, don't jump to conclusions! I'll fix the situation.";
			link.l1.go = "PearlQ4_late_2";
		break;
		//удачный наезд
		case "PL_Q4_goodWork":
			dialog.text = "Well... Where is pearls, "+ GetSexPhrase("buddy","" + pchar.name + "") +"?";
			if (!CheckAttribute(pchar, "items.jewelry12") || !CheckAttribute(pchar, "items.jewelry11"))
			{
				link.l1 = "You know, Henry, somehow everything went wrong. There are problems with pearls, in general... He's not here.";
				link.l1.go = "PL_Q4_goodWork_lair";
			}
			else
			{
				link.l1 = "I have them all. In total I've earned " + pchar.items.jewelry12 + " small and " + pchar.items.jewelry11 + " big pearls!";
				link.l1.go = "PL_Q4_goodWork_1";
			}
		break;

		case "PL_Q4_goodWork_lair":
			dialog.text = "It turns out you're a rat! Are you an idiot? Do you think I don't know that you performed the operation?!";
			link.l1 = "Henry, don't get too excited...";
			link.l1.go = "PL_Q4_goodWork_lair_1";
		break;
		case "PL_Q4_goodWork_lair_1":
			dialog.text = "Don't get too excited?!! Yeah, you've got a lot of nerve. Tell you what, rat, you're finished. I'll kill you with my own hands... Close the doors!";
			link.l1 = "Henry, Henry!..";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			pchar.questTemp.piratesLine = "over";
		break;

		case "PL_Q4_goodWork_1":
			if (sti(pchar.items.jewelry12) < sti(pchar.questTemp.piratesLine.Qty.SmallPearl) || sti(pchar.items.jewelry11) < sti(pchar.questTemp.piratesLine.Qty.BigPearl))
			{
				dialog.text = "Um, wait, I have other information. You got " + pchar.questTemp.piratesLine.Qty.SmallPearl + " small and " + pchar.questTemp.piratesLine.Qty.BigPearl + " big pearls from robbery. What do you think?";
				link.l1 = "Come on, Henry! I'm telling you the truth.";
				link.l1.go = "PL_Q4_goodWork_2";
			}
			else
			{
				if (sti(pchar.items.jewelry12) >= 1000 && sti(pchar.items.jewelry11) >= 500)
				{
					dialog.text = "Great, you did a good job. In addition, I completed the 'extraction plan' - pearls are not less than the specified amount. Well done, what else can I say!";
					link.l1 = "How could it be otherwise?";
					link.l1.go = "PL_Q4_goodWork_3";
				}
				else
				{
					dialog.text = "Um, I can't say I'm happy. You didn't put into indicated plan includes 1000 small and 500 large pearls. So I'm sorry, but I'm taking everything for myself...";
					link.l1 = "Damn it! But I executed this work!";
					link.l1.go = "PL_Q4_goodWork_5";
				}
			}
		break;
		case "PL_Q4_goodWork_2":
			dialog.text = "But I don't think so. My information is exceptionally correct. You stole pearls. The only punishment for this is death. Well, close the doors, now I'm going to crush the rat...";
			link.l1 = "Henry, what are you doing?!..";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			pchar.questTemp.piratesLine = "over";
		break;

		case "PL_Q4_goodWork_3":
			dialog.text = "Half of the loot is yours, as agreed. The rest is mine.";
			link.l1 = "Great! Well, Admiral, I think I'll go.";
			link.l1.go = "PL_Q4_goodWork_4";
			TakeNItems(pchar, "jewelry12", -makeint(sti(pchar.items.jewelry12)/2));
			TakeNItems(pchar, "jewelry11", -makeint(sti(pchar.items.jewelry11)/2));
		break;
		case "PL_Q4_goodWork_4":
			dialog.text = "Don't forget to check in on me. Maybe something else will turn up.";
			link.l1 = "Okay. I'll definitely come by when the money runs out.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q5";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_4_Pearl");
			//дача пятого квеста
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1 = "location";
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1.location = "PortRoyal_town";
            Pchar.quest.PQ5_meetInPortRoyal.function = "PQ5_meetInPortRoyal";
		break;
		case "PL_Q4_goodWork_5":
			dialog.text = "You have executed it bad, "+ GetSexPhrase("buddy","girlfriend") +"! I was counting on a completely different income. And if you missed tartans - it's at the expense of your share. In general, it's useless to argue, I'm taking the pearls...";
			link.l1 = "Hmm, well, I have nowhere to go, I concede... Can I go now?";
			link.l1.go = "PL_Q4_goodWork_4";
			TakeNItems(pchar, "jewelry12", -sti(pchar.items.jewelry12));
			TakeNItems(pchar, "jewelry11", -sti(pchar.items.jewelry11));
		break;
		//квест №5, ГГ-ОЗГ. базар после дела
		case "PL_Q5_begin":
			dialog.text = "So, finally you're here. I have a message for you, " + PChar.Name + ", there is a rather unpleasant conversation.";
			link.l1 = "What happened?";
			link.l1.go = "PL_Q5_begin_1";
		break;
		case "PL_Q5_begin_1":
			dialog.text = "I was informed that you killed John Avory, after hunting him for a long time. Is it true?!";
			link.l1 = "Yes, it's true. I had an order for him. And what exactly is the matter?";
			link.l1.go = "PL_Q5_begin_2";
		break;
		case "PL_Q5_begin_2":
			dialog.text = "Whose order was it?";
			link.l1 = "Henry, you know these things are not advertised.";
			link.l1.go = "PL_Q5_begin_3";
		break;
		case "PL_Q5_begin_3":
			dialog.text = "Who is the customer?! I'm asking you!!!";
			link.l1 = "Captain Goodley.";
			link.l1.go = "PL_Q5_begin_4";
		break;
		case "PL_Q5_begin_4":
			dialog.text = "Is that so?! Since when did you start working for Captain Goodley? I thought you were my man! Maybe you don't know, of course, but John Avory was my man too! Okay, if you were fighting a duel, it happens. But to kill a member of the Brethren for money!I will take cruel revenge for his death.";
			link.l1 = "The Devil!!! But I didn't know that Avory is your man!";
			link.l1.go = "PL_Q5_begin_5";
		break;
		case "PL_Q5_begin_5":
			dialog.text = "Let's say I didn't know. But why the hell did you trust Goodley?!I did some scouting when I was informed of Avory's death. But it's not clear to me WHO the real customer of all this fuss is, who is trying to move the pieces on my board?!! But I admit, it's a delicate job. Remove two pieces in one move - you and Avory. Two of MY pieces, damn it!What did Goodley say about the real customer?";
			link.l1 = "Nothing. I asked , but he didn't admit it.";
			link.l1.go = "PL_Q5_begin_6";
		break;
		case "PL_Q5_begin_6":
			dialog.text = "Okay. Oliver, order Goodley to be here immediately! We'll figure it out on the spot, so to speak... You stand aside for now.";
			link.l1 = "Now it's clear why this jackal was constantly grinning.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_talking";
			AddDialogExitQuestFunction("PQ5_Morgan_1");
		break;

		case "PL_Q5_talking":
			sld = characterFromId("Blaze");
			dialog.text = "Oh, what people! Thanks for stopping by. Tell me, our friend Goodley, what kind of order did you order " + GetMainCharacterNameDat() + "?";
			link.l1 = "Me?!! There was nothing like that, Admiral. I'm nothing "+ NPCharSexPhrase(sld, "him","her") +"I did not instruct.";
			link.l1.go = "PL_Q5_talking_1";
		break;
		case "PL_Q5_talking_1":
			sld = characterFromId("Blaze");
			dialog.text = ""+ NPCharSexPhrase(sld, "He","She") +" claims that you gave order for money to remove John Avory. Don't you remember that?";
			link.l1 = "Am I really sick? No, of course not! Dog is trying to set me up!";
			link.l1.go = "PL_Q5_talking_2";
		break;

		case "PL_Q5_talking_2":
			sld = characterFromId("Blaze");
			dialog.text = "Okay, Goodley, don't yule. I know everything. I've interviewed people from your inner circle. They confirmed that it was you who planned to get rid of " + GetMainCharacterNameGen() + " and Avory. You knew that none of them were too tough for you, so you came up with the idea of removing one with the other's hands! You also knew that I would avenge the death of any of them, so the other one would not live. "+"Well, that's pretty clear. You'd better tell me who paid you for this intrigue. Who would want to set my people against each other?! And how much did you get for your clever move?!";
			link.l1 = "Admiral, this is a misunderstanding! I've been slandered! You've known me for so many years, would you really believe "+ NPCharSexPhrase(sld, "this sucker","this girl") +"?!";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end";
			AddDialogExitQuestFunction("PQ5_Morgan_4");
		break;

		case "PL_Q5_end":
			dialog.text = "" + GetFullName(pchar) + " how much did he pay you for Avory's death?";
			link.l1 = "Fifteen thousand.";
			link.l1.go = "PL_Q5_end_1";
		break;
		case "PL_Q5_end_1":
			dialog.text = "Hmm, it begins to seem to me that I pay your work too generously, since you agreed to fight with one of the best fighters of the archipelago for such pennies.";
			link.l1 = "But we agreed on fifty.";
			link.l1.go = "PL_Q5_end_2";
		break;
		case "PL_Q5_end_2":
			dialog.text = "Yeah, that's great! Since he won't repay you in any case, then for thirty-five thousand gold I charge you to kill the scoundrel and the rat Captain Goodley. You can start right here, I'm not squeamish.";
			link.l1 = "Ha, I would do that without payment!";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end_3";
			AddDialogExitQuestFunction("PQ5_Morgan_5");
		break;

		case "PL_Q5_end_3":
			dialog.text = "First you need to finish the job...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end_3";
		break;

		case "PL_Q5_afterFight":
			dialog.text = "Please get your money. Oliver! Bring 35,000 gold for the captain " + GetMainCharacterNameGen() + ". Well, luck was on your side today, one less scoundrel.";
			link.l1 = "Yes, it is. But I thought, what would have happened if you hadn't investigated?";
			link.l1.go = "PL_Q5_afterFight_1";
			AddMoneyToCharacter(PChar, 35000);
		break;
		case "PL_Q5_afterFight_1":
			dialog.text = "I'll be honest: I do NOT know what would have happened if I had not conducted an investigation. Okay, don't get upset. You can't lie anyway. Even an idiot can understand that.Yeah, that's not all, go to Jackman. He had some kind of trouble there, in which your name appears again. At the same time, tell us about today's event. It looks like they are links in the same chain.";
			link.l1 = "All right, Admiral. I'll leave immediately.";
			link.l1.go = "PL_Q5_afterFight_2";
		break;
		case "PL_Q5_afterFight_2":
			dialog.text = "Be careful. It seems to me that someone is digging too actively for you.";
			link.l1 = "I get it, Admiral, I'll try.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q6";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_5_Hunter");
			//сразу даём квест №6
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "1");
		break;
		//квест №7, охота на Соукинса
		case "PL_Q7_begin":
			dialog.text = "Ah, that's it " + pchar.name + " granted! So the problems will start soon.";
			link.l1 = "Henry, jokes are jokes, but I'm frankly not laughing anymore.";
			link.l1.go = "PL_Q7_begin_1";
			CloseQuestHeader("Pir_Line_6_Jackman");
		break;
		case "PL_Q7_begin_1":
			dialog.text = "If you want to tell a story about"+ GetSexPhrase("your twin","your little sister") +", then I already know it.";
			link.l1 = "And what do you think about this?";
			link.l1.go = "PL_Q7_begin_2";
		break;
		case "PL_Q7_begin_2":
			dialog.text = "It's too early to draw conclusions. It seems to me that something very bloody is brewing.";
			link.l1 = "What am I supposed to do? Waiting for a knife in the back?";
			link.l1.go = "PL_Q7_begin_3";
		break;
		case "PL_Q7_begin_3":
			dialog.text = "Try to find out who is behind all these misunderstandings. It all looks like carefully planned actions.I have taken some measures here to clarify the situation. I sent a man to investigate, so to speak. You can find him and find out what he's found.";
			link.l1 = "And what kind of person? Hmm... reliable?";
			link.l1.go = "PL_Q7_begin_4";
		break;
		case "PL_Q7_begin_4":
			dialog.text = "Ha ha ha! This one is reliable. His name is Steve Linnaeus, he went to La Vega, then had to visit every pirate settlement. But whether you visited or not, you will find out for yourself.";
			link.l1 = "I understand. I am getting ready.";
			link.l1.go = "exit";
            SetQuestHeader("Pir_Line_7_Soukins");
            AddQuestRecord("Pir_Line_7_Soukins", "1");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toLaVega";
			SetLocationCapturedState("LaVega_town", false);
		break;

		case "PL_Q7_LaVegaLate":
			dialog.text = "Oh, again our hero revealed. Well, what did you find out?";
			link.l1 = "You know, I'm didn't find Steve Linnaeus in La Vega.";
			link.l1.go = "PL_Q7_LaVegaLate_1";
		break;
		case "PL_Q7_LaVegaLate_1":
			dialog.text = "I don't even know what to tell you. You're slow like a sea turtle. Steve Linney is missing, and there are rumors that his schooner Swallow was being sold at the Santo Domingo shipyard.";
			link.l1 = "The Devil!!";
			link.l1.go = "PL_Q7_LaVegaLate_2";
		break;
		case "PL_Q7_LaVegaLate_2":
			dialog.text = "Exactly. Go to Santo Domingo, find out everything about the Swallow at the shipyard there. And be quick, or something...";
			link.l1 = "Okay, I'll do everything in the best possible way.";
			link.l1.go = "exit";
            AddQuestRecord("Pir_Line_7_Soukins", "4");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
		break;

		case "PL_Q7_LeonNotFound":
			dialog.text = "Oh, again our hero revealed. Well, what did you find out?";
			link.l1 = "Henry, Steve Linnaeus is missing.";
			link.l1.go = "PL_Q7_LeonNotFound_1";
		break;
		case "PL_Q7_LeonNotFound_1":
			dialog.text = "How is it?";
			link.l1 = "He was called somewhere by two unknown people in La Vega, no one has seen him since, and his ship was sold at the Santo Domingo shipyard.";
			link.l1.go = "PL_Q7_LeonNotFound_2";
		break;
		case "PL_Q7_LeonNotFound_2":
			dialog.text = "Well, apparently we won't see Steve anymore... Well, come see me sometime. Maybe some kind of job will turn up for you.";
			link.l1 = "Okay, Henry, I'll come in.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, -3);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
		break;

		case "PL_Q7_afterLeon":
			dialog.text = "Ah, glad to see you. What's new to tell me?";
			link.l1 = "Unfortunately, Steve Linney is dead. He was killed by pirates from the frigate Leon. But I've already paid them off.";
			link.l1.go = "PL_Q7_afterLeon_1";
		break;
		case "PL_Q7_afterLeon_1":
			dialog.text = "Karamba! Sorry for Steve...";
			link.l1 = "That's not all. The captain of this frigate persuaded me to work for the Admiral of the Brethren.";
			link.l1.go = "PL_Q7_afterLeon_2";
		break;
		case "PL_Q7_afterLeon_2":
			dialog.text = "Is that so?! I wonder who else in the Caribbean thinks of himself as an admiral of the Brethren? Was it Edward Mansfield? It seemed to me that the old man and I had agreed on everything a long time ago.";
			link.l1 = "No, Henry. This is Richard Sawkins, the head of Puerto Principe.";
			link.l1.go = "PL_Q7_afterLeon_3";
		break;
		case "PL_Q7_afterLeon_3":
			dialog.text = "Ha! Although why be surprised? Envy, greed and vanity are the three pillars on which the world rests. The captain of a pirate schooner - and he risks getting a black mark from his crew every minute, if only one of his pirates imagines himself smarter than the rest. And the admiral of the Brethren...";
			link.l1 = "Hmm, Jackman was talking about the same thing.";
			link.l1.go = "PL_Q7_afterLeon_4";
		break;
		case "PL_Q7_afterLeon_4":
			dialog.text = "Well, Jackman is a famous philosopher, so he's smart enough to stay away from admirals. Well, whatever. So we have two positive points: the first is that the scheming to eliminate you failed; and the second is that we know who is behind the scheming! Now, let's see what we can do now that Soukins has put his propaganda into action.";
			link.l1 = "Let's figure it out.";
			link.l1.go = "PL_Q7_afterLeon_5";
		break;
		case "PL_Q7_afterLeon_5":
			dialog.text = "So that's it. There are rumors that Sawkins is planning an action. We must not allow his idea to succeed, otherwise he will gain additional weight. He's lucky, and that needs to be fixed.";
			link.l1 = "Do you know anything about this promotion?";
			link.l1.go = "PL_Q7_afterLeon_6";
		break;
		case "PL_Q7_afterLeon_6":
			dialog.text = "Yes, as always, he wants to pinch the Spaniards. And this case needs to be disrupted.";
			link.l1 = "I mean, do you know the details of the promotion?";
			link.l1.go = "PL_Q7_afterLeon_7";
		break;
		case "PL_Q7_afterLeon_7":
			dialog.text = "No. You'll find out yourself and you will implement his plan earlier. Well, or you'll rip it off. In general, act on the situation. The main thing for me is a positive result.";
			link.l1 = "Understood. Well, I'm getting started.";
			link.l1.go = "PL_Q7_afterLeon_8";
		break;
		case "PL_Q7_afterLeon_8":
			dialog.text = "Great! I'm waiting for you with good news.";
			link.l1 = "I'll do everything right.";
			link.l1.go = "exit";
            AddQuestRecord("Pir_Line_7_Soukins", "8");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toPuertoPrincipe";
			sld = ItemsFromID("OpenBook");
			sld.shown = true;
			sld = ItemsFromID("Ladder");
			sld.shown = true;
			sld.startLocation = "PuertoPrincipe_town";
			sld.startLocator = "item1";
			sld.useLocation = "PuertoPrincipe_town";
			sld.useLocator = "button01";
			//прерывание на вход в резиденцию, не дать осмотреться геймеру
            Pchar.quest.PQ7_inSoukinsResidence.win_condition.l1 = "location";
            Pchar.quest.PQ7_inSoukinsResidence.win_condition.l1.location = "PuertoPrincipe_townhall";
            Pchar.quest.PQ7_inSoukinsResidence.function = "PQ7_inSoukinsResidence";
		break;

		case "PL_Q7_BadWork":
			dialog.text = "Well, how are you? Managed to stop Sawkins?";
			link.l1 = "Unfortunately, no, Henry...";
			link.l1.go = "PL_Q7_BadWork_1";
		break;
		case "PL_Q7_BadWork_1":
			dialog.text = "Bad. Now Sawkins has become stronger...";
			link.l1 = "I did everything I could.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, -10);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
		break;

		case "PL_Q7_GoodWork":
			dialog.text = "Well, how are you? Managed to stop Sawkins?";
			link.l1 = "Yes, I did everything, as planned.";
			link.l1.go = "PL_Q7_GoodWork_1";
		break;
		case "PL_Q7_GoodWork_1":
			dialog.text = "Great! And what was he up to?";
			link.l1 = "He planned to intercept a battleship that the Spaniards were sending to Europe.";
			link.l1.go = "PL_Q7_GoodWork_2";
		break;
		case "PL_Q7_GoodWork_2":
			dialog.text = "So what?";
			link.l1 = "And did not intercept...";
			link.l1.go = "PL_Q7_GoodWork_3";
		break;
		case "PL_Q7_GoodWork_3":
			dialog.text = "So, " + GetFullName(PChar) + ", let's learn more. What did you do?";
			link.l1 = "Drowned him. The gunners there were skillful, they immediately left me without sails. So I had to drown it so that Sawkins wouldn't get it.";
			link.l1.go = "PL_Q7_GoodWork_4";
		break;
		case "PL_Q7_GoodWork_4":
			dialog.text = "Damn! And you didn't even find out why was he so valuable to Sawkins?";
			link.l1 = "I'm so tired. I even stole his logbook. But only the route and time of the operation were found out from it. You can see for yourself.";
			link.l1.go = "PL_Q7_GoodWork_5";
		break;
		case "PL_Q7_GoodWork_5":
			dialog.text = "Indeed. This rascal tore out the pages, apparently he really did not want to leak information. It's all the better that such an important operation for him has been disrupted.";
			link.l1 = "That's what I thought when I ordered to load bombs.";
			link.l1.go = "PL_Q7_GoodWork_6";
			RemoveItems(PChar, "OpenBook", 1);
		break;
		case "PL_Q7_GoodWork_6":
			dialog.text = "Well, now you better mind your own business, if you want to work for some power, I won't mind. When you're done, come to me, we'll continue our cooperation.";
			link.l1 = "What if I don't want to contact the authorities?";
			link.l1.go = "PL_Q7_GoodWork_7";
		break;
		case "PL_Q7_GoodWork_7":
			dialog.text = "Then come back in about a month.";
			link.l1 = "Understood, Admiral.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, 10);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
		break;
		//квест №8, штурм Панамы
		case "PL_Q8_1":
			if (pchar.questTemp.State == "" || pchar.questTemp.State == "EndOfQuestLine")
			{
				dialog.text = "You're just in time! I already wanted to send a man to look for you.";
				link.l1 = "Well, finally! What's the deal?";
				link.l1.go = "PL_Q8_2";
				pchar.questTemp.State = "EndOfQuestLine"; //если геймер ещё не брал нац.линейку, то и не даём её после штурма Панамы
				bWorldAlivePause = false; // Конец линейки
			}
			else
			{
				dialog.text = "Hmm, I heard rumors that you are linked with " + NationNamePeopleAcc(sti(pchar.questTemp.NationQuest)) + ". I think I clearly told you to finish work for the authorities, and then come to me. What don't you understand?!";
				link.l1 = "It's clear, Henry, I'm sorry...";
				link.l1.go = "exit";
			}
		break;
		case "PL_Q8_2":
			dialog.text = "Business? Hmm, this is a serious matter. I'm gathering all the pirates for a grand enterprise that will leave a mark on history!";
			link.l1 = "Serious statement.";
			link.l1.go = "PL_Q8_3";
		break;
		case "PL_Q8_3":
			dialog.text = "More than! And in this case, "+ GetSexPhrase("my friend","my dear") +", you will have a special mission. It's time to settle accounts with our friend Sawkins.";
			link.l1 = "It's about time.";
			link.l1.go = "PL_Q8_4";
		break;
		case "PL_Q8_4":
			dialog.text = "When the 'time' comes, it's up to me, and your task is to strictly do what I ask you to do.";
			link.l1 = "Henry, although we had occasional misunderstandings, but I always acted from the principle of loyalty to the Admiral of the Brethren.";
			link.l1.go = "PL_Q8_5";
		break;
		case "PL_Q8_5":
			dialog.text = "You're right "+ GetSexPhrase("you did, buddy","you did, " + pchar.name + "") +", I appreciate it. Well, now let me bring you up to speed!";
			link.l1 = "I'm listening to you carefully, Henry.";
			link.l1.go = "PL_Q8_6";
		break;
		case "PL_Q8_6":
			dialog.text = "About the main thing. I decided to take Panama!!";
			link.l1 = "Wow! Are you sure it's possible in principle?";
			link.l1.go = "PL_Q8_7";
		break;
		case "PL_Q8_7":
			dialog.text = "Why is it impossible?";
			link.l1 = "The largest and most trained garrison of soldiers has always been there. I don't think the Spaniards are ready to weaken it in any way.";
			link.l1.go = "PL_Q8_8";
		break;
		case "PL_Q8_8":
			dialog.text = "Did it ever occur to you that the strongest garrison guards the most valuable thing the Escorial has in the New World?";
			link.l1 = "Hmm, but it seemed to me that he was guarding the bridgehead... Wait, but I heard that our Charles has made peace with the Spanish queen! Will you have any problems in London?";
			link.l1.go = "PL_Q8_9";
		break;
		case "PL_Q8_9":
			dialog.text = "You said correctly - 'heard'! And I heard that it would be very useful to weaken the position of the Spaniards and slow down their pace of development of the continent. Long story short, this event is approved.";
			link.l1 = "Hmm, well, you know better. And are you sure that it is possible to bring the squadron to Panama via Cape Horn without losses?";
			link.l1.go = "PL_Q8_10";
		break;
		case "PL_Q8_10":
			dialog.text = "I'm not sure, so we won't go through Cape Horn, but across the isthmus.";
			link.l1 = "The Devil! This is even more crazy!!";
			link.l1.go = "PL_Q8_11";
		break;
		case "PL_Q8_11":
			dialog.text = "True. Therefore, the Spaniards do not expect this from us, and the fort will not help them repel an attack from the rear. But mark my words-we will do it.";
			link.l1 = "Oh, shit! Tempting, though dangerous! When do we start?";
			link.l1.go = "PL_Q8_12";
			link.l2 = "You know, Morgan, I doubt the success of this adventure. I will refuse.";
			link.l2.go = "PL_Q8_17";
		break;
		case "PL_Q8_12":
			dialog.text = "I'm giving you 20 days so you can prepare properly. Pick up a more powerful ship, and especially assemble a bigger team. You can only participate in this case with one ship, keep that in mind.";
			link.l1 = "Understood. What else do I need to know?";
			link.l1.go = "PL_Q8_13";
		break;
		case "PL_Q8_13":
			dialog.text = "First we will take Porto Bello, so as not to leave the Spanish garrison in the rear. Then we will move to Panama through the jungle. By the way, it's useless to attack Porto Bello ahead of time, so you don't even have to try.";
			link.l1 = "Yes, I wasn't going to!";
			link.l1.go = "PL_Q8_14";
		break;
		case "PL_Q8_14":
			dialog.text = "Hehe, I know "+ GetSexPhrase("such nimble little ones, he's like that.","you, a smart girl!") +" The main thing is that in addition to successful actions in battle, you will also need to solve some issues. I'll tell you when the time comes.";
			link.l1 = "What are the questions?";
			link.l1.go = "PL_Q8_15";
		break;
		case "PL_Q8_15":
			dialog.text = "I'm telling you, you'll find out when the time comes.";
			link.l1 = "Hmm, I just don't like unpleasant surprises.";
			link.l1.go = "PL_Q8_16";
		break;
		case "PL_Q8_16":
			dialog.text = "I assure you that there are only pleasant surprises ahead of us. Anyway, I'm waiting for you in 20 days, and now get ready.";
			link.l1 = "I got it, Henry.";
			link.l1.go = "exit";
            AddQuestRecord("Pir_Line_8_Panama", "1");
			NextDiag.TempNode = "PL_Q8_ready";
			pchar.questTemp.piratesLine = "Panama_toReady";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			SetTimerFunction("PQ8_timeOver", 0, 0, 35);
			LocatorReloadEnterDisable("Shore48", "reload1_back", true); //закрывем подходы к Панаме
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
		break;
		
		case "PL_Q8_17":
			dialog.text = "Very wrong. Your refusal disappointed me, but I will not persuade you. Goodbye.";
			link.l1 = "Have a nice day, Morgan.";
			link.l1.go = "PL_Q8_18";
		break;
		case "PL_Q8_18":
			DialogExit();
			NextDiag.TempNode = "First time";
		break;

		case "PL_Q8_ready":
			if (GetQuestPastDayParam("questTemp.piratesLine") > 19)
			{
				dialog.text = "Aha, here you are! It's good, because the time has come. I understand that you are ready?";
				link.l1 = "Yes, Admiral. In full combat readiness.";
				link.l1.go = "PL_Q8_ready_1";
			}
			else
			{
				dialog.text = "Why did you here? In 20 days, I told you!";
				if (GetQuestPastDayParam("questTemp.piratesLine") == 19) dialog.text = "Why did you here? There's one more day left.";
				link.l1 = "Yes, I remember. I just wanted to see...";
				link.l1.go = "exit";
			}
		break;
		case "PL_Q8_ready_1":
            if (GetCompanionQuantity(pchar) == 1)
            {
				dialog.text = "Great! So, we're on our way. Jackman, John Morris and our great friend Richard Sawkins are also involved in the case as captains. I entrust you with the command of the squadron and the assault on Porto Bello.";
				link.l1 = "Thank you for your trust, Admiral. I won't let you down, be sure!";
				link.l1.go = "PL_Q8_ready_2";
			}
			else
			{
				dialog.text = "Listen, " + pchar.name + ", I told you to come with one ship. You just have to do what I say. What's not clear here?!";
				link.l1 = "Everything is clear, Admiral, I will do everything.";
				link.l1.go = "exit";
				NextDiag.TempNode = "PL_Q8_ready";
			}
		break;
		case "PL_Q8_ready_2":
			dialog.text = "I really hope so, "+ GetSexPhrase("buddy","" + pchar.name + "") +". Otherwise, there will be no forgiveness for you.";
			link.l1 = "It's not the first time I've taken forts, don't worry.";
			link.l1.go = "PL_Q8_ready_3";
		break;
		case "PL_Q8_ready_3":
			dialog.text = "Okay. Then let's start immediately.";
			link.l1 = "So I'm ready totake command.";
			link.l1.go = "PL_Q8_ready_4";
		break;
		case "PL_Q8_ready_4":
			pchar.quest.PQ8_timeOver.over = "yes"; //снимаем таймер
			SetTimerFunction("PQ8_PanamaTimerOver", 0, 0, 20); //ставим новый таймер
			pchar.Quest.PQ8_EnterPortoBello.win_condition.l1 = "location";
			pchar.Quest.PQ8_EnterPortoBello.win_condition.l1.location = "PortoBello";
			pchar.Quest.PQ8_EnterPortoBello.function = "PQ8_EnterPortoBello";
            pchar.questTemp.piratesLine = "Panama_toPortoBello";
			AddQuestRecord("Pir_Line_8_Panama", "4");
			AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("en","on"));
			pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
			characters[GetCharacterIndex("PortoBello_Mayor")].dialog.captureNode = "PQ8_MayorPortoBello"; //капитулянтская нода мэра
			//Морган
			FantomMakeCoolSailor(npchar, SHIP_REDOUTABLE, "Terrifying", CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
            //pchar.nation = PIRATE;//фикс - чтобы не убегать из ПортРояля с боем
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
			//LAi_SetImmortal(NPChar, false);
			NPChar.Ship.Cargo.Goods.Food = 1000;
            LAi_NoRebirthDisable(NPChar);
			LAi_RebirthOldName(NPChar);
			npchar.DeckDialogNode = "PL_Q8_deck"; //ноду на палубу
            ChangeCharacterAddressGroup(NPChar, "PortRoyal_houseS1", "goto", "goto7");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 8.5, false);
            npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
			SetCharacterRemovable(npchar, false);
			//Джекмен
			sld = characterFromId("Jackman");
			FantomMakeCoolSailor(sld, SHIP_INGERMANLAND, "Fortunato", CANNON_TYPE_CULVERINE_LBS32, 90, 90, 90);
			sld.CompanionEnemyEnable = false;  // нет отпора при обстреле
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 1000;
			LAi_SetImmortal(sld, false);
            LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			//Джон Моррис
			if (GetCharacterIndex("John Morris") == -1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("John Morris", "bocman", "man", "man", 38, PIRATE, -1, false));
        		sld.name 	= "John";
        		sld.lastname = "Morris";
				sld.Dialog.Filename = "Quest\JohnMorris.c";
				sld.greeting = "Gr_HeadPirates";
				FantomMakeCoolFighter(sld, 35, 90, 50, BLADE_LONG, "pistol4", 150);
           		LAi_SetStayType(sld);
        		LAi_SetLoginTime(sld, 0.0, 24.0);
        		LAi_SetHP(sld, 180.0, 180.0);
			}
			else
			{
				sld = characterFromId("John Morris");
			}
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, "Lagoon", CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
			sld.CompanionEnemyEnable = false;  // нет отпора при обстреле
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 1000;
            LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			sld.RebirthPhantom = true; //не тереть фантома после смерти.
			sld.DeckDialogNode = "PL_Q8_deck"; //ноду на палубу
			SetCompanionIndex(pchar, -1, sti(sld.index));
			//Ричард Соукинс
			sld = characterFromId("Richard_Soukins");
			FantomMakeCoolSailor(sld, SHIP_MANOWAR, "Lucky guy", CANNON_TYPE_CULVERINE_LBS32, 90, 90, 90);
			sld.CompanionEnemyEnable = false;  // нет отпора при обстреле
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 2500;
			LAi_SetImmortal(sld, true);
			LAi_NoRebirthEnable(sld);
			LAi_RemoveLoginTime(sld);
			sld.DeckDialogNode = "PL_Q8_deck"; //ноду на палубу
			SetCompanionIndex(pchar, -1, sti(sld.index));
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "PL_Q8_timeOver":
			dialog.text = "I entrusted you with the management of the squadron, and you are not clear what you are doing. We've been cruising the Caribbean for twenty days now, when it's ten days at most from Port Royal to Porto Bello!";
			link.l1 = "It just happened, Henry...";
			link.l1.go = "PL_Q8_timeOver_1";
			// выход с палубы
			pchar.quest.Munity = "Deads";
            LAi_LockFightMode(Pchar, false);
		break;
		case "PL_Q8_timeOver_1":
			dialog.text = "May you 'do it that way' somewhere else. I hope the Spaniards will blow your head off quickly with this approach to work. Anyway, we're leaving, we'll do without you in our business somehow. Goodbye.";
			link.l1 = "Well, to hell with you!";
			link.l1.go = "PL_Q8_timeOver_2";
		break;
		case "PL_Q8_timeOver_2":
			dialog.text = "Goodbye, "+ GetSexPhrase("buddy","girlfriend") +". Don't piss me off.";
			link.l1 = "Why would I give up your Panama Hat? Only mosquitoes in the jungle to feed.";
			link.l1.go = "PL_Q8_timeOver_3";
		break;
		case "PL_Q8_timeOver_3":
			SetTimerFunction("PQ8_openPanama", 0, 0, 40);
			LocatorReloadEnterDisable("Shore48", "reload1_back", true); //закрывем подходы к Панаме
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
			pchar.questTemp.piratesLine = "over";
			AddQuestRecord("Pir_Line_8_Panama", "3");
			AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("","a"));
			CloseQuestHeader("Pir_Line_8_Panama");
			//возвращаем Моргана
            if(IsCompanion(npchar))  RemoveCharacterCompanion(pchar, npchar);
            //Возвращаем на место Джекмена
			iTemp = GetCharacterIndex("Jackman");
			if (iTemp != -1)
			{
				if(IsCompanion(&characters[iTemp]))
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}
				LAi_SetHuberType(&characters[iTemp]);
				LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
                ChangeCharacterAddressGroup(&characters[iTemp], "Pirates_townhall", "sit", "sit1");
                characters[iTemp].dialog.currentnode = "First time";
            }
			//Джон Моррис
			iTemp = GetCharacterIndex("John Morris");
			if (iTemp != -1)
			{
				if(IsCompanion(&characters[iTemp]))
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}
				sld = &characters[iTemp];
				sld.lifeDay = 0;
			}
            //Возвращаем на место Соукинса
			iTemp = GetCharacterIndex("Richard_Soukins");
			if (iTemp != -1)
			{
				if(IsCompanion(&characters[iTemp]))
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}
				LAi_SetHuberType(&characters[iTemp]);
				LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
                ChangeCharacterAddressGroup(&characters[iTemp], "PuertoPrincipe_townhall", "sit", "sit1");
                characters[iTemp].dialog.currentnode = "First time";
            }
            NextDiag.TempNode = "PL_Q8_timeOver_exit";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_timeOver_exit":
			dialog.text = "There is nothing more to talk about.";
			link.l1 = "...";
			link.l1.go = "PL_Q8_timeOver_exit";
		break;
		//в резиденции взятого Порто Белло
		case "PL_Q8_PBResidence":
			dialog.text = "You're good at assault, praise you.";
			link.l1 = "Porto Bello is ours, Admiral. But we have a serious problem.";
			link.l1.go = "PL_Q8_PBResidence_1";
		break;
		case "PL_Q8_PBResidence_1":
			dialog.text = "What's the matter?";
			link.l1 = "The Spaniards are aware of our intentions to go to Panama. This was told to me by the captured governor.";
			link.l1.go = "PL_Q8_PBResidence_2";
		break;
		case "PL_Q8_PBResidence_2":
			dialog.text = "The devil!! And who told him about it?";
			link.l1 = "According to him, the Spanish governor-General.";
			link.l1.go = "PL_Q8_PBResidence_3";
		break;
		case "PL_Q8_PBResidence_3":
			dialog.text = "Well, it's not important. It seems to me that this is again the machinations of Sawkins. Now the Spaniards are probably ready for our arrival and will strengthen the defense of Panama.";
			link.l1 = "Yes, this trip seemed risky before, but now it's suicide altogether.";
			link.l1.go = "PL_Q8_PBResidence_4";
		break;
		case "PL_Q8_PBResidence_4":
			dialog.text = "Yes, yes, maybe. That's what, " + pchar.name + "It's time for us to get rid of Sawkins.";
			link.l1 = "Agree.";
			link.l1.go = "PL_Q8_PBResidence_5";
		break;
		case "PL_Q8_PBResidence_5":
			dialog.text = "But there is one problem here - his people. I need them. If something happens to him now, they may well leave us. And they are extremely necessary for the assault on Panama!";
			link.l1 = "Henry, so you're not going to give up on this idea?!";
			link.l1.go = "PL_Q8_PBResidence_6";
		break;
		case "PL_Q8_PBResidence_6":
			dialog.text = "Of course not!! When did I give up on the Castilian dons? Don't worry, the main thing is to do what I tell you. And everything will be fine.";
			link.l1 = "You're crazy, Henry! But for some reason I believe in success! What should I do?";
			link.l1.go = "PL_Q8_PBResidence_7";
		break;
		case "PL_Q8_PBResidence_7":
			if (pchar.location.from_sea == "Shore48")
			{
				dialog.text = "You landed in the Darien Bay, and that's right. Go there, gather your men and move on to Panama. I will go to the goal with my fighters from here, from Porto Bello. We will meet at the gates of Panama and begin the assault from two directions at once.";
				link.l1 = "I understand, Admiral!";
				link.l1.go = "PL_Q8_PBResidence_8";
			}
			else
			{
				dialog.text = "Go to the Darien Bay. Gather your men and move to Panama. I will go to the goal with my fighters from here, from Porto Bello. We will meet at the gates of Panama and begin the assault from two directions at once.";
				link.l1 = "I understand, Admiral!";
				link.l1.go = "PL_Q8_PBResidence_8";
			}
		break;
		case "PL_Q8_PBResidence_8":
			dialog.text = "That's not all. Jackman and Morris are coming with me. You're going with Sawkins. The Spaniards know about our campaign, and they will certainly try to organize an ambush in the jungle. And most likely, more than one.";
			link.l1 = "I think so, Admiral. We'll be ready.";
			link.l1.go = "PL_Q8_PBResidence_9";
		break;
		case "PL_Q8_PBResidence_9":
			dialog.text = "You don't just need to fight off the Castilians. Solve Sawkins' problem during the fight, too, I don't want to see him at the walls of Panama. He's damn brave, and as soon as he appears on the walls of Panama, his men will raise their commander to heaven. And you can't strangle a hero that easily, popularity is a great thing in the Brethren.";
			link.l1 = "What exactly do you suggest?"
			link.l1.go = "PL_Q8_PBResidence_10";
		break;
		case "PL_Q8_PBResidence_10":
			dialog.text = "Very simple. Quietly finish off Sawkins in battle, but without anyone seeing. A shot in the back is the surest means.";
			link.l1 = "Hmm, Admiral, I didn't think that you could say something like that.";
			link.l1.go = "PL_Q8_PBResidence_11";
		break;
		case "PL_Q8_PBResidence_11":
			dialog.text = "Listen, " + PChar.name + ", let's not be too particular.";
			link.l1 = "But the Admiral...";
			link.l1.go = "PL_Q8_PBResidence_12";
		break;
		case "PL_Q8_PBResidence_12":
			dialog.text = "Long story short, you can find any other way that is acceptable to you. But remember that Sawkins should not appear at the storming of Panama.";
			link.l1 = "Okay, I'll figure something out.";
			link.l1.go = "PL_Q8_PBResidence_13";
		break;
		case "PL_Q8_PBResidence_13":
			dialog.text = "Well, that's great! In general, take your people and move to the specified location. In no more than two days, you should be there. And don't try to launch an assault alone, it will give the Spaniards a head start.";
			link.l1 = "Okay, Henry, I'll be waiting for you at Panama.";
			link.l1.go = "PL_Q8_PBResidence_14";
		break;
		case "PL_Q8_PBResidence_14":
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			//bQuestDisableMapEnter = false;
			LocatorReloadEnterDisable("Shore48", "reload1_back", false); //открываем проход в джанглы через бухту
            Pchar.quest.PQ8_PBExitResidence.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.PQ8_PBExitResidence.win_condition.l1.location = pchar.location;
            Pchar.quest.PQ8_PBExitResidence.function = "PQ8_PBExitResidence";
			NextDiag.TempNode = "PL_Q8_PBResidence_over";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_PBResidence_over":
			dialog.text = "Don't linger, go to Panama!";
			link.l1 = "Yes, I get it, Henry.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_PBResidence_over";
		break;
		//у ворот Панамы
		case "PL_Q8_ExTPanama":
			iTemp = GetCharacterIndex("Richard_Soukins");

			if(PChar.QuestTemp.piratesLine == "Panama_RichardBadWork")
			{
				if(LAi_IsDead(&Characters[iTemp]))
				{
					dialog.text = "I saw Sawkins among those fighting in the last battle. It looks like you made a mistake in the jungle...";
					link.l1 = "Yes, but he's dead now! So, the job is done - Richard can prepare a tombstone.";
					link.l1.go = "PL_Q8_ExTPanama_1";
				}
				else
				{
					dialog.text = "So you couldn't complete the task! Our friend is walking around here as if nothing had happened.";
					link.l1 = "Henry, I couldn't do anything, it was very dangerous!";
					link.l1.go = "PL_Q8_ExTPanama_7_Soukins";
				}
			}
			else
			{
				dialog.text = "Ho ho, glad to see you, " + PChar.name + ", alive and healthy! I haven't seen Sawkins in this fight.";
				link.l1 = "Henry, I regret to inform you that Richard Sawkins has left this mortal world. He fell like a hero!";
				link.l1.go = "PL_Q8_ExTPanama_1";
			}
		break;
		case "PL_Q8_ExTPanama_1":
			dialog.text = "I grieve with you, my friends! We will remember him as a hero. pNu, tell me what happened in the transition?";
			link.l1 = "Before this battle at the city walls of Panama, we had to withstand three more attacks. Even the Indians attacked us!";
			link.l1.go = "PL_Q8_ExTPanama_2";
		break;
		case "PL_Q8_ExTPanama_2":
			dialog.text = "The same thing happened with us. Everything is going according to plan, "+ GetSexPhrase("buddy","dear") +"!";
			link.l1 = "What do you mean? We have suffered serious losses!";
			link.l1.go = "PL_Q8_ExTPanama_3";
		break;
		case "PL_Q8_ExTPanama_3":
			dialog.text = "But how about lossless? This is a war. But the fact is that the Spaniards made a serious tactical mistake. They scattered their forces by ambushes, so we managed to destroy them piece by piece! If they had gathered all their strength into a fist, they would undoubtedly have defeated us. Well, now the city itself is not so strong anymore. I'm sure Panama is ours!";
			link.l1 = "Do you think there are no soldiers in the city?";
			link.l1.go = "PL_Q8_ExTPanama_4";
		break;
		case "PL_Q8_ExTPanama_4":
			dialog.text = "I'm sure of it! Now listen, go to the governor's residence right now and start the interrogation. I have a bad feeling about this.";
			link.l1 = "What do you mean?";
			link.l1.go = "PL_Q8_ExTPanama_5";
		break;
		case "PL_Q8_ExTPanama_5":
			dialog.text = "It is already obvious that the mayor of Porto Bello told the truth - they were waiting for us. This means that the population of the city left it along with all the valuable belongings. In this case, the revenue from our company will be negligible. But we have a chance to take the gold of the Escorial, and for that we need a governor. He probably knows where the gold was hidden in anticipation of the assault.";
			link.l1 = "You're really right.";
			link.l1.go = "PL_Q8_ExTPanama_6";
		break;
		case "PL_Q8_ExTPanama_6":
			dialog.text = "Move out to the Panama Residence, and don't linger! I'll take care of other things in the city.";
			link.l1 = "Understood. I'm doing it.";
			link.l1.go = "PL_Q8_ExTPanama_7";
		break;
		case "PL_Q8_ExTPanama_7":
			AddQuestRecord("Pir_Line_8_Panama", "9");
			//characters[GetCharacterIndex("Panama_Mayor")].dialog.captureNode = "PQ8_afterAttack"; //капитулянтская нода мэра
			pchar.quest.PQ8_piratesInPanama.win_condition.l1 = "location";
			pchar.quest.PQ8_piratesInPanama.win_condition.l1.location = "Panama_town";
			pchar.quest.PQ8_piratesInPanama.function = "PQ8_piratesInPanama";
			NextDiag.TempNode = "PL_Q8_ExTPanama_over";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_ExTPanama_over":
			dialog.text = "Move to the residence, don't waste time!";
			link.l1 = "Yes, Henry, I get it...";
			link.l1.go = "exit";
		break;
		case "PL_Q8_ExTPanama_7_Soukins":
			dialog.text = "Well, of course!";
			link.l1 = "If you're so smart, you should have shot him yourself.";
			link.l1.go = "PL_Q8_ExTPanama_8_Soukins";
		break;
		case "PL_Q8_ExTPanama_8_Soukins":
			dialog.text = "I got it! So, let's stop there. You can go back to your ship, there's no way for you to go to Panama. For letting me down, I'm excluding you from the Brethren. Get out!";
			link.l1 = "I didn't really want to!";
			link.l1.go = "PL_Q8_ExTPanama_9_Soukins";
		break;
		case "PL_Q8_ExTPanama_9_Soukins":
			QuestSetCurrentNode("Richard_Soukins", "PQ8_exitTown");
			AddQuestRecord("Pir_Line_8_Panama", "10");
			CloseQuestHeader("Pir_Line_8_Panama");
			LocatorReloadEnterDisable("Panama_ExitTown", "reload4", true); //закроем вход в город
			SetTimerFunction("PQ8_openPanama_2", 0, 0, 30); //таймер на открыть все потом.
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//в Панаме после выхода ГГ из резиденции
		case "PL_Q8_Panama1":
			dialog.text = "Did you found governor?";
			link.l1 = "Yes, I found him and questioned.";
			link.l1.go = "PL_Q8_Panama1_1";
		break;
		case "PL_Q8_Panama1_1":
			dialog.text = "And what did he say?";
			link.l1 = "The Escorial gold may be in the governor's office at the residence. Only there's no key to the chest, it's locked.";
			link.l1.go = "PL_Q8_Panama1_2";
		break;
		case "PL_Q8_Panama1_2":
			dialog.text = "And where is this key?";
			link.l1 = "At the commandant's. I should take a good look at the last battlefield, maybe I'll find the commandant there. If not, we'll have to look in the fort.";
			link.l1.go = "PL_Q8_Panama1_3";
		break;
		case "PL_Q8_Panama1_3":
			dialog.text = "Hmm, well, go ahead. In the meantime, I'll take care of the governor, his story is suspicious. The chest is with the governor, and the key is with the commandant! Heh, it's weird...";
			link.l1 = "What's so strange about that? Surely this was organized to exclude the plundering of the treasury by the top officials of the city. It's a good thing the trunk wasn't dragged into the jungle. Look for him later.";
			link.l1.go = "PL_Q8_Panama1_4";
		break;
		case "PL_Q8_Panama1_4":
			sld = characterFromId("FantomMayor");
			sld.lifeDay = 0;
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1 = "locator";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.location = "Panama_TownhallRoom";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator_group = "box";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator = "private1";
			pchar.quest.PL_Q8_ResEnterBox.function = "PL_Q8_ResEnterBox";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload3", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//в резиденции Панамы с ключом
		case "PL_Q8_Panama2":
			npchar.quest.locInd = FindLocation(pchar.location);
			sld = &locations[sti(npchar.quest.locInd)];
			if (CheckAttribute(sld, "private1.money")) sld.private1.money = 0;
			if (CheckAttribute(sld, "private2.money")) sld.private2.money = 0;
			dialog.text = "I see you've done with the task. You found the key!";
			link.l1 = "I did! Where is the governor?";
			link.l1.go = "PL_Q8_Panama2_1";
		break;
		case "PL_Q8_Panama2_1":
			dialog.text = "Went to the next world. It seemed to me that he didn't tell you everything, so I questioned him with passion. But his health failed him...";
			link.l1 = "Hmm, did you find out something important?";
			link.l1.go = "PL_Q8_Panama2_2";
		break;
		case "PL_Q8_Panama2_2":
			dialog.text = "He knew how much gold was in the closed chest. There are 50 million piastres, "+ GetSexPhrase("buddy","" + pchar.name + "") +"! Yes, you already know that without me, come on, lay out the loot!";
			link.l1 = "This is the money, Morgan. Listen, how do you plan to organize the share division?";
			link.l1.go = "PL_Q8_Panama2_3";
			sld = &locations[sti(npchar.quest.locInd)];
			if (CheckAttribute(sld, "private1.items.gold")) DeleteAttribute(sld, "private1.items.gold");
			else AddMoneyToCharacter(pchar, -50000000);
		break;
		case "PL_Q8_Panama2_3":
			dialog.text = "Our brave pirates hid a lot of things in their pockets. Today I will force you to hand over everything to the common cauldron, and then we will divide all the loot according to the laws of the Brethren.";
			link.l1 = "Hmm, that would be fair!";
			link.l1.go = "PL_Q8_Panama2_4";
		break;
		case "PL_Q8_Panama2_4":
			dialog.text = "You have already handed over your loot, so I have no complaints against you - you can be free from the event I'm planning. But there is a job for you at this time "+
				"Go back to the Panama Fort. There's a chest behind the fort, on the outside of the wall. There must be more Escorial gold in it! This was told by the late governor of Panama.";
			link.l1 = "Damn, it can't be! From the outside?!";
			link.l1.go = "PL_Q8_Panama2_5";
		break;
		case "PL_Q8_Panama2_5":
			dialog.text = "That's right, the chest is located right on a sheer cliff. I'm waiting for you with this gold, so don't delay.";
			link.l1 = "Okay, I'll check it out now.";
			link.l1.go = "PL_Q8_Panama2_6";
		break;
		case "PL_Q8_Panama2_6":
			AddQuestRecord("Pir_Line_8_Panama", "12");
			AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("ate","la"));
			AddQuestUserData("Pir_Line_8_Panama", "sSex1", GetSexPhrase("","a"));
			Pchar.quest.PL_Q8_inPanamaFort2.win_condition.l1 = "location";
			Pchar.quest.PL_Q8_inPanamaFort2.win_condition.l1.location = "Panama_Fort";
			Pchar.quest.PL_Q8_inPanamaFort2.function = "PL_Q8_inPanamaFort2";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//Морган в Порт Рояле
		case "PL_Q8_afterPanama":
			dialog.text = "Wow, that's a meeting! " + pchar.name + "Is that you?!";
			link.l1 = "Me, in person. Here, to look into your eyes.";
			link.l1.go = "PL_Q8_afterPanama_1";
		break;
		case "PL_Q8_afterPanama_1":
			dialog.text = "You're probably offended at me. Well, I'm sorry I had to leave you in Panama - I was in a hurry, you know.";
			link.l1 = "Offended?!! No, I'm not offended by you. I despise you like a rat who stole his share from the Brethren!";
			link.l1.go = "PL_Q8_afterPanama_2";
		break;
		case "PL_Q8_afterPanama_2":
			dialog.text = "You think what you're saying!!! You know, times are changing!";
			link.l1 = "What the hell are the times?!!";
			link.l1.go = "PL_Q8_afterPanama_3";
		break;
		case "PL_Q8_afterPanama_3":
			dialog.text = "Ordinary, "+ GetSexPhrase("buddy","" + pchar.name + "") +". Do you hope to rob ships at sea or storm cities for the rest of your life? Piracy therefore managed to develop in such a way that there was a war between the great powers. As soon as a lasting peace is established, we will immediately become superfluous!That time has already come! You are already superfluous!";
			link.l1 = "Yes, no one has ever needed us, except for impostors trying to make money at our expense! We have always been used for their own selfish purposes by people like you! And then they betrayed us under the guise of anti-piracy laws!";
			link.l1.go = "PL_Q8_afterPanama_4";
		break;
		case "PL_Q8_afterPanama_4":
			dialog.text = "No one will touch you now. I managed to justify myself in court for taking Panama, but do you know why it happened?";
			link.l1 = "Don't act like a saint! The money that you took to England helped only you, and we were persecuted, and we will be persecuted! The powers, kings, governors, when it suits them, try to weaken the enemy with our hands, and then they hypocritically hang us in the squares! And they gather again under their banners when the need comes.";
			link.l1.go = "PL_Q8_afterPanama_5";
		break;
		case "PL_Q8_afterPanama_5":
			dialog.text = "Yes. I have done a great service to the English crown - I have greatly reduced the number of pirates in the Caribbean, and even brought such money to the English treasury!";
			link.l1 = "Our money, Morgan!!! Ours! The money of those guys who believed in you as a hero, whom you lured into the jungle with flattery and the promise of fame and wealth, and then abandoned in a plundered and hungry Panama. The money of those whose bones rot under its walls!";
			link.l1.go = "PL_Q8_afterPanama_6";
		break;
		case "PL_Q8_afterPanama_6":
			dialog.text = "Yes, "+ GetSexPhrase("buddy","" + pchar.name + "") +". And this was the only chance to continue to exist. And anyway, I'm a planter now, not an admiral of the Brethren.";
			link.l1 = "It was a chance for you! But you have already ceased to exist for us as a significant figure. And if you like this kind of existence, then I'll tell you what: in just five years you'll turn into a fat, drunken pig, to whom no self-respecting privateer will shake hands. And then you'll die of rum in a puddle of your own manure, and pirates will come to your grave to spit on the tombstone of the most famous scoundrel!";
			link.l1.go = "PL_Q8_afterPanama_7";
		break;
		case "PL_Q8_afterPanama_7":
			dialog.text = "You didn't understand anything! I paid for myself, and for you, and for all the pirates who want to live a normal life! The Brethren is no more, so its admiral is no more. I have brought the pardon of the English throne to all the pirates! And those who do not want to obey, I will punish.";
			link.l1 = "What can you do? Without us, you've become as much a target as any other governor. Without the support of the pirates, you turned into an ordinary official, forced to pay us for your peace of mind.";
			link.l1.go = "PL_Q8_afterPanama_8";
		break;
		case "PL_Q8_afterPanama_8":
			dialog.text = "Keep in mind, " + PChar.name + "you're playing with fire. I won't spare anyone, you know me!";
			link.l1 = "That's why I'm challenging you! I will destroy all the settlements one by one until there is not a single English city left in the Caribbean, and then you will be called to Europe and presented with a bill! Until then, you will wake up at night from the sound of palm leaves knocking on your window and grab a pistol, afraid that " + GetFullName(PChar) + " came for your filthy soul!";
			link.l1.go = "PL_Q8_afterPanama_9";
		break;
		case "PL_Q8_afterPanama_9":
			dialog.text = "Well, whatever you want... You selected your destiny yourself.";
			link.l1 = "Goodbye, Henry, you are pathetic. I'll tell your former friends about it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "over";
            AddQuestRecord("Pir_Line_8_Panama", "14");
	    AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("xia","as"));
            CloseQuestHeader("Pir_Line_8_Panama");
		break;

		//*************************** Квест "Orion fluyt accompaniment"Орион"" **********************

		case "Andre_Abel_Quest_Morgan_Dialog_1":
			dialog.text = "Do you have business with me?";
			link.l1 = "Yes, Admiral. A good man really needs your help.";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_2";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_2":
			dialog.text = "State the essence of the question, I don't have much time.";
			link.l1 = "Have you heard of a merchant named Andre Abel?";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_3";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_3":
			dialog.text = "Andre Abel, Andre Abel... I've heard something about him... from Jackman, if I'm not mistaken.";
			link.l1 = "That's right. Jackman is after him after Abel refused to pay him 50 percent of his profits.";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_4";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_4":
			dialog.text = "Everything! I remembered!.. Ah yes, Abel! Ha ha ha!.. So he sent you to solve this issue?";
			link.l1 = "After several pirate attacks, he is completely broke, and asked Jackman to intercede for him, but he doesn't want to hear anything.";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_5";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_5":
			dialog.text = "You see, Captain " + GetFullName(pchar) + " what does greed and unwillingness to share lead a person to? "+
                          "Well, I'm ready to write to Jackman about him, but on condition that you do one of my errands... A quid pro quo, so to speak.";

			link.l1 = "And what service are we talking about?";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_6";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_6":
			dialog.text = "I need you to deliver an official letter to the Governor-General of Curacao, Peter Stuyvesant.";
			link.l1 = "Phew, I will deliver of course!";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_9";
			link.l2 = "Sorry, Admiral, but I had completely different plans...";
			link.l2.go = "Andre_Abel_Quest_Morgan_Dialog_7";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_7":
			dialog.text = "Hmm, where does such arrogance come from? So you think it's possible to occupy my time with fables about this 'good man' Abele, and after I've sacrificed my principles and am ready to help him, don't you want to lift a finger for me? "+
                          "We won't agree on that. Goodbye.";
			link.l1 = "Even so, but I also have my own principles. I'm not a errand dog...";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_8";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("Andre_Abel_Quest", "12");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("xia","as"));
			ChangeCharacterAddressGroup(CharacterFromID("Andre_Abel"), "none", "", "");
			PChar.QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek = true; // Флаг для разговора с тавернщиком в Порт-о-Принсе
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_9":
			dialog.text = "Well, that's great. You have 10 days to complete it. So hurry up.";
			link.l1 = "Okay, I'm leaving immediately.";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_10";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_10":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			Log_TestInfo("A letter has been received from Henry Morgan.");
			GiveItem2Character(PChar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_Andre_Abel_Quest_Letter_1");
			AddQuestRecord("Andre_Abel_Quest", "14");
			QuestSetCurrentNode("hol_guber", "Andre_Abel_Quest_Hol_Gov_Node_1");
			SetFunctionTimerCondition("Andre_Abel_Quest_Curasao_10Days_Left", 0, 0, 10, false);
			SetFunctionLocationCondition("Andre_Abel_Quest_In_Curacao_Townhall", "Villemstad_townhall", false);
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_11":	// Попали в тюрьму
			dialog.text = "Glad to see you alive and unharmed... Well, did you deliver the letter?";
			link.l1 = "Yes, delivered. That's the only reason they put me in jail and wanted to hang me!";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_12";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_12":
			dialog.text = "Hmm, I knew that the Governor General of Curacao has a short temper. But I didn't expect it to come to an arrest in any way... "+
                          "But I'm glad you managed to get out.";
			link.l1 = "How glad I am! You can't imagine...";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_13";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_13":
			dialog.text = "Okay, okay... If it were that simple, I would have sent one of my henchmen, but if he failed, he would have been hanged for sure. And you're a disinterested person, so to speak.";
			link.l1 = "So that's what my service was...";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_14";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_14":
			dialog.text = "Okay, that's enough!.. I actually had no doubt that you would be able to return alive. In such matters, ignorance sometimes plays a crucial role. The townsfolk then say that luck smiles on the simpletons ... "+
                          "Here's a letter to Jackman. As agreed, a quid pro quo.";
			link.l1 = "Thanks for that...";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_15";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_15":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			Log_TestInfo("A letter has been received from Henry Morgan.");
			GiveItem2Character(PChar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_Andre_Abel_Quest_Letter_2");
            AddQuestRecord("Andre_Abel_Quest", "21");
	    AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("xia","as"));
	    AddQuestUserData("Andre_Abel_Quest", "sSex1", GetSexPhrase("","a"));
            QuestSetCurrentNode("Jackman", "Andre_Abel_Quest_Jackman_Dialog_7");
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_16":	// Отбивались от солдат в резиденции
			dialog.text = "Glad to see you alive and unharmed... Well, did you deliver the letter?";
			link.l1 = "Delivered... Only I almost went to jail!";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_12";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_17":
			dialog.text = "To jail?! The Dutch are more bloodthirsty than I thought - to put the messenger in jail... Well okay... The main thing is that you delivered the letter, which means that you have completed my errand.";
			link.l1 = "And?";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_14";
		break;


// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("Get out of here!", "Get out of my office!");
			link.l1 = "Ah...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Морганом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "You shouldn't distract me from the case with empty appeals. From now on, the result may be more deplorable...";
        			link.l1 = "I got it, Morgan.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("You've really tired me out, no more communication.", "I don't want to communicate with you, so you better not bother me.");
			link.l1 = RandPhraseSimple("Well, as you know...", "Hmm, well...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Морганом через 20 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "I hope you won't bore me with empty conversations in the future, otherwise I'll have to kill you. I admit, it will be very unpleasant for me.";
        			link.l1 = "I won't, Morgan.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
			if (Pchar.location == "SentJons_HouseF3")
			{
				DoReloadCharacterToLocation("SentJons_town","reload","houseF3");
			}
			else
			{
				DoReloadCharacterToLocation("PortRoyal_town","reload","houseS1");
			}
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

