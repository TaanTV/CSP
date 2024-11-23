// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Quite recently you tried to ask me a question...", "At my shipyard, and in general in the city, I have not seen such monotonously inquisitive people.",
                          "Well, what kind of questions? My job is to build ships, let's do it.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Hmm, however...", "Let's...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toSantoDomingo")
			{
				link.l1 = "I was told that you have the schooner Swallow for sale, is that so?";
				link.l1.go = "PL_Q7_1";
			}
			if(PChar.MysteriousIsland == "10" && NPChar.City == "SantoDomingo")	//Загадочный остров
			{
				link.l1 = "Did Captain Davy Forser contact you?";
				link.l1.go = "MysteriousIsland_1";
			}
		break;
		//пиратка, квест №7
		case "PL_Q7_1":
			dialog.text = "No, it's not like that. Not for sale, but already sold. A buyer came and I liked him so much that I gave him this schooner literally for pennies...";
			link.l1 = "I'm not interested in the buyer, but the seller. Who sold you the schooner?";
			link.l1.go = "PL_Q7_2";
		break;
		case "PL_Q7_2":
			dialog.text = "Sold? Sold out... Some man sold it...";
			link.l1 = "Yes, I understand that it is not a horse. Who is this man, what is his name?";
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = "I don't know your name, I was looking at the ship more...";
			link.l1 = "Don't get dark, buddy, this could end badly for you.";
			link.l1.go = "PL_Q7_4";
		break;
		case "PL_Q7_4":
			dialog.text = "Damn! I knew that this purchase could go sideways for me. But a very good price was offered... I immediately suspected that something was wrong here, but hoped I was wrong.";
			link.l1 = "Most likely, you are not mistaken. Where can I find a seller?";
			link.l1.go = "PL_Q7_5";
		break;
		case "PL_Q7_5":
			dialog.text = "In the sea. Yesterday he went to sea on the frigate Leon, as far as I know. I didn't see the frigate myself. This guy was very cautious, but one of my workers saw him and told me.His food is somewhere off the coast of Hispaniola. I don't think he got very far.";
			link.l1 = "Thank you. We will look for it.";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_seekLeon";
			AddQuestRecord("Pir_Line_7_Soukins", "6");
			AddDialogExitQuestFunction("PQ7_LoginLeon");
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_LeonNotFound"); //нода, ничего не узнал
		break;
		
		// Загадочный остров -->
		case "MysteriousIsland_1":
			dialog.text = "Well, I've known Davy for a long time. He took his galleon from me just yesterday after strengthening the sailing equipment. He mentioned that he was going to La Vega, I remember exactly because I was surprised by this fact. You can get to La Vega on foot, why does he need such sails?!";
			link.l1 = "Thank you, you helped me a lot.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MysteriousIslandToLaVega");
		break;
		// Загадочный остров <--
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

