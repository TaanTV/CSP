#include "DIALOGS\english\Rumours\Common_rumours.c"  //homo 25/06/06
string sProf;

void ProcessDialogEvent()
{
	int license_price = sti(PChar.rank) * (2500) * (0.01 * (120 - GetSummonSkillFromName(PChar, SKILL_COMMERCE)));;
	int license_expires = rand(2);

	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	int i, cn;
	ref chref, compref;
	ref rRealShip;
	string attrL, sTitle, sCapitainId, s1;
	string sColony;

	String sLastSpeakDate = LastSpeakDate();

	// Warship 25.07.09 Генер "The burnt-out ship.". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
	bool ok, ok2;
	int iTest = FindColony(NPChar.City); // город магазина
	ref rColony;
	string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}

	attrL = Dialog.CurrentNode;

	if(HasSubStr(attrL, "ShipStockManBack11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack2_"))
	{
		i = findsubstr(attrL, "_" , 0);
		AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));

		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));//сторож

		DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));

        int iChar = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); //выбранный пассажир
		compref = GetCharacter(iChar);

		DeleteAttribute(compref, "ship");//зачем-то стираем корабль офицера, хотя его там и не должно быть
		compref.ship = "";

		aref    arTo, arFrom;

		makearef(arTo, compref.ship);
		makearef(arFrom, chref.Ship);
		CopyAttributes(arTo, arFrom);

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);//увольнение офицера с должностей, если он не просто пассажир
		RemovePassenger(pchar, compref);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);
		DelBakSkill(compref);
		DeleteAttribute(chref, "ShipInStockMan");
		chref.id = "ShipInStockMan";//сбрасываем индекс к стандартному, чтобы этот номер массива в следующий раз можно было занять
		DeleteAttribute(chref, "ship");//затираем данные корабля у сторожа
		chref.ship = "";
		LAi_SetCurHP(chref, 0.0);//ещё и убивать непися, чтоб точно очистился из массива?

		NPChar.Portman	= sti(NPChar.Portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		Dialog.CurrentNode = "exit";//закрываем диалог, ещё одно подтверждение уже не справшиваем
	}

	if(HasSubStr(attrL, "ShipStockMan11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_Choose";
	}

	if(HasSubStr(attrL, "ShipStockMan22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_Choose";
	}

	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
		Dialog.CurrentNode = "BurntShip19";
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
	  			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("The alarm has been raised in the city, they are looking for you everywhere! If I were you, I wouldn't stay here too long.", "The entire city guard is scouring the city in search of you. I'm not an idiot and I won't talk to you!", "Run, "+ GetSexPhrase("buddy", "girlfriend") +"before the soldiers make a sieve out of you..."),
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel", "scoundrel") +"?! The city guards have already are on your trail, you can't get far"+ GetSexPhrase(", dirty pirate", "") +"!", " Dirty murderer, get out of my house! Guards!!", "I'm not afraid of you, bastard! You'll be hanged in our fort soon, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, anxiety is not a problem for me...", "They will never catch me."),
					RandPhraseSimple("Shut your mouth, " + GetWorkTypeOfMan(npchar, "") + ", or I'll rip out your filthy tongue!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", and still there - catch pirates! I'll tell you what, buddy: stay quiet and you'll live..."));
				link.l1.go = "fight";
				break;
			}
			//homo
			//homo Линейка Блада
			if (CheckAttribute(Pchar, "questTemp.CapBloodLine") && Pchar.questTemp.CapBloodLine == true)
			{
				dialog.Text = LinkRandPhrase("Hey, Dr. Blood! " + TimeGreeting() + ".",
									"Glad to see you, Peter Blood.",
									"It's good that you looked at me, " + GetFullName(pchar) + ". How is Colonel Bishop?");
				Link.l1 = "Alas, I'm already leaving, " + npchar.name + ". See you later.";
				Link.l1.go = "exit";
				break;
			}
			//homo
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Greetings, " + GetAddress_Form(NPChar) + ". We don't seem to know each other. I am "  + GetFullName(npchar)+ " - the head of the port.";
				Link.l1 = "Hello, " + GetFullName(NPChar) + ". I am " + GetFullName(PChar) + ", captain of the ship '" + PChar.ship.name + "'.";
			}
			else
			{
				dialog.text = LinkRandPhrase("Greetings, " + GetAddress_Form(NPChar) + ". Are you here on business?",
									"Hello, " + GetFullName(Pchar) + ". I saw your ship enter the port, and I was sure that you would come to me.",
									"Ah, Captain " + GetFullName(Pchar) + ". What brings you to me?");
				Link.l1 = "Hello, " + GetFullName(NPChar) + ". I want to talk to you.";
			}
			Link.l1.go = "node_2";
		break;
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "That's fine. I am at your service, " + GetFullName(PChar) + ".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "So, what's with the money? Have you brought me at least 1000 piastres?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "Yes, prin"+ GetSexPhrase("eu", "esla") +". Here is exactly one thousand gold. Now the information!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("No, not yet"+ GetSexPhrase("eu", "if") +"...", "Not yet...", "Not yet"+ GetSexPhrase("eu", "if") +", but I'll bring it soon...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "Let me tell you the essence of the question. I missed with my old friend for just a few hours, and I have an urgent matter with him. Now I have to catch up with him, but unfortunately I am not aware in which direction he left.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "Mr. Portmaster, I need information about the ship '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "', captain by name " + PChar.GenQuest.ChurchQuest_1.CapFullName + ".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}
				break;
			}
			//========================  Квест "Strange things are happening in the archipelago" ==>
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_NevisPortMan_1"))
			{
				link.l1 = "I am interested in whether a black frigate vessel has entered the port.";
				link.l1.go = "PKM_BlackFregat";
			}
			//========================  Квест "Strange things are happening in the archipelago" <==

			dialog.text = "That's fine. I am at your service, " + GetFullName(PChar) + ".";
			if(NPChar.city != "Pirates")
			{
				Link.l2 = "Is it possible to find a job here? Or a contract?";
				Link.l2.go = "node_4";
				Link.l13 = LinkRandPhrase("Merchants who are looking for escorts for their ships are probably contacting you. Are there any such people today?", "Do you have any passengers in mind who want to get to another colony?", "I have a great ship, and I want to earn extra money by escorting merchants or delivering passengers. Do you have any of these?"));
				Link.l13.go = "work_PU";
			}
				Link.l3 = "Can I leave one of my ships for a while?";
				Link.l3.go = "ShipStock_1";

			if (sti(NPChar.Portman) > 0)
			{
				Link.l4 = "I want to take my ship back.";
				Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "I'm here for financial matters.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
 			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("I'm here on behalf of a man. His name is the governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".",
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " sent me to pick up something...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "I am interested in captains who have registered with your port authority.";
			link.l6.go = "CapitainList";
			if (bBribeSoldiers ==true && GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
				if (!CheckNationLicence(sti(npchar.nation)))
				{
					link.l77 = "Do you happen to have a short-term trading license? Maybe it was left over from some captain?";
					link.l77.go = "BuyLicense";
				}
				}
			//ОЗГ
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				if (pchar.questTemp.Headhunter == "Houm" && npchar.nation == ENGLAND)
				{
					link.l12 = "Can you tell me if the ship Deadhead with Captain Hannibal Holm stopped at your place?";
					link.l12.go = "Houm_portman_1";
				}
			}

			link.l8 = "I'm on another matter.";
			// Warship 26.07.09 Генер "The burnt-out ship"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar, "GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Hello, I'm here at your son's invitation.";
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "I'm talking about your daughter...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "I happen to find this package of ship's documents.";
					link.l10.go = "ShipLetters_out1";
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "I happen to find package of ship's documents, probably forgotten by someone.";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}
			}
			if (CheckAttribute(pchar, "Whisper.ActiveChardQuest") && !CheckAttribute(pchar, "Whisper.PortmanAtSea") && GetNpcQuestPastDayWOInit(npchar, "Whisper.LastSeenPortman") > 7 && GetNpcQuestPastDayWOInit(pchar, "Whisper.LastSeenPortman") > 7)
			{
				Link.l11 = "I'm looking for a captain named Ralph Portman. Did you have such a thing in your magazine?";
				Link.l11.go = "Whisper_chard_quest";
			}

			Link.l15 = "Thank you. Goodbye.";
			Link.l15.go = "exit";
		break;
		
		//========================  Квест "Strange things are happening in the archipelago" ==>
		case "PKM_BlackFregat":
			dialog.text = "Black frigate? Does the ship have a name? How do you think I should respond if my document lists all the ships with their name, and not with the color of the hull. I can't tell you anything else.";
			link.l1 = "Sorry, I'm going to keep looking.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_NevisPortMan_1");
		break;
		//========================  Квест "Strange things are happening in the archipelago" <==	

		case "Whisper_chard_quest":
			SaveCurrentNpcQuestDateParam(npchar, "Whisper.LastSeenPortman");
			if (!CheckAttribute(pchar, "Whisper.PortmanTries"))
			{
				pchar.Whisper.PortmanTries = 0;
			}
			pchar.Whisper.PortmanTries = sti(pchar.Whisper.PortmanTries)+1;
			if (npchar.nation != HOLLAND && npchar.nation != SPAIN)
			{
				if (sti(pchar.Whisper.PortmanTries) > 2)
				{
					WhisperSpawnPortman(npchar);
					SaveCurrentNpcQuestDateParam(pchar, "Whisper.LastSeenPortman");
					//SaveCurrentQuestDateParam("Whisper.LastSeenPortman");
					dialog.text = "There was one. He has only recently left the port. It seems to have gone to the colony "+XI_ConvertString("Colony" + pchar.Whisper.PortmanTargetCity)+". If you hurry up, you might still be able to catch up with him.";
					link.l1 = "Thank you, I'll go. Goodbye.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Hmm... No, I haven't had one yet.";
					link.l1 = "Thanks for the information, I'll go. Goodbye.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Who? If it's an Englishman, then it's unlikely. We only let them into the port in exceptional cases.";
				link.l1 = "Thanks and that's it, I'll go. Goodbye.";
				link.l1.go = "exit";
			}
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "Your problem is easily solvable. You can contact any official of the navigation service, and get all the available information about the route of your friend's ship.";
			link.l1 = "Unfortunately, it's not that simple. It is in your port that my friend, captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + " changed the name of the vessel... for religious reasons.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;

		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "So. This is already more difficult. I need to get the records in the ship's register up, it will take time. And nowadays, as you know, time is money...";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "I understand that perfectly, " + GetFullName(NPChar) + ", and ready to pay for your time... 1,000 gold, I'd say.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "Oh... And I don't have any money... I'll be back later...";
				link.l1.go = "exit";
			}
		break;

		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "Great! Let's see what we have there... Just a minute... okay... Here you are. The renaming is noted in the ship's register, and the vessel is now called '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' went to the side today " + XI_ConvertString("Colony" + sColony + "Gen") + ".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "Oh-oh-oh!... I mean, yes, you appreciated it, because I'm a very, very busy person. Just a minute... okay... Here you are. The renaming is noted in the ship's register. The vessel, now called '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' departed today aside " + XI_ConvertString("Colony" + sColony + "Gen") + ".";
				link.l1 = "Thank you, sir, you have done me a really great service.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;

		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("en", "on"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "What exactly do you want to know?";
			link.l1 = "Tell me, did this captain's ship enter your port?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "Hmm... May I ask what purpose you are looking for him for?";
			link.l1 = "I have business with him. If he wasn't in your port or you didn't...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "He was. But - thank the Saints - just this morning, he finally mercifully delivered us sinners from his company and headed to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Acc") + ". And I must admit, I sincerely feel sorry for anyone who has to deal with him.";
			link.l1 = "In that case, wish me luck, and thank you for your help.";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Voc"));
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if(rand(2) == 1)
			{
				Log_TestInfo("The next colony is the last");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "What exactly are you interested in, "+ GetSexPhrase("sir", "miss") +" " + GetFullName(PChar) + "?";
			link.l1 = "Tell me, did this captain enter your port?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "Hmm, I came in... He's come in so much that I'm looking forward to him leaving my long-suffering port.";
			link.l1 = "So this ship is still here?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "Yes, gracious "+ GetSexPhrase("my lord", "my lady") +". The entire port, from the last loader to the head of the pilotage service, prays for his speedy safe departure. The ship has just left the dry dock, where it received the necessary repairs, and its valiant captain managed to quarrel with every carpenter, and rejected three batches of selected planks for the outer skin. But tomorrow, the all-seeing and all-merciful Lord will deliver us from this... from this plague, from this plague in human form!";
			link.l1 = "Calm down, sir " + npchar.name + ", and think about the fact that someone is going to have a harder time than you right now. You've already been through this ordeal, and I'm just about to meet this captain... Let me take my leave.";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;

		case "ShipLetters_out1":
			dialog.text = "Let's take a look! Yes, this set is invalid in my documents. It's very kind of you to take the time to drop by and hand over the papers. Fair wind, Captain!";
			link.l1 = "Thank you!";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "10");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "Let's take a look! Yes, both this ship and its owner are listed in my documents.";
			s1 = s1 + "Your conscientiousness, Captain, does you credit! Of course, your efforts should be rewarded.";
			dialog.text = s1 + "Let's say " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " is ok?";
			link.l1 = "Of course not!";
			link.l1.go = "exit";
			link.l2 = "Well, a very modest amount, but the service is not great either. Yes, I accept your offer, "  + npchar.name +" .";
			link.l2.go = "ShipLetters_Portman1_2";
		break;

		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "5");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipLetters_Portman2":
			dialog.text = "Do you agree to accept my offer?";
			link.l1 = "Of course not!";
			link.l1.go = "exit";
			link.l2 = "Perhaps. Although I am sure that these papers are more expensive.";
			link.l2.go = "ShipLetters_Portman2_1";
		break;

		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "6");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "I'm listening to you carefully.";
			link.l1 = "I brought your fugitive.";
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = "Ah, Captain, thank you very much! How is she? Are you healthy, are you not injured? It's been a day since she ran away, the wretch. Do I wish her any harm? I'm going to get married... The groom is rich, young, and what is not good-looking, so do not drink water from the face. No! She tries everything in her own way-just like her mother, damn her...Yes, and she would not have been born if her mother had not run away with an enterprising blockhead at the time... Well, what to remember... Youth is naive, stupid... and cruel.";
			link.l1 = "Of course, you are the father and it's up to you, but I wouldn't rush happy wedding...";
			link.l1.go = "EncGirl_3";
		break;

		case "EncGirl_3":
			dialog.text = "What do you understand? Do you have children of your own? Not there? So, when they are, come in, then we'll talk... yes... I promised a reward to the one who returns it - please accept it.";
			link.l1 = "Thank you. And hold her tight. Something tells me she's not going to stop there.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, so you are that "+ GetSexPhrase("captain who brought", "girl who brought") +" my prodigal son with a young bride?";
				link.l1 = "Yes, I helped them escape.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, revealed"+ GetSexPhrase("you, benefactor", "you, benefactress") +". Are you expecting a reward?";
				link.l1 = "Well, not that there are awards, but it would be nice to hear gratitude.";
				link.l1.go = "EncGirl_6";
			}
		break;

		case "EncGirl_5":
			dialog.text = "I am very grateful to you for not leaving my child in a difficult situation and helping him to get out of such a delicate situation with honor. Let me thank you as much as I can. Accept this modest sum and a gift from me personally.";
			link.l1 = "Thank you, it was a pleasure to help these young people.";
			link.l1.go = "EncGirl_5_1";
		break;

		case "EncGirl_6":
			dialog.text = "What thanks?! What is the gratitude for?! Not only has this blockhead been hanging around without work for six months, he's also found time to be nice! Yes, I was already running my own business at his age. And look, he's gone hunting! The governor has a marriageable daughter, and this one has brought some kind of rootless slut, God forgive me, and is asking for parental blessing!";
			link.l1 = "Hmm, so you don't believe in sincere feelings?";
			link.l1.go = "EncGirl_6_1";
		break;

		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_6_1":
			dialog.text = "What kind of feelings are these?! What kind of feelings are you talking about? An adult, like a person, but there... Feelings! It should be a shame for you young people to indulge in such matters, and to contract as a pimp. The girl was torn out of her parents' nest and my sucker's life was ruined. There will be no gratitude to you. Goodbye.";
			link.l1 = "Well, you don't get sick either...";
			link.l1.go = "EncGirl_6_2";
		break;

		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ate", "la"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", "a"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "node_4":
			//--> проверка миниквестов начальника порта.
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "You should have found a captain named " + npchar.quest.PortmansJornal.capName + " and return the logbook to him. Did you do it?";
				link.l1 = "No, it didn't work out yet...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "You are trying to find the stolen " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. Until you complete this assignment, no other assignments are out of the question.";
				link.l1 = "I will continue the search, wait.";
				link.l1.go = "exit";
				link.l2 = "I want to cancel your assignment.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "You promised me you'd find the stolen one " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. Did you do it?";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName &&
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_LEUDO, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}
				if (bOk)
				{
					link.l1 = "Yes, I found him, he's standing in the harbor on the raid. You can take it.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "I will continue the search, wait.";
					link.l1.go = "exit";
				}
				link.l2 = "I want to cancel your assignment.";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта.

			//--> дача миниквестов начальника порта.
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("Yes, damn it! I have a job for you!",
					"Ha! You're just in time! I have a problem that needs to be resolved.",
					"Of course! Of course I have a job! Problems, you know, just crushed...");
				link.l1 = "State the point, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}

			// Warship 25.07.09 Генер "The burnt-out ship"
			if(dRand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "God! Captain " + GetFullName(PChar) + ", you are just in time! Such a misfortune has happened, such a misfortune... A ship burned down in our raid, left in the care of the port authority! By an oversight of the security team, it burned down... up to the waterline.. " +
					"Lord, why am I being punished like this? After all, so many years of faith and truth...";
				link.l1 = "Hmm, this is unprecedented - the ship burned down. And what are the insurance contracts for? Or have you not insured it? in order to save money, so to speak. And now we'd like to bite your elbow, yes...";
				link.l1.go = "BurntShip4";
				link.l2 = "With such questions, you need to go to the shipyard for help, not to me. In a couple of months, at least the old one will be restored, at least a new one will be built. I am not a shipbuilder"+ GetSexPhrase("", "nice") +", so sorry, wrong address...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "The governor is happy for the well-being of the city - he always has a job. Then, there may be interested merchants in the tavern, and the store sometimes charters captains.";
			Link.l1 = "One more question.";
			Link.l1.go = "node_2";
			Link.l2 = "Thank you. Goodbye.";
			Link.l2.go = "exit";
		break;


		/////////////////////////////////////////////////////////==========================/////////////////////////////////////////////////////
		//эскорт-пассажиры
		case "work_PU":
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("There is no work here for those who walk under the flag of " + NationNameGenitive(sti(pchar.nation)) + "! Leave my office immediately!", "I do not intend to cooperate with " + NationNameAblative(sti(pchar.nation)) + ". Get out of here!");
				link.l1 = RandPhraseSimple("Hmm, your right...", "Well, as you know...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("I have a whole list of passengers waiting for passing ships in my log. But I'm afraid there isn't an idiot among them who would agree to travel under your command. Reputation, you know, is a delicate thing, and notoriety in the Caribbean spreads like waves in a pond...", "I am constantly approached by merchants who need an escort. But an escort implies protection, not the danger of being robbed by one's own escort. Given the notoriety that follows you around, no merchant would take such a risk.");
				link.l1 = LinkRandPhrase("What?! Yes, all people lie.", "Is everyone really afraid of me?! Yes, it seems there is something for that.", "What kind of people have gone today! If there is no one to spit at, they immediately run to complain!");
				link.l1.go = "exit";
				break;
			}
			dialog.text = "I receive requests from merchants and passengers from all over the colony, who ask me to find escorts or passing ships to different parts of the archipelago. If you are looking for something specific, then you can take a look.";
			link.l1 = "I will gladly take on an escort if there is one along the way.";
			link.l1.go = "work_PU_1";
			link.l2 = "Are there many passengers? I just have some cabins available.";
			link.l2.go = "work_PU_2";
		}
		else
		{
			dialog.text = "Where is your ship? Are you going to carry passengers on your own hump?";
			link.l1 = "Hmm, that's right...";
			link.l1.go = "exit";
		}
		break;

		case "work_PU_1":
			if (!CheckAttribute(npchar, "work_date_PU") || GetNpcQuestPastDayParam(npchar, "work_date_PU") >= 2 || bBettaTestMode)
			{
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//при низком авторитете и на 7 класс не даём
				{
				dialog.text = "I'm sorry, but I don't have anyone willing to travel with you.";
				link.l1 = "Understood. Whatever you say.";
				link.l1.go = "exit";
				break;
				}
				//конвой
				if (!CheckQuestAttribute("generate_convoy_quest_progress", "begin"))
				{
					if (GetCompanionQuantity(PChar) == COMPANION_MAX)
					{
						dialog.text = "But your squadron is too big for an escort. Merchants will not go to such a caravan, which in itself can attract unwanted attention.";
						link.l1 = "That's right, I didn't think about it. Okay, I'll come back later if I'm in the mood.";
						link.l1.go = "exit";
					}
					else
					{
						if (drand(6) > 1)
						{
							dialog.text = "I don't know if it will be on the way, but I just had one merchant who was looking for an escort... Ah, that's how he came back!";
							link.l1 = RandPhraseSimple("Do you know him well? Is he a wealthy gentleman or a crook?", "And who is he? Is he worth dealing with?");
							link.l1.go = "ConvoyAreYouSure_PU";

						}
						else
						{
									dialog.text = "I usually have a lot of merchants who need an escort, but now, unfortunately, there's no one. Maybe you'll have better luck another day.";
							link.l1 = RandPhraseSimple("Okay, there is no trial either.", "Yes, it was not lucky... Well, goodbye.");
							link.l1.go = "exit";
						}
					}
			  	}
				else
				{
					dialog.text = "But you already have a maintainer. In case of an attack, you will not be able to protect several ships at the same time - you will have to sacrifice someone. No merchant would do that. So finish what you started first, then come over.";
					link.l1 = RandPhraseSimple("What kind of cowardly merchants have gone these days. And they would have to go alone, and across the Atlantic... Well, anyway, goodbye.", "That's a bad luck... All right, have a nice day.");
					link.l1.go = "exit";
					}
				}
				else
				{
				dialog.text = "No one is here today. Come back in a couple of days.";
					link.l1 = "Okay. Whatever you say.";
								link.l1.go = "exit";
				}
		break;

		case "work_PU_2":
			if (!CheckAttribute(npchar, "work_date_PU") || GetNpcQuestPastDayParam(npchar, "work_date_PU") >= 2 || bBettaTestMode)
			{
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//при низком авторитете и на 7 класс не даём
				{
				dialog.text = "I'm sorry, but I don't have anyone willing to travel with you.";
				link.l1 = "Understood. Whatever you say.";
				link.l1.go = "exit";
				break;
				}
				 // пассажир
				if (drand(6) > 1)
				{
					dialog.Text = "A lot, not a lot, but one guy has already come in several times today, looking for a passing ship. Yes, here he is again!";
					link.l1 = RandPhraseSimple("Do you think it's worth taking him on board?", "And what kind of person? Is it worth dealing with?");
					Link.l1.go = "PassangerAreYouSure_PU";
				}
				else
				{
					dialog.text = "Unfortunately, there are no passengers today. So don't blame me...";
					link.l1 = RandPhraseSimple("Well, no, that's not it. What is there ...", "Yes, it was not lucky... Well, goodbye.");
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "No one is here today. Come back in a couple of days.";
				link.l1 = "Okay. Whatever you say.";
				link.l1.go = "exit";
			}
		break;

		case "ConvoyAreYouSure_PU":
			dialog.text = RandPhraseSimple("Yes, quite a respectable gentleman. On the price agree yourself, here I am not your assistant.", "God be with you, I will not advise anyone. If only you could agree on the price.");
			Link.l1 = "I see. Now we'll find out where he needs to go.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity_PU(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date_PU");
		break;

		case "PassangerAreYouSure_PU":
			dialog.text = RandPhraseSimple("Yes, quite a normal passenger.", "Why not? Quite a wealthy gentleman.");
			Link.l1 = "Thanks, I'll talk to you now.";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity_PU(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date_PU");
		break;


		case "PortmanQuest_NF":
			dialog.text = "Hmm, this is bad. In that case, I'm out of the question about any new job.";
			link.l1 = "Understood. That's what I wanted to say...";
			link.l1.go = "node_2";
		break;

		// Warship 25.07.09 Генер "The burnt-out ship"
		/*case "BurntShip1":
			dialog.text = "You're right, Captain, but the thing is, there's little hope of help... A ship burned down in our raid, left in the care of the port authority! By an oversight of the security team, it burned down... up to the waterline" +
				"Lord, why am I being punished like this? After all, so many years of faith and truth...";
			link.l1 = "Okay, my dear, let's do everything in order, otherwise we won't agree on anything.";
			link.l1.go = "BurntShip3";
			link.l2 = "With such questions, you need to go to the shipyard for help, not to me. In a couple of months, at least the old will be restored, at least a new one will be built. I am not a shipbuilder"+ GetSexPhrase("", "nice") +", so sorry, wrong address...";
			link.l2.go = "BurntShip2";
		break;*/

		case "BurntShip2":
			dialog.text = "Very sorry, Captain... It's a pity that you don't want to help me.";
			link.l1 = "It's not about desire, dear. You understand that... Goodbye...";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;

		/*case "BurntShip3":
			dialog.text = "Yes, yes, Captain. In general, the misfortune is terrible... Nothing like this has happened in my long career. Only Providence and your good will can save us.";
			link.l1 = "Hmm, this is unprecedented - the ship burned down. And what are the insurance contracts for? Or have you not insured it? in order to save money, so to speak. And now we'd like to bite your elbow, yes...";
			link.l1.go = "BurntShip4";
		break;*/

		case "BurntShip4":
			dialog.text = "What are you, Captain?! Fear God!.. How can you?! I know my business well, I've been serving tea for so many years. And there are insurance contracts, and the insurance company is ready to make a payment, and the insurance amount is considerable, I assure you.";
			link.l1 = "Dear, so what is your problem? A hook cell exploded from a fire, and people were injured, and are you being sued for negligence?";
			link.l1.go = "BurntShip5";
		break;

		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");

			dialog.text = "Well, what didn't happen, didn't happen - the Lord was merciful, otherwise I wouldn't have had my head blown off. The empty hold was as empty as it was, thank God, the Blessed Virgin Mary!" +
				"And the whole problem is that the ship belongs to someone... rather, it belonged to the well-known Caribbean gentleman " + sCapitainId + ". And it was built in Europe on a special order, with extraordinary characteristics. " +
				"And the owner was very proud of this ship and boasted wherever he went, a kind of fool, God forgive me... What am I going to tell him now? At least get into the loop, by God...";
			link.l1 = "Oh, I see you're in a lot of trouble. And what was wrong with it, as with all ships? That is, what was this gentleman so proud of in his boat?";
			link.l1.go = "BurntShip6";

			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;

		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);

			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);

			switch(attrL)
			{
				case "speedrate":
					attrL = "" + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Gen")) + ", speed was over " + NPChar.Quest.BurntShip.ShipNeededValue + " knots. For a privateer, this was the first pride... He's just telling his boys to hang me from the yard! The devil brought him to our harbor along with his pirate tub...";
				break;

				case "turnrate":
					attrL = "" + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Gen")) + ", maneuverability was over " + NPChar.Quest.BurntShip.ShipNeededValue + " units. This was the first pride for the soldier... He says to spot me with spitzrutens! The devil told him to leave his vessel with me...";
				break;

				case "capacity":
					attrL = "" + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Gen")) + ", deadweight was over " + NPChar.Quest.BurntShip.ShipNeededValue + " displacement units. For a merchant, this was the first pride... He's quartering me without a trial. The devil pulled him to leave his trough with me!";
				break;
			}

			dialog.text = attrL;
			link.l1 = "What do they say at the shipyard? Is it really impossible to build such a thing here?";
			link.l1.go = "BurntShip7";
		break;

		case "BurntShip7":
			dialog.text = "No one is taking it. I already went to the neighboring island with a bow. They say that there is a noble master in Bermudes. But where are we, and where are Bermudes. It remains only for the help of such free captains as you can count on. After all, you are drowning these tubs by the dozens. Maybe it won't be difficult for you to find a similar boat for me. And we will touch it up here, we will correct it so that the owner does not complain " +
				"I will thank you generously, and the insurance company will not be stingy. It's an extraordinary thing, you know. Who wants to fall out of favor with such an influential gentleman?";
			link.l1 = "Yes, it's not easy. How much time do I have?";
			link.l1.go = "BurntShip8";
			link.l2 = "No, my dear, I will not take it up. And no one will give guarantees that a vessel with similar characteristics exists. Don't forget...";
			link.l2.go = "BurntShip2";
		break;

		case "BurntShip8":
			dialog.text = "Thank God, there is time. The owner has left for Europe and will not turn around before six months.";
			link.l1 = "Well, I'll take it. I will deliver a similar vessel to you. But keep in mind, if you start to be stingy and cut out, I'll burn it right in front of your eyes!";
			link.l1.go = "BurntShip9";
		break;

		case "BurntShip9":
			dialog.text = "What are you, Captain? How can I? I understand that this is not a tub to fish out of the first puddle, it will take time... You just bring the ship, and we'll part ways. Rest assured...";
			link.l1 = "I hope so... Wait for me with good news. Goodbye.";
			link.l1.go = "BurntShip9_exit";
		break;

		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 120, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 120, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 120, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;

			attrL = NPChar.Quest.BurntShip.ShipAttribute;

			iTest = sti(NPChar.Quest.BurntShip.ShipType);

			switch(attrL)
			{
				case "speedrate":
					attrL = "speed. U " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " the wind speed should be at least " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;

				case "turnrate":
					attrL = "maneuverability. U " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " maneuverability should be at least " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;

				case "capacity":
					attrL = "the hold. U " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " the hold must be at least " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}

			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Voc"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);

			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя

			DialogExit();
		break;

		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = "What did you want to talk about?";
			link.l1 = "Where is the former head of the port authority, sir " + NPChar.Quest.BurntShip.LastPortmanName + "? I have business with him.";
			link.l1.go = "BurntShip11";
		break;

		case "BurntShip11":
			dialog.text = "But it's not there... Can you imagine? he burned the ship of a famous gentleman and pocketed the insurance amount. By the time the authorities figured out what was going on, he had already resigned and slipped away to Europe. What a rascal, eh?";
			link.l1 = "Yes, I know this story. Excuse me, I have to go...";
			link.l1.go = "BurntShip11_exit";
		break;

		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);

			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = "What did you want to talk about?";
			link.l1 = "I brought a vessel with an extraordinary characteristic. I am waiting for the promised reward.";
			link.l1.go = "BurntShip14";
			link.l2 = "You know, " + GetFullName(NPChar) + ", I cant see any vessels with the characteristics you ordered. I think I'll give up this assignment. Sorry if I let you down...";
			link.l2.go = "BurntShip13";
		break;

		case "BurntShip13":
			dialog.text = "Very sorry, Captain... It's a pity that you don't want to help me.";
			link.l1 = "It's not about desire, dear. You understand that... Goodbye...";
			link.l1.go = "BurntShip13_exit";
		break;

		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);

			ChangeCharacterReputation(PChar, -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		case "BurntShip14":
			dialog.text = "That's how it is! And what is the name of our new ship?";

			sTitle = NPChar.Quest.BurntShip.ShipAttribute;

			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);

			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);

					if(cn > 0)
					{
						chref = GetCharacter(cn);

						sld = &RealShips[sti(chref.ship.type)];

						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}

			link.l99 = "Sorry, I'll come back later.";
			link.l99.go = "exit";
		break;

		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Ah, Captain, I'm glad I didn't make a mistake about you! You did a great job, you just saved me from death... Please come back for the money in two days. The formalities, you know, need to be settled with the receipt of the insurance amount... In the meantime, get the ship in order. Well, the sails need to be updated, the holes patched up, the heeling, again, will not hurt...";
			link.l99 = "Have you forgotten what exactly I promised you, if there will be delays in payment?";
			link.l99.go = "BurntShip16";
		break;

		case "BurntShip16":
			dialog.text = "No, no, God forbid! I'll keep my word, don't worry. Simply, knowing that there were still expenses to be spent on, so to speak, disguising the ship, I put the insurance amount in growth. Don't get me wrong...";
			link.l1 = "I will understand you when the piastres are in my chest. See you later.";
			link.l1.go = "BurntShip16_exit";
		break;

		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");

			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату

			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время

			DialogExit();
		break;

		case "BurntShip17":
			dialog.text = "What did you want to talk about?";
			link.l1 = "I'm here for a reward. I still have the ship you need.";
			link.l1.go = "BurntShip18";
		break;

		case "BurntShip18":
			dialog.text = "Please remind me of its name. Otherwise, with all this hassle, you know, there is absolutely no memory left.";

			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);

			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);

					if(cn > 0)
					{
						chref = GetCharacter(cn);

						sld = &RealShips[sti(chref.ship.type)];

						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}

			link.l99 = "Sorry, I'll come back later.";
			link.l99.go = "exit";
		break;

		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 1.2;
			rRealShip = GetRealShip(GetCharacterShipType(sld));//почему считается цена привезенного корабля, а не цена сгоревшего? :)
			if (sti(rRealShip.Stolen)) cn *= 2;//"ворованные" компенсируются
			dialog.text = "Yes, great! I am ready to give out your reward, " + FindRussianMoneyString(cn) + ". This is how the insurance company assessed the burnt-out vessel. The insurance was paid with credit chests - there is no cash, sorry.";
			link.l1 = "Uh no, this amount won't suit me. I am sure that this ship is much more expensive.";
			link.l1.go = "BurntShip21";
			link.l2 = "That's a completely different matter. I am glad that I could help you. See you later.";
			link.l2.go = "BurntShip20_exit";

			NPChar.Quest.BurntShip.Money = cn;

			//sTitle = "BurntShipQuest" + NPChar.location;
			//PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
		break;

		case "BurntShip20_exit":
			//AddMoneyToCharacter(PChar, sti(NPChar.Quest.BurntShip.Money));
			TakeNItems(pchar, "chest", makeint((sti(NPChar.Quest.BurntShip.Money) + 7500)/15000));
			Log_Info("You got the credit chests");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("", "a"));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);

			ChangeCharacterReputation(PChar, 3);

			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);

			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		case "BurntShip21":
			dialog.text = "Well, what are you, Captain?! Believe me, I know what I'm saying. For such money, you could buy two similar vessels!";
			link.l1 = "I'd rather keep it for myself. I really liked it... Goodbye.";
			link.l1.go = "BurntShip21_exit";
		break;

		case "BurntShip21_exit":
			ChangeCharacterReputation(PChar, -5);

			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("", "a"));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);

			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		//--> миниквесты портмана
		case "PortmanQuest":
			if (cRand(2) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = "A captain forgot my logbook. How can he be so сareless!.. In general, you need to catch up with him and return the loss.";
				link.l1 = "Well, it's possible... I'm taking this job!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "No, I don't want to do this. These are his problems, actually...";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "A ship was stolen from my ship parking lot. I want you to find it and return to me.";
				link.l1 = "Hmm, well, I'm ready to take up the search.";
				link.l1.go = "SeekShip_1";
				link.l2 = "I'm sorry, but I'm not looking for ships.";
				link.l2.go = "node_2";
			}
		break;
		// -------------------------------- квест доставки судового журнала до рассеяного кэпа --------------------------
		case "PortmanQuest_1":
			dialog.text = "Great, here's his log... Ugh, it's a load off my mind! The loss of a ship's log is an unpleasant thing, I worry about such captains.";
			link.l1 = "That's for sure, it's worth worrying about! Well, now tell me more about this absent-minded captain.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 0); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "Yes, of course! His name is " + npchar.quest.PortmansJornal.capName + "He's captain of " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")) + " with name '" + npchar.quest.PortmansJornal.shipName + "'. He went to sea recently, but headed to " + XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc") + ".";
			link.l1 = "Understood. Well, I'll definitely find him. What about the payment?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName + " he will settle with you, it is in his interests. Just try to find him faster, and everything will be fine.";
			link.l1 = "Clear. Well, goodbye...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Voc"));
			}
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = "Great! You know, the stolen ship doesn't belong to the last person, so it's very important to me. I will pay well for the work...";
			link.l1 = "Understood. Tell us in more detail what kind of ship it was, under what circumstances it was stolen.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 0); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " with name '" + npchar.quest.PortmansSeekShip.shipName + "'. It was stolen at night, " + FindRussianDaysString(rand(5)+10) + " ago. The watchman has been killed.";
			link.l1 = "Hmm, they've already managed to leave, probably decently. In general, there is no need to talk about hot tracks...";
			link.l1.go = "SeekShip_3";
			link.l2 = LinkRandPhrase("Sorry, but I can't complete this responsible assignment...", "No, it doesn't suit me...", "Unfortunately, I have to give up the search...");
			link.l2.go = "SeekShip_Icantfindship";
		break;
		case "SeekShip_Icantfindship":
			dialog.text = "Very sorry, " + GetAddress_Form(npchar) + "... I was counting on you very much...";
			link.l1 = "I'm sorry again... Goodbye.";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор ещё жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0;
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана

			ChangeCharacterReputation(pchar, -2);
		break;
		case "SeekShip_3":
			dialog.text = "Yes, that's right. But there was no point in me immediately raising a panic. If the military catches up, they'll smash the ship to pieces, and that's not exactly what I need.";
			link.l1 = "Understood. Well, I'm starting to search. I hope I get lucky.";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;
		case "SeekShip_break":
			dialog.text = "Hmm, well, it's a pity. Although it was difficult to count on success...";
			link.l1 = "Yes, too much time has passed since the theft.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "Well, thank you for your help, even though it was not successful.";
			link.l1 = "You're welcome...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор ещё жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0;
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterReputation(pchar, -7);
		break;
		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "Great! However, I believe that this is not exactly the ship that was stolen... Although, actually, it doesn't matter! I'm taking it from you.";
				link.l1 = "Yes, indeed...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterReputation(pchar, 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
				AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "Excellent! You've been very helpful. I can imagine how difficult it was.";
				link.l1 = "Yes, indeed...";
				ChangeCharacterReputation(pchar, 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
				AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
				AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
				AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "I am ready to pay you a reward. It is " + FindRussianMoneyString(makeint(sti(npchar.quest.chest)*15000)) + " in chests. Unfortunately, I can't pay any more.";
			link.l1 = "Well, that's enough too. Thank you and have a nice day.";
			link.l1.go = "exit";
			//AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, "chest", sti(npchar.quest.chest));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);

			AchievementsCounter_genquests(1);

			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "BuyLicense":
				dialog.text = "I have one document that is about to expire. I don't know why anyone would need it, but I'm just glad to get rid of this piece of paper. For a certain amount, of course. " + license_price + ". Do you take it?";
				if(makeint(Pchar.money) >= license_price)
				{
					link.l1 = "I take it.";
					link.l1.go = "LicenseBought";
				}
				link.l2 = "No. Thank you.";
				link.l2.go = "exit";
		break;
		case "LicenseBought":
				AddMoneyToCharacter(Pchar, -license_price);
				GiveNationLicence(sti(NPChar.nation), license_expires);

				dialog.text = "Hold on.";
				link.l1 = "Goodbye.";
				link.l1.go = "exit";
				license_expires = rand(2);
		break;
		case "CapitainList":
			makearef(arCapBase, npchar.quest.capitainsList);
			if (GetAttributesNum(arCapBase) > 0)
			{
				dialog.text = "There are registered captains. Who exactly are you interested in?";
				for (i=0; i<GetAttributesNum(arCapBase); i++)
				{
					arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", captain of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Gen")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "I don't have any captains on my list who can interest you.";
				link.l1 = "Understood. Thanks for the information.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
			if (GetAttributesNum(arCapBase) <= 0) {
				trace("ERROR: capitainsList is empty")
				link.l2 = "That's it, I'm not interested in captains anymore.";
				link.l2.go = "node_2";
				break;
			}
			arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Yeah, let's see... Yeah, there is! ", "Well, well... yeah, I found it!", "So that's it. ") +
				"Captain" + GetFullName(sld) + " " + arCapLocal.date + " the year left our port in " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Thank you. I would like to see the list further...";
			link.l1.go = "CapitainList";
			link.l2 = "That's it, I'm not interested in captains anymore.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Voc"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
			if (GetAttributesNum(arCapBase) <= 1) {
				trace("ERROR: capitainsList is empty")
				link.l2 = "That's it, I'm not interested in captains anymore.";
				link.l2.go = "node_2";
				break;
			}
			arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Yeah, let's take a look... Yeah, there is! ", "Well, well... yeah, I found it!", "So that's it. ") +
				"Captain" + GetFullName(sld) + " " + arCapLocal.date + " the year left our port in " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Thank you. I would like to see the list further...";
			link.l1.go = "CapitainList";
			link.l2 = "That's it, I'm not interested in captains anymore.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Voc"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
			if (GetAttributesNum(arCapBase) <= 2) {
				trace("ERROR: capitainsList is empty")
				link.l2 = "That's it, I'm not interested in captains anymore.";
				link.l2.go = "node_2";
				break;
			}
			arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Yeah, let's see... Yeah, there is! ", "Well, well... yeah, I found it!", "So that's it. ") +
				"Captain" + GetFullName(sld) + " " + arCapLocal.date + " the year left our port in " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Thank you. I would like to see the list further...";
			link.l1.go = "CapitainList";
			link.l2 = "That's it, I'm not interested in captains anymore.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Voc"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
			if (GetAttributesNum(arCapBase) <= 3) {
				trace("ERROR: capitainsList is empty")
				link.l2 = "That's it, I'm not interested in captains anymore.";
				link.l2.go = "node_2";
				break;
			}
			arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Yeah, let's take a look... Yeah, there is! ", "Well, well... yeah, I found it!", "So that's it. ") +
				"Captain" + GetFullName(sld) + " " + arCapLocal.date + " the year left our port in " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Thank you. I would like to see the list further...";
			link.l1.go = "CapitainList";
			link.l2 = "That's it, I'm not interested in captains anymore.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Voc"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
			if (GetAttributesNum(arCapBase) <= 4) {
				trace("ERROR: capitainsList is empty")
				link.l2 = "That's it, I'm not interested in captains anymore.";
				link.l2.go = "node_2";
				break;
			}
			arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Yeah, let's take a look... Yeah, there is! ", "Well, well... yeah, I found it!", "So that's it. ") +
				"Captain" + GetFullName(sld) + " " + arCapLocal.date + " the year left our port in " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Thank you. I would like to see the list further...";
			link.l1.go = "CapitainList";
			link.l2 = "That's it, I'm not interested in captains anymore.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Voc"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
				ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "Which ship exactly do you want to leave?";
					for(i=1; i<COMPANION_MAX; i++)//почему нельзя свой единственный корабль сдать?
					{
						cn = GetCompanionIndex(PChar, i);
						if(cn > 0)
						{
							chref = GetCharacter(cn);
							if (!GetRemovable(chref)) continue;
							if(RealShips[sti(chref.Ship.Type)].BaseName == SHIP_SOLEYRU) continue; //Отрубаем хитрость на получение Солея

							attrL = "l"+i;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'. I think will leave with him captain " + GetFullName(chref) + ".";
							Link.(attrL).go = "ShipStockMan11_" + i;
							attrL = "l"+i+COMPANION_MAX;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' without officer.";
							Link.(attrL).go = "ShipStockMan22_" + i;

						}
					}
					Link.l17 = "Thanks, no need.";
					Link.l17.go = "exit";
				}
				else
				{
					dialog.text = "Hmm. I don't see your ships in port.";
					Link.l1 = "I just wanted to find out about the possibility of parking.";
					Link.l1.go = "exit";
				}
		break;

		case "ShipStock_Choose":
			dialog.text = "Let's see what kind of ship it is.";
			Link.l1 = "Good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, I changed my mind.";
			Link.l2.go = "exit";
		break;

		case "ShipStock_2":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (pchar.location != "Caiman_PortOffice")  NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			else NPChar.MoneyForShip = 0;
			if (pchar.location != "Caiman_PortOffice")
			{
				dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', class " + RealShips[sti(chref.Ship.Type)].Class +
					 ", parking cost " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + " per month, money first.";
			}
			else
			{
				dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', class" + RealShips[sti(chref.Ship.Type)].Class +
					 ", parking is free.";
			}
			Link.l1 = "Yeah. That's fine with me.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
				Link.l1.go = "ShipStock_3";
			}
			else
			{
				Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "No, I changed my mind.";
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "Everything will suit me too, if you have the right amount.";
			Link.l1 = "Oops... I'll come back later.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			if (sti(NPChar.StoreWithOff))
			{
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.ShipInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта
			//chref.Ship.Crew.Quantity  = 0;
			RemoveCharacterCompanion(pchar, chref);
			}
			else
			{
			chref = GetCharacter(NPC_GenerateCharacter("ShipInStockMan", "PKM_rab_"+(rand(3)+1), "man", "man", rand(5)+1, NPChar.nation, -1, false));
			chref.id = chref.id + "_" + chref.index; //меняем ID на оригинальный
			chref.reputation = 10 + rand(80);
			chref.lastname = chref.name;//"watchman Ivan" лучше чем "watchman Ivanov"?
			chref.name = "the watchman";
			DeleteAttribute(chref, "ship");
			chref.ship = "";

			chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта

			compref = GetCharacter(sti(NPChar.ShipToStoreIdx));//компаньон, у которого надо забрать корабль

			makearef(arTo, chref.ship);
			makearef(arFrom, compref.Ship);
			CopyAttributes(arTo, arFrom);

			compref.ship.type = SHIP_NOTUSED;
			RemoveCharacterCompanion(pchar, compref);
			AddPassenger(pchar, compref, false);
			DelBakSkill(compref);
			}

			chref.location = "";
			chref.location.group = "";
			chref.location.locator = "";
			NPChar.Portman	= sti(NPChar.Portman) + 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) + 1;//разобраться - что это. не могу найти, где оно используется.

			dialog.text = "Okay. You can pick it up when you need it.";
			Link.l1 = "Thank you.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
				{
					dialog.text = "What ship?";
					cn = 1;
					for(i=1; i<MAX_CHARACTERS; i++)
					{
						makeref(chref, Characters[i]);
						if (CheckAttribute(chref, "ShipInStockMan"))
						{
							if (chref.ShipInStockMan == NPChar.id)
							{
								attrL = "l"+cn;
								if(HasSubStr(chref.id, "ShipInStockMan_"))
								{
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
								Link.(attrL).go = "ShipStockManBack22_" + i;
								}
								else
								{
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' and officer " + GetFullName(chref) + ".";
								Link.(attrL).go = "ShipStockManBack11_" + i;
								}
								cn++;
							}
						}
					}

					Link.l99 = "No, I changed my mind.";
					Link.l99.go = "exit";
				}
				else
				{
					dialog.text = "Your squadron is too big. There is no longer enough space for your ships in the water area.";
					Link.l1 = "Yes, that's right. I'll pick it up another time.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. I don't see your flagship in port. And you can only pick up your ships here.";
				Link.l1 = "Okay, I'll come get them later.";
				Link.l1.go = "exit";
			}
		break;
	  	case "ShipStockManBack":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);

			//if (sti(NPChar.StoreWithOff)) string sTextAdd = ""; else string sTextAdd = "And which of your officers will take him away?";

			if (sti(NPChar.MoneyForShip) > 0)
			{
				dialog.Text = "Are you taking it? You are charged for storing more " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + ".";
			}
			else
			{
				dialog.Text = "Are you taking it?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Yes.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "No, I changed my mind.";
			Link.l2.go = "exit";
		break;

		case "ShipStockManBack2":
			if (sti(NPChar.StoreWithOff))
			{
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			}
			else
			{
			dialog.Text = "Which of your officers should I give it to?";
			int _curCharIdx;
			int q = 0;
			int nListSize = GetPassengersQuantity(pchar);
			for(i=0; i<nListSize; i++)
				{
				_curCharIdx = GetPassenger(pchar,i);
				sld = GetCharacter(_curCharIdx);
					if (_curCharIdx!=-1)
					{
						ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
						if (!CheckAttribute(sld,"HPminusDaysNeedtoRestore"))
						{
							if (!ok && GetRemovable(&characters[_curCharIdx]))
							{
								attrL = "l"+i;
								sProf = "";
								if (IsOfficer(sld)) sProf += " (fighter)";
								if (sti(pchar.Fellows.Passengers.navigator) == sti(sld.index)) sProf += " (navigator)";
								if (sti(pchar.Fellows.Passengers.boatswain) == sti(sld.index)) sProf += " (boatswain)";
								if (sti(pchar.Fellows.Passengers.cannoner) == sti(sld.index)) sProf += " (gunner)";
								if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index)) sProf += " (doctor)";
								if (sti(pchar.Fellows.Passengers.carpenter) == sti(sld.index)) sProf += " (carpenter)";
							    if (sti(pchar.Fellows.Passengers.treasurer) == sti(sld.index)) sProf += " (treasurer)";
								Link.(attrL)	= GetFullName(&characters[_curCharIdx]) + sProf;
								Link.(attrL).go = "ShipStockManBack2_" + i;
								q++;
							}
						}
					}
				}
			attrL = "l"+nListSize;
			if (q == 0)
				{
				Link.(attrL) = RandSwear() + "I forgot to bring captain for this ship with me.";
				Link.(attrL).go = "exit";
				}
			else
				{
				Link.(attrL) = "No, I changed my mind.";
				Link.(attrL).go = "exit";
				}
			}
		break;

		//ОЗГ, Хоум
		case "Houm_portman_1":
			if (pchar.questTemp.Headhunter.City == npchar.city)
			{
				dialog.text = "Yes, I stopped. You can find captain you are interested in in the city.";
				link.l1 = "Thank you! You have helped me a lot.";
				link.l1.go = "Houm_portman_yes";
			}
			else
			{
				dialog.text = "No, this is the first time I've heard of this.";
				link.l1 = "Hmm... Okay, we'll keep looking.";
				link.l1.go = "exit";
			}
		break;

		case "Houm_portman_yes":
			pchar.questTemp.Headhunter = "houm_tavern";
			CreateHoum();
			AddQuestRecord("Headhunt", "5");
			AddQuestUserData("Headhunt", "sCity", pchar.questTemp.Headhunter.Cityname);
			DialogExit();
		break;
		//ОЗГ, Хоум
	}
}

float BurntShipQuest_GetMaxNeededValue(int iShipType, string _param)
{
	float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
	switch (_param)
	{
		case "speedrate":
			NeededValue += ((0.33 + frandSmall(0.27)) * (NeededValue/10.0));
		break;
		case "turnrate":
			NeededValue += ((0.33 + frandSmall(0.28)) * (NeededValue/10.0));
		break;
		case "capacity":
			NeededValue += ((0.33 + frandSmall(0.28)) * (NeededValue/8.0));
		break;
	}
	return NeededValue;
}


// Warship 25.07.09 Генер "The burnt-out ship.". Начальные иниты для портмана - тип разыскиваемого судна, выдающаяся характеристика и т.д.
void BurntShipQuest_FillStartParams(ref _npchar)
{
	int rank = sti(PChar.rank);
	int shipType, temp;
	float neededValue;
	String shipAttribute;
	ref rBaseShip;

	// TODO Пересмотреть зависимость от ранга
	if (rank < 5) temp = 6;
	if (rank >= 5 && rank < 10) temp = 5;
	if (rank >= 10 && rank < 15) temp = 4;
	if (rank >= 15 && rank < 20) temp = 3;
	if (rank >= 20 && rank < 30) temp = 2;
	if (rank >= 30) temp = 1;
	shipType = GetShipTypeExtNotNation(temp, temp, "", sti(_npchar.Nation));
	rBaseShip = GetShipByType(shipType);
	temp = 0;
	if (rBaseShip.Type.Merchant == true) temp++;//для торговых и универсальных рандом от 1 до 2, для военных от 0 до 1
	switch(temp+rand(1))
	{
		case 0: shipAttribute = "turnrate"; break;
		case 1: shipAttribute = "speedrate"; break;
		case 2: shipAttribute = "capacity"; break;
	}

	neededValue = BurntShipQuest_GetMaxNeededValue(shipType, shipAttribute);

	Log_TestInfo("shipType == " + shipType);
	Log_TestInfo("ShipAttribute == " + shipAttribute);
	Log_TestInfo("ShipNeededValue == " + neededValue);

	_npchar.Quest.BurntShip.ShipType = shipType;
	_npchar.Quest.BurntShip.ShipAttribute = shipAttribute;

	if(shipAttribute != "capacity") // Чтобы трюм с десятичными не писался
	{
		_npchar.Quest.BurntShip.ShipNeededValue = FloatToString(neededValue, 2);
	}
	else
	{
		_npchar.Quest.BurntShip.ShipNeededValue = MakeInt(neededValue);
	}
}


void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true));
	SetCaptanModelByEncType(sld, "trade");
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушёл кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("The Absent-minded Cap " + sld.id + " headed to: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red"; //стояла модель кораблекрушенца
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity)) + 1; //дней доехать даём с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 2;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
	makearef(arCapBase, npchar.quest.capitainsList);
	int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId;
	for (int i=0; i<Qty; i++)
	{
		arCapLocal = GetAttributeN(arCapBase, i);
		sCapitainId = GetAttributeName(arCapLocal);
		if (GetCharacterIndex(sCapitainId) > 0) //если ещё жив
		{
			bResult++;
		}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
	}
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаём кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true));
	SetCaptanModelByEncType(sld, "pirate");
	SetShipToFantom(sld, "pirate", true);
	sld.Ship.Mode = "pirate";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	npchar.quest.chest = 7-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	Log_TestInfo("Cap Thief " + sld.id + " exited: " + sld.city + " and headed to: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спёр корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city)) + 1; //дней доехать даём с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 2;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";
		break;
		case 1:
			itemID = "jewelry2";
		break;
		case 2:
			itemID = "jewelry3";
		break;
		case 3:
			itemID = "jewelry3";
		break;
		case 4:
			itemID = "jewelry5";
		break;
		case 5:
			itemID = "jewelry17";
		break;
	}
	return itemID;
}

string findTraderCity_PU(ref NPChar)
{
	int n, nation;
	int storeArray[MAX_COLONIES];
	int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
			if(nation != RELATION_ENEMY)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity_PU(ref NPChar)
{
	int n, nation;
	int storeArray[MAX_COLONIES];
	int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

void DelBakSkill(ref _compref)
{
	DelBakSkillAttr(pchar);
	ClearCharacterExpRate(pchar);
	RefreshCharacterSkillExpRate(pchar);
	SetEnergyToCharacter(pchar);

	DelBakSkillAttr(_compref);
	ClearCharacterExpRate(_compref);
	RefreshCharacterSkillExpRate(_compref);
	SetEnergyToCharacter(_compref);
}
