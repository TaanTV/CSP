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
			//пиратка, квест №7
			if (pchar.questTemp.piratesLine == "Soukins_toLaVega")
			{
				link.l1 = "Master, I'm looking for Steve Linnaeus, can you tell me if he came to see you?";
				link.l1.go = "PL_Q7_1";
			}
		break;
		case "PL_Q7_1":
			dialog.text = "Was. He and his friend often stayed here too long. I was there the day before yesterday, but I didn't come in yesterday... A friend of his recently departed from the pier on a lugger, if you hurry up, you will have time to intercept him at sea. You'll ask him where to find Linnaeus.";
			link.l1 = "Thank you!";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_toLaVegaSea";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			AddQuestRecord("Pir_Line_7_Soukins", "2");
			pchar.quest.PQ7_FriendLinney.win_condition.l1 = "location";
			pchar.quest.PQ7_FriendLinney.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PQ7_FriendLinney.function = "PQ7_FriendLinney";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

