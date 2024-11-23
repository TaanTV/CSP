// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I'm listening.";
			link.l1 = "I "+ GetSexPhrase("wrong", "wrong") +". Goodbye.";
			link.l1.go = "Exit";
            if (pchar.questTemp.State == "MorrisWillams_ArrestedToPrison")   // разговор по шестому квесту англ.линейки
            {
    			link.l2 = "Lieutenant, I won't beat around the bush. I want prisoner Morris Williams to be free.";
    			link.l2.go = "Step_E6_1";
            }
            if (pchar.questTemp.State == "SaveFromMorgan_toPrison")   // испанка, квест №1
            {
    			link.l2 = "Officer, I know that you have three Spaniards in custody, it seems that Morgan captured them.";
    			link.l2.go = "Step_S1_1";
            }
		break;

        case "Step_E6_1":
            dialog.text = "Hmm... Well, I appreciate your frankness. I confess that I also do not like the arrest and detention of a gentleman\n"+
                          "But I am a military man and I will not violate the order under any circumstances. I advise you to contact the Governor General and wish you good luck.";
			link.l1 = "Why the Governor-General?";
			link.l1.go = "Step_E6_2";
		break;
        case "Step_E6_2":
            dialog.text = "Because Morris Williams was arrested on his written order.";
			link.l1 = "Understood... Tell me, Lieutenant, can I talk to Williams?";
			link.l1.go = "Step_E6_3";
		break;
        case "Step_E6_3":
            dialog.text = "I think so. Only right now, not later. And be laconic.";
			link.l1 = "Thank you, Lieutenant.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			pchar.questTemp.State = "MorrisWillams_ArrestedToModiford";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "16");
		break;

        case "Step_S1_1":
            dialog.text = "So what?";
			link.l1 = "Nothing special. I just want to give them freedom.";
			link.l1.go = "Step_S1_2";
		break;
        case "Step_S1_2":
            dialog.text = "This issue is outside my area of expertise.";
			link.l1 = "And I think you should be extremely interested in this. Otherwise, I will kill you.";
			link.l1.go = "Step_S1_3";
		break;
        case "Step_S1_3":
            dialog.text = "The world has never seen such arrogance. Take "+ GetSexPhrase("his", "her") +"!!";
			link.l1 = "Well, you asked for it...";
			link.l1.go = "fight";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

