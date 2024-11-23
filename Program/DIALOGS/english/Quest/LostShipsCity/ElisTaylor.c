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
					dialog.text = "Hello, "+ GetSexPhrase("sir", "miss") +". I am very glad that you managed to escape after this terrible disaster... Although, needless to say, we've all been through it... You know, this storm will end soon, and your mood will definitely lift. Yes, my name is " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + ", at your service, miss... Tell me, do you have a replenishment after every storm?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Hello, "+ GetSexPhrase("sir", "miss") +". I am very glad that you managed to escape after this terrible disaster... Although, needless to say, we've all been through it. Yes, my name is " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + ", at your service, Miss...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "What do you need?";
				link.l1 = "You know, I'm looking for someone. Will you help me?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I wanted to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the latest gossip...");
				link.l3.go = "rumours_LSC";
				//муж Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "begin")
				{
					link.l7 = "I heard that you are looking for help in one case...";
					link.l7.go = "ELTHusb_begin";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElis")
				{
					link.l7 = "Your husband, Maxim Taylor, sent me to you.";
					link.l7.go = "ELTHusb_toElis";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElisGood")
				{
					link.l7 = "Alice, the Admiral will release your husband.";
					link.l7.go = "ELTHusb_good";
				}
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
			dialog.text = "No, this is far from the case, unfortunately. There are a lot of ships sticking to us, but there are not enough living people there. I don't know why... And by the way, I'm Mrs.";
			link.l1 = "Oh, I'm sorry...";
			link.l1.go = "FT_2";
		break;
		case "FT_1":
			dialog.text = "Mrs. I'm married.";
			link.l1 = "Oh, I'm sorry...";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "By the way, if you haven't visited our head, Admiral Chad Capper, then you better hurry up. Otherwise, he will come to you himself.";
			link.l1 = "Hmm, I see.";
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
				Link.l2 = "Thank you, but I'd rather do it myself.";
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
					Link.l2 = "No, I mean another.";
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
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Listen, what kind of island is this?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Are you English?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "Tell me, have you been living in the City for a long time?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "I have no questions for you, I'm sorry.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "How, you don't know yet? This Is the City of Abandoned Ships. And we are all lost people here... Oh, how tired I am of all this!";
			link.l1 = "I understand...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Yes, I am English. Why?";
			link.l1 = "Are there many Englishmen here at all?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "There are, but I didn't count. You know, it doesn't matter what kind of nation you are here. It says absolutely nothing and has no effect on anything.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Yes, I am English. Why?";
			link.l1 = "Are there many Englishmen here at all?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "Not really, about six months.";
			link.l1 = "Clear.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Which ones exactly?",
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
			dialog.text = "Well, I don't have any food or medicine. But there are quite a lot of balls left on the ship from the time when it sailed. How much do you need?";
			link.l1 = "100 штук вполне хватит.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "All right, take it.";
			link.l1 = "Thank you very much! Can you tell me who can drag them to the San Gabriel?";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Hmm, well, I don't know... Ask Felix Mendoza!";
			link.l1 = "Okay, I will definitely do that. Thank you!";
			link.l1.go = "exit";
			pchar.questTemp.LSC.additional.balls = true;
			AddQuestRecord("ISS_MainLine", "49");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "However... And why should I believe you?";
			link.l1 ="You don't owe me anything. But if you don't leave with me now, you will surely die. The fact is that the impending storm will destroy the City.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "How do you know?";
			link.l1 = "The Mechanic figured it out.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Oh, I believe Vedeker, apparently that's what's going to happen. Well, I agree.";
			link.l1 = "Okay. Now go to the San Gabriel. Henrik Wedeker will transfer you to my ship.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Agreed.";
			link.l1 = "Just don't stay anywhere!";
			link.l1.go = "SeekCrew_all";
		break;
		//вызволение мужа
		case "ELTHusb_begin":
			dialog.text = "That's right, "+ GetSexPhrase("sir", "miss") +". My husband, that cretin Maxim, went to prison again. I want to help him one last time.";
			link.l1 = "As far as I understand, you want to get him out of prison.";
			link.l1.go = "ELTHusb_begin_1";
		break;
		case "ELTHusb_begin_1":
			dialog.text = "True. Do it, and I will be able to thank you.";
			link.l1 = "What, may I ask?";
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = "Well, you are new"+ GetSexPhrase("th citizen", "th citizen") +" Cities. I can give you a very necessary thing.";
			link.l1 = "What exactly?";
			link.l1.go = "ELTHusb_begin_3";
		break;
		case "ELTHusb_begin_3":
			dialog.text = "One of the keys that locks all the chests in the City.";
			link.l1 = "This is really the right thing. I agree.";
			link.l1.go = "ELTHusb_begin_4";
			link.l2 = "Sorry, I don't need this.";
			link.l2.go = "ELTHusb_begin_disagree";
		break;
		case "ELTHusb_begin_disagree":
			dialog.text = "Well, it's a pity. I'll look for help from other people.";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			CloseQuestHeader("ISS_ElisHusband");
			pchar.questTemp.LSC.ElisHusband = "over"; //закончим
		break;
		case "ELTHusb_begin_4":
			dialog.text = "Very good. Then I will wait for my husband.";
			link.l1 = "I will do everything, wait.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "5");
			AddQuestUserData("ISS_ElisHusband", "sSex", GetSexPhrase("", "a"));
			pchar.questTemp.LSC.ElisHusband = "seekFreeMotod";
			sld = characterFromId("MaximTailor");
			sld.dialog.currentnode = "DontRemember";
		break;

		case "ELTHusb_toElis":
			dialog.text = "And what does this bastard want?";
			link.l1 = "I understand that he wants to get out of prison.";
			link.l1.go = "ELTHusb_toElis_1";
		break;
		case "ELTHusb_toElis_1":
			dialog.text = "How tired I am of him!..";
			link.l1 = "Listen, do you want to get him out of there or not? If you want, I could help in this matter.";
			link.l1.go = "ELTHusb_toElis_2";
		break;
		case "ELTHusb_toElis_2":
			dialog.text = "Okay, I accept your help. Release him, and I will give you a very necessary thing.";
			link.l1 = "Hmm... And what exactly, may I ask you?";
			link.l1.go = "ELTHusb_toElis_3";
		break;
		case "ELTHusb_toElis_3":
			dialog.text = "One of the keys that open the chests in the City.";
			link.l1 = "This is the right thing, I agree!";
			link.l1.go = "ELTHusb_begin_4";
			link.l2 = "Sorry, I don't need this.";
			link.l2.go = "ELTHusb_begin_disagree";
		break;

		case "ELTHusb_good":
			dialog.text = "Oh my God, is this really true? How did you manage to do that?";
			link.l1 = "Well, I found out something and told the Admiral about it. Chad has agreed to give your husband another chance to settle down.";
			link.l1.go = "ELTHusb_good_1";
		break;
		case "ELTHusb_good_1":
			dialog.text = "Great! I think that after such a shake-up, he won't drink like that anymore.";
			link.l1 = "I really hope so.";
			link.l1.go = "ELTHusb_good_2";
		break;
		case "ELTHusb_good_2":
			dialog.text = "You have kept your word, and I will keep mine. Please get the key.";
			link.l1 = "Thank you, I really need it.";
			link.l1.go = "ELTHusb_good_3";
			GiveItem2Character(pchar, "key1");
		break;
		case "ELTHusb_good_3":
			dialog.text = "But keep in mind that you should not rummage through other people's chests. If you get caught, you're finished.";
			link.l1 = "I understand that, thank you.";
			link.l1.go = "exit";
			CloseQuestHeader("ISS_ElisHusband");
			pchar.questTemp.LSC.ElisHusband = "over"; //закончим
			SetTimerFunction("LSC_ElisHusbandSet", 0, 0, 1);
		break;

	}
	NextDiag.PrevNode = NodeName;
}
