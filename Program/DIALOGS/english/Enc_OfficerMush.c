void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;

    Pchar.quest.FreeRandomOfficerIdx = NPChar.index;

	switch(Dialog.CurrentNode)
	{
		case "CitizenNotBlade":
			dialog.text = "Captain, what nonsense! Put away your weapons before you cause trouble!";
			link.l1 = LinkRandPhrase("Good.", "Okay.", "Don't worry, I'm already removing...");
			link.l1.go = "exit";
		break;

		//--> хорошист-саксонец
		case "Saxon":
			if (sti(PChar.reputation) > 60)//при низкой репутации - в сад
			{
				dialog.text = "Greetings, Captain! I've been waiting for you for the whole day...";
				link.l1 = "Are you waiting? Me!? I don't recall that we knew each other.";
				link.l1.go = "Saxon_1";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("Good goose! Look, sir, at the sides, and not at the cleavage of the ladies you meet", "Madam! I would ask you not to try to flirt with me.") +". Although I am retired, but the order of the dish ...";
				link.l1 = "How gentle we are! Go, veteran, on your course.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Saxon";
			}
		break;

		case "Saxon_1":
			dialog.text = "It is never too late to catch up. Let me introduce myself - Magnus von Kokkai-Stade. I have served different kings and dukes for as long as I can remember. In Europe, he became a lieutenant in a Musketeer regiment paid by the Spanish crown... until recently.\nBut they sent a nephew to the governor, damn it! This young bastard wanted an officer's rank. So now the garrison is less than one Saxon, but more than one Spaniard, which does not mean equal exchange, if you value the experience, of course!";
			link.l1 = "Very well, sir. But you still haven't explained why you were waiting for me?";
			link.l1.go = "Saxon_2";
		break;

		case "Saxon_2":
			dialog.text = "Every morning I come to the pier and ask the arriving captains if they need the head of the boarding company. Former colleagues recommended you as a very reputable, respected, experienced and brave commander."+ GetSexPhrase(".", "despite the fact that you are a woman.") +"I don't want to serve under a sucker in the prime of my life or end up in a bandit gang.";
			link.l1 = "You say you were an officer...?";
			link.l1.go = "Saxon_3";
		break;

		case "Saxon_3":
			dialog.text = "What does 'was'? Captain, I wasn't, I'm not. Here I am. I'm an officer, and I will be an officer. If you want order and a true shoulder in battle, you can have me if you agree on a price. I won't take it. Just as much as I have to sort out and distribute debts.";
			link.l1 = "How much will your faithful eye, strong arm, reliable shoulder and other advantages of the son of the Saxon lands cost me in the future?";
			link.l1.go = "Saxon_4";
		break;

		case "Saxon_4":
			dialog.text = "Forty thousand one-time allowance and a small salary in the future. I'm not begging for extra money, I'll take it like the others, I'll eat from the officer's boiler. I'll ask you for bullets and gunpowder. The more of them you provide, the fewer reasons there will be for anxiety and frustration, haha!";
			if(sti(Pchar.money) >= 40000)
			{
				link.l1 = "It's okay! Here's your money, finish your business and get on the ship, I'll warn you to have a boat prepared for you.";
				link.l1.go = "Saxon_check";
			}
			link.l2 = "These are the requests! It was nice to meet you, Herr Officer, but I'm used to trust a good blade more than someone else's musket behind your back.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgain";
		break;

        case "OnceAgain":
            NextDiag.TempNode = "OnceAgain";
			dialog.text = "What a meeting, Captain! Have you decided to strengthen your team with a brave Musketeer after all?";
			link.l1 = "You're right, Herr Officer, you're definitely right. Remind me, how much did you rate your service on my ship?";
			link.l1.go = "Saxon_4";
            link.l2 = "No, I haven't decided. Have a nice stay, Herr Officer.";
			link.l2.go = "exit";
		break;

		case "Saxon_check":
            if (FindFreeRandomOfficer() == -1)//если перебор с офицерами
            {
                dialog.text = "Hmm. You have a full complement of officers, Captain. Come back when you can give me a job.";
    			link.l1 = "Good.";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
    			break;
            }
			if (sti(PChar.reputation) <= 60)//повторная проверка репутации, для второго и далее заходов
			{
				dialog.text = "Hmm... You know, Cap, people don't speak well of you. I told you, I don't want to serve in a bandit gang!";
				link.l1 = "How gentle we are! Go, veteran, on your course.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
			break;
			}
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 21 + MOD_SKILL_ENEMY_RATE*3)//при низком авторитете - в сад
			{
                dialog.text = "Hmm. Nothing personal, Captain, but even though you are considered a hero, your deeds do not speak for you too much yet. I want to be sure that I am going to work for a respectable person. So I think I'll wait to hire you.";
    			link.l1 = "Well, I don't run from difficulties, and I eat a scoundrel for breakfast every day. You'll hear from me soon, don't doubt it. In the meantime, I wish you good health...";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
    			break;
            }
			dialog.text = "That's great. I swear to serve faithfully. You won't regret the money you spent on me.";
			link.l1 = "I hope I wont.";
			link.l1.go = "Exit_hire_Saxon";
		break;
		//<-- хорошист-саксонец

		//--> плохиш-пират
		case "Lostpirate":
			if (sti(PChar.reputation) < 40)//при повышенной репутации - в сад
			{
				dialog.text = "Greetings, Cap! What happiness it is to see human faces and hear living voices again, and not the disgusting hubbub of feathered brethren.";
				link.l1 = "What are you doing alone in this secluded paradise? Are you studying the habits of seabirds?";
				link.l1.go = "Lostpirate_1";
			}
			else
			{
				dialog.text = "And you're lucky, Cap! I almost shot you thinking you were my bully, heh-heh";
				link.l1 = "It is unknown who was more fortunate. You could have missed. And I just wanted to help.";
				link.l1.go = "exit_Rep";
				link.l1 = "You could have missed. And I was wondering, I saw you off the ship. Are you a hermit here?";
				link.l1.go = "Lostpirate_1";
			}
		break;

		case "exit_Rep":
			NextDiag.TempNode = "Lostpirate";
			dialog.text = "I never miss. One shot - one corpse. And even two, as luck. So don't tempt fate with your noble intentions again, the musket is loaded.";
			link.l1 = "I liked you too, stranger. And I think I'll follow your advice.";
			link.l1.go = "exit";
		break;

		case "Lostpirate_1":
			dialog.text = "You didn't guess. I'm more of a poet than a naturalist. I write for the soul, and I get my food by hunting. The gentle whisper of the divine muses is clearly audible alone with nature. As a poet, I, Nicolas Rimalier, am little known. While. But he is quite popular as a skilled marksman. So to speak, the creator of fatal wounds and the maestro of volleys. If a person is talented, then he is talented in everything.";
			link.l1 = "Hmm, and how did such a multifaceted talent end up in the bay of a desert island without a ship, supplies and prospects?";
			link.l1.go = "Lostpirate_2";
		break;

		case "Lostpirate_2":
			dialog.text = "(sings) It's hard to survive in this world without a reliable musket, maybe it's easier somewhere - but not here, and not for a poet. My story may seem ridiculous, but it's all the fault of an ill-fated bet that I made on my head with a senior assistant. He was stupid enough to accuse me of the fact that the foraging team returned empty-handed, because its main shooter, in which capacity I was assigned to it, cannot even hit a shark carcass. I have to admit, I can be overly adventurous at times. This time, to prove my skill, I had to hit the thrown piaster. Wanting to laugh at me, the XO ordered me to shoot without letting the coin out of his hand. His joke didn't go well. The bullet tore off his finger and pierced his hand along with the coin. It turns out that I won the argument. Everyone recognized this. Apparently, that's why they were reluctant to catch up with me, despite the terrible swearing of the first officer. And as I was, with a song in my soul and a musket in my hands, I hid in the thicket. The ship is gone, with supplies and perspective. That's the whole story. So I've been trading for a long time by beating seagulls for breakfast, lunch and dinner.";
			link.l1 = "It's a funny story. What are you going to do now?";
			link.l1.go = "Lostpirate_check";
		break;

        case "OnceAgainLP":
            NextDiag.TempNode = "OnceAgainLP";
			dialog.text = "Well, Cap, you seduced with my singing talent? Or small arms? I'm telling you, you're lucky - I'm still here!";
			link.l1 = "You're also a cheat, I see. Didn't you want to get a job on a ship?";
			link.l1.go = "Lostpirate_check";
            link.l2 = "It may very well be for this reason that the crew on my ship has not yet shot each other. Maybe someone will believe your stories, but today I'm too sober for this.";
			link.l2.go = "exit";
		break;

		case "Lostpirate_check":
            if (FindFreeRandomOfficer() == -1)//если перебор с офицерами
            {
                dialog.text = "Hmm. I would like to go to your service... But I see you have a full complement of officers, alas. And I have no intention of crowding into the forecastle with the sailors. So I'll have to stay in this cozy cove.";
    			link.l1 = "Yes, I don't have any vacancies. Maybe I'll visit you later.";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgainLP";
    			break;
            }
			if (sti(PChar.reputation) >= 40)//повторная проверка репутации, для второго и далее заходов
			{
				if (!CheckAttribute(pchar, "RimalieDone"))
				{
					dialog.text = "Hmm... You know, Cap, I don't like you. You'll also turn yourself in to the authorities, which is good... You can expect anything from the saints. I'd rather stay here in this cozy cove.";
					link.l1 = "Good luck, hawkeye! Look, don't go wild here...";
					link.l1.go = "exit";
					link.l2 = "So I'll give it up right away? You still have to look for a good Musketeer, but you create a similar impression.";
					link.l2.go = "LPGoodSide";
					NextDiag.TempNode = "OnceAgainLP";
				}
				else
				{
					dialog.text = "Since you have managed to reconcile me with the smugglers, then I will not be arrogant. 10,000 piastres and I'm yours.";
					if (sti(pchar.money)>= 10000)
					{
						link.l1 = "Here's your money. And I hope you'll temper your scandalous nature.";
						link.l1.go = "Exit_hire_Lostpirate";
					}
					link.l2 = "As soon as there is money, so immediately. I delayed them a little.";
					link.l2.go = "exit";
				}
				break;
			}
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 31)//при низком везении - в сад
			{
                dialog.text = "Under the hand of a lucky, easy-going cap, I would agree to continue to surf the seas. And with you, it seems, it's more likely not to catch courage, but lashes.";
    			link.l1 = "Well, if the muses do not lure you to the divine distances, or the devil does not take you away, then we will meet again. I think very soon.";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgainLP";
    			break;
            }
			dialog.text = "Take me in as a shooter, you won't regret it! I will even make a feasible contribution to today's menu - I will give all the loot, because nothing is a pity for real friends!";
			link.l1 = "Why not? I hope you won't argue with anyone on my team.";
			link.l1.go = "Exit_hire_Lostpirate";
			link.l2 = "I heard your story in another version. You raised your hand against your captain, knocking out his blade with a shot when he wanted to arrest you for attempted mutiny. I like desperate guys like you, but I don't want to test your marksmanship on my own skin.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgainLP";
		break;
		case "LPGoodSide":
			dialog.text = "To be honest, I'm frankly sick of hanging around here. Solve one problem and pay extra from above - I'll go with you.";
			link.l1 = "And what do you want?";
			link.l1.go = "LPGoodSide_2";
		break;
		case "LPGoodSide_2":
			dialog.text = "I've been able to get to civilization for a long time, but I fell out with the locals. I broke a deal with the smugglers once, I just wanted a normal meal and to get hold of bullets with gunpowder. And they apparently gave a paw to the local governor, who gave the order to the guards. If they see it, they will put it on the spot.";
			link.l1 = "To make peace with the smugglers, then?";
			link.l1.go = "LPGoodSide_3";
		break;
		case "LPGoodSide_3":
			dialog.text = "They are touchy people, they will get them out of the ground. So far, I've been able to hide, but I'm not sure it's going to be like this forever. I guess even on another island they'll get me.";
			link.l1 = "I'll try to do something. Wait for my return.";
			link.l1.go = "LPGoodSide_4";
		break;
		case "LPGoodSide_4":
			dialog.text = "Well, I'll try to trust you and not reflexively put a bullet in your forehead on your return.";
			link.l1 = "Heh, if you get in...";
			link.l1.go = "exit";
			pchar.RimalieGood = 1;
			NextDiag.TempNode = "OnceAgainLPGood";
			SetQuestHeader("Rimalie");
			AddQuestRecord("Rimalie", "1");
			AddQuestUserData("Rimalie", "sSex", GetSexPhrase("", "a"));
		break;
		case "OnceAgainLPGood":
			dialog.text = "How's it going, Captain?";
			link.l1 = "Nothing yet.";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "RimalieDone"))
			{
				link.l1 = "The problem has been solved. You can join my team. By the way, how much did you want there?";
				link.l1.go = "Lostpirate_check";
				NextDiag.TempNode = "OnceAgainLP";
				AddQuestRecord("Rimalie", "3");
				CloseQuestHeader("Rimalie");
				pchar.questdata.Rimalie = 1;
			}
			else NextDiag.TempNode = "OnceAgainLPGood";
			pchar.questdata.Rimalie = 1;
		break;
		//<-- плохиш-пират

		//--> приказы
        case "hired":
			NextDiag.TempNode = "Hired";
			dialog.text = "What are the orders?";
			link.l2 = "You're fired. I'll do without your services!";
			link.l2.go = "AsYouWish";
            Link.l5 = "Listen to my order!";
            Link.l5.go = "stay_follow";
			Link.l3 = "I want you to keep a certain distance from the target.";
			Link.l3.go = "TargetDistance";

			// по тёк локации определим можно ли тут приказать  -->
			if (IsEntity(loadedLocation))
            {
                if (CheckAttribute(loadedLocation, "fastreload"))
                {
                    iTemp = FindColony(loadedLocation.fastreload);
                    if (iTemp != -1)
                    {
                        sld = GetColonyByIndex(iTemp);
                        if (sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
                        {
							if(Locations[FindLocation(PChar.location)].islandId != "Caiman" && !CheckAttribute(NPChar, "HPminusDaysNeedtoRestore"))
							{
								NPChar.ColonyIdx = iTemp;
								Link.l7 = "I am appointing you as the governor of this city!";
								Link.l7.go = "Gover_Hire";
							}
                        }
                    }
                }
            }
			if(PChar.ColonyBuilding.Stage != "0" && PChar.ColonyBuilding.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman" && !CheckAttribute(NPChar, "HPminusDaysNeedtoRestore"))
					{
						Link.l8 = "I want to appoint you as the governor of the colony."" + PChar.ColonyBuilding.ColonyName + "", which we built on the island of Cayman.";
						Link.l8.go = "ColonyBuilding_Hovernor_1";
					}
				}
			}

            link.l9 = "Nothing. At ease.";
			link.l9.go = "exit";
        break;
		//<-- приказы


		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Which one exactly, Captain? Specify in meters, but not more than 20.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;

		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Captain, what a bad tone!";
				link.l1 = "Sorry, I made a mistake...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "I will stand still, not moving anywhere. Is that okay with you, Captain?";
				link.l1 = "Yes, that's exactly what is required of you.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "I think I said that I can't stay more than 20 meters from the target.";
				link.l1 = "Okay, keep a distance of 20 meters.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "I understand the task, I take it into account.";
			link.l1 = "Good.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы

		//--> найм
        case "Exit_hire_Saxon":
			npchar.HalfImmortal = true;
			AddMoneyToCharacter(Pchar, -40000);
			npchar.MusketerDistance = 10;
			TakeNItems(npchar, "Mineral7", 1);
			TakeNItems(npchar, "indian17", 1);
			TakeNItems(npchar, "potionwine", 1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			npchar.Dialog.FileName = "Enc_Officer_dialog.c";
			NPChar.Dialog.TempNode = "hired";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_hire_Lostpirate":
			if(CheckAttribute(pchar, "RimalieDone"))
			{
				AddMoneyToCharacter(pchar,-10000);
				npchar.reputation = 65;
				npchar.alignment = "good";
				DeleteAttribute(pchar,"RimalieDone");
			}
			pchar.questdata.Rimalie = 1;
			npchar.HalfImmortal = true;
			TakeNItems(pchar, "Mineral4", 5);
			Log_Info("You got cormorants");
			PlaySound("interface\important_item.wav");
			npchar.MusketerDistance = 10;
			TakeNItems(npchar, "Mineral2", 1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			npchar.Dialog.FileName = "Enc_Officer_dialog.c";
			NPChar.Dialog.TempNode = "hired";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			locations[FindLocation("Shore59")].DisableEncounters = false; //энкаутеры в бухте откроем
			pchar.questdata.Rimalie = 1;
		break;
		//<-- найм

		//--> увольнение
		 case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Captain, although I do not understand the reason for such a statement, let's return to this issue on shore. Or did you decide to just throw me overboard?";
					Link.l1 = "Hmm... no, I didn't mean it. Stay until we get to the port.";
					Link.l1.go = "Exit";
					break;
				}
			}
			// проверка на море <--
			dialog.text = "Whatever you say, Captain, it's up to you. You will not find a second such Musketeer.";
			link.l1 = "I think I've changed my mind. I still need you.";
			link.l1.go = "exit";
			link.l2 = "And don't. You can get the hell out of here.";
			link.l2.go = "Exit_Fire";
		break;

		case "exit_fire":
   			NextDiag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Fired":
		      NextDiag.TempNode = "Fired";
		      dialog.text = "I warned you that I would not return to your ship. I'm going to hire another captain.";
		      Link.l1 = "I don't need you.";
		      Link.l1.go = "Exit";
	    break;
		//<-- увольнение

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		//--> стоять-следовать
		case "stay_follow":
            dialog.Text = "What are your orders?";
            Link.l1 = "Stay here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
			if (!CheckAttribute(npchar, "AboardRestriction"))
			{
				Link.l4 = "I ask you not to participate in the boarding. Take care of yourself.";
				Link.l4.go = "AboardRestriction";
			}
			else
			{
				Link.l4 = "I've changed my mind, you can participate in the boarding.";
				Link.l4.go = "AboardAllowed";
			}
        break;

		case "AboardRestriction":
			npchar.AboardRestriction = true;
			dialog.text = "That's right, Captain. I will not participate in boarding until you allow it again.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
		break;

		case "AboardAllowed":
			DeleteAttribute(npchar, "AboardRestriction");
			dialog.text = "That's right, Captain. I will participate in boarding from now on.";
            Link.l1 = "That's good.";
            Link.l1.go = "exit";
		break;

        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "There is a change of location!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;

        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "There is a change of location!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
        break;
		//<-- стоять-следовать

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "I would be honored!";
            Link.l1 = "Keep an eye on the order and prosperity of the city, I will sometimes come to collect the toll.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "I've changed my mind.";
            Link.l2.go = "Exit";
            NextDiag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "What are your orders? Your last visit was " + FindRussianDaysString(iTemp) + " ago.";
			}
			else
			{
			    dialog.Text = "What are your orders?";
			}

            Link.l1 = "What amount of taxes you collected?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "You needed on the ship, I'm taking you off city duty.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Have a nice day.";
            Link.l9.go = "Exit";
            NextDiag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "My skills allow me to collect " + FindRussianMoneyString(iFortValue*iTax) + " per day. For " + FindRussianDaysString(iTemp) + " I collected " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "I want to collect the entire amount of taxes.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Thank you for your service!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Wonderful! Being a land rat is not my destiny.";
            Link.l8 = "That's good.";
            Link.l8.go = "exit_hire";
            NextDiag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "I'm listening carefully.";
			Link.l1 = "It's about boarding.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "It's about your ship.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "I want you to come out from my squadron for a month and look for luck on your own.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Nothing yet.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "What do you want?";
			Link.l1 = "I want you not to board ships. Take care of yourself and your team.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "I need you to board enemy ships.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "What do you want?";
			Link.l1 = "I want you not to change your ship after boarding. He's too valuable.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "When you board your enemies, see if there's a decent boat, then take it for yourself.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "That's right.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "It will be done.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "That's right.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "It will be done.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	}
}
