void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();

    string ret;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
		break;

		case "start":
			dialog.text = "Wake up, " + Pchar.name + "! We finally got to "+ Pchar.HeroParam.Land +"after all these storms!"+
                          "What are you going to do? You don't have a ship anymore.";
			link.l1 = "Not for the first time! Luck is a fickle thing.";
			link.l1.go = "start1";
			link.l2 = "Do you want to offer me a job, Abraham?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "I hope you have better luck than with Mercury. Goodbye.";
			link.l1 = "I have no doubt. Goodbye, Captain!";
			link.l1.go = "game_begin";
		break;

		case "start2":
            ret = Pchar.name + "I'm a smuggler, not the mayor of the city. What kind of job do I have for you?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret + "Stop by Inez's tavern. She knows everyone on this island\n"+
                              "Go to Yurksen, he's here with the pirates instead of the governor. But first, talk to the common pirates.";
            }
            else
            {
                dialog.text = ret + "Borrow money somewhere, sell something. It's not for me to teach you.";
            }
            link.l1 = "Okay, thanks for the advice. Goodbye.";
			link.l1.go = "game_begin";
			link.l2 = "You know, Abraham, I think I'll commandeer your ship. I really liked him!";
			link.l2.go = "start3";
		break;

		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;

		case "start3":
			dialog.text = "You're not joking well, buddy.";
			link.l1 = "Never mind, old man. Goodbye!";
			link.l1.go = "game_begin";
			link.l2 = "Who said I was joking? You'll tell the crew that you sold me your boat. And I'll let you live. Is it a deal?";
			link.l2.go = "start4";
		break;

		case "start4":
			dialog.text = "It was said that you killed your teacher Malcolm Hutcher because of a lousy saber. I didn't believe it, but in vain. Today you will feed the fish. You don't stand a chance, buddy.";
			link.l1 = "Really?!";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "Oops...";
			Link.l1.go = "exit";
		break;

////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel_talkStart":
            NPChar.location = "none"; // чтоб на палубе не болтался
			//Шанс на то что продадут на рудники.
			int iRnd = (rand(100) == 30);
			if (iRnd)
			{
				dialog.text = "We've been thinking that maybe we should sell you to the mines. Ha... money is never superfluous.";
				link.l1 = "What are you saying?";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "We have arrived at the place, goodbye.";
				link.l1 = "Goodbye.";
				link.l1.go = "Travel_end";
				link.l2 = "I was thinking, I like your ship. I want to keep it for myself.";
				link.l2.go = "Travel_fight";
			}
		break;

		case "Travel_fight":
			ChangeContrabandRelation(pchar, -60);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Travel_AfterDeckFight");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);
			//Вытащим саблю
   			LAi_SetFightMode(Pchar, true);

			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Travel_end":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			//Квест бук
			AddQuestRecord("Gen_ContrabandTravel", "4");
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt")));


			LAi_SetPlayerType(PChar);
			//грузим ГГ куда нужно....
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc,
									pchar.GenQuest.contraTravel.destination.group,
									pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
			CloseQuestHeader("Gen_ContrabandTravel");
			//трём аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
		break;
	}
}
