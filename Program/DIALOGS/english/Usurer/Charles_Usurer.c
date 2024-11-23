// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Just recently you tried to ask me a question...", "Well, let me guess... Nothing significant again?",
                          "Listen, I'm handling finances, not answering questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "You guessed it, I'm sorry...", "I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> Квест Аззи
			if (CheckAttribute(pchar, "questTemp.Azzy.GiveMoney"))
            {
                link.l5 = "I'm here on behalf of Azzi. You must have something prepared for me.";
                link.l5.go = "Step_Az_1";
            }
			if (!CheckAttribute(pchar, "questTemp.Azzy.GiveMoney") && pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
                link.l5 = "Listen, I need to find Azzi urgently.";
                link.l5.go = "Step_Az_4";
            }
		break;
        // ==> Квест Аззи. Дача трёх лимонов ГГ по поручению Аззи.
		case "Step_Az_1":
			dialog.text = "All right. Three million in cash are waiting for you, " + GetAddress_Form(NPChar) + ". Would you like to receive it right now?";
			Link.l1 = "Yes, and the whole amount.";
			Link.l1.go = "Step_Az_2";
		break;
		case "Step_Az_2":
			dialog.text = "Please, " + GetAddress_Form(NPChar) + ". Is there anything else?";
			Link.l1 = "No, nothing is needed... Listen, what's your deal with this Azzie? So, for the sake of interest, I'm asking...";
			Link.l1.go = "Step_Az_3";
            DeleteAttribute(pchar, "questTemp.Azzy.GiveMoney");
            AddMoneyToCharacter(pchar, 3000000);
		break;
		case "Step_Az_3":
			dialog.text = ""+ GetSexPhrase("Sir", "Miss") +", I advise you not to be too curious. With Azzie, it's life-threatening. If that's all, then let me go about my business...";
			Link.l1 = "Yes, of course! Thanks for the money.";
			Link.l1.go = "exit";
		break;
		case "Step_Az_4":
            dialog.text = NPCStringReactionRepeat("Do you need Azzi? I don't advise you to look for him. I've already told you that it's life-threatening.", "I don't want to talk about it anymore.", "No, I've had enough...", "I won't talk.", "block", 0, npchar, Dialog.CurrentNode);
			Link.l1 = HeroStringReactionRepeat("It's about my life. I need it, if you know how to find it, then please tell me.", "I understand...", "I'm sorry...", "Well, then you really have nothing to say.", npchar, Dialog.CurrentNode);
			Link.l1.go = DialogGoNodeRepeat("Step_Az_5", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_Az_5":
			dialog.text = "Unfortunately, I do not know. I have no idea\n"+
                     "You know, I took these five million without really thinking about the consequences. Yes, exactly five, since two of them were intended for me as payment for my work\n"+
                     "So these two million, a huge sum, literally ruined me. I don't want to go into the intricacies of financial transactions, but trust me - it's not clean here\n"+
                     "I've always considered myself very perceptive. But how could I not guess here - I don't know.";
			Link.l1 = "Everything is clear... Thank you.";
			Link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

