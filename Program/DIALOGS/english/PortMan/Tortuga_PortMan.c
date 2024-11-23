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
            // ==> квест №7 голл.линейки, догнать похитителей депеши
            if (pchar.questTemp.State == "DelivLettTortuga_toPortMan")
            {
    			link.l1 = "D'Ogeron sent me to you so that you would immediately tell me which ship left the waters of Tortuga within the next two hours!";
    			link.l1.go = "Step_H7_1";
            }
            if (pchar.questTemp.State == "Sp6TakeMess_toTotuga")
            {
                link.l1 = "I am authorized to pay my respects to you and familiarize you with my documents. Please read my trade power of attorney for the French East India Company.";
                link.l1.go = "Step_S6_1";
            }
            if (pchar.questTemp.State == "Sp6TakeMess_waitMessanger")
            {
                link.l1 = "Listen, has there been a Dutch ship I expected yet?";
                link.l1.go = "Step_S6_6";
            }
            if (pchar.questTemp.State == "Fr4SoleiRoyal_toPortMan")
            {
                link.l1 = "According to the regulation d'Ogeron, you need to place the first-class battleship Soleil Royal at my disposal.";
                link.l1.go = "Step_F4_1";
            }

			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "Good afternoon. I'm looking for Francois Gontier. His corvette '" + pchar.questTemp.Slavetrader.ShipName + "' should have anchored in your harbor.";
                link.l1.go = "Tortuga_ratP_1";
            }

		break;

//************************************* Голл. линейка, квест №7, доставка депеши *******************************
		case "Step_H7_1":
            dialog.text = "Only one thing - the Brig La Rochelle. He left for Puerto Rico in the direction of San Juan. The sales representative of the French East India Company also left with him.";
			link.l1 = "Which representative?!";
			link.l1.go = "Step_H7_2";
		break;
		case "Step_H7_2":
            dialog.text = "I'm telling you: a representative of the French East India Company. He arrived here a few days ago and immediately presented a power of attorney to the company. He had done his business and wanted to go straight from here to you, to Curacao, for which he was looking for a passing ship. I sent him to you\n"+
                          "But at the last moment, his plans apparently changed, and he left with the brig, on which he came to Tortuga, actually.";
			link.l1 = "Damn it, it looks like this is Antonio...";
			link.l1.go = "Step_H7_3";
		break;
		case "Step_H7_3":
            dialog.text = "That's right, Anotio de... de... I can't remember anymore.";
			link.l1 = "I must catch up with that damned brig immediately. It's a matter of life and death.";
			link.l1.go = "Step_H7_4";
		break;
		case "Step_H7_4":
            dialog.text = "Really? Well, it's possible. In that case, don't waste any time.";
			link.l1 = "Thank you for the information, although I have no feelings of gratitude for meeting Antonio...";
			link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "5");
			pchar.questTemp.State = "DelivLettTortuga_NotFoundLetter";
            Pchar.quest.DelivLettTortuga_AttackBrig.win_condition.l1 = "location";
            Pchar.quest.DelivLettTortuga_AttackBrig.win_condition.l1.location = "PuertoRico";
            Pchar.quest.DelivLettTortuga_AttackBrig.win_condition = "DelivLettTortuga_AttackBrig";
            SetTimerCondition("DelivLettTortuga_BrigTimeOver", 0, 0, 5, false);
		break;
//************************************* Испанская линейка, квест №6, перехват вестового *******************************
		case "Step_S6_1":
            dialog.text = NPCStringReactionRepeat("Hmm, I see. But what does this have to do with me? I don't do trading...",
                          "Yes, yes, I already know...", "What? You again?", "Well, how much can I do? You showed me your paper...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I know that. I have a request for you of a different nature... The fact is that I have almost finished here the cases for which I arrived. Next, I should arrive in Willemstad, on the island of Curacao. So, I would like  do it on a passing ship. Can you tell me if you don't have enough fast ships going to Curacao in your port?",
                     "Ah, well...", "Yes, I...", "Yes? All right...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S6_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S6_2":
            dialog.text = "Hmm, not yet. But I suppose they will appear soon - the Dutch from Willemstad come here quite often.";
			link.l1 = "Merchants?";
			link.l1.go = "Step_S6_3";
		break;
 		case "Step_S6_3":
            dialog.text = "There are traders, but I would recommend that you wait for the ship with a messenger from Curacao. They never stay here for long, an hour or two at the residence of our Governor-General - and immediately back to Willemstad. And our governor-General does not receive anyone during this time...";
			link.l1 = "Oh, that's great, perfect for me. Would you be so kind as to let me know when such a ship will enter the port of Tortuga?";
			link.l1.go = "Step_S6_4";
		break;
 		case "Step_S6_4":
            dialog.text = "Okay. Where are you staying, "+ GetSexPhrase("monsieur", "mademoiselle") +"?";
			link.l1 = "I rented a room in a tavern.";
			link.l1.go = "Step_S6_5";
		break;
 		case "Step_S6_5":
            dialog.text = "Fine. As soon as the Dutch ship anchors in our port, I will immediately send a messenger to your tavern with this information.";
			link.l1 = "Very good. Thank you very much, monsieur. You have rendered a service to our company, we will not forget it.";
			link.l1.go = "exit";
            AddQuestRecord("Spa_Line_6_TakeMessangeer", "2");
            pchar.questTemp.State = "Sp6TakeMess_waitMessanger";
            if (CheckAttribute(pchar, "questTemp.State.Sp6Ok"))
            {
                SetTimerCondition("Sp6TakeMess_waitingBoy", 0, 0, rand(7)+1, false);
                DeleteAttribute(pchar, "questTemp.State.Sp6Ok");
            }
            else
            {
                pchar.questTemp.State.Sp6Ok = 1;
            }
		break;
 		case "Step_S6_6":
            dialog.text = "No, it hasn't happened yet. I told you I'd send a messenger. Don't worry, I remember you.";
			link.l1 = "Thank you, sir. And forgive me for being annoying...";
			link.l1.go = "exit";
		break;
//************************************* Французская линейка, квест №4, Солей Руаяль *******************************
 		case "Step_F4_1":
    		if (GetCompanionQuantity(pchar) == 1)
            {
                dialog.text = "Yes, I have already been notified, "+ GetSexPhrase("monsieur", "mademoiselle") +". Take command. To be honest, commanding such a ship is happiness even for an admiral...";
    			link.l1 = "Fully agree with this statement, sir... And now let me take my leave - business.";
    			link.l1.go = "Step_F4_2";
            }
            else
            {
                dialog.text = "You need to get rid of the additional ships in your squadron. Then you can take any measures that you consider necessary, but at the time of the transfer of the ship you must be free from third-party obligations.";
    			link.l1 = "Okay, I'll do it.";
    			link.l1.go = "exit";
            }
		break;
 		case "Step_F4_2":
    		pchar.questTemp.State = "Fr4SoleiRoyal_toBasTer";
			SaveCurrentQuestDateParam("questTemp");
			AddQuestRecord("Fra_Line_4_SoleiRoyal", "2");
			ref sld = GetCharacter(NPC_GenerateCharacter("SoleiRoyalCaptain", "off_fra_2", "man", "man", 35, FRANCE, -1, true));
			sld.Ship.Name = "Soleil Royal";
			sld.Ship.Type = CreateBaseShip(SHIP_SOLEYRU);
			ResetShipCannonsDamages(sld);
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");
			FantomMakeCoolFighter(sld, 35, 80, 70, BLADE_LONG, "pistol3", 100);

			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetShipRemovable(sld, false);

            Pchar.quest.Fr4SoleiRoyal_Fight.win_condition.l1 = "location";
            Pchar.quest.Fr4SoleiRoyal_Fight.win_condition.l1.location = "Dominica";
            Pchar.quest.Fr4SoleiRoyal_Fight.win_condition = "Fr4SoleiRoyal_Fight";
			DialogExit();
		break;

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat("Hmm... I have to disappoint you. Corvette '" + pchar.questTemp.Slavetrader.ShipName + "' did not enter our port, and Francois Gontier did not check in.", "You have already asked about that, I answered you.", "You have already asked about that Gontier, I answered you.", "I'm telling you, you already asked! I ask you not to interfere with my work!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wow... And where did he go? Okay, I'll go ask around the city.", "Hmm, well...", "Yes, exactly, asked...", "Sorry, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

