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
			//если Сесил Галард замочили, то это оставшийся шанс узнать о Механике
			if (pchar.questTemp.LSC == "SessilIsDead")
			{
				dialog.text = "Tell me, is it true that you tried to save Cecil Galard?";
				link.l1 = "Yes, it is. Unfortunately, it didn't work out...";
				link.l1.go = "SessilDead";
				npchar.quest.meeting = "1";
				break;
			}

			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					if (npchar.location == "FurieShipInside2") dialog.text = "My God, what a storm!.. Hello, my name is " + GetFullName(npchar) + ", I am the owner of this house.";
					else dialog.text = "My God, like a storm!.. Hello, my name is " + GetFullName(npchar) + ".";
					link.l1 = "Very nice. And I am captain " + GetFullName(pchar) + ". Or rather, the former Captain. And all because of this devilish storm!";
					link.l1.go = "FS_1";
				}
				else
				{
					if (npchar.location == "FurieShipInside2") dialog.text = "Hello, my name is " + GetFullName(npchar) + ", I am the owner of this house.";
					else dialog.text = "Hello, my name is " + GetFullName(npchar) + ".";
					link.l1 = "Very nice. And I am captain " + GetFullName(pchar) + ". Rather, the former Captain...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "What do you need, "+ GetSexPhrase("monsieur", "mademoiselle") +"?";
				link.l1 = "You know, I'm looking for someone. Will you help me?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I wanted to ask you a question.";
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
			dialog.text = "Do not mention the unclean, otherwise it will appear! And, being at my house, please do not swear!";
			link.l1 = "Oh, I'm sorry...";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "Well, don't worry so much. After all, you're alive, and that's pretty good!";
			link.l1 = "Yes, you are right. I apologize for the momentary weakness"+ GetSexPhrase(", unworthy of a man", "") +"...";
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
							dialog.text = LinkRandPhrase("Sorry, but it's right here, " + npchar.quest.seekIdx.where + ". You need to be careful.", "Hmm, he's here among us!", "If you looked around more carefully, you probably would have already seen him...");
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
							dialog.text = LinkRandPhrase("Sorry, but it's right here, " + npchar.quest.seekIdx.where + ". You need to be careful.", "Hmm, she's here among us!", "If you looked around more carefully, you probably would have already seen her...");
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
				link.l1 = "How long have you been here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Are you bored?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "Tell me, did you get here before Hill Brunner?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "I have no questions for you, I'm sorry.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Me personally... Hmm, I don't remember anymore. But if you're wondering how long this city has been standing here, then... a long time ago. Very much.";
			link.l1 = "Clear.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "By native lands? Sure... But you have to put up with the circumstances. A person can adapt, which is what is required of us.";
			link.l1 = "I don't feel like it.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "No, he was already the owner of the tavern here.";
			link.l1 = "Understood... Listen, does the Mechanic's name or nickname mean anything to you?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Mm-hmm... I don't remember, I'm sorry. You know, I'm a little busy right now and I don't want to continue this conversation. I'm sorry.";
			link.l1 = "Understood. Well, thank you.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "30");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("xia", "as"));
		break;

		case "SessilDead":
			dialog.text = "Cecil was the oldest resident of the City... Do you know why she was killed?";
			link.l1 = "No, but I, like Hill Brunner, was looking for a person who could answer my question. She probably could.";
			link.l1.go = "SessilDead_1";
		break;
		case "SessilDead_1":
			dialog.text = "And what is this question?";
			link.l1 = "Who is the Mechanic?";
			link.l1.go = "SessilDead_2";
		break;
		case "SessilDead_2":
			dialog.text = "I know who it is. I didn't want to talk about it before, because I thought such conversations were unsafe. But Cecil's death made me change my mind...";
			link.l1 = "Speak up, I'm listening to you carefully.";
			link.l1.go = "SessilDead_3";
		break;
		case "SessilDead_3":
			dialog.text = "The Mechanic's name is Henrik Wedeker. Most of the citizens of the City don't even know that he lives with us. I haven't seen a mechanic since the Casper clan settled on the San Gabriel barge.";
			link.l1 = "Have you lived in the City for a long time too?";
			link.l1.go = "SessilDead_4";
		break;
		case "SessilDead_4":
			dialog.text = "Not as long ago as Cecil lived, but still a long time ago. I saw the mechanic...";
			link.l1 = "So you're saying this Henrik is on the barque San Gabriel?";
			link.l1.go = "SessilDead_5";
		break;
		case "SessilDead_5":
			dialog.text = "Yes. I think the admiral is keeping Henrik in isolation on purpose, which is why he gave the barque San Gabriel to the Casper clan. The thing is, the Mechanic is an extraordinarily talented person. When you need to make something, he has no equal. At one time he began to talk about some kind of danger threatening us all. He said that we should leave the City before it's too late\n"+
				"But you know, eccentric people are not taken seriously, so they only laughed at his stories. And then the Law came out to prevent the construction of swimming facilities, and immediately the Caspers occupied the San Gabriel. Well, it became somehow indecent to remember about our eccentric, and it was unsafe.";
			link.l1 = "Are you sure Henrik is still alive?";
			link.l1.go = "SessilDead_6";
		break;
		case "SessilDead_6":
			dialog.text = "I'm sure. The fact is, Henrik invented a way to attach ships to the island, the admiral needs it. Otherwise, there will be no one to repair the City of Abandoned Ships.";
			link.l1 = "That's how it is!.. Well, thank you very much, Aurelie. I guess I need to get to the Mechanic and talk to him.";
			link.l1.go = "SessilDead_7";
		break;
		case "SessilDead_7":
			dialog.text = "Well, try it. I wish you good luck.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toSeekMechanik";
			AddQuestRecord("ISS_MainLine", "32");
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
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("What exactly are you looking for?",
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
			dialog.text = "I can help you with the knippels, although I don't understand why you need this stuff.";
			link.l1 = "I do. You know, 100 grand of this stuff will be enough.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "All right, you can take it.";
			link.l1 = "Damn it, I can't make it! Can you tell me who can arrange delivery to the barque San Gabriel?";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Ask Pablo Baradez on my behalf. He has to help.";
			link.l1 = "Okay, I will definitely do that. Thank you!";
			link.l1.go = "exit";
			pchar.questTemp.LSC.additional.knippels = true;
			AddQuestRecord("ISS_MainLine", "51");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Is that so? Interesting... Do you really have a ship?";
			link.l1 = "Yes.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "And is it in good condition? Are we going to reach the Mainland?";
			link.l1 = "Absolutely.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Then I agree.";
			link.l1 = "Okay. Go to the San Gabriel as soon as possible now. Henrik Wedeker will take you to my ship.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "I understand you. I'll do everything as you said.";
			link.l1 = "Please, hurry up...";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
