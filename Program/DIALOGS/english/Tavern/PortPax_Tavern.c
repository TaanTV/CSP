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
			 // ==> квест "Странные вещи творятся на архипелаге
            if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_PoiskUchitel_Tavern"))
            {
                link.l1 = "I need information about one person. He always wears a red hoodie, and calls himself a Teacher.";
                link.l1.go = "PKM_SvtvA_PU_1";
            }
		break;
		
		//Квест "Strange things are happening in the archipelago"
		case "PKM_SvtvA_PU_1":
			dialog.text = "Oh, I remember that. But he's already been arrested. They say he tried to start a riot. So if you want to find him, you go straight to the Port-au-Prince prison.";
			link.l1 = "Thank you, you helped me a lot.";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_PoiskUchitel_Tavern");
			//pchar.questTemp.PKM_SvtvA_PoiskUchitel_Turma = true;
			AddQuestRecord("PKM_Animists", "27");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			
			PChar.quest.PKM_SvtvA_TuremchikQuest.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_TuremchikQuest.win_condition.l1.location = "PortPax_prison";
			PChar.quest.PKM_SvtvA_TuremchikQuest.win_condition = "PKM_SvtvA_TuremchikQuest";
			
			sld = GetCharacter(NPC_GenerateCharacter("Satanist_Uchitel", "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, false));
			sld.name = "Teacher";
			sld.lastname = "";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Учитель_Смерть";
			ChangeCharacterAddressGroup(sld, "PortPax_prison", "goto",  "goto9");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

