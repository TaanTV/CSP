// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question, " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Are we going to ask questions again?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yeah, really for the third time...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
            if (pchar.questTemp.State == "SeekBible_toBermudes")
			{
                link.l1 = HeroStringReactionRepeat("Listen, I'm looking for a pirate who sold some kind of strange Bible here. Haven't you heard about this case?",
                "I'm talking about the Bible... we've already found out, I'm sorry.", "Yes, that's right...", "Ah, we've already figured it out, I'm sorry...", npchar, Dialog.CurrentNode);
                link.l1.go = DialogGoNodeRepeat("Step_H8_1", "", "", "", npchar, Dialog.CurrentNode);
            }
            if (pchar.RomanticQuest == "BrotherIsDead")
			{
                link.l1 = HeroStringReactionRepeat("Listen, do you know where Atilla is now?",
                "Oh, yes, we've already told about Atilla...", "Yeah, right...", "Sorry, I forgot it...", npchar, Dialog.CurrentNode);
                link.l1.go = DialogGoNodeRepeat("Step_Romantic_1", "", "", "", npchar, Dialog.CurrentNode);
            }
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = "Listen, buddy, have you heard anything interesting about the Bluebird xebec in the tavern?";
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toBermudes")
			{
				link.l1 = "Did Edward Law happen to be here?";
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain" || pchar.questTemp.piratesLine == "KillLoy_2toTavernAgain")
			{
				link.l1 = "I'm looking for Edward Law.";
				link.l1.go = "PL_Q3_2";
			}
			if (pchar.questTemp.piratesLine == "PL5Hunter_toBermudes")
			{
				link.l1 = "Did John Avory stop by your tavern?";
				link.l1.go = "StepPL5Berm_1";
			}
            // <== Проверяем поле состояния квестов.
		break;
		//шебека Синяя Птица
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat("I hear a lot of things. They mostly say that the ship is very fast. They tried to catch it, but all in vain.",
				"We've already talked about this.",
				"Again? We've already found out everything.",
                "I'm sorry, if you don't need anything else, then I'll probably take care of other clients.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Who tried to catch it?",
				"Yes, that's right...",
                "Hmm, that's right.",
				"Okay...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

		case "BlueBird_2":
			dialog.text = "A lot of people tried, but they broke off, haha!!";
			link.l1 = "Do you know anything useful? Where it is often seen, for example.";
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = "They see it here, near Bermudes. The Blue Bird has no equal in walking in our reefs, galleons and frigates have fought more than once in pursuit of it - and straight to the bottom!";
			link.l1 = "That's how it is... Well, let's look for it. Listen, what kind of person local storekeeper is?";
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = "Highly reputable, respected among merchants.";
			link.l1 = "Understood... Is there a person who is not on very good terms with him?";
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = "He has no outright enemies. But the former owner of the store, I think, has a grudge against him, hehe...";
			link.l1 = "Would you kindly tell me his name, my dear.";
			link.l1.go = "BlueBird_6";
		break;
		case "BlueBird_6":
			dialog.text = "His name is John Norton. You won't find him in Bermudes anymore. I heard that he moved to Puerto Principe, trades there on the sly and does not stick out anywhere.";
			link.l1 = "Thank you very much, buddy. You're a good innkeeper.";
			link.l1.go = "BlueBird_7";
		break;
		case "BlueBird_7":
			dialog.text = "Thank you, " + GetAddress_Form(NPChar) + ". Good luck!";
			link.l1 = "And have a nice day, buddy.";
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "3");
			pchar.questTemp.BlueBird = "toPuertoPrincipe";
		break;

		//голл. линейка, квест №8
 		case "Step_H8_1":
    		dialog.text = "No, I haven't heard.";
    		link.l1 = "It seems to be a well-known story, I was told it in Curacao.";
    		link.l1.go = "Step_H8_2";
 		break;
 		case "Step_H8_2":
    		dialog.text = "I don't know anything about it, I didn't have that in the tavern.";
    		link.l1 = "Thanks for the help.";
    		link.l1.go = "exit";
 		break;
		//Изабелла, ищем Атиллу
 		case "Step_Romantic_1":
    		dialog.text = "I know, he bought a house here in the city. So that's where it should be.";
    		link.l1 = "Thanks, buddy...";
    		link.l1.go = "exit";
 		break;
		//Пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = "Appeared. He kept walking around, sniffing around. He gets hooked on one, then on the other... It seems he was interested in our shipyard.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "9");
			pchar.questTemp.piratesLine = "KillLoy_toAlexus";
		break;

		case "PL_Q3_2":
			dialog.text = "So you've already asked about him.";
			link.l1 = "Maybe you remembered something?";
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = "Yes, what's there to remember, he asked all about the shipyard, sat down with different people. By the way, Captain Goodley is sitting there, he was talking to Law.";
			link.l1 = "Captain Goodley?! Thanks, that's something.";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "KillLoy_toGoogly";
		break;
		//Пиратка, квест №5, ОЗГ
		case "StepPL5Berm_1":
			dialog.text = "Yes, I just ran in. He asked where Orrie Bruce lived and left.";
			link.l1 = "And where does this Orry Bruce live?";
			link.l1.go = "StepPL5Berm_2";
		break;
		case "StepPL5Berm_2":
			dialog.text = "So, he lives in a two-story masonry house. As soon as you leave the tavern, the first house is on the left. That's where it lives...";
			link.l1 = "Thank you, you helped me a lot!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "10");
			pchar.questTemp.piratesLine = "PL5Hunter_toOrryHouse";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

