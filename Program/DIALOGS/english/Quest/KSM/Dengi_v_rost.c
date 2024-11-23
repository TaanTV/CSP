
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sBlade;

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

		case "simon_helper_bazar":
			dialog.text = "Join us, Captain! Crazy Simon pours it for free, you just play along with him a little if you want a drink.";
			link.l1 = "Of course I will join. Which one of you is Simon?";
			link.l1.go = "1";
		break;

		case "1":
			dialog.text = "Yes, this one, in a hat.";
			link.l1 = "That's nice.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "simon_helper_bazar";
		break;

		case "simon_bazar":
			dialog.text = "Oh, neophyte! Did you come to bow to the Master of the sea?";
			link.l1 = "Not really. I've come to talk about the money that you borrowed from...";
			link.l1.go = "6";
		break;

		case "6":
			int KSM_DVR_Schitaem2 = pchar.Quest.KSM_DVR_Dengi.FindCitizenMoney;
			if(KSM_DVR_Schitaem2 < 10000) { KSM_DVR_Schitaem2 = 10000 + drand2(1000); }
			if(KSM_DVR_Schitaem2 > 30000) { KSM_DVR_Schitaem2 = 30000 + drand2(1000); }
			dialog.text = "The owner of the sea does not need money! You'd better have a drink with us and praise ME properly!";
			link.l1 = "Simon, you borrowed " + KSM_DVR_Schitaem2 + " piastres from a usurer, you'd better remember that...";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "I'm tired of you, annoying fly. It's time for you to die... Guys, help "+GetSexPhrase("him die", "her die")+"!";
			link.l1 = "Damn it!";
			link.l1.go = "Draka";
		break;

		case "Draka":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("KSM_DVR_Saiman");
			LAi_SetActorType(sld);
			for (i=1; i<=3; i++)									//Количество
			{
				sld = CharacterFromID("KSM_DVR_SaimanOhrana_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "KSM_DVR_Pobeda");

			chrDisableReloadToLocation = true;
		break;

		case "dolg_bazar_1":
			dialog.text = "Thank you, Captain "+pchar.name+".";
			link.l1 = "Why the hell did you kill this weirdo?";
			link.l1.go = "8";
		break;

		case "8":
			dialog.text = "A bullet is the best cure for insanity, Captain. And besides... Didn't he deserve to die by ordering you to be killed?";
			link.l1 = "Perhaps... Well, since Simon is dead thanks to your efforts, you can see how much money he left us.";
			link.l1.go = "Smotrim";
		break;

		case "Smotrim":
			DialogExit();
			LAi_Fade("", "");
			sld = CharacterFromID("Villemstad_usurer");
			LAi_SetActorType(sld);
			DoQuestCheckDelay("KSM_DVR_Smotrim_2", 0.5);
		break;

		case "dolg_bazar_2":
			int KSM_DVR_Dengi = sti(pchar.Quest.KSM_DVR_Dengi.FindCitizenMoney);
			int KSM_DVR_Nashli = KSM_DVR_Dengi - (KSM_DVR_Dengi / 4);
			dialog.text = "Great! There are more than " + KSM_DVR_Nashli + " piastres!";
			link.l1 = "And how many of them belong to me?";
			link.l1.go = "9";
		break;

		case "9":
			int KSM_DVR_Dengi2 = pchar.Quest.KSM_DVR_Dengi.FindCitizenMoney;
			int KSM_DVR_Nashli2 = KSM_DVR_Dengi2 - (KSM_DVR_Dengi2 / 4);
			int KSM_DVR_Nagrada = KSM_DVR_Nashli2 / 2;
			dialog.text = "" + KSM_DVR_Nagrada + " piastres, captain. Take them, they're yours.";
			link.l1 = "Thank you.";
			link.l1.go = "Konets";
			AddMoneyToCharacter(pchar, sti(KSM_DVR_Nagrada));
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Konets":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);

			AddQuestRecord("KSM_DVR", "2");
			CloseQuestHeader("KSM_DVR");
			pchar.questdata.DengiRost = 1;
			DeleteAttribute(pchar, "Quest.KSM_DVR_Dengi");

			PChar.quest.KSM_DVR_RostovshikDomoy.win_condition.l1 = "ExitFromLocation";
			PChar.quest.KSM_DVR_RostovshikDomoy.win_condition.l1.location = PChar.location;
			PChar.quest.KSM_DVR_RostovshikDomoy.win_condition = "KSM_DVR_RostovshikDomoy";
		break;
	}
}
