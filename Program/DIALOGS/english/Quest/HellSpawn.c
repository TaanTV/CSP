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

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Brother in non-life, what did you need at the entrance to the church?";
            link.l1 = "Where else did you come from?";
            link.l1.go = "HS_1";
			link.l2 = "It's none of your business. Don't bother me.";
            link.l2.go = "HS_2";
			link.l3 = "I was asked to take a donation.";
            link.l3.go = "HS_2";
		break;

		case "HS_1":
			dialog.text = "We've been looking out for you for a long time. And we don't really like what we see.";
			link.l1 = "And what did you see?";
			link.l1.go = "HS_2";
		break;
		case "HS_2":
			dialog.text = "You serve mortals! You fulfill their vile whims, while not even demanding anything in return! We can't bear to watch this. The brothel mistress's errand was the last straw. Do you think that this way you can get closer to their normal life? To be reborn? This is not going to happen! There is one ritual, but by your actions you have only made yourself unworthy of it, even to pitiful mortals, now you will see how this city will burn down with them.";
			link.l1 = "I won't let this happen.";
			link.l1.go = "HS_fight";
		break;

		case "HS_fight":
			DialogExit();
			Lai_SetPlayerType(pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			//LocatorReloadEnterDisable(pchar.HellSpawnLocation, "reload7_back", false);

			string cnd;
			for (int i = 1; i<15; i++)
			{
				cnd = "l" + i;
				sld = characterFromID("HellSpawn"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				PChar.quest.HellSpawnFinish.win_condition.(cnd) = "NPC_Death";
				PChar.quest.HellSpawnFinish.win_condition.(cnd).character = sld.id;
			}
			pchar.quest.HellSpawnFinish.function = "HellSpawnFinish";
		break;

		case "Ritual":
			dialog.text = "Why did you come here? Do you want to interrupt our rebirth ritual?";
			link.l1 = "Opposite. I want to join you.";
			link.l1.go = "Ritual_1";
			link.l2 = "Yes. People like you don't deserve the gift of life.";
			link.l2.go = "Ritual_fight";
		break;

		case "Ritual_1":
			dialog.text = "Many have been waiting for their turn for hundreds of years. You're not worthy yet.";
			link.l1 = "Now we'll see who deserves what here.";
			link.l1.go = "Ritual_fight";
		break;

		case "Ritual_fight":
			DialogExit();
			Lai_SetPlayerType(pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			ref RitualLocLoad = &locations[reload_location_index];
			cnd;
			for (i = 1; i<sti(pchar.Hellspawn.num); i++)
			{
				cnd = "l" + i;
				sld = characterFromID("HellSpawnR"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				PChar.quest.HellSpawnRitualFinish.win_condition.(cnd) = "NPC_Death";
				PChar.quest.HellSpawnRitualFinish.win_condition.(cnd).character = sld.id;
			}
			pchar.quest.HellSpawnRitualFinish.function = "HellSpawnRitualFinish";

		break;
	}
}
