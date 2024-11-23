// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, " + GetAddress_Form(NPChar) + "?", "Whatever you want, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hmm, aren't you bothering me, " + GetAddress_Form(NPChar) + "? ", "Again with strange questions? Girl, would you drink rum, or something...") +"", "This is the third time you've been talking about some issue this day..."+ GetSexPhrase("Are these tokens of attention?", "") +"",
                          "Are you going to ask me again, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I have nothing to talk about right now."), "No, no, you're beautiful...",
                      "No way, dear, sclerosis...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "Whisper.FindDesouzaHolWaitress"))
			{
				DeleteAttribute(pchar, "Whisper.FindDesouzaHolWaitress")
				link.l1 = "Your boss, "+GetCharacterFullName("Marigo_tavernkeeper")+", told me that suspicious guys approached you with a crucifix-shaped stamp on your arm. I'm looking for them. Can you tell me more about what they asked?";
				link.l1.go = "FindDesouzaHolWaitress";
				break;
			}
		break;

		case "FindDesouzaHolWaitress":
			dialog.text = "There were such. By the way, they were looking for you too. At least you fit the description they gave me.";
			link.l1 = "Why were they looking for someone like me?";
			link.l1.go = "FindDesouzaHolWaitress_1";
		break;
		case "FindDesouzaHolWaitress_1":
			dialog.text = "Unfortunately, they didn't say that. But they were not only looking for you, they had a list of several dozen people with atypical appearance, most of whom are Spaniards. They said that all these people are criminals and they are wanted. One, as it turned out, had recently been seen in the city, so these branded ones went after him. It was just a couple of hours ago.";
			link.l1 = "And in which direction did they go to look for this guy?";
			link.l1.go = "FindDesouzaHolWaitress_2";
		break;
		case "FindDesouzaHolWaitress_2":
			dialog.text = "Captain, I'm a little uncomfortable with this whole story. Tell me, what are they looking for you for?";
			link.l1 = "I have old scores with them. Their leader is a sadist and a madman. He tortures people for fun. These people are dangerous and they need to be stopped.";
			link.l1.go = "FindDesouzaHolWaitress_3";
		break;
		case "FindDesouzaHolWaitress_3":
			dialog.text = "I still don't understand anything, but for some reason I want to believe you. Eligio didn't look like the dangerous criminal these people described him to either.";
			link.l1 = "Eligio? Is he the one the Inquisitors are looking for?";
			link.l1.go = "FindDesouzaHolWaitress_4";
		break;
		case "FindDesouzaHolWaitress_4":
			dialog.text = "So it was the Inquisitors? Why didn't you say so right away, Captain? These Catholic scum need to be driven out of our Protestant colony with a filthy broom! Inquisitors! Poor Eligio...";
			link.l1 = "Tell me where they went. Maybe I can still save him.";
			link.l1.go = "FindDesouzaHolWaitress_5";
		break;
		case "FindDesouzaHolWaitress_5":
			dialog.text = "One of the guests said that Eligio went to the cave to check the rumors about some treasure.";
			link.l1 = "Thanks for the information, I ran.";
			link.l1.go = "exit";
			PChar.quest.WhisperHuntersCaveEntrance.win_condition.l1 = "location";
			PChar.quest.WhisperHuntersCaveEntrance.win_condition.l1.location = "Marigo_CaveEntrance";
			PChar.quest.WhisperHuntersCaveEntrance.function = "WhisperHuntersCaveEntrance";
			AddQuestRecord("WhisperQuestline", "5");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

