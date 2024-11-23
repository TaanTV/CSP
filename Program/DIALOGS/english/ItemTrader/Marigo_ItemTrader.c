// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "Whatever you want, " + GetAddress_Form(NPChar) + "?"), "More questions, " + GetAddress_Form(NPChar) + "...", "Questions, questions... Maybe we'll do some trading, " + GetAddress_Form(NPChar) + "?",
                          "Listen, how many empty conversations can you have?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("No questions...", "I have nothing to talk about right now."), "Eh, again...",
                      "Yes, it's really better to bargain...", "Hmm, sorry, trader...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Анжелика Тич: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.AT_PZD_Lavochniki") && !CheckAttribute(npchar, "AT_PZD_Vopros"))
			{
				link.l1 = "Can you tell me where I can buy a dress worthy of going out?";
				link.l1.go = "AT_PZD_Lavochniki_1";
				DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki");
			}
            if(CheckAttribute(pchar, "questTemp.AT_PZD_Lavochniki_2") && !CheckAttribute(npchar, "AT_PZD_Vopros"))
            {
				link.l1 = "I need to get a dress, no worse than the wife of a local banker.";
				link.l1.go = "AT_PZD_Lavochniki_2";
				DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki_2");
			}
			if(CheckAttribute(pchar, "questTemp.AT_PZD_Lavochniki_3") && !CheckAttribute(npchar, "AT_PZD_Vopros"))
            {
				link.l1 = "I need a dress, but not an ordinary one, but one that would not be ashamed to show up in it at least at a reception with the King of France himself.";
				link.l1.go = "AT_PZD_Lavochniki_3";
				DeleteAttribute(pchar, "questTemp.AT_PZD_Lavochniki_3");
			}
			// <== Анжелика Тич: Портниха знатной дамы
		break;
		
		//============ Анжелика Тич: Портниха знатной дамы
		case "AT_PZD_Lavochniki_1":
    		dialog.text = "You are unlikely to buy this on the market. You should find a good dressmaker. Unfortunately, I can't recommend anyone..";
    		link.l1 = "Okay...";
    		link.l1.go = "exit";
			pchar.questTemp.AT_PZD_Lavochniki_2 = true;
			npchar.AT_PZD_Vopros;
 		break;
		
		case "AT_PZD_Lavochniki_2":
    		dialog.text = "No, madam, I don't have that on sale.";
    		link.l1 = "Okay...";
    		link.l1.go = "exit";
			pchar.questTemp.AT_PZD_Lavochniki_3 = true;
			npchar.AT_PZD_Vopros;
 		break;
		
		case "AT_PZD_Lavochniki_3":
    		dialog.text = "At the tailor of the King of France, who else. And we are simple people, not like these rich gentlemen who visit the local brothel.";
    		link.l1 = "How interesting, do these gentlemen enjoy a special status? Surely they don't run there to the harbor girls?";
    		link.l1.go = "AT_PZD_Lavochniki_3_1";
 		break;
		
		case "AT_PZD_Lavochniki_3_1":
    		dialog.text = "Sorry, it's not my way to spread gossip. Come and ask, maybe you will be offered something special, but I am not, do not ask. The hostess there is a prominent lady, she takes wine from my cousin, he is an excellent winemaker, and there is no need for me to slander her.";
    		link.l1 = "I understand you. Well, I'll take note and I'll definitely take your wine sometime.";
    		link.l1.go = "exit";
 		break;
		

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

