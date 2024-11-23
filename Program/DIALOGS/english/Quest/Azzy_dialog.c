
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			Dialog.CurrentNode = "AngryQuest";
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
        	dialog.text = "Good afternoon, " + GetFullName(pchar) + ". Fresh wind, sea... I like. Isn't that the kind of dress they're wearing now?";
    		link.l1 = "Yes, the dress is just right... I just was at shipyard in " + XI_ConvertString("Colony"+pchar.questTemp.Ascold.ShipyarderColony+"Gen") + "!!! How did I get here?! What the hell is going on?!!";
    		link.l1.go = "Step_1";
		break;

		case "Step_1":
        	dialog.text = "Don't worry so much\n"+
                          "First of all, I am not a banal devil, but a demon! I took you on loan, we'll talk now and I'll put you back in place\n"+
                          "And secondly, thank you for opening the lamp.";
    		link.l1 = "What?! Again?!!!";
    		link.l1.go = "Step_2";
		break;

		case "Step_2":
        	dialog.text = "Are you talking about Leif Erickson? Don't worry, I won't force you to find items for yourself and storm cities\n"+
                          "I spent a lot of time in this lamp, I have a lot of other things to do right now.";
       		link.l1 = "What about body swapping? Aren't you going to do that either?";
    		link.l1.go = "Step_3";
		break;

		case "Step_3":
        	dialog.text = "No, I won't. It's forbidden by circular 15315/28. And why?";
    		link.l1 = "Ugh, that's good... listen, is Leif more powerful than you, demon?";
    		link.l1.go = "Step_4";
		break;

		case "Step_4":
        	dialog.text = "Why did you decide like that? Ah, because he switched bodies twice?"+
                          "I am a demon, and not the last in our structure. I can give you anything, including any body. However, Circular 15315/28 of the Department of Audit and Control of Hell does not allow the exchange of bodies without the consent of death and the relevant documents\n"+
                          "And Leif is a small-time crook, picked up Indian occult rituals and managed to summon me. And the saddest thing is that he managed to deceive me, although it was all my fault...";
    		link.l1 = "How is it? I'm sorry for the question, of course, but it's very interesting.";
    		link.l1.go = "Step_5";
		break;

		case "Step_5":
        	dialog.text = "Yes, no problem. I feel a certain sense of gratitude to you, because you opened this tin instead of giving it to the church\n"+
                          "So, this bastard Leif, in his old age, began to think about how he could gain immortality, and all roads on the way to this goal lead to Hell\n"+
                          "Leif, who by that time had traveled half of the continent now called America and visited many local tribes, had learned quite a lot of powerful spells. That is, he became a good sorcerer, in the European sense of the word. By the way, he learned the trick of transmigrating souls between two bodies from the Aztecs\n"+
                          "In Europe, he was also engaged in obscurantism (he was lucky and had a nickname - Happy), so he knew that if there was a demon nearby at the moment of death, then the soul does not leave the body for the Last Judgment\n"+
                          "And Leif found an effective demon summoning ritual among the Toltecs. He set the ritual in motion and, unfortunately, it was me he summoned.";
    		link.l1 = "So how did he manage to deceive you, because demons know everything!";
    		link.l1.go = "Step_6";
		break;

		case "Step_6":
        	dialog.text = "They know, that's right. But, you see, we use this procedure to summon us to receive the soul and body of a mortal directly to Hell, bypassing the office of the Last Judgment\n"+
                          "There are enough mortal idiots, they try to enclose us in a specially prepared bottle in order for us to fulfill their desires. Under the oath not to close the bottle as a pledge of our own soul, we calmly fit inside, and after a moment the bottle always turns out to be closed\n"+
                          "Mortals think it's all in the bag, but each of us has a diamond ring on our finger, especially for such cases. Using it as a glass cutter, we free ourselves and take the soul and body into the bargain.";
    		link.l1 = "And Leif didn't use a bottle, but a tin can...";
    		link.l1.go = "Step_7";
		break;

		case "Step_7":
        	dialog.text = "Exactly. Eastern demons, djinn slaves, are placed in such cans. Leif used the genie lamp to imprison me\n"+
                          "And it must happen that he performed the summoning procedure the day after Walpurgisnacht, my favorite holiday on Earth\n"+
                          "As always, I spent this holiday extremely fun. I like, you know, to take pictures of earthly girls, and Gothic witches are so hot\n"+
                          "In general, with a hangover, I didn't even see where I was going. That's how I got caught. And after my imprisonment, Leif sent a letter to his relatives, where he described the ritual of his resurrection. The Frenchman de la Fontaine found this letter, and you brought ritual into action.";
    		link.l1 = "Listen, couldn't your fellow demons free you?";
    		link.l1.go = "Step_8";
		break;

		case "Step_8":
        	dialog.text = "No, I was not on duty at that time, I took indefinite leave. And those who hang around the Earth in search of entertainment on their own, the office of Hell does not really like. So I'm in trouble, don't mess around.";
    		link.l1 = "Yeah, I don't even know what to say...";
    		link.l1.go = "Step_9";
		break;

		case "Step_9":
        	dialog.text = "And what can I say, the swashbuckling demon Azzi is like the last earthly sucker.";
    		link.l1 = "Oh, is that your name Azzie?! It's very nice to meet you.";
    		link.l1.go = "Step_10";
		break;

		case "Step_10":
        	dialog.text = "Me too. Considering that the result of the acquaintance was my release, I am doubly pleased\n"+
                          "However, now you know my name and can perform the ritual of my summoning. I hope you won't bother me about anything for no reason\n"+
                          "I really don't like it, you know. So you will get into a bad mood, and my good attitude towards you will disappear in a moment. And when I'm angry, I'm scary...";
    		link.l1 = "I don't even know the rituals. I am the most perfect in this business. It's for me to run to the Toltecs, or something, from whom Leif got the rite...";
    		link.l1.go = "Step_11";
		break;

		case "Step_11":
        	dialog.text = "See for yourself, I definitely won't help you in this matter. Whatever you need, or rather, whatever you want to take, I'll give you now.";
    		link.l1 = "Hmm... Gifts from evil spirits? Frankly, I don't wish myself any harm.";
    		link.l1.go = "Step_12";
		break;

		case "Step_12":
        	dialog.text = "Good, evil... Two sides of the same coin\n"+
                          "Zoroastrianism of the time of the Persian king Darius is the first religion in the history of mankind that came close to understanding the essence of things, but the prophet Zoroaster was very far from the truth\n"+
                          "Good and evil are often so intertwined that it is very difficult to distinguish them. And the essence of what is happening is always far from clear.";
    		link.l1 = "How is it?";
    		link.l1.go = "Step_13";
		break;

		case "Step_13":
        	dialog.text = "It's hard to explain exactly in human terms, but let's look at an example\n"+
                          "Suppose you cured a person from a serious illness is a kind act. But your good deed is an evil deed towards his unfortunate stepdaughter\n"+
                          "Or suppose that you have maimed a preson - it is evil. But this evil deed will be a boon for the same stepdaughter suffering from her tyrant stepfather.";
    		link.l1 = "Hmm, that's how it is...";
    		link.l1.go = "Step_14";
		break;

		case "Step_14":
        	dialog.text = "As a result, the forces of evil and good in their confrontation commit acts that are difficult to qualify unambiguously\n"+
                          "Thus, it is absolutely not necessary that I start sowing evil towards you right now. Nothing obliges me to do this, even though I am a demon.";
    		link.l1 = "So I can make wishes and you will fulfill them?";
    		link.l1.go = "Step_15";
		break;

		case "Step_15":
        	dialog.text = "Basically, yes. However, there is one very big BUT\n"+
                          "It lies in the fact that our relations with mortals are regulated by circulars. I've already given you an example - the exchange of bodies\n"+
                          "I can only act within these rules. So let's discuss your wishes.";
        	link.l1 = "With pleasure.";
    		link.l1.go = "Wishes";
		break;

		case "Wishes":
            dialog.text = LinkRandPhrase("I'm listening to you carefully. What do you want?", "So what do you want?" , "I'm listening to you. What do you want?");
    		link.l1 = "So that you kill my enemies.";
    		link.l1.go = "ToKillEnemy";
    		link.l2 = "Money.";
    		link.l2.go = "ToGiveMoney";
    		link.l4 = "Rum.";
    		link.l4.go = "ToGiveRum";
    		link.l5 = "Good ship.";
    		link.l5.go = "ToShip";
    		link.l6 = "Immortality.";
    		link.l6.go = "ToImmortal";
    		link.l7 = "Become Governor General of Jamaica.";
    		link.l7.go = "ToGovernor";
    		link.l8 = "Become "+ GetSexPhrase("the strongest, dexterous, smart, lucky","the strongest, dexterous, smart, lucky") +"...";
    		link.l8.go = "ToAddSpecial";
    		link.l9 = "That's it, I don't want anything more. Anyway, nothing comes to mind.";
    		link.l9.go = "ToEnd";
		break;

		case "ToKillEnemy":
			dialog.text = NPCStringReactionRepeat("Killing people at your will? A completely wrong approach to understanding the forces of Evil.",
                                           "We have already discussed this wish of yours.",
                                           "I said that we have already discussed this desire. Don't piss me off, I might lose my patience.",
                                           "So, it looks like you're a completely deranged person. So, goodbye to death.", "quest", 0, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("I didn't really understand... And what does understanding have to do with it?", "Yes, that's right, that's it. Let's discuss the rest.", "Sorry, I didn't mean to piss you off. Let's continue.", "How's goodbye?!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_16", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_16":
        	dialog.text = "Yes, despite the fact, " + GetFullName(pchar) + " that the forces of evil, with the rarest exceptions, do not kill people. Those horror stories that nannies and grandmothers tell you since childhood are nothing more than fairy tales.";
    		link.l1 = "But you're after our souls!";
    		link.l1.go = "Step_17";
		break;

    	case "Step_17":
        	dialog.text = "That's right, just like the forces of good are hunting for these same souls\n"+
                          "Killing a person does not mean at all that his soul will go to Hell - this is decided by the board of the Last Judgment. The task of the dark forces is to provide a solution in our favor\n"+
                          "And this is achieved not by killing a person, but by indulging his vices. His own actions should give us his soul. The passions in the soul of a mortal should flare up from a smoldering ember into an all-consuming flame, and everyone has such an ember in their soul...";
    		link.l1 = "Hmm, go into any cave in the archipelago, so it's full of your brother. If you gape a little, they'll blow your head off, not particularly indulging my vices...";
    		link.l1.go = "Step_18";
		break;

		case "Step_18":
        	dialog.text = "Oh, that... These insane crowds have very little to do with the forces of evil. The souls of some deceased people do not get into the office of the Senior Court, there are a number of reasons for this\n"+
                          "We have Indian demons, they are brought out in a separate department, the Aztec god Mictlantehutl runs there. It is this gang that forces a soul that has already lost consciousness after death to control a dead body, and not necessarily its own\n"+
                          "It's a costly and troublesome task to make a dead body move, but as far as I know, they found a way to tie elemental elements derived from pure natural energy to this case. So these walking corpses are essentially autonomous\n"+
						  "I have no idea why the Redskins need this. They keep to themselves, their department provides reports only to senior management. They are strange\n"+
                          "Furthermore, the killing of persons without justification is prohibited by circular 55115/13.";
    		link.l1 = "So you won't be able to kill anyone at my will?";
    		link.l1.go = "Step_19";
		break;

		case "Step_19":
        	dialog.text = "Why, I can. I'll put the whole nearest city under the knife, if you only wish. There is only one condition - I will take your immortal soul for this service\n"+
                          "But first I will tear and devour your body - I am a demon, and the Control and Audit Department of Hell strictly monitors the performance of their official duties by demons\n"+
						  "But if you are so bloodthirsty, I can give you this cursed sword, it will help you kill your enemies\n"+
                          "Agree?";
			log_info("You got Iris's sword.");
			TakeNItems(pchar,"blade013",1);			  
    		link.l1 = "Okay, give me your sword. I'm not going to sell my soul at all. Let's talk about other wishes.";
    		link.l1.go = "Wishes";
		break;

		case "ToGiveMoney":
        	dialog.text = NPCStringReactionRepeat("It's possible.", "We have already discussed this desire.", "I repeat, we have already discussed this desire, you should not bother me.", "It seems that you are the most boring and boring person in this world. Goodbye.", "quest", 0, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("And what, will you demand my soul in return?", "That's right, we discussed it. Let's talk about other desires.", "Sorry, I didn't mean to piss you off. Let's continue.", "How's goodbye?!", npchar, Dialog.CurrentNode);
            link.l1.go = DialogGoNodeRepeat("Step_20", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_20":
        	dialog.text = "Actually, that's what demons do: money, jewelry, gold - and then the soul goes straight to hell. But I am a demon, I do not intend to humiliate myself with a petty scam\n"+
                          "Besides, you provided a favor, I don't want to hurt you.";
    		link.l1 = "Ugh-f-f, it pleases...";
    		link.l1.go = "Step_21";
		break;

		case "Step_21":
        	dialog.text = "I will provide you with money. But I won't give them to you\n"+
                          "In Charlestown, you approach a usurer, his name is " + GetFullName(characterFromId("Charles_usurer")) + ". Tell him that he owes you three million and you will immediately receive the entire amount.";
    		link.l1 = "Hmm, has he already sold you his soul?";
    		link.l1.go = "Step_22";
    		pchar.questTemp.Azzy.GiveMoney = 1;
		break;

		case "Step_22":
        	dialog.text = "Ha ha ha! Every person who lends money at interest has already sold his soul to us\n"+
                          "Some people just don't realize it. Until then..\n"+
                          "Well, let's not get distracted. Are you happy? Or does your soul still require fulfillment of desires? Ha ha!";
    		link.l1 = "Uv-f-f, I would like to look at the price list again.";
    		link.l1.go = "Wishes";
		break;

		case "ToGovernor":
        	dialog.text = NPCStringReactionRepeat("Very good. From now on, you are the governor of Jamaica. No problem.",
                                                  "You have already become governor.",
                                                  "I've already made you governor of Jamaica. Do it again?",
                                                  "It looks like you're the stupidest person on Earth. Goodbye.", "quest", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("So I can go to my residence in Port Royal? And the English fleet in the Caribbean will be subordinate to me? And will I be able to communicate with the king?", "Yes, that's right. I want to become a governor of Jamaica...", "I don't even know if it's worth it?", "How's goodbye?!", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_25", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_25":
        	dialog.text = "Well, how should I tell you... This is more difficult.";
    		link.l1 = "What are the difficulties? You made me governor of Jamaica!";
    		link.l1.go = "Step_26";
		break;

		case "Step_26":
        	dialog.text = "That's right. However, I only made you governor, I had no effect on the world around me.";
    		link.l1 = "So, the people around me won't perceive me as a governor? Then why do I need all this?";
    		link.l1.go = "Step_27";
		break;

		case "Step_27":
        	dialog.text = "How do I know why you need this? You wanted to be a governor, I made you one\n"+
                          "However, in order for the outside world to perceive you as a governor, I will have to change the course of events in the past\n"+
                          "I will have to simulate the whole chain of events that led you to the governor's chair. Accordingly, the events of the surrounding world and the people around them will also be changed. What this will lead to in the end, even I cannot say for sure\n"+
                          "That is to say, it may well happen that the world will change beyond recognition. And I will need to dispose of the existing reality in accordance with departmental circular 315/188\n"+
                          "Are you ready for such a turnaround?";
    		link.l1 = "No, not ready! Everything is difficult for you...";
    		link.l1.go = "Step_28";
		break;

		case "Step_28":
        	dialog.text = "As an alternative, take this bracelet. Wear it on your hand and everyone will love you, see for yourself, you'll be governor, heh.";
			log_info("You got 'Slanderer'.");
			TakeNItems(pchar,"talisman17",1);
    		link.l1 = "At least something... Let's see what else you have to offer me.";
    		link.l1.go = "Wishes";
		break;

		case "ToImmortal":
        	dialog.text = dialog.text = NPCStringReactionRepeat("Do you want immortality? It's possible. Just let's clarify exactly what you mean by the word immortality. Do you want your soul not to leave your body for various reasons that usually cause death? Is that so?",
                                    "We've already talked about immortality.",
                                    "I repeat, we have already discussed the issue of immortality, you should not annoy me.",
                                    "It seems that you are the stupidest person in the sublunary world. Goodbye.", "quest", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("Well, in fact yes...", "Yes, exactly, the question is closed with immortality.", "We discussed and decided everything, you are absolutely right!", "How is goodbye?!", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_29", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_29":
        	dialog.text = "It can be arranged. Only you owe to understand that the wounds inflicted on you in battles will lead to the decomposition of your body\n"+
                          "Soon you will become one of those creatures that infest the catacombs here-a living corpse, similar to my friend Leif. Are we talking about this?";
    		link.l1 = "No, not about that. To be precise, I want the enemy's blades and bullets to not harm my body.";
    		link.l1.go = "Step_30";
		break;

		case "Step_30":
        	dialog.text = "Now it's clear. Only it's not immortality, it's invulnerability. You can arrange it\n"+
                          "Only here there is a problem - heavy labor costs in terms of implementation. It's one thing to bind the soul to the body forever, it's a trifle. And another thing is to keep the body intact under a hail of bullets, it requires serious energy expenditure.";
    		link.l1 = "What?! Azzie, you're a demon, a supernatural being. You can do anything, but you're telling me about some labor costs...";
    		link.l1.go = "Step_31";
		break;

		case "Step_31":
        	dialog.text = "What did you want? We all live by the laws of the universe, it's just that you don't know these laws\n"+
                          "In general, like this: if you want invulnerability, I'll say that you should to make some work.";
    		link.l1 = "I want to. Tell me what I owe to do.";
    		link.l1.go = "Step_32";
		break;

		case "Step_32":
        	dialog.text = "So, you are signing a contract with the Department of Human Accounting of Hell. Based on this contract, you owe to provide this hellish Department with the necessary amount of vital energy, which the Chinese call qi\n"+
                          "Pure natural energy, which feeds all these evil spirits in caves and catacombs, is also suitable.";
    		link.l1 = "How to ensure this? What exactly should I do to get this energy?";
    		link.l1.go = "Step_33";
		break;

		case "Step_33":
        	dialog.text = "You owe do what you already do every day - send people and evil spirits to the next world\n"+
                          "And the Hell Department automatically credits the released energy to your balance, which goes to ensure your invulnerability.";
    		link.l1 = "Is there no way without it? I do send a lot of people to the next world every day, but I do it of my own free will...";
    		link.l1.go = "Step_34";
		break;

		case "Step_34":
        	dialog.text = "Listen, "+ GetSexPhrase("mon cher","dear") +", I'm doing you a huge favor. Do you think such contracts with the Department of Hell for the registration of people are lying on the road?"+
                          "Such contracts are rare and exclusive. There is no other way, there are no miracles in the world.";
    		link.l1 = "How many people or evil spirits do I owe to kill for the normal functioning of my invulnerability system?";
    		link.l1.go = "Step_35";
		break;

		case "Step_35":
        	dialog.text = "This is the Department as the general contractor defines. But there are no special problems there - a few units a day and that's it\n"+
                          "I'm telling you, you do it every day. I don't see any problems..\n"+
                          "So, do you agree?";
    		link.l1 = "Yes, agree. Should I sign in blood?";
    		link.l1.go = "Step_36";
    		link.l2 = "No, do not agree. Let everything remain as it is. Let's see what else you have in terms of fulfilling my wishes.";
    		link.l2.go = "Wishes";
		break;

		case "Step_36":
        	dialog.text = "In blood?! Heh, where did you read these cheap mystery novels?"+
                          "Just say, 'I, " + GetFullName(pchar) + ", being in my right mind, make a contract with the demon Azzi to ensure the invulnerability of my body.'";
    		link.l1 = "I, " + GetFullName(pchar) + ", being in my right mind, I enter into a contract with the demon Azzi to ensure the invulnerability of my body.";
    		link.l1.go = "Step_37";
		break;

		case "Step_37":
        	dialog.text = "Well, that's it. The text of the contract has been entered in the ship's log for you, read it at your leisure\n"+
                          "Congratulations to you. You are now completely invulnerable.";
    		link.l1 = "That's great! Listen, I want to see what else you can offer me in terms of wish fulfillment.";
    		link.l1.go = "Wishes";
    		LAi_SetImmortal(pchar, true);
            SetQuestHeader("ContractWithHell");
            AddQuestRecord("ContractWithHell", "1");
			AddQuestUserData("ContractWithHell", "Conrtragent", GetFullName(pchar));
            pchar.questTemp.Azzy.Immortal = 1;
            SaveCurrentQuestDateParam("questTemp.Azzy");
            SaveCurrentQuestDateParam("questTemp.Azzy.Immortal");
            pchar.questTemp.Azzy.Immortal.AllQuota = 0;
            pchar.questTemp.Azzy.Immortal.DayQuota = 3; //ежедневный норматив
            pchar.questTemp.Azzy.Immortal.CurBalance = 0;
            pchar.questTemp.Azzy.Immortal.CurKilled = 0;
            pchar.questTemp.Azzy.Immortal.Penalty = 0;
            pchar.questTemp.Azzy.Immortal.EarlyKilled = Statistic_AddValue(PChar, "Solder_s", 0) +
                                                 Statistic_AddValue(PChar, "Solder_g", 0) +
                                                 Statistic_AddValue(PChar, "Warrior_s", 0) +
                                    	         Statistic_AddValue(PChar, "Warrior_g", 0) +
                                    	         Statistic_AddValue(PChar, "Citizen_s", 0) +
                                    	         Statistic_AddValue(PChar, "Citizen_g", 0) +
                                    	         Statistic_AddValue(PChar, "Monster_s", 0) +
                                    	         Statistic_AddValue(PChar, "Monster_g", 0);
            AddQuestRecord("Azzy_HellSign", "1");
			AddQuestUserData("Azzy_HellSign", "sName", GetMainCharacterNameGen());
			AddQuestUserData("Azzy_HellSign", "DayQuota", pchar.questTemp.Azzy.Immortal.DayQuota);
			AddQuestUserData("Azzy_HellSign", "AllQuota", pchar.questTemp.Azzy.Immortal.AllQuota);
			AddQuestUserData("Azzy_HellSign", "CurKilled", pchar.questTemp.Azzy.Immortal.CurKilled);
			AddQuestUserData("Azzy_HellSign", "CurBalance", pchar.questTemp.Azzy.Immortal.CurBalance);
		break;

		case "ToGiveRum":
        	dialog.text = NPCStringReactionRepeat("You have plenty of money. Can't you provide yourself with rum?",
                                    "About the rum again? The issue has been resolved...",
                                    "Don't piss me off, I don't want to repeat myself.",
                                    "It seems that you are the stupidest person in the sublunary world. Goodbye.", "quest", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("I can and do. But you know, today there is money, tomorrow it may not be. And I always want rum!", "That's right, we've decided everything!", "Sorry...", "How's goodbye?!", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_38", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_38":
        	dialog.text = "Well, it can be arranged. Let's agree this way: if you need rum, then you can get it for free at the Port-au-Prince store from a seller named " + GetFullName(characterFromId("PortPax_trader")) + ".";
    		link.l1 = "Okay, that would be great! Free rum is a pirate's dream! And I won't owe you anything for that?";
    		link.l1.go = "Step_39";
    		pchar.questTemp.Azzy.GiveRum = 1;
		break;

		case "Step_39":
        	dialog.text = "Nothing. I do this at the expense of my own resources, I do not involve anyone else.";
    		link.l1 = "That's good. Well, let's see, what else do you have interesting in terms of wish fulfillment?";
    		link.l1.go = "Wishes";
		break;

		case "ToAddSpecial":
        	dialog.text = NPCStringReactionRepeat("This can be arranged. So, what exactly dou you want?",
                                    "I sent you to a certain person, I don't see the point in repeating myself.",
                                    "Don't piss me off, I don't want to repeat myself.",
                                    "It seems that you are the stupidest person in the sublunary world. Goodbye.", "quest", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("Well, I don't know... Strength would not hurt, luck...", "Yes, that's right, I'll find the way to it...", "Sorry...", "How's goodbye?!", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_40", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_40":
        	dialog.text = "Clear. In general, there is a brothel on Tortuga, a certain Margarita keeps it. This woman is a witch, she can do what you need. In the time that you get to her, I'll make arrangements with her.";
    		link.l1 = "Okay, I'll go see her, thank you. And what else can you wish for?";
    		link.l1.go = "Wishes";
    		pchar.questTemp.Azzy.AddSpecial = 1;
		break;

		case "ToShip":
        	dialog.text = NPCStringReactionRepeat("What does good mean?",
                                    "We've already talked about ships...",
                                    "I understand your dream of the Flying Dutchman, but we've already discussed everything.",
                                    "It seems that you are the stupidest person in the sublunary world. Goodbye.", "quest", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("So that it surpasses any existing one in speed, so that the sails do not tear from the wind and knippels, so that the cores fly off the sides without causing harm...", "Yes, ships are my favorite topic...", "I was talking about the Black Pearl, but nevertheless everything is true.", "How is goodbye?! But what about the ships?", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_41", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_41":
        	dialog.text = "I won't do this - it's very expensive.";
    		link.l1 = "And the 'Flying Dutchman'?";
    		link.l1.go = "Step_42";
		break;

		case "Step_42":
        	dialog.text = "'Flying Dutchman' is under a serious curse. A bunch of Indian demons are only engaged in tracking the state of this curse and maintaining its functionality\n"+
                          "Or are you going to ask me to join your team to ensure the safety of your vessel and keep it running well?!";
    		link.l1 = "No, of course, I didn't even think about it, dear Azzi...";
    		link.l1.go = "Step_43";
		break;

		case "Step_43":
        	dialog.text = "And that's right, because it's not safe for you\n"+
                          "Although wait, I don't remember exactly, but the protection of the ship's hull is carried out as part of one of the contracts with mortals\n"+
                          "In general, I advise you to visit the shipyard in Bermudes, the Master runs it, he brings local sailboats to mind.";
    		link.l1 = "Dear Azzi, thanks for the advice, I will definitely use it. Now, can I hear anything else about wish fulfillment?";
    		link.l1.go = "Wishes";
            if (CheckAttribute(pchar, "questTemp.Azzy.Immortal"))
		    {
            	dialog.text = "Wait, we signed a contract for your invulnerability. So, this contract also prescribes the safety of your ship's hull so that you do not drown it inadvertently in the middle of the ocean. Otherwise, arrange later with the mermaids to get you out of the abyss...";
        		link.l1 = "Azzi, that's just great! Is there anything else I can hear about wish fulfillment?";
		    }
		break;

		case "ToEnd":
        	dialog.text = "You've really tired me out, but I've tested my patience. And now don't let the angels say that demons are wild and unbridled creatures\n"+
                          "It was nice talking to you. If you ever dare to summon me, I promise that I will listen to you at least, and not devour your body immediately. Ha ha ha\n"+
                          "Goodbye, "+ GetSexPhrase("caper","" + pchar.name + "") +".";
    		link.l1 = "Goodbye, Azzi. Thank you.";
    		link.l1.go = "Back_Exit";
		break;

 		case "Back_Exit":
            LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], false);
 		    ChangeCharacterAddress(characterFromID("Azzy"), "None", "");
 		    DoReloadCharacterToLocation(pchar.questTemp.Ascold.ShipyarderColony + "_Shipyard", "reload", "reload2");
 		    LAi_SetPlayerType(PChar);
 		    NextDiag.TempNode = "Second time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

 		case "Azzy_Exit":
 		    ChangeCharacterAddress(characterFromID("Azzy"), "None", "");
 		    LAi_SetPlayerType(PChar);
 		    NextDiag.TempNode = "Death";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

 		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Second time":
        	dialog.text = "So, I'm on calls again... " + GetFullName(pchar) + ", you know I can't stand it. Now you will have to try very hard to explain the reason.";
    		link.l1 = "Azzi, I want to break the invulnerability contract.";
    		link.l1.go = "Step_44";
		break;

		case "Step_44":
        	dialog.text = "Why all of a sudden? Such contracts are not scattered. Invulnerability, you know...";
    		link.l1 = "Azzi!!! Your office in hell is constantly raising the stakes in the game! I'm risking my life!!!";
    		link.l1.go = "Step_45";
		break;

		case "Step_45":
        	dialog.text = "And with my immortal soul. And what did you want? Messing with the forces of evil leads a mortal to Hell.";
    		link.l1 = "Azzi! I want to terminate the contract. There is a paragraph in the text providing for this issue. But we were supposed to meet, so I called you .";
    		link.l1.go = "Step_46";
		break;

		case "Step_46":
        	dialog.text = "Hmm, good. Say, 'With Azzi's consent, I will terminate the contract for my invulnerability.' And that's all there is to it.";
    		link.l1 = "With Azzi's consent, I terminate the contract for my invulnerability!!!";
    		link.l1.go = "Step_47";
		break;

		case "Step_47":
        	dialog.text = "Hmm, what a feeling it is said! Well, it's okay - you're vulnerable again now. The contract is terminated.";
    		link.l1 = "Thank you, Azzi. You saved me more than my life...";
    		link.l1.go = "Step_48";
			pchar.questTemp.Azzy = "over";
    		LAi_SetImmortal(pchar, false);
    		DeleteAttribute(pchar, "questTemp.Azzy.Immortal");
    		DeleteQuestHeader("ContractWithHell");
    		DeleteQuestHeader("Azzy_HellSign");
		break;

		case "Step_48":
        	dialog.text = "That's right. Well, let's say goodbye, mortal. Forever now, because one more challenge from me will cost you your life\n"+
                          "Try to atone for your sins, maybe you will succeed. Goodbye...";
    		link.l1 = "Goodbye, Azzi. I'll try my best.";
    		link.l1.go = "Azzy_Exit";
			npchar.lifeDay = 0;
		break;
		//помощь ГГ, если вляпался с долгом у ростовщика ГПК
		case "ClimeUsurer":
			dialog.text = "Hehe... What, "+ GetSexPhrase("buddy, messed up","girlfriend, messed up") +"?";
			link.l1 = "Azzi, damn it, I'm so glad o see you!!!";
			link.l1.go = "ClimeUsurer_1";
		break;
		case "ClimeUsurer_1":
			dialog.text = "Don't swear, I don't like it, what do you think you're doing?";
			link.l1 = "I thought that's it, the end of me. Now, I don't think so anymore. Azzie, how glad to see you, my friend!..";
			link.l1.go = "ClimeUsurer_2";
		break;
		case "ClimeUsurer_2":
			dialog.text = "Yes, and I must admit, too. You amuse me, mortal. All you need is something, you're meddling somewhere out of your businessow you've contacted Indian demons. It just happened...";
			link.l1 = "Azzi, I couldn't even think that it will come to this! By the way, where am I, do you know?";
			link.l1.go = "ClimeUsurer_3";
		break;
		case "ClimeUsurer_3":
			dialog.text = "You're in Tenochtitlan, the abandoned Aztec capital. The demon that took you is called Mictlantecutli. He's pretending to be the king of the dead Aztecs here.";
			link.l1 = "Wow... Azzie, help me out, buddy!";
			link.l1.go = "ClimeUsurer_4";
		break;
		case "ClimeUsurer_4":
			dialog.text = "I don't even know... He closed you down on the case. What did you take the money for?";
			link.l1 = "Azzi, if I knew, then for no reason would I go for it! I swear to you...";
			link.l1.go = "ClimeUsurer_5";
		break;
		case "ClimeUsurer_5":
			dialog.text = "Come on, I believe that I'll get you out of here, but you look more carefully in the future. Do you understand me?";
			link.l1 = "I get it, I am not stupid.";
			link.l1.go = "ClimeUsurer_6";
		break;
		case "ClimeUsurer_6":
			dialog.text = "Okay, goodbye, mortal.";
			link.l1 = "Thank you, Azzi, from the bottom of my heart...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClimeUsurer_haveMoney");
		break;

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		//==> попытки дать денег
		case "AngryQuest":
            Dialog.text = GetFullName(pchar)+ ", there are far more interesting and pleasant things in this world than dealing with such a nerd.";
			Link.l1 = "Listen...";
		    Link.l1.go = "AngStep_1";
    	break;

		case "AngStep_1":
            Dialog.text = "I won't listen! Goodbye, mortal...";
			Link.l1 = "...";
		    Link.l1.go = "Back_Exit";
            DeleteAttribute(npchar, "angry.ok");
            Dialog.CurrentNode = "Back_Exit";
    	break;

		case "AngryExitAgain":
 		    ChangeCharacterAddress(characterFromID("Azzy"), "None", "");
 		    LAi_SetPlayerType(PChar);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}


