// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions, "+ GetSexPhrase("young man", "young lady") +"?", "What do you want, "+ GetSexPhrase("handsome", "pretty woman") +"? Ask your questions ..."), "More questions?", "Hee-hee, the third time a day the same thing - questions ...",
                          ""+ GetSexPhrase("Hmm, can you choose some beauty for yourself? And then I already have a very definite opinion about you...", "Hmm, maybe you will choose some kind of beauty for yourself? We don't keep boys, hee-hee...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "Hmm, nothing..."), "No...",
                      "Yeah, it's really the third time... Sorry.", "Not now... Another time...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
            if (pchar.questTemp.State == "SeekBible_toFFBrothel" && npchar.id == "FortFrance_Hostess") //Голландская линейка, квест №8. узнаем о пирате, который о Библии базарил.
			{
                link.l1 = "Listen, some time ago Jackman was on vacation with you in the company of corsairs...";
                link.l1.go = "Step_H8_1";
			}
			if (pchar.questTemp.Sharp == "seekSharp" && GetNpcQuestPastDayWOInit(npchar, "quest.SharpTime") > 7 && !LAi_IsDead(&characters[GetCharacterIndex("Sharp")]))
			{
				link.l1 = "Listen, " + npchar.name + ", I'm looking for Sharp. Do you know where he is?";
				link.l1.go = "SharpPearl_1";
				SaveCurrentNpcQuestDateParam(npchar, "quest.SharpTime");
			}
            // <== Проверяем поле состояния квестов.
		break;

        case "Step_H8_1":
            dialog.text = ""+ GetSexPhrase("Young man", "Young lady") +", they are relaxing with us in the company of girls, not each other! Watch what you say...";
            link.l1 = "Well, they were vacationing in a big company...";
            link.l1.go = "Step_H8_2";
        break;
        case "Step_H8_2":
            dialog.text = "Really big, there were a lot of people there. I will remember this vacation of theirs for a long time...";
            link.l1 = "Why, let me ask you?";
            link.l1.go = "Step_H8_3";
        break;
        case "Step_H8_3":
            dialog.text = "Yes, because my entire establishment was working for them that night. It was terrible!";
            link.l1 = "I see... listen, you haven't heard about this: someone tried to sell one book, like the Bible...";
            link.l1.go = "Step_H8_4";
        break;
        case "Step_H8_4":
            dialog.text = "No, I haven't heard that.";
            link.l1 = "Maybe your girls will tell you?";
            link.l1.go = "Step_H8_5";
        break;
        case "Step_H8_5":
            dialog.text = "Maybe they will tell you. But I don't care about that, ask "+ GetSexPhrase("myself", "myself") +".";
            link.l1 = "And who? Who was there that night?";
            link.l1.go = "Step_H8_6";
        break;
        case "Step_H8_6":
            dialog.text = "Everyone was! All as one! Ask everyone. Maybe someone will really remember...";
            link.l1 = "Thank you, I'm going to ask...";
            link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_toGirl";
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

