
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

    int iTemp, i; // нужно для вычислений любых целых (нации)
	string attrName; // любые строки для вычислений
	ref sld;

    switch(Dialog.CurrentNode)
	{
		case "exit":
			StopCoastalGuardPursuit();
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LAi_SetPlayerType(Pchar);
		break;

		case "First time":
			chrDisableReloadToLocation = false;
   			LAi_LockFightMode(pchar, false);
			dialog.text = RandPhraseSimple("Something illegal seems to be going on here.",
                                     "By name "+NationKingsName(npchar)+ "stop doing lawlessness!!!");
			Link.l1 = "No, no, Officer. My friends and I are just relaxing by the sea.";
			if (makeint(Pchar.reputation) > 70 && GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) >= 5)
			{
				Link.l1.go = "ThisTimeFree";
			}
			else
			{
				Link.l1.go = "IDontBelieveYou";
			}
			Link.l2 = "I'm giving away gold. Can this be considered an illegal activity?";
			if(makeint(Pchar.rank) >= 4 && GetSummonSkillFromNameToOld(Pchar, SKILL_COMMERCE) >= 2)
			{
				Link.l2.go = "GiveMeSomeMoneyToo";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}
			Link.l3 = "Get lost, soldier. It's none of your business!";
			//#20181215-02
			bool bFencing = false;
			if(GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) >= 8)
                bFencing = true;
            if(!bFencing && GetSummonSkillFromNameToOld(Pchar, SKILL_F_LIGHT) >= 8)
                bFencing = true;
            if(!bFencing && GetSummonSkillFromNameToOld(Pchar, SKILL_F_HEAVY) >= 8)
                bFencing = true;
			if(makeint(Pchar.reputation) < 20 && bFencing)
			{
				Link.l3.go = "GettingLostFromHere";
			}
			else
			{
				Link.l3.go = "howDareYou";
			}

		break;

		case "ThisTimeFree":
			dialog.snd = "Voice\COGU\COGU002";
			dialog.text = "Don't mess with us, Captain " + Pchar.name + "! And who would have thought that such a positive and respected person like you would be involved in smuggling!";
			Link.l1 = "Alas, everyone makes mistakes. But I'm already repenting!";
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = "I'm going to cut off your head now!";
			Link.l2.go = "ThisTimeFree_fight";
		break;

		case "ThisTimeFree_1":
			dialog.snd = "Voice\COGU\COGU003";
			ChangeCharacterReputation(pchar, -40);
			dialog.text = "Since I've only heard good things about you, I'm letting you go this time. And we'll take these bastards with us!";
			Link.l1 = "Thank you, Officer. All the best to you!";
			Link.l1.go = "ThisTimeFree_exit";
		break;

		case "ThisTimeFree_fight":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(sti(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }

			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);
			LAi_group_SetHearRadius("CoastalGuards", 100.0);
			LAi_group_SetHearRadius(pchar.GenQuest.Smugglers_Group, 100.0);
			LAi_group_FightGroups("CoastalGuards", pchar.GenQuest.Smugglers_Group, true);
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);

			//LAi_SetPlayerType(Pchar);
            LAi_SetFightMode(Pchar, true);
			//trace("And we fight those soldiers!!" + Pchar.quest.contraband.CurrentPlace);
		break;

		case "ThisTimeFree_exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;

            DialogExit();
			StopCoastalGuardPursuit();
			ChangeContrabandRelation(pchar, -30);
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(sti(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);
			LAi_group_FightGroups(pchar.GenQuest.Smugglers_Group, "CoastalGuards", true);
			LAi_SetPlayerType(Pchar);
		break;

		case "IDontBelieveYou":
			dialog.snd = "Voice\COGU\COGU004";
			dialog.text = "What are you telling me! I'm not blind! Follow us - you are arrested and the goods are confiscated!";
			Link.l1 = "Hurry up, I'll gut you!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":
			dialog.snd = "Voice\COGU\COGU005";
			dialog.text = "Is that so? No, of course, this activity is perfectly legitimate... If we get it too, of course. And how much are you giving away?";
			Link.l1 = "I think that " + makeint(sti(Pchar.contratradedmoney)*(0.1+(0.01*MOD_SKILL_ENEMY_RATE*3))) + " piastres will be enough.";
			//if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/10))
			if (sti(pchar.money)>=makeint(sti(Pchar.contratradedmoney)*(0.1+(0.01*MOD_SKILL_ENEMY_RATE*3))))
			{
				Link.l1.go = "MoneyAccepted10";
			}
			else
			{
				Link.l1.go = "TryingToGiveBribe";
			}

			/*Link.l2 = "How about " + makeint(sti(Pchar.money)/5) + "piastres?";
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/5))
			{
				Link.l2.go = "MoneyAccepted5";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}

			Link.l3 = "I'm ready to give it to you, officer " + makeint(sti(Pchar.money)/2) + "piastres!";
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/2))
			{
				Link.l3.go = "MoneyAccepted2";
			}
			else
			{
				Link.l3.go = "TryingToGiveBribe";
			}*/
		break;

		case "TryingToGiveBribe":
			dialog.snd = "Voice\COGU\COGU006";
			dialog.text = "Yeah, are you offering a bribe? No, the honor of the uniform is more precious to me! Please follow us!";
			Link.l1 = "Damn it! I'm sorry to disappoint you, but I don't think you're going anywhere right now!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "I will gladly accept your donation. Since you're doing charity work.";
			Link.l1 = "Always at your service.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.contratradedmoney)*(0.1+(0.01*MOD_SKILL_ENEMY_RATE*3))));
		break;

		case "MoneyAccepted5":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "I will gladly accept your donation. Since you're doing charity work.";
			Link.l1 = "Always at your service.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/5));
		break;

		case "MoneyAccepted2":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "I will gladly accept your donation. Since you're doing charity work.";
			Link.l1 = "Always at your service.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/2));
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = "But... Devil... I have to arrest you!";
			Link.l1 = "Arrgh! Are you still here? Tired of living?";
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = "I... I'm going to complain! I'm not going to let this go...";
			Link.l1 = "Pfft!";
			Link.l1.go = "GettingLostFromHere_exit";
		break;

		case "GettingLostFromHere_exit":
			ChangeContrabandRelation(pchar, 10);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
            DialogExit();

			StopCoastalGuardPursuit();
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
                attrName = "SoldierIDX"+i;
                LAi_SetActorType(&Characters[sti(Pchar.quest.contraband.(attrName))]);
                LAi_ActorRunToLocation(&Characters[sti(Pchar.quest.contraband.(attrName))], "reload", "Reload1", "none", "", "", "", 40);
			}
			LAi_SetPlayerType(Pchar);
		break;

		case "howDareYou":
			dialog.snd = "Voice\COGU\COGU010";
			dialog.text = "Oh, you dog! Now you definitely can't get away with it. You're going to die on this shore!";
			Link.l1 = "Try to make words come true, you windbag!";
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
