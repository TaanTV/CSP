// Квестовые атакующий кэпа, 10 штук в комплекте.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (pchar.questTemp.Ascold == "Ascold_MummyIsLive")
            {
            	dialog.text = "You managed with my servants, it's good. Now tell me, what year is it?";
        		link.l1 = environment.date.year + "-th... What the hell is going on?!!";
        		link.l1.go = "Step_8";
            }
            if (pchar.questTemp.Ascold == "Ascold_BodyChange")
            {
            	dialog.text = "Well, that's all right now. Are you ready to fulfill your destiny?";
        		link.l1 = "What have you done?!! Listen, Leif, fucking Erickson, the world has changed a lot during this time. There are a lot of white people here now.";
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "Ascold_SkelSlave")
            {
            	dialog.text = "Now you're ready. I give you permission to leave the tomb.";
        		link.l1 = "What will happen to my body?";
        		link.l1.go = "Step_27";
            }
            if (pchar.questTemp.Ascold == "Ascold_ImMummy")
            {
            	dialog.text = "Do your job, caper.";
        		link.l1 = "Okay, Leif.";
        		link.l1.go = "exit";
            }
            if (pchar.questTemp.Ascold == "Ascold_MummyFoundItems")
            {
            	dialog.text = "Ah, here you are at last! Where are the items I sent you to get?";
                if  (CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3") && CheckCharacterItem(pchar, "indian22"))
                {
                	link.l1 = "I have them. Take it and give me my body!";
            		link.l1.go = "Step_29";
                }
                else
                {
                	link.l1 = "I don't have them...";
            		link.l1.go = "Step_30";
                }
            }
            if (pchar.questTemp.Ascold == "Ascold_BackMyBody")
            {
            	dialog.text = "Now I'm freeing you. You can go, the exit is free.";
        		link.l1 = "Thank you. I hope we won't see each other again.";
        		link.l1.go = "Step_31";
            }
            if (pchar.questTemp.Ascold == "Ascold_ReturnToAscold")
            {
            	dialog.text = "Goodbye, caper...";
        		link.l1 = "Goodbye, Leif.";
        		link.l1.go = "exit";
            }
		break;

 		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_8":
        	dialog.text = "The following is happening now - you and I are talking\n"+
                          "And the great event that I have been waiting for for six centuries has already happened -I have risen from a dream.";
    		link.l1 = "(to myself) To be torn apart! (aloud) And it looks like I woke you up...";
    		link.l1.go = "Step_9";
		break;

        case "Step_9":
        	dialog.text = "What is your name and who are you? Answer me, and you will live.";
    		link.l1 = "My name is " + GetFullName(pchar) + ". I'm a privateer.";
    		link.l1.go = "Step_10";
    		link.l2 = "Isn't the tone too high for a mangy skull?";
    		link.l2.go = "ToDeath";
		break;

        case "ToDeath":
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
    		LAi_SetPlayerType(pchar);
		    LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], false);
			LAi_SetFightMode(pchar, true);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_10":
        	dialog.text = "What does 'caper' mean?";
    		link.l1 = "A privateer is a corsair... A filibuster, a pirate...";
    		link.l1.go = "Step_11";
		break;

        case "Step_11":
        	dialog.text = "What is a 'filibuster', a 'pirate'?";
    		link.l1 = "Well, how do I explain it to you... I am free"+ GetSexPhrase("the sailor and the free warrior", "the sailor and the free bird") +". I have my own ship and I'm doing what I think is right.";
    		link.l1.go = "Step_12";
		break;

        case "Step_12":
        	dialog.text = "Haha! Yes, you and I "+ GetSexPhrase("blood brothers", "of the same blood") +"! I am happy that my plan was realized by a kindred spirit. This is a sign of great luck for me...";
    		link.l1 = "What's the idea?";
    		link.l1.go = "Step_13";
		break;

        case "Step_13":
        	dialog.text = "What's the idea? Ha ha ha.... You're here talking to me, to a man who died more than six centuries ago!"+
                          "This is my idea. So my message to the descendants has been found...";
    		link.l1 = "What... Who are you?";
    		link.l1.go = "Step_14";
		break;

        case "Step_14":
        	dialog.text = "My name is Leif Erickson. I, like you, a sailor and a warrior, am my own boss\n"+
                          "Only I have sailed the seas north of this place.";
    		link.l1 = "When I was headed here, I heard that Leif the Lucky was buried here. It's you?";
    		link.l1.go = "Step_15";
		break;

        case "Step_15":
        	dialog.text = "Yes. I am Leif the Happy, son of Eric the Red, descendant of the ancient Svions, Viking and yorsalirsfari.";
    		link.l1 = "So you're a Viking, one of the barbarian nation that ravaged Europe six hundred years ago?";
    		link.l1.go = "Step_16";
		break;

        case "Step_16":
        	dialog.text = "Viking is not a nation, corsair. Viking is a way of life, a profession of a sailor and a warrior\n"+
                          "And you, "+ GetSexPhrase("free warrior", "free sailor") +", call us barbarians? Six hundred years ago, we were the best warriors and sailors on earth. I was in Yorsalir and participated in the campaign against Rome, and my brother owned a Gardarika!";
    		link.l1 = "But how did you end up in America? Christopher Columbus discovered America 150 years ago!";
    		link.l1.go = "Step_17";
		break;

        case "Step_17":
        	dialog.text = "Do you call these big lands America? Ha ha ha. Listen to me, "+ GetSexPhrase("free corsair", "female warrior") +"\n"+
                          "In the summer of 986 AD, the Norwegian Viking Bjarni Herulfson, who was on his way to Greenland, was assigned to a new unknown land, but did not join it\n"+
                          "In the year 1000, I, Leif Erikson, set out to find this land. I found the island of Hellyland (Baffin land), then Markland (Labrador) and Winland (Newfoundland). I founded a settlement on Winland\n"+
                          "Two years later, I went further and found this big land. I stuck to her much further north.";
    		link.l1 = "It can't be! This is how America was discovered six centuries ago...";
    		link.l1.go = "Step_18";
		break;

        case "Step_18":
        	dialog.text = "I discovered this land in 1002\n"+
                          "Then I went deep into the earth and saw that this land was endless and inhabited by red-skinned people.";
    		link.l1 = "Indians...";
    		link.l1.go = "Step_19";
		break;

        case "Step_19":
        	dialog.text = "No, each tribe calls itself differently\n"+
                          "For twenty years I lived in the Toltec tribe, who revered me, a white man, as a deity. Twenty years later, I returned to the settlement I founded on Vinland and left a will there to my descendants\n"+
                          "Six hundred years later, it was fulfilled. Executed by you.";
    		link.l1 = "Great! Well, bye?..";
    		link.l1.go = "Step_20";
		break;

        case "Step_20":
        	dialog.text = "Take your time, first I'll give you a priceless gift for my release.";
    		link.l1 = "Oh, I love this business. And what kind of gift is this?";
    		link.l1.go = "Step_21";
		break;

        case "Step_21":
        	dialog.text = "Your life. I'm giving it to you as a thank you.";
    		link.l1 = "Great... Well, bye?..";
    		link.l1.go = "Step_22";
		break;

        case "Step_22":
        	dialog.text = "Take your time. For my gift, you will do something for me.";
    		link.l1 = "Hmm, and what do I owe to do?";
    		link.l1.go = "Step_23";
    		link.l2 = "The hell with it, you rotten monkey! You'd better taste the taste of steel...";
    		link.l2.go = "ToDeath";
		break;

        case "Step_23":
        	dialog.text = "I feel like there is a big city nearby. There, at the most important person in the city, are the things I need, I feel their presence\n"+
                          "You owe to bring me three crystal Toltec skulls - white, pink and blue, as well as an ancient object called a strange thing. Then I will become stronger and I will be able to rebuild my body. The world is waiting for its ruler...";
    		link.l1 = "(to myself) I just want to get out of this crypt, and I'm not going to drag anything here, look for a fool... (aloud) Okay, can I go?";
    		link.l1.go = "Step_24";
		break;

        case "Step_24":
        	dialog.text = "In general, yes. Just one more little thing, so that you can quickly return\n"+
                          "I'm taking your body for a while, and I'm giving you mine. Also for a while.";
    		link.l1 = "What?!!!";
    		link.l1.go = "Body_Change";
		break;

        case "Body_Change":
			if (findsubstr(pchar.model.animation, "mushketer" , 0) != -1) SetMainCharacterToMushketer("", false);
			LAi_SetPlayerType(pchar);
            bDisableCharacterMenu = true; //закрываем Ф2
            // ==> меняем модели
            Pchar.questTemp.Ascold.heroFaceId    = pchar.FaceId;
            Pchar.questTemp.Ascold.heroAnimation = pchar.model.animation;
			Pchar.questTemp.Ascold.reputation    = pchar.reputation;
			Pchar.questTemp.Ascold.nation		 = pchar.nation;
			Pchar.questTemp.Ascold.relation      = GetNationRelation2MainCharacter(FRANCE);
			if (CheckAttribute(pchar, "heromodel")) {Pchar.questTemp.Ascold.heromodel = pchar.heromodel; DeleteAttribute(pchar, "heromodel");}
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
            npchar.model = pchar.model;
			npchar.model.animation = pchar.model.animation;
            // FaceMaker(npchar);
			npchar.FaceId = Pchar.questTemp.Ascold.heroFaceId;
			DeleteAttribute(npchar, "heromodel");
            SetNewModelToChar(npchar);
            pchar.model = "Mummy";
            pchar.model.animation = "man";
            pchar.FaceId = 207; //мумия
            //FaceMaker(pchar);
            SetNewModelToChar(pchar);
            pchar.questTemp.Ascold = "Ascold_BodyChange";
    		LAi_SetCitizenType(npchar);

            //==> убираем офицеров
			StoreOfficers_Ascold(pchar);  // запомним офицеров во временном хранилище
            for (i=1; i<=MAX_NUM_FIGHTERS; i++)
            {
                string officers = "Fellows.Passengers.Officers."+"id"+i;
                if(CheckAttribute(pchar, officers))
                {
                     RemoveOfficersIndex(pchar, sti(pchar.(officers)));
                }
            }

            //<== убираем офицеров
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_25":
        	dialog.text = "So what?";
    		link.l1 = "And the fact that the city on the island is French, and not the Toltecs, Aztecs and other red-skinned beasts. And I can't walk around a French city like this!";
    		link.l1.go = "Step_26";
		break;

        case "Step_26":
        	dialog.text = "There is no need to walk around, the city needs to be captured. And I will give you my servants to help you, they will be enough to take the city.";
    		link.l1 = "...";
    		link.l1.go = "exit";
            for (i=1; i<=6; i++)
            {
				sld = GetCharacter(NPC_GenerateCharacter("MySkel"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 30, PIRATE, 0, true));
				FantomMakeCoolFighter(sld, 20, 70, 70, "topor2", "pistol3", 50);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+(rand(2)+1));
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
            }
            pchar.questTemp.Ascold = "Ascold_SkelSlave";
		break;

        case "Step_27":
        	dialog.text = "Don't worry about it, I'll return it to you in one piece. I don't need your body, I don't like it\n"+
                          "That's it, you can go.";
    		link.l1 = "Okay, I'll bring it all to you. In the meantime, be very careful.";
    		link.l1.go = "Step_28";
		break;

        case "Step_28":
            PChar.GenQuest.CrewSkelModeClassic = true; //команда - скелеты
  		    chrDisableReloadToLocation = false; // открыть выход из локации.
            pchar.questTemp.Ascold = "Ascold_ImMummy";
            //==> потом вернуть
            Pchar.location.from_sea.save = Pchar.location.from_sea;
            Pchar.location.from_sea = "none";
            Pchar.Ship.Crew.Quantity.save = Pchar.Ship.Crew.Quantity;
            Pchar.Ship.Crew.Quantity = 1000;
            Pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			Pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			Pchar.NationAgressivePatentDisable = true; //патент не отбирать
            ChangeCharacterAddress(characterFromID("Ascold"), "None", "");
            //<== потом вернуть
            Pchar.quest.Ascold_MummyFightTown.win_condition.l1 = "location";
            Pchar.quest.Ascold_MummyFightTown.win_condition.l1.location = "BasTer_ExitTown";
            Pchar.quest.Ascold_MummyFightTown.win_condition = "Ascold_MummyFightTown";

            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_29":
            DeleteAttribute(PChar, "GenQuest.CrewSkelModeClassic"); // команда-скелеты в нормальное сост.
            bDisableCharacterMenu = false; //открываем Ф2
            bDisableLandEncounters = false;
            TakeItemFromCharacter(pchar, "sculMa1");
            TakeItemFromCharacter(pchar, "sculMa2");
            TakeItemFromCharacter(pchar, "sculMa3");
            TakeItemFromCharacter(pchar, "indian22");
            //==> вертаем
            Pchar.location.from_sea = Pchar.location.from_sea.save;
            DeleteAttribute(PChar, "location.from_sea.save");
            Pchar.Ship.Crew.Quantity = Pchar.Ship.Crew.Quantity.save;
            DeleteAttribute(PChar, "Ship.Crew.Quantity.save");

            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Ascold")], "BasTer_houseSp1", "goto", "goto1");
           	LAi_SetStayTypeNoGroup(characterFromID("Ascold"));
           	SetLocationCapturedState("BasTer_town", false);
            // ==> возвращаем модели
            pchar.model = npchar.model;
            pchar.model.animation = Pchar.questTemp.Ascold.heroAnimation;
            pchar.FaceId          = Pchar.questTemp.Ascold.heroFaceId;
			pchar.reputation	  = Pchar.questTemp.Ascold.reputation;
			pchar.nation		  = Pchar.questTemp.Ascold.nation;
			SetNationRelation2MainCharacter(FRANCE, sti(Pchar.questTemp.Ascold.relation));
			if (CheckAttribute(Pchar, "questTemp.Ascold.heromodel")) pchar.heromodel = Pchar.questTemp.Ascold.heromodel;
            //FaceMaker(pchar);
            SetNewModelToChar(pchar);
            npchar.model = "Mummy";
			npchar.model.animation = "man";
            FaceMaker(npchar);
            SetNewModelToChar(npchar);
            DeleteAttribute(PChar, "questTemp.Ascold.heroFaceId");
            DeleteAttribute(PChar, "questTemp.Ascold.heroAnimation");
            DeleteAttribute(PChar, "questTemp.Ascold.reputation");
			DeleteAttribute(PChar, "questTemp.Ascold.relation");
			DeleteAttribute(pchar, "questTemp.Ascold.heromodel");
			DeleteAttribute(PChar, "GenQuest.HunterScore2Pause"); //вертаем начисление нзг
			DeleteAttribute(PChar, "GenQuest.ReputationNotChange"); //вертаем смену репы
			DeleteAttribute(PChar, "NationAgressivePatentDisable"); //вертаем отдачу патента
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            pchar.questTemp.Ascold = "Ascold_BackMyBody";
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_30":
        	dialog.text = "You won't get your body back until you find it.";
    		link.l1 = "I will search...";
    		link.l1.go = "exit";
		break;

        case "Step_31":
        	dialog.text = "It's in your best interest. I'm not going to give you any more priceless gifts.";
    		link.l1 = "I understand. Well, be healthy, if I may say so...";
    		link.l1.go = "exit";
    		chrDisableReloadToLocation = false; // открыть выход из локации.
			bDisableFastReload = false;
    		pchar.questTemp.Ascold = "Ascold_ReturnToAscold";
    		characters[GetCharacterIndex("Ascold")].dialog.currentnode = "AfterAttackMummy";
		break;
	}
}


