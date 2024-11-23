// Слухи - диалог по типажам

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	switch(Dialog.CurrentNode)
	{
	case "rumours_citizen":
		NextDiag.CurrentNode = "rumours";
		//------------- квестовые слухи горожан --------->>>>>>>>
		//жемчужный генератор Шарпа
		if(CheckAttribute(NPChar, "city") && pchar.questTemp.Sharp.City == npchar.city && sti(pchar.questTemp.Sharp.City.rumour))
		{
			pchar.questTemp.Sharp.City.rumour = false; //слух дан
			Dialog.Text = Sharp_choiceAction();
			link.l1 = "Um, I see... What else is new?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("Thanks, take my leave.",
									"Have a nice day.");
			link.l2.go = "exit";
			break;
		}

		//квест шебеки Синяя Птица
		if(CheckAttribute(NPChar, "city") && pchar.questTemp.BlueBird.City == npchar.city && pchar.questTemp.BlueBird == "returnMoney" && sti(pchar.questTemp.BlueBird.count)<7)
		{//после 7 флейтов перестаём пускать новые
			Dialog.Text = BlueBurd_setTradeShip();
			link.l1 = "Yeah, I see... What else is new in the city?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("Thanks, take my leave.",
									"Have a nice day.");
			link.l2.go = "exit";
			//новый слух в другом городе
			pchar.questTemp.BlueBird.City = GetSharpCity();
			break;
		}

		if (pchar.questTemp.Slavetrader == "canTakeQuest" && rand(4) == 0)
		{
			sld = characterFromId(pchar.questTemp.Slavetrader.UsurerId);
			Dialog.Text = "They say that a usurer from the colony "+ XI_ConvertString("Colony" + sld.city) +" is looking for a captain who does not disdain to dirty his hands for some profitable work...";
			link.l1 = "Yeah, I see... What else is new in the city?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("Thanks, take my leave.",
									"Have a nice day.");
			link.l2.go = "exit";
			break;
		}

		if(pchar.questTemp.Ascold == "canTakeQuest" && rand(3) == 0)
		{
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
			Dialog.Text = "They say that the storekeeper from the colony "+ XI_ConvertString("Colony" + sld.city) +" is looking for some powder, offers a lot of money for it...";
			link.l1 = "Yeah, I see... What else is new in the city?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("Thanks, take my leave.",
									"Have a nice day.");
			link.l2.go = "exit";
			break;
		}

		//<<<<<-------- квестовые слухи горожан -----------------
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 3 )
        srum = SelectRumourEx("citizen", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(". Such are the things...", ". Perhaps this will amuse you.");
            posrep2 = " Captain, do you have any news for our colony?";
            answ1 = RandPhraseSimple(RandSwear() + "Interesting things you're telling me, " + GetFullName(NPChar)+".",
                                 "Then tell me more...");
            answ2 = RandPhraseSimple(RandSwear() + "It's very interesting! I wanted to ask...",
                                 "One more question.");
            answ3 = RandPhraseSimple("Everything happens in the world. I'm sorry, but I don't have any news.",
                                 "I'm in a bit of a hurry, so some other time.");
            answ4 = "";

        }
        else
        {
            posrep1 = " We rarely have anything going on. But if something unusual happens, then everyone is talking about it.";
            posrep2 = " So there's no news. But maybe " + GetAddress_Form(NPChar) + " captain knows something?";
            answ1 = RandPhraseSimple("Then tell me better...",
                                 RandSwear() + "You don't know anything! I wanted to ask...");
            answ2 = RandPhraseSimple("You say you don't know, okay, then tell me...",
                                 "Yes, you didn't help me much, but maybe you know something else?");
            answ3 = RandPhraseSimple("I don't think I know anything that might interest you.",
                                 "I'll be happy to tell you something, but some other time.");
            answ4 = "";

        }
		Dialog.Text = NPCStringReactionRepeat(srum,
                                                srum+posrep1,
                                                srum+posrep2,
                                                RandPhraseSimple("Unfortunately, I don't know anything else, let me go.",
                                                                    "You've tired me out with your questions, I'm sorry, but I have things to do."),
                                                "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Thanks, take my leave.",
                                 "Have a nice day.");
		link.l2.go = "exit";
	break;

	///////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
	case "rumours_sailor":
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(". Such are the things...", ". Perhaps this will amuse you.");
            posrep2 = " And do you, Captain, have any news for our colony?";
            answ1 = RandPhraseSimple(RandSwear() + "Interesting things you're telling me, " + GetFullName(NPChar)+".",
"Then tell me more...");
            answ2 = RandPhraseSimple(RandSwear() + "It's very interesting! I wanted to ask...", "One more question.");
            answ3 = RandPhraseSimple("Everything happens in the world. I'm sorry, but I don't have any news. ", "I'm in a bit of a hurry, so some other time.");
            answ4 = "";
        }
        else
        {
            posrep1 = " We rarely have anything going on. But if something unusual happens, then everyone is talking about it.";
            posrep2 = " So there's no news. But maybe " + GetAddress_Form(NPChar) + " captain knows something?";
            answ1 = RandPhraseSimple("Then tell me better...",RandSwear() + "You don't know anything! I wanted to ask...");
            answ2 = RandPhraseSimple("You say you don't know, okay, then tell me...", "Yes, you didn't help me much, but maybe you know something else?");
            answ3 = RandPhraseSimple("I don't think I know anything that might interest you.", "I'll be happy to tell you something, but some other time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Unfortunately, I don't know anything else, let me go.", "You have tired me with your questions, please forgive me, but I have things to do."), "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Thanks, take my leave.", "Have a nice day.");
		link.l2.go = "exit";
	break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//Black Sails
		if (CheckAttribute(pchar, "BSUrka_Negril") && rand(10) > 5)
		{
			if (npchar.location == "PortRoyal_tavern" || npchar.location == "FortOrange_tavern")
			{
				PChar.quest.BSUrka_Negril.over = "yes";
				DeleteAttribute(pchar, "BSUrka_Negril");
				dialog.text = "Well, your health! Wow, the rum is good. You should know what was going on here in the bay a couple of days ago! A pirate brig, all dented from nukes, with sails like a ghost ship, gave battle to two Spanish frigates. And then, out of nowhere, three pirates on corvettes came from behind the cape! It's not clear who was chasing whom. The Spaniards laid down on their left tack and started firing battery fire. One corvette was shot through from bow to stern, it was a scream! You could hear it in the fort! So, the one that was shot at once fell on board and began to sink, and the other two, with their own broadsides, almost at point-blank range blew the frigate apart. And the brig, which was fleeing from the Spaniards, suddenly became bolder, threw anchor on the port side and made a sharp turn around the chain, so that the mast was even lost. And began to shoot at the pirate from the side. In general, they sank the second corvette together with the Spanish survivor. Heh, my throat's dry.";
				link.l1 = "Here, have another drink. So what happened next? You're telling me an interesting story! I can see this fight in reality!";
				link.l1.go = "BS_NU_11";
				break;
			}
		}
		link.l1 = RandPhraseSimple(RandSwear() + "We need to drink another cup for this...",
                                 "Good. Let's have another one.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Thanks, take my leave.",
                                 "Oh, the strong rum. Okay, I have to go, have a good time.");
		link.l2.go = "exit_sit";
		if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst" && npchar.location == pchar.questTemp.piratesLine.Q5.city_1 + "_tavern")
		{
			dialog.text = "Imagine, I'm sitting without touching anyone, suddenly this Avory flies up and without asking – hit me in the face! He says you owe the dealer money?! And then he says he got it wrong. He made a mistake, and I was left without a tooth! Ah! What's it like?! And, you won't believe it, a week has already passed, but it still hurts. Such pain! Maybe a mug of ale...?";
			link.l1 = "Well, it's possible...";
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "3");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Gen"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFirstUsurer";
			break;
		}
		if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond" && npchar.location == pchar.questTemp.piratesLine.Q5.city_2 + "_tavern")
		{
			dialog.text = "Sat down with me, about five days ago, man, just like you are now. His name was, God forbid... John Avory. He told me how he cheated on a local usurer, heh-heh-heh. That's what he needs, the damned bloodsucker, sits on money and swells, and the working man has nothing to eat...";
			link.l1 = "Yes, these moneylenders are filthy people.";
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "5");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Gen"));
			pchar.questTemp.piratesLine = "PL5Hunter_toSecondUsurer";
			break;
		}
		if (pchar.questTemp.piratesLine == "PL5Hunter_toThird" && npchar.location == pchar.questTemp.piratesLine.Q5.city_3 + "_tavern")
		{
			dialog.text = "There was such a fight three days ago! John Avory had a trick on the cheater. It is notable, I must say, that the uncle is waving a piece of iron. Whack, whack! And there is no cheat. A shout went up, a din. But John is a good guy, he gave everyone in the tavern a drink. I respect you!";
			link.l1 = "Oh how! Cool...";
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "7");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3 + "Gen"));
			pchar.questTemp.piratesLine = "PPL5Hunter_toThirdUsurer";
			break;
		}
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(sings) One day I came across a Hamburg spike. There are woodlice and a fungus on the masts, the skin is rotten, and there is food in the shells. Bedbugs are full of shit, and the galley is full of shit... How is life, sailor, tell me, how is it out there in the sea?";
            link.l1 = "Yes, everything is the same in the sea as always - it is damp and salty. You'd better tell me, do you know where my friend who rented a room here recently went? His name is Francois Gontier.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(sings) I blamed the whiskey for my purple nose, and I took his coat to hell on his advice... Oh, pour sailor! I just got off the flight yesterday, so I'm still a little out of it.";
            link.l1 = "Help yourself, buddy! Well, how was it at sea, what interesting things did you see?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец

		//ОЗГ, Крыса
		if(CheckAttribute(pchar, "questTemp.Headhunter"))
		{
    		if (pchar.questTemp.Headhunter == "Rat_Tavern" && npchar.location == pchar.questTemp.Headhunter.Ratrumcity + "_tavern")
            {
    			dialog.text = "(sings) The Flying Dutchman, the Flying Dutchman, rushes across unknown seas... Eh, sailor, let's drink!";
                link.l1 = "Listen, I was told that sailors from one ship, the Adelaide, staged a drunken pogrom...";
                link.l1.go = "Rat_Tavern_1";
				break;
            }
		}
		//<--ОЗГ, Крыса

		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "Eh, " + GetAddress_Form(pchar) + " what kind of life has gone on now... There is nothing sacred left in the people!";
			link.l1 = "What are you talking about, buddy?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}

		if(CheckAttribute(PChar, "HellSpawn.SeekRebirth"))
	    {
			//получим пещёру для чистки
			pchar.quest.HellSpawn.locationId = "DeckWithReefs"; //Id целевой пещёры
			sld = &locations[FindLocation(pchar.quest.HellSpawn.locationId)];
			npchar.quest.HellSpawn.label = GetConvertStr(sld.id.label, "LocLables.txt"); //тип подземелья для диалогов

			dialog.text = "Eh, " + GetAddress_Form(pchar) + " what kind of life has gone on now... I've heard about the terrible things that are happening on Skeleton Reef. They say the undead gather in the local bay for some kind of rebirth ritual.";
			DeleteAttribute(PChar, "HellSpawn.SeekRebirth");
			SaveCurrentQuestDateParam("pchar.questTemp.HellSpawn.Rit");

			pchar.quest.HellSpawnRitual.win_condition.l1 = "location";
			pchar.quest.HellSpawnRitual.win_condition.l1.location = pchar.quest.HellSpawn.locationId;
			pchar.quest.HellSpawnRitual.function = "HellSpawnRitual";
			AddQuestRecordInfo("Important_rumours", "1");
			AddQuestUserData("Important_rumours", "sSex", GetSexPhrase("", "a"));
			break;
		}

		if(!CheckAttribute(pchar, "SalasarEventKnow") && rand(20)==0 && pchar.rank >= 20)
		{
			dialog.text = "It is rumored that every year on March 3 at 3 o'clock on the Skeleton Reef in the Devil's Canyon on the ruins of the cemetery keeper's house, a particularly bright and frightening glow, which smells of horror and hopelessness. I'd like to see for myself, but too scared...";
			Log_Info("It is worth remembering. So... March 3, 3 o'clock and every year.");
			pchar.SalasarEventKnow = true;
			AddQuestRecordInfo("Important_rumours", "2");
			AddQuestUserData("Important_rumours", "sSex", GetSexPhrase("", "a"));
			break;
		}
		if(CheckAttribute(pchar, "GiantEvilSkeleton") && rand(20)==0 && !CheckAttribute(pchar, "MalteseInfo"))
		{
			 if (pchar.name != "Whisper" && pchar.sex != "skeleton" && !CheckAttribute(pchar, "OrderHunter"))
			 {
				dialog.text = "There are rumors that the Spanish Inquisition is collecting information about the Skeleton Reef. For what purpose is unknown, but anyone who knows anything is promised a reward...";
				Log_Info("It's worth remembering. The Spanish Inquisition and the Skeleton Reef.");
				pchar.MalteseInfo = true;
				AddQuestRecordInfo("Important_rumours", "3");
				AddQuestUserData("Important_rumours", "sSex", GetSexPhrase("", "a"));
				break;
			 }
		}
		if(!CheckAttribute(pchar, "BlackBeardSpawn") && sti(pchar.rank)>=20)
		{
			AddQuestRecordInfo("Important_rumours", "4");
			AddQuestUserData("Important_rumours", "sSex", GetSexPhrase("", "a"));
			dialog.text = "It is said that the ship of Blackbeard himself was seen on the archipelago for the first time in years. Rumor has it that he is looking for the luckiest pirate in the archipelago for some strange business.";
			Log_Info("It's worth remembering. Edward Teach appeared in the archipelago.");
			pchar.BlackBeardSpawn = true;

			sld = GetCharacter(NPC_GenerateCharacter("BlackBeardNPC", "PGG_Tich_0", "man", "man", 60, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 60, 100, 100, "blackbeard_sword", "howdah", 100);
			sld.items.spyglass3 = 0;
			sld.items.spyglass5 = 1;
			EquipCharacterbyItem(sld, "spyglass5");
			sld.name = "Edward";
			sld.lastname = "(Blackbeard) Teach";
			sld.dialog.filename   = "Quest\BlackBeard.c";
			sld.dialog.currentnode   = "Greetings";
			sld.greeting = "";
			sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
			sld.items.GunEchin = 30;
			LAi_SetCharacterUseBullet(sld, "GunEchin");//зарядить патрики покруче
			FantomMakeCoolSailor(sld, SHIP_FRIGATEQUEEN, "Queen Anne's Revenge", CANNON_TYPE_CANNON_LBS36, 90, 90, 90);
			GiveItem2Character(sld, "cirass5");
			EquipCharacterbyItem(sld, "cirass5");

			DeleteAttribute(sld, "DontClearDead");
			DeleteAttribute(sld, "AboardToFinalDeck");
			DeleteAttribute(sld, "SinkTenPercent");
			DeleteAttribute(sld, "DontRansackCaptain");
			sld.AlwaysFriend = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true; //не сдаваться

			SelAllPerksToNotPCHAR(sld);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			SetCharacterPerk(sld, "AgileMan"); // ловкач
			sld.SuperShooter  = true;
			SetSPECIAL(sld, 10,10,10,10,10,10,10); // SPECIAL (Сила, Восприятие, Выносливость, Лидерство, Обучаемость, Реакция, Удача)
			SetSelfSkill(sld, 100, 100, 100, 100, 100); //лёгкое, среднее, тяжёлое, пистолет, удача
			SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100); // лидерство, торговля, точность, пушки, навигация, ремонт, абордаж, защита, скрытность
			LAi_SetHP(sld,1500,1500);
			SetCharacterPerk(sld, "Grunt"); //рубака
			AddBonusEnergyToCharacter(sld, 50);
			TakeNItems(sld, "potion2",10);

			//в морскую группу кэпа
			sGroup = "BlackBeardGroup";
			Group_FindOrCreateGroup(sGroup);
			Group_AddCharacter(sGroup, sld.id);
			Group_SetGroupCommander(sGroup, sld.id);
			Group_SetType("BlackBeardGroup", "pirate");
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			SetRandGeraldSail(sld, sti(sld.Nation));
			sld.quest = "InMap"; //личный флаг искомого кэпа
			sld.city = "LaVega"; //определим колонию
			sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
			sld.quest.targetCity = GetRandomPirateCity(); //определим колонию, в бухту которой он придёт
			sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
			Log_TestInfo("The frigate Queen Anne's Revenge left: " + sld.city + " and headed to: " + sld.quest.targetShore);
			//==> на карту
			sld.mapEnc.type = "trade";
			//выбор типа кораблика на карте
			sld.mapEnc.worldMapShip = "Tich_MKA"; // LEO: Сюда надо заюзать модельку МКА на глобалку, персональную.
			sld.mapEnc.Name = "The frigate 'Queen Anne's Revenge'";
			int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city)) + 1; //дней доехать даём с запасом
			Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
			//заносим Id кэпа в базу нпс-кэпов
			sTemp = sld.id;
			NullCharacter.capitainBase.(sTemp).quest = "BlackBeard"; //идентификатор квеста
			NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
			NullCharacter.capitainBase.(sTemp).Tilte1 = "BlackBeard"; //заголовок квестбука
			NullCharacter.capitainBase.(sTemp).Tilte2 = "BlackBeard"; //имя квеста в квестбуке
			NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 2;
			NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
			NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
			NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
			break;
		}

		if (!CheckAttribute(pchar, "PGG_killed_known")) pchar.PGG_killed_known = 0;
		if (CheckAttribute(pchar, "PGG_killed") && sti(pchar.PGG_killed) > 4 && pchar.PGG_killed != pchar.PGG_killed_known)
		{
			pchar.PGG_killed_known = pchar.PGG_killed;
			dialog.text = "They say that in our waters "+GetSexPhrase("got a hunter for honest corsairs, ", "got a hunter for honest corsairs, ") + GetFullName(pchar)+GetSexPhrase("his", "her") + " call. The number of souls sent to the next world by this person has already reached " + pchar.PGG_killed + ". All the respected people in these places. Brr... Something is starting to make me sick. Either because of the rum, or the whole story...";
			break;
		}
		//Титаник
		if (CheckAttribute(pchar, "TitanicRumour") && rand(100) > 80)
		{
			AddQuestRecord("WhisperTitanic", 6);
			AddQuestUserData("WhisperTitanic", "sCity", XI_ConvertString("Colony" + pchar.TitanicCity));
			DeleteAttribute(pchar, "TitanicRumour");
			dialog.text = "That's rum! By the way, Captain, I do not advise you to go into the " + XI_ConvertString("Colony" + pchar.TitanicCity) + ". There's an English floating fortress out there right now.'Titanic' is its name, it seems...";
			break;
		}
		//BlackThorn викинг
		if (CheckAttribute(pchar, "questTemp.pirateVikingQuest") && rand(100) > 60)
		{
			if (CheckAttribute(pchar, "LastHearedViking") && pchar.LastHearedViking != npchar.city)
			{
				if (pchar.questTemp.pirateVikingQuest == "4")
				{
					if(ShipsTypes[sti(RealShips[sti(pchar.Ship.Type)].BaseType)].Type.Merchant == true && GetCompanionQuantity(pchar) == 1)
					{
						if (GetSquadronGoods(Pchar, GOOD_EBONY) >= 600 || GetSquadronGoods(Pchar, GOOD_SILK) >= 1000 || GetSquadronGoods(Pchar, GOOD_SILVER) >= 400)
						{
							dialog.text = "I see you are a seasoned merchant, captain, you have seen a lot of troubles. But still, even though I am not a sailor myself, I would give you advice - do not go to sea today. A pirate chirp has been seen in the surrounding waters, which is just hunting people like you.";
							link.l1 = "Ha! Scared the hedgehog with a needle. Yes, if I get this pebble, then consider it already at the bottom. Okay, goodbye.";
							link.l1.go = "exit_sit";
							AddQuestRecord("pirateVikingQuest", "6");
							//Можно будет вызвать повторно, если ещё не убили
							//pchar.questTemp.pirateVikingQuest = "5";
							pchar.LastHearedViking = npchar.city;

							if (MOD_SKILL_ENEMY_RATE == 3 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("pirateVikingQuest_Captain", "OZG_3", "man", "man_fast", 20, PIRATE, -1, true)); // LEO: Превозмогаторам - страдать 01.12.2021
							else sld = GetCharacter(NPC_GenerateCharacter("pirateVikingQuest_Captain", "OZG_3", "man", "man", 20, PIRATE, -1, true));
							sld.mapEnc.worldMapShip = "quest_ship";
							sld.mapEnc.Name = "xebec 'Drakkar'";
							sld.mapEnc.type = "war";
							FantomMakeCoolFighter(sld, 20, 80, 80, "topor_viking", "pistol3", 100 * MOD_SKILL_ENEMY_RATE + 100);
							FantomMakeCoolestSailor(sld, SHIP_REQUIN, "Drakkar", CANNON_TYPE_CANNON_LBS24, 80, 80, 60);

							sld.name 	= "Ragnar";
							sld.lastname = "Lodbrok";
							sld.AlwaysSandbankManeuver = true;
							sld.DontRansackCaptain = true;
							sld.AnalizeShips = true;
							if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
							SetCharacterPerk(sld, "MusketsShoot");

							sld.ship.Crew.Morale = 100;
							ChangeCrewExp(sld, "Sailors", 80);
							ChangeCrewExp(sld, "Cannoners", 80);
							ChangeCrewExp(sld, "Soldiers", 60);

							GiveItem2Character(sld, "cirass3");
							EquipCharacterbyItem(sld, "cirass3");
							GiveItem2Character(sld, "talisman10");
							EquipCharacterbyItem(sld, "talisman10");
							GiveItem2Character(sld, "jewelry9");
							SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
							TakeNItems(sld, "Food5", 15);
							TakeNItems(sld, "potion2", 5);
							sld.SaveItemsForDead = true;
							sld.DontClearDead = true;

							LAi_group_MoveCharacter(sld, "Vikings");
							string  sGroup = "Sea_" + sld.id;
							group_DeleteGroup(sGroup);
							Group_FindOrCreateGroup(sGroup);
							Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
							Group_LockTask(sGroup);
							Group_AddCharacter(sGroup, sld.id);
							Group_SetGroupCommander(sGroup, sld.id);
							Map_CreateWarrior("", sld.id, 8);
							SetFunctionNPCDeathCondition("PirateVikingQuest_Captain_Is_Dead", sld.id, false);
							pchar.questTemp.pirateVikingQuest.pcharShipType = pchar.Ship.Type;
							Pchar.quest.pirateVikingShipMapEnterCheck.win_condition.l1 = "MapEnter";
							Pchar.quest.pirateVikingShipMapEnterCheck.win_condition = "ReleaseCheck_pirateVikingShip";
							break;
						}
						else
						{
							dialog.text = "They say there is a pirate ship floating in the surrounding waters. But you have nothing to fear, Captain. Even though you have a merchant ship, they are unlikely to want to waste their strength on such a meager cargo.";
						}
					}
					else
					{
						dialog.text = "They say there is a pirate ship floating in the surrounding waters. But you have nothing to fear, Captain. They only hunt lone merchant ships.";
					}
				}
				if (pchar.questTemp.pirateVikingQuest == "3")
				{
					dialog.text = "They say the local store owner is going to sue a hapless captain. He chartered his ship to deliver a large shipment of Chinese silk, but came with an empty hold! You know, there's a lot of money involved. The accused captain says that he was robbed by some kind of xebec, whose captain is a blue-eyed blond man. The whole team confirms this. Even the damage on the ship is there after the battle, a few dents from the balls, a damaged frame, but the owner of the store still does not believe. He repeats every time that the evidence is fabricated, and captain and his team are lying. But I'm thinking, why would he lie? He has carried freight more than a dozen times, and with much more valuable cargoes. If he wanted to steal, he would have done so long ago.";
					AddQuestRecord("pirateVikingQuest", "4");
					AddQuestRecord("pirateVikingQuest", "5");
					pchar.questTemp.pirateVikingQuest = "4";
					pchar.LastHearedViking = npchar.city;
					break;
				}
				if (pchar.questTemp.pirateVikingQuest == "2")
				{
					dialog.text = "I do not advise you to go to sea, captain. Usually only pirates were there, but now there are also real Vikings! One merchant did not want to part with the silver in his hold to the last, naively hoping that he would be able to fight them back. He paid with the lives of his team. With the wreckage of his ship, a poor fellow, a sailor, who miraculously survived, recently washed up in a local bay. He told me this story. He says he has personally seen these animals. They're big, feisty, and they speak an incomprehensible language!";
					AddQuestRecord("pirateVikingQuest", "3");
					pchar.questTemp.pirateVikingQuest = "3";
					pchar.LastHearedViking = npchar.city;
					break;
				}
				if (pchar.questTemp.pirateVikingQuest == "1")
				{
					dialog.text = "Have you heard, Captain? A merchant has recently returned to our port, which usually sells ebony. Except this time he came with an empty hold. They say he was intercepted at sea by a ship called a Drakkar. The captain wisely raised the white flag and was spared, but robbed to the skin. He is now completely broke and can no longer continue the business. He is going to return to Europe, to his relatives.";
					AddQuestRecord("pirateVikingQuest", "2");
					pchar.questTemp.pirateVikingQuest = "2";
					pchar.LastHearedViking = npchar.city;
					break;
				}
			}
		}
		Dialog.Text = LinkRandPhrase("Well... I-ic! ", "Oh, what a rum! ", "Well... ")+SelectRumourEx("habitue", NPChar);
	break;
//Black Sails
		case "BS_NU_11":
            dialog.text = "Wow. It went well, thank you. And so. The pirate, on the surviving corvette, realized that things were bad, went downwind and ran off over the horizon with all sails! And on the brig, the anchor chain was cut off and the side of the frigate was piled on. So they went on board. And they defeated the Spaniards! The frigate raised the black flag, fired a volley at the battered brig and left, somewhere to the north. There was such a battle, even for a picture! The whole coast is strewn with debris.";
            link.l1 = "Thanks for the story. You should write books with such talent!";
			link.l1.go = "exit_sit";

			BSBons_SeaBattle(true);
			AddQuestRecord("BSUrka", "3");
			PChar.quest.BSUrka_Pirates_town.win_condition.l1 = "location";
			PChar.quest.BSUrka_Pirates_town.win_condition.l1.location = "Nassau_town";
			PChar.quest.BSUrka_Pirates_town.function = "BSUrka_Pirates_town";
		break;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text =  NPCStringReactionRepeat(strum, strum+" Yeah. I don't remember anything else.",
                                                   strum+" And now I need to get back to business.",
                                                    RandPhraseSimple("I've already said that I don't have time for idle chatter!",
                                                                        "I'm a busy person and I don't have time to discuss all sorts of gossip!"),
                                                                         "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + "This is very interesting! But let's get to the point", "Thank you, then here's another thing."),
                                                pcharrepphrase(""+ GetSexPhrase("May I die", "Thunder blast me") +"! You're a good liar. But I have another question.",
                                                                "So let's not waste any more precious time and get down to business."),
                                                pcharrepphrase(RandSwear() +"One more thing, and I'll leave", ".You're right, time is money."),
                                                pcharrepphrase("All you think about is your own benefit. Okay, don't get exited.",
                                                                "Please forgive me. Let's get down to business."),
                                                npchar, Dialog.CurrentNode);

			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Bye, old drunk.",
													               "Have a nice day, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase("Carramba! Don't go anywhere. I'll come back.",
													               "Nice to see you, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! Goodbye!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Give up the mooring lines!",
													               "Goodbye, my dear."),
													pcharrepphrase("Hey! What are you hiding there? Rum? No?! Well, I'm going to wet my whistle.",
													               "Please excuse me, I have urgent business in the city.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Heh! See you again!",
													               "I have to go. Goodbye, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase("And don't you dare contradict me! I don't have time to argue with you here!",
													               "Perhaps it's worth checking out how things are on the ship. Goodbye, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("What's the matter with you, old man? It's me - " +GetFullName(pchar)+ "! Sleep it off, I'll come back later.",
													               "I'm afraid your liver will kill you before I come in here again."),
													pcharrepphrase("Count your piastres, you rascal! I'll come back.",
													               "Glad to see you, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "It's very interesting! I wanted to ask...",
                                     "One more question.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Thanks, thanks, take my leave.",
                                     "Have a nice day");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
                 Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Any information worth money. For humble 1000 coins I'll tell you everything.",
                "I forgot almost everything. But may be 1000 coins will help me remember.",
                "I'm ready" + NPCharSexPhrase(NPChar, "", "a") + " to tell you everything i know. But only for 1000 coins, no less" + NPCharSexPhrase(NPChar, "en", "on") + "."),
                "I have nothing more to add. Now, if you'll excuse me, but things are not waiting for you.",
                "", "", "block", 1, npchar, Dialog.CurrentNode);

    			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + "Pay for empty chatter? No, look for someone else.",
                                         "For such money, I'll find out everything myself."), "Let's talk about something else.", "Let's talk about something else.", "Let's talk about something else.", npchar, Dialog.CurrentNode);
                link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
                NextDiag.CurrentNode = NextDiag.TempNode;
    			if (makeint(pchar.money) >= 1000 )
    			{
    				link.l2 = HeroStringReactionRepeat(RandPhraseSimple("You will get them if I get really valuable information.", "I will pay, but only on condition that you tell me something really important."),
                     "", "", "" , npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}
    			else
    			{
                    link.l2 =  HeroStringReactionRepeat("I don't have that amount.", "", "", "", npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}

		break;

		case "rumours_tavern_yes":

			//------------- квестовые слухи тавернщика --------->>>>>>>>
			//пиратка, квест №3
			if (pchar.questTemp.piratesLine == "KillLoy_toCumana")
			{
				Dialog.Text =  "Ships have been disappearing frequently lately, and, strangely, only courier luggers and sloops are disappearing. There is talk of the appearance of a brig in the waters of Cumana... So be careful!";
				link.l1 = "Courier luggers only, you say? Very interesting... Do you know anything else remarkable?";
				link.l1.go = "rumours_tavern";
				AddQuestRecord("Pir_Line_3_KillLoy", "14");
				AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("", "a"));
				pchar.questTemp.piratesLine = "KillLoy_toCumana_2";
				break;
			}
			//ОЗГ, Крыса на Тортуге
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if (pchar.questTemp.Headhunter == "Rat_tortuga" && npchar.location == "Tortuga_tavern")
	    		{
	    			Dialog.Text =  "They say captain and owner of the pinnace Adelaide has made some kind of deal with d'Ogeron and is sailing just the other day. His whole team has been messing around in the brothel and in my tavern for a week. Thank God, they will finally get out, it would be faster... And captain himself is resting at my place right now - you see, he's sitting over there, at a round table. A prominent sailor...";
	    			link.l1 = "Very interesting... Do you know anything else remarkable?";
	    			link.l1.go = "rumours_tavern";
	    			pchar.quest.Headhunter_PinasseTortugaOver.over = "yes";
	    			AddQuestRecord("Headhunt", "17");
	    			pchar.questTemp.Headhunter = "Rat_officer";
	    			FreeSitLocator("Tortuga_tavern", "sit1");
	    			SetFunctionTimerCondition("Headhunter_RatOfficerOver", 0, 0, 3, false);//таймер
	    			break;
	    		}
			}
			//ОЗГ, Крыса на Тортуге
			//<<<<<-------- квестовые слухи тавернщика -----------------

            string RumText = SelectRumourEx("tavern", NPChar); //fix
            //SelectRumour();

		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
                link.l1 = RandPhraseSimple("I won't pay for empty gossip, goodbye.", "Your information isn't worth a damn - you won't get anything.");

			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {

                AddMoneyToCharacter(pchar, -1000);

                Dialog.Text = RumText;

    			link.l1 = RandPhraseSimple("Thank you, here's your gold. Do you remember anything else?", "Well, you deserve your money - here you go. Is there anything else?");

    			link.l1.go = "rumours_tavern";
    			NextDiag.CurrentNode = NextDiag.TempNode;
            }

		break;

		case "rumours_tavern_no":
			Dialog.Text = "Don't get me wrong, I need to feed my family.";
            link.l1 = "Let's talk about something else.";
			link.l1.go = "first time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			link.l2 = LinkRandPhrase("Thanks, take my leave.",
                                     "Have a nice day", "Goodbye.");
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Yes, it's interesting. There is another question...",
										"I wanted to ask...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Well, goodbye, huckster.",
										"Have a nice day, buddy.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else
			{
				Dialog.Text = RandPhraseSimple("There's nothing to talk about, I've already blurted out everything I knew.",
					"I didn't hear anything else, I'm sorry...");
				Link.l1 = RandPhraseSimple("I see. Well, have a nice day.",
										"I see. Well, goodbye, buddy...");
				Link.l1.go = "exit";
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Yes, it's interesting. There is another question...",
										"I wanted to ask...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Well, goodbye, huckster.",
										"Have a nice day, buddy.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else
			{
				Dialog.Text = RandPhraseSimple("There's nothing to talk about, I've already blurted out everything I knew.",
					"I didn't hear anything else, I'm sorry...");
				Link.l1 = RandPhraseSimple("I see. Well, have a nice day.",
										"I see. Well, goodbye, buddy...");
				Link.l1.go = "exit";
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple("I see...",
										"I see...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple("There's nothing to talk about, I've already blurted out everything I knew.", "I haven't heard anything else, I'm sorry..."),
					RandPhraseSimple("I'm sorry, but I've already blurted it out to you.", "I haven't heard anything else, I'm sorry..."));
				Link.l1 = RandPhraseSimple("I got it.", "Well, have a nice day.");
				Link.l1.go = "exit";
			}
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanForAll": //пересылка в финансы для всех
			dialog.text = LinkRandPhrase("Finance? Hmm, speak up, I'm listening to you.", "Financial issues are always interesting. Speak up, I'm listening to you.", "Well, let's talk about finances.");
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
                    dialog.text = LinkRandPhrase("Are you sure you've come to the right place, " + GetAddress_Form(NPChar) + "? my name is " + GetFullName(npchar) + ". What can I do for you?",
                             "For finance to me, " + GetAddress_Form(NPChar) + "?! I am " + GetFullName(npchar) + ". What kind of business do you have?",
                             "I'm listening to you, " + GetAddress_Form(NPChar) + ". What did you want? By the way, my name is " + GetFullName(npchar) + ".");
                    link.l1 = NPCharRepPhrase(pchar, "I'm from a usurer, a debtor! Money on the barrel!", "I have a sensitive question for you about your debt, " + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "LoanFindCitizen_1";
				    NPChar.quest.LoanFindCitizenType = rand(2); // три типа
                    break;
                }
            }
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
            {
                link.l2 = "I brought your credit.";
                link.l2.go = "TakeChest_2";
            }
			link.l9 = RandPhraseSimple("Mmm, I must have made a mistake. I don't do any financial business with you.", "I'm sorry, I don't have any financial questions for you.");
			link.l9.go = "exit";
		break;
		// вернуть долг ростовщику
		case "LoanFindCitizen_1":
            switch (sti(pchar.GenQuest.Loan.FindCitizenChance1))
            {
                case 0 :
                    dialog.text = "Yes, exactly. I was just about to give it all to him.";
        			Link.l1 = "Well, very good! Total from you " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ".";
        			Link.l1.go = "LoanFindCitizenType_0";
        			Link.l2 = "Great, so take it all yourself!";
        			Link.l2.go = "exit";
                break;

                case 1 :
                    dialog.text = "No! I won't give anything away! If you bother, I'll call the guards.";
                    Link.l1 = "I don't know anything, I'm done with you " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". Otherwise, we can talk in another way.";
        			Link.l1.go = "LoanFindCitizenType_1";
        			Link.l2 = "Oh, you scoundrel! Well, never mind, the Earth is round, we'll see you again...";
        			Link.l2.go = "LoanFindCitizenType_1_1";
                break;

                case 2 :
                    dialog.text = "Unfortunately, I don't have the whole amount.";
                    Link.l1 = "I don't know anything, I'm done with you " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". Otherwise, we can talk in another way.";
        			Link.l1.go = "LoanFindCitizen_1_1";
        			Link.l2 = "How many are there?";
        			Link.l2.go = "LoanFindCitizenType_2";
        			//NPChar.quest.LoanFindCitizenType = rand(1);// первые 2 типа
                break;
			}
		break;

		case "LoanFindCitizen_1_1":
            switch (sti(pchar.GenQuest.Loan.FindCitizenChance2))
            {
                case 0 :
                    dialog.text = "Yes, exactly. I was just about to give it all to him.";
        			Link.l1 = "Well, very good! Total from you " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ".";
        			Link.l1.go = "LoanFindCitizenType_0";
        			Link.l2 = "Great, so take it all yourself!";
        			Link.l2.go = "exit";
                break;

                case 1 :
                    dialog.text = "No! I won't give anything away! If you bother, I'll call the guards.";
                    Link.l1 = "I don't know anything, I'm done with you " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". Otherwise, we can talk in another way.";
        			Link.l1.go = "LoanFindCitizenType_1";
        			Link.l2 = "Oh, you scoundrel! Well, never mind, the Earth is round, we'll see you again...";
        			Link.l2.go = "LoanFindCitizenType_1_1";
                break;
			}
		break;

			case "LoanFindCitizen_1_2":
            switch (sti(pchar.GenQuest.Loan.FindCitizenChance3))
            {
                case 0 :
                    dialog.text = "Yes, exactly. I was just about to give it all to him.";
        			Link.l1 = "Well, very good! Total from you " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ".";
        			Link.l1.go = "LoanFindCitizenType_0";
        			Link.l2 = "Great, so take it all yourself!";
        			Link.l2.go = "exit";
                break;

                case 1 :
                    dialog.text = "No! I won't give anything away! If you bother, I'll call the guards.";
                    Link.l1 = "I don't know anything, I'm done with you " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". Otherwise, we can talk in another way.";
        			Link.l1.go = "LoanFindCitizenType_1";
        			Link.l2 = "Oh, you scoundrel! Well, never mind, the Earth is round, we'll see you again...";
        			Link.l2.go = "LoanFindCitizenType_1_1";
                break;
			}
		break;

		case "LoanFindCitizenType_0":
            dialog.text = "Here's the whole amount.";
			Link.l1 = "Thank you for your cooperation!";
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenDone = true;
        	addMoneyToCharacter(Pchar, (sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent)));
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("You have 30 days to report to your employer and return the money.");
        	AddCharacterExpToSkill(pchar, "COMMERCE", 100);
		AddCharacterExpToSkill(pchar, "Fortune", 50);
        	AddQuestRecord("Gen_LoanFindCitizen", "3");
			npchar.LifeDay = 0;
		break;

		case "LoanFindCitizenType_1_1":
            dialog.text = "I am glad that we have reached an agreement.";
			Link.l1 = "You'll remember me later!";
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenFalied = true;
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("You have 30 days to report to your employer for mission failure.");
        	AddQuestRecord("Gen_LoanFindCitizen", "2");
			npchar.LifeDay = 0;
		break;

		case "LoanFindCitizenType_1":
            dialog.text = "Guards!!! Bully!";
			Link.l1 = "Shut up!";
			Link.l1.go = "fight";
			pchar.GenQuest.Loan.FindCitizenFalied = true;
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("You have 30 days to report to your employer for mission failure.");
        	AddQuestRecord("Gen_LoanFindCitizen", "2");
			npchar.LifeDay = 0;
			AddCharacterExpToSkill(pchar, "Sneak", 150);
		break;

		case "LoanFindCitizenType_2":
            pchar.GenQuest.Loan.FindCitizenTempMoney = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) - rand(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
            dialog.text = "Only " + pchar.GenQuest.Loan.FindCitizenTempMoney + " gold.";
			Link.l1 = "no. We need the whole amount!";
			Link.l1.go = "LoanFindCitizen_1_2";
			Link.l2 = "We have what we have. I'll pay extra. I am kind today.";
			Link.l2.go = "LoanFindCitizenType_2_1";
			//NPChar.quest.LoanFindCitizenType = rand(1);// первые 2 типа
		break;

		case "LoanFindCitizenType_2_1":
            dialog.text = "You are very kind! Thank you very much!";
			Link.l1 = "Eh! Everytime I'm getting into everything.";
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenDone = true;
        	addMoneyToCharacter(Pchar, sti(pchar.GenQuest.Loan.FindCitizenTempMoney));
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("You have 30 days to report to your employer and return the money.");
        	OfficersReaction("good");
        	ChangeCharacterReputation(pchar, 3);
        	AddCharacterExpToSkill(pchar, "Leadership", 30);
        	AddQuestRecord("Gen_LoanFindCitizen", "3");
			npchar.LifeDay = 0;
		break;
		//доставка сундуков
        case "TakeChest_2":
            if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
            {
                if (CheckAttribute(pchar, "GenQuest.LoanChest.Money.Discount"))
				{
					Dialog.Text = "It's all good, and I accept the gold from you. However, you did not meet the delivery time allotted to you. Therefore, I have to reduce the amount of your fee by " + pchar.GenQuest.LoanChest.Money.Discount + " percent. I'm sorry, but this is not up for discussion. Kindly receive...";
					link.l1 = "Thank you!";
    				link.l1.go = "exit";
					AddMoneyToCharacter(pchar, sti(pchar.GenQuest.LoanChest.Money)/100*sti(pchar.GenQuest.LoanChest.Money.Discount));
				}
				else
				{
					Dialog.Text = "Wonderful! I've been waiting for him for a long time. Here is your reward.";
					link.l1 = "Thank you!";
    				link.l1.go = "exit";
					AddMoneyToCharacter(pchar, sti(pchar.GenQuest.LoanChest.Money));
				}
				ChangeCharacterReputation(pchar, 1);
                AddCharacterExpToSkill(pchar, "Sailing", 50);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 5);
                OfficersReaction("good");
    			TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));
    			DeleteAttribute(pchar, "GenQuest.LoanChest");
    			DeleteAttribute(Pchar, "quest.LoanChestTimer");
    			AddQuestRecord("Gen_LoanTakeChest", "3");
                CloseQuestHeader("Gen_LoanTakeChest");

				AchievementsCounter_genquests(1);
			}
			else
			{
                Dialog.Text = "Wonderful! But where are all the chests of gold?";
                link.l1 = "Can you accept gold without chests?";
    			link.l1.go = "TakeChest_3";
                link.l2 = "I'll come back later.";
    			link.l2.go = "exit";
			}
		break;

		case "TakeChest_3":
            Dialog.Text = "No! Only in chests!";
            link.l1 = "Bad. The rats have ruined them.";
			link.l1.go = "exit";
			//link.l2 = "Well, let's say the amount in " + FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Chest)*30000) + "will it cover the cost of the chests?";
			//link.l2.go = "TakeChest_4";
		break;

		/*case "TakeChest_4":
            Dialog.Text = "Yes, it's acceptable.";
            if (sti(pchar.Money) >= (sti(pchar.GenQuest.LoanChest.Chest)*30000))
            {
                link.l1 = "That's settled!";
    			link.l1.go = "TakeChest_5";
			}
			link.l2 = "That's just a lot for me.";
			link.l2.go = "exit";
		break;

		case "TakeChest_5":
            ChangeCharacterReputation(pchar, 1);
            AddCharacterExpToSkill(pchar, "Sailing", 30);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "COMMERCE", 30);
            OfficersReaction("good");
            Dialog.Text = "You can be dealt with!";
            link.l1 = "Thank you!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1*(sti(pchar.GenQuest.LoanChest.Chest)*30000));
			DeleteAttribute(pchar, "GenQuest.LoanChest");
			DeleteAttribute(Pchar, "quest.LoanChestTimer");
			AddQuestRecord("Gen_LoanTakeChest", "4");
            CloseQuestHeader("Gen_LoanTakeChest");
		break;
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квесты мэра, проникновение во враждебный город
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple("Well, very good. I have a package ready for you, which you must deliver to a well-known man in hands. Please receive it. Don't come near me anymore and don't talk to me, it might be suspicious. Be careful...",
				"Hmm, fine. I am handing you a package, and remember that it must be delivered to the man you named in hands. Now goodbye and don't come near me anymore - it's dangerous.");
            link.l1 = RandPhraseSimple("I got it. Goodbye...", "Goodbye and good luck.");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId));
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квест Асокольда, рендомные базары
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "AscoldTrader": //рендомный хозяин магаза
            dialog.Text = "Listen, have you found mummy powder that I asked you to find?";
            if (GetQuestPastDayParam("questTemp.Ascold") > 3)
			{
				Link.l1 = "No, I haven't found yet... Listen, the merchants on the streets seem to have it, but they are obscuring something...";
            	Link.l1.go = "AscoldTrader_6";
			}
			else
			{
				Link.l1 = "No, I haven't found yet... But I'll keep looking.";
            	Link.l1.go = "quests";
			}
		break;
        case "AscoldTrader_WasSeek":
            dialog.Text = "Listen, have you found mummy powder that I asked you to find?";
            Link.l2 = "Yes, I found. And how much will you pay me for it?";
            Link.l2.go = "AscoldTrader_1";
        break;
		case "AscoldTrader_1":
        	dialog.text = "I - not at all. But I know who will buy it from you.";
    		link.l1 = "Hmm, I was counting to receive money right now.";
    		link.l1.go = "AscoldTrader_2";
		break;
 		case "AscoldTrader_2":
        	dialog.text = "I guess you won't be left out. Listen carefully\n"+
                          "There is a strange guy on Guadeloupe in the city of Basse-Terre - Askold.";
            if (Characters[GetCharacterIndex("Ascold")].quest.meeting == "0")
            {
                link.l1 = "Strange name...";
                link.l1.go = "AscoldTrader_4";
            }
            else
            {
                link.l1 = "I know him, I had a chance to talk. Impudent, what to look for ...";
                link.l1.go = "AscoldTrader_3";
            }
		break;
 		case "AscoldTrader_3":
        	dialog.text = "What happened? He tested his temper on you?";
    		link.l1 = "Yeah, he just threw me out the door like a toy!";
    		link.l1.go = "AscoldTrader_4";
		break;
 		case "AscoldTrader_4":
        	dialog.text = "Askold is a little harsh, but he is a good, honest man. According to rumors, a Muscovite, there are such people who live in the north of the Old World, where it snows all year round, and there are only forests and bears around. That's why the character is harsh, and the strength in his hands is enough for four hefty fellows\n"+
                          "How and when he got here, I don't know exactly how and I don't know what he does\n"+
                          "But he trusts me, because I have business dealings with him\n"+
                          "So go to him, introduce yourself, tell him that it's from me, and everything will be fine. He'll buy this stuff from you, since it's his order.";
    		link.l1 = "What's your income from this?";
    		link.l1.go = "AscoldTrader_5";
		break;
 		case "AscoldTrader_5":
        	dialog.text = "Don't worry about me, I'll deduct the required amount of commission from our current turnover.";
    		link.l1 = "Understood. Well, I'll probably look you upr Askold on occasion.";
    		link.l1.go = "exit";
    	    pchar.questTemp.Ascold = "GoToAscold";
    	    QuestSetCurrentNode("Ascold", "HaveRecomendation");
            AddQuestRecord("Ascold", "2");
		break;
 		case "AscoldTrader_6":
        	dialog.text = "Are they threatening the Inquisition too?";
    		link.l1 = "Exactly, they are threatening...";
    		link.l1.go = "AscoldTrader_7";
		break;
 		case "AscoldTrader_7":
        	dialog.text = "Well, how did you want? I'll tell you what, "+ GetSexPhrase("buddy", "girlfriend") +": they have the powder. Not everyone, of course, but someone definitely has it. Therefore, you must be more persistent with them - and in the end you will achieve your goal.";
    		link.l1 = "Heh, well, thanks for the help.";
    		link.l1.go = "quests";
			SaveCurrentQuestDateParam("questTemp.Ascold");
		break;
        //==> Общий диалог для хозяев верфи, квест Аззи.
		case "AzzyTryTalk":
			dialog.Text = NPCStringReactionRepeat("Let's take a look at your tin can. Uh, no. Look at her, she's covered in strange writing, it must be witchcraft. I advise you to take this thing to the church, they will figure out what to do with it.", "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
  			Link.l1 = HeroStringReactionRepeat("Thanks for the kind advice.", "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l1.go = "Exit";
		break;
		case "AggryHelp":
			dialog.Text = NPCStringReactionRepeat("There is a tool on the table: a blowtorch, a metal hacksaw, tin shears and so on. Take it and open it yourself, but I don't need money.", "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
			Link.l10 = HeroStringReactionRepeat("Thank you, " + npchar.name + ".", "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l10.go = "exit";
			items[GetItemIndex("Azzy_bottle")].shown = 0; //даём возможность вскрыть лампу
		break;
		//==> Общий диалог для церкви, квест Аззи.
        case "GiveLamp":
			dialog.text = "You did the right thing"+ GetSexPhrase("my son", "ah, my daughter") +". It is not known what is inside, but it is clear that tomorrow the church will need to be consecrated anew\n"+
                          "I don't want to ask where you got this. In the name of the Savior, I forgive you your sins! Go in peace.";
			link.l1 = "Thank you, Holy Father.";
			link.l1.go = "exit";
            ChangeCharacterReputation(pchar, 100);
            TakeItemFromCharacter(pchar, "Azzy_bottle");
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Грабёж среди бела дня, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery in broad daylight!!! What is going on?! Well, wait, "+ GetSexPhrase("buddy","girlfriend") +"...", "Hey, what are you doing there?! No way, you decided to rob me? Well, then you're finished...", "Wait, where are you going? You are a thief! Well, consider that you have sailed, bitch...");
			link.l1 = LinkRandPhrase("Devil!!", "Carramba!!", "Oh, damn!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квест получения Синей птицы
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "RBlueBird":
			dialog.text = "Eh, Captain, it didn't happen, but it has been happening for a long time. We Caribbean traders are on the verge of ruin. And the damn 'Blue Bird' is to blame for everything...";
			link.l1 = "'The Blue Bird'?";
			link.l1.go = "RBlueBird_1";
		break;
		case "RBlueBird_1":
			dialog.text = "Yes, it's a damn xebec, it's impossible to get away from it at sea. He only robs merchant ships. Large caravans reinforced by warships are not touched.";
			link.l1 = "Why did you say that merchants are going broke? After all, goods come here with these caravans anyway.";
			link.l1.go = "RBlueBird_2";
		break;
		case "RBlueBird_2":
			dialog.text = "Yes, that's right. But the thing is that turnover in this situation becomes unprofitable. It is best to have your own sloop or fluyt, buy goods yourself in the Old World and bring them here. This is a trade!When we buy goods from carriers, there is no longer any profit, we are talking about simple survival.";
			link.l1 = "Understood. And just as your ships are being boarded by xebec...";
			link.l1.go = "RBlueBird_3";
		break;
		case "RBlueBird_3":
			dialog.text = "That's right. Almost all the merchants have already lost their own ships, damn it, this 'Blue Bird'!";
			link.l1 = "Mmm, sad for you... Well, what do you want from me?";
			link.l1.go = "RBlueBird_4";
		break;
		case "RBlueBird_4":
			dialog.text = "We want you to destroy this blue-winged muskrat, fuck it!!!";
			link.l1 = "And what will I get out of it?";
			link.l1.go = "RBlueBird_5";
		break;
		case "RBlueBird_5":
			dialog.text = "I will collect from all colleagues a decent payment for you for this work. I can promise you fifty thousand piastres. The damn xebec has to go to the bottom!";
			link.l1 = "For such money, buddy, I won't lift a finger. Look for a fool!";
			link.l1.go = "RBlueBird_close";
			link.l2 = "Hmm, this money interests me. I'm ready to take up this case. What are the deadlines?";
			link.l2.go = "RBlueBird_6";
		break;
		case "RBlueBird_6":
			dialog.text = "You are not limited in time. I perfectly understand that it will not be easy to do this, damn it! To tell the truth, we have already involved hired assassins in this case, we wanted to remove captain. To no avail...";
			link.l1 = "Is that so? Can you tell us more about this?";
			link.l1.go = "RBlueBird_7";
		break;
		case "RBlueBird_7":
			dialog.text = "Well, we chipped in and hired someone to find the cap of this xebec among the pirates. It didn't work out, our hireling scoured the Caribbean for six months, but found nothing. The devil knows where they are based and where they sell their loot...";
			link.l1 = "So, buddy, that's something. Now listen to my terms of the deal.";
			link.l1.go = "RBlueBird_8";
		break;
		case "RBlueBird_8":
			dialog.text = "Listening carefully, " + GetAddress_Form(NPChar) + "." ;
			link.l1 = "This deal is between you and me, collect the money as you want, but don't tell anyone that I took for this case. And the second thing. You said that ALMOST all the merchants lost their ships. What does 'almost' mean?";
			link.l1.go = "RBlueBird_9";
		break;
		case "RBlueBird_9":
			dialog.text = "One merchant has a fluyt left. But he's a lucky guy, he's never been to this xebec. He is our only hope to gain a foothold here, already all of us owe him. If he hadn't supported us in a difficult moment, everyone would have come to an end long ago. He has never refused anyone's requests to lend money!";
			link.l1 = "Understood. Almost a saint! And what is his name?";
			link.l1.go = "RBlueBird_10";
		break;
		case "RBlueBird_10":
			dialog.text = "Pascal Voisier. He runs a shop in Bermudes in a pirate settlement. So are you taking the case?";
			link.l1 = "Do you accept my condition of silence?";
			link.l1.go = "RBlueBird_11";
		break;
		case "RBlueBird_11":
			dialog.text = "Absolutely!";
			link.l1 = "Then I'll take it. I'm starting the search from this day, I hope to finish soon.";
			link.l1.go = "RBlueBird_12";
		break;
		case "RBlueBird_12":
			dialog.text = "Oh, with your mouth, yes, to drink honey! Well, get started. I really hope that everything will go as you said.";
			link.l1 = "There will be, you can be sure!";
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "toBermudes";
			pchar.questTemp.BlueBird.traiderId = npchar.id; //запомним Id торговца
			SetQuestHeader("Xebeca_BlueBird");
			AddQuestRecord("Xebeca_BlueBird", "1");
			AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Xebeca_BlueBird", "sName", GetFullName(npchar));
		break;


		case "RBlueBird_close":
			dialog.text = "Well, it's a pity. Perhaps we'll look for the 'fool' somewhere else...";
			link.l1 = "Um...";
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "declined";//Блокировка ЧП
		break;
		case "RBlueBirdWon":
			dialog.text = "Great news, I'll tell you! Finally, we will be able to engage in real trading... Do you want to get the money right now?";
			link.l1 = "Yes, preferably...";
			link.l1.go = "RBlueBirdWon_1";
			int chComp;
			for (int i=0; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar, i);
                if(chComp != -1 && RealShips[sti(characters[chComp].ship.type)].Name == "XebekVML1")
        		{
					dialog.text = "Hmm, wait... As far as I know, you managed to overtake the xebec, but did not sink it! It is now in your possession.";
					link.l1 = "Yes, it is. So what's the problem?";
					link.l1.go = "RBlueBirdWon_10";
					break;
                }
            }
		break;

		case "RBlueBirdWon_1":
			dialog.text = "No problem, please get it. The money is in the chests. There's even a little over fifty thousand here.";
			link.l1 = "Thanks, we're even. I wish you all the best... By the way, don't you want to know who was behind all this?";
			link.l1.go = "RBlueBirdWon_2";
			TakeNItems(pchar, "chest", 4);
			Log_Info("You got the credit chests");
			PlaySound("interface\important_item.wav");
		break;
		case "RBlueBirdWon_2":
			dialog.text = "Hmm, it will be very interesting to find out...";
			link.l1 = "This is the most 'holy' trader in the Caribbean - Pascal Voisier.";
			link.l1.go = "RBlueBirdWon_3";
		break;
		case "RBlueBirdWon_3":
			dialog.text = "It can't be!..";
			link.l1 = "Maybe. Unfortunately, I don't have any proof, but keep in mind who lends you your own money.";
			link.l1.go = "RBlueBirdWon_4";
		break;
		case "RBlueBirdWon_4":
			dialog.text = "Hmm, all this needs to be checked... Well, thank you for your work and for the information.";
			link.l1 = "You're welcome, it's paid for by you. Goodbye.";
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questdata.SinyaPtitsa = 1;
			pchar.questTemp.BlueBird = "over";
		break;

		case "RBlueBirdWon_10":
			dialog.text = "The problem is that this damn ship is now in your hands. And you, by the way, are also a pirate! And who's going to stop you from robbing merchants just like the previous owner did?";
			link.l1 = "Hmm, the question is certainly interesting... However, I've done this work!";
			link.l1.go = "RBlueBirdWon_11";
		break;
		case "RBlueBirdWon_11":
			dialog.text = "No, you didn't do it. We negotiated the sinking of the Bluebird, not the boarding.";
			link.l1 = "Hmm, that's how it is! Well, I understand you... All the best, give my fervent greetings to your colleagues.";
			link.l1.go = "RBlueBirdWon_12";
		break;
		case "RBlueBirdWon_12":
			dialog.text = "I will definitely send it! Goodbye, liar.";
			link.l1 = "Okay... But I'm not saying goodbye...";
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "9");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("Xebeca_BlueBird", "sSex1", GetSexPhrase("a complete idiot", "a complete fool"));
			pchar.questTemp.BlueBird = "returnMoney";
			pchar.questTemp.BlueBird.City = GetSharpCity();
		break;

		case "RBlueBirdDieHard":
			dialog.text = "Very, very sorry. Well, you are not the first who takes on this case, and who does not succeed. It's bad, we'll have to continue to vegetate...";
			link.l1 = "I hope everything will come back to normal with time...";
			link.l1.go = "RBlueBirdDieHard_1";
		break;
		case "RBlueBirdDieHard_1":
			dialog.text = "That's for sure. Here we live in a fuss, and naively believe that the earth revolves around us. But no, it's taken from the ground, let's go to the ground, something pulled me to the lyrics.";
			link.l1 = "It happens... Well, goodbye.";
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questdata.SinyaPtitsa = 1;
			pchar.questTemp.BlueBird = "over";
		break;

		case "RBlueBird_retMoney_1":
			dialog.text = "Oh, you're bastard! So our fears turned out to be true!!";
			link.l1 = "I wouldn't touch you if you hadn't started cheating!";
			link.l1.go = "RBlueBird_retMoney_2";
		break;
		case "RBlueBird_retMoney_2":
			dialog.text = "Oh, shit! Guards, grab "+ GetSexPhrase("him", "her") +"!!! You can't get far, bastard...";
			link.l1 = "It would be better to get my money back, weasels. We will continue to treat you...";
			link.l1.go = "fight";
		break;

		case "RBlueBird_retMoney_3":
			dialog.text = "Damn you, bastard! How I regret contacting you!! Before you, the Blue Bird had never caused us SO MUCH trouble!..";
			link.l1 = "My friends, it's your own fault, you should have stuck to the contract.";
			link.l1.go = "RBlueBird_retMoney_4";
		break;
		case "RBlueBird_retMoney_4":
			dialog.text = "What kind of agreement is ours with you? We strictly adhered to it! It was you who violated it by not sinking the xebec!";
			link.l1 = "Mon cher, don't shout like that, it has a detrimental effect on the vocal cords. What if you can't talk later? In general, I'm ready to speak to you only in moderate tones...";
			link.l1.go = "RBlueBird_retMoney_5";
		break;
		case "RBlueBird_retMoney_5":
			dialog.text = "Well, okay, although the tone has nothing to do with it. It was you who violated the terms of the deal, not us-that's the crux of the matter!";
			link.l1 = "Heh! You merchants are great masters of such quirks in contracts. I know your tricks. I didn't put a comma somewhere, and the meaning of the text immediately changes.";
			link.l1.go = "RBlueBird_retMoney_6";
		break;
		case "RBlueBird_retMoney_6":
			dialog.text = "What does commas have to do with it? We had an oral agreement with you.";
			link.l1 = "Well, I'm figuratively speaking. The point is that you jumped at the opportunity to throw me for money, and you did it. And I'm a pirate, I don't have time to figure out the double meanings of your terms.";
			link.l1.go = "RBlueBird_retMoney_7";
		break;
		case "RBlueBird_retMoney_7":
			dialog.text = "What conditions?";
			link.l1 = "The terms of our agreements. The 'Blue Bird' was bothering you - I solved this problem. If you had given me my money, I wouldn't have touched you. So all your problems are from your wisdom, so to speak...";
			link.l1.go = "RBlueBird_retMoney_8";
		break;
		case "RBlueBird_retMoney_8":
			dialog.text = "All right, take your 50 thousand and get out of here!";
			link.l1 = "Not so fast, mon cher. The thing is, I suffered additional financial costs of trying to reason with you. Not to mention the moral damage. Therefore, the amount has increased.";
			link.l1.go = "RBlueBird_retMoney_9";
		break;
		case "RBlueBird_retMoney_9":
			dialog.text = "And what is this new amount? Name her.";
			link.l1 = "Quadruple it. 200,000, and I'll leave you alone. Otherwise, I'll ruin you. And then I'll kill you. First your family, and then you...";
			link.l1.go = "RBlueBird_retMoney_10";
		break;
		case "RBlueBird_retMoney_10":
			dialog.text = "You are the devil!!";
			link.l1 = "And very, very angry devil...";
			link.l1.go = "RBlueBird_retMoney_11";
		break;
		case "RBlueBird_retMoney_11":
			dialog.text = "Okay. Here's your money-fourteen chests. There are even more than two hundred thousand here. Now get out! And leave us alone!";
			link.l1 = "Absolutely. Now that you have settled with me, the Blue Bird is no longer threatening you. Goodbye, good luck in business...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.BlueBird");
			pchar.questTemp.BlueBird = "over"; //закрываем квест
			TakeNItems(pchar, "chest", 14);
			Log_Info("You got the credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Xebeca_BlueBird", "14");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("Xebeca_BlueBird", "sSex1", GetSexPhrase("en", "bna"));
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questdata.SinyaPtitsa = 1;
		break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Линейка острова погибших кораблей ISS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "ISS_deposit":
			dialog.text = NPCStringReactionRepeat("That's right. You can receive one million piastres in a minute after I receive the confirmation.",
				"I already told you, " + GetAddress_Form(NPChar) + " that I have a deposit. I am waiting for confirmation of its issuance.",
				"You don't have to worry. The deposit is with me, I am only waiting for confirmation of its issuance.",
				"Hmm, it seems to me that you are overly concerned about this deposit. My reputation is impeccable, so I can only repeat what I said earlier. The deposit in your name is with me, you will be able to receive it after confirmation for issuance.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Understood. Well, that's fine. I found out what I wanted.",
				"Yeah, I see...",
				"I'm not really worried.",
				"I see... Thank you, " + GetAddress_Form(NPChar) + ".", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "ISS_takeDeposit":
			dialog.text = "Yes, yes, I have received permission to conduct this financial transaction. Kindly get, " + GetAddress_Form(NPChar) + ".";
			link.l1 = "Hehe, very good...";
			link.l1.go = "ISS_takeDeposit_1";
			AddMoneyToCharacter(pchar, 1000000);
			CloseQuestHeader("ISS_PoorsMurder");
			pchar.questdata.UbitVsehNishih = 1;
		break;
		case "ISS_takeDeposit_1":
			dialog.text = "Maybe you decide to use this money for growth? I am always at your service, my reputation...";
			link.l1 = "I understand. Thank you a lot. I'll think about it.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "over"; //конец линейки ГПК
			CloseQuestHeader("ISS_PoorsMurder");
			pchar.questdata.UbitVsehNishih = 1;
		break;
		//механика арестовали, диалоги мужика
		case "MechanicIsPrison_man":
			dialog.text = "Ah, well, here you are at last...";
			link.l1 = "What's the matter? Why aren't you on the clipper yet? Where's the Mechanic?";
			link.l1.go = "MechanicIsPrison_man_1";
		break;
		case "MechanicIsPrison_man_1":
			dialog.text = "I do not know where he is now. When I was on the San Gabriel, he was just being taken out by the police. Apparently, he was arrested, and only the admiral could have done it.";
			link.l1 = "Carramba!!! What should I do now?";
			link.l1.go = "MechanicIsPrison_man_2";
		break;
		case "MechanicIsPrison_man_2":
			dialog.text = "Can't we do without a Mechanic?";
			link.l1 = "We need a Vedeker. We can get on the clipper, but we won't be able to free it without Henrik.";
			link.l1.go = "MechanicIsPrison_man_3";
		break;
		case "MechanicIsPrison_man_3":
			dialog.text = "Then you need to go to the Capper's residence, help out the Mechanic. Unfortunately, I pass in this case - the admiral terrifies me with his very appearance...";
			link.l1 = "Heh, that's understandable... Go to the ship, I will arrive soon with Vedeker. The rest of the team is already there, apparently.";
			link.l1.go = "MechanicIsPrison_man_4";
		break;
		case "MechanicIsPrison_man_4":
			dialog.text = "Whatever you say, Captain.";
			link.l1 = "Don't panic there without me. Everything will be fine.";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "MechanicIsArrest_toResidence";
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
			bDisableFastReload = true;
			AddQuestRecord("ISS_MainLine", "64");
			pchar.quest.LSC_fightEnterResidence.win_condition.l1 = "location";
			pchar.quest.LSC_fightEnterResidence.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_fightEnterResidence.function = "LSC_fightEnterResidence";
		break;
		//механика арестовали, диалоги бабы
		case "MechanicIsPrison_woman":
			dialog.text = "Ah, well, here you are at last...";
			link.l1 = "What's the matter? Why aren't you on the clipper yet? Where's the Mechanic?";
			link.l1.go = "MechanicIsPrison_man_1";
		break;
		case "MechanicIsPrison_woman_1":
			dialog.text = "I do not know where he is now. When I came to the San Gabriel, he was just being taken out by the police. Apparently, he was arrested, and only the admiral could have done it.";
			link.l1 = "Carramba!!! What should I do now?";
			link.l1.go = "MechanicIsPrison_woman_2";
		break;
		case "MechanicIsPrison_woman_2":
			dialog.text = "Can't we do without a Mechanic?";
			link.l1 = "We need a Vedeker. We can get on the ship, but we won't be able to free it without Henrik.";
			link.l1.go = "MechanicIsPrison_man_3";
		break;
		case "MMechanicIsPrison_woman_3":
			dialog.text = "Then you need to go to the Capper's residence, help out the Mechanic. Unfortunately, as a woman, I cannot help you in this matter.";
			link.l1 = "That's right... Go to the ship, I will arrive soon with Vedeker. The rest of the team is already there, apparently.";
			link.l1.go = "MechanicIsPrison_man_4";
		break;
		case "MechanicIsPrison_woman_4":
			dialog.text = "Whatever you say, Captain.";
			link.l1 = "Don't panic there without me. Everything will be fine.";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "MechanicIsArrest_toResidence";
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
			bDisableFastReload = true;
			AddQuestRecord("ISS_MainLine", "64");
			pchar.quest.LSC_fightEnterResidence.win_condition.l1 = "location";
			pchar.quest.LSC_fightEnterResidence.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_fightEnterResidence.function = "LSC_fightEnterResidence";
		break;
		case "SeekCrew_all":
			pchar.questTemp.LSC.crew = sti(pchar.questTemp.LSC.crew) + 1;
			chrDisableReloadToLocation = true;
			float   locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			if (sti(pchar.questTemp.LSC.crew) >= 15)
			{
				DeleteAttribute(pchar, "questTemp.LSC.crew");
				pchar.questTemp.LSC = "MechanicIsArrest";
				pchar.questTemp.LSC.lastManId = npchar.index; //сюда запишем индекс
				NextDiag.TempNode = "MechanicIsPrison_" + npchar.sex;
				AddQuestRecord("ISS_MainLine", "63");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("en", "on"));
				if (npchar.location.group == "sit")
				{
					ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
				}
				npchar.cityTape = "quest";  //чтобы не передвигался
				DeleteAttribute(npchar, "location.going"); //снять метку на перемещёние
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 10.0);
				pchar.quest.LSC_afterArestMachanic.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LSC_afterArestMachanic.win_condition.l1.location = pchar.location;
				pchar.quest.LSC_afterArestMachanic.function = "LSC_afterArestMachanic";
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "62");
				AddQuestUserData("ISS_MainLine", "sName", GetFullName(npchar));
				AddQuestUserData("ISS_MainLine", "Sex", NPCharSexPhrase(npchar, "agreed", "agreed"));
				AddQuestUserData("ISS_MainLine", "iCrew", FindRussianPeoplesString(15-sti(pchar.questTemp.LSC.crew), "Acc"));
				npchar.lifeDay = 0;
				if (npchar.location.group == "sit")
				{
					ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
				}
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 10.0);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идёт распределение по городам
{
	string sRetRumour = "Явный баг. Сообщите о нем АТ, для Warship'а.";
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;

		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;

		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;

		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;

		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;

		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;

		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;

		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;

		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;

		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;

		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;

		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;

		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;

		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;

		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;

		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;

		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;

		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;

		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;

		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;

		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;

		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;

		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
		
		case "Nassau":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 23;
		break;
		
		case "DesMoines":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3, sCity);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 24;
		break;
	}

	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum, string sTown) // База слухов жителей. Можно менять без новой игры
{

	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = "Oh, Mr. Governor is a wonderful man. He skillfully manages our colony - since its foundation, we have not had a single major conflict, his only drawback is... mmm... very frugal. Although, perhaps, this is the opposite of dignity.";
	STR_MAYOR[1] = "Oh, Mr. Governor is a wonderful man. He skillfully manages our colony - since its foundation, we have not had a single major conflict, his only drawback is... mmm... very frugal. Although, perhaps, this is the opposite of dignity.";
	STR_MAYOR[2] = "Alas, Mr. Governor, we have a good one... But weak of character. If he had a little bit of firmness in his soul, our merchants would have small tax benefits... And subsidies for the repair of the fort should have been allocated long ago.";
	STR_MAYOR[3] = "Hmm... He recently became our governor. He is quite young and therefore very proactive - our colony is thriving under him.";
	STR_MAYOR[4] = "Our governor is still relatively young. They say he is the wayward younger son of a Spanish count, sent far away from the court to stop shaming his family. He was appointed here quite recently, and did not manage to create anything memorable.";
	STR_MAYOR[5] = "Hmm... He recently became our governor. He is quite young and therefore very proactive - our colony is thriving under him.";
	STR_MAYOR[6] = "Uh... Nothing... I can't say anything bad about him.";

	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Hmm, I wouldn't entrust my property to this rascal. Don't get me wrong, but it seems to me that this is the most unreliable person in our town, they say that he gets mixed up with smugglers and pirates - and all the rabble hangs out in his tavern all the time!";
	STR_TAVERNKEEPER[1] = "What can you say about him! He's a little cowardly, and he's not very smart. Besides, he is greedy for money, which is why he constantly gets into various troubles! But, however, he is always up to date with all the news.";
	STR_TAVERNKEEPER[2] = "Quite a nice guy. It's always nice to sit in his tavern, and the owner's sense of humor is fine. And most importantly, he keeps order in the tavern and does not allow any drunken trash to bully respectable citizens.";
	STR_TAVERNKEEPER[3] = "An amazing man. He does not need to keep a tavern, but to be an informant at the secret chancellery. Sometimes it seems that he knows literally everything that happens in our city. It's even creepy.";
	STR_TAVERNKEEPER[4] = "I don't know what to tell you about him. A man is like a man. He keeps the tavern, accordingly, up to date with all the news of our island.";
	STR_TAVERNKEEPER[5] = "They say you can rely on him. On the other hand, I have heard that he does not like unnecessary risks and always conducts his business prudently. And he doesn't seem to be involved in shady business either.";
	STR_TAVERNKEEPER[6] = "He inherited the tavern from his father. His father ran a tavern not far from here, on the small island of Hyrok in another archipelago. Then my father moved here, built a new tavern here, and now his son runs it.";

	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "He builds good ships... And as a person, it is difficult to say anything about him - he lives quietly and peacefully. Probably not a bad person.";
	STR_SHIPYARDER[1] = "He builds good ships... And as a person, it's hard to say anything about him - he lives quietly and peacefully. Probably not a bad person.";
	STR_SHIPYARDER[2] = "He's not a bad person, but they say he's too harsh. Constantly chastises all employees. Therefore, they often change with him. However, despite this, he is an excellent shipbuilder.";
	STR_SHIPYARDER[3] = "He is a very educated man. It is said that he studied shipbuilding in England, then in Holland. And in the end he ended up here - far from the metropolis, in a backwater archipelago, they say that he did not get along with the Holy Inquisition at the time, and he had to flee to the colonies.";
	STR_SHIPYARDER[4] = "Yes, this old man is no good anymore. He constantly dreams about the past times, and grumbles when he is ordered anything other than a caravel or galleon.";
	STR_SHIPYARDER[5] = "Great guy. I am always ready to help, to help out of trouble. I must say that he builds very good ships for such a backwater.";
	STR_SHIPYARDER[6] = "He was an exile in our colony until it turned out that he had a talent for shipbuilding. After two magnificent brig ships were built at the shipyards of our colony under his leadership, he was forgiven for his sins, and now he is a full member of our society.";

	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "I can't say anything particularly bad about him. A decent resident, a diligent parishioner of our church. I've never heard of anyone blaspheming him or being offended by him.";
	STR_TRADER[1] = "He is the main supplier of our governor, and this gives him a good income. But he does his business honestly. Well, or so far he has not been seen in anything disgraceful.";
	STR_TRADER[2] = "This fat man enjoys well-deserved respect in our city. His goods are always excellent, and I do not recall a case when he cheated anyone.";
	STR_TRADER[3] = "He's a bad guy. He trades, he trades, but there is no sense. Some goods are missing, then others. And he won't get out of debt himself.";
	STR_TRADER[4] = "He's not a good man, monsieur. They say he was Baldwin Coffier's assistant, but he ruined him and then outbid the store. I don't know about the quality of the goods he sells, but as a person he is very unpleasant to me.";
	STR_TRADER[5] = "Oh! This is a vile man, I would not advise you to have anything to do with him, he keeps half of the inhabitants of our city in debt! And the goods that are sold in his store are always of poor quality.";
	STR_TRADER[6] = "No one really knows anything about him. He recently moved here, and immediately opened his own business. He seems to trade honestly, he does not carry contraband.";

	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];

	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") //если правильно понял, идёт прямая связь, конкретному городу один вариант прописывается, чтобы все жители одинаково говорили?
	{
		if (rand(4) == 4) sTempShipyarder = GetInfoShipYarder(sTown);//20%, что нам расскажут насколько хорош навык корабела, а не типовую фразу. 
		return sTempShipyarder;
	}
	if(sOwnerType == "Trader") return sTempTrader;
}

string GetInfoShipYarder(string _sTown)
{
	ref refNPCShipyard = CharacterFromID(_sTown+"_shipyarder");
	ref rChar;
	int iYardersSum = 0; 		//всего верфистов на архипелаге
	int iBetterYarders = 0; 	//верфистов с более высоким навыком
	int iBetterNationYarders = 0; 	//верфистов той же нации с более высоким навыком
	string sTemp = "They say that he is the worst shipbuilder in these waters. It's strange that his ships stay afloat at all."; 
	string sBestInNation;
	int iBestInNation = sti(refNPCShipyard.reputation);

	if (sti(refNPCShipyard.reputation) > 19) sTemp = "He is not praised for his skill. He does not build outstanding ships.";
	if (sti(refNPCShipyard.reputation) > 39) sTemp = "He is quite a normal master. He does not build outstanding ships, but he does not launch very bad ones either.";
	if (sti(refNPCShipyard.reputation) > 59) sTemp = "He is praised for his skill. His shipyard produces good ships.";
	if (sti(refNPCShipyard.reputation) > 79) sTemp = "He is highly praised for his skill. If you need an outstanding ship, then feel free to contact it.";
	if (sti(refNPCShipyard.reputation) > 99) sTemp = "He has mastered shipbuilding perfectly. Feel free to contact him if you want the best ship.";

	string sTemp2 = "They say that he has the lowest prices for ships and repairs.";
	if (stf(refNPCShipyard.shipCostRate) > 0.9) sTemp2 = "They say that he has low prices for ships and repairs."; 
	if (stf(refNPCShipyard.shipCostRate) > 1.0) sTemp2 = "They say that he has high prices for ships and repairs."; 
	if (stf(refNPCShipyard.shipCostRate) > 1.1) sTemp2 = "They say that he has insanely high prices for ships and repairs."; 
	sTemp += sTemp2;

	for (int j=0; j< MAX_CHARACTERS; j++)
	{
        rChar = GetCharacter(j);
		if (hassubstr(rChar.id, "_shipyarder")) iYardersSum++; else continue;
		if (rChar.id != refNPCShipyard.id && sti(rChar.reputation)>sti(refNPCShipyard.reputation)) //TO DO добавить сюда инфу о том, насколько высокие у него цены
		{
			if (rChar.nation == refNPCShipyard.nation) 
			{
				iBetterNationYarders++; 
				if (sti(rChar.reputation)>iBestInNation) 
				{
					iBestInNation = sti(rChar.reputation);
					sBestInNation = XI_ConvertString("Colony" + rChar.city + "Voc");
				}
			}
			iBetterYarders++; 
		}
	}
	if (iBetterNationYarders == 0) sTemp += "And there are rumors that he is the best shipbuilder in " + GetNationNameX(refNPCShipyard.nation) + "colonies";
		else sTemp += "There are still rumors that in " + sBestInNation + "The shipbuilder is more skilled, so our military orders ships there.";
	//if (iBetterYarders <= 1) sTemp += "There are also rumors that he is the best shipbuilder in the entire archipelago.";

	return sTemp;
}

string GetNationNameX(string snation)
{
	string sTemp;
	switch (snation)
	{
		case "0": sTemp = "English"; break;
		case "1": sTemp = "French"; break;// в французских...
		case "2": sTemp = "Spanish"; break;
		case "3": sTemp = "Dutch"; break;
		case "4": sTemp = "Pirate"; break;
	}
	return sTemp;
}
