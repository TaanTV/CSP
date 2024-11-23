// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now.");
		    link.l1.go = "exit";
		break;

		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Am I working for a secret agent network for "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "All right... Bye then.";
			link.l1.go = "exit";
			link.l2 = "Then another question";
			link.l2.go = "new question";
		break;

		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "What are you interested in?";

            link.l1 = "Where is the pharmacy located?";
			link.l1.go = "Apteka";
			link.l2 = "Where is the Dutch West India Company located?";
			link.l2.go = "GVIK";
			link.l3 = "I have another question.";
			link.l3.go = "new question";
		break;
		
		case "Apteka":
			dialog.text = "The pharmacy is located next to the embankment next to the tavern and the church. The building is painted in blue and white colors. The main entrance is closed, so it is better to enter from the right side. When you come to the arch, immediately go inside the courtyard, and turn left to the blue door. I hope this information was useful to you.";
            link.l1 = "How did you help me out"+ NPCharSexPhrase(NPChar, "", "a") +"thank you!";
			link.l1.go = "exit";
			link.l2 = "I also wanted to ask you something.";
			link.l2.go = "new question";
		break;
		
		case "GVIK":
			dialog.text = "The Dutch West India Company is located in a large office building, which is painted yellow. There is a huge beautiful clock hanging on one of the towers. There is a well-armed guard at the entrance. I hope this information was useful to you.";
            link.l1 = "How did you help me out"+ NPCharSexPhrase(NPChar, "", "a") +"thank you!";
			link.l1.go = "exit";
			link.l2 = "I also wanted to ask you something.";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

