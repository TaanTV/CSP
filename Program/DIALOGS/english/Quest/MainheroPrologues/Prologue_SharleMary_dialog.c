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
			if (npchar.id == "SharleMary")
			{
				chrDisableReloadToLocation = false;
				LAi_SetPlayerType(PChar);
				LAi_SetImmortal(NPChar, true);
				dialog.text = GetSexPhrase("Charles! You're covered in blood!", "Mary! You're covered in blood!");
				link.l1 = "It's nothing. "+GetSexPhrase("attached", "attached")+" about the rocks on the shore. Have you been hurt? These devils poison their weapons.";
				link.l1.go = "2";
				
				pchar.SharleMaryId = npchar.id;
			}

			if (npchar.id == "SMPirate1")
			{
				chrDisableReloadToLocation = false;
				LAi_SetPlayerType(PChar);
				LAi_SetImmortal(NPChar, true);
				dialog.text = "Look, guys, what a sweet couple wandered onto our beach! The sea battered our tub and washed overboard a third of the crew, and here is such a gift! There is no silver lining, as our chaplain said, God rest his sinful soul!";
				link.l1 = "We were wrecked near these shores and we ask you, as Christians, to help us get to any friendly colony, where, on my honor, I will thank you in full.";
				link.l1.go = "SMPirate1_2";
				if (CheckAttribute(pchar, "SharleMary.LowerIsDead"))
				{
					dialog.text = "Look guys who wandered onto our beach! The sea battered our tub and washed overboard a third of the crew, and here is such a gift! There is no silver lining, as our chaplain said, God rest his sinful soul!";
					link.l1 = "I was wrecked near these shores and I ask you, as Christians, to help me get to any friendly colony, where, on my honor, I will thank you in full.";
					link.l1.go = "SMPirate1_3";
				}
			}
			if (npchar.id == "SMCrew1")
			{
				chrDisableReloadToLocation = false;
				LAi_SetPlayerType(PChar);
				LocatorReloadEnterDisable("Shore_ship2", "boat", false);
				bDisableCharacterMenu = false;
				bDisableLandEncounters = false;
				dialog.text = "Damn it! If we had known that everything would turn out this way, we would never have escaped from penal servitude at the beginning of this storm, and now you have come out of nowhere and killed the last one who knew how to control the ship.";
				link.l1 = "I also understand the ship business. I have an offer that will benefit us all. You take me as skipper and we're off from here.";
				link.l1.go = "SMCrew1_2";
			}
			NextDiag.TempNode = "First time";
		break;

		case "SMCrew1_2":
			dialog.text = "We are not in a position to refuse. Please come on board.";
			link.l1 = "Great!";
			link.l1.go = "SMCrew1_3";
		break;
		case "SMCrew1_3":
			DialogExit();
			sld = characterFromID("SharleMary");
			DeleteAttribute(sld, "cirassId");
			LAi_SetHP(sld, 150.0, 150.0);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "boat", "none", "", "", "", 5);
			if (pchar.sex == "man")
			{
				sld.Dialog.Filename = "Quest\MainheroPrologues\Mary_dialog.c";
				sld.dialog.currentnode = "hired";
			}
			if (pchar.sex == "woman")
			{
				sld.Dialog.Filename = "Enc_Officer_dialog.c";
				sld.dialog.currentnode = "hired";
			}
		break;
		case "SMPirate1_2":
			DialogExit();
			StartInstantDialog("SharleMary", "SMPirate1_3", "Quest\MainheroPrologues\Prologue_SharleMary_dialog.c");
		break;
		case "SMPirate1_3":
			dialog.text = "(to the pirate) Yes, our friends will pay you for the inconvenience and you will be credited with a godly deed, helping those in need.";
			link.l1 = "";
			link.l1.go = "SMPirate1_4";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("SMPirate1"));
		break;
		case "SMPirate1_4":
			DialogExit();
			StartInstantDialog("SMPirate1", "SMPirate1_5", "Quest\MainheroPrologues\Prologue_SharleMary_dialog.c");
		break;
		case "SMPirate1_5":
			dialog.text = "Watch how they sing, just like at mass, you will listen. Guys, tie them up!";
			link.l1 = "We'll see about that!";
			if (CheckAttribute(pchar, "SharleMary.LowerIsDead"))
			{
				dialog.text = "Watch how he sings, just like at mass, you will listen. "+GetSexPhrase("Guys, knit him!", "Guys, knit the girl, then bring her to my cabin.");
				link.l1 = "...";
				link.l1.go = "SMPirate1_5";
			}
			link.l1.go = "Exit_fight_pirates";
		break;

		case "2":
			dialog.text = ""+GetSexPhrase("I'm fine, and ready to fight again, yes!", "No, I'm fine.");
			link.l1 = "Why are you "+GetSexPhrase("went alone?", "went alone?");
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = "I "+GetSexPhrase("thought", "thought")+" meet our miskito friends, and cannibals live here. We need to get out of here as soon as possible. Let's go to the beach, maybe someone else washed up on the shore. And we need to do something about your head wound. It looks bad.";
			link.l1 = "Let's go, "+GetSexPhrase("Mary", "Charles")+".";
			link.l1.go = "Exit_follow";
		break;



		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_fight_pirates":
			NextDiag.CurrentNode = "5";
			AddDialogExitQuest("MainHeroFightModeOn");

			SharleMary_FightPirates();

			//LAi_group_Attack(NPChar, Pchar);
			//LAi_SetWarriorType(NPChar);
			//LAi_SetImmortal(NPChar, false);
			DialogExit();
		break;

		case "Exit_follow":
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.rank = 3;
			SetSPECIAL(sld, 6, 6, 8, 5, 8, 8, 8);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			sld.quest.meeting = true;
			Npchar.CanTakeMushket = true;
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // Контузия
			LAi_SetImmortal(NPChar, false);
			if (bHalfImmortalPGG)
			{
				sld.immortalofficer = true;
				pchar.Option_ImmortalOfficers = "1";
			}
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			if (pchar.sex == "man")
			{
				sld.Dialog.Filename = "Quest\MainheroPrologues\Mary_dialog.c";
				sld.dialog.currentnode = "hired";
			}
			if (pchar.sex == "woman")
			{
				sld.Dialog.Filename = "Enc_Officer_dialog.c";
				sld.dialog.currentnode = "hired";
			}
			DialogExit();
		break;
	}
}
