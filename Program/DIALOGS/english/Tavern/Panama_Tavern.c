// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the gossip of the city "+ GetCityName(npchar.city) +" at your service. What would you like to know?",
                          "We just brought up this topic. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Why are you talking like a parrot? The same thing...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Yeah...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> проверка на квесты
			if (CheckAttribute(pchar, "questTemp.State.Store"))
            {
                link.l1 = "Listen, do you know anything about a Dutch merchant named Jacob Lopez de Fonseca?";
                link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "Listen, they say you had a privateer in town - Francois Gontier. Do you know where I can find him?";
                link.l1.go = "Panama_rat_1";
            }
            // <== проверка на квесты
		break;
//*************************** Квест №2 испанки, задание Инквизиции ***************************
 		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat("No, I haven't seen this here or heard about it.", "You already"+ GetSexPhrase("asked", "asked") +"about that, I answered you.", "I'm telling you, you already"+ GetSexPhrase("asked", "asked") +"about this Yakov.", "Listen, step back and don't interfere! Are you screw loose?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Well, thank you.", "Hm, really...", "Yes, exactly, "+ GetSexPhrase("asked", "asked") +"...", "Sorry, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("Yes, we had this guy in our city. He was hiding in dark corners... Then some friends came to him - they looked like uniform thugs, and he left the city with them.", "You've already "+ GetSexPhrase("asked", "asked") +"about that, I answered you.", "I'm telling you, you already"+ GetSexPhrase("asked", "asked") +"about this Gontiere.", "Listen, step back and don't get in the way! Are you screw loose?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Do you know where did he go?", "Hm, really...", "Yes, exactly, "+ GetSexPhrase("asked", "asked") +"...", "Sorry, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;

		case "Panama_rat_2":
			dialog.text = "Well, there's only one road on foot from here - to Porto Bello. And he went on foot. So look for him there.";
			link.l1 = "Thank you, you helped me a lot!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

