
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sBlade;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int Plata1 = 14000 * MOD_SKILL_ENEMY_RATE*3 * 0.21;
	int Plata2 = 14000 * MOD_SKILL_ENEMY_RATE*3 * 0.31;

	pchar.PDM_NK_Plata2.Money = 14000 * MOD_SKILL_ENEMY_RATE*3 * 0.31;

	int Sila = 25 + MOD_SKILL_ENEMY_RATE*3 * 2.8;
	int DopHP = 40 + MOD_SKILL_ENEMY_RATE*3 * 10;
	int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE*3 * 1.2;
	if (Rank < 1) Rank = 1;

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":							//Автор Sinistra
			dialog.text = "K-who are you?";
			link.l1 = "Captain "+pchar.name+". And you?";
			link.l1.go = "Fickler_1";
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			DeleteAttribute(npchar, "talker");
			UnmarkCharacter(npchar);
		break;

		case "Fickler_1":
			dialog.text = "Ah-andreas Fickler, k-at your service.";
			link.l1 = "Why are you shaking all over, buddy?";
			link.l1.go = "Fickler_2";
		break;

		case "Fickler_2":
			dialog.text = "Y-y-you'd be s-s-shaking too if someone was going to kill you!";
			link.l1 = "Does someone want to kill you?";
			link.l1.go = "Fickler_3";
		break;

		case "Fickler_3":
			dialog.text = "Yes, "+ GetSexPhrase("mynheer", "frau") +". I can't sleep. I'm all broken up. And it's all because of that damn gunpowder!";
			link.l1 = "This seems to be a curious story. Pour out your soul to me, buddy.";
			link.l1.go = "Fickler_4";
		break;

		case "Fickler_4":
			dialog.text = "Well, I-I think I can trust you. I'm the treasurer... I used to be the treasurer on the Sea Gull caravel. Our c-c-captain bought too much gunpowder- although I advised him not to do it! I had to store some barrels in the wrong places. On the poop, for example. And one of our brainless sailors somehow got drunk to the point of insensibility. I told you not to smoke on the poop, but this stupid drunk freak sat right on a keg of gunpowder and... and...";
			link.l1 = "Lit a pipe?";
			link.l1.go = "Fickler_5";
		break;

		case "Fickler_5":
			dialog.text = "Yes... And then he dropped it... And he went straight to hell. Along with the poop, the helm, and half the ship. The mat-t-cables put out the fire, but all the cargo was already lost. And the c-captain said I wouldn't live to see the dawn! He's in the tavern now, pouring rum on his anger. But I'm afraid he's not going to stop with a drink. And t-then he'll pull out his c-cutlass and kill me right here in the square!";
			link.l1 = "A really funny story. Don't worry, Andreas. I'll help you.";
			link.l1.go = "Fickler_6";
			link.l2 = "Well, be careful with gunpowder in the future. Well, have a good life for the few remaining hours. Goodbye.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Fickler_8";
		break;

		case "Fickler_6":
			dialog.text = "H-h-how?";
			link.l1 = "I don't know. I'll figure something out. Wait for me here.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Fickler_7";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_NK_Viktor", "officer_15", "man", "man", 10, PIRATE, -1, false));
			sld.name = "Victor";
			sld.lastname = "Bretier";
			FreeSitLocator("Villemstad_tavern", "sit12");
			sld.city = "Villemstad";
			sld.location	= "Villemstad_tavern";
			sld.location.group = "sit";
			sld.location.locator = "sit12";
			LAi_SetSitType(sld);
			sld.dialog.filename   = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode   = "Viktor";

			SetQuestHeader("PDM_Neputyovy_kaznachey");
			AddQuestRecord("PDM_Neputyovy_kaznachey", "1");
		break;

		case "Fickler_7":
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			dialog.text = "Captain Victor! Oh, it's you, yes... You scared me half to death. Have you seen the B-b-ictor?");
			link.l1 = "Not yet. But don't worry-I'll take care of him.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Fickler_7";
		break;

		case "Fickler_8":
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			dialog.text = "Uh! Wait! Stay away from me! And... it's you. Well, he'll find me soon...";
			link.l1 = "Don't worry, Andreas. I'll take care of him.";
			link.l1.go = "Fickler_6";
			link.l2 = "Okay, have a nice few hours left. Goodbye.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Fickler_8";
		break;

		case "Viktor":
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			dialog.text = "You! Hey, you! Have you seen a bespectacled, brainless treasurer named Andreas here? It's his fault that I'm broke! A parasite! I'm going to kill him! He ruined me!";
			link.l1 = "So-so-so. You are Victor Bretier.";
			link.l1.go = "Viktor_2";
		break;

		case "Viktor_2":
			dialog.text = "Yes, I am Victor. And that stinking dog burned down half of my ship with those damn barrels of gunpowder! I'll skin him alive!";
			link.l1 = "Calm down, buddy. Andreas is under my protection.";
			link.l1.go = "Viktor_3";
		break;

		case "Viktor_3":
			dialog.text = "What? Under your protection? Yes, who are you?!";
			link.l1 = "I am captain "+pchar.name+". And if you touch even a hair on his head, I'll burn down the other half of your ship.";
			link.l1.go = "Viktor_4";
		break;

		case "Viktor_4":
			dialog.text = "Damn pirate! Who do you think you are? Is there any justice in this world for these brazen pirates? They oppress honest captains both at sea and on land! Where is the justice?";
			link.l1 = "You're threatening to kill your treasurer, and you're also talking about justice? I don't think the governor will take the murder of an innocent man on his land lightly.";
			link.l1.go = "Viktor_5";
		break;

		case "Viktor_5":
			dialog.text = "Innocent? I lost my freight because of that idiot! " + Plata1 + " gold! If not more! I'll find out where he's hidden!";
			link.l1 = "I'd rather chop you up into small pieces than give Andreas a hard time.";
			link.l1.go = "Viktor_Bitva";
			if (sti(pchar.Money) >= Plata2)
			{
				link.l2 = "" + Plata1 + " gold? And that's why you made a fuss? Here. I'm covering your damage, now leave Andreas alone.";
				link.l2.go = "Zaplati_ED";
			}
			else
			{
				link.l2 = "" + Plata1 + " gold? It's not a good freight.";
				link.l2.go = "Zaplati_ED";
			}
			link.l3 = "Wow! And you know what, look for your Andreas wherever you want, I won't bother you.";
			link.l3.go = "Konec";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
		break;

		case "Zaplati_ED":
			dialog.text = "Did I say " + Plata1 + "? No, I was wrong! At least " + Plata2 + "!";
			link.l1 = "Yes, you are insolent, Victor! I'd rather chop you up into small pieces than give Andreas a hard time.";
			link.l1.go = "Viktor_Bitva";
			if (sti(pchar.Money) >= Plata2)
			{
				link.l2 = "Here, hold your money. Have a nice time, Victor.";
				link.l2.go = "Zaplati_2";
			}
			else
			{
				link.l2 = "I'll bring you " + Plata2 + " gold. But remember - one volley from my ship will turn your trough into a sieve, so don't touch Andreas with a finger!";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Viktor_VernulsyDengi";
			AddQuestRecord("PDM_Neputyovy_kaznachey", "2");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sMoney", FindRussianMoneyString(sti(pchar.PDM_NK_Plata2.Money)));
		break;
		
		case "Konec":
			DialogExit();
			
			sld = CharacterFromID("PDM_NK_Viktor");
			sld.lifeday = 0;
			sld.dialog.filename   = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode   = "Viktor_Poka";
			
			sld = CharacterFromID("Andreas_Fickler");
			sld.lifeday = 0;
			
			AddQuestRecord("PDM_Neputyovy_kaznachey", "7");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader("PDM_Neputyovy_kaznachey");
			pchar.questdata.NeputyovyKaznachey = 1;
		break;
		
		case "Zaplati_ND":
			dialog.text = "";
			link.l1 = "Yes, you are insolent, Victor! I'd rather chop you up into small pieces than give Andreas a hard time.";
			link.l1.go = "Viktor_Bitva";
			link.l2 = "Okay, as soon as I have the money, I'll look you up.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Zaplati_ND";
		break;

		case "Zaplati_2":
			AddMoneyToCharacter(pchar, -sti(Plata2));
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Commerce", 220);
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			sld = CharacterFromID("PDM_NK_Viktor");
			sld.dialog.filename   = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode   = "Viktor_Poka";
			sld.lifeday = 0;
			sld = CharacterFromID("Andreas_Fickler");
			sld.dialog.filename   = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode   = "Fickler_11";
			AddQuestRecord("PDM_Neputyovy_kaznachey", "3");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("", "a"));
			DialogExit();
		break;

		case "Viktor_Poka":
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			dialog.text = "Burst your spleen! What else do you need?";
			link.l1 = "Nothing. Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Viktor_Poka";
		break;

		case "Viktor_VernulsyDengi":
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			dialog.text = "You again? What do you need?";
			link.l1 = "I just want to pay for your former treasurer, Andreas.";
			link.l1.go = "Viktor_VernulsyDengi_2";
		break;

		case "Viktor_VernulsyDengi_2":
			dialog.text = "Did you bring the money?";
			if (sti(pchar.Money) >= Plata2)
			{
				link.l1 = "" + Plata2 + " gold. Here you go.";
				link.l1.go = "Zaplati_2";
			}
			else
			{
				link.l1 = "I don't have enough money right now, Victor, but I'll come back later and pay for Andreas.";
				link.l1.go = "exit";
			}
			link.l2 = "I'm sick of being dragged around the archipelago by your stupid freight. You could've gotten your ass up 100 times and made your own money, you old fart!";
			link.l2.go = "Konec";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
		break;

		case "Viktor_Bitva":
			dialog.text = "You'll regret those words, you jerk!";
			link.l1 = "Fewer words - to the point!";
			link.l1.go = "fight_right_now";
			sld = CharacterFromID("PDM_NK_Viktor");
			if (MOD_SKILL_ENEMY_RATE <= 2)
			{
				FantomMakeCoolFighter(sld, Rank, Sila, Sila, "blade34", "Pistol1", DopHP);
			}
			else
			{
				FantomMakeCoolFighter(sld, Rank, Sila, Sila, "blade34", "Pistol2", DopHP);
			}
			sld.SaveItemsForDead = true;
			sld.DontChangeBlade = true;
			sld.DontChangeGun = true;
			AddMoneyToCharacter(sld, 15000);
			GiveItem2Character(sld, "Litsenzia");
			GiveItem2Character(sld, "mineral9");
			AddItems(sld, "jewelry1", rand(7)+2);
			AddItems(sld, "jewelry3", rand(7)+2);
			AddItems(sld, "jewelry6", 1);

			PChar.quest.PDM_NK_Viktor.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_NK_Viktor.win_condition.l1.character = "PDM_NK_Viktor";
			PChar.quest.PDM_NK_Viktor.win_condition = "PDM_NK_Viktor";

			PChar.quest.PDM_NK_Litsenzia.win_condition.l1 = "item";
			PChar.quest.PDM_NK_Litsenzia.win_condition.l1.item = "Litsenzia";
			PChar.quest.PDM_NK_Litsenzia.win_condition = "PDM_NK_Litsenzia";
		break;

		case "fight_right_now":
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Fickler_11":
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			dialog.text = "C-c-captain "+pchar.name+"! Oh, it's you, "+ GetSexPhrase("mynheer", "mefrau") +"! You scared me. Have you talked to V-victor yet?");
			link.l1 = "Yes. He won't touch you anymore. You can safely return to your Sea Gull.";
			link.l1.go = "Fickler_12";
		break;

		case "Fickler_12":
			dialog.text = "Thank you! T-a thousand times s-s-thank you! Y-you saved my life! But I can't go back to my ship. I'll be the laughingstock of the team. And this is despite the fact that I am a good k-treasurer with ten years of experience. I have no desire to return to the Sea Gull. Uh... Maybe you could use a c-c-treasurer, Captain?");
			link.l1 = "I think it would be useful. You're hired. But just dare to approach the hook cell!";
			link.l1.go = "Fickler_13";
			link.l2 = "Sorry, but I don't need a treasurer right now.";
			link.l2.go = "Fickler_NeNujen";
		break;

		case "Fickler_13":
			dialog.text = "Thank you, Captain! You won't r-r-regret it!");
			link.l1 = "Welcome aboard, Andreas.";
			link.l1.go = "Fickler_Nanyat";
			sld = CharacterFromID("Andreas_Fickler");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			ChangeCharacterReputation(sld, 80);
			sld.rank = 10;
			SetSPECIAL(sld, 4, 6, 4, 10, 10, 7, 6);
			SetSelfSkill(sld, 5, 5, 5, 5, 5);
			SetShipSkill(sld, 30, 60, 5, 5, 5, 5, 5, 5, 30);
			sld.loyality = MAX_LOYALITY;
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			sld.greeting = "GR_Andreas_Fickler";
			LAi_SetImmortal(sld, false);
			sld.HalfImmortal = true;
		break;

		case "Fickler_NeNujen":
			AddQuestRecord("PDM_Neputyovy_kaznachey", "6");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("xia", "as"));
			CloseQuestHeader("PDM_Neputyovy_kaznachey");
			pchar.questdata.NeputyovyKaznachey = 1;
			sld = CharacterFromID("Andreas_Fickler");
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			DialogExit();
		break;

		case "Fickler_Nanyat":
			sld = CharacterFromID("Andreas_Fickler");
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*50;
			sld.OfficerWantToGo.DontGo = true;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("PDM_Neputyovy_kaznachey", "5");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("xia", "as"));
			CloseQuestHeader("PDM_Neputyovy_kaznachey");
			pchar.questdata.NeputyovyKaznachey = 1;
			DialogExit();
		break;

	}
}
