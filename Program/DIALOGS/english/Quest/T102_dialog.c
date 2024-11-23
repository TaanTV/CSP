//мумия в алькове
void ProcessDialogEvent()
{
	ref NPChar, PChar, d;
	PChar = GetMainCharacter();
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "First time":
			dialog.text = "... (the skeleton takes away the metal arm and clanks it into place, the arm begins to move)";
			link.l1 = "What is it?!";
			link.l1.go = "Term_1";
			TakeNItems(Pchar, "term_arm", -1);
			LAi_CharacterPlaySoundAtOnce(NPChar, "T102_Intro");
		break;

		case "Term_1":
			dialog.text = "I am a cyborg of the T-102 brand, manufactured by Skynet Production, enclave of Detroit, class of 2022. I've caught up with you, man from a strange ship.";
			link.l1 = "Who? What? What kind of Ki Borg? What year is it? It's the seventeenth century since the birth of Christ! You are evil spirits! But for some reason it's metal, which is strange.";
			link.l1.go = "Term_2";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_1");
			if(startherotype == 2)
			{
				link.l1 = "Skynet Production? I've never heard of such a corporation. Damn it, it seems that by my actions here I violated the temporal sequence, which gave rise to an alternative future. Tell me, do you know anything about Omnitech Corporation? It seems that in 2022 it already existed.";
				link.l1.go = "Whisper_Term_2";
			}

		break;

		case "Whisper_Term_2":
			dialog.text = "There are no matches in my database for this query.";
			link.l1 = "Damn it! This is very bad. Anyway, what are you doing at this time?";
			link.l1.go = "Term_3";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_2");
		break;

		case "Term_2":
			dialog.text = "Don't argue with me, a biological individual who identifies himself as " +GetFullName(pchar) +
			              ". I am a bio-coated machine, a cyborg. The coating had a shorter service life than the main base made of an alloy of metallic polymers. For 170 years, the bio-cover has been lost. My resource is at its limit. The nuclear power supply is down, I'm working on standby.";
			link.l1 = "A century and a half? I didn't understand then. When were you born-in the 15th century or in the 21st?";
			link.l1.go = "Term_3";
			if (startherotype > 0 && startherotype < 10) LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_3_"+startherotype);
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_3_unknown");
		break;

		case "Term_3":
			dialog.text = "Error. Main power is too low. Critical error - restarting....";
			link.l1 = "What?";
			link.l1.go = "Term_4";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_4");
		break;

		case "Term_4":
			dialog.text = "Loading from backup store....";
			link.l1 = "What's the matter with him? My dear, who are you talking to now? I don't talk to evil spirits at all, I make an exception here, but he does!";
			if(startherotype == 2)
			{
				link.l1 = "It looks like he's breathing hard, he's about to fall apart. Hey, are you here?";
			}
			link.l1.go = "Term_5";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_5");
		break;

		case "Term_5":
			dialog.text = "System ready.......I am a cyborg of the T-102 brand, manufactured by Skynet Production, Enclave of Detroit, release 2022.";
			link.l1 = "I've already heard that! Don't piss me off, you stupid piece of hardware!";
			link.l1.go = "Term_6";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_6");
		break;

		case "Term_6":
			dialog.text = "My mission was to go back in time, the year is 1985, the goal is Sarah Connor, destruction.";
			link.l1 = "And we have it now " + GetDataYear() + "-th year! And there's no Sarah here.";
			if(startherotype == 2)
			{
				link.l1 = "You missed the year by a lot, just like me.";
			}
			link.l1.go = "Term_7";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_7");
		break;

		case "Term_7":
			dialog.text = "When sending, the distortions caused by weapons and uniforms were not taken into account. The timing has failed. Delivery at the end of the 15th century. The main task is to complete the mission. The search did not yield any results.";
			link.l1 = "Let's say, what does this have to do with me?";
			link.l1.go = "Term_8";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_8");
		break;

		case "Term_8":
			dialog.text = "An integral part of the database is a manipulator. The manipulator has a marker - took him. The manipulator was lost during operation 'I'll be back', conducted on a strange ship 30 years ago. Unidentifiable inhabitants of the ship, missing from the catalog of the identification database, turned out to be aggressive, but poorly destructible objects. The definition is cyborgs with a biological basis, the source of energy is unknown.";
			link.l1 = "Oh, is it on a ghost ship or something? It's clear that they themselves are like you, only there are more of them, so they threw hats! I've suffered from them too.";
			if(startherotype == 2)
			{
				link.l1 = "Oh, are you talking about a ghost ship or something? I've suffered from him too.";
			}
			link.l1.go = "Term_9";
			if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_9_man");
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_9_woman");
		break;

		case "Term_9":
			dialog.text = "Now the manipulator is integrated and functioning correctly. Previously, it was inaccessible due to a water barrier and constant relocation.";
			link.l1 = "Who goes where correctly what?";
			link.l1.go = "Term_9_1";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_10");
		break;

		case "Term_9_1":
			dialog.text = "It's not important.";
			link.l1 = "Oh, so operation 'I'll be back' is just a runaway? Or, as I say, to make a maneuver of strategic distance from the enemy.";
			link.l1.go = "Term_9_2";
		break;

		case "Term_9_2":
			dialog.text = "Yes, an individual '" +GetFullName(pchar) +"', you're right. My time is running out with the discharge of the backup battery. The mission cannot be completed, the object has not been detected, and genetic analysis has shown the absence of the target's closest ancestors in this area.";
			link.l1 = "Yeah, you're out of luck. It's time, apparently, to retire. I've already figured out where to get a good weapon. If I meet Sarah about'Kohner, I will definitely kill you, as payment for such a gift from descendants.";
			if(startherotype == 2)
			{
				link.l1 = "Yeah, you're out of luck. Well, if you don't have a functioning time machine with you, then there's nothing more to talk about. I'll go, I think.";
			}
			link.l1.go = "Term_11";
			if (startherotype > 0 && startherotype < 10) LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_11_"+startherotype);
			else
			{
				if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_11_man");
				else LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_11_woman");
			}

		break;

		case "Term_10":
			dialog.text = "Thank you for your cooperation. Scanning in process... complete... I don't need your clothes. Goodbye.";
			link.l1 = "Here! Do good deeds, and they will not leave you alone!";
			link.l1.go = "Term_10_exit";
			//PChar.GenQuest.GhostShip.TakeShotgun = true;
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_12");
		break;

		case "Term_10_exit":
            LAi_SetPlayerType(PChar);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);
			//ChangeCharacterAddressGroup(NPChar, "none", "", "");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Term_11":
			dialog.text = "Scanning in process... complite... Your phenotype is 68 percent similar to Sarah Connor. You're a potential ancestor. The mission must be completed. Proceed immediately.";
			link.l1 = "This is the first time they have told me so intricately that they want to kill me. All right, piece of iron, I won't look at your antiquity and I'll knock the dust out of you.";
			link.l1.go = "Term_11_exit";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_13");
			if(startherotype == 2)
			{
				link.l1 = "Dumb piece of hardware, which ancestor? Don't you get it? I'm from the future myself. Have you got all your insides swimming in there already?";
				link.l1.go = "Term_11_Whisper";
			}

		break;

		case "Term_11_Whisper":
			dialog.text = "The target is being aggressive. Combat mode is activated.";
			link.l1 = "You shouldn't have started this. In my time, I managed to destroy a lot of your brother, and these were newer and more deadly models.";
			link.l1.go = "Term_11_exit";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_14");
		break;

		case "Term_11_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            NPChar.location = "none";
            LAi_SetWarriorType(NPChar);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Kill_T102");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);
			//Вытащим саблю
   			LAi_SetFightMode(Pchar, true);
			NPChar.SaveItemsForDead = true;
   			chrDisableReloadToLocation = true;
			pchar.quest.T102.win_condition.l1 = "NPC_Death";
			pchar.quest.T102.win_condition.l1.character = "T102";
			pchar.quest.T102.function = "T102_DoorUnlock";
		break;
	}
}
