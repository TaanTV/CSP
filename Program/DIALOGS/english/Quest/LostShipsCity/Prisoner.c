
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	float   locx, locy, locz;

	switch(Dialog.CurrentNode)
	{
		case "prisonerHead":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hello. I understand that this is you - "+ GetSexPhrase("last arrived citizen", "last arrived citizen") +"?";
				link.l1 = "That's right. My name is " + GetFullName(pchar) + ".";
				link.l1.go = "FTH_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Hello. What do you need in prison?";
				link.l1 = "Nothing special. I just dropped in .";
				link.l1.go = "Exit";
				//квест со скелетом Декстера
				if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && !CheckAttribute(npchar, "quest.decster"))
				{
					if (pchar.questTemp.LSC.lostDecster == "seekBox" || pchar.questTemp.LSC.lostDecster == "toAdmiral")
					{
						link.l6 = "Do you know who was the head of the prison before you?";
						link.l6.go = "LostDecsterHead";
					}
				}
				//муж Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElis")
				{
					link.l7 = "Can you tell me why Maxim Taylor got here?";
					link.l7.go = "ELTHusb_begin";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "seekFreeMotod")
				{
					link.l7 = "Listen, is there any way to facilitate the release of this drunkard and rowdy Maxim Taylor?";
					link.l7.go = "ELTHusb_SF";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiral")
				{
					link.l7 = "Listen, is there any way to facilitate the release of this drunkard and rowdy Maxim Taylor?";
					link.l7.go = "ELTHusb_SF";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Listen, we have a serious conversation. I'm recruiting a team.";
					link.l8.go = "SeekCrew";
				}
			}
			NextDiag.TempNode = "prisonerHead";
		break;
		case "FTH_1":
			dialog.text = "Well, congratulations. I am the head of the City's prison, reporting directly to the Admiral. I don't mind being friendly with anyone, but keep in mind that if you end up behind bars, friendship is over.";
			link.l1 = "Yes, yes, I understand. And how many people pass through you?";
			link.l1.go = "FTH_2";
		break;
		case "FTH_2":
			dialog.text = "No, unfortunately, there hasn't been anyone for a long time. The clans live their lives, they don't stick out. And citizens prefer not to rowdy.";
			link.l1 = "Clear. Well, good luck with the hard work of doing nothing.";
			link.l1.go = "FTH_3";
		break;
		case "FTH_3":
			dialog.text = "And don't say it! Sometimes, I'm ready to howl at the moon from longing...";
			link.l1 = "I understand... Well, have a nice day.";
			link.l1.go = "Exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "prisoner":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Greetings. I'm glad you survived and now you are among us. I am a jailer, my name is " + GetFullName(npchar) + ".";
				link.l1 = "Very nice. And I am captain " + GetFullName(pchar) + ".";
				link.l1.go = "FTP_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "If you are here on business, then I ask you to talk to the boss.";
				//квест со скелетом Декстера
				if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && npchar.chr_ai.type == LAI_TYPE_SIT && !CheckAttribute(npchar, "quest.decster"))
				{
					if (pchar.questTemp.LSC.lostDecster == "seekBox" || pchar.questTemp.LSC.lostDecster == "toAdmiral")
					{
						link.l1 = "Hey, do you know who Leighton Dexter is?";
						link.l1.go = "LostDecster";
					}
				}
				//квест с вином от Доминика Легро
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toTomasBoil" && CheckCharacterItem(pchar, "potionwine"))
				{
					link.l2 = "Buddy, I'm a prin"+ GetSexPhrase("eu", "if") +" you'll get a bottle of wine from your friend Dominic Legro. Have a drink, relax, otherwise you're sitting here forever...";
					link.l2.go = "WineLogro";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toSecondToPrison")
				{
					link.l2 = "Buddy, it's me again. And again about Dominic Legro.";
					link.l2.go = "SecondLogro";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "to3ToPrison")
				{
					link.l2 = "Buddy, it looks like Dominic didn't do anything wrong with Armo.";
					link.l2.go = "LastLegro";
				}
				//помощь тюремщика в наезде на касперов, если Армо убита
				iTemp = GetCharacterIndex("LSCwaitress");
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "over" && CheckAttribute(pchar, "questTemp.LSC.LegroHelp.Armo") && iTemp != -1 && characters[iTemp].name != "Armo" && pchar.questTemp.LSC == "toSeekMechanik")
				{
					link.l3 = "Buddy, do you know that Armo was killed?";
					link.l3.go = "ArmoIsDead";
				}
				link.l10 = "Okay, I got it.";
				link.l10.go = "Exit";
			}
			NextDiag.TempNode = "prisoner";
		break;
		case "FTP_1":
			dialog.text = "Well, that's how we met. If you're here on business, then you need to talk to my boss.";
			link.l1 = "Clear.";
			link.l1.go = "exit";
		break;

		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("Which command?",
				"We've already talked about this.",
				"This has already been discussed, I repeat for the second time.",
                "That's enough, I'm tired...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Command to the ship. I'm leaving town.",
				"a.",
                "As you know...",
				"Well, okay...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "Are you crazy? Don't you know the laws of the City?";
			link.l1 = "I'm saving my life, that's all. I suggest you save yours at the same time. The fact is that the City will be destroyed by this storm.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "I don't believe you.";
			link.l1 = "Very wrong.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Heh, you're such a "+ GetSexPhrase("seer", "fortune teller") +", it just takes me aback! I recommend that you slow down.";
			link.l1 = "Well, my business is to suggest...";
			link.l1.go = "exit";
		break;

		//освободить мужа Элис Тейлор
		case "ELTHusb_begin":
			dialog.text = NPCStringReactionRepeat("You won't believe it! This cretin got drunk in a tavern and went to the residence to the admiral to pump his rights.",
				"I've already answered your question.",
				"We've already talked about this!",
                "Listen, stop right now!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oh ho ho... And what kind of demands was he trying to make?",
				"Yes, yes, I remember.",
                "Of course.",
				"Good, good...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_begin_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_begin_1":
			dialog.text = "Yes, the fool knows him. Actually, Maxim is our permanent guest, but this is the first time he contacted Capper. And very wrongly, I tell you. Once here, he got off very well...";
			link.l1 = "What could have happened in the worst case scenario?";
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = "Well, history does not tolerate subjunctive moods.";
			link.l1 = "In general, it is clear...";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "3");
		break;

		case "ELTHusb_SF":
			dialog.text = NPCStringReactionRepeat("I would ask you to contact the Admiral with this question. He put him here, let him decide on his future fate.",
				"We have already talked about this topic.",
				"I repeat once again that we have already talked about this topic.",
                "Are you an idiot?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Is there any way I can come to an agreement with you?",
				"Yes, I forgot...",
                "I forgot again.",
				"It looks very much like that...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_SF_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_SF_1":
			dialog.text = "You're crazy! Go to Capper, my advice to you.";
			link.l1 = "Thanks for the advice.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "4");
		break;

		case "LostDecsterHead":
			dialog.text = "No, I don't know. And I don't advise you to know.";
			link.l1 = "In what sense?";
			link.l1.go = "LostDecsterHead_1";
		break;
		case "LostDecsterHead_1":
			dialog.text = "In the direct. I don't advise you to know who was the commandant before me.";
			link.l1 = "Or maybe it's Leighton Dexter.";
			link.l1.go = "LostDecsterHead_2";
		break;
		case "LostDecsterHead_2":
			dialog.text = "Anything can happen... And why these questions?";
			link.l1 = "There's no need, empty curiosity.";
			link.l1.go = "LostDecsterHead_3";
		break;
		case "LostDecsterHead_3":
			dialog.text = "Don't show it anymore. Curiosity, you know, is a very dangerous property of the body...";
			link.l1 = "Hmm... Yes, yes, I understand.";
			link.l1.go = "exit";
			npchar.quest.decster = true; //не повторять базар
		break;

		case "LostDecster":
			dialog.text = "Former boss of Tartarus.";
			link.l1 = "Where is he now?";
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = "Hehe... Behind the door to the left of the last cell in the right row. But don't say a word to anyone!..";
			link.l1 = "Never!";
			link.l1.go = "exit";
			AddQuestRecord("LSC_findDekster", "4");
			npchar.quest.decster = true; //не повторять базар
		break;
		//вино от Доминика Легро
		case "WineLogro":
			dialog.text = "A bottle of wine from Dominic Legro?!I'll take it, so be it. But tell this scoundrel, I'll get even with him!";
			link.l1 = "Did not understand...";
			link.l1.go = "WineLogro_1";
		break;
		case "WineLogro_1":
			dialog.text = "And you have nothing to understand. Just tell him I'll cut off his ears on the go.";
			link.l1 = "Okay, I'll pass it on... And Dominic thought you'd be happy.";
			link.l1.go = "WineLogro_2";
			TakeItemFromCharacter(pchar, "potionwine");
		break;
		case "WineLogro_2":
			dialog.text = "I am very glad... Well, okay, I don't have time to start talking here. Thanks for the wine, and tell Dominic what I said.";
			link.l1 = "Okay, I'll pass it on.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toFackDominic";
			AddQuestRecord("TakeVineToPrisoner", "2");
			AddQuestUserData("TakeVineToPrisoner", "sSex", GetSexPhrase("", "la"));
		break;

		case "SecondLogro":
			dialog.text = "What do you say?";
			link.l1 = "I told him your words. He was very surprised and swears that he is completely unaware of what is happening.";
			link.l1.go = "SecondLogro_1";
		break;
		case "SecondLogro_1":
			dialog.text = "Really?";
			link.l1 = "He swore.";
			link.l1.go = "SecondLogro_2";
		break;
		case "SecondLogro_2":
			iTemp = GetCharacterIndex("LSCwaitress");
			if (iTemp != -1 && characters[iTemp].name == "Armo")
			{
				dialog.text = "And when he swore, did he by any chance remember how he flirted with Armo Dulin, the waitress from the tavern, the other day?";
				link.l1 = "I have no idea.";
				link.l1.go = "SecondLogro_3";
				pchar.questTemp.LSC.LegroHelp.Armo = true; //флаг на то, что квест пошёл с участием Армо
			}
			else
			{
				dialog.text = "Even so? Hmm, well, then, perhaps we should make up.";
				link.l1 = "So Dominic didn't fight with you.";
				link.l1.go = "LastLegroAdd";
			}
		break;
		case "SecondLogro_3":
			dialog.text = "Well, you ask him.";
			link.l1 = "Okay...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toArmoDominic";
			AddQuestRecord("TakeVineToPrisoner", "4");
		break;

		case "LastLegro":
			dialog.text = "How is it?";
			link.l1 = "He says he was just talking to Armo, but he wasn't hitting on her in any way.";
			link.l1.go = "LastLegro_1";
		break;
		case "LastLegro_1":
			dialog.text = "But I was told...";
			link.l1 = "Don't be guided by gossip in your relationships with friends.";
			link.l1.go = "LastLegro_2";
		break;
		case "LastLegro_2":
			dialog.text = "Yes, you're right. Well, I believe Dominic. Tell him I'm sorry. It seems that I have behaved unworthily.";
			link.l1 = "Yes, indeed, it looks like that.";
			link.l1.go = "LastLegro_3";
		break;
		case "LastLegro_3":
			dialog.text = "Thank you, "+ GetSexPhrase("friend", "" + pchar.name + "") +", for participating in our business with Dominic.";
			link.l1 = "Always glad to help.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toKeyDominic";
			AddQuestRecord("TakeVineToPrisoner", "6");
		break;

		case "LastLegroAdd":
			dialog.text = "Yes, you're right... Listen, tell Dominic that everything is fine. I'm not mad at him.";
			link.l1 = "Well, great! Well, then I think I'll go...";
			link.l1.go = "LastLegro_3";
		break;
		//если Армо убита, то тюремщик может помочь в наезде на касперов
		case "ArmoIsDead":
			dialog.text = "I know that.";
			link.l1 = "Do you know who did this?";
			link.l1.go = "ArmoIsDead_1";
		break;
		case "ArmoIsDead_1":
			dialog.text = "Trying to find out. As soon as I find it, I'll cut out the heart.";
			link.l1 = "It was done by Juan Kobo, one of the 'caspers'.";
			link.l1.go = "ArmoIsDead_2";
		break;
		case "ArmoIsDead_2":
			dialog.text = "How do you know?";
			link.l1 = "He told me that himself. But there's no hurry, I've already killed him.";
			link.l1.go = "ArmoIsDead_3";
		break;
		case "ArmoIsDead_3":
			dialog.text = "Sorry...";
			link.l1 = "Well, I wouldn't say that.";
			link.l1.go = "ArmoIsDead_4";
		break;
		case "ArmoIsDead_4":
			dialog.text = "What do you mean?";
			link.l1 = "I suggest that you not personify revenge, but take revenge on the whole clan, because Kobo was just a performer. You know as well as I do that they don't move a step without the direction of the clan leader.";
			link.l1.go = "ArmoIsDead_5";
		break;
		case "ArmoIsDead_5":
			dialog.text = "This is so...";
			link.l1 = "I'm going to invade the San Gabriel. You can come with me.";
			link.l1.go = "ArmoIsDead_6";
		break;
		case "ArmoIsDead_6":
			dialog.text = "I'm ready.";
			link.l1 = "Then go ahead, there will be no postponement of this matter.";
			link.l1.go = "ArmoIsDead_7";
		break;
		case "ArmoIsDead_7":
			if (npchar.chr_ai.type == LAI_TYPE_SIT)
			{
				GetCharacterPos(npchar, &locx, &locy, &locz);
				ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			//sld.dialog.currentnode = "AfterFightCasper";//фикс - sld - вообще рандомный непись, а диалог прописывается позже в квестреакциях
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("ISS_MainLine", "70");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "AfterFightCasper":
			dialog.text = "Well, it looks like we've done it.";
			link.l1 = "True. Thanks for the help, buddy. Don't you want to continue to get involved in this kind of mess with me?";
			link.l1.go = "AfterFightCasper_1";
		break;
		case "AfterFightCasper_1":
			dialog.text = "No. It was revenge, not a thirst for adventure. I think I'm going to get drunk. It's hard without Armo...";
			link.l1 = "What about prison?";
			link.l1.go = "AfterFightCasper_2";
		break;
		case "AfterFightCasper_2":
			dialog.text = "I don't care about the prison, the admiral, or even the whole damn city! Eh, life is not sweet to me without Armo...";
			link.l1 = "Sorry, buddy.";
			link.l1.go = "AfterFightCasper_3";
		break;
		case "AfterFightCasper_3":
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
