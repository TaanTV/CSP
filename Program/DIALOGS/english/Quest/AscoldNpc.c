
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = "Nothing to talk about.";
			link.l1 = "Okay...";
            link.l1.go = "exit";
//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
            if (pchar.questTemp.Ascold == "SeekInformatorHavanna" || pchar.questTemp.Ascold == "2SeekInformatorHavanna")
            {
            	dialog.text = "Good afternoon, who are you and what do you want?";
        		link.l1 = "My name is " + GetFullName(pchar) + ". I have arrived on behalf of Askold.";
        		link.l1.go = "Step_1";
            }
            if (pchar.questTemp.Ascold == "ReciveInformationManowar")
            {
				if (!CheckAttribute(pchar, "questTemp.Ascold.IKnowTheShip"))
				{
					dialog.text = "What you exaclty want?";
					link.l1 = "Listen to me, you said that you made inventory list. I will be very geneeuros if you will remember captain and ship...";
					link.l1.go = "Step_8";	
				}
				else
				{
            	dialog.text = "I'll probably refrain from contacting you, I don't like you, though"+ GetSexPhrase("friend", "acquaintance") +" Askold.";
        		link.l1 = "Whatever you want...";
        		link.l1.go = "exit";
				}
            }
        break;

//<<<<<<<<<<<<======== Разброс диалогов по персонажам ======================
 		case "Step_1":
        	dialog.text = "What kind of Askold?";
    		link.l1 = "An ordinary person who lives in Guadeloupe. There is no other in the Caribbean.";
    		link.l1.go = "Step_2";
		break;

 		case "Step_2":
        	dialog.text = "Speak softly, I understand you perfectly. What does my friend Askold need?";
    		link.l1 = "There is one problem. Some time ago, a man left Havana, loaded to the brim with objects of Indian worship.";
    		link.l1.go = "Step_3";
		break;

 		case "Step_3":
        	dialog.text = "Well, to the brim - that's a big word. There were objects of Indian worship, but not so much\n"+
                          "I was seconded to Havana and personally completed the inventory shipping list.";
    		link.l1 = "That's what Askold needs, this list.";
    		link.l1.go = "Step_4";
		break;

 		case "Step_4":
        	dialog.text = "If he knew he needed it, he would have made a copy. Well, now I can't even remember the half of it\n"+
                          "Now I don't even know how to help him.";
    		link.l1 = "I understand. The only thing I need to know is where Man went.";
    		link.l1.go = "Step_5";
		break;

 		case "Step_5":
        	dialog.text = "He went to Amatique Bay, south of Belize. I have to make a stop at Cayman Island on the way.";
    		link.l1 = "Wow! It's a strange place... And did he just leave alone?";
    		link.l1.go = "Step_6";
		break;

 		case "Step_6":
        	dialog.text = "Yes, he left alone. The fact is that Cayman is a gathering place and other ships from the Spanish colonies in America. You can imagine, in Amatica, they found an abandoned Indian temple further inland in Maine, and now there's a royal extermination there. And after the expedition is finished, the squadron must go to the Old World\n"+
                          "Yes, one left. The fact is that Cayman is a gathering place for other ships from the Spanish colonies in America. Imagine, an abandoned Indian temple was found in Amatika, further into the Main, and now a royal expedition is working there. And after the expedition finishes its work, the squadron must go to the Old World.";
    		link.l1 = "That's all I know.";
    		link.l1.go = "Step_7";
		break;

 		case "Step_7":
        	dialog.text = "That's enough, thanks, friend. I'll say hello to Askold for you."+ GetSexPhrase("Hey, ", "friend") +"girlfriend";
    		link.l1 = ", wait! And the money?";
    		link.l1.go = "exit";

			// Nathaniel (21.01.24): здесь делаю развилку на случай, если игрок захочет упростить себе задачу
			link.l2 = "Listen to me, you said that you made inventory list. I will be very geneeuros if you will remember captain and ship...";
			link.l2.go = "Step_8";

			npchar.LifeDay = 5;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
            AddQuestRecord("Ascold", "7");
            pchar.questTemp.Ascold = "ReciveInformationManowar";
            Pchar.quest.Ascold_AttackTenManowars.win_condition.l1 = "location";
            Pchar.quest.Ascold_AttackTenManowars.win_condition.l1.location = "Caiman";
            Pchar.quest.Ascold_AttackTenManowars.win_condition = "Ascold_AttackTenManowars";
		break;

        case "Step_8":
            dialog.text = "Hmm, I didn't expect it from you, " + GetAddress_Form(pchar) + " " + pchar.name + ". And how much you can offer?";
            link.l1 = "Let's say 250,000 piastres. I guess it's enough for information.";
            link.l1.go = "Step_9";
        break;

		case "Step_9":
			if (IsCharacterPerkOn(pchar, "Agent") || GetCharacterSkillNoBonus(pchar, SKILL_LEADERSHIP) > 70)
			{
				dialog.text = "Well, it's a deal.";
				link.l1 = "Here you go! Goodbye, " + GetAddress_FormToNPC(npchar) + ".";
				link.l1.go = "Step_10";
			}
			else
			{
				dialog.text = "What are you saying?! Go to hell!!!";
				link.l1 = "Don't be so exited, " + GetAddress_FormToNPC(npchar) + "... Goodbye...";
				link.l1.go = "exit";
			}
		break;

		case "Step_10":
			if (sti(pchar.money) < 250000)
			{
				dialog.text = "Are you kiddong me?! Where is promised 250,000 piastres? Oh, you have some troubles...";
				link.l1 = "Argh... I forgot to ask treasurer. Wait for me!";
				link.l1.go = "exit";
				NextDiag.TempNode = "IHaveNoMoney";
			}
			else
			{
				dialog.text = "Thank you a lot, " + GetAddress_Form(pchar) + " " + pchar.name + ". But I can only describe this ship... Good luck to you, my friend...";
				link.l1 = "...";
				link.l1.go = "exit";
				AddMoneyToCharacter(pchar, -250000);
				
				// Nathaniel (21.01.24): признак того, что знаем корабль (пока не знаю, вдруг понадобится)
				pchar.questTemp.Ascold.IKnowTheShip = true;
				
				// Nathaniel (21.01.24): дополнительная запись в судовом журнале
				AddQuestRecord("Ascold", "7_1");
			}
		break;

		case "IHaveNoMoney":
			dialog.text = "Damn, " + GetAddress_FormToNPC(npchar) + ", where are you missing?!";
			link.l1 = "Take your money, " + GetAddress_FormToNPC(npchar) + ".";
			link.l1.go = "Step_10";
		break;

 		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
    }
}
