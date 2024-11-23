// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question, " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Are we going to ask questions again?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yes, really for the third time...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = "There are rumors that Sawkins is gathering people for some kind of business. Don't you know?";
				link.l1.go = "PL_Q7_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_Novaya_Rodina.IshemHugo"))
			{
				link.l2 = "Have you seen Hugo's Sawmill here?";
				link.l2.go = "PDM_Gde_Lesopilka";
			}
		break;
		//пиратка, квест №7, попытка узнать о планах Соукинса
		case "PL_Q7_1":
			dialog.text = NPCStringReactionRepeat("Yes, something is brewing. Richard is probably going to pinch the Spaniards again.",
				"We have already talked about this topic.",
				"Are you talking about Richard's plans again?",
                "I won't give you any new advice.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Understood... And when and where do you not know?",
				"Yes, that's right.",
                "Yeah, again...",
				"Hmm, thanks for that...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q7_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q7_2":
			dialog.text = "Ha, well, you give! Richard never reveals such things, until the very last moment, even to his captains. And you're asking me...";
			link.l1 = "Well, you never know. I'm asking because I doubt if I should sign up for this case. What do you think?";
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = "I don't know "+ GetSexPhrase("myself", "myself") +" decide. Sawkins has a reputation for being a lucky cap. But personally, I would go with him, Richard is too painfully preparing for this carefully - he sits in the residence all day and scribbles something in his magazine...";
			link.l1 = "Heh, I see... Well, thank you for the advice.";
			link.l1.go = "exit";
		break;
		//Квест "New Homeland", Ищем Лесопилку
		case "PDM_Gde_Lesopilka":
			dialog.text = "He was here, the English bounty hunters came for him, he slipped out the back door in time.";
			link.l1 = "Well? Where did he go?";
			link.l1.go = "PDM_Gde_Lesopilka_2";
		break;

		case "PDM_Gde_Lesopilka_2":
			dialog.text = "Mmm... For 1000 gold, I will tell you the way.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Here, hold your money. So where did he go?";
				link.l1.go = "PDM_Gde_Lesopilka_3";
				link.l2 = "I don't have that much money right now.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "I don't have that much money right now.";
				link.l1.go = "exit";
			}
		break;

		case "PDM_Gde_Lesopilka_3":
			DeleteAttribute(pchar, "questTemp.PDM_Novaya_Rodina.IshemHugo");
			dialog.text = "He's headed for La Vega, look for him there.";
			link.l1 = "Thank you, see you later.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld, "LaVega_Tavern", "sit", "sit10");
			AddQuestRecord("PDM_Novaya_Rodina", "3");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

