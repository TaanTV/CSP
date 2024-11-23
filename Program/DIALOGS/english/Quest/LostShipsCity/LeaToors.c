#include "DIALOGS\english\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					if (npchar.location == "PlutoStoreSmall") dialog.text = "Greetings, "+ GetSexPhrase("mynheer", "mistress") +", at home, you can wait out this storm with me. My name is " + GetFullName(npchar) + ".";
					else dialog.text = "Greetings, mynheer. My name is " + GetFullName(npchar) + ".";
					link.l1 = "And I am captain " + GetFullName(pchar) + ". Wait out the storm, you say?";
					link.l1.go = "FS_1";
				}
				else
				{
					if (npchar.location == "PlutoStoreSmall") dialog.text = "Greetings, "+ GetSexPhrase("mynheer", "madam") +", at home. My name is " + GetFullName(npchar) + ".";
					else dialog.text = "Greetings, "+ GetSexPhrase("mynheer", "madam") +". My name is " + GetFullName(npchar) + ".";
					link.l1 = "And I am captain " + GetFullName(pchar) + ". In fairness, it should be noted that the former Captain...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Can I help you with something, "+ GetSexPhrase("mynheer", "madam") +"?";
				link.l1 = "You know, I'm looking for someone. Will you help me?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I wanted to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the lastest gossip...");
				link.l3.go = "rumours_LSC";
				//квест со скелетом Декстера
				if (CheckActiveQuest("LSC_findDekster") && !CheckAttribute(pchar, "questTemp.LSC.lostDecster"))
				{
					link.l4 = "Lea, I heard that you know something about a certain Leighton Dexter...";
					link.l4.go = "LostDecster";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.grapes"))
				{
					link.l8 = "Listen, I'm looking for some goods.";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.grapes") && sti(npchar.quest.grapes))
				{
					link.l8 = "I'm talking about grapeshot.";
					link.l8.go = "TakeGrapes";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "You know, I'm typing a command to get out of here. I suggest you come with me to the Mainland.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Nothing...";
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "FS_1":
			dialog.text = "Yes, you can stay here as long as you want. The law says that every landlord in the City must give shelter to those in need during the rampage of the elements. It's just such a time now.";
			link.l1 = "Yes, it's noticeable... Well, thank you very much.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "I understand that it is not easy for you to lose everything. But you were saved!";
			link.l1 = "Yes, yes, of course...";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Listen, you shouldn't despair. I advise you to get involved in our lives faster, it's not as bad as it might seem at first glance.";
			link.l1 = "Thank you for your support.";
			link.l1.go = "exit";
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
			dialog.text = LinkRandPhrase("Yes you are a thief!!! Violation of the Law of the City!", "Wow! As soon as I looked at it, you went straight into the chest with your head!", "Police! Robbery!!! Hold " + GetSexPhrase("him!", "her!"));
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
			dialog.text = LinkRandPhrase("Listen, you should take weapons away. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "serious man"+ GetSexPhrase("girl", "...") +"...");
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this city, I ask you not to walk with a naked blade here.", "You know, as a citizen of this city, I ask you not to walk with a naked blade here.");
				link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Careful on turns, "+ GetSexPhrase("buddy", "girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like when "+ GetSexPhrase("men", "all sorts") +" walk in front of me with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Understood.", "I'm removing.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;


		//ищем человека
		case "SeekCitizen":
			dialog.text = "I will be happy to help you if I can, of course. So who are you looking for?";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = "I'm sorry, but I don't understand at all who you're talking about. To help you, I need a first and last name.";
				Link.l1 = "Hmm. Let me try to name them again.";
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = "Thank you, I'll look myself.";
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = "Hmm, I'm sorry, but you're looking for me. It's me.";
					link.l1 = "Wow!";
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + ", do you mean him?";
					Link.l1 = "Exactly him.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "No, I mean another one.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + "Have you talked about her?";
					Link.l1 = "That's right, it's about her.";
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = "No, not about her. Maybe I'll try to name it again?";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "You know, I'm very grateful to you, but I don't want to ask about anyone else.";
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = "Then you will have to give your first and last name again.";
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
					dialog.text = LinkRandPhrase("I have no idea where he is.", "I have no idea where he is now.", "I haven't seen him for quite a while. So I can't know.");
					link.l1 = RandPhraseSimple("Clear.", "Clear... Well, thank you.");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("I have no idea where she is.", "I have no idea where he is now.", "I haven't seen her for quite a while. So I can't know.");
					link.l1 = RandPhraseSimple("Clear.", "Clear... Well, thank you.");
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
							dialog.text = LinkRandPhrase("He's here on this ship. Take a closer look, please.", "Hmm, so he's on this ship now...", "He's on this ship, it's strange that you haven't met yet.");
						}
						else
						{
							dialog.text = LinkRandPhrase("I saw him quite recently " + npchar.quest.seekIdx.where + ".", "You know, I met him recently " + npchar.quest.seekIdx.where + ". So look for him there.", "As far as I know, he is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("Sorry, but it's right here, " + npchar.quest.seekIdx.where + ". You need to be careful.", "Hmm, he's here among us!", "If you looked around more carefully, you probably already saw him...");
						}
						else
						{
							dialog.text = LinkRandPhrase("I saw him quite recently " + npchar.quest.seekIdx.where + ".", "Recently met him " + npchar.quest.seekIdx.where + ". So you can see him there.", "As far as I know, he is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Yeah, I see. Thank you!", "Thank you very much.");
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
							dialog.text = LinkRandPhrase("She's here on this ship. Take a closer look, please.", "Hmm, so she's on this ship now...", "She's on this ship, it's strange that you haven't met yet.");
						}
						else
						{
								dialog.text = LinkRandPhrase("I saw her quite recently " + npchar.quest.seekIdx.where + ".", "You know, I met her recently " + npchar.quest.seekIdx.where + ". So look for her there.", "As far as I know, she is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("Sorry, but it's right here, " + npchar.quest.seekIdx.where + ". You need to be careful.", "Hmm, she's here among us!", "If you looked around more carefully, you probably already saw her...");
						}
						else
						{
							dialog.text = LinkRandPhrase("I saw her quite recently " + npchar.quest.seekIdx.where + ".", "Recently met her " + npchar.quest.seekIdx.where + ". So you can see her there.", "As far as I know, she is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Yeah, I see. Thank you!", "Thank you very much.");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = "I'm listening to you carefully.";
			if (!CheckAttribute(NextDiag, NodeName+".l1") && npchar.location == "PlutoStoreSmall")
			{
				link.l1 = "And how does it feel to be the mistress of this house?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l2 = "Tell me, have you lived here long?";
				link.l2.go = "ansewer_2";
			}
			link.l10 = "I have no questions for you, I'm sorry.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "It's quite normal, you know. I have everything under control, my house is my fortress.";
			link.l1 = "That's great.";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "And don't try to grab something from me, I'm strictly watching it!";
			link.l1 = "No way!";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "No, it's only been about a year.";
			link.l1 = "Understood... Tell me, do you know any of the local old-timers who have been living here for a very long time?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "I knew. This is Hill Brunner.";
			link.l1 = "Heh, I know that. But the bad luck is, he's dead...";
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = "Yes, a terrible story! And completely incomprehensible, besides.";
			link.l1 = "That's right... Well, all the best to you, Lea.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("And how can I help you?",
				"You've already asked about this.",
				"They've already asked...",
                "You have already asked me about these goods. I don't know anything!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I'm looking for balls, bombs, grapeshot, knippels, food, medicines...",
				"yeah... Sorry, I forgot .",
                "Oh, yeah.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "I have grapeshot on my ship. How much do you need?";
			link.l1 = "Five centers should be enough.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Okay, I'll give it to you. Just bring me 10 bags of salt first.";
			link.l1 = "What?";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "I want you to bring me 10 bags of salt. What's so strange? And then I'll give you the buckshot.";
			link.l1 = "Okay, you'll have your salt.";
			link.l1.go = "exit";
			npchar.quest.grapes = true;
			AddQuestRecord("ISS_MainLine", "53");
		break;
		//проверка на соль
		case "TakeGrapes":
			dialog.text = "Did you bring me ten bags?";
            if (CheckCharacterItem(pchar, "Mineral10") && sti(pchar.items.Mineral10) >= 10)
            {
				link.l1 = "Yes, I have them, and I'm ready to give them to you.";
				link.l1.go = "TakeGrapes_yes";
			}
			else
			{
				link.l1 = "Not yet, I can't find it. Maybe we can come to an agreement in some other way?";
				link.l1.go = "TakeGrapes_no";
			}
		break;
		case "TakeGrapes_no":
			dialog.text = "Don't even dream about it!";
			link.l1 = "Hmm, I see...";
			link.l1.go = "exit";
		break;
		case "TakeGrapes_yes":
			dialog.text = "Excellent! Well, you can take your grapeshot.";
			link.l1 = "Thank you. Eh, how can I get her to the San Gabriel?";
			link.l1.go = "TakeGrapes_1";
			TakeNItems(pchar, "Mineral10", -10);
		break;
		case "TakeGrapes_1":
			dialog.text = "Um... Well, I made you run, and now I'm going to help you. Transportation to the San Gabriel I'll arrange it for you myself, since I have a lot of men I know...";
			link.l1 = "Great! I don't even know how to thank you.";
			link.l1.go = "TakeGrapes_2";
		break;
		case "TakeGrapes_2":
			dialog.text = "Oh, come on, it's not worth it. Everything is fine.";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddQuestRecord("ISS_MainLine", "54");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "la"));
			npchar.quest.grapes = false;
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Wow!.. Are you serious?";
			link.l1 = "Not at all.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "You know, I'm pretty tired of everything here. So if you're telling the truth, then I agree.";
			link.l1 = "You made the right choice, I can assure you.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "I really hope so. So, what should I do now?";
			link.l1 = "Go to the San Gabriel. Henrik Wedeker will take you to my ship. And don't hesitate!";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Okay, I'll be on 'San Gabriel' soon.";
			link.l1 = "Please, hurry up...";
			link.l1.go = "SeekCrew_all";
		break;
		//квест со скелетом Лейтона Декстера
		case "LostDecster":
			dialog.text = "Hmm, why are you asking?";
			link.l1 = "Well, how do I say it? I was just curious.";
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = "Let me say that your interests are spreading in a very dangerous direction...";
			link.l1 = "What is this supposed to mean?";
			link.l1.go = "LostDecster_2";
		break;
		case "LostDecster_2":
			dialog.text = "If you want to engage in a confrontation with the admiral, then I'm afraid the fate of the unfortunate Leighton awaits you.";
			link.l1 = "So, who is he? And what happened to him anyway?";
			link.l1.go = "LostDecster_3";
		break;
		case "LostDecster_3":
			dialog.text = "Are you sure you want to know this?";
			link.l1 = "Absolutely.";
			link.l1.go = "LostDecster_4";
		break;
		case "LostDecster_4":
			dialog.text = "Well, I'll tell you, you probably already know that Dexter was a pirate, like Chad Capper, actually. At first, the two corsairs became friends. Chad, when he became an admiral, immediately appointed Leighton chief of the Tartarus. I hope you know that this is our prison?";
			link.l1 = "Hmm... Yes, of course, I know that.";
			link.l1.go = "LostDecster_5";
		break;
		case "LostDecster_5":
			dialog.text = "But then a black cat ran between them. Once I went to visit Maxim Taylor, who was once again imprisoned. And it was in the evening, and, in general, I stayed there until midnight, so when I went on deck, I heard two voices - Chad and Leighton. They were arguing about money...";
			link.l1 = "Yeah... And what happened next?";
			link.l1.go = "LostDecster_6";
		break;
		case "LostDecster_6":
			dialog.text = "Then the argument was interrupted by a hoarse gurgling moan. I'm not a fool, and I hurried to quietly get off the Tartarus. I don't know anything else, but no one has seen Leighton Dexter since.";
			link.l1 = "Do you think Chad killed him?";
			link.l1.go = "LostDecster_7";
		break;
		case "LostDecster_7":
			dialog.text = "I don't know, but it looks like it.";
			link.l1 = "Understood... So all this happened on Tartarus?";
			link.l1.go = "LostDecster_8";
		break;
		case "LostDecster_8":
			dialog.text = "Apparently.";
			link.l1 = "Clear. Thank you for your frankness.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.lostDecster = "toAdmiral";
			AddQuestRecord("LSC_findDekster", "3");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
