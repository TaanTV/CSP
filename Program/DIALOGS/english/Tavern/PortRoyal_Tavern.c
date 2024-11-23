// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the gossip of the city "+ GetCityName(npchar.city) +" at your service. What would you like to know?",
                          "We have just raised this issue. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Why are you talking like a parrot? The same thing...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, I forgot...",
                      "Yeah, really for the third time...", "Yeah...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> Шестой квест английки, Моррис Уильямс
            if (pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfo")
			{
                link.l1 = "Listen, what kind of person is a local usurer?";
                link.l1.go = "Step_E6_1";
			}
            // ==> Восьмой квест фр.линейки, отговорить трёх корсаров
            if (pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek")
			{
                link.l1 = "Where can I find Captain Gay? I have important business with him.";
                link.l1.go = "Step_F8_1";
			}
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Do you know where I can find Francois Gontier?";
                link.l1.go = "Jamaica_ratP_1";
            }
		break;
        //********************** Английская линейка **********************
        case "Step_E6_1":
			dialog.text = "He is a usurer, there are no good people among them.";
			link.l1 = "Have you heard anything interesting about him?";
			link.l1.go = "Step_E6_2";
		break;
        case "Step_E6_2":
			dialog.text = "No, nothing special.";
			link.l1 = "And who in the city knows him well?";
			link.l1.go = "Step_E6_3";
		break;
        case "Step_E6_3":
			dialog.text = "He doesn't really communicate with anyone, I can't say anything.";
			link.l1 = "Well, thanks for that too.";
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_ArrestedSeekInfoFather";
		break;
		//********************** Французская линейка **********************
        case "Step_F8_1":
			dialog.text = NPCStringReactionRepeat("Captain Gay? There is nothing easier. He's renting a room from me, and he hasn't come out yet today, so you'll definitely see him there.",
				          "I've already said everything...", "There's nothing to talk about...", ""+ GetSexPhrase("Sir", "Miss") +", give me the opportunity to do my own thing!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thank you, friend...", "Got it, Sorry...", "Yeah, right...", "Yeah, yeah, sorry, buddy...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
        break;

		case "Jamaica_ratP_1":
			dialog.text = NPCStringReactionRepeat("No clue. This is the first time I've ever heard this name.", "You've already"+ GetSexPhrase("asked", "asked") +"about that, I answered you.", "I'm telling you, you already"+ GetSexPhrase("asked", "asked") +"about this Gontiere.", "Listen, step back and don't bother! Are you screw loose?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Well, let's look around.", "Well...", "Yeah, right, I asked...", "Sorry, " + npchar.name + "...", npchar, Dialog.CurrentNode);
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

