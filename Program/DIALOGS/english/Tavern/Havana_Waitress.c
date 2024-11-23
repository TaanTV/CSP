// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
    float locx, locy, locz, fTemp;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, " + GetAddress_Form(NPChar) + "?", "Whatever you want, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hmm, aren't you bothering me, " + GetAddress_Form(NPChar) + "? ", "Again with strange questions? Girl, would you drink rum, or something...") +"", "This is the third time you've been talking about some issue this day..."+ GetSexPhrase("Are these tokens of attention?", "") +"",
                          "Are you going to ask me again, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I have nothing to talk about right now."), "No, no, you're beautiful...",
                      "No way, dear, sclerosis...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
            if (pchar.questTemp.State == "Sp4Detection_FoundLetter")
            {
    		    dialog.text = "I'm listening to you, "+ GetSexPhrase("senor", "senorita") +".";
    			link.l1 = "Listen, "+ GetSexPhrase("beauty", "baby") +", have you noticed anything unusual in the tavern lately?";
    			link.l1.go = "Step_S4_1";
			}
            if (pchar.questTemp.State == "Fr3TakeAnna_toHavana")
            {
    		    dialog.text = "I'm listening to you, "+ GetSexPhrase("senor", "senorita") +".";
    			link.l1 = "Dear girl, if your soul is as angelic as your appearance, then you certainly won't refuse to help me.";
    			link.l1.go = "Step_F3_1";
			}
            if (pchar.questTemp.State == "Fr3TakeAnna_WaitOneDay")
            {
				if (GetQuestPastDayParam("questTemp") > 0)
				{
    				dialog.text = "Ah, here you are, "+ GetSexPhrase("senor", "senorita") +"! Just in time.";
    				link.l1 = "Yeah, I see that you handed over the ring...";
    				link.l1.go = "Step_F3_4";
				}
				else
				{
    				dialog.text = ""+ GetSexPhrase("Senor", "Senorita") +", I haven't completed your assignment yet. Wait, be patient, please...";
    				link.l1 = "Okay, darling, I'm waiting...";
    				link.l1.go = "exit";
				}
			}
            // <== Проверяем поле состояния квестов.
		break;
//========================== Исп. линейка, квест №4. Расследование убийства ==================================
 	 	case "Step_S4_1":
			dialog.text = "No, "+ GetSexPhrase("senor", "senorita") +", it's all right.";
			link.l1 = "Have you noticed any strange people, anything so unusual?";
			link.l1.go = "Step_S4_2";
        break;
 	 	case "Step_S4_2":
			dialog.text = "There are a lot of strange people in our tavern, you can't even mention them all...";
			link.l1 = "Have you seen any strangers here lately?";
			link.l1.go = "Step_S4_3";
        break;
 	 	case "Step_S4_3":
			dialog.text = "There are different people... Listen, "+ GetSexPhrase("senor", "senorita") +", I need to work. Don't bother me, please.";
			link.l1 = "I needed to interfere. Do you know something about the murder in the house of the Commandant of Havana, Don Jose Ramirez de Leyva?";
			link.l1.go = "Step_S4_4";
        break;
 	 	case "Step_S4_4":
			dialog.text = "(pales, pause) I know...";
			link.l1 = "So, I am investigating this case on behalf of the Governor General of Havana. I see that you know something. Answer me immediately, or you'll end up in jail today!";
			link.l1.go = "Step_S4_5";
        break;
 	 	case "Step_S4_5":
			dialog.text = "Okay, "+ GetSexPhrase("senor", "senorita") +", I'll tell you everything! Just promise me that you won't hurt me.";
			link.l1 = "I promise that if you are not a murderer, I will not do anything to you.";
			link.l1.go = "Step_S4_6";
        break;
 	 	case "Step_S4_6":
			dialog.text = "I am not a murderer, "+ GetSexPhrase("senor", "senorita") +", of course not...";
			link.l1 = "Yeah, it's not a waiter's job to take down five big men in full combat gear. Now tell me everything you know.";
			link.l1.go = "Step_S4_7";
        break;
 	 	case "Step_S4_7":
			dialog.text = ""+ GetSexPhrase("Senor", "Senorita") +", I think I know the man who killed Don Jose and took Donna Anna away...";
			link.l1 = "Who is he?";
			link.l1.go = "Step_S4_8";
        break;
 	 	case "Step_S4_8":
			dialog.text = "He showed up unexpectedly, I don't remember seeing him before. Now, this stranger, a Frenchman said, asked me to give Donna a ring. I told you what was wrong with that? Donna got the ring, and for a minute, she didn't say anything, just stared at the wall with no eyes. Then she told me to wait, wrote a note and told me to give it to the Frenchman.\n"+
                          "When I received the note, I suspected something was wrong. But I gave it to the Frenchman anyway, because it's obvious that this is a terrible person. For such a person, sending a man to his forefathers is easier than drinking a glass of wine. And his eyes are as sharp as the point of a sword. Most likely, this is one of those devils that we call ladrons, and they call themselves filibusters.";
			link.l1 = "Damn it! So you're the one who notified Donna Anna... What else do you know?";
			link.l1.go = "Step_S4_9";
        break;
 	 	case "Step_S4_9":
			dialog.text = "Nothing more, "+ GetSexPhrase("senor", "senorita") +". This man took the note and left. And in the morning, the news spread through the city that Don Juan was dead. That's when I figured out what was going on. I just didn't tell anyone, I was afraid that I would be considered an accomplice to the crime. "+ GetSexPhrase("Senor", "Senorita") +", you promised not to do anything bad to me. Please keep your word!";
			link.l1 = "Okay, I'll leave you free. Although it is clear that you brought the murderer to Don Jose's house. However, I believe that if not through you, then somehow he would have got to Donna Anna anyway. So live for now...";
			link.l1.go = "Step_S4_10";
        break;
 	 	case "Step_S4_10":
			dialog.text = "Thank you, "+ GetSexPhrase("senor", "senorita") +", may the Lord protect you! I'm very sorry that it happened like this, but I'm not to blame for anything!";
			link.l1 = "If you see this Frenchman again, call the guards immediately. Although, it is unlikely that he will appear here again.";
			link.l1.go = "exit";
            pchar.questTemp.State = "Sp4Detection_toGovernor";
            AddQuestRecord("Spa_Line_4_MirderDetection", "3");
        break;
//========================== Фр. линейка, квест №3. Увезти донну Анну ==================================
 	 	case "Step_F3_1":
			dialog.text = "Well, really ..."+ GetSexPhrase("It is impossible to refuse anything to such a noble caballero!", "I will help such a prominent woman, of course.") +"";
			link.l1 = "I need you to take this ring to Donna Anna Ramirez de Leyva, the commandant's wife. But only in such a way that not a single living soul knows about it!";
			link.l1.go = "Step_F3_2";
        break;
 	 	case "Step_F3_2":
			dialog.text = "Oh, Donna Anna has so many beautiful rings, why does she need another one? And the poor girl has nothing...";
			link.l1 = "I know what you mean! Well, keep 500 coins, and you'll get the same amount when you bring the answer from Donna Anna. With this money, you can buy yourself as much jewelry as you want.";
			link.l1.go = "Step_F3_3";
			AddMoneyToCharacter(pchar, -500);
        break;
 	 	case "Step_F3_3":
			dialog.text = "Thank you, "+ GetSexPhrase("senor", "senorita") +"! You'll have to wait a day or two. I have to turn in my shift and find time to go to Senora de Leyva's house. And you need a suitable case - you can't just show up at their house...";
			link.l1 = "Very good, honey. I'm waiting for you...";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "DOjeronRing");
			pchar.questTemp.State = "Fr3TakeAnna_WaitOneDay";
			SaveCurrentQuestDateParam("questTemp");
			AddQuestRecord("Fra_Line_3_TakeAnna", "2");
        break;
 	 	case "Step_F3_4":
			dialog.text = "Yes, I did.";
			link.l1 = "Okay. Now tell me what she told you...";
			link.l1.go = "Step_F3_5";
        break;
 	 	case "Step_F3_5":
			dialog.text = "Is "+ GetSexPhrase("senor", "senorita") +" want to help poor girl?\n"+
				          "Oh, "+ GetSexPhrase("senor", "senorita") +"Please don't squeeze my hand so hard! I'll have bruises from your fingers later!";
			link.l1 = "Okay... Listen, I'm asking you to speak quickly and to the point. Don't pull the cat's tail, honey - you'll be safer...";
			link.l1.go = "Step_F3_6";
        break;
 	 	case "Step_F3_6":
			dialog.text = "Okay, "+ GetSexPhrase("senor", "senorita") +"... I gave her your ring. And you know what? When she saw him, she turned pale as a sheet.";
			link.l1 = "So what? What did she say?";
			link.l1.go = "Step_F3_7";
        break;
 	 	case "Step_F3_7":
			dialog.text = "Nothing special. She ordered me to wait, immediately wrote a note and handed it to me.";
			link.l1 = "Give me the note here!";
			link.l1.go = "Step_F3_8";
        break;
 	 	case "Step_F3_8":
			dialog.text = "Okay, "+ GetSexPhrase("senor", "senorita") +", just don't hurt me again... Here it is, take it.";
			link.l1 = "Well done, good girl. Don't be afraid, take some more money, buy yourself something... And keep your mouth shut, beautiful. Do you understand?";
			link.l1.go = "Step_F3_9";
        break;
 	 	case "Step_F3_9":
			dialog.text = "Understood, "+ GetSexPhrase("senor", "senorita") +", luckily I'm not a fool.";
			link.l1 = "Well, that's nice.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -500);
			AddQuestRecord("Fra_Line_3_TakeAnna", "3");
			AddQuestUserData("Fra_Line_3_TakeAnna", "sSex", GetSexPhrase("ate", "la"));
            ChangeItemDescribe("letter_open", "itmdescr_letter_open_FraLineQ3");
            GiveItem2Character(pchar, "letter_open");
			pchar.questTemp.State = "Fr3TakeAnna_WaitMidnight";
        break;
//========================== Тревога в таверне Гаваны ==================================
		case "Allarm":
    		dialog.text = "I reconized "+ GetSexPhrase("him", "her") +"! Guards! Someone call the guards, we need to detain "+ GetSexPhrase("this ladron", "this criminal") +"!";
    		link.l1 = "Ah, carramba!!";
    		link.l1.go = "Step_F_Allarm";
			NextDiag.TempNode = "First time";
        break;
		case "Step_F_Allarm":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			GetCharacterPos(pchar, &locx, &locy, &locz);
            for (int i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("SpaGuard"+i, "sold_spa_"+(rand(7)+1), "man", "man", 20, SPAIN, 0, true));
				FantomMakeCoolFighter(sld, 20, 60, 50, BLADE_LONG, "pistol3", 30);
				LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
                ChangeCharacterAddressGroup(sld, "Havana_tavern", "goto",   LAi_FindFarLocator("goto", locx, locy, locz));
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //на всякий случай
			LAi_SetWaitressType(npchar);
			LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

