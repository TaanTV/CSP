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
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = "Ask your questions, "+ GetSexPhrase("senor", "senorita") +".";
				link.l1 = "I heard that we recently managed to capture Rock the Brazilian, that pirate!";
				link.l1.go = "Step_F7_1";
				break;
			}
			Link.l1.go = "exit";
            if (pchar.questTemp.Ascold == "ToHavanna") // квест Аскольда
            {
    			Link.l1 = "Listen, the city is unusually calm today. There is no fuss, everything is quiet... Why would that be?";
    			Link.l1.go = "Step_A1";
            }
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Listen, has Francois Gontier appeared in your city? By the way, he has a corvette '" + pchar.questTemp.Slavetrader.ShipName+ "'... ";
                link.l1.go = "Havana_ratT_1";
            }
		break;
//******************** Фр.линейка, квест №7. Спасение Рока Бразильца ******************
 	 	case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat("Yes, that's right, it was a case. Unheard-of luck, I'll tell you, "+ GetSexPhrase("senor", "senorita") +".", "You already asked me about the Breezy.",
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
//******************** Квест Аскольда, узнаем о мановарах с ипанским добром ******************
		case "Step_A1":
			dialog.text = "Heh, yeah. People are exhausted, so they don't have the strength for the usual fuss. And the whole point is that only the day before yesterday they finally sent a man...";
			Link.l1 = "What kind of man?";
			Link.l1.go = "Step_A2";
		break;

		case "Step_A2":
			dialog.text = "Yes, a ship loaded with all sorts of junk. The Governor-General of Oregon and Gascon himself ordered all citizens to engage in loading. They carried all sorts of junk: mosaics, jugs, various Indian gods - ugh!";
			Link.l1 = "Here you go! And why is that? Spaniards used to melt everything into bars, but now what kind of a whim?";
			Link.l1.go = "Step_A3";
		break;

		case "Step_A3":
			dialog.text = "So what do you think, they were golden, these idols? Where is there, a stone and a tree...";
			Link.l1 = "Marianne has gone completely crazy. And where did this man go?";
			Link.l1.go = "Step_A4";
		break;

		case "Step_A4":
			dialog.text = "You talk, but don't talk too much, the Queen mother is in our esteem. And who are you? And why do you need to know where Man went?";
			Link.l1 = "There's no need, I asked... Sorry to be rude, I didn't mean to offend anyone.";
			Link.l1.go = "Step_A5";
		break;

		case "Step_A5":
			dialog.text = "That's fine, if didn't mean. But watch out, don't stick your nose where you don't get - you'll inadvertently end up behind bars.";
			Link.l1 = "Okay... What wrong did I do to you? I think I'll go...";
			Link.l1.go = "exit";
			pchar.questTemp.Ascold = "SeekInformatorHavanna";
			AddQuestRecord("Ascold", "6");
            ref sld = GetCharacter(NPC_GenerateCharacter("FernandoGonsales", "off_spa_1", "man", "man", 28, SPAIN, -1, true));
            FantomMakeCoolFighter(sld, 28, 90, 70, BLADE_LONG, "pistol3", 10);
            LAi_SetStayType(sld);
           	sld.name 	= "Fernando";
			sld.lastname 	= "Gonzalez";
			sld.Dialog.Filename = "Quest\AscoldNpc.c";
			ChangeCharacterAddressGroup(sld, "Santiago_houseSp2", "goto", "goto2");
            LAi_LocationFightDisable(&Locations[FindLocation("Santiago_houseSp2")], true);
		break;

		case "Havana_ratT_1":
			dialog.text = "Ah, this gloomy guy? Yes, he came to my place, stopped by. I'll tell you a secret: he went to an appointment with Oregon and Gascon himself. I applied for a patent. But something didn't burn out there, and he got away.";
			Link.l1 = "And where did he go, do you know? I've been reaching for him since Porto Bello, but I still can't find him.";
			Link.l1.go = "Havana_ratT_2";
		break;

		case "Havana_ratT_2":
			dialog.text = "Why do you need him? He is afraid of strangers - he always hides from everyone, as soon as he sees an armed stranger, he grabs a sword. He walks only accompanied by four guards. Isn't he so careful of you?";
			Link.l1 = "My God, what kind of punishment is this! Am I look like murderer? He's my friend, I'm in a hurry to tell him the news, which will make him very, very happy, and he doesn't have to hide anymore - no one is looking for him.";
			Link.l1.go = "Havana_ratT_3";
		break;

		case "Havana_ratT_3":
			dialog.text = "Don't? Ha ha ha! Yes, only the day before his departure from Havana, a whole pack of ragamuffins attacked him in the jungle... Well, he and his men, however, crumbled them into cabbage in a flash. And you say...";
			Link.l1 = "Come on. Probably, the local bandits coveted his purse. You know how many scum are roaming the jungle right now. So where did he go?";
			Link.l1.go = "Havana_ratT_4";
		break;

		case "Havana_ratT_4":
			dialog.text = "Well, after he was turned away from us, he mumbled that he would go to the frogs, his compatriots. He went to Tortuga, to d'Ogeron... He was muttering something else about his mistress, but I still didn't really understand.";
			Link.l1 = "To Tortuga, then? Great! I hope I'll catch up with him there at least. Thank you, " + npchar.name + ", you helped me a lot. Goodbye.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

