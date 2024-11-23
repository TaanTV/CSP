// Блад
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sLocator, sTemp;
    int iTime, n, iChar;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);




	switch(Dialog.CurrentNode)
	{

		// ----------------------------------- Диалог первый - первая встреча
		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Exit_Away":

            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", Pchar.questTemp.sLocator, "none", "", "", "", sti(Pchar.questTemp.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

        case "Exit_RunAway":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", Pchar.questTemp.sLocator, "none", "", "", "", sti(Pchar.questTemp.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;




        case "sfight":

			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
            LAi_group_Attack(NPChar, Pchar);

		break;

        case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
            AddDialogExitQuest("MainHeroFightModeOn");
			chrDisableReloadToLocation = false;
            LAi_CharacterPlaySound(npchar, "toArm");

		break;

        case "Qfight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			LAi_group_FightGroups(GetNationNameByType(ENGLAND) + "_citizens", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			chrDisableReloadToLocation = true;
			//#20190120-03
			LAi_group_SetCheck("TmpEnemy", "OpenTheDoors");

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
			dialog.text = LinkRandPhrase("Robbery in broad daylight!!! What is this that is being done?! Well, wait a minute, buddy...", "Hey, what are you doing there?! No way, you're trying to rob me? Well, then you're finished...", "Wait, where are you going? You're a thief, it turns out! Well, consider that you have sailed, dear...");
			link.l1 = LinkRandPhrase("The devil!!", "Carramba!!", "Oh, shit!");
			link.l1.go = "Qfight";
		break;

        case "Draguns_0":
			dialog.text = LinkRandPhrase("Here he is-hold him!", "Grab him guys!", "Wait a minute!");
			link.l1 = LinkRandPhrase("The devil!!", "No way!", "Oh, shit!");
			link.l1.go = "Draguns_1";
 		     NextDiag.TempNode = "Draguns_0";
		break;

        case "Draguns_1":

            LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

		break;

		case "First time":
        	dialog.text = "Error";
            link.l1 = "...";
            link.l1.go = "Exit";


            if (CheckAttribute(npchar, "CityType") && npchar.CityType == "soldier")
            {

                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape2_1")
                {
                    dialog.text = "Go your own way and don't distract me.";
					link.l1 = "I'm afraid it's a serious matter. A Spanish spy got into the city, perhaps even a mercenary. He went to the armorer's house, and now the door to Griffin is tightly closed.";
					link.l1.go = "SQStep_0";
					Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_2";
				    break;
                }

               	if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY || ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
                {

    				dialog.text = RandPhraseSimple("Stop! Surrender your weapons! Follow me!", "A runaway slave! Grab him immediately!");
    				link.l1 = RandPhraseSimple("Shut up, you little fool!", "No way!");
    				link.l1.go = "sfight";
    				break;
				}

        		switch (rand(5))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Why is a slave hanging around here doing nothing?";
							link.l1 = "I'm running an errand for Colonel Bishop.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Oh, it's you, Dr. Blood. You treated me when I was decommissioned from Pride of Devon.";
							link.l1 = "I'm glad you've recovered.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Get away, slave!";
							link.l1 = "I'm glad to see you too, whoever you are.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "What a weather, and I have to stand here. My only entertainment is to keep the flies off my face.";
							link.l1 = "I'm sorry. But I can't help you, that's your job.";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "If you want to chat, then find someone else, or better yet, go back to the plantations.";
							link.l1 = "Absolutely.";
							link.l1.go = "exit";
						break;



						case 5: ////////////////////////////////////////////
							dialog.text = "Go your own way and don't distract me.";
							link.l1 = "Whatever you say, soldier.";
							link.l1.go = "exit";
						break;


					}
    		}

    		if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen")
    		{
            	dialog.text = TimeGreeting() + ", Doctor.";
        		link.l1 = "Hello.";
        		link.l1.go = "Exit";
        		if( Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
        		{
                    link.l2 = RandPhraseSimple("Can you tell me where I can find Dr. Wacker?", "I need Dr. Wacker. Have you seen him?");
                    link.l2.go = "Citizen_0";
                }
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.ShipForJack") && Pchar.questTemp.CapBloodLine.ShipForJack == true)
                {
                    Link.l2 = RandPhraseSimple("I need to get somewhere - can you tell me a decent captain?", "I'm looking for a captain who will take my friend somewhere for a reasonable fee. Is there anyone in mind?");
    				Link.l2.go = "Citizen_1";
                }
    		}

    		if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && npchar.location.group == "merchant")
    		{
                if(findsubstr(Pchar.questTemp.CapBloodLine.stat, "PrepareToEscape" , 0) != -1)
                {
                        if (CheckAttribute(npchar, "quest.bGoodMerch") && sti(Pchar.reputation) > 60)
                        {
                            dialog.text = "Oh, Dr. Blood, hello! I still haven't thanked you."+NPCharSexPhrase(NPChar, " ", "a")+"thank you then for saving my little son, which I still often remember and regret. How nice that I met you today!";
                            link.l1 = "Indeed, it's nice that people strive to thank you at the most appropriate moment. Can you tell me, "+NPCharSexPhrase(NPChar, "dear friend", "my dear")+", where can I get hold of a few cutlasses and a couple of pistols in the shortest possible time without too much noise and fuss?";
                            link.l1.go = "Merchant_0";
                            break;
                        }
                }
                if (CheckAttribute(npchar, "quest.bGoodMerch"))
                {
                    dialog.text = TimeGreeting() + ", Doctor.";
                    link.l1 = "Hello.";
                }
                else
                {
                    dialog.text = "You're blocking my goods. Get out, you slave carrion!";
                    link.l1 = "I'm leaving now.";
                }
        		link.l1.go = "Exit";
				if (CheckAttribute(pchar, "SeekVolverstonRum") && !CheckCharacterItem(pchar, "potionrum") && !CheckAttribute(npchar, "VolverstonRum_fail") && !CheckAttribute(npchar, "quest.bGoodMerch"))
				{
					link.l2 = "Do you happen to have a bottle of rum on sale?";
                    link.l2.go = "Merchant_VolverstonRum";
				}
    		}
    		//Рабы на плантациях - постоянный диалог
    		if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
			    dialog.text = RandPhraseSimple(RandPhraseSimple("I'm so tired-I'm just falling off my feet.", "I don't have the strength to live like this anymore!"), RandPhraseSimple("This job is too hard for me.", "The overseers have already left no living place on my skin!"));
				if(CheckAttribute(pchar, "GenQuest.CaptainComission") && pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
				{
					link.l1 = RandPhraseSimple("Yes, life in captivity is a difficult ordeal. And tell me, are there any among you " + pchar.GenQuest.CaptainComission.SlaveName + "?", "Yes, you won't be envied... Somewhere on the plantation there must be a slave named " + pchar.GenQuest.CaptainComission.SlaveName + ". Do you happen to know him?");
					link.l1.go = "CapComission_1";
				}
				else
				{
					link.l1 = RandPhraseSimple("I'm sorry, buddy.", "I feel sorry for you.");
					link.l1.go = "exit";
				}
    		}

    		if (npchar.id == "Bridgetown_Poorman")
    		{
            	dialog.text = "Hey, kid, flip a coin... Oh, it's you, Dr. Blood.";
        		link.l1 = "Good luck.";
        		link.l1.go = "Exit";
    		}

    		if (npchar.id == "QuestCitiz_Bridgetown")
    		{
            	dialog.text = TimeGreeting() + ", Doctor.";
        		link.l1 = "And you.";
        		link.l1.go = "Exit";
    		}

    		if (npchar.id == "SolderTakeBlades")
    		{
                dialog.text = RandPhraseSimple("Since when do slaves walk around with guns?", "You're Colonel Bishop's slave, why are you armed?");
        		link.l1 = RandPhraseSimple("Uh...", "I don't understand myself...");
        		link.l1.go = "STBStep_0";
    		}

    		if (npchar.id == "Winterwood")
    		{

                if(npchar.location == "Bridgetown_Brothel_room")
                {
                    dialog.text = "What the hell do you want here?! Get out now!";
                    link.l1 = "I'm sorry, but this woman is mine.";
                    link.l1.go = "WWStep_7";
                    break;
                }
                dialog.text = "What the hell do you want here?! Get out now!";
        		link.l1 = "Don't be rude to me! I have a matter for you.";
        		link.l1.go = "WWStep_0";
    		}

    		if (npchar.id == "Quest_Habitue")
    		{
				dialog.text = "And-ik! Oh, man, you look like a seasoned sea wolf! Why don't you buy me a glass of rum?";
				link.l1 = "Maybe I'm a sea wolf, but that doesn't mean I'm going to drink all sorts of trash...";
				link.l1.go = "exit";
    		}

    		if (npchar.id == "Weston")
    		{
				dialog.text = "Get out of my house!";
				link.l1 = "I'm leaving now.";
				link.l1.go = "exit";
    		}

    		if (npchar.id == "MoneySpy")
    		{
                if(npchar.quest.meeting == "1")
                {
                    dialog.text = "Get lost!";
    				link.l1 = "I'm leaving now.";
    				link.l1.go = "exit";
                }
                else
                {
                    npchar.quest.meeting = "1";
                    dialog.text = "Finally! I already thought you weren't coming! So, uh, did you find out anything?";
    				link.l1 = "You mistook me for someone else.";
    				link.l1.go = "MSStep_0";
    				link.l2 = "Uh-uh... yes, of course.";
    				link.l2.go = "MSStep_1";
                }
    		}

    		if (npchar.id == "Fisherman")
    		{
                dialog.text = "Won't you put me a cup, huh? Ic..";
    			link.l1 = "I don't think so.";
                link.l1.go = "exit";
    		}

    		if (npchar.id == "QStranger")
    		{
                dialog.text = "What do you need?";
    			link.l1 = "I'm here to find out if you're going to leave the city, forgetting that you owe thirty thousand to someone?";
                link.l1.go = "QSTStep_0";
    			link.l2 = "Hey, old man, what are you doing? Have you completely forgotten me?";
                link.l2.go = "QSTStep_1";
    			link.l3 = "I'm afraid your situation is serious. Your deception, uh... Raf, has been exposed. If you don't return the 30,000 usurers immediately, you will hang tonight!";
                link.l3.go = "QSTStep_2";
    		}


		break;

		case "CapComission_1":
			dialog.text = "He was unlucky today. The poor man was whipped and shackled. You can find him in the courtyard of the barracks. I'm afraid he won't last long in this kind of sun...";
			link.l1 = "Thanks, buddy.";
			link.l1.go = "exit";
		break;


		case "Citizen_0":

            if (!CheckAttribute(npchar, "quest.btmp"))
            {
                npchar.quest.btmp = true;
                if(rand(3)==2)
                {
                    dialog.text = LinkRandPhrase("I ran to the tavern at a trot - look there. Don't forget to look under the tables.", "I recently went to a tavern, sort of. If I remember correctly, I didn't go out.", "I just popped into a pub... Are you hungover or something?");
                    link.l1 = "Thank you.";
                    link.l1.go = "Exit";
                }
                else
                {
                    dialog.text = RandPhraseSimple(RandPhraseSimple("I don't know, get lost!", "I can't help you."), RandPhraseSimple("Come on, you slave carrion!", "And who is this? I only know Dr. Blood... Oh, it's you, hello."));
                    link.l1 = "Thank you.";
                    link.l1.go = "Exit";
                }

            }
            else
            {
                dialog.text = "Doctor, you've already asked me about this.";
                link.l1 = "I'm sorry.";
                link.l1.go = "Exit";
            }

		break;

		case "Citizen_1":

            dialog.text = LinkRandPhrase("I can't help you.", "With all due respect, Doctor, in your position, you shouldn't ask that.", "Alas, I have no one to recommend to you, Dr. Blood.");
            link.l1 = "Thank you.";
            link.l1.go = "Exit";

		break;

		case "Merchant_VolverstonRum":

        	dialog.text = "There is. That'll be five hundred coins.";
			if (pchar.money >= 500)
			{
				link.l1 = "Here. Give it to me.";
				link.l1.go = "Merchant_VolverstonRum_1";
			}
			link.l2 = "What is so expensive? I'll be back.";
    		link.l2.go = "exit";

		break;

		case "Merchant_VolverstonRum_1":
			AddMoneyToCharacter(pchar, -500);
        	dialog.text = "Wait a minute. And where did a slave get such money from? I won't give you anything. Consider it a price to pay for silence. Now get out, or I'll call the guards!";
    		link.l1 = "Listen, I really need this bottle. It's a matter of life and death.";
    		link.l1.go = "Merchant_VolverstonRum_2";
		break;
		case "Merchant_VolverstonRum_2":
        	dialog.text = "Okay. Pay another thousand, or get lost.";
			if (pchar.money >= 1000)
			{
				link.l1 = "Here, choke on your money already!";
				link.l1.go = "Merchant_VolverstonRum_3";
			}
			else
			{
				link.l1 = "But I don't have that much...";
				link.l1.go = "Merchant_VolverstonRum_2_1";
			}

		break;

		case "Merchant_VolverstonRum_2_1":
			npchar.VolverstonRum_fail = true;
        	dialog.text = "In that case, get out! And don't ask me anymore.";
    		link.l1 = "I wouldn't think about it.";
    		link.l1.go = "exit";

		break;

		case "Merchant_VolverstonRum_3":
			npchar.VolverstonRum_fail = true;
			AddMoneyToCharacter(pchar, -1000);
			TakeNItems(PChar, "potionrum", 1);
        	dialog.text = "Ha, do you have any money left? All right, take your bottle. And don't bother me anymore, slave.";
    		link.l1 = "Yes, I won't come near you now even for a cannon shot.";
    		link.l1.go = "exit";

		break;

		case "Merchant_0":

        	dialog.text = "I won't ask you what you need it for, and if they ask me, I won't have to lie and get out of it. However, I won't be asked for a report until the day after tomorrow, so...";
    		link.l1 = "The day after tomorrow, you can safely say that you provided several sabers and pistols for free use to Dr. Peter Blood, who was a doctor in Bridgetown. I don't think Colonel Bishop will mind...";
    		link.l1.go = "Merchant_1";

		break;

		case "Merchant_1":

        	dialog.text = "My son owes you his life, however, as do I. Here, take this, Dr. Blood. And good luck to you!";
    		link.l1 = "Thank you very much.";
    		link.l1.go = "Exit";
            NextDiag.TempNode = "Merchant_2";
            if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape") Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";//fix чтоб не сбивать
            GiveItem2Character(Pchar, "Weapon_for_escape");                                                                 //уже начатые варианты
            AddQuestRecord("WeaponsForEscape", "10");
    		CloseQuestHeader("WeaponsForEscape");

		break;

		case "Merchant_2":

        	dialog.text = "And good luck to you, Dr. Blood!";
    		link.l1 = "Thank you.";
    		link.l1.go = "Exit";
    		NextDiag.TempNode = "Merchant_2";

		break;


		// ==> Забираем клинки, пистоли.
		case "STBStep_0":
        	dialog.text = "Come on, hand over all your weapons immediately! You should tell Colonel Bishop to give you a good shot...";
    		link.l1 = "Here, take it and forget about it.";
    		link.l1.go = "STBStep_1";
            link.l2 = "Now we'll see who's going to hit who!";
            link.l2.go = "fight";
		break;

		case "STBStep_1":

                dialog.text = "Oh, well, get lost.";
                link.l1.go = "Exit_Away";
                Pchar.questTemp.sLocator = "reload1_back";
                Pchar.questTemp.iTime = 40;
                RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
                RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
				string blads_blade;
				string blads_dagger = "";
				while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
                {
					blads_blade = FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE);
					if (CheckAttribute(Pchar, "questTemp.CapBloodLine.dagger") && Pchar.questTemp.CapBloodLine.dagger == blads_blade) blads_dagger = blads_blade;
                    TakeItemFromCharacter(pchar, blads_blade);
                }
				if (blads_dagger != "") GiveItem2Character (PChar, blads_dagger);
                while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
                }
                //GiveItem2Character(Pchar, "unarmed");
                //EquipCharacterByItem(Pchar, "unarmed");
                SetNewModelToChar(Pchar);
                //свободен
                pchar.quest.CapBloodDetectBlades1.over = "yes";
                pchar.quest.CapBloodDetectBlades2.over = "yes";
                chrDisableReloadToLocation = false;

		break;

		case "STBStep_2":
        	dialog.text = "Colonel Bishop has been looking for you. Go to the plantation immediately...";
    		link.l1 = "Whatever you say.";
            link.l1.go = "Exit_Away";
            //link.l1.go = "finish";
            Pchar.questTemp.sLocator = "gate1_back";
            Pchar.questTemp.iTime = -1;

            chrDisableReloadToLocation = false;
            pchar.quest.CapBloodEscape2.win_condition.l1          = "location";
            pchar.quest.CapBloodEscape2.win_condition.l1.location = "Bridgetown_Plantation";
            pchar.quest.CapBloodEscape2.function                  = "ReturnToPlantation2";

            sld = characterFromID("Hugtorp");
            sld.Dialog.CurrentNode = "HTStep_14";
            ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "goto", "goto18");
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":

            if (Pchar.questTemp.CapBUnarmed == false )
            {
                dialog.text = LinkRandPhrase("Why the hell are you running around the city with a drawn blade? Put the weapon away immediately!", "I order you to sheathe your weapon immediately!", "Hey buddy, stop scaring people! Sheathe your weapon.");
                link.l1 = LinkRandPhrase("Good.", "Okay.", "Whatever you say...");
    			link.l1.go = "exit";
                link.l2 = LinkRandPhrase("The hell with it!", "Dream...", "After the rain, on Thursday.");
                link.l2.go = "fight";
			}
            else
            {
                dialog.text = RandPhraseSimple("Since when do slaves walk around with guns everywhere?", "You're Colonel Bishop's slave, why are you armed?")+"\nА ну, немедленно сдай  все оружие! Следует сообщить полковнику Бишопу, чтобы он всыпал тебе как следует...";
                link.l1 = "Take this, and let's forget about it.";
                link.l1.go = "SoldierNotBladeEx";
                link.l2 = "Now we'll see who's going to hit who!";
                link.l2.go = "fight";
            }
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "SoldierNotBladeEx":

                RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
                RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
                while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "" )
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));

                }
                while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
                }
                //свободен
                pchar.quest.CapBloodDetectBlades1.over = "yes";
                pchar.quest.CapBloodDetectBlades2.over = "yes";

                iChar = GetCharacterIndex("SolderTakeBlades");
                if (iChar != -1)
                {
                    sld = &characters[iChar];
                    LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
                    chrDisableReloadToLocation = false;
                }
                NextDiag.CurrentNode = NextDiag.TempNode;
                DialogExit();

		break;


        // --> Квестовый солдат


 		case "SQStep_0":

            dialog.text = "The Spaniard? You're kidding me!.. The Spaniard couldn't... or...?";
        	link.l1 = "I assure you, it was a Spaniard.";
            link.l1.go = "SQStep_1";
		break;

 		case "SQStep_1":

            dialog.text = "I'm going there immediately. Where is this house located?";
        	link.l1 = "This is Mr. Griffin's house, it's not far from the governor's estate.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.sLocator = "houseSp2";
            Pchar.questTemp.iTime = 20;

            string smodel = NPChar.model;
            if (findsubstr(smodel, "eng_mush" , 0) != -1) smodel = "sold_eng_"+(rand(7)+1);
            sld = GetCharacter(NPC_GenerateCharacter("CPBQuest_Solder", smodel, "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
            SetFantomParamHunter(sld); //крутые парни
            sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true;
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorSetLayMode(sld);
            LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "reload", "reload3");

            sld = &characters[GetCharacterIndex("Griffin")];
            ChangeCharacterAddressGroup(sld, "CommonRoom_MH4", "barmen", "bar1");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToLocator(sld, "goto", "goto2");
            LAi_SetStayTypeNoGroup(sld);
            sld = &characters[GetCharacterIndex("Spain_spy")];
            ChangeCharacterAddressGroup(sld, "CommonRoom_MH4", "goto", "goto2");
            sld.dialog.currentnode = "SSStep_3";
            LAi_SetActorType(sld);
            LAi_ActorDialog(sld, pchar, "", 0, 0);
             //#20190120-02
            LocatorReloadEnterDisable("BridgeTown_town", "houseSp2", false);


            pchar.quest.PrepareToEscape2_3.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape2_3.win_condition.l1.location = "CommonFlamHouse";
            pchar.quest.PrepareToEscape2_3.function                  = "_DeadSolder";

            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_3";
            DoQuestFunctionDelay("SpainSpyAttack", 20.0);

		break;
        // --> Квестовый раб

        case "SLQStep_0":

            dialog.text = "Hello, Mr. Blood, are you like our doctor? Will you give me some medicine for my headache? Sometimes my head hurts so much that it becomes unbearable.";
            if (GetCharacterItem(pchar, "migraine_potion") > 0)
            {
           	    link.l0 = "Here, take this medicine - it will cure your migraine.";
                link.l0.go = "SLQStep_3";
            }
        	link.l1 = "Unfortunately, I have nothing for a headache. And Colonel Bishop will most likely not give money to buy the necessary medicine, since he believes that all the diseases of his slaves are from idleness. Alas, but I can only advise you to rest more when possible.";
            link.l1.go = "SLQStep_1";

        break;

        case "SLQStep_1":

            dialog.text = "Doctor, in my position it is difficult to follow your advice. I don't have any money, but I have something that might be very useful to you. So, if you do manage to get something for me, then I will not remain in debt.";
        	link.l1 = "Okay, I'll try to get some medicine for you.";
            link.l1.go = "Exit";
           	NextDiag.TempNode = "SLQStep_2";

        break;

        case "SLQStep_2":

            dialog.text = "Will you give me the medicine, Doctor?";
            if (GetCharacterItem(pchar, "migraine_potion") > 0)
            {
            	link.l1 = "Yes, I brought the migraine medicine.";
                link.l1.go = "SLQStep_3";
           		link.l2 = "Probably not.";
                link.l2.go = "Exit";
             }
             else
             {
            	link.l1 = "No, I haven't been able to get the right medicine yet.";
                link.l1.go = "Exit";
             }
           	NextDiag.TempNode = "SLQStep_2";

        break;

        case "SLQStep_3":

            dialog.text = "Thank you, Doctor. As a token of gratitude, accept this dagger, I have been hiding it from the overseers for a long time, but I think you will need it more.";
        	link.l1 = "Yes, but slaves are not allowed to have weapons!";
            link.l1.go = "SLQStep_4";
            TakeItemFromCharacter(Pchar, "migraine_potion");
			Pchar.questTemp.CapBloodLine.dagger = GetGeneratedItem("blade5");
			if (CheckAttribute(Pchar, "questTemp.CapBloodLine.dagger")) GiveItem2Character(Pchar, Pchar.questTemp.CapBloodLine.dagger);

        break;


        case "SLQStep_4":

            dialog.text = "Don't worry Doctor, it's easy to hide it under your clothes, so no one will notice anything. Unless you wave it in front of the soldiers.";
        	link.l1 = "Thank you, my friend, get well.";
            link.l1.go = "Exit";
            NPChar.talker = 0;
           	NextDiag.TempNode = "First time";

        break;


        // --> Уинтервуд

        case "WWStep_0":

            dialog.text = "What are you talking about, you slave scum?! What business can you have with me?!";
        	link.l1 = "I need this ring...";
            link.l1.go = "WWStep_1";

        break;

        case "WWStep_1":

            dialog.text = "The ring?! I won't sell it to you for any money! Go and buy yourself another one from some merchant who will agree to deal with a slave!";
        	link.l1 = "I need not only this ring, but also the finger on which it is worn.";
            link.l1.go = "WWStep_2";

        break;

        case "WWStep_2":

            dialog.text = "You will pay dearly for your words!";
        	link.l1 = "I knew it. It's better to do such things without witnesses. Come to the entrance of the city in an hour.";
            link.l1.go = "WWStep_3";

        break;

       	case "WWStep_3":
		Dialog.Text = "Well, I'll meet you outside the gate in an hour. I'll even bring some hardware for you so that it looks a little like a duel.";
		link.l1 = "See you soon.";
		link.l1.go = "WWStep_4";
        break;

		//что ж, пойдём выйдем
	case "WWStep_4":

        PChar.quest.CapBloodLineTimer_3.win_condition.l1            = "Timer";
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.hour  = sti(GetTime() + 1);
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
        PChar.quest.CapBloodLineTimer_3.function = "WinterwoodDuel";

		NextDiag.CurrentNode = "WWStep_5";
		DialogExit();
    break;

    case "WWStep_5":

		Dialog.Text = "Well, what else do you want?";
		link.l1 = "I don't have much time, I want to end you right now!";
		link.l1.go = "WWStep_5_1";
		link.l2 = "I just thought I'd remind you of our meeting.";
		link.l2.go = "Exit";
		NextDiag.TempNode = "WWStep_5";
        break;

    case "WWStep_5_1":
		Dialog.Text = "Hmm, you chose your own destiny!";
		link.l1 = "Let's get down to business.";
		link.l1.go = "WWStep_6";
    break;

	case "talk_off_town":
		Dialog.Text = "Well, are you ready to go to hell?";
		link.l1 = "Yes. Now let's see who's who!";
		link.l1.go = "WWStep_6";
		GiveItem2Character(Pchar, "blade2");
        EquipCharacterByItem(Pchar, "blade2");
        chrDisableReloadToLocation = false;
    break;

	//дуэли быть!
	case "WWStep_6":
		AddDialogExitQuestFunction("Winterwood_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

	break;

    case "WWStep_7":

        dialog.text = "What are you talking about, you slave scum?!";
    	link.l1 = "I bring you the news that the pleasant pastime is canceled.";
        link.l1.go = "WWStep_8";

    break;

    case "WWStep_8":

        dialog.text = "You have three seconds to get back to where you crawled out of and pray that we don't meet again.";
    	link.l1 = "I have a better idea. Let's get angry and challenge me to a duel, and I'll stand and wait.";
        link.l1.go = "WWStep_3";
        n = FindLocation("Bridgetown_Brothel");
        locations[n].reload.l2.disable = true;

    break;

    // --> Алкаш

    case "QHStep_0":

		dialog.text = "And-ik! Oh, man, you look like a seasoned sea wolf! Shall we have a glass of rum? I'm buying.";
		link.l1 = "I may be a sea wolf, but that doesn't mean I'm going to drink with just anyone.";
		link.l1.go = "exit";
		link.l2 = "I'll be happy to join you myself, for the company.";
		link.l2.go = "QHStep_1";
		NextDiag.TempNode = "QHStep_0";

    break;

	case "QHStep_1":
		NextDiag.TempNode = "begin_sit";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
	break;

	case "begin_sit":
		NextDiag.TempNode = "first time";
		dialog.snd = "Voice\HADI\HADI028";
		dialog.text = "Ick! That's what I understand! That's our way! I'm buying a treat today!";
		link.l1 = "Innkeeper, bring me rum!";
		link.l1.go = "QHStep_2";
	break;

	case "QHStep_2":
		WaitDate("",0,0,0, 0, 30);
		dialog.text = LinkRandPhrase("You are a true friend! Let's get to know each other!",
		                             "Ick! What a rum! Well... Let's shudder!",
									 "To your health, and to your speedy release!");
		link.l1 = "Tell me, brother, what kind of stories are going around the taverns?";
		link.l1.go = "QHStep_3";
	break;

	case "QHStep_3":
		dialog.text = "Nothing particularly new... A merchant recently arrived on ship from Jamaica. Rumor has it that he brought a very valuable cargo. If I'm not confusing anything, he seems to be an old acquaintance of Colonel Bishop. He is staying in one of the houses in the city, he is going to stay here for another day or two.";
		link.l1 = "Yes, we had a nice time, well, I have to go.";
		link.l1.go = "exit_sit";
		NextDiag.TempNode = "First time";

		if (CheckNationLicence(HOLLAND)) TakeNationLicence(HOLLAND);
		sTemp = NationShortName(HOLLAND)+"TradeLicence";
		ref rItem = ItemsFromID(sTemp);
		SaveCurrentNpcQuestDateParam(rItem, "Action_date");
		rItem.Action_date = GetCurrentDate();
		rItem.Validity = FindRussianDaysString(24);
		rItem.Validity.QtyDays = 24;

       // pchar.GenQuestBox.CommonStoneHouse = true;
       // pchar.GenQuestBox.CommonStoneHouse.stay = true;

        n = FindLocation("CommonStoneHouse");
        locations[n].private1.items.indian1 = 1;
        locations[n].private1.items.HolTradeLicence = 1;
        locations[n].private1.items.potionrum = 1;
        locations[n].private1.money = 6000;




       // pchar.GenQuestBox.CommonStoneHouse.box1.money = 6000;
       // pchar.GenQuestBox.CommonStoneHouse.box1.items.EngTradeLicence = 1;
       // pchar.GenQuestBox.CommonStoneHouse.box1.items.indian1 = 1;

        //Чарльз Вестон
       	sld = GetCharacter(NPC_GenerateCharacter("Weston", "trader_3", "man", "man", 10, ENGLAND, 1, false));
        sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
        sld.name = "Charles";
        sld.lastname = "Weston";
		sld.greeting = "Gr_bankeer";
        FantomMakeCoolFighter(sld, 7, 100, 50, "topor2", "", 10);
       	LAi_SetImmortal(sld, true);
       	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
        LAi_group_MoveCharacter(sld, sTemp);
        LAi_SetOwnerTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, "CommonStoneHouse", "barmen", "stay");

        pchar.quest.MoneyForDieke.win_condition.l1 = "item";
        pchar.quest.MoneyForDieke.win_condition.l1.item = "HolTradeLicence";
        pchar.quest.MoneyForDieke.function = "MoneyForDieke";
        AddQuestRecord("DiekeQuest", "3");

	break;

	case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
	break;

    //Шпион

    case "MSStep_0":

        dialog.text = "Then get out!";
    	link.l1 = "";
        link.l1.go = "Exit";

    break;

    case "MSStep_1":

        dialog.text = "So how many are there?";
    	link.l1 = "They're all there.";
        link.l1.go = "MSStep_2";
       	link.l2 = "There are five of them.";
        link.l2.go = "MSStep_3";
       	link.l3 = "There are more of them than I could count.";
        link.l3.go = "MSStep_4";

    break;

    case "MSStep_2":

        dialog.text = "That's it? What are you talking about?! Go away, you damned scum!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_3":

        dialog.text = "Five... hmm. That makes sense. Are they armed?";
    	link.l1 = "They have light weapons, they don't flaunt them.";
        link.l1.go = "MSStep_5";
       	link.l2 = "No, they're being pretty peaceful.";
        link.l2.go = "MSStep_6";

    break;

    case "MSStep_4":

        dialog.text = "Their... what?! Get out of my house, you liar! ";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_5":

        dialog.text = "I knew it! It was Griffin who sold them the guns! Are they asking about me or about my goods?";
    	link.l1 = "They were interested in you, they asked the Guards.";
        link.l1.go = "MSStep_7";
       	link.l2 = "They were trying to get something out of the innkeeper about you.";
        link.l2.go = "MSStep_8";

    break;

    case "MSStep_6":

        dialog.text = "Peacefully? You're crazy!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_7":

        dialog.text = "The Guards? (laughs) A clown, though smart! Go to the devil!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_8":

        dialog.text = "The old dog won't give me away. How did they get into the city?";
    	link.l1 = "The Cinco Llagas docked-they came in it.";
        link.l1.go = "MSStep_9";
       	link.l2 = "They made their way into the city at night through the jungle.";
        link.l2.go = "MSStep_10";
       	link.l3 = "They've been here for quite a while, they just haven't shown up.";
        link.l3.go = "MSStep_11";

    break;

    case "MSStep_9":

        dialog.text = "On... A ship? But... You're lying! Fuck you! ";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_10":

        dialog.text = "The jungle... The five of us? You're ridiculous! Get lost. ";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_11":

        dialog.text = "That's right, I'm sure I've seen them before. Okay, you did a good job, man. Also... Who are they?";
    	link.l1 = "Spaniards.";
        link.l1.go = "MSStep_12";
       	link.l2 = "Pirates.";
        link.l2.go = "MSStep_13";
       	link.l3 = "Bounty hunters.";
        link.l3.go = "MSStep_14";

    break;

    case "MSStep_12":

        dialog.text = "Not a bad attempt... I think they've already paid you. Just go away.";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_13":

        dialog.text = "Pirates? (laughs) And you can make me laugh. Go to the sea devil!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_14":

        dialog.text = "Take your money. Tell him I'm satisfied with your work.";
    	link.l1 = "...";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, 1000);
        AddCharacterExpToSkill(pchar, "Sneak", 80);
        AddCharacterExpToSkill(pchar, "Fortune", 30);
    break;

    case "FStep_1":

        dialog.text = "Eh-H... Today, I think I'm buying. Just like yesterday, and the day before yesterday, and every day since... However, it doesn't matter.";
        if(makeint(Pchar.money) >=4 )
        {
            link.l1 = "No, let me treat the best Barbadian fisherman!";
            link.l1.go = "FStep_1_2";
        }
       	link.l2 = "Whatever you say, Lord... of the fishes.";
        link.l2.go = "FStep_1_3";

    break;

   	case "FStep_1_2":
		NextDiag.TempNode = "FStep_2";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
	break;

	case "FStep_1_3":
		NextDiag.TempNode = "FStep_3";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
	break;


    case "FStep_2":

        AddMoneyToCharacter(pchar, -2);
        dialog.snd = "Voice\HADI\HADI028";
        dialog.text = "You're damn right you are! Let's drink to that!";
    	link.l1 = "To the best fisherman! (sending the contents of the mug down his throat) How long have you been doing this, Arnie?";
        link.l1.go = "FStep_4";

    break;

    case "FStep_3":

        dialog.snd = "Voice\HADI\HADI028";
        dialog.text = "What don't you like? Hell, I'm the best fisherman in the whole archipelago!";
    	link.l1 = "It's no wonder to be the best where there are no fish... I caught it too... fish.";
        link.l1.go = "FStep_5";


    break;

    case "FStep_4":

        AddMoneyToCharacter(pchar, -2);
        dialog.text = "It's been decades, my friend. Not the first dozen... but THIS has never happened before, anchor me...";
    	link.l1 = "WHICH one didn't exist before? Okay, let's drink to THAT!";
        link.l1.go = "FStep_6";

    break;

    case "FStep_5":

        dialog.text = "No? No fish?! You need to know the places, you idiot! I found a unique place... The network fills up to capacity overnight-God is my witness!";
    	link.l1 = "Places... I was also looking for places, I was fishing everywhere... There are no fish here, and there are no places. To hell with fishing-it's not a profitable business!";
        link.l1.go = "FStep_7";

    break;

    case "FStep_6":

        dialog.text = "Let's have a drink... And this... such... such a place... it's...";
    	link.l1 = "...";
        link.l1.go = "FStep_8";
       	link.l2 = "Well? What kind of place is this?!";
        link.l2.go = "FStep_Fail";

    break;

    case "FStep_7":

        dialog.text = "You don't know how to search! I can show you how it is... How does it feel...";
    	link.l1 = "...";
        link.l1.go = "FStep_8";
       	link.l2 = "Well? What kind of place is this?!";
        link.l2.go = "FStep_Fail";

    break;

    case "FStep_8":

        Pchar.questTemp.CapBloodLine.fishplace = "Cape Rugged Point.";
        dialog.text = "...It's very close. "+Pchar.questTemp.CapBloodLine.fishplace;
    	link.l1 = "Unbelievable!.. But I have to go now.";
        link.l1.go = "exit_sit";
        NextDiag.TempNode = "First time";
        AddQuestRecord("FishermanQuest", "2");

    break;

    case "FStep_Fail":

        dialog.text = "Oh, you... Go away, you slave scout!..";
    	link.l1 = "May the sea devil take you away!";
        link.l1.go = "exit_sit";
        NextDiag.TempNode = "First time";

    break;

    case "QSTStep_0":

        dialog.text = "Who are you anyway? My name is Alex Winner, I am a merchant! Get out, or I'll outbid you from your master and send you to the bottom hugging the ball!";
    	link.l1 = "Um...";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        if(npchar.location == "CommonRoom_MH7") Pchar.questTemp.sLocator = "reload1"
        Pchar.questTemp.iTime = -1;
   		CloseQuestHeader("UsurerQuest");

    break;

    case "QSTStep_1":

        dialog.text = "Mmm... do we know each other? Could I have forgotten... What's your name?";
    	link.l1 = "Of course, Raf! But... If you've forgotten my debt to you, then...";
        link.l1.go = "QSTStep_3";

    break;


    case "QSTStep_2":

        dialog.text = "What are you talking about? I do not know any usurer!.. I... damn it!";
    	link.l1 = "Give me the money, and I'll tell Governor Steed that you voluntarily returned it, and I'll let you go.";
        link.l1.go = "QSTStep_6";

    break;

    case "QSTStep_3":

        dialog.text = "I remember... it seems. Right. So, when will you pay me back?";
    	link.l1 = "The duty of life, my friend... Where would you like to die? Maybe right here?";
        link.l1.go = "QSTStep_4";

    break;

    case "QSTStep_4":

        dialog.text = "What?!";
    	link.l1 = "You betrayed me, Guinness! I lost everything because of you!.. You're going to die!";
        link.l1.go = "QSTStep_5";

    break;

    case "QSTStep_5":

        PChar.quest.QUsurer.win_condition.l1            = "Timer";
        PChar.quest.QUsurer.win_condition.l1.date.hour  = 0;
        PChar.quest.QUsurer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
        PChar.quest.QUsurer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        PChar.quest.QUsurer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
        PChar.quest.QUsurer.function = "QUsurerLate";

        AddMoneyToCharacter(pchar, 55000);
        ChangeCharacterReputation(PChar, -10);
        AddCharacterExpToSkill(pchar, "Leadership", 30);
        dialog.text = "No, wait... look... I've got 55,000. Take it all!";
    	link.l1 = "Thank you very much, dear friend.";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        if(npchar.location == "CommonRoom_MH7") Pchar.questTemp.sLocator = "reload1";
        Pchar.questTemp.iTime = -1;
        AddQuestRecord("UsurerQuest", "3");

    break;

    case "QSTStep_6":

        PChar.quest.QUsurer.win_condition.l1            = "Timer";
        PChar.quest.QUsurer.win_condition.l1.date.hour  = 0;
        PChar.quest.QUsurer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
        PChar.quest.QUsurer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        PChar.quest.QUsurer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
        PChar.quest.QUsurer.function = "QUsurerLate";

        AddMoneyToCharacter(pchar, 30000);
        dialog.text = "You... Okay. Here, take it, take it, damn it!";
    	link.l1 = "Thank you very much, dear friend.";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        if(npchar.location == "CommonRoom_MH7") Pchar.questTemp.sLocator = "reload1"
        Pchar.questTemp.iTime = -1;
        AddQuestRecord("UsurerQuest", "4");

    break;

    //Жак Соловей

    case "JSTStep_0":

        dialog.text = "Hello, stranger. Are you here on business? If not, fuck off.";
    	link.l1 = "That's not very polite... And who are you? I have not heard that our merchant has changed.";
        link.l1.go = "JSTStep_1";

    break;

    case "JSTStep_1":

        dialog.text = "Maybe... Is it because he hasn't changed, eh, my friend?";
    	link.l1 = "I have no honor to be your friend. Let me guess... Are you a pirate? Or a simple thief?";
        link.l1.go = "JSTStep_2";

    break;

    case "JSTStep_2":

        dialog.text = "You are surprisingly ignorant! Haven't you heard of Captain Rolando Pizarro?";
    	link.l1 = "Should I have heard?";
        link.l1.go = "JSTStep_3";

    break;

    case "JSTStep_3":

        dialog.text = "Hmm, let me fill in this hurtful gap of your awareness. So, I hasten to introduce myself! Captain Rolando Pizarro, aka the Catalan Fox! A champion of justice and honor! It is known in all Seven Seas from the northern ice, to...";
    	link.l1 = "It's all very interesting, but what are you, a champion of justice and so on, doing here?";
        link.l1.go = "JSTStep_4";
    break;

    case "JSTStep_4":

        dialog.text = "I? What am I doing here... Um, well, let's say the same as you! Yes, exactly! Why did you come here?";
    	link.l1 = "Honestly? Or a version for the public?";
        link.l1.go = "JSTStep_6";

    break;

    case "JSTStep_6":

        dialog.text = "Let's be honest, we're friends now, right? When two people break into the same store at the same time, without the owner's knowledge, Heaven just tells them to become friends, isn't it?";
    	link.l1 = "Have you tried to speak in parliament? So many speeches, and not a single answer. Okay, I need money more than new acquaintances right now, so I'm sorry, but I have to go.";
        link.l1.go = "JSTStep_7";

    break;

    case "JSTStep_7":

        dialog.text = "Hey, hey, take your time, sir! Let's combine business with pleasure - I just, by pure chance, got hold of a few coins... and if you decide to continue our acquaintance, some of them may come to you. Well, shall we say, as a sign of friendship?";
    	link.l1 = "Something tells me that this arrangement will not be at all disinterested...";
        link.l1.go = "JSTStep_8";

    break;

    case "JSTStep_8":

        dialog.text = "Well, here we are official again. That's a bad sign, don't you think? Is our friendship already starting to crack at the seams as soon as it comes to money?";
    	link.l1 = "You are an amazingly obsessive and talkative guy. And at any other time, I would...";
        link.l1.go = "JSTStep_9";

    break;

    case "JSTStep_9":

        dialog.text = "Omitting the details, find me someone who will agree to take me to Porto Bello for three thousand, and I'll give you one and a half. Is it a deal? I don't think a single peso would be superfluous in your position?";
    	link.l1 = "Yeah... It's a tempting offer. And there is nothing to choose from. It's a deal.";
        link.l1.go = "JSTStep_10";
       	link.l2 = "You know, you should go... fooling the heads of gullible provincial young ladies! I've had enough for today.";
        link.l2.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        Pchar.questTemp.iTime = -1;

    break;

    case "JSTStep_10":

        dialog.text = "One condition, Mon Sherry-no names. Well, that is, you can name your own, if you want... And here's mine... tell me - I forgot it... or... You'd better say that I'm a beautiful young lady!";
    	link.l1 = "Young lady? however. Okay, I'll figure something out.";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        Pchar.questTemp.iTime = -1;
        AddQuestRecord("PirateQuest", "1");
        Pchar.questTemp.CapBloodLine.ShipForJack = true;
       	sld = characterFromID("Bridgetown_trader");
   	    LAi_RemoveLoginTime(sld);

    break;

    case "JSTStep_11":

        dialog.text = "It's good to see you, my new friend. So, did you manage to help me... with the service we agreed on?";
    	link.l1 = "The corvette 'Floating Briton'. Captain John Miner is already waiting.";
        link.l1.go = "JSTStep_12";

    break;

    case "JSTStep_12":

        dialog.text = "Well, what can I say - bow and thank you very much, oh...";
    	link.l1 = "Get 1500 piastres up, Rolando.";
        link.l1.go = "JSTStep_13";

    break;

    case "JSTStep_13":

        dialog.text = "Of course, of course! I just wanted to express my sincere gratitude to you and offer you a taste of this wonderful rum in order to seal the bonds of a wonderful friendship with a joint toast, which from now on...";
    	link.l1 = "Get 1500 piastres up! I'm waiting... my new friend.";
        link.l1.go = "JSTStep_14";

    break;

    case "JSTStep_14":

        dialog.text = "Be quiet! Here, here's your money!..";
    	link.l1 = "Thank you.";
        link.l1.go = "Exit";
        AddMoneyToCharacter(pchar, 1500);
        AddQuestRecord("PirateQuest", "5");
        CloseQuestHeader("PirateQuest");
        NextDiag.TempNode = "JSTStep_15";
        NPChar.lifeDay = 0;

    break;

    case "JSTStep_15":

        dialog.text = "I am grateful to you... friend. Go spend your money on something beautiful.";
    	link.l1 = "And good luck to you...";
        link.l1.go = "Exit";
        NextDiag.TempNode = "JSTStep_15";

    break;

    //Джон Майнер

    case "MNStep_0":

        dialog.text = "John Miner, captain of the corvette Floating Briton, at your service. How can I help you?";
    	link.l1 = "Good afternoon, my name is Peter Blood. May I ask you a favor, Captain? One of my, um... friends really needs to get to Porto Bello, and he's ready to say goodbye to three thousand piastres.";
        link.l1.go = "MNStep_1";

    break;

    case "MNStep_1":

        dialog.text = "May I ask your friend's name, Mr. Blood?";
    	link.l1 = "Of course. His name is... her... in general, yes - it is, in fact, she...";
        link.l1.go = "MNStep_2";
       	link.l2 = "Of course. His name is Rolando Pizarro, have you heard?";
        link.l2.go = "MNStep_3";
       	link.l3 = "No.";
        link.l3.go = "MNStep_4";

    break;

    case "MNStep_2":

        dialog.text = "Young lady? Your friend... I mean, is a friend going to Porto Bello?";
    	link.l1 = "Why not? Porto Bello is quite a decent port. Why doesn't the young lady go there?";
        link.l1.go = "MNStep_5";

    break;

    case "MNStep_3":

        dialog.text = "I am... I've heard, yes. Well, I'm waiting for him on board. Thank you for the truthful answer, Mr. Blood.";
    	link.l1 = "Honesty is a double-edged blade. All the best. I hope you won't regret your decision.";
        link.l1.go = "MNStep_Exit";

    break;


    case "MNStep_4":

        dialog.text = "No? How can I agree to take a passenger if I don't even know his name?!";
    	link.l1 = "You can do it. Let's just say it's a Mrs. Taylor... Yes, that's right-Mrs. Taylor, who... which will give you three thousand in gold if you stop asking questions.";
        link.l1.go = "MNStep_6";

    break;

    case "MNStep_5":

        dialog.text = "Okay, I'll take him... her. Tell my future passenger that the 'Floating Briton' is ready to depart.";
    	link.l1 = "Thank you.";
        link.l1.go = "MNStep_Exit";
        AddCharacterExpToSkill(pchar, "Sneak", 50);

    break;

    case "MNStep_6":

        dialog.text = "You should have said that right away! It's a deal-I'm waiting for Miss Taylor, on board.";
    	link.l1 = "Mrs. Taylor, with your permission. Have a nice day, Captain.";
        link.l1.go = "MNStep_Exit";

    break;

   	case "MNStep_Exit":

            AddQuestRecord("PirateQuest", "4");
            sld = characterFromID("Jack");
            sld.Dialog.CurrentNode = "JSTStep_11";
            LAi_SetSitTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit", "sit4");
            LAi_SetActorType(npchar);
 			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
	break;


    //Служанка Арабеллы

    case "ASStep_0":

        dialog.text = "Did you save me? Who are you?!";
    	link.l1 = "I'm Peter Blood, uh... the local doctor. Will you wait for me to show you my documents? And what the hell is going on here?";
        link.l1.go = "ASStep_1";
        ChangeCharacterReputation(pchar, 5);

    break;

    case "ASStep_1":

        dialog.text = "Spaniards... they are... That big ship, which was allowed to enter our bay so calmly today under a false flag, turned out to be a Spanish privateer. His trick with the flag remained undiscovered so much that, without arousing suspicion, he calmly entered the bay and saluted the fort at point-blank range with a broadside of twenty guns...";
    	link.l1 = "And now, as I understand it, the crew of this privateer is robbing the city?";
        link.l1.go = "ASStep_2";

    break;

    case "ASStep_2":

        dialog.text = "Yes, by sunset our garrison surrendered and two hundred and fifty Spaniards became masters of Bridgetown.";
    	link.l1 = "This is what is called the timely intervention of fate. Although only the devil knows what will come of all this! And you - run into the forest and hide until the Spaniards leave the city.";
        Pchar.questTemp.CapBloodLine.SpainInBridgetown = true;
        Pchar.questTemp.sLocator = "gate1_back";
        Pchar.questTemp.iTime = -1;
        link.l1.go = "Exit_RunAway";
        AddQuestRecord("EscapeFormBarbados", "3");

    break;


	}
}

