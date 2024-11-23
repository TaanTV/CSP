// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, "+ GetSexPhrase("young man", "young lady") +"?", "What do you want, "+ GetSexPhrase("handsome", "pretty woman") +"?"), "More questions?", "Hee-hee, the third time a day the same thing - questions...",
                          ""+ GetSexPhrase("Hmm, can you choose some beauty for yourself? And then I already have a very definite opinion about you...", "Hmm, maybe you will choose some kind of beauty for yourself? We don't keep boys, hee-hee...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "Hmm, nothing..."), "No...",
                      "Yeah, it's really the third time... Sorry.", "Not now... Another time...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Анжелика Тич: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.AT_PZD_Bordel"))
			{
				DeleteAttribute(pchar, "questTemp.AT_PZD_Bordel")
				link.l1 = "I have come to you with a somewhat unusual offer. Could you sell me the best dress from your wardrobe?";
				link.l1.go = "AT_PZD_Bordel_1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.AT_PZD_Bordel_2"))
			{
				DeleteAttribute(pchar, "questTemp.AT_PZD_Bordel_2")
				link.l1 = "I'm back about the dress.";
				link.l1.go = "AT_PZD_Bordel_6";
				break;
			}
			// <== Анжелика Тич: Портниха знатной дамы
			if (pchar.questTemp.Sharp == "seekSharp" && GetNpcQuestPastDayWOInit(npchar, "quest.SharpTime") > 7 && !LAi_IsDead(&characters[GetCharacterIndex("Sharp")]))
			{
				link.l1 = "Listen, " + npchar.name + ", I'm looking for Sharp. Do you know where he is?";
				link.l1.go = "SharpPearl_1";
				SaveCurrentNpcQuestDateParam(npchar, "quest.SharpTime");
			}
		break;
		
		//============ Анжелика Тич: Портниха знатной дамы
		case "AT_PZD_Bordel_1":
    		dialog.text = "Really unusual. I'm afraid such a service will cost you a fortune.";
    		link.l1 = "Maybe it can be rented for an evening or two?";
    		link.l1.go = "AT_PZD_Bordel_2";
 		break;
		case "AT_PZD_Bordel_2":
    		dialog.text = "Perhaps this can be arranged. Let's say 15,000 piastres and a guarantee that it will be returned in time, safe and sound.";
			link.l1 = "Without a single spot... And since we've agreed on the price, maybe you can also find a suitable carnival mask, one that covers the whole face?";
    		link.l1.go = "AT_PZD_Bordel_3";
 		break;
		case "AT_PZD_Bordel_3":
    		dialog.text = "Let's pick something up. Fifty thousand and she's yours.";
			link.l1 = "What?! Did you miss the price by any chance?";
    		link.l1.go = "AT_PZD_Bordel_4";
 		break;
		case "AT_PZD_Bordel_4":
    		dialog.text = "I'm sure there was just some misunderstanding between us. You probably mistook me for a stupid woman who couldn't understand the intentions of entering the local residence incognito. Fifty thousand for my silence, fifteen will cost you a dress for the evening and you will receive a mask from me as a gift. So how is it?";
			if (sti(pchar.Money) >= 65000)
			{
				link.l1 = "And you know how to do business. I don't seem to have a way out. Here's your money. I hope the style won't disappoint me.";
				link.l1.go = "AT_PZD_Bordel_5";
			}
			link.l2 = "Well, I'll think about it and maybe come back later.";
    		link.l2.go = "AT_PZD_Bordel_4_1";
 		break;
		case "AT_PZD_Bordel_4_1":
    		DialogExit();
			pchar.questTemp.AT_PZD_Bordel_2 = true;
 		break;
		case "AT_PZD_Bordel_6":
    		dialog.text = "So, is our deal going to happen? (65,000)";
			if (sti(pchar.Money) >= 65000)
			{
				link.l1 = "Here's your money. I hope the style won't disappoint me.";
				link.l1.go = "AT_PZD_Bordel_5";
			}
			link.l2 = "I'm still considering whether your offer is worth it.";
    		link.l2.go = "AT_PZD_Bordel_4_1";
 		break;		
		case "AT_PZD_Bordel_5":
			LAi_Fade("", "");
			Log_info("You're wearing a carnival costume");
			AddMoneyToCharacter(pchar, -65000);
			//PlaySound("Interface\important_item.wav");
			GiveItem2Character(PChar, "AT_PZD_KarnavalKostum");
    		dialog.text = "Tie up a little more here and I'll be almost satisfied with the result. It's a pity, Angelica, that you didn't wear a corset in your youth, it would have fit much better. Talia is still giving away a commoner.";
			link.l1 = "The soldiers won't pay attention to this, and then I'll manage.";
    		link.l1.go = "AT_PZD_Bordel_8";
 		break;
		case "AT_PZD_Bordel_8":
    		dialog.text = "No, it's not bad, it's not bad. I think I've even changed my mind, you don't have to return the outfit to me, consider it bought.";
			link.l1 = "I like this deal a lot more. I will not refuse. That's it, I have to hurry, or I'll be late!";
    		link.l1.go = "AT_PZD_Bordel_9";
 		break;
		case "AT_PZD_Bordel_9":
    		DialogExit();
			
			SetCurrentTime(22, 1);
			DoQuestReloadToLocation("Marigo_town", "goto", "goto19", "AT_PZD_IdemNaKarnaval");
 		break;
		
		// капитан Шарп, грабёж жемчужных промыслов
		case "SharpPearl_1":
			if (drand(1) || bBettaTestMode)
			{
				if (sti(pchar.questTemp.Sharp.brothelChance) < 9)
				{	//футболим геймера в город
					pchar.questTemp.Sharp.City = GetSharpCity();
					pchar.questTemp.Sharp.City.rumour = true; //флаг дачи слуха
					dialog.text = "As far as I know, Captain Sharp went to " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + ".";
					link.l1 = "Heh! Thank you, " + npchar.name + ". You've helped me a lot!";
					link.l1.go = "exit";
					pchar.questTemp.Sharp = "toSharp_going"; //в бордели больше не заходить
					pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
					pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
					pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
					ReOpenQuestHeader("SharpPearl");
					AddQuestRecord("SharpPearl", "1");
					AddQuestUserData("SharpPearl", "sCity", XI_ConvertString("Colony" + npchar.city + "Voc"));
					AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
					if (GetIslandByCityName(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
					{
						AddQuestUserData("SharpPearl", "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.questTemp.Sharp.City) + "Voc"));
					}
					//запускаем энкаунтер Шарпа на карте
					group_DeleteGroup("Sharp_Group");
					sld = characterFromId("Sharp");
					string sGroup = "Sharp_Group";
					Group_FindOrCreateGroup(sGroup);
					Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
					Group_LockTask(sGroup);
					Group_AddCharacter(sGroup, sld.id);
					Group_SetGroupCommander(sGroup, sld.id);
					sld.mapEnc.type = "trade";
					sld.mapEnc.worldMapShip = "quest_ship";
					sld.mapEnc.Name = "Brig 'Sharp Bearer'";
					string sColony= SelectAnyColony(npchar.city); //колония, откуда плывёт Шарп
					int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sColony), GetArealByCityName(pchar.questTemp.Sharp.City)) + 1; //дней доехать даём с запасом
					Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
					Log_TestInfo("The sharp-bearer is installed from  " + sColony + " in " + pchar.questTemp.Sharp.City);
				}
				else
				{	//чудо, Шарп здесь, в борделе!
					dialog.text = "I know. He's resting at my place. I can call Sharp if you need him urgently.";
					link.l1 = "Do me a favor, " + npchar.name + "...";
					link.l1.go = "SharpPearl_2";
				}
			}
			else
			{
				dialog.text = "I don't know, I haven't had it for a long time.";
				link.l1 = "Understood... Well, thank you, " + npchar.name + ".";
				link.l1.go = "exit";
			}
		break;
		case "SharpPearl_2":
			dialog.text = "Bartalomew-yu-sha! Come to me, dear, someone is asking for you here!";
			link.l1 = "Heh, and you hold Sharp in high esteem, I see...";
			link.l1.go = "SharpPearl_3";
		break;
		case "SharpPearl_3":
			chrDisableReloadToLocation = true;
			pchar.questTemp.Sharp.count = 0; //счётчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			sld = &characters[GetCharacterIndex("Sharp")];
			sld.dialog.currentnode = "BrothelSharp";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

