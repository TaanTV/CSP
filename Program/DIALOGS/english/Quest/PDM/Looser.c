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
		case "first time":
			dialog.text = "I'm listening to you, buddy.";
			link.l1 = "I couldn't do as you asked.";
			link.l1.go = "1";
		break;

		case "1":
			dialog.text = "I shouldn't have contacted you. You're not good for even the simplest tasks. Now get out! You won't see me anymore.";
			link.l1 = "Heh, life will show! And now, goodbye. I hope that life has taught you something too, buddy!";
			link.l1.go = "exit";

			NextDiag.TempNode = "second time";
			AddDialogExitQuestFunction("LooserGenerator_TimeFailed");
		break;

		case "second time":
			dialog.text = LinkRandPhrase("Did I make myself clear? Get out!", "I don't want to talk to you.", "Go away so I don't see you.");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "second time";
		break;

		case "quest":
			dialog.text = "I'm listening to you, buddy.";
			link.l1 = "I took all wallets, as you requested. So what about the reward?";
			link.l1.go = "2";
		break;

		case "2":
			dialog.text = "I have an unusual thing for you. Thanks to her, you will be able to win more often in gambling.";
			link.l1 = "Huh, how did you lose all the money with such a thing?";
			link.l1.go = "2.1";
			
			GiveItem2Character(PChar, "Joker");
			Log_info("You have received the Joker playing card.");
			PlaySound("Interface\important_item.wav"); 
		break;
		
		case "2.1":
			dialog.text = "It only increases the chance of winning, but it does not guarantee victory. In any case, it will do you more good than it will me.";
			link.l1 = "Thank you for such a gift, but now I have to take my leave, see you later.";
			link.l1.go = "exit";

			AddDialogExitQuestFunction("LooserGenerator_Complette");
			NextDiag.TempNode = "3";
		break;

		case "3":
			dialog.text = LinkRandPhrase("Oh, it's you...", "I'm leaving soon, see you later.", "Maybe we'll cross paths again someday...");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "3";
		break;

		case "Jdet_1":
			dialog.text = "I'm listening to you, buddy.";
			link.l1 = "I'll get your money soon, don't worry.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Jdet_1";
		break;

		case "exit":
			if (CheckAttribute(NextDiag, "TempNode")) NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
