
void ProcessDialogEvent()
{
	ref NPChar;											// 						АВТОРЫ И БЛАГОДАРНОСТИ
	aref Link, NextDiag;								// Оригинальная идея квеста				    			 - Акелла
														// Написанный с нуля код и переосмысление квеста 	 	 - Sinistra
	DeleteAttribute(&Dialog, "Links");					// Улучшенная и обновлённая локация "The Lair of Satanists"  - Nikk
														// Улучшенный и обновлённый корабль "Mephisto"			 - Noctus
	makeref(NPChar,CharacterRef);						// Новая анимация "Worship"							 - Antix
	makearef(Link, Dialog.Links);						// Улучшенная и обновлённая иконка "Amulet of Chaos"		 - LEOPARD
	makearef(NextDiag, NPChar.Dialog);					// Новая текстура модели для "Maltese" 				 - Gregg
														// Новая текстура модели для "Satanists" 				 - Ерилейн
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "First time":
			dialog.text = "What? Are you laughing at poor women too!?";
			link.l1 = "What exactly is going on?";
			link.l1.go = "Verni_detey_1";
			PlayVoice("Kopcapkz\Voices\Quest\Dut_f_a_002.wav");
		break;
		
		case "Verni_detey_1":
			dialog.text = "Just look at "+GetSexPhrase("this impudent man", "this impudent woman")+"! And aren't you ashamed to mock us?!";
			link.l1 = "I really don't understand what happened. Maybe you can tell me?";
			link.l1.go = "Verni_detey_2";
		break;
		
		case "Verni_detey_2":
			dialog.text = "Good people, what is going on in the world! Our children were stolen from us last night, and this provincial didn't even lift a finger!";
			link.l1 = "Wait, how was this stolen? Who?";
			link.l1.go = "Verni_detey_3";
		break;
		
		case "Verni_detey_3":
			dialog.text = "I don't know! I fell asleep - the child was in the cradle, and at night I woke up because my heart was badly squeezed, I look, but the baby is already gone!";
			link.l1 = "This is very strange. And what does the governor say?";
			link.l1.go = "Verni_detey_4";
		break;
		
		case "Verni_detey_4":
			dialog.text = "He doesn't show his nose from his house! Afraid, then! He has nothing to tell us!";
			link.l1 = "Wait, stop making noise, I'll try to talk to him.";
			link.l1.go = "Verni_detey_5";
		break;
		
		case "Verni_detey_5":
			dialog.text = "God bless you, "+GetSexPhrase("good man", "kind girl")+"!";
			link.l1 = "Wait for me here.";
			link.l1.go = "Verni_detey_6";
		break;
		
		case "Verni_detey_6":
			DialogExit();
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_1")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Verni_detey_7";
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_2")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Verni_detey_7";
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_3")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Verni_detey_7";
			
			pchar.questTemp.PKM_SvtvA_Gde_Deti = "Gde_Deti";
			SetQuestHeader("PKM_Animists");
			AddQuestRecord("PKM_Animists", "1");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
		break;
		
		case "Verni_detey_7":
			dialog.text = "Well? Did you find out anything? How are our children?!";
			link.l1 = "I'll try to help you. Now, please disperse.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Verni_detey_7";
			PlayVoice("Kopcapkz\Voices\Quest\Dut_f_a_002.wav");
		break;
		
		case "Capitan_v_taverne_1":
			dialog.text = "Do you want to buy me a drink?";
			link.l1 = "Sorry, buddy, I won't buy a drink, but I'll ask you questions.";
			link.l1.go = "Capitan_v_taverne_1_5";
			UnmarkCharacter(npchar);
		break;
		
		case "Capitan_v_taverne_1_5":
			dialog.text = "Then ask them as soon as possible and fuck off.";
			link.l1 = "They say that you saw some kind of black frigate when you approached the island.";
			link.l1.go = "Capitan_v_taverne_2";
		break;
		
		case "Capitan_v_taverne_2":
			dialog.text = "Well, have you seen it?";
			link.l1 = "What course did he take?";
			link.l1.go = "Capitan_v_taverne_3";
		break;
		
		case "Capitan_v_taverne_3":
			dialog.text = "Straight to Nevis.";
			link.l1 = "Could it be pirates?";
			link.l1.go = "Capitan_v_taverne_4";
		break;
		
		case "Capitan_v_taverne_4":
			dialog.text = "The devil knows them! Go and ask them. Ha ha!";
			link.l1 = "Thank you, dear.";
			link.l1.go = "Capitan_v_taverne_5";
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Capitan_v_taverne_5":
			DialogExit();
			AddQuestRecord("PKM_Animists", "4");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			pchar.questTemp.PKM_SvtvA_SprositKapitanov_v_more = true;
			pchar.questTemp.PKM_SvtvA_NevisTaverna_1 = true;
			pchar.questTemp.PKM_SvtvA_NevisPortMan_1 = true;
			
			PChar.quest.PKM_SvtvA_SprositKapitanov_v_more.win_condition.l1 = "MapEnter";
			PChar.quest.PKM_SvtvA_SprositKapitanov_v_more.win_condition = "PKM_SvtvA_SprositKapitanov_v_more";
			
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvpvA_Shturman_1", "shipowner_17", "man", "man", 10, ENGLAND, -1, true));
			sld.name = "Balltezar";
			sld.lastname = "Figueidal";
			FreeSitLocator("Charles_tavern", "sit_base4");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Shturman_v_taverne_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Charles_tavern", "sit", "sit_base4");	
		break;
		
		case "Shturman_v_taverne_1":
			dialog.text = "Get lost, "+ GetSexPhrase("buddy", "girl") +"!";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shturman_v_taverne_1";
		break;
		
		case "Shturman_v_taverne_2":
			dialog.text = ""+ GetSexPhrase("Old man", "Girlfriend") +"! Put the drink to the best navigator in the New World!";
			link.l1 = "Have you already drunk everything, buddy?";
			link.l1.go = "Shturman_v_taverne_3";
		break;
		
		case "Shturman_v_taverne_3":
			dialog.text = "Everything, up to a penny. Well, will you put down a mug?";
			link.l1 = "Wait, I'm wondering if you saw a black frigate while sailing?";
			link.l1.go = "Shturman_v_taverne_4";
		break;
		
		case "Shturman_v_taverne_4":
			dialog.text = "Treat me to rum and I'll tell you everything!";
			link.l1 = "Okay, here's your rum.";
			link.l1.go = "Shturman_v_taverne_5";
			link.l2 = "Oh, can I hit you a couple of times on the countertop?";
			link.l2.go = "Shturman_v_taverne_9";
		break;
		
		case "Shturman_v_taverne_5":
			dialog.text = "Gulp-gulp. Go-o-o-d rum!";
			link.l1 = "So, did you see the black frigate?";
			link.l1.go = "Shturman_v_taverne_6";
			AddMoneyToCharacter(pchar, -10);
		break;
		
		case "Shturman_v_taverne_9":
			dialog.text = "Hmm... Let's do without it.";
			link.l1 = "So, did you see the black frigate?";
			link.l1.go = "Shturman_v_taverne_6";
			ChangeCharacterReputation(pchar, -2);
		break;
		
		case "Shturman_v_taverne_6":
			dialog.text = "The frigate? Black?! I saw him as I see you. If they hadn't been empty, I wouldn't be talking to you now - they obviously had the holds to the brim. He also had a strange, not Christian name - 'Mephisto'.";
			link.l1 = "Did he follow you? And where did he go after he realized that he couldn't catch up with you?";
			link.l1.go = "Shturman_v_taverne_7";
		break;
		
		case "Shturman_v_taverne_7":
			dialog.text = "And the devil knows him. Somewhere to the south, and there is only Le Francois.";
			link.l1 = "Okay, keep drinking.";
			link.l1.go = "Shturman_v_taverne_8";
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Shturman_v_taverne_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_NevisPortMan_1");
			AddQuestRecord("PKM_Animists", "6");
			pchar.questTemp.PKM_SvtvA_LeFrancuaTaverna_1 = "Taverna";
		break;
		
		case "Satanist_v_gorode_1":
			dialog.text = "Take your time, "+ GetSexPhrase("senor", "senorita") +"! You won't refuse to talk to us, will you?!";
			link.l1 = "I don't think I want to talk to you.";
			link.l1.go = "Satanist_v_gorode_2";
		break;
		
		case "Satanist_v_gorode_2":
			dialog.text = "Give me the letter now!";
			link.l1 = "Maybe we'll have a mug of ale and go our separate ways? No? I knew it.";
			link.l1.go = "Satanist_v_gorode_3";
		break;
		
		case "Satanist_v_gorode_3":		//Битва в городе
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for (i=1; i<=11; i++)
			{
				sld = CharacterFromID("SatanaElita_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PKM_SvtvA_DostavkaPisma_Gorod_2");
			LAi_SetFightMode(pchar, true);			
		break;
		
		case "Satanist_v_buhte_1":
			dialog.text = "Take your time, "+ GetSexPhrase("senor", "senorita") +"! You won't refuse to talk to us, will you?!";
			link.l1 = "I don't think I want to talk to you.";
			link.l1.go = "Satanist_v_buhte_2";
			link.l2 = "Let's talk, but hurry up, I'm in a hurry.";
			link.l2.go = "Satanist_v_buhte_4";
		break;
		
		case "Satanist_v_buhte_2":
			dialog.text = "Give me the letter now!";
			link.l1 = "Maybe we'll have a mug of ale and go our separate ways? No? I knew it.";
			link.l1.go = "Satanist_v_buhte_3";
		break;
		
		case "Satanist_v_buhte_3":		//Битва в бухте без разговора
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("Satanist_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PKM_SvtvA_DostavkaPisma_Buhta_2");
			LAi_SetFightMode(pchar, true);			
		break;
		
		case "Satanist_v_buhte_4":
			dialog.text = "It's come to our attention that you're carrying a letter, and we need to read it. Don't worry, we have a copy of the sealing seal that sealed it, and the addressee won't know anything about what happened. And as a reward for our service, we're willing to pay you 20000 piastres. What do you say?";
			link.l1 = "What will I say? Let me find the right phrase... hmm... ah! First, why don't you go away? And you can stick your seal in you know where.";
			link.l1.go = "Satanist_v_buhte_5";
			link.l2 = "Hmm... 20,000 piastres... sounds tempting, I think we have a deal. Here’s the letter.";
			link.l2.go = "Satanist_v_buhte_7";
		break;
		
		case "Satanist_v_buhte_5":
			dialog.text = "In that case, we will have to kill you.";
			link.l1 = "Try it!";
			link.l1.go = "Satanist_v_buhte_6";
		break;
		
		case "Satanist_v_buhte_6":		//Битва в бухте с разговором и отказываемся отдавать письмо
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("Satanist_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PKM_SvtvA_DostavkaPisma_Buhta_3");
			LAi_SetFightMode(pchar, true);			
		break;
		
		case "Satanist_v_buhte_7":
			dialog.text = "You did the right thing, "+ GetSexPhrase("senor", "senorita") +". Here's your money, and now let's look at the letter Hmm... That's what I thought... Well, they're wrong about that... Well, I found out everything I wanted to know. I seal the letter back - do you see the pattern on the seals is identical? You can go now.";
			link.l1 = "Okay.";
			link.l1.go = "Satanist_v_buhte_8";
			AddMoneyToCharacter(pchar, 20000);
		break;
		
		case "Satanist_v_buhte_8":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("Satanist_"+i)
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
				sld.lifeday = 0;
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
			}
			LAi_LocationFightDisable(loadedLocation, false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("PKM_Animists", "12");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("xia", "as"));
			pchar.questTemp.PKM_SvtvA_SanJuanChurch_1_Zlo = "Church1";
			PChar.quest.PKM_SvtvA_SJ_B1.over = "yes";
			PChar.quest.PKM_SvtvA_SJ_B2.over = "yes";
			PChar.quest.PKM_SvtvA_SJ_B3.over = "yes";
		break;
		
		case "Знакомство с Жаком":
			dialog.text = "Captain, I don't even know how to thank you! If it weren't for you, my ship and its entire crew would already be lying in the depths of the sea. My name is Jacqueline de Masset, Knight of the Order of Malta.";
			link.l1 = "Nice to meet you, Jacqueline. And I'm " + GetFullName(pchar)+".";
			link.l1.go = "Знакомство с Жаком_2";
		break;
		case "Знакомство с Жаком_2":
			dialog.text = "So you're captain I was warned about by pigeon mail.";
			link.l1 = "You are right in your guesses. I have instructions to escort you to Puerto Rico.";
			link.l1.go = "Знакомство с Жаком_3";
		break;
		case "Знакомство с Жаком_3":
			dialog.text = "Okay. In that case, we can hit the road.";
			link.l1 = "Great! Then let's not delay!";
			link.l1.go = "Знакомство с Жаком_4";
		break;
		case "Знакомство с Жаком_4":
			DialogExit();
			pchar.questTemp.PKM_SvtvA_Znakomstvo_s_Malta2 = true;
			pchar.questTemp.PKM_SvtvA_Dostavka_Malty = true;
			SetCompanionIndex(pchar, -1, sti(NPChar.index));
			SetShipRemovable(npchar, false);
			SetCharacterRemovable(npchar, false);
			AddQuestRecord("PKM_Animists", "18");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("xia", "as"));
			npchar.dialog.currentnode = "Знакомство с Жаком_5";
		break;
		case "Знакомство с Жаком_5":
			dialog.text = "In the name of all the saints! We have no time to waste, we need to hurry to Puerto Rico.";
			link.l1 = "Yes, Jacqueline, you're right.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Знакомство с Жаком_5";
		break;
		
		case "Satanist_zasada2":
			dialog.text = "I don't think you're going anywhere! Give me the letter now!";
			link.l1 = "Maybe we'll have a mug of ale and go our separate ways? No? I knew it.";
			link.l1.go = "Satanist_zasada2_2";	
		break;
		
		case "Satanist_zasada2_2":
			dialog.text = "Stop clowning around! I'm counting to three, and if you don't give us the letter, then you can blame yourself. One...";
			link.l1 = "Three!";
			link.l1.go = "Satanist_zasada2_3";
		break;
		
		case "Satanist_zasada2_3":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Satanist_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PKM_SvtvA_Zasada2_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Сатанист_крыса":
			dialog.text = "Die! Satan is coming! You can't stop him!";
			link.l1 = "The Devil! Your assistant is a Satanist!";
			link.l1.go = "Сатанист_крыса_2";
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Satanist_"+i, "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				sld.DontChangeGun = true;
				sld.DeleteFood = true;
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1_back");
				GiveItem2Character(sld, "PKM_SvtvA_znachok");
				AddItems(sld, "mineral3", rand(7)-4);
			}
		break;
		
		case "Сатанист_крыса_2":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			sld = CharacterFromID("Satanist_Krisa")
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Satanist");
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("Satanist_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Satanist");
			}
			LAi_group_SetRelation("Satanist", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Satanist", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("Satanist", "PKM_SvtvA_Нападение_в_церкви_Победа");
			LAi_SetFightMode(pchar, true);
			
			DoQuestFunctionDelay("PKM_SvtvA_Malta_na_pomosh", 15.0);
		break;
		
		case "Победа_в Церкви":
			dialog.text = "Who would have thought Father Gareth worshipped the Prince of Darkness... Who would have thought...";
			link.l1 = "But now I know who caused me so much trouble! He was the one who reported all my movements to these monks.";
			link.l1.go = "Победа_в Церкви_2";
		break;
		
		case "Победа_в Церкви_2":
			dialog.text = "Monks?! No, they are not monks. They are servants of the Devil!";
			link.l1 = "Hmm... But their cloth...";
			link.l1.go = "Победа_в Церкви_3";
		break;
		
		case "Победа_в Церкви_3":
			dialog.text = "Yes, you are right. But first we need to find out where the pagans' lair is. I think it would be best if you go to San Juan and try to find out more information there.";
			link.l1 = "Then bless me.";
			link.l1.go = "Победа_в Церкви_4";
		break;
		
		case "Победа_в Церкви_4":
			dialog.text = "That's not all. I would like to introduce one person...";
			link.l1 = "";
			link.l1.go = "Победа_в Церкви_5";
		break;
		
		case "Победа_в Церкви_5":
			DialogExit();
			StartInstantDialog("Maltese", "Победа_в Церкви_6", "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c");
		break;
		
		case "Победа_в Церкви_6":
			dialog.text = "We've already met, Captain "+pchar.name+".";
			link.l1 = "Jacqueline! How did you get here in time! I would not have coped here alone. Your help came in handy here.";
			link.l1.go = "Победа_в Церкви_7";
		break;
		
		case "Победа_в Церкви_7":
			dialog.text = "I am glad that I was useful to you. But let's get down to business. A few years ago, I took part in the defeat of the pagans in Italy...";
			link.l1 = "Ah, and now you've come here to finish the job you started?";
			link.l1.go = "Победа_в Церкви_8";
		break;
		
		case "Победа_в Церкви_8":
			dialog.text = "That's right. And if you don't mind, I'll join you.";
			link.l1 = "Well, you know the enemy by sight, you know how to fight, I see no reason to refuse.";
			link.l1.go = "Победа_в Церкви_9";
		break;
		
		case "Победа_в Церкви_9":
			dialog.text = "Glad to have your agreement. Well, give the order, Captain.";
			link.l1 = "To Puerto Rico! We need more information.";
			link.l1.go = "Победа_в Церкви_10";
		break;
		
		case "Победа_в Церкви_10":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			PChar.quest.PKM_SvtvA_MalteseMertv.over = "yes";
		
			sld = CharacterFromID("Maltese");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetShipRemovable(sld, true);
			SetCharacterRemovable(sld, true);
			sld.location = "None";
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.rank = 15;
			LAi_SetHP(sld, 250.0, 250.0);
			sld.HalfImmortal = true;
			sld.HasNoFear = true;		//Не убегает
		
			sld = CharacterFromID("FortFrance_Priest");
			LAi_SetPriestType(sld);
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Победа_в Церкви_11";
			
			sld = CharacterFromID("SanJuan_Priest");
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Падре_Робано";			
			
			PChar.quest.PKM_SvtvA_PriestVernuDialog.win_condition.l1 = "ExitFromLocation";
			PChar.quest.PKM_SvtvA_PriestVernuDialog.win_condition.l1.location = PChar.location;
			PChar.quest.PKM_SvtvA_PriestVernuDialog.win_condition = "PKM_SvtvA_PriestVernuDialog";
			
			pchar.questTemp.PKM_SvtvA_PoiskPadre_Tavern = true;
			
			AddQuestRecord("PKM_Animists", "21");
		break;
		
		case "Победа_в Церкви_11":
			dialog.text = "Don't worry about me, I'll clean up here. You'd better start looking for a pagan lair.";
			link.l1 = "Yes, I'm leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Победа_в Церкви_11";
		break;
		
		case "Падре_Робано":
			dialog.text = "Padre Dominguez was abducted by some strange people? What should I do, what should I do...";
			link.l1 = "The Devil! I don't like it anymore!";
			link.l1.go = "Падре_Робано_2";
			locCameraFromToPos(2.00, 3.00, -2.00, true, -4.00, -0.20, -12.50);
		break;
		
		case "Падре_Робано_2":
			dialog.text = "Stop blaspheming in the house of the Lord!";
			link.l1 = "Really? And what will happen to me if I say something else? For example: Damn! Satan!";
			link.l1.go = "Падре_Робано_3";
		break;
		
		case "Падре_Робано_3":
			dialog.text = "";
			link.l1 = "Uh-huh... What was that?!";
			link.l1.go = "Падре_Робано_4";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "hit_fire", "", 2);
			LAi_SetAfraidDead(pchar);
			DoQuestFunctionDelay("PKM_SvtvA_Gospod_nakazal", 1.15);
			LaunchBlood(pchar, 1.0, true);
			LaunchBlood(pchar, 2.0, true);
			LAi_SetCurHP(pchar, 30.0);
		break;
		
		case "Падре_Робано_4":
			dialog.text = "Miracle! It was a miracle! God for some reason decided to remind you of his existence in this way! Oh! I will read 20 times today 'The Lord's Prayer' on this subject, and I will give you an extra service!";
			link.l1 = "Kha-kha. Do as you like, and I'll probably go.";
			link.l1.go = "Падре_Робано_5";
		break;
		
		case "Падре_Робано_5":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("SanJuan_Priest");
			sld.dialog.filename = "Common_church.c";
			sld.dialog.currentnode = "First time";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;
		
		case "Джордано_1":
			dialog.text = "Did you bring news from the Teacher? He said he would send his man.";
			link.l1 = "Yes, I'm from the Teacher, but maybe you won't yell about it all over the street, sucker?";
			link.l1.go = "Джордано_2";
			PlayVoice("Kopcapkz\Voices\Quest\Spa_m_b_001.wav");
		break;
		
		case "Джордано_2":
			dialog.text = "Oh! From the Teacher! I knew it! Oh, I'm sorry, of course I'll keep it down. Where's your locket?";
			link.l1 = "Yeah, I remembered about him after all, otherwise you jump like a puppy, you forgot about everything. Here it is, the medallion.";
			link.l1.go = "Джордано_3";
		break;
		
		case "Джордано_3":
			dialog.text = "Oh! I knew it was you! Then I'll run and tell the others. When do we leave?";
			link.l1 = "Are we sailing? You know everything. Maybe you even know where to go?";
			link.l1.go = "Джордано_4";
		break;
		
		case "Джордано_4":
			dialog.text = "No, the Teacher didn't tell us.";
			link.l1 = "That's good - you have nothing to know about such things yet, otherwise you'll blab to anyone. And where is the Teacher himself? We won't sail anywhere without him.";
			link.l1.go = "Джордано_5";
		break;
		
		case "Джордано_5":
			dialog.text = "He said he was going to Port-au-Prince for a few days. However, he was supposed to come back yesterday, but he's still not here.";
			link.l1 = "Strange. Then I think our voyage is postponed.";
			link.l1.go = "Джордано_6";
		break;		
		
		case "Джордано_6":
			dialog.text = "How? Why?";
			link.l1 = "Do you really think that we will sail without him? I need to find out what happened to him first, and only then will we hit the road.";
			link.l1.go = "Джордано_7";
		break;
		
		case "Джордано_7":
			DialogExit();
			
			sld = CharacterFromID("PKM_Jordano");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "houseF2", "none", "", "", "PKM_SvtvA_IdemSledom", -1);
			
			AddQuestRecord("PKM_Animists", "26");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("la", "a"));
			AddQuestUserData("PKM_Animists", "sSex1", GetSexPhrase("", "a"));
			
			pchar.questTemp.PKM_SvtvA_PoiskUchitel_Tavern = true;
		break;
		
		case "Разговор с тюремщиком":
			dialog.text = "" + TimeGreeting() + ", "+ GetSexPhrase("monsieur", "mademoiselle") +". What do you want?";
			link.l1 = "I need to talk to a prisoner.";
			link.l1.go = "Разговор с тюремщиком_2";
		break;
		
		case "Разговор с тюремщиком_2":
			dialog.text = "Actually, we are prohibited from talking to prisoners...";
			link.l1 = "But, let me! I am engaged in a matter of national importance!";
			link.l1.go = "Разговор с тюремщиком_3";
			link.l2 = "(pulling out a gun) You take me to the prisoner right now, or, by God, I'll kill you!";
			link.l2.go = "Угроза тюремщику_1";
		break;
		
		case "Разговор с тюремщиком_3":
			dialog.text = "What other business is this? What are you even talking about?!";
			if (sti(pchar.reputation) > 80)
			{
				link.l1 = "You've probably heard about the kidnapping of children, that strange things have been happening in the archipelago lately? So, your prisoner can help me deal with all this!";
				link.l1.go = "Уговариваем тюремщика_1";
			}
			else
			{
				link.l1 = "You've probably heard about child abduction, that...";
				link.l1.go = "Деньги тюремщику_1";
			}
		break;
		
		case "Уговариваем тюремщика_1":
			dialog.text = "Okay, okay, convinced. I'm not happy about what's going on myself. You can talk to that bastard, he'll be strung up in the afternoon anyway.";
			link.l1 = "Great! Thank you!";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			NextDiag.TempNode = "Уговариваем тюремщика_2";
			
			AddQuestRecord("PKM_Animists", "30");
			
			sld = CharacterFromID("Satanist_Uchitel");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Учитель_Спасение";
		break;
		
		case "Уговариваем тюремщика_2":
			dialog.text = "I hope you get all the information you need out of this scumbag.";
			link.l1 = "Thank you, Officer. I'm already looking for his cell.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Уговариваем тюремщика_2";
		break;
		
		case "Деньги тюремщику_1":
			dialog.text = "You're just wasting your time. Although... If you will do me a favor...";
			link.l1 = "What other service?";
			link.l1.go = "Деньги тюремщику_2";
		break;
		
		case "Деньги тюремщику_2":
			dialog.text = "My son's wedding is coming up, and I'd like to celebrate this big-time... Anyway, if you want to talk to a prisoner, for 40,000 piastres, I'd be happy to let you do it.";
			if (sti(pchar.Money) >= 40000)
			{
				link.l1 = "Here's your money.";
				link.l1.go = "Деньги тюремщику_3_да";
			}
			link.l2 = "I'm afraid I have no other choice... Defend yourself!";
			link.l2.go = "Деньги тюремщику_3_нет";
		break;
		
		case "Деньги тюремщику_3_нет":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			LAi_group_AttackGroup("FRANCE_CITIZENS", LAI_GROUP_PLAYER);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Деньги тюремщику_3_да":
			dialog.text = "Okay, you can talk to the prisoner.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			NextDiag.TempNode = "Деньги тюремщику_4_да";
			
			AddQuestRecord("PKM_Animists", "29");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			
			sld = CharacterFromID("Satanist_Uchitel");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Учитель_Спасение";
		break;
		
		case "Деньги тюремщику_4_да":
			dialog.text = "Something else?";
			link.l1 = "No. Just checking out the prison.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Деньги тюремщику_4_да";
		break;
		
		case "Угроза тюремщику_1":
			dialog.text = "What the... You will be responsible for this!";
			link.l1 = "Maybe, but now you are my prisoner. So sit still until I release the prisoner.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			NextDiag.TempNode = "Угроза тюремщику_2";
			
			AddQuestRecord("PKM_Animists", "28");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			ChangeCharacterReputation(pchar, -30);
			ChangeCharacterNationReputation(pchar, FRANCE, -30);
		break;
		
		case "Угроза тюремщику_2":
			dialog.text = "What else do you want?";
			link.l1 = "Nothing. Sit still and don't twitch.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Угроза тюремщику_2";
		break;
		
		case "Учитель_Смерть":
			dialog.text = "What do you need from me?!";
			link.l1 = "Tell me where your lair is and I'll let you die quickly.";
			link.l1.go = "Учитель_Смерть_1";
			PChar.quest.PKM_SvtvA_TuremchikKonets.over = "yes";
		break;
		
		case "Учитель_Смерть_1":
			dialog.text = "Are you trying to scare me?! I am a servant of the forces of chaos! I'm not afraid of death!";
			link.l1 = "Hmm... indeed...";
			link.l1.go = "Учитель_Смерть_2";
		break;
		
		case "Учитель_Смерть_2":
			dialog.text = "What does death mean to me! For me, who is going to take a worthy place at the foot of his master's throne!";
			link.l1 = "Maybe you're not afraid of death. What about a life sentence in this cage?";
			link.l1.go = "Учитель_Смерть_3";
		break;
		
		case "Учитель_Смерть_3":
			dialog.text = "...";
			link.l1 = "But this is still quite a cozy cell, I can request that you be transferred to a more gloomy and damp place.";
			link.l1.go = "Учитель_Смерть_4";
		break;
		
		case "Учитель_Смерть_4":
			dialog.text = "...";
			link.l1 = "Icy water on the floor, not giving a minute's rest, rotting flesh... It sounds good, damn it!";
			link.l1.go = "Учитель_Смерть_5";
		break;
		
		case "Учитель_Смерть_5":
			dialog.text = "Wait! I'll tell you everything. What do you need?";
			link.l1 = "Where is your lair?";
			link.l1.go = "Учитель_Смерть_6";
		break;
		
		case "Учитель_Смерть_6":
			dialog.text = "On the island of Maria Galante, near...";
			link.l1 = "";
			link.l1.go = "Учитель_Смерть_7";
			npchar.lifeday = 0;
			LAi_SetHP(npchar, 1.0, 1.0);
		break;
		
		case "Учитель_Смерть_7":
			dialog.text = "Kha... noooo... hmm...";
			link.l1 = "What the?!";
			link.l1.go = "Учитель_Смерть_8";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "death_citizen_1", "", 2.0);
			DoQuestFunctionDelay("PKM_SvtvA_Uchitel_smert", 2.2);
		break;
		
		case "Учитель_Смерть_8":
			DialogExit();
			
			AddQuestRecord("PKM_Animists", "32");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition.l1 = "ExitFromLocation";  //Выход из локации
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition.l1.location = PChar.location;
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition = "PKM_SvtvA_TuremchikDialog";
				
			locations[FindLocation("Guadeloupe_deadlock")].models.day.charactersPatch = "jungle9_patch";
			locations[FindLocation("Guadeloupe_deadlock")].models.night.charactersPatch = "jungle9_patch";
			Locations[FindLocation("Guadeloupe_deadlock")].models.always.l4 = "jungle9_nowall";
			
			PChar.quest.LogovoSatanistov.win_condition.l1 = "location";
			PChar.quest.LogovoSatanistov.win_condition.l1.location = "Cave_Satanists";
			PChar.quest.LogovoSatanistov.win_condition = "LogovoSatanistov";
		break;
		
		case "Учитель_Спасение":
			dialog.text = "What do you want from me, you dirty pigs?!";
			link.l1 = "We have come to free you.";
			link.l1.go = "Учитель_Спасение_1";
			PChar.quest.PKM_SvtvA_TuremchikKonets.over = "yes";
		break;
		
		case "Учитель_Спасение_1":
			dialog.text = "How nice of you. And why on earth did I get such a favor?";
			link.l1 = "There is no time to explain. At any moment, they may discover that the papers for your release have been forged.";
			link.l1.go = "Учитель_Спасение_2";
		break;
		
		case "Учитель_Спасение_2":
			dialog.text = "Even so? Fine. I allow you to accompany me to San Juan, and then we will decide what to do with you next.";
			link.l1 = "Whatever you say.";
			link.l1.go = "Учитель_Спасение_3";
		break;
		
		case "Учитель_Спасение_3":
			DialogExit();
			
			AddQuestRecord("PKM_Animists", "31");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition.l1 = "ExitFromLocation";  //Выход из локации
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition.l1.location = PChar.location;
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition = "PKM_SvtvA_TuremchikDialog";
			
			sld = CharacterFromID("Satanist_Uchitel");
			ChangeCharacterAddressGroup(sld, "PortPax_prison", "goto", "goto23");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			AddPassenger(pchar, sld, true);
			
			PChar.quest.PKM_SvtvA_UchitelPassakir.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_UchitelPassakir.win_condition.l1.location = "PuertoRico";
			PChar.quest.PKM_SvtvA_UchitelPassakir.win_condition = "PKM_SvtvA_UchitelPassakir";
		break;
		
		case "Обманываем Учителя":
			dialog.text = "We're almost in San Juan, but you didn't have time to prove yourself. Can't you make it up to me?";
			link.l1 = "Whatever you say.";
			link.l1.go = "Обманываем Учителя_2";
		break;
		
		case "Обманываем Учителя_2":
			dialog.text = "In that case, immediately after landinging, I hope to see you in one of the rooms of the tavern.";
			link.l1 = "Okay.";
			link.l1.go = "Обманываем Учителя_3";
		break;
		
		case "Обманываем Учителя_3":
			DialogExit();
			
			if (GetDaysContinueNationLicence(SPAIN) < 2) GiveNationLicence(SPAIN, 2);
			DoQuestReloadToLocation("SanJuan_tavern_upstairs", "goto", "goto2", "PKM_SvtvA_UchitelvTaverne");
		break;
		
		case "Обманываем Учителя_4":
			dialog.text = "Yes, I see that you are not lying, and you are really connected with our Brotherhood. The version of this boy completely coincides with yours, I do not know when and where you joined us, it does not matter now, what is important is that we urgently need to go to our shelter, as the time is right for the ritual.I think you'll agree to escort me and some of the locals to our temple?";
			link.l1 = "Of course. Just tell me where we need to go.";
			link.l1.go = "Обманываем Учителя_5";
		break;
		
		case "Обманываем Учителя_5":
			dialog.text = "Our temple is located on the island of Maria Galante. That's where we plan - and...";
			link.l1 = "...Well, now I've found out all I need. I think it's time for you to die.";
			link.l1.go = "Обманываем Учителя_6";
		break;
		
		case "Обманываем Учителя_6":
			dialog.text = "What?! So you...";
			link.l1 = "Yes, I don't belong to your fraternity. Now defend yourself!";
			link.l1.go = "Обманываем Учителя_7";
			LAi_group_MoveCharacter(pchar, "PIRATE_CITIZENS");
		break;
		
		case "Обманываем Учителя_7":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_group_Attack(characterFromId("Satanist_Uchitel"), Pchar);
			LAi_SetFightMode(pchar, true);
			
			PChar.quest.PKM_SvtvA_UbivaemUchitelya.win_condition.l1 = "NPC_Death";
			PChar.quest.PKM_SvtvA_UbivaemUchitelya.win_condition.l1.character = "Satanist_Uchitel";
			PChar.quest.PKM_SvtvA_UbivaemUchitelya.win_condition = "PKM_SvtvA_UbivaemUchitelya";
		break;
		
		case "Спасите, помогите1":
			dialog.text = "Save me! Get us out!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Спасите, помогите1";
		break;
		
		case "Спасите, помогите2":
			dialog.text = "Don't leave us here! I don't want to die!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Спасите, помогите2";
		break;
		
		case "Спасите, помогите3":
			dialog.text = "Unlock the grate! I want to get out of here!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Спасите, помогите3";
		break;
		
		case "Домингес в клетке":
			dialog.text = ""+ GetSexPhrase("My son", "My daughter") +"... Is it really you?";
			link.l1 = "Yes, it's me, Holy Father.";
			link.l1.go = "Домингес в клетке_2";
		break;
		
		case "Домингес в клетке_2":
			dialog.text = "I was captured immediately after your departure from San Juan. But I am glad that you have managed to find the lair of these soulless pagans. Their leader, Black Sun, is sitting in the throne room. You need to stop him!";
			link.l1 = "Don't worry, Holy Father. I'm here just to put an end to this diabolical sect.";
			link.l1.go = "Домингес в клетке_3";
		break;
		
		case "Домингес в клетке_3":
			dialog.text = "In that case, I will pray for you!";
			link.l1 = "I won't let you down!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Домингес в клетке_4";
		break;
		
		case "Домингес в клетке_4":
			dialog.text = "I will pray for you!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Домингес в клетке_4";
		break;
		
		case "Лорд_Хаоса_1":
			dialog.text = "You'll die and the demons will dance on your bones, you slug!";
			link.l1 = "Well, yes, of course, I'm going to die right now. I'm dreaming!";
			link.l1.go = "Лорд_Хаоса_2";
			PlayVoice("Kopcapkz\Voices\Quest\Dark_teacher.wav");
		break;
		
		case "Лорд_Хаоса_2":
			DialogExit();
			
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Chernoe_Solntse");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto57");
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("Satanist_"+i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			}			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("Satanist_Oderjim_"+i);
				LAi_SetImmortal(sld, false);
				LAi_group_MoveCharacter(sld, "Chernoe_Solntse_sluga");
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Satanist_Turma_"+i);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			}
			if (!CheckAttribute(pchar, "questTemp.PKM_SvtvA_Satanist_Kuhnya_Pobeda"))
			{
				for (i=1; i<=5; i++)
				{
					sld = CharacterFromID("Satanist_Kuhnya_"+i);
					LAi_SetHP(sld, 180.0, 180.0);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
					LAi_group_SetRelation("Chernoe_Solntse", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
					LAi_group_SetLookRadius("Chernoe_Solntse", 10.0);
					LAi_group_SetHearRadius("Chernoe_Solntse", 3.0);
					LAi_group_SetSayRadius("Chernoe_Solntse", 1.0);
					ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto8");
				}
			}
			
			PChar.quest.PKM_SvtvA_KuhnyaStels1.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels2.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels3.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels4.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels5.over = "yes";
			
			LAi_group_SetRelation("Chernoe_Solntse", "Chernoe_Solntse_sluga", LAI_GROUP_FRIEND);
			LAi_group_SetRelation("Chernoe_Solntse_sluga", "Chernoe_Solntse", LAI_GROUP_FRIEND);
			
			LAi_group_SetRelation("Chernoe_Solntse", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Chernoe_Solntse", LAI_GROUP_PLAYER, true);
			
			//LAi_group_SetRelation("Chernoe_Solntse_sluga", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			//LAi_group_FightGroups("Chernoe_Solntse_sluga", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Chernoe_Solntse_sluga", "PKM_SvtvA_Lord_Haos_Padet");
		break;
		
		case "Лорд_Хаоса_3":
			dialog.text = "No! This can't be happening!..";
			link.l1 = "What? Didn't you expect someone to tear your gloomy hideout to shreds?";
			link.l1.go = "Лорд_Хаоса_4";
			
			sld = CharacterFromID("Satanist_Oderjim_1");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Oderjim_2");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Oderjim_3");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Oderjim_4");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Oderjim_5");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;
		
		case "Лорд_Хаоса_4":
			dialog.text = "It's not over yet...";
			link.l1 = "";
			link.l1.go = "Лорд_Хаоса_5";
		break;
		
		case "Лорд_Хаоса_5":
			dialog.text = "";
			link.l1 = "Uh, where are you going? Coward!";
			link.l1.go = "exit";
			
			sld = CharacterFromID("Chernoe_Solntse");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "goto", "goto28", "none", "", "", "PKM_SvtvA_Lord_Haos_Pobeda_no_ne_sovsem2", 4);
		break;
		
		case "Спасение пленников":
			dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", did we win?";
			link.l1 = "There is nothing left of their lair, Holy Father, but their leader managed to escape...";
			link.l1.go = "Спасение пленников_2";
		break;
		case "Спасение пленников_2":
			dialog.text = "It's okay, "+ GetSexPhrase("my son", "my daughter") +". While you were fighting these demons, I managed to free all the civilians.";
			link.l1 = "Great! My ship '" + PChar.Ship.Name + "' is standing in the bay, take them on board. I'll follow you and make sure that not a single creature gets out of the ambush. Go ahead!";
			link.l1.go = "Спасение пленников_3";
		break;
		
		case "Спасение пленников_3":
			DialogExit();
			AddQuestRecord("PKM_Animists", "34");
			sld = CharacterFromID("Plennik_Dominges");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "PKM_SvtvA_Dominges_na_bort", -1);
		break;
		
		case "Домингес_спасён_1":
			dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", finally, all these horrors are behind us. You can't even imagine what kind of trouble you've prevented.";
			link.l1 = "You say that as if they were going to create a portal to hell from which a huge army of evil spirits would come out.";
			link.l1.go = "Домингес_спасён_2";
		break;
		
		case "Домингес_спасён_2":
			dialog.text = "It's scary to imagine what would happen if they had time to perform their demonic rite. But it doesn't matter anymore. I will go to the church service now, and I will thank the Lord God for the help he gave you in that sacred battle.";
			link.l1 = "Goodbye, Holy Father. It was an honor for me to serve the Light.";
			link.l1.go = "Домингес_спасён_3";
		break;
		
		case "Домингес_спасён_3":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			sld = CharacterFromID("Plennik_Dominges");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload7", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			sld = CharacterFromID("SanJuan_Priest");
			sld.name		= "Padre Dominguez";
			sld.lastname = "";
			sld.dialog.filename = "Common_church.c";
			sld.dialog.currentnode = "First time";
			
			AddQuestRecord("PKM_Animists", "40");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.PKM_Animists_PadreDominges = true;
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
		
		case "Verni_detey_11":
			dialog.text = "Are you back? Where are our little kids?";
			link.l1 = "Your children are completely safe. They're being ferried ashore from my ship right now.";
			link.l1.go = "Verni_detey_12";
		break;
		
		case "Verni_detey_12":
			dialog.text = "Oh! Thank you, thank you, "+GetSexPhrase("kind man", "kind girl")+"!";
			link.l1 = "You're welcome.";
			link.l1.go = "Verni_detey_13";
		break;
		
		case "Verni_detey_13":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterReputation(pchar, 12);
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_1")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_2")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_3")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			
			AddQuestRecord("PKM_Animists", "37");
			pchar.questTemp.PKM_Animists_MamaDeti = true;
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
}
