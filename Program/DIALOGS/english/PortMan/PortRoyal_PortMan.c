// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Listen, if you're not on port business, then don't bother me with questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yeah, really for the third time...", "Sorry, but I'm not interested in port affairs right now.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> квест №6 англ.линейки, базар о пинасе
            if (pchar.questTemp.State == "MorrisWillams_SeekSpanishGoods")
            {
    			link.l1 = "Listen, have you had any Spaniards in the port lately?";
    			link.l1.go = "Step_E6_1";
            }

			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Good afternoon. Have you checked in with Captain Francois Gontier, who arrived from Porto Bello? He has a corvette named '" + pchar.questTemp.Slavetrader.ShipName + "'.";
                link.l1.go = "Jamaica_ratPP_1";
            }

		break;
//************************************* Диалоги по англ.линейке *******************************
		case "Step_E6_1":
            dialog.text = "The Spaniard is a rare guest here. But one has definitely anchored here quite recently, and under the protection of garrison soldiers.";
			link.l1 = "Wow! Why would English soldiers guard a Spanish ship?";
			link.l1.go = "Step_E6_2";
		break;

		case "Step_E6_2":
            dialog.text = "Yes, the devil knows, it must be an order from the Governor-General.";
			link.l1 = "Where is this Spaniard now? And what kind of ship?";
			link.l1.go = "Step_E6_3";
		break;

		case "Step_E6_3":
            dialog.text = "Pinnace Santa Agueda, left yesterday with a fair wind heading for San Juan. What about the Spaniard?";
			link.l1 = "I want to see captain, he owes me...";
			link.l1.go = "Step_E6_4";
		break;

		case "Step_E6_4":
            dialog.text = "Heh, good... But keep in mind that the wind has been preserved. If you want to see the stern of the pinnace to San Juan, you need to go to sea right now. And whether you will catch up is a big question...";
			link.l1 = "I'll try anyway. Goodbye and be healthy.";
			link.l1.go = "exit";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "9");
			pchar.questTemp.State = "MorrisWillams_CatchUpPinnace";
            SaveCurrentQuestDateParam("questTemp");
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition.l1 = "location";
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition.l1.location = "Jamaica";
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition = "MorrisWillams_CheckTimeForForward";
		break;

		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("No. Francois Gontier was not registered, and the corvette '" + pchar.questTemp.Slavetrader.ShipName + "' has not entered the port of Port Royal.", "You have already"+ GetSexPhrase("asked", "asked") +"about that, I answered you.", "I'm telling you, you already"+ GetSexPhrase("asked", "asked") +"about this Gontier.", "I ask you not to interfere with my work!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I see. We'll keep looking...", "Hmm, well, yes...", "Yes, that's right, "+ GetSexPhrase("I asked", "I asked") +"...", "I'm sorry, " + npchar.name + "...", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

