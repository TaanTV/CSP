// диалоговый файл №2 на испанку
void ProcessDialogEvent()
{
	ref NPChar, sld;
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
            if (npchar.id == "Francisco")// квест №2, базар с Франциско
            {
    			dialog.text = "It's you "+ GetSexPhrase("the person who got it", "the girl who got it") +"an assignment from Antonio de Souza?";
    			link.l1 = "I just left him.";
    			link.l1.go = "Step_S2_1";
            }
            if (CheckAttribute(pchar, "questTemp.State.Usurer"))// квест №2, малый де Фонкейсао
            {
    			dialog.text = "I give up, you won!";
    			link.l1 = "Jansen Noonan de Foncacao himself, if I'm not mistaken...";
    			link.l1.go = "Step_S2_6";
            }
            if (npchar.id == "Bandit" && CheckAttribute(pchar, "questTemp.State.Store"))// квест №2, бандит на 1-м этаже
            {
    			dialog.text = "What do you need here? Get out!";
    			link.l1 = "Hey, take it easy! What kind of manners?";
    			link.l1.go = "Step_S2_11";
            }
			if (npchar.id == "JacowDeFonseka" && CheckAttribute(pchar, "questTemp.State.Store"))
			{
                dialog.text = "Who are you? How do you know me? Do we know each other? How did you know where I am?";
    			link.l1 = "Stop! Stop, dear. I'll tell you everything, just let me set you free first. You won't mind that, will you?";
    			link.l1.go = "Step_S2_14";
            }
			if (npchar.id == "PortMansBoy")  //квест №6, посыльный начальника порта.
			{
                dialog.text = ""+ GetSexPhrase("Monsieur", "Mademoiselle") +", the portmaster sent me to you.";
    			link.l1 = "Yes, very good. What did he tell me to tell you?";
    			link.l1.go = "Step_S6_1";
            }	//квест №7, Моисей Воклейн.
 			if (pchar.questTemp.State == "Sp7SavePardal_toAntigua" || pchar.questTemp.State == "Sp7SavePardal_PardalIsSink")
			{
                dialog.text = "The devil!!! It all started so well - we caught Pardal... And then you...";
    			link.l1 = "Hmm, that's why I showed up, so your good beginnings wouldn't end so well...";
    			link.l1.go = "Step_S7_1";
            }  //квест №8, капитан Ансель.
 			if (pchar.questTemp.State == "Sp8SaveCumana_toCumana")
			{
                dialog.text = "Argh, damn Spanish dog!";
    			link.l1 = "Let's continue, Captain, let's not get distracted...";
    			link.l1.go = "exit";
				LAi_SetCurHPMax(npchar);
				QuestAboardCabinDialogExitWithBattle("");
            }
		break;

//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//*************************** Квест №2, диалоги с Франциско на выходе из Инквизиии ***************************
 		case "Step_S2_1":
			dialog.text = "I know what your task is, and I know how it can end. It is beneficial for the Order to improve its financial affairs at the expense of merchants, especially with someone else's hands.";
			link.l1 = "Do you think that's the only question?";
			link.l1.go = "Step_S2_2";
		break;
 		case "Step_S2_2":
			dialog.text = "Perhaps not, but you should remember one thing - if you are faced with the question of killing merchants, then please think carefully about why you are taking the lives of these people. You don't know them, they can be good believers and good citizens.";
			link.l1 = "How can they be good believers if they are Jansenists?!";
			link.l1.go = "Step_S2_3";
		break;
 		case "Step_S2_3":
			dialog.text = "They believe in the same Lord as you and me. Think about it...";
			link.l1 = "I'll take note of your words. But who do I have the honor to communicate with?";
			link.l1.go = "Step_S2_4";
		break;
 		case "Step_S2_4":
			dialog.text = "Francisco de San Agostinho.";
			link.l1 = "Thank you, Francisco. Have a nice day.";
			link.l1.go = "Step_S2_5";
		break;
 		case "Step_S2_5":
			chrDisableReloadToLocation = false;
			pchar.questTemp.State = "Inquisition_afterFrancisco";
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 40.0);
            LAi_SetPlayerType(pchar);
            DialogExit();
		break;
 		case "Step_S2_6":
			dialog.text = "That's right... And how do you know me?";
			link.l1 = "A girl told me, her name is Tanneken Clemens. Do you know one?";
			link.l1.go = "Step_S2_7";
		break;
 		case "Step_S2_7":
			dialog.text = "Damn it! And what these girls don't do to get married! It's necessary to hire thugs!";
			link.l1 = "She didn't hire me, our interests just coincided at the moment...";
			link.l1.go = "Step_S2_8";
		break;
 		case "Step_S2_8":
			dialog.text = "Ugh, that's better... You know, it's too early for me to start a family yet... What do you want from me?";
			link.l1 = "Nothing from you. I need something from your father. You'll sit in my hold for a while, think about your family, about children, about eternal human values... In the meantime, your dad and I will discuss something.";
			link.l1.go = "Step_S2_9";
		break;
 		case "Step_S2_9":
			dialog.text = "Not the worst option in my current position. Thanks for not killing me.";
			link.l1 = "Thank Tanneken, she asked me not to touch you, you bastard... Well, that's it.";
			link.l1.go = "Step_S2_10";
		break;
 		case "Step_S2_10":
            AddQuestRecord("Spa_Line_2_Inquisition", "8");
            pchar.quest.Inquisition_DieHard.over = "yes";
            Island_SetReloadEnableGlobal("Jamaica", true);
            QuestAboardCabinDialogQuestSurrender();
            DialogExit();
		break;
 		case "Step_S2_11":
			dialog.text = "Get lost, I'm telling you. Tired of living?!";
			link.l1 = "Hmm, something is wrong here... I'm not going anywhere until you answer me one question. What are you doing here? Is it Jacob Lopez de Fonseca who is being held captive by you?";
			link.l1.go = "Step_S2_12";
		break;
 		case "Step_S2_12":
			dialog.text = "So... It's time for you to die, talker...";
			link.l1 = "It's not for you to determine the length of my life...";
			link.l1.go = "Step_S2_13";
		break;
 		case "Step_S2_13":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_S2_14":
			dialog.text = "Of course I won't. It's me out of excitement. I no longer have any hope of liberation, and I am not used to waiting for miracles. I heard these bandits discussing the price of my ransom and one of them has probably already reached Curacao\n"+
                          "But how did you get here so quickly? And you still haven't told me your name.";
			link.l1 = "" + GetFullName(pchar) + ", at your service. Well... My ship is waiting in Porto Bello, we can leave.";
			link.l1.go = "Step_S2_15";
		break;
 		case "Step_S2_15":
			dialog.text = "I don't want to sound annoying, but seeing how you handled and dealt with these people, I realized that you are a military man"+ GetSexPhrase("", ", though a girl") +". I want to ask you a favor\n"+
                          "It's on the way from here to Curacao. I have no right to insist, I can only ask you. The fact is that our community owned an ancient Christian relic - the Gospel of Judas Iscariot.";
			link.l1 = "Owned?";
			link.l1.go = "Step_S2_16";
		break;
 		case "Step_S2_16":
			dialog.text = "She's been missing for about 20 years with her guardian, Samuel Coheno.";
			link.l1 = "I've already heard this name somewhere...";
			link.l1.go = "Step_S2_17";
		break;
 		case "Step_S2_17":
			dialog.text = "It's unlikely. So, recently we got on the trail of the kidnapper, he showed up in Bermudes. Attempts to buy the relic from him failed, so we hired sailors from the tavern. The thief turned out to be surprisingly strong and even injured several people, after which he rushed to run. The sailors followed him closely and caught up with him at the shipyard. But there he fell through the ground.";
			link.l1 = "How is it?";
			link.l1.go = "Step_S2_18";
		break;
 		case "Step_S2_18":
			dialog.text = "He went into the shipyard office and that was it. Where he went is completely unclear. The owner of the shipyard has not told us anything. I'm asking you to help me get the book back. Will you help me?";
			link.l1 = "How much do you think this book might cost?";
			link.l1.go = "Step_S2_19";
		break;
 		case "Step_S2_19":
			dialog.text = "She is priceless! But why are you asking about this?";
			link.l1 = "The protection of Christian relics is the sacred duty of every true Catholic... But I haven't decided anything yet, let's see under the circumstances.";
			link.l1.go = "Step_S2_20";
		break;
 		case "Step_S2_20":
			dialog.text = "Thank you!";
			link.l1 = "Not yet.";
			link.l1.go = "Step_S2_21";
		break;
 		case "Step_S2_21":
 		    LAi_SetPlayerType(pchar);
            AddQuestRecord("Spa_Line_2_Inquisition", "12");
            AddQuestRecord("Spa_Line_2_Inquisition", "13");
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
            pchar.questTemp.State.SeekBible = 1; //флаг на поиск Евангелие
            LocatorReloadEnterDisable("Shore3", "reload2_back", true); //закрываем для особо хитрых
            DialogExit();
		break;
//*************************** Квест №6, базар с посыльным начальника порта ***************************
 		case "Step_S6_1":
			dialog.text = "The ship you are expecting has anchored in the Tortuga raid. The messenger, a Dutch officer, is now at d'Ogeron, you can meet him a little later at the exit of the residence.";
			link.l1 = "Great! Thank you for your service.";
			link.l1.go = "Step_S6_2";
		break;
 		case "Step_S6_2":
			dialog.text = "You're welcome. Thank the portmaster.";
			link.l1 = "Hmm, I will definitely thank you.";
			link.l1.go = "Step_S6_3";
		break;
 		case "Step_S6_3":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Spa_Line_6_TakeMessangeer", "3");
			bDisableFastReload = true; //закрываем фаст релоад
			SaveCurrentQuestDateParam("questTemp");
			Pchar.quest.Sp6TakeMess_Interception.win_condition.l1 = "location";
            Pchar.quest.Sp6TakeMess_Interception.win_condition.l1.location = "Tortuga_town";
            Pchar.quest.Sp6TakeMess_Interception.win_condition = "Sp6TakeMess_Interception";
            LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
            DialogExit();
		break;
//*************************** Квест №7, базар с Моисеем Воклейном при абордаже ***************************
 		case "Step_S7_1":
			dialog.text = "Well, you did it... Having rested, I suggest we continue.";
			link.l1 = "With great pleasure...";
			link.l1.go = "exit";
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
		break;


    }
}


