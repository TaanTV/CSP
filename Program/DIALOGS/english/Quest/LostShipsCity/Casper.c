
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fightQuest":
			pchar.questTemp.LSC.Armo.checkCasper = npchar.index; //для обработки в АИ
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//первый каспер на разводе Армо
		case "Casper_1":
			dialog.text = "Hey, "+ GetSexPhrase("buddy", "girlfriend") +", get out of here! Clear the site.";
			link.l1 = "What's the matter?";
			link.l1.go = "Casper_1_1";
			NextDiag.TempNode = "Casper_12";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_1_1":
			dialog.text = "I'm waiting for someone here, there will be a third extra. Understood?";
			link.l1 = "Are you expecting Armo? So I'm for her.";
			link.l1.go = "Casper_1_2";
			link.l2 = "Ah, I see. Well, okay...";
			link.l2.go = "exit";
		break;
		case "Casper_1_2":
			dialog.text = "What?!";
			link.l1 = "Still don't get it? Well, you'll understand now...";
			link.l1.go = "fightQuest";
		break;

		case "Casper_12":
			dialog.text = "Listen, I think I've made myself clear. Get out of here, "+ GetSexPhrase("buddy", "girlfriend") +"...";
			link.l1 = "Aren't you waiting for Armo, my friend? So she won't be, I'm for her.";
			link.l1.go = "Casper_12_1";
			link.l2 = "Okay, okay...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_13";
		break;
		case "Casper_12_1":
			dialog.text = "What?!";
			link.l1 = "Still don't get it? Well, you'll understand now...";
			link.l1.go = "fightQuest";
		break;

		case "Casper_13":
			dialog.text = "Well, that's it, you got me. It doesn't work out well...";
			link.l1 = "Well, yes, I'm persistent!";
			link.l1.go = "fightQuest";
		break;
		//второй каспер на разводе Армо
		case "Casper_3":
			dialog.text = ""+ GetSexPhrase("Buddy", "Darling") +", you better get out of here...";
			link.l1 = "What is it?";
			link.l1.go = "Casper_3_1";
			NextDiag.TempNode = "Casper_32";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_3_1":
			dialog.text = "Well, you know, I have a date here. So your presence here is undesirable, to put it mildly.";
			link.l1 = "Not Armo, by any chance, are you waiting?";
			link.l1.go = "Casper_3_2";
			link.l2 = "Okay, buddy.";
			link.l2.go = "exit";
		break;
		case "Casper_3_2":
			dialog.text = "How do you know?";
			link.l1 = "There will be no Armo, I will take her place.";
			link.l1.go = "fightQuest";
		break;

		case "Casper_32":
			dialog.text = ""+ GetSexPhrase("Buddy", "Darling") +"I beg you, don't be rude.";
			link.l1 = "Rudeness? Hehe, okay, that's enough. Armo won't come, I'm for her.";
			link.l1.go = "Casper_32_1";
			link.l2 = "Okay.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_33";
		break;
		case "Casper_32_1":
			dialog.text = "How to understand?";
			link.l1 = "Whatever you want, understand...";
			link.l1.go = "fightQuest";
		break;

		case "Casper_33":
			dialog.text = "I warned you, "+ GetSexPhrase("buddy", "girl") +". Now blame yourself!";
			link.l1 = "Who should I blame? Wait, I didn't hear...";
			link.l1.go = "fightQuest";
		break;
		//третий каспер на разводе Армо
		case "Casper_5":
			dialog.text = "Hey, get out of here while you're alive!";
			link.l1 = "Hmm, why is that?";
			link.l1.go = "Casper_5_1";
			NextDiag.TempNode = "Casper_52";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_5_1":
			dialog.text = "Because I'm standing here! I have a date here. Understood"+ GetSexPhrase("?", "? And not with you.") +"";
			link.l1 = "Date with Armo? Well, it's for nothing...";
			link.l1.go = "Casper_5_2";
			link.l2 = "Understood...";
			link.l2.go = "exit";
		break;
		case "Casper_5_2":
			dialog.text = "Yes, with Armo.";
			link.l1 = "There will be no Armo, you have a date with me.";
			link.l1.go = "fightQuest";
		break;

		case "Casper_52":
			dialog.text = "Listen, I already told you to get out of here!";
			link.l1 = "If you expect it, it won't happen. You see, you have a date with me.";
			link.l1.go = "Casper_52_1";
			link.l2 = "Yes, yes, I'm already leaving...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_53";
		break;
		case "Casper_52_1":
			dialog.text = "What?!";
			link.l1 = "That idiot!..";
			link.l1.go = "fightQuest";
		break;

		case "Casper_53":
			dialog.text = "That's it, I've had enough of persuasion...";
			link.l1 = "Yes, I think that's enough.";
			link.l1.go = "fightQuest";
		break;
		//ГГ застукали за первым
		case "FackYou":
			dialog.text = "It's not for nothing that I suspected bad things. Too many of our people are missing...";
			link.l1 = ""+ GetSexPhrase("Oh... What are you talking about?", "What the hell... What are you talking about?") +"";
			link.l1.go = "FackYou_1";
		break;
		case "FackYou_1":
			dialog.text = "About this bitch Armo. And about you, of course, "+ GetSexPhrase("buddy", "girlfriend") +". What are you doing, "+ GetSexPhrase("brute", "scoundrel") +"?";
			link.l1 = ""+ GetSexPhrase("I don't even know how to say it... Well, in general, I cut the 'Casper' one at a time.", "Tracked down, bastard... Yes, I'm cutting you scum one by one.") +"";
			link.l1.go = "FackYou_2";
		break;
		case "FackYou_2":
			dialog.text = "Understood... Well, it's not for nothing that I bled Armo.";
			link.l1 = "What?!";
			link.l1.go = "FackYou_3";
		break;
		case "FackYou_3":
			dialog.text = "Yes, yes, "+ GetSexPhrase("buddy", "girlfriend") +". I sent Armo after her boss, Hill Brunner. And it's fair - they had such a good time together...";
			link.l1 = ""+ GetSexPhrase("You're going to pay for this!", "Oh you... That's it, you're finished, you bastard.") +"";
			link.l1.go = "FackYou_4";
		break;
		case "FackYou_4":
			dialog.text = "What, do you think I'm completely stupid? Yesterday everything became clear to me, although it was only suspicions. And now I'm not alone.";
			link.l1 = ""+ GetSexPhrase("It won't help you...", "It won't help you! Die, you bastard!!") +"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_3CarperAttackArmo");
		break;

	}
}
