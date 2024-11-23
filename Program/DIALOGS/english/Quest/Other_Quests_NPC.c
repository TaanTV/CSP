void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(NPChar.id == "Andre_Abel_Quest_Officer_1") // Офицер в резиденции Кюрасао. Сопровождение флейта "Orion"
			{
				dialog.text = LinkRandPhrase("Be polite to Mr. Governor-General.", "Don't you dare distract me!", "Keep in mind, the Governor-General has very little time!");
				link.l1 = "Yes, I know, I know...";
				link.l1.go = "exit";
			}

			if(NPChar.id == "Martin_Bleker")	// Мартин Блэкер
			{
				dialog.text = GetSexPhrase("So that's what 'Morgan's messenger' is like...","Ah... So you brought it...") + ". Well, welcome to our mansions.";
				//	link.l1 = "Go to hell!";
				//	link.l1.go = "Andre_Abel_Quest_In_Prison_Wrong_Way_1";
				link.l2 = "Your information is spreading fast... Thanks for the hospitality, but I'm not here for long.";
				link.l2.go = "Andre_Abel_Quest_In_Prison_1";
			}
			break;

		// Мартин Блэкер. Квест "Accompaniment of the Orion fluyt" -->
		case "Andre_Abel_Quest_In_Prison_Wrong_Way_1":
			dialog.text = "You shouldn't do that... But, it's your right... Tomorrow afternoon, our lifeless bodies will be the laughing stock of the public...";
			link.l1 = "I will be released soon... You'll see...";
			link.l1.go = "Andre_Abel_Quest_In_Prison_Wrong_Way_2";
			link.l2 = "Yes... If it's like you say, then we need to get out of here as soon as possible...";
			link.l2.go = "Andre_Abel_Quest_In_Prison_2";
			break;

		case "Andre_Abel_Quest_In_Prison_Wrong_Way_2":
			dialog.text = "I hope so...";
			link.l1 = "Me too.";
			link.l1.go = "Andre_Abel_Quest_In_Prison_Wrong_Way_3";
			break;

		case "Andre_Abel_Quest_In_Prison_Wrong_Way_3":
			DialogExit();
			SetLaunchFrameFormParam("Two days have passed...", "", 5, 3);
			LaunchFrameForm();
			break;

		case "Andre_Abel_Quest_In_Prison_1":
			dialog.text = "That's right, not for long... I heard the guards talking, and by the way, I learned about the 'messenger' from him... So they said you'd be hanged tomorrow.";
			link.l1 = "That's the devil!.. Your Stuyvesant is too quick on the uptake. I didn't leave any time for reflection at all...";
			link.l1.go = "Andre_Abel_Quest_In_Prison_2";
			break;

		case "Andre_Abel_Quest_In_Prison_2":
			dialog.text = "What's there to think about? If they are going to hang tomorrow, then you need to run today.";
			link.l1 = "Ho! Are you related to him, by any chance? He is also quick to make decisions.";
			link.l1.go = "Andre_Abel_Quest_In_Prison_3";
			break;

		case "Andre_Abel_Quest_In_Prison_3":
			dialog.text = "What kind of 'fast' is there?! I've been here for a year, and I've already prepared lockpicks and blades. I can't get through the guards alone, so I'm waiting for a traveling companion. And you "+ GetSexPhrase("the guy is strong","the girl is fighting") +", and you know how to fence, judging by the way you hold yourself... And God himself told you to run. So you can't find a better traveling companion. Hehe...";
			link.l1 = "Yeah, I was definitely lucky to have a cellmate. Won't the lockpicks let you down?";
			link.l1.go = "Andre_Abel_Quest_In_Prison_4";
			break;

		case "Andre_Abel_Quest_In_Prison_4":
			dialog.text = "Are you kidding? I unlock the door to the cell almost every night, smear the hinges with oil. At first, I even walked along the corridors, but it's too dangerous... So I'm fine here.";
			link.l1 = "Well, if that's the case, then go ahead? Where ours has not disappeared!.. By the way, what's your name?";
			link.l1.go = "Andre_Abel_Quest_In_Prison_5";
			break;

		case "Andre_Abel_Quest_In_Prison_5":
			dialog.text = "What? What's your name? My name is Martin Blacker... Put a candle for the repose, if I don't get out alive, otherwise it's not from my hand somehow without communion...I'll kick, hold the blade... Wrap the handle with a handkerchief, do you see the blade without a handle?";
			link.l1 = "Eh-eh, not flomberg, of course, but what there is, we'll get into trouble with that... Just in case, my name is " + GetFullName(pchar) + "... Well, with God.";
			link.l1.go = "Andre_Abel_Quest_In_Prison_6";
			break;

		case "Andre_Abel_Quest_In_Prison_6":
			DialogExit();
			NextDiag.CurrentNode = "Andre_Abel_Quest_In_Prison_7";
			LAi_SetCitizenType(NPChar);
			PChar.items.blade7 = 1;
			PChar.equip.blade = "blade7";
			NPChar.items.blade7 = 1;
			NPChar.equip.blade = "blade7";
			SetFunctionLocationCondition("Andre_Abel_Quest_Liberty", "Villemstad_ExitTown", false);
			SetFunctionNPCDeathCondition("Andre_Abel_Quest_Martin_Bleker_Is_Dead", "Martin_Bleker", false);
			ChangeCharacterAddressGroup(NPChar, "Villemstad_prison", "goto", "goto12");
			DoFunctionReloadToLocation("Villemstad_prison", "goto", "goto23", "Andre_Abel_Quest_Runaway_From_Prison");
			break;

		case "Andre_Abel_Quest_In_Prison_7":
			dialog.text = RandPhraseSimple("We need to hurry up.", "Rather, before the guards raise the alarm.");
			link.l1 = "Don't fuss. We haven't gotten out of such scrapes yet...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_Quest_In_Prison_7";
			break;

		case "Andre_Abel_Quest_In_Liberty_1":
			dialog.text = "I've been waiting for this moment for over a year! Thank you, Captain. I still had seven years to prepare.";
			link.l1 = "Thank you for that. I don't know how would I get out if there weren't your picks and blades.";
			link.l1.go = "Andre_Abel_Quest_In_Liberty_2";
			chrDisableReloadToLocation = false;
			break;

		case "Andre_Abel_Quest_In_Liberty_2":
			dialog.text = "Well? Did you run away? Goodbye, good luck to you.";
			link.l1 = "Goodbye...";
			link.l1.go = "Andre_Abel_Quest_In_Liberty_3";
			link.l2 = "Wait. And you're a smart guy, don't you want to join my team as a boarder?";
			link.l2.go = "Andre_Abel_Quest_In_Liberty_4";
			break;

		case "Andre_Abel_Quest_In_Liberty_3":
			DialogExit();
			NPChar.LifeDay = 0;
			LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			break;

		case "Andre_Abel_Quest_In_Liberty_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 24 && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 29)
			{
				dialog.text = "An officer? Hmm, why not, if we agree on the price.";
				link.l1 = "Don't worry about that. I won't hurt you in money.";
				link.l1.go = "Andre_Abel_Quest_In_Liberty_5";
			}
			else
			{
				dialog.text = "No, Captain... Don't forget, but I'm a man of a slightly different profession. Service is not for me.";
				link.l1 = "Okay, no, no. Good luck to you.";
				link.l1.go = "Andre_Abel_Quest_In_Liberty_3";
			}
			break;

		case "Andre_Abel_Quest_In_Liberty_5":
			dialog.text = "Then I agree!";
			link.l1 = "That's great. Welcome to the team!";
			link.l1.go = "Andre_Abel_Quest_In_Liberty_6";
			break;

		case "Andre_Abel_Quest_In_Liberty_6":
			dialog.text = "Thank you, Captain. I will try my best.";
			link.l1 = "I have no doubt about that.";
			link.l1.go = "Andre_Abel_Quest_In_Liberty_7";
			break;

		case "Andre_Abel_Quest_In_Liberty_7":
			DialogExit();
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
			LAi_SetStayType(NPChar);
			NPChar.Greeting = "Gr_Officer";
			NPChar.Money   = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;
			AddPassenger(PChar, NPChar, false);
			NPChar.OfficerWantToGo.DontGo = true;
			NPChar.HalfImmortal = true;  // Контузия
			NPChar.HeroModel = "OffOrion,OffOrion_1,OffOrion_2,OffOrion_3,OffOrion_4,OffOrion_5";
			NPChar.loyality = MAX_LOYALITY;
			AddQuestRecord("Andre_Abel_Quest", "19");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","a"));
			SetFunctionExitFromLocationCondition("Andre_Abel_Quest_Delete_Martin", PChar.location, false);
			break;
        	// <-- Мартин Блэкер. Квест "Accompaniment of the Orion fluyt"

		//--> работорговец, пинас
		case "TakeShoreCap":
    		dialog.text = "You rascal! Didn't expect?";
    		link.l1 = "Did not expect what?";
    		link.l1.go = "Node_1";
		break;

		case "Node_1":
			dialog.text = "Haha! There are no slaves here! Didn't you show them?";
			link.l1 = "Oh you... And I'm wondering where the soldiers on the merchant pinnace come from, and so many more... A trap!!";
			link.l1.go = "Node_2";
		break;

 		case "Node_2":
			dialog.text = "Yes bastard, this is a trap. And I'm not a merchant, but a combat officer! And even though you won the fight, you still won't escape justice.";
			link.l1 = "Why is that? I'm going to finish with you now, I'm going to put your trough to the bottom - and no one will know anything.";
			link.l1.go = "Node_3";
		break;

 		case "Node_3":
			dialog.text = "You're wrong. Your shady dealings with a local usurer have been uncovered. The governor-General will find out about it soon, and you will not get away from the gallows. Well, I'll try so that you don't live to see it.";
			link.l1 = "Try it, the governor's bloodhound!";
			link.l1.go = "Node_4";
		break;

 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Slave_arest":
			dialog.text = "" + GetFullName(pchar) + ", in the name of the law you are under arrest! Hand over your weapons immediately and follow us!";
			link.l1 = "What does this mean, Officer? On what basis?";
			link.l1.go = "Slave_arest_1";
		break;

		case "Slave_arest_1":
			dialog.text = "Don't pretend to be a sheep, Captain! Your dirty deeds are revealed. And for the massacre that you have committed, and for the sunk ship " + NationNameGenitive(sti(npchar.nation)) + ", you will hang out on the yardarm!";
			link.l1 = "Well, if that's the case... Then I have nothing left to lose, do I? Hold on, you dogs!";
			link.l1.go = "Slave_arest_2";
		break;

		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<--работорговец пинас

		//--> работорговец, крыса в доме
		case "Rat_bandos":
			dialog.text = "Hey! What are you forgetting here? Come on, get out of here!";
    		link.l1 = "You're not being very nice, my dear. Isn't that where that rat Gontier is hiding, huh?";
    		link.l1.go = "Node_rat_1";
		break;

		case "Node_rat_1":
			dialog.text = "There is no Gontier here! If that's all you wanted to find out - get out!";
			link.l1 = "It seems to me that you are lying. Now we will search the house and see...";
			link.l1.go = "Node_rat_2";
		break;

 		case "Node_rat_2":
			dialog.text = "Hey! Francois! Run! Guys, come to my aid!";
			link.l1 = "You dog!";
			link.l1.go = "Node_rat_3";
		break;

		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Rat_lover":
			dialog.text = "Ouch! Don't touch me!";
    		link.l1 = "Where is Francois Gontier? Answer me, you little bitch, or you'll follow your friends!";
    		link.l1.go = "Rat_lover_1";
		break;

		case "Rat_lover_1":
			dialog.text = "No, no, I'll tell you everything! He jumped out the window and ran away, apparently to his ship.";
    		link.l1 = "Which ship? His ship is not in port, I know that. Don't lie to me, honey, it's going to get worse...";
    		link.l1.go = "Rat_lover_2";
		break;

		case "Rat_lover_2":
			dialog.text = "I'm not lying, I swear! He said that he moored at a small island with a lighthouse on it, and reached the city by boat... He's there! Don't touch me!";
    		link.l1 = "Okay, it looks like you're not lying. Stay quiet and don't twitch. In general, you need to choose your friends wisely. Although, what kind of mind you have, I can see by your eyes, you're a fool.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;

		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		//<--работорговец крыса в доме

		//--> работорговец, беглые рабы
		case "Slave_woman":
			dialog.text = "Spare me! Have mercy! We surrender!";
    		link.l1 = "Is that so? Come on, everyone, get on the ship and into the holds! Anyone who makes an awkward move will be shot on the spot!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
		//<--работорговец беглые рабы

		//ОЗГ, Карлос Кассир
		case "Carlos":
            dialog.text = "Get out, whoever you are. See, I'm busy.";
            link.l1 = "Maybe I really should come back later... It stinks too much in here right now. I really didn't know that pigs are allowed in such establishments.";
            link.l1.go = "Carlos_7";
        break;

       	case "Carlos_3":
			Dialog.Text = "No, look at that! Look, don't regret it, Captain, no one will call Carlos the Cashier a coward with impunity! We'll meet outside the city gates in an hour, and we'll continue our conversation so as not to spoil the floors of this institution with your guts. I hope your courage will not leave you, and I'll shove your words into your...";
			link.l1 = "That's enough, dear. Save your fervor for confirming your words. I'll be there in an hour, and if I don't find you there, then be sure that the fame of the cowardice of the condottiere Cashier will find you everywhere, no matter what crevice you hide in.";
			link.l1.go = "Carlos_4";
			pchar.questTemp.Headhunter = "hunt_carlos_fight";
        break;

		case "Carlos_4":
			LAi_LocationDisableOfficersGen(pchar.questTemp.Headhunter.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.questTemp.Headhunter.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			AddQuestRecord("Headhunt", "2_1");
			pchar.quest.HeadhunterTimer.win_condition.l1 = "Timer";
			pchar.quest.HeadhunterTimer.win_condition.l1.date.hour  = sti(GetTime() + 1);
			pchar.quest.HeadhunterTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.HeadhunterTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.HeadhunterTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.HeadhunterTimer.function = "CarlosDuel";
			SetFunctionTimerCondition("CarlosDuelOver", 0, 0, 2, false);
			NextDiag.CurrentNode = "Carlos_5";
			DialogExit();
		break;

		case "Carlos_5":
			Dialog.Text = "Well, what else do you want?";
			link.l1 = "Just decided to remind you of our meeting.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "Carlos_5";
        break;

		case "talk_off_town_Carlos":
			Dialog.Text = "Well, that's it, "+ GetSexPhrase("chatty puppy","chatty trash") +"! Now you will regret that you gave birth into the light!";
			link.l1 = "I see you brought company with you, dog? So much the better – you won't be lonely in hell. To the point!";
			link.l1.go = "Carlos_6";
			chrDisableReloadToLocation = true;
		break;

		case "Carlos_6":
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "CarlosDie");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Carlos_7":
			dialog.text = "Wait a minute"+ GetSexPhrase("guy","girl") +"... I don't like your tone. Do you have any idea who you're talking to, hero?";
			link.l1 = "I'm talking to a drunken pig who took over the place where I was going to spend the evening. And now everything here stinks hopelessly, like in a barn – what a shame, isn't it?";
			link.l1.go = "Carlos_8";
		break;

		case "Carlos_8":
			dialog.text = "You are a "+ GetSexPhrase("brave puppy","brave girl") +", as I see... I am Carlos the Cashier – everyone in this city and in many others knows my name and my sword has already counted fifty arrogant talkers. My advice to you is to get out of here before I clip your tongue. I don't want to ruin a good evening.";
			link.l1 = "For a pig, you are surprisingly polite. Or, more likely, it's cowardice... It's really a pity.";
			link.l1.go = "Carlos_3";
			int n = FindLocation(pchar.questTemp.Headhunter.City + "_Brothel");
			locations[n].reload.l2.disable = true;
		break;
		//ОЗГ, Карлос Кассир

		//ОЗГ, Ганнибал Хоум
		case "Houm":
            dialog.text = "Go away, man from the sea. You're standing in the way of the black lion.";
        	link.l1 = "Politeness is the lot of people, but not animals – I see you are not familiar with it.";
            link.l1.go = "Houm_1";
        break;

		case "Houm_1":
            dialog.text = "Is the ship's mouse trying to annoy the lion? Boldly, but stupidly, the lion does not notice those who are crawling in the ground under his feet.";
        	link.l1 = "Maybe you'll notice my sword, sir 'lion'?";
            link.l1.go = "Houm_2";
        break;

		case "Houm_2":
            dialog.text = "Brave little mouse... You were paid by the Dutch jackals, right? They want to get the lion that wounded them with someone else's hands, and they promise gold to the one who does not coward. I know that only gold makes you white people forget fear. Remember him before the lion gets really angry.";
        	link.l1 = "Enough reasoning, black image. Let's leave this diplomacy and talk openly.";
            link.l1.go = "Houm_3";
        break;

		case "Houm_3":
            dialog.text = "The black lion will listen, but be short, Dutch mercenary.";
        	link.l1 = "I don't work for the authorities, black dog. My brother was on the Dutch ship that you sank. And I want you to answer for his death.";
            link.l1.go = "Houm_4";
        break;

		case "Houm_4":
            dialog.text = "Ha, the lion is surprised. In front of him is not a mouse who fancies himself a hunter for Dutch coins, but wolf, wishing to avenge a brother? The spit accepts your challenge with dignity. Do not disturb the peace of this city – the lion will be waiting for the hunter in the sea. Fight like it should, and die like a warrior, and the lion will eat your heart, and the courage of the hunter will continue to live after "+ GetSexPhrase("his","her") +" death.";
        	link.l1 = "Go to your ship, scum, and get ready to drown with it!";
            link.l1.go = "Houm_5";
			AddQuestRecord("Headhunt", "6");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","a"));
			pchar.quest.Headhunter_HoumAttack.win_condition.l1 = "location";
            pchar.quest.Headhunter_HoumAttack.win_condition.l1.location = pchar.questTemp.Headhunter.Island;//отправляем в локацию
            pchar.quest.Headhunter_HoumAttack.function = "Headhunter_CreateHoumShips";//создание кораблей
        break;

		case "Houm_5":
			if (findsubstr(PChar.location, "_tavern" , 0) != -1)
			{
				DialogExit();
				NextDiag.CurrentNode = "Houm_6";
			}
			else
			{
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
			}
			DialogExit();
        break;

		case "Houm_6":
			Dialog.Text = "Well, what else do you want?";
			link.l1 = "Just decided to remind you of our meeting.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "Houm_6";
        break;

		case "RatOfficer":
			int iGoods1 = 400 - GetSquadronGoods(Pchar, GOOD_EBONY);
			int iGoods2 = 500 - GetSquadronGoods(Pchar, GOOD_MAHOGANY);
			int iGoods3 = 670 - GetSquadronGoods(Pchar, GOOD_SANDAL);
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if(pchar.questTemp.Headhunter == "Rat_officer" && GetCompanionQuantity(pchar) == 1 && 3-sti(RealShips[sti(pchar.ship.type)].Class) <= 0)
				{

					if(iGoods1 < 1 || iGoods2 < 1 || iGoods3 < 1)
					{
						dialog.text = "Well, what do you want? Get lost, I'm not in the mood to chat.";
						link.l1 = "I'm just off the flight... I want a drink, not with anyone. Will you join the company? I'm buying!";
						link.l1.go = "RatOfficer_1";
					}
					else
					{
						dialog.text = "Well, what do you want? Get lost, I'm not in the mood to chat.";
						link.l1 = "I don't want to chat with you. Have a nice rest.";
						link.l1.go = "exit";
						NextDiag.TempNode = "RatOfficer";
					}
					break;
				}
			}
			dialog.text = "What do you want? Get lost, I'm not in the mood to chat.";
			link.l1 = "I don't want to chat with you. Have a nice rest.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RatOfficer";
		break;

		case "RatOfficer_1":
			dialog.text = "Ah, well, then it's another matter. Have a seat.";
			link.l1 = "Here! You are a real sailor!";
			link.l1.go = "RatOfficer_1_sit";
		break;

		case "RatOfficer_1_sit":
			NextDiag.CurrentNode = "RatOfficer_2";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.5);
			DoQuestReloadToLocation("Tortuga_tavern", "sit", "sit1", "");
			LAi_SetSitType(Pchar);
			DialogExit();
		break;

		case "RatOfficer_2":
			dialog.text = "Pour, "+ GetSexPhrase("guy","girl") +"! I see you're no less than a captain! Where are you heading from?";
			link.l1 = "Argh, what a rum! What? Ah, we came from Martinique, from Martinique. We are trading, slowly.";
			link.l1.go = "RatOfficer_3";
		break;

		case "RatOfficer_3":
			dialog.text = "Are you trading? Well, that's a good thing. We are also merchants - saw the pinnace at the port?";
			link.l1 = "Yes, trade is a good thing, only pirates, damn them, don't give a living at all... Even caravans are attacked, not like single ships. And my master, damn him, bought a full hold of valuable timber...ick!";
			link.l1.go = "RatOfficer_4";
		break;

		case "RatOfficer_4":
			dialog.text = "Is your master rich, perhaps?";
			link.l1 = "He's not poor. Greedy only very much. I told him to equip an escort, hire a security vessel, well, look for a traveling companion, as a last resort... But no, he feels sorry for the money! I'll have to walk all the way to Belize alone.";
			link.l1.go = "RatOfficer_5";
		break;

		case "RatOfficer_5":
			dialog.text = "Yes, it's not safe at sea these days. And all the damn Buccaneers...ik! Hunters! What hunters they are! Honest traders like you and me, they are hunters...";
			link.l1 = "Yes, you're damn right! It's all because of them, the apostates. Eh, and how can you get from Tortuga to Belize alone? But even on the way to the Gulf of Doom, it is necessary to go in - the owner ordered to make a deal with the Indians there - to buy precious stones from them for a song, and replenish fresh water supplies... Listen, are you heading in the wrong direction by any chance? Maybe...";
			link.l1.go = "RatOfficer_6";
		break;

		case "RatOfficer_6":
			dialog.text = "No, we are completely...ick! We're going in a completely different direction.";
			link.l1 = "Oh, it's a pity. Well, let's pray to the Almighty that he will protect us on the way... There is little hope for guns - the goods take up all the space in the hold, there is almost no place left for bullets and gunpowder... Here it is, human greed!";
			link.l1.go = "RatOfficer_7";
		break;

		case "RatOfficer_7":
			dialog.text = "Greed... Greed is... IC, it's bad. They count every peso, they are ready to strangle themselves for a gold coin. They don't see the light of God behind their purse and don't let others live. Am I right, Captain?";
			link.l1 = "You're a hundred times right, my friend! When the pirates attack, I don't even have anything to fight back with. There are two volleys of charges in the guns, and the boarding party has three cripples and two rookies... Oh, our share, our share...";
			link.l1.go = "RatOfficer_8";
		break;

		case "RatOfficer_8":
			dialog.text = "Don't worry about it! What's the first time, or what? Let's have a drink, otherwise it's time for me to get back to my boat.";
			link.l1 = "Well, let's have one more, and I'm off too... All seventy-five did not return until-oh, my, they drowned in the depths of the sea... Goodbye, my friend...";
			link.l1.go = "RatOfficer_9";
			pchar.quest.Headhunter_Ratgulf.win_condition.l1 = "location";
            pchar.quest.Headhunter_Ratgulf.win_condition.l1.location = "Shore_ship2";//отправляем в локацию
            pchar.quest.Headhunter_Ratgulf.function = "Headhunter_Ratgulf";
			SetFunctionTimerCondition("Headhunter_RatgulfOver", 0, 0, 15, false);//таймер
		break;

		case "RatOfficer_9":
			pchar.quest.Headhunter_RatOfficerOver.over = "yes";
			LAI_SetPlayerType(pchar);
			LAI_SetSitType(npchar);
            DoQuestReloadToLocation("Tortuga_tavern", "goto", "goto2", "");
			AddQuestRecord("Headhunt", "18");
			pchar.questTemp.Headhunter = "Rat_gulf";
			NextDiag.CurrentNode = "RatOfficer_10";
			npchar.lifeDay = 0;
			DialogExit();
		break;

		case "RatOfficer_10":
			dialog.text = "Look at the dead man's chest... ick!";
			link.l1 = "Understood.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RatOfficer_10";
		break;

		//ОЗГ, кэп-Крыса
		case "Rat_talk":
			dialog.text = "Argh! So you're not a merchant?";
			link.l1 = "No, Rat. You made a mistake this time. Instead of valuable wood, cold steel and hot lead are waiting for you. Your adventures will end here in this bay.";
			link.l1.go = "Rat_talk_1";
		break;

		case "Rat_talk_1":
			dialog.text = "I will not give up so easily, although the boarding has already been lost. You'll find out what it means to get in touch with a Rat! Ja Preston will avenge me!";
			link.l1 = "Now you're going to tell your fables to the devils in hell. Ready to fight, you bastard!";
			link.l1.go = "Rat_talk_exit";
		break;

		case "Rat_talk_exit":
 		    pchar.questTemp.Headhunter = "hunt_rat_yes1";
            AddQuestRecord("Headhunt", "23");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","a"));
            pchar.quest.Headhunter_DieHard.over = "yes";
			pchar.quest.Headhunter_AfterBattle.over = "yes";
            Island_SetReloadEnableGlobal("Beliz", true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "RatHunters":
			//dialog.text = "...";
			link.l1 = "Ah?! What? What the hell are you doing here? Who let you in here?";
			link.l1.go = "RatHunters_1";
		break;

		case "RatHunters_1":
			dialog.text = "Ja Preston sends his regards...";
			link.l1 = "What? Oh, devil!";
			link.l1.go = "RatHunters_2";
		break;

		case "RatHunters_2":
			LAi_SetFightMode(pchar, true);
			LAi_LockFightMode(pchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "RatHunters_Dead");
			if (startHeroType == 2)
			{
				if(CheckAttribute(pchar,"Whisper.EsFriendTown") && pchar.Whisper.EsFriendTown == "Villemstad")
				{
					ref sldd = CharacterFromID("W_Chard");
					ChangeCharacterAddressGroup(sldd, "Villemstad_tavern", "reload", "reload1");
					LAi_LocationFightDisable(loadedLocation, false);
				}

			}
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Halen":
			dialog.text = "You pushed me, "+ GetSexPhrase("kind","kind") +"! It makes some sense, or is it a misunderstanding?";
			link.l1 = "Are you Martin Van Halen?";
			link.l1.go = "Halen_1";
		break;

		case "Halen_1":
			dialog.text = "Yes, that's my name, but you still haven't told me yours? Do you mind explaining whatever you want, or get out. Don't try my patience - I have no desire to waste my time talking to the rabble.";
			link.l1 = "Yes... Really - banal, strewn with the authorities of the fop. Excess of politeness you do not die. But from an excess of arrogance - it is possible. Have you not been told that arrogant dumbasses do not linger in this world, even if they are welcomed by dignitaries?";
			link.l1.go = "Halen_2";
			link.l2 = "Hmm... just wantedto meet the famous Dutch corsair.";
			link.l2.go = "Halen_3";
		break;

		case "Halen_2":
			dialog.text = "Argh! I've never heard such insolence from anyone! Don't bother to answer - I can see you hardly speak. Insult you, I guess I won't succeed - all the epithets will be only flattery against you! Bare your sword, "+ GetSexPhrase("worm","whore") +"if you know how to hold it down! I want satisfaction immediately. Otherwise I'll just stab you like a pig!";
			link.l1 = "Hold on, you bastard!";
			link.l1.go = "Halen_fight";
		break;

		case "Halen_fight":
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "HOLLAND_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");

		break;

		case "Halen_3":
			dialog.text = "Satisfied"+ GetSexPhrase("yen","yen") +" acquaintance? Now - get off the devil and stop your eye-sore, redneck!";
			link.l1 = "Hmm...";
			link.l1.go = "exit_halen";
		break;

		case "Halen_4":
			dialog.text = "Are you again? Do the courtesy - go already "+ GetSexPhrase("to the tavern, under the table to scraps and other garbage","to the brothel, entertain a drunken matron") +". That's where you belong.";
			link.l1 = "Hmm...";
			link.l1.go = "exit_halen";
			link.l2 = "I'll teach you some courtesy, you arrogant Dutch pig!";
			link.l2.go = "Halen_2";
			NextDiag.CurrentNode = "Halen_4";
		break;

		case "exit_halen":
			LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "Headhunter_HalenOut", -1);
            LAi_Actor2WaitDialog(npchar, pchar);
			NextDiag.CurrentNode = "Halen_4";
            DialogExit();
		break;

		case "Miko":
			dialog.text = "What do you want from me?";
			link.l1 = "So... you are Miko Pistoliero?";
			link.l1.go = "Miko_1";
		break;

		case "Miko_1":
			dialog.text = "Yes, I am. To what do I owe the pleasure?";
			link.l1 = "I need to talk to you about Jar Preston. I really want to meet him.";
			link.l1.go = "Miko_2";
		break;

		case "Miko_2":
			dialog.text = "Yeah... Okay. That's it. So you are "+ GetSexPhrase("that guy","that girl") +" which we are looking for... You came... Well, it makes my task much easier. I don't think you'll just walk away from here.";
			link.l1 = "Yes, it's me. Tell me where Preston is and you'll live.";
			link.l1.go = "Miko_3";
		break;

		case "Miko_3":
			dialog.text = "You threaten me, "+ GetSexPhrase("friend","girl") +"? In vain. You are a stranger here, and we will all tear you to shreds. As for my patron, he is not far. Much closer than you think. But you will never find Ja - because you found ME, ha-ha-ha!!";
			link.l1 = "Well, you bastard, you chose your own fate...";
			link.l1.go = "Miko_fight";
			pchar.questTemp.Headhunter = "miko_mustdie";
			pchar.quest.Headhunter_Miko_mustdie.win_condition.l1 = "NPC_Death";
			pchar.quest.Headhunter_Miko_mustdie.win_condition.l1.character = "Miko";
			pchar.quest.Headhunter_Miko_mustdie.function = "Miko_die";
		break;

		case "Miko_fight":
			chrDisableReloadToLocation = true;
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "Pearlgroup_2");
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Headhunt", "34");
		break;

		case "JaHunters":
			dialog.text = "And here is "+ GetSexPhrase("our friend","our friend") +"!";
			link.l1 = "My God... Again!";
			link.l1.go = "JaHunters_1";
		break;

		case "JaHunters_1":
			dialog.text = "Ja Preston asked me to say hi to you...";
			link.l1 = "Ah-ah!!";
			link.l1.go = "JaHunters_2";
		break;

		case "JaHunters_2":
			LAi_SetImmortal(npchar, false);
			pchar.quest.Headhunter_Find_Ja.win_condition.l1 = "location";
			pchar.quest.Headhunter_Find_Ja.win_condition.l1.location = "SantaCatalina";
			pchar.quest.Headhunter_Find_Ja.function = "Create_Ja";
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FindJa");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Ja_talk":
			dialog.text = "So we meet, finally... Well, we'll kill each other, or maybe talk?";
			link.l1 = "Glad to see you. Otherwise all greetings and greetings... Raise your blade, Preston, I want to finish you once and for all.";
			link.l1.go = "Ja_talk_1";
			link.l2 = "Let's have a conversation, if you suggest. You will not run away from here... What is there to talk about, I wonder?";
			link.l2.go = "Ja_talk_3";
		break;

		case "Ja_talk_1":
			dialog.text = "Well... Then let's continue!";
			link.l1 = "Argh! Hang on!";
			link.l1.go = "Ja_talk_exit";
		break;

		case "Ja_talk_exit":
 		    pchar.questTemp.Headhunter = "hunt_ja_yes";
            bQuestDisableMapEnter = false;
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Ja_talk_3":
			dialog.text = "Why the hell are you hunting me? Why did you kill all my people?";
			link.l1 = "Argh! I think you're the one who's been hunting me! As for your question, your gang has been poisoning the lives of people at Le Francois so much. So we decided to get rid of you...";
			link.l1.go = "Ja_talk_4";
		break;

		case "Ja_talk_4":
			dialog.text = "Here's the devil! Rogers got wind of what we were up to... I should have been more careful.";
			link.l1 = "It's too late now, Ja. It's time to end this conversation - I think you've learned everything you wanted to know. I have nothing more to say to you.";
			link.l1.go = "Ja_talk_5";
		break;

		case "Ja_talk_5":
			dialog.text = "Wait... look, I'll give you another one. You are "+ GetSexPhrase("a desperate and intelligent corsair","a desperate and intelligent girl") +" and I... I lost my game. I have no more people and no ship - you won boarding. Even if I can kill you now, the end is still the same. Why don't we join forces? I propose a change from hostility to peace, and I am ready to work with you, under your command.";
			link.l1 = "No, Jia. I don't believe you. Today you're my officer, tomorrow you stab me in the back? It's time to end our confrontation!";
			link.l1.go = "Ja_talk_1";
			link.l2 = "Ha! That's interesting! And you know, Ja - I agree. An officer like you, still need to look. But look - if you make jokes - I'll send you overboard in a jiffy!";
			link.l2.go = "Ja_talk_6";
		break;

		case "Ja_talk_6":
			dialog.text = "The warning is unnecessary, Captain. For me now the safest place in the archipelago - your vessel. You can not doubt me. I'm glad we agreed.";
			link.l1 = "Welcome to the team, corsair!";
			link.l1.go = "Ja_hired";
			pchar.quest.Headhunter_AfterBattleJa.over = "yes";
		break;

		case "Ja_hired":
			bQuestDisableMapEnter = false;
			characters[GetCharacterIndex("Jafar")].lifeDay = 0;
			pchar.questTemp.Headhunter = "end_quest_full";
			AddQuestRecord("Headhunt", "38");
			CloseQuestHeader("Headhunt");
			pchar.questdata.Kondotier = 1;
			sld = GetCharacter(NPC_GenerateCharacter("Jafarry", "QuestCaptain", "man", "man", 25, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 25, 70, 70, "blade14", "pistol6", 100);
			sld.name = "Ja";
			sld.lastname = "Preston";
			sld.greeting = "Gr_Officer";
			sld.rank = 25;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			sld.HoldEquip = true;
			SetSelfSkill(sld, 80, 80, 75, 80, 80);
			SetShipSkill(sld, 60, 50, 60, 60, 65, 70, 60, 60, 60);
			SetSPECIAL(sld, 9, 9, 10, 10, 8, 10, 10);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "Ciras");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			//SetCharacterPerk(sld, "Medic");
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.HalfImmortal = true;  // Контузия
			sld.HeroModel = "QuestCaptain,QuestCaptain_1,QuestCaptain_2,QuestCaptain_3,QuestCaptain_4,QuestCaptain_5";
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			AddDialogExitQuestFunction("Pascal_Escape");
			QuestAboardCabinDialogNotBattle();
            DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
				
		case "AscoldSpainCapitain":
			pchar.questTemp.Ascold.SpainCapitainDialogue = true;
			dialog.text = "Enough! Please, stop!";
			link.l1 = "Whats wrong? Spaind trusted to coward?";
			link.l1.go = "AscoldSpainCapitain_offer_1";
		break;	
		
		case "AscoldSpainCapitain_offer_1":
			dialog.text = "I don't know what's your need, I suggest a deal..";
			link.l1 = "Do you have inventory list?!";
			link.l1.go = "AscoldSpainCapitain_offer_2";
		break;
		
		case "AscoldSpainCapitain_offer_2":
			dialog.text = "I don't have any lists. ABy the way, in this battle - list could appear on the sea bottom...";
			link.l1 = "Ah... You know where is it! Tell me now!";
			link.l1.go = "AscoldSpainCapitain_offer_3";
		break;
		
		case "AscoldSpainCapitain_offer_3":
			dialog.text = "I will! But promise that you leave me and let take my stuff with 250,000 piastres! Also let me leave your board in safe place for me!";
			if (sti(pchar.money) < 250000)
			{
			link.l1 = "I don't have such money. By the way, I'm not willing to let you live!";
			link.l1.go = "AscoldSpainCapitain_fight";
			}
			else
			{
			link.l1 = "You have my word. We have no more time. Where is list?!";
			link.l1.go = "AscoldSpainCapitain_offer_accepted";			
			link.l2 = "Fuck it all! I'll manage it myself!";
			link.l2.go = "AscoldSpainCapitain_fight";
			}
		break;
	
		case "AscoldSpainCapitain_offer_accepted":
			AddMoneyToCharacter(Pchar, - 250000);
			AddMoneyToCharacter(NPchar, 250000);
			dialog.text = "It's " + GetStrSmallRegister(XI_ConvertString(pchar.questTemp.Ascold.ShipType)) +" '"+pchar.questTemp.Ascold.ShipName+"'.";
			if (CheckAttribute(PChar, "questTemp.Ascold.Ship.foundcheck") && !CheckCharacterItem(pchar, "ShipsJournal"))
			{
				link.l1 = "Shit! I've already checked it, and didn't manage to find any fucking thing! Die!";
				link.l1.go = "AscoldSpainCapitain_fight";	
			}
			else if (LAi_IsDead(CharacterFromID(pchar.questTemp.Ascold.Ship)))
			{
			link.l1 = "Shit! I cant find anything there already... So, our deal has gone! Die!";
			link.l1.go = "AscoldSpainCapitain_fight";
			}
			else 
			{
				link.l1 = "Great!";
				link.l1.go = "AscoldSpainCapitain_agreed";
			}
		break;
		
		case "AscoldSpainCapitain_fight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AscoldSpainCapitain_agreed":
			NPChar.LifeDay = 0;
			QuestAboardCabinDialogNotBattle();
			DialogExit();
		break;

			
		// СФ -->
		
		case "SF_InvitingOfficer":
			SaveCurrentQuestDateParam("InvitingOfficerDialogue");
			dialog.text = "Hello, " + GetAddress_Form(pchar) + ". Your name " + pchar.name + "?";
			link.l1 = "Yeah, that's right.";
			link.l1.go = "SF_InvitingOfficerToHuber";
		break;
		
		case "SF_InvitingOfficerToHuber":
			dialog.text = "His Excellency the Governor-General of Port Royal, Sir Thomas Madiford, wishes to see you. As soon as you have finished your business in port, please report at once to his residence.";
			link.l1 = "Я вольный капитан. Мне совершенно не интересно шляться по лощёным залам губернаторского дворца.";
			link.l1.go = "SF_InvitingOfficerToHuberFirstCancel";
			link.l2 = "Okay, I'll be there.";
			link.l2.go = "SF_InvitingOfficerToHuberTaken";
		break;
		
		case "SF_InvitingOfficerToHuberFirstCancel":
			dialog.text = "Are you sure? When you change your mind, I'm sure His Excellency won't need you anymore...";
			link.l1 = "All right, you've convinced me. I'll be there.";
			link.l1.go = "SF_InvitingOfficerToHuberTaken";
			link.l2 = "I'm pretty sure.";
			link.l2.go = "SF_InvitingOfficerToHuberCancelConfirmation";
		break;
		
		case "SF_InvitingOfficerToHuberTaken":
			dialog.text = "He'll be waiting for you. Goodbye, " + GetAddress_Form(pchar) + ".";
			link.l1 = "Goodbye.";
			link.l1.go = "SF_InvitingOfficerToHuberExit";
			pchar.questTemp.silverfleet = "ToHuber";
		break;
		
		case "SF_InvitingOfficerToHuberCancelConfirmation":
			dialog.text = "It's your right to refuse. Goodbye, " + GetAddress_Form(pchar) + ".";
			link.l1 = "Goodbye.";
			link.l1.go = "SF_InvitingOfficerToHuberExit";
		break;
		
		case "SF_InvitingOfficerToHuberExit":
			LAi_SetCitizenTypeNoGroup(NPchar);
			NextDiag.TempNode = "SF_InvitingOfficerToHuberWaiting";
    			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SF_InvitingOfficerToHuberWaiting":
			dialog.text = "I have no orders to escort you to His Excellency, " + GetAddress_Form(pchar) + ".";
			link.l1 = "All right, all right.";
			link.l1.go = "SF_InvitingOfficerToHuberExit";
		break;
		
		case "SilverSurferCaptain":
			dialog.text = "Ahem... Ahem... Uh...";
			link.l1 = "Still alive? I can't wait for you to cough up your last word.";
			link.l1.go = "SilverSurferCaptainThreat";
			pchar.questTemp.silverfleet.silversurfercaptainspeak = true;
		break;
		
		case "SilverSurferCaptainThreat":
			dialog.text = "You're not getting out of here... Ahem. I've thought of everything. My men will capture you now, and we'll get you out of this battle on my ship. Don't be stupid, or you'll just die here.";
			link.l1 = "Well. first, you die!";
			link.l1.go = "SilverSurferCaptainDead";
		break;
		
		case "SilverSurferCaptainDead":
			QuestAboardCabinDialogFree();
			LAi_KillCharacter(NPChar);
			DoQuestFunctionDelay("SF_CabinOfficer", 1.0);
		break;

		case "SilverSurferCaptainTrap":
			dialog.text = "Captain! It's a trap! They've been waiting for us to get far enough away to crawl out of their holes. An impressive force, I suspect their best fighters, have blocked us here. There's a fight on!";
			link.l1 = "Hold on! We're gonna make it! We'll kill them all!";
			link.l1.go = "SilverSurferCaptainTrapBattle";	
		break;

		case "SilverSurferCaptainTrapBattle":
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_LockFightMode(pchar, false);
			DialogExit();
		break;
		
		// <-- СФ
	}
}
