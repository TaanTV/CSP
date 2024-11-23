// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I'm listening.";
			if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
			{
				link.l1 = "Officer, I see you look very worried. Can I help you with something?";
				link.l1.go = "zpq_prs1";
			}
			if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 50000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
			{
				link.l2 = "I hasten to inform you that the cargo of gunpowder has been delivered. The ship is ready to be unloaded.";
				link.l2.go = "zpq_ex";
			}
			if (pchar.questTemp.zpq == "begin")
			{
				link.l3 = "I want to cancel our contract for the delivery of gunpowder. It turned out to be too troublesome...";
				link.l3.go = "zpq_fld2";
			}
			link.l4 = "I "+ GetSexPhrase("wrong", "wrong") +". Have a nice day.";
			link.l4.go = "Exit";
		break;

		case "zpq_prs1":
		if(!isBadReputation(pchar, 70))
		{
			dialog.text = "Hmm, maybe-maybe... Perhaps, thanks to your good reputation, I will venture to trust you. Otherwise, I wouldn't even talk about such a topic. The fact is that we need a fairly large shipment of difficult cargo, so you will need a ship with a large hold and a willingness to take risks. And you must promise that the information you receive will remain closed to prying ears. If you are confused by at least one of the conditions, tell me about it right away. I think you understand me...";
			link.l1 = "It sounds quite intriguing. And although I do not guess what kind of cargo we are talking about, I am still ready to take a chance if the payment is decent. Anyway, I give you my word.";
			link.l1.go = "zpq_prs2";
			link.l2 = "No, perhaps not... My word to you will oblige me to take up a case that already seems very doubtful to me. I won't mess with it...";
			link.l2.go = "zpq_fld";
		}
		else
		{
			dialog.text = "Your reputation does not allow me to conduct any serious business with you. Please vacate the room. We are able to solve our own problems.";
			link.l1 = "Well, decide...";
			link.l1.go = "exit";
		}
		break;
		case "zpq_fld":
			dialog.text = "Well, at least you refused honestly and did not dissemble... I dare not detain you.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
		break;
		case "zpq_fld2":
			dialog.text = "Hmm, I must admit, I did not expect such a retreat. I have to ask you to leave... And remember about the promise not to disclose the information received.";
			link.l1 = "Please forgive me...";
			link.l1.go = "exit";
    			ChangeCharacterReputation(pchar, -10);

			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("", "a"));
				CloseQuestHeader("zpq");
				pchar.questdata.OpasnyGruz = 1;
			}
			pchar.questTemp.zpq = "failed";
		break;
		case "zpq_prs2":
			dialog.text = "That's great. The fact is that a recent prolonged storm has soaked a fair amount of gunpowder in the arsenals of our fort. I hope you don't need to explain what a delicate situation we are in. In the event of a serious siege, the fort is unlikely to be able to put up a decent fight, we will not last long.";
			link.l1 = "Now it is clear what kind of cargo you need. And how many are we talking about?";
			link.l1.go = "zpq_prs3";
		break;
		case "zpq_prs3":
			dialog.text = "We need 50,000 cartridges of gunpowder. I'll pay 300,000 piastres for the whole shipment... that's a very good price, you know. Our situation makes it necessary to pay such a price, although I have made great efforts to convince the governor's treasurer... The storm season does not allow us to use the regular supply channels, and we can not advertise such a case...";
			link.l1 = "Understood... the price is really good. By the way, you mentioned some kind of risk.";
			link.l1.go = "zpq_prs4";
		break;
		case "zpq_prs4":
			dialog.text = "I meant that this amount of gunpowder in the hold can be very dangerous during transportation. In my memory, there have been several cases of ships exploding from an accidental spark, and even if you get into a storm... During transportation, even the convoy stays away from such a potential fire ship, because if anything happens, everyone will be blown to pieces!..";
			link.l1 = "Clear... But I'm not throwing words to the wind - consider that the order has been accepted.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Oh, senor... You are telling terrible things... I don't feel like getting involved in this anymore.";
			link.l2.go = "zpq_fld2";
		break;
		case "zpq_prs5":
			dialog.text = "That's great, I'm so glad we had a deal. We will settle immediately after delivery, you can not worry about it. Cargo needs to be delivered not earlier than a week, just by that time I will have all the money. Although I understand that it will be difficult to assemble such a party, and I do not give you time limits, still try not to delay.";
			link.l1 = "Everything is very clear to me, senor. I'm starting immediately.";
			link.l1.go = "zpq_prs5_ok";
		break;
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			//pchar.questTemp.zpq.time = 20;//не вижу использования этого
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("", "a"));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		case "zpq_ex":
			dialog.text = "Well, finally! I thought you'd forgotten about our agreement. I will now order soldiers to be dispatched for unloading. Handling gunpowder does not tolerate fuss, hehe!";
			link.l1 = "It's all fine, senor, but I have to remind you about the payment.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 50000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            		pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            		pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            		pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		case "zpq_ex2":
			dialog.text = "Yes, yes, of course. You'll be paid 150,000 piastres at once, as per our agreement.";
			link.l1 = "Are you kidding me, senor?! The contract was for 300,000 and I'm not giving up a piastre!";
			link.l1.go = "zpq_ex3";
			link.l2 = "I'm starting to think you're trying to trick me, so I'm not leaving here without my 450,000 piastres!";
			link.l2.go = "zpq_ex4";
			link.l3 = "Hmm... I see circumstances have changed. Well, I'm ready to accept the specified amount so as not to inflame the situation.";
			link.l3.go = "zpq_ex5";
		break;
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, "Leadership") > 50)
			{
				dialog.text = "Oh yes... exactly! 300,000 piastres. Forgot, please excuse me. Age, you know, not the same, sclerosis... Of course, here's your money. It's been a pleasure doing business with you. Now, if you'll excuse me, things are waiting for me...";
				link.l1 = "Nice to meet you too, senor. Have a nice day.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            			AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("", "a"));
				CloseQuestHeader("zpq");
				pchar.questdata.OpasnyGruz = 1;
				pchar.questTemp.zpq.sum = 300000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = "What about?!! Take the money and get out, otherwise you'll rot in these casemates!";
				link.l1 = "Yes, senor, you are a liar! I suggest you give the money we agreed on in a good way, or I'll take the goods!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Please forgive me... Okay, I'll take the offered amount and we'll part ways.";
				link.l2.go = "zpq_ex5";
			}
		break;
		case "zpq_ex4":
				dialog.text = "How insolence! I'm not out of my mind yet and I definitely remember that our deal was for 300,000 pi... Oh, damn it! You won't fool me!";
				link.l1 = "Don't boil over. It is better to think about the fact that there is a ready-made fire-ship, filled to the brim with gunpowder, at the walls of your fort. All I have to do is whistle and your fortifications will be nothing but ruins.";
				link.l1.go = "zpq_ex6";
		break;
		case "zpq_ex6":
			if (GetSummonSkillFromName(pchar, "Leadership") > 75)
			{
				dialog.text = "Um... a strong argument. 450,000 piastres, speak? Here, hold your money... And now, if you'll excuse me, things await...";
				link.l1 = "Have a nice day, senor. Goodbye.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            			AddQuestRecord("zpq", "5");
				CloseQuestHeader("zpq");
				pchar.questdata.OpasnyGruz = 1;
				pchar.questTemp.zpq.sum = 450000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = "What?! I'm a combat officer! Who are you trying to scare"+ GetSexPhrase(", brat", ", brat") +"?! Guards, take "+ GetSexPhrase("him", "her") +"!!!";
				link.l1 = "Well, hang on, casemate rats...";
				link.l1.go = "zpq_ex_war";
			}
		break;
		case "zpq_ex5":
			dialog.text = "Great! You made the right choice. Get the money and goodbye. It was a pleasure doing business with you. Ha ha ha!";
			link.l1 = "Goodbye...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            		AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("zpq");
			pchar.questdata.OpasnyGruz = 1;
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		case "zpq_ex_agry":
			dialog.text = "Oh, you're bastard!!! Guards, take "+ GetSexPhrase("him", "her") +"!!!";
			link.l1 = "Argh!! I'll have to take the money from your corpse...";
			link.l1.go = "zpq_ex_war";
		break;
        	case "zpq_ex_war":

			DialogExit();

			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			Flag_Change(PIRATE);
			pchar.questTemp.zpq = "failed";
            		AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questdata.OpasnyGruz = 1;
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade20");
			EquipCharacterbyItem(npchar, "blade20");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass4");

			chrDisableReloadToLocation = true;

			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";

			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");

			AddSimpleRumour("Such things are happening here!! Rumor has it that in Cumana some prisoner got out of the casemates, killed all the guards of the fort, robbed the treasury and was gone! Well, that's it!..", SPAIN, 5, 1);

		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

