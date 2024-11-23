// Ришард Шамбон - контрабандист
#include "DIALOGS\english\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	bool hungry = true;
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "(Here is a cub of overgrown monsters, the extermination of which you have been engaged in the last few hours. Maybe it's just your imagination, but looking at the crab you feel its sorrow.)";
				npchar.quest.meeting = "1";
				link.l1 = "Sorry buddy, but I had no other choice. It was either my life or theirs at stake.";
				link.l1.go = "crab_meat";

				link.l2 = "Wow, I missed one. Die, you beast!";
				link.l2.go = "crab_fight";
				//link.l3 = "Нire";
				//link.l3.go = "crab_hire";


				NextDiag.TempNode = "First time";
				break;
			}
			else
			{
				if (!CheckAttribute(npchar, "quest.answer_1"))
				{
					dialog.text = "(The crab looks at you as if it is waiting for something.)";
					link.l1 = "Hungry?";
					link.l1.go = "crab_meat_1";
					link.l2 = "I'm sorry, but I have more important things to do right now.";
					link.l2.go = "exit";


				}
				else
				{
					dialog.text = "(The crab clicks its claw in greeting.)";
					link.l1 = "Hello to you too, buddy.";
					link.l1.go = "exit";

				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "crab_fight": // первая встреча
            DialogExit();
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld.SaveItemsForDead = true;
		break;

		case "crab_meat":
			dialog.text = "(The crab scratches the deck of the ship with sad understanding.)";
			link.l1 = "I don't even know if I can comfort you in any way... Damn it, now there's no one to take care of you at all. Are you hungry?";
			link.l1.go = "crab_meat_1";

		break;

		case "crab_meat_1":
			dialog.text = "(The crab clicks its claw approvingly, anticipating its treat.)";

			if (CheckCharacterItem(pchar, "food1") || CheckCharacterItem(pchar, "food2") || CheckCharacterItem(pchar, "food3") || CheckCharacterItem(pchar, "food4") || CheckCharacterItem(pchar, "food5"))
			{
				link.l1 = "Here you go!";
				link.l1.go = "crab_meat_2";
			}
			link.l2 = "Wait here, I'll get you something.";
			link.l2.go = "exit";
		break;

		case "crab_meat_2":
			dialog.text = "(The crab greedily devours food from the outstretched hand, and then unceremoniously reaches into your bag and eats all the other supplies.)";
			RemoveItems(PChar, "food1", 100);
			RemoveItems(PChar, "food2", 100);
			RemoveItems(PChar, "food3", 100);
			RemoveItems(PChar, "food4", 100);
			RemoveItems(PChar, "food5", 100);
			npchar.quest.answer_1 = "true";
			link.l1 = "Take it easy, buddy! Not all at once! Okay, I have to go. Maybe I'll look you up sometime.";
			link.l1.go = "exit";
		break;

		case "crab_hire":
			dialog.text = "(A huge crab is approaching you. Instinctively, your hand reaches for the weapon, but you leave yourself. For some reason, it seems to you that this creature has friendly intentions.)";
			link.l1 = "Crab, are you? Well, you've grown up! Did you gain that much weight on my food? Or you're someone else... Perhaps it's better for me not to know. What are you doing here?";
			link.l1.go = "crab_hire_1";
		break;
		case "crab_hire_1":
			dialog.text = "(Crab makes a series of clicking sounds)";
			link.l1 = "Damn it. I don't understand you, but I hope you can do it. You seem to be smart and not as evil as your relatives. Don't you want to run away from here with me?";
			link.l1.go = "crab_hire_2";
		break;
		case "crab_hire_2":
			dialog.text = "(The creature makes a sound that you perceive as agreement)";
			link.l1 = "I have an urgent matter, but in the meantime, get to that ship over there, I'll meet you soon.";
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			DeleteAttribute(npchar, "city");
			chrDisableReloadToLocation = false;
		/*
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");

			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.dialog.CurrentNode = "First time";
			NPChar.quest.meeting = true;
			*/



			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.loyality = MAX_LOYALITY;

			npchar.Dialog.Filename = "Enc_OfficerCrab.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Npchar.cirassId = Items_FindItemIdx("cirass5");  // предмета нет, но влияение есть
			NextDiag.CurrentNode = NextDiag.TempNode;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;

			DialogExit();
		break;


// <-- специальные реакции

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetWarriorType(npchar);
			DialogExit();
		break;
	}
}
