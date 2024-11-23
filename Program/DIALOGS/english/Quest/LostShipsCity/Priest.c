
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	if (CheckAttribute(pchar, "ReturnToLSC") && !CheckAttribute(NPChar, "MetAgain"))
	{
		NPChar.MetAgain = true;
		dialog.text = "Captain, did you survive after all? I can't believe my eyes!";
		link.l1 = "As you can see, Padre."
		link.l1.go = "MetAgain1";
		return;
	}

	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "Give thanks to our Lord, Jesus Christ, for your salvation! Until the storm passed...";
					link.l1 = "I exalt, Padre, and thank you for the honor you have given me to prolong my miserable existence on this mortal earth... My name is " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.text = "Let us praise our Lord!";
					link.l1 = "I exalt, Padre, and thank you for the honor you have given me to prolong my miserable existence on this mortal earth... My name is " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "What do you need, "+ GetSexPhrase("my son", "my daughter") +"?";
    			link.l1 = RandPhraseSimple("I want to donate to the parish of the City, Holy Father.", "I want to make a donation to the parish of the City, Padre.");
    			link.l1.go = "donation";
				link.l2 = "Padre, I need to find a citizen. Do you know where he is now?";
				link.l2.go = "SeekCitizen";
				link.l3 = "I want to ask you a question, Holy Father.";
				link.l3.go = "int_quests";
				квесты
				if (pchar.questTemp.LSC != "AdmiralIsWaiting" && !CheckAttribute(npchar, "quest.takeCandles"))
				{
					link.l4 = "Padre, is there anything I can do to help your parish?";
					link.l4.go = "askCandles";
				}
				if (CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "seek" && CheckCharacterItem(pchar, "mineral3"))
				{
					link.l4 = "Padre, I want to give you the candles.";
					link.l4.go = "takeCandles";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.takeCandles"))
				{
					link.l8 = "Holy Father, I want to ask if I can purchase some goods from you?";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "seek")
				{
					link.l8 = "Holy Father, I want to ask if I can purchase some goods from you?";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "found")
				{
					link.l8 = "Holy Father, I want to ask you for medicine.";
					link.l8.go = "FSeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Holy Father, I have a serious offer for you.";
					link.l8.go = "SeekCrew";
				}
				if (CheckAttribute(pchar, "ReturnToLSC"))
				{
					if (CheckAttribute(pchar, "Ship.Cargo.Goods.Medicament") && sti(pchar.Ship.Cargo.Goods.Medicament) > 0)
					{
						link.l9 = "Padre, I have brought medicines in quantity "+pchar.Ship.Cargo.Goods.Medicament+" units";
						link.l9.go = "TradeMed";
					}
					if (CheckAttribute(pchar, "Ship.Cargo.Goods.Clothes") && sti(pchar.Ship.Cargo.Goods.Clothes) > 0)
					{
						link.l10 = "Padre, I brought clothes in quantity "+pchar.Ship.Cargo.Goods.Clothes+" units";
						link.l10.go = "TradeCloth";
					}
				}
				link.l11 = "Nothing...";
				link.l11.go = "exit";
			}
		break;

		case "FT_1":
			dialog.text = "I see, "+ GetSexPhrase("my son", "my daughter") +", that your soul is restless. For one cannot lay the blame for one's misfortunes on the Lord...";
			Link.l1 = "Holy Father, here, tell me one simple thing. We thank our Lord for all the successful turns in life, but we have no right to blame him for all the misfortunes. How is that, Padre?";
			Link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = ""+ GetSexPhrase("My son", "My daughter") +", are you sinless?";
			link.l1 = "There is no man without sin!";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "True. Our shepherd leads his flock in the midst of many nets. Tell me, do you keep his commandments?";
			link.l1 = "Um, I'd not say...";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "So why are you offended on the Lord, if He says to you: 'Do that!' Aren't you doing it? If he asks: 'Don't do that!'What are you doing?"+
				"His flock is like young sons, disobedient to their father: everyone thinks that he knows everything and about everything. Praise the Lord for the benefits that have been shown to you!";
			link.l1 = "You're right, Father. I thank our Lord for my salvation.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Okay. And don't blaspheme from now on!";
			link.l1 = "I won't, Padre.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Yes you are a thief!!! Violation of the Law of the City!", "Wow! As soon as I looked at it, you went straight into the chest with your head!", "Police! They're robbing!!! Hold him, he broke the Law!");
			link.l1 = "Ah, the devil!!!";
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = "Oh, so that's how it is?! Are you going to rummage through the chests?! Now the citizens and the police will tear you up like an old rag!";
			link.l1 = "What a fool!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Put away the weapon, "+ GetSexPhrase("my son", "my daughter") +". And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the gun away.", "Put the gun away, it doesn't suit you"+ GetSexPhrase("serious man", "girl") +"...");
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = "Who are you looking for?";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = "I don't understand who you're talking about. I need to know this person's first and last name.";
				Link.l1 = "I see. Let me try to name it again.";
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = "Thanks, I'd better look for it myself.";
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = "So it's me!";
					link.l1 = "Wow, it's right you!";
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + "are you talking about him?";
					Link.l1 = "Yes, yes, that's right, it's him.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "No, not about him. Let me name it again.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + "are you talking about her?";
					Link.l1 = "Yeah, it's about her.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "No, not about her. Let me try to name it again.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "I don't want to ask about anyone else. Goodbye.";
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = "Then tell me your first and last name again.";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;

		case "SeekCitizen_agree":
			sld = &characters[sti(npchar.quest.seekIdx)];
			npchar.quest.seekIdx.where = WhereLSCCitizen(sld);
			if (npchar.quest.seekIdx.where == "none")
			{
				if (sld.sex == "man")
				{
					dialog.text = LinkRandPhrase("I don't know, I haven't seen him for a long time.", "The devil knows where he is...", "I haven't seen him for a decent time, so I don't know.");
					link.l1 = RandPhraseSimple("I see.", "Sorry...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("I haven't seen her for quite a while, I'm sorry.", "I have no idea where she is now.", "Hmm, I don't know where she might be right now.");
					link.l1 = RandPhraseSimple("Clear.", "Sorry...");
					link.l1.go = "exit";
				}
			}
			else
			{
				if (sld.sex == "man")
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str1 = npchar.location.locator;
						string Str2 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str1, 0, 5) == strcut(Str2, 0, 5))
						{
							dialog.text = LinkRandPhrase("He's here on this ship. Look carefully.", "Ha, so he's here on this ship!", "He's on this ship, it's strange that you haven't seen him yet.");
						}
						else
						{
							dialog.text = LinkRandPhrase("I saw him quite recently at " + npchar.quest.seekIdx.where + ".", "Recently met him at " + npchar.quest.seekIdx.where + ". So look for him there.", "As far as I know, he is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("So he's here: " + npchar.quest.seekIdx.where + ". Look carefully.", "But he's here, among us!", "Where are you looking? He's hanging around here.");
						}
						else
						{
							dialog.text = LinkRandPhrase("I saw it quite recently at " + npchar.quest.seekIdx.where + ".", "Recently met him at " + npchar.quest.seekIdx.where + ". So look for him there.", "As far as I know, he is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Yeah, I see. Thank you, Holy Father.", "Thank you, Padre!");
					link.l1.go = "exit";
				}
				else
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str3 = npchar.location.locator;
						string Str4 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str3, 0, 5) == strcut(Str4, 0, 5))
						{
							dialog.text = LinkRandPhrase("She's here on this ship. Look carefully.", "Ha, so she's here on this ship!", "She's on this ship, it's strange that you haven't seen her yet.");
						}
						else
						{
							dialog.text = LinkRandPhrase("I saw her quite recently " + npchar.quest.seekIdx.where + ".", "Recently met her " + npchar.quest.seekIdx.where + ". We even talked.", "As far as I know, she is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("So she's here, " + npchar.quest.seekIdx.where + ". Look carefully.", "But she's here, among us!", "Where are you looking? She's walking around here somewhere.");
						}
						else
						{
							dialog.text = LinkRandPhrase("I saw her quite recently " + npchar.quest.seekIdx.where + ".", "Recently met her " + npchar.quest.seekIdx.where + ". We even talked to her.", "As far as I know, she is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Yeah, I see. Thank you, Holy Father.", "Thank you, Padre!");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = "I'm listening to you carefully, "+ GetSexPhrase("my son", "my daughter") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Listen, what kind of island is this?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Tell me, Padre, how did you get here?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "Tell me, Padre, have you lived here long?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "No questions asked. I'm sorry, Father...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "This is the City of Abandoned Ships. I am the only clergyman here, and my mission is to guide the citizens of the City on the right path.";
			link.l1 = "Understood.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "I followed from the Old World to preach the Word of God on the new continent among the pagans. But the Lord judged otherwise...";
			link.l1 = "Did you also survive the crash?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Alas, yes. The ways of the Lord are inscrutable.";
			link.l1 = "That's right.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "No, not very long ago.";
			link.l1 = "Understood... Do you know any old-timers?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "I don't care when a parishioner gets here. The main thing is that now all the citizens are here, in my flock.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
		break;
		//Исповедь
		case "donation":
			if (startherotype != 2 || IsEquipCharacterByItem(pchar, "glasses"))
			{
			dialog.Text = "Of course, "+ GetSexPhrase("my son", "my daughter") +". How much do you want to donate to atone for your sins?";
			Link.l1 = "I'm sorry, Father, I changed my mind. Stranded...";
			Link.l1.go = "No donation";
			Link.l2 = "Let me decide...";
			link.l2.go = "donate_input";
			}
			else
			{
				dialog.Text = "No need. Your mere appearance here is already worth more than any money.";
				Link.l1 = "As you know. Then another question...";
				Link.l1.go = "First time";

			}
		break;

		case "No donation":
			dialog.Text = "Hmm, the parishioners of the City won't be thrilled with this...";
			Link.l1 = "Well, that's fine. Excuse me, Father, I have to go.";
			Link.l1.go = "First time";
			Link.l2 = "Sorry, Holy Father, I have to go.";
			Link.l2.go = "exit";
		break;

		case "donate_input":
			dialog.Text = "Of course, "+ GetSexPhrase("my son", "my daughter") +". How much do you want to donate to atone for your sins?";
			Link.l1.edit = 1;
			link.l1 = " ";
			link.l1.go = "donation_thank_you";
		break;

		case "donation_thank_you":
			int iDonation = sti(dialogEditStrings[1]);
			if(iDonation > sti(pchar.money) || iDonation <= 0)
			{
				dialog.text = "Oh, " + GetSexPhrase("my son", "my daughter") + ", I see you don't have enough money...";
				link.l1 = "You're right, Father, I will change amount."
				link.l1.go = "donate_input";
				link.l2 = "You know, I changed my mind.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.Text = "On behalf of the Holy Church, thank you, "+ GetSexPhrase("my son", "my daughter") +", for your gift.";
				int iRepIncr = iDonation / 5000;
				ChangeCharacterReputation(pchar, iRepIncr);
				AddMoneyToCharacter(pchar, -iDonation);
				Link.l1 = "I need to talk to you, Father.";
				Link.l1.go = "First time";
				Link.l2 = "Excuse me, Father, I have to go.";
				Link.l2.go = "exit";
			}
		break;

		//достать свечки
		case "askCandles":
			dialog.text = "Yes, "+ GetSexPhrase("my son", "my daughter") +". Приход нуждается в свечах, а у нас в Городе что-то давно не был поступлений этого товара. Помоги мне, принеси 400 свечей.";
			link.l1 = "And where can I get them?";
			link.l1.go = "askCandles_1";
		break;
		case "askCandles_1":
			dialog.text = "If I knew where to get them, I would go get them myself. Look for, "+ GetSexPhrase("my son", "my daughter") +".";
			link.l1 = "Hmm... Well, all right, Holy Father, I'll look for...";
			link.l1.go = "askCandles_2";
		break;
		case "askCandles_2":
			dialog.text = "Search diligently, "+ GetSexPhrase("my son", "my daughter") +", the reward will be worthy.";
			link.l1 = "I understand, Padre. Everything will be done.";
			link.l1.go = "exit";
			npchar.quest.takeCandles = "seek";
			npchar.quest.takeCandles.Qty = 0; //кол-во свечей
			AddQuestRecord("ISS_takeCandles", "1");
		break;

		case "takeCandles":
			iTemp = GetCharacterItem(pchar, "mineral3");
			npchar.quest.takeCandles.Qty = sti(npchar.quest.takeCandles.Qty) + iTemp;
			DeleteAttribute(pchar, "items.mineral3");
			if (sti(npchar.quest.takeCandles.Qty) < 400)
			{
				dialog.text = "Well, let's see. Now you're a prin"+ GetSexPhrase("collective", "if") +" " + FindRussianQtyString(iTemp) + " candles. You're a total prin"+ GetSexPhrase("collective", "if") +" " + FindRussianQtyString(sti(npchar.quest.takeCandles.Qty)) + "candles. You have to bring more " + FindRussianQtyString(400 - sti(npchar.quest.takeCandles.Qty)) + ".";
				link.l1 = "Understood. Well, I'll keep looking, Father.";
				link.l1.go = "exit";
				AddQuestRecord("ISS_takeCandles", "2");
				AddQuestUserData("ISS_takeCandles", "iQty", 400 - sti(npchar.quest.takeCandles.Qty));
			}
			else
			{
				dialog.text = "Great, you did the task, "+ GetSexPhrase("my son", "my daughter") +". Now we have enough candles for church services for a long time.";
				link.l1 = "I'm glad that I could help the parish. Holy Father, what about the reward for your efforts?";
				link.l1.go = "takeCandles_ok";
			}
		break;
		case "takeCandles_ok":
			dialog.text = "Yes, of course, as promised. I think this book about Lady Fortune will be more useful to you than to me. Go, "+ GetSexPhrase("my son", "my daughter") +".";
			link.l1 = "Yes, Padre, thank you. Although it is unclear why...";
			link.l1.go = "exit";
			TakeNItems(pchar, "book3_6",1);
			log_info("What are you talking about, ");
			npchar.quest.takeCandles = "found";
			AddQuestRecord("ISS_takeCandles", "3");
			CloseQuestHeader("ISS_takeCandles");
		break;
		//поиск товаров на корвет не принеся свечи
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("my son"+ GetSexPhrase("my daughter", "?") +"?",
				"You already asked about this.",
				"Already asked...",
                ""+ GetSexPhrase("My son", "My daughter") +", that's enough...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I need kernels, knippels, food, gunpowder, weapons, medicines...",
				"a.",
                "Oh, yeah.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Medicines? Are you in pain?";
			link.l1 = "No, Holy Father... I need medicines, lots of medicines for people.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Hmm, I have medicines. Just to start, do me a favor, "+ GetSexPhrase("my son", "my daughter") +". I'm talking about candles.";
			link.l1 = "About candles?";
			link.l1.go = "askCandles";
		break;
		//поиск товаров на корвет не принеся свечи
		case "FSeekGoods":
			dialog.text = NPCStringReactionRepeat("How many?",
				"You already asked about this.",
				"Already asked...",
                ""+ GetSexPhrase("My son", "My daughter") +", that's enough...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("50 packs should be enough.",
				"Yes... Sorry, I forgot.",
                "Oh, yeah.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FSeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "FSeekGoods_1":
			dialog.text = "What do you need, "+ GetSexPhrase("my son", "my daughter") +"?";
			link.l1 = "Alas, Holy Father, I cannot say yet.";
			link.l1.go = "FSeekGoods_2";
		break;
		case "FSeekGoods_2":
			dialog.text = "Well, I'm not curious, because it's a sin... You can take the batch of medicines you need from me. Somewhen you helped me, now I'll help you.";
			link.l1 = "Thank you, Padre! Maybe it will be too much, but can't you arrange for these medicines to be delivered to the San Gabriel?";
			link.l1.go = "FSeekGoods_3";
		break;
		case "FSeekGoods_3":
			dialog.text = "Okay. Go in peace, "+ GetSexPhrase("my son", "my daughter") +". The parishioners will do everything.";
			link.l1 = "Thank you very much, Holy Father!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_MEDICAMENT, 50);
			AddQuestRecord("ISS_MainLine", "47");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("What's the matter, "+ GetSexPhrase("my son", "my daughter") +"?",
				"We've already talked about this.",
				"This has already been discussed, I repeat for the second time, "+ GetSexPhrase("my son", "my daughter") +".",
                "Oh, "+ GetSexPhrase("my son", "my daughter") +", you're so annoying...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I am recruiting a team for my ship and invite you to join me.",
				"Okay...",
                "As you know...",
				"Well, okay...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "Hmm, is that so? Thanks for the offer, but I can't leave the congregation of the City.";
			link.l1 = "Holy Father, there will soon be nothing left of the City.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "God willing, "+ GetSexPhrase("my son", "my daughter") +". I'm staying.";
			link.l1 = "Well, as you know, Holy Father.";
			link.l1.go = "exit";
		break;
		case "MetAgain1":
			dialog.text = "Providence of God, no other way. This place itself has decided to let you and those who decided to go with you go.";
			link.l1 = "I would write off it all down to luck, Padre, but I won't argue with you.";
			link.l1.go = "MetAgain2";
		break;
		case "MetAgain2":
			dialog.text = "Anyway, why did you decide to come back, Captain?";
			link.l1 = "Knowing that the Island is isolated and few people know about its existence, I decided to offer your services for the import of goods of the first and not very necessary. For example, medicines, food and clothes.";
			link.l1.go = "MetAgain3";
		break;
		case "MetAgain3":
			dialog.text = "That's a good idea. With food, you'd better go to our tavern on the Fleron. But medicines and clothes will not be superfluous.";
			link.l1 = "Well, now I know what I can bring you. See you later!";
			link.l1.go = "exit";
		break;
		case "TradeMed":
			dialog.text = "How much of this amount did you bring to us?";
			Link.l1.edit = 1;
			link.l1 = "";
			link.l1.go = "TradeMed2";
			link.l2 = "I need to think about it.";
			link.l2.go = "exit";
		break;
		case "TradeMed2":
			npchar.amount = GetStrSmallRegister(dialogEditStrings[1]);
			npchar.amount = func_min((sti(npchar.amount),sti(pchar.Ship.Cargo.Goods.Medicament));//фикс, нельзя продать больше, чем привёз
			npchar.amount = func_max((sti(npchar.amount),1);
			NPChar.sumtotal = sti(npchar.amount)*10;
			dialog.text = "I take medicine 10 per unit. Total, "+NPChar.sumtotal+" gold for "+npchar.amount+" units. Are you satisfied with the offer?";
			link.l1 = "Yes.";
			link.l1.go = "TradeMed3";
			link.l2 = "I need to think about it.";
			link.l2.go = "exit";
		break;
		case "TradeMed3":
			pchar.Ship.Cargo.Goods.Medicament = sti(pchar.Ship.Cargo.Goods.Medicament)-sti(npchar.amount);
			dialog.text = "Thank you, Captain!";
			AddCharacterExpToSkill(pchar, "Commerce", sti(NPChar.sumtotal) / 2000.0);
			ChangeCharacterReputation(pchar, sti(NPChar.sumtotal) / 10000.0);
			AddMoneyToCharacter(pchar, sti(NPChar.sumtotal));
			link.l1 = "Glad to help. See you later!";
			link.l1.go = "exit";
		break;
		case "TradeCloth":
			dialog.text = "How much of this amount did you bring to us?";
			Link.l1.edit = 1;
			link.l1 = "";
			link.l1.go = "TradeCloth2";
			link.l2 = "I need to think about it.";
			link.l2.go = "exit";
		break;
		case "TradeCloth2":
			npchar.amount = GetStrSmallRegister(dialogEditStrings[1]);
			npchar.amount = func_min((sti(npchar.amount),sti(pchar.Ship.Cargo.Goods.Clothes));//фикс, нельзя продать больше, чем привёз
			npchar.amount = func_max((sti(npchar.amount),1);
			NPChar.sumtotal = sti(npchar.amount)*5;
			dialog.text = "I take clothes 5 per unit. Total, "+NPChar.sumtotal+" gold for "+npchar.amount+" units. Are you satisfied with the offer?";
			link.l1 = "Yes.";
			link.l1.go = "TradeCloth3";
			link.l2 = "I need to think about it.";
			link.l2.go = "exit";
		break;
		case "TradeCloth3":
			pchar.Ship.Cargo.Goods.Clothes = sti(pchar.Ship.Cargo.Goods.Clothes)-sti(npchar.amount);
			dialog.text = "Thank you, Captain!";
			AddCharacterExpToSkill(pchar, "Commerce", sti(NPChar.sumtotal) / 2000.0);
			ChangeCharacterReputation(pchar, sti(NPChar.sumtotal) / 10000.0);
			AddMoneyToCharacter(pchar, sti(NPChar.sumtotal));
			link.l1 = "Glad to help. See you later!";
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
