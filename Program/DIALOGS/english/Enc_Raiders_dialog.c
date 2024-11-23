void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	int iMoney;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "exit_Robbed":
			ChangeCharacterReputation(pchar, -1);
			//int iMoney = makeint(makeint(Pchar.money)/20)*10;
			iMoney = sti(NPChar.moneyfee);
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			AddSimpleRumour(LinkRandPhrase("Did you hear the local robber" + GetFullName(npchar) + "another victim has appeared. One captain chickened out and paid off. Rumor has it he's gone away " + FindRussianMoneyString(iMoney) + ", hee hee...",
				"Yes, Captain " + GetFullName(pchar) + ", I've already heard what you had to give away " + FindRussianMoneyString(iMoney) + " to buy off a local bandit " + GetFullName(npchar) + ". Well, what can I say - no luck! Ha ha ha!",
				"Have you heard that local robbers attacked some captain? So, he was robbed of the whole " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("You've finally heard about this bandit" + GetFullName(npchar) + "the board was found. He and his friends wanted to rob "+ GetSexPhrase("some captain, but he turned out to be", "some kind of sailor, but she turned out to be") +"they can't handle it. As a result, our brave robber pissed himself in his pants, haha! It serves him right, it's not for him to shake loose change from local farmers.",
				"Thank you so much, Captain " + GetFullName(pchar) + ", you finally broke up this gang of " + GetFullName(npchar) + ". And then there was no life at all from these scoundrels. Sometimes you're afraid to send a messenger to the farm for milk, they'll meet you and take away the money."),
				"You heard, "+ GetSexPhrase("finally some captain gave", "some sailor girl gave") +" a worthy rebuff to this thug " + GetFullName(npchar) + ", who was operating in the jungle and terrifying local farmers. I wonder how long this will discourage them from robbing.",
				"Have you not heard that the local bandit" + GetFullName(npchar) + " tried to rob with his henchmen "+ GetSexPhrase("some kind of captain", "some girl captain") +"? So, it was not there - captain provided a tough nut to crack. They say these robbers are moving through the jungle like a shark through a flock of sardines. Thank God that there are still people who can stand up for us at a time when the authorities are inactive, too busy with their own affairs..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_SetCitizenTypeNoGroup(sld);
				//#20200315-01
                sld.chr_ai.type.checkFight = 999999.0;
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			bool bRape = GetOfficersQuantity(pchar) == 0 || rand(4) == 0;
			if (pchar.sex == "woman" && bRape)
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Well, wow, what a beauty is wandering through the jungle! ",
				"That's lucky for me today, I'm finally going to get laid with a woman! ",
				"Not so fast, darling, there's one thing for you to do! ")+
				LinkRandPhrase("I hope you don't mind if we have a little fun? I must say right away, I do not accept refusals.",
				"Let's do it the good way: take off your clothes, do the job and move on.",
				"You didn't think you could just walk past me like that, did you? You'll have to meet my little friend first!"),

				LinkRandPhrase("Pop my eyes! Lady, do you know that you are getting married today?  Accidentally and for a short time...",
				"Wait, milaha, there is no need to hurry anywhere, you have already found your destiny. My friend liked you, if you're not stupid, I'll like you too... Throw the piece of iron, let's get to know each other better, baby.",
				"Well, chick, did you go into the forest out of longing? We can make you laugh! Who's the last one and Dad, guys!"))

				Link.l1 = "Okay, do your thing, you bastard."
				Link.l1.go = "Rape";
				if (GetOfficersQuantity(pchar) > 0)
				{
					Link.l1 = LinkRandPhrase("Well, no, I won't give myself to you, and my guards won't allow it.",
					"You should stop with these dirty thoughts, my boarders won't let me be offended anyway. ",
					"You could try to take me, but think about it, is it worth risking your life for this in a fight with my officers? ")+
					LinkRandPhrase("Let me pay you with money, and we'll part without bloodshed.",
					"In return, how about a small sum of money so that we can part peacefully?",
					"How much money do you want to let us through?")
					Link.l1.go = "Node_2_woman";
				}
				Link.l2 = RandPhraseSimple("I attacked the wrong one, scum. I'm not a fragile girl, I can stand up for myself.",
				"Say that down the barrel of my gun, you horny baboon!",
				"Yes, you have decided to become a dancer in any way, but something prevents you? Come on, my blade will fix it in a moment.");
				Link.l2.go = "CheckSkills";
				break;
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("Stop! Drop your weapon! Lay out the gold, or you'll die on the spot!",
				"Don't move, "+ GetSexPhrase("traveler", "girl") +"! Do not touch the weapon and do not try to joke if life is precious!",
				"Wait, "+ GetSexPhrase("traveler", "girl") +"! This is a toll road! If you want to pass, give me the toll."),
				LinkRandPhrase("Hey, "+ GetSexPhrase("buddy", "girlfriend") +"! Not so fast! I want to see if your purse is too heavy.",
				"Come closer, my dear. I want to hear the gold jingling in your purse.",
				"Wait a minute, "+ GetSexPhrase("buddy", "girlfriend") +". My friends and I were arguing about how much gold would fit into your purse. Now we need to check before it comes to a fight."),
				"Take your time, "+ GetSexPhrase("passer-by", "darling") +"! I want to have a heart-to-heart talk with you.");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("What are you talking about?", "What's the matter?", "What are you talking about?"), "What do you mean?", "What are you talking about?");
			Link.l1.go = "Node_2";

			Link.l2 = LinkRandPhrase(LinkRandPhrase("No robbers?! Let's get some rest now!",
				"Robbers, what is it?! Are you running from justice, I suppose? But justice has come to you by itself...",
				"Didn't they teach you that it's not good to molest all sorts of nonsense? I'll have to teach you a lesson..."),
				LinkRandPhrase("Oh, you insolent fellow! I hope your blade is as sharp as your tongue.",
				"I see you have a sharp tongue. I hope you're just as good with a blade?",
				"Ah, the robbers! They hang you, they hang you, but you still don't let up..."),
				LinkRandPhrase(RandPhraseSimple("Ah, the robbers! I have a short conversation with people like you!",
				"Well, the impudent one! You stink a mile away, but you're talking too much for a decent "+ GetSexPhrase("man", "girl") +"."),
				"My gun usually talks to people like you!",
				"Robbers again! Well, I don't promise you the gallows, but I can make a couple of holes in my belly!"));
			Link.l2.go = "CheckSkills";
			Link.l3 = LinkRandPhrase("Do you know that a patrol unit is following me? All I have to do is whistle, and you're dead.",
				RandPhraseSimple("Aren't you afraid that I'll call the patrol? They're looking for you right here.",
				"A patrol unit has already been sent for you, he will be here any minute, so you are taking a big risk."),
				RandPhraseSimple("You'd better get out of here fast. A patrol unit is heading here, I was just talking with their officer.",
				"I would love to continue a conversation, but I'm afraid the patrol squad that I just met will not let our acquaintance grow into a close friendship."));
			Link.l3.go = "Node_3";
		break;

		case "Node_2":
			iMoney = 100*MOD_SKILL_ENEMY_RATE*3*sti(NPChar.EncQty)+makeint(100 * sti(PChar.rank))+makeint(100 * sti(NPChar.rank)*sti(NPChar.EncQty));
			NPChar.moneyfee = iMoney;
			dialog.text = LinkRandPhrase(LinkRandPhrase("Don't pretend to be a simpleton! Lay out your gold, then maybe I'll let you go!",
				"Haven't you heard about travel expenses? If you don't part with your gold, you'll part with your head!",
				"Heh, this is an ordinary road trip that will cost you your wallet... That's if I don't get angry."),
				RandPhraseSimple("It's very simple - you voluntarily give us the gold and leave, or you stay here and we leave with your gold, but you probably won't like the second option, hehe.",
				"And you don't seem to understand. Untie the purse! If you don't want me to take it off your corpse!"),
				"I'm explaining, since you're like incomprehensible. Give me all the money if you want to live!");
				dialog.text = dialog.text+ "\nI don't think you'd become poor by giving away "+iMoney+" piastres. Approximately per "+makeint(iMoney/sti(NPChar.EncQty))+" on brother.";
			//Link.l1 = "Damn it! You bastard! I only have with me " + makeint(makeint(Pchar.money)/20)*10 + "piastres.";
			if(sti(pchar.money) >= sti(NPChar.moneyfee))
			{
				Link.l1 = "Damn it! You bastard! Take your money!";
			}
			else
			{
				Link.l1 = "I don't have that much money.";
			}
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase((LinkRandPhrase("Do you want money? So come and get it, and I'll see how many pennies you're worth.",
				"How dare you, you ignoramus! I'll have to give you a lesson in manners!",
				"What arrogance! Well, let's see if the land rats can handle the seawolf!")),
				LinkRandPhrase("You should be whipped for such insolence!",
				"Oh, you scoundrels! Well, then pray to your devils!",
				"You gallows should be hanged in the square! Yes, you'll have to dirty your sword!"),
				RandPhraseSimple("What makes you think I'm going to shake my purse in front of you?",
				"Doesn't it bother you that I'm well armed?"+" And I didn't run out into the jungle half asleep?"));
			Link.l2.go = "CheckSkills";
		break;

		case "Node_2_woman":
			iMoney = 100*MOD_SKILL_ENEMY_RATE*3*sti(NPChar.EncQty)+makeint(100 * sti(PChar.rank))+makeint(100 * sti(NPChar.rank)*sti(NPChar.EncQty));
			NPChar.moneyfee = iMoney;
			dialog.text = "I think you won't be impoverished by giving it away."+iMoney+" piastres. Approximately by "+makeint(iMoney/sti(NPChar.EncQty))+" on brother.";
			//Link.l1 = "Damn it! You bastard! I only have with me " + makeint(makeint(Pchar.money)/20)*10 + "piastres.";
			if(sti(pchar.money) >= sti(NPChar.moneyfee))
			{
				Link.l1 = "Damn it! You bastard! Take your money!";
			}
			else
			{
				Link.l1 = "I don't have that much money.";
			}
			Link.l1.go = "CheckMoney";
			Link.l2 = RandPhraseSimple("How much? Well, that's arrogance, we'll have to teach you a lesson for it.",
				"And I was hoping for your discretion. With these prices, it's much easier for us to kill you!");
			Link.l2.go = "CheckSkills";
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation) < 10 || makeint(pchar.reputation) > 90;
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckOfficersPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("Damn it! Okay, bye. And don't make a fuss.",
					"You're lucky this time, but next time you'll owe me doubly! Don't forget to remind me, hehe.");
				Link.l1 = RandPhraseSimple("Well, how can I?", "Come on, come on, run while you're safe.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk1 = makeint(pchar.reputation) < 61 && makeint(pchar.reputation) > 39;
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("And we'll cut you down quietly, you won't even have time to make a sound.",
						"Damn it! I'll have to cut you down quickly without making a fuss.");
					Link.l1 = "Well, as you know. I warned you.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("What do I care about your patrol? I've got everything captured here and paid for everything. So turn out your purse and use your tongue less.",
						"Who are you trying to scare?! I'm the patrol in this forest for people like you. Not one has left without a fee yet!");
					Link.l1 = "Damn it! You bastard! I only have " + makeint(makeint(Pchar.money)/20)*10 + " piastres with me.";
					Link.l1.go = "CheckMoney";
					Link.l2 = RandPhraseSimple(LinkRandPhrase("Hmm, it's not your place to command me.",
						"For such audacity, I will make a couple of holes in your head. To clear my head.",
						"Such insolence cannot go unpunished!"),
						"Eh, you're not doing your job...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;

		case "CheckSkills":
			bool z_ok = (GetCharacterSkillToOld(Pchar, "Fencing") >= 7) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation) < 30);
			if (z_ok || CheckOfficersPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Hey, don't be so nervous, "+ GetSexPhrase("buddy", "girlfriend") +"! I was joking! Go your own way!",
					"Okay, I've changed my mind. You can go, if that's the case."),
					"What, "+ GetSexPhrase("'brave captain'", "'fighting girl'") +" again? Okay, go in peace...",
					"Keep it down, "+ GetSexPhrase("buddy", "girlfriend") +". Don't you see, we've made a mistake. Get out of harm's way.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("Well, then, see you later!",
					"You should give up this case while the skin is intact.",
					"Well, look, don't get caught by me anymore."),
					RandPhraseSimple("Next time, watch who you open your mouth to.",
					"Thank God that I am kind today."),
					RandPhraseSimple("Such a trade will not bring you any good. Goodbye.",
					"Well, that's a wise decision. Have a nice stay!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("No way, buddy. I'll have to teach you some manners.",
					"Did you get scared?! But you need to be responsible for your actions! Isn't that right?",
					"No way! Now I won't rest until I ruin your hide.");
				Link.l99.go = "GetTheHellOut";
			}
			else
			{
				dialog.text = LinkRandPhrase("But I wish I could leave in peace! Now blame yourself!",
								"You shouldn't have started this. You rascal! Now you're going to die like a dog!",
								"I'll tear you to pieces! I'll cut out the liver and feed it to the dogs!");
				Link.l1 = RandPhraseSimple("I'll shove these words down your throat!", "Who are you threatening, scum?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(sti(pchar.money) >= sti(NPChar.moneyfee))
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Good! Give them to me and get out!",
					"It's not much, but it's better than nothing. It's nice to deal with an intelligent person! You can go now."),
					"That's another thing! As one of my friends said, it's nice to listen to an intelligent person, but you can talk to a fool, hehe.",
					"In exchange for your gold, I'll give you some advice-don't wander around the jungle, "+ GetSexPhrase("if you're such a weakling! Sit in a port tavern, and drink your rum - you'll be healthier", "a girl. Otherwise, they can not only rob") +".");
				Link.l1 = "Damn hanged men!";
				Link.l1.go = "Exit_Robbed";
			}
			else
			{
				dialog.text = "I think you're trying to trick me! But never mind, I'm going to tickle you now - you'll see what will fall out.";
				Link.l1 = "Damn it!";
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "Rape":
			AddCharacterExpToSkill(pchar, "Leadership", -100);
            AddCharacterExpToSkill(pchar, "Fencing", 50);
            AddCharacterExpToSkill(pchar, "Pistol", 50);
            AddCharacterHealth(pchar, -10);
			Diag.TempNode = "OnceAgainRape";
			AddDialogExitQuest("PlaySex_1");
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgainRape";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();
		break;

		case "OnceAgainRape":
			Diag.TempNode = "OnceAgainRape";
			dialog.text = LinkRandPhrase("We're done, you can go where you were going.",
				"I hope we'll see each other again, hehe. In the meantime, you can go.",
				"If you don't want to go on a second run, you'd better get out of here.");
			Link.l1 = "I'm leaving now.";
			Link.l1.go = "Exit";
			Link.l2 = "No way, I'll leave only after you're dead, you bitch!";
			Link.l2.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("You again? Come on, run home to your mom! Otherwise, I might get angry.",
				"What? You didn't give away all gold? Ha ha ha!",
				"Listen, "+ GetSexPhrase("buddy", "girlfriend") +", I'm tired of you! Get out of sight while you're alive!");
			Link.l1 = "Yes, I'm already leaving.";
			Link.l1.go = "Exit";
			Link.l2 = "I thought that it would be unfair. Here, I've decided to equalize costs...";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("What do you need? We agreed that you were leaving!",
				"Leave me alone, "+ GetSexPhrase("guy", "girl") +". I have my own business, you have your own, we shouldn't keep getting to know each other!",
				"Go away, "+ GetSexPhrase("buddy", "girlfriend") +"! Damn it, do you really want to give your money away after all?");
			Link.l1 = "Yes, I'm already leaving.";
			Link.l1.go = "Exit";
			Link.l2 = "I remembered that you didn't say goodbye! So come on... Say goodbye!";
			Link.l2.go = "Exit_Fight";
		break;
        //#20200315-01
        case "CitizenNotBlade":
            npchar.chr_ai.type.checkFight = 999999.0;
            Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("I've decided to punish you for your evil deeds!",
				"Get off me! Get out! I want to live!",
				"Help me! "+ GetSexPhrase("He's a maniac", "She's a maniac") +"! Don't kill me!");
			Link.l1 = "Have mercy! I'm just a lowly robber! I'm too young to die!";
			Link.l1.go = "Exit";
        break;
		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("Get off me! Get out! I want to live!",
				"Help me! "+ GetSexPhrase("He's a maniac", "She's a maniac") +"! Don't kill me!",
				"Have mercy! I'm just a lowly robber! I'm too young to die!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("If I stayed at home, I would live longer!",
				"You should have thought earlier!",
				"You knew what you were doing!"),
				"It had to happen sooner or later.",
				"It's too late to repent, defend yourself!");
			Link.l1.go = "exit_Fight";
		break;
	}
}
