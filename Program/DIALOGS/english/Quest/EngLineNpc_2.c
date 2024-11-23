// Герцог Альбермаль и другие
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;

    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = "Nothing to talk about.";
			link.l1 = "Okay...";
            link.l1.go = "exit";

//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
            // ==> Боцман Морриса Уильямса
            if (pchar.questTemp.State == "MorrisWillams_ModifordGood5000" && npchar.id == "Bocman_Willams")// перехват на посыльного Морриса Уильямса
            {
    			dialog.text = "Hey, Captain, seems that you're going to sea?";
    			link.l1 = "Yes, I'm leaving. What do you care about that and who are you?";
    			link.l1.go = "Step_E6_1";
            }
            if (pchar.questTemp.State == "MorrisWillams_GoToHimselfBussines" && npchar.id == "Bocman_Willams")// перехват на посыльного Морриса Уильямса второй раз
            {
    			dialog.text = "Captain, good afternoon. It's me again, the boatswain from the Favorite.";
    			link.l1 = "What do you say this time?";
    			link.l1.go = "Step_E6_4";
            }
			// ==> Джилиан Эттербери.
			if (pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfoWomen" && npchar.id == "Gillian Atterbury") // англ.линейка квест №6, разговор с Джиллиан Эттербери
            {
    			dialog.text = "What do you want from me?";
                link.l2 = "Listen, the holy father advised me to contact you.";
                link.l2.go = "Step_E6_25";
            }
			if (pchar.questTemp.State == "MorrisWillams_SeekHusband" && npchar.id == "Gillian Atterbury") // англ.линейка квест №6, разговор с Джиллиан Эттербери после дачи задания
            {
    			dialog.text = "Have you found out anything about my husband, "+ GetSexPhrase("sir", "miss") +"?";
    			link.l1 = "Not yet, but I'm doing it. I will do my best to find him.";
    			link.l1.go = "exit";
            }
			if (npchar.id == "Gillian Atterbury" && CheckAttribute(npchar, "TempQuest.SavedHusband")) // разговор с Джиллиан Эттербери, если мы спасли её мужа
            {
                dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Sir", "Miss") +", I will never forget what you have done for us. You saved my husband's life and saved our family from debt. We will name our child after you.",
                         "It's you again, "+ GetSexPhrase("sir", "miss") +". I'm so glad to see you!", ""+ GetSexPhrase("Sir", "Miss") +", we are seeing you for the umpteenth time today. It's just wonderful!",
                         ""+ GetSexPhrase("Sir", "Miss") +"no matter how much you contact me, know that I am always glad to see you.", "block", 1, npchar, Dialog.CurrentNode);
    			link.l1 = HeroStringReactionRepeat("Come on, it's empty... But you know, it's still nice...",
                                               "Well...",
                                               "I think so too...",
                                               "Hmm, how nice! Thank you.", npchar, Dialog.CurrentNode);
    			link.l1.go = "exit";
    			//ChangeCharacterReputation(pchar, 1); // чит, но вряд ли кто-то найдёт TO_DO eddy
            }
            // ==> Один из бандитов в пещере, удерживающий мужа Джилиан
            if (pchar.questTemp.State == "MorrisWillams_SeekHusband" && npchar.id == "Bandit3")   // базар в пещере перед боевкой
            {
    			dialog.text = "Damn...";
    			link.l1 = "Who are you and what are you doing here?!!";
    			link.l1.go = "Step_E6_30";
            }
            // ==> Муж Джилиан
            if (pchar.questTemp.State == "MorrisWillams_AfterFight" && npchar.id == "Jillians_Husband")   // базар в пещере с мужем, англ.линейка, квест №6
            {
    			dialog.text = "You saved my life! Thank you!";
    			link.l1 = "Thanks later. Is your name Tom Ettrebury?";
    			link.l1.go = "Step_E6_32";
            }
            // ==> Спасишийся перец в поселении буканьеров
            if (pchar.questTemp.State == "ToMansfield_GoOn")   // разговор со спасшимся перцем, анл.линейка, квест №8
            {
    			dialog.text = "English privateer! Thank the Lord!";
    			link.l1 = "What happened here?";
    			link.l1.go = "Step_E8_1";
            }
            if (pchar.questTemp.State == "ToMansfield_CatchToPardal")   // остаточный разговор со спасшимся перцем
            {
    			dialog.text = "You need to hurry. The galleons left almost a day ago, you may not make it.";
    			link.l1 = "Yes, I know. Indeed, we need to hurry...";
    			link.l1.go = "exit";
            }


        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//*************************************** Диалог боцмана Морриса Уильямса *********************************
 		case "Step_E6_1":
			dialog.text = "I am the boatswain from the frigate Favorit. Just recently I saw you on our deck, you talked to cap...";
			link.l1 = "That's right, go on.";
			link.l1.go = "Step_E6_2";
		break;

 		case "Step_E6_2":
			dialog.text = "Our cap is in the tavern, he has already drunk a whole barrel of rum. He sent me to find you. He's waiting, it's urgent.";
			link.l1 = "Okay, I'm coming immediately.";
			link.l1.go = "Step_E6_3";
		break;

 		case "Step_E6_3":
			chrDisableReloadToLocation = false;
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 40.0);
            LAi_SetPlayerType(pchar);
            sld = characterFromID("Morris_Willams");
            LAi_SetHuberTypeNoGroup(sld);
			FreeSitLocator("PortRoyal_tavern", "sit10");
            ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit10");
            LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true); //на всякий случай, чтобы геймер не слинял.
            LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
            NextDiag.TempNode = "First time";
            DialogExit();
		break;

 		case "Step_E6_4":
			dialog.text = "There is little good, or rather, nothing at all. Our Capt Williams has just been arrested on the way out of the tavern\n"+
                          "About ten soldiers surrounded him, the commandant showed him some paper, and Cap was taken away.";
			link.l1 = "And you didn't stand up for him? Where is your team?";
			link.l1.go = "Step_E6_5";
		break;

 		case "Step_E6_5":
			dialog.text = "There is no command, Captain, everyone has fled. There are only a few people left on the ship. And the ship has also been arrested..\n"+
                          "In general, things are going badly, very badly...";
			link.l1 = "I'm going to the commandant to find out what's what. Don't drift, go to your boat and keep order. I'll get your captain out, you can be sure.";
			link.l1.go = "Step_E6_6";
		break;

 		case "Step_E6_6":
			chrDisableReloadToLocation = false;
    	    npchar.LifeDay = 1; // уберём нпс на след.день.
    	    SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			pchar.questTemp.State = "MorrisWillams_ArrestedToPrison";
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 40.0);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "15");
            ref sld = characterFromID("Morris_Willams");
			LAi_SetStayType(sld);
            ChangeCharacterAddressGroup(sld, "PortRoyal_prison", "goto", "goto9");
            RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
            LAi_SetPlayerType(pchar);
			DialogExit();
		break;

//*********************************** Диалоги Джиллиан Эттербери *************************************
		case "Step_E6_25":
			dialog.text = "What's the matter, "+ GetSexPhrase("sir", "miss") +"?";
			link.l1 = "Don't be scared, I won't hurt you. I just need to settle a score with a usurer. As far as I understand, we have common interests.";
			link.l1.go = "Step_E6_26";
		break;

        case "Step_E6_26":
			dialog.text = "(crying) "+ GetSexPhrase("Sir", "Miss") +", it's terrible. My husband Tom is missing.";
			link.l1 = "Calm down and tell us more details, please.";
			link.l1.go = "Step_E6_27";
		break;

        case "Step_E6_27":
			dialog.text = "We owed the usurer money and did not pay the debt on time. Then he came to our house and told my husband that he would throw him in jail if we did not repay the debt with interest within a week\n"+
                     "We gave everything we had, but it did not cover the interest accrued over the year on the amount of debt\n"+
                     "My husband asked him for a delay in payment, but received only another week of time to refund the remaining amount\n"+
                     "Then my husband went to look for money. He didn't get any money, but he learned something that, according to him, will allow us not to be afraid of being in prison\n"+
                     "Yesterday he was in town all day, then he dropped in for a minute, packed up and went out into the night. He still hasn't returned. I am very afraid!";
			link.l1 = "Where did he go? Did he say anything at all?";
			link.l1.go = "Step_E6_28";
		break;

        case "Step_E6_28":
			dialog.text = "He only said that he was going out of town. Nothing else, he was in a hurry (crying). "+ GetSexPhrase("Sir", "Miss") +"I beg you, help me find my husband!";
			link.l1 = "I will do my best.";
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_SeekHusband";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "20");
            Pchar.quest.MorrisWillams_HusbandInCave.win_condition.l1 = "location";
            Pchar.quest.MorrisWillams_HusbandInCave.win_condition.l1.location = "Jamaica_Grot";
            Pchar.quest.MorrisWillams_HusbandInCave.win_condition = "MorrisWillams_HusbandInCave";
		break;



//**************************** Диалоги бандита в пещере, поиски мужа Джиллиан ****************************
 		case "Step_E6_30":
			dialog.text = "Finish "+ GetSexPhrase("his", "her") +", we don't need witnesses...";
			link.l1 = "Hmm...";
			link.l1.go = "Step_E6_31";
		break;

 		case "Step_E6_31":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "MorrisWillams_AftreFightingInCave");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

//************************************** Диалоги мужа Джиллиан ***********************************
 		case "Step_E6_32":
			dialog.text = "Yes, but how do you know? Although I don't care, I'm glad to see you more than the Archangel Gabriel!";
			link.l1 = "Tell me what happened?";
			link.l1.go = "Step_E6_33";
		break;

 		case "Step_E6_33":
			dialog.text = "I don't even know where to start... About a year ago, we borrowed money from a usurer...";
			link.l1 = "I know all this, tell me from the moment you left the city at night. What have you found out about the usurer?";
			link.l1.go = "Step_E6_34";
		break;

 		case "Step_E6_34":
			dialog.text = "This devil turned out to be associated with smugglers! Yesterday I noticed that a strange stranger came into his house from the back door. I waited for him to come out and went after him\n"+
                          "I managed to follow him almost to this place when I was ambushed. They grabbed me and dragged me here. They wanted to kill me, but decided to find out who I was first, and maybe make money from my capture\n"+
                          "You were on time, "+ GetSexPhrase("sir", "miss") +". Thank you from the bottom of my heart!";
			link.l1 = "Everything is clear. Now run to the city to your wife, she is very scared of your disappearance. Consider that your debt to the usurer is not there. But don't tell anyone about this case, and it's better to leave the city.";
			link.l1.go = "Step_E6_35";
		break;

 		case "Step_E6_35":
			Characters[GetCharacterIndex("Gillian Atterbury")].TempQuest.SavedHusband = 1; // чтоб Джиллиан помнила об услуге...
            AddQuestRecord("Eng_Line_6_MorrisWillams", "21");
            LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
            //ChangeCharacterReputation(pchar, 5); TO_DO eddy
            pchar.questTemp.State = "MorrisWillams_AfterFightGoRedmond";
			DialogExit();
		break;

//************************************** Диалоги спасшегося буканьера ***********************************
  		case "Step_E8_1":
			dialog.text = "Spaniards on three galleons approached the bay, landed and took our settlement by storm.";
			link.l1 = "Damn it! Where's Mansfield?";
			link.l1.go = "Step_E8_2";
		break;

   		case "Step_E8_2":
			dialog.text = "Killed, like many others. About half of the Buccaneers managed to retreat from the settlement. And it's good that they left, otherwise the end would have come to everyone.";
			link.l1 = "I don't recognize the Buccaneers. When did you retreat before the Spaniards?";
			link.l1.go = "Step_E8_3";
		break;

   		case "Step_E8_3":
			dialog.text = "There were a lot of them and they were armed as well as they could be\n"+
                          "They took the culverins off the ships and just shot us, while we couldn't get them with rifle fire\n"+
                          "We launched a raid on the Spanish battery, but they destroyed the entire attacking group with three musket volleys\n"+
                          "None of the guys survived - these devils immediately launched a counterattack, and finished off the wounded on the way...";
			link.l1 = "Damn it! I arrived to Mansfield on behalf of Madiford. I owe to pick up the gold prepared for him.";
			link.l1.go = "Step_E8_4";
		break;

   		case "Step_E8_4":
			dialog.text = "Spaniards took everything. Mansfield is dead.";
			link.l1 = "What else can you say?";
			link.l1.go = "Step_E8_5";
		break;

   		case "Step_E8_5":
			dialog.text = "I know they went to Cuba, to Santiago.";
			link.l1 = "How do you know that?";
			link.l1.go = "Step_E8_6";
		break;

   		case "Step_E8_6":
			dialog.text = "When the Spaniards broke in here, I pretended to be dead and lay there, to the side\n"+
                          "I understand a little Spanish and I heard their captain talking, they called him Manoel\n"+
                          "They searched the settlement, loaded everything they found onto ships and left for Santiago. Anyway, we were preparing for this. Judging by the conversation, they came from Santiago.";
			link.l1 = "Manoel... Is this not Manoel Rivero Pardal? The only Spanish corsair in these waters? Hm... Okay, thank you. Your comrades will be back soon. Tell them that I will take revenge.";
			link.l1.go = "Step_E8_7";
		break;

   		case "Step_E8_7":
			dialog.text = "Thank you. If you want to catch the Spaniards on the way, then hurry up.";
			link.l1 = "Don't worry, I'll catch up with the galleons.";
			link.l1.go = "exit";
			pchar.questTemp.State = "ToMansfield_CatchToPardal";
			AddQuestRecord("Eng_Line_8_ToMansfield", "2");
			
			Pchar.quest.ToMansfield_OutFromFort.win_condition.l1 = "location";
			Pchar.quest.ToMansfield_OutFromFort.win_condition.l1.location = "LaVega_town";
			Pchar.quest.ToMansfield_OutFromFort.win_condition = "ToMansfield_OutFromFort";
		break;

        case "You_baster":
            dialog.text = "I never imagined that you would do this to me...";
            link.l1 = "I quote you, sir: 'I have nothing more to say to you. Politics rules the fates of states, nothing to think about the fates of individual... governors-general.' Goodbye.";
            link.l1.go = "exit";
            NextDiag.TempNode = "You_baster";
			pchar.questTemp.jailCanMove = true;
        break;
    }
}
