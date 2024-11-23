void ProcessDialogEvent()
{
	ref NPChar, TempChar;
	aref Link, Diag;

	int iTemp;
	string sTemp, sTemp1;
	string sGroup;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			dialog.text = GetFullName(PChar) + "! "+"We've been tracking you for a long time, and now we finally have you in our hands.";
			if (SFheadhunters(NPChar.id)) dialog.text = "So, you got a lot of silver and you think no one's gonna look for it?"; // СФ
			if (HasSubStr(NPChar.id, "BShh")) dialog.text = "Influential people have asked me to send you greetings from the Guthrie family.";
			Link.l1 = "Who are you and what do you want from me?";
			Link.l1.go = "meeting";
			if (!HasSubStr(NPChar.id, "BShh")) PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name) + "I paid a good price for your head, it doesn't matter"+ GetSexPhrase("we'll deliver you alive or dead", "we'll deliver you alive or dead") +".";
			Link.l1 = "I'm ready to pay you more if you'll just leave me alone.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+ GetSexPhrase("Excuse me, but it looks like you've made a mistake. I "+ GetFullName(TempChar) + " - a well-known merchant in these parts", "It seems that you have mistaken me. I am a simple girl, my father is "+ GetFullName(TempChar) + " - a well-known merchant in these parts") +".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "Well, try your luck.";
			Link.l3.go = "battle";
		break;

        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "Oh! We must have made a mistake, forgive us, "+ GetAddress_Form(NPChar) + ".";
                Link.l1 = "Of course it happens...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "It looks like you're lying!";
                Link.l1 = "I'm ready to pay you more if you'll just leave me alone.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "Well, try your luck.";
			    Link.l2.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }

        break;

        case "lier_2":
            AddDialogExitQuest("GoAway_Hunters_Land");
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // только ОЗГи, а не кладоисатели
            {   // запись в СЖ
	            AddQuestRecord("HeadHunter", "HeadHunter_free");
				AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("xia", "as"));
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart");
				CloseQuestHeader("HeadHunter");
            }
            DialogExit();
        break;
        // boal <--

        case "battle":
            AddDialogExitQuest("Battle_Hunters_Land");    // BOAL Весь код я перенёс сюда по всем нациям, просто не переименовал
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // только ОЗГи, а не кладоисатели
            {   // запись в СЖ
	            AddQuestRecord("HeadHunter", "HeadHunter_battle");
				AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("xia", "as"));
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart");
				CloseQuestHeader("HeadHunter");
            }
            DialogExit();
        break;

        case "Cost_Head2":
            AddMoneyToCharacter(pchar, -sti(PChar.HunterCost));

            AddDialogExitQuest("GoAway_Hunters_Land");

            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // только ОЗГи, а не кладоисатели
            {   // запись в СЖ
	            AddQuestRecord("HeadHunter", "HeadHunter_Buy");
				AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("xia", "as"));
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart");
				CloseQuestHeader("HeadHunter");
            }
            DialogExit();
        break;

        case "Cost_Head":
			dialog.text = "I think that " + PChar.HunterCost + " piastres will suit us.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "I don't have enough money.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "Here's your money, take it and get out.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "Such a sum to you scum... I'd rather cut you all here!!!";
                Link.l2.go = "battle";
            }
		break;


        case "NoMoney":
			dialog.text = "In that case, the conversation is over!";
			Link.l1 = "You can't take me alive.";
			Link.l1.go = "battle";
		break;

		case "TreasureHunter":
			dialog.text = "Wait a minute, "+ GetSexPhrase("buddy", "girlfriend") +"... I think you have something interesting. It is necessary to share the found treasures with your loved ones.";
            Link.l1 = "Okay, I'm ready to pay you to leave me alone.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+ GetSexPhrase("Excuse me, but it looks like you've made a mistake. I "+ GetFullName(TempChar) + " - a well-known personality in these parts, not a treasure hunter, ", "It seems that you have mistaken me. I'm a simple girl, not a treasure hunter! My father is "+ GetFullName(TempChar) + " - a well-known personality in these parts") +"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "Well, it's time for your heads to separate from your body.";
			Link.l3.go = "battle";
		break;

		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "Oh! We must have made a mistake, forgive us, "+ GetAddress_Form(NPChar)+".";
                Link.l1 = "Of course it happens...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "It looks like you're lying!";
			    Link.l1 = "Then listen to my saber sing.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;

		// генератор "A reason to hurry"
		case "ReasonToFast_THunter_1":
			if(CheckAttribute(pchar, "GenQuest.CannotWait"))	DeleteAttribute(pchar, "GenQuest.CannotWait");
			dialog.text = "Here comes our gold. We didn't guard you for nothing.";
			link.l1 = RandPhraseSimple("What are you gentlemen talking about? I am "+ GetSexPhrase("representative", "representative") +" of the Dutch West Indies Campaign and am only passing through here! "+ GetSexPhrase("Stopped", "Stopped") +"admire the coast!", "It seems to me that you are confusing me with someone else. I "+ GetSexPhrase("naturalist Jacques Francois Paganel", "naturalist Marie-Therese") +" and I collect samples of the local flora. Would you like to take a look at my collection of yucca leaves? The most curious specimens are found here!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "What do you want?! Get out of the way!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;

		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "Uh no, " + GetSexPhrase("Mr. good", "honey") + ". It's not going to work that way... We know for sure that the map is " + GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN) +" you got it. And he was a pretty miser, and his coffers were bursting with piastres. Therefore, we will not leave empty-handed.";
			link.l1 = "You're right. The chests were full. Only you won't get them. You can go to the cave, there are still a couple of leaky buckets left.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8)
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "You're right, take your treasures. But they won't bring you happiness -there's too much blood on them...";
				link.l2.go = "ReasonToFast_THunter_4";
			}
		break;

		case "ReasonToFast_THunter_3":
			dialog.text = ""+ GetSexPhrase("Eh, Captain. So young, you should still live and live, ", "Oh, girl. So young, you should still live and live") +"...";
			link.l1 = "I'm not going to die!";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;

		case "ReasonToFast_THunter_4":
			dialog.text = "These are the sensible words of a sane person!";
			link.l1 = "Damn you along with these treasures...";
			link.l1.go = "ReasonToFast_THunter_GoAway";
		break;

		case "ReasonToFast_THunter_GoAway":
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0)
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}

			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0)
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "24");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");
			}
			DialogExit();
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;

		case "ReasonToFastTHunter_Fight":
			sGroup = "LAND_HUNTER";
			sTemp = "LandHunter0";
			iTemp = sti(pchar.HunterCost.Qty);
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			for(i = 1; i <= iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}

			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors");
			LAi_group_SetCheck(sGroup, "ReasonToFast_TrHuntersDied");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "ReasonToFast_HunterShore1":
			dialog.text = "Hey, "+ GetSexPhrase("buddy", "girlfriend") +"! " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "said you have something for us.";
			link.l1 = "What do you mean?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap")
			{
				dialog.text = "Map from " + GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN);
				link.l1 = "Take it and say hello to " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ". Tell him we'll meet soon...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " he is very mistaken if he thinks that I will drag chestnuts out of the fire for him.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "Whatever you stole from the governor.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8)
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "Take it and say hello to " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ". Tell him we'll meet soon...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}
				link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "he is very mistaken if he thinks that I will drag chestnuts out of the fire for him.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			chrDisableReloadToLocation = false;
		break;

		case "ReasonToFast_HunterShore12_1":
			TakeNItems(pchar, "mapQuest", -1);
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "the map");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;

		case "ReasonToFast_HunterShore12_2":
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0)
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}

			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0)
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "values");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.city + "_townhall");
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.LakeyLocation);
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;

		case "ReasonToFast_HunterShore2":
			dialog.text = "Hey, "+ GetSexPhrase("buddy", "girlfriend") +"! Y " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + "I have a couple of questions for you.";
			link.l1 = "Why doesn't he ask them himself?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;

		case "ReasonToFast_HunterShore21":
			dialog.text = "What a chaos... You  the operation that caused us to lose " + sti(pchar.questTemp.ReasonToFast.p10) + " piastres. So you owe me.";
			link.l1 = "Take it and say hello to " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ". Tell him we'll meet soon...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " is very mistaken if he thinks that I will drag chestnuts out of the fire for him.";
			link.l2.go = "ReasonToFast_HunterShore23";
		break;

		case "ReasonToFast_HunterShore22":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p10))
			{
				AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p10)));
				AddQuestRecord("ReasonToFast", "20");
				AddQuestUserData("ReasonToFast", "sText", "money");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				DialogExit();
				AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
			}
			else
			{
				dialog.text = "You don't have enough money! Well, you've made your choice... ";
				link.l1 = "A long time ago...";
				link.l1.go = "ReasonToFastTHunter_Fight";
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;

		case "ReasonToFast_HunterShore23":
			dialog.text = "Well, you've made your choice...";
			link.l1 = "A long time ago...";
			link.l1.go = "ReasonToFastTHunter_Fight";
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
				pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
			}
		break;
		// генератор "A reason to hurry"
	}
}
string GetLocHunterName()
{
	int nLoc = FindLocation(Pchar.location);
	int nFile = LanguageOpenFile("LocLables.txt");
	string ret = "";

	if(nFile >= 0)
	{
		if (CheckAttribute(&locations[nLoc], "islandId"))
		{
			if (locations[nLoc].islandId != "Mein")
			{
				ret = "islands " + LanguageConvertString(nFile, locations[nLoc].islandId);
			}
			else
			{
				ret = "mainland";
			}
		}
		//
        if (CheckAttribute(&locations[nLoc], "fastreload"))
		{
			ret += " (" +LanguageConvertString(nFile, locations[nLoc].fastreload + " Town") + ")";
		}
		//ret += LanguageConvertString(nFile, locations[nLoc].id.label);
		LanguageCloseFile( nFile );
	}
	return ret;
}
