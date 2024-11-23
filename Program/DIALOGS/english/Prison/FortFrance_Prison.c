// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I'm listening.";
			link.l1 = "I "+ GetSexPhrase("wrong", "wrong") +". Goodbye.";
			link.l1.go = "Exit";
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_SS"))
			{
				link.l1 = "I have a matter for you, Officer. I think you will be interested in this. One of your soldiers, Jory, tried to buy wine in the city through my mediation. Knowing your ways...";
				link.l1.go = "PDM_PJ_SS_1";
			}
		break;
		
		case "PDM_PJ_SS_1":
			dialog.text = "What?! I have strictly banned drinking at strategic facilities! Well, he will pay for it. For your vigilance, I will reward you with 5,000 gold, and Jory will be sent to the brig for three days.";
			link.l1 = "Thank you, " + GetFullName(NPChar)+". It is our common duty to stop such violations.";
			link.l1.go = "PDM_PJ_SS_2";
			DeleteAttribute(pchar, "questTemp.PDM_PJ_SS");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KV");
			AddMoneyToCharacter(pchar, 5000);
		break;
		
		case "PDM_PJ_SS_2":
			DialogExit();
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			LAi_SetLoginTime(sld, 0.0, 24.0);
			sld = CharacterFromID("PDM_PJ_Strajnik_2")
			LAi_SetLoginTime(sld, 0.0, 24.0);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			LAi_SetActorType(pchar);
			DoQuestReloadToLocation("FortFrance_town", "goto", "goto2", "PDM_PJ_Arest_0");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
