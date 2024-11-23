
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);						// 						АВТОРЫ И БЛАГОДАРНОСТИ
	makearef(Link, Dialog.Links);						// Идея квеста, диалоги и кодинг					- Sinistra
	makearef(NextDiag, NPChar.Dialog);					// Модель, текстура и анимация акулы				- IG Baron
														// Иконка кота										- Noctus
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = "(calling someone) Gatilio... Where are you, my friend? Gatilio...";
			link.l1 = "Did you lose someone, kid?";
			link.l1.go = "Знакомство_1";
		break;
		
		case "Знакомство_1":
			dialog.text = "Oh, I'm sorry, Captain. I didn't notice you. My name is Horatio, I am a local fisherman. I live here by the shore and catch various marine life. That's what I do for a living.";
			link.l1 = "My name is " +GetFullName(pchar)+". So what happened to you?";
			link.l1.go = "Знакомство_2";
		break;
		
		case "Знакомство_2":
			dialog.text = "So be it, I'll tell you, "+pchar.name+". A terrible storm broke out late last night. And all my things that were on the shore were swept out to sea. And so... My dear friend Gatilio really likes to sleep inside my trunk...";
			link.l1 = "Wait, WHAT!? Why did Senor Gatilio go into the trunk at all?";
			link.l1.go = "Знакомство_3";
		break;
		
		case "Знакомство_3":
			dialog.text = "Because Gatilio was very hungry, and I keep my fish inside the chest.";
			link.l1 = "But if Gatilio was really sitting in the trunk during the storm, then I'm afraid he was carried away by the current and drowned along with your things. He is no longer alive...";
			link.l1.go = "Знакомство_4";
		break;
		
		case "Знакомство_4":
			dialog.text = "It's not true! I heard a plaintive meowing from the other side, he's definitely alive! I know that!";
			link.l1 = "So your Gatilio is a cat!? Why didn't you tell me right away?";
			link.l1.go = "Знакомство_4_1";
			locCameraFromToPos(1.43, 5.67, -3.17, false, 56.59, 6.38, -11.15);
		break;
		
		case "Знакомство_4_1":
			DialogExit();
			npchar.dialog.filename = "Quest\KotVMeshke.c";
			npchar.dialog.currentnode = "Знакомство_5";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 0.0);
		break;
		
		case "Знакомство_5":
			dialog.text = "So I said. He's my friend. How could you not understand\nIf you find my chest, you can have it all as a reward. Most importantly, I want my dear friend Gatilio back.";
			link.l1 = "Okay, I'll look for your cat.";
			link.l1.go = "Согласие_1";
			link.l2 = "You need to hire someone else for such a weird job.";
			link.l2.go = "Отказ_1";
		break;
		
		case "Отказ_1":
			dialog.text = "You are a very angry man, Captain. But yes, you're right, I wouldn't trust you with this job.";
			link.l1 = "See you later.";
			link.l1.go = "Отказ_2";
		break;
		
		case "Отказ_2":
			DialogExit();
			DeleteAttribute(npchar, "talker");
			UnmarkCharacter(npchar);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Согласие_1":
			dialog.text = "Thank you, Captain. I will be waiting for you with my Gatilio.";
			link.l1 = "I'll be back soon.";
			link.l1.go = "Согласие_2";
		break;
		
		case "Согласие_2":
			DialogExit();
			DeleteAttribute(npchar, "talker");
			UnmarkCharacter(npchar);
			LAi_SetStayType(npchar);
			
			SetQuestHeader("CSP_KvM");
			AddQuestRecord("CSP_KvM", "1");
			AddQuestUserData("CSP_KvM", "sSex", GetSexPhrase("", "a"));
			
			sld = CharacterFromID("CSP_KvM_Ribak");
			sld.dialog.filename = "Quest\KotVMeshke.c";
			sld.dialog.currentnode = "ЕщёРаз_1";
			
			pchar.questTemp.CSP_KvM_PoiskGatilio = true;
			
			DeleteAttribute(&locations[FindLocation("SantoDomingo_town")], "private1.QuestClosed");
			
			PChar.quest.CSP_KvM_GatilioVSunduke.win_condition.l1 = "item";
			PChar.quest.CSP_KvM_GatilioVSunduke.win_condition.l1.item = "CSP_KvM_Gatilio";
			PChar.quest.CSP_KvM_GatilioVSunduke.win_condition = "CSP_KvM_GatilioVSunduke";
		break;
		
		case "ЕщёРаз_1":
			dialog.text = "Gatilio... Where are you...";
			link.l1 = "I'll find your cat, don't worry...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ЕщёРаз_1";
		break;
		
		case "ВозвращаемГатилио_1":
			dialog.text = "Gatilio! I thought I'd never see you again... (lets out a tear) Gatilio...";
			link.l1 = "I'm happy that everything worked out well.";
			link.l1.go = "ВозвращаемГатилио_2";
			TakeItemFromCharacter(pchar, "CSP_KvM_Gatilio");
			Log_info("You brought Gatilio back");
		break;
		case "ВозвращаемГатилио_2":
			dialog.text = "Thank you, Captain "+GetFullName(pchar)+". You are a man of your word. I'll tell everyone what a wonderful person you are.";
			link.l1 = "It was really nice to help you and your cat. Goodbye.";
			link.l1.go = "ВозвращаемГатилио_3";
		break;
		case "ВозвращаемГатилио_3":
			DialogExit();
			
			AddQuestRecord("CSP_KvM", "3");
			AddQuestUserData("CSP_KvM", "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader("CSP_KvM");
			pchar.questdata.KotVMeshke = 1;
			ChangeCharacterReputation(pchar, 2);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			InterfaceStates.Buttons.Save.enable = true;
			bDisableFastReload = false;
			DeleteAttribute(pchar, "questTemp.CSP_KvM_Akula");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddSimpleRumour("They say that you saved a cat in Santo Domingo! It's amazing!", SPAIN, 10, 1);
		break;
		
		
	}
}
