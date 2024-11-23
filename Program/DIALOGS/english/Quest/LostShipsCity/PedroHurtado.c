#include "DIALOGS\english\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

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
					dialog.text = "Yeah, so you came out of the storm? Well, that's great! Let's get acquainted. My name is " + GetFullName(npchar) + ", and yours?";
					link.l1 = "My name is " + GetFullName(pchar) + ".";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "Yeah, so are you from the last replenishment? I see... Well, let's get acquainted. My name is " + GetFullName(npchar) + ", and yours?";
					link.l1 = "My name is " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				//квест проникновения в дом хозяина магазина
				if (pchar.questTemp.LSC != "AdmiralIsWaiting" && !CheckAttribute(npchar, "quest.store"))
				{
					dialog.text = ""+ GetSexPhrase("Buddy","Girlfriend") +", would you like to do something?";
					link.l1 = "Tell me what the deal is.";
					link.l1.go = "StBegin_1";
					break;
				}
				// <-- квесты
				dialog.text = "You wanted something?";
				link.l1 = "Listen, I'm looking for someone. Do you know where he is now?";
				link.l1.go = "SeekCitizen";
				link.l2 = "I want to ask you a question.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Can you tell me something interesting?",
					"What's new in the City?", "Eh, I would listen the latest gossip...");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.store") && npchar.quest.store == "waiting" && npchar.chr_ai.type == LAI_TYPE_STAY)
				{
					link.l4 = "Well, I'm ready togo through this terrifying door.";
					link.l4.go = "StStart_1";
				}
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Listen, I'm looking for some goods here.";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "You know, I'm typing a command to get out of here. I suggest you come to me as a sailor.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Nothing...";
				link.l10.go = "exit";
			}
		break;

		case "FS_1":
			dialog.text = "Very nice. Don't pay attention to the storm, it will end soon. The people here are friendly, so become citizens of the "+ GetSexPhrase("other","coy") +" City and everything will be fine. In general, welcome to the City!";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "Very nice. Well, get used to it a little bit. The people here live quite amicably, so welcome to the City, as they say...";
			link.l1 = "Thank you.";
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
			dialog.text = LinkRandPhrase("Thief!!! Violation of the Law of the City!", "Wow! As soon as I looked at it, you went straight into the chest with your head! You violated the Law!", "Police! Robbery!!! Hold "+ GetSexPhrase("his","her") +"!");
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
			dialog.text = LinkRandPhrase("Listen, you should put the gun away. And then you get a little nervous...", "You know, it's not customary to swing a saber here. Put the weapon away.", "Listen, what are you, like three Musketeers, running around here, waving a sword? Put away your weapon, it doesn't suit your face "+ GetSexPhrase("serious man","girl") +"...");
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
				dialog.text = NPCharSexPhrase(NPChar, "Careful on turns, "+ GetSexPhrase("buddy","girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like when "+ GetSexPhrase("men","all sorts") +" walk in front of me with weapons at the ready. It scares me...");
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
				Link.l2 = "Thanks, I'll better look for it myself.";
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
			dialog.text = "I'm listening to you. Ask whatever your heart desires.";
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "Damn storm! Do you often have this?";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "What kind of island is this?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "What is worthy of attention in the city?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "How did you get here yourself?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "I've heard it more than once on the Mainland . Isn't this your City, by any chance?";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l6 = "Listen, have you been living in the City for a long time?";
				link.l6.go = "ansewer_6";
			}
			link.l10 = "No questions asked. Sorry, buddy...";
			link.l10.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = "It happens, of course... By the way, you need to talk to Admiral Chad Capper if you haven't done so by now.";
			link.l1 = "Understood.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_1":
			dialog.text = "This is the City of Abandoned Ships, "+ GetSexPhrase("buddy","" + pchar.name + "") +". All those who managed to escape from shipwrecks live here. Now you are.";
			link.l1 = "Yes, now I am... Listen, why is this happening here? Is there any explanation for all these crashes?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "No one knows for sure. Ships seem to be hitting the reefs. Well, they are carried to the reefs by the current... But it's just a guess. No one knows for sure.";
			link.l1 = "And no one has tried to find out?";
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = "We tried, of course. Only this idea is bad - especially curious people die. So I don't advise you to be too quick either. Either you die, or you are screw loose...";
			link.l1 = "Yeah, funny prospects...";
			link.l1.go = "ansewer_1_3";
		break;
		case "ansewer_1_3":
			dialog.text = "Once I got there, then accept and live like everyone else. Here's my advice for you.";
			link.l1 = "Well, thanks for the advice.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "First of all, you need to come to the Admiral of the City as soon as possible, if you haven't been there yet. Well, then you can visit the tavern and the store. There is also a church.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "Yes, just like everyone else - through shipwreck"+ GetSexPhrase(", buddy","") +"...";
			link.l1 = "Understood.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4":
			dialog.text = "I don't know... In general, "+ GetSexPhrase("buddy","" + pchar.name + "") +", this is your City now, not just ours.";
			link.l1 = "Ha, that's good!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_6":
			dialog.text = "A year and a half, no more.";
			link.l1 = "Clear...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l6 = true;
		break;
		//квест проникновения в кабинет хозяина магазина
		case "StBegin_1":
			dialog.text = "There is one place here where there is a lot of money...";
			link.l1 = "So what?";
			link.l1.go = "StBegin_2";
		break;
		case "StBegin_2":
			dialog.text = "I suggest we go there and pick them up. Then we'll split the income in half.";
			link.l1 = "I, in principle, do not mind. And where is this place?";
			link.l1.go = "StBegin_3";
		break;
		case "StBegin_3":
			dialog.text = "On the galleon 'Esmeralda'. This is where the store is, only in the other half of the ship. If we go there in the afternoon, we won't find the owner of the store, Eric Yost, but I can open the door.";
			link.l1 = "If the owner of the store is not there, and you can open the door, then why are you calling me? After all, you're losing half the money.";
			link.l1.go = "StBegin_4";
		break;
		case "StBegin_4":
			dialog.text = "Well, it's not that simple there. Eric hired three thugs, they live there permanently. I can't handle them myself, but you can.";
			link.l1 = "Heh, now it's clear...";
			link.l1.go = "StBegin_5";
		break;
		case "StBegin_5":
			dialog.text = "Well, do you agree?";
			link.l1 = "Well, you can try. Let's do this thing, I can use the money.";
			link.l1.go = "StBegin_6";
			link.l2 = "No, I'm not interested. Stealing, you know...";
			link.l2.go = "StBegin_not";
		break;
		case "StBegin_not":
			dialog.text = "Well, as you know, "+ GetSexPhrase("buddy","girlfriend") +"...";
			link.l1 = "Yeah, Goodbye.";
			link.l1.go = "exit";
			npchar.quest.store = "over";
		break;
		case "StBegin_6":
			dialog.text = "Great! So, let's agree in this way. You go about your business now, as soon as you're ready - go to the Esmeralda, in the afternoon I will be waiting for you there on the quarterdeck next to the door over which the skull is nailed. We'll figure out what's what...";
			link.l1 = "Agreed.";
			link.l1.go = "exit";
			pchar.quest.LCS_SetPedroHurtado.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LCS_SetPedroHurtado.win_condition.l1.location = pchar.location;
			pchar.quest.LCS_SetPedroHurtado.function = "LCS_SetPedroHurtado";
			npchar.quest.store = "waiting";
			AddQuestRecord("ISS_takeStoreMoney", "1");
		break;
		case "StStart_1":
			dialog.text = "Great! Well, then, am I opening up?";
			link.l1 = "Yes, open it.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_PedroRunOpenDoor");
		break;
		case "StStart_Opened":
			dialog.text = "The door is open, you can go through.";
			link.l1 = "Great! What are you going to do yourself?";
			link.l1.go = "StStart_3";
		break;
		case "StStart_3":
			dialog.text = "I'll wait for you here, outside.";
			link.l1 = "Okay, wait.";
			link.l1.go = "exit";
			NextDiag.TempNode = "StResult";
			npchar.quest.store.money = pchar.money;
			AddQuestRecord("ISS_takeStoreMoney", "2");
			AddQuestUserData("ISS_takeStoreMoney", "sSex", GetSexPhrase("cя","ась"));
			AddDialogExitQuestFunction("LSC_PedroGoWaiting");
		break;
		case "StResult":
			dialog.text = "Well, "+ GetSexPhrase("buddy","girlfriend") +", the job is done, as I see?";
			link.l1 = "Yes, everything is fine, I killed three guards.";
			link.l1.go = "StResult_1";
		break;
		case "StResult_1":
			dialog.text = "Well, I didn't expect anything else. The fact that you "+ GetSexPhrase("are a good warrior","fight well") +" is visible from half a glance... And now let's share the loot.";
			if (sti(pchar.money) <= sti(npchar.quest.store.money))
			{
				link.l1 = "Listen, I didn't find anything. There was no money. I searched everything, but the money wasn't found.";
				link.l1.go = "StResult_2";
			}
			else
			{
				npchar.quest.store.money = sti(pchar.money) - sti(npchar.quest.store.money); //чистая выручка
				link.l1 = "I found " + FindRussianMoneyString(sti(npchar.quest.store.money)) + " in total. Half is yours, as we agreed.";
				link.l1.go = "StResult_3";
			}
		break;
		case "StResult_2":
			dialog.text = "Yeah, I didn't expect this outcome... Well, come on. Money is like dirt here, I'll get it somewhere else...";
			link.l1 = "Also true.";
			link.l1.go = "StResult_4";
			AddQuestRecord("ISS_takeStoreMoney", "3");
			AddQuestUserData("ISS_takeStoreMoney", "sSex", GetSexPhrase("ate","la"));
		break;
		case "StResult_3":
			dialog.text = "Well, that's great! I'm glad that everything ended so well... Well, sometimes, "+ GetSexPhrase("buddy","girlfriend") +". If there are problems, contact us.";
			link.l1 = "Absolutely.";
			link.l1.go = "StResult_4";
			AddMoneyToCharacter(pchar, -makeint(sti(npchar.quest.store.money)/2));
			AddQuestRecord("ISS_takeStoreMoney", "4");
			CloseQuestHeader("ISS_takeStoreMoney");
		break;
		case "StResult_4":
			npchar.quest.store = "over"; //флаг этого миниквеста
			LAi_SetLoginTime(npchar, 6.0, 21.99);
			LAi_SetLSCoutType(npchar);
			LAi_group_MoveCharacter(npchar, "TmpEnemy");
			SaveCurrentNpcQuestDateParam(npchar, "location");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("What kind of goods?",
				"You already asked about this.",
				"Already asked...",
                "You've already asked me about these goods. I don't know anything!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I need kernels, bombs, knippels, food, medicines, gunpowder, weapons...",
				"a.",
                "Oh, yeah.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Why do you need this?";
			link.l1 = "Just in case.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Well, bombs with cores, and other ammunition, can be obtained from the shipwrights. There's a lot of this stuff. But gunpowder and weapons are only the admiral's.";
			link.l1 = "Clear. Well, thank you.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "However!.. I'm behind the times.";
			link.l1 = "I'm waiting for a response.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = ""+ GetSexPhrase("Buddy","" + pchar.name + "") +", do you really have a ship that can sail away from here?";
			link.l1 = "Yes.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Then there's nothing to think about! I agree.";
			link.l1 = "Great! Go to the San Gabriel right now, where a Mechanic will ferry you to my ship.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Okay, I'll just get the stuff together quickly.";
			link.l1 = "Don't be late!";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
