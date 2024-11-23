// boal 25/04/04 общий диалог горожан
#include "DIALOGS\english\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
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

			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Rumor has it that you are the owner of this city, "+ GetSexPhrase("sir", "miss") +".", "What a nice meeting, the head of the city has come to me with a question.");
					link.l1 = RandPhraseSimple("I changed my mind. Good luck!", "Just looking around the city. Goodbye.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("I have a question for you.", "I need information.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("I want to discuss financial matters.", "Regarding finance...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("What do you want? Pass by.", "Stop blocking the road, get off.");
					link.l1 = RandPhraseSimple("You know what? Don't bark!", "Slow down your ardor. Otherwise I'll cool it down quickly!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("I want to ask you.", "Attention a minute, just one question.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("I want to discuss financial matters.", "Regarding finance...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text =NPCharRepPhrase(npchar,
                                LinkRandPhrase("My name is ", "My name is ", "You can call me ")
                                +GetFullName(npchar)
                                +LinkRandPhrase(". What do you need?", ". I didn't see you before."
                                +" Who are you?", ". Who are you and what do you want from me?"),

        		                LinkRandPhrase("Greetings, " + GetAddress_Form(NPChar) + ". My name is " + GetFullName(npchar) + ". What's your name?",
                                 "Hello, " + GetAddress_Form(NPChar) + "! I am " + GetFullName(npchar) + ". May I know your name?",
                                 "Yes, " + GetAddress_Form(NPChar) + ". What did you want? By the way, my name is " + GetFullName(npchar) + ". And you?"));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase ("Thunder blast me!", "A thousand devils! ", "May it be empty for you! ") + "Yes, I am captain "+ getFullName(Pchar)+ LinkRandPhrase(", haven't you heard about me"+NPCharSexPhrase(NPChar, ", rascal?", "?"), " and "+ GetSexPhrase("the most famous pirate", "the most famous female pirate") +" in these waters! ", "and I'll be damned if that's not the case!"),
 								LinkRandPhrase("I'am captain " + getFullName(Pchar) + ".", "My name is " + GetFullName(Pchar) +".", "You can call me Captain " + GetFullName(Pchar) +"."));

                //LinkRandPhrase("I am " + GetFullName(Pchar) + ", Captain.", "My name is " + GetFullName(Pchar) + ".", "You can call me Captain " + GetFullName(Pchar));				
				Link.l1.go = "Meeting";
				
				if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue6") && pchar.questTemp.AnjelikaTichPrologue6 == "ATP6")	//Sinistra Пролог Анжелики Шарп
				{					
					dialog.text = LinkRandPhrase("The whole city is discussing only one news today – the failed attempt to capture our colony.", "No, but think what brave men they are, they decided to attack the fortifications of our city! And what did they expect? I think this adventure was doomed to failure when it was just born in the head of the one who came up with it.", "I admit, when the shooting started, I panicked.");
					link.l1 = "";
					link.l1.go = "exit";
					LAi_CharacterDisableDialog(npchar);
				}
				if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue") && pchar.questTemp.AnjelikaTichPrologue == "ATP" && pchar.questTemp.AnjelikaTichPrologue2 == "ATP2")	//Sinistra Пролог Анжелики Шарп
				{
					pchar.ATP_MirJitId = npchar.id;
					
					int Phrase2;
					Phrase2 = rand(1);
					if (Phrase2 == 0)
					{
						dialog.text = "Good afternoon, Angelica, so glad to see you. The weather is perfect for a walk today!";
						link.l1 = "Hello, " + npchar.name+", I'm glad to see you too.";
						link.l1.go = "ATP_0_1";
					break;
					}
					if (Phrase2 == 1)
					{
						dialog.text = "Angelica, how beautiful you are. It's nice to look at you. I'm going to the market now to stock up on food supplies.";
						link.l1 = "Thanks for the compliment, " + npchar.name+". Good luck to you!";
						link.l1.go = "ATP_0_1";
					break;
					}
				}
				if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue") && pchar.questTemp.AnjelikaTichPrologue == "ATP")	//Sinistra Пролог Анжелики Шарп
				{
					pchar.ATP_MirJitId = npchar.id;
					
					int Phrase;
					Phrase = rand(3);
					if (Phrase == 0)
					{
						dialog.text = "Good afternoon, Angelica, Rebecca, so glad to see you. The weather is perfect for a walk today!";
						link.l1 = "Hello, " + npchar.name+", we are glad to see you too.";
						link.l1.go = "ATP_1";
					break;
					}
					if (Phrase == 1)
					{
						dialog.text = "Two beauties - Angelica, Rebecca. It's nice to look at you. I'm going to the market now to stock up on food supplies.";
						link.l1 = "Hello, " + npchar.name+".";
						link.l1.go = "ATP_2";
					break;
					}
					if (Phrase == 2)
					{
						dialog.text = ""+ NPCharSexPhrase(NPChar, "Greetings, young girls.", "Angelica, hello. Becky! You've completely become a stay-at-home mom, I'm glad to see you.") +"";
						link.l1 = ""+ NPCharSexPhrase(NPChar, "I think we already met in the morning, or it was yesterday at noon.", "Hello, " + npchar.name+".") +"";
						link.l1.go = "ATP_3";
					break;
					}
					if (Phrase == 3)
					{
						dialog.text = "A wonderful day, don't you think? A light wind knocked down the usual heat a little.";
						link.l1 = "Yesterday morning was the same, and by noon the sun was already burning the grass.";
						link.l1.go = "ATP_4";
					break;
					}
				}
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "Captain, could you help me with something?";
					link.l1 = LinkRandPhrase("Sorry, no. I have very little time right now.", "I'm sorry, I can't. Affairs...", "No, I can't. I have a lot of important things to do right now.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("Of course. What's the deal?", "Yes, I will help. Tell me what this case is...", "Tell me about this case in more detail...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}

				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "Yes, Captain, I'm listening to you.";
					link.l1 = NPChar.name + ", I've found your wedding ring.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}

				link.l1 = PCharRepPhrase("I wanted to find out something about this town!", "I wanted to learn something about the city.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("I have a question for you.", "I need information.");
				if (CheckCharacterItem(pchar, "CaptainBook"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  
					}
					else
					{
						link.l2.go = "quests";
					}
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("I want to discuss financial matters.", "Regarding finance...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("Wait! Tell me immediately, who are you?! I'm looking for an enemy spy on behalf of the governor of " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!",
						"Stop immediately! I am acting in the interests of the city " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " on behalf of the governor. I'm looking for an enemy agent in the city.",
						"Stop, buddy! Local governor " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + "really wants to find a spy in the city."),
						LinkRandPhrase("Woman, stop! Tell me immediately, who are you?! I am looking for an enemy spy on behalf of the governor " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!",
						"Woman, I owe to detain you! I am acting in the interests of the city " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " on behalf of the governor. I'm looking for an enemy agent in the city.",
						"Wait, beautiful! Local governor " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + "really wants to find a spy in the city..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице

				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("You know", "You know", "Do you know anything about that") + "that the local church was robbed recently?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.

                dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Oh, it's you, " + GetFullName(Pchar)
                        +" "+ GetSexPhrase("- old rascal", "- reckless girl") +"", "Glad to see you, "+ GetSexPhrase("old man", "beauty") +" "
                        + Pchar.name, "Oh, I see "+ GetSexPhrase("captain himself", "herself") +" "
                         +GetFullName(Pchar))
                                        +LinkRandPhrase(". I thought you are already dead!", ". And drunk as usual, I guees?"+ GetSexPhrase("drunk as always.", "already a little tipsy.") +"", " And, as I see, still free!")
                                        +LinkRandPhrase("Well, tell me, what do you want?", " What do you want this time?", "Are you bothering me about nothing again?"),
                                        LinkRandPhrase(TimeGreeting() + ", captain!", "Hello, "+GetAddress_Form(NPChar)+" ", "Greetings, captain ")+GetFullName(Pchar)
                                        +LinkRandPhrase(". What may need "+ GetSexPhrase("to such a respectable man", "to such a brave girl") +"How are you, from me?", ". Why did you come?", ". What do you want to know this time?")

                                        ),

                        PCharRepPhrase(LinkRandPhrase("Hello, Captain ", "Hello, oh it's you "+GetAddress_Form(NPChar)+" ", "Ah, Captain ")
                                        +GetFullName(Pchar)
                                        +LinkRandPhrase(", I thought that we won't meet again, ",
                                                         ", can't say, I glad to see you, but", "I see you're still alive, it's unfortunate, huh")
                                        +LinkRandPhrase(" why are you here?", " why did you come?", " how may I be"+NPCharSexPhrase(NPChar, "useful?", "useful?")),
                                        LinkRandPhrase(TimeGreeting() + ", captain " + GetFullName(Pchar) + ". How may I help you?",
                                        "Oh, captain " + GetFullName(Pchar) + "! What do you want to know this time?",
                                        "Hello, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". Did you want something?"))
                                        );
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("You heard me, I'm going.", "No, nothing - I am going to the tavern."),
                                        RandPhraseSimple("Okay, nothing. Good luck!", "Just looking around the city. Goodbye."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "ShipLetters_7":
			dialog.text = "What are the questions?";
			link.l1 = "Does the name in these papers mean anything to you?";
			link.l1.go = "ShipLetters_8";
		break;

		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("I don't care about unfamiliar papers, and I can't read either. Go to the usurer, they say he has been trained in the devil's letters.",
										"I have no idea what you're talking about, ask more residents of this city, Captain " + GetFullName(Pchar) + ".",
										"I don't even know how to help you, Captain " + GetFullName(Pchar) + ". Try contacting a usurer, maybe he knows?");
			link.l1 = "I would be happy to take your advice!";
			link.l1.go = "exit";
		break;

		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("Aren't you lying, Captain " + GetFullName(Pchar)+"?",
                                                                    "So what " + PChar.name+"?",
                                                                    "I'll remember you, " + GetFullName(Pchar)+".")
                                                                     + " Now please, say what is your need?",
                                                    LinkRandPhrase("Nice to meet you, Captain " + PChar.name,
                                                                    "Nice to meet you, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     "It's a pleasure, Captain " + PChar.name) + ". But you probably didn't just want to know my name, did you?");

            link.l1 = PCharRepPhrase("I wanted to learn something about this town!", "I wanted to learn something about the city.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("I have a question for you.", "I need information.");
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  
				}
				else
				{
					Link.l2.go = "quests";
				}
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("I want to discuss financial matters.", "Regarding finance...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("Wait! Tell me immediately, who are you?! I'm looking for an enemy spy on behalf of the governor of " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!",
					"Stop immediately! I am acting in the interests of the city " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " on behalf of the governor. I'm looking for an enemy agent in the city.",
					"Stop, buddy! Local governor " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + "really wants to find a spy in the city."),
					LinkRandPhrase("Woman, stop! Tell me immediately, who are you?! I am looking for an enemy spy on behalf of the governor " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!",
					"Woman, I owe you to detain you! I am acting in the interests of the city " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " on behalf of the governor. I'm looking for an enemy agent in the city.",
					"Wait, beautiful! Local governor " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + "really wants to find a spy in the city..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("You know", "Do you know anything about that", "Do you know anything about that") + "that the local church was robbed recently?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.

			Link.l6 = PCharRepPhrase(RandPhraseSimple("You heard me, I'm going.", "No, nothing - I am going to the tavern."),
                                        RandPhraseSimple("Okay, nothing. Good luck!", "Just looking around the city. Goodbye."));
			Link.l6.go = "exit";
		break;

		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Oh, yes, I'm glad"+NPCharSexPhrase(NPChar, " ", "a ")+"ask you what you want as a drink.", "Do you like to chat, Captain? Well, me too... Especially over a mug of rum.", "Yes, " + PChar.name + "?"),
                                        LinkRandPhrase("Well, what else do you want?", "I see, Captain "+PChar.name+", you are willing to chat? ", "You tortured me with your questions, Captain, it would be better to drink rum.")),
		                PCharRepPhrase(LinkRandPhrase("What did you want to know "+ GetAddress_Form(NPChar) + "?", "I'm listening to you, Captain.", "I have to go, so ask me soon, Captain."),
                                        LinkRandPhrase("I'm always happy to have a nice companion, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ".",
                                                        "Yes, " + GetAddress_Form(NPChar) + "?",
                                                        "Do you like to chat, Captain? Well, me too..."))
                            );

            // homo 25/06/06
			link.l1 = LinkRandPhrase ("What kind of stories are in use in the tavern here?",
                                    "What's new in these parts?",
                                    "How does life flow on land?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("Can you explain the way to me?", "I can't find the way somewhere...", "Tell me the way...");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("I want to know what they say about one person here.", "Do you know what they say about one person here?", "I would like to know something about the locals.");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(перессылка в файл города)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
				}
			}
			else
			{
				link.l3 = "Tell me about your colony.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("I have an important matter!", "I have a matter for you.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("You heard me, I'm going.", "No, nothing - I am going to the tavern."),
                                        RandPhraseSimple("Okay, nothing. Good luck!", "Just looking around the city. Goodbye."));
			link.l5.go = "exit";
		break;

		case "RumourAboutOwners":
			Dialog.Text = "Which of the residents do you want to know about?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "About the governor.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "About the local tavern owner.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "About the owner of the shipyard.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "About the local store owner.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "About no one. Forget.";
			link.l9.go = "exit";
			break;

		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;

		case "colony":
			dialog.text = LinkRandPhrase("To be honest, I don't know much about this. But I can tell you something.",
                           "What are you interested in in our colony?", "You're welcome. What do you want to hear about?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "What kind of city is this?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "What do you know about the fort protecting the city?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "Let's talk about something else.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "Oh, are you kidding me? Or are you kidding? Look at the right corner of the screen.";
			link.l1 = "That's right, I'm stupid.";
		    link.l1.go = "exit";
		break;

		case "fort":
            dialog.text = "I don't know anything about it.";
			link.l1 = "Sorry.";
		    link.l1.go = "exit";
		break;
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar, "Well, what do I have to do with it? I'm a local resident!", "Well, what do I have to do with it? I live in this city, and I don't want to know anything like that!"),
				NPCharSexPhrase(npchar, "What do you want from me again? I've already told you that I'm not a spy!", "I already told you that I'm a local!"),
				NPCharSexPhrase(npchar, "Well, how much can I do? Leave me alone, I'm a local!", "Why are you bothering me with your stupid questions again?"),
				NPCharSexPhrase(npchar, "What, again?! Well, it doesn't go through any gates!!!", "Listen, leave me alone at last, please!!"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Who can confirm your words?", "Oh, sorry, I already asked you...",
                      "Sorry, so many people...", "Okay, okay...", npchar, Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> выбираем подтверждателя
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //индекс выбранного
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
			{
				dialog.text = "Yes, anyone! Listen, why are you bothering me?! If you have any problems, then let's go to the governor and we'll clear everything up!",
				link.l1 = "Um... Perhaps we won't bother him in vain. I believe you...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Anyone in this city! " + NPCharSexPhrase(npchar, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]) + " can do it, good thing " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], "he", "she") + " is two steps away.",
				"Oh, my God, at least that's it " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], GetAddress_FormToNPC(NPChar) + " " + characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])) + "maybe.");
			link.l1 = "Well, let's hear it...";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0);
			DialogExit();
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "Yes, I confirm, " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], "he's really a local.", "she's really a local.");
			link.l1 = RandPhraseSimple("I got it. Thanks for the help.", "Everything is clear. Thanks for the help.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;

		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = "The fact is that I was walking outside the city yesterday and lost my wedding ring..."+ GetSexPhrase("Captain, could you look for it?", "Girl, please help me find him!") +"";
			link.l1 = "Of course "+ GetSexPhrase("I can! For the sake of such a beautiful girl, I am ready to do anything!", "I will help. The Church teaches to help one's neighbor.") +"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("No, I can't. Sorry. I have a lot to do.", "Sorry, I can't. I suddenly remembered that I still have one unfinished business left...", "I have very little time right now, so I can't help in any way...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;

		case "CitizenFindItem_2":
			dialog.text = ""+ GetSexPhrase("Captain", "Girl") +"That's great! Please find this ring, because through " + sti(NPChar.LifeDay) + "my husband is coming today and I wouldn't want him to see me without my wedding ring.";
			link.l1 = RandPhraseSimple("How did you say where did you lose it?", "So where did you lose it?");
			link.l1.go = "CitizenFindItem_3";
		break;

		case "CitizenFindItem_3":
			dialog.text = "Just outside the city gate...";
			link.l1 = "Well, then I'm going to search...";
			link.l1.go = "CitizenFindItem_4";
		break;

		case "CitizenFindItem_4":
			dialog.text = "Yes, go ahead. And hurry up. Remember, you have only " + sti(NPChar.LifeDay) + " of the day.";
			link.l1 = "I remember.";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;

			sCity = NPChar.City + "_ExitTown";

			//sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
			sTemp = "randitem1";
			Log_TestInfo("The ring will be in the locator - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");
		break;

		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;

		case "CitizenFindItem_Complete_1":
			dialog.text = ""+ GetSexPhrase("Captain", "Girl") +"! I'm so glad! How can I thank you?";
			link.l1 = "No, thank you, I did it completely selflessly.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "I could use a hundred or two piastres...";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;

		case "CitizenFindItem_Complete_2":
			dialog.text = "Ah, "+ GetSexPhrase("captain, what a wonderful person you are", "girl, you are so noble") +"! I will definitely pray for you in the church! Goodbye...";
			link.l1 = "Goodbye, " + npchar.name + ".";
			link.l1.go = "exit";
			ChangeCharacterReputation(PChar, 1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;

		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "Oh yes, of course. Here you have " + FindRussianMoneyString(iTemp) + ". That's all I have. Take them... And goodbye.";
			link.l1 = "Goodbye, " + GetFullName(NPChar) + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца

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
				dialog.text = NPCharSexPhrase(NPChar, "Be careful on turns, "+ GetSexPhrase("buddy", "girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like when " + GetSexPhrase("men", "all sorts") +" walk in front of me with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Understood.", "I'm removing.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		
		//Sinistra Пролог Анжелика Тич
		case "ATP_0_0":
			DialogExit();
			
			sld = CharacterFromID(pchar.ATP_MirJitId)
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ATP_0_1":
			DialogExit();
			
			sld = CharacterFromID(pchar.ATP_MirJitId)
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
		break;
		
		case "ATP_1":
			DialogExit();
			StartInstantDialog("AT_pr_Rebekka", "Rebekka_s_mirnymi_jitelyami_1", "Quest\AngelikaTichLine\MechtySbyvautsya.c");
			
			sld = CharacterFromID(pchar.ATP_MirJitId)
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ATP_1_1":
			dialog.text = "Thanks, but I'm fine, I'll move on, good luck to you!");
			link.l1 = "And good luck to you!";
			link.l1.go = "ATP_0_0";
		break;
		
		case "ATP_2":
			DialogExit();
			StartInstantDialog("AT_pr_Rebekka", "Rebekka_s_mirnymi_jitelyami_2", "Quest\AngelikaTichLine\MechtySbyvautsya.c");
			
			sld = CharacterFromID(pchar.ATP_MirJitId)
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ATP_2_1":
			dialog.text = "Take care of yourself!");
			link.l1 = "Have a nice day!";
			link.l1.go = "ATP_0_0";
		break;
		
		case "ATP_3":
			DialogExit();
			StartInstantDialog("AT_pr_Rebekka", "Rebekka_s_mirnymi_jitelyami_3", "Quest\AngelikaTichLine\MechtySbyvautsya.c");
			
			sld = CharacterFromID(pchar.ATP_MirJitId)
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ATP_3_1":
			dialog.text = "Good luck to you!");
			link.l1 = "Thank you!";
			link.l1.go = "ATP_0_0";
		break;
		
		case "ATP_4":
			DialogExit();
			StartInstantDialog("AT_pr_Rebekka", "Rebekka_s_mirnymi_jitelyami_4", "Quest\AngelikaTichLine\MechtySbyvautsya.c");
			
			sld = CharacterFromID(pchar.ATP_MirJitId)
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ATP_4_1":
			dialog.text = "Yes, yes. Your sister is absolutely right.");
			link.l1 = "Well, that's fine.";
			link.l1.go = "ATP_0_0";
		break;

	}
}
