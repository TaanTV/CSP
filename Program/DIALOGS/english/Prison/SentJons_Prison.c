// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I'm listening.";
			link.l1 = "I "+ GetSexPhrase("wrong", "wrong") +". Goodbye.";
			link.l1.go = "Exit";
			// ==> Проверяем поле состояния квестов.
            if (pchar.questTemp.State == "WormEnglPlans_SaveOfficer")   // разговор по квест №3 голландской линейке.
            {
    			link.l2 = "I want to see Lieutenant Alan McLane.";
    			link.l2.go = "Step_H3_1";
            }
             // <== Проверяем поле состояния квестов.
		break;

        case "Step_H3_1":
            dialog.text = "It's impossible.";
			link.l1 = "Anything is possible, but for this we will have to kill you all. Ready to fight!";
			link.l1.go = "fight";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

