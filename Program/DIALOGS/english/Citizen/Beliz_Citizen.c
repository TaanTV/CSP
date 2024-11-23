// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now.");
		    link.l1.go = "exit";
			// ==> Квест "Witch Hunt"
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Beliz") && npchar.sex == "man" && !CheckAttribute(npchar, "PDM_ONV_Vopros"))
			{
				link.l1 = RandPhraseSimple("Excuse me, have you seen Maria?", "Do you know where Maria is?");
				link.l1.go = "PDM_ONV_MAN";
			}
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Beliz") && npchar.sex == "man" && !CheckAttribute(npchar, "PDM_ONV_Vopros") && CheckAttribute(pchar, "questTemp.PDM_ONV_MAN_1"))
			{
				link.l1 = RandPhraseSimple("Excuse me, have you seen Maria?", "Do you know where Maria is?");
				link.l1.go = "PDM_ONV_MAN_2";
				DeleteAttribute(pchar, "questTemp.PDM_ONV_MAN_1");
			}
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Beliz") && npchar.sex == "man" && !CheckAttribute(npchar, "PDM_ONV_Vopros") && CheckAttribute(pchar, "questTemp.PDM_ONV_MAN_2"))
			{
				link.l1 = RandPhraseSimple("Excuse me, have you seen Maria?", "Do you know where Maria is?");
				link.l1.go = "PDM_ONV_MAN_3";
				DeleteAttribute(pchar, "questTemp.PDM_ONV_MAN_2");
			}
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Beliz") && npchar.sex == "man" && !CheckAttribute(npchar, "PDM_ONV_Vopros") && CheckAttribute(pchar, "questTemp.PDM_ONV_MAN_3"))
			{
				link.l1 = RandPhraseSimple("Excuse me, have you seen Maria?", "Do you know where Maria is?");
				link.l1.go = "PDM_ONV_MAN_4";
			}
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Beliz") && npchar.sex == "woman" && !CheckAttribute(npchar, "PDM_ONV_Vopros"))
			{
				link.l1 = RandPhraseSimple("Excuse me, have you seen Maria?", "Do you know where Maria is?");
				link.l1.go = "PDM_ONV_WOMAN";
			}
			// <== Квест "Witch Hunt"
		break;

		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Am I working for a secret agent network for "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "All right... Bye then.";
			link.l1.go = "exit";
			link.l2 = "Then another question";
			link.l2.go = "new question";
		break;

		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "What do I tell you? I don't know. I don't know anything.";

            link.l1 = "What a fool! Bye.";
			link.l1.go = "exit";
			link.l2 = "Then another question";
			link.l2.go = "new question";
		break;
		
//**************************Квест "Witch Hunt"*******************************

		case "PDM_ONV_WOMAN":
			dialog.text = RandPhraseSimple("I don't know any Maria.", "Who else is Maria?", "I don't know who you're talking about.", "Who, who? This is the first time I've heard of such a girl.", "We've never had such a girl.");
			link.l1 = "Sorry.";
			link.l1.go = "exit";
			npchar.PDM_ONV_Vopros;
		break;

		case "PDM_ONV_MAN":
			dialog.text = "Sorry, but I'm in a hurry.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			npchar.PDM_ONV_Vopros;
			pchar.questTemp.PDM_ONV_MAN_1 = true;
		break;
		
		case "PDM_ONV_MAN_2":
			dialog.text = "Leave me alone, "+ GetSexPhrase("senor", "senorita") +".";
			link.l1 = "Sorry.";
			link.l1.go = "exit";
			npchar.PDM_ONV_Vopros;
			pchar.questTemp.PDM_ONV_MAN_2 = true;
		break;
		
		case "PDM_ONV_MAN_3":
			dialog.text = "Go your own way, amig"+ GetSexPhrase("o", "a") +".";
			link.l1 = "Sorry.";
			link.l1.go = "exit";
			npchar.PDM_ONV_Vopros;
			pchar.questTemp.PDM_ONV_MAN_3 = true;
		break;
		
		case "PDM_ONV_MAN_4":
			dialog.text = "I'm telling you, "+ GetSexPhrase("senor", "senorita") +" - this witch Maria has bewitched everyone in this city! All decent people should go straight to the governor and tell him that she is an evil witch and she should be burned on a slow fire!";
			link.l1 = "Maria? What do you know about her?";
			link.l1.go = "PDM_ONV_MAN_4_1";
		break;

		case "PDM_ONV_MAN_4_1":
			dialog.text = "Me? I know that she is the source of mortal sin for any man in this city! We must put an end to this debauchery!");
			link.l1 = "So. So you're the only man in town who doesn't use Maria's services? Oh, poor man! Now it's clear why you don't have a sense of humor. Ha-ha. But I have to interrupt our conversation - goodbye.";
			link.l1.go = "exit";
			link.l2 = "The governor ordered me to capture this witch - he wants to personally interrogate her. Do you know where I can find her?";
			link.l2.go = "PDM_ONV_MAN_4_2";
		break;

		case "PDM_ONV_MAN_4_2":
			dialog.text = "She usually brings her victims to the tavern. God bless you, Captain! Go in there and get that snake out of its nest! You are "+ GetSexPhrase("brave man, senor", "brave, senorita") +". The fact that this witch walks around here and does whatever she wants is a disgrace to our city!");
			link.l1 = "We will deal with this witch, do not hesitate.";
			link.l1.go = "exit";
			AddQuestRecord("PDM_Ohota_na_vedmu", "7");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "a"));
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Beliz");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Oficiantka_Beliz");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_MAN_3");
			pchar.questTemp.PDM_ONV_Detectiv_Tavern_Da = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

