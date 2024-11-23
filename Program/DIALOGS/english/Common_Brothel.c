
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1,iColony;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string iDay, iMonth, lastspeak_date;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}

	if (Dialog.CurrentNode == "SpecialExit")
	{
		LAi_SetCitizenTypeNoGroup(npchar);
		Dialog.CurrentNode = "exit";
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (PChar.sex == "woman")
			{
				npchar.greeting = "hostess_lady";
			}
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase(""+ GetSexPhrase("Dear, what kind of girls?! Half of the garrison is chasing you, and he came to the brothel!","You should get out of here... Half of the garrison is chasing you!") +"", "The entire city guard is scouring the city in search of you. I'm not an idiot, to welcome you at such a moment...", "I'll ask you to leave my place, you have nothing to do here!"),
					LinkRandPhrase(""+ GetSexPhrase("Just try to touch my girls - I'll skin you alive!","Get out of here, you bastard!") +"", "Dirty killer, get out of my place! Guards!!", "I'm not afraid of you, bastard! You'll be hanged in our fort soon, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, anxiety is not a problem for me...", "They will never catch me."),
					RandPhraseSimple("It would be better to be silent, you fool...", "Shut up, otherwise it will be worse ..."));
				link.l1.go = "exit";
				break;
			}
			//homo Линейка Блада
            if (CheckAttribute(Pchar, "questTemp.CapBloodLine") && Pchar.questTemp.CapBloodLine == true)
            {
                dialog.Text = LinkRandPhrase("Hey, Dr. Blood! " + TimeGreeting() + ".",
                                    "Glad to see you, Peter Blood.",
                                    "It's good that you looked at me, " + GetFullName(pchar) + ". How is Colonel Bishop?");
                Link.l1 = "Alas, I'm already leaving, " + NPChar.name + ". See you later.";
				Link.l1.go = "exit";
				break;
            }
			//-->> квест Кольцо Жозефины Лодет
			if (CheckAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh") && npchar.city == "SantoDomingo") 
			{
				dialog.text = "What can I do for you, " + GetAddress_Form(NPChar) + "?";
				link.l1 = "Listen, " + npchar.name + ", I want to spend time with one of your girls, I think her name is Francesca.";
				link.l1.go = "PDM_PK_UvestiNaVerh";
				break;
			}
			//<<-- квест Кольцо Жозефины Лодет
			//-->> квест пожертвования в церковь
			//результаты
			if (npchar.questChurch == "baster")
			{
				dialog.text = "You took money, but did not donate them! You bastard, in a word! I will not serve you in my establishment. Get out!";
				link.l1 = "Cough, damn it!";
				link.l1.go = "exit";
				link.l2 = "Listen, I understand that you are offended by me. I'm really sorry for you. But I want to ask you a question, and I think it's in your best interest to answer it.";
				link.l2.go = "quests";//(перессылка в файл города)
				break;
			}
			if (npchar.questChurch == "taken")
			{

				if (!CheckAttribute(pchar, "HellSpawnFinished"))
				{
					dialog.text = "You didn't give the money to the church. Get on with it, you have the current day! You promised me!";
					link.l1 = "Yes, I remember. I'm doing it.";
					link.l1.go = "exit";
					break;
				}
				else
				{
					dialog.text = "You're back...";
					link.l1 = "I really tried to help you and take the money to the church. But as it turned out, good deeds are contraindicated for people like me. As a result of my attempt, many innocent people died. Take your money, I can't help you.";
					link.l1.go = "ResultChurch_2";
					break;
				}
			}
			if (npchar.questChurch == "yes")
			{
				dialog.text = "Did you donate?";
				link.l1 = "Yes, I did everything. Padre asked me to tell you that your money has been accepted by the church.";
				link.l1.go = "ResultChurch_1";
				break;
			}
			if (npchar.questChurch == "no")
			{
				dialog.text = "Did you donate?";
				link.l1 = "Listen, " + npchar.name + " church didn't take your money. I'm giving them back to you.";
				link.l1.go = "ResultChurch_2";
				break;
			}

			//-->> дача развода на секс
			if (rand(3) == 1 && pchar.questTemp.different == "free" && PChar.sex != "woman" && GetNpcQuestPastDayWOInit(npchar, "questSex") > 180 && !CheckAttribute(npchar, "quest.selected") && !CheckAttribute(npchar, "quest.NotGoneToSex.over"))
			{
				if (!CheckAttribute(npchar, "quest.NotGoneToSex"))
				{
					dialog.text = "Oh, how boring it is in our town. Maybe a prominent captain like you will dispel my boredom?";
					link.l5 = "Absolutely! I will be happy to entertain such a beautiful lady.";
					link.l5.go = "toHostessSex";
					link.l8 = "Unfortunately, I don't have time, " + npchar.name + ". Some other time...";
					link.l8.go = "exit";
					pchar.questTemp.different = "HostessSex";
					SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
					SaveCurrentNpcQuestDateParam(npchar, "questSex");
				}
				else
				{
					dialog.text = "Last time I was waiting for you in the room upstairs, you didn't come... you missed your chance.";
					link.l1 = "Oh, it's a pity...";
					link.l1.go = "exit";
					npchar.quest.NotGoneToSex.over = true; //больше вообще не говоить
				}
				break;
			}
			//<<-- развод на секс

			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". Welcome to the house of tolerance. My name is " + npchar.name + ", I'm in charge of everything here. "+ GetSexPhrase("What can I do for you?, " + GetAddress_Form(NPChar) + "","I admit, I'm a little surprised to see you here, " + GetAddress_Form(NPChar) + ", but I can assure you: we provide services not only to men.") +"",
				                               "Welcome to my humble establishment, "+ GetSexPhrase("stranger","girl") +". Let me introduce myself, I am "+ NPChar.Name + ", owner of this shelter of men offended by affection. "+ GetSexPhrase("How can I help you?","Although we also have something for women...") +"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". What can I do for you, " + GetAddress_Form(NPChar) + "?",
				                               TimeGreeting() + ". How can I help you, " + GetAddress_Form(NPChar) + "?");
			}
			if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри
			{
				link.l2 = npchar.name + ", I want to spend time with one of your girls.";
				link.l2.go = "Hostess_1";
			}
			link.l3 = "I haven't pampered my guys for a long time. Can I make a wholesale order for the girls?";
			link.l3.go = "ForCrew";
			link.l4 = "You look worried, don't you, "+npchar.name+"?";
			link.l4.go = "works";
			link.l5 = "I have a question.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  
				}
				else
				{
					link.l4.go = "quests";
				}
			}
			else
			{
			link.l5.go = "quests";//(перессылка в файл города)
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l6 = "Listen, " + npchar.name + ", I'm looking for the governor's ring. He was partying at your place the other day, and he lost it.";
				link.l6.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			if (CheckAttribute(pchar,"drugstaken") && pchar.drugstaken >= 3)
			{
				link.l7 = "I don't feel well. It seems that the third tube was superfluous.";
				link.l7.go = "tubeheal";
			}
			link.l9 = "Nothing. I'm already leaving.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "tubeheal":
			pchar.questTemp.drugsprice = 1000*MOD_SKILL_ENEMY_RATE*3;
			dialog.text = "It looks like you really smoked some kind of rubbish, captain. Fortunately, I can help you. But it will take some time and will cost you "+pchar.questTemp.drugsprice+" piastres. So, agree?";
			if (sti(pchar.money) >= sti(pchar.questTemp.drugsprice))
			{
				link.l1 = "Anything to make it go away.";
				link.l1.go = "tubeheal_1";
			}
			link.l2 = "Probably not.";
			link.l2.go = "exit";
		break;

		case "tubeheal_1":
			AddMoneyToCharacter(pchar,-sti(pchar.questTemp.drugsprice));
			ClearDrugs();
			WasteTime(12);
			dialog.text = "Well, you look much better now. I suppose you feel great now, too?";
			link.l1 = "Definitely! Thank you very much"+GetSexPhrase("ren.","rna.");
			link.l1.go = "exit";
		break;

		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("What do you want, handsome?","I'm listening to you carefully, Captain.");
				link.l1 = "Listen, " + npchar.name + ", I found these papers in the private room of your institution...";
				link.l1.go = "ShipLetters_2";
		break;
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Let's take a look! Hm... Did some unknown captain drop the documents? I think such questions should be asked to the portmaster.";
				link.l1 = "Maybe, maybe...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Let's take a look! Oh! Judging by the name, they belong to my esteemed client and a worthy citizen of our city. I can hand over the documents myself.";
				link.l1	= "Probably not ...";
				link.l1.go = "exit";
				link.l2 = "Wonderful! Always glad to help a respected person and a decent institution.";
				link.l2.go = "ShipLetters_3";
			}
		break;

		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "2");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;


		//#20171211-02 Allow reconciling with Hostess if promised donation missed.
		case "Reconcile_1":
		    sld = GetFreeHorseRef(npchar.city);
            int nRand = rand(1) + 2;
            int nPrice = sti(sld.quest.price) * nRand;
            //string sPrice = FindRussianMoneyString(nPrice);
            pchar.quest.reconcileHostess = nPrice;
            dialog.text = strreplace("My God, I fully admit that this is my fault, but to be honest, I just got distracted and forgot about the promised donation. Is there any way to reimburse you for this?", "#thisamount", FindRussianMoneyString(nPrice));
            if (sti(pchar.money) >= nPrice)
            {
                link.l1 = "Well, I suppose so. How about you give me back #thisamount?";
                link.l1.go = "Reconcile_2";
                link.l2 = "Of course.  Here you go.";
                link.l2.go = "exit";
            }
            else
            {
                Link.l1 = "No way.";
                Link.l1.go = "exit";
            }
        break;
        case "Reconcile_2":
            AddMoneyToCharacter(pchar, -sti(pchar.quest.reconcileHostess));
            dialog.text = "Nonsense! Never mind.";
            link.l1 = "Very good, continue your business. Don't try your luck in the future.";
            link.l1.go = "exit";
            npchar.questChurch = "";
        break;
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+ GetSexPhrase("We are always glad to have a customer. Tell me, darling, have you already looked for someone or don't you care?","Well, my girls will be able to help you... to help. Have you looked for someone, or don't you care?") +"";
					Link.l1 = ""+ GetSexPhrase("Heh, I need a girl right away, and I don't care who she is. You have all of them cute...","Yes, any one, if only she knew her business...") +"";
					Link.l1.go = "Hostess_NotChoice";
					Link.l2 = "Yes, there is one, who I liked...";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "Today I can't give you a girl anymore, I still have clients besides you. Come back tomorrow, we'll serve you properly!";
					Link.l1 = "Oh, it's a pity"+ GetSexPhrase(", I just got a taste","") +"... Well, all right.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm, you've already paid the girl. So take care of her closely, so to speak, and don't distract me for nothing.";
				Link.l1 = "Okay, I'm on my way.";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			//#20171008-01 Brothel adjust changeover period
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > (BROTHEL_CHANGEDAYS - 2)) //98)
			{
				dialog.text = "I don't have any available girls right now, you'll need to come here in a couple of days.";
				Link.l1 = "Okay, whatever you say.";
				Link.l1.go = "exit";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("Well, stallion, excellent!","I have them all skilled, you can be sure.") +" I can offer a beautiful girl named " + GetFullName(sld) + ", she is free now. This pleasure will cost " + FindRussianMoneyString(sti(sld.quest.price)) + ". Agree?";
				Link.l1 = "No, I think I'll refuse. It's a little expensive...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= sti(sld.quest.price))
				{
					Link.l2 = "Of course you agree, what kind of questions can there be?!";
					Link.l2.go = "Hostess_NotChoice_agree";
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Ah, I don't have enough money right now...";
					Link.l1.go = "exit";
				}
			}
		break;
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= sti(sld.quest.price))
			{
				/*if (rand(4) == 0 && pchar.sex != "woman" && !CheckAttribute(pchar,"NoPriest") && GetCharacterSPECIALSimple(pchar, SPECIAL_L) >= 8)
				{
					dialog.text = "Great, dear, " + sld.name + " he will be waiting for you in the privacy room on the second floor. I'm sure you'll be sooo pleased...");
					Link.l1 = "Heh, well, I'm off...";
					Link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -sti(sld.quest.price));
					sld.greeting = "Gr_Church";
					sld.model = "priest_2";
					sld.model.animation = "man";
					sld.name = "Padre Pedro";
					sld.lastname = "";
					sld.Dialog.Filename = "Common_Brothel.c";
					sld.dialog.currentnode = "Priest1";
					pchar.NoPriest = true;
					pchar.PedroID = sld.id;
					pchar.quest.Pedro.win_condition.l1 = "location";
					pchar.quest.Pedro.win_condition.l1.location = npchar.city + "_Brothel_room";
					pchar.quest.Pedro.function = "Pedro_Horse";
				}
				else
				{*/
					dialog.text = "Great, dear,  " + sld.name + " will be waiting for you in the privacy room on the second floor.";
					Link.l1 = ""+ GetSexPhrase("Heh, well, I went","Well, I ran") +"...";
					Link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -sti(sld.quest.price));
					sld.dialog.currentnode = "Horse_ReadyFack";
				//}
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}

				// генератор найденных бумаг
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10)
				{
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE*3) + 1; // даём хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;

					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем
					sTemp = "_Brothel_room";
					sTemp1 = "_town";
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("The papers are in the location " + sld.startLocation + ", in the locator " + sld.startLocator + " p1 : " + p1);

					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";

					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");
				}

				// генератор - "A reason to hurry"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20)
				{
					iColony = FindColony(npchar.city);
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");
					}
				}

			}
			else
			{
				dialog.text = "Everything would be fine, but the fact is that " + sld.name + " - the girl is not cheap, it's worth it " + FindRussianMoneyString(sti(sld.quest.price)) + ". And as far as I can see, you don't have enough money. Come as soon as you get rich"+ GetSexPhrase(", native","") +"...";
				Link.l1 = "Eh, it's always like this...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "I am always glad when there are warm feelings between girls and clients... Tell me her name.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
		break;
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Hmm, you're wrong, I don't have such a girl in the institution. Perhaps you're mispronouncing her name.";
				Link.l1 = "Hmm, but I just talked to her.";
				Link.l1.go = "Hostess_Choice_2";
				Link.l2 = "Perhaps I'd better clarify her name. I'll talk to you about it later.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = GetFullName(sld) + "are you talking about her?";
				Link.l1 = "Yeah, it's about her.";
				Link.l1.go = "Hostess_NotChoice_agree";
				Link.l2 = "No, not about her.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
        case "Hostess_Choice_2":
			dialog.text = "Then you need to say her name again, maybe I'll understand who you're talking about.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Perhaps I'd better clarify her name. I'll talk to you about it later.";
			Link.l2.go = "exit";
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Hmm.. For the whole team? So, you want your guys to relax perfectly? Well, I have some highly qualified girls who can do that... You owe " + FindRussianMoneyString(GetCrewQuantity(pchar)*30) + ".";
			link.l1 = "Okay, I agree to pay this money.";
			link.l1.go = "ForCrew_1";
			link.l2 = "I think they'll manage somehow...";
			link.l2.go = "exit";
		break;

		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*30 && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*30));

	            AddCrewMorale(Pchar, 10);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "It's none of my business, of course, but it seems to me that you need to earn money for the team first, and then think about its morality.";
			    link.l1 = "Perhaps, yes...";
			    link.l1.go = "exit";
		    }
		break;
		case "Woman_FackYou":
			dialog.text = "Darling, where are you going?! Wow, seemed like a decent captain...\nWell, now you're not gonna get away with it, " + GetSexPhrase("handsome", "beauty") + ". They'll clip your wings...";
			link.l1 = "Shut up, you fool...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//просьба о пожертвовании в церкви
		case "toChurch":
			dialog.text = "You see, I run an institution that... Well, it's not quite the usual thing.";
			link.l1 = "I understand.";
			link.l1.go = "toChurch_1";
		break;
		case "toChurch_1":
			dialog.text = "Okay... But that doesn't mean that I don't think about my soul. Anyway, I want to make a donation to the church. But it's difficult for me to appear there - sidelong glances, whispering wives...";
			link.l1 = "Clear. I'll make a donation, don't worry.";
			link.l1.go = "toChurch_2";
		break;
		case "toChurch_2":
			pchar.questTemp.different.HostessChurch.money = (rand(4)+1) * 300;
			dialog.text = "Okay, take " + FindRussianMoneyString(sti(pchar.questTemp.different.HostessChurch.money)) +  " gold. Make it right now, please...";
			link.l1 = "I'll do everything right now, don't worry.";
			link.l1.go = "toChurch_3";
			link.l2 = "You know, I'm a little busy right now. I'm sorry.";
			link.l2.go = "toChurch_4";
		break;
		case "toChurch_3":
			dialog.text = "Great! Drop by my place later and tell me how it went...";
			link.l1 = "Okay.";
			link.l1.go = "exit";
			pchar.questTemp.different.HostessChurch.city = npchar.city; //город
			pchar.questTemp.different = "HostessChurch_toChurch";
			SetTimerFunction("HostessChurch_null", 0, 0, 1); //освобождаем разрешалку на миниквесты и чистим структуру
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.HostessChurch.money));
			ChangeCharacterReputation(pchar, 0.30);

			if(pchar.sex == "skeleton")
			{
				location = &locations[FindLocation(npchar.city + "_Town")];
				pchar.HellSpawnLocation = location.id;
				LocatorReloadEnterDisable(pchar.HellSpawnLocation, "reload7_back", true);
				//id Города
				//Log_Info(pchar.HellSpawnLocation);
				SaveCurrentQuestDateParam("pchar.questTemp.HellSpawn");
				pchar.quest.HellSpawn.win_condition.l1 = "locator";
				pchar.quest.HellSpawn.win_condition.l1.location = pchar.HellSpawnLocation;
				pchar.quest.HellSpawn.win_condition.l1.locator_group = "reload";
				pchar.quest.HellSpawn.win_condition.l1.locator = "reload7_back";
				pchar.quest.HellSpawn.function = "HellSpawn";
			}

		break;
		case "toChurch_4":
			dialog.text = "Sorry, very sorry...";
			link.l1 = "Some other time.";
			link.l1.go = "exit";
			pchar.questTemp.different = "free";
			DeleteAttribute(pchar, "questTemp.different.HostessChurch");
			npchar.questChurch = ""; //нулим личный флаг квеста
			ChangeCharacterReputation(pchar, -1);
		break;

		case "ResultChurch_1":
			dialog.text = "Thank God, everything is not lost for me in this life yet!.. Thank you.";
			link.l1 = "You're welcome."+ GetSexPhrase("For your sake, " + npchar.name + ", I'm ready for anything...","") +"";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 3);
			AddCharacterExpToSkill(pchar, "Sneak", 20);
			npchar.questChurch = ""; //нулим личный флаг квеста
		break;
		case "ResultChurch_2":
			if (!CheckAttribute(pchar, "HellSpawnFinished"))
			{
				dialog.text = "How did you not do it?! Oh, you couldn't persuade the holy father! And I was hoping so much...";
				link.l1 = "Sorry, but it just happened...";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
			}
			else
			{
				DeleteAttribute(pchar, "HellSpawnFinished")
				dialog.text = "Yes, I saw outside the window what a massacre was going on in the city. I never thought that my little request could lead to such a...";
				link.l1 = "Next time, it's better to think again before you ask the undead to do a good deed. That won't do any good.";
				link.l1.go = "exit";
				PChar.HellSpawn.SeekRebirth = true;
				ChangeCharacterReputation(pchar, 12);
			}


			npchar.questChurch = ""; //нулим личный флаг квеста
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
		break;
		//Квест Кольцо Жозефины Лодет
		case "PDM_PK_UvestiNaVerh":
			dialog.text = "Oh, "+ GetSexPhrase("handsome","beautiful") +", Francesca is one of the best girls of our institution. You'll have to pay 3,000 gold for it.";
			link.l1 = "Yes, of course.";
			link.l1.go = "PDM_PK_UvestiNaVerh_2";
			link.l2 = "I changed my mind.";
			link.l2.go = "exit";
		break;
		case "PDM_PK_UvestiNaVerh_2":
			if (sti(pchar.Money) >= 3000)
			{
				dialog.text = "Excellent, "+ GetSexPhrase("dear","dear") +". Francesca will be waiting for you in the privacy room on the second floor.";
				link.l1 = "Heh, I am going...";
				link.l1.go = "PDM_PK_UvestiNaVerh_3";
				AddMoneyToCharacter(pchar, -3000);
			}
			else
			{
				dialog.text = "";
				link.l1 = "Listen, I don't have enough money with me right now - but I'll bring it to you later.";
				link.l1.go = "exit";
			}
		break;
		case "PDM_PK_UvestiNaVerh_3":
			DoQuestReloadToLocation("SantoDomingo_Brothel_room", "reload", "reload1_back", "");
			sld = CharacterFromID("PDM_PK_Francheska")
			ChangeCharacterAddressGroup(sld, "SantoDomingo_Brothel_room", "goto", "goto2");
			sld.dialog.filename   = "Quest\PDM\Poteryanoe_Koltso.c";
			sld.dialog.currentnode   = "NaVerhuSFrancheska";
			chrDisableReloadToLocation = true;
			DeleteAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh");
		break;
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "I didn't find any ring.";
			link.l1 = "Are the girls yours?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		case "TakeMayorsRing_H2":
			dialog.text = "Girls too. If a client forgets or loses something, then they will definitely bring it to me. No one brought me the governor's ring.";
			link.l1 = "Understood... Or maybe someone decided to hold it after all?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		case "TakeMayorsRing_H3":
			dialog.text = "It's unlikely. Girls are allowed to keep gifts from customers, that's all.";
			link.l1 = "Understood... Thank you, " + npchar.name + ".";
			link.l1.go = "exit";
		break;
		//------- развод на секс ------------
		case "toHostessSex":
			dialog.text = "You're very sweet. So what are you going to do to amuse me?";
			link.l1 = "What?! Mm... But with what! I have the biggest one... Uh-uh... authority... among the pirates. Here.";
			link.l1.go = "toHostessSex_1";
			link.l2 = "I have a sharp eye and strong hands, and also...";
			link.l2.go = "toHostessSex_2";
			link.l3 = "Madam, I've been through so much in this world...";
			link.l3.go = "toHostessSex_3";
		break;
		case "toHostessSex_1":
			dialog.text = "Your 'authority' I'm not interested. Goodbye...";
			link.l1 = "How come...?";
			link.l1.go = "exit";
		break;
		case "toHostessSex_2":
			if (rand(1))
			{
				dialog.text = "Listen! Besides self-praise, do you know any other topics for conversation?! Tell an entertaining story, after all!";
				link.l1 = "Oh! The story. It's possible! So it was like this...";
				link.l1.go = "SpeakHistory";
			}
			else
			{
				dialog.text = "Listen! Besides self-praise, do you know any other topics for conversation?! You don't know how to entertain a woman at all...";
				link.l1 = "Hmm, there are a lot of interesting topics to talk about.";
				link.l1.go = "SpeakHistoryTwo";
			}
		break;
		case "toHostessSex_3":
			dialog.text = "Cry into the vest of some merchant in the city. And this is called a pirate?! Mm, where have the real men gone?";
			link.l1 = "That's not what I meant!";
			link.l1.go = "exit";
		break;
		//истории
		case "SpeakHistory":
			dialog.text = "I'm listening carefully...";
			if (rand(1))
			{
				link.l1 = "I have a story about how I was almost eaten by a shark. Do you want to listen?";
				link.l1.go = "SpeakHistory_1";
			}
			else
			{
				link.l1 = "Once we took a merchant, a nice catch, I'll tell you, it turned out to be in his hold! Gold and silver!!! By thunder, it was! Ha ha! And he also had nice chickens on board, so neat, shapely, we pinched them well...";
				link.l1.go = "SpeakHistory_2";
			}
		break;
		case "SpeakHistory_1":
			dialog.text = "Oh! You were attacked by a shark! How did you manage to escape?!";
			link.l1 = "Well, then, in order. Somehow we got into a complete calm, not a breeze, and the heat is terrible. We decided to take a swim to refresh ourselves a little. It's such a pleasure, I tell you, to plunge into the water after the sweltering heat. And I got so carried away with swimming and diving that I didn't hear the shouts of the watchman: '" + GetAddress_Form(PChar) + ", beware! A shark! A shark!!!'. And then I saw her! I was just diving in and noticed her silhouette underneath me. What a whopper!!! Five times bigger than me! At that moment, she turns around and walks right at me!..";
			link.l1.go = "SpeakHistory_3";
		break;
		case "SpeakHistory_2":
			dialog.text = "Enough is enough! I've had enough! You're an arrogant, narcissistic type! Get out of my sight!";
			link.l1 = "Hmm, for what?";
			link.l1.go = "exit";
		break;
		case "SpeakHistory_3":
			dialog.text = "Oh my God! And what is it?!";
			link.l1 = "I understand that my salvation is in my hands, I turn around and swim with all my might to the boat, there the guys are trying to drive away the shark with shots, but you can't drive away such a monster... I was only seven yards away from the boat, and a huge fin was already showing behind me...";
			link.l1.go = "SpeakHistory_4";
		break;
		case "SpeakHistory_4":
			dialog.text = "And you?!..";
			link.l1 = "No, not me. The cabin boy. Our brave cabin boy. He saw that I did not have time to swim to the boat, and threw me a saber.";
			link.l1.go = "SpeakHistory_5";
		break;
		case "SpeakHistory_5":
			dialog.text = "And you hacked her down! Really?! Didn't you cut down that monster?";
			link.l1 = "Well, of course I hacked it! He swung my trusty saber twice - and the terrible monster was defeated!";
			link.l1.go = "SpeakHistory_6";
			link.l2 = "No, I didn't hack it. What are you, how can you cut down such a huge thing! I was saved in a different way...";
			link.l2.go = "SpeakHistory_7";
		break;
		case "SpeakHistory_6":
			dialog.text = "Hee-hee... You're a lousy liar! Cut down a monster five times bigger than you in the water? I don't believe you, you're a braggart like everyone else! I'm not interested in you...";
			link.l1 = "The Devil!! It's a pity, however...";
			link.l1.go = "exit";
		break;
		case "SpeakHistory_7":
			dialog.text = "And how?! How did you escape?";
			link.l1 = "I barely had time to grab my saber and turn around when I saw huge jaws full of terrible teeth coming at me. And I had no choice but to stick the saber between them in the hope that the steel would withstand the powerful onslaught of the jaws! And indeed, the shark shook its muzzle and went into the depths, finally hitting me with its tail so hard that I flew to the surface! By the time the shark got rid of the saber and returned to get even with me, I was already in the boat and the guys were rowing as hard as they could to the ship... In memory of that story, I have a few scars left.";
			link.l1.go = "SpeakHistory_8";
		break;
		case "SpeakHistory_8":
			dialog.text = "Oh! Scars!.. Show me...";
			link.l1 = "I'll show you now! Now I'm going to show you this, this!..";
			link.l1.go = "SpeakHistory_9";
			link.l2 = "Show? Here?! Um, I can be rude, of course, but to undress in front of a lady, in a room where strangers can enter... I could compromise you.";
			link.l2.go = "SpeakHistory_10";
		break;
		case "SpeakHistory_9":
			dialog.text = "Ugh, ham! You have no idea how to behave with a lady! I don't want to communicate!";
			link.l1 = "Hmm, wait, what about...?";
			link.l1.go = "exit";
		break;
		case "SpeakHistory_10":
			dialog.text = "Oh, how noble you are! I even forgot for a moment which establishment I was the owner of. You're probably really a bit rude and... straightforward, but there's something attractive about you... and besides, I'm still curious to see your scars, let's go upstairs to the room, no one will bother us there... And you might want to see something there too...";
			link.l1 = "Hmm, that's how it goes!..";
			link.l1.go = "exit";
			pchar.questTemp.different.HostessSex = "toRoom";
			pchar.questTemp.different.HostessSex.city = npchar.city;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			pchar.quest.SmallQuests_free.over = "yes";
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); //возврат хозяйки на место, если ГГ не прийдет в комнату
		break;

		case "Hostess_inSexRoom":
			dialog.text = "Ah, here you are...";
			link.l1 = "That's right, my queen!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("SexWithHostess_fack");

			//pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            		AddCharacterExpToSkill(pchar, "Fencing", -50);
            		AddCharacterExpToSkill(pchar, "Pistol", -50);
            		AddCharacterHealth(pchar, 10);
		break;

		case "SpeakHistoryTwo":
			dialog.text = "For example?";
			link.l1 = "For example, it's you. Truly, an inexhaustible topic!";
			link.l1.go = "SpeakHistoryTwo_1";
		break;
		case "SpeakHistoryTwo_1":
			dialog.text = "Careful, you're walking on the edge...";
			link.l1 = "I love risk! Onslaught and pressure, that's my motto! As soon as I saw you, I knew you had to be mine! I have never seen such a charming figure before! What shapes, my God!..";
			link.l1.go = "SpeakHistoryTwo_2";
			link.l2 = "I'll be careful.";
			link.l2.go = "SpeakHistoryTwo_3";
		break;
		case "SpeakHistoryTwo_2":
			dialog.text = "I'm afraid these forms are not about you. You missed your chance, you're our pushy...";
			link.l1 = "The devil, how is that?!";
			link.l1.go = "exit";
		break;
		case "SpeakHistoryTwo_3":
			dialog.text = "Hmm, then I'm all attention...";
			link.l1 = "I have seen many women, and only now realized that, alas, not all ladies can dress as exquisitely as you. I was stupid and blind...";
			link.l1.go = "SpeakHistoryTwo_4";
		break;
		case "SpeakHistoryTwo_4":
			dialog.text = "Why is it so self-critical?";
			link.l1 = "I should have run to you right away!";
			link.l1.go = "SpeakHistoryTwo_5";
		break;
		case "SpeakHistoryTwo_5":
			dialog.text = "For what?";
			link.l1 = "To invite you upstairs, my queen!";
			link.l1.go = "SpeakHistoryTwo_6";
			link.l2 = "It took me a lot of time to understand and see this truth. The world is poor and poor without you, but when you appear, everything comes to life, the birds sing more loudly, the surf gently rustles and in the rays of the morning sun, the blossoming flowers shine with dew on the petals...";
			link.l2.go = "SpeakHistoryTwo_7";
		break;
		case "SpeakHistoryTwo_6":
			dialog.text = "That's enough! You're too arrogant. You missed your chance.";
			link.l1 = "Ah, it didn't work out...";
			link.l1.go = "exit";
		break;
		case "SpeakHistoryTwo_7":
			dialog.text = "Oh!.. And you're a romantic... and a flatterer!";
			link.l1 = "Flatterer? Not at all! I'm telling the truth. And I speak, alas, in few words. But that's because all the words evaporated at the sight of a pair of your adorable, incredibly huge...";
			link.l1.go = "SpeakHistoryTwo_8";
		break;
		case "SpeakHistoryTwo_8":
			dialog.text = "What-oh?!!";
			link.l1 = "...shining eyes.";
			link.l1.go = "SpeakHistoryTwo_9";
		break;
		case "SpeakHistoryTwo_9":
			dialog.text = "Oh! I was thinking the wrong thing. Go on, please.";
			link.l1 = "To tell you the truth, I wasn't just thinking about your eyes either...";
			link.l1.go = "SpeakHistoryTwo_10";
			link.l2 = "How could you think of something else? Of course, I only meant the eyes.";
			link.l2.go = "SpeakHistoryTwo_15";
		break;
		case "SpeakHistoryTwo_10":
			dialog.text = "Yes? And what else is it about? I'm even afraid to guess.";
			link.l1 = "About your lovely neck, and about your incredible cleavage, and it takes my breath away as soon as I think how beautiful your bust is!";
			link.l1.go = "SpeakHistoryTwo_11";
		break;
		case "SpeakHistoryTwo_11":
			dialog.text = "Insolent!..";
			link.l1 = "Maybe... And you'll probably send me away, but... Looking at your beautiful dress, I keep thinking about what's underneath. Oh, I'm sorry, I forgot...";
			link.l1.go = "SpeakHistoryTwo_12";
		break;
		case "SpeakHistoryTwo_12":
			dialog.text = "Impudent and deceitful... and...";
			link.l1 = "What?";
			link.l1.go = "SpeakHistoryTwo_13";
		break;
		case "SpeakHistoryTwo_13":
			dialog.text = "Charming rogue...";
			link.l1 = "Am I forgiven?";
			link.l1.go = "SpeakHistoryTwo_14";
		break;
		case "SpeakHistoryTwo_14":
			dialog.text = "Maybe... It's too stuffy in here, let's go upstairs, it's cooler there, and we'll continue... the conversation.";
			link.l1 = "With great pleasure!";
			link.l1.go = "exit";
			pchar.questTemp.different.HostessSex = "toRoom";
			pchar.questTemp.different.HostessSex.city = npchar.city;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			pchar.quest.SmallQuests_free.over = "yes";
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); //возврат хозяйки на место, если ГГ не прийдет в комнату
		break;

		case "SpeakHistoryTwo_15":
			dialog.text = "Yes? And I thought you were interested in the whole thing, not in individual details. Just the eyes! Don't I have anything else to look at?!";
			link.l1 = "I didn't mean it...";
			link.l1.go = "SpeakHistoryTwo_16";
		break;
		case "SpeakHistoryTwo_16":
			dialog.text = "I know what you meant! Ugly, with bulging eyes! That's what!!! Get out! You disgust me!";
			link.l1 = "What are you doing " + npchar.name + ", I had no idea!..";
			link.l1.go = "exit";
		break;
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("You'd better leave the establishment!", "The whole city guard is prowling around the city! You'd better leave...", "You've made a mistake - and come to us?! No, another time..."),
					LinkRandPhrase("Get out!!", "Dirty murderer, get out of here! Guards!!", "I'm not afraid of you, bastard! You'll be hanged in our fort soon, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, anxiety is not a problem for me...", "They will never catch me."),
					RandPhraseSimple("Heh, what a fool you are...", "Shut up, otherwise it will be worse ..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Hello, " + GetAddress_Form(NPChar) + GetSexPhrase("", ", hee-hee..") +". You need to contact the hostess of the establishment, all orders go through her.",
				"Oh, it's you again. I'm sorry, but you need to settle all the issues with the hostess first. I ask you to go to her.",
				"Listen, " + GetAddress_Form(NPChar) + GetSexPhrase(", I really hope that you are just as stubborn in other matters, and not just in conversations... ","") +"once again, I ask you to go to the hostess of the establishment.",
				"Ah, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", what are you like... persistent!",", hee-hee... You are, however, eager.") +" You need to go to the hostess of the establishment to place an order.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("As you say"+ GetSexPhrase(", beauty,", "") +", I got it.", "Oh, yeah, you're right...",
                      ""+ GetSexPhrase("You can be sure, beauty, I am stubborn and strong as a bull!","Yes, yes...") +"", ""+ GetSexPhrase("Damn it, I missed something... I'm sorry, honey.","Okay.") +"", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "And where is she?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+ GetSexPhrase("Argh, beauty, I can drown in your eyes...","You look just wonderful, baby!") +"", ""+ GetSexPhrase("You know, I haven't seen such a beautiful woman in a long time!","You know, I haven't met such a pretty girl in a long time!") +"", ""+ GetSexPhrase("Oh, honey, you are incredibly adorable.","Oh, I'm tired of all these uncouth louts... And you're just lovely!") +"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("Listen, "+ GetSexPhrase("beauty","darling") +", have you found an engagement ring here? A man lost it here...",
					"Darling, did you happen to find an engagement ring in your establishment?",
					"Listen, "+ GetSexPhrase("my fish","baby") +"Did you come across a ring here, an engagement ring?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
            //--> Голл. линейка, квест №8. базар с девокой о Библиии.
			if (pchar.questTemp.State == "SeekBible_toFFBrothel" || pchar.questTemp.State == "SeekBible_toGirl")
            {
    			if (npchar.id == "HorseGen_"+FindLocation("FortFrance_Brothel")+"_1")
				{
					if (!CheckAttribute(npchar, "quest.HolLineTalk"))
					{
						dialog.text = "Whatever he wants so"+ GetSexPhrase("oh beautiful pirate","brave girl") +", it will be fulfilled...";
    					link.l4 = "Listen, some time ago you had Jackman and the company having fun here...";
    					link.l4.go = "Step_Hol8_1";
					}
					else
					{
						dialog.text = "Did you got a thousand?";
						link.l4 = "Here's your money, tell me everything you know immediately.";
    					link.l4.go = "Step_Hol8_5";
						AddMoneyToCharacter(pchar, -1000);
					}
				}
            }
			//<-- Голл. линейка, квест №8. базар с девокой о Библиии.
			NextDiag.TempNode = "Horse_talk";
		break;
        case "Horse_1":
			dialog.text = "She is in her office, you can go to her from here through the door opposite the exit to the street, or across the street from the other side of the house. Her name is " + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + ".";
			Link.l1 = "I see, "+ GetSexPhrase("honey","darling") +"Thank you.";
			Link.l1.go = "exit";
		break;
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Oh, my God, it's so nice to hear that! Listen, I'm free now, so if you choose me, you won't regret...", "Do you really think so? I am very, very pleased... Look, I'm free now, so you can choose me."+ GetSexPhrase("I promise you a sea of love and an ocean of affection...","") +"", ""+ GetSexPhrase("Is that so?! Hmm, I will not hide it, I am flattered, it is not often that I hear such words addressed to me...","Eh, girl... how these guys got to me...") +"Listen, I'm not busy at the moment, so I suggest you choose me. I promise that you will be satisfied...");
				link.l1 = "Heh, I'm choosing you!";
				Link.l1.go = "Horse_3";
				Link.l2 = ""+ GetSexPhrase("Nah, it was just a compliment to a beautiful lady","It was just a compliment") +".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("You know what I'll tell you, my dear? I don't need empty conversations. Get busy!","Well , that's just what I needed - compliments from women!") +"", ""+ GetSexPhrase("Do you also imagine that all women love with their ears? Hmm, it's a waste... If you want me, pay the hostess of the establishment, and I don't need any chatter.","Girl, don't waste your time on empty words. If you want to do something, pay...") +"", ""+ GetSexPhrase("Another lover of sensuality... Pay and I'll be yours, but only without this gentle nonsense!","What are you doing, darling? If you want pleasure, pay, and don't engage in chatter!") +"");
				link.l1 = "Wow, what a grip!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + " draws up everything in his office. Go to her"+ GetSexPhrase(", my hero,","") +" and tell her my name - " + npchar.name + ". I'll be waiting for you...";
			Link.l1 = "I see, honey, I'll be there soon...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
        case "Horse_4":
			dialog.text = NPCStringReactionRepeat("You have already paid for the girl, she's waiting for you, come upstairs.",
				"I told you to go up to her.",
				"Listen carefully, I repeat once again - go up to her...",
				"It's useless to talk, it doesn't reach...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes, I know.", "I remember.",
                      "You don't have to repeat it, I remember about her.", "Hmm, what are you talking about..", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("I don't understand you."+ GetSexPhrase(" Sometimes you compliment, then suddenly you back down. A strange type...","") +"",
					"With your compliments again? Hmm, go to the hostess, decide everything with her.",
					"Hmm, aren't you tired of it? I told you to go to the hostess of the establishment.",
					"We can't insult customers here, but you're running into it...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("It just happened, you know...", "Okay, I'll do it.",
						"Yes, yes, I got it...", "Hmm, sorry, dear.", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Thanks for the compliment. If you want to take me, then go to the owner of the establishment. Everything is as usual...";
				Link.l1 = "I see.";
				Link.l1.go = "exit";
			}
		break;
        case "HorseChoice_1":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Honey, we've talked it all out.","") +"Don't keep me waiting too long...",
						""+ GetSexPhrase("Hmm, listen, honey, to me","To me") +"all your words are very pleasant, but it's time to get down to business...",
						"Listen, can you still sort things out with the hostess?",
						"No way in the world!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Absolutely!", "Yes, of course!",
							"I'm running, I'm running to the hostess...",  npchar, Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "I was waiting for you, but you didn't fuck me! I can't say that I'm thrilled about it...";
					Link.l1 = "Um, it just so happened...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Ahh, it's you again, "+ GetSexPhrase("brave corsair","beautifull girl") +"! If you need me again, then go to the hostess - you won't regret it..."+ GetSexPhrase("By the way, I recognized you, dear, but we have to address all clients as standard, I'm sorry...","") +"";
				Link.l1 = "Wait for me just a little bit, "+ GetSexPhrase("beauty","cutie") +"and we'll leave again.";
				Link.l1.go = "exit";
				Link.l2 = "I'm very pleased that you remembered me, but unfortunately I can't spend the night with you right now.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
        case "HorseChoice_2":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("That's what, "+ GetSexPhrase("dear friend,","") +" you'd better get busy. It will be more useful than prattle.",
					""+ GetSexPhrase("Hmm, you're weird,","Well, what are you") +"you're saying the same thing...",
					"Listen, will you stop already?!",
					"Hmm, well, wow, nothing new"+ GetSexPhrase(", again stupid attempts to charm. If you want to sleep with me, go to the hostess of the establishment, you idiot!","...") +"", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Yes, I heard...", "Hmm, that's how it comes out...",
						"Hmm, maybe that's enough, maybe not...", "Be careful with expressions"+ GetSexPhrase(", goat","") +"...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ah, it's you again! "+ GetSexPhrase(" And again with silly eulogies, nothing changes in this world... ","I remind you, ") +" if you want to "+ GetSexPhrase("sleep together","mess around") +", pay the hostess of the establishment, and I don't care about your words...";
				Link.l1 = "Heh, who would doubt...";
				Link.l1.go = "exit";
			}
		break;
        case "HorseChoice_1_Add":
			dialog.text = "Hmm, I can't say that I was happy about it... It's a pity.";
			Link.l1 = "I'm sorry...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		//===>> секс
		case "Priest1":
			chrDisableReloadToLocation = true;
			dialog.text = "Greetings, my son. Come on, come closer...";
			Link.l1 = "What the fuck is going on? No, don't come near...";
			Link.l1.go = "SpecialExit";
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			if(CheckAttribute(PChar, "chr_ai.HeavyTrauma"))//лечение травмы в борделе - Gregg
			{
				DeleteAttribute(PChar, "chr_ai.TraumaQ");
				DeleteAttribute(PChar, "chr_ai.HeavyTrauma");
				Log_Info("You have recovered from a severe injury");
				CheckAndSetOverloadMode(pchar);
			}
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счётчик
			NextDiag.TempNode = "Priest2";
			AddDialogExitQuest("PlaySex_1");

			/// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Luck", 500);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

		case "Priest2":
			dialog.text = "Did you like it? You are a real lucky man, you are the first one whom I have baptized with my dignity, you can go and do any business, and God will forgive you.";
			Link.l1 = "There are just no words, Padre...";
			Link.l1.go = "exit_2";
			NextDiag.TempNode = "Priest3";
		break;

		case "Priest3":
			dialog.text = "That's enough for today. You can leave in peace.";
			Link.l1 = "Fucked up...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Priest3";
		break;

        case "Horse_ReadyFack":
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("Very glad to see you in the privacy room. "+ GetSexPhrase("And what are we going to do next?","Well, are we going to have fun?") +"", "Come on in, don't be shy"+ GetSexPhrase(", make yourself at home for the next two hours.",". I can handle you... entertain, don't worry.") +"");
					Link.l1 = RandPhraseSimple("We won't be bored, I guess...", ""+ GetSexPhrase("Let's have fun, baby!","Let's not waste time!") +"");
				break;
				case "1":
					dialog.text = "Ah, here you are, "+ GetSexPhrase("myy glorious corsair! I promised you something and I'm ready to keep my word,","my nice girl! You will never forget the next two hours") +"...";
					Link.l1 = "Wow, how tempting it sounds...";
				break;
				case "2":
					dialog.text = "You're here finally. Well, let's not waste any time!";
					Link.l1 = ""+ GetSexPhrase("Let's not, pussy...","Well, show me what you can...") +"";
				break;
			}
			Link.l1.go = "exit";
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			if(CheckAttribute(PChar, "chr_ai.HeavyTrauma"))//лечение травмы в борделе - Gregg
			{
				DeleteAttribute(PChar, "chr_ai.TraumaQ");
				DeleteAttribute(PChar, "chr_ai.HeavyTrauma");
				Log_Info("You have recovered from a severe injury");
				CheckAndSetOverloadMode(pchar);
			}
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счётчик
			NextDiag.TempNode = "Horse_AfterSex";
			AddDialogExitQuest("PlaySex_1");

			/// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "Captain, why are you not talkative?";
				link.l1 = LinkRandPhrase("Really...", "Next time we'll chat.", RandPhraseSimple("I'm not paying you to talk.", "But you, "+ GetSexPhrase("pretty woman","darling") +", you were singing like a nightingale."));
				link.l1.go = "exit";
				link.l2 = ""+ GetSexPhrase("You were so good that I was speechless with delight! A rare woman combines so much beauty and temperament","Oh, you still know how to please a woman... I am delighted.") +".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Did you like it?", "Well, what do you say? Is everything okay?", "How are you, "+ GetSexPhrase("corsair, everything"," everything") +"is it okay?");
						Link.l1 = RandPhraseSimple(""+ GetSexPhrase("Of course it's okay,","And you really are... Can you") +".", ""+ GetSexPhrase("Everything is fine, baby","You know, I'm quite happy") +".");
						Link.l1.go = "exit";
					break;
					case "1":

						if (sti(npchar.quest.sexHappend) > (rand(4)+5) && sti(pchar.questTemp.HorseLoot) < 3 && !CheckAttribute(npchar, "questTemp.HorseLoot"))
						{
							dialog.text = "Listen, you've been coming to me for a long time, I've become so attached to you...";
							Link.l1 = "Yes, and I'm coming to you too, why...";
							Link.l1.go = "HorseQuest";
						}
						else
						{
							dialog.text = LinkRandPhrase("Well, did I fulfill my promise?", "Well, how"+ GetSexPhrase("did you like me","did you like me") +"?", "I hope"+ GetSexPhrase("are you satisfied because I very pleased,","you are pleased. I tried my best") +"...");
							Link.l1 = RandPhraseSimple("Yes, I really liked everything.", ""+ GetSexPhrase("We had a great time, you were on top!","Everything was just wonderful!") +"");
							Link.l1.go = "exit";
						}
					break;
					case "2":
						dialog.text = RandPhraseSimple("Well, it's time for you.", "Time's up, "+ GetSexPhrase("corsair,","") +"it's time for you to go out.");
						Link.l1 = RandPhraseSimple("Yeah, bye...", "Goodbye and thank you...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}
		break;
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "Well, how did you like it here?";
				link.l1 = "Listen, pretty girl, have you seen a valise somewhere here?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Come visit us again sometime...", "Goodbye and see you again...", "We will be glad to see you again...");
				Link.l1 = "Okay...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}
		break;

		case "EncGirl_GetBag":
			dialog.text = "Is this a brown chest with a handle?";
			link.l1 = "Yes, something like that...";
			link.l1.go = "EncGirl_GetBag1";
		break;

		case "EncGirl_GetBag1":
			dialog.text = "Since the owner of this chest was not found, Madame took it to her boudoir.";
			link.l1 = "Thanks, baby. Goodbye.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		//==> квест на лут
        case "HorseQuest":
			pchar.questTemp.HorseLoot = sti(pchar.questTemp.HorseLoot) + 1;
			npchar.questTemp.HorseLoot = true; //уже давала
			dialog.text = "You know what, I want to tell you something, maybe it will help you...";
			Link.l1 = "Hmm, say"+ GetSexPhrase(", darling",", I'm listening to you") +".";
			Link.l1.go = "HorseQuest_1";
		break;
        case "HorseQuest_1":
			dialog.text = "Recently, one of my clients was very drunk. So, he was talking about a treasure on the coast of Main, he promised to make money...";
			Link.l1 = "Maybe it's just drunken chatter.";
			Link.l1.go = "HorseQuest_2";
		break;
        case "HorseQuest_2":
			dialog.text = "Maybe so. Although I don't think he remembered anything afterwards, so his tongue loosened against his will.";
			Link.l1 = "Did he say anything about a specific location?";
			Link.l1.go = "HorseQuest_3";
		break;
        case "HorseQuest_3":
			sTemp = LinkRandPhrase("Shore55", "Shore9", "Shore_ship2");
			if (sTemp == "Shore55")
			{
				str = "San Juan del Norte Bay";
				str1 = "box" + (rand(1)+1);
			}
			if (sTemp == "Shore9")
			{
				str = "Amatike Bay";
				str1 = "box1";
			}
			if (sTemp == "Shore_ship2")
			{
				str = "the Gulf of Doom, near Belize";
				str1 = "box2";
			}
         	pchar.GenQuestBox.(sTemp) = true;
			switch (pchar.questTemp.HorseLoot)
			{
				case "1":
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass2 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry1 = 4;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry5 = 6;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry10 = 2;
					pchar.GenQuestBox.(sTemp).(str1).items.indian11 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 15000;
				break;
				case "2":
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass3 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry14 = 3;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry16 = 2;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry18 = 4;
					pchar.GenQuestBox.(sTemp).(str1).items.indian17 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 19000;
				break;
				case "3":
					pchar.GenQuestBox.(sTemp).(str1).items.indian20 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian5 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian10 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass4 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian19 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 24000;
				break;
			}
			dialog.text = "He was self talking about " + str + ".";
			Link.l1 = "Well, thank you for the information. If I get ready sometime, I'll check this place out.";
			Link.l1.go = "exit";
		break;

		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "Then come back, I will always be glad to see you... You're so"+ GetSexPhrase("oh honey, not like the others","oh honey, not like these guys") +" - neither hello, nor goodbye, and even try to offend...";
			link.l1 = "What are you talking about?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;

		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "Yes, there was a guard sergeant in front of you. He doesn't actually come to us, but here he brought a hard one. He also chose me... He fussed and fussed, then called me an incompetent and hurried into some kind of bay. He ran away so fast, he almost left his trousers, ha ha ha...";
			link.l1 = "Don't you know, "+ GetSexPhrase("beautiful","dear") +" what kind of men are there? He told his wife that he had gone to a brothel, his mistress that he was in a hurry to see his wife, and he went to the bay to patrol. "+ GetSexPhrase("Ho-ho-ho-ho!..","Ha-ha-ha!") +"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;

		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "") {
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// <-- генератор "A reason to hurry"

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Exit_2":
			AddSimpleRumour("Do you know what I heard? It's mind-boggling! The father of our church decided to switch to the dark side and engaged in sex with a very influential and famous person throughout the archipelago.", sti(npchar.nation), 10, 1);
			npchar.lifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "", "", "", "OpenTheDoors_Priest", -1);
			chrDisableReloadToLocation = true;
			DialogExit();
		break;
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("No, "+ GetSexPhrase("dear","dear") +", unfortunately, I did not come across it. I would be glad to help, but I can't...",
					"No, "+ GetSexPhrase("handsome","girl") +"I haven't seen the ring...",
					"Unfortunately, no. I didn't see any ring.");
				link.l1 = "Sorry... Well, thank you.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "Is it the governor's ring you mean?";
					link.l1 = "Exactly, baby!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("No, "+ GetSexPhrase("dear","dear") +", unfortunately, I did not come across it. I would be glad to help, but I can't...",
						"No, "+ GetSexPhrase("handsome","girl") +"I haven't seen the ring...",
						"Unfortunately, no. I didn't see any ring.");
					link.l1 = "Sorry... Well, thank you.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "Sorry, but the ring was given to me! So I don't have to return it.";
			link.l1 = "Donated?! By whom?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		case "TakeMayorsRing_S3":
			dialog.text = "By the governor himself, of course!";
			link.l1 = "So he was a little sad, to put it mildly. He doesn't remember anything at all.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		case "TakeMayorsRing_S4":
			dialog.text = "Well, what do I have to do with it? If he wasn't out of his mind, then that's his problem!";
			link.l1 = "Listen, darling, this is the governor. Why would you quarrel with him? It's an engagement ring, you know... Give it back, don't make trouble for yourself over such a small thing.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "I will give you the ring, only you will pay me five thousand piastres.";
				link.l1 = "Okay, take your money and give me the ring.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Hmm, okay. Let him take it away!..";
				link.l1 = "Absolutely, darling!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		case "TakeMayorsRing_S6":
			dialog.text = "Please...";
			link.l1 = "Well, great. Thanks for the help, darling.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
//********************************* Диалоги девки из борделя ФФ **********************************
  		case "Step_Hol8_1":
			dialog.text = "So what?";
			link.l1 = "I heard that one of the pirates, offered some kind of book for sale, like a Bible...";
			link.l1.go = "Step_Hol8_2";
		break;
  		case "Step_Hol8_2":
			dialog.text = "It was like that, I remember... Listen, "+ GetSexPhrase("handsome, let's go upstairs","girl, pay me -") +" and I will answer all your questions. It will only cost you 1000 coins...";
			link.l1 = ""+ GetSexPhrase("I just need to know something...","Do you do anything for free at all?") +"";
			link.l1.go = "Step_Hol8_3";
		break;
  		case "Step_Hol8_3":
			dialog.text = ""+ GetSexPhrase("Okay, I'll answer any of your questions. But only upstairs - this is not the place to talk.","Hee hee hee... You need information, I need money. If you want, I can give you not only information, but also something else if we go upstairs... I know you. Only it will be more expensive, hee-hee...") +"";
			link.l1 = ""+ GetSexPhrase("Ah, I don't have time...","I don't have time for nonsense.") +"";
			link.l1.go = "Step_Hol8_4";
		break;
  		case "Step_Hol8_4":
			dialog.text = ""+ GetSexPhrase("Oh, the man was afraid of a woman's affection!!!","Oh, come on... Give me a thousand - I'll tell you everything I know.") +"";
            if (sti(pchar.money) >= 1000)
            {
    			link.l1 = "Here's your money, but tell me what you know here and now.";
    			link.l1.go = "Step_Hol8_5";
                AddMoneyToCharacter(pchar, -1000);
            }
            else
            {
    			link.l1 = ""+ GetSexPhrase("I wasn't afraid of anything, there's just no money...","") +"I'll come to you as soon as I get a thousand...";
    			link.l1.go = "exit";
				npchar.quest.HolLineTalk = true;
            }
			NextDiag.TempNode = "Horse_talk";
		break;
		case "Step_Hol8_5":
			dialog.text = "Laurent de Graaf said then that he could sell a rare book, like the Bible.";
			link.l1 = "Hmm, so what?";
			link.l1.go = "Step_Hol8_6";
		break;
		case "Step_Hol8_6":
			dialog.text = "They turned it over in their hands. The crucifix is stamped on the cover, and it's impossible to understand what kind of book it is. It was written in an unfamiliar language, no one could even say roughly what kind of writing it was.";
			link.l1 = "Hmm, since it's for sale, then I would like to buy it. How can I find this corsair?";
			link.l1.go = "Step_Hol8_7";
    	break;
		case "Step_Hol8_7":
			dialog.text = "Go straight to Tortuga, that's where you'll find it. As I said, his name is Laurent de Graf, he is a famous filibuster, a Dutchman.";
			link.l1 = "Thanks, I'll go there.";
			link.l1.go = "Step_Hol8_8";
    	break;
		case "Step_Hol8_8":
			dialog.text = "Listen, is this book really worth the money?";
			link.l1 = "It's hard to say, it's necessary to watch. And what did de Graaf say? Where did you find out what he knows about the book?";
			link.l1.go = "Step_Hol8_9";
    	break;
		case "Step_Hol8_9":
			dialog.text = "Nothing special, no one really listened to him. It was not up to that, certainly not up to the Bible...";
			link.l1 = "Clear. Thank you, I'll go look for de Graf.";
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "4");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.State = "SeekBible_toTavern";
			NextDiag.TempNode = "Horse_talk";
    	break;
		//Даёт работу здесь Хозяйка
		case "works":
			//-->> дача квеста пожертвования в церковь
			if (rand(2) == 1 && pchar.questTemp.different == "free" && NPChar.GenQuest.BrothelQuest.GiveQuestDay != lastspeak_date && GetNpcQuestPastDayWOInit(npchar, "questChurch") > 45 && GetHour() < 20)
			{
				dialog.text = "Listen, I have a favor to ask...";
				link.l1 = "Listening carefully.";
				link.l1.go = "toChurch";
				//личные флаги хозяйки на взятие квеста
				npchar.questChurch = "taken";
				SaveCurrentNpcQuestDateParam(npchar, "questChurch");
				break;
			}
			//<<-- квест пожертвования в церковь
			dialog.text = "We're fine. Thank you for your concern.";
			link.l9 = "If it's all right, I'll go about my business.";
			link.l9.go = "exit";
			NPChar.GenQuest.BrothelQuest.GiveQuestDay = lastspeak_date;		// Если не дала сегодня, то токо на след день.
		break;
	}
}


ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(GetFullName(rCharacter));
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
