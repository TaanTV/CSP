
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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
	if (PChar.sex != "woman")
	{
		dialog.text = "May I burst! Old man " + GetFullName(PChar) + "!";
		link.l1 = "Atilla! Hello, old sea devil!";
		link.l1.go = "port_1";
	}
	else
	{
		dialog.text = "Beauty " + GetFullName(PChar) + "! How glad I am to see you!";
		link.l1 = "But I'm not happy about you, Attila. We have nothing to talk about. Or do you think I've forgotten how you framed me in Caracas? Get lost.";
		link.l1.go = "W_exit";
		if (startherotype == 2)
		{
			dialog.text = RandPhraseSimple("What do you want? Pass by.", "Stop blocking the road, get off.");
			link.l1 = RandPhraseSimple("You know what? Don't bark!", "Slow down your ardor. Otherwise I'll cool it down quickly!");
			link.l1.go = "exit";
			NextDiag.TempNode = "W_exit";
		}
	}
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "talker"); //снимаем говорилку
		break;

	case "W_exit":
		npchar.lifeDay = 1;
	LAi_CharacterDisableDialog(npchar);
    DialogExit();
	break;

	case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = "" + PChar.name + ", what kind of nonsense is this? Put the weapon away immediately!";
				link.l1 = LinkRandPhrase("Okay.", "Okay.", "Don't worry, I'm already removing...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful on turns, "+ GetSexPhrase("buddy", "girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like when "+ GetSexPhrase("men", "all sorts") +" walk in front of me with weapons at the ready. It scares me...");
				link.l1 = LinkRandPhrase("Okay.", "Okay.", "Don't worry, I'm already removing...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "port_1":
		    sld = characterFromID("Atilla");
			dialog.text = "Look, you've dressed up like your don!  Probably, the wind doesn't whistle in your pockets either! Would you like to offer a drink to an old friend?";
			if (pchar.RomanticQuest == "")
			{
			    link.l1 = "I'm damn glad to see you, but I can't right now, buddy. Another time...";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "Ha ha ha! It's a sin not to knock over a mug of good Jamaican rum for such a meeting!";
				link.l1.go = "port_1_1";
			}
		break;

		case "port_1_1":
			dialog.text = "Burst my spleen, you need to drink to such a meeting! Go to the tavern immediately...";
			link.l1 = "I agree - to the tavern!";
			link.l1.go = "port_toTavern";
		break;

		case "port_toTavern":
			DialogExit();
			NextDiag.CurrentNode = "Tavern_1";
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			FreeSitLocator("Pirates_tavern", "sit3");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Pirates_tavern", "sit", "sit3", "Romantic_Pirat_toTavern", -1);
		break;

		case "Tavern_1":
			LAi_SetSitType(Pchar);
			dialog.text = "Damn it, " + GetFullName(PChar)+"! You and I did a nice job in Caracas that time, damn me!";
			link.l1 = "Yeah... You sent many Catalan devils to their forefathers in that battle. For that dashing cabin, you were given this nickname - Attila... I see you haven't had much luck since then.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "Arrgh! I'll tell you what - never trust these Catalan dons! I went with one. They took a French vessel once. The jeweler was among the passengers.  I don't care about his bills of exchange, but I know a lot about trinkets. Mother of God, they cost so much that you could buy half of Hispaniola and the governor's house with the governor himself in addition. Well, we divided everything honorably, found five barrels of rum in the hold, got drunk on joy...";
			link.l1 = "Heh, well, as always...";
			link.l1.go = "Tavern_3";
		break;

		case "Tavern_3":
			dialog.text = "That's right, but the next morning it turned out that my friend is not a fool. I untied the skiff at night, took all the stuff and was gone.";
			link.l1 = "And you let him get away with it? May the shark swallow me! Yes, I would...";
			link.l1.go = "Tavern_4";
		break;

		case "Tavern_4":
			dialog.text = "What would you do, rookie?! He fled to the Spanish island. And I'm not allowed to go there. Well, God be with him. You could have just cut my throat, a drunken fool, and no one would have said a word.";
			link.l1 = "Hmm, you've become painfully melancholic, my friend.";
			link.l1.go = "Tavern_5";
		break;

		case "Tavern_5":
			dialog.text = "Time is passing, and I'm getting old. It's not so easy for me to send a man to the next world... and Salvator, they say, played a wedding with my money. He lives in San Juan now...";
			link.l1 = "Damn me!  Atilla, my friend, why don't I visit this quiet family nest? You see, your wife's jewelry box will find your trinkets, eh?";
			link.l1.go = "Tavern_6";
		break;

		case "Tavern_6":
			dialog.text = "Ha ha ha! It seems to me that you didn't decide to sneak into her bedroom for the sake of trinkets!  No, my friend, since the prey has sailed away from my hands, it must be so... Well, it's time for me. God willing, we'll see each other again.";
			link.l1 = "Goodbye, Atilla.";
			link.l1.go = "Tavern_Out";
		break;

		case "Tavern_Out":
			NextDiag.CurrentNode = "Tavern_Bye";
			DialogExit();
			AddDialogExitQuest("Romantic_Pirat_toTavern_end");
		break;

		case "Tavern_Bye":
            NextDiag.TempNode = "Tavern_Bye";
			dialog.text = "I'm going to finish my drink and go to the ship...";
			link.l1 = "I won't bother you.";
			link.l1.go = "exit";
		break;
		//доводим новости до сведения Атиллы
		case "TalkingNews":
			dialog.text = "Oh, who do I see!? " + GetFullName(pchar) + ", in person!";
			link.l1 = "Hello, Atilla! Things seem to be getting better for you slowly - you bought a house...";
			link.l1.go = "TalkingNews_1";
		break;
		case "TalkingNews_1":
			dialog.text = "Money appeared, so I decided to invest in real estate. Although, to be honest, a house here is far from a house on Tortuga...";
			link.l1 = "Well, it's also a roof.";
			link.l1.go = "TalkingNews_2";
		break;
		case "TalkingNews_2":
			dialog.text = "Hmm, that's right! Well, tell me, why did you come to me?";
			link.l1 = "Yes, you know, there's such a thing here that you can't tell it in two words... Anyway, I visited your friend Salvator Olevares.";
			link.l1.go = "TalkingNews_3";
		break;
		case "TalkingNews_3":
			dialog.text = "Heh, that's the news! How's this crook doing? Was it true that you got married?";
			link.l1 = "Yes, the truth. His wife, Isabella, is a very beautiful woman... And decent, too.";
			link.l1.go = "TalkingNews_4";
		break;
		case "TalkingNews_4":
			dialog.text = "Heh, what makes you think that? Women are an insidious people, and great evil can hide behind external beauty.";
			link.l1 = "Evil is Salvator! I haven't told you what happened, so listen up.";
			link.l1.go = "TalkingNews_5";
		break;
		case "TalkingNews_5":
			dialog.text = "With pleasure...";
			link.l1 = "Anyway, I arrived in San Juan after talking to you and started to figure out what was what. A lot of things happened there, but in the end it turned out that Salvator robbed his wife and killed her brother in front of me.";
			link.l1.go = "TalkingNews_6";
		break;
		case "TalkingNews_6":
			dialog.text = "Yeah, he's gone, you bastard...";
			link.l1 = "He slandered me and tried to arrest me... When I managed to resolve the situation somehow, Salvator disappeared into the water. And Isabella is locked in the house, she won't let anyone in...";
			link.l1.go = "TalkingNews_7";
		break;
		case "TalkingNews_7":
			dialog.text = "Well, friend, thank you for trying to restore justice. What do you think to do next?";
			link.l1 = "I'm thinking of finding Salvator and gutting him. I also need to explain myself to Isabella... She thinks I killed her brother.";
			link.l1.go = "TalkingNews_8";
		break;
		case "TalkingNews_8":
			dialog.text = "Wow, buddy, do you care?";
			link.l1 = "No, Atilla, not anymore...";
			link.l1.go = "TalkingNews_9";
		break;
		case "TalkingNews_9":
			dialog.text = "L'amour... Qu'ici faire?";
			link.l1 = "What?";
			link.l1.go = "TalkingNews_10";
		break;
		case "TalkingNews_10":
			dialog.text = "This is French... Nothing, it's all right.\n"+
				          "And where do you think to look?";
			link.l1 = "I don't know, I just can't figure it out.";
			link.l1.go = "TalkingNews_11";
		break;
		case "TalkingNews_11":
			dialog.text = "Listen, you smoked Salvator out of San Juan, and that's very good. Now I can connect to the search.";
			link.l1 = "And will you be able to find it?";
			link.l1.go = "TalkingNews_12";
		break;
		case "TalkingNews_12":
			dialog.text = "I think so. You are not the only one who respects Attila, this pirate also has friends...";
			link.l1 = "Well, that would be great. What should I do?";
			link.l1.go = "TalkingNews_13";
		break;
		case "TalkingNews_13":
			dialog.text = "Mind your own business for now, well, I'll do the search right now. You can't help me in any way, you'll only get in the way. We'll meet here in two months, at my house. Then I'll tell you everything I've learned.";
			link.l1 = "Okay, Atilla. Well, good luck to you.";
			link.l1.go = "TalkingNews_14";
		break;
		case "TalkingNews_14":
			SetTimerCondition("Romantic_AtillaToHouse", 0, 2, 0, false);
			AddQuestRecord("Romantic_Line", "11");
            LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			//открываем дом Сальватора и убираем Изабеллу, ставим наёмных убийц в дом.
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", false);
			ChangeCharacterAddress(characterFromId("Isabella"), "none", "");
            Pchar.quest.Romantic_AmbushInHouse.win_condition.l1 = "location";
            Pchar.quest.Romantic_AmbushInHouse.win_condition.l1.location = "SanJuan_houseSp6";
            Pchar.quest.Romantic_AmbushInHouse.win_condition = "Romantic_AmbushInHouse";
			DialogExit();
		break;
		//через два месяца по завершению поисков
		case "AtillaInHouse":
			dialog.text = "Ah, here you are, " + GetFullName(pchar) + ". Come on in, it's good to see you.";
			link.l1 = "Atilla, how are you doing? Have you learned anything new about our great friend?";
			link.l1.go = "AtillaInHouse_1";
		break;
		case "AtillaInHouse_1":
			dialog.text = "Found out, " + pchar.name + ", how else? Anyway, Salvator was pretty shaken up by you. He's not sitting in one place anymore, he's constantly moving around.";
			link.l1 = "And how do I catch him now?";
			link.l1.go = "AtillaInHouse_2";
		break;
		case "AtillaInHouse_2":
			dialog.text = "I need to think...";
			link.l1 = "Listen, do you know anything about Isabella?";
			link.l1.go = "AtillaInHouse_3";
		break;
		case "AtillaInHouse_3":
			dialog.text = "I know, buddy. It looks like Salvator lured her out of San Juan. He sent the pirate brig Rapturous for her and, according to rumors, the cap set course for Porto Bello.";
			link.l1 = "And why does he need it? He has already ruined her...";
			link.l1.go = "AtillaInHouse_4";
		break;
		case "AtillaInHouse_4":
			dialog.text = "I guess to hide the ends in the water, buddy. Your Isabella will not live if she falls into Salvator's hands.";
			link.l1 = "Argh, when did the brig leave San Juan? I have to intercept him in time!";
			link.l1.go = "AtillaInHouse_5";
		break;
		case "AtillaInHouse_5":
			dialog.text = "If you want to see Isabella alive, then yes. The brig sailed from San Juan three days ago. According to my calculations, he will be at Porto Bello in fifteen to sixteen days, no more.";
			link.l1 = "So I have to hurry... Thank you, Atilla!";
			link.l1.go = "AtillaInHouse_6";
		break;
		case "AtillaInHouse_6":
			dialog.text = "Buddy, don't forget the little detail - Salvator himself must be somewhere in Porto Bello. He's waiting for Isabella there.";
			link.l1 = "Heh, that's right! Attila, I have to hurry. If everything goes well, then I will return the lost jewels to you.";
			link.l1.go = "AtillaInHouse_7";
		break;
		case "AtillaInHouse_7":
			dialog.text = "Okay, " + pchar.name + ". Good luck to you!";
			link.l1 = "Thank you, Atilla.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AtillaInHouse_Again";
			AddQuestRecord("Romantic_Line", "13");
			pchar.RomanticQuest = "AttackBrig"; //флаг для кэпа на абордаже брига
            Pchar.quest.Romantic_AttackBrig.win_condition.l1 = "location";
            Pchar.quest.Romantic_AttackBrig.win_condition.l1.location = "PortoBello";
            Pchar.quest.Romantic_AttackBrig.win_condition = "Romantic_AttackBrig";
			SetTimerCondition("Romantic_BrigTimeOver", 0, 0, 16, false);
		break;
		case "AtillaInHouse_Again":
			dialog.text = "Well, how are you doing?";
			link.l1 = "No way yet...";
			link.l1.go = "exit";
		break;
		// после погони за бригом Восторженный, если не догнал его вообще
		case "Brig_Late":
			dialog.text = "Well, tell me, how are you doing?";
			link.l1 = "It doesn't matter... I couldn't catch up with this brig, I didn't even see the stern...";
			link.l1.go = "Brig_Late_1";
		break;
		case "Brig_Late_1":
			dialog.text = "Hmm, bad... It seems that Isabella is no longer alive...";
			link.l1 = "You're probably right. When I think about it, my heart breaks apart...";
			link.l1.go = "Brig_Late_2";
		break;
		case "Brig_Late_2":
			dialog.text = "Tears of grief can't help, why bother now? This adventure is over for you, you need to move on.";
			link.l1 = "You're right, Atilla. Thank you for your support. Goodbye...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Last_Talk";
			CloseQuestHeader("Romantic_Line");
			pchar.questdata.IstoriyaIzabely = 1;
			DeleteAttribute(pchar, "RomanticQuest");
		break;
		case "Last_Talk":
			dialog.text = "Soon I will have to go to sea too - I need to live on something...";
			link.l1 = "Good luck to you, Atilla.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Last_Talk";
		break;
		// если догнал бриг свалил или ГГ ушёл на карту
		case "Brig_DieHard":
			dialog.text = "Well, buddy, what's the news?";
			link.l1 = "Bad news. I caught up with a brig at Porto Bello, but I couldn't board it...";
			link.l1.go = "Brig_DieHard_1";
		break;
		case "Brig_DieHard_1":
			dialog.text = "Mmm, that's very bad. Isabella is probably already dead...";
			link.l1 = "Carramba! Apparently, this is how it is... I can't think about it without crying...";
			link.l1.go = "Brig_Late_2";
		break;
		// если догнал бриг, но утопил его
		case "Brig_Sunk":
			dialog.text = "Well, tell me, how are you doing?";
			link.l1 = "It doesn't matter... I caught up with the brig at Porto Bello, but I could not board it - it sank during the battle. No one survived...";
			link.l1.go = "Brig_Sunk_1";
		break;
		case "Brig_Sunk_1":
			dialog.text = "Yeah, buddy, it's bad... You will not envy you - you have lost the woman you liked...";
			link.l1 = "I can't talk about it - my heart is breaking apart...";
			link.l1.go = "Brig_Late_2";
		break;
		// если Изабелла утонула с бригом, нет векселей
		case "Isabella_Sink":
			dialog.text = "Well, tell me, how are you doing?";
			link.l1 = "It doesn't matter... I caught up with a brig at Porto Bello and boarded it.";
			link.l1.go = "Isabella_Sink_1";
		break;
		case "Isabella_Sink_1":
			dialog.text = "What, your Isabella wasn't there?";
			link.l1 = "She was, but she didn't believe me. And I couldn't pick her up from the sinking ship, she preferred to go down with the brig. That's it, Attila...";
			link.l1.go = "Brig_Late_2";
		break;
		// узнать что-нибудь новое о Сальватора
		case "SalvatorNews":
			dialog.text = "Who do I see?! " + GetFullName(pchar) + ", in person!";
			link.l1 = "Hello, Atilla! How are you, buddy?";
			link.l1.go = "SalvatorNews_1";
		break;
		case "SalvatorNews_1":
			dialog.text = "I'm fine. How are you doing?";
			link.l1 = "With varying success. I can't find Salvator, I just run into his henchmen.";
			link.l1.go = "SalvatorNews_2";
		break;
		case "SalvatorNews_2":
			dialog.text = "I see...";
			link.l1 = "Listen, have you heard anything about him yourself?";
			link.l1.go = "SalvatorNews_3";
		break;
		case "SalvatorNews_3":
			dialog.text = "There is little concrete. He hires all the rabble in the dens, pays them for their work, but he disappears. It's hard to catch him.";
			link.l1 = "Hmm, yeah... I don't know what to do.";
			link.l1.go = "SalvatorNews_4";
		break;
		case "SalvatorNews_4":
			dialog.text = "Go to Belize and look for him there.";
			link.l1 = "Why Belize?";
			link.l1.go = "SalvatorNews_5";
		break;
		case "SalvatorNews_5":
			dialog.text = "Because Salvator went there. That's the last I heard about him just a couple of days ago.";
			link.l1 = "The Devil! I took Isabella to Belize!!!";
			link.l1.go = "SalvatorNews_6";
		break;
		case "SalvatorNews_6":
			dialog.text = "Ah, well, now it's clear what he needed there. I wouldn't waste any time if I were you...";
			link.l1 = "I won't... Goodbye, Atilla, thanks for the help!";
			link.l1.go = "exit";
			NextDiag.TempNode = "AtillaInHouse_Again";
			AddQuestRecord("Romantic_Line", "20");
			ChangeCharacterAddress(characterFromId("Isabella"), "none", "");
			QuestSetCurrentNode("Rosita", "BackRosita");
			//Изабеллу в шахту
			sld = characterFromId("Isabella");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_Cave_2", "goto", "goto5");
			sld.dialog.currentnode = "IsabellaInCave";
		break;
		//Изабелла убита в церкви.
		case "IsabellaIsDead":
			dialog.text = "Oh, captain " + GetFullName(pchar) + ". How are you, buddy?";
			link.l1 = "Attila, I lost Isabella...";
			link.l1.go = "IsabellaIsDead_1";
		break;
		case "IsabellaIsDead_1":
			dialog.text = "What happened?";
			link.l1 = "I killed Salvator and we were supposed to marry Isabella in San Juan. At the ceremony, a crowd of thugs broke into the church, and they killed her... Salvator hired them when he was still alive.";
			link.l1.go = "IsabellaIsDead_2";
		break;
		case "IsabellaIsDead_2":
			dialog.text = "Mmm, I'm sorry. But what can be done? We have to move on somehow...";
			link.l1 = "Yes, Atilla, that's right...";
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "IsabellaIsDead_after";
			CloseQuestHeader("Romantic_Line");
			pchar.questdata.IstoriyaIzabely = 1;
		break;
		case "IsabellaIsDead_after":
			dialog.text = "Oh, Atilla, how hard it is for me...";
			link.l1 = "I understand, buddy...";
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsDead_after";
			npchar.lifeDay = 0;
		break;
		//если ГГ отбился в церкви
		case "IsabellaIsMyWife":
			dialog.text = "Hello, buddy! How are you?";
			link.l1 = "Life is beautiful, Atilla! Everything is great! Isabella and I got married, and now I'm married.";
			link.l1.go = "IsabellaIsMyWife_1";
			npchar.lifeDay = 0;
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = "Congratulations, this is a good thing. Otherwise, the life of a pirate is not very long, you need to stop in time...";
			link.l1 = "Yes, that's right. Isabella got married on the condition that I quit privateering.";
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = "Well, maybe it's true, buddy...";
			link.l1 = "Probably, yes, Atilla. Well, goodbye...";
			link.l1.go = "exit";
			link.l2 = "Atilla, here's the deal... I want to thank you for everything.";
			link.l2.go = "IsabellaIsMyWife_3";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
			pchar.RomanticQuest.Atilla = "YouAreBaster";
			npchar.LifeDay = 0;
		break;
		case "IsabellaIsMyWife_after":
			dialog.text = "Cap again " + pchar.name + " he came. What do you want from Attila this time?";
			link.l1 = "Nothing special, just dropped by, buddy...";
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		case "IsabellaIsMyWife_3":
			dialog.text = "For what exactly?";
			link.l1 = "Well, for your help, how many times have you helped me out! Anyway, I met Isabella on your tip, so to speak...";
			link.l1.go = "IsabellaIsMyWife_4";
		break;
		case "IsabellaIsMyWife_4":
			dialog.text = "Heh, I won't refuse, buddy...";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "Well, then accept a thousand coins, Atilla!";
				link.l1.go = "AddRepa_1";
			}
			if (sti(pchar.money) >= 70000)
			{
				link.l2 = "I've prepared 70,000 coins for you.";
				link.l2.go = "AddRepa_2";
			}
			if (sti(pchar.money) >= 150000)
			{
				link.l3 = "Your share in this case is 150,000 coins.";
				link.l3.go = "AddRepa_3";
			}
			if (sti(pchar.money) >= 300000)
			{
				link.l4 = "Your share in this case is 300,000 coins.";
				link.l4.go = "AddRepa_4";
			}
		break;
		case "AddRepa_1":
			dialog.text = "I surprised, " + pchar.name + "... Well, thanks for that, too. They don't look a gift horse in the mouth, as they always do...";
			link.l1 = "You're welcome, buddy! Be healthy...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			ChangeCharacterReputation(pchar, -10);
		break;
		case "AddRepa_2":
			dialog.text = "Well, that's great! I am grateful to you, " + GetFullName(pchar) + ".";
			link.l1 = "It's okay, Atilla. Be healthy...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -70000);
			pchar.RomanticQuest.Atilla = "YouAreNormal";
			ChangeCharacterReputation(pchar, 5);
		break;
		case "AddRepa_3":
			dialog.text = "Oh, great! Even though I didn't really strain myself...";
			link.l1 = "Atilla, you may not have strained too much, but all your efforts were very much to the point! Be healthy...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -150000);
			pchar.RomanticQuest.Atilla = "YouAreNormal";
			ChangeCharacterReputation(pchar, 15);
		break;
		case "AddRepa_4":
			dialog.text = "Oh, damn me!! That's a lot of money!"+
				          "Well, thanks, buddy, I made friends - so I made friends. I'm going to buy myself a nicer kennel now... No, I'll probably go back to the Old World, I stayed here too long...";
			link.l1 = "Do as you like, buddy! Be healthy...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -300000);
			pchar.RomanticQuest.Atilla = "YouAreGood";
			ChangeCharacterReputation(pchar, 30);
		break;
	}
}
