// Секретать Моргана и актёр для сложных диалогов с действиями.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    sld = characterFromID("Henry Morgan");

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (sld.location == pchar.location && bWorldAlivePause)
            {
    			dialog.text = "If you're going to the admiral, then go a little further. He's at the residence now.";
    			link.l1 = "Okay, I'll go talk to him.";
            }
            else
            {
    			if (pchar.questTemp.piratesLine == "Panama_inEngland" || pchar.questTemp.piratesLine == "Panama_backToShip")
				{
					dialog.text = "The Admiral went to London. He won't be here for at least a year.";
    				link.l1 = "I see...";
				}
				else
				{
					dialog.text = "The Admiral is not in place - absent on business. Now don't bother me, I'm very busy.";
    				link.l1 = "If Morgan is not here, then I have nothing to do in this house.";
				}
            }
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "My name is " + GetFullName(npchar) + ". I'm Henry Morgan's secret.";
				link.l1 = "My name is " + GetFullName(pchar) + ".";
				link.l1.go = "First time";
				npchar.quest.meeting = "1";
			}
            //============>>>>>>>>> перехват квестовых диалогов
            if (pchar.questTemp.State == "WormEnglPlans_toMorgan")  // HolLine_3, переадресовка в Антигуа.
            {
    			link.l1 = "Listen, I need Morgan, and I need him very urgently.";
    			link.l1.go = "Step_H3_1";
            }
            if (pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek")  // FraLine_8, переадресовка в Антигуа.
            {
    			link.l1 = "Monsieur, I wanted  I would like to talk to Henry Morgan. Where can I find him?";
    			link.l1.go = "Step_F8_1";
            }
            // квест Аскольда. Пасхалка на получение индейских предметов.
            if (pchar.questTemp.Ascold == "SeekThreeObject" && !CheckAttribute(pchar, "questTemp.Ascold.Oliver"))
            {
    			link.l2 = "Listen, you're running Morgan's business. Did you come across any Indian items in the prize accounting reports?";
    			link.l2.go = "Step_As_1";
            }
            if (pchar.questTemp.Ascold == "SeekThreeObject" && CheckAttribute(pchar, "questTemp.Ascold.Oliver"))
            {
    			link.l2 = "Oliver, maybe you'll change your mind about the price of those Indian items I told you about?";
    			link.l2.go = "Step_As_7";
            }
            if (pchar.questTemp.Azzy == "DestrContract" || pchar.questTemp.Azzy == "2DestrContract")
            {
                if (!CheckAttribute(pchar, "questTemp.Azzy.Oliver"))
                {
        			link.l2 = "Oliver, listen, I want to ask you for help. I really need Indian trinkets. We are talking about three Toltec crystal skulls and a strange thing that looks like a rattle.";
        			link.l2.go = "Step_As_9";
        		}
            }
            //============>>>>>>>>> перехват квестовых диалогов
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
		//********************* Голландская линейка *********************
        case "Step_H3_1":
            dialog.text = "Who are you and why do you need Henry?";
            link.l1 = "My name is " + GetFullName(pchar) + ", Edward Mansfield sent me to Morgan.";
            link.l1.go = "Step_H3_2";
        break;
        case "Step_H3_2":
            dialog.text = "Dutch? Are you dutchman?";
            link.l1 = "What do you care what nation I am? I have business with Morgan from Mansfield, what else is not clear to you?";
            link.l1.go = "Step_H3_3";
        break;
        case "Step_H3_3":
            dialog.text = "Don't get excited, "+ GetSexPhrase("mynheer", "mistress") +", everything is fine. There are a lot of Dutch pirates, but it's not safe for you to be in Port Royal right now\n"+
                          "So I'll tell you what: Morgan is in Antigua, at his house. Be careful there too - if I recognize holland in you, then it will not be a secret for others either\n"+
                          "And also, it's not that easy to get into Morgan's house, the door only works for the exit, hehe... Look for the dungeon under St. John's, it will lead you to Henry...";
            link.l1 = "Thank you, Oliver.";
            link.l1.go = "exit";
            pchar.questTemp.State = "WormEnglPlans_toMorganAntigua";
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "3");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("", "a"));
        break;
		//********************* Французская линейка *********************
 	 	case "Step_F8_1":
			dialog.text = NPCStringReactionRepeat("Who are you so"+ GetSexPhrase("oh, sir", "aya, miss") +"?", "I already answered you...",
				          "I repeat, I have already answered this question for you.", "You should not bother me, I will not say anything more.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("My name is " + GetFullName(pchar) + ", I am acting on behalf of the French government.", "Yes, that's right...", "Yes, I remember...", "Okay.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F8_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
        case "Step_F8_2":
            dialog.text = "What business does the French government need Henry Morgan for?";
            link.l1 = "Listen, my dear, don't you think you're too talkative for a secretary?";
            link.l1.go = "Step_F8_3";
        break;
        case "Step_F8_3":
            dialog.text = "Okay, okay, "+ GetSexPhrase("monsieur", "mademoiselle") +"... Morgan is currently at his home in Antigua.";
            link.l1 = "Well, that's nice. I'm going there immediately!";
            link.l1.go = "Step_F8_4";
        break;
        case "Step_F8_4":
            dialog.text = ""+ GetSexPhrase("Monsieur", "Mademoiselle") +", keep in mind that it is not so easy to get into Morgan's house in St. John's, the door is always locked there. The entrance is through the dungeon...";
            link.l1 = "Let's figure it out...";
            link.l1.go = "exit";
        break;
		//********************* Квест Асокльда *********************
   		case "Step_As_1":
			dialog.text = "What kind of questions are so strange?! Maybe I have, but why should I tell you about it?";
			link.l1 = "Don't get all worked up. The thing is, I'm looking for three objects of Indian worship. For purchase. It's all the same - you either throw this stuff away or sell it for next to nothing. I'm ready to pay handsomely for these things, if you have them.";
			link.l1.go = "Step_As_2";
		break;
   		case "Step_As_2":
			dialog.text = "What kind of things?";
			link.l1 = "Tlaloc Indian statuette, ceremonial vessel and ceremonial knife.";
			link.l1.go = "Step_As_3";
		break;
   		case "Step_As_3":
			dialog.text = "Heh, all these things are made of precious metals. We melt them into bars and send them to jewelers in Europe for work. There's a lot of demand, you know, good prices...";
			link.l1 = "I understand. I'm ready to pay two prices for these Indian trinkets, only in non-melted form, so to speak... Do you actually have these things? Or are we having a stupid conversation?";
			link.l1.go = "Step_As_4";
		break;
   		case "Step_As_4":
			dialog.text = "I have these things. And, in principle, I will be ready to sell them to you. But only two prices are not a subject for serious conversation. Too little.";
			link.l1 = "How much do you want?";
			link.l1.go = "Step_As_5";
		break;
   		case "Step_As_5":
			dialog.text = "Million.";
			link.l1 = "What?!!! Are you crazy?!";
			link.l1.go = "Step_As_6";
		break;
   		case "Step_As_6":
			dialog.text = "Not at all. What do you think, for some two prices, the size of three thousand, I will withdraw something from the Morgan prize? You're crazy, "+ GetSexPhrase("my friend", "girlfriend") +", if you don't know how it might end for me. If you don't like it, go to the shops and try to buy there.";
			link.l1 = "Damn it, Oliver!";
			link.l1.go = "Step_As_7";
			pchar.questTemp.Ascold.Oliver = 1;
		break;
   		case "Step_As_7":
			dialog.text = "Okay, stop talking. Are you taking it or not?";
			link.l1 = RandPhraseSimple("No way! For such money, I'll buy the whole Port Royal!", "For a million? Oh, come on! No, of course not.");
			link.l1.go = "exit";
            if (sti(pchar.money) >= 1000000)
            {
    			link.l2 = "Oh, I take it! And wrap it up for me in a gift box!";
    			link.l2.go = "Step_As_8";
            }
            else
            {
    			link.l2 = "I would take, but there is no such money. I'll go, maybe I'll earn more...";
    			link.l2.go = "exit";
            }
		break;
   		case "Step_As_8":
			dialog.text = GetFullName(pchar) + ", nice to do business with you. Get your priceless artifacts! I hope they will bring you good luck, since you are ready to paying such money for them...";
			link.l1 = "I hope so too, Oliver.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			DeleteAttribute(pchar, "questTemp.Ascold.Oliver");
			pchar.questTemp.Ascold = "SoughtThreeObject";
    		GiveItem2Character(pchar, "indian19");
    		GiveItem2Character(pchar, "indian20");
    		GiveItem2Character(pchar, "indian21");
		break;
   		case "Step_As_9":
			dialog.text = "I have such items. Five million and they're yours.";
			link.l1 = RandPhraseSimple("Five million?!!", "Five million... A good amount!");
			link.l1.go = "exit";
            if (sti(pchar.money) >= 5000000)
            {
    			link.l2 = "It looks like I have no other choice. We need to take it. Take the money and give me the items as soon as possible!";
    			link.l2.go = "Step_As_10";
            }
            else
            {
    			link.l2 = "I really need them, but I don't have enough money...";
    			link.l2.go = "exit";
            }
		break;
   		case "Step_As_10":
			dialog.text = GetFullName(pchar) + ", nice to do business with you. Get your priceless artifacts!";
			link.l1 = "Thank you, Oliver! You literally saved my life...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000000);
    		GiveItem2Character(pchar, "sculMa1");
    		GiveItem2Character(pchar, "sculMa2");
    		GiveItem2Character(pchar, "sculMa3");
    		GiveItem2Character(pchar, "indian22");
    		pchar.questTemp.Azzy.Oliver = 1;
		break;

		case "PL_Q8_over":
			dialog.text = "Greetings to captain " + GetFullName(pchar) + ".";
			link.l1 = "Listen, Oliver, I need Morgan!";
			link.l1.go = "PL_Q8_over_1";
		break;
		case "PL_Q8_over_1":
			dialog.text = "But he's not here, he went to Panama without you. And you were told to tell them that you can sunbathe on the beaches.";
			link.l1 = "What?!";
			link.l1.go = "PL_Q8_over_2";
		break;
		case "PL_Q8_over_2":
			dialog.text = "Togo! I'm translating it especially for you. You didn't make the deadline, and now you are not needed. I'm sorry...";
			link.l1 = "The Devil!!! Come on, it's your own fault...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
	}
}


