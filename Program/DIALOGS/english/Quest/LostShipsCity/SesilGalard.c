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
			//после драки, когда Сесил пытаются убить
			if (pchar.questTemp.LSC == "toKnowAboutMechanic")
			{
				dialog.text = "You killed them! Thank you!";
				link.l1 = "Hmm, who are these people?";
				link.l1.go = "AfterFight";
				break;
			}

			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					if (npchar.location == "AvaShipInside3") dialog.text = "Welcome to my humble abode, Captain. How did you get to the storm?";
					else dialog.text = "Greetings, Captain. How did you get to the storm?";
					link.l1 = "Not without problems, but thanks for your concern. My name is " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
				else
				{
					if (npchar.location == "AvaShipInside3") dialog.text = "Welcome to my humble abode, Captain. How did you get there?";
					else dialog.text = "Greetings, Captain. How did you get there?";
					link.l1 = "Not without problems, but thanks for your concern. My name is " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "What do you need again?";
				link.l1 = "You know, I'm looking for someone. Will you help me?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I wanted to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Oh, I'd love to hear the latest gossip...");
				link.l3.go = "rumours_LSC";
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "You know, I'm typing a command to get out of here. I suggest you sail with me to the Mainland.";
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
			dialog.text = LinkRandPhrase("Listen, you should take weapons away. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "Listen, what are you, like d'Artagnan, running around here, waving your sword? Put away your weapon, it doesn't suit your face "+ GetSexPhrase("serious man", "girl") +"...");
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
				dialog.text = NPCharSexPhrase(NPChar, "Be Careful on turns, "+ GetSexPhrase("buddy", "girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like it when"+ GetSexPhrase("men", "all sorts of things here") +" they walk in front of me with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Understood.", "I'm removing.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;


		case "FS_1":
			dialog.text = GetFullName(npchar) + ", captain. Nice to meet you.";
			link.l1 = "What are you doing here in this weather?";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "With all due respect, Captain, this is none of your business.";
			link.l1 = "I understand. We all have something to hide, don't we?";
			link.l1.go = "FS_3";
		break;
		case "FS_3":
			dialog.text = "Please leave my house!";
			link.l1 = "Does the law allow you to do this?";
			link.l1.go = "FS_4";
		break;
		case "FS_4":
			dialog.text = "If the visitor is "+ GetSexPhrase("boorish lout", "ill-mannered girl") +", that's quite enough!";
			link.l1 = "Oh, thanks for the compliment...";
			link.l1.go = "exit";
		break;

		case "FT_1":
			dialog.text = GetFullName(npchar) + ", captain. Nice to meet you.";
			link.l1 = "What are you doing here?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "With all due respect, Captain, this is none of your business.";
			link.l1 = "I understand. We all have something to hide, don't we?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Please leave my house!";
			link.l1 = "Don't get too excited, I'm just getting used to it.";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Get used to another place.";
			link.l1 = "Hmm, I won't bother you.";
			link.l1.go = "exit";
		break;
		//ищем человека
		case "SeekCitizen":
			dialog.text = "If I have seen it, I will definitely tell you. So who are you looking for?";
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
					dialog.text = GetFullName(sld) + ", do you mean it?";
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
					dialog.text = LinkRandPhrase("I have no idea where he is.", "I have no idea where he is now.", "I haven't seen him for a decent amount of time. So I can't know.");
					link.l1 = RandPhraseSimple("Clear.", "Clear... Well, thank you.");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("I have no idea where she is.", "I have no idea where he is now.", "I haven't seen her for a decent amount of time. So I can't know.");
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
							dialog.text = LinkRandPhrase("He's here on this ship. Take a closer look, please.", "Hmm, so he's on this ship now...", "He's on this ship, it's strange that you've met yet.");
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
							dialog.text = LinkRandPhrase("She's here on this ship. Take a closer look, please.", "Hmm, so she's on this ship now...", "She's on this ship, it's strange that you've met yet.");
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
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "What can you do here other than walk around feeling sorry for yourself?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "How is life organized? Do people work here?";
				link.l2.go = "ansewer_2";
			}
			link.l10 = "I have no questions for you, I'm sorry.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Arrogant! You'd better forget how strong you were at sea and on land. Perhaps, of course, it was... But not here! You are nobody here, like all of us, and it is important for you now to gain the favor of people in the city, and you...";
			link.l1 = "I didn't mean to offend you, madam. Just tell me what you can do here at your leisure. Something interesting, eh?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Interesting? Are you a fan of risk, right? Well, try to visit the narwhals, for example...";
			link.l1 = "Are you talking about the Narwhal clan?";
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = "About them. There will be a lot of impressions, I promise.";
			link.l1 = "Hmm, you're a funny lady, I see...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Ha, if only that made sense... or a goal. But you can't set goals for yourself. You will not leave here alive like the rest of us.";
			link.l1 = "Very encouraging...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		//квесты
		case "HelpMe":
			dialog.text = "My God, help me!! Don't let them kill me!!";
			link.l1 = "What happened?";
			link.l1.go = "HelpMe_1";
		break;
		case "HelpMe_1":
			dialog.text = "Later... Protect me, please!";
			link.l1 = "Hmm, I don't see anyone yet.";
			link.l1.go = "exit";
			npchar.quest.meeting = "1";
			AddDialogExitQuestFunction("LSC_SaveSesilGalard_2");
		break;

		case "AfterFight":
			dialog.text = "These are 'Caspers'.";
			link.l1 = "Have they privatized this ship already?";
			link.l1.go = "AfterFight_1";
		break;
		case "AfterFight_1":
			dialog.text = "No, not at all. They just came to kill me.";
			link.l1 = "Is it that simple? They violated the Law of the City, which gives citizens the right to life!";
			link.l1.go = "AfterFight_2";
			npchar.greeting = "Gr_Woman_Citizen";
		break;
		case "AfterFight_2":
			dialog.text = ""+ GetSexPhrase("Young man", "Girl") +", that's what I'll tell you... I'm probably the oldest inhabitant of this island, and I've seen something like this here.";
			link.l1 = "Did you live here before Hill Brunner came to Town?";
			link.l1.go = "AfterFight_3";
		break;
		case "AfterFight_3":
			dialog.text = "I have been living here for about ten years. When I was washed up on the island, there were only five people living on it, and Hill Brunner was not among them.";
			link.l1 = "Wow... You know, Hill Brunner, before he died, was looking for a man who got to the island before him.";
			link.l1.go = "AfterFight_4";
		break;
		case "AfterFight_4":
			dialog.text = "Do you know why?";
			link.l1 = "Apparently, ask about the Mechanics.";
			link.l1.go = "AfterFight_5";
		break;
		case "AfterFight_5":
			dialog.text = "Hmm, well, wow... You know, since he's been isolated, you're the second person I've told about him. The first was Teaser Dan.";
			link.l1 = "Teaser Dan?! Damn it, do you know what happened to him?";
			link.l1.go = "AfterFight_6";
		break;
		case "AfterFight_6":
			dialog.text = "They say he drowned.";
			link.l1 = "Nothing like that. He has reached the Mainland!";
			link.l1.go = "AfterFight_7";
		break;
		case "AfterFight_7":
			dialog.text = "So he's alive?!";
			link.l1 = "Um, not anymore... He was killed in Willemstad by agents of the Dutch East India Company.";
			link.l1.go = "AfterFight_8";
		break;
		case "AfterFight_8":
			dialog.text = "Oh, what a pity! He fulfilled his dream - he got out of here, but he couldn't save himself. It's a pity...";
			link.l1 = "Yes, it's a pity... Listen, so who is this Mechanic?";
			link.l1.go = "AfterFight_9";
		break;
		case "AfterFight_9":
			dialog.text = "Oh, this is a legendary man, his name is Henrik Wedeker. The vast majority of the City's citizens do not even know that he lives with us. I haven't seen a mechanic since the Casper clan settled on the San Gabriel barge.";
			link.l1 = "You said he was isolated...";
			link.l1.go = "AfterFight_10";
		break;
		case "AfterFight_10":
			dialog.text = "Well, what else can you call it? I think the admiral is keeping Henrik in isolation on purpose. The thing is that a Mechanic is an extraordinarily talented person in terms of making something. At one time he began to talk about some kind of danger threatening us all. He said that we should leave the City before it's too late\n"+
				"But you know, eccentric people are not taken seriously, so they only laughed at his stories. And then the Law came out to prevent the construction of swimming facilities, and immediately the 'Caspers' occupied San Gabriel. Well, it became somehow indecent to remember about our eccentric, and it was unsafe.";
			link.l1 = "What do you mean, unsafe?";
			link.l1.go = "AfterFight_11";
		break;
		case "AfterFight_11":
			dialog.text = "People who knew Henrik personally began to disappear without a trace. And I would have disappeared today too, if it hadn't been for you...";
			link.l1 = "Do you mean this attempted murder?";
			link.l1.go = "AfterFight_12";
		break;
		case "AfterFight_12":
			dialog.text = "Exactly. It has become very easy to hide the traces of the crime now. The fact is that there are some creepy creatures under us, in the depths. If you dump the body into the water, it won't even float up afterwards...";
			link.l1 = "Oh... And why was the Mechanic isolated? Or maybe he's already been killed?";
			link.l1.go = "AfterFight_13";
		break;
		case "AfterFight_13":
			dialog.text = "The mechanic is alive because he is too necessary a person. After all, he came up with a way to attach ships to each other. When I got here, there were only four ships, and they were constantly moving. And Henrik managed to fasten them so that they would hold up normally.";
			link.l1 = "Ah, that's it...";
			link.l1.go = "AfterFight_14";
		break;
		case "AfterFight_14":
			dialog.text = "And his child isolated him after he began to panic. He said that we should all leave here while we have the opportunity...";
			link.l1 = "Understood. I suppose I should get to your genius Henrik and talk to him.";
			link.l1.go = "AfterFight_15";
		break;
		case "AfterFight_15":
			dialog.text = "Well, go ahead. Good luck!";
			link.l1 = "Thank you.";
			link.l1.go = "AfterFight_16";
		break;
		case "AfterFight_16":
			LAi_SetOwnerTypeNoGroup(npchar);
			pchar.questTemp.LSC = "toSeekMechanik";
			AddQuestRecord("ISS_MainLine", "31");
			pchar.quest.LSC_enterCasper.win_condition.l1 = "location";
			pchar.quest.LSC_enterCasper.win_condition.l1.location = "SanGabrielMechanic";
			pchar.quest.LSC_enterCasper.function = "LSC_enterCasper";
			sld = characterFromID("Casper_head");
			LAi_SetImmortal(sld, false);
			for (int i=1; i<=11; i++)
			{
				sld = characterFromID("Casper_"+i);
				LAi_SetImmortal(sld, false);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("Interesting suggestion...",
				"We've already talked about this.",
				"This has already been discussed, I repeat for the second time.",
                "That's enough, you've tired me...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes, and timely, too. A terrible storm is coming to the City.",
				"yeah... Sorry, I forgot .",
                "As you know...",
				"Well, okay...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "What are you saying? And who told you that?";
			link.l1 = "None other than the well-known Henrik Wedeker.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Hmm... You know, I'll take a chance and stay here. I'm too old for sea travel.";
			link.l1 = "Are you sure about your decision? That's not why I saved you from the 'Caspers' so you'd be so stupid as to risk your life.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Agree, Captain, that I have the right to do so.";
			link.l1 = "Undoubtedly.";
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = "Then the conversation is over.";
			link.l1 = "Well, it's a pity.";
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
