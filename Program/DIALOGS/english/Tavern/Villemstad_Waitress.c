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
			//==> проверяем поле состояния квестов
            if (CheckAttribute(pchar, "questTemp.State.Usurer"))
            {
                dialog.text = "Is there something you want to tell me?";
    			link.l1 = ""+ GetSexPhrase("Yes. I mean, you look great, beautiful. Even though there are tears in your eyes.", "Why are you so upset, baby? Are you crying in any way?") +"";
    			link.l1.go = "Step_S2_1";
            }
            //<== проверяем поле состояния квестов
		break;
//*************************** Квест №2 испанки, задание Инквизиции ***************************
 		case "Step_S2_1":
    		dialog.text = NPCStringReactionRepeat("Oh...", "Oh, we've already talked about this...", "Listen, we've talked - and that's it...", "Why are you bothering the poor girl. "+ GetSexPhrase("Do you think that I have grief - and you are here to comfort me?", "") +"", "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("So who is he, your abuser? Maybe I can help?", "Yes, that's right.", "Okay, okay...", ""+ GetSexPhrase("I don't think anything, beautiful. It's okay...", "Okay...") +"", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
 		break;
 		case "Step_S2_2":
    		dialog.text = "This is the usurer's son, Jansen! He... he...";
    		link.l1 = "(What luck!) I'm just looking for this man. What did he do to you? And where can I find him?";
    		link.l1.go = "Step_S2_3";
 		break;
 		case "Step_S2_3":
    		dialog.text = "He tricked me. He promised mountains of gold, promised to get married, but he slipped away! Escaped yesterday with pirates on a lugger to Fort Orange!";
    		link.l1 = "That scoundrel! I'll let my guts out when I meet you.";
    		link.l1.go = "Step_S2_4";
 		break;
 		case "Step_S2_4":
    		dialog.text = "What if he dies from this? You'd better tell him not to show up at the tavern. Otherwise, I'll scratch his eyes out!";
    		link.l1 = "All right, I'll pass it on.";
    		link.l1.go = "exit";
            AddQuestRecord("Spa_Line_2_Inquisition", "6");
            Pchar.quest.Inquisition_AttackLugger.win_condition.l1 = "location";
            Pchar.quest.Inquisition_AttackLugger.win_condition.l1.location = "Jamaica";
            Pchar.quest.Inquisition_AttackLugger.win_condition = "Inquisition_AttackLugger";
            SetTimerCondition("Inquisition_LuggerTimeOver", 0, 0, 20, false);
 		break;



	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

