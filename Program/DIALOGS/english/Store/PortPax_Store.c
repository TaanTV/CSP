// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Ask, what do you want?",
                          "We have just raised this issue. You probably forgot...", "Today is the third time you have talked about some issue...",
                          "Listen, this is a store, people are buying something here. Don't distract me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + npchar.name + ", some other time.", "Exactly, "+ GetSexPhrase("forgot", "forgot") +"something...",
                      "Yeah, really for the third time...", "Um, I won't...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            if (CheckAttribute(pchar, "questTemp.Azzy.GiveRum"))
            {
        		Link.l1 = "Listen, buddy, someone named Azzi sent me to you.";
        	    Link.l1.go = "Step_Az6";
                if (pchar.questTemp.Azzy.GiveRum == "OK")
                {
            		Link.l1 = "I want to pick up the rum I'm supposed to have.";
            	    Link.l1.go = "Step_Az8";
                }
            }
            if (pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
    			Link.l2 = "Listen, I need to find Azzie urgently!";
    			Link.l2.go = "Step_Az10";
            }
		break;
		//============================== Квест Аззи ===============================
 		case "Step_Az6":
        	dialog.text = "Oh, did Sir Azzie send you to me?! I am very glad to hear about him - such a pleasant and businesslike man! And what did he tell you?";
    		link.l1 = "Human?! Hmm, well, okay... He told me that I can borrow rum from you for free and as much as I want.";
    		link.l1.go = "Step_Az7";
		break;

 		case "Step_Az7":
        	dialog.text = "Well, not exactly. You can take 300 of my rum once a day. And, of course, free.";
    		link.l1 = "Okay, that's fine with me. Shall we proceed with the procedure?";
    		link.l1.go = "Step_Az8";
    		pchar.questTemp.Azzy.GiveRum = "OK";
		break;

 		case "Step_Az8":
        	dialog.text = NPCStringReactionRepeat("I can give you 300 cents of rum.",
                       "You have already "+ GetSexPhrase("took", "took") +"you're supposed to have rum today.",
                       "I'm telling you that you have your rum for today "+ GetSexPhrase("chose", "chose") +". Come back tomorrow.",
                       "Tomorrow, come tomorrow...", "block", 1, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("Okay, I'll take it all!!!", "That's right, "+ GetSexPhrase("took it", "took it") +"...", "I'm sorry...", "Well, see you tomorrow then.", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_Az9", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;

 		case "Step_Az9":
        	dialog.text = "Kindly load into the holds. Rum has been issued to you.";
    		link.l1 = "That's good. Thanks, buddy.";
    		link.l1.go = "exit";
            AddCharacterGoods(Pchar, GOOD_RUM, 300);
		break;

 		case "Step_Az10":
        	dialog.text = NPCStringReactionRepeat("I do not know where Azzi is. I have no idea just.",
                                    "I've already told you, I don't know where he is.",
                                    "I repeat, I don't know where Azzie is.",
                                    "I say again that I don't know where Azzie is. And I don't want to know.", "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("But you get the rum from him that I take from you.", "Yes, I remember saying it", "Don't repeat it, I remember.", "Sorry, very sorry...", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_Az11", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;

 		case "Step_Az11":
        	dialog.text = "I do not know how your rum is delivered to me at all. I just leave the barn in the backyard open at night, and in the morning the rum is already there. I keep the third part for myself, two thirds goes to you. This is the essence of this commercial transaction.";
    		link.l1 = "Damn it... So you need to ambush those who deliver rum to you at night!";
    		link.l1.go = "Step_Az12";
		break;

 		case "Step_Az12":
        	dialog.text = "But I wouldn't do that. My assistant was already curious, hid in the barn during the day, wanted to peek. Only in the morning they found him next to the rum touched, now he sits all day, drooling and mumbling\n"+
                          "I do not know who this Azzi is, but I have not been satisfied with free rum for a long time. I'm scared for myself, you know\n"+
                          "And you won't see anything at all. I've already locked the barn, I think I'll do without rum. And the rum is back in place in the morning. That's it, "+ GetSexPhrase("buddy", "girlfriend") +".";
    		link.l1 = "Yes, it's clear that I won't find Azzi here.";
    		link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

