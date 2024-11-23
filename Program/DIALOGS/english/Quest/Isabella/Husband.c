// boal 27.03.2004 Муж Изабелы Армани

void ProcessDialogEvent()
{
	ref NPChar, d, sld;
	aref Link, NextDiag;
	string NPC_Meeting;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Good_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "RP_talkWithHusbandIsOver", 0);
		break;

		case "First time":
			NextDiag.TempNode = "first time";
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			if (CheckAttribute(pchar, "quest.wasInBeedroom"))
			{
	            if (CheckAttribute(NPChar, "quest.NiceMeet"))
				{
					dialog.text = "Hmm, however, you allow yourself too much - to enter the bedroom without asking the owner of the house...";
					link.l1 = "Sorry, buddy, I just got lost...";
					link.l1.go = "Good_exit";
				}
				else
				{
					dialog.text = "What the hell are you doing hanging around my house? Defend yourself, you bastard!";
					link.l1 = "All right...";
					link.l1.go = "Romantic_Battle_in_Bedroom_2";
				}
				DeleteAttribute(pchar, "quest.wasInBeedroom");
			}
			else
			{
				dialog.text = "Greetings, stranger! May I ask who you are and to what do I owe the honor of seeing you at home?";
				link.l1 = "My name is " + GetFullName(pchar) + ", I am captain.";
				link.l1.go = "Next_1";
				link.l2 = "I'm sorry. I got the wrong address.";
				link.l2.go = "Good_exit";
			}
		break;

        case "Next_1":
            NextDiag.TempNode = "Usual_1";
			dialog.text = "Captain or still a corsair? Judging by your appearance, senor, it's more likely the latter. Well, nowadays, more than one honorable don has made a decent fortune in this way. And I'm no exception.";
			link.l1 = "Were you a corsair?!";
			link.l1.go = "Next_2";
			link.l2 = "I'm sorry... business!";
			link.l2.go = "Good_exit";
		break;

		case "Next_2":
		    NextDiag.TempNode = "Usual_1";
			dialog.text = "What's so amazing about that? This is a very fast and reliable way to get rich. But after a successful marriage, I decided to settle down, which is what I wish you.";
			link.l1 = "Understood. Thanks for the advice. I will certainly follow him on occasion...";
			link.l1.go = "Good_exit";
			NPChar.quest.NiceMeet = true;
		break;

		case "Usual_1":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		    NextDiag.TempNode = "Usual_1";
			dialog.text = "Nice to see you again. What brings you to me this time?";
			link.l1 = "Nothing special. I just came to visit.";
			link.l1.go = "Good_exit";
			if (CheckAttribute(pchar, "quest.VisitStep"))
			{
				if (sti(pchar.quest.VisitStep)>2 && !CheckAttribute(pchar, "quest.wasInBeedroom"))
				{
					dialog.text = "Oh, "+ GetFullName(pchar)+" back at my place. Well, it's nice to see you again. Why did you come?";
					link.l1 = "Salvator, I want to talk to your wife. May I?";
					link.l1.go = "Step_2";
				}
				if (sti(pchar.quest.VisitStep)>2 && CheckAttribute(pchar, "quest.wasInBeedroom"))
				{
					if (!CheckAttribute(pchar, "quest.already"))
					{
						dialog.text = "Aren't you visiting my wife too often, buddy?";
						link.l1 = "Yes, it's okay, friend Salvator. I know her relatives, so don't worry.";
						link.l1.go = "Step_1";
					}
					else
					{
						dialog.text = "Have you passed everything you need?";
						link.l1 = "Yes, Salvator, everything is fine.";
						link.l1.go = "Good_exit";
						LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", true);
					}
					DeleteAttribute(pchar, "quest.wasInBeedroom");
				}
			}
		break;
		case "Step_1":
			dialog.text = "All this is good, but from now on, please ask permission to visit her, as is done in decent houses.";
			link.l1 = "Okay, Salvator, whatever you say.";
			link.l1.go = "Good_exit";
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", true);
			pchar.quest.already = true;
		break;
		case "Step_2":
			dialog.text = "Why do you need this?";
			link.l1 = "I want to give her a message from my family.";
			link.l1.go = "Step_3";
		break;
		case "Step_3":
			dialog.text = "Okay, I'll let you.";
			link.l1 = "Thank you, Salvator. I'll be right there.";
			link.l1.go = "Good_exit";
			if (pchar.RomanticQuest == "DelivMigel")
			{
				dialog.text = "You got her brother Miguel out of Cumana, so you're kind of a family friend now. So come on in, no problem.";
				link.l1 = "Hmm, I get it, Salvator. Thank you.";
			}
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", false);
		break;

		case "Romantic_Battle_in_Bedroom":
		    if (CheckAttribute(NPChar, "quest.NiceMeet"))
		    {
			    dialog.text = "" + GetFullName(pchar) +", have you already met my wife? " + Characters[GetCharacterIndex("Isabella")].Name + " if there are no objections, I'll get back to my business. I'm waiting for you downstairs...";
			    link.l1 = "Oh, yes. Now I look at your advice in a different way.";
			    link.l1.go = "Romantic_Battle_in_Bedroom_3";
			}
			else
			{
			    dialog.text = "What! You! You're doing it! In my wife's bedroom?!";
			    link.l1 = "I... I got here by mistake... I had no idea...";
			    link.l1.go = "Romantic_Battle_in_Bedroom_1";
			}
		break;

		case "Romantic_Battle_in_Bedroom_1":
			dialog.text = "Defend yourself, you fool, you're going to die now!";
			link.l1 = "What??? Well, we'll see about that!";
			link.l1.go = "Romantic_Battle_in_Bedroom_2";
		break;

		case "Romantic_Battle_in_Bedroom_2":
			DialogExit();
			AddDialogExitQuest("Romantic_Battle_in_Bedroom_3");
		break;

		case "Romantic_Battle_in_Bedroom_3":
		    NextDiag.CurrentNode = "Usual_1";
            Pchar.RomanticQuest.TalkInShop = true;// обошлось все мирно - до встречи в магазине
			DialogExit();
			AddDialogExitQuest("Romantic_Battle_in_Bedroom_4");
		break;

		case "WeWaitYouTonight":
			NextDiag.CurrentNode = "WeWaitYouTonight";
			dialog.text = "My wife and I will be glad to see you tonight, Captain.";
			link.l1 = "I will definitely be there, Salvator.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		break;

		case "SeenMainHero":
			dialog.text = "Heh, you're just in time, " + GetFullName(pchar) + "... Kill this dirty pig. Let everyone think that they stabbed each other.";
			link.l1 = "...";
			link.l1.go = "SeenMainHero_1";
		break;
		case "SeenMainHero_1":
			AddQuestRecord("Romantic_Line", "9");
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "houseSp6", "SanJuan_houseSp6", "goto", "goto1", "Romantic_DeadBrother_3", 2.0);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			NextDiag.CurrentNode = "ArrestInHome_1";
			DialogExit();
		break;

		case "ArrestInHome_1":
			dialog.text = "Yeah, here you are\n"+
				          "Officer, this man killed the unfortunate Don Miguel de Valdez! And now he was probably going to kill me and my wife! Look at this! His hands are covered in blood!";
			link.l1 = "Sneaky liar! You killed Don Miguel de Valdez!";
			link.l1.go = "ArrestInHome_2";
		break;
		case "ArrestInHome_2":
			AddDialogExitQuest("Romantic_ArrestInHouse");
			NextDiag.CurrentNode = "Romantic_Battle_in_Bedroom_1";
			DialogExit();
		break;
		//базар в пещере
		case "TalkInCave":
			dialog.text = "Oh, oh, just like the lovebirds cooing! Am I bothering you?";
			link.l1 = "On the contrary, Salvator, you're just in time! If you only knew how glad I am to see you!";
			link.l1.go = "TalkInCave_1";
		break;
		case "TalkInCave_1":
			dialog.text = "Really?";
			link.l1 = "Yes, yes, don't even doubt it. I'm looking for you all over the Caribbean... did you bring a brazier?";
			link.l1.go = "TalkInCave_2";
		break;
		case "TalkInCave_2":
			dialog.text = "Not yet, later...";
			link.l1 = "I'm afraid you won't get another chance for a barbecue, buddy. It's time for Senora Isabella to become a widow.";
			link.l1.go = "TalkInCave_3";
		break;
		case "TalkInCave_3":
			dialog.text = "And aren't you that hero?";
			link.l1 = "I, Salvator, I...";
			link.l1.go = "TalkInCave_4";
		break;
		case "TalkInCave_4":
			dialog.text = "Then let's get started! Welcome to hell, " + GetFullName(pchar) + "!";
			link.l1 = "I think I'll let you go ahead... Oh, and I really like your wife, Salvator. Can she not go into mourning after your death? We are in a hurry to get married...";
			link.l1.go = "TalkInCave_5";
		break;
		case "TalkInCave_5":
			dialog.text = "Ah, I'll send this bastard after you!";
			link.l1 = "It's not good to talk about your own wife like that...";
			link.l1.go = "TalkInCave_6";
		break;
		case "TalkInCave_6":
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "goto5", "", -1);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Romantic_SalvatorIsDead");
			DialogExit();
		break;
	}
}
