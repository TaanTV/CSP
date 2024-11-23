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

		case "First time":
			if (Pchar.Location == Pchar.location.from_sea)
			{
				dialog.text = "Finally you're here. I thought you'd be scared. Is there no one behind you? This is a serious matter.";
				link.l1 = "There is no one behind me. And I have nothing to fear, I'm not stealing sheep, but I'm making a deal with honest smugglers. Or not?";
				link.l1.go = "pirateStartQuest_Smuggler3_1";
			}
			else
			{
				dialog.text = "Finally you're here. Only I don't see your ship, "+ GetSexPhrase("buddy", "girlfriend") +". Where should we put the goods?";
				link.l1 = "Right, anchored in the wrong bay... I'll be right there!";
				link.l1.go = "exit";

			}
		break;
		case "pirateStartQuest_Smuggler3_1":
			dialog.text = "Heh, well said. Well, now tell me how much " + pchar.questTemp.pirateStartQuest.Name + " paid you to find slaves.";
			link.l1 = "Well, I warned you that I don't have time to play your games. Either you sell me slaves, or I'll look for them elsewhere.";
			link.l1.go = "pirateStartQuest_Smuggler3_2";
		break;
		case "pirateStartQuest_Smuggler3_2":
			dialog.text = "The slaves are in that cage over there, look. Fresh, full of energy. Are they satisfied?";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Satisfied. Here is half the amount, you will receive the rest after loading.";
				link.l1.go = "pirateStartQuest_Smuggler3_3";
			}
			link.l2 = "Take your time, buddy, it seems to me that this goods is from the schooner Sentblue. Tell me who the informant is.";
			link.l2.go = "pirateStartQuest_Smuggler3_5";
			GiveItem2Character(npchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_pirateStartQuest");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			AddQuestRecord("pSQ", "5");
			AddQuestUserData("pSQ", "sSex", GetSexPhrase("ate", "la"));
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
		break;
		case "pirateStartQuest_Smuggler3_3":
			dialog.text = "Slaves are loaded. Let's get settled, and run away before the patrol covers us.";
			link.l1 = "Take your time, buddy, it seems to me that this goods is from the schooner Sentblue. If you want to get the other half, tell me who the informant is.";
			link.l1.go = "pirateStartQuest_Smuggler3_5";
			AddMoneyToCharacter(pchar, -15000);
			AddMoneyToCharacter(npchar, 15000);
			AddCharacterGoods(pchar, GOOD_SLAVES, 100);
			AddQuestUserData("pSQ", "sText", "My employer doesn't need to know about slaves.");
		break;
		case "pirateStartQuest_Smuggler3_5":
			dialog.text = "Damn it! Now everything is clear. I'll have to shake the money out of you, along with your guts and your filthy soul!";
			link.l1 = "Apparently, you're not that serious. But, I hope, at least they are not stupid, so I suggest a peaceful option - you tell the name of the informant who handed over the schooner and the buyer to you, then you can leave here alive.";
			link.l1.go = "pirateStartQuest_Smuggler3_6";
		break;
		case "pirateStartQuest_Smuggler3_6":
			dialog.text = "It's good that everything turned out that way. It's a secluded place here, you couldn't have dreamed of a better grave, I guess. A " + pchar.questTemp.pirateStartQuest.Name + "let him look for more spies.";
			link.l1 = "Yes, I guess I'll have to tickle your liver...";
			link.l1.go = "pirateStartQuest_Smuggler3_7";
		break;
		case "pirateStartQuest_Smuggler3_7":
			chrDisableReloadToLocation = true;
			RemoveGeometryFromLocation(pchar.questTemp.pirateStartQuest.Shore, "smg");

			for(i=1; i<=3; i++)
			{
				sld = CharacterFromID("psq2_" +i);
				LAi_SetImmortal(sld, false);
			}

			LAi_group_SetRelation("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("pirateStartQuest_Smuggler_group", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");

			pchar.quest.pirateStartQuest_Lether_fc.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirateStartQuest_Lether_fc.win_condition.l1.location = pchar.location;
			pchar.quest.pirateStartQuest_Lether_fc.function = "pirateStartQuest_Lether_fc";
		break;
	}
}





