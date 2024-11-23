// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "Whatever you want, " + GetAddress_Form(NPChar) + "?"), "More questions, " + GetAddress_Form(NPChar) + "...", "Questions, questions... Maybe we'll do some trading, " + GetAddress_Form(NPChar) + "?",
                          "Listen, how many empty conversations can you have?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("No questions...", "I have nothing to talk about right now."), "Eh, again...",
                      "Yes, it's really better to bargain...", "Hmm, sorry, trader...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Beliz"))	// Квест "Witch Hunt"
            {
    			link.l1 = RandPhraseSimple("Excuse me, have you seen Maria?", "Do you know where Maria is?");
    			link.l1.go = "PDM_ONV_Prodavec";
			}
		break;
		
//**************************Квест "Witch Hunt"*******************************
		case "PDM_ONV_Prodavec":
			dialog.text = dialog.text = RandPhraseSimple("I "+ GetSexPhrase("seller", "saleswoman") +", and not a supplier of rumors.", "Will you buy or just grind your tongue?", "Maria? No, I sell fruit. Buy a fruit, preferably two.");
			link.l1 = "Sorry.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

