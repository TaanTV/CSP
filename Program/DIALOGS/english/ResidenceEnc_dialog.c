
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

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

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- служанка в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (isBadReputation(pchar, 40))
			{
				dialog.text = LinkRandPhrase("You better get out of here, " + GetAddress_Form(NPChar) + ". There's nothing to do for "+ GetSexPhrase("such guy", "such jerk") +", in the governor's house...", "Go away, "+ GetSexPhrase("robber", "robber") +"! How did you get here?", "Well, the times have come. Every kind of abomination is roaming around the governor's house " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!");
				link.l1 = RandPhraseSimple("Take it easy, you fool...", "Be careful in your expressions...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Hello. I serve the governor. My name is " + GetFullName(NPChar) + ".", "I'm cleaning this room, " + GetAddress_Form(NPChar) + ".", "You know, " + GetAddress_Form(NPChar) + ", our governor is a good man, and pays the servants well...");
				link.l1 = RandPhraseSimple("Very good.", "Hmm, fine...");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "Oh, what is it doing?! And I'm a fool, I walk around, I don't notice anything... Security!!!";
			link.l1 = "Shut up, you fool...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 40))
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("Get out of here, scoundrel", "Get out of here, scoundrel") +"!", "Get out of the governor's house immediately, "+ GetSexPhrase("scoundrel", "scoundrel") +"!", "I don't care to what you need in the governor's house " + XI_ConvertString("Colony" + npchar.city + "Gen") + ". But I'll give you some advice - get out of here!");
				link.l1 = RandPhraseSimple("Take it easy, dear...", "Look, don't choke on your words!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Hello. I am the governor's servant. My name is " + GetFullName(NPChar) + ".", "I'm looking after the order here, " + GetAddress_Form(NPChar) + ".", "You know, " + GetAddress_Form(NPChar) + "our governor is a good man, and pays the servants well...");
				link.l1 = RandPhraseSimple("Very good.", "Hmm, fine...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "You don't do anything "+ GetSexPhrase("I took it into my head", "I took it into my head") +"rob the governor?! Guard, hold "+ GetSexPhrase("thief", "thief") +"!!";
			link.l1 = "Close your mouth...";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 40))
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("Would you go from here, buddy", "Would you go from here, girlfriend") +"...", "Get out of here!", "By the way, you're not at the door"+ GetSexPhrase("wrong", "wrong") +"? This is the governor's house " + XI_ConvertString("Colony" + npchar.city + "Gen") + ". You better leave!");
				link.l1 = RandPhraseSimple("I'll leave when I want!", "Mind your own business...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Today I was assigned to the governor's office. Not a bad place...", "I'm guarding the governor's house, " + GetAddress_Form(NPChar) + ".", "My task is to guard the governor's house.");
				link.l1 = RandPhraseSimple("Great.", "Hmm, I see...");
				link.l1.go = "exit";
			}
		break;
	}
}
