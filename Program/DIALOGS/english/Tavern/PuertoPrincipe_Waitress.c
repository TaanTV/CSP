// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, " + GetAddress_Form(NPChar) + "?", "Whatever you want, " + GetAddress_Form(NPChar) + "?"), "Hmm, aren't you bothering me, " + GetAddress_Form(NPChar) + "? Again with strange questions...", "This is the third time you have been talking about a question this day... Are these tokens of attention?",
                          "Are you going to ask me again, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind..", "I have nothing to talk about right now."), "No, no, you're beautiful...",
                      "No way, dear, sclerosis...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = "Listen, "+ GetSexPhrase("beauty", "baby") +", I need to know what Sawkins is up to. I really need to...";
				link.l1.go = "PL_Q7_1";
			}
			if (pchar.questTemp.piratesLine == "Soukins_seekRings" && CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry7"))
			{
				link.l1 = "I "+ GetSexPhrase("brought", "brought") +" what you wanted. Here are your rings.";
				link.l1.go = "PL_Q7_3";
			}
		break;
		case "PL_Q7_1":
			dialog.text = "Bring me a ring with emerald and a ring with ruby. And then maybe I can help you...";
			link.l1 = "I don't have them...";
			link.l1.go = "PL_Q7_2";
			pchar.questTemp.piratesLine = "Soukins_seekRings";
			if (CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry7"))
            {
				link.l2 = "Here are your rings, darling...";
				link.l2.go = "PL_Q7_3";
			}
		break;
		case "PL_Q7_2":
			dialog.text = "I'm sorry, but this is my categorical condition.";
			link.l1 = "I see...";
			link.l1.go = "exit";
		break;
		case "PL_Q7_3":
			dialog.text = "Mmm, how beautiful!.. Thank you. So, what you wanted to know?";
			link.l1 = "I need to know what Richard Sawkins is up to. Are you aware of that?";
			link.l1.go = "PL_Q7_4";
			TakeItemFromCharacter(pchar, "jewelry7");
			TakeItemFromCharacter(pchar, "jewelry18");
		break;
		case "PL_Q7_4":
			dialog.text = "No.";
			link.l1 = "So what the hell are you messing with my head for?!!";
			link.l1.go = "PL_Q7_5";
		break;
		case "PL_Q7_5":
			dialog.text = "I'm telling you, I know how to find out. So, listen carefully. Richard is a meticulous man, he writes everything down in his logbook. You need to get it, that's all.";
			link.l1 = "Ha! Can you tell me how to do it?";
			link.l1.go = "PL_Q7_6";
		break;
		case "PL_Q7_6":
			dialog.text = "I'll tell you. Take the magazine from his residence. He stays there all the time during the day, so you won't leave alive if you dare to take the magazine. But at night...";
			link.l1 = "So everything is closed at night!";
			link.l1.go = "PL_Q7_7";
		break;
		case "PL_Q7_7":
			dialog.text = "Climb through the window at the back of the house. Only you'll need a ladder to climb up.";
			link.l1 = "And where can I get it?";
			link.l1.go = "PL_Q7_8";
		break;
		case "PL_Q7_8":
			dialog.text = "I don't know...";
			link.l1 = "Hmm, well, thanks for that too.";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_toWindow";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

