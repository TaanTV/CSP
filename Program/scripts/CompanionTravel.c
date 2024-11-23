// Warship 17.07.08 Свободное плавание компаньонов

void CompanionTravel_SetTraveller(ref _NPChar)
{
	ref sld;
	string sTemp, attrLoc, attr;
	int fChance;
	sld = &characters[sti(_NPChar.realcompanionidx)];

	if(!CheckAttribute(PChar, "CompanionTravel")) PChar.CompanionTravel = 0;
	PChar.CompanionTravel = sti(PChar.CompanionTravel) + 1; // Сколько компаньонов уже отправили
	for(iTemp=1; iTemp<=3; iTemp++) // Нужно, чтоб была свободная группа
	{
		if(Group_IsDead("CompanionTravel_Companion"+iTemp))
			attr = "Companion" + iTemp;
	}

	CompanionTravel_SetSpecialShipAttributes(sld);
	sld.CompanionTravel.GroupID = "CompanionTravel_" + attr; // Это группа. Её потом нужно будет потереть

	sTemp = _NPChar.ID;
	PChar.CompanionTravel.(attr).ID = sld.ID ; // Запомним ID
	PChar.CompanionTravel.(attr).Days = sti(sld.CompanionTravel.Days); // Сколько дней будет путешествовать
	PChar.CompanionTravel.(attr).ToColonyID = sld.CompanionTravel.ToColonyID; // Где с ним назначена встреча

	fChance = CompanionTravel_CalculateSinkChance(sld, PChar.CompanionTravel.(attr).ToColonyID);
	if(fChance > rand(100)) // Не дойдет до места назначения
	{
		// PChar.CompanionTravel.(attr).Sink = true;
	}

	attrLoc = "CompanionTravel_" + attr; // Заносим в группу

	Group_FindOrCreateGroup(attrLoc);
	Group_SetType(attrLoc, "pirate");
	Group_AddCharacter(attrLoc, PChar.CompanionTravel.(attr).ID);
	Group_SetGroupCommander(attrLoc, PChar.CompanionTravel.(attr).ID);
	Group_SetTaskRunaway(attrLoc, PLAYER_GROUP); // Уходим
	Group_LockTask(attrLoc);

	// Записи в СЖ
	ReOpenQuestHeader("CompanionTravel");
	AddQuestRecord("CompanionTravel", "1");
	AddQuestUserData("CompanionTravel", "sDays", PChar.CompanionTravel.(attr).Days);
	AddQuestUserData("CompanionTravel", "sShipInfo", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].Basename + "Voc")) + " '" + sld.Ship.name + "'");
	AddQuestUserData("CompanionTravel", "sCapName", GetFullName(sld)); 
//xxxZohanxxx Путешествия -->
	if (sld.CompanionTravel.ToColonyID == "Caiman")
	{
	AddQuestUserData("CompanionTravel", "sColony", XI_ConvertString("Caiman" + "Dat"));
	Log_Info(GetConvertStrWithReplace("Variable_CompanionTravel_1", "Logs.txt", "#space#", " ") + XI_ConvertString("Caiman" + "Gen"));
	}
	if (sld.CompanionTravel.ToColonyID == "Dominica")
	{
	AddQuestUserData("CompanionTravel", "sColony", XI_ConvertString("Dominica" + "Dat"));
	Log_Info(GetConvertStrWithReplace("Variable_CompanionTravel_2", "Logs.txt", "#space#", " ") + XI_ConvertString("Dominica" + "Gen"));
	}
	if (sld.CompanionTravel.ToColonyID == "StLucia")
	{
	AddQuestUserData("CompanionTravel", "sColony", XI_ConvertString("StLucia" + "Dat"));
	Log_Info(GetConvertStrWithReplace("Variable_CompanionTravel_3", "Logs.txt", "#space#", " ") + XI_ConvertString("StLucia" + "Gen"));
	}
	if (sld.CompanionTravel.ToColonyID == "Terks")
	{
	AddQuestUserData("CompanionTravel", "sColony", XI_ConvertString("Terks" + "Dat"));
	Log_Info(GetConvertStrWithReplace("Variable_CompanionTravel_4", "Logs.txt", "#space#", " ") + XI_ConvertString("Terks" + "Gen"));
	}
	else
	{
	AddQuestUserData("CompanionTravel", "sColony", XI_ConvertString("Colony" + sld.CompanionTravel.ToColonyID + "Dat"));
	Log_Info(GetConvertStrWithReplace("Variable_CompanionTravel_5", "Logs.txt", "#space#", " ") + XI_ConvertString("Colony" + sld.CompanionTravel.ToColonyID + "Gen"));
	}

	Log_TestInfo("=====" + attr + "=====");
	Log_TestInfo("ID компаньона, отправившегося в плавание - " + PChar.CompanionTravel.(attr).ID);
	Log_TestInfo(GetConvertStrWithReplace("Variable_CompanionTravel_6", "Logs.txt", "#space#", " ") + PChar.CompanionTravel.(attr).Days + GetConvertStrWithReplace("Variable_CompanionTravel_7", "Logs.txt", "#space#", " "));
	Log_TestInfo("Назначена встреча в колонии с ID - " + PChar.CompanionTravel.(attr).ToColonyID);
	Log_TestInfo(GetConvertStrWithReplace("Variable_CompanionTravel_8", "Logs.txt", "#space#", " ")+fChance);
	Log_TestInfo(GetConvertStrWithReplace("Variable_CompanionTravel_9", "Logs.txt", "#space#", " ")+!CheckAttribute(PChar, "CompanionTravel."+(attr)+".Sink"));
	RemoveCharacterCompanion(PChar, sld);
}

void CompanionTravel_ProcessAllTravellers() // Этот метод вызывается каждый день из QuestActions()
{
	aref arTravellers;
	if (!CheckAttribute(PChar,"CompanionTravel")) return;
	makearef(arTravellers, PChar.CompanionTravel);

	string sCompanionTraveller;
	for(int i=0; i<GetAttributesNum(arTravellers); i++)
	{
		sCompanionTraveller = GetAttributeName(GetAttributeN(arTravellers, i));
		Log_TestInfo(GetConvertStrWithReplace("Variable_CompanionTravel_10", "Logs.txt", "#space#", " ")+sCompanionTraveller);
		CompanionTravel_DayUpdate(sCompanionTraveller);
	}
}

void CompanionTravel_DayUpdate(string sCompanion) // Обработка конкретного компаньона-путешественника
{
	string sID
	if (CheckAttribute(PChar, "CompanionTravel."+sCompanion+".ID")) sID = PChar.CompanionTravel.(sCompanion).ID; else {DeleteAttribute(PChar,"CompanionTravel."+sCompanion); return;}
	int iDays = sti(PChar.CompanionTravel.(sCompanion).Days);
	ref rCompanion = CharacterFromID(sID);
	CompanionTravel_SetExperienceToTraveller(rCompanion); // Начисляем экспу
	if(!bNoEatNoRats)
	{
		DailyEatCrewUpdateForShip(rCompanion, true);
	}
	CompanionTravel_SetRandomEvent(rCompanion); // Случайное событие по типу покоцался корпус или паруса и т.д.
	iDays--;
	PChar.CompanionTravel.(sCompanion).Days = iDays;
	if (sCompanion == "") trace("sukasuka"+sCompanion)
	Log_TestInfo(sCompanion+" - осталось дней (если < 0, значит ждет в порту) - "+iDays);
	if(iDays == 0) // Если дней < 0, хначит он уже ждет в колонии
	{
		CompanionTravel_TimerToSetInColony(sCompanion); // Доехал - ставим в колонию или топим
	}

	if(iDays == -30) // Убираем его из колонии - слишком долго игрок не мог добраться до него
	{
		CompanionTravel_DeleteCompanion(sID, sCompanion, true);
	}
}

void CompanionTravel_TimerToSetInColony(string sCompanion) // Таймер вышел (т.е. компаньона нужно потавить в колонию или потопить)
{
	if(!CheckAttribute(PChar, "CompanionTravel."+sCompanion+".ToColonyID")
	|| !CheckAttribute(PChar, "CompanionTravel."+sCompanion+".ID") || !CheckAttribute(PChar, "CompanionTravel."+sCompanion+".Days"))
	{
		Log_Info(GetConvertStrWithReplace("Variable_CompanionTravel_11", "Logs.txt", "#space#", " ")+sCompanion+". Немедленно сообщите Warship'у.");
		return;
	}

	string sID = PChar.CompanionTravel.(sCompanion).ID;
	string sColony = PChar.CompanionTravel.(sCompanion).ToColonyID;
	int iDays = sti(PChar.CompanionTravel.(sCompanion).Days);
	ref sld = CharacterFromID(sID);

	if(CheckAttribute(PChar, "CompanionTravel."+sCompanion+".Sink")) // Не дошёл до места назначения
	{
		CompanionTravel_DeleteCompanion(sID, sCompanion, false);
		return;
	}

	CompanionTravel_SetCompanionToColony(sColony, "CompanionTravel_"+sCompanion, sID); // Ставим его в колонию
}

void CompanionTravel_DeleteCompanion(string sID, string sCompanion, bool WaitInColony)
{
	ref rTraveller = CharacterFromID(sID);
	DeleteAttribute(rTraveller, "CompanionTravel");
	rTraveller.LifeDay = 0;
	DeleteAttribute(PChar, "CompanionTravel."+sCompanion);
	PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Тут счетчик уменьшаем
	AddQuestRecord("CompanionTravel", "3");
	AddQuestUserData("CompanionTravel", "sCapName", GetFullName(rTraveller)); 
	AddQuestUserData("CompanionTravel", "sShipInfo", GetStrSmallRegister(XI_ConvertString(RealShips[sti(rTraveller.Ship.Type)].Basename + "Voc")) + " '" + rTraveller.Ship.name + "'");
	string strReason; 
	if(WaitInColony)
	{
		Log_TestInfo("Кэпа группы CompanionTravel_"+sCompanion+GetConvertStrWithReplace("Variable_CompanionTravel_12", "Logs.txt", "#space#", " "));
		strReason = "не дождался вас в колонии и покинул её.";
	}
	else
	{
		Log_TestInfo("Судно кэпа группы CompanionTravel_"+sCompanion+GetConvertStrWithReplace("Variable_CompanionTravel_13", "Logs.txt", "#space#", " "));
		strReason = "не добрался до места встречи.");
	}
	Log_Info(XI_ConvertString(RealShips[sti(rTraveller.Ship.Type)].Basename)+" '"+rTraveller.Ship.name+"' " + strReason); 
	AddQuestUserData("CompanionTravel", "sReason", strReason);
	if(GetAttrValue(PChar, "CompanionTravel") == 0) CloseQuestHeader("CompanionTravel");
	Group_DeleteAtEnd("CompanionTravel_"+sCompanion);
}

void CompanionTravel_SetCompanionToColony(string sColony, string sGroupID, string sID) // Поставим компаньона в колонию
{
	if (sColony == "Terks" || sColony == "Dominica" || sColony == "StLucia")
	{
		if (sColony == "Terks")	sIsland = "Terks";
		if (sColony == "StLucia")	sIsland = "StLucia";
		if (sColony == "Dominica")	sIsland = "Dominica";	//это можно удалить, если добавить Люсию в списко колоний
	}
	else string sIsland = colonies[FindColony(sColony)].Island;
	Log_TestInfo(GetConvertStrWithReplace("Variable_CompanionTravel_14", "Logs.txt", "#space#", " ") + sID + GetConvertStrWithReplace("Variable_CompanionTravel_15", "Logs.txt", "#space#", " ") + sGroupID + GetConvertStrWithReplace("Variable_CompanionTravel_16", "Logs.txt", "#space#", " ") + sColony + " (" + sIsland + ")");
	ref sld = CharacterFromID(sID);
	sld.CompanionTravel.WaitOnColony = true;
	sld.DeckDialogNode = "hired";
	Group_FindOrCreateGroup(sGroupID);
	Group_SetType(sGroupID, "pirate");
	Group_AddCharacter(sGroupID, sID);
	Group_SetGroupCommander(sGroupID, sID);
	Group_SetTaskNone(sGroupID);
	if(sIsland != "Barbados")
		Group_SetAddress(sGroupID, sIsland, "Quest_Ships", "reload_fort1_siege");
	else
		Group_SetAddress(sGroupID, sIsland, "Quest_Ships", "reload_fort1__siege");
	Group_LockTask(sGroupID);
}

float CompanionTravel_CalculateSinkChance(ref _NPC, String _sColony)
{
	Log_TestInfo("=============== Рассчитываем шанс потопления ===============");

	float fChance = 5;
	int iHPPercent = GetHullPercent(_NPC);
	int iSPPercent = GetSailPercent(_NPC);
	int iCrew = sti(_NPC.Ship.Crew.Quantity);
	int iRealShipOptimalCrew = sti(RealShips[sti(_NPC.Ship.Type)].SailorCrew);
	int iSailSkill = GetSummonSkillFromNameSimple(_NPC, SKILL_SAILING);
	int iShipClass = GetCharacterShipClass(_NPC);
	int iNeedSailSkill = GetShipClassNavySkill(iShipClass);
	int iDays = makeint(GetDistanceToColony2D(_sColony)/100); // Сколько дней идти до колонии

	Log_TestInfo(GetConvertStrWithReplace("Variable_CompanionTravel_17", "Logs.txt", "#space#", " ")+fChance);
	if(iHPPercent < 50) fChance = fChance+(50-iHPPercent)*1.5; // Проценты потопления за состояние корпуса
	Log_TestInfo("База + учёт корпуса - "+fChance);

	if(iSPPercent < 50) fChance = fChance+(50-iSPPercent)*0.5; // За состояние парусов
	Log_TestInfo("База + учёт корпуса + учёт парусов - "+fChance);

	if(iSailSkill < iNeedSailSkill) fChance = fChance+(iNeedSailSkill-iSailSkill)*0.8; // Учитываем скилл навигации
	Log_TestInfo("База + учёт корпуса + учёт парусов + учёт навы - "+fChance);

	if(iDays > 7) fChance = fChance*((iDays-7)*0.1+1);
	Log_TestInfo("( База + учёт корпуса + учёт парусов + учёт навы ) * учёт дней - "+fChance);
	Log_TestInfo("=============== Шанс потопления рассчитан. Шанс - "+fChance+" ===============");

	return fChance;
}

void CompanionTravel_SetSpecialShipAttributes(ref _NPChar)
{
	_NPChar.Abordage.Enable = false;
	_NPChar.DontCheckFlag = true;
	_NPChar.AlwaysFriend        = true;
	_NPChar.ShipEnemyDisable  = true;
}

void CompanionTravel_DeleteSpecialShipAttributes(ref _NPChar)
{
	DeleteAttribute(_NPChar, "Abordage.Enable");
	DeleteAttribute(_NPChar, "DontCheckFlag");
	DeleteAttribute(_NPChar, "AlwaysFriend");
	DeleteAttribute(_NPChar, "ShipEnemyDisable");
}

void CompanionTravel_SetExperienceToTraveller(ref _NPC)
{
	int iRank = sti(_NPC.Rank);
	int iExp = (rand(1)+1)+(iRank/2);
	AddCharacterExpToSkill(_NPC, "Leadership", iExp);
	AddCharacterExpToSkill(_NPC, "Fortune", iExp);
	AddCharacterExpToSkill(_NPC, "Sailing", iExp);
	AddCharacterExpToSkill(_NPC, "Accuracy", iExp/2);
	AddCharacterExpToSkill(_NPC, "Cannons", iExp/2);
}

/*void CompanionTravel_SetEatFood(ref _NPC) // to_do del
{
	int iCrew = GetCrewQuantity(_NPC);
	int iSlaves = GetCargoGoods(_NPC, GOOD_SLAVES);
	int iCrewEat = makeint((iCrew+6) / 10);
	int iSlavesEat = makeint((iCrew+6) / 20);
	int iRumQty = GetCargoGoods(_NPC, GOOD_RUM);
	int iMedicamentQty = GetCargoGoods(_NPC, GOOD_MEDICAMENT);
	int iTemp = iCrew/30;
	RemoveCharacterGoodsSelf(_NPC, GOOD_FOOD, iCrewEat); // Съела команда
	RemoveCharacterGoodsSelf(_NPC, GOOD_FOOD, iSlavesEat); // Съели рабы
	if(iTemp < 5) iTemp=5;
	if(iMedicamentQty < iTemp)
	{
		if(iCrew > 10)
		{
			_NPC.Ship.Crew.Quantity = iCrew - rand(9);
			_NPC.Ship.Crew.Morale = sti(_NPC.Ship.Crew.Morale)-1;
		}
	}
	else
	{
		RemoveCharacterGoodsSelf(_NPC, GOOD_MEDICAMENT, iTemp);
	}

	if(iRumQty >= iTemp)
	{
		RemoveCharacterGoodsSelf(_NPC, GOOD_RUM, iTemp);
		_NPC.Ship.Crew.Morale = sti(_NPC.Ship.Crew.Morale)+1;
	}
	else
	{
		_NPC.Ship.Crew.Morale = sti(_NPC.Ship.Crew.Morale)-1;
	}
}*/

void CompanionTravel_SetRandomEvent(ref _NPC) // Просто случайные события для компаньона
{
	int iRand = rand(4);
	int iShipHP = sti(_NPC.Ship.HP);
	int iShipHPMax = sti(RealShips[sti(_NPC.Ship.Type)].hp);
	int iShipSP = GetSailPercent(_NPC);
	int iCrew = GetCrewQuantity(_NPC);
	int iMinCrew = sti(RealShips[sti(_NPC.Ship.Type)].mincrew)

	switch(iRand)
	{
		case 0: // Покоцался корпус
			if(iShipHP <= iShipHPMax/10) break;
			_NPC.Ship.HP = sti(_NPC.Ship.HP) - (iShipHPMax/30);
		break;

		case 1: // Покоцались паруса
			/*if(iShipSP <= 10) break;
			_NPC.Ship.SP = iShipSP-5;*/ // не работает
		break;

		case 2: // Минусуем команду
			if(iCrew <= iMinCrew) break;
			_NPC.Ship.Crew.Quantity = iCrew-(rand(4)+2);
		break;

		case 3:

		break;

		case 4:

		break;
	}
}
