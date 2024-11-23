// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What did you want? Ask.", "I'm listening to you, what's the question?"), "For the second time in a day you're trying to ask a question...", "For the third time in a day you're trying to ask a question again...",
                          "But when will it end?! I have a lot of things to do to manage the affairs of the city, and you're trying to ask all the questions!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, not the place and not the time..."), "Yes, that's right... But not now, later...",
                      "I will ask, I will ask... Only later...", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr4SoleiRoyal_GoodWork")
			{
				dialog.text = "I'm listening to you, Captain.";
				link.l1 = "Sir, I have been instructed by the Governor-General of Tortuga to escort the first-class battleship Soleil Royal to the island of Dominica. The Guadeloupe squadron was supposed to be waiting for me there, but it wasn't there. Is there any way you can clarify the situation?";
				link.l1.go = "Step_F4_1";
			}
		break;
		//************************** Фр.линкейка, квест №4. Солей Руаяль ************************
		case "Step_F4_1":
            dialog.text = "The fact is that I received an order to move the squadron to Dominica only yesterday - the courier was very late. Thus, I did not have time to prepare the squadron. I believe that you are from Dominica...";
			link.l1 = "True. I had to take on the Spanish squadron of a certain Juan Galeno. He tracked down and tried to capture the Soleil Royal.";
            link.l1.go = "Step_F4_2";
        break;
		case "Step_F4_2":
            dialog.text = "And where is this Juan Galeno and his squadron now?";
			link.l1 = "At the bottom, monsieur...";
            link.l1.go = "Step_F4_3";
        break;
		case "Step_F4_3":
			if (CheckCompanionInCharacter(pchar, "SoleiRoyalCaptain"))
			{
				dialog.text = "Haha, great job! Well, your task is done - you managed to deliver the Soleil Royal to its destination and coped with a difficult situation with honor. Great job, Captain. I am now taking command of the Soleil Royal.";
				link.l1 = "Fine, sir. I won't keep you - business... Goodbye, monsieur.";
				link.l1.go = "exit";
				RemoveCharacterCompanion(pchar, characterFromId("SoleiRoyalCaptain"));
				pchar.questTemp.State = "Fr4SoleiRoyal_backTortuga";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "6");
			}
			else
			{
				dialog.text = "But you failed to save the Soleil Royal! This is bad, "+ GetSexPhrase("sir", "miss") +", very bad... Now you must report to the Governor-General of Tortuga on the failure of your mission. Goodbye.";
				link.l1 = "Goodbye, monsieur...";
				link.l1.go = "exit";
				pchar.questTemp.State = "Fr4SoleiRoyal_SoleiRoyalSunk";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "7");
			}
        break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("You've already taken everything. What else do you need?", "Is there really anything left that you didn't bring?");
            link.l1 = RandPhraseSimple("Looking around for the last time...", "Checking, maybe I forgot to pick up something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//Квест Аскольда, штурм в обличие мумии
        case "Ascold_MummyAttack":
			dialog.text = "Ahhh!!!";
			Link.l1 = "Stop yelling, you idiot. I'm here on business and I won't hurt you.";
			Link.l1.go = "Step_Asc1";
			AfterTownBattle();
        break;
        case "Step_Asc1":
            dialog.text = "The mummy speaks!!! Ahhh!!!";
			Link.l1 = "Listen to me, you miserable coward. I know that you have four items: three crystal Toltec skulls of different colors and a strange Indian object that looks like a rattle. Give me these items and we'll get out of town.";
			Link.l1.go = "Step_Asc2";
        break;
        case "Step_Asc2":
            dialog.text = "They are in the closet to my left, in one of the closed drawers. Here's the key, you can take everything...";
			Link.l1 = "Of course you forbid me, worm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
			Locations[FindLocation(pchar.location)].box1.items.sculMa1 = 1;
            Locations[FindLocation(pchar.location)].box1.items.sculMa2 = 1;
            Locations[FindLocation(pchar.location)].box1.items.sculMa3 = 1;
            Locations[FindLocation(pchar.location)].box1.items.indian22 = 1;
            pchar.questTemp.Ascold = "Ascold_MummyFoundItems";
			chrDisableReloadToLocation = false;
			SetReturn_Gover_Dialog_Exit(NPChar);
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

