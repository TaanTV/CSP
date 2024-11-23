// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, " + GetAddress_Form(NPChar) + "?", "Whatever you want, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hmm, aren't you bothering me, " + GetAddress_Form(NPChar) + "? ", "Again with strange questions? Girl, would you drink rum, or something...") +"", "This is the third time you've been talking about some issue this day..."+ GetSexPhrase("Are these tokens of attention?", "") +"",
                          "Are you going to ask me again, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I have nothing to talk about right now."), "No, no, you're beautiful...",
                      "No way, dear, sclerosis...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Oficiantka_Beliz"))	// Квест "Witch Hunt"
			{
				link.l1 = "Do you know where Maria is now?";
				link.l1.go = "PDM_ONV_WOMAN";
			}
		break;
		
//========================== Квест "Witch Hunt" ==================================
		case "PDM_ONV_WOMAN":
			dialog.text = "Uh... no. It is better to ask the city residents. I think they will definitely say something.");
			link.l1 = "Okay, beauty, I'll go.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Oficiantka_Beliz");
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

