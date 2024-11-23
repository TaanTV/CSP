void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank;
	string attr;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase("My God, it's good that I met you!",
				"Finally, someone has appeared here!!",
				"My God, I'm so glad to see you!");
			Link.l1 = LinkRandPhrase("What's wrong, baby?",
				"What's the problem, honey?",
				"Don't worry so much, it's bad for the female body. Tell me quickly, what happened there?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("My friend is so fearless, she climbed into an abandoned well!",
				"My friend climbed into an abandoned well, and she's been gone for hours!",
				"My friend disappeared into an abandoned well!");
			Link.l1 = "What the hell did she do in there?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "Oh, she's not afraid of anything! She heard somewhere that there is a dungeon down there where you can find gold, so she climbed. But I'm not such a fool, I don't set foot there...";
			Link.l1 = "And that's right, there's nothing for you to do there.";
			Link.l1.go = "Step_3";
		break;
		case "Step_3":
			dialog.text = "What should I do now? Please, for God's sake, help her!";
			Link.l1 = "Okay, I'll deal with it. And you go home, there's nothing to chill out here alone.";
			Link.l1.go = "Step_agree";
			Link.l2 = "These are your problems, I don't care about them. Goodbye...";
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //бандюганы
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirl.locationId, 1); //монстров не генерить 1 день
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirl.locationId, 1); //офицеров не пускать 1 день
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirl.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirl.locationId; //флаг для открытия релоада
				object models;
				for (i = 0; i < 10; i++)
				{
					attr = "s" + i;
					models.(attr) = "pirate_" + (i + 1);
				}
				RandomShuffle(&models);
				for (i = 0; i < 3; i++)
				{
					iRank = sti(pchar.rank) - rand(5) + rand(5);
					if (iRank < 1) iRank = 1;
					attr = "s" + i;
					sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, models.(attr), "man", "man", iRank, PIRATE, 1, true));
					SetFantomParamFromRank(sld, iRank, true);
					sld.SaveItemsForDead = true;
					sld.DontClearDead = true;
					sld.money = iRank*200+1000+rand(500);
					LAi_CharacterDisableDialog(sld);
					LAi_SetWarriorType(sld);
					LAi_warrior_SetStay(sld, true);
					//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.locationId, "quest", "quest" + i);
					LAi_group_MoveCharacter(sld, "CaveBandit");// лесник изменил группу чтобы ядом таино травить можно было
					LAi_group_FightGroups("CaveBandit", LAI_GROUP_PLAYER, true);
					i++;
				}
				pchar.quest.Enc_FriendGirl_afterGang.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Enc_FriendGirl_afterGang.win_condition.l1.location = pchar.location;
				pchar.quest.Enc_FriendGirl_afterGang.win_condition = "Enc_FriendGirl_afterGang";
			}
			else
			{ //и правда девка
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "girl_"+(rand(7)+1), "woman", "towngirl", 5, PIRATE, 1, false));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground1";//+ iTemp; //здесь рендом поведения девки: 0-помогите, 1-сама крутая
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //соотв. озвучка
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.locationId, "monsters", "monster"+(rand(9)+1));
			}
			LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterReputation(pchar, -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			//#20200315-01
            npchar.chr_ai.type.checkFight = 999999.0;
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		//#20200315-01
		case "CitizenNotBlade ":
		    npchar.chr_ai.type.checkFight = 999999.0;
            NextDiag.TempNode = "FackYou";
            dialog.text = "I don't want to talk to "+ GetSexPhrase("such a soulless idiot", "such a soulless girl") +". Get out of here!";
			Link.l1 = "Heh, bitch...";
			Link.l1.go = "exit";
		break;
		case "FackYou":
            NextDiag.TempNode = "FackYou";
            dialog.text = "I don't want to talk to "+ GetSexPhrase("such a soulless idiot", "such a soulless girl") +". Get out of here!";
			Link.l1 = "Heh, bitch...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "My God, how glad I am to see you!!";
			Link.l1 = "What's wrong, beauty?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1":
            dialog.text = "I got lost here! God, I was so scared!!!";
			Link.l1 = "Well, it's all right now. Follow me, I'll take you out. As soon as you get to the surface, go home quickly, and I hope I won't see you again!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2":
            dialog.text = "As you say, " + GetAddress_Form(NPChar) + ".";
			Link.l1 = "Good.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterReputation(pchar, 4);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Wow, someone else cares about this dungeon!";
			Link.l1 = "Beauty, what are you doing here?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1":
            dialog.text = "None of your business!";
			Link.l1 = "Wow, the answer to a million piastres...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2":
            dialog.text = "Two million... You should go your way from here, I don't care about you.";
			Link.l1 = "Heh, and I don't care about you either, actually, but your friend raised a panic upstairs...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3":
            dialog.text = "What a fool! I'm ready to shit myself out of fear, and she thinks I'm the same.";
			Link.l1 = "Yeah, you're obviously not the same. The devil in the skirt!";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4":
            dialog.text = "Take it easy with epithets! Anyway, get lost and be done with it.";
			Link.l1 = "Well, since you don't need my help...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5":
            dialog.text = "I don't need it!";
			Link.l1 = "Then goodbye and be well.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		case "Underground1_again":
            dialog.text = "You again? Get lost, I'm tired of you...";
			Link.l1 = "Hmm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
