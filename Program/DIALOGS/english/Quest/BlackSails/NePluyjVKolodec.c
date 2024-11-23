
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
			AddQuestRecord("BSPrologue", "6");
			CloseQuestHeader("BSPrologue");
			PChar.BS_PiratesStoreMassacre = true;
			SaveCurrentQuestDateParam("BS_PiratesStoreMassacreDate");
			BS_SL_yes();
			DeleteAttribute(pchar, "BSStart");
			BS_QuestCleaning(true);			
			ChangeCharacterHunterScore(pchar, "enghunter", 200);
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
            dialog.text = "Settling our differences, captain, will be easy for you. All we have to do is knock the British out of Fort Nassau.";
			link.l1 = "Is that what you call 'easy'? Declare war on Britain?";
			link.l1.go = "BS_NPVK_8";
		break;

		case "BS_NPVK_7_WhisperIsHere":
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "BS_10_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
		break;

		case "BS_NPVK_8":
            dialog.text = "No war. Just a group of pirates, under black flags, robbing a remote, not very important colony and disappearing over the horizon. It will take a few years for the Crown to find the means and energy to try to get the colony back, but most likely they'll just turn a blind eye and pretend the colony never happened. The Guthrie family will go to great lengths to keep those eyes closed.";
            link.l1 = "Has your family gotten crowded in Boston and Philadelphia and are you expanding your area of influence?";
			link.l1.go = "BS_NPVK_9";
		break;

		case "BS_NPVK_9":
            dialog.text = "You're a fast scrambler! Destroy the fort, kill or capture the garrison. You can find the forces for this on your own, but don't even try to get the local pirate barons to sign off on it. This must be the private initiative of a desperate pirate. It's in your best interest to avoid publicity.";
            link.l1 = "Let's say the city's taken. What's next? You have a plan to hold the colony, don't you?";
			link.l1.go = "BS_NPVK_10";
		break;
		
		case "BS_NPVK_10":
            dialog.text = "There's a plan, just let me know when you're headed for the Bahamas. And if successful, me and my men will be there in a day or two.";
            link.l1 = "The Guthrie family 'just happens' to be in the neighborhood and come to the colonists' aid? That's clever. And what happens if I refuse to take this gamble?";
			link.l1.go = "BS_NPVK_11";
		break;
		
		case "BS_NPVK_11":
            dialog.text = "Every bounty hunter in the Old World and the New will suddenly be eager to bring me your head. I assure you, Captain, even kings don't dare quarrel with the Guthrie Trading House. We have the means and the connections to make life very difficult for anyone.";
            link.l1 = "Who the hell do you think you are, girl? Ha! A bunch of merchants and accountants! I know the best way to settle our differences is with cold steel!";
			link.l1.go = "Fight_gatri";
			link.l2 = "This all sounds like complete insanity, but I agree! I need time to prepare. I won't say how long, but I'll let you know. I'll see you around.";
			link.l2.go = "BS_NPVK_12";
		break;
		
		case "BS_NPVK_12":
            dialog.text = "That's fine. And you can get everything you need from this store. Bermuda Warehouse is always at your service. You'll find me through the bartender.";
            link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_NPVK_13";
			BS_SL_yes();
			AddQuestRecord("BSPrologue", "2");
			pchar.questTemp.BSPrologue.WaitingForNassauSiege = true;
		break;

		case "BS_NPVK_13":
            dialog.text = "What else? I won't keep you any longer.";
			link.l1 = "...";
			link.l1.go = "BS_NPVK_14";
		break;
		
		case "BS_NPVK_14":
			DialogExit();
			DoReloadCharacterToLocation("Pirates_town", "reload", "reload6_back");
		break;
		
		case "Woman_FackYou":
			dialog.text = "Honey, where are you going?! You seemed like a decent person. Now you can't just walk away, beautiful. They're gonna clip your wings...";
			link.l1 = "Shut up, stupid...";
			link.l1.go = "Fight_gatri";
			LAi_SetOwnerTypeNoGroup(npchar);
		break;
		
		case "BS_NPVK_15":
			dialog.text = "Is the day here? Are you ready to go camping?";
			link.l1 = "More than enough! Are your men ready?";
			link.l1.go = "BS_NPVK_16";
		break;
		
		case "BS_NPVK_16":
			dialog.text = "We'll be in the neighborhood. Good luck, Captain!";
			link.l1 = "We can use a little luck. Let's do it!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("BS_ToNassauSiege_PiratesTown");
		break;
		
		case "BS_NPVK_17":
			dialog.text = "The deed is done, your debts are canceled. Now leave the island, I'll contact you through the pirate bartenders if there's any work in your line of work.";
			link.l1 = "I've got a bunch of thugs who've just had a little bloodshed. You can't just convince them to get in their boats and leave. You know what I'm saying?";
			link.l1.go = "BS_NPVK_18";
		break;
		
		case "BS_NPVK_18":
			dialog.text = "I understand perfectly. Well, the colony stores are at your service, take what you can carry and finally leave my island!";
			link.l1 = "That's the business approach. It's a pleasure to work with an understanding person!";
			link.l1.go = "BS_NPVK_18_exit";
			
		break;
		
		case "BS_NPVK_18_exit":
			NextDiag.CurrentNode = "BS_NPVK_19";
			DialogExit();
			SaveCurrentQuestDateParam("BSPrologueEnded");
			AddQuestRecord("BSPrologue", "3");
			CloseQuestHeader("BSPrologue");
			DeleteAttribute(pchar, "BSStart");
			pchar.BSInProgress = true;
			AddDialogExitQuestFunction("BS_NassauSiegeComplete");
		break;
		
		case "BS_NPVK_19":
			dialog.text = "It's done.";
			link.l1 = "Yes.";
			Link.l1.go = "BS_NPVK_19_loop";
		break;
		
		case "BS_NPVK_19_loop":
			NextDiag.CurrentNode = "BS_NPVK_19";
			DialogExit();
		break;
		
		case "BS_NPVK_20":
			dialog.text = NPCStringReactionRepeat("I'm busy right now.", "Come back another time.", "Ah, Captain, it's good to see you, but I'm sorry, a lot to do.", "Let's do it another time, it's very busy.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Uh, excuse me.", "I will.", "I understand.", "I'm on my way out.", npchar, Dialog.CurrentNode);
			Link.l1.go = "BS_NPVK_20_loop";			
		break;
		
		case "BS_NPVK_20_meet":
			if(!CheckAttribute(PChar, "GatriSalutation") || GetQuestPastDayParam ("GatriSalutation") > 0)
			{
				SaveCurrentQuestDateParam("GatriSalutation");
				dialog.text = "Hello.";
				link.l1 = "Greetings...";				
			}
			else
			{
				dialog.text = "Did you want something?";
				link.l1 = "Yes...";
			}
			Link.l1.go = "BS_NPVK_20";
		break;
		
		case "BS_NPVK_20_loop":
			NextDiag.CurrentNode = "BS_NPVK_20_meet";
			DialogExit();
		break;
	}
}
