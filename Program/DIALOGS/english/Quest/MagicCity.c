
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Nothing to talk about.";
			link.l1 = "Okay...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_orient":
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
                LAi_ActorStay(sld);
			}
			LAi_ActorTurnByLocator(npchar, npchar.location.group, npchar.location.locator);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = "In Des Moines, you shouldn't walk around with a naked weapon.";
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "DesMoinesCitizen";
		break;

		//бунтующие горожане в Каракасе
		case "CaracasMan":
			dialog.text = "Hey, "+ GetSexPhrase("sailor","girl") +"! Do you want to participate too? You're welcome!";
			link.l1 = "Maybe I will participate if you tell me what it is.";
			link.l1.go = "CaracasMan_1";
		break;
		case "CaracasMan_1":
			dialog.text = "Yes, there is a werewolf here in the tavern. Here, we want to heat it up-hic!-on a campfire, haha!";
			link.l1 = "You're drunk, buddy! Go sleep it off!";
			link.l1.go = "CaracasMan_2";
		break;
		case "CaracasMan_2":
			dialog.text = "Pop my eyes if I'm lying! And I drank, so for courage and on my own! Do you meet a werewolf every day?";
			link.l1 = "Werewolf, you say? Well, then why are you standing here? Burn him!";
			link.l1.go = "CaracasMan_3";
		break;
		case "CaracasMan_3":
			dialog.text = "So the tavern owner, the rascal, locked himself in! Here are the guys behind the log- ik! - let's go, break down the door!";
			link.l1 = "Eh, you'll blow up half the city here with drunken eyes! Come on, let me through, I'll find out who the werewolf is. And if anyone comes after me, I'll cut off my ears!";
			link.l1.go = "exit_orient";
			DeleteAttribute(&locations[reload_location_index], "reload.l41.disable");
		break;
		//оборотень в Каракасе
		case "CaracasWervolf":
			dialog.text = "Who are you and what do you need?";
			link.l1 = "I am the captain " + GetFullName(pchar) + ". But who are you? There, on the street, a few determined guys are going to visit you, and it's unlikely that they are going to present gifts for Christmas.";
			link.l1.go = "CaracasWervolf_1";
		break;
		case "CaracasWervolf_1":
			dialog.text = "They're going to burn me! But God knows I'm innocent! I fled from Maracaibo, from a terrible curse that fell on all the inhabitants of our city. Captain! You can help me. I need to confess!";
			link.l1 = "Wrong address, my dear. I'm not a priest.";
			link.l1.go = "CaracasWervolf_2";
		break;
		case "CaracasWervolf_2":
			dialog.text = "But you can bring a priest here, right?";
			link.l1 = ""+ GetSexPhrase("I have destroyed so many souls that I will probably get help in saving at least one.","Good.") +" Wait here, try to hold out!";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			pchar.questTemp.MC = "toCaracasPadre";
			iTemp = FindLocation("Caracas_tavern");
			DeleteAttribute(&locations[iTemp], "reload.l1.disable");
			DeleteAttribute(&locations[iTemp], "reload.l4.disable");
			LocatorReloadEnterDisable("Caracas_town", "reload7_back", false);
			locations[iTemp].reload.l2.disable = true;
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
				sld.dialog.currentnode = "CaracasMan2";
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorWaitDialog(sld, pchar);
			}
		break;
		//горожане Каракаса на выходе из таверны
		case "CaracasMan2":
			dialog.text = "Well, what? Did the werewolf escape?";
			link.l1 = "That's what, you should go home! There is no werewolf there!";
			link.l1.go = "exit_orient";
		break;
		//охрана Дес-Мойнеса в бухте
		case "ShoreGuard":
			dialog.text = "Hey, you! We don't need outsiders here. Get out of here!";
			link.l1 = "Maybe a hundred yellow chubby chickens will teach you to cackle more politely?";
			link.l1.go = "ShoreGuard_1";
		break;
		case "ShoreGuard_1":
			dialog.text = "How would you like it"+ GetSexPhrase("you didn't crow yourself, cockerel","you didn't cackle yourself, chicken") +"! If you don't turn back with kindness, we'll make you!";
			link.l1 = "And who can forbid me to go where I want?";
			link.l1.go = "ShoreGuard_2";
		break;
		case "ShoreGuard_2":
			dialog.text = "Three inches of steel between the ribs!";
			link.l1 = "Well, let's compare whose steel is better?";
			link.l1.go = "ShoreGuard_3";
		break;
		case "ShoreGuard_3":
			LocatorReloadEnterDisable("DesMoines_port", "gate_back", false);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("MagicCity", "3");
			DialogExit();
		break;
		//жители Дес-Мойнеса обычные
		case "DMCitiz":
			NextDiag.TempNode = "DMCitiz";
			dialog.text = LinkRandPhrase("What do you need in our city?", "Guests in our city appear very rarely. And what did you want?", "I would not say that we are glad to welcome you. What do you need in Des Moines?");
			link.l1 = "See how you live...";
			link.l1.go = "DesMoinesCitizen_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = LinkRandPhrase("Damn you! Leave while you can still do it...", "Come on, run away from here, coward...", "Get out of here! And don't let me see you here anymore...");
				link.l1 = "Required!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister" || pchar.questTemp.MC == "toSeekSkull" || pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = LinkRandPhrase("They say you agreed to help us. Good luck to you, captain...", "God bless you, "+ GetSexPhrase("senor captain","senorita") +"!", "How I wish that everything worked out for you!");
				link.l1 = "Required!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = ""+ GetSexPhrase("Senor, you are our savior","Senorita, you are our savior") +"! May the Lord protect you!";
				link.l1 = "Thank you. Touched by, touched by...";
				link.l1.go = "exit";
			}
		break;
		case "DesMoinesCitizen_1":
			dialog.text = "Everything is fine.";
			link.l1 = "Well, great!";
			link.l1.go = "DesMoinesCitizen_2";
		break;
		case "DesMoinesCitizen_2":
			dialog.text = "I do not advise you to stay with us. Our town is not very hospitable...";
			link.l1 = "Hmm... well, that's how it turns out.";
			link.l1.go = "exit";
		break;
		//жители Дес-Мойнеса скелеты
		case "DMSkel":
			NextDiag.TempNode = "DMSkel";
			dialog.text = LinkRandPhrase("The curse has fallen on us!", "Our city is cursed!", "Do you see what is happening to us? What a terrible misfortune!");
			link.l1 = "Yeah...";
			link.l1.go = "DesMoinesSkel_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = LinkRandPhrase("Damn you! Leave while you can still do it...", "Come on, run away from here, coward...", "Get out of here! And don't let me see you here anymore...");
				link.l1 = "Required!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister" || pchar.questTemp.MC == "toSeekSkull" || pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = LinkRandPhrase("They say you agreed to help us. Good luck to you, captain...", "God bless you, "+ GetSexPhrase("senor captain","senorita") +"!", "How I wish that everything worked out for you!");
				link.l1 = "Required!";
				link.l1.go = "exit";
			}
		break;
		case "DesMoinesSkel_1":
			dialog.text = "Since you've seen this whole nightmare, then go to our head, Fernando Torres. Be sure to talk to him.";
			link.l1 = "Okay.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("DesMoines_town", "reload1_back", true);
		break;
		//глава городка обычный
		case "DMCitizHead":
			NextDiag.TempNode = "DMCitizHead";
			dialog.text = "Hello. Why did you come to Des Moines?";
			link.l1 = "Just to see what's what... Tell me, is everything okay in the city?";
			link.l1.go = "DMCitizHead_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = "Go away! I don't want to deal with you.";
				link.l1 = "Hmm... well, for nothing.";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister")
			{
				dialog.text = ""+ GetSexPhrase("Senor capitan","Senorita") +" as soon as you learn something new, please notify me immediately. In fact, you are our last hope for a normal life.";
				link.l1 = "I will do my best to remove this terrible curse. Hope!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSkull")
			{
				dialog.text = "Hello, Captain! What do you say?";
				link.l1 = "I found Elizabeth Sheppard.";
				link.l1.go = "FoundLiz";
			}
			if (pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = "Hello, Captain! What do you say?";
				link.l1 = "I started search of the galleon 'Queen'. It looks like this is the last step towards your release.";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = "Did you lift the curse? At some point, everything went back to normal!";
				link.l1 = "Yes. I found the galleon 'Queen' and did everything needed. I am glad that I helped you.";
				link.l1.go = "DMHeadOver";
			}
			if (CheckAttribute(pchar, "questTemp.MC.DesMoines"))
			{
				dialog.text = ""+ GetSexPhrase("Senior","Seniorita") +", our savior! Did you want something?";
				link.l1 = "No, nothing special...";
				link.l1.go = "exit";
			}
		break;
		case "DMCitizHead_1":
			dialog.text = "Everything is fine. Why are you asking?";
			link.l1 = "You know when I dropped off at the port, I was attacked by some people. It's completely unclear why.";
			link.l1.go = "DMCitizHead_2";
		break;
		case "DMCitizHead_2":
			dialog.text = "I can't tell you anything about this. I don't know who it was.";
			link.l1 = "Understood... So, you say everything is calm in Des Moines.";
			link.l1.go = "DMCitizHead_3";
		break;
		case "DMCitizHead_3":
			dialog.text = "Absolutely correct.";
			link.l1 = "Well, I see. I'm sorry...";
			link.l1.go = "exit";
		break;

		case "FoundLiz":
			dialog.text = NPCStringReactionRepeat("Great! And what did you find out?",
				"We've already talked about this, Captain.",
				"Captain, we've already talked about this.",
                "Captain, how much can I do?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Elizabeth doesn't know how or why this curse was cast. But she found out how to take it off.",
				"Yes, I remember.",
                "Yes, of course...",
				"I am so persistent. I think I'll keep asking the same thing - maybe a miracle will happen! The spell will fall off, or something else...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FoundLiz_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "FoundLiz_1":
			dialog.text = "My God, Captain! Hope takes the shape of reality! Tell me quickly, how to do it?";
			link.l1 = "Using the jade skull of the Aztecs. We need to get it, and Elizabeth will tell us what to do next.";
			link.l1.go = "FoundLiz_2";
		break;
		case "FoundLiz_2":
			dialog.text = "Captain, please do your best.";
			link.l1 = "That's what I'm doing.";
			link.l1.go = "exit";
		break;

		case "DMHeadOver":
			dialog.text = "Thank you very much! On behalf of our citizens, I am pleased to inform you that we have prepared a reward for your efforts.";
			link.l1 = "What's the reward?";
			link.l1.go = "DMHeadOver_1";
		break;
		case "DMHeadOver_1":
			dialog.text = "Twenty thousand piastres! It may not be much for you, but our city has become very poor in a damn while, so this is all we have.";
			link.l1 = "Come on, keep this money for yourself. You need them more now.";
			link.l1.go = "DMHeadOver_2";
			link.l2 = "I accept your money.";
			link.l2.go = "DMHeadOver_3";
			
			AddQuestRecord("MagicCity", "9");
			CloseQuestHeader("MagicCity");
			pchar.questdata.ZacharovanyGorod = 1;
			pchar.questTemp.MC.DesMoines = true;
			SetTimerFunction("MC_DesMoinesVozrojdenie", 0, 0, 7);
		break;
		case "DMHeadOver_2":
			dialog.text = "Thanks again. Honestly, I didn't expect...";
			link.l1 = "You're welcome. Live happily ever after.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 10);
		break;
		case "DMHeadOver_3":
			dialog.text = "Great! Well, all the best to you, "+ GetSexPhrase("senor","senorita") +".";
			link.l1 = "And all the best to you.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
		break;

		//глава городка скелет
		case "DMSkelHead":
			NextDiag.TempNode = "DMSkelHead";
			dialog.text = "I've already forgotten when I saw a living person in the middle of the night, not a vile skeleton!";
			link.l1 = "Mother of God, you have a funny place here! For God's sake, what's going on here?";
			link.l1.go = "DMSkelHead_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = "Go away! I don't want to deal with you.";
				link.l1 = "Hmm... well, for nothing.";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister")
			{
				dialog.text = ""+ GetSexPhrase("Senor capitan","Senorita") +" as soon as you learn something new, please notify me immediately. In fact, you are our last hope for a normal life.";
				link.l1 = "I will do my best to remove this terrible curse. Hope!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSkull")
			{
				dialog.text = "Hello, Captain! What do you say?";
				link.l1 = "I found Elizabeth Sheppard.";
				link.l1.go = "FoundLiz";
			}
			if (pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = "Hello, Captain! What do you say?";
				link.l1 = "I stated search of the galleon 'Queen'. It looks like this is the last step towards your release.";
				link.l1.go = "exit";
			}
		break;
		case "DMSkelHead_1":
			dialog.text = "I'll tell you if you want it! You won't get far with this story anyway.";
			link.l1 = "I'm not one of the timid ones, so there's nothing to scare me. Tell me.";
			link.l1.go = "DMSkelHead_2";
		break;
		case "DMSkelHead_2":
			dialog.text = "One day the pirate galleon 'Queen' docked at our cape. Pirates sold slaves to smugglers here. They agree among themselves.... "+
				"The pirates sold the slaves, and then they had some kind of quarrel with each other. Some of the crew stayed here, and the rest went to sea with the captain on the galleon. That's when it all started.";
			link.l1 = "Yes, what started? You're talking straight!";
			link.l1.go = "DMSkelHead_3";
		break;
		case "DMSkelHead_3":
			dialog.text = "Yes, that's what you see. During the day, all people are like people, but as the sun sets, this is such a masquerade. They realized that it was all because of these pirates, damn them! And even though they also turned into skeletons at night, but all the same - everyone who stayed with us was sent to the bonfire one fine night. It didn't help...";
			link.l1 = "Yeah, it's a sad story...";
			link.l1.go = "DMSkelHead_4";
		break;
		case "DMSkelHead_4":
			dialog.text = "So, Captain, you know our secret and our grief. Do you understand that from now on you will have to share them with us?";
			link.l1 = "What do you mean?";
			link.l1.go = "DMSkelHead_5";
		break;
		case "DMSkelHead_5":
			dialog.text = "In the sense that you are not allowed to leave Des Moines. No one needs publicity.";
			link.l1 = "My plans do not include staying here.";
			link.l1.go = "DMSkelHead_6";
		break;
		case "DMSkelHead_6":
			dialog.text = "You were honestly not allowed here by the guards at the port. But you broke through to us anyway. So blame only yourself.";
			link.l1 = "I do not advise you to try to hold me by force. I broke through guards here, and I'll get out of here anyway...";
			link.l1.go = "DMSkelHead_7";
		break;
		case "DMSkelHead_7":
			dialog.text = "Perhaps that's right, but no one will hold you by force. No one will believe your stories anyway, and if they do, they will send the Inquisition with a hundred soldiers... and the life of the whole city will be on your conscience. However, it seems that you are not used to it...";
			link.l1 = "Damn, you're right. Is there anything I can do to help?";
			link.l1.go = "DMSkelHead_8";
			link.l2 = "You are absolutely right, Mr. Mayor. What do I care about you and your town? Have pleasant dreams!";
			link.l2.go = "DMSkelHead_bye";
			LocatorReloadEnterDisable("DesMoines_town", "reload1_back", false); //выпускаем из города
		break;

		case "DMSkelHead_bye":
			dialog.text = "The same to you, dear captain.";
			link.l1 = "Bye. Don't get bored...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -20);
			AddQuestRecord("MagicCity", "4");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("","a"));
			AddQuestUserData("MagicCity", "sSex1", GetSexPhrase("ate","la"));
			pchar.questTemp.MC = "toByeBye"; //флаг квеста
		break;

		case "DMSkelHead_8":
			dialog.text = "Lifting the curse is our dream. The trouble is, we don't even know what's going on.";
			link.l1 = "Bad... Maybe he should try to find this galleon on which the pirates left? It looks like this is the only lead.";
			link.l1.go = "DMSkelHead_9";
		break;
		case "DMSkelHead_9":
			dialog.text = "You know, recently a girl came to our city, Elizabeth Sheppard, I think her name was. So, this young lady hired a tartan on Maracaibo, sailed to us and persuaded the guards to let her come to me.";
			link.l1 = "So what?";
			link.l1.go = "DMSkelHead_10";
		break;
		case "DMSkelHead_10":
			dialog.text = "She was trying to find out in detail what happened that night among the pirates. I asked her why she needed it, but she turned out to be something else! She didn't say anything.";
			link.l1 = "And you let her go?";
			link.l1.go = "DMSkelHead_11";
		break;
		case "DMSkelHead_11":
			dialog.text = "Released. She didn't see us in this monstrous image.So that's what I'm telling you about. The more time passes since our conversation, the more I am convinced that Miss Elizabeth Sheppard knows something.";
			link.l1 = "Is she English?";
			link.l1.go = "DMSkelHead_12";
		break;
		case "DMSkelHead_12":
			dialog.text = "Without a doubt. I admit that I made a mistake by letting her go on all fours. I had to find out everything she knew.Now I ask you to find her and find out everything she knows about these damned pirates and the galleon Queen.";
			link.l1 = "Okay, I'll do that.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 5);
			AddQuestRecord("MagicCity", "5");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("xia","as"));
			pchar.questTemp.MC = "toSeekSister"; //флаг квеста
			LocatorReloadEnterDisable("Charles_town", "housePirate", false);
			//ставим Лиз Шеппард
			sld = GetCharacter(NPC_GenerateCharacter("LizSheppard", "BaynesDaughterSTOK", "woman", "towngirl", 10, ENGLAND, -1, false));
			sld.name = "Elizabeth";
			sld.lastname = "Sheppard";
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "LizBegin";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Charles_PirateHouse", "goto", "goto1");
		break;
		//Элизабет Шеппард
		case "LizBegin":
			dialog.text = "Hello, Captain. To what do I owe the pleasure of seeing you at home?";
			link.l1 = "Hello, Elizabeth. My name is " + GetFullName(pchar) + ". I came to talk to you about one thing... a very unusual case.";
			link.l1.go = "LizBegin_1";
		break;
		case "LizBegin_1":
			dialog.text = "I'm listening to you carefully, Captain.";
			link.l1 = "Some time ago you visited a small Spanish settlement - Des Moines. The head of this small town, Fernando Torres, whom I believe you are familiar with, asked me to find you. Which I gladly did.";
			link.l1.go = "LizBegin_2";
		break;
		case "LizBegin_2":
			dialog.text = "You surprised me, Captain. Go on.";
			link.l1 = "Fernando is asking for your help.";
			link.l1.go = "LizBegin_3";
		break;
		case "LizBegin_3":
			dialog.text = "How can I help?";
			link.l1 = "Help me find the galleon 'Queen'.";
			link.l1.go = "LizBegin_4";
		break;
		case "LizBegin_4":
			dialog.text = "Why does he need this galleon?";
			link.l1 = "The fact is, young lady, that the residents of the city associate with this galleon... the emergence of a sudden epidemic that struck the city.";
			link.l1.go = "LizBegin_5";
		break;
		case "LizBegin_5":
			dialog.text = "Has the curse overtaken the inhabitants of Des Moines?!";
			link.l1 = "Yes, it is. So you know about the curse?";
			link.l1.go = "LizBegin_6";
		break;
		case "LizBegin_6":
			dialog.text = "Of course I know! The fact is that the captain of the Queen galleon is a very dear person to me. Lately, all I've been doing is trying to solve this tangle and break the devil's spell.";
			link.l1 = "Is it working?";
			link.l1.go = "LizBegin_7";
		break;
		case "LizBegin_7":
			dialog.text = "Partly. The fact is that I am the daughter of a famous man among pirates. My father, Captain Staton, was Edward Mansfield's closest associate!";
			link.l1 = "Oh, that's very decent, miss...";
			link.l1.go = "LizBegin_8";
		break;
		case "LizBegin_8":
			dialog.text = "So, having no other choice, I turned to Jackman for help. I hope you know who this is?";
			link.l1 = "Of course!";
			link.l1.go = "LizBegin_9";
		break;
		case "LizBegin_9":
			dialog.text = "What the pirates learned from the Indian slaves only caused the corsairs to laugh in unison. But I'm not joking, I've seen it with my own eyes!..";
			link.l1 = "I saw it too, Elizabeth. Walking and talking human skeletons are an unpleasant sight. So what did my colleagues learn from the Indians?";
			link.l1.go = "LizBegin_10";
		break;
		case "LizBegin_10":
			dialog.text = "Only an Aztec god of the dead named Mictlantecutli could have done this.";
			link.l1 = "Oh... Well, what should I do now?";
			link.l1.go = "LizBegin_11";
		break;
		case "LizBegin_11":
			dialog.text = "We need to get a jade skull, an artifact of this god. Only with his help can the curse be lifted.";
			link.l1 = "And where do you think it is?";
			link.l1.go = "LizBegin_12";
		break;
		case "LizBegin_12":
			dialog.text = "In the lost city of the Aztecs.";
			link.l1 = "Elizabeth, so what happened at the port? Why did this curse fall on the people of Des Moines?";
			link.l1.go = "LizBegin_13";
		break;
		case "LizBegin_13":
			dialog.text = "I do not know. One night, more than a year ago, I heard someone enter the house. I went downstairs and saw a decayed skeleton. It was terrible. I screamed. The skeleton also screamed and ran away. It was only then that I realized it was the captain of the Queen. And I scared him away!";
			link.l1 = "You know, miss, you are a girl of rare composure. Most young ladies in your place would get a heartbreak from fear.";
			link.l1.go = "LizBegin_14";
		break;
		case "LizBegin_14":
			dialog.text = "Nevertheless, I pushed away a person close to me. Then I firmly decided that I would find out about the misfortune that befell the captain of the Queen and free him!";
			link.l1 = "Damn it, how romantic! It's lucky for the poor guy that he has such a loyal girlfriend.";
			link.l1.go = "LizBegin_15";
		break;
		case "LizBegin_15":
			dialog.text = "Captain, I ask you to be very correct in expressions. Don't forget whose daughter is standing in front of you!Now that it has become clear that you are doing essentially the same thing, I want to ask you to get the jade skull of the god of the dead. I can't do it, as you know.";
			if (CheckCharacterItem(pchar, "SkullAztec"))
			{
				link.l1 = "I already have this skull, Elizabeth.";
				link.l1.go = "LizBegin_haveSkull";
			}
			else
			{
				link.l1 = "Well, young lady, I'm ready todo it, at least in memory of your father. So you're saying that this skull is in an Indian town?";
				link.l1.go = "LizBegin_seekSkull";
			}
		break;

		case "LizBegin_SeekSkull":
			dialog.text = "That's right. In the abandoned Aztec capital of Tenochtitlan.";
			link.l1 = "Understood. If I manage to get this skull, then I'll go here to Charlestown first.";
			link.l1.go = "LizBegin_16";
			ChangeCharacterReputation(pchar, 3);
		break;
		case "LizBegin_16":
			dialog.text = "Okay, Captain, I'll be waiting for you. Thank you.";
			link.l1 = "You're welcome...";
			link.l1.go = "exit";
			AddQuestRecord("MagicCity", "6");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("ate","la"));
			AddQuestUserData("MagicCity", "sSex1", GetSexPhrase("xia","as"));
			pchar.questTemp.MC = "toSeekSkull"; //флаг квеста
			NextDiag.TempNode = "LizCheckSkull";
		break;

		case "LizBegin_haveSkull":
			dialog.text = "How did you manage to get it?!";
			link.l1 = "It's a long story... Tell me what to do next.";
			link.l1.go = "LizCheckSkull_1";
		break;
		//проверка черепа
		case "LizCheckSkull":
			dialog.text = "Did you bring the jade skull, Captain?";
			if (CheckCharacterItem(pchar, "SkullAztec"))
			{
				link.l1 = "I have it, Elizabeth.";
				link.l1.go = "LizCheckSkull_Ok";
			}
			else
			{
				link.l1 = "Not yet. But I'm on this case.";
				link.l1.go = "exit";
			}
		break;
		case "LizCheckSkull_Ok":
			dialog.text = "You managed to get it after all!";
			link.l1 = "It wasn't easy, I'll tell you... What should I do now, miss?";
			link.l1.go = "LizCheckSkull_1";
		break;
		case "LizCheckSkull_1":
			dialog.text = "Now we have a tool to remove the curse. You need to find the galleon 'Queen' and, in fact, remove the curse from the captain.";
			link.l1 = "The Aztec god of the dead, the one who gave me the jade skull, said among other things that the skull is able to help the cursed living. But he didn't explain how to help...";
			link.l1.go = "LizCheckSkull_2";
		break;
		case "LizCheckSkull_2":
			dialog.text = "I suppose we just need to deliver the skull to the cabin of the captain of the Queen'. In that case, the curse should disappear on its own.";
			link.l1 = "Maybe... And where can I find this galleon?";
			link.l1.go = "LizCheckSkull_3";
		break;
		case "LizCheckSkull_3":
			dialog.text = "I don't know. Most likely, the captain wanders the sea far from the cities. Take a closer look around, you definitely won't miss this galleon.";
			link.l1 = "Clear. Well, I'll do the search.";
			link.l1.go = "exit";
			SetDanielleInWorld();
			AddQuestRecord("MagicCity", "7");
			pchar.questTemp.MC = "toSeekQueen"; //флаг квеста
			NextDiag.TempNode = "LizSeekQueen";
		break;
		case "LizSeekQueen":
			dialog.text = "Captain, have you found the galleon 'Queen'?";
			link.l1 = "Not yet...";
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = "You've lifted the curse after all!";
				link.l1 = "Yes, I succeeded.";
				link.l1.go = "LizOver";
			}
		break;

		case "LizOver":
			dialog.text = "God, I'm so glad for my sister!";
			link.l1 = "By the way, Elizabeth, why didn't you tell me right away that the person you care about is your sister?";
			link.l1.go = "LizOver_1";
		break;
		case "LizOver_1":
			dialog.text = "Just in case...";
			link.l1 = "Understood. You are your father's daughter, it shows... By the way, Danielle joined me as an officer.";
			link.l1.go = "LizOver_2";
		break;
		case "LizOver_2":
			dialog.text = "Very good. I think that you will be able to take care of her, otherwise she completely lost her sense of proportion in corsair prowess.";
			link.l1 = "Well, I'll try.";
			link.l1.go = "LizOver_3";
		break;
		case "LizOver_3":
			dialog.text = "By the way, Captain, before you leave, I would like to thank you with something. I thought about it and decided to give you the thing that I got from my father. This is an ancient amulet called 'Janissary'. According to rumors, the owner of such a talisman makes the team much more obedient. I hope he will be of more use to you than to me.";
			link.l1 = "Wow, aren't you sorry to part with such a thing, miss? Well, I will gladly accept your gift!";
			Log_Info("You have received a talisman");
			AddItems(pchar, "talisman4", 1);
			link.l1.go = "LizOver_4";
		break;
		case "LizOver_4":
			dialog.text = "Perhaps that's all. Goodbye, Captain!";
			link.l1 = "Goodbye, Elizabeth.";
			link.l1.go = "exit";
			npchar.lifeDay = 30;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			NextDiag.TempNode = "LizOver_end";
		break;
		case "LizOver_end":
			dialog.text = "Did you want something, Captain?";
			link.l1 = "No, nothing special...";
			link.l1.go = "exit";
		break;
		//Даниэль на абордаже
		case "DanAbordage":
			dialog.text = "I'm going to bleed you now!";
			link.l1 = "Hey lady, what's up?! Let's talk, why are you rushing at me like an angry fury?!";
			link.l1.go = "DanAbordage_1";
		break;
		case "DanAbordage_1":
			dialog.text = "We have nothing to talk about. You attacked my galleon!";
			link.l1 = "I needed to get into the captain's cabin, I had no other option!.. Wait, is this galleon yours?";
			link.l1.go = "DanAbordage_2";
		break;
		case "DanAbordage_2":
			dialog.text = "Mine has been for five years.";
			link.l1 = "So you are the person dear to Elizabeth's heart... And I was thought that she was talking about a man!";
			link.l1.go = "DanAbordage_3";
		break;
		case "DanAbordage_3":
			dialog.text = "Do you know my sister Elizabeth?";
			link.l1 = "It is on her behalf that I am here now. And you, as I understand it, are her older sister Danielle Sheppard?";
			link.l1.go = "DanAbordage_4";
		break;
		case "DanAbordage_4":
			dialog.text = "Exactly! Let me ask you, who are you?";
			link.l1 = "My name is captain " + GetFullName(pchar) + ". I was looking for your galleon to break the curse. Tell me how it happened that the curse of the Aztec god of the dead fell on you.";
			link.l1.go = "DanAbordage_5";
		break;
		case "DanAbordage_5":
			dialog.text = "So that's who it was! And I still didn't know what kind of scarecrow it was in the Des Moines, in Maracaibo Bay. You probably know that I am Captain Staton's daughter. Despite the fact that I am a woman, I managed to defend my right to be the captain of the Queen.. "+
				"Once in Bermudes, I hired a skipper named Pierre Cabal. It was a mistake, the world has never seen such a scoundrel. Off the coast of Santa Catalina, he grabbed a young Indian. Unfortunately, I found out about it when we were already approaching Maracaibo. The scoundrel decided to sell it and take the money for himself. He motivated this by the fact that the Indian is personally his legitimate prey.. "+
				"It is clear that I could not allow such lawlessness. At Des Moines, at the time of the deal, I stated that either we were selling the Indian on a general basis, or I was letting him go. In the end, I had to let go. But that scoundrel Cabal pulled out a pistol and shot the Indian in the back. It seemed that our duel was imminent.. "+
				"However, fate decreed otherwise. As soon as the Indian fell into the grass with a groan, a terrible stuffed animal in feathers appeared out of nowhere, grabbed the dead Indian, and announced in a thunderous voice that my team and I were now cursed. And it disappeared.";
			link.l1 = "I recognize Mictlantecutli in person.";
			link.l1.go = "DanAbordage_6";
		break;
		case "DanAbordage_6":
			dialog.text = "Everyone stood as if thunderstruck. There was no question of any duel. But it was also impossible to take Cabal aboard the galleon. Therefore, I went to sea with most of the crew. Only those who sympathized with Pierre remained.";
			link.l1 = "And then you realized that the curse is not a joke..";
			link.l1.go = "DanAbordage_7";
		break;
		case "DanAbordage_7":
			dialog.text = "The same night. Imagine our horror!";
			link.l1 = "I imagine. By the way, the curse has fallen not only on you, but also on the people of Des Moines.";
			link.l1.go = "DanAbordage_8";
		break;
		case "DanAbordage_8":
			dialog.text = "That's the devil!";
			link.l1 = "You are lucky, Daniel, that Elizabeth recognized you in the skeleton that came to her at night. And she began to act.";
			link.l1.go = "DanAbordage_10";
		break;
		case "DanAbordage_10":
			dialog.text = "Baby Elizabeth! Yes, there is a reason to be proud of your sister, so, Captain, if you have come to remove the curse, then do it!";
			link.l1 = "It looks like the job is already done. I needed to deliver the jade skull of Mictlantecutli closer to the captain of the galleon 'Queen', which I did .";
			link.l1.go = "DanAbordage_11";
		break;
		case "DanAbordage_11":
			dialog.text = "Has the curse been lifted? Am I not going to become a skeleton anymore?";
			link.l1 = "I think not. It's over.";
			link.l1.go = "DanAbordage_12";
		break;
		case "DanAbordage_12":
			dialog.text = "Captain, how can I thank you for the service rendered?";
			link.l1 = "Thank your sister... Although, you know, I have a business proposal for you - come to me as an officer. I am "+ GetSexPhrase("pirate","the same corsair woman") +", just like you. I guess we'll work together.";
			link.l1.go = "DanAbordage_13";
		break;
		case "DanAbordage_13":
			dialog.text = "Well, why not? I agree.";
			link.l1 = "Great!";
			link.l1.go = "DanAbordage_14";
		break;
		case "DanAbordage_14":
			//чистим базу нпс-кэпов  -->
			DeleteAttribute(NullCharacter, "capitainBase.Danielle");
			//<-- чистим базу нпс-кэпов
			AddQuestRecord("MagicCity", "8");
			pchar.questTemp.MC = "over"; //флаг квеста
			sld = GetCharacter(NPC_GenerateCharacter("DanielleOff", "Danielle", "woman", "Danielle", 25, PIRATE, -1, true));
			sld.name = "Daniel";
			sld.lastname = "Sheppard";
			sld.greeting = "Gr_Danielle";
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			SetSelfSkill(sld, 90, 60, 30, 60, 90);
			SetShipSkill(sld, 80, 20, 75, 75, 80, 20, 70, 60, 70);
			SetSPECIAL(sld, 6, 9, 9, 10, 8, 8, 10);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.HalfImmortal = true;  // Контузия
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle();
            DialogExit();
		break;
		
		case "Man_FackYou":
			dialog.text =LinkRandPhrase("You're a thief, my dear! Guards, hold him!!!", "Wow! As soon as I looked at it, you went straight into the chest with your head! Stop the thief!!!", "Guards! They're robbing!!! Stop the thief!!!");
			link.l1 = "Ah, the devil!!!";
			link.l1.go = "Nasilie_fight";
		break;
		case "Nasilie_fight":
			LAi_LocationFightDisable(&Locations[FindLocation("DesMoines_townhall")], false);
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
            LAi_group_SetLookRadius("SPAIN_CITIZENS", 100);
            LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("SPAIN_CITIZENS", LAI_GROUP_PLAYER, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SetDanielleInWorld()
{
	//создаём кэпов
	ref sld = GetCharacter(NPC_GenerateCharacter("Danielle", "Danielle", "woman", "Danielle", 30, PIRATE, -1, true));
	sld.name = "Daniel";
	sld.lastname = "Sheppard";
	sld.dialog.filename   = "Quest\MagicCity.c";
	sld.dialog.currentnode   = "DanAbordage";
	sld.greeting = "";
	sld.GenQuest.CrewSkelModeClassic = true; //команда - скелеты
	FantomMakeCoolSailor(sld, SHIP_CATHERINE, "Queen", CANNON_TYPE_CANNON_LBS42, 90, 90, 90);
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
	sld.Ship.Mode = "pirate";

	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "DanielleGroup";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.city = "SantaCatalina"; //определим колонию, из бухты которой с мушкетом выйдет
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("Queen Galleon left: " + sld.city + " and headed to: " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Queen";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city)) + 1; //дней доехать даём с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "Danielle"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = "MagicCity"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "MagicCity"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 2;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

