object MerchantParam;
bool trap = false;

string CreateMerchant(int ination)
{
    ref chref, sld;
    aref  MerPrm;

    makearef(MerPrm, MerchantParam);

    //for (int n = 0; n<=4; n++ )
    //{

        //Map_ReleaseQuestEncounter( NationShortName(sti(MerPrm.nation))+"_QuestMerchant");
        //Group_DeleteGroup("Sea_"+NationShortName(sti(MerPrm.nation))+"_QuestMerchant");
    //}

    int iChar = NPC_GenerateCharacter(NationShortName(sti(MerPrm.nation))+"_QuestMerchant", "off_spa_2", "man", "man", 5, sti(MerPrm.nation), 6, true));
    makeref(chref, Characters[iChar]);
    SetMerchantShip(chref, sti(MerPrm.QuestGoodsIdx));
	SetFantomParamHunter(chref); //крутые парни
	string sGroup = "Sea_"+chref.id
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    Group_SetType(sGroup,"trade");
    //Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);

    ref rGroup = Group_GetGroupByID(sGroup);
    rGroup.Task = AITASK_MOVE;
    Group_LockTask(sGroup);

    Group_AddCharacter(sGroup, chref.id);
    Group_SetGroupCommander(sGroup, chref.id);

    chref.mapEnc.type = "trade";
    chref.mapEnc.Name = GetConvertStrWithReplace("Variable_MerchantOnMap_1", "Names.txt", "#space#", " ");
    //chref.mapEnc.Task = AITASK_MOVE; // ?


    Map_CreateTrader(MerPrm.sColony, MerPrm.sNextColony, chref.id, 5);
    MerPrm.CapIndex = iChar;

    string sQuest = NationShortName(sti(MerPrm.nation))+"_QuestMerchant_1";
	pchar.quest.(sQuest).win_condition.l1 = "Character_sink";
    pchar.quest.(sQuest).win_condition.l1.character = chref.id;
    pchar.quest.(sQuest).function= "KillMerchant";

    sQuest = NationShortName(sti(MerPrm.nation))+"_QuestMerchant_2";

	pchar.quest.(sQuest).win_condition.l1 = "Character_Capture";
    pchar.quest.(sQuest).win_condition.l1.character = chref.id;
    pchar.quest.(sQuest).function= "CaptureMerchant";





    int gcount = rand(3)-1;
    if (gcount < 0 || makeint(pchar.rank) < 5) gcount = 0;

    for (int i = 0; i<gcount; i++)
    {
        iChar = NPC_GenerateCharacter(NationShortName(sti(MerPrm.nation))+"_QuestMerchantGuard_"+i, "off_spa_2", "man", "man", 5, sti(MerPrm.nation), 20, true));
        makeref(sld, Characters[iChar]);
        SetShipHunter(sld);
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.Ship.Mode = "war";
        Group_AddCharacter(sGroup, sld.id);

    }
    MerPrm.gcount = gcount;


    return chref.Ship.Name;
}

bool MerchantPrepare(int Mnation)
{

    ref  MerPrm;
    int  i;

    makeref(MerPrm, MerchantParam);

    i = 0;
    MerPrm.nation = PIRATE;
    while (GetNationRelation(sti(MerPrm.nation), Mnation) == RELATION_ENEMY && i < 15)
    {
        MerPrm.nation = rand(PIRATE);
        i++;
    }
    if (i == 15)
    {
        MerPrm.nation = PIRATE;
    }

     // goods
    switch (rand(12 + makeint(GetCharacterSPECIALSimple(pchar, SPECIAL_L)/5)))
    {
        case 0 :
            MerPrm.QuestGoodsIdx = GOOD_SILVER;
        break;
        case 1 :
            MerPrm.QuestGoodsIdx = GOOD_GOLD;
        break;
        case 2 :
            MerPrm.QuestGoodsIdx = GOOD_COFFEE;
        break;
        case 3 :
            MerPrm.QuestGoodsIdx = GOOD_MAHOGANY;
        break;
        case 4 :
            MerPrm.QuestGoodsIdx = GOOD_SLAVES;
        break;
        case 5 :
            MerPrm.QuestGoodsIdx = GOOD_FOOD;
        break;
        case 6 :
            MerPrm.QuestGoodsIdx = GOOD_WEAPON;
        break;
        case 7 :
            MerPrm.QuestGoodsIdx = GOOD_TOBACCO;
        break;
        case 8 :
            MerPrm.QuestGoodsIdx = GOOD_ALE;
        break;
        case 9 :
            MerPrm.QuestGoodsIdx = GOOD_RUM;
        break;
        case 10 :
            MerPrm.QuestGoodsIdx = GOOD_SUGAR;
        break;
        case 11 :
            MerPrm.QuestGoodsIdx = GOOD_SANDAL;
        break;
        case 12 :
            MerPrm.QuestGoodsIdx = GOOD_PAPRIKA;
        break;
		case 13 :
            MerPrm.QuestGoodsIdx = GOOD_SILVER;
        break;
		case 14 :
            MerPrm.QuestGoodsIdx = GOOD_GOLD;
        break;

    }
    string HomeColony = All_GetColony();
    int iFColony = FindNonEnemyColonyForAdventure(sti(MerPrm.nation), HomeColony, true));

    if (HomeColony!="none" && iFColony != -1 )
    {

        if (rand(1)==1)
        {
            MerPrm.sColony = "none";
            MerPrm.sNextColony = HomeColony;
            Log_TestInfo(MerPrm.sColony+"-->"+MerPrm.sNextColony);
        }
        else
        {
            string FriendColony = Colonies[iFColony].id;
            MerPrm.sColony = HomeColony;
            MerPrm.sNextColony = FriendColony;
            Log_TestInfo(MerPrm.sColony+"-->"+MerPrm.sNextColony);
        }
        return true;
    }
    return false;
}

int SetShipTypeMerchant(ref Cap)
{
    int iShip, hcrew, irank;
	int iClassMin, iClassMax;

    if(makeint(pchar.rank) > 15)
    {
        irank = rand(2) + 3;
		iClassMin = 3; 
		iClassMax = 2;
    }
    if(makeint(pchar.rank) > 10 && makeint(pchar.rank) < 16)
    {
        irank = rand(2) + 2;
		iClassMin = 4; 
		iClassMax = 3;
    }
    if(makeint(pchar.rank) > 5 && makeint(pchar.rank) < 11)
    {
        irank = rand(2) + 1;
		iClassMin = 5; 
		iClassMax = 4;
    }
    if(makeint(pchar.rank) < 6)
    {
        iClassMin = 6;
		iClassMax = 5;
        irank = 0;
    }
	iShip = GetShipTypeExt(iClassMin, iClassMax, "Merchant", sti(Cap.nation))
    SetRandomNameToShip(Cap);
    Cap.Ship.Type = GenerateShipExt(iShip, 1, Cap);
    SetBaseShipData(Cap);

    hcrew = GetMaxCrewQuantity(Cap);
    SetCrewQuantity(Cap, hcrew);

    DeleteAttribute(Cap,"ship.sails");
	RepairMasts(Cap);
    DeleteAttribute(Cap,"ship.blots");

    if (sti(Cap.nation == PIRATE)) //navy fix -- приведение типов.
    {
        Fantom_SetCannons(Cap, "pirate");
        Fantom_SetBalls(Cap, "pirate");
    }
    else
    {
        Fantom_SetCannons(Cap, "trade");
        Fantom_SetBalls(Cap, "trade");
    }

    return irank;
}

void SetMerchantShip(ref Cap, int igoods)
{
    int hcrew, irank;
    int killMax;

    irank = SetShipTypeMerchant(Cap);
    SetRandomNameToCharacter(Cap);
    SetCaptanModelByEncType(Cap, "trade");//
    Cap.Ship.Mode = "trade";
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ref MerPrm;
    makeref(MerPrm, MerchantParam);
    int killM = Statistic_AddValue(GetMainCharacter(), "Rob"+NationShortName(sti(MerPrm.nation))+"MerchantOnMap", 0)
    if (MOD_SKILL_ENEMY_RATE*3 > 5) // 20/01/07 homo
    {
        killMax = makeint(3+(10 - MOD_SKILL_ENEMY_RATE*3)/2);
    }
    else
    {
        killMax = 6;
    }
    if  (killM >= killMax && rand(1)== 0 )
    {
        //Cap.AlwaysEnemy = true;
        //на тест
        SetCaptanModelByEncType(Cap, "war");
        //Cap.Ship.Mode = "war";
        Cap.greeting = "soldier_arest";
        Cap.DontRansackCaptain = true; //квестовые не сдаются
        Cap.dialog.filename = "Capitans_dialog.c";
		Cap.dialog.currentnode = "MerchantTrap_Abordage";
		Cap.DeckDialogNode = "First time";
        Statistic_AddValue(GetMainCharacter(), "Rob"+NationShortName(sti(MerPrm.nation))+"MerchantOnMap", -( killM + 1));

        hcrew = GetMaxCrewQuantity(Cap);
		//SetCrewQuantityOverMax(Cap, 2*hcrew);
		SetCrewQuantity(Cap, hcrew);
        ChangeCrewExp(pchar, "Soldiers", 90);  // за счет солдат - засада для ГГ
        trap = true;
    }
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (!trap)
    {
        int iSpace = GetCharacterFreeSpace(Cap, igoods);

        Log_TestInfo("irank = "+irank);
        float del = makefloat(7-irank+rand(1))/10; //eddy. товаров меньше
        if (del > 1.0 ) del = 1;
        Log_TestInfo("goods load = "+iSpace+"/"+makeint(iSpace*del));
        iSpace = makeint(iSpace*del); // чтоб не так жирно было
        Fantom_SetCharacterGoods(Cap, igoods, iSpace,1);
    }
}

string All_GetColony();
{
    int locnum = FindLocation(pchar.location);
    if (locnum != -1 )
    {
		if(CheckAttribute(locations[locnum],"townsack")) // если в городе <-- ugeen fix
		{
			if (locations[locnum].townsack == "Bahames") locations[locnum].townsack = "Nassau";//TO DO - удалить эту подмену позже - просто фикс, чтоб обойтись без НИ
			return locations[locnum].townsack;
		}
		else // а если в джунглях или на побережье?
		{
			if(CheckAttribute(locations[locnum],"islandIdAreal")) // если на острове или Мэйне несколько городов
			{
				return GetCityNameByIsland(locations[locnum].islandIdAreal);
			}
			else // остров с одним городом
			{
				return GetCityNameByIsland(locations[locnum].islandId);
			}
		}
    }
    if (!IsEntity(worldMap)) // в море
    {
        return Sea_FindNearColony();
    }
    return "none";
}

void KillMerchant(string temp)
{
    AddTemplRumour("MerchantRumour", id_counter+1);
    DieMerchant(5);
}


void CaptureMerchant(string temp)
{
    int qind;
    ref MerPrm;
    makeref(MerPrm, MerchantParam);
    if (trap)
    {
        qind = 6;
        Log_TestInfo("TRADER_TRAP!!!");
        string stext1 = GetConvertStrWithReplace("Variable_MerchantOnMap_1", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_2", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_3", "AddRumours.txt", "#space#", " ")) +" - "+GetFullName(pchar)+", "+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_4", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_5", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_MerchantOnMap_6", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_7", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_8", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_MerchantOnMap_9", "AddRumours.txt", "#space#", " ")+NationNameGenitive(sti(MerPrm.ination))+GetConvertStrWithReplace("Variable_MerchantOnMap_10", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_11", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_12", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_MerchantOnMap_13", "AddRumours.txt", "#space#", " ")+pchar.name+GetConvertStrWithReplace("Variable_MerchantOnMap_14", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_15", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_16", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_MerchantOnMap_17", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_18", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_19", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_MerchantOnMap_20", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_21", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_22", "AddRumours.txt", "#space#", " ")) +" "+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_23", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_24", "AddRumours.txt", "#space#", " ")) +" "+GetFullName(pchar)+".";
        string stext2 = GetConvertStrWithReplace("Variable_MerchantOnMap_25", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_26", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_27", "AddRumours.txt", "#space#", " ")) +" - "+GetFullName(pchar)+", "+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_28", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_29", "AddRumours.txt", "#space#", " ")) + GetConvertStrWithReplace("Variable_MerchantOnMap_30", "AddRumours.txt", "#space#", " ") + NationNameGenitive(sti(MerPrm.ination))+GetConvertStrWithReplace("Variable_MerchantOnMap_31", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_32", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_33", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_MerchantOnMap_34", "AddRumours.txt", "#space#", " ")+ GetSexPhrase(GetConvertStrWithReplace("Variable_MerchantOnMap_35", "AddRumours.txt", "#space#", " "),GetConvertStrWithReplace("Variable_MerchantOnMap_36", "AddRumours.txt", "#space#", " ")) +GetConvertStrWithReplace("Variable_MerchantOnMap_37", "AddRumours.txt", "#space#", " ");
        AddSimpleRumour(stext1, sti(MerPrm.ination)+10, 30, 3);
        AddSimpleRumour(stext2, sti(MerPrm.ination), 30, 3);

    }
    else
    {
       qind = 4;
       AddTemplRumour("MerchantRumour", id_counter+1);
    }
    DieMerchant(qind);



}


void DieMerchant(int qind)
{
    ref MerPrm;
    makeref(MerPrm, MerchantParam);

    if (sti(MerPrm.ination)!= PIRATE )
    {
        Statistic_AddValue(GetMainCharacter(), "Rob"+NationShortName(sti(MerPrm.ination))+"MerchantOnMap", 1);
    }

    AddQuestRecord("MerchantOnMap", qind);
    AddQuestUserData("MerchantOnMap", "sSex", GetSexPhrase("","а"));
    AddQuestUserData("MerchantOnMap", "sShipName", MerPrm.ShipName);
    AddQuestUserData("MerchantOnMap", "sQuestGoodsIdx", MerPrm.QuestGoodsIdx);
    AddQuestUserData("MerchantOnMap", "snation", MerPrm.nation);

    CloseQuestHeader("MerchantOnMap");
    Map_ReleaseQuestEncounter(NationShortName(sti(MerPrm.ination))+"_QuestMerchant");
    //fix homo
    trap = false; //fix
    MerPrm.active = false;

}

void ClearMerchant(string stemp)
{
    ref MerPrm;
    makeref(MerPrm, MerchantParam);
    CloseQuestHeader("MerchantOnMap");
    Map_ReleaseQuestEncounter(NationShortName(sti(MerPrm.ination))+"_QuestMerchant");
    Group_DeleteGroup("Sea_"+NationShortName(sti(MerPrm.ination))+"_QuestMerchant");
    MerPrm.active = false;
}

string GenerateMerchant()
{
        ref MerPrm, sld;
        ref CurTpl
        string reztext, tresult, sdirect;
        int lngFileID;
        string HomeColony = All_GetColony();
        int iNation = sti(Colonies[FindColony(HomeColony)].nation)
        if ( MerchantPrepare(iNation) )
        {

            makeref(MerPrm, MerchantParam);
            MerPrm.ShipName = CreateMerchant(iNation);


            if (MerPrm.sColony == "none")
            {
                MerPrm.sColony = Colonies[FindNonEnemyColonyForAdventure(iNation, HomeColony, true)].id;
                sdirect = "To";
            }
            Characters[sti(MerPrm.CapIndex)].FromColony = MerPrm.sColony;


            int tNum = TplNameToNum("MerchantOnMap");
            makeref(CurTpl,  templat[tNum]);
            lngFileID = LanguageOpenFile("RumourTexts.txt");
            string tid = CurTpl.name+sdirect+"_t"+rand(sti(CurTpl.texts)-1);
            reztext = LanguageConvertString(lngFileID, tid);
            MerPrm.ination = MerPrm.nation; // fix
            MerPrm.nation = NationNameGenitive(sti(MerPrm.nation));
            string GoodName = "seg_"+goods[sti(MerPrm.QuestGoodsIdx)].name;
            MerPrm.QuestGoodsIdx = GetConvertStr(GoodName, "ShipEatGood.txt");
            MerPrm.sColony = GetConvertStr(MerPrm.sColony+" Town", "LocLables.txt");
            MerPrm.sNextColony = GetConvertStr(MerPrm.sNextColony+" Port", "LocLables.txt");

            tresult += GetAssembledString( reztext,	MerPrm);


            ReOpenQuestHeader("MerchantOnMap");
            AddQuestRecord("MerchantOnMap", 1+rand(2));
    		AddQuestUserData("MerchantOnMap", "snation", MerPrm.nation);
    		AddQuestUserData("MerchantOnMap", "sQuestGoodsIdx", MerPrm.QuestGoodsIdx);
    		AddQuestUserData("MerchantOnMap", "sColony", MerPrm.sColony);
    		AddQuestUserData("MerchantOnMap", "sNextColony", MerPrm.sNextColony);
    		AddQuestUserData("MerchantOnMap", "sShipName", MerPrm.ShipName);
			AddQuestUserData("MerchantOnMap", "sSex", GetSexPhrase("","а"));

            string sQuest = "ClearMerchant";
            SetTimerFunction(sQuest, 0, 0, 5);
            MerPrm.active = true;
            //AddQuestRecord();
            //CloseQuestHeader();
            return tresult;
        }
        else
        {
            return NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
        }
}

string AfteMerchantRumour()
{
    ref MerPrm,CurTpl;
    string reztext, tresult;
    makeref(MerPrm, MerchantParam);
    int tNum = TplNameToNum("MerchantRumour");

    makeref(CurTpl,  templat[tNum]);
    int lngFileID = LanguageOpenFile("RumourTexts.txt");
    string tid = CurTpl.name+"_t"+rand(sti(CurTpl.texts)-1);
    reztext = LanguageConvertString(lngFileID, tid);
    tresult += GetAssembledString( reztext,	MerPrm);
    if (tresult!="") return tresult;
    else
	{
		return NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
	}

}