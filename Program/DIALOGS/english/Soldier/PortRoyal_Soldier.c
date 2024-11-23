// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have for a soldier?", "A soldier's life is painted - guards, divorces... Whatever you want, " + GetAddress_Form(NPChar) + "?"), "It is not appropriate to pester a soldier with stupid questions, " + GetAddress_Form(NPChar) + "...", "For the third time today you are trying to ask a question...",
                          "The soldier's share is already difficult, and here you are, "+ GetSexPhrase("bastard, ", " ") +"infuriating...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I have nothing to talk about right now."), "It's not appropriate...",
                      "Yeah, really for the third time...", "I'm sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/*sld = characterFromId("eng_guber");
			if (npchar.location == "PortRoyal_townhall" && pchar.questTemp.State == "" && CheckAttribute(sld, "notQuestLine"))
			{
                dialog.text = "Key! Give me the key!!!";
				link.l1.edit = 7;
				link.l1 = "";
				link.l1.go = "ELOpenKey_1";
			}*/
		break;

		case "ELOpenKey_1":

			if (dialogEditStrings[7] == KEY_ENG_LINE)
			{
				dialog.text = "You know what it's about, your key is accepted. I'll put in a good word for you to Madiford...";
				Link.l1 = "All right, buddy. Thank you...";
				Link.l1.go = "exit";
				sld = characterFromId("eng_guber");
				DeleteAttribute(sld, "notQuestLine");
			}
			else
			{
				dialog.text = "You don't know what it's about. Go away, don't interfere with my duty.";
				Link.l1 = "Hmm, well...";
				Link.l1.go = "exit";
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

