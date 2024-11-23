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
			dialog.text = "Greetings to my friend and just really"+ GetSexPhrase("good man", "good girl") +". How can I help you?";
			link.l1 = "Listen, I'm looking for someone. Do you know where he is now?";
			link.l1.go = "SeekCitizen";
			link.l2 = "I want to ask you a question.";
			link.l2.go = "int_quests";
			link.l3 = LinkRandPhrase("Can you tell me something interesting?",
				"What's new in the City?", "Eh, I'd listen the latest gossip...");
			link.l3.go = "rumours_LSC";
			link.l10 = "Nothing...";
			link.l10.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
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
				Link.l2 = "Thanks, I'd better do it myself'. I'll look for it.";
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
				Link.l3 = "You know, I don't want to ask anyone else. Goodbye.";
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
					link.l1 = RandPhraseSimple("Yeah, I see. Thank you, buddy.", "Thank you!");
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
					link.l1 = RandPhraseSimple("Yeah, I see. Thank you, buddy.", "Thank you!");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = "I'm listening to you carefully, "+ GetSexPhrase("buddy", "" + pchar.name + "") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Well, how are you doing after being in prison?";
				link.l1.go = "ansewer_1";
			}
			link.l10 = "No questions asked. Sorry, buddy...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Now I'm at my wife's beck and call. I gave my word not to drink anymore.";
			link.l1 = "And that's right, well done.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		//нерадивый муж Элис Тейлор
		case "InPrison":
			dialog.text = "Hey, "+ GetSexPhrase("buddy", "girlfriend") +"! Will you help me?";
			link.l1 = "Well, how can I help you?";
			link.l1.go = "InPrison_1";
		break;
		case "InPrison_1":
			dialog.text = "Tell my wife that I'm in trouble again!";
			link.l1 = "Who is your wife?";
			link.l1.go = "InPrison_2";
		break;
		case "InPrison_2":
			dialog.text = "Alice Taylor, "+ GetSexPhrase("friend", "girlfriend") +". She is the owner of the Ceres Smithy fluyt. And my name is Maxim Taylor.";
			link.l1 = "Nice to meet you, Maxim.";
			link.l1.go = "InPrison_3";
		break;
		case "InPrison_3":
			dialog.text = "Me too! Well, what are you going to do?";
			link.l1 = "If I see your wife, I will definitely let you know.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "2");
			pchar.questTemp.LSC.ElisHusband = "toElis";
			NextDiag.TempNode = "InPrison_wait";
		break;

		case "InPrison_wait":
			dialog.text = "Eh, "+ GetSexPhrase("friend", "girlfriend") +", you are my only hope to get out of here. Please find Alice as soon as possible...";
			link.l1 = "Okay.";
			link.l1.go = "exit";
		break;

		case "DontRemember":
			dialog.text = NPCStringReactionRepeat("What do you need, "+ GetSexPhrase("buddy", "girlfriend") +"?",
				""+ GetSexPhrase("Buddy", "Girlfriend") +"Is there anything else you want to know?",
				"I don't remember anything, total darkness in my mind.",
                ""+ GetSexPhrase("Buddy", "Girlfriend") +", you should get me out faster. You lift it up, the pipes are burning...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Your wife wants to get you out of here. Can you explain to me what you did to get here?",
				"No.",
                "Yeah...",
				"We'll have to be patient.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("DontRemember_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "DontRemember_1":
			dialog.text = "I don't remember anything...";
			link.l1 = "How? Nothing at all?";
			link.l1.go = "DontRemember_2";
		break;
		case "DontRemember_2":
			dialog.text = "Generally. I passed out in the tavern. They say that I went to the residence and ran over the admiral himself! The horror...";
			link.l1 = "Well, yes, you need to drink less.";
			link.l1.go = "DontRemember_3";
		break;
		case "DontRemember_3":
			dialog.text = "It is necessary. But it doesn't work out!";
			link.l1 = "Heh, well done!";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "6");
			pchar.questTemp.LSC.ElisHusband = "toAdmiral";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
