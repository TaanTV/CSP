// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_PK_IshemKoltso"))	// Квест "The Lost Ring"
            {
                link.l1 = "I'm looking for a ring that belonged to... to one of my friends. Quite a valuable ring. And this ring is located somewhere in this city. Maybe you've heard something about it? A large sapphire set in gold.";
                link.l1.go = "IshemKoltso";
            }
			if(PChar.MysteriousIsland == "10" && PChar.MysteriousIsland.FindForser.Citizen == false)	// Квест "The Mysterious Island"
			{
				link.l1 = "Listen, do you know anything about a certain Captain Davy Forser?";
				link.l1.go = "MysteriousIsland_1";
			}
		break;

		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Am I working for a secret agent network for "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "All right... Bye then.";
			link.l1.go = "exit";
			link.l2 = "Then another question";
			link.l2.go = "new question";
		break;

		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "What do I tell you? I don't know. I don't know anything.";

            link.l1 = "What a fool! Bye.";
			link.l1.go = "exit";
			link.l2 = "Then another question";
			link.l2.go = "new question";
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
					dialog.text = "I have a ring, but it is with a " + LinkRandPhrase("ruby", "emerald", "diamond") + ".";
					link.l1 = "I'm happy for you.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 2)
                {
					dialog.text = "I have more important things to do than respond to such nonsense.";
					link.l1 = "Sorry.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 3)
                {
					dialog.text = "I don't have any rings, sorry.";
					link.l1 = "Okay, I'll ask someone else.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 4)
                {
					dialog.text = "Hmmm... A sapphire, you say? Yes, I remember seeing "+ NPCharSexPhrase(NPChar, "", "a") +" a ring like the one you're talking about. One girl has it-maybe you even know her-at least most sailors know her well. Her name is Francesca. I've never met a dumber girl, to be honest. Some soldier gave her this ring a couple of years ago. Maybe he was even more stupid than she was-because this ring is worth a lot of money. Yes, this is probably the ring you are looking for.";
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
//******************** Квест "The Mysterious Island" ******************		
		case "MysteriousIsland_1":
			PChar.MysteriousIsland.FindForser.Citizen = true;
			dialog.text = "Hmm... No, I don't recall that.";
			link.l1 = "Sorry.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

