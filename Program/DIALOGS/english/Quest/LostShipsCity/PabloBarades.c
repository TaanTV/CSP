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
					dialog.text = "Hello! We haven't met yet. I don't think it's worth waiting for the storm to end to get acquainted, so I'll introduce myself. My name is " + GetFullName(npchar) + ".";
					link.l1 = "I am " + GetFullName(pchar) + ".";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Hello! We haven't met yet. My name is " + GetFullName(npchar) + ".";
					link.l1 = "I am " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "You wanted something."+ GetSexPhrase(", my friend", "Ah, " + pchar.name + "") +"?";
				link.l1 = "Listen, I'm looking for someone. Do you know where he is now?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I want to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the lastest gossip...");
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(pchar, "questTemp.LSC.additional.knippels"))
				{
					link.l8 = "Listen, I need to move something to the barque San Gabriel. I wanted to ask you to help me.";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "You know, I'm typing a command to get out of here.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Nothing...";
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = "How are you feeling?";
			link.l1 = "Okay. The storm doesn't scare me anymore. So it's okay, I'm getting used to it slowly.";
			link.l1.go = "FT_3";
		break;
		case "FT_1":
			dialog.text = "Well, now I've seen you too. How is the mood after this?";
			link.l1 = "What's the 'big deal'?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "After the crash, of course. I remember I couldn't come to my senses for a long time...";
			link.l1 = "Well, I don't have time to rock. We need to get used to it here.";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "And that's right, "+ GetSexPhrase("buddy", "" + pchar.name + "") +". You can't let sadness take over your mind, otherwise you won't last long here! Some people are screw loose, it's okay if they only ruin themselves, otherwise they will harm the City. You see, it's not clear what we're holding on to here, but as ships begin to sail, it's generally creepy. Creaking, cracking, decks dancing underfoot...";
			link.l1 = "Yeah... Does this happen often?";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "No, that's what I'm telling you! Our City is alive, you can't touch it. When they begin to disassemble him, to make some new ships to sail away from here, he begins to take revenge on people. That's it!";
			link.l1 = "Yes, things are...";
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
			dialog.text = LinkRandPhrase("Listen, you should put the gun away. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "serious man"+ GetSexPhrase("girl", "...") +"...");
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
					Link.l2 = "No, not about her. Listen, let me try to name it again.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "You know, I don't want to ask anyone else. Goodbye.";
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
					dialog.text = LinkRandPhrase("I don't know, I haven't seen him for a long time.", "The devil knows where he is...", "I haven't seen him decently, so I don't know.");
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
							dialog.text = LinkRandPhrase("I saw it quite recently " + npchar.quest.seekIdx.where + ".", "Recently met him " + npchar.quest.seekIdx.where + ". So look for him there.", "As far as I know, he is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("So he's here, " + npchar.quest.seekIdx.where + ". Look carefully.", "But he's here, among us!", "Where are you looking? He's hanging around here.");
						}
						else
						{
							dialog.text = LinkRandPhrase("I saw it quite recently " + npchar.quest.seekIdx.where + ".", "Recently met him " + npchar.quest.seekIdx.where + ". So look for him there.", "As far as I know, he is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Yeah, I see. Thank you, buddy.", "Thank you!");
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
					link.l1 = RandPhraseSimple("Yeah, I see. Thank you, buddy.", "Thank you!");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = "Ask. If I can answer, I will definitely do it.";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Listen, what kind of island is this?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l2 = "Listen, buddy, how long have you been here?";
				link.l2.go = "ansewer_2";
			}
			link.l10 = "No questions asked. Sorry, buddy...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "This is the City of Abandoned Ships, "+ GetSexPhrase("buddy", "" + pchar.name + "") +". Keep in mind that the City is alive. Some citizens don't believe it, but you know that it is true!";
			link.l1 = "Well, whatever you say, I'll keep it in mind.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "No, not really. About two years already.";
			link.l1 = "Clear. So Hill Brunner has already been here.";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Yes, of course.";
			link.l1 = "Okay, thanks.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Well, why should I work hard?",
				"It's all been decided.",
				"I'll do everything.",
                "Oh, and you're annoying.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Aurelie Bertin asked you to help me.",
				"Great!",
                "Oh, yeah.",
				"Yeah.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Ah, Aurelie... Well, I'll help you, I respect this old lady. What needs to be done?";
			link.l1 = "Of the 'Furya', 100 of the knippels must be delivered to the 'San Gabriel' barque.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Okay, I'll do it.";
			link.l1 = "Well, thank you, buddy!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddQuestRecord("ISS_MainLine", "52");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Which command?";
			link.l1 = "Command to my ship. I suggest you leave the City with me.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Heh, that's a suggestion! I need to think about it...";
			link.l1 = "There is no time to think, you need to decide right now.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Why the rush?";
			link.l1 = "There is an assumption that an impending storm will destroy the City.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Hmm, this may well be. As the storm begins, the city creaks, cracks...";
			link.l1 = "I'm waiting for a response. Time is running out.";
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = "I agree, I'm going to join your team as a sailor.";
			link.l1 = "Great! Go to the San Gabriel right now, and a Mechanic will ferry you to the ship.";
			link.l1.go = "SeekCrew_5";
		break;
		case "SeekCrew_5":
			dialog.text = "Okay, I'll just pack my things.";
			link.l1 = "Don't be late!";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
