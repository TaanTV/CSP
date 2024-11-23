// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What did you want? Ask.", "I'm listening to you, what's the question?"), "For the second time in a day you're trying to ask a question...", "For the third time in a day you're trying to ask a question again...",
                          "But when will it end?! I have a lot of things to do to manage the affairs of the city, and you're trying to ask all the questions!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, not the place and not the time..."), "Yes, that's right... But not now, later...",
                      "I'll ask, I'll ask... Only later...", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "RomanticQuest.MayorOk"))
			{
				link.l1 = "Senior Governor, I am captain " + GetFullName(pchar) + ". It was I who got married in the church of the city with the widow Isabella Olevares, nee de Valdez.";
				link.l1.go = "Romantic_1";
			}
		break;
		case "Romantic_1":
			dialog.text = "You're just in time, Captain! I've already sent the commandant for you\n"+
				          "Well, since you're here, tell me, for God's sake, what a terrible massacre you've committed in our church!";
			link.l1 = "Senor" + npchar.lastname + ", I was simply defending my life, honor and Isabella, my wife...";
			link.l1.go = "Romantic_2";
		break;
		case "Romantic_2":
			dialog.text = "Sounds great, Captain. But I'm just waiting for the details of what has stirred up the whole city!";
			link.l1 = "Senor Governor, Isabella's late husband, Salvator Olevares, was a pretty scoundrel. He is followed by a whole trail of vile crimes, among which there are many murders...";
			link.l1.go = "Romantic_3";
		break;
		case "Romantic_3":
			dialog.text = "I know that. Upon arrival from Belize from her cousin Fernandez, Isabella was at my reception and told me about all this. So you are her savior?";
			link.l1 = "Yes, Mr. Governor. I suppose it's not surprising that Isabella and I decided to get married as soon as it became possible. However, the bastard Salvator, even before he died, hired a whole gang of disgusting scum from all over the Caribbean in order to destroy us.";
			link.l1.go = "Romantic_4";
		break;
		case "Romantic_4":
			dialog.text = "And there were those mercenaries in the church?";
			link.l1 = "That's right, Senor Governor. I guess I've done a lot of good for the whole region by killing so many bandits at once...";
			link.l1.go = "Romantic_5";
		break;
		case "Romantic_5":
			dialog.text = "Undoubtedly, Captain, that's the way it is. Well, now everything is clear enough to me. I suppose we'll have a church lighting ceremony at the public expense.";
			link.l1 = "Senor Governor, thank you so much for understanding the situation...";
			link.l1.go = "Romantic_6";
		break;
		case "Romantic_6":
			dialog.text = "It is my duty to understand such matters, Captain! Well, I wish you happiness with your spouse. Congratulations.";
			link.l1 = "Thank you, Mr. Governor!";
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "27");
			DeleteAttribute(pchar, "RomanticQuest.MayorOk");
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false); //и только теперь открываем дверь в дом Изабеллы
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

