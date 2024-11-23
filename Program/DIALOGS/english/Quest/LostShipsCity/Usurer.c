
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Yeah, so you're the one from the last replenishment of citizens? Well, welcome.";
				link.l1 = "Thank you. My name is " + GetFullName(pchar) + ".";
				link.l1.go = "FT_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Hello. Did you want something?";
				link.l1 = "I need money.";
				link.l1.go = "GiveMoney";
				link.l10 = "No, I just dropped by to you.";
				link.l10.go = "Exit";
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Listen, we have a serious conversation. I'm recruiting a team.";
					link.l8.go = "SeekCrew";
				}
			}

			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FT_1":
			dialog.text = "Very nice. And my name is Augusto Brahms. Let's get to know each other.";
			link.l1 = "Okay.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "If you need money, come to me, I can help you out.";
			link.l1 = "Great, I'll know...";
			link.l1.go = "Exit";
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = "You, "+ GetSexPhrase("buddy", "girlfriend") +", don't know who you linked to! And now you're finished...";
			link.l1 = "Ah, the devil!!!";
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = "Oh, so that's how it is?! Are you going to rummage through the chests?! Now the citizens and the police will tear you up like an old newspaper!";
			link.l1 = "What a fool!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = "Hmm, funny... Put the weapon away.";
			link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this city, I ask you not to walk with a naked blade here.", "You know, as a citizen of this city, I ask you not to walk with a naked blade here.");
				link.l1 = LinkRandPhrase("Okay.", "Okay.", "Whatever you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be Careful on turns, "+ GetSexPhrase("buddy", "girlfriend") +", when you run with a gun in your hand. I can get nervous...", "I don't like it when men walk in front of me with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Understood.", "I'm removing.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("I know.",
				"We've already talked about this.",
				"This has already been discussed, I repeat for the second time.",
                "Enough, tired...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Do you know? From where?",
				"yeah... Sorry, I forgot .",
                "As you know...",
				"Well, okay...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "I know a lot... You want me to go with you?";
			link.l1 = "Yes. Do you agree to join my team?";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "No. I will stay here until the last moment.";
			link.l1 = "By the way, it's coming soon, this is the last moment. A storm of unprecedented force is approaching the city.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "I know, but I'm going to stay anyway. I'm not in any danger.";
			link.l1 = "You're weird... Whatever you want.";
			link.l1.go = "exit";
		break;

		//занять бабла
		case "GiveMoney":
			if (CheckAttribute(npchar, "quest.loan"))
			{
				if (sti(npchar.quest.loan.qtyMoney) >= 1000000)
				{
					dialog.text = "You have completely exhausted the allocated quota. The credit line is closed to you.";
					link.l1 = "Clear.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "I am ready to consider your request.";
					link.l1 = "Great!";
					link.l1.go = "GiveMoney_1";
				}
			}
			else
			{
				dialog.text = "Okay. Do you know the terms on which I provide loans?";
				link.l1 = "Not yet. But I hope you'll tell me.";
				link.l1.go = "GiveMoneyKn_1";
				npchar.quest.loan = true;
				npchar.quest.loan.qtyMoney = 0; //кол-во взятых денег
			}
		break;

		case "GiveMoneyKn_1":
			dialog.text = "Required. So, the loan amount is limited to one million piastres. You can take any amount from me within these limits.";
			link.l1 = "Understood. And at what percentage per annum?";
			link.l1.go = "GiveMoneyKn_2";
		break;
		case "GiveMoneyKn_2":
			dialog.text = "I don't have a percentage tied to time. You just have to refund me five times the amount at the first request of my authorized representative.";
			link.l1 = "What?!!!";
			link.l1.go = "GiveMoneyKn_3";
		break;
		case "GiveMoneyKn_3":
			dialog.text = "Do you have hearing problems?";
			link.l1 = "No, I was just a little taken aback...";
			link.l1.go = "GiveMoneyKn_4";
		break;
		case "GiveMoneyKn_4":
			dialog.text = "I have no other conditions, as well as preferences for anyone.";
			link.l1 = "Hmm, I see...";
			link.l1.go = "GiveMoney_1";
		break;

		case "GiveMoney_1":
			dialog.text = "How much money do you want to borrow from me?";
			Link.l1.edit = 4;
			Link.l1 = "";
			link.l1.go = "GiveMoney_2";
			Link.l2 = "Hmm, I guess I'll give up the loan for now.";
			link.l2.go = "GiveMoney_disAgree";
		break;
		case "GiveMoney_2":
			iTemp = sti(dialogEditStrings[4]);
			if ((iTemp + sti(npchar.quest.loan.qtyMoney)) > 1000000)
			{
				dialog.text = "The requested amount exceeds the established quota of one million. I can give you " + FindRussianMoneyString(1000000 - sti(npchar.quest.loan.qtyMoney)) + ", no more.";
				link.l1 = "I see...";
				link.l1.go = "exit";
			}
			else
			{
				if (iTemp <= 0)
				{
					dialog.text = "Joke, right? I don't advise you to fool around with me.";
					link.l1 = "Hmm, got it...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Okay, I'm handing you the required amount with pleasure.";
					link.l1 = "Excellent! You really helped me out, buddy.";
					link.l1.go = "GiveMoney_3";
					AddMoneyToCharacter(pchar, iTemp);
					npchar.quest.loan.qtyMoney = sti(npchar.quest.loan.qtyMoney) + iTemp;
				}
			}
		break;
		case "GiveMoney_3":
			dialog.text = "Very glad. I hope that you will remember the terms of payment for the loan provided. When you have time, you must repay five times the amount of the debt. And at the moment, it's " + FindRussianMoneyString(sti(npchar.quest.loan.qtyMoney) * 5) + ".";
			link.l1 = "Yes, I remember. What happens if I can't get them back right away?";
			link.l1.go = "GiveMoney_4";
		break;
		case "GiveMoney_4":
			dialog.text = "Hmm, it would be better if you had them"+ GetSexPhrase(", buddy", "") +". The alternative, to put it mildly, is very scary. Very...";
			link.l1 = "Clear. Well, I'm going to try.";
			link.l1.go = "exit";
		break;
		case "GiveMoney_disAgree":
			dialog.text = "Well, whatever you want. Think about it properly, maybe you'll think about it again.";
			link.l1 = "Yes, of course...";
			link.l1.go = "exit";
		break;
	}
}
