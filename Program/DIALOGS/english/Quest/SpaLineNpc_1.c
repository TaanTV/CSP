// диалоговый файл №1 на испанку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

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
            //Квест №1, спасение трёх горожан.
            if (npchar.id == "SpaPrisoner1" || npchar.id == "SpaPrisoner2" || npchar.id == "SpaPrisoner3")
            {
    			if (pchar.questTemp.State == "SaveFromMorgan_toPrison")
    			{
                    dialog.text = ""+ GetSexPhrase("Senior", "Seniorita") +", who are you?";
        			link.l1 = "To hell with talking, I'm going to set you free now and we're getting out of here. Or do you like English balanda? Spread out and head towards my ship without attracting attention. Your task is to get to my ship alive. After a while, I'll make a little mess that will distract attention, so it will be easier for you. I hope you understand everything?";
        			link.l1.go = "Step_S1_1";
                }
                else
                {
                    dialog.text = LinkRandPhrase("The Lord has heard our prayers!", "If you knew how glad we are to see you...", "Thank you to the Governor General, he has not forgotten about us...");
        			link.l1 = "Yes, yes... But please don't talk until we get out of here...";
        			link.l1.go = "exit";
                }
            }
            if (pchar.questTemp.State == "TakeRockBras_toNearestMaracaibo")// квест №3, Рок Бриазилец в каюте на абордаже
            {
    			dialog.text = "You "+ GetSexPhrase("won, damn Castilian", "won, damn Spaniard") +".";
    			link.l1 = "It's very good that you decided to give up. I came to you for a reason, but with an offer.";
    			link.l1.go = "Step_S3_1";
            }
            if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toTortuga")// квест №4, базар со слугой д'Эстре предварительный.
            {
    			dialog.text = "What did you want, "+ GetSexPhrase("monsieur", "mademoiselle") +"? The owner is not at home.";
    			link.l1 = "I see...";
    			link.l1.go = "exit";
            }
            if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toDEstre")// квест №4, базар со слугой д'Эстре
            {
    			dialog.text = "What did you want, "+ GetSexPhrase("monsieur", "mademoiselle") +"?";
    			link.l1 = "I need your master, Henri d'Estre.";
    			link.l1.go = "Step_S4_1";
            }
            if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toDEstre_1")// квест №4, базар со слугой д'Эстре
            {
    			dialog.text = ""+ GetSexPhrase("Monsieur", "Mademoiselle") +", you need to hurry up!";
    			link.l1 = "Yes, I get it.";
    			link.l1.go = "exit";
            }
            if (npchar.id == "AnryDEstre")// квест №4, базар с самим д'Эстре
            {
    			dialog.text = "Damn it, please explain immediately - why are you following me?!!";
    			link.l1 = "I needed to talk to you urgently, please excuse me, monsieur...";
    			link.l1.go = "Step_S4_2";
            }
            if (npchar.id == "LaVega_Comendant") // ==>  квест №5, фантом Мэнсфилада при штурме Ла Веги
            {
    			dialog.text = "Well, what do you say, Catalan beast?";
    			link.l1 = "Today we will end a long-standing dispute with the Buccaneers. You will all be destroyed, and Hispaniola will be inhabited only by Spanish colonists!";
    			link.l1.go = "Step_S5_1";
            }
            if (npchar.id == "Boozer") // ==>  квест №6, базар с алкашом в таверне
            {
    			dialog.text = "Eh? What do you need?!";
    			link.l1 = "Nothing special. I just wanted to give you a few coins - you're suffering, but you'll improve your health...";
    			link.l1.go = "Step_S6_1";
            }
            if (npchar.id == "Messanger" && pchar.questTemp.State == "Sp6TakeMess_waitMessanger") //квест №6, базар с голландским вестовым
            {
    			dialog.text = "What do you want?";
    			link.l1 = "I am a trusted representative of the Governor General of Curacao. I need to talk to you. Let's go to the tavern, have a chat...";
    			link.l1.go = "Step_S6_8";
    			link.l2 = "I want you to give me the diplomatic correspondence. And let's keep it quiet, or I'll let my guts out...";
    			link.l2.go = "Step_S6_11";
            }
            if (npchar.id == "Messanger" && pchar.questTemp.State == "Sp6TakeMess_Action") //квест №6, базар с голландским вестовым
            {
    			dialog.text = "I was told that Stuyvesant's confidant is waiting for me here. Who are you and what do you need?";
    			link.l1 = "It doesn't matter who I am, but I need your papers.";
    			link.l1.go = "Step_S6_13";
			}
            if (npchar.id == "OurCaptain_1") //квест №7, базар с Пардалем его на корабле до битвы
            {
    			dialog.text = "Damn it, this is not the time for politics! Ladrons are attacking me, help me!!!";
    			link.l1 = "Okay.";
    			link.l1.go = "Exit";
			}
            if (npchar.id == "OurCaptain_1" && pchar.questTemp.State == "Sp7SavePardal_GoodWork") //квест №7, базар с Пардалем его на корабле
            {
    			dialog.text = "Devil, it's the perfect time to be here! I don't even know what I would have done without your help... Tell me, to whom do I owe my salvation?";
    			link.l1 = "My name is " + GetFullName(pchar) +". And Francisco Oregon y Gascon sent me to your rescue. He learned that a squadron of French bandits came out specifically to fight with you.";
    			link.l1.go = "Step_S7_1";
			}
            if (npchar.id == "OurCaptain_1" && pchar.questTemp.State == "Sp7SavePardal_2GoodWork") //квест №7, базар с Пардалем его на корабле
            {
    			dialog.text = "We talked, and that's enough...";
    			link.l1 = "Agree...";
    			link.l1.go = "exit";
			}
            if (npchar.id == "SpaTalkOfficer" && pchar.questTemp.State == "Sp10Maracaibo_TalkWithOfficer") //квест №10, базар c оффом на выходе
            {
    			dialog.text = "Make way!!!";
    			link.l1 = "Take it easy, my dear! Where are you rushing to?";
    			link.l1.go = "Step_S10_1";
			}

		break;
//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Спасение трёх горожан. Квест №1 **********************************
 		case "Step_S1_1":
			dialog.text = "Yes, "+ GetSexPhrase("senor", "senorita") +". Thank you and may the Lord protect you!";
			link.l1 = "Amen! Now hurry up...";
			link.l1.go = "Step_S1_2";
		break;
 		case "Step_S1_2":
            AddQuestRecord("Spa_Line_1_SaveCitizens", "2");
			pchar.questTemp.State = "SaveFromMorgan_OutOfPrison";
            for (i=1; i<=3; i++)
            {
                sld = characterFromId("SpaPrisoner"+i);
                ChangeCharacterAddressGroup(sld, "PortRoyal_Prison", "goto", "goto12");
                LAi_SetActorType(sld);
                LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
                AddPassenger(pchar, sld, false);
                SetCharacterRemovable(sld, false);
            }
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
		break;
//********************************* Работа на инквизицию. Квест №3 **********************************
 		case "Step_S3_1":
			dialog.text = "What's the offer?";
			link.l1 = "Offer of a meeting with Monsignor Antonio de Souza.";
			link.l1.go = "Step_S3_2";
		break;
 		case "Step_S3_2":
			dialog.text = "I don't know who this is?";
			link.l1 = "A very important person in the Holy Inquisition, a big shot. So you're lucky.";
			link.l1.go = "Step_S3_3";
		break;
 		case "Step_S3_3":
			dialog.text = "Damn it, I'm sorry I gave up. It would be better for me to die in battle than to suffer...";
			link.l1 = "Maybe. Well, now we have to go, they are waiting for us in Santiago with impatience.";
			link.l1.go = "Step_S3_4";
		break;
 		case "Step_S3_4":
 		    pchar.questTemp.State = "TakeRockBras_RockTaken";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "5");
            pchar.quest.TakeRockBras_DieHard.over = "yes";
            Island_SetReloadEnableGlobal("Maracaibo", true);
		    QuestAboardCabinDialogQuestSurrender();
            DialogExit();
		break;
//********************************* Расследование убийства. Квест №4 **********************************
 		case "Step_S4_1":
			dialog.text = "He's here on the street, right next to the house. He was in a hurry to get somewhere, but he was stopped by a familiar filibuster talking a minute ago. He will finish the conversation quickly and run about his business. So if you want to catch him, hurry up.";
			link.l1 = "Okay, I'll hurry...";
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp4Detection_toDEstre_1";
			pchar.quest.Sp4Detection_Race_1.win_condition.l1 = "location";
			pchar.quest.Sp4Detection_Race_1.win_condition.l1.location = "Tortuga_town";
			pchar.quest.Sp4Detection_Race_1.win_condition = "Sp4Detection_Race_1";
    	    NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
		break;
 		case "Step_S4_2":
			dialog.text = "Okay, I'm sorry... Who do I have the honor to talk to?";
			link.l1 = "My name is " + GetFullName(pchar) + ". I'm going to find out from you who is Donna Anna, whom you delivered to Monsieur d'Ogeron?";
			link.l1.go = "Step_S4_3";
		break;
 		case "Step_S4_3":
			dialog.text = "You, "+ GetSexPhrase("sir", "miss") +", you're poking your nose in the wrong place. It may end very badly for you...";
			link.l1 = "I know that. But nevertheless, I will ask you again: is Donna Anna the wife, and now the widow, of the Commandant of Havana, Don Juan Ramirez de Leyva?";
			link.l1.go = "Step_S4_4";
		break;
 		case "Step_S4_4":
			dialog.text = "If that's the case, then what?";
			link.l1 = "Then, sir, I have to kill you.";
			link.l1.go = "Step_S4_5";
		break;
 		case "Step_S4_5":
			dialog.text = "A very straightforward statement. Well, why immediately - and kill? Personally, as far as I remember correctly, I did not cause any harm to you. Don't think that I'm scared, I just need to understand the reason for your appearance here.";
			link.l1 = "The reason is simple - the laws of honor. You have encroached on something that does not belong to you - another man's woman. At the same time, five people were killed!";
			link.l1.go = "Step_S4_6";
		break;
 		case "Step_S4_6":
			dialog.text = "Uh-oh, yes, you are very aware of this adventure of mine, you even know how many Spanish devils I sent to the next world... I'm impressed. So who are you, "+ GetSexPhrase("sir", "miss") +"?";
			link.l1 = "I am a Spanish privateer, and I am currently investigating the murder of the commandant of Havana and the disappearance of his widow. Yes, I completely forgot - on behalf of the Governor General of Havana, Don Francisco Oregon y Gascon.";
			link.l1.go = "Step_S4_7";
		break;
 		case "Step_S4_7":
			dialog.text = "Yeah, now everything is clear to me, and I can safely send you to the next world. To arms, "+ GetSexPhrase("senor", "senorita") +"!";
			link.l1 = "Absolutely, sir!";
			link.l1.go = "Step_S4_8";
		break;
 		case "Step_S4_8":
            LAi_SetPlayerType(pchar);
			pchar.questTemp.State = "Sp4Detection_toDEstre_2";
            LAi_SetHP(npchar, 300, 300);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Sp4Detection_YouWin");
    	    NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Уничтожение Ла Веги. Квест №5 **********************************
 		case "Step_S5_1":
			dialog.text = "Agrx, "+ GetSexPhrase("Spanish dog", "Spanish trash") +"! The old buccaneer will sell his life dearly...";
			link.l1 = "Yes, it's time to end all this...";
			link.l1.go = "Step_S5_2";
			AfterTownBattle();
		break;
 		case "Step_S5_2":
            LAi_SetPlayerType(pchar);
            LAi_group_MoveCharacter(npchar, LAI_GROUP_TmpEnemy);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "Sp5LaVegaAttack_AfterFight");
    	    NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			SetReturn_Gover_Dialog_Exit(NPChar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Перехват посыльного Сювесанта. Квест №6 **********************************
 		case "Step_S6_1": //алкаш
			dialog.text = "Oh, this is the right thing to do! Give me the money...";
			link.l1 = "Do something for me first, then you'll get your money.";
			link.l1.go = "Step_S6_2";
		break;
 		case "Step_S6_2":
			dialog.text = "K-heh, but I was glad... What should I do?";
			link.l1 = "After a while, a Dutchman will leave the residence and head to the port, to the ship. You need to tell him that I, Governor General Stuyvesant's confidant, am waiting for him in the tavern room upstairs.";
			link.l1.go = "Step_S6_3";
		break;
 		case "Step_S6_3":
			dialog.text = "And how much will you give me?";
			link.l1 = "Hmm, well, you can safely count on a hundred.";
			link.l1.go = "Step_S6_4";
		break;
 		case "Step_S6_4":
			dialog.text = "One hundred coins now and I'll do it. And so I can't move from my place - I have a terrible hangover...";
			link.l1 = "Keep your money. And get to work, I'm waiting.";
			link.l1.go = "Step_S6_5";
		break;
 		case "Step_S6_5":
			dialog.text = "Don't worry, I'll have a drink now and you'll be fine...";
			link.l1 = "Hurry up with a drink, don't miss the messenger. And remember, I'm waiting for the Dutchman in the tavern room upstairs!";
			link.l1.go = "Step_S6_6";
            AddMoneyToCharacter(pchar, -100);
		break;
 		case "Step_S6_6":
			pchar.questTemp.State = "Sp6TakeMess_Action";
			AddQuestRecord("Spa_Line_6_TakeMessangeer", "4");
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, "Tortuga_tavern", "tables", LAi_FindNearestFreeLocator("tables", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
            Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition.l1 = "location";
            Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition.l1.location = "Tortuga_tavern_upstairs";
            Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition = "Sp6TakeMess_WaitMessanger";
			pchar.quest.Sp6TakeMess_Interception.over = "yes";
			LocatorReloadEnterDisable("Tortuga_tavern", "reload1_back", true);
            DialogExit();
		break;
		//=====>>> вестовой при попытке взять его в городе.
		case "Step_S6_11":
			dialog.text = "Hmm, come on, try it...";
			link.l1 = "Argh!";
			link.l1.go = "Step_S6_7";
		break;
 		case "Step_S6_7":
			LAi_RemoveCheckMinHP(sld);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
		break;
 		case "Step_S6_8":
			dialog.text = NPCStringReactionRepeat("If you want to tell me something, then tell me immediately and here.",
                          "You again? I told you I'm not going anywhere!", "That's it, you've tired me out... Guards, hold "+ GetSexPhrase("him", "her") +", he is a spy!", "none", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Let's go to the tavern...", "Listen...", "Oh, what?!", "none", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S6_9", "Step_S6_12", "Step_S6_7", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S6_9":
			dialog.text = "I'm not going to go to any tavern. Tell me, what do you have for me?";
			link.l1 = "You know... um...";
			link.l1.go = "Step_S6_10";
		break;
 		case "Step_S6_10":
			dialog.text = "Understand... I'll probably report your strange actions to the port... I guess it won't be so easy for you to leave this city now.";
			link.l1 = "Hmm...";
			link.l1.go = "Step_S6_12";
		break;
 		case "Step_S6_12":
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "Sp6TakeMess_MessengerOut", -1);
            LAi_Actor2WaitDialog(npchar, pchar);
            DialogExit();
		break;
		//=====>>> вестовой захвате в комнате таверны.
 		case "Step_S6_13":
			dialog.text = "This is a diplomatic correspondence, you are taking a big risk...";
			link.l1 = "I know, but if you don't give them to me voluntarily, then I'll have to take them off your body. Choose – life or papers.";
			link.l1.go = "Step_S6_14";
		break;
 		case "Step_S6_14":
			dialog.text = "Both life and paper! Perhaps I'd better look at the color of your blood...";
			link.l1 = "Hmm, well, as you know...";
			link.l1.go = "Step_S6_15";
		break;
		case "Step_S6_15":
			bDisableFastReload = false; // открыть переходы.
			LocatorReloadEnterDisable("Tortuga_tavern", "reload1_back", false);
			LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Спасение Пардаля. Квест №7 **********************************
 		case "Step_S7_1":
			dialog.text = "So I owe him as much as I owe you. Very well, I will have the opportunity to thank him.";
			link.l1 = "Excellent. Well, I must return to Havana to the Governor-General. We need to report to him on the successful completion of the case.";
			link.l1.go = "Step_S7_2";
		break;
 		case "Step_S7_2":
			dialog.text = "I'll probably stay in these waters for a while. Maybe I'll get lucky...";
			link.l1 = "I wish you good luck, Manoel. Goodbye.";
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp7SavePardal_2GoodWork";
		break;
//********************************* Спасение Пардаля. Квест №7 **********************************
 		case "Step_S10_1":
			dialog.text = "The British!!";
			link.l1 = "What did you say?";
			link.l1.go = "Step_S10_2";
		break;
 		case "Step_S10_2":
			dialog.text = "I said that a squadron of English pirates is moving towards the city! Damn it, there's going to be a fight! It's not for nothing that we've been preparing lately...";
			link.l1 = "It looks like I'm on time...";
			link.l1.go = "Step_S10_3";
		break;
 		case "Step_S10_3":
			dialog.text = "What? Ah, make way, "+ GetSexPhrase("senor", "senorita") +", I need to notify the Governor General...";
			link.l1 = "Come in, officer.";
			link.l1.go = "Step_S10_4";
		break;
 		case "Step_S10_4":
			pchar.questTemp.State = "Sp10Maracaibo_toGovernor";
			AddQuestRecord("Spa_Line_10_Maracaibo", "2");
			AddQuestUserData("Spa_Line_10_Maracaibo", "sSex", GetSexPhrase("", "a"));
			LocatorReloadEnterDisable("Maracaibo_town", "gate_back", true);
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", true);
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
            DialogExit();
		break;




    }
}
