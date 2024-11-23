
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":

            		if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text = NPCharRepPhrase(npchar,
                                LinkRandPhrase("My name is ", "My name is ", "You can call me ")
                                +GetFullName(npchar)
                                +LinkRandPhrase(". What do you want?", ". I've never seen you here before. "
                                +", who are you?", ". Who are you and what do you want from me?"),

        		                LinkRandPhrase("Greetings, " + GetAddress_Form(NPChar) + ". My name is " + GetFullName(npchar) + ". What's your name?",
                                 "Hello, " + GetAddress_Form(NPChar) + "! I am " + GetFullName(npchar) + ". May I know your name?",
                                 "Yes, " + GetAddress_Form(NPChar) + ". What did you want? By the way, my name is " + GetFullName(npchar) + ". And you?"));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase("Damn me!", "A thousand devils! ", "May it be empty for you! ") + "Yes, I am the captain "+ GetFullName(Pchar)+ LinkRandPhrase(", haven't you heard"+NPCharSexPhrase(NPChar,"","a")+"about me, "+NPCharSexPhrase(NPChar,"rascal?","?"), "and the most famous pirate in these waters! ", "and I'll be damned if that's not the case!"),
                                LinkRandPhrase("I am " + GetFullName(Pchar) + ", captain.", "My name is " + GetFullName(Pchar) + ".", "You can call me Captain " + GetFullName(Pchar) + "."));
                                Link.l1.go = "Meeting";
			}
			else
			{
				dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("Aren't you lying, Captain " + GetFullName(Pchar)+"?",
                                                                    "So what" + PChar.name+"?",
                                                                    "I'll remember you, " + GetFullName(Pchar)+".")
                                                                     + "Now tell me, what do you want?",
                                                    LinkRandPhrase("Nice to meet you, Captain " + PChar.name,
                                                                    "Glad to "+NPCharSexPhrase(NPChar, " ", "a ")+" meet you, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     "It's a pleasure, Captain " + PChar.name) + ". But you probably didn't just want to know my name, did you?");
				link.l1 = PCharRepPhrase("I want to learn something about this town!", "I want to learn something about the city.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("I have a question for you.", "I need information.");
				link.l2.go = "quests";//(перессылка в файл города)
			}

			NextDiag.TempNode = "First time";
		break;


		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("Aren't you lying, Captain " + GetFullName(Pchar)+"?",
                                                                    "So what, " + PChar.name+"?",
                                                                    "I'll remember you, " + GetFullName(Pchar)+".")
                                                                     + "Now tell me, what do you want",
                                                    LinkRandPhrase("Nice to meet you, Captain " + PChar.name,
                                                                    "Glad to meet you, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     "It's a pleasure, Captain " + PChar.name) + ". But I don't think you just wanted to know my name, did you?");

            	link.l1 = PCharRepPhrase("I want to learn something about this town!", "I want to learn something about the city.");
			link.l1.go = "new question";
            		Link.l2 = RandPhraseSimple("I have a question for you.", "I need information.");
			Link.l2.go = "quests";

			Link.l5 = PCharRepPhrase(RandPhraseSimple("You heard me, I'm going.", "No, nothing - I'm going to the tavern."),
                                        RandPhraseSimple("Okay, nothing. Good luck!", "Just looking around the city. Goodbye."));
			Link.l5.go = "exit";
			NextDiag.TempNode = "Meeting";
		break;

		case "new question":
            		dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Oh, yes, I'm glad to ask... You'd better want a drink.", "Do you like to chat, Captain? Well, me too... Especially over a mug of rum.", "Yes, " + PChar.name + "?"),
                                        LinkRandPhrase("Well, what else do you want?", "I see, Captain"+PChar.name+", you are chatterer? ", "You tormented me with questions, Captain, it would be better to treat you with rum.")),
		                PCharRepPhrase(LinkRandPhrase("What did you want to know "+ GetAddress_Form(NPChar) + "?", "I'm listening to you, Captain.", "I have to go, so ask me soon, Captain."),
                                        LinkRandPhrase("I'm always happy to have a good conversation, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Speak.",
                                                        "Yes, " + GetAddress_Form(NPChar) + "?",
                                                        "Do you like to chat, Captain? Well, me too...")));

            		link.l1 = RandPhraseSimple("I have an important matter!", "I have a matter for you.");
			link.l1.go = "quests";
			link.l2 = PCharRepPhrase(RandPhraseSimple("You heard me, I'm going.", "No, nothing - I'm going to the tavern."),
                                        RandPhraseSimple("Okay, nothing. Good luck!", "Just looking around the city. Goodbye."));
			link.l2.go = "exit";
		break;

		case "quests":
            		dialog.text = RandPhraseSimple("What questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind..", "I have nothing to talk about right now.");
		    	link.l1.go = "exit";
		break;


		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this city, I ask you not to walk with a naked blade here.", "You know, as a citizen of this city, I ask you not to walk with a naked blade here.");
				link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful on turns, captain, when you run with a gun in your hands. I can get nervous...", "I don't like it when people walk in front of me with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Got it.", "I'm removing.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;




		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
