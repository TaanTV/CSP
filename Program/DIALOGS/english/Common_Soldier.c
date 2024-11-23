// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	int bribe_price = sti(PChar.rank) * (500) * (0.01 * (160 - GetSummonSkillFromName(PChar, SKILL_COMMERCE)));

	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
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
			// заглушка на нежить
			if (pchar.sex == "Skeleton" && GetCharacterEquipSuitID(pchar)!= "suit_1")
			{
				dialog.text = RandPhraseSimple("Are the living dead in the city?! To arms!!!", "Perish, evil spirits!!!");
				link.l1 = "For this audacity, I will take your soul, you fool!";
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				// заглушка на пирата
				if (sti(pchar.nation) == PIRATE)
				{
    				dialog.text = RandPhraseSimple("Are pirates in town?! Well, that's it... Grab "+ GetSexPhrase("him", "her") +"!!!", "This is a pirate!! Hold "+ GetSexPhrase("him", "her") +"!!!");
					link.l1 = RandPhraseSimple("Pirate, so what...", "Heh, try to grab it.");
					link.l1.go = "fight";
					break;
				}
				dialog.text = RandPhraseSimple("Spy? Surrender your weapons!! Follow me!", "Enemy agent! Immediately grab "+ GetSexPhrase("him", "her") +"!");
				link.l1 = RandPhraseSimple("Shut up, you little fool!", "Whatever it is!");
				link.l1.go = "fight";
				// ==> eddy. Засада, если опознали в инквизиции.
				if (Pchar.location == "Santiago_Incquisitio") StartIncquisitioAttack();
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Who are you and what do you need here?", "Wait! Who are you? On what basis are you trying to enter the city?");
					//==> по лицензии
					if (CheckNationLicence(sti(npchar.nation)))
					{
						link.l1 = "Officer, I have " + GetRusNameNationLicence(sti(npchar.nation)) + ", so I am here legally. Please familiarize yourself...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Can't you see the flag of " + NationNameGenitive(sti(pchar.nation)) + " is flying on my ship?!";
						}
						else //если причалил не в городе
						{
							link.l2 = "I anchored near " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " under the flag of " + NationNameGenitive(sti(pchar.nation)) + ". What else is not clear to you?";
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Pirates in town?! Well, that's it... Grab him!!", "It's a pirate!! Hold him!!!");
							link.l1 = RandPhraseSimple("Yes, pirate, so what...", "Heh, try to grab...");
							link.l1.go = "fight";
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Can't you see the flag of " + NationNameGenitive(sti(pchar.nation)) + " is flying on my ship?!";
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
						if (sti(rColony.HeroOwn) == true) // наш горожанин
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
									link.l1 = "I'm tired of this whining! You have enough booze on earth! Serve where captain put you! Otherwise, someone will have to be strung up as an example.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "I'll tell you a secret, Captain, the new governor is a bribe taker and embezzler. But of course it's none of my business...";
									link.l1 = "You're right, corsair: your job is to stand guard and keep order. Well, hanging the governor on a yardarm is already an occupation for me. Well done!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Thank you for not forgetting about us captain! We are for you in fire and in water!";
									link.l1 = "I know you crooks! Love only gold. There's a drinking party at the tavern today, I'm treating you. Don't forget to look in.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Eh, Captain! It's been a long time since we've been in a bloody fight! Well, which corsairs are cops?!";
									link.l1 = "Don't relax, corsair! Enemy armadas are prowling around our islands, so a bloodbath could happen at any moment.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Captain, they say the royal authorities are sending a squadron here again?";
									link.l1 = "Of course, corsair. As long as we are alive, there will never be peace. And even in Hell we will fight the devils!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! What a great party we had yesterday, Captain! It's a pity you weren't there.";
									link.l1 = "Never mind, I'll make up for my time. And I don't envy you guys.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "I'll tell you a secret, Captain, since you've never offended us, yesterday we flunked a chick here with the guys...";
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
						else
						{ // пираты, не наши
							dialog.text = LinkRandPhrase(RandPhraseSimple("Do you have business with me, Captain?", "I'm here on business, if you need something, ask, don't delay."), RandPhraseSimple("Captain, I'm very busy, so look for other interlocutors.", "Is something wrong, Captain? If there are no questions, then let me pass."), "Make way, Captain, I'm in a hurry.");
							link.l1 = LinkRandPhrase("Sorry, buddy, I mistaken.", "Okay, mind your own business.", "No, nothing.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("I have a couple of questions for you.", "I have a case for you."), RandPhraseSimple("I see you're in a hurry. One question and you'll be free.", "I wanted to ask something."), "Your business will wait. I'm going to ask you something.");
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("You look, "+ GetSexPhrase("what a bastard! He dared", "what a scoundrel! Dared") +" will appear in " + XI_ConvertString("Colony" + npchar.city)+ ". Hold "+ GetSexPhrase("him", "her") +"!!", "Ha, I recognized you, scoundrel! Grab "+ GetSexPhrase("him", "her") +"!!");
							link.l1 = RandPhraseSimple("Argh!..", "Well, you asked for it...");
							link.l1.go = "fight";
							break;
						}
					}
					//зачарованный город -->
					if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
					{
						dialog.text = LinkRandPhrase("Do you see what's going on in the city? But we won't interfere in anything...",
							"Until the unrest turns into pogroms, we will do nothing. Let them brawl.",
							"We behave as if everything is normal in the city. You must not give in to the mood of the crowd, otherwise the unrest may turn into a riot!");
						link.l1 = "I see...";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
					{
						dialog.text = "You went to the tavern. And what do you say?";
						link.l1 = "Nothing yet...";
						link.l1.go = "exit";
						break;
					}
					//<-- зачарованный город
					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar, "GenQuest.EncGirl") && CheckAttribute(pchar, "GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)
						{
							dialog.text = "Oh, what faces! Sama " + pchar.GenQuest.EncGirl.name + " she came to us in person! And how did you dare? And we've been looking for you already! Please go to the casemate, your cell has been prepared for a long time and is just waiting for you.";
							link.l1 = "What are you talking about?! You've made a mistake! We are with "+ GetSexPhrase("beau", "girlfriend") +" we walked in the jungle, picked flowers. Get off me! What kind of manners do these soldiers have?! As soon as they see a pretty girl, they immediately find a reason to cling! "+ GetSexPhrase("Honey, tell these blockheads to get out and not molest an honest lady", "Honey, tell these blockheads...") +"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)
						{
							dialog.text = "Here you are, beautiful. She came by herself! Your dad got the whole garrison on their feet, told them to find you and bring you home.";
							link.l1 = "Get off! I know where I'm going and I don't need your help!.. Captain, tell them to take their hands off.";
							link.l1.go = "GirlEnc_2";
						}
						DeleteAttribute(pchar, "GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "The regulations of the guard service do not allow me to chat with passers-by.";
							link.l1 = "Well done, soldier! Keep it up.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Is something wrong? Have you noticed any disturbances?";
							link.l1 = "No, it's okay. But your vigilance is commendable.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Fights and duels are prohibited on the streets of the city. Weapons can only be drawn in case of danger.";
							link.l1 = "Okay, I'll take that into consideration.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Oh, what a weather! And I'm stuck here like a statue... I'm just chasing flies.";
							link.l1 = RandPhraseSimple("Don't relax, soldier. The enemy is not asleep.", "It is not good to complain about the service. You can't fight a lot with this mood.");
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Look for another interlocutor, if you need to chat - I have been instructed to keep order, not to prattle.";
							link.l1 = "Well done, soldier, you are serving well! Just too rude.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Maintaining order, I'll tell you, it's not as easy as it might seem from the outside. This is a very responsible and dangerous job. Here was a case in the garrison...";
							link.l1 = LinkRandPhrase("Don't get distracted at the post.", "What kind of talk is on duty?!", "Stop where you put it. You'll prattle in the tavern.");
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = RandPhraseSimple("Don't distract me, " + GetAddress_Form(NPChar) + ", I'm on duty.", "Come on in, " + GetAddress_Form(NPChar) + ", do not distract the sentry from duty.");
							link.l1 = "I just "+ GetSexPhrase("checked", "checked") +"did you fall asleep on duty. You're standing there like a statue.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hey, " + GetAddress_Form(NPChar) + " Do you have a couple of sips of wine to wet your throat? I'm dying of thirst.";
							link.l1 = "A service is a service. Be patient until they change.";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("You are not the first sailor who has tried to distract me from my duty. Well, why don't appetizing widows come up to me", "Hey, beautiful! How about a little flirtation with the brave soldier") +"?";
							link.l1 = RandPhraseSimple("You've forgotten that you're on duty, not in a brothel.", "Your job is to keep order... and pick up the drool.");
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("You look like a tough guy! Don't you want to join the service? We have a spacious barracks, good food and drinks for free.", "Oh, you can't even imagine, girl, how nice it is to meet such a nice person like you in this backwater!") +"";
							link.l1 = ""+ GetSexPhrase("Tempting as hell, but I have to give up. Barracks drill is not for me.", "Thank you for the compliment, soldier, I am very pleased.") +".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "This heat... I would give half my life to be back in Europe.";
							link.l1 = RandPhraseSimple("Yeah, you're a lousy soldier.", "Military service is not sugar everywhere.");
							link.l1.go = "exit";
						break;
					}
					link.l3 = "A minute. I wanted to ask...";
					link.l3.go = "quests";//(перессылка в файл города)
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
		if (GetQuestPastDayParam("questTemp.LastBribe") > 0 || !CheckAttribute(pchar, "BribePrice"))
		{
			SaveCurrentQuestDateParam("questTemp.LastBribe");
			pchar.BribePrice = bribe_price;
		}
		if (IsCharacterPerkOn(pchar, "Adventurer") || IsCharacterPerkOn(pchar, "Agent"))
		{
			dialog.text = RandPhraseSimple("It seems to me that this is a hoax... Let's go to the commandant's office, "+ GetSexPhrase("darling", "darling") +", we'll figure it out there...", "Hmm, something tells me that you're not "+ GetSexPhrase("that", "that") +", who are you pretending to be... Immediately hand over your weapon, " + GetAddress_Form(npchar) + ", and follow me for further proceedings!");
			link.l1 = RandPhraseSimple("Why don't you believe me?", "Why such conclusions?");
			switch (rand(1))
			{
				case 0: link.l1.go = "NotPegYou"; break;
				else link.l1.go = "PegYou_2"; break;
			}
			if(bBribeSoldiers == true)
			{
				if(makeint(Pchar.money) >= sti(pchar.BribePrice))
				{
					link.l2 = RandPhraseSimple("There was a purse lying next to it, wasn't it yours? Wow, he's heavy, damn it! Here, keep it and don't waste any more. By the way, can I go?", "You've got me figured out. In fact, I just travel around the Caribbean and give money to those in need. They say the guards are not paid enough? This needs to be fixed. Let's start with you. Here you go. Is everything okay now?");
					link.l2.go = "NotPegYou_2";
				}
			}
		}
		else
		{
			if(bBribeSoldiers == true)
			{
				if(makeint(Pchar.money) >= sti(pchar.BribePrice))
				{
					link.l2 = RandPhraseSimple("There was a purse lying next to it, wasn't it yours? Wow, he's heavy, damn it! Here, keep it and don't waste any more. By the way, can I go?", "You've got me figured out. In fact, I just travel around the Caribbean and give money to those in need. They say the guards are not paid enough? This needs to be fixed. Let's start with you. Here you go. Is everything okay now?");
					link.l2.go = "NotPegYou_2";
				}
			}
			dialog.text = RandPhraseSimple("It seems to me that this is a hoax... Let's go to the commandant's office, "+ GetSexPhrase("darling", "darling") +", we'll figure it out there...", "Hmm, something tells me that you're not "+ GetSexPhrase("that", "that") +", who are you pretending to be... Immediately hand over your weapon, " + GetAddress_Form(npchar) + ", and follow me for further proceedings!");
			link.l1 = RandPhraseSimple("As if not so!", "After the rain, on Thursday...");
			link.l1.go = "fight";

		}
		if (!CheckAttribute(pchar, "questTemp.stels.landSolder"))
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		break;
		case "PegYou_2":
		dialog.text = RandPhraseSimple("You don't mess with my head! Hand over your weapons!", "Well, definitely a spy... Surrender immediately!");
		if(bBribeSoldiers == true)
			{

				if(makeint(Pchar.money) >= sti(pchar.BribePrice))
				{
					link.l2 = RandPhraseSimple("There was a purse lying next to it, wasn't it yours? Wow, he's heavy, damn it! Here, keep it and don't waste any more. By the way, can I go?", "You've got me figured out. In fact, I just travel around the Caribbean and give money to those in need. They say the guards are not paid enough? This needs to be fixed. Let's start with you. Here you go. Is everything okay now?");
					link.l2.go = "NotPegYou_2";
				}
			}
		link.l1 = RandPhraseSimple("As if not so!", "After the rain, on Thursday...");
		link.l1.go = "fight";
		if (!CheckAttribute(pchar, "questTemp.stels.landSolder"))
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Ah, I see... It's all right, you can go, " + GetAddress_Form(NPChar) + ".", "I'm a little tired on guard duty... It's okay, " + GetAddress_Form(NPChar) + ", I'm sorry.");
			link.l1 = "That's it!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "questTemp.stels.landSolder"))
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		break;
				case "NotPegYou_2":
			dialog.text = RandPhraseSimple("And thank you for that, " + GetAddress_Form(NPChar) + " " + " In parting, I'll give you a free tip: look at our port chief and ask for some paper. It will immediately become easier to live.", "I think there will be a lot more coins in your purse, " + GetAddress_Form(NPChar) + ", but okay, I'm kind today " + " In parting, I'll give you a free tip: look at our port chief and ask for some paper. It will immediately become easier to live.");
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			AddMoneyToCharacter(Pchar, -sti(pchar.BribePrice));

			pchar.questTemp.bribescount = sti(pchar.questTemp.bribescount) +1;
			if(sti(pchar.questTemp.bribescount) >= 10) UnlockAchievement("AchVzyatka", 1);
			if(sti(pchar.questTemp.bribescount) >= 25) UnlockAchievement("AchVzyatka", 2);
			if(sti(pchar.questTemp.bribescount) >= 50) UnlockAchievement("AchVzyatka", 3);

			pchar.BribePrice = sti(pchar.BribePrice) * 1.33;

			if (!CheckAttribute(pchar, "questTemp.stels.landSolder"))
			{
				AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 60);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
			if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 60);
				pchar.questTemp.stels.landSolder = GetDataDay();
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
				dialog.text = "Hmm, that's right. However, let me note that your license expires today. I'll let you through now, but you'll need to change your license to a valid one.";
				link.l1 = "Thanks, I'll get a new one at the first opportunity.";
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
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Hey, buddy, don't break anything at the lighthouse.", "The lighthouse is a very important object for the city. Be careful!");
			link.l1 = RandPhraseSimple("Okay, don't worry.", "Everything will be fine.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("No need to walk near the guns - this is a military facility!", "Access to the guns of unauthorized persons is strictly prohibited!", "If I notice that you are hanging around the guns - you are finished!");
			link.l1 = RandPhraseSimple("I got you.", "Okay, I got it.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице ==================
		case "SeekSpy_Checking":
			dialog.text = "Yes, I confirm. " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], "He's really a local.", "She really is a local resident.");
			link.l1 = RandPhraseSimple("I understand. Thanks for the help.", "Everything is clear. Thanks for the help.");
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

		// --> генератор "The Girl in the Jungle"
		case "GirlEnc_1":
			dialog.text = "And you, Captain, who are you? 'Fag' of the most famous thief in the whole settlement?";
			link.l1 = "Who are you calling a 'fag', dogshit?! Overheated in the sun?! Get your hands off the girl!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "Yes, actually, I just met...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+ GetSexPhrase("Sir", "Madam") +", we were ordered to detain her and escort her to the casemate. And you shouldn't think you can stop us.";
			link.l1 = "Let's check now...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterReputation(pchar, -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "GirlEnc_12":
			dialog.text = "Yes? You should have checked your pockets then. It's not even an hour... The lady is a professional with a capital letter 'P'";
			link.l1 = "Thank you, I will definitely check. It was necessary to make such a mistake...";
			link.l1.go = "GirlEnc_12End";
		break;

		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "GirlEnc_2":
			dialog.text = ""+ GetSexPhrase("Sir", "Madam") + " , we have been ordered to find this person and bring her to her father.";
			link.l1 = "Hmm, well, bring, if ordered.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "You're too late. I'm already taking her home.";
			link.l2.go = "GirlEnc_21";
		break;

		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("JungleGirl", "11");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "GirlEnc_21":
			ChangeCharacterReputation(pchar, 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Captain, we have orders and you are wrong to think that you can stop us.";
				link.l1 = "Let's check it out now...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Eh, "+ GetSexPhrase("lucky guy", "lucky girl") +". Her father promised to reward generously the one who returns her daughter..";
				link.l1 = "Don't despair, your rewards are still ahead.";
				link.l1.go = "exit";
			}
		break;

		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		// <-- генератор "The Girl in the Jungle"

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			dialog.text = LinkRandPhrase("Why are you brandishing a blade?! Put your weapons away immediately!", "I order you to put your weapons away immediately!", "Hey, " + GetAddress_Form(NPChar) + ", don't scare the people! Put away the weapon.");
			link.l1 = LinkRandPhrase("Okay, I'm removing...", "Already"+ GetSexPhrase("removed", "removed") +".", "Whatever you say...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("The hell with it!", "I'll put it into action now!", "I'll put it away when the time comes.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
			if(NPChar.chr_ai.type == "guardian") link.l1.go = "First Time";
		break;

	}
}
