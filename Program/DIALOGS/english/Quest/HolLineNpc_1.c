// диалоговый файл №1 на голландку
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
            if (npchar.id == "Bandit2" && pchar.questTemp.State == "SeekChumakeiro_ToAaronHouse")// перехват на бандитов, грябящих Аарона
            {
    			dialog.text = "Get lost while you're safe...";
    			link.l1 = "My name is "+ GetFullName(pchar) +". I'm looking for Aaron Mendes Chumaceiro.";
    			link.l1.go = "Step_H1_1";
            }// Аарон собственной персоной, после драки с грабителями
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekChumakeiro_ToAaronHouse")
            {
    			dialog.text = "It seems you saved my skin! Who are you and what are you doing here?";
    			link.l1 = "My name is "+ GetFullName(pchar) +". I'm looking for Aaron Mendes Chumaceiro.";
    			link.l1.go = "Step_H1_3";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekChumakeiro_GoToVillemstad")
            {
    			dialog.text = "I am grateful to you for a successful journey. And I am doubly grateful that you showed up in San Martin on time. I hope we'll meet again.";
    			link.l1 = "With pleasure.";
    			link.l1.go = "Step_H1_6";
            }// Квест №3, лейтенант в тюрьме.
            if (npchar.id == "Alan_MacLine" && pchar.questTemp.State == "WormEnglPlans_SaveOfficer")
            {
    			dialog.text = "Hmm, this is the first time I've seen you... Who are you?";
    			link.l1 = "I'm here to set you free!";
    			link.l1.go = "Step_H3_1";
            } // Квест №5, базар в Ла Веге о гибели Мэнсфилда
            if (npchar.id == "Talker" && pchar.questTemp.State == "ThreeFleutes_toLaVega")
            {
    			dialog.text = "Oh, you appeared in a sad time... Mansfield is dead.";
    			link.l1 = "How was he killed?!";
    			link.l1.go = "Step_H5_1";
            } // Квест №7, незнакомец на Тортуге
            if (npchar.id == "Stranger_HL7" && pchar.questTemp.State == "DelivLettTortuga_SnapMeeting")
            {
    			dialog.text = "Tell me, are you none other than messenger of the Governor General of Curaсao?";
    			link.l1 = "What did you want?";
    			link.l1.go = "Step_H7_1";
            } // Квест №7, Антонио в комнате таверны
            if (npchar.id == "AntonioDeBarras" && pchar.questTemp.State == "DelivLettTortuga_toStranger")
            {
    			dialog.text = "Ah, here you are, finally...";
    			link.l1 = "Did you want to see me? Who are you?";
    			link.l1.go = "Step_H7_4";
            }
            if (pchar.questTemp.State == "DelivLettTortuga_NotFoundLetter")
            {
    			dialog.text = "Damn it! I didn't think to see you again, and even so quickly...";
    			link.l1 = "Hello, Antonio. Let's continue our entertaining conversation. Only now everything will go according to my rules.";
    			link.l1.go = "Step_H7_6";
            } // Квест №8, Аарон даёт задание
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_toAaron")
            {
    			dialog.text = "Glad to see you, "+ GetSexPhrase("my friend", "" + pchar.name + "") +". Why have you come?";
    			link.l1 = "Mynheer, I'm seconded at your disposal by Peter Stuyvesant.";
    			link.l1.go = "Step_H8_1";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_toBermudes")
            {
    			dialog.text = "I look forward to your report on the search.";
    			link.l1 = "I'm doing this, the results will be...";
    			link.l1.go = "exit";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_DeGrafIsDead")
            {
    			dialog.text = "I look forward to your report on the search.";
    			link.l1 = "Mynheer, I managed to find out who was selling the Christian book I was looking for. This filibuster's name is Laurent de Graf. Or rather, they called him, since he died. When I went before him, off the coast of Cartagena, he fought a battle with a very powerful Spanish squadron. I was unable to save his frigate, Laurent himself sank along with the ship. I'm afraid that's all, it's just impossible to find the book now.";
    			link.l1.go = "Step_H8_12";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_DeGrafDieHard")
            {
    			dialog.text = "I look forward to your report on the search.";
    			link.l1 = "Mynheer, I managed to find out who was selling the Christian book I was looking for. This filibuster's name is Laurent de Graf. I found him near Cartagena, he was fighting with a very powerful Spanish squadron. I couldn't help de Graaf, the forces were too unequal. I had to leave the battlefield.";
    			link.l1.go = "Step_H8_12";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_BadResult")
            {
    			dialog.text = "I have nothing more to say to you. Go to Stuyvesant.";
    			link.l1 = "Okay, mynheer.";
    			link.l1.go = "exit";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_WeWon")
            {
    			dialog.text = "I look forward to your report on the search.";
    			link.l1 = "I couldn't find anything. I am forced to end the search.";
    			link.l1.go = "Step_H8_12";
    			link.l2 = "I'm always looking, fighting, drowning Spaniards... But I've not found book yet... However, I will continue to search...";
    			link.l2.go = "exit";
			}
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_IHaveMap")
            {
                dialog.text = "I look forward to your report on the search.";
    			link.l1 = "I couldn't find anything. I am forced to end the search.";
    			link.l1.go = "Step_H8_12";
				if (CheckCharacterItem(pchar, "Bible"))
				{
           			link.l2 = "I managed to get some book. I don't know if this is what you're looking for, but there's definitely a cross on the cover.";
        			link.l2.go = "Step_H8_13";
                }
                else
                {
        			link.l2 = "I haven't managed to find the book yet, but I am in search. You need to wait...";
        			link.l2.go = "exit";
                }
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_GoodResult")
            {
    			dialog.text = "I and our entire community are praying for you...";
    			link.l1 = "Heh, thanks...";
    			link.l1.go = "exit";
            }

        break;

//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Дилоги бандитов, грабящих Аарона. Квест №1 **********************************
 		case "Step_H1_1":
			dialog.text = "I told you to get out, or I'll gut you.";
			link.l1 = "Actually, I am against this approach, I value my guts very much. But it looks like it's time to take a look at your guts...";
			link.l1.go = "Step_H1_2";
		break;
 		case "Step_H1_2":
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_H1_3":
			dialog.text = "It's me.";
			link.l1 = "Peter Stuyvesant sent me to pick you up, I owe take you to Curacao. And what were these rude people doing in your house?";
			link.l1.go = "Step_H1_4";
		break;
 		case "Step_H1_4":
			dialog.text = "It looks like they robbed me. The fact is that I've been waiting for a person from Peter for the third day, and when they knocked on the door, I didn't even ask who it was before opening it. In one minute, I was twisted and thrown into this room, and the robbers themselves actively began to gut my personal belongings.";
			link.l1 = "Well, all's well that ends well. Pack up and welcome aboard my sailboat. Stuyvesant is waiting for you, we will leave immediately.";
			link.l1.go = "Step_H1_5";
		break;
 		case "Step_H1_5":
            AddQuestRecord("Hol_Line_1_Chumakeiro", "2");
			AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex", GetSexPhrase("ate", "la"));
	AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex1", GetSexPhrase("", "a"));
		    pchar.questTemp.State = "SeekChumakeiro_GoToVillemstad";
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
            //ChangeCharacterReputation(pchar, 5); TO_DO eddy
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            Pchar.quest.SeekChumakeiro_intoResidence.win_condition.l1 = "location";
            Pchar.quest.SeekChumakeiro_intoResidence.win_condition.l1.location = "Villemstad_townhall";
            Pchar.quest.SeekChumakeiro_intoResidence.win_condition = "SeekChumakeiro_intoResidence";
			DialogExit();
		break;
 		case "Step_H1_6":
			dialog.text = "Now, I'd like you to accept a small reward from me - 30,000 piastres.";
			link.l1 = "I will not refuse, thank you.";
			link.l1.go = "Step_H1_7";
		break;
 		case "Step_H1_7":
            LAi_SetPlayerType(pchar);
			AddMoneyToCharacter(pchar, 30000);
			RemovePassenger(pchar, npchar);
			AddQuestRecord("Hol_Line_1_Chumakeiro", "3");
			AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex", GetSexPhrase("", "a"));
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DialogExit();
		break;

//********************************* Дилоги лейтенанта в тюрьме. Квест №3 **********************************
 		case "Step_H3_1":
			dialog.text = "Wow, that's great! To what do I owe such attention to my person and such participation in my fate?";
			link.l1 = "I need to know something from you.";
			link.l1.go = "Step_H3_2";
		break;
 		case "Step_H3_2":
			dialog.text = "Everything is at your service. But first, let's choose a more peaceful place for such an entertaining conversation.";
			link.l1 = "I promise that I will set you free. But first I have to get the information I need. I want to know where Madiford is preparing the landing.";
			link.l1.go = "Step_H3_3";
		break;
 		case "Step_H3_3":
			dialog.text = "The Dutch Fort Orange will be taken and destroyed.";
			link.l1 = "Damn it, everything pointed to that! I keep my word.: You're free to go anywhere. Goodbye.";
			link.l1.go = "Step_H3_4";
		break;
 		case "Step_H3_4":
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
            LAi_SetHuberType(characterFromId("Henry Morgan"));
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "14");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("", "a"));
 		    pchar.questTemp.State = "WormEnglPlans_GoodRusultWorm";
            ChangeCharacterAddressGroup(npchar, "SentJons_prison", "goto", "goto23");
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
            DialogExit();
		break;

//********************************* Базар в Ла Веге о гибели Мэнсфилда. Квест №5 **********************************
  		case "Step_H5_1":
			dialog.text = "Spaniards attacked us. A good half of the people died.";
			link.l1 = "Wow! It's a pity for Edward, he was a great old man.";
			link.l1.go = "Step_H5_2";
		break;
 		case "Step_H5_2":
			chrDisableReloadToLocation = false;
 		    AddQuestRecord("Hol_Line_5_ThreeFleutes", "2");
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
            Pchar.quest.ThreeFleutes_BackToCuracao.win_condition.l1 = "location";
            Pchar.quest.ThreeFleutes_BackToCuracao.win_condition.l1.location = "Hispaniola1";
            Pchar.quest.ThreeFleutes_BackToCuracao.win_condition = "ThreeFleutes_BackToCuracao";
            DialogExit();
		break;

//********************************* Базар с незнакомцем на Тортуге. Квест №7 **********************************
  		case "Step_H7_1":
			dialog.text = "Stuyvesant's confidant is waiting for you at the tavern.";
			link.l1 = "And what does the person need from me?";
			link.l1.go = "Step_H7_2";
		break;
  		case "Step_H7_2":
			dialog.text = "Urgent order from the Governor-General, you need to read it immediately.";
			link.l1 = "Hmm... well, good.";
			link.l1.go = "Step_H7_3";
		break;
  		case "Step_H7_3":
			chrDisableReloadToLocation = false;
			pchar.questTemp.State = "DelivLettTortuga_toStranger";
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 40.0);
            LAi_SetPlayerType(pchar);
            sld = GetCharacter(NPC_GenerateCharacter("AntonioDeBarras", "officer_9", "man", "man", 40, SPAIN, -1, true));
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
        	sld.name 	= "Antonio";
        	sld.lastname = "de Barras";
        	LAi_SetStayTypeNoGroup(sld);
            FantomMakeCoolSailor(sld, SHIP_INGERMANLAND, "Isabella", CANNON_TYPE_CULVERINE_LBS32, 100, 100, 100);
            FantomMakeCoolFighter(sld, 40, 100, 100, "blade32", "pistol5", 150);
          	ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
            DialogExit();
		break;

        case "Step_H7_4":
			dialog.text = "My name is Antonio, but that's it, by the way. In the meantime, "+
                          "Well, well! Look who came to us!";
			link.l1 = "Eh?";
			link.l1.go = "Step_H7_5";
		break;
  		case "Step_H7_5":
            LocatorReloadEnterDisable("Tortuga_town", "gate_back", false);
            LocatorReloadEnterDisable("Tortuga_town", "reload1_back", false);
            LocatorReloadEnterDisable("Tortuga_town", "reload2_back", false);
            LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
            LAi_SetActorType(npchar);
            LAi_SetActorType(pchar);
            LAi_ActorTurnToLocator(pchar, "reload", "reload1_back");
            DoQuestFunctionDelay("DelivLettTortuga_Digress", 1.0);
            DialogExit();
		break;

        case "Step_H7_6":
			dialog.text = "And what will these rules be?";
			link.l1 = "You will answer the questions, for each incorrect answer I will cut off one of your fingers. Ten wrong answers - there will be no fingers on your hands. Are the rules clear?";
			link.l1.go = "Step_H7_7";
		break;
        case "Step_H7_7":
			dialog.text = "Hmm... You know, at this particular moment, my limbs are very dear to me. So ask your questions, I'll tell you everything.";
			link.l1 = "Question number one: who are you and what were you doing on Tortuga?";
			link.l1.go = "Step_H7_8";
		break;
        case "Step_H7_8":
			dialog.text = "My name is Antonio de Barras, I am a Spanish agent. I wasn't waiting for you at Tortuga, I was just waiting for a messenger from Stuyvesant. It is not difficult to identify a Dutch ship entering the port. Well, when you directly went to d'Ogeron - everything became clear.";
			link.l1 = "Okay... Question number two: where is the dispatch?";
			link.l1.go = "Step_H7_9";
		break;
        case "Step_H7_9":
			dialog.text = "I have it. Please take it...";
			link.l1 = "Very good, I'm glad for your fingers... Well, that's enough for that, the rest is in Willemstad. I hope you will do me the favor, Senor Antonio, to visit this glorious Dutch city?";
			link.l1.go = "Step_H7_10";
            GiveItem2Character(pchar, "letter_1");
		break;
        case "Step_H7_10":
			dialog.text = "I'm afraid that in this particular case my wish will not be taken into account...";
			link.l1 = "It won't, Senor Antonio, that's right.";
			link.l1.go = "Step_H7_11";
		break;
        case "Step_H7_11":
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "11");
            pchar.questTemp.State = "DelivLettTortuga_LetterFound";
            pchar.quest.DelivLettTortuga_WarshipDieHard.over = "yes";
            pchar.quest.DelivLettTortuga_AfterWarshipSunk.over = "yes";
            Island_SetReloadEnableGlobal("SantaCatalina", true);
            QuestAboardCabinDialogSurrender();
            DialogExit();
		break;

//********************************* Поиски Библии. Квест №8 **********************************
        case "Step_H8_1":
			dialog.text = "Oh, it's great that you will be the one to help me in my search. I've already seen you in action.";
			link.l1 = "What kind of searches are we talking about? Stuyvesant didn't say anything specific...";
			link.l1.go = "Step_H8_2";
		break;
        case "Step_H8_2":
			dialog.text = "That's right, "+ GetSexPhrase("my friend", "" + pchar.name + "") +"

. But first things first.\n"+
                          "Samuel Kohano was the first Yansen to flee Europe to Curaçao about twenty years ago. He was a very wealthy man, and on one occasion he managed to buy a very, very mysterious document from the Inquisition Office in Seville, with fabulous money. This is another Gospel.\n"+
                          "Being a Christian, have you probably read the Old and New Testaments?";
			link.l1 = "What can I say, not without it...";
			link.l1.go = "Step_H8_3";
		break;
        case "Step_H8_3":
			dialog.text = "Did you know that the biblical texts that we currently have are not primary sources, so to speak...";
			link.l1 = "What is this supposed to mean?";
			link.l1.go = "Step_H8_4";
		break;
        case "Step_H8_4":
			dialog.text = "The fact is that the Bible was not written immediately after the Resurrection of Christ. It took quite a long time before the strengthened church took care of the need to collect and classify Christian material in order to bring the faith to uniform dogmas\n"+
                          "That's when a detailed revision of everything that was in the hands of the church at that time took place. When the information was collected and analyzed, it turned out that some things directly contradict each other. Then a church council was held at the highest level, where decisions were made as to whether a particular document could be considered true.";
			link.l1 = "Very interesting. But what does this have to do with my assignment?";
			link.l1.go = "Step_H8_5";
		break;
        case "Step_H8_5":
			dialog.text = "Patience, my friend, and everything will become clear to you.\n"+ 
                          "So, a lot of things were recognized as heresy and were either destroyed or hidden so deeply and securely that it was not possible to bring it back to the light of Day. But Samuel succeeded! For an astronomical sum, he managed to bribe a Jesuit archivist and he stole a hitherto unknown Gospel from the secret vaults of the Inquisition!\n"+
                          "Samuel immediately fled the Old World, but misfortunes followed him literally at every step. As a result, this richest and most worthy man lost everything, was sold into slavery and perished on sugar cane plantations somewhere here in the English settlements.";
			link.l1 = "I must find the place of his death?";
			link.l1.go = "Step_H8_6";
		break;
        case "Step_H8_6":
			dialog.text = "No, it doesn't make any sense. You must find the missing tract.";
			link.l1 = "I can't even imagine what you can cling to, where to start looking...";
			link.l1.go = "Step_H8_7";
		break;
        case "Step_H8_7":
			dialog.text = "There is a clue, it was she who was the catalyst for what I begged you from Stuyvesant.";
			link.l1 = "I'm listening to you carefully, Aaron.";
			link.l1.go = "Step_H8_8";
		break;
        case "Step_H8_8":
			dialog.text = "I have heard rumors that one of the English privateers in a pirate settlement in Bermudes intended to sell an old Christian book written in a language unknown to him.";
			link.l1 = "Hmm, but if the language is unknown, then how did he determine that the book is Christian?";
			link.l1.go = "Step_H8_9";
		break;
        case "Step_H8_9":
			dialog.text = "According to the images of the crucifixion on the book, my friend.";
			link.l1 = "Understood... Okay, what's this pirate's name?";
			link.l1.go = "Step_H8_10";
		break;
        case "Step_H8_10":
			dialog.text = "I do not know.";
			link.l1 = "That's how... Well, I suppose I can find out his name and where this book is now.";
			link.l1.go = "Step_H8_11";
		break;
        case "Step_H8_11":
			dialog.text = "I am almost one hundred percent sure of this. Get started, "+ GetSexPhrase("my friend", "" + pchar.name + "") +". If successful, the reward will be very high.";
			link.l1 = "This encouraging news will undoubtedly give me zeal. See you later, Aaron, I'll start searching immediately.";
			link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_toBermudes";
            AddQuestRecord("Hol_Line_8_SeekBible", "2");
            QuestSetCurrentNode("Jackman", "HolLine8_quest");
		break;
        case "Step_H8_12":
			dialog.text = "This is very, very bad... Well, I don't need you anymore. Go back to Stuyvesant.";
			link.l1 = "Okay, mynheer.";
			link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_BadResult";
            NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
		break;
        case "Step_H8_13":
			dialog.text = "So, let's take a look... Yes, that's exactly what we've lost! You have found the lost treasure of Samuel Cohen! God, Thank You!!!";
			link.l1 = "Now, and always, and forever. Amen.";
			link.l1.go = "Step_H8_14";
			TakeItemFromCharacter(pchar, "Bible");
		break;
        case "Step_H8_14":
			dialog.text = GetFullName(pchar) + ", I promised you that your reward would be very high. How much would you rate your work?";
			link.l1 = "Well, I had overhead, I spent 235 thousand on purchase. Anything you offer me over this amount will be a reward.";
			link.l1.go = "Step_H8_15";
		break;
        case "Step_H8_15":
			dialog.text = "In addition to this, I will offer you one million. And the boundless respect of our community until the end of the century, which, by the way, will come soon...";
			link.l1 = "Heh, a million is not bad, even very good! Why are you talking about the end of the world?";
			link.l1.go = "Step_H8_16";
		break;
        case "Step_H8_16":
			dialog.text = "The mortal existence of mankind on this earth is a tragedy of people. But soon everything will be back to normal, back to where it started...";
			link.l1 = "Are you serious about this? Damn it, they ruined my whole mood from receiving such a significant amount. Well, all right... You, perhaps, expect the denouement of your tragedy, and I will deal with more prosaic things - vanity of vanities. With such a sum in my pocket, this personal tragedy of my existence will give me a lot of pleasant moments.";
			link.l1.go = "Step_H8_17";
		break;
        case "Step_H8_17":
			dialog.text = "Goodbye, and may the Lord protect you!";
			link.l1 = "And all the best to you. Goodbye.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1235000);
            pchar.questTemp.State = "SeekBible_GoodResult";
            AddQuestRecord("Hol_Line_8_SeekBible", "10");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("", "a"));
            NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
		break;
    }
}
