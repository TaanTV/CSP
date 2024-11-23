//Jason общий диалог уличных матросов
#include "DIALOGS\english\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (CheckAttribute(npchar, "City"))//фикс ошибок в логе. у наёмных скелетов в пещере нет города.
	{
		NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
	    if (LoadSegment(NPChar.FileDialog2))// вызов диалога по городам <--
		{
	        ProcessCommonDialog(NPChar, Link, NextDiag);
			UnloadSegment(NPChar.FileDialog2);
		}
	}

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch(Dialog.CurrentNode)
	{
		case "First time":
            if (CheckAttribute(Pchar, "questTemp.CapBloodLine") && Pchar.questTemp.CapBloodLine == true)
            {
                dialog.Text = "Hello, Doctor.";
                Link.l1 = "And you don't get sick.";
				Link.l1.go = "exit";
				break;
    		}

			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = "Hello, "+GetAddress_Form(NPChar)+". As I know, you are captain of your own ship. I have a business conversation with you.";
					link.l1 = "I'm listening to you carefully, "+GetAddress_FormToNPC(NPChar)+". What is it about?";
					link.l1.go = "crew";
					link.l2 = "Sorry, "+GetAddress_FormToNPC(NPChar)+", but I'm in a hurry.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
					{
						dialog.text = "Welcome to our cozy cave! Make yourself at home.";
						link.l1 = "Thank you, kinsman. I'll take a look around.";
						link.l1.go = "UP_Skelet_Vihod";
						if (!checkattribute(pchar, "questTemp.UP_SkeletyVPeshere"))//Sinistra Нежить
						{
							link.l2 = "I have a suggestion for you.";
							link.l2.go = "crew";
						}
					}
					break;
				}
				dialog.text = LinkRandPhrase("Greetings, Captain! What do you want from a simple sailor?", "Hello, "+ GetSexPhrase("sir", "miss") +". What can I do for you?", "Good afternoon, dear. Did you want something?");
				link.l1 = "Glad to meet you, dear! My name is " + GetFullName(pchar)+". Do you have a minute to chat?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("I have a question for you.", "I need information about the affairs in this colony.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Just wanted say hello. Come on!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue") && pchar.questTemp.AnjelikaTichPrologue == "ATP")	//Sinistra Пролог Анжелика Тич
				{
					dialog.text = "Greetings, madam! What do you want from a simple sailor?";
					link.l1 = "Yes, I'm looking for my sister's fiance.";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
					DeleteAttribute(link, "l3");
				}
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")//Sinistra Нежить
				{
					dialog.text = "Welcome to our cozy cave! Make yourself at home.";
					link.l1 = "Thank you, kinsman. I'll take a look around.";
					link.l1.go = "UP_Skelet_Vihod";
					DeleteAttribute(link, "l2");
					DeleteAttribute(link, "l3");
				}
			}
			else
			{
				dialog.text = "It's you again, "+ GetSexPhrase("sir", "madam") +"? Is there anything else you wanted?";
				link.l1 = "Do you have a minute to chat about this and that?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("I have a question for you.", "I need information about the affairs in this colony.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "No, mate, nothing. Good luck!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+"at your service, my dear! What did you want to know?",
				"Glad to chat, Captain!",
				"Well, I guess I still have time...",
                "Unfortunately, I have to go. Have a nice day!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Can you tell me something interesting?",
				"Can you tell me something interesting?",
                "Can you tell me something interesting?",
				"Yes, of course. Good luck to you!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (drand(2))
			{
				case 0: sTemp = "Several of my friends and I were decommissioned after being injured. Now we have recovered and want to re-enlist as sailors. Would you like to join your team?"; break;
				case 1: sTemp = "Me and several guys were recently decommissioned from a merchant ship - the agreement with the owner expired. We've been stranded for days and we want to hire ourselves as sailors. Don't you need experienced sailors for your crew?"; break;
				case 2: sTemp = "My friends and I returned from a flight two weeks ago, the owner counted us out, and we had a lot of fun these days. However, the wind is whistling in the sailor's pocket, which means it's time to go to sea again. Will you hire us on your ship, Captain?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "Well, I'm ready to consider your offer. How many of you are there, and what do you know how to do on a ship?";
			link.l1.go = "crew_1";
			link.l2 = "I'm sorry, sailor, but my team is fully staffed. So you'll have to look for another captain.";
			link.l2.go = "exit";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = "And what do you want to offer me?";
				link.l1 = "I have a ship, and I want to hire your skinny guys to join my team, what do you say?";
				link.l1.go = "crew_1";
				link.l2 = "You know, I've changed my mind.";
				link.l2.go = "UP_Skelet_Vihod";
			}
			if (pchar.sex == "Skeleton" && npchar.sex == "man")	//Sinistra Нежить
			{
				link.l1 = "Sorry to disappoint you, sailor, but... I don't need the 'living' in the team. Hehe.";
				link.l1.go = "exit";
				DeleteAttribute(link, "l2");
			}
		break;

		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "Although we know how to handle sails and rigging better than anything else. Without too much modesty, I will say: we ate the dog in this case, so we will not let you down even in the most ferocious storm!"; break;
				case 1: sTemp = "However, we like the gun deck the most. We know how to handle guns like no one else in your team, I assure you. During a heated battle, you can safely rely on us!"; break;
				case 2: sTemp = "But our element is a boarding fight. The glitter of sabers, the smell of gunpowder and blood - that's our calling. We are not easy to deal with in battle, so in case of danger, our blades will help you out, Captain!"; break;
			}
			dialog.text = "Us "+sti(npchar.quest.crew.qty)+" people, and we will go to the service only together. We can do everything a sailor should. "+sTemp+"";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = "Us "+sti(npchar.quest.crew.qty)+" skeletons, and we will be glad to serve you as devoted servants.";
			}
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "Sounds very tempting. How much do you want in advance?";
				link.l1.go = "crew_2";
				link.l2 = "Sorry, sailor, but I was counting on something... different. You'll have to look for another captain.";
				link.l2.go = "exit";
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
				{
					link.l1 = "Yes, that's enough for me, and how much do you want?";
					link.l1.go = "crew_2";
					link.l2 = "It's not enough, forget it.";
					link.l2.go = "UP_Skelet_Vihod";
				}
			}
			else
			{
				if(GetCompanionQuantity(PChar) > 1)
				{
					ref rChar;
					for(int i = 1; i<GetCompanionQuantity(PChar); i++)
					{
						if (GetCompanionIndex(PChar,i)>-1)
						{
							rChar = &characters[GetCompanionIndex(PChar,i)];
							if(sti(rChar.index) != -1 && GetFreeCrewQuantity(rChar) >= sti(npchar.quest.crew.qty))
							{
								link.l1 = "I'm sorry, sailor, but I don't have seats on the ship for all of you. You'll have to go to my companion, his name is " + GetFullName(rChar) + ".";
								link.l1.go = "crew_comp";
								pchar.addcrew.character = rChar.id;
								if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
								{
									link.l1 = "I'm sorry, kinsman, but I don't have seats on the ship for all of you. You'll have to go to my companion, his name is "+ GetFullName(rChar) + ".";
									link.l1.go = "crew_comp";
								}
								break;
							}
						}
						else
						{
							link.l1 = "I'm sorry, sailor, but I don't have seats for all of you on any ship. You'll have to look for another captain.";
							link.l1.go = "exit";
							if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
							{
								link.l1 = "I'm sorry, kinsman, but I don't have seats for all of you on any ship. Stay here in the cave.";
								link.l1.go = "UP_Skelet_Vihod";
							}
						}

					}
				}
				else
				{
					link.l1 = "I'm sorry, sailor, but I don't have seats for all of you on any ship. You'll have to look for another captain.";
					link.l1.go = "exit";
				}
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
				{
					link.l1 = "I'm sorry, kinsman, but I don't have seats for all of you on any ship. Stay here in the cave.";
					link.l1.go = "UP_Skelet_Vihod";
				}
				link.l2 = "Sorry, sailor, but I was counting on something... different. You'll have to look for another captain.";
				link.l2.go = "exit";
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
				{
					DeleteAttribute(link, "l2");
				}
			}
		break;

		case "crew_comp":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" on my brother. Then the usual sailor's salary. We won't ask for too much, Cap.";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" on the skeleton. Then the usual sailor's salary. We won't ask for too much.";
			}
			if (sti(pchar.money) >= iTemp)
			{
				rChar = CharacterFromID(pchar.addcrew.character);
				link.l1 = "Agreed! Here's the whole amount. Go to the ship, it's called '"+rChar.ship.name+"', stands on the raid. The boatswain will give you places in the forecastle and give you a job.";
				link.l1.go = "crew_comp1";
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
				{
					link.l1 = "Agreed! Now get your bony asses up and get on the ship, it's called '"+rChar.ship.name+"'. So that everyone is in place in an hour.";
					link.l1.go = "crew_comp1";
				}
			}
			link.l2 = "Unfortunately, I cannot afford to pay for your services. You'll have to look for another captain.";
			link.l2.go = "exit";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				link.l2 = "You're asking too much, let's forget about it.";
				link.l2.go = "UP_Skelet_Vihod";
			}	
		break;

		case "crew_comp1":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "We're on our way, Captain! I'll get the guys together and we'll go on board immediately!";
			link.l1 = "Come on, hurry up, I'm not planning to stay here long.";
			link.l1.go = "crew_comp2";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = "We obey and obey, " + RandPhraseSimple("O lord!", "dark lord!");
				link.l1 = "That's better!";
				link.l1.go = "crew_comp2";
			}
		break;

		case "crew_comp2":
			DialogExit();
			rChar = CharacterFromID(pchar.addcrew.character);
			AddCharacterCrew(rChar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(rChar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(rChar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(rChar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(rChar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(rChar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				for (i=1; i<=15; i++)
				{
				sld = CharacterFromID("Skelet_Drug_"+i)
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 20.0);
				}
				pchar.questTemp.UP_SkeletyVPeshere = "SVP";
				SetTimerCondition("UP_SkeletyVPeshere_NanyatSnova", 0, 0, 2, false);	//Sinistra: скелетов можно будет нанимать через два дня!
			}
		break;

		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" on my brother. Then the usual sailor's salary. We won't ask for too much, Cap.";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" on the skeleton. Then the usual sailor's salary. We won't ask for too much.";
			}
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "Agreed! Here's the whole amount. Go to my ship, it's called '"+pchar.ship.name+"', stands on the raid. The boatswain will give you places in the forecastle and give you a job.";
				link.l1.go = "crew_3";
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
				{
					link.l1 = "Agreed! Now get your bony asses up and get on the ship, it's called '"+pchar.ship.name+"'. So that everyone is in place in an hour.";
					link.l1.go = "crew_3";
				}
			}
			link.l2 = "Unfortunately, I cannot afford to pay for your services. You'll have to look for another captain.";
			link.l2.go = "exit";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				link.l2 = "You're asking too much, let's forget about it.";
				link.l2.go = "UP_Skelet_Vihod";
			}			
		break;

		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "We're on our way, Captain! I'll get the guys together and we'll go on board immediately!";
			link.l1 = "Come on, hurry up, I'm not planning to stay here long.";
			link.l1.go = "crew_4";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = "We obey and obey, " + RandPhraseSimple("O lord!", "dark lord!");
				link.l1 = "That's better!";
				link.l1.go = "crew_4";
			}
		break;

		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				for (i=1; i<=15; i++)
				{
				sld = CharacterFromID("Skelet_Drug_"+i)
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 20.0);
				}
				pchar.questTemp.UP_SkeletyVPeshere = "SVP";
				SetTimerCondition("UP_SkeletyVPeshere_NanyatSnova", 0, 0, 2, false);	//Sinistra: скелетов можно будет нанимать через два дня!
			}
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this city, I ask you not to walk with a naked blade here.", "You know, as a citizen of this city, I ask you not to walk with a naked blade here.");
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// спайчекинг
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
		
		case "UP_Skelet_Vihod":
			DialogExit();
			sld = CharacterFromID("Skelet_Drug")
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
	}
}
