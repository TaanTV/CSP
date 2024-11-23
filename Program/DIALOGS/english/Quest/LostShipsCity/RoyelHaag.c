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
					dialog.text = "Good afternoon! How do you like it here? It's a beautiful city, isn't it? And in stormy weather, it's just great!";
					link.l1 = "Absolutely! Only I got out of this storm?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Good afternoon! How do you like it here? It's a beautiful city, isn't it?";
					link.l1 = "Absolutely. My name is " + GetFullName(pchar) + ", I was...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "What did you want, "+ GetSexPhrase("mynheer", "mistress") +"?";
				link.l1 = "Listen, I'm looking for someone. Do you know where he is now?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I want to ask you a question.";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the lastest gossip...");
				link.l3.go = "rumours_LSC";
				link.l2.go = "int_quests";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Listen, I'm looking for some goods here.";
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
			dialog.text = "It looks like it is. I'm really sorry...";
			link.l1 = "Such is life... Yes, let me introduce myself. My name is " + GetFullName(pchar) + ", I was ...";
			link.l1.go = "FT_1";
		break;
		case "FT_1":
			dialog.text = "It doesn't matter who you were. I recommend this construction to you, I do not use the word 'city' here. Well, a new life has begun for you, and there is no turning back. By the way, I am " + GetFullName(npchar) + ".";
			link.l1 = "And why are you so sure, mynheer " + npchar.lastname + " that there is no return?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Because in the three years of being here, I have repeatedly seen where those who are trying to return go. Believe me, they're cold and wet there, and they're going to be stuck forever. I mean purgatory...";
			link.l1 = "I got it. Hmm, well, who helps them find nirvana? Is it not a Capper?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Hehe hehe... Chad Capper is our everything, moreover, he is our nothing at the same time. Anyway, you will have to follow his instructions. So you should be careful in your conversations.";
			link.l1 = "Be careful? And if I don't want to be careful?!";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Well, I will pray for the repose of your soul in this case. Without any doubt, the fate of Leighton Dexter awaits you.";
			link.l1 = "Hmm, so what happened to this Dexter?";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "I don't want to talk about it. If you want to know something about him, you'd better ask Lea Toors.";
			link.l1 = "Okay... You know, hope is a good thing, mynheer " + npchar.lastname + ". By convincing yourself of the hopelessness of the situation, you make it so yourself.";
			link.l1.go = "FT_6";
			AddQuestRecord("LSC_findDekster", "2");
			AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("LSC_findDekster", "sSex1", GetSexPhrase("en", "on"));
		break;
		case "FT_6":
			dialog.text = "Maybe, everything can be. But it's not that bad. We have the Law, we have our own life, we have... interesting. I would even say I like it here.";
			link.l1 = "And you are an opportunist!";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "So what? In my opinion, this is very good in this situation. By the way, I sincerely advise you too.";
			link.l1 = "Well, good luck to you, Mynheer " + npchar.lastname + ".";
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
			dialog.text = LinkRandPhrase("Listen, you should hide your weapon. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "Listen, what are you, like d'Artagnan, running around here, waving your sword? Put away your weapon, it doesn't suit your face "+ GetSexPhrase("serious man", "girl") +"...");
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
							dialog.text = LinkRandPhrase("So he's here, " + npchar.quest.seekIdx.where + ". Take a closer look.", "But he's here, among us!", "Where are you looking? He's hanging around here.");
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
							dialog.text = LinkRandPhrase("So she's here, " + npchar.quest.seekIdx.where + ". Look carefully.", "But she's here, among us!", "Where are you looking? She's walking around here somewhere.");
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
			dialog.text = "I'm listening to you carefully, "+ GetSexPhrase("buddy", "madam") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "This Law... is there any way around it?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Is there one government in the city? There is... The Admiral's opponents?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Is there somewhere to have fun?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = "Tell me, how long have you been living here? Aren't you tired of it?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions asked. I'm sorry...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "You can bypass anything, "+ GetSexPhrase("buddy", "madam") +". What matters is how it ends. I'm sure you're talking about sailing away from here...";
			link.l1 = "That's exactly what it's about!";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Well, it's possible...";
			link.l1 = "I'm all ears.";
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = "...in a coffin, ha ha ha!..";
			link.l1 = "You're a funny mynheer, you know...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "As many as you want. Look under the planks and at the bottom for what's left of them... We have clans, but they live in peace with the Admiral and the citizens of the City. However, as long as you don't go inside their ships.";
			link.l1 = "And what happens if I log in?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "They will, without any doubt, kill the person who entered.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Have some fun? Did you bring here to have fun?!";
			link.l1 = "Hmm, why not?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "You'll have fun when you get out of here! Ahem, but here's the bad luck: it's impossible! Ha ha ha!";
			link.l1 = "Understood.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = "Of course, I'm tired. Well, where to go? That's right, nowhere to go.";
			link.l1 = "Well, yes... Was Hill Brunner already here when you got here?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "I was, I already commanded the parade in my tavern. Oh, it's a pity for the man, he was a good innkeeper.";
			link.l1 = "That's for sure...";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Very good. How can I help you?",
				"You already asked about this.",
				"Already asked...",
                "You already asked me about these goods. I don't know anything!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I'm looking for bombs, grapeshot, food, medicines, gunpowder, weapons...",
				"Yeah... Sorry, I forgot .",
                "Oh, yeah.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Clear. It is better to ask the admiral for gunpowder and weapons. Bombs, grapeshot and other ammunition are at the housewives of the houses. And the holy Father has the medicines.";
			link.l1 = "I understand. Thank you very much.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Excuse me, what?";
			link.l1 ="I suggest you come to me as a sailor on my ship. I'm leaving soon.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Wow!.. And how did you manage to pull this off? After all, the Law forbids...";
			link.l1 = "Sorry, I don't have time. Do you agree?";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Of course I agree. What kind of questions can there be?";
			link.l1 = "Good! Then go to the San Gabriel immediately. The mechanic will transfer you to my ship.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Okay, I'll do that. I just need to pack my things.";
			link.l1 = "Okay, but don't linger.";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
