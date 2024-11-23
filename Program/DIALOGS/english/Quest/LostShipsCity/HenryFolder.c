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
					dialog.text =  TimeGreeting() + ", captain " + pchar.name + ". Congratulations on your arrival in the City! The storm will settle down soon, then you can get used to it better.";
					link.l1 = "Why do you think it will settle down soon?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = TimeGreeting() + ", captain " + pchar.name + ".";
					link.l1 = "Do we know each other?";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "How can I help you, "+ GetSexPhrase("sir", "miss") +"?";
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
					link.l8 = "You know, I'm typing a command to get out of here. I suggest you come with me.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Nothing...";
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = "Hmm, well, this is not my first storm here in the City. Therefore, I can say more or less accurately that the storm will settle down by tomorrow evening. " + GetFullName(npchar) + " at your service!";
			link.l1 = "Thank you. Tell me, my friend, if it's not a mystery, how you got here.";
			link.l1.go = "FT_5";
		break;
		case "FT_1":
			dialog.text = "No, not at all. It's just that I've heard about you before.";
			link.l1 = "But, alas, I have not heard of you.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Nothing surprising! " + GetFullName(npchar) + " at your service. How can I help you?";
			link.l1 = "Yes, I'm getting to know people, I'm adapting... I'll find out about the City.";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "About the city, hmm... And how do you like the City?";
			link.l1 = "Well, the city is quite interesting.";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Wrong word, Captain! This city is unique.";
			link.l1 = "How did you get here?";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "My story is probably the most boring of all. Maybe it's because I'm too lazy to embellish it. Besides, no one believes me.";
			link.l1 = "So what happened?";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "I literally came here myself, Captain. That's all.";
			link.l1 = "Yourself? Did you deliberately come here?! Then we are colleagues! And what brings you here?";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "The rumor has passed, Captain. I was the first to realize that this was not just a drunken bike, and decided to come here. I hired a captain and crew, gathered all the information, and got a dubious map... but it turned out to be much simpler\n"+
				"At night, for no reason, without storms and storms, the wind accelerated us to twenty knots, if I remember correctly the words of captain – I myself am not a navigator at all. We were happy for a while, and then we crashed into this city at full speed...";
			link.l1 = "Crashed?!";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "Yes, that's right – our ship is nearby, it has become part of this city. Besides, quite a lot of people survived, which is very rare. You can't imagine how Capper looked at us–I swear to God, this shake even made him jump up and put on his knickers!";
			link.l1 = "I wouldn't say that this story is boring.";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "To whom, but I would prefer a storm rather than a stupid wreck.";
			link.l1 = "Well, I'm glad to meet you. Thanks for the story.";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = "You're welcome, Captain. Let's get to know each other.";
			link.l1 = "Have a nice day.";
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
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "How is the weather here anyway?";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Why is this place not of interest to the authorities of the national powers? Does it belong to anyone?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Can you tell me where to bury the goods for a while?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Does everyone know the Law and follow it implicitly?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l5 = "Listen, how long have you been here?";
				link.l5.go = "ansewer_5";
			}
			link.l10 = "No questions asked. I'm sorry...";
			link.l10.go = "exit";
		break;
		case "ansewer_4":
			dialog.text = "Yes, it's fine. Storms are a fairly rare phenomenon, mostly sunny and windless here.";
			link.l1 = "It pleases.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_1":
			dialog.text = "Funny, huh, really... nobody.";
			link.l1 = "And no one tried to take over the city?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Of course not. No one knows anything about him on the Mainland. Rumors are only circulating among beggars about the Island of Justice... But who will take it seriously?";
			link.l1 = "That's right.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Chests, "+ GetSexPhrase("friend", "miss") +", chests... There are enough of them here. But you shouldn't meddle with other people's – just open the general ones, if you can, of course.";
			link.l1 = "How to understand?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "There are no chests without keys here, "+ GetSexPhrase("buddy", "" + pchar.name + "") +". Everything opens only with keys. And keep in mind that besides you there are a lot of people who have such keys. If you want to hide something safely, then you need to look for a chest somewhere outside the City, where you need to sail...";
			link.l1 = "Yeah, I see...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Ha, it doesn't matter if they know him or not!.. Violations are severely punished, and Capper is not interested in whether you have learned our Law the first time.";
			link.l1 = "Yes, I suspected as much.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_5":
			dialog.text = "It's already decent, so to speak...";
			link.l1 = "How much is it?";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "About five years.";
			link.l1 = "Ha, you're an old-timer! Probably, even before the late Hill Brunner, he became a citizen of the City.";
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = "No, not before.";
			link.l1 = "I see... listen, do you know any other old residents of the city?";
			link.l1.go = "ansewer_5_3";
		break;
		case "ansewer_5_3":
			dialog.text = "Why do you need it?";
			link.l1 = "Yes, it is necessary for one small matter...";
			link.l1.go = "ansewer_5_4";
		break;
		case "ansewer_5_4":
			dialog.text = "Well, if you don't want to talk, don't. And to answer your question - look for the old residents...";
			link.l1 = "How to understand?";
			link.l1.go = "ansewer_5_5";
		break;
		case "ansewer_5_5":
			dialog.text = "Whatever you want, understand it.";
			link.l1 = "Oh... Well, thanks for that, too.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("I'm sorry, I don't understand what you're talking about.",
				"You've already asked about this.",
				"They've already asked...",
                "You have already asked me about these goods. I don't know anything!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I need bombs, grapeshot, food, medicines, gunpowder, weapons...",
				"yeah... Sorry, I forgot .",
                "Oh, yeah.",
				"Got it, got it...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Ah, I see... I can't help you with anything. Although...";
			link.l1 = "What?";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Bombs and grapeshot can be searched by the housewives of the houses. These are far from the most valuable items in the City.";
			link.l1 = "Okay, thanks.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("Shall I go with you? That's the offer!",
				"We've already talked about this.",
				"This has already been discussed, I repeat for the second time.",
                "That's enough, I'm tired...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I'm waiting for a response.",
				"yeah... Sorry, I forgot .",
                "As you know...",
				"Well, okay...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "I think I'll give up. I like it here!";
			link.l1 = "Not tired yet?";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "No, I'm not tired. Everything you need for life is here. And all this is acquired without effort.";
			link.l1 = "Maybe the coming storm will bring you to your senses? The fact is that he will destroy the City.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "How do you know?";
			link.l1 = "I know for sure, you already believe me.";
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = "Sorry, I don't believe...";
			link.l1 = "Well, as you know.";
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
