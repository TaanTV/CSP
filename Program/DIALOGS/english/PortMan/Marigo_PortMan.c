// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Listen, if you're not on port business, then don't bother me with questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yeah, really for the third time...", "Sorry, but I'm not interested in port affairs right now.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// ==> Анжелика Тич: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.AT_PZD_PU"))
			{
				DeleteAttribute(pchar, "questTemp.AT_PZD_taverna")
				DeleteAttribute(pchar, "questTemp.AT_PZD_PU")
				link.l1 = "Tell me, which ships under the Spanish flag have you seen in the last week?";
				link.l1.go = "AT_PZD_PU_1";
				break;
			}
			// <== Анжелика Тич: Портниха знатной дамы
		break;
		
		//============ Анжелика Тич: Портниха знатной дамы
		case "AT_PZD_PU_1":
    		dialog.text = "Under the Spanish flag, you say? There are not many words under Spanish. The galleon 'Ernal Diaz' by Captain Gabriel de Seguens. Two trading flutes arrived from Porto Bello yesterday. The owner of both is Andres Foseca. And also your '" + PChar.Ship.Name + "'.";
    		link.l1 = "Where's the galleon from?";
    		link.l1.go = "AT_PZD_PU_2";
 		break;
		
		case "AT_PZD_PU_2":
    		dialog.text = "From Havana. But this is what is indicated in my documents, no one reported on their route in detail.";
    		link.l1 = "Do you know anything about the passengers?";
    		link.l1.go = "AT_PZD_PU_3";
 		break;
		
		case "AT_PZD_PU_3":
    		dialog.text = "Sorry, that's all.";
    		link.l1 = "Yes, it's a pity.";
    		link.l1.go = "AT_PZD_PU_4";
 		break;
		
		case "AT_PZD_PU_4":
    		dialog.text = "You know, if you are looking for someone, ask the local day laborers at the port, they also communicate with the arriving sailors. They don't have time to chat during the day, but in the evenings they often set up camps right here on the shore.";
    		link.l1 = "Thank you.";
    		link.l1.go = "AT_PZD_PU_5";
 		break;
		
		case "AT_PZD_PU_5":
    		DialogExit();
			
			AddQuestRecord("AT_PZD", "3");
			
			//Сюда ставить матросов у костра
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Matros1", "shipowner_22", "man", "man", 3, HOLLAND, -1, false));
			sld.name = "Paltures";
			sld.lastname = "Kate";
			LAi_SetLoginTime(sld, 22.0, 3.99);
			LAi_SetGroundSitType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_MatrosUKostra_1";
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			sld.City = "Marigo";
			ChangeCharacterAddressGroup(sld, "Marigo_town", "sit", "fire1_1");
			
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Matros2", "pirate_19", "man", "man", 3, HOLLAND, -1, false));
			sld.name = "Paltures";
			sld.lastname = "Kate";
			LAi_SetLoginTime(sld, 22.0, 3.99);
			LAi_SetGroundSitType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_MatrosUKostra_1";
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			sld.City = "Marigo";
			ChangeCharacterAddressGroup(sld, "Marigo_town", "sit", "fire1_2");
			
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Matros3", "pirate_20", "man", "man", 3, HOLLAND, -1, false));
			sld.name = "Paltures";
			sld.lastname = "Kate";
			LAi_SetLoginTime(sld, 22.0, 3.99);
			LAi_SetGroundSitType(sld);
			sld.dialog.filename = "Quest\AngelikaTichLine\PortnihaZnatnoyDamy.c";
			sld.dialog.currentnode = "AT_PZD_MatrosUKostra_1";
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			sld.City = "Marigo";
			ChangeCharacterAddressGroup(sld, "Marigo_town", "sit", "fire1_3");
			
			sld = GetCharacter(NPC_GenerateCharacter("AT_PZD_Matros4", "shipowner_23", "man", "man", 3, HOLLAND, -1, false));
			LAi_SetLoginTime(sld, 22.0, 3.99);
			LAi_SetActorType(sld);
			LAi_ActorSetLayMode(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			sld.City = "Marigo";
			ChangeCharacterAddressGroup(sld, "Marigo_town", "sit", "fire2_1");
 		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


