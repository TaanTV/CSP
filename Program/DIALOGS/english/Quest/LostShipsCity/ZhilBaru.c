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
					dialog.text = "Greetings! As far as I understand, you are exactly "+ GetSexPhrase("the man who escaped", "the girl who escaped") +" in the last storm. Let me introduce myself, my name is " + GetFullName(npchar) + ".";
					link.l1 = "Very nice. Well, I'm " + GetFullName(pchar) + ".";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Greetings! As far as I understand, you are exactly "+ GetSexPhrase("the man who escaped", "the girl who escaped") +" from the last disaster. Let me introduce myself, my name is " + GetFullName(npchar) + ".";
					link.l1 = "Very nice. Well, I'm " + GetFullName(pchar) + ".";
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
					"What's new in the City?", "Eh, I would listen the lastest gossip...");
				link.l3.go = "rumours_LSC";
				//освобождение мужа Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toZhilBaru")
				{
					link.l5 = "I need to talk to you about Maxim Taylor.";
					link.l5.go = "ELTHusb_SF";
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
			dialog.text = "Well, how do you like our City in the hands of the elements, so to speak?";
			link.l1 = "You know, I'm not quite right now, because I lost everything and everyone. Therefore, the impressions are terrible so far.";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "Of course, it's understandable! I'm sorry for the tactlessness... You know, the storm will pass soon.";
			link.l1 = "I know, thanks.";
			link.l1.go = "FT_1";
		break;
		case "FT_1":
			dialog.text = "You know, it's very good that our City has been replenished with such a pleasant person like you. Very good.";
			link.l1 = "What makes you think I'm pleasant?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Um... It seemed so to me.";
			link.l1 = ""+ GetSexPhrase("When it seems, then they cross themselves, buddy. Is that clear?", "Well, thanks for the compliment!") +"";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = ""+ GetSexPhrase("Very clear, very clear!..", "Please. If you have any questions, please contact us.") +"";
			link.l1 = ""+ GetSexPhrase("Well, that's fine...", "Sure...") +"";
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
			dialog.text = LinkRandPhrase("Listen, you should take weapons away. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "Listen, why are you running around like d'Artagnan, waving your sword? Put away your weapon, it doesn't suit your face "+ GetSexPhrase("serious man", "girl") +"...");
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
			dialog.text = "I'm listening to you carefully, "+ GetSexPhrase("buddy", "mademoiselle") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Listen, what kind of island is this?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Do you know the reasons why this island was formed?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "Listen, how long have you been hanging out here?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "No questions asked. I'm sorry...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "This is the City of Abandoned Ships, "+ GetSexPhrase("buddy", "mademoiselle") +". Everything is a little different here than on the Mainland...";
			link.l1 = "And what do you mean?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Here is another life with its own Law! In principle, the arrangements are quite good and fairly fair. So I guess you'll like it here.";
			link.l1 = "Hmm, I hope so.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "No, and no one knows. They talk about some kind of strong current, then about algae, then about coral reefs, but no one knows for sure.";
			link.l1 = "Has anyone tried to find out?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "They say that there were attempts, but everything ended very, very sadly...";
			link.l1 = "Hmm, I see.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Chilling? Well said... I've been wiping my pants for about three years.";
			link.l1 = "It's been a long time. Aren't you tired?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Maybe I'm tired...";
			link.l1 = "Was Hill Brunner already here when you got here?";
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = "Was, of course. He knew everyone in the City. It's a pity for Hill, he was a very good man...";
			link.l1 = "I agree.";
			link.l1.go = "int_quests";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Sorry, I didn't understand. What did you say?";
			link.l1 ="I suggest you sail from the City to the Mainland as part of the crew of my ship.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "This is a suggestion! And do you really have a ship afloat?";
			link.l1 = "Yes, there is.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Well, there's nothing to think about. I'm going with you.";
			link.l1 = "Fine. Now go to the San Gabriel. Henrik Wedeker will transfer you to my ship.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "I'll just run to get my things, and I'm at your disposal.";
			link.l1 = "Great!";
			link.l1.go = "SeekCrew_all";
		break;
		//освобождение мужа Элис Тейлор
		case "ELTHusb_SF":
			dialog.text = "I'm listening to you.";
			link.l1 = "I found out that you left the tavern together the day Taylor was arrested. What happened? How did he get to the Admiral's residence?";
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = "I'm sorry, but what's it to you?";
			link.l1 = "The thing is that Maxim Taylor will spend the rest of his days in a cage on Tartarus. As punishment, the admiral gave him a life sentence.";
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = "Wow!..";
			link.l1 = "Exactly. I care about the Taylors, that's why I want to know what happened.";
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = "Damn, I didn't think it would come to this...";
			link.l1 = "Explain your words.";
			link.l1.go = "ELTHusb_SF_4";
		break;
		case "ELTHusb_SF_4":
			dialog.text = "Oh, how should I say this... In general, I was playing a joke on the admiral. He got it with his laws...";
			link.l1 = "What does Taylor have to do with it?";
			link.l1.go = "ELTHusb_SF_5";
		break;
		case "ELTHusb_SF_5":
			dialog.text = "Nothing to do with it, actually. It's just that we were having a drink that day at the tavern and we were just talking about it. Well, when Taylor and I went home, I took him to the San Augustine and invited him to express his displeasure to the admiral directly in the eyes. He did just that.";
			link.l1 = "Ho ho, not bad... However, I won't say that it looks decent from a moral point of view.";
			link.l1.go = "ELTHusb_SF_6";
		break;
		case "ELTHusb_SF_6":
			dialog.text = "I understand that I did not do the right thing. Therefore, I will go to the admiral and tell him that we were just joking.";
			link.l1 = "Well, great. I will also go to Capper, I will try to make sure that Taylor is released as soon as possible.";
			link.l1.go = "ELTHusb_SF_7";
		break;
		case "ELTHusb_SF_7":
			dialog.text = "Goodbye. I hope the Admiral doesn't kill me.";
			link.l1 = "It's unlikely.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "9");
			pchar.questTemp.LSC.ElisHusband = "toAdmiralGood";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
