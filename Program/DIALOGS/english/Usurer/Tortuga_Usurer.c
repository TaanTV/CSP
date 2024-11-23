// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want?"), "Just recently you tried to ask me a question...", "Well, let me guess... Nothing significant again?",
                          "Listen, I'm handling finances, not answering questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "You guessed it, I'm sorry...", "I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			if (CheckAttribute(pchar, "questTemp.PDM_PI_Rostov"))	//Квест 'Проклятый Идол'
			{
    			link.l1 = "I want to give you a gift. I heard that you are interested in gems... What do you say about this idol?";
				link.l1.go = "PDM_PI_Rostov_2";
			}
			switch(pchar.questTemp.State)
            {
                case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
                    link.l2 = "Listen, I would like to offer you one financial transaction...";
                    link.l2.go = "Step_H3_1";
                break;

            }
             // <== Проверяем поле состояния квестов.
		break;

		//Квест 'Проклятый Идол'
		case "PDM_PI_Rostov_2":
			dialog.text = "Oh-oh-oh! Oh, my God! "+ GetSexPhrase("Monsieur", "Mademoiselle") +" "+pchar.name+"! How wonderful! That's great! Yes, this idol can atone for all ten mortal sins!";
			link.l1 = "You seem to like him. He's yours.";
			link.l1.go = "PDM_PI_Rostov_3";
        break;

		case "PDM_PI_Rostov_3":
			dialog.text = "You have given me a priceless gift, "+ GetSexPhrase("monsieur", "mademoiselle") +" "+pchar.name+". I am extremely grateful to you. I am rewarding you with 45,000 gold - nobody will say that I am a miser! By the way, "+ GetSexPhrase("monsieur", "mademoiselle") +" "+pchar.name+", I think I'll send this idol to His Majesty! I've heard that he's just into such interesting things.";
			link.l1 = "I am very glad that my gift turned out to be so useful.";
			link.l1.go = "PDM_PI_Rostov_4";
			AddMoneyToCharacter(pchar, 45000);
			Log_info("You gave an idol to a usurer");
			TakeItemFromCharacter(pchar, "Cursed_idol");
        break;

		case "PDM_PI_Rostov_4":
			dialog.text = "Yes, yes, your gift was very timely. But I have to ask you to leave. I want to admire... uh, I mean, I want to think about how to send this idol to His Majesty.";
            link.l1 = "(door opens from behind)";
			link.l1.go = "Rostovshik_5";
			bDisableFastReload = true;
			DeleteAttribute(pchar, "questTemp.PDM_PI_Rostov");
			DeleteAttribute(pchar, "questTemp.PDM_PI_Skelety_v_more");
        break;

		case "Rostovshik_5":
			DialogExit();
			int Phrase;
			Phrase = rand(4);
			if (Phrase == 0)
            {
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "skel1", "skeleton", "skeleton", sti(pchar.rank), PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 15 + MOD_SKILL_ENEMY_RATE * 5, 15 + MOD_SKILL_ENEMY_RATE* 5, "blade19", "", 20);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename   = "Quest\PDM\Cursed_Idol.c";
				sld.dialog.currentnode   = "Rostovshik_Fra_Off_3";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				sld.DeleteFood = true;
				AddMoneyToCharacter(sld, 7000);
				AddItems(sld, "jewelry1", 25);
				AddItems(sld, "jewelry7", 10);
				AddItems(sld, "compcraft_copper", 20);
				AddItems(sld, "compcraft_grindstone", 20);
			break;
			}
			else
            {
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "pirate_22", "man", "man", sti(pchar.rank), PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 15 + MOD_SKILL_ENEMY_RATE * 5, 15 + MOD_SKILL_ENEMY_RATE* 5, "blade19", "", 20);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename   = "Quest\PDM\Cursed_Idol.c";
				sld.dialog.currentnode   = "Rostovshik_Fra_Off_1";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				sld.DeleteFood = true;
				AddMoneyToCharacter(sld, 7000);
				AddItems(sld, "jewelry1", 25);
				AddItems(sld, "jewelry7", 10);
				AddItems(sld, "compcraft_copper", 20);
				AddItems(sld, "compcraft_grindstone", 20);
			break;
			}
		break;

		//Голландская линейка, квест №3
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat("I want to say right away that I don't take money on loan. Borrow is please.", "Is it the same financial transaction again?", "Will we offer money again?", "Let's get busy, and not talk about business.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Why is that?", "Yes, it's the same again...", "Again...", "Let's...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = "Pierre Picardy provided me with a substantial sum, I would like to master this money. So, are you taking it?";
			link.l1 = "No, I just wanted to give you the money.";
			link.l1.go = "exit";
            pchar.questTemp.Talks.Usurer = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "10");
        break;



	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

