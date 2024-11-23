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
		case "First time":
			NextDiag.TempNode = "First time";
		break;

		case "Gravedigger":
			dialog.text = GetSexPhrase("He", "She")+" it's moving!!! Holy Virgin, have mercy!";
			link.l1 = "BRAINS!!!";
			link.l1.go = "exit_fight";
			
			//	Здесь прописываем каюты, где появится письмо =====>			
			PChar.quest.UP_KrovPismo1.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo1.win_condition.l1.location = "My_Cabin_Small";
			PChar.quest.UP_KrovPismo1.win_condition = "UP_KrovPismo";

			PChar.quest.UP_KrovPismo2.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo2.win_condition.l1.location = "My_Cabin_Small2";
			PChar.quest.UP_KrovPismo2.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo3.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo3.win_condition.l1.location = "My_Cabin_Medium";
			PChar.quest.UP_KrovPismo3.win_condition = "UP_KrovPismo";

			PChar.quest.UP_KrovPismo4.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo4.win_condition.l1.location = "My_Cabin_Medium1";
			PChar.quest.UP_KrovPismo4.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo5.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo5.win_condition.l1.location = "My_Cabin_Medium2";
			PChar.quest.UP_KrovPismo5.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo6.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo6.win_condition.l1.location = "My_New_Cabin1";
			PChar.quest.UP_KrovPismo6.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo7.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo7.win_condition.l1.location = "My_New_Cabin2";
			PChar.quest.UP_KrovPismo7.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo8.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo8.win_condition.l1.location = "My_New_Cabin3";
			PChar.quest.UP_KrovPismo8.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo9.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo9.win_condition.l1.location = "My_Cabin_Huge";
			PChar.quest.UP_KrovPismo9.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo10.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo10.win_condition.l1.location = "My_Cabin_Quest";
			PChar.quest.UP_KrovPismo10.win_condition = "UP_KrovPismo";			
			//	<===== Здесь прописываем каюты, где появится письмо
			
			//	Читаем письмо
			PChar.quest.UP_DrugPridet.win_condition.l1 = "item";
			PChar.quest.UP_DrugPridet.win_condition.l1.item = "UP_PismoZagadka";
			PChar.quest.UP_DrugPridet.win_condition = "UP_DrugPridet";
		break;

		case "DeadmansGod":
			dialog.text = "Do you know who I am?";
			link.l1 = "Death.";
			link.l1.go = "DeadmansGod_1";
			LAi_CharacterPlaySoundAtOnce(NPChar, "DeadmansGod_0");
		break;
		case "DeadmansGod_1":
			dialog.text = "I am the balance! I separate souls from flesh and keep track of the balance in the world of the living and the dead. All living things will go through my court. You are the defendant.";
			link.l1 = "I remember... Life... Another god must judge me. Not you!";
			link.l1.go = "DeadmansGod_2";
			LAi_CharacterPlaySoundAtOnce(NPChar, "DeadmansGod_1");
		break;
		case "DeadmansGod_2":
			dialog.text = "You died far from the places where your god is strong. And what does he care about you, greedy, vicious, unbelievers?";
			link.l1 = "Let me...";
			link.l1.go = "DeadmansGod_3";
			LAi_CharacterPlaySoundAtOnce(NPChar, "DeadmansGod_2");
		break;
		case "DeadmansGod_3":
			dialog.text = "SHUT UP! You don't deserve peace or punishment. Your ancestors are not here, and your god is powerless here, there is no place for your soul or your ashes.\n I could erase what's left of you from realities and probabilities! Easy! Even though I'm an impartial judge, I don't mind playing with a slave of someone else's god at all. I will take your death and give you NON-LIFE in return.\n There are others like you, and they have awakened. And what will come of it... hmm... I hope it won't be boring. Do you hear the knock? These fools are breaking the lid of your coffin. Go before I change my mind!";
			link.l1 = "...";
			link.l1.go = "DeadmansGod_4";
			LAi_CharacterPlaySoundAtOnce(NPChar, "DeadmansGod_3");
		break;
		case "DeadmansGod_4":
			DialogExit();
			DoReloadCharacterToLocation("Common_CryptBig2", "goto", "goto9");
			PlaySound("interface\grob.waw");
			DoQuestFunctionDelay("Undead_Start_Graveyard", 0.1);
			DoQuestFunctionDelay("Undead_Start_Graveyard_1", 1.0);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
		
		case "PGG_Undead_1":
			dialog.text = "(conjures) Armenamo -- delcamano -- MRISTO!";
			link.l1 = "Uh, who are you and how did you get here?";
			link.l1.go = "PGG_Undead_2";
		break;
		
		case "PGG_Undead_2":
			dialog.text = "Extraterrestrial forces are calling us. Don't you hear their call?";
			link.l1 = "I stopped hearing voices a long time ago, now I'm minding my own business.";
			link.l1.go = "PGG_Undead_3";
		break;
		
		case "PGG_Undead_3":
			dialog.text = "I'm here for a reason. Look, we don't have much time. If we do not comply with his request, then even our remaining bones will dissolve from his influence. He is strong and very domineering. I don't even know how to describe it. There has never been such power in our world. I don't have time to explain the details to you, you need to prepare well for my next visit. I can't control it, he directs me to you. You just need to have twice as much experience as you have now. See you, my bone comrade....";
			link.l1 = "What? Hey, wait! Where are you going?";
			link.l1.go = "PGG_Undead_4";
		break;
		
		case "PGG_Undead_4":
			DialogExit();
			sld = CharacterFromID("PGG_Undead")
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "UD_DrugUshel", -1);
			pchar.questTemp.UndeadPrologue3 = "UP3";
		break;
		
		case "PGG_Undead_5":
			dialog.text = "Hurry up, he's coming!";
			link.l1 = "You again, what's up? Tell me everything, otherwise our bones will rattle all over the grod!";
			link.l1.go = "PGG_Undead_6";
			TakeItemFromCharacter(pchar, "UP_PismoZagadka");
		break;
		
		case "PGG_Undead_6":
			dialog.text = "The time has come! His strength and power mock me. I'm not myself. We need to find our master! He rules over all of us, even the gods in this world! It seems to me that he will stop at nothing. Come on, we need to find him, quickly!";
			link.l1 = "Yes, can you explain the problem normally? What? Who! What for? What other host? My master is Mictlantecutli. He's the only one I can obey, for the time being.";
			link.l1.go = "PGG_Undead_7";
		break;
		
		case "PGG_Undead_7":
			dialog.text = "My goal was to bring you to him. But it's not that simple, at first I had him, but then he was taken away from me alive. I couldn't do anything but hide. Forgive me, my lord... Oh no, my lord, you're not...! I'm confused! Lil... Lila... That's it, I'm tempted by pain! I can't get out....! Help me, please!";
			link.l1 = "In business! What's holding you back so much, bone comrade? Come on, calm down and tell me in more detail, what should we do? I'll help you, I promise!";
			link.l1.go = "PGG_Undead_7_1";
		break;
		
		case "PGG_Undead_7_1":
			dialog.text = "Okay. There is one... very unusual... The subject, I... I... I can't call him by his first name, I'm sorry... We just need to find him, then you'll figure it out and see for yourself. We just need to go out to the open sea and he himself will bring the living to you. Just prepare yourself well. Although He is against the living, he still gives them strength.";
			link.l1 = "... ... I... I... I have no words. All right, get your bones, let's go. I hope I'm ready enough to figure this out.";
			link.l1.go = "PGG_Undead_8";
		break;
		
		case "PGG_Undead_8":
			dialog.text = "Collect more of our knuckles from caves and dungeons. There may be a lot of people alive and they are all under his influence.";
			link.l1 = "I get it, where are you going? Let's surf the archipelago with me? What are you but a native?";
			link.l1.go = "PGG_Undead_9";
		break;
		
		case "PGG_Undead_9":
			dialog.text = "Yes? So I'll be happy to join you. Hopefully, together we can stand up to him and all the living.";
			link.l1 = "It's crazy. I'm in trouble. I wanted to start a new life here, to honor the gods. Okay, let's see what awaits us.";
			link.l1.go = "PGG_Undead_10";
		break;
		
		case "PGG_Undead_10":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			DoQuestCheckDelay("UD_DrugUshel_2", 1.5);
			
			sld = CharacterFromID("PGG_Undead");
			sld.name = "Terrible";
			sld.lastname = "";
			sld.FaceId = 537;
			SetSPECIAL(sld, 8, 10, 8, 3, 8, 10, 8);
			GiveItem2Character(sld, "mushket");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "Energaiser");
			AddItems(sld, "bullet", 20);
			AddItems(sld, "GunPowder", 20);
			LAi_SetHP(sld, 180.0, 180.0);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.HalfImmortal = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			sld.OfficerWantToGo.DontGo = true;
		break;
	}
}
