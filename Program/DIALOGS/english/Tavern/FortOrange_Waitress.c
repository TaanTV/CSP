// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, " + GetAddress_Form(NPChar) + "?", "Whatever you want, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hmm, aren't you bothering me, " + GetAddress_Form(NPChar) + "? ", "Again with strange questions? Girl, would you drink rum, or something...") +"", "This is the third time you've been talking about some issue this day..."+ GetSexPhrase("Are these tokens of attention?", "") +"",
                          "Are you going to ask me again, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I have nothing to talk about right now."), "No, no, you're beautiful...",
                      "No way, dear, sclerosis...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "Listen, darling, they say you were in close contact with my friend Francois Gontiere. I talked very closely...";
                link.l1.go = "Jamaica_ratW_1";
            }

			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry15"))
				{
					link.l1 = "I bring your pendants. Here you go.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "Nothing yet. I'm looking for pendants for you.";
					link.l1.go = "exit";
				}
            }

		break;

        case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
            dialog.text = "Oh, "+ GetSexPhrase("mynheer", "mistress") +", I'm just happy that I'm alive! And I'm also happy...";
            link.l2 = "And from what else?";
            link.l2.go = "Step_H4_1";
        break;

        case "Step_H4_1":
			dialog.text = ""+ GetSexPhrase("And I'm also happy to see such a great captain and officer! The whole Fort is grateful to you, you just saved us!", "And I'm also happy that there are such brave women in the world! The whole Fort is grateful to you, you just saved us!") +"";
			link.l1 = "Come on, "+ GetSexPhrase("beauty", "girl") +", I performed my duty...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Jamaica_ratW_1":
            dialog.text = "Yes, I did, so what? I am an unmarried girl, with whom I want to communicate. Francois is a very prominent sailor, not like our local fishermen and farmers. He's all like that... Ah! And what gifts he gave me!";
            link.l1 = "Stop, stop, that's enough! I know about the merits of my friend, you don't have to tell me about them. I don't care what happened between you-at least get married. I need to find him urgently, you know? Do you know where he went?";
            link.l1.go = "Jamaica_ratW_2";
        break;

		case "Jamaica_ratW_2":
            dialog.text = "Hee-hee... You are his "+ GetSexPhrase("buddy", "friend, hee-hee") +", and you do not know where he went. That's funny!";
            link.l1 = "Nothing funny, baby. We agreed to meet with him in Jamaica, and then we will have a joint flight... If you know what I mean. I can't do it alone, but he just took off and went nowhere!";
            link.l1.go = "Jamaica_ratW_3";
        break;

		case "Jamaica_ratW_3":
            dialog.text = "Understood. Well, since you have such a profitable flight waiting for you, and you and Francois are friends... I'll tell you where he went, but for a reason.";
            link.l1 = "Hmm... How much do you want?";
            link.l1.go = "Jamaica_ratW_4";
        break;

		case "Jamaica_ratW_4":
            dialog.text = "Ugh, "+ GetSexPhrase("how vulgar", "what a rude girl you are") +". I don't need any money. Francois promised to give me emerald pendants, I already bragged to my friends, but he just took off... Bring me the pendants and I'll tell you where he went.";
            link.l1 = "Oh, you cheat! You know what to ask for - you can't get such jewelry from merchants. All right, you'll get the pendants.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;

		case "Jamaica_ratW_5":
            dialog.text = "Oh, what a beauty! Now all my friends will burst with envy!";
            link.l1 = "Give them my condolences. Now I'm waiting for an answer where Francois went.";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry15", 1);
        break;

		case "Jamaica_ratW_6":
            dialog.text = "Yeah, yeah, "+ GetSexPhrase("mynheer", "mistress") +". Francois took his way on Cuba, in Havana";
            link.l1 = "Thank you, dear. That's all I wanted to know.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

