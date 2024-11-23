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
					dialog.text = "Welcome to the City of Abandoned Ships, Captain. I am " + GetFullName(npchar) + ". Well, how do you like our weather? It's fun, isn't it?!";
					link.l1 = "Fun is not the right word!.. " + GetFullName(pchar) + ", at your service, monsieur " + npchar.lastname + ". Does this happen to you often?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Welcome to the City of Abandoned Ships, Captain. I am " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + ", at your service, monsieur " + npchar.lastname + ". Where are you from?";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "What did you want, "+ GetSexPhrase("monsieur", "mademoiselle") +"?";
				link.l1 = "Listen, I'm looking for someone. Do you know where he is now?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I want to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the latest gossip...");
				link.l3.go = "rumours_LSC";
				link.l4 = "Nothing...";
				link.l4.go = "exit";
				if (pchar.questTemp.LSC == "toAndreLabor")
				{
					link.l5 = "Buddy, how are you, how are you?";
					link.l5.go = "Tizer_1";
				}

			}
		break;
		case "FS_1":
			dialog.text = "It happens, "+ GetSexPhrase("monsieur", "mademoiselle") +"... At first, I was just dying of fear on such days, but now I'm used to it.";
			link.l1 = "Understood... Tell me, where are you from?";
			link.l1.go = "FT_1";
		break;
		case "FT_1":
			dialog.text = "At one time I was an apprentice to the owner of the shipyard on Tortuga, and after that I served as a carpenter on board the frigate Andromeda. Unfortunately, we were in the wrong place at the wrong time.";
			link.l1 = "What happened?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "A lot of things, "+ GetSexPhrase("monsieur", "mademoiselle") +", a lot. And all at once, imagine! First, the slaves rebelled, and in the midst of the suppression, we were attacked by bounty hunters because we had one on board... the man they needed\n"+
				"A hot boarding battle, and then a storm began, or rather, as if we were swept into some kind of storm zone. Next, our frigate came across rocks or reefs, leaked and sank. I grabbed an empty barrel and managed to get attached to it. It saved my life. I was floating around the ocean for a day, and then I was washed up here.";
			link.l1 = "Famously...";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "You really want to get out of here, don't you?";
			link.l1 = "Do you think this is possible?";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "I don't know, I haven't heard of this. If I had been given the opportunity to make something, I would definitely have tried. But this is prohibited by Law...";
			link.l1 = "Can we try together?";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "No, "+ GetSexPhrase("buddy", "mademoiselle") +", I pass. With our admiral, you can be at the bottom much sooner than you weigh anchor.";
			link.l1 = "Yeah... Well, it was nice to meet you, " + npchar + ". Have a nice day.";
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
			dialog.text = LinkRandPhrase("Yes you are a thief!!! Violation of the Law of the City!", "Wow! As soon as I looked at it, you went straight into the chest with your head!", "Police! They're robbing!!! Hold "+ GetSexPhrase("him", "her") +", "+ GetSexPhrase("he", "she") +" violated the law!");
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
				Link.l2 = "Thanks, I'll better look for it myself.";
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
			dialog.text = "I'm listening to you carefully, "+ GetSexPhrase("buddy", "mademoiselle") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "Listen, what are these ships holding on to in a storm?";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Why doesn't anyone unite against these prohibitions in the Law?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Listen, do you know where this City came from?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Has it ever happened that a ship or a squadron sailed here without first sinking in a wreck?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "Don't high-ranking officers get here?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions asked. I'm sorry...";
			link.l10.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = "I have no idea. And I don't advise you to find out - it's very dangerous.";
			link.l1 = "Why is it dangerous?";
			link.l1.go = "ansewer_5_1";
		break;
		case "ansewer_5_1":
			dialog.text = "Heh, to find out, you have to dive under the ships. And whoever dives doesn't come up...";
			link.l1 = "I see now.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_1":
			dialog.text = "Hmm, unite? Well, try it – a fair wind in your hunchbacked back. I... we love executions, we like to look at your kind, whose silhouettes slowly dissolve into the depths of the sea.";
			link.l1 = "I am not eager to look at the world from under the water.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "The devil knows! I am an ordinary carpenter, it is difficult for me to talk about natural science issues.";
			link.l1 = "Well, do you have any opinion at all?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Just like that, in general terms. I think there are reefs under the City that hold all these ships. First one caught on, then the other, and then it all grew.";
			link.l1 = "Ha! An interesting theory...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "I don't recall that.";
			link.l1 = "But is it possible?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Only if a miracle happens. Judge itself, there are rocks and reefs around...";
			link.l1 = "Hmm, that's for sure.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = "They get where they want to go.";
			link.l1 = "So what?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "Why? Capper is a pirate!";
			link.l1 = "Is he killing them?";
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = "Not necessary at all. If they understand in time where their place is and in which direction all their privileges have gone, then they stay alive.";
			link.l1 = "Funny.";
			link.l1.go = "int_quests";
		break;
		//квестовые диалоги
		case "Tizer_1":
			dialog.text = "Yes, everything is fine.";
			link.l1 = "Listen, can't you build some kind of swimming facility? A raft or a boat of some kind...";
			link.l1.go = "Tizer_2";
		break;
		case "Tizer_2":
			dialog.text = "Heh, do you know the Law? It's forbidden!";
			link.l1 = "Come on! You helped Teaser Dan, help the rest of those in need.";
			link.l1.go = "Tizer_3";
		break;
		case "Tizer_3":
			dialog.text = "To Teaser Dan? Ho!.. You surprised me pretty much, "+ GetSexPhrase("buddy", "beauty") +". Teaser Dan is dead.";
			link.l1 = "At this particular moment, yes. But not before. Hehe...";
			link.l1.go = "Tizer_4";
		break;
		case "Tizer_4":
			dialog.text = "Mmm, something is unclear... You know what, let's talk about this case somewhere else. Do you know where the Protector Corvette is? Go there and wait for me in the cabin. Well, I'll follow so that we don't hang out together.";
			link.l1 = "Sound idea! I'm going to tell you some news that I think will make you very happy. So don't keep me waiting.";
			link.l1.go = "Tizer_5";
		break;
		case "Tizer_5":
			dialog.text = "No way in the world, "+ GetSexPhrase("my friend", "" + pchar.name + "") +"!";
			link.l1 = "Okay, I'll be waiting for you at the Tread.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "8");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("I found a carpenter and talked to him carefully", "I found a carpenter and talked to him carefully"));
			pchar.questTemp.LSC = "toProtector";
			pchar.quest.LSC_enterToProtector.win_condition.l1 = "location";
			pchar.quest.LSC_enterToProtector.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_enterToProtector.function = "LSC_enterToProtector";
		break;

	}
	NextDiag.PrevNode = NodeName;
}
