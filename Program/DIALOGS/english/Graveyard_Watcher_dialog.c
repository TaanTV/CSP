// boal 25/04/04 общий диалог горожан
#include "DIALOGS\english\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
    string sTemp, sCity;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	String attrLoc = Dialog.CurrentNode;

	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":

            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Spy? Guards!!!!!", "Guard! There is an enemy in the city!");
				link.l1 = "Shut up! I'm already leaving.";
				link.l1.go = "fight";
				break;
			}*/

            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text =NPCharRepPhrase(npchar,
                                LinkRandPhrase("My name is ", "My name ", "You can call me ")
                                +GetFullName(npchar)
                                +LinkRandPhrase(". What do you need?", "I didn't see you before "
                                +", who are you?", ". Who are you and what do you want from me?"),

        		                LinkRandPhrase("Greetings, " + GetAddress_Form(NPChar) + ". My name is " + GetFullName(npchar) + ". What's your name?",
                                 "Hello, " + GetAddress_Form(NPChar) + "! I am " + GetFullName(npchar) + ". May I know your name?",
                                 "Yes, " + GetAddress_Form(NPChar) + ". What did you want? By the way, my name is " + GetFullName(npchar) + ". And you?"));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase("Damn me!", "A thousand devils! ", "May it be empty for you! ") + "Yes, I am the captain "+ GetFullName(Pchar)+ LinkRandPhrase(", haven't you heard about me"+NPCharSexPhrase(NPChar,", rascal?","?"), " and "+ GetSexPhrase("the most famous pirate","the most famous female pirate") +" in these waters! ", "and I'll be damned if that's not the case!"),
                                LinkRandPhrase("I am " + GetFullName(Pchar) + ", Captain.", "My name is " + GetFullName(Pchar) + ".", "You can call me Captain " + GetFullName(Pchar) + "."));

                //LinkRandPhrase("I " + GetFullName(Pchar) + ", Captain.", "My name is " + GetFullName(Pchar) + ".", "You can call me Captain " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
				if (pchar.sex == "Skeleton")	//Проверка на скелета
				{
					if	(GetCharacterEquipSuitID(pchar) == "suit_1")
					{
						dialog.text = "Even though you're dressed up in these rags, you can't fool my old eyes...";
						link.l1 = "Is my disguise really that bad?",
						link.l1.go = "UndeadObuchenie_2";
					}
					else
					{
						dialog.text = "Judging by your ridiculous gait, you have recently risen from the grave. But don't be afraid of me, I won't hurt you.";
						link.l1 = "Surprisingly, YOU should be afraid of ME, not the other way around!";
						link.l1.go = "UndeadObuchenie_11";
					}
				}
			}
			else
			{
				link.l1 = PCharRepPhrase("I want to learn something about the town in the vicinity!", "I want to find out something about the city that is not far from here.");
				link.l1.go = "new question";
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l2 = LinkRandPhrase("You know", "You know", "Do you know anything about that") + "that the local church was robbed recently?");
					link.l2.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.

                dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Oh, it's you "+GetFullName(Pchar)
                        +" "+ GetSexPhrase(", my friend",", my friend") +"", "Glad to see you, "+ GetSexPhrase("old man","beauty") +" "
                        + Pchar.name, "Oh, yes, it's "+ GetSexPhrase("the captain himself","herself") +" "
                         +GetFullName(Pchar))
                                        +LinkRandPhrase(". I thought you've already dead!", "And probably "+ GetSexPhrase("drunk as always.","already a little tipsy.") +"", ". And, as I see, still at large!")
                                        +LinkRandPhrase(" Tell me, what do you want?", " What do you want this time?", " Are you bothering me again for nothing?"),
                                        LinkRandPhrase(TimeGreeting() + ", captain ", "Hello, "+GetAddress_Form(NPChar)+" ", "Greetings, Captain ")+GetFullName(Pchar)
                                        +LinkRandPhrase(". What are you interested in?", ". Why are you here?", ". What do you want to know this time?")

                                        ),

                        PCharRepPhrase(LinkRandPhrase("Hello, Captain ", "Hello, oh it's you "+GetAddress_Form(NPChar)+" ", "Ah, Captain ")
                                        +GetFullName(Pchar)
                                        +LinkRandPhrase(", I thought that we won't meet again,",
                                                         ", I wouldn't say that I am happy to see you, but", "I see you're still alive, it's unfortunate, huh")
                                        +LinkRandPhrase(" what do you want?", " why are you here?", " how may I be useful?"),
                                        LinkRandPhrase(TimeGreeting() + ", captain " + GetFullName(Pchar) + ". How may I help you?",
                                        "Oh, captain " + GetFullName(Pchar) + "! What do you want to know this time?",
                                        "Greetings, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". Did toy want something?"))
                                        );
	   			link.l3 = "Nothing, I changed my mind" + GetSexPhrase(".","a.");
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("Aren't you lying, Captain " + GetFullName(Pchar)+"?",
                                                                    "So what" + PChar.name+"?",
                                                                    "I'll remember you, " + GetFullName(Pchar)+".")
                                                                     + " Now tell me, what do you want?",
                                                    LinkRandPhrase("Nice to meet you, Captain " + PChar.name,
                                                                    "Glad to our acquaintance, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     "It's a pleasure, Captain " + PChar.name) + ". But you probably didn't just want to know my name, did you?");

            link.l1 = PCharRepPhrase("I want to learn something about this town!", "I want to learn something about the city.");
			link.l1.go = "new question";
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l2 = LinkRandPhrase("You know", "Do you know anything about that", "Do you know anything about that") + "that the local church was robbed recently?");
				link.l2.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.

			link.l3 = "Nothing, I changed my mind" + GetSexPhrase(".","a.");
			Link.l3.go = "exit";
		break;

		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Oh, yes, I'm glad ask you what you want as a drink.", "Do you like to chat, Captain? Well, me too... Especially over a mug of rum.", "Yes, " + PChar.name + "?"),
                                        LinkRandPhrase("Well, what else do you want?", "I see, Captain "+PChar.name+", you are willing to chat? ", "You tortured me with your questions, Captain, it would be better to drink rum.")),
		                PCharRepPhrase(LinkRandPhrase("What did you want to know "+ GetAddress_Form(NPChar) + "?", "I'm listening to you, Captain.", "I have to go, so ask me soon, Captain."),
                                        LinkRandPhrase("I always glad to have a pleasant companion, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Speak.",
                                                        "Yes, " + GetAddress_Form(NPChar) + "?",
                                                        "Do you like to chat, Captain? Well, me too..."))
                            );

            // homo 25/06/06
			link.l1 = LinkRandPhrase ("What kind of stories are in use in the tavern here?",
                                    "What's new in these parts?",
                                    "How does life flow on land?");
			link.l1.go = "rumours_citizen";
			link.l2 = "Nothing, I changed my mind" + GetSexPhrase(".","a.");
			link.l2.go = "exit";
		break;

		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("No, I don't know anything about this.", "I don't know anything about this issue.", "I don't know anything.");
					link.l1 = LinkRandPhrase("Okay, good.", "Okay, thanks.", "Okay, sorry.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("I don't know anything about this, but you can ask the regulars at the tavern - they will certainly tell you something.", "I can't tell you anything, ask someone at the tavern better.", "I don't know anything specific, but I I heard they were talking about it in the tavern.");
				link.l1 = "Thanks for that.";
				link.l1.go = "exit";
			}

			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;

		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this city, I ask you not to walk with a naked blade here.", "You know, as a citizen of this city, I ask you not to walk with a naked blade here.");
				link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful on turns, "+ GetSexPhrase("buddy","girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like it when "+ GetSexPhrase("men","all sorts here") +" they walk in front of me with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Understood.", "I'm removing.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Yes you are "+ GetSexPhrase("thief, my dear! Guards, hold him down","thief! Guards, hold her down") +"!!!", "Wow! As soon as I looked at it, you went straight into the chest with your head! Hold this theif!!!", "Guards! They're robbing!!! Hold this theif!!!");
			link.l1 = "Ah, the devil!!!";
			link.l1.go = "fight";
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "UndeadObuchenie_2":
			dialog.text = "I have lived in this graveyard almost all my life. And I can easily figure out who is in front of me, human or undead. But it's not your clothes that betray the undead in you, but your GAIT. Look at how you stand - uncertainly, it's immediately obvious that you recently got up from the grave. Simply put, he's new.";
			link.l1 = "Yes, you see this world in a completely different way with dead eyes. And it makes me rock from side to side.",
			link.l1.go = "UndeadObuchenie_3";
		break;
		
		case "UndeadObuchenie_3":
			dialog.text = "You don't have to be afraid, it's just me who's so big-eyed. The rest of the inhabitants of this island will not even notice the trick, and they will take you for their own, that is, for a person. But once you take off your disguise, people will be hostile to you. It's clear to you, isn't it?";
			link.l1 = "It's unpleasant. But... Do I have any allies?",
			link.l1.go = "UndeadObuchenie_13";
		break;
		
		case "UndeadObuchenie_11":
			dialog.text = "Hehe, no! I'm used to people like you. I even maintain good relations with some undead. But I am an exception to the rule. You need to be careful, because the rest of the inhabitants of this island will be afraid of you and... will try to destroy you.";
			link.l1 = "This is unpleasant... But then what should I do?",
			link.l1.go = "UndeadObuchenie_12";
		break;
		
		case "UndeadObuchenie_12":
			dialog.text = "You need to wear a disguise. Find some rags and walk among people like the spitting image of your own.";
			link.l1 = "Do I have any allies?",
			link.l1.go = "UndeadObuchenie_13";
		break;
		
		case "UndeadObuchenie_13":
			dialog.text = "Of course, almost any undead is your friend. You can look for your relatives in the caves, they will gladly join your ship's crew.";
			link.l1 = "It's so good that I looked in on you. I will continue to explore this world, in this cursed body. Goodbye.",
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
	}
}
