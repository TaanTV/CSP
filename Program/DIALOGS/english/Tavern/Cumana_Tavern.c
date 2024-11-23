// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the gossip of the city "+ GetCityName(npchar.city) +" at your service. What would you like to know?",
                          "We just brought up this topic. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Why are you talking like a parrot? The same thing...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Yeah...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            if (CheckAttribute(pchar, "RomanticQuest.ShipToCumana"))
			{
    			link.l1 = "Do you know where I can find captain of the brig Five Wounds of Christ?";
    			Link.l1.go = "RomanticQuest_1";
			}
			if (CheckAttribute(pchar, "RomanticQuest.ShipToCumanaTavenrn"))
			{
    			link.l1 = "Where can I find captain of the brig 'Five Wounds of Christ'? I was told he was here.";
    			Link.l1.go = "RomanticQuest_2";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toCumana")
			{
				link.l1 = "Did a certain captain of the brig, named Edward Law, come to see you?";
				link.l1.go = "PL_Q3_1";
			}
		break;

		case "RomanticQuest_1":
			dialog.text = "Yes, this captain appears here, he has been repairing his ship for some time. But he's not here now. Look in the city.";
			link.l1 = "Thank you!";
			link.l1.go = "exit";
		break;
		case "RomanticQuest_2":
			dialog.text = "He's sitting at a round table, pouring wine over the mountain.";
			link.l1 = "Thank you!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "RomanticQuest.ShipToCumanaTavenrn");
		break;

		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat("No. This is the first time I've heard that name.",
				"I've already answered this question for you.",
				"We've already talked about this Law...",
                "For the last time, I haven't heard anything about Edward Law!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thanks, buddy.",
				"Yes, yes, I remember...",
                "Yes, of course...",
				"Understood.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

