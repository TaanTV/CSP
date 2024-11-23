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
            // ==> квест №5 голл.линейки, забрать три флейта.
            if (pchar.questTemp.State == "ThreeFleutes_toPortMan")
            {
    			link.l1 = "I'm here on behalf of Stuyvesant. I need to take command of three flutes.";
    			link.l1.go = "Step_H5_1";
            }
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "I would like to know about the bark that disappeared the night after the slave uprising.";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			//ОЗГ, Крыса
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
    			if (pchar.questTemp.Headhunter == "Rat" && pchar.questTemp.Headhunter.countV == 0)
    			{
    				link.l1 = "I heard, recently, upon leaving your port, that a merchant ship disappeared. Can you tell me more about it?";
	    			link.l1.go = "Rat_portmanV";
	    		}
			}
		break;

//************************************* Диалоги по голл.линейке *******************************
		case "Step_H5_1":
    		if (GetCompanionQuantity(pchar) == 1)
            {
                dialog.text = "Please accept. Three flutes are at your disposal.";
    			link.l1 = "Great.";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("HL5_portManGiveFleuts");
            }
            else
            {
                dialog.text = "Yes, I am aware of this issue. However, to take command of the flutes, you need to get rid of your squadron. I ask you to do this and then contact me again.";
    			link.l1 = "Okay, I'll do that.";
    			link.l1.go = "exit";
            }
		break;
		//работорговец
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "Hmm... And why on earth are you suddenly interested in this?";
				link.l1 = "I am acting on the instructions of Peter Stevesant, Governor General. There is reason to believe that runaway slaves were involved in the disappearance of the ship. Therefore, I ask you to provide me with all possible assistance in the search.";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;

		case "EscapeSlave_Villemstad_P2":
				dialog.text = "Understood. But unfortunately, there's not much I can do to help you. A bark named " + pchar.questTemp.Slavetrader.ShipName + "disappeared at night, nobody saw or heard anything. The watchman disappeared without a trace\nThe search for the ship turned up nothing, actually, because there was no trace. The town was agitated, all expecting a slave attack, preparing to defend themselves...";
				link.l1 = "Yes, there really isn't much information. But thanks for that, too. Goodbye.";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;

		//ОЗГ, Крыса
		case "Rat_portmanV":
			dialog.text = "Yes, a couple of weeks ago, or so, the heavy galleon Santa Anna left the harbor, and, as they say, did not arrive at the specified point. No one else has seen him, but why are you interested in this?";
			link.l1 = "This is, let's say, a private interest. Do you remember any details?";
			link.l1.go = "Rat_portmanV_1";
		break;

		case "Rat_portmanV_1":
			dialog.text = "What can I remember, wait a minute... Yes, here is the entry – the heavy galleon Santa Anna sailed with a cargo of ebony on board, more than six hundred units. So... He did not show up at the destination port. That seems to be it.";
			link.l1 = "Tell me, which ships left the harbor on the same day, or a day later than this galleon?";
			link.l1.go = "Rat_portmanV_2";
		break;

		case "Rat_portmanV_2":
			dialog.text = "Let's take a look. On that day, the ships left the port: the pinnace Adelaide, the galleon Medemblink and the frigate Zultchen.";
			link.l1 = "Thank you!";
			link.l1.go = "CheckV";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countV = 1;
		break;

		case "CheckV":
			if(pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_3");
			}
			DialogExit();
		break;



	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

