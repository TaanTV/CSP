void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Exit_Fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");

			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("You'd better go your own way, "+ GetSexPhrase("buddy", "girlfriend") +". She'll thank us later.",
											 "Get out of here! Don't stop the gentlemen from having fun.",
											 "Don't get involved in my own business, "+ GetSexPhrase("stranger", "girl") +". Big deal, we'll have a little fun!");
				link.l1 = LinkRandPhrase("I won't let this happen!", "Quit your bad business!", "I will not allow violence!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("Understood, I'm leaving. Sorry for interrupting you.", "I dare not disturb you. Sorry to bothering you.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("You'd better go your own way, "+ GetSexPhrase("buddy", "girlfriend") +". She'll thank us later.",
											 "Get out of here! Don't stop the gentlemen from having fun.",
											 "Don't get involved in my own business, "+ GetSexPhrase("stranger", "girl") +". Big deal, we'll have a little fun!");
					link.l1 = LinkRandPhrase("I won't let this happen!", "Quit your bad business!", "I will not allow violence!");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("Understood, I'm leaving. Sorry for interrupting you.", "I dare not disturb you. Sorry to bothering you.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hey, "+ GetSexPhrase("stranger", "girl") +" Why do you need trouble? This is a well-known person in the settlement. We've already paid her off. But she saw you and decided to sneak away.",
												   "Hey, "+ GetSexPhrase("buddy", "girlfriend") +", go your own way and do not interfere where you are not asked. We won this girl at dice, but she turned out to be too frisky. We've been running after her for an hour.");
					link.l1 = "I don't know anything, I won't hurt the girl!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("That's the thing! And I almost believed! Well, the beauty gives...", "Ah, well, that's another matter. Well, have fun if you want to.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{
					dialog.text = "Go, "+ GetSexPhrase("nice person", "girl") +", my dear. We'll figure it out without you.";
					link.l1 = "I will not allow violence!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hey, "+ GetSexPhrase("stranger", "girl") +", why do you need trouble? This is a well-known person in the settlement. We've already paid her off. But she saw you and decided to sneak away.",
												   "Hey, "+ GetSexPhrase("buddy", "girlfriend") +", go your own way and do not interfere where you are not asked. We won this girl at dice, but she turned out to be too frisky. We've been running after her for an hour.");
					link.l1 = "I don't know anything, I won't hurt the girl!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("That's the thing! And I almost believed! Well, the beauty gives...", "Ah, well, that's another matter. Well, have fun if you want to.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}
		break;

		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Oh, you went out for a walk at the wrong time...", "Did you decide to be a hero?") +"Kill "+ GetSexPhrase("him", "her") +" guys!", "Oh you"+ GetSexPhrase("slug", "trash") +"! Who are you getting in the way of?! Cut "+ GetSexPhrase("him", "her") +"!");
			link.l1 = "And you haven't seen such menacing ones.";
			link.l1.go = "Exit_Fight";
			ChangeCharacterReputation(pchar, 5);
		break;

		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "Yes, it cost us a tidy sum! If you're so noble, then you can take it for " + sti(pchar.GenQuest.EncGirl.price) + " piastres."+ GetSexPhrase("Roll around a lot, hehe..", "") +"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("Here's your money, I'm taking her.", "Don't show your teeth. I'm taking the girl, here's the money.");
				link.l1.go = "Node_4";
			}
			link.l2 = LinkRandPhrase("Did you want piasters?! Don't you want steel under the rib?!",
									 "You're having fun, but the girl is barely standing on her feet from fear!",
									 "Who are you trying to fool?! a forest scarecrow!");
			link.l2.go = "Node_Fight";
		break;

		case "Node_4": // бандюки уходят, девица остаётся - ГГ её выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price)));
			ChangeCharacterReputation(pchar, 7);
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;

		case "Node_5":
			dialog.text = "Why do you believe her?! What kind of violence? She ran away from home, we've been chasing all day - the owner sent her.";
			link.l1 = RandPhraseSimple("Is that so? Well, that makes a difference. Catch up with your fugitive.", "Ah, well, chase, chase. And I have business here...");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("You will tell these tales to your grandchildren if you live to see it!", "Who have you decided to deceive?!");
			link.l2.go = "Node_6";
			link.l3 = "I'll take her home so that nothing superfluous happens. Who are her parents?";
			link.l3.go = "Node_7";
		break;

		case "Node_6":
			dialog.text = "Well, you got on the knife yourself. So, forgive me...";
			link.l1 = "Who would speak.";
			link.l1.go = "Exit_Fight";
		break;

		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = drand(2);
			else	i = drand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "the storekeeper";
					pchar.GenQuest.EncGirl.FatherGen = "the owner of the store";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "he serves in the port authority";
					pchar.GenQuest.EncGirl.FatherGen = "an employee in the port authority";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "he serves as the commandant of the fort";
					pchar.GenQuest.EncGirl.FatherGen = "the commandant of the fort";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "the owner of the shipyard";
					pchar.GenQuest.EncGirl.FatherGen = "the owner of the shipyard";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;
			}
			dialog.text = "Her father - " + pchar.GenQuest.EncGirl.FatherNom + " is in the settlement " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ". Just don't let us down, otherwise his temper is painfully cool - he'll lose three skins...";
			link.l1 = "Don't worry. I will deliver it in the best possible way.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;

		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterReputation(pchar, 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;

		case "Node_8":
			dialog.text = "Here we meet again. And where is your traveling companion? However, she's no longer needed, since you're here.";
			link.l1 = "Gentlemen, it seems to me that the amount you received is enough to leave the girl alone.";
			link.l1.go = "Node_9";
		break;

		case "Node_9":
			if(drand(1) == 0)
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;
			}
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;
			}
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(drand(4))
			{
				case 0:
					sTemp = "leg";
				break;
				case 1:
					sTemp = "hand";
				break;
				case 2:
					sTemp = "ear";
				break;
				case 3:
					sTemp = "nose";
				break;
				case 4:
					sTemp = "eye";
				break;
			}
			dialog.text = "What your sum is, compared to the treasures " + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_GEN) + "? " +
							"He was so stingy that he didn't marry his own daughter off because he didn't want to spend money on the wedding...\nBut there is also our share in his chests! "+
							GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM) +" lost his " + sTemp +" during boarding! And what for?" +
							"A pitiful handful of piastres?! " + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_NOM) + " dragged all loot to his hiding place. But now we are not going to retreat! Show me where his chests are ";
			link.l1 = "Hmm, even though I didn't hire to guard your captain's treasures, but I can't show you the place... Because I don't know it.";
			link.l1.go = "Node_10";
		break;

		case "Node_10":
			dialog.text = "You're lying!!! I can already smell the piastres coming out of this cave! Show me the place if you don't want to die!";
			link.l1 = "I see you are not convinced by my words. Maybe the blade will convince you?";
			link.l1.go = "Node_11";
		break;

		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "You "+ GetSexPhrase("dog", "trash") +"! Get out of the way!...";
			link.l1 = "Argh...";
			link.l1.go = "exit_fight";
		break;

		case "EncGirl_Berglar":
			dialog.text = "Hello, dear. There are complaints about you.";
			link.l1 = "Who are the complaints from? From this slut?";
			link.l1.go = "EncGirl_Berglar1";
		break;

		case "EncGirl_Berglar1":
			dialog.text = "Take it easy with your expressions! I won't let you hurt my little sister! First you hit on her in the jungle, then "+ GetSexPhrase("brought here to offer obscenities", "dragged here and robbed") +".";
			link.l1 = "Listen, buddy, do I have to listen to all this?";
			link.l1.go = "EncGirl_Berglar2";
		break;

		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "No. A modest amount in " + sti(pchar.GenQuest.EncGirl.BerglarSum) + " piastres can save you any trouble.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "Hmm, but noble deeds don't come cheap nowadays. Take it...";
					link.l1.go = "EncGirl_Berglar3";
				}
				link.l2 = "It will be cheaper to make a hole in your belly so that you don't block my way to the exit.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "No. But you'll have to turn out your pockets, or I'll stab you!";
				link.l1 = "Take it, you brat! But you won't get away with it that easily...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "It will be easier to make a hole in your belly so that you don't block my way to the exit.";
				link.l2.go = "EncGirl_Berglar4";
			}
		break;

		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "That's nice. Good riddance.";
			link.l1 = "Have a nice stay.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");
		break;

		case "EncGirl_Berglar3_1":
			dialog.text = "Of course it won't do, who's arguing? Well, goodbye, "+ GetSexPhrase("buddy", "girlfriend") +"."+ GetSexPhrase(" And remember - you're not so handsome that girls would throw themselves at you on the spot. You'll be smarter from now on!", "") +"";
			link.l1 = ""+ GetSexPhrase("That's for sure!..", "Come on, get lost!") +"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");
		break;

		case "EncGirl_Berglar4":
			dialog.text = "In appearance of "+ GetSexPhrase("such a noble man", "such a well-mannered girl") +", you're so uncivilized.";
			link.l1 = "As I can...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;

		case "Node_2":
			dialog.text = "Well, then blame yourself! Tickle "+ GetSexPhrase("his", "her") +" ribs with seteel, guys!";
			Link.l1 = "Pray before you die!";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "Did you want to join? "+ GetSexPhrase("Go to hell - it's not enough for us", "Get out of here, one girl is enough for us") +"!";
			Link.l1 = "If that's the case, I won't bother you.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "I will not let violence happen in front of my eyes!";
			Link.l2.go = "Node_2";
		break;

	}
}
