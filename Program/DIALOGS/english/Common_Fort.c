// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Spy? Surrender your weapons!! Follow me!", "Enemy agent!! Immediately grab "+ GetSexPhrase("him", "her") +"!");
				link.l1 = RandPhraseSimple("Shut up, you little fool!", "Whatever it is!");
				link.l1.go = "fight";
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Who are you and what do you need here?", "Wait! Who are you? On what basis are you trying to enter the fort?");
					//==> по лицензии
					if (CheckNationLicence(sti(npchar.nation)))
					{
						link.l1 = "Officer, I have " + GetRusNameNationLicence(sti(npchar.nation)) + ", so I am here legally. Please familiarize yourself...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Pirates in the fort?! Hold "+ GetSexPhrase("him", "her") +"!!!", "Pirate sniffing around here!! Hold "+ GetSexPhrase("him", "her") +"!!!");
							link.l1 = RandPhraseSimple("Yes, pirate, so what...", "Heh, try to grab...");
							link.l1.go = "fight";
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Can't you see the flag flying on the mast of my ship " + NationNameGenitive(sti(pchar.nation)) + "?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "I anchored near " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " under the flag of " + NationNameGenitive(sti(pchar.nation)) + ". What else is not clear to you?";
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Eh, captain, how nice it was with you at sea! How many ships have we sunk under your command! And here...";
									link.l1 = "And here, my friend, charming women who do not happen at sea are constantly flashing in front of you.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Captain, what is the punishment for?! We're not land rats!";
									link.l1 = "Calm down, sailor! You're in an important and honorable position, so don't whine.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "How is it at sea, Captain? Will we ever see him again?";
									link.l1 = "Of course, sailor! Take a shift from the guard, go out to the pier and enjoy the sea as much as you want.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "I'm in a hurry to complain, Captain: We all want to go back to the sea. This service on land is just across the throat!";
									link.l1 = "I'm tired of this whining! You have enough booze on earth! Serve where the captain says! Otherwise, someone will have to be strung up as an example.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "I'll tell you a secret, Captain, the new governor is a bribe taker and embezzler. But of course it's none of my business...";
									link.l1 = "You're right, corsair: your job is to stand guard and keep order. Well, hanging the governor on a yardarm is already an occupation for me. Well done!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Thank you for not forgetting about us captain! We are for you in fire and in water!";
									link.l1 = "I know you crooks! Love only gold. There's a drinking party at the tavern today, I'm buying. Don't forget to look in.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Eh, Captain! Well, which of the corsairs are the guardians of order?! It's been a long time since we've been in a real case!";
									link.l1 = "Don't relax, corsair! Enemy armadas are prowling around our islands, so a bloodbath could happen at any moment.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Captain, they say the royal authorities are sending a squadron here again?";
									link.l1 = "Of course, corsair. As long as we are alive, there will never be peace. Even in Hell, we'll have to fight the devils!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! What a great party we had yesterday, Captain! It's a pity you weren't there.";
									link.l1 = "Never mind, I'll make up for my time. And I don't envy you guys.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "I'll tell you a secret, Captain, since you've never offended us, we flunked a chick here yesterday with the guys...";
									link.l1 = "Eh, corsair, the loop is crying for you!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Cap! Will you free me from this cursed duty! Well, I can't play the lawman here!";
									link.l1 = "You'd better remember: it's not easy to stand night watch on a ship either. Service, brother, it's service everywhere.";
									link.l1.go = "exit";
								break;
							}
							link.l2 = RandPhraseSimple("I have an important matter!", "I have a matter for you.");
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
					}
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Don't you see, I'm on duty! Don't distract me.";
							link.l1 = "Good, good...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Do you want to report something suspicious to me?";
							link.l1 = "No, nothing like that, besides, I'm captain. I see you're not listening anymore? Goodbye.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Remember, this is a military facility! So be quiet here.";
							link.l1 = "Okay, I'll take that into consideration.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "What is the weather, and I have to stand here. Eh, at least girls go to cities, but here there are only garrison rats around...";
							link.l1 = ""+ GetSexPhrase("I'm sorry. But I can't help you, this is your job.", "Hey! Am I not a girl?") +"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "If you want to chat, then find someone else, and I have to keep order, and I don't have time to prattle with you.";
							link.l1 = "No, I just"+ GetSexPhrase("checked", "checked") +"are you still alive, otherwise you're standing like a statue.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Do you think garrison days are toys? As if not so! This is a very responsible and dangerous job. I remember...";
							link.l1 = "Tell your story some other time, but now I'm in a hurry.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Be careful here, it's a fort! Be quiet...";
							link.l1 = "Whatever you say, soldier.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hey! Do you have any water? I'm dying of thirst.";
							link.l1 = "No, buddy, be patient...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("Oh, and boredom in the garrison, there are only uncouth louts like you around! But the city garrison is fattening...", "Hey, beautiful! How about a little flirtation with a brave soldier?") +"";
							link.l1 = ""+ GetSexPhrase("And this is called 'serving'? Look, you'll miss some spy!", "Your job is to keep order... and pick up the drool.") +"";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("You look like a tough guy! Do you want to join the garrison of the fort? We have a spacious barracks, two meals a day, plus free drinks.", "Oh, you can't even imagine, girl, how nice it is to meet such a nice person like you in this backwater!") +"";
							link.l1 = ""+ GetSexPhrase("Tempting as hell, but I have to give up. Barracks drill is not for me.", "Thank you for the compliment, soldier, I am very pleased.") +".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "This heat... I would give half my life to be back in Europe.";
							link.l1 = "Yes, I see you're not healthy for the climate here.";
							link.l1.go = "exit";
						break;
					}
					link.l3 = "Oh... clear. I wanted to ask...";
					link.l3.go = "quests";//(перессылка в файл города)
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			if (IsCharacterPerkOn(pchar, "Adventurer") || IsCharacterPerkOn(pchar, "Agent"))
			{
				dialog.text = RandPhraseSimple("It seems to me that this is a hoax... Let's go to the commandant, "+ GetSexPhrase("darling", "darling") +", we'll figure it out there...", "Hmm, something tells me that you're not "+ GetSexPhrase("that", "that") +", who are you pretending to be... Immediately hand over your weapon, " + GetAddress_Form(npchar) + ", and follow me for further proceedings!");
				link.l1 = RandPhraseSimple("Why don't you believe me?", "Why such conclusions?");
				switch (rand(1))
				{
					case 0: link.l1.go = "NotPegYou"; break;
					else link.l1.go = "PegYou_2"; break;
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("It seems to me that this is a hoax... Let's go to the commandant's office, "+ GetSexPhrase("darling", "darling") +", we'll figure it out there...", "Hmm, something tells me that you're not "+ GetSexPhrase("that", "that") +", who are you pretending to be... Immediately hand over your weapon, " + GetAddress_Form(npchar) + ", and follow me for further proceedings!");
				link.l1 = RandPhraseSimple("As if not so!", "After the rain, on Thursday...");
				link.l1.go = "fight";

			}
			if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		case "PegYou_2":
		dialog.text = RandPhraseSimple("You don't mess with my head! Hand over your weapons!", "Well, definitely a spy... Surrender immediately!");
		link.l1 = RandPhraseSimple("As if not so!", "After the rain, on Thursday...");
		link.l1.go = "fight";
		if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Ah, I see... It's okay, you can go, " + GetAddress_Form(pchar) + ".", "I'm a little tired on guard duty... It's okay, " + GetAddress_Form(pchar) + ", I'm sorry.");
			link.l1 = "That's it!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "questTemp.stels.landFort") || sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(sti(npchar.nation));
			if (iTemp == -1)
			{
				dialog.text = "Your license is subject to withdrawal, as it is expired and therefore invalid. Hand over your weapons and follow me for further proceedings!";
				link.l1 = RandPhraseSimple("As if not so!", "After the rain, on Thursday...");
				link.l1.go = "fight";
				TakeNationLicence(sti(npchar.nation));
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 20); // враг, которого узнали - потом будет умнее - бонус в скрытность
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm, that's right. However, let me note that your license expires today. I'll let you through now, but you'll need to get a new license.";
				link.l1 = "Thanks, I'll do it at the first opportunity.";
				link.l1.go = "exit";
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm, that's right. However, let me note that your license expires soon - it is still valid only for " + FindRussianDaysString(iTemp) + ". So keep in mind, " + GetAddress_Form(npchar) + ".";
				link.l1 = "Thanks, I'll get a new one at the first opportunity.";
				link.l1.go = "exit";
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Well, very well, your license is still valid " + FindRussianDaysString(iTemp) + ". You can go through.", "Everything is clear, "+GetAddress_Form(npchar)+". You can freely enter the city, your license is still valid " + FindRussianDaysString(iTemp) + ". I'm sorry to bother you.", "Everything is fine, " + GetAddress_Form(npchar) + ", I dare not detain you.");
				link.l1 = RandPhraseSimple("Excellent. Have a nice day.", "Thank you, Officer.");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			dialog.text = LinkRandPhrase("Why the hell are you running around the city with a naked blade? Put your weapon away immediately!", "I order you to sheathe your weapon immediately!", "Hey, "+ GetSexPhrase("buddy", "girlfriend") +" Stop scaring people! Sheathe your weapon.");
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("The hell with it!", "Dream ...", "After the rain, on Thursday.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
