void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
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
		
////////////////////////////////////////////////////////////////////////////////////////////////
// Анжелика Тич: "The dressmaker of a noble lady"			Авторы: Nikk и Sinistra
////////////////////////////////////////////////////////////////////////////////////////////////		
		
		case "First time":
			dialog.text = "Inform Sinistra about the bug";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "AT_PZD_Pilar_1_1":
			dialog.text = "";
			link.l1 = "Rebecca?";
			link.l1.go = "AT_PZD_Pilar_1_2";
			DeleteAttribute(npchar, "talker");
		break;

		case "AT_PZD_Pilar_1_2":
			dialog.text = "I beg your pardon?";
			link.l1 = "How... I think I made a mistake. I confused you with one of my friends.";
			link.l1.go = "AT_PZD_Pilar_1_3";
		break;

		case "AT_PZD_Pilar_1_3":
			dialog.text = "And I've already understood that perfectly well. Now, please step away from me.";
			link.l1 = "Of course, of course. But I'd just like to know who made your dress? Because of him, it seemed to me that you were the girl.";
			link.l1.go = "AT_PZD_Pilar_1_4";
		break;

		case "AT_PZD_Pilar_1_4":
			dialog.text = "Nonsense.";
			link.l1 = "";
			link.l1.go = "AT_PZD_Pilar_1_5";
		break;

		case "AT_PZD_Pilar_1_5":
			dialog.text = "Garbird, what are you standing here for?";
			link.l1 = "";
			link.l1.go = "AT_PZD_Pilar_1_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("AT_PZD_Herineldo"));
		break;

		case "AT_PZD_Pilar_1_6":
			DialogExit();
			StartInstantDialog("AT_PZD_Herineldo", "AT_PZD_Pilar_1_7", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
			sld = CharacterFromID("AT_PZD_Pilar");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);			
		break;

		case "AT_PZD_Pilar_1_7":
			dialog.text = "Senorita, I have to insist.";
			link.l1 = "Don't bother yourself!";
			link.l1.go = "AT_PZD_Pilar_1_8";
		break;

		case "AT_PZD_Pilar_1_8":
			DialogExit();
			
			sld = CharacterFromID("AT_PZD_Pilar");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("AT_PZD_Herineldo");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, CharacterFromID("AT_PZD_Pilar"), "", -1);
			sld.lifeday = 0;
			
			sld = CharacterFromID("AT_PZD_R1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, CharacterFromID("AT_PZD_Pilar"), "", -1);
			sld.lifeday = 0;
			
			SetQuestHeader("AT_PZD");
			AddQuestRecord("AT_PZD", "1");
			LocatorReloadEnterDisable("Marigo_town", "reload3_back", true);
			LocatorReloadEnterDisable("Marigo_town", "reloadR2", true);
			
			PChar.quest.AT_PZD_ProvalMissii.win_condition.l1 = "MapEnter";
			PChar.quest.AT_PZD_ProvalMissii.win_condition = "AT_PZD_ProvalMissii";
			
			pchar.questTemp.AT_PZD_taverna = true;
			pchar.questTemp.AT_PZD_PU = true;
		break;
		
		case "AT_PZD_MatrosUKostra_1":
			locCameraFromToPos(43.47, 3.58, -6.19, true, 32.50, 0.20, 0.00);
			TeleportCharacterToPosAy(pchar, 39.58, 0.02, -4.80, -0.40);
			dialog.text = "... (not noticing us)... And I tell him that he is a naive fool, since he believes in these rumors that I allegedly hugged a black bear... Yes, there was no such thing, what do you need?";
			link.l1 = "Are you resting, workers? There is a conversation.";
			link.l1.go = "AT_PZD_MatrosUKostra_2";
		break;
		
		case "AT_PZD_MatrosUKostra_2":
			dialog.text = "You've got that right, young lady. We are resting. If you want to offer a job, come back tomorrow... Or not, better in 2 days. We already have an employer for tomorrow, or offer a big price.";
			link.l1 = "I need it now. 2,000 coins for a simple conversation, okay?";
			link.l1.go = "AT_PZD_MatrosUKostra_3";
		break;
		
		case "AT_PZD_MatrosUKostra_3":
			dialog.text = "It's a deal. Spread it out, just the money in advance, and we'll tell you what we know.";
			if (sti(pchar.Money) >= 2000)
			{
				link.l1 = "Here you go.";
				link.l1.go = "AT_PZD_MatrosUKostra_4";
			}
			link.l2 = "I left my wallet in the cabin, I'll be back soon.";
			link.l2.go = "AT_PZD_MatrosUKostra_3_0";
		break;
		
		case "AT_PZD_MatrosUKostra_3_0":
			DialogExit();
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("AT_PZD_Matros"+i);
				sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
				sld.dialog.currentnode = "AT_PZD_MatrosUKostra_3_1";
			}
		break;
		
		case "AT_PZD_MatrosUKostra_3_1":
			dialog.text = "Hey, young lady! Do you have 2000 piastres?";
			if (sti(pchar.Money) >= 2000)
			{
				link.l1 = "Here you go.";
				link.l1.go = "AT_PZD_MatrosUKostra_4";
			}
			link.l2 = "Not yet, I'll be back soon.";
			link.l2.go = "exit";
			NextDiag.TempNode = "AT_PZD_MatrosUKostra_3_1";
		break;
		
		case "AT_PZD_MatrosUKostra_4":
			dialog.text = "Great, so what did you want to know?";
			link.l1 = "I'm interested in an aristocrat woman who got off one of the Spanish ships. She was walking along the embankment recently, accompanied by soldiers, she was wearing a wide-brimmed hat, it's hard not to notice.";
			link.l1.go = "AT_PZD_MatrosUKostra_5";
		break;
		
		case "AT_PZD_MatrosUKostra_5":
			dialog.text = "Her Ladyship must have deigned to walk along the pavement, and we are plowing from dawn to dusk in the port. You need to go to the governor, sailor, with such questions, but he does not accept people like you.";
			link.l1 = "I am captain of my own ship, I will accept it on duty.";
			link.l1.go = "AT_PZD_MatrosUKostra_6";
		break;
		
		case "AT_PZD_MatrosUKostra_6":
			dialog.text = "That's it. They have masquerade balls there every night, no time for state affairs. The noble guests come to him, but no one else is allowed in.";
			link.l1 = "Like masquerades?";
			link.l1.go = "AT_PZD_MatrosUKostra_7";
		break;
		case "AT_PZD_MatrosUKostra_7":
			dialog.text = "As it is. Yesterday I was walking past the residence, I saw a scarecrow with a big nose in the garden, I already crossed myself, and this is some don wearing a mask and standing, looking at the statue. Oh, I was laughing then.";
			link.l1 = "Well, at least there's a clue. How else would I get to this reception?";
			link.l1.go = "AT_PZD_MatrosUKostra_8";
		break;
		case "AT_PZD_MatrosUKostra_8":
			dialog.text = "It's you, sailor, asking the wrong people questions again.";
			link.l1 = "I know, and thanks for that.";
			link.l1.go = "AT_PZD_MatrosUKostra_9";
		break;
		case "AT_PZD_MatrosUKostra_9":
			DialogExit();
			
			AddQuestRecord("AT_PZD", "4");
			
			pchar.questTemp.AT_PZD_Rostovshik = true;
			pchar.questTemp.AT_PZD_Lavochniki = true;
			pchar.questTemp.AT_PZD_Bordel = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("AT_PZD_Matros"+i);
				sld.lifeday = 0;
				LAi_CharacterDisableDialog(sld);
			}
		break;
		
		case "AT_PZD_ManBal5":
			dialog.text = "And where did the host of the evening go? He promised me a poker game.";
			link.l1 = "He's not in the garden.";
			link.l1.go = "AT_PZD_ManBal5_2";
		break;
		case "AT_PZD_ManBal5_2":
			dialog.text = "If you meet him, please tell him that I'm waiting for him here.";
			link.l1 = "I'll do that.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AT_PZD_ManBal5";
		break;
		
		case "AT_PZD_WomanBal1":
			dialog.text = "If Mrs. Sharp, deep down in her heart, decided to defeat the obese dandy, then I do not think that we have the right to condemn her in any way for this, because the task of catching suitors is usually entrusted with appropriate modesty by young people to their mothers, but remember that Mrs. Sharp does not have a loving parent, and if she herself if she doesn't get herself a husband, then there won't be anyone in the whole world who would do her this favor.";
			link.l1 = "";
			link.l1.go = "AT_PZD_WomanBal2";
			sld = CharacterFromID("AT_PZD_WomanBal1");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest1");
		break;
		
		case "AT_PZD_WomanBal2":
			DialogExit();
			StartInstantDialog("AT_PZD_WomanBal2", "AT_PZD_WomanBal3", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_WomanBal3":
			dialog.text = "I can't disagree. Another thing is Mrs. Pilar, who brought her overgrown son to the viewing. Poor boy, he's probably burning with shame.";
			link.l1 = "";
			link.l1.go = "AT_PZD_WomanBal4";
			sld = CharacterFromID("AT_PZD_WomanBal2");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest2");
		break;
		
		case "AT_PZD_WomanBal4":
			DialogExit();
			StartInstantDialog("AT_PZD_WomanBal1", "AT_PZD_WomanBal5", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_WomanBal5":
			dialog.text = "The parents could have settled the matter without the presence of their offspring, I don't think even one of the sisters will pay any attention to the young man.";
			link.l1 = "";
			link.l1.go = "AT_PZD_WomanBal6";
			sld = CharacterFromID("AT_PZD_WomanBal1");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest1");
		break;
		
		case "AT_PZD_WomanBal6":
			DialogExit();
			StartInstantDialog("AT_PZD_WomanBal2", "AT_PZD_WomanBal7", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_WomanBal7":
			dialog.text = "He seems pretty nice to me, but what do you think, Mynheer Andres?";
			link.l1 = "";
			link.l1.go = "AT_PZD_WomanBal8";
			sld = CharacterFromID("AT_PZD_WomanBal2");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest2");
		break;
		
		case "AT_PZD_WomanBal8":
			DialogExit();
			StartInstantDialog("AT_PZD_ManBal4", "AT_PZD_WomanBal9", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_WomanBal9":
			dialog.text = "The Turner family does business in the West India Company, the guy has a great future, it would be imprudent to let him go without a bride...";
			link.l1 = "";
			link.l1.go = "exit";
			sld = CharacterFromID("AT_PZD_ManBal4");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest3");
			
			AddQuestRecord("AT_PZD", "6");
		break;
		
		case "AT_PZD_DochGubera":
			dialog.text = "...";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			
			AddQuestRecord("AT_PZD", "7");
		break;

		case "AT_PZD_MujikBoltun_1":
			dialog.text = "I've warned you a thousand times. I can't help you any more. All my money is settled down to the last shilling.";
			link.l1 = "";
			link.l1.go = "AT_PZD_MujikBoltun_2";
			sld = CharacterFromID("AT_PZD_MujikBoltun1");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest5");
		break;
		
		case "AT_PZD_MujikBoltun_2":
			DialogExit();
			StartInstantDialog("AT_PZD_MujikBoltun2", "AT_PZD_MujikBoltun_3", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_MujikBoltun_3":
			dialog.text = "I don't want to talk about myself. It doesn't matter what happens to me...";
			link.l1 = "";
			link.l1.go = "AT_PZD_MujikBoltun_4";
			sld = CharacterFromID("AT_PZD_MujikBoltun2");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest6");
		break;
		
		case "AT_PZD_MujikBoltun_4":
			DialogExit();
			StartInstantDialog("AT_PZD_MujikBoltun1", "AT_PZD_MujikBoltun_5", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_MujikBoltun_5":
			dialog.text = "Then what's the matter?";
			link.l1 = "";
			link.l1.go = "AT_PZD_MujikBoltun_6";
			sld = CharacterFromID("AT_PZD_MujikBoltun1");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest5");
		break;
		
		case "AT_PZD_MujikBoltun_6":
			DialogExit();
			StartInstantDialog("AT_PZD_MujikBoltun2", "AT_PZD_MujikBoltun_7", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_MujikBoltun_7":
			dialog.text = "You know I was supposed to get Mrs. Crowley's money. I didn't do a bad job in the regiment, the salary covered all my expenses. And you know why the inheritance sailed away from me, and who got it...";
			link.l1 = "";
			link.l1.go = "AT_PZD_MujikBoltun_8";
			sld = CharacterFromID("AT_PZD_MujikBoltun2");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest6");
		break;
		
		case "AT_PZD_MujikBoltun_8":
			DialogExit();
			StartInstantDialog("AT_PZD_MujikBoltun1", "AT_PZD_MujikBoltun_9", "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c");
		break;
		
		case "AT_PZD_MujikBoltun_9":
			dialog.text = "Don't raise your voice, this is not the time or the place, but where did everyone go? No master, no servants... God knows, next time I'll bring a bottle of wine with me.";
			link.l1 = "";
			link.l1.go = "exit";
			sld = CharacterFromID("AT_PZD_MujikBoltun1");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "quest5");
		break;
		
		case "AT_PZD_GabrielDeSeguensa_1":
			dialog.text = "Do you feel uncomfortable in an unfamiliar company?";
			link.l1 = "You have no idea how much.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_2";
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_ActorTurnByLocator(sld, "quest", "quest9");
			LAi_ActorAnimation(sld, "barman_look_around", "", 2.9);
			locCameraFromToPos(-0.74, 8.81, 42.94, true, 2.00, 7.20, 42.00);
			ChangeCharacterAddressGroup(pchar, "Marigo_hall", "quest", "quest17");
		break;
		
		case "AT_PZD_GabrielDeSeguensa_1":
			dialog.text = "Do you feel uncomfortable in an unfamiliar company?";
			link.l1 = "You have no idea how much.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_2";
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_ActorTurnByLocator(sld, "quest", "quest9");
			LAi_ActorAnimation(sld, "barman_look_around", "", 2.9);
			locCameraFromToPos(-0.74, 8.81, 42.94, true, 2.00, 7.20, 42.00);
			ChangeCharacterAddressGroup(pchar, "Marigo_hall", "quest", "quest17");
		break;
		
		case "AT_PZD_GabrielDeSeguensa_2":
			dialog.text = "Oh, are you Spanish? It is incredibly unfortunate that we only met now, when the event has already come to an end. I would be glad to invite you to dance.";
			link.l1 = "Nothing would have come of it, I don't know how to waltz.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_3";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_3":
			dialog.text = "A lady of your position could not help but be taught this art. That's right, you refuse to even hope for me in absentia...";
			link.l1 = "To be honest, I'm here even without an invitation. I took advantage of the fact that all the guests were wearing masks and counted on their courtesy, because the day before we had allegedly already been introduced to each other. By the way, where's your mask?";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_4";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_4":
			dialog.text = "She rubbed the bridge of my nose. Still, let me be rude.";
			link.l1 = "My name is Angelica Remedios, the eldest daughter of the commandant of Fort La Vega.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_5";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_5":
			dialog.text = "Gabriel de Seguenza, arrived in the Caribbean on behalf of the Spanish Crown, to solve the problem of piracy in Cuban waters. I was recently seconded from the Old World, but I have already heard about the sad fate of the fort. Why haven't you told me a word of the truth yet? You're playing with me like a kitten.";
			link.l1 = "You've heard the saying, the best way to hide the truth is to tell it, and since you're privy to my little secret, can I ask for a small favor?";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_6";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_6":
			dialog.text = "Well, I accept the terms of your game.";
			link.l1 = "The night La Vega was sacked, the pirates separated me and my sister. She was missing and I had already accepted the thought of her death until I met a woman in a dress exactly like the one poor Becky was wearing when we last saw each other. Her face was covered by a huge hat, and for a moment I even thought it was really Rebecca, but the arrogant woman refused to even talk to me. Here I am, hiding behind a mask in the hope of finding her again and finding out the story of her outfit.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_7";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_7":
			dialog.text = "Bad temper, wide hat - Senora Turner Pilar. She is not present at the party, but just recently I ran into her son in the yard.";
			link.l1 = "You will be doing me an invaluable service if you bring us together.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_8";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_8":
			dialog.text = "I'll look for him and talk to him. Angelica, try not to draw too much attention to yourself yet, at the same time you will help me. Do you see that gentleman sitting at the table over there? He is the commander of the garrison, I think you will find a common language. Say that Gabriel asked to keep him company, and after a while, go out through the door behind the stage to the embankment.";
			link.l1 = "Okay, I get it.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_9";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_9":
			DialogExit();
			
			AddQuestRecord("AT_PZD", "8");
			
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2_back", "", "", "", "", -1);
			
			sld = CharacterFromID("AT_PZD_ManBal5");
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_IgraVKosti";
		break;
		
		case "AT_PZD_IgraVKosti":
			dialog.text = "";
			link.l1 = "Will you invite the lady to the table?";
			link.l1.go = "AT_PZD_IgraVKosti_2";
		break;
		
		case "AT_PZD_IgraVKosti_2":
			dialog.text = "I don't want to be tactless, I'm waiting for a dice partner.";
			link.l1 = "Give me my cubes.";
			link.l1.go = "AT_PZD_IgraVKosti_3";
		break;
		
		case "AT_PZD_IgraVKosti_3":
			dialog.text = "The rules are very simple, we take turns throwing the dice...";
			link.l1 = "Cubes!";
			link.l1.go = "AT_PZD_IgraVKosti_4";
		break;
		
		case "AT_PZD_IgraVKosti_4":
			dialog.text = "God knows, I would bet my award pistol if at least one woman could beat me. To my shame, I pawned it last week.";
			link.l1 = "Playing for fun, I just need to kill some time.";
			link.l1.go = "AT_PZD_IgraVKosti_5";
			npchar.money = 10000;
			
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = 0;
            pchar.GenQuest.Dice.SitType   = true;			
			//pchar.GenQuest.Cards.npcharIdx = npchar.index;
            //pchar.GenQuest.Cards.iRate     = 0;
			//pchar.GenQuest.Cards.SitType   = true;
		break;
		
		case "AT_PZD_IgraVKosti_5":
			DialogExit();
			LaunchDiceGame();
			//LaunchCardsGame();
			
			LAi_CharacterDisableDialog(npchar);
			DoQuestCheckDelay("AT_PZD_UbiliVremya", 60.0);
		break;
		
		case "AT_PZD_GabrielDeSeguensa_11":
			dialog.text = "";
			link.l1 = "Did you manage to find the guy?";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_12";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_12":
			dialog.text = "Yes, there he is on the balustrade. The youngster is not in the mood for long conversations, at least not in my company, but still a wonderful evening, don't you think?";
			link.l1 = "I can't agree, my mind is on other things right now.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_13";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_13":
			dialog.text = "I managed to find out where Miss Pilar is staying. It's better not to have anything to do with her, but talk to her maid, who knows, maybe she brought her own dressmaker. Let me walk you out.";
			link.l1 = "Sure, let's go.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_14";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_14":
			DialogExit();
			
			DoQuestReloadToLocation("Marigo_town", "goto", "goto29", "AT_PZD_VGorod");
		break;
		
		case "AT_PZD_GabrielDeSeguensa_15":
			dialog.text = "Here. Up the stairs.";
			link.l1 = "Will you come up with me?";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_16";
			Log_info(GetConvertStrWithReplace("Variable_quests_reaction_160", "Logs.txt", "#space#", " "));
		break;
		
		case "AT_PZD_GabrielDeSeguensa_16":
			dialog.text = "It's time for me to return to Havana. His Grace, Origon-y-Gascon has been waiting for my reports. Good luck to you, Angelica.";
			link.l1 = "Take care of yourself. Hunting pirates is a very dangerous activity.";
			link.l1.go = "AT_PZD_GabrielDeSeguensa_17";
		break;
		
		case "AT_PZD_GabrielDeSeguensa_17":
			DialogExit();
			
			sld = CharacterFromID("AT_PZD_GabrielDeSeguensa");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
		break;
		
		case "AT_PZD_Sofia_1":
			dialog.text = "";
			link.l1 = "You?! So this is your job?";
			link.l1.go = "AT_PZD_Sofia_2";
		break;
		
		case "AT_PZD_Sofia_2":
			dialog.text = "Oh my God! Senorita, I didn't hear you come in. The owners are staying downstairs, these rooms are now given to the servants. But I'm afraid they're still...";
			link.l1 = "Sofia, don't you recognize me? La Vega, the day before the siege.";
			link.l1.go = "AT_PZD_Sofia_3";
		break;
		
		case "AT_PZD_Sofia_3":
			dialog.text = "Ouch... Are you the girl at the market who wanted to help me in some way?You know, I'm so embarrassed, I was overwhelmed by the problems that piled up, besides, I was fascinated by the unusual cut of your companion's outfit, so I didn't remember your face at all.";
			link.l1 = "How did you manage to escape then?";
			link.l1.go = "AT_PZD_Sofia_4";
		break;
		
		case "AT_PZD_Sofia_4":
			dialog.text = "It was said that before the pirates started shooting at the city, they entered our ship and threw all the barrels of gunpowder into the sea. The officers went to negotiate with them, and when they returned, captain ordered all the passengers to get into the boats, and we sailed away.";
			link.l1 = "They just abandoned us!";
			link.l1.go = "AT_PZD_Sofia_5";
		break;
		
		case "AT_PZD_Sofia_5":
			dialog.text = "It's so terrible, I only recently found out what happened there.";
			link.l1 = "Why didn't you return to Europe?";
			link.l1.go = "AT_PZD_Sofia_6";
		break;
		
		case "AT_PZD_Sofia_6":
			dialog.text = "The ship did not return, I had to look for a job. Fortunately, Miss Pilar was so generous, and you know, I don't want to go back to my father's estate. Have I already told you? She's not here.";
			link.l1 = "Well, I'll come back another time. I am glad that you have coped with your difficulties.";
			link.l1.go = "AT_PZD_Sofia_7";
		break;
		
		case "AT_PZD_Sofia_7":
			dialog.text = "Thank you, senorita.";
			link.l1 = "Good luck, Sofia.";
			link.l1.go = "AT_PZD_Sofia_8";
		break;
		
		case "AT_PZD_Sofia_8":
			DialogExit();
			
			sld = CharacterFromID("AT_PZD_Sofia");
			LAi_SetActorType(sld);
			
			AddQuestRecord("AT_PZD", "10");
			CloseQuestHeader("AT_PZD");
			PChar.quest.AT_PZD_ProvalMissii.over = "yes";
			
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			bDisableOfficers = false;
			LocatorReloadEnterDisable("Marigo_town", "reload3_back", false);
			LocatorReloadEnterDisable("Marigo_town", "reloadR2", false);			
			DeleteAttribute(pchar, "questTemp.AT_PZD_Bordel")
			DeleteAttribute(pchar, "questTemp.AT_PZD_Bordel_2")
			DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki");
			DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki_2");
			DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki_3");
			DeleteAttribute(pchar, "questTemp.AT_PZD_taverna")
			DeleteAttribute(pchar, "questTemp.AT_PZD_PU")
			DeleteAttribute(pchar, "questTemp.AT_PZD_Rostovshik")
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "Cirgnore");
			locations[FindLocation("Marigo_hall")].models.always.l1 = "residence06";
			//locations[FindLocation("Marigo_hall")].models.always.l1 = "residence06_quest";
			locations[FindLocation("Marigo_hall")].models.always.locators = "residence06_locators";
			//locations[FindLocation("Marigo_hall")].models.always.locators = "residence06_quest_locators";
			locations[FindLocation("Marigo_hall")].models.day.charactersPatch = "residence06_patch";
			//locations[FindLocation("Marigo_hall")].models.day.charactersPatch = "residence06_quest_patch";
			locations[FindLocation("Marigo_hall")].models.night.charactersPatch = "residence06_patch";
			//locations[FindLocation("Marigo_hall")].models.night.charactersPatch = "residence06_quest_patch";
			
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Sneak", 150);
		break;

	}
}
