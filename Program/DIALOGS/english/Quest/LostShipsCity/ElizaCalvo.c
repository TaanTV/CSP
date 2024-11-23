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
					if (npchar.location == "SantaFlorentinaShipInside4") dialog.text = "This storm was very strong, "+ GetSexPhrase("senor", "senorita") +", you are very lucky that you were able to get out to us... My name is " + GetFullName(npchar) + ", I am the owner of this house.";
					else dialog.text = "This storm was very strong, "+ GetSexPhrase("senor", "senorita") +", you are very lucky that you were able to get out to us... My name is " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + ", at your service, senora. Tell me, how long did this storm last?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Hello! I understand that it was you who was saved last.";
					link.l1 = GetFullName(pchar) + ", at your service, senora. Yes, it's me.";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				if (npchar.location == "SantaFlorentinaShipInside4") dialog.text = "What do you need in my house, "+ GetSexPhrase("senor", "senorita") +"?";
				else dialog.text = "I'm listening to you, "+ GetSexPhrase("senor", "senorita") +".";
				link.l1 = "You know, I'm looking for someone. Will you help me?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I wanted to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting, senora?",
					"What's new in the City?", "Eh, I would listen the lastest gossip...");
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.bombs"))
				{
					link.l8 = "You know, I'm looking for some goods. Could you help me?";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.bombs") && sti(npchar.quest.bombs))
				{
					link.l8 = "I'm talking about bombs.";
					link.l8.go = "TakeBombs";
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
			dialog.text = "About a week, I won't say for sure. You know, when this happens around, you lose track of time.";
			link.l1 = "Yes, I understand.";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "By the way, everyone who gets into the City should check in with Admiral Chad Capper and get citizenship. If you haven't done it yet, then I advise you to hurry up.";
			link.l1 = "Where is this Chad Capper?";
			link.l1.go = "FS_3";
		break;
		case "FS_3":
			dialog.text = "In the residence of the city, on the varship 'San Augustine'.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "And my name is " + GetFullName(npchar) + ". I am the mistress of this cabin, or this house, as you like to call this haven.";
			link.l1 = "Probably 'house' would be more correct.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "I think so too. Well, welcome to my house.";
			link.l1 = "Thank you.";
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
			dialog.text = LinkRandPhrase("Yes you are a thief!!! Violation of the Law of the City!", "Wow! As soon as I looked at it, you went straight into the chest with your head! He broke the Law!", "Police! They're robbing!!! Hold "+ GetSexPhrase("him!", "her!"));
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
					Link.l2 = "No, I meant the other one.";
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
				link.l2 = "Do storms happen here often?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "Tell me, how long have you been living here?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "I have no questions for you, I'm sorry.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "This island is called the City of Abandoned Ships. And the name, I'll tell you, is absolutely accurate in essence.";
			link.l1 = "Understood.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Quite often. It's very scary, of course, but we're used to...";
			link.l1 = "Well, yes, there's nowhere to go!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "Quite a while ago, about three years. Why?";
			link.l1 = "Oh, nothing. Was the late Hill Brunner already here when you got here?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Yes, there was, of course. He was an old resident of the City. It's a pity that he died...";
			link.l1 = "Yes, it's a pity...";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("If I can, of course I will help.",
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
			dialog.text = "Bombs... I think I have something like that... Yes, that's right! How much do you need?";
			link.l1 = "100 штук будет вполне достаточно.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "There are so many. Only you have to do something for me, too.";
			link.l1 = "Always at your service.";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Bring me 10 grapes bunches, three bottle of vine and lute. I have a good mood now, I will sing and learn how to play.";
			link.l1 = "Is there anyone to teach you?";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = ""+ GetSexPhrase("Are you hinting at yourself? It's not worth it, the place is occupied...", "Yes, don't worry.") +"";
			link.l1 = ""+ GetSexPhrase("Not in any way, I just asked. ", "Yes ...") +"I think that if you eat so many grapes and drink so much wine, then you are unlikely to learn how to play.";
			link.l1.go = "SeekGoods_5";
		break;
		case "SeekGoods_5":
			dialog.text = "But that's none of your business. Carry what I told you, and that's it.";
			link.l1 = "Good, good, whatever you say.";
			link.l1.go = "exit";
			npchar.quest.bombs = true;
			AddQuestRecord("ISS_MainLine", "55");
		break;
		//проверка на соль
		case "TakeBombs":
			dialog.text = "Did you bring what I ordered?";
            if (CheckCharacterItem(pchar, "Mineral2") && CheckCharacterItem(pchar, "potionwine") && sti(pchar.items.potionwine) >= 3 && CheckCharacterItem(pchar, "potion5") && sti(pchar.items.potion5) >= 10)
            {
				link.l1 = "Yes, I have everything. Please receive it.";
				link.l1.go = "TakeBombs_yes";
			}
			else
			{
				link.l1 = "Not yet, I can't find it. Maybe you don't want to learn how to play anymore?";
				link.l1.go = "TakeBombs_no";
			}
		break;
		case "TakeBombs_no":
			dialog.text = "No...";
			link.l1 = "Understood.";
			link.l1.go = "exit";
		break;
		case "TakeBombs_yes":
			dialog.text = "Okay. You can take your bombs.";
			link.l1 = "Thank you. Is there any way to get it to the San Gabriel? I beg you very much.";
			link.l1.go = "TakeBombs_1";
			TakeNItems(pchar, "Mineral2", -1);
			TakeNItems(pchar, "potionwine", -3);
			TakeNItems(pchar, "potion5", -10);
		break;
		case "TakeBombs_1":
			dialog.text = "To 'San Gabriel'... Well, Okay, I will arrange it for your efforts. I will ask my chosen one, he will do everything.";
			link.l1 = "Great! Many thanks to you and the chosen one. He was very lucky...";
			link.l1.go = "TakeBombs_2";
		break;
		case "TakeBombs_2":
			dialog.text = "Thank you..."+ GetSexPhrase(" You're a flatterer, I see!", "") +"";
			link.l1 = ""+ GetSexPhrase("Sometimes...", "") +" Well, have a nice day.";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddQuestRecord("ISS_MainLine", "56");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
			npchar.quest.Bombs = false;
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Very frankly! And you're just breaking the Law like that?";
			link.l1 ="I have no way out, I'm saving my life. I can save yours too.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Hmm, explain yourself.";
			link.l1 = "The fact is that the coming storm is highly likely to destroy the city. The Mechanic figured it out.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Understood... Well, I agree to go to your ship. What should I do?";
			link.l1 = "Go to the San Gabriel. Henrik Wedeker will take you to my ship. And don't hesitate!";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Okay, I'll be on 'San Gabriel' soon.";
			link.l1 = "Please, hurry up...";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
