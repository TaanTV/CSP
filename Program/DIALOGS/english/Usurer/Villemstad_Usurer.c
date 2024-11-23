// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
   	float locx, locy, locz;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Just recently you tried to ask me a question...", "Well, let me guess... Nothing significant again?",
                          "Listen, I'm handling finances, not answering questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "You guessed it, I'm sorry...", "I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> англ.линейка квест №4 Разведмиссию в Кюрасао
			if (pchar.questTemp.State == "Intelligence_Curacao_toYozef")
            {
                link.l1 = "I wanted to ask you for help in one case. This assistance will be generously paid for.";
                link.l1.go = "Step_E4_1";
            }
			if (pchar.questTemp.State == "Intelligence_Curacao_NoMoney_Yozef")
            {
                link.l1 = "I would talk about deal for 100000 coins.";
                link.l1.go = "no_money";
            }
            if (pchar.questTemp.State == "Inquisition_toCuracao" || pchar.questTemp.State == "Inquisition_afterFrancisco" )// квест №2 голл. линейки.
            {
                if (!CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
        			dialog.text = "What do you need?";
        			link.l1 = "The Holy Inquisition gives you the Pope's forgiveness for only 50,000. What is it? Why do I not see tears of joy in my eyes?";
        			link.l1.go = "Step_S2_1";
                }
                else
                {
                    if (CheckPassengerInCharacter(pchar, "JansenDeFonceicao"))
                    {
                        dialog.text = "It's you again! Get out of here!";
            			link.l1 = "I'm tired of you! Shut your mouth. Now I dictate the terms, and you listen carefully, comprehend, and already begin to regret that you did not immediately heed my words.";
            			link.l1.go = "Step_S2_5";
                    }
                    else
                    {
                        if (pchar.questTemp.State.Usurer != "Ok")
                        {
                            dialog.text = "What, you haven't told me everything yet"+ GetSexPhrase("told", "told") +"about the Pope's forgiveness?";
                			link.l1 = "Okay, Josef, let's talk more...";
                			link.l1.go = "exit";
                        }
                        else
                        {
                            dialog.text = "What else do you need, "+ GetSexPhrase("damn bloodsucker, Jesuit henchman", "damn bloodsucker, Jesuit henchman") +" ...";
                			link.l1 = "What emotions, what courage! Great...";
                			link.l1.go = "exit";
                        }
                    }
                }
            }
			//пиратка, квест №5
			if (pchar.questTemp.piratesLine == "PL5Hunter_toVillemstad")
            {
				link.l1 = "Daddy, don't you need to shake off debts from someone?!";
				link.l1.go = "Step_P5_1";
			}
		break;
//********************** Английская линейка, квест №4 "Exploration in Curacao" ************************
		case "Step_E4_1":
			dialog.text = "Tell me what you need?";
			link.l1 = "I'm ready to pay a lot for information. I need to know about the plans of the Governor-General of Curacao regarding the British.";
			link.l1.go = "Step_E4_2";
		break;
		case "Step_E4_2":
			dialog.text = "I hope you understand what you are asking for.";
			link.l1 = "I hope you understand that I will be very "+ GetSexPhrase("generous", "generous") +".";
			link.l1.go = "Step_E4_3";
		break;
		case "Step_E4_3":
			dialog.text = "100000 coins and I'll tell you everything I know.";
			link.l1 = "I'm ready to deposit the required amount.";
			link.l1.go = "agree_to_pay";
			link.l2 = "I don't have enough money with me, but I'll definitely come back later.";
			link.l2.go = "no_money_now";
			link.l3 = "Isn't it too greasy, dirty pig?";
			link.l3.go = "fack_yozef";
		break;
		case "agree_to_pay":
            if (sti(pchar.money) >= 100000)
            {
        		dialog.text = "Well, I can tell you the following: about an hour ago, at the residence of Peter Stuyvesant, the governor-General of this island, a military council ended on just your question - the participation of the Dutch colonies in the trade war with England. I was not present at the meeting itself, but I know that as a result of this, the Governor-General's messenger is going somewhere on an urgent errand. A brig is waiting for a messenger in the raid\n"+
                         "You look like a pirate, and it won't be difficult for you to take a Dutch brig. So hurry up before he disappears over the horizon. And more... I don't know you. Goodbye.";
        		link.l1 = "Here's your money. And I don't know you either, and I don't want to know. Goodbye.";
        		link.l1.go = "exit";
        		AddMoneyToCharacter(pchar, -100000);
        		AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "3");
        		pchar.questTemp.State = "Intelligence_Curacao_GaveMoneyYozef"; // заглушка на повторный вывод данного пункта в меню.
                Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1 = "location";
                Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1.location = "Curacao";
                Pchar.quest.Intelligence_Curacao_GoToShore.win_condition = "Intelligence_Curacao_GoToShore";
                Log_QuestInfo("The brig is installed in the bay.");
            }
            else
            {
        		dialog.text = "Hmm, it looks like you don't have enough money after all. From now on, please don't mess with my head. I am waiting for you with the required amount.";
        		link.l1 = "Okay, I got you.";
        		link.l1.go = "exit";
        		pchar.questTemp.State = "Intelligence_Curacao_NoMoney_Yozef";
        		//ChangeCharacterReputation(pchar, -1); TO_DO eddy
            }
		break;
		case "no_money_now":
			dialog.text = "Well, get the required amount. I'll be waiting for you.";
			link.l1 = "I think I'll be fine soon.";
			link.l1.go = "exit";
            if (pchar.questTemp.State != "Intelligence_Curacao_NoMoney_Yozef")
            {
                AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "4");
            }
            pchar.questTemp.State = "Intelligence_Curacao_NoMoney_Yozef";
		break;
		case "no_money":
			dialog.text = "Did you get the money? Where's my 100000?";
			link.l1 = "Yes, I have the money and I'm ready to give them to you. So what did you find out?";
			link.l1.go = "agree_to_pay";
			link.l2 = "Not yet, but I will definitely get them and come back later.";
			link.l2.go = "no_money_now";
			link.l3 = "Isn't it too greasy, dirty pig?";
			link.l3.go = "fack_yozef";
		break;
		case "fack_yozef":    // посыл Йозефа с попыткой замочить
			dialog.text = "You are cheeky! I'll ask you to get out of my house immediately!";
			link.l1 = "Damn you, you damn bloodsucker! I'm going to gut you now!";
			link.l1.go = "Step_E4_4";
		break;
		case "Step_E4_4":
			dialog.text = "It wasn't there, "+ GetSexPhrase("bastard", "trash") +". Security, come to me!!!";
			link.l1 = "Damn it!";
			link.l1.go = "Step_E4_5";
		break;
		case "Step_E4_5":
            pchar.questTemp.State = "Intelligence_Curacao_FightGard";
            LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_bank")], false);
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "5");
	    AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("", "a"));
	    AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex1", GetSexPhrase("xia", "as"));
            LAi_NoRebirthEnable(npchar);
            LAi_group_Register("EnemyFight");
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (int i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("HolSolder"+i, "sold_hol_"+i, "man", "man", 20, HOLLAND, 0, true));
                FantomMakeCoolFighter(sld, 20, 70, 60, BLADE_LONG, "pistol2", 40);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Villemstad_bank", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_SetCheckMinHP(pchar, 10, true, "Intelligence_Curacao_KickYozef");
            LAi_SetPlayerType(pchar);
            LAi_SetFightMode(pchar, true);
            Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1 = "location";
            Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1.location = "Curacao";
            Pchar.quest.Intelligence_Curacao_GoToShore.win_condition = "Intelligence_Curacao_GoToShore";
			DialogExit();
		break;
//********************** Испанская линейка, квест №2 "The Inquisition" ************************
		case "Step_S2_1":
			dialog.text = "You've got me confused with someone else. There is no blame for me!";
			link.l1 = "That's what you think, but the order has a different opinion. So you'll have to pay the money.";
			link.l1.go = "Step_S2_2";
		break;
		case "Step_S2_2":
			dialog.text = "I won't pay you anything! And if you don't get out of my house right now, then I'll call the servants!";
			link.l1 = "Well, as you know, it will be worse for you...";
			link.l1.go = "Step_S2_4";
		break;
		case "Step_S2_4":
			dialog.text = "Are you threatening me"+ GetSexPhrase("took it into your head", "took it into your head") +"?";
			link.l1 = "No, why not. It's okay, Joseph...";
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_2_Inquisition", "5");
			pchar.questTemp.State.Usurer = 1;
		break;
		case "Step_S2_5":
			dialog.text = "And why should I listen to the nonsense you're talking about?";
			link.l1 = "It's simple, Josef - your son is in my hands. Am I speaking convincingly? Or do you need to show proof? Well, for example, I can bring a severed finger, or your son's ear. Do you want to?";
			link.l1.go = "Step_S2_6";
		break;
		case "Step_S2_6":
			dialog.text = "You... Don't, I believe you... If I give the money back now, where's the guarantee that you won't deal with him?";
			link.l1 = "And there is no such guarantee. Stay at least a little bit in the shoes of those whom you drove to despair. Find out how much a pound is worth. And stop talking, give me the money.";
			link.l1.go = "Step_S2_7";
		break;
		case "Step_S2_7":
			dialog.text = "Take it. But I won't forget it.";
			link.l1 = "No problem. Remember. Remember that the Order is watching you too...";
			link.l1.go = "Step_S2_8";
		break;
		case "Step_S2_8":
            AddQuestRecord("Spa_Line_2_Inquisition", "10");
			ReleasePrisoner(characterFromId("JansenDeFonceicao"));
            AddMoneyToCharacter(pchar, 50000);
            pchar.questTemp.State.Usurer = "Ok"; //бабки получены
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
//********************** Пиратская линейка, квест №5 ОГЗ ************************
		case "Step_P5_1":
			dialog.text = "No. No need. He, you so-called debt collectors, like all twins, "+ GetSexPhrase("even your speech is the same", "even your speech is the same. Even though you are a girl") +". That's exactly how Avory talks.";
			link.l1 = "John Avory?! So this is my buddy. Is he still in town? Where can I find him?";
			link.l1.go = "Step_P5_2";
		break;
		case "Step_P5_2":
			dialog.text = "I have no idea. He's a free man, he goes where he pleases. As for the fact that he is still in Willemstad, it is unlikely, there is no work left for him here. You are "+ GetSexPhrase("buddy", "friend") +"John, you must understand that you need to look for him where rum flows like a river - in taverns!";
			link.l1 = "Ha! Of course, who would doubt it... But are you sure you don't remember anything like that, where could he have gone? Did he say something?";
			link.l1.go = "Step_P5_3";
		break;
		case "Step_P5_3":
			pchar.questTemp.piratesLine.Q5.city_1 = GetQuestNationsCity(ENGLAND);
			dialog.text = "He said he was going to the British now. Like about " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Voc") + "there was a speech, but I won't say for sure.";
			link.l1 = "You said you had no idea. Well, thank you!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "2");
			AddQuestUserData("Pir_Line_5_Hunter", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_1) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFirst";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

