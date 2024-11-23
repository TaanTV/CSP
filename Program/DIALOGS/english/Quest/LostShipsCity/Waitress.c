
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = "I don't want to talk to you! You attacked citizens!!";
				link.l1 = "As you know..."
				link.l1.go = "exit";
				break;
			}
			//после завала Хилла Брюннера
			if (pchar.questTemp.LSC == "barmenIsDead")
			{
				dialog.Text = "Ah, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +", do you already know about our misfortune?";
				link.l4 = "About what misfortune? What happened?";
				link.l4.go = "NB_1";
				pchar.questTemp.LSC = "barmenIsDeadYouKnow";
				break;
			}
			if (pchar.questTemp.LSC == "barmenIsDeadYouKnow" || pchar.questTemp.LSC == "toArmo_BrunnerDead")
			{
				dialog.Text = "Ah, "+ GetSexPhrase("monsieur captain", "mademoiselle") +", what a nightmare! What a horror!!";
				link.l4 = "Yes, Armo, I'm aware. It's a pity for Hill, it's a pity...";
				link.l4.go = "NBB_1";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.Text = "Yes, yes, I know you! This storm destroyed your ship. Well, that's your fate, and now it's joined with ours! We are all imprisoned on this island...";
					Link.l1 = "Yes, I noticed...";
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.Text = "Yes, yes, I know you! It was your ship that sank here last. Well, that's your fate, and now it's joined with ours! We are all imprisoned on this island...";
					Link.l1 = "Yes, I noticed...";
					Link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "What did you want, "+ GetSexPhrase("Monsieur Captain", "mademoiselle") +"?";
				Link.l1 = "I want to ask you a few questions, " + npchar.name + ".";
				Link.l1.go = "int_quests";
				link.l10 = "Oh, nothing, actually...";
				link.l10.go = "exit";
				//рассказываем ей о том, что, возможно, за убийством Хилла стоят касперы
				if (pchar.questTemp.LSC == "toSeekMechanik" && !CheckAttribute(pchar, "questTemp.LSC.Armo"))
				{
					link.l4 = "Listen, Armo, I have some thoughts about Hill's death.";
					link.l4.go = "AboutCasper_1";
				}
				//наводка на первого
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 0)
				{
					link.l4 = "Armo, is there any news on the first date?";
					link.l4.go = "Casper1";
				}
				//ждём втогого
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 2 && CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "Armo, I want to tell you that my first date was a success...";
					link.l4.go = "WaitCasper1";
				}
				//наводка на второго
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 2 && !CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "Armo, is there any news on the second date?";
					link.l4.go = "Casper2";
				}
				//ждём третьего
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 4 && CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "Armo, the second one is ready.";
					link.l4.go = "WaitCasper2";
				}
				//наводка на третьего
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 4 && !CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "Armo, is there any news on the third date?";
					link.l4.go = "Casper3";
				}
                //опоздал или упустил вызванного каспера
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 11 && npchar.name == "Armo")
				{
					link.l4 = "Armo, I'm sorry, but I think I'm late for a date after all.";
					link.l4.go = "CasperLate";
				}
                //опоздал или упустил вызванного каспера
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 15 && npchar.name == "Armo")
				{
					link.l4 = "Armo, it turned out like this...";
					link.l4.go = "CasperAllFight";
				}
				if (pchar.questTemp.LSC == "seekMillionAndHalf" && npchar.name == "Armo" && !CheckAttribute(npchar, "quest.giveMoney"))
				{
					link.l4 = "Listen, Armo, I'm in financial trouble here...";
					link.l4.go = "askMoney";
				}
				//освобождение мужа Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toWaitress")
				{
					link.l5 = "Do you remember the night Maxim Taylor was drinking at your place?" + npchar.name + "";
					link.l5.go = "ELTHusb_SF";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Listen, you don't know where you can get some goods.";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Listen, we have a serious conversation. I'm recruiting a team to leave here on the ship.";
					link.l8.go = "SeekCrew";
				}
			}
		break;
		case "FT_1":
			dialog.text = "Well, let's get acquainted. My name is " + GetFullName(npchar) + ". And you?";
			link.l1 = "My name is " + GetFullName(pchar) + ". I'm the captain... K-heh, ex-captain...";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "So you are the captain of the ship that sank?! I can imagine how your conscience torments you for the death of your people. Oh, I'm so sorry, I'm sorry...";
			link.l1 = "Yes, no problem, actually..";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "I will call you "+ GetSexPhrase("'monsieur capitan'", "just 'mademoiselle'") +"! Do you mind?";
			link.l1 = "I don't mind, " + npchar.name + ". Call me what you want...";
			link.l1.go = "exit";
		break;
		//вопросы
		case "int_quests":
			dialog.text = "Ask, Captain.";
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "It's kind of uncomfortable here, don't you think? It's still stormy here...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Don't you want to get out of here?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "Listen, what kind of clans are thriving here? I mean 'narwhals' and 'Casper'.";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "Listen, I still can't really get my bearings in the City. Where would I get some kind of map, or something...";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6") && CheckActiveQuest("LSC_findDekster"))
			{
				link.l6 = "Listen, " + npchar.name ", do you know anything about Leighton Dexter?";
				link.l6.go = "ansewer_6";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l7") && CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "over" && npchar.name == "Armo")
			{
				link.l7 = "I've heard you're dating Thomas Boyle?";
				link.l7.go = "ansewer_7";
			}
			link.l10 = "You know, I forgot what I wanted to ask. Sorry for distracting you...";
			link.l10.go = "exit";
		break;
		case "ansewer_3":
			dialog.text = "Stormy, yes... But you are sailor, you are used to it.";
			link.l1 = "Yes, but still... It's kind of gloomy.";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Don't lose heart, it happens to everyone who gets here. Everything will work out, the main thing is not to do anything stupid.";
			link.l1 = "Nonsense?";
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = "Don't quarrel with the admiral, follow the Law - and everything will be fine.";
			link.l1 = "Understood... Thanks for the support.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = "Just like everything here. Our ship sank, I managed to swim out. In general, you know, very few people swim out from the ships that go to the bottom. There's a strange current here, or something... In general, I don't know, but the fact, as they say, is obvious.";
			link.l1 = "Clear...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Hee hee, everyone wants to get out of here. Only it's impossible.";
			link.l1 = "Are you sure?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Yes, unfortunately. Ships come only here, no one sails from here anymore. And building new ships is prohibited by law.";
			link.l1 = "Understood.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = "Hmm... I'm going to tell you one very simple thing, and I hope you'll remember it properly. Don't mess with them!!";
			link.l1 = "What's the matter?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "The fact is that you will simply be killed. It used to happen more than once with the new ones, so do not repeat the mistakes of your predecessors. It will be very unpleasant for me to see your corpse floating overboard.";
			link.l1 = "Thanks, I'll take it into account.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_5":
			dialog.text = "Map? Eric Yorst has one! This is the owner of the store.";
			link.l1 = "Where is the store located?";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "On the galleon 'Esmeralda', "+ GetSexPhrase("Monsieur captain", "mademoiselle") +".";
			link.l1 = "I understand. Thank you so much, " + npchar.name + ".";
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = ""+ GetSexPhrase("Monsieur captain", "Mademoiselle") +", I don't know anything about Leighton Dexter. I don't want to know.";
			link.l1 = "Hmm, well, I'm sorry...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_7":
			dialog.text = "Yes, it is. And why do you ask, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +"?";
			link.l1 = "Just like that... Glad for you!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l7 = true;
		break;
		//смерть Брюннера
		case "NB_1":
			dialog.text = "Hill Brunner was killed!!";
			link.l1 = "What?! It can't be!..";
			link.l1.go = "NB_2";
		break;
		case "NB_2":
			dialog.text = "Yes, that's right! God, I still can't get away from this nightmare.";
			link.l1 = "Armo, tell me how it happened.";
			link.l1.go = "NB_3";
		break;
		case "NBB_1":
			dialog.text = "Oh, my God, I've worked for him for so long! What a good man he was!";
			link.l1 = "Yes, that's for sure... Armo, tell me how it happened.";
			link.l1.go = "NB_3";
		break;
		case "NB_3":
			dialog.text = "Oh, it's terrible! I can't remember it without shuddering...";
			link.l1 = "Armo, I'm asking you to pull yourself together and tell me how it was.";
			link.l1.go = "NB_4";
		break;
		case "NB_4":
			dialog.text = "Now... By midnight, Hill was going to the cellar. When he stayed there for more than two hours, I went there to hurry him up, as I had to serve the customers. And I found him there...";
			link.l1 = "Was he really dead?";
			link.l1.go = "NB_5";
		break;
		case "NB_5":
			dialog.text = "Yes, his skull was split open. Oh, I can't remember this without crying...";
			link.l1 = "Listen, have you seen anyone around? Coming out of the cellar, for example...";
			link.l1.go = "NB_6";
		break;
		case "NB_6":
			dialog.text = "No, no one.";
			link.l1 = "A thousand devils! It's completely unclear... listen, did he say anything to you before he died? Well, remember some details...";
			link.l1.go = "NB_7";
		break;
		case "NB_7":
			dialog.text = "Um, I don't know if this will be useful to you, but he asked me if I knew any of the citizens who lived here before him.";
			link.l1 = "And what did you say?";
			link.l1.go = "NB_8";
		break;
		case "NB_8":
			dialog.text = "I replied that I didn't know. And then he asked if I had heard in the conversations of the visitors about some kind of mechanic...";
			link.l1 = "And what did you say?";
			link.l1.go = "NB_9";
		break;
		case "NB_9":
			dialog.text = "What I didn't hear.";
			link.l1 = "Is this really true?";
			link.l1.go = "NB_10";
		break;
		case "NB_10":
			dialog.text = "Of course! Why would I lie to my boss?!";
			link.l1 = "Yes, indeed... Well, thank you, Armo.";
			link.l1.go = "NB_11";
		break;
		case "NB_11":
			dialog.text = "For what?";
			link.l1 = "For being such a good girl.";
			link.l1.go = "NB_12";
		break;
		case "NB_12":
			dialog.text = "Hmm... You know, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +", I'm not joking right now.";
			link.l1 = "I'm not kidding... Okay, Armo, don't be sad. Life is such a thing - people die...";
			link.l1.go = "NB_13";
		break;
		case "NB_13":
			dialog.text = "It's good if by your death!.. "+ GetSexPhrase("Monsieur captain", "Mademoiselle") +", promise me that if you find out anything about this case, then let me know.";
			link.l1 = "I promise, Armo.";
			link.l1.go = "NB_14";
		break;
		case "NB_14":
			dialog.text = "Thank you. I'd really like to know who did this. This scoundrel has no right to live!";
			link.l1 = "Yes, yes, I agree with you...";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toAdmiralBarmenDead";
			npchar.quest.meeting = "1";
			if (CheckAttribute(pchar, "questTemp.LSC.knowMechanic"))
			{
				AddQuestRecord("ISS_MainLine", "26");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("mu", "y"));
				DeleteAttribute(pchar, "questTemp.LSC.knowMechanic");
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "25");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("xia", "as"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("moo", "oh"));
			}
		break;

		case "AboutCasper_1":
			dialog.text = "Speak, "+ GetSexPhrase("monsieur captain", "mademoiselle") +".";
			link.l1 = "It looks like the Casper clan is behind this.";
			link.l1.go = "AboutCasper_2";
		break;
		case "AboutCasper_2":
			dialog.text = "Are you sure?";
			link.l1 = "Yes, I'm sure. I went to the admiral, asked him questions about the investigation of Hill's murder, wanted  help. As a result, I was told not to dig in this case. Bluntly and frankly.";
			link.l1.go = "AboutCasper_3";
		break;
		case "AboutCasper_3":
			dialog.text = "What does 'casper' have to do with it?";
			link.l1 = "As it turned out, they are closely related to the Admiral. It's very cramped... And apparently the admiral is covering for them now.";
			link.l1.go = "AboutCasper_4";
		break;
		case "AboutCasper_4":
			dialog.text = "Clear... I want to avenge Hill.";
			link.l1 = "I'm going to join the fight with the Casper clan.";
			link.l1.go = "AboutCasper_5";
		break;
		case "AboutCasper_5":
			dialog.text = "Are you going to do this with "+ GetSexPhrase("in", "on") +"?";
			link.l1 = "Well, yes. The Admiral won't help me this time.";
			link.l1.go = "AboutCasper_6";
		break;
		case "AboutCasper_6":
			dialog.text = "They will kill you. There is no doubt about it, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +".";
			link.l1 = "Well, we'll see about that...";
			link.l1.go = "AboutCasper_7";
		break;
		case "AboutCasper_7":
			dialog.text = "Here's what, I know how I can help you. The fact is that I carry food for these bastards on the San Gabriel. There are plenty of my fans there. I'll date them, and you'll deal with them one-on-one.";
			link.l1 = "Ho! Not a bad idea...";
			link.l1.go = "AboutCasper_8";
		break;
		case "AboutCasper_8":
			dialog.text = "Where will it be convenient for you to hold these meetings?";
			link.l1 = "Hmm, I don't know. Actually, I don't care where to meet with "+ GetSexPhrase("man", "enemy") +"...";
			link.l1.go = "AboutCasper_9";
		break;
		case "AboutCasper_9":
			dialog.text = "Hee-hee, well said... Come here tomorrow, I'll tell you what time the date is.";
			link.l1 = "Okay, Armo. Thank you.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "33");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "la"));
			pchar.questTemp.LSC.Armo = 0; //флаг на мочилово касперов. чётные - готовность Армо, нечётные - флаг questAction
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//первый каспер
		case "Casper1":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = "Today, at midnight, a casper named Denis Hopfer will seek my favor on the quarterdeck of the Ceres Smithy fluyt. Be careful, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +", if you attack the Hopper too close to the San Gabriel, then the sounds of the fight can be heard by the rest of the bandits, and then you are finished.";
				link.l1 = "I understand, Armo.";
				link.l1.go = "Casper1_1";
			}
			else
			{
				dialog.text = "Not yet, wait.";
				link.l1 = "Understood.";
				link.l1.go = "exit";
			}
		break;
		case "Casper1_1":
			dialog.text = "Please don't be late for a date, it would be indecent of you...";
			link.l1 = ""+ GetSexPhrase("Hehe, that's right. I'll be on the spot like a bayonet at midnight!", "Yes, decent girls are not late. I'll be on time, don't doubt it.") +"";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 1; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_MainLine", "34");
		break;

		case "WaitCasper1":
			dialog.text = "Excellent, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +". Shall we continue?";
			link.l1 = "Of course, Armo!";
			link.l1.go = "WaitCasper1_1";
		break;
		case "WaitCasper1_1":
			dialog.text = "Then come back tomorrow, maybe I'll be able to get someone else out.";
			link.l1 = "I understand you.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Armo.waiting");
			DeleteAttribute(pchar, "questTemp.LSC.Armo.Interrapt");
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//второй каспер
		case "Casper2":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = "Yes, there is. At the same place, at the same hour, I made an appointment with a casper named Serge Chambon. The coxcomb is still the one who has been courting me for a long time...";
				link.l1 = "Heh, he won't be bothering you for long.";
				link.l1.go = "Casper2_1";
			}
			else
			{
				dialog.text = "Not yet, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +". Wait for it.";
				link.l1 = "Clear.";
				link.l1.go = "exit";
			}
		break;
		case "Casper2_1":
			dialog.text = "Okay, that's good. So, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +", do not be late for the quarterdeck of the fluyt 'Ceres Smithy'. I don't think you should disappoint Serge.";
			link.l1 = "No way, Armo.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 3; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_MainLine", "37");
		break;

		case "WaitCasper2":
			dialog.text = "Very good, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +". Shall we try to pull this off again?";
			link.l1 = "If possible, Armo.";
			link.l1.go = "WaitCasper2_1";
		break;
		case "WaitCasper2_1":
			dialog.text = "It is possible. Come back tomorrow, I hope I will have time to arrange with someone else.";
			link.l1 = "Okay, Armo. Thank you.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Armo.waiting");
			DeleteAttribute(pchar, "questTemp.LSC.Armo.Interrapt");
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//третий каспер
		case "Casper3":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = "Yes, of course. Felipe Armas will be waiting for me at the same place as before, at the same time. The scoundrel that the world has never seen.";
				link.l1 = "Well, let's do it too...";
				link.l1.go = "Casper3_1";
			}
			else
			{
				dialog.text = "Not yet, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +". Wait for it.";
				link.l1 = "Clear.";
				link.l1.go = "exit";
			}
		break;
		case "Casper3_1":
			dialog.text = "Great! Well, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +", good luck to you.";
			link.l1 = "Thank you, I'll need it.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 5; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_MainLine", "38");
		break;
		//прерывания хода квеста Армо
		case "CasperLate":
			dialog.text = "You know what, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +", I'm not risking my life for you to take your promises so lightly. I'm not going to help you anymore. I'm sorry.";
			link.l1 = "Oh, it's a pity...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 12; //Отмазала девка
			AddQuestRecord("ISS_MainLine", "35");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
		break;
		case "CasperAllFight":
			dialog.text = "Yes, I know. The whole clan attacked you at once, they probably heard the noise of your fight. The main thing is that you did it. I am happy for you, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +".";
			link.l1 = "Thank you, Armo.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 16; //чтобы диалога больше не было
		break;
		//Армо мертва
		case "ArmoIsDead":
			dialog.text = "Hello. I know you, you are "+ GetSexPhrase("the very new citizen with whom", "the very new citizen with whom") +"Armo was very friendly.";
			link.l1 = "Yes, it is.";
			link.l1.go = "ArmoIsDead_1";
		break;
		case "ArmoIsDead_1":
			dialog.text = "It's a pity that Armo died. No one knows who killed her. The tavern just heard her scream upstairs. As luck would have it, no one was there at that moment. When people came running to her scream, she was lying with her throat cut in a pool of her own blood...";
			link.l1 = "Armo died because of me, that's for sure!";
			link.l1.go = "ArmoIsDead_2";
		break;
		case "ArmoIsDead_2":
			dialog.text = "Well, tears won't help grief, as they say... You know, in memory of Armo, I will call you the same as she does - "+ GetSexPhrase("Monsieur captain", "mademoiselle") +". Do you mind?";
			link.l1 = "Of course not.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		//Если Армо жива, то даёт денег
		case "askMoney":
			dialog.text = "You need money, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +"? And why?";
			link.l1 = "For one very necessary thing for the whole City. It's a matter of life and death!";
			link.l1.go = "askMoney_1";
		break;
		case "askMoney_1":
			dialog.text = "I believe you, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +". I can give you my savings, especially since I don't need them.";
			link.l1 = "You will oblige me very much, Armo.";
			link.l1.go = "askMoney_2";
		break;
		case "askMoney_2":
			dialog.text = "One hundred thousand is all I can offer.";
			link.l1 = "Great!";
			link.l1.go = "askMoney_3";
		break;
		case "askMoney_3":
			dialog.text = "Then take it. And I wish you good luck.";
			link.l1 = "Thank you, Armo!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			npchar.quest.giveMoney = true;
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("What goods are we talking about, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +"?",
				"You've already asked about this.",
				"They've already asked...",
                "You have already asked me about these goods. Is that enough?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I need bombs, knippels, food, gunpowder, weapons, medicines...",
				"yeah... Sorry, I forgot .",
                "Oh, yeah.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Bombs and other things can be asked from the housewives in the ships. If you are not familiar with them, then these are Alice Taylor, Aurelie Bertin, Lea Toors and Eliza Calvo. I have no idea about the rest.";
			link.l1 = "Clear... Thank you.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "48");
			AddQuestUserData("ISS_MainLine", "sName", GetFullName(npchar));
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("So what?",
				"We've already talked about it.",
				"This has already been discussed, I repeat for the second time.",
                "Enough, tired...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I want to invite you to join my team.",
				"Yeah... Sorry, I forgot.",
                "As you know...",
				"Well, okay...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			if (npchar.name == "Armo")
			{
				dialog.text = "No, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +". Thomas and I are staying in Town.";
				link.l1 = "What does your Thomas have to do with it?! By staying here, you're risking your life.";
				link.l1.go = "SeekCrew_2";
			}
			else
			{
				dialog.text = "No, "+ GetSexPhrase("monsieur captain", "mademoiselle") +". I'll stay here in my tavern.";
				link.l1 = "By staying here, you're risking your life.";
				link.l1.go = "SeekCrew_2";
			}
		break;
		case "SeekCrew_2":
			dialog.text = "Why?";
			link.l1 = "An impending storm is likely to destroy the City.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "How many of these storms have already been, we will survive another one.";
			link.l1 = "In vain... Well, okay, whatever you want.";
			link.l1.go = "exit";
		break;
		//освобождение мужа Элис Тейлор
		case "ELTHusb_SF":
			dialog.text = "I remember, "+ GetSexPhrase("Monsieur captain", "mademoiselle") +".";
			link.l1 = "Please tell me how it was.";
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = "Yes, there's not much to tell. Taylor stayed with us for three hours and left 'on the eyebrows.' However, as always.";
			link.l1 = "Understood... Is one gone?";
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = "With Gilles Baru by the hand.";
			link.l1 = "Wait. It turns out that Gilles Barou accompanied him home?";
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = "Well, yes.";
			link.l1 = "Aha! Thank you, darling.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "8");
			pchar.questTemp.LSC.ElisHusband = "toZhilBaru";
		break;

	}
	NextDiag.PrevNode = NodeName;
}

