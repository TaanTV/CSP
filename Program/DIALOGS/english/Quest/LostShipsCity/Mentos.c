
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

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
					dialog.text = LinkRandPhrase("Ha, new citizen! I guess the storm won't stop us from getting to know each other. I am " + GetFullName(npchar) + ", I belong to the local militia.",
						"So you're the only one who survived in the storm? Well, welcome to the City. My name is " + GetFullName(npchar) + ", I work in the police.",
						"I see new citizen! Welcome, as they say, but you can already ignore the storm. My name is " + GetFullName(npchar) + ", I am registered in the local militia.");
					link.l1 = RandPhraseSimple("Hi, I'm " + GetFullName(pchar) + ". What kind of police?", "Greetings. My name is " + GetFullName(pchar) + ". And what kind of militia is this?");
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ha, new citizen! Well, hello and let's get acquainted. I am " + GetFullName(npchar) + ", I am a member of the local militia.",
						"So you're the only one who survived in the storm? Well, welcome to the City. My name is " + GetFullName(npchar) + ", I work in the police.",
						"I see a new citizen of the City! Welcome, as they say. My name is " + GetFullName(npchar) + ", I am registered in the local militia.");
					link.l1 = RandPhraseSimple("Hi, I'm - " + GetFullName(pchar) + ", what kind of police?", "Greetings. My name is " + GetFullName(pchar) + ", and what kind of militia is this?");
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Is there a crime somewhere?", "What's the matter, is there a riot in the City?", "Has something happened?");
				link.l1 = RandPhraseSimple("Listen, I'm looking for someone. Do you know where he is now?", "I need to find someone. Have you seen him anywhere nearby?");
				link.l1.go = "SeekCitizen";
				link.l2 = RandPhraseSimple("I want to ask you a question.", "I have a question for you.");
				link.l2.go = "int_quests";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.additional.powder") && sti(pchar.questTemp.LSC.additional.powder))
				{
					link.l8 = "Listen, I really need gunpowder and weapons. The Admiral doesn't want to give me anything, but I really need...";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew" && npchar.id == "Ment_6" && !CheckAttribute(pchar, "questTemp.LSC.crew.ment_6"))
				{
					link.l8 = "Hello, my friend. Well, the time has come. We're leaving.";
					link.l8.go = "SeekCrew";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew" && npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.crew.ment_6"))
				{
					link.l8 = "Well, how are you?";
					link.l8.go = "SeekCrew2";
				}
				if (pchar.questTemp.LSC == "MechanicIsArrest_toResidence" && npchar.id == "Ment_6" && CheckAttribute(npchar, "quest.LSCofficer"))
				{
					link.l8 = "Well, buddy, it looks like the time has come.";
					link.l8.go = "SeekCrew3";
				}
				if (pchar.questTemp.LSC == "MechanicIsArrest_toResidence" && npchar.id == "Ment_6" && !CheckAttribute(npchar, "quest.LSCofficer"))
				{
					link.l8 = "Buddy, we were talking about how you want to leave this damn island with me.";
					link.l8.go = "SeekCrew4";
				}
				link.l10 = "No, it's fine.";
				link.l10.go = "exit";
			}
		break;

		case "FT_1":
			dialog.text = LinkRandPhrase("The police ensures order and compliance with the Law by the citizens of the City.",
				"The police are watching everything that is happening here. In general, this is the power in the City...",
				"In ordinary cities there is a governor with a garrison of soldiers. Here, the governor is our admiral, and the garrison is us, the militiamen.")
			link.l1 = RandPhraseSimple("I see...", "Now I see, thanks for the clarification.");
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
			dialog.text = LinkRandPhrase("I'm listening to you carefully, "+ GetSexPhrase("buddy", "citizen") +".", "Speak, I'm listening.", "I'm listening carefully.");
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = LinkRandPhrase("Listen, what kind of island is this?", "What kind of island is this strange?", "Listen, buddy, what kind of island is this?");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = LinkRandPhrase("Have you tried to get out of here?", "Maybe there is an opportunity to get out of this place?", "Have you tried to sail away from here?");
				link.l2.go = "ansewer_2";
			}
			link.l10 = RandPhraseSimple("No questions asked. Sorry, buddy...", "Something slipped my mind, I forgot...");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = LinkRandPhrase("This island is called the City of Abandoned Ships. You are now a citizen of this City.",
				"It's a very unusual place, isn't it? The island is called the City of Abandoned Ships. Now you're going to live with us.",
				"This Is The City of Abandoned Ships. The whole island consists of ships that were brought here by a difficult...");
			link.l1 = RandPhraseSimple("Clear.", "Clear...");
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = LinkRandPhrase("Why? We are well fed here...",
				"This is prohibited by law. Actually, I personally don't want to, everything suits me here.",
				"You know, everything I wanted to get out of life is here. Why should I look for a better life?");
			link.l1 = RandPhraseSimple("Clear.", "Clear...");
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l2 = true;
		break;
		//диалог перед боем на Веласко
		case "OffNarval":
			dialog.text = LinkRandPhrase("We are ready to attack, lead on.", "We have been waiting for you already... Well, come on, don't delay.", "Let's send these 'narwhals' to hell!");
			link.l1 = "Good!";
			link.l1.go = "exit";
		break;
		//диалог после боем на Веласко
		case "AffterFightN":
			dialog.text = LinkRandPhrase("We did it!", "Hehe, the admiral will be pleased...", "That's it, the Narwhal clan no longer exists!");
			link.l1 = "I won't keep you any longer.";
			link.l1.go = "exit";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Why do you need gunpowder and weapons? It's a dead weight here.",
				"It's all been decided.",
				"I'll do everything.",
                "Oh, you're so annoying.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Here, yes. But there are places where these goods are needed.",
				"Great!",
                "Oh, yeah.",
				"Yeah.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "For example, in swimming?";
			link.l1 = "Hmm... well, let's say.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Understood... You know, I'll help you if you take me with you.";
			link.l1 = "Agree, especially since I just need good company.";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "Okay. I can sneak a lot out of the warehouse... How many weapons and gunpowder do you need, and where do you want it delivered?";
			link.l1 = "I need 10 centners of gunpowder and 50 weapons. We need to get this to the San Gabriel barque.";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = "Okay, I'll do it. Don't forget to pick me up later!";
			link.l1 = "No way, it's in my best interest, buddy. Goodbye.";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_WEAPON, 50);
			AddCharacterGoods(pchar, GOOD_POWDER, 200);
			AddQuestRecord("ISS_MainLine", "58");
			pchar.questTemp.LSC.additional.powder = false;
		break;
		//поиски команды на корвет
		case "SeekCrew":
			dialog.text = "Great! When?";
			link.l1 = "I'm just putting a crew on the ship right now, so welcome. Go to the San Gabriel. Henrik Wedeker, who is there, will transfer you to my ship.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Yes, that would be nice. But you know, I'll wait here for now.";
			link.l1 = "Why?";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "The Admiral is very unhappy with you. I think he's getting ready to kill you. So I'll wait here, see what happens next. If you get into trouble with Chad, I can cover your back.";
			link.l1 = "Yes, that would be nice. You know, buddy, when all this is over, I want to take you on board my ship as an officer. I guarantee a monthly salary.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Interesting suggestion. I think I'll agree. Well, in the meantime, we need to try to make sure that 'all this' ends well for us.";
			link.l1 = "That's right! Well, wait here.";
			link.l1.go = "exit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.LSC.crew.ment_6 = true;
			npchar.quest.LSCofficer = true;
			AddQuestRecord("ISS_MainLine", "61");
		break;

		case "SeekCrew2":
			dialog.text = "Everything is fine so far, but keep your eyes open! If there's a fight, I'll come to the rescue.";
			link.l1 = "Great! Thank you.";
			link.l1.go = "exit";
		break;

		case "SeekCrew3":
			dialog.text = "I'm ready. Come into the residence, I'll go there a little later.";
			link.l1 = "Agreed!";
			link.l1.go = "exit";
		break;

		case "SeekCrew4":
			dialog.text = "Yes, it is. And what do you say?";
			link.l1 = "If you help me now, then I'm ready to take you as an officer with a decent monthly salary. We're leaving, and I need your help right now.";
			link.l1.go = "SeekCrew4_1";
		break;
		case "SeekCrew4_1":
			dialog.text = "I agree. How can I help you?";
			link.l1 = "Apparently, there is going to be a serious mess at the residence right now. If you come out on my side, then it's a deal.";
			link.l1.go = "SeekCrew4_2";
		break;
		case "SeekCrew4_2":
			dialog.text = "Hmm, the admiral is a serious fighter. But I'm willing to take the risk!";
			link.l1 = "Great! Then let's agree like this: Wait here, but if a fight starts, then join the fight immediately.";
			link.l1.go = "SeekCrew4_3";
		break;
		case "SeekCrew4_3":
			dialog.text = "Okay. I won't let you down, Captain.";
			link.l1 = "Well, that's nice...";
			link.l1.go = "exit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ref ment = CharacterFromID("Ment_5");
			ment.model = "officer_8";
			FaceMaker(ment);
			npchar.quest.LSCofficer = true;
			AddQuestRecord("ISS_MainLine", "68");
		break;
		//финальный разговор мента_6 перед посадкой на корвет
		case "MentOffIsLife":
			dialog.text = "Well, it looks like we've fought back.";
			link.l1 = "Yes... Thank you, my friend, you kept your word. I owe you one.";
			link.l1.go = "MentOffIsLife_1";
		break;
		case "MentOffIsLife_1":
			Npchar.quest.OfficerPrice = (rand(4)+1)*1000;
			dialog.text = "No problem. I'm ready to join your team as an officer. What will you offer me?";
			link.l1 = "Buddy, this is not the time to trade. Set your own salary, then we'll figure it out...";
			link.l1.go = "MentOffIsLife_2";
		break;
		case "MentOffIsLife_2":
			dialog.text = "Okay, whatever you say...";
			link.l1 = "Listen, the Admiral has arrested the Mechanic. Do you know where he is?";
			link.l1.go = "MentOffIsLife_3";
		break;
		case "MentOffIsLife_3":
			dialog.text = "In prison, of course. He was sent to Tartarus.";
			link.l1 = "Thank you, you helped me a lot. Now go to the San Gabriel, there is an opportunity to get on my ship. The rest of the citizens of the City who wanted to leave with me are already there. Wait for Vedeker and me.";
			link.l1.go = "MentOffIsLife_4";
		break;
		case "MentOffIsLife_4":
			dialog.text = "All right, Captain. I'll just look around here for a bit...";
			link.l1 = "Okay, but don't be late for the ship.";
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			DialogExit();
			DeleteAttribute(npchar, "city");
			chrDisableReloadToLocation = false;
			AddQuestRecord("ISS_MainLine", "66");
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.greeting = "Gr_questOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;  // Контузия
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;

		break;
	}
	NextDiag.PrevNode = NodeName;
}
