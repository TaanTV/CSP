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
					dialog.text = "Welcome to the City of Abandoned Ships, captain " + pchar.name + ". How do you like the situation in your new place of residence? Do you like the weather?";
					link.l1 = "I am sailor, I like any weather, just to be at sea. Wait, how do you know me?";
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.text = "Welcome to the City of Abandoned Ships, captain " + pchar.name + ".";
					link.l1 = "Do you know me?";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Can I help you with something, "+ GetSexPhrase("senor", "senorita") +"?";
				link.l1 = "Listen, I'm looking for someone. Do you know where he is now?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I want to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the latest gossip...");
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(pchar, "questTemp.LSC.additional.balls"))
				{
					link.l8 = "Listen, buddy, I need to move something to the barque San Gabriel. Will you help me with this case?";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "You know, I'm typing a command to get out of here. I suggest you come with me.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Nothing...";
				link.l10.go = "exit";
			}
		break;
		case "FT_1":
			dialog.text = "How not to know, "+ GetSexPhrase("senor", "senorita") +". My name is " + GetFullName(npchar) + " and I once stood up to you in battle.";
			link.l1 = "Did we fight with you?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "The past doesn't matter here, nor does your rank or nationality. I don't consider you my enemy while we're here, and I don't advise you to. My brig has sunk into the abyss of eternity, like all my people, and I have started a new life here.";
			link.l1 = "How long have you been here?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Six months or... a year, maybe.";
			link.l1 = "Have you tried to sail away?";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Ha, I wouldn't blame cowardice on those who don't even think about it. It's not worth trying–it's not courage, it's madness.";
			link.l1 = "Why? Nothing is impossible.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Well? You seem to know more about this place than I do, hmm?";
			link.l1 = "Rumors have leaked to the Mainland. If no one got out of here, then where would these rumors come from?";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = ""+ GetSexPhrase("My friend", "My dear") +"Believe me, it's a coincidence. And don't fill your head with empty hopes.";
			link.l1 = "Thanks for the advice.";
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
			dialog.text = LinkRandPhrase("Yes you are a thief!!! Violation of the Law of the City!", "Wow! As soon as I looked at it, you went straight into the chest with your head!", "Police! Robbery!!! Hold "+ GetSexPhrase("him!", "her!"));
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
			dialog.text = LinkRandPhrase("Listen, you should hide your weapon. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "serious man"+ GetSexPhrase("girl", "...") +"...");
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
				Link.l2 = "Thanks, I'll look for it myself.";
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
				Link.l3 = "You know, I don't want to ask about anyone else. Goodbye.";
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
					link.l1 = RandPhraseSimple("Yeah, I see. Thank you.", "Thank you!");
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
							dialog.text = LinkRandPhrase("So she's here, " + npchar.quest.seekIdx.where + ". Take a closer look.", "But she's here, among us!", "Where are you looking? She's walking around here somewhere.");
						}
						else
						{
							dialog.text = LinkRandPhrase("I saw her quite recently " + npchar.quest.seekIdx.where + ".", "Recently met her " + npchar.quest.seekIdx.where + ". We even talked to her.", "As far as I know, she is now " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Yeah, I see. Thank you, "+GetAddress_FormToNPC(NPChar)+".", "Thank you!");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = "I'm listening to you carefully, "+ GetSexPhrase("buddy", "senorita") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Do storms happen here often?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "How did you come to terms with the rules here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "It seems to me, or are people around in a hurry?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = "Tell me, how long have you been living here?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions asked. I'm sorry...";
			link.l10.go = "exit";
		break;
		case "ansewer_3":
			dialog.text = "Yes, often. This is especially felt when you are constantly at sea, as we all are here.";
			link.l1 = "Not tired?";
			link.l1.go = "ansewer_3_1";
		break;
		case "ansewer_3_1":
			dialog.text = "Where to go? Nowhere to go, "+ GetSexPhrase("buddy", "senorita") +"!";
			link.l1 = "Yeah, it's sad...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_1":
			dialog.text = "It was impossible not to accept. I, too, like many people, tried to prevent something, but I did not bring it to the point of absurdity.";
			link.l1 = "To the point of absurdity?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "In other words, before your own death.";
			link.l1 = "Hmm...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "This is not the first time I have heard this question... Yes, haha. There was one joker here–Bert. He got it into the heads of several people that life flows faster on this damned island...";
			link.l1 = "So what...?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "He was just joking, actually, but these fools believed him. Moreover, they began to spread this 'theory'. So it got to the point that those who believe in it are always in a hurry to get somewhere so as not to waste time.";
			link.l1 = "Very interesting.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = "Well, two years, probably. I don't remember exactly anymore.";
			link.l1 = "Was Hill Brunner already here when you got here?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "Yes, of course. Hill Brunner was one of the oldest citizens. It's a pity that he was killed.";
			link.l1 = "Yes, it's really a pity.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Ha! And why on earth would that be?",
				"It's all been decided.",
				"I'll do everything.",
                "Oh, you're so annoying.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Alice Taylor told me to talk to you...",
				"Great!",
                "Oh, yeah.",
				"Yeah.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Understood. Well, that makes a difference, I owe her. And what needs to be transferred, from where and where?";
			link.l1 = "From the fluyt 'Ceres Smithy' 100 pieces of kernels must be delivered to the barque 'San Gabriel'.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Let's do it, no problem.";
			link.l1 = "Well, thank you, buddy!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddQuestRecord("ISS_MainLine", "50");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Is this really possible?!";
			link.l1 ="Of course, it's possible. I'm waiting for an answer.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "I agree. What should I do?";
			link.l1 = "Go to the San Gabriel right now, where the Mechanic will arrange a transfer to my ship.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Okay. I'll be on the San Gabriel within the hour.";
			link.l1 = "Well, welcome. Don't be late.";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
