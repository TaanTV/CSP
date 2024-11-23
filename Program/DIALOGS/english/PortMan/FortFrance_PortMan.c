// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Listen, if you're not on port business, then don't bother me with questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yeah, really for the third time...", "Sorry, but I'm not interested in port affairs right now.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = "I'm looking for Edward Law, has he visited you?";
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_noMoney")
			{
				link.l1 = "I found money!";
				link.l1.go = "PL_Q3_7";
			}
		break;
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat("Edward Law? I came in, at that time I had a French privateer, so he asked for it, as a passenger.",
				"We've already talked about this topic!",
				"Stop repeating the same thing immediately.",
                "Hmm, I'm tired...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Do you know where this privateer was going?",
				"Yes, I remember.",
                "Well...",
				"I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = "I know, but you understand that I have no right to disclose such information...";
			link.l1 = "But I really need to find him! I have a matter of high importance for him!";
			link.l1.go = "PL_Q3_out";
			link.l2 = "The fact is that we're far away relatives with Edward Law, and I hasten to inform him about his mother's illness. You, as a decent person, will not allow your son to be unable to say goodbye to a dying woman because of a bureaucratic letter...";
			link.l2.go = "PL_Q3_3";
		break;

		case "PL_Q3_out":
			dialog.text = "Search...";
			link.l1 = "Ah, the devil!..";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "6");
			AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("", "a"));
			pchar.questTemp.piratesLine = "KillLoy_notFound";
			QuestSetCurrentNode("Henry Morgan", "PL_Q3_notFound");
		break;
		case "PL_Q3_3":
			if (GetCharacterSkill(pchar, "Sneak") >= 60 || GetCharacterSPECIAL(pchar, "Charisma") > 6)
			{
				dialog.text = "Yes, it's a big tragedy, I'll help you. The privateer was heading for Bermudes.";
				link.l1 = "Thank you very much! You have no idea what you've done for me! Thank you.";
				link.l1.go = "exit";
				AddQuestRecord("Pir_Line_3_KillLoy", "7");
				pchar.questTemp.piratesLine = "KillLoy_toBermudes";
			}
			else
			{
				dialog.text = "Well, yes, of course. Everyone here tells me stories about poor relatives, about dying mothers, and I have to believe everyone! No, come up with something else.";
				link.l1 = "Maybe a small donation to the Port Authority Building renovation Fund will help us get around this unpleasant point in your charter?";
				link.l1.go = "PL_Q3_4";
			}
		break;
		case "PL_Q3_4":
			dialog.text = "Mm-hmm... well, since you're insisting that 15,000 could compensate me for the moral hazard of breaking the rules...";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "What are the problems?! Here's your fee.";
				link.l1.go = "PL_Q3_5";
			}
			else
			{
				link.l1 = "Hmm, I don't have that amount with me right now!";
				link.l1.go = "PL_Q3_6";
			}
		break;
		case "PL_Q3_5":
			dialog.text = "That privateer went to Bermudes...";
			link.l1 = "I understand. Thank you for your sincere participation in our family problems. Goodbye.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "7_1");
			pchar.questTemp.piratesLine = "KillLoy_toBermudes";
			AddMoneyToCharacter(pchar, -15000);
		break;
		case "PL_Q3_6":
			dialog.text = "So you'll have to get it. Don't worry, I'll wait...";
			link.l1 = "Um, okay. I'll get the money!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "8");
			pchar.questTemp.piratesLine = "KillLoy_noMoney";
		break;
		case "PL_Q3_7":
			if (sti(pchar.money) >= 15000)
			{
				dialog.text = "Very good!";
				link.l1 = "Here's your 15 thousand. Say what you know.";
				link.l1.go = "PL_Q3_5";
			}
			else
			{
				dialog.text = "Um, do you take me for an idiot? Go get the money!";
				link.l1 = "The Devil!!";
				link.l1.go = "exit";
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

