// boal 27.03.2004 Изабела Армани (романтическая ветка)
void ProcessDialogEvent()
{
	ref NPChar, d, sld, rColony;
	aref Link, NextDiag;
	string NPC_Meeting;
	int i, iMoney, iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, sTemp;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
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
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
					//когда достал обещаниями денег дать
                    if (npchar.angry.name == "NewLife_Budget_Add") Dialog.CurrentNode = "AngryRepeat_Budget_Add";
					//когда подарками достал, а сам не давал
					if (npchar.angry.name == "NewLife_Present") Dialog.CurrentNode = "AngryRepeat_Present";
                break;
				case "quest":
					//когда долги достали Изабеллу
					if (npchar.angry.name == "NewLife_Budget_Pay") Dialog.CurrentNode = "AngryRepeat_Budget_Pay";
					//когда достало Изабеллу пиратсво ГГ
					if (npchar.angry.name == "NewLife_KnowPirates") Dialog.CurrentNode = "AngryRepeat_KnowPirates";
				break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "first time";
			//был в спальне
			pchar.quest.wasInBeedroom = true;
			bDisableFastReload = true;
			// прерывание на выход, а то ход истории в руках геймера
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
            dialog.text = "How did you get here? If you don't leave my bedroom immediately, I'll call my husband.";
			link.l1 = "I am " + GetFullName(pchar) + ". May I know the name of such a beautiful senorita?";
			link.l1.go = "Next_1";
			link.l2 = "Please forgive me. I'm already leaving...";
			link.l2.go = "exit";
		break;

		case "Next_1":
			NextDiag.TempNode = "Next_2";

            dialog.text = "Seniora, not senorita. I am the owner of this house, " + GetFullName(npchar) + ". Why did you break into my chambers?";
            link.l1 = "Calm down, senora, I am your husband's companion. He invited me to explore your new house, and there are so many rooms here that it's not difficult to get lost.";
			link.l1.go = "Next_4";
			link.l2 = "Simple curiosity. I'm already leaving.";
			link.l2.go = "exit";
		break;

		case "Next_2":
			NextDiag.TempNode = "Next_2";
            dialog.text = "Are you still here? Leave me alone!";
            link.l1 = "May I know something?";
			link.l1.go = "Next_3";
            link.l2 = "Sorry...";
			link.l2.go = "exit";
		break;

		case "Next_3":
			NextDiag.TempNode = "Next_2";
            dialog.text = "What do you need from me? Talk to my husband. I don't want to talk to you right now.";
            link.l1 = "Okay, I'll do that.";
			link.l1.go = "exit";
		break;

		case "Next_4":
            dialog.text = "Yes, we recently bought this house. And what kind of business do you have in common with my husband?";
            link.l1 = "Our interests overlap in the commercial sphere of influence of the Spanish Crown.";
			link.l1.go = "Next_5";
            link.l2 = "We are old friends.";
			link.l2.go = "Next_6";
			link.l3 = "Must bow out. I'm sorry.";
			link.l3.go = "Next_7";
		break;

		case "Next_5":
            dialog.text = "Interests... commercial... intersect... I'm too far away from that. Well, come on. How do you like our house? I chose the decor myself.";
            link.l1 = "Simply incomparable! You have such refined taste!";
			link.l1.go = "Next_8";
            link.l2 = "Honestly, it's not impressive. I saw something similar in the English colony.";
			link.l2.go = "Next_9";
			Pchar.RomanticQuest.TalkInShop = true;
		break;

		case "Next_6":
            dialog.text = "Friends? I don't think my husband can have such friends. "+ Characters[GetCharacterIndex("Husband")].Name + "!!!";
            link.l1 = "Wait! I'll explain everything...";
			link.l1.go = "Romantic_Battle_in_Bedroom";
		break;

		case "Next_7":
			dialog.text = "I don't like you. I think it would be better if I called my husband. "+ Characters[GetCharacterIndex("Husband")].Name + "!!!";
            link.l1 = "Wait! I'll explain everything...";
			link.l1.go = "Romantic_Battle_in_Bedroom";
		break;

		case "Next_8":
		    NextDiag.TempNode = "Good_1";
            dialog.text = "I'm flattered. You know how to win over a lady, senor.";
            link.l1 = "I just told the truth. And now let me take my leave, I won't bother you...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 3);
		break;

		case "Next_9":
		    NextDiag.TempNode = "Next_2";
            dialog.text = "In my opinion, you are just an uncouth blockhead!";
            link.l1 = "Well... some people think otherwise...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -4);
		break;

		case "Good_1":
		    NextDiag.TempNode = "Good_1";
            dialog.text = "Glad to meet you again. By what fates?";
            link.l1 = "Just came to greet you, lovely " + npchar.name+".";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep)+1;
			pchar.quest.wasInBeedroom = true;
			bDisableFastReload = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
		break;

		case "Romantic_Battle_in_Bedroom":
		    NextDiag.CurrentNode = "Next_2";
			DialogExit();
			AddDialogExitQuest("Romantic_Battle_in_Bedroom_1");
		break;

		case "Murder":
		    NextDiag.TempNode = "Murder";
            dialog.text = "Leave me alone, you dirty murderer!";
            link.l1 = "...";
			link.l1.go = "exit";
			PChar.quest.Romantic_TalkInShop.over = "yes";
		break;

		case "TalkInShop":
		    NextDiag.TempNode = "TalkInShop_2";
            dialog.text = "Captain " + GetFullName(PChar)+"!";
            link.l1 = "Senora! What a pleasant meeting!";
			link.l1.go = "exit";
			//AddDialogExitQuest("Romantic_TalkInShop_3");
		break;

		case "TalkInShop_2":
            dialog.text = "For God's sake, Captain, leave him alone!";
            link.l1 = "Not before this scoundrel asks for forgiveness!";
			link.l1.go = "TalkInShop_3";
		break;

		case "TalkInShop_3":
            dialog.text = "Why, it's just a little misunderstanding.";
            link.l1 = "Then tell me what happened?";
			link.l1.go = "TalkInShop_4";
		break;

		case "TalkInShop_4":
            dialog.text = "I came to find out why the groceries weren't delivered today as agreed. I was sure my husband had paid for them, but apparently he had forgotten. It turns out we have a month's debt. I don't have 1200 gold pieces. I said I'd bring them later, and senor " +
                          GetCharacterFullName("SanJuan_trader")+" decided that I refused to pay at all.";
            link.l1 = "(to the merchant) Get your money, you worthless huckster.";
			link.l1.go = "TalkInShop_5";
			link.l2 = "(to the merchant) Well, now he'll believe you, won't he?";
			link.l2.go = "TalkInShop_6";
		break;

		case "TalkInShop_5":
            AddMoneyToCharacter(pchar, -1200);
		    NextDiag.TempNode = "Good_1";
            dialog.text = "I'm really embarrassed, Captain. I will refund your money immediately. Now I have to go.";
            link.l1 = "Empty, Senora Isabella. I am fully rewarded for having the good fortune to see you.";
			link.l1.go = "TalkInShop_Go";
		break;

		case "TalkInShop_6":
            NextDiag.CurrentNode = "TalkInShop_7";
			DialogExit();
			characters[GetCharacterIndex("SanJuan_trader")].dialog.currentnode = "Romantic_2";
			AddDialogExitQuest("Romantic_TalkInShop_3");
		break;

		case "TalkInShop_7":
		    NextDiag.TempNode = "Good_1";
            dialog.text = "Thank you. But I have to go. Goodbye.";
            link.l1 = "Empty, Senora Isabella. I am fully rewarded for having the good fortune to see you.";
			link.l1.go = "TalkInShop_Go";
		break;

		case "TalkInShop_Go":
            NextDiag.CurrentNode = "Good_1";
			DialogExit();
            LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "SanJuan_church", "goto", "goto1", "Romantic_TalkInShop_end", 4.0);
			chrDisableReloadToLocation = true;
		break;

		case "TalkInChurch":
		    //NextDiag.TempNode = "TalkInChurch_1";
            dialog.text = "Captain, I am glad to see you. Tell me, aren't you captain of the brig Five Wounds of Christ?";
            link.l1 = "'The Five Wounds of Christ'? A sinner like me would never have thought of calling his vessel by such a pious name. However, for the sake of the beautiful senora, I am ready to change not only the name of the ship, but also my own.";
			link.l1.go = "TalkInChurch_1";
			DeleteAttribute(npchar, "talker"); //снимаем говорилку
		break;

		case "TalkInChurch_1":
            dialog.text = "Sorry, Captain, I made a mistake.";
            link.l1 = "Wait, senora! Why are you so sad? Who is this lucky captain whose fate worries you so much? Maybe I've heard something about him and I can help you?";
			link.l1.go = "TalkInChurch_2";
		break;

		case "TalkInChurch_2":
            dialog.text = "I remember, you're a captain too, right? The brig Five Wounds of Christ was supposed to anchor in the harbor of San Juan yesterday. Maybe a recent storm caught him on his way from Cumana?";
            link.l1 = "Alas, senora, I know nothing about the fate of this brig, but I am ready to immediately go in search of your brave captain if you give me a single smile.";
			link.l1.go = "TalkInChurch_3";
		break;

		case "TalkInChurch_3":
            dialog.text = "Ah, senor, it's not this captain I'm waiting for, God bless him. There should be a passenger on board-my brother Don Miguel de Valdez. I promise you a smile for the good news about this ship.";
            link.l1 = "I'm sailing to Cumana immediately, lovely senora!";
			link.l1.go = "TalkInChurch_4";
		break;

		case "TalkInChurch_4":
            dialog.text = "I look forward to hearing from you about my brother. Do you remember where my house is?";
            link.l1 = "Yes, of course. Have a nice day.";
			link.l1.go = "TalkInChurch_Go";
		break;

		case "TalkInChurch_Go":
			chrDisableReloadToLocation = true;
            NextDiag.CurrentNode = "WaitShip";
            Pchar.RomanticQuest.ShipToCumana = true;
			DialogExit();
			AddQuestRecord("Romantic_Line", "5");
			LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "SanJuan_houseS1Bedroom", "goto", "goto4", "Romantic_TalkInChurch_end", 20.0);
            // немного весёлой жизни
            TraderHunterOnMap();
		break;

		case "WaitShip":
		    NextDiag.TempNode = "WaitShip";
            dialog.text = "Is there any news?";
            link.l1 = "I will inform you when I find out the fate of the ship 'Five Wounds of Christ'. See you later, " + npchar.name+ ".";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep)+1;
			bDisableFastReload = true;
			pchar.quest.wasInBeedroom = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
		break;
		// разговор с братом
		case "Brother_1":
            dialog.text = "Miguel! I'm so glad to see you! I was worried about you! I haven't heard from you for so long! How's the father?";
            link.l1 = "Isabella! If it hadn't been for this brave captain, I wouldn't have been able to get to San Juan for a long time. Terrible storms raged around Cumana like demons. I bring the terrible news-our father is dead, Isabella! He was forced to sell the family estate to pay your bills. It was a real tragedy for him, and his heart couldn't stand it!";
			link.l1.go = "Brother_2";
		break;
		case "Brother_2":
            dialog.text = "But, Miguel! But I didn't issue any bills! This is some kind of tragic misunderstanding!";
            link.l1 = "Sister, you have not yet thanked our wonderful captain for the service so kindly rendered to us. I guess we can figure out our family matters later.";
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_Brother_House_3");
			NextDiag.TempNode = "Brother_3";
		break;
		case "Brother_3":
            dialog.text = "Ah, captain " + GetFullName(pchar)+"! I am grateful to you from the bottom of my heart! Forgive me! I was so shocked by my father's death that I forgot about you! I will be glad to see you at our house tonight!";
            link.l1 = "Senora Isabella! I am always at your service. And now, if you'll excuse me, I have to leave you.";
			link.l1.go = "Brother_4";
		break;
		case "Brother_4":
			AddQuestRecord("Romantic_Line", "8");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SanJuan_houseS1Bedroom", "goto", "goto4", "Romantic_TalkInChurch_end", 5.0);
			NextDiag.CurrentNode = "Temp_Thanks";
			DialogExit();
		break;
		case "Temp_Thanks":
            NextDiag.TempNode = "Temp_Thanks";
            dialog.text = "Oh, brave captain! I'm waiting for you for dinner tonight!";
            link.l1 = "I will certainly be there, Senora Isabella.";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep)+1;
			bDisableFastReload = true;
			pchar.quest.wasInBeedroom = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
		break;
		// разговор с ГГ на взятом бриге
		case "BrigAbordage":
            dialog.text = "IT'S YOU!!! A ruthless and hypocritical murderer! A thief and a pirate!";
            link.l1 = "Senora, I am not sinless, but my honor is not allowed to offend even you!";
			link.l1.go = "BrigAbordage_1";
		break;
		case "BrigAbordage_1":
            dialog.text = "Don't pretend to be innocent! Salvator told me how you meanly killed my brother Miguel! Yes! The murderer!";
            link.l1 = "And you believed it? Senora! I'm willing to do so much for you, and you think I killed your brother? Senora...";
			link.l1.go = "BrigAbordage_2";
		break;
		case "BrigAbordage_2":
            dialog.text = "My brother is dead, and you ran away! I don't want to listen to your excuses!";
			if (CheckCharacterItem(pchar, "Order"))
			{
				link.l1 = "I don't need to make excuses, because I saw Salvator stab your brother myself. Miguel found out that it was Salvator who forged the bills that killed your father. He was going to report it to the authorities, and then Salvator killed him. I found the forged bills on your brother's body. They are covered in Don Miguel's blood, but they are quite readable. Here they are, take a look...";
				link.l1.go = "BrigAbordage_8";
			}
			else
			{
				link.l1 = "I have no need to justify myself, because I saw Salvator stabbing your brother. Your brother found out that it was Salvator who forged the bills that killed your father. Don Miguel was going to report this to the governor, and then Salvator killed him. He tried to kill me too to cover up his crime. You wouldn't have believed me anyway, so I decided to leave the city for a while.";
				link.l1.go = "BrigAbordage_3";
			}
		break;
		// --> нету поддельных векселей в наличие
		case "BrigAbordage_3":
            dialog.text = "You, Captain, are not only a bloody murderer, but also a dirty liar! How can you confirm the correctness of your words?";
            link.l1 = "Senora, I heard with my own ears how your brother boldly threw accusations of forgery of bills in Salvator's face. And then I saw with my own eyes how Salvator and two murderers stabbed poor Miguel! Unfortunately, I didn't have time to come to the rescue...";
			link.l1.go = "BrigAbordage_4";
		break;
		case "BrigAbordage_4":
            dialog.text = "Do you want me to believe your words? And where are those 'fake bills' that killed my brother?! Show them to me!";
            link.l1 = "I don't have them, senora...";
			link.l1.go = "BrigAbordage_5";
		break;
		case "BrigAbordage_5":
            dialog.text = "Truly, there are no limits to human baseness. Listen up, Captain! I hate and deeply despise you...";
            link.l1 = "Senora Isabella, we don't have time to talk, the ship is going to sink soon. I suggest we continue this conversation on my ship.";
			link.l1.go = "BrigAbordage_6";
		break;
		case "BrigAbordage_6":
            dialog.text = "Listen, you vile pirate! No force in the world will force me to go with you. If I'm going to die, then let it be here and now. And I curse you, Captain, for all the troubles you have brought to our family!";
            link.l1 = "Damn it, Isabella!!";
			link.l1.go = "BrigAbordage_7";
		break;
		case "BrigAbordage_7":
            dialog.text = "Goodbye, I won't say another word...";
            link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetPlayerType(pchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.location = "none";
			npchar.location.group = "";
			npchar.location.locator = "";
			AddQuestRecord("Romantic_Line", "17");
			QuestSetCurrentNode("Atilla", "Isabella_Sink");
		break;
		// --> поддельные векселя - у ГГ.
		case "BrigAbordage_8":
            dialog.text = "WHAT?!! Salvator?!! This is a vile lie!! Bills of exchange! Salvator loves me... You bastard! But this is a letter... and this ship... I'm completely confused... As I wish it was just a dream, captain " + GetFullName(pchar) + ".";
            link.l1 = "Letter? A ship? What are you talking about?";
			link.l1.go = "BrigAbordage_9";
			TakeItemFromCharacter(pchar, "Order");
		break;
		case "BrigAbordage_9":
            dialog.text = "The captain of this ship came to my house with a letter written in Salvator's handwriting. My husband wrote about some kind of danger that threatens me. He asked me to leave San Juan on the ship of captain who delivered the letter. But as soon as the ship left the harbor of San Juan, I was locked in a cabin. It's only now that I realize I've fallen into a trap!";
            link.l1 = "Where is Salvator now? I think it's time to talk to him.";
			link.l1.go = "BrigAbordage_10";
		break;
		case "BrigAbordage_10":
            dialog.text = "I do not know where my husband is... God, this is just unbearable! To lose my father and brother, and now it turns out that my husband Salvator is the culprit of all these troubles!"+
				          "May I ask you a favor, Captain?";
            link.l1 = "I will be glad to serve you, Senora Isabella.";
			link.l1.go = "BrigAbordage_11";
		break;
		case "BrigAbordage_11":
            dialog.text = "Could you take me to my cousin Rosita Fernandez in Belize?";
            link.l1 = "Of course, senora. But let me, since we are near Porto Bello, visit this city. I will try to find Salvator there, because he is waiting for your arrival.";
			link.l1.go = "BrigAbordage_12";
		break;
		case "BrigAbordage_12":
            dialog.text = "All right, Captain. Well, after that, please take me to Rosita...";
            link.l1 = "Everything will be done, senora.";
			link.l1.go = "exit";
			LAi_SetPlayerType(pchar);
			pchar.RomanticQuest = "SeekInPortoBello";
			AddQuestRecord("Romantic_Line", "18");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			//засада, оставленная Сальватором в Порто Белло
            Pchar.quest.Romantic_AmbushInPortoBello.win_condition.l1 = "location";
            Pchar.quest.Romantic_AmbushInPortoBello.win_condition.l1.location = "PortoBello_houseF2";
            Pchar.quest.Romantic_AmbushInPortoBello.win_condition = "Romantic_AmbushInPortoBello";
			//кузину Роситу в дом Белиза
			sld = GetCharacter(NPC_GenerateCharacter("Rosita", "girl_11", "woman", "towngirl", 5, SPAIN, -1, false));
            sld.name 	= "Fernandez";
	        sld.lastname = "Senior ";
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
	        sld.dialog.currentnode = "Rosita";
			sld.greeting = "Gr_Dama";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_houseS4", "goto", "goto2");
		break;
		//Изабелла в доме с засадой в Порто Белло
		case "AmbushPortoBello":
            dialog.text = ", I went ashore from the ship to find out how you are doing " + pchar.name + "Senora Isabella, this is a very rash act...";
            link.l1 = "My God, what happened here?!!";
			link.l1.go = "AmbushPortoBello_1";
		break;
		case "AmbushPortoBello_1":
            dialog.text = "Oh, Isabella, you are very unlucky with your marriage. These are the two bandits that Salvator ordered your murder.";
            link.l1 = "My murder?!";
			link.l1.go = "AmbushPortoBello_2";
		break;
		case "AmbushPortoBello_2":
            dialog.text = "That's right. As one of the couple said, 'strangle quietly.' They told me everything-they confused me with captain of the brig that took you out of San Juan. Senora, it's just lucky that I found out about it in time and managed to intercept you...";
			link.l1 = "The right word, Captain, it really is. Without any doubt, I owe you my life...";
			link.l1.go = "AmbushPortoBello_3";
		break;
		case "AmbushPortoBello_3":
            dialog.text = "Empty, Isabella. When I see you so scared and defenseless, a hitherto unknown feeling wakes up in my soul...";
            link.l1 = "Ah, senor ";
			link.l1.go = "AmbushPortoBello_4";
		break;
		case "AmbushPortoBello_4":
            dialog.text = ", now is not the time and, moreover, not the place for this kind of conversation. I'm sorry, Captain " + pchar.name + "Let's leave this terrible place!"+
				          "Forgive me, Senora Isabella, I really chose the wrong time... We're leaving.";
            link.l1 = "Well, we've arrived. What do you say, senor ";
			link.l1.go = "AmbushPortoBello_5";
		break;
		case "AmbushPortoBello_5":
			AddQuestRecord("Romantic_Line", "24");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			DialogExit();
		break;
		//Изабелла на выходе из дома Роситы в Белизе
		case "BelizTalk":
            dialog.text = "?" + pchar.name + "?";
            link.l1 = "Senora, I have fulfilled your request. I have already informed Rosita of your arrival, she is waiting for you. Besides, I've looked around the house and found out from your cousin that Salvator hasn't been around.";
			link.l1.go = "BelizTalk_1";
		break;
		case "BelizTalk_1":
            dialog.text = "Captain, you are my guardian angel...";
            link.l1 = "Isabella, tell me, can I talk about my feelings now?";
			link.l1.go = "BelizTalk_2";
		break;
		case "BelizTalk_2":
            dialog.text = "Speak, senor...";
            link.l1 = "Isabella, you know that I am a privateer. An occupation unworthy of the cavalier of a lady like you. But I like you, Isabella, and I want you to know that!";
			link.l1.go = "BelizTalk_3";
		break;
		case "BelizTalk_3":
            dialog.text = "Captain " + pchar.name + "You are a noble man, a true knight. I owe you my life, but I want to say bluntly that my feelings for you are not limited to gratitude for your salvation...";
            link.l1 = "Senora, if I understand you correctly, can I hope that one day you will say yes to me?";
			link.l1.go = "BelizTalk_4";
		break;
		case "BelizTalk_4":
            dialog.text = "You got it right, my guardian angel.";
            link.l1 = "I'm just damn happy and ready to jump for joy like a boy! Oh, forgive me, senora, for a strong word - it escaped...";
			link.l1.go = "BelizTalk_5";
		break;
		case "BelizTalk_5":
            dialog.text = "Nothing, Captain. I will try to soften your temper if I am given the opportunity.";
            link.l1 = "Isabella, I am yours to the core. But now we have one little business left-Salvator.";
			link.l1.go = "BelizTalk_6";
		break;
		case "BelizTalk_6":
            dialog.text = "And what do you want to do?";
            link.l1 = "I don't know, there are no clear leads, Salvator is constantly on the move. But I have a mutual friend of ours, a pirate named Atilla. Salvator owes him a lot...";
			link.l1.go = "BelizTalk_7";
		break;
		case "BelizTalk_7":
            dialog.text = "Clear, Captain. Well, I need to take a break from what I've been through for now, I'll be waiting for you with good news here at my cousin's.";
            link.l1 = "Goodbye, Isabella.";
			link.l1.go = "BelizTalk_8";
		break;
		case "BelizTalk_8":
			QuestSetCurrentNode("Atilla", "SalvatorNews");
			NextDiag.CurrentNode = "BelizTalk_after";
			AddQuestRecord("Romantic_Line", "19");
			chrDisableReloadToLocation = false;
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseS4", "Beliz_houseS4", "goto", "goto1", "Romantic_TalkInChurch_end", 3.5);
			DialogExit();
		break;
		case "BelizTalk_after":
            dialog.text = "Captain, what news do you have?";
            link.l1 = "None yet, Isabella.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BelizTalk_after";
		break;
		//Изабелла в пещере
		case "IsabellaInCave":
            dialog.text = "Ah, here you are, " + pchar.name + "! I've finally waited for you!";
            link.l1 = "Isabella, you are alive! Thank the Lord! I found a dead girl in the jungle, apparently this is the maid you left Rosita's house with yesterday.";
			link.l1.go = "IsabellaInCave_1";
		break;
		case "IsabellaInCave_1":
            dialog.text = "Poor Kanchita, Salvator killed her!";
            link.l1 = "Bastard! Tell me quickly, Isabella, what happened?";
			link.l1.go = "IsabellaInCave_2";
		break;
		case "IsabellaInCave_2":
            dialog.text = pchar.name + "My husband is a fiend! I must admit that I acted very recklessly - I went out for a walk outside the city every day. Yesterday Salvator and another bandit attacked us, and this killer, without hesitation, stabbed Kanchita with a knife. My God!..";
            link.l1 = "Calm down, Isabella... What happened next?";
			link.l1.go = "IsabellaInCave_3";
		break;
		case "IsabellaInCave_3":
            dialog.text = "Then they dragged me here. Salvator tried to get me to sign a power of attorney for the disposal of poor Miguel's property, because after his death everything went to me in his will.";
            link.l1 = "So that's why he didn't kill you immediately! Isabella, it's just unprecedented luck that Salvator found out about Miguel's will.";
			link.l1.go = "IsabellaInCave_4";
		break;
		case "IsabellaInCave_4":
            dialog.text = "I realized that as soon as I sign these papers, I will be dead in the same minute. I gathered all my strength and refused to sign, despite all the threats. I only hoped that Rosita would inform you about my disappearance and you would be able to find me...";
            link.l1 = "Oh, Isabella, I'm good too! I left you in Belize alone and without protection! But you could have guessed what this could lead to...";
			link.l1.go = "IsabellaInCave_5";
		break;
		case "IsabellaInCave_5":
            dialog.text = "Don't beat yourself up, " + pchar.name + "because you saved me again.";
            link.l1 = "Isabella, I've dealt with your jailers, but where is Salvator himself?";
			link.l1.go = "IsabellaInCave_6";
		break;
		case "IsabellaInCave_6":
            dialog.text = "He went to the city, but promised to return soon with a brazier.";
            link.l1 = "Which brazier?";
			link.l1.go = "IsabellaInCave_7";
		break;
		case "IsabellaInCave_7":
            dialog.text = "With a brazier and tongs to cauterize my heels.";
            link.l1 = "Damn it! I really showed up here on time...";
			link.l1.go = "exit";
			LAi_SetActorType(npchar);
			pchar.RomanticQuest = "FoundIsabella";
			AddDialogExitQuest("Romantic_SalvatorInCave");
		break;
		//после схватки с Сальватором в пещере
		case "SalvatorIsDead":
            dialog.text = "It's over!";
            link.l1 = "Finally, Isabella...";
			link.l1.go = "SalvatorIsDead_1";
		break;
		case "SalvatorIsDead_1":
            dialog.text = "Senior " + pchar.name + "Please take me to Rosita's house.";
            link.l1 = "Senora Isabella, since that's how it turned out and you're now a widow, then let me offer you my hand and heart!";
			link.l1.go = "SalvatorIsDead_2";
		break;
		case "SalvatorIsDead_2":
            dialog.text = pchar.name + ", I accept your offer.";
            link.l1 = "Great! In the meantime, I'll try to find what Salvator stole from you.";
			link.l1.go = "SalvatorIsDead_3";
		break;
		case "SalvatorIsDead_3":
            dialog.text = "Senor, do whatever you want, I just want to forget about everything that happened\n"+
				          "Let's do it this way: I'll stay with Rosita for a few days, and then I'll get to San Juan on my own, because now I'm not in danger.";
            link.l1 = "Yes, Isabella, I believe that there is no danger for you anymore.";
			link.l1.go = "SalvatorIsDead_4";
		break;
		case "SalvatorIsDead_4":
            dialog.text = "In San Juan, I will put my affairs in order, return my maiden name - de Valdez, and in about a month we will get married in the church of the city.";
            link.l1 = "Very reasonable, Isabella...";
			link.l1.go = "SalvatorIsDead_5";
		break;
		case "SalvatorIsDead_5":
            dialog.text = "But you must promise me that you will give up your current occupation - privateering.";
            link.l1 = "Senora, this is a serious step for me. I do this for a living. But I'll do anything for you... I agree, Isabella!";
			link.l1.go = "SalvatorIsDead_6";
		break;
		case "SalvatorIsDead_6":
            dialog.text = "Very good, " + pchar.name + ". And now I ask you to take me to my cousin, I can't be here anymore...";
            link.l1 = "Okay, Isabella.";
			link.l1.go = "SalvatorIsDead_7";
		break;
		case "SalvatorIsDead_7":
			Pchar.quest.Romantic_DelivToRosita.win_condition.l1 = "location";
			Pchar.quest.Romantic_DelivToRosita.win_condition.l1.location = "Beliz_houseS4";
			Pchar.quest.Romantic_DelivToRosita.win_condition = "Romantic_DelivToRosita";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
		//после спасения в доме у Роситы
		case "RositaHouse":
            dialog.text = "Captain" + GetFullName(pchar) + ", I'm waiting for you in San Juan in a month...";
            link.l1 = "Okay, Isabella. But are you sure you can get there yourself without any problems?";
			link.l1.go = "RositaHouse_1";
			AddQuestRecord("Romantic_Line", "22");
		break;
		case "RositaHouse_1":
            dialog.text = "I'll be in San Juan in a month, rest assured...";
            link.l1 = "Okay, Isabella.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RositaHouse_1";
		break;
		//Изабелла вновь в Сан-Хуане
		case "InSanJuanAgain":
            dialog.text = "Senior " + pchar.name + "You have arrived...";
            link.l1 = "Yes, Senora Isabella. Is everything okay?";
			link.l1.go = "InSanJuanAgain_1";
		break;
		case "InSanJuanAgain_1":
            dialog.text = "Yes, everything is fine. So, my guardian angel, are you ready for a quiet family life?";
            link.l1 = "Yes, Isabella, I've had enough blood.";
			link.l1.go = "InSanJuanAgain_2";
		break;
		case "InSanJuanAgain_2":
            dialog.text = "And do you still love me?";
            link.l1 = "Isabella, dear, how can you ask such a thing?! I'm crazy about you!";
			link.l1.go = "InSanJuanAgain_3";
		break;
		case "InSanJuanAgain_3":
            dialog.text = "Okay, " + pchar.name + ". Then I'll tell you that everything is already prepared for the wedding. I'll be waiting for you at the altar in the church tomorrow morning...";
            link.l1 = "Isabella... In the morning our destinies will unite!";
			link.l1.go = "InSanJuanAgain_4";
		break;
		case "InSanJuanAgain_4":
            dialog.text = "Yes, my knight. And now I ask you to leave my house, there is nothing for you to do here before the wedding...";
            link.l1 = "Okay, Isabella, see you tomorrow...";
			link.l1.go = "exit";
			NextDiag.TempNode = "InSanJuanAgain_after";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //закрываем двери дома.
			pchar.RomanticQuest = "WaitBeginWidding";
			AddQuestRecord("Romantic_Line", "23");
		break;
		case "InSanJuanAgain_after":
			dialog.text = NPCStringReactionRepeat("There is nothing for you to do here before the wedding...", "Senor, be reasonable! Before the wedding, you can't!", "No, no and no again!",
                          "Senor 'my beloved', I ask you to leave immediately!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oh, Isabella, how can I stand all this?! I want to see you now...", "Isabella, this is some kind of curse. I'll go crazy until tomorrow!",
                      "Carramba! But what to do? But I am glad that the laws of honor for my bride are not an empty word...", "Ah, Isabella, I have to obey ...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "InSanJuanAgain_out", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "InSanJuanAgain_after";
		break;
		case "InSanJuanAgain_out":
			AddDialogExitQuest("Romantic_OutFromHouse");
			DialogExit();
		break;

		case "Cancel_Widding":
            dialog.text = "How dare you not come to the church for the wedding?! I gave you my love, and you trampled on it so cruelly and incompetently!";
            link.l1 = "Isabella...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Cancel_Widding_1";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //закрываем дом
			CloseQuestHeader("Romantic_Line");
			pchar.questdata.IstoriyaIzabely = 1;
		break;
		case "Cancel_Widding_1":
            dialog.text = "That's it, I've had enough. Get out!";
            link.l1 = "Oh, Isabella...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Cancel_Widding_1";
		break;
		//свадьба
		case "TalkWidding":
            dialog.text = "Hello, " + pchar.name + ".";
            link.l1 = "Hello, Isabella... You are more beautiful today than ever!";
			link.l1.go = "TalkWidding_1";
		break;
		case "TalkWidding_1":
            dialog.text = "Thank you, " + pchar.name + ". Are you ready, can we start?";
            link.l1 = "Of course!";
			link.l1.go = "TalkWidding_2";
		break;
		case "TalkWidding_2":
            dialog.text = "Padre, you can start...";
            link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "barmen", "stay");
			AddDialogExitQuest("Romantic_Padre");
		break;
		//драка в церкви
		case "AmbushInChurch":
            dialog.text = "What's going on? " + pchar.name + "I'm afraid!";
            link.l1 = "Isabella, aside!!";
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_fightInChurch_2");
		break;
		case "IsabellaIsMyWife":
			dialog.text = "Were these Salvator's men? But how can this be-you killed him in front of me?!";
			link.l1 = "He hired them before I killed him.";
			link.l1.go = "IsabellaIsMyWife_1";
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = "Oh, my God, am I really going to live in fear like this?";
			link.l1 = "Isabella, that's it! Salvator is gone, and so are the people he hired.";
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = "I really hope so... " + pchar.name + "I want to go home as soon as possible!";
			link.l1 = "Go, dear, I'll be a little late, but I'll be home soon.";
			link.l1.go = "IsabellaIsMyWife_3";
		break;
		case "IsabellaIsMyWife_3":
			rColony = GetColonyByIndex(FindColony("SanJuan"));
			dialog.text = "Dear, you need to go to the governor and personally tell him everything about this incident. After that, we need to get the approval of the authorities to live in the city.";
			if (sti(rColony.HeroOwn))
			{
				link.l1 = "Isabella, this city belongs to me with all its guts. So don't worry...";
				LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			}
			else
			{
				link.l1 = "Okay, Isabella, I'll do everything...";
				pchar.RomanticQuest.MayorOk = 1; //флаг на базар с мэром Сан-Хуана
			}
			link.l1.go = "IsabellaIsMyWife_4";
		break;
		case "IsabellaIsMyWife_4":
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto1", "Romantic_TalkInChurch_end", 15.0);
			NextDiag.TempNode = "NewLife_firstTime";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//первый диалог после свадьбы
		case "NewLife_firstTime":
			rColony = GetColonyByIndex(FindColony("SanJuan"));
			dialog.text = "Oh dear, it's good that you finally came home! Have you settled all the issues with the incident at the church?";
			if (sti(rColony.HeroOwn))
			{
				dialog.text = "Oh dear, it's good that you finally came home! Is everything okay?";
				link.l1 = "Yes, dear, everything is fine...";
			}
			else
			{
				dialog.text = "Oh dear, it's good that you finally came home! Have you settled all the issues with the incident at the church?";
				link.l1 = "Yes, dear, I was at the governor's reception. It's all right-he congratulates us.";
			}
			link.l1.go = "NewLife_firstTime_1";
		break;
		case "NewLife_firstTime_1":
			dialog.text = "Well, that's very good. Now, if you don't mind, let's discuss the principles of living together.";
			link.l1 = "What principles can there be, Isabella? I like you-that's the basic principle!";
			link.l1.go = "NewLife_firstTime_2";
		break;
		case "NewLife_firstTime_2":
			dialog.text = "And I like you too, dear. But family is not only love, it is also a life together. Thus, in addition to mutual love, we have at least two more principles by which our family should live.";
			link.l1 = "Isabella, I admire your discretion! But maybe we'll stop at the first principle for now and put it into practice immediately?";
			link.l1.go = "NewLife_firstTime_3";
		break;
		case "NewLife_firstTime_3":
			dialog.text = "Dear, all in good time, don't be too persistent! Let's discuss the remaining two first, do you mind...?";
			link.l1 = "Darling, anything is for you... Let's discuss these two principles.";
			link.l1.go = "NewLife_firstTime_4";
		break;
		case "NewLife_firstTime_4":
			dialog.text = "Honey, I adore you... So, principle number two is finance. We have to determine the family budget. Your home was a ship, but now your home is here, and you must understand that owning real estate is a certain financial burden, that is, city taxes\n"+
				          "In addition, providing for our living needs also requires costs...";
			link.l1 = "Isabella, I'm ready to give everything I have!";
			link.l1.go = "NewLife_firstTime_5";
		break;
		case "NewLife_firstTime_5":
			dialog.text = "Okay, but let's start small... Well, to summarize: every month you will need to bring into our home " + FindRussianMoneyString(MOD_SKILL_ENEMY_RATE*3*10000) + ".";
			link.l1 = "Whatever you say, Isabella. Everything is for you! So, what's our third principle?";
			link.l1.go = "NewLife_firstTime_6";
		break;
		case "NewLife_firstTime_6":
			dialog.text = "The third principle is your promise to quit privateering. Provide for your family in another way, no need to sink ships and capture cities - the Lord will not forgive us for this...";
			link.l1 = "Well, I remember my promises perfectly. I agree with this scenario, dear.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NewLife";
			UnlockAchievement("Isabella_quest", 3);
			AddDialogExitQuest("Romantic_afterFirstTime");
		break;
//************************************ новая жизнь бывшего корсара ********************************
		case "NewLife_hello":
			iDay = GetQuestPastDayParam("RomanticQuest");
			dialog.text = LinkRandPhrase("Hello, dear!", "Greetings to my husband.", "Glad to see my spouse.");
			link.l1 = RandPhraseSimple("Hello, Isabella!", "Hello, my dear...");
			link.l1.go = "NewLife";
			if (iDay > 40)
			{
				dialog.text = RandPhraseSimple("Hello dear! And immediately explain to me, please, where you were " + FindRussianDaysString(iDay) + "?", "Greetings to my husband, who was carried unknown where " + FindRussianDaysString(iDay) + ". Can you tell me, dear?");
				link.l1 = RandPhraseSimple("Isabella, darling, I've been squandering all this time on business.", "Darling, it all came together somehow...");
				link.l1.go = "NewLife_hello_1";
			}
			if (GetQuestPastDayParam("RomanticQuest") > 3 && pchar.RomanticQuest == "OpenTheDoosOfHouse")
			{
				dialog.text = "Hello, dear husband. I only opened the door for you because Cousin Rosita asked me to.";
				link.l1 = "Isabella, I understand everything, but you also understand me - I'm a sailor!";
				link.l1.go = "NewLife_hello_2";
			}
		break;
		case "NewLife_hello_1":
			dialog.text = "Listen, of course, I understand that you are a captain and your job is to sail the sea. But understand me, too - I'm not going to stay at home alone for several months in a row! And keep in mind that if you are not at home for so long, then I will not open the door for you again!";
			link.l1 = RandPhraseSimple("Isabella, I understand... I'm sorry that I had to leave you alone for a long time.", "I'm sorry that you had to stay alone for a long time, I understand everything...");
			link.l1.go = "NewLife";
			SaveCurrentQuestDateParam("RomanticQuest"); //обновим дату, от которой считаем отсутствие
			LAi_CharacterPlaySound(npchar, "Gr_Isabella_3");
		break;
		case "NewLife_hello_2":
			dialog.text = "I want to understand only one thing - the interests of my family. If you think you can come here from time to time, you are deeply mistaken. We should have a family, not a farce.";
			link.l1 = "Okay, Isabella, I will try not to leave you for a long time...";
			link.l1.go = "NewLife";
			SaveCurrentQuestDateParam("RomanticQuest"); //обновим дату, от которой считаем отсутствие
			LAi_CharacterPlaySound(npchar, "Gr_Isabella_3");
		break;
		//======================== типовое меню ==========================
		case "NewLife":
			//проверяем, как там с финансами у нас
			iMoney = IsabellaCheckBudgetMoney();
			if (iMoney > 0)
			{
				dialog.text = NPCStringReactionRepeat("Dear, we have a problem - we are in debt, like in silks. It is necessary to add " + FindRussianMoneyString(iMoney) + " and thereby resolve tax problems.",
					"This is the second time today that I have informed you about financial problems. We owe " + FindRussianMoneyString(iMoney) + ".",
					"For the third time today, I remind you of our debts that make up " + FindRussianMoneyString(iMoney) + ".",
					"Once again reminding about a huge problem - debts in the amount of " + FindRussianMoneyString(iMoney) + ".", "block", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Carramba!! How did I launch this case?!", "Wow, how everything is launched in family affairs ..."),
					"The second time? That's the problem...",
					"The third time already?! Yeah...",
					"I remember Isabella...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay";
				break;
			}
			//--> проверяем статистику на пиратство
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.GrabbingTown") && pchar.RomanticQuest.Cheking != "Ok")
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.GrabbingTown)*150) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = RandPhraseSimple("Listen, all they're saying is that you've looted some city. Is it true?", "Listen, there are rumors that you've gone back to your old ways and looted some city. Is it true?");
					link.l1 = LinkRandPhrase("Come on, honey, that's slander!", "Honey, I didn't do anything like that.", "No, honey, that's not true, I promised!");
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("GrabbingTown");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.TakeTown") && pchar.RomanticQuest.Cheking != "Ok")
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.TakeTown)*140) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = RandPhraseSimple("Listen, there are rumors that you have captured some city. Is it true?", "Listen, there are rumors that you've gone back to your old ways and captured some city. Is it true?");
					link.l1 = LinkRandPhrase("Come on, honey, that's slander!", "Honey, I didn't do anything like that.", "No, honey, that's not true, I promised!");
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("TakeTown");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.KillFort") && pchar.RomanticQuest.Cheking != "Ok")
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.KillFort)*130) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = RandPhraseSimple("Listen, I've heard rumors here that you've captured some kind of fort. Is it true?", "Listen, there are rumors that you've gone back to your old ways and captured some fort. Is it true?");
					link.l1 = LinkRandPhrase("Come on, honey, that's slander!", "Honey, I didn't do anything like that.", "No, honey, that's not true, I promised!");
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("KillFort");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.AbordShip") && pchar.RomanticQuest.Cheking != "Ok")
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.AbordShip)*70) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = RandPhraseSimple("I have heard terrible rumors that you are boarding ships. Is it true?", "Listen, there are rumors that you're up to your old tricks again - boarding and looting ships. Is it true?");
					link.l1 = LinkRandPhrase("Come on, honey, that's slander!", "Honey, I didn't do anything like that.", "No, honey, that's not true, I promised!");
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("AbordShip");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.KillShip") && pchar.RomanticQuest.Cheking != "Ok")
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.KillShip)*50) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = RandPhraseSimple("Listen, people are saying that you sink ships. Is it true?", "Listen, there are rumors that you're back to your old ways - sinking ships. Is it true?");
					link.l1 = LinkRandPhrase("Come on, honey, that's slander!", "Honey, I didn't do anything like that.", "No, honey, that's not true, I promised!");
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("KillShip");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			//<-- проверяем статистику на пиратство
			//        -------  ОСНОВНОЕ МЕНЮ  ----------
			dialog.text = LinkRandPhrase("Dear, I'm listening to you...", "What does my dear husband want?", "Senor " + pchar.lastname + "your wife listens to you in the most attentive way...");
			link.l1 = "Just like that, just to talk... I missed you, you know...";
			link.l1.go = "NewLife_JustTalk";
			link.l2 = "Let's see what state our family budget is in...";
			link.l2.go = "NewLife_Budget";
			link.l3 = "Honey, I brought you a gift.";
			link.l3.go = "NewLife_Present";
			link.l4 = "Listen, honey, about marital duty...";
			link.l4.go = "NewLife_Sex";
			link.l5 = "I want to sleep, I just don't have the strength...";
			link.l5.go = "NewLife_Sleep";
		break;
		//=========================== Бюджет =================================
		case "NewLife_Budget":
			iMoney = IsabellaCheckBudgetMoney();
			if (iMoney > -(MOD_SKILL_ENEMY_RATE*3*10000)) //деньги на исходе
			{
				if (iMoney == 0)
				{
					dialog.text = RandPhraseSimple("There are no debts yet, but the money is over, dear...", "Unless there are no debts and the bailiff is not banging on the door... And so the money ran out completely.");
				}
				else
				{
					dialog.text = "There are no debts yet, but the money is running out. I still have " + FindRussianMoneyString(-iMoney) + ".";
					link.l1 = RandPhraseSimple("Well, the time will come - we will decide...", "I'm not up to it now, spend what you have...");
					link.l1.go = "NewLife";
				}
				link.l2 = RandPhraseSimple("Well, then we'll give you some piastres, dear!", "We need to replenish the budget urgently, let's do it!");
				link.l2.go = "NewLife_Budget_Add";
				LAi_CharacterPlaySound(npchar, "Gr_Isabella_4");
			}
			else //профицит
			{
				dialog.text = RandPhraseSimple("No problem, dear, there is still enough money - " + FindRussianMoneyString(-iMoney) + "I still have it.", "It's okay, honey, there is enough money in our budget - " + FindRussianMoneyString(-iMoney) + ".");
				link.l1 = RandPhraseSimple("Well, that's good.", "Fine, dear, very good!");
				link.l1.go = "NewLife";
				link.l2 = "I also want to leave you money so that you don't need anything.";
				link.l2.go = "NewLife_Budget_Add";
			}
		break;
		case "NewLife_Budget_Add":
            dialog.text = NPCStringReactionRepeat("Okay, dear. How much money do you want to leave me?", "Why do you want to leave me something for the second time in a day - I don't understand... So how much do you want to keep?", "Are you kidding me? For the third time in a day, you want to give me money! Can't everything be solved right away?", "That's it, I'm tired of you - you're an unbearable bore! I won't talk to you anymore!", "repeat", 10, npchar, Dialog.CurrentNode);
			if (sti(pchar.money) >= 50000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l1 = HeroStringReactionRepeat("50 thousand.", "Hmm, I want to keep 50000.", "Uh... I want to leave you 50,000.", "...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_50";
			}
			if (sti(pchar.money) >= 100000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l2 = HeroStringReactionRepeat("100 thousand.", "100 thousand...", "100 thousand...", "...", npchar, Dialog.CurrentNode);
				link.l2.go = "NewLife_Budget_100";
			}
			if (sti(pchar.money) >= 200000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l3 = HeroStringReactionRepeat("200 thousand.", "200 thousand...", "200 thousand...", "...", npchar, Dialog.CurrentNode);
				link.l3.go = "NewLife_Budget_200";
			}
			if (sti(pchar.money) >= 500000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l4 = HeroStringReactionRepeat("500 thousand.", "500 thousand...", "500 thousand...", "...", npchar, Dialog.CurrentNode);
				link.l4.go = "NewLife_Budget_500";
			}
			link.l5 = HeroStringReactionRepeat("Ahem... Nothing yet, Isabella... Money is tight...", "It just so happened, dear... I'm sorry, but there's no money.", "It didn't work out right away, Isabella... And there is no money.", "Isabella, how is that?", npchar, Dialog.CurrentNode);
			link.l5.go = "NewLife_Budget_No";
		break;
		case "NewLife_Budget_50":
			dialog.text = "Okay, " + pchar.name + "Thank you.";
			link.l1 = "This is my duty, Isabella...";
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(50000);
		break;
		case "NewLife_Budget_100":
			dialog.text = "Okay, honey. 100,000 is a lot, thank you.";
			link.l1 = "You're welcome, honey...";
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(100000);
		break;
		case "NewLife_Budget_200":
			dialog.text = "Very good, dear. 200,000 is good for the family budget.";
			link.l1 = "I'm glad you're happy, Isabella...";
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(200000);
		break;
		case "NewLife_Budget_500":
			dialog.text = "So much! Where did you get so much money?";
			link.l1 = "Earned, where else?";
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(500000);
		break;
		case "NewLife_Budget_No":
            dialog.text = LinkRandPhrase("Well, then why did you suggest it?", "Then why are you talking about it?" , "Then why talk about it?");
			link.l1 = LinkRandPhrase("I was wrong, dear, I'm sorry...", "Sorry, dear, something happened to my memory...", "Something is not very good with my head...");
			link.l1.go = "NewLife";
		break;
		//заплатить долги и понулить счётчик бюджета
		case "NewLife_Budget_Pay":
			iMoney = IsabellaCheckBudgetMoney();
			dialog.text = NPCStringReactionRepeat("That's right, captain " + pchar.name + ", you've pretty much started this thing! So please pay off the debt!",
				"You should have found the money to pay off the debt!",
				"Captain, I'm asking you again to pay off our tax arrears!",
				"Captain, I'm tired of repeating the same thing. I keep talking and talking, but there are still a lot of financial problems there. I'll tell you what, hubby: I can handle the problems myself! Well, I don't want to see you!", "quest", 30, npchar, Dialog.CurrentNode);
			if (sti(pchar.money) >= iMoney)
			{
				link.l1 = HeroStringReactionRepeat("Okay, honey, I'm ready to pay off the debt.", "Isabella, dear, I remember everything perfectly. I have found the money and I am ready to close the debts.", "Isabella, right now...", "You see, Isabella, right now I don't have any money...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay_2";
				link.l2 = "Listen, darling, I don't have it now";
				link.l2.go = "NewLife_Budget_Pay_1";
			}
			else
			{
				link.l1 = HeroStringReactionRepeat(".. " + FindRussianMoneyString(iMoney) + "...", "I should have, but I didn't find it...", "Isabella, I don't have money now!", "That's how it is?", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay_1";
			}
		break;
		case "NewLife_Budget_Pay_1":
			dialog.text = RandPhraseSimple("So go and find it! I'm not going to get into debt because of you!", "Listen to me, hubby! I do not want a bailiff to come to my house every other day and demand payment of debts! Find the money, it's your direct responsibility!");
			link.l1 = RandPhraseSimple("Okay, Isabella, whatever you say...", "I get it, Isabella, I'll try...");
			link.l1.go = "NewLife_exit";
		break;
		case "NewLife_Budget_Pay_2":
            dialog.text = RandPhraseSimple("Well, that's great! I am very glad that my husband is a responsible person.", "Fine, dear! You are a real man...");
			link.l1 = RandPhraseSimple("Yeah...", "Heh, of course!");
			link.l1.go = "NewLife";
			iMoney = IsabellaCheckBudgetMoney();
			AddMoneyToCharacter(pchar, -iMoney);
			IsabellaNullBudget();
		break;
		//=========================== Изабелла узнала, что ГГ опять пиратствует =================================
		case "NewLife_KnowPirates":
			pchar.RomanticQuest.Cheking = "Ok"; //флаг "don't check for piracy anymore" в этот раз
			if (rand(12) < GetCharacterSPECIAL(pchar, "Charisma")) //поверила, дура :)
			{
				dialog.text = LinkRandPhrase("Hmm, I believe you, " + pchar.name + "...", "Well, I'd rather believe you than some rumors!", "I'd like to believe, " + pchar.name + "to you, not to speculation...");
				link.l1 = RandPhraseSimple("Well, that's good, dear.", "How great! We quickly decided - and the misunderstanding is over...");
				link.l1.go = "NewLife";
			}
			else //не поверила, и правильно сделала
			{
				dialog.text = NPCStringReactionRepeat("You know, honey, I tend to believe these rumors and speculations. However, I can't prove anything for sure, so let this be your first warning.",
					"I guess I won't believe you-they talk about it too much... Consider this a second warning.",
					"Hmm, listen, I don't understand, do you take me for a fool? Everyone is talking about it, but he refuses! It looks like you're not keeping your word. In general, this was the last warning, " + pchar.name + ".",
					"That's it, captain " + pchar.name + ", there is no trust in you anymore. You've been fooling me! I don't want to talk to you!", "quest", 80, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Okay, honey. I believe that I have been warned once.",
					"Good, dear, let this be warning number two.",
					"Mmm, okay, Isabella, let this be the last warning.",
					"Oh, Isabella...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife";
			}
		break;
		//=========================== Секс =================================
		case "NewLife_Sex":
			if (GetQuestPastMonthParam("RomanticQuest") > 2 && GetNpcQuestPastDayParam(npchar, "sex") != 0)
			{
				dialog.text = "What's a sailor, have you been sailing too long?";
				link.l1 = "Well, there is such a thing...";
				link.l1.go = "NewLife_Sex_1";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("What are you talking about?",
					"Ah, I can guess what you're talking about...",
					"Debt? And what do I owe you?",
					"Hmm, I don't understand...", "cycle", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Yes, it's all about the same thing, Isabella, about love...",
					"It's about this, dear - about love...",
					"I'm talking about the duty of love, dear...",
					"Isabella, I'm talking about love, dear...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Sex_5";
			}
		break;
		case "NewLife_Sex_1":
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //запоминаем секс
			dialog.text = "If I were you, dear, I wouldn't leave home for so long...";
			link.l1 = "Why is that?";
			link.l1.go = "NewLife_Sex_2";
		break;
		case "NewLife_Sex_2":
			dialog.text = "Because your wife is a beautiful woman, if you haven't noticed it before. And there are more than one women living in San Juan, there are many more interesting caballeros...";
			link.l1 = "Hey, the devil!! Isabella, what are you talking about?!";
			link.l1.go = "NewLife_Sex_3";
		break;
		case "NewLife_Sex_3":
			dialog.text = "That's what I'm saying, so that you come home more often, dear!";
			link.l1 = "Okay, Isabella, I get you... Let's not fight, honey...";
			link.l1.go = "NewLife_Sex_4";
		break;
		case "NewLife_Sex_4":
			if (rand(6) < 5)
			{
				dialog.text = "All right... I'm going to the bedroom...";
				link.l1 = "I'm coming for you!";
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = "Okay, let's not quarrel, honey. But I have a migraine today, so it's not going to work. I'm sorry...";
				link.l1 = "Oh, what a bad time!..";
				link.l1.go = "NewLife_exit";
			}
		break;

		case "NewLife_Sex_Late":
			dialog.text = "You know what, dear, I'm not going to wait for you here forever in full combat readiness... You missed your chance!";
			link.l1 = "Isabella, how come...?";
			link.l1.go = "NewLife_Sex_Late_1";
		break;
		case "NewLife_Sex_Late_1":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto1", "Romantic_TalkInChurch_end", 3.5);
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NewLife_Sex_5":
			if (GetNpcQuestPastDayParam(npchar, "sex") > 3)
			{
				dialog.text = NPCStringReactionRepeat("Mm-hmm... I like such conversations...",
					"About love? Well, go on, darling...",
					"Love, this is interesting... So what is it...?",
					"Ah, this love... I sometimes do such stupid things!..", "block", 60, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Isabella, I'm burning with passion!!",
					"Isabella, I long to share a bed with you!",
					"Isabella, the desire to possess you overwhelms me...",
					"What kind of nonsense is this, Isabella?! Let's go to the bedroom quickly, dear?", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("NewLife_Sex_10", "NewLife_Sex_11", "NewLife_Sex_12", "NewLife_Sex_13", npchar, Dialog.CurrentNode);
			}
			else //слишком часто, не прокатит
			{
				dialog.text = LinkRandPhrase("You can't talk about love too often, dear. So I'm sorry, but it won't work...", "No, dear, frequent conversations about love are harmful to the soul and body, that's what the padre says...", "Oh, honey, I don't want to talk about this topic too often, don't tire me, please. In a few days, dear...");
				link.l1 = RandPhraseSimple("Um... Ahem... It's a pity...", "Yeah, I'm disappointed...");
				link.l1.go = "NewLife_exit";
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //запоминаем секс
		break;
		case "NewLife_Sex_10":
			dialog.text = "Then I'm waiting for you in the bedroom, dear!";
			link.l1 = "Isabella, I'm following...";
			link.l1.go = "NewLife_GoSex";
		break;
		case "NewLife_Sex_11":
			if (rand(10) < 8)
			{
				dialog.text = "Split the bed? Well, all right. I'm going to the bedroom...";
				link.l1 = "Oh, Isabella...";
				link.l1.go = "NewLife_GoSex";
			}
			else //не свезло
			{
				dialog.text = LinkRandPhrase("I have a headache, dear, not today...", "I don't feel well today, dear. Not now...", "Honey, let's put it off... I can't -I feel bad.");
				link.l1 = RandPhraseSimple("Oh, what a bad time!..", "Damn!.. I'm sorry, Isabella, it came out...");
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_Sex_12":
			if (rand(10) < 5)
			{
				dialog.text = "Desire... Mm-hmm, all right. I'm waiting for you in the bedroom, dear...";
				link.l1 = "Isabella, I'll be right there!..";
				link.l1.go = "NewLife_GoSex";
			}
			else //не свезло
			{
				dialog.text = LinkRandPhrase("I have a headache, dear, not today...", "I don't feel well today, dear. Not now...", "Honey, let's put it off... I can't -I feel bad.");
				link.l1 = RandPhraseSimple("Oh, what a bad time!..", "Damn!.. I'm sorry, Isabella, it came out...");
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_Sex_13":
			if (rand(10) < 2)
			{
				dialog.text = "Dear, you are impudent!.. Well, okay, I persuaded...";
				link.l1 = "Isabella...";
				link.l1.go = "NewLife_GoSex";
			}
			else //не свезло
			{
				dialog.text = "We're not going anywhere! And from now on, do not allow yourself vulgar phrases!";
				link.l1 = "Okay, Isabella, I'm sorry...";
				link.l1.go = "NewLife_exit";
			}
		break;
		//идём в спальню
		case "NewLife_GoSex":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //запомнить секс
			Pchar.quest.Romantic_Sex.win_condition.l1 = "location";
			Pchar.quest.Romantic_Sex.win_condition.l1.location = "SanJuan_houseS1Bedroom";
			Pchar.quest.Romantic_Sex.win_condition = "Romantic_Sex";
			SetTimerCondition("Romantic_IsabellaBackToHall", 0, 0, 1, false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SanJuan_houseS1Bedroom", "goto", "goto6", "Romantic_TalkInChurch_end", 20.0);
			DialogExit();
		break;
		//после секса
		case "NewLife_afterSex":
			dialog.text = NPCStringReactionRepeat("Mm-hmm... Honey, it was... Great!",
				"Well, how are you doing, dear? Is everything okay?",
				"You're not in good shape today...",
				"Ah, love... It's fine...", "block", 30, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thank you, dear...",
				"Fine, honey, you were just great!",
				"Hmm... I'm sorry, dear, it just happened...",
				"I totally agree with you, dear.", npchar, Dialog.CurrentNode);
			link.l1.go = "NewLife_afterSex_1";
		break;
		case "NewLife_afterSex_1":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto2", "Romantic_TalkInChurch_end", 20.0);
			Pchar.quest.Romantic_IsabellaBackToHall.over = "yes";
			DialogExit();
		break;
		//=========================== Сон =================================
		case "NewLife_Sleep":
			dialog.text = "When should I wake you up, dear?";
			if(!isDay())
			{
				link.l1 = "In the morning, be kind...";
				link.l1.go = "NewLife_Sleep_day";
			}
			else
			{
				link.l1 = "I need to get up at night, Isabella.";
				link.l1.go = "NewLife_Sleep_night";
				link.l2 = "I want to sleep it off. Wake me up the next morning.";
				link.l2.go = "NewLife_Sleep_day";
			}
		break;
		case "NewLife_Sleep_day":
			dialog.text = "Okay, I'll wake you up in the morning.";
			link.l1 = "Well, great. Then I went to the bedroom...";
			link.l1.go = "room_day_wait";
			link.l2 = "You know, I've changed my mind. I won't sleep yet.";
			link.l2.go = "NewLife_exit";
		break;
		case "NewLife_Sleep_night":
			dialog.text = "Okay, I'll wake you up after midnight.";
			link.l1 = "Great, honey. Then I went to the bedroom...";
			link.l1.go = "room_night_wait";
			link.l2 = "You know, I've changed my mind. I'd rather spend this time on my feet.";
			link.l2.go = "NewLife_exit";
		break;
		case "room_day_wait":
			DialogExit();
			NextDiag.TempNode = "NewLife_hello";
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate("wait_day");
			AddDialogExitQuest("sleep_in_home");
		break;
		case "room_night_wait":
			DialogExit();
			NextDiag.TempNode = "NewLife_hello";
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate("wait_night");
			AddDialogExitQuest("sleep_in_home");
		break;
		//=========================== Просто разговор =================================
		case "NewLife_JustTalk":
			if (CheckAttribute(pchar, "RomanticQuest.Atilla"))
			{
				switch (pchar.RomanticQuest.Atilla)
				{
					case "YouAreBaster":
						dialog.text = "Listen, I heard that you did something wrong to your friend Attila. They say that you gave him very little money, but I know how much he has done for us... I'm just shocked!";
						link.l1 = "Darling, it's all over now, there's nothing to stir it up...";
						link.l1.go = "NewLife_exit";
					break;
					case "YouAreNormal":
						dialog.text = "Dear, I heard that you thanked your friend Atilla. This is a worthy act, I am glad that my husband is a real man, a man of honor!";
						link.l1 = "Isabella, could it be otherwise?";
						link.l1.go = "NewLife_exit";
					break;
					case "YouAreGood":
						dialog.text = "Dear, you didn't tell me anything, but I happened to find out that you gave your friend Atilla a very large sum. I guess it's a thank you for all that he's done for us. Darling, you are the best person in the world! I was convinced of this once again.";
						link.l1 = "Isabella, come on... It's not worth it, I just returned the debt...";
						link.l1.go = "NewLife_exit";
					break;
				}
				DeleteAttribute(pchar, "RomanticQuest.Atilla");
				break;
			}
			switch (rand(1))
			{
				case 0:
					dialog.text = LinkRandPhrase("Oh, dear, I am so pleased with your attention...", pchar.name + ", you are a real knight...", "Oh, my God, what a blessing that you sent me as a husband " + GetMainCharacterNameGen() + "...");
					link.l1 = RandPhraseSimple("I'm lucky to have you too, dear...", "You know, Isabella, I often think: it's good that we decided to link our destinies...");
					link.l1.go = "NewLife_exit";
				break;
				case 1:
					dialog.text = LinkRandPhrase("Dear, do you know, the governor of the city was interested in how we were doing.", "The governor asked me the other day how you were doing, dear.", "Yesterday I met the governor on the street and we talked. He was wondering how you were doing.");
					link.l1 = RandPhraseSimple("It's all right, tell him so next time.", "I wouldn't say I'm flattered by the governor's attention to you...");
					link.l1.go = "NewLife_exit";
				break;
			}
		break;
		//=========================== Подарки =================================
		case "NewLife_Present":
			dialog.text = RandPhraseSimple("And what do you want to give me, dear?", "Come on, tell me quickly, what are you going to give me?");
			iTemp = 1;
			for (i=18; i>=1; i--)
			{
				if (i==8 || i==9) continue;
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = XI_ConvertString("jewelry"+i+"Gen") + ".";
					link.(sTemp).go = "NewLife_jewelry_"+i;
					iTemp++;
				}
			}
			if (iTemp == 1)
			{
				dialog.text = NPCStringReactionRepeat("And what do you want to give me, dear?",
					"Do you want to give me something again? Hmm, so what is it?",
					pchar.name + ", are you kidding me with these gifts? What is it this time?",
					"That's it, you've got me, you dumbass! I'm angry with you and I don't want to talk to you!", "repeat", 20, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Nothing like that...",
					"I don't have anything worthy of you, I'm sorry...",
					"Isabella, I haven't found anything for you again, I'm sorry...",
					"Isabella, I'm sorry!..", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_jewelry_1":
			dialog.text = LinkRandPhrase("Thank you, dear, you are very kind. I really like sapphires.", "Oh, how it plays in the sun! Thank you, dear..." , "A magnificent stone! Thank you, dear...");
			link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry1");
		break;
		case "NewLife_jewelry_2":
			if (rand(4)==1)
			{
				dialog.text = "Ah, diamond... I'm just going crazy! Honey, let's go upstairs!";
				link.l1 = "With pleasure, honey.";
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = LinkRandPhrase("Thank you, dear, you are very kind. I really like diamonds.", "Oh, how he plays in the sun! Thank you, darling..." , "A magnificent stone! Thank you, dear...");
				link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry2");
		break;
		case "NewLife_jewelry_3":
			if (rand(10)==1)
			{
				dialog.text = "Oh, it's a ruby! I love these blood-red stones so much! Dear, you made me very happy, and now I want to go upstairs with you...";
				link.l1 = "And I want it too, honey...";
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = LinkRandPhrase("Thank you, dear, you are very kind. I really like rubies.", "Oh, how he plays in the sun! Thank you, darling..." , "A magnificent stone! Thank you, dear...");
				link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry3");
		break;
		case "NewLife_jewelry_4":
			if (rand(3)==1)
			{
				dialog.text = "Oh, this is my favorite stone - an emerald! You spoil me, honey... Darling, I want to go upstairs with you...";
				link.l1 = "And I want it too, honey...";
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = LinkRandPhrase("Thank you, dear, you are very kind. I really like emeralds.", "Oh, how he plays in the sun! Thank you, darling..." , "A magnificent stone! Thank you, dear...");
				link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry4");
		break;
		case "NewLife_jewelry_5":
			dialog.text = LinkRandPhrase("Mmm, gold! A very good gift, thank you, dear.", "Oh, and what a shape it is, this nugget! Thank you, dear." , "A magnificent nugget! Thank you, dear...");
			link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the richest woman in the Caribbean!", "Everything is for you, honey...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry5");
		break;
		case "NewLife_jewelry_6":
			dialog.text = LinkRandPhrase("Thank you, dear, you are very kind. Jewelry with sapphires suits me very well.", "Oh, how well a sapphire looks in a silver frame! Thank you, darling..." , "A magnificent ring! Thank you, dear...");
			link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry6");
		break;
		case "NewLife_jewelry_7":
			if (rand(2)==1)
			{
				dialog.text = "Ah, the ring with my favorite emerald! You spoil me, honey... Darling, I want to go upstairs with you...";
				link.l1 = "And I want it too, honey...";
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = LinkRandPhrase("Thank you, dear, you are very kind. Rings with emeralds really suit me...", "Oh, how he plays in the sun in a gold frame! Thank you, dear..." , "A magnificent stone in a decent setting! Thank you, dear...");
				link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry7");
		break;
		case "NewLife_jewelry_10":
			dialog.text = LinkRandPhrase("Thank you, dear, you are very kind. Jewelry with sapphires suits me very well.", "Oh, how well a sapphire looks in a gold frame! Thank you, darling..." , "A magnificent ring! Thank you, dear...");
			link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry10");
		break;
		case "NewLife_jewelry_11":
			dialog.text = LinkRandPhrase("Thank you, dear, you are very kind. Such a large pearl looks amazing!", "Pearls... The fisheries on the pearl coast are working properly. Thank you, dear." , "A magnificent pearl! Thank you, dear...");
			link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry11");
		break;
		case "NewLife_jewelry_12":
			dialog.text = LinkRandPhrase("Thank you, dear, you are very kind...", "Pearls... The crafts on the pearl coast are working properly ..." , "Magnificent pearl! Thank you, dear...");
			link.l1 = RandPhraseSimple("Ahem...", "Um...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry12");
		break;
		case "NewLife_jewelry_13":
			dialog.text = LinkRandPhrase("Oh, what an interesting trinket, this cameo... Thank you dear.", "Interesting little thing, honey. Thank you..." , "Nice decoration! Thank you, dear...");
			link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry13");
		break;
		case "NewLife_jewelry_14":
			if (rand(1)==1)
			{
				dialog.text = "Ah, honey, this brooch is worthy of a queen... I want to go upstairs with you immediately...";
				link.l1 = "And I want it too...";
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = LinkRandPhrase("Thank you, dear, you are very kind. This gold brooch is very beautiful...", "Oh, how good it looks in the bright light! Thank you, dear..." , "Magnificent stones in a decent setting! Thank you, dear...");
				link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry14");
		break;
		case "NewLife_jewelry_15":
			if (rand(1)==1)
			{
				dialog.text = "Oh, honey, those pendants... I'm just crazy about you and I want to go upstairs with you immediately...";
				link.l1 = "I don't mind, dear.";
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = LinkRandPhrase("Thank you, dear, you are very kind. This emerald pendant suits me very well...", "Oh, how emeralds look good in bright light! Thank you, dear ..." , "Magnificent stones in a decent setting! Thank you, dear...");
				link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry15");
		break;
		case "NewLife_jewelry_16":
			dialog.text = LinkRandPhrase("Dear, keep this necklace for yourself, I won't be offended...", "Hmm, and do you think I'll wear this?" , "What a taste you have, dear. You're just a dork if you're suggesting I wear this!");
			link.l1 = RandPhraseSimple("Yes? Ah, well...", "I made a mistake...");
			link.l1.go = "NewLife_exit";
		break;
		case "NewLife_jewelry_17":
			dialog.text = LinkRandPhrase("Ah, silver! Well, I'll take it, it will be useful in the household ...", "Silver? Well, goodbye..." , "A silver nugget? Hmm, silver is valued in large quantities. But okay, let's take it...");
			link.l1 = RandPhraseSimple("You're welcome, dear...", "I want you to be the richest woman in the Caribbean!");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry17");
		break;
		case "NewLife_jewelry_18":
			if (rand(8)==1)
			{
				dialog.text = "Emeralds and rubies are my favorite stones. This ring is just great, you spoil me, honey... Darling, I want to go upstairs with you...";
				link.l1 = "And I want it too...";
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = LinkRandPhrase("Thank you, dear, you are very kind, this ruby ring is very beautiful...", "A ruby in gold looks very good! Thank you, dear..." , "A magnificent stone in a decent setting! Thank you, dear...");
				link.l1 = LinkRandPhrase("You're welcome, honey...", "I want you to be the most beautiful woman in the world!", "Everything is for you, honey...");
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry18");
		break;
		//выход
		case "NewLife_exit":
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto"+(rand(3)+1), "Romantic_TalkInChurch_end", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		//==> попытки дать денег
		case "AngryRepeat_Budget_Add":
            dialog.text = RandPhraseSimple("I don't want to talk to such a bore! Unless a silver and gold ring with sapphires will melt my heart...", "I don't want to talk, I'm offended by you, a bore and a miser! Actually, I want a silver and gold ring with sapphires...");
			link.l1 = "Oh, Isabella...";
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Well, okay, hubby, I agree to communicate with you. But don't be such a miser! And moreover, do not promise anything when there is no money!";
        			link.l1 = "Okay, Isabella, I'll try...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
				else //примирение через кольцо с сапфиром
				{
					if (CheckCharacterItem(pchar, "jewelry6") && CheckCharacterItem(pchar, "jewelry10"))
					{
         				dialog.text = "Oh, you brought me what I wanted - a gold and silver sapphire ring! Hmm, you know how to please me... Well, I'm ready to talk to you...";
        				link.l1 = "Ugh-f-f, great!";
        				link.l1.go = NextDiag.TempNode;
        				CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry6");
						TakeItemFromCharacter(pchar, "jewelry10");
					}
				}
            }
    	break;
		//==> вовремя не рассчитался с долгами
		case "AngryRepeat_Budget_Pay":
            dialog.text = RandPhraseSimple("Listen, hubby, you are not able to provide for your wife's existence, I had to solve our financial problems myself. This is no good!", "Just think, I have to solve all the issues in the family myself! Your inability to provide for your family amazes me!");
			link.l1 = "Senora Isabella, it just so happened...";
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Well, I agree to reconciliation, but you need to pay off all the debt that has been formed!";
        			link.l1 = "Okay, Isabella, I'll do whatever you say.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
				else //примирение через изумруды
				{
					if (CheckCharacterItem(pchar, "jewelry4") && CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "jewelry15"))
					{
         				dialog.text = "You bastard! You brought me jewelry with emeralds... I love these stones, I like them so much!.. Well, I agree to reconciliation, but you need to pay off all the debts that have arisen!";
        				link.l1 = "Okay, Isabella, okay...";
        				link.l1.go = NextDiag.TempNode;
        				CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry4");
						TakeItemFromCharacter(pchar, "jewelry7");
						TakeItemFromCharacter(pchar, "jewelry15");
					}
				}
            }
    	break;
		//==> если попался на пиратстве
		case "AngryRepeat_KnowPirates":
            dialog.text = RandPhraseSimple("You broke your word to me before the wedding! I don't want to see you!", "You promised that privateering was over, but you didn't even think to stop shedding the blood of innocents!");
			link.l1 = "Isabella, I didn't want this to happen...";
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся 80 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "That's what, husband! I am ready for reconciliation, but you must keep your word from now on!";
        			link.l1 = "Okay, Isabella, I'll do whatever you say. There will be no more piracy, dear...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
					IsabellaSetCurrentState("All");
                }
				else //примирение через алмаз, рубины и большую жемчужину
				{
					if (CheckCharacterItem(pchar, "jewelry1") && CheckCharacterItem(pchar, "jewelry2") && CheckCharacterItem(pchar, "jewelry3") && CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry11"))
					{
         				dialog.text = "Oh, " + pchar.name + " you know how to make me calm... But you must keep your word and end the privateering!";
        				link.l1 = "Oh, Isabella, I'll let it be so. I can't live without you...";
        				link.l1.go = NextDiag.TempNode;
        				CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry1");
						TakeItemFromCharacter(pchar, "jewelry2");
						TakeItemFromCharacter(pchar, "jewelry3");
						TakeItemFromCharacter(pchar, "jewelry18");
						TakeItemFromCharacter(pchar, "jewelry11");
						IsabellaSetCurrentState("All");
					}
				}
			}
    	break;
		//==> если достал подарками
		case "AngryRepeat_Present":
            dialog.text = RandPhraseSimple("No, well, it's just impossible to live with such a person! And why was it necessary to give me non-existent gifts?! There are just no words!!", "I don't want to talk to such an impenetrable dumbass and impudent! It's necessary to give your wife non-existent gifts! Well, thank you, dear!..");
			link.l1 = RandPhraseSimple("Isabella, you're being unfair to me...", "Something came over me, Isabella. I didn't mean to...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся 20 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Well, I'm ready to make peace with you. But don't be such a dork and don't offer gifts if you don't have any!";
        			link.l1 = "Okay, honey, I won't do that anymore...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
				else //примирение через злато-серебро
				{
					if (CheckCharacterItem(pchar, "jewelry5") && CheckCharacterItem(pchar, "jewelry17"))
					{
						if (sti(pchar.items.jewelry5) >= 3 && sti(pchar.items.jewelry17) >=5)
						{
         					dialog.text = "Well, wow!.. You brought the only thing I really want right now- gold and silver bars... Well, I'm ready to resume communication. But just so that there are no repetitions of this bullying with gifts!!";
        					link.l1 = "Okay, Isabella, whatever you say...";
        					link.l1.go = NextDiag.TempNode;
        					CharacterDelAngry(npchar);
							TakeNItems(pchar, "jewelry5", -3);
							TakeNItems(pchar, "jewelry17", -5);
						}
					}
				}
			}
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
