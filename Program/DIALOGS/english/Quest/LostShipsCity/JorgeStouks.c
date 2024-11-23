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
				dialog.text = "New faces! This is good, because apart from these terrible storms and entertainment, there are no such things. My name is " + GetFullName(npchar) + " and I am happy to be the first to welcome you to the City!";
				link.l1 = "Thank you for the warm welcome, although my arrival turned out to be somewhat muddied!.. My name is Captain " + GetFullName(pchar) + ".";
				link.l1.go = "FT_1";
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
		case "FT_1":
			dialog.text = "Captain, it looks like you are the only one who survived in this storm. I'm really sorry...";
			link.l1 = "Me too... What is this place, my friend?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "This is the City of Abandoned Ships.";
			link.l1 = "And not the Island of Justice?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Hmm, no... Although, you know, they say that at one time there was such a name. But I didn't find those days anymore.";
			link.l1 = "I see...";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Well, I consider it my duty, so to speak, to enlighten you about our City.";
			link.l1 = "I will gladly and gratefully listen to everything you have to say.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "The first thing you need to do upon arrival here is to obtain citizenship of the City. To do this, you need to report to the Admiral of the City, Chad Capper.";
			link.l1 = "To Chad Capper? This name seems familiar to me...";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "You will remember later, listen to the rest first... So, Chad Capper is the head of the City. This position is elective, so he came to power, so to speak, democratically. His duties include monitoring the implementation of the Law...";
			link.l1 = "...collect taxes...";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "What taxes? There are no taxes here, no one pays him anything, except for the initial payment...";
			link.l1 = "No taxes?!! Oh, my God! But it really is the Island of Justice...";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "Well, maybe so... I will continue. You need to report to the Admiral for registration as soon as possible. There's a storm right now, so there aren't many people on the decks. But as soon as it's over, Capper will find you anyway. And I advise you not to delay registration.";
			link.l1 = "Okay, I got that. And when do you think this storm will end?";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "Everything will definitely calm down by tomorrow evening. The storm has already subsided.";
			link.l1 = "Clear. What else do I need to know?";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = "The Admiral will tell you about the Law by which we all live in more detail, but I can describe its postulates in a nutshell.";
			link.l1 = "Very interesting!";
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = "So it is forbidden to kill citizens, steal from them, disassemble ships to build something to sail away from here...";
			link.l1 = "Stop! Does that mean I can't get out of here?!";
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = "Of course not! This is prohibited by Law!.. You know, I wouldn't want to go into these topics, it's none of my business. Go to the admiral, he will tell you everything.";
			link.l1 = "And where is it located?";
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = "On the ship 'San Augustine'. It's quite a long way from here, there's a bridge leading to the varship... I'm sorry, but I can't explain it more precisely, since you don't know the landmarks. Look for 'San Augustine'!";
			link.l1 = "Understood... Listen, did you know a man named Teaser Dan?";
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = "No, this name is unfamiliar to me.";
			link.l1 = "Yeah, I see... Well, thank you for the information.";
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = "You're welcome. I am always at your service, "+ GetSexPhrase("sir", "miss") +"... Wait, I almost forgot vital information!";
			link.l1 = "It's very nice to hear that.";
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = "Never go inside the barque 'San Gabriel' and the galleon 'Velasco'! The galleon Velasco is the ship we are currently standing on...";
			link.l1 = "Why?";
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = "You will be killed. These ships belong to the Narwhal and Casper clans. You can walk on them, but you can't go down!";
			link.l1 = "Hmm, well, I see. I'll keep that in mind. Thank you again for the warm welcome.";
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			AddQuestRecord("ISS_MainLine", "1");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("", "la"));
			pchar.JustGotIntoLSC = true;
			LAi_SetLSCoutTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
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
			dialog.text = "I'm listening to you carefully, "+ GetSexPhrase("buddy", "miss") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "This city... Where did he come from?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Have you lived here long yourself?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "How many people are dying here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4") && CheckCharacterItem(pchar, "keyQuestLSC"))
			{
				link.l4 = "Listen, do you know what Diffindur is?";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "What is interesting in your City? Except for Chad Capper's residence, of course...";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6"))
			{
				link.l6 = "How would I navigate here?";
				link.l6.go = "ansewer_6";
			}
			link.l10 = "No questions asked. I'm sorry...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Someone says that this is a natural formation that strangely attracts ships, while someone is sure that this place is cursed and will only grow due to more and more wrecks... It's hard to say, it's hard to isolate the truth from the general mass of gossip and fantasies.";
			link.l1 = "Well, what do you think?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Is my opinion important? Of course, no more and no less than the opinions of others.";
			link.l1 = "Also...?";
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = "Look around, listen... You can hear their voices, the moans and screams of thousands of dead sailors echo in you, in each of us. Walking along the deck, you can catch barely noticeable sounds, but with due attention to them, you realize that these are nothing but echoes of those days when the ship sailed the seas.";
			link.l1 = "What does it mean?";
			link.l1.go = "ansewer_1_3";
		break;
		case "ansewer_1_3":
			dialog.text = "The city is not only holding us back, Captain. He will captivate souls and time, he can deceive eternity.";
			link.l1 = "And I foolishly thought that it's Chad Capper holding us back...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "No, about three months. There was a night battle with pirates who captured a huge warship. Our captain was one of the desperate madmen, and therefore entered into a losing battle on the brig. Of course, with the very first broadside, the battleship swept away all living and not so much from our deck, including captain and half of the officers\n"+
				"I have never experienced anything like this before, I rushed to the deck and could barely get there through the wreckage of the mast and pieces of rigging... This is an incomparable sight, Captain. Although, you probably know that I"+
				"In general, not wanting to wait for the next volley, which would undoubtedly have killed me, the remaining sailors and the whole ship in general, I rushed overboard and, swimming to the nearest wreck of sufficient size, clung to it. Then I probably lost consciousness–I don't remember, but... I was here by morning.";
			link.l1 = "Exciting...";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Of course! It took my breath away so much that I almost peed in my pants... But it's all over now, and I really like it here. Calm, quiet, interesting.";
			link.l1 = "I see you're not the only one.";
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = "Of course. Why resist? At first, yes, everything seems hostile, I want to get away from this damn place, but... then everything will work out, believe me. You'll get used to it, just like the rest of us.";
			link.l1 = "Not sure that I like this addictive idea.";
			link.l1.go = "ansewer_2_3";
		break;
		case "ansewer_2_3":
			dialog.text = "And I'm not sure if anyone will ask you. I'm not the first, I'm not the last to tell you that it's better to immediately forget everything that happened to you before. Start a new life! You'll see, it's very nice here.";
			link.l1 = "Thanks for the advice, mister " + npchar.lastname + ".";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "More than. But even more have been arriving lately.";
			link.l1 = "Recently? Why?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "I don't know for sure, but it seems that the City has become known in the big world.";
			link.l1 = "Hmm, I heard there have been rumors about some kind of Island of Justice more than once. Probably, it was about the City...";
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = "Maybe. However, if this is the case, how did the rumors reach the cities of the Mainland?";
			link.l1 = "Heh, I don't know. But I really want to know...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = "Diffindur? Hm... Could it be one of the ships here, the Fernando Diffindur flutes?";
			link.l1 = "What kind of fluyt?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "A half-sunken ship, it has cracked in half and is miraculously holding on to the reef. No one lives there-it's too dangerous.";
			link.l1 = "Where is it located?";
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = "Exactly on the other side of the City. In general, I talked you to talk to the tavern owner about this, he knows everything here.";
			link.l1 = "Do you have a tavern too?";
			link.l1.go = "ansewer_4_3";
		break;
		case "ansewer_4_3":
			dialog.text = "The tavern, the church, and the store are just like people in an ordinary city! There is also a usurer named Augusto Brahms, but you should be careful with him...";
			link.l1 = "Ho, that's better!";
			link.l1.go = "int_quests";
			//AddQuestRecord("ISS_MainLine", "2");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "a"));
		break;
		case "ansewer_5":
			dialog.text = "Everything that is in an ordinary city is here - a church, a tavern, a shop. There is a person who lends money. But I'll tell you, it's the stupidest thing to do here.";
			link.l1 = "Why?";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "There is so much gold in the City that it has no practical value. People collect it out of habit rather than in the hope of using it.";
			link.l1 = "I don't understand, does anyone need money here?";
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = "No, why not? Money is money here too. But they are not as necessary as on the Mainland... In general, you will understand later.";
			link.l1 = "Hmm, I don't understand yet, but I hope it will come...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = "It will be difficult at first, but you will quickly figure out what's what.";
			link.l1 = "Well, yes, an encouraging statement... Well, is there a map of the City?";
			link.l1.go = "ansewer_6_1";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_6_1":
			dialog.text = "There is, I even saw one like it.";
			link.l1 = "Here! And where did you see her?";
			link.l1.go = "ansewer_6_2";
		break;
		case "ansewer_6_2":
			dialog.text = "In Eric Yost's store on the galleon 'Esmeralda'.";
			link.l1 = "I understand, thank you.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("What exactly, let me ask you?",
				"You've already asked about this.",
				"They've already asked...",
                "You have already asked me about these goods. I don't know anything!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Bombs, grapeshot, food, medicines, gunpowder, weapons...",
				"yeah... Sorry, I forgot .",
                "Oh, yeah.",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Understood. It's not clear why you need this. Well, okay, it's better to ask the housewives of the ships for a car with bombs, they have a lot of this stuff. But the admiral has the guns and gunpowder.";
			link.l1 = "And will he give?";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "I don't know. Ask him.";
			link.l1 = "Clear. Thank you very much.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Command to the ship?";
			link.l1 ="Yes.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "So, do you have it in stock?";
			link.l1 = "Available.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "That's the news... I agree!";
			link.l1 = "Great! Then go to the San Gabriel immediately. Henrik Wedeker will transfer you to my ship.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Okay, I'll do that. I'll just pack my things quickly and I can leave.";
			link.l1 = "Don't linger.";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
