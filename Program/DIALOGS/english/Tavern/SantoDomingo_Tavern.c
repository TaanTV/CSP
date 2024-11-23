// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the gossip of the city "+ GetCityName(npchar.city) +" at your service. What would you like to know?",
                          "We have just raised this issue. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Why are you talking like a parrot? The same thing...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Yeah...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = "Ask your questions, "+ GetSexPhrase("senor", "senorita") +".";
				link.l1 = "I heard that we recently managed to capture Rock the Brazilian, that pirate!";
				link.l1.go = "Step_F7_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PK_IshemKoltso"))	// Квест "The Lost Ring"
            {
                link.l1 = "I'm looking for a ring that belonged to... to one of my friends. Quite a valuable ring. And this ring is located somewhere in this city. Maybe you've heard something about him? A large sapphire set in gold.";
                link.l1.go = "IshemKoltso";
            }
			if(PChar.MysteriousIsland == "10" && PChar.MysteriousIsland.FindForser.Tavern == false && NPChar.City == "SantoDomingo")	//Квест "The Mysterious Island"
			{
				link.l1 = "Did a certain Davy Forser come to you?";
				link.l1.go = "MysteriousIsland_2";
			}
		break;
//******************** Фр.линейка, квест №7. Спасение Рока Бразильца ******************
 	 	case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat("Yes, that's right, it was a case. Unheard-of luck, I'll tell you, "+ GetSexPhrase("senor", "senorita") +".", "You already asked me about the Brazilian.",
				          "Again about the Brazilian?", "Well, how much can we talk about these pirates, let's talk about something else...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("That's right, that's right... And what was done to him? Probably strangled right there.", ""+ GetSexPhrase("Asked", "Asked") +"? Well, yes, probably...", "Yes, exactly, "+ GetSexPhrase("I asked", "I asked") +", sorry...", "We can talk about something else...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_F7_2":
			dialog.text = "What are you, "+ GetSexPhrase("senor", "senorita") +". They brought it and showed it to everyone. And then they gave it to the holy fathers...";
			link.l1 = "And why do the holy fathers need it?";
			link.l1.go = "Step_F7_3";
        break;
 	 	case "Step_F7_3":
			dialog.text = "Heh, "+ GetSexPhrase("senor", "senorita") +", these are not confessors. Those holy fathers are militant monks! The Inquisition...";
			link.l1 = "Uh-uh, the case is clear. Well, thank you, friend.";
			link.l1.go = "exit";
        break;
//******************** Квест "The Lost Ring" ******************
		case "IshemKoltso":
			dialog.text = "Hmmm... A sapphire, you say? Yes, I remember seeing a ring like the one you're talking about. One girl has it-maybe you even know her-at least most sailors know her well, hehe. Her name is Francesca. I've never met a dumber girl, to be honest. Some soldier gave her this ring a couple of years ago. Maybe he was even more stupid than she was, because this ring is worth a lot of money. Yes, this is probably the ring that you are looking for, so do you want to arrange a competition with your officers, who will drink the most?";
			link.l1 = "Great idea! I think I'll bring the team. Wait for me here, don't go anywhere -I'll be back soon.";
			link.l1.go = "IshemKoltso_2";
        break;
		
		case "IshemKoltso_2":
			DialogExit();
			
			AddQuestRecord("PDM_Poteryanoe_Koltso", "3");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "a"));
			DeleteAttribute(pchar, "questTemp.PDM_PK_IshemKoltso");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_PK_Francheska", "BaynesDaughterSTOK", "woman", "woman", 10, SPAIN, -1, false));
			sld.name = "Francesca";
			sld.lastname = "";
			sld.city = "SantoDomingo";
			sld.location	= "SantoDomingo_Brothel";
			sld.location.group = "goto";
			sld.location.locator = "goto3";
			sld.dialog.filename   = "Quest\PDM\Poteryanoe_Koltso.c";
			sld.dialog.currentnode   = "Francheska";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			LAi_SetImmortal(sld, true);
        break;
		
		// Загадочный остров -->
		case "MysteriousIsland_2":
			PChar.MysteriousIsland.FindForser.Tavern = true;
			dialog.text = "Davy Forser? I've never heard of it.";
			link.l1 = LinkRandPhrase("Oh, sorry...", "Thanks for that.", "See you soon.");
			link.l1.go = "exit";
		break;
		// Загадочный Остров <--
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

