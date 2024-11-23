// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the gossip of the city "+ GetCityName(npchar.city) +" at your service. What would you like to know?",
                          "We just brought up this topic. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "You are like a parrot, talking the same thing...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Yeah...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = "Ask your questions, "+ GetSexPhrase("senor", "senorita") +".";
				link.l1 = "I heard that you recently managed to capture Rock the Brazilian!";
				link.l1.go = "Step_F7_1";
			}
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Tavern_NET"))	// Квест "Witch Hunt"
            {
                link.l1 = "I need a girl... by the name of Maria. Where can I find her?";
                link.l1.go = "PDM_ONV_Sprashivaem_Pro_Karlu_NeZnaet";
            }
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Tavern_DA"))	// Квест "Witch Hunt"
            {
                link.l1 = "I need a girl... by the name of Maria. Where can I find her?";
                link.l1.go = "PDM_ONV_Sprashivaem_Pro_Karlu";
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
//******************** Квест "Witch Hunt" ******************
		case "PDM_ONV_Sprashivaem_Pro_Karlu_NeZnaet":
			dialog.text = "I don't know any Maria. And we don't provide any other services here- except food or drink. Would you like a drink?";
			Link.l1 = "No, thanks. I'm going to go.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Tavern_NET");
			AddQuestRecord("PDM_Ohota_na_vedmu", "6");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "a"));
			pchar.questTemp.PDM_ONV_Detectiv_Jiteli_Beliz = true;
			pchar.questTemp.PDM_ONV_Detectiv_Oficiantka_Beliz = true;
		break;

		case "PDM_ONV_Sprashivaem_Pro_Karlu":
			dialog.text = "I already told you that there is no Maria here!";
			Link.l1 = "She is accused of witchcraft! Do you know what that means? That she's a WITCH, and if you cover for her, you'll burn at the same bonfire as her. Is that clear? People have seen her enter your tavern more than once. So, are you going to lock up, or...?";
			Link.l1.go = "PDM_ONV_SPKarlu_2";
		break;

		case "PDM_ONV_SPKarlu_2":
			dialog.text = "Oh, spare me, "+ GetSexPhrase("senor", "senorita") +" captain! I didn't want to break the law-just... I'm barely making ends meet... I had no choice but to let whores bring clients here.";
			Link.l1 = "Well, I suppose a couple of thousand dollars can mitigate your guilt. But I need to know where she is.";
			Link.l1.go = "PDM_ONV_SPKarlu_3";
			Link.l2 = "Your petty complaints don't interest me. I just want to know where she is.";
			Link.l2.go = "PDM_ONV_SPKarlu_5";
		break;

		case "PDM_ONV_SPKarlu_3":
			dialog.text = "Oh, "+ GetSexPhrase("senor", "senorita") +" - you will ruin me and my business! I have to pay the tax collector next month! Two thousand, it's just impossible! You threatened me with death at the stake, and now you want me to starve to death?!";
			Link.l1 = "You're just an insignificant sinner... Well, tell me where Maria is and I'll leave you. May the Lord forgive you.";
			Link.l1.go = "PDM_ONV_SPKarlu_5";
			Link.l2 = "You've been harboring public enemies in your tavern-so you're going to have to pay one way or another.";
			Link.l2.go = "PDM_ONV_SPKarlu_4";
		break;

		case "PDM_ONV_SPKarlu_4":
			dialog.text = "Oh, you ruined my life! Yes, take the gold - but you will be damned forever!";
			Link.l1 = "Think about your fate, you miserable sinner! If you don't tell me where Maria is, then your screams from the governor's dungeon will disturb the people of Belize for a long time.";
			Link.l1.go = "PDM_ONV_SPKarlu_5";
			ChangeCharacterReputation(pchar, -2);
			AddMoneyToCharacter(pchar, 2000);
		break;

		case "PDM_ONV_SPKarlu_5":
			dialog.text = "Yes, yes, she was here! But she sailed recently with a captain. When she told me she was leaving, I almost burst into tears. Such a good girl has finally found her destiny. Her captain was "+ GetSexPhrase("a real man, just like you - just as strong and brave", "a strong and brave man, just like you.") +"...";
			Link.l1 = "What was his name?";
			Link.l1.go = "PDM_ONV_SPKarlu_6";
		break;

		case "PDM_ONV_SPKarlu_6":
			dialog.text = "Miguel Cuenda, as far as I remember. He sailed away and took Maria Carle with him. And... forgive me, "+ GetSexPhrase("senor", "senorita") +" - I ask you not to tell her that I informed on her. I don't want her to curse my name forever...";
			Link.l1 = "I won't tell her. But you have to tell me where they went.";
			Link.l1.go = "PDM_ONV_SPKarlu_7";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Tavern_DA");
		break;

		case "PDM_ONV_SPKarlu_7":
			int Isp_Coloni
			Isp_Coloni = rand(2);
			if (Isp_Coloni == 0)
			{
				dialog.text = "I have no thoughts on this, "+ GetSexPhrase("senor", "senorita") +" captain. I remember that she said something about some kind of colony-Spanish, of course... And there were two letters: 'p' and 'b'.";
				Link.l1 = "I believe you. But remember - you have to take good care of your dirty, but alas, immortal soul. Have a nice day!";
				Link.l1.go = "exit";
				AddQuestRecord("PDM_Ohota_na_vedmu", "8");
				AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "a"));

				sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Viktor_Martos", "officer_22", "man", "man", 10, SPAIN, -1, false));
				sld.name = "Silino";
				sld.lastname = "Sav";
				sld.city = "PortoBello";
				FreeSitLocator("PortoBello_tavern", "sit_base2");
				ChangeCharacterAddressGroup(sld, "PortoBello_tavern", "sit", "sit_base2");
				LAi_SetSitType(sld);
				sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
				sld.dialog.currentnode   = "RazgovorSViktorom_1";
				pchar.questTemp.PDM_ONV_PortoBello = true;
			break;
			}
			if (Isp_Coloni == 1)
			{
				dialog.text = "I have no thoughts on this, "+ GetSexPhrase("senor", "senorita") +" captain. I remember that she said something about some kind of colony-Spanish, of course... And there were two letters: 'm' and 'b'.";
				Link.l1 = "I believe you. But remember - you have to take good care of your dirty, but alas, immortal soul. Have a nice day!";
				Link.l1.go = "exit";
				AddQuestRecord("PDM_Ohota_na_vedmu", "9");
				AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "a"));

				sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Viktor_Martos", "officer_22", "man", "man", 10, SPAIN, -1, false));
				sld.name = "Silino";
				sld.lastname = "Sav";
				sld.city = "Maracaibo";
				FreeSitLocator("Maracaibo_tavern", "sit_base2");
				ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_base2");
				LAi_SetSitType(sld);
				sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
				sld.dialog.currentnode   = "RazgovorSViktorom_1";
				pchar.questTemp.PDM_ONV_Maracaibo = true;
			break;
			}
			if (Isp_Coloni == 2)
			{
				dialog.text = "I have no thoughts on this, "+ GetSexPhrase("senor", "senorita") +" Captain. I remember that she said something about some kind of colony-Spanish, of course... And there were two letters: 'S' and 'J'.";
				Link.l1 = "I believe you. But remember - you have to take good care of your dirty, but alas, immortal soul. Have a nice day!";
				Link.l1.go = "exit";
				AddQuestRecord("PDM_Ohota_na_vedmu", "10");
				AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("", "a"));

				sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Viktor_Martos", "officer_22", "man", "man", 10, SPAIN, -1, false));
				sld.name = "Silino";
				sld.lastname = "Sav";
				sld.city = "SanJuan";
				FreeSitLocator("SanJuan_tavern", "sit_base2");
				ChangeCharacterAddressGroup(sld, "SanJuan_tavern", "sit", "sit_base2");
				LAi_SetSitType(sld);
				sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
				sld.dialog.currentnode   = "RazgovorSViktorom_1";
				pchar.questTemp.PDM_ONV_SanJuan = true;
			break;
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

