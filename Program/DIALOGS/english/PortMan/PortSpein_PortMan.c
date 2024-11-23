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
			if (checkattribute(pchar, "questTemp.Headhunter") && pchar.questTemp.Headhunter == "Rat" && pchar.questTemp.Headhunter.countP == 0)
			{
				link.l1 = "They say not so long ago, upon leaving your port, that a merchant ship disappeared. Can you tell me more about it?";
				link.l1.go = "Rat_portmanP";
			}
		break;

		//ОЗГ, Крыса
		case "Rat_portmanP":
			dialog.text = "Yes, a disgusting story came out – as I remember now: a whole pinnace loaded with mahogany almost to the brim. His captain was so happy about the successful deal then – he spent the whole evening on the eve of sailing carousing in a tavern and bragging. And then the news came that he had never reached the port where he was heading. They say he was intercepted by some pirates.";
			link.l1 = "Yes, there are plenty of these guys in our waters. Tell me, can't you see which ships were in your port with this ill-fated pinnace?";
			link.l1.go = "Rat_portmanP_1";
		break;

		case "Rat_portmanP_1":
			dialog.text = "Let's take a look. So... that's it. There were ships: the schooner Jenny, the corvette Swift and the pinnace Adelaide.";
			link.l1 = "Thank you!";
			link.l1.go = "CheckP";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countP = 1;
		break;

		case "CheckP":
			if(pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_2");
			}
			DialogExit();
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


