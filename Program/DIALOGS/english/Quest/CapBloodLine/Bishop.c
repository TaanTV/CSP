// Блад
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sLocator;
    int iTime, n;
    string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

/*
	switch(Pchar.questTemp.CapBloodLine.stat)
    {
  		case "1":
            Dialog.CurrentNode = "First Bishop";
		break;

		case "2":
            Dialog.CurrentNode = "First Guard";
		break;

		case "3":
            Dialog.CurrentNode = "First Stid";
		break;

		case "4":
            Dialog.CurrentNode = "First MsStid";
		break;

    }
    */


	switch(Dialog.CurrentNode)
	{
	    // --> Бишоп
		// ----------------------------------- Диалог первый - первая встреча
		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Exit_Away":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorGoToLocation(npchar, "reload", Pchar.questTemp.CapBloodLine.sLocator, "none", "", "", "", sti(Pchar.questTemp.CapBloodLine.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

        case "Exit_RunAway":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", Pchar.questTemp.CapBloodLine.sLocator, "none", "", "", "", sti(Pchar.questTemp.CapBloodLine.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

        case "GFight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
            sld = &characters[GetCharacterIndex("Dragun_0")];
            LAi_SetCheckMinHP(sld, 1, true, "Dragun_0_CheckMinHP");
            LAi_SetImmortal(sld, false);
   	        LAi_SetWarriorTypeNoGroup(sld);//fix
   	        LAi_warrior_DialogEnable(sld, false);//fix
            LAi_group_MoveCharacter(sld, "TmpEnemy");
            //LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
            LAi_group_Attack(sld, Pchar);
            LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);//fix
            LAi_group_SetHearRadius("TmpEnemy", 3000.0); //fix
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_ActorRunToLocation(NPChar, "goto", "goto6", "none", "", "", "", 20);
			LAi_ActorGoToLocator(NPChar, "goto", "goto6", "", -1);

		break;

        case "fight1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");
            LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true)
			AddDialogExitQuest("MainHeroFightModeOn");
			Spain_spyDie("");
			AddQuestRecord("WeaponsForEscape", "5");

		break;

        case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");
            LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");

		break;

		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RestoreBridgetown();
			initMainCharacterItem();
            ref mc = GetMainCharacter();
            mc.Ship.Type = GenerateShipExt(SHIP_ARABELLA, true, mc);
            mc.Ship.name="Arabella";
            SetBaseShipData(mc);
            mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
            SetCrewQuantityFull(mc);

            SetCharacterGoods(mc,GOOD_FOOD,2000);
        	SetCharacterGoods(mc,GOOD_BALLS,2000);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,400);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,2000);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,2000);
            SetCharacterGoods(mc,GOOD_PLANKS,10);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,2000);//2000);
            DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;

        case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery in broad daylight!!! What is this that is being done?! Well, wait, buddy...", "Hey, what are you doing there?! No way, you're trying to rob me? Well, then you're finished...", "Wait, where are you going? You're a thief, it turns out! Well, consider that you have sailed, dear...");
			link.l1 = LinkRandPhrase("Devil!!", "Carramba!!", "Oh, damn!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			//if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NextQuest":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			Pchar.questTemp.CapBloodLine.stat = "";
            CapBloodLineInit("");
		break;







		case "First time":
        	dialog.text = "Error";
            link.l1 = "...";
            link.l1.go = "Exit";
            npchar.quest.meeting = "1";

            if (npchar.id == "Pitt")
            {
     			if (bBettaTestMode)
                {
			        link.l0 = "BetaTest - skip and start the game.";
			        link.l0.go = "Finish";
                }

                if (Pchar.questTemp.CapBloodLine.stat == "Begining")
                {
                    dialog.text = "Lord Gildoy is seriously injured... he is here in the house... I dragged him there... He sent me to get you... Hurry up to him! Hurry up!";
            		link.l1 = "Thank you, Pitt... I'll go to him, and you stay here, and if you see the royal dragoons galloping here, warn us immediately.";
                    link.l1.go = "Exit_Away";
                    Pchar.questTemp.CapBloodLine.sLocator = "reload1";
                    Pchar.questTemp.CapBloodLine.iTime = -1;
           			if (bBettaTestMode)
                    {
				        link.l3 = "BetaTest - To the second quest.";
				        link.l3.go = "NextQuest";
                    }
            		break;
        		}

                if (Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
                {
                    dialog.text = "Peter, Colonel Bishop has been looking for you all evening, the governor's wife has another attack. You need to go to Governor Steed's residence urgently.";
            		link.l1 = "Thanks, Pitt, he told me.";
            		link.l1.go = "Exit";
            		break;
        		}
                if (Pchar.questTemp.CapBloodLine.stat == "WakerOfferComplited")
                {
                    dialog.text = "How are you doing, my friend?";
            		link.l1 = "Keep your voice down, because our future fate is at stake, colleague.";
            		link.l1.go = "PStep_0";
            		break;
        		}

                dialog.text = "Sorry, Peter, I have to go to work.";
        		link.l1 = "Okay, go.";
        		link.l1.go = "Exit";

    		}

            if (npchar.id == "Beyns")
            {
                dialog.text = "Oh, hello, Dr. Blood, how nice of you to come. Lord Gildoy is seriously injured... He's lying in a bedroom on the second floor, in the west wing of the house...";
        		link.l1 = "I arrived as soon as I could. I will go up to him immediately, while you prepare hot water and clean linen.";
        		link.l1.go = "EBStep_0";
    		}

            if (npchar.id == "CapGobart")
            {
                dialog.text = "I am Captain Hobart of Colonel Kirk's dragoons. Are you harboring rebels? What kind of cripple is lying on the second floor?";
        		link.l1 = "We're not harboring rebels, sir. This gentleman is injured...";
        		link.l1.go = "CGStep_1";
        		DragunInvansion4();
    		}

            if (npchar.id == "Bridgetown_Mayor" )
            {
                if( Pchar.questTemp.CapBloodLine.stat == "CureMisStid" )
                {
                    dialog.text = "I was about to send for a Wacker. Why is it taking so long?";
            		link.l1 = "I had to stay late. I'm sorry, Governor.";
            		link.l1.go = "SStep_0";
            		link.l2 = "Your people have detained me, Governor Steed. As it turns out, your orders are subject to discussion, also-some individuals are actively preventing me from treating Spanish soldiers.";
            		link.l2.go = "SStep_1";
            		break;
                }

                if( Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape3" )
                {
                    dialog.text = "Greetings, Dr. Blood. To what do I owe your visit?";
            		link.l1 = "Good afternoon, Governor. I have brought more prophylactic extract for your spouse and would like to be able to examine her.";
            		link.l1.go = "SStep_9";
            		break;
                }
                dialog.text = "What do you want, Dr. Blood?";
          		link.l1 = "No, nothing, sorry to bother you.";
          		link.l1.go = "Exit";
 		         NextDiag.TempNode = "First time";
    		}

    		if (npchar.id == "MisStid" && Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
    		{
            	dialog.text = "Oh, Dr. Blood! Finally... Please help me!";
        		link.l1 = "Good evening, Mrs. Steed. Don't worry, you have to calm down and stop squinting - be patient and look at me, I need to see your eyes.";
        		link.l1.go = "MSStep_0";
    		}

    		if (npchar.id == "Nettl" ) // && Pchar.questTemp.CapBloodLine.stat == "CureMisStid"
    		{
            	dialog.text = "Hey, man... I'm in good mind and... and... well. What a hello... In good health? Oh, yes, sober... Yes, sober. Do you know how to use it? disappear somewhere, and... and then appear somewhere... somewhere completely out of place... not where he disappeared?";
	            if( Pchar.questTemp.CapBloodLine.stat == "needMoney")
                {
                	link.l1 = "I must admit that I know just one similar trick.";
                    link.l1.go = "NStep_6";
                }
                else
                {
            		link.l1 = "I'd like to know that myself, old man.";
            		link.l1.go = "NStep_0";
                }
    		}

    		if (npchar.id == "Waker")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
                {
                	dialog.text = "Dr. Blood, how glad I am to see you! I was looking for you today, but my search was unsuccessful - you move around the city like a ghost.";
            		link.l1 = "Life has taught me. Where can I find Mr. Dan?" ;
            		link.l1.go = "WStep_0";
            		link.l2 = "Good evening. Where can I find Mr. Dan?";
            		link.l2.go = "WStep_1";
                }

                if(Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
                {
                	dialog.text = "I hear Mrs. Steed is taking up a lot of your time. Well, youth and good looks, Dr. Blood! Youth and beauty! This gives the doctor a huge advantage, especially when he treats ladies!";
            		link.l1 = "I think I guess your idea. Share it not with me, but with Governor Steed. Maybe it will amuse him. If that's all you have, then with your permission..." ;
            		link.l1.go = "WStep_3";

                }
    		}

    		if (npchar.id == "Den")
    		{
            	dialog.text = "Good evening, Dr. Blood. May I ask what you were doing at my house?";
        		link.l1 = "Mrs. Steed has a migraine attack, I was urgently called to her. I examined her and had to go to you at such a late hour to get the necessary medicine. Not finding you at home, I decided to wait, but I was about to leave." ;
        		link.l1.go = "DStep_0";
    			if (GetCharacterItem(pchar, "migraine_potion") > 0)
    			{
            			link.l2 = "Mrs. Steed has a migraine attack, I was urgently called to her. I examined her and had to go to you at such a late hour to get the necessary medicine. Having failed to find you, I allowed myself to take the medicine without permission - the situation is extremely serious. I'm sorry.";
            			link.l2.go = "DStep_1";
    			}
        		link.l3 = "I just came to tell you that Dr. Wacker was looking for you, Mr. Dan.";
        		link.l3.go = "DStep_2";
    		}



    		if (npchar.id == "Griffin")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1" && !CheckAttribute(pchar, "LockBloodWeaponsOptions"))
                {
                	dialog.text = "What the hell are you barging in without knocking, damn you... Oh, it's you, Dr. Blood!";
            		link.l1 = "Good afternoon, Mr. Griffin. I apologize for the unceremonious intrusion, but I have urgent business with you.";
            		link.l1.go = "GRStep_0";
            		break;
                }

                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape")
                {

                    dialog.text = "Who the hell are you?!";
            		link.l1 = "I am Dr. Blood, the doctor of Bridgetown." ;
            		link.l1.go = "GRStep_10";
            		break;

                }

                dialog.text = "What are you doing here, the devil take you apart?!";
                link.l1 = "I'm Dr. Blood, I'm leaving now." ;
                link.l1.go = "Exit";
    		}

    		if (npchar.id == "Hells")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1_1")
                {
                	dialog.text = "What the hell do you all want?! Defend yourself!..";
            		link.l1 = "Calm down, I'm Peter Blood, the Bridgetown doctor. I'm not going to hurt you.";
            		link.l1.go = "HStep_0";
            		link.l2 = "Since you're asking...";
            		link.l2.go = "fight1";
            		break;
                }

                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && !CheckAttribute(Pchar, "questTemp.CapBloodLine.fishplace"))
                {
                	dialog.text = "Oh, it's good that you're here...";
            		link.l1 = "How can I help you?";
            		link.l1.go = "HStep_5";
            		break;
                }

                dialog.text = "What are you doing here, the devil take you apart?!";
                link.l1 = "I'm Dr. Blood, I'm leaving now." ;
                link.l1.go = "Exit";
    		}

    		if (npchar.id == "Quest_Smuggler")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape" && sti(Pchar.reputation) > 55  && !CheckAttribute(pchar, "LockBloodWeaponsOptions"))
                {
                	dialog.text = "I've heard about you, Dr. Blood. You have become, to some extent, a star personality among the local slaves who rot on the plantations. What can I do for you?";
            		link.l1 = "With your permission, we'll keep our voices down. The thing is, I need a weapon...";
            		link.l1.go = "QSStep_0";
            		break;
                }

                dialog.text = "Hello, Dr. Blood, if they find out that you talked to me, you will be locked up to death. So you better go your own way.";
                link.l1 = "I can be flogged to death without it... Although you're right-I have to go." ;
                link.l1.go = "Exit";
    		}

    		if (npchar.id == "Spain_spy" )
    		{
            	dialog.text = "Hey, you! Wait...";
        		link.l1 = "How can I help you?";
        		link.l1.go = "SSStep_0";
    		}

    		 if(npchar.id == "Volverston")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = "Ah, Peter, glad to see you!";
                    link.l1 = "Would you like to keep me and a few of our brothers in misfortune company on the way to the Dutch colony of Curacao tomorrow night?";
                    link.l1.go = "VLStep_0";
              		break;
                }
                dialog.text = "Ah, Peter, glad to see you!.";
                link.l1 = "Hello, Wolverstone. I'm sorry, but I have to go.";
                link.l1.go = "Exit";

    		 }

    		 if(npchar.id == "Hugtorp")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = "I already know, Peter. Jeremy gave me a brief summary, but, alas, I have to refuse you.";
                    link.l1 = "But why? Are you doubting something?";
                    link.l1.go = "HTStep_1";
              		break;
                }
                dialog.text = "Greetings, Peter. The hand that you treated for me is completely healed, thank you.";
                link.l1 = "I'm glad you got better.";
                link.l1.go = "Exit";

    		 }

    		 if(npchar.id == "Dieke")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = "What can I do for you, Doctor?";
                    link.l1 = "You can, you really can, Nicholas. Has Pitt told you what we're up to?";
                    link.l1.go = "DKStep_0";
              		break;
                }
                dialog.text = "What can I do for you, Doctor?";
                link.l1 = "No, nothing, just walking by.";
                link.l1.go = "Exit";
    		 }

    		 if(npchar.id == "Ogl")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = TimeGreeting() + ", Dr. Blood.";
                    link.l1 = "How about a deal, Ogle? Is there any more life in the old dog?";
                    link.l1.go = "OGLStep_0";
              		break;
                }
                dialog.text = TimeGreeting() + ", Dr. Blood.";
                link.l1 = "Kind.";
                link.l1.go = "Exit";
    		 }



		break;


		case "First Bishop":
            if(NPChar.quest.meeting == "0")
            {
            	dialog.text = "The governor's wife has another attack. Go to Steed's residence immediately and do what you have to do. When you're done, come right here... And God forbid you end up near Spanish patients! Tomorrow I'll find something more important to occupy you with. There is...";
                link.l1 = "...there are Wacker and Bronson, whom you can always recommend to the governor, referring to my extraordinary employment on the plantation. Doctors are still the same, but still educated and hardworking people. Otherwise, if Governor Steed demands to report on the condition of the wounded, I will have to answer him, and then go to the poor people and examine them.";
                link.l1.go = "BStep_0";
                npchar.quest.meeting = "1";
            }
            else
            {
           	    dialog.text = "Get out of here, you worthless bum, or I'll have you shackled!";
                link.l1 = "Whatever you say.";
                link.l1.go = "Exit";
            }
		break;

		case "BStep_0":
        	dialog.text = "Don't interrupt me, dog!\nCure the noble Steed family, or the condescending attitude of a sick person towards you will be replaced by the cold indifference of a politician.\nThen let's see how you like hoeing the land on the plantation instead of freely wandering around the city! Remember your place, slave.";
    		link.l1 = "I suppose you're risking a lot by detaining me when Mrs. Steed needs emergency health care.";
    		link.l1.go = "Bishop_Away";
            LAi_LockFightMode(pchar, false);
            chrDisableReloadToLocation = false;
            LAi_LocationFightDisable(loadedLocation, false);
            Pchar.questTemp.CapBloodLine.stat = "CureMisStid";
            NextDiag.TempNode = "First Bishop";

            //сроки 4 часа
            PChar.quest.CapBloodLineTimer_1.win_condition.l1            = "Timer";
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.hour  = 4;
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
            PChar.quest.CapBloodLineTimer_1.function = "CapBloodLine_q1_Late";
            AddQuestRecord("CapBloodLine_q1", "1");

		break;

		case "BStep_1":
        	dialog.text = "If you stick your nose in my business, I'll have to do something, handsome, so that you don't mess around and abuse the freedom given to you. Don't forget that you are a convicted rebel!";
            link.l1 = "I am reminded of this all the time.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "BStep_1";
		break;

		case "BStep_2":
        	dialog.text = "You've been hanging around all day! As far as I know, the governor and his wife are fine. Shouldn't you block access to the city for the time being?";
            link.l1 = "Are you going to sell Nicholas Dyke?";
            link.l1.go = "BStep_3";
		break;

		case "BStep_3":
        	dialog.text = "... and then there are already rumors about you... what? Why do you care about this shit, dog?";
            link.l1 = "The thing is that he has... Hmm, he has the first signs of leprosy...";
            link.l1.go = "BStep_4";
		break;


		case "BStep_4":
        	dialog.text = "What are you talking about? Don't you dare meddle in my business, otherwise I'll send you to hoe, after whipping you half to death!..";
            link.l1 = "Responsibility for the sale will fall on...";
            link.l1.go = "BStep_5";
		break;

		case "BStep_5":
        	dialog.text = "Be silent! I am in debt to Mr. Westen, and this deal is going to happen! Get out of my sight!";
            link.l1 = "Okay.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "BStep_1";
            sld = characterFromID("Quest_Habitue");
            sld.Dialog.CurrentNode = "QHStep_0";
            AddQuestRecord("DiekeQuest", "2");

		break;

		case "Bishop_Away":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Plantation_Sp1", "goto", "goto1", "BishopOnHouse", -1);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit()
		break;

		// -->Эндрю Бейнс

		case "EBStep_0":

            dialog.text = "I will bring whatever you ask. Please hurry up, my lord is really bad!";
        	link.l1 = "I will do my best.";
            link.l1.go = "Exit_RunAway";
            DeleteAttribute(npchar, "talker");
            Pchar.questTemp.CapBloodLine.sLocator = "Reload5";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;

		case "EBStep_1":

            dialog.text = "Doctor, I have prepared everything you asked for.";
        	link.l1 = "Thank you, put it there.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "EBStep_2";
            AddDialogExitQuestFunction("CureLordMovie");

		break;

		case "EBStep_2":

            dialog.text = "What's wrong with Lord Gildoy? Will he survive?";
        	link.l1 = "The worst is over. I treated the wounds, gave him medicine, now he will recover, but he needs complete rest...";
            link.l1.go = "Exit";
            NextDiag.TempNode = "EBStep_3";
            AddDialogExitQuestFunction("DragunInvansion");

		break;

		case "EBStep_3":

            dialog.text = "I think you should take Jeremy Pitt's advice and get yourself a gun.";
        	link.l1 = "Okay, I'll do that.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "EBStep_3";

		break;

		//--> капитан Гобард

		case "CGStep_1":
        	dialog.text = "It's clear without words! There is no need to ask where this damned rebel is wounded... Get him, guys!";
    		link.l1 = "In the name of humanity, sir! We live in England, not Tangier. This man is seriously injured, he cannot be touched without danger to his life.";
    		link.l1.go = "CGStep_2";

		break;

		case "CGStep_2":
        	dialog.text = "Oh, so I still have to take care of the health of the rebels! Damn it! Do you think we're going to treat him? There are gallows all along the road from Weston to Bridgewater, and he will fit any of them. Colonel Kirk will teach these Protestant fools something that their children, grandchildren and great-grandchildren will remember!";
    		link.l1 = "Fine, but if you do, I'm afraid you might be hanged tomorrow. He doesn't belong to the category of people you can string up without asking questions. He has the right to demand a court, a court of peers.";
    		link.l1.go = "CGStep_3";

		break;

		case "CGStep_3":
        	dialog.text = "Peer courts?";
    		link.l1 = "Of course. Any person, unless he is an idiot or a savage, would have asked his last name before sending a man to the gallows. This man is Lord Gildoy.";
    		link.l1.go = "CGStep_4";

		break;

		case "CGStep_4":
        	dialog.text = "This man is a rebel, and he will be taken to Bridgewater, to prison.";
    		link.l1 = "It will not carry this path. He can't be touched right now.";
    		link.l1.go = "CGStep_5";

		break;

		case "CGStep_5":
        	dialog.text = "So much the worse for him. My job is to arrest the rebels! Who is this guy who was hiding in the fireplace? Another grandee? I'll certainly hang him with my own hands.";
    		link.l1 = "You guessed right, Captain. This is Viscount Pitt, the cousin of Sir Thomas Vernon, who is married to the beautiful Molly Kirk, your colonel's sister.";
    		link.l1.go = "CGStep_6";

		break;

		case "CGStep_6":
        	dialog.text = "You're lying, aren't you? I swear to God, he's mocking me!";
    		link.l1 = "If you are sure of this, then hang it up and see what they will do to you.";
    		link.l1.go = "CGStep_7";
		break;

		case "CGStep_7":
        	dialog.text = "The devil. Who the hell are you? And how did you end up here?";
    		link.l1 = "My name is Peter Blood, I am a doctor, and I was brought here to help the wounded.";
    		link.l1.go = "CGStep_8";
		break;

		case "CGStep_8":
        	dialog.text = "Well, who invited you? The rebels? Take him! Tie these up too. We will show you how to shelter the rebels!";
    		link.l1 = "Well, no way. I can't let that happen!";
    		link.l1.go = "GFight";
    		NextDiag.TempNode = "CGStep_9";
			EndQuestMovie();
		break;

        case "CGStep_9":
			dialog.text = LinkRandPhrase("Here he is - hold him!", "Grab him guys!", "Stop there!");
			link.l1 = LinkRandPhrase("The devil!!", "As if not so!", "Oh, damn!");
			link.l1.go = "Exit";
			AddDialogExitQuestFunction("CapGobartAttack");
            NextDiag.TempNode = "CGStep_9";
		break;


		// -->Стражник на входе

		case "First Guard":
        	dialog.text = "Where are you going?";
    		link.l1 = "My name is Peter Blood, I am here on the orders of Colonel Bishop - I have been ordered to report for the examination and treatment of the governor's wife.";
    		link.l1.go = "GStep_0";

		break;

		case "GStep_0":

            dialog.text = "Yes, I remember you. You treated my brother and the others from Pride of Devon, as well as all that Spanish scum that miraculously survived. Bronson is my friend... and you're ruining him, as well as Wacker, by doing everything and everywhere. Such tricksters are rare among slaves, and they don't live long.";
        	link.l1 = "I'm sorry, but the governor's wife is unwell at the moment, and detaining me, you risk being in the same cage with the 'Spanish scum'.";
            link.l1.go = "Exit";
            LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//отпираем резеденцию
            //LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);
            LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
            //солдата на место
            LAi_SetLoginTime(npchar, 6.0, 23.0);
            npchar.protector = false;
            npchar.protector.CheckAlways = 0;
            npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";

		break;

		case "GStep_1":

            dialog.text = "Oh, Dr. Blood! I don't know if Governor Steed is sending for you this time. What do you need?";
            if (GetCharacterItem(pchar, "migraine_potion") > 0)
            {
       	        link.l1 = "I have a medicine for the prevention of migraines in my hands. My task is to deliver it to Mrs. Steed and examine her. Do you think it's a good idea to detain me at such a moment?";
                link.l1.go = "Exit";
                LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//отпираем резеденцию
                //LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);
                LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
                //солдата на место
                npchar.protector = false;
                npchar.protector.CheckAlways = 0;
                npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";

            }
            else
            {
           	    link.l1 = "Since I'm here, it's logical to conclude that I need to get to the governor.";
                link.l1.go = "GStep_2";
            }

		break;

 		case "GStep_2":

            dialog.text = "That's how it is. But since I have stopped you, it is logical to conclude that you will not be able to enter this door until I find out about the relevant order given by Governor Steed.";
        	link.l1 = "In that case, I dare not distract you anymore.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "GStep_3";
            AddQuestRecord("WeaponsForEscape", "12");
		break;

		case "GStep_3":

            dialog.text = "Well, what else?";
            if (GetCharacterItem(pchar, "migraine_potion") > 0)
            {
       	        link.l1 = "I have a medicine for the prevention of migraines in my hands. My task is to deliver it to Mrs. Steed and examine her. Do you think it's a good idea to detain me at such a moment?";
                link.l1.go = "Exit";
                LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//отпираем резеденцию
                //LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);
                LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
                //солдата на место
                npchar.protector = false;
                npchar.protector.CheckAlways = 0;
                npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                NextDiag.TempNode = "First time";

            }
            else
            {
            	link.l1 = "I checked to see if you were alive or not.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GStep_3";
            }

		break;

        // --> Стид


 		case "SStep_0":

            ChangeCharacterReputation(PChar, 5);
            dialog.text = "Anyway, the main thing right now is my wife. She has a migraine attack again, she is overexcited and rejects all attempts to put her to bed!";
        	link.l1 = "Can I see her?";
            link.l1.go = "SStep_2";
		break;

 		case "SStep_1":

            dialog.text = "Anyway, the main thing right now is my wife. She has a migraine attack again, she is overexcited and rejects all attempts to put her to bed!";
        	link.l1 = "Can I see her?";
            link.l1.go = "SStep_2";
		break;

 		case "SStep_2":

            dialog.text = "Yes, yes, of course - she's in the bedroom on the second floor. There's a door on your right and up the stairs. Come on in.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_3";

			sld = GetCharacter(NPC_GenerateCharacter("MisStid", "AnnaDeLeiva", "woman", "towngirl2", 10, ENGLAND, 3, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
			sld.name = "Mrs.";
			sld.lastname = "Steed";
			sld.greeting = "Gr_Dama";
			sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "CommonBedroom", "goto", "goto5");
			AddQuestRecord("CapBloodLine_q1", "2");
		break;


		case "SStep_3":

            sld = &characters[GetCharacterIndex("MisStid")];
            if (sld.quest.meeting != "1")
            {
                dialog.text = "Dr. Blood, check on my wife as soon as possible.";
                link.l1 = "I'm on my way.";
                link.l1.go = "Exit";
            }
            else
            {
                dialog.text = "How is she, Doctor? You...";
                link.l1 = "Everything will be fine, Governor Steed, but I need to go to the pharmacist's house immediately to get the necessary medicines. I just thought I'd let you know.";
                link.l1.go = "SStep_4";

                link.l2 = "It will be all right, Governor Steed, if I can find Mr. Dan at home and wake him up. Medicines are urgently needed, and I ask you to give me the funds to buy them.";
                link.l2.go = "SStep_5";
            }
		break;

		case "SStep_4":

            dialog.text = "Please hurry up!";
            link.l1 = "I'm on my way.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";

		break;

		case "SStep_5":

            dialog.text = "Oh, of course, of course... How much do you need?";
            link.l1 = "500 piastres.";
            link.l1.go = "SStep_6";
            link.l2 = "1000 piastres.";
            link.l2.go = "SStep_7";
            link.l3 = "2500 piastres, sir. It's a very expencive and rare medicine.";
            link.l3.go = "SStep_8";

		break;

		case "SStep_6":

            AddMoneyToCharacter(pchar, 500);
            dialog.text = "Here, take your money.";
            link.l1 = "I have to hurry.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";
            AddQuestRecord("CapBloodLine_q1", "4");
            AddQuestUserData("CapBloodLine_q1", "iMoney", 500);

		break;

		case "SStep_7":

            AddMoneyToCharacter(pchar, 1000);
            dialog.text = "Here, take it, I hope it's for Mr Dan.";
            link.l1 = "I have to hurry.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";
            AddQuestRecord("CapBloodLine_q1", "4");
            AddQuestUserData("CapBloodLine_q1", "iMoney", 1000);

		break;

		case "SStep_8":

            AddMoneyToCharacter(pchar, 2500);
            dialog.text = "That's a lot of money, Doctor. I will give her away, but I ask you to report back - I will check everything.";
            link.l1 = "I have to hurry.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";
            AddQuestRecord("CapBloodLine_q1", "5");


		break;

		case "SStep_9":

            dialog.text = "The right word, of course, I give you this opportunity. Do you think we should be afraid of a new attack?";
            link.l1 = "I came here to prevent it, sir. With your permission...";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", false);
            LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape3_1";

		break;

        //--> Миссис Стид

        case "MSStep_0":

            dialog.text = "Is there anything you can do, Doctor?";
        	link.l1 = "It seems that there is no way to do without medicines, but the pharmacy has been closed for a long time. I'll have to go to Mr. Dan's house to get everything I need. Drink some warm water and wait for me, I'll be back as soon as I can!";
            link.l1.go = "Exit";
            NextDiag.TempNode = "MSStep_1";

            sld = GetCharacter(NPC_GenerateCharacter("Waker", "usurer_5", "man", "man", 7, ENGLAND, 3, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.name = "The doctor";
            sld.lastname = "Wacker";
            sld.greeting 	=  "Gr_medic";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
			ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "goto", "goto6");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorDialog(sld, pchar, "", 2.0, 0);

            pchar.quest.CureMisStid.win_condition.l1 = "item";
			pchar.quest.CureMisStid.win_condition.l1.item= "migraine_potion";
			pchar.quest.CureMisStid.function = "CapBloodLine_q1_End";

			sld = ItemsFromID("migraine_potion");
			sld.shown = true;
			sld.startLocation = "CommonPirateHouse";
			sld.startLocator = "item1";

			AddQuestRecord("CapBloodLine_q1", "3");


		break;

        case "MSStep_1":

            dialog.text = "Did you bring the medicine, Doctor?";
            if(Pchar.questTemp.CapBloodLine.stat == "CureMisStid_Complite")
            {
                link.l1 = "Yes, it will get you back on your feet quickly.";
                link.l1.go = "MSStep_2";
                TakeItemFromCharacter(Pchar, "migraine_potion");

            }
            else
            {
                link.l1 = "Not yet, I was just following them.";
                link.l1.go = "Exit";
            }

		break;

        case "MSStep_2":

        NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		//Вывести экран в темноту, выполнить квест questFadeOut, вернуть всё обратно, выполнить квест questFadeIn
        //LAi_Fade("", "CapBloodLine_q1_Complited");
        CapBloodLine_q1_Complited("");

		break;

        case "MSStep_3":

            dialog.text = "Hello, Dr. Blood. I'm feeling much better and it looks like I'm really on the mend - all thanks to you.";
        	link.l1 = "Thank you, Mrs. Steed. I'm here to...";
            link.l1.go = "MSStep_4";
            DeleteAttribute(npchar, "talker");

		break;

        case "MSStep_4":

            dialog.text = "I see you are not taking your eyes off this ringlet... Maybe it's yours?";
        	link.l1 = "Mm... mine?";
            link.l1.go = "MSStep_5";
           	link.l1 = "No, alas, it doesn't belong to me.";
            link.l1.go = "MSStep_5";

		break;

        case "MSStep_5":

            dialog.text = "The thing is, it's not mine either. I didn't have such a ring just yesterday, but this morning I found it where it is now. Oh, if my husband hadn't been sure that he was with me at the time of the ring's appearance, and no one could have appeared here, he would have...";
        	link.l1 = "Very interesting.";
            link.l1.go = "MSStep_6";

		break;

        case "MSStep_6":

            dialog.text = "The ring is simple, without frills. It's not my style, and... take it away, Dr. Blood. Whoever it is, I don't need it.";
        	link.l1 = "What are you, Mrs. Steed! I can't accept it... However, I can try to find out for you whose it is and how it got here.";
            link.l1.go = "MSStep_7";

		break;

        case "MSStep_7":

            dialog.text = "Let it be so. And now I have to ask you to leave me.";
        	link.l1 = "Here, I brought you some more miraculous extract, which was the original purpose of my visit. Goodbye.";
            TakeItemFromCharacter(Pchar, "migraine_potion");
            AddQuestRecord("WeaponsForEscape", "15");
            link.l1.go = "Exit";
            NextDiag.TempNode = "MSStep_8";


		break;

        case "MSStep_8":

            dialog.text = "Goodbye, Dr. Blood.";
        	link.l1 = "Goodbye.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "MSStep_8";
		break;




        //--> Нэтталл

        case "NStep_0":

            dialog.text = "Uh... If you find out... if you find out the way, then... Don't leave me, I'll help you. Great... Really.";
        	link.l1 = "Go home, you old sea wolf. You need to get some sleep.";
            link.l1.go = "Nettl_Away";
            NextDiag.TempNode = "NStep_1";
            Pchar.questTemp.CapBloodLine.TalkWithNettl = true;
		break;

        case "NStep_1":

            dialog.text = "Your health, doctor! Ehhh!";
            if( Pchar.questTemp.CapBloodLine.stat == "needMoney")
            {
                link.l1 = "I have a conversation with you.";
                link.l1.go = "NStep_2";
            }
            else
            {
                link.l1 = "My advice to you is to go home and sleep it off.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "NStep_1";
            }
		break;

        case "NStep_2":

            dialog.text = "I'm aware, Jeremy Pitt has already buzzed...";
            if(makeint(pchar.money) >= 25000)
            {
                link.l1 = "Here's twenty-five thousand for you. Take care of the purchase and all related matters immediately, friend. Don't let me down.";
                link.l1.go = "NStep_3";
            }
            else
            {
                link.l1 = "Be ready, as soon as I collect the necessary amount of money, you will start buying a sloop.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "NStep_5";
            }
		break;

        case "NStep_3":

            AddMoneyToCharacter(pchar, -25000);
            dialog.text = "Well, I don't have much choice... It looks like it.";
        	link.l1 = "Hurry up.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "NStep_4";
            NPChar.lifeDay = 0;
       		CloseQuestHeader("CapBloodLine_q2");
            CapBloodLine_q3_Complited();

		break;

        case "NStep_4":

            dialog.text = "I'm going to finish my rum and go to the shipyard.";
        	link.l1 = "Hurry up.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "NStep_4";
		break;

        case "NStep_5":

            dialog.text = "Did you bring the money?";
            if(makeint(pchar.money) >= 25000)
            {
                link.l1 = "Here's twenty-five thousand for you. Take care of the purchase and all related matters immediately, friend. Don't let me down.";
                link.l1.go = "NStep_3";
            }
            else
            {
               	link.l1 = "Not yet.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "NStep_5";
            }
		break;

		case "Nettl_Away":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NettlOnTavern", -1);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
		break;

        case "NStep_6":

            dialog.text = "Ir... Good heavens! And how can this be done?";
        	link.l1 = "Well, in general, I'll take care of everything. All you have to do is go to the shipyard and buy a sloop, I'll bring you the money. Go to the tavern, otherwise we are very conspicuous here.";
            link.l1.go = "Nettl_Away";
            NextDiag.TempNode = "NStep_5";
            Pchar.questTemp.CapBloodLine.TalkWithNettl = true;
		break;

        //--> Вакер

        case "WStep_0":

            AddCharacterExpToSkill(pchar, "Sneak", 50);
            dialog.text = "I'd be glad to know where he is myself. I've been waiting for him here for an hour, but he's still not here. Had the poor man gone off the hook? Meanwhile, I have a conversation with you...";
        	link.l1 = "I'm in a hurry, Dr. Wacker, I need to find Mr. Dan as soon as possible. The conversation will have to be postponed.";
            link.l1.go = "WStep_2";

		break;

        case "WStep_1":

            dialog.text = "I'd be glad to know where he is myself. I've been waiting for him here for an hour, but he's still not here. Has the poor guy disappeared from a binge? Meanwhile, I have a conversation with you...";
        	link.l1 = "I'm in a hurry, Dr. Wacker, I need to find Mr. Dan as soon as possible. The conversation will have to be postponed.";
            link.l1.go = "WStep_2";

		break;

        case "WStep_2":

            dialog.text = "Well, I myself am not in the mood to discuss everything that needs to be discussed, right here and now. I think I'll go, and if you want, wait for Dan. We'll talk tomorrow. As soon as you find a free minute, come to the tavern. I really hope for you.";
        	link.l1 = "Goodbye.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "reload1";
            Pchar.questTemp.CapBloodLine.iTime = 5;

            sld = GetCharacter(NPC_GenerateCharacter("Den", "usurer_1", "man", "man", 7, ENGLAND, 3, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.name = "Mr.";
            sld.lastname = "Dan";
            sld.greeting 	=  "Gr_medic";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
			ChangeCharacterAddressGroup(sld, "BridgeTown_town", "goto", "goto3");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorDialog(sld, pchar, "", 2.0, 0);
            AddQuestRecord("CapBloodLine_q2", "1");

		break;
		//Предложение Вакера - вторая встреча
        case "WStep_3":

            dialog.text = "Don't be so short-tempered, my friend. You misunderstood, I didn't have such thoughts at all. I want to help you!";
        	link.l1 = "What an insight!";
            link.l1.go = "WStep_4";

		break;

        case "WStep_4":

            dialog.text = "I'm not a fool, dear colleague. I can see right through a man and I can even tell what he's thinking.";
        	link.l1 = "You'll convince me of that if you tell me what I'm thinking.";
            link.l1.go = "WStep_5";

		break;

        case "WStep_5":

            dialog.text = "I have watched you more than once when you gazed longingly into the sea. And you think that I do not know your thoughts? If you managed to escape from this hell, you could, as a free person, with pleasure and benefit for yourself, completely devote yourself to your profession, of which you are an ornament.The world is great, and besides England, there are many other countries where a person like you will always be warmly welcomed. Besides the English colonies, there are others. It's not far from here to the Dutch colony of Curacao. At this time of the year, it is quite possible to get there even by small boat. Curacao can become a bridge to a vast world. It will open up to you as soon as you are free from the chains. What do you say to that?";
        	link.l1 = "I don't have any money, and it's gonna take a lot of money.";
            link.l1.go = "WStep_6";

		break;

        case "WStep_6":

            dialog.text = "Didn't I say that I wanted to be your friend?";
        	link.l1 = "Why?";
            link.l1.go = "WStep_7";
           	link.l2 = "That's very noble of you, colleague. That's exactly what I would do if I had a chance like this.";
            link.l2.go = "WStep_8";

		break;

        case "WStep_7":

            dialog.text = "You can't imagine how my heart bleeds at the sight of a colleague languishing in slavery and deprived of the opportunity to put his wonderful abilities into practice! Why should you languish in chains, though invisible to the eye, when you can go to the horizon, make this world at least a little bit better... And we should leave our work in Bridgetown... Right?";
        	link.l1 = "In addition to courage, money is needed to escape. The sloop will probably cost twenty thousand.";
            link.l1.go = "WStep_9";

		break;

        case "WStep_8":

            dialog.text = "So you agree?";
        	link.l1 = "In addition to courage, money is needed to escape. The sloop will probably cost twenty thousand.";
            link.l1.go = "WStep_9";

		break;

        case "WStep_9":

            dialog.text = "You will get the money! This will be a loan that you will return to us... give it back to me when you can.";
        	link.l1 = "I need to prepare, think about everything and coordinate with the right people. Tomorrow we will continue our conversation. You have opened the doors of hope for me, colleague!";
            link.l1.go = "Exit";
            n = FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = true;
            Pchar.questTemp.CapBloodLine.stat = "WakerOfferComplited";
            AddQuestRecord("CapBloodLine_q2", "4");
            NextDiag.TempNode = "WStep_10";

		break;

        case "WStep_10":

            dialog.text = "See you tomorrow, colleague.";
        	link.l1 = "Goodbye.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_10";

		break;

		//Предложение Вакера - заключение

        case "WStep_11":

            dialog.text = "Good morning, Dr. Blood. I've been waiting for you.";
        	link.l1 = "Good morning, Dr. Wacker. Well, I've gathered the people and everything I need. I'm just waiting for the promised money.";
			npchar.LifeDay = 0;
            link.l1.go = "WStep_12";

		break;

        case "WStep_12":

            dialog.text = "The thing is, I only have 18,000 piastres on hand, and you'll need about 25,000. However, I am sure you will be able to get the remaining amount.";
        	link.l1 = "It will be difficult, but I have no choice. What about the sloop? None of the slaves will be able to just come to the shipyard and buy themselves a sloop, as if nothing had happened.";
            link.l1.go = "WStep_13";
            AddMoneyToCharacter(pchar, 18000);

		break;

        case "WStep_13":

            dialog.text = "Hmm, you're right, as always, Doctor. I hadn't thought of that...";
            if(Pchar.questTemp.CapBloodLine.TalkWithNettl == false)
            {
            	link.l1 = "Do you know someone who can help?";
                link.l1.go = "WStep_14";
            }
            else
            {
            	link.l1 = "There is Nattall, the carpenter. I saw him once in the city.";
                link.l1.go = "WStep_15";
            }

		break;

        case "WStep_14":

            dialog.text = "There are not only slaves on the island, but also exiles, people who are exiled for debts. They will be happy to spread their wings. I think any of them would be happy to take the opportunity to leave.";
        	link.l1 = "Thank you, colleague!";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_16";
            n = FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = true;
            Pchar.questTemp.CapBloodLine.stat = "needMoney";
            AddQuestRecord("CapBloodLine_q2", "7");

		break;

        case "WStep_15":

            dialog.text = "Nuttall... yes, the ship's carpenter can help. It is unlikely that he will have any reason to refuse you. Well, go ahead, Dr. Blood. And good luck to you!";
        	link.l1 = "Thank you, colleague!";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_16";
            n = FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = true;
            Pchar.questTemp.CapBloodLine.stat = "needMoney";
            AddQuestRecord("CapBloodLine_q2", "7");

		break;

        case "WStep_16":

            dialog.text = "Good luck to you!";
        	link.l1 = "Thank you.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_16";

		break;

        //--> Мистер Дэн

        case "DStep_0":

            dialog.text = "What a nightmare! Here, I have a bottle with me - take it. It's not the first day I've been suffering, so I always keep it to myself. But never mind, I have some more left. Take it for free, Doctor-it's my civic duty!";
        	link.l1 = "Goodbye.";
            link.l1.go = "Exit_Away";
            GiveItem2Character(Pchar, "migraine_potion");
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;

        case "DStep_1":

            dialog.text = "What are you! Mrs. Steed's health is at stake-you did the right thing! Hurry up!";
        	link.l1 = "Goodbye.";
            link.l1.go = "Exit_Away";
            ChangeCharacterReputation(PChar, 5);
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;

        case "DStep_2":

            dialog.text = "Hmm... I see.";
        	link.l1 = "Goodbye.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;

        case "DStep_3":

            dialog.text = "Hello, Dr. Blood. How can I help you?";
        	link.l1 = "Good afternoon, Mr. Dan. I am here on the orders of His Excellency Governor Steed. I urgently need your wonderful extract to prevent migraines.";
            link.l1.go = "DStep_4";

		break;

        case "DStep_4":

            dialog.text = "Oh, sure, here you go - I don't have much left. Give my regards to the governor.";
        	link.l1 = "Thank you. Let me take my leave.";
            link.l1.go = "Exit";
            GiveItem2Character(Pchar, "migraine_potion");
            NextDiag.TempNode = "DStep_5";
            AddQuestRecord("WeaponsForEscape", "13");

		break;

        case "DStep_5":

            dialog.text = "Do you need something?";
        	link.l1 = "No thanks.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "DStep_5";

		break;

		//--> Джереми Питт

		 case "PStep_0":

            dialog.text = "What? What are you talking about?";
        	link.l1 = "I'm talking about the possibility tomorrow morning to buy a sloop at the shipyard, gather people from the plantation and from the city - of course, only those who can be trusted - and go to the horizon to the southwest, to the Dutch colony of Curacao.";
            link.l1.go = "PStep_1";

		break;

        case "PStep_1":

            dialog.text = "Are you delirious, Doctor? We have no money, no influence among the slaves, no contact in the city, and we can't have any of that.";
        	link.l1 = "Listen to me, Jeremy Pitt. You are the only navigator among us. I can't get to the right place without you, even if I gather people and sail safely on the sloop just after midnight tomorrow. I need you now, just as you once needed me at Oglethorpe Manor...";
        	link.l1.go = "PStep_2";  //(+ небольшой процент авторитета)
        	link.l2 = "Do you want to get out of here or not?";
        	link.l2.go = "PStep_3";

		break;

        case "PStep_2":

            dialog.text = "Okay, I got it, I got it. I will do everything in my power to help...";
        	link.l1 = "Remember that by giving yourself away, you will ruin everything: after all, you are the only navigator among us, and escape is impossible without you.";
            link.l1.go = "Exit";
            AddCharacterExpToSkill(pchar, "LeaderShip", 50);
            NextDiag.TempNode = "PStep_4";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape";
            Pchar.questTemp.CapBloodLine.statcrew = "find";
            Pchar.questTemp.CapBloodLine.Officer = 0;
            AddQuestRecord("CapBloodLine_q2", "5");
            AddQuestRecord("WeaponsForEscape", "1");

		break;

        case "PStep_3":

            dialog.text = "Okay, I got it, I got it. I will do everything in my power to help...";
        	link.l1 = "Remember that by giving yourself away, you will ruin everything: after all, you are the only navigator among us, and escape is impossible without you.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_4";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape";
            Pchar.questTemp.CapBloodLine.statcrew = "find";
            AddQuestRecord("CapBloodLine_q2", "5");
            AddQuestRecord("WeaponsForEscape", "1");
		break;

        case "PStep_4":

            if(CheckAttribute(Pchar, "questTemp.CapBloodLine.Officer") && Pchar.questTemp.CapBloodLine.Officer == 4 && Pchar.questTemp.CapBloodLine.stat == "ReadyToEscape")
            {
                dialog.text = "When are we leaving, Peter?";
                link.l1 = "I got a gun and made an agreement with the guys. All that remains is to buy a sloop. We'll be far away from here by tomorrow evening!";
                link.l1.go = "PStep_9";
                while (GetCharacterItem(pchar, "Weapon_for_escape") > 0)//homo fix 06/02/08 отбираем все квестовое оружие
                {
                    TakeItemFromCharacter(Pchar, "Weapon_for_escape");
                }
                //link.l10 = "Continue the game.";
                //link.l10.go = "finish";
                NextDiag.TempNode = "PStep_10";
                break;

            }
            dialog.text = "Recruit people and prepare everything you need. I'll be waiting for you here.";
        	link.l1 = "See you later.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_4";
		break;

        case "PStep_5":

            dialog.text = "Peter, the dragoons of the Tangier regiment are galloping here, they are looking for participants in the uprising...";
        	link.l1 = "I think we have nothing to fear, because we live in a Christian country, and Christians do not fight with the wounded and those who sheltered them. But Pitt should disappear somewhere.";
            link.l1.go = "PStep_6";
            //NextDiag.TempNode = "SStep_4";

		break;

        case "PStep_6":

            dialog.text = "Okay, I'll hide in the chimney, but you don't know Colonel Kirk well, he's a real devil. And you don't even have a sword to stand up for yourself.Take mine, I hid it on the balcony in a chest. And hurry up, the dragoons are about to break into the manor.";
        	link.l1 = "Thanks, I'll go get it, but I hope I won't need it.";
            link.l1.go = "Exit_RunAway";
			//кладём ключ на стол
			sld = ItemsFromID("key3");
			sld.shown = true;
			sld.startLocation = "Estate";
			sld.startLocator = "item1";

            Pchar.questTemp.CapBloodLine.sLocator = "reload2";
            Pchar.questTemp.CapBloodLine.iTime = 5;
            AddDialogExitQuestFunction("DragunInvansion2");

		break;

        case "PStep_7":

            dialog.text = "Hello, Peter. Today marks exactly one month since we have been working on Colonel Bishop's sugar plantations. Sometimes it seems to me that it would be better if we were executed - it's so hard for us. Everyone is so exhausted that they just fall off their feet. Only yesterday, the former blacksmith from Bridgewater was whipped to death as a warning to the others, and he only resented the severity of the overseer Kent. We need to do something, Peter, otherwise we won't live to see winter.";
        	link.l1 = "I keep thinking about it, but just running away from here, without any outside support, is too risky, take at least that poor guy who dared to run two weeks ago and was caught. He was flogged, and then the letters 'E.C.' were burned on his forehead so that everyone would know for the rest of his life that he was an escaped convict.";
            link.l1.go = "PStep_8";
        break;

        case "PStep_8":
            dialog.text = "Fortunately for the sufferer, he died of beatings, but I came to you not to complain about the hardships, but to inform you that Bishop is looking for you for some reason. Try not to anger him, otherwise we risk being left without your medical help.";
        	link.l1 = "Thank you, Pitt, then I'll go to him, and I promise I'll be as meek as a lamb.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "reload1";
            Pchar.questTemp.CapBloodLine.iTime = -1;
            NextDiag.TempNode = "First time";
            Pchar.questTemp.CapBloodLine.stat = "";
            chrDisableReloadToLocation = false;
            AddDialogExitQuestFunction("ChangePIRATES");
		break;

        case "PStep_9":

            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
            CapBloodLine_q2_Complited();

		break;

        case "PStep_10":

            dialog.text = "Peter, did you manage to buy a sloop?";
        	link.l1 = "Not yet.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_10";

		break;

        case "PStep_11":

            dialog.text = "Sorry, Peter, they are... They tracked me down...";
        	link.l1 = "Calm down, Pitt, Hagthorpe told me everything. You probably thought we could do without a navigator if you gave that bastard Bishop a reason to almost kill you?";
            link.l1.go = "PStep_12";

		break;

        case "PStep_12":

            dialog.text = "I don't think you'll need a navigator at all, Peter.";
        	link.l1 = "What, what is it?";
            link.l1.go = "PStep_13";

		break;

        case "PStep_13":

            dialog.text = "Nattall escaped.";
        	link.l1 = "To hell with Nuttall! We'll figure something out. We'll steal the sloop, after all! Hagthorpe and the others are already waiting for us in the city, we need to warn them before they are captured!";
            link.l1.go = "PStep_14";

		break;

        case "PStep_14":

            dialog.text = "Then run to the city and warn the others, you can come back for me later.";
        	link.l1 = "Wait for us here, Pitt.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_15";
            chrDisableReloadToLocation = false;
           	LAi_group_SetHearRadius("TmpEnemy", LAI_GROUP_GRD_HEAR - 3);
   	        LAi_group_SetSayRadius("TmpEnemy", LAI_GROUP_GRD_SAY - 1);
   	        LAi_group_SetLookRadius("TmpEnemy", LAI_GROUP_GRD_LOOK - 1);
            AddQuestRecord("EscapeFormBarbados", "2");

		break;

        case "PStep_15":

            dialog.text = "Run to the city!";
        	link.l1 = "We'll pick you up.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_15";

		break;

        case "PStep_16":

            dialog.text = "Congratulations, Peter, the guys told me about the fight with the Spaniards. I wish I had been with you! But the main thing is that we escaped from this damned island!";
        	link.l1 = "Glad to see you on your feet, buddy. Unfortunately, we haven't escaped yet. We still need to go out to sea and decide where we're going.";
            link.l1.go = "PStep_17";

		break;

        case "PStep_17":

            dialog.text = "Yes, we cannot return to England - they will hang us there immediately. We won't be any safer in Spain or Holland. The same applies to all colonies. Only the French colonies remain, or to the pirates.";
        	link.l1 = "I think we'll have time to think about it later. And now there is no time to waste, those who remained on the shore are not blind and have not died and will soon realize that something is wrong with the ship. We need to choose a captain and prepare for the defense.";
            link.l1.go = "PStep_18";

		break;

        case "PStep_18":

            dialog.text = "What's there to choose! Everyone wants you to be our captain, Peter.";
			DeleteAttribute(pchar, "LockBloodWeaponsOptions");
        	link.l1 = "Well, if there are no objections, then we are preparing the ship for battle. You will be the navigator, Jeremy, since you are the only one of us who can control the ship.";
            link.l1.go = "PStep_19";

		break;

        case "PStep_19":

            dialog.text = "Yes, Captain.";
        	link.l1 = "";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);

            Pchar.Ship.Type = GenerateShipExt(SHIP_ARABELLA, true, Pchar);
            Pchar.Ship.name="Cinco Llagas";
            SetBaseShipData(Pchar);
            Pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
            SetCrewQuantity(Pchar, GetMinCrewQuantity(Pchar));

            SetCharacterGoods(Pchar,GOOD_FOOD,70);
        	SetCharacterGoods(Pchar,GOOD_BALLS,300);//2000);
            SetCharacterGoods(Pchar,GOOD_GRAPES,100);//700);
            SetCharacterGoods(Pchar,GOOD_KNIPPELS,100);//700);
            SetCharacterGoods(Pchar,GOOD_BOMBS,200);//1500);
            SetCharacterGoods(Pchar,GOOD_POWDER,500);
//            SetCharacterGoods(Pchar,GOOD_PLANKS,10);
//            SetCharacterGoods(Pchar,GOOD_RUM,40);//600);
            SetCharacterGoods(Pchar,GOOD_WEAPON,50);//2000);

            n = FindLocation("Bridgetown_town");

            locations[n].reload.ship1.name = "reloadShip";
            locations[n].reload.ship1.go = "Barbados";
            locations[n].reload.ship1.emerge = "reload_1";
            locations[n].reload.ship1.autoreload = "1";
            locations[n].reload.ship1.label = "Sea";

            Pchar.location.from_sea = "Bridgetown_town";
            setWDMPointXZ("Bridgetown_town");

            string sQuest = "CapBloodLaspEpisode";
            pchar.quest.(sQuest).win_condition.l1 = "EnterToSea";
            pchar.quest.(sQuest).win_condition = "CapBloodLaspEpisode";
            pchar.quest.(sQuest).function = "CapBloodLaspEpisode";

            AddDialogExitQuestFunction("SpaCrewAtack");


		break;

		//-->оружейние Гриффин

        case "GRStep_0":

            dialog.text = "With all due respect, Doctor, which you undoubtedly deserve... To hell with your urgent business!";
        	link.l1 = "I'm sorry that I didn't find you in a good mood. Maybe I can help you with something, after which you will listen to me?";
            link.l1.go = "GRStep_1";

		break;

        case "GRStep_1":

            dialog.text = "Help me? You?! How can a self-willed slave help...";
        	link.l1 = "It looks like you underestimate me, Mr. Griffin. Well, you and many others have yet to regret it!";
            link.l1.go = "GRStep_2";
        	link.l2 = "Why not? I need your help and it seems that I can only offer mutual help in this situation.";
            link.l2.go = "GRStep_3";
		break;

        case "GRStep_2":

            AddQuestRecord("WeaponsForEscape", "4");
            dialog.text = "Get out, doctor!";
            link.l1.go = "Exit";
            pchar.quest.PrepareToEscape2.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape2.win_condition.l1.location = "Bridgetown_town";
            pchar.quest.PrepareToEscape2.function                  = "LoginSpain_spy";
        	Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2";

		break;
        case "GRStep_3":

            dialog.text = "Well, let's see. The fact is that a Spaniard came to see me today. He didn't give his name, but I could tell by his eyes that this man was ready for anything. I don't know where he came from or how he got into the city, but he needed a weapon. Yes, Doctor, I was scared... That's why I can't go to the authorities now, because I should have done it earlier. The Spaniard refused to wait for me to make an order, and took my samples from the wall - several cutlasses, a long-barrel musket and a pair of pistols. Damn Spanish hog!";
        	link.l1 = "...I know, I know - 'to the sea devil'.";
            link.l1.go = "GRStep_2";
            NextDiag.TempNode = "GRStep_2";
           	link.l2 = "Did he not pay for the weapon?";
            link.l2.go = "GRStep_4";

		break;
        case "GRStep_4":

            dialog.text = "To hell with the payment! My name is engraved on the samples! If he goes into battle with my weapon in his hands, someone will definitely notice it... And they'll catch him sooner or later without a fight! The last thing I want to do is end my life on the yard now.";
        	link.l1 = "If you tell me where the Spaniard went, I will try to solve your problem. In return, I only ask you to give me what this man took.";
            link.l1.go = "GRStep_5";

		break;

        case "GRStep_5":

            dialog.text = "A weapon with my name on the blade of a Spaniard or a slave... What the hell difference does it make?! We will hang together in the central square by dawn tomorrow!";
        	link.l1 = "To the devil, I think, no. Fine. I will return the weapon to you, and in return, by tonight, you will prepare for me several cutlasses and pistols without your identification marks. Is it okay?";
            link.l1.go = "GRStep_6";

		break;

        case "GRStep_6":

            dialog.text = "The Spanish thug will gut you, Doctor. But it doesn't concern me. Return the samples to me, and I will do for you what you ask. For fifteen hundred piastres. He went to the port to the fisherman Hells, whose house is not far from the house of the pharmacist Dan.";
        	link.l1 = "I'll be back soon, my dear Mr. Griffin. Prepare everything you need.";
            link.l1.go = "GRStep_7_1";
           	link.l2 = "Aren't you asking too much? I'm already risking my life for your reputation. A thousand, and not a pound more.";
            link.l2.go = "GRStep_7_2";

            sld = GetCharacter(NPC_GenerateCharacter("Spain_spy", "shipowner_13", "man", "man", 7, ENGLAND, -1, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.name = "";
            sld.lastname = "The Spaniard";
            GiveItem2Character(sld, "Griffins_Weapon");
            sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true;
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorSetLayMode(sld);
            LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "CommonRoom_MH2", "goto", "goto2");


            sld = &characters[GetCharacterIndex("Hells")];
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorDialog(sld, pchar, "", 1.0, 0);

		break;

        case "GRStep_7_1":

            dialog.text = "Okay, hurry up.";
        	link.l1 = "You won't have to wait long.";
            link.l1.go = "Exit";
            Pchar.questTemp.CapBloodLine.iMoney = 1500;
            NextDiag.TempNode = "GRStep_8";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_1";
            AddQuestRecord("WeaponsForEscape", "3");
            AddQuestUserData("WeaponsForEscape", "iMoney", 1500);

		break;

        case "GRStep_7_2":

            dialog.text = "Okay, hurry up.";
        	link.l1 = "You won't have to wait long.";
            link.l1.go = "Exit";
            Pchar.questTemp.CapBloodLine.iMoney = 1000;
            NextDiag.TempNode = "GRStep_8";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_1";
            AddQuestRecord("WeaponsForEscape", "3");
            AddQuestUserData("WeaponsForEscape", "iMoney", 1000);

		break;

        case "GRStep_8":

            dialog.text = "You came earlier than I expected to see you. What happened?";
            if (GetCharacterItem(pchar, "Griffins_Weapon") > 0)
            {
            	link.l1 = "Here are your samples, Mr. Griffin, every single one. The Spanish thug is no longer a danger.";
                link.l1.go = "GRStep_9";
                TakeItemFromCharacter(Pchar, "Griffins_Weapon");
            }
            else
            {
            	link.l1 = "I just came to check on you.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_8";
            }

		break;

        case "GRStep_9":

            dialog.text = "Hmm... well, I'm not even interested in how you did it and how many you killed in the process. Today, in an hour, the exact same package will be ready for you. And now I will ask you to leave me, having previously, of course, paid for my work.";
            if (makeint(pchar.money) >= sti(Pchar.questTemp.CapBloodLine.iMoney))
            {
           	    link.l1 = "Yes, absolutely, dear Mr. Griffin. Here's your money. I'll come in at the appointed hour.";
                link.l1.go = "Exit";
                AddMoneyToCharacter(pchar, (-sti(Pchar.questTemp.CapBloodLine.iMoney)));
                Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_3";
                NextDiag.TempNode = "GRStep_12";
            }
            else
            {
           	    link.l1 = "I don't have the required amount with me right now, I'll come back later.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_13";
            }
            //Pchar.questTemp.CapBloodLine.GriffinTime = GetHour();
            SaveCurrentQuestDateParam("questTemp.CapBloodLine.GriffinTime");
            AddQuestRecord("WeaponsForEscape", "6");

		break;

        case "GRStep_10":

            dialog.text = "Yes, I remember something. But what kind of anchor do you need here?";
        	link.l1 = "To me... Some of your assortment would be nice.";
            link.l1.go = "GRStep_11";

		break;

        case "GRStep_11":

            dialog.text = "What?! Weapon... You?! You're crazy, you sea devil! Get out!";
        	link.l1 = "";
            link.l1.go = "Exit";
            pchar.quest.PrepareToEscape2.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape2.win_condition.l1.location = "Bridgetown_town";
            pchar.quest.PrepareToEscape2.function                  = "LoginSpain_spy";
        	Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2";


		break;

        case "GRStep_12":

            if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1_3" && GetQuestPastTimeParam("questTemp.CapBloodLine.GriffinTime") >= 1)
            {
                dialog.text = "Here, take it, but remember - I didn't do it for you.";
                link.l1 = "Thank you.";
                link.l1.go = "Exit";
                GiveItem2Character(Pchar, "Weapon_for_escape");
                NextDiag.TempNode = "First time";
          		CloseQuestHeader("WeaponsForEscape");
                Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";
            }
            else
            {
                dialog.text = "The weapon is not ready for you yet, come back later.";
                link.l1 = "Good.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_12";

            }

		break;

        case "GRStep_13":

            dialog.text = "Did you bring the money?";
            if (makeint(pchar.money) >= sti(Pchar.questTemp.CapBloodLine.iMoney))
            {
                link.l1 = "Yes, here is your money. I'll come in at the appointed hour.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_12";
                AddMoneyToCharacter(pchar, (-sti(Pchar.questTemp.CapBloodLine.iMoney)));
                Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_3";
            }
            else
            {
           	    link.l1 = "I don't have the required amount with me right now, I'll come back later.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_13";
            }


		break;

        case "GRStep_14":

            dialog.text = "Good God!..";
        	link.l1 = "Not really. Nevertheless, I came to find out - maybe you've changed your mind?";
            link.l1.go = "GRStep_15";

		break;

        case "GRStep_15":

            dialog.text = "P-pe... Changed your mind?";
        	link.l1 = "Weapons, dear Mr. Griffin. I need a weapon. Just a few cutlasses and a couple of pistols, if it's not too much trouble.";
            link.l1.go = "GRStep_16";

		break;

        case "GRStep_16":

            dialog.text = "I... I can't, sir. With all my desire, me... They'll hang you!";
        	link.l1 = "Calm down, I don't need you to do anything officially at all. No identifying engravings on the hilt, no papers or reports - everything is quiet and peaceful. No one will ever know that this happened.";
            link.l1.go = "GRStep_17";

		break;

        case "GRStep_17":

            dialog.text = "Mmm... Okay, good. I have it all, here - take it. I hope that's enough.";
        	link.l1 = "More than. Thank you very much.";
            link.l1.go = "Exit";

            GiveItem2Character(Pchar, "Weapon_for_escape");
            AddQuestRecord("WeaponsForEscape", "9");
       		CloseQuestHeader("WeaponsForEscape");
            Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";
            NextDiag.TempNode = "First time";

		break;


        //-->рыбак Хелльс

        case "HStep_0":

            dialog.text = "Doctor... What do you want here?";
        	link.l1 = "I needed a man whose lifeless body is now lying at your feet.";
            link.l1.go = "HStep_1";

		break;

        case "HStep_1":

            dialog.text = "Do you want to avenge your bastard friend? Come on, puppy!";
        	link.l1 = "You're being too aggressive, Mr. Hells. I'll prescribe you a sedative. The fact is, I just want to thank you for making my task easier. I'm here to retrieve some property that this dead gentleman had the temerity to steal from Mr. Griffin.";
            link.l1.go = "HStep_2";

		break;

        case "HStep_2":

            dialog.text = "I will not give this money back! The bastard attacked me, and you just want to...";
        	link.l1 = "... to take away the weapon, which he probably used in the attack. Nothing else. His money rightfully belongs to you.";
            link.l1.go = "HStep_3";

		break;

        case "HStep_3":

            dialog.text = "You can take it, I don't think he needs it anymore.";
        	link.l1 = "Thank you.";
            link.l1.go = "HStep_4";
            NextDiag.TempNode = "First time";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_2";
		break;

        case "HStep_4":

            NextDiag.CurrentNode = NextDiag.TempNode;
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(NPChar, sTemp);
            LAi_SetOwnerTypeNoGroup(NPChar);
            DialogExit();
            Spain_spyDie("");
		break;

        case "HStep_5":

            dialog.text = "I have some work for you if you're interested. Although, I'm sure this is a stupid question. You all need money.";
        	link.l1 = "How much?";
            link.l1.go = "HStep_6";

		break;

        case "HStep_6":

            dialog.text = "I'm willing to pay you two thousand for some information. The fact is that Arnold Summerlight, my competitor, has found a place... a very fishy place. He's ruining me! Find out at any cost where he gets his catch, and I'll gladly part with two thousand. Is it okay?";
        	link.l1 = "Coming.";
            link.l1.go = "HStep_7";
           	link.l2 = "This is not for me.";
            link.l2.go = "Exit";
            NextDiag.TempNode = "HStep_8";
		break;

        case "HStep_7":

            AddQuestRecord("FishermanQuest", "1");
            sld = &characters[GetCharacterIndex("Fisherman")];
            sld.dialog.currentnode = "FStep_1";
            NextDiag.TempNode = "HStep_9";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

		break;

        case "HStep_8":

            dialog.text = "So won't you help me?";
        	link.l1 = "I will help.";
            link.l1.go = "HStep_7";
           	link.l2 = "No.";
            link.l2.go = "Exit";
            NextDiag.TempNode = "HStep_8";

		break;

        case "HStep_9":

            dialog.text = "So?";
            if(CheckAttribute(Pchar, "questTemp.CapBloodLine.fishplace"))
            {
            	link.l1 = "I found out everything, Mr. Hells.";
                link.l1.go = "HStep_10";
            }
            else
            {
            	link.l1 = "No news yet.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "HStep_9";
            }

		break;

        case "HStep_10":

            dialog.text = "It can't be! Where? Where does he get fish?";
        	link.l1 = "He's casting nets at Ragged Point.";//+Pchar.questTemp.CapBloodLine.fishplace;
            link.l1.go = "HStep_11";

		break;

        case "HStep_11":

            dialog.text = "Damn, how did I not think of it before!.. Okay, here's your money.";
        	link.l1 = "Thank you.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            AddMoneyToCharacter(pchar, 2000);
       		CloseQuestHeader("FishermanQuest");
		break;


        //-->Испанский шпион

        case "SSStep_0":

            dialog.text = "I need a gunsmith. Where is the armorer?";
        	link.l1 = "His house is nearby. First of all, he's there.";
            link.l1.go = "SSStep_1";
           	link.l2 = "Why would I show you the way? What do you want from a gunsmith?";
            link.l2.go = "SSStep_2";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_1";
            chrDisableReloadToLocation = false;
            LocatorReloadEnterDisable("BridgeTown_town", "houseSp2", true);

		break;

        case "SSStep_1":

            dialog.text = "*хриплый смех*";
        	link.l1 = "";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp2";
            Pchar.questTemp.CapBloodLine.iTime = 20;
            AddQuestRecord("WeaponsForEscape", "7");

		break;

        case "SSStep_2":

            dialog.text = "Then get lost before I gut you.";
        	link.l1 = "That would be problematic.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp2";
            Pchar.questTemp.CapBloodLine.iTime = 20;
            AddQuestRecord("WeaponsForEscape", "7");

		break;

        case "SSStep_3":

            dialog.text = "(to Griffin): English dog!.. I'm going to kill everyone in this town, and I'm going to start with you, you stubborn old man! You don't understand, it's about to be Cinco Llagas... What are YOU doing here?!";
        	link.l1 = "Let me interrupt you.";
            link.l1.go = "SSStep_4";
		break;

        case "SSStep_4":

            dialog.text = "Well, since you've come... You're next!";
        	link.l1 = "No, I guess I'll be the previous one...";
            link.l1.go = "fight";
            sld = &characters[GetCharacterIndex("Griffin")];
            sld.dialog.currentnode = "GRStep_14";

		break;

		//--> Контрабандист

        case "QSStep_0":

            dialog.text = "Stop, stop, stop... Asking for such a favor is not much better than asking me to take you away from here. Moreover, I will not risk taking you away from these lands on pain of death, because if they find out about it, I will die much more painfully, but a weapon! You have to be a man bold enough and a little crazy to ask for it in a tavern, being a privileged slave. And you have to be even more crazy to agree to help you with this...";
        	link.l1 = "Since you are so verbose, it means that your interest is in this, it remains only to agree on the price.";
            link.l1.go = "QSStep_1";
		break;

        case "QSStep_1":

            dialog.text = "You're very perceptive, Doctor. Well, I won't hide it - you're right. I'm interested in something, but I'm afraid you won't dare to take the risk...";
        	link.l1 = "What is it about?";
            link.l1.go = "QSStep_2";
		break;

        case "QSStep_2":

            dialog.text = "I know that you have access to the governor's estate...";
        	link.l1 = "It's not worth continuing. I'm in a hurry, and the chance that the governor or his wife will get worse right now is negligible. Otherwise, the road to the estate is closed to me.";
            link.l1.go = "QSStep_3";

		break;

        case "QSStep_3":

            dialog.text = "I am sure that for the sake of a dozen cutlasses and a few muskets that I have by a lucky chance right on me, as well as, say, three thousand always shiny money, you will find a way to get to the governor.";
        	link.l1 = "What is required of me?";
            link.l1.go = "QSStep_4";

		break;

        case "QSStep_4":

            dialog.text = "A small ring. Just.";
        	link.l1 = "A ring? It's on his wife's arm, I think. And I have to take it off and bring it back?";
            link.l1.go = "QSStep_5";

		break;

        case "QSStep_5":

            dialog.text = "I don't think she's wearing it, my dear doctor. Nevertheless, she has it. A small gold ring-simple as three piastres, but damn important to me. The buyer will give you barely a fifth of what I'm offering for it. Just don't ask me why. Just answer it.";
			pchar.LockBloodWeaponsOptions = true;
        	link.l1 = "I'll be back as soon as I can. Prepare the money and the goods.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "QSStep_6";

            sld = &characters[GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2")];
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.Dialog.CurrentNode = "GStep_1";
            sld.protector = true;
            sld.protector.CheckAlways = 1 ;
            LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", true);
            LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", true);
            LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", true);

            sld = characterFromID("MisStid");
            sld.Dialog.CurrentNode = "MSStep_3";
        	sld.talker = 10;
            ChangeCharacterAddressGroup(sld, "Bridgetown_TownhallRoom", "barmen", "bar1");

            sld = characterFromID("Den");
            LAi_SetCitizenTypeNoGroup(sld);
            //LAi_SetStayTypeNoGroup(sld);
            LAi_SetOwnerTypeNoGroup(sld);
            sld.Dialog.CurrentNode = "DStep_3";
			ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "goto", "goto6");

            sld = ItemsFromID("MsStid_ring");
			sld.shown = true;
			sld.startLocation = "Bridgetown_TownhallRoom";
			sld.startLocator = "item1";

            pchar.quest.PrepareToEscape3.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape3.win_condition.l1.location = "Bridgetown_TownhallRoom";
            pchar.quest.PrepareToEscape3.function                  = "FindMsStid_ring";
			AddQuestRecord("WeaponsForEscape", "11");
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape3";

		break;


        case "QSStep_6":

            if (GetCharacterItem(pchar, "MsStid_ring") > 0)
			{
                dialog.text = "The Doctor is back! Wonderful!";
                link.l1 = "How did you find out about the ring?";
    			link.l1.go = "QSStep_7";
                link.l2 = "Here's your thing. So what about the gold and weapons?";
    			link.l2.go = "QSStep_12";
			}
			else
			{
                dialog.text = "Something else?";
            	link.l1 = "No.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "QSStep_6";
            }

		break;

        case "QSStep_7":

            dialog.text = "Did you find out? Dear Doctor, I had no idea about him.";
        	link.l1 = "I am slightly puzzled by your answer. What kind of ring is this? Where is it from?";
            link.l1.go = "QSStep_8";

		break;

        case "QSStep_8":

            dialog.text = "This ring is extremely important to me, but it's of no use to you. I am lucky to have found him again, and therefore I am ready to fulfill my part of the deal and give you everything that I promised.";
        	link.l1 = "Or maybe, since you didn't know about the ring, go and find out about it from someone? Perhaps they will tell me in the market square? Look at this... how alluringly it glitters.";
            link.l1.go = "QSStep_10";

		break;

        case "QSStep_10":

            dialog.text = "*laughs* The arrogant Captain Blood has already sensed a taste for life with new strength... give it here!";
        	link.l1 = "I think, sir, you'd better return this ring to me and explain why you called me captain.";
            link.l1.go = "QSStep_11";
            TakeItemFromCharacter(Pchar, "MsStid_ring");

		break;

        case "QSStep_11":

            dialog.text = "Don't waste your precious time on this, Peter Blood. Here's your money and weapons-hurry up. Who knows, maybe fate brought us together for a reason.";
        	link.l1 = "Well, okay.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            GiveItem2Character(Pchar, "Weapon_for_escape");
            NextDiag.TempNode = "First time";
       		CloseQuestHeader("WeaponsForEscape");
            AddMoneyToCharacter(pchar, 3000);
            AddQuestRecord("WeaponsForEscape", "16");
            CloseQuestHeader("WeaponsForEscape");
            Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";

		break;

        case "QSStep_12":

            dialog.text = "Thank you very much. Here's your money and everything you need. Goodbye.";
        	link.l1 = "All the best.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            GiveItem2Character(Pchar, "Weapon_for_escape");
            NextDiag.TempNode = "First time";
       		CloseQuestHeader("WeaponsForEscape");
            AddMoneyToCharacter(pchar, 3000);
            TakeItemFromCharacter(Pchar, "MsStid_ring");
            AddQuestRecord("WeaponsForEscape", "16");
            CloseQuestHeader("WeaponsForEscape");
            Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";

		break;

		  //--> Волверстон

        case "VLStep_0":
            dialog.text = "I would love to, but I'm afraid I won't be much use.";
        	link.l1 = "Why is that?";
            link.l1.go = "VLStep_0_1";
            NextDiag.TempNode = "VLStep_1";
		break;

		case "VLStep_0_1":
            dialog.text = "During these long months of hard labor, I haven't taken a drop in my mouth, but I'm very slow to think when I'm sober. Could you bring me a bottle of rum?";
			SetQuestHeader("VolversonRum");
			AddQuestRecord("VolversonRum", "1");
			pchar.SeekVolverstonRum = true;
        	link.l1 = "It looks like I have no choice. Without your participation, the escape can be forgotten.";
            link.l1.go = "exit";
            NextDiag.TempNode = "VLStep_0_2";
		break

		case "VLStep_0_2":
            dialog.text = "Did you bring what I asked for?";
			if(CheckCharacterItem(pchar, "potionrum"))
			{
				link.l1 = "Here you go.";
				link.l1.go = "VLStep_0_3";
			}
			link.l2 = "Not yet.";
            link.l2.go = "exit";
            NextDiag.TempNode = "VLStep_0_2";

		break;

		case "VLStep_0_3":
            dialog.text = "(He drinks the whole bottle down to the last drop in a few moments) Oh...  It's much better this way. Did you talk about running away? I'm in business.";
			RemoveItems(PChar, "potionrum", 1);
			AddQuestRecord("VolversonRum", "2");
			CloseQuestHeader("VolversonRum");
			DeleteAttribute(pchar, "SeekVolverstonRum")
        	link.l1 = "Pitt will tell you all the details. I hope you don't pass out from intoxication now and miss all the fun.";
            link.l1.go = "exit";
            NextDiag.TempNode = "VLStep_1";
            //Pchar.questTemp.CapBloodLine.Volverston = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
		break;

        case "VLStep_1":

            dialog.text = "Devil, when is this damn night coming?!";
        	link.l1 = "A little patience, my friend. We're going to get off this damn island very soon.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "VLStep_1";

		break;

		 case "VLStep_11":

            dialog.text = "I did a good workout! It's a pity that most of these cowardly dogs of the Spaniards are on the shore now -I would have fun, hehe!";
        	link.l1 = "If they were all here on board, I don't think we'd have fun, my friend.";
            link.l1.go = "VLStep_12";

		break;

        case "VLStep_12":

            dialog.text = "Yes, Peter, you're probably right as always.";
        	link.l1 = "But that's not what I wanted to talk to you about. Wolverston, you are a good fighter, not everyone can compare with you in strength, and I think if you go sailing a little, you will become an excellent first assistant. Will you come to me as an officer?";
            link.l1.go = "VLStep_13";

		break;

        case "VLStep_13":

            dialog.text = "Raise the Jolly Roger, become a free pirate, spend more time at sea than on land, risk every day, the smell of gunpowder, gold, rum? With great pleasure!";
        	link.l1 = "I knew you would agree.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("VolverstonAdd");

		break;
        //--> Натаниэль Хагторп

        case "HTStep_0":

            dialog.text = "This ring is extremely important to me, but it's of no use to you. I am lucky to have found him again, and therefore I am ready to fulfill my part of the deal and give you everything that I promised.";
        	link.l1 = "Or maybe, since you didn't know about the ring, go and find out about it from someone? Perhaps they will tell me in the market square? Look at this... how alluringly it glitters.";
            link.l1.go = "HTStep_1";

		break;

        case "HTStep_1":

            dialog.text = "I have it here... There's unfinished business, friend.";
        	link.l1 = "So you will finish it immediately and with my help. I'm going to need you on this voyage, and I can't let you stay, old sea wolf.";
            link.l1.go = "HTStep_2";

		break;

        case "HTStep_2":

            dialog.text = "*laugh* I respect the hell out of you, you know. But it's a matter of honor, I have to finish what I started.";
        	link.l1 = "Then I ask you to share with me. What is the case and how can I help?";
            link.l1.go = "HTStep_3";

		break;

        case "HTStep_3":

            dialog.text = "A man named Stuart Winterwood recently arrived here. I don't know if you'll understand me, but he's my bloodline. Because of him, I lost everything: my family, my honor, my life. He's the reason I got here!..";
        	link.l1 = "What happened?";
            link.l1.go = "HTStep_4";

		break;

        case "HTStep_4":

            dialog.text = "Don't give a damn about the past! It doesn't matter anymore. I thought that I would never see his face again, that that mocking grin on his face would be my last memory of this man... But do you know what kind of memory I would like to have? His agonized face on his severed head, damn it!";
        	link.l1 = "Well, so be it. How do I find him?";
            link.l1.go = "HTStep_5";

		break;

        case "HTStep_5":

            dialog.text = "Tavern, brothel... He's out there somewhere, the devil! Having fun and drinking, playing cards! My wedding ring is on his hand, MY wife is waiting for him at home! Bring me the ring... along with the finger.";
        	link.l1 = "If you wish, you can get his head too.";
            link.l1.go = "HTStep_13";
            NextDiag.TempNode = "HTStep_10";
        	link.l2 = "Are you sure you want to do this, Hagthorpe? His death will not ease your torment.";
            link.l2.go = "HTStep_6";
		break;

        case "HTStep_6":

            dialog.text = "If I doubted for even a moment that I wanted him dead, I wouldn't talk about it so confidently.";
        	link.l1 = "However, you may be wrong. Think about it, is it worth killing him now, risking everything? We can...";
            link.l1.go = "HTStep_7";

		break;

        case "HTStep_7":

            dialog.text = "The devil take you apart, Blood! It's a matter of honor, I told you! You're afraid to take risks, you don't dare to help me - don't! You'll sail to the sea devil without me!";
        	link.l1 = "All right, Hagthorpe. I'll kill him.";
            link.l1.go = "HTStep_13";
           	link.l2 = "Without you? Hardly possible, but with the right skill... Listen to me. We can go to sea now and start a new life, and sooner or later you will meet the damn Winterwood and take revenge as you want, without risking your own skin. You'll string him up on the yardarm, cutting off at least every single finger!";
            link.l2.go = "HTStep_8";
            NextDiag.TempNode = "HTStep_10";

		break;

        case "HTStep_8":

            dialog.text = "You... Are you trying to talk me out of it when that freak is under my nose?!";
            if(Pchar.SPECIAL.Charisma >= 5)
            {
            	link.l0 = "Well... yes, that's the way it is.";
                link.l0.go = "HTStep_9";
            }
            else
            {
                AddCharacterExpToSkill(pchar, "LeaderShip", 50);
            }
           	link.l1 = "All right, Hagthorpe. I'll kill him.";
            link.l1.go = "HTStep_13";

		break;

        case "HTStep_9":

            dialog.text = "Okay, I agree! To hell with Winterwood until now. I'll join you.";
        	link.l1 = "Deal.";
            link.l1.go = "Exit";
            AddCharacterExpToSkill(pchar, "LeaderShip", 150);
            NextDiag.TempNode = "HTStep_12";
            Pchar.questTemp.CapBloodLine.Hugtorp = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
			Pchar.HugtorpQuestFinish = true;
            AddQuestRecord("HugtorpTrouble", "2");
            CloseQuestHeader("HugtorpTrouble");

		break;
        case "HTStep_10":

            dialog.text = "Have you returned yet? Is he dead?";
            if (GetCharacterItem(pchar, "DOjeronRing") > 0)
            {
                link.l1 = "It couldn't be deader. This is what you asked for.";
                link.l1.go = "HTStep_11";
                TakeItemFromCharacter(Pchar, "DOjeronRing");
                ref itm = ItemsFromID("DOjeronRing"); //возвращаем все как было
                BackItemName("DOjeronRing");
                BackItemDescribe("DOjeronRing");
                itm.picIndex = 2;
                itm.picTexture = "ITEMS_9";
            }
            else
            {
                link.l1 = "No, I just wanted to see if you've changed your mind - apparently not.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "HTStep_10";
            }
		break;

        case "HTStep_11":

            dialog.text = "Well... finally... I'll join you in your escape, Blood. And thank you.";
        	link.l1 = "Deal.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "HTStep_12";
            Pchar.questTemp.CapBloodLine.Hugtorp = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
			Pchar.HugtorpQuestFinish = true;
            AddQuestRecord("HugtorpTrouble", "4");
            CloseQuestHeader("HugtorpTrouble");

		break;

        case "HTStep_12":

            dialog.text = "Is everything ready? What is required of me?";
        	link.l1 = "Not yet, I'll let you know when the time is right.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "HTStep_12";

		break;

        case "HTStep_13":

            LoginWinterwood();
			Pchar.HugtorpQuestStart = true;
            AddQuestRecord("HugtorpTrouble", "1");
            NextDiag.CurrentNode = "HTStep_10";
			DialogExit();

		break;

        case "HTStep_14":

            dialog.text = "Peter, bad news - Colonel Bishop's men tracked down Jeremy Pitt, just at the moment when he was hiding supplies for escape. He barely managed to tell me that he had managed to hide some weapons in a chest between the planks-on the edge of the plantation.";
        	link.l1 = "What's wrong with Pitt?";
            link.l1.go = "HTStep_15";
            chrDisableReloadToLocation = false;

		break;

        case "HTStep_15":

            dialog.text = "That pig, Bishop, whipped him half to death and told him not to give him food and water until he gave up his accomplices.";
        	link.l1 = "Bad. Bishop brought me back from the city for some reason, maybe I'm under suspicion too...";
            link.l1.go = "HTStep_16";



		break;

        case "HTStep_16":

            dialog.text = "Pitt is holding up, but you better not go to the colonel, he may order you to be locked up. It's better not to do anything now - we'll wait until dark. And as soon as it gets dark, we'll take out our weapons and free Jeremy.";
        	link.l1 = "Yes, that's what we'll do, I'll take care of Pitt's release, and you take the people to the city in the confusion. Can you handle it?";
            link.l1.go = "HTStep_17";

		break;

        case "HTStep_17":

            dialog.text = "Yes, Peter, we will be waiting for you at the shipyard. And beware of the patrols-Bishop's men are grabbing everyone indiscriminately right now.";
        	link.l1 = "I'll be careful.";
            link.l1.go = "Exit";
            AddDialogExitQuestFunction("ReturnToPlantation3");
            AddQuestRecord("EscapeFormBarbados", "1");

		break;

        case "HTStep_18":

            dialog.text = "Bad news, Peter...";
            if(Pchar.questTemp.CapBloodLine.SpainInBridgetown == false)
            {
               	link.l1 = "What happened?";
                link.l1.go = "HTStep_19";
            }
            else
            {
               	link.l1 = "I already know.";
                link.l1.go = "HTStep_20";
            }
		break;

        case "HTStep_19":

            dialog.text = "Spaniards have captured Bridgetown. Today, a large ship entered our port under a false flag. It was a Spanish privateer. His trick with the flag remained undiscovered so much that, without arousing suspicion, he calmly entered the bay and saluted the fort at point-blank range with a broadside of twenty guns.";
        	link.l1 = "This is what is called the timely intervention of fate. Although only the devil knows what will come of all this!";
            link.l1.go = "HTStep_20";
            AddQuestRecord("EscapeFormBarbados", "3");

		break;

        case "HTStep_20":

            dialog.text = "What about our escape plan? Nattal has escaped, the sloop is now missing...";
        	link.l1 = "The plan is changing - we will capture another ship.";
            link.l1.go = "HTStep_21";

		break;

        case "HTStep_21":

            dialog.text = "Which other one?";
        	link.l1 = "The one that is currently on the raid. I think most of the crew is rampaging ashore right now, so we can easily capture him.";
            link.l1.go = "HTStep_22";

		break;

        case "HTStep_22":

            dialog.text = "Then we'd rather die in battle with the Spaniards than rot on Bishop's plantations! Lead the way, Peter!";
        	link.l1 = "Let's try to get close unnoticed...";
            link.l1.go = "Exit";
            AddDialogExitQuestFunction("CapBloodOfficers");
            AddQuestRecord("EscapeFormBarbados", "4");
            NextDiag.TempNode = "HTStep_22b";

		break;

        case "HTStep_22b":

            dialog.text = "What are your orders, Peter?";
        	link.l1 = "Follow me, we're going to storm.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "HTStep_22b";
            AddDialogExitQuestFunction("CapBloodOfficers");

		break;

        case "HTStep_23":

            dialog.text = "Which other one?";
        	link.l1 = "The one that is currently on the raid. I think most of the crew is rampaging ashore right now, so we can easily capture him.";
            link.l1.go = "HTStep_22";

		break;

        case "HTStep_24":

            dialog.text = "You were right, Peter. Everything turned out as you said, we captured this beautiful ship with almost no losses.";
        	link.l1 = "Yes, Hagthorpe, but I'm afraid it's just beginning. I think you're a great sailor. Will you come to me as an officer?";
            link.l1.go = "HTStep_25";

		break;

        case "HTStep_25":

            dialog.text = "Peter, you are a kind and sympathetic person, the word 'honor' is not an empty word for you, you are a wonderful doctor, a talented captain and an excellent leader. If necessary, I will give my life for you.";
        	link.l1 = "Thank you, Nathaniel, but you will still have time to give your life for me, and now we still need to escape from this hell.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("HugtorpAdd");
		break;

        //--> Николас Дайк

        case "DKStep_0":

            dialog.text = "No, alas, I don't know anything. Maybe he hasn't done it yet... but it doesn't matter anymore.";
        	link.l1 = "Doesn't matter? What happened?";
            link.l1.go = "DKStep_1";

		break;

        case "DKStep_1":

            dialog.text = "Colonel Bishop is selling me. Yesterday, a buyer arrived in the city who needs a slave who is well acquainted with the maritime business. I'm afraid there's nothing more that can be done...";
        	link.l1 = "Really? Hm. Well, let's see.";
            link.l1.go = "exit";
            NextDiag.TempNode = "DKStep_2";
            sld = characterFromID("Bishop");
            sld.Dialog.CurrentNode = "BStep_2";
            AddQuestRecord("DiekeQuest", "1");
		break;

        case "DKStep_2":

            dialog.text = "I'm sorry about what happened.";
        	link.l1 = "All is not lost yet, Nick.";
            link.l1.go = "exit";
            NextDiag.TempNode = "DKStep_2";
		break;

        case "DKStep_3":

            dialog.text = "Recently, a doctor came from a customer, he examined me... It looks like a deal is about to happen.";
        	link.l1 = "Calm down, Nicholas. The gold intended to buy you has already been inherited by me. You're coming with us tomorrow night.";
            link.l1.go = "exit";
            Pchar.questTemp.CapBloodLine.Dieke = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
            NextDiag.TempNode = "DKStep_4";
            CloseQuestHeader("DiekeQuest");

		break;

        case "DKStep_4":

            dialog.text = "I can't wait for tomorrow night!";
        	link.l1 = "Me too, Nick.";
            link.l1.go = "exit";
            NextDiag.TempNode = "DKStep_4";

		break;

        case "DKStep_5":

            dialog.text = "I didn't think that so much blood would have to be shed on the way to freedom.";
        	link.l1 = "Nicholas, you're a nice guy, you'll make a smart officer. Will you come with us?";
            link.l1.go = "DKStep_6";

		break;

        case "DKStep_6":

            dialog.text = "To be honest, I don't even know what to do... I wanted to leave the sea, settle on land, find a decent wife and live a quiet life. Now there is no return to England, the situation is the same with Spain and Holland, only France remains, but there is nothing there that would hold me, no one who would help me survive in this cruel world.On the plantations, I managed to make friends with you, Pitt and other slaves. I will go to your service, but when the time comes and I still decide to settle on the shore, do not keep me.";
        	link.l1 = "Okay, I'll take that into account. Now go get ready, we're still not free.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;
			NPChar.model = "PBLine_Daik_0";
			FaceMaker(NPChar);

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("DiekeAdd");
		break;

        //--> Нед Огл

        case "OGLStep_0":

            dialog.text = "What the hell are you talking about?";
        	link.l1 = "I'm talking about the wonderful opportunity to set a course for Curacao tomorrow night.";
            link.l1.go = "OGLStep_1";

		break;

        case "OGLStep_1":

            dialog.text = "Get away from Bishop? Do you think it's that simple? He is not only a sadistic planter, he is also a part-time commander of the Barbados militia...";
        	link.l1 = "I am aware of all this. But I also know that someone really wants to help us. He wants it so much that he will even provide funds for the sloop.";
            link.l1.go = "OGLStep_2";
		break;

        case "OGLStep_2":

            dialog.text = "Well, then I can only envy you and your accomplices...";
        	link.l1 = "Cheer up, my one-eyed friend. I'm here to invite you to come with us.";
            link.l1.go = "OGLStep_3";
		break;

        case "OGLStep_3":

            dialog.text = "Peter, as much as I would like to, I can't.";
        	link.l1 = "What's the problem?";
            link.l1.go = "OGLStep_4";
		break;

        case "OGLStep_4":

            dialog.text = "Ehhh... the problem is money.";
        	link.l1 = "Money? But...";
            link.l1.go = "OGLStep_5";
		break;

        case "OGLStep_5":

            dialog.text = "I took out a loan some time ago. The usurer took pity on me, and I really needed it. He helped me, and I'm not at the age to be so indifferent anymore, I don't want to have debts behind my back.";
        	link.l1 = "But how did you get out of the territory?";
            link.l1.go = "OGLStep_6";
		break;


        case "OGLStep_6":

            dialog.text = "I didn't get out, he was here - he came to the colonel for some reason.";
        	link.l1 = "Okay, okay... I can't leave without a cannoneer, and besides you, I won't find anyone here. How much do you owe?";
            link.l1.go = "OGLStep_7";
		break;

        case "OGLStep_7":

            dialog.text = "I owe five thousand, so forget it, friend. You won't need a cannoneer to get to Curacao.";
        	link.l1 = "Well, let's see.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "OGLStep_8";
            Pchar.questTemp.CapBloodLine.Ogl = false;
            AddQuestRecord("OglQuest", "1");

		break;

        case "OGLStep_8":

            if(CheckAttribute(Pchar, "questTemp.CapBloodLine.Ogl") && Pchar.questTemp.CapBloodLine.Ogl == true)
            {
                dialog.text = "Yes, Peter?";
            	link.l1 = "Your debt is paid off, Ogle. Now I will not tolerate rejection.";
                link.l1.go = "OGLStep_9";
            }
            else
            {
                NextDiag.TempNode = "OGLStep_8";
                dialog.text = "Yes, Peter?";
            	link.l1 = "No, I'm already leaving.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "OGLStep_8";
            }
		break;

        case "OGLStep_9":

            dialog.text = "What? Did you give the money for me?";
        	link.l1 = "Wait for my orders by tomorrow evening.";
            link.l1.go = "exit";
            Pchar.questTemp.CapBloodLine.Ogl = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
            NextDiag.TempNode = "OGLStep_10";
            AddQuestRecord("OglQuest", "3");
            CloseQuestHeader("OglQuest");

		break;

        case "OGLStep_10":

            dialog.text = "What are the orders?";
        	link.l1 = "None yet, Ned.";
            link.l1.go = "exit";
            NextDiag.TempNode = "OGLStep_10";

		break;

        case "OGLStep_11":

            dialog.text = "It was a hot fight, Captain. It's been a long time since I've fighting like I did today.";
        	link.l1 = "Ned, if I'm not mistaken, were you once a cannoneer in the Royal Navy?";
            link.l1.go = "OGLStep_12";

		break;

        case "OGLStep_12":

            dialog.text = "For fifteen years I was the best cannoneer in His Majesty's entire fleet!";
        	link.l1 = "Then, since I am captain of this ship, will you come to me as the senior cannoneer?";
            link.l1.go = "OGLStep_13";

		break;

        case "OGLStep_13":
            dialog.text = "To be honest, I don't even know what to do... I wanted to leave the sea, settle on land, find a decent wife and live a quiet life. Now there is no return to England, the situation is the same with Spain and Holland, only France remains, but there is nothing that would hold me, no one who would help me survive in this cruel world.On the plantations, I managed to make friends with you, Pitt and other slaves. I will go to your service, but when the time comes and I still decide to settle on the shore, do not keep me.";
        	link.l1 = "Okay, I'll take that into account. Now go get ready, we're still not free.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("OglAdd");

		break;

	}
}
