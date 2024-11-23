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
					dialog.text = "Congratulations to the newcomer, now is the time. I am " + GetFullName(npchar) + ", they also call me Happy here.";
					link.l1 = "Well, hello, " + npchar.name + ". My name is " + GetFullName(pchar) + ", let's get acquainted. What does 'on time' mean?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Congratulations to the newcomer. I am " + GetFullName(npchar) + ", they also call me Happy here.";
					link.l1 = "Well, hello, " + npchar.name + ". My name is " + GetFullName(pchar) + ", let's get acquainted.";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				//квест отнести бутылочку вина тюремщику. дача квеста
				if (!CheckActiveQuest("TakeVineToPrisoner") && !CheckAttribute(pchar, "questTemp.LSC.LegroHelp"))
				{
					dialog.text = "Hey, "+ GetSexPhrase("buddy", "girlfriend") +"I have business with you.";
					link.l1 = "Spit it out.";
					link.l1.go = "GiveVineBottle";
					break;
				}
				dialog.text = "What did you want, "+ GetSexPhrase("sir", "miss") +"?";
				link.l1 = "Listen, I'm looking for someone. Do you know where he is now?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I want to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the lastest gossip...");
				link.l3.go = "rumours_LSC";
				//квест доставки вина тюремщику. после разговора с Бойлом
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toFackDominic")
				{
					link.l7 = "You know, I'll give a bottle of wine to Thomas Boyle.";
					link.l7.go = "FackDominic";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toArmoDominic")
				{
					link.l7 = "Buddy, didn't you flirt with Armo Dulin the other day?";
					link.l7.go = "ArmoDominic";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toKeyDominic")
				{
					link.l7 = "Well, I've fixed everything with Thomas Boyle.";
					link.l7.go = "KeyDominic";
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
					link.l8 = "You know, I'm typing a command to get out of here. I suggest you come with me.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Nothing...";
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = "The storm subsides, and all the lucky ones crawl out of the water.";
			link.l1 = "Understood. Well, you're one of them too!";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "That's true, but I'm an absolute lucky guy. The fact is that my ship crashed at the peak of the storm!";
			link.l1 = "Wow, wow! Tell me, please.";
			link.l1.go = "FT_3";
		break;
		case "FT_1":
			dialog.text = "Well, it's very nice.";
			link.l1 = "Why are you called Happy?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "There are more than enough reasons for this. I escaped from a shipwreck, like most locals, but my wreck was special...";
			link.l1 = "And what was special about your crash?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Ha, it was just a hell of a wreck, damn it! Lightning struck our frigate, and a fire started instantly, after which the fire somehow very quickly made its way into the powder magazine\n"+
				"Just imagine! The ship turned into a pile of burning wreckage in a matter of minutes, and I didn't even get burned! Moreover, I was not far from the hold at the time of the disaster, and I did not come to the City empty–handed at all - I had jewelry, money, rare artifacts...";
			link.l1 = "Did the Admiral confiscate all this?";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "The Admiral is an extremely quick–witted greedy bastard, but I can cheat any crook. I was informed about the upcoming meeting with Capper in advance, and I managed to take measures, so to speak. Although, for what reason I got these trinkets here, I don't understand myself...";
			link.l1 = "Hmm... listen, what kind of measures did you take? It's very interesting to find out...";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "I won't say, "+ GetSexPhrase("buddy", "girlfriend") +"I'm sorry. My happiness is only mine, I'm afraid to lose it. I'm superstitious.";
			link.l1 = "Yeah, that's for sure. What are you doing here?";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "Nothing! There is no way back, and therefore I do not want to look for it. I'm just living for today... and I love it, damn it!";
			link.l1 = "Well, this is also a position. Thanks for the conversation... listen, maybe you'll change your mind and tell me about the measures?";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "Sorry, "+ GetSexPhrase("buddy", "" + pchar.name + "") +", it is impossible in any way. I can only hint that everything needs to be put somewhere before meeting with Chad... That's all.";
			link.l1 = "Understood... Well, thanks for that, too.";
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
					dialog.text = GetFullName(sld) + ", are you talking about him?";
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
			dialog.text = "I'm listening to you carefully, "+ GetSexPhrase("buddy", "" + pchar.name + "") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "I understand that storms are common here.";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Is it possible here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "How are personal problems solved in the city? Are the people here so law-abiding that they don't start fights and kill each other?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "There is a chance to swim... Somewhere?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l5 = "Listen, have you been here long?";
				link.l5.go = "ansewer_5";
			}
			link.l10 = "No questions asked. Sorry, buddy...";
			link.l10.go = "exit";
		break;
		case "ansewer_4":
			dialog.text = "Yes, I wouldn't say that. It's just that no matter what the storm, it's a living hell! Everything creaks and wobbles... It's a little scary, in general.";
			link.l1 = "Understood.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_1":
			dialog.text = "You can do anything that is not prohibited by Law. May... Just be careful.";
			link.l1 = "I'll take it into account.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "Anything happens, of course. Chad and his militia can calm anyone down. It is simply announced that the citizen has gone mad - and that's it.";
			link.l1 = "Not bad... Is it really blowing people's towers off?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "It happens...";
			link.l1 = "Clear. Well, how do the rest of the people deal with each other?";
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = "On the sly. Sometimes, some people disappear without a trace, they sin against the clans... In general, not caught is not a thief.";
			link.l1 = "Uh-huh, I see...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Of course"+ GetSexPhrase(", buddy", "") +"! Straight to hell!";
			link.l1 = "Thank you.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_5":
			dialog.text = "Well, that's how to say it. For some, a year here is an eternity...";
			link.l1 = "So you've been living here for a year?";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "No, more. I put it figuratively about the year.";
			link.l1 = "Understood. Has Hill Brunner been here yet?";
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = "Was. It's a pity for Hill, he was a good innkeeper. No matter how you go to him, he has everything in stock. Oh, it's a pity...";
			link.l1 = "Okay, be healthy.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("What kind of goods?",
				"You already asked about this.",
				"You already asked...",
                "You already asked me about these goods. I don't know anything!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I need kernels, bombs, knippels, food, medicines, gunpowder, weapons...",
				"Yeah... Sorry, I forgot.",
                "Oh, yeah.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Well, the kernels can be begged from the housewives of the houses. They have a lot of such goods unattended. I recommend asking our holy father for medicines. But weapons and gunpowder are the admiral's business...";
			link.l1 = "How to understand?";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Well, he collects weapons and gunpowder from all the ships. So he has all the supplies.";
			link.l1 = "I understand, thank you.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "K-he.. I was stunned by, however...";
			link.l1 = "I understand. But make a decision quickly. If you agree, then you need to get poisoned on my ship right now.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Immediately?";
			link.l1 = "Yes. A storm is approaching the City, which will most likely destroy the island. We need to hurry.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Heh, I'm lucky again! I agree.";
			link.l1 = "Excellent. Now go to the San Gabriel, where the Mechanic will arrange a transfer to my ship.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Okay. I'll just drop by to pack my things.";
			link.l1 = "Don't be late.";
			link.l1.go = "SeekCrew_all";
		break;
		//отнести бутылку вина тюремщику
		case "GiveVineBottle":
			dialog.text = "I have a friend, Thomas Boyle, a jailer. He sits on this damn Tartarus all day long, as if he's behind bars.I want to please him.";
			link.l1 = "Great. How can I help you?";
			link.l1.go = "GiveVineBottle_1";
		break;
		case "GiveVineBottle_1":
			dialog.text = "Listen, get a bottle of wine somewhere and take it to him from me. Thomas will be surprised!";
			link.l1 = "Buddy, are you crazy? What do you think I am, "+ GetSexPhrase("boy", "girl") +"running errands?";
			link.l1.go = "GiveVineBottle_not";
			link.l2 = "Okay, I'll do it.";
			link.l2.go = "GiveVineBottle_2";
		break;
		case "GiveVineBottle_not":
			dialog.text = "Don't get so worked up. If you don't want to, don't...";
			link.l1 = "Don't bother me with such idiotic suggestions from now on!";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "over";
			CloseQuestHeader("TakeVineToPrisoner");
		break;
		case "GiveVineBottle_2":
			dialog.text = "Well, thank you, "+ GetSexPhrase("buddy", "" + pchar.name + "") +". Thomas will be so happy!..";
			link.l1 = "I hope so.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toTomasBoil";
			AddQuestRecord("TakeVineToPrisoner", "1");
		break;

		case "FackDominic":
			dialog.text = "Great! I can imagine how glad he was...";
			link.l1 = "He was satisfied with the wine, but he asked me to tell you that he would cut off his ears on the move. They'll cut it off for you.";
			link.l1.go = "FackDominic_1";
		break;
		case "FackDominic_1":
			dialog.text = "For me? For what?!!";
			link.l1 = "I have no idea. But he's very angry with you.";
			link.l1.go = "FackDominic_2";
		break;
		case "FackDominic_2":
			dialog.text = "Wow!Listen, go to him again, please. Find out what happened!";
			link.l1 = "Go and find out for yourself.";
			link.l1.go = "FackDominic_3";
		break;
		case "FackDominic_3":
			dialog.text = "Damn, I'm scared. I think he'll give me a hard time first, and then he'll figure it out. Go and ask what's the matter, I beg you very much!";
			link.l1 = "Okay, so be it, I'll ask.";
			link.l1.go = "FackDominic_4";
			link.l2 = "The hell with it! What am I to you, "+ GetSexPhrase("boy", "girl") +"running errands?";
			link.l2.go = "GiveVineBottle_not";
		break;
		case "FackDominic_4":
			dialog.text = "Thank you, "+ GetSexPhrase("buddy", "" + pchar.name + "") +"! I swear I have absolutely no idea what's going on here.";
			link.l1 = "I believe you.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toSecondToPrison";
			AddQuestRecord("TakeVineToPrisoner", "3");
		break;

		case "ArmoDominic":
			dialog.text = "Well, I talked to her the other day. Flirting is out of the question! It's like I don't know whose young lady she is.";
			link.l1 = "Whose young lady is she?";
			link.l1.go = "ArmoDominic_1";
		break;
		case "ArmoDominic_1":
			dialog.text = "Thomas Boyle, of course. I'm not such an idiot to mess around with his girlfriend under my friend's nose!";
			link.l1 = "I suppose so. It would be an obvious overkill...";
			link.l1.go = "ArmoDominic_2";
		break;
		case "ArmoDominic_2":
			dialog.text = ""+ GetSexPhrase("Buddy", "" + pchar.name + "") +", do me one more favor.";
			link.l1 = "Again?";
			link.l1.go = "ArmoDominic_3";
		break;
		case "ArmoDominic_3":
			dialog.text = "Hmm, well, yes... Go to Thomas again, convince him that I was slandered.";
			link.l1 = "By the way, who could have done this?";
			link.l1.go = "ArmoDominic_4";
		break;
		case "ArmoDominic_4":
			dialog.text = "Yes, anyone in the tavern! When I was talking to Armo, half the city was sitting there.";
			link.l1 = "Oh... Well, then, I'll try to convince Thomas of your innocence.";
			link.l1.go = "ArmoDominic_5";
		break;
		case "ArmoDominic_5":
			dialog.text = "Thank you"+ GetSexPhrase(", buddy", "") +"!";
			link.l1 = "You're welcome.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "to3ToPrison";
			AddQuestRecord("TakeVineToPrisoner", "5");
		break;

		case "KeyDominic":
			dialog.text = "Great! What did he say?";
			link.l1 = "He apologizes to you for his inappropriate behavior.";
			link.l1.go = "KeyDominic_1";
		break;
		case "KeyDominic_1":
			dialog.text = "This is Thomas, I recognize a friend"+ GetSexPhrase("Buddy", "" + pchar.name + "") +", I am eternally grateful to you!";
			link.l1 = "Listen, can't endless gratitude be converted into something more tangible?";
			link.l1.go = "KeyDominic_2";
		break;
		case "KeyDominic_2":
			dialog.text = "I don't even know what I can give you, that's what! I'm giving you the key to the chests. I think you'll need it.";
			link.l1 = "I suppose so.";
			link.l1.go = "KeyDominic_3";
		break;
		case "KeyDominic_3":
			dialog.text = "Well, that's great! Thank you again.";
			link.l1 = "You're welcome, why...";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "key1");
			pchar.questTemp.LSC.LegroHelp = "over";
			AddQuestRecord("TakeVineToPrisoner", "7");
			AddQuestUserData("TakeVineToPrisoner", "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader("TakeVineToPrisoner");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
