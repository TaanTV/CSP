void ProcessDialogEvent()
{
	ref NPChar, mc;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, rShip;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr;

	float dmg_min, dmg_max, weight;

	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индех в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}

// Вызов персонажей by xxxZohanxxx -->
  	if (findsubstr(sAttr, "CabinPassengerTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
		PChar.GenQuest.CabinPassengerNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Passenger_Talk";
 	}
// <-- Вызов персонажей by xxxZohanxxx
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;

		case "WhisperTownbattle_1":
				dialog.Text = "Your hat is interesting\n(Hint: to pick up the rest of the items press the 1 key above the corpse)";
				//GiveItem2Character(pchar, "blade19");
				//EquipCharacterByItem(pchar, "blade19");
				Pchar.model="PGG_Whisper_0";
				pchar.Whisper.HatEnabled = true;
				TakeNItems(PChar, "hatWhisper", 1);
				EquipCharacterByItem(pchar, "hatWhisper");
				ChangeWhisperHeroModel();
				Link.l1 = "I'm sorry about what happened, buddy. I hope you're not offended.";
				Link.l1.go = "exit_WhisperTownbattle";
		break;

		case "exit_WhisperTownbattle":
			NextDiag.CurrentNode = NextDiag.TempNode;
			WhisperPirateTownBattleMortality();
			//AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit_Self();
		break;
		case "exit_WhisperIncq":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			DoQuestFunctionDelay("WhisperLine_WhisperHits_3", 3.00);
		break;
		case "exit_WhisperAddWidow":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();

			mc = GetMainCharacter();

			mc.Ship.Type = GenerateShipExt(SHIP_VEINARD, true, mc);
			mc.Ship.name="The Black Widow";
			SetBaseShipData(mc);
			mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS10;
			SetCrewQuantityFull(mc);

            SetCharacterGoods(mc,GOOD_FOOD,200);
        	SetCharacterGoods(mc,GOOD_BALLS,300);//2000);
        	SetCharacterGoods(mc,GOOD_MEDICAMENT,300);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,300);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,300);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,1000);
            SetCharacterGoods(mc,GOOD_PLANKS,50);
            SetCharacterGoods(mc,GOOD_SAILCLOTH,50);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,200);//2000);
            SetCharacterGoods(mc,GOOD_EBONY,100);//2000);
		break;
		case "Exit_incq":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperLine_Inquisition", 2.0);
			WaitDate("", 0, 0, 3, 2, 30);
			DialogExit_Self();
		break;
		case "Exit_Special":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;

		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "If you are reading these lines, it means that there is an obvious bug in the code somewhere";
			Link.l1 = "Exit";
			Link.l1.go = "exit";

			//ОЗГ
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if (pchar.questTemp.Headhunter == "halen_room")
        		{
        		    dialog.text = "Well, you can rest for now. I need to get a good night's sleep...";
        			link.l1 = "...";
        			link.l1.go = "exit";
		    		AddDialogExitQuestFunction("RatHunters_Sleep");
        		}
			}
 			//===> Квесты мэра, базар после боевки на палубе
			if (CheckAttribute(pchar, "quest.DestroyPirate_PirateIsOut") || CheckAttribute(pchar, "quest.CaptainComission_CapIsOut"))
			{
				dialog.text = "It's time to get out of here before Cap gets back with the rest of the team...";
				Link.l1 = "...";
    			Link.l1.go = "exit";
				pchar.quest.Munity = "Deads";
			}
			// ==> Английская линейка, квест №8: в поселении буканьеров
   	    	if (pchar.questTemp.State == "ToMansfield_GoOn")
    		{
    		    dialog.text = "The devil!!! What happened here? I need to try to find at least someone alive...";
    			link.l1 = "...";
    			link.l1.go = "exit";
				chrDisableReloadToLocation = false;//снимаем блок перехода
    		}
            // ==> Исп. линейка, квест №4: в спальне донны Анны
            if (pchar.questTemp.State == "Sp4Detection_toMirderPlace")
    		{
    		    dialog.text = "Hmm, a strange letter. She received the news of the arrival of a man... And who could have notified her? Someone who won't attract the attention of the servants with his visit! It can only be a local resident. I need to find and interrogate the local who notified Donna Anna.";
    			link.l1 = "...";
    			link.l1.go = "exit";
                pchar.questTemp.State = "Sp4Detection_FoundLetter";
                AddQuestRecord("Spa_Line_4_MirderDetection", "2");
				AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("", "a"));
    		}
            // ==> Французская линейка, квест №2: в таверне Тортуги
   	    	if (pchar.questTemp.State == "Fr2Letter_SeekProblems")
    		{
    		    dialog.text = "A strange couple, however... Perhaps it's worth tracing where they went...";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.questTemp.Out = 1;
				SaveCurrentQuestDateParam("questTemp");
    		}
			// ==> Изабелла, нашли мёртвую служанку
   	    	if (pchar.RomanticQuest == "SeekIsabella" && pchar.location == "Beliz_ExitTown")
    		{
    		    dialog.text = "It looks like this is Rosita's maid... Salvator's cases are easy to guess-there are innocent corpses everywhere. So I'm on the right track.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.RomanticQuest = "FoundServantGirl";
				characters[GetCharacterIndex("ServantGirl")].LifeDay = 0;
    		}
			// ==> Квест Аскольда, обнаружение входа в пещеру к гробнице
			if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
			{
				dialog.text = "Yeah, there's clearly an entrance somewhere. But it's covered by a stove. I can't log in.";
				link.l1 = "";
				link.l1.go = "exit";
			}
			//===> Квест Аскольда, попытка вскрыть лампу.
			if (pchar.questTemp.Azzy == "Azzy_IHaveLamp" && locations[reload_location_index].type == "shipyard")
			{
				dialog.text = "Yeah, that's what I need: a blowtorch, a rotisserie, tin shears... You can start the operation...";
				Link.l1 = "Apply the tools.";
    			Link.l1.go = "FreedomAzzy";
			}
			//===> шебека Синяя Птица
			if (pchar.questTemp.BlueBird == "seenCarriers")
			{
				dialog.text = "So, I hear some noise. I'll stand here and see what happens next...";
				Link.l1 = "...";
    			Link.l1.go = "exit";
				AddDialogExitQuestFunction("BlueBird_endCaveDialog");
			}
			//Квест нежити на перерождение
			if (CheckAttribute(pchar, "questTemp.HellSpawn.Rebirth"))
			{
				dialog.Text = "(У одного из поверженных противников вы находите клочок бумаги с каким-то текстом, а также пузырёк со странным содержимым)\nКажется, чтобы переродиться, я должен выпить зелье и прочесть вслух этот текст.";
				bMonstersGen = true;
				DeleteAttribute(pchar, "questTemp.HellSpawn.Rebirth");
				Link.l1 = "(perform the ritual)";
				Link.l1.go = "HellSpawn_Ritual";
				Link.l2 = "No, I'm quite satisfied with my current form.";
				Link.l2.go = "exit";
			}
			//Старт за Шарпов
			if (CheckAttribute(pchar, "questTemp.Sharp.Entered_Shore"))
			{
				dialog.Text = "According to the clues on the map, the treasure must be somewhere nearby.";
				bMonstersGen = true;
				DeleteAttribute(pchar, "questTemp.Sharp.Entered_Shore");
				Link.l1 = "We need to find the grotto.";
				Link.l1.go = "Exit_Special";
			}
			//Старт за Мэри и Шарля
			if (CheckAttribute(pchar, "questTemp.SharleMary.Entered_Shore"))
			{
				dialog.Text = "Mother of Heaven, that was a storm... Blood... My head is broken... Damn it, it's all a blur. "+GetSexPhrase("Mary! Where is Mary?!", "Charles! Where is Charles?!")+". There are no planks on the sand, no corpses. The Fortune has sunk or is drifting somewhere at sea. To hell with them all!";
				DeleteAttribute(pchar, "questTemp.SharleMary.Entered_Shore");
				Link.l1 = "I need to find "+GetSexPhrase("Mary.", "Charles.");
				Link.l1.go = "Exit_Special";
			}
			if (CheckAttribute(pchar, "questTemp.SharleMary.Death"))
			{
				dialog.Text = "Oh... "+GetSexPhrase("Poor Mary...", "Poor Charles...")+" I couldn't save you.";
				chrDisableReloadToLocation = false;
				DeleteAttribute(pchar, "questTemp.SharleMary.Death");
				Link.l1 = "I don't know if I can live on after this. I'll go to the beach, maybe someone else survived.";
				Link.l1.go = "Exit";
			}
			//Старт за нежить
			if (CheckAttribute(pchar, "questTemp.Undead.Leave_Crypt"))
			{
				dialog.Text = "Miktu... Meketlu... M... What's wrong with me? I feel that I have to leave this place. I hear the call. Other. They're waiting locked up. There is no strength to resist. I'm coming, God of the dead. I'm coming.";
				DeleteAttribute(pchar, "questTemp.Undead.Leave_Crypt");
				Link.l1 = "It's worth changing into these inconspicuous clothes before visiting the world of the living.";
				Link.l1.go = "Exit_Special";
			}
			//Линейка Виспер
			if (CheckAttribute(pchar, "questTemp.Whisper.Entered_Dungeon"))
			{
				dialog.Text = "Coordinates match. I think I'm in position\nLooks like some kind of underground communication. It's a good place if you don't want to flash your face in front of the cameras.";
				bMonstersGen = true;
				DeleteAttribute(pchar, "questTemp.Whisper.Entered_Dungeon");
				sld = characterFromId("AntonioDeSouza");
				sld.lifeday = 0;
				PChar.quest.PDM_ONV_Nachalo.over = "yes";	//квест "охота на ведьму" недоступна для Виспер
				DeleteAttribute(pchar, "questdata.OhotaNaVedmu");
				if (bBettaTestMode)
                {
			        link.l1 = "Beta Test - skip and start the game.";
			        link.l1.go = "Whisper_Finish";
					Link.l2 = "(re-read the message from the customer)";
					Link.l2.go = "Whisper_mission_1";

                }
				else
				{
					Link.l1 = "(re-read the message from the customer)";
					Link.l1.go = "Whisper_mission_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Inside_Incquisition"))
			{
				dialog.Text = "Damn, it's so loud! Also, this 'weapon' shattered into pieces after the shot. Oh, I'd give anything for my trusty shotgun right now...";
				DeleteAttribute(pchar, "questTemp.Whisper.Inside_Incquisition");
				Link.l1 = "We need to get the saber off the corpse before the rest of the guards come running. It looks like we'll have to fight our way through.";
				Link.l1.go = "exit_WhisperIncq";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Escaped_Incquisition"))
			{
				dialog.Text = "I think I lost track of the chase. I had to flee the city\nAmong other things, the jailer had a map of the island. It marked the settlement of Puerto Principe, which is near here.";
				DeleteAttribute(pchar, "questTemp.Whisper.Escaped_Incquisition");
				Link.l1 = "It's worth trying your luck there.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Near_Chest"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.Near_Chest");

				dialog.Text = "Great, I have the device. Now it's time to get out of here.";
				Log_Info("You have found a quantum clock rectifier.");
				Link.l1 = "...";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.HoldMonologue"))
			{
				string sTemp = ""
				DeleteAttribute(pchar, "questTemp.Whisper.HoldMonologue");
				if (CheckAttribute(pchar, "Whisper.Podralas"))
				{
					pchar.Whisper.PodralasCheck = true;
				}
				dialog.Text = "Damn it! What was missing was that I was thrown into the past, and the time machine is damaged and is together with all my things in the clutches of these unwashed thugs. In addition, I was captured, and in the next few days I will surely be executed."+sTemp;
				//pchar.Whisper.Podralas = true;
				Link.l1 = "We need to get ready. I'm going to get out, sooner or later.";
				Link.l1.go = "exit_incq";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.GetHat"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.GetHat");
				dialog.Text = "Damn it! Bullets whistling around!\nI'm sorry, mate, but I'm borrowing your belongings, and I need them more than ever right now.";
				//GiveItem2Character(pchar, "blade19");
				//EquipCharacterByItem(pchar, "blade19");
				//Pchar.model="PGG_Whisper_0";
				//pchar.Whisper.HatEnabled = true;
				//TakeNItems(PChar, "hatWhisper", 1);
				//EquipCharacterByItem(pchar, "hatWhisper");

				Link.l1 = "";
				Link.l1.go = "WhisperTownbattle_1";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.AfterTownBattle"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.AfterTownBattle");
				dialog.Text = "Looks like we fought back. It's a shame so many people died\nHe said there was a ship waiting for him. It's worth trying to get on it, because the Spanish could probably come back here any time with reinforcements.";
				Link.l1 = "I need to find a cove.";
				Link.l1.go = "exit_WhisperAddWidow";
				PChar.quest.WhisperPirateTownBattle.win_condition.l1 = "location";
				PChar.quest.WhisperPirateTownBattle.win_condition.l1.location = "PuertoPrincipe_Port";
				PChar.quest.WhisperPirateTownBattle.function = "WhisperMeetCrew";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.SmugPatrol"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.SmugPatrol");
				dialog.Text = "I knew it! Of course, patrols come here, this merchant has put noodles on my ears.";
				Link.l1 = "I need to hurry to the deck before my ship is sunk.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Portman_Deck"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.Portman_Deck");
				dialog.Text = "I don't think I'll be able to find out anything wandering around the deck, and they won't let me into the cabin.";
				Link.l1 = "There is only one way out - to board.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.KilledPortman"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.KilledPortman");
				AddQuestRecord("WhisperChardQuest", "7");
				pchar.Whisper.FoundPortmanJournal = true;
				dialog.Text = "Hmm... There is also some kind of cipher in the log. I don't think I can figure it out on my own.";
				Link.l1 = "We need to take it to Chard.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.EngRevenge"))
			{
				AddQuestRecord("WhisperChardQuest", "9");
				CloseQuestHeader("WhisperChardQuest");
				DeleteAttribute(pchar, "questTemp.Whisper.EngRevenge");
				dialog.Text = "It seems that Portman's death angered the British. I can already see ships on the horizon.";
				Link.l1 = "We should hurry to the boat.";
				Link.l1.go = "exit";
			}
			//Линейка Виспер
		break;
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("It was a hot fight... Now you can call the cowards who ran away.", "Ha! It was easy. And those land rats have run away!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Hmm... What would I like to do now?", "What would you like to do?");
		if(!bDisableMapEnter && !CheckAttribute(pchar, "GenQuest.CannotWait") && CheckSaveGameEnabled() == true) // 21.03.09 Warship fix Во время линейки Блада отдыхать нельзя
	    {
				if(PChar.Dozor != "0" && PChar.Dozor != "END")
				{
					if(sti(PChar.Dozor.Riddle.CanInterface) == 1)
					{
							link.l4 = "The current task of the mecachrome.";
							link.l4.go = "Dozor_MekaKhrom";
					}
				}
		}
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
	        	// Для отдыха теперь есть отдельный интерфейс
	            if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    		{
	    			link.l1 = "Rest until morning.";
	    			link.l1.go = "TalkSelf_room_day";
	    		}
	    		else
	    		{
	    			link.l1 = "Rest until nightfall.";
	    			link.l1.go = "TalkSelf_room_night";
	    			link.l2 = "Rest until the next morning.";
					link.l2.go = "TalkSelf_room_day";
	    		}
				//navy --> 13.02.08
				if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
				{
// Вызов персонажей by xxxZohanxxx -->
					link.l3 = "Call me...";
					link.l3.go = "Cabin_PersonSelect";
// <-- Вызов персонажей by xxxZohanxxx
				}
				//navy <--
			}
			else
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "Rest until morning.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "Rest until nightfall.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "Rest until the next morning.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        /*if (CheckAttribute(pchar, "Quest.Loans") || CheckAttribute(pchar, "Quest.Deposits"))
	        {
	    		Link.l4 = "The cash register.";
	    		Link.l4.go = "TalkSelf_CashBook";
			}*/
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Enroll slaves in the team";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
	        {
	            Link.l6 = "Start capturing the nearest city.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }

			if(PChar.ColonyBuilding.Stage != "0" && PChar.ColonyBuilding.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
					{
						Link.l18 = "Hmm... It is necessary to appoint a governor of the colony '" + PChar.ColonyBuilding.ColonyName + "' as soon as possible. Maybe I can handle it myself?";
						Link.l18.go = "ColonyBuilding_Hovernor_1";
					}
				}
			}

			if(PChar.ColonyBuilding.Hovernor == PChar.id)
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
					{
						Link.l19 = "Go to the colony's affairs.";
						Link.l19.go = "ColonyBuilding_Hovernor";
					}
				}
			}

			if(PChar.Dozor != "0" && PChar.Dozor != "END")
			{
				if(sti(PChar.Dozor.Riddle.CanInterface) == 1)
				{
		    			link.l10 = "The current task of the mecachrome.";
		    			link.l10.go = "Dozor_MekaKhrom";
				}
			}

			if (!CheckAttribute(pchar, "questTemp.stels.sea")) pchar.questTemp.stels.sea = GetDataDay();
			bool isBloodPrologue = false;
			if (CheckAttribute(Pchar, "questTemp.CapBloodLine") && Pchar.questTemp.CapBloodLine == true) isBloodPrologue = true;
	        if (pchar.location != Get_My_Cabin() && !isBloodPrologue && !CheckAttribute(pchar, "DisableChangeFlagMode") && sti(pchar.questTemp.stels.sea) != GetDataDay() && CheckSaveGameEnabled() == true)
			{
				Link.l7 = "Give the order to change the flag.";
				Link.l7.go = "TalkSelf_ChangeFlag";
			}
	        if(!bDisableMapEnter && !isBloodPrologue && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(pchar, "ContraInterruptWaiting")) // 21.03.09 Warship fix Во время линейки Блада отдыхать нельзя
	        {
	        	Link.l8 = "I could use a break...";
	    		Link.l8.go = "TalkSelf_StartWait";
	    	}
			if (!CheckAttribute(pchar, "bookreadtoday") && (GetCharacterEquipByGroup(pchar, BOOK_ITEM_TYPE)) != "" && !bDisableMapEnter && !isBloodPrologue && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait")) // 21.03.09 Warship fix Во время линейки Блада отдыхать нельзя
	        {
	        	Link.l9 = "Read a book.";
	    		Link.l9.go = "ReadBook";
	    	}
			Link.l10 = "Prioritize the use of food.";
	    	Link.l10.go = "food_priority";
			if (pchar.location == Get_My_Cabin())
			{
				Link.l11 = "Use food automatically.";
				Link.l11.go = "autofood";
				if(CheckAttribute(pchar, "autofood"))
				{
					Link.l11 = "Stop using food automatically.";
					Link.l11.go = "autofood_stop";
				}
			}
			if (CheckAttribute(pchar, "usepotionbest"))
			{
				link.lpotion = "Remove the priority for the use of the best medicinal goods.";
				Link.lpotion.go = "potion_priority";
			}
			else
			{
				link.lpotion = "Prioritize the use of the best medicinal goods.";
				Link.lpotion.go = "potion_priority";
			}
			if (pchar.location == Get_My_Cabin())
			{
				link.lcompanioncapture = "Instruct the companions on the disposal of loot during boarding.";
				if (CheckAttribute(PChar, "CompanionsLeaveCapturesDrift"))
				{
					link.lcompanioncapture = link.lcompanioncapture + " Order them to act the old way - change the ship if necessary, rob it quickly and drown it.";
				}
				else
				{
					link.lcompanioncapture = link.lcompanioncapture + " Order them to leave the prize ship adrift.";
				}
				link.lcompanioncapture.go = "companion_capture";
			}
			if (findsubstr(PChar.location, "_church" , 0) != -1)
            {
				Link.lfixbag = "To pray to God. (fix bugs)";
				Link.lfixbag.go = "fixbag";
            }
			if(startHeroType == 2)
			{
				if(CheckCharacterItem(pchar, "hatWhisper"))
				{
					if (!CheckAttribute(pchar, "Whisper.Equipped"))
					{
						Link.lWhisperHat = "Stop wearing a hat.";
						Link.lWhisperHat.go = "WhisperHatUnequip";
					}
					else
					{
						Link.lWhisperHat = "Wear a hat.";
						Link.lWhisperHat.go = "WhisperHatEquip";
					}
				}
				if(CheckCharacterItem(pchar, "glasses"))
				{
					if (IsEquipCharacterByItem(pchar, "glasses"))
					{
						Link.lWhisperGlasses = "Stop wearing glasses.";
						Link.lWhisperGlasses.go = "WhisperGlassesUnequip";
					}
					else
					{
						Link.lWhisperGlasses = "Wear glasses.";
						Link.lWhisperGlasses.go = "WhisperGlassesEquip";
					}
				}
				Link.lWhisperPortrait = "Change the portrait.";
				Link.lWhisperPortrait.go = "WhisperPortrait";
			}

			if (bBettaTestMode)
			{
				Link.l12 = "Set the time on the global map. (the value should be float)";
				Link.l12.go = "WorldmapTime";

				Link.l13 = "Modify the equipped blade.";
				Link.l13.go = "BladeModify";
			}

			Link.lSmugglingFlag = "During smuggling transactions, automatically change the flag to a pirate flag in case of an attack by a patrol.";
			Link.lSmugglingFlag.go = "SmugglingFlag";
			if (CheckAttribute(pchar, "SmugglingFlag"))
			{
				Link.lSmugglingFlag = "Disable automatic flag change during smuggling transactions.";
				Link.lSmugglingFlag.go = "SmugglingFlag";
			}
			if (CheckAttribute(loadedLocation, "id"))
			{
				if (loadedLocation.id == "SanGabrielMechanic" && CheckAttribute(pchar, "VedekerDiscount"))
				{
					Link.lhenric = "Ask Henrik to prepare the suit for a new dive.";
					Link.lhenric.go = "RechargeCostume";
				}
			}
			Link.l14 = RandPhraseSimple("Not now. There is no time.", "There's no time. Things are waiting.");
			Link.l14.go = "exit";
		break;

		case "SmugglingFlag":
			if (CheckAttribute(pchar, "SmugglingFlag")) DeleteAttribute(pchar, "SmugglingFlag");
			else pchar.SmugglingFlag = true;
			Dialog.Text = "Done.";
			Link.l12 = "We're done with this.";
			Link.l12.go = "exit";
		break;
// Вызов персонажей by xxxZohanxxx -->
		case "Cabin_PersonSelect":
				Dialog.Text = "Who exactly?";
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l1 = "A companion.";
    				link.l1.go = "Cabin_CompanionSelect";
				}
				if (!bDisableMapEnter)
				{
					if (sti(pchar.Fellows.Passengers.navigator) != -1 || sti(pchar.Fellows.Passengers.boatswain) != -1 || sti(pchar.Fellows.Passengers.cannoner) != -1 || sti(pchar.Fellows.Passengers.doctor) != -1 || sti(pchar.Fellows.Passengers.treasurer) != -1 || sti(pchar.Fellows.Passengers.carpenter) != -1)
					{
					link.l2 = "An officer.";
    				link.l2.go = "Cabin_OfficerSelect";
					}
				}
				if (!bDisableMapEnter)
				{
					link.l3 = "A passenger.";
    				link.l3.go = "Cabin_PassengerSelect";
				}
			link.l4 = "Another time.";
			link.l4.go = "exit";
		break;
// <-- Вызов персонажей by xxxZohanxxx

		case "WorldmapTime":
			Dialog.Text = "Write float amount like x.x, preferably no more than 12.0, or there could be problems and bugs.";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "WorldmapTime_Change";
		break;

		case "WorldmapTime_Change":
			if (stf(GetStrSmallRegister(dialogEditStrings[1])) > 0.0 && stf(GetStrSmallRegister(dialogEditStrings[1])) < 12.1) pchar.wmtimechange = stf(GetStrSmallRegister(dialogEditStrings[1]));
			else pchar.wmtimechange = 0.5;
			if (stf(pchar.wmtimechange) != 0.5) Dialog.Text = "The speed of the global map is set "+pchar.wmtimechange+".";
			else Dialog.Text = "The standard value is set to 0.5.";
			worldMap.date.hourPerSec = stf(pchar.wmtimechange);
			Link.l1 = "Great.";
			Link.l1.go = "exit";
		break;

		case "BladeModify":
			sAttr = GetCharacterEquipByGroup(PChar, BLADE_ITEM_TYPE);
			if (sAttr == "")
			{
				Dialog.Text = "Why are you doing this, you know yourself that you don't have an equipped blade.";
				link.l1 = "Just like that, I wanted to throw the game...";
				link.l1.go = "exit";
			}

			sAttr = GetBladeParams(sAttr, &dmg_min, &dmg_max, &weight);
			iTemp = LanguageOpenFile("ItemsDescribe.txt");
			rShip = ItemsFromID(sAttr);

			Dialog.Text = "Your blade:" + LanguageConvertString(iTemp, rShip.name) + ", damage " + dmg_min + "/" + dmg_max + ", weight " + weight + ". Выберите действие: увеличить/уменьшить характеристики оружия в границах допустимого или просто сгенерировать имбу.";
			link.l1 = "Reduce the minimum damage by 1.";
			link.l1.go = "BladeModifyDecMinDmg";
			link.l2 = "Increase the minimum damage by 1.";
			link.l2.go = "BladeModifyIncMinDmg";
			link.l3 = "Reduce the maximum damage by 1.";
			link.l3.go = "BladeModifyDecMaxDmg";
			link.l4 = "Increase the maximum damage by 1.";
			link.l4.go = "BladeModifyIncMaxDmg";
			link.l5 = "Reduce the weight by 0.05.";
			link.l5.go = "BladeModifyDecWeight";
			link.l6 = "Increase the weight by 0.05.";
			link.l6.go = "BladeModifyIncWeight";
			link.l7 = "Make a super weapon.";
			link.l7.go = "BladeModifyCreateSuper";
			Link.l8 = "That's enough.";
			Link.l8.go = "exit";

			LanguageCloseFile(iTemp);
		break;

		case "BladeModifyDecMinDmg":
			sAttr = GetCharacterEquipByGroup(PChar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(PChar, sAttr);
			sAttr = ModifyGeneratedBlade(sAttr, -1, 0, 0);
			GiveItem2Character(PChar, sAttr);
			EquipCharacterByItem(PChar, sAttr);
			Dialog.Text = "Done.";
			link.l1 = "That's great.";
			link.l1.go = "BladeModify";
		break;

		case "BladeModifyIncMinDmg":
			sAttr = GetCharacterEquipByGroup(PChar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(PChar, sAttr);
			sAttr = ModifyGeneratedBlade(sAttr, 1, 0, 0);
			GiveItem2Character(PChar, sAttr);
			EquipCharacterByItem(PChar, sAttr);
			Dialog.Text = "Done.";
			link.l1 = "That's great.";
			link.l1.go = "BladeModify";
		break;

		case "BladeModifyDecMaxDmg":
			sAttr = GetCharacterEquipByGroup(PChar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(PChar, sAttr);
			sAttr = ModifyGeneratedBlade(sAttr, 0, -1, 0);
			GiveItem2Character(PChar, sAttr);
			EquipCharacterByItem(PChar, sAttr);
			Dialog.Text = "Done.";
			link.l1 = "That's great.";
			link.l1.go = "BladeModify";
		break;

		case "BladeModifyIncMaxDmg":
			sAttr = GetCharacterEquipByGroup(PChar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(PChar, sAttr);
			sAttr = ModifyGeneratedBlade(sAttr, 0, 1, 0);
			GiveItem2Character(PChar, sAttr);
			EquipCharacterByItem(PChar, sAttr);
			Dialog.Text = "Done.";
			link.l1 = "That's great.";
			link.l1.go = "BladeModify";
		break;

		case "BladeModifyDecWeight":
			sAttr = GetCharacterEquipByGroup(PChar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(PChar, sAttr);
			sAttr = ModifyGeneratedBlade(sAttr, 0, 0, -0.05);
			GiveItem2Character(PChar, sAttr);
			EquipCharacterByItem(PChar, sAttr);
			Dialog.Text = "Done.";
			link.l1 = "That's great.";
			link.l1.go = "BladeModify";
		break;

		case "BladeModifyIncWeight":
			sAttr = GetCharacterEquipByGroup(PChar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(PChar, sAttr);
			sAttr = ModifyGeneratedBlade(sAttr, 0, 0, 0.05);
			GiveItem2Character(PChar, sAttr);
			EquipCharacterByItem(PChar, sAttr);
			Dialog.Text = "Done.";
			link.l1 = "That's great.";
			link.l1.go = "BladeModify";
		break;

		case "BladeModifyCreateSuper":
			sAttr = GetCharacterEquipByGroup(PChar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(PChar, sAttr);
			sAttr = GenerateBladeByParams(GetOriginalItem(sAttr), 200, 1000, 0.1);
			GiveItem2Character(PChar, sAttr);
			EquipCharacterByItem(PChar, sAttr);
			Dialog.Text = "Oh, you shouldn't do that... All right, get what you ordered.";
			link.l1 = "Come on over here, and don't argue with the terminator.";
			link.l1.go = "BladeModify";
		break;

		case "HellSpawn_Ritual"://перерождение
			Dialog.Text = "(you feel a little different).";
			pchar.Ritual.ModelChanged = false;
			pchar.sex = "man";
			pchar.animation = "man";
			pchar.model = "PGG_Skeletman_0";
			pchar.HeroModel  = "PGG_Skeletman_0,PGG_Skeletman_1,PGG_Skeletman_2,PGG_Skeletman_3,PGG_Skeletman_4,PGG_Skeletman_5,PGG_Skeletman_6,PGG_Skeletman_7,PGG_Skeletman_8";
			pchar.Ritual.ModelChanged = true;
			SetNewModelToChar(pchar);
			link.l1 = "I don't feel well. I'll go outside.";
			Link.l1.go = "exit";
		break

		case "autofood":
			Dialog.Text = "Enter the percentage to which energy should drop before you start using food (10-90).";
			//PChar.autofood_use
			link.l1 = "";
			Link.l1.edit = 3;
			Link.l1.go = "autofood_percentage";
		break

		case "autofood_stop":
			//DoQuestReloadToLocation(pchar.location, "reload", "LAi_FindNearestFreeLocator("reload", locx, locy, locz)", "");
			DeleteAttribute(pchar, "autofood");
			DeleteAttribute(pchar, "autofood_use");
			dialog.text = "Automatic food usage is disabled.";
			Link.l1 = "That's enough for today.";
			Link.l1.go = "exit";
		break

		case "autofood_percentage":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 10 || iTemp > 90)
			{
				dialog.text = "I'm a little out of my mind today... Another time, perhaps.";
				link.l1 = "The devil!";
				link.l1.go = "exit";
				break;
			}
			PChar.autofood_use = iTemp;
			dialog.text = "Automatic food usage is enabled.";
			pchar.autofood = true;
			link.l1 = "Nice!";
			link.l1.go = "exit";
		break;

		case "food_priority":
			dialog.text = "Which food should I use first?";
			link.l1 = "Less nutritious (Fruits, bread)";
			link.l1.go = "autofood_finished";
			link.l2 = "More nutritious (Fish, meat)";
			link.l2.go = "autofood_finished_betterfood";
		break;

		case "potion_priority":
			if (CheckAttribute(pchar, "usepotionbest"))
			{
				dialog.text = "The priority for the use of the best medicinal goods has been removed.";
				link.l1 = "Nice!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "usepotionbest");
			}
			else
			{
				dialog.text = "Priority has been set for the use of the best medicinal goods.";
				link.l1 = "Nice!";
				link.l1.go = "exit";
				pchar.usepotionbest = true;
			}
		break;

		case "autofood_finished":
			dialog.text = "The priority for food is set.";
			DeleteAttribute(pchar, "betterfood");
			link.l1 = "Nice!";
			link.l1.go = "exit";
		break;

		case "autofood_finished_betterfood":
			dialog.text = "The priority for food is set.";
			PChar.betterfood = true;
			link.l1 = "Nice!";
			link.l1.go = "exit";
		break;

		case "fixbag":
			dialog.text = "What bug will we fix?";
			/* if (!CheckAttribute(pchar, "molitva.bagPP"))
			{
				link.l1 = "Fix the landing bug in Puerto Principe.";
				link.l1.go = "fixbagPP";
			}

			if (!CheckAttribute(pchar, "molitva.bagDMU"))
			{
				link.l2 = "Add a usurer to Des Moines.";
				link.l2.go = "fixbagDMU";
			} */

			link.l99 = "Finish the prayer.";
			link.l99.go = "exit";
		break

		case "fixbagPP":
			dialog.text = "The bug has been fixed.";
			link.l1 = "Amen!";
			link.l1.go = "exit";
			pchar.molitva.bagPP = true;
			Islands[FindIsland("Cuba1")].reload.l5.emerge = "reload1";
		break;
		case "fixbagDMU":
			dialog.text = "A usurer has been added to Des Moines.";
			link.l1 = "Amen!";
			link.l1.go = "exit";
			pchar.molitva.bagDMU = true;

			ref rLoc = LocFromID("DesMoines_Hut2");//реинит домика
			DumpAttributes(rLoc);
			rLoc.id = "DesMoines_bank";
			rLoc.id.label = "Usurer House";
			rLoc.filespath.models = "locations\inside\Pirate_House";
			rLoc.image = "loading\jonny_load\inside\bank03.tga";
			rLoc.type = "shop";
			rLoc.fastreload = "DesMoines";
			rLoc.models.always.locators = "PirH_l";
			rLoc.models.always.tavern = "PirH";
			rLoc.models.always.tavern.level = 65538;
			rLoc.models.always.window = "PirH_w";
			rLoc.models.always.back.level = 65529;
			rLoc.models.day.charactersPatch = "PirH_p";
			rLoc.models.night.charactersPatch = "PirH_p";
			LAi_LocationFightDisable(&rLoc, true);
			DeleteAttribute(rLoc, "MustSetReloadBack");
			DeleteAttribute(rLoc, "models.day.locators");
			DeleteAttribute(rLoc, "models.night.locators");

			DeleteAttribute(rLoc, "models.always.smallhouse");
			DeleteAttribute(rLoc, "models.always.windows");
			rLoc.models.always.window.tech = "LocationWindows";
			rLoc.models.always.window.level = 65539;
			rLoc.locators_radius.soldiers = 0.5;
			rLoc.locators_radius.patrol = 0.5;
			rLoc.locators_radius.smugglers = 0.5;
			rLoc.locators_radius.monsters = 0.5;
			rLoc.locators_radius.prison = 0.5;

			rLoc = LocFromID("OutRHouse");
			rLoc.reload.l2.label = "ExitTown";

			rLoc = LocFromID("DesMoines_town");
			DeleteAttribute(rLoc, "reload.l15");
			rLoc.reload.l7.name = "reload9";
			rLoc.reload.l7.go = "DesMoines_bank";
			rLoc.reload.l7.emerge = "reload1";
			rLoc.reload.l7.autoreload = "0";
			rLoc.reload.l7.label = "Usurer House";
			rLoc.reload.l7.close_for_night = 1;

			ref sld = characterFromID("DesMoines_usurer");
			sld.model = "usurer_8";
			sld.UsurerDeposit = 5000;

		break;

		case "companion_capture":
			dialog.text = "Instructions have been transmitted.";
			if (CheckAttribute(PChar, "CompanionsLeaveCapturesDrift"))
				DeleteAttribute(PChar, "CompanionsLeaveCapturesDrift");
			else
				PChar.CompanionsLeaveCapturesDrift = true;
			link.l1 = "Great!";
			link.l1.go = "exit";
		break;

		case "ReadBook":
			Dialog.Text = "I can read for a couple of hours...";
			WasteTime(4);
			TryReadBook();
			pchar.bookreadtoday = true;
			Link.l6 = "That's enough for today.";
			Link.l6.go = "exit";
		break

		case "TalkSelf_ChangeFlag":
			Dialog.Text = "Which flag do I need at the moment? His shift will take 1 hour.";
			if (IsCharacterPerkOn(pchar, "FlagPir") && sti(pchar.nation) != 4) {Link.l1 = "Raise the pirate flag."; Link.l1.go = "TalkSelf_ChangeFlagPir";}
			if (IsCharacterPerkOn(pchar, "FlagEng") && sti(pchar.nation) != 0) {Link.l2 = "Raise the English flag."; Link.l2.go = "TalkSelf_ChangeFlagEng";}
			if (IsCharacterPerkOn(pchar, "FlagFra") && sti(pchar.nation) != 1) {Link.l3 = "Raise the French flag."; Link.l3.go = "TalkSelf_ChangeFlagFra";}
			if (IsCharacterPerkOn(pchar, "FlagSpa") && sti(pchar.nation) != 2) {Link.l4 = "Raise the Spanish flag."; Link.l4.go = "TalkSelf_ChangeFlagSpa";}
			if (IsCharacterPerkOn(pchar, "FlagHol") && sti(pchar.nation) != 3) {Link.l5 = "Raise the Dutch flag."; Link.l5.go = "TalkSelf_ChangeFlagHol";}
			Link.l6 = RandPhraseSimple("Not now. There is no time.", "There's no time. Things are waiting.");
			Link.l6.go = "exit";
		break;

		case "TalkSelf_ChangeFlagPir":
			Log_Info("The pirate flag is selected");
			FlagsProcess1(4);
			DialogExit_Self();
		break;

		case "TalkSelf_ChangeFlagEng":
			Log_Info("The English flag is selected");
			FlagsProcess1(0);
			DialogExit_Self();
		break;

		case "TalkSelf_ChangeFlagFra":
			Log_Info("The French flag has been selected");
			FlagsProcess1(1);
			DialogExit_Self();
		break;

		case "TalkSelf_ChangeFlagSpa":
			Log_Info("The Spanish flag has been selected");
			FlagsProcess1(2);
			DialogExit_Self();
		break;

		case "TalkSelf_ChangeFlagHol":
			Log_Info("The Dutch flag has been selected");
			FlagsProcess1(3);
			DialogExit_Self();
		break;

		// Мекахром смотрим
		case "Dozor_MekaKhrom":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchMekakhrom();
		break;

		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;

		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            bOk = (GetPartyCrewQuantity(Pchar, true) >= 500) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
				bool isntFortHere = colonies[FindColony(chr.city)].HasNoFort;
	            if (chr.from_sea == Pchar.location.from_sea && isntFortHere == false)
	            {
					Dialog.Text = "Of course, it is possible to start the capture, but only the ship will not last long under the volleys of the fort. And we won't have time to land the troops.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
	                if (pchar.location == "Santiago_ExitTown")
					{
						if (CheckAttribute(pchar, "PGGWhisperLetter") || CheckAttribute(pchar, "PGGWhisperLetterSent"))
						{
							Dialog.Text = "The fort has enough guns to bury us right in the city. No, Whisper is right - we can only capture Santiago from the sea.";
							Link.l1 = "...";
							Link.l1.go = "exit";
							break;
						}
					}
					if (pchar.location == "Panama_ExitTown")
					{
						Dialog.Text = "Nah, I'm not crazy. This is Panama! It is IMPOSSIBLE to take it!!! We need to get out of here, or I'll definitely wait for the black mark...";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						Dialog.Text = "Attack the city " + GetCityName(chr.City) + ".";
		    			Link.l1 = "To arms!";
		    			Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Stand down!";
		    			Link.l2.go = "exit";
					}
	    		}
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Eh! There is not enough team, at least 500 people are needed.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Don't scatter! We continue the attack!";
					Link.l2 = "...";
					Link.l2.go = "exit";
				}
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
			pchar.HalfOfPaymentByCity = true;
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "None of the slaves want to join the team.";
	            Link.l1 = "Well, you don't have to!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "There is no room for new sailors on the ship.";
	                Link.l1 = "Eh! We need to move some of the crew to another ship.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = pchar.GenQuest.SlavesToCrew+ " slaves want to join the team. Take them?";
	                Link.l1 = "Yes.";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "No";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
	        if (CheckOfficersPerk(pchar, "IronWill"))
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
	        }
	        else
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
	        }
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) +
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) +
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) +
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <--
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew);
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));

	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "Now this great ship is mine, and I'm captain here! It's a pity, we had to cut out the whole team.";
			Link.l1 = "It's time to go ashore...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;

			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трём аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Which of the companions should I call?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "Another time.";
			link.l9.go = "exit";
			break;

// Вызов персонажей by xxxZohanxxx -->
		case "Cabin_OfficerSelect":
			Dialog.Text = "Which officer should I call?";
			if (sti(pchar.Fellows.Passengers.navigator) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.navigator));
				if (chr.location != Get_My_Cabin())
				{
				link.l1 = "Navigator, " + GetFullName(chr) + ".";
				link.l1.go = "Cabin_navigator_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.boatswain) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
				if (chr.location != Get_My_Cabin())
				{
				link.l2 = "Boatswain, " + GetFullName(chr) + ".";
				link.l2.go = "Cabin_boatswain_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.cannoner) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.cannoner));
				if (chr.location != Get_My_Cabin())
				{
				link.l3 = "Cannoneer, " + GetFullName(chr) + ".";
				link.l3.go = "Cabin_cannoner_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.doctor) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.doctor));
				if (chr.location != Get_My_Cabin())
				{
				link.l4 = "Doctor, " + GetFullName(chr) + ".";
				link.l4.go = "Cabin_doctor_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.treasurer) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.treasurer));
				if (chr.location != Get_My_Cabin())
				{
				link.l5 = "Treasurer, " + GetFullName(chr) + ".";
				link.l5.go = "Cabin_treasurer_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.carpenter) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.carpenter));
				if (chr.location != Get_My_Cabin())
				{
				link.l6 = "Carpenter, " + GetFullName(chr) + ".";
				link.l6.go = "Cabin_carpenter_Talk";
				}
			}
			link.l7 = "Another time.";
			link.l7.go = "exit";
			break;

		case "Cabin_PassengerSelect":
			Dialog.Text = "Which of the passengers should I call?";
			for (i = 0; i < GetPassengersQuantity(PChar); i++)
			{
				chr = GetCharacter(GetPassenger(PChar,i));
					if (HasSubStr(chr.id, "ShipWreckSailor"))
					{
						LAi_SetCitizenType(chr);
						sAttr = "l" + i;
						link.(sAttr) = GetFullName(chr) + ".";
						link.(sAttr).go = "CabinPassengerTalk_" + i;
						continue;
					}
					if (!CheckAttribute(chr, "prisoned") && !IsOfficer(chr) && GetRemovable(chr) && chr.location != Get_My_Cabin() && !CheckAttribute(chr, "isfree")) // Чтобы в список не попадали квестовые, офицеры и пленники
					{
						sAttr = "l" + i;
						link.(sAttr) = GetFullName(chr) + ".";
						link.(sAttr).go = "CabinPassengerTalk_" + i;
					}
			}
			link.l99 = "Another time.";
			link.l99.go = "exit";
			break;

		case "Cabin_navigator_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.navigator));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_boatswain_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_cannoner_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.cannoner));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_doctor_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.doctor));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_treasurer_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.treasurer));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_carpenter_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.carpenter));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;

		case "Cabin_Passenger_Talk":
			i = sti(PChar.GenQuest.CabinPassengerNum);
			chr = GetCharacter(GetPassenger(PChar,i));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
// <-- Вызов персонажей by xxxZohanxxx

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		// Квест Аскольда, освобождение Аззи.
		case "FreedomAzzy":
			chr = GetCharacter(NPC_GenerateCharacter("Azzy", "Azzy", "man", "man", 22, PIRATE, -1, false));
			chr.name = "The demon";
			chr.lastname = "Azzie";
			chr.Dialog.Filename = "Quest\Azzy_dialog.c";
			GiveItem2Character(chr, "blade28");// сабля Моргана
			chr.equip.blade = "blade28";
			chr.rank 	= 100;
			chr.reputation = 0;
			SetSelfSkill(chr, 100, 100, 100, 100, 100);
			SetShipSkill(chr, 100, 100, 100, 100, 100, 100, 100, 100, 100);
			LAi_SetImmortal(chr, true);
			LAi_SetActorType(chr);
			LAi_SetLoginTime(chr, 0.0, 24.0);
			LAi_SetHP(chr, 10000.0, 10000.0);
			chr.greeting = "Gr_Azzy";
			ChangeCharacterAddressGroup(chr, pchar.location, "officers", "reload1_1");
			DoQuestCheckDelay("Ascold_AzzyIsFree", 4.0);
			pchar.questTemp.Azzy = "Azzy_Freedom";
			DialogExit();
		break;

		// Сами хотим колонией управлять.
		case "ColonyBuilding_Hovernor_1":
			dialog.Text = "Or find an assistant?";
			Link.l1 = "I guess I'll do it myself. I can handle it.";
			Link.l1.go = "ColonyBuilding_Hovernor_2";
			Link.l2 = "I've changed my mind.";
			Link.l2.go = "Exit";
		break;
	        case "ColonyBuilding_Hovernor_2":
		        bQuestDisableMapEnter = true;
		        Log_SetStringToLog("Since you have become the governor, now you cannot leave the island.");

			PChar.ColonyBuilding.Hovernor = PChar.id;
			DialogExit_Self();
	        break;

		case "ColonyBuilding_Hovernor":
			dialog.Text = "View the current state of affairs of the colony " + PChar.ColonyBuilding.ColonyName + ".";
			Link.l1 = "We need to study the current state of affairs in detail.";
			Link.l1.go = "ColonyBuilding_Hovernor_3";
			Link.l2 = "I don't like this land life.";
			Link.l2.go = "ColonyBuilding_Hovernor_4";
			Link.l3 = "Do nothing.";
			Link.l3.go = "Exit";
		break;

		case "ColonyBuilding_Hovernor_3":
			dialog.Text = "Hmm... What kind of cases do I want to inquire about?";
			Link.l1 = "The state of the colony and its financial capabilities.";
			Link.l1.go = "ColonyBuilding_Hovernor_3_1";
			Link.l2 = "The combat readiness of the garrison and the health of the inhabitants.";
			Link.l2.go = "ColonyBuilding_Hovernor_3_2";
			Link.l3 = "The name of the colony and the appearance of the soldiers.";
			Link.l3.go = "ColonyBuilding_Hovernor_3_3";
			Link.l4 = "Do nothing.";
			Link.l4.go = "Exit";
		break;

		case "ColonyBuilding_Hovernor_3_1":
			DialogExit_Self();
			LaunchColony();
		break;

		case "ColonyBuilding_Hovernor_3_2":
			DialogExit_Self();
			LaunchColonyLandGuard();
		break;

		case "ColonyBuilding_Hovernor_3_3":
			DialogExit_Self();
			LaunchColonyBuilding(true, false);
		break;

		case "ColonyBuilding_Hovernor_4":
			dialog.Text = "Are you sure you don't want to run your colony?";
			Link.l1 = "Yes.";
			Link.l1.go = "ColonyBuilding_Hovernor_5";
			Link.l2 = "No, I've changed my mind. My calling is governor!";
			Link.l2.go = "Exit";
		break;

		case "ColonyBuilding_Hovernor_5":
			PChar.ColonyBuilding.Hovernor = "";
		        bQuestDisableMapEnter = false;
		        Log_SetStringToLog("By ceasing to be a governor, you can once again be a free captain!");
			dialog.Text = "Wonderful! Being a land rat is not my destiny.";
			Link.l1 = "...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "TalkSelf_Main";
		break;

		// Мекахром смотрим
		case "Dozor_MekaKhrom":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchMekakhrom();
		break;

		case "Whisper_mission_1":
			dialog.Text = "'Dear Whisper, Omnitech welcomes you! We have heard that you are the best in your field and we want to offer you one job. The thing is, there is an object - a quantum particle rectifier. This is a dangerous device, in the wrong hands it can harm all mankind. At the moment it is in such hands.'";
			Link.l1.go = "Whisper_mission_2";
		break;
		case "Whisper_mission_2":
			dialog.Text = "'We have sent you the coordinates of the laboratory of the mad scientist who developed this device. He has surrounded himself with a squad of combat bots, but this should not be a big hindrance for you. The payment will be decent, we will not stand behind the price. We have information that a mortgage loan is registered in your name. Consider it already paid off if you take up this case. And hurry up, the device can be activated at any time!'";
			Link.l1 = "Well, let's get started...";
			DeleteAttribute(pchar, "questTemp.Whisper.Entered_Dungeon");
			//AddDialogExitQuest("MainHeroFightModeOn");
			Link.l1.go = "Exit_Special";
		break;
		case "Whisper_Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			Pchar.BaseNation = FRANCE;
			Flag_Change(FRANCE);
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.DisFastTravel = false;
			pchar.Whisper.NanoCostume = true;
			DeleteAttribute(pchar, "questTemp.WhisperLine");
			pchar.Whisper.HatEnabled = false;

			TakeNItems(PChar, "hatWhisper", 1);
			TakeNItems(PChar, "glasses", 1);

			SetQuestHeader("WhisperContraband");
			AddQuestRecord("WhisperContraband", "1");
			pchar.Whisper.Contraband = true;
			pchar.Whisper.FindDesouza = true;
			SetTimerCondition("W_Smuggling", 0, 0, 60, false);

			//initMainCharacterItem();
            mc = GetMainCharacter();

			mc.Ship.Type = GenerateShipExt(SHIP_VEINARD, true, mc);
			mc.Ship.name="The Black Widow";
			SetBaseShipData(mc);
			mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS10;
			SetCrewQuantityFull(mc);

            SetCharacterGoods(mc,GOOD_FOOD,200);
        	SetCharacterGoods(mc,GOOD_BALLS,300);//2000);
        	SetCharacterGoods(mc,GOOD_MEDICAMENT,300);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,300);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,300);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,1000);
            SetCharacterGoods(mc,GOOD_PLANKS,50);
            SetCharacterGoods(mc,GOOD_SAILCLOTH,50);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,200);//2000);
            SetCharacterGoods(mc,GOOD_EBONY,100);//2000);
            DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;
		case "WhisperPortrait":
			dialog.Text = "And what will I look like today?";
			Link.l1 = "Option 1.";
			Link.l1.go = "portrait1";
			Link.l2 = "Option 2.";
			Link.l2.go = "portrait2";
			Link.l3 = "Option 3.";
			Link.l3.go = "portrait3";
			Link.l4 = "Option 4.";
			Link.l4.go = "portrait4";
			Link.l5 = "Option 5.";
			Link.l5.go = "portrait5";
			Link.l6 = "Option 6.";
			Link.l6.go = "portrait6";
			Link.l7 = "Option 7.";
			Link.l7.go = "portrait7";
			Link.l99 = "I think I'll leave it as it is.";
			Link.l99.go = "Exit";
		break;
		case "portrait1":
			pchar.faceID = "543";
			dialog.Text = "Much better.";
			Link.l1 = "That's enough for today.";
			Link.l1.go = "Exit";
		break;
		case "portrait2":
			pchar.faceID = "543_2";
			dialog.Text = "Much better.";
			Link.l1 = "That's enough for today.";
			Link.l1.go = "Exit";
		break;
		case "portrait3":
			pchar.faceID = "543_3";
			dialog.Text = "Much better.";
			Link.l1 = "That's enough for today.";
			Link.l1.go = "Exit";
		break;
		case "portrait4":
			pchar.faceID = "543_4";
			dialog.Text = "Much better.";
			Link.l1 = "That's enough for today.";
			Link.l1.go = "Exit";
		break;
		case "portrait5":
			pchar.faceID = "543_5";
			dialog.Text = "Much better.";
			Link.l1 = "That's enough for today.";
			Link.l1.go = "Exit";
		break;
		case "portrait6":
			pchar.faceID = "543_6";
			dialog.Text = "Much better.";
			Link.l1 = "That's enough for today.";
			Link.l1.go = "Exit";
		break;
		case "portrait7":
			pchar.faceID = "543_7";
			dialog.Text = "Much better.";
			Link.l1 = "That's enough for today.";
			Link.l1.go = "Exit";
		break;
		case "WhisperHatUnequip":
			dialog.Text = "I'll leave her in the cabin, otherwise my head is sweating.";
			ref hatRef = ItemsFromID("hatWhisper");
			string itmGroup = hatRef.groupID;
			RemoveCharacterEquip(pchar, itmGroup);
			ChangeWhisperHeroModel();
			Link.l1 = "It's been dealt with.";
			Link.l1.go = "TalkSelf_Main";
		break;
		case "WhisperHatEquip":
			dialog.Text = "That's much better.";
			EquipCharacterByItem(pchar, "hatWhisper");
			ChangeWhisperHeroModel();
			Link.l1 = "It's been dealt with.";
			Link.l1.go = "TalkSelf_Main";
		break;
		case "WhisperGlassesUnequip":
			dialog.Text = "My eyes are already hurting, I think I'll take off my glasses.";
			ref glassesRef = ItemsFromID("glasses");
			string gItmGroup = glassesRef.groupID;
			RemoveCharacterEquip(pchar, gItmGroup);
			Link.l1 = "It's been dealt with.";
			Link.l1.go = "TalkSelf_Main";
		break;
		case "WhisperGlassesEquip":
			dialog.Text = "That's much better.";
			EquipCharacterByItem(pchar, "glasses");
			Link.l1 = "It's been dealt with.";
			Link.l1.go = "TalkSelf_Main";
		break;
		case "PriestSurprise":
			dialog.Text = "I'm going to throw up... I didn't expect this from visiting a brothel. Let's play, arghhhh, stick holes! It was necessary to send a gay priest to a room of seclusion. God forbid there will be more rumors.";
			Link.l1 = "Well, there's nothing you can do about it, we'll move on.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "TalkSelf_Main";
			chrDisableReloadToLocation = false;
		break;
		case "RechargeCostume":
			if (!CheckAttribute(pchar, "questTemp.LSC.immersions"))
			{
				dialog.Text = "Henrik said that everything is ready to dive.";
				Link.l1 = "That's great.";
				Link.l1.go = "exit";
				pchar.questTemp.LSC = "toUnderwater";
				pchar.questTemp.LSC.immersions = 0;
				pchar.questTemp.LSC.immersions.pay = true;
				SaveCurrentQuestDateParam("questTemp.LSC.immersions");
				WaitDate("", 0, 0, 0, 1, 0);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.immersions") && pchar.questTemp.LSC.immersions.pay == true)
			{
				dialog.Text = "The suit is ready, you can dive in.";
				Link.l1 = "That's great.";
				Link.l1.go = "exit";
				break;
			}
			if (GetQuestPastDayParam("questTemp.LSC.immersions") > 1)
			{
				dialog.Text = "Henrik said that everything is ready to dive.";
				Link.l1 = "That's great.";
				Link.l1.go = "exit";
				pchar.questTemp.LSC = "toUnderwater";
				pchar.questTemp.LSC.immersions = 0;
				pchar.questTemp.LSC.immersions.pay = true;
				SaveCurrentQuestDateParam("questTemp.LSC.immersions");
				WaitDate("", 0, 0, 0, 1, 0);
			}
			else
			{
				dialog.Text = "Henrik said that the suit is not ready for diving and asked to check it tomorrow.";
				Link.l1 = "What can I do...";
				Link.l1.go = "exit";
			}
		break;

	}
}

void  DialogExit_Self()
{
    DialogExit();
	locCameraSleep(false); //boal
}


void FlagsProcess1(int nation)
{
	// boal 04.04.2004 -->
	bool bTmpBool = true;
	int i, cn;
	ref chref;

	Sea_ClearCheckFlag(); // сбросить всем в море проверку смотрения на флаг.
	Flag_Change(nation);
	DoQuestFunctionDelay("FreeChangeFlagMode", 15.0); // ролик + запас

	switch (nation)
	{
    	case ENGLAND:	EnglandProcess();	break;
    	case FRANCE:	FranceProcess();	break;
    	case SPAIN:		SpainProcess();		break;
    	case PIRATE:	PirateProcess();	break;
    	case HOLLAND:	HollandProcess();	break;
	}
}

void PirateProcess()
{
	pchar.DisableChangeFlagMode = true;
    //DoQuestCheckDelay("pir_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "Pirate";
    PChar.GenQuest.VideoAfterQuest = "pir_flag_rise";

    //DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void EnglandProcess()
{
	pchar.DisableChangeFlagMode = true;
    //DoQuestCheckDelay("eng_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "England";
    PChar.GenQuest.VideoAfterQuest = "eng_flag_rise";

    //DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void FranceProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "France";
    PChar.GenQuest.VideoAfterQuest = "fra_flag_rise";

    //DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void SpainProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "Spain";
    PChar.GenQuest.VideoAfterQuest = "spa_flag_rise";

    //DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void HollandProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "Holland";
    PChar.GenQuest.VideoAfterQuest = "hol_flag_rise";

    //DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

