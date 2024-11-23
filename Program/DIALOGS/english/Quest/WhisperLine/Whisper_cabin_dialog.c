void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;

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
		case "Exit_Chinaman_Speak":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperChinamanSpeaks", 0.5);
			DialogExit();
		break;
		case "Exit_ChiGuard_Speak":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperChinamanCapSpeaksAgain", 0.5);
			DialogExit();
		break;
		case "Exit_portman":
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.questTemp.Whisper.Portman_Deck = true;
			DoQuestCheckDelay("TalkSelf_Quest", 1.0);
			DialogExit();
		break;

		case "First time":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "exit";

			if (npchar.id == "W_ChinamanGuard")
			{

				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "Captain, look what a 'rat' we caught in the hold.";
					Link.l1 = "Damn it, not another time traveler. Does he even understand our language?";
					Link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "You chose the wrong place for a better life. The situation here is not much better, except that women are more accessible here. Uh-uh... Of course, I didn't mean you specifically, Captain.";
					link.l1 = "Don't interfere with my interrogation.";
					link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "But Captain... Ah, okay.";
					RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
					link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 3;
					break;
				}
			}
			if (npchar.id == "W_Chinaman")
			{

				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "I understand.";
					Link.l1 = "And what's your name?";
					Link.l1.go = "ChinamanSpeak_1";
					npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "For a while, everything will go as promised. We have been sailing west for a long time, passing many countries and peoples unknown in our country.  Although the food we were provided with was monotonous, joy overwhelmed us. We will reach the land of the sands of the edge of the world, which the great admiral vaguely described, and go even further. However, some of us start to get sick, lose our teeth, even die, although the journey was not difficult. When we finally got there, the Dutch did not accept us as we expected. Our ships should be sent one at a time to a secluded bay. I suspected something was wrong and ordered the team to prepare for battle. But everything should be decided long before that. The Dutch wet our gunpowder, so our team couldn't put up a proper resistance. The Dutch will take away the ship, and make me and the crew a slave.";
					Link.l1 = "It's a harsh story. I was accepted here about the same way.";
					Link.l1.go = "ChinamanSpeak_1_1";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "Thank you Captain, I won't forget this.";
					GiveItem2Character(npchar, "blade9");
					EquipCharacterByItem(npchar, "blade9");
					LAi_SetImmortal(NPChar, false);
					Link.l1 = "I really hope so.";
					Link.l1.go = "ChinamanOff";
					npchar.quest.meting = 3;
					break;
				}
			}

			NextDiag.TempNode = "First time";
		break;

		case "Portman_Cabin":
			dialog.Text = "Have you completely lost your fear, girl? Why the hell did you attack me?";
			Link.l1 = "You know something that interests me. Coordinates of the island where the treasure is buried.";
			Link.l1.go = "Portman_Cabin_1";
		break;
		case "Portman_Cabin_1":
			dialog.Text = "A... I'm still the thief who robbed my hiding place in Bermudes. Do you still have the nerve to come straight to me? You won't learn anything from me!";
			Link.l1 = "Then I'll find everything myself as soon as I'm done with you!";
			Link.l1.go = "Portman_Cabin_fight";
		break;
		case "Portman_Cabin_fight":
			//AddQuestRecord("WhisperQuestline", "8");
			//CloseQuestHeader("WhisperQuestline");
			//SetFunctionNPCDeathCondition("Whisper_Portman_Cabin_Is_Dead", npchar.id, false);
			pchar.questTemp.Whisper.KilledPortman = true;
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			//AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "Portman":
			dialog.Text = "Greetings, beautiful stranger.";
			Link.l1 = "Hello, Captain.";
			Link.l1.go = "Portman_1";

			if (CheckAttribute(pchar, "Whisper.BetrayChard"))
			{
				dialog.Text = "Well, did this brazen pirate get the punishment he deserved?";
				Link.l1 = "Not yet.";
				Link.l1.go = "exit";
				if (CheckCharacterItem(pchar, "Bible"))
				{
					Link.l1 = "Of course. Here's your bible.";
					Link.l1.go = "Portman_betray_chard_1";
					pchar.Whisper.GotPortmanAx = true;
				}
			}
		break;
		case "Portman_1":
			NextDiag.TempNode = "Portman_3";
			dialog.Text = "What are you doing on board my ship?";
			//Link.l1 = "I want to ask, is it possible to search your cabin? The fact is that my brother served with you and recently signed off on shore, but forgot some documents.";
			//Link.l1.go = "Portman_enemy";
			Link.l1 = "I want to warn you that your hiding place in Bermudes was found and robbed by a pirate. This man is hunting for your other treasures, if you have any.";
			Link.l1.go = "Portman_ally";
			Link.l2 = "Just looking around. I'm thinking of buying a similar ship.";
			Link.l2.go = "Portman_2";
		break;
		case "Portman_2":
			dialog.Text = "In that case, I won't bother you. But please don't stay too long, it's time for us to sail soon.";
			Link.l1 = "Okay.";
			Link.l1.go = "exit_portman";
		break;
		case "Portman_3":
			dialog.Text = "Please don't stay too long, we will sail soon!";
			Link.l1 = "Okay...";
			Link.l1.go = "exit";
		break;
		case "Portman_ally":
			dialog.Text = "I am aware of this. But you didn't know the name of the robber, who is it?";
			Link.l1 = "The adventurer's name is Michael Chard. This fool sent me to get information about your hiding places.";
			Link.l1.go = "Portman_ally_1";
		break;
		case "Portman_ally_1":
			dialog.Text = "I've never heard of such a name. Well, it doesn't matter. If it's really him, he probably has my bible. Kill this Chard and bring her back.";
			Link.l1 = "And what will be the reward for the help?";
			Link.l1.go = "Portman_ally_2";
		break;
		case "Portman_ally_2":
			AddQuestRecord("WhisperChardQuest", "4");
			pchar.Whisper.BetrayChard = true;
			NextDiag.TempNode = "Portman_betray_chard";
			dialog.Text = "I won't hurt you with this, believe me. All right, go ahead. When you do the job, I think you can find me without any problems, since you've already done it once.";
			Link.l1 = "Agreed.";
			Link.l1.go = "exit";
		break;
		case "Portman_betray_chard":
			dialog.Text = "Well, did this brazen pirate get the punishment he deserved?";
			Link.l1 = "Not yet.";
			Link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "Bible"))
			{
				Link.l1 = "yeah. Here's your bible.";
				Link.l1.go = "Portman_betray_chard_1";
				pchar.Whisper.GotPortmanAx = true;
			}
		break;
		case "Portman_betray_chard_1":
			AddQuestRecord("WhisperChardQuest", "5");
			CloseQuestHeader("WhisperChardQuest");
			pchar.Whisper.PortmanAtSea = true;//Отключаем подсказки по поиску Портмана - квест закрыт
			TakeItemFromCharacter(pchar, "Bible");
			Log_Info("You have received the Imperial axe");
			GiveItem2Character(pchar, "topor_emperor");
			PlaySound("interface\important_item.wav");
			dialog.Text = "Great! Now I can sleep peacefully without fear that this carrion will rob me again. I told you that I would not offend with a reward. Here, take this axe. Don't ask me where I got it from, there aren't any more like it. If you don't like it, you can sell it. I'm sure this thing is worth a lot of money.";
			Link.l1 = "Wow! Thank you.";
			Link.l1.go = "exit";
		break;

		case "WarDogCap":
			dialog.Text = "You again? I thought you had long since disappeared within the walls of the Inquisition.";
			Link.l1 = "You can't get rid of me that easily.";
			Link.l1.go = "WarDogCap_1";
		break;
		case "WarDogCap_1":
			dialog.Text = "How did you even find me?";
			Link.l1 = "Your inquisitor friend, Antonio de Souza, set this trap himself. Your recent actions have angered the Spanish crown very much, de Souza wanted to catch you here personally, but I politely asked you to do this honor to me.";
			Link.l1.go = "WarDogCap_2";
		break;
		case "WarDogCap_2":
			dialog.Text = "What the hell do you want from me?";
			Link.l1 = "You have something of mine.";
			Link.l1.go = "WarDogCap_2_1";
		break;
		case "WarDogCap_2_1":
			dialog.Text = "You mean your costume? I can give it to you if you let me go.";
			Link.l1 = "Not just the suit, all my gear, including the device I used to teleport here.";
			Link.l1.go = "WarDogCap_3";
		break;
		case "WarDogCap_3":
			dialog.Text = "What? Oh, you mean that useless piece of hardware? That's how I got rid of it, along with the rest of the junk. Only the suit is left.";
			Link.l1 = "What did you do, stupid?! What do you mean, got rid of it?";
			Link.l1.go = "WarDogCap_4";
		break;
		case "WarDogCap_4":
			dialog.Text = "That you won't see him again. And I'm not going to let a woman talk to me like that!";
			Link.l1 = "I'll bury you, you bastard!";
			Link.l1.go = "WarDogCap_fight";
		break;
		case "WarDogCap_fight":
			AddQuestRecord("WhisperQuestline", "8");
			CloseQuestHeader("WhisperQuestline");

			UnlockAchievement("WhisperLine", 3);

			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			pchar.Whisper.NanoCostume = true;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "DeSouza":
			dialog.Text = "Wow, what a surprise. I've been looking for you everywhere, Whisper.";
			Link.l1 = "I'm tired of waiting for you to find me, so I came to you myself.";
			Link.l1.go = "DeSouza_1";
		break;
		case "DeSouza_1":
			dialog.Text = "Brave, but stupid. Do you have any idea what I'm going to do to you now?";
			Link.l1 = "I doubt you have the strength for this, you can barely stand on your feet. I can offer you a break. Let's talk a little bit.";
			Link.l1.go = "DeSouza_2";
		break;
		case "DeSouza_2":
			dialog.Text = "And what do you want to talk about?";
			Link.l1 = "I came here with a time machine. This is an atypical-looking device, you would definitely remember it. Did Hernan Esteban give you something like that?";
			Link.l1.go = "DeSouza_2_1";
		break;
		case "DeSouza_2_1":
			dialog.Text = "Yes, he showed me something like that the day he brought you in. I asked him to quickly remove this diabolical object from his eyes, and then bury it at the bottom of the sea. I don't really know if he listened to me or not.";
			Link.l1 = "I really hope not. Do you know where Esteban can be found?";
			Link.l1.go = "DeSouza_3";
		break;
		case "DeSouza_3":
			dialog.Text = "If only! I want to know that too. Until recently, he was an exemplary privateer, but recently he began to do things that were unacceptable for a servant of Spain. I can't imagine what kind of fly bit him, but he stopped appearing at the Governor-General's, and his ship, according to rumors, was seen robbing other ships of Spain. This is unacceptable, so the Governor-General asked me to find him personally and punish him. That's what I'm doing now, and at the same time I'm catching other enemies of the crown, like you.";
			Link.l1 = "So there's absolutely no clue where he might be?";
			Link.l1.go = "DeSouza_4";
		break;
		case "DeSouza_4":
			dialog.Text = "There is one, but before I name it, let me ask you a question. Are you really from the future?";
			Link.l1 = "Yes.";
			Link.l1.go = "DeSouza_5";
		break;
		case "DeSouza_5":
			dialog.Text = "God, now I see you're not lying. Tell me, does anyone remember me and my order in the future?";
			Link.l1 = "In the future, people will try to forget about your crazy order. If they do, it is only in a negative way, as a hotbed of cruelty and ignorance. All you have achieved is a lot of deaths and ruined lives.";
			Link.l1.go = "DeSouza_6";
		break;
		case "DeSouza_6":
			dialog.Text = "For such words, I like you, nevertheless, there is some truth in this. Trying to fulfill the will of the Lord, I have sinned a lot. However, I do not think that I did wrong, sometimes sin is a necessary measure to bring goodness to the devil of people! Only the Lord can judge me!";
			Link.l1 = "I've satisfied your curiosity. It's your turn.";
			Link.l1.go = "DeSouza_7";
		break;
		case "DeSouza_7":
			AddQuestRecord("WhisperQuestline", "7");
			AddQuestUserData("WhisperQuestline", "sWhCapName", GetFullName(characterFromId("wl_Pirate_Cap")));
			SetTimerCondition("Whisper_WarDog", 0, 0, 7, false);
			dialog.Text = "I paid a bordello girl who is often visited by " + GetFullName(characterFromId("wl_Pirate_Cap"))+", so that she would put one rumor in his ear, allegedly there is a treasure hidden in the bay on Turks. He's a greedy man, he probably has to bite. According to my rough calculations, if everything worked out, he should show up there in a week.";
			Link.l1 = "An insidious and cruel plan, just in the style of the Inquisition.";
			Link.l1.go = "DeSouza_8";
		break;
		case "DeSouza_8":
			dialog.Text = "Let the Lord decide which of the two of us is destined to intercept him, and who will go to the judgment of God today.";
			Link.l1 = "Amen.";
			Link.l1.go = "DeSouza_fight";
		break;
		case "DeSouza_fight":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			pchar.Whisper.DeSouzaTalked = true;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "ChinamanSpeak_1":
			dialog.Text = "Long Wei.";
			Link.l1 = "I see you're a little far from home. You're from Japan, aren't you? You know, I once had a Japanese sword...";
			Link.l1.go = "ChinamanSpeak_2";
		break;
		case "ChinamanSpeak_2":
			dialog.Text = "I come here from China, Shandong Province.";
			Link.l1 = "I see. And for what reason, instead of being in your China, you ended up on my ship?";
			Link.l1.go = "ChinamanSpeak_3";
		break;
		case "ChinamanSpeak_3":
			dialog.Text = "It's a long story. The homeland is at war all year round. The Emperor is constantly arranging conscription into the army. Many men die without knowing a woman to serve under Admiral Jiang Yin, who manages what remains of the once great Zheng He flotilla, which made seven great sea voyages two centuries ago. To order me to be captain of the junk, the admiral called together trusted officers and captains, including me, and offered to leave the service. To go not to pirates, but to the Dutch, a nation of seafarers like us, like Zheng He. The admiral says they appreciate good sailors. Many agreed to go, the dissenters died. After that, we'll head here to the Caribbean in search of a better life.";
			Link.l1 = "...";
			Link.l1.go = "Exit_ChiGuard_Speak";
		break;
		case "ChinamanSpeak_1_1":
			dialog.Text = "I was resold many times, until one day I was sent to serve these evil people that you meet on the shore. They beat me and make me carry heavy things. I'm hiding from them in the hold of this ship.";
			Link.l1 = "Yeah, it's all clear to me now. So you're a runaway slave.";
			Link.l1.go = "ChinamanSpeak_1_2";
		break;
		case "ChinamanSpeak_1_2":
			dialog.Text = "It turns out that it is.";
			Link.l1 = "I was hooked by your story. I can offer you a place in the team. You say you were a captain? I could use someone with your experience, since I'm new to this craft myself.";
			Link.l1.go = "ChinamanSpeak_1_3";
			Link.l2 = "Then your place is among the other slaves. Juan, take him to the hold.";
			Link.l2.go = "ChinamanSlave";
		break;
		case "ChinamanSpeak_1_3":
			dialog.Text = "I can help steer the ship, and also, I can wield a sword, I can be a bodyguard.";
			Link.l1 = "In that case, Juan, give him your blade. Then you'll find another one.";
			Link.l1.go = "Exit_ChiGuard_Speak";
		break;
		case "ChinamanSlave":
			DialogExit();
			ChangeCharacterReputation(pchar, -30);
			AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			npchar.lifeday = 0;
			sld = characterFromID("W_ChinamanGuard");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 7);
			sld.lifeday = 0;

			PlayVoice("interface\"+LanguageGetLanguage()+"_EvEnemy1.wav");
			pchar.questTemp.Whisper.SmugPatrol = true;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
		break;
		case "ChinamanOff":
			DialogExit();
			NPChar.Payment = true;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.greeting = "GR_longway";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.HalfImmortal = true;  // Контузия
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			LAi_SetWarriorType(NPChar);
			SetSelfSkill(NPChar, 25, 25, 25, 25, 25);
			SetShipSkill(NPChar, 15, 15, 20, 20, 40, 15, 15, 15, 15);
			SetSPECIAL(sld, 5, 5, 9, 4, 9, 9, 9);
			NPChar.rank = 6;
			LAi_SetHP(npchar, 120.0, 120.0);
			SetCharacterPerk(NPChar, "ByWorker");
			SetCharacterPerk(NPChar, "ShipSpeedUp");
			SetCharacterPerk(NPChar, "ShipTurnRateUp");
			SetCharacterPerk(NPChar, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней

			sld = characterFromID("W_ChinamanGuard");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 7);
			sld.lifeday = 0;
			PlayVoice("interface\"+LanguageGetLanguage()+"_EvShip3.wav");
			pchar.questTemp.Whisper.SmugPatrol = true;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
		break;

		//Реакции
		case "WhisperIsHere_exit":
			DialogExit();
			RestoreOldDialog(npchar);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_SetPlayerType(pchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
		break;

		case "BS_21_WhisperIsHere":
			dialog.text = "";
			Link.l1 = "You're just in time! I don't know what I'm thinking about when I climb into the cabins to fight captains alone.";
			Link.l1.go = "BS_21_WhisperIsHere_1";
		break;

		case "BS_21_WhisperIsHere_1":
			Pchar.CabinHelp = false;
			dialog.text = "If you want, I will always storm the cabins with you.";
			Link.l1 = "Yes, it would be nice.";
			Link.l1.go = "BS_21_WhisperIsHere_2";
			Link.l2 = "Perhaps it's unnecessary.";
			Link.l2.go = "WhisperIsHere_exit";
		break;

		case "BS_21_WhisperIsHere_2":
			Pchar.CabinHelp = true;
			dialog.text = "Agreed.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
	}
}
