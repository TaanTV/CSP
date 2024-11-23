
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
		case "First":
			dialog.text = "You not afraid to show up here at this time? My respect to you.";
			link.l1 = "So this is what the tavern guests told you about?";
			link.l1.go = "Meeting";
			if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_1_man");
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_1_woman");
		break;

		case "Meeting":
			dialog.text = "Who else is it about? Here is the once legendary Armando Salazar, El Matador del Mar! However, I'm better known to the townspeople by 'Sea Butcher' nickname... ";
			link.l1 = "Yes, I heard about you. An officer of the Spanish Royal Navy, who commanded the Mute Maria. He is known as an implacable pirate hunter.";
			link.l1.go = "Meeting_2";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_2");
		break;

		case "Meeting_2":
			dialog.text = "Perhaps enough talking. I've been in this world too long. Kill me or die!";
			link.l1 = "And why does it all come down to a banal fight...";
			link.l1.go = "exit";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_3");
		break;

		case "Exit":
			NextDiag.CurrentNode = "Meeting_2";
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "ReefAssholes");
			LAi_group_SetRelation("ReefAssholes", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_Attack(npchar, Pchar);
			LAi_group_SetLookRadius("ReefAssholes", 1000.0);
			SetNoRun(npchar); //инвалид
		break;

		case "Last":
			dialog.text = "You impressed me! None of those who dared to come here before could overcome us and stayed here forever.";
			link.l1 = "It was very hard. You and your guys made me sweat a lot. And I don't feel well either.";
			link.l1.go = "Last_2";
			if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_4_man");
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_4_woman");
		break;

		case "Last_2":
			dialog.text = "My curse was that I would stay in this world in this state until I was defeated in battle. Now it's broken and I can finally go to eternal rest. As for your health, it's all a curse. With my final death, you will feel much better.";
			link.l1 = "Encouraging. And now what?";
			link.l1.go = "Last_3";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_5");
		break;

		case "Last_3":
			dialog.text = "I don't want to leave you without a present. Everything you find here in this graveyard is now available to you and it is yours. And now, goodbye!";
			link.l1 = "Rest in peace, Butcher...";
			link.l1.go = "Last_exit";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_6");
		break;

		case "Last_exit":
			UnlockAchievement("AchSalazar", 3);
			pchar.questdata.Salazar = 1;
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.questdata.Salazar = 1;
			DialogExit();
			npchar.LifeDay = 0;
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			AddCharacterHealth(pchar, 30);
			chrDisableReloadToLocation = false; //пока Салазар жив - хер, а не выход
			DeleteAttribute(loadedLocation, "box1.items");
			loadedLocation.box1.items.cirass5 = 1;
			loadedLocation.box1.items.pistol8 = 1;
			loadedLocation.box1.items.gold = 1000000;
			loadedLocation.box1.items.blade39 = 1;
			loadedLocation.box1.items.suit_3 = 1;
			loadedLocation.box1.items.chest = 5;
			loadedLocation.box1.items.icollection = 5;
			loadedLocation.box1.items.Ship_Print_1 = 1;
			LAi_LocationFightDisable(loadedLocation, false);
		break;
	}
}
