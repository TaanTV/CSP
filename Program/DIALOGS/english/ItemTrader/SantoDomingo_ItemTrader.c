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
			if (CheckAttribute(pchar, "questTemp.PDM_PK_IshemKoltso"))	// Квест "The Lost Ring"
            {
                link.l1 = "I'm looking for a ring that belonged to... to one of my friends. Quite a valuable ring. And this ring is located somewhere in this city. Maybe you've heard something about it? A large sapphire set in gold.";
                link.l1.go = "IshemKoltso";
            }
		break;

//******************** Квест "The Lost Ring" ******************
		case "IshemKoltso":
			int Phrase;
                Phrase = rand(4);
                if (Phrase == 0)
                {
					dialog.text = "Who do you think I am, a jeweler? This question is definitely not for me.";
					link.l1 = "Sorry.";
					link.l1.go = "exit";
				break;
				}
                if (Phrase == 1)
                {
					dialog.text = "I have a ring, but it's with a " + LinkRandPhrase("ruby", "emerald", "diamond") + ".";
					link.l1 = "I'm happy for you.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 2)
                {
					dialog.text = "I don't sell rings.";
					link.l1 = "Sorry.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 3)
                {
					dialog.text = "I don't have any rings, sorry.";
					link.l1 = "Okay, I'll look somewhere else.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 4)
                {
					dialog.text = "Hmmm... A sapphire, you say? Yes, I remember seeing "+ NPCharSexPhrase(NPChar, "", "a") +" a ring like the one you're talking about. One girl has it-maybe you even know her-at least most sailors know her well. Her name is Francesca. I've never met a dumber girl, to be honest. Some soldier gave her this ring a couple of years ago. Maybe he was even more stupid than she was, because this ring is worth a lot of money. Yes, this is probably the ring you are looking for.";
					link.l1 = "Thank you, " + npchar.name+", you have no idea how you helped me out. See you later.";
					link.l1.go = "exit";

					AddQuestRecord("PDM_Poteryanoe_Koltso", "3");
					AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "a"));
					DeleteAttribute(pchar, "questTemp.PDM_PK_IshemKoltso");

					sld = GetCharacter(NPC_GenerateCharacter("PDM_PK_Francheska", "BaynesDaughterSTOK", "woman", "woman", 10, SPAIN, -1, false));
					sld.name = "Francesca";
					sld.lastname = "";
					sld.city = "SantoDomingo";
					sld.location	= "SantoDomingo_Brothel";
					sld.location.group = "goto";
					sld.location.locator = "goto3";
					sld.dialog.filename   = "Quest\PDM\Poteryanoe_Koltso.c";
					sld.dialog.currentnode   = "Francheska";
					LAi_SetCitizenType(sld);
					LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
					LAi_SetImmortal(sld, true);
				break;
				}
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

