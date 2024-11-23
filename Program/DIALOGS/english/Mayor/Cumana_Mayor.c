// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	int i;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What did you want? Ask.", "I'm listening to you, what's the question?"), "For the second time in a day you're trying to ask a question...", "For the third time in a day you're trying to ask a question again...",
                          "But when will it end?! I have a lot of things to do to manage the affairs of the city, and you're trying to ask all the questions!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, not the place and not the time..."), "Yes, that's right... But not now, later...",
                      "I'll ask, I'll ask... Only later...", "I'm sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Sp8SaveCumana_GoodWork")//квест №8 испанки.
			{
				dialog.text = RandPhraseSimple(""+ GetSexPhrase("Senor", "Senorita") +", the whole city is grateful to you for the rest of its life. If it wasn't for you, it's even scary to imagine what could have happened...", "The whole city was watching the battle - it was a great battle. We are very grateful to you for saving us from dirty pirates.");
				link.l1 = RandPhraseSimple("Yes, you can't expect mercy from Ladrons...", "These ladrons need to be destroyed everywhere...");
				link.l1.go = "exit";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You've already taken everything. What else do you need?", "Is there really anything left that you didn't bring?");
            link.l1 = RandPhraseSimple("Looking around for the last time...", "Checking, maybe I forgot to pick up something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//************************** Квестовые штрумы ************************
        //==> Одиннадцатый квест англ.линейки: захват Каракаса и Куманы.
        case "EngLine11Quest_OccupyMein":
			dialog.text = "That's it, we've stopped resisting. The city is yours. What's going to happen now?";
			link.l1 = "By the authority given to me by the Governor-General of Jamaica, I declare this city to be the possession of Charles II Stuart.";
			link.l1.go = "Step_E10_1";
			AfterTownBattle();
        break;
        case "Step_E10_1":
			dialog.text = "So...";
			link.l1 = "Now the city of Cumana is under the protectorate of England. All tax fees, trade duties, and other taxes must be paid by the new English administration.";
			link.l1.go = "exit";
            AddQuestRecord("Eng_Line_11_OccupyMein", "3");
            pchar.questTemp.Q11_Cumana = 1;
            NextDiag.TempNode = "Cupture_after";
			PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            UpdateRelations();
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
        break;
        //==> Шестой квест фр.линейки: захват Куманы с Олоне.
 		case "FraLine6Quest_Attack":
			dialog.text = "Our city has fallen... I am ready to listen to your demands.";
			link.l1 = "We have learned that there are 200,000 reais in Cumana... We came here for this money.";
			link.l1.go = "Step_F6_1";
			group_DeleteGroup("Spa_Attack");
			AfterTownBattle();
		break;
		case "Step_F6_1":
            dialog.text = "Hmm, I see... And if I say that there is no money?";
			link.l1 = "Listen, senor, do you know who Francois Olone is?";
            link.l1.go = "Step_F6_2";
        break;
		case "Step_F6_2":
            dialog.text = "I've heard the name of this devil's brat...";
			link.l1 = "So, Olone is my companion, he took the city with me. And believe me, if you persist, half of the inhabitants of your city will lose their heads. And he will cut off Olona's heads with his own hands in front of other people. How do you like this prospect?";
            link.l1.go = "Step_F6_3";
        break;
		case "Step_F6_3":
			if (GetQuestPastDayParam("questTemp") < 14)
			{
				dialog.text = "I've heard that he's done this before... Well, I won't pretend to be a hero, especially since completely innocent people will suffer... All the reals are in the next room in the secretary. Take it and be damned!";
				link.l1 = "Then we will torture the population of the city...";
				link.l1.go = "Step_F6_exit";
         		pchar.GenQuestBox.Cumana_TownhallRoom = true;
				pchar.GenQuestBox.Cumana_TownhallRoom.box1.money = 200000;
				LocatorReloadEnterDisable("Cumana_townhall", "reload2", false);
				pchar.questTemp.State = "Fr5Olone_FoundMoney";
			}
			else
			{
				dialog.text = "Be careful what you say, sir. Although I am not an Old man, I will gladly cut off your filthy tongue...";
				link.l1 = "I have heard that he has already done this and I have no doubt that he will be able to do it again. But there is no money, it's true. Five days ago, a squadron came for them. Money is on the way to the new world.";
				link.l1.go = "Step_F6_4";
			}
        break;
		case "Step_F6_4":
            dialog.text = GetSexPhrase("Senior", "Seniorita") +", it is quite clear that we are in your power. As the governor of this city, I am very clearly aware of the situation we are in. Take everything you find, but the money you came here for is no longer here. You're too late...";
			link.l1 = "Carramba! I must discuss the fate of the city with my associates!";
            link.l1.go = "Step_F6_exit";
			pchar.questTemp.State = "Fr5Olone_WeLate";
        break;
		case "Step_F6_exit":
			for (i=0; i<3; i++)
			{
				if (i==0)	sld = characterFromID("Olone");
				else	sld = characterFromID("Captain_"+i);
				RemoveCharacterCompanion(pchar, sld);
				sld.dialog.currentnode = "First time";
				LAi_SetStayType(sld);
				LAi_SetCurHPMax(sld);
				LAi_LoginInCaptureTown(sld, true);
			}
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition.l1 = "location";
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition.l1.location = "Cumana_town";
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition = "Fr6Olone_TalkWithOlone";
			LAi_LocationDisableOfficersGen("Cumana_town", true); //офицеров не пускать
			chrDisableReloadToLocation = false;
			NextDiag.CurrentNode = "Cupture_after";
			SetReturn_Gover_Dialog_Exit(NPChar);
			DialogExit();
        break;

	}
    UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

