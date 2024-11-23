// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	string sStr;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, "+ GetSexPhrase("my son", "my daughter") +"?", "Ask, I'm listening to you..."), "I'm listening to you, tell me, "+ GetSexPhrase("my son", "my daughter") +"...", "And for the third time I tell you, "+ GetSexPhrase("my son", "my daughter") +": ask your question.",
                          "A clergyman has so many responsibilities, and then you're bothering, "+ GetSexPhrase("my son", "my daughter") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind..", "Not now, Padre..."), "Yes, there's not much to say yet...",
                      "I will ask, I will ask... Only later...", "Excuse me, Holy Father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//============= Изабелла Росселини ================
            if (CheckAttribute(Pchar, "RomanticQuest.PriestAsk"))
			{
				link.l2 = "May I ask if Don Salvator's wife goes to church often?";
				link.l2.go = "Romantic_1";
			}
			//Квест "Strange things are happening in the archipelago"
			if (CheckAttribute(Pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Dobro"))	//Письмо не вскрывали
			{
				link.l1 = "I was instructed to deliver this letter.";
				link.l1.go = "PKM_SvtvA_Ch1_1_Dobro";
				TakeItemFromCharacter(pchar, "PKM_SvtvA_pismo1");			
			}
			if (CheckAttribute(Pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Zlo"))	//Письмо вскрыли
			{
				link.l1 = "I was instructed to deliver this letter.";
				link.l1.go = "PKM_SvtvA_Ch1_1_Zlo";
				TakeItemFromCharacter(pchar, "PKM_SvtvA_pismo1");			
			}
			if (CheckAttribute(Pchar, "questTemp.PKM_SvtvA_Dostavka_Malty"))	//Доставили Мальтильца
			{
				link.l1 = "Your assignment has been completed. The ship you asked me to escort is in port.";
				link.l1.go = "PKM_SvtvA_Ch2_1";				
			}
		break;

		//Квест "Strange things are happening in the archipelago" (Доставили письмо)
		case "PKM_SvtvA_Ch1_1_Dobro":
			dialog.text = "Give it to me here. Well, well... hmm... That's what I thought! Hm... Well, you've done a good job, but let me ask you a few questions.";
			link.l1 = "Yes, what exactly do you want to know?";
			link.l1.go = "PKM_SvtvA_Ch1_2_Dobro";
			
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Dobro");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Zlo");
		break;

		case "PKM_SvtvA_Ch1_1_Zlo":
			dialog.text = "Give it to me here. Well, well... hmm... That's what I thought! By the way, who opened the letter?";
			link.l1 = "No one opened it, what are you doing?! Do you think I could do something like that?!";
			link.l1.go = "PKM_SvtvA_Ch1_2_Zlo_Poka";
			link.l2 = "Did you guess?! That's how I knew that it wouldn't end well.";
			link.l2.go = "PKM_SvtvA_Ch1_2_Zlo";
			
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Dobro");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Zlo");
		break;

		case "PKM_SvtvA_Ch1_2_Zlo":
			dialog.text = "So who opened the letter?";
			link.l1 = "I was met in the bay where I needed to land. And I had no choice but to give them the letter. Some people in red robes, they knew that I would dock there!";
			link.l1.go = "PKM_SvtvA_Ch1_3_Zlo";
		break;

		case "PKM_SvtvA_Ch1_3_Zlo":
			dialog.text = "Okay. I see that you can be forgiven for this sin. Moreover, we foresaw such an outcome of events, and in order to understand the true meaning of the words of this letter, you need to have some knowledge. You even helped us in some way by misleading these people. I think I can even pay you the promised amount.";
			link.l1 = "Oh, thank you, thank you!";
			link.l1.go = "PKM_SvtvA_Ch1_6";
			ChangeCharacterReputation(pchar, -15);
			AddMoneyToCharacter(pchar, 1000);
			AddQuestRecord("PKM_Animists", "13");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
		break;

		case "PKM_SvtvA_Ch1_2_Zlo_Poka":
			dialog.text = "I see that you are not going to repent of what you did. Also, your will, and now leave the church!";
			link.l1 = "As you wish.";
			link.l1.go = "PKM_SvtvA_Ch1_3_Zlo_Poka";
			link.l2 = "No, wait, I'm sorry! The devil got confused!";
			link.l2.go = "PKM_SvtvA_Ch1_2_Zlo";
		break;

		case "PKM_SvtvA_Ch1_3_Zlo_Poka":
			DialogExit();

			ChangeCharacterReputation(pchar, -30);
			AddQuestRecord("PKM_Animists", "14");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("PKM_Animists", "sSex2", GetSexPhrase("xia", "as"));
			CloseQuestheader("PKM_Animists");
			pchar.questdata.Satanisty = 1;
		break;

		case "PKM_SvtvA_Ch1_2_Dobro":
			dialog.text = "Did you have any troubles on the way?";
			link.l1 = "You know, " + GetFullName(CharacterFromID("FortFrance_Priest"))+"he asked me to land in a secluded bay to avoid surprises, but the fact is that they were already waiting for me there...";
			link.l1.go = "PKM_SvtvA_Ch1_3_Dobro";
			if (CheckAttribute(Pchar, "questTemp.PKM_SvtvA_DralisVG"))	//Если дрались в городе
			{
				link.l1 = "You know, mysterious people in red were already waiting for me at the pier... After my refusal to give them the letter, they attacked me. As you can see, I'm standing here alive, what can't be said about my killers.";
				link.l1.go = "PKM_SvtvA_Ch1_4_Dobro";
			}
		break;

		case "PKM_SvtvA_Ch1_3_Dobro":
			dialog.text = "You mean...";
			link.l1 = "I don't want to cast a shadow on anyone, just take it into consideration. Four men in red robes met me at the bay and were very interested in writing. So much so that I had to kill them.";
			link.l1.go = "PKM_SvtvA_Ch1_4_Dobro";
		break;

		case "PKM_SvtvA_Ch1_4_Dobro":
			dialog.text = "Hmm, I see that " + GetFullName(CharacterFromID("FortFrance_Priest"))+" really didn't entrust this case to you for nothing...";
			link.l1 = "That's not all. After searching the bodies of the attackers, I managed to find strange medallions around the necks of each of them.";
			link.l1.go = "PKM_SvtvA_Ch1_5_Dobro";
		break;

		case "PKM_SvtvA_Ch1_5_Dobro":
			dialog.text = "Let's take a look at them... hmm... How interesting... But let's get back to our business. Here is your reward.";
			link.l1 = "Thank you.";
			link.l1.go = "PKM_SvtvA_Ch1_6";
			AddMoneyToCharacter(pchar, 4000);
			ChangeCharacterReputation(pchar, 2);
		break;
		
		case "PKM_SvtvA_Ch1_6":
			dialog.text = "And I have one more thing for you, if you, of course, agree to take it on, the payment for its successful completion will be much more generous than this time.";
			link.l1 = "And what do you want me to do?";
			link.l1.go = "PKM_SvtvA_Ch1_7";
		break;

		case "PKM_SvtvA_Ch1_7":
			dialog.text = "A ship carrying Maltese knights important to our cause is due to arrive from Europe. I have every reason to believe that this ship is in danger, and your task is to meet it at San Martin Island and escort it to our port.";
			link.l1 = "Tell me the name of this vessel and I will do my best.";
			link.l1.go = "PKM_SvtvA_Ch1_8";
		break;

		case "PKM_SvtvA_Ch1_8":
			dialog.text = "So, you should meet the bark 'Maenez', commanded by one Jacqueline de Masset, a Maltese officer.";
			link.l1 = "Great, this information is enough. I think I can sail-the sooner I do it, the better the chances of success.";
			link.l1.go = "PKM_SvtvA_Ch1_9";
		break;
		
		case "PKM_SvtvA_Ch1_9":
			DialogExit();
			AddQuestRecord("PKM_Animists", "15");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			if (CheckAttribute(Pchar, "questTemp.PKM_SvtvA_DralisVG")) sStr = "the pier";
			else sStr = "the beach";
			AddQuestUserData("PKM_Animists", "sStr", sStr);
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_DralisVG");
			
			//Корабль 'Маёнез'
			sld = GetCharacter(NPC_GenerateCharacter("Maltese", "Maltese", "man", "man", 10, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, 10, 30, 30, "blade16", "pistol1", 50);
			SetSPECIAL(sld, 10, 6, 8, 10, 6, 5, 6);
			SetSelfSkill(sld, 18, 21, 70, 3, 40);
			SetShipSkill(sld, 60, 12, 18, 17, 32, 41, 60, 31, 26);
			LAi_SetHP(sld, 300.0, 300.0);
			sld.name = "Jacqueline";
			sld.lastname = "de Masset";
			sld.loyality = 20;
			FantomMakeCoolSailor(sld, SHIP_BARQUE, "Maenez", CANNON_TYPE_CULVERINE_LBS16, 30, 50, 30);	//Корабль
			sld.AlwaysFriend = true;
			sld.Ship.Mode = "trade";
			Group_FindOrCreateGroup("PKM_SvtvA_Malta");
			Group_SetType("PKM_SvtvA_Malta", "war");
			Group_AddCharacter("PKM_SvtvA_Malta", "Maltese");
			Group_SetTaskAttack("PKM_SvtvA_Malta", "PKM_SvtvA_TL");
			SetCharacterGoods(sld, GOOD_FOOD, 500);
			SetCharacterGoods(sld, GOOD_FRUITS, 700);

			Group_SetGroupCommander("PKM_SvtvA_Malta", "Maltese");
			Group_SetAddress("PKM_SvtvA_Malta", "SentMartin", "quest_ships", "Quest_ship_7");
			Group_LockTask("PKM_SvtvA_Malta");
			
			//Корабль 'Тёмный Ангел'
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvtvA_TA", "Animists1", "man", "man", 10, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 12, 40, 50, "blade26", "pistol1", 80);
			sld.name = "Secret";
			sld.lastname = "personality";
			FantomMakeCoolSailor(sld, SHIP_LA_MARIANNA, "Dark Angel", CANNON_TYPE_CULVERINE_LBS24, 60, 60, 60);	//Корабль
			sld.AlwaysEnemy = true;
			Group_FindOrCreateGroup("PKM_SvtvA_TL");
			Group_SetType("PKM_SvtvA_TL", "war");
			Group_AddCharacter("PKM_SvtvA_TL", "PKM_SvtvA_TA");
			realships[sti(sld.ship.type)].HP = 6000;
			realships[sti(sld.ship.type)].SpeedRate = 13;
			realships[sti(sld.ship.type)].TurnRate  = 14;

			Group_SetGroupCommander("PKM_SvtvA_TL", "PKM_SvtvA_TA");
			Group_SetAddress("PKM_SvtvA_TL", "SentMartin", "quest_ships", "Quest_ship_7");
			Group_LockTask("PKM_SvtvA_TL");
			
			//Условия задания
			
			PChar.quest.PKM_SvtvA_TA_ploho.win_condition.l1 = "NPC_Death";		//Поражение
			PChar.quest.PKM_SvtvA_TA_ploho.win_condition.l1.character = "Maltese";
			PChar.quest.PKM_SvtvA_TA_ploho.win_condition = "PKM_SvtvA_Маёнез_потопили";
			
			PChar.quest.PKM_SvtvA_TA_horosho.win_condition.l1 = "NPC_Death";		//Победа
			PChar.quest.PKM_SvtvA_TA_horosho.win_condition.l1.character = "PKM_SvtvA_TA";
			PChar.quest.PKM_SvtvA_TA_horosho.win_condition = "PKM_SvtvA_Ангела_потопили";
		break;
		
		//Квест "Strange things are happening in the archipelago" (После сопровождения корабля мальтийских рыцарей)
		case "PKM_SvtvA_Ch2_1":
			dialog.text = "You did a great job! But tell me, were there any surprises in your voyage?";
			link.l1 = "No, except that when I met the bark, it was attacked by pirates who tried to sink it by any means.";
			link.l1.go = "PKM_SvtvA_Ch2_2";
		break;

		case "PKM_SvtvA_Ch2_2":
			dialog.text = "Understood. Now let me present you with your award and propose a new case.";
			link.l1 = "Thank you, but what kind of task do you want me to do?";
			link.l1.go = "PKM_SvtvA_Ch2_3";
			AddMoneyToCharacter(pchar, 5000);
			PChar.quest.PKM_SvtvA_TA_ploho.over = "yes";
		break;

		case "PKM_SvtvA_Ch2_3":
			dialog.text = "Nothing out of the ordinary. Just take this letter to Father Clermont in Martinique. And make sure that it doesn't get to anyone but him!";
			link.l1 = "I'll do it. May I leave you?";
			link.l1.go = "PKM_SvtvA_Ch2_4";
			GiveItem2Character(PChar, "PKM_SvtvA_pismo2");
		break;

		case "PKM_SvtvA_Ch2_4":
			dialog.text = "You can, and may God be with you.";
			link.l1 = "Amen.";
			link.l1.go = "exit";
			
			AddQuestRecord("PKM_Animists", "19");
			sld = CharacterFromID("Maltese");
			RemoveCharacterCompanion(pchar, sld);
			Group_SetAddress("PKM_SvtvA_Malta", "none", "", "");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Znakomstvo_s_Malta2");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Dostavka_Malty");
			
			PChar.quest.PKM_SvtvA_Zasada2.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_Zasada2.win_condition.l1.location = "SanJuan_town";
			PChar.quest.PKM_SvtvA_Zasada2.win_condition = "PKM_SvtvA_Zasada2";
			
			bDisableFastReload = true;
		break;

		//Квест "The story of the Beautiful Isabella"
        case "Romantic_1":
			dialog.text = "Salvator Olevares? Yes, my son, she is often a worthy parishioner... What's the matter?";
			link.l1 = "I just asked, Padre. Goodbye...";
			link.l1.go = "exit";
			DeleteAttribute(Pchar, "RomanticQuest.PriestAsk");
		break;

        case "Romantic_2":
			dialog.text = GetFullName(pchar) + ", do you take Isabella de Valdez as your wife and swear to live with her in peace and harmony until death do you part?";
			link.l1 = "Yes, Padre.";
			link.l1.go = "Romantic_3";
		break;
        case "Romantic_3":
			locCameraToPos(3.64, 3.25, -7.84, false);
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "goto", "goto5");
			dialog.text = "And you, Isabella de Valdez, do you take as your husband " + GetMainCharacterNameGen() + " and swear to live with him in peace and harmony until death do you part?";
			link.l1 = "Yes, Padre.";
			link.l1.go = "Romantic_4";
		break;
        case "Romantic_4":
			locCameraToPos(-0.75, 3.85, -10.60, false);
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "goto", "goto5");
			dialog.text = "If someone present knows the reason why this man and this woman cannot be together, let them say it right now or keep silent forever.";
			link.l1 = "...";
			link.l1.go = "Romantic_5";
		break;
        case "Romantic_5":
			dialog.text = "From now on you are husband and wife!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuest("Romantic_Padre_3");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
