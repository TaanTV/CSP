void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;
	string sTemp;
	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":

			//dialog.text = "Error";
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.quest.meeting = "1";

			if (npchar.id == "CrazyScientist")
			{
				dialog.text = "Well, wait!";
				link.l1.go = "CS";
			}
			if (npchar.id == "FinalBot")
			{
				dialog.text = "(You notice the bot too late, only after you hear the sound of a gunshot.)";
				LAi_LocationFightDisable(locLoad, false);
				DeleteAttribute(locLoad, "box1");
				DeleteAttribute(locLoad, "box2");
				DeleteAttribute(locLoad, "box3");
				DeleteAttribute(locLoad, "box4");
				DeleteAttribute(locLoad, "box5");
				DeleteAttribute(locLoad, "box6");
				DeleteAttribute(locLoad, "box7");
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorAnimation(npchar, "Shot", "pchar_back_to_player", 1.0);
				link.l1 = "Damn!";
				link.l1.go = "FB";
			}
			if (npchar.id == "wl_Pirate_Cap")
			{

				if (!CheckAttribute(npchar, "quest.meting"))
				{
				dialog.text = "What kind of cuttlefish is that on my deck?! Identify yourself!";
				link.l1 = "Where am I? How did I get here?";
				link.l1.go = "PC";
				npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "You have interesting things, I decided that for now I will keep them all to myself.  You are unlikely to object. Your pistol, however, is a very killer thing, besides it looks unusual. Where did you get it?";
					link.l1 = "None of your business. How long are you going to keep me here?";
					link.l1.go = "PC_2";
					npchar.quest.meting = 2;
				}
			}

			if (npchar.id == "AntonioDeSouza")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "Wow, what an interesting 'instance' " + GetFullName(characterFromId("wl_Pirate_Cap"))+" brought me. Tell me, demon, which circle of hell did you come from?";
					link.l1 = "I am not a demon.";
					link.l1.go = "ADS";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "Well, did you manage to remember something?";
					link.l1 = "You shouldn't have started this, Father. After all, I can take revenge when I get out.";
					link.l1.go = "ADS_2";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					dialog.text = "Don't expect me to feel sorry for you, so you better start talking. That pistol. Is this a British development? Answer me!";
					link.l1 = "Okay. I'll tell you everything.";
					link.l1.go = "ADS_1_truth";
					npchar.quest.meting = 3;
					break;
				}
				if (npchar.quest.meting == 3)
				{
					dialog.text = "Well?";
					link.l1 = "I have nothing more to tell you.";
					pchar.Whisper.DeSouzaHits = 3;
					link.l1.go = "ADS_1_2";
					npchar.quest.meting = 4;
					break;
				}
				if (npchar.quest.meting == 4)
				{
					dialog.text = "I really don't want to interrupt our lovely conversation, but I have a meeting with the governor scheduled for today. Don't go anywhere, and don't miss me here, hehe. We'll continue tomorrow.";
					link.l1 = "...";
					link.l1.go = "ADS_4_exit";
					if(rand(100) < 90)
					{
						pchar.Whisper.IncqGuard_bad = true;
					}
					npchar.quest.meting = 5;
					break;
				}
			}
			if (npchar.id == "NineFingers")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "Wow, a real beauty wandered into our village! By what fates?";
					chrDisableReloadToLocation = false;
					link.l1 = "Yes, I'm hiding from the Inquisition campfire.";
					link.l1.go = "NF";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "Do you see that? The village was attacked by a punitive detachment from Santiago. Didn't they come for your soul?";
					link.l1 = "Damn! You're right, the Spaniards are probably on my trail. What should we do now?";
					AddMoneyToCharacter(npchar, 777);
					npchar.SaveItemsForDead = true;
					link.l1.go = "NF_2_1";
					npchar.quest.meting = 2;
					break;
				}
			}
			if (npchar.id == "Wh_Jack")
			{
				dialog.text = "Where is our captain? What the hell are you doing with his hat and blade?";
				chrDisableReloadToLocation = true;
				link.l1 = "The village was raided by the Spaniards, your captain died in battle.";
				link.l1.go = "Jack";
				break;
			}
			if (npchar.id == "Wh_Jim")
			{
				dialog.text = "The devil! You killed Jack! Now you are rightfully our captain.";
				link.l1 = "Is it true? Just like that?";
				link.l1.go = "Jim";
				break;
			}
			if (npchar.id == "W_Lejitos")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					npchar.DontChangeBlade = true; // нельзя снять или залутать оружие

					dialog.text = "Fools. You should know that a cornered animal is dangerous. And I'm not just some kind of animal, I'm a Jaguar. I hope you managed to pray to your dead god, because now I'm going to send you to him!";
					link.l1.go = "exit_cave_entrance_fight";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "I could have done it myself, but anyway, thank you for your timely intervention. As I see, you have your own scores with the Spaniards?";
					link.l1 = "Yes, I managed to make a couple of enemies. And what did you say before the fight, about the dead god?";
					link.l1.go = "Lejitos";
					npchar.quest.meting = 2;
					break;
				}
			}
			if (npchar.id == "W_Chard")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "Who else are you? I don't think I ordered any bordello girls to my room.";
					link.l1 = "So you called me here just to make fun of me? One more joke like that and the 'bordello girl' will rip your belly open.";
					link.l1.go = "meet_chard";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					chrDisableReloadToLocation = false;
					if (CheckAttribute(pchar, "WhisperWonSword"))
					{
						dialog.text = "Congratulations on your victory. And you play well, much better than the local drunks. Take your sword. It's not a bad blade, I've never even had to sharpn it. And I managed to kill a lot of poor people with it, another one would have been blunted long ago...";
						link.l1 = "(Pick up the sword)";
						link.l1.go = "chard_get_sword";
					}
					else
					{
						dialog.text = "You're out of luck. But don't worry, this can happen to anyone, I see, this blade is very dear to you, I even regret that I won myself. Tell you what, if you help me with something, I'll give it to you. Anyway, I've already looked for a new one at the local store.";
						link.l1 = "What kind of help is needed?";
						link.l1.go = "chard_discuss_quest";
					}
					npchar.quest.meting = 2;
					break;
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "Chinaman_plead":
			npchar.ChinamanAskedSword = true;
			WhisperSelectRandomUsurer();
			LAi_SetOfficerType(NPChar);
			dialog.Text = "Captain, I would like to ask you a favor. Can you listen to me?";
			Link.l1 = "Of course I'll listen to you! You're a good officer, you've never let me down yet.";
			Link.l1.go = "Chinaman_plead_1";
		break;
		case "Chinaman_plead_1":
			dialog.Text = "Thank you for the flattering words, Captain. Then listen, before I was enslaved, I had a sword. I got it from my father, and he got it from his father, and so on for over a thousand years. Do you understand how important this sword is to me?";
			Link.l1 = "I see, it's a family heirloom.";
			Link.l1.go = "Chinaman_plead_2";
		break;
		case "Chinaman_plead_2":
			dialog.Text = "All this time, I've been thinking that the sword is lost forever. But when we entered the port, I heard two people talking. They're talking about a usurer-a collector of rare artifacts from different parts of the world. The conversation was just about the 'sword with five rings'. The last time it was true there were nine cozzets in my sword, but I'm still sure it was about mine. These barbarians must have ruined it. Please, Captain, help me get him back!";
			Link.l1 = "A usurer, you say? Where can I find him?";
			Link.l1.go = "Chinaman_plead_3";
		break;
		case "Chinaman_plead_3":
			sld = characterFromId(pchar.Whisper.UsurerId);
			//Lai_SetStayType(npchar);
			dialog.Text = XI_ConvertString("Colony" + sld.city) +". This is where call those people.";
			NextDiag.TempNode = "Hired";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			SetQuestHeader("WhisperChinamanRelic");
			AddQuestRecord("WhisperChinamanRelic", "1");
			AddQuestUserData("WhisperChinamanRelic", "sCity", XI_ConvertString("Colony" + sld.city+ "Gen"));
			Link.l1 = "Well, if we're in this city, I'll drop by the usurer.";
			Link.l1.go = "exit";
		break;
		case "Chinaman_plead_4":
			dialog.Text = "Thank you, Captain. I know that I already owe you a lot. But if you help, I swear I will be faithful to you until the very end.";
			Link.l1 = "Well, if we're in those places, I'll drop by the usurer.";
			Link.l1.go = "exit";
		break;

		case "chard_waiting_quest_result":
			dialog.Text = "Well, how are you doing on our case?";
			if (!CheckAttribute(npchar,"DiscussedEsteban"))
			{
				Link.l2 = "And what is your connection with Esteban? You're not even Spanish.";
				Link.l2.go = "chard_discuss_esteban"
			}
			if (!CheckAttribute(pchar,"Whisper.FoundPortmanJournal") && !CheckAttribute(pchar,"Whisper.ActiveChardQuest"))
			{
				Link.l1 = "I'm sorry, but I couldn't interrogate him. And pull out the documents too. Portman's ship went down...";
				Link.l1.go = "chard_failed"
				break;
			}
			if (CheckAttribute(pchar,"Whisper.FoundPortmanJournal"))
			{
				Link.l1 = "I found this magazine at Portman's. I think there's an answer to your question there.";
				Link.l1.go = "chard_check_journal"
				break;
			}
			if (CheckAttribute(pchar,"Whisper.BetrayChard"))
			{
				Link.l1 = "I didn't really like your idea. It's nothing personal, but I told Portman about her. He offered a reward for the return of his book.";
				Link.l1.go = "chard_betrayed"
				break;
			}
			Link.l1 = "Nothing so far.";
			Link.l1.go = "exit";

		break;
		case "chard_check_journal":
			Log_Info("You gave away the magazine");
			PlaySound("interface\important_item.wav");
			dialog.Text = "Let's see... Everything is encrypted here too. I'm going to need some time. A few hours. You can take a walk for now.";
			Link.l1 = "I'll wait here.";
			Link.l1.go = "chard_check_journal_1";
		break;
		case "chard_check_journal_1":
			dialog.Text = "Don't you trust me? Okay, you can lie down on the bed for now.";
			Link.l1 = "...";
			Link.l1.go = "chard_check_journal_2";
		break;
		case "chard_check_journal_2":
			chrDisableReloadToLocation = true;
			LAi_Fade("", "");
			WaitDate("",0,0,0,12,3);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			NextDiag.TempNode = "chard_check_journal_after";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "chard_check_journal_after":
			AddQuestRecord("WhisperChardQuest", "8");
			chrDisableReloadToLocation = false;
			dialog.Text = "If I understand correctly, the treasure is located on Dominica. I'll tell you a more precise place when we get there.";
			Link.l1 = "Then let's not delay. Get your brig ready.";
			npchar.Ship.Type = GenerateShipExt(SHIP_NEUFCHATEL, true, npchar);
			npchar.Ship.name = "The darling of luck";
			SetBaseShipData(npchar);
			npchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCharacterGoods(npchar,GOOD_FOOD,500);
			SetCharacterGoods(npchar,GOOD_BALLS,500);
			SetCharacterGoods(npchar,GOOD_GRAPES,500);
			SetCharacterGoods(npchar,GOOD_KNIPPELS,500);
			SetCharacterGoods(npchar,GOOD_BOMBS,500);
			SetCharacterGoods(npchar,GOOD_POWDER,1000);
			SetCharacterGoods(npchar,GOOD_PLANKS,150);
			SetCharacterGoods(npchar,GOOD_SAILCLOTH,150);
			SetCharacterGoods(npchar,GOOD_RUM,200);
			SetCharacterGoods(npchar,GOOD_WEAPON,250);
			SetCharacterGoods(npchar,GOOD_MEDICAMENT,300);
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(NPChar.index));
			Link.l1.go = "exit_chard_setsail";
		break;
		case "exit_chard_setsail":
			NextDiag.TempNode = "chard_on_dominica";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.WhisperChardCompanion = true;
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", pchar.Whisper.EsFriendTown+"_tavern", "", "", "", 7);
			LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], false);
			DeleteAttribute(pchar,"Whisper.EsFriendTown");

			pchar.quest.WhisperChardShore26.win_condition.l1          = "location";
			pchar.quest.WhisperChardShore26.win_condition.l1.location = "shore26";
			pchar.quest.WhisperChardShore26.function             = "WhisperChardShore";
			pchar.quest.WhisperChardShore27.win_condition.l1          = "location";
			pchar.quest.WhisperChardShore27.win_condition.l1.location = "shore27";
			pchar.quest.WhisperChardShore27.function             = "WhisperChardShore";
		break;
		case "chard_on_dominica":
			dialog.Text = "Here we are. The treasure is very close, it remains to find the grotto.";
			Link.l1 = "Well, let's go.";
			Link.l1.go = "chard_follow";
		break;
		case "chard_follow":
			NextDiag.TempNode = "chard_in_cave";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);

			pchar.quest.WhisperChardCave.win_condition.l1          = "location";
			pchar.quest.WhisperChardCave.win_condition.l1.location = "Dominica_grot";
			pchar.quest.WhisperChardCave.function             = "WhisperChardCave";
		break;
		case "chard_in_cave":
			if (!CheckAttribute(pchar, "cursed.waitingSkull"))
			{
				pchar.cursed.waitingSkull = true;
				pchar.cursed.lockspawn = true;
			}
			if (CheckAttribute(pchar, "WhisperWonSword"))
			{
				dialog.Text = "Ha ha ha! And this blade is for me! Look how wide it is. And it feels pleasantly heavy in my hands. Look into the chest, maybe you'll find something interesting for yourself.";
			}
			else
			{
				Log_Info("You got your sword back");
				GiveItem2Character(pchar, "blade_whisper");
				EquipCharacterByItem(pchar, "blade_whisper");
				PlaySound("interface\important_item.wav");
				dialog.Text = "Ha ha ha! And this blade is for me! Look how wide it is. And it feels pleasantly heavy in my hands. And by the way, I promised you, I'm giving you your feather sword. Don't forget to look in the chest, maybe you'll find something interesting for yourself.";

			}
			Link.l1 = "Well, you're smart! I guess I've already pulled out all the most valuable things. I'm going to take a look...";
			Link.l1.go = "chard_exit_to_cave_entrance";

			ref _location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 300000;
			_location.box1.items.icollection = 1;
			_location.box1.items.Map_Best = 1;
			_location.box1.items.suit_2 = 1;
			//_location.box1.items.indian11 = 1;
			_location.box1.items.chest = 5;
			_location.box1.items.chest_quest = 2;
			_location.box1.items.jewelry1 = 30+rand(5);
			_location.box1.items.jewelry2 = 30+rand(5);
			_location.box1.items.jewelry3 = 30+rand(5);
			_location.box1.items.jewelry4 = 15+rand(5);
			_location.box1.items.jewelry6 = rand(55);
			_location.box1.items.jewelry7 = rand(70);
			_location.box1.items.jewelry10 = rand(55);
			_location.box1.items.jewelry14 = rand(55);
			_location.box1.items.jewelry15 = rand(8);
			_location.box1.items.jewelry18 = rand(90);

		break;
		case "chard_exit_to_cave_entrance":
			chrDisableReloadToLocation = false;
			NextDiag.TempNode = "chard_cave_entrance";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Dominica_caveentrance", "", "", "", 7);
			pchar.quest.WhisperChardCave.win_condition.l1          = "location";
			pchar.quest.WhisperChardCave.win_condition.l1.location = "Dominica_caveentrance";
			pchar.quest.WhisperChardCave.function             = "WhisperChardCave";
		break;

		case "chard_cave_entrance":
			if (CheckAttribute(pchar, "cursed.lockspawn"))
			{
				DeleteAttribute(pchar, "cursed.waitingSkull");
				DeleteAttribute(pchar, "cursed.lockspawn");

			}
			pchar.quest.WhisperChardCave.win_condition.l1          = "location";
			pchar.quest.WhisperChardCave.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.WhisperChardCave.function             = "WhisperEngRevengeWarning";
			LocatorReloadEnterDisable("shore26", "boat", false);
			LocatorReloadEnterDisable("shore27", "boat", false);
			WhisperEnglandRevengel();
			pchar.ContraInterruptWaiting = true;
			dialog.Text = "You have to admit, we have made a big jackpot. There was so much loot there that I'm not even sorry to share it with you. I can drink it for a few years. Well, shall we run away?";
			Link.l2 = "Yes, I also need to sort out my share. Good luck to you.";
			Link.l2.go = "chard_exit_to_cave_entrance_1";
			if (CheckAttribute(pchar, "WhisperWonSword"))
			{
				Link.l1 = "Wait a minute, buddy. Don't you want to keep swimming with me? I'm sure we'll find a lot more loot together.";
				Link.l1.go = "chard_discuss_recruitment";
			}
		break;
		case "chard_discuss_recruitment":
			dialog.Text = "Hmm... I only go with those whose luck I am absolutely sure of. You beat me at cards, but I'm not as good at them as I am at dice. Let's check it out. If luck really loves you, then you will win, and I will follow you to the ends of the earth. The rules are the same, up to five wins.";
			Link.l1 = "Good. We're playing.";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 0;
            pchar.GenQuest.Dice.SitType   = false;
			Link.l1.go = "meet_chard_dice_begin_go";
			Link.l2 = "No, I don't want to play today, let's split up then. Good luck to you.";
			Link.l2.go = "chard_exit_to_cave_entrance_1";
		break;
		case "meet_chard_dice_begin_go":
			chrDisableReloadToLocation = true;
			NextDiag.TempNode = "chard_after_dice_game";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchDiceGame();
			Lai_SetStayType(npchar);
		break;
		case "chard_after_dice_game":
			chrDisableReloadToLocation = false;

			if(CheckAttribute(pchar, "WhisperWonChard"))
			{
				LAi_SetImmortal(NPChar, false);
				SetCharacterRemovable(npchar, true);
				dialog.Text = "Yes, good luck to you. So be it, I trust you with my life.";
				Link.l1 = "That's great. You'll get into the fire-ship. Joke... Let's go.";
				Link.l1.go = "chard_hired";
			}
			else
			{
				dialog.Text = "It looks like fate itself has intervened. Unfortunately, nothing will work out for us.";
				Link.l1 = "Well, okay. Then good luck to you.";
				Link.l1.go = "chard_exit_to_cave_entrance_1";
			}
		break;
		case "chard_exit_to_cave_entrance_1":
			dialog.Text = "And you. Always keep an ace up your sleeve! Here's a good luck souvenir for you, from my share.";
			npchar.LifeDay = 0;
			TakeNItems(pchar, "indian11", 1);
			Log_Info("You got the rags");
			PlaySound("interface\important_item.wav");
			Link.l1 = "Thank you! Goodbye.";
			Link.l1.go = "chard_exit_to_cave_entrance_2";
		break;
		case "chard_hired":
			chrDisableReloadToLocation = false;
			DialogExit();
			Lai_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "Dominica_grot", "", "", "", 12);
			SetCharacterPerk(npchar, "Adventurer");
			NPChar.Payment = true;
			//npchar.greeting = "Gr_QuestOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;  // Контузия
			npchar.loyality = MAX_LOYALITY;
			//AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			npchar.Dialog.CurrentNode = "hired";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
		break;
		case "chard_exit_to_cave_entrance_2":
			chrDisableReloadToLocation = false;
			//NextDiag.TempNode = "chard_cave_entrance";
			//NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			Lai_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "Dominica_grot", "", "", "", 12);
		break;

		case "chard_failed":
			dialog.Text = "Eh, it seemed to me that the bet was right, but I shouldn't have trusted you. Get out of my sight...";
			LAi_SetImmortal(NPChar, true);
			npchar.LifeDay = 0;
			Link.l1 = "Don't get so mad, I'm leaving already.";
			Link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], false);
			DeleteAttribute(pchar,"Whisper.EsFriendTown");
		break;
		case "chard_betrayed":
			NPChar.rank = 77;
			LAi_SetHP(NPChar, 777.0, 777.0);
			if (CheckAttribute(pchar, "WhisperWonSword"))
			{
				NPChar.money = 77777;
			}
			else
			{
				NPChar.money = 277777;
			}
			chrDisableReloadToLocation = true;
			pchar.Whisper.BetrayChardKill = true;
			TakeNItems(npchar, "bible", 1);
			npchar.SaveItemsForDead = true;
			dialog.Text = "Eh, it seemed to me that the bet was right, but I shouldn't have trusted you, let's see who gets lucky today. Let's cross blades!";
			Link.l1 = "I see it's the same game for you as the cards. It's worse for you.";
			Link.l1.go = "chard_fight";
			LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], false);
			DeleteAttribute(pchar,"Whisper.EsFriendTown");
		break;
		case "chard_fight":
			Group_FindOrCreateGroup("EnemyFight");
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			//ref sld;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		case "chard_discuss_esteban":
			npchar.DiscussedEsteban = true;
			dialog.Text = "He and I were old acquaintances, we even went under the same sail when we were simple sailors. Our captain recruited everyone into the team, regardless of nationality. But that was many years ago. In the end, Hernan went to serve in his homeland, and I inherited a ship from Cap. We haven't seen each other for a long time since then, but recently we met again and decided to play a few cards. It seems that over the years of service, he lost all his former luck, as I beat him pretty quickly. As a result, he owed me a large sum of money. As an old friend, I didn't rush him too much with the payment. But he didn't like the idea that he owed anyone, especially me, so Hernan decided that he would rob everyone indiscriminately until he accumulated the amount, which his employer didn't seem to like. And in the end, he said that he would go after the bordello treasure, supposedly the valuables from there would more than cover the gambling debt. I doubted the existence of this treasure, and it seems for good reason.I didn't want to let him go, but Hernan insisted on his own. As a result, we agreed that he would pay me at least partially before sailing. I took this sword and one other thing, but it seems like I've lost the chance to get the remaining amount from it forever.";
			Link.l1 = "You mentioned something. What is it?";
			Link.l1.go = "chard_discuss_esteban_1";
			//Link.l1 = "Aren't you going to avenge your friend's death on me?";
			//Link.l1.go = "chard_discuss_esteban_1";
		break;
		case "chard_discuss_esteban_1":
			dialog.Text = "I don't know, it just seemed like a beautiful trinket to me. I sold it the very next day to some guy in a hood who suddenly showed up to me.";
			Link.l1 = "What did this trinket look like?";
			Link.l1.go = "chard_discuss_esteban_2";
		break;
		case "chard_discuss_esteban_2":
			dialog.Text = "A metal plate with a bunch of glass tubes and levers attached to it. It was also covered with strange inscriptions and other tinsel.";
			Link.l1 = "Damn it, this is my time machine!";
			Link.l1.go = "chard_discuss_esteban_3";
		break;
		case "chard_discuss_esteban_3":
			dialog.Text = "What?";
			Link.l1 = "Nothing. Where did this customer of yours go?";
			Link.l1.go = "chard_discuss_esteban_4";
		break;
		case "chard_discuss_esteban_4":
			dialog.Text = "I have no idea, after our deal, I wanted to find him myself and show him a couple more items for sale, but I couldn't. He seemed to have disappeared. Neither the innkeeper nor the port commander saw him. I almost believed that I had never seen him myself, if not for the weight in my wallet. Perhaps he paid these people a tidy sum for their silence.";
			Link.l1 = "Clearly, it's a dead end again, but at least I have hope. Thanks for the information.";
			Link.l1.go = "exit";
		break;
		case "chard_discuss_esteban_old":
			dialog.Text = "You had your own scores with him, I can't blame you for that. And in the Caribbean, people kill each other every day, I've already become indifferent to this. But losing a large debtor is always a shame. But I won't ask you for it.";
			Link.l1 = "I see.";
			Link.l1.go = "exit";
		break;
		case "chard_discuss_quest":
			dialog.Text = "I visited Bermudes once. There, in the dungeon, I found someone's treasure full of all sorts of jewelry, as well as a bible. I initially put it aside and did not pay attention, but when I drank my share of the treasure, I decided to look through it out of curiosity. Apart from the fact that it was all written in Latin or some other strange language, there was nothing remarkable about it. Except for a few underlined phrases scattered throughout the book. As I later realized, it was a cipher. It took me and my team several days to solve it. In this hidden message, it was said about a much larger treasure collected by the efforts of a group of corsairs, even the coordinates of its location were attached. That's just not complete, some of the pages have deteriorated. I'm missing one number to get the exact location. The book also talked about a certain Ralph Portman, either a friend of the one who left the bible, or the owner himself. Perhaps this is a weak lead, and there may be many people with that name in the Caribbean, but I still dug deeper and found out that there is such a privateer in the service of the British. ";
			Link.l1 = "You've already told me a lot, but you haven't got to the point. Why do you need me?";
			Link.l1.go = "chard_discuss_quest_1";
		break;
		case "chard_discuss_quest_1":
			//NextDiag.TempNode = "chard_discuss_quest_1";
			dialog.Text = "I need you to find this Portman and find out the missing coordinate, if he has one.";
			Link.l1 = "Why don't you do it yourself?";
			Link.l1.go = "chard_discuss_quest_2";
		break;
		case "chard_discuss_quest_2":
			dialog.Text = "You see, I own only a modest brig, and Portman has several frigates. I'm afraid if it comes to a fight, only a wet spot will remain of my tub. But your 'War Dog' will overcome them without any problems.";
			Link.l1 = "A corvette against a group of frigates? I doubt it.";
			Link.l1.go = "chard_discuss_quest_3";
		break;
		case "chard_discuss_quest_3":
			dialog.Text = "You probably just switched to 'War Dog' recently. This corvette is in no way inferior to the frigates, in many ways even surpasses them. But if you still doubt your abilities, you can visit Alexus.";
			Link.l1 = "Alexus? Who is this?";
			Link.l1.go = "chard_discuss_quest_4";
			Link.l2 = "Okay, I'll think about it. Where can I even look for this Englishman?";
			Link.l2.go = "chard_discuss_quest_5";
		break;
		case "chard_discuss_quest_4":
			dialog.Text = "Well, the master shipbuilder, the best in the whole archipelago. He has his own shipyard in Bermudes. You can show him your ship. Although the 'War Dog' is good, I'm sure Alexus will find ways to improve it. Then you can deal with any squadron without any problems.";
			Link.l2 = "Okay, I'll think about it. Where is this Englishman to be found?";
			Link.l2.go = "chard_discuss_quest_5";
		break;
		case "chard_discuss_quest_5":
			NextDiag.TempNode = "chard_waiting_quest_result";
			//SaveCurrentNpcQuestDateParam(pchar,"Whisper.LastSeenPortman");
			pchar.Whisper.ActiveChardQuest = true;
			AddQuestRecord("WhisperChardQuest", "2");
			dialog.Text = "The last time I saw him was in local waters, but then I did not dare to act, and he swam away. I think you'll have no problem finding him. Ask around at the port authorities, you've probably seen him somewhere, and if you can handle it, come back here. I'll combine the coordinates and get the exact location of the treasure.";
			Link.l2 = "Okay, goodbye.";
			Link.l2.go = "exit";
		break;
		case "chard_get_sword":
			Log_Info("You got your sword back");
			GiveItem2Character(pchar, "blade_whisper");
			EquipCharacterByItem(pchar, "blade_whisper");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			DeleteAttribute(npchar, "items");
			DeleteAttribute(npchar, "equip");
			GiveItem2Character(npchar, "pistol4");
			EquipCharacterbyItem(npchar, "pistol4");
			GiveItem2Character(npchar, "blade34");
			EquipCharacterByItem(npchar, "blade34");
			dialog.Text = "Since you're here and you have a good ship, would you mind helping me with something?";
			Link.l1 = "What kind of help is needed?";
			Link.l1.go = "chard_discuss_quest";
		break;
		case "chard_not_played":
			dialog.Text = "You again? Did you decide to play with me?";
			if (sti(pchar.money) >= 200000)
			{
				Link.l1 = "Okay, deal the cards.";
				Link.l1.go = "meet_chard_7_cardGame";
			}
			Link.l2 = "No.";
			Link.l2.go = "exit";
		break;
		case "meet_chard":
			NextDiag.TempNode = "chard_not_played";
			dialog.Text = "Did I call you? I'm sorry, I don't remember. I was probably too drunk... Who exactly are you?";
			Link.l1 = "Whisper. The captain of the corvette ";
			Link.l1.go = "meet_chard_1";
		break;
		case "meet_chard_1":
			dialog.Text = "Captain? Wait, where did Esteban go?";
			Link.l1 = "Tragically died at Turks. He was ambushed there.";
			Link.l1.go = "meet_chard_2";
			Link.l2 = "I killed that bastard.";
			Link.l2.go = "meet_chard_3";
		break;
		case "meet_chard_2":
			dialog.Text = "But I told him that there was something unclean with this treasure. Like I smelled a trap.";
			Link.l1 = "(Your eye is drawn to the familiar grip of the blade that hangs from the waist of a stranger.) Wait a minute... That's my sword! ";
			Link.l1.go = "meet_chard_4";
		break;
		case "meet_chard_3":
			dialog.Text = "You can't argue with the fact that he's a scumbag, but how dare he die without paying me back first?";
			Link.l1 = "(Your eye is drawn to the familiar grip of the blade that hangs from the waist of a stranger.) Wait a minute... That's my sword! ";
			Link.l1.go = "meet_chard_4";
		break;
		case "meet_chard_4":
			dialog.Text = "I don't know anything. This blade is mine, I honestly won it at cards from Esteban... I think I've figured out who you are, Whisper. Esteban was talking about the girl he took the pistol and sword from. It's really nice to finally meet you, I'm Michael Chard. He really told me that he finished you off.";
			Link.l1 = "As you can see, I'm more alive than anyone alive, unlike this windbag. Now give me the sword!";
			Link.l1.go = "meet_chard_5";
		break;
		case "meet_chard_5":
			dialog.Text = "Look what you've done! I won't give you anything just like that, but still, I don't really like this sword, it's too light, and I like heavier weapons. You know what? Let's play cards. If you win, it's yours. If I win, you'll pay. Let's say... two hundred thousand.";
			Link.l1 = "How much? Did you hit your head?";
			Link.l1.go = "meet_chard_6";
			if (sti(pchar.money) >= 200000)
			{
				Link.l2 = "All right, hand out the cards.";
				Link.l2.go = "meet_chard_7_cardGame";
			}
			Link.l3 = "Let's do it some other time.";
			Link.l3.go = "exit";
		break;
		case "meet_chard_6":
			dialog.Text = "I'm not going to play for less money. Either we play, or get out of here.";
			if (sti(pchar.money) >= 200000)
			{
				Link.l1 = "Okay, deal the cards.";
				Link.l1.go = "meet_chard_7_cardGame";
			}
			Link.l2 = "Let's do it some other time.";
			Link.l2.go = "meet_chard_8";
		break;
		case "meet_chard_8":
			dialog.Text = "Come back if you change your mind.";
			Link.l1 = "Goodbye.";
			Link.l1.go = "exit";
		break;
		case "meet_chard_7_cardGame":
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.Text = "That's our way! We play to five wins.";
			Link.l1 = "Okay.";
			Link.l1.go = "meet_chard_Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			int iLa_Puesta = 0;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		break;
		case "meet_chard_Cards_begin_go":
				chrDisableReloadToLocation = true;
                //Diag.CurrentNode = Diag.TempNode;
                DialogExit();
                LaunchCardsGame();
		break;

		case "LejitosOff":
			NPChar.Payment = true;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			//npchar.greeting = "Gr_QuestOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;  // Контузия
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			//LAi_SetWarriorType(NPChar);
			DialogExit();
		break;
		case "LejitosNoOff":
			DialogExit();
			NPChar.lifeday = 0;
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10);
		break;
		case "Lejitos":
			dialog.Text = "I am not a Christian. My parents used to be, but they didn't live long enough to impose this belief on me. I was found, raised and raised in the Guarani Indian tribe. They opened my eyes to the true faith and told me the whole point about the Christian God.";
			Link.l1 = "Have you lived your whole life among Indians?";
			Link.l1.go = "Lejitos_1";
		break;
		case "Lejitos_1":
			dialog.Text = "Unfortunately, the Spaniards didn't give me that luxury. One day I went hunting, and when I returned home with the loot, I found our village in ruins. The whole tribe was exterminated. Of course, I took revenge, but this will not bring back the tribe. After that, I went to live with the Spaniards, in a so-called civilized society. For several years I lived in peace, settling into a new place, until one day someone told the local priest about the harmless Indian rituals that I performed before eating. He, in turn, brought this to the Inquisition, and what happened next, I think you can understand for yourself. Since then, I have been hiding from the Spaniards in the Dutch colonies, but even here they do not give me peace. This is far from the first and not the last group of hunters that comes after my head.";
			Link.l1 = "Personally, I don't care what you believe in. But as a fighter, I see that you are a real beast. Do you want to come to my office? I promise you, being on my team, you will kill a lot of Spaniards. Right now, I intend to catch up with that ship that one of those scum was talking about.";
			Link.l1.go = "Lejitos_2";
			Link.l2 = "I don't think you and I are on the same path, buddy. Goodbye.";
			Link.l2.go = "LejitosNoOff";
		break;
		case "Lejitos_2":
			dialog.Text = "You're very persuasive. Of course, I wouldn't mind adding a couple more Spanish scalps to my collection.";
			Link.l1 = "That's settled. By the way, I was told that you went to this cave for the treasure. Did you manage to find anything?";
			Link.l1.go = "Lejitos_3";
		break;
		case "Lejitos_3":
			dialog.Text = "This is not a treasure, but an Indian relic. I can give it to you for safekeeping, but please don't sell it. It will surely be melted down into bars, after which its true value will be lost forever.";
			Link.l1 = "All right, let's go.";
			Link.l1.go = "LejitosOff";
		break;

		case "DeSouzaHunter":
			dialog.Text = "Wow, who came! It looks like we're going to kill two birds with one stone! That godless Eligio would already be enough to please Senor de Souza, but when we bring him you too, we will surely be given a bonus!";
			Link.l1 = "De Souza, you say? Where is he?";
			Link.l1.go = "DeSouzaHunter_1";
		break;
		case "DeSouzaHunter_1":
			AddQuestRecord("WhisperQuestline", "6");
			dialog.Text = "What, can't wait to get a fresh dose of torture from him? I assure you, it won't be long to wait, because he's here, not far away, on the ship. We docked in a bay with an ironic name for you - The Coast of Salvation On the ship, all the tools are already prepared. You're a Wisper, right? I saw an iron maiden there, signed with your name, so how are you going to go yourself? Or do you want to grab a portion from us first? I'm asking you the same question, Senor Lejito.";
			Link.l1 = "Now let's see who gets it from whom!";
			Link.l1.go = "exit_lejitos_speak";
		break;
		case "exit_lejitos_speak":
			DialogExit();
			sld = characterFromID("W_Lejitos");
			SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
		break;
		case "exit_cave_entrance_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			//ref sld;
			for (int i = 1; i <= 7; i++)
			{
				sld = characterFromID("DeSouzaHunter"+sti(i));
				LAi_SetWarriorType(sld);
				LAi_SetImmortal(sld, false);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			}
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		case "Smuggler":
			NextDiag.TempNode = "Smuggler";
			if (CheckAttribute(pchar, "Whisper.ContraSmuggler"))
			{
				dialog.Text = "Who else are you? What do you want here?";
				Link.l1 = "You and I have a mutual acquaintance named "+GetCharacterFullName("Tortuga_trader")+". I brought the goods as agreed.";
				Link.l1.go = "Whisper_contraband";
				Link.l2 = "Nothing.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.Text = "The deal has been done, and now get out of here, there's nothing to bother your eyes!";
				Link.l1 = "I'm leaving, but I don't need to be impertinent.";
				Link.l1.go = "exit";
			}

		break;
		case "Whisper_contraband":
			if(Pchar.Location != Pchar.location.from_sea)
			{
				dialog.Text = "This is all very interesting, but where is your ship? Or did you bring all the goods on the hump?";
				Link.l1 = "There will be a ship, I just wanted to check the place first.";
				Link.l1.go = "Whisper_contraband_2";
				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) >= 100)
			{
				DeleteAttribute(pchar, "Whisper.ContraSmuggler");
				dialog.Text = "I see it. Everything seems to be in order. My slaves... that is, the workers will unload everything in a flash. Here's your money.";
				AddMoneyToCharacter(PChar, 50000);
				RemoveCharacterGoods(Pchar, GOOD_EBONY, 100);
				Link.l1 = "Not a bad amount, thank you.";
				Link.l1.go = "Whisper_contraband_1";

				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) < 100 && GetSquadronGoods(Pchar, GOOD_EBONY) > 0)
			{
				dialog.Text = "You don't have enough goods. Come back when you've packed it.";
				Link.l1 = "It's true. Wait, I'll buy more now and come back.";
				Link.l1.go = "Whisper_contraband_2";
				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) == 0)
			{
				dialog.Text = "Are you kidding me? You don't have the right goods in your hold at all!";
				Link.l1 = "I think I moved it somewhere. Don't go anywhere, I'm here now.";
				Link.l1.go = "Whisper_contraband_2";
			}
		break;
		case "Whisper_contraband_1":
			dialog.Text = "By the way, if you find anything else interesting, bring it to us right away, otherwise "+GetCharacterFullName("Tortuga_trader")+" he is going to tie up with such deals. You can always find one of our representatives in the tavern.";
			WhisperRemoveSmugglersFromShore();
			AddQuestRecord("WhisperContraband", "3");
			CloseQuestHeader("WhisperContraband");
			Link.l1 = "Okay, I'll take that into account.";
			Link.l1.go = "exit";
			//pchar.quest.WhisperChinaman.win_condition.l1 = "ExitFromLocation";
			pchar.quest.WhisperChinaman.win_condition.l1 = "EnterToSea";
			pchar.quest.WhisperChinaman.function    = "WhisperChinaman";
			WhisperSmugglingPatrol();
			pchar.ContraInterruptWaiting = true;
			//CaptainComission_GenerateCoastalPatrol();

		break;
		case "Whisper_contraband_2":
			dialog.Text = "And hurry up, I'm not going to stay in this bay all my life.";
			Link.l1.go = "exit";
		break;

		case "Jim":
			dialog.text = "After you've dealt with Jack, none of the team will want to contradict you. He kept everyone at bay. In addition, we have such a tradition on the ship - after the death of the old captain, the new ones appoint the most desperate hack who will kill the rest of the applicants for the hat. Such a captain would not be afraid to lead us to the richest loot.";
			link.l1 = "You know, I like your tradition. How many captains have changed already?";
			link.l1.go = "Jim_1";
		break;
		case "Jim_1":
			dialog.text = "Decent.  It's not for nothing that the ship is called the Black Widow. People of all stripes, ages and genders have managed to visit this post. On average, the cap holds his position for several months, and then either by some ridiculous accident he dies, or the team rebels. Bill was the luckiest-he lasted three years.";
			link.l1 = "You described a gloomy picture to me. It seems as if this 'Widow' of yours is cursed. But you can't get rid of me that easily. I agree to become a captain, though I would not say that I understand the management of the ship.";
			link.l1.go = "Jim_2";
		break;
		case "Jim_2":
			SetQuestHeader("WhisperContraband");
			AddQuestRecord("WhisperContraband", "1");
			pchar.Whisper.Contraband = true;
			pchar.Whisper.FindDesouza = true;
			SetTimerCondition("W_Smuggling", 0, 0, 60, false);
			dialog.text = "Nothing, you'll learn. Bill couldn't do it at first either, but nevertheless became the most successful captain of the Widow. We will help you, if you'll need, at first. By the way, Bill also had a map of the archipelago with him, if you found it, use it to make it easier to navigate the sea, and if you don't know where to start, look at his ship's log. There are notes that Bill made up. We were supposed to take the goods to someone on Tortuga, but I don't know all the details, so you'd better read it yourself.";
			link.l1 = "Okay, I'll read it at my leisure. And where is our boat?";
			link.l1.go = "Jim_EndLine";
		break;
		case "Jim_EndLine":
			dialog.text = "Yes, right here in the bay. Come to the shore and get into the boat again. The case that Bill was up to was probably not entirely legal. I advise you to change into something inconspicuous before you take it on. We have a lot of rags on the ship, you can pick up something for yourself.";
			TakeNItems(pchar, "suit_1", 1);
			Log_Info("You got the rags");
			PlaySound("interface\important_item.wav");
			link.l1 = "...";
			link.l1.go = "Finish";
		break;
		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			LocatorReloadEnterDisable("Santiago_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload4", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_Port", "reload1_back", false);
			InterfaceStates.DisFastTravel = false;
			DeleteAttribute(Pchar, "questTemp.WhisperTutorial");
			bDisableLandEncounters = false;
			//DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
			Lai_SetPlayerType(pchar);

			SetQuestHeader("WhisperQuestline");
			AddQuestRecord("WhisperQuestline", "1");
			AddQuestRecord("WhisperQuestline", "2");
			AddQuestUserData("WhisperQuestline", "sWhCapName", GetFullName(characterFromId("wl_Pirate_Cap")));
			//AddQuestRecord("WhisperQuestline", "3");

			SetQuestsCharacters();

			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 25);
			for(i=1; i < 5; i++)
			{
				sld = CharacterFromID("Wh_Crew"+sti(i));
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 20);
			}
		break;
		case "Jack":
			dialog.text = "Is it true? Ha ha! That is, E... It's a pity, of course. Okay, give me his stuff and get out.";
			link.l1 = "Unlikely, I need it too.";
			link.l1.go = "Jack_1";
		break;
		case "Jack_1":
			dialog.text = "You probably didn't understand. These hats with a blade, like a crown with a scepter, are symbols of power on the Black Widow. To whom they belong and to be the captain. I've been patient for a long time, waiting for my turn. I didn't strangle the captain in my sleep to speed it up. I was going to, but I didn't.";
			link.l1 = "Judging by what has been said, you are still a scumbag, and trusting you with power is madness.";
			link.l1.go = "Jack_2";
		break;
		case "Jack_2":
			dialog.text = "Oh, you rascal! Yes, I like you...";
			link.l1 = "Try it.";
			link.l1.go = "Jack_fight";
		break;
		case "Jack_fight":
			Lai_SetPlayerType(pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			PChar.quest.WhisperJimTalk.win_condition.l1 = "NPC_Death";
			PChar.quest.WhisperJimTalk.win_condition.l1.character = npchar.id;
			pchar.quest.WhisperJimTalk.function = "WhisperJimTalk";
			DialogExit();
		break;
		case "NF":
			dialog.text = "If I were an inquisitor, I would definitely want to roast you too. Ha, a joke! But still, they don't hold such an appearance in high esteem.";
			link.l1 = "I've already figured that out.";
			link.l1.go = "NF_1";
		break;
		case "NF_1":
			dialog.text = "Let's get acquainted. I'm Nine-Fingered Bill.";
			link.l1 = "Whisper.";
			link.l1.go = "NF_2";
		break;
		case "NF_2":
			dialog.text = "Damn, you already have a nickname like a real corsair! I'll tell you what, Whisper. Since you are hiding from the Spaniards, it would be nice for you to make new documents so that you can hide in the colonies of another country.";
			link.l1 = "And where can I get them?";
			link.l1.go = "NF_3";
		break;
		case "NF_3":
			dialog.text = "Yes, right in our town, in a tavern. It's a big building behind me. Look for a diplomat at one of the tables. He will do everything for you in the best possible way.";
			link.l1 = "Thanks for the advice, I will definitely use it.";
			link.l1.go = "NF_exit";
		break;
		case "NF_exit":
			Lai_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.Whisper.BuyDocuments = true;
		break;
		case "NF_2_1":
			dialog.text = "I don't know about you, but I'm breaking through to my ship and leaving here.";
			link.l1 = "...";
			link.l1.go = "NF_2_exit";
		break;
		case "NF_2_exit":
			//Lai_SetPlayerType(pchar);
			TakeNItems(npchar, "blade19", 1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_CharacterPlaySound(pchar, "People Fight\Player_Man_Shoot_01.wav");
			DoQuestFunctionDelay("WhisperKillNineFingers", 0.7);
			DialogExit();
			pchar.questTemp.Whisper.GetHat = true;
			DoQuestCheckDelay("TalkSelf_Quest", 2.5);
		break;
		case "Pirateguard":
			dialog.text = RandPhraseSimple("What do you want? Pass by.", "Stop blocking the road, get off.");
			link.l1 = RandPhraseSimple("You know what? Don't bark!", "Slow down your ardor. Otherwise I'll cool it down quickly!");
			NextDiag.CurrentNode = "Pirateguard";
			link.l1.go = "exit";
		break;
		case "IncqGuard_bad":
			dialog.text = "So we were left alone. Did you really think that was the end of it? If so, I have to disappoint you. You see, while de Souza is resting or doing other things, I'm filling in for him here. I won't ask you any questions, that's what the Inquisitor is doing. I'll just make you more accommodating by the time he arrives, so that he no longer has to get answers out of you. Come on, I'll introduce you to our 'toys'. We recently received a 'Wheel', and you will have the honor of being the first to experience it in action. Come on, don't be shy. And don't try to escape, there are a lot of guards here.";
			link.l1 = "(Follow him silently)";
			link.l1.go = "IncqGuard_bad_go_to_wheel";
		break;
		case "IncqGuard_bad_go_to_wheel":
			DialogExit();
			LAi_ActorGoToLocator(NPChar, "goto", "goto11", "WhisperLine_IncqGuard_bad_speaks", -1);
			LAi_ActorGoToLocator(PChar, "goto", "goto11", "WhisperLine_IncqGuard_bad_speaks", 10);
			Npchar.dialog.currentnode = "IncqGuard_bad_wheel";
			//DoQuestFunctionDelay("WhisperLine_IncqGuard_bad_speaks", 5);
		break;
		case "IncqGuard_bad_wheel":
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("IncqGuard_"+i);
				LAi_SetActorTypeNoGroup(sld);
			}
			dialog.text = "Here is our beauty.  If I remember the instructions correctly, you should first be tied to the wheel, after which, slowly rotate the lever. The spikes below will hopelessly cripple and disfigure your body. It is unlikely that after this you will be able to walk at all without someone else's help... Well, where did the rope go?";
			link.l1 = "I'm sorry, but I have to decline your offer. I will still need the ability to walk when I look for a way out of here. (While he hesitates, you pull his gun out of its holster with a sharp movement)";
			link.l1.go = "IncqGuard_bad_wheel_kill";
		break;
		case "IncqGuard_bad_wheel_kill":
			DialogExit();
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			npchar.SaveItemsForDead = true;
			GiveItem2Character(pchar, "pistol3");
			EquipCharacterByItem(pchar, "pistol3");
			Lai_SetPlayerType(pchar);
			//AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("WhisperLine_WhisperHits", 0.2);
		break;
		case "IncqGuard":
			dialog.text = "I've heard that the local tavern is talking about you. Allegedly, you were able to beat up a crowd of sailors alone. Is it true?";
			link.l1 = "With my modern weapons, it wasn't difficult. Why are you staring at me like that?";
			link.l1.go = "IncqGuard_1";
		break;
		case "IncqGuard_1":
			dialog.text = "I've never seen such beautiful girls in my life, and even with purple hair... you... Are you a witch?";
			link.l1 = "Do you want me to enchant you too?";
			link.l1.go = "IncqGuard_2";
		break;
		case "IncqGuard_2":
			dialog.text = "God have mercy on me! I'm not...";
			link.l1 = "...Abuda, kabuda, avara kadava!";
			link.l1.go = "IncqGuard_3";
		break;
		case "IncqGuard_3":
			dialog.text = "Shut up immediately, or you'll be here now!";
			link.l1 = "Kumprana, vocamos, turn into a frog, BYDYSCH!";
			link.l1.go = "IncqGuard_4";
			Pchar.BaseNation = SPAIN;
			if (CheckAttribute(npchar,"quest.answer_1"))
			{
				link.l1 = "Okay, I'm ready.";
				link.l1.go = "IncqGuard_exit";
			}
		break;
		case "IncqGuard_4":
			dialog.text = "Aaaaa, help!!";
			npchar.quest.answer_1 = true;
			link.l1 = "...";
			link.l1.go = "IncqGuard_exit";
		break;
		case "IncqGuard_exit":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			
			Lai_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			PChar.quest.WhisperEscape.win_condition.l1 = "locator";
			PChar.quest.WhisperEscape.win_condition.l1.location = "Santiago_Incquisitio";
			PChar.quest.WhisperEscape.win_condition.l1.locator_group = "reload";
			PChar.quest.WhisperEscape.win_condition.l1.locator = "reload1_back";
			PChar.quest.WhisperEscape.function = "WhisperEscape";
		break;
		case "ADS":
			dialog.text = "Really? Tell me then, who are you? You don't see that kind of eye and hair color every day, you know. And what kind of pistol did " + GetFullName(characterFromId("wl_Pirate_Cap"))+" take away from you?";
			link.l1 = "I... I find it difficult to answer.";
			link.l1.go = "ADS_1_lie";

		break;
		case "ADS_1":
			dialog.text = "From the future, you say? And in that case, what did you need in our time?";
			link.l1 = "Nothing, moving here was an accident. Listen, you need to talk to Hernan Esteban and ask him for the device that I had on me. I'll show you how it works and prove my words.";
			link.l1.go = "ADS_1_1";
		break;
		case "ADS_1_lie":
			dialog.text = "Are you going to play silent with me?";
			pchar.Whisper.DeSouzaHits = 0;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_1_truth":
			dialog.text = "Listening. ";
			link.l2 = "This may be hard for you to believe, but I came from the future. A few centuries later, such weapons will be as widespread as swords are now. And my appearance won't seem so unusual.";
			link.l2.go = "ADS_1";
		break;
		case "ADS_1_1":
			dialog.text = "That's enough. Do you take me for an idiot? I will never believe in time travel. You should have told me another story about the Flying Dutchman. Let's get to the point. If the pistol is not the British, then whose is it, the Dutch?";
			pchar.Whisper.DeSouzaHits = 2;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_1_2":
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits", 0.5);
			DialogExit();
		break;
		case "ADS_2":
			dialog.text = "Do you still dare to threaten me?! You bastard!";
			pchar.Whisper.DeSouzaHits = 1;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_3":
			dialog.text = "You're asking for it.";
			pchar.Whisper.DeSouzaHits = 2;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_4_exit":
			LAi_SetActorTypeNoGroup(npchar);
			//LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DoQuestFunctionDelay("WhisperLine_IncqGuard", 8.0);
		break;


		case "PC":
			dialog.text = "I should be asking you that! Is there a name?";
			link.l1 = "Whisper.";
			link.l1.go = "PC_1";
		break;
		case "PC_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			dialog.text = "Oh, I don't like you. You look too suspicious. Come on, guys, show our new traveling companion the way to the hold, and tie her up well there. I'll deal with her later.";
			link.l1 = "This is where I got myself into...";
			link.l1.go = "PC_nofight";
		break;
		case "PC_nofight":
			Pchar.model="PGG_Whisper_0_NoHat";
			DeleteAttribute(pchar,"cirassID");
			DoQuestFunctionDelay("WhisperHold", 0.5);
			DialogExit();
		break;
		case "PC_2":
			dialog.text = "As long as it takes. These things look expensive, you probably have rich parents. I suggest we go to them and demand a ransom. As soon as I get the money, you're free. So, in which colony can we find them?";
			link.l1 = "I'm not from these places. I don't have any family here.";
			link.l1.go = "PC_2_1";
		break;
		case "PC_2_1":
			dialog.text = "Do you think that would make me feel sorry for you? Or maybe you think you're a fool? Then you are deeply mistaken, you know, I have one friend who can get you to talk - Antonio de Souza. This is the head of the Inquisition in Santiago, and I had to work with him once. I'll tell you what, the guy is very unpleasant, but he knows how to get his way. I brought one taciturn pirate to him, and the next day we already knew about the location of four buried treasures. The poor guy himself died while testifying, I can't even imagine what de Souza will do to you when he sees you. With such a hair color, most likely - right at the stake.";
			link.l1 = "Scare as much as you want, I know a worse story!";
			link.l1.go = "PC_2_2";
			link.l2 = "Can't we come to an agreement?";
			link.l2.go = "PC_2_3";
		break;
		case "PC_2_2":
			dialog.text = "I'm just saying it like it is, be strong. By the time we get there, you have a few days to prepare for far from the most pleasant meeting in your life.";
			link.l1 = "...";
			link.l1.go = "PC_2_exit";
		break;
		case "PC_2_3":
			dialog.text = "I'm afraid not. I offered you an option, but you started dodging the question. Let de Souza already find out if it is possible to get a ransom from you, or where such pistols come from, be strong. By the time we get there, you have a few days to prepare for far from the most pleasant meeting in your life.";
			link.l1 = "...";
			link.l1.go = "PC_2_exit";
			link.l2 = "Wait...";
			link.l2.go = "PC_2_exit";
		break;
		case "PC_2_exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.Whisper.HoldMonologue = true;
			DoQuestCheckDelay("TalkSelf_Quest", 3.0);

		break;

		case "FB":
			//CharacterPlayAction(npchar, "Shot");
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.text = "(You are not injured, but this cannot be said about the device in your hands. The bullet hits the quantum particle rectifier, after which the device turns on and starts working in an arbitrary way, emitting a series of crackles and clicks)";
			PlayVoice("interface\beeping.wav");
			link.l1 = "The Devil!";
			link.l1.go = "FB_exit";
		break;
		case "FB_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.text = "(You are not injured, but this cannot be said about the device in your hands. The bullet hits the quantum particle rectifier, after which the device turns on and starts working in an arbitrary way, emitting a series of crackles and clicks)";
			link.l1 = "The Devil!";
			link.l1.go = "exit";
			DoReloadCharacterToLocation("Ship_Deck_Big","goto","goto5");
			PChar.quest.WhisperTeleport.win_condition.l1 = "location";
			PChar.quest.WhisperTeleport.win_condition.l1.location = "Ship_Deck_Big";
			PChar.quest.WhisperTeleport.function = "WhisperTeleport";
		break;
		case "CS":
			dialog.text = "This is not a toy for you, girl. You can't even imagine what this object is capable of. Put it back, slowly and carefully.";
			link.l1 = "Are you talking about a quantum particle rectifier?";
			link.l1.go = "CS_1";
		break;
		case "CS_1":
			dialog.text = "Do you even realize what you just said?";
			link.l1 = "Not very...";
			link.l1.go = "CS_1_1";
			link.l2 = "Of course! I'm not stupid.";
			link.l2.go = "CS_1_2";
		break;
		case "CS_1_1":
			dialog.text = "Although the name itself may not be clear, but this device allows you to move in space and time. However, any application can cause the entire time sequence to be completely rewritten. Neither you nor I may ever be born. So you'd better put it back in its place, out of harm's way.";
			link.l1 = "Listen, man, I don't have time to sort things out with you. The customer is waiting.";
			link.l1.go = "CS_2";
		break;
		case "CS_1_2":
			dialog.text = "Well, then you should understand why it's not worth touching.";
			link.l1 = "Listen, man, I don't have time to sort things out with you. The customer is waiting.";
			link.l1.go = "CS_2";
		break;
		case "CS_2":
			dialog.text = "Customer? I know only one possible customer who knows about this device, so are you a corporate litter? Do you do whatever you're told?! I'd punch you, but I've been taught since childhood that you can't hit women...";
			link.l1 = "I will ask without insults. I am a free mercenary. I only take on the job that I choose.";
			link.l1.go = "CS_2_1";
		break;
		case "CS_2_1":
			dialog.text = "That's what you think. In fact, you and all of us have been on the hook for a long time. I suppose you got enough loans, and they offered to close them? You don't have to answer. I worked for Omnitech myself and saw their whole rotten system from the inside.";
			link.l1 = "Hmm. The order did not say that the 'mad scientist' is their former employee.";
			link.l1.go = "CS_3";
		break;
		case "CS_3":
			dialog.text = "What a nickname! Yes, my thoughts are clearer than yours! It's the corporations that made me develop the thing in your hands - the madmen! That's why I decided to hide it from them.";
			link.l1 = "So you stole this device from Omnitech?";
			link.l1.go = "CS_3_1";
		break;
		case "CS_3_1":
			dialog.text = "I'm afraid the word 'stolen' is not applicable in this situation. One hundred percent, this is my development. But yes, according to their slave law, any intellectual property developed by an employee of a corporation on the territory of a corporation belongs to the corporation. But you can still call me a thief. When I took the time machine, I also reprogrammed a dozen corporate bots that you might have met on the way here.";
			link.l1 = "Why would a corporation need a time machine?";
			link.l1.go = "CS_4";
		break;
		case "CS_4":
			dialog.text = "And now you're starting to ask the right questions. To return to the past and enslave all mankind even faster! With such a trump map in reserve, like all the time in the world, they will easily become monopolists in everything imaginable and unthinkable, and we will have a future even sadder than what is happening in the world now.";
			LAi_SetImmortal(npchar, false);
			link.l1 = "I really understand you. But personally, I don't care what happens to the rest of humanity. And I will get paid for this order, regardless of whether I have to step over your corpse or not!";
			link.l1.go = "CS_bad";
			link.l2 = "If this thing really does what you say, then maybe you shouldn't give it to corporations. I will find a much better use for it in my hands.";
			link.l2.go = "CS_neutral";
			link.l3 = "Damn, but you're right... So be it, take it and leave here. I'll tell the customer that you ran away.";
			link.l3.go = "CS_good";
		break;
		case "CS_bad":
			dialog.text = "What a bastard you are.";
			ChangeCharacterReputation(pchar, -100);
			LAi_tmpl_afraid_SetAfraidCharacter(npchar,pchar,false);
			link.l1 = "Shut up!";
			Link.l1.go = "ExitSC";
		break;
		case "CS_neutral":
			dialog.text = "Greed... I understand this feeling. Well, I'm unarmed and I can't stop you.";
			link.l1 = "You're absolutely right about that. Goodbye.";
			link.l1.go = "ExitSC";
		break;
		case "CS_good":
			dialog.text = "But you're not really a soulless creature at all, as it seemed to me at first. But you'd better keep the device. If they could track me down even in this godforsaken hole, then most likely a tracking device was somehow hung on me. It's too late to start looking for him now, so I'm unlikely to be able to escape. You, on the other hand, still have a chance.";
			ChangeCharacterReputation(pchar, 100);
			link.l1 = "This is more than what I was ready to subscribe to. But I can't refuse, there's too much at stake. I promise the corporations won't get this device.";
			link.l1.go = "CS_good_1";
		break;
		case "CS_good_1":
			dialog.text = "Just be careful when you get out of here. My sensors show that you haven't destroyed all the bots. I won't be able to disable them remotely, so you'll have to deal with them yourself.";
			link.l1 = "Yeah, goodbye.";
			link.l1.go = "ExitSC";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "ExitSC":
			LAi_LocationFightDisable(locLoad, true);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorTypeNoGroup(npchar);
			DialogExit();
		break;

		case "exit_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			//LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			//LAi_SetImmortal(npchar, false);
			//LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;

		case "OrderHunter":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			if(!CheckAttribute(pchar,"OrderHunter"))
			{
				SetQuestHeader("TheLastMass");
				if (startherotype == 2)
				{
					sTemp = "You didn't think you could kill the head of the Inquisition and get away with it so easily, did you?";
					AddQuestRecord("TheLastMass", "1");
				}
				else
				{
					sTemp = "The Inquisition has received information about your atrocities!";
					AddQuestRecord("TheLastMass", "1_1");
				}
				pchar.OrderHunter = "1";
				Link.l1 = "The Inquisitor? I advise you to go back to your hole under the church of Santiago. Come on, run while I'm kind!";
				Link.l1.go = "OrderHunterMeeting";
				if (WhisperIsHere())
				{
					Link.l1 = "...";
					Link.l1.go = "OrderHunterMeetingWhisperIsHere";
				}
			}
			else
			{
				sTemp = " ";

				Link.l1 = "Again? Okay, get ready to ascend to heaven.";
				Link.l1.go = "OrderHunterBattle";

				if(sti(PChar.OrderHunter) == 2) {AddQuestRecord("TheLastMass", "2");}

				if(sti(PChar.OrderHunter) == 3)
				{
					Link.l1 = "You know, you're not the first inquisitor to hunt me. I think you can guess what happened to the others. Tell me where your base is, and I'll let you leave alive.";
					Link.l1.go = "OrderHunterNegotiate";
				}
				if(sti(PChar.OrderHunter) > 3)
				{
					Link.l2 = "Eh, don't learn anything at all... Did someone want to die again?";
					Link.l2.go = "OrderHunterCheck";
				}
			}
			dialog.text = GetFullName(PChar) + "!"+ sTemp + "I've been stalking you for a long time, and now, finally, you're going to get the punishment you deserve.";
			if (WhisperIsHere())
			{
				dialog.text = dialog.text + "\nAre you this witch Whisper? My brothers will be glad when they find out that I have rid the church of two enemies at once!"
			}
		break;

		case "OrderHunterNegotiateWhisperIsHere":
			pchar.PrevNpc = npchar.id;
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "OrderHunterNegotiateWhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
		break;

		case "OrderHunterNegotiateWhisperIsHere_1":
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			W_RestoreOfficerDialog();
			dialog.text = "Now I'm interested. We definitely need to go to this Skeleton Reef.";
            Link.l1 = "Well, I keep my word, you can go.";
			Link.l1.go = "OrderHunterPeace";
			Link.l2 = "Thank you for the information. Don't take it personally, but I can't let you leave alive and warn you about my visit.";
			Link.l2.go = "OrderHunterBattle";
		break;

		case "OrderHunterNegotiate":
			dialog.text = "Hmm... So be it. I'm not sure what I can do, but Don Julio Iglesias will definitely beat you. Our Chapter House is located on Skeleton Reef, in the Bay of the Damned. It's a couple of days east of Cayman.";

            Link.l1 = "Isn't this a bit too desecrated a place for 'godly' church servants?";
			Link.l1.go = "OrderHunterNegotiate_1";
		break;

		case "OrderHunterNegotiate_1":
			dialog.text = "The notoriety of this reef provides protection more reliably than any walls and guns. Everyone bypasses him.";
			if (WhisperIsHere())
			{
				Link.l1.go = "OrderHunterNegotiateWhisperIsHere";
			}
			else
			{
				Link.l1 = "Well, I keep my word, you can go.";
				Link.l1.go = "OrderHunterPeace";
				Link.l2 = "Thank you for the information. Don't take it personally, but I can't let you leave alive and warn you about my visit.";
				Link.l2.go = "OrderHunterBattle";
			}

			AddQuestRecord("TheLastMass", "3");
			CaptureCapitol_SeaBattle();
			pchar.quest.CaptureCapitol_SeaBattleStarted.win_condition.l1          = "location";
			pchar.quest.CaptureCapitol_SeaBattleStarted.win_condition.l1.location = "Reefs";
			pchar.quest.CaptureCapitol_SeaBattleStarted.function             = "CaptureCapitol_SeaBattleStarted";
		break;

		case "OrderHunterMeetingWhisperIsHere":
			pchar.PrevNpc = npchar.id;
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "OrderHunterMeetingWhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
		break;

		case "OrderHunterMeetingWhisperIsHere_1":
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			W_RestoreOfficerDialog();
			dialog.text = "The Inquisition again? I'm already sick of them, if it doesn't bother you, "+pchar.name+"do me a favor and kill him.";
            Link.l1 = "Maybe we should give him a chance to come to his senses. Inquisitor, I advise you to go back to your hole under the church of Santiago. Come on, run while I'm kind!";
			Link.l1.go = "OrderHunterMeetingWhisperIsHere_2";
		break;

		case "OrderHunterMeetingWhisperIsHere_2":
			StartInstantDialog(pchar.PrevNpc, "OrderHunterMeeting", "Quest\WhisperLine\Whisper.c");
		break;

		case "OrderHunterMeeting":
			dialog.text = "Santiago is no longer our main residence in the Caribbean. Don Julio Iglesias arrived here from Europe and began the construction of a new Chapter House. And in connection with recent events, our order has received almost unlimited funding and its own military squadron.";
            Link.l1 = "Wow! How interesting... And where is your new capital?";
			Link.l1.go = "OrderHunterMeeting_1";
		break;

		case "OrderHunterMeeting_1":
			dialog.text = "In a secret place and under reliable protection.";
            Link.l1 = "The expected response. Since you're still here, I think you can't wait to go to heaven.";
			Link.l1.go = "OrderHunterBattle";
		break;

		case "OrderHunterCheck":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > rand(150))
            {
                dialog.text = "I guess I'm not ready to fight you today. The Lord has given you time to repent of your sins.";
                Link.l1 = "Well, get lost.";
                Link.l1.go = "OrderHunterPeace";
				Link.l2 = "I hope you've already repented of yours, because you don't have time left.";
				Link.l2.go = "OrderHunterBattle";
                AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            }
            else
            {
                dialog.text = "You can't intimidate me with your sinful verbiage!";
			    Link.l1 = "Then I'll shut you up with my blade.";
			    Link.l1.go = "OrderHunterBattle";
			    AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            }
		break;

		case "OrderHunterPeace":
            PChar.OrderHunter = sti(PChar.OrderHunter)+1;
			AddDialogExitQuest("GoAway_Hunters_Land");
            DialogExit();
        break;

		case "OrderHunterBattle":
			PChar.OrderHunter = sti(PChar.OrderHunter)+1;
            AddDialogExitQuest("Battle_Hunters_Land");
            DialogExit();
        break;

		case "OrderLeader":
			LAi_SetActorType(npchar);
			dialog.text = "I see you managed to ruin the lives of many of my brothers. But as the Lord said: The dead will come to life, their bodies will rise to life again, they will rise and triumph, and you who are in the dust, wake up and rejoice!";

            Link.l1 = "What the hell is this?";
			Link.l1.go = "OrderLeader_exit";
		break;

		case "OrderLeader_exit":
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			DoQuestFunctionDelay("CaptureCapitol_ShoreBattleRaiseUndead", 3.5);
			DialogExit();
		break;

		case "OrderLeader_1":
			dialog.text = "I was cornered like a wild beast. But I will not become like him and fall into fear! No! I do not despair, if I am destined to go to the Kingdom of Heaven today, so be it. But I still hope that the Lord will give me strength so that I can defeat his enemy.";

			if (WhisperIsHere())
			{
				Link.l1.go = "OrderLeaderWhisperIsHere";
			}
			else
			{
				Link.l1 = "What was that up there? I suspect that after having connections with evil spirits, it's more likely that you are the enemy of God, not me, and the road to Hell is straight for you.";
				Link.l1.go = "OrderLeader_2";
			}
		break;

		case "OrderLeaderWhisperIsHere":
			pchar.PrevNpc = npchar.id;
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "OrderLeaderWhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
		break;

		case "OrderLeaderWhisperIsHere_1":
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			W_RestoreOfficerDialog();
			dialog.text = "That's who was behind it all... A mad fanatic? To be honest, I'm a little disappointed.";
			Link.l1.go = "OrderLeaderWhisperIsHere_2";
		break;

		case "OrderLeaderWhisperIsHere_2":
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.PrevNpc, "OrderLeaderWhisperIsHere_3", "Quest\WhisperLine\Whisper.c");
		break;

		case "OrderLeaderWhisperIsHere_3":
			dialog.text = "Isn't that you, Whisper? I've heard a lot about the misadventures you've caused my brother, Antonio de Souza. I think he'd be glad to know that I finally sent you to hell, witch!";
			Link.l1 = "What was that up there? I suspect that after having connections with evil spirits, it's more likely that you are the enemy of God, not us, and your road is straight to Hell.";
			Link.l1.go = "OrderLeader_2";
		break;

		case "OrderLeader_2":
			dialog.text = "Look at the icon behind me. George the Victorious is fighting a snake. She's beautiful, isn't she? I looked at her a lot and thought, what if I didn't kill the snake, but tamed it? Just as man tames the lamb, and other creatures. And so, one day I found a way. Once these people were servants of darkness, but I managed to curb the forces of this cursed island and direct them for good. I have made them instruments in the hands of the Lord!";
            Link.l1 = "For the benefit of your perverted desires? I don't know how you did it, and I don't want to know. There were people's souls in these rotting bodies! Instead of freeing them, you left them to suffer and submit to your whims. I don't think God would like that. But now it's over, they've found peace.";
			Link.l1.go = "OrderLeader_3";
		break;

		case "OrderLeader_3":
			dialog.text = "You don't understand, it was all started for the greater good. When my efforts bear fruit, the Lord will forgive me. And the fact that the guards of the grotto are dead, it doesn't matter, you and your people will take their place!";

            Link.l1 = "That's unlikely.";
			Link.l1.go = "OrderLeader_fight";
			if (startherotype == 2)
			{
				Link.l1 = "Is that by any chance my shotgun on your belt?";
				Link.l1.go = "OrderLeader_4";
			}
		break;

		case "OrderLeader_4":
			dialog.text = "Oh, you noticed. I found this weapon among the documents in de Souza's office when I took over his post. You say this thing is yours? I must admit, I admire this mechanism, sinners fall in droves from every shot. I think you know that yourself. And soon you'll even experience it for yourself.";

            Link.l1 = "Another reason to kill you sooner!";
			Link.l1.go = "OrderLeader_fight";
		break;

		case "OrderLeader_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			CaptureCapitol_OnLeaderDeath();
			LAi_LocationFightDisable(locLoad, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "CaptureCapitol");
			for (int j=1; j<=6; j++)
			{
				sld = CharacterFromID("MaltGuard_"+j);
				LAi_group_MoveCharacter(sld, "CaptureCapitol");
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto5");
			}

			LAi_group_SetHearRadius("CaptureCapitol", 100.0);
			LAi_group_FightGroupsEx("CaptureCapitol", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
		break;

		case "CapitolCaptured":
			chrDisableReloadToLocation = false;
			pchar.quest.CaptureCapitol_Decision.win_condition.l1          = "location";
			pchar.quest.CaptureCapitol_Decision.win_condition.l1.location = "DeckWithReefs";
			pchar.quest.CaptureCapitol_Decision.function             = "CaptureCapitol_Decision";

			dialog.text = "This is a massacre, I have never seen so many corpses in my life! We did a great job on them, didn't we, Captain?";
            Link.l1 = "Yeah, you're right!";
			Link.l1.go = "CapitolCaptured_1";
		break;
		case "CapitolCaptured_1":
			dialog.text = "Well, I was defending the rear, in case they tried to surround us. Don't be angry, Captain, because I know how to please you! While I, ahem... I defended other rooms, I managed to inspect them a little. There is a whole warehouse of weapons of various types, tons of supplies, and the most interesting thing is that I found a library filled with books on military subjects. It looks like the Inquisition was going to train its own army here.";

            Link.l1 = "I wonder what can be done with all this? Sell it to someone?";
			Link.l1.go = "CapitolCaptured_2";
		break;
		case "CapitolCaptured_2":
			dialog.text = "You can sell, but you can... maybe it's stupid, but I think we could use this place to train and maintain our own army? Well, maybe not the whole army, but you could leave your officers here to gain experience.";

            Link.l1 = "You're right, it's stupid. We'll sell everything and be done with it.";
			Link.l1.go = "CapitolCaptured_3";
			Link.l2 = "You can try it. Let's have our own base, just in case.";
			Link.l2.go = "CapitolCaptured_4";
		break;
		case "CapitolCaptured_3":
			dialog.text = "Okay. Then I will quickly make a list of everything that is here, and you will look for a buyer.";

            Link.l1 = "I think the usurers will be only too happy to get a bunch of this stuff.";
			Link.l1.go = "CapitolCaptured_sell";
			Link.l2 = "Although... Let's keep this place for ourselves anyway.";
			Link.l2.go = "CapitolCaptured_4";
		break
		case "CapitolCaptured_4":
			dialog.text = "Great idea, Captain!";

            Link.l1 = "Sit here and stay in charge. Take a few people with you. You'll be a staff rat, you're no good in battle anyway.";
			Link.l1.go = "CapitolCaptured_keep";
		break;

		case "CapitolCaptured_keep":
			dialog.text = "Thank you, Captain! I won't let you down.";
            Link.l1 = "We'll see.";
			Link.l1.go = "exit";
		break;

		case "CapitolCaptured_sell":
			pchar.SellCapitol = true;
			DialogExit();
			if (CheckAttribute(pchar, "WhisperChSpokeToUsurer"))
			{
				AddQuestRecord("WhisperChinamanRelic", "4");
			}
		break;

		case "Beatrice":
			dialog.text = "You don't often see girls here. Are you also going to get a job as an officer on some ship? I would not advise you to try your luck here, the local pirates need only one thing from us, and this is not knowledge of maritime affairs at all.";
            Link.l1 = "I'll keep that in mind.";
			Link.l1.go = "exit";
			npchar.MetWhisper = true;
		break;

		case "Hugo_Lesopilka":
			dialog.text = "Pour me some more, girl.";
            Link.l1 = "I'm not your waitress!";
			Link.l1.go = "exit";
		break;

		//Реакции
		case "WhisperIsHere_exit":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
		break;

		case "BS_WhisperIsHere":
			dialog.text = "Will we have to fight Spain again? Well, I'm used to it.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_1_WhisperIsHere":
			dialog.text = "Bird? Are you talking about Maxine?";
			Link.l1 = "Yeah. I hope she's still in Port Royal.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_2_WhisperIsHere":
			dialog.text = "It looks like there's not much left of the 'Ranger'...";
			Link.l1 = "Let's go to Fort Orange. Maybe the local drunks saw what happened here.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_3_WhisperIsHere":
			dialog.text = "'Keep your friends close and your enemies even closer'. I like this Guthrie!";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_4_WhisperIsHere":
			dialog.text = "To me, Ann did the right thing. There is no need for witnesses in our case.";
			Link.l1 = "I guess you're right.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_5_WhisperIsHere":
			dialog.text = "I have a bad feeling. Be on your guard.";
			Link.l1 = "What are you talking about? It's done, we can finally relax.";
			Link.l1.go = "BS_5_WhisperIsHere_1";
		break;

		case "BS_5_WhisperIsHere_1":
			dialog.text = "Relax when one hundred and fifty million are at stake? At times like this, you need to be ready like never before!";
			Link.l1 = "Don't be so nervous. Nothing's going to happen.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_6_WhisperIsHere_1":
			dialog.text = "Oh, how bad I feel, I don't want to reproach you, but I told you to be careful. Damn, I thought you knew what you were doing, and you drank that poison too.";
			Link.l1 = "I'm sorry, it was a little unexpected, even for me. Did Flint poison us? How are the others?";
			Link.l1.go = "BS_6_WhisperIsHere_2";
		break;

		case "BS_6_WhisperIsHere_2":
			dialog.text = "I don't know any more than you do, I woke up half an hour ago.";
			Link.l1 = "Okay, let's go downstairs. Maybe someone in the tavern heard something.";
			Link.l1.go = "BS_6_WhisperIsHere_3";
		break;

		case "BS_6_WhisperIsHere_3":
			dialog.text = "Just take your time, my head is still spinning.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_7_WhisperIsHere":
			dialog.text = "Yeah, that Flint threw you a lot.";
			Link.l1 = "He dumped all of us. You, as my partner, are one of them.";
			Link.l1.go = "BS_7_WhisperIsHere_1";
		break;

		case "BS_7_WhisperIsHere_1":
			dialog.text = "You're right, and I can't wait to hit his face.";
			Link.l1 = "Me too, but only after he answers why he did it.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_8_WhisperIsHere":
			dialog.text = "Keep your head down? Aren't you afraid that they'll kill us there while Wayne is holed up?";
			Link.l1 = "You and I have been through so much. Are you afraid of some pathetic ambush?";
			Link.l1.go = "BS_8_WhisperIsHere_1";
		break;

		case "BS_8_WhisperIsHere_1":
			dialog.text = "Your truth, then lead on.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_9_WhisperIsHere":
			dialog.text = "Let's not make her angry. We didn't need to make another enemy...";
			Link.l1.go = "BS_9_WhisperIsHere_1";
		break;

		case "BS_9_WhisperIsHere_1":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			StartInstantDialogNoType("Pirates_trader", "BS_NPVK_6_1", "Quest\BlackSails\NePluyjVKolodec.c");
		break;

		case "BS_10_WhisperIsHere":
			dialog.text = "Although... It would probably be easier for us to kill her.";
			Link.l1.go = "BS_10_WhisperIsHere_1";
		break;

		case "BS_10_WhisperIsHere_1":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			StartInstantDialogNoType("Pirates_trader", "BS_NPVK_7_1", "Quest\BlackSails\NePluyjVKolodec.c");
		break;

		case "BS_11_WhisperIsHere":
			dialog.text = "This aimless running has really tired me out.";
			Link.l1 = "Me too. But I feel that Silver is somewhere nearby. Let's check out the prison again.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_12_WhisperIsHere":
			dialog.text = "That's a fight! I even got a little sweaty.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_13_WhisperIsHere":
			dialog.text = "What are you going to do with your share?";
			Link.l1 = "I don't know. I'm thinking of giving up piracy. Maybe I'll rebuild a colony or two. And you?";
			Link.l1.go = "BS_13_WhisperIsHere_1";
		break;

		case "BS_13_WhisperIsHere_1":
			dialog.text = "I want to return to my homeland. Maybe the money will help with that.";
			Link.l1 = "Is it really that expensive? Get on any passing ship as a passenger, and go ahead!";
			Link.l1.go = "BS_13_WhisperIsHere_2";
		break;

		case "BS_13_WhisperIsHere_2":
			dialog.text = "My homeland is very far away. I'm afraid the ships don't go there.";
			Link.l1 = "You're talking in riddles again. Okay, let's go already. I think Silver is done.";
			Link.l1.go = "BS_13_WhisperIsHere_3";
		break;

		case "BS_13_WhisperIsHere_3":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_SetPlayerType(pchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern", "goto", "goto2");
			BSHangover_Cutscene_2("");
		break;

		case "BS_14_WhisperIsHere_1":
			dialog.text = "Eh... It looks like our dreams won't come true.";
			Link.l1 = "It looks like it. But at least you won't leave me for your homeland yet. I have already used to you, you know.";
			Link.l1.go = "BS_14_WhisperIsHere_2";
		break;

		case "BS_14_WhisperIsHere_2":
			dialog.text = "Oh, don't make me blush.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_15_WhisperIsHere":
			dialog.text = "How long is he going to run?";
			Link.l1 = "Until he takes us to his ship, I guess.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_16_WhisperIsHere":
			dialog.text = "Here comes the ship. It looks like you were right.";
			Link.l1 = "I'm always right.";
			Link.l1.go = "BS_16_WhisperIsHere_1";
		break;

		case "BS_16_WhisperIsHere_1":
			dialog.text = "I would argue with that, but okay.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_17_WhisperIsHere":
			dialog.text = "Look, we have guests!";
			Link.l1.go = "BS_17_WhisperIsHere_1";
		break;

		case "BS_17_WhisperIsHere_1":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			StartInstantDialogNoType("Flint", "BS_PN_8_1", "Quest\BlackSails\Pogonya_Nachalas.c");
		break;

		case "BS_18_WhisperIsHere":
			dialog.text = "It looks like we got the dirtiest job.";
			Link.l1 = "Goodbye.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_19_WhisperIsHere":
			dialog.text = "Let's get out into the fresh air. I've had enough of dungeons for today.";
			Link.l1 = "Yes, let's go.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_20_WhisperIsHere":
			dialog.text = "Something is not good for me...";
			Link.l1.go = "BS_20_WhisperIsHere_1";
		break;

		case "BS_20_WhisperIsHere_1":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			SetCharacterTask_Dead(npchar);
			DoQuestFunctionDelay("BSUrka_PoisonOfficers", 1);
			DoQuestFunctionDelay("BSUrka_PoisonSelf", 3.0);
			DoQuestFunctionDelay("BSUrka_Poison_Flint", 6.0);
		break;

		// <- Реакции
	}
}
