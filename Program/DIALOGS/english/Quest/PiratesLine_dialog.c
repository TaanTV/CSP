
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "I have nothing to talk about with you, I'm sorry...";
			link.l1 = "Understood.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "exit_hl":
			NextDiag.TempNode = "PiratesManNew1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// -------------------------------------- квест №1 -------------------------------------------------
		//первая встреча с посыльным Моргана в Пуэрто Принсипе
		case "PiratesMan1":
			if (pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN)
			{
				if(CheckAttribute(pchar, "QuestTemp.AndreAbelQuest") || CheckAttribute(pchar, "questTemp.WhisperTutorial"))
				{
					dialog.text = RandPhraseSimple("What do you want? Pass by.", "Stop blocking the road, get off.");
					link.l1 = RandPhraseSimple("You know what? Don't bark!", "Slow down your ardor. Otherwise I'll cool it down quickly!");
					link.l1.go = "exit";
					NextDiag.TempNode = "PiratesMan1";
				}
				else
				{
					dialog.text = GetSexPhrase("Boy", "Girl") +"! What are you staring at me like that for?";
					link.l1 = "Just passing by.";
					link.l1.go = "exit_hl";
					link.l2 = "Aren't you Captain Goodley by any chance?";
					link.l2.go = "PiratesMan1_1";
					if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue8_Gudli"))	//Sinistra Пролог Анжелика тич
					{
						dialog.text = "The girl is healthy... Are you the owner of the ship that anchored in our cozy bay?";
						link.l1 = "I am his captain.";
						link.l1.go = "ATpr_F1";
						DeleteAttribute(link, "l2");
					}
				}
			}
			else
			{
				dialog.text = "Great, "+ GetSexPhrase("guy", "girl") +". Oh, the devil!! It's a pity that I can't trust you, it's a pity...";
				link.l1 = "What's the matter? Have I stained myself in the eyes of the Brethren?";
				link.l1.go = "PiratesManNot_1";
				npchar.talker = 2; //начать диалог
				NextDiag.TempNode = "PiratesManNew1";
			}
		break;
		//Sinistra Пролог Анжелика тич ==>
		case "ATpr_F1":
			dialog.text = "Are you lying? No... Let me guess, you have very serious patrons behind you if the pack on your ship is ready to follow your orders.";
			link.l1 = "Angelica Teach, at your service.";
			link.l1.go = "ATpr_F2";
		break;
		case "ATpr_F2":
			dialog.text = "It can't be! Is that the little Angelica? You probably don't remember me, I'm Goodley. I served with Edward Teach, not for long, though, I was young and ambitious, and I got my own tub pretty quickly.";
			link.l1 = "Captain Goodley? That's how I'm looking for you. Jackman sent me because you need some help.";
			link.l1.go = "ATpr_F3";
		break;
		case "ATpr_F3":
			dialog.text = "I need to do a favor for Henry Morgan. Come to the tavern, we'll discuss everything there.";
			link.l1 = "To Morgan, you say? Hmm, all right.";
			link.l1.go = "PiratesMan1_2";
			link.l2 = "I'm busy right now, let's do it later.";
			link.l2.go = "ATpr_F4_exit";
		break;
		case "ATpr_F4_exit":
			NextDiag.TempNode = "ATpr_F5";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "ATpr_F5":
			dialog.text = "Hello, Angelica! Well, have you changed your mind? I need to do a favor for Henry Morgan.";
			link.l1 = "Yes, let's discuss this in the tavern.";
			link.l1.go = "PiratesMan1_2";
			link.l2 = "I'm busy right now, let's do it later.";
			link.l2.go = "ATpr_F4_exit";
		break;
		//<== Sinistra Пролог Анжелика тич
		case "PiratesMan1_1":
			dialog.text = "Yes, it's me. What did you want?";
			link.l1 = "Jackman sent me to you. He said you needed help.";
			link.l1.go = "PiratesMan1_2";
		break;
		case "PiratesMan1_2":
			dialog.text = "I need to do a favor for Henry Morgan. Come to the tavern, we'll discuss everything there.";
			link.l1 = "Hmm, all right.";
			link.l1.go = "PiratesMan1_3";
		break;
		case "PiratesMan1_3":
			DialogExit();
			NextDiag.CurrentNode = "Tavern_1";
			//LockQuestLine(characterFromId("eng_guber")); // лочим английскую линейку
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			FreeSitLocator("PuertoPrincipe_tavern", "sit3");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5", "PuertoPrincipe_tavern", "sit", "sit3", "PiratesLine_toTavern", -1);
		break;

		case "PiratesManNot_1":
			dialog.text = "No, that's not the point. You're working for the Governor General of " + NationNameGenitive(sti(pchar.questTemp.NationQuest)) + ". This is a problem for me right now.";
			link.l1 = "Really sorry...";
			link.l1.go = "PiratesManNot_2";
		break;
		case "PiratesManNot_2":
			dialog.text = "Listen, you come to me later when your service is coming to an end. I think I can be honest with you then.";
			link.l1 = "Okay. I'll keep that in mind.";
			link.l1.go = "exit";
            SetQuestHeader("Pir_Line_0_Waiting");
            AddQuestRecord("Pir_Line_0_Waiting", "1");
			AddQuestUserData("Pir_Line_0_Waiting", "sNation", NationNameAblative(sti(pchar.questTemp.NationQuest)));
		break;

		case "PiratesManNew1":
			if (pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN)
			{
				dialog.text = GetSexPhrase("Boy", "Girl") +"! What are you staring at me like that for?";
				link.l1 = "Just passing by.";
				link.l1.go = "exit_hl";
				link.l2 = "Aren't you Captain Goodley by any chance?";
				link.l2.go = "PiratesMan1_1";
			}
			else
			{
				dialog.text = "Ah, we met again. But it's not time yet, "+ GetSexPhrase("buddy", "girlfriend") +". Later...";
				link.l1 = "Maybe I will, but what do I need?";
				link.l1.go = "exit";
				npchar.talker = 2; //начать диалог
				NextDiag.TempNode = "PiratesManNew1";
			}
		break;
		//разговор в таверне Пуэрто Принсипе
		case "Tavern_1":
			LAi_SetSitType(pchar);
			dialog.text = "Well, what do you say? Ready to help Morgan?";
			link.l1 = "To Morgan?! If this is the same Morgan - Admiral of the Brethren, then I am ready... and what should I do?";
			link.l1.go = "Tavern_2";
			npchar.lifeDay = 0;
		break;
		case "Tavern_2":
			dialog.text = "Yes, it's simple. You take one little man on board, Morgan has already been waiting for him, and – to Port Royal. And Morgan will meet you there... and he will pay in the same place. As you can see, it's nothing complicated. And don't forget, you're doing Morgan a big favor. Well, do you agree?";
			link.l1 = "Hmm, the service is small... What kind of person is that?";
			link.l1.go = "Tavern_3";
			link.l2 = "Morgan is, of course, a famous pirate, but I have other things to do and I don't intend  drop everything. And anyway, I'm not captain of a courier longboat!";
			link.l2.go = "Tavern_over";
		break;
		case "Tavern_3":
			dialog.text = "Nothing special. My name is John Bolton, he will be waiting for you in the bay. Just don't talk too much!";
			link.l1 = "I'm not the chatty guy. Should I be afraid of something?";
			link.l1.go = "Tavern_4";
		break;
		case "Tavern_4":
			dialog.text = "Be afraid? Well no. It's just that Morgan doesn't like it... Well, do you agree?";
			link.l1 = "I agree.";
			link.l1.go = "Tavern_5";
		break;
		case "Tavern_5":
			dialog.text = "That's great! Well, have a nice day, "+ GetSexPhrase("buddy", "girlfriend") +". Be healthy!";
			if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue8_Gudli"))	//Sinistra Пролог Анжелика тич
			{
				dialog.text = "That's great! Well, have a nice day, Blackbeard's daughter. Be healthy!";
				DeleteAttribute(pchar, "questTemp.AnjelikaTichPrologue8_Gudli");
			}
			link.l1 = "The same to you...";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			NextDiag.TempNode = "Tavern_again";
            SetQuestHeader("Pir_Line_1_JohnBolton");
            AddQuestRecord("Pir_Line_1_JohnBolton", "1");
			CloseQuestHeader("Pir_Line_0_Waiting");
			pchar.questTemp.piratesLine = "toJohnBolton";
			sld = GetCharacter(NPC_GenerateCharacter("QuestPirate2", "officer_4", "man", "man", 20, PIRATE, -1, true));
			sld.name = "John";
			sld.lastname = "Bolton";
			sld.city = "PuertoPrincipe";
			sld.location	= "PuertoPrincipe_port";
			sld.location.group = "goto";
			sld.location.locator = "goto14";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "JohnBolton";
			sld.greeting = "Gr_MiddPirate";
			sld.talker = 8; //начать диалог
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddDialogExitQuestFunction("PiratesLine_q1_tavernEnd");
		break;

		case "Tavern_again":
			dialog.text = "John is waiting for you in the bay of Puerto Principe. Don't delay it!";
			link.l1 = "Okay...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tavern_again";
		break;
		case "Tavern_over":
			dialog.text = "Hmm... Well, as you know, "+ GetSexPhrase("buddy", "girlfriend") +". Our business is to offer, your business is to refuse. Bye...";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			pchar.questTemp.piratesLine = "over";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("PiratesLine_q1_tavernEnd");
		break;
		//базар с Джоном Болтоном в порту Пуэрто Принсипе
		case "JohnBolton":
			dialog.text = "Good afternoon. Tell me, are you captain " + GetFullName(pchar) + "?";
			link.l1 = "Yes. And you must be John Bolton?";
			link.l1.go = "JohnBolton_1";
		break;
		case "JohnBolton_1":
			dialog.text = "Yes, yes. And I need to get to Port Royal, and preferably quickly.";
			link.l1 = "I know, get in the boat, the ship is ready.";
			link.l1.go = "JohnBolton_2";
		break;
		case "JohnBolton_2":
			AddQuestRecord("Pir_Line_1_JohnBolton", "2");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1 = "locator";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.location = "PortRoyal_town";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.locator_group = "quest";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.locator = "detector_PQ1";
			pchar.quest.PiratesLine_q1_arrest.function = "PiratesLine_q1_arrest";
			NextDiag.TempNode = "JohnBolton_inWay";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "", 5.0);
		break;
		case "JohnBolton_inWay":
			dialog.text = "We haven't reached Port Royal yet, but I'm in a hurry, "+ GetSexPhrase("buddy", "girlfriend") +"...";
			link.l1 = "We're going there, don't worry.";
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnBolton_inWay";
		break;
		//базар с арестовывающими солдерами
		case "ArrestInPR":
			dialog.text = "A report has been received that you have a criminal John Bolton on board... Bah! Yes, there he is! You're under arrest!";
			link.l1 = "Hey, buddy, aren't you mistaken? I brought this man on behalf of Henry Morgan!";
			link.l1.go = "ArrestInPR_1";
		break;
		case "ArrestInPR_1":
			dialog.text = "The commandant will figure out where the error is and where it is not. Follow me!";
			link.l1 = "Damn it...";
			link.l1.go = "ArrestInPR_2";
		break;
		case "ArrestInPR_2":
			AddQuestRecord("Pir_Line_1_JohnBolton", "3");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Portroyal_town", "houseS1", false); //закроем дом Моргана
			DialogExit();
			AddDialogExitQuestFunction("PiratesLine_q1_toPrison");
		break;
		// -------------------------------------- квест №2 -------------------------------------------------
		case "EdwardLoy":
			dialog.text = "You need me, "+ GetSexPhrase("buddy", "girlfriend") +"? To what do I owe it?";
			link.l1 = "Greetings from Henry Morgan.";
			link.l1.go = "EdwardLoy_1";
		break;
		case "EdwardLoy_1":
			dialog.text = "...From Henry Morgan? And what did Henry Morgan want with me?";
			link.l1 = "Henry has missed you very much, he asks to visit you on occasion.";
			link.l1.go = "EdwardLoy_2";
		break;
		case "EdwardLoy_2":
			dialog.text = "...Why is that?";
			link.l1 = "I don't know. Maybe he decided to include you in his will. And so that you wouldn't doubt his sincerity, he told me to give you something. He said that you've been waiting for her for a long time, but somehow I didn't have time to get out - to please you.";
			link.l1.go = "EdwardLoy_3";
			RemoveItems(PChar, "BlackLabel", 1);
		break;
		case "EdwardLoy_3":
			dialog.text = "The devil! A black Mark. I knew it... And if I don't take it?";
			link.l1 = "And if you don't take it, I'll shove it down your throat.";
			link.l1.go = "EdwardLoy_4";
		break;
		case "EdwardLoy_4":
			dialog.text = "Enough! You did your dastardly business, now get out of here!";
			link.l1 = "Have a nice day, Law... And if you want to live, go to Morgan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "EdwardLoy_again";
			QuestSetCurrentNode("Henry Morgan", "PL_Q2_away_1");
			AddQuestRecord("Pir_Line_2_BlackLabel", "3");
			AddQuestUserData("Pir_Line_2_BlackLabel", "sSex", GetSexPhrase("", "a"));
		break;
		case "EdwardLoy_again":
			dialog.text = "Are you still here?";
			link.l1 = "I'm already leaving...";
			link.l1.go = "exit";
			NextDiag.TempNode = "EdwardLoy_again";
		break;
		// -------------------------------------- квест №3 -------------------------------------------------
		case "CapGoodly":
			dialog.text = "Ho! Great, "+ GetSexPhrase("guy", "girl") +"! Here we go again. Have a seat, let's have a drink.";
			link.l1 = "Hello, Goodley! The tavern keeper said you were talking to Law.";
			link.l1.go = "CapGoodly_1";
		break;
		case "CapGoodly_1":
			dialog.text = "That's right, I talked. He told me that he was working on a secret assignment from Morgan.";
			link.l1 = "Uh-huh, it's so secret that Morgan is looking for it all over the Caribbean... Did he say where he was going?";
			link.l1.go = "CapGoodly_2";
		break;
		case "CapGoodly_2":
			dialog.text = "Morgan, you say, is looking for?  No, he didn't say anything like that... We just sat and gossiped about life.";
			link.l1 = "It seems to me, friend Goodley, that you, like in the story with Bolton, are again hiding something. Are you already figuring out how much Morgan will pay for Law's head? So know this – I'll be right behind you. And when you take me out to the Law, I'll finish you first, so that you don't get in the way.";
			link.l1.go = "CapGoodly_3";
		break;
		case "CapGoodly_3":
			dialog.text = "Come on! What kind of misunderstandings can there be between friends?I just returned from Cumana, I was guarding the galleons there. Well, he asked a couple of times... But I'm not sure.";
			link.l1 = "Okay, don't be offended, I was joking. Well, it's time for me. If I find Law, I'll share it with you, goodbye.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "13");
			pchar.questTemp.piratesLine = "KillLoy_toCumana";
			npchar.lifeDay = 0;
			pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1 = "location";
			pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1.location = "Cumana";
			pchar.quest.PiratesLine_q3_loginSeaWolf.function = "PiratesLine_q3_loginSeaWolf";
		break;
		//Эдвард Лоу в каюте Морского Волка
		case "SeaWolf":
			dialog.text = "The devil! You still got me!";
			link.l1 = "How could it be otherwise?!";
			link.l1.go = "SeaWolf_1";
		break;
		case "SeaWolf_1":
			dialog.text = "Who do you think you are?! Do you think you're almighty?! You are simple messenger of Morgan, nothing more!";
			link.l1 = "Oh Law, man is made for happiness, but he has to work all the time. And today you are my job.";
			link.l1.go = "SeaWolf_2";
		break;
		case "SeaWolf_2":
			dialog.text = "Of course! How much did Morgan promise you for me? I'll pay you twice... Three times!";
			link.l1 = "If it can amuse your ego before you die, then Morgan put fifty thousand on you.";
			link.l1.go = "SeaWolf_3";
		break;
		case "SeaWolf_3":
			dialog.text = "Listen, " + GetFullName(pchar) + ", I'll give you two hundred thousand, just let me go.";
			link.l1 = "Law, why does Morgan have a grudge against you. You can't understand with your rotten nature that a fat piece today could be the cause of starvation tomorrow.";
			link.l1.go = "SeaWolf_4";
		break;
		case "SeaWolf_4":
			dialog.text = "What is it?! Does Morgan have a grudge against me?! Do you know how many pirates have a grudge against him?! Who chose him?! You?!" +
				"Morgan has a grudge against me! Ha ha ha! I fooled him like a puppy! That's what he can't forgive me for! This impostor is infuriated that I once told him that no one chose him, that I did not lick his heels, as all of you do!He'll throw you out like a kitten, or drown you in a puddle of your own urine as soon as you're no longer needed!";
			link.l1 = "Shut up, Law! I will sort out my business with Morgan myself, when the time comes. And you won't die for fifty thousand. You will die for your meanness. Jackman asked me to do it for free... Do I have any reason to let you live?";
			link.l1.go = "SeaWolf_5";
		break;
		case "SeaWolf_5":
			dialog.text = "Ha! I can imagine Jackman's face when he found out that his brig was tut-tut...";
			link.l1 = "Introduced? Well, God be with you then...";
			link.l1.go = "SeaWolf_6";
		break;
		case "SeaWolf_6":
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		// -------------------------------------- квест №5 -------------------------------------------------
		case "PQ5CapGoodly":
			dialog.text = "Great, "+ GetSexPhrase("buddy", "girlfriend") +"! It's very good that I caught you! If you're not in a hurry, let's talk. I have a case for you again, help me out.";
			link.l1 = "Great. I recognize old Goodley - as always, problems. Well, tell me, what's the deal?";
			link.l1.go = "PQ5CapGoodly_1";
		break;
		case "PQ5CapGoodly_1":
			dialog.text = "I'm not going to beat around the bush, that's what my case is.As you know, I work for Morgan. But besides this job, I have another one, the main one. I'm a bounty hunter. So far, I've been able to combine Morgan's business and my main job, but now, alas, it hasn't worked out. I was approached with an order by a man whom I cannot refuse...";
			link.l1 = "Can't you postpone, reschedule? What's the rush? You see, a man would have lived a little longer, ha ha ha...";
			link.l1.go = "PQ5CapGoodly_3";
		break;
		case "PQ5CapGoodly_3":
			dialog.text = "If everything were solved so simply, I wouldn't ask you. Make up your mind. You will take all the reward from the customer for yourself.";
			link.l1 = "Hmm, not a bad incentive. Perhaps we should agree. Come on, what's the order?";
			link.l1.go = "PQ5CapGoodly_4";
		break;
		case "PQ5CapGoodly_4":
			dialog.text = "We need to remove a man named John Avory. He works hard, shaking out debts for usurers. A good fighter, a good shot. An impudent brute, which, however, does not prevent him from finding clients "+
				"He was last seen in Willemstad. I don't know where he ran across the aisle to the customer, but he put a bounty on John's head of 15 grand.";
			link.l1 = "Goodley, do you think I'm going to do someone else's job for such pennies?! Either you decided to pocket more than half of the fee, or your customer is a rare brute. Tell me who he is, and I'll beat other conditions out of him.";
			link.l1.go = "PQ5CapGoodly_5";
		break;
		case "PQ5CapGoodly_5":
			dialog.text = "Sorry, "+ GetSexPhrase("buddy", "girlfriend") +", I won't tell you that. The customer won't like it.";
			link.l1 = "Tell me, Goodley, what kind of manner do you have? Again, some 'person', 'I can't refuse', 'the customer won't like it'... Do you take me for a rookie?";
			link.l1.go = "PQ5CapGoodly_6";
		break;
		case "PQ5CapGoodly_6":
			dialog.text = "Don't get too excited again! If you want to know, when delivering Bolton, Morgan himself asked me not to tell the newcomer all the details. He was looking for a reliable person... and as you can see, I found it... So, will you take my order?";
			link.l1 = "And you can flatter yourself. But keep in mind – only for your sake, and only for fifty thousand. ";
			link.l1.go = "PQ5CapGoodly_7";
		break;
		case "PQ5CapGoodly_7":
			dialog.text = "The hell with you. I'll pay with my own money. I just can't refuse this man.I wish you good luck. I'll be waiting in the city.";
			link.l1 = "Heh. No, to put it bluntly: " + PChar.Name + ", this is for ME to remove Avory. But no, I invented some kind of customer. And, Goodley: if you try to cheat me, you'll be the next one... Have a nice stay!";
			link.l1.go = "PQ5CapGoodly_8";
		break;
		case "PQ5CapGoodly_8":
			chrDisableReloadToLocation = false;
			pchar.questTemp.piratesLine = "PL5Hunter_toVillemstad";
			SetQuestHeader("Pir_Line_5_Hunter");
			AddQuestRecord("Pir_Line_5_Hunter", "1");
			AddQuestUserData("Pir_Line_5_Hunter", "sSex", GetSexPhrase("k", "ca"));
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "houseS1", "none", "", "", "", -1.0);
			DialogExit();
		break;
		//Эйвори вместо ГГ
		case "PQ5Hero":
			dialog.text = "...Money! And let's be nice, or my cleaver will taste your blood!";
			link.l1 = "Ha! Do you want to take it?!! Shish to you! This is my prey!!!";
			link.l1.go = "PQ5Hero_1";
		break;
		case "PQ5Hero_1":
            DialogExit();
			AddDialogExitQuestFunction("PQ5_afterChangeMainHero");
		break;
		//Эйвори в доме Шарп-Тауна
		case "PQ5Aivory":
			dialog.text = "You weren't invited! Get out of here while I'm letting you go!";
			link.l1 = "Gentlemen, you may be surprised, but I have an order for both of you. So present your arguments.";
			link.l1.go = "PQ5Aivory_1";
		break;
		case "PQ5Aivory_1":
			dialog.text = "Ha!! And they also say that I'm an impudent person. Well, let's check now who you are...";
			link.l1 = "Let's check...";
			link.l1.go = "PQ5Aivory_2";
		break;
		case "PQ5Aivory_2":
            DialogExit();
			AddDialogExitQuestFunction("PQ5_afterChangeMainHero2");
		break;
		//Гудли в таверне Порт Рояля
		case "PQ5CapGoodlyEnd":
			dialog.text = "Who do I see, " + GetFullName(pchar) + "! You returned! And I must admit, I've been waiting...";
			link.l1 = "Yes, the search took a little longer than I expected. But they ended successfully!";
			link.l1.go = "PQ5CapGoodlyEnd_1";
		break;
		case "PQ5CapGoodlyEnd_1":
			dialog.text = "Ha! You made me incredibly happy! It's a load off my mind. I'm sorry, I haven't yet collected all the money, until only 15000, I'll pay the rest later... Be sure, I won't cheat, I don't need an enemy in your face.";
			link.l1 = "It's good that you understand this. Okay, give me what you have and pack the rest.";
			link.l1.go = "PQ5CapGoodlyEnd_2";
			AddMoneyToCharacter(pchar, 15000);
		break;
		case "PQ5CapGoodlyEnd_2":
			dialog.text = "I'll collect it, don't worry. But such a thing will greatly add to your popularity among pirates, hehe...";
			link.l1 = "Hmm, why would that be? Anyway, Goodley, why on earth would you be so happy?";
			link.l1.go = "PQ5CapGoodlyEnd_3";
		break;
		case "PQ5CapGoodlyEnd_3":
			dialog.text = "Why? Taking down a fighter like Avory is not an easy task. And why shouldn't I be happy if my order is completed. Yeah, I almost forgot: Morgan wanted to see you. So hurry up.";
			link.l1 = "Morgan? And why did he need me, don't you know?";
			link.l1.go = "PQ5CapGoodlyEnd_4";
		break;
		case "PQ5CapGoodlyEnd_4":
			dialog.text = "No, I don't know. He doesn't give me a report. So, for all the answers to him.";
			link.l1 = "Hmm, well, I'll go now... And why are you smiling again, like you're out of your mind?";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "12");
			sld = characterFromId("Henry Morgan");
			LAi_SetHuberTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
			QuestSetCurrentNode("Henry Morgan", "PL_Q5_begin");
		break;
		// -------------------------------------- квест №6 -------------------------------------------------
		case "JohnLids":
			dialog.text = "Greetings to a member of the Brethren! To what do I owe the pleasure of seeing you on my deck?";
			link.l1 = "Hello, John. Jackman sent me to you.";
			link.l1.go = "JohnLids_1";
		break;
		case "JohnLids_1":
			dialog.text = "Very good. What's your full name?";
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "JohnLids_2";
		break;
		case "JohnLids_2":
			dialog.text = "Ha!! It can't be! And then who have we locked up in this bay?";
			link.l1 = "I have no idea. That's exactly what I am " + GetFullName(PChar) +  ". Why are you beating around the bush? Tell me what's going on. Who have you locked up?";
			link.l1.go = "JohnLids_3";
		break;
		case "JohnLids_3":
			dialog.text = "It all started with the fact that poor Sid Bonnet's schooner was captured by a certain privateer named " + GetFullName(pchar) + ", on the corvette. Maybe "+ GetSexPhrase("he's your brother", "she's your sister") +", I don't know. "+
				"Our Bonnet passed to the Spaniards, and they immediately hung him in the city square of Havana. In general, a sad end for a pirate, you will not wish anyone...";
			link.l1 = "Well, what's next with my namesake?";
			link.l1.go = "JohnLids_4";
		break;
		case "JohnLids_4":
			dialog.text = "We caught up with "+ GetSexPhrase("him", "her") +" right here. The corvette was launched to the bottom, but the crew from the sinking ship managed to land.Just pick up the boarders here the issue cannot be solved: these devils are well armed and numerous, and landing the whole team in this bay is very inconvenient. And my guys aren't too eager to fight - you can't bring Sid back, and there's still nothing to profit from these landsmen. You know, nobody wants to die for nothing.";
			link.l1 = "And what do you suggest?";
			link.l1.go = "JohnLids_5";
		break;
		case "JohnLids_5":
			dialog.text = "Well, it seems to me that it is for you to deal with your own relative. Otherwise, you see, you're going to have more problems the further you go. The fact is that there are people in my team who know you by sight. So, they are firmly convinced that you are the one on the corvette... That's it, "+ GetSexPhrase("buddy", "girlfriend") +"!";
			link.l1 = "Yeah, it doesn't get any easier from hour to hour. But maybe you can still help me with people?";
			link.l1.go = "JohnLids_6";
		break;
		case "JohnLids_6":
			dialog.text = "Just that I'll keep this bunch here if you need to go somewhere.";
			link.l1 = "Well, I guess I'll have to do it myself.";
			link.l1.go = "JohnLids_7";
		break;
		case "JohnLids_7":
			dialog.text = "Well, that's nice. Get started, "+ GetSexPhrase("buddy", "girlfriend") +". I am very interested in how it will end...";
			link.l1 = "Heh, you're going to laugh, but so am I.";
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnLids_again";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "3");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase("my namesake", "my namesake"));
			AddQuestUserData("Pir_Line_6_Jackman", "sSex1", GetSexPhrase("iy", "ay"));
			Pchar.quest.PQ6_ShoreBattle.win_condition.l1 = "location";
			Pchar.quest.PQ6_ShoreBattle.win_condition.l1.location = "Shore7";
			Pchar.quest.PQ6_ShoreBattle.function = "PQ6_ShoreBattle";
		break;
		case "JohnLids_again":
			dialog.text = "You're not done with your "+ GetSexPhrase("'brother'", "'sister'") +" yet and I won't wait for you forever...";
			link.l1 = "I got it, John...";
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnLids_again";
		break;
		//двойник ГГ
		case "QuestPirateHead":
			dialog.text = "Ha, so you are " + GetFullName(pchar) + "! Glad to see you, "+ GetSexPhrase("brother", "sister") +"...";
			link.l1 = GetSexPhrase("Brother", "Sister") +"?!";
			link.l1.go = "QuestPirateHead_1";
		break;
		case "QuestPirateHead_1":
			dialog.text = "Well, that's just me, in a friendly way... So what? You still decided to get rid of me?";
			link.l1 = "Come on, tell me. Who are you, where are you from...";
			link.l1.go = "QuestPirateHead_2";
		break;
		case "QuestPirateHead_2":
			dialog.text = "Will you let us go?";
			link.l1 = "Of course! So let's go hand in hand – "+ GetSexPhrase("two brothers!", "two sisters!") +"";
			link.l1.go = "QuestPirateHead_3";
		break;
		case "QuestPirateHead_3":
			dialog.text = "Hmm, you're kidding. Then what's the point of talking?";
			link.l1 = "Argh!! Well, since you're in a hurry...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PQ6_JungleBattle");
		break;
		// -------------------------------------- квест №7 -------------------------------------------------
		case "FriendLinney":
			dialog.text = "Glad to see you on my deck.";
			link.l1 = "I'm looking for Steve Linnaeus, they say you're friends with him, you were seen together in a tavern.";
			link.l1.go = "FriendLinney_1";
		break;
		case "FriendLinney_1":
			dialog.text = "Hmm, maybe friends...";
			link.l1 = "My name is " + GetFullName(pchar) + ", I am running an errand for Morgan. Steve didn't come back for a long time, and since he was gathering information for Morgan, Henry sent me to find out his fate.";
			link.l1.go = "FriendLinney_2";
		break;
		case "FriendLinney_2":
			dialog.text = "Ah, well, I would immediately say . I've known Steve for a long time, and now he's told me about Morgan's assignment. Anyway, he didn't find out anything in La Vega. He was supposed to meet here with a man who supposedly knows something, but the man did not show up for the meeting. Steve was already planning to leave for another city, but in the evening two people I didn't know approached him. They talked, and Steve left with them. You understand, and that would be all right. You never know, maybe he found new informants, but yesterday I accidentally found out that his schooner Swallow is being sold at the Santo Domingo shipyard. And Steve loved his Swallow very much and would never sell it himself. So I thought it was time to leave La Vega out of harm's way. Otherwise, you can wait for them to come for me.";
			link.l1 = "Understood. Maybe he sold it after all? Although, it's all strange...";
			link.l1.go = "FriendLinney_3";
		break;
		case "FriendLinney_3":
			dialog.text = "No, I wouldn't sell it. You just don't know him... I volunteered to help him, but now I don't know what to do.";
			link.l1 = "Okay, I got it. Thanks for the information, buddy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendLinney_again";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
			AddQuestRecord("Pir_Line_7_Soukins", "5");
		break;
		case "FriendLinney_again":
			dialog.text = "We've already talked about Steve, I don't know anything else...";
			link.l1 = "Yes, yes, of course.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendLinney_again";
		break;
		//кэп, продавшие шлюп Ласточку
		case "LeonCapitain":
			dialog.text = "What do you need from me?";
			link.l1 = "Where is captain of the Swallows?!";
			link.l1.go = "LeonCapitain_1";
		break;
		case "LeonCapitain_1":
			dialog.text = "The captain of the Swallow is already at the bottom, he was painfully curious. Ha ha ha!";
			link.l1 = "The Devil!!! Who are you working for?! Who ordered you to remove Linnaeus?!";
			link.l1.go = "LeonCapitain_2";
		break;
		case "LeonCapitain_2":
			dialog.text = "I work for the Admiral of the Brethren. Not at that impostor Morgan, but at our Admiral Richard Sawkins! Join us if you don't want to follow Linnaeus.";
			link.l1 = "I have no reason not to consider Henry Morgan an admiral.";
			link.l1.go = "LeonCapitain_3";
		break;
		case "LeonCapitain_3":
			dialog.text = "And who chose it? Maybe you are?!";
			link.l1 = "But I didn't choose your Admiral Skunk either!";
			link.l1.go = "LeonCapitain_4";
		break;
		case "LeonCapitain_4":
			dialog.text = "We are both pirates, and neither of us chose Morgan as admiral. Think about it. And Morgan is too fast, and he's not nearly as honest with us as people think.";
			link.l1 = "I don't care about your reasoning! Your honest Sawkins has already tried to take me away with someone else's hands twice! And when he realized that he couldn't handle me, he decided to poach me? He's just an ordinary rat, a petty schemer who thinks he's an admiral!";
			link.l1.go = "LeonCapitain_5";
		break;
		case "LeonCapitain_5":
			dialog.text = ""+ GetSexPhrase("Idiot", "Fool") +"! You'll regret your stupidity...";
			link.l1 = "It's not for you to judge my stupidity!..";
			link.l1.go = "LeonCapitain_6";
		break;
		case "LeonCapitain_6":
			Map_ReleaseQuestEncounter("LeonCapitain");
			pchar.questTemp.piratesLine = "Soukins_toMorgan";
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_afterLeon");
			AddQuestRecord("Pir_Line_7_Soukins", "7");
			AddQuestUserData("Pir_Line_7_Soukins", "sSex", GetSexPhrase("", "a"));
			AddQuestUserData("Pir_Line_7_Soukins", "sSex1", GetSexPhrase("xia", "as"));
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//поход на Панаму, пираты в городе
		case "PQ8_PirInPan":
			dialog.text = "You know, " + pchar.name + " it's not for nothing that I joined your team. As a result, I am alive, and even in captured Panama! Who would have thought...?";
			link.l1 = "Yeah, we should make a decent profit on this case.";
			link.l1.go = "PQ8_PirInPan_1";
		break;
		case "PQ8_PirInPan_1":
			dialog.text = "We are already looking for something to grab!";
			link.l1 = "And that's right.";
			link.l1.go = "exit";
		break;
		case "PQ8_RsPirInPan":
			dialog.text = "Oh, it's a pity our captain died! Richard Sawkins was a nice man...";
			link.l1 = "Do you think?";
			link.l1.go = "PQ8_RsPirInPan_1";
		break;
		case "PQ8_RsPirInPan_1":
			dialog.text = "Of course! I served under him for over a year. He was a fair man!";
			link.l1 = "Hmm, I see...";
			link.l1.go = "exit";
		break;
		case "PQ8_MPirInPan":
			dialog.text = "I heard you got a hard time too! Morgan and I were on our way to Panama from Porto Bello.";
			link.l1 = "Yeah, there were Spanish ambushes waiting for us at every turn.";
			link.l1.go = "PQ8_MPirInPan_1";
		break;
		case "PQ8_MPirInPan_1":
			dialog.text = "We had the same thing, pure hell...";
			link.l1 = "But the main thing is that we have coped with this and are alive. So, don't hang up your nose!";
			link.l1.go = "exit";
		break;
		//фантом мэра Панамы
		case "PQ8_Mayor":
			dialog.text = "What do you want from me?";
			link.l1 = "Hello, dear. As far as I understand, you are the governor of Panama...";
			link.l1.go = "PQ8_Mayor_1";
		break;
		case "PQ8_Mayor_1":
			dialog.text = "That's right.";
			link.l1 = "I want you to give me the Escorial gold. I know you have it.";
			link.l1.go = "PQ8_Mayor_2";
		break;
		case "PQ8_Mayor_2":
			dialog.text = "Hmm, well, look...";
			link.l1 = "You're playing with fire! Henry Morgan took Panama, and the whole color of Caribbean piracy gathered here. Can you imagine what will happen to you?";
			link.l1.go = "PQ8_Mayor_3";
		break;
		case "PQ8_Mayor_3":
			dialog.text = "I imagine. But there's nothing I can do to help anyway. The thing is, I don't have the key to the chest, which may contain something... I'm talking about one of the chests in this office.";
			link.l1 = "And where is this key?";
			link.l1.go = "PQ8_Mayor_4";
		break;
		case "PQ8_Mayor_4":
			dialog.text = "He is always with the commandant. This chest has always been under the control of the military, not the civilian authorities of the city.";
			link.l1 = "Where is the commandant now?";
			link.l1.go = "PQ8_Mayor_5";
		break;
		case "PQ8_Mayor_5":
			dialog.text = "I have no idea. He led the defense of the city. As far as I know, he was supposed to attack the Ladrons from the fort. It was necessary to prevent the capture of Panama, so no one defended the fort\n"+
				"So maybe he's been killed, or maybe he's in his fort.";
			link.l1 = "Keep in mind that your life depends on the successful opening of this chest.";
			link.l1.go = "PQ8_Mayor_6";
		break;
		case "PQ8_Mayor_6":
			dialog.text = "I understand. But I can only hope for luck.";
			link.l1 = "I'll look for the key. And I recommend you to strain your memory - perhaps you will remember something else...";
			link.l1.go = "PQ8_Mayor_7";
		break;
		case "PQ8_Mayor_7":
			dialog.text = "If something illuminates me, then you will certainly find out about it. It's in my best interest.";
			link.l1 = "Okay.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_8_Panama", "11");
			pchar.quest.PQ8_MorganInPanama_1.win_condition.l1 = "location";
			pchar.quest.PQ8_MorganInPanama_1.win_condition.l1.location = "Panama_town";
			pchar.quest.PQ8_MorganInPanama_1.function = "PQ8_MorganInPanama_1";
		break;
		//обманутые пиратусы в Панаме
		case "PQ8_FackMorgan":
			dialog.text = LinkRandPhrase("Devil, Henry tricked us!", "Did you hear what did Morgan do?! It's just mind-boggling...", "Now we're finished here, we have to get out of here somehow. Now it's every man for himself...");
			link.l1 = LinkRandPhrase("Yes, I heard...", "Damn!!!", "Blast me!");
			link.l1.go = "exit";
		break;
		//первый подбегающий пират
		case "PL_Q8_QFackMorgan":
			dialog.text = "You're just in time, Captain! It's a pity that you weren't here a little earlier...";
			link.l1 = "What happened?";
			link.l1.go = "PL_Q8_QFackMorgan_1";
		break;
		case "PL_Q8_QFackMorgan_1":
			dialog.text = "Ha!! I'm going to make you so happy that you'll go crazy with joy!";
			link.l1 = "Speak to the point, don't drag it out.";
			link.l1.go = "PL_Q8_QFackMorgan_2";
		break;
		case "PL_Q8_QFackMorgan_2":
			dialog.text = "Our admiral, Henry Morgan, has collected loot from all of us! He built the pirates and was the first to empty his pockets into the common cauldron!";
			link.l1 = "So what, I knew that. What's so extraordinary about that?";
			link.l1.go = "PL_Q8_QFackMorgan_3";
		break;
		case "PL_Q8_QFackMorgan_3":
			dialog.text = "There's nothing in it, but that's not all the news... We all laid out the contents of our wallets and went about our business, waiting for Henry to divide everything according to the law of the Brethren. Meanwhile, our valiant and most honest admiral quietly sank into a Spanish galleon and gave up.";
			link.l1 = "How? And the money?!";
			link.l1.go = "PL_Q8_QFackMorgan_4";
		break;
		case "PL_Q8_QFackMorgan_4":
			dialog.text = "Our money also ran out with Morgan! That's what I'm telling you-Henry took all the loot and left us here in this damn Panama!";
			link.l1 = "It can't be... But it just can't be!..";
			link.l1.go = "PL_Q8_QFackMorgan_5";
		break;
		case "PL_Q8_QFackMorgan_5":
			dialog.text = "Ha! That's a fact, Captain! What should I do now?";
			link.l1 = "The Devil!! Of course, I suspected that Morgan is not as honest as he wants to seem, but to leave his army in an empty city without loot and food like that!..";
			link.l1.go = "PL_Q8_QFackMorgan_6";
		break;
		case "PL_Q8_QFackMorgan_6":
			dialog.text = "Oh, if Sawkins were alive, nothing like this would happen for sure! What a captain he was, a real admiral!God, how many times has Richard said that Morgan would betray us. And we all didn't listen, we lingered...";
			link.l1 = "What do you mean you were slow?";
			link.l1.go = "PL_Q8_QFackMorgan_7";
		break;
		case "PL_Q8_QFackMorgan_7":
			dialog.text = "That's what it means! Sawkins applied for the position of admiral of the Brethren, but we persuaded him not to rush the election. Carramba, how wrong we were!";
			link.l1 = "Like your Sawkins, like our Morgan, one was worth the other...";
			link.l1.go = "PL_Q8_QFackMorgan_8";
		break;
		case "PL_Q8_QFackMorgan_8":
			dialog.text = "Yeah, you and Morgan lived soul to soul. I didn't think he'd leave you here either...";
			link.l1 = "Well, we'll see about that!! What was the name of the galleon that Morgan left on?";
			link.l1.go = "PL_Q8_QFackMorgan_9";
		break;
		case "PL_Q8_QFackMorgan_9":
			dialog.text = "I don't remember. Whether 'Fortune' or 'Wheel of Fortune'... Come on, you can't find it. Otherwise, I went to Europe, or even to India..\nAll right, no Admiral, no money, no Brethren!";
			link.l1 = "Carramba!! It's no use hanging around here anyway. We need to gather people, share gunpowder, bullets and food, and go through the jungle to the Darien Bay to our ships.";
			link.l1.go = "PL_Q8_QFackMorgan_10";
		break;
		case "PL_Q8_QFackMorgan_10":
			dialog.text = "Through the jungle again? No, I won't survive a second trip like this. And no one will go with you: "+ GetSexPhrase("You are friends with Morgan!", "Everyone is sure that you are Morgans... w-w... well, girlfriend.")+  " And if you mention collecting something, I'm sure you'll get a bullet in the forehead right away! It's every man for himself now, Captain... Well, okay, I don't have time to make mistakes with you here. I'm going to the tavern, I hope there's still rum left...";
			link.l1 = "Go on, go. There's no point in me sticking around.";
			link.l1.go = "PL_Q8_QFackMorgan_11";
		break;
		case "PL_Q8_QFackMorgan_11":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_houseS1")], true);
			SetTimerFunction("PQ8_openPanama_2", 0, 0, 30);
			pchar.questTemp.piratesLine = "Panama_backToShip";
			AddQuestRecord("Pir_Line_8_Panama", "13");
			CloseQuestHeader("Pir_Line_8_Panama");
			Pchar.quest.PL_Q8_backFight_1.win_condition.l1 = "location";
			Pchar.quest.PL_Q8_backFight_1.win_condition.l1.location = "Panama_jungle_04";
			Pchar.quest.PL_Q8_backFight_1.function = "PL_Q8_backFight_1";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
