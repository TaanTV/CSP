// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Just recently you tried to ask me a question...", "Well, let me guess... Nothing significant again?",
                          "Listen, I'm handling finances, not answering questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "You guessed it, I'm sorry...", "I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "MorrisWillams_ArrestedToUsurer")
            {
                link.l1 = "I need to talk to you about Morris Williams.";
                link.l1.go = "Step_E6_1";
            }
			if (pchar.questTemp.State == "MorrisWillams_AfterFightGoRedmond")
            {
                link.l1 = "You won't see your partners anymore.";
                link.l1.go = "Step_E6_5";
            }
		break;

		case "Step_E6_1":
			dialog.text = "What happened to Morris Williams?";
			link.l1 = "Don't you know he's in jail?!";
			link.l1.go = "Step_E6_2";
		break;
		case "Step_E6_2":
			dialog.text = "I know, of course. What happened, did he die?";
			link.l1 = "No, he's not dead, but he's suffering a lot. You probably know that he was just terribly unlucky, otherwise the debt would have been paid to you.";
			link.l1.go = "Step_E6_3";
		break;
		case "Step_E6_3":
			dialog.text = "But it's not paid!";
			link.l1 = "So you don't care that a privateer might rot in prison?!";
			link.l1.go = "Step_E6_4";
		break;
		case "Step_E6_4":
			dialog.text = "I'm only worried about my own health, and I don't care about the rest, "+ GetSexPhrase("sir", "miss") +". I don't want to talk about it anymore.";
			link.l1 = "I will not leave this case like this. We'll meet again...";
			link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ArrestedSeekInfo";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "18");
		break;
		case "Step_E6_5":
			dialog.text = "Who are you talking about?";
			link.l1 = "I'm talking about the smugglers you're dealing with. I "+ GetSexPhrase("let go", "let go") +"they're bleeding.";
			link.l1.go = "Step_E6_6";
		break;
		case "Step_E6_6":
			dialog.text = "Hmm... And what do you need?";
			link.l1 = "Morris Williams IOUS to begin with. And leave the Atterbury family alone, who had the temerity to borrow money from you a year ago.";
			link.l1.go = "Step_E6_7";
		break;
		case "Step_E6_7":
			dialog.text = "And this is what the pirate says?!! All right, Williams will be released immediately.";
			link.l1 = "That's not all. For my silence about your smuggling business, you'll be paying me... 10,000 a month.";
			link.l1.go = "Step_E6_8";
		break;
		case "Step_E6_8":
			dialog.text = "Haha! No, I won't\n"+
                     "You can no longer prove my connection with smuggling, only your word against mine\n"+
                     "But I don't need a scandal, so I'm making concessions to you on Williams. You will not see more. Goodbye.";
			link.l1 = "Goodbye. And don't forget what you promised me.";
			link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "5";
            //ChangeCharacterReputation(pchar, -2); // за попытку шантажа TO_DO eddy
            AddCharacterExpToSkill(pchar, "Accuracy", 80);
            AddCharacterExpToSkill(pchar, "Commerce", 50);
            AddCharacterExpToSkill(pchar, "Sneak ", 70);
            AddCharacterExpToSkill(pchar, "Fencing  ", 100);
            AddCharacterExpToSkill(pchar, "Defence  ", 50);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "22");
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Morris_Willams")], "PortRoyal_tavern", "sit", "sit1");
			characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "Willams_NiceTalking";
            LAi_SetSitTypeNoGroup(characterFromID("Morris_Willams"));
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

