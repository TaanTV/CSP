//#include "DIALOGS\convoy_traider.h"
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("Oh, damn!! I know who you are! Only a complete idiot can hire you to accompany his ship. Goodbye!", "Ah, I know who you are! Should I hire you as an escort?! Look for a fool...");
				link.l1 = RandPhraseSimple("Heh, what a timid...", "What a timid people went!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! I "+ GetFullName(NPChar) + ", the merchant. I heard that you are looking for a job?";
				link.l1 = "Something like that. And, as I heard, you are looking for a captain who would accompany you and your ship to your destination?";
				link.l1.go = "prepare_convoy_quest_2";
			}
		break;

		case "prepare_convoy_quest_2":
			dialog.text = "That's right. Moreover, I think that you are suitable for me as an escort. What do you say?";
			link.l1 = "I'll tell you - tell me the amount and maybe we'll come to an agreement.";
			link.l1.go = "prepare_convoy_quest_3";
		break;

		case "prepare_convoy_quest_3":
			LookShipConvoy();
			GenerateConvoyQuest(npchar);
			dialog.text = "I need to be escorted to " + XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + " which is on " + XI_ConvertString(GetIslandByCityName(pchar.quest.destination) + "Voc") +
				", in " + FindRussianDaysString(sti(pchar.ConvoyQuest.iDay)) +", and for that I will pay you " + FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney)) + ". What do you think?";
			link.l1 = "I agree.";
			link.l1.go = "convoy_agreeded";
			link.l2 = "I don't think I'm interested in this.";
			link.l2.go = "convoy_refused";
		break;

		case "convoy_refused":
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_refused");
		break;

		case "convoy_agreeded":
			chrDisableReloadToLocation = false;
		    pchar.convoy_quest = pchar.quest.destination;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_agreeded");
		break;

		case "complete_convoy_quest":
			dialog.text = "Oh! Thank you. I felt more relaxed than ever under your protection. Here is your reward.";
			Link.l1 = "Thank you.";
			link.l1.go = "exit";
			//слухи
			AddSimpleRumour(LinkRandPhrase("A certain trading cap by name " + GetFullName(npchar) + " says you can trust " + GetMainCharacterNameDat() + " in terms of escorting merchant ships.",
				"Merchant by name " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted. "+ GetSexPhrase("That protected", "That protected") +" his ship is in the best possible way when escorted to " + XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ".",
				"I've heard that you keep your word on escorting ships given to merchant captains. A certain merchant named " + GetFullName(npchar) + " speaks very well of you."), sti(npchar.nation), 40, 1);
			pchar.quest.generate_convoy_quest_progress = "completed";
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			AddDialogExitQuest("convoy_refused");
		break;
	}
}

// boal 03.05.04 квест сопроводить торговца -->
void GenerateConvoyQuest(ref npchar)
{
	int iTradeMoney, iNation;

	DeleteAttribute(NPChar, "Ship");
    SetShipToFantom(NPChar, "trade", true);

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.ConvoyQuest.City), GetArealByCityName(pchar.quest.destination));
	if (sti(daysQty) > 14) daysQty = 14;
	pchar.ConvoyQuest.iDay = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*600*sti(pchar.GenQuest.Convoy.Shipmod)+rand(100))*sti(daysQty)/sti(pchar.ConvoyQuest.iDay);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.4); //то размер награды увеличивается
	pchar.ConvoyQuest.convoymoney = iTradeMoney;

	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(pchar.quest.destination);
	//Log_Info(pchar.ConvoyQuest.City);
	SetTimerCondition("generate_convoy_quest_timer", 0, 0, sti(pchar.ConvoyQuest.iDay), false);

	pchar.quest.generate_convoy_quest_progress = "begin";

	pchar.quest.generate_convoy_quest_failed.win_condition.l1 = "NPC_Death";
	pchar.quest.generate_convoy_quest_failed.win_condition.l1.character = "QuestTrader";
	pchar.quest.generate_convoy_quest_failed.win_condition = "generate_convoy_quest_failed";
}

void LookShipConvoy()
{
	switch(makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.Convoy.Shipmod = 0.7;
		break;
		case 1:
			pchar.GenQuest.Convoy.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.Convoy.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.Convoy.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.Convoy.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.Convoy.Shipmod = 3;
		break;
		case 6:
			pchar.GenQuest.Convoy.Shipmod = 4.5;
		break;
	}
}
