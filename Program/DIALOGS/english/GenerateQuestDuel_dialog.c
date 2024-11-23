
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sName = PChar.name + " " + PChar.lastname;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you need?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		// Первый дуалист -->
		case "Duelist_1_1":
			dialog.text = "Hello, Captain " + sName + ". I hope you have some free time to talk?";
			link.l1 = "Greetings, sir. What happened?";
			link.l1.go = "Duelist_1_2";
			LAi_CharacterPlaySound(NPChar, "Duel_Man_Help");
		break;

		case "Duelist_1_2":
			dialog.text = "The fact is that I have a duel scheduled for today, with a certain person...";
			link.l1 = "And what is your problem?";
			link.l1.go = "Duelist_1_3";
		break;

		case "Duelist_1_3":
			dialog.text = "You understand... I wouldn't want to fight him myself. I'm a bad swordsman, but my honor is at stake and I can't give up the duel. I thought that...";
			link.l1 = "What can I do for you?";
			link.l1.go = "Duelist_1_4";
		break;

		case "Duelist_1_4":
			dialog.text = "That's right. I'll pay you.";
			link.l1 = "And how much?";
			link.l1.go = "Duelist_1_5";
		break;

		case "Duelist_1_5":
			dialog.text = sti(PChar.GenerateQuestDuel.Money) + " piastres.";
			link.l1 = "I am at your service.";
			link.l1.go = "Duelist_1_7";
			link.l2 = "Ha ha ha! Fight for your honor yourself.";
			link.l2.go = "Duelist_1_6";
		break;

		case "Duelist_1_6":
			dialog.text = "But captain!";
			link.l1 = "Good luck. You'll need it.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelManCancel");
		break;

		case "Duelist_1_7":
			dialog.text = "Thank you very much, Captain. The duel is scheduled outside the city gates. The time has come - let's go.";
			link.l1 = "Let's go.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelAgree");
		break;

		case "Duelist_1_8":
			dialog.text = PChar.GenerateQuestDuel.WifeName + ", who is this "+GetSexPhrase("guy", "girl")+"?";
			link.l1 = "";
			link.l1.go = "Duelist_1_9";
		break;
		
		case "Duelist_1_9":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Wife));
			dialog.text = + GetSexPhrase("Dear, this captain agreed to help us.", "Dear, this girl agreed to help us.") +"";
			link.l1 = "";
			link.l1.go = "Duelist_1_10";
		break;

		case "Duelist_1_10":
			SetCameraDialogMode(NPChar);
			dialog.text = "Help with what?!";
			link.l1 = "Sir, I promised your wife to dissuade you from the duel.";
			link.l1.go = "Duelist_1_11";
		break;

		case "Duelist_1_11":
			dialog.text = "This is out of the question. The duel will take place even if that bastard publicly apologizes to me. Your honor is hurt, dear, and I must wash away the shame with blood!";
			link.l1 = "";
			link.l1.go = "Duelist_1_12";
		break;
		
		case "Duelist_1_12":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Wife));
			dialog.text = + PChar.GenerateQuestDuel.DuelistName + "Please, for the sake of all saints, come to your senses and make peace!..";
			link.l1 = "";
			link.l1.go = "Duelist_1_13";
		break;

		case "Duelist_1_13":
			SetCameraDialogMode(NPChar);
			dialog.text = "I will fight for you and if necessary I will die. But I will die with honor!";
			link.l1 = "Everything is clear. I see that the duel cannot be prevented. And that's why I offer you my fencing services.";
			link.l1.go = "Duelist_1_14";
		break;

		case "Duelist_1_14":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Wife));
			dialog.text = "How kind of you! " + PChar.GenerateQuestDuel.DuelistName + ", agree!";
			link.l1 = "";
			link.l1.go = "Duelist_1_15";
		break;
		
		case "Duelist_1_15":
			SetCameraDialogMode(NPChar);
			dialog.text = "Under the circumstances, this is the only way out. I'm a bad fighter, and judging by your appearance, you've been in more serious scrapes.";
			link.l1 = "Your truth. So, for " + sti(PChar.GenerateQuestDuel.Money) + " piastres, I am at your service. Where is the duel scheduled?";
			link.l1.go = "Duelist_1_16";
		break;

		case "Duelist_1_16":
			dialog.text = "Outside the city gate. Come on, Captain, the time has come. " + PChar.GenerateQuestDuel.WifeName + ", you will stay at home.";
			link.l1 = "";
			link.l1.go = "Duelist_1_17";
		break;
		
		case "Duelist_1_17":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Wife));
			dialog.text = "God bless you, Captain...";
			link.l1 = "We have to go.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelWoman2Agree");
		break;

		case "Duelist_1_18":
			dialog.text = "Captain, I don't know how to thank you! You saved my life. This mercenary wouldn't have given me a chance!";
			link.l1 = "As far as I understand, I have "+ GetSexPhrase("fulfilled", "fulfilled") +"?";
			link.l1.go = "Duelist_1_19";
			LAi_group_Delete("EnemyFight");
		break;

		case "Duelist_1_19":
			dialog.text = "Here, take this money. Thank you again, Captain!";
			link.l1 = "See you later.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithMercenaryHappyEnd");
		break;

		case "Duelist_1_20":
			dialog.text = "I don't know how to thank you, Captain! Take the money and... I hope no one will find out the details of the duel?";
			link.l1 = "Don't worry, I'm not the chatty guy. See you later.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithDuelistHappyEnd");
			LAi_group_Delete("EnemyFight");
		break;
		// Первый дуалист <--

		// Жена первого дуэлянта -->
		case "Wife_1":
			dialog.text = "Captain! I beg you, help me!";
			link.l1 = "Madam, please calm down. What happened?";
			link.l1.go = "Wife_2";
			LAi_CharacterPlaySound(NPChar, "Duel_Woman_Help");
		break;

		case "Wife_2":
			dialog.text = "My husband had an argument with a neighbor and the quarrel went so far that they decided to resolve it in a duel. " + PChar.GenerateQuestDuel.DuelistName + " does not wield a sword well. He'll be killed, I'm sure!";
			link.l1 = "I understand. Do you want me to reconcile your husband with a neighbor?";
			link.l1.go = "Wife_3";
		break;

		case "Wife_3":
			dialog.text = "Yes! I'll pay you " + sti(PChar.GenerateQuestDuel.Money) + " piastres, just talk him out of the duel.";
			link.l1 = "I'll try. Take me to your husband.";
			link.l1.go = "Wife_5";
			link.l2 = "Sorry, but this is not for me. Look for another parliamentarian.";
			link.l2.go = "Wife_4";
		break;

		case "Wife_4":
			dialog.text = "You are a cruel man!";
			link.l1 = "Uh.. What to do.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelWomanCancel");
		break;

		case "Wife_5":
			QuestDuelWomanAgree();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// Жена первого дуэлянта <--


		// Второй дуалист -->
		case "Duelist_2_1":
			dialog.text = "Yeah, I came! Ahem!";
			link.l1 = "";
			link.l1.go = "Duelist_2_2";
		break;
		
		case "Duelist_2_2":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = "I demand satisfaction!";
			link.l1 = "";
			link.l1.go = "Duelist_2_3";
		break;

		case "Duelist_2_3":
			SetCameraDialogMode(NPChar);
			dialog.text = "You will be satisfied. Who is this with you?";
			link.l1 = "";
			link.l1.go = "Duelist_2_4";
		break;
		
		case "Duelist_2_4":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = + GetSexPhrase("This man", "This girl") +" will fight in my place.";
			link.l1 = "";
			link.l1.go = "Duelist_2_5";
		break;

		case "Duelist_2_5":
			SetCameraDialogMode(NPChar);
			dialog.text = "This is your right. Well, my confidant will act in my place. I'll tell you a secret - an excellent swordsman.";
			link.l1 = "";
			link.l1.go = "Duelist_2_6";
		break;
		
		case "Duelist_2_6":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = "To hell with words. Captain, are you ready?";
			link.l1 = "At your service, gentlemen.";
			link.l1.go = "Duelist_2_7";
			LAi_ActorTurnToCharacter(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1), pchar);
		break;

		case "Duelist_2_7":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Mercenary));
			dialog.text = "Prepare to die, "+GetSexPhrase("brat", "brat")+"!";
			link.l1 = "Let's get started!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithMercenary");
			LAi_ActorTurnToCharacter(CharacterFromID(PChar.GenerateQuestDuel.Characters.Mercenary), pchar);
		break;

		case "Duelist_2_8":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = "Damn it!!! I hope you are satisfied?";
			link.l1 = "";
			link.l1.go = "Duelist_2_9";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "Duelist_2_9":
			SetCameraDialogMode(NPChar);
			dialog.text = "Quite. Now get out. I don't intend to look at you anymore.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithMercenaryEnd");
		break;
		
		case "Duelist_2_10":
			dialog.text = "Greetings, gentlemen! " + PChar.GenerateQuestDuel.DuelistName + ", who is this with you?";
			link.l1 = "";
			link.l1.go = "Duelist_2_11";
		break;
		
		case "Duelist_2_11":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = + GetSexPhrase("This man", "This girl") +" will fight in my place.";
			link.l1 = "";
			link.l1.go = "Duelist_2_12";
		break;
		
		case "Duelist_2_12":
			SetCameraDialogMode(NPChar);
			dialog.text = "My God! And you are a decent coward, " + PChar.GenerateQuestDuel.DuelistName + ", I didn't know, I didn't know...";
			link.l1 = "";
			link.l1.go = "Duelist_2_13";
		break;

		case "Duelist_2_13":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = "Enough with the comedy! The rules allow to use the services of trusted persons.";
			link.l1 = "";
			link.l1.go = "Duelist_2_14";
		break;

		case "Duelist_2_14":
			SetCameraDialogMode(NPChar);
			dialog.text = "Well, when I finish your confidant, the whole city will know about your cowardice. Shall we start?";
			link.l1 = "At your service.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithDuelist");
		break;
		// Второй дуалист <--

		// Родственники -->
		case "Relative_1":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_1));
			dialog.text = "What happened here?";
			link.l1 = "Who are you?";
			link.l1.go = "Relative_2";
			LAi_CharacterPlaySound(NPChar, "Duel_Victory");
		break;

		case "Relative_2":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_2));
			dialog.text = "We didn't make it! Our uncle has been killed! "+ GetSexPhrase("Bastard!!! What have you done?", "You bastard!!! What have you done?") +"";
			link.l1 = "Wait, I'll explain everything now...";
			link.l1.go = "Relative_3";
		break;

		case "Relative_3":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_1));
			dialog.text = "I'LL SKIN YOU ALIVE!!!";
			link.l1 = "We kind of misunderstood each other...";
			link.l1.go = "Relative_4";
		break;

		case "Relative_4":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_2));
			dialog.text = "Defend yourself, carrion!";
			link.l1 = "Damn!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithRelativeRevenge");
		break;
		// Родственники <--

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
