
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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

		case "BS_NPVK_1":	//Торговец
			dialog.text = "Captain, nothing personal, but a very influential person has forbidden me to do business with you. No deals, sorry";
			link.l1 = "I'm sorry, but I don't understand. What happened?";
			link.l1.go = "BS_NPVK_2";
		break;

		case "BS_NPVK_2":
            dialog.text = "Contact Ms. Guthrie, she recently arrived from Nassau and took control of the prize deals. Jackman himself comes to her with a bow.";
            link.l1 = "Hmm. Guthrie... Something familiar. Okay, see you later.";
			link.l1.go = "exit";
		break;

		case "BS_NPVK_3":	//Гатри
            dialog.text = "Ah, here comes our troubled captain! Have you come to settle your differences? Let's settle this, but I warn you – these guys with muskets are not just standing here.";
            link.l1 = "Hmm. The fact is that traders in the colonies and even pirates have stopped doing business with me, they say that you are the reason for this. May I ask what's the matter?";
			link.l1.go = "BS_NPVK_4";
		break;

		case "BS_NPVK_4":
            dialog.text = "It's about your indiscretion, and as I think, your inexperience in the affairs of the New World. Let me explain.";
            link.l1 = "I'm listening to you.";
			link.l1.go = "BS_NPVK_5";
		break;

		case "BS_NPVK_5":
            dialog.text = "The former owner of this store, Monsieur Voisier, was, one might say, our family's attorney. All the goods obtained by pirates, and often by privateers, became quite legal through his efforts and brought profit to everyone. Including governors and commanders of military squadrons\n"+
							"And suddenly, a brave captain decides that the rules do not apply to him and begins to create chaos. Money, my dear – they love peace.";
            link.l1 = "Your 'attorney' himself, in fact, was a pirate and interfered with trade in the archipelago. I was contacted by a respected merchant on behalf of the community, and I solved problem to the best of your abilities. I don't understand what differences you and I might have?";
			link.l1.go = "BS_NPVK_6";
		break;

		case "BS_NPVK_6":
            dialog.text = "Captain. I can attribute your tone to inexperience and misunderstanding of the essence of things, but I warn you: another word and the weapon will speak!";
            if (WhisperIsHere())
			{
				link.l1.go = "BS_NPVK_6_WhisperIsHere";
				break;
			}
			link.l1 = "Who do you think you are, girl?";	//Драка
			link.l1.go = "Fight_gatri";
			link.l2 = "Let's tone it down and find a solution to our 'difficulties'.";
			link.l2.go = "BS_NPVK_7";
		break;

		case "BS_NPVK_6_1":
			link.l1 = "Who do you think you are, girl?";	//Драка
			link.l1.go = "Fight_gatri";
			link.l2 = "Let's tone it down and find a solution to our 'difficulties'.";
			link.l2.go = "BS_NPVK_7";
		break;

		case "BS_NPVK_6_WhisperIsHere":
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "BS_9_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
		break;

		case "Fight_gatri":
			pchar.quest.BS_Fail_Prologue.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BS_Fail_Prologue.win_condition.l1.location = pchar.location;
			pchar.quest.BS_Fail_Prologue.function = "BS_RestoreGatriTrader";

			CloseQuestHeader("BSPrologue");
			pchar.questTemp.BlueBird = "declined";//Блокировка ЧП
			string killGatri;
			for (i = 1; i < 4; i++)
			{
				sld = CharacterFromID("gatri_grunt"+i);
				LAi_SetImmortal(sld, false);
				killGatri = "l"+i;
				pchar.quest.KillGatri.win_condition.(killGatri) = "NPC_Death";
				pchar.quest.KillGatri.win_condition.(killGatri).character = sld.id;
				pchar.quest.KillGatri1.win_condition.(killGatri) = "NPC_Death";
				pchar.quest.KillGatri1.win_condition.(killGatri).character = sld.id;
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_MoveCharacter(npchar, "EnemyFight");
				LAi_SetHP(sld, 200, 200);

			}
			killGatri = npchar.id;
			LAi_SetImmortal(npchar, false);
			npchar.Dialog.FileName = npchar.beforeGatriFileName;
			npchar.Dialog.CurrentNode = npchar.beforeGatriCurrentNode;
			pchar.quest.KillGatri.win_condition.(killGatri) = "NPC_Death";
			pchar.quest.KillGatri.win_condition.(killGatri).character = npchar.id;
			pchar.quest.KillGatri1.win_condition.(killGatri) = "NPC_Death";
			pchar.quest.KillGatri1.win_condition.(killGatri).character = npchar.id;
			pchar.quest.KillGatri.function = "LockWeapons";
			pchar.quest.KillGatri1.win_condition = "OpenTheDoors";

			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "BS_NPVK_7":
            dialog.text = "One million pesos. At once or in parts – at your choice. And we will forget this misunderstanding.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "Take this shitty money... ('quietly' Bitch)";
				link.l1.go = "BS_NPVK_11";
			}
			link.l2 = "How much?! Are you out of your mind? It's incredible!";
			link.l2.go = "BS_NPVK_8";
		break;

		case "BS_NPVK_7_1":
			link.l1 = "How much?! Are you out of your mind? It's incredible!";
			link.l1.go = "BS_NPVK_8";
		break;

		case "BS_NPVK_7_WhisperIsHere":
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "BS_10_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
		break;

		case "BS_NPVK_8":
            dialog.text = "That's how much my family and its partners suffered from your prank. I hope the benefit was worth it?";
            link.l1 = "And how do you order to extract such an amount of gold? After all, the merchants are under your thumb!";
			link.l1.go = "BS_NPVK_9";
		break;

		case "BS_NPVK_9":
            dialog.text = "Aren't you a formidable pirate? A privateer? An adventurer? Have the local seas become impoverished with galleons? Think for yourself. The term is one month. Otherwise, all the bounty hunters in the New and Old World will suddenly be eager to bring me your head.";
            link.l1 = "Well, goodbye.";
			link.l1.go = "exit";
			AddQuestRecord("BSPrologue", "2");
			SetTimerCondition("Gatri_Hunters", 0, 0, 30, true);//Отсчёт времени до НЗГ
			NextDiag.TempNode = "BS_NPVK_10";
		break;

		case "BS_NPVK_10":
            dialog.text = "Are you back?";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "This is what I managed to get.";
				link.l1.go = "BS_NPVK_11";
			}
			link.l2 = "I'm already leaving.";
			link.l2.go = "exit"
		break;

		case "BS_NPVK_11":
			dialog.text = "I see everything is here. For now, our differences are settled. I am always glad to see an executive and savvy earner. Come in again!";
			if (CheckAttribute(pchar, "BSPrologue.GatriHunters"))
			{
				link.l1 = "Will you recall your hunters now?";
				link.l1.go = "BS_NPVK_12";
			}
			link.l2 = "Goodbye.";
			link.l2.go = "end_quest";
			AddMoneyToCharacter(pchar, -1000000);
		break;

		case "end_quest":
			SaveCurrentQuestDateParam("BSPrologueEnded");
			AddQuestRecord("BSPrologue", "3");
			CloseQuestHeader("BSPrologue");
			DeleteAttribute(pchar, "BSStart")//Снимаем блокировку торгашей и ежемесячное начисление НЗГ
			pchar.BSInProgress = true;
			//NPChar.Dialog.Filename = "Common_store.c";
			//NPChar.Dialog.CurrentNode = "Second time";
			NextDiag.CurrentNode = "end_quest_loop";
			DialogExit();

			//LAi_CharacterDisableDialog(npchar);
			pchar.quest.BS_End_Prologue.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BS_End_Prologue.win_condition.l1.location = pchar.location;
			pchar.quest.BS_End_Prologue.function = "BS_RestoreGatriTrader";
		break;

		case "end_quest_loop":
			NextDiag.TempNode = "end_quest_loop";
			dialog.text = "I don't need anything from you yet, Captain. You can go now.";
			link.l2 = "Nice to hear.";
			link.l2.go = "exit";
		break;

		case "BS_NPVK_12":
			dialog.text = "I'm afraid I can't help you, you brought these problems on yourself. It was worth doing my errand more efficiently. The money has long been paid, the flywheel is running, and the hunters cannot be stopped with just a click of their fingers. But I'm sure you're a resourceful captain and you can get out of any scrape. For my part, I can only promise that I will not send any new mercenaries to you.";
			link.l2 = "I really want to be rude to you, but I think I'll refrain. Goodbye.";
			link.l2.go = "end_quest";
		break;
	}
}
