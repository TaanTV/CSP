// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question, " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Are we going to ask questions again?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yes, really for the third time...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "toMaracaibo")
			{
				link.l1 = "I want to find out something.";
				link.l1.go = "MCTavernMar";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_ONV_Maracaibo"))	//Квест "Witch Hunt"
            {
                link.l1 = "Does the name Maria Carle mean anything to you?";
                link.l1.go = "PDM_ONV_MB_1";
            }
		break;
		//зачарованный город
		case "MCTavernMar":
			dialog.text = "What exactly are you interested in?";
			link.l1 = "They say that Maracaibo has fallen under some kind of curse. What happened here?";
			link.l1.go = "MCTavernMar_1";
		break;
		case "MCTavernMar_1":
			dialog.text = "Maracaibo? As you can see, everything is fine with us. There is, however, Des Moines, but it is such a backwater that nothing ever happens there. Although it's strange – usually I have two or three fishermen from there in my tavern, but no one has appeared here for a long time.";
			link.l1 = "Well, there's not much information, but thanks for that.";
			link.l1.go = "exit";
			pchar.questTemp.MC = "toDesMoines";
		break;
		//Квест ***Охота на ведьму***
		case "PDM_ONV_MB_1":
			dialog.text = "This name doesn't mean anything to me. But you're lucky, that man at the table said that name more than once when he was swallowing rum in a frenzied rage.";
			link.l1 = "How did you help me out. Thank you!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Maracaibo");
			if(InterfaceStates.EnabledQuestsMarks)
			{
				sld = CharacterFromID("PDM_ONV_Viktor_Martos");
				sld.quest.questflag.model = "questionmarkY";
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

