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
			if (CheckAttribute(PChar, "BSSentJonsWaitress"))
			{			
				link.l1 = "Honey, have you seen my friend around here? He's a big fisherman, we had a drink here a while back?";
				link.l1.go = "BS_F3_24";
			}
		break;
		
		case "BS_F3_24":
			DeleteAttribute(PChar, "BSSentJonsWaitress");
			AddMoneyToCharacter(pchar, -500);
			SetFunctionLocationCondition("BS_BonsDominicaMeeting", "Dominica", false);
			AddQuestRecord("BSHangover", "62");
			dialog.text = "Hunting for big fish? He said to tell you that another fisherman will be waiting for you in Dominica waters off Castle Brush Beach.";
			link.l1 = "Thank you. Here's one for, uh, something pretty!"; //Отдаём 500 рублей
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
