// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, "+ GetSexPhrase("my son", "my daughter") +"?", "Ask, I'm listening to you..."), "I'm listening to you, tell me, "+ GetSexPhrase("my son", "my daughter") +"...", "And for the third time I tell you, "+ GetSexPhrase("my son", "my daughter") +": ask your question.",
                          "A clergyman has so many responsibilities, and then you're bothering, "+ GetSexPhrase("my son", "my daughter") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind..", "Not now, Padre..."), "Yes, there's not much to say yet...",
                      "I'll ask, I'll ask... Only later...", "Excuse me, Holy Father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfo" || pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfoFather")
            {
                link.l1 = "Holy Father, tell me, is the local usurer your parishioner?";
                link.l1.go = "Step_E6_1";
            }
		break;
		
        case "Step_E6_1":
			dialog.text = "Yes, he attends church, but very rarely.";
			link.l1 = "What kind of person is he?";
			link.l1.go = "Step_E6_2";
		break;

        case "Step_E6_2":
			dialog.text = "It's hard for me to talk badly about people\n"+
                          "I would advise you to contact one of our parishioners, Gillian Atterbury. I know that she has serious problems with this man. Perhaps you can even help her in some way\n"+
                          "Gillian is a good parishioner, as a rule she goes to church from eleven o'clock in the morning every day and prays for two or three hours\n"+
                          "In general, you can meet her in the city.";
			link.l1 = "Thank you, Holy Father.";
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_ArrestedSeekInfoWomen";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "19");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("", "a"));
            ref sld = GetCharacter(NPC_GenerateCharacter("Gillian Atterbury", "girl_8", "woman", "towngirl", 5, ENGLAND, 100, false));
        	sld.name 	= "Gillian";
        	sld.lastname = "Atterbury";
        	LAi_SetCitizenType(sld);
            sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
            LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
           	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", "goto1");
			LAi_SetFanatic(sld, "PortRoyal_church", "sit", "sit1", 11.0, 14.0);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

