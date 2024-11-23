// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, "+ GetSexPhrase("my son", "my daughter") +"?", "Ask, I'm listening to you..."), "I'm listening to you, tell me, "+ GetSexPhrase("my son", "my daughter") +"...", "And for the third time I tell you, "+ GetSexPhrase("my son", "my daughter") +"mine: ask your question.",
                          "A clergyman has so many responsibilities, and then you're bothering, "+ GetSexPhrase("my son", "my daughter") +"my...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "Not now, Padre..."), "Yes, there's not much to say yet...",
                      "I'll ask, I'll ask... Only later...", "Excuse me, Holy Father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Inquisition_toDeSouza")
            {
                link.l1 = "Father, tell me, where can I find Senor Antonio de Souza?";
                link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
            {
                link.l1 = "Father, tell me, where is the Inquisition here?";
                link.l1.go = "Step_F7_1";
            }
		break;
        case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat("Do you know, "+ GetSexPhrase("my son", "my daughter") +", who is this?", ""+ GetSexPhrase("My son", "My daughter") +", I've already told you everything.", "Are you asking the same question again? I've already answered you...", "Again? Okay, the entrance to the Inquisition is right up the stairs leading to the church...",  "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Of course, he's a high-ranking inquisitor.", "Sorry, Padre, I dont really understand... Okay...", "Yes, but I didnt understand... Hmm, sorry, Padre...", "Uh, thanks, Padre...", npchar, Dialog.CurrentNode);
			link.l1.go = "Step_S2_2";
		break;
        case "Step_S2_2":
			dialog.text = "True... Well, he's at his residence.";
			link.l1 = "Excuse me, Padre, but where is it, the residence of the Inquisition?";
			link.l1.go = "Step_S2_3";
		break;
        case "Step_S2_3":
			dialog.text = "Right under the church.";
			link.l1 = "How is it?";
			link.l1.go = "Step_S2_4";
		break;
        case "Step_S2_4":
			dialog.text = "That's it... Go, "+ GetSexPhrase("my son", "my daughter") +", go. Few people voluntarily go to the Holy Inquisition...";
			link.l1 = "Ah, well...";
			link.l1.go = "exit";
		break;

        case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat("Right under the church, "+ GetSexPhrase("my son", "my daughter") +".", "Right under our church, "+ GetSexPhrase("my son", "my daughter") +". The entrance is under the stairs.", "You're completely "+ GetSexPhrase("hard of hearing, my son", "hard of hearing, my daughter") +". Oh, you need to be treated...",
                          "Humility...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thank you, Padre.", "Thank you again, Padre.",
                      "Absolutely!", "What?", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

