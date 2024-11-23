// диалоговый файл №1 на голландку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;

    switch (Dialog.CurrentNode)
    {
        case "First time":
            dialog.text = NPCStringReactionRepeat("What do you want, "+ GetSexPhrase("my son","my daughter") +"?",
                         "You again? Did you forget to say something?", ""+ GetSexPhrase("My son","My daughter") +", what's eating you, why are you coming to me for the umpteenth time today and not saying anything?",
                         "Listen, " + GetFullName(pchar) + ", if you have nothing to say, then you don't have to come here.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("It's nothing special, Padre...",
                                               "No, just like that...",
                                               "There's nothing to say, Padre...",
                                               "Okay, Padre...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
//>>>>>>>>>>>>========= Разброс диалогов =====================
			if (CheckAttribute(pchar, "questTemp.PDM_ONV_OhotaNaVedmu"))	//Квест "Witch Hunt"
			{
				dialog.text = "... this city is mired in sin! But soon we will free people from the dark snares of Satan with the fire and will of our Lord! Uh... what do you want, "+ GetSexPhrase("my son","my daughter") +"?";
				link.l1 = "Holy Father, I know there is a witch here named Maria, a former harbor prostitute. With her dark art, she has already killed two people - Captain Miguel Cuenda, and the good hidalgo Bartholomew, who died before he could repent. He was a servant of the Governor of Belize. I pray to God that the Holy Inquisition will punish her for her sinful deeds.";
				link.l1.go = "Inqizitor_2";
				break;
			}
			if (pchar.questTemp.MC == "toByeBye")	//Квест 'Зачарованный город'
			{
				dialog.text = "What do you want in the Holy Inquisition!";
				link.l1 = "Father, I have business with you. Don't deny to "+ GetSexPhrase("zealous Catholic","zealous Catholic") +" a minute of attention";
				link.l1.go = "MCIncq";
				pchar.questTemp.MC = "Incquisitio";
				break;
			}
			if (pchar.questTemp.State == "Inquisition_toDeSouza")//Квест №2, базар с гл.Инквизитором
			{
                dialog.text = "Welcome to the bosom of the church, "+ GetSexPhrase("my son","my daughter") +".";
    			link.l1 = "Padre, I am here on the orders of the Governor-General...";
    			link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.State == "Inquisition_toCuracao")
			{
                if (CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
                    dialog.text = "Glad to see you, " + GetFullName(pchar) + ". Are you ready to report on the assignment?";
        			link.l1 = "Padre, I visited all the people you mentioned.";
        			link.l1.go = "Step_S2_12";
        			link.l2 = "Perhaps not yet, monsignor. I'll work on it some more...";
        			link.l2.go = "exit";
                }
                else
                {
                    dialog.text = "You got a task, "+ GetSexPhrase("my son","my daughter") +". Get to work.";
        			link.l1 = "All right, monsignor...";
        			link.l1.go = "exit";
                }
            }
			if (pchar.questTemp.State == "Inquisition_afterFrancisco")
			{
                if (CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
                    dialog.text = "Glad to see you, " + GetFullName(pchar) + ". Are you ready to report on the assignment?";
        			link.l1 = "Monsignor, I visited all the people you mentioned.";
        			link.l1.go = "Step_S2_12";
        			link.l2 = "Perhaps not yet, monsignor. I'll work on it some more...";
        			link.l2.go = "exit";
                }
                else
                {
                    dialog.text = "What happened, "+ GetSexPhrase("my son","my daughter") +"? Do you need atonement for your sins?";
        			link.l1 = "No, monsignor. I returned not for that. Now a certain Francisco de San Agostinho came up to me and began to fill in with nightingale trills about the morality of your assignment. He knows where I'm going, why I'm going. Don't you find this strange?";
        			link.l1.go = "Step_S2_11";
                }
            }
			if (pchar.questTemp.State == "Inquisition_backAllGood" || pchar.questTemp.State == "Inquisition_backPartGood" || pchar.questTemp.State == "Inquisition_backBad")
			{
                dialog.text = ""+ GetSexPhrase("My son","My daughter") +", you can go back to Havana. I don't need you anymore...";
    			link.l1 = "All right, monsignor.";
    			link.l1.go = "exit";
            }
			if (pchar.questTemp.State == "TakeRockBras_RockTaken")
			{
                dialog.text = "I'm listening to you, "+ GetSexPhrase("my son","my daughter") +". Why did you send?";
    			link.l1 = "Monsignor, according to the order received from the Governor-General of Havana, Don Francisco Oregon y Gascon, I am handing over to the Holy Inquisition the famous Ladron Roca Brazilian, captured by me in the hot battle of Maracaibo.";
    			link.l1.go = "Step_S3_1";
            }

        break;

//<<<<<<<<<<<<===== Разброс диалогов  =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Задания Инквизиции. Квест №2 **********************************
 		case "Step_S2_1":
			dialog.text = "I know, "+ GetSexPhrase("my son","my daughter") +". I've been waiting for you. So, your mission.\n"+
                          "There are a few people living in the dark, and we can't help them see the light yet. These are the Florentine gentiles Joao Ilhajo, Josef Nunen de Fonquezao, and Jacob Lopez de Fonseca. We were able to find out that they were influenced by the heretical teachings of Jansen.\n"+
                          "We free the souls of the adherents of the Jansenist sect from unholy bonds by burning their bodies at the stake. But they don't appreciate it, they don't appreciate the salvation of their soul that we give them...";
			link.l1 = "Excuse me, monsignor, I have a question. If, of course, you allow me to ask it.";
			link.l1.go = "Step_S2_2";
		break;
 		case "Step_S2_2":
			dialog.text = "Ask, "+ GetSexPhrase("my son","my daughter") +".";
			link.l1 = "I have heard that Jansenists believe in Christ in the same way as Catholics. Why burn them if they are Christians too?";
			link.l1.go = "Step_S2_3";
		break;
 		case "Step_S2_3":
			dialog.text = "Jansenius has perverted the dogmas of the Church, we have disagreements on the issue of reconciling the existence of free human will and the need for divine grace, without which human salvation is impossible.";
			link.l1 = "Is it not possible to come to an agreement, that is, to resolve differences through negotiations?";
			link.l1.go = "Step_S2_4";
		break;
 		case "Step_S2_4":
			dialog.text = "This is impossible, "+ GetSexPhrase("my son","my daughter") +". Враги Церкви только и ждут того, чтобы увести заблудшие души от Пастыря своего. Никому не позволено трактовать постулаты христианской веры произвольно, а тем более подвергать их сомнению. Никому!\n"+
                          "Besides, the Jansenists have stained themselves with a crime that will never be forgiven. About twenty years ago, one of the first followers of this sect, Samuel Cohen, stole ancient church documents from our archives in Seville!";
			link.l1 = "Wow! I have always believed that the Holy Inquisition is impeccable. How could this happen?";
			link.l1.go = "Step_S2_5";
		break;
 		case "Step_S2_5":
			dialog.text = "With the help of the enemy of the human race, "+ GetSexPhrase("my son","my daughter") +"! We confront his machinations every minute, but sometimes he gets the better of one of our brothers. So it happened this time, our Seville archivist fell victim to the mortal sin of greed...";
			link.l1 = "Did he confess everything?";
			link.l1.go = "Step_S2_6";
		break;
 		case "Step_S2_6":
			dialog.text = "Confessed, repented and cleansed his soul, how else? We are glad that we were able to help him. I am sure that the Lord has accepted his soul...";
			link.l1 = "Amen... So what will my assignment be?";
			link.l1.go = "Step_S2_7";
		break;
 		case "Step_S2_7":
			dialog.text = "You need to visit the escaped merchants for a specific purpose.";
			link.l1 = "Do you know where they are now?";
			link.l1.go = "Step_S2_8";
		break;
 		case "Step_S2_8":
			dialog.text = "Of course "+ GetSexPhrase("my son","my daughter") +". At first they fled to the Netherlands, but there they did not fit in - the Calvinist heresy is very jealous of another heresy.\n"+
                          "They then moved to the New World, and have now established a sectarian community on the island of Curaçao. Your job is to get these nepotists, by the way, very rich people, to buy the Pope's forgiveness.\n"+
                          "The indulgence will cost 50 thousand each. And if they refuse, then for the greater Glory of God, I give permission for extreme measures.";
			link.l1 = "50 thousand each, and in case of disobedience, I can do anything with them. Did I understand correctly?";
			link.l1.go = "Step_S2_9";
		break;
 		case "Step_S2_9":
			dialog.text = "Yes, "+ GetSexPhrase("my son","my daughter") +", you got it right...";
			link.l1 = "But are 50 thousand able to atone for the sins of the Jansenists before the Lord?";
			link.l1.go = "Step_S2_10";
		break;
 		case "Step_S2_10":
			dialog.text = "No, of course not. But we have to start somewhere. We need to turn their eyes to the Lord, and that's what you're going to do. Is everything clear to you, are you ready to complete the mission?";
			link.l1 = "Yes, monsignor, I will start immediately!!";
			link.l1.go = "exit";
    		pchar.questTemp.State = "Inquisition_toCuracao";
            AddQuestRecord("Spa_Line_2_Inquisition", "2");
            Pchar.quest.Inquisition_MeetFrancisco.win_condition.l1 = "location";
            Pchar.quest.Inquisition_MeetFrancisco.win_condition.l1.location = "Santiago_town";
            Pchar.quest.Inquisition_MeetFrancisco.win_condition = "Inquisition_MeetFrancisco";
		break;
 		case "Step_S2_11":
			dialog.text = "Thanks for the warning, "+ GetSexPhrase("my son","my daughter") +". Excessive softness towards heretics only leads to an increase in the suffering of their souls. I'll take care of Francisco, he won't bother you anymore. Take this as a token of appreciation. I suppose you'll need it...";
			link.l1 = "Thank you, Holy Father.";
			link.l1.go = "exit";
			pchar.questTemp.State = "Inquisition_toCuracao";
            GiveItem2Character(pchar,"DeSouzaCross");
		break;
 		case "Step_S2_12":
			dialog.text = "And what are the results, "+ GetSexPhrase("my son","my daughter") +"?";
			link.l1 = "I was unable to get money from any of these people.";
			link.l1.go = "Step_S2_NotMoney";
            if (pchar.questTemp.State.Usurer == "Ok")
            {
    			link.l1 = "I managed to get the money only from Joseph Nunen de Fonquesao, a Curacao usurer.";
    			link.l1.go = "Step_S2_OnlyUsurer";
            }
            if (pchar.questTemp.State.Store == "Ok")
            {
    			link.l1 = "I managed to get the money only from Joao Ilhaio, the owner of the store in Curacao, and his partner Jacob Lopez de Fonseca.";
    			link.l1.go = "Step_S2_OnlyStore";
            }
            if (pchar.questTemp.State.Store == "Ok" && pchar.questTemp.State.Usurer == "Ok")
            {
    			link.l1 = "The rear is fully completed, Holy Father. I managed to get the money from all three of the Jansenists you mentioned.";
    			link.l1.go = "Step_S2_All";
            }
		break;
 		case "Step_S2_NotMoney":
			dialog.text = "Your words have saddened my soul... You couldn't complete the simplest task.";
			link.l1 = "Holy Father, I tried with all my might...";
			link.l1.go = "Step_S2_13";
		break;
 		case "Step_S2_13":
			dialog.text = "I understand that diligence is a great human virtue... Go to Havana, "+ GetSexPhrase("my son","my daughter") +", I don't need you anymore...";
			link.l1 = "All right, monsignor. Goodbye...";
			link.l1.go = "exit";
            pchar.questTemp.State = "Inquisition_backBad";
            AddQuestRecord("Spa_Line_2_Inquisition", "15");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
		break;
 		case "Step_S2_OnlyUsurer":
            if (sti(pchar.money) >= 50000)
            {
                dialog.text = "Well, a partially completed task is good, "+ GetSexPhrase("my son","my daughter") +"... But it could have been better.";
    			link.l1 = "Holy Father, I tried with all my might...";
    			link.l1.go = "Step_S2_14";
            }
            else
            {
                dialog.text = "Uh, the task is completed, but where are the 50 thousand? Go, "+ GetSexPhrase("my son","my daughter") +", and come with the money for the task report.";
    			link.l1 = "I'm sorry, monsignor, I forgot it on the ship. I'll be right there...";
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_OnlyUsurer";
            }
		break;
 		case "Step_S2_14":
			dialog.text = "All right, all right, well... So, let's do the math. According to the Papal Chancellery, the recovery of the debtor's money is equal to finding the treasure. The discoverer of the treasure is entitled to 20 to 30 percent of its value at the market price, depending on the value of the treasure.\n"+
                          "A church tithe is charged from the proceeds - 10 percent, which is why it is called a tithe, hehe. Your total reward is... compose... 9 thousand piastres. Get it, "+ GetSexPhrase("my son","my daughter") +", sign up and you can be free.";
			link.l1 = "Thank you, monsignor. Goodbye...";
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = "Wait, monsignor. I have something else for you...";
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backPartGood";
			AddMoneyToCharacter(pchar, -41000);
			AddQuestRecord("Spa_Line_2_Inquisition", "16");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_OnlyStore":
            if (sti(pchar.money) >= 100000)
            {
                dialog.text = "Well, a partially completed task is good, "+ GetSexPhrase("my son","my daughter") +"... But it could have been better.";
    			link.l1 = "Holy Father, I tried with all my might...";
    			link.l1.go = "Step_S2_15";
            }
            else
            {
                dialog.text = "Uh, the task is completed, but where are the 100 thousand? Go, "+ GetSexPhrase("my son","my daughter") +", and come with the money for the task report.";
    			link.l1 = "I'm sorry, monsignor, I forgot it on the ship. I'll be right there...";
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_OnlyStore";
            }
		break;
 		case "Step_S2_15":
			dialog.text = "All right, all right, well... So, let's do the math. According to the Papal Chancellery, the recovery of the debtor's money is equal to finding the treasure. The discoverer of the treasure is entitled to 20 to 30 percent of its value at the market price, depending on the value of the treasure.\n"+
                          "A church tithe is charged from the proceeds - 10 percent, which is why it is called a tithe, hehe. In total, your reward is... It is... 18 thousand piastres. Get it, "+ GetSexPhrase("my son","my daughter") +", sign up and you can be free.";
			link.l1 = "Thank you, monsignor. Goodbye...";
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = "Wait, Padre. I have something else for you...";
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backPartGood";
			AddMoneyToCharacter(pchar, -82000);
			AddQuestRecord("Spa_Line_2_Inquisition", "16");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_All":
            if (sti(pchar.money) >= 150000)
            {
                dialog.text = "Fine, "+ GetSexPhrase("my son","my daughter") +"! 150 thousand is a significant contribution to the cause of our Order. We are grateful to you...";
    			link.l1 = "Holy Father, I tried with all my might...";
    			link.l1.go = "Step_S2_16";
            }
            else
            {
                dialog.text = "Uh, the task is completed, but where are the 150 thousand? Go, "+ GetSexPhrase("my son","my daughter") +", and come with the money for the task report.";
    			link.l1 = "I'm sorry, monsignor, I forgot it on the ship. I'll be right there...";
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_All";
            }
		break;
 		case "Step_S2_16":
			dialog.text = "All right, all right, well... So, let's do the math. According to the Papal Chancellery, the recovery of the debtor's money is equal to finding the treasure. The discoverer of the treasure is entitled to 20 to 30 percent of its value at the market price, depending on the value of the treasure.\n"+
                          "A church tithe is charged from the proceeds - 10 percent, which is why it is called a tithe, hehe. In total, your reward is... compose... 27 thousand piastres. Get it, "+ GetSexPhrase("my son","my daughter") +", sign up and you can be free.";
			link.l1 = "Thank you, monsignor. Goodbye...";
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = "Wait, monsignor. I have something else for you...";
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backAllGood";
			AddMoneyToCharacter(pchar, -123000);
			AddQuestRecord("Spa_Line_2_Inquisition", "17");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_17":
			dialog.text = "And what is it, "+ GetSexPhrase("my son","my daughter") +"?";
			link.l1 = "Holy Father, I remember you told me about a certain Samuel Cohen, who stole ancient church documents from your archives in Seville...";
			link.l1.go = "Step_S2_18";
		break;
 		case "Step_S2_18":
			dialog.text = "It happened, so what?";
			link.l1 = "Did he steal a certain Gospel from one of the First Apostles, but not the most worthy, rather the opposite...";
			link.l1.go = "Step_S2_19";
		break;
 		case "Step_S2_19":
			dialog.text = "It is forbidden to even talk about it! But you go on, "+ GetSexPhrase("my son","my daughter") +", because I was very surprised by...";
			link.l1 = "So, monsignor, I found this book. Here she is.";
			link.l1.go = "Step_S2_20";
		break;
 		case "Step_S2_20":
			dialog.text = "Holy Virgin, Mother of God!!! About such luck we could not even dream! All we could think about was where this heretical pasquil would come from and what we would do about it.\n"+
                          "What a load off my mind!.. "+ GetSexPhrase("my son","my daughter") +", as a reward for such an act, I absolve you of all sins and three more in advance!";
			link.l1 = "I am sincerely glad that I could help you, Holy Father...";
			link.l1.go = "Step_S2_21";
			TakeItemFromCharacter(pchar, "Bible");
		break;
 		case "Step_S2_21":
			dialog.text = "That's not all, "+ GetSexPhrase("my son","my daughter") +". The Holy Inquisition, as a token of gratitude for your service, presents you with this magnificent protective armor encrusted with gold.\n"+
                          "However, the value of this cuirass is not in the inlay. Its true value lies in the greatest reliability, which is what you need most of all, I believe...";
			link.l1 = "That's right, Padre. I somehow value my skin... Well, thanks for that, too. And now let me take my leave, Holy Father.";
			link.l1.go = "Step_S2_22";
		break;
 		case "Step_S2_22":
			dialog.text = "Yes, yes, of course. I will also run and write about the good news to Seville!";
			link.l1 = "Goodbye, monsignor.";
			link.l1.go = "exit";
            GiveItem2Character(pchar, "cirass5");
		break;
//********************************* Захват Рока Бразильца. Квест №3 **********************************
 		case "Step_S3_1":
            if (CheckPassengerInCharacter(pchar, "RockBrasilian"))
            {
    			dialog.text = "Great job, "+ GetSexPhrase("my son","my daughter") +"! I'm in awe!";
    			link.l1 = "I can say without false modesty - it was not easy to capture the scoundrel. To do this, I had to board a corvette packed with pirate rabble from Tortuga.";
    			link.l1.go = "Step_S3_2";
            }
            else
            {
    			dialog.text = "However, you don't have it in the hold! "+ GetSexPhrase("my son","my daughter") +"Go and bring me Rock the Brazilian.";
    			link.l1 = "All right, monsignor...";
    			link.l1.go = "exit";
            }
		break;
 		case "Step_S3_2":
			dialog.text = "Well, order this ladron to be delivered to me immediately, I can't wait to start the investigation. And I ask you to come to the Governor-General as well.";
			link.l1 = "All right, monsignor.";
			link.l1.go = "exit";
			//NPChar.LifeDay = 10;
    	    //SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			AddQuestRecord("Spa_Line_3_RockBrasilian", "6");
			pchar.questTemp.State = "TakeRockBras_RockGiven";
			sld = characterFromId("RockBrasilian");
			ReleasePrisoner(sld);
     	    sld.LifeDay = 0; // уберём нпс
		break;
//********************************* Квест "Witch Hunt" **********************************		
		case "Inqizitor_2":
			dialog.text = "Ah, may your soul be eternally blessed for your righteous deed, "+ GetSexPhrase("my son","my daughter") +". We will take care of this witch.";
			link.l1 = "I hope so, Holy Father. Have a nice day.";
			link.l1.go = "KAZN";
			AddBonusEnergyToCharacter(pchar, 25);
			PlaySound("Interface\new_level.wav");
			Log_info("The Inquisitor blessed you.");
			Log_info("Your energy has increased by 25 forever.");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_OhotaNaVedmu");
		break;

		case "KAZN":
			DialogExit();
			TavernWaitDate("wait_night");
			PostVideoAndQuest("Witch",50,"PDM_ONV_Kazn_NEW");
			//DoQuestReloadToLocation("Santiago_town", "officers", "reload8_2", "PDM_ONV_KaznVedmi");
		break;
//**************************** сдаём зачарованный Дес-Мойнес ********************************
		case "MCIncq":
			dialog.text = "I am listening, "+ GetSexPhrase("my son","my daughter") +".";
			link.l1 = "I want to tell you about the devil's place where the devil walks at night!";
			link.l1.go = "MCIncq_1";
		break;
		case "MCIncq_1":
			dialog.text = "...";
			link.l1 = "This is the town of Des Moines, in the lagoon of Maracaibo. We must burn it down!";
			link.l1.go = "MCIncq_2";
		break;
		case "MCIncq_2":
			dialog.text = "Yeah... we'll do it, "+ GetSexPhrase("my son","my daughter") +". God thanks you for your faithful service to the church.";
			link.l1 = "Thank God!";
			link.l1.go = "MCIncq_3";
		break;
		case "MCIncq_3":
			dialog.text = "Accept 50000 piasters as a reward for your efforts.";
			link.l1 = "I'am greatful, your Holiness!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 50000);
			CloseQuestHeader("MagicCity");
			pchar.questdata.ZacharovanyGorod = 1;
			SetTimerFunction("MC_DesMoinesVozrojdenie", 0, 0, 1);
		break;

    }
}
