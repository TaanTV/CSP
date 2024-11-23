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

			if (CheckAttribute(pchar, "questTemp.PDM_ONV_SanJuan"))	//Квест "Witch Hunt"
            {
                link.l1 = "Does the name Maria Carle mean anything to you?";
                link.l1.go = "PDM_ONV_SJ_1";
            }
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_PoiskPadre_Tavern"))	//Квест "Strange things are happening in the archipelago"
            {
                link.l1 = "I would like to know what rumors are circulating about the kidnapping of a local priest.";
                link.l1.go = "PKM_SvtvA_PPT_1";
            }

            // ==> Проверяем поле состояния квестов. Эдди.
			switch(pchar.questTemp.State)
            {
                case "MorrisWillams_PinnaceNotFound":
                    link.l2 = "It's been a while since I've been here... What's new in San Juan?";
                    link.l2.go = "Step_E6_1";
                break;
            }
		break;
        //---------------- квесты --------------------
        case "Step_E6_1":
			dialog.text = "In general, everything is the same as before. The city is thriving.";
			link.l1 = "I see... listen, did the pinnace Santa Agueda enter the city?";
			link.l1.go = "Step_E6_2";
		break;
        case "Step_E6_2":
			dialog.text = "Yes, I came straight from somewhere, but from Port Royal!";
			link.l1 = "Wow! Is there peace with the British?";
			link.l1.go = "Step_E6_3";
		break;
        case "Step_E6_3":
			dialog.text = "Yes, not to say peace, but not war anymore. The British are having clashes with the Dutch now, so relations are improving in the Old World.";
			link.l1 = "Well, that's for the best... And where is this pinnace now?";
			link.l1.go = "Step_E6_4";
		break;
        case "Step_E6_4":
			dialog.text = "Unloaded the holds and left. Now San Juan is littered with indigo and silver. Prices have dropped...";
			link.l1 = "So is the cargo from the pinnace sold out?";
			link.l1.go = "Step_E6_5";
		break;
        case "Step_E6_5":
			dialog.text = "Of course! And why do you need this pinnace?";
			link.l1 = "Yes I am "+ GetSexPhrase("agreed", "agreed") +"that this cargo will be given to me, and they sold everything here...";
			link.l1.go = "Step_E6_6";
		break;
        case "Step_E6_6":
			dialog.text = "Well, next time, make an agreement with someone else.";
			link.l1 = "That's right, buddy. Thank you, be healthy.";
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_2PinnaceNotFound";
		break;

		case "PDM_ONV_SJ_1":	//Квест "Witch Hunt"
			dialog.text = "This name doesn't mean anything to me. But you're lucky, that man at the table said that name more than once when he was swallowing rum in a frenzied rage.";
			link.l1 = "How did you help me out. Thank you!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_SanJuan");
			if(InterfaceStates.EnabledQuestsMarks)
			{
				sld = CharacterFromID("PDM_ONV_Viktor_Martos");
				sld.quest.questflag.model = "questionmarkY";
			}
		break;
		
		case "PKM_SvtvA_PPT_1":	//Квест "Strange things are happening in the archipelago"
			dialog.text = "Yes, the whole colony is talking about it! Imagine, they broke into the church in the middle of the day and kidnapped him! No one even had time to blink an eye as they disappeared!";
			link.l1 = "And who were they? People in red robes?";
			link.l1.go = "PKM_SvtvA_PPT_2";
		break;
		
		case "PKM_SvtvA_PPT_2":
			dialog.text = "No. They were ordinary thugs. But it's strange that you mentioned people in red robes...";
			link.l1 = "Yes? Why is that?";
			link.l1.go = "PKM_SvtvA_PPT_3";
		break;
		
		case "PKM_SvtvA_PPT_3":
			dialog.text = "The fact is that recently a guy appeared here dressed exactly as you said...";
			link.l1 = "Really? And what happened next?";
			link.l1.go = "PKM_SvtvA_PPT_4";
		break;
		
		case "PKM_SvtvA_PPT_4":
			dialog.text = "Nothing that might interest you. These are our internal problems.";
			link.l1 = "Maybe you can tell me about them after all? It seems to me that these two events are connected.";
			link.l1.go = "PKM_SvtvA_PPT_5";
		break;
		
		case "PKM_SvtvA_PPT_5":
			dialog.text = "Maybe you're right. I will. Listen\nThree years ago, we had this guy in red chlamydia. He is so polite, never say a bad word to anyone...";
			link.l1 = "Go on.";
			link.l1.go = "PKM_SvtvA_PPT_6";
		break;
		
		case "PKM_SvtvA_PPT_6":
			dialog.text = "Well, somehow everyone started to squint at him, but he didn't do anything wrong, he talked to the young people, but we were even glad - for once they didn't hang around.";
			link.l1 = "And?";
			link.l1.go = "PKM_SvtvA_PPT_7";
		break;
		
		case "PKM_SvtvA_PPT_7":
			dialog.text = "Heh, and then something happened. Now honor all the young guys going on some hike with him\nThe blacksmith's son left the house at all, the blacksmith went to talk to this guy, and ran out of his house like a boil, and at night he got drunk and drowned - he went to the pier\nAnd his son did not even notice. He lives as usual.";
			link.l1 = "Yes, it's all weird. Where can I find this guy??";
			link.l1.go = "PKM_SvtvA_PPT_8";
		break;
		
		case "PKM_SvtvA_PPT_8":
			dialog.text = "The son of a blacksmith? Yes, he's wandering around the city somewhere. And this guy in a hoodie has disappeared somewhere.";
			link.l1 = "Okay, I'll go talk to him, what's his name?";
			link.l1.go = "PKM_SvtvA_PPT_9";
		break;
		
		case "PKM_SvtvA_PPT_9":
			dialog.text = "His name is Giordano.";
			link.l1 = "Thank you.";
			link.l1.go = "PKM_SvtvA_PPT_10";
		break;
		
		case "PKM_SvtvA_PPT_10":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_PoiskPadre_Tavern");
			AddQuestRecord("PKM_Animists", "25");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("", "a"));
			
			sld = GetCharacter(NPC_GenerateCharacter("PKM_Jordano", "Jordano", "man", "man1", 10, PIRATE, -1, false));
			sld.name = "Giordano";
			sld.lastname = "";
			LAi_SetStayType(sld);
			sld.City = "SanJuan";
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Джордано_1";
			ChangeCharacterAddressGroup(sld, "SanJuan_town", "patrol", "patrol16");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

