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
			//ОЗГ, Крыса
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
    			if (pchar.questTemp.Headhunter == "Rat" && pchar.questTemp.Headhunter.countC == 0)
	    		{
		    		link.l1 = "I heard not so long ago, on leaving your port, that a merchant ship disappeared. Can you tell me more about it?";
			    	link.l1.go = "Rat_portmanC";
	    		}
			}
		break;

		//ОЗГ, Крыса
		case "Rat_portmanC":
			dialog.text = "What's there to tell. I loaded up in our Happy Bride fluyt store with sandal to the brim, went to sea - but did not come to the destination port. I've seen a lot of such stories in my service, and it doesn't surprise me.";
			link.l1 = "Can you tell me which ships, other than the Happy Bride, left the harbor at the same time?";
			link.l1.go = "Rat_portmanC_1";
		break;

		case "Rat_portmanC_1":
			dialog.text = "I'll tell you, of course. Now, let's look at the recordings... The galleon San Juan Nepomacedo and the pinnace Adelaide.";
			link.l1 = "Thank you!";
			link.l1.go = "CheckC";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countC = 1;
		break;

		case "CheckC":
			if(pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_1");
			}
			DialogExit();
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


