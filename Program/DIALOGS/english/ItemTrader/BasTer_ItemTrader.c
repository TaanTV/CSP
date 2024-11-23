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
			if (pchar.questTemp.PDM_PK_UznatLichnost == "UznatLichnost")	// Квест "The Lost Ring"
            {
                link.l1 = "Tell me about a strange woman who lost her ring. Do you know her?";
                link.l1.go = "PDM_PK_UznatLichnost";
            }
		break;

//**************************Квест "The Lost Ring"*******************************
		case "PDM_PK_UznatLichnost":
			int Phrase;
                Phrase = rand(4);
                if (Phrase == 0)
                {
					dialog.text = "She's just crazy, don't pay attention to her.";
					link.l1 = "Okay.";
					link.l1.go = "exit";
				break;
				}
                if (Phrase == 1)
                {
					dialog.text = "And why did you give up this crazy woman? You'd better buy something from me.";
					link.l1 = "Sorry.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 2)
                {
					dialog.text = "I "+ GetSexPhrase("seller", "saleswoman") +", not a rumor purveyor.";
					link.l1 = "Sorry.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 3)
                {
					dialog.text = "I do not know her, sorry.";
					link.l1 = "Okay, I'll ask someone else.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 4)
                {
					dialog.text = "She didn't just lose the ring. It's a terrible story. It breaks my heart when I tell it. Her name is Josephine Lodet. She gave her son a magnificent ring on the day before his first trip. For luck, she said. He participated in the attack on Santo Domingo and was killed in the first battle. When the news of his death reached our shores, poor Josephine... Well, you have eyes, so you saw what happened to her.";
					link.l1 = "What kind of ring was that?";
					link.l1.go = "PDM_PK_UznatLichnost_2";
				break;
				}
        break;

		case "PDM_PK_UznatLichnost_2":
			dialog.text = "A very beautiful and very expensive piece of jewelry. The most beautiful sapphire I have ever seen, set in gold. Her grandfather brought him here from Europe. I'm not a jeweler, but it could have been priced at ten... or twenty thousand? Ah, a terrible story! Okay, good luck to you!";
			Link.l1 = "Thank you, " + npchar.name+". You've been very helpful. Goodbye.";
			Link.l1.go = "exit";

			sld = CharacterFromID("Josephine_Lodet")
			sld.name = "Josephine";
			sld.lastname = "Lodet";

			AddQuestRecord("PDM_Poteryanoe_Koltso", "2");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "a"));

			pchar.questTemp.PDM_PK_IshemKoltso = "IshemKoltso";
			DeleteAttribute(pchar, "questTemp.PDM_PK_UznatLichnost");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

