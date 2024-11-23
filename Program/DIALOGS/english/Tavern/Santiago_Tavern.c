// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Just recently you tried to ask me a question " + GetAddress_Form(NPChar) + "...", "This is the third time you've talked about a question this day...",
                          "Are we going to ask questions again?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I have nothing to talk about right now."), "Hmm, something happened to my memory...",
                      "Yes, really for the third time...", "No, what questions...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "RevengeMansfield_toTavern": //Голландская линейка, квест №6. Узнать инфу о губере.
                    link.l2 = "How are you doing anyway? Is the city thriving?";
                    link.l2.go = "Step_H6_1";
                break;
                case "Fr7RockBras_toSeekPlace": //Фр. линейка, квест №7. Узнать инфу о Роке Бразильце.
					link.l1 = "I heard that a famous pirate, Rock the Brazilian, fell into the hands of the Inquisition...";
					link.l1.go = "Step_F7_1";
                break;
            }
            // <== Проверяем поле состояния квестов.
		break;
//**************************** Голл. линейка, квест №6. Узнать для Моргана инфу о губере Сантьяго ************************
 	 	case "Step_H6_1":
			dialog.text = "Praise Almighty God - we are doing well. The city is thriving.";
			link.l1 = "Surrounded by enemies, it is quite difficult to thrive. How do you do it?";
			link.l1.go = "Step_H6_2";
        break;
 	 	case "Step_H6_2":
			dialog.text = "Our governor, Jose Sancho Jimenez, knows how to solve problems. He recently got rid of the Buccaneer settlement on Hispaniola. It was a pretty business, I tell you!";
			link.l1 = "Wow! Did the Buccaneers bother you a lot?";
			link.l1.go = "Step_H6_3";
        break;
 	 	case "Step_H6_3":
			dialog.text = "No, for me, it was more convenient with them. I've always had good fresh meat for my kitchen. And cheap, too. And now it has become more difficult, everything is getting more expensive.";
			link.l1 = "Hmm, then why did your governor do that?";
			link.l1.go = "Step_H6_4";
        break;
 	 	case "Step_H6_4":
			dialog.text = "The devil knows. Probably because they were all dirty French. Hispaniola should be Spanish!";
			link.l1 = "Well, let it be... Listen, I want to join your governor's service. What do you recommend? Is he even in town?";
			link.l1.go = "Step_H6_5";
        break;
 	 	case "Step_H6_5":
			dialog.text = "Yes, he's here now. And you can easily get hired if you contact him personally.";
			link.l1 = "Understood... And he's not going anywhere in the near future, don't you know?";
			link.l1.go = "Step_H6_6";
        break;
 	 	case "Step_H6_6":
			dialog.text = "Yes, no, nowhere. We have a city holiday coming soon, so it will definitely be here... Hey, why do you need this?";
			link.l1 = "Just like that, just...";
			link.l1.go = "Step_H6_7";
        break;
 	 	case "Step_H6_7":
			dialog.text = "Simple, but not simple. If you want to get a job, then go and get one. Why do you need to know where the governor will be in the near future?";
			link.l1 = "What are you so excited about, I don't understand?! Sit there, roast meat, sell bacon...";
			link.l1.go = "Step_H6_8";
        break;
 	 	case "Step_H6_8":
			dialog.text = "You are "+ GetSexPhrase("suspicious, senor", "suspicious, dear senorita") +".\n"+
                          "Oh, officers, you are very timely! Take "+ GetSexPhrase("this man", "this woman") +"!";
			link.l1 = "Ah, devil!..";
			link.l1.go = "Step_H6_9";
        break;
 	 	case "Step_H6_9":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "3");
            QuestSetCurrentNode("Henry Morgan", "HolLine6_fromSantiago");
            //==> потом вернуть
            LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
            //<== потом вернуть
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
            LAi_group_MoveCharacter(characterFromID("Santiago_waitress"), "SPAIN_CITIZENS");
            LAi_group_Delete("QuestGroup");
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //если флаг сменён.
            ref sld;
            for (int i=1; i<=2; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Solder"+i, "off_spa_"+i, "man", "man", 30, SPAIN, 0, true));
                FantomMakeCoolFighter(sld, 30, 100, 80, "blade33", "pistol3", 120);

            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
            }
            LAi_group_SetLookRadius("EnemyFight", 100);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
            DialogExit();
        break;
//**************************** Фр. линейка, квест №7. Узнать инфу о Роке Бразильце ************************
 	 	case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat("That's right, he's with the holy fathers now.", "You already asked me about the Brazilian.",
				          "Again about the Brazilian?", "Well, how much can we talk about these pirates, let's talk about something else...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Heh, and when will they hang him now?", ""+ GetSexPhrase("Asked", "Asked") +"? Well, yes, probably...", "Yes, exactly, "+ GetSexPhrase("I asked", "I asked") +", sorry...", "We can talk about something else...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_F7_2":
			dialog.text = "Antonio de Souza himself has to say this now! He runs the affairs of the Holy Inquisition here now.";
			link.l1 = "But where is the Inquisition itself?";
			link.l1.go = "Step_F7_3";
        break;
 	 	case "Step_F7_3":
			dialog.text = "But where is she? Here in the city, "+ GetSexPhrase("senor", "senorita") +".\n"+
				          "In general, "+ GetSexPhrase("senor", "senorita") +", it would be better for us to stop these conversations. It's not good to remember the holy fathers in vain...";
			link.l1 = "Okay, be healthy, innkeeper.";
			link.l1.go = "exit";
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

