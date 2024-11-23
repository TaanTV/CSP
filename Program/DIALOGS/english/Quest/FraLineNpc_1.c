// диалоговый файл №1 на фр. линейку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
    float locx, locy, locz;
	string sTemp, attrName;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = "Nothing to talk about.";
			link.l1 = "Okay...";
            link.l1.go = "exit";

//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
            //Квест №1, сопровождение Леграна.
            if (pchar.questTemp.State == "Fr1Legran_toTavern")// квест №1, Легран в таверне
            {
    			dialog.text = "I'm listening to you, what do you want?";
    			link.l1 = "Monsieur, as far as I know, you are Pierre Legrand.";
    			link.l1.go = "Step_F1_1";
            }
            if (pchar.questTemp.State == "Fr1Legran_afterFightBand")// квест №1, Легаран после боя.
            {
    			dialog.text = "I need to hurry up, I don't have time...";
    			link.l1 = "Monsieur, I delivered you to the bay, my task is completed...";
    			link.l1.go = "Step_F1_3";
    			link.l2 = "And we have already arrived! I decided that your money is mine, they will come in handy.";
    			link.l2.go = "Step_F1_5";
            }
            //Квест №2, доставка письма на Тортугу
			if (pchar.questTemp.State == "Fr2Letter_SeekProblems")// квест №2, странные типы в таверне
            {
    			dialog.text = "...to the Palm Beach.";
				link.l1 = "(to myself) so, so, Palm Beach...";
    			link.l1.go = "Step_F2_1";
            }
			if (pchar.questTemp.State == "Fr2Letter_SeekProblems" && pchar.location == "Shore22")// квест №2, странные типы в бухте
            {
    			dialog.text = "...Our galleon should be here by now.";
				link.l1 = "(to myself) well, well, galleon...";
    			link.l1.go = "Step_F2_5";
            }
			if (npchar.id == "DeLeiva")// квест №3, база с мужем донны Анны
            {
    			dialog.text = "Well, so we waited for our guest. Welcome to dinner, "+ GetSexPhrase("monsieur","mademoiselle") +". The main dish for you today is good Toledo steel!";
				link.l1 = "That's the meeting! What's the matter?!";
    			link.l1.go = "Step_F3_1";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_toAnna")// квест №5, донна Анна в резиденции Тортуги
            {
    			dialog.text = "Senor d sent you'Augeron?";
    			link.l1 = "Yes, madam. What can I do for you?";
    			link.l1.go = "Step_F5_1";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_toHavana")
            {
    			dialog.text = "Tell me, "+ GetSexPhrase("senor","senorita") +", what have you learned?";
    			link.l1 = "Nothing yet. But I'm on this case, don't worry, madam...";
    			link.l1.go = "exit";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_SeekHoseBrothers")
            {
    			dialog.text = "Tell me, "+ GetSexPhrase("senor","senorita") +", what have you learned?";
    			link.l1 = "Nothing yet. But I'm on this case, don't worry, madam...";
    			link.l1.go = "exit";
            }
			if (npchar.id == "DeLeivaBrother_1" || npchar.id == "DeLeivaBrother_2")// квест №5, братья де Лейва
            {
    			dialog.text = "What do you need here?";
    			link.l1 = "Seniora, aren't you relatives of Don Jose Ramirez de Leyva?";
    			link.l1.go = "Step_F5_2";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_GoodWork")// квест №5, донна Анна после выполнения задачи
            {
				dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Senor","Senorita") +"This is the second time you've saved my life. Know that in my person you have found a true friend.",
					         "Hello again, Captain. I'm glad to see you.", "And hello captain again...", "Once again a day: hello captain...", "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Senora, quite by chance near Havana I met two Castilian noblemen, and you should know how they expressed themselves about you... It seems, Donna Anna, that your memory is cherished in Castile.",
					      "And I'm glad to see you too.", "And once again I'm glad to see you...", "Hello, senora...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F5_8", "none", "none", "none", npchar, Dialog.CurrentNode);

            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "empty")// квест №5, донна Анна после выполнения задачи
            {
				dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Senor","Senorita") +"This is the second time you've saved my life. Know that in my person you have found a true friend.",
					         "Hello again, Captain. I'm glad to see you.", "And hello captain again...", "Once again a day: hello captain...", "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Senora, quite by chance near Havana I met two Castilian noblemen, and you should know how they expressed themselves about you... It seems, Donna Anna, that your memory is cherished in Castile.",
					      "And I'm glad to see you too.", "And once again I'm glad to see you...", "Hello, senora...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F5_8", "none", "none", "none", npchar, Dialog.CurrentNode);
            }
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_toGuadeloupe")// квест №6, базар в доме Олоне
            {
				dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Sir","Miss") +", are you going to be taught good manners?! No one can enter my house without an invitation!",
					         "We seem to have discussed everything...", "Something else?", "The same thing again, how much can I do?!", "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("I have my invitation with me. Here it is - this is an urgent package from the Governor-General d'Ogeron.",
					      "Yes, that's right...", "No, it's okay...", "Come on, don't get excited...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F6_1", "none", "none", "none", npchar, Dialog.CurrentNode);
            }
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_FoundMoney") //успели к деньгам
            {
    			dialog.text = "Did you find our reals?";
    			link.l1 = "Yes, everything is fine. Fortunately, we made it in time-I have the money.";
    			link.l1.go = "Step_F6_14";
				LAi_LocationDisableOfficersGen("Cumana_town", false); //офицеров пускать
            }
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_WeLate") //деньги ушли
            {
    			dialog.text = "Did you find our reals?";
    			link.l1 = "No, Francois...";
    			link.l1.go = "Step_F6_10";
				LAi_LocationDisableOfficersGen("Cumana_town", false); //офицеров пускать
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr8ThreeCorsairs_toBonrepo") //Квест №8. Маркиз Бонрепо в Бас-Тере
            {
    			dialog.text = "With whom do I have the honor?";
    			link.l1 = "Captain " + GetFullName(pchar) + ". I have arrived to you by order of the Governor-General d Augeron.";
    			link.l1.go = "Step_F8_1";
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek")
            {
    			dialog.text = "So, how is your mission progressing successfully?";
    			if (sti(pchar.questTemp.Count) == 3)
				{
					link.l1 = "It's done. All three of them will not participate in the war on the side of England.";
    				link.l1.go = "Step_F8_9";
				}
				else
				{
					link.l1 = "I haven't been able to meet everyone yet, but I'm working on it.";
    				link.l1.go = "exit";
				}
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr12EndWar_toBorepo")
            {
    			dialog.text = "Ah, "+ GetSexPhrase("Baron","Baronessa") +"! I'm glad to see you. I'll say more - I've been waiting for you...";
    			link.l1 = "Glad to see you too, Marquis.";
    			link.l1.go = "Step_F12_1";
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "EndOfQuestLine")
            {
    			dialog.text = "That's it, "+ GetSexPhrase("Baron","Baronessa") +", I'm not detaining you anymore. Goodbye...";
    			link.l1 = "Goodbye, Marquis...";
    			link.l1.go = "exit";
            }
		break;
//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Доставка Леграна до Мартиники. Квест №1 **********************************
 		case "Step_F1_1":
			dialog.text = "Yes, it is.";
			link.l1 = "My name is "+ GetFullName(pchar) +". I have been sent to you by the Governor-General d'Ogeron. I have an assignment to quietly and unnoticeably take you to Martinique in the Bay of Le Maren.";
			link.l1.go = "Step_F1_2";
		break;
 		case "Step_F1_2":
			dialog.text = "If the Governor-General trusts you, then so do I. When do we leave?";
			link.l1 = "As soon as possible. Wait for me on my ship.";
			link.l1.go = "Step_F1_exit";
		break;
 		case "Step_F1_exit":
			locations[FindLocation("Shore39")].DisableEncounters = true; //энкаунтеры закроем
    		pchar.questTemp.State = "Fr1Legran_toLeMaren";
            AddQuestRecord("Fra_Line_1_LegranDis", "2");
			LAi_SetStayType(npchar);
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, "Tortuga_tavern", "tables", LAi_FindNearestFreeLocator("tables", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8);
			Pchar.quest.Fr1Legran_intoLeMaren.win_condition.l1 = "location";
            Pchar.quest.Fr1Legran_intoLeMaren.win_condition.l1.location = "Shore39";
            Pchar.quest.Fr1Legran_intoLeMaren.win_condition = "Fr1Legran_intoLeMaren";
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            DialogExit();
		break;
 		case "Step_F1_3":
			dialog.text = "Yes, yes, undoubtedly, you have fully fulfilled your obligations. Let me thank you properly: the sum of 20,000 gold looks very decent, I suppose?";
			link.l1 = "Quite...";
			link.l1.go = "Step_F1_4";
		break;
 		case "Step_F1_4":
			dialog.text = "This money is yours, if you will.\n"+
				          "Goodbye and be well, "+ GetSexPhrase("monsieur","mademoiselle") +".";
			link.l1 = "Goodbye, sir. I wish you a good trip home to France... Goodbye!";
			link.l1.go = "Step_F1_4_exit";
		break;
		case "Step_F1_4_exit":
			pchar.questTemp.State = "Fr1Legran_backGovernor";
			AddQuestRecord("Fra_Line_1_LegranDis", "3");
			AddMoneyToCharacter(pchar, 20000);
			LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", 10.0);
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], true);
			NPChar.LifeDay = 0;
			RemovePassenger(pchar, npchar);
            DialogExit();
		break;
 		case "Step_F1_5":
			dialog.text = "Oh, you're bastard! I will inform the Governor-General how"+ GetSexPhrase("oh, the scoundrel got in","the scoundrel got in") +"trust him!";
			link.l1 = "Stay alive first, mattress!";
			link.l1.go = "Step_F1_6";
		break;
 		case "Step_F1_6":
			LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
			AddQuestRecord("Fra_Line_1_LegranDis", "4");
			pchar.questTemp.State = "Fr1Legran_LegranKilled";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Арест ГГ у Стэвезанта. Квест №2 **********************************
 		case "Step_F2_1":
			dialog.text = "Hey, what do you want here, what are you up for? We didn't invite you for a drink.";
			link.l1 = "My name is captain " + GetFullName(pchar) + ", I just came from Tortuga... Would you like to join my team?";
    		link.l1.go = "Step_F2_2";
		break;
 		case "Step_F2_2":
			dialog.text = "No, we don't want to!";
			link.l1 = "I have good conditions, think about it... Shall we have a drink? Let me sit down with you...";
			link.l1.go = "Step_F2_3";
		break;
 		case "Step_F2_3":
			dialog.text = "Sit down and have a drink, Captain. Well, we have to go.";
			link.l1 = "Ah, well...";
			link.l1.go = "Step_F2_4";
		break;
 		case "Step_F2_4":
			chrDisableReloadToLocation = true;
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (i=1; i<=2; i++)
            {
				sld = characterFromId("Bandit_"+i);
				LAi_SetStayType(sld);
				if (i==2) ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "tables", "stay2");
				else ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "goto", "goto3");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", 10);
			}
			Pchar.quest.Fr2Letter_OutTavern_2.win_condition.l1 = "location";
            Pchar.quest.Fr2Letter_OutTavern_2.win_condition.l1.location = "Villemstad_town";
            Pchar.quest.Fr2Letter_OutTavern_2.win_condition = "Fr2Letter_OutTavern_2";
			locations[FindLocation("Shore22")].DisableEncounters = true; //энкаутеры уберём временно
			LAi_SetPlayerType(pchar);
            DialogExit();
		break;

 		case "Step_F2_5":
			dialog.text = "You again? And what are you doing here?";
			link.l1 = "I want to know something. You were talking about some galleon of yours...";
    		link.l1.go = "Step_F2_6";
		break;
 		case "Step_F2_6":
			dialog.text = "You have sharp hearing. Good ears...";
			link.l1 = "I'm waiting for an answer!";
    		link.l1.go = "Step_F2_7";
		break;
 		case "Step_F2_7":
			dialog.text = "Who are you to demand an answer?";
			link.l1 = "I already introduced myself, if memory serves. Or do you not know what Tortuga is and who filibusters are?!";
    		link.l1.go = "Step_F2_8";
		break;
 		case "Step_F2_8":
			dialog.text = "We know who the filibusters are. We call you Ladrons.";
			link.l1 = "That's what only the Spaniards call us...";
    		link.l1.go = "Step_F2_9";
		break;
 		case "Step_F2_9":
			dialog.text = "True... Amigo, St. Anthony gave us the opportunity to commune the captain of the Ladrones - the benefit of "+ GetSexPhrase("he is one","she is one") +". Let's not waste any time...";
			link.l1 = "Those are the Spaniards! And what about your galleon, you didn't answer!";
    		link.l1.go = "Step_F2_10";
		break;
 		case "Step_F2_10":
			dialog.text = "We are waiting for our galleon here, it is about to anchor. Now you know everything, but you won't need this knowledge...";
			link.l1 = "Well, that's how to say it. Perhaps it's time to look at the color of Castilian blood...";
    		link.l1.go = "Step_F2_11";
		break;
 		case "Step_F2_11":
			DeleteAttribute(&locations[FindLocation("Shore22")], "DisableEncounters"); //энкаутеры вернём
			chrDisableReloadToLocation = true;
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition.l1 = "location";
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition.l1.location = "Curacao";
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition = "Fr2Letter_FightWithGaleon";
			AddQuestRecord("Fra_Line_2_DelivLetter", "4");
            for (i=1; i<=2; i++)
            {
				sld = characterFromId("Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetHP(sld, 200, 200);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetPlayerType(pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Драка с мужем де Лейва. Квест №3 **********************************
 		case "Step_F3_1":
			dialog.text = "No, whatever you like... Someone else's house is broken into in the middle of the night "+ GetSexPhrase("man","some strange girl") +", а потом спрашивает: 'А в чём дело?!'\n"+
				          "Don't act like an idiot! My wife is locked up, I found this damn ring on her.'Augeron.";
			link.l1 = "Everything is clear... Well, I will do my best to treat you to the dish that you have prepared for me today.";
    		link.l1.go = "Step_F3_2";
		break;
 		case "Step_F3_2":
			dialog.text = "Let's start the meal!";
			link.l1 = "Let's start, perhaps...";
    		link.l1.go = "Step_F3_3";
		break;
 		case "Step_F3_3":
			LAi_LocationFightDisable(loadedLocation, false);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetPlayerType(pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Месть Анне де Лейва. Квест №5 **********************************
 		case "Step_F5_1":
			dialog.text = "I got a letter from Havana from my friend Inez de las Sierra. The Governor-General of Havana has launched an investigation into my husband's death and is convinced that I am responsible for it. Oh, it is! But my compatriots are plotting revenge, I'm facing death or kidnapping, and I don't know what's worse.\n"+
				          ""+ GetSexPhrase("Sir","Miss") +", I'm asking you to go to Havana and find out how serious this is.";
			link.l1 = "Madam, you can count on me.";
    		link.l1.go = "exit";
    		pchar.questTemp.State = "Fr5AnnaHant_toHavana";
			AddQuestRecord("Fra_Line_5_KillAnnaHanters", "2");
			sld = GetCharacter(NPC_GenerateCharacter("InesDeLasCierras", "girl_8", "woman", "towngirl", 10, SPAIN, -1, false));
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			sld.name = "Ines";
			sld.lastname = "de Las Sierras";
			sld.greeting = "Gr_Dama";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Havana_houseSp2", "goto","goto2");
		break;
 		case "Step_F5_2":
			dialog.text = "What's it to you?";
			link.l1 = "If I didn't care, I wouldn't ask, believe me...";
    		link.l1.go = "Step_F5_3";
		break;
 		case "Step_F5_3":
			dialog.text = "Maybe. And what do you want from us?";
			link.l1 = "I understand that you are plotting to avenge Don Jose?";
    		link.l1.go = "Step_F5_4";
		break;
 		case "Step_F5_4":
			dialog.text = "Tell me who you are immediately. Otherwise, I'll cut off your long tongue.";
			link.l1 = "I sent dear Don Jose to the next world. His servants also went there, following the master.";
    		link.l1.go = "Step_F5_5";
		break;
 		case "Step_F5_5":
			dialog.text = "Argh, luck is with us today! Half the work is done, brother, it remains to find that beast Anna, and we can go home.";
			link.l1 = "What about me?!";
    		link.l1.go = "Step_F5_6";
		break;
 		case "Step_F5_6":
			dialog.text = "And you're gone... Come on, brother, let's get rid of "+ GetSexPhrase("this bastard","this trash") +"!";
			link.l1 = "I disagree with this interpretation of my being! Well, let's get started...";
    		link.l1.go = "Step_F5_7";
		break;
 		case "Step_F5_7":
			LAi_LocationDisableOfficersGen("Mayak10", false); //офицеров пускать
			pchar.questTemp.State = "Fr5AnnaHant_GoodWork";
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak10")], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=2; i++)
            {
				LAi_group_MoveCharacter(characterFromId("DeLeivaBrother_"+i), "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_F5_8":
			dialog.text = "I would gladly give up this kind of reverence.";
			link.l1 = "You are not in danger anymore, believe me. I managed to convince these brave Castilians...";
    		link.l1.go = "Step_F5_9";
		break;
 		case "Step_F5_9":
			dialog.text = "Ah, "+ GetSexPhrase("senor","senorita") +" " + pchar.name + ", how can I thank you?";
			link.l1 = "Donna Anna, I ask you to take care of Monsieur d'Ogeron, he deserves it.";
    		link.l1.go = "Step_F5_10";
		break;
 		case "Step_F5_10":
			dialog.text = "I will certainly fulfill your request, you can no longer worry about Bertrand's mental health.";
			link.l1 = "Madam, you have done all the filibusters a great service. I guess we're even.";
			Pchar.quest.Fr3_AfterAnna_IKnowYou.over = "yes";
    		link.l1.go = "exit";
			npchar.LifeDay = 0;
		break;
//********************************* Франсуа Олоне. Квест №6 **********************************
 		case "Step_F6_1":
			dialog.text = "A-a-a! Well, that makes a difference. Make yourself comfortable while I read the letter.";
			link.l1 = "By the way, monsieur, I want to inform you that the Spaniards were extremely interested in this letter. They even dispatched a warship to intercept my ship.";
    		link.l1.go = "Step_F6_2";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
		break;
 		case "Step_F6_2":
			dialog.text = "I suppose since you're here, the Spanish won't be waiting for their warship anytime soon, haha! Yes, they sleep and see how to prove the French Governor-General's connection to the freebooters. So, having delivered the letter in one piece, you have rendered both me and Monsieur d'Ogeron a great service. The reward will be appropriate. By the way, how would you like it?";
			link.l1 = "In what sense?";
    		link.l1.go = "Step_F6_3";
		break;
 		case "Step_F6_3":
			dialog.text = "I can give you a bag of gold. And I can offer to participate in an interesting business. In this letter, the Governor-General informs that there is now gold worth at least two hundred thousand reais in the fort of Cumana. There are three ships in my flotilla, and their captains are my companions. Join us and, according to the laws of the Brethren, we will divide the loot into four. Well, how is it?";
			link.l1 = "I prefer the first option.";
    		link.l1.go = "Step_F6_WantMoney";
			link.l2 = "What kind of corsair will refuse a hot, but profitable business! Of course I'm with you!";
    		link.l2.go = "Step_F6_4";
			SaveCurrentQuestDateParam("questTemp");
		break;
 		case "Step_F6_WantMoney":
			dialog.text = "Whatever you say. Here is your reward.";
			link.l1 = "Thank you, Francois. Well, now, I think I'll leave for Tortuga...";
    		link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddMoneyToCharacter(pchar, 10000);
			pchar.questTemp.State = "Fr6Olone_TakeMoney";
			AddQuestRecord("Fra_Line_6_Olone", "2");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("","a"));
		break;
 		case "Step_F6_4":
            if (GetCompanionQuantity(pchar) == 1)   // Заставляем геймера избавиться от взятых кубиков.
            {
				if (GetQuestPastDayParam("questTemp") < 6)
				{
					dialog.text = "Well, you're ready to take a place in our squadron. Welcome and forward to Cumana!";
					link.l1 = "Very good! Francois, what is the action plan for this company?";
    				link.l1.go = "Step_F6_5";
				}
				else
				{
					dialog.text = "Well, where have you been for so long?";
					link.l1 = "Yes, I was getting rid of ships like you said.";
    				link.l1.go = "Step_F6_7";
				}
            }
            else
            {
				dialog.text = "Colleague, but I can take you into this case alone, on the condition that your share is a fourth part. I don't need any more companions. So get rid of the extra ships if you want to participate. And hurry up!";
				link.l1 = "Okay, Francois, I'll be back soon.";
    			link.l1.go = "exit";
				link.l2 = "No, I don't agree to this arrangement. Therefore, I think I'd better take my money...";
    			link.l2.go = "Step_F6_WantMoney";
				NextDiag.TempNode = "Step_F6_4";
             }
		break;
 		case "Step_F6_5":
			dialog.text = "The plan is quite simple. We go there and take Cumana by storm. Then we find the gold, divide it and run away each to his own business.";
			link.l1 = "Excellent. Well, I'm ready.";
    		link.l1.go = "Step_F6_6";
		break;
 		case "Step_F6_6":
			dialog.text = "Then go to Cumana, and as soon as possible!";
			link.l1 = "Very good, let's start...";
    		link.l1.go = "Step_F6_GoOn";
		break;
		case "Step_F6_GoOn":
			//==> формируем эскадру
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
			CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 5, false);
			for (i=1; i<=2; i++)
			{
                sld = GetCharacter(NPC_GenerateCharacter("Captain_"+i, "officer_"+(rand(42)+1), "man", "man", 20, FRANCE, -1, true));
                FantomMakeCoolSailor(sld, SHIP_CORVETTE, "", CANNON_TYPE_CANNON_LBS24, 70, 80, 40);
                FantomMakeCoolFighter(sld, 20, 90, 70, BLADE_LONG, "pistol4", 120);
				sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				sld.CompanionEnemyEnable = false;
				sld.Abordage.Enable = false; // НЕЛЬЗЯ!
				sld.RebirthPhantom = true;
                SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.DeckDialogNode = "HaveHotBussines";
				SetCharacterRemovable(sld, false);
				LAi_LoginInCaptureTown(sld, true);
			}
            // ==> текущая дата, у генерал-губернатора Куманы потом сверим
            SaveCurrentQuestDateParam("questTemp");
            pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
            // ==> капитулянтская нода губернатору Куманы
			characters[GetCharacterIndex("Cumana_Mayor")].dialog.captureNode = "FraLine6Quest_Attack";
			npchar.DeckDialogNode = "HaveHotBussines";
			AddQuestRecord("Fra_Line_6_Olone", "3");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("xia","as"));
			DialogExit();
		break;
		case "Step_F6_7":
			dialog.text = "Got rid of?";
			link.l1 = "Yes, of course.";
    		link.l1.go = "Step_F6_8";
		break;
 		case "Step_F6_8":
			dialog.text = "I congratulate you on your successful rid, but there will be no campaign to Cumana.";
			link.l1 = "How will it not be?!";
    		link.l1.go = "Step_F6_9";
		break;
 		case "Step_F6_9":
			dialog.text = "Very simple, "+ GetSexPhrase("mon cher","darling") +". There is no gold in Cuman anymore, it has been taken out. So in our case, the lost time cost us 200 thousand reais. That's it...";
			link.l1 = "Damn, it's annoying... Well, then I'll take the money I'm owed for delivering the letter.";
    		link.l1.go = "Step_F6_WantMoney";
		break;
 		case "HaveHotBussines":
			dialog.text = "Captain, we have no time to waste, we urgently need to take Cumana before the gold evaporates.";
			link.l1 = "Yes, Francois, we will definitely make it...";
    		link.l1.go = "exit";
		break;
 		case "Step_F6_10":
			dialog.text = "I don't like your answer, " + pchar.name + ".";
			link.l1 = "We're too late, Francois. The fact is that the money has already gone to the Old World about a week ago. It was all useless...";
    		link.l1.go = "Step_F6_11";
		break;
 		case "Step_F6_11":
			dialog.text = "I don't think so, "+ GetSexPhrase("mon cher","darling") +". And I think it's because of you that we didn't make it in time!";
			link.l1 = "A controversial statement, friend Olone. Very controversial...";
    		link.l1.go = "Step_F6_12";
		break;
 		case "Step_F6_12":
			dialog.text = "I think it's time to resolve all disputes. To arms, "+ GetSexPhrase("sir","miss") +"! Let's taste your blood...";
			link.l1 = "God knows, I don't want to fight you!";
    		link.l1.go = "Step_F6_13";
		break;
 		case "Step_F6_13":
			dialog.text = "Then I will kill you like a cowardly dog! Last chance - take up arms.";
			link.l1 = "All right, Francois or whatever your name is... You asked for it.";
    		link.l1.go = "Step_F6_fight";
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "4");
		break;
 		case "Step_F6_fight":
			NPChar.LifeDay = 0;
			DeleteAttribute(NPChar, "RebirthPhantom");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Captain_"+i);
				sld.LifeDay = 0;
				DeleteAttribute(sld, "RebirthPhantom");
			}
			chrDisableReloadToLocation = true;
			pchar.questTemp.State = "Fr6Olone_OloneIsDead";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_F6_14":
			if (sti(pchar.money) >= 200000)
			{
				dialog.text = "Excellent, companion! We divide the money and go home.";
				link.l1 = "Goodbye, Olone. I'll manage a little more in the city...";
    			link.l1.go = "Step_F6_15";
				link.l2 = "But I think I don't have to share with you. I've done all work!";
    			link.l2.go = "Step_F6_20";
			}
			else
			{
				dialog.text = "You found money, and you don't have them available. Did you try to trick?!";
				link.l1 = "What are you, Francois?!";
    			link.l1.go = "Step_F6_17";
			}
		break;
 		case "Step_F6_15":
			dialog.text = "Take care of yourself, but don't stay too long - there may be Spaniards nearby.";
			link.l1 = "Okay, Francois. Be healthy...";
    		link.l1.go = "Step_F6_16";
			AddMoneyToCharacter(pchar, -150000);
		break;
 		case "Step_F6_16":
			chrDisableReloadToLocation = true;
			NPChar.LifeDay = 0;
			DeleteAttribute(NPChar, "RebirthPhantom");
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("Captain_"+i)
				if (iTemp > 0)
				{
					sld = &characters[iTemp];
					sld.LifeDay = 0;
					DeleteAttribute(sld, "RebirthPhantom");
				}
			}
			AddQuestRecord("Fra_Line_6_Olone", "5");
			pchar.questTemp.State = "Fr6Olone_OloneIsLive";
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "CanFightCurLocation", -1);
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], true);
            DialogExit();
		break;
 		case "Step_F6_17":
			dialog.text = "And I think you're being tricky, "+ GetSexPhrase("buddy","girlfriend") +"... But there's a way to find out-get your blade out.";
			link.l1 = "Fight?";
    		link.l1.go = "Step_F6_18";
		break;
 		case "Step_F6_18":
			dialog.text = "That's right. The rat must be punished...";
			link.l1 = "Okay, you asked for it.";
    		link.l1.go = "Step_F6_fight";
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "6");
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], false);
			//==> кэпов в подмогу Олоне, пенальти за попытку сшустрить.
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("Captain_"+i)
				if (iTemp > 0)
				{
					sld = &characters[iTemp];
					LAi_SetWarriorType(sld);
					ChangeCharacterAddress(sld, "Cumana_town", LAi_FindRandomLocator("goto"));
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
		break;
 		case "Step_F6_20":
			dialog.text = "So that's how it is?! Well, then prepare for the worst...";
			link.l1 = "Always ready, Francois...";
    		link.l1.go = "Step_F6_21";
		break;
 		case "Step_F6_21":
			NPChar.LifeDay = 0;
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "8");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("","a"));
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], false);
			//==> кэпов в подмогу Олоне, пенальти за попытку сшустрить.
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("Captain_"+i)
				if (iTemp > 0)
				{
					sld = &characters[iTemp];
					sld.LifeDay = 0;
					DeleteAttribute(sld, "RebirthPhantom");
					LAi_SetWarriorType(sld);
					ChangeCharacterAddress(sld, "Cumana_town", LAi_FindRandomLocator("goto"));
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			chrDisableReloadToLocation = true;
			pchar.questTemp.State = "Fr6Olone_OloneIsDead";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Маркиз Бонрепо. Квест №8 **********************************
 		case "Step_F8_1":
			dialog.text = "Aha, finally! And I was already starting to worry. Governor-General d'Ogeron has told me a lot of flattering things about you. I hope that you will fully justify his and my trust. And keep in mind: everything you hear here should never be known to anyone but you.";
			link.l1 = "I warned about this...";
    		link.l1.go = "Step_F8_2";
		break;
 		case "Step_F8_2":
			dialog.text = "Great! So, to the point\n"+
				          "The current situation in European politics is very difficult. Another trade war is brewing between England and Holland, and our great Sun King Louis XIV begins a devolution war with Spain.";
			link.l1 = "Excuse me, Marquis... What kind of war? Revolutionary?!";
    		link.l1.go = "Step_F8_3";
		break;
 		case "Step_F8_3":
			dialog.text = "Um... yeah, I wouldn't know a simple privateer.\n"+
				          "Devolution War is a war for hereditary rights over certain territories. Such for France is undoubtedly the part of Flanders and Burgundy, now under Spanish rule. This is a good deed, as the Dutch have been seeking for a hundred years to throw off the yoke of the Spanish devils dressed in church robes.\n"+
						  "For the successful conduct of the war, we are in dire need of Dutch money, so it is necessary to prevent the British from attacking their colonies. The task is supervised personally by Jean-Baptiste Colbert, I hope you know who this is...";
			link.l1 = "How do I owe to do it?";
    		link.l1.go = "Step_F8_4";
		break;
 		case "Step_F8_4":
			dialog.text = "The Dutch are able to stand up for themselves if the Governor-General of Jamaica, Sir Thomas Madiford, is not reinforced. And in these waters they can only count on the help of famous corsairs, who have weight and authority in the Coast Brotherhood.\n"+
				          "There are only three people who could seriously influence the course of the war: Henry Morgan in Jamaica, Jackman in a pirate settlement in Bermudes, John Morris in Trinidad. Your task is to meet with each of them and convince them not to attack Dutch colonies and ships in any case. For this Brethren, the main thing is profit, so spare no expense!";
			link.l1 = "And where do I owe to take these funds?";
    		link.l1.go = "Step_F8_5";
		break;
 		case "Step_F8_5":
			dialog.text = "I admit, you surprised me. You were recommended to me as an extremely smart and resourceful person! If I had these funds, why would I need your help? However, you have the right to refuse, but...";
			link.l1 = "But then what?";
    		link.l1.go = "Step_F8_6";
		break;
 		case "Step_F8_6":
			dialog.text = "Then I'll have to send you to jail. After all, you became the owner of state secrets! With such knowledge, disloyal people do not walk free.";
			link.l1 = "First you have to detain me, and it's not that easy!";
    		link.l1.go = "Step_F8_Fight";
			link.l2 = "Well, if the king can't do without my piastres, so be it, I'll help him!";
    		link.l2.go = "Step_F8_7";
		break;
 		case "Step_F8_Fight":
			CloseQuestHeader("Fra_Line_8_ThreeCorsairs");
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
            for (i=1; i<=4; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Guard_"+i, "Sold_fra_"+(rand(7)+1), "man", "man", 30, FRANCE, 0, true));
				FantomMakeCoolFighter(sld, 30, 65, 50, BLADE_LONG, "pistol3", 40);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
               	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
            }
			LAi_group_AttackGroup("FRANCE_CITIZENS", LAI_GROUP_PLAYER);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", 10.0);
			NPChar.LifeDay = 0;
			pchar.questTemp.State = "QuestLineBreake";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "2");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_F8_7":
			dialog.text = "That's great! D'Ogeron was not mistaken about you. So, I'm waiting for you with good news.";
			link.l1 = "I'll do everything, Marquis.";
    		link.l1.go = "exit";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "3");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("","a"));
			pchar.questTemp.State = "Fr8ThreeCorsairs_toSeek";
			SaveCurrentQuestDateParam("questTemp");
            // ==>  Помещаем Моргана на Антигуа и даём ноду доступа к квестам
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
            QuestSetCurrentNode("Henry Morgan", "FraLine8_talk");
            sld = characterFromID("Henry Morgan");
            LAi_SetHuberStayType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
            LAi_SetLoginTime(sld, 0.0, 24.0);
            // ==>  Генерим и помещаем Джона Морриса в Бриджтаун и даём ноду доступа к квестам
            sld = GetCharacter(NPC_GenerateCharacter("John Morris", "bocman", "man", "man", 38, PIRATE, -1, false));
        	sld.name 	= "John";
        	sld.lastname = "Morris";
            sld.Dialog.Filename = "Quest\JohnMorris.c";
			sld.greeting = "Gr_HeadPirates";
           	LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
        	LAi_SetLoginTime(sld, 0.0, 24.0);
            ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "sit", "sit1");
            LAi_LocationFightDisable(&Locations[FindLocation("PortSpein_houseF2")], true);
            // ==>  Даём ноду доступа к квестам Джону Моррису
            QuestSetCurrentNode("John Morris", "FraLine8_talk");
            // ==>  Даём ноду доступа к квестам Джекмену
            QuestSetCurrentNode("Jackman", "FraLine8_talk");
            // ==>  Оформляем счётчик посещения корсаров, в итоге должен == 3
            pchar.questTemp.Count = "0";
		break;
 		case "Step_F8_9":
			dialog.text = "I must say that this was one of the most difficult diplomatic assignments I have given to anyone. A man who copes so brilliantly with such matters simply should not walk in commoners. Fortunately, I have been given the authority to welcome you "+ GetSexPhrase("baronial title","title of baroness") +"! France needs people like you!";
			link.l1 = "Uh... ah..."+ GetSexPhrase("Baronial title","Title of Baroness") +"? And what about the expenses that I spend on "+ GetSexPhrase("eu","esla") +"?";
    		link.l1.go = "Step_F8_10";
		break;
 		case "Step_F8_10":
			dialog.text = "The pirate will always be a pirate! Ha-ha!\n"+
				          "Believe me, "+ GetSexPhrase("sweetest","dear") +", I give you much more than despicable metal! I give you the honor and respect of the King himself! And now I dare not detain you, the Governor-General is waiting for you.'Augeron. It seems that he has some important business for you again... Goodbye.";
			link.l1 = "Goodbye, Intendant Bonrepo...";
    		link.l1.go = "Step_F8_11";
		break;
 		case "Step_F8_11":
			pchar.questTemp.State = "Fr8ThreeCorsairs_backGovernor";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "8");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("became a nobleman","became a noblewoman"));
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex1", GetSexPhrase("mu","y"));
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex2", GetSexPhrase("en","on"));
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 6.0);
			if (PChar.sex == "woman")
			{
			pchar.name = "The Baroness " + pchar.name;
			}
			else
			{
			pchar.name = "The Baron " + pchar.name;
			}
            DialogExit();
		break;
//********************************* Конец войне. Квест №12 **********************************
 		case "Step_F12_1":
			dialog.text = "So, as you already know, the devolution war with Spain is over. Spain is defeated!";
			link.l1 = "Yes, Marquis, excellent news.";
    		link.l1.go = "Step_F12_2";
		break;
 		case "Step_F12_2":
			dialog.text = "Your merits have been appreciated - Louis himself knows about you now...";
			link.l1 = "Marquis, to be honest, I would like a slightly different assessment of my services to France.";
    		link.l1.go = "Step_F12_3";
		break;
 		case "Step_F12_3":
			dialog.text = "What do you mean?";
			link.l1 = "I'm talking about monetary compensation for my expenses in this war. I carried the burden of fighting the Spanish on my own the burden of fighting the Spanish and want to receive compensation.";
    		link.l1.go = "Step_F12_4";
		break;
 		case "Step_F12_4":
			dialog.text = "Listen, you have become nobles"+ GetSexPhrase("other","coy") +"The Louvre knows about you! Isn't that enough for you?!";
			link.l1 = "For my ego, it's more than a lot. But I'm talking about something else - money...";
    		link.l1.go = "Step_F12_5";
		break;
 		case "Step_F12_5":
			dialog.text = ""+ GetSexPhrase("Baron","Baronessa") +", don't make an idiot of me, I don't require you to report on the trophies captured in the cities. This is your fee.";
			link.l1 = "Hmm, now it's clear...";
    		link.l1.go = "Step_F12_6";
		break;
 		case "Step_F12_6":
			dialog.text = "It's very good that we clarified all the nuances, "+ GetSexPhrase("Baron","Baronessa") +". And now to the point - the Soleil Royal is being withdrawn from your squadron.";
			link.l1 = "I see...";
    		link.l1.go = "Step_F12_7";
		break;
 		case "Step_F12_7":
			dialog.text = "In a month, I'm sending this magnificent ship to the Old World. So I am grateful to you for keeping it in its proper form.";
			link.l1 = "Thank you for your gratitude, Marquis...";
    		link.l1.go = "Step_F12_8";
		break;
 		case "Step_F12_8":
			dialog.text = "Don't, "+ GetSexPhrase("Baron","Baronessa") +"... Well, I dare not detain you any longer, goodbye.";
			link.l1 = "Have a nice day, Marquis.";
    		link.l1.go = "exit";
			npchar.LifeDay = 0;
			pchar.questTemp.State = "EndOfQuestLine";
			bWorldAlivePause   = false; // Конец линейки
			AddQuestRecord("Fra_Line_12_EndOfWar", "2");
			AddQuestUserData("Fra_Line_12_EndOfWar", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("Fra_Line_12_EndOfWar", "sSex1", GetSexPhrase("mu","y"));
			CloseQuestHeader("Fra_Line_12_EndOfWar");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			//==> в течение месяца Солей Руаяль можно взять себе.
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");
			Group_SetType("SoleiRoyal", "war");
			Group_AddCharacter("SoleiRoyal", "SoleiRoyalCaptain");
			Group_SetGroupCommander("SoleiRoyal", "SoleiRoyalCaptain");
			Group_SetAddress("SoleiRoyal", "Guadeloupe", "Quest_ships", "quest_ship_1");
			SetTimerCondition("Fr12EndOfWar_TakeOutShip", 0, 0, 30, false);
			AddTitleNextRate(sti(NPChar.nation), 5);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			AddCharacterExpToSkill(pchar, "Repair", 630);
			AddCharacterExpToSkill(pchar, "Sneak", 490);
			AddCharacterExpToSkill(pchar, "FencingLight", 530);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 530);
			AddCharacterExpToSkill(pchar, "Fencing", 530);
			AddCharacterExpToSkill(pchar, "Pistol", 530);
			AddCharacterExpToSkill(pchar, "Fortune", 660);
			AddCharacterExpToSkill(pchar, "Accuracy", 520);
			AddCharacterExpToSkill(pchar, "Grappling", 750);
			//слухи
			AddSimpleRumour("They say that you are now a "+ GetSexPhrase("Baron","Baronessa") +"! You are the darling of fate, Captain...", sti(npchar.nation), 5, 1);
		break;
    }
}
