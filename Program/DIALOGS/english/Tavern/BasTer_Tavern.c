// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "Whatever you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question, " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Are we going to ask questions again?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yes, really for the third time...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_PK_UznatLichnost"))	// Квест "The Lost Ring"
            {
                link.l1 = "Tell me about a strange woman who lost her ring. Do you know her?";
                link.l1.go = "PDM_PK_UznatLichnost";
            }
		break;
//******************** квест "The Lost Ring" ******************
		case "PDM_PK_UznatLichnost":
			dialog.text = "She didn't just lose the ring. It's a terrible story. It breaks my heart when I tell it. Her name is Josephine Lodet. She gave her son a magnificent ring on the day before his first trip. For luck, she said. He participated in the attack on Santo Domingo and was killed in the first battle. When the news of his death reached our shores, poor Josephine... Well, you have eyes, so you saw what happened to her.",
			link.l1 = "What kind of ring was that?";
			link.l1.go = "PDM_PK_UznatLichnost_2";
        break;

		case "PDM_PK_UznatLichnost_2":
			dialog.text = "A very beautiful and very expensive piece of jewelry. The most beautiful sapphire I've ever seen, set in gold. Her grandfather brought him here from Europe. I'm not a jeweler, but it could have been priced at ten... or twenty thousand? Ah, a terrible story! Let's talk about something else. Or would you like a drink?";
			Link.l1 = "I'd better go, " + npchar.name+". We'll talk another time.";
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

