void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "exit":
			LAi_SetCitizenTypeNoGroup(npchar);
			//#20200315-01
            npchar.chr_ai.type.checkFight = 999999.0;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Captain", "Girl") +"! Be merciful, protect me! Please!", "Help! "+ GetSexPhrase("Stranger", "Girl") +"Save me, I beg you!");
			link.l1 = LinkRandPhrase("What happened?", "What's wrong?",RandPhraseSimple("What's the matter?", "What's going on?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Captain! Captain", "Girl! Girl") +", wait!", "Wait, "+ GetSexPhrase("captain", "girl") +"! Please.");
			link.l1 = LinkRandPhrase("What happened?", "What's wrong?",RandPhraseSimple("What's the matter?", "What's going on?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Ah, stranger! Help the poor girl, please! These people are plotting something evil!";
			link.l1 = LinkRandPhrase("What happened?", "What's wrong?",RandPhraseSimple("What's the matter?", "What's going on?"));
			link.l1.go = "Begin_31";
		break;

		case "Begin_11":
			dialog.text = RandPhraseSimple("These scoundrels want to abuse me! For God's sake, don't let them do this!", "For Christ's sake, protect me from these monsters! They want to dishonor me!");
			link.l1 = "Don't panic"+ GetSexPhrase(", beauty", "") +". We'll figure it out now.";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("Rapists are chasing me!"+ GetSexPhrase("Could you stand up for the lady's honor?", "") +"", "Captain, "+ GetSexPhrase("be a man", "you're brave woman") +" - save the girl from dishonor!");
			link.l1 = "Don't panic"+ GetSexPhrase(", beauty", "") +". We'll figure it out now.";
			link.l1.go = "exit_1";
		break;

		case "Begin_31":
			dialog.text = "I'm being chased... Bandits are chasing me! Tell them to leave me alone!";
			link.l1 = "Don't panic"+ GetSexPhrase(", beauty", "") +". We'll figure it out now.";
			link.l1.go = "exit_1";
		break;

		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("Help! Help! These people are following me! Save me!",
				"Ah! To help, "+ GetSexPhrase("stranger", "girl") +"! Save me from these scoundrels!",
				"Be merciful, protect me from these scoundrels! Please!");
			Link.l1 = LinkRandPhrase("What's going on?", "What's the matter?", "What happened?");


			Link.l1.go = "Node_2";
		break;

		case "Node_2":
			dialog.text = LinkRandPhrase("They... They want to abuse me! I beg you, don't let them do this! Save me!",
				"These beasts... they want to do something terrible... Protect me from them, please!",
				"In the name of our Lord, protect me from these lustful monsters! They want to dishonor me!");
			Link.l1 = "Okay, let's figure it out now.";
			Link.l1.go = "exit_1";
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("Thank you, "+ GetSexPhrase("captain", "girl") +". I was so scared!", "Thank you for saving me! I am so grateful to you!");
					link.l1 = "That's it, "+ GetSexPhrase("beauty", "darling") +"calm down - it's all over now.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "Ah, thank you, "+ GetSexPhrase("noble man! You are a real gentleman!", "girl! You saved me!") +"";
					link.l1 = "I couldn't do otherwise.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "Ah, thank you, "+ GetSexPhrase("noble man! You are a real gentleman!", "stranger! You saved me!") +"";
					link.l1 = "I couldn't do otherwise.";
					link.l1.go = "Node_12";
				}
				else
				{
					dialog.text = "What have you done?! Why did you kill them?! Now they'll be looking for me! My God, why am I being punished like this?!";
					link.l1 = "That's a thank you!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "Well, what have you done, "+ GetSexPhrase("captain", "girl") +"?! Why did you kill them?! They were really sent by my father!.. God! he'll just kill me...";
				link.l1 = "Gee! And what were you thinking when you shouted that bandits were chasing you?!";
				link.l1.go = "Node_31";
			}
		break;

		case "Node_11":
			Diag.TempNode = "ThanksAgain";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "I have some money with me, do not disdain - take it as a token of gratitude. I'm going to tell everyone now, "+ GetSexPhrase("what a noble and brave man you are", "what a noble and brave woman you are") +".";
			link.l1 = "Okay, okay, tell me. Thank you... Now go home.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;

		case "Node_12":
			dialog.text = "I still can't get over it. Do not spend "+ GetSexPhrase("lady", "me") +"before settlement " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? Because now I see rapists behind every bush.";
			link.l1 = RandPhraseSimple("Don't worry so much... All right, let's go.", "Why are you such a coward? Come on, I'll see you off.");
			link.l1.go = "Node_121Next";
			link.l2 = "Sorry, honey, I don't have time - things are waiting for me.";
			link.l2.go = "Node_3End";
		break;

		case "Node_22":
			dialog.text = "I thought you'd just scare them!.. You must take me to the settlement tavern " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "I have no one else to ask for help.";
			link.l1 = "Oh, shit! Let's go. Just keep up.";
			link.l1.go = "Node_122Next";
			link.l2 = "Oh no, "+ GetSexPhrase("beauty", "darling") +"! There are enough surprises for today. Look for another assistant.";
			link.l2.go = "Node_3End";
		break;

		case "Node_31":
			dialog.text = "What was I supposed to do?! My father wants to marry me off to the son of a usurer- that slobber... Because his dad has a lot of piastres in his trunks. And I love someone else! Take me to him, please.";
			link.l1 = "That's imposed on my head! Come on, where are you going now? And what is the name of your chosen one, where should I lead you?";
			link.l1.go = "Node_32";
			link.l2 = "Oh no, "+ GetSexPhrase("beauty", "darling") +"! There are enough surprises for today. Look for another assistant.";
			link.l2.go = "Node_3End";
		break;

		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "His name is " + pchar.GenQuest.EncGirl.sLoverId + ", he is a visitor. Now he lives in the settlement " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", I was looking for a job there, but we're having a hard time with it. Everyone says it's a crisis... And I don't have to go home now anyway.";
			link.l1 = "Crisis, you say? Well, well... For a real pirate, a crisis is when there is a caravan on the horizon and the sky is completely calm...";
			link.l1.go = "Node_12Next";
		break;

		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeathSimple.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathSimple.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathSimple.function = "EncGirl_DeathSimple";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeathSimple.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathSimple.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathSimple.function = "EncGirl_DeathSimple";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("Do you know "+ GetSexPhrase("captain", "girl") +"? And I was so scared that my knees are still shaking.", "Oh, I've been through a lot of fear. It's good that God sent you in time.");
			link.l1 = RandPhraseSimple("Thank God you're safe.", "Don't take it personally. It's good that everything turned out that way.");
			link.l1.go = "exit";
		break;

		case "Node_1Next": //не исользуется эта ветка... а ведёт к кладам и жемчугу
			dialog.text = RandPhraseSimple("Thank you, "+ GetSexPhrase("captain", "girl") +", once again. I don't know how to thank you.", "Thank you very much, "+ GetSexPhrase("captain", "girl") +". I can't even imagine what I would have done if you hadn't arrived in time.");
			link.l1 = RandPhraseSimple("From now on, you will have science. Well, have a nice stay...", "You'll be more careful next time... Well, go home, things are waiting for me.");
			link.l1.go = "Node_1End";
			link.l2 = "Is it possible to be so careless? Why are you alone in the jungle?";
			link.l2.go = "Node_13";
		break;

		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterReputation(pchar, -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("Have you changed your mind?", "Captain, it's good that you changed your mind!");
			link.l1 = RandPhraseSimple("No, no, dear, without me.", "Don't even hope...");
			link.l1.go = "exit";
		break;

		case "Node_13":
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "You'll probably laugh... I was collecting a love potion... One witch said that there is a root that helps in love affairs.";
						link.l1 = "My God! What "+ GetSexPhrase("these women think", "you only thought") +"?! You must have scored a lot, that a whole pack of suitors followed you - they could hardly beat off. Ha ha ha ha... Well, be healthy.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "I just decided to take a walk, I breathed air, I collected herbs... Yes, it must have come out at a bad hour.";
						link.l1 = "What kind of frivolity is this?! Thank God it turned out that way... Well, have a nice day.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "My mistress scattered a pearl necklace somewhere here when she was walking. When she came home, she screamed, and sent me to look for her. He says, 'Don't come home until you collect the pearls.'.. And I don't even really know the place. And how can you find them - tiny pearls in such grass? Now I'm wandering around -I don't know what to do.";
					link.l1 = "What kind of necklace? Maybe it will be cheaper to buy a new one than to wander around the jungle I don't know where? Was there a lot of pearls in it?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "I got the map from my late father, but his friends wanted to take it away. While my father was alive, everyone trembled in front of him, but as soon as I buried him, there was no life at all. At first they tried to redeem the map, and when it refused, they began to threaten. ";
					link.l1 = "What didn't you sell? What is it about this map that pirates are scouring for it in whole gangs?";
					link.l1.go = "Node_132";
				break;
			}
		break;

		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "There were selected pearls there. You can't buy that cheap. It had " + sti(pchar.GenQuest.EncGirl.BigCoins) + " large pearls and " + sti(pchar.GenQuest.EncGirl.SmallCoins) + " small ones. If such pearls could be picked up, then it would be possible to make a similar necklace to order.";
			link.l1 = "Yes, your mistress has set a difficult task... Well, look for it, since it's assigned. Have a nice stay.";
			link.l1.go = "Node_131End";
			link.l2 = "Your occupation is useless... Looking for pearls in such grass is like looking for a needle in a haystack. Moreover, you don't know the exact location...";
			link.l2.go = "Node_133";
		break;

		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterReputation(pchar, -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "The father marked the place on it where he hid his treasures. You haven't heard of the famous pirate " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_VOC) + "?";
			link.l1 = "No, I haven't heard anything.";
			link.l1.go = "Node_132_1";
		break;

		case "Node_132_1":
			dialog.text = "So that's it " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM) + " and there was my father. Everyone was afraid of him, no one even dared to make a sound. Now, of course, they are insolent. When I refused to sell the map, they said that their share in this treasure was also there. I wanted to hide the map, but they tracked me down...";
			link.l1 = "So why hide it? Hire a ship and go get your treasures. Did your parent hide them for nothing?";
			link.l1.go = "Node_132_2";
		break;

		case "Node_132_2":
			dialog.text = "Easy to say. I don't have money for a boat, and I'm afraid... How I'm going to dig it all out, drag it... And take it where? Anyone will rob me on the way, and even take my life...";
			link.l1 = "Yes, that's right... Well, go hide your map. Just don't forget the place later.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "Hmm, that's right. So, moreover, it was necessary to sell.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "Have you tried to find a travel companion?";
			link.l3.go = "Node_132_8";
		break;

		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_132_3":
			dialog.text = "Sorry... My father told me how much he hid there. Who's going to pay me that much?";
			link.l1 = "Look, don't get cheap. Any gold is not worth laying down your head for. And you don't have any worries - you took the money and went with a smile...";
			link.l1.go = "Node_132_4";
		break;

		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "Tempting of course... And how much are you willing to give for it?";
			link.l1 = "I don't think it can cost more than " + sti(pchar.GenQuest.EncGirl.mapPrice) + " piastres.";
			link.l1.go = "Node_132_5";
		break;

		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "Oh, the female share... I agree. I'll finally get rid of this nightmare... It's better that you get this map"+ GetSexPhrase(" - to the noble gentleman", "") +"than some crooks.";
				link.l1 = "That's great. Keep the money, just don't spend it all at once.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "No, "+ GetSexPhrase("captain", "girl") +". I'm not going to sell it. When I get married, my husband and I will take out the treasure...";
				link.l1 = "Well, it's up to you. No one else will pay for your piece of paper anyway.";
				link.l1.go = "Node_132_2End";
			}
		break;

		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice)));
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_132_8":
			dialog.text = "Where will you find them? There is no hope for the young - they immediately climb up their skirts, they don't even need treasures. And I'm afraid of the old ones, they remind me of my father's friends, they're all so cunning - you don't know what to expect from them.";
			link.l1 = "Ha ha ha... Will you go with me to get the treasure?";
			link.l1.go = "Node_132_9";
		break;

		case "Node_132_9":
			dialog.text = "With you?! Can I? Only then you will bring me back here to the settlement " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "Okay?!";
			link.l1 = "Let's go if you tell me where.";
			link.l1.go = "Node_132_10";
		break;

		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "The treasure is hidden in a cave on " + XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Voc") + ". We need to land in " + XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen") + " and I'll show you the place myself... Only, we'll split it in half!";
			link.l1 = "Okay, okay, I won't hurt you. Follow me and keep up.";
			link.l1.go = "Node_132_11";
		break;

		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_132_11_1":
			dialog.text = "Captain, now we have to find the cave.";
			link.l1 = "Well, let's look.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;

		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "Captain, we have to find the cave.";
			link.l1 = "Well, let's look.";
			link.l1.go = "exit";
		break;

		case "Node_132_12":
			dialog.text = "Here. I found him!.. As my father used to say, there's a whole bunch of jewelry here! Your half is as agreed.";
			link.l1 = "You see how simple it turned out to be? And you were afraid.";
			link.l1.go = "Node_132_13";
		break;

		case "Node_132_13":
			dialog.text = "Ha ha ha!.. I'm rich now! Will you take your share now?";
			link.l1 = "Perhaps.";
			link.l1.go = "Node_132_15";
		break;

		case "Node_132_15":
			dialog.text = "Then hold and help me carry the treasure to the ship. Have you forgotten that you promised to take me home?";
			link.l1 = "I didn't forget. I will definitely take you.";
			link.l1.go = "Node_132_16";
		break;

		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("You got your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+drand(1));
			TakeNItems(pchar, "chest", 2+drand(6));
			TakeNItems(pchar, "jewelry1", 30+drand(15));
			TakeNItems(pchar, "jewelry2", 30+drand(15));
			TakeNItems(pchar, "jewelry3", 30+drand(15));
			TakeNItems(pchar, "jewelry11", 30+drand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry15", 10+rand(10));
			TakeNItems(pchar, "jewelry18", 20+rand(10));
			TakeNItems(pchar, "jewelry14", 30+rand(10));
			TakeNItems(pchar, "jewelry7", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;

		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "It's great to be rich! I feel like a different person.";
			link.l1 = "I'm happy for you.";
			link.l1.go = "exit";
		break;

		case "Node_132_18":
			dialog.text = "That's it, Captain. My journey is over. Thank you for your help.";
			link.l1 = "Please... What are you thinking of doing with your wealth? You'll probably buy a plantation, get slaves...";
			link.l1.go = "Node_132_19";
		break;

		case "Node_132_19":
			dialog.text = "I don't know, I haven't decided yet... Maybe I'll go to Europe...";
			link.l1 = "Well, have a nice stay.";
			link.l1.go = "Node_132_20";
		break;

		case "Node_132_20":
			dialog.text = "Wait... There was this little thing in my father's treasure. I don't need it, but you might need it. Take it as a gift for what you have done for me... It's out of my share, ha ha ha...";
			link.l1 = "Wow, what a gift. Thank you"+ GetSexPhrase(", beauty", "") +". A good groom for you...";
			link.l1.go = "Node_132_21";
		break;

		case "Node_132_21":
			chrDisableReloadToLocation = false;
			RemovePassenger(pchar, npchar);
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_133":
			dialog.text = "But what should I do? I can't disobey the hostess! She'll skin me three times.";
			link.l1 = "Wait for me at the church in " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", I'll bring you pearls for a necklace.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "Here, take 15,000 piastres, for this money you can, if not buy a whole necklace, then the pearls to pick up - for sure.";
				link.l2.go = "Node_135";
			}
		break;

		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";
			Diag.TempNode = "Node_134";
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins));
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins));
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_134":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("captain", "girl") +"How glad I am to see you again! Did you manage to collect the pearls for the necklace?", "Hello, Captain! Well, have you brought the pearls? The hostess is very nervous.");
			if (GetCharacterItem(pchar, "jewelry11") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry12") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "Yes. Keep your pearls. Give them to the hostess and give them to her, let her choose the place next time before scattering the necklace.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "Not yet. It turned out to be not so easy... Wait, I will definitely bring it.";
				link.l1.go = "Node_134_2";
			}
		break;

		case "Node_134_1":
			TakeNItems(pchar, "jewelry11", -sti(pchar.GenQuest.EncGirl.BigCoins));
			TakeNItems(pchar, "jewelry12", -sti(pchar.GenQuest.EncGirl.SmallCoins));
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Ah, "+ GetSexPhrase("captain", "girl") +"How happy I am to have met you! As a token of gratitude for all that you have done for me, I want to give you one thing and these stones. I hope you will find all this very useful.";
			link.l1 = "Wow! Thank you too"+ GetSexPhrase(", beauty", "") +", I did not expect that... Goodbye, and be happy.";
			link.l1.go = "Node_134_End";
		break;

		case "Node_134_2":
			dialog.text = "Ah, "+ GetSexPhrase("captain", "girl") +", I really hope for you.";
			link.l1 = "And you're doing the right thing...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;

		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			TakeNItems(pchar, "jewelry1", 15+drand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterReputation(pchar, 10);
			dialog.text = "Ah, "+ GetSexPhrase("captain", "girl") +", this is the second time you've helped me out today. Thank you very much. I will never forget your kindness.";
			link.l1 = "Please. Give my regards to the hostess...";
			link.l1.go = "Node_135End";
		break;

		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse"))
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}
				else
				{
					iRnd = 1;
				}
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("You shouldn't have given them the money. They're lying.", "Don't believe them. They all lie... They also gave me the money.");
					link.l1 = "Should I have killed them?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "Oh, what a noble act! You can immediately see "+ GetSexPhrase("a real gentleman", "a noble lady") +"! Please accept my sincere thanks... I hope you didn't believe what those crooks were saying?";
					link.l1 = "It doesn't matter. A girl with a crowd of hungry people in the jungle is quite natural...";
					link.l1.go = "Node_210";
					link.l2 = "Well, what are you, "+ GetSexPhrase("beauty", "darling") +"? How can I?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "Thank you, Captain. I'm sorry for getting involved in such an unpleasant story, but I had no other choice.";
					link.l1 = "Yes, I see you're in a lot of trouble yourself. How did that happen to you?";
					link.l1.go = "Node_220";
				break;
			}
		break;

		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "Maybe so... They won't leave me alone anyway.";
				link.l1 = "Uh, go home, you have nothing to be afraid of anymore.";
				link.l1.go = "Node_200End";
				link.l2 = "Wow! Why do you dislike men so much?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "No, of course not! But they won't let up anyway. Take me to the settlement " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "please.";
				link.l1 = "Go home, they won't touch you anymore. They're going to the tavern now to spend their free money.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("Don't worry so much... All right, let's go.", "Why are you such a coward? Come on, I'll see you off.");
				link.l2.go = "Node_121Next";
			}
		break;

		case "Node_201":
			dialog.text = "No, what are you? It's just that I know these scoundrels well. These are my father's former friends. They're tracking down the place where Father hid the jewels.";
			link.l1 = "What about the father?";
			link.l1.go = "Node_202";
		break;

		case "Node_202":
			dialog.text = "He was captain of a pirate ship. He died recently... They were all so polite at the funeral, but as time passed, they forgot about their father and their conscience... It's good that I noticed them. As soon as they find out where the treasure is, I won't live anymore...";
			link.l1 = "Yes, it's a sad story. And what are you going to do, hide from them?";
			link.l1.go = "Node_203";
		break;

		case "Node_203":
			dialog.text = "I can't keep valuables at home, there's no one to protect me. That's how I go to the cave at night when the money runs out...Please escort me to the cave, and I will return the money you gave them... I don't think the pirates will risk following us while you're with me.";
			link.l1 = "Sorry, darling, I have completely different plans. Next time, you'll take your treasures.";
			link.l1.go = "Node_200End";
			link.l2 = "Come on, if you're not afraid of me.";
			link.l2.go = "Node_204";
		break;

		case "Node_204":
			dialog.text = "For some reason I'm not afraid of you...";
			link.l1 = "Well, you're doing the right thing.";
			link.l1.go = "Node_205";
		break;

		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "Captain, you promised to take me to the cave.";
			link.l1 = "Let's go...";
			link.l1.go = "exit";
		break;

		case "Node_207":
			dialog.text = "That's it, Captain, I took as much as I needed. We can go back.";
			link.l1 = "I don't think I can see your buddies.";
			link.l1.go = "Node_208";
		break;

		case "Node_208":
			dialog.text = "Well, thank God. There will be less trouble... Here, take these bars, it should cover your expenses. Go od"+ GetSexPhrase("in", "on") +"I'll go the other way...";
			link.l1 = "Well, good luck if you're not afraid.";
			link.l1.go = "Node_209";
		break;

		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			sGems = makeint(sti(pchar.GenQuest.EncGirl.price))/100;
			TakeNItems(pchar, "jewelry17", sGems);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;

		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;

		case "Node_210":
			dialog.text = "Hmm, "+ GetSexPhrase("captain", "girl") +"I don't like your irony.";
			link.l1 = "Free, "+ GetSexPhrase("pretty woman", "sweetheart") +". You better hurry to the city before they follow you again.";
			link.l1.go = "Node_1End";
		break;

		case "Node_211":
			dialog.text = "I was so excited! Don't take me to the settlement tavern " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? Otherwise, I'm afraid they'll follow me again.";
			link.l1 = "I guess you're right. Let's go...";
			link.l1.go = "Node_122Next";
			ChangeCharacterReputation(pchar, 1);
		break;

		case "Node_220":
			dialog.text = "Oh, Captain, it's a long story, I don't think you'll be interested in it. Although... I can't do without your help now anyway. Would you agree to escort the settlement to the tavern " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? Otherwise, I'm afraid they won't let go.";
			link.l1 = "Sorry, honey, I don't have time, things are waiting.";
			link.l1.go = "Node_221";
			link.l2 = "Why are you so secretive?";
			link.l2.go = "Node_222";
		break;

		case "Node_221":
			ChangeCharacterReputation(pchar, -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;

		case "Node_222":
			dialog.text = "How can you not be secretive if everyone tries to profit from your misfortune?";
			link.l1 = "Come on...";
			link.l1.go = "Node_223";
		break;

		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_224":
			chrDisableReloadToLocation = false;
			if (PChar.sex != "woman")
			{
				dialog.text = "It's too crowded here. Let's go into the room, I need to tell you something.";
				link.l1 = LinkRandPhrase("I've already done a lot for you, so goodbye.", "Don't abuse my location. Goodbye, dear.", "I'm not interested in your stories. You'll figure it out for yourself.");
				link.l1.go = "Node_226";
				link.l2 = "Hmm, all right. I'm going to get the keys from the innkeeper.";
				link.l2.go = "Node_227";
			}
			else
			{
				dialog.text = "Thank you so much for your help, sweet girl. I will never forget your kindness.";
				link.l1 = "Goodbye. You better be careful from now on.";
				link.l1.go = "Node_226_1";
			}
		break;

		case "Node_225":
			chrDisableReloadToLocation = false;
			if (PChar.sex != "woman")
			{
				dialog.text = "It's too crowded here. Let's go into the room, I need to tell you something.";
				link.l1 = LinkRandPhrase("I've already done a lot for you, so goodbye.", "Don't abuse my location. Goodbye, dear.", "I'm not interested in your stories. You'll figure it out for yourself.");
				link.l1.go = "Node_226";
				link.l2 = "Hmm, all right. I'm going to get the keys from the innkeeper.";
				link.l2.go = "Node_227";
			}
			else
			{
				dialog.text = "Thank you so much for your help, sweet girl. I will never forget your kindness.";
				link.l1 = "Goodbye. You better be careful from now on.";
				link.l1.go = "Node_226_1";
			}
		break;

		case "Node_226":
			ChangeCharacterReputation(pchar, -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_226_1":
			ChangeCharacterReputation(pchar, 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
//			chrDisableReloadToLocation = true;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "Do you still want to hear my story?";
				link.l1 = "No, I think I should go now. Have a nice stay.";
				link.l1.go = "Node_232";
				link.l2 = "Tell me, once you've started.";
				link.l2.go = "Node_233";
			}
			else
			{
				dialog.text = "Ah, my noble savior, at last I can thank you in a way that only women can do.When I saw you in the jungle, everything turned upside down in me. I forgot about the rapists and the sharp palm leaves that slapped my cheeks. I forgot where I was running, why I was running... I've only seen you. And I only wanted you... And after what you've done for me...";
				link.l1 = "Wow! That's the temperament! Your pursuers knew who to run after...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "Listen, pretty girl, I understand your enthusiasm, but keep your temperament to yourself.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;

		case "Node_229":
			dialog.text = "Well, come to me, my hero...";
			link.l1 = "Ah, beautiful...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;

		case "Node_230":
			dialog.text = "Ah! How are you!.. How dare you?! Dork! The girl comes to him with all her soul and body, and he!..";
			link.l1 = "If you twisted your tail less, and hung yourself on the neck of the first person you met, you would have fewer problems. Otherwise they'll pull up their skirts, and then rescue them through the jungle...";
			link.l1.go = "Node_231";
		break;

		case "Node_231":
			dialog.text = "Well, I haven't heard that from anyone yet! And I don't intend to forgive anyone! Mark my words again!";
			link.l1 = "Stomp-stomp. And pick up your stockings, otherwise you'll have to save them again...";
			link.l1.go = "Node_231_1";
		break;

		case "Node_231_1":
			LAi_LockFightMode(pchar, true);
			ChangeCharacterReputation(pchar, 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();
		break;

		case "Node_232":
			ChangeCharacterReputation(pchar, -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "My family lives in a settlement " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City) + ". I got here completely by accident - the ship on which the groom was taking me to his parents was captured by pirates. The ship was taken away, and the passengers were dropped off in a bay not far from here. My fiance died during the boarding, and I became seriously ill during the jungle crossing.The hostess of a local brothel visited me, and when I got back on my feet, she demanded to work off the funds spent on treatment. But I didn't turn out to be a whore, and the madam hostess, in order to earn something, sold me to some bandits. You know the rest.";
			link.l1 = "So drop it all and go home! Why do you allow yourself to be treated like a slave?!";
			link.l1.go = "Node_234";
		break;

		case "Node_234":
			dialog.text = "I can't! all my belongings-decent clothes, money, documents-were left in the brothel in a travel bag. I hid it in the dating room. And in such an outfit, the sailors in the port will not let me pass, let alone travel. And who will take me on board without money and documents? And now I can't even show up in the city... They'll put me in jail...";
			link.l1 = "I've come up with a problem! Get ready, let's go. I'll take you.";
			link.l1.go = "Node_235";
			link.l2 = "Wait here. I'll get your valise...";
			link.l2.go = "Node_236";
			if(sti(pchar.money) >= 5000)
			{
				link.l3 = "Yes, who is interested in your documents? How much money do you need to get home?";
				link.l3.go = "Node_237";
			}
		break;

		case "Node_235":
			dialog.text = "Thank you, Captain... But I have nothing to pay you with.";
			link.l1 = "What's the payback?! Let's go before they miss you...";
			link.l1.go = "Node_240";
		break;

		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit();
		break;

		case "Node_236":
			dialog.text = "Ah, Captain, and I didn't even dare to ask for it.";
			link.l1 = "Don't be afraid. I'll be there soon.";
			link.l1.go = "Node_239";
		break;

		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";

			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;

		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "Oh, I thought something had happened to you.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "What can happen to me? Here, take your things.";
				link.l1.go = "Node_241";
			}
			else
			{
				link.l1 = "Listen, I didn't find anything. Are you sure you left the bag in the visiting room?";
				link.l1.go = "Node_242";
			}
		break;

		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "Thank you, "+ GetSexPhrase("noble captain", "noble girl") +". I will never forget what you have done for me. And even though I have nothing, let me give you this amulet, maybe it's only thanks to it that I survived the pirate attack.";
			link.l1 = "Thank you. Have a good trip. Goodbye...";
			link.l1.go = "Node_243";
		break;

		case "Node_242":
			dialog.text = "Has my hiding place been found?";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "How much money do you need to get home?";
				link.l1.go = "Node_237";
			}
			link.l2 = "We may have found it. Only now our paths are diverging. Goodbye!";
			link.l2.go = "Node_244";
		break;

		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "la"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", "a"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_245":
			dialog.text = "Thank you, Captain. I can't believe I'm home. Please don't refuse, come on, I'll introduce you to your parents.";
			link.l1 = "Listen, "+ GetSexPhrase("beauty", "darling") +", I really don't have time. Let's do it next time...";
			link.l1.go = "Node_246";
		break;

		case "Node_246":
			dialog.text = "Very sorry... Well, then, goodbye, and may God protect you. And even though I don't have anything, let me give you this amulet.";
			link.l1 = "Thank you! Run, run, please your parents...";
			link.l1.go = "Node_247";
//			link.l2 = "Do you really think this is necessary?";
//			link.l2.go = "Node_248"
		break;

		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_248":
		break;

		case "Node_237":
			dialog.text = "Well, I do not know... Maybe you'll have to wait for a passing flight for a while. But I can't ask you for money.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "Okay. Here, take 5,000 piastres. That should do it.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "Okay. Here, take 25,000 piastres. And go home.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "I see. Here, have 35,000 piastres. Get yourself a suite cabin.";
				link.l3.go = "Node_237_3";
			}
		break;

		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterReputation(pchar, -5);
			dialog.text = "Thank you, "+ GetSexPhrase("noble captain", "noble girl") +". I will never forget what you have done for me.";
			link.l1 = "Have a good trip. Goodbye...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;

		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "Thank you, "+ GetSexPhrase("noble captain", "noble girl") +". I will never forget what you have done for me.";
			link.l1 = "Have a good trip. Goodbye...";
			link.l1.go = "Node_238";
		break;

		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterReputation(pchar, 2);
			dialog.text = "Thank you, "+ GetSexPhrase("noble captain", "noble girl") +". I will never forget what you have done for me.";
			link.l1 = "Have a good trip. Goodbye...";
			link.l1.go = "Node_238";
		break;

		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney")
			{
				AddSimpleRumour(RandPhraseSimple("Did you hear that some whore tried to enter the ship without documents? She was caught and taken back to the brothel. They say she owes the landlady a tidy sum.",
				"Have you heard? Some kind of undocumented whore was caught in our port. They say she escaped from the brothel after cleaning the chests of the local hostess. This peddler of infection and theft should have been shut down long ago. After all, our children see all this, what can they learn?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_250":
			dialog.text = "Don't ruin it, Captain! My father wants to marry me off to the son of a usurer, a slobbery freak... Because his dad has a lot of piastres in his trunks! I'd rather stay in the jungle, to be eaten by wild animals! Do not send me into lifelong bondage, I beg you!";
			link.l1 = "What are you doing, "+ GetSexPhrase("beauty", "darling") +", are you running away from marriage? Go for the one who woos while they take it. Time will pass - and you'll be glad to see a slobbery freak, he won't call you anymore...";
			link.l1.go = "Node_251";
		break;

		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "No!.. No, Captain, I love a man named " + pchar.GenQuest.EncGirl.sLoverId + " and besides him, I don't want to know anyone! And my father is against it! he says that he is in the settlement " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + " a visitor and will never find a job here, he is about to go around the world and lead me with him. And I would go to the end of the world just to be with him... Take me to him, please.";
			link.l1 = "Okay, let's go. I'll think about where to put you on the way...";
			link.l1.go = "Node_252";
		break;

		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId);
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "Captain, you promised to take me to the settlement " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) +".";
			link.l1 = RandPhraseSimple("I remember, I remember.", "Don't worry - I'll see you off.");
			link.l1.go = "exit";
		break;

		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(2) > 0)
			{
				dialog.text = RandPhraseSimple("Thank you, "+ GetSexPhrase("captan", "girl") +", once again. I don't know how to thank you.", "Thank you very much, "+ GetSexPhrase("captain", "girl") +". I can't even imagine what I would have done if you hadn't arrived in time.");
				link.l1 = RandPhraseSimple("From now on, you will have science. Well, have a nice stay...", "You'll be more careful next time... Well, go home, things are waiting for me.");
				link.l1.go = "Node_1End";
				link.l2 = "Is it possible to be so careless? Why are you alone in the jungle?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Ah, "+ GetSexPhrase("captain", "girl") +"I really don't know how to thank you.";
				link.l1 = "Don't mention it. Always happy to help...";
				link.l1.go = "Node_261";
			}
		break;

		case "Node_261":
			dialog.text = "Will you take me to the tavern? I need to wait for my aunt and rest, I was so worried...";
			link.l1 = "No, "+ GetSexPhrase("beauty", "darling") +", then without me. I've got my hands full as it is.";
			link.l1.go = "Node_262";
			link.l2 = ""+ GetSexPhrase("Oh those women! They can't take a step without a man!", "And why are you so helpless?") +"Let's go...";
			link.l2.go = "Node_263";
		break;

		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation) > 80)
			{
				dialog.text = "I have some money. Take them as a token of my gratitude!";
				Link.l1 = "Thank you. Be careful next time.";
				Link.l1.go = "exit";
			}
			else
			{
				if(drand(1) == 0)
				{
					dialog.text = "I'll tell everyone that you saved me! Let everyone know, "+ GetSexPhrase("what a brave and kind person you are", "what a brave and kind person you are") +"!";
					Link.l1 = "Thank you. You'd better go home now.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "I have some money. Take them as a token of my gratitude!";
					Link.l1 = "Thank you. Be careful next time.";
					Link.l1.go = "exit";
				}
			}
		break;
        //#20200315-01
        case "CitizenNotBlade":
            npchar.chr_ai.type.checkFight = 999999.0;
            Diag.TempNode = "ThanksAgain";
			dialog.text = "I have some money. Take them as a token of my gratitude!";
			Link.l1 = "Thank you. Be careful next time.";
			Link.l1.go = "exit";
		break;
		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "I'll tell everyone that you saved me! Let everyone know, "+ GetSexPhrase("what a brave and kind person you are", "what a brave and kind person you are") +"!";
			Link.l1 = "Thank you. You'd better go home now.";
			Link.l1.go = "exit";
		break;
	}
}
