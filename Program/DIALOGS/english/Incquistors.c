
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("Brothers, there is an enemy in the Inquisition!!!", "Raise the alarm, brothers!!!");
					link.l1 = "Yes, the enemies of the Inquisition are not asleep...";
					link.l1.go = "fight";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hello, "+ GetSexPhrase("my son","my daughter") +". What are our fates?", "Glad to see you in our monastery, "+ GetSexPhrase("my son","my daughter") +". Why did you come?"),
							""+ GetSexPhrase("My son","My daughter") +", we've already talked to you today. Do you need anything else?", ""+ GetSexPhrase("My son","My daughter") +"The novices of our order are not distinguished by patience. I ask you again: do you need anything?",
							RandPhraseSimple("It is not good to be idle yourself and distract others from work. I won't say another word...", ""+ GetSexPhrase("My son","My daughter") +"I don't want to have meaningless conversations. I won't say another word to you."), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Just dropped by, Holy Father...", "It's all business, Padre. I'm working like a bee-"+ GetSexPhrase("all of it","all of it") +"in care..."),
							"No, Holy Father...", "No, Padre, I just wanted chat...", RandPhraseSimple("Hmm...", "Well, as you know, Holy Father..."), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);
				if (CheckAttribute(pchar,"GiantEvilSkeleton") && CheckAttribute(pchar,"MalteseInfo") && !CheckAttribute(pchar,"MalteseOrder"))
				{
					link.l2 = "Holy Father, I wanted to inform you that I have visited Skeleton Reef and destroyed the undead in there. Maybe I should get some kind of reward?";
					link.l2.go = "Maltese";
					if (CheckAttribute(pchar,"MalteseOrderOnHold"))
					{
						link.l2 = "I want to talk about Skeleton Reef again.";
						link.l2.go = "Maltese_5";
					}
				}
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Damn it, it's a spy! Hold him!!!";
					link.l1 = "Carramba!!";
					link.l1.go = "fight";
					StartIncquisitioAttack();
				}
				else
				{
					dialog.text = LinkRandPhrase("This is a secure cell, entry here is strictly prohibited!!!", "Don't even think about entering here-it's punishable by death.", "One step inside this cell and you're finished...");
					link.l1 = RandPhraseSimple("I see, soldier.", "I see...");
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключённые
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("Ho ho, it's so much fun to watch how 'holy'They're going straight to hell!'", "My God, did anyone dare to challenge them!!", "I am no longer a tenant in this world - torture... But you brought pleasure the last pleasure in my life. Thank you...");
					link.l1 = RandPhraseSimple("Heh!", "Argh...");
					link.l1.go = "exit";
					//==> квест №7, базар о Роке Бразильце.
					if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
					{
						link.l1 = "Listen, do you know such a person here-Rock the Brazilian?";
						link.l1.go = "Step_F7_2";
					}
					//<== квест №7, базар о Роке Бразильце.
				}
				else
				{
					dialog.text = LinkRandPhrase("There is nothing human about these 'saints'. Mark my words-burn them in hell for our torments...", "Daily tortures and tortures! But I'm not guilty of anything before the Lord!!!", "My cellmate died yesterday, they tortured him on the rack for two days... And how long do I have left?");
					link.l1 = RandPhraseSimple("Hmm... Well, I don't know...", "Well, I understand...");
					link.l1.go = "exit";
					//==> квест №7, базар о Роке Бразильце.
					if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
					{
						link.l1 = "Listen, do you know such a person here-Rock the Brazilian?";
						link.l1.go = "Step_F7_1";
					}
					//<== квест №7, базар о Роке Бразильце.
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

//**************************** Фр. линейка. Квест №7, спасение Рока Бразильца ********************************
 		case "Step_F7_1":
			dialog.text = "I know, he's sitting in the last cell, guarded by that soldier over there. A special place...";
			link.l1 = "Thank you!";
			link.l1.go = "exit";
		break;
 		case "Step_F7_2":
			dialog.text = "In the last cell to the right of the entrance, where the sentry was standing before you killed him...";
			link.l1 = "Yeah, I see... Thank you.";
			link.l1.go = "exit";
		break;

//**************************** запил Капитула ********************************
		case "Maltese":
			dialog.text = "This is very good news, "+ GetSexPhrase("my son","my daughter") +", the Inquisition has long wanted to create a new base somewhere in the archipelago. And the disreputable abandoned island is perfect for that.";
			link.l1 = "So am I supposed to get some kind of reward?";
			link.l1.go = "Maltese_2";
		break;

		case "Maltese_2":
			dialog.text = "We can pay you a million piastres as a reward. But we have another suggestion. Won't you listen?";
			link.l1 = "And what is it?";
			link.l1.go = "Maltese_3";
		break;

		case "Maltese_3":
			dialog.text = "If you pay for the construction yourself, we will appoint you as the head of this structure. And we will provide our specialists for the training of enlisted men and officers.";
			link.l1 = "What will be my responsibilities?";
			link.l1.go = "Maltese_4";
		break;
		case "Maltese_4":
			dialog.text = "Your goal is to make sure that the base is not attacked by the undead. And in case that happens, protect her.";
			link.l1 = "It sounds tempting... But I suppose the price of the question is a million piastres?";
			link.l1.go = "Maltese_5";
		break;

		case "Maltese_5":
			if (!CheckAttribute(pchar,"MalteseOrderOnHold")) dialog.text = "Absolutely. So what do you say?";
			else dialog.text = "And what do you say?";
			if (sti(pchar.money)>=1000000)
			{
				link.l1 = "There's nowhere to put the gold anyway, and the conditions suit me. Here you go, here's a million piastres.";
				link.l1.go = "Maltese_6";
			}
			link.l2 = "I don't have that amount at the moment.";
			link.l2.go = "Maltese_51";
			link.l3 = "I still don't want to take on such responsibility. I'll take a million piastres.";
			link.l3.go = "Maltese_no";
		break;

		case "Maltese_6":
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "I'm glad you agreed. The construction of the Chapter House (which is how this structure will be named) will be approximately completed in 1 month. As time passes, go to Devil's Cove and look for the entrance there.";
			link.l1 = "When the time comes, I will.";
			link.l1.go = "Maltese_build";
		break;

		case "Maltese_build":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.MalteseOrder = true;
			SetTimerFunction("BuildMalteseOrder", 0, 0, 30);
		break;

		case "Maltese_no":
			AddMoneyToCharacter(pchar, 1000000);
			dialog.text = "This is your right. Here you go, here's your million.";
			link.l1 = "Thank you. I have to go.";
			link.l1.go = "Maltese_nofix";
		break;

		case "Maltese_nofix":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.MalteseOrder = true;
		break;

		case "Maltese_51":
			dialog.text = "Good. As soon as you collect the required amount or make another decision, talk to any of those present here.";
			link.l1 = "I have to go.";
			link.l1.go = "Maltese_52";
		break;

		case "Maltese_52":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.MalteseOrderOnHold = true;
		break;
	}
}
