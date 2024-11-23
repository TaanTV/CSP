void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;
	int i;
	bool hungry = true;
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":

			//dialog.text = "Error";
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.quest.meeting = "1";

			if (npchar.id == "CrazyScientist")
			{
				dialog.text = "Well, wait!";
				link.l1.go = "CS";
			}
			NextDiag.TempNode = "First time";
		break;

		case "GrottoSkeleton":
			scareOfficers(70);
			InterfaceStates.Buttons.Save.enable = false;
			LAi_SetImmortal(npchar, false);
			dialog.Text = "You're here to mix your bones with ours?";
			Link.l1 = "Who are you?";
			Link.l1.go = "GrottoSkeleton_1";
		break;
		case "GrottoSkeleton_1":
			dialog.Text = "Damn loser! That's who I am! Dad left his treasures with my brother and me, but instead of sharing and forgetting, he decided that we were still children and his idea of finding a treasure would bring us closer. Well, we got so close that it couldn't be closer!";
			Link.l1 = "I passed by all his clues, they are untouched, almost. How did you get here?";
			Link.l1.go = "GrottoSkeleton_2";
		break;
		case "GrottoSkeleton_2":
			dialog.Text = "Luigi was a smart and sneaky guy, he would sneak into his father's office and carefully study his notes. And when the old man died, he immediately went here. Well, I interrogated the household servants with passion and followed him.";
			Link.l1 = "But something went wrong?";
			Link.l1.go = "GrottoSkeleton_3";
		break;
		case "GrottoSkeleton_3":
			dialog.Text = "Everything went wrong. I caught him opening a chest and shot him in the head. The roar of the shot collapsed the roof of the cave, and I was crushed against the corpse of my stepbrother. So I lay in the dark, my face in the mess left by his head. Then I died. And now you're here.";
			Link.l1 = "A terrible fate, but a fratricide deserves no less! Die again!";
			Link.l1.go = "exit_fight";
		break;

		case "GrottoPirate":
			dialog.Text = "Has someone blabbed about where we're going? Everyone is under the knife! Sons of bitches!";
			Link.l1 = "...";
			Link.l1.go = "exit_fight_grotto";
		break;

		case "Girl":
			dialog.Text = GetSexPhrase("Monsieur", "Madam") + ", excuse me, are you captain?";
			Link.l1 = "Captain, but I don't buy anything and I only give alms at the church on Sundays.";
			Link.l1.go = "Girl_1";
		break;
		case "Girl_1":
			dialog.Text = "No, "+GetSexPhrase("monsieur", "madam")+", I am not a beggar, please listen to me! My stepfather, also a captain, a corsair, in the service of France, he...";
			Link.l1 = "A fine day, a young maiden asking for help, sounds like the beginning of an adventure. I'll listen to you.";
			Link.l1.go = "Girl_2";
			Link.l2 = "He will probably scold you for talking to strangers. I'm sorry, but I have urgent business!";
			Link.l2.go = "Exit_cancel";
		break;
		case "Girl_2":
			dialog.Text = "Thank you, Captain. My stepfather gave his soul to God the third day, leaving my mother, two brothers and me completely without funds. His sloop turned out to be mortgaged to a usurer and he was taken away for debts.";
			Link.l1 = "Mademoiselle, I was happy to help, but I have things to do...";
			Link.l1.go = "Girl_3";
		break;
		case "Girl_3":
			dialog.Text = "Wait, please. Before his death, his stepfather handed his mother this diary, said something about the inheritance and gave up the ghost. I attended a church school, I can read and write a little, but there is some kind of incomprehensible language here. Perhaps the place where he hid the treasure is indicated here! He was a corsair!";
			Link.l1 = "Or maybe there's a collection of obscene sailor songs...";
			Link.l1.go = "Girl_4";
		break;
		case "Girl_4":
			dialog.Text = "Captain, please!";
			if (sti(pchar.money) >= 7000)
			{
				Link.l1 = "Okay, I'll buy this diary. Is five thousand enough? Okay, take seven, I hope it helps your family for the first time. Take...";
				Link.l1.go = "Girl_5";
			}
			Link.l2 = "I'm not interested. Goodbye.";
			Link.l2.go = "Exit_cancel";
		break;
		case "Girl_5":
			dialog.Text = "Thank you very much, Captain! Here's the diary.";
			AddMoneyToCharacter(PChar, -7000);
			SetQuestHeader("UnexpectedInheritance");
			AddQuestRecord("UnexpectedInheritance", "1");
			AddQuestUserData("UnexpectedInheritance", "sSex", GetSexPhrase("iy", "ay"));
			pchar.UnexpectedInheritance = "part1";
			Link.l1 = "Well, we'll read it at our leisure.";
			Link.l1.go = "Girl_done";
		break;
		case "Girl_done":
			DialogExit();			
			npchar.lifeday = 0;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit_cancel":
			NextDiag.TempNode = "Girl";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;


		case "exit_fight":
			locLoad = &locations[reload_location_index];
			locLoad.box1.items.indian11 = 1;
			locLoad.box1.items.jewelry1 = 5;
			locLoad.box1.items.jewelry2 = 10;
			locLoad.box1.items.jewelry3 = 15;
			locLoad.box1.items.jewelry4 = 20;
			locLoad.box1.items.jewelry5 = 25;
			locLoad.box1.items.jewelry6 = 30;
			locLoad.box1.items.jewelry7 = 35;
			SetSkeletonsToLocation(&locations[reload_location_index]);
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;

		case "exit_fight_grotto":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			//LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);;
			for (i = 1; i <= MOD_SKILL_ENEMY_RATE; i++)
			{
				sld = CharacterFromID("UI_pirate"+i)
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			}
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
	}
}

