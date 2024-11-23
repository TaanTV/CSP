#include "DIALOGS\english\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
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
					dialog.text = "Hello, "+ GetSexPhrase("sir", "miss") +". I am very glad that you managed to save yourself after this terrible disaster... Although, needless to say, we've all been through it. Yes, my name is " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + ", at your service, Miss...";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Hello, "+ GetSexPhrase("sir", "miss") +". I am very glad that you managed to save yourself after this terrible disaster... Although, needless to say, we've all been through it. Yes, my name is " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + ", at your service, Miss...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "What did you want, "+ GetSexPhrase("sir", "miss") +"?";
				link.l1 = "You know, I'm looking for someone. Will you help me?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I wanted to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the latest gossip...");
				link.l3.go = "rumours_LSC";
				link.l10 = "Nothing...";
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "FT_1":
			dialog.text = "Mrs. I'm married.";
			link.l1 = "Oh, I'm sorry...";
			link.l1.go = "exit";
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
				Link.l2 = "Thank you, but I'd rather do it myself. I'll look for it.";
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
					Link.l2 = "No, I had something else.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", have you talked about her?";
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
				link.l1 = "Listen, what kind of island is this?";
				link.l1.go = "ansewer_1";
			}
			link.l10 = "I have no questions for you, I'm sorry.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "How, you don't know yet? This Is the City of Abandoned Ships. And we are all lost people here... Oh, how tired I am of all this!";
			link.l1 = "I understand...";
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l1 = true;
		break;



		case "_1":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_2";
		break;
		case "_2":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_3";
		break;
		case "_3":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_4";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
