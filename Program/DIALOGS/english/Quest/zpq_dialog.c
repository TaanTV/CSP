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
		case "First time":
			dialog.text = "I don't want to talk.";
			link.l1 = "Hmm, I see...";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Wait a minute, "+ GetSexPhrase("senor", "senorita") +". Isn't that you "+ GetFullName (pchar) +"?";
			link.l1 = "Yes, that's right. What can I do for you?";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "We need you. Or rather, your gold. And don't try to be stubborn, I'm not in the mood today - I might get angry inadvertently.";
			link.l1 = "For God's sake, what kind of gold? You don't think I'm going to carry the treasury with me.";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "Don't mess with us. Just give back the money you just received - " + FindRussianMoneyString(sti(pchar.questTemp.zpq.sum)) + ", and go your own way. Or we'll take them by force.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "Aren't you working for this prison rat? Then I can make you happy - I sent him to forefathers. So get lost before I'll do the same with you.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "Aren't you working for this prison rat? Tell him that the gold has fallen into safe hands, let him forget about it!";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Okay, take your dirty money, you bastards!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "I don't have them...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "Well, then this is your fate - to die in the prime of life from greed, because now it's too dangerous to leave you alive.";
			link.l1 = "What self-confidence.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "Hehe, so this is his fate - to die of greed. But it's even good for us - now we don't have to share it with anyone.";
			link.l1 = "And greed will ruin you...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "Hey guys!! Put the bag over "+ GetSexPhrase("his", "her") +" head!";
			link.l1 = "Well, you asked for it...";
			link.l1.go = "zpq_sld2_5";
		break;
		case "zpq_sld2_5":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(PChar, true);

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("zpq", "7");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = "Cumana";
			pchar.quest.zpq_seaBattle.function = "zpq_seaBattle";
		break;
		case "zpq_sld2_6":
			dialog.text = "That's nice. Give them to me and get out, Captain!";
			link.l1 = "Kha...";
			link.l1.go = "zpq_sld2_7";
			AddMoneyToCharacter(Pchar, -makeint(pchar.questTemp.zpq.sum));
			ChangeCharacterReputation(pchar, -5);
			AddQuestRecord("zpq", "8");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("", "a"));
		break;
		case "zpq_sld2_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for(int i = 1; i <= 3; i++)

			{

				sld = CharacterFromID("qp2_" +i);
				LAi_SetImmortal(sld, true);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 6.0);
			}
		break;
	}
}





