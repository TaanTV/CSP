
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

		case "First time":							//Автор Sinistra
			dialog.text = "What a pity, what a pity. Oh, damn it!";
			link.l1 = "What are you mumbling to yourself here?";
			link.l1.go = "Nachalo_1";
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
		break;

		case "Nachalo_1":
            dialog.text = "My name is Hugo. Hugo Sawmill. I see that you are also a captain. Would you take an hour to listen to my story?";
            link.l1 = "I don't mind.";
			link.l1.go = "Slushau_1";
			link.l2 = "Well, no, actually. I'd rather spend an hour somewhere else.";
			link.l2.go = "Ya_Ustal_Ya_Uhoju";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Slushau_1":
            dialog.text = "You're a corsair, aren't you?";
			link.l1 = "Are you trying to insult me? I am free pirate!";
			link.l1.go = "Nelzya_Pomoch";
			if (sti(pchar.nation) != PIRATE)
			{
				link.l1 = "No, corsairs serve the state, and I am the free captain of my ship.";
				link.l1.go = "Nelzya_Pomoch";
			}
            if (CheckCharacterItem(Pchar, "patent_spa") || CheckCharacterItem(Pchar, "patent_fra") || CheckCharacterItem(Pchar, "patent_hol") || CheckCharacterItem(Pchar, "patent_eng"))
			{
				link.l1 = "Yes, I am a corsair.";
				link.l1.go = "Korsar_1";
			}
		break;

		case "Nelzya_Pomoch":
            dialog.text = "Ah, then you can't help me. I wish you good luck, goodbye.";
			link.l1 = "Well, yes, a fruitful conversation, nothing to say. See you later.";
			link.l1.go = "Ya_Ustal_Ya_Uhoju";
            link.l2 = "Well, you can at least tell me your story.";
			link.l2.go = "Istoria_1";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Istoria_1":
            dialog.text = "All right. Here, listen: I've become too old to lead the life of a pirate. Robbery and fighting are games for young people, you know? And I don't want to risk my skin anymore, and I want to sail calmly, without flinching at the sight of other ships. But the problem is that I have nowhere to go. Everyone wants to hang me, you know? But I came up with one thing, "+ GetSexPhrase("guy", "girl") +"\n"+
							"I'm thinking of buying myself a patent, earning some gold and bribing a couple of officials, but the damn forts open fire as soon as I approach any port, and I can't get to the governor to make him an offer. The British or the French will hang me as soon as they have me in their hands: they have orders to kill me as soon as I stick my nose out. I think I could join the Spanish service, but I can't go into their damn ports, they'll open fire on me right away!";
			link.l1 = "I'm sorry, Hugo, but there's nothing I can do to help you. I wish you good luck. Happily.";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "questTemp.PDM_NR_Pomoch"))
			{
				link.l2 = "But how can I help you?";
				link.l2.go = "Davai_Pomogu_NET";
			}
			if (!CheckAttribute(pchar, "questTemp.PDM_NR_Bratstvo"))
			{
				link.l3 = "What about the Brethren?";
				link.l3.go = "Davai_Pomogu_Bratstvo";
			}
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;

		case "Davai_Pomogu_NET":
            dialog.text = "You can't help me, "+ GetSexPhrase("guy", "girl") +". You're a pirate, aren't you? You'll get your brains blown out as soon as you get within a mile of a Spanish city.";
			if (sti(pchar.nation) != PIRATE)
			{
				dialog.text = "You can't help me, "+ GetSexPhrase("guy", "girl") +". You don't serve the Spanish governor-General, do you? Which means you don't have the right connections either.";
			}
			link.l1 = "Correct remark. See you then. And I wish you good luck.";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "questTemp.PDM_NR_Bratstvo"))
			{
				link.l3 = "What about the Brethren?";
				link.l3.go = "Davai_Pomogu_Bratstvo";
			}
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
			pchar.questTemp.PDM_NR_Pomoch = "PDM_NR_Pomoch";
			pchar.questTemp.PDM_NR_Bratstvo = "PDM_NR_Bratstvo";
		break;

		case "Davai_Pomogu_Bratstvo":
            dialog.text = "Brethren! I am not entering it, and I will never enter it! They set the rules of piracy - the rules, have you heard? Rules for pirates! I've never heard such nonsense. I'll tell you honestly, "+ GetSexPhrase("guy", "girl") +", the Brethren is just a gang of brainless cretins gathered together to get in the way of us free sailors.";
            link.l1 = "Hmm. After all, that's your opinion. Well, then I'm afraid I can't offer you anything else. See you later.";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "questTemp.PDM_NR_Pomoch"))
			{
				link.l2 = "But how can I help you?";
				link.l2.go = "Davai_Pomogu_NET";
			}
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
			pchar.questTemp.PDM_NR_Pomoch = "PDM_NR_Pomoch";
			pchar.questTemp.PDM_NR_Bratstvo = "PDM_NR_Bratstvo";
		break;

		case "Podhodim_SNOVA_Reactia":
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
			if (CheckCharacterItem(Pchar, "patent_spa"))
			{
				dialog.text = "(drinks rum)";
				link.l1 = "Hello, Hugo. I am now "+ GetSexPhrase("Spanish corsair", "Spanish corsair") +", can I help you with something?";
				link.l1.go = "Ya_Ispania_1";
			}
			else
			{
				dialog.text = "If you are not a Spanish corsair, then we have nothing to talk about with you.";
				link.l1 = "Good luck then.";
				link.l1.go = "exit";
				link.l2 = "Spaniards are my enemies - remember this!";
				link.l2.go = "Ya_Ustal_Ya_Uhoju";
			}
		break;
		
		case "Ya_Ustal_Ya_Uhoju":
			DialogExit();
            npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Korsar_1":
			if (CheckCharacterItem(Pchar, "patent_eng"))
			{
				dialog.text = "That's what I thought. And what flag are you sailing under?";
				link.l1 = "I sail under the flag of England.";
				link.l1.go = "Nelzya_Pomoch_Korsar_2";
			}
			if (CheckCharacterItem(Pchar, "patent_fra"))
			{
				dialog.text = "That's what I thought. And what flag are you sailing under?";
				link.l1 = "I sail under the flag of France.";
				link.l1.go = "Nelzya_Pomoch_Korsar_2";
			}
			if (CheckCharacterItem(Pchar, "patent_spa"))
			{
				dialog.text = "That's what I thought. And what flag are you sailing under?";
				link.l1 = "I sail under the flag of Spain.";
				link.l1.go = "Ya_Ispania_1";
			}
			if (CheckCharacterItem(Pchar, "patent_hol"))
			{
				dialog.text = "That's what I thought. And what flag are you sailing under?";
				link.l1 = "I sail under the Dutch flag.";
				link.l1.go = "Nelzya_Pomoch_Korsar_2";
			}
		break;

		case "Nelzya_Pomoch_Korsar_2":
            dialog.text = "Ah, then you can't help me. I wish you good luck, goodbye.";
			link.l1 = "Well, yes, a fruitful conversation, nothing to say. See you later.";
			link.l1.go = "Ya_Ustal_Ya_Uhoju";
            link.l2 = "Well, you can at least tell me your story.";
			link.l2.go = "Istoria_Korsar_2";
			
		break;

		case "Istoria_Korsar_2":
            dialog.text = "All right. Here, listen: I've become too old to lead the life of a pirate. Robbery and fighting are games for young people, you know? And I don't want to risk my skin anymore, and I want to sail calmly, without flinching at the sight of other ships. But the problem is that I have nowhere to go. Everyone wants to hang me, you know? But I came up with one thing, "+ GetSexPhrase("guy", "girl") +"\n"+
							"I'm thinking of buying myself a patent, earning some gold and bribing a couple of officials, but the damn forts open fire as soon as I approach any port, and I can't get to the governor to make him an offer. The British or the French will hang me as soon as they have me in their hands: they have orders to kill me as soon as I stick my nose out. I think I could join the Spanish service, but I can't go into their damn ports, they'll open fire on me right away!";
			link.l1 = "I'm sorry, Hugo, but there's nothing I can do to help you. I wish you good luck. Happily.";
			link.l1.go = "Ya_Ustal_Ya_Uhoju";
			link.l2 = "But how can I help you?";
			link.l2.go = "Davai_Pomogu_KORSAR_NET_2";
		break;

		case "Davai_Pomogu_KORSAR_NET_2":
            dialog.text = "You can't help me, "+ GetSexPhrase("guy", "girl") +". You serve the enemies of Spain, don't you? You'll get your brains blown out as soon as you get within a mile of a Spanish city.";
            link.l1 = "Correct remark. See you then. And I wish you good luck.";
			link.l1.go = "Ya_Ustal_Ya_Uhoju";
		break;

		case "Ya_Ispania_1":
            dialog.text = "Oh, so you're with the Spaniards! You really could help me!";
            link.l1 = "What happened to you?";
			link.l1.go = "Ya_Ispania_2"
		break;

		case "Ya_Ispania_2":
            dialog.text = "All right. Here, listen: I've become too old to lead the life of a pirate. Robbery and fighting are games for young people, you know? And I don't want to risk my skin anymore, and I want to sail calmly, without flinching at the sight of other ships. But the problem is that I have nowhere to go. Everyone wants to hang me, you know? But I came up with one thing, "+ GetSexPhrase("guy", "girl") +"\n"+
							"I'm thinking of buying myself a patent, earning some gold and bribing a couple of officials, but the damn forts open fire as soon as I approach any port, and I can't get to the governor to make him an offer. The British or the French will hang me as soon as they have me in their hands: they have orders to kill me as soon as I stick my nose out. I think I could join the Spanish service, but I can't go into their damn ports, they'll open fire on me right away!";
            link.l1 = "And what do I need to do?";
			link.l1.go = "Ya_Ispania_3";
		break;

		case "Ya_Ispania_3":
            dialog.text = "You are a corsair, aren't you? You can go into a Spanish port and the guns of the fort won't sink your tub, right? Then you can put in a good word for me to the Governor General in Havana, right? Just tell him that I would buy a patent for ten thousand gold, and I am ready to swear to serve him faithfully.";
            link.l1 = "I'm sorry for you, Hugo, but I don't have time for this right now. See you later.";
			link.l1.go = "Otkazal";
			link.l2 = "Actually I could do this, but to be honest, what will I get out of it?";
			link.l2.go = "Ya_Ispania_4";
		break;

		case "Otkazal":
            dialog.text = "Whatever you say, "+ GetSexPhrase("guy", "girl") +". I'll find someone else for this job.";
            link.l1 = "See you later.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Obida";
			npchar.lifeday = 0;
		break;

		case "Obida":
            dialog.text = "Ha, "+ GetSexPhrase("buddy", "girl") +", I don't play like that. You did it once "+ GetSexPhrase("refused", "refused") +"help me, and I won't give you a second chance.";
            link.l1 = "This is your problem, Grandfather. Then have a nice day.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Obida";
		break;

		case "Ya_Ispania_4":
            dialog.text = "Money, of course! I can pay you 8,000. What do you say?";
            link.l1 = "It suits me. I agree. I will bring you a Spanish letter of marque in exchange for gold.";
			link.l1.go = "Ya_Ispania_5";
			link.l2 = "You must be joking. 8,000 for such a difficult and dangerous business? That's not gonna work.";
			link.l2.go = "Otkazal";
		break;

		case "Ya_Ispania_5":
            dialog.text = "That's a good man! Fair wind to you, Captain. I can only wait for you here for a couple of months. If you don't come back by then, I'll probably be hanging from the French or English gallows by now.";
            link.l1 = "See you later.";
			link.l1.go = "Havana_Cod_1";
			NextDiag.TempNode = "Jugo_PodhodimSnova";
		break;

		case "Jugo_PodhodimSnova":
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
            dialog.text = "So, "+pchar.name+" - and where is this letter of marque that you promised to bring?";
            link.l1 = "I'm sorry, Hugo, but I don't have it yet.";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Patent") && pchar.questTemp.PDM_Novaya_Rodina.Patent == "Patent")
			{
				link.l2 = "Oh yeah, it worked! Don Francisco said he'd invite you to visit him at his residence as soon as possible, along with your ten grand, of course. And now I suppose you owe me 8,000, too?";
				link.l2.go = "Ya_Ispania_Patent_1";
			}
		break;

		case "Havana_Cod_1":
            SetQuestHeader("PDM_Novaya_Rodina");
			AddQuestRecord("PDM_Novaya_Rodina", "1");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("", "a"));
			pchar.questTemp.PDM_Novaya_Rodina.Guber = "HugoLesopilka";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Ya_Ispania_Patent_1":
            dialog.text = "This is amazing news, "+ GetSexPhrase("guy", "girl") +"! Amazing! Here is your gold, and with it, accept my gratitude. Don Francisco, did you say? I'll turn the wheel in that direction immediately!";
            link.l1 = "Goodbye, Hugo.";
			link.l1.go = "Ya_Ispania_Patent_Сod_1";
			AddMoneyToCharacter(pchar, 8001);
			TakeItemFromCharacter(pchar, "Patent_Espa_Lesopilka");
			NextDiag.TempNode = "Podhodim_SNOVA_vipemromu";
		break;

		case "Ya_Ispania_Patent_Сod_1":
			AddQuestRecord("PDM_Novaya_Rodina", "4");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("", "a"));
			PChar.quest.PDM_HugoSeaHavana.win_condition.l1 = "EnterToSea"
			Pchar.quest.PDM_HugoSeaHavana.win_condition = "PDM_HugoSeaHavana";
			pchar.questTemp.PDM_Novaya_Rodina.Guber = "Lubopitno";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Podhodim_SNOVA_vipemromu":
            dialog.text = "Ah, "+ GetSexPhrase("guy", "girl") +"! "+ GetSexPhrase("Returned", "Returned") +"again, eh? Well, I have to go to Don Francisco... Well, after I drink a couple of mugs to you and my new home, Spain!";
            link.l1 = "Thank you for your kind words, Hugo. I'll leave you to celebrate your appointment.";
			link.l1.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
			NextDiag.TempNode = "Podhodim_SNOVA_vipemromu";
		break;

		case "Novoe_Zadanie_1":
			PlayVoice("Kopcapkz\Voices\PDM\Timothy - Town Guard.wav");
            dialog.text = "Oh, it's you again, Captain "+pchar.name+"! Glad to see you!";
            link.l1 = "Oh, the old Sawmill! And how is your honest life?";
			link.l1.go = "Novoe_Zadanie_2";
		break;

		case "Novoe_Zadanie_2":
            dialog.text = "Very good, thank you. I'll tell you that the other Spanish captains were suspicious of me at first, but I showed them a couple of fighting techniques, and now we're all best friends\n"+
							"Ha! Listen, "+pchar.name+", in gratitude for what you did for me, I have a good advice for you. Come closer and listen\n"+
							"I know where you can get a good goods, a very good goods. You see, "+pchar.name+", one of my old, uh, friends, belonging to the pirates, you know... Well, he told me that an English heavy galleon full of gold and silver bars was caught in a severe storm and is now being repaired near Dominica.";
            link.l1 = "So what?";
			link.l1.go = "Novoe_Zadanie_3";
		break;

		case "Novoe_Zadanie_3":
            dialog.text = "What? What are you doing, selling turnips, "+pchar.name+"? There's a fortune in this galleon!";
            link.l1 = "Ah. I understand . And...?";
			link.l1.go = "Novoe_Zadanie_4";
		break;

		case "Novoe_Zadanie_4":
            dialog.text = "Well, the ship is anchored near Dominica - you know it for sure: a small island between Guadeloupe and Barbados. My friend said that he saw this galleon being repaired after a violent storm - its rigging was damaged, if that's what you can call its complete absence, and its hull was also damaged. He said the ship was almost unable to move. Without the shipyard, the repair seems to take some time, so he's stuck there, you could say, and is only waiting for captain to come and capture him.";
            link.l1 = "Why don't you grab it yourself?";
			link.l1.go = "Novoe_Zadanie_5";
		break;

		case "Novoe_Zadanie_5":
            dialog.text = "Oh, you think I'm luring you into a trap, huh? No, "+ GetSexPhrase("guy", "girl") +": my ship is not strong enough to capture a heavy galleon, and I am too old to change ships. I know every nail and every bar on my Felicia, and I don't want to give it up. So, "+ GetSexPhrase("guy", "girl") +", it's yours if you just want to take it!";
            link.l1 = "Hmmm. You know, I think we should go take a look at it. He's on the raid at Dominica, you say? Well, thanks for the advice, Hugo. Goodbye!";
			link.l1.go = "Novoe_Zadanie_Cod_1";
			NextDiag.TempNode = "Novoe_Zadanie_PodhodimSnova_1";
		break;

		case "Novoe_Zadanie_Cod_1":
			AddQuestRecord("PDM_Novaya_Rodina", "6");
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("", "a"));

			int Rank = sti(pchar.rank) - 3 + MOD_SKILL_ENEMY_RATE*3;
			if (Rank < 1) Rank = 1;
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Lesopilka_Galeon", "off_eng_1", "man", "man", Rank, ENGLAND, -1, true));
			FantomMakeCoolSailor(sld, SHIP_GALEON_H, "Yummy", CANNON_TYPE_CANNON_LBS32, 20, 20, 50);
			FantomMakeCoolFighter(sld, Rank, 55, 55, "blade22", "pistol2", 120);
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "EnergyPlus");
			sld.equip.blade = "blade22";
			sld.equip.gun = "pistol2";
			AddItems(sld, "bullet", 10);
			AddItems(sld, "GunPowder", 10);
			EquipCharacterByItem(Pchar, "cirass1");
			AddCharacterGoodsSimple(sld, GOOD_GOLD, 800 + rand(400));
			AddCharacterGoodsSimple(sld, GOOD_SILVER, 800 + rand(400));
			AddCharacterGoodsSimple(sld, GOOD_WEAPON, 500);
			SetShipSkill(sld, 100, 80, 80, 80, 80, 80, 80, 80, 80);
			sld.ship.Crew.Morale = 100;
			sld.ship.masts.mast4 = 1;
			sld.ship.masts.mast3 = 1;
			sld.ship.masts.mast1 = 1;
			sld.ship.HP = sti(sld.ship.HP) / 3.5;
			sld.DontRansackCaptain = true;

			Group_FindOrCreateGroup("PDM_HUGO_GAL");
			Group_SetType("PDM_HUGO_GAL", "war");
			Group_AddCharacter("PDM_HUGO_GAL", "PDM_Lesopilka_Galeon");

			Group_SetGroupCommander("PDM_HUGO_GAL", "PDM_Lesopilka_Galeon");
			Group_SetTaskAttack("PDM_HUGO_GAL", PLAYER_GROUP);
			Group_SetAddress("PDM_HUGO_GAL", "Dominica", "quest_ships", "Quest_ship_2");
			Group_LockTask("PDM_HUGO_GAL");

			SetTimerCondition("PDM_Lesopilka_Vremy", 0, 0, 30, false);

			PChar.quest.PDM_Lesopilka_SJ.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_Lesopilka_SJ.win_condition.l1.character = "PDM_Lesopilka_Galeon";
			PChar.quest.PDM_Lesopilka_SJ.win_condition = "PDM_Lesopilka_SJ";

			PChar.quest.PDM_Lesopilka_SJNashel.win_condition.l1 = "item";
			PChar.quest.PDM_Lesopilka_SJNashel.win_condition.l1.item = "PDM_SJ_Angl_Gal";
			PChar.quest.PDM_Lesopilka_SJNashel.win_condition = "PDM_Lesopilka_SJNashel";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Novoe_Zadanie_PodhodimSnova_1":
            dialog.text = "Ah! Would you like to have a drink with me, "+pchar.name+"?";
            link.l1 = "Not now, Hugo. But thanks!";
			link.l1.go = "Novoe_Zadanie_PodhodimSnova_2";
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
		break;

		case "Novoe_Zadanie_PodhodimSnova_2":
            dialog.text = "Then why are you wasting your time here, "+ GetSexPhrase("guy", "girl") +"? Go and get this galleon before it sails away!";
            link.l1 = "You're right, Hugo. I'm leaving. Goodbye!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Novoe_Zadanie_PodhodimSnova_1";
		break;

		case "Novoe_Zadanie_ZaIspaniu":
            dialog.text = LinkRandPhrase("I'm for you - into fire and water!", "For Spain!", "For our captain!");
            link.l1 = LinkRandPhrase("Keep it up, soldier!", "Well done!", "Good girl!");
			link.l1.go = "exit";
			NextDiag.TempNode = "Novoe_Zadanie_ZaIspaniu";
		break;

		case "Final_1":
            dialog.text = "Ha, "+ GetSexPhrase("guy", "girl")+", I knew you would succeed!";
            link.l1 = "Thank you, Hugo. I got all these treasures only thanks to you.";
			link.l1.go = "Final_2";
			PlayVoice("Kopcapkz\Voices\PDM\William Shakesbeer.wav");
		break;

		case "Final_2":
			dialog.text = "";
			if (sti(pchar.Money) >= 30000)
			{
				link.l1 = "And I thought that you deserve these 30000 piastres.";
				link.l1.go = "Final_3";
				link.l2 = "Okay, Hugo, I have things to do. See you later.";
				link.l2.go = "FinalPL_3";
				NextDiag.TempNode = "Final_Again";
			}
			else
			{
				link.l2 = "Okay, Hugo, I have things to do. See you later.";
				link.l2.go = "FinalPL_3";
				NextDiag.TempNode = "Final_Again";
			}
		break;

		case "Final_3":
            dialog.text = "Oh-oh! "+ GetSexPhrase("Boy", "Girl")+", you are very kind to me, of course I will take this money! Shall we go have a drink?";
            link.l1 = "Sorry Hugo, I have unfinished business, maybe another time. Adios!";
			link.l1.go = "Final_4";
			ChangeCharacterReputation(pchar, 5);
			NextDiag.TempNode = "Final_Again";
			AddMoneyToCharacter(pchar, -30000);
			AddCharacterExpToSkill(pchar, "Leadership", 70);
			AddCharacterExpToSkill(pchar, "Commerce", 70);
			AddCharacterExpToSkill(pchar, "Fortune", 70);
		break;

		case "Final_4":
			CloseQuestHeader("PDM_Novaya_Rodina");
			pchar.questdata.NovayaRodina = 1;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FinalPL_3":
			CloseQuestHeader("PDM_Novaya_Rodina");
			pchar.questdata.NovayaRodina = 1;
            sld = CharacterFromID("Hugo_Lesopilka");
			sld.lifeday = 0;
			ChangeCharacterReputation(pchar, -5);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Final_Again":
            dialog.text = "Ah! Would you like to have a drink with me, "+pchar.name+"?";
            link.l1 = "Sorry Hugo, I have unfinished business, maybe another time. Adios!";
			link.l1.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\William Shakesbeer.wav");
			NextDiag.TempNode = "Final_Again";
		break;


	}
}
