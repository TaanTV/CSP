
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Who do I have the honor to talk to?";
			link.l1 = "Uh... My name is " + GetFullName(pchar) + " , I'm the captain of '" + PChar.Ship.Name + "'.";
			link.l1.go = "talk_1";
			if (bBettaTestMode && !CheckAttribute(pchar,"ScamFanActive"))
			{
				link.l2 = "Summon the Kraken";
				link.l2.go = "Kraken";
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			dialog.text = "To what do I owe the pleasure, Captain " + GetFullName(pchar) + " ?";
			link.l1 = "I would like to know about the upcoming matches.";
			link.l1.go = "ArenaBattle_1";
			link.l2 = "I would like to practice.";
			link.l2.go = "academy";
			if (CheckAttribute(pchar,"ScamFanActive") && !CheckAttribute(pchar,"KnowScam"))
			{
				link.l3 = "Do you happen to know anything about this champion's ";
				link.l3.go = "legend";
			}
			link.l99 = "I just wanted to see you, " + GetFullName(NPChar) + ". See you later.";
			link.l99.go = "exit";
			if (bBettaTestMode && !CheckAttribute(pchar,"ScamFanActive"))
			{
				link.l4 = "Summon the Kraken";
				link.l4.go = "Kraken";
			}
			NextDiag.TempNode = "meeting";
		break;

		/////////////////////////////////////////////////////////////////////////////////////////
		/////////// Бои на арене - возможность сделать ставки или самому участвовать ////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		case "ArenaBattle_1":
			if(GetCharacterItem(PChar, "ArenaBilet") > 0)
			{
				dialog.text = "Captain, you were going to go and watch the competition.";
				link.l1 = "Oh, yes, it's true.";
				link.l1.go = "exit";
				break;
			}

			if(CheckAttribute(PChar, "Arena"))
			{
				if(PChar.AcademyLand.Begin == true)
				{
					dialog.text = "Hmm... In my opinion, you haven't completed the training that we recently agreed on.";
					link.l1 = "Uh, yeah? In that case, let me take my leave.";
					link.l1.go = "exit";
				}
				else
				{
					if(PChar.Arena == "Generate")
					{
						dialog.text = "If you are interested, the next fights will take place in the near future.";
						link.l1 = "Yes, I am interested in this. I want to know more about it.";
						link.l1.go = "ArenaBattle_2";
						link.l2 = "Hmm.. Thanks for the information, but I'm probably not up to it right now...";
						link.l2.go = "exit";
					}
					else
					{
						if(PChar.Arena == "Prepare")
						{
							dialog.text = "Hmm... In my opinion, Captain, you should already be at the event site - after all, you have already chosen the competition!";
							link.l1 = "Yes? Uh-uh.. I'm already running!";
							link.l1.go = "exit";
						}
						else
						{
							dialog.text = "Unfortunately, captain " + GetFullName(pchar) + ", no fights are expected yet.";
							link.l1 = "Sorry. Then, see you later!";
							link.l1.go = "exit";
						}
					}
				}
			}
			else
			{
				dialog.text = "Unfortunately, captain " + GetFullName(pchar) + ", no fights are expected yet.";
				link.l1 = "Sorry. Then, see you later!";
				link.l1.go = "exit";
			}

		break;

		case "ArenaBattle_2":
			dialog.text = "Would you like to take part in a duel or try to earn some money?";
			link.l1 = "I'd love to take part or a deal.";
			link.l1.go = "ArenaBattle_3";
			link.l3 = "If it's possible, I'd like to just watch it.";
			link.l3.go = "ArenaBattle_5";
		break;

		case "ArenaBattle_3":
			NextDiag.CurrentNode = "Meeting";
			DialogExit();
			LaunchArena(false);
		break;

		case "ArenaBattle_5":
			int iMoney = sti(PChar.Arena.ViewCost);
			dialog.text = "Hmm... Perhaps I can give you that opportunity. For " + iMoney + " gold, of course.";

			if(sti(PChar.money) >= iMoney)
			{
				link.l1 = "I agree. Here they are, your " + iMoney + " piastres.";
				link.l1.go = "ArenaBattle_6";
			}
			else
			{
				link.l1 = "Oh.. Perhaps I can't afford such entertainment. I'll come back another time.";
				link.l1.go = "exit";
			}

			link.l2 = "Here's another thing, pay for some pathetic sight!";
			link.l2.go = "exit";
		break;

		case "ArenaBattle_6":
			AddMoneyToCharacter(PChar, -sti(PChar.Arena.ViewCost));
			GiveItem2Character(PChar, "ArenaBilet");
			dialog.text = "That's nice. Take this piece of paper and show it at the entrance... ... (smiles)...";
			link.l1 = "Heh. Thank you.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PrepareArenaOdds");
			PChar.Arena.Mode.NotOdd = true;
		break;

		/////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////// ТРЕНИРОВКИ ////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		case "academy":
			if(GetCharacterItem(PChar, "ArenaBilet") > 0)
			{
				dialog.text = "Captain, you were going to go and watch the competition.";
				link.l1 = "Oh, yes, it's true.";
				link.l1.go = "exit";
				break;
			}

			if(PChar.AcademyLand.Can == false)
			{
				if(PChar.AcademyLand.Begin == true)
				{
					dialog.text = "Hmm... In my opinion, you haven't completed the previous training yet...";
					link.l1 = "Uh, yeah? In that case, let me take my leave.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Hmm... I can't provide you with the people for that at the moment. Come back later.";
					link.l1 = "Well, it's a pity.";
					link.l1.go = "exit";
				}
			}
			else
			{
				if(PChar.Arena != "Prepare")
				{
					dialog.text = "Hmm... Which way do you want to try out?";
					link.l1 = "Let's see.";
					link.l1.go = "academy_land";
				}
				else
				{
					dialog.text = "Hmm... In my opinion, Captain, you have already chosen the competition! You shouldn't be up to training.";
					link.l1 = "Yes? Uh-uh.. I'm already running!";
					link.l1.go = "exit";
				}
			}
		break;

		case "academy_land":
			NextDiag.CurrentNode = "Meeting";
			DialogExit();
			LaunchAcademyLand();
		break;

		case "academy_sea":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		/////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////// ПЕРВАЯ ВСТРЕЧА ////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		case "talk_1":
			dialog.text = "Glad to meet you, Captain. My name is " + GetFullName(NPChar) + ". Hmm.. To be honest, I haven't heard of you. How did you get here, Captain?";
			link.l1 = "Well, how to say it. I tend to explore previously unseen territories. That is why I found your settlement is here. But, what kind of settlement is this?";
			link.l1.go = "talk_2";
		break;

		case "talk_2":
			dialog.text = "Oh, it's a very long story that I don't want to remember.. But it's probably worth telling... Although you may have heard her.";
			link.l1 = "Hmm... I don't remember anything.";
			link.l1.go = "talk_3";
		break;

		case "talk_3":
			dialog.text = "A few years ago, a great navigator decided to build a colony on this island. The transportation of the necessary goods lasted for months, and the colony was being built. When the construction of the fort was completed, it was decided to proceed with the construction of the colony itself... But suddenly the colonial powers found out about the new building and decided to intervene in the course of construction. Almost everyone was killed, and the fort and the beginnings of a new colony were destroyed... There was this small camp where workers and slaves lived. Everyone who now lives in this settlement was also destined for death, but we were saved by a lucky chance - at that moment we went deep into the jungle in search of firewood, and when we returned we saw this destruction... All those who now live in this settlement are builders, and the team of that captain.";
			link.l1 = "Yes... It's a sad story. But what are you doing here?";
			link.l1.go = "talk_4";
		break;

		case "talk_4":
			dialog.text = "It took a long time for us to recover from such a disaster, especially when we were left alone on a desert island. I had to eat plants and insects. But over time, we managed to build this settlement, and later, getting a little stronger, we began to conduct endless training, and those builders and slaves who almost starved to death and barely held a sword in their hands, thanks to incredible endurance and desire, were able to learn the art of fencing well. Soon our town was noticed by unknown ships passing by, and rumors about our settlement began to spread throughout the Caribbean. Time has passed, and now we can say that if it hadn't been for the misfortune that happened to us, perhaps none of this would have happened, and those slaves continued to rot, working for fat merchants in unbearable conditions, and we would have divided pennies among ourselves, worshiping our captain... Now various tournaments are held here from time to time - from duels to full-fledged tournaments, as well as the opportunity to place bets. You can only participate by paying, but if you win, all the money will be yours! And of course, we can provide you with people for different types of training. For a small fee, of course.";
			link.l1 = "Very interesting! I think I'd like to "+ GetSexPhrase("g","gla") +"use your services.";
			link.l1.go = "meeting";
			NextDiag.TempNode = "meeting";
		break;
		// говорим при первой встрече <--

		// На арене -->
		case "FightInArena_1":
			dialog.text = "Greetings, captain " + GetFullName(pchar) + ". You have to fight with a worthy opponent. The duel takes place in several rounds: up to three victories of one of the participants. Good luck!";
			link.l1 = "Thank you for the information, " + NPChar.lastname + ".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaDuelTalkWithEnemy");
		break;

		case "FightInArena_2":
			switch(sti(PChar.Arena.Duel.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("You've lost, Captain " + GetFullName(PChar) + "! Perhaps next time you will be stronger!", "It's a pity that you failed, captain " + pchar.name + ".", "Eh, you just barely missed the victory! Well, maybe you'll have better luck next time.");
					link.l1 = LinkRandPhrase("Eh.. No luck.", "But you saw how I charged him?!", "Yyour arena - is nonsense!");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaDuelTheEnd");
				break;

				case 1:
					dialog.text = LinkRandPhrase("You got him, Cap! I was rooting for you. You have honestly earned your winnings. Here, now these " + sti(PChar.Arena.Duel.Prize) + " gold rightfully belong to you.", "How did you beat him, Captain! And how did you make the first transition! I admired your actions. You deserve your " + sti(PChar.Arena.Duel.Prize) + "gold.", "You have proved to everyone again who is in charge here. Congratulations, here are your " + sti(PChar.Arena.Duel.Prize) + " gold as a prize.");
					link.l1 = LinkRandPhrase("Thank you! See you soon.", "Thank you, dear. I will definitely come next time.", "Hehe!");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Duel.Prize));
					AddDialogExitQuestFunction("ArenaDuelTheEnd");
				break;
			}
		break;

		case "FightInArena_3":
			dialog.text = LinkRandPhrase("Ha ha ha! Welcome to hell, Captain " + GetFullName(pchar) + "! You will have to seriously try to come out of this fight with the hermits of nature as a winner.", "Well, goto"+ GetSexPhrase("in","va") +"to fight the devil's spawn?", "Ah, here you are, Captain. Hehe, well, the audience is waiting.");
			link.l1 = LinkRandPhrase("And you've seen better ones.", "I'll pound them into noodles!", "Get the money ready, buddy.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StartArenaEtapsBattle");
		break;

		case "FightInArena_4":
			switch(sti(PChar.Arena.Etaps.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("These creatures almost tore you to pieces! Maybe next time you will be stronger.", "Yes, yes, they almost devoured you! Ha-ha-ha!", "Cool you loaded these creatures! But I didn't have enough strength for everything. Come again.");
					link.l1 = LinkRandPhrase("Yes, you just have stupid sabers! Yes, the roof is uneven...", "Where did you find these monsters?! Well, never mind, I'll be back! Tell them so...", "I was just unlucky!");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaEtapsTheEnd");
				break;

				case 1:
					dialog.text = LinkRandPhrase("How do you like them! I wish there were more such fighters! You have honestly earned your winnings. Here, now these " + sti(PChar.Arena.Etaps.Prize) + " piastres rightfully belong to you. Come again.", "Yeah, I didn't expect you to be so quick. Yes, you are good - not every brave man will go out to fight with these creatures. Here is your winnings - " + sti(PChar.Arena.Etaps.Prize) + "gold.", "They almost crumbled from your blade! What a battle it was! Here is your winnings - " + sti(PChar.Arena.Etaps.Prize) + "gold.");
					link.l1 = LinkRandPhrase("Heh. No one can beat me!", "Order a batch of these creatures for me. I will definitely come again!", "Did you see how I cut off that crab's claw?!");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Etaps.Prize));
					AddDialogExitQuestFunction("ArenaEtapsTheEnd");
				break;
			}
		break;

		case "FightInArena_5":
			dialog.text = LinkRandPhrase("Here you are, captain " + GetFullName(pchar) + "! Well, you're just in time - all the participants are gathered and there are no obstacles to starting our tournament already.", "Greetings, captain " + GetFullName(PChar) + ". You are going to have very difficult fights - I promise you that. Well, if you pass the first round, of course. Haha!", "I hope you give heat to these conceits, captain " + pchar.name + ".");
            PlayVoice("Kopcapkz\Voices\Arena\ArenaHead_"+rand(7)+".wav");
			link.l1 = LinkRandPhrase("Tell these participants that they have no chance in a fight with me!", "Let's get started - I can't wait to beat someone up!", "The prize will be mine - don't even doubt it.");
			AddDialogExitQuestFunction("ArenaTournamentTalkWithRandEnemy");
			bDisableCharacterMenu = true;
			string sQuest = "AT_LooserDetector_1_4";
			PChar.quest.(sQuest).win_condition.l1 = "locator";
			PChar.quest.(sQuest).win_condition.l1.location = "FencingTown_Arena";
			PChar.quest.(sQuest).win_condition.l1.locator_group = "item";
			PChar.quest.(sQuest).win_condition.l1.locator = "looser_detector";
			PChar.quest.(sQuest).function = "ArenaTournamentLooserDetector";
		break;


		case "FightInArena_7":
			bDisableCharacterMenu = false;
			switch(sti(PChar.Arena.Tournament.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("Yes, the tournament was a success! You fought well, Captain! But luck was not on your side. We will wait for you again - maybe next time you will be the winner.", "I was hoping for you, cap, but you were almost smeared on the floor! Ugh.", "Eh, that's not lucky. You probably just didn't get enough sleep.");
					link.l1 = LinkRandPhrase("I'm just a little, ahem, sick... Goodbye.", "The opponent used forbidden techniques - I will complain.", "Well, never mind, I'll be back.");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaTournamentTheEnd");
				break;

				case 1:
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Tournament.Money));

					pchar.questTemp.tournamentcount = sti(pchar.questTemp.tournamentcount) + 1;
					if(sti(pchar.questTemp.tournamentcount) >= 1) UnlockAchievement("AchTurnir", 1);
					if(sti(pchar.questTemp.tournamentcount) >= 3) UnlockAchievement("AchTurnir", 2);
					if(sti(pchar.questTemp.tournamentcount) >= 7) UnlockAchievement("AchTurnir", 3);

					/*if (rand(3) == 0 && !CheckAttribute(pchar,"ScamFanActive"))
					{
						pchar.quest.SpawnScamFan.win_condition.l1 = "Location";
						pchar.quest.SpawnScamFan.win_condition.l1.location = "FencingTown_ExitTown";
						pchar.quest.SpawnScamFan.win_condition = "SpawnScamFan";
						pchar.ScamFanActive = true;
					}*/

					bool nopirate = false;
					if (!CheckAttribute(pchar,"questTemp.UniquePirate.Drake") || !CheckAttribute(pchar,"questTemp.UniquePirate.Barbarigo") || !CheckAttribute(pchar,"questTemp.UniquePirate.BlackBeard") || !CheckAttribute(pchar,"questTemp.UniquePirate.Levasser")) nopirate = true;
					if (sti(pchar.questTemp.tournamentcount) == 3 && nopirate)
					{
						aref item;
						Items_FindItem("map_full", &item);
						string type = GetUniquePirateName();
						FillMapForUniqueTreasure(item, type);
						type = GetUniquePirateNameString(type);
						GiveItem2Character(pchar, "map_full");
						dialog.text = LinkRandPhrase("Yes, the tournament was a success. And you became its winner! To be honest, I couldn't take my eyes off how you handle weapons! Now these " + sti(PChar.Arena.Tournament.Money) + " gold rightfully belongs to you.", "Captain, you are the champion! Even the fiercest rivals did not expect such skill with weapons! Take your prize - these " + sti(PChar.Arena.Tournament.Money) + "gold.", "Yes, you almost tore them all to shreds! What a grip! These " + sti(PChar.Arena.Tournament.Money) + " gold is rightfully yours.");
						dialog.text = dialog.text + "  Since you have already become a three-time winner of the tournament, we decided to prepare something special... According to rumors, this treasure map is the famous "+type+". I think you will be able to find what this villain has hidden.";
						link.l1 = "This is a truly royal gift from your side! Thank you very much"+GetSexPhrase("en!","on!");
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = LinkRandPhrase("Yes, the tournament was a success. And you became its winner! To be honest, I couldn't take my eyes off how you handle weapons! Now these " + sti(PChar.Arena.Tournament.Money) + " gold rightfully belongs to you.", "Captain, you are the champion! Even the fiercest rivals did not expect such skill with weapons! Take your prize - these " + sti(PChar.Arena.Tournament.Money) + "gold.", "Yes, you almost tore them all to shreds! What a grip! These " + sti(PChar.Arena.Tournament.Money) + " gold is rightfully yours.");
						int randreward = drand2(100);
						string reward;
						if (randreward < 6)
						{
							int quality = 1;
							if (pchar.rank <= 6) quality = 1;
							if (pchar.rank >= 12) quality = 2;
							if (pchar.rank >= 18) quality = 3;
							if (pchar.rank > 24) quality = 4;
							reward = "book"+quality+"_"+sti(drand(13)+1);
						}
						if (randreward >5 && randreward < 17)
						{
							switch (drand(12))
							{
								case 0: reward = "blade19"; break;
								case 1: reward = "blade22"; break;
								case 2: reward = "blade36"; break;
								case 3: reward = "blade05"; break;
								case 4: reward = "blade31"; break;
								case 5: reward = "blade34"; break;
								case 6: reward = "blade40"; break;
								case 7: reward = "blade46"; break;
								case 8: reward = "blade15"; break;
								case 9: reward = "blade21"; break;
								case 10: reward = "blade01"; break;
								case 11: reward = "blade010"; break;
								case 12: reward = "topor2"; break;
							}
						}
						if (randreward >16 && randreward < 28)
						{
							switch (drand(8))
							{
								case 0: reward = "pistol6"; break;
								case 1: reward = "pistol_grapebok"; break;
								case 2: reward = "pistol11"; break;
								case 3: reward = "mushket"; break;
								case 4: reward = "mushket_Arguebuze"; break;
								case 5: reward = "mushket_Temppo"; break;
								case 6: reward = "mushket_mushketon1"; break;
								case 7: reward = "mushket_mushket_SHZ"; break;
								case 8: reward = "mushket_flint_mushketon"; break;
							}
						}
						if (randreward >17 && randreward < 39)
						{
							switch (drand(2))
							{
								case 0: reward = "cirass2"; break;
								case 1: reward = "cirass3"; break;
								case 2: reward = "cirass4"; break;
							}
						}
						if (randreward >38 && randreward < 50)
						{
							switch (drand(7))
							{
								case 0: reward = "indian1"; break;
								case 1: reward = "indian10"; break;
								case 2: reward = "indian15"; break;
								case 3: reward = "indian18"; break;
								case 4: reward = "indian19"; break;
								case 5: reward = "indian20"; break;
								case 6: reward = "indian21"; break;
								case 7: reward = "indian22"; break;
							}
						}
						if (randreward > 49)
						{
							GiveItem2Character(pchar,"Chest");
							reward = "icollection";
						}
						GiveItem2Character(pchar,reward);

						int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
						aref item1;
						Items_FindItem(reward, &item1);
						string sTemp = LanguageConvertString(idLngFile, item1.name); 
						if (HasSubStr(reward, "book")) sTemp = sTemp + " book";
						dialog.text = dialog.text + " In addition to the cash prize, we also decided to give you a special gift for winning. This is a " + sTemp + ".";
						LanguageCloseFile(idLngFile);
						link.l1 = LinkRandPhrase("Did you really doubt me!", "I will show you more than once who is in charge here. And now - to rest.", "Ha ha ha, pathetic insects! I crack such rivals like nuts on boarding. By the way, nuts are good for your health.");
						link.l1.go = "exit";
					}
					AddDialogExitQuestFunction("ArenaTournamentTheEnd");
				break;
			}
		break;

		case "FightInArena_8":
			dialog.text = LinkRandPhrase("Ah, here you are, captain " + GetFullName(pchar) + ". Glad to see you here. I hope you're lucky today.", "Ah, here you are, captain " + pchar.name + ". Your bet must definitely play!", "Ah, here you are, captain " + pchar.name + ". I think that luck will turn to you today, and not like last time...") + "Take your place - go to-o-o-n there...(pointing to the left)... and climb the tower.";
			link.l1 = LinkRandPhrase("This is not luck - it's a cold calculation. You'll see, I'll win.", "Luck has never left me yet.", "Get my money ready.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StartArenaOddsContinue");
		break;

		case "FightInArena_9":
			switch(sti(PChar.Arena.Odds.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("Yeah, the fights were great! But, unfortunately, your bet didn't play out.. We will be waiting for you again - maybe next time you will be more successful in betting.", "You were unlucky today, Captain. But the game continues! Uh..", "That fighter was close to bringing you a lot of money. But it failed.");
					link.l1 = LinkRandPhrase("I don't play like that!! Give me the money!", "Oh, I didn't get lucky. But you saw how he hit him before he fell...", "Well, never mind, I'll take my own, be sure!");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaOddsTheEnd");
				break;

				case 1:
					dialog.text = LinkRandPhrase("Yeah, the fights were great! In addition, your bet has been played and now these " + sti(PChar.Arena.Odds.Prize) + " piastres rightfully belong to you. Honestly, I had a different opinion about the outcome of the fights, but it seems that I still know too little about the balance of power...", "Wow! No one predicted such a course of events, but you were able to correctly name the winner! Bravo, bravo! Here are your " + sti(PChar.Arena.Odds.Prize) + " gold as a prize.", "Well, you are a captain and an expert! So figure out the balance of forces of the duelists! Oh, my God! No one predicted such a course of events, but you were able to correctly name the winner! Bravo, bravo! Here are your " + sti(PChar.Arena.Odds.Prize) + "gold!");
					link.l1 = LinkRandPhrase("Hehe, learn while I live"+ GetSexPhrase("in","va") +".", "Well, you can't drink your skill. I advise you to listen to others sometimes.", "Thank you. I will definitely come back here.");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Odds.Prize));
					AddDialogExitQuestFunction("ArenaOddsTheEnd");
				break;
			}
		break;

		case "FightInArena_10":

			dialog.text = LinkRandPhrase("Here you are, " + GetFullName(pchar) + "! Welcome to our fights. I hope you enjoy our event.", "Greetings, Cap. Today we are planning very serious fights.", "I am sure you will like our event.") + "Take your place - go to-o-o-n there...(pointing to the left)... and climb the tower.";
			link.l1 = LinkRandPhrase("I am also ra"+ GetSexPhrase("d","yes") +" to be here. I will be happy to take my place.", "I hope they hold serious fights here, and not divide the sandbox.", "Come on, start your event already.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StartArenaOddsContinue");
		break;

		case "FightInArena_11":
			dialog.text = LinkRandPhrase("Yes, the fights were clearly a success! I did not have time to admire the ability of these people to handle weapons. We will be glad to see you again. In the meantime, until new fights!", "Yes, the guys clearly did not make a mistake - what a passion, what a skill!", "You should have participated in our events yourself.");
			link.l1 = LinkRandPhrase("I liked the fights as much as you did. Thank you, and goodbye.", "Yes, the fights came out well. I will be happy to come here again.", "Archg! Next time ca"+ GetSexPhrase("m","ma") +"I will participate in these events - then they will see what a real duel is.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaOddsTheEnd");
		break;

		case "EnemyFightInArena_1":
			dialog.text = LinkRandPhrase("Well, goth"+ GetSexPhrase("s","ova") +" give your money to me? I can't wait for your defeat.", "Yes, I'll tear you to shreds, insect!", "Get ready to leave with nothing, you jerk!");
			link.l1 = LinkRandPhrase("Heh. Don't give up, my friend. Let's get down to business.", "Shut your mouth, rotten coconut. Now I'm going to let you go to the rags.", "Haha, now let's see who of us leaves with nothing.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaDuelStartBattleWithEnemy");
		break;

		case "FightInArena_6":
			dialog.text = RandSwear() + LinkRandPhrase("In a fight with me, you will only fail!",+ GetFullName(pchar) + "?! I'll tear you to pieces if you stand in my way!", "Hey, you! Now you will regret that you went here!");
			link.l1 = LinkRandPhrase("Now you're leaving here with nothing!", "Haha, will the pathetic bastard argue with me?", "Now I like you...");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaTournamentGo");
		break;
		// На арене <--

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("An alarm has been raised in the city. It looks like it's time for me to take up arms...", "Isn't the whole city guard running after you? Come to me, soldiers!!!", "You will not find shelter with me. But you'll find a few inches of cold steel under the rib!"),
					LinkRandPhrase("What do you want, you scoundrel?! The city guards have already are on your trail, you can't get far, you dirty pirate!", "Dirty killer! Guards!!!", "I'm not afraid of you, you bastard! You'll be hanged in our fort soon, you won't get far..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("You seem tired of living...", "Heh, and there are no peaceful citizens " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"),
					RandPhraseSimple("Go to hell!", "Heh, you have a few seconds left to live..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "I warned you. And then you see for yourself whether to run into it or not...";
					link.l1 = "Heh!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "What do you want in my house, you scoundrel?! I'll give you ten seconds to get out of here!";
					link.l1 = LinkRandPhrase("Heh, they know me here too!", "My glory goes ahead of me...", "Hmm, I see.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("I am glad to welcome you to my house. Are you on business with me?",
						"How can I help you?",
						"Hmm, what can I do for you?",
						"I'm sorry if you don't need me, I'll ask you not to bother me...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("No, just looking around the city, getting to know the residents...",
						"Oh, nothing special...",
						"Nothing...",
						"Okay, whatever you say.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("I'm sorry, you showed up at my house at the wrong time - it's night outside. I'm asking you to leave my house!",
						"I have already said that the time is late. Please leave.",
						"I don't want to be rude, but I insist that you leave my house immediately!",
						"What the hell is this?! Guards, thieves!!!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Okay, I understand...",
						"Yes, now...",
						"Okay, don't get all worked up.",
						"Shut up, what thieves?!", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "Oh, let me introduce myself - " + GetFullName(npchar) + ". We are glad to see you, the laws of hospitality for our city are not an empty phrase.";
			link.l1 = GetFullName(pchar) + ", with your permission...";
			link.l1.go = "exit_setOwner";
		break;

		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You're a thief, my dear! Guards, hold him!!!", "Wow! As soon as I looked at it, you went straight into the chest with your head! Stop the thief!!!", "Guards! They're robbing!!! Stop the thief!!!");
			link.l1 = "Ah, the devil!!!";
			link.l1.go = "fight";
			link.l2 = "If you make another sound, you're finished!..";
			link.l2.go = "FackYou_1";
			link.l3 = "I.. I.. I will return everything!..";
			link.l3.go = "FackYou_2";
		break;

		case "FackYou_1":
			dialog.text = "What? You're a brave man, I'll take a look... Get the hell out, you damn bastard!";
			link.l1 = "Damn!..";
			if(NPChar.sex == "man")
			{
				link.l1.go = "fight";
			}
			else
			{
				link.l1.go = "exit_setOwner3";
			}
		break;

		case "FackYou_2":
			dialog.text = "Of course you will... Hmm, pay " + sti(PChar.StealItemsMoney) +  " gold coins right now and you can get out on all fours. You can be sure everything will be fine.";
			if(sti(PChar.money)>= sti(PChar.StealItemsMoney))
			{
				link.l1 = "Okay.. Here's your money.";
				link.l1.go = "exit_setOwner2";
			}
			else
			{
				link.l2 = "But I don't have enough money... I'm sorry..";
				link.l2.go = "FackYou_3";
			}
			link.l3 = "Here's another one! I'll take whatever I want here!";

			if(NPChar.sex == "man")
			{
				link.l3.go = "fight";
			}
			else
			{
				link.l3.go = "exit_setOwner3";
			}
		break;

		case "FackYou_3":
			dialog.text = "What did you say, you damned thief?";
			link.l1 = "Damn!..";

			if(NPChar.sex == "man")
			{
				link.l1.go = "fight";
			}
			else
			{
				link.l1.go = "exit_setOwner3";
			}
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner2":
			AddMoneyToCharacter(PChar, -sti(PChar.StealItemsMoney));
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner3":
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "legend":
			dialog.text = "Oh, you're probably talking about Scam Games? Is it really that unlucky that he stuck to you?";
			link.l1 = "Who is he anyway?";
			link.l1.go = "legend_1";
		break;

		case "legend_1":
			dialog.text = "Rumor has it that he was once a damned fool who was a real fan of fencing championships. Once something happened to him and since then he has not eaten, drunk or received absolutely no harm from anything. Believe me, we've been trying to get rid of him for a very long time.";
			link.l1 = "He seems completely harmless... But if he constantly behaves like that, then I can understand you perfectly.";
			link.l1.go = "legend_2";
		break;

		case "legend_2":
			dialog.text = "Maybe you'll get lucky and find a way to get rid of it without leaving the archipelago. All his previous 'victims' sailed to Europe and were never heard from again.";
			link.l1 = "Do you have any thoughts on this?";
			link.l1.go = "legend_3";
		break;

		case "legend_3":
			dialog.text = "I don't even know what to say about this. Unless the gods could help. We have already tried all possible and impossible ways to get rid of it.";
			link.l1 = "Gods, then... Yes, it sounds completely hopeless, but thank you for that at least.";
			link.l1.go = "exit";
			pchar.quest.RidScamFan.win_condition.l1 = "Location";
			pchar.quest.RidScamFan.win_condition.l1.location = "Temple_skulls";
			pchar.quest.RidScamFan.win_condition = "RidScamFan";
			pchar.KnowScam = true;
		break;

		case "Kraken":
			dialog.text = "Kraken called.";
			link.l1 = "I'm going to meet you.";
			link.l1.go = "exit";
			pchar.quest.SpawnScamFan.win_condition.l1 = "Location";
			pchar.quest.SpawnScamFan.win_condition.l1.location = "FencingTown_ExitTown";
			pchar.quest.SpawnScamFan.win_condition = "SpawnScamFan";
			pchar.ScamFanActive = true;
			AddDialogExitQuestFunction("ArenaTournamentTheEnd");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
