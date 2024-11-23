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
					dialog.text = "Despite the ongoing storm, congratulations, Captain.";
					link.l1 = "Congratulations?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Congratulations, Captain.";
					link.l1 = "Congratulations?";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "What did you want, "+ GetSexPhrase("sir", "miss") +"?";
				link.l1 = "Listen, I'm looking for someone. Do you know where he is now?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I want to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the lastest gossip...");
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Listen, I'm looking for some goods.";
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
			dialog.text = "Of course! You survived the crash, got here instead of sinking into oblivion. Isn't that something to be congratulated on? And the storm will pass by tomorrow evening, besides, it's not dangerous for you now.";
			link.l1 = "Agree...";
			link.l1.go = "FT_2";
		break;
		case "FT_1":
			dialog.text = "Of course! You survived the crash, got here instead of sinking into oblivion. Isn't that something to be congratulated on?";
			link.l1 = "You know best, sir...";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = GetFullName(npchar) + ", "+ GetSexPhrase("sir", "miss") +".";
			link.l1 = "Hello, Roger. My name is Captain " + GetFullName(pchar) + ".";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Likewise, Captain. How can I help you?";
			link.l1 = "How long have you been in the city?";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "A long time ago, "+ GetSexPhrase("dear captain", "dear") +". I won't say that I've been here the longest, but...";
			link.l1 = "Were you here before Capper?";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "I... ahem, what does it matter?";
			link.l1 = "Why is no one allowed to leave the city?";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "There are special reasons for this, Captain. I would not advise you to get involved in this matter.";
			link.l1 = "Why?";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "Because my congratulations in this case, it would be wise to cancel - you won't be... alive.";
			link.l1 = "Even so?";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "With all due respect, Captain, I have seen a lot of brave men in my lifetime, but those of them that I met in this city went to the Sea Devil a long time ago.";
			link.l1 = "Maybe meeting him won't hurt me either... Anyway, does Capper have friends, a right-hand man, assistants?";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "He has a whole militia of right hands! But I insist, Captain, that you don't put yourself at risk. I've told too many people the same thing, too many stood in front of me like you are now, and I saw courage when I looked at them... But they're all dead.";
			link.l1 = "Capper isn't immortal, is he?";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = "Who knows, who knows...";
			link.l1 = "Well, thank you for your concern.";
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = "Take care of yourself, Captain.";
			link.l1 = "Absolutely.";
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
			dialog.text = "Oh, so that's how it is?! Are you going to rummage through the chests?! Now the citizens and the police will tear you up like an old newspaper!";
			link.l1 = "What a fool!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you should hide your weapon. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "Listen, why are you running around like d'Artagnan, waving your sword? Put away your weapon, it doesn't suit your face "+ GetSexPhrase("serious man", "girl") +"...");
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
				dialog.text = NPCharSexPhrase(NPChar, "Be Careful on turns, "+ GetSexPhrase("buddy", "girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like when "+ GetSexPhrase("men", "all sorts") +" walk in front of me with weapons at the ready. It scares me...");
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
				Link.l1 = "I see. I'll try to name it again.";
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = "Thanks, I'll look myself.";
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
			dialog.text = "I'm listening to you carefully, "+ GetSexPhrase("buddy", "miss") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "And how long are the storms here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "It's kind of uncomfortable here, don't you think?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Where does the goods come from in stores? Is there a connection to the outside world?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = "Have you been living here for a long time?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions asked. I'm sorry...";
			link.l10.go = "exit";
		break;
		case "ansewer_3":
			dialog.text = "In different ways. The last one lasted a week, and was quite strong. In general, of course, the soul sinks into the heels when the waves begin to beat against the ships of the City...";
			link.l1 = "Does this happen?";
			link.l1.go = "ansewer_3_1";
		break;
		case "ansewer_3_1":
			dialog.text = "Of course it happens! But if the City is in place, then there is no reason to worry. I think so...";
			link.l1 = "Well, agree.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_1":
			dialog.text = "Of course it would be cozy here! No, this place is no better or worse than many others, but you will not find peace here.";
			link.l1 = "Hmm, I'm not looking for it.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Why do we need a connection? Ships come here regularly, so as not to return back... full holds, gold reserves, supplies for colonies in the New World. We have enough of everything.";
			link.l1 = "Interesting.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_4":
			dialog.text = "Yes, quite a while ago.";
			link.l1 = "How much?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "About two years.";
			link.l1 = "Understood. Hill Brunner, zanchit, was already here when you got here.";
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = "Yes, exactly.";
			link.l1 = "Okay, thanks.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("What kind of goods?",
				"You've already asked about it.",
				"They've already asked...",
                "You have already asked me about these goods. I don't know anything!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I'm looking for kernels, knippels, bombs, grapeshot, food, medicines, gunpowder, weapons...",
				"yeah... Sorry, I forgot .",
                "Oh, yeah.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "That's it, you don't have to continue. I don't know anything about it.";
			link.l1 = "Nothing at all?";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Absolutely. Have a nice day.";
			link.l1 = "Okay, goodbye...";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "What is the command?";
			link.l1 ="Command to my ship. I suggest you join me as a sailor.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Are you kidding?";
			link.l1 = "No. I do have a ship afloat, ready to sail. I'm waiting for your decision.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Damn, I agree! I'm sick of everything here already.";
			link.l1 = "Great! Then go to the San Gabriel immediately. Henrik Wedeker will transfer you to my ship.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Okay, I'll do that. I'll just pack my things quickly and I can leave.";
			link.l1 = "Don't linger.";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
