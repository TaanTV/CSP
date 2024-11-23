// Диалог начала игры (туториал) 03.10.06 boal
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref sld;

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Finish_2":
            DoQuestFunctionDelay("Tut_locCamera_2", 0.1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_RemoveCheckMinHP(Pchar); // снимем проверки
			LAi_SetImmortal(pchar, false);
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;

		case "ChangePIRATES":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;

		case "ChangePIRATES_Jess":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5_Jess";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;

		case "Teach_battle_1":
		    LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Teach_6";
			AddDialogExitQuestFunction("Tut_TeachBattle");
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LockFightMode(Pchar, false);
			LAi_SetActorTypeNoGroup(Pchar);
			LAi_ActorTurnToCharacter(Pchar, NPChar);
			if (pchar.name == "Jessica")
			{
				dialog.text = "You're finally back on your feet, Captain. Thank God, otherwise we didn't know what to think.";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - skip and start the game";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Sandro? What the hell happened? And why does my head hurt like hell?";
				link.l1.go = "Node_1_Jess";
			}
			else
			{
				dialog.text = "Now, Captain, at least you look like yourself. How are you feeling?";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - skip and start the game";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Hmm... and who did I look like before?";
				link.l1.go = "Node_1";
			}
		break;

        case "Node_1":
			dialog.text = "Yes, these red-faced atheists, even their language was spoken.";
			link.l1     = "The Devil! Sandro, what are you talking about?!";
			link.l1.go  = "Node_2";
		break;

		case "Node_1_Jess":
			dialog.text = "So you don't remember anything? And no wonder, another would have died from such a concussion long ago, or smiled and dirtied his pants for the rest of his life, but you turned out to be a tough nut to crack. However, you are very weak, you can barely stand on your feet - soon we have been trying to get you out for six months.";
			link.l1     = "Tell me exactly what the concussion is - you see, I don't remember anything.";
			link.l1.go  = "Node_2_Jess";
		break;

		case "Node_2":
			dialog.text = "Don't worry, you can't worry. You'll get some air, look at the sea, and your head will clear up. That's what the doctor said, if he wakes up, he won't remember anything, so you don't remember, and you don't need to.";
			link.l1     = "An interesting case - what if it doesn't come?";
			link.l1.go  = "Node_3";
		break;

		case "Node_2_Jess":
			dialog.text = "Oh, what's there to tell... We told you-both me and the XO-drop this Beltrop, he'll take us to zugunder. No way!.. So you played it out until this guy in the mask sent a bullet to the back of your head! Yes, thank God and your magnificent head of hair that the bullet went through the edge. Only the bone was crushed, but it did not get stuck in the skull, otherwise you would not have lived because there was a lot of blood, and you lost consciousness - it's even good - the Mask decided that it was all over with you. By the time he rushed, we had already managed to pull you out of the ruins of that old church.";
			link.l1     = "Damn it! The mask tried to kill me... You can't trust anyone... What about Lawrence? Is he alive?";
			link.l1.go  = "Node_3_Jess";
		break;

		case "Node_3":
			dialog.text = "And if he doesn't come, he says, that's it, take him to a shelter for the mentally ill and don't even manage. For he is no longer a personal split... Hopkins and I are thinking - how can he not be if he is! Only, it seems, with a strong hangover, and he tries to swear all the time, but his tongue slurs, and his speech comes out in the manner of the natives. Read it, we've been talking to you like this for six months, and in the end we've already got used to understanding. Only the weapon was put out of harm's way, and the doctor did not tell me to give it...";
			link.l1     = "What nonsense are you talking about - did all this happen to me?";
			link.l1.go  = "Node_4";
		break;

		case "Node_3_Jess":
			dialog.text = "No, thank God. Oh, I'm sorry... They strung him up, ordered him to hang the Mask. And the Mask itself, they say, was stabbed by a shark. And for me, that's where they both go. Both are smeared with the same world - scoundrels. So much blood has been spoiled for you, scoundrels!";
			link.l1     = "It's not good about the deceased... And you can't bring back the past. God is their judge... Thank you, brothers, for pulling me out of the grave, I will not forget this.";
			link.l1.go  = "Node_4_Jess";
		break;

		case "Node_4":
			dialog.text = "Here's a cross for you. We were scared ourselves - but if you don't come to your senses, what are we going to do? And what have these red-assed bastards drugged you with, damn it! Well, thank God, you've already recovered. How are you feeling now?";
			link.l1     = "Drugged, you say... It's very similar-I don't remember anything... Let me collect my thoughts and come to my senses. (creating your own type of hero).";
			link.l1.go  = "ChangePIRATES";
			link.l2     = "Yes, I feel fine. I'm just a little dizzy, like I'm hungover...";
			link.l2.go  = "Node_5";
		break;

		case "Node_4_Jess":
			dialog.text = "It's our duty, Captain! Hopkins and I transported you to the ship and stopped the bleeding as best we could. Then the doctor was brought in- he wanted to cut your hair off, but we wouldn't let him. He was afraid that we would shoot him if you gave your soul to God, but everything worked out - now you are on your feet. How are you feeling?";
			link.l1     = "Hmm... Give me a minute to collect my thoughts...(creating your own type of hero).";
			link.l1.go  = "ChangePIRATES_Jess";
			link.l2     = "It seems like nothing anymore. Thank you for your concern, Sandro.";
			link.l2.go  = "Node_5_Jess";
		break;

		case "Node_5":
			dialog.text = "Well, you can't have alcohol, otherwise, the split will start again. But it wouldn't hurt to practice with a sword. You've probably already forgotten which end to hold it from.";
			link.l1     = "And you know what to pick up. Well, let's try, otherwise I feel like a bear with a sore head.";
			link.l1.go  = "Teach_1";
			link.l2     = "Don't worry, I had problems with my head, not with my hands. I'll go to the port, otherwise I've gone absolutely wild.";
			link.l2.go  = "Finish_1";
		break;

		case "Node_5_Jess":
			dialog.text = "Well, you see, I knew that everything would be all right... But a head wound does not go away without a trace, it will take time and perseverance to restore your strength and skills. Would you like to stretch your arm and practice fencing?";
			link.l1     = "Good idea. Let's see if I'm really falling apart.";
			link.l1.go  = "Teach_1_Jess";
			link.l2     = "No, I don't want to. I am confident in my abilities.";
			link.l2.go  = "Finish_1";
		break;

		case "Finish_1":
			if (pchar.name == "Jessica")
			{
				dialog.text = "We are currently in port " + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId) + ". We need to start a new life somehow without all these Masks and Beltrops, damn them... That is, may they rest in peace, I wanted to say... And we will not let you down, Captain. Your team will stay with you until the end.";
				link.l1     = "Well, then - to a new dream! I will not let you down or disappoint you. That's it, I'm going ashore.";
				link.l1.go  = "Finish_2";
				link.l2     = "Some scoundrels will be replaced by others - that's life, Sandro. Will you give me some advice before I go ashore?";
				link.l2.go  = "Advice_1";
			}
			else
			{
				dialog.text = "We are now at the settlement port " + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId) + ", get used to it, and come back. We really missed the real business - we had to sell the old ship, and you can't win much on this. So, we've been living in anticipation of your recovery. And the guys believe in you, otherwise they would have run away a long time ago...";
				link.l1     = "Wonderful. That's it, I'm going ashore... Don't worry so much, I am not a little kid - I won't get lost.";
				link.l1.go  = "Finish_2";
				link.l2     = "If you think I'm not ready yet - speak up. Good advice will not be superfluous.";
				link.l2.go  = "Advice_1";
			}
		break;

		case "Advice_1":
			dialog.text = "Well, cap... We need to patch up the ship, replenish the crew and stock up on supplies. And go on in search of adventures! It is better, of course, to get a patent - then we will not be outlawed if we engage in piracy, and we can honestly tell our families that our work is quite legal. And then you can make a good career and make your name famous.";
			link.l1     = "What else is worth knowing?";
			link.l1.go  = "Advice_2";
			link.l2     = "Wonderful. That's it, I'm going ashore.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_2":
			dialog.text = "To trade profitably, you need to know what the current prices of goods in the archipelago's stores are. You can find them out by visiting the shops in person, or you can ask the merchants you meet at sea or listen to rumors.";
			link.l1     = "Next.";
			link.l1.go  = "Advice_3";
			link.l2     = "Wonderful. That's it, I'm going ashore.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_3":
			dialog.text = "The guns on the ship may fail, and then they will have to be replaced. You can also remove some of the guns and free up additional space for the load.";
			link.l1     = "Next.";
			link.l1.go  = "Advice_4";
			link.l2     = "Wonderful. That's it, I'm going ashore.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_4":
			dialog.text = "If we do become privateers, then keep in mind that ships captured at sea are sold at a shipyard at bargain prices, whereas honestly bought ones can be sold at another shipyard with a good profit.";
			link.l1     = "Next.";
			link.l1.go  = "Advice_5";
			link.l2     = "Wonderful. That's it, I'm going ashore.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_5":
			dialog.text = "Do not spoil relations with smugglers for nothing - they provide a good income, albeit at a risk to health.";
			link.l1     = "Next.";
			link.l1.go  = "Advice_6";
			link.l2     = "Wonderful. That's it, I'm going ashore.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_6":
			dialog.text = "Hire officers, we don't have anyone at all. If your authority is low, you will not be able to hire many officers. In this case, hire those who can hold two or three positions at once. Three such know-it-alls will close all positions for us.";
			link.l1     = "Next.";
			link.l1.go  = "Advice_7";
			link.l2     = "Wonderful. That's it, I'm going ashore.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_7":
			dialog.text = "Theft is an unsightly thing, but it may happen that you really need to clean out a chest in some house, bank or store. Try to wait until the owner turns away, and only then climb into the chest. And remember - if the owner suddenly turns around and sees that you have climbed into his chest, then there will be trouble. So you need to be faster here!";
			link.l1     = "Next.";
			link.l1.go  = "Advice_8";
			link.l2     = "Wonderful. That's it, I'm going ashore.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_8":
			dialog.text = "You may need to infiltrate an enemy city. Remember well what I'm going to tell you now - there are no soldiers at the port and at the gates that check everyone entering the city at night! So it's better to enter an enemy city at night, and there you already know - do not get caught by the patrol. Patrol soldiers, by the way, do not have eyes on the back of their heads and see only in front of themselves and on the sides. At night in an enemy city, sneak into a tavern, spend the night there until morning, and do your business in the afternoon. But when moving around the city, stay away from the soldiers.";
			link.l1     = "Next.";
			link.l1.go  = "Advice_9";
			link.l2     = "Wonderful. That's it, I'm going ashore.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_9":
			dialog.text = "You can also raise a hostile flag on the ship, if you have one, and rely on your luck and stealth. Well, the most reliable way to safely enter an enemy city is to buy a license from a national trading company, in which case no one will detain you. However, do not forget to raise the appropriate flag on the ship. You know, it's stupid to try to show a Spanish license if the flag on the mast is English.";
			link.l1     = "Next.";
			link.l1.go  = "Advice_10";
			link.l2     = "Wonderful. That's it, I'm going ashore.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_10":
			dialog.text = "Know that the casemates are in the forts, do not look for them in the cities.";
			link.l1     = "Thank you. It's time for me to go ashore.";
			link.l1.go  = "Finish_2";
		break;
		/////   фехт
		case "Teach_1":
			dialog.text = "Well, let's start, perhaps. You've always been great at it, but I'll remind you. There are three attacking strikes: a regular punch, a lunge, and a punchy punch. There are also three defensive actions: block, parry and feint. There is also a defensive and attacking roundabout. And, of course, a pistol to treat the enemy from afar with a lead thaler.";
			link.l1     = "Okay, okay, let's get to the point.";
			link.l1.go  = "Teach_2";
		break;

		case "Teach_1_Jess":
			dialog.text = "Well, let's start, perhaps. You've always been great at it, but I'll remind you. There are three attacking strikes: a regular punch, a lunge, and a punchy punch. There are also three defensive actions: block, parry and feint. There is also a defensive and attacking roundabout. And, of course, a pistol to treat the enemy from afar with a lead thaler.";
			link.l1     = "It's clear. What's next?";
			link.l1.go  = "Teach_2";
		break;

		case "Teach_2":
			dialog.text = "Any attacking action requires energy consumption, no energy is spent on defensive actions. You can also dodge punches by bouncing back and to the sides. But this way you can get a bullet if the distance increases, and the enemy is not a fool.";
			link.l1     = "Next.";
			link.l1.go  = "Teach_3";
			link.l2     = "What is energy?";
			link.l2.go  = "Teach_2_1";
		break;

		case "Teach_2_1":
			dialog.text = "Energy is an indicator of a character's reserve of strength in hand-to-hand combat. All attacking actions require energy expenditure. In other words, during the fight, the character gets tired, and he needs a break to replenish his strength. "+
						  "The maximum energy value depends on the current magnitude of the character's reaction.";
			link.l1     = "Next.";
			link.l1.go  = "Teach_3";
		break;

		case "Teach_3":
			dialog.text = "During the fight, avoid being surrounded by a large number of opponents, otherwise you will quickly be cut into steaks. It is still possible to resist two, but it is already difficult to put down three or more at once. When the opponents' energy runs out, they will start feints and parry. Watch out, don't get caught - you'll quickly be left without a head.";
			link.l1     = "Next.";
			link.l1.go  = "Teach_4";
		break;

		case "Teach_4":
			dialog.text = "If an opponent falls for your feint, he will receive noticeable damage, more than from a stabbing blow. If you get caught parrying, then you can stay without energy. They'll knock you off the rhythm, and that's it.";
			link.l1     = "Next.";
			link.l1.go  = "Teach_5";
		break;

		case "Teach_5":
			dialog.text = "Everyone has different weapons, divided by weight into light, medium and heavy. The weight of the weapon determines the energy consumption. You can wield a light dagger tirelessly, but with a heavy axe you can send several opponents to the next world with one circular blow at a time.";
			link.l1     = "Next.";
			link.l1.go  = "Teach_6";
		break;

		case "Teach_6":
			pchar.HeroParam.Teach_battle = 1;
			Tut_RestoreState();
			dialog.text = "Well, shall we move on to practice? I suggest you stretch your bones. We will fight for real, but not to the death. Life in battle can be restored with elixirs, potions or rum, but now you better save them - we will train.";
			link.l1     = "Come on, don't expect mercy!";
			link.l1.go  = "Teach_battle_1";
			link.l2     = "No, thanks. I've already figured it out.";
			link.l2.go  = "Finish_1";
		break;

		case "Teach_battle_lose":
			Tut_RestoreState();
			dialog.text = LinkRandPhrase("Yes... You've become quite weak. Be more careful, block and parry more. Do not yawn at the punch - the block does not save you from it, use a feint, parry or rebound.",
			                             "Do not let yourself be hit, intercept the opponent's thrust with a stabbing or parry. But be careful, if you fall for a feint, they will intercept your stabbing, and they will also inflict it on you.",
										 "If the energy runs out, run away or jump away, and get the enemy with a feint. Keep in mind that a feint is not so easy to repel, but you can deceive the enemy. And if he falls for your trick, and tries to respond to your deceptive swing with a blow, then you will not only take his blade away from yourself, but also damage him yourself.");
			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1     = "Once again!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2     = "No, that's enough. I understand everything.";
			link.l2.go  = "Finish_1";
		break;

		case "Teach_battle_win":
			pchar.HeroParam.Teach_battle = 2;
			Tut_RestoreState();
			dialog.text = "Okay. Well done! Keep in mind, I fought honestly, but enemies may have their own elixirs of life, then they will not be so easy to give. " +
						  "Well, let's complicate the task. Let's go against two opponents?";
			link.l1     = "Well, come on. Hey, Hopkins! Grab your cleaver and run to the deck!";
			link.l1.go  = "Teach_battle_1";
			link.l2     = "No, thanks. I have practiced enough.";
			link.l2.go  = "Finish_1";
		break;

		case "Teach_battle_win_2":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			if (pchar.name == "Jessica")
			{
				dialog.text = "Fine, Captain! Beltrop's lessons did not go unnoticed, but he taught you well. And one last tip: the more you fence with the same type of weapon, the more your skill grows. If you want to restore mastery of all types, change the type of weapon more often.";
			}
			else
			{
				dialog.text = "Yes, everything is fine with your hands - we did not hide weapons in vain. And one last tip: the more you fence with the same type of weapon, the more your skill grows. If you want to be a master in all types, change the type of blades more often.";
			}
			link.l1     = "Thank you!";
			link.l1.go  = "Finish_1";
		break;

		case "Teach_battle_win_3":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = "Well, not bad. You have defeated one opponent, but two are not one. You need a knack here. Enemies can attack three or four together. Shall we repeat it?";
   			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1     = "Once again!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2     = "No, I've already figured it out.";
			link.l2.go  = "Finish_1";
		break;

		//Альтернативные старты
		case "Alt_start":
			EndQuestMovie();
			LAi_LockFightMode(Pchar, false);
			LAi_SetActorTypeNoGroup(Pchar);
			LAi_ActorTurnToCharacter(Pchar, NPChar);
			dialog.text = "Oh, look who's awake! I thought you were "+ GetSexPhrase("dead!", "dead!");
			link.l = "What the fuck is going on, who are you?";
			link.l.go = "Alt_start_2";
		break;

		case "Alt_start_2":
			if (pchar.sex != woman) LAi_CharacterPlaySound(NPChar, "Welcome_Fucking_Event1");
			else LAi_CharacterPlaySound(NPChar, "Welcome_Fucking_Event2");
			dialog.text = "Welcome to the Caribbean, " + GetSexPhrase("son of a bitch!", "bald scum!")+" And who am I? It's none of your business! I'm your glitch.";
			link.l = "I don't remember anything... What other Caribbean?";
			link.l.go = "Alt_start_3";
		break;

		case "Alt_start_3":
			dialog.text = "My God, with "+GetSexPhrase("what an idiot", "what a fool")+" I've been fucked on my head... Get your brains together, quickly!";
			link.l = "(creating your own type of hero)";
			link.l.go = "ChangePIRATES_Alt";
		break;

		case "ChangePIRATES_Alt":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Alt_start_4";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;

		case "Alt_start_4":
			dialog.text = "Well done! Now get to the port, get some air!";
			link.l = "(softly) You're a fucker!";
			link.l.go = "Finish_2";
		break;

		case "Alt_start2":
			EndQuestMovie();
			LAi_LockFightMode(Pchar, false);
			LAi_SetActorTypeNoGroup(Pchar);
			LAi_ActorTurnToCharacter(Pchar, NPChar);
			dialog.text = "Greetings, hero! Our search for the 'Necromancer's Amulet' is nearing completion.";
			link.l = "What's going on here?! What amulet? What are you?";
			link.l.go = "Alt_start2_2";
		break;

		case "Alt_start2_2":
			dialog.text = "Wait a minute... Check... Oh, shit! I was wrong. Have a nice game, sorry for the problems! Goodbye!";
			link.l = "Stop! What does it mean? But what about the training? PIRATES distribution?";
			link.l.go = "Alt_start2_3";
		break;

		case "Alt_start2_3":
			dialog.text = "All right, all right. Who are you in life?";
			link.l = "(creating your own type of hero)";
			link.l.go = "ChangePIRATES_Alt2";
		break;

		case "ChangePIRATES_Alt2":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Alt_start2_4";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;

		case "Alt_start2_4":
			dialog.text = "Did you decide? That's it, go to the port, come to your senses. Have a nice day!";
			link.l = "I don't understand anything. Well, okay...";
			link.l.go = "Finish_2";
		break;
	}
}
