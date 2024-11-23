// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Ask, what do you want?",
                          "We have just raised this issue. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Listen, this is a store, people are buying something here. Don't distract me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Um, I won't...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			if(CheckAttribute(pchar, "questTemp.BlueBird"))
			{
				if (pchar.questTemp.BlueBird == "toBermudes")
				{
					link.l1 = "Dear, I am looking for an unusual ship, the xebec Blue Bird. Have you heard anything about her? For any information about her, I'm ready to pay...";
					link.l1.go = "BlueBird_1";
				}
				bOk = pchar.questTemp.BlueBird == "weWon" || pchar.questTemp.BlueBird == "returnMoney" || pchar.questTemp.BlueBird == "over";
	    		if (bOk && !CheckAttribute(pchar, "questTemp.BlueBird.speakWon"))
    			{
		    		link.l1 = "Where is Pascal Voisier?";
	    			link.l1.go = "BlueBird_3";
    			}
			}
			if (bBettaTestMode)
			{
				link.l5 = "WAREHOUSE RENTAL";
				link.l5.go = "storage_rent1";
			}
		break;
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat("I don't know anything about this ship. If that's all you wanted, then leave.",
				"Again? I've told you everything.",
				"What, the same thing again?",
                "But when will it end?! Please don't distract me from my work!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You're not very kind, my dear!",
				"Yes, yes, I remember...",
                "Yeah.",
				"Okay, Okay...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;
		case "BlueBird_2":
			dialog.text = "I'm not your sweetest, I didn't have the pleasure of whipping rum and lying under the fence with you.";
			link.l1 = "Son of a bitch...(silently). I just asked. Well, thank you!";
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "2");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("xia", "as"));
		break;

		case "BlueBird_3":
			if ( sti(pchar.Ship.Type) == SHIP_NOTUSED || pchar.location.from_sea != "Pirates_town")
			{
				dialog.text = "He sailed off the island without explanation. It is rumored that he was involved in the story of the xebec 'Blue Bird'.";
				link.l1 = "I know about this story.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "He sailed off the island without explanation. It is rumored that he was involved in the story of the xebec 'Blue Bird'. I have a tempting offer for you. You may be interested in it.";
				link.l1 = "Is that so? Well, state your tempting offer.";
				link.l1.go = "storage_rent";
			}
			pchar.questTemp.BlueBird.speakWon = true;
		break;

		case "storage_rent":
			dialog.text = "After the well-known events, we have freed up areas suitable for storage. Don't you want to rent for a reasonable fee? You'll get your own warehouse...";
			link.l1 = "Warehouse, you say? It's tempting... Is he big? and how much will you ask for the rent?";
			link.l1.go = "storage_rent1";
		break;

		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			dialog.text = "It is spacious enough even for a port warehouse - capacity of 50000 centners. For " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + " per month I am ready to ensure the safety of your goods. "+
				"This includes security services, flood protection and rodent control. Is it okay? Well, I guarantee confidentiality, of course.";
			link.l1 = "Good. May I examine him?";
			link.l1.go = "storage_rent2";
			link.l2 = "Ask too much. There's probably knee-deep water and rats running around.";
			link.l2.go = "storage_rent3";
		break;

		case "storage_rent2":
			dialog.text = "Of course, of course. Only, uh... I'll ask for the payment for the month in advance.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "What are you... mercantile. Keep your money-I'm renting this barn.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "What are you... mercantile. I'll get the money now.";
				link.l1.go = "exit";
			}
		break;

		case "storage_rent3":
			dialog.text = "Well, as you know. If you decide to, please contact us. Just keep in mind that such a treasure will not be empty for a long time. No matter how late you are.";
			link.l1 = "Don't worry. If necessary, I'll ask.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

