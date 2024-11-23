// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Ask, what do you want?",
                          "We have just raised this issue. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Listen, this is a store, people are buying something here. Don't distract me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Um, I won't...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> проверка на квесты
			if (CheckAttribute(pchar, "questTemp.State.Store"))
            {
                link.l1 = "Listen, I'm looking for a merchant named Jacob Lopez de Fonseca. He went here on business, but he hasn't come back yet.";
                link.l1.go = "Step_S2_1";
            }
            // <== проверка на квесты

		break;
//*************************** Квест №2 испанки, задание Инквизиции ***************************
 		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat("I saw it about a month ago. I must say, it was a strange meeting. In the morning I met Yakov on the street, we greeted him, and he said that he would come by for lunch on business. But I haven't had it since.",
                                                  "You've already "+ GetSexPhrase("asked", "asked") +"about that, I answered you.", "I'm telling you, you already"+ GetSexPhrase("asked", "asked") +"about this Yakov.", "Listen, step back and don't interfere! Are you screw loose?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("And he didn't say anything in more detail: where did he stop, where is he going?", "Hmm, well...", "Yes, exactly, "+ GetSexPhrase("asked", "asked") +"...", "Sorry, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S2_2":
			dialog.text = "No, nothing.";
			link.l1 = "Understood... Thank you.";
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_2_Inquisition", "11");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

