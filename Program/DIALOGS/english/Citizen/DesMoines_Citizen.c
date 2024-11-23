// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now.");
		    link.l1.go = "exit";
		break;

		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Am I working for a secret agent network for "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Well, okay... Bye then.";
			link.l1.go = "exit";
			link.l2 = "Then another question.";
			link.l2.go = "new question";
		break;

		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "What do I tell you? I don't know. I don't know anything.";

            link.l1 = "What a fool! Bye.";
			link.l1.go = "exit";
			link.l2 = "Then another question.";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

