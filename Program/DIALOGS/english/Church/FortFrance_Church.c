// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, "+ GetSexPhrase("my son", "my daughter") +"?", "Ask, I'm listening to you..."), "I'm listening to you, tell me, "+ GetSexPhrase("my son", "my daughter") +"...", "And for the third time I tell you, "+ GetSexPhrase("my son", "my daughter") +": ask your question.",
                          "A clergyman has so many responsibilities, and then you're bothering, "+ GetSexPhrase("my son", "my daughter") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "Not now, Padre..."), "Yes, there's not much to say yet...",
                      "I will ask, I will ask... Only later...", "Excuse me, Holy Father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_FortFranceChurch_1"))	//Квест "Strange things are happening in the archipelago"
            {
                link.l1 = "Holy Father, I heard that you are also looking for the mysterious black frigate that kidnapped the children on San Martin.";
                link.l1.go = "PKM_SvtvA_Ch1_1";
            }
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_PismoKlermon"))	//Квест "Strange things are happening in the archipelago"
            {
                link.l1 = "I have a letter for you.";
                link.l1.go = "PKM_SvtvA_Ch2_1";
            }
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_Clermon_Final"))	//Квест "Strange things are happening in the archipelago"
            {
				dialog.text = "Did you manage to find out anything about the case that was assigned to you?";
                link.l1 = "Moreover, my people and I destroyed the sect.";
                link.l1.go = "PKM_SvtvA_Ch3_1";
            }
		break;
		
		//Квест "Strange things are happening in the archipelago"
		case "PKM_SvtvA_Ch1_1":
			dialog.text = "Kidnapped children?! Hm. I didn't know about it. We are really concerned, because in our city, traces of a pagan ritual were found in one of the houses, and the dead bodies of our good law-abiding citizens lay there. Each of them had their hearts brutally ripped out...";
			link.l1 = "What kind of monsters could do this?";
			link.l1.go = "PKM_SvtvA_Ch1_2";
		break;
		case "PKM_SvtvA_Ch1_2":
			dialog.text = "If you really care about all this, then maybe you could do my errand? Our information about children sheds some light on this picture.\nI want you to deliver the letter to Puerto Rico, and deliver it personally into the hands of a man named Padre Dominguez. You will find him in the cathedral, and he will give you further instructions if he sees fit.";
			link.l1 = "This is a fairly simple task. I will leave immediately, Holy Father.";
			link.l1.go = "PKM_SvtvA_Ch1_3";
		break;
		case "PKM_SvtvA_Ch1_3":
			dialog.text = "Take your time, "+ GetSexPhrase("my son", "my daughter") +". The man who was supposed to deliver the letter today was found dying on the doorstep of his house. All he managed to say before he died was that he was attacked by some people in red robes armed with daggers.\nI have reason to believe that the case here is not clean - someone clearly does not want the letter to be delivered.";
			link.l1 = "So they might try to intercept me on the way?";
			link.l1.go = "PKM_SvtvA_Ch1_4";
		break;
		case "PKM_SvtvA_Ch1_4":
			dialog.text = "Yes, I'm afraid you're right, so if you refuse to deliver the letter, I'll understand you.";
			link.l1 = "I don't see any reason why I would have to give up this case.";
			link.l1.go = "PKM_SvtvA_Ch1_5";
		break;
		case "PKM_SvtvA_Ch1_5":
			dialog.text = "That's great. So, here is a letter, you must deliver it to a priest named Padre Dominguez and only to him. You can find him in Puerto Rico...";
			link.l1 = "";
			link.l1.go = "PKM_SvtvA_Ch1_5.1";
			GiveItem2Character(PChar, "PKM_SvtvA_pismo1");
		break;
		case "PKM_SvtvA_Ch1_5.1":
			dialog.text = "I will also give you a document that will allow you to stay in Puerto Rico legally.I beg you not to enter the port. Land somewhere in a secluded bay so that no one can see you. This letter is of great importance.";
			link.l1 = "Okay. I don't think it will take me too long.";
			link.l1.go = "PKM_SvtvA_Ch1_6";
			GiveNationLicence(SPAIN, 8);
		break;
		case "PKM_SvtvA_Ch1_6":
			DialogExit();
			AddQuestRecord("PKM_Animists", "8");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_FortFranceChurch_1");
			
			PChar.quest.PKM_SvtvA_SJ_B1.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_SJ_B1.win_condition.l1.location = "SanJuan_town";
			PChar.quest.PKM_SvtvA_SJ_B1.win_condition = "PKM_SvtvA_DostavkaPisma_Gorod_1";
			
			PChar.quest.PKM_SvtvA_SJ_B2.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_SJ_B2.win_condition.l1.location = "Shore44";
			PChar.quest.PKM_SvtvA_SJ_B2.win_condition = "PKM_SvtvA_DostavkaPisma_Buhta_1";
			
			PChar.quest.PKM_SvtvA_SJ_B3.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_SJ_B3.win_condition.l1.location = "Shore45";
			PChar.quest.PKM_SvtvA_SJ_B3.win_condition = "PKM_SvtvA_DostavkaPisma_Buhta_1";
		break;
		
		case "PKM_SvtvA_Ch2_1":
			dialog.text = "Aha! I was wondering if Padre Dominguez had sent him away or not.";
			link.l1 = "What do you mean by that?";
			link.l1.go = "PKM_SvtvA_Ch2_2";
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_PismoKlermon");
			TakeItemFromCharacter(pchar, "PKM_SvtvA_pismo2");
		break;
		case "PKM_SvtvA_Ch2_2":
			dialog.text = "Ah, you probably don't know yet - the person who gave you this letter has been kidnapped. I'm afraid that what I was so afraid of has happened.";
			link.l1 = "And what is it?";
			link.l1.go = "PKM_SvtvA_Ch2_3";
			
			sld = characterFromID("SanJuan_Priest");
			sld.name = "Padre";
			sld.lastname = "Robano";
		break;
		case "PKM_SvtvA_Ch2_3":
			dialog.text = "A few years ago, the lair of Satan's servants was destroyed in Italy. Unfortunately, the head of the order managed to escape, and he settled in the archipelago. Now, judging by the loss of children and a high-ranking priest, he is going to conduct an ancient ritual, and we must stop him!";
			link.l1 = "And what is my role in all this?";
			link.l1.go = "PKM_SvtvA_Ch2_4";
		break;
		case "PKM_SvtvA_Ch2_4":
			dialog.text = "I'd like you to take on the role of the sword of God. I understand you're a business man, so how would you like to see 50,000 piastres as a reward for this service?";
			link.l1 = "Well, not bad, not bad at all...";
			link.l1.go = "exit";
			AddDialogExitQuest("PKM_SvtvA_Нападение_в_церкви");
		break;
		case "PKM_SvtvA_Ch3_1":
			AddMoneyToCharacter(pchar, 50000);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Oh, thank God! You did it! I will order a service to be performed in the name of this momentous event!";
			link.l1 = "Now, if you'll excuse me, I have to go.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Clermon_Final");
			AddQuestRecord("PKM_Animists", "39");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			pchar.questTemp.PKM_Animists_OtetsKlermon = true;
			if (CheckAttribute(pchar, "questTemp.PKM_Animists_MamaDeti") && CheckAttribute(pchar, "questTemp.PKM_Animists_GuberMarigo") && CheckAttribute(pchar, "questTemp.PKM_Animists_OtetsKlermon") && CheckAttribute(pchar, "questTemp.PKM_Animists_PadreDominges"))
			{
				CloseQuestHeader("PKM_Animists");
				pchar.questdata.Satanisty = 1;
				UnlockAchievement("AchStrannyeDela", 3);
				DeleteAttribute(pchar, "questTemp.PKM_Animists_MamaDeti");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_GuberMarigo");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_OtetsKlermon");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_PadreDominges");
			}
		break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



