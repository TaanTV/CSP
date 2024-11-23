
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
		if (rand(2) == 0 && GetNpcQuestPastDayWOInit(npchar, "questPrisonGun") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
				{
					dialog.text = RandPhraseSimple(RandPhraseSimple("Listen, I have an important matter for you. I hope you can help...", "Captain, would you be interested in some very lucrative offer?"), RandPhraseSimple("I was thinking that you could help us with a very important question.", "Captain, I have a delicate offer for you that may be beneficial for both of us."));
					link.l1 = "Explain, let's try to solve...";
					link.l1.go = "GiveTaskGun";
					npchar.quest.PrisonGun = "Target";
					SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
					break;
				}

			dialog.text = RandPhraseSimple("I am the commandant. What do you need here?", "What do you need? Why did you come to the prison?");
			link.l1 = "It's nothing special, I'm looking around the city, you know.";
			link.l1.go = "exit";
			link.l2 = "I want to talk business.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}
			}
			else
			{
				if(CheckAttribute(pchar, "questTemp.ReasonToFast") && !CheckAttribute(pchar, "questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}
			}

			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "I want to go inside the prison.";
				link.l4.go = "ForGoodMove";
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Listen, can you tell me what crime a prisoner named " + GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId)) + " is sitting here for?";
				link.l5.go = "KnowAboutPrisoner";
			}

			if(CheckAttribute(pchar, "GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar, "GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "I heard rumors that the former captain of the patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " is being held in your custody. Can I talk to him?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "I am " + GetFullName(pchar) + ", acting on behalf and on behalf of the governor " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". I need to talk to the former captain " + pchar.GenQuest.CaptainComission.Name + ".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}
			}

			if (CheckAttribute(pchar, "questTemp.PrisonGun") && pchar.questTemp.PrisonGun.Id == npchar.location)
			{
				link.l8 = "I'm here about your order for the supply of guns.";
				link.l8.go = "CheckGun";
			}

			if(CheckAttribute(pchar, "GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "I'm talking about your daughter...";
						link.l9.go = "EncGirl_1";
					}
				}
			}

			if(CheckAttribute(pchar, "UnexpectedInheritanceFort") && npchar.id == "FortFranceJailOff")
			{
				link.lUnexpectedInheritance = "Monsieur, I have a question for you, it may seem strange, but still...";
				link.lUnexpectedInheritance.go = "UnexpectedInheritance";
			}

			if(CheckAttribute(pchar, "LambriniPGGInPrison") && CheckAttribute(pchar, "LambriniPGGPlata") && npchar.id == "MaracaiboJailOff")
			{

				link.lLambriniPGGInPrison = "Senor, I took a participation in a recent raid on smugglers. I was told that the arrested are being held here. May I ask you to release a certain person? Under my responsibility, of course.";
				link.lLambriniPGGInPrison.go = "LambriniPGGInPrison";
			}
			NextDiag.TempNode = "First_officer";
		break;

		case "LambriniPGGInPrison":
			dialog.Text = "Who are we talking about?";
			Link.l1 = "I think her name is " + GetFullName(CharacterFromID(pchar.LambriniPGG))+".";
			Link.l1.go = "LambriniPGGInPrison_1";
		break;
		case "LambriniPGGInPrison_1":
			dialog.Text = ""+GetFullName(CharacterFromID(pchar.LambriniPGG))+"? Give me a minute, I'll review the list of prisoners.";
			Link.l1 = "Yes, of course, I'll wait.";
			Link.l1.go = "LambriniPGGInPrison_2";
		break;
		case "LambriniPGGInPrison_2":
			dialog.Text = "Hmm... "+GetFullName(CharacterFromID(pchar.LambriniPGG))+"... " + GetFullName(CharacterFromID(pchar.LambriniPGG))+"... Yeah, I found it. The owner of a contraband shipment of sandal. Her fine is 25,000 gold.";
			if (sti(pchar.money) >= 25000)
			{
				Link.l1 = "Here's your money.";
				Link.l1.go = "LambriniPGGInPrison_3";
			}
			Link.l2 = "Well, you have the prices... I need to think about it.";
			Link.l2.go = "LambriniPGGInPrison_3_1";
		break;
		case "LambriniPGGInPrison_3":
			AddMoneyToCharacter(pchar, -25000);
			DeleteAttribute(pchar, "LambriniPGGPlata")
			dialog.Text = "That's nice. She will be brought to you now.";
			Link.l1 = "";
			Link.l1.go = "LambriniPGGInPrison_4";
		break;
		case "LambriniPGGInPrison_3_1":
			dialog.Text = "If you decide to come, come. I just advise you to think faster, you never know what might happen here in a couple of days. This is your girlfriend, not mine.";
			Link.l1 = "";
			Link.l1.go = "exit";
		break;
		case "LambriniPGGInPrison_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = CharacterFromID(pchar.LambriniPGG);
			ChangeCharacterAddressGroup(sld, "Maracaibo_prison", "goto", "goto20");
			LAi_SetStayTypeNoGroup(sld);
			sld.talker = 10;
			sld.dialog.currentnode   = "LambriniPGG_2_1";
		break;

		case "UnexpectedInheritance":
			dialog.Text = "I'm listening To you.";
			Link.l1 = "The fact is that I became aware of the finds of unusual Indian idols on the territory of the fort. My employer is a collector and spares no expense on pagan trinkets, if you know what I mean.";
			Link.l1.go = "UnexpectedInheritance_1";
		break;
		case "UnexpectedInheritance_1":
			dialog.Text = "I understand you perfectly, Captain. In the metropolis, fashion has gone for all this exoticism and dealers are now paying mere pennies for finds, planning to cash in. Indeed, the soldiers who were doing the excavation work discovered something interesting.";
			Link.l1 = "My employer is not short of money. Will 12 thousand suit you?";
			Link.l1.go = "UnexpectedInheritance_2";
		break;
		case "UnexpectedInheritance_2":
			dialog.Text = "Is your employer Jewish? 25 thousand and not a peso less.";
			Link.l1 = "My employer is a Frenchman and a nobleman. 16. Is it a deal?";
			Link.l1.go = "UnexpectedInheritance_3";
		break;
		case "UnexpectedInheritance_3":
			dialog.Text = "A Frenchman? A nobleman? Well, I'll give it to a compatriot for 18 thousand miserable pesos.";
			if (sti(pchar.money) >= 18000)
			{
				Link.l1 = "Please, monsieur, your money. Goodbye!";
				Link.l1.go = "UnexpectedInheritance_4";
			}
			else
			{
				Link.l1 = "Hmm... I don't have that much with me. I'll look you up later.";
				Link.l1.go = "exit";
			}
		break;
		case "UnexpectedInheritance_4":
			dialog.Text = "Thank you, there were still some papers in the trunk, take them.";
			Log_Info("You have received a parchment with Latin text and half a map");
			Log_Info("You have received a ceremonial vessel");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("UnexpectedInheritance", "10");
			TakeNItems(pchar, "indian21", 1);
			DeleteAttribute(pchar, "UnexpectedInheritanceFort");
			pchar.quest.UnexpectedInheritanceTerks.win_condition.l1 = "location";
			pchar.quest.UnexpectedInheritanceTerks.win_condition.l1.location = "Terks_Grot";
			pchar.quest.UnexpectedInheritanceTerks.function = "UnexpectedInheritanceTerks";
			Link.l1 = "Curious...";
			Link.l1.go = "exit";
		break;

		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("The fact is that the guns of our fort are pretty worn out. The treasury, however, allocated money to replace them, but it is very expensive to purchase new ones now. So I thought that the ship's guns from the prizes you boarded could be very useful here.", "I need to replace the fort's gun battery. Money has been allocated for this, but, you know... I want something cheaper... Well, I hope you understand me.", "I received an order to replace the worn-out guns of the fort, but there is such a problem with them - I can't collect enough anywhere.");
			Link.l1 = "Hmm, but you can get more details - caliber, quantity... the price, finally.";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;

		case "GiveTaskGun_1":
			GetGunType();
			//iGunPrice = sti(pchar.questTemp.PrisonGun.Price);
			//iGunQty = pchar.questTemp.PrisonGun.Qty;
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			//sText = pchar.questTemp.PrisonGun.Text;
			dialog.Text = "I need "+ pchar.questTemp.PrisonGun.Text +", in the amount of exactly " + sti(pchar.questTemp.PrisonGun.Qty) + " pieces. I'm ready to pay " + FindRussianMoneyString(sti(pchar.questTemp.PrisonGun.Sum)) + ", it will come out by "+ sti(pchar.questTemp.PrisonGun.Price) +" piastres for each. What do you say? Yes, one more thing - I will accept the whole batch at once, but not earlier than in a month... The money is still on the way.";
			Link.l1 = RandPhraseSimple("No, Officer, I'm not interested in your offer... I'm sorry.", "It's tempting, of course, but I won't take it. Let me not explain my decision...");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("I will not hide it, the offer is interesting. Consider that we have already agreed.", "I think I'll take it. It's not difficult for me, but the benefits are obvious.");
			Link.l2.go = "GiveTaskGun_2";
		break;

		case "exit_gun":
			dialog.Text = "It's a pity... I'm sorry, Captain, I was counting on you... I hope this conversation will not go beyond the fort?";
			Link.l1 = "This reminder was unnecessary. Have a nice day.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First_officer";
		break;

		case "GiveTaskGun_2":
			dialog.Text = "That's it. I'm not limiting you in terms, but still, try not to stretch it for six months. And I hope you understand that this is a confidential matter?";
			Link.l1 = "I understand. See you later.";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First_officer";
		break;

		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "I told you not to come for at least a month!";
				Link.l1 = "Damn it! I lost time counting... Sorry, I'll come back later, as agreed.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First_officer";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Hmm... You know, more than six months have passed since our 'agreement' was signed. I have already purchased the guns. Or did you think that I would wait for you forever?";
				Link.l1 = "Damn it! What are you going to do with them now?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город

			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (rColony.id == "Panama") ok = true;
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Yes, are you ready to please me?";
				if (amount < 0)
				{
					Link.l1 = "No, I'm still studying. I just wanted to make sure our agreement is still in effect.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "Of course. The whole lot is in the hold - "+ sTemp +" pieces, as agreed.";
					Link.l1.go = "TakeGun";
				}
			}
			else
			{
				dialog.text = "I don't see something in your ship's port. Or are you suggesting dragging guns through the jungle? Dock at our harbor and come back.";
				link.l1 = "My ship is on the other side of the island. I'll bring him to the port now.";
				link.l1.go = "exit";
			}
		break;

		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
			dialog.Text = RandPhraseSimple("I'm really embarrassed, but I have to cancel our agreement.  A financial audit has come, and you know how scrupulous they are in these matters. Alas, but it won't work in any way, I'm sorry.", "Captain, here's the thing... in general, we were sent guns from the metropolis, and, of course, I was forced to buy them back. The prices are certainly extortionate, but... I'm sorry to let you down, but I'm very disappointed myself.");
			Link.l1 = "Damn it! What do you want me to do now?";
            Link.l1.go = "TakeGun_no";
			}
			else
			{
			dialog.Text = RandPhraseSimple("Great. I'll send a garrison outfit for unloading right away.", "Great. The soldiers will help your people with unloading.");
			Link.l1 = "Have you prepared the payment?";
            Link.l1.go = "TakeGun_1";
			}
		break;

		case "TakeGun_no":
			dialog.Text = "I don't know. Sell it at the shipyard, equip some merchant ship, sink it... I really don't know. And I beg you very much, do not spread about this matter.";
			Link.l1 = "What the hell?! I just don't have the words!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
			NextDiag.TempNode = "First_officer";
		break;

		case "TakeGun_late":
			dialog.Text = "I don't know. These are your difficulties. Sell it, throw it away, drown it - I don't care.";
			Link.l1 = "Oh, I was wasting my time...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("xia", "as"));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
			NextDiag.TempNode = "First_officer";
		break;

		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = makeint((sti(pchar.questTemp.PrisonGun.Sum) + 7500)/15000);
			dialog.Text = RandPhraseSimple("They brought me money for guns in credit chests. Please receive the "+ iTemp +" chests you are entitled to.", "But how else! But they brought me money in credit chests. According to our agreement, you are entitled to "+ iTemp +" chests. Here, please get it.");
			Link.l1 = "Chests means chests. Thank you. It's a pleasure doing business with you.";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "chest", iTemp);
			Log_Info("You got the credit chests");
			PlaySound("interface\important_item.wav");
			//AddMoneyToCharacter(pchar, makeint(pchar.questTemp.different.PrisonGun.Sum));
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;

		case "TakeGun_2":
			dialog.Text = "Thank you, you helped me a lot. And, please, let this deal remain between us.";
			Link.l1 = "Well, that goes without saying. Have a nice day.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("", "a"));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
			NextDiag.TempNode = "First_officer";
		break;

		case "EncGirl_1":
			dialog.text = "I'm listening to you carefully.";
			link.l1 = "I brought your fugitive.";
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = "Ah, Captain, thank you very much! How is she? Are you healthy, are you not injured? It's been a day since she ran away, the wretch. Do I wish her any harm? I'm going to get married... The groom is rich, young, and what is not good-looking, so do not drink water from the face. No! She tries everything in her own way-just like her mother, damn her...Yes, and she would not have been born if her mother had not run away with an enterprising blockhead at the time... Well, what to remember... Youth is naive, stupid... and cruel.";
			link.l1 = "Of course, you are the father and it's up to you, but I wouldn't rush happy wedding...";
			link.l1.go = "EncGirl_3";
		break;

		case "EncGirl_3":
			dialog.text = "";
			link.l1 = "Thank you. And hold her tight. Something tells me she won't stop there.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "I'm listening to you carefully, Captain.";
			link.l1 = "I want to report a criminal conspiracy between an officer of your garrison and pirates (sets out the circumstances of the case).";
			if(makeint(pchar.reputation) < 40)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
			{
				// вилка_А
				dialog.text = "Thank you, captain! I will immediately give the order to detain the scoundrel. However, you have spent a lot, and the municipal treasury, alas, is empty...";
				link.l1 = "Your Grace! I did it not for the money...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";

				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
			{
				// получена карта
				dialog.text = "Thank you, "+ GetSexPhrase("sir", "miss") +"! I will immediately give the order to detain the scoundrel.Just think about it! We wanted to reward him with a personalized weapon for his impeccable service. It's good that everything has cleared up, and there was no such embarrassment!";
				link.l1 = "Proud to serve justice...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied")
			{
				// патруль перебит
				dialog.text = ""+ GetSexPhrase("Sir", "Miss") +"! We have long suspected that this officer and the rabble surrounding him are dishonest, but it seems to me that you acted recklessly by dealing with them without witnesses.";
				link.l1 = "Your Grace! But I was protecting my life...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}
		break;

		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
			{
				// вилка_А
				dialog.text = "Captain, do you even understand what you're getting into?!! We've been trying to set this trap for over a month! And for the sake of entertainment, you disrupted the meeting of our patrol with the messenger " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " and also came to me to brag about it! Maybe now you can tell me how I should justify the government costs for organizing this operation?!!";
				link.l1 = "Your Honor! You refuse to see the essence of what is happening...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";

				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
			{
				// получена карта
				dialog.text = "Let's take a look at this map...Are you kidding me? Is this worn piece of parchment proof?";
				link.l1 = "Your Honor! You refuse to see the essence of what is happening...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied")
			{
				// патруль перебит
				dialog.text = "An original justification for the death of an entire patrol unit. Well, at least by coming here, you've saved us the trouble of looking for the killer.";
				link.l1 = "Your Grace! You refuse to see the essence of what is happening...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}
		break;

		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Nevertheless, I want your efforts to be rewarded. Here, take the map found in the belongings of the recently hanged sea robber. Perhaps, with the help of the Lord, you will indeed discover the treasures, although it is very doubtful...";
			link.l1 = "Thank you, you are very generous!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterReputation(pchar, 1);
			GiveItem2Character(pchar, "mapQuest");
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Commendable zeal. Take this blade as a reward, it's the least I can give you! Yes.. and keep this map for yourself. I'm sure there are a lot of such fakes going around the Archipelago.";
			link.l1 = "Thank you, you are very generous!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterReputation(pchar, 1);
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Yes, maybe, maybe... Well, I am ready to consider that the matter was resolved by God's judgment and by His will.";
			link.l1 = "Thank you, you are very generous!";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 1);
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar, "ReasonToFast");
		break;

		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "Don't you dare lecture me! Your collusion with scammers is obvious to me! Guard, take "+ GetSexPhrase("this 'well-wisher'", "this 'well-wisher'") +"!";
			link.l1 = "No way!";
			link.l1.go = "fight";

			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_Change(PIRATE);
		break;
		// ------------------------- Повод для спешки -----------------------------

		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "What business do you need it for?";
			link.l1 = "I have a few personal questions for him.";
			link.l1.go = "CapComission_PrisonBad2";
		break;

		case "CapComission_PrisonBad2":
			dialog.text = "Captain, I have a clear order to take into custody and send to the residence for an inquiry anyone who will be interested in the person " + pchar.GenQuest.CaptainComission.Name + ".";
			link.l1 = "You've done well! The prisoners are already coming to you for arrest!";
			link.l1.go = "CapComission_PrisonBad3";
		break;

		case "CapComission_PrisonBad3":
			dialog.text = "Nevertheless, I ask you to hand over your weapons.";
			link.l1 = "No way! You will have to take it away by force.";
			link.l1.go = "fight";
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;

		case "CapComission_PrisonGood1":
			dialog.text = "Yes, of course. I have received an order from the governor to assist you in this matter. You can go to the prisoner.";
			link.l1 = "Thank you...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;

		case "CapComission_PrisonFree1":
			dialog.text = "Uh, Captain, I have no instructions to release this prisoner from custody. You need to ask the governor's permission for this.";
			link.l1 = "Officer, I am acting in the interests of the inquiry. The prisoner has agreed to cooperate with the authorities and is ready to indicate the location of the hiding place. Any delay threatens that the valuable cargo will be found by smugglers and lost to the settlement.";
			link.l1.go = "CapComission_PrisonFree2";
		break;

		case "CapComission_PrisonFree2":
			dialog.text = "But I could allocate an escort to accompany him.";
			link.l1 = "It won't be necessary, I have enough security. Besides, I'm afraid of the location of the cache being made public.";
			link.l1.go = "CapComission_PrisonFree3";
		break;

		case "CapComission_PrisonFree3":
			dialog.text = "Mmm... well, okay. Just keep in mind that you are responsible for him with your head.";
			link.l1 = "Absolutely...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------

		case "F_ShipLetters_1":
			dialog.text = "Speak, I'm listening.";
			link.l1 = "I have the ship's documents. I think the owner has absentmindedly forgotten them, but you will be interested in them.....";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;

		case "F_ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Nonsense! Don't interfere with your work, you'd better go to the Port Authority.";
				link.l1 = "Thanks for that too....";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Yes, the owner is from the local area. Perhaps the award is in " + sti(pchar.questTemp.different.GiveShipLetters.price2) + "Gold coins will serve as a worthy reward for your vigilance, Captain.";
					link.l1 = "Probably not.";
					link.l1.go = "F_ShipLetters_3";
					link.l2 = "Generous offer! The papers are yours from now on....";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Wow, it's breathtaking how interesting they are! I think the city treasury will gratefully pay you "+ sti(pchar.questTemp.different.GiveShipLetters.price4) +"gold, for assistance in combating illegal trade.";
						link.l1 = "Probably not.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Generous offer! The papers are yours from now on....";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "God! What luck that you came to me. I think my unlucky colleague will agree to pay " + sti(pchar.questTemp.different.GiveShipLetters.price3) + " to avoid publicity.";
						link.l1 = "Probably not.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Generous offer! The papers are yours from now on....";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;

		case "F_ShipLetters_3":
			dialog.text = "Heh! This is my city, Captain.";
			link.l1 = "I'll remember that.";
			link.l1.go = "exit";
		break;

		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook");
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4));
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3));
				}
			}

			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{
				ChangeCharacterReputation(pchar, -1);
				OfficersReaction("bad");
			}
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "8");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;


        case "ForGoodMove":
			dialog.text = NPCStringReactionRepeat("But why would you do that? Believe me, there's nothing worth looking at, just thieves and bandits.", "We have already discussed this wish of yours.",
				"The same thing again? We've already talked about this twice!", "Um, again...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nevertheless, I wanted to take a tour of your casemates. I'm very interested!", "Yes, that's right. But I wanted to talk more about this topic.",
				"Well, maybe for the third time...", "The hope of looking at your prisoners does not leave me...", npchar, Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = (rand(15)+10)*100;
			if (sti(colonies[FindColony(npchar.city)].jail) && sti(pchar.money) >= sti(pchar.questTemp.jailCanMove.money))
			{
				dialog.text = "Well, I see no reason to refuse you. " + FindRussianMoneyString(sti(pchar.questTemp.jailCanMove.money)) + " - and until you leave the prison, you can freely walk through the corridors and even talk to prisoners.";
				link.l1 = "I agree. Here are your coins!";
				link.l1.go = "ForGoodMove_agree";
				link.l2 = "That won't do, it's too expensive to walk aimlessly through the corridors.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("No, this is strictly prohibited by the charter. Is this a circus for you? Go away, and don't distract me from my duty.", "I can't let strangers walk around the prison. Please don't bother me!");
				link.l1 = "Okay, whatever you say...";
				link.l1.go = "exit";
			}
		break;
        case "ForGoodMove_agree":
            dialog.text = "Well, you can start your own, so to speak, excursion...";
			link.l1 = "Thank you, Officer.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.jailCanMove.money));
		break;
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "For murder."; break;
				case "1": sTemp = "For banditry and armed robbery."; break;
				case "2": sTemp = "He was caught stealing."; break;
				case "3": sTemp = "For petty theft."; break;
				case "4": sTemp = "For cheating."; break;
			}
			dialog.text = sTemp;
			link.l1 = "Understood... Is there a chance to pay a ransom for him, bail, or in some other way contribute to his rescue?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
        case "KnowAboutPrisoner_0":
			dialog.text = "No, of course not. This hanged man has a direct road to hell. He is under special control of the governor!";
			link.l1 = "Heh, I see...";
			link.l1.go = "notFree_exit";
		break;
        case "KnowAboutPrisoner_1":
			dialog.text = "I don't think so. He spoiled a lot of blood for the residents of our city. So don't even ask.";
			link.l1 = "Hmm, I see.";
			link.l1.go = "notFree_exit";
		break;
        case "KnowAboutPrisoner_2":
			dialog.text = "No, perhaps not. He's a thief, and a thief should be in jail!";
			link.l1 = "Oh how! Well said, Lieutenant...";
			link.l1.go = "notFree_exit";
		break;
        case "KnowAboutPrisoner_3":
			dialog.text = "I don't even know. This brat stole a frying pan from one of the housewives. And I can't let him go, but rotting here for such a small thing is also not the case...";
			link.l1 = "So give it to me, Lieutenant. I will pay, within reasonable limits, of course.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
        case "KnowAboutPrisoner_4":
			dialog.text = "Getting out? It is quite possible. From my point of view, it doesn't make any sense to keep this little crook here.";
			link.l1 = "So give it to me, Lieutenant. I will pay, within reasonable limits, of course.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = (rand(3)+2)*1000;
			if (sti(pchar.money) > sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				dialog.text = "Hmm, all right. " + FindRussianMoneyString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "on the barrel, and take it right now.";
				link.l1 = "Great, I agree.";
				link.l1.go = "KnowAboutPrisoner_agree";
				link.l2 = "No, it's going to be expensive. I will refuse.";
				link.l2.go = "KnowAboutPrisoner_exit";
			}
			else
			{
				dialog.text = "No, it won't work. I can have an inspection at any time, I don't want to take any chances.";
				link.l1 = "Oh how! Well said, Lieutenant...";
				link.l1.go = "exit";
			}
		break;
        case "KnowAboutPrisoner_agree":
			dialog.text = "That's it, you can go to his cell and pick up this ragamuffin.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
        case "KnowAboutPrisoner_exit":
			dialog.text = "Well, look, I won't give you another chance...";
			link.l1 = "And don't. I made the desision.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//---------------- Протектор ------------------
        case "First_protector":
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("You can go through, the commandant has allowed...", "The commandant's order has been received. You can pass freely.");
				link.l1 = "Well, that's wonderful.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("It is strictly forbidden to proceed further without the permission of the commandant!", "I obey only the commandant. If you try to go further without his permission, you're finished!");
				link.l1 = RandPhraseSimple("Clear", "Clear") + ", soldier.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("I'm on duty, don't distract me.", "Pass by, I can't talk to you.");
			link.l1 = "Okay, soldier.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключённые ------------------
        case "First_prisoner":
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Ho ho, what fun!!", "Cut them, "+ GetSexPhrase("buddy", "girlfriend") +"cut!!!", "Oh, the devil! I never thought I'd see the corpse of my overseer!");
				link.l1 = RandPhraseSimple("Heh!", "Argh...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander"))
				{
					dialog.text = RandPhraseSimple("Wait, "+ GetSexPhrase("buddy", "girlfriend") +"!!! Let me out!", "Listen, "+ GetSexPhrase("buddy", "girlfriend") +", be so kind, open the cell.");
					link.l1 = "Why on earth would that be?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("I was taken for robbery, the case is being sewn...", "Ah, you're so elegant... You should be in my cell for a week! Khe-heh-heh...", "I'm not to blame for anything!");
				link.l1 = RandPhraseSimple("Shut up!", "I don't care about you...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn))
				{
					dialog.text = RandPhraseSimple("Wait, "+ GetSexPhrase("buddy", "girlfriend") +", don't pass by my cell so fast!", "Take your time, "+ GetSexPhrase("buddy", "girlfriend") +"Let's talk.");
					link.l1 = "Why on earth would that be?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "To listen to me. Don't look at me like this right now. I'd like to get out of here...";
			link.l1 = "What?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Sum = (rand(10)+10)*1000+(sti(pchar.rank)*1000); //сумма клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
		break;
        case "Prisoner_2":
            dialog.text = "Help me out, and I'll be able to thank you.";
			link.l1 = "Already interesting. Who are you and what can you offer me?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "My name is " + GetFullName(npchar) + ". I have something stashed away in a safe place. Get me out of here and take me to " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Acc") + ". I have a treasure hidden in the grotto there. Let's get it and divide it equally!";
			link.l1 = "And what's in your treasure? And how do I know that your words are true?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "I swear to you, I'm telling the absolute truth! And I hid money and jewelry in the treasure...";
			link.l1 = "No, buddy. I'm not going to risk my skin for a dubious treasure. I'm sorry...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{
				link.l2 = "It's probably worth the risk... I suggest the following: I can kill the guards in the prison and take you to my ship. If everything works out, I want you to stay with me until we get to the grotto on " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Voc") + ". Is it okay?";
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				link.l3 = "Well, okay, I'll try to help you - I'll talk to the commandant. It may be possible to post bail for your release.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Well, okay, I'll believe you and open the cell. I want you to stay with me until we get to the grotto on " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Voc") + ". Is it okay?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("Damn you, rascal!!", "May you be torn apart, Judas...");
			link.l1 = RandPhraseSimple("And have a nice day. Goodbye...", "The dog barked at Uncle Fryer...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Okay, I don't have to choose.";
			link.l1 = "Okay. I'm going to break your lock, come out of there, and we'll break through. Are you ready?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Yes, "+ GetSexPhrase("buddy", "girlfriend") +"I'm ready!";
			link.l1 = "Get to work!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Okay, I don't have to choose.";
			link.l1 = "Okay. Follow me as fast as you can, we still need to get to my ship. Don't fall behind!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Well, try it. Ehhh, it would have worked! Just don't waste any time, I won't be here in a couple of days...";
			link.l1 = "Wait, I'll fix it.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.MayorId = characters[GetCharacterIndex(npchar.city + "_Mayor")].id; //Id мэра
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(4); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("xia", "as"));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Well, what do you say, "+ GetSexPhrase("buddy", "girlfriend") +"?";
			link.l1 = "Everything is settled, I can pick you up.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "Well, let's get out of here faster! Damn it, I'm so glad!";
			link.l1 = "Let's summarize. I want all the time until we get to the grotto on " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Voc") + ", you didn't leave my side a single step. Just in case, so to speak. Do you agree?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Of course I agree! And I don't have to choose.";
			link.l1 = "Then you're free.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "armed robbery"; break;
				case "2": sTemp = "theft"; break;
			}
            dialog.text = "Well, what do you say, "+ GetSexPhrase("buddy", "girlfriend") +"?";
			link.l1 = "I was unable to negotiate your release. You are accused of " + sTemp + ", so there can be no question of any collateral.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
        case "ToPrisonHead_notFree_1":
            dialog.text = "I was lied to!.. Oh, the devil!! What am I supposed to do now? I'm going to rot here alive!";
			link.l1 = "I'm sorry, buddy, but I can't help you.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "There remains a chance to free you by force. I'm going to break your lock, come out of there, and we'll break through. Are you ready?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Damn you, scoundrel!!", "May you be torn apart, Judas...");
			link.l1 = "And have a nice day. Goodbye...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Well, what will please you, "+ GetSexPhrase("buddy", "girlfriend") +"?";
			link.l1 = "The bail for your release is too high, I don't have enough money. I am forced to refuse.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Listen, I've checked everything here, but I haven't found my treasure. It's a pity that it happened like this, probably someone dug it up before us.";
					link.l1 = "How can this be?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "I found it! The jewels were lying where I left them.";
					link.l1 = "Great. Well, are we going to share?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Well, here it is, my cache. It's not much, really, but it's all I have. As agreed, half is yours.";
					link.l1 = "Yes, the treasure is really not so good. Well, thanks for that, too.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Captain, I'm sorry, it just happened... Long story short, there is no treasure.";
					link.l1 = "What? You tricked me, you scoundrel! I pulled you out of your cell, dragged you to this island, and for what?! You can't get away with this!";
					link.l1.go = "Node_3";
				break;
				case 4:
					dialog.text = "Damn it... Well, how is that? It can't be!";
					link.l1 = "What are you doing, buddy? Where is our treasure? Don't tell me he's not here!";
					link.l1.go = "Node_4";
				break;
			}
		break;

		case "Node_1":
			dialog.text = "Yes, of course, as agreed. Half of the treasure is yours.";
			link.l1 = "Wow, there are so many valuable things here!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You got your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+drand(1));
			TakeNItems(pchar, "chest", 4+drand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry15", 10+rand(10));
			TakeNItems(pchar, "jewelry18", 60+rand(20));
			TakeNItems(pchar, "jewelry14", 40+rand(15));
			TakeNItems(pchar, "jewelry7", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		case "Node_2":
			dialog.text = "Captain, there is this Indian item here among other things. Take it over your share.";
			link.l1 = "Well, at least I'll get something sensible for your release! Give it to me.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You got your share of the treasure");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry11", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		case "Node_3":
			dialog.text = "Wait, Captain, don't get too excited, let me speak. I'm a sailor too, just like you. I was thrown into prison by mistake, I swear. You were my only chance to escape, and I had to lie to you about the treasure.There is no salary, but I hid one good thing here. Take her, and let me go in peace. Perhaps you will remember me with a kind word more than once in battle.";
			link.l1 = "Okay, there's nothing to charge you anyway. Thank God that I am forgiving.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You got the equipment");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		case "Node_4":
			dialog.text = "No!!! He really doesn't exist! The damn piece... Captain, believe me, I really thought he was here! But apparently I was wrong! Everything is so unclear on this piece of paper...";
			link.l1 = "Well, it looks like you're going to be in serious trouble right now, buddy. But I still want to hear your explanation.";
			link.l1.go = "Node_4_1";
		break;

		case "Node_4_1":
			dialog.text = "I had a piece of the map. An authentic map, I swear! But it's so hard to make out what kind of island is indicated on it... I thought it was here. But as you can see, this is not the case.";
			link.l1 = "What is the piece of the map? Give it here, now!";
			link.l1.go = "Node_4_2";
		break;

		case "Node_4_2":
			if (CheckCharacterItem(pchar, "map_part1"))
			{
				GiveItem2Character(pchar, "map_part2");
			}
			else
			{
				GiveItem2Character(pchar, "map_part1");
			}
			dialog.text = "Here, take it, of course. Captain, let me go, please... I really thought the treasure was here. Maybe you can figure out where it is on this piece and take it all for yourself. Please.";
			link.l1 = "Yeah... It is very difficult to make out anything here. The second half of the map is needed. Okay, get lost, I see you really meant well.";
			link.l1.go = "PrisonerInPlace_4";
		break;
        case "PrisonerInPlace_1":
			dialog.text = "Yes, very simple, "+ GetSexPhrase("buddy", "girlfriend") +". It's also not something that happens in life. Okay, you're here, if you want to stay, look for more. Well, I have to go!Goodbye, "+ GetSexPhrase("friend", "girlfriend") +", thanks for saving. I will remember you forever!";
			link.l1 = "You bastard! Do you think I'm going to let you just walk away?! Hey... Stop there, you coward!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");

			AchievementsCounter_genquests(1);

			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
        case "PrisonerInPlace_3":
			dialog.text = "Please receive. And thank you!";
			link.l1 = "Goodbye...";
			link.l1.go = "PrisonerInPlace_2";
		break;
        case "PrisonerInPlace_4":
			dialog.text = "Thank you, Captain! I will pray for you until the end of my days!";
			link.l1 = "Come on, fill it up! Go with God...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "iSum", FindRussianMoneyString(sti(pchar.questTemp.jailCanMove.Sum)));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("GivePrisonFree");

			AchievementsCounter_genquests(1);

			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
 		break;
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "My nickname is " + GetFullName(npchar) + ". I have one request for you, hehe...";
			link.l1 = "What is it?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "It is necessary to transfer the baby to freedom. Will you do it?";
			link.l1 = "What's the point of that for me?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "Your homies won't offend you, of course... So, will you take it?";
			link.l1 = "No, I'm not interested in that.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Hmm, if you don't have to go far, then I'll take it.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Okay. Now listen to me carefully. Two Kents are waiting for my baby in the city, they hid in the house so as not to get under the hood. I don't know which house, I'll have to look for it.";
			link.l1 = "How to search?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Usually search. You run around the city, you look at houses... Once you get to the right place, they won't let you out without talking. Just keep in mind that I'll be here for two more days, no more. So don't delay.";
			link.l1 = "Clear. Well, give me your message.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Hmm, I don't like you. I've changed my mind. Come on, come on, don't stand here!";
				link.l1 = "Wow! Well, whatever you want...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Here you go. Thank you, "+ GetSexPhrase("buddy", "girlfriend") +"!";
				link.l1 = "You're welcome.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true;
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("cя", "as"));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(4);
	switch (iTemp)
	{
		case 0:
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1:
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2:
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3:
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
		case 4:
			pchar.questTemp.jailCanMove.islandId = "StLucia";
			pchar.questTemp.jailCanMove.placeId = "StLucia_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId;
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{
				storeArray[howStore] = LocId;
				howStore++;
			}
			if (arCommon.label != "Sea")
			{
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    				{
						storeArray[howStore] = LocId;
						howStore++;
					}
				}
			}
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{
				storeArray[howStore] = LocId;
				howStore++;
			}
			if (arCommon.label != "Sea")
			{
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1)
    				{
						storeArray[howStore] = LocId;
						howStore++;
					}
				}
			}
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId)
		{
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = "indian6";
		break;
		case 1:
			itemID = "indian10";
		break;
		case 2:
			itemID = "indian12";
		break;
		case 3:
			itemID = "indian19";
		break;
		case 4:
			itemID = "indian20";
		break;
		case 5:
			itemID = "indian22";
		break;
		case 6:
			itemID = "indian21";
		break;
		case 7:
			itemID = "sculMa2";
		break;
		case 8:
			itemID = "sculMa1";
		break;

	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade22");
		break;
		case 1:
			itemID = GetGeneratedItem("blade19");
		break;
		case 2:
			itemID = GetGeneratedItem("blade31");
		break;
		case 3:
			itemID = "cirass3";
		break;
		case 4:
			itemID = GetGeneratedItem("blade21");
		break;
		case 5:
			itemID = "spyglass4";
		break;
		case 6:
			itemID = GetGeneratedItem("blade15");
		break;
		case 7:
			itemID = GetGeneratedItem("blade34");
		break;
		case 8:
			itemID = "cirass4";
		break;

	}
	return itemID;
}

void GetGunType()
{
		int iGunType;
		ref rCannon;
		if(makeint(pchar.rank) < 5) { iGunType = rand(1); }	//24
		if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 13) { iGunType = rand(3); } //24&&32
		if(makeint(pchar.rank) >= 13 && makeint(pchar.rank) < 20) { iGunType = rand(2)+2; } //32&&42
		if(makeint(pchar.rank) >= 20) { iGunType = 4; } //42

		switch (iGunType)
		{
			case 0:
				pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;
				rCannon = GetGoodByType(GOOD_CANNON_24);
				pchar.questTemp.PrisonGun.Price = sti(rCannon.Cost) + 175*GetCharacterSPECIALSimple(PChar, SPECIAL_C)*GetSummonSkillFromName(pchar, SKILL_COMMERCE)/200;
                pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank)*5+30+rand(sti(pchar.rank)));
				pchar.questTemp.PrisonGun.Text = "24 caliber guns";
			break;
			case 1:
				pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_24;
				rCannon = GetGoodByType(GOOD_CULVERINE_24);
				pchar.questTemp.PrisonGun.Price = sti(rCannon.Cost) + 225*GetCharacterSPECIALSimple(PChar, SPECIAL_C)*GetSummonSkillFromName(pchar, SKILL_COMMERCE)/200;
                pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank)*5+20+rand(sti(pchar.rank)));
				pchar.questTemp.PrisonGun.Text = "24 caliber culverins";
			break;
			case 2:
				pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;
				rCannon = GetGoodByType(GOOD_CANNON_32);
				pchar.questTemp.PrisonGun.Price = sti(rCannon.Cost) + 275*GetCharacterSPECIALSimple(PChar, SPECIAL_C)*GetSummonSkillFromName(pchar, SKILL_COMMERCE)/200;
                pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank)*4+10+rand(sti(pchar.rank)));
				pchar.questTemp.PrisonGun.Text = "32 caliber guns";
			break;
			case 3:
				pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_32;
				rCannon = GetGoodByType(GOOD_CULVERINE_32);
				pchar.questTemp.PrisonGun.Price = sti(rCannon.Cost) + 325*GetCharacterSPECIALSimple(PChar, SPECIAL_C)*GetSummonSkillFromName(pchar, SKILL_COMMERCE)/200;
                pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank)*4+10+rand(sti(pchar.rank)));
				pchar.questTemp.PrisonGun.Text = "culverins of 32 caliber";
			break;
			case 4:
				pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;
				rCannon = GetGoodByType(GOOD_CANNON_42);
				pchar.questTemp.PrisonGun.Price = sti(rCannon.Cost) + 425*GetCharacterSPECIALSimple(PChar, SPECIAL_C)*GetSummonSkillFromName(pchar, SKILL_COMMERCE)/200;
                pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank)*3+20+rand(sti(pchar.rank)));
				pchar.questTemp.PrisonGun.Text = "42 caliber guns";
			break;
		}
}
