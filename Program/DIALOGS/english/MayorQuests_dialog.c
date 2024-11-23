void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно
			for(i = 1; i <= 29; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("Money on a barrel "+ GetSexPhrase("buddy","girlfriend") +"! My name is " + GetFullName(npchar) + ", and I do not tolerate objections to my address...",
				"Show me the contents of your wallet, "+ GetSexPhrase("buddy","girlfriend") +", and quickly! My name is " + GetFullName(npchar) + ", and I hope you've heard about me...",
				"Lay out everything of value that you have, I will commandeer the contents of your wallet. And hurry up, because I, " + GetFullName(npchar) + ", am not very patient. But he's very bloodthirsty!");
			Link.l1 = LinkRandPhrase("Heh, so you're " + GetFullName(npchar) + "? The local governor " + sTemp + " is talking about you all the time.",
				"Oh, so you're the bandit that the local governor " + sTemp +" is hunting on?!",
				"Glad to see you, " + GetFullName(npchar) + ". The local governor, " + sTemp + ", talks only about you...");
			Link.l1.go = "DestroyGang_1";
		break;
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("Yes, I'm famous in these parts, hehe... Stop, aren't you an another governor's dog, who is trying to set me on fire?",
				"The governor is my great friend, what should I hide? Ha, aren't you another hero who came for my head?",
				"The governor's 'friendly' attitude towards me is a fact, hehe. How do you know that? Maybe he sent you after me?");
			Link.l1 = LinkRandPhrase("That's right, you bastard. Get ready to die!", "Wow, how smart you are. Well, it's time to start your liquidation. We've talked, that's enough...", "Yes, that's me. Get your weapon out, buddy! Let's see what color your blood is.");
			Link.l1.go = "DestroyGang_ExitFight";
			Link.l2 = LinkRandPhrase("No, really! I don't need these problems at all...", "No, I don't take on such things, I'm not a hero, in general...", "No, no way! I don't need any problems...");
			Link.l2.go = "DestroyGang_2";
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("That's better, "+ GetSexPhrase("buddy", "girlfriend") +"... Now get lost!",
				"And this is the right decision, you should know how many heroes I sent to the next world... Okay, less lyrics. Get out of here, "+ GetSexPhrase("bag of shit","whore") +"!",
				"Well done, I praise you! A very wise life position is not to go where you are not asked... Okay, get lost, "+ GetSexPhrase("buddy","girlfriend") +".");
			Link.l1 = "Goodbye, I wish you good health...";
			Link.l1.go = "DestroyGang_ExitAfraid";
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 30; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 30; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//----------------- поиски лазутчика в коммонах ----------------------
		case "SeekSpy_house":
			chrDisableReloadToLocation = false;
			dialog.text = "What do you need, " + GetAddress_Form(PChar) + "?";
			Link.l1 = "I need to find out who you are. Tell me immediately who you are and what are you doing here?";
			Link.l1.go = "SeekSpy_1";
		break;
		case "SeekSpy_1":
			dialog.text = "And who are you to answer your questions?";
			Link.l1 = "I'm acting on behalf of the governor, looking for an enemy spy!";
			Link.l1.go = "SeekSpy_2";
		break;
		case "SeekSpy_2":
			dialog.text = "Well, what do I have to do with it?";
			Link.l1 = "Maybe it has nothing to do with it, but let's go to the commandant's office first. We'll figure it out there...";
			Link.l1.go = "SeekSpy_3";
		break;
		case "SeekSpy_3":
			dialog.text = "No, I'm not going to the commandant's office. Consider that you've found the spy. Well, now try to get out of here.";
			Link.l1 = "Heh, I will...";
			Link.l1.go = "SeekSpy_fight";
		break;
		case "SeekSpy_fight":
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SeekSpy_Afrer");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "CitizenNotBlade":
			dialog.text = "Who are you?! Put away your weapons, quickly!";
			link.l1 = "I just wanted to brag...";
			link.l1.go = "SeekSpy_house";
		break;
		//----------------- поиски лазутчика на улице ----------------------
		case "SeekSpy_street":
			Diag.TempNode = "SeekSpy_street";
            dialog.Text = NPCharRepPhrase(npchar,
		            PCharRepPhrase(LinkRandPhrase("Oh, it's you, " + GetFullName(Pchar)
                    +", "+ GetSexPhrase("the old rascal","desperate girl") +"", ""+ GetSexPhrase("Glad to see you, old man","Glad to see you, beautiful") +""
                    + Pchar.name, "Oh! Captain "
                        +GetFullName(Pchar))
                                    +LinkRandPhrase(". I thought you were gone.", ". And probably, as always, "+ GetSexPhrase("drunk","drunk") +".", ". And, as I see, still free!")
                                    +LinkRandPhrase("Tell me, what do you want?", "What do you want this time?", "Bothering me again for nothing?"),
                                    LinkRandPhrase(TimeGreeting() + ", captain ", "Hello "+GetAddress_Form(NPChar)+" ", "Greetings, Captain ")+GetFullName(Pchar)
                                    +LinkRandPhrase(". What might be needed "+ GetSexPhrase("to such a respectable man","to a brave girl") +"How are you, from me?", ". Why did you come?", ". What do you want to know this time?")
                                    ),

                    PCharRepPhrase(LinkRandPhrase("Hello Captain ", "Hello, ah, it's you "+GetAddress_Form(NPChar)+" ", "Ah, Captain ")
                                    +GetFullName(Pchar)
                                    +LinkRandPhrase(" I thought that we won't meet again,",
                                                        "can't say I'm glad to see you, but", " I see you are still alive, unfortunately. A")
                                    +LinkRandPhrase(" what do you want?", " why are you here?", "  how may I be "+NPCharSexPhrase(NPChar, "useful?", "useful?")),
                                    LinkRandPhrase(TimeGreeting() + ", captain " + GetFullName(Pchar) + ". How can I help you?",
                                    "Oh, it's the captain " + GetFullName(Pchar) + "! What do you want to know this time?",
                                    "Hello, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". Do you need something?"))
                                    );

	   		link.l1 = PCharRepPhrase(RandPhraseSimple("You heard me, I'm going.", "No, nothing - just"+ GetSexPhrase("walking","walking") +"to the tavern."),
                                    RandPhraseSimple("Okay, nothing. Good luck!", "Just looking around the city. Goodbye."));
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("I have a question for you.", "I need information.");
			link.l2.go = "exit";//(перессылка в файл города)
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("Wait! Tell me immediately, who are you?! I am looking for an enemy spy on behalf of the governor " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!",
					"Stop immediately! I am acting in the interests of the city " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " on behalf of the governor. I'm looking for an enemy agent in the city.",
					"Stop, buddy! Local governor " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + "really wants to find a spy in the city."),
					LinkRandPhrase("Woman, stop! Tell me immediately, who are you?! I am looking for an enemy spy on behalf of the governor " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!",
					"Woman, I owe to detain you! I am acting in the interests of the city " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " on behalf of the governor. I'm looking for an enemy agent in the city.",
					"Wait, beautiful! Local governor " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + "really wants to find a spy in the city..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			link.l5 = PCharRepPhrase("I want to learn something about this town!", "I want to learn something about the city.");
			link.l5.go = "new question";
		break;

		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Oh, yes, I'm glad"+NPCharSexPhrase(NPChar, " ", "a ")+"you like a drink, ask what you want.", "Do you like to chat, Captain? Well, me too... Especially over a mug of rum.", "Yes, " + PChar.name + "?"),
                                        LinkRandPhrase("Well, what else do you want?", "I see, Captain "+PChar.name+", you are willing to chat? ", "You tortured me with your questions, Captain, it would be better to drink rum.")),
		                PCharRepPhrase(LinkRandPhrase("What did you want to know "+ GetAddress_Form(NPChar) + "?", "I'm listening to you, Captain.", "I have to go, so ask me soon, Captain."),
                                        LinkRandPhrase("I am always glad to have "+NPCharSexPhrase(NPChar, " ", "a ")+" a pleasant companion, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Speak.",
                                                        "Yes, " + GetAddress_Form(NPChar) + "?",
                                                        "Do you like to chat, Captain? Well, me too..."))
                            );

            // homo 25/06/06
			link.l1 = LinkRandPhrase ("What kind of stories are in use in the tavern here?",
                                    "What's new in these parts?",
                                    "How does life flow on land?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("Can you explain the way to me?", "I can't find the way somewhere...", "Tell me the way...");
			link.l2.go = "exit";  //(перессылка в файл города)
			link.l3 = "Tell me about your colony.";
			link.l3.go = "colony";
            link.l4 = RandPhraseSimple("I have an important matter!", "I have a matter for you.");
			link.l4.go = "exit";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("You heard me, I'm going.", "No, nothing - just"+ GetSexPhrase("walking","walking") +"to the tavern."),
                                        RandPhraseSimple("Okay, nothing. Good luck!", "Just looking around the city. Goodbye."));
			link.l5.go = "exit";
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
            dialog.text = "Oh, are you kidding me? Or are you kidding? Look at the upper-right corner of the screen.";
			link.l1 = "That's right, I'm stupid.";
		    link.l1.go = "exit";
		break;

		case "fort":
            dialog.text = "I don't know anything about it.";
			link.l1 = "Sorry.";
		    link.l1.go = "exit";
		break;
		//==> поймал засланца
		case "SitySpy":
			dialog.text = "Well, what do I have to do with it? I'm a local!";
			link.l1 = "Who can confirm your words?";
		    link.l1.go = "SitySpy_1";
		break;
		case "SitySpy_1":
			dialog.text = "Everyone can confirm, everyone!!!",
			link.l1 = "Who is everyone? Name at least one citizen in " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!";
			link.l1.go = "SitySpy_3";
		break;
		case "SitySpy_3":
            dialog.text = "Uh... Now... Mmm..";
			link.l1 = "It's clear, buddy, that's what I'm looking for! Follow me, or I'll kill you on the spot. Do you understand everything?!";
		    link.l1.go = "SitySpy_4";
		break;
		case "SitySpy_4":
            dialog.text = "Damn! It was so stupid to get involved!.. Everything is clear, I will follow you - my life is still dear to me...";
			link.l1 = "Well, that's nice. We're going to the governor, he wanted to see you...";
		    link.l1.go = "SitySpy_5";
		break;
		case "SitySpy_5":
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)]);
			AddQuestRecord("MayorsQuestsList", "5");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			// слухи
			AddSimpleRumour("You know, the governor " + sTemp + " instructed "+ GetSexPhrase("to a certain captain","to a certain girl captain") +" " + GetMainCharacterNameGen() + " find an enemy spy in the city. And you know, "+ GetSexPhrase("he found it","she found it") +"right on the streets!", sti(characters[sti(pchar.GenQuest.SeekSpy.MayorId)].nation), 5, 1);
			AddSimpleRumourCity("Our governor gave the task to the captain " + GetMainCharacterNameGen() + " to find an enemy agent in the city. And "+ GetSexPhrase("this captain found","this girl found") +"a spy among the townspeople!", npchar.city, 5, 1, "");
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			pchar.GenQuest.SeekSpy = "FoundSpy"; //флаг нашёл шпиона
			DeleteAttribute(pchar, "GenQuest.SeekSpy.City"); //не опрашивать более в городе
			LocatorReloadEnterDisable(pchar.location, "gate_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload1_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
		//----------------- найти и уничтожить пирата в море ----------------------
		case "DestroyPirate_Abordage": //абордаж
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate.wasTalkInDeck"))
			{
				dialog.text = "You still back...";
				Link.l1 = "Yes, I forgot...";
				Link.l1.go = "DP_Abordage_1";
			}
			else
			{
				dialog.text = "Who are you?!";
				Link.l1 = "I came for your head, buddy. Governor " + XI_ConvertString("Colony"+pchar.GenQuest.DestroyPirate.MayorId+"Gen") + " wants to see it nailed to the city gate.";
				Link.l1.go = "DP_Abordage_2";
			}
		break;
		case "DP_Abordage_1":
			dialog.text = "Fuck this shit! I'll kill you!";
			Link.l1 = "Try to...";
			Link.l1.go = "DP_Abordage_fight";
		break;
		case "DP_Abordage_2":
			dialog.text = "Heh, I see... Well, I'll try not to give him such pleasure!";
			Link.l1 = "Try to...";
			Link.l1.go = "DP_Abordage_fight";
		break;
 		case "DP_Abordage_fight":
			LAi_SetCurHP(npchar, rand(sti(npchar.chr_ai.hp_max)) + 5);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
		break;
		//разговор на палубе
		case "DestroyPirate_Deck":
			pchar.GenQuest.DestroyPirate.wasTalkInDeck = true; //флаг на палубный базар
			dialog.text = "Why did you here, buddy?";
			Link.l1 = "I am acting on behalf of the governor of " + XI_ConvertString("Colony"+pchar.GenQuest.DestroyPirate.MayorId+"Gen") + ", I'm looking for a pirate operating in these waters lately.";
			Link.l1.go = "DestroyPirate_1";
		break;
		case "DestroyPirate_1":
			dialog.text = "I can't say that this is a worthy occupation for a captain...";
			Link.l1 = "What does this mean?!";
			Link.l1.go = "DestroyPirate_2";
		break;
		case "DestroyPirate_2":
			dialog.text = "Exactly what I'm telling you now. Catching free corsairs so that the local governor can then hang our corpses around the city is an occupation unworthy of a ship's captain.";
			Link.l1 = "So you are the pirates...";
			Link.l1.go = "DestroyPirate_3";
		break;
		case "DestroyPirate_3":
			dialog.text = "That's right, the governor's puppy. Heh, you have an unenviable position - you're alone... on my ship...";
			Link.l1 = "Well, what are you going to do next?";
			Link.l1.go = "DestroyPirate_4";
		break;
		case "DestroyPirate_4":
			int lngFileID;
			if (pchar.GenQuest.DestroyPirate.fortPlace == "1")
			{
				pchar.GenQuest.DestroyPirate.outShoreId = GetIslandRandomShoreId(pchar.GenQuest.DestroyPirate.Areal);
				sld = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
				lngFileID = LanguageOpenFile("LocLables.txt");
				sTemp = LanguageConvertString(lngFileID, pchar.GenQuest.DestroyPirate.outShoreId);
				dialog.text = "Hmm, next... I got too close to the fort, so I won't take any chances and keep you here for a while. You will tell your friends that you will go on my ship to a place called " + sTemp + ", and let them wait for you in " + XI_ConvertString("Colony"+sld.city+"Dat") +
					"In this case, I'll let you live. Otherwise, you'll be gutted right here on the deck. What are the prospects for the future?";
				Link.l1 = "I will not say that they are tempting. How do I know you'll keep your word when the fort doesn't get to you?";
				Link.l1.go = "DestroyPirate_5";
				break;
			}
			if (GetCompanionQuantity(pchar) == 1 && makeint(pchar.GenQuest.DestroyPirate.shipState) > 1)
			{
				dialog.text = "I think I'll let you go, "+ GetSexPhrase("governor's dog","governor's mutt") +". You will pay for my generosity with your cash.In general, get out while I'm kind...";
				Link.l1 = "Thanks for that, too. Goodbye...";
				Link.l1.go = "DP_WithoutFight";
				Link.l2 = "You know what, I'm going to slit your throat before your whole team runs out...";
				Link.l2.go = "DP_FightInDeck";
			}
			else
			{
				pchar.GenQuest.DestroyPirate.outShoreId = GetIslandRandomShoreId(pchar.GenQuest.DestroyPirate.Areal);
				sld = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
				lngFileID = LanguageOpenFile("LocLables.txt");
				sTemp = LanguageConvertString(lngFileID, pchar.GenQuest.DestroyPirate.outShoreId);
				dialog.text = "And then you tell your friends that you will go on my ship to a place called " + sTemp + ", and let them wait for you in " + XI_ConvertString("Colony"+sld.city+"Dat") +
					"In this case, I'll let you live. Otherwise, you'll be gutted right here on the deck. What are the prospects for the future?";
				Link.l1 = "I will not say that they are tempting. How do I know that you will keep your word when I am completely alone?";
				Link.l1.go = "DestroyPirate_5";
			}
		break;
		case "DestroyPirate_5":
			dialog.text = "Heh, you can't know, but you'll have my word. As it is, death awaits you right now. It seems to me that the choice is obvious...";
			Link.l1 = "Hmm, well, I agree. I hope you keep your word...";
			Link.l1.go = "DP_toShore";
			Link.l2 = "To me, that's the way it is. And this choice is to fight, here and right now. To arms, scoundrels!";
			Link.l2.go = "DP_FightInDeck";
		break;

		case "DP_toShore":
			dialog.text = "I'll keep it, don't be afraid.";
			Link.l1 = "Then I'm ready. Let's get to work.";
			Link.l1.go = "exit";
			AddDialogExitQuest("DestroyPirate_toShore");
		break;

		case "DP_WithoutFight":
			dialog.text = "If I see you again, you'll be hanging out on the yard, keep in mind...";
			Link.l1 = "I see...";
			Link.l1.go = "exit";
			Diag.TempNode = "DP_WithoutFight_again";
			AddDialogExitQuest("DestroyPirate_WithoutFight");
		break;
		case "DP_WithoutFight_again":
			dialog.text = "Are you still here? If I were you, I wouldn't stay here...";
			Link.l1 = "I'm leaving.";
			Link.l1.go = "exit";
			Diag.TempNode = "DP_WithoutFight_again";
		break;

		case "DP_FightInDeck":
			dialog.text = "Wow, "+ GetSexPhrase("what a brave man","what a brave girl") +"! I appreciate the courage, it will be a pity to kill you... Hey, on deck, take  "+ GetSexPhrase("this","this") +"upstart carefully, I'll prepare the ship for battle for now. Just don't make too much noise!";
			Link.l1 = "It's a pity that you're leaving us...";
			Link.l1.go = "DP_FightInDeck_1";
		break;
		case "DP_FightInDeck_1":
			pchar.GenQuest.DestroyPirate.FightAfterDeck = true; //после резни на палубе - драка в море
			float locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "DestroyPirate_FightInDeck", 3.5);
			DialogExit();
		break;


	}
}
