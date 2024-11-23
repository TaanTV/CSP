// boal 13.05.05
int scx, scy, spx, spy, smxy;
int move_i, dir_i, dir_i_start;
bool openExit;
int  money_i, moneyOp_i;
int money_won;	// Общий выигрыш в рамках одной сессии. Равен деньгам игрока на старте игры минус текущие деньги игрока, которые обновляются в процессе игры
string money_s = "silver";
string cards_pack = "CARDS";    // файл колоды
string sukno = "card_sukno_03.tga"; // файл сукна

ref npchar;

int cardsPack[36], cardsP[36], cardsN[36];
int howCard;

int howPchar, howNpchar;
int iRate, iMoneyP, iMoneyN, iChest, iExpRate;
int bStartGame;

int iTurnGame;
int iHeroLose, iHeroWin;
int randPlaceCoinSize = 30;
int randPlaceCoin[99];

void InitInterface(string iniName)
{
    GameInterface.title = "";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("My_eventMoveImg","MoveImg",0);
	SetEventHandler("My_eStartGame","StartGame",0);
	SetEventHandler("My_eOpenCards","OpenCards",0);

    scx = 114;
    scy = 170;

    spx = 172;
    spy = 188;

    openExit = false;  // можно ли прервать игру

    pchar = GetMainCharacter();

    iRate  = sti(pchar.GenQuest.Cards.iRate); // ставки золотых

    npchar = GetCharacter(sti(pchar.GenQuest.Cards.npcharIdx));

    if (iRate <= 99)            //WW  прокачка фортуны  от суммы ставки
    {   money_s = "silver";
        iExpRate = 1;
        sukno = "interfaces\cardAndDice\card_sukno_03.tga";
        cards_pack = "CARDS2";
    }
    if (iRate >= 100)
    {   
        money_s = "silver";
        iExpRate = 2;
        sukno = "interfaces\cardAndDice\card_sukno_03.tga";
        cards_pack = "CARDS2";
    }
    if (iRate >= 250)
    {   
        money_s = "silver";
        iExpRate = 3;
        sukno = "interfaces\cardAndDice\card_sukno_02.tga";
        cards_pack = "CARDS1";
    }
    if (iRate >= 500)
    {   
        money_s = "silver";
        iExpRate = 4;
        sukno = "interfaces\cardAndDice\card_sukno_02.tga";
        cards_pack = "CARDS1";
    }
    if (iRate >= 600)
    {    
        money_s = "gold";
        iExpRate = 5;
        sukno = "interfaces\cardAndDice\card_sukno_02.tga";
        cards_pack = "CARDS1";
    }
    if (iRate >= 700)
    {    
        money_s = "silver";
        sukno = "interfaces\cardAndDice\card_sukno_01.tga";
        cards_pack = "CARDS";
        iExpRate = 6;
    }
    if (iRate >= 800)
    {    
        money_s = "silver";
        sukno = "interfaces\cardAndDice\card_sukno_01.tga";
        cards_pack = "CARDS";
        iExpRate = 8;
    }
    if (iRate >= 1000)
    {    
        money_s = "gold";
        sukno = "interfaces\cardAndDice\card_sukno.tga";
        cards_pack = "CARDS3";
        iExpRate = 10;
    }
    if (iRate >= 5000)
    {    
        money_s = "gold";
        sukno = "interfaces\cardAndDice\card_sukno.tga";
        cards_pack = "CARDS3";
        iExpRate = 25;
    }
    /* Обновляем ситец на столе */
    SetNewPicture("SCROLLPICT", sukno);
    
    /* Размер монетки */
	smxy = 70;
    
    CreateImage("BLANK","","", 0, 0, 0, 0); // выше всех

	CreateImage("Pack",cards_pack,"pack", 40, 203, 40 + spx, 203 + spy);

	SetNewPicture("ICON_1", "interfaces\PORTRAITS\128\face_" + Npchar.faceId+ ".tga");
    SetNewPicture("ICON_2", "interfaces\PORTRAITS\128\face_" + pchar.faceId+ ".tga");

    if (rand(1) == 1)
    {
        dir_i  = -1;  // кто ходит - комп
    }
    else
    {
        dir_i  = 1;  // кто ходит - ГГ
    }
    dir_i_start = dir_i; // запомним кто начал

    CreateString(true,"Beta_P", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 140, 370, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_N", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 140, 210, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_MoneyN", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 460, 210, SCRIPT_ALIGN_LEFT,1.0);

    // новая игра
    money_won = sti(pchar.Money);	// Сохраняем начальное кол-во денег игрока за сессию
    NewGameBegin();
    iTurnGame = 1; // игра первая
	WaitDate("",0,0,0, 0, 5);
	SetFormatedText("INFO_TEXT_DATE", GetQuestBookData());
    iHeroLose = 0;
    iHeroWin  = 0;

    SetFormatedText("WIN_LOSE", GetConvertStrWithReplace("Variable_boal_cards_1", "Interface.txt", "#space#", " ") +iHeroWin + GetConvertStrWithReplace("Variable_boal_cards_2", "Interface.txt", "#space#", " ") +iHeroLose));
}

void ProcessBreakExit()
{
	Exit();
}

void ProcessCancelExit()
{
	Exit();
}

void Exit()
{
	if (npchar.id == "W_Chard" || npchar.id == "BlackBeardNPC")
	{
		if (npchar.id == "W_Chard")
		{
			if (iHeroWin < 5 && iHeroLose < 5) PlaySound("interface\knock.wav");
			else Exit2();
		}

		if (npchar.id == "BlackBeardNPC")
		{
			if (iHeroWin < 3 && iHeroLose < 3) PlaySound("interface\knock.wav");
			else Exit2();
		}
	}
	else
	{
		if (openExit)
		{
			/* Лог итогов игры выводим до удаления переменных. Для нуля выводим "Потрачено" */
			int money_won_tmp = iMoneyP - money_won;
			if(money_won_tmp > 0)
			{
				Log_Info(GetConvertStrWithReplace("Variable_CharacterUtilite_1", "Logs.txt", "#space#", " ") + money_won_tmp + GetConvertStrWithReplace("Variable_CharacterUtilite_2", "Logs.txt", "#space#", " "));
			}
			else
			{
				Log_Info(GetConvertStrWithReplace("Variable_CharacterUtilite_3", "Logs.txt", "#space#", " ") + abs(money_won_tmp)  + GetConvertStrWithReplace("Variable_CharacterUtilite_4", "Logs.txt", "#space#", " "));
			}
      DelEventHandler("InterfaceBreak","ProcessBreakExit");
			DelEventHandler("exitCancel","ProcessCancelExit");
			DelEventHandler("ievnt_command","ProcessCommandExecute");
			DelEventHandler("My_eventMoveImg","MoveImg");
			DelEventHandler("My_eStartGame","StartGame");
			DelEventHandler("My_eOpenCards","OpenCards");

			if (sti(pchar.GenQuest.Cards.SitType) == true)
			{
				DoQuestCheckDelay("exit_sit", 0.6);
			}
			interfaceResultCommand = RC_INTERFACE_SALARY_EXIT;

			Statistic_AddValue(Pchar, "GameCards_Win", iHeroWin);
			AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*5*iHeroWin);
			AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*2*iHeroLose);
			Statistic_AddValue(Pchar, "GameCards_Lose", iHeroLose);

			bQuestCheckProcessFreeze = true;
			//WaitDate("",0,0,0, 0, iTurnGame*5);
			bQuestCheckProcessFreeze = false;
			RefreshLandTime();
			EndCancelInterface(true);
		}
		else
		{
			PlaySound("interface\knock.wav");
		}
	}
}

void Exit2()
{
	if (openExit)
	{
		DelEventHandler("InterfaceBreak","ProcessBreakExit");
		DelEventHandler("exitCancel","ProcessCancelExit");
		DelEventHandler("ievnt_command","ProcessCommandExecute");
		DelEventHandler("My_eventMoveImg","MoveImg");
		DelEventHandler("My_eStartGame","StartGame");
		DelEventHandler("My_eOpenCards","OpenCards");

		if (sti(pchar.GenQuest.Cards.SitType) == true)
		{
			DoQuestCheckDelay("exit_sit", 0.6);
		}
		interfaceResultCommand = RC_INTERFACE_SALARY_EXIT;

		Statistic_AddValue(Pchar, "GameCards_Win", iHeroWin);
		AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*5*iHeroWin);
		AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*2*iHeroLose);
		Statistic_AddValue(Pchar, "GameCards_Lose", iHeroLose);

		if (npchar.id == "BlackBeardNPC" && iHeroWin >= 3) npchar.Cards = true;

		bQuestCheckProcessFreeze = true;
		//WaitDate("",0,0,0, 0, iTurnGame*5);
		bQuestCheckProcessFreeze = false;
		RefreshLandTime();
		EndCancelInterface(true);
	}
	else
	{
		PlaySound("interface\knock.wav");
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	ref chr = GetMainCharacter();

	switch(nodName)
	{
    	case "B_PACK":
    		if(comName=="activate" || comName=="click")
    		{
                if (openExit == true)
                {   // ещё одна игра
                    if (bStartGame != 100)
                    {
                        dir_i = -dir_i_start;
                        dir_i_start = dir_i;
                        iTurnGame++;
						WaitDate("",0,0,0, 0, 5);
						SetFormatedText("INFO_TEXT_DATE", GetQuestBookData());
                        NewGameBegin();
                        openExit = false;
                    }
                    else
                    {
                        PlaySound("interface\knock.wav");
                    }
                }
                else
                {   // ГГ берёт карты
                    if (bStartGame <2) break; // ещё сдают
                    if (bStartGame == 100) break; // открываемся

                    if (dir_i == 1 && (iMoneyP - iRate) < 0)
                    {
                        PlaySound("interface\knock.wav");
                        SetFormatedText("INFO_TEXT", GetConvertStrWithReplace("Variable_boal_cards_3", "Interface.txt", "#space#", " "));
                        break;
                    }
                    if (dir_i == -1 && (iMoneyN - iRate) < 0)
                    {
                        PlaySound("interface\knock.wav");
                        SetFormatedText("INFO_TEXT", GetConvertStrWithReplace("Variable_boal_cards_4", "Interface.txt", "#space#", " "));
                        break;
                    }

                    if (dir_i == 1)
                    {
                        move_i = 0;
                        PlaySound("interface\took_item.wav");
                        PostEvent("My_eventMoveImg", 100);

                        PutNextCoin();
                        money_i++;

                        iMoneyP = iMoneyP - iRate;
                        iChest += iRate;
                        howCard--;
                        cardsP[howPchar] = cardsPack[howCard];
                        howPchar++;
                    }
                    ShowMoney();
                }
    		}
    	break;

    	case "B_ICON_1":
    		if(comName=="activate" || comName=="click")
    		{
                if (dir_i == 1 && bStartGame != 100 && bStartGame > 1 && !openExit) // только передача хода или открываемся
                {
                    dir_i = -1; // смена хода
                    SetNextTip();
                    if (dir_i_start == -1) // комп начинал игру первый
                    {
                        SetFormatedText("INFO_TEXT", GetConvertStrWithReplace("Variable_boal_cards_5", "Interface.txt", "#space#", " "));
                        bStartGame = 100;
                        PostEvent("My_eOpenCards", 2000);
                    }
                    else
                    { // комп должен себе набрать
                        SetFormatedText("INFO_TEXT", GetConvertStrWithReplace("Variable_boal_cards_6", "Interface.txt", "#space#", " "));

                        move_i = 0;
                        PlaySound("interface\took_item.wav");
                        PostEvent("My_eventMoveImg", 500);

                        PutNextCoinOp();
                        moneyOp_i++;
                        iMoneyN = iMoneyN - iRate;
                        iChest += iRate;
                        howCard--;
                        cardsN[howNpchar] = cardsPack[howCard];
                        howNpchar++;
                        ShowMoney();
                    }
                }
                else
                {
                    PlaySound("interface\knock.wav");
                }
    		}
    	break;

    	case "B_ICON_2":
    		if(comName=="activate" || comName=="click")
    		{
                //PlaySound("interface\knock.wav");
    		}
    	break;
	}
}

void MoveImg()
{
    CreateImage("BLANK",cards_pack,"blank", 90+move_i*25, 210+ dir_i*move_i*22, 90 + scx+move_i*25, 210 + scy + dir_i*move_i*22);
    move_i++;
    if (move_i < 10)
    {
        PostEvent("My_eventMoveImg", 60);
    }
    else
    {
        CreateImage("BLANK","","", 0, 0, 0, 0);
        PlaySound("interface\button3.wav");
        // перерисуем все карты на руках
        RedrawCards();

        // начало игры, по карте каждому -->
        if (bStartGame < 2)
        {
            dir_i = -dir_i; // смена хода
            bStartGame++;
            if (bStartGame == 1)  PostEvent("My_eStartGame", 500);
        }
        // начало игры, по карте каждому <--
        SetNextTip();
        BetaInfo();
        CheckGame();
    }
}

void PutNextCoin()
{
	if (npchar.id != "W_Chard")
	{
		CreateImage("Money_"+money_i,cards_pack,money_s, 280+money_i*3, 280-money_i*3, 280+money_i*3 + smxy, 280-money_i*3 + smxy);
	}
}
void PutNextCoinOp()
{
	if (npchar.id != "W_Chard")
	{
		CreateImage("Money_"+(18+moneyOp_i),cards_pack,money_s, 380+moneyOp_i*3, 280-moneyOp_i*3, 380+moneyOp_i*3 + smxy, 280-moneyOp_i*3 + smxy);
	}
}

void PackShake()
{
    // тасуем карты
    int  i;
    bool ok;
    int  nextCard;

    howCard = 0;
    while (howCard <36)
    {
        ok = false;
        while (!ok)
        {
            ok = true;
            nextCard = rand(35)+1;
            for (i=0; i<howCard; i++)
        	{
                if (nextCard == cardsPack[i])
                {
                    ok = false;
                    break;
                }
        	}
        	if (ok)
        	{
                cardsPack[howCard] = nextCard;
                //log_info(""+nextCard);
                howCard++;

        	}
    	}
    }
}
void RedrawCards()
{
    int i;
    string sTemp;
    int k;
    k = scx;
    if (howPchar > 6)
    {
        k = scx/2;
    }
    for (i=0; i<howPchar; i++)
	{
        sTemp = "c"+cardsP[i];
        CreateImage("PCard"+i,cards_pack, NullCharacter.Cards.(sTemp).pic, 400 - howPchar*k/2 + i*k , 394, 400 - howPchar*k/2 + i*k + scx, 394 + scy);
	}
	k = scx;
	if (howNpchar > 6)
    {
        k = scx/2;
    }
	for (i=0; i<howNpchar; i++)
	{
        sTemp = "c"+cardsN[i];
        sTemp = NullCharacter.Cards.(sTemp).pic;
        if (!openExit)
        {
            sTemp = "blank";
        }
        CreateImage("PCard"+(18+i),cards_pack, sTemp, 400 - howNpchar*k/2 + i*k , 36, 400 - howNpchar*k/2 + i*k + scx, 36 + scy);
	}
}
void RedrawDeck()
{
    // монетки с запасом
    int i;
    for (i=35; i>=0; i--)
	{
        CreateImage("Money_"+i, "","", 0, 0, 0, 0);
        CreateImage("PCard"+i, "", "", 0, 0, 0, 0);
	}
	money_i = 0; // индекс монетки
    moneyOp_i = 0;
    iChest = 0; // на кону

    iMoneyP = sti(pchar.Money);
    iMoneyN = sti(npchar.Money);
    ShowMoney();

    // тасуем карты
    PackShake();
    howPchar  = 0; // карты на руках
    howNpchar = 0;
    SetNextTip();
    BetaInfo();
}

void SetNextTip()
{
    if (dir_i == 1)
    {
        if (bStartGame <2)
        {
            SetFormatedText("INFO_TEXT",GetConvertStrWithReplace("Variable_boal_cards_7", "Interface.txt", "#space#", " ")+NewStr()+GetConvertStrWithReplace("Variable_boal_cards_8", "Interface.txt", "#space#", " "));
        }
        else
        {
            SetFormatedText("INFO_TEXT",LinkRandPhrase(GetConvertStrWithReplace("Variable_boal_cards_9", "Interface.txt", "#space#", " "), GetConvertStrWithReplace("Variable_boal_cards_10", "Interface.txt", "#space#", " "), RandSwear() + GetConvertStrWithReplace("Variable_boal_cards_11", "Interface.txt", "#space#", " ")));
        }
    }
    else
    {
        if (bStartGame <2)
        {
            SetFormatedText("INFO_TEXT",GetConvertStrWithReplace("Variable_boal_cards_12", "Interface.txt", "#space#", " ")+NewStr()+GetConvertStrWithReplace("Variable_boal_cards_13", "Interface.txt", "#space#", " "));
        }
        else
        {
            SetFormatedText("INFO_TEXT",LinkRandPhrase(GetConvertStrWithReplace("Variable_boal_cards_14", "Interface.txt", "#space#", " "), GetConvertStrWithReplace("Variable_boal_cards_15", "Interface.txt", "#space#", " "), GetConvertStrWithReplace("Variable_boal_cards_16", "Interface.txt", "#space#", " ")));
        }
    }
}
int CountCardsP()
{
    int ret = 0;
    int i;
    string sTemp;

    for (i = 0; i < howPchar; i++)
    {
        sTemp = "c"+cardsP[i];
        ret += sti(NullCharacter.Cards.(sTemp).count);
    }
    return ret;
}

int CountCardsN()
{
    int ret = 0;
    int i;
    string sTemp;

    for (i = 0; i < howNpchar; i++)
    {
        sTemp = "c"+cardsN[i];
        ret += sti(NullCharacter.Cards.(sTemp).count);
    }
    return ret;
}
void BetaInfo()
{
	if (isEquippedArtefactUse(pchar, "Joker", 0.0, 2.0) && rand(100) < 5 + (GetCharacterSkill(pchar, SKILL_FORTUNE) / 20) + (GetCharacterSkill(pchar, SKILL_SNEAK) / 20) + (sti(Pchar.SPECIAL.Luck))) 		// Удача - 10%, Везение - 5%, Скрытность - 5%
	{
        SetFormatedText("CARD_PEEK", GetConvertStrWithReplace("Variable_boal_cards_17", "Interface.txt", "#space#", " ") + NextCardPack());
	}
	else
	{
        SetFormatedText("CARD_PEEK", "");
	}
    SetFormatedText("WIN_LOSE", GetConvertStrWithReplace("Variable_boal_cards_1", "Interface.txt", "#space#", " ") +iHeroWin + GetConvertStrWithReplace("Variable_boal_cards_2", "Interface.txt", "#space#", " ") +iHeroLose);
    if (bBettaTestMode)
    {
        GameInterface.strings.Beta_P       = "Beta_P " + CountCardsP();
        GameInterface.strings.Beta_N       = "Beta_N " + CountCardsN();
        SetFormatedText("CARD_PEEK", "Beta_Next " + NextCardPack());
        GameInterface.strings.Beta_MoneyN  = "Beta_MoneyN " + MakeMoneyShow(iMoneyN, MONEY_SIGN,MONEY_DELIVER);

        SetFormatedText("WIN_LOSE", GetConvertStrWithReplace("Variable_boal_cards_1", "Interface.txt", "#space#", " ") + (Statistic_AddValue(Pchar, "GameCards_Win", 0)+iHeroWin) + GetConvertStrWithReplace("Variable_boal_cards_2", "Interface.txt", "#space#", " ") + (Statistic_AddValue(Pchar, "GameCards_Lose", 0)+iHeroLose));
	}
	else
	{
        SetFormatedText("WIN_LOSE", GetConvertStrWithReplace("Variable_boal_cards_1", "Interface.txt", "#space#", " ") +iHeroWin + GetConvertStrWithReplace("Variable_boal_cards_2", "Interface.txt", "#space#", " ") +iHeroLose);
        ShowCashWinning();
        if (isEquippedArtefactUse(pchar, "Joker", 0.0, 2.0))
        {
            SetFormatedText("CARD_SUM", GetConvertStrWithReplace("Variable_boal_cards_2.2", "Interface.txt", "#space#", " ") + CountCardsP());
        }
	}
}
int NextCardPack()
{
    string sTemp;
    int ret;

    sTemp = "c"+cardsPack[howCard-1];
    ret = sti(NullCharacter.Cards.(sTemp).count);

    return ret;
}
// сдать карту
void StartGame()
{
    move_i = 0;

    PlaySound("interface\took_item.wav");
    PostEvent("My_eventMoveImg", 100);

    if (dir_i == 1)
    {
        PutNextCoin();
        money_i++;

        iMoneyP = iMoneyP - iRate;

        howCard--;
        cardsP[howPchar] = cardsPack[howCard];
        howPchar++;
    }
    else
    {
        PutNextCoinOp();
        moneyOp_i++;
        iMoneyN = iMoneyN - iRate;
        howCard--;
        cardsN[howNpchar] = cardsPack[howCard];
        howNpchar++;
    }
    iChest += iRate;
    ShowMoney();
}

void ShowMoney()
{
	if (npchar.id == "W_Chard")
	{
		for (int wCoins = 0; wCoins < randPlaceCoinSize; wCoins++)
		{
			if(wCoins < 10)
			{
				if (wCoins > 2 && wCoins < 8) money_s = "gold";
				else money_s = "silver";
			}
			else
			{
				if (wCoins > 11 && wCoins < 19) money_s = "silver";
				else money_s = "gold";
			}
			if ( randPlaceCoin[wCoins] == 0)
			{
				randPlaceCoin[wCoins] = rand(120)+1;
			}
			CreateImage("Money_"+(18+wCoins),cards_pack,money_s, 250+randPlaceCoin[wCoins]+wCoins*3, 230+randPlaceCoin[wCoins]-wCoins*3, 250+randPlaceCoin[wCoins]+wCoins*3 + smxy, 230+randPlaceCoin[wCoins]-wCoins*3 + smxy);
		}
        SetFormatedText("MONEY_IN_CHEST", MakeMoneyShow(iMoneyP-200000,MONEY_SIGN,MONEY_DELIVER));
        SetFormatedText("MONEY_ON_TABLE", MakeMoneyShow(200000,MONEY_SIGN,MONEY_DELIVER));
	}
	else
	{
        SetFormatedText("MONEY_IN_CHEST", MakeMoneyShow(iMoneyP,MONEY_SIGN,MONEY_DELIVER));
        SetFormatedText("MONEY_ON_TABLE", MakeMoneyShow(iChest,MONEY_SIGN,MONEY_DELIVER));
	}
    SetFormatedText("WIN_LOSE", GetConvertStrWithReplace("Variable_boal_cards_1", "Interface.txt", "#space#", " ") +iHeroWin + GetConvertStrWithReplace("Variable_boal_cards_2", "Interface.txt", "#space#", " ") +iHeroLose);
    ShowCashWinning();
    if (isEquippedArtefactUse(pchar, "Joker", 0.0, 2.0))
    {
        SetFormatedText("CARD_SUM", GetConvertStrWithReplace("Variable_boal_cards_2.2", "Interface.txt", "#space#", " ") + CountCardsP());
    }
}

bool CheckGame()
{
    string sTemp;
    int   ok = 0;
    bool  ok1;
    bool  ret = false;

    if (CountCardsP() > 21)
    {
        ok = -1;
        sTemp = GetConvertStrWithReplace("Variable_boal_cards_26", "Interface.txt", "#space#", " ")+NPCharSexPhrase(npchar, "", GetConvertStrWithReplace("Variable_boal_cards_27", "Interface.txt", "#space#", " "))+".";
        iHeroLose++;
    }
    if (CountCardsN() > 21)
    {
        ok = 1;
        sTemp = RandSwear() + GetConvertStrWithReplace("Variable_boal_cards_28", "Interface.txt", "#space#", " ")+ GetSexPhrase("",GetConvertStrWithReplace("Variable_boal_cards_29", "Interface.txt", "#space#", " ")) +".";
        iHeroWin++;
    }

    if (ok != 0)
    {
		EndGameCount(ok);
		if (ok == 1) RedrawCards(); // покажем перебор
		if (npchar.id == "W_Chard" || npchar.id == "BlackBeardNPC")
		{
			if (npchar.id == "W_Chard") sTemp = CheckChardGames(sTemp);
			if (npchar.id == "BlackBeardNPC") sTemp = CheckBlackGames(sTemp);
		}
		else
		{
			if (CheckNextGame() && rand(10) < 10) // есть деньги на игру
			{
				sTemp += NewStr() + RandPhraseSimple(GetConvertStrWithReplace("Variable_boal_cards_30", "Interface.txt", "#space#", " "),GetConvertStrWithReplace("Variable_boal_cards_31", "Interface.txt", "#space#", " "));
			}
			else
			{
				bStartGame = 100; //признах запрета новой игры
				sTemp += NewStr() + GetConvertStrWithReplace("Variable_boal_cards_32", "Interface.txt", "#space#", " ");
			}
		}
		SetFormatedText("INFO_TEXT", sTemp);
        ShowMoney();
		ret = true;
    }
    else
    {
        ok1 = (CountCardsN() > 16) && (CountCardsN() <22);
        // жухло!!!!! -->
		int zhuhlo = rand(12);
		int zhuhlo1 = rand(10);
		if (npchar.id == "W_Chard")
		{
			zhuhlo = 33;
			zhuhlo1 = 33
		}
		if (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) < zhuhlo)
		//if (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) + makeint(isEquippedArtefactUse(pchar, "Joker", 0.0, 2.0)) < zhuhlo)
        {
            if (ok1 && (CountCardsN() + NextCardPack()) <= 21)
            {
                ok1 = false;
            }
			if (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) < zhuhlo1 && CountCardsN() < 17 &&  (CountCardsN() + NextCardPack()) > 21)
			//if (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) - makeint(isEquippedArtefactUse(pchar, "Joker", 0.0, 2.0)) < zhuhlo1 && CountCardsN() < 17 &&  (CountCardsN() + NextCardPack()) > 21)          
            {
                ok1 = true;
            }
        }

        // жухло!!!!! <--
        if (ok1 || (iMoneyN - iRate) < 0)
        {
            if (dir_i == -1 && dir_i_start == 1) // комп ходит последним
            {
                SetFormatedText("INFO_TEXT", GetConvertStrWithReplace("Variable_boal_cards_33", "Interface.txt", "#space#", " "));
                bStartGame = 100;
                PostEvent("My_eOpenCards", 2000);
                ret = true;
            }
            if (dir_i == -1 && dir_i_start == -1) // комп начинает
            {
                dir_i = 1;
                SetFormatedText("INFO_TEXT", GetConvertStrWithReplace("Variable_boal_cards_34", "Interface.txt", "#space#", " "));
                ret = true;
            }
        }
        else
        {
            if (dir_i == -1 && bStartGame >= 2) // комп играет сам
            {
                move_i = 0;
                PlaySound("interface\took_item.wav");
                PostEvent("My_eventMoveImg", 500);

                PutNextCoinOp();
                moneyOp_i++;
                iMoneyN = iMoneyN - iRate;
                iChest += iRate;
                howCard--;
                cardsN[howNpchar] = cardsPack[howCard];
                howNpchar++;
                ShowMoney();

                ret = true;
            }
        }
    }
    return ret;
}

void NewGameBegin()
{
    RedrawDeck(); // новая игра
    bStartGame = 0;
    SetFormatedText("INFO_TEXT",GetConvertStrWithReplace("Variable_boal_cards_35", "Interface.txt", "#space#", " ")+NewStr()+GetConvertStrWithReplace("Variable_boal_cards_36", "Interface.txt", "#space#", " "));
    PostEvent("My_eStartGame", 1000);
}

void EndGameCount(int who)
{
    openExit = true;
    if (who == 1) // ГГ
    {
        /* Отключаем вывод лога для каждого изменения денег ГГ. В конце игры выведем одно сообщение. Отключение сбрасывается после вызова AddMoneyToCharacter */
        setShowMoneyLogValue(false);
        AddMoneyToCharacter(pchar, iChest - (sti(pchar.Money) - iMoneyP));
        AddMoneyToCharacter(npchar,  -(sti(npchar.Money) - iMoneyN));
    }
    else
    {
        /* Отключаем вывод лога для каждого изменения денег ГГ. В конце игры выведем одно сообщение. Отключение сбрасывается после вызова AddMoneyToCharacter */
        setShowMoneyLogValue(false);
        AddMoneyToCharacter(pchar, -(sti(pchar.Money) - iMoneyP));
        AddMoneyToCharacter(npchar, iChest - (sti(npchar.Money) - iMoneyN));
    }

    /* Обновляем iMoneyP для актуального кол-ва денег у ГГ и строки выигрыша */
    iMoneyP = sti(pchar.Money);
}

void OpenCards();
{
   if (CheckAttribute(npchar, "PGGAI")) PGG_ChangeRelation2MainCharacter(npchar, 2);

   string sTemp;
    if (CountCardsP() > makefloat(CountCardsN() + 0.1*dir_i_start)) // преимущество тому, кто сдает (те ходит последним)
    {
        EndGameCount(1);
        sTemp = RandSwear() + GetConvertStrWithReplace("Variable_boal_cards_37", "Interface.txt", "#space#", " ")+ GetSexPhrase("",GetConvertStrWithReplace("Variable_boal_cards_38", "Interface.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_boal_cards_39", "Interface.txt", "#space#", " ") + CountCardsP() +GetConvertStrWithReplace("Variable_boal_cards_40", "Interface.txt", "#space#", " ") + CountCardsN()+"." ;
        iHeroWin++;
    }
    else
    {
        EndGameCount(-1);
        sTemp = GetConvertStrWithReplace("Variable_boal_cards_41", "Interface.txt", "#space#", " ") + CountCardsN() +GetConvertStrWithReplace("Variable_boal_cards_42", "Interface.txt", "#space#", " ") + CountCardsP()+GetConvertStrWithReplace("Variable_boal_cards_43", "Interface.txt", "#space#", " ")+NPCharSexPhrase(npchar, "", GetConvertStrWithReplace("Variable_boal_cards_44", "Interface.txt", "#space#", " "))+"!";
        iHeroLose++;
    }
	if (npchar.id == "W_Chard" || npchar.id == "BlackBeardNPC")
	{
		if (npchar.id == "W_Chard") sTemp = CheckChardGames(sTemp);
		if (npchar.id == "BlackBeardNPC") sTemp = CheckBlackGames(sTemp);
	}
	else
	{
		if (CheckNextGame() && rand(10) < 10) // есть деньги на игру
		{
			sTemp += NewStr() + RandPhraseSimple(GetConvertStrWithReplace("Variable_boal_cards_45", "Interface.txt", "#space#", " "),GetConvertStrWithReplace("Variable_boal_cards_46", "Interface.txt", "#space#", " "));
			bStartGame = 2;
		}
		else
		{
			bStartGame = 100; //признах запрета новой игры
			sTemp += NewStr() + GetConvertStrWithReplace("Variable_boal_cards_47", "Interface.txt", "#space#", " ");
		}
	}
    SetFormatedText("INFO_TEXT", sTemp);
    RedrawCards();
    ShowMoney();
}
bool CheckNextGame()
{
    bool ret = true;
    if (iRate*3 > iMoneyN) ret = false;
    if (iRate*3 > iMoneyP) ret = false;

    return ret;
}

string CheckChardGames(string sTemp)
{
	if (iHeroWin < 5 && iHeroLose < 5)
	{
		sTemp += NewStr() + GetConvertStrWithReplace("Variable_boal_cards_48", "Interface.txt", "#space#", " ");
		bStartGame = 2;
	}
	else
	{
		bStartGame = 100;
		if (iHeroWin == 5)
		{
			sTemp = RandSwear() + GetConvertStrWithReplace("Variable_boal_cards_49", "Interface.txt", "#space#", " ");
			pchar.WhisperWonSword = true;
		}
		else
		{
			sTemp = GetConvertStrWithReplace("Variable_boal_cards_50", "Interface.txt", "#space#", " ");
			AddMoneyToCharacter(pchar, -200000);
		}
		sTemp += NewStr() + GetConvertStrWithReplace("Variable_boal_cards_51", "Interface.txt", "#space#", " ");
	}
	return sTemp;
}

string CheckBlackGames(string sTemp)
{
	if (iHeroWin < 3 && iHeroLose < 3)
	{
		sTemp += NewStr() + GetConvertStrWithReplace("Variable_boal_cards_52", "Interface.txt", "#space#", " ");
		bStartGame = 2;
	}
	else
	{
		bStartGame = 100;
		openExit = true;
		if (iHeroWin == 3)
		{
			sTemp = RandSwear() + GetConvertStrWithReplace("Variable_boal_cards_53", "Interface.txt", "#space#", " ")+ GetSexPhrase("",GetConvertStrWithReplace("Variable_boal_cards_54", "Interface.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_boal_cards_55", "Interface.txt", "#space#", " ");
		}
		else
		{
			sTemp = GetConvertStrWithReplace("Variable_boal_cards_56", "Interface.txt", "#space#", " ");
		}
		sTemp += NewStr() + GetConvertStrWithReplace("Variable_boal_cards_57", "Interface.txt", "#space#", " ");
	}
	return sTemp;
}

/* Обновить строку с денежным выигрышем или проигрышем */
void ShowCashWinning()
{
    string sTemp;
    if((iMoneyP - money_won) >= 0)
    {
        
        sTemp = GetConvertStrWithReplace("Variable_boal_cards_2.1", "Interface.txt", "#space#", " ") + (iMoneyP - money_won);
    }
    else
    {
        sTemp = GetConvertStrWithReplace("Variable_boal_cards_2.1.1", "Interface.txt", "#space#", " ") + (money_won - iMoneyP);
    }
    SetFormatedText("MONEY_WON", sTemp);
}

