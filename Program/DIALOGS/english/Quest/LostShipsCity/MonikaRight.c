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
					dialog.text = "Hello! I'm glad to see you. You know, it seems that only you survived this terrible storm... Oh, I'm sorry, "+ GetSexPhrase("sir", "miss") +", my name is " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + ", at your service. Happy to welcome the hospitable hosts.";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Hello! I'm glad to see the new citizen. You know, in that terrible last storm, it seems only you survived... Oh, I'm sorry, "+ GetSexPhrase("sir", "miss") +", my name is " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + ", at your service. Happy to welcome the hospitable hosts.";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Do you need something, "+ GetSexPhrase("sir", "miss") +"?";
				link.l1 = "You know, I'm looking for someone. Will you help me?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I wanted to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I'd listen the latest gossip...");
				link.l3.go = "rumours_LSC";
				//покупка карты
				sld = characterFromId("LSC_Trader");
				if (CheckAttribute(sld, "quest.takeMap") && sld.quest.takeMap == "notTrade" && sld.quest.takeMap != "discount")
				{
					link.l4 = "You have no idea what a greedy and selfish person Eric Yost is!";
					link.l4.go = "takeMap";
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
			dialog.text = "You know, giving shelter to anyone in a storm is our responsibility. However, I always do it with great pleasure.";
			link.l1 = "This is very commendable.";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "You know, we're already in a cage in the City. That's why I'm always happy to meet new people.";
			link.l1 = "I'm also pleased to meet a nice man. I understand that the City is sparsely populated.";
			link.l1.go = "FT_2";
		break;

		case "FT_1":
			dialog.text = "You know, the weather is good now. But sometimes I'm even glad that a storm starts and people caught on Velasco stay with me to wait out the bad weather. There is someone to talk to...";
			link.l1 = "Yeah, you don't have many people here.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "What can I say, the longing can be mortal... Well, how did you get to us? Tell me.";
			link.l1 = "My ship crashed and I lost whole team. Unfortunately... Although, on the other hand, I was also lucky.";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Um... It sounds a bit sacrilegious, but you're really lucky.";
			link.l1 = "Yes, I understand that.";
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
				link.l1 = "Listen, what kind of island is this?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l2 = "How long have you been here?";
				link.l2.go = "ansewer_2";
			}
			link.l10 = "I have no questions for you, I'm sorry.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Welcome to the City of Abandoned Ships, that's the name of this island.";
			link.l1 = "Understood.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Not that long ago. However, I was bored to death by all this.";
			link.l1 = "I understand...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Oh my God, is this not a dream?";
			link.l1 = "This is reality...";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "My God, it's finally happened! Can I sail away from here?";
			link.l1 = "Yes, if you hurry up.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "I'm ready for anything. What should I do?";
			link.l1 = "Go to the San Gabriel. Henrik Wedeker will take you to my ship. And don't hesitate!";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Okay, I'll be on 'San Gabriel' soon.";
			link.l1 = "Please, hurry up...";
			link.l1.go = "SeekCrew_all";
		break;
		//квест получения карты
		case "TakeMap":
			dialog.text = "What's wrong with you?";
			link.l1 = "You know, he literally wants to rob me!";
			link.l1.go = "TakeMap_1";
		break;
		case "TakeMap_1":
			dialog.text = "It can't be.";
			link.l1 = "Well, without putting a knife to your throat, of course. This Eric Yost of yours wants to sell me a map of the City for an incredible price!";
			link.l1.go = "TakeMap_2";
		break;
		case "TakeMap_2":
			dialog.text = "Well, that's okay. If you have something to sell, you have the right to set any price for the goods. And Eric is also in his right.";
			link.l1 = "Well, that's a pretty right...";
			link.l1.go = "TakeMap_3";
		break;
		case "TakeMap_3":
			dialog.text = "So, do you really need this map? Are you completely lost without her?";
			link.l1 = "Yes, it's a bit heavy...";
			link.l1.go = "TakeMap_4";
		break;
		case "TakeMap_4":
			dialog.text = "Well, I'll help you. After all, the Lord requires us to be merciful to our neighbor. Come to Eric tomorrow, I will tell him to reduce the price of this map to a divine one.";
			link.l1 = "And will he listen to you?";
			link.l1.go = "TakeMap_5";
		break;
		case "TakeMap_5":
			dialog.text = "Without a doubt.";
			link.l1 = "Thank you very much!";
			link.l1.go = "exit";
			sld = characterFromId("LSC_Trader");
			sld.quest.takeMap = "discount";
			sld.quest.takeMap.name = GetFullName(npchar);
		break;
	}
	NextDiag.PrevNode = NodeName;
}
